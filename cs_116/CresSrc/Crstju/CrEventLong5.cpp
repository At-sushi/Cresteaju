/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrEventLong5.cpp ...Event functions

-----------------------------------------------------------*/


#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CREVENTLONG5

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#include "CrBase.h"
#include "CrBattle.h"
#include "CrEvent.h"
#include "CrEvCom.h"

//---game info
#define CR_GAMEINFO_EXTERNPOINTER
#include "CrGameInfo.h"

//---�R���X�^�[�g�I
CREVENTLONG5_API int crevent_ThirdStart(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	crmusicPlay(CRMUSIC_SILENT);

	crsoundPlay(CRSOUND_GS_SOUND,EISOUND_PLAYLOOP);
	evFrameWait(500);
	evFadeOut(2000);

	et->Delay2(2000);
	npPos(4,7,3);
	npDir(4,SOUTH);
	npPos(5,5,5);
	npDir(5,EAST);
	evFieldNoFlip(0,1);
	evFadeIn(2000);

	evFrameWait(500);
	mes.OpenMessage("Fillgalt.msg",113);
	mes.ReadDraw(2);

	//---�܂���
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(250);

	mes.ReadDraw();

	//---���f�̐X��
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);

	//---��
	evFrameWait(500);
	npDir(4,EAST);
	evFrameWait(250);
	npMove(4,1,0);
	evFrame();
	evFrameWait(250);
	npDir(4,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---���~�I
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(150);
	npDir(0,NORTH);
	evFrameWait(150);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw(2);

	//---���i���̘b�𕷂��Ă�
	evFrameWait(500);
	npDir(1,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(150);
	npDir(2,SOUTH);
	evFrameWait(150);
	mes.ReadDraw();

	//---������
	evFrameWait(500);
	mes.ReadDraw(3);

	//---�e���^�]
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(250);

	mes.ReadDraw(4);

	//---���肪�Ƃ�
	evFrameWait(500);
	npDir(0,NORTH);
	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(500);
	npDir(0,NORTH);
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);

	//---�N���C�V���̂���
	mes.ReadDraw();
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(2,EAST);
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);
	//---�Ȃ�ł��Ȃ�
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(150);
	npDir(3,EAST);
	evFrameWait(150);
	mes.ReadDraw(2);

	//---�����̖ړI��
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	npDir(4,WEST);
	evFrameWait(250);
	npMove(4,-1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();


	//---���~�O��
	evFrameWait(250);
	for(a = 0;a < 15;a ++){
		if(a < 3)
			npMove(4,-1,0);
		else if(a < 8)
			npMove(4,0,1);
		else
			npMove(4,1,0);

		if(a == 4)
			npDir(0,WEST);
		if(a == 9)
			npDir(0,SOUTH);
		if(a == 13)
			npDir(0,EAST);

		if(a == 6)
			npDir(1,WEST);
		if(a == 9)
			npDir(1,SOUTH);
		if(a == 11)
			npDir(1,EAST);

		if(a == 5)
			npDir(2,WEST);
		if(a == 9)
			npDir(2,SOUTH);
		if(a == 12)
			npDir(2,EAST);

		if(a == 7)
			npDir(5,SOUTH);
		if(a == 10)
			npDir(5,EAST);
		evFrame();
	}
	npShow(4,0);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(1500);

	evShake(250,2);
	npDir(0,WEST);
	crsoundPlay(CRSOUND_GS_TUIRAKUMAE,EISOUND_PLAYLOOP);
	evShake(250,4);
	npDir(1,EAST);
	evShake(250,6);
	npDir(2,EAST);
	evShake(250,8);
	npDir(5,NORTH);

	evShake(250,12);
	npDir(0,NORTH);
	evShake(250);
	npDir(2,SOUTH);
	evShake(250);
	npDir(1,SOUTH);
	evShake(500);

	mes.ReadDraw(2);

	//---���݂܂���E�E�E
	evShake(500,18);
	mes.ReadDraw();
	evShake(500,20);
	evShake(500,24);

	//---�ė�
	evFadeOut(2000);
	et->Delay2(1000);
	crsoundStop(CRSOUND_GS_TUIRAKUMAE,0);
	crsoundStop(CRSOUND_GS_SOUND,0);

	crsoundPlay(CRSOUND_GS_TUIRAKU);
	et->Delay2(3000);

	npPos(0,8,6);
	npDir(0,EAST);
	npPos(1,6,5);
	npDir(1,EAST);
	npPos(2,7,3);
	npDir(2,SOUTH);
	npPos(5,2,4);
	npDir(5,EAST);
	evReadObject(5,"Tarai.acf");
	evFieldNoFlip(0,1);

	//---�������E�E�E
	evFadeIn(2000);
	evFrameWait(500);
	npDir(0,NORTH);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(3,SOUTH);
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(2,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(1000);

	//---���~�Q��
	npDir(4,WEST);
	for(a = 0;a < 6;a ++){
		npMove(4,-1,0);
		evFrame();
		if(a == 5)
			npDir(1,SOUTH);
	}
	npDir(4,NORTH);
	evFrameWait(150);
	mes.ReadDraw();
	evFrameWait(500);

	//---�������傤����
	npDir(2,SOUTH);
	npMove(2,0,1);
	evFrame();
	evFrameWait(150);
	npDir(2,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---�Ȃ�Ƃ��E�F�X�g�f�U�[�g��
	evFrameWait(500);
	npDir(3,SOUTH);
	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(800);
	mes.ReadDraw();
	evFrameWait(500);

	//---����
	npPos(0,9,5);
	npDir(0,NORTH);
	npDir(2,EAST);
	npPos(4,9,3);
	npDir(4,SOUTH);
	npPos(5,4,3);
	npDir(5,EAST);
	npDir(1,EAST);
	evReadObject(5,"Lizel.acf");

	evFadeOut(2000);
	evFieldNoFlip(0,1);
	et->Delay2(1000);
	evFadeIn(2000);

	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);

	mes.ReadDraw();

	//---������
	evFrameWait(500);
	npDir(0,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---�����
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(150);
	npDir(0,NORTH);
	evFrameWait(150);
	mes.ReadDraw(2);

	//---�N���c��l
	evFrameWait(250);
	npDir(4,WEST);
	evFrameWait(250);

	mes.ReadDraw();

	//---�I�W�T�}
	evFrameWait(250);
	npMove(4,-1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(5,SOUTH);
	evFrameWait(100);
	//---���i���B��
	for(a = 0;a < 3;a ++){
		if(a < 2)
			npMove(5,0,1);
		else
			npDir(5,EAST);

		if(a == 1)
			npDir(1,NORTH);
		if(a == 2)
			npDir(1,WEST);
		if(a == 2)
			npDir(2,NORTH);
		evFrame();
	}
	npDir(0,WEST);
	npDir(2,WEST);
	evFrameWait(150);
	npDir(3,WEST);
	evFrameWait(150);
	mes.ReadDraw(2);
	evFrameWait(250);

	mes.CloseMessage();

	evSet(170,1);

	mcShow(1);
	mcDir(SOUTH);
	evMap(10,0,57,94);

	//---�p�[�e�B�[�Ґ�
	//---�T���B�A�[�Ăђ��ԂɂȂ�
	{
		pPartyInfo->PartyMember[0] = 0;
		pPartyInfo->PartyMember[1] = 1;
		pPartyInfo->PartyMember[2] = 2;
		pPartyInfo->PartyMember[3] = 3;
		pPartyInfo->PartyMember[4] = -1;

		crcharaLoadFace(-1);
		for(a = 0;a < 4;a ++){
			crcharaCheckBattleFieldPos(a);
		}
	}
	prtRecoveryAll();

	return 1;
}


//---�_�̎R�A����
CREVENTLONG5_API int creventKaminoYama_Top(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	npPos(0,17,17);
	npDir(0,NORTH);
	npPos(1,16,17);
	npDir(1,NORTH);
	npPos(2,16,18);
	npDir(2,NORTH);
	npPos(3,17,19);
	npDir(3,NORTH);

	evScene(4,17,20);

	evFrameWait(250);
	npDir(2,EAST);
	evFrameWait(250);
	//---���H
	mes.OpenMessage("KaminoYama.msg",104);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(150);
	npDir(0,WEST);
	evFrameWait(100);
	npDir(1,SOUTH);
	evFrameWait(150);
	npDir(0,SOUTH);
	evFrameWait(250);
	//---����
	mes.ReadDraw(2);
	mes.CloseMessage();

	evFrameWait(500);

	{
		mes.CreateNewMessage(0,160,144,20,4,1);
		mes.OpenMessage("KaminoYama.msg",105);
		mes.ReadDraw();

		evFrameWait(250);
		npDir(0,EAST);
		evFrameWait(250);
		npDir(0,NORTH);
		evFrameWait(250);
		npDir(1,EAST);
		evFrameWait(150);
		npDir(2,NORTH);
		evFrameWait(100);
		npDir(1,NORTH);
		evFrameWait(250);

		mes.Paint();
		mes.ReadDraw();
		evFrameWait(250);

		mes.Paint();
		mes.ReadDraw();
		mes.CloseMessage();
	}
	//---�o�g��
	evFrameWait(500);

	//---�o�g��
	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = CRMUSIC_BOSSBATTLE1;
	BattleInfo.Enemy[0].Enemy = 148;
	BattleInfo.Enemy[0].x = 3;
	BattleInfo.Enemy[0].y = 9;
	BattleInfo.Enemy[2].Enemy = 150;
	BattleInfo.Enemy[2].x = 6;
	BattleInfo.Enemy[2].y = 6;
	BattleInfo.Enemy[1].Enemy = 148;
	BattleInfo.Enemy[1].x = 10;
	BattleInfo.Enemy[1].y = 8;
	BattleInfo.Enemy[3].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
//	BattleInfo.MapNumber = 1;
	evField(0,1);

	npPos(0,17,15);
	npPos(1,15,15);
	npPos(2,16,16);
	npPos(3,18,17);

	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}

	evFrameWait(250);
	for(a = 0;a < 4;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(500);
	npMove(0,0,-1);
	evFrame();
	evFrameWait(250);
	//---�|�����H
	mes.OpenMessage("KaminoYama.msg",106);
	mes.ReadDraw();
	mes.CloseMessage();
	evFrameWait(500);


	{
		mes.CreateNewMessage(0,160,144,20,4,1);
		mes.OpenMessage("KaminoYama.msg",107);
		mes.ReadDraw();
		mes.CloseMessage();
	}

	//---�܂�����
	evFrameWait(250);
	mes.OpenMessage("KaminoYama.msg",108);
	mes.ReadDraw();
	mes.CloseMessage();
	evFrameWait(500);

	{
		mes.CreateNewMessage(0,160,144,20,4,1);
		mes.OpenMessage("KaminoYama.msg",107);
		mes.ReadDraw();
		mes.CloseMessage();
	}

	//---�������Ă����I
	evFrameWait(250);
	mes.OpenMessage("KaminoYama.msg",109);
	mes.ReadDraw();
	mes.CloseMessage();
	evFrameWait(500);

	npPos(4,17,8);
	npDir(4,SOUTH);

	for(a = 0;a < 11;a ++){
		//---��߂�I
		{
			mes.CreateNewMessage(0,160,288,20,5,1);
			mes.OpenMessage("KaminoYama.msg",110 + a * 2);
			if(a == 5 || a == 10){
				mes.ReadDraw();

				evFrameWait(250);
				mes.Paint();
				mes.ReadDraw();
			} else if(a == 6){
				mes.ReadDraw();

				evFrameWait(250);
				mes.Paint();
				mes.ReadDraw();

				evFrameWait(250);
				mes.Paint();
				mes.ReadDraw();

				evFrameWait(250);
				mes.Paint();
				mes.ReadDraw();
			} else {
				mes.ReadDraw(10);
			}

			mes.CloseMessage();
		}
		evFrameWait(500);
		mes.OpenMessage("KaminoYama.msg",111 + a * 2);
		if(a == 6){
			//---�߁H
			mes.ReadDraw();
			evFrameWait(250);
			npMove(0,0,-1);
			evFrame();
			evFrameWait(250);
			mes.ReadDraw();
		} else {
			mes.ReadDraw(10);
		}

		if(a == 0){
			evFrameWait(250);
			for(b = 0;b < 5;b ++){
				mcMove(0,-1);
				evFrame();
			}
			for(b = 0;b < 3;b ++){
				npMove(0,0,-1);
				evFrame();
			}
		}

		mes.CloseMessage();
		evFrameWait(1000);
	}


	//---����̂�
	{
		mes.CreateNewMessage(0,160,288,20,5,1);
		mes.OpenMessage("KaminoYama.msg",132);
		mes.ReadDraw();
		mes.CloseMessage();
	}

	//---������
	evFrameWait(500);
	eiTime let;
	let.Reset();
	while(let.Get() < 1000){
		npShow(4,1);
		evFrameWait(25);
		npShow(4,0);
		evFrameWait(25);
	}
	evFrameWait(500);

	mes.OpenMessage("KaminoYama.msg",133);
	mes.ReadDraw();
	evFrameWait(1000);
	//---�E�E�E
	mes.ReadDraw();
	evFrameWait(500);

	for(a = 0;a < 4;a ++){
		npMove(1,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---����悤��
	npMove(1,0,-1);
	evFrame();
	evFrameWait(150);
	npDir(1,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	for(a = 0;a < 4;a ++){
		npMove(2,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	for(a = 0;a < 5;a ++){
		npMove(3,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---�o�C�c
	crfieldChangeMap(75,0,1,1);
	crfieldChangeScene(0,23,35);

	npPos(22,23,44);
	npDir(22,NORTH);
	npPos(23,22,45);
	npDir(23,NORTH);
	npPos(24,22,44);
	npDir(24,NORTH);
	npPos(25,24,46);
	npDir(25,NORTH);

	npPos(26,23,23);
	npDir(26,SOUTH);

	evScene(0,23,35);

	evFrameWait(500);
	for(a = 0;a < 10;a ++){
		for(b = 22;b <= 25;b ++){
			npMove(b,0,-1);
		}
		npMove(26,0,1);
		evFrame();
	}

	evFrameWait(1);
	mes.ReadDraw(7);
	evFrameWait(250);
	//---�j�̐l�ؗ�ȃt�b�g���[�N�ŋ���
	npDir(26,EAST);
	for(a = 0;a < 15;a ++){
		if(a < 1)
			npMove(26,1,0);
		else if(a < 3)
			npMove(26,0,1);
		else if(a < 4)
			npMove(26,-1,0);
		else
			npMove(26,0,1);

		if(a == 1)
			npDir(22,EAST);
		if(a == 3)
			npDir(22,SOUTH);

		if(a == 2)
			npDir(24,EAST);
		if(a == 4)
			npDir(24,SOUTH);
		if(a == 3)
			npDir(23,EAST);
		if(a == 4)
			npDir(23,SOUTH);

		if(a == 4)
			npDir(25,WEST);
		if(a == 5)
			npDir(25,SOUTH);
		evFrame();
	}

	//---�f�r��
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---�O���E���h�V�b�v
	crfieldChangeMap(59,0,1,1);

	npPos(0,20,6);
	npDir(0,EAST);
	npPos(1,19,8);
	npDir(1,WEST);
	npPos(2,17,8);
	npDir(2,EAST);
	npPos(3,20,5);
	npDir(3,EAST);
	npPos(4,22,6);
	npDir(4,WEST);
	npPos(5,23,7);
	npDir(5,WEST);

	evScene(0,21,9);

	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);

	//---�N���C�V���������ł�
	npDir(1,NORTH);
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	mes.ReadDraw(2);
	//---�E�E�E
	evFrameWait(1000);
	mes.ReadDraw();
	//---�킽��
	evFrameWait(1000);
	npDir(0,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---�Ȃ񂾂ƁI�H
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---�݂�Ȃ�
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(150);
	npDir(1,EAST);
	evFrameWait(150);
	npMove(1,1,0);
	evFrame();
	evFrameWait(150);
	npDir(1,NORTH);
	evFrameWait(150);
	mes.ReadDraw();

	//---������I
	evFrameWait(250);
//	npMove(0,0,1);
//	evFrame();
//	evFrameWait(150);
	mes.ReadDraw();

	//---���΂�
	evFrameWait(150);
	npMove(1,0,-1);
	evFrame();
	evFrameWait(150);
	mes.ReadDraw(5);

	//---���́E�E�E
	evFrameWait(500);
	mes.ReadDraw();

	//---�������
	evFrameWait(500);
	npDir(1,EAST);
	evFrameWait(250);
	mes.ReadDraw(2);
	//---������������
	evFrameWait(800);
	mes.ReadDraw(3);

	//---�f�B�U�o�Ă���
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);
	for(a = 0;a < 16;a ++){
		if(a < 4)
			npMove(1,0,1);
		else
			npMove(1,-1,0);

		if(a == 6)
			npDir(2,SOUTH);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();

	//---�i�b�N
	evFrameWait(750);
	for(a = 0;a < 6;a ++){
		if(a < 1)
			npMove(2,0,1);
		else if(a < 4)
			npMove(2,1,0);
		else
			npMove(2,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(2);

	//---���߂��
	evFrameWait(2000);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(3);
	//---�h���C
	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	//---�V���o�[�X�^�[
	evFrameWait(250);
	npDir(2,EAST);
	evFrameWait(250);
	mes.ReadDraw(3);
	evFrameWait(250);

	mes.CloseMessage();

	mcShow(1);
	mcDir(SOUTH);
	evMap(10,0,57,94);
	prtRecoveryAll();

	evSet(173,1);

	return 1;
}

//---�V���o�[�X�^�[�A�͂��߂�
CREVENTLONG5_API int creventSilverStar_First(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	crfieldChangeMap(77,0,1,1);

	npPos(21,30,43);
	npDir(21,NORTH);
	npPos(22,29,44);
	npDir(22,NORTH);
	npPos(23,31,43);
	npDir(23,NORTH);
	npPos(24,31,44);
	npDir(24,NORTH);
	evScene(0,30,43);

	evFrameWait(500);
	for(a = 0;a < 15;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(1500);
	for(a = 0;a < 15;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(500);
	npMove(21,0,-1);
	evFrame();
	evFrameWait(500);

	mes.OpenMessage("SilverStar.msg",100);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.CloseMessage();

	mcShow(1);
	for(a = 21;a <= 24;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}

	mcDir(NORTH);
	evScene(0,30,43);
	evSet(174,1);

	return 1;
}

//---�V���o�[�X�^�[�A����
CREVENTLONG5_API int creventSilverStar_Chocho(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	crfieldChangeScene(2,7,6);

	npPos(0,2,5);
	npDir(0,NORTH);
	npPos(1,7,5);
	npDir(1,WEST);
	npPos(2,9,4);
	npDir(2,WEST);
	npPos(3,8,5);
	npDir(3,WEST);
	npPos(4,7,6);
	npDir(4,WEST);

	evScene(2,7,6);
	evFrameWait(500);

	mes.OpenMessage("SilverStar.msg",101);
	mes.ReadDraw();

	//---�Ȃ񂾁H
	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(250);
	for(a = 0;a < 3;a ++){
		npMove(0,1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw(4);

	//---�ǂȂ������
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);

	for(a = 1;a <= 4;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}

	//---�O
	crfieldChangeScene(0,49,29);
	npPos(21,48,27);
	npDir(21,SOUTH);
	npPos(22,47,28);
	npDir(22,SOUTH);
	npPos(23,49,27);
	npDir(23,SOUTH);
	npPos(24,48,28);
	npDir(24,NORTH);
	evScene(0,48,29);

	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	npDir(23,WEST);
	evFrameWait(500);
	//---������
	mes.ReadDraw();
	evFrameWait(500);

	mcShow(1);
	for(a = 21;a <= 24;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}

	mcDir(SOUTH);
	evScene(0,48,27);
	evSet(174,2);

	mes.CloseMessage();

	return 1;
}

//---�V���o�[�X�^�[�A���~����
CREVENTLONG5_API int creventSilverStar_YumiCome(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	npPos(25,30,53);
	npDir(25,NORTH);
	npPos(26,29,54);
	npDir(26,NORTH);
	for(a = 0;a < 8;a ++){
		if(a < 7)
			npMove(25,0,-1);
		npMove(26,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.OpenMessage("SilverStar.msg",102);
	mes.ReadDraw();
	evFrameWait(250);


	mcShow(0);

	npPos(21,30,45);
	npDir(21,SOUTH);
	npPos(22,31,43);
	npDir(22,SOUTH);
	npPos(23,29,45);
	npDir(23,SOUTH);
	npPos(24,29,44);
	npDir(24,SOUTH);

	evScene(0,30,46);
	evFrameWait(500);
	//---��������
	mes.ReadDraw(2);
	evFrameWait(500);
	//---���ꂪ�E�E�E
	mes.ReadDraw();
	evFrameWait(500);

	//---�Ӂ[��
	crfieldChangeMap(59,0,1,1);

	npPos(0,20,6);
	npDir(0,EAST);
	npPos(1,17,8);
	npDir(1,EAST);
	npPos(2,19,8);
	npDir(2,WEST);
	npPos(3,20,5);
	npDir(3,EAST);
	npPos(4,22,6);
	npDir(4,WEST);
	npPos(5,21,8);
	npDir(5,NORTH);

	evScene(0,21,9);
	evFrameWait(500);
	mes.ReadDraw(5);
	//--���������Ƃ���
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);
	//---�������
	mes.ReadDraw();
	evFrameWait(500);

	//---���~�̌̋���
	//---�c�[���A��
	crfieldSetMainCharacter(1);

	crfieldChangeMap(10,0,1,0);
	mcShow(1);
	crfieldSetMainCharacter(4);
	mcDir(NORTH);
	ef->SetMoveEnything(1);
	evScene(0,61,175);
	evFrameWait(250);
	crmusicPlay(CRMUSIC_GS);
	for(a = 0;a < 4;a ++){
		mcDir(a);
		evFrameWait(150);
	}
	mcDir(EAST);
	crfieldSetMainCharacter(3);

	//---�t�B�[���h�I�I
	for(a = 0;a < 57;a ++){
		if(a < 2)
			mcMove(1,0);
		else if(a < 17)
			mcMove(0,1);
		else if(a < 37)
			mcMove(-1,0);
		else if(a < 54)
			mcMove(0,1);
		else if(a < 57)
			mcMove(1,0);
		evFrame();
	}

	//---���~�̌̋������I�I
	evFrameWait(100);
	crfieldSetMainCharacter(4);
	for(a = 3;a >= 0;a --){
		mcDir(a);
		evFrameWait(150);
	}
	evFrameWait(150);
	mcDir(SOUTH);
	crmusicPlay(CRMUSIC_FIELD1);
	ef->SetMoveEnything(0);

	npPos(NP_GS_CANTNUMBER,46,207);
	npDir(NP_GS_CANTNUMBER,NORTH);
	crfieldSetMainCharacter(1);

	mes.CloseMessage();

	//---���~���ԂɂȂ�
	{
		pPartyInfo->PartyMember[4] = 4;

		crcharaGetPartyMember(4)->SetBattleFieldStartPos(2,1);
		crcharaLoadFace(-1);
		crcharaCheckBattleFieldPos(4);
	}
	prtRecovery(4);

	evSet(171,1);
	evSet(174,3);
	evSet(175,1);
//46,208
	//61,175
	return 1;
}

//---�T���s�A�X�A�͂��߂�
CREVENTLONG5_API int creventSunpias_First(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	crmusicFadeOut();
	evFadeOut(2000);
	et->Delay2(1000);

	crfieldChangeMap(78,0,1,1);
	npPos(0,26,51);
	npDir(0,NORTH);
	npPos(1,28,52);
	npDir(1,NORTH);
	npPos(2,27,52);
	npDir(2,NORTH);
	npPos(3,26,53);
	npDir(3,NORTH);
	npPos(4,27,49);
	npDir(4,NORTH);

	crfieldChangeScene(0,27,40);
	evFieldNoFlip();
	evFadeIn(2000);

	evFrameWait(500);
	for(a = 0;a < 14;a ++){
		if(a > 0 && a < 14)
			npMove(0,0,-1);
		if(a > 1 && a < 14)
			npMove(1,0,-1);
		if(a > 1 && a < 14)
			npMove(2,0,-1);
		if(a > 1 && a < 14)
			npMove(3,0,-1);
		if(a < 12)
			npMove(4,0,-1);

		evFrame();
	}
	evFrameWait(1000);
	for(a = 0;a < 16;a ++){
		mcMove(0,-1);
		evFrame();
	}
	for(a = 0;a < 10;a ++){
		mcMove(1,0);
		evFrame();
	}
	for(a = 0;a < 16;a ++){
		mcMove(0,1);
		evFrame();
	}
	for(a = 0;a < 10;a ++){
		mcMove(-1,0);
		evFrame();
	}

	evFrameWait(500);
	npDir(0,WEST);
	evFrameWait(500);
	npDir(0,NORTH);
	evFrameWait(500);
	npDir(0,EAST);
	evFrameWait(500);
	npDir(0,NORTH);
	evFrameWait(500);

	//---���̐ՁH
	mes.OpenMessage("Sunpias.msg",100);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	//---���̉��̐X
	mes.ReadDraw();
	evFrameWait(500);
	mes.CloseMessage();

	for(a = 0;a < 15;a ++){
		if(a > 3)
			npMove(0,0,-1);
		if(a > 5)
			npMove(1,0,-1);
		if(a > 4)
			npMove(2,0,-1);
		if(a > 4)
			npMove(3,0,-1);

		npMove(4,0,-1);

		evFrame();
	}
	evFrameWait(1000);

	//---�X��
	mcShow(1);
	mcDir(NORTH);
	evMap(79,0,6,24);

	evSet(176,1);

	return 1;
}

//25,9,= 98

ei_s32 SunpiasbatCallBack1(int turn,int action,int number,
				  ei_u32 com,CrCharacter *chara)
{
	CR_BATTLECOMMAND *pCommand = (CR_BATTLECOMMAND *)com;
	CrBattleCharacter *pChara = (CrBattleCharacter *)chara;
	int crnum = BATTLECHARA_STARTENEMY;

	if(action == 3){
/*		if(number == 0){
			if(turn == 1){
				crbatDrawSceneWhile(500);
				CrMesManager mes;
				mes.CreateNewMessage(-1,-1,32,24,5);
				mes.OpenMessage("Cresfield.msg",141);
				mes.ReadMessage();
				mes.Draw();
				mes.CloseMessage();
			}
		} else if(number == 1){
			if(turn == 0){
				crbatDrawSceneWhile(250);

				crbatBeginMovingCamera(0,
					0.4f,0.4f,2.0f,
					6,6.0f,0.0f);

				crbatDoMovingCamera(1000);
				et->Wait2(WAIT_AFTERMOVECAMERA);

				CrMesManager mes;
				mes.CreateNewMessage(-1,-1,32,24,5);
				mes.OpenMessage("Cresfield.msg",139);
				mes.ReadMessage();
				mes.Draw();

				crbatBeginMovingCamera(0,
					2.0f,2.0f,4.0f,
					11,11.0f,0.0f);
				crbatDoMovingCamera(1000);
				et->Wait2(WAIT_AFTERMOVECAMERA);

				mes.ReadMessage();
				mes.Draw();
				mes.CloseMessage();
			}
		}
		return 1;*/
	}

	if(action == 1){
		if(number == 0){
			//---���~
			if(turn == 0){
				pCommand->Main = BAT_COMMAND_WAIT;
			} else if(turn == 1){
				pCommand->Main = BAT_COMMAND_DEFENSE;
				pCommand->Sub[0] = BAT_SUBCOM_MOVE;;
				pCommand->Sub[1] = 4;
				pCommand->Sub[2] = 3;
			} else if(turn <= 3 || turn == 5){
				pCommand->Main = BAT_COMMAND_WEAPON;
				pCommand->Sub[0] = 0;
				pCommand->Hit = 0;
				pCommand->Range = BAT_TARGET_ENEMYSINGLE;
				pCommand->Target = (ei_u32)crbatRandomSelect(pChara,BAT_TARGET_ENEMY);
			} else {
				pCommand->Main = BAT_COMMAND_WAIT;
			}
		}
	} else if(action == 2){
		if(number == 0){
			if(turn == 0){
				crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);
				crbatBeginCameraObjectToObject(0,pChara,&pChara[crnum],
				ANGLE(270),
				-1.0f,-1.0f,500);
				crbatClearDrawingList();
				crbatAddDrawingListAll();
				crbatDoMovingCamera(500);

				crbatDrawSceneWhile(500);
				CrMesManager mes;
				mes.CreateNewMessage(-1,-1,32,24,5);
				mes.OpenMessage("Sunpias.msg",102);
				mes.ReadMessage();
				mes.Draw();

				crbatDrawSceneWhile(500);
				mes.ReadMessage();
				mes.Draw();

				//---����ς�
				crbatDrawSceneWhile(1000);
				mes.ReadMessage();
				mes.Draw();
				crbatDrawSceneWhile(1000);
				mes.ReadMessage();
				mes.Draw();
				crbatDrawSceneWhile(1000);
				mes.ReadMessage();
				mes.Draw();
				crbatDrawSceneWhile(500);
				mes.ReadMessage();
				mes.Draw();

				mes.CloseMessage();
			}
			if(turn == 3){
			//---���̒��x��
				crbatDrawSceneWhile(500);
				CrMesManager mes;
				mes.CreateNewMessage(-1,-1,32,24,5);
				mes.OpenMessage("Sunpias.msg",103);
				mes.ReadMessage();
				mes.Draw();
				mes.CloseMessage();
			}
			if(turn == 4){
			//---��
				crbatDrawSceneWhile(500);
				CrMesManager mes;
				mes.CreateNewMessage(-1,-1,32,24,5);
				mes.OpenMessage("Sunpias.msg",104);
				mes.ReadMessage();
				mes.Draw();
				mes.CloseMessage();
			}
		}

		if(turn == 7 && number == 0){
			return 0;
		}
	}

	return 1;
}

//---�T���s�A�X�A���~�΃N���C�V��
CREVENTLONG5_API int creventSunpias_YumiVSCrasive(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	em->Put(25,8,2,98);

	npPos(0,17,6);
	npDir(0,EAST);
	npPos(1,15,7);
	npDir(1,EAST);
	npPos(2,17,8);
	npDir(2,EAST);
	npPos(3,16,7);
	npDir(3,EAST);
	npPos(4,18,7);
	npDir(4,EAST);

	evScene(1,21,10);
	evFrameWait(500);

	mes.OpenMessage("Sunpias.msg",101);
	mes.ReadDraw();
	evFrameWait(500);

	//---�ꂳ��̂�
	npMove(4,1,0);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw(2);

	//---����������
	evFrameWait(500);
	npDir(4,NORTH);
	evFrameWait(500);
	npDir(4,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	//---���������
	evFrameWait(500);
	for(a = 0;a < 2;a ++){
		npMove(2,1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---���̕��
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---���A��
	evFrameWait(500);
	npDir(2,EAST);
	evFrameWait(250);
	npMove(2,1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---���~�U��Ԃ�
	evFrameWait(250);
	npDir(4,SOUTH);
	evFrameWait(200);
	npDir(4,EAST);
	evFrameWait(200);
	mes.ReadDraw();

	//---���~���苎��
	evFrameWait(200);
	crmusicPlay(CRMUSIC_BARRIER);

	{
		eiMapObject *np = npGet(4);
		np->Data.MoveSpeed = 3;
	}
	for(a = 0;a < 8;a ++){
		if(a < 4)
			npMove(4,1,0);
		else if(a < 6)
			npMove(4,0,1);
		else
			npMove(4,1,0);
		evFrame();
	}
	evFrameWait(100);
	npDir(4,NORTH);
	evFrameWait(500);
	npDir(4,EAST);
	evFrameWait(100);

	for(a = 0;a < 14;a ++){
		if(a < 3)
			npMove(4,1,0);
		else if(a < 7)
			npMove(4,0,1);
		else if(a < 10)
			npMove(4,1,0);
		else if(a < 12)
			npMove(4,0,1);
		else
			npMove(4,1,0);
		evFrame();
	}
	//---���~�I
	evFrameWait(250);
	mes.ReadDraw(3);
	evFrameWait(250);

	//21,10
	//43,39
	npPos(4,0,0);
	for(a = 0;a < 11;a ++){
		mcMove(1,0);
		evFrame();
	}
	for(a = 0;a < 14;a ++){
		mcMove(0,1);
		evFrame();
	}
	for(a = 0;a < 11;a ++){
		mcMove(1,0);
		evFrame();
	}
	for(a = 0;a < 15;a ++){
		mcMove(0,1);
		evFrame();
	}

	//---���~�̃X�s�[�h�߂�
	{
		eiMapObject *np = npGet(4);
		np->Data.MoveSpeed = 2;
	}
	evFrameWait(3000);

	npPos(0,43,30);
	npPos(1,44,26);
	npPos(2,44,29);
	npPos(3,43,27);

	for(a = 0;a < 8;a ++){
		if(a < 7){
			npMove(0,0,1);
			npMove(2,0,1);
		}
		npMove(1,0,1);
		npMove(3,0,1);
		evFrame();
	}
	//---��������
	evFrameWait(500);
	npDir(0,EAST);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);

	mes.ReadDraw();

	//---���~�̐�
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---�R�����I
	evFrameWait(250);
	for(a = 0;a < 4;a ++){
		if(a < 1)
			npMove(3,0,1);
		else if(a < 2)
			npMove(3,-1,0);
		else if(a < 4)
			npMove(3,0,1);
		evFrame();
	}
	
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);

	npPos(4,43,50);
	npDir(4,SOUTH);
	npPos(5,43,56);
	npDir(5,SOUTH);

	for(a = 0;a < 10;a ++){
		mcMove(0,1);
		evFrame();	
	}
	//---���~�I
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(1250);

	//---�N���C�V��������
	for(a = 0;a < 6;a ++){
		mcMove(0,1);
		evFrame();	
	}
	evFrameWait(1500);
	for(a = 0;a < 16;a ++){
		mcMove(0,-1);
		evFrame();	
	}

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(100);
	for(a = 0;a < 4;a ++){
		if(a < 1)
			npMove(1,1,0);
		else
			npMove(1,0,1);
		evFrame();
	}
	//---�Ȃ�ł�����
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---�܂������Ă���Ƃ�
	for(a = 0;a < 17;a ++){
		mcMove(0,1);
		evFrame();	
	}
	evFrameWait(1000);
	npMove(4,0,1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);

	//---�U�����
	npDir(5,WEST);
	evFrameWait(500);
	npDir(5,NORTH);
	evFrameWait(1000);
	mes.ReadDraw();

	//---���Ȃ���ǂ�������
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	npMove(4,0,1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();

	//---�Ȃɂ�
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.CloseMessage();


	//---�o�g���I
	int h_lp = 0,h_maxlp = 0;
	{
		pPartyInfo->PartyMember[0] = 4;
		pPartyInfo->PartyMember[1] = 5;
		pPartyInfo->PartyMember[2] = -1;
		pPartyInfo->PartyMember[3] = -1;
		pPartyInfo->PartyMember[4] = -1;
		pCharacterInfo[4].SetBattleFieldStartPos(5,1);

		for(b = 0;b < 2;b ++){
			CrCharacter *pChara = crcharaGetPartyMember(b);
			//---�����i���O��
			for(a = 0;a < EQ_WEAPON_MAX;a ++){
				if(pChara->GetWeapon(a)){
					critemAddItem(pChara->GetWeapon(a));
					pChara->SetWeapon(a,0);
				}
			}
			for(a = 0;a < EQ_PROTECTOR_MAX;a ++){
				if(pChara->GetProtector(a)){
					critemAddItem(pChara->GetProtector(a));
					pChara->SetProtector(a,0);
				}
			}
			for(a = 0;a < EQ_ACCESSORY_MAX;a ++){
				if(pChara->GetAccessory(a)){
					critemAddItem(pChara->GetAccessory(a));
					pChara->SetAccessory(a,0);
				}
			}
			if(b == 0){
				pChara->SetWeapon(0,59);

				h_lp = pChara->GetLP();
				h_maxlp = pChara->GetMaxLP();
				pChara->SetMaxLP(500);
			}
		}
		pPartyInfo->PartyMember[1] = -1;
		prtRecovery(0);

		crcharaLoadFace(-1);
	}

	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = 0;
	BattleInfo.Enemy[0].Enemy = 155;
	BattleInfo.Enemy[0].x = 6;
	BattleInfo.Enemy[0].y = 9;
	BattleInfo.Enemy[1].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	BattleInfo.lpTurnCallBack = SunpiasbatCallBack1;
	BattleInfo.DontShowAfterBattle = 1;
	BattleInfo.FailOK = 1;
	evField(0,1);

	int old = crdataGetSystem()->BattleCameraAngle;
	crdataGetSystem()->BattleCameraAngle = 0;
	{
		crbatSetShowStatus(0);

		evReadObject(5,"YumiDown.acf");
		npDir(4,NORTH);
		if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		}
		crbatSetShowStatus(1);
	}
	crdataGetSystem()->BattleCameraAngle = old;

	//---�k�o�����ɖ߂�
	CrCharacter *pChara = crcharaGetPartyMember(0);
	pChara->SetMaxLP(h_maxlp);
	pChara->SetWeapon(0,0);
	prtRecovery(0);

	crhistSubBattleCount();

	evFrameWait(500);
	for(a = 0;a < 17;a ++){
		mcMove(0,-1);
		evFrame();	
	}
	evFrameWait(500);
	npMove(0,0,1);
	evFrame();
	evFrameWait(250);

	//---���~�I
	mes.OpenMessage("Sunpias.msg",105);
	mes.ReadDraw(2);

	//---�f�B�U���o��
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(1,0,1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---�f�B�U�B��������
	npDir(1,WEST);
	evFrameWait(250);
	for(a = 0;a < 16;a ++){
		npMove(1,-1,0);
		if(a == 5)
			npDir(3,WEST);
		if(a > 6)
			npMove(3,-1,0);
		evFrame();
	}
	//---���E�E�E
	mes.ReadDraw();
	evFrameWait(250);
	npMove(0,0,1);
	evFrame();
	//---��߂āI�I
	evFrameWait(250);
	mes.ReadDraw();

	//---�킽����
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	for(a = 0;a < 17;a ++){
		mcMove(0,1);
		evFrame();	
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---���Ȃ��͂���
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---�N���C�V������
	npDir(5,EAST);
	evFrameWait(500);
	npDir(5,SOUTH);
	evFrameWait(500);
	for(a = 0;a < 8;a ++){
		npMove(5,0,1);
		evFrame();
		evFrameWait(500);
	}
	npPos(1,32,53);
	npPos(3,26,52);
	//---�f�B�U�B������
	for(a = 0;a < 2;a ++){
		mcMove(0,-1);
		evFrame();
	}
	for(a = 0;a < 16;a ++){
		if(a < 11)
			npMove(1,1,0);
		npMove(3,1,0);
		if(a == 11)
			npDir(1,NORTH);
		evFrame();
	}
	evFrameWait(1500);
	mes.CloseMessage();

	//---�O���E���h�V�b�v
	crmusicFadeOut();
	evFadeOut(2000);
	et->Delay2(1000);

	crfieldChangeMap(59,0,1,0);
	crfieldChangeScene(0,15,9);
	evReadObject(4,"YumiSlp.acf");

	npPos(0,15,9);
	npDir(0,NORTH);
	npPos(1,12,7);
	npDir(1,EAST);
	npPos(2,15,6);
	npDir(2,SOUTH);
	npPos(3,13,6);
	npDir(3,EAST);
	npPos(4,15,7);
	npDir(4,SOUTH);
	npPos(5,14,9);
	npDir(5,NORTH);

	evFieldNoFlip();
	evFadeIn(2000);

	evFrameWait(1000);
	mes.OpenMessage("Sunpias.msg",106);
	mes.ReadDraw(2);
	//---�N���C�V�����āE�E�E
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---�ł������
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(2000);
	mes.ReadDraw();

	//---���~�̘b
	evFrameWait(500);
	crmusicPlay(CRMUSIC_SINCETHEDAY);
	evFrameWait(700);
	mes.ReadDraw(4);

	//---�P�O�N�O�E�E�E
	evFrameWait(500);
	mes.ReadDraw();
	//---����
	evFrameWait(500);
	mes.ReadDraw(4);

	evFrameWait(1000);
	mes.ReadDraw(2);

	//---�搶�͐��Ȃ�����
	evFrameWait(500);
	mes.ReadDraw(2);
	//---���~����̂��ꂳ���
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(4);

	//---���l���H
	evFrameWait(500);
	mes.ReadDraw();

	//---���ꂽ
	evFrameWait(500);
	mes.ReadDraw(3);

	//---�ނ�ɂ��Ă݂��
	evFrameWait(500);
	mes.ReadDraw(3);

	//---���͒m��Ȃ�����
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();

	//---�����c��
	evFrameWait(1000);
	mes.ReadDraw(3);
	//---���
	evFrameWait(500);
	mes.ReadDraw(2);
	//---���΂炭
	evFrameWait(1000);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw();

	//---���l��
	evFrameWait(2000);
	mes.ReadDraw(2);

	//---���ꂩ��E�E�E
	evFrameWait(2000);
	mes.ReadDraw(3);

	crmusicFadeOut();
	evFrameWait(500);
	mes.ReadDraw(3);

	//---�A�[�W�F
	evFrameWait(500);
	crmusicPlay(CRMUSIC_SILENT);
	mes.ReadDraw();
	evFrameWait(500);
	npMove(3,1,0);
	evFrame();
	npDir(3,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);
	//---�ڂ�����
	evFrameWait(500);
	mes.ReadDraw(3);

	//---���ׂ�
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---�A�[�W�F����
	evFrameWait(500);
	mes.ReadDraw();
	//---���Ⴀ
	evFrameWait(500);
	mes.ReadDraw(3);

	//---�G�^�[�i����
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(2000);
	mes.ReadDraw();

	//---���i��
	evFrameWait(1000);
	npDir(1,SOUTH);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(1,0,1);
		evFrame();
	}
	evFrameWait(150);
	npDir(1,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	//---�킽��
	evFrameWait(2000);
	npDir(0,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	mes.ReadDraw(3);

	//---��Տ���
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---��N���[�^�[�H
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	mes.ReadDraw(3);

	//---����
	evFrameWait(100);
	crmusicPlay(CRMUSIC_GS);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	mes.CloseMessage();

	evSet(175,1);
	evSet(177,1);

	crfieldChangeMap(10,0,1,0);
	mcShow(1);

	mcDir(EAST);
	evSet(EV_GS_NUMBER_STATUS,1);
	crfieldSetGroundShipPos();
	crfieldSetMainCharacter(3);

	evScene(0,46,207);

	evFrameWait(250);
	{
		pPartyInfo->PartyMember[0] = 0;
		pPartyInfo->PartyMember[1] = 1;
		pPartyInfo->PartyMember[2] = 2;
		pPartyInfo->PartyMember[3] = 3;
		pPartyInfo->PartyMember[4] = -1;

		crcharaLoadFace(-1);
		for(a = 0;a < 4;a ++){
			crcharaCheckBattleFieldPos(a);
		}
	}
	prtRecoveryAll();

	//---�T���B�A�[�̐���
	mes.FileMessage("Sunpias.msg",108);
	evFrameWait(250);

	if(crbaseSelectYesNo("�����𕷂��܂����H",64,64) == 0){
		int count = 0,sel;
		CrSelectWindow win;
		do {
			mes.FileMessage("Sunpias.msg",109);
			evFrameWait(250);

			if(count == 0){
				win.Create(64,64,16,6,"�킩��܂������H",
					"�킩����;�����ς�;�T���B�A�[���ăV���f�B�D���H;");
			} else {
				win.Create(64,64,10,5,"�킩��܂������H",
					"�킩����;�����ς�;");
			}
			do {
				crbaseMenuReset();
				win.Paint();
				win.Refresh();
				crbaseMenuStart();
				sel = win.Select();
			} while(sel == -1);

			evFrameWait(250);
			mes.FileMessage("Sunpias.msg",110 + sel);
			evFrameWait(250);

			count ++;
		} while(sel != 0);
	}
	evFrameWait(250);

	return 1;
}

//---�m�[�X�e���A�A�T���B�A�[�̗��A��
CREVENTLONG5_API int creventNorthTereia_Xavier(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	npPos(45,13,24);
	npDir(45,WEST);
	npPos(46,16,24);
	npDir(46,WEST);
	npPos(47,14,25);
	npDir(47,WEST);
	evReadObject(15,"Xavier.acf");
	npPos(48,13,25);
	npDir(48,WEST);

	evScene(0,13,25);
	evFrameWait(250);

	//---���΂����
	npDir(22,NORTH);
	evFrameWait(250);
	for(a = 0;a < 5;a ++){
		if(a < 1)
			npMove(22,0,-1);
		else if(a < 3)
			npMove(22,1,0);
		else if(a < 4)
			npMove(22,0,1);
		else if(a < 5)
			npMove(22,1,0);
		evFrame();
	}
	evFrameWait(250);
	mes.OpenMessage("NorthTereia.msg",107);
	mes.ReadDraw(2);

	//---�m�荇��
	evFrameWait(250);
	npDir(45,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---�A��
	evFrameWait(1000);
	npMove(48,-1,0);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---�Q�K
	crfieldChangeScene(2,5,6);
	npPos(0,4,4);
	npDir(0,SOUTH);
	npPos(1,2,4);
	npDir(1,EAST);
	npPos(2,3,6);
	npDir(2,NORTH);
	npPos(3,6,4);
	npDir(3,WEST);

	evScene(2,5,6);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---�����Ă���
	evFrameWait(500);
	npDir(2,EAST);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	//---��������
	evFrameWait(500);
	mes.ReadDraw(3);

	//---�܁A
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---��o��
	npPos(4,9,9);
	npDir(4,NORTH);
	evFrameWait(250);
	for(a = 0;a < 6;a ++){
		if(a < 1)
			npMove(4,0,-1);
		else if(a < 4)
			npMove(4,-1,0);
		else
			npMove(4,0,-1);
		if(a == 1)
			npDir(3,SOUTH);
		if(a == 3)
			npDir(0,SOUTH);
		if(a == 4)
			npDir(1,SOUTH);
		if(a == 5)
			npDir(2,EAST);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(3);
	//---�F�B��
	evFrameWait(250);
	npDir(4,WEST);
	npMove(4,-1,0);
	evFrame();
	evFrameWait(250);
	npDir(4,NORTH);
	evFrameWait(250);
	npDir(4,WEST);
	evFrameWait(500);
	npDir(4,NORTH);
	evFrameWait(250);

	mes.ReadDraw(2);

	//---�T���B�A�[��
	evFrameWait(500);
	npDir(1,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	//---���e����
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(2);

	//---���F�B�̕���
	evFrameWait(500);
	npDir(4,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---�����
	evFrameWait(750);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	//---�C�̂���
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---���܂�
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(4,SOUTH);
	evFrameWait(250);
	npDir(4,EAST);
	evFrameWait(250);
	for(a = 0;a < 5;a ++){
		if(a < 4)
			npMove(4,1,0);
		else
			npMove(4,0,1);
		evFrame();
	}
	//---�ۂ��
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(4,0,1);
		evFrame();
	}
	npDelete(4);
	evFrameWait(2000);

	npDir(0,SOUTH);
	evFrameWait(500);
	npDir(1,SOUTH);
	evFrameWait(1500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(2000);

	//---����������
	crmusicPlay(CRMUSIC_SAKABA);
	npDir(0,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	//---�O��j
	evFrameWait(500);
	npMove(3,-1,0);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---�y����
	npDir(2,EAST);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(2,1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	evScene(5,15,15);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---����
	evReloadMap(1);
	crfieldChangeScene(0,13,25);
	npPos(22,12,24);
	npDir(22,EAST);
	npPos(45,17,32);
	npDir(45,SOUTH);
	npPos(46,18,33);
	npDir(46,SOUTH);
	npPos(47,13,25);
	npDir(47,WEST);
	npPos(48,13,24);
	npDir(48,WEST);
	evReadObject(15,"Xavier.acf");

	evScene(0,13,25);
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);

	for(a = 0;a < 4;a ++){
		mcMove(1,0);
		evFrame();
	}
	for(a = 0;a < 9;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(500);
	npMove(45,0,1);
	evFrame();
	evFrameWait(500);
	npDir(45,EAST);
	evFrameWait(500);

	mes.ReadDraw(2);
	evFrameWait(500);
	npDir(45,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	evReloadMap(0);
	mcShow(1);
	mcDir(SOUTH);
	evScene(0,17,34);

	prtRecoveryAll();

	mes.CloseMessage();

	evSet(180,1);

	return 1;
}

//---�h�[�O��������
CREVENTLONG5_API int creventDoguri_Muraokoshi(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;


	evFrameWait(250);

	mcShow(0);
	npPos(20,35,26);
	npDir(20,SOUTH);
	npPos(21,36,26);
	npDir(21,SOUTH);
	npPos(22,34,25);
	npDir(22,SOUTH);
	npPos(30,37,25);
	npDir(30,SOUTH);

	npPos(10,35,28);
	npDir(10,NORTH);
	evScene(0,35,28);
	evFrameWait(500);

	mes.OpenMessage("Doguri.msg",104);
	mes.ReadDraw(2);

	//---�ǂ�
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	npDir(21,WEST);
	evFrameWait(250);
	npDir(21,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---������
	evFrameWait(500);
	mes.ReadDraw(4);
	//---���傤��
	evFrameWait(500);
	npMove(10,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(3);
	evFrameWait(500);

	//---�Ⴂ�O
	npPos(31,35,19);
	npDir(31,SOUTH);
	npPos(32,36,19);
	npDir(32,SOUTH);
	npPos(33,35,18);
	npDir(33,SOUTH);
	npPos(34,36,18);
	npDir(34,SOUTH);
	npPos(35,35,17);
	npDir(35,SOUTH);
	for(a = 0;a < 5;a ++){
		npMove(31,0,1);
		npMove(32,0,1);
		npMove(33,0,1);
		npMove(34,0,1);
		npMove(35,0,1);

		evFrame();
	}

	//---�U�����
	npDir(20,WEST);
	evFrameWait(125);
	npDir(21,EAST);
	evFrameWait(125);
	npDir(20,NORTH);
	evFrameWait(125);
	npDir(21,NORTH);
	evFrameWait(125);
	npDir(30,WEST);
	evFrameWait(125);
	npDir(22,EAST);
	evFrameWait(125);
	npDir(30,NORTH);
	evFrameWait(125);
	npDir(22,NORTH);

	evFrameWait(500);
	mes.ReadDraw(2);

	for(a = 31;a <= 35;a ++){
		npMove(a,0,1);
	}
	evFrame();
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---�ӎ`��
	for(a = 0;a <= 30;a ++){
		npDelete(a);
	}
	npPos(10,18,24);
	npDir(10,SOUTH);
	em->Put(18,25,3,96);
	em->Put(18,24,3,97);
	npPos(4,16,24);
	npDir(4,SOUTH);
	em->Put(16,25,3,96);
	em->Put(16,24,3,97);
	npPos(5,20,24);
	npDir(5,SOUTH);
	em->Put(20,25,3,96);
	em->Put(20,24,3,97);


	npPos(20,17,26);
	npDir(20,NORTH);
	em->Put(17,27,3,96);
	em->Put(17,26,3,97);

	npPos(21,20,26);
	npDir(21,NORTH);
	em->Put(20,27,3,96);
	em->Put(20,26,3,97);

	npPos(22,16,26);
	npDir(22,NORTH);
	em->Put(16,27,3,96);
	em->Put(16,26,3,97);

	npPos(30,19,26);
	npDir(30,NORTH);
	em->Put(19,27,3,96);
	em->Put(19,26,3,97);


	npPos(6,16,28);
	npDir(6,NORTH);
	em->Put(16,29,3,96);
	em->Put(16,28,3,97);

	npPos(3,17,28);
	npDir(3,NORTH);
	em->Put(17,29,3,96);
	em->Put(17,28,3,97);

	npPos(7,18,28);
	npDir(7,NORTH);
	em->Put(18,29,3,96);
	em->Put(18,28,3,97);

	npPos(8,20,28);
	npDir(8,NORTH);
	em->Put(20,29,3,96);
	em->Put(20,28,3,97);

	for(a = 16;a <= 20;a ++){
		em->Put(a,25,1,53);
	}
	for(a = 16;a <= 20;a ++){
		em->Put(a,27,1,53);
	}
	for(a = 16;a <= 20;a ++){
		em->Put(a,29,1,53);
	}

	crfieldPaletteChange(PALETTE_NIGHT);

	evScene(0,18,28);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);

	//---�݂�ȐU��Ԃ�
	npDir(20,EAST);
	evFrameWait(100);
	npDir(21,WEST);
	evFrameWait(100);
	npDir(22,EAST);
	evFrameWait(100);
	npDir(20,SOUTH);
	evFrameWait(100);
	npDir(21,SOUTH);
	evFrameWait(100);
	npDir(22,SOUTH);
	evFrameWait(100);

	npDir(30,EAST);
	evFrameWait(100);
	npDir(6,WEST);
	evFrameWait(100);
	npDir(3,EAST);
	evFrameWait(100);
	npDir(30,SOUTH);
	evFrameWait(100);
	npDir(6,SOUTH);
	evFrameWait(100);
	npDir(3,SOUTH);
	evFrameWait(100);

	npDir(7,EAST);
	evFrameWait(100);
	npDir(8,WEST);
	evFrameWait(100);
	evFrameWait(100);
	npDir(7,SOUTH);
	evFrameWait(100);
	npDir(8,SOUTH);
	evFrameWait(100);
	evFrameWait(1000);

	mes.ReadDraw(4);
	//---�H�ׂĂ݂܂��傤
	evFrameWait(500);
	mes.ReadDraw(2);

	//---����߁[�I
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(2);

	//---����H
	evFrameWait(500);
	npDir(20,WEST);
	evFrameWait(500);
	mes.ReadDraw();
	//---�l
	evFrameWait(1000);
	mes.ReadDraw(2);

	evFrameWait(250);
	npDir(22,EAST);
	evFrameWait(250);
	npDir(22,NORTH);
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(22,EAST);
	evFrameWait(250);
	npDir(22,SOUTH);
	evFrameWait(500);

	evFrameWait(250);
	npDir(20,SOUTH);
	evFrameWait(500);

	//---����Ȃ�
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	eiMapObject *np =npGet(20);
	np->Data.AnimeWait = 100000;
	em->Put(17,27,3,1024);
	em->Put(17,26,3,1024);
	em->Put(17,26,3,99);
	evFrameWait(500);

	//---�������[�I
	evFrameWait(250);
	mes.ReadDraw();

	//---�s��Ȃ�������
	em->Put(17,27,3,1024);
	em->Put(17,26,3,1024);
	em->Put(17,26,3,98);
	evFrame();
	mes.ReadDraw();

	evFrameWait(250);
	npDir(30,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(21,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---��������
	evFrameWait(250);
	npDir(30,NORTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(2);

	//---����邩�H
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

	//---���
	evReloadMap(0);
	npPos(20,14,6);
	npDir(20,SOUTH);
	npPos(21,13,7);
	npDir(21,EAST);
	npPos(22,15,6);
	npDir(22,SOUTH);
	npPos(30,16,7);
	npDir(30,WEST);
	evScene(0,15,8);

	evFrameWait(500);
	for(a = 0;a < 2;a ++){
		npMove(22,0,1);
		evFrame();
	}
	evFrameWait(250);
	npDir(22,WEST);
	evFrameWait(250);
	npDir(22,NORTH);
	evFrameWait(250);

	mes.ReadDraw();

	//---�{����
	evFrameWait(500);
	npDir(21,SOUTH);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(30,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);

	npDelete(20);
	npDelete(21);
	npDelete(22);
	npDelete(30);

	mcShow(1);
	mcDir(SOUTH);
	evScene(0,15,8);

	mes.CloseMessage();

	prtRecoveryAll();
	evSet(182,1);

	return 1;
}

//---�h�[�O���A�����̃T�C������
CREVENTLONG5_API int creventDoguri_Sain(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;


	evFrameWait(250);

	mcShow(0);
	npPos(20,35,26);
	npDir(20,SOUTH);
	npPos(21,36,26);
	npDir(21,SOUTH);
	npPos(22,34,25);
	npDir(22,SOUTH);
	npPos(30,37,25);
	npDir(30,SOUTH);

	npPos(10,35,28);
	npDir(10,NORTH);
	evScene(0,35,28);
	evFrameWait(500);

	mes.OpenMessage("Doguri.msg",105);
	mes.ReadDraw(3);
	evFrameWait(500);
	mes.ReadDraw(4);
	evFrameWait(250);
	mes.CloseMessage();

	int sel;
	CrSelectWindow win;

	evFrameWait(250);
	win.Create(64,64,16,6,"�厖�ɂ��Ă����H",
		"������;����������;�f�B�U����������;");

	do {
		crbaseMenuReset();
		win.Paint();
		win.Refresh();
		crbaseMenuStart();
		sel = win.Select();
	} while(sel == -1);

	evFrameWait(250);
	if(sel == 2){
		npDir(21,WEST);
		evFrameWait(250);
		mes.FileMessage("Doguri.msg",106);
		evFrameWait(250);
		npDir(21,SOUTH);
		evFrameWait(250);
	}
	//---�V���b�N
	mes.OpenMessage("Doguri.msg",107);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---�[��
	evFrameWait(1000);
	mes.ReadDraw(3);
	evFrameWait(250);
	npMove(10,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---����
	mes.ReadDraw(3);
	evFrameWait(500);
	mes.CloseMessage();

	evSet(183,1);

	critemAddItem(214,99);
	npDelete(20);
	npDelete(21);
	npDelete(22);
	npDelete(30);
	npPos(10,33,34);

	mcShow(1);
	mcDir(SOUTH);
	evScene(0,35,26);


	return 1;
}

//---�h�[�O���A�����E�j�u���[�h������
CREVENTLONG5_API int creventDoguri_Moriuni(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;


	evFrameWait(250);

	mcShow(0);
	npPos(20,35,26);
	npDir(20,SOUTH);
	npPos(21,36,26);
	npDir(21,SOUTH);
	npPos(22,34,25);
	npDir(22,SOUTH);
	npPos(30,37,25);
	npDir(30,SOUTH);

	npPos(10,35,28);
	npDir(10,NORTH);
	evScene(0,35,28);
	evFrameWait(500);

	mes.OpenMessage("Doguri.msg",108);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);

	//---�[��
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(250);
	for(a = 0;a < 3;a ++){
		npMove(22,0,1);
		evFrame();
	}
	evFrameWait(100);
	npDir(22,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	//---�ǂ䂱�ƁI
	evFrameWait(250);
	npMove(10,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);

	//---��������
	evFrameWait(250);
	npDir(10,EAST);
	evFrameWait(250);
	npDir(10,SOUTH);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(10,0,1);
		evFrame();
	}
	npDir(22,SOUTH);
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---��������
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(10,WEST);
	evFrameWait(250);
	npDir(10,NORTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---�����
	evFrameWait(500);
	mes.ReadDraw(5);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(10,0,-1);
		evFrame();
	}
	npDir(22,NORTH);
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	mes.CloseMessage();


	evSet(184,1);

	critemAddItem(82,1);
	npDelete(20);
	npDelete(21);
	npDelete(22);
	npDelete(30);
	npPos(10,33,34);

	mcShow(1);
	mcDir(SOUTH);
	evScene(0,35,26);

	return 1;
}

//---���グ��
CREVENTLONG5_API int creventGreatCrater_Sky(void)
{
	eiCell bgCell;

	evFadeOut();
	crbaseClearScreen();

	bgCell.ReadFile(CR_DATADIR1"GrateCrater.acf",CR_DATAFILE1,crdataGetFileMode());
	RECT rect = {0,0,640,480} , srcrect,dstrect;
	bgCell.SetSurface(&rect,3,0);

	int y;
	eiTime let;
	for(y = 0;y < 480;y ++){
		let.Reset();

		srcrect.left = 0;
		srcrect.right = 640;
		srcrect.top = 240 - (y / 2);
		srcrect.bottom = srcrect.top + 240;

		dstrect.left = 0;
		dstrect.right = 640;
		dstrect.top = (y % 2);
		dstrect.bottom = dstrect.top + 479;

		(eiGetSurfacePointer() + 3)->PutExtend2(
			(eiGetSurfacePointer() + 1),
			&dstrect,&srcrect,DDBLT_WAIT);

		ew->lpCell[1]->DrawFillBox(0,0,639,0,ep->ToRGB(CRCOLOR_BLACK));

		if(y == 0){
			RECT scr = {0,0,640,480};
			crefectScreenEfect_FadeIn(&scr,2000);
		}

		ew->Flip();
		if(crsysGetScreenMode() == 1){
			let.Wait2(12);
		}
	}
	et->Delay2(1000);
	{
		RECT scr = {0,0,640,480};
		crefectScreenEfect_FadeOut(&scr,2000);
	}
	crbaseClearScreen();
	et->Delay2(1000);
	evFieldNoFlip(0,1);
	evFadeIn();

	bgCell.Release();

	return 1;
}

//---��N���[�^�[�A�����D
CREVENTLONG5_API int creventGreatCrater_First(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	evSet(EV_GS_NUMBER_STATUS,0);

	mcShow(0);
	crfieldChangeMap(59,1,1,0);

	npPos(0,7,6);
	npDir(0,EAST);
	evScene(1,5,6);

	//---�~��܂���I
	evFrameWait(500);
	mes.OpenMessage("GreatCrater.msg",101);
	mes.ReadDraw();

	evFrameWait(250);
	crmusicFadeOut();
	evFrameWait(500);

	crfieldChangeMap(10,0,1,0);
	evScene(0,227,61);
	evFrameWait(500);

	float f;
	for(f = 100.0;f <= 700.0;f *= (float)(1.011)){
		ef->SetFieldZoom((int)f);
		evFrameWait(10);
	}
	ef->SetFieldZoom(100);

	et->Delay2(2000);
	crfieldSetMainCharacter(1);

	//---������
	crmusicPlay(CRMUSIC_SILENT);
	crfieldChangeMap(83,0,1,0);
	npPos(0,19,32);
	npDir(0,NORTH);
	npPos(1,21,34);
	npDir(1,NORTH);
	npPos(2,23,32);
	npDir(2,NORTH);
	npPos(3,17,30);
	npDir(3,NORTH);

	crfieldChangeScene(0,20,21);
	evFieldNoFlip(0,1);
	evFadeIn(2000);

	evFrameWait(500);
	for(a = 0;a < 14;a ++){
		if(a < 13)
			npMove(0,0,-1);
		npMove(1,0,-1);
		if(a < 13)
			npMove(2,0,-1);
		if(a < 11)
			npMove(3,0,-1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw(2);
	//---��
	evFrameWait(500);
	npDir(2,WEST);
	evFrameWait(250);
	npDir(2,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	creventGreatCrater_Sky();

	evFrameWait(500);
	npDir(3,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	npDir(3,NORTH);
	for(a = 0;a < 10;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(1000);

	mes.CloseMessage();

	crfieldSetMainCharacter(1);
	evSet(EV_GS_NUMBER_STATUS,0);
	mcDir(SOUTH);
	mcShow(1);
	evMap(83,1,39,4);
	evReloadMapMusic();

	evSet(185,1);

	return 1;
}


//---��N���[�^�[�A�����I�I
CREVENTLONG5_API int creventGreatCrater_Yokuryu(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	npPos(0,8,14);
	npDir(0,NORTH);
	npPos(1,7,15);
	npDir(1,NORTH);
	npPos(2,9,14);
	npDir(2,NORTH);
	npPos(3,9,15);
	npDir(3,NORTH);

	evScene(11,8,15);

	evFrameWait(250);
	mes.OpenMessage("GreatCrater.msg",102);
	mes.ReadDraw();

	evFrameWait(250);
	for(a = 0;a < 6;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(250);

	for(a = 0;a < 6;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	for(a = 0;a <= 3;a ++){
		npDelete(a);
	}
	mes.CloseMessage();

	mcShow(1);
	mcDir(NORTH);
	evScene(11,8,15);

	evSet(188,1);

	return 1;
}

//---��N���[�^�[�A�����o�g���I�I
CREVENTLONG5_API int creventGreatCrater_YokuryuBattle(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	evFrameWait(250);

	//---�o�g��
	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = CRMUSIC_BOSSBATTLE1;
	BattleInfo.Enemy[0].Enemy = 161;
	BattleInfo.Enemy[0].x = 6;
	BattleInfo.Enemy[0].y = 8;
	BattleInfo.Enemy[1].Enemy = 184;
	BattleInfo.Enemy[1].x = 6;
	BattleInfo.Enemy[1].y = 8;
	BattleInfo.Enemy[2].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
//	BattleInfo.MapNumber = 1;
	evField(0,1);

	npDelete(4);
	npDelete(5);
	npDelete(6);

	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}

	evFrameWait(250);
	mes.OpenMessage("GreatCrater.msg",103);
	mes.ReadDraw();
	evFrameWait(250);

	mes.CloseMessage();

	evSet(189,1);

	return 1;
}

//---��N���[�^�[�A���_�̂̐�
CREVENTLONG5_API int creventGreatCrater_Seishintai(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	crfieldChangeScene(12,10,9);

	em->Put(5,5,2,18);

	npPos(0,7,5);
	npDir(0,EAST);
	npPos(1,5,6);
	npDir(1,EAST);
	npPos(2,7,7);
	npDir(2,NORTH);
	npPos(3,11,5);
	npDir(3,NORTH);

	evScene(12,7,7);

	evFrameWait(500);
	npDir(1,SOUTH);
	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(500);
	npDir(0,SOUTH);
	evFrameWait(500);
	npDir(1,SOUTH);
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	//---���ɉ���
	mes.OpenMessage("GreatCrater.msg",104);
	mes.ReadDraw();

	//---�Ⴄ
	evFrameWait(500);
	npDir(0,EAST);
	evFrameWait(500);
	npDir(0,SOUTH);
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(500);
	npDir(0,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---�Ȃɂ�
	evFrameWait(500);
	npDir(2,WEST);
	evFrameWait(500);
	npDir(2,NORTH);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---�ӂ邦�Ă�
	evFrameWait(1000);
	mes.ReadDraw();
	mes.ReadDraw();

	//---����
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---���_��
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(3,-1,0);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();

	//---��
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	crmusicFadeOut();
	evFrameWait(2500);
	crmusicPlay(CRMUSIC_SILENT);

	//---�b
	mes.ReadDraw(3);
	evFrameWait(500);
	mes.ReadDraw();

	//---���󂳂�
	evFrameWait(1500);
	mes.ReadDraw(3);
	evFrameWait(500);
	mes.ReadDraw();

	//---�܂�����
	evFrameWait(1500);
	mes.ReadDraw(5);
	evFrameWait(500);
	mes.ReadDraw();

	//---�Ō�̐�
	evFrameWait(1500);
	mes.ReadDraw(2);

	//---�����������Ȃ�
	evFrameWait(1000);
	npDir(0,EAST);
	evFrameWait(500);
	npDir(0,NORTH);
	evFrameWait(1000);
	npDir(0,WEST);
	evFrameWait(500);
	npDir(0,SOUTH);
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	crmusicPlay(CRMUSIC_DANGEON2);
	//---�A�[�W�F�Ƃ͂���قǂ܂ł�
	evFrameWait(500);
	mes.ReadDraw(2);

	//---�[�����܂���
	evFrameWait(500);
	npDir(3,SOUTH);
	evFrameWait(250);
	npMove(3,0,1);
	evFrame();
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();
	//---�A�[�W�F�͂܂��c���Ă�
	evFrameWait(500);
	mes.ReadDraw(4);

	//---�܁A���낢��
	evFrameWait(500);
	npDir(1,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---���A����
	evFrameWait(500);
	npDir(0,WEST);
	evFrameWait(500);
	npMove(0,-1,0);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	npDir(1,NORTH);

	//---�J�[�h�H
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(250);
	for(a = 0;a < 3;a ++){
		npMove(3,-1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---�n�}
	evFrameWait(500);
	evShowWorldMap(55,27,1);
	//---�͂�����
	evFrameWait(500);
	mes.ReadDraw();

	//---����́I
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(250);
	mes.ReadDraw(3);

	//---���ꂪ���H
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);

	mes.CloseMessage();
	evSet(190,1);

	//---�t�B�[���h��
	mcShow(1);
	crfieldSetMainCharacter(3);
	evSet(EV_GS_NUMBER_STATUS,1);
	mcDir(EAST);
	evFadeOut(2000);
	crfieldChangeMap(10,0,1,1);
	crfieldChangeScene(0,227,53);
	evFieldNoFlip(0,1);
	evFadeIn(1000);

	return 1;
}

//---�[�r�A�}�C���A�f�B���}���I�[�u
CREVENTLONG5_API int creventZeviaMine_DiyamaOve(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	npPos(0,10,4);
	npDir(0,SOUTH);

	npPos(2,11,7);
	npDir(2,NORTH);
	npPos(3,10,7);
	npDir(3,NORTH);
	npPos(4,9,8);
	npDir(4,NORTH);
	npPos(5,12,8);
	npDir(5,NORTH);
	evReadObject(15,"Xavier.acf");

	evScene(3,11,7);

	//---�Ȃ񂾂��݂�
	evFrameWait(250);
	npMove(0,0,1);
	evFrame();
	evFrameWait(250);

	mes.OpenMessage("ZeviaMine.msg",106);
	mes.ReadDraw();
	evFrameWait(250);
	npMove(0,0,-1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---�悤
	evFrameWait(250);
	npMove(3,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);

	//---�ȁA���̂悤�H
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	npMove(2,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(4);
	evFrameWait(250);

	//---�I�[�u����
	npDir(0,WEST);
	evFrameWait(250);
	for(a = 0;a < 6;a ++){
		if(a < 2)
			npMove(0,-1,0);
		else if(a < 4)
			npMove(0,0,1);
		else
			npMove(0,-1,0);
		if(a == 3)
			npDir(3,WEST);
		evFrame();
	}
	//---���O���
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(800);
	mes.ReadDraw();
	evFrameWait(1000);

	npDir(0,EAST);
	evFrameWait(250);

	for(a = 0;a < 5;a ++){
		if(a < 2)
			npMove(0,1,0);
		else if(a < 3)
			npMove(0,0,-1);
		else
			npMove(0,1,0);
		if(a == 4)
			npDir(3,NORTH);
		evFrame();
	}
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(2,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(1000);

	//---����������
	mes.ReadDraw();
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);

	mes.ReadDraw(3);
	//---�́H
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(7);

	//---�\�͔���
	evFrameWait(500);
	npDir(3,WEST);
	evFrameWait(250);
	npMove(3,-1,0);
	evFrame();
	npDir(2,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---�������H
	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(250);
	npMove(3,1,0);
	evFrame();
	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);
	mes.ReadDraw(3);
	evFrameWait(250);

	//---�l���I
	for(a = 0;a < 2;a ++){
		npMove(5,0,-1);
		evFrame();
	}
	evFrameWait(250);
	npDir(5,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	npDelete(2);
	npDelete(3);
	npDelete(4);
	npDelete(5);
	//---�O
	crfieldChangeScene(0,16,46);
	npPos(27,20,45);
	npDir(27,SOUTH);
	npPos(28,19,47);
	npDir(28,EAST);
	npPos(29,22,46);
	npDir(29,SOUTH);
	npPos(30,20,47);
	npDir(30,SOUTH);
	evScene(0,20,47);

	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(30,EAST);
	evFrameWait(250);
	npDir(30,NORTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---�����
	evFrameWait(250);
	npDir(30,WEST);
	evFrameWait(250);
	mes.ReadDraw(3);

	//---�w�҂����
	evFrameWait(500);
	npDir(30,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(250);

	mcShow(1);
	npDelete(27);
	npDelete(28);
	npDelete(29);
	npDelete(30);
	evScene(0,20,45);

	mes.CloseMessage();

	evSet(191,1);
	critemAddItem(215,1);

	return 1;
}

//---�_�C�A���^�[���I�[�u
CREVENTLONG5_API int creventDai_ReturnOve(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	evFadeOut();
	crfieldChangeScene(1,6,6);
	npPos(1,4,4);
	npDir(1,EAST);
	npPos(3,5,4);
	npDir(3,WEST);
	npPos(4,5,5);
	npDir(4,WEST);
	npPos(5,6,3);
	npDir(5,WEST);
	npPos(6,6,4);
	npDir(6,WEST);
	evReadObject(11,"Xavier.acf");

	evFieldNoFlip(0,1);
	evFadeIn();

	evFrameWait(250);

	mes.OpenMessage("Dai.msg",104);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw(4);

	//---�킴�킴
	evFrameWait(500);
	mes.ReadDraw(4);

	//---�Ȃɂ������
	evFrameWait(500);
	npDir(1,NORTH);
	evFrameWait(500);
	npDir(1,EAST);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---������
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	npDir(1,SOUTH);
	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(250);

	for(a = 0;a < 2;a ++){
		npMove(1,-1,0);
		evFrame();
	}
	evFrameWait(1000);
	npDir(1,NORTH);
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(1,1,0);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw(4);

	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	npDelete(3);
	npDelete(4);
	npDelete(5);
	npDelete(6);

	mcShow(1);
	mcDir(SOUTH);
	evScene(1,7,4);

	mes.CloseMessage();

	evSet(192,1);
	critemAddItem(215,-1);
	critemAddItem(156,1);

	return 1;
}

//28,35 = 6


//---凋C�O�̓��A���J��
CREVENTLONG5_API int creventShinkiro_TobiraHiraku(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	crfieldChangeMap(82,0,1,1);

	npPos(0,28,38);
	npDir(0,NORTH);
	npPos(1,27,39);
	npDir(1,NORTH);
	npPos(2,26,39);
	npDir(2,NORTH);
	npPos(3,29,38);
	npDir(3,NORTH);

	evScene(0,28,39);

	//---���グ��
	evFrameWait(500);
	for(a = 0;a < 12;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(1000);
	for(a = 0;a < 12;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(500);

	//---�傫������
	mes.OpenMessage("Shinkiro.msg",100);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw(2);

	//---�؂�����
	evFrameWait(500);
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(2,0,-1);
		else
			npMove(2,1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	//---��
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);
	for(a = 0;a < 3;a ++){
		if(a < 2)
			npMove(2,0,-1);
		else
			npMove(2,1,0);
		evFrame();
	}
	npDir(0,NORTH);
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---�J��
	em->Put(28,35,1,6);
	crsoundPlay(CRSOUND_ATACK4);
	evFrameWait(500);
	//---�J������
	evFrameWait(250);
	npDir(2,EAST);
	evFrameWait(250);
	npDir(2,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(3);

	//---�i�b�N���T���B�A�[�s��
	evFrameWait(250);
	npDir(2,WEST);
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);
	for(a = 0;a < 1;a ++){
		npMove(2,0,-1);
		evFrame();
	}
	npDelete(2);
	evFrameWait(500);
	for(a = 0;a < 4;a ++){
		if(a < 1)
			npMove(3,0,-1);
		else if(a < 2)
			npMove(3,-1,0);
		else
			npMove(3,0,-1);
		evFrame();
	}
	npDelete(3);
	evFrameWait(350);

	//---���i�����s�����Ƃ���
	npMove(0,0,-1);
	evFrame();
	evFrameWait(100);
	//---�Ȃ�
	mes.ReadDraw();
	evFrameWait(250);

	//---�ȂɁH
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	//---���̑O��
	npDir(1,EAST);
	evFrameWait(250);
	for(a = 0;a < 1;a ++){
		if(a < 1)
			npMove(1,1,0);
		else
			npMove(1,0,-1);
		evFrame();
	}
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	mes.ReadDraw(3);

	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(250);
	npDir(0,NORTH);
	//---�˂�
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw(2);
	//---�߂��Ă���
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---���������
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);

	//---�������g��
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(0,0,-1);
		evFrame();
	}
	npDelete(0);
	for(a = 0;a < 4;a ++){
		npMove(1,0,-1);
		evFrame();
	}
	npDelete(1);
	evFrameWait(500);

	mes.CloseMessage();

	mcShow(1);
	mcDir(NORTH);
	evScene(1,18,32);

	evSet(198,1);

	return 1;
}


//---凋C�O�̓��A�ŏ�K
CREVENTLONG5_API int creventShinkiro_Saijokai(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	crfieldChangeScene(9,11,9);

	npPos(0,10,8);
	npDir(0,WEST);
	npPos(1,13,9);
	npDir(1,EAST);
	npPos(2,10,10);
	npDir(2,WEST);
	npPos(3,12,10);
	npDir(3,NORTH);

	evScene(9,11,12);

	evFrameWait(500);
	mes.OpenMessage("Shinkiro.msg",101);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(2,SOUTH);
	evFrameWait(250);

	//---�Y��Ȑ΂�
	mes.ReadDraw();

	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	npMove(3,-1,0);
	evFrame();
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);

	//---����́I�H
	mes.ReadDraw();

	//---������
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(5);

	//---�͂��I
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---����
	evFrameWait(250);
	for(a = 0;a < 8;a ++){
		if(a < 2)
			npMove(1,1,0);
		else if(a < 4)
			npMove(1,0,1);
		else
			npMove(1,1,0);
		evFrame();
	}
	for(a = 0;a < 10;a ++){
		if(a < 8)
			mcMove(1,0);
		else
			mcMove(0,1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---�C���I
	for(a = 0;a < 12;a ++){
		if(a < 6)
			mcMove(-1,0);
		else
			mcMove(0,-1);
		evFrame();
	}
	npDir(2,WEST);
	evFrameWait(250);
	for(a = 0;a < 11;a ++){
		if(a < 1)
			npMove(2,-1,0);
		else if(a < 5)
			npMove(2,0,-1);
		else if(a < 10)
			npMove(2,1,0);
		else
			npMove(2,0,-1);

		if(a == 4)
			npDir(0,WEST);
		if(a == 6)
			npDir(0,NORTH);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(2,EAST);
	evFrameWait(250);
	npDir(2,SOUTH);
	evFrameWait(250);

	//---���i��
	for(a = 0;a < 11;a ++){
		npMove(2,0,1);

		if(a < 5){
		} else if(a < 6)
			npMove(0,0,-1);
		else if(a < 9)
			npMove(0,1,0);
		else if(a < 11)
			npMove(0,0,-1);
		evFrame();
	}
	//---�C�̌�����
	for(a = 0;a < 3;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(3,EAST);
	evFrameWait(250);
	for(a = 0;a < 8;a ++){
		if(a < 3)
			npMove(3,1,0);
		else
			npMove(3,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	//---�i�b�N�I�C�����C�N��������
	for(a = 0;a < 13;a ++){
		if(a < 1)
			mcMove(1,0);
		else
			mcMove(0,1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);

	//---�ق�Ƃ�
	for(a = 0;a < 13;a ++){
		if(a < 2)
			npMove(0,0,1);
		else if(a < 4)
			npMove(0,1,0);
		else
			npMove(0,0,1);
		evFrame();
	}
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(250);

	//---�A���V�A
	for(a = 0;a < 7;a ++){
		if(a < 4)
			mcMove(1,0);
		else
			mcMove(0,-1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);

	//---�T���B�A�[����
	for(a = 0;a < 11;a ++){
		if(a < 1)
			npMove(3,0,1);
		else if(a < 2)
			npMove(3,1,0);
		else if(a < 9)
			npMove(3,0,1);
		else
			npMove(3,1,0);
		evFrame();
	}
	evFrameWait(1000);
	npDir(3,NORTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---�p�l���G���Ă݂�H
	npDir(0,EAST);
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	for(a = 0;a < 3;a ++){
		npMove(0,0,-1);
		evFrame();
	}
	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---�p�l���̑O��
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	for(a = 0;a < 4;a ++){
		if(a == 0)
			npDir(1,SOUTH);
		if(a == 1)
			npDir(1,WEST);

		if(a == 2)
			npDir(2,EAST);
		if(a == 3)
			npDir(2,NORTH);

		if(a < 2)
			npMove(0,0,-1);
		else
			npMove(0,1,0);
		evFrame();
	}
	for(a = 0;a < 2;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(1000);

	//---����H
	crsoundPlay(CRSOUND_MASINBTN);
	evFrameWait(500);
	crsoundPlay(CRSOUND_KIDOU);
	evFrameWait(1500);
	em->Put(17,10,2,108);
	evFrameWait(1500);
	em->Put(17,10,2,107);
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(3,1,0);
		else
			npMove(3,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---�i�b�N����
	for(a = 0;a < 6;a ++){
		if(a < 3)
			npMove(2,0,-1);
		else if(a < 5)
			npMove(2,1,0);
		else
			npMove(2,0,-1);
		evFrame();
	}
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(250);

	//---�l�b�g���[�N�G���[
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---�g���Ȃ�
	evFrameWait(500);
	npMove(1,-1,0);
	evFrame();
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	crsoundPlay(CRSOUND_ATACK4);
	evFrameWait(250);

	//---�_������I
	mes.ReadDraw();

	evFrameWait(500);
	crsoundPlay(CRSOUND_KIDOU);
	evFrameWait(1000);
	em->Put(17,10,2,108);
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---�I���Ɍ����Ă��E�E�E
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(1,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---�ǂ�
	evFrameWait(500);
	mes.ReadDraw(2);

	//---�߂����́H
	evFrameWait(500);
	mes.ReadDraw();

	//---�ǂ�
	evFrameWait(500);
	mes.ReadDraw(5);

	//---�܂�A�A�[�W�F�Ƃ�
	evFrameWait(500);
	mes.ReadDraw(2);

	//---�A�[�W�F�̊����E�E�E
	evFrameWait(500);
	mes.ReadDraw(2);

	//---���A����E�E�E
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	em->Put(17,10,2,107);
	evFrameWait(100);
	em->Put(17,10,2,108);
	evFrameWait(100);
	em->Put(17,10,2,107);
	evFrameWait(100);
	em->Put(17,10,2,108);
	evFrameWait(500);
	mes.ReadDraw();

	//---�l�b�g���[�N��
	evFrameWait(250);
	mes.ReadDraw();

	//---������
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	crsoundPlay(CRSOUND_ATACK4);
	evFrameWait(1000);
	//---����
	em->Put(17,10,2,107);
	evFrameWait(100);
	em->Put(17,10,2,108);
	evFrameWait(100);
	em->Put(17,10,2,107);
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---�����I
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(250);
	crsoundPlay(CRSOUND_ATACK4);
	evFrameWait(250);
	crsoundPlay(CRSOUND_ATACK4);
	evFrameWait(750);
	crsoundPlay(CRSOUND_ATACK4);
	evFrameWait(1000);
	mes.ReadDraw();

	//---�ł��A�A�[�W�F����
	evFrameWait(1000);
	npDir(0,EAST);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(2,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	//---�t�B���K���g��
	evFrameWait(500);
	npDir(1,WEST);
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();

	//---����Ȃ��̂��E�E�E
	evFrameWait(1000);
	mes.ReadDraw(5);

	//---�N���C�V����
	evFrameWait(500);
	mes.ReadDraw(2);

	//---���̑O��
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---�����Ă�����
	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---���Ⴀ�Ȃ�ŁA
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---�I
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(100);
	npDir(3,WEST);
	evFrameWait(150);
	mes.ReadDraw(3);

	//---�암��ጴ
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---���B�ɂł��邱�Ƃ�
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---�f�r
	evFadeOut();
	evSet(199,1);
	crfieldChangeMap(59,0,1,1);
	crfieldChangeScene(0,15,9);

	npPos(0,15,6);
	npDir(0,SOUTH);
	npPos(1,13,6);
	npDir(1,SOUTH);
	npPos(2,15,9);
	npDir(2,NORTH);
	npDelete(5);

	evFieldNoFlip(0,1);
	evFadeIn();

	//---�o��
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw(3);

	//---������ꏊ��
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	evShowWorldMap(55,27);

	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	evShowWorldMap(80,316);

	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);

	int sel;
	CrSelectWindow win;
	win.Create(64,64,10,5,"�ē����Ă��炢�܂����H","�ē�����;������;");

	do {
		crbaseMenuReset();
		win.Paint();
		win.Refresh();
		crbaseMenuStart();
		sel = win.Select();
	} while(sel == -1);
	
	//---����
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	mes.CloseMessage();

	crfieldChangeMap(10,0,0,0);
	crfieldChangeScene(0,55,28);

	evSet(EV_GS_NUMBERX,55);
	evSet(EV_GS_NUMBERY,28);
	crfieldSetGroundShipPos();
	mcShow(1);
	mcDir(NORTH);
	crfieldSetMainCharacter(4);

	evFieldNoFlip(0,1);
	evFadeIn();

	evFrameWait(500);
	evChangeGroundShip();

	if(sel == 0){
		//---�ē�
		for(a = 0;a < 20;a ++){
			mcMove(1,0);
			evFrame();
		}
		for(a = 0;a < 30;a ++){
			mcMove(0,1);
			evFrame();
		}

		evScene(0,61,299);
		for(b = 0;b < 3;b ++){
			for(a = 0;a < 6;a ++){
				mcMove(0,1);
				evFrame();
			}
			for(a = 0;a < 6;a ++){
				mcMove(1,0);
				evFrame();
			}
		}
	}
//80,316
	evFrameWait(250);
	evChangeGroundShip();

	return 1;
}

//---�łт̈�ՁA�`����҂̐�
CREVENTLONG5_API int creventHorobi_Koe(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	npPos(0,22,17);
	npDir(0,SOUTH);
	npPos(1,21,16);
	npDir(1,SOUTH);
	npPos(2,21,15);
	npDir(2,SOUTH);
	npPos(3,22,15);
	npDir(3,SOUTH);

	evScene(0,22,14);

	for(a = 0;a < 14;a ++){
		mcMove(0,1);
		evFrame();
	}

	evFrameWait(1000);
	for(a = 0;a < 10;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(1000);

	//---�����Ȃ���
	mes.FileMessage("Horobi.msg",100);
	evFrameWait(500);
	{
		mes.CreateNewMessage(0,160,288,20,5,1);
		mes.OpenMessage("Horobi.msg",101);
		mes.ReadDraw();
		mes.CloseMessage();
	}
	evFrameWait(250);

	npDir(0,EAST);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);

	//---���I�H
	mes.FileMessage("Horobi.msg",102);
	evFrameWait(500);
	{
		mes.CreateNewMessage(0,160,288,20,5,1);
		mes.OpenMessage("Horobi.msg",103);
		mes.ReadDraw();
		mes.CloseMessage();
	}
	evFrameWait(500);
	npMove(1,0,1);
	evFrame();
	evFrameWait(250);

	//---���@�H
	mes.FileMessage("Horobi.msg",104);
	evFrameWait(500);
	{
		mes.CreateNewMessage(0,160,288,20,5,1);
		mes.OpenMessage("Horobi.msg",105);
		mes.ReadDraw();
		mes.CloseMessage();
	evFrameWait(500);
		mes.CreateNewMessage(0,160,288,20,5,1);
		mes.OpenMessage("Horobi.msg",106);
		mes.ReadDraw();
		mes.CloseMessage();
	evFrameWait(500);
		mes.CreateNewMessage(0,160,288,20,5,1);
		mes.OpenMessage("Horobi.msg",107);
		mes.ReadDraw();
		mes.CloseMessage();
	}
	evFrameWait(1000);

	//---����Ȃ�
	mes.OpenMessage("Horobi.msg",108);
	mes.ReadDraw();
	evFrameWait(500);

	npMove(3,0,1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	for(a = 0;a <= 3;a ++){
		npDelete(a);
	}
	mcShow(1);
	mcDir(SOUTH);
	evScene(0,22,17);

	evSet(200,1);

	return 1;
}

//---�łт̈�ՁA�u�r�R�s�[
CREVENTLONG5_API int creventHorobi_VSCopy(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	int bat = 0;

//	evSet(202,1);
	if(!evGet(202) && !evGet(201)){
		//---�͂��߂āI
		bat = 1;
		mcShow(0);

		npPos(0,16,11);
		npDir(0,NORTH);
		npPos(1,15,12);
		npDir(1,NORTH);
		npPos(2,17,12);
		npDir(2,NORTH);
		npPos(3,16,12);
		npDir(3,NORTH);

		evScene(2,16,12);

		evFrameWait(500);

		//---�͂�
		{
			mes.CreateNewMessage(0,160,288,20,5,1);
			mes.OpenMessage("Horobi.msg",110);
			mes.ReadDraw();
			mes.CloseMessage();
		}
		evFrameWait(500);
		mes.FileMessage("Horobi.msg",111);
		evFrameWait(500);

		//---����
		{
			mes.CreateNewMessage(0,160,288,20,5,1);
			mes.OpenMessage("Horobi.msg",112);
			mes.ReadDraw();
			mes.CloseMessage();
		}
		evFrameWait(500);
		mes.FileMessage("Horobi.msg",113);
		evFrameWait(500);


		//---�����
		{
			mes.CreateNewMessage(0,160,288,20,5,1);
			mes.OpenMessage("Horobi.msg",114);
			mes.ReadDraw();
			mes.CloseMessage();
		}
		evFrameWait(500);
	} else {
		if(!evGet(201)){
			evFrameWait(100);
			if(crbaseSelectYesNo("�킢�܂����H",64,64) == 0){
				//---�키
				bat = 1;
			}
			evFrameWait(250);
		} else {
			{
				mes.CreateNewMessage(0,160,288,20,5,1);
				mes.OpenMessage("Horobi.msg",145);
				mes.ReadDraw();
				mes.CloseMessage();
			}
			evFrameWait(100);
			if(crbaseSelectYesNo("�킢�܂����H",64,64) == 0){
				//---�키
				bat = 1;
			}
			evFrameWait(250);
		}
	}

	if(bat == 1){
		//---�o�g��
		CR_BATTLEINFO BattleInfo;
		memset(&BattleInfo,0,sizeof(BattleInfo));
		BattleInfo.MapNumber = crfieldGetMapNumber();
		BattleInfo.SceneNumber = crfieldGetMapScene();
		BattleInfo.Music = CRMUSIC_BOSSBATTLE1;
		BattleInfo.Enemy[0].Enemy = 207;
		BattleInfo.Enemy[1].Enemy = 208;
		BattleInfo.Enemy[2].Enemy = 209;
		BattleInfo.Enemy[3].Enemy = 210;
		BattleInfo.Enemy[4].Enemy = -1;
		BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
		BattleInfo.FailOK = 1;
		BattleInfo.LimitTurn = 8;
//		BattleInfo.MapNumber = 1;
		for(a = 0;a < 4;a ++){
			BattleInfo.Enemy[a].x = pCharacterInfo[a].GetBattleFieldStartX();
			BattleInfo.Enemy[a].y = 11 - pCharacterInfo[a].GetBattleFieldStartY();
		}
		evField(0,1);

		mcShow(0);

		npPos(0,16,11);
		npDir(0,NORTH);
		npPos(1,15,12);
		npDir(1,NORTH);
		npPos(2,17,12);
		npDir(2,NORTH);
		npPos(3,16,12);
		npDir(3,NORTH);
		crfieldChangeScene(2,16,12);

		int old = crbatSetBattleMagicMode(1);
		int oldkiz = crbatSetBattleKizetuMode(1);
		int olditem = crbatSetBattleItemMode(1);
		int result = crbatEventBattle(&BattleInfo);
		if(result == BATRET_WIN && !evGet(201)){
			//---�������I
			//---����
			for(a = 0;a < 3;a ++){
				evFrameWait(500);
				mes.CreateNewMessage(0,160,288,20,5,1);
				mes.OpenMessage("Horobi.msg",120 + a);
				mes.ReadDraw();
				mes.CloseMessage();
			}
			evFrameWait(500);

			evFadeOut(500,RGB_MAKE(255,255,255));
			evFieldNoFlip(0,1);
			evFadeIn(2000,RGB_MAKE(255,255,255));

			//---�ǂ����H
			evFrameWait(500);
			npMove(1,0,-1);
			evFrame();
			evFrameWait(250);
			npDir(1,EAST);
			evFrameWait(250);

			mes.OpenMessage("Horobi.msg",123);
			mes.ReadDraw();

			evFrameWait(500);
			npDir(0,EAST);
			evFrameWait(250);
			npDir(0,NORTH);
			evFrameWait(250);
			npDir(0,WEST);
			evFrameWait(250);
			mes.ReadDraw(4);

			//---���ꂪ�̖̂��@��
			evFrameWait(250);
			mes.ReadDraw();

			evFrameWait(250);
			npMove(2,0,-1);
			evFrame();
			evFrameWait(250);
			npDir(2,WEST);
			evFrameWait(250);
			mes.ReadDraw();

			evFrameWait(500);
			mes.ReadDraw();
			evFrameWait(250);

			mes.CloseMessage();

			mcShow(1);
			mcDir(SOUTH);
			evMap(10,0,370,154);
			evSet(201,1);
		} else if(result == BATRET_WIN || evGet(201)){
			//---�Q���ڈȍ~
			mcShow(1);
			mcDir(SOUTH);
			evMap(10,0,370,154);
			evSet(201,1);
		} else {
			//---������
			evFrameWait(500);
			//---�����
			if(!evGet(202)){
				mes.CreateNewMessage(0,160,288,20,5,1);
				mes.OpenMessage("Horobi.msg",130);
				mes.ReadDraw();
				mes.CloseMessage();
			}
			evSet(202,1);
			evFrameWait(500);
			//---�o�����Ă���
			{
				mes.CreateNewMessage(0,160,288,20,5,1);
				mes.OpenMessage("Horobi.msg",131);
				mes.ReadDraw();
				mes.CloseMessage();
			}
			evFrameWait(250);

			mcShow(1);
			mcDir(SOUTH);
			crfieldChangeMap(10,0,1,1);
			crfieldChangeScene(0,370,154);
			evFadeOut(1000,RGB_MAKE(255,255,255));
			evFieldNoFlip(0,1);
			evFadeIn(1000,RGB_MAKE(255,255,255));
		}
		crbatSetBattleMagicMode(old);
		crbatSetBattleKizetuMode(oldkiz);
		crbatSetBattleItemMode(olditem);

		prtRecoveryAll();
	}

	return 1;
}

//---�A���V�A�A���[���h
CREVENTLONG5_API int creventAlsia_World(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	crfieldChangeScene(3,8,8);

	npPos(0,8,4);
	npDir(0,SOUTH);

	npPos(1,7,8);
	npDir(1,NORTH);
	npPos(2,8,7);
	npDir(2,NORTH);
	npPos(3,9,7);
	npDir(3,NORTH);
	npPos(4,10,8);
	npDir(4,NORTH);

	evScene(3,8,8);

	evFrameWait(250);
	mes.OpenMessage("Alsia.msg",104);
	mes.ReadDraw();
	//---���傤��
	evFrameWait(250);
	mes.ReadDraw(2);
	//---���������
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	for(a = 0;a < 3;a ++){
		if(a < 1)
			npMove(3,0,-1);
		else if(a < 2)
			npMove(3,-1,0);
		else
			npMove(3,0,-1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw(2);

	//---����͂��Ă���
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);


	//---�Ԃ��
	evReloadMap(0);
	crfieldChangeScene(0,41,27);
	npPos(23,42,25);
	npDir(23,NORTH);
	npPos(24,41,26);
	npDir(24,SOUTH);
	npPos(27,40,26);
	npDir(27,SOUTH);

	evScene(0,41,27);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---���i������
	evFrameWait(500);
	npDir(23,WEST);
	evFrameWait(250);
	npDir(23,SOUTH);
	evFrameWait(250);
	for(a = 0;a < 1;a ++){
		npMove(23,0,1);
		evFrame();
	}
	evFrameWait(250);

	//---�����Ƃ�
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

	//---���΂���񌻂�I
	npPos(26,52,25);
	npDir(26,NORTH);
	for(a = 0;a < 8;a ++){
		npMove(26,-1,0);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	//---�E�E�E
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(27,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	//---�ߊ�邨�΂����
	evFrameWait(250);
	for(a = 0;a < 3;a ++){
		npMove(26,-1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(26,SOUTH);
	evFrameWait(250);

	npDir(24,EAST);
	evFrameWait(125);
	npDir(23,WEST);
	evFrameWait(125);
	npDir(24,NORTH);
	evFrameWait(125);
	npDir(23,NORTH);
	evFrameWait(125);
	npDir(27,EAST);
	evFrameWait(250);
	npDir(27,NORTH);
	evFrameWait(250);

	mes.ReadDraw(3);

	//---�Ƃ�Ȃ���
	evFrameWait(250);
	mes.ReadDraw(2);

	//---������
	evFrameWait(250);
	mes.ReadDraw(3);

	//---���ǂ�
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(26,WEST);
	evFrameWait(250);
	for(a = 0;a < 20;a ++){
		if(a < 5)
			npMove(26,-1,0);
		else if(a < 9)
			npMove(26,0,1);
		else
			npMove(26,-1,0);
		if(a == 4)
			npDir(27,WEST);
		evFrame();
	}
	//---�}�V���K���g�[�N
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(23,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(24,WEST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---���܂���
	npPos(25,28,29);
	npDir(25,WEST);
	for(a = 0;a < 13;a ++){
		if(a < 6)
			npMove(25,1,0);
		else if(a < 8)
			npMove(25,0,-1);
		else if(a < 10)
			npMove(25,1,0);
		else if(a < 11)
			npMove(25,0,-1);
		else if(a < 13)
			npMove(25,1,0);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(2);
	//---�ǂ����H
	evFrameWait(250);
	npDir(24,NORTH);
	evFrameWait(250);
	for(a = 0;a < 4;a ++){
		if(a < 1)
			npMove(24,0,-1);
		else if(a < 3)
			npMove(24,-1,0);
		else
			npMove(24,0,1);
		evFrame();
	}
	evFrameWait(250);
	npDir(24,WEST);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	for(a = 23;a <= 27;a ++){
		npDelete(a);
	}

	mes.CloseMessage();

	mcShow(1);
	mcDir(SOUTH);
	evScene(0,77,48);

	evSet(203,1);

	return 1;
}

