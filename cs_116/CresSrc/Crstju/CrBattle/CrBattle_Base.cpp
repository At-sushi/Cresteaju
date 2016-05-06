/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBattle_Base.cpp ...Battle Base functions

-----------------------------------------------------------*/

#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBATTLE_BASE

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#define EXTERN_CRBATTLE
#include "..\CrBase.h"
#include "..\CrBattle.h"

#define CR_GAMEINFO_EXTERNPOINTER
#include "..\CrGameInfo.h"
#include "CrBattle_BaseSubShowStatus.cpp"

//----------------------------------------------------
//----------------------------------------------------
static int BattleSpeed = 0,BattleMagicMode = 0,KizetuMode = 0,BattleItemMode = 0;

CRBATBASE_API int crbatSetBattleItemMode(int mode)
{
	int old = BattleItemMode;

	BattleItemMode = mode;

	return old;
}

CRBATBASE_API int crbatGetBattleItemMode(void)
{
	return BattleItemMode;
}

CRBATBASE_API int crbatSetBattleKizetuMode(int mode)
{
	int old = KizetuMode;

	KizetuMode = mode;

	return old;
}

CRBATBASE_API int crbatGetBattleKizetuMode(void)
{
	return KizetuMode;
}

CRBATBASE_API int crbatSetBattleMagicMode(int mode)
{
	int old = BattleMagicMode;

	BattleMagicMode = mode;

	return old;
}

CRBATBASE_API int crbatGetBattleMagicMode(void)
{
	return BattleMagicMode;
}

//---バトルスピード
CRBATBASE_API int crbatSetBattleSpeed(int speed)
{
	int old = BattleSpeed;

	BattleSpeed = speed;

	return old;
}

CRBATBASE_API int crbatGetBattleSpeed(void)
{
	return BattleSpeed;
}

static CrBattleCharacter SetCharaAngleTempChara;
//---敵味方で向かい合わせる
CRBATBASE_API void crbatSetCharaAngleToRandom(CrBattleCharacter *pChara)
{
	CrBattleCharacter *pDstChara;
	if(pChara->IsFriend()){
		//---味方だったら
		pDstChara = crbatRandomSelect(pChara,BAT_TARGET_ENEMY);
	} else {
		pDstChara = crbatRandomSelect(pChara,BAT_TARGET_FRIEND);
	}

//	SetCharaAngleTempChara.SetFieldPos(BATTLEFIELD_MAX_X / 2,BATTLEFIELD_MAX_Y / 2,0);
	if(pDstChara != NULL){
		pChara->SetAngle(pChara->GetCharaAngle(pDstChara));
	}
}

CRBATBASE_API void crbatSetCharaAngleToRandomAll(void)
{
	int a;
	for(a = 0;a < BATTLECHARA_MAX;a ++){
		if(pBtChara[a].DoExist()){
			crbatSetCharaAngleToRandom(&pBtChara[a]);
		}
	}
}

//---キャラクターをバトルフィールドの中心に向かせる
CRBATBASE_API void crbatSetCharaAngleToCenter(CrBattleCharacter *pChara)
{
	SetCharaAngleTempChara.SetFieldPos(BATTLEFIELD_MAX_X / 2,BATTLEFIELD_MAX_Y / 2,0);
	pChara->SetAngle(pChara->GetCharaAngle(&SetCharaAngleTempChara));
}

CRBATBASE_API void crbatSetCharaAngleToCenterAll(void)
{
	int a;
	for(a = 0;a < BATTLECHARA_MAX;a ++){
		if(pBtChara[a].DoExist()){
			crbatSetCharaAngleToCenter(&pBtChara[a]);
		}
	}
}

CRBATBASE_API int crbatMakeCharaList(CrBattleCharacter **ppList,
				CrBattleCharacter *pSrc,int mode,
				int include_minasLP /*= 0*/)
{
	int a,count,min,max;

	if(mode == BAT_TARGET_FRIEND){
		min = 0;
		max = BATTLECHARA_PARTY_MAX;
	} else if(mode == BAT_TARGET_ENEMY){
		min = BATTLECHARA_STARTENEMY;
		max = min + BATTLE_ENEMYMAX;
	} else {
		min = 0;
		max = BATTLECHARA_STARTENEMY + BATTLE_ENEMYMAX;
	}

	for(a = min,count = 0;a < max;a ++){
		if(pBtChara[a].DoExist()){
			if(include_minasLP == 0
				&& pBtChara[a].IsKizetu()){
				//---気絶を抜かすなら
				continue;
			}
			ppList[count] = &pBtChara[a];
			count ++;
		}
	}

	return count;
}

