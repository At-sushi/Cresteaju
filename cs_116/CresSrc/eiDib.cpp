/*-----------------------------------------------------------

   eiLibray
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   eiDib.cpp ...eiDib Class

-----------------------------------------------------------*/

//---------------------------
//	eiDib
//	ビットマップを扱うクラス
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

//ＤＩＢを作成する
int eiDib::Create(int hx,int hy,int color,int mode)
{
	int a,size;
	EIMEMORY hg;

	if(color <= 8){
		//---パレット含む
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
		//---パレット
		lpRGB = (LPRGBQUAD)(((BYTE *)(lpBitmapInfo)) + sizeof(BITMAPINFOHEADER));
		RGBQUAD *rgb = lpRGB;

		memset(lpRGB,0,sizeof(RGBQUAD) * (1 << color));
		for(a = 0;a < (1 << color);a ++){
			rgb->rgbBlue = rgb->rgbGreen = rgb->rgbRed = 0;	
			rgb->rgbReserved = 0;
			rgb ++;
		}
		rgb--;
		//---インデックスの最後を白にする
		if((mode & EIDIB_DIBSECTION)){
			rgb->rgbBlue = rgb->rgbGreen = rgb->rgbRed = 255;	
		}
	} else {
		lpRGB = (LPRGBQUAD)((BYTE *)(lpBitmapInfo)); 
	}

	Color = color;

	//ビットマップメモリを確保
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
		//---通常DIB
		hg = eiAllocMemory(size);//GlobalAlloc(GMEM_MOVEABLE,size);
		lpBitmap = (BYTE *)eiLockMemory(hg);//GlobalLock(hg);
		if(hg == NULL){
			Delete();
			return FALSE;
		}
		hgBitmap = hg;
		hBitmap = NULL;
	} else {
		//---DIBセクション作成
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

	//---ＤＩＢをクリア
	memset(lpBitmap,0,size);
	BitmapSize = size;
#ifdef YOBUN
	memset( ((BYTE *)lpBitmap) + size - 1024,0xff,1024);
	BitmapSize = size - 1024;
#endif
	//１ラインのバイト数
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

//---DIBをファイルから読み込む
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
			//---ディフォルトの拡張子
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
			sprintf(str,"(eiDib::Read) %s:%s が開けません\n",temp,slname);
			eiDebugWriteFile(str);
			return FALSE;
		}
	} else if(mode == EI_RESOURCEFILE){
		//リソースの場合
		hGlobal = LoadResource(::eiSystem.hThisInst,
			FindResource(::eiSystem.hThisInst,name, RT_BITMAP));
		if(hGlobal == NULL)
			return FALSE;
		lpbi = (LPBITMAPINFO)LockResource(hGlobal);
	} else if(mode == EI_CLIPBOARD){
		//クリップボードの場合
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

//BITMAPFILEHEADERを読み込む
	if(!(mode == EI_RESOURCEFILE || mode == EI_CLIPBOARD)){
		file.Read(&bfh,sizeof(BITMAPFILEHEADER),1);
	//先頭が’ＢＭ’かどうか

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

//とりあえずＤＩＢを作る
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

//カラーを探す

	if(bih.biBitCount <= 8){//２５６色以下なら
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
			//---ちゃんとしたヘッダーなら
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
		//---対応外の色数だったら
		eiSetLastError(EIER_DIB_NOSUPORTCOLOR);
		Delete();
		return FALSE;
	}

	return TRUE;
}

//---ビットマップを保存
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
		//---パレット
		fwrite(lpRGB,
			sizeof(RGBQUAD)*(1 << 8),1,fp);
	}
		
	fwrite(lpBitmap,
		BitmapSize,1,fp);
		
	fclose(fp);

	return 1;
}

//---ＤＩＢのアドレスを計算する
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

