/*-----------------------------------------------------------

   eiLibray
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   eiDib.cpp ...eiDib Class

-----------------------------------------------------------*/

//---------------------------
//	eiDib
//	�r�b�g�}�b�v�������N���X
//---------------------------
#define DIB_INIT() \
{\
	lpBitmap = NULL;\
	lpBitmapInfo = NULL;\
	lpRGB = NULL;\
\
	hgBitmap = NULL;\
	hgBitmapInfo = NULL;\
\
	hBitmap = NULL;\
\
	hMemoryDC = NULL;\
	hwnd = NULL;\
\
	TransColor = 16;\
\
	InfoSize = 0;\
}

#define DIB_DELETE() \
{\
	CheckMemory();\
\
	if(hgBitmap != NULL){\
		eiFreeMemory(hgBitmap);\
		hgBitmap = NULL;\
	}\
	if(hgBitmapInfo != NULL){\
		eiFreeMemory(hgBitmapInfo);\
		hgBitmapInfo = NULL;\
	}\
	if(hBitmap != NULL){\
		DeleteObject(hBitmap);\
		hBitmap = NULL;\
	}\
}

eiDib::eiDib(void)
{
	DIB_INIT();
}

eiDib::~eiDib()
{
/*	if(hgBitmap != NULL){
		eiFreeMemory(hgBitmap);
//		eiDebugWriteFile(FileName);
		eiDebugWriteFile("a!!!!!!!!!\n");
		hgBitmap = NULL;
	}
	if(hgBitmapInfo != NULL){
//		eiDebugWriteFile(FileName);
		eiDebugWriteFile("b!!!!!!!!!\n");
		eiFreeMemory(hgBitmapInfo);
		hgBitmapInfo = NULL;
	}
	if(hBitmap != NULL){
//		eiDebugWriteFile(FileName);
		eiDebugWriteFile("c!!!!!!!!!\n");
		DeleteObject(hBitmap);
		hBitmap = NULL;
	}*/
	DIB_DELETE();
}

void eiDib::Init(void)
{
	DIB_INIT();

/*	lpBitmap = NULL;
	lpBitmapInfo = NULL;
	lpRGB = NULL;

	hgBitmap = NULL;
	hgBitmapInfo = NULL;

	hBitmap = NULL;

	hMemoryDC = NULL;
	hwnd = NULL;

	TransColor = 16;

//	FileName[0] = NULL;
	InfoSize = 0;*/
}

//#define YOBUN

void eiDib::CheckMemory(void)
{
#ifdef YOBUN
/*	if(lpBitmapInfo != NULL){
		if( *( ((BYTE *)lpBitmapInfo) + InfoSize) != 0xff){
			eiDebugWriteFile("(eiDib::Delete) memory was broken! info\n");
			char s[80];
			sprintf(s,"%s: %x \n",FileName,
				*( ((BYTE *)lpBitmapInfo) + InfoSize));
			eiDebugWriteFile(s);
		}
	}
	if(lpBitmap != NULL){
		if( *(BYTE *)(lpBitmap + BitmapSize) != 0xff){
			eiDebugWriteFile("(eiDib::Delete) memory was broken! bitmap\n");
			char s[80];
			sprintf(s,"%s: %x \n",FileName,
				*(BYTE *)(lpBitmap + BitmapSize));
			eiDebugWriteFile(s);
		}
	}*/
#endif
}

void eiDib::Delete(void/*int mode /* = 1 */)
{
/*	CheckMemory();

	if(hgBitmap != NULL){
		eiFreeMemory(hgBitmap);
		hgBitmap = NULL;
	}
	if(hgBitmapInfo != NULL){
		eiFreeMemory(hgBitmapInfo);
		hgBitmapInfo = NULL;
	}
	if(hBitmap != NULL){
		DeleteObject(hBitmap);
		hBitmap = NULL;
	}*/
	DIB_DELETE();
	Init();
}

