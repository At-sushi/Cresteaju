/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBattle_Draw.cpp ...Battle Drawing functions

-----------------------------------------------------------*/

#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBATTLE_DRAW

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#define EXTERN_CRBATTLE
#include "..\CrBase.h"
#include "..\CrBattle.h"

#define CR_GAMEINFO_EXTERNPOINTER
#include "..\CrGameInfo.h"

static CR_BATTLE_DRAWCHARA DrawingList[BATTLE_DRAWINGLISTMAX],TempList[BATTLE_DRAWINGLISTMAX];
static int ListPointer = 0;

#include "CrBattle_DrawRadar.cpp"
#include "CrBattle_DrawCamera.cpp"
#include "CrBattle_DrawWindow.cpp"
#include "CrBattle_DrawLight.cpp"

CRBATTLEDRAW_API int crbatIsEnableAddAlpha(void)
{
//	return (eiGetDDInfo()->D3DDeviceDesc.dpcTriCaps.dwDestBlendCaps & D3DPBLENDCAPS_ONE);
	return crdataGetIniFile()->EnableAddAlpha;
}

CRBATTLEDRAW_API void crbatSetAddAlpha(void)
{
	if(crbatIsEnableAddAlpha()){
		eid3d->lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_ONE);
//		eid3d->lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND,D3DBLEND_ONE);
	} else {
	}
}

//---高速描画用にコピーする
CRBATTLEDRAW_API void crbatCopyScene(void)
{
//	RECT rect = {0,32,640,256 + 32};
	RECT rect = {0,16,640,256 + 16};
	RECT rect2 = {0,BATTLE_TEMPSURFACE_Y,
		640,256 + BATTLE_TEMPSURFACE_Y};

//	(eiGetSurfacePointer() + 1)->Put((eiGetSurfacePointer() + 2),0,BATTLE_TEMPSURFACE_Y,
//		&rect,DDBLTFAST_WAIT);
	(eiGetSurfacePointer() + 1)->PutExtend2((eiGetSurfacePointer() + 2),
		&rect2,&rect,DDBLT_WAIT);
}

//---高速描画
CRBATTLEDRAW_API void crbatDrawSceneFast(void)
{
	RECT rect = {0,BATTLE_TEMPSURFACE_Y,640,256 + BATTLE_TEMPSURFACE_Y};
	RECT rect2 = {0,16,640,256 + 16};

//	(eiGetSurfacePointer() + 2)->Put((eiGetSurfacePointer() + 1),0,16,
//		&rect,DDBLTFAST_WAIT);
	(eiGetSurfacePointer() + 2)->PutExtend2((eiGetSurfacePointer() + 1),
		&rect2,&rect,DDBLT_WAIT);
}

//---ビューポートをセット
CRBATTLEDRAW_API void crbatDraw_SetViewport(int number)
{
	static RECT rect;
	
	rect = BattleViewRect[BattleViewMode][number];

	pViewport->SetRect((D3DRECT *)&rect);

//	pViewport->SetRect(0,0,256,256);
	pViewport->Set();

	rect.right += rect.left;
	rect.bottom += rect.top;
	ew->lpCell[1]->SetClipingRect(&rect);
}

//---画面クリア
CRBATTLEDRAW_API void crbatDraw_Clear(void)
{
	//---
	if(BattleViewMode != BATTLE_VIEWMODE_HALF)
		pViewport->SetRect(32,16,640 - 64,256);
	else
		pViewport->SetRect(32 + (16 * 12) + 32,32,
						BattleViewRect[BATTLE_VIEWMODE_HALF][0].right,256);

	pViewport->SetRect(32,16,640 - 64,256);

	pViewport->Set();
	//---Ｚバッファークリア
	pViewport->ClearZBuffer();
	//---バックグラウンドクリア
	pViewport->ClearBackground();
}

CRBATTLEDRAW_API void crbatDraw_ClearMenuArea(void)
{
	ew->lpCell[1]->DrawFillBox(0,256 + 32,639,479,ep->ToRGB(CRCOLOR_BLACK));
}

CRBATTLEDRAW_API void crbatDraw_CopyScreen(void)
{
	ew->Refresh();
}

//---ワールド行列を微妙にずらす
float WorldMatrixDeltaX,WorldMatrixDeltaY,WorldMatrixDeltaZ;

CRBATTLEDRAW_API void crbatDraw_SetWorldMatrixDelta(float x,float y,float z)
{
	WorldMatrixDeltaX = x;
	WorldMatrixDeltaY = y;
	WorldMatrixDeltaZ = z;
}

//---行列セット
static eiD3DMatrix matWorld,matProjection;

CRBATTLEDRAW_API void crbatDraw_SetMatrix(int number)
{
	//---ワールド行列初期化
	matWorld.IdentityMatrix();
	matWorld.Set(3,0,0.0f);
	matWorld.Set(3,1,0.0f);
	matWorld.Set(3,2,0.0f);
	if(WorldMatrixDeltaX != 0
		|| WorldMatrixDeltaY != 0
		|| WorldMatrixDeltaZ != 0){
		matWorld.Move(WorldMatrixDeltaX,WorldMatrixDeltaY,WorldMatrixDeltaZ);
	}

	eid3d->SetTransformWorld(&matWorld);

	//---ビュー行列設定
	eid3d->SetTransformView(&BattleView[number].matCamera);

	//---プロジェクション行列設定
//	matProjection.CalcProjectionMatrix(0.5f,40.0f,3.14f / HViewNumber);
	matProjection.CalcProjectionMatrix(0.5f,40.0f,3.14f / HViewNumber[BattleViewMode]);
	eid3d->SetTransformProjection(&matProjection);
}