//---ランダム選択
CRBATBASE_API CrBattleCharacter *crbatRandomSelect(CrBattleCharacter *pSrc,int mode,
												   int include_minasLP /*= 0*/)
{
	int count;//,a,min,max;
	CrBattleCharacter *pList[BATTLECHARA_MAX + 1];
	int index[BATTLECHARA_MAX + 1];

	memset(&pList[0],0,sizeof(pList));
	memset(&index[0],0,sizeof(index));

	count = crbatMakeCharaList(&pList[0],pSrc,mode,include_minasLP);
/*
	if(mode == BAT_TARGET_FRIEND){
		min = 0;
		max = BATTLECHARA_PARTY_MAX;
	} else if(mode == BAT_TARGET_ENEMY){
		min = BATTLECHARA_STARTENEMY;
		max = min + BATTLE_ENEMYMAX;
	}

	for(a = min,count = 0;a < max;a ++){
		if(pBtChara[a].DoExist()){
			if(include_minasLP == 0
				&& pBtChara[a].IsKizetu()){
				//---気絶を抜かすなら
				continue;
			}
			pList[count] = &pBtChara[a];
			index[count] = a;
			count ++;
		}
	}
char s[80];
sprintf(s,"%d,%d %d",min,max,count);
eiMsgBox(s);*/
	return pList[eiRnd(count)];
//	return index[eiRnd(count)];
}

//---ターゲットフィールド
int TargetField[BATTLEFIELD_MAX_X][BATTLEFIELD_MAX_Y];

CRBATBASE_API int crbatGetTargetField(int x,int y)
{
	return TargetField[x][y];
}

CRBATBASE_API void crbatInitTargetField(void)
{
	memset(&TargetField[0][0],0,sizeof(TargetField));
}

//---サークル範囲内にいるキャラクターを検索
CRBATBASE_API int crbatTargetCircle(
					CrBattleCharacter *pSrc,CrBattleCharacter *pDst,
					ei_s32 Range,int Width,CrBattleCharacter **ppList /*= NULL*/)
{
	int a,x,y;
	float src_x,src_y,dst_x,dst_y;
	float dis,fWidth = (float)Width / 32.0f;

	crbatInitTargetField();

	src_x = (float)pSrc->GetFieldX();// + 0.50f;
	src_y = (float)pSrc->GetFieldY();// + 0.50f;
	dst_x = (float)pDst->GetFieldX();// + 0.50f;
	dst_y = (float)pDst->GetFieldY();// + 0.50f;

	//---範囲フィールドを計算
	for(y = 0;y < BATTLEFIELD_MAX_Y;y ++){
		for(x = 0;x < BATTLEFIELD_MAX_X;x ++){
			dis = (float)sqrt(
				   ((float)x - dst_x) * ((float)x - dst_x)
				 + ((float)y - dst_y) * ((float)y - dst_y));

			if((float)dis + 0.20f < (float)fWidth * 0.5f){
				//---範囲内だったら
				TargetField[x][y] = 1;
			}
		}
	}
	if(ppList != NULL){
		*ppList = pDst;
		ppList ++;
	}
	//---範囲内にいるキャラクターを計算
	for(a = 0;a < BATTLECHARA_MAX;a ++){
		if(pBtChara[a].DoExist()){
			x = pBtChara[a].GetFieldX();
			y = pBtChara[a].GetFieldY();

/*			dis = (float)sqrt(
			   ((float)x + 0.5f - dst_x) * ((float)x + 0.5f - dst_x)
				 + ((float)y + 0.5f - dst_y) * ((float)y + 0.5f - dst_y));
			if(dis + 0.20f < fWidth * 0.5f){*/
			if(TargetField[x][y] && pDst != &pBtChara[a]){
				//---範囲内だったら
				if(pBtChara[a].IsFriend() && (Range & BAT_TARGET_FRIEND)){
					if(ppList != NULL){
						*ppList = &pBtChara[a];
						ppList ++;
					}
				} else if(!pBtChara[a].IsFriend() && (Range & BAT_TARGET_ENEMY)){
					if(ppList != NULL){
						*ppList = &pBtChara[a];
						ppList ++;
					}
				}
			}
		}
	}
	if(ppList != NULL){
		*ppList = NULL;
	}

	return 1;
}

