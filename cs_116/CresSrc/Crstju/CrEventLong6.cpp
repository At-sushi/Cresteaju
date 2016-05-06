/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrEventLong6.cpp ...Event functions

-----------------------------------------------------------*/


#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CREVENTLONG6

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#include "CrBase.h"
#include "CrBattle.h"
#include "CrEvent.h"
#include "CrEvCom.h"

//---game info
#define CR_GAMEINFO_EXTERNPOINTER
#include "CrGameInfo.h"

CREVENTLONG6_API int crevent_dumy(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	return 1;
}


//---�암��ጴ�A�����D
CREVENTLONG6_API int creventSouthSnowField_First(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;
	int x = ef->xGet(),y = ef->yGet();

	mcShow(0);

	crmusicFadeOut();
	crfieldChangeMap(59,0,0,0);
	crfieldChangeScene(0,13,9);
	evFadeOut();

	et->Delay2(1000);

	npPos(0,13,6);
	npDir(0,SOUTH);
	npPos(1,11,7);
	npDir(1,EAST);
	npPos(5,12,9);
	npDir(5,NORTH);

	evFieldNoFlip(0,1);
	evFadeIn();

	evFrameWait(1000);
	crmusicPlay(CRMUSIC_SILENT);
	//---����
	mes.OpenMessage("GS.msg",101);
	mes.ReadDraw(2);
	//---�Ȃ�Ȃ�
	evFrameWait(500);
	npMove(5,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---�T���B�A�[����
	npPos(3,5,7);
	npDir(3,SOUTH);
	for(a = 0;a < 15;a ++){
		if(a < 4)
			npMove(3,0,1);
		else if(a < 12)
			npMove(3,1,0);
		else if(a < 14)
			npMove(3,0,-1);
		else
			npMove(3,1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//--����������
	evFrameWait(250);
	npDir(2,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw(2);

	//---�I
	evFrameWait(500);
	mes.ReadDraw();

	//---�O������
	evFrameWait(500);
	npDir(2,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---�f�B�U������
	evFrameWait(250);
	npDir(1,SOUTH);
	for(a = 0;a < 4;a ++){
		if(a < 2)
			npMove(1,0,1);
		else
			npMove(1,1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---����ȁE�E�E
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(2,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---�ǂ����悤
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	//---�N���C�V�����I
	evFrameWait(500);
	npDir(0,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---�Ⴄ�́I
	evFrameWait(250);
	mes.ReadDraw(2);

	//---�V���o�[�����O�́E�E�E
	evFrameWait(250);
	mes.ReadDraw();

	//---�Ȃ�قǂ�
	evFrameWait(500);
	mes.ReadDraw(3);

	//---���I�H
	evFrameWait(250);
	npDir(2,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---�����I
	evFrameWait(500);
	mes.ReadDraw();

	//---�����ł���
	evFrameWait(500);
	mes.ReadDraw(3);

	//---���[�t�B�A�B��
	evFrameWait(500);
	npDir(5,EAST);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---��k����Ȃ����I
	evFrameWait(250);
	mes.ReadDraw(2);

	//---�����Ȃ��
	evFrameWait(1000);
	mes.ReadDraw();

	//---�����E�E�E
	evFrameWait(2000);
	mes.ReadDraw(4);

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	mcShow(1);
	crfieldChangeMap(10,0,0,0);
	evScene(0,x,y);
	evFrameWait(500);

	evSet(204,1);

	return 1;
}

//---�암��ጴ�A�Y���ꂽ��ՁA�͂��߂�
CREVENTLONG6_API int creventWasurerareta_First(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	crfieldChangeMap(86,0,1,1);
	crfieldChangeScene(0,6,4);

	npPos(0,6,4);
	npDir(0,SOUTH);
	npPos(1,4,3);
	npDir(1,SOUTH);
	npPos(2,5,3);
	npDir(2,SOUTH);
	npPos(3,7,4);
	npDir(3,SOUTH);

	evScene(0,6,5);

	evFrameWait(250);

	mes.OpenMessage("Wasurerareta.msg",100);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(250);

	mes.CloseMessage();

	for(a = 0;a <= 3;a ++){
		npDelete(a);
	}

	mcShow(1);
	mcDir(SOUTH);
	evScene(0,6,4);

	evSet(206,1);

	return 1;
}


//---�암��ጴ�A�Y���ꂽ��ՁA�V���o�[�v�����g
CREVENTLONG6_API int creventWasurerareta_SP(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	npPos(0,10,15);
	npDir(0,SOUTH);
	npPos(1,9,15);
	npDir(1,SOUTH);
	npPos(2,9,14);
	npDir(2,SOUTH);
	npPos(3,10,14);
	npDir(3,WEST);

	evScene(2,10,17);

	evFrameWait(250);
	mes.OpenMessage("Wasurerareta.msg",101);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(150);
	npDir(1,WEST);
	evFrameWait(150);
	npDir(2,WEST);
	evFrameWait(250);
	npMove(2,-1,0);
	evFrame();
	evFrameWait(250);
	//---�ǂ�ł݂��
	mes.ReadDraw();

	evFrameWait(250);
	npMove(2,-1,0);
	evFrame();
	evFrameWait(250);
	npDir(2,NORTH);
	//---�V���o�[�v�����g
	evFrameWait(1500);
	mes.ReadDraw(2);
	//---������
	evFrameWait(500);
	npDir(1,SOUTH);
	evFrameWait(250);
	npMove(1,0,1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	mes.CloseMessage();

	for(a = 0;a <= 3;a ++){
		npDelete(a);
	}

	mcShow(1);
	mcDir(SOUTH);
	evScene(2,10,15);

	evSet(207,1);

	return 1;
}


//---�암��ጴ�A�Y���ꂽ��ՁA�����Ă���@�B
CREVENTLONG6_API int creventWasurerareta_MoveingMachin(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	npPos(0,25,10);
	npDir(0,EAST);
	npPos(1,25,11);
	npDir(1,EAST);
	npPos(2,24,11);
	npDir(2,EAST);
	npPos(3,23,10);
	npDir(3,EAST);

	evScene(5,23,10);

	evFrameWait(500);
	for(a = 0;a < 5;a ++){
		mcMove(1,0);
		evFrame();
	}

	evFrameWait(250);
	for(a = 0;a < 4;a ++){
		if(a < 3)
			npMove(1,1,0);
		else
			npMove(1,0,-1);
		evFrame();
	}
	evFrameWait(250);

	//---�Ȃ񂾂����
	mes.OpenMessage("Wasurerareta.msg",102);
	mes.ReadDraw();

	//---���i������
	evFrameWait(250);
	npMove(0,1,0);
	evFrame();
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);

	//---�����̋@�B
	for(a = 0;a < 5;a ++){
		if(a < 1)
			npMove(3,1,0);
		else if(a < 2)
			npMove(3,0,-1);
		else
			npMove(3,1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(250);

/*	for(a = 0;a <1;a ++){
		npMove(2,1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);
	*/
	mes.ReadDraw();

	//---�҂��҂�
	evFrameWait(500);
	npMove(2,0,-1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();

	//---�Ȃ�œ����Ă�́H
	evFrameWait(2000);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(2,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	mes.CloseMessage();

	for(a = 0;a <= 3;a ++){
		npDelete(a);
	}

	mcShow(1);
	mcDir(NORTH);
	evScene(5,26,10);

	evSet(208,1);

	return 1;
}

//---�암��ጴ�A�Y���ꂽ��ՁA����t�H�[����
CREVENTLONG6_API int creventWasurerareta_VSFollne(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	npPos(0,18,26);
	npDir(0,NORTH);
	npPos(1,17,26);
	npDir(1,NORTH);
	npPos(2,17,27);
	npDir(2,NORTH);
	npPos(3,18,27);
	npDir(3,NORTH);

	evScene(7,18,26);
	crmusicPlay(CRMUSIC_CRAYSIVE);

	//---�t�H�[�����I
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(0,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.OpenMessage("Wasurerareta.msg",103);
	mes.ReadDraw();
	evFrameWait(250);

	//---�U�����
	npDir(5,WEST);
	evFrameWait(500);
	npDir(5,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	for(a = 0;a < 5;a ++){
		if(a < 2)
			npMove(1,0,-1);
		if(a > 1 && a < 4)
			npMove(2,0,-1);

		if(a == 0){
		} else if(a < 3)
			npMove(3,0,-1);
		else if(a < 5)
			npMove(3,1,0);
		evFrame();
	}
	//---�搶�I
	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---�Ȃ�
	evFrameWait(1000);
	mes.ReadDraw();

	//---�A�[�W�F���I
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---�Ȃ�ŁI�H
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(1000);
	npDir(4,WEST);
	evFrameWait(1000);
	mes.ReadDraw();

	//---�H
	evFrameWait(500);
	mes.ReadDraw();

	//---���ꂾ����
	evFrameWait(500);
	for(a = 0;a < 2;a ++){
		npMove(4,-1,0);
		evFrame();
		evFrameWait(500);
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);

	//---���������ɂ��Ƃ���
	npMove(1,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---���낻��
	evFrameWait(1000);
	npDir(4,NORTH);
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(1000);
	npMove(4,0,-1);
	evFrame();
	evFrameWait(1000);
	mes.ReadDraw();
	//---�͂�
	evFrameWait(500);
	npDir(5,WEST);
	evFrameWait(500);
	npDir(5,NORTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);

	//---�҂��āI
	mes.ReadDraw();
	evFrameWait(2000);
	mes.ReadDraw(2);

	//---������
	evFrameWait(500);
	npMove(0,0,-1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1500);
	mes.ReadDraw();

	//---���j��ς���H
	evFrameWait(500);
	mes.ReadDraw(3);
//	evFrameWait(2000);
//	mes.ReadDraw(3);

	//---�N���C�V���s��
	evFrameWait(500);
	for(a = 0;a < 4;a ++){
		npMove(4,0,-1);
		evFrame();
		evFrameWait(500);
	}
	npDelete(4);

	//---�N���C�V����|���ɂ�
	mes.ReadDraw();
	evFrameWait(500);

	//---����
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(5,0,-1);
		else
			npMove(5,-1,0);
		evFrame();
	}
//	npDir(5,WEST);
//	evFrameWait(250);
//	npMove(5,-1,0);
//	evFrame();

	evFrameWait(250);
	npDir(5,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---�i�b�N����
	evFrameWait(250);
	for(a = 0;a < 3;a ++){
		if(a < 1)
			npMove(2,0,-1);
		else if(a < 2)
			npMove(2,-1,0);
		evFrame();
	}
	npDir(2,NORTH);

	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(3,0,-1);
		else if(a < 2)
			npMove(3,-1,0);
		evFrame();
	}
	npDir(3,NORTH);
	for(a = 0;a < 1;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(2);

	//---�z���
	evFrameWait(500);
	mes.ReadDraw(2);

	//---���ł�
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(250);
	npMove(1,0,-1);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---��������
	evFrameWait(500);
	mes.ReadDraw(3);

	//---�o��H
	evFrameWait(500);
	mes.ReadDraw();

	//---�����Ȃ��I
	evFrameWait(500);
	npMove(0,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(250);
	mes.ReadDraw();

	//---���O��
	evFrameWait(500);
	mes.ReadDraw();

	//---��������
	evFrameWait(500);
	npDir(5,WEST);
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	npDir(5,NORTH);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---�����H
	evFrameWait(500);
	mes.ReadDraw();

	//---�A�Y�O���C�͋�������
	evFrameWait(500);
	npDir(5,WEST);
	evFrameWait(250);
	npDir(5,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(3);
	//---�����܂ł���
	evFrameWait(250);
	npMove(3,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---�N����
	evFrameWait(500);
	mes.ReadDraw();

	//---�݂�Ȃ������ɍs������
	evFrameWait(250);
	npMove(2,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	//---���i���������܂���
	evFrameWait(1000);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw();
	//---����Ȃ�
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---���Ȃ����āA
	crmusicFadeOut();
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	crmusicPlay(CRMUSIC_SILENT);
	npMove(0,0,-1);
	evFrame();
	evFrameWait(100);

	//---�o�g��
	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = CRMUSIC_DRAGONBREATH;
	BattleInfo.Enemy[0].Enemy = 178;
	BattleInfo.Enemy[0].x = 6;
	BattleInfo.Enemy[0].y = 8;
	BattleInfo.Enemy[1].Enemy = -1;
	BattleInfo.Enemy[1].x = 10;
	BattleInfo.Enemy[1].y = 8;
	BattleInfo.Enemy[2].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	evField(0,1);

	npPos(5,17,20);

	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}

	//---����
	evFrameWait(250);
	npMove(5,0,-1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);


	//---�|���
	//---�ϔO����
	npMove(1,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	//---�����̂���I
	evFrameWait(250);
//	npDir(1,EAST);
//	evFrameWait(250);
	mes.ReadDraw();

	//---�����ˁA�ł�
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---���i�����s��
	evFrameWait(250);
	for(a = 0;a < 8;a ++){
		npMove(0,0,-1);
		evFrame();
	}
	npDir(3,WEST);
	evFrameWait(250);

	//---�T���B�A�[
	for(a = 0;a < 3;a ++){
		if(a < 1)
			npMove(3,-1,0);
		else
			npMove(3,0,-1);
		evFrame();
	}
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(3,NORTH);
	npDir(2,EAST);
	evFrameWait(250);

	//---�i�b�N
	for(a = 0;a < 5;a ++){
		npMove(3,0,-1);
		if(a < 2)
			npMove(2,1,0);
		else if(a < 4)
			npMove(2,0,-1);
		evFrame();
	}
	evFrameWait(250);
	npDir(2,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);
	for(a = 0;a < 8;a ++){
		npMove(2,0,-1);
		evFrame();
	}
	//---���Ƃ�
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(1,EAST);
	evFrameWait(250);
	for(a = 0;a < 3;a ++){
		if(a < 1)
			npMove(1,1,0);
		else
			npMove(1,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	for(a = 0;a < 8;a ++){
		npMove(1,0,-1);
		evFrame();
	}

	evFrameWait(500);
	for(a = 0;a <= 4;a ++){
		npDelete(a);
	}

	for(a = 0;a < 16;a ++){
		mcMove(0,-1);
		evFrame();
	}
	mes.CloseMessage();

	evFrameWait(1000);

	//---�ŉ��w
	crfieldChangeScene(8,14,20);
	npPos(4,14,9);
	npDir(4,NORTH);
	evScene(8,14,19);

	evFrameWait(500);
	npPos(0,14,21);
	npDir(0,NORTH);
	crmusicPlay(CRMUSIC_CRAYSIVE);

	for(a = 0;a < 27;a ++){
		if(a < 8)
			npMove(0,0,-1);

		if(a < 3){
		} else if(a == 3){
			npPos(3,14,21);
			npDir(3,NORTH);
			npMove(3,0,-1);
		} else if(a < 10)
			npMove(3,0,-1);
		else if(a < 11)
			npMove(3,1,0);
		else
			npDir(3,NORTH);

		if(a < 7){
		} else if(a == 7){
			npPos(2,14,21);
			npDir(2,NORTH);
		} else if(a < 14)
			npMove(2,0,-1);
		else if(a < 16)
			npMove(2,-1,0);
		else if(a < 17)
			npMove(2,0,-1);

		if(a < 17){
		} else if(a == 17){
			npPos(1,14,21);
			npDir(1,NORTH);
		} else if(a < 24)
			npMove(1,0,-1);
		else if(a < 25)
			npMove(1,-1,0);
		else if(a < 27)
			npMove(1,0,-1);

		evFrame();
	}
	for(a = 0;a < 5;a ++){
		mcMove(0,-1);
		evFrame();
	}

	evFrameWait(500);
	npMove(0,0,-1);
	evFrame();
	evFrameWait(250);

	mes.OpenMessage("Wasurerareta.msg",104);
	mes.ReadDraw();

	//---�o�債�Ă��炤��
	evFrameWait(250);
	npMove(1,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---�搶
	evFrameWait(250);
	npMove(3,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();
	//---�ق��ĂȂ��ŁI
	evFrameWait(250);
	npMove(2,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---���傤��
	evFrameWait(2000);
	npMove(4,0,-1);
	evFrame();
	evFrameWait(2000);
	mes.ReadDraw();

	evFrameWait(1000);
	mcMove(0,-1);
	evFrame();

	evFrameWait(1000);

	//---�U������A�����O��������
	npDir(4,WEST);
	evFrameWait(500);
	npDir(4,SOUTH);
	evFrameWait(1000);

	evReadObject(5,"Crasive2.acf");
	evFrameWait(250);
	npPos(5,14,8);
	npDir(5,NORTH);
	evFrameWait(1000);

	//---�����
	mes.ReadDraw();
	evFrameWait(500);
	npMove(0,0,1,0);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();

	//---�ǂ������񂾂�I
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(150);
	npDir(2,EAST);
	evFrameWait(100);
	mes.ReadDraw(2);

	//---��������I
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---�N���C�V������
	npDelete(5);
	evFrameWait(250);
	evReadObject(5,"Crasive.acf");
	npDir(4,WEST);
	evFrameWait(500);

	for(a = 0;a < 5;a ++){
		npMove(4,-1,0);
		evFrame();
		if(a == 2)
			npDir(2,NORTH);
		evFrameWait(500);
	}
	evFrameWait(500);
	npDir(4,SOUTH);
	evFrameWait(500);

	for(a = 0;a < 1;a ++){
		npMove(4,0,1);
		evFrame();
		evFrameWait(500);
	}
	evFrameWait(500);
	npDelete(4);
	crsoundPlay(CRSOUND_KIDOU);
	evFrameWait(500);

	//---�ȁE�E�E
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	//---�q�}�͂Ȃ���
	evFrameWait(500);
	npDir(1,EAST);
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	mes.CloseMessage();

	evSet(209,1);

	mcShow(1);
	mcDir(SOUTH);
	evMap(10,0,195,341);

	return 1;
}

//---�S�E�A�A�����E�j�����I
CREVENTLONG6_API int creventZenuren_Moriuni(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	evField(0,1);
	mes.OpenMessage("Zenuren.msg",101);

	mes.ReadDraw(9);

	//---����́[�[�[�[�[�[�[
	evFrameWait(500);
	mes.ReadDraw(3);

	//---�ς�
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw(2);

	//---�܂���
	evFrameWait(1000);
	mes.ReadDraw(12);
	evFrameWait(500);
	mes.ReadDraw(2);

	mes.CloseMessage();

	evSet(212,1);

	//---�������炵�A�s�[�X�I�u���[��
	critemAddItem(233,-1);
	critemAddItem(210,1);

	return 1;
}

//---�����̈�ՁA�����ɗ�����
CREVENTLONG6_API int creventRyusa_TasukenikitaHatu(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	crfieldChangeMap(81,0,1,1);
	mcShow(0);
	npPos(0,16,21);
	npDir(0,NORTH);
	npPos(1,15,22);
	npDir(1,NORTH);
	npPos(2,18,22);
	npDir(2,NORTH);
	npPos(3,17,23);
	npDir(3,NORTH);
	npPos(4,19,23);
	npDir(4,NORTH);
	npPos(5,14,23);
	npDir(5,NORTH);

	evScene(0,16,23);

	evFrameWait(500);
	for(a = 0;a < 10;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(1500);
	for(a = 0;a < 10;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(250);
	mes.OpenMessage("RyusanoIseki.msg",101);
	mes.ReadDraw(4);
	evFrameWait(250);

	for(a = 0;a <= 5;a ++){
		npDelete(a);
	}
	mcShow(1);
	mcDir(SOUTH);
	evScene(1,24,2);

	evSet(213,1);

	return 1;
}


//---�����̈�ՁA��������
CREVENTLONG6_API int creventRyusa_Koegasuru(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	npPos(0,15,11);
	npDir(0,SOUTH);
	npPos(1,14,11);
	npDir(1,SOUTH);
	npPos(2,14,10);
	npDir(2,SOUTH);
	npPos(3,16,11);
	npDir(3,SOUTH);
	npPos(4,16,10);
	npDir(4,SOUTH);
	npPos(5,14,9 );
	npDir(5,SOUTH);

	mcShow(0);
	evScene(2,15,11);

	evFrameWait(100);
	mes.OpenMessage("RyusanoIseki.msg",102);
	mes.ReadDraw(2);
	//---���i������
	evFrameWait(250);
	npMove(0,0,1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);

	//---�s���Ă�낤��
	for(a = 0;a < 3;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(250);
	npMove(1,0,1);
	evFrame();
	npDir(1,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	//---�݂�ȍs��
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);
	for(a = 0;a < 12;a ++){
		if(a > 0 && a < 3)
			npMove(0,0,1);

		if(a < 8)
			npMove(1,0,1);
		else if(a < 9)
			npMove(1,1,0);
		else if(a < 10)
			npMove(1,0,1);

		if(a > 1)
			npMove(2,0,1);
		if(a > 2)
			npMove(3,0,1);
		if(a > 3)
			npMove(4,0,1);
		if(a > 3)
			npMove(5,0,1);

		evFrame();
	}
	for(a = 0;a < 6;a ++){
		mcMove(0,1);
		evFrame();
	}
	//---�ǂ������H
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);

	mes.ReadDraw();

	//---�݂�Ȍ���
	evFrameWait(250);
	npDir(2,EAST);
	evFrameWait(80);
	npDir(5,EAST);
	evFrameWait(80);
	npDir(3,WEST);
	evFrameWait(80);
	npDir(2,NORTH);
	evFrameWait(80);
	npDir(5,NORTH);
	evFrameWait(80);
	npDir(3,NORTH);
	evFrameWait(80);
	npDir(4,WEST);
	evFrameWait(250);
	npDir(4,NORTH);
	evFrameWait(500);

	mes.ReadDraw();
	//---���i���A����
	evFrameWait(500);
	for(a = 0;a < 3;a ++){
		npMove(0,0,1);
		evFrame();
	}
	evFrameWait(250);
	npDir(5,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(0,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	for(a = 0;a <= 5;a ++){
		npDelete(a);
	}

	mes.CloseMessage();

	mcShow(1);
	evScene(2,15,17);

	evSet(214,1);

	return 1;
}


//---�����̈�ՁA�K�[�[���~�o�I
CREVENTLONG6_API int creventRyusa_Gazell(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	npPos(0,21,33);
	npDir(0,NORTH);
	npPos(1,20,34);
	npDir(1,NORTH);
	npPos(2,22,34);
	npDir(2,NORTH);
	npPos(3,23,35);
	npDir(3,NORTH);
	npPos(4,24,33);
	npDir(4,NORTH);
	npPos(5,19,33);
	npDir(5,NORTH);

	npPos(6,20,21);
	npDir(6,EAST);
	npPos(7,20,22);
	npDir(7,EAST);
	npPos(8,17,27);
	npDir(8,NORTH);
	npPos(9,20,28);
	npDir(9,NORTH);
	npPos(10,22,27);
	npDir(10,NORTH);

	npPos(11,21,21);
	npDir(11,WEST);

	mcShow(0);
	//---
	evScene(3,21,35);

	evFrameWait(250);
	for(a = 0;a < 10;a ++){
		mcMove(0,-1);
		evFrame();
	}
	crmusicPlay(CRMUSIC_HEAT);
	evFrameWait(250);

	//---������I
	mes.OpenMessage("RyusanoIseki.msg",104);
	mes.ReadDraw();
	evFrameWait(250);

	npDir(11,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---�G�^�[�i���U�����
	evFrameWait(250);
	npDir(8,EAST);
	evFrameWait(80);
	npDir(9,EAST);
	evFrameWait(80);
	npDir(10,WEST);
	evFrameWait(80);
	npDir(8,SOUTH);
	evFrameWait(80);
	npDir(9,SOUTH);
	evFrameWait(80);
	npDir(10,SOUTH);

	for(a = 0;a < 9;a ++){
		mcMove(0,1);
		evFrame();
	}
	for(a = 0;a < 3;a ++){
		if(a < 2)
		npMove(8,0,1);
		if(a > 1)
			npMove(9,0,1);
		if(a < 3)
			npMove(10,0,1);
		evFrame();
	}

	evFrameWait(250);
	mes.ReadDraw();

	//---�Ȃ񂾂��Č����Ă��Ȃ�
	evFrameWait(250);
	npMove(1,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);

	//---�������
	evFrameWait(500);
	npMove(9,0,1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw(4);

	//---�킵��
	evFrameWait(250);
	npMove(5,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npMove(4,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---��l�s��
	evFrameWait(250);
	for(a = 0;a < 14;a ++){
		if(a < 10)
			npMove(5,0,-1);
		if(a < 1){
		} else if(a < 5)
			npMove(4,0,-1);
		else if(a < 9)
			npMove(4,-1,0);
		else
			npMove(4,0,-1);
		evFrame();
	}
	npDir(5,EAST);

	//---���x����
	evFrameWait(250);
	npMove(10,0,1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(4);
	evFrameWait(250);

	//---�o�g��
	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = CRMUSIC_BATTLE;
	BattleInfo.Enemy[0].Enemy = 186;
	BattleInfo.Enemy[0].x = 3;
	BattleInfo.Enemy[0].y = 7;
	BattleInfo.Enemy[1].Enemy = 122;
	BattleInfo.Enemy[1].x = 6;
	BattleInfo.Enemy[1].y = 9;
	BattleInfo.Enemy[2].Enemy = 121;
	BattleInfo.Enemy[2].x = 10;
	BattleInfo.Enemy[2].y = 8;
	BattleInfo.Enemy[3].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	evField(0,1);

	npPos(8,20,24);
	npDir(8,SOUTH);
	npPos(9,18,23);
	npDir(9,SOUTH);
	npDelete(10);

	npDir(6,EAST);
	npDir(7,SOUTH);
	npDir(11,WEST);

	npPos(0,20,28);
	npDir(0,NORTH);
	npPos(1,19,28);
	npDir(1,NORTH);
	npPos(2,21,29);
	npDir(2,NORTH);
	npPos(3,18,30);
	npDir(3,NORTH);

	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}

	evFrameWait(250);

	for(a = 0;a < 6;a ++){
		mcMove(0,-1);
		evFrame();
	}

	for(a = 0;a < 4;a ++){
		if(a < 2)
			npMove(0,0,-1);
		if(a && a < 3)
			npMove(1,0,-1);
		if(a > 1)
			npMove(2,0,-1);
		if(a > 1)
			npMove(3,0,-1);
		evFrame();
	}

	evFrameWait(250);
	mes.ReadDraw(3);
	evFrameWait(250);

	//---�o�g��
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = CRMUSIC_BATTLE;
	BattleInfo.Enemy[0].Enemy = 186;
	BattleInfo.Enemy[0].x = 3;
	BattleInfo.Enemy[0].y = 7;
	BattleInfo.Enemy[1].Enemy = 187;
	BattleInfo.Enemy[1].x = 6;
	BattleInfo.Enemy[1].y = 9;
	BattleInfo.Enemy[2].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	evField(0,1);

	npDelete(8);
	npDelete(9);
	npDelete(6);
	npDelete(7);

	npPos(4,22,23);
	npDir(4,WEST);
	npPos(5,16,21);
	npDir(5,SOUTH);
	npPos(5,21,21);
	npPos(11,19,21);
	npDir(11,SOUTH);

	npPos(0,19,25);
	npDir(0,NORTH);
	npPos(1,17,24);
	npDir(1,EAST);
	npPos(2,20,26);
	npDir(2,NORTH);
	npPos(3,18,26);
	npDir(3,NORTH);

	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}

	evFrameWait(250);
	mcMove(0,-1);
	evFrame();
	//---������
	evFrameWait(250);
	npDir(1,NORTH);
	crmusicFadeOut();
	evFrameWait(500);
	int old = ef->SetMoveSpeed(2);
	for(a = 0;a < 8;a ++){
		mcMove(0,-1);
		evFrame();
	}
	for(a = 0;a < 8;a ++){
		mcMove(-1,0);
		evFrame();
	}
	for(a = 0;a < 6;a ++){
		mcMove(0,1);
		evFrame();
	}
	for(a = 0;a < 6;a ++){
		mcMove(1,0);
		evFrame();
	}
	ef->SetMoveSpeed(old);
	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(250);
	npDir(1,SOUTH);
	crmusicPlay(CRMUSIC_SILENT);
	evFrameWait(250);
	mes.ReadDraw();

	//---��������v�I�H
	evFrameWait(750);
	for(a = 0;a < 3;a ++){
		npMove(0,0,-1);

		if(a == 0)
			npDir(1,EAST);
		if(a == 1)
			npDir(1,NORTH);
		if(a == 2)
			npDir(4,NORTH);
		if(a == 1)
			npDir(5,WEST);
		evFrame();
	}
	evFrameWait(250);
	crmusicPlay(CRMUSIC_SEEK);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	//---�R�������̐l��
	evFrameWait(250);
	npDir(1,NORTH);
	for(a = 0;a < 3;a ++){
		npMove(1,0,-1);
		evFrame();
	}
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---�i�b�N
	for(a = 0;a < 3;a ++){
		npMove(2,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---�T���B�A�[
	for(a = 0;a < 3;a ++){
		npMove(3,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---����ȂƂ���܂�
	evFrameWait(250);
	npDir(11,WEST);
	evFrameWait(500);
	npDir(11,SOUTH);
	evFrameWait(250);
	npDir(11,EAST);
	evFrameWait(500);
	npDir(11,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---�킽���E�E�E
	evFrameWait(1250);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---�̂̂���
	evFrameWait(1000);
	mes.ReadDraw(2);

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---�킽���ɂ�
	evFrameWait(500);
	mes.ReadDraw(2);
	//---����������
	evFrameWait(500);
	mes.ReadDraw(2);

	//---�U�N��
	evFrameWait(500);
	mes.ReadDraw(3);

	//---����Ȃӂ���
	evFrameWait(800);
	mes.ReadDraw(2);
	//---���ӂ��[��
	evFrameWait(500);
	mes.ReadDraw();

	//---���āA����ȏꏊ����
	evFrameWait(500);
	npDir(3,EAST);
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(4,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(1,SOUTH);

	//---���܂��Ă�
	evFrameWait(500);
	em->Put(21,36,2,113);
	em->Put(21,37,2,113);
//	em->Put(21,38,0,33);
	for(a = 0;a < 11;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---�T���B�A�[����
	for(a = 0;a < 15;a ++){
		if(a < 10)
			npMove(3,0,1);
		else if(a < 13)
			npMove(3,1,0);
		else
			npMove(3,0,1);
		evFrame();
	}
	evFrameWait(1000);
	crmusicPlay(CRMUSIC_SILENT);
	mes.ReadDraw(2);
	//---�f�B�U������
	evFrameWait(250);

	for(a = 0;a < 18;a ++){
		if(a < 10)
			npMove(1,0,1);
		else if(a < 14)
			npMove(1,1,0);
		else
			npMove(1,0,1);

		if(a == 6)
			npDir(3,WEST);
		if(a == 7)
			npDir(3,NORTH);
		if(a == 13)
			npMove(3,-1,0);
		if(a == 14)
			npDir(3,SOUTH);
		if(a == 15)
			npDir(3,EAST);

		evFrame();
	}
	evFrameWait(1000);
	mes.ReadDraw();
	//---�т��Ƃ����Ȃ�
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(250);

	npDir(0,SOUTH);
	npDir(2,SOUTH);
	npDir(4,SOUTH);
	npDir(5,SOUTH);
	npDir(11,SOUTH);
	for(a = 0;a < 11;a ++){
		mcMove(0,-1);
		evFrame();
	}
	//---�C�z
	evFrameWait(500);
	npMove(0,0,1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	crmusicPlay(CRMUSIC_CRAYSIVE);
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	evReadObject(0,"Crasive.acf");
	npPos(22,21,45);
	npDir(22,NORTH);
	npDir(3,SOUTH);
	for(a = 0;a < 2;a ++){
		mcMove(1,0);
		evFrame();
	}
	for(a = 0;a < 14;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(500);

	//---�N���C�V������
	for(a = 0;a < 6;a ++){
		npMove(22,0,-1);
		evFrame();
		evFrameWait(500);
	}
	mes.ReadDraw();

	//---��������
	evFrameWait(1000);
	mes.ReadDraw();

	//---�����߂�C�H
	npPos(0,22,30);
	evFrameWait(500);
	for(a = 0;a < 5;a ++){
		npMove(0,0,1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();

	//---�����
	evFrameWait(2000);
	mes.ReadDraw();

	evFrameWait(1000);
	npDir(22,WEST);
	evFrameWait(1000);
	npDir(22,SOUTH);
	evFrameWait(1000);
	npMove(22,0,1);
	evFrame();
	//---�҂��āI
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	for(a = 0;a < 5;a ++){
		npMove(22,0,1);
		evFrame();
		evFrameWait(500);
	}
	crmusicFadeOut();
	npDelete(22);

	//---�J���Ȃ�
	evFrameWait(500);
	for(a = 0;a < 3;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(500);
	npDir(0,WEST);
	evFrameWait(500);
	npDir(3,EAST);
	evFrameWait(1000);
	crmusicPlay(CRMUSIC_SILENT);
	mes.ReadDraw();
	evFrameWait(3000);

	//---�_���I
	mes.ReadDraw(2);

	//---���[��
	evFrameWait(500);
	for(a = 0;a < 10;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();

	//---��
	npPos(0,21,35);
	npDir(0,NORTH);
	evFrameWait(250);
	for(a = 0;a < 10;a ++){
		npMove(0,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	for(a = 0;a < 22;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(2000);
	npPos(3,20,26);
	npDir(3,NORTH);
	for(a = 0;a < 22;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);

	evSet(215,1);
	evReloadMap(1);
	mcShow(1);
	mcDir(SOUTH);

	evScene(3,21,27);

	mes.CloseMessage();

	return 1;
}

//---�����̈�ՁA�V���f�B�o��I
CREVENTLONG6_API int creventRyusa_Cindy(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	npPos(0,21,35);
	npDir(0,EAST);
	npPos(1,20,34);
	npDir(1,SOUTH);
	npPos(2,21,34);
	npDir(2,SOUTH);
	npPos(3,22,33);
	npDir(3,SOUTH);
	npPos(25,23,32);
	npDir(25,SOUTH);
	npPos(6,21,45);
	npDir(6,NORTH);
	npPos(26,21,45);
	npDir(26,NORTH);
	npPos(27,21,45);
	npDir(27,NORTH);
	evReadObject(14,"Cindy.acf");

	evScene(3,21,37);
	evFrameWait(500);

	mes.OpenMessage("RyusanoIseki.msg",105);
	mes.ReadDraw(2);
	//---���������傤�I
	evFrameWait(500);
	mes.ReadDraw(2);

	//---��
	evFrameWait(500);
	crsoundPlay(CRSOUND_ANAAKU);
	evFrameWait(1000);

	//---�J��
	em->Put(21,37,2,1024);
	crsoundPlay(CRSOUND_ATACK4);
	evFrameWait(300);
	em->Put(21,36,2,1024);
	crsoundPlay(CRSOUND_ATACK4);
	evFrameWait(300);
	npDir(0,SOUTH);
	evFrameWait(100);
	npDir(24,SOUTH);
	evFrameWait(250);

	mes.ReadDraw();

	//---�V���f�B�o��
	evFrameWait(250);
	for(a = 0;a < 8;a ++){
		npMove(6,0,-1);
		evFrame();
	}
	crmusicPlay(CRMUSIC_DRAGONBREATH);
	evFrameWait(250);
	mes.ReadDraw(2);
	//---�V���f�B����I�H
	evFrameWait(250);
	npMove(3,0,1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	mes.ReadDraw(3);

	//---���������̒���
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---�}�[�N�X����
	evFrameWait(250);
	for(a = 0;a < 7;a ++){
		npMove(26,0,-1);
		if(a)
			npMove(27,0,-1);

		evFrame();
	}
	evFrameWait(500);

	npDelete(15);
	npDelete(19);
	npDelete(20);
	npDelete(21);
	npDelete(24);
	npDelete(25);

	npPos(0,22,30);
	npDir(0,WEST);
	npPos(1,23,32);
	npDir(1,WEST);
	npPos(2,21,33);
	npDir(2,NORTH);
	npPos(3,22,31);
	npDir(3,WEST);
	npPos(4,20,33);
	npDir(4,NORTH);
	npPos(5,20,29);
	npDir(5,SOUTH);
	npPos(23,21,29);
	npDir(23,SOUTH);

	npPos(6,19,30);
	npDir(6,EAST);
	npPos(26,19,31);
	npDir(26,EAST);
	npPos(27,19,32);
	npDir(27,EAST);

	evFadeOut();
	crfieldChangeScene(3,21,32);
	em->Put(21,36,2,1024);
	em->Put(21,37,2,1024);
	evFieldNoFlip(0,1);
	evFadeIn();
//	evScene(3,21,32);

	//---�v���Ԃ肾��
	evFrameWait(500);
	mes.ReadDraw(2);

	//---���C�[����
	evFrameWait(500);
	npMove(26,1,0);
	evFrame();
	evFrameWait(250);
	npDir(26,NORTH);
	evFrameWait(250);

	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	//---�킵��
	evFrameWait(1000);
	mes.ReadDraw();

	//---�V���f�B�́A
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(26,EAST);
	evFrameWait(500);

	//---���̌�
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw();

	//---���������Ԃ�
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw(2);

	//---�ӂ���ƂȂ�
	evFrameWait(500);
	npMove(1,-1,0);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw(2);


	//---�������E�E�E
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---���l��
	evFrameWait(500);
	npDir(26,NORTH);
	evFrameWait(250);
	npDir(26,EAST);
	evFrameWait(250);
	npDir(26,SOUTH);
	evFrameWait(250);
	npDir(26,EAST);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---�N���X�t�B�[���h�̕��X��
	evFrameWait(250);
	npDir(26,NORTH);
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);

	mes.CloseMessage();

	evSet(217,1);
	evReloadMap(1);
	mcShow(1);
	evScene(3,21,33);

	prtRecoveryAll();

	return 1;
}

#define RANK_MAX 5

//---�i����
CREVENTLONG6_API int creventKakutojo(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	if(!evGet(222)){
		//---�͂��߂�
		evField(0,1);
		mes.FileMessage("kakutojo.msg",50,1);
		evField(0,1);
		mes.FileMessage("kakutojo.msg",51,1);
		evField(0,1);
		evSet(222,1);
	}

	//---�I��
	eistr *rankstr[] = {"�r","�`","�a","�b","�c","�d","�e"};
	int rank = evGet(224);
	eistr str[80],*p = str;

	if(rank == RANK_MAX + 1){
		//---�r�����N�N���A�Ȃ̂Ŗ����I
		evField(0,1);
		mes.FileMessage("kakutojo.msg",57,1);
		return 1;
	}

	sprintf(p,"�����N%s �ɒ��킷��;",rankstr[RANK_MAX - rank]);
	p += strlen(p);
	sprintf(p,"�����𕷂�;");

	CrSelectWindow win;
	int sel,fan;

	fan = (rank + 1) * 2000;

//	fan = 0;
//	rank = 3;

	do {
		crbaseMenuReset();
		win.Create(64,64,16,5,"�ǂ����܂����H",str);
		win.Paint();
		win.Refresh();
		crbaseMenuStart();

		sel = win.Select();

		if(sel == 0){
			//---�키�I
			if(evGet(270 + rank) == 0){
				//---�����x����
				eistr s[80];
				sprintf(s,
				"���u�����N%s�ɁA������ł��ˁB\\n;�@�o�^���� %d �t�@���ƂȂ�܂��v\\c;",
				rankstr[RANK_MAX - rank],fan);

				mes.CreateNewMessage();
				mes.Message(s);
				mes.Draw();
				mes.CloseMessage();

				crbaseMenuReset();
				evField(0,1);

				crbaseShowMoney(64,160);
				CrSelectWindow selwin;
				selwin.Create(64,64,10,5,"�����܂����H","����;����Ȃ�;");
				ew->Refresh();

				if(selwin.Select() == 0){
					if(crbaseGetMoney() < fan){
						//---����Ȃ��I
						evField(0,1);
						mes.FileMessage("kakutojo.msg",52,1);
						return 1;
					}
					//---������
					evSet(270 + rank,1);
					evField(0,1);
					mes.FileMessage("kakutojo.msg",53,1);
				} else {
					crbaseMenuReset();
					crbaseMenuStart();
					return 1;
				}
			}

			evField(0,1);

			//---�키�l���I��
			int party[MEMBER_MAX],kx,ky;

			for(a = 0,p = str;a < MEMBER_MAX;a ++){
				if(crcharaGetPartyMember(a) != NULL){
					party[a] = crcharaGetPartyMember(a)->Who();
					sprintf(p,"%s;",crcharaGetPartyMember(a)->GetName());
					p += strlen(p);
				} else {
					party[a] = 0;
				}
			}

			crbaseMenuReset();
			win.Create(64,64,16,9,"�N���킢�܂����H",str);
			win.Paint();
			win.Refresh();
			crbaseMenuStart();

			sel = win.Select();

			if(sel == -1){
				//---���~
				crbaseMenuReset();
				crbaseMenuStart();
				return 1;
			}

			mcShow(0);
			evScene(2,15,15);

#define KAK_ENEMY 6
			//---�o�g���I
			CR_BATTLEINFO BattleInfo;
			//---f:����Ȃ���
			int class_f[4][KAK_ENEMY] = {//�������A�G�i���o�[
				{95,-1},
				{98,96,-1},
				{103,103,-1},
				{0}
			};
			//---e:�����������߂ł�������
			int class_e[5][KAK_ENEMY] = {//�������A�G�i���o�[
				{152,-1},
				{133,-1},
				{134,135,134,-1},
				{136,137,-1},
				{0}
			};
			//---d:
			int class_d[5][KAK_ENEMY] = {//�������A�G�i���o�[
				{143,-1},
				{147,149,-1},
				{228,151,-1},
				{229,230,-1},
				{0}
			};
			//---c:
			int class_c[5][KAK_ENEMY] = {//�������A�G�i���o�[
				{231,-1},
				{162,-1},
				{126,233,126,-1},
				{232,234,-1},
				{0}
			};
			//---b:
			int class_b[5][KAK_ENEMY] = {//�������A�G�i���o�[
				{192,-1},
				{237,237,-1},
				{151,127,204,84,-1},
				{236,193,-1},
				{0}
			};
			//---a:
			int class_a[5][KAK_ENEMY] = {//�������A�G�i���o�[
				{240,-1},
				{241,172,172,-1},
				{242,160,-1},
				{203,193,-1},
				{0}
			};
			int enemy_count = 0,enemy[8],win;

			int *p_enemy;

			switch(rank){
			case 0:
				//---F
				p_enemy = &class_f[0][0];
				break;
			case 1:
				//---E
				p_enemy = &class_e[0][0];
				break;
			case 2:
				//---d
				p_enemy = &class_d[0][0];
				break;
			case 3:
				//---c
				p_enemy = &class_c[0][0];
				break;
			case 4:
				//---b
				p_enemy = &class_b[0][0];
				break;
			case 5:
				//---a
				p_enemy = &class_a[0][0];
				break;
			default:
				p_enemy = &class_f[0][0];
				break;
			}

			crmusicPlay(CRMUSIC_BATTLE);

			for(a = 0;a < MEMBER_MAX;a ++){
				pPartyInfo->PartyMember[a] = -1;
			}
			pPartyInfo->PartyMember[0] = party[sel] - 1;
			kx = crcharaGetPartyMember(0)->GetBattleFieldStartX();
			ky = crcharaGetPartyMember(0)->GetBattleFieldStartY();
			crcharaGetPartyMember(0)->SetBattleFieldStartPos(6,3);

			int olditem = crbatSetBattleItemMode(1);

			for(a = 0 , win = 1;*(p_enemy + a * KAK_ENEMY) != 0;a ++){
				memset(&BattleInfo,0,sizeof(BattleInfo));

				for(b = 0 , enemy_count = 0;*(p_enemy + a * KAK_ENEMY + b) != -1;b ++,enemy_count ++){
					enemy[b] = *(p_enemy + a * KAK_ENEMY + b);
				}

				BattleInfo.MapNumber = crfieldGetMapNumber();
				BattleInfo.SceneNumber = crfieldGetMapScene();
				BattleInfo.Music = 0;
				BattleInfo.ScreenEfect = CRINTOBAT_NONE;
				BattleInfo.FailOK = 1;
				BattleInfo.LimitTurn = 10;
				for(b = 0;b < enemy_count;b ++){
					BattleInfo.Enemy[b].Enemy = enemy[b];
					BattleInfo.Enemy[b].x = 6 - (enemy_count - 1) * 3 / 2
						+ (10 / enemy_count) * b + eiRnd(3 / enemy_count);
					BattleInfo.Enemy[b].y = 7 + eiRnd(4);
				}
				BattleInfo.Enemy[b].Enemy = -1;

				if(crbatEventBattle(&BattleInfo) != BATRET_WIN){
					//---�����I
					win = 0;
					break;
				}
				//---�k�o�Ƃl�b��
//				if(a != 2){
					CrCharacter *pChara = crcharaGetPartyMember(0);
					pChara->AddLP(pChara->GetMaxLP() * 250 / 1000);
//					pChara->AddMC(pChara->GetMaxMC() * 250 / 1000);
//				}

/*				for(b = 0;*(p_enemy + a * KAK_ENEMY + b) != -1;b ++){
					char s[50];
					sprintf(s,"%2d,%2d : %2d\n",a,b,enemy);
					eiDebugWriteFile(s);

				}*/
			}
			crbatSetBattleItemMode(olditem);

			evReloadMapMusic();
			mcShow(1);
			mcDir(NORTH);
			evScene(0,12,18);

			evFrameWait(100);

			if(win == 0){
				//---����
				evField(0,1);
				mes.FileMessage("kakutojo.msg",54,1);
			} else {
				//---�����I
				int item_list[] = {225,176,164,138,  75,187,228};
				mes.CreateNewMessage();
				sprintf(str,"���u�����N%s�����A���߂łƂ��������܂��I�@�V���Ȃ鏟�҂̒a���ł��I�I\\c;",
					rankstr[RANK_MAX - rank]);
				mes.Message(str);
				mes.Draw();

				mes.Message("���u���i�́A������ɂȂ�܂��v\\c;");
				mes.Draw();

				sprintf(str,"%s����ɓ��ꂽ�I\\c;",
					critemGetItemClass(item_list[rank])->GetName());
				mes.Message(str);
				mes.Draw();

				critemAddItem(item_list[rank]);

				rank ++;
				if(rank > RANK_MAX){
					//---���S���e
					mes.Message("���u���Ɍ���܂����I�@�S�N���X���S���e�ҁI�v\\c;");
					mes.Draw();
					mes.Message("���u���Ȃ����̋����́A�嗤���ɒm���邱�Ƃł��傤�B���߂łƂ��������܂��I�I�v\\c;");
					mes.Draw();
				} else {
					mes.Message("���u�V���Ȃ�N���X�ւ̒���A���҂����Ă��܂��v\\c;");
					mes.Draw();
				}
				mes.CloseMessage();

				evSet(224,rank);
			}
			evFrameWait(150);

			//---���ɖ߂�
			crcharaGetPartyMember(0)->SetBattleFieldStartPos(kx,ky);
			for(a = 0;a < MEMBER_MAX;a ++){
				pPartyInfo->PartyMember[a] = party[a] - 1;
			}
			sel = 0;
		} else if(sel == 1){
			//---����
			evField(0,1);
			mes.FileMessage("kakutojo.msg",51,1);
		}
	} while(sel == 1);
	crbaseMenuReset();
	crbaseMenuStart();

	return 1;
}
