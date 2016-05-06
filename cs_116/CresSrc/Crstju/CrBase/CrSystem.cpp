//--------------------------
//CRESTEAJU System Function
//

#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRSYSTEM

#define EXTERN_EICLASS
#include "..\CrSystem.h"


//---描画ＦＰＳ（何フレームに一回描くか）
CRSYSTEM_API int crsysGetFieldDrawRate(void)
{
	return crdataGetSystem()->DrawRate;
}

//---フィールド中心にキャラクターを描くか
CRSYSTEM_API int crsysGetDrawMainCharacter(void)
{
	return crdataGetSystem()->DrawCenterCharacter;
}

//---キー入力待ちの時のウェイト
CRSYSTEM_API int crsysGetWaitKeyDelay(void)
{
	return crdataGetSystem()->KeyWaitDelay;
}

//---キーを押したあとのウェイト
CRSYSTEM_API int crsysGetWaitKeyAfterPush(void)
{
	return crdataGetSystem()->KeyWaitAfterPush;
}

//---スクリーンモード
CRSYSTEM_API int crsysGetScreenMode(void)
{
	return crdataGetInitialize()->ScreenMode;
}

//---グラフィックレベル
CRSYSTEM_API int crsysGetExtentionLevel(void)
{
	return crdataGetIniFile()->ExtentionLevel;
}

//---システム情報をセット
CRSYSTEM_API int crsysSetSystemInfo(void)
{
	ef->SetDrawRate(crdataGetSystem()->DrawRate);

	if(crdataGetSystem()->AutoDrawFrame == 0){
		ef->SetDrawMode(EF_DRAW_MANUAL);
	} else {
		ef->SetDrawMode(EF_DRAW_AUTOCHANGE);
	}

	return 1;
}

//---３Ｄ能力をテスト
static int UseGouraudShading = 1;
CRSYSTEM_API int crsysGetGouraudShading(void)
{
	return UseGouraudShading;
}

CRSYSTEM_API int crsysSetGouraudShading(int flag)
{
	int old = UseGouraudShading;

	UseGouraudShading = flag;

	return old;
}

CRSYSTEM_API int crsysSetup3DCaps(void)
{
	if(eid3d->Begin()){
		D3DDEVICEDESC7 desc;

		memset(&desc,0,sizeof(desc));
		eid3d->lpD3DDevice->GetCaps(&desc);

		if(desc.dpcTriCaps.dwShadeCaps & D3DSHADE_GOURAUD){
			UseGouraudShading = 1;
		} else {
			UseGouraudShading = 0;
		}
		eid3d->End();
	}

	return 1;
}

//---ディスプレイセットアップ
CRSYSTEM_API int crsysSetupDisplay(void)
{
	int rate;
//#if (CR_DEBUG == 1)
//	rate = eiSetDrawRefreshRate(-1);//crsysBenchRefreshRate(1000);
//#else
	if(crdataGetIniFile()->UseDirectDrawHardware == 0){
		//---DirectDrawがエミュレーション
		rate = 60;
	} else {
		rate = crsysBenchRefreshRate(1000);
	}
//#endif
	if(crdataGetIniFile()->ForceRefreshRate){
		rate = crdataGetIniFile()->ForceRefreshRate;
	} else if(rate < 60){
		rate = 60;
	} else if(rate > 120){
		rate = 120;
	}

	//---80Hz以上だったら
	if(rate >= 78 && crdataGetIniFile()->ForceRefreshRate_Over80){
		rate = 60;
		crdataGetIniFile()->ForceRefreshRate = 60;
	}

	rate = ((rate + 2) / 5) * 5;
//	crdataGetSystem()->DisplayRefreshRate = rate;

	if(crdataGetIniFile()->ForceFPS){
		crdataGetSystem()->DrawRate = (crdataGetIniFile()->ForceFPS * 100) / (rate);
	} else if(rate <= 90){
		if(rate < 60)
			rate = 60;
		crdataGetSystem()->DrawRate = 100;
	} else {
		if(rate >= 120)
			rate = 120;
		crdataGetSystem()->DrawRate = rate / 2;
//		crdataGetSystem()->DrawRate = (60 * 100) / rate;
	}
	ef->SetDrawRate(crdataGetIniFile()->BaseCount);
	crdataGetSystem()->DrawRate = crdataGetIniFile()->BaseCount;

	if(crdataGetIniFile()->ForceRefreshRate){
		eiSetDisplayRefreshRate(crdataGetIniFile()->ForceRefreshRate);
	} else {
		eiSetDisplayRefreshRate(rate);
	}

	if(crdataGetIniFile()->ForceFPS){
		eiSetDrawRefreshRate(crdataGetIniFile()->ForceFPS);
	} else {
		eiSetDrawRefreshRate(rate);
	}
	et->SetWaitCount(1000 / eiSetDrawRefreshRate(-1));

	crdataGetIniFile()->RuningRefreshRate = rate;

	return rate;
}