//�c�h�a���쐬����
int eiDib::Create(int hx,int hy,int color,int mode)
{
	int a,size;
	EIMEMORY hg;

	if(color <= 8){
		//---�p���b�g�܂�
		size = (sizeof(BITMAPINFO)) + (1 << color) * (sizeof(RGBQUAD));
	} else {
		size = (sizeof(BITMAPINFO));
	}

	InfoSize = size;
#ifdef YOBUN
	size += 256;
#endif
	hg = eiAllocMemory(size);
	lpBitmapInfo = (BITMAPINFO *)eiLockMemory(hg);
	if(hg == NULL){
		return FALSE;
	}
	hgBitmapInfo = hg;

//-------------------------
	lpbih = (BITMAPINFOHEADER *)lpBitmapInfo;
	memset(lpbih,0,sizeof(BITMAPINFOHEADER));
#ifdef YOBUN
	memset( ((BYTE *)lpBitmapInfo) + size - 256,0xff,256);
#endif
	lpbih->biSize			= sizeof(BITMAPINFOHEADER);
	lpbih->biWidth			= hx;
	lpbih->biHeight			= hy;
	lpbih->biPlanes			= 1;
	lpbih->biBitCount		= (ei_u16)color;
	lpbih->biCompression	= BI_RGB;
	lpbih->biSizeImage		= 0;
	lpbih->biXPelsPerMeter	= 0;
	lpbih->biYPelsPerMeter	= 0;
	lpbih->biClrUsed= 0;
	lpbih->biClrImportant	= 0;

	xSize					= hx;
	ySize					= hy;
//-------------------------
	if(color <= 8){
		//---�p���b�g
		lpRGB = (LPRGBQUAD)(((BYTE *)(lpBitmapInfo)) + sizeof(BITMAPINFOHEADER));
		RGBQUAD *rgb = lpRGB;

		memset(lpRGB,0,sizeof(RGBQUAD) * (1 << color));
		for(a = 0;a < (1 << color);a ++){
			rgb->rgbBlue = rgb->rgbGreen = rgb->rgbRed = 0;	
			rgb->rgbReserved = 0;
			rgb ++;
		}
		rgb--;
		//---�C���f�b�N�X�̍Ō�𔒂ɂ���
		if((mode & EIDIB_DIBSECTION)){
			rgb->rgbBlue = rgb->rgbGreen = rgb->rgbRed = 255;	
		}
	} else {
		lpRGB = (LPRGBQUAD)((BYTE *)(lpBitmapInfo)); 
	}

	Color = color;

	//�r�b�g�}�b�v���������m��
	if(Color == 24)
		size = (  ((hx * 3) / 4 + ((hx * 3 % 4) != 0)) * 4  ) * hy;
	else if(Color == 16)
		size = (  ((hx * 2) / 4 + ((hx * 2 % 4) != 0)) * 4  ) * hy;
	else if(Color == 8)
		size = (((hx + 3) & ~(3)) * hy * (color / 8));
	else if(Color == 4)
		size = ( ( (hx + 7) & ~(7) ) * hy / 2);
#ifdef YOBUN
	size += 1024;
#endif	
	if(!(mode & EIDIB_DIBSECTION)){
		//---�ʏ�DIB
		hg = eiAllocMemory(size);//GlobalAlloc(GMEM_MOVEABLE,size);
		lpBitmap = (BYTE *)eiLockMemory(hg);//GlobalLock(hg);
		if(hg == NULL){
			Delete();
			return FALSE;
		}
		hgBitmap = hg;
		hBitmap = NULL;
	} else {
		//---DIB�Z�N�V�����쐬
		HBITMAP hb;
		LPBYTE s;

		hb = CreateDIBSection(
			0,lpBitmapInfo,DIB_RGB_COLORS,(VOID **)&s,0,0);
		if(hb == NULL){
			Delete();
			return FALSE;
		}
		if(s == NULL){
			Delete();
			return FALSE;
		}
		hBitmap = hb;
		hgBitmap = NULL;
		lpBitmap = s;
	}

	//---�c�h�a���N���A
	memset(lpBitmap,0,size);
	BitmapSize = size;
#ifdef YOBUN
	memset( ((BYTE *)lpBitmap) + size - 1024,0xff,1024);
	BitmapSize = size - 1024;
#endif
	//�P���C���̃o�C�g��
	if(Color == 24){
		LineSize = ((hx * 3) / 4 + ((hx * 3 % 4) != 0)) * 4;
	} else if(Color == 16){
		LineSize = ((hx * 2) / 4 + ((hx * 2 % 4) != 0)) * 4;
	} else if(Color >= 8){
		LineSize = (((hx + 3) & ~3) * (color / 8));
	} else if(Color == 4){
		LineSize = (((hx + 7) & ~(7)) / 2);
	}

	return TRUE;
}

