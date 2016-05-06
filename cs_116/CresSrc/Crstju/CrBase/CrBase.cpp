/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBase.cpp ...Base functions

-----------------------------------------------------------*/

#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBASE

#define EXTERN_EICLASS
#include "..\CrBase.h"

#ifdef MAKE_DLL
	#define CR_GAMEINFO_POINTER
#else
	#define CR_GAMEINFO_EXTERNPOINTER
#endif /*MAKE_DLL*/
#include "..\CrGameInfo.h"

//__declspec(dllimport)
//---Include sub files
	#include "CrInput.cpp"
	#include "CrWindow.cpp"
	#include "CrMessageManager.cpp"
	#include "CrBase_SubHistory.cpp"
//-----------------------------------
//#include "CrObject.h"

ei_u32 *pDumyPtr;

//---DLL�̏�����
CRBASE_API int crbaseInitDLL(CRESTEAJU_GAMEDATA *pgameusingdata,
							 CRESTEAJU_GAMEINFO *pgame,
							 CRESTEAJU_PARTYINFO *pparty,
							 CrCharacter *pplayer,
							 CrItem *pitem,CrMagic *pmagic,
							 int *pdebug,int *pfilemode,
							 CRESTEAJU_SYSTEM *psystem,CRESTEAJU_INITIALIZE *pini,
							 CRESTEAJU_EXEINFO *pexeInfo,
							 ei_u32 *pDumy)
{
	pGameUsingData = pgameusingdata;
	pGameInfo = pgame;
	pPartyInfo = pparty;
	pCharacterInfo = pplayer;
	pItemInfo = pitem;
	pMagicInfo = pmagic;
	pCrExeInfo = pexeInfo;

	//---
	crdataSetPointer(pdebug,pfilemode,psystem,pini);

	pDumyPtr = pDumy;
	return 1;
}

CRBASE_API CRESTEAJU_GAMEINFO *crbaseGetGameInfo(void)
{
	return pGameInfo;
}


//---�S�f�[�^���Z�b�g������
CRBASE_API int crbaseSetAllData(int load_map /*= 0*/)
{
	//---���y���Z�b�g
	crmusicPlay(CRMUSIC_INIT);

	if(load_map){
		//---�}�b�v�f�[�^���[�h
		crfieldChangeMap(
			crbaseGetGameInfo()->MapNumber,
			crbaseGetGameInfo()->MapScene,
			1,1);
	}

	//---�ʒu�𒼂�
	crfieldChangePos(
		crbaseGetGameInfo()->FieldX,
		crbaseGetGameInfo()->FieldY,
		crbaseGetGameInfo()->FieldPlane);

	//---�R���t�B�O�ݒ�
	crsysSetSystemInfo();

	//---�ǎ����[�h
	crbaseLoadWallPaper(pGameInfo->UseWallPaper);

	//---��l�����[�h
	crfieldSetMainCharacter(pGameInfo->MainCharacterNumber);
	//---��l���`��
	crfieldShowMainCharacter(1);
	//---��l���ړ�����

	//---�烍�[�h
	crcharaLoadFace(-1);

	//---���y���f�B�t�H���g��
	eiSleep(250);
	crfieldChangeMapMusic();

	return 1;
}

//---------------------------------------------
HANDLE hCresteajuLock = NULL;

//---���b�N
CRBASE_API int crbaseLockCresteaju(void)
{
	hCresteajuLock = CreateSemaphore(NULL,1,1,"CresteajuLock");

	if(hCresteajuLock == NULL)
		return 0;

	if(WaitForSingleObject(hCresteajuLock,100) == WAIT_OBJECT_0)
		return 1;

	return 0;
}

CRBASE_API int crbaseUnlockCresteaju(void)
{
	ReleaseSemaphore(hCresteajuLock,1,NULL);
	CloseHandle(hCresteajuLock);
	hCresteajuLock = NULL;

	return 1;
}

//---------------------------------------------
//---���j���[�E�F�C�g���Z�b�g
CRBASE_API void crbaseMenuReset(void)
{
	et->Reset();
}

//---���j���[�E�F�C�g
CRBASE_API void crbaseMenuStart(int wait /*= -1*/)
{
	if(wait == -1)
		wait = crdataGetSystem()->MenuWaitTime;

	if(!crsysQuick()){
		et->Wait2(wait);
	}
}

