/*-----------------------------------------------------------

   eiLibray
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   eiCell.cpp ...eiCell Class

-----------------------------------------------------------*/

//---------------------------
//	eiCell
//	DirectDrawやDIBを同等のものとして扱うクラス
//---------------------------


eiCell::eiCell(void)
{
	//---変数を初期化
//	memset(&Data,0,sizeof(Data));
	eimemset(&Data,0,sizeof(Data));
//	dib.Init();

#ifdef EIUSE_DIRECTDRAW
	pDDSurface = NULL;
#endif
}

eiCell::~eiCell()
{
//	dib.Delete();
}

//---作成
int eiCell::Create(int sx,int sy,int color/* = 8*/,int dib_mode)
{
	//---古いのを削除
	if(dib_mode == 0){
		dib.Delete();

		dib.Init();

		if(!dib.Create(sx,sy,color,0)){
			return 0;
		}
	}

	Data.CreateFlag = 1;
	Data.xSize = sx;
	Data.ySize = sy;
	Data.Color = color;

	//---クリッピング範囲
	Data.rectClip.left = Data.rectClip.top = 0;
	Data.rectClip.right = sx;
	Data.rectClip.bottom = sy;

	return 1;
}

int eiCell::Release(void)
{
	return Delete();
}

//---削除
int eiCell::Delete(void)
{
	dib.Delete();
	dib.Init();
	Data.CreateFlag = 0;

	//---変数を初期化
//	memset(&Data,0,sizeof(Data));
	eimemset(&Data,0,sizeof(Data));

	return 1;
}

void eiCell::SetClipingRect(LPRECT rect)
{
	//---クリッピング範囲
	memcpy(&Data.rectClip,rect,sizeof(RECT));
}


//-------------------------------------------------------------
#ifdef EI_RUNWINDOWS
#ifdef EIUSE_DIRECTDRAW

//---サーフェイスに転送
void eiCell::SetSurface(LPRECT lpRect /*= NULL*/,int plane /* = 2 */,int trans /*= 1*/)
{
	if(!Data.CreateFlag)
		return;
//	if(plane < 2)
//		return;

	if(lpRect == NULL){
		plane = Data.SurfaceNumber;
	}
	//---DirectDrawを使ってなければもどる
	if(!(::eiSystem.ScreenMode & DIRECTDRAW_MODE))
		return;
	//---サーフェイスがあるかどうかチェック
	if(eiSurface[plane].lpSurface == NULL){
		return;
	}
//plane = 0;
	//---転送
	if(lpRect != NULL){
		//---再セットでなければ
		memcpy(&Data.rectSurface,lpRect,sizeof(RECT));
	}
	dib.CopyToDDSurface(&eiSurface[plane],Data.rectSurface.left,Data.rectSurface.top,NULL,trans);

	Data.SurfaceFlag = 1;
	Data.SurfaceNumber = plane;

#ifdef EIUSE_DIRECTDRAW
	pDDSurface = &eiSurface[plane];
#endif
}

#endif
#endif
//-------------------------------------------------------------

int eiCell::ReadDIB(EISTR *name,EISTR *slname,int mode)
{
	return ReadFile(name,slname,mode);
}

//---ファイルから読み込み
int eiCell::ReadFile(EISTR *name,EISTR *slname,int mode)
{
	int sx,sy;

	Delete();

	if(dib.Read(name,slname,mode) == FALSE){
		return 0;
	}

	sx = dib.xSize;
	sy = dib.ySize;
		
	Create(sx,sy,dib.Color,1);

	return 1;
}

//-----------------------------------------------------------
//転送関数は、サーフェイス－＞DIBの転送をサポートしていない
//-----------------------------------------------------------

