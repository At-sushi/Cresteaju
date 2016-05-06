/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBattle_Anime.cpp ...Battle Animation functions

-----------------------------------------------------------*/

#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBATTLE_ANIME

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#define EXTERN_CRBATTLE
#include "..\CrBase.h"
#include "..\CrBattle.h"

#define CR_GAMEINFO_EXTERNPOINTER
#include "..\CrGameInfo.h"


//---アニメーション開始
CRBATANIME_API void crbatBeginAnime(void)
{
}

//---アニメーション終了
CRBATANIME_API void crbatEndAnime(void)
{
}

//---アニメシーン初期化
CRBATANIME_API int crbatInitAnimeScene(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,int anime)
{
	int object = 0;

	if(anime != -1){
		crbatLoadAnime(anime);
		pChara->BeginAnime(anime);
		//---オブジェクト初期化
		for(object = 0; pDamageInfo->pList[object] != NULL; object ++){
			pBtObject[object].SetPos(
				(float)pDamageInfo->pList[object]->GetFieldX(),
				(float)pDamageInfo->pList[object]->GetFieldY(),
				(float)pDamageInfo->pList[object]->GetFieldZ());
			pBtObject[object].SetAnime(anime);
		}
	}

	return object;
}

//---アニメシーン終了
CRBATANIME_API void crbatEndAnimeScene(CrBattleCharacter *pChara)
{
	pChara->EndAnime();

	crbatClearDrawingList();
	crbatAddDrawingListAll();
//---2001/5/1コメントアウト
//	crbatDrawScene();
//	crbatDrawRefresh();

	crbatReleaseAnime();
}

//---ジャンプアニメーション
CRBATANIME_API int crbatLoadExtCharacter_Jumping(CrBattleCharacter *pChara)
{
	return crbatLoadExtCharacter(pChara,8,8);
}

//---走りアニメーション
CRBATANIME_API int crbatLoadExtCharacter_Running(CrBattleCharacter *pChara)
{
	return crbatLoadExtCharacter(pChara,8,8);
}

//---銃アニメーション
CRBATANIME_API int crbatLoadExtCharacter_Gun(CrBattleCharacter *pChara)
{
	return crbatLoadExtCharacter(pChara,16,4);
}

//---魔法アニメーション
CRBATANIME_API int crbatLoadExtCharacter_Magic(CrBattleCharacter *pChara)
{
	return crbatLoadExtCharacter(pChara,16,8);
}

//---アイテムアニメーション
CRBATANIME_API int crbatLoadExtCharacter_Item(CrBattleCharacter *pChara)
{
	return crbatLoadExtCharacter(pChara,16,8);
}

//---拡張キャラクターパターンをロード
CRBATANIME_API int crbatLoadExtCharacter(CrBattleCharacter *pChara,int start,int number)
{
	int chara_pos;

	if(!pChara->IsFriend()){// && pChara->GetDrawType() != 0){
		return 1;
	}

	for(chara_pos = 0;chara_pos < BATTLECHARA_MAX;chara_pos ++){
		if(pChara == &pBtChara[chara_pos])
			break;
	}
	if(chara_pos == BATTLECHARA_MAX){
		return 0;
	}

	if(number > BATTLE_EXTCHARASURFACE_MAX){
		number = BATTLE_EXTCHARASURFACE_MAX;
	}

	eiCellSetSurface(
		&BattleCharaCell[chara_pos * BATTLE_CHARAPATTERN + start],
		0,
		BATTLE_EXTCHARASURFACE,
		32,32,number);

	return 1;
}

CRBATANIME_API void crbatSetCharaMoving(void)
{
}

void crbatAnime_EfectLiner_CallBack(eiCell *pCell)
{
}