//---フィールドを描く！
CRBATTLEDRAW_API void crbatDraw_DrawField(void)
{
	int x,y;

	//---BG
	BattleBackgroundCell[0].PutClip(
		ew->lpCell[1],
		32,//ew->lpCell[1]->Data.rectSurface.left,
		16);//ew->lpCell[1]->Data.rectSurface.top);

/*	int offset_x = 0;
	
	offset_x = (int)(BattleView[0].Angle / (PI * 2) * 160);

//	offset_x = 0;
	RECT rect = {offset_x * 2,0,(320 + offset_x) * 2,128 * 2};
	BattleBackgroundCell[0].PutExtend(
		ew->lpCell[1],
		32,16,2.00,2.00,EI_PSET,&rect);
*/

	if(eid3d->Begin()){

		if(crdataGetIniFile()->AlphaBattleField){
			eid3d->BeginAlphaBlend();
		}
		eid3d->SetMaterial(&BattleFieldMaterial);

		//---フィールドを描く
		for(y = 0;y < BATTLEFIELD_VERTEXCOUNT_Y;y ++){
			for(x = 0;x < BATTLEFIELD_VERTEXCOUNT_X;x ++){
				if(crdataGetIniFile()->Battle3DUseFilling){
					if(crdataGetIniFile()->Battle3DUseTexture){
						eid3d->SetTexture(&BattleFieldCell[BattleField[x][y].TextureNumber]);
					} else {
						eid3d->SetTexture(NULL);
					}
				}

				if(eid3d->DrawPrimitive(
					D3DPT_TRIANGLESTRIP,D3DFVF_VERTEX,
					&BattleField[x][y].Vertex[0], 4,0/*D3DDP_WAIT*/) != D3D_OK){
				}
			}
		}
		if(crdataGetIniFile()->AlphaBattleField){
			eid3d->EndAlphaBlend();
		}
		eid3d->SetMaterial(NULL);
		eid3d->SetTexture(NULL);
		eid3d->End();
	}
}

int crbatCallbackQsort(const void *pData1,const void *pData2)
{
	CR_BATTLE_DRAWCHARA *pList1 = (CR_BATTLE_DRAWCHARA *)pData1,
		*pList2 = (CR_BATTLE_DRAWCHARA *)pData2;

	if(pList2->MustBeFront)
		return -1;
	if(pList1->MustBeFront)
		return 1;

	if(pList1->cz < pList2->cz)
		return 1;
	if(pList2->cz < pList1->cz)
		return -1;
	return 0;
}