//---高速矩形転送
int eiCell::Put(eiCell *cell,int x,int y)
{
	if(Data.SurfaceFlag && cell->Data.SurfaceFlag){
		//---両方がサーフェイス上にあれば
#ifdef EIUSE_DIRECTDRAW
		pDDSurface->Put(
			cell->pDDSurface,
			x + cell->Data.rectSurface.left,
			y + cell->Data.rectSurface.top,
			&Data.rectSurface,
			DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
	} else if(cell->Data.SurfaceFlag){
		//---転送先がサーフェイスにあれば
		dib.CopyToDDSurface(
			cell->pDDSurface,
			x + cell->Data.rectSurface.left,
			y + cell->Data.rectSurface.top);
#endif
	} else {
		//---どちらもＤＩＢならば
		RECT rect;
		rect.left = 0;
		rect.top = 0;
		rect.right = dib.xSize;
		rect.bottom = dib.ySize;

		dib.Put(&cell->dib,
			x,y,&rect);
	}

	return EI_NOERR;
}

//---クリッピング処理をして転送
int eiCell::PutClip(eiCell *cell,int x,int y,LPRECT lpSrc,int efect /*= 0*/)
{
	int sx,sy;
	RECT rect;

	//---クリッピング計算
	if(!lpSrc){
		if(!eiGetClipingRect(&rect,&Data.rectClip,&cell->Data.rectClip,x,y)){
			return EI_NOERR;
		}
	} else {
		if(!eiGetClipingRect(&rect,lpSrc,&cell->Data.rectClip,x,y)){
			return EI_NOERR;
		}
	}

	sx = rect.left;
	sy = rect.top;
	if(lpSrc){
		sx -= lpSrc->left;
		sy -= lpSrc->top;
	}
	if(Data.SurfaceFlag && cell->Data.SurfaceFlag){
		//---両方がサーフェイス上にあれば
#ifdef EIUSE_DIRECTDRAW
		rect.left   += Data.rectSurface.left;
		rect.right  += Data.rectSurface.left;
		rect.top    += Data.rectSurface.top;
		rect.bottom += Data.rectSurface.top;

		pDDSurface->Put(
			cell->pDDSurface,
			x + cell->Data.rectSurface.left + sx,
			y + cell->Data.rectSurface.top + sy,
			&rect,
			DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
	} else if(cell->Data.SurfaceFlag){
		//---転送先がサーフェイスにあれば
		dib.CopyToDDSurface(
			cell->pDDSurface,
			x + cell->Data.rectSurface.left + sx,
			y + cell->Data.rectSurface.top + sy,&rect);
#endif
	} else {
		//---どちらもＤＩＢならば
		dib.Put(&cell->dib,
			x + sx,y + sy,&rect,efect);
	}

	return EI_NOERR;
}

//---透明色ありの高速転送
int eiCell::PutTrans(eiCell *cell,int x,int y)
{
	if(Data.SurfaceFlag && cell->Data.SurfaceFlag){
		//---両方がサーフェイス上にあれば
#ifdef EIUSE_DIRECTDRAW
		pDDSurface->Put(
			cell->pDDSurface,
			x + cell->Data.rectSurface.left,
			y + cell->Data.rectSurface.top,
			&Data.rectSurface,
			DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT);

	} else if(cell->Data.SurfaceFlag){
		//---転送先がサーフェイスにあれば
		dib.CopyToDDSurface(
			cell->pDDSurface,
			x + cell->Data.rectSurface.left,
			y + cell->Data.rectSurface.top);
#endif
	} else {
		//---どちらもＤＩＢならば
		RECT rect;
		rect.left = 0;
		rect.top = 0;
		rect.right = dib.xSize;
		rect.bottom = dib.ySize;

		dib.PutTrans(&cell->dib,
			x,y,&rect);
	}

	return EI_NOERR;
}

//---クリッピング処理をして透明転送
int eiCell::PutTransClip(eiCell *cell,int x,int y,LPRECT lpSrc,int efect /*= 0*/)
{
	int sx,sy;
	RECT rect;
	//---クリッピング計算
	if(!lpSrc){
		if(!eiGetClipingRect(&rect,&Data.rectClip,&cell->Data.rectClip,x,y)){
			return EI_NOERR;
		}
	} else {
		if(!eiGetClipingRect(&rect,lpSrc,&cell->Data.rectClip,x,y)){
			return EI_NOERR;
		}
	}
/*
	if(x < 0)
		x = 0;
	if(y < 0)
		y = 0;*/

	sx = rect.left;
	sy = rect.top;
	if(lpSrc){
		sx -= lpSrc->left;//(lpSrc->left - rect.left);
		sy -= lpSrc->top;//(lpSrc->top - rect.top);
	}

	if(Data.SurfaceFlag && cell->Data.SurfaceFlag){
		//---両方がサーフェイス上にあれば
#ifdef EIUSE_DIRECTDRAW
		rect.left   += Data.rectSurface.left;
		rect.right  += Data.rectSurface.left;
		rect.top    += Data.rectSurface.top;
		rect.bottom += Data.rectSurface.top;

		pDDSurface->Put(
			cell->pDDSurface,
			x + cell->Data.rectSurface.left + sx,
			y + cell->Data.rectSurface.top + sy,
			&rect,
			DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT);
	} else if(cell->Data.SurfaceFlag){
		//---転送先がサーフェイスにあれば
		dib.CopyToDDSurface(
			cell->pDDSurface,
			x + cell->Data.rectSurface.left + sx,
			y + cell->Data.rectSurface.top + sy,&rect);
#endif
	} else {
		//---どちらもＤＩＢならば
		dib.PutTrans(&cell->dib,
			x + sx,y + sy,&rect,efect);
	}

	return EI_NOERR;
}

//---透明転送指定可能クリッピング
int eiCell::PutClipSelect(eiCell *cell,int x,int y,LPRECT lpSrc,int trans,int efect /*= 0*/)
{
	int sx,sy;
	RECT rect;
	//---クリッピング計算
	if(!lpSrc){
		if(!eiGetClipingRect(&rect,&Data.rectClip,&cell->Data.rectClip,x,y)){
			return EI_NOERR;
		}
	} else {
		if(!eiGetClipingRect(&rect,lpSrc,&cell->Data.rectClip,x,y)){
			return EI_NOERR;
		}
	}

	sx = rect.left;
	sy = rect.top;
	if(lpSrc){
		sx -= lpSrc->left;
		sy -= lpSrc->top;
	}

	if(Data.SurfaceFlag && cell->Data.SurfaceFlag){
		//---両方がサーフェイス上にあれば
		int DDFlag = DDBLTFAST_WAIT;

		if(trans)
			DDFlag |= DDBLTFAST_SRCCOLORKEY;
#ifdef EIUSE_DIRECTDRAW
		rect.left   += Data.rectSurface.left;
		rect.right  += Data.rectSurface.left;
		rect.top    += Data.rectSurface.top;
		rect.bottom += Data.rectSurface.top;

		pDDSurface->Put(
			cell->pDDSurface,
			x + cell->Data.rectSurface.left + sx,
			y + cell->Data.rectSurface.top + sy,
			&rect,
			DDFlag);
	} else if(cell->Data.SurfaceFlag){
		//---転送先がサーフェイスにあれば
		dib.CopyToDDSurface(
			cell->pDDSurface,
			x + cell->Data.rectSurface.left + sx,
			y + cell->Data.rectSurface.top + sy,&rect);
#endif
	} else {
		//---どちらもＤＩＢならば
		if(trans)
			dib.PutTrans(&cell->dib,
				x + sx,y + sy,&rect,efect);
		else
			dib.Put(&cell->dib,
				x + sx,y + sy,&rect,efect);
	}

	return EI_NOERR;
}

//---多機能矩形転送
int eiCell::PutExtend(eiCell *cell,int x,int y,
							  double xRate,double yRate,int efect,LPRECT lpSrc)
{
	int tx,ty,sx,sy;
	RECT rect,rect2;
	int DDFlag = DDBLT_WAIT;//,result;

	if(efect & EI_TRANS)
		DDFlag |= DDBLT_KEYSRC;

	//---クリッピング計算
	if(!lpSrc){
		tx = rect2.left = Data.rectClip.left;
		ty = rect2.top = Data.rectClip.top;
		rect2.right = (int)((double)(Data.rectClip.right - rect2.left) * xRate) + rect2.left;
		rect2.bottom = (int)((double)(Data.rectClip.bottom - rect2.top) * yRate) + rect2.top;

		if(!eiGetClipingRect(&rect,&rect2,&cell->Data.rectClip,x,y)){
			return EI_NOERR;
		}
	} else {
		tx = rect2.left = lpSrc->left;
		ty = rect2.top = lpSrc->top;
//		rect2.right = (int)((double)(Data.rectClip.right - rect2.left) * xRate) + rect2.left;
//		rect2.bottom = (int)((double)(Data.rectClip.bottom - rect2.top) * yRate) + rect2.top;

		if(!eiGetClipingRect(&rect,lpSrc,&cell->Data.rectClip,x,y)){
			return EI_NOERR;
		}
	}
	//---転送先の矩形
	rect2 = rect;

/*	if(rect2.right >= cell->Data.rectClip.right){
		rect2.right = cell->Data.rectClip.right;
	}
	if(rect2.bottom >= cell->Data.rectClip.bottom){
		rect2.bottom = cell->Data.rectClip.bottom;
	}*/

	sx = rect.left;
	sy = rect.top;
	rect.right = (int)((double)(rect.right - tx/*rect.left*/) / xRate) + tx;// + rect.left;
	rect.bottom = (int)((double)(rect.bottom - ty/*rect.top*/) / yRate) + ty;// + rect.top;
	if(tx != rect.left){
		rect.left = (int)((double)(rect.left - tx) / xRate);
	}
	if(ty != rect.top){
		rect.top = (int)((double)(rect.top - ty) / yRate) ;
	}
/*	rect.left = 0;
	rect.top = 0;
	rect.right = 31;
	rect.bottom = 31;*/
/*	//----------------------
	rect2.right = (int)((double)(rect2.right - tx) / xRate) + tx;
	rect2.bottom = (int)((double)(rect2.bottom - ty) / yRate) + ty;
	if(tx != rect2.left){
		rect2.left = (int)((double)(rect2.left - tx) / xRate) ;
	}
	if(ty != rect2.top){
		rect2.top = (int)((double)(rect2.top - ty) / yRate) ;
	}
*/
	if(Data.SurfaceFlag && cell->Data.SurfaceFlag){
		//---両方がサーフェイス上にあれば
#ifdef EIUSE_DIRECTDRAW
		rect.left   += (Data.rectSurface.left);
		rect.right  += (Data.rectSurface.left);
		rect.top    += Data.rectSurface.top;
		rect.bottom += Data.rectSurface.top;

/*		rect.left = 0 * 32 + 64;
		rect.top = 256 + 64;
		rect.right = rect.left + 32;
		rect.bottom = rect.top + 32;*/
/*		eiSurface[Data.SurfaceNumber].PutExtend(
			&eiSurface[cell->Data.SurfaceNumber],
			x + cell->Data.rectSurface.left + sx,
			y + cell->Data.rectSurface.top + sy,
			&rect,
			//&Data.rectSurface,
			DDFlag,
			xRate,yRate);*/
		rect2.left   += (cell->Data.rectSurface.left + x);
		rect2.right  += (cell->Data.rectSurface.left + x);
		rect2.top    += (cell->Data.rectSurface.top + y);
		rect2.bottom += (cell->Data.rectSurface.top + y);
		pDDSurface->PutExtend2(
			cell->pDDSurface,
			&rect2,&rect,DDFlag);

/*		char s[100];
		sprintf(s,"(%4d,%4d,%4d,%4d) (%4d,%4d,%4d,%4d)\n",
			rect.left,rect.top,rect.right,rect.bottom,
			rect2.left,rect2.top,rect2.right,rect2.bottom);
		eiDebugWriteFile(s);
*/
	} else if(cell->Data.SurfaceFlag){
		//---転送先がサーフェイスにあれば
		dib.CopyToDDSurface(
//			&eiSurface[cell->Data.SurfaceNumber],
			cell->pDDSurface,
			x + cell->Data.rectSurface.left,
			y + cell->Data.rectSurface.top);
#endif
	} else {
		//---どちらもＤＩＢならば
		dib.PutTrans(&cell->dib,
			x,y,&rect);
	}

	return EI_NOERR;
}

int eiCell::PutFile(int x,int y,
						   EISTR *name,EISTR *slname,int mode)
{
	eiCell ec;// = new eiCell;

	if(slname == NULL){
		if(ec.ReadDIB(name,NULL,mode)){
			ec.Put(this,x,y);
			ec.Delete();
		}
	} else {
		if(ec.ReadDIB(name,slname,mode)){
			ec.Put(this,x,y);
			ec.Delete();
		}
	}

	return 1;
}

//---コピー
int eiCell::Copy(eiCell *cell,int x,int y,LPRECT lpSrcRect)
{
	RECT rect,rect2;
	int DDFlag = DDBLT_WAIT;

	rect = *lpSrcRect;

	rect2.left = x;
	rect2.right = (rect.right - rect.left) + x;
	rect2.top = y;
	rect2.bottom = (rect.bottom - rect.top) + y;

	if(Data.SurfaceFlag && cell->Data.SurfaceFlag){
		//---両方がサーフェイス上にあれば
#ifdef EIUSE_DIRECTDRAW
		rect.left   += (Data.rectSurface.left);
		rect.right  += (Data.rectSurface.left);
		rect.top    += Data.rectSurface.top;
		rect.bottom += Data.rectSurface.top;

		rect2.left   += (cell->Data.rectSurface.left);
		rect2.right  += (cell->Data.rectSurface.left);
		rect2.top    += (cell->Data.rectSurface.top);
		rect2.bottom += (cell->Data.rectSurface.top);

		pDDSurface->PutExtend2(
			cell->pDDSurface,
			&rect2,&rect,DDFlag);

	} else if(cell->Data.SurfaceFlag){
		//---転送先がサーフェイスにあれば
		dib.CopyToDDSurface(
			cell->pDDSurface,
			x + cell->Data.rectSurface.left,
			y + cell->Data.rectSurface.top);
#endif
	} else {
		//---どちらもＤＩＢならば
		dib.PutTrans(&cell->dib,
			x,y,&rect);
	}

	return EI_NOERR;
}

//---グラフィック描画関数
int eiCell::DrawCalcPos(int &x1,int &y1,int &x2,int &y2)
{
	if(x1 < 0)
		x1 = 0;
	if(y1 < 0)
		y1 = 0;
	if(x2 < 0)
		x2 = 0;
	if(y2 < 0)
		y2 = 0;

	if(x1 >= Data.xSize && x2 >= Data.xSize)
		return 0;
	if(y1 >= Data.ySize && y2 >= Data.ySize)
		return 0;

	if(x1 >= Data.xSize)
		x1 = Data.xSize -1;
	if(y1 >= Data.ySize)
		y1 = Data.ySize -1;
	if(x2 >= Data.xSize)
		x2 = Data.xSize - 1;
	if(y2 >= Data.ySize)
		y2 = Data.ySize -1;

	if(x1 == x2 && y1 == y2)
		return 0;

	return 1;
}

//---ラインを描く
void eiCell::DrawLine(int x1,int y1,int x2,int y2,int col,int efect)
{
	if(!DrawCalcPos(x1,y1,x2,y2))
		return;

	if(Data.SurfaceFlag){
#ifdef EIUSE_DIRECTDRAW
		pDDSurface->DrawLine(
			x1 + Data.rectSurface.left ,
			y1 + Data.rectSurface.top,
			x2 + Data.rectSurface.left,
			y2 + Data.rectSurface.top,
			col,efect);
#endif
	} else {
		dib.DrawLine(x1,y1,x2,y2,col,efect);
	}
}

//---ボックスを描く
void eiCell::DrawBox(int x1,int y1,int x2,int y2,int col,int efect)
{
	if(!DrawCalcPos(x1,y1,x2,y2))
		return;

	if(Data.SurfaceFlag){
#ifdef EIUSE_DIRECTDRAW
		pDDSurface->DrawBox(
			x1 + Data.rectSurface.left ,
			y1 + Data.rectSurface.top,
			x2 + Data.rectSurface.left,
			y2 + Data.rectSurface.top,
			col,efect);
#endif
	} else {
		dib.DrawBox(x1,y1,x2,y2,col,efect);
	}
}

//---塗りつぶしたボックスを描く
void eiCell::DrawFillBox(int x1,int y1,int x2,int y2,int col,
						 int efect,int alpha /* = 255*/)
{
	if(efect & EI_ALPHA){
		//---アルファ値使用だったら
		DrawFillBoxAlpha(x1,y1,x2,y2,col,alpha);
		return;
	}

	if(!DrawCalcPos(x1,y1,x2,y2))
		return;

	if(Data.SurfaceFlag){
#ifdef EIUSE_DIRECTDRAW
		pDDSurface->DrawFillBox(
			x1 + Data.rectSurface.left,
			y1 + Data.rectSurface.top,
			x2 + Data.rectSurface.left,// + 1,
			y2 + Data.rectSurface.top,// + 1,
			col,efect);
#endif
	} else {
		dib.DrawFillBox(x1,y1,x2,y2,col,efect);
	}
}

//---透明値を含む描画
void eiCell::DrawFillBoxAlpha(int x1,int y1,int x2,int y2,int col,int alpha/* = 255*/)
{
	int x,y,sx,addres,size = (Data.Color / 8),
		xOffset = Data.rectSurface.left,yOffset = Data.rectSurface.top;
	int BlueBit = 0,GreenBit = BlueBit + ::eiSystem.BlueBit,
		RedBit = GreenBit + ::eiSystem.GreenBit;
	DWORD pixel,wcolor = col;
	int red,green,blue,AlphaRed,AlphaGreen,AlphaBlue;
	EILOCKEDCELL ec;

	if(Data.Color < 16)
		return;
	if(!DrawCalcPos(x1,y1,x2,y2))
		return;

	Lock(&ec);

	x1 += xOffset;
	y1 += yOffset;
	x2 += xOffset;
	y2 += yOffset;

	AlphaRed = ((col & ::eiSystem.RedMask) >> RedBit) * alpha / 256;
	AlphaGreen = ((col & ::eiSystem.GreenMask) >> GreenBit) * alpha / 256;
	AlphaBlue = ((col & ::eiSystem.BlueMask) >> BlueBit) * alpha / 256;

	//---16,24,32bit Color
	for(y = y1;y <= y2;y ++){
		addres = y * ec.LineSize;
		for(x = x1,sx = x1 * (Data.Color / 8);x <= x2;x ++, sx += (Data.Color / 8)){
			if(Data.Color == 16){
				pixel = *(WORD *)(ec.lpMemory + addres + sx);
			} else if(Data.Color == 32){
				pixel = *(DWORD *)(ec.lpMemory + addres + sx);
			} else {
				pixel = ((*(BYTE *)(ec.lpMemory + addres + sx)) << 16)
				| ((*(BYTE *)(ec.lpMemory + addres + sx + 1)) << 8)
				| ((*(BYTE *)(ec.lpMemory + addres + sx + 2)) << 0);
			}

			red = ((pixel & ::eiSystem.RedMask) >> RedBit) * (255 - alpha) / 256;
			green = ((pixel & ::eiSystem.GreenMask) >> GreenBit) * (255 - alpha) / 256;
			blue = ((pixel & ::eiSystem.BlueMask) >> BlueBit) * (255 - alpha) / 256;

			wcolor = ((red + AlphaRed) << RedBit)
				| ((green + AlphaGreen) << GreenBit)
				| ((blue + AlphaBlue) << BlueBit);

			if(Data.Color == 16){
				*(WORD *)(ec.lpMemory + addres + sx) = (WORD)wcolor;
			} else if(Data.Color == 32){
				*(DWORD *)(ec.lpMemory + addres + sx) = (DWORD)wcolor;
			} else {
				*(BYTE *)(ec.lpMemory + addres + sx) = 
					(BYTE)(wcolor >> 16);
				*(BYTE *)(ec.lpMemory + addres + sx + 1) = 
					(BYTE)(wcolor >> 8);
				*(BYTE *)(ec.lpMemory + addres + sx + 2) = 
					(BYTE)(wcolor >> 0);
			}
		}
	}

	UnLock();
}


//---点を打つ
void eiCell::DrawPixel(int x,int y,int col,int efect/* = EI_PSET*/)
{
	if(Data.SurfaceFlag){
#ifdef EIUSE_DIRECTDRAW
		pDDSurface->DrawPixel(
			x + Data.rectSurface.left,
			y + Data.rectSurface.top,col,efect);
#endif
	} else {
		dib.DrawPixel(x,y,col,efect);
	}
}

int eiCell::GetPixel(int x,int y,int efect /*= EI_PSET*/)
{
//	if(!(x >= 0 && y >= 0 && x < Data.xSize && y < Data.ySize))
//		return 0;

	if(Data.SurfaceFlag){
#ifdef EIUSE_DIRECTDRAW
		return pDDSurface->GetPixel(
			x + Data.rectSurface.left,
			y + Data.rectSurface.top,efect);
#endif
	} else {
		return dib.GetPixel(x,y,efect);
	}

	return 0;
}

//---テキストを描く
void eiCell::DrawText(EISTR *string,int x,int y,int color,int efect)
{
	if(Data.SurfaceFlag){
#ifdef EIUSE_DIRECTDRAW
		if(eiUseDirectText){
			//---ダイレクトテキスト
			pDDSurface->DDSurfaceTextDirect(
				string,
				x + Data.rectSurface.left,
				y + Data.rectSurface.top,color,efect);
		} else {
			//---通常
			pDDSurface->DDSurfaceText(
				string,
				x + Data.rectSurface.left,
				y + Data.rectSurface.top,color,efect);
		}
#endif
	} else {
		dib.DibText(string,x,y,color,efect);
	}
}

void eiCell::DrawTextDirect(EISTR *string,int x,int y,int color,int efect /*= EI_TRANS*/)
{
	if(Data.SurfaceFlag){
#ifdef EIUSE_DIRECTDRAW
		pDDSurface->DDSurfaceTextDirect(
			string,
			x + Data.rectSurface.left,
			y + Data.rectSurface.top,color,efect);
#endif
	} else {
		dib.DibText(string,x,y,color,efect);
	}
}

//---セルの内容をクリア
void eiCell::Clear(int col /* = 16 */)
{
	DrawFillBox(0,0,Data.xSize - 1,Data.ySize - 1,col);
}

//---グラフィックメモリ領域をロックする
int eiCell::Lock(EILOCKEDCELL *ec)
{
#ifdef EIUSE_DIRECTDRAW
	LPBYTE Pointer;
	int Pitch;
#endif

	if(!Data.CreateFlag)
		return 0;

	if(Data.SurfaceFlag){
#ifdef EIUSE_DIRECTDRAW
		if(pDDSurface->Lock(&Pointer,&Pitch) == FALSE)
			return 0;
		ec->lpMemory = Pointer;
		ec->LineSize = Pitch;
		if(pDDSurface->Color == 8)
			ec->PixelSize = 1;
		else
			ec->PixelSize = 2;

		return 1;
#endif
	} else {
		ec->lpMemory = dib.lpBitmap;
		ec->LineSize = dib.LineSize;
		ec->PixelSize = 1;
		return 1;
	}
	return 0;
}

//---ロックを解除
void eiCell::UnLock(void)
{
	if(!Data.CreateFlag)
		return;

	if(Data.SurfaceFlag){
#ifdef EIUSE_DIRECTDRAW
		pDDSurface->UnLock();
#endif
	} else {
	}
	return;
}

//----------------------------------------
//---eiCellの配列にパターンを連続読み込み
EI_API int eiCellReadPattern(eiCell *cell,EISTR *name,EISTR *slname,int mode,
							int top,int num,int sx,int sy)
{
	int a,x,y;
	eiDib ed;
	RECT rect;
	
	if(ed.Read(name,slname,mode) == FALSE)
		return 0;

	for(a = top,x = 0,y = 0;a < top + num;a ++){
		//前にあったセルを削除

		cell[a].Delete();

		if(sx == 0){
			sx = ed.xSize;
		}
		if(sy == 0){
			sy = ed.ySize;
		}
		
		cell[a].Create(sx,sy);		
		
		memcpy(cell[a].dib.lpRGB,ed.lpRGB,sizeof(RGBQUAD)*256);

		rect.left = x;
		rect.top = y;
		rect.right = x + sx;
		rect.bottom = y + sy;
		ed.Put(&cell[a].dib,
			0,0,&rect);
		
		x += sx;
		if(x >= ed.xSize){
			x = 0;
			y += sy;
			if(y >= ed.ySize){
				y = 0;
				break;
			}
		}
	}

	ed.Delete();

	return 1;
}

#ifdef EIUSE_DIRECTDRAW
//---eiCellの配列をサーフェイスに連続転送
EI_API void eiCellSetSurface(eiCell *cell,int x,int y,
					  int sx,int sy,int num ,int plane /*= 2*/)
{
	int a,dx = x,dy = y;
	RECT rect;//={0,0,640,480};

	if(!(::eiSystem.ScreenMode & DIRECTDRAW_MODE))
		return;

	for(a = 0;a < num;a ++){
		SetRect(&rect,dx,dy,
			dx + cell[a].Data.xSize,
			dy + cell[a].Data.ySize);
		cell[a].SetSurface(&rect,plane);

		dx += sx;
		if(dx >= ::eiSystem.xScreenSize){
			dx = 0;
			dy += sy;
			if(dy >= ::eiSystem.yScreenSize){
				dy = 0;
			}
		}
	}
}

//----------------------------------------
//---eiCellの配列にパターンを連続読み込み
EI_API int eiTextureCellReadPattern(eiTextureCell *cell,EISTR *name,EISTR *slname,int mode,
							int top,int num,int sx,int sy)
{
	int a,x,y;
	eiDib ed;
	RECT rect;
	
	if(ed.Read(name,slname,mode) == FALSE)
		return 0;

	for(a = top,x = 0,y = 0;a < top + num;a ++){
		//前にあったセルを削除

		cell[a].Delete();

		if(sx == 0){
			sx = ed.xSize;
		}
		if(sy == 0){
			sy = ed.ySize;
		}
		
		cell[a].Create(sx,sy);		
		
		memcpy(cell[a].dib.lpRGB,ed.lpRGB,sizeof(RGBQUAD)*256);

		rect.left = x;
		rect.top = y;
		rect.right = x + sx;
		rect.bottom = y + sy;
		ed.Put(&cell[a].dib,
			0,0,&rect);
		
		x += sx;
		if(x >= ed.xSize){
			x = 0;
			y += sy;
			if(y >= ed.ySize){
				y = 0;
				break;
			}
		}
	}

	ed.Delete();

	return 1;
}
#endif

#ifdef EIUSE_DIRECTDRAW
//---eiCellの配列をサーフェイスに連続転送
EI_API void eiTextureCellSetSurface(eiTextureCell *cell,int x,int y,
					  int sx,int sy,int num ,int plane /*= 2*/)
{
	int a,dx = x,dy = y;
	RECT rect;//={0,0,640,480};

	if(!(::eiSystem.ScreenMode & DIRECTDRAW_MODE))
		return;

	for(a = 0;a < num;a ++){
		SetRect(&rect,dx,dy,
			dx + cell[a].Data.xSize,
			dy + cell[a].Data.ySize);
		cell[a].SetSurface(&rect,plane);

		dx += sx;
		if(dx >= ::eiSystem.xScreenSize){
			dx = 0;
			dy += sy;
			if(dy >= ::eiSystem.yScreenSize){
				dy = 0;
			}
		}
	}
}
#endif