//---ぐるぐるっと・・・
CRBATANIME_API void crbatAnime_EfectLiner(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo)
{
	int a,RunTime = 500,StartTime,NowTime = 0,count = 8;
	ei_u32 Color = RGBA_MAKE(255,255,255,127);
	float r = 0.50f,height = 3.0f,
		bwidth = 0.0030f/*0.075f*/,twidth, 
		angle,
		bx,by,tx,ty;
	float VAngle[32] /*= ANGLE(60)*/,SideAngle = ANGLE(80);

	D3DVECTOR vNormal( D3DVAL(0.0f), D3DVAL(1.0f), D3DVAL(0.0f) );
	D3DVECTOR vNormal2( D3DVAL(0.0f), D3DVAL(-1.0f), D3DVAL(0.0f) );

	D3DVERTEX EfectBox[4 * 16];

	eiD3DMaterial material;

	material.Create();
	material.SetDeffuseColor(255,255,255,96);

	eiD3DMatrix matWorld;
	{
		//---ワールド行列初期化
		matWorld.IdentityMatrix();
		matWorld.Set(3,0,(float)pChara->GetFieldX());
		matWorld.Set(3,1,0.0f);
		matWorld.Set(3,2,(float)pChara->GetFieldY());
	}

	StartTime = et->GetTime();

	for(a = 0;a < count;a ++){
		VAngle[a] = ANGLE(60);// + eiRnd(16) - 8);
	}

	while(NowTime < RunTime){
		material.SetDeffuseColor(255,255,255,160 - (int)(160.0f * ((float)NowTime / RunTime)));
		//---共通変数
//		r = (float)(0.10f + ((float)NowTime / 500));
		r = 0.01f;
//		bwidth = (float)(0.075f + ((float)NowTime / 5000));

		height = 0.5f + (float)NowTime / 50.0f;
//		twidth = (float)(bwidth + height * 0.03f);
		twidth = bwidth;

		//---頂点初期化
		for(a = 0,angle = 0.0f + ANGLE(NowTime / 10);a < count;a ++,angle += (ANGLE(360 / count))){
			//---底辺
			bx = (float)(r * cos(angle));
			by = (float)(r * sin(angle));
			//---頂点
			tx = (float)((r + height * cos(VAngle[a])) * cos(angle));
			ty = (float)((r + height * cos(VAngle[a])) * sin(angle));

			D3DVECTOR p1(
				D3DVAL(bx + bwidth * cos(angle - ANGLE(90))),
				D3DVAL(0.0f),
				D3DVAL(by + bwidth * sin(angle - ANGLE(90)))
			);
			D3DVECTOR p2(
				D3DVAL(bx + bwidth * cos(angle + ANGLE(90))),
				D3DVAL(0.0f),
				D3DVAL(by + bwidth * sin(angle + ANGLE(90)))
			);

			D3DVECTOR p3(
				D3DVAL(tx + twidth * cos(angle - ANGLE(90))),
				D3DVAL(height * sin(VAngle[a])),
				D3DVAL(ty + twidth * sin(angle - ANGLE(90)))
			);
			D3DVECTOR p4(
				D3DVAL(tx + twidth * cos(angle + ANGLE(90))),
				D3DVAL(height * sin(VAngle[a])),
				D3DVAL(ty + twidth * sin(angle + ANGLE(90)))
			);

			EfectBox[a * 4 + 0] = D3DVERTEX( p1, vNormal,D3DVAL(0.0f),D3DVAL(0.0f));
			EfectBox[a * 4 + 1] = D3DVERTEX( p2, vNormal,D3DVAL(1.0f),D3DVAL(0.0f));
			EfectBox[a * 4 + 2] = D3DVERTEX( p3, vNormal,D3DVAL(0.0f),D3DVAL(1.0f));
			EfectBox[a * 4 + 3] = D3DVERTEX( p4, vNormal,D3DVAL(1.0f),D3DVAL(1.0f));
		}

		crbatClearDrawingList();
		crbatAddDrawingListAll();

crdataEnableRec(0);
		crbatDrawScene();
		if(eid3d->Begin()){
			crbatDraw_SetViewport(0);
			crbatDraw_SetMatrix(0);

			eid3d->SetTexture(NULL);
			eid3d->SetMaterial(&material);
			eid3d->SetTransformWorld(&matWorld);
			eid3d->SetAmbientLight(RGBA_MAKE(255,255,255,255));
			eid3d->BeginAlphaBlend();

			eid3d->SetDrawMode(EID3D_DRAWMODE_CULLNONE);

			//---描画モード設定
			if(crdataGetIniFile()->Battle3DUseFilling){
				eid3d->SetDrawMode(EID3D_DRAWMODE_FILL);
			} else {
				eid3d->SetDrawMode(EID3D_DRAWMODE_LINE);
				eid3d->SetTexture(NULL);
			}
			eid3d->lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_ONE);
			eid3d->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,D3DFVF_VERTEX,
				&EfectBox[0], 4 * count,0);

			eid3d->EndAlphaBlend();
			eid3d->End();
		}
