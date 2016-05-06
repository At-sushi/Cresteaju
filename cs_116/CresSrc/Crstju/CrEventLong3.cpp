/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrEventLong3.cpp ...Event functions

-----------------------------------------------------------*/


#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CREVENTLONG3

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#include "CrBase.h"
#include "CrBattle.h"
#include "CrEvent.h"
#include "CrEvCom.h"

//---game info
#define CR_GAMEINFO_EXTERNPOINTER
#include "CrGameInfo.h"

//---�A���V�A�A�f�B�U�ƃi�b�N�̗��A��
CREVENTLONG3_API int creventAlsia_Satogaeri(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	crfieldChangeMap(51,0,1,1);
	npPos(23,80,48);
	npDir(23,WEST);
	npPos(24,80,49);
	npDir(24,WEST);
	npPos(25,78,48);
	npDir(25,WEST);
	evScene(0,77,50);

	evFrameWait(1000);

	mes.OpenMessage("Alsia.msg",100);
	mes.ReadDraw(3);

	//---�i�b�N�s��
	evFrameWait(500);
	for(a = 0;a < 16;a ++){
		npMove(25,-1,0);
		evFrame();
	}
	evFrameWait(500);
	//---���ꂢ�ȂƂ���
	npMove(23,-1,0);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	npMove(24,-1,0);
	evFrame();
	evFrameWait(250);
	npDir(24,NORTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---�f�B�U�͂Ȃ�Ŗ����m����Ȃ��́H
	evFrameWait(500);
	npDir(23,SOUTH);
	evFrameWait(500);
	mes.ReadDraw(4);
	evFrameWait(500);

	//---�ό��ē�
	evFrameWait(500);
	npDir(23,WEST);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---�\
	evFrameWait(500);
	for(a = 0;a < 2;a ++){
		npMove(23,-1,0);
		evFrame();
	}
	npDir(24,WEST);
	evFrameWait(250);
	npDir(23,SOUTH);
	evFrameWait(250);
	npDir(23,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw(3);
	evFrameWait(500);

	//---�Ƃ��납�����
	npPos(23,40,26);
	npDir(23,SOUTH);
	npPos(24,41,26);
	npDir(24,SOUTH);

	npPos(26,51,25);
	npDir(26,SOUTH);
	evScene(0,41,29);

	evFrameWait(1000);
	mes.ReadDraw(2);
	//---���΂����o��I�I
	evFrameWait(1000);
	for(a = 0;a < 7;a ++){
		npMove(26,-1,0);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	//---������Ƃ��������
	evFrameWait(250);
	npDir(24,EAST);
	evFrameWait(250);
	npDir(23,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	//---���΂���񂳂�ɋ߂Â�
	evFrameWait(500);
	for(a = 0;a < 4;a ++){
		npMove(26,-1,0);
		if(a == 2)
			npDir(24,NORTH);
		if(a == 3)
			npDir(23,NORTH);
		evFrame();
	}
	evFrameWait(250);
	npDir(26,SOUTH);
	evFrameWait(500);
	mes.ReadDraw(2);
	//---�i�b�N����Ȃ���
	evFrameWait(500);
	mes.ReadDraw(2);

	//---�́H
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---�ȂɏƂ�Ă�̂�
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(6);

	//---�r�炵�߂�����
	evFrameWait(500);
	npDir(26,WEST);
	evFrameWait(250);
	for(a = 0;a < 16;a ++){
		if(a < 5)
			npMove(26,-1,0);
		else if(a < 8)
			npMove(26,0,1);
		else
			npMove(26,-1,0);
		if(a == 2)
			npDir(24,WEST);
		if(a == 4)
			npDir(23,WEST);
		evFrame();
	}
	npPos(26,0,0);
	npShow(26,0);
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---���V�̉�
	npPos(23,26,27);
	npDir(23,NORTH);
	npPos(24,27,27);
	npDir(24,NORTH);
	evScene(0,26,29);

	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---�Q�K��
	crfieldChangeScene(3,9,7);
	npPos(1,12,11);
	npPos(2,12,11);
	npDir(0,NORTH);
	evScene(3,12,11);

	evFrameWait(1000);
	npShow(2,1);
	npDir(2,WEST);
	for(a = 0;a < 4;a ++){
		npMove(2,-1,0);
		if(a == 2){
			npShow(1,1);
			npDir(1,WEST);
		}
		evFrame();
	}
	npDir(2,NORTH);
	for(a = 0;a < 3;a ++){
		npMove(1,-1,0);
		npMove(2,0,-1);
		evFrame();
	}
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	for(a = 0;a < 3;a ++){
		npMove(1,0,-1);
		evFrame();
	}
	evFrameWait(500);

	for(a = 0;a < 6;a ++){
		if(a < 3)
			mcMove(-1,0);
		else
			mcMove(0,-1);
		evFrame();
	}
	//---�您
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(0,EAST);
	evFrameWait(500);
	npDir(0,SOUTH);
	evFrameWait(500);

	//---�f�B�U�ł͂Ȃ���
	evFrameWait(500);
	mes.ReadDraw();

	//---�ڂ������H
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---����
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(1,NORTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---�p���́H
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();

	//---����̂��Ƃ��H
	evFrameWait(1000);
	mes.ReadDraw();

	//---�m���Ă�̂�
	evFrameWait(250);
	mes.ReadDraw(3);

	//---�I�����~������
	evFrameWait(500);
	npMove(2,0,-1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();

	//---��
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---�ʐl
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---�����
	evFrameWait(2000);
	mes.ReadDraw(2);

	//---�����񂶂�����
	evFrameWait(1000);
	mes.ReadDraw(3);
	//---���肪�Ƃ��������܂���
	evFrameWait(500);
	npMove(1,0,-1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---�U��Ԃ�
	npDir(2,EAST);
	evFrameWait(250);
	npDir(2,SOUTH);
	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);

	mes.ReadDraw();

	//---�U���Ȃ�
	npDir(1,WEST);
	evFrameWait(125);
	npDir(2,WEST);
	evFrameWait(125);
	npDir(1,NORTH);
	evFrameWait(125);
	npDir(2,NORTH);
	evFrameWait(250);

	mes.ReadDraw(2);

	//---���킯���I
	evFrameWait(250);
	mes.ReadDraw(3);
	//---����
	evFrameWait(500);
	mes.ReadDraw(5);

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---�s������
	evFrameWait(500);
	npDir(2,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---�ĂъO
	crfieldChangeScene(0,26,29);
	npPos(23,30,23);
	npShow(23,0);
	npPos(24,30,23);
	npShow(24,0);
	evScene(0,26,29);

	evFrameWait(500);
	npShow(24,1);
	npDir(24,WEST);
	evFrameWait(250);
	for(a = 0;a < 11;a ++){
		if(a < 4)
			npMove(24,-1,0);
		else if(a < 8)
			npMove(24,0,1);

		if(a < 4){
		} else if(a < 7)
			npMove(23,-1,0);
		else if(a < 11)
			npMove(23,0,1);

		if(a == 3){
			npShow(23,1);
			npDir(23,WEST);
		}

		evFrame();
	}
	evFrameWait(250);
	npDir(23,WEST);
	evFrameWait(250);

	//---���C�Ȃ���������
	mes.ReadDraw(3);

	evFrameWait(500);
	npDir(24,EAST);
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---����
	npPos(23,60,19);
	npDir(23,NORTH);
	npPos(24,59,18);
	npDir(24,NORTH);
	evScene(0,59,22);

	evFrameWait(1000);
	mes.ReadDraw();
	crmusicFadeOut();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	crmusicStop();

	//---�e�́E�E�E
	evFrameWait(1500);
	crmusicPlay(CRMUSIC_ENDLESSP);
	mes.ReadDraw(2);

	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw(3);

	//---�f�B�U
	evFrameWait(1000);
	mes.ReadDraw();

	//---�Y��Ȃ�
	evFrameWait(2000);
	mes.ReadDraw();

	//---�͂��߂�
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---�f�B�U�A���߂�
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(24,EAST);
	evFrameWait(250);
	npDir(24,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();
	//---�b���������Ƃ�����Ȃ�
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---�i�b�N����
	npPos(25,59,34);
	npDir(25,NORTH);
	for(a = 0;a < 12;a ++){
		npMove(25,0,-1);
		evFrame();
	}
	evFrameWait(500);

	mes.ReadDraw();
	evFrameWait(500);
	npDir(23,WEST);
	evFrameWait(250);
	npDir(23,SOUTH);
	evFrameWait(500);

	mes.ReadDraw(2);

	//---�q�ɂ������Ă݂邩
	for(a = 0;a < 2;a ++){
		npMove(24,0,1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw(3);

	//---�f�B�U�s��
	evFrameWait(500);
	npDir(24,WEST);
	evFrameWait(250);
	for(a = 0;a < 12;a ++){
		if(a < 1)
			npMove(24,-1,0);
		else
			npMove(24,0,1);
		if(a == 4)
			npDir(25,WEST);
		if(a == 6)
			npDir(25,SOUTH);
		evFrame();
	}
	//---����
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(800);
	npDir(25,WEST);
	evFrameWait(250);
	npDir(25,NORTH);
	evFrameWait(250);

	for(a = 0;a < 4;a ++){
		npMove(25,0,-1);
		if(a == 2)
			npDir(23,WEST);
		if(a == 3)
			npDir(23,NORTH);
		evFrame();
	}
	//---��
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	em->Put(59,17,2,98);

	evFrameWait(1000);
	mes.ReadDraw();

	//---�嗤����ŁE�E�E
	evFrameWait(1000);
	mes.ReadDraw(2);

	evFrameWait(1000);
	mes.ReadDraw();

	//---�ł��������ɂ�
	evFrameWait(500);
	npDir(25,EAST);
	evFrameWait(250);
	npDir(25,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();
	//---�Y��Ȃ��悤�ɂ��Ȃ����
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();

	//---�����
	evFrameWait(500);
	npDir(25,EAST);
	evFrameWait(250);
	npDir(25,NORTH);
	evFrameWait(1700);
	mes.ReadDraw();
	evFrameWait(1500);
	crmusicFadeOut();
	evFrameWait(1000);

	//---������I
	npDir(25,EAST);
	evFrameWait(250);
	npDir(25,SOUTH);
//	evFrameWait(500);
	crmusicPlay(CRMUSIC_INIT);
	evFrameWait(2000);
	evReloadMapMusic();
	mes.ReadDraw();
	evFrameWait(500);

	mes.CloseMessage();

	mcShow(1);
	mcDir(SOUTH);
	evReloadMap(0);
	em->Put(59,17,2,98);
	evScene(0,59,19);
	evSet(121,1);

	return 1;
}


//---�A���V�A�A�f�B�U�̉�
CREVENTLONG3_API int creventAlsia_DizzasHome(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	crfieldChangeScene(2,9,7);
	npPos(1,2,2);
	npShow(1,0);
	npPos(2,5,8);
	npDir(2,NORTH);
	npPos(3,2,2);
	npShow(3,0);
	evScene(2,9,7);

	evFrameWait(1000);
	npDir(3,EAST);
	evFrameWait(250);

	for(a = 0;a < 5;a ++){
		npMove(3,1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	npDir(3,SOUTH);
	for(a = 0;a < 3;a ++){
		npMove(1,1,0);
		evFrame();
	}
	npDir(3,SOUTH);
	evFrameWait(250);

	//---���Z����񂢂�́H
	mes.OpenMessage("Alsia.msg",102);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(500);

	for(a = 0;a < 10;a ++){
		if(a < 6)
			npMove(3,0,1);
		else if(a < 7)
			npMove(3,-1,0);

		if(a < 1){
		} else if(a < 3)
			npMove(1,1,0);
		else
			npMove(1,0,1);
		evFrame();
	}
	npDir(2,EAST);
	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(500);
	for(a = 0;a < 3;a ++){
		if(a < 2)
			mcMove(0,1);
		else
			mcMove(-1,0);
		evFrame();
	}

	//---�������{�̗�
	evFrameWait(500);
	mes.ReadDraw(4);

	//---�i�b�N�[�э��
	evFrameWait(500);
	npDir(3,NORTH);
	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(250);
	for(a = 0;a < 12;a ++){
		if(a < 1)
			npMove(3,1,0);
		else if(a < 6)
			npMove(3,0,-1);
		else if(a < 11)
			npMove(3,-1,0);
		else if(a < 12)
			npMove(3,0,-1);
		evFrame();
	}
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	//---�킽������`����
	mes.ReadDraw();
	evFrameWait(500);
	for(a = 0;a < 1;a ++){
		npMove(1,0,-1);
		evFrame();
	}
	//---�҂�
	evFrameWait(100);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	//---�����ł����̂��H
	evFrameWait(1000);
	mes.ReadDraw(3);

	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---���ג�
	npPos(2,3,8);
	npDir(2,NORTH);
	npPos(1,6,8);
	npDir(1,NORTH);

	evScene(2,8,10);
	evFrameWait(1500);
	mes.ReadDraw();

	//---���i���ړ�
	evFrameWait(1500);
	npDir(1,WEST);
	evFrameWait(250);
	npMove(1,-1,0);
	evFrame();
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);

	//---�t�@�X���N���A
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(2,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	//---�x�z�҂̏�
	evFrameWait(500);
	npDir(1,WEST);
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw(2);

	//---�������[�I�[�u��
	evFrameWait(1000);
	npDir(1,NORTH);
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(1000);
	npDir(1,WEST);
	evFrameWait(1000);
	mes.ReadDraw(2);
	//---�킽�����L�������߂����āE�E�E
	evFrameWait(1000);
	mes.ReadDraw(3);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---���i���̓��i��
	evFrameWait(250);
	npDir(2,SOUTH);
	evFrameWait(250);
	for(a = 0;a < 4;a ++){
		if(a < 2)
			npMove(2,0,1);
		else
			npMove(2,1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);

	evFrameWait(500);
	mes.ReadDraw();
	//---����
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);

	for(a = 1;a <= 3;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}

	evScene(4,15,15);
	evFrameWait(1000);
	//---���肪�Ƃ�
	mes.ReadDraw();
	evFrameWait(1000);

	//---����
	prtRecoveryAll();
	crfieldChangeScene(0,34,64);
	npPos(23,33,62);
	npDir(23,EAST);
	npPos(24,35,62);
	npDir(24,WEST);
	npPos(25,34,63);
	npDir(25,NORTH);
	evScene(0,34,64);

	evFrameWait(500);
	mes.ReadDraw(5);
	evFrameWait(500);

	for(a = 23;a <= 25;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}

	mcShow(1);
	mcDir(SOUTH);
	evScene(0,34,63);
	evSet(122,1);

	mes.CloseMessage();

	return 1;
}

//---��N���[�^�[�A���I
CREVENTLONG3_API int creventGreatCrater_Visit(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	crfieldChangeMap(52,0,1);
	npPos(0,31,6);
	npDir(0,SOUTH);
	npPos(1,32,6);
	npDir(1,SOUTH);
	npPos(2,33,6);
	npDir(2,SOUTH);
	evScene(0,32,58);

	for(a = 0;a < 49;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(1000);

	mes.OpenMessage("GreatCrater.msg",100);
	mes.ReadDraw();
	evFrameWait(500);
	//---�͂��߂āH
	npDir(1,WEST);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();

	//---覐΂Ƃ�
	evFrameWait(500);
	npDir(1,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---���i���A�`��
	evFrameWait(500);
	npMove(0,0,1);
	evFrame();
	evFrameWait(1000);
	mes.ReadDraw(3);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);

	mes.CloseMessage();

	evSet(123,1);
	mcShow(1);
	mcDir(NORTH);
	evMap(10,0,227,54);

	return 1;
}

//---�Z�m�E�A���I
CREVENTLONG3_API int creventCenow_Visit(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	crfieldChangeMap(54,0,1);
	npPos(0,28,44);
	npDir(0,NORTH);
	npPos(1,27,45);
	npDir(1,NORTH);
	npPos(2,29,45);
	npDir(2,NORTH);

	npPos(3,26,27);
	npDir(3,WEST);
	evScene(0,28,48);

	evFrameWait(1000);
	for(a = 0;a < 4;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(1000);
	//---�����́H
	mes.OpenMessage("Cenow.msg",100);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(1000);

	//---�����Ă݂�
	for(a = 0;a < 14;a ++){
		if(a < 12)
			npMove(0,0,-1);
		if(a > 1)
			npMove(1,0,-1);
		if(a > 2)
			npMove(2,0,-1);
		evFrame();
	}
	for(a = 0;a < 9;a ++){
		mcMove(0,-1);
		evFrame();
	}
	//---���I
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	crmusicFadeOut();

	for(a = 0;a < 6;a ++){
		mcMove(0,-1);
		evFrame();
	}

	for(a = 0;a < 8;a ++){
		if(a < 2)
			npMove(0,0,-1);
		else if(a < 4)
			npMove(0,-1,0);
		else if(a < 5)
			npMove(0,0,-1);

		if(a < 1){
		} else if(a < 2)
			npMove(1,0,-1);
		else if(a < 4)
			npMove(1,-1,0);
		else if(a < 6)
			npMove(1,0,-1);

		if(a < 1){
		} else if(a < 3)
			npMove(2,0,-1);
		else if(a < 5)
			npMove(2,-1,0);
		else if(a < 8)
			npMove(2,0,-1);

		if(a == 5)
			npDir(3,SOUTH);

		evFrame();
	}
	for(a = 0;a < 1;a ++){
		mcMove(-1,0);
		evFrame();
	}
	crmusicStop();

	evFrameWait(1000);
	mes.ReadDraw(2);
	//---�Z�m�E����
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---�ǂ������H
	evFrameWait(500);
	npMove(1,0,-1);
	evFrame();
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(2,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	//---���i���E�E�E
	evFrameWait(1000);
	mes.ReadDraw();
	
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();
	//---���̑��ɂ��܂���
	evFrameWait(1000);
	npMove(0,0,-1);
	evFrame();
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(150);
	npDir(1,NORTH);
	evFrameWait(150);
	mes.ReadDraw();

	//---�H
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---��E�E�E�ȁE�E�E��E�E�E�H
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw(2);

	//---�Ȃɂ������Ă�񂶂�H
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---�Z�m�E�ŏ��������̂́E�E�E
	evFrameWait(1000);
	npDir(3,WEST);
	evFrameWait(1000);
	npDir(3,NORTH);
	evFrameWait(1000);

	npMove(3,0,-1);
	evFrame();
	evFrameWait(2000);
	mes.ReadDraw(2);

	//---���[�t�B�A
	evFrameWait(1000);
	npDir(3,EAST);
	evFrameWait(1000);
	npDir(3,SOUTH);
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(2000);
	mes.ReadDraw(2);
	//---��k�悹��I
	evFrameWait(250);
	npMove(1,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---���̎q�́E�E�E
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---�����
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---��������ł�
	evFrameWait(1000);
	npMove(2,0,-1);
	evFrame();
	evFrameWait(500);
	npDir(2,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	npDir(1,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

//	crmusicStop();
	crfieldChangeMap(32,6,1,0);
	evScene(6,12,12);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	crmusicPlay(CRMUSIC_ENDLESSP);

	//---�N���X�t�B�[���h
	crfieldChangeScene(5,12,11);
	npPos(0,14,9);
	npDir(0,SOUTH);
	npPos(1,13,9);
	npDir(1,EAST);
	evReadObject(7,"Gazell.acf");
	evReadObject(12,"LunarnSlp4.acf");
	evScene(5,2,2);

	evFrameWait(1000);
	for(a = 0;a < 10;a ++){
		mcMove(1,0);
		evFrame();
	}
	for(a = 0;a < 9;a ++){
		mcMove(0,1);
		evFrame();
	}
//	evScene(5,12,11);

	evFrameWait(4000);
	npDir(0,WEST);
	evFrameWait(100);
	npDir(0,SOUTH);
	evFrameWait(1000);
	npDir(0,WEST);
	evFrameWait(1000);

	//---�C�Â������I�H
	mes.ReadDraw();
	evFrameWait(1000);
	npDir(0,SOUTH);
	evFrameWait(100);
	npDir(0,WEST);
	evFrameWait(900);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---�N�H
	evFrameWait(1000);
	npDir(0,NORTH);
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(2000);
	mes.ReadDraw();
	//---���A���i���H
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);

	//---�܂�����
	evScene(6,12,12);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw(3);
	evFrameWait(1000);
	mes.ReadDraw();

	//---������
	evFrameWait(2000);
	mes.ReadDraw(2);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	//---�R�������킯
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(250);
	crmusicFadeOut();
	evFrameWait(2000);
	crmusicPlay(CRMUSIC_INIT);
	et->Delay2(2000);

	//---�ĂуZ�m�E
	crfieldChangeMap(54,0,1,0);
	npPos(0,28,33);
	npDir(0,SOUTH);
	npPos(1,27,34);
	npDir(1,NORTH);
	npPos(2,29,33);
	npDir(2,WEST);
	evScene(0,28,45);

	for(a = 0;a < 10;a ++){
		npMove(0,0,1);
		npMove(1,0,1);
		npMove(2,0,1);
		evFrame();
	}
	npMove(1,1,0);
	evFrame();
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(500);

	//---�Ȃ�
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(2,WEST);

	//---����܋C�ɂ���ȁE�E�E
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	//---�t�^
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(2,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---�킽���ɂ́E�E�E
	evScene(1,15,15);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	evScene(0,28,45);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(250);
	npMove(1,-1,0);
	evFrameWait(250);
	evFrame();
	npDir(1,SOUTH);

	for(a = 0;a < 16;a ++){
		npMove(0,0,1);
		if(a > 0)
			npMove(1,0,1);
		if(a > 0)
			npMove(2,0,1);
		evFrame();
	}
	evFrameWait(250);
	mcDir(SOUTH);
	mcShow(1);
	evMap(10,0,254,33);

	mes.CloseMessage();
	evSet(124,1);

	return 1;
}

//---�[�r�A�}�C���A�Y�B���w��
CREVENTLONG3_API int creventZevia_BuyMineSuit(int event)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	evFrameWait(250);

	mes.OpenMessage("ZeviaMine.msg",100);
	mes.ReadDraw();
	evFrameWait(250);
	if(event == 22)
		mcDir(NORTH);
	else
		mcDir(EAST);
	evFrameWait(250);
	mes.ReadDraw(3);

	evFrameWait(500);

	//---�}�b�v�����[�h
	evReloadMap(0);
	npPos(27,41,43);
	npDir(27,NORTH);
	npPos(28,40,43);
	npDir(28,NORTH);
	npPos(29,39,43);
	npDir(29,NORTH);
	mcShow(0);
	evScene(0,40,45);

	//---����ō���c
	evFrameWait(1000);
	mes.ReadDraw(2);
	//---�Ȃɂɂ�ɂ�
	evFrameWait(500);
	npDir(28,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(27,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	//---��������g�}�g
	evFrameWait(500);
	npDir(28,NORTH);
	evFrameWait(500);
	mes.ReadDraw(3);

	//---�{��񂾂�
	evFrameWait(500);
	npDir(28,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(28,NORTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---�l���悤��
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(27,NORTH);
	evFrameWait(500);

	evFrameWait(1000);
	mes.ReadDraw(3);

	evFrameWait(500);
	npDir(27,WEST);
	evFrameWait(500);
	mes.ReadDraw(3);

	//---����
	evFrameWait(500);
	npDir(29,EAST);
	evFrameWait(2000);

	//---����A��k��
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(28,EAST);
	evFrameWait(250);
	//---���ꂶ�Ⴀ
	mes.ReadDraw();
	evFrameWait(250);

	//---�Ƃ��납�����
	npPos(27,44,23);
	npDir(27,EAST);
	npPos(28,45,23);
	npDir(28,WEST);
	npPos(29,44,22);
	npDir(29,EAST);
	npPos(17,50,29);
	npDir(17,WEST);
	evScene(0,47,25);
	evFrameWait(500);
	mes.ReadDraw(4);
	//---���������I
	evFrameWait(250);
	npDir(29,EAST);
	npMove(29,1,0);
	evFrame();
	npDir(29,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---�܂���
	evFrameWait(250);
	npDir(28,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---�����X
	for(a = 0;a < 8;a ++){
		if(a < 6)
			mcMove(0,1);
		else
			mcMove(1,0);
		if(a == 1)
			npDir(28,NORTH);
		if(a == 2)
			npDir(28,EAST);
		if(a == 4)
			npDir(29,EAST);
		evFrame();
	}

	for(a = 0;a < 12;a ++){
		if(a < 3)
			npMove(28,1,0);
		else if(a < 10)
			npMove(28,0,1);
		else
			npDir(28,EAST);

		if(a < 1){
		} else if(a < 4)
			npMove(27,1,0);
		else if(a < 10)
			npMove(27,0,1);
		else
			npDir(27,EAST);

		if(a < 1){
		} else if(a < 4)
			npMove(29,1,0);
		else if(a < 10)
			npMove(29,0,1);
		else
			npDir(29,EAST);

		evFrame();
	}

	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	npMove(27,1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);

	//---�΂��A�����Ǝ��R��
	evFrameWait(250);
	npDir(28,NORTH);
	evFrameWait(250);
	mes.ReadDraw(3);

	evFrameWait(250);
	npDir(28,EAST);
	evFrameWait(500);
	//---���݂܂���
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(2);

	//---����Ȃ�ł����H
	evFrameWait(1000);
	npDir(17,NORTH);
	evFrameWait(500);
	npDir(17,EAST);
	evFrameWait(500);
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(17,1,0);
		else
			npMove(17,0,-1);
		evFrame();
		if(a == 0){
			evFrameWait(500);
			npDir(17,NORTH);
			evFrameWait(500);
		}
	}
	evFrameWait(1500);
	npDir(17,WEST);
	evFrameWait(500);
	npDir(17,SOUTH);
	evFrameWait(500);
	for(a = 0;a < 3;a ++){
		if(a < 1)
			npMove(17,0,1);
		else
			npMove(17,-1,0);
		evFrame();
		if(a == 0){
			evFrameWait(500);
			npDir(17,WEST);
			evFrameWait(500);
		}
	}
	evFrameWait(1000);
	npMove(17,1,0,0);
	evFrame();
	evFrameWait(1000);

	mes.ReadDraw(2);
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---���ŋ�
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(28,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	//---�������܂���
	evFrameWait(250);
	npDir(27,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(29,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---�A�낤��
	evFrameWait(250);
	npDir(28,WEST);
	evFrameWait(250);
	npDir(28,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---�ގU
	evFrameWait(250);
	npDir(29,WEST);
	evFrameWait(250);
	npDir(29,NORTH);
	evFrameWait(250);

	for(a = 0;a < 8;a ++){
		if(a < 6)
			mcMove(0,-1);
		else
			mcMove(-1,0);
		evFrame();
	}
	for(a = 0;a < 12;a ++){
		if(a < 5)
			npMove(29,0,-1);
		else if(a < 9)
			npMove(29,-1,0);

		if(a < 7)
			npMove(28,0,-1);
		else if(a < 10)
			npMove(28,-1,0);

		if(a < 5)
			npMove(27,0,-1);
		else if(a < 8)
			npMove(27,-1,0);
		evFrame();
	}

	evFrameWait(250);
	npDir(29,SOUTH);
	evFrameWait(150);
	npDir(27,NORTH);
	evFrameWait(150);
	npDir(29,EAST);
	evFrameWait(500);

	mes.ReadDraw();
	//---�����Ȃ�
	evFrameWait(500);
	npDir(28,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(300);
	npDir(28,WEST);
	evFrameWait(200);
	npDir(27,WEST);
	evFrameWait(300);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(28,SOUTH);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---�킽�������Ă����
	evFrameWait(300);
	npDir(27,NORTH);
	evFrameWait(300);
	mes.ReadDraw(2);
	evFrameWait(500);

	for(a = 27;a <= 29;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	mcShow(1);
	evScene(0,45,24);

	evSet(125,1);

	return 1;
}

//---�[�r�A�}�C���A�N���C�V�u����
CREVENTLONG3_API int creventMine_CrasiveAppear(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	evReloadMap(1);
	crfieldChangeScene(0,16,46);
	npPos(26,0,0);
	npShow(0,0);

	evSet(126,0);
	npPos(27,16,45);
	npDir(27,NORTH);
	npPos(28,16,44);
	npDir(28,SOUTH);
	npPos(29,15,44);
	npDir(29,EAST);
	evScene(0,16,46);

	evFrameWait(500);
	mes.OpenMessage("Mine.msg",101);
	mes.ReadDraw(3);
	evFrameWait(500);

	//---�����I
	crmusicStop();
	crsoundPlay(CRSOUND_FIRE1);
	evFrameWait(250);
	crsoundPlay(CRSOUND_FIRE2);
	evFrameWait(300);
	crsoundPlay(CRSOUND_FIRE3);

	evFrameWait(150);
	npDir(27,EAST);
	evFrameWait(150);
	//---�ȂɁI�H
	mes.ReadDraw();

	//---
	evFrameWait(500);
	crmusicPlay(CRMUSIC_HEAT);
	mes.ReadDraw();
	evFrameWait(150);
	npDir(28,EAST);
	evFrameWait(150);
	//---�Y�B�I�H
	mes.ReadDraw();
	evFrameWait(250);

	//---�l�X
	{
		npPos(6,32,23);
		npDir(6,NORTH);
		npPos(7,33,23);
		npDir(7,NORTH);
		npPos(8,27,23);
		npDir(8,NORTH);
		npPos(9,35,23);
		npDir(9,NORTH);

		npPos(10,24,24);
		npDir(10,NORTH);
		npPos(11,28,24);
		npDir(11,NORTH);
		npPos(12,31,24);
		npDir(12,NORTH);
		npPos(13,34,24);
		npDir(13,NORTH);

		npPos(14,26,25);
		npDir(14,NORTH);
		npPos(15,27,25);
		npDir(15,NORTH);
		npPos(16,32,25);
		npDir(16,NORTH);
		npPos(17,37,25);
		npDir(17,NORTH);

		npPos(18,28,26);
		npDir(18,NORTH);
		npPos(19,30,26);
		npDir(19,NORTH);
		npPos(20,34,26);
		npDir(20,NORTH);
		npPos(21,36,26);
		npDir(21,NORTH);
	}

	npPos(30,32,55);
	npDir(30,NORTH);
	eiMapObject *np = npGet(30);
	np->Data.MoveSpeed = 4;

	//33,24
	for(a = 0;a < 16;a ++){
		mcMove(1,0);
		npMove(30,0,-1);
		evFrame();
	}
	npPos(27,23,45);
	npPos(28,22,44);
	npPos(29,21,44);
	for(a = 0;a < 6;a ++){
		npMove(27,1,0);
		npMove(28,1,0);
		npMove(29,1,0);
		evFrame();
	}
	//---���̐l���āE�E�E
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);

	//---���~
	evReadObject(1,"TwMin2m_down.acf");
	npPos(30,33,25);

	npPos(31,31,11);
	npDir(31,NORTH);
	for(a = 0;a < 22;a ++){
		mcMove(0,-1);
		if(a == 0)
			npDir(28,NORTH);
		if(a == 1)
			npDir(27,NORTH);
		if(a == 2)
			npDir(29,NORTH);
		evFrame();
	}

//	crmusicFadeOut();
	evFrameWait(1000);
	//---�N���C�V�u������
	for(a = 0;a < 10;a ++){
		mcMove(0,-1);
		evFrame();
	}

	evFrameWait(1000);
	npDir(31,WEST);
	evFrameWait(500);
	npDir(31,SOUTH);
	evFrameWait(2000);

	npDir(31,WEST);
	evFrameWait(500);
	npDir(31,NORTH);
	evFrameWait(1000);
	for(a = 0;a < 2;a ++){
		npMove(31,0,-1);
		evFrame();
		evFrameWait(500);
	}

	for(a = 0;a < 32;a ++){
		mcMove(0,1);
		evFrame();
	}
	//---�N���C�V�u�I�I
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	for(a = 0;a < 3;a ++){
		npMove(28,0,-1);
		if(a > 0)
			npMove(29,0,-1);
		evFrame();
	}
	evFrameWait(150);
	npDir(28,EAST);
	evFrameWait(150);
	npDir(28,SOUTH);
	evFrameWait(150);

	//---�Ȃɂځ[���ƁI
	mes.ReadDraw();

	evFrameWait(150);
	npDir(29,EAST);
	evFrameWait(150);
	npDir(29,SOUTH);
	evFrameWait(150);
	mes.ReadDraw();

	//---�ӂ�����
	for(a = 0;a < 19;a ++){
		if(a == 0)
			npDir(28,EAST);
		if(a == 1)
			npDir(28,NORTH);
		if(a == 2)
			npDir(29,EAST);
		if(a == 3)
			npDir(29,NORTH);
		mcMove(0,-1);
		evFrame();
	}

	//---�₶���܂����ς�
	npPos(27,33,38);
	npPos(28,32,34);
	npPos(29,31,35);
	evFrameWait(1000);
	for(a = 0;a < 11;a ++){
		npMove(27,0,-1);
		if(a < 8)
			npMove(28,0,-1);
		if(a < 8)
			npMove(29,0,-1);
		evFrame();
	}

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---�Ȃɂځ[���Ƃ��Ă��񂾁H
	npDir(28,EAST);
	evFrameWait(250);
	npDir(28,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---���~�U��Ԃ�
	evFrameWait(500);
	npDir(30,WEST);
	evFrameWait(250);
	npDir(30,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	npDir(28,EAST);
	evFrameWait(250);
	npDir(28,NORTH);
	evFrameWait(500);

	//---����
	evReloadMap(1);
	npPos(27,45,45);
	npDir(27,WEST);
	npPos(28,44,44);
	npDir(28,SOUTH);
	npPos(29,44,46);
	npDir(29,NORTH);
	npPos(30,43,45);
	npDir(30,EAST);
	evScene(0,44,47);

	evFrameWait(500);
	mes.ReadDraw(3);
	//---���ŒY�B��
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(250);
	npDir(28,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---�N���C�V�u��
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(1000);
	mes.ReadDraw();
	//---���݂͂����Ȃ��I
	evFrameWait(250);
	npDir(29,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---�����炢�����傩�H
	evFrameWait(500);
	mes.ReadDraw(3);

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(29,NORTH);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---�I���̈ӌ��́H
	evFrameWait(500);
	npDir(28,SOUTH);
	evFrameWait(500);
	mes.ReadDraw(2);
	//---�c���
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	mes.CloseMessage();

	//---�f�B�U�B�����ɖ߂�
	pPartyInfo->PartyMember[1] = 1;
	pPartyInfo->PartyMember[2] = 2;
	//---���~���ԂɂȂ�
	{
		pPartyInfo->PartyMember[3] = 4;
		int level = crcharaGetPartyMember(0)->GetLevel();

		level += 2;
		if(level < 20)
			level = 20;
		if(level > 30)
			level = 30;

		crcharaSetLevelStatus(3,level);
		CrCharacter *pChara = crcharaGetPartyMember(3);
		pChara->SetWeapon(0,54);
		pChara->SetWeapon(1,0);
		pChara->SetProtector(0,112);
		pChara->SetProtector(1,151);
		pChara->SetProtector(2,258);
		pChara->SetAccessory(0,0);
		pChara->SetAccessory(1,0);
		pChara->SetBattleFieldStartPos(8,2);
		pChara->SetLevelExperience();
		crcharaLoadFace(-1);
		crcharaCheckBattleFieldPos(3);

		pChara->CharaInfo.MagicTable[0] = 41;
		pChara->AddMagicExperience(-15);
		pChara->CharaInfo.MagicTable[1] = 43;
		pChara->AddMagicExperience(-45);
		pChara->CharaInfo.MagicTable[2] = 47;
		pChara->AddMagicExperience(-20);
		pChara->CharaInfo.MagicTable[3] = 49;
		pChara->AddMagicExperience(-60);

		pChara->CharaInfo.MagicTable[4] = 11;
		pChara->AddMagicExperience(-10);
		pChara->CharaInfo.MagicTable[5] = 14;
		pChara->AddMagicExperience(-20);
		pChara->CharaInfo.MagicTable[6] = 15;
		pChara->AddMagicExperience(-30);
	}
	prtRecoveryAll();

	for(a = 27;a <= 30;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	mcShow(1);
	crfieldSetMainCharacter(1);
	mcDir(SOUTH);
	evScene(0,44,44);
	//---�t���b�O
	evSet(126,0);
	evSet(127,1);

	evReloadMap(0);

	return 1;
}

//---�[�r�A�}�C���A�Y�B�����`�f�B���}�X�q����
CREVENTLONG3_API int creventMine_DizzaHead(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	npPos(4,17,6);
	npDir(4,NORTH);

	evFrameWait(150);
	npDir(5,NORTH);
	evFrameWait(150);

	mes.OpenMessage("Mine.msg",100);
	mes.ReadDraw(2);

	for(a = 0;a < 5;a ++){
		mcMove(0,1);
		evFrame();
	}

	//---�ʍs�֎~
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---�߂�
	evFrameWait(500);
	npDir(4,EAST);
	evFrameWait(500);
	npDir(4,SOUTH);
	evFrameWait(500);

	for(a = 0;a < 4;a ++){
		npMove(4,0,1);
		if(a == 3)
			npDir(5,WEST);
		evFrame();
	}
	//---�܂�
	evFrameWait(100);
	mes.ReadDraw();
	evFrameWait(100);
	npMove(4,0,1);
	npDir(5,SOUTH);
	evFrame();
	evFrameWait(100);
	mes.ReadDraw(2);

	//---�Ȃ��H
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	npDir(4,EAST);
	evFrameWait(500);
	npDir(4,NORTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	//---�͂�
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(4,EAST);
	evFrameWait(500);
	npDir(4,SOUTH);
	evFrameWait(500);

	//---�G�^�[�i������
	npPos(6,17,19);
	npDir(6,NORTH);
	for(a = 0;a < 7;a ++){
		npMove(6,0,-1);
		evFrame();
	}
	for(a = 0;a < 1;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(250);
	//---�I
	mes.ReadDraw();
	evFrameWait(250);
	npDir(5,WEST);
	evFrameWait(250);
	npMove(5,-1,0);
	evFrame();
	npDir(5,SOUTH);
	evFrameWait(250);
	//---
	mes.ReadDraw(2);
	//---���̂΂ꂽ��
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(1000);
	mes.ReadDraw();
	//---����
	evFrameWait(250);
	mes.ReadDraw();

	//---�߂炦��I
	evFrameWait(250);

	npPos(7,17,19);
	npDir(7,NORTH);

	for(a = 0;a < 5;a ++){
		if(a < 1)
			npMove(4,-1,0);
		else if(a < 3)
			npMove(4,0,1);
		else if(a < 4)
			npMove(4,1,0);
		else if(a < 5)
			npMove(4,0,1);

		if(a == 2)
			npDir(6,WEST);
		if(a == 3)
			npDir(6,SOUTH);
		evFrame();
	}

	evFrameWait(100);
	crmusicPlay(CRMUSIC_HEAT);
	mes.ReadDraw();
	for(a = 0;a < 4;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(4,0,1);
		npMove(6,0,1);
		npMove(7,0,-1);
		evFrame();
	}
	evFrameWait(500);
	for(a = 0;a < 1;a ++){
		npMove(4,0,-1,0);
		evFrame();
	}
	evFrameWait(1000);
	for(a = 0;a < 1;a ++){
		npMove(7,0,-1);
		evFrame();
	}

	//---�Ö��K�X
	crsoundPlay(CRSOUND_WIND1);
	evFadeOut(50,RGB_MAKE(255,255,255));
	evFieldNoFlip(0,1);
	evFadeIn(50,RGB_MAKE(255,255,255));
	evFrameWait(100);

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

	//---���i���̖�
	crmusicFadeOut();
	evFadeOut(2000);

	crfieldChangeMap(48,0,1,0);
	crfieldChangeScene(0,8,8);
	crmusicStop();
	mcShow(0);
	evFieldNoFlip(0,1);
	evWait(2000,1);
	evFadeIn(2000);
	evFrameWait(3000);

	//---���ꂩ��̂́E�E�E
	npPos(3,13,5);
	npDir(3,WEST);
	evFrameWait(500);
	npMove(3,-1,0);
	evFrame();
	evFrameWait(250);

	for(a = 0;a < 5;a ++){
		npMove(3,-1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(1000);
	npDir(0,NORTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---�͂�
	evFrameWait(1000);
	mes.ReadDraw();
	//---��Ă����̂��H
	evFrameWait(500);
	npDir(1,EAST);
	evFrameWait(500);
	for(a = 0;a < 2;a ++){
		npMove(1,1,0);
		evFrame();
	}
	evFrameWait(500);
	npDir(1,NORTH);
	evFrameWait(500);
	mes.ReadDraw(2);
	//---�]��łȂ��I
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	evFadeOut(2000);

	crfieldChangeMap(55,3,1,0);
	em->Put(14,4,2,52);
	npPos(0,13,4);
	npDir(0,EAST);
	evReadObject(12,"Lunarn2.acf");
	npPos(2,10,1);
	npDir(2,NORTH);

	npPos(1,0,0);
	npShow(1,0);
	crfieldChangeScene(3,10,6);

	evFieldNoFlip(0,1);
	evFadeIn(2000);
	evFrameWait(2000);
	//---���i���ڂ��o�܂�
	mes.ReadDraw();
	evReloadMapMusic();
	evFrameWait(1000);
	npDir(2,SOUTH);
	evFrameWait(100);
	npDir(2,NORTH);
	evFrameWait(100);
	npDir(2,SOUTH);
	evFrameWait(1000);

	mes.ReadDraw();

	//---�f�B���}�o��
	evFrameWait(500);
	npDir(0,NORTH);
	evFrameWait(500);
	npDir(0,WEST);
	evFrameWait(500);
	for(a = 0;a < 3;a ++){
		npMove(0,-1,0);
		evFrame();
	}
	evFrameWait(500);
	npDir(0,NORTH);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(3);

	//---�������[�I�[�u���o��
	evFrameWait(500);
	npDir(0,WEST);
	evFrameWait(500);
	npDir(0,SOUTH);
	evFrameWait(500);
	for(a = 0;a < 6;a ++){
		if(a < 2)
			npMove(0,0,1);
		else
			npMove(0,-1,0);
		evFrame();
	}
	evFrameWait(500);
	npDir(0,NORTH);
	evFrameWait(1500);

	evFrameWait(500);
	npDir(0,EAST);
	evFrameWait(500);
	for(a = 0;a < 5;a ++){
		if(a < 4)
			npMove(0,1,0);
		else
			npMove(0,0,-1);
		evFrame();
	}
	evFrameWait(500);
	//---����
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw(2);

	//---��Ֆړ��Ă��낤
	evFrameWait(1000);
	mes.ReadDraw(4);

	//---�������H
	evFrameWait(500);
	npMove(0,0,-1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw(2);

	//---����ɋ߂Â�
	npMove(0,0,-1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);
	//---����ɋ߂Â�
	npMove(0,0,-1);
	evFrame();
	evFrameWait(500);
	//---�t�@�C�A�{�[��
	mes.ReadDraw();
	evFrameWait(100);

	crsoundPlay(CRSOUND_FIRE2);
	evFadeOut(50,RGB_MAKE(255,0,0));
	evFieldNoFlip(0,1);
	evFadeIn(50,RGB_MAKE(255,0,0));
	evFrameWait(100);

	//---���Ⴀ
	for(a = 0;a < 2;a ++){
		npMove(0,0,1,0);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	//---�N���I�I
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	//---
	npPos(1,10,17);
	npDir(1,NORTH);
	for(a = 0;a < 1;a ++){
		mcMove(0,1);
	}
	for(a = 0;a < 11;a ++){
		npMove(1,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(4);

	//---�V���i�`
	evFrameWait(250);
	mes.ReadDraw(2);

	//---��������o��
	evFrameWait(250);
	npPos(3,10,16);
	npDir(3,NORTH);
	npPos(4,10,17);
	npDir(4,NORTH);
	for(a = 0;a < 8;a ++){
		npMove(3,0,-1);
		npMove(4,0,-1);
		if(a == 6)
			npDir(1,EAST);
		if(a == 7)
			npDir(1,SOUTH);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(3);
	//---���v�������H
	evFrameWait(250);
	npDir(4,EAST);
	evFrameWait(250);
	npMove(4,1,0);
	evFrame();
	npMove(4,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---�f�B�U�O��
	evFrameWait(250);
	for(a = 0;a < 10;a ++){
		if(a < 1)
			npMove(3,0,-1);
		else if(a < 2)
			npMove(3,-1,0);
		else if(a < 7)
			npMove(3,0,-1);
		else if(a < 8)
			npMove(3,1,0);
		if(a == 3)
			npDir(1,WEST);
		if(a == 4)
			npDir(1,NORTH);
		if(a == 6)
			npDir(0,WEST);
		if(a == 7)
			npDir(0,NORTH);

		evFrame();
	}
	//---�O���
	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(1000);
	evReadObject(12,"Lunarn.acf");
	npDir(2,SOUTH);
	npMove(2,0,1);
	npMove(3,0,1,0);
	evFrame();
	evFrameWait(500);
	//---���炩�邩
	mes.ReadDraw();

	//---�ق��ɁI�H
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(150);
	npDir(0,SOUTH);
	evFrameWait(150);
	npDir(0,EAST);
	evFrameWait(150);
	npDir(0,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(500);
	//---�����Ă߂�
	mes.ReadDraw();
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(150);
	npDir(0,NORTH);
	evFrameWait(250);
	//---���Ƃ΂�
	crsoundPlay(CRSOUND_ATACK4);
	evFill(ep->MakeRGB(255,255,255));
	ew->Flip();
	et->Delay2(50);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(1,WEST);
	npMove(0,0,1,0);
	npMove(3,0,1);
	evFrame();
	npDir(1,NORTH);
	evFrameWait(250);
	//---�����ɂ��i�؂�
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);

	//---���A�����ȁE�E�E
	evFrameWait(500);
	mes.ReadDraw();
	//---���̉�
	evFrameWait(500);
	npDir(3,EAST);
	evFrameWait(500);
	for(a = 0;a < 3;a ++){
		npMove(3,1,0);
		if(a == 2)
			npDir(0,EAST);
		if(a == 2)
			npDir(4,EAST);
		if(a == 1)
			npDir(1,EAST);
		if(a == 1)
			npDir(2,EAST);
		evFrame();
	}
	evFrameWait(500);
	em->Put(14,4,2,1024);
	crsoundPlay(CRSOUND_ATACK4);
	evFill(ep->MakeRGB(255,255,255));
	ew->Flip();
	et->Delay2(50);

	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	for(a = 0;a < 3;a ++){
		npMove(3,-1,0);
		if(a == 2)
			npDir(0,NORTH);
		if(a == 2)
			npDir(4,NORTH);
		if(a == 1)
			npDir(1,NORTH);
		if(a == 1)
			npDir(2,SOUTH);
		evFrame();
	}
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);

	//---�������Ȃ�
	mes.ReadDraw(2);

	//--�Ȃɂ�����Ȃ��������H
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---�܁A������
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(250);
	npDir(2,EAST);
	evFrameWait(250);
	for(a = 0;a < 8;a ++){
		if(a < 2)
			npMove(2,1,0);
		else if(a < 8)
			npMove(2,0,1);
		if(a < 4){
		} else if(a < 5)
			npMove(1,-1,0);
		else if(a < 6)
			npMove(1,0,-1);
		else if(a < 7)
			npDir(1,EAST);
		else if(a < 8)
			npDir(1,SOUTH);
		evFrame();
	}
	npDir(3,EAST);
	evFrameWait(250);
	for(a = 0;a < 5;a ++){
		if(a < 1)
			npMove(4,-1,0);
		else
			npDir(4,NORTH);

		if(a < 1)
			npMove(3,1,0);
		else if(a < 4)
			npMove(3,0,1);
		if(a < 0)
			npDir(2,WEST);
		else if(a < 1)
			npDir(2,NORTH);

		if(a == 2)
			npDir(0,EAST);
		else if(a == 3)
			npDir(0,SOUTH);
		evFrame();
	}
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	npDir(3,NORTH);
	mcMove(0,1);
	evFrame();
	evFrameWait(250);

	//---������܂��܂���
	mes.ReadDraw();

	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);
	npMove(3,0,1);
	evFrame();
	evFrameWait(250);

	//---���҂���������
	mes.ReadDraw();
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(0,EAST);
	evFrameWait(500);
	npMove(0,1,0);
	evFrame();
	evFrameWait(250);
	npDir(0,SOUTH);
	//---�^���V
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(1000);
	npDir(2,WEST);
	evFrameWait(300);
	npDir(2,WEST);
	evFrameWait(300);
	npDir(4,EAST);
	evFrameWait(1500);

	for(a = 0;a < 2;a ++){
		npMove(3,0,-1);
		if(a == 1)
			npDir(4,NORTH);
		evFrame();
	}
	evFrameWait(150);
	npDir(2,NORTH);
	evFrameWait(1000);

	//---�O��
	mes.CloseMessage();

	return creventMine_CrasiveAppear();
}

//---�u�r�A�Y�O���C
ei_s32 minebatCallBack2(int turn,int action,int number,
				  ei_u32 com,CrCharacter *chara)
{
	if(action == 2){
		if(turn >= 1 && number == BATTLECHARA_STARTENEMY){
			//---���[�t�B�A�s����̋����I��
			return 0;
		}
		if(turn >= 1 && number == BATTLECHARA_STARTENEMY + 1){
			return 0;
		}
	}

	return 1;
}

//---�[�r�A�}�C���Y�B��ՁA�t�@�X���N���A
CREVENTLONG3_API int creventMine_FasraCrear(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	npPos(1,18,18);
	npDir(1,NORTH);
	npPos(2,19,18);
	npDir(2,NORTH);
	npPos(3,18,19);
	npDir(3,NORTH);
	npPos(4,17,18);
	npDir(4,NORTH);
	evScene(1,18,19);

	evFrameWait(500);
	mes.OpenMessage("Mine.msg",103);
	mes.ReadDraw(3);
	//---�~����҂�
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

	//---�o�g��
	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.Music = CRMUSIC_BOSSBATTLE1;
	BattleInfo.Enemy[0].Enemy = 100;
	BattleInfo.Enemy[0].x = 6;
	BattleInfo.Enemy[0].y = 7;
	BattleInfo.Enemy[1].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	BattleInfo.MapNumber = 1;
	evField(0,1);

	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}

	evFrameWait(1000);
	npDir(0,EAST);
	evFrameWait(500);

	npPos(9,18,17);
	npDir(9,EAST);
	evFrameWait(1000);
	//---���ꂪ�t�@�X���N���A
	mes.ReadDraw();
	evFrameWait(500);
	npShow(9,0);
	evFrameWait(500);
	//---�A�낤��
	mes.ReadDraw();
	evFrameWait(250);
	npDir(2,EAST);
	evFrameWait(250);

	npMove(2,1,0);
	evFrame();
	npDir(4,EAST);
	evFrameWait(100);
	//---�҂��āI
	mes.ReadDraw();
	evFrameWait(250);
	npDir(2,NORTH);
	npDir(1,EAST);
	evFrameWait(250);
	npDir(2,WEST);
	npDir(3,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	//---���Ă݂Ȃ���
	mes.ReadDraw();
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(150);
	npDir(3,SOUTH);
	evFrameWait(150);
	npDir(1,WEST);
	evFrameWait(150);

	for(a = 0;a < 1;a ++){
		npMove(3,-1,0);
		evFrame();
	}
	evFrameWait(150);
	npDir(3,NORTH);
	evFrameWait(150);

	mes.ReadDraw(2);
	//---�K�i�̏��
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);
	npDir(2,EAST);
	evFrameWait(250);
	//---�҂������Ȃ��
	mes.ReadDraw();
	evFrameWait(1000);

	//---�܂���
	mes.ReadDraw();
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(150);
	npDir(3,NORTH);
	evFrameWait(150);
	npDir(1,EAST);
	evFrameWait(150);
	npDir(3,EAST);
	evFrameWait(150);

	//---�A�Y�O���C�o��
	npPos(6,22,20);
	npDir(6,NORTH);
	crmusicPlay(CRMUSIC_ETERNAL);
	evFrameWait(100);
	for(a = 0;a < 2;a ++){
		npMove(6,0,-1);
		evFrame();
	}
	npPos(7,22,20);
	npDir(7,NORTH);
	evFrameWait(100);
	npDir(6,WEST);
	for(a = 0;a < 1;a ++){
		npMove(7,0,-1);
		npMove(2,-1,0,0);
		evFrame();
	}
	evFrameWait(100);
	npDir(7,WEST);
	evFrameWait(250);

	mes.ReadDraw(2);

	//---�N���X�e�B�[����
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);

	//---�E�E�E
	evFrameWait(500);
	mes.ReadDraw();

	//---�A�Y�O���C�̌��
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(250);
	mes.ReadDraw();

	//---�܂��ɐ_�̗͂�
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	//---��N���[�^�[��
	evFrameWait(500);
	mes.ReadDraw();
	//---�R��I
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(100);
	npMove(1,0,1);
	evFrame();
	evFrameWait(100);
	npDir(1,EAST);
	evFrameWait(150);
	mes.ReadDraw(2);

	//---�Ԃ��Ȃ����n��
	evFrameWait(500);
	mes.ReadDraw();

	//---����Ȃ���
	evFrameWait(250);
	npMove(1,1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	npMove(7,-1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();
	//---�Ȃɂ��Ă������킯�H
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	npMove(6,-1,0);
	evFrame();
	evFrameWait(500);
	//---�n���Ă��炨����
	mes.ReadDraw(2);

	//---�o�g��
	evFrameWait(250);

	//---�f�B�U�̑����؂�ւ�
	CrCharacter *pChara = crcharaGetPartyMember(1);
	int old = pChara->GetWeapon(0);
	pChara->SetWeapon(0,27);

	//---�o�g��
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.Music = CRMUSIC_ETERNALBATTLE;
	BattleInfo.Enemy[0].Enemy = 109;
	BattleInfo.Enemy[0].x = 4;
	BattleInfo.Enemy[0].y = 7;
	BattleInfo.Enemy[1].Enemy = 110;
	BattleInfo.Enemy[1].x = 8;
	BattleInfo.Enemy[1].y = 6;
	BattleInfo.Enemy[2].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	BattleInfo.MapNumber = 1;
	BattleInfo.ForceInputCommand = 1;
	BattleInfo.lpTurnCallBack = minebatCallBack2;
	evField(0,1);

	npPos(1,18,19);

	npPos(9,19,19);
	npDir(9,EAST);

	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
//		return MAINLOOP_BATTLEFAIL;
	}
	//---�f�B�U�̑������ɖ߂�
	pChara->SetWeapon(0,old);

	npDir(2,SOUTH);
	//---�t�@�X���N���A���
	npGet(9)->Data.MoveSpeed = 4;
	for(a = 0;a < 6;a ++){
		npMove(9,0,1,0);
		if(a == 3)
			npDir(1,SOUTH);
		evFrame();
	}
	evFrameWait(100);
	//---���܂����I
	mes.ReadDraw();
	evFrameWait(100);
	npDir(7,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---���E�E�E
	evFrameWait(500);
	crmusicStop();
	mes.ReadDraw();
	evFrameWait(250);
	npDir(6,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---�|��Ă�
	npPos(8,19,26);
	npDir(8,NORTH);
	npPos(5,18,26);
	npDir(5,EAST);

	npDir(4,SOUTH);
	//---�N���C�V��
	for(a = 0;a < 7;a ++){
		if(a == 2)
			npDir(3,SOUTH);
		mcMove(0,1);
		evFrame();
	}
	crmusicPlay(CRMUSIC_CRAYSIVE);
	evFrameWait(500);

	mes.ReadDraw(2);
	evFrameWait(500);

	for(a = 0;a < 7;a ++){
		mcMove(0,-1);
		evFrame();
	}
	npDir(4,WEST);
	evFrameWait(250);
	//---���~���苎��
	for(a = 0;a < 9;a ++){
		if(a < 1)
			npMove(4,-1,0);
		else if(a < 3)
			npMove(4,0,1);
		else if(a < 9)
			npMove(4,1,0);
		if(a == 7)
			npDir(1,EAST);
		evFrame();
	}
	npShow(4,0);
	//---���~�I�I
	evFrameWait(250);
	mes.ReadDraw();

	//---��������
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(7,WEST);
	evFrameWait(250);
	npDir(7,SOUTH);
	evFrameWait(250);
	//---�A�Y�O���C�ƃ��[�t�B�A����
	for(a = 0;a < 4;a ++){
		if(a < 1)
			npMove(7,0,1);
		else if(a < 2)
			npMove(7,1,0);
		else
			npShow(7,0);
		if(a == 1 || a == 2)
			npMove(6,0,1);
		if(a == 3)
			npMove(6,1,0);
		evFrame();
	}
	npShow(6,0);
	evFrameWait(500);
	npDir(1,SOUTH);
	evFrameWait(500);
	//---�Ȃ�̂���Ȃ񂾁H
	mes.ReadDraw();
	evFrameWait(500);

	for(a = 0;a < 7;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(500);
	npDir(5,NORTH);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	npMove(5,0,-1);
	evFrameWait(500);
	npDir(5,EAST);
	//---�t�@�X���N���A����ɂ���
	evFrameWait(1000);
	npShow(9,0);
	evFrameWait(900);

	evFrameWait(500);
	npDir(5,NORTH);
	evFrameWait(2000);
	npDir(5,WEST);
	evFrameWait(1000);
	npDir(5,SOUTH);
	evFrameWait(1000);

	npMove(5,0,1);
	evFrame();

	for(a = 0;a < 7;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(1000);
	mes.ReadDraw();
	crmusicFadeOut();
	evFrameWait(1000);

	//---���ǁE�E�E
	evFadeOut(2000);
	crfieldChangeMap(55,4,1,0);
	crfieldChangeScene(4,15,15);
	evFieldNoFlip(0,1);

	evFadeIn(500);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---�h���ɂ�
	crfieldChangeScene(1,13,6);
	npPos(3,12,5);
	npDir(3,EAST);
	npPos(4,13,6);
	npDir(4,NORTH);
	npPos(5,13,4);
	npDir(5,SOUTH);
	npPos(6,14,5);
	npDir(6,WEST);
	evScene(1,13,6);
	evReloadMapMusic();

	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);

	for(a = 3;a <= 6;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	mcDir(SOUTH);
	mcShow(1);
	evScene(1,12,5);

	mes.CloseMessage();
	evSet(132,1);

//	prtRecoveryAll();

	return 1;
}

