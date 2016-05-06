/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBase_EfectAPI.cpp ...Screen Efect functions

-----------------------------------------------------------*/

#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBASE_EFECTAPI

#define EXTERN_EICLASS
#include "..\CrBase.h"

#define CR_GAMEINFO_EXTERNPOINTER
#include "..\CrGameInfo.h"

extern EI_API EI_DDINFO eiDDInfo;

//---エフェクト範囲取得
static RECT ScreenRect = {0,0,640,480};
static int UseFadeCallBack = 0;

void crefectSetup3DEfect(void);
#include "CrBase_EfectSub3D.cpp"

static eiD3DMatrix crefectSetup3DEfect_matProjection;

void crefectSetup3DEfect(void)
{
	//---ビューポート設定
	if(UseFadeCallBack == 1){
		pViewport->SetRect(0,0,640,ef->Field.ySize * 32 + 32);
	} else {
		pViewport->SetRect(0,0,640,480);
	}
	pViewport->Set();

	crefectSetup3DEfect_matProjection.CalcProjectionMatrix(0.50f,1000.0f,3.14f / 4.0f);
	eid3d->SetTransformProjection(&crefectSetup3DEfect_matProjection);
}

CRBASE_EFECTAPI void crefectSetFadeCallBack(int mode)
{
	UseFadeCallBack = mode;
}

CRBASE_EFECTAPI void crefectScreenEfect_FadeOut(RECT *pRect /*= NULL*/,int count/*= -1*/,int color/* = RGB(255,255,255)*/,int mode /*= 0*/)
{
	eiCell *pSrcCell = ew->lpBackCell[1];//(eiGetSurfacePointer() + 3);

	crefectSetup3DEfect();

	int a = 0,
		r = (color >> 16) & 0xff,
		g = (color >> 8) & 0xff,
		b = color & 0xff;
	int alpha = 255;
	int Start,RunTime = count;
	D3DTLVERTEX tex[4];

	//---準備
	if(mode == 0){
		crbaseSaveFrontPage();
	} else {
		ew->CopyToBackground();
	}

	memset(&tex[0],0,sizeof(tex));

	for(a = 0;a < 4;a ++){
		tex[a].dvRHW = 1;
		tex[a].dcSpecular = 0;
	}

	tex[0].dvSX = (float)pRect->left;
	tex[0].dvSY = (float)pRect->top;
	tex[0].dvSZ = (float)0.0f;

	tex[1].dvSX = (float)pRect->right;
	tex[1].dvSY = (float)pRect->top;
	tex[1].dvSZ = (float)0.0f;

	tex[2].dvSX = (float)pRect->left;
	tex[2].dvSY = (float)pRect->bottom;
	tex[2].dvSZ = (float)0.0f;

	tex[3].dvSX = (float)pRect->right;
	tex[3].dvSY = (float)pRect->bottom;
	tex[3].dvSZ = (float)0.0f;

	int flag = 0,now;

	for(Start = et->GetTime() , flag = 1;flag == 1;){
		now = et->GetTime() - Start;
		if(now >= RunTime){
			flag = 0;
			now = RunTime;
		}

		alpha = (int)( ((float)(now) / (float)RunTime) * 255.0f );
		if(mode == 1)
			alpha = 255 - alpha;

		if(alpha < 0)
			alpha = 0;
		if(alpha > 255)
			alpha = 255;

		for(a = 0;a < 4;a ++){
			tex[a].dcColor = RGBA_MAKE(r,g,b,alpha);
		}

		pViewport->ClearAll();
		pSrcCell->Put(ew->lpCell[1],0,0);

		//---描画開始
		if(eid3d->Begin()){
			eid3d->BeginAlphaBlend();
			eid3d->SetTexture(NULL);
			eid3d->SetDrawMode(EID3D_DRAWMODE_FILL);

			eid3d->DrawPrimitive( D3DPT_TRIANGLESTRIP,
				D3DFVF_TLVERTEX,&tex[0], 4, D3DDP_WAIT);
			//---描画終了
			eid3d->EndAlphaBlend();
			eid3d->End();
		}

		//---コールバック
		if(UseFadeCallBack == 1){
			if(ef->FGCallback != NULL){
				(*ef->FGCallback)(ew->lpCell[1],0,0,0,0,0);
			}
		}

		//---フリップ
		ew->Flip();
		if(!eiGetFullScreen()){
			eiSleep(1);
		}
	}
}

CRBASE_EFECTAPI void crefectScreenEfect_FadeIn(RECT *pRect /*= NULL*/,int count/*= -1*/,int color/* = RGB(255,255,255)*/)
{
	crefectScreenEfect_FadeOut(pRect,count,color,1);
}