//---リフレッシュレートを計測
CRSYSTEM_API int crsysBenchRefreshRate(int range)
{
	int rate = 0;
	eiTime et;

	if(crsysGetScreenMode() == 1)
		return 0;

	et.Reset();
	et.Wait(4);
	et.Reset();
	while(et.Get() <= range && rate <= 240){
		ew->Flip();
		rate ++;
	}

	return rate;//rate * (1000 / range);
}

//---クイック処理
#define IF_QUICK() if((ei->Quick == 1 && crdataGetDebug() == 1))
#define IF_NOTQUICK() if(!(ei->Quick == 1 && crdataGetDebug() == 1))

CRSYSTEM_API int crsysQuick(void)
{
#if(CR_DEBUG == 1)
	ei->Get();
	if((ei->Quick == 1 && crdataGetDebug() == 1))
		return 1;
#endif
	return 0;
}

CRSYSTEM_API int crsysNotQuick(void)
{
#if(CR_DEBUG == 1)
	ei->Get();
	if(!(ei->Quick == 1 && crdataGetDebug() == 1))
		return 1;
#else
	return 1;
#endif
	return 0;
}

static ei_s32 CodeMode = CODE_OTHER;

//---動作モード設定＆取得
CRSYSTEM_API int crsysSetCodeMode(int mode)
{
	int old = CodeMode;

	CodeMode = mode;

	return CodeMode;
}

CRSYSTEM_API int crsysGetCodeMode(void)
{
	return CodeMode;
}

//---３Ｄファンクションテスト
CRSYSTEM_API void crsysTest3DFunction(void)
{
	int a;
	D3DTLVERTEX tex[4];
	eiD3DMaterial mat;

	memset(&tex[0],0,sizeof(tex));

	for(a = 0;a < 4;a ++){
		tex[a].dvRHW = 1;
		tex[a].dcSpecular = 0;
		tex[a].dvSZ = 0.0f;
		tex[a].dcColor = RGBA_MAKE(255,255,255,0);
	}

	tex[0].dvSX = 0;
	tex[0].dvSY = 0;
	tex[1].dvSX = 639;
	tex[1].dvSY = 0;
	tex[2].dvSX = 0;
	tex[2].dvSY = 479;
	tex[3].dvSX = 639;
	tex[3].dvSY = 479;

	pViewport->ClearAll();

	//---描画開始
	eid3d->Begin();
	eid3d->BeginAlphaBlend();
//	eid3d->lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND,D3DBLEND_ONE);
	eid3d->lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_ONE);
	eid3d->SetDrawMode(EID3D_DRAWMODE_FILL);

	eid3d->DrawPrimitive( D3DPT_TRIANGLESTRIP,
		D3DFVF_TLVERTEX,&tex[0], 4, D3DDP_WAIT);
	//---描画終了
	eid3d->EndAlphaBlend();
	eid3d->End();


	EILOCKEDCELL ec;
	ei_u32 pixel;
	ew->lpCell[1]->Lock(&ec);
	if(eiGetSurfacePointer()->Color == 16){
		pixel = *(ei_u16 *)(ec.lpMemory + ec.LineSize * 8 + 128 * 2);
		if((pixel == 0x7fff || pixel == 0xffff)
			&& crdataGetIniFile()->EnableAddAlpha == 0){
			//---加算半透明合成不可！！
			crdataGetIniFile()->EnableAddAlpha = 0;
		} else {
			crdataGetIniFile()->EnableAddAlpha = 1;
		}
	} else {
		pixel = *(ei_u32 *)(ec.lpMemory + ec.LineSize * 8 + 128 * 4);
		if((pixel == 0x00ffffff || pixel == 0xffffff0)
			&& crdataGetIniFile()->EnableAddAlpha == 0){
			//---加算半透明合成不可！！
			crdataGetIniFile()->EnableAddAlpha = 0;
		} else {
			crdataGetIniFile()->EnableAddAlpha = 1;
		}
	}
	ew->lpCell[1]->UnLock();

	ew->lpCell[1]->DrawFillBox(0,0,639,479,ep->ToRGB(CRCOLOR_BLACK));
	ew->lpCell[0]->DrawFillBox(0,0,639,479,ep->ToRGB(CRCOLOR_BLACK));

	//---３Ｄ能力取得
	crsysSetup3DCaps();

//crdataGetIniFile()->EnableAddAlpha = 1;

//	ew->Flip();
//	et->Delay2(1000);
}
