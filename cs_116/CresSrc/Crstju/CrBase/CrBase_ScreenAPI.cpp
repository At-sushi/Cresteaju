/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBase_ScreenAPI.cpp ...Screen functions

-----------------------------------------------------------*/

#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBASE_SCREENAPI

#define EXTERN_EICLASS
#include "..\CrBase.h"

#define CR_GAMEINFO_EXTERNPOINTER
#include "..\CrGameInfo.h"

//---画面からクリア
CRBASE_SCREENAPI void crbaseClearScreen(int mode /*= 0x03*/)
{
	if(mode & 0x02){
		ew->lpCell[1]->Clear(ep->ToRGB(CRCOLOR_BLACK));
	}
	if(crsysGetScreenMode()/*::CrSystem.ScreenMode*/ == 0){
		//---ウィンドウ表示でなかったら
		if(mode & 0x01){
			ew->lpCell[0]->Clear(ep->ToRGB(CRCOLOR_BLACK));
		}
	}
}

//---表示画面から裏画面へのコピー（フルスクリーン時のみ）
CRBASE_SCREENAPI void crbaseCopyFromFrontPage(void)
{
	if(crsysGetScreenMode()/*::CrSystem.ScreenMode*/ == 1)
		//---ウィンドウ表示だったら戻る
		return;
	//---バックバッファーにコピー
	ew->lpCell[0]->Put(ew->lpCell[1],0,0);
}

//---表示画面をバックグラウンドにコピーして保存
CRBASE_SCREENAPI void crbaseSaveFrontPage(int screen /*= 0*/)
{
	if(screen == 0)
		crbaseCopyFromFrontPage();
	ew->CopyToBackground();
}

//---バックグラウンドをバックバッファーに復元
CRBASE_SCREENAPI void crbaseLoadFrontPage(void)
{
	ew->CopyFromBackground();
}

//---壁紙をサーフェイスにコピー
CRBASE_SCREENAPI void crbaseSetWallPaperSuraface(void)
{
	RECT rect = {CR_PTNSURFACE_WALLPAPER_X,CR_PTNSURFACE_WALLPAPER_Y,
		CR_PTNSURFACE_WALLPAPER_X + pWallPaperCell->Data.xSize,
		CR_PTNSURFACE_WALLPAPER_Y + pWallPaperCell->Data.ySize};
	pWallPaperCell->SetSurface(&rect,3);
}

//---壁紙をロード
CRBASE_SCREENAPI void crbaseLoadWallPaper(int number)
{
	char s[80];

	if(number == -1){
		number = pGameInfo->UseWallPaper;
	}

	if(pGameInfo->WallPaper[number] || number <= 1){
		sprintf(s,CR_DATADIR1"Wall%02d.bmp",number);
		if(!pWallPaperCell->ReadFile(s,CR_DATAFILE1,crdataGetFileMode())){
		} else {
		}
		crbaseSetWallPaperSuraface();
/*		RECT rect = {CR_PTNSURFACE_WALLPAPER_X,CR_PTNSURFACE_WALLPAPER_Y,
			CR_PTNSURFACE_WALLPAPER_X + pWallPaperCell->Data.xSize,
			CR_PTNSURFACE_WALLPAPER_Y + pWallPaperCell->Data.ySize};
		pWallPaperCell->SetSurface(&rect,3);*/
	}
}


CRBASE_SCREENAPI void get_rgb(int col,int *r,int *g,int *b)
{
	*r = (col >> 0) & 0xff;
	*g = (col >> 8) & 0xff;
	*b = (col >> 16) & 0xff;
}

static int rate_2_1[4] = {7,7};
static int rate_4_1[4] = {6,6,6,6};