CRBASE_EFECTAPI void crefectScreenChange_AlphaBlend(RECT *pRect /*= NULL*/,int count/*= -1*/)
{
	int sx,sy,ax,alpha;
	ei_u16 src_pix,src2_pix;
	eiCell *lpSrcCell1 = ew->lpCell[1],*lpSrcCell2 = ew->lpBackCell[1],
		*lpDstCell = ew->lpCell[0];
	EILOCKEDCELL src_ec,src2_ec,dst_ec;
	EISYSTEMDATA sys;
	ei_u16 wcolor;
	int src_addres,src2_addres,dst_addres;
	int red,green,blue;
	float AddWorld = 0.1f;
	eiInput lei;

	eiGetLibrarySystemInfo(&sys);
	int BlueBit = 0,GreenBit = BlueBit + sys.BlueBit,
		RedBit = GreenBit + sys.GreenBit;

	if(count == -1)
		count = 16;

	//---保存用セルにコピー
	ew->lpCell[0]->Put(lpSrcCell2,0,0);

	lpSrcCell1->Lock(&src_ec);
	lpSrcCell2->Lock(&src2_ec);
	lpDstCell->Lock(&dst_ec);

	for(alpha = 0;alpha < 256;alpha += count){
		et->Reset();
		lei.Get();
		if(lei.Escape)
			break;
		for(sy = pRect->top;sy < pRect->bottom;sy ++){
			src_addres = sy * src_ec.LineSize;
			src2_addres = sy * src2_ec.LineSize;
			dst_addres = sy * dst_ec.LineSize;

			for(sx = pRect->left,ax = pRect->left;sx < pRect->right;sx ++,ax += 2){
				src_pix = *(ei_u16 *)(src_ec.lpMemory + src_addres + ax);
				src2_pix = *(ei_u16 *)(src2_ec.lpMemory + src2_addres + ax);

				red = ((((src_pix & sys.RedMask) >> RedBit) * alpha) >> 8)
					+ ((((src2_pix & sys.RedMask) >> RedBit) * (255 - alpha)) >> 8);
				green = ((((src_pix & sys.GreenMask) >> GreenBit) * alpha)  >> 8) 
					+ ((((src2_pix & sys.GreenMask) >> GreenBit) * (255 - alpha)) >> 8);
				blue = ((((src_pix & sys.BlueMask) >> BlueBit) * alpha) >> 8)
					+ ((((src2_pix & sys.BlueMask) >> BlueBit) * (255 - alpha)) >> 8);

				wcolor = (ei_u16)((red << RedBit)
					| (green << GreenBit)
					| (blue << BlueBit));
				*(ei_u16 *)(dst_ec.lpMemory + dst_addres + ax) = wcolor;
			}
		}

		//---進める時間
//		AddWorld = (float)et->Get() / 15.0f;

		if(et->Get() < (1000 / 60))
			ew->WaitVSync();
	}

	lpSrcCell1->UnLock();
	lpSrcCell2->UnLock();
	lpDstCell->UnLock();
}

//---幕が切り替わるように画面チェンジ
CRBASE_EFECTAPI void crefectScreenChange_DualScreen(RECT *pRect /*= NULL*/,int count /*= -1*/)
{
	int sx;
	RECT rect;

	if(count == -1)
		count = 40;

	for(sx = 0;sx < 640;sx += count){
		et->Reset();

		ew->lpCell[0]->DrawFillBox(
			sx,
			pRect->top,
			sx + count - 1,
			(pRect->bottom - pRect->top) / 2 + pRect->top - 1,
			ep->ToRGB(CRCOLOR_BLACK));

		ew->lpCell[0]->DrawFillBox(
			639 - (sx + count - 1),
			(pRect->bottom - pRect->top) / 2 + pRect->top,
			639 - sx,
			pRect->bottom,
			ep->ToRGB(CRCOLOR_BLACK));

		if(et->Get() < (1000 / 60))
			ew->WaitVSync();
		if(et->Get() < (1000 / 60))
			ew->WaitVSync();
	}

	for(sx = 0;sx < 640;sx += count){
		et->Reset();

		rect.left = sx;rect.right = sx + count;
		rect.top = (pRect->bottom - pRect->top) / 2 + pRect->top;rect.bottom = pRect->bottom;
		ew->lpCell[1]->PutClip(ew->lpCell[0],sx,
			(pRect->bottom - pRect->top) / 2 + pRect->top,&rect);

		rect.right = 639 - sx;rect.left = 639 - (sx + count);
		rect.top = pRect->top;rect.bottom = (pRect->bottom - pRect->top) / 2 + pRect->top;
		ew->lpCell[1]->PutClip(ew->lpCell[0],639  - (sx + count),pRect->top,&rect);

		if(et->Get() < (1000 / 60))
			ew->WaitVSync();
	}
}