//---DIB���t�@�C������ǂݍ���
int eiDib::Read(EISTR *name,EISTR *slname,int mode)
{
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	LPBITMAPINFO lpbi = NULL;
	int color = 0,read_mode,FileMode = 0;
	RGBQUAD *rgb;
	EIMEMORY hGlobal = NULL;

	eiFile file(slname);

	Delete();
	Init();

	read_mode = (mode & 0xff00) >> 8;
	mode &= 0xff;

	memset(&bfh,0,sizeof(bfh));

	static eistr temp[_MAX_PATH];
	{
		sprintf(temp,"%s",name);
		char *s = strstr(temp,".acf");

		if(s){
			//---�f�B�t�H���g�̊g���q
			*(s + 1) = 'b';
			*(s + 2) = 'm';
			*(s + 3) = 'p';
			*(s + 4) = 0;
		}
	}

/*	for(int a = 0;a < sizeof(FileName);a ++){
		if(slname != NULL){
			FileName[a] = slname[a];
		} else {
			FileName[a] = name[a];
		}
	}*/

	if(mode == EI_NORMALFILE || mode == EI_LINKEDFILE){
		if(file.Open(temp /*name*/) == 0){
			eiSetLastError(EIER_DIB_CANTOPEN);
			eistr str[_MAX_PATH];
			sprintf(str,"(eiDib::Read) %s:%s ���J���܂���\n",temp,slname);
			eiDebugWriteFile(str);
			return FALSE;
		}
	} else if(mode == EI_RESOURCEFILE){
		//���\�[�X�̏ꍇ
		hGlobal = LoadResource(::eiSystem.hThisInst,
			FindResource(::eiSystem.hThisInst,name, RT_BITMAP));
		if(hGlobal == NULL)
			return FALSE;
		lpbi = (LPBITMAPINFO)LockResource(hGlobal);
	} else if(mode == EI_CLIPBOARD){
		//�N���b�v�{�[�h�̏ꍇ
		if(lpMainWindow != NULL){
			if(!OpenClipboard(lpMainWindow->hwnd)){
//				s_ReadDIBErrors=SDE_NOT_OPENCLIPBOARD;
				return FALSE;
			}
			hGlobal = GetClipboardData(CF_DIB);
			if(hGlobal == NULL){
				CloseClipboard();
				return FALSE;
			}
			lpbi = (LPBITMAPINFO)eiLockMemory(hGlobal);
		}
	}

//BITMAPFILEHEADER��ǂݍ���
	if(!(mode == EI_RESOURCEFILE || mode == EI_CLIPBOARD)){
		file.Read(&bfh,sizeof(BITMAPFILEHEADER),1);
	//�擪���f�a�l�f���ǂ���

		if(mode != EI_LINKEDFILE){
			if(bfh.bfType != 0x4d42){
				file.Close();
				eiSetLastError(EIER_DIB_NOTDIB);
				return FALSE;
			}
		}
	} 
	if(!(mode == EI_RESOURCEFILE || mode == EI_CLIPBOARD))
		file.Read(&bih,sizeof(BITMAPINFOHEADER),1);
	else {
		memcpy(&bih,&lpbi->bmiHeader,sizeof(BITMAPINFOHEADER));
	}

//�Ƃ肠�����c�h�a�����
	if(Create(bih.biWidth , bih.biHeight , bih.biBitCount ,0) == FALSE){
		if(!(mode == EI_RESOURCEFILE || mode == EI_CLIPBOARD)){
			file.Close();
		} else if(mode == EI_RESOURCEFILE){
		    UnlockResource(hGlobal);
			FreeResource(hGlobal);
		} else if(mode == EI_CLIPBOARD){
		    eiUnlockMemory(hGlobal);
			CloseClipboard();
		}
		eiSetLastError(EIER_DIB_CANTCREATE);
		return FALSE;
	}

//�J���[��T��

	if(bih.biBitCount <= 8){//�Q�T�U�F�ȉ��Ȃ�
		if(bih.biClrUsed != 0)
			color = bih.biClrUsed;
		else
			color = 1 << bih.biBitCount;

		if(!(mode == EI_RESOURCEFILE || mode == EI_CLIPBOARD)){
			file.Read(lpRGB , sizeof(RGBQUAD) * color , 1);
		} else {
			memcpy(lpRGB , &lpbi->bmiColors[0] , sizeof(RGBQUAD) * color);
		}
		rgb = lpRGB;
	}

	if(!(mode == EI_RESOURCEFILE || mode == EI_CLIPBOARD)){
		if(mode == EI_LINKEDFILE){
			file.Seek(bfh.bfOffBits);
		} else {
			file.Seek(bfh.bfOffBits);
		}

		if((int)bfh.bfSize - (int)bfh.bfOffBits > 0){
			//---�����Ƃ����w�b�_�[�Ȃ�
			file.Read(lpBitmap , 1 , bfh.bfSize - bfh.bfOffBits);
		} else {
			file.Read(lpBitmap , 1 , LineSize * ySize);
		}
		file.Close();
	} else {
		LPBYTE lpBits;
		lpBits = (LPBYTE)lpbi + lpbi->bmiHeader.biSize + (color * sizeof(RGBQUAD));
		memcpy(lpBitmap,lpBits,BitmapSize);
	}

	memcpy(lpbih,&bih,sizeof(BITMAPINFOHEADER));

	if((mode == EI_RESOURCEFILE || mode == EI_CLIPBOARD)){
		if(mode == EI_RESOURCEFILE){
		    UnlockResource(hGlobal);
			FreeResource(hGlobal);
		} else if(mode == EI_CLIPBOARD){
		    eiUnlockMemory(hGlobal);
			CloseClipboard();
		}
	}

	if(bih.biBitCount < 4){
		//---�Ή��O�̐F����������
		eiSetLastError(EIER_DIB_NOSUPORTCOLOR);
		Delete();
		return FALSE;
	}

	return TRUE;
}

//---�r�b�g�}�b�v��ۑ�
int eiDib::Save(EISTR *name)
{
	FILE *fp;

	fp = fopen(name,"wb");

	BITMAPFILEHEADER bfh;

	memset(&bfh,0,sizeof(BITMAPFILEHEADER));
	bfh.bfType = 0x4d42;
	if(Color <= 8){
		bfh.bfSize=  sizeof(BITMAPFILEHEADER) +
			sizeof(BITMAPINFOHEADER) +
			sizeof(RGBQUAD) * (1 << 8) + BitmapSize;
		bfh.bfOffBits = sizeof(BITMAPFILEHEADER) +
			sizeof(BITMAPINFOHEADER) +
			sizeof(RGBQUAD) * (1 << 8);
	} else {
		bfh.bfSize=  sizeof(BITMAPFILEHEADER) +
			sizeof(BITMAPINFOHEADER) + BitmapSize;
		bfh.bfOffBits = sizeof(BITMAPFILEHEADER) +
			sizeof(BITMAPINFOHEADER);
	}
	
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fp);

	fwrite(lpbih,
		sizeof(BITMAPINFOHEADER),1,fp);

	if(lpbih->biBitCount <= 8){
		//---�p���b�g
		fwrite(lpRGB,
			sizeof(RGBQUAD)*(1 << 8),1,fp);
	}
		
	fwrite(lpBitmap,
		BitmapSize,1,fp);
		
	fclose(fp);

	return 1;
}

