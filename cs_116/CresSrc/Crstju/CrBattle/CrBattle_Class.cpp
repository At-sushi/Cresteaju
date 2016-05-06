/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBattle_Class.cpp ...Battle Class functions

-----------------------------------------------------------*/

#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBATTLE_CLASS

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#define EXTERN_CRBATTLE
#include "..\CrBase.h"
#include "..\CrBattle.h"

#define CR_GAMEINFO_EXTERNPOINTER
#include "..\CrGameInfo.h"

#include "CrBattle_ClassCommand.cpp"
#include "CrBattle_ClassStatus.cpp"
#include "CrBattle_ClassBtStatus.cpp"
#include "CrBattle_ClassObject.cpp"
#include "CrBattle_ClassDamage.cpp"
#include "CrBattle_ClassAnime.cpp"
//#include "CrBattle_ClassWindow.cpp"

CrBattleCharacter::CrBattleCharacter(void) : CrCharacter()
{
	eimemset(&BattleInfo,0,sizeof(BattleInfo));
	eimemset(&OnlyInfo,0,sizeof(OnlyInfo));

	ResetMagicTime();
	AddFromLastMagic();
}

CrBattleCharacter::~CrBattleCharacter()
{
}

void CrBattleCharacter::InitBattleCharacter(void)
{
	eimemset(&BattleInfo,0,sizeof(BattleInfo));
	eimemset(&OnlyInfo,0,sizeof(OnlyInfo));

	ResetMagicTime();
	AddFromLastMagic();
//	CrBattleCharacter();
}

int CrBattleCharacter::KindOf(void)
{
	return 0;
}

//---存在するか
int CrBattleCharacter::DoExist(void)
{
	return BattleInfo.Existence;
}

//---存在するか
int CrBattleCharacter::DoExistExtend(void)
{
	if(DoExist())
		return DoExist();

	return BattleInfo.ExistenceExtend;
}

void CrBattleCharacter::SetExistance(int exist)
{
	BattleInfo.Existence = exist;
}

//----------------------------------------------
//---グラフィック管理

//---セルを設定
void CrBattleCharacter::SetCell(eiCell *pc)
{
	OnlyInfo.pCell = pc;
}

eiCell *CrBattleCharacter::GetCell(void)
{
	return OnlyInfo.pCell;
}

//---パターン設定
void CrBattleCharacter::SetPattern(int number)
{
	OnlyInfo.Pattern = number;
}

//---パターンを自動設定
void CrBattleCharacter::SetPatternAuto(void)
{
	if(!GetDrawType()){
		if(IsDown()){
			SetPattern(4);
		} else {
			SetPattern(0);
		}
	} else {
		SetPattern(0);
	}
}

int CrBattleCharacter::GetPattern(void)
{
	return OnlyInfo.Pattern;
}

//---描画モードの設定
void CrBattleCharacter::SetDrawType(int type)
{
	OnlyInfo.DrawType = type;
}

int CrBattleCharacter::GetDrawType(void)
{
	return OnlyInfo.DrawType;
}

//---アニメモード
int CrBattleCharacter::GetAnimeMode(void)
{
	return OnlyInfo.AnimeMode;
}

int CrBattleCharacter::SetNotShow(int show)
{
	int old = OnlyInfo.Show;

	OnlyInfo.Show = show;

	return old;
}

int CrBattleCharacter::DontShow(void)
{
	return OnlyInfo.Show;
}

//----------------------------------------------
//---座標管理
void CrBattleCharacter::SetFieldPos(ei_s32 sx,ei_s32 sy,ei_s32 sz /*= 0*/)
{
	OnlyInfo.x = sx;
	OnlyInfo.y = sy;
	OnlyInfo.z = sz;
}

ei_s32 CrBattleCharacter::GetFieldX(void)
{
	return OnlyInfo.x;
}

ei_s32 CrBattleCharacter::GetFieldY(void)
{
	return OnlyInfo.y;
}

ei_s32 CrBattleCharacter::GetFieldZ(void)
{
	return OnlyInfo.z;
}

//---Ｚオフセット
void CrBattleCharacter::SetZOffset(float offset)
{
	OnlyInfo.ZOffset = offset;
}

float CrBattleCharacter::GetZOffset(void)
{
	return OnlyInfo.ZOffset;
}

//---キャラクターの大きさ
ei_s32 CrBattleCharacter::GetCharaWidth(void)
{
	return OnlyInfo.pCell[0].Data.xSize;
}

