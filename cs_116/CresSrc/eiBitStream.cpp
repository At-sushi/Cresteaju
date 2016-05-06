eiBitStream::eiBitStream(void)
{
	eimemset(&Buffer,0,sizeof(Buffer));
	eimemset(&LZ77Range[0],0,sizeof(LZ77Range));

	Buffer.hMemory = NULL;
	Buffer.BitPos = 7;
	Buffer.BytePos = 0;

	MinLength = 3;//---�ŒZ��v������
	MaxLength = 65535;//---�Œ���v������
	SearchRange = 65535;//---�T���͈�
	Reserch = 0;//---����ɍŒ���v�������T����
	HashSize = EB_HASHTABLE_SIZE;
	AddPointer = 1;
	HashMakeMode = 0;
}

eiBitStream::~eiBitStream()
{
}

void eiBitStream::SetOption(int min,int max,int range,int res,int hash,int add,int hash_make_mode)
{
	MinLength = min;
	MaxLength = max;
	SearchRange = range;
	Reserch = res;
	HashSize = hash;
	AddPointer = add;
	HashMakeMode = hash_make_mode;
}

int eiBitStream::AllocNewBuffer(int size)
{
	Buffer.hMemory = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT,size);
	Buffer.pMemory = (ei_u8 *)GlobalLock(Buffer.hMemory);

	Buffer.BufferSize = size;

	return 1;
}

int eiBitStream::ReallocBuffer(int size)
{
	Buffer.BufferSize = size;

	return 1;
}

int eiBitStream::FreeBuffer(void)
{
	if(Buffer.hMemory){
		GlobalUnlock(Buffer.hMemory);
		GlobalFree(Buffer.hMemory);
		Buffer.hMemory = NULL;
	}

	return 1;
}

void eiBitStream::ResetPointer(void)
{
	//---DWORD BufferSize ,OriginalSize, CheckSum
	SetPointer(EB_HEADSIZE);
}

void eiBitStream::SetPointer(int pos)
{
	Buffer.BitPos = 7;
	Buffer.BytePos = pos;
}

//---�`�F�b�N�f�[�^�v�Z
ei_u32 eiBitStream::CalcCheckData(ei_u8 *pMemory,int Size)
{
	int p = 0;
	ei_u32 CheckData = 0;

	while(p < Size){
		CheckData += (*(pMemory + p));
		p ++;
	}

	return CheckData;
}

//-----------------------------------------------
//---�n�b�V��
void eiBitStream::InitHash(void)
{
	//--- -1�Ŗ��߂�
	memset(&HashTable[0],0xff,sizeof(HashTable));
	HashHit = 0;
	HashMiss = 0;
}

void eiBitStream::InsertHash(ei_u32 hash1,ei_u32 value)
{
	HashTable[hash1] = value;
}

ei_u32 eiBitStream::CalcHash(ei_u8 *pMemory,int size)
{
	int a;
	ei_u32 hash = 0;

	if(HashSize){
		for(a = 0;a < size; a ++){
//			hash = ((hash << SHIFT_BIT)  | ((hash >> (32 - SHIFT_BIT)) & SHIFT_MASK))
//				^ (*(pMemory + a));
			hash = (hash << SHIFT_BIT) ^ (*(pMemory + a));
//			hash += (*(pMemory + a));
		}

//		(*hash) &= (HashSize - 1);
		hash %= HashSize;
//		(*hash) = (hash * 12347 + 123456789) >> (sizeof(ei_u32) - 15);
	}
	return hash;
}

//-----------------------------------------------
//---���k

//---�R�s�[
int eiBitStream::CopyBuffer(ei_u8 *pMemory,ei_u8 *pCopy,int Size)
{
	memcpy(pMemory,pCopy,Size);

	return 1;
}

//---���o�C�g��������r����
int eiBitStream::Compare(ei_u8 *pMemory,ei_u8 *pCompare,int Size)
{
	int a;

	for(a = 0;a < Size;a ++){//---Size:�ő匟����
		if(*(pMemory + a) != *(pCompare + a)){
			//---�������
			if(a < MinLength){
				return 0;
			}
			//---�ŏ���v���𖞂����Ă����
			break;
		}
	}

	return a;
}

#define BIT1 15
#define BIT2 127
#define BIT3 1023
#define BIT4 8191
#define BIT5 65535

#define BITL1 4
#define BITL2 7
#define BITL3 10
#define BITL4 13
#define BITL5 16