//---�c�h�a�̃A�h���X���v�Z����
int eiDib::GetAddres(int x,int y)
{
	int addres;
	
	if(Color >= 8)
		addres = (BitmapSize - ( (y + 1) * LineSize) ) + (x * (Color / 8) );
	else
		addres = (BitmapSize - ( (y + 1) * LineSize) ) + (x / 2);

	if(addres >= BitmapSize || addres < 0){
		addres = 0;
	}

	return addres;	
}

//---�c�h�a����c�h�a�ւ̋�`�R�s�[
int eiDib::Put(eiDib *dib,int dx,int dy,LPRECT lpRect,int efect /*= 0*/)
{
	int x = 0,y = 0,z,bit,
		sx = lpRect->right - lpRect->left,
		sy = lpRect->bottom - lpRect->top;
	int SrcAddres,DstAddres;

	SrcAddres = GetAddres(lpRect->left , lpRect->top + y);
	DstAddres = dib->GetAddres(dx,dy + y);

	if(Color == 8 && dib->Color == 8
		&& !(efect & EI_FORCEDDRAWPIXEL)){
		for(y = 0;y < sy;y ++){
			for(x = 0;x < sx;x += 4){
				*(DWORD *)(dib->lpBitmap + DstAddres + x) =
					*(DWORD *)(lpBitmap + SrcAddres + x);
			}
			SrcAddres = (SrcAddres - LineSize) & 0x00ffffff;
			DstAddres = (DstAddres - dib->LineSize) & 0x00ffffff;
		
			if(DstAddres >= dib->BitmapSize)
				DstAddres = 0;
			if(SrcAddres >= BitmapSize)
				SrcAddres = 0;
		}
	} else if(Color > 8 && Color == dib->Color && !(efect & EI_FORCEDDRAWPIXEL)){
		//---�R�s�[�悪��p���b�g�ŐF���������Ȃ�
		bit = Color / 8;
		for(y = 0;y < sy;y ++){
			SrcAddres = GetAddres(lpRect->left , lpRect->top + y);
			DstAddres = dib->GetAddres(dx,dy + y);

			for(x = 0;x < sx;x ++){
				for(z = 0;z < bit;z ++){
					*(BYTE *)(dib->lpBitmap + DstAddres + (x * bit) + z) =
						*(BYTE *)(lpBitmap + SrcAddres + (x * bit) + z);
				}
			}
		}
	} else if(dib->Color <= 8 && (dib->Color <= Color || Color <= 8)
		&& (efect & EI_COLORMATCH)){
		//---�R�s�[��̐F�����R�s�[����菭�Ȃ��A�p���b�g���g���Ă����
		static int ColorTable[EIDIB_COLORTABLE_SIZE],HashTable[EIDIB_COLORTABLE_SIZE];
		//---�n�b�V�����g���Ă�����Ȃɑ����Ȃ�^^;

		//----�n�b�V���e�[�u���̏�����
		for(x = 0;x < EIDIB_COLORTABLE_SIZE;x ++){
			HashTable[x] = -1;
		}
		memset(&ColorTable[0],0,sizeof(ColorTable));

		for(y = 0;y < sy;y ++){
				for(x = 0;x < sx;x ++){
					z = GetPixel(x + lpRect->left,y + lpRect->top);
					if(HashTable[z % EIDIB_COLORTABLE_SIZE] == z){
						//---�n�b�V���e�[�u���ɑ��݂��Ă����
						z = ColorTable[z % EIDIB_COLORTABLE_SIZE];
					} else {
						if(Color > 8){
							//---�R�s�[������p���b�g�Ȃ�
							z = ColorTable[z % EIDIB_COLORTABLE_SIZE]
								= dib->SeekNearColor(z & 0xff,(z >> 8) & 0xff,(z >> 16) & 0xff);
						} else {
							z = ColorTable[z % EIDIB_COLORTABLE_SIZE]
								= dib->SeekNearColor(
								GetPaletteRed(z),
								GetPaletteGreen(z),
								GetPaletteBlue(z));
						}
						HashTable[z % EIDIB_COLORTABLE_SIZE] = z;
					}
					dib->DrawPixel(x + dx,y + dy,z);
				}
		}
	} else {
		for(y = 0;y < sy;y ++){
			if(Color <= 8 && dib->Color > 8){
				//---�p���b�g���g���ăR�s�[�悪��p���b�g�Ȃ�
				for(x = 0;x < sx;x ++){
					z = GetPixel(x + lpRect->left,y + lpRect->top);
					dib->DrawPixel(x + dx,y + dy,
						ToRGB(z,dib->Color));
				}
			} else {
				for(x = 0;x < sx;x ++){
					dib->DrawPixel(x + dx,y + dy,GetPixel(x + lpRect->left,y + lpRect->top));
				}
			}
		}
	}

	return 1;
}