//---キャラクター同士を結ぶ直線上にいるキャラクターを検索
CRBATBASE_API int crbatTargetLine(
					CrBattleCharacter *pSrc,CrBattleCharacter *pDst,
					ei_s32 Range,int Width,CrBattleCharacter **ppList /*= NULL*/)
{
	int a,x,y,start;
	float src_x,src_y,dst_x,dst_y;
	float la,lb,lc,dx,dy,dis,ix,fWidth = (float)Width / 32;
	float f;
	int add;

	crbatInitTargetField();

	src_x = (float)pSrc->GetFieldX();
	src_y = (float)pSrc->GetFieldY();
	dst_x = (float)pDst->GetFieldX();
	dst_y = (float)pDst->GetFieldY();
	dx = (float)(dst_x - src_x);
	dy = (float)(dst_y - src_y);

	la = dy;
	lb = -dx;
	lc = (-dy * (float)pSrc->GetFieldX()) + (dx * (float)pSrc->GetFieldY());
	//---範囲フィールドを計算
	for(y = 0;y < BATTLEFIELD_MAX_Y;y ++){
		for(x = 0;x < BATTLEFIELD_MAX_X;x ++){
			dis = (float)(fabs((la * ((float)x) + lb * ((float)y) + lc))
				/ sqrt(la * la + lb * lb));

			if(dis < fWidth * 0.5f){
				//---範囲内だったら
				TargetField[x][y] = 1;
			}
		}
	}
	if(dst_x - src_x != 0.0f){
		if(dy / dx != 0.0f){
			ix = -(float)(1.0f / (dy / dx));
			for(x = 0;x < BATTLEFIELD_MAX_X;x ++){
				f = (float)(ix * (float)x + ((float)src_y - (ix * (float)src_x)));
				if(src_y <= dst_y){
					add = -1;
				} else {
					add = 1;
				}
				start = (int)(f) + add;
				if(src_y <= dst_y && start >= BATTLEFIELD_MAX_X){
					start = BATTLEFIELD_MAX_X - 1;
				} else if(start < 0){
					start = 0;
				}

				for(y = start;0 <= y && y < BATTLEFIELD_MAX_Y;y += add){
					TargetField[x][y] = 0;
				}
			}
		} else {
			if(src_x <= dst_x){
				add = -1;
			} else {
				add = 1;
			}
			for(x = (int)(src_x) + add;0 <= x && x < BATTLEFIELD_MAX_X;x += add){
				for(y = 0;y < BATTLEFIELD_MAX_Y;y ++){
					TargetField[x][y] = 0;
				}
			}
		}
	} else {
		if(src_y <= dst_y){
			add = -1;
		} else {
			add = 1;
		}
		for(y = (int)(src_y) + add;0 <= y && y < BATTLEFIELD_MAX_Y;y += add){
			for(x = 0;x < BATTLEFIELD_MAX_X;x ++){
				TargetField[x][y] = 0;
			}
		}
	}
	//---範囲内にいるキャラクターを計算
	for(a = 0;a < BATTLECHARA_MAX;a ++){
		if(pBtChara[a].DoExist()){
			x = pBtChara[a].GetFieldX();
			y = pBtChara[a].GetFieldY();

/*			if(src_y <= dst_y && y < src_y)
				continue;
			else if(dst_y <= src_y && src_y < y)
				continue;
			if(src_x <= dst_x && x < src_x)
				continue;
			else if(dst_x <= src_x && src_x < x)
				continue;*/

//			dis = (float)(fabs((la * ((float)x + 0.5f) + lb * ((float)y + 0.5f) + lc))
//				/ sqrt(la * la + lb * lb));
//			if(dis < fWidth * 0.5f){
			if(TargetField[x][y]){
				//---範囲内だったら
				if(pBtChara[a].IsFriend() && (Range & BAT_TARGET_FRIEND)){
					if(ppList != NULL){
						*ppList = &pBtChara[a];
						ppList ++;
					}
				} else if(!pBtChara[a].IsFriend() && (Range & BAT_TARGET_ENEMY)){
					if(ppList != NULL){
						*ppList = &pBtChara[a];
						ppList ++;
					}
				}
			}
		}
	}
	if(ppList != NULL){
		*ppList = NULL;
	}

	return 1;
}