//---キャラクターを描く
CRBATTLEDRAW_API void crbatDraw_DrawCharacter(int number)
{
	int a,index,ptn;
	float px,py,pz,rate;

	//---頂点バッファーをロックしてデータ書き込み
	{
		D3DVERTEX *pVer = (D3DVERTEX *)vbSrc.Lock();
		if(!pVer)
			return;

		for(a = 0,index = 0;a < ListPointer;a ++){
			//---キャラクター座標を３Ｄ（ポリゴン）座標に変換
			if(DrawingList[a].Flag){
				//---リストにキャラクターがセットされていれば
				crbatTranslatePos(DrawingList[a].cx,DrawingList[a].cy,DrawingList[a].cz,&px,&py,&pz);
				pVer[index] = D3DVERTEX( D3DVECTOR(px,pz,py), D3DVECTOR(0.0f,0.0f,0.0f),D3DVAL(0.0f),D3DVAL(0.0f));
				index ++;
			}
		}
		vbSrc.Unlock();
	}

	//---座標変換
	vbSrc.Process(&vbDest,index);
	//---ソート
	{
		memcpy(&TempList[0],&DrawingList[0],sizeof(TempList));
		D3DTLVERTEX *pDstVer = (D3DTLVERTEX *)vbDest.Lock();
		for(a = 0;a < index;a ++){
			TempList[a].cx = pDstVer[a].sx;
			TempList[a].cy = pDstVer[a].sy;
			TempList[a].cz = pDstVer[a].sz;
		}
		vbDest.Unlock();

		qsort(&TempList[0],index,sizeof(CR_BATTLE_DRAWCHARA),crbatCallbackQsort);
	}

	//---描く
	{
/*		static CrBattleCharacter TempChara;
		TempChara.SetFieldPos(BATTLEFIELD_MAX_X,BATTLEFIELD_MAX_Y,0);
		//画面中心ではなくて、現在表示している中心に向かって
		float delta;
		float
			dx = (float)(BattleView[number].dx - BattleView[number].cx),
			dy = (float)(BattleView[number].dy - BattleView[number].cy);
		float dis = (float)sqrt(dx * dx + dy * dy);
		if(dis != 0)
			delta = (BattleView[number].dz - BattleView[number].cz) / dis;
		else
			delta = 0;*/

/*		TempChara.SetFieldPos(
			(int)(BattleView[number].dx + (BattleView[number].cx - BattleView[number].dx) / 2 + 0.5),
			(int)(BattleView[number].dy + (BattleView[number].cy - BattleView[number].dy) / 2 + 0.5),
			0);
*/
		//---影を描く
		if(crdataGetIniFile()->BattleShadow){
			D3DVERTEX ver[4];
			eiD3DMaterial mat;

			mat.Create();
			mat.SetDeffuseColor(255,255,255,128);
			mat.SetEmissiveColor(255,255,255,128);
			mat.SetAmbientColor(255,255,255,128);

			memset(ver,0,sizeof(ver));
			if(eid3d->Begin()){
				eid3d->BeginAlphaBlend();
				eid3d->SetMaterial(&mat);
				eid3d->SetTexture(&ShadowCell);
				eid3d->SetTextureColorkey(1);
				float shadow = 0.2f,ag_x = 0 , ag_y = 0;
				for(a = 0;a < index;a ++){
					if(TempList[a].CannotDraw)
						continue;
					if(TempList[a].pObjectInfo != NULL)
						continue;

					pz = TempList[a].cz;
					if(!(pz > TempList[a].Limit && TempList[a].DrawMode == 0)){
						//---描く範囲内にないなら
						continue;
					}

					if(TempList[a].pCell->Data.xSize < 200){
						shadow = (float)TempList[a].pCell->Data.xSize / 32.0f / 5.0f;
					} else {
						shadow = (float)TempList[a].pCell->Data.xSize / 32.0f / 7.5f;
					}

					ver[0].x = -shadow + TempList[a].src_x + ag_x;
					ver[0].y = 0.001f;
					ver[0].z = -shadow + TempList[a].src_y + ag_y;
					ver[0].nx = 0;
					ver[0].ny = 1.0;
					ver[0].nz = 0;
					ver[0].tu = 0;
					ver[0].tv = 0;

					ver[1].x = shadow + TempList[a].src_x + ag_x;
					ver[1].y = 0.001f;
					ver[1].z = -shadow + TempList[a].src_y + ag_y;
					ver[1].nx = 0;
					ver[1].ny = 1.0;
					ver[1].nz = 0;
					ver[1].tu = 1;
					ver[1].tv = 0;

					ver[2].x = -shadow + TempList[a].src_x + ag_x;
					ver[2].y = 0.001f;
					ver[2].z = shadow + TempList[a].src_y + ag_y;
					ver[2].nx = 0;
					ver[2].ny = 1.0;
					ver[2].nz = 0;
					ver[2].tu = 0;
					ver[2].tv = 1;

					ver[3].x = shadow + TempList[a].src_x + ag_x;
					ver[3].y = 0.001f;
					ver[3].z = shadow + TempList[a].src_y + ag_y;
					ver[3].nx = 0;
					ver[3].ny = 1.0;
					ver[3].nz = 0;
					ver[3].tu = 1;
					ver[3].tv = 1;

					eid3d->DrawPrimitive(
						D3DPT_TRIANGLESTRIP,D3DFVF_VERTEX,
						&ver[0], 4,0);
				}
				eid3d->SetMaterial(NULL);
				eid3d->SetTextureColorkey(0);
				eid3d->SetTexture(NULL);
				eid3d->EndAlphaBlend();
				eid3d->End();
			}
		}
		//---
		for(a = 0;a < index;a ++){
			if(TempList[a].CannotDraw)
				continue;

			px = TempList[a].cx;
			py = TempList[a].cy;
			pz = TempList[a].cz;
			rate = (float)((1.0 - pz) * (BATTLE_ZDEPTH));//---係数をかける

			rate = rate / ((float)(640 - 64) / (float)BattleViewRect[0/*BattleViewMode*/][0/*number*/].right);
			rate = rate / 32.0f;

			ptn = 0;
			if(TempList[a].PatternMode == DRAWTYPE_4){
				float angle = BattleView[number].Angle
					- ((CrBattleCharacter *)TempList[a].pData)->GetAngle();
//				float angle = BattleView[number].Angle
//					- ((CrBattleCharacter *)TempList[a].pData)->GetCharaAngle(&TempChara);
				CALC_ANGLE(angle);
//				float angle;
//				angle = crbatGetCameraAngle(BattleView[number].c
//				angle =
//					((CrBattleCharacter *)TempList[a].pData)->GetAngle()
//					- (BattleView[number].Angle + ANGLE(90));

				if(ANGLE(-45) <= angle && angle <= ANGLE(45)){
					ptn = 1;
				} else if(ANGLE(45) <= angle && angle <= ANGLE(135)){
					ptn = 2;
				} else if(ANGLE(135) <= angle && angle <= ANGLE(225)){
					ptn = 0;
				} else if(ANGLE(225) <= angle && angle <= ANGLE(315)){
					ptn = 3;
				} else {
					ptn = 1;
				}
//				if(a == 0){
//					char s[80];
//					sprintf(s,"%f , %f,  %f",BattleView[0].Angle,angle,((CrBattleCharacter *)TempList[a].pData)->GetAngle());
//					SetWindowText(ew->hwnd,s);
//				}
			} else if(TempList[a].PatternMode == DRAWTYPE_2){
				float angle = BattleView[number].Angle
					- ((CrBattleCharacter *)TempList[a].pData)->GetAngle();
//				float angle = BattleView[number].Angle
//					- ((CrBattleCharacter *)TempList[a].pData)->GetCharaAngle(&TempChara);
				CALC_ANGLE(angle);
				if(ANGLE(-45) <= angle && angle <= ANGLE(45)){
					ptn = 2;
				} else if(ANGLE(45) <= angle && angle <= ANGLE(135)){
					ptn = 2;
				} else if(ANGLE(135) <= angle && angle <= ANGLE(225)){
					ptn = 3;
				} else if(ANGLE(225) <= angle && angle <= ANGLE(315)){
					ptn = 3;
				} else {
					ptn = 2;
				}
			}

			//---最後に描いたセル
			if(TempList[a].Type == 0){
				((CrBattleCharacter *)TempList[a].pData)->OnlyInfo.pDrawCell = &TempList[a].pCell[ptn];
			}

			if(pz > TempList[a].Limit && TempList[a].DrawMode == 0){
				//---描く範囲内にあれば
				TempList[a].pCell[ptn].PutExtend( ew->lpCell[1],
					(int)(px - (float)TempList[a].pCell[ptn].Data.xSize * (float)rate * 0.50f),
					(int)(py - (float)TempList[a].pCell[ptn].Data.ySize * (float)rate),rate,rate,EI_TRANS);

				if(TempList[a].pAfterDraw){
					//---その後に描くパターンがあれば
					TempList[a].pAfterDraw->pCell[0].PutExtend( ew->lpCell[1],
						(int)(px - (float)TempList[a].pAfterDraw->pCell[0].Data.xSize * (float)rate * 0.50f),
						(int)(py - (float)TempList[a].pAfterDraw->pCell[0].Data.ySize * (float)rate),rate,rate,EI_TRANS);
				}
			} else if(pz > TempList[a].Limit && TempList[a].DrawMode == 1){
				//---ポリゴン
				if(eid3d->Begin()){
					eid3d->BeginAlphaBlend();
					crbatDraw_SetViewport(0);
					crbatDraw_SetMatrix(0);
					eid3d->SetDrawMode(EID3D_DRAWMODE_FILL);
					eid3d->SetTexture(TempList[a].pObjectInfo->pTex);
					eid3d->SetTextureColorkey(1);

					if(TempList[a].pObjectInfo->AlphaMode == 1){
//						eid3d->lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND,D3DBLEND_ONE);
						crbatSetAddAlpha();
//						eid3d->lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_ONE);
					}

					D3DTLVERTEX ver[4];
					memcpy(&ver[0],&TempList[a].pObjectInfo->tlVertex[0],sizeof(ver));

					ver[0].sx = (px - (float)TempList[a].pObjectInfo->RSize
						* (float)rate * 0.50f * TempList[a].pObjectInfo->XRate);
					ver[0].sy = (py - (float)TempList[a].pObjectInfo->RSize
						* (float)rate * 0.50f * TempList[a].pObjectInfo->YRate);
					ver[1].sx = (px + (float)TempList[a].pObjectInfo->RSize
						* (float)rate * 0.50f * TempList[a].pObjectInfo->XRate);
					ver[1].sy = (py - (float)TempList[a].pObjectInfo->RSize
						* (float)rate * 0.50f * TempList[a].pObjectInfo->YRate);
					ver[2].sx = (px - (float)TempList[a].pObjectInfo->RSize
					* (float)rate * 0.50f * TempList[a].pObjectInfo->XRate);
					ver[2].sy = (py + (float)TempList[a].pObjectInfo->RSize
						* (float)rate * 0.50f * TempList[a].pObjectInfo->YRate);
					ver[3].sx = (px + (float)TempList[a].pObjectInfo->RSize
						* (float)rate * 0.50f * TempList[a].pObjectInfo->XRate);
					ver[3].sy = (py + (float)TempList[a].pObjectInfo->RSize
						* (float)rate * 0.50f * TempList[a].pObjectInfo->YRate);

					eid3d->DrawPrimitive(
						D3DPT_TRIANGLESTRIP,D3DFVF_TLVERTEX,
						&ver[0], 4,0);

					eid3d->SetTextureColorkey(0);
					eid3d->SetTexture(NULL);
					eid3d->EndAlphaBlend();
					eid3d->End();
				}
			}
		}
	}
}