crdataEnableRec(1);

		crbatDrawRefresh();

		NowTime = et->GetTime() - StartTime;
	}

	material.Release();
}

//---フラッシュ
CRBATANIME_API void crbatAnime_Flash(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,
			int RunTime,int r,int g,int b)
{
	eiTime let;
	int a,StartTime,NowTime = 0;
	ei_u32 Color = RGBA_MAKE(r,g,b,255);
	int alpha;

	D3DTLVERTEX ver[4];
	RECT rect = BattleViewRect[BattleViewMode][0];
	rect.right += rect.left;
	rect.bottom += rect.top;

	memset(&ver[0],0,sizeof(ver));
	ver[0].sx = ver[2].sx = (float)(rect.left);
	ver[0].sy = ver[1].sy = (float)(rect.top);
	ver[1].sx = ver[3].sx = (float)(rect.right);
	ver[2].sy = ver[3].sy = (float)(rect.bottom);

	let.Reset();
	StartTime = let.Get();

	while(NowTime < RunTime){
		crbatClearDrawingList();
		crbatAddDrawingListAll();

crdataEnableRec(0);
		crbatDrawScene();

		alpha = (int)((float)(RunTime - NowTime) / (float)RunTime * 255.0);
		for(a = 0;a < 4;a ++){
			ver[a].dcColor = RGBA_MAKE(r,g,b,alpha);
			ver[a].rhw = 1;
		}
		if(eid3d->Begin()){
			eid3d->BeginAlphaBlend();

			eid3d->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,D3DFVF_TLVERTEX,
				&ver[0],4,0);

			eid3d->EndAlphaBlend();
			eid3d->End();
		}
crdataEnableRec(1);

		crbatDrawRefresh();

		NowTime = let.Get();
	}
}

//---アニメーションパターンをロード
CRBATANIME_API int crbatLoadAnime(int number)
{
	char name[100];

//	if(PreviousAnimeNumber == number)
//		return 1;

	sprintf(&name[0],"%sanime%03d.bmp",CR_DATADIR4,number);

	int c = eiCellReadPattern(
		&BattleAnimeCell[0],
		name,CR_DATAFILE4,crdataGetFileMode(),
		0,AnimePatternCount[number],
		AnimePatternSize[number],AnimePatternSize[number]);
	eiCellSetSurface(
		&BattleAnimeCell[0],
		0,BATTLE_ANIMESURFACE,
		AnimePatternSize[number],AnimePatternSize[number],
		AnimePatternCount[number]);

	//---アニメーションナンバーを記憶
	PreviousAnimeNumber = number;

	return 1;
}

//---解放
CRBATANIME_API int crbatReleaseAnime(void)
{
	int a;

	for(a = 0;a < ANIMEPATTERN_1;a ++){
		BattleAnimeCell[a].Release();
	}

	return 1;
}

#include "CrBattle_AnimeSubWeapon.cpp"
#include "CrBattle_AnimeSubMagic.cpp"
#include "CrBattle_AnimeSubDefense.cpp"
#include "CrBattle_AnimeSubItem.cpp"
#include "CrBattle_AnimeSubSpecial.cpp"