//---細かい四角形で画面チェンジ
CRBASE_EFECTAPI void crefectScreenChange_Rect(RECT *pRect /*= NULL*/,int count /*= -1*/)
{
	int a,sx,sy;
	RECT rect;

	for(a = 0;a < 16;a ++){
		et->Reset();
		for(sy = pRect->top;sy < pRect->bottom;sy += 16){
			rect.left = pRect->left;rect.right = pRect->right;
			rect.top = sy + a;rect.bottom = sy + 1 + a;
			ew->lpCell[0]->DrawFillBox(0,sy + a,pRect->right,sy + 1 + a,ep->ToRGB(CRCOLOR_BLACK));
		}
		for(sx = pRect->left;sx < pRect->right;sx += 16){
			rect.left = sx + a;rect.right = sx + 1 + a;
			rect.top = pRect->top;rect.bottom = pRect->bottom;
			ew->lpCell[0]->DrawFillBox(sx + a,0,sx + 1 + a,pRect->bottom,ep->ToRGB(CRCOLOR_BLACK));
//			ew->lpCell[1]->PutClip(ew->lpCell[0],sx + a,0,&rect);
		}
		if(et->Get() < (1000 / 60))
			ew->WaitVSync();
	}
	for(a = 0;a < 16;a ++){
		et->Reset();
		for(sy = pRect->top;sy < pRect->bottom;sy += 16){
			rect.left = pRect->left;rect.right = pRect->right;
			rect.top = sy + a;rect.bottom = sy + 1 + a;
			ew->lpCell[1]->PutClip(ew->lpCell[0],0,sy + a,&rect);
		}
		for(sx = pRect->left;sx < pRect->right;sx += 16){
			rect.left = sx + a;rect.right = sx + 1 + a;
			rect.top = pRect->top;rect.bottom = pRect->bottom;
			ew->lpCell[1]->PutClip(ew->lpCell[0],sx + a,0,&rect);
		}
		if(et->Get() < (1000 / 60))
			ew->WaitVSync();
	}
}

CRBASE_EFECTAPI RECT *crefectGetRect(RECT *pRect /*= NULL*/)
{
	if(pRect == NULL){
		pRect = &ScreenRect;
	}

	return pRect;
}

//---画面フェードアウト
CRBASE_EFECTAPI void crefectScreenFadeOut(RECT *pRect /*= NULL*/)
{
}

//---画面フェードイン
CRBASE_EFECTAPI void crefectScreenFadeIn(RECT *pRect /*= NULL*/)
{
}

//---連続モザイク
CRBASE_EFECTAPI void crefectScreenEfect_osaic(RECT *pRect,int size,int point)
{
}

//---モザイク
CRBASE_EFECTAPI void crefectScreenEfect_MosaicFrame(RECT *pRect,int size,int point)
{
}

//-------------------------------------------------------
//---別の画面に切り換え
CRBASE_EFECTAPI void crefectScreenChange_FadeOut(RECT *pRect /*= NULL*/,int count /*= -1*/,int run_time /*= -1*/,int color /*= -1*/)
{
	//---lpBackCell[1] : 元の画面 , lpCell[1] : 新しい画面
	int level =  crsysGetExtentionLevel();

	//---ウィンドウ表示かクイックだったら
	if(crsysQuick())
		return;

	if(color == -1)
		color = RGB_MAKE(0,0,0);

	pRect = crefectGetRect(pRect);
	if(count == -1)
		count = 20;
	if(run_time == -1)
		run_time = 250;

	if(level <= CR_EXTENTION_LOW){
		//---単純に黒い矩形で消していく
	} else {
		//---アルファブレンド
		crefectScreenEfect_FadeOut(pRect,run_time,color);
	}
}

CRBASE_EFECTAPI void crefectScreenChange_FadeIn(RECT *pRect /*= NULL*/,int count /*= -1*/,int run_time /*= -1*/,int color /*= -1*/)
//---別の画面に切り換え
{
	//---lpBackCell[1] : 元の画面 , lpCell[1] : 新しい画面
	int level =  crsysGetExtentionLevel();

	//---ウィンドウ表示かクイックだったら
	if(crsysQuick())
		return;

	if(color == -1)
		color = RGB_MAKE(0,0,0);

	pRect = crefectGetRect(pRect);
	if(count == -1)
		count = 20;
	if(run_time == -1)
		run_time = 250;

	if(level <= CR_EXTENTION_LOW){
		if(crsysGetScreenMode() == 1)
			return;
		crefectScreenChange_DualScreen(pRect);
	} else {
		crefectScreenEfect_FadeIn(pRect,run_time,color);
	}
}