void (*pDrawSceneCallback)(eiCell *,int) = NULL;
void (*pDrawSceneCallback2)(eiCell *,int) = NULL;

CRBATTLEDRAW_API int crbatDrawRefresh(void)
{
	ew->Flip();

//	eiGetSurfacePointer()->WaitVSync();
//	ew->Refresh();

	if(!eiGetFullScreen()){
		eiSleep(1);
	}

	return 0;
}

//---一定時間シーンを描き続ける
CRBATTLEDRAW_API int crbatDrawSceneWhile(int DrawTime)
{
	int StartTime,NowTime;

	StartTime = et->GetTime();

	if(crsysQuick()){
		return 0;
	}

	do {
		NowTime = et->GetTime() - StartTime;
crdataEnableRec(0);
		crbatDrawScene();
crdataEnableRec(1);
		crbatDrawRefresh();
	} while(NowTime <= DrawTime);

	return 0;
}

CRBATTLEDRAW_API int crbatDrawScene(void)
{
	int a,b;

	et->Reset();

	//---画面をクリア
	crbatDraw_Clear();

	if(eid3d->Begin()){
		//---基本設定
		//---ライト計算
		crbatCalcLight();
		eid3d->SetAmbientLight(::BattleLight);//RGBA_MAKE(255,255,255,255));
		eid3d->SetDrawMode(EID3D_DRAWMODE_CULLNONE);

		//---描画モード設定
		if(crdataGetIniFile()->Battle3DUseFilling){
			eid3d->SetDrawMode(EID3D_DRAWMODE_FILL);
		} else {
			eid3d->SetDrawMode(EID3D_DRAWMODE_LINE);
			eid3d->SetTexture(NULL);
		}

		for(a = 0;a < ViewNumber[BattleViewMode];a ++){
			b = 1;
			if(a)
				b = eid3d->Begin();
			if(b){
				//---ビューポート、セルのクリッピングセット
				crbatDraw_SetViewport(a);

				//---行列セット
				crbatDraw_SetMatrix(a);

				//---フィールドを描く
				eid3d->End();//---crbatDraw_DrawField内で２Ｄ書くため一旦終える
			}
			crbatDraw_DrawField();

			if(pDrawSceneCallback2 != NULL){
				(*pDrawSceneCallback2)(ew->lpCell[1],1);
			}

			//---キャラクターを描く
			if(eid3d->Begin(0)){
				eid3d->SetTransformWorld(&::matWorld);
				eid3d->SetTransformView(&BattleView[a].matCamera);
				eid3d->SetTransformProjection(&::matProjection);
				eid3d->End(0);
			}
			crbatDraw_DrawCharacter(a);
		}
	}

	if(pDrawSceneCallback != NULL){
		(*pDrawSceneCallback)(ew->lpCell[1],0);
	}

	//---範囲を元に戻しておく
	pViewport->SetRect(0,0,640,480);
	RECT rect = {0,0,640,480};
	ew->lpCell[1]->SetClipingRect(&rect);

//#ifdef _DEBUG
#if (CR_DEBUG == 1)
	if(eiGetDebugMode()){
/*		if(ei->Input[0].Button[2] && ei->Quick){
			(eiGetSurfacePointer() + 3)->Put(
				(eiGetSurfacePointer() + 1),
				0,0,&rect);
		} else */if(ei->Input[0].Button[2]){
			(eiGetSurfacePointer() + 2)->Put(
				(eiGetSurfacePointer() + 1),
				0,0,&rect);
//			ew->Refresh();
//			return et->Get();


			//---ステータス情報
			ew->lpCell[1]->DrawFillBox(0,0,640,479,0);

			char s[100];
			int b;
			for(a = 0 + (ei->Quick ? 5: 0),b = 0;a < 5 + (ei->Quick ? 5 : 0);a ++,b ++){
				if(!pBtChara[a].DoExist())
					continue;
//BTST_DIST
				ew->lpCell[1]->DrawText(pBtChara[a].GetName(),0,b * 96,ep->ToTextRGB(CRCOLOR_WHITE));
				sprintf(s,"ds:%2d/%2d  ,pr:%2d/%2d  ,pw:%2d/%2d ,"
					"fs:%2d/%2d  ,ex:%2d/%2d ,"
					"ac:%2d/%2d  ,sl:%2d/%2d",
//					pBtChara[a].GetName(),
					pBtChara[a].GetBtStatusContinue(BTST_DIST),
					pBtChara[a].GetBtStatusContinueMax(BTST_DIST),
					pBtChara[a].GetBtStatusContinue(BTST_PROTECT),
					pBtChara[a].GetBtStatusContinueMax(BTST_PROTECT),
					pBtChara[a].GetBtStatusContinue(BTST_POWER),
					pBtChara[a].GetBtStatusContinueMax(BTST_POWER),
					pBtChara[a].GetBtStatusContinue(BTST_FSHIELD),
					pBtChara[a].GetBtStatusContinueMax(BTST_FSHIELD),
					pBtChara[a].GetBtStatusContinue(BTST_EXTEND),
					pBtChara[a].GetBtStatusContinueMax(BTST_EXTEND),
					pBtChara[a].GetBtStatusContinue(BTST_ACCEL),
					pBtChara[a].GetBtStatusContinueMax(BTST_ACCEL),
					pBtChara[a].GetBtStatusContinue(BTST_SOUL),
					pBtChara[a].GetBtStatusContinueMax(BTST_SOUL)
					);

				ew->lpCell[1]->DrawText(s,0,b * 96 + 16,ep->ToTextRGB(CRCOLOR_WHITE));

				//---
				sprintf(s,"           dk:%2d/%2d  ,if:%2d/%2d ,"
					"zr:%2d/%2d ",
					pBtChara[a].GetBtStatusContinue(BTST_KURAYAMI),
					pBtChara[a].GetBtStatusContinueMax(BTST_KURAYAMI),
					pBtChara[a].GetBtStatusContinue(BTST_JAKUKA),
					pBtChara[a].GetBtStatusContinueMax(BTST_JAKUKA),
					pBtChara[a].GetBtStatusContinue(BTST_ZERO),
					pBtChara[a].GetBtStatusContinueMax(BTST_ZERO)
					);

				ew->lpCell[1]->DrawText(s,0,b * 96 + 32,ep->ToTextRGB(CRCOLOR_RED));
				//---
				sprintf(s,"   %s %s %s %s %s %s %s %s %s %s %s %s"
					" %s %s %s %s %s %s %s %s %s %s ",
					pBtChara[a].Ability(BTAB_P_DOKU) ? "＋毒":"",
					pBtChara[a].Ability(BTAB_P_NEMURI) ? "＋眠":"",
					pBtChara[a].Ability(BTAB_P_KURAYAMI) ? "＋闇":"",
					pBtChara[a].Ability(BTAB_P_CHINMOKU) ? "＋沈":"",
					pBtChara[a].Ability(BTAB_P_KONRAN) ? "＋混":"",
					pBtChara[a].Ability(BTAB_P_MAHI) ? "＋痺":"",

					pBtChara[a].Ability(BTAB_P_SOKUSHI) ? "＋死":"",
					pBtChara[a].Ability(BTAB_P_HENKA_23) ? "＋変2/3":"",
					pBtChara[a].Ability(BTAB_P_HENKA_12) ? "＋変1/2":"",
					pBtChara[a].Ability(BTAB_P_HENKA_14) ? "＋変1/4":"",
					pBtChara[a].Ability(BTAB_P_HENKA) ? "＋変":"",
					pBtChara[a].Ability(BTAB_P_BUTURIKOUGEKI) ? "＋物":"",

					pBtChara[a].Ability(BTAB_P_KAIFUKU1) ? "＋回1":"",
					pBtChara[a].Ability(BTAB_P_KAIFUKU2) ? "＋回2":"",
					pBtChara[a].Ability(BTAB_P_MC1) ? "＋MC1":"",
					pBtChara[a].Ability(BTAB_P_MC2) ? "＋MC2":"",
					pBtChara[a].Ability(BTAB_P_JIZOKU1) ? "＋持1":"",
					pBtChara[a].Ability(BTAB_P_JIZOKU2) ? "＋持2":"",

					pBtChara[a].Ability(BTAB_P_BREATH45) ? "＋息4/5":"",
					pBtChara[a].Ability(BTAB_P_BREATH23) ? "＋息2/3":"",
					pBtChara[a].Ability(BTAB_P_BREATH12) ? "＋息1/2":"",
					pBtChara[a].Ability(BTAB_P_SUBETE) ? "＋全":""
					);

				ew->lpCell[1]->DrawText(s,0,b * 96 + 48,ep->ToTextRGB(CRCOLOR_GREEN));

				//---
				sprintf(s,"   %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
					" %s %s %s %s %s %s %s %s %s %s %s",
					pBtChara[a].Ability(BTAB_S_HOJOMAHO) ? "補":"",
					pBtChara[a].Ability(BTAB_S_SAISEI1) ? "再1":"",
					pBtChara[a].Ability(BTAB_S_SAISEI2) ? "再2":"",
					pBtChara[a].Ability(BTAB_S_BARRIER5) ? "B5":"",
					pBtChara[a].Ability(BTAB_S_BARRIER10) ? "B10":"",
					pBtChara[a].Ability(BTAB_S_BARRIER25) ? "B25":"",
					pBtChara[a].Ability(BTAB_S_BARRIER50) ? "B50":"",
					pBtChara[a].Ability(BTAB_S_BARRIER100) ? "B100":"",
					pBtChara[a].Ability(BTAB_S_BARRIER200) ? "B200":"",
					pBtChara[a].Ability(BTAB_S_BARRIER2000) ? "B2000":"",

					pBtChara[a].Ability(BTAB_S_COUNTER25) ? "Ct25":"",
					pBtChara[a].Ability(BTAB_S_COUNTER50) ? "Ct50":"",
					pBtChara[a].Ability(BTAB_S_COUNTER75) ? "Ct75":"",
					pBtChara[a].Ability(BTAB_S_COUNTER100) ? "Ct100":"",
					pBtChara[a].Ability(BTAB_S_ATKDOKU) ? "At毒":"",

					pBtChara[a].Ability(BTAB_S_ATKNEMURI) ? "At眠り":"",
					pBtChara[a].Ability(BTAB_S_ATKMAHI) ? "At痺":"",
					pBtChara[a].Ability(BTAB_S_ATKKONRAN) ? "A混":"",
					pBtChara[a].Ability(BTAB_S_AUTOGARD) ? "AtGd":"",
					pBtChara[a].Ability(BTAB_S_CRITICAL1) ? "Cr1":"",
					pBtChara[a].Ability(BTAB_S_CRITICAL2) ? "Cr2":"",

					pBtChara[a].Ability(BTAB_S_CRITICAL3) ? "Cr3":"",
					pBtChara[a].Ability(BTAB_S_KAIFUKUMAGIC_P) ? "回P":"",
					pBtChara[a].Ability(BTAB_S_KAIFUKUMAGIC_M) ? "回M":"",
					pBtChara[a].Ability(BTAB_S_FIRSTATACK) ? "FsAtk":"",
					pBtChara[a].Ability(BTAB_S_FIRSTESTATACK) ? "FsTAtk":"",

					pBtChara[a].Ability(BTAB_S_ANMIN) ? "安眠":""
					);

				ew->lpCell[1]->DrawText(s,0,b * 96 + 64,ep->ToTextRGB(CRCOLOR_GREEN));
				//---
				sprintf(s,"   %d %s %s %s %s %s %s",
					pBtChara[a].GetLP(),
					pBtChara[a].Ability(BTAB_M_HENKA) ? "－変":"",
					pBtChara[a].Ability(BTAB_M_MC) ? "－MC":"",
					pBtChara[a].Ability(BTAB_M_KAIFUKU) ? "－回":"",
					pBtChara[a].Ability(BTAB_M_JIZOKU) ? "－持":"",
					pBtChara[a].Ability(BTAB_M_SUBETE) ? "－全":"",
					pBtChara[a].Ability(BTAB_M_BOSS) ? "－ボ":""
					);

				ew->lpCell[1]->DrawText(s,0,b * 96 + 80,ep->ToTextRGB(CRCOLOR_GREEN));
			}
/*			if(ei->Input[0].Button[2] && ei->Quick){
				(eiGetSurfacePointer() + 4)->Put(
					(eiGetSurfacePointer() + 1),
					0,0,&rect);
			} else if(ei->Input[0].Button[2]){
				(eiGetSurfacePointer() + 3)->Put(
					(eiGetSurfacePointer() + 1),
					0,0,&rect);
			}*/
			ew->Refresh();
		}
	}
#endif /*(CR_DEBUG == 1)*/
//#endif /*_DEBUG*/

	return et->Get();
}