//---キャラクター検索
CRBATBASE_API int crbatGetTargetChara(CrBattleCharacter *pSrc,CrBattleCharacter *pChara,ei_s32 Range,
					 	CrBattleCharacter **ppList,int Crash /*= 0*/)
{
	int a;

	if((pChara->DoExist() == 0)
		|| (!pSrc->IsFriend() && pChara->IsKizetu())){
		//---中心キャラクターがいない！！か、敵キャラで対象が気絶
		//---かわりのを探す
		if(Range & BAT_TARGET_FRIEND){
			pChara = crbatRandomSelect(pSrc,BAT_TARGET_FRIEND);
		} else if(Range & BAT_TARGET_ENEMY){
			pChara = crbatRandomSelect(pSrc,BAT_TARGET_ENEMY);
		}
	}

	//---自分がターゲット
	if(Range & BAT_TARGET_ME){
		ppList[0] = pChara;
		ppList[1] = NULL;
		ppList[2] = NULL;
		return 1;
	}

	if(Crash == 1){
		//---衝突補正
		float distance,f;
		CrBattleCharacter *TempList[BATTLECHARA_MAX],*pNear = NULL;
		crbatTargetLine(pSrc,pChara,Range,2 * 32,&TempList[0]);

		for(a = 0 , distance = 9999.0f;a < BATTLECHARA_MAX && TempList[a] != NULL;a ++){
			if(TempList[a]->IsKizetu())
				//---気絶だったら衝突補正しない
				continue;

			f = (float)sqrt(
				  (TempList[a]->GetFieldX() - pSrc->GetFieldX()) * (TempList[a]->GetFieldX() - pSrc->GetFieldX())
				+ (TempList[a]->GetFieldY() - pSrc->GetFieldY()) * (TempList[a]->GetFieldY() - pSrc->GetFieldY()));
			if(f < distance){
				//---近かったら
				pNear = TempList[a];
				distance = f;
			}
		}
		if(pNear != NULL && pNear != pSrc/*一番近いのが自分でない*/){
			if(ppList != NULL){
				ppList[0] = pNear;
			}
		} else {
			if(ppList != NULL)
				ppList[0] = pChara;
		}
		if(ppList != NULL)
			ppList[1] = NULL;
		if(pNear == pSrc)
			pNear = pChara;

		if(pNear == NULL)
			pNear = pChara;

		//---再び範囲検索
		crbatGetTargetChara(pSrc,pNear,Range,ppList,0);

		return 1;
	}

	//---最初は中心
	if(ppList != NULL){
		ppList[0] = pChara;
		ppList[1] = NULL;
		ppList[2] = NULL;
	}

	if(Range & BAT_TARGET_SINGLETARGET){
	} else if(Range & BAT_TARGET_RANGETARGET){
		//---レンジターゲット
		if(BAT_RANGE_LINE1 <= (Range & 0xff0000) && (Range & 0xff0000) <= BAT_RANGE_LINE7){
			//---ラインターゲットなら
			crbatTargetLine(pSrc,pChara,Range,
				BattleLineRange[(((Range & 0xff000) >> 16) - BAT_RANGE_LINESTART)] * 32,ppList);
		} else if(BAT_RANGE_CIRCLE1 <= (Range & 0xff0000) && (Range & 0xff0000) <= BAT_RANGE_CIRCLE7){
			//---サークルターゲット
			crbatTargetCircle(pSrc,pChara,Range,
				BattleCircleRange[(((Range & 0xff000) >> 16) - BAT_RANGE_CIRCLESTART)] * 32,ppList);
		}
	} else if(Range & BAT_TARGET_ALLTARGET){
		//---オールターゲット
		int x,y;
		for(y = 0;y < BATTLEFIELD_MAX_Y;y ++){
			for(x = 0;x < BATTLEFIELD_MAX_X;x ++){
				TargetField[x][y] = 1;
			}
		}

		for(a = 0;a < BATTLECHARA_MAX;a ++){
			if(pBtChara[a].DoExist()){
				if(pBtChara[a].IsFriend() && Range & BAT_TARGET_FRIEND){
					if(ppList != NULL){
						*ppList = &pBtChara[a];
						ppList ++;
					}
				} else if(!pBtChara[a].IsFriend() && Range & BAT_TARGET_ENEMY){
					if(ppList != NULL){
						*ppList = &pBtChara[a];
						ppList ++;
					}
				}
			}
		}
	}

	return 1;
}

