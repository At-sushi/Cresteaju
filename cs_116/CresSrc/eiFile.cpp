/*-----------------------------------------------------------

   eiLibray
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   eiFile.cpp ...eiFile Class

-----------------------------------------------------------*/

//---------------------------
//	eiFile
//---------------------------

eiFile::eiFile(void)
{
	fp = NULL;
	hTempMemory = NULL;
	pTempMemory = NULL;
	FilePointer = 0;
	eimemset(&FileName[0],0,sizeof(FileName));
	eimemset(&LinkName[0],0,sizeof(LinkName));
#ifdef EIUSE_LINK
	eimemset(&elf,0,sizeof(elf));
#endif /* EIUSE_LINK */

	SetLinkFile(NULL);
}

eiFile::eiFile(eistr *lpLinkName)
{
	fp = NULL;
	hTempMemory = NULL;
	pTempMemory = NULL;
	FilePointer = 0;
	eimemset(&FileName[0],0,sizeof(FileName));
	eimemset(&LinkName[0],0,sizeof(LinkName));
#ifdef EIUSE_LINK
	eimemset(&elf,0,sizeof(elf));
#endif /* EIUSE_LINK */

	if(lpLinkName != NULL)
		SetLinkFile(lpLinkName);
	else
		SetLinkFile(NULL);
}

eiFile::~eiFile()
{
	Close();
}

//---リンクファイルをセット
int eiFile::SetLinkFile(eistr *lpLinkName)
{
	if(fp != NULL)
		return 0;

	if(lpLinkName != NULL){
		eistr *p = lpLinkName,*q = LinkName;
		do {
			*q = *p;
			p ++;
			q ++;
		} while(*p != NULL);
//		sprintf(LinkName,"%s",lpLinkName);
	}

	return 1;
}

//---開く
int eiFile::Open(eistr *lpFileName,int mode /*= EI_FILE_READ*/)
{
	if(LinkName[0]){
		//---リンクファイルなら
		if(mode & EI_FILE_READ){
			fp = fopen(LinkName,"rb");
			if(fp == NULL){
				return 0;
			}
#ifdef EIUSE_LINK
			if(eiFindLinkedFile(lpFileName,&elf,fp,&eli) == 0){
				fclose(fp);
				return 0;
			}
#endif /* EIUSE_LINK */
			//---圧縮ファイルなら
/*			if(elf.Compress){
				eiBitStream eb;

				hTempMemory = eiAllocMemory(elf.RealSize + 1024);
				pTempMemory = (ei_u8 *)eiLockMemory(hTempMemory);
				//---読み込んで解凍
				eb.ReadCompressFile(fp);
				eb.Decompress(pTempMemory);
				eb.FreeBuffer();
			}*/
		} else {
			return 0;
		}
	} else {
		//---通常ファイルなら
		if(mode & EI_FILE_READ){
			fp = fopen(lpFileName,"rb");
		} else if(mode & EI_FILE_WRITE){
			fp = fopen(lpFileName,"wb");
		}
	}

	if(fp == NULL){
		return 0;
	}
	sprintf(FileName,"%s",lpFileName);
//	eiDebugWriteFile(FileName);
//	eiDebugWriteFile(LinkName);

	ReadByte = 0;
	FilePointer = 0;

	return 1;
}

//---閉じる
int eiFile::Close(void)
{
	if(fp != NULL){
		fclose(fp);

		//---変数初期化
		fp = NULL;
		eimemset(&FileName[0],0,sizeof(FileName));
	}

	return 1;
}

//---読み込み
int eiFile::Read(LPVOID lpMemory,int size,int count)
{
	if(fp != NULL){
		unsigned char *lpByte = (LPBYTE)lpMemory;
		int a = 0,read_byte;

		//---圧縮されていたなら
/*		if(elf.Compress){
			read_byte = size * count;
			if(FilePointer + read_byte > elf.RealSize){
				//---ファイルサイズより大きく読み込もうとしていたら直す
				read_byte = elf.RealSize - FilePointer;
			}
			memcpy(lpMemory,pTempMemory + FilePointer,read_byte);
		} else*/ {
			read_byte = fread(lpMemory,size,count,fp) * size;

#ifdef EIUSE_LINK
			if(read_byte && LinkName[0]){
				if(elf.fFlags & EI_LINK_FLAG_CODE1){
					//---暗号化されいたら直す
					for(a = 0;a < read_byte;a ++,lpByte ++){
						(*lpByte) = (ei_u8)((*lpByte) ^ (unsigned char)elf.CodePassword);
//						*(unsigned char *)(lpByte) = (*(unsigned char *)(lpByte)) ^ 0x11;
					}
				}
			}
#endif /* EIUSE_LINK */
		}
		ReadByte += read_byte;
		FilePointer += read_byte;

		return read_byte;
	}
	return 0;
}

int eiFile::Read(LPVOID lpMemory,int read_byte)
{
	return Read(lpMemory,1,read_byte);
}