//---�c�h�a����c�h�a�ւ̓����F���܂ދ�`�R�s�[
int eiDib::PutTrans(eiDib *dib,int dx,int dy,LPRECT lpRect,int efect /*= 0*/)
{
	int x = 0,y = 0,z,
		sx = lpRect->right - lpRect->left,
		sy = lpRect->bottom - lpRect->top;
	int SrcAddres,DstAddres;
	BYTE s;

	SrcAddres = GetAddres(lpRect->left , lpRect->top + y);
	DstAddres = dib->GetAddres(dx,dy+y);

	if(Color == 8){
		//---256�F
		for(y = 0;y < sy;y ++){
//			SrcAddres = GetAddres(lpRect->left , lpRect->top + y);
//			DstAddres = dib->GetAddres(dx,dy + y);

			for(x = 0;x < sx;x ++){
				s = *(BYTE *)(lpBitmap + SrcAddres + x);
				if(s != TransColor)
					*(BYTE *)(dib->lpBitmap + DstAddres + x) = s;
			}
		
			SrcAddres = (SrcAddres - LineSize) & 0x00ffffff;
			DstAddres = (DstAddres - dib->LineSize) & 0x00ffffff;
		
			if(DstAddres >= dib->BitmapSize)
				DstAddres = 0;
			if(SrcAddres >= BitmapSize)
				SrcAddres = 0;
		}
	} else if(Color == dib->Color){
		//---���̑��̐F���Ȃ�
		for(y = 0;y < sy;y ++){
			for(x = 0;x < sx;x ++){
				z = GetPixel(x,y);
				if(z != TransColor)
					dib->DrawPixel(x,y,z);
			}
		}
	} else {
		//---�F�����Ⴆ��
		return Put(dib,dx,dy,lpRect,efect);
	}

	return 1;
}

#ifdef EIUSE_DIRECTDRAW
//---�T�[�t�F�C�X�ɓ]��
int eiDib::CopyToDDSurface(eiDDSurface *esDst,int x,int y,LPRECT lpRect,int trans /*= 1*/)
{
	int a,sx,sy,tx,ty,pitch,addres,dds_addres;
	int xStart,yStart,xEnd,yEnd;
	LPBYTE dds;

	//---�����R�s�[�͈͂��Ȃ���΁A�S���R�s�[
	if(lpRect == NULL){
		xStart = 0;
		yStart = 0;
		xEnd   = xSize;
		yEnd   = ySize;
	} else {
		xStart = lpRect->left;
		yStart = lpRect->top;
		xEnd   = lpRect->right;
		yEnd   = lpRect->bottom;
	}

	//---���W�ϊ�
	eiChangePoint(&x,&y);
	eiChangePoint(&xStart,&yStart);
	eiChangePoint(&xEnd,&yEnd);

	if(esDst->Color == Color){
		//�f�B�X�v���C�̐F���ƁA�c�h�a�̐F�����ꏏ�Ȃ�
		a = esDst->Lock(&dds,&pitch);
		if(a == TRUE && ::eiSystem.ScreenZoomRate == 0){
			for(sy = yStart ,ty = 0; sy < yEnd ; sy ++ , ty++){
				addres = GetAddres(xStart,sy);
				dds_addres = (y + ty) * pitch + x;
				for(sx = xStart ,tx = 0; sx < (xEnd);
					sx += 4 , tx +=4 ,addres += 4 , dds_addres +=4){
					
					*(DWORD *)(dds + dds_addres) =
					*(DWORD *)(lpBitmap + addres);
				}
				if(ty + 1 >= esDst->ySize){
					//�T�[�t�F�C�X�����r�x���傫��������
					break;
				}
			}
			esDst->UnLock();
		} else if(a == TRUE){
			for(sy = yStart ,ty = 0; sy < yEnd ; sy ++ , ty ++){
				addres = GetAddres(xStart,sy << ::eiSystem.ScreenZoomRate);
				dds_addres = (y + ty) * pitch + x;
				for(sx = xStart ,tx = 0; sx < (xEnd);
					sx ++ , tx ++ ,addres += (1 << ::eiSystem.ScreenZoomRate) , dds_addres += 1){
					
					*(BYTE *)(dds + dds_addres) =
					*(BYTE *)(lpBitmap + addres);
				}
				if(ty + 1 >= esDst->ySize){
					//�T�[�t�F�C�X�����r�x���傫��������
					break;
				}
			}

			esDst->UnLock();
		}
	} else if(Color == 8){
		//--- 256-> HighColor,TrueColor
		if(esDst->Lock(&dds,&pitch) == TRUE){
			DWORD wd = 0;
			BYTE bt = 0;
			for(sy = yStart ,ty = 0; sy < yEnd ; sy ++ , ty++){
				addres = GetAddres(xStart,sy);
				dds_addres = (y + ty) * pitch + (x * (esDst->Color / 8));
				for(sx = xStart ,tx = 0; sx < (xEnd);
					sx += 1 , tx += 1 ,addres += 1 , dds_addres += (esDst->Color / 8)){
					
					bt = *(BYTE *)(lpBitmap + addres);
					if(bt == ::eiSystem.TransColor && trans){
						//---�����F�Ȃ�
						wd = 0x0001;
					} else {
						if(esDst->Color == 16){
							wd = //---red
							  ( (((WORD)lpRGB[bt].rgbRed >> (8 - esDst->RedBit)) )
							  << (esDst->RedShift))
							//---green
							| ( (((WORD)lpRGB[bt].rgbGreen >> (8 - esDst->GreenBit)) )
							<< (esDst->GreenShift))
							//---blue
							| ( (((WORD)lpRGB[bt].rgbBlue >> (8 - esDst->BlueBit)) )
							<< (esDst->BlueShift));
						} else {
							wd = //---red
							  ( ((DWORD)lpRGB[bt].rgbRed ) << (esDst->RedShift))
							//---green
							| ( ((DWORD)lpRGB[bt].rgbGreen ) << (esDst->GreenShift))
							//---blue
							| ( ((DWORD)lpRGB[bt].rgbBlue ) << (esDst->BlueShift));
						}
					}
					if(esDst->Color == 16){
						*(WORD *)(dds + dds_addres) = (WORD)wd;
					} else if(esDst->Color == 32){
						*(DWORD *)(dds + dds_addres) = (DWORD)wd;
					} else if(esDst->Color == 24){
						if(wd == 0x0001){
							*(BYTE *)(dds + dds_addres) = 0x01;
							*(BYTE *)(dds + dds_addres + 1) = 0x00;
							*(BYTE *)(dds + dds_addres + 2) = 0x00;
						} else {
							*(BYTE *)(dds + dds_addres) = (BYTE)lpRGB[bt].rgbBlue;
							*(BYTE *)(dds + dds_addres + 1) = (BYTE)lpRGB[bt].rgbGreen;
							*(BYTE *)(dds + dds_addres + 2) = (BYTE)lpRGB[bt].rgbRed;
						}
					}
				}
				if(ty + 1 >= esDst->ySize){
					//�T�[�t�F�C�X�����r�x���傫��������
					break;
				}
			}
			esDst->UnLock();
		}
	} else {
		//--- True -> HighColor,TrueColor
		if(esDst->Lock(&dds,&pitch) == TRUE){
			DWORD wd = 0;
			BYTE red,green,blue;
			for(sy = yStart ,ty = 0; sy < yEnd ; sy ++ , ty++){
				addres = GetAddres(xStart,sy);
				dds_addres = (y + ty) * pitch + (x * (esDst->Color / 8));
				for(sx = xStart ,tx = 0; sx < (xEnd);
					sx += 1 , tx += 1 ,addres += 3 , dds_addres += (esDst->Color / 8)){

					addres = GetAddres(sx,sy);
					
					red = *(BYTE *)(lpBitmap + addres + 2);
					green = *(BYTE *)(lpBitmap + addres + 1);
					blue = *(BYTE *)(lpBitmap + addres + 0);

					if(0){
						//---�����F�Ȃ�
						wd = 0x0001;
					} else {
						if(esDst->Color == 16){
							wd = //---red
							  ( (((WORD)red >> (8 - esDst->RedBit)) )
							  << (esDst->RedShift))
							//---green
							| ( (((WORD)green >> (8 - esDst->GreenBit)) )
							<< (esDst->GreenShift))
							//---blue
							| ( (((WORD)blue >> (8 - esDst->BlueBit)) )
							<< (esDst->BlueShift));
						} else if(esDst->Color == 32){
							wd = //---red
							  ( (((WORD)red) )
							  << (esDst->RedShift))
							//---green
							| ( (((WORD)green) )
							<< (esDst->GreenShift))
							//---blue
							| ( (((WORD)blue) )
							<< (esDst->BlueShift));
						}
					}
					if(esDst->Color == 16){
						*(WORD *)(dds + dds_addres) = (WORD)wd;
					} else if(esDst->Color == 32){
						*(DWORD *)(dds + dds_addres) = (DWORD)wd;
					} else if(esDst->Color == 24){
						*(BYTE *)(dds + dds_addres) = blue;
						*(BYTE *)(dds + dds_addres + 1) = green;
						*(BYTE *)(dds + dds_addres + 2) = red;
					}
				}
				if(ty + 1 >= esDst->ySize){
					//�T�[�t�F�C�X�����r�x���傫��������
					break;
				}
			}
			esDst->UnLock();
		}
	}
	return TRUE;
}