//---コールバックをセット
CRBATTLEDRAW_API void crbatSetDrawSceneCallback(void(*pFunc)(eiCell *,int))
{
	pDrawSceneCallback = pFunc;
}

//---コールバックをセット
CRBATTLEDRAW_API void crbatSetDrawSceneCallback2(void(*pFunc)(eiCell *,int))
{
	pDrawSceneCallback2 = pFunc;
}

//-----------------------------------------------
static float ZClip = 0.60f;

//---Ｚクリッピング
CRBATTLEDRAW_API float crbatSetDrawingZClip(float z)
{
	float old = ZClip;

	ZClip = z;

	return old;
}

CRBATTLEDRAW_API float crbatGetDrawingZClip(void)
{
	return ZClip;
}

//---描画リストをクリア
CRBATTLEDRAW_API void crbatClearDrawingList(void)
{
	memset(&DrawingList[0],0,sizeof(DrawingList));
	ListPointer = 0;
}

CRBATTLEDRAW_API void crbatAddDrawingListFriend(int view /*= -1*/)
{
	for(int a = 0;a < BATTLECHARA_PARTY_MAX;a ++){
		if(pBtChara[a].DoExist()){
			crbatAddDrawingList(&pBtChara[a]);
		}
	}
}

CRBATTLEDRAW_API void crbatAddDrawingListEnemy(int view /*= -1*/)
{
	for(int a = CHARA_ENEMY;a < CHARA_ENEMY + BATTLE_ENEMYMAX;a ++){
		if(pBtChara[a].DoExist()){
			crbatAddDrawingList(&pBtChara[a]);
		}
	}
}