int eiBitStream::GetBitLength(int data)
{
	int a = 0;

	if(data <= BIT1){
		//5bit
		a = BITL1;
	} else if(data <= BIT2){
		//8bit
		a = BITL2;
	} else if(data <= BIT3){
		//12bit
		a = BITL3;
	} else if(data <= BIT4){
		//16bit
		a = BITL4;
	} else if(data <= BIT5){
		//16bit
		a = BITL5;
	}

	return a;
}

int eiBitStream::GetBitID(int data)
{
	int a = 0;

	if(data <= BIT1){
		//5bit
		a = 0;
	} else if(data <= BIT2){
		//8bit
		a = 2;
	} else if(data <= BIT3){
		//12bit
		a = 6;
	} else if(data <= BIT4){
		//16bit
		a = 14;
	} else if(data <= BIT5){
		//16bit
		a = 30;
	}

	return a;
}

int eiBitStream::GetBitIDLength(int data)
{
	int a = 0;

	if(data <= BIT1){
		//5bit
		a = 1;
	} else if(data <= BIT2){
		//8bit
		a = 2;
	} else if(data <= BIT3){
		//12bit
		a = 3;
	} else if(data <= BIT4){
		//16bit
		a = 4;
	} else if(data <= BIT5){
		//16bit
		a = 5;
	}

	return a;
}

//---�Œ���v�������T��
int eiBitStream::SerchData(ei_u8 *pMemory,ei_u8 *pStart,ei_u8 *pEnd,ei_u8 *pTop,int *MatchSize,int *MatchPos)
{
	int size,searchsize = 0,pos;
	ei_u8 *pSearch = pStart;
	ei_u32 hash = 0;

	*MatchSize = 0;
	*MatchPos = 0;

//------------------------------------------------
	searchsize = pMemory - pStart;
	if(searchsize > MaxLength)
		searchsize = MaxLength;
	if(pMemory + searchsize >= pEnd)
		searchsize = pEnd - pMemory;
	if(searchsize < MinLength)
		return 0;

	if(HashSize){
		//---�n�b�V���v�Z
		hash = CalcHash(pMemory,MinLength);

		if(HashTable[hash] != -1){
			//---�n�b�V��������I
			//---���Έʒu
			pos = (pMemory - pTop) - HashTable[hash];
			if(pos < SearchRange && pos >= MinLength){
				//---�T���͈͓��ɂ���̂Ȃ�
				if(searchsize > pos)
					searchsize = pos;
				size = Compare(pMemory,pMemory - pos,searchsize);

				if(size >= MinLength){
					*MatchSize = size;//---����������
					*MatchPos = pos;//---�������O����
					HashHit ++;
				} else {
					HashMiss ++;
				}
			}
		}

		//---�n�b�V���l��������
		if(*MatchSize){
			InsertHash(hash,pMemory - pTop);
		}

		if(*MatchSize)
			return 1;
		return 0;
	} else {

		while(pSearch < pMemory - MinLength){
			searchsize = pMemory - pStart;
			if(searchsize > MaxLength)
				searchsize = MaxLength;
			if(pSearch + searchsize >= pMemory)
				searchsize = pMemory - pSearch;
			if(searchsize <= MinLength)
				break;
		
			//---��r
			size = Compare(pMemory,pSearch,searchsize);
			pos = pMemory - pSearch;

			if(size >= MinLength && size >= *MatchSize){
				*MatchSize = size;//---����������
				*MatchPos = pos;//---�������O����
				//---���T�[�`�`�F�b�N
				if(!Reserch && *MatchSize < MaxLength){
					break;
				}
			}

			pSearch += 1;//AddPointer;
		}

		if(*MatchSize)
			return 1;
		return 0;
	}
}

void eiBitStream::MakeHash(ei_u8 *pMemory,ei_u8 *pStart,ei_u8 *pEnd)
{
	ei_u32 hash = 0;
	int searchsize = 0;

	searchsize = MinLength;
	if(pMemory - pStart <= searchsize)
		searchsize = (pMemory - pStart) - 1;
	if(searchsize >= MaxLength)
		searchsize = MaxLength;
	hash = CalcHash(pMemory - (searchsize),searchsize);
	InsertHash(hash,(pMemory - pStart) - (searchsize));

}