//---�T�[�t�F�C�X����eiDib�֓]��
//---�܂��s���S
int eiDib::CopyDDSurfaceTo(eiDDSurface *esDst,int x,int y,LPRECT lpRect)
{
	int sx,sy,Pitch,addres,dds_addres,count;
	LPBYTE lpMemory;
	RECT SurfaceRect;

	if(lpRect == NULL){
		lpRect = &SurfaceRect;
		lpRect->left = lpRect->top = 0;
		lpRect->right = esDst->xSize;
		lpRect->bottom = esDst->ySize;
	}

	//---���W�ϊ�
	eiChangeRect(lpRect);

	if(esDst->Lock(&lpMemory,&Pitch) == TRUE){
		for(sy = 0 ; sy < lpRect->bottom - lpRect->top ; sy ++){
			addres = GetAddres(x,y + sy);
			dds_addres = (lpRect->top + sy) * Pitch + lpRect->left;
			count = (lpRect->right - lpRect->left);
			count = 1;//*=(ColorMode / 8);
			
			for(sx = 0 ; sx < count ;
				sx += 4 , addres += 4 , dds_addres += 4){
				
				*(DWORD *)(lpBitmap + addres)=
				*(DWORD *)(lpMemory + dds_addres);
			}
			if(sy+1 >= ySize){
				//�T�[�t�F�C�X�����r�x���傫��������
				break;
			}
			if(sy+1 >= ySize){
				//dib���r�x���傫��������
				break;
			}
		}
		esDst->UnLock();
	}
	return TRUE;
}
#endif