//---キャラクターを特定キャラクターに向かせる
void crbatSetAllCharacterDirection(CrBattleCharacter *pChara,CrBattleCharacter **ppList)
{
	float angle;

	if(ppList[1] == NULL){
		//---対象が一体だけなら
		if(pChara != ppList[0]){
			//---自分でなければ
			angle = pChara->GetCharaAngle(ppList[0]);
			pChara->SetAngle(angle);
			ppList[0]->SetAngle(angle + ANGLE(180));
		}
	} else {
		for(; *ppList != NULL ; ppList ++){
			if(pChara != *ppList){
				//---自分でなければ
				angle = pChara->GetCharaAngle(*ppList);
				(*ppList)->SetAngle(angle + ANGLE(180));
			}
		}
	}
}

CRBATBASE_API int crbatIsFieldRange(ei_s32 x,ei_s32 y)
{
	if(x < 0 || x >= BATTLEFIELD_MAX_X
	|| y < 0 || y >= BATTLEFIELD_MAX_Y)
		return 0;

	return 1;
}

//---そこに誰かいるか
CRBATBASE_API int crbatIsThere(ei_s32 x,ei_s32 y,CrBattleCharacter *pChara /* = NULL*/)
{
	int a;

	for(a = 0;a < BATTLECHARA_MAX;a ++){
		if(pChara != NULL){
			if(pChara == &pBtChara[a]){
				//---自分自身だったら　
				continue;
			}
		}
		if(pBtChara[a].DoExist()){
			if(x == pBtChara[a].GetFieldX() && y == pBtChara[a].GetFieldY()){
				return 1;
			}
		}
	}

	return 0;
}

CRBATBASE_API int crbatIsThere(CrBattleCharacter *pChara)
{
	return crbatIsThere(pChara->GetFieldX(),pChara->GetFieldY(),pChara);
}

//---------------------------------------------------------------
//---------------------------------------------------------------

//---画面全体を描き直す
CRBATBASE_API void crbatDrawScreen(void)
{
	crbaseClearScreen();

	crbatShowStatus();
crdataEnableRec(0);
	crbatDrawScene();
crdataEnableRec(1);
}

//---------------------------------------------------------------
//---------------------------------------------------------------

//---キャラクター座標をポリゴン座標に直す
CRBATBASE_API int crbatTranslatePos(float x,float y,float z,float *dx,float *dy,float *dz)
{
//	*dx = (float)x / (float)BATTLEFIELD_PTN_SIZE;
//	*dy = (float)y / (float)BATTLEFIELD_PTN_SIZE;
//	*dz = (float)z / (float)BATTLEFIELD_PTN_SIZE;

	*dx = (float)x;
	*dy = (float)y;
	*dz = (float)z;

	return 1;
}

//---ビューモードを得る
CRBATBASE_API int crbatGetViewMode(void)
{
	return BattleViewMode;
}

//---ビューモードをセット
CRBATBASE_API void crbatSetViewMode(int mode)
{
	BattleViewMode = mode;

	if(BattleViewMode == BATTLE_VIEWMODE_FULLSCREEN){
	} else if(BattleViewMode == BATTLE_VIEWMODE_SINGLE){
	} else if(BattleViewMode == BATTLE_VIEWMODE_DOUBLE){
	}
}