int eiBitStream::Compress(void *pmem,int size)
{
	ei_u8 *pStart = (ei_u8 *)pmem,
		*pEnd = (ei_u8 *)pmem + size,
		*pMemory = pStart,*pSearch = pStart;
	int AddSize = 0,MatchSize = 0,MatchPos = 0;
	int a = 0;
	ei_u32 hash = 0;

	//---�o�b�t�@�[���Z�b�g
	ResetPointer();
	InitHash();
	//---�I���W�i���T�C�Y
	Buffer.OriginalSize = size;

	while(pMemory < pEnd){
		//---�n�b�V��----------------------------------

		if((pMemory - pStart) < MinLength){
			//---�o�b�t�@�[�|�C���^���ŏ���v����菬�������
			WriteBit(0,1);//---�f�[�^�t���b�O
			WriteBit(*pMemory,8);//---�f�[�^
			AddSize = 1;
		} else {
			if(SerchData(pMemory,pSearch,pEnd,pStart,&MatchSize,&MatchPos)
				&& (GetBitIDLength(MatchSize) + GetBitIDLength(MatchPos)
				+ GetBitLength(MatchSize) + GetBitLength(MatchPos) + 1) <= MatchSize * 8
				){
				//---��v�����񂪌���������
				WriteBit(1,1);//---���k�^�t���b�O
				WriteBit(GetBitID(MatchSize),GetBitIDLength(MatchSize));
				if(GetBitLength(MatchSize) <= 8){
					WriteBit(MatchSize,GetBitLength(MatchSize));//---�}�b�`�T�C�Y
				} else {
					WriteBit(MatchSize >> (GetBitLength(MatchSize) - 8),8);
					WriteBit(MatchSize,GetBitLength(MatchSize) - 8);
				}

				WriteBit(GetBitID(MatchPos),GetBitIDLength(MatchPos));
				if(GetBitLength(MatchPos) <= 8){
					WriteBit(MatchPos,GetBitLength(MatchPos));//---�}�b�`�|�W�V����
				} else {
					WriteBit(MatchPos >> (GetBitLength(MatchPos) - 8) , 8);
					WriteBit(MatchPos,GetBitLength(MatchPos) - 8);
				}

				a = GetBitLength(MatchPos);
/*				if(a == BITL1)
					LZ77Range[0]++;
				else if(a == BITL2)
					LZ77Range[1]++;
				else if(a == BITL3)
					LZ77Range[2]++;
				else if(a == BITL4)
					LZ77Range[3]++;
				else if(a == BITL5)
					LZ77Range[4]++;
*/
				a = GetBitLength(MatchSize);
/*				if(a == BITL1)
					LZ77Range[0]++;
				else if(a == BITL2)
					LZ77Range[1]++;
				else if(a == BITL3)
					LZ77Range[2]++;
				else if(a == BITL4)
					LZ77Range[3]++;
				else if(a == BITL5)
					LZ77Range[4]++;
*/
//				WriteBit(MatchSize,8);//---�}�b�`�T�C�Y
//				WriteBit(MatchPos,8);//---�}�b�`�|�W�V����

				AddSize = MatchSize;
			} else {
				for(a = 0;a < AddPointer && pMemory < pEnd;a ++){
					WriteBit(0,1);//---�f�[�^�t���b�O
					WriteBit(*(pMemory + a),8);//---�f�[�^
				}
				AddSize = AddPointer;
			}
		}

		if(HashMakeMode == 0){
			MakeHash(pMemory,pStart,pEnd);
			//---�|�C���^��i�߂�
			pMemory += AddSize;
		} else {
			//---�|�C���^��i�߂�
			for(a = 0;a < AddSize;a ++){
				MakeHash(pMemory,pStart,pEnd);
				pMemory ++;
			}
		}

		//---�T���X�^�[�g�ʒu
		if(pMemory - pSearch > SearchRange){
			pSearch = pMemory - SearchRange;
		}
	}

	if(Buffer.BitPos != 7){
		Buffer.BytePos ++;
	}
	Buffer.FreezeSize = Buffer.BytePos;

	//--------------------------------------------------------
	*(ei_s32 *)(Buffer.pMemory + 0) = Buffer.FreezeSize;
	*(ei_s32 *)(Buffer.pMemory + 4) = Buffer.FreezeSize + 12345;
	*(ei_s32 *)(Buffer.pMemory + 8) = Buffer.OriginalSize;
	Buffer.CheckData = CalcCheckData(Buffer.pMemory + EB_HEADSIZE,Buffer.FreezeSize);
	*(ei_u32 *)(Buffer.pMemory + 12) = Buffer.CheckData;

	return 1;
}