CRBASE_SCREENAPI int make_rgb(int count,int value,int *r,int *g,int *b)
{
	int *rate;

	if(count == 2){
		rate = rate_2_1;

		r[0] = ((r[0] << rate[0]) + (r[1] << rate[1])) >> 8;
		g[0] = ((g[0] << rate[0]) + (g[1] << rate[1])) >> 8;
		b[0] = ((b[0] << rate[0]) + (b[1] << rate[1])) >> 8;
	} else if(count == 4){
		rate = rate_4_1;

		r[0] = (
			(r[0] << rate[0]) + (r[1] << rate[1])
		  + (r[2] << rate[2]) + (r[3] << rate[3])
			) >> 8;
		g[0] = (
			(g[0] << rate[0]) + (g[1] << rate[1])
		  + (g[2] << rate[2]) + (g[3] << rate[3])
			) >> 8;
		b[0] = (
			(b[0] << rate[0]) + (b[1] << rate[1])
		  + (b[2] << rate[2]) + (b[3] << rate[3])
			) >> 8;
	}

	return 0;
}

//---画像復元
CRBASE_SCREENAPI int decode_image(eiCell *pdecode,eiCell *psrc,ei_u8 *pdif)
{
	int x,y,pal;
	int x_size = psrc->Data.xSize,y_size = psrc->Data.ySize;
	int r[4],g[4],b[4];

	x_size *= 2;
	y_size *= 2;

	pdecode->Create(x_size,y_size,24);

	int addres[5];

	for(y = 0;y < y_size;y += 2){
		addres[0] = (psrc->dib.BitmapSize - ( ((y / 2) + 1) * psrc->dib.LineSize) );
		addres[1] = (pdecode->dib.BitmapSize - ((y + 1) * pdecode->dib.LineSize) );

		for(x = 0;x < x_size;x += 2 , addres[0] ++,addres[1] += 6){
//			pal = psrc->GetPixel(x / 2,y / 2);
			if(addres[0] >= psrc->dib.BitmapSize || addres[0] < 0){
				continue;
			}
//			if(addres[1] >= pdecode->dib.BitmapSize || addres[1] < 0){
//				continue;
//			}

			pal = *(psrc->dib.lpBitmap + addres[0]);

/*			col[0] = (int)(
				   ((ei_u32)psrc->dib.lpRGB[pal].rgbBlue << 16)
				| ((ei_u32)psrc->dib.lpRGB[pal].rgbGreen << 8)
				| ((ei_u32)psrc->dib.lpRGB[pal].rgbRed << 0)
				);
			pdecode->DrawPixel(x,y,col[0]);
*/
			*(BYTE *)(pdecode->dib.lpBitmap + addres[1])     = psrc->dib.lpRGB[pal].rgbBlue;
			*(BYTE *)(pdecode->dib.lpBitmap + addres[1] + 1) = psrc->dib.lpRGB[pal].rgbGreen;
			*(BYTE *)(pdecode->dib.lpBitmap + addres[1] + 2) = psrc->dib.lpRGB[pal].rgbRed;
		}
	}

	//---補完処理
	for(y = 1;y < y_size - 1;y ++){
		if((y % 2) == 0){
			addres[0] = (pdecode->dib.BitmapSize - ((y + 1) * pdecode->dib.LineSize)) - 0;
			addres[1] = (pdecode->dib.BitmapSize - ((y + 1) * pdecode->dib.LineSize)) + 6;
		} else {
			addres[0] = (pdecode->dib.BitmapSize - ((y -1  + 1) * pdecode->dib.LineSize) + 0);
			addres[1] = (pdecode->dib.BitmapSize - ((y +1  + 1) * pdecode->dib.LineSize) + 0);
		}
		addres[4] = (pdecode->dib.BitmapSize - ((y + 1) * pdecode->dib.LineSize)
			+ ((y % 2) == 0 ? 3 : 0));

		for(x = (y % 2) == 0 ? 1 : 0;x < x_size;x += 2 ,
			addres[0] += 6,addres[1] += 6,addres[4] += 6){

			b[0] = *(pdecode->dib.lpBitmap + addres[0]);
			g[0] = *(pdecode->dib.lpBitmap + addres[0] + 1);
			r[0] = *(pdecode->dib.lpBitmap + addres[0] + 2);

			b[1] = *(pdecode->dib.lpBitmap + addres[1]);
			g[1] = *(pdecode->dib.lpBitmap + addres[1] + 1);
			r[1] = *(pdecode->dib.lpBitmap + addres[1] + 2);

/*			if((y % 2) == 0){
				col[0] = pdecode->GetPixel(x - 1,y);
				col[1] = pdecode->GetPixel(x + 1,y);
			} else {
				col[0] = pdecode->GetPixel(x,y - 1);
				col[1] = pdecode->GetPixel(x,y + 1);
			}*/

//			get_rgb(col[0],&r[0],&g[0],&b[0]);
//			get_rgb(col[1],&r[1],&g[1],&b[1]);

			make_rgb(2,1, r,g,b);

			*(pdecode->dib.lpBitmap + addres[4]) = (ei_u8)b[0];
			*(pdecode->dib.lpBitmap + addres[4] + 1) = (ei_u8)g[0];
			*(pdecode->dib.lpBitmap + addres[4] + 2) = (ei_u8)r[0];

//			pdecode->DrawPixel(x,y,col[0]);
		}
	}

	for(y = 1;y < y_size - 1;y += 2){
		addres[0] = (pdecode->dib.BitmapSize - ((y -1 + 1) * pdecode->dib.LineSize)) -3 + 3 ;
		addres[1] = (pdecode->dib.BitmapSize - ((y -1 + 1) * pdecode->dib.LineSize)) +3 + 3;
		addres[2] = (pdecode->dib.BitmapSize - ((y +1 + 1) * pdecode->dib.LineSize)) -3 + 3;
		addres[3] = (pdecode->dib.BitmapSize - ((y +1 + 1) * pdecode->dib.LineSize)) +3 + 3;
		addres[4] = (pdecode->dib.BitmapSize - ((y + 1) * pdecode->dib.LineSize)) + 3;

		for(x = 1;x < x_size - 1;x += 2,
			addres[0] += 6,addres[1] += 6,addres[2] += 6,
			addres[3] += 6,addres[4] += 6){

			b[0] = *(pdecode->dib.lpBitmap + addres[0]);
			g[0] = *(pdecode->dib.lpBitmap + addres[0] + 1);
			r[0] = *(pdecode->dib.lpBitmap + addres[0] + 2);

			b[1] = *(pdecode->dib.lpBitmap + addres[1]);
			g[1] = *(pdecode->dib.lpBitmap + addres[1] + 1);
			r[1] = *(pdecode->dib.lpBitmap + addres[1] + 2);

			b[2] = *(pdecode->dib.lpBitmap + addres[2]);
			g[2] = *(pdecode->dib.lpBitmap + addres[2] + 1);
			r[2] = *(pdecode->dib.lpBitmap + addres[2] + 2);

			b[3] = *(pdecode->dib.lpBitmap + addres[3]);
			g[3] = *(pdecode->dib.lpBitmap + addres[3] + 1);
			r[3] = *(pdecode->dib.lpBitmap + addres[3] + 2);

/*			col[0] = pdecode->GetPixel(x - 1,y - 1);
			col[1] = pdecode->GetPixel(x + 1,y - 1);
			col[2] = pdecode->GetPixel(x - 1,y + 1);
			col[3] = pdecode->GetPixel(x + 1,y + 1);

			get_rgb(col[0],&r[0],&g[0],&b[0]);
			get_rgb(col[1],&r[1],&g[1],&b[1]);
			get_rgb(col[2],&r[2],&g[2],&b[2]);
			get_rgb(col[3],&r[3],&g[3],&b[3]);*/

			make_rgb(4,1, r,g,b);

			*(pdecode->dib.lpBitmap + addres[4]) = (ei_u8)b[0];
			*(pdecode->dib.lpBitmap + addres[4] + 1) = (ei_u8)g[0];
			*(pdecode->dib.lpBitmap + addres[4] + 2) = (ei_u8)r[0];
//			pdecode->DrawPixel(x,y,col[0]);
		}
	}

	return 1;
}