//---
CRBATTLEDRAW_API void crbatAddDrawingListAll(int view /*= -1*/)
{
	crbatAddDrawingListFriend(view);
	crbatAddDrawingListEnemy(view);
}

//---リストに追加
CRBATTLEDRAW_API void crbatAddDrawingList(CrBattleCharacter *pChara,int view /*= -1*/,int front /*= 0*/)
{
	int a;

	if(pChara->DontShow() == 1)
		return;

	DrawingList[ListPointer].Flag = 1;
	DrawingList[ListPointer].Type = 0;
	DrawingList[ListPointer].ViewNumber = view;
	DrawingList[ListPointer].MustBeFront = front;
	DrawingList[ListPointer].DrawMode = 0;

	if(pChara->IsAnime()){
		//---アニメーション中だったら
		DrawingList[ListPointer].cx = (float)pChara->GetAnimeX();
		DrawingList[ListPointer].cy = (float)pChara->GetAnimeY();
		DrawingList[ListPointer].cz = (float)pChara->GetAnimeZ();
		DrawingList[ListPointer].src_x = (float)pChara->GetAnimeX();
		DrawingList[ListPointer].src_y = (float)pChara->GetAnimeY();
		DrawingList[ListPointer].src_z = (float)pChara->GetAnimeZ();
	} else {
		DrawingList[ListPointer].cx = (float)pChara->GetFieldX();
		DrawingList[ListPointer].cy = (float)pChara->GetFieldY();
		DrawingList[ListPointer].cz = (float)pChara->GetFieldZ();
		DrawingList[ListPointer].src_x = (float)pChara->GetFieldX();
		DrawingList[ListPointer].src_y = (float)pChara->GetFieldY();
		DrawingList[ListPointer].src_z = (float)pChara->GetFieldZ();
	}
	DrawingList[ListPointer].cz += (pChara->GetZOffset());
	DrawingList[ListPointer].src_z += (pChara->GetZOffset());

	DrawingList[ListPointer].Limit = crbatGetDrawingZClip();//0.60f;//0.50f
	DrawingList[ListPointer].pCell = (pChara->GetCell() + pChara->GetPattern());
	if(pChara->IsFriend()){
//		int ptn = pChara->GetPattern();
		//---角度切り替えパターン
		DrawingList[ListPointer].PatternMode = DRAWTYPE_4;
	} else {
		if(pChara->GetDrawType() == DRAWTYPE_4_ANIME)
			DrawingList[ListPointer].PatternMode = DRAWTYPE_4;
		else
			DrawingList[ListPointer].PatternMode = pChara->GetDrawType();//DRAWTYPE_2;
	}

	DrawingList[ListPointer].pData= (void *)pChara;
	DrawingList[ListPointer].pAfterDraw = NULL;

	DrawingList[ListPointer].XRate = DrawingList[ListPointer].YRate = 1.0f;

	ListPointer ++;

	if(!pChara->IsAnime()){
		//---アニメーション中でなければ状態表示
		int x = 1;
		float y = (float)pChara->GetCharaHeight() / 48.0f;
		for(a = 0;a < 8;a ++){
			if(pChara->GetBtStatus() & (1 << a)){
				pChara->StatusObject[a].SetPos(
					(float)((float)pChara->GetFieldX() + ((float)x * 0.25)),
					(float)((float)pChara->GetFieldY()),
					(float)((float)pChara->GetFieldZ() + y));
				pChara->StatusObject[a].SetPattern(0);
				pChara->StatusObject[a].SetCell(&BattleStatusCell[a]);
				crbatAddDrawingList(&pChara->StatusObject[a]);
				y += 0.25;
				if(x == 1)
					x = -1;
				else
					x = 0;
			}
		}
		return;
	}
}