CRBATBASE_API float crbatGetCameraAngle(float fcx,float fcy,float fdx,float fdy)
{
	float angle;

	if(fdx - fcx == 0.0f && fcy - fdy == 0.0f)
		return 0.0f;

	if(fdx - fcx != 0.0f){
		//---角度計算
		angle = (float)atan((fdy - fcy) / (fdx - fcx));
	} else {
//		angle = PI * 0.5f;
		if(fdy - fcy >= 0.0f)
			return ANGLE(90);
		else
			return ANGLE(270);
	}
//	angle = (float)atan2(fdx - fcx , fdy - fcy);
//	angle += ANGLE(180);
//	if(angle < 0.0f)
//		angle = ANGLE(360) + angle;

	if(fdx - fcx <= 0.0f && fdy - fcy >= 0.0f)
		//---90 - 180
		angle = PI + angle;
	else if(fdx - fcx <= 0.0f && fdy - fcy < 0.0f)
		//---180 - 270
		angle = PI + angle;
	else if(fdx - fcx >= 0.0f && fdy - fcy < 0.0f)
		//---270 - 360
		angle = ANGLE(360) /*PI * 2.0f*/ + angle;

	return angle;
}

//---カメラをセット
CRBATBASE_API int crbatSetCamera(int camera,float cx,float cy,float cz,float dx,float dy,float dz,float angle)
{
	int a;
	float fcx,fcy,fcz,fdx,fdy,fdz;

	crbatTranslatePos(cx,cy,cz,&fcx,&fcy,&fcz);
	crbatTranslatePos(dx,dy,dz,&fdx,&fdy,&fdz);

/*	char s[80];
	sprintf(s,"%f , %f, %f\n",fcx,fcy,fcz);
	eiDebugWriteFile(s);
	sprintf(s,"%f , %f, %f   %f\n\n",fdx,fdy,fdz,angle);
	eiDebugWriteFile(s);*/
	if(fcx == fdx && fcy == fdy && fcz == fdz){
//		eiDebugWriteFile("@@@@@@@@@@@@@@@@@@@@@\n");
		fdx += 0.01f;
		fdy += 0.01f;
	}

	BattleView[camera].matCamera.SetCalcCamera(1.00f,2.00f,1.00f);
	BattleView[camera].matCamera.CalcCamera(
		D3DVECTOR(fcx,fcz,fcy),
		D3DVECTOR(fdx,fdz,fdy),
		D3DVECTOR(0.0f,1.0f,0.0f),
		angle);
	for(a = ViewNumber[BattleViewMode];a < 2;a ++){
		BattleView[a].matCamera.SetCalcCamera(1.00f,2.00f,1.00f);
		BattleView[a].matCamera.CalcCamera(
			D3DVECTOR(fcx,fcz,fcy),
			D3DVECTOR(fdx,fdz,fdy),
			D3DVECTOR(0.0f,1.0f,0.0f),
			angle);
		BattleView[a].cx = fcx; BattleView[a].cy = fcy; BattleView[a].cz = fcz;
		BattleView[a].dx = fdx; BattleView[a].dy = fdy; BattleView[a].dz = fdz;
	}

	BattleView[camera].cx = fcx; BattleView[camera].cy = fcy; BattleView[camera].cz = fcz;
	BattleView[camera].dx = fdx; BattleView[camera].dy = fdy; BattleView[camera].dz = fdz;

	BattleView[camera].Angle = crbatGetCameraAngle(fcx,fcy,fdx,fdy);
/*	sprintf(s,"%f\n",BattleView[camera].Angle);
	eiDebugWriteFile(s);*/

/*	if(fdx - fcx != 0.0f){
		//---角度計算
		BattleView[camera].Angle = (float)atan((fdy - fcy) / (fdx - fcx));
	} else {
		BattleView[camera].Angle = PI * 0.5f;
	}

	if(fdx - fcx < 0.0f && fdy - fcy > 0.0f)
		BattleView[camera].Angle = PI + BattleView[camera].Angle;
	else if(fdx - fcx < 0.0f && fdy - fcy < 0.0f)
		BattleView[camera].Angle = PI + BattleView[camera].Angle;
	else if(fdx - fcx > 0.0f && fdy - fcy < 0.0f)
		BattleView[camera].Angle = PI * 2.0f + BattleView[camera].Angle;
*/
	return 1;
}