//---��
int eiBitStream::Decompress(void *pmem)
{
	ei_u8 *pStart = (ei_u8 *)pmem,
		*pMemory = pStart,*pSearch = pStart;
	int AddSize = 0,MatchSize = 0,MatchPos = 0,flag = 0;
	int a,id[] = {BITL1,BITL2,BITL3,BITL4,BITL5};

	//---�o�b�t�@�[���Z�b�g
	ResetPointer();

	//---
	Buffer.FreezeSize = *(ei_s32 *)(Buffer.pMemory + 0);
//	Buffer.FreezeSize = *(ei_s32 *)(Buffer.pMemory + 4);
	Buffer.OriginalSize = *(ei_s32 *)(Buffer.pMemory + 8);
	Buffer.CheckData = *(ei_u32 *)(Buffer.pMemory + 12);
	//---�f�[�^�`�F�b�N
/*	char sss[100];
	sprintf(sss,"1:%5d,%5d , %5d\n",Buffer.BytePos,Buffer.FreezeSize,Buffer.OriginalSize);
	eiDebugWriteFile(sss);*/
	if(Buffer.CheckData != CalcCheckData(Buffer.pMemory + EB_HEADSIZE,Buffer.FreezeSize)){
		eiDebugWriteFile("(eiBitStream::Decompress) �`�F�b�N�G���[�I�I\n");
		return 0;
	}

	while(pMemory - pStart < Buffer.OriginalSize){
		flag = ReadBit(1);
		if(flag == 0){
			//---�f�[�^�t���b�O
			*pMemory = (ei_u8)ReadBit(8);
			AddSize = 1;
		} else {
			//---���k�t���b�O
			a = 0;
			while(1){
				if(ReadBit(1) == 0)
					break;
				a ++;
			}
//			if(a >= 5)
//				//---���Ă���I
//				return 0;

			if(id[a] <= 8){
				MatchSize = ReadBit(id[a]);
			} else {
				MatchSize = (ReadBit(8) << (id[a] - 8)) | ReadBit(id[a] - 8);
			}

			a = 0;
			while(1){
				if(ReadBit(1) == 0)
					break;
				a ++;
			}
//			if(a >= 5)
//				//---���Ă���I
//				return 0;

			if(id[a] <= 8){
				MatchPos = ReadBit(id[a]);
			} else {
				MatchPos = (ReadBit(8) << (id[a] - 8)) | ReadBit(id[a] - 8);
			}

//			MatchSize = ReadBit(8);
//			MatchPos = ReadBit(8);

/*			if((pMemory - pStart) + MatchSize > Buffer.OriginalSize){
				//---�ُ�I��
				return 0;
			}*/
			CopyBuffer(pMemory,pMemory - MatchPos,MatchSize);

			AddSize = MatchSize;
		}

		pMemory += AddSize;
	}

/*	if((pMemory - pStart) != Buffer.OriginalSize){
		return 0;
	}*/
/*	char ss[100];
	sprintf(ss,"2:%5d,%5d , %5d\n",Buffer.BytePos,Buffer.FreezeSize,Buffer.OriginalSize);
	eiDebugWriteFile(ss);*/
/*	if(!(Buffer.BytePos == Buffer.FreezeSize || Buffer.BytePos + 1 == Buffer.FreezeSize)){
		return 0;
	}*/

	return 1;
}

//------------------------------------------
//---�r�b�g����֐�

void eiBitStream::AddBit(int bit)
{
	Buffer.BitPos -= bit;

	if(Buffer.BitPos < 0){
		//---���̃o�C�g��
		Buffer.BitPos += 8;
//		Buffer.BitPos = 7;
		//---add byte
//		AddByte(1);
		Buffer.BytePos ++;
//		Buffer.FreezeSize ++;
		if(Buffer.BytePos >= Buffer.BufferSize){
			//---�T�C�Y���傫���Ȃ�����
			ReallocBuffer(Buffer.BytePos + 4096);
		}
	}
}

void eiBitStream::AddByte(int byte /*= 1*/)
{
	Buffer.BytePos += byte;
//	Buffer.FreezeSize += byte;
	if(Buffer.BytePos >= Buffer.BufferSize){
		//---�T�C�Y���傫���Ȃ�����
		ReallocBuffer(Buffer.BytePos + 4096);
	}
}


int eiBitStream::ReadBit(int bit)
{
	ei_u16 w;
	static ei_u16 mask[] = {0,0x01,0x03,0x07,0x0f,0x1f,0x3f,0x7f,0xff};

	w = *(ei_u16 *)(Buffer.pMemory + Buffer.BytePos);
	w = (ei_u16)(((w >> 8) | (w << 8)) >> ((Buffer.BitPos + 1) - bit + 8));
	AddBit(bit);

	return (w & mask[bit]);
}