//---�c�h�a���c�b�ɃR�s�[
int eiDib::CopyToDC(HDC hdc,int x,int y,
						   double rx /*= 1.000*/,double ry /*= 1.000*/,
						   LPRECT lpRect /*= NULL*/)
{
	if(lpRect){
		StretchDIBits(hdc,x,y,
			(int)((double)lpRect->right * rx),
			(int)((double)lpRect->bottom * ry),
			0,0,
			lpbih->biWidth,lpbih->biHeight,
			lpBitmap,lpBitmapInfo,
			DIB_RGB_COLORS,
			SRCCOPY);
	} else {
		StretchDIBits(hdc,x,y,
			(int)((double)lpbih->biWidth * rx),
			(int)((double)lpbih->biHeight * ry),
			0,0,
			lpbih->biWidth,lpbih->biHeight,
			lpBitmap,lpBitmapInfo,
			DIB_RGB_COLORS,
			SRCCOPY);
	}

	return 1;
}

//---�c�h�a�ɓ_��ł�
int eiDib::DrawPixel(int x,int y,int col,int efect)
{
	int addres;

	addres = GetAddres(x,y);
	//�|�C���^�[���c�h�a�̊O�ɂ���Ȃ�߂�
/*	if(addres >= BitmapSize || addres < 0){
		return FALSE;
	}*/
	if(x < 0 || xSize <= x
		|| y < 0 || ySize <= y)
		return FALSE;

	if(Color == 8){
		*(BYTE *)(lpBitmap + addres) = (BYTE)col;
	} else if(Color == 4){
		if(x % 2 == 0){
			*(BYTE *)(lpBitmap + addres) = (ei_u8)(
				(*(BYTE *)(lpBitmap + addres) & 0x0f) | (BYTE)(col << 4));
		} else {
			*(BYTE *)(lpBitmap + addres) = (ei_u8)(
				(*(BYTE *)(lpBitmap + addres) & 0xf0) | (BYTE)(col));
		}
	} else if(Color == 16){
		*(WORD *)(lpBitmap + addres) = (WORD)col;
	} else if(Color == 24){
		*(BYTE *)(lpBitmap + addres + 0) = (BYTE)((col >> 16) & 0x0000ff);
		*(BYTE *)(lpBitmap + addres + 1) = (BYTE)((col >> 8) & 0x0000ff);
		*(BYTE *)(lpBitmap + addres + 2) = (BYTE)((col) & 0x0000ff);
	}

	return TRUE;
}

//---�c�h�a�̓_��ǂ�
int eiDib::GetPixel(int x,int y,int efect)
{
	int addres,col = 0;

	addres = GetAddres(x,y);
	//�|�C���^�[���c�h�a�̊O�ɂ���Ȃ�߂�
	if(addres >= BitmapSize || addres < 0){
		return 0;
	}

	if(Color == 8){
		col = *(BYTE *)(lpBitmap + addres);
	} else if(Color == 4){
		if(x % 2 == 0){
			col = (*(BYTE *)(lpBitmap + addres) & 0xf0) >> 4;
		} else {
			col = (*(BYTE *)(lpBitmap + addres) & 0x0f);
		}
	} else if(Color == 16){
		col = *(WORD *)(lpBitmap + addres);
	} else if(Color == 24){
		col = 0;
		col |= ( ( (*(BYTE *)(lpBitmap + addres + 0)) << 16) & 0xff0000);
		col |= ( ( (*(BYTE *)(lpBitmap + addres + 1)) <<  8) & 0xff00);
		col |= ( ( (*(BYTE *)(lpBitmap + addres + 2))      ) & 0xff);
	}

	return col;
}

//---�c�h�a�ɐ���`��
void eiDib::DrawLineNextY(int xp,int yp,int dx,int dy,int dirVector,
					   int color,int mode)
{
	int k1,k2,errorTerm;
	int wc = color;

	k1 = dy << 2;
	k2 = k1 -(int)(dx << 2);
	errorTerm = k1 - (int)dx;

	DrawPixel(xp,yp,wc);
	while(dx--){
		if(errorTerm >= 0){
			yp++;
			errorTerm += k2;
		} else {
			errorTerm += k1;
		}
		xp += dirVector;

		DrawPixel(xp,yp,wc);
	}
}

void eiDib::DrawLineNextX(int xp,int yp,int dx,int dy,int dirVector,
					   int color,int mode)
{
	int k1,k2,errorTerm;
	int wc = color;

	k1 = dx << 2;
	k2 = k1 -(int)(dy << 2);
	errorTerm = k1 - (int)dy;

	DrawPixel(xp,yp,wc);
	while(dy--){
		if(errorTerm >= 0){
			xp+= dirVector;
			errorTerm += k2;
		} else {
			errorTerm += k1;
		}
		yp ++;
		DrawPixel(xp,yp,wc);
	}
}

//---���C����`��
void eiDib::DrawLine(int x1,int y1,int x2,int y2,
			   int col,int mode)
{
	int dx,dy,step;

	if(y1 > y2){
		eiSwap(&y1,&y2);
		eiSwap(&x1,&x2);
	}

	dx = x2 - x1;
	dy = y2 - y1;
	if(dx > 0){
		step = 1;
	} else {
		dx = -dx;
		step = -1;
	}
	if(dx > dy){
		DrawLineNextY(x1,y1,dx,dy,step,col,mode);
	} else {
		DrawLineNextX(x1,y1,dx,dy,step,col,mode);
	}
}

//---����`��
void eiDib::DrawBox(int x1,int y1,int x2,int y2,
			  int col,int mode)
{
	if(x1 > x2)
		eiSwap(&x1,&x2);
	if(y1 > y2)
		eiSwap(&y1,&y2);
	DrawLine(x1,y1,x2,y1,col,mode);
	DrawLine(x1,y2,x2,y2,col,mode);
	DrawLine(x1,y1,x1,y2,col,mode);
	DrawLine(x2,y1,x2,y2,col,mode);
}