int eiFile::GetLine(LPVOID lpMemory,int size)
{
	int c = 0,file_size = GetSize();
	BYTE s;

#ifdef EIUSE_LINK
	if(GetAddres() >= file_size){
		return 0;
	}
#endif /* EIUSE_LINK */

	while(Read(lpMemory,sizeof(BYTE),1) && (c - 1) < size
		&& GetAddres() < file_size){
		c ++;
		s = *(BYTE *)lpMemory;
		if(s == 0){
			return c;
		}
		if(s == 0x0d){
			Read(&s,sizeof(BYTE),1);
			if(s == 0x0a){
				*(BYTE *)lpMemory = 0x0a;
				break;
			}
		}

		lpMemory = (LPBYTE)lpMemory + 1;
	}
	lpMemory = (LPBYTE)lpMemory + 1;
	*(BYTE *)lpMemory = 0;

	return c;
}

//---書き込み
int eiFile::Write(LPVOID lpMemory,int size,int count)
{
	if(fp != NULL){
		return fwrite(lpMemory,size,count,fp);
	}
	return 0;
}

int eiFile::Write(LPVOID lpMemory,int read_byte)
{
	return Write(lpMemory,1,read_byte);
}

//---現在のファイルポインターの位置
int eiFile::GetAddres(void)
{
	return FilePointer;
}

//---シーク
int eiFile::Seek(int addres)
{
	if(fp != NULL){
		FilePointer = addres;
//		if(!elf.Compress)
#ifdef EIUSE_LINK
		return fseek(fp , addres + elf.fAddres , SEEK_SET);
#else
		return fseek(fp , addres , SEEK_SET);
#endif /* EIUSE_LINK */

//		return 0;
	}
	return 0;
}

//---サイズ
int eiFile::GetSize(void)
{
	if(fp != NULL){
		if(LinkName[0]){
#ifdef EIUSE_LINK
			return elf.RealSize;//elf.fSize;
#endif /* EIUSE_LINK */
		} else {
			struct _finddata_t fd;

			_findfirst(FileName,&fd);
			return fd.size;
		}
	}

	return 0;
}

//---現在オープン中か
int eiFile::IsOpen(void)
{
	if(fp != NULL)
		return 1;
	return 0;
}

//--------------------------------------------
//--------------------------------------------
//--------------------------------------------

eiMemoryFile::eiMemoryFile(void) : eiFile()
{
	ResetPointer();
	MemorySize = 0;
	hMemory = 0;
	pMemory = NULL;
}

eiMemoryFile::~eiMemoryFile()
{
	Free();
}

int eiMemoryFile::Open(eistr *lpFileName,int mode /*= EI_FILE_READ | EI_FILE_BINARY*/)
{
	ResetPointer();

	return 1;
}

int eiMemoryFile::Close(void)
{
	return 1;
}

void eiMemoryFile::ResetPointer(void)
{
	MemoryPointer = 0;
}

//---メモリーを確保
int eiMemoryFile::Alloc(int size)
{
	hMemory = eiAllocMemory(size);
	if(hMemory){
		pMemory = (ei_u8 *)eiLockMemory(hMemory);
		if(pMemory){
			MemorySize = size;
			return 1;
		}
		Free();
	}

	return 0;
}

//---再確保
int eiMemoryFile::Realloc(int size)
{
	if(MemorySize == 0){
		return Alloc(size);
	}

	if(pMemory){
		eiUnlockMemory(hMemory);
	}

	hMemory = eiReallocMemory(hMemory,size);
	if(hMemory){
		pMemory = (ei_u8 *)eiLockMemory(hMemory);
		if(pMemory){
			MemorySize = size;
			return 1;
		}
	}
	Free();

	return 0;
}

int eiMemoryFile::Free(void)
{
	if(hMemory){
		if(pMemory){
			eiUnlockMemory(hMemory);
			pMemory = NULL;
		}
		eiFreeMemory(hMemory);
		hMemory = 0;
	}
	return 1;
}

void *eiMemoryFile::GetMemory(void)
{
	return pMemory;
}

int eiMemoryFile::Read(LPVOID lpMemory,int size,int count)
{
	if(MemoryPointer + (size * count) >= MemorySize){
//		if(!Realloc(size * count + MemoryPointer + 1024))
//		return 0;
		memcpy(lpMemory,(pMemory + MemoryPointer),MemorySize - MemoryPointer);
		MemoryPointer += (size * count);
		MemoryPointer = MemorySize;
		return 1;
	}

	memcpy(lpMemory,(pMemory + MemoryPointer),size * count);
	MemoryPointer += (size * count);

	return 1;
}

int eiMemoryFile::Read(LPVOID lpMemory,int read_byte)
{
	return Read(lpMemory,1,read_byte);
}

int eiMemoryFile::Write(LPVOID lpMemory,int size,int count)
{
	if(MemoryPointer + (size * count) >= MemorySize){
		if(!Realloc(size * count + MemoryPointer + 1024))
			return 0;
	}

	memcpy((pMemory + MemoryPointer),lpMemory,size * count);
	MemoryPointer += (size * count);

	return 1;
}

int eiMemoryFile::Write(LPVOID lpMemory,int write_byte)
{
	return Write(lpMemory,1,write_byte);
}

int eiMemoryFile::Seek(int addres)
{
	MemoryPointer = addres;

	return 1;
}

int eiMemoryFile::GetSize(void)
{
	return MemoryPointer;
}