CRBATTLEDRAW_API void crbatAddDrawingList(CrBattleObject *pObject,int view /*= -1*/,
					int front /*= 0*/,CrBattleCharacter *pChara /*= NULL*/)
{
	DrawingList[ListPointer].Flag = 1;
	DrawingList[ListPointer].Type = 1;
	DrawingList[ListPointer].ViewNumber = view;
	DrawingList[ListPointer].MustBeFront = front;
	DrawingList[ListPointer].DrawMode = pObject->ObjectInfo.DrawMode;

	DrawingList[ListPointer].cx = pObject->GetX();
	DrawingList[ListPointer].cy = pObject->GetY();
	DrawingList[ListPointer].cz = pObject->GetZ();
	DrawingList[ListPointer].src_x = pObject->GetX();
	DrawingList[ListPointer].src_y = pObject->GetY();
	DrawingList[ListPointer].src_z = pObject->GetZ();
	DrawingList[ListPointer].Limit = 0.60f;
	DrawingList[ListPointer].pCell = (pObject->ObjectInfo.pCell + pObject->GetPattern());
	DrawingList[ListPointer].PatternMode = 0;
	DrawingList[ListPointer].PatternMode = DRAWTYPE_1;
	DrawingList[ListPointer].pAfterDraw = NULL;
	//---特定のキャラクター描画直後に描く
	if(pChara != NULL){
		int a;
		for(a = 0;a < ListPointer;a ++){
			if(DrawingList[a].pData == (void *)pChara){
				DrawingList[a].pAfterDraw = &DrawingList[ListPointer];
			}
		}
		DrawingList[ListPointer].CannotDraw = 1;
	}

	DrawingList[ListPointer].XRate = pObject->ObjectInfo.XRate;
	DrawingList[ListPointer].YRate = pObject->ObjectInfo.YRate;
	DrawingList[ListPointer].pObjectInfo = &pObject->ObjectInfo;

	ListPointer ++;
}