//---����`���h��Ԃ�
void eiDib::DrawFillBox(int x1,int y1,int x2,int y2,
			   int col,int mode)
{
	int x,y,dx,addres,sx2;
	DWORD dw = (col << 24) | (col << 16) | (col << 8) | col;

	if(x1 > x2)
		eiSwap(&x1,&x2);
	if(y1 > y2)
		eiSwap(&y1,&y2);
	sx2 = x2;
	if(sx2 != 0){
		sx2 = sx2-(sx2 % 4);
	}
	dx = x2-x1;
	if(dx >= 4 && Color == 8){
		for(y = y1;y <= y2;y ++){
			addres = GetAddres(x1,y);
			for(x = x1;x < sx2;x += 4,addres += 4){
				if(addres >= BitmapSize || addres < 0)
					continue;
				*(DWORD *)(lpBitmap + addres) = (DWORD)dw;
			}
			for(;x <= x2;x ++,addres ++){
				if(addres >= BitmapSize || addres < 0)
					continue;
				*(BYTE *)(lpBitmap + addres) = (BYTE)col;
			}
		}
	} if(Color == 24){
		int red = (col >> 16) & 0xff,
			green = (col >> 8) & 0xff,
			blue = (col >> 0) & 0xff;

		for(y = y1;y <= y2;y ++){
			addres = GetAddres(x1,y);
			for(x = x1;x <= x2;x ++,addres += 3){
//				DrawPixel(x,y,col);
				*(BYTE *)(lpBitmap + addres) = (BYTE)red;
				*(BYTE *)(lpBitmap + addres + 1) = (BYTE)green;
				*(BYTE *)(lpBitmap + addres + 2) = (BYTE)blue;
			}
		}
	} else {
		for(y = y1;y <= y2;y ++){
			for(x = x1;x <= x2;x ++){
				DrawPixel(x,y,col);
			}
		}
	}
	mode++;
}

//---�����`��
int eiDib::DibText(EISTR *String,int x,int y,int color,int efect)
{
	DrawTextMemory((lpBitmap + GetAddres(x,y)),-1,1,LineSize,
		String,x,y,color,efect);
	return 1;
}

//---�c�h�a�p���b�g
int eiDib::ToRGB(int num,int bit /*= 0*/)
{
	int rgb = 0;

	if(bit == 0)
		bit = Color;

	if(Color > 8 && Color == bit)
		return num;

	if(bit == 24){
		rgb = MakeRGB(lpRGB[num].rgbRed,lpRGB[num].rgbGreen,lpRGB[num].rgbBlue,bit);
/*		rgb = ((lpRGB[num].rgbRed) & 0x000000ff)
			| ((lpRGB[num].rgbGreen << 8) & 0x0000ff00)
			| ((lpRGB[num].rgbBlue << 16) & 0x00ff0000);*/
	}

	return rgb;
}

//---�q�f�a�����
int eiDib::MakeRGB(int red,int green,int blue,int bit /* = 0*/)
{
	int rgb = 0;

	if(bit == 0)
		bit = Color;

	if(bit == 24){
		rgb = ((red) & 0x000000ff)
			| ((green << 8) & 0x0000ff00)
			| ((blue << 16) & 0x00ff0000);
	}

	return rgb;
}

//---�ł��߂��F��T��
int eiDib::SeekNearColor(int red,int green,int blue)
{
	int distance = (1 << 16) * 3,num,c,palette = 0;

	if(Color > 8){
		//---��p���b�g�Ȃ炻�̂܂܂q�f�a�ɂ��ĕԂ�
		return MakeRGB(red,green,blue);
	}

	for(num = 0;num < (1 << Color);num ++){
		c =   (red - GetPaletteRed(num)) * (red - GetPaletteRed(num))
			+ (green - GetPaletteGreen(num)) * (green - GetPaletteGreen(num))
			+ (blue- GetPaletteBlue(num)) * (blue - GetPaletteBlue(num));
		if(c < distance){
			//---�e�F�v�f�̍��̍��v���ł��������F��I��
			distance = c;
			palette = num;
		}
	}

	return palette;
}

//---�p���b�g�Z�b�g
int eiDib::SetPalette(int num,int red,int green,int blue)
{
	lpRGB[num].rgbRed = (ei_u8)red;
	lpRGB[num].rgbGreen = (ei_u8)green;
	lpRGB[num].rgbBlue = (ei_u8)blue;

	return 1;
}

int eiDib::GetPaletteRed(int num)
{
	if(Color <= 8)
		return lpRGB[num].rgbRed;

	return ((num >> 0) & 0xff);
}

int eiDib::GetPaletteGreen(int num)
{
	if(Color <= 8)
		return lpRGB[num].rgbGreen;

	return ((num >> 8) & 0xff);
}

int eiDib::GetPaletteBlue(int num)
{
	if(Color <= 8)
		return lpRGB[num].rgbBlue;

	return ((num >> 16) & 0xff);
}

//---�c�h�a�p���b�g���R�s�[
int eiDib::CopyPalette(eiDib *lpDib)
{
	if(Color <= 8 && lpDib->Color <= 8){
		memcpy(lpDib->lpRGB,lpRGB,sizeof(RGBQUAD) * (1 << Color));
		return 1;
	}
	return 0;
}