void eiBitStream::WriteBit(int data,int bit)
{
	ei_u16 w;

	//---�r�b�g�ʒu�ɃV�t�g
	w = (ei_u16)(data << ( (Buffer.BitPos + 1) - bit + 8));

	//---��������
	*(ei_u16 *)(Buffer.pMemory + Buffer.BytePos) = (ei_u16)(
		*(ei_u16 *)(Buffer.pMemory + Buffer.BytePos) | ((w >> 8) | (w << 8)));
	AddBit(bit);
}


int eiBitStream::WriteCompressFile(eiFile *pFile)
//int eiBitStream::WriteCompressFile(FILE *fp)
{
	if(pFile->Write(Buffer.pMemory,sizeof(ei_u8),Buffer.FreezeSize + EB_HEADSIZE)
		!= (int)((Buffer.FreezeSize + EB_HEADSIZE) * sizeof(ei_u8))){
//		fclose(fp);
		pFile->Close();
		return 0;
	}

	return 1;
}

//---�t�@�C���ɏ�������
int eiBitStream::WriteCompressFile(eistr *name)
{
//	FILE *fp;
	eiFile file;

/*	fp = fopen(name,"wb");
	if(fp == NULL)
		return 0;
*/
	file.Open(name,EI_FILE_WRITE | EI_FILE_BINARY);

	if(!WriteCompressFile(&file)){
		return 0;
	}

//	fclose(fp);
	file.Close();

	return 1;
}

int eiBitStream::ReadCompressFile(eiFile *pFile)
//int eiBitStream::ReadCompressFile(FILE *fp)
{
	ei_s32 freeze,frzcheck,original;
	ei_u32 check;

	pFile->Read(&freeze,sizeof(ei_s32),1);
	pFile->Read(&frzcheck,sizeof(ei_s32),1);
	pFile->Read(&original,sizeof(ei_s32),1);
	pFile->Read(&check,sizeof(ei_u32),1);

/*	fread(&freeze,sizeof(ei_s32),1,fp);
	fread(&frzcheck,sizeof(ei_s32),1,fp);
	fread(&original,sizeof(ei_s32),1,fp);
	fread(&check,sizeof(ei_u32),1,fp);
*/
	if(freeze != frzcheck - 12345){
		//---�`�F�b�N�T�C�Y���Ⴆ��
		pFile->Close();
//		fclose(fp);
		return 0;
	}

	AllocNewBuffer(freeze + 256);

	if(pFile->Read(Buffer.pMemory + EB_HEADSIZE,sizeof(ei_u8),freeze)
//	if(fread(Buffer.pMemory + EB_HEADSIZE,sizeof(ei_u8),freeze,fp)
		!= (int)((freeze) * sizeof(ei_u8))){
		pFile->Close();
//		fclose(fp);
		return 0;
	}

	*(ei_s32 *)(Buffer.pMemory +  0) = Buffer.FreezeSize = freeze;
	*(ei_s32 *)(Buffer.pMemory +  8) = Buffer.OriginalSize = original;
	*(ei_u32 *)(Buffer.pMemory + 12) = Buffer.CheckData = check;

	return 1;
}

int eiBitStream::ReadCompressFile(eistr *name)
{
//	FILE *fp;
	eiFile file;

	if(!file.Open(name))
		return 0;
/*	fp = fopen(name,"rb");
	if(fp == NULL)
		return 0;
*/
	ReadCompressFile(&file);
//	ReadCompressFile(fp);

	file.Close();
//	fclose(fp);

/*	fp = fopen(name,"rb");
	if(fp == NULL)
		return 0;

	fread(&freeze,sizeof(ei_s32),1,fp);
	fread(&frzcheck,sizeof(ei_s32),1,fp);
	fread(&original,sizeof(ei_s32),1,fp);
	fread(&check,sizeof(ei_u32),1,fp);

	if(freeze != frzcheck - 12345){
		//---�`�F�b�N�T�C�Y���Ⴆ��
		fclose(fp);
		return 0;
	}

	AllocNewBuffer(freeze + 256);

	if(fread(Buffer.pMemory + EB_HEADSIZE,sizeof(ei_u8),Buffer.FreezeSize,fp)
		!= (Buffer.FreezeSize) * sizeof(ei_u8)){
		fclose(fp);
		return 0;
	}

	*(ei_s32 *)(Buffer.pMemory +  0) = Buffer.FreezeSize = freeze;
	*(ei_s32 *)(Buffer.pMemory +  8) = Buffer.OriginalSize = original;
	*(ei_u32 *)(Buffer.pMemory + 12) = Buffer.CheckData = check;

	fclose(fp);*/

	return 1;
}