//----------------------------------------------
//---ダメージ表示
CRBATTLEDRAW_API int crbatShowDamage(CR_BATTLE_DAMAGEINFO *pDamageInfo)
{
	int Flag,number;
	float AddWorld = 0.0f;
	int damage,damage_mode,count = 0,obj_count = 0;
	CrBattleCharacter **ppList = &pDamageInfo->pList[0];
	CrBattleDamage Pattern[BATTLECHARA_MAX + 1];
	eiTime let;

	let.Reset();

	if(crsysQuick()){
		//---クイック
		return 1;
	}

	for(count = 0 ,obj_count = 0; pDamageInfo->pList[count] != NULL; count ++){
		if(pDamageInfo->DontShowThisDamage[count]){
			//---ダメージを表示しなければ、とばす
			continue;
		}
		damage_mode = pDamageInfo->DamageMode[count];
		if(damage_mode == 0){
			damage_mode = pDamageInfo->DamageMode[0];
		}

		damage = pDamageInfo->Damage[count];

		Pattern[obj_count].SetCharacter(pDamageInfo->pList[count]);
		Pattern[obj_count].SetDamage(damage,pDamageInfo->Miss[count],damage_mode);
		Pattern[obj_count].SetDelay(count * 50);
		obj_count ++;
	}

	Flag = 0;
	AddWorld = 0.0f;

	if(crsysGetExtentionLevel() < 6){
		//---高速描画ようにコピー
		crbatDrawScene();
		crbatCopyScene();
	}

	if(obj_count == 0){
		//---もし、何も表示しないならもどる
		return 1;
	}

/*	int t = let.Get();
	char s[80];
	sprintf(s,"******%d****\n",t);
	eiDebugWriteFile(s);
*/
	int prev = 0,now = 0;
	let.Reset();
	while(Flag == 0){
		Flag = 1;

		//---シーンを描く
crdataEnableRec(0);
		if(crsysGetExtentionLevel() >= 6){
			crbatDrawScene();
		} else {
			crbatDrawSceneFast();
		}

		for(count = 0 , obj_count = 0; pDamageInfo->pList[count] != NULL; count ++){
			if(pDamageInfo->DontShowThisDamage[count]){
				//---ダメージを表示しなければ、とばす
				continue;
			}
			Flag &= Pattern[obj_count].AddWorld(AddWorld);
			obj_count ++;
		}

		for(number = 0;number < ViewNumber[BattleViewMode];number ++){
			//---ビューポート、セルのクリッピングセット
			crbatDraw_SetViewport(number);
			//---行列セット
			crbatDraw_SetMatrix(number);
			//---ダメージ
			for(count = 0 , obj_count = 0; pDamageInfo->pList[count] ; count ++){
				if(pDamageInfo->DontShowThisDamage[count]){
					//---ダメージを表示しなければ、とばす
					continue;
				}
				Pattern[obj_count].Draw();
				obj_count ++;
			}
		}

crdataEnableRec(1);
		crbatDrawRefresh();
		if(eiGetFullScreen()){
			eiSleep(1);
		}

		now = let.Get();
		AddWorld = (float)now - prev;//(float)let.Get();
		prev = now;
//		if(AddWorld <= 1.0f)
//			AddWorld = 1.0f;
	}

	int l_time = 1000;

	if(crbatGetBattleSpeed() == 1)
			l_time = 100;
	et->Delay2(l_time);

	return 1;
}

//---画面フラッシュ
CRBATTLEDRAW_API void crbatDrawFlash(int r,int g,int b)
{
	int a;

	for(a = 0;a < ViewNumber[BattleViewMode];a ++){
		RECT rect = BattleViewRect[BattleViewMode][a];
		rect.right += rect.left;
		rect.bottom += rect.top;
		ew->lpCell[1]->DrawFillBox(rect.left,rect.top,
			rect.right - 1,rect.bottom - 1,ep->MakeRGB(r,g,g));
	}
}
