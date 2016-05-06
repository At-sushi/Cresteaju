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

//---���݂��邩
int CrBattleCharacter::DoExist(void)
{
	return BattleInfo.Existence;
}

//---���݂��邩
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
//---�O���t�B�b�N�Ǘ�

//---�Z����ݒ�
void CrBattleCharacter::SetCell(eiCell *pc)
{
	OnlyInfo.pCell = pc;
}

eiCell *CrBattleCharacter::GetCell(void)
{
	return OnlyInfo.pCell;
}

//---�p�^�[���ݒ�
void CrBattleCharacter::SetPattern(int number)
{
	OnlyInfo.Pattern = number;
}

//---�p�^�[���������ݒ�
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

//---�`�惂�[�h�̐ݒ�
void CrBattleCharacter::SetDrawType(int type)
{
	OnlyInfo.DrawType = type;
}

int CrBattleCharacter::GetDrawType(void)
{
	return OnlyInfo.DrawType;
}

//---�A�j�����[�h
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
//---���W�Ǘ�
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

//---�y�I�t�Z�b�g
void CrBattleCharacter::SetZOffset(float offset)
{
	OnlyInfo.ZOffset = offset;
}

float CrBattleCharacter::GetZOffset(void)
{
	return OnlyInfo.ZOffset;
}

//---�L�����N�^�[�̑傫��
ei_s32 CrBattleCharacter::GetCharaWidth(void)
{
	return OnlyInfo.pCell[0].Data.xSize;
}

//---�L�����N�^�[�̑傫��
ei_s32 CrBattleCharacter::GetCharaHeight(void)
{
	return OnlyInfo.pCell[0].Data.ySize;
}

void CrBattleCharacter::SetAngle(float angle)
{
	//---�_�E����������������ݒ薳��
	if(IsDown())
		return;

	OnlyInfo.Angle = angle;
}

float CrBattleCharacter::GetAngle(void)
{
	return OnlyInfo.Angle;
}

//---�ΏۃL�����N�^�[�Ƃ̑��Ίp�x
float CrBattleCharacter::GetCharaAngle(CrBattleCharacter *pChara)
{
	float angle;

	angle = crbatGetCameraAngle(
		(float)GetFieldX(),(float)GetFieldY(),
		(float)pChara->GetFieldX(),(float)pChara->GetFieldY());

	return angle;
}

//---�L�����N�^�[�Ԃ̋���
float CrBattleCharacter::GetDistance(CrBattleCharacter *pChara)
{
	int sx = GetFieldX(),sy = GetFieldY(),
		dx = pChara->GetFieldX(),dy = pChara->GetFieldY();

	return (float)sqrt(((sx - dx) * (sx - dx)) + ((sy - dy) * (sy - dy)));
}

//---�J�����A���O�����ړ�
void CrBattleCharacter::MoveCamera(float angle,float r,int run_time,int camera /*= 0*/)
{
	float cx,cy,cz,dx,dy,dz;

	GetCameraAngle(angle,r,&cx,&cy,&cz,&dx,&dy,&dz);
	crbatMoveCamera(camera,cx,cy,cz,dx,dy,dz,run_time);
}

//---�J�����𐳖ʂɃZ�b�g
void CrBattleCharacter::SetCameraFront(int camera /* = 0*/)
{
	SetCameraAngle(ANGLE(180),5.0f,camera);
}

void CrBattleCharacter::BeginMovingCameraFront(int camera /*= 0*/)
{
	BeginMovingCameraAngle(ANGLE(180),5.0f,camera);
}

//---�J�����A���O�����Z�b�g����
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

//---�J�����A���O�����Z�b�g����
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
//---�G��������
ei_s32 CrBattleCharacter::IsFriend(void)
{
	return BattleInfo.FriendOrEnemy;
}

//---�ʂ��ԍ�
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