//---ＤＩＢからＤＩＢへの矩形コピー
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
		//---コピー先が非パレットで色数が同じなら
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
		//---コピー先の色数がコピー元より少なく、パレットを使っていれば
		static int ColorTable[EIDIB_COLORTABLE_SIZE],HashTable[EIDIB_COLORTABLE_SIZE];
		//---ハッシュを使ってもそんなに速くない^^;

		//----ハッシュテーブルの初期化
		for(x = 0;x < EIDIB_COLORTABLE_SIZE;x ++){
			HashTable[x] = -1;
		}
		memset(&ColorTable[0],0,sizeof(ColorTable));

		for(y = 0;y < sy;y ++){
				for(x = 0;x < sx;x ++){
					z = GetPixel(x + lpRect->left,y + lpRect->top);
					if(HashTable[z % EIDIB_COLORTABLE_SIZE] == z){
						//---ハッシュテーブルに存在していれば
						z = ColorTable[z % EIDIB_COLORTABLE_SIZE];
					} else {
						if(Color > 8){
							//---コピー元が非パレットなら
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
				//---パレットを使ってコピー先が非パレットなら
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

//---ＤＩＢからＤＩＢへの透明色を含む矩形コピー
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
		//---256色
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
		//---その他の色数なら
		for(y = 0;y < sy;y ++){
			for(x = 0;x < sx;x ++){
				z = GetPixel(x,y);
				if(z != TransColor)
					dib->DrawPixel(x,y,z);
			}
		}
	} else {
		//---色数が違えば
		return Put(dib,dx,dy,lpRect,efect);
	}

	return 1;
}

#ifdef EIUSE_DIRECTDRAW
//---サーフェイスに転送
int eiDib::CopyToDDSurface(eiDDSurface *esDst,int x,int y,LPRECT lpRect,int trans /*= 1*/)
{
	int a,sx,sy,tx,ty,pitch,addres,dds_addres;
	int xStart,yStart,xEnd,yEnd;
	LPBYTE dds;

	//---もしコピー範囲がなければ、全部コピー
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

	//---座標変換
	eiChangePoint(&x,&y);
	eiChangePoint(&xStart,&yStart);
	eiChangePoint(&xEnd,&yEnd);

	if(esDst->Color == Color){
		//ディスプレイの色数と、ＤＩＢの色数が一緒なら
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
					//サーフェイスよりもＳＹが大きかったら
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
					//サーフェイスよりもＳＹが大きかったら
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
						//---透明色なら
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
					//サーフェイスよりもＳＹが大きかったら
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
						//---透明色なら
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
					//サーフェイスよりもＳＹが大きかったら
					break;
				}
			}
			esDst->UnLock();
		}
	}
	return TRUE;
}

//---サーフェイスからeiDibへ転送
//---まだ不完全
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

	//---座標変換
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
				//サーフェイスよりもＳＹが大きかったら
				break;
			}
			if(sy+1 >= ySize){
				//dibもＳＹが大きかったら
				break;
			}
		}
		esDst->UnLock();
	}
	return TRUE;
}
#endif

//---ＤＩＢをＤＣにコピー
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

//---ＤＩＢに点を打つ
int eiDib::DrawPixel(int x,int y,int col,int efect)
{
	int addres;

	addres = GetAddres(x,y);
	//ポインターがＤＩＢの外にあるなら戻る
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

//---ＤＩＢの点を読む
int eiDib::GetPixel(int x,int y,int efect)
{
	int addres,col = 0;

	addres = GetAddres(x,y);
	//ポインターがＤＩＢの外にあるなら戻る
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

//---ＤＩＢに線を描く
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

//---ラインを描く
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

//---箱を描く
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

//---箱を描き塗りつぶす
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

//---文字描画
int eiDib::DibText(EISTR *String,int x,int y,int color,int efect)
{
	DrawTextMemory((lpBitmap + GetAddres(x,y)),-1,1,LineSize,
		String,x,y,color,efect);
	return 1;
}

//---ＤＩＢパレット
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

//---ＲＧＢを作る
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

//---最も近い色を探す
int eiDib::SeekNearColor(int red,int green,int blue)
{
	int distance = (1 << 16) * 3,num,c,palette = 0;

	if(Color > 8){
		//---非パレットならそのままＲＧＢにして返す
		return MakeRGB(red,green,blue);
	}

	for(num = 0;num < (1 << Color);num ++){
		c =   (red - GetPaletteRed(num)) * (red - GetPaletteRed(num))
			+ (green - GetPaletteGreen(num)) * (green - GetPaletteGreen(num))
			+ (blue- GetPaletteBlue(num)) * (blue - GetPaletteBlue(num));
		if(c < distance){
			//---各色要素の差の合計が最も小さい色を選ぶ
			distance = c;
			palette = num;
		}
	}

	return palette;
}

//---パレットセット
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

//---ＤＩＢパレットをコピー
int eiDib::CopyPalette(eiDib *lpDib)
{
	if(Color <= 8 && lpDib->Color <= 8){
		memcpy(lpDib->lpRGB,lpRGB,sizeof(RGBQUAD) * (1 << Color));
		return 1;
	}
	return 0;
}