//---カメラを全体表示にする
CRBATBASE_API int crbatSetCamera_ViewBattleField(int camera,float angle,int moving /*= 0*/,int run_time /*= 500*/)
{
	float r1 = 15.0f,r2 = 15.0f;//14,9

	if(moving == 1){
		crbatMoveCamera(camera,
			5.5f - (float)(cos(angle) * r1),
			5.5f - (float)(sin(angle) * r1),
			5.0f,
			5.5f + (float)(cos(angle) * r2),
			5.5f + (float)(sin(angle) * r2),
			0.0f,run_time);
		return 1;
	} else if(moving == 2){
		crbatBeginMovingCamera(camera,
			5.5f - (float)(cos(angle) * r1),
			5.5f - (float)(sin(angle) * r1),
			5.0f,
			5.5f + (float)(cos(angle) * r2),
			5.5f + (float)(sin(angle) * r2),
			0.0f);
		return 1;
	} else {
		return crbatSetCamera(camera,
			5.5f - (float)(cos(angle) * r1),
			5.5f - (float)(sin(angle) * r1),
			5.0f,
			5.5f + (float)(cos(angle) * r2),
			5.5f + (float)(sin(angle) * r2),
			0.0f);
	}

	return 1;
}

//---キャラクター座標からスクリーン座標へ
CRBATBASE_API int crbatCalcCharacterToScreen(float sx,float sy,float sz,float *dx,float *dy,float *dz,float *rate)
{
	D3DVERTEX *pVer = (D3DVERTEX *)vbSrc.Lock();
	float px,py,pz;

	crbatTranslatePos(sx,sy,sz,&px,&py,&pz);

	if(pVer){
		pVer[0] = D3DVERTEX( D3DVECTOR(px,py,pz), D3DVECTOR(0.0f,0.0f,0.0f),D3DVAL(0.0f),D3DVAL(0.0f));
		vbSrc.Unlock();
		//---座標変換
		vbSrc.Process(&vbDest,1);

		D3DTLVERTEX *pDstVer = (D3DTLVERTEX *)vbDest.Lock();
		*dx = pDstVer[0].sx;
		*dy = pDstVer[0].sy;
		*dz = pDstVer[0].sz;
		vbDest.Unlock();

		//---倍率
		*rate = 1.0f;

		if(pViewport->InViewport(*dx,*dy)){
			//---描く範囲にある
			return 1;
		}
	}
	return 0;
}

//---２Ｄキャラクターを３Ｄ座標上に描く
CRBATBASE_API void crbatPut3DCell(eiTextureCell *pCell,float sx,float sy,float sz,float limit /* = 0.50f*/)
{
	float dx,dy,dz,rate;

	if(crbatTranslate3DTo2D(sx,sy,sz,&dx,&dy,&dz,&rate)){
	}
	{
		rate = rate / (float)pCell->Data.xSize;

		if(dz > limit){
			pCell->PutExtend( ew->lpCell[1],
				(int)(dx - (float)pCell->Data.xSize * (float)rate * 0.50f),
				(int)(dy - (float)pCell->Data.ySize * (float)rate),rate,rate,EI_TRANS);
		}
	}
}

//---座標変換
CRBATBASE_API int crbatTranslate3DTo2D(
	float sx,float sy,float sz,
	float *dx ,float *dy ,float *dz ,float *rate)
{
	D3DVERTEX *pVer = (D3DVERTEX *)vbSrc.Lock();
	float px,py,pz;

	crbatTranslatePos(sx,sy,sz,&px,&py,&pz);

	if(pVer){
		pVer[0] = D3DVERTEX( D3DVECTOR(px,py,pz), D3DVECTOR(0.0f,0.0f,0.0f),D3DVAL(0.0f),D3DVAL(0.0f));

		vbSrc.Unlock();
		//---座標変換
		vbSrc.Process(&vbDest,1);

		D3DTLVERTEX *pDstVer = (D3DTLVERTEX *)vbDest.Lock();
		*dx = pDstVer[0].sx;
		*dy = pDstVer[0].sy;
		*dz = pDstVer[0].sz;
		*rate = (float)((1.0 - *dz) * BATTLE_ZDEPTH);//---係数をかける

		vbDest.Unlock();

		if(pViewport->InViewport(*dx,*dy)){
			//---描く範囲にある
			return 1;
		}
	}

	return 0;
}

//---今いる敵の数を返す
CRBATBASE_API int crbatGetEnemyCount(void)
{
	int a,count;

	for(a = 0 , count = 0;a < BATTLECHARA_MAX;a ++){
		if(pBtChara[a].DoExist()){
			if(pBtChara[a].IsFriend() == 0){
				count ++;
			}
		}
	}
	return count;
}