//---���j���[�V�[����������
CRBASE_API void crbaseInitMenuScene(void)
{
	crbaseMenuReset();
	if(pGameInfo->TransWindow == 0){
		//---����ʃN���A
//		crbaseClearScreen(0x02);
	}
	crbaseSaveFrontPage(1);
}

//---���j���[�V�[�����I�����ăt�B�[���h�ɖ߂�
CRBASE_API void crbaseEndMenuScene(void)
{
	crbaseMenuReset();
	crbaseClearScreen();
	crfieldDrawFrame();
	crbaseMenuStart();
}

//---�͂��A�������̑I��
CRBASE_API int crbaseSelectYesNo(eistr *pText /*= NULL*/,
								 int x /*= -1*/,int y /*= -1*/)
{
	int ret;
	CrSelectWindow win;

	crbaseMenuReset();

	if(x == -1)
		x = 96;
	if(y == -1)
		y = 64;

	int sx = 11;

	if((int)strlen(pText) * 6 + 32 > sx * 16)
		sx = (strlen(pText) * 6 + 32) / 16;

	win.Create(x,y,sx,5,pText,"   �͂� ;  ������;",1,16);
	win.Refresh();
	crbaseMenuStart();
	ret = win.Select();

	crbaseMenuReset();
	crbaseMenuStart(250);
	if(ret == -1)
		ret = 1;

	return ret;
}

//-------------------------------------
//---������
CRBASE_API int crbaseGetMoney(void)
{
	return pGameInfo->Money;
}

CRBASE_API void crbaseSetMoney(int money)
{
	if(money < 0)
		money = 0;
	if(money > MONEY_MAX)
		money = MONEY_MAX;

	pGameInfo->Money = money;
}

CRBASE_API void crbaseAddMoney(int money)
{
	money += pGameInfo->Money;
	crbaseSetMoney(money);
}

//---��������\��
CRBASE_API void crbaseShowMoney(int tx,int ty)
{
	char s[80];
	CrStringWindow win;

	win.Create(tx,ty,11,2);
	win.DrawText("������");
	win.SetColor(CRCOLOR_GREEN);
	sprintf(&s[0]," %7d",crbaseGetMoney());
	win.DrawText(s);
	win.SetColor(CRCOLOR_WHITE);
	win.DrawText(MONEY_NAME);
}

#define HIST_MAX 999999999

//---���܂܂ŕ���������
CRBASE_API void crbaseAddWalk(void)
{
	if(pGameInfo->WalkCount < HIST_MAX)
		pGameInfo->WalkCount ++;
}

CRBASE_API ei_s32 crbaseGetWalk(void)
{
	return pGameInfo->WalkCount;
}

//----------------------------------------------
//---�v���C����
CRBASE_API ei_s32 crbaseGetPlayTime(void)
{
	return pGameInfo->PlayHours * 3600
		+ pGameInfo->PlayMinutes * 60
		+ pGameInfo->PlaySeconds;
}

CRBASE_API void crbaseShowPlayTime(int tx,int ty,int refresh /*= 0*/)
{
	char s[80];
	CrStringWindow win;

	win.Create(tx,ty,11,2);
	win.SetColor(CRCOLOR_WHITE);
	win.DrawText("�v���C����");
	win.SetColor(CRCOLOR_GREEN);
	sprintf(&s[0]," %3d:%02d:%02d",
		pGameInfo->PlayHours,pGameInfo->PlayMinutes,pGameInfo->PlaySeconds);
	win.DrawText(s);
	if(refresh){
		win.Refresh();
	}
}

CRBASE_API void crbaseCalcHour(int hour)
{
	pGameInfo->PlayHours += hour;

	if(pGameInfo->PlayHours > 999){
		pGameInfo->PlayHours = 999;
	}
}

CRBASE_API void crbaseCalcMinute(int minute)
{
	pGameInfo->PlayMinutes += minute;

	if(pGameInfo->PlayMinutes >= 60){
		crbaseCalcHour(pGameInfo->PlayMinutes / 60);
		pGameInfo->PlayMinutes %= 60;
	}
}

CRBASE_API void crbaseCalcSecond(int second)
{
	pGameInfo->PlaySeconds += second;

	if(pGameInfo->PlaySeconds >= 60){
		crbaseCalcMinute(pGameInfo->PlaySeconds / 60);
		pGameInfo->PlaySeconds %= 60;
	}
}