//---キャラクターの大きさ
ei_s32 CrBattleCharacter::GetCharaHeight(void)
{
	return OnlyInfo.pCell[0].Data.ySize;
}

void CrBattleCharacter::SetAngle(float angle)
{
	//---ダウン中だったら向き設定無効
	if(IsDown())
		return;

	OnlyInfo.Angle = angle;
}

float CrBattleCharacter::GetAngle(void)
{
	return OnlyInfo.Angle;
}

//---対象キャラクターとの相対角度
float CrBattleCharacter::GetCharaAngle(CrBattleCharacter *pChara)
{
	float angle;

	angle = crbatGetCameraAngle(
		(float)GetFieldX(),(float)GetFieldY(),
		(float)pChara->GetFieldX(),(float)pChara->GetFieldY());

	return angle;
}

//---キャラクター間の距離
float CrBattleCharacter::GetDistance(CrBattleCharacter *pChara)
{
	int sx = GetFieldX(),sy = GetFieldY(),
		dx = pChara->GetFieldX(),dy = pChara->GetFieldY();

	return (float)sqrt(((sx - dx) * (sx - dx)) + ((sy - dy) * (sy - dy)));
}

//---カメラアングルを移動
void CrBattleCharacter::MoveCamera(float angle,float r,int run_time,int camera /*= 0*/)
{
	float cx,cy,cz,dx,dy,dz;

	GetCameraAngle(angle,r,&cx,&cy,&cz,&dx,&dy,&dz);
	crbatMoveCamera(camera,cx,cy,cz,dx,dy,dz,run_time);
}

//---カメラを正面にセット
void CrBattleCharacter::SetCameraFront(int camera /* = 0*/)
{
	SetCameraAngle(ANGLE(180),5.0f,camera);
}

void CrBattleCharacter::BeginMovingCameraFront(int camera /*= 0*/)
{
	BeginMovingCameraAngle(ANGLE(180),5.0f,camera);
}

//---カメラアングルをセットする
void CrBattleCharacter::SetCameraAngle(float angle,float r,int camera /* = 0*/)
{
	float sx = (float)GetFieldX(),sy = (float)GetFieldY(),sz = CAMERA_DEFAULT_Z;

	angle = GetAngle() + angle;

	crbatSetCamera(camera,
		sx - r * (float)cos(angle),
		sy - r * (float)sin(angle),
		sz,
		sx + CAMERA_DEFAULT_R * (float)cos(angle),
		sy + CAMERA_DEFAULT_R * (float)sin(angle),
		0.0f);
}

//---カメラアングルをセットする
void CrBattleCharacter::BeginMovingCameraAngle(float angle,float r,int camera /* = 0*/)
{
	float sx = (float)GetFieldX(),sy = (float)GetFieldY(),sz = CAMERA_DEFAULT_Z;

	angle = GetAngle() + angle;

	crbatBeginMovingCamera(
		camera,
		sx - r * (float)cos(angle),
		sy - r * (float)sin(angle),
		sz,
		sx + CAMERA_DEFAULT_R * (float)cos(angle),
		sy + CAMERA_DEFAULT_R * (float)sin(angle),
		0.0f);
}

void CrBattleCharacter::GetCameraAngle(float angle,float r,
	float *cx,float *cy,float *cz,float *dx,float *dy,float *dz)
{
	float sx = (float)GetFieldX(),sy = (float)GetFieldY(),sz = CAMERA_DEFAULT_Z;

	angle = GetAngle() + angle;

	*cx = sx - r * (float)cos(angle);
	*cy = sy - r * (float)sin(angle);
	*cz = sz,
	*dx = sx + CAMERA_DEFAULT_R * (float)cos(angle);
	*dy = sy + CAMERA_DEFAULT_R * (float)sin(angle);
	*dz = 0.0f;
}

//----------------------------------------------
//---敵味方判別
ei_s32 CrBattleCharacter::IsFriend(void)
{
	return BattleInfo.FriendOrEnemy;
}

//---通し番号
ei_s32 CrBattleCharacter::GetNumber(void)
{
	int a;

	for(a = 0;a < BATTLECHARA_MAX;a ++){
		if(this == &pBtChara[a])
			return a;
	}
	return -1;
}


//-------------------------------------------------
void CrBattleCharacter::AddEnemyExperience(void)
{
	BattleExperience += BattleInfo.Enemy.Experience;
	BattleMoney += BattleInfo.Enemy.Money;
}

void CrBattleCharacter::AddEnemyMoney(void)
{
}
