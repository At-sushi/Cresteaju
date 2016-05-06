/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrEventLong4.cpp ...Event functions

-----------------------------------------------------------*/


#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CREVENTLONG4

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#include "CrBase.h"
#include "CrBattle.h"
#include "CrEvent.h"
#include "CrEvCom.h"

//---game info
#define CR_GAMEINFO_EXTERNPOINTER
#include "CrGameInfo.h"

extern int crmainMainMenu(int mode);
CREVENTLONG4_API int creventTuriaEternal_Dasshutu2(void);


//---�[�r�A�}�C���A�T���B�A�[�Ƃ̍ĉ�
CREVENTLONG4_API int creventMine_Xavier(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	crfieldChangeScene(0,48,48);
	npPos(27,48,48);
	npDir(27,SOUTH);
	evScene(0,48,48);

	evReadObject(7,"Xavier.acf");
	npPos(31,37,43);
	npDir(31,NORTH);
	npPos(14,36,43);
	npDir(14,EAST);

	em->Put(36,42,2,59);
	em->Put(37,42,2,59);
	em->Put(38,42,2,59);

	evFrameWait(250);

	mes.OpenMessage("ZeviaMine.msg",103);
	mes.ReadDraw(2);

	//---���i������
	evFrameWait(250);
	npDir(27,WEST);
	evFrameWait(250);

	for(a = 0;a < 10;a ++){
		mcMove(-1,0);
		evFrame();
	}
	for(a = 0;a < 4;a ++){
		mcMove(0,-1);
		evFrame();
	}
	crmusicPlay(CRMUSIC_SAKABA);
	evFrameWait(500);
	npDir(31,EAST);
	evFrameWait(150);
	npDir(31,SOUTH);
	evFrameWait(150);
	npDir(31,WEST);
	evFrameWait(150);
	npDir(31,NORTH);
	evFrameWait(150);
	mes.ReadDraw(2);

	//---�������i��
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	//---�v���Ԃ�̍ĉ�
	npPos(27,45,45);
	npDir(27,WEST);
	npPos(28,44,46);
	npDir(28,NORTH);
	npPos(29,44,44);
	npDir(29,SOUTH);
	npPos(30,42,43);
	npDir(30,SOUTH);
	npPos(31,43,45);
	npDir(31,EAST);
	npDir(14,NORTH);
	em->Put(42,42,2,59);
	evScene(0,43,46);//44,45

	evFrameWait(500);
	mes.ReadDraw();

	//---�Ȃ��
	evFrameWait(500);
	mes.ReadDraw(2);
	//---�o�r���X�L�[�����
	evFrameWait(250);
	npDir(31,NORTH);
	evFrameWait(250);
	npDir(31,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---�o�r���X�L�[
	evFrameWait(250);
	npDir(14,EAST);
	evFrameWait(250);
	npDir(14,SOUTH);
	npDir(28,WEST);
	evFrameWait(250);
	npDir(29,WEST);

	npMove(14,0,1);
	evFrame();
	evFrameWait(250);
	npDir(14,EAST);
	npDir(30,WEST);
	evFrameWait(250);

	mes.ReadDraw();

	evFrameWait(500);
	npDir(14,NORTH);
	evFrameWait(250);
	npMove(14,0,-1);
	evFrame();
	evFrameWait(250);

	//---���ׂ��Ƃ�
	evFrameWait(250);
	npDir(28,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(29,SOUTH);
	evFrameWait(150);
	npDir(30,SOUTH);
	evFrameWait(150);

	//---�ł����̑O�ɋߋ���
	evFrameWait(250);
	npDir(31,SOUTH);
	evFrameWait(250);
	npDir(31,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	//---���̕ςȐl��
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(31,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	//---���̐l�͂�
	evFrameWait(250);
	npDir(29,WEST);
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---�͂��E�E�E
	mes.ReadDraw();
	evFrameWait(500);

	//---��
	npDir(29,SOUTH);
	npDir(31,EAST);
	evReloadMapMusic();
	evScene(0,43,46);
	evFrameWait(1000);
	mes.ReadDraw(3);

	//---�ԈႢ
	evFrameWait(250);
	mes.ReadDraw();

	//---�N���_�ł͂Ȃ�
	evFrameWait(500);
	mes.ReadDraw(2);
	//---����
	evFrameWait(500);
	mes.ReadDraw(5);

	//---�����`����
	evFrameWait(250);
	npDir(31,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	//---�������E�E�E
	evFrameWait(250);
	npDir(31,EAST);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---���肪�E�E�E
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(250);

	mes.CloseMessage();

	if(crbaseSelectYesNo("�����`���𕷂��܂����H",64,64) == 0){
		mes.FileMessage("ZeviaMine.msg",104);
	}

	evFrameWait(500);
	mes.OpenMessage("ZeviaMine.msg",105);
	mes.ReadDraw(2);

	//---�킢�ɕ��������Ă��ƁH
	evFrameWait(500);
	mes.ReadDraw(3);
	//---�킩���
	evFrameWait(500);
	mes.ReadDraw(2);

	//---���C�y�ł������
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(250);
	npDir(30,EAST);
	evFrameWait(250);
	npMove(30,1,0);
	evFrame();
	evFrameWait(250);
	npDir(30,SOUTH);

	evFrameWait(250);
	npDir(29,WEST);
	evFrameWait(150);
	npDir(27,NORTH);
	evFrameWait(150);
	npDir(29,NORTH);
	evFrameWait(150);
	npDir(31,NORTH);
	evFrameWait(150);
	//---���~�̐���
	evFrameWait(300);
	mes.ReadDraw(2);

	evFrameWait(300);
	mes.ReadDraw(5);

	//---�`����
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);
	//---�_���Ȃ�ق��́H
	evFrameWait(250);
	mes.ReadDraw(2);

	//---��j���[�X
	evFrameWait(500);
	npPos(16,40,54);
	npDir(16,NORTH);

	for(a = 0;a < 8;a ++){
		npMove(16,0,-1);
		evFrame();
	}
	evFrameWait(100);
	crmusicStop();
	mes.ReadDraw();
	//---�}�X�^�[�A�������āH
	evFrameWait(100);
	npDir(28,WEST);
	evFrameWait(100);
	npDir(27,WEST);
	npDir(4,EAST);
	npDir(7,NORTH);
	evFrameWait(100);
	npDir(29,WEST);
	npDir(31,WEST);
	npMove(4,1,0);
	evFrame();
	evFrameWait(100);
	npDir(7,WEST);
	npDir(4,SOUTH);
	npDir(14,EAST);
	evFrameWait(100);
	mes.ReadDraw();

	//---�����ł���E�E�E
	mes.ReadDraw();

	evFrameWait(250);
	for(a = 0;a < 3;a ++){
		npMove(16,0,-1);
		evFrame();
	}
	npDir(30,WEST);
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);

	//---����������
	mes.ReadDraw(2);

	//---�����܂����H
	evFrameWait(250);
	npDir(31,NORTH);
	evFrameWait(250);
	npDir(31,EAST);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---������߂�̂�
	evFrameWait(250);
	npDir(30,SOUTH);
	evFrameWait(250);
	npDir(28,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(29,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);
	//---��ɓ����
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	//---����͓y�΁[����
	crmusicPlay(CRMUSIC_SAKABA);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);

	//---����
	evReloadMap(1);
	evReadObject(7,"Xavier.acf");
	evScene(0,31,59);
	evFrameWait(1000);

	npPos(27,31,47);
	npDir(27,SOUTH);
	npPos(28,29,49);
	npDir(28,SOUTH);
	npPos(30,32,49);
	npDir(30,SOUTH);

	npPos(29,31,49);
	npPos(31,30,48);
	for(a = 0;a < 10;a ++){
		npMove(29,0,1);
		npMove(31,0,1);
		evFrame();
	}
	for(a = 0;a < 8;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(500);
	npMove(27,0,1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(28,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---�A���V�A�ցI
	for(a = 0;a < 10;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(29,WEST);
	evFrameWait(250);
	npDir(29,NORTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(500);

	//---�T���B�A�[�Ăђ��ԂɂȂ�
	{
		pPartyInfo->PartyMember[3] = 3;
		pPartyInfo->PartyMember[4] = 4;

		int level = crcharaGetPartyMember(0)->GetLevel();
		CrCharacter *pChara = crcharaGetPartyMember(3);

		if(level > pChara->GetLevel() && level < 30){
			//---���i���̕������������烌�x���Z�b�g
			crcharaSetLevelStatus(3,level + 1);
			pChara->SetLevelExperience();
		} else if(level > pChara->GetLevel() && level >= 30){
			//---���x���R�O�ȏゾ������
			crcharaSetLevelStatus(3,30);
			pChara->SetLevelExperience();
		}

		pChara->SetWeapon(0,54);
		pChara->SetWeapon(1,0);
		pChara->SetProtector(0,105);
		pChara->SetProtector(1,144);
		pChara->SetProtector(2,260);
		pChara->SetBattleFieldStartPos(4,4);
		crcharaLoadFace(-1);
		crcharaCheckBattleFieldPos(3);
	}
	prtRecoveryAll();

	//---�A���V�A�Ίݓ��A
	evMap(10,0,189 + 15,63);
	for(a = 0;a < 15;a ++){
		mcMove(-1,0);
		evFrame();
	}
	evFrameWait(1000);

	mcShow(1);
	mcDir(SOUTH);
	evMap(53,0,19,4);
	evFrameWait(500);
	mcMove(0,1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.CloseMessage();

	evSet(133,1);

	return 1;
}

//---�A���V�A�Ίݓ��A�A�΂ǂڂ�
CREVENTLONG4_API int creventAlsia_IntoLake(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	npPos(0,17,33);
	npDir(0,SOUTH);
	npPos(1,18,34);
	npDir(1,SOUTH);
	npPos(2,19,33);
	npDir(2,SOUTH);
	npPos(3,16,33);
	npDir(3,SOUTH);
	npPos(4,15,32);
	npDir(4,SOUTH);
	evScene(0,17,34);

	evFrameWait(500);
	mes.OpenMessage("AlsiaLake.msg",100);
	mes.ReadDraw(2);

	//---�T���B�A�[�΂�
	evFrameWait(250);
	for(a = 0;a < 4;a ++){
		npMove(3,0,1);
		evFrame();
	}
	for(a = 0;a < 2;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npMove(0,0,1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(250);
	//---�j�A�s��
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();
	//---�j���܂����
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	for(a = 0;a <= 4;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}

	crfieldChangeScene(1,14,11);
	npPos(0,15,9);
	npDir(0,NORTH);
	npPos(1,15,8);
	npDir(1,WEST);
	npPos(2,14,10);
	npDir(2,NORTH);
	npPos(3,16,11);
	npDir(3,WEST);
	npPos(4,13,11);
	npDir(4,SOUTH);
	evScene(1,14,11);

	evFrameWait(500);
	npDir(4,WEST);
	evFrameWait(250);
	npDir(4,NORTH);
	evFrameWait(250);
	npDir(4,EAST);
	evFrameWait(250);
	npDir(4,SOUTH);
	evFrameWait(250);
	//---���[�����I
	mes.ReadDraw();
	//---���낶��
	evFrameWait(500);
	npDir(1,SOUTH);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw(3);

	//---�S�R�m��Ȃ�����
	evFrameWait(500);
	npDir(2,WEST);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);

	for(a = 0;a <= 4;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	mcShow(1);
	mcDir(SOUTH);
	evScene(1,15,9);

	mes.CloseMessage();

	evSet(134,1);

/*
	evSet(EV_GS_NUMBERX,190);
	evSet(EV_GS_NUMBERY,64);
	evSet(136,1);
	mcDir(SOUTH);
	mcShow(1);
	evMap(10,0,189,64);
*/
	return 0;
}

//---�A���V�A�Ίݓ��A�A�O���E���h�V�b�v�Q�b�g�I�I
CREVENTLONG4_API int creventAlsia_GetGS(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	npPos(0,43,17);
	npDir(0,WEST);
	npPos(1,42,16);
	npDir(1,WEST);
	npPos(2,43,16);
	npDir(2,WEST);
	npPos(3,42,18);
	npDir(3,WEST);
	npPos(4,44,18);
	npDir(4,WEST);

	evScene(2,40,17);

	evFrameWait(500);
	npMove(1,-1,0);
	evFrame();
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(500);

	mes.OpenMessage("AlsiaLake.msg",102);
	mes.ReadDraw(2);
	//---������āI
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);
	for(a = 0;a < 4;a ++){
		if(a < 1)
			npMove(2,0,-1);
		else
			npMove(2,-1,0);
		evFrame();
	}
	crmusicFadeOut();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	//---�O���E���h�V�b�v
	for(a = 0;a < 21;a ++){
		npDir(1,WEST);
		mcMove(-1,0);
		evFrame();
	}
	crmusicPlay(CRMUSIC_GS);
	evFrameWait(2000);
	for(a = 0;a < 20;a ++){
		mcMove(1,0);
		evFrame();
	}

	evFrameWait(500);
	npMove(0,-1,0);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);

	//---���̒ʂ�
	evFrameWait(250);
	for(a = 0;a < 5;a ++){
		if(a < 4)
			npMove(3,-1,0);
		else
			npMove(3,0,-1);
		evFrame();
	}
	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(250);

	mes.ReadDraw();

	//---�Ȃ�ŁE�E�E
	evFrameWait(500);
	npMove(0,-1,0);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw(3);

	//---���R
	evFrameWait(500);
	mes.ReadDraw(3);

	//---�{���E�E�E
	evFrameWait(500);
	mes.ReadDraw();

	//---���������I�Ђǂ��I
	evFrameWait(500);
	npMove(3,1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);

	//---�������̓{���ł�
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	//---����荞��9,4 6:6

	crfieldChangeMap(59,1,1);
	npPos(0,8,4);
	npDir(0,EAST);
	npPos(1,4,3);
	npDir(1,SOUTH);
	npPos(2,4,4);
	npDir(2,NORTH);
	npPos(3,9,4);
	npDir(3,EAST);
	npPos(4,8,5);
	npDir(4,EAST);

	evScene(1,6,7);

	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(500);

//
	//---���c�������I
	mes.ReadDraw();
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---�܂ɂ゠��H
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---���i������I�I
	npPos(0,9,4);
	npDir(0,EAST);
	npPos(3,9,3);
	npDir(3,SOUTH);

	npPos(1,7,3);
	npDir(1,EAST);
	npPos(2,6,4);
	npDir(2,EAST);
	npPos(4,8,5);
	npDir(4,EAST);
	evScene(1,6,7);

	evFrameWait(1000);
	mes.ReadDraw();
	//---�N���b�`����
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	//---�M���q
	evFrameWait(1000);
	em->Put(10,3,2,24);
	evFrameWait(1000);
	//---�A�N�Z������
	crsoundPlay(CRSOUND_GS_FUMISUGI1);
	evFrameWait(1000);
	crsoundPlay(CRSOUND_GS_FUMISUGI2,EISOUND_PLAYLOOP);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(1000);
	crsoundStop(CRSOUND_GS_FUMISUGI2);
	crsoundPlay(CRSOUND_GS_SOUND,EISOUND_PLAYLOOP);

	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();

	//---�G���X�g
	evFrameWait(1000);
	crsoundStop(CRSOUND_GS_SOUND);
	crsoundPlay(CRSOUND_GS_ENSTO);

	//---�~�܂������ǁH
	evFrameWait(2000);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---���I
	npPos(0,9,3);
	npDir(0,SOUTH);
	npPos(3,9,4);
	npDir(3,EAST);

	npPos(1,7,3);
	npDir(1,EAST);
	npPos(2,6,4);
	npDir(2,EAST);
	npPos(4,8,5);
	npDir(4,EAST);

	em->Put(10,3,2,23);
	evScene(1,6,6);

	evFrameWait(1000);
	//---���i�I�I
	mes.ReadDraw();

	evFrameWait(1000);
	em->Put(10,3,2,24);
	evFrameWait(250);

	crsoundPlay(CRSOUND_GS_SOUND);//,EISOUND_PLAYLOOP);
	evFrameWait(500);
	em->Put(10,3,2,23);
	evFrameWait(150);
	em->Put(10,3,2,25);
	evFrameWait(500);


//	evChangeGroundShip();
	mcDir(WEST);
	mcShow(1);
	ef->SetMoveEnything(1);
	crfieldChangeMap(10,0,1,0);
	crfieldSetMainCharacter(3);
	evScene(0,188,63);
	evFrameWait(500);

	//---�t�B�[���h�I�I
	for(a = 0;a < 56;a ++){
		if(a < 1)
			mcMove(-1,0);
		else if(a < 4)
			mcMove(0,1);
		else if(a < 30)
			mcMove(1,0);
		else if(a < 35)
			mcMove(0,-1);
		else if(a < 39)
			mcMove(1,0);
		else if(a < 50)
			mcMove(0,-1);
		else if(a < 56)
			mcMove(1,0);
		evFrame();
	}
	evFrameWait(500);
	int x = ef->xGet(),y = ef->yGet();

	mcShow(0);
	crfieldChangeMap(59,1,1);
	npPos(0,9,3);
	npDir(0,SOUTH);
	npPos(3,9,4);
	npDir(3,EAST);

	npPos(1,7,3);
	npDir(1,EAST);
	npPos(2,6,4);
	npDir(2,EAST);
	npPos(4,8,5);
	npDir(4,EAST);
	em->Put(10,3,2,25);
	evScene(1,6,7);

	//---�Ȃ�ł킽���̂Ƃ��́H
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---�b�o��I
	mes.ReadDraw();
	evFrameWait(250);
	npDir(2,SOUTH);
	evFrameWait(250);

	for(a = 0;a < 9;a ++){
		if(a < 4)
			npMove(2,0,1);
		else
			npMove(2,1,0);
		if(a == 2)
			npDir(1,SOUTH);
		evFrame();
	}
	npShow(2,0);
	evFrameWait(500);

	//---�M�A�����H
	mes.ReadDraw(2);
	evFrameWait(500);
	npMove(4,1,0);
	evFrameWait(250);
	npDir(4,NORTH);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---�N���X�t�B�[���h��

	crfieldSetMainCharacter(1);

	crfieldChangeMap(10,0,1,0);
	mcShow(1);
	crfieldSetMainCharacter(3);
	mcDir(EAST);
	ef->SetMoveEnything(1);
	evScene(0,x,y);

	//---�t�B�[���h�I�I
	for(a = 0;a < 120;a ++){
		if(a < 14)
			mcMove(1,0);
		else if(a < 24)
			mcMove(0,-1);
		else if(a < 34)
			mcMove(1,0);
		else if(a < 40)
			mcMove(0,-1);
		else if(a < 56)
			mcMove(1,0);
		else if(a < 102)
			mcMove(0,1);
		else if(a < 120)
			mcMove(1,0);
		evFrame();
	}
	evFrameWait(500);

	mcShow(0);
	crfieldSetMainCharacter(1);

	crfieldChangeMap(32,6,1,0);
	crmusicFadeOut();
	evScene(6,15,15);

//	crsoundStop(CRSOUND_GS_SOUND);
	evFrameWait(2500);
	crmusicStop();
	mes.ReadDraw();
	evFrameWait(500);

	evSet(136,1);
	mes.CloseMessage();

	mcDir(SOUTH);
	mcShow(1);
	evMap(10,0,236,198);

	return 1;
}

//---�N���X�t�B�[���h�A�����錾�O
CREVENTLONG4_API int creventCresfield_Kenkokusengenmae(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	crfieldChangeMap(32,0);
	npPos(18,37,6);
	npDir(18,SOUTH);
	npPos(19,36,6);
	npDir(19,SOUTH);
	npPos(20,35,5);
	npDir(20,SOUTH);
	npPos(21,38,5);
	npDir(21,SOUTH);
	npPos(22,39,6);
	npDir(22,SOUTH);

	npPos(3,39,11);
	npDir(3,SOUTH);
	evReadObject(7,"Yumi.acf");

	evScene(0,37,10);
	evFrameWait(1000);

	mes.OpenMessage("Cresfield.msg",130);
	mes.ReadDraw(2);

	evFrameWait(1000);

	//---�T���B�A�[�����˂�
	for(a = 0;a < 7;a ++){
		if(a < 6)
			npMove(21,0,1);
		else
			npDir(21,EAST);
		evFrame();
	}
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);

	mes.ReadDraw(4);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);

	//---�T���B�A�[�߂��Ă���
	npDir(21,NORTH);
	evFrameWait(250);

	for(a = 0;a < 4;a ++){
		npMove(21,0,-1);
		if(a == 3)
			npDir(3,SOUTH);
		evFrame();
	}
	evFrameWait(250);

	//---��c
	mes.ReadDraw(2);

	//---�ǂ�����̂�
	evFrameWait(500);
	npDir(22,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	//---���������΂��O�Ȃ�ł���񂾁H
	evFrameWait(250);
	npDir(19,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(18,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	//---�����
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);

	mes.CloseMessage();

	for(a = 18;a <= 22;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	mcShow(1);
	mcDir(SOUTH);
	evScene(0,37,7);

	evSet(137,1);

	return 1;
}

//---�N���X�t�B�[���h�A�����錾�V���f�B�ƍĉ�
CREVENTLONG4_API int creventCresfield_KenkokusengenCindy(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	npTurn(9);
	evFrameWait(150);

	mes.OpenMessage("Cresfield.msg",132);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---�݂�ȂłȂ��悭�H
	npPos(3,7,4);
	npDir(3,SOUTH);
	npPos(4,7,6);
	npDir(4,NORTH);
	npPos(5,6,4);
	npDir(5,SOUTH);
	npPos(6,6,6);
	npDir(6,NORTH);
	npPos(7,5,5);
	npDir(7,EAST);
	npPos(9,8,5);
	npDir(9,WEST);
	evReadObject(7,"Yumi.acf");
	evSet(138,1);
	mcShow(0);
	evScene(4,7,7);

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---������ƋC�܂���
	evFrameWait(2000);
	//---�T���B�A�[�̘b��ӂ�
	evFrameWait(250);
	npDir(6,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	//---�����
	evFrameWait(3000);
	mes.ReadDraw();
	evFrameWait(2000);
	mes.ReadDraw();

	//---�V���f�B����
	evFrameWait(250);
	npDir(9,NORTH);
	evFrameWait(250);

	for(a = 0;a < 7;a ++){
		if(a < 3)
			npMove(9,0,-1);
		else
			npMove(9,1,0);
		if(a == 4)
			npDir(3,EAST);
		if(a == 6)
			npDir(4,EAST);
		evFrame();
	}
	npShow(9,0);
	evFrameWait(500);

	//---���ς�炸
	mes.ReadDraw();
	evFrameWait(500);
	npDir(5,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	for(a = 3;a <= 9;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}

	//---�h���Q�K�ɂ�
	crfieldChangeScene(3,3,10);
	npPos(0,3,9);
	npDir(0,SOUTH);
	npPos(1,4,10);
	npDir(1,WEST);
	npPos(2,3,11);
	npDir(2,NORTH);
	npPos(3,2,10);
	npDir(3,EAST);
	npPos(4,2,11);
	npDir(4,NORTH);
	evReadObject(7,"Yumi.acf");

	evScene(3,3,11);
	evFrameWait(500);

	mes.ReadDraw(2);
	//---�ǂ�����Ėh���́H
	evFrameWait(500);
	mes.ReadDraw(2);
	//---�T���B�A�[�̏���
	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(250);

	//---�I�����E�E�E
	evFrameWait(500);
	npDir(1,NORTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(250);
	mes.ReadDraw(2);
	//---���i���E�E�E
	evFrameWait(500);
	mes.ReadDraw();

	//---�����錾���Ă��E�E�E
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	mes.CloseMessage();

	for(a = 0;a <= 4;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}

	mcShow(1);
	mcDir(SOUTH);
	evScene(3,3,9);

	return 1;
}

//---�N���X�t�B�[���h�A�����錾�O��`�����錾�i�b�N�ƈꏏ
CREVENTLONG4_API int creventCresfield_KenkokusengenZennya(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	prtRecoveryAll();

	evFrameWait(250);
	crmusicFadeOut();
	evFadeOut(1000);

	crfieldPaletteChange(PALETTE_NIGHT);
	mcShow(0);
	crfieldChangeScene(0,30,35);
	for(a = 0;a < 100;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}

	npPos(18,31,25);
	npDir(18,SOUTH);

	et->Delay2(2000);
	crmusicStop();

	evFieldNoFlip(0,1);
	evFadeIn(2000);
	evFrameWait(2000);

	//---���i�������Ă���
	for(a = 0;a < 10;a ++){
		if(a < 4)
			npMove(18,0,1);
		else if(a < 5)
			npMove(18,-1,0);
		else if(a < 10)
			npMove(18,0,1);
		evFrame();
	}

	evFrameWait(1000);
	npDir(18,WEST);
	evFrameWait(500);

	npPos(19,18,32);
	npDir(19,SOUTH);
	for(a = 0;a < 6;a ++){
		npMove(18,-1,0);
		evFrame();
	}

	evFrameWait(1000);
	mes.OpenMessage("Cresfield.msg",134);
	mes.ReadDraw();
	evFrameWait(500);

	//---�f�B�U������
	evFrameWait(500);
	for(a = 0;a < 11;a ++){
		mcMove(-1,0);
		evFrame();
	}
	evFrameWait(1000);
	for(a = 0;a < 6;a ++){
		npMove(18,-1,0);
		evFrame();
	}
	evFrameWait(500);
	npDir(18,NORTH);
	evFrameWait(1000);
	//---�f�B�U�Ȃ�ŁE�E�E
	crmusicPlay(CRMUSIC_SEEK);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	//---�f�B�U���ĉ��ŁE�E�E
	evFrameWait(500);
	mes.ReadDraw(2);
	//---������������Ȃ�
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	//---�f�B�U������ς薳�����Ƃ��������H
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(250);
	mes.ReadDraw(2);
	//---�����E�E�E
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(18,EAST);
	evFrameWait(1000);
	for(a = 0;a < 2;a ++){
		npMove(18,1,0);
		evFrame();
	}
	npDir(19,EAST);
	evFrameWait(1000);
	//---�f�B�U�ɉ��
	mes.ReadDraw(2);

	//---��������Ȃ���
	evFrameWait(500);
	npDir(18,NORTH);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(18,0,-1);
		evFrame();
	}
	evFrameWait(250);
	npDir(18,WEST);
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(1000);
	mes.ReadDraw(2);

	//---��Ȃ��
	evFrameWait(500);
	mes.ReadDraw();
	//---�����ǁE�E�E
	evFrameWait(500);
	npDir(18,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---�݂�Ȃɂ݂͂�Ȃ�
	evFrameWait(500);
	npDir(18,WEST);
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw();
	//---�������
	evFrameWait(1000);
	mes.ReadDraw();
	//---�ł���
	evFrameWait(500);
	mes.ReadDraw(2);
	//---������Ƃ�����
	evFrameWait(500);
	npDir(19,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(19,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	//---�܂��̓G�^�[�i����
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---�������E�E�E
	evFrameWait(1000);
	npDir(18,SOUTH);
	evFrameWait(500);
	npMove(18,0,1);
	evFrame();
	evFrameWait(500);
	npDir(18,WEST);
	evFrameWait(500);
	for(a = 0;a < 2;a ++){
		npMove(18,-1,0);
		evFrame();
	}
	npDir(19,SOUTH);
	evFrameWait(1000);
	npDir(18,NORTH);
	evFrameWait(1500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();
	//---�������Ȃ�
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(19,EAST);
	evFrameWait(500);
	crmusicFadeOut();
	evFadeOut(2000);


	//---�����h���Q�K�ɂ�
	crfieldChangeScene(3,3,11);
	et->Delay2(2000);
	evReloadMap(1);
	npPos(0,3,9);
	npDir(0,SOUTH);
	npPos(1,4,10);
	npDir(1,WEST);
	npPos(2,3,11);
	npDir(2,NORTH);
	npPos(3,5,7);
	npDir(3,SOUTH);
	npPos(4,1,8);
	npDir(4,EAST);
	evReadObject(7,"Yumi.acf");

	evFieldNoFlip();
	evFadeIn();

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	//---�킽�������ɂ���
	evFrameWait(500);
	mes.ReadDraw();
	//---�ǂ����Ȃ�
	evFrameWait(500);
	npMove(4,1,0);
	evFrameWait(250);
	npDir(4,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	//---����
	evFrameWait(500);
	mes.ReadDraw(2);
	//---����
	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	//---�����Ă��܂�
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(250);
	for(a = 0;a < 45;a ++){
		if(a < 2)
			npMove(3,1,0);
		else if(a < 5)
			npMove(3,0,-1);
		else
			npMove(3,1,0);

		if(a < 4){
		} else if(a < 5)
			npDir(4,EAST);
		else if(a < 11)
			npMove(4,1,0);
		else if(a < 16)
			npMove(4,0,-1);
		else
			npMove(4,1,0);

		if(a < 20){
		} else if(a < 21)
			npDir(1,WEST);
		else if(a < 22)
			npDir(1,NORTH);
		else if(a < 23)
			npMove(1,0,-1);
		else if(a < 24){
			npDir(1,WEST);
			evFrameWait(1000);
			npDir(1,NORTH);
			evFrameWait(500);
		} else if(a < 27)
			npMove(1,0,-1);
		else if(a < 31)
			npMove(1,1,0);
		else if(a < 34)
			npMove(1,0,-1);
		else
			npMove(1,1,0);
		if(a == 30)
			crmusicFadeOut();

		evFrame();
	}
	//---���߂��
	evFrameWait(500);
	crmusicStop();

	mes.ReadDraw(2);
	evFrameWait(500);

	mes.CloseMessage();

	npPos(0,0,0);
	npShow(0,0);
	npPos(1,0,0);
	npShow(1,0);
	npPos(3,0,0);
	npShow(3,0);
	npPos(4,0,0);
	npShow(4,0);

	evSet(139,1);
	mcShow(1);
	mcDir(EAST);
	evScene(3,5,7);
	//---�͂���
	pPartyInfo->PartyMember[1] = 2;
	pPartyInfo->PartyMember[2] = -1;
	pPartyInfo->PartyMember[3] = -1;
	pPartyInfo->PartyMember[4] = -1;
	crcharaLoadFace(-1);

	return 1;
}

ei_s32 KenkokubatCallBack1(int turn,int action,int number,
				  ei_u32 com,CrCharacter *chara)
{
	CR_BATTLECOMMAND *pCommand = (CR_BATTLECOMMAND *)com;
	CrBattleCharacter *pChara = (CrBattleCharacter *)chara;

	if(action == 3){
		if(number == 0){
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
		return 1;
	}
	if(action == 1){
		if(number == 0){
			//---���[�t�B�A
			if(turn <= 1){
				pCommand->Main = BAT_COMMAND_WAIT;
			} else if(turn == 2){
				pCommand->Main = BAT_COMMAND_MAGIC;
				pCommand->Sub[0] = 45;
				pCommand->Hit = 0;
				pCommand->Range = BAT_TARGET_ENEMYRANGE | BAT_RANGE_CIRCLE3;
				pCommand->Target = (ei_u32)crbatRandomSelect(pChara,BAT_TARGET_ENEMY);
			} else if(turn == 3){
				pCommand->Main = BAT_COMMAND_WAIT;
				crbatDrawScene();
				CrMesManager mes;
				mes.CreateNewMessage(-1,-1,32,24,5);
				mes.OpenMessage("Cresfield.msg",143);
				mes.ReadMessage();
				mes.Draw();
				mes.CloseMessage();
			} else {
				pCommand->Main = BAT_COMMAND_WAIT;
			}
		} else if(number == 1){
			if(turn <= 1){
				pCommand->Main = BAT_COMMAND_WEAPON;
				pCommand->Sub[0] = 0;
				pCommand->Hit = 0;
				pCommand->Range = BAT_TARGET_ENEMYSINGLE;
				pCommand->Target = (ei_u32)crbatRandomSelect(pChara,BAT_TARGET_ENEMY);
			} else {
				pCommand->Main = BAT_COMMAND_WAIT;
			}
		} else {
			pCommand->Main = BAT_COMMAND_WAIT;
		}
	} else if(action == 2){
		if(number == 0){
			if(turn == 2){
				crbatDrawSceneWhile(500);
				CrMesManager mes;
				mes.CreateNewMessage(-1,-1,32,24,5);
				mes.OpenMessage("Cresfield.msg",142);
				mes.ReadMessage();
				mes.Draw();
				mes.CloseMessage();
			}
		} else if(number == 1){
			if(turn == 1){
				crbatDrawSceneWhile(500);
				CrMesManager mes;
				mes.CreateNewMessage(-1,-1,32,24,5);
				mes.OpenMessage("Cresfield.msg",140);
				mes.ReadMessage();
				mes.Draw();
				mes.CloseMessage();
			}
		}
		if(turn == 4 && number == 0){
			return 0;
		}
	}

	return 1;
}

//---�N���X�t�B�[���h�A�����錾�N���C�V������
CREVENTLONG4_API int creventCresfield_Kenkokusengen(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	evFrameWait(250);
	mes.OpenMessage("Cresfield.msg",135);
	mes.ReadDraw(3);
	//---�ł�
	evFrameWait(500);
	mes.ReadDraw(4);

	//---�f�B�U������
	evFrameWait(500);
	npPos(1,14,2);
	npDir(1,WEST);
	for(a = 0;a < 16;a ++){
		if(a < 7)
			npMove(1,-1,0);
		else if(a < 12)
			npMove(1,0,1);
		else if(a < 16)
			npMove(1,-1,0);
		evFrame();
	}
	npDir(1,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	mcDir(NORTH);
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);

	//---�ǂ�������
	mes.ReadDraw();
	evFrameWait(250);
	crmusicPlay(CRMUSIC_CRAYSIVE);
	mes.ReadDraw(3);
	evFrameWait(250);

	//---���
	crfieldChangeScene(0,20,20);
	//---���O
	for(a = 0;a < 100;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	int x,y;
	for(a = 0;a < 18;a ++){
		if(a == 12)
			continue;
		x = 54 + (a + 4) % 12  + (a < 5 ? eiRnd(2) - (a * 3) : 0);
		y = 54 + (a + 4) / 12;
		while(em->IsObject(x,y,1) != EF_NOFIND){
			x ++;
		}
		npPos(a,x,y);
		npDir(a,NORTH);
	}
	for(a = 34;a <= 47;a ++){
		x = 52 + (a * 2) % 14 + eiRnd(2);
		y = 52 + (a * 2) / 14;
		while(em->IsObject(x,y,1) != EF_NOFIND){
			x ++;
		}
		npPos(a,x,y);
		npDir(a,NORTH);
	}
	for(a = 48;a <= 57;a ++){
		x = 51 + (a * 3) % 15 + eiRnd(2);
		y = 49 + (a * 3) / 15;
		while(em->IsObject(x,y,1) != EF_NOFIND){
			x ++;
		}
		npPos(a,x,y);
		npDir(a,NORTH);
	}
	evReadObject(7,"Yumi.acf");
	evReadObject(0,"Asgray_down.acf");
	evReadObject(2,"Follne.acf");
	evReadObject(3,"Crasive.acf");
	evReadObject(4,"Fasra2.acf");
	mcShow(0);

	npPos(21,59,62);
	npDir(21,NORTH);
	npPos(22,60,61);
	npDir(22,NORTH);

	npPos(18,47,61);
	npDir(18,EAST);
	npPos(19,48,62);
	npDir(19,EAST);
	npPos(20,46,62);
	npDir(20,EAST);

	npPos(59,59,51);
	npDir(59,NORTH);
	npPos(60,61,51);
	npDir(60,WEST);
	npPos(61,55,51);
	npDir(61,EAST);
	npPos(62,58,51);
	npDir(62,SOUTH);

	evScene(0,58,64);
	evReadObject(1,"Rarfia.acf");

	evFrameWait(1000);
	//---�R�l����
	for(a = 0;a < 10;a ++){
		npMove(18,1,0);
		npMove(19,1,0);
		npMove(20,1,0);
		if(a == 5)
			npDir(21,WEST);
		if(a == 6)
			npDir(22,WEST);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();
	//---�A�Y�O���C���E�E�E
	evFrameWait(1000);
	mes.ReadDraw();

//	crmusicFadeOut();
	evFrameWait(500);
	for(a = 0;a < 9;a ++){
		mcMove(0,-1);
		evFrame();
	}
	npDir(18,NORTH);
	npDir(19,NORTH);
	npDir(20,NORTH);
	npDir(21,NORTH);
	npDir(22,NORTH);

	evFrameWait(1000);
	mes.ReadDraw(2);
	//---���Ȃ��Ȃɂ��E�E�E
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---�o�g���I
	{
		pPartyInfo->PartyMember[0] = 12;
		pPartyInfo->PartyMember[1] = 15;
		pPartyInfo->PartyMember[2] = -1;
		pPartyInfo->PartyMember[3] = -1;
		pPartyInfo->PartyMember[4] = -1;
		crcharaLoadFace(-1);
	}
	//---------------------------------
	a = 12;
	memset(&pCharacterInfo[a].CharaInfo,0,sizeof(pCharacterInfo[a].CharaInfo));
	sprintf(pCharacterInfo[a].CharaInfo.Name,"���[�t�B�A");
	pCharacterInfo[a].SetWho(a + 1);
	pCharacterInfo[a].SetMaxLP(9999);
	pCharacterInfo[a].SetLP(9999);
	pCharacterInfo[a].SetMaxMC(9999);
	pCharacterInfo[a].SetMC(9999);
	pCharacterInfo[a].SetWeapon(0,13);
	pCharacterInfo[a].SetProtector(0,91);
	pCharacterInfo[a].SetBattleFieldStartPos(3,3);
	pCharacterInfo[a].CharaInfo.level = 32;
	pCharacterInfo[a].CharaInfo.power = 250;
	pCharacterInfo[a].CharaInfo.vitality = 125;
	pCharacterInfo[a].CharaInfo.agility = 99;
	pCharacterInfo[a].CharaInfo.soul = 98;
	pCharacterInfo[a].CharaInfo.magic = 76;

	pCharacterInfo[a].CharaInfo.magic_experience = 0;
	pCharacterInfo[a].CharaInfo.sub_hit_prob = 100;

	pCharacterInfo[a].CharaInfo.MagicTable[0] = 45;
	//---------------------------------
	a = 15;
	memset(&pCharacterInfo[a].CharaInfo,0,sizeof(pCharacterInfo[a].CharaInfo));
	sprintf(pCharacterInfo[a].CharaInfo.Name,"�t�H�[����");
	pCharacterInfo[a].SetWho(a + 1);
	pCharacterInfo[a].SetMaxLP(9999);
	pCharacterInfo[a].SetLP(9999);
	pCharacterInfo[a].SetMaxMC(9999);
	pCharacterInfo[a].SetMC(9999);
	pCharacterInfo[a].SetWeapon(0,16);
	pCharacterInfo[a].SetProtector(0,91);
	pCharacterInfo[a].SetBattleFieldStartPos(9,5);
	pCharacterInfo[a].CharaInfo.level = 28;
	pCharacterInfo[a].CharaInfo.power = 120;
	pCharacterInfo[a].CharaInfo.vitality = 130;
	pCharacterInfo[a].CharaInfo.agility = 198;
	pCharacterInfo[a].CharaInfo.soul = 120;
	pCharacterInfo[a].CharaInfo.magic = 66;

	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = 0;
	BattleInfo.Enemy[0].Enemy = 99;
	BattleInfo.Enemy[0].x = 6;
	BattleInfo.Enemy[0].y = 9;
	BattleInfo.Enemy[1].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	BattleInfo.lpTurnCallBack = KenkokubatCallBack1;
	BattleInfo.DontShowAfterBattle = 1;
	evField(0,1);

	int old = crdataGetSystem()->BattleCameraAngle;
	crdataGetSystem()->BattleCameraAngle = 0;
	{
		crbatSetShowStatus(0);
		if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		}
		crbatSetShowStatus(1);
	}
	crdataGetSystem()->BattleCameraAngle = old;
	crhistSubBattleCount();

	evFrameWait(500);
//	crmusicFadeIn();
	evFrameWait(1000);
	//---�t�@�X���N���A���f����
	npMove(62,0,1);
	evFrame();
	evFrameWait(2000);

	//---�t�@�X���N���A��������
	evReadObject(3,"Crasive2.acf");
	evFrameWait(1000);
	npDir(62,SOUTH);
	npPos(63,58,52);
	npDir(63,NORTH);
	npPos(64,58,51);
	npDir(64,EAST);
	evFrameWait(2000);

	//---�󍂂��I
	npDir(62,NORTH);
	npPos(63,58,52);
	npDir(63,SOUTH);
	npPos(64,58,51);
	npDir(64,WEST);
	evFrameWait(1000);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw();

	//---���O
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	//---���O
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---���i��
	for(a = 18;a <= 22;a ++){
		npDir(a,NORTH);
	}
	for(a = 0;a < 9;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	//---�Ăѕ���
	for(a = 0;a < 9;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(1000);
	npDir(62,SOUTH);
	npPos(63,58,52);
	npDir(63,NORTH);
	npPos(64,58,51);
	npDir(64,EAST);
	evFrameWait(1000);
	//---�������܂�
	npShow(63,0);
	npShow(64,0);
	evFrameWait(500);

	evReadObject(3,"Crasive.acf");
	npDir(62,SOUTH);
	//---�����������Ƃ͂Ȃ���
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(1500);
	npDir(62,WEST);
	evFrameWait(1000);
	npDir(62,NORTH);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---����
	for(a = 0;a < 6;a ++){
		npMove(62,0,-1);
		evFrame();
		evFrameWait(500);
	}
	crmusicFadeOut();
	evFrameWait(1000);

	//---�h����c
	evSet(139,3);
	evSet(140,1);

	evFadeOut(2000);
	crfieldChangeScene(3,3,11);
	et->Delay2(500);
	evReloadMap(1);
	npPos(0,3,9);
	npDir(0,SOUTH);
	npPos(1,4,10);
	npDir(1,WEST);
	npPos(2,3,11);
	npDir(2,NORTH);
	npPos(3,2,10);
	npDir(3,EAST);
	npPos(4,2,11);
	npDir(4,NORTH);

	evReadObject(7,"Yumi.acf");

	evFieldNoFlip();
	evFadeIn();

	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();
	//---������I
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(500);
	npDir(3,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	//---����ŃG�^�[�i����
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);

	//---�V���f�B����
	evReadObject(1,"Cindy.acf");
	npPos(5,7,3);
	npDir(5,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		mcMove(0,-1);
		evFrame();
	}
	mes.ReadDraw(2);
	evFrameWait(500);

	//---�i�b�N�̓G�ΐS
	npPos(5,4,9);
	npDir(5,SOUTH);
	npDir(0,SOUTH);
	evScene(3,3,11);
	evFrameWait(500);
	mes.ReadDraw(2);
	//---�f�B�U�̔���
	evFrameWait(500);
	npDir(1,SOUTH);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(250);

	//---���e�������Ă����
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw(2);
	//---�T���B�A�[
	evFrameWait(500);
	npDir(3,SOUTH);
	evFrameWait(500);
	mes.ReadDraw(2);
	//---�s���Ă݂悤��
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(250);
	mes.ReadDraw();
	//---�݂�Ȃ��肪�Ƃ�
	evFrameWait(500);
	mes.ReadDraw();

	//---����
	evFrameWait(500);
	npDir(5,WEST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(100);
	npDir(0,EAST);
	evFrameWait(100);
	npDir(1,NORTH);
	evFrameWait(100);
	npDir(3,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	//---�����s������
	evFrameWait(500);
	mes.ReadDraw(2);

	//---�h�[�O����
	evFrameWait(500);
	mes.ReadDraw(4);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---�킩������
	evFrameWait(500);
	mes.ReadDraw(2);
	//---�I���͂ǂ����ł�
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(2,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	//---�T���B�A�[��������{��
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(250);
	for(a = 0;a < 5;a ++){
		if(a < 3)
			npMove(3,0,-1);
		else if(a < 5)
			npMove(3,1,0);
		if(a == 3)
			npDir(2,NORTH);
		if(a == 2)
			npDir(0,EAST);
		if(a == 3)
			npDir(0,NORTH);
		if(a == 4)
			npDir(1,NORTH);
		if(a == 3)
			npDir(5,NORTH);
		evFrame();
	}
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);

	mes.ReadDraw();
	evFrameWait(500);

	for(a = 0;a <= 5;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	mcShow(1);
	mcDir(SOUTH);
	evScene(3,4,8);
	{
		pPartyInfo->PartyMember[0] = 0;
		pPartyInfo->PartyMember[1] = 1;
		pPartyInfo->PartyMember[2] = 2;
		pPartyInfo->PartyMember[3] = 3;
		pPartyInfo->PartyMember[4] = 4;
		crcharaLoadFace(-1);
		for(a = 0;a < 5;a ++){
			crcharaCheckBattleFieldPos(a);
		}
	}

	mes.CloseMessage();

	return 1;
}

//---�N���X�t�B�[���h�A�O���E���h�V�b�v����������
CREVENTLONG4_API int creventCresfield_GotoTulia(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	evMap(60,0,11,17);
	evFrameWait(250);

	mes.OpenMessage("Cresfield.msg",137);
	mes.ReadDraw(2);
	//---�������I�I
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	for(a = 0;a < 4;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(500);
	for(a = 0;a < 2;a ++){
		npMove(1,0,-1);
		evFrame();
	}
	evFrameWait(500);
	//---�ق�Ƃ�
	mes.ReadDraw();

	evFrameWait(500);
	for(a = 0;a < 2;a ++){
		npMove(0,0,-1);
		evFrame();
	}
	evFrameWait(1000);
	mes.ReadDraw();
	//---�S�����肪�E�E�E
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	for(a = 0;a < 6;a ++){
		npMove(3,0,-1);
		evFrame();
	}
	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	//---�c�[���A��
	crfieldSetMainCharacter(1);

	crfieldChangeMap(10,0,1,0);
	mcShow(1);
	crfieldSetMainCharacter(4);
	mcDir(NORTH);
	ef->SetMoveEnything(1);
	evScene(0,237,198);
	evFrameWait(250);
	crmusicPlay(CRMUSIC_GS);
	for(a = 0;a < 4;a ++){
		mcDir(a);
		evFrameWait(150);
	}
	mcDir(EAST);
	crfieldSetMainCharacter(3);

	//---�t�B�[���h�I�I
	for(a = 0;a < 126;a ++){
		if(a < 24)
			mcMove(1,0);
		else if(a < 42)
			mcMove(0,1);
		else if(a < 50)
			mcMove(1,0);
		else if(a < 60)
			mcMove(0,1);
		else if(a < 115)
			mcMove(1,0);
		else if(a < 124)
			mcMove(0,1);
		else if(a < 126)
			mcMove(1,0);
		evFrame();
	}

	//---�c�[���A�����I�I
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

	npPos(NP_GS_CANTNUMBER,326,235);
	npDir(NP_GS_CANTNUMBER,NORTH);
	crfieldSetMainCharacter(1);

	evSet(141,1);

	mes.CloseMessage();

	return 1;
}

//---�c�[���A�A������
CREVENTLONG4_API int creventTuria_FirstVisit(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	crfieldChangeMap(61,0,1,1);
	npPos(43,19,1);
	npDir(43,SOUTH);
	npPos(44,18,1);
	npDir(44,SOUTH);
	npPos(45,17,1);
	npDir(45,SOUTH);
	npPos(46,18,0);
	npDir(46,SOUTH);
	npPos(47,20,0);
	npDir(47,SOUTH);
	evReadObject(1,"Yumi.acf");
	npPos(48,19,0);
	npDir(48,SOUTH);

	evScene(0,19,3);

	evFrameWait(500);
	mes.OpenMessage("Turia.msg",100);
	mes.ReadDraw(2);

	//---��������
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(44,0,1);
		evFrame();
	}
	evFrameWait(250);
	npDir(44,EAST);
	evFrameWait(250);
	npDir(44,NORTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(250);
	npMove(43,0,1);
	evFrame();
	npMove(45,0,1);
	npMove(46,0,1);
	evFrame();
	npMove(47,0,1);
	evFrame();


	//---���͖߂��
	evFrameWait(100);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(43,WEST);
	evFrameWait(100);
	npDir(45,EAST);
	evFrameWait(100);
	npDir(43,NORTH);
	npDir(46,EAST);
	evFrameWait(100);
	npDir(45,NORTH);
	npDir(46,NORTH);
	evFrameWait(100);
	npDir(47,WEST);
	evFrameWait(200);
	npDir(47,NORTH);
	evFrameWait(250);

	mes.ReadDraw();
	//---���̒��́E�E�E
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---�f�B�U�؂�C��
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(44,0,-1);
		else {
			npMove(43,1,0,0);
			npMove(44,1,0);
		}
		evFrame();
	}
	npDir(44,NORTH);
	evFrameWait(250);
	mes.ReadDraw(3);

	//---����
	evFrameWait(250);
	npDir(43,WEST);
	evFrameWait(250);
	npDir(43,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---���~���낤�Ƃ���
	npDir(48,EAST);
	evFrameWait(250);
	npDir(48,NORTH);
	evFrameWait(250);
	npMove(48,0,-1);
	evFrame();
	evFrameWait(100);
	mes.ReadDraw();
	//---�U��Ԃ�
	evFrameWait(500);
	npDir(48,WEST);
	evFrameWait(250);
	npDir(48,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---�T���B�A�[�q��
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(46,EAST);
	evFrameWait(50);
	npMove(46,1,0);
	evFrame();
	npDir(46,NORTH);
	evFrameWait(250);

	//---�����܂���
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw(2);
	//---�����猾���Ă邶��Ȃ�
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	mes.ReadDraw(3);
	//---�����������Ƃ͂��ꂾ���H
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(48,EAST);
	evFrameWait(250);
	npDir(48,NORTH);
	evFrameWait(650);
	npDir(48,WEST);
	evFrameWait(250);
	npDir(48,SOUTH);
	evFrameWait(250);
	npMove(48,0,1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---���~����
	evFrameWait(250);
	npDir(48,EAST);
	evFrameWait(250);
	npDir(48,NORTH);
	evFrameWait(250);
	for(a = 0;a < 7;a ++){
		npMove(48,0,-1);
		evFrame();
	}
	//---��������������
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(44,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	//---����
	evFrameWait(250);
	npDir(45,EAST);
	evFrameWait(250);
	npDir(43,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(46,EAST);
	evFrameWait(250);
	npDir(46,SOUTH);
	evFrameWait(250);

	evFrameWait(250);
	npDir(47,WEST);
	evFrameWait(250);
	npDir(47,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(44,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---�����ˁE�E�E
	evFrameWait(500);
	npDir(43,NORTH);
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	mes.CloseMessage();

	evSet(142,1);

	for(a = 43;a <= 48;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	mcShow(1);
	evScene(0,19,2);
	evReadObject(1,"Gazell.acf");
	mcDir(SOUTH);

	//---�V���f�B���ԂɂȂ�
	{
		pPartyInfo->PartyMember[3] = 3;
		pPartyInfo->PartyMember[4] = 6;

		int level = crcharaGetPartyMember(0)->GetLevel();
		CrCharacter *pChara = crcharaGetPartyMember(4);

		if(level > pChara->GetLevel() && level < 34){
			//---���i���̕������������烌�x���Z�b�g
			crcharaSetLevelStatus(4,level + 1);
			pChara->SetLevelExperience();
		} else if(level > pChara->GetLevel() && level >= 34){
			//---���x���R�S�ȏゾ������
			crcharaSetLevelStatus(4,34);
			pChara->SetLevelExperience();
		}

		pChara->SetWeapon(0,15);
		pChara->SetWeapon(1,0);
		pChara->SetProtector(0,97);
		pChara->SetProtector(1,145);
		pChara->SetProtector(2,260);
		pChara->SetBattleFieldStartPos(2,3);
		crcharaLoadFace(-1);
		crcharaCheckBattleFieldPos(4);
	}
	prtRecovery(4);

	return 1;
}

//---�c�[���A�A�K�[�[���Ƃ̍ĉ�
CREVENTLONG4_API int creventTuria_MeetGazell(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	evSet(143,1);

	evFrameWait(250);
	mes.OpenMessage("Turia.msg",101);
	mes.ReadDraw();

	//---�K�[�[���U��Ԃ�
	crmusicFadeOut();
	evFrameWait(250);
	npDir(48,WEST);
	evFrameWait(250);
	npDir(48,SOUTH);
	evFrameWait(250);

	mes.ReadDraw(2);
	evFrameWait(500);

	npPos(43,56,36);
	npDir(43,NORTH);
	npPos(44,55,37);
	npDir(44,NORTH);
	npPos(47,57,37);
	npDir(47,NORTH);
	npPos(48,56,35);
	npDir(48,SOUTH);
	mcShow(0);
	evScene(0,56,37);
	crmusicPlay(CRMUSIC_SEEK);
	evFrameWait(500);

	mes.ReadDraw();
	evFrameWait(500);
	//---���i����
	mes.ReadDraw();
	evFrameWait(250);
	npDir(43,WEST);
	evFrameWait(250);
	npDir(43,SOUTH);
	evFrameWait(1000);
	npDir(43,EAST);
	evFrameWait(250);
	npDir(43,NORTH);
	evFrameWait(500);
	//---�݂�Ȃ�
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	//---���݂̂�Ȃ́H
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(1000);
	//---�C�����͕����邪
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---������̕��́H
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(43,WEST);
	evFrameWait(250);
	npDir(43,SOUTH);
	evFrameWait(1000);
	npDir(43,EAST);
	evFrameWait(250);
	npDir(43,NORTH);
	evFrameWait(500);
	mes.ReadDraw(3);

	evFrameWait(500);
	mes.ReadDraw(3);

	//---�Ȃ����₶����
	evFrameWait(250);
	npMove(44,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);
	//---�Ȃ��Ă����Ȃ��Ƃ�
	evFrameWait(250);
	npDir(43,WEST);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---�����H
	evFrameWait(500);
	mes.ReadDraw(2);
	//---������́H
	evFrameWait(250);
	npDir(43,NORTH);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();
	//---���W
	evFrameWait(250);
	npDir(14,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(14,SOUTH);
	evFrameWait(250);

	mes.ReadDraw();

	//---�K�[�[������
	evFrameWait(250);
	npMove(43,0,1,0);
	evFrame();
	evFrameWait(250);
	for(a = 0;a < 4;a ++){
		if(a < 1)
			npMove(48,0,1);
		else
			npMove(48,1,0);

		if(a == 3)
			npMove(43,0,-1);
		if(a == 2)
			npDir(44,EAST);
		evFrame();
	}
	npDir(43,EAST);
	evFrameWait(100);

	//---������I�I
	mes.ReadDraw();
	evFrameWait(250);
	npDir(48,SOUTH);
	evFrameWait(150);
	npDir(47,EAST);
	evFrameWait(100);
	evFrameWait(250);
	npDir(48,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	//---�Z�m�E�ŁE�E�E
	evFrameWait(700);
	mes.ReadDraw();
	//---�Ȃɂ��H
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---�������낤��
	evFrameWait(1000);
	npMove(48,-1,0);
	evFrame();
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();
	//---�]�񂾂���
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(350);
	npDir(48,SOUTH);
	evFrameWait(350);
	npDir(48,EAST);
	evFrameWait(350);
	//---�K�[�[���s��
	crmusicFadeOut();
	for(a = 0;a < 10;a ++){
		if(a < 2)
			npMove(48,1,0);
		else if(a < 3)
			npMove(48,0,-1);
		else
			npMove(48,1,0);
		evFrame();
	}

	evFrameWait(1000);
	crmusicStop();
	mes.ReadDraw();
	//---�����
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.CloseMessage();

	npPos(48,0,0);
	npShow(48,0);

	//---����//11,22
	npPos(43,11,22);
	npDir(43,SOUTH);
	npPos(44,12,23);
	npDir(44,WEST);
	npPos(45,10,22);
	npDir(45,SOUTH);
	npPos(46,11,24);
	npDir(46,NORTH);
	npPos(47,10,24);
	npDir(47,NORTH);

	evScene(0,11,25);
	evReloadMapMusic();
	evFrameWait(500);
	mes.OpenMessage("Turia.msg",102);
	//---�ǂ��������H
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(44,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(5);

	//---���i���ǂ������́H
	evFrameWait(250);
	npDir(45,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	//---������Ƃ����Ă�
	evFrameWait(250);
	npDir(44,WEST);
	evFrameWait(250);
	npDir(44,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(44,WEST);
	evFrameWait(250);
	npDir(44,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(45,SOUTH);
	evFrameWait(250);

	//---�b�̑���
	evFrameWait(250);
	mes.ReadDraw(3);

	//---�s���́H
	evFrameWait(250);
	npDir(45,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(44,WEST);
	evFrameWait(250);
	npDir(44,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---����
	evFrameWait(700);
	mes.ReadDraw(3);
	//---�����Ȃ񂾂��ǂˁE�E�E
	evFrameWait(500);
	mes.ReadDraw(2);
	//---�Ȃ�ł��Ȃ�
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(44,WEST);
	evFrameWait(150);
	npDir(45,SOUTH);
	evFrameWait(100);
	npDir(44,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---�������
	for(a = 43;a <= 48;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	crfieldChangeScene(2,11,6);
	npPos(0,11,3);
	npDir(0,EAST);
	npPos(1,10,2);
	npDir(1,EAST);
	npPos(2,10,3);
	npDir(2,EAST);
	npPos(3,11,2);
	npDir(3,EAST);
	npPos(4,9,2);
	npDir(4,EAST);

	evScene(2,11,6);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---���������
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);
	//---�͂��ƋC�Â�
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---�̐S�Ȃ̂�
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---�V���f�B�����
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);

	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(500);

	for(a = 0;a <= 4;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	mes.CloseMessage();

	mcShow(1);
	mcDir(SOUTH);
	evScene(2,11,3);

	return 1;
}

//---�c�[���A�A�h�q�V�X�e��
CREVENTLONG4_API int creventTuria_BoueiSystem(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	npPos(1,ef->xGet(),ef->yGet());
	npDir(1,EAST);
	evFrameWait(250);

	npPos(6,53,24);
	npDir(6,NORTH);

	for(a = 0;a < 10;a ++){
		if(a < 8)
			mcMove(1,0);
		evFrame();
	}

	npPos(1,53,26);
	npDir(1,NORTH);
	npPos(2,52,26);
	npDir(2,NORTH);
	npPos(3,54,27);
	npDir(3,NORTH);
	npPos(4,53,28);
	npDir(4,NORTH);
	npPos(5,51,27);
	npDir(5,NORTH);

	evScene(2,53,28);
	evFrameWait(250);

	mes.OpenMessage("TuriaChika.msg",100);
	mes.ReadDraw();
	evFrameWait(500);
	crsoundPlay(CRSOUND_KIDOU);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);

	mes.CloseMessage();

	//---�o�g��
	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = CRMUSIC_BOSSBATTLE1;
	BattleInfo.Enemy[2].Enemy = 120;
	BattleInfo.Enemy[2].x = 6;
	BattleInfo.Enemy[2].y = 9;
	BattleInfo.Enemy[0].Enemy = 119;
	BattleInfo.Enemy[0].x = 2;
	BattleInfo.Enemy[0].y = 6;
	BattleInfo.Enemy[1].Enemy = 119;
	BattleInfo.Enemy[1].x = 10;
	BattleInfo.Enemy[1].y = 6;
	BattleInfo.Enemy[3].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
//	BattleInfo.MapNumber = 1;
	evField(0,1);

	npPos(1,52,26);
	npDir(1,NORTH);
	npPos(2,53,25);
	npDir(2,NORTH);
	npPos(3,54,26);
	npDir(3,NORTH);
	npPos(4,56,27);
	npDir(4,NORTH);
	npPos(5,51,29);
	npDir(5,NORTH);

	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}

	//---�|�����I
	evFrameWait(250);
	mes.OpenMessage("TuriaChika.msg",101);
	mes.ReadDraw(2);
	evFrameWait(250);

	//---�ǂ�����オ��
	int x,y;

	crsoundPlay(CRSOUND_ATACK4);
	for(x = 49,y = 22;x <= 57;x ++){
		em->Put(x,y,2,33);
		evFrameWait(20);
	}
	crsoundPlay(CRSOUND_ATACK4);
	for(x = 57,y = 23;y <= 28;y ++){
		em->Put(x,y,2,51);
		em->Put(x,y - 1,2,35);
		evFrameWait(20);
	}
	crsoundPlay(CRSOUND_ATACK4);
	for(x = 57,y = 28;x >= 49;x --){
		em->Put(x,y,2,33);
		evFrameWait(20);
	}
	crsoundPlay(CRSOUND_ATACK4);
	for(x = 49,y = 27;y >= 22;y --){
		em->Put(x,y,2,35);
		evFrameWait(20);
	}

	//---�ȁA�ȂɁI�H
	npDir(4,EAST);
	evFrameWait(100);
	npDir(1,WEST);
	evFrameWait(100);
	mes.ReadDraw();

	//---��ȁI�H
	evFrameWait(100);
	npDir(3,EAST);
	evFrameWait(100);
	npDir(2,WEST);
	evFrameWait(100);
	npDir(3,SOUTH);
	evFrameWait(200);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(2,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---�ǂ��ɂ��Ȃ�Ȃ�
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(5,EAST);
	evFrameWait(500);
	npDir(4,SOUTH);
	for(a = 0;a < 2;a ++){
		npMove(5,1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(5,NORTH);
	evFrameWait(1000);
	//---���߂�Ȃ���
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---�ł�������
	npPos(7,53,38);
	npDir(7,NORTH);
	evFrameWait(1000);
	crmusicPlay(CRMUSIC_ETERNAL);
	mes.ReadDraw();

	evFrameWait(250);
	for(a = 0;a < 11;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();

	//---�J�����߂��ăV���f�B�ق�
	evFrameWait(500);
	npDir(5,EAST);
	evFrameWait(500);
	npDir(5,SOUTH);
	for(a = 0;a < 9;a ++){
		mcMove(0,-1);
		evFrame();
	}
	for(a = 0;a < 7;a ++){
		npMove(7,0,-1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	//---�f�B�U���{��
	for(a = 0;a < 2;a ++){
		npMove(2,0,1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();

	//---�V���f�B��
	evFrameWait(500);
	mes.ReadDraw(2);
	//---�P��
	evFrameWait(500);
	mes.ReadDraw();

	//---����ŕ������
	evFrameWait(1000);
	npMove(5,0,1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);

	//---�N�Y
	evFrameWait(250);
	npMove(1,0,1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(3);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---�N���C�V���l��
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(7,WEST);
	evFrameWait(500);
	npDir(7,SOUTH);
	evFrameWait(500);
	//---�s����
	mes.ReadDraw();
	evFrameWait(1000);

	for(a = 0;a < 3;a ++){
		mcMove(0,1);
		evFrame();
	}
	for(a = 0;a < 2;a ++){
		npMove(7,0,1);
		evFrame();
	}
	for(a = 0;a < 1;a ++){
		npMove(5,0,1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	for(a = 0;a < 20;a ++){
		npMove(7,0,1);
		if(a < 6){
		} else
			npMove(5,0,1);
		evFrame();
		if(a == 10)
			evFrameWait(1000);
	}
	evFrameWait(500);

	//---�Ö��K�X
	crsoundPlay(CRSOUND_WIND1);
	evFadeOut(200,RGB_MAKE(255,255,255));
	evFieldNoFlip(0,1);
	evFadeIn(200,RGB_MAKE(255,255,255));

	evFrameWait(750);
	npDir(2,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---�C������

	mes.CloseMessage();

	//---�V���f�B�͂����
	{
		CrCharacter *pChara = crcharaGetPartyMember(4);
		if(pChara != NULL){
			//---���������łȂ���ΊO��
			if(pChara->GetWeapon(0) != 15){
				critemAddItem(pChara->GetWeapon(0),1);
				pChara->SetWeapon(0,0);
			}
			if(pChara->GetWeapon(1) != 15){
				critemAddItem(pChara->GetWeapon(1),1);
				pChara->SetWeapon(1,0);
			}

			if(pChara->GetProtector(0) != 97){
				critemAddItem(pChara->GetProtector(0),1);
				pChara->SetProtector(0,0);
			}
			if(pChara->GetProtector(1) != 145){
				critemAddItem(pChara->GetProtector(1),1);
				pChara->SetProtector(1,0);
			}
			if(pChara->GetProtector(2) != 260){
				critemAddItem(pChara->GetProtector(2),1);
				pChara->SetProtector(2,0);
			}

			if(pChara->GetAccessory(0) != 0){
				critemAddItem(pChara->GetAccessory(0),1);
				pChara->SetAccessory(0,0);
			}
			if(pChara->GetAccessory(1) != 0){
				critemAddItem(pChara->GetAccessory(1),1);
				pChara->SetAccessory(1,0);
			}
		}
		pPartyInfo->PartyMember[4] = -1;
		crcharaLoadFace(-1);
	}

	evSet(149,1);

	crmusicFadeOut();
	evFadeOut(2000);
	crfieldChangeMap(64,4,1,0);
	crfieldChangeScene(4,15,15);
	et->Delay2(1000);
	crmusicStop();

	//---�Èł̒�
	evFieldNoFlip(0,1);
	evFadeIn();

	evFrameWait(1000);

	mes.OpenMessage("TuriaEternal.msg",100);
	for(a = 0;a < 3;a ++){
		mes.ReadDraw();
		evFrameWait(1000);
	}
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(2000);

	//---�ڂ��o�߂�
	crfieldChangeScene(0,6,13);
	em->Put(6,8,2,97);

	npPos(0,8,10);
	npDir(0,NORTH);
	npPos(1,6,10);
	npDir(1,SOUTH);
	npPos(2,3,11);
	npDir(2,NORTH);
	npPos(3,5,12);
	npDir(3,EAST);

	evReadObject(12,"LunarnSlp3.acf");

	evFieldNoFlip(0,1);
	crfieldChangeScene(0,6,13);
	evFadeIn(2000);

	//---���i�����ڂ��o�܂�
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(0,EAST);
	evFrameWait(1000);
//	mes.ReadDraw();

	//---�ڊo�߂���
	evFrameWait(500);
	npDir(1,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	evReadObject(12,"Lunarn.acf");
	npDir(0,SOUTH);
	evFrameWait(1000);
	npDir(0,WEST);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---��������
	evFrameWait(500);
	npDir(2,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(2);

	//---�������΂����̂��H
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);

	npPos(0,0,0);
	npShow(0,0);
	mcShow(1);
	evScene(0,8,10);

	evSet(EV_MENU_MODE,1);
	crmusicPlay(CRMUSIC_SILENT,1,CRMUSIC_LOADFORCE);

	mes.CloseMessage();

	return 1;
}

//19,6
//---�c�[���A�����A�t�H�[��������
CREVENTLONG4_API int creventTuriaEternal_Follne(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	npPos(4,19,6);
	npDir(4,WEST);

	for(a = 0;a < 13;a ++){
		npMove(4,-1,0);
		if(a == 10)
			npDir(1,EAST);
		if(a == 11)
			npDir(1,NORTH);
		if(a == 12)
			npDir(2,NORTH);
		evFrame();
	}
	evFrameWait(250);
	npDir(4,SOUTH);
	evFrameWait(250);

	mcShow(0);
	npPos(0,7,11);
	npDir(0,NORTH);
	evScene(0,7,12);
	crmusicPlay(CRMUSIC_ETERNAL,1,CRMUSIC_LOADFORCE);
	evFrameWait(500);

	mes.OpenMessage("TuriaEternal.msg",101);
	mes.ReadDraw();

	//---�ڊo�߂́H
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw(2);

	//---�N���X�e�B�[����
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw(2);

	//---�����Ă��O���
	evFrameWait(500);
	mes.ReadDraw(2);

	//---�Ƃ肢���������
	evFrameWait(500);
	mes.ReadDraw();
	npPos(5,6,6);
	npDir(5,NORTH);

	//---�܂����E�E�E
	evFrameWait(1000);
	mes.ReadDraw(3);
	//---�b��������
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw(3);

	//---���������
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---���_��
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	//---�N���X�t�B�[���h���n

	//---
	crfieldChangeMap(30,3,1,0);
	crfieldChangeScene(3,10,15);

	npPos(3,8,15);
	npDir(3,EAST);

	npPos(7,12,6);
	npDir(7,SOUTH);
	npPos(8,13,15);
	npDir(8,NORTH);
	npPos(9,10,13);
	npDir(9,NORTH);
	npPos(10,11,16);
	npDir(10,NORTH);


	npPos(8,12,18);
	npPos(9,10,19);
	npPos(10,15,20);

	npPos(3,12,14);
	npDir(3,NORTH);
	npPos(4,13,15);
	npDir(4,NORTH);
	npPos(5,10,15);
	npDir(5,NORTH);
	npPos(6,12,16);
	npDir(6,NORTH);

	npPos(7,12,12);
	npDir(7,NORTH);
	crfieldPaletteChange(PALETTE_MONO);

	evScene(3,12,15);

	evFrameWait(1000);
	npDir(3,WEST);
	evFrameWait(300);
	npDir(3,SOUTH);
	evFrameWait(300);

	evFrameWait(250);
	//---�K�C�R�c����
	npMove(7,0,1);
	evFrame();
	evFrameWait(250);

	evFill(ep->MakeRGB(0,0,0));
//	crsoundPlay(CRSOUND_ATACK1);
	ew->Flip();
	npPos(7,0,0);
	npShow(7,0);
//	et->Delay2(50);
	evWait(50,1);
	evFieldNoFlip(0,1);
	evFadeIn(250);
	evFrameWait(1500);

	//---�ӂ�����
	crfieldChangeMap(64,0,1,0);
	
	npPos(0,7,11);
	npDir(0,NORTH);
	npPos(1,6,10);
	npDir(1,NORTH);
	npPos(2,3,11);
	npDir(2,NORTH);
	npPos(3,5,12);
	npDir(3,NORTH);

	npPos(4,6,6);
	npDir(4,SOUTH);
	npPos(5,6,6);
	npDir(5,NORTH);
	evScene(0,7,12);

	//---�����ł���
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(250);
	npMove(1,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(4);

	//---������
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---���ʂȂ�āE�E�E
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---���i������
	evFrameWait(500);
	npDir(0,WEST);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(0,-1,0);
		else
			npMove(0,0,-1);
		evFrame();
	}
	evFrameWait(250);
	//---���i���I�I
	mes.ReadDraw(3);
	evFrameWait(500);
	mes.ReadDraw();

	//---���o���Ă�Ȃ�
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);
	npPos(5,0,0);
	npShow(5,0);
	evFrameWait(250);
	npDir(4,EAST);
	evFrameWait(250);
	//---�t�H�[��������
	crmusicFadeOut();
	for(a = 0;a < 14;a ++){
		npMove(4,1,0);
		evFrame();
	}
	crmusicPlay(CRMUSIC_SILENT);

	//---���̂Ƃ��̂��ォ�����񂾂�
	mes.ReadDraw();
	evFrameWait(250);
	for(a = 0;a < 1;a ++){
		npMove(2,0,-1);
		evFrame();
	}
	evFrameWait(250);
	npDir(2,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(3);
	evFrameWait(500);
	mes.ReadDraw();

	//---���̂킽���Ȃ�
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1500);
	mes.ReadDraw();

	//---�����@
	evFrameWait(1000);
	crsoundPlay(CRSOUND_MUSEN);
	evFrameWait(100);
	crsoundStop(CRSOUND_MUSEN);

	evFrameWait(200);
	crsoundPlay(CRSOUND_MUSEN);
	evFrameWait(1000);

	mes.ReadDraw();
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(150);
	npDir(2,NORTH);
	evFrameWait(100);
	npDir(1,NORTH);

	em->Put(7,3,2,100);
	evFrameWait(250);
	crsoundPlay(CRSOUND_MUSEN);
	for(a = 0;a < 5;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(1000);
	crsoundPlay(CRSOUND_MUSEN);
	evFrameWait(100);
	crsoundStop(CRSOUND_MUSEN);
	evFrameWait(200);
	crsoundPlay(CRSOUND_MUSEN);
	mes.ReadDraw(2);
	evFrameWait(250);

	//---����Ő搶��
	for(a = 0;a < 5;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(250);
	npMove(3,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	//---���i���E�E�E
	evFrameWait(500);
	npDir(2,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---�킽��
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npMove(2,1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(300);
	npDir(0,WEST);
	evFrameWait(300);
	npDir(0,SOUTH);
	evFrameWait(1000);
	npDir(0,WEST);
	evFrameWait(1000);
	npDir(0,NORTH);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---�����ǂȂ�
	evFrameWait(500);
	npDir(1,WEST);
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(250);

	//---���̑O��
	for(a = 0;a < 2;a ++){
		npMove(3,0,-1);
		evFrame();
	}
	npDir(1,WEST);
	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	for(a = 0;a < 1;a ++){
		npMove(1,1,0,0);
		evFrame();
	}
	evFrameWait(500);
	for(a = 0;a < 1;a ++){
		npMove(3,1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(250);
	//---�i�b�N�ړ�
	npDir(2,NORTH);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(2,0,-1);
		else
			npMove(2,1,0);
		evFrame();
	}
	evFrameWait(500);

	//---�ዾ���O����
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	//---����
	evFrameWait(1000);
	em->Put(6,8,2,1024);
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	mes.ReadDraw(3);
	evFrameWait(500);

	evSet(155,1);
	evSet(EV_MENU_MODE,0);

	for(a = 0;a <= 5;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}

	em->Put(7,3,2,1024);
	mcShow(1);
	mcDir(SOUTH);
	prtRecoveryAll();
	evScene(0,7,4);

	return 1;
}

//---�c�[���A�����A�E�o�I
CREVENTLONG4_API int creventTuriaEternal_Dasshutu(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	npPos(5,6,33);
	npDir(5,NORTH);
	npPos(6,5,33);
	npDir(6,NORTH);
	npPos(7,6,34);
	npDir(7,NORTH);
	npPos(8,5,34);
	npDir(8,NORTH);

	evScene(1,9,29);
	evFrameWait(250);

//	crmusicPlay(CRMUSIC_SILENT);
	crmusicPlay(CRMUSIC_ETERNAL);
	npDir(2,WEST);
	evFrameWait(250);
//	6,33
	for(a = 0;a < 8;a ++){
		if(a < 7)
			npMove(5,0,-1);
		if(a)
			npMove(6,0,-1);
		if(a > 1)
			npMove(7,0,-1);
		if(a)
			npMove(8,0,-1);
		if(a == 3)
			npDir(3,WEST);
		evFrame();
	}
	npDir(5,EAST);
	evFrameWait(100);
	npDir(6,EAST);
	evFrameWait(100);
	npDir(7,EAST);
	evFrameWait(100);
	npDir(8,EAST);
	evFrameWait(100);

	mes.OpenMessage("TuriaEternal.msg",103);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(4,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---���ƂȂ���
	evFrameWait(250);
	npMove(4,0,1);
	evFrame();
	evFrameWait(250);
	npDir(4,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npMove(5,1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---��]��
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(6,NORTH);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(6,0,-1);
		else
			npMove(6,1,0);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();

	//---����ȉ^���I�I
	//---�󂵂Ă��
	crmusicFadeOut();
	evFrameWait(250);
	mes.ReadDraw();
	evField(0,1);
	crmusicPlay(CRMUSIC_BREAKFORTUNE);
	evFrameWait(100);
	for(a = 0;a < 2;a ++){
		npMove(5,1,0);
		npMove(6,1,0);
		npMove(7,1,0);
		npMove(8,1,0);
		evFrame();
	}
	mes.CloseMessage();
	evField(0,1);

	//-------------------
	//---�o�g��
	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = 0;
	BattleInfo.Enemy[0].Enemy = 121;
	BattleInfo.Enemy[0].x = 3;
	BattleInfo.Enemy[0].y = 6;
	BattleInfo.Enemy[1].Enemy = 123;
	BattleInfo.Enemy[1].x = 9;
	BattleInfo.Enemy[1].y = 7;
	BattleInfo.Enemy[2].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
//	BattleInfo.MapNumber = 1;
	evField(0,1);

	npPos(2,0,0);
	npPos(3,0,0);
	npPos(4,0,0);

	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}

	npPos(5,11,26);
	npDir(5,SOUTH);
	npPos(6, 8,26);
	npDir(6,EAST);
	npPos(7, 7,27);
	npDir(7,EAST);
	npPos(8,12,28);
	npDir(8,NORTH);

	evFrameWait(250);
	npDir(5,EAST);
	evFrameWait(250);

	mes.OpenMessage("TuriaEternal.msg",104);
	//---�t�H�[�����́H
	mes.ReadDraw(2);

	//---����������
	evFrameWait(250);
	npMove(6,1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---��񂾂����j���[���J����
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	crmainMainMenu(1);
	evFrameWait(500);

	//---�ꏊ�ړ�
	for(a = 0;a < 17;a ++){
		mcMove(1,0);
		evFrame();
	}
	evScene(1,26,12);
/*	for(a = 0;a < 17;a ++){
		mcMove(0,-1);
		evFrame();
	}*/

	npPos(5,26,18);
	npPos(6,25,18);
	npPos(7,25,19);
	npPos(8,26,20);

	npPos(2,37,10);
	npPos(9,38,11);
	npPos(3,39,10);

	for(a = 0;a < 8;a ++){
		npMove(5,0,-1);
		npMove(6,0,-1);
		npMove(7,0,-1);
		npMove(8,0,-1);

		if(a){
			npMove(2,-1,0);
			npMove(3,-1,0);
			npMove(9,-1,0);
		}
		evFrame();
	}
	npDir(5,EAST);
	evFrameWait(80);
	npDir(6,EAST);
	evFrameWait(80);
	npDir(7,EAST);
	evFrameWait(80);
	npDir(8,EAST);
	evFrameWait(250);

	mes.ReadDraw(3);
	mes.CloseMessage();
	evFrameWait(250);

	//-------------------
	//---�o�g��
	memset(&BattleInfo,0,sizeof(BattleInfo));

	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = 0;
	BattleInfo.Enemy[0].Enemy = 122;
	BattleInfo.Enemy[0].x = 4;
	BattleInfo.Enemy[0].y = 9;
	BattleInfo.Enemy[1].Enemy = 121;
	BattleInfo.Enemy[1].x = 6;
	BattleInfo.Enemy[1].y = 6;
	BattleInfo.Enemy[2].Enemy = 123;
	BattleInfo.Enemy[2].x = 8;
	BattleInfo.Enemy[2].y = 9;
	BattleInfo.Enemy[3].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
//	BattleInfo.MapNumber = 1;
	evField(0,1);

	npPos(2,0,0);
	npPos(3,0,0);
	npPos(9,0,0);

	npPos(5,30,9);
	npDir(5,EAST);
	npPos(6,28,8);
	npDir(6,SOUTH);
	npPos(7,26,10);
	npDir(7,EAST);
	npPos(8,25,11);
	npDir(8,NORTH);

	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}

	//---�s��
	evFrameWait(250);
	npDir(5,SOUTH);
	for(a = 0;a < 16;a ++){
		if(a < 1)
			npMove(5,0,1);
		else
			npMove(5,1,0);
		if(a < 3)
			npMove(6,0,1);
		else
			npMove(6,1,0);

		if(a < 1){
		} else
			npMove(7,1,0);
		if(a < 2){
		} else
			npMove(8,1,0);

		evFrame();

	}
	evFrameWait(250);

	//---�P�e
	evScene(2,35,22);
	npPos(9,46,20);
	npDir(9,WEST);
	npPos(10,47,20);
	npDir(10,WEST);
	npPos(11,49,21);
	npDir(11,WEST);
	npPos(12,49,20);
	npDir(12,WEST);

	npPos(13,17,20);
	npDir(13,EAST);
	npPos(14,16,21);
	npDir(14,EAST);

	for(a = 0;a < 11;a ++){
		npMove(9,-1,0);
		npMove(10,-1,0);
		npMove(11,-1,0);
		npMove(12,-1,0);

		npMove(13,1,0);
		npMove(14,1,0);

		evFrame();
	}

	//---�������I�I
	evFrameWait(100);
	mes.OpenMessage("TuriaEternal.msg",105);
	mes.ReadDraw(2);

	evFrameWait(100);
	for(a = 0;a < 13;a ++){
		if(a < 8){
			npMove(13,1,0);
			npMove(14,1,0);
		} else {
			npDir(13,SOUTH);
			npDir(14,SOUTH);
		}

		if(a < 12){
			npMove(9,0,1);
			npMove(10,0,1);
		}

		if(a < 2)
			npMove(11,-1,0);
		else if(a < 12)
			npMove(11,0,1);
		if(a < 3)
			npMove(12,-1,0);
		else
			npMove(12,0,1);
		evFrame();
	}
	npPos(15,36,35);
	npDir(15,NORTH);
	npPos(16,35,35);
	npDir(16,NORTH);

	//---�J�����ړ�
	for(a = 0;a < 12;a ++){
		mcMove(0,1);
		evFrame();
	}
	npPos(13,35,27);
	npPos(14,36,27);

	//---�I
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(150);
	npDir(12,EAST);
	evFrameWait(150);
	npDir(12,NORTH);
	evFrameWait(150);
	for(a = 0;a < 1;a ++){
		npMove(13,0,1);
		npMove(14,0,1);
		evFrame();
	}

	//---���݌����I�H
	evFrameWait(250);
	mes.ReadDraw(2);
	mes.CloseMessage();
	evFrameWait(250);

	npMove(13,0,1);
	npMove(10,0,1);
	evFrame();
	npMove(15,0,-1);
	evFrame();
	evField(0,1);
	evField(0,1);

	//---���݌����o�g���I
	//---�o�g��
	memset(&BattleInfo,0,sizeof(BattleInfo));

	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = 0;
	BattleInfo.Enemy[0].Enemy = 122;//---��
	BattleInfo.Enemy[0].x = 3;
	BattleInfo.Enemy[0].y = 10;
	BattleInfo.Enemy[1].Enemy = 124;
	BattleInfo.Enemy[1].x = 8;
	BattleInfo.Enemy[1].y = 10;
	BattleInfo.Enemy[2].Enemy = 121;
	BattleInfo.Enemy[2].x = 3;
	BattleInfo.Enemy[2].y = 2;
	BattleInfo.Enemy[3].Enemy = 123;
	BattleInfo.Enemy[3].x = 9;
	BattleInfo.Enemy[3].y = 3;
	BattleInfo.Enemy[4].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	//---���݌����I
	BattleInfo.Friend[0].x = 4;
	BattleInfo.Friend[0].y = 5;
	BattleInfo.Friend[1].x = 7;
	BattleInfo.Friend[1].y = 5;
	BattleInfo.Friend[2].x = 6;
	BattleInfo.Friend[2].y = 7;
	BattleInfo.Friend[3].x = 4;
	BattleInfo.Friend[3].y = 7;
	BattleInfo.EnableFriendPos = 1;
	BattleInfo.OffsetBattle = 0;//OFFSETBAT_HASAMIUCHI;
	evField(0,1);

	for(a = 13;a <= 16;a ++){
		npPos(a,0,0);
	}

	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}

	//---�Q�e
	crfieldChangeScene(3,40,28);

/*	npPos(5,41,25);
	npDir(5,WEST);
	npPos(6,40,25);
	npDir(6,EAST);
	npPos(7,38,26);
	npDir(7,NORTH);*/

	evScene(3,40,28);
	npPos(1,40,36);
	npDir(1,NORTH);
	npPos(2,39,35);
	npDir(2,NORTH);
	npPos(3,39,36);
	npDir(3,NORTH);
	npPos(4,40,37);
	npDir(4,NORTH);
	for(a = 0;a < 7;a ++){
		npMove(1,0,-1);
		npMove(2,0,-1);
		npMove(3,0,-1);
		npMove(4,0,-1);

		if(a == 1)
			npDir(7,EAST);
		if(a == 2)
			npDir(7,SOUTH);
		if(a == 3)
			npDir(5,SOUTH);
		if(a == 4)
			npDir(6,SOUTH);

		evFrame();
	}
//-------------------------------------------
	for(a = 0;a < 7;a ++){
		if(a < 2)
			npMove(1,0,-1);
		else if(a < 5)
			npMove(1,-1,0);
		else
			npDir(1,NORTH);

		if(a < 1)
			npMove(2,-1,0);
		else
			npDir(2,NORTH);

		if(a < 1)
			npDir(3,EAST);
		else if(a < 3)
			npMove(3,1,0);
		else if(a < 7)
			npMove(3,0,-1);

		if(a < 2){
		} else if(a < 3)
			npDir(4,EAST);
		else if(a < 4)
			npMove(4,1,0);
		else if(a < 7)
			npMove(4,0,-1);
		else
			npDir(4,NORTH);

		evFrame();
	}
	evFrameWait(250);
//-------------------------------------------


/*	//---����Ȃ��I
	evFrameWait(250);
	mes.OpenMessage("TuriaEternal.msg",106);
	mes.ReadDraw();
	mes.CloseMessage();

	evFrameWait(250);
	//---���@�A�m���A����
	//---�o�g��
	memset(&BattleInfo,0,sizeof(BattleInfo));

	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = 0;
	BattleInfo.Enemy[0].Enemy = 122;
	BattleInfo.Enemy[0].x = 3;
	BattleInfo.Enemy[0].y = 8;
	BattleInfo.Enemy[1].Enemy = 124;
	BattleInfo.Enemy[1].x = 6;
	BattleInfo.Enemy[1].y = 6;
	BattleInfo.Enemy[2].Enemy = 123;
	BattleInfo.Enemy[2].x = 7;
	BattleInfo.Enemy[2].y = 9;
	BattleInfo.Enemy[3].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	evField(0,1);

	npPos(5,0,0);
	npPos(6,0,0);
	npPos(7,0,0);*/

	npPos(1,37,27);
	npDir(1,NORTH);
	npPos(2,38,28);
	npDir(2,NORTH);
	npPos(3,41,25);
	npDir(3,WEST);
	npPos(4,41,27);
	npDir(4,NORTH);

/*	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}
*/
	evFrameWait(500);

	//---�������́H
	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(250);
	mes.OpenMessage("TuriaEternal.msg",107);
	mes.ReadDraw();
	evFrameWait(250);

	//---��
	int x,y;
	crsoundPlay(CRSOUND_ATACK4);
	for(x = 44,y = 28;x >= 39;x --){
		em->Put(x,y,2,65);
		evFrameWait(20);
	}
	crsoundPlay(CRSOUND_ATACK4);
	for(x = 39,y = 27;y >= 22;y --){
		em->Put(x,y,2,67);
		evFrameWait(20);
	}
	evFrameWait(100);
	npDir(1,NORTH);
	npDir(2,EAST);
	evFrameWait(150);
	npDir(1,EAST);
	evFrameWait(150);
	mes.ReadDraw();

	//---�������֖����ł���
	evFrameWait(250);
	npDir(4,WEST);
	evFrameWait(250);
	npDir(3,SOUTH);
	npMove(4,-1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	mes.ReadDraw();

	//---�C������
	evFrameWait(250);
	npMove(3,0,1);
	evFrame();
	evFrameWait(100);
	npDir(3,WEST);
	evFrameWait(250);
	mes.ReadDraw(4);

	//---�������I
	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	//---�́A�͂�
	evFrameWait(250);
	npDir(4,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(4,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---��l�s��
	evFrameWait(250);
	npDir(4,NORTH);
	evFrameWait(250);
	for(a = 0;a < 10;a ++){
		npMove(3,0,-1);
		if(a)
			npMove(4,0,-1);
		evFrame();
	}
	npDir(2,NORTH);
	evFrameWait(150);
	npDir(2,WEST);
	evFrameWait(150);
	npDir(1,SOUTH);
	evFrameWait(150);
	npDir(1,WEST);
	evFrameWait(250);

	//---���i���ƃi�b�N������
	for(a = 0;a < 8;a ++){
		npMove(1,-1,0);
		if(a)
			npMove(2,-1,0);
		evFrame();
	}

	evFrameWait(250);

	//---���i���ƃf�B�U
	evScene(3,22,13);
	npPos(1,22,23);
	npPos(2,21,24);

	npPos(5,35,11);
	npPos(7,33,12);
	npPos(8,32,11);
	for(a = 0;a < 12;a ++){
		npMove(1,0,-1);
		npMove(2,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);

	//---�������I
	for(a = 0;a < 2;a ++){
		npMove(5,-1,0);
		npMove(7,-1,0);
		npMove(8,-1,0);
		evFrame();
	}
	npDir(2,EAST);
	evFrameWait(50);
	npDir(1,EAST);
	evFrameWait(100);
	mes.ReadDraw(2);

	evFrameWait(100);
	npDir(2,NORTH);
	evFrameWait(50);
	npDir(1,NORTH);
	evFrameWait(50);


	//---������
	for(a = 0;a < 9;a ++){
		npMove(1,0,-1);
		npMove(2,0,-1);

		npMove(5,-1,0);
		npMove(7,-1,0);
		npMove(8,-1,0);
		evFrame();
	}

	for(a = 0;a < 9;a ++){
		if(a < 2)
			npMove(5,-1,0);
		else
			npMove(5,0,-1);
		npMove(7,0,-1);
		npMove(8,0,-1);
		evFrame();
	}

	evScene(3,7,29);
	npPos(1,6,18);
	npDir(1,SOUTH);
	npPos(2,5,17);
	npDir(2,SOUTH);

	npPos(5,5,6);
	npDir(5,SOUTH);
	npPos(7,6,7);
	npDir(7,SOUTH);
	npPos(8,5,8);
	npDir(8,SOUTH);

	for(a = 0;a < 29;a ++){
		if(a < 12)
			npMove(1,0,1);
		else
			npShow(1,0);
		if(a < 13)
			npMove(2,0,1);
		else
			npShow(2,0);


		if(a < 24)
			npMove(5,0,1);
		else
			npShow(5,0);
		if(a < 23)
			npMove(7,0,1);
		else
			npShow(7,0);
		if(a < 22)
			npMove(8,0,1);
		else
			npShow(8,0);
		evFrame();
	}
	evFrameWait(500);

	//---�O��
	crfieldChangeMap(61,0,1,0);
	npPos(43,7,61);
	npPos(44,7,61);
	evReadObject(14,"LunarnSwim.acf");
	evReadObject(1,"Yumi.acf");

	crfieldPaletteChange(PALETTE_NIGHT);
	evScene(0,7,64);
	evFrameWait(500);
	npShow(43,1);
	for(a = 0;a < 2;a ++){
		npMove(43,0,1);
		if(a == 1){
			npShow(44,1);
		}
		if(a == 2)
			npMove(44,0,1);
		evFrame();
	}
	//---���I
	evFrameWait(100);
	mes.ReadDraw();

	evFrameWait(250);
	for(a = 0;a < 3;a ++){
		if(a < 1)
			npMove(43,0,1);
		else if(a < 2)
			npMove(43,1,0);
		else
			npDir(43,SOUTH);
		npMove(44,0,1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();

	//---�G�^�[�i��������
	evFrameWait(250);
	npDir(44,WEST);
	evFrameWait(150);
	npDir(44,NORTH);
	evFrameWait(50);
	npDir(43,WEST);
	evFrameWait(150);
	npDir(43,NORTH);
	evFrameWait(150);

	npPos(54,7,61);
	npPos(55,7,61);
	npPos(56,7,61);
	npShow(54,1);
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(54,0,1);
		else
			npMove(54,1,0);
		if(a == 1)
			npShow(55,1);
		evFrame();
	}
	npDir(54,SOUTH);
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(55,0,1);
		else
			npMove(55,-1,0);
		if(a == 1)
			npShow(56,1);
		evFrame();
	}
	npDir(55,SOUTH);
	npMove(56,0,1);
	evFrame();
	evFrameWait(500);
	//---���傱�܂���
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();
	//---��΂�
	evFrameWait(1000);
	mes.ReadDraw();
	//---��������
	evFrameWait(250);
	npDir(43,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(44,0,-1);
		else
			npMove(44,1,0);
		evFrame();
	}
	npDir(43,NORTH);
	evFrameWait(150);
	npDir(44,SOUTH);
	evFrameWait(150);

	//---���i���𗎂Ƃ�
	crsoundPlay(CRSOUND_ATACK4);
	eiMapObject *np = npGet(43);
	np->Data.MoveSpeed = 4;
	for(a = 0;a < 5;a ++){
		npMove(43,0,1,0);
		if(a == 1)
			npDir(44,WEST);
		if(a == 2)
			npDir(44,NORTH);
		evFrame();
	}
	evField(0,1);
	evScene(4,16,16);

//	evFrameWait(250);

	mes.CloseMessage();

	return creventTuriaEternal_Dasshutu2();
}

//---�c�[���A�����A���~�Ɣ���
CREVENTLONG4_API int creventTuriaEternal_Dasshutu2(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	evFrameWait(250);

	mes.OpenMessage("TuriaEternal.msg",108);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---�炪�o��
	crfieldChangeScene(0,37,44);
//	evReloadMap(0);

	for(a = 0;a <= 70;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
//	crfieldPaletteChange(PALETTE_NIGHT);

	npPos(45,37,44);
	npDir(45,WEST);
	evScene(0,37,45);
	//---��������
	evFrameWait(250);
	npDir(45,SOUTH);
	evFrameWait(100);
	npDir(45,WEST);
	evFrameWait(250);
	npDir(45,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(45,EAST);
	evFrameWait(500);
	npDir(45,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---�オ�낤�Ƃ���
	evFrameWait(500);
	npDir(45,EAST);
	evFrameWait(500);
	npDir(45,NORTH);
	evFrameWait(250);
	eiMapObject *np = npGet(45);
	np->Data.MoveSpeed = 1;
	for(a = 0;a < 4;a ++){
		if(a < 2)
			npMove(45,0,-1);
		else
			npMove(45,1,0);
		evFrame();
		if(a == 1)
			evFrameWait(250);
	}
	evFrameWait(500);

	//---�オ��
	npPos(45,0,0);
	npPos(43,40,42);
	npDir(43,EAST);
	evScene(0,40,45);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(43,NORTH);

	//---�����I
	np = npGet(43);
	np->Data.MoveSpeed = 2;
	for(a = 0;a < 2;a ++){
		npMove(43,0,-1);
		evFrame();
	}
	evFrameWait(100);
	crsoundPlay(CRSOUND_FIRE2);
	evFadeOut(150,RGB_MAKE(255,0,0));
	evFieldNoFlip(0,1);
	evFadeIn(150,RGB_MAKE(255,0,0));
	crsoundPlay(CRSOUND_FIRE3);
	evFrameWait(500);
	mes.ReadDraw();
	for(a = 0;a < 1;a ++){
		npMove(43,0,-1);
		evFrame();
	}

	//---���~������
	evFrameWait(250);
	npPos(48,39,37);
	npDir(48,EAST);
	for(a = 0;a < 3;a ++){
		mcMove(0,-1);
		evFrame();
	}
	npMove(48,1,0);
	evFrame();
	npDir(48,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---�݂�Ȃ́I�H
	evFrameWait(250);
	npDir(48,EAST);
	evFrameWait(150);
	for(a = 0;a < 1;a ++){
		npMove(48,1,0);
		evFrame();
	}
	evFrameWait(50);
	npDir(48,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---���U�������Ă��
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(48,0,1);
		evFrame();
	}
	npDir(43,EAST);
	evFrameWait(250);
	npDir(48,WEST);
	evFrameWait(250);
	mes.ReadDraw(3);
	crmusicFadeOut();
	evFrameWait(500);

	//---�O���E���h�V�b�v
	evFadeOut(2000);
	crfieldChangeMap(59,0,1,0);
	crfieldChangeScene(0,21,9);
	npPos(0,22,6);
	npDir(0,WEST);
	npPos(4,20,6);
	npDir(4,EAST);
	crfieldPaletteChange(PALETTE_NIGHT);
	evFieldNoFlip(0,1);
	crmusicStop();
	evFadeIn(2000);

	evFrameWait(1000);
	mes.ReadDraw(2);
	//---���C��
	evFrameWait(500);
	mes.ReadDraw(2);

	//---������
	evFrameWait(500);
	mes.ReadDraw(3);

	//---����������
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(4,NORTH);
	evFrameWait(250);
	npMove(4,0,-1);
	evFrame();
	evFrameWait(1000);
	npDir(4,EAST);
	evFrameWait(250);
	npDir(4,SOUTH);
	evFrameWait(250);

	//---���߂΁H
	npMove(4,0,1);
	evFrame();
	evFrameWait(250);
	npDir(4,EAST);
	evFrameWait(250);
	em->Put(21,6,2,13);
	evFrameWait(250);
	mes.ReadDraw();

	//---�퓅��i
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();

	//---���炤
	evFrameWait(700);
	em->Put(21,6,2,1024);
	evFrameWait(2000);
	em->Put(21,6,2,13);
	evFrameWait(500);
	//---�g�}�g�����
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(2);

	//---�����̒��܂ł�
	npDir(4,SOUTH);
	evFrameWait(250);
	for(a = 0;a < 5;a ++){
		if(a < 2)
			npMove(4,0,1);
		else if(a < 4)
			npMove(4,1,0);
		else
			npMove(4,0,-1);
		if(a == 4)
			npDir(0,SOUTH);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(3);
	//---���������āE�E�E
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	evFadeOut(500);
	evFieldNoFlip(0,1);
	evFadeIn(500);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	evFadeOut(2000);

	//---�������x�݂Ȃ���
	crfieldChangeScene(2,15,15);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(2000);

	//---�ڂ��o�߂� 5,7
	crfieldChangeScene(0,12,9);
	evReloadMap(0);
	evReadObject(0,"LunarnSlp2.acf");
	npPos(0,13,7);
	npDir(0,SOUTH);
	npPos(2,5,7);
	evScene(0,12,9);

	evFrameWait(500);
	npDir(0,WEST);
	evFrameWait(100);
	npDir(0,SOUTH);
	evFrameWait(100);
	npDir(0,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---����
	evFrameWait(500);
	npDir(0,NORTH);
	evFrameWait(500);
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(500);
	npDir(0,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	//---�i�b�N
	evFrameWait(500);
	npDir(2,SOUTH);
	for(a = 0;a < 13;a ++){
		if(a < 4)
			npMove(2,0,1);
		else if(a < 12)
			npMove(2,1,0);
		else
			npMove(2,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	//---�������ł��I�H
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---�N����
	evReadObject(0,"Lunarn.acf");
	npPos(0,12,7);
	npDir(0,SOUTH);
	npPos(2,12,8);
	npDir(2,NORTH);
	evScene(0,12,9);
	crmusicPlay(CRMUSIC_ENDLESSP);
	evFrameWait(500);
	mes.ReadDraw();

	//---�i�b�N�͂����ǂ��Ă����́H
	evFrameWait(500);
	mes.ReadDraw(4);

	evFrameWait(500);
	npDir(0,EAST);
	evFrameWait(500);
	npDir(0,NORTH);
	evFrameWait(500);
	npMove(0,0,-1);
	evFrame();
	evFrameWait(1000);
	mes.ReadDraw();
	//---�W�[�_�C�ցI
	evFrameWait(1500);
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---�݂�Ȃ�
	evFrameWait(250);
	npMove(2,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(2);

	//---�i�b�N�E�E�E
	evFrameWait(1000);
	mes.ReadDraw();
	//---�₽���Ă�
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);

	//---�f�r��
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(2,EAST);
	evFrameWait(250);
	npDir(2,SOUTH);
	evFrameWait(250);
	//---������
	mes.ReadDraw();

	evFrameWait(1000);
	evFrameWait(500);
	npDir(2,WEST);
	evFrameWait(500);
	npDir(2,NORTH);
	evFrameWait(500);
	mes.ReadDraw(2);

	crmusicFadeOut();
	evFrameWait(1000);
	evFadeOut(2000);

	mes.CloseMessage();

	//---�p�[�e�B�[�O��
	evSet(154,1);

	prtRecoveryAll();
	pPartyInfo->PartyMember[1] = 2;
	pPartyInfo->PartyMember[2] = -1;
	pPartyInfo->PartyMember[3] = -1;
	pPartyInfo->PartyMember[4] = -1;

	crcharaLoadFace(-1);
	prtRecoveryAll();

	mcShow(1);
	mcDir(SOUTH);

	crmusicPlay(CRMUSIC_INIT);
	et->Delay2(2000);
	evMap(10,0,327,235);

	return 1;
}

//---���C�[���Q��I�I
CREVENTLONG4_API int creventGiedie_Lizel(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	npPos(0,21,16);
	npDir(0,NORTH);
	npPos(1,20,16);
	npDir(1,NORTH);
	evScene(2,21,17);

	evFrameWait(250);
	mes.OpenMessage("GiedieDokutu.msg",100);
	mes.ReadDraw(3);

	//---����c
	evFrameWait(250);
	npPos(0,25,25);
	npDir(0,EAST);
	npPos(1,26,25);
	npDir(1,WEST);
	evScene(2,25,27);

	//---�ǂ����悤���H
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	evScene(3,15,15);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---�킽���B��������E�E�E
	evScene(2,25,27);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	evScene(3,15,15);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---�ł�
	evScene(2,25,27);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	evScene(3,15,15);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---������낤����Ȃ��I�I
	evScene(2,25,27);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);

	//---�J�����ړ�
	for(a = 0;a < 4;a ++){
		mcMove(-1,0);
		evFrame();
	}
	for(a = 0;a < 10;a ++){
		mcMove(0,-1);
		evFrame();
	}

	for(a = 0;a < 16;a ++){
		if(a < 4)
			npMove(0,-1,0);
		else if(a < 13)
			npMove(0,0,-1);
		if(a < 1){
		} else if(a < 7)
			npMove(1,-1,0);
		else if(a < 16)
			npMove(1,0,-1);

		evFrame();
	}
	evFrameWait(250);

	//---
	mes.ReadDraw(3);
	//---�ǂ����Ă�
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);

	//---�o�g��
	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = CRMUSIC_BATTLE;
	BattleInfo.Enemy[0].Enemy = 121;
	BattleInfo.Enemy[0].x = 5;
	BattleInfo.Enemy[0].y = 6;
	BattleInfo.Enemy[1].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
//	BattleInfo.MapNumber = 1;
	evField(0,1);

	npPos(0,21,16);
	npPos(1,20,17);
	npPos(3,20,15);

	npPos(4,21,9);
	npDir(4,SOUTH);
	npPos(5,21,8);
	npDir(5,SOUTH);
	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}

	//---���E�E�E
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(250);

	//---�G�^�[�i��������
	for(a = 0;a < 4;a ++){
		npMove(4,0,1);
		npMove(5,0,1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(250);
	npMove(4,0,1);
	evFrame();
	evFrameWait(250);
	npMove(0,0,1,0);
	evFrame();
	npMove(1,0,1,0);
	evFrame();
	evFrameWait(250);
	npMove(5,0,1);
	evFrame();
	npMove(4,0,1);
	evFrame();
	npMove(5,0,1);
	evFrame();

	//---���̍߂̏d����
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---��̐�
	mes.ReadDraw();

	evFrameWait(250);
	npDir(4,WEST);
	evFrameWait(250);
	npDir(5,EAST);
	npDir(4,SOUTH);
	evFrameWait(250);
	npDir(5,SOUTH);
	npDir(4,EAST);
	evFrameWait(250);
	npDir(4,SOUTH);
	evFrameWait(250);

	mes.ReadDraw(2);

	//---���납�Ȃ�
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(250);
	npDir(4,WEST);
	evFrameWait(250);
	npDir(4,SOUTH);
	evFrameWait(250);
	npDir(4,EAST);
	evFrameWait(250);
	npDir(4,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---�΂��̓�
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---���g����
	evFrameWait(250);
	npPos(2,21,26);
	npDir(2,SOUTH);
	for(a = 0;a < 10;a ++){
		mcMove(0,1);
		evFrame();
	}
	crmusicPlay(CRMUSIC_LIZEL);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(250);
	npDir(2,WEST);
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);

	npDir(0,SOUTH);
	npDir(1,SOUTH);
	for(a = 0;a < 8;a ++){
		mcMove(0,-1);
		evFrame();
	}

	for(a = 0;a < 7;a ++){
		npMove(2,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(3);

	//---���O���n�������̂��H
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(150);
	npDir(1,WEST);
	evFrameWait(100);
	npDir(0,NORTH);
	evFrameWait(150);
	npDir(1,NORTH);
	evFrameWait(250);
	//---�{���Ȃ�
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw(3);

	//---����������I�I
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);

	//---���C�[���Ăђ��ԂɂȂ�
	{
		pPartyInfo->PartyMember[2] = 5;
		pPartyInfo->PartyMember[4] = -1;

		int level = crcharaGetPartyMember(0)->GetLevel();
		CrCharacter *pChara = crcharaGetPartyMember(2);

		if(level < 25 && pChara->GetLevel() < 25){
			crcharaSetLevelStatus(2,25);
			pChara->SetLevelExperience();
		} else if(level > pChara->GetLevel() && level < 35){
			//---���i���̕������������烌�x���Z�b�g
			crcharaSetLevelStatus(2,level + 1);
			pChara->SetLevelExperience();
		} else if(level > pChara->GetLevel() && level >= 35){
			//---���x���R�T�ȏゾ������
			crcharaSetLevelStatus(2,35);
			pChara->SetLevelExperience();
		}

		pChara->SetWeapon(0,81);
		pChara->SetWeapon(1,0);
		pChara->SetProtector(0,129);
		pChara->SetProtector(1,165);
		pChara->SetProtector(2,251);
		pChara->SetBattleFieldStartPos(5,4);
		crcharaLoadFace(-1);
		crcharaCheckBattleFieldPos(2);
	}
	prtRecovery(2);

	//---�o�g��
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = CRMUSIC_BATTLE;
	BattleInfo.Enemy[0].Enemy = 121;
	BattleInfo.Enemy[0].x = 8;
	BattleInfo.Enemy[0].y = 6;
	BattleInfo.Enemy[1].Enemy = 122;
	BattleInfo.Enemy[1].x = 4;
	BattleInfo.Enemy[1].y = 8;
	BattleInfo.Enemy[2].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
//	BattleInfo.MapNumber = 1;
	evField(0,1);

	npPos(0,21,17);
	npPos(2,21,16);
	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}

	//---������
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	npDir(5,EAST);
	evFrameWait(125);
	npDir(4,WEST);
	evFrameWait(125);
	npDir(5,NORTH);
	evFrameWait(125);
	npDir(4,NORTH);
	evFrameWait(125);
	npDir(3,EAST);
	evFrameWait(125);

	for(a = 0;a < 10;a ++){
		if(a < 1)
			npMove(3,1,0);
		else
			npMove(3,0,-1);
		npMove(4,0,-1);
		npMove(5,0,-1);
		evFrame();
	}
	//---��������I
	evFrameWait(250);
	npMove(1,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---���������͂ǂ����āH
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(2,WEST);
	evFrameWait(250);
	npDir(2,SOUTH);
	evFrameWait(250);

	//---�����R
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);

	//---�Ƃ���ŁE�E�E
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	evSet(158,1);
	evScene(2,21,18);
	evReloadMapMusic();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);

	for(a = 0;a <= 5;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	mcShow(1);
	mcDir(NORTH);
	evScene(2,21,16);

	mes.CloseMessage();


	return 1;
}

//---�L���̈�ՁA����G�^�[�i���I�I
CREVENTLONG4_API int creventKiokunoIseki_Kessen(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	npPos(0,14,41);
	npDir(0,EAST);
	npPos(2,14,42);
	npDir(2,EAST);
	npPos(5,13,42);
	npDir(5,EAST);

	npPos(6,16,27);
	npDir(6,SOUTH);
	npPos(7,19,28);
	npDir(7,SOUTH);

	npPos(8,15,31);
	npDir(8,WEST);
	npPos(9,22,26);
	npDir(9,SOUTH);
	npPos(10,19,25);
	npDir(10,WEST);
	npPos(11,21,30);
	npDir(11,SOUTH);
	npPos(12,23,31);
	npDir(12,SOUTH);
	npPos(13,14,26);
	npDir(13,EAST);

	evScene(0,14,43);

	for(a = 0;a < 18;a ++){
		if(a < 4)
			mcMove(1,0);
		else
			mcMove(0,-1);
		evFrame();
	}
	evFrameWait(500);

	mes.OpenMessage("KiokunoIseki.msg",100);
	mes.ReadDraw(2);

	//---�G�h
	evFrameWait(1000);
	npMove(6,0,1);
	evFrame();
	evFrameWait(50);
	npDir(6,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	//---�Ȃ񂶂�H
	evFrameWait(500);
	npDir(7,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	//---��������̂�
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---������I
	for(a = 0;a < 18;a ++){
		if(a < 14)
			mcMove(0,1);
		else
			mcMove(-1,0);
		evFrame();
	}
	evFrameWait(500);

	npPos(14,10,52);
	npDir(14,NORTH);
	for(a = 0;a < 8;a ++){
		npMove(14,0,-1);
		evFrame();
	}
	evFrameWait(250);
	npDir(14,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	//---�U�����
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(80);
	npDir(5,SOUTH);
	evFrameWait(80);
	npDir(2,SOUTH);
	evFrameWait(80);
	npDir(0,WEST);
	evFrameWait(80);
	npDir(5,WEST);
	evFrameWait(80);
	npDir(2,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---�킢�I
	evFrameWait(250);

	//-------------------
	//---�o�g��
	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));

	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = CRMUSIC_BATTLE;
	BattleInfo.Enemy[0].Enemy = 121;
	BattleInfo.Enemy[0].x = 6;
	BattleInfo.Enemy[0].y = 7;
	BattleInfo.Enemy[1].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
//	BattleInfo.MapNumber = 1;
	evField(0,1);

	npPos(14,0,0);
	npShow(14,0);

	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}

	//---�N������́I�H
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---��ނ���
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);

	//---�s�����I
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(500);
	npDir(2,NORTH);
	evFrameWait(125);
	npDir(5,NORTH);
	evFrameWait(125);
	npDir(2,EAST);
	evFrameWait(125);
	npDir(5,EAST);
	evFrameWait(250);

	mes.ReadDraw(2);
	evFrameWait(250);
	crmusicPlay(CRMUSIC_BREAKFORTUNE);

	for(a = 6;a <= 13;a ++){
		npDir(a,SOUTH);
	}
	npPos(6,17,29);
	npPos(8,16,32);
	npPos(13,17,31);

	for(a = 0;a < 13;a ++){
		if(a < 4)
			mcMove(1,0);
		else
			mcMove(0,-1);
		evFrame();
	}

	for(a = 0;a < 11;a ++){
		if(a < 4)
			npMove(0,1,0);
		else
			npMove(0,0,-1);
		if(a < 4)
			npMove(2,1,0);
		else
			npMove(2,0,-1);
		if(a < 4)
			npMove(5,1,0);
		else
			npMove(5,0,-1);

		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---������������
	npMove(8,0,1);
	npMove(13,0,1);
	evFrame();
	evFrameWait(250);


	//---�킢�I
	//-------------------
	//---�o�g��
	memset(&BattleInfo,0,sizeof(BattleInfo));

	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = 0;
	BattleInfo.Enemy[0].Enemy = 122;
	BattleInfo.Enemy[0].x = 4;
	BattleInfo.Enemy[0].y = 9;
	BattleInfo.Enemy[1].Enemy = 123;
	BattleInfo.Enemy[1].x = 7;
	BattleInfo.Enemy[1].y = 8;
	BattleInfo.Enemy[2].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
//	BattleInfo.MapNumber = 1;
	evField(0,1);

	npPos(8,0,0);
	npShow(8,0);
	npPos(13,0,0);
	npShow(13,0);

	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}

	evFrameWait(250);

	//---�܂�����Ȃɂ����ς�
	for(a = 0;a < 4;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(1000);
	for(a = 0;a < 4;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(2);

	//---����Ȃ��ƌ����Ă��
	evFrameWait(500);
	mes.ReadDraw();

	npPos(1,29,29);
	npDir(1,WEST);
	npPos(3,30,28);
	npDir(3,WEST);
	npPos(4,30,30);
	npDir(4,WEST);
	evFrameWait(250);
	for(a = 0;a < 10;a ++){
		mcMove(1,0);
		if(a == 7)
			npDir(11,EAST);
		if(a == 6)
			npDir(12,EAST);
		evFrame();
	}
	for(a = 0;a < 4;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();

	//---�܂�������
	evFrameWait(250);
	npMove(1,-1,0);
	evFrame();

	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	npMove(3,-1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	npMove(4,-1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	npDir(0,EAST);
	npDir(2,EAST);
	npDir(7,EAST);
	npDir(9,EAST);

	//---���l�W�܂낤��
	for(a = 0;a < 10;a ++){
		mcMove(-1,0);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);

	//---�I���͂�������
	for(a = 0;a < 10;a ++){
		mcMove(1,0);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	for(a = 0;a < 10;a ++){
		mcMove(-1,0);
		evFrame();
	}
	for(a = 0;a < 4;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	evScene(1,15,15);
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);

	//---���C�t�J�v�Z���r
	critemAddItem(222,10);
	//---�}�W�b�N
	critemAddItem(223,3);
	//---���P�V�X
	critemAddItem(227,4);
	//---�G���_�[
	critemAddItem(225,1);
	//---�L���A�[
	critemAddItem(226,5);
	//---���j���[�E�f�B�U
	{
		CrCharacter *pChara;

		pPartyInfo->PartyMember[0] = 1;
		pPartyInfo->PartyMember[1] = 3;
		pPartyInfo->PartyMember[2] = 4;
		pPartyInfo->PartyMember[3] = -1;

		for(a = 0;a < 2;a ++){
			pChara = crcharaGetPartyMember(a);
			if(pChara->GetLevel() < 40){
				crcharaSetLevelStatus(a,pChara->GetLevel() + 1);
				pChara->SetLevelExperience();
			}
			if(a == 0){
				pChara->SetBattleFieldStartPos(5,4);
				for(b = 0;b < 2;b ++){
					//---�f�B�U�̕���
					int wp = pChara->GetWeapon(b);
					if(1 <= wp && wp <= 4){
						pChara->SetWeapon(b,43);
					}
					if(39 <= wp && wp <= 42){
						pChara->SetWeapon(b,43);
					}
					if(10 <= wp && wp <= 15){
						pChara->SetWeapon(b,16);
					}
					if(31 <= wp && wp <= 32){
						pChara->SetWeapon(b,33);
					}
				}
			} else {
				for(b = 0;b < 2;b ++){
					//---�T���B�A�[�̕���
					int wp = pChara->GetWeapon(b);
					if(49 <= wp && wp <= 54){
						pChara->SetWeapon(b,55);
						break;
					}
				}
				pChara->SetBattleFieldStartPos(7,2);
			}
		}

		int level = crcharaGetPartyMember(0)->GetLevel();
		pChara = crcharaGetPartyMember(2);

		if(level > pChara->GetLevel() && level < 40){
			//---�f�B�U�̕������������烌�x���Z�b�g
			crcharaSetLevelStatus(2,level);
			pChara->SetLevelExperience();
		} else if(level > pChara->GetLevel() && level >= 40){
			//---���x���S�O�ȏゾ������
			crcharaSetLevelStatus(2,40);
			pChara->SetLevelExperience();
		}

/*		pChara->SetWeapon(0,54);
		pChara->SetWeapon(1,0);
		pChara->SetProtector(0,105);
		pChara->SetProtector(1,144);
		pChara->SetProtector(2,260);*/

		pChara->SetBattleFieldStartPos(3,1);
		for(a = 0;a < 2;a ++){
			if(49 <= pChara->GetWeapon(a) && pChara->GetWeapon(a) <= 54){
				pChara->SetWeapon(a,55);
				break;
			}
		}
		if(109 <= pChara->GetProtector(0) && pChara->GetProtector(0) <= 113){
			pChara->SetProtector(0,113);
		}

		crcharaLoadFace(-1);
		crcharaCheckBattleFieldPos(0);
		crcharaCheckBattleFieldPos(1);
		crcharaCheckBattleFieldPos(2);
	}
	prtRecoveryAll();
	crmainMainMenu(1);
	evFrameWait(500);


	//---���j���[�E���i��
	{
		pPartyInfo->PartyMember[0] = 0;
		pPartyInfo->PartyMember[1] = 2;
		pPartyInfo->PartyMember[2] = 5;
		pPartyInfo->PartyMember[3] = -1;
		crcharaLoadFace(-1);
	}
	crmainMainMenu(1);

	//---�������I
	{
		pPartyInfo->PartyMember[0] = 1;
		pPartyInfo->PartyMember[1] = 3;
		pPartyInfo->PartyMember[2] = 4;
		pPartyInfo->PartyMember[3] = -1;
	}
	crfieldChangeScene(0,25,30);
	npDir(0,NORTH);
	npDir(2,NORTH);
	npDir(5,NORTH);
	evScene(0,25,30);
//	crmusicPlay(CRMUSIC_DRAGONBREATH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	for(a = 0;a < 5;a ++){
		npMove(1,-1,0);
		npMove(3,-1,0);
		npMove(4,-1,0);

		if(a > 2)
			npMove(7,1,0);

		evFrame();
	}
	evFrameWait(250);

	//---�o�g��
	int fail = 0,dizza = 0,lunarn = 0;

	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = 0;
	BattleInfo.Enemy[2].Enemy = 122;
	BattleInfo.Enemy[2].x = 3;
	BattleInfo.Enemy[2].y = 7;
	BattleInfo.Enemy[0].Enemy = 131;
	BattleInfo.Enemy[0].x = 6;
	BattleInfo.Enemy[0].y = 9;
	BattleInfo.Enemy[1].Enemy = 123;
	BattleInfo.Enemy[1].x = 10;
	BattleInfo.Enemy[1].y = 7;
	BattleInfo.Enemy[3].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	BattleInfo.FailOK = 1;
	BattleInfo.KeepEnemyNumber = 1;
	evField(0,1);

	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		//---�����I
		fail ++;
		dizza ++;
	}

	//---�p�[�e�B�[�g�ݑւ�
	{
		pPartyInfo->PartyMember[0] = 0;
		pPartyInfo->PartyMember[1] = 2;
		pPartyInfo->PartyMember[2] = 5;
		pPartyInfo->PartyMember[3] = -1;
		crcharaLoadFace(-1);
	}

	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = 0;
	BattleInfo.Enemy[2].Enemy = 121;
	BattleInfo.Enemy[2].x = 3;
	BattleInfo.Enemy[2].y = 9;
	BattleInfo.Enemy[0].Enemy = 132;
	BattleInfo.Enemy[0].x = 6;
	BattleInfo.Enemy[0].y = 7;
	BattleInfo.Enemy[1].Enemy = 124;
	BattleInfo.Enemy[1].x = 10;
	BattleInfo.Enemy[1].y = 8;
	BattleInfo.Enemy[3].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_NONE;
	BattleInfo.FailOK = 1;
	BattleInfo.KeepEnemyNumber = 4;
	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		//---�����I
		fail ++;
		lunarn ++;
		if(fail >= 2){
			//---�Q�p�[�e�B�[�Ƃ���������
			return MAINLOOP_BATTLEFAIL;
		}
	}

	if(dizza){
		//---�f�B�U�p�[�e�B�[�������Ă���
		{
			pPartyInfo->PartyMember[0] = 0;
			pPartyInfo->PartyMember[1] = 2;
			pPartyInfo->PartyMember[2] = 5;
			pPartyInfo->PartyMember[3] = -1;
			crcharaLoadFace(-1);
		}
		memset(&BattleInfo,0,sizeof(BattleInfo));
		BattleInfo.MapNumber = crfieldGetMapNumber();
		BattleInfo.SceneNumber = crfieldGetMapScene();
		BattleInfo.Music = 0;
		BattleInfo.LoadKeepEnemy = 1;
		BattleInfo.LoadKeepEnemyCount = 3;
		BattleInfo.Enemy[2].Enemy = 122;
		BattleInfo.Enemy[2].x = 3;
		BattleInfo.Enemy[2].y = 7;
		BattleInfo.Enemy[0].Enemy = 131;
		BattleInfo.Enemy[0].x = 6;
		BattleInfo.Enemy[0].y = 9;
		BattleInfo.Enemy[1].Enemy = 123;
		BattleInfo.Enemy[1].x = 10;
		BattleInfo.Enemy[1].y = 7;
		BattleInfo.Enemy[3].Enemy = -1;
		BattleInfo.ScreenEfect = CRINTOBAT_NONE;
		BattleInfo.FailOK = 1;

		if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
			//---�����I
			return MAINLOOP_BATTLEFAIL;
		}
	} else if(lunarn){
		//---���i���p�[�e�B�[�������Ă���
		{
			pPartyInfo->PartyMember[0] = 1;
			pPartyInfo->PartyMember[1] = 3;
			pPartyInfo->PartyMember[2] = 4;
			pPartyInfo->PartyMember[3] = -1;
			crcharaLoadFace(-1);
		}
		memset(&BattleInfo,0,sizeof(BattleInfo));
		BattleInfo.MapNumber = crfieldGetMapNumber();
		BattleInfo.SceneNumber = crfieldGetMapScene();
		BattleInfo.Music = 0;
		BattleInfo.LoadKeepEnemy = 4;
		BattleInfo.LoadKeepEnemyCount = 3;
		BattleInfo.Enemy[2].Enemy = 121;
		BattleInfo.Enemy[2].x = 3;
		BattleInfo.Enemy[2].y = 9;
		BattleInfo.Enemy[0].Enemy = 132;
		BattleInfo.Enemy[0].x = 6;
		BattleInfo.Enemy[0].y = 7;
		BattleInfo.Enemy[1].Enemy = 124;
		BattleInfo.Enemy[1].x = 10;
		BattleInfo.Enemy[1].y = 8;
		BattleInfo.Enemy[3].Enemy = -1;
		BattleInfo.ScreenEfect = CRINTOBAT_NONE;
		BattleInfo.FailOK = 1;

		if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
			//---�����I
			return MAINLOOP_BATTLEFAIL;
		}
	}

	//---------------------------------------
	//---�킢�̌�
	for(a = 8;a < 14;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	npPos(0,16,28);
	npDir(0,NORTH);
	npPos(1,15,26);
	npDir(1,NORTH);
	npPos(2,18,29);
	npDir(2,NORTH);
	npPos(3,15,28);
	npDir(3,NORTH);
	npPos(4,19,27);
	npDir(4,NORTH);
	npPos(5,17,29);
	npDir(5,NORTH);

	npPos(6,12,26);
	npDir(6,EAST);
	npPos(7,22,25);
	npDir(7,WEST);

	evScene(0,16,28);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	crfieldChangeMap(70,0,1,1);
	npPos(0,8,17);
	npDir(0,NORTH);
	npPos(1,7,17);
	npDir(1,NORTH);
	npPos(2,10,18);
	npDir(2,NORTH);
	npPos(3,12,17);
	npDir(3,NORTH);
	npPos(4,9,16);
	npDir(4,NORTH);
	npPos(5,6,18);
	npDir(5,NORTH);

	//---��Ղ̒�
	evScene(0,8,19);
	evFrameWait(500);
	mes.ReadDraw();


	//---�ǂ�����āH
	evFrameWait(500);
	npDir(2,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(1,EAST);
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(150);
	npDir(3,WEST);
	evFrameWait(150);
	npDir(5,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	//---�����ɂ���
	evFrameWait(500);
	npDir(5,EAST);
	evFrameWait(250);
	npDir(4,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	//---�D�ŁH
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---�U�l�ŁH
	evFrameWait(1000);
	npMove(3,-1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);
	npDir(2,EAST);
	evFrameWait(250);
	npDir(4,SOUTH);
	evFrameWait(250);
	npDir(4,EAST);

	//---������
	evFrameWait(500);
	mes.ReadDraw();

	//---���~�ƃ��C�[��
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npMove(5,1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(4,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---���~�H
	npMove(0,1,0);
	evFrame();
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);

	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(4,EAST);
	evFrameWait(500);
	npDir(4,NORTH);
	evFrameWait(500);
	npMove(4,0,-1);
	evFrame();
	evFrameWait(150);
	npDir(3,NORTH);
	evFrameWait(150);
	npDir(1,NORTH);
	evFrameWait(150);
	npDir(5,NORTH);
	evFrameWait(800);
	mes.ReadDraw();

	//---���
	evFrameWait(2000);
	npDir(4,WEST);
	evFrameWait(500);
	npDir(4,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---�P�`
	evFrameWait(250);
	mes.ReadDraw();

	//---���i����I
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(5,1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(5,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);


	mes.CloseMessage();

	evSet(159,1);

	//---�p�[�e�B�[�Z�b�g
	pPartyInfo->PartyMember[0] = 0;
	pPartyInfo->PartyMember[1] = 1;
	pPartyInfo->PartyMember[2] = 2;
	pPartyInfo->PartyMember[3] = 3;
	pPartyInfo->PartyMember[4] = -1;
	crcharaCheckBattleFieldPos(0);
	crcharaCheckBattleFieldPos(1);
	crcharaCheckBattleFieldPos(2);
	crcharaCheckBattleFieldPos(3);
	crcharaLoadFace(-1);

	for(a = 0;a <= 5;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	mcShow(1);
	mcDir(NORTH);
	evScene(0,8,16);

	return 1;
}

//---9,8
//---�L���̈�ՁA�Ώ̂̃v���[�g
CREVENTLONG4_API int creventKiokunoIseki_Taisho(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	crfieldChangeScene(7,9,18);

	npPos(1,10,19);
	npDir(1,NORTH);
	npPos(2,9,18);
	npDir(2,NORTH);
	npPos(3,11,19);
	npDir(3,NORTH);
	npPos(4,7,18);
	npDir(4,NORTH);
	evScene(7,9,18);

	evFrameWait(500);
	for(a = 0;a < 12;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(2000);
	for(a = 0;a < 12;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(500);

	mes.OpenMessage("KiokunoIseki.msg",106);
	mes.ReadDraw();

	//---���������Ă���
	evFrameWait(500);
	npMove(4,0,-1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	for(a = 0;a < 2;a ++){
		npMove(4,0,-1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();

	//---�������ɂ������v���[�g��
	evFrameWait(500);
	for(a = 0;a < 5;a ++){
		if(a < 3)
			npMove(3,0,-1);
		else
			npMove(3,-1,0);
		evFrame();
	}
	evFrameWait(100);
	npDir(3,NORTH);
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---������
	npPos(1,8,7);
	npDir(1,NORTH);
	npPos(2,9,5);
	npDir(2,SOUTH);
	npPos(3,11,6);
	npDir(3,WEST);
	npPos(4,9,18);
	npDir(4,NORTH);
	evScene(7,9,10);

	evFrameWait(500);
	mes.ReadDraw();
	//---�ǂ���
	evFrameWait(500);
	for(a = 0;a < 10;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();

	//---���
	evFrameWait(500);
	for(a = 0;a < 12;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(500);
	npMove(2,0,1);
	evFrame();
	evFrameWait(250);

	//---�J��
	em->Put(13,4,2,1024);
	em->Put(13,3,2,1024);
	crsoundPlay(CRSOUND_ATACK4);
	evFrameWait(250);

	//---�J�����I
	npDir(3,NORTH);
	evFrameWait(125);
	npDir(1,EAST);
	evFrameWait(125);
	npDir(3,EAST);
	evFrameWait(125);
	npDir(2,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	//---�f�B�U���ǂ�
	npDir(2,NORTH);
	evFrameWait(250);
	npMove(2,0,-1);
	evFrame();
	evFrameWait(250);
	em->Put(13,4,2,35);
	em->Put(13,3,2,35);
	crsoundPlay(CRSOUND_ATACK4);
	evFrameWait(250);
	npDir(2,EAST);
	evFrameWait(500);
	mes.ReadDraw(1);
	evFrameWait(500);

	//---����c
	npPos(1,8,6);
	npDir(1,EAST);
	npPos(2,9,5);
	npDir(2,SOUTH);
	npPos(3,10,6);
	npDir(3,WEST);
	npPos(4,9,7);
	npDir(4,NORTH);
	evScene(7,9,8);
	evFrameWait(500);

	mes.ReadDraw(2);
	//---�f�B�U����
	evFrameWait(500);
	mes.ReadDraw(2);

	//---���
	evFrameWait(500);
	mes.ReadDraw(2);

	//---�f�B�U�����H
	evFrameWait(500);
	npDir(1,NORTH);
	evFrameWait(250);
	npMove(1,0,-1);
	evFrame();
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(2,WEST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---
	npPos(1,10,4);
	npDir(1,SOUTH);
	npPos(2,9,4);
	npDir(2,SOUTH);
	npPos(3,9,6);
	npDir(3,NORTH);
	npPos(4,9,18);
	npDir(4,NORTH);
	em->Put(13,4,2,1024);
	em->Put(13,3,2,1024);

	evScene(7,9,18);
	evFrameWait(500);
	for(a = 0;a < 12;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(1,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(1,SOUTH);
	evFrameWait(125);
	npDir(2,SOUTH);
	evFrameWait(125);
	npDir(1,EAST);
	evFrameWait(125);
	npDir(2,EAST);
	evFrameWait(250);

	for(a = 0;a < 15;a ++){
		npMove(1,1,0);
		if(a)
			npMove(2,1,0);
		if(a == 5)
			npDir(3,EAST);
		evFrame();
	}
	npShow(1,0);
	npShow(2,0);

	crmusicFadeOut();
	for(a = 0;a < 14;a ++){
		mcMove(1,0);
		evFrame();
	}
	evFrameWait(1000);
	crmusicPlay(CRMUSIC_SILENT);

	//---�p�[�e�B�[���炷
	pPartyInfo->PartyMember[2] = -1;
	pPartyInfo->PartyMember[3] = -1;
	pPartyInfo->PartyMember[4] = -1;
	crcharaLoadFace(-1);

	mes.CloseMessage();

	evSet(162,1);

	mcShow(1);
	mcDir(SOUTH);
	evScene(8,5,2);

	return 1;
}

//---�L���̈�ՁA���i����l�ŁE�E�E
CREVENTLONG4_API int creventKiokunoIseki_OnlyLunarn(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	crfieldChangeScene(9,12,6);

	npPos(0,12,4);
	npDir(0,SOUTH);
	npPos(1,11,4);
	npDir(1,SOUTH);

	evScene(9,12,6);
	evFrameWait(500);
	for(a = 0;a < 10;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(1500);
	for(a = 0;a < 10;a ++){
		mcMove(0,-1);
		evFrame();
	}

	evFrameWait(500);

	mes.OpenMessage("KiokunoIseki.msg",107);
	mes.ReadDraw(2);

	//---�f�B�U���������Ƃ���
	evFrameWait(500);
	npMove(1,0,1);
	evFrame();

	//---�t���b�V��
	{
		crsoundPlay(CRSOUND_KIOKUNOISEKI_BARRIER);
		evFill(ep->ToRGB(CRCOLOR_WHITE));
		ew->Flip();
		et->Delay2(50);
		evFieldNoFlip(0,1);
		evFadeIn(100,RGB_MAKE(255,255,255));

		npMove(1,0,-1,0);
		evFrame();
		evFrameWait(250);
	}
	mes.ReadDraw();
	evFrameWait(250);

	//---�ǂ������́H
	npDir(0,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---���i�������Ă݂�
	npDir(0,SOUTH);
	evFrameWait(500);
	npMove(0,0,1);
	evFrame();
	evFrameWait(500);
	npMove(0,0,1);
	evFrame();

	evFrameWait(500);
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	//---�������t���b�V��
	npMove(1,0,1);
	evFrame();
	{
		crsoundPlay(CRSOUND_KIOKUNOISEKI_BARRIER);
		evFill(ep->ToRGB(CRCOLOR_WHITE));
		ew->Flip();
		et->Delay2(50);
		evFieldNoFlip(0,1);
		evFadeIn(100,RGB_MAKE(255,255,255));

		npMove(1,0,-1,0);
		evFrame();
		evFrameWait(500);
	}
	mes.ReadDraw();
	evFrameWait(800);

	//---�N���C�V���̐�
	mes.ReadDraw();
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);
	crmusicPlay(CRMUSIC_CRAYSIVE);
	evFrameWait(250);

	mes.ReadDraw(2);

	//---�Ă�
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

	//---���s��
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(500);
	mes.ReadDraw();
	//---�C�������
	evFrameWait(250);
	npDir(1,EAST);
	npMove(1,1,0);
	evFrame();
	evFrameWait(150);
	npDir(1,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---���i��
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(1000);
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);
	//---������
	mes.ReadDraw();
	//---���ɉ�Ƃ���
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	//---�s���ė���
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(1000);
	//---���i������
	for(a = 0;a < 3;a ++){
		npMove(0,0,1);
		evFrame();
	}
	evFrameWait(250);

	//---�p�[�e�B�[
	pPartyInfo->PartyMember[1] = -1;
	pPartyInfo->PartyMember[2] = -1;
	pPartyInfo->PartyMember[3] = -1;
	pPartyInfo->PartyMember[4] = -1;
	crcharaLoadFace(-1);

	mcShow(1);
	mcDir(SOUTH);
	evFadeOut(1000);
	crfieldChangeScene(10,26,24);
	evFieldNoFlip(0,1);
	et->Delay2(1200);
	evFadeIn(1000);

	mes.CloseMessage();

	return 1;
}


//----------------------------------------------------

ei_s32 cresbatCallBack1(int turn,int action,int number,
				  ei_u32 com,CrCharacter *chara)
{
	CR_BATTLECOMMAND *pCommand = (CR_BATTLECOMMAND *)com;
	CrBattleCharacter *pChara = (CrBattleCharacter *)chara;

	if(action == 0){
		return 1;
	}
	if(action == 1){
		if(number == 0){
			if(turn == 0){
				pCommand->Main = BAT_COMMAND_WAIT;
			} else {
				if(turn == 1){
					CrMesManager mes;
					mes.CreateNewMessage(-1,-1,32,24,5);
					mes.OpenMessage("Fillgalt.msg",101);
					mes.ReadMessage();
					mes.Draw();
					mes.CloseMessage();
				}
				//---�N���X�e�B�[��
				pCommand->Main = BAT_COMMAND_ENEMYABILITY;
				pCommand->Sub[0] = BAT_ECOM_CRESTEAJU1;
				pCommand->Sub[3] = 1500;
				pCommand->Hit = 1;
				pCommand->Range = BAT_TARGET_ENEMYALL;
				pCommand->Target = (ei_u32)crbatRandomSelect(pChara,BAT_TARGET_ENEMY);
			}
		} else {
			pCommand->Main = BAT_COMMAND_WAIT;
		}
	}

	return 1;
}


ei_s32 cresbatCallBack2(int turn,int action,int number,
				  ei_u32 com,CrCharacter *chara)
{
	CR_BATTLECOMMAND *pCommand = (CR_BATTLECOMMAND *)com;
	CrBattleCharacter *pChara = (CrBattleCharacter *)chara;

	if(action == 0){
		return 1;
	}
	if(action == 1){
		if(number == 0){
			{
				//---�N���X�e�B�[��
				pCommand->Main = BAT_COMMAND_ENEMYABILITY;
				pCommand->Sub[0] = BAT_ECOM_CRESTEAJU1;
				pCommand->Sub[3] = 1500;
				pCommand->Hit = 1;
				pCommand->Range = BAT_TARGET_ENEMYALL;
				pCommand->Target = (ei_u32)crbatRandomSelect(pChara,BAT_TARGET_ENEMY);
			}
		} else {
			pCommand->Main = BAT_COMMAND_WAIT;
		}
	}

	return 1;
}

ei_s32 cresbatCallBack3(int turn,int action,int number,
				  ei_u32 com,CrCharacter *chara)
{
	CR_BATTLECOMMAND *pCommand = (CR_BATTLECOMMAND *)com;
	CrBattleCharacter *pChara = (CrBattleCharacter *)chara;

	if(action == 0){
		return 1;
	}
	if(action == 1){
		if(number == 0){
			if(turn == 0){
				pCommand->Main = BAT_COMMAND_WAIT;
			} else {
				//---�N���X�e�B�[��
				if(turn == 1){
					CrMesManager mes;
					mes.CreateNewMessage(-1,-1,32,24,5);
					mes.OpenMessage("Fillgalt.msg",103);
					mes.ReadMessage();
					mes.Draw();
					mes.CloseMessage();
				}
				pCommand->Main = BAT_COMMAND_ENEMYABILITY;
				pCommand->Sub[0] = BAT_ECOM_CRESTEAJU2;
				pCommand->Sub[3] = 7200;
				pCommand->Hit = 1;
				pCommand->Range = BAT_TARGET_ENEMYALL;
				pCommand->Target = (ei_u32)crbatRandomSelect(pChara,BAT_TARGET_ENEMY);
			}
		} else {
			pCommand->Main = BAT_COMMAND_WAIT;
		}
	} else if(action == 2){
		if(number == 0 && turn == 1){
			return 0;
		}
	}

	return 1;
}

//---�L���̈�ՁA�������[�I�[�u
CREVENTLONG4_API int creventKiokunoIseki_MemoryOve(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	crfieldChangeScene(10,13,13);

	npPos(0,13,13);
	npDir(0,NORTH);

	evScene(10,13,14);
	evFrameWait(500);

	mes.OpenMessage("KiokunoIseki.msg",109);
	mes.ReadDraw();

	//---�I�[�u�͎��̌�낾
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

	for(a = 0;a < 8;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(2000);
	for(a = 0;a < 8;a ++){
		mcMove(0,1);
		evFrame();
	}
	//---�Ӂ[���[��[�H
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---�Ȃ�̂��߂�
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---�I�[�u����ɂ����
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(1000);

	//---���i���A�������[�I�[�u�̕���
	for(a = 0;a < 4;a ++){
		mcMove(0,-1);
		evFrame();
	}
	for(a = 0;a < 9;a ++){
		if(a < 1)
			npMove(0,0,-1);
		else if(a < 2)
			npMove(0,1,0);
		else if(a < 8)
			npMove(0,0,-1);
		else if(a < 9)
			npMove(0,-1,0);

		evFrame();
		if(a == 2)
			evFrameWait(500);
	}

	evFrameWait(250);
	npDir(0,NORTH);

	for(a = 0;a < 7;a ++){
		mcMove(0,-1);
		evFrame();
	}

	evFrameWait(1000);
	npMove(0,0,-1);
	evFrame();
	evFrameWait(1000);
	npMove(0,0,-1);
	evFrame();
	//---���ꂪ�E�E�E
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---����Ȃ�
	evFrameWait(1500);
	mes.ReadDraw();
	evFrameWait(250);
	npMove(0,0,-1);
	evFrame();
	//---������
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	mes.CloseMessage();

//-----------------------------------------
	//---���i���̋L����
	crmusicFadeOut();
	evFadeOut(2000,RGB_MAKE(255,255,255));

	evFill(ep->ToRGB(CRCOLOR_WHITE));
	ew->Flip();
	et->Delay2(3000);

	crfieldChangeMap(71,0,1,1);
	crfieldChangeScene(0,9,13);
	npPos(0,12,12);
	npDir(0,WEST);
	evFieldNoFlip(0,1);
	evFadeIn(2000,RGB_MAKE(255,255,255));
	evFrameWait(1000);

	//---�ڂ��o�߂���
	npDir(1,EAST);
	evFrameWait(500);
	mes.OpenMessage("Fillgalt.msg",100);
	mes.ReadDraw();
	evFrameWait(500);

	//---�N���X�e�B�[������
	for(a = 0;a < 2;a ++){
		npMove(0,-1,0);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	for(a = 0;a < 3;a ++){
		npMove(0,-1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	for(a = 0;a < 3;a ++){
		npMove(0,0,-1);
		evFrame();
	}
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	//---����
	mes.ReadDraw();
	evFrameWait(500);

	//---���̓���
	evScene(4,15,15);
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);

	//---�p�[�e�B�[�Z�b�g
	{
		int level = crcharaGetPartyMember(0)->GetLevel();
		pPartyInfo->PartyMember[0] = 13;

		CrCharacter *pChara = crcharaGetPartyMember(0);
		if(level > pChara->GetLevel())
			crcharaSetLevelStatus(0,level);

		pChara->CharaInfo.max_lp = 9999;
		pChara->CharaInfo.max_mc = 9999;
		pChara->SetLevelExperience();

		pChara->SetWeapon(0,8);
		pChara->SetWeapon(1,0);
		pChara->SetProtector(0,99);
		pChara->SetProtector(1,0);
		pChara->SetProtector(2,0);
		pChara->SetBattleFieldStartPos(6,2);
		crcharaLoadFace(-1);
		crcharaCheckBattleFieldPos(0);
		prtRecoveryAll();
	}


	//----------------------------------------------------
	//---�o�g��
	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = 0;
	BattleInfo.Enemy[0].Enemy = 136;
	BattleInfo.Enemy[0].x = 2;
	BattleInfo.Enemy[0].y = 6;
	BattleInfo.Enemy[1].Enemy = 136;
	BattleInfo.Enemy[1].x = 4;
	BattleInfo.Enemy[1].y = 7;
	BattleInfo.Enemy[2].Enemy = 136;
	BattleInfo.Enemy[2].x = 6;
	BattleInfo.Enemy[2].y = 6;
	BattleInfo.Enemy[3].Enemy = 136;
	BattleInfo.Enemy[3].x = 9;
	BattleInfo.Enemy[3].y = 7;
	BattleInfo.Enemy[4].Enemy = 136;
	BattleInfo.Enemy[4].x = 3;
	BattleInfo.Enemy[4].y = 9;
	BattleInfo.Enemy[5].Enemy = 136;
	BattleInfo.Enemy[5].x = 8;
	BattleInfo.Enemy[5].y = 10;
	BattleInfo.Enemy[6].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_NONE;
	BattleInfo.lpTurnCallBack = cresbatCallBack1;
	BattleInfo.DontShowAfterBattle = 1;
	crbatSetShowStatus(0);
	prtRecoveryAll();

	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
	}
	et->Delay2(1000);
	crhistSubBattleCount();
	//----------------------------------------------------

	//---�Ȃ�Ő���Ă��񂾂낤
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	evScene(5,7,8);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---�������A�É����
	npDir(1,EAST);
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	npMove(1,0,-1);
	evFrame();
	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npMove(1,0,1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---���i��
	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(1000);

	//---�N���C�V����
	crfieldChangeScene(0,7,10);
	npPos(0,6,9);
	npDir(0,WEST);
	npDir(1,EAST);
	evScene(0,7,10);

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---�����Ȃ���
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);


	//---���i��
	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---���Q��
	crfieldChangeScene(0,7,10);
	npPos(0,8,8);
	npDir(0,NORTH);
	npDir(1,NORTH);
	npPos(2,8,6);
	npDir(2,SOUTH);
	evScene(0,7,10);

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---�{��N���C�V��
	npDir(1,EAST);
	evFrameWait(100);
	for(a = 0;a < 3;a ++){
		npMove(1,1,0);
		evFrame();
	}
	evFrameWait(100);
	npDir(1,NORTH);
	evFrameWait(250);
	mes.ReadDraw(3);
	evFrameWait(500);


	//---���i��
	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---���s��
	evScene(0,7,10);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(2,WEST);
	evFrameWait(250);
	npMove(2,-1,0);
	evFrame();
	evFrameWait(250);
	npDir(2,SOUTH);
	evFrameWait(500);
	//---����ɂЂ�����
	mes.ReadDraw(2);
	evFrameWait(500);

	//---���i��
	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---�������I
	evScene(0,7,10);
	evFrameWait(500);
	evFrameWait(150);
	npDir(0,WEST);
	npMove(0,-1,0);
	evFrame();
	evFrameWait(100);
	npDir(0,NORTH);
	evFrameWait(100);

	npMove(0,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);

	//---�s����
	evFrameWait(250);
	npDir(2,EAST);
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

	//---��l�s��
	for(a = 0;a < 10;a ++){
		if(a < 1)
			npMove(2,0,-1);
		else if(a < 7)
			npMove(2,1,0);
		else
			npShow(2,0);

		if(a < 1){
		} else if(a < 3)
			npMove(0,0,-1);
		else if(a < 9)
			npMove(0,1,0);
		else
			npShow(0,0);

		evFrame();
	}
	evFrameWait(1000);

//---���i��
	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(1000);


	//----------------------------------------------------
	//---�o�g��
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = 0;
	BattleInfo.Enemy[0].Enemy = 141;
	BattleInfo.Enemy[0].x = 4;
	BattleInfo.Enemy[0].y = 6;
	BattleInfo.Enemy[1].Enemy = 141;
	BattleInfo.Enemy[1].x = 6;
	BattleInfo.Enemy[1].y = 7;
	BattleInfo.Enemy[2].Enemy = 141;
	BattleInfo.Enemy[2].x = 8;
	BattleInfo.Enemy[2].y = 6;
	BattleInfo.Enemy[3].Enemy = 141;
	BattleInfo.Enemy[3].x = 4;
	BattleInfo.Enemy[3].y = 8;
	BattleInfo.Enemy[4].Enemy = 141;
	BattleInfo.Enemy[4].x = 4;
	BattleInfo.Enemy[4].y = 10;
	BattleInfo.Enemy[5].Enemy = 141;
	BattleInfo.Enemy[5].x = 8;
	BattleInfo.Enemy[5].y = 8;
	BattleInfo.Enemy[6].Enemy = 141;
	BattleInfo.Enemy[6].x = 8;
	BattleInfo.Enemy[6].y = 10;
	BattleInfo.Enemy[7].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_NONE;
	BattleInfo.lpTurnCallBack = cresbatCallBack2;
	BattleInfo.DontShowAfterBattle = 1;
	BattleInfo.MapNumber = 10;
	BattleInfo.SceneNumber = 0;
	BattleInfo.AreaNumber = 8;
	crbatSetShowStatus(0);
	prtRecoveryAll();

	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
	}
	et->Delay2(1000);
	//----------------------------------------------------
	crhistSubBattleCount();


	//---�悭������
	crfieldChangeScene(6,5,18);
	npPos(0,5,17);
	npDir(0,NORTH);
	npPos(1,5,15);
	npDir(1,SOUTH);
	evScene(6,5,18);

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(1,WEST);
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	//---��l����
	for(a = 0;a < 10;a ++){
		npMove(1,0,-1);
		if(a)
			npMove(0,0,-1);
		evFrame();
	}
	evFrameWait(1000);
	npShow(0,0);
	npShow(1,0);
	for(a = 0;a < 12;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(500);

/*	//---�j����
	npDir(2,WEST);
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);
	for(a = 0;a < 6;a ++){
		if(a < 1)
			npMove(2,0,-1);
		else
			npMove(2,1,0);
		evFrame();
	}
	npShow(2,0);
	evFrameWait(1000);*/

//---���i��
	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---�L��
	crfieldChangeScene(1,48,17);
	npPos(2,45,14);
	npDir(2,EAST);
	npPos(3,46,14);
	npDir(3,WEST);

	npPos(0,53,15);
	npPos(1,53,15);
	evScene(1,48,17);

	evFrameWait(1000);
	npDir(1,WEST);
	for(a = 0;a < 20;a ++){
		npMove(1,-1,0);
		if(a < 2){
		} else
			npMove(0,-1,0);

		if(a == 6)
			npDir(2,SOUTH);
		if(a == 9)
			npDir(2,WEST);
		if(a == 8)
			npDir(3,SOUTH);
		if(a == 11)
			npDir(3,WEST);
		evFrame();
	}
	//---�Ђ��Ђ��b��
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);

	for(a = 0;a <= 3;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}

//---���i��
	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---�N���C�V����
	crfieldChangeScene(0,7,10);
	npPos(0,6,9);
	npDir(0,WEST);
	npPos(1,4,9);
	npDir(1,EAST);
	evScene(0,7,10);

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);

//---���i��
	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	evScene(0,7,10);
	evFrameWait(500);
	mes.ReadDraw();
	//---���߂�
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	//---����
	evFrameWait(500);
	npDir(1,NORTH);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(250);
	mes.ReadDraw();

	//---�����A�����ɂ����邾��
	evFrameWait(500);
	npDir(1,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

//---���i��
	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw(3);
	evFrameWait(1000);

	//---�N���C�V����
	crfieldChangeScene(0,7,10);
	npPos(0,12,12);
	npDir(0,WEST);
	npPos(1,4,9);
	npDir(1,NORTH);
	evScene(0,7,12);

	evFrameWait(500);
	npMove(0,-1,0);
	evFrame();
	npDir(1,EAST);
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);

//---���i��
	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	crfieldChangeScene(0,11,12);
	npDir(1,NORTH);
	npPos(0,0,0);
	npShow(0,0);
	npPos(2,0,0);
	npShow(2,0);
	mcShow(1);
	mcDir(WEST);
	crfieldSetMainCharacter(6);
	evScene(0,11,12);
	evSet(EV_MENU_MODE,1);

	crbatSetShowStatus(1);
	mes.CloseMessage();

	return 1;
}

//---�L���̒��A�����ĕ����
CREVENTLONG4_API int creventKiokunoNaka_Fuin(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

//---���i��
	evScene(4,15,15);
	evFrameWait(1000);
	mes.OpenMessage("Fillgalt.msg",102);
	mes.ReadDraw();
	evFrameWait(1000);


	//---���ꂩ��̂́E�E�E
	crfieldChangeScene(0,8,8);
	npPos(0,7,8);
	npDir(0,WEST);
	npPos(1,4,9);
	npDir(1,NORTH);
	npShow(2,0);
	npPos(2,13,5);
	npDir(2,WEST);
	evScene(0,8,8);

	evFrameWait(500);
	npMove(2,-1,0);
	evFrame();
	evFrameWait(250);

	for(a = 0;a < 5;a ++){
		npMove(2,-1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(2,SOUTH);
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
	evFrameWait(250);

//---���i��
	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---�r��
	crfieldChangeMap(72,0,1,0);
	for(a = 0;a <= 39;a ++){
		npDir(a,SOUTH);
	}
	for(a = 40;a <= 69;a ++){
		npDir(a,NORTH);
	}
	evScene(0,13,25);
	evFrameWait(1000);
	for(a = 0;a < 14;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(1000);

	//----------------------------------------------------
	//---�o�g��
	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = 0;
	BattleInfo.Enemy[0].Enemy = 140;
	BattleInfo.Enemy[0].x = 4;
	BattleInfo.Enemy[0].y = 6;
	BattleInfo.Enemy[1].Enemy = 141;
	BattleInfo.Enemy[1].x = 6;
	BattleInfo.Enemy[1].y = 7;
	BattleInfo.Enemy[2].Enemy = 140;
	BattleInfo.Enemy[2].x = 8;
	BattleInfo.Enemy[2].y = 6;
	BattleInfo.Enemy[3].Enemy = 141;
	BattleInfo.Enemy[3].x = 4;
	BattleInfo.Enemy[3].y = 8;
	BattleInfo.Enemy[4].Enemy = 141;
	BattleInfo.Enemy[4].x = 4;
	BattleInfo.Enemy[4].y = 10;
	BattleInfo.Enemy[5].Enemy = 140;
	BattleInfo.Enemy[5].x = 8;
	BattleInfo.Enemy[5].y = 8;
	BattleInfo.Enemy[6].Enemy = 141;
	BattleInfo.Enemy[6].x = 8;
	BattleInfo.Enemy[6].y = 10;
	BattleInfo.Enemy[7].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_NORMAL;
	BattleInfo.lpTurnCallBack = cresbatCallBack2;
	BattleInfo.DontShowAfterBattle = 1;
	BattleInfo.MapNumber = 10;
	BattleInfo.SceneNumber = 0;
	BattleInfo.AreaNumber = 8;
	crbatSetShowStatus(0);
	prtRecoveryAll();

	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
	}
	et->Delay2(1000);
	crhistSubBattleCount();
	//----------------------------------------------------

	//----------------------------------------------------
	//---�o�g��
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = 0;
	BattleInfo.Enemy[0].Enemy = 140;
	BattleInfo.Enemy[0].x = 4;
	BattleInfo.Enemy[0].y = 6;
	BattleInfo.Enemy[1].Enemy = 141;
	BattleInfo.Enemy[1].x = 6;
	BattleInfo.Enemy[1].y = 7;
	BattleInfo.Enemy[2].Enemy = 140;
	BattleInfo.Enemy[2].x = 8;
	BattleInfo.Enemy[2].y = 6;
	BattleInfo.Enemy[3].Enemy = 140;
	BattleInfo.Enemy[3].x = 4;
	BattleInfo.Enemy[3].y = 8;
	BattleInfo.Enemy[4].Enemy = 140;
	BattleInfo.Enemy[4].x = 4;
	BattleInfo.Enemy[4].y = 10;
	BattleInfo.Enemy[5].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_NONE;
	BattleInfo.lpTurnCallBack = cresbatCallBack3;
	BattleInfo.DontShowAfterBattle = 1;
	BattleInfo.MapNumber = 10;
	BattleInfo.SceneNumber = 0;
	BattleInfo.AreaNumber = 8;
	crbatSetShowStatus(0);
	prtRecoveryAll();

	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
	}
	et->Delay2(1000);
	crhistSubBattleCount();
	//----------------------------------------------------
	
	//---�N���X�e�B�[���o�g���I��
	crbatSetShowStatus(1);

	//---�傫�Ȍ�
	crfieldChangeMap(73,0,1,0);
	evScene(0,32,0);
	for(a = 0;a < 24;a ++){
		mcMove(0,1);
		evFrame();
	}
	evScene(1,10,7);
	for(a = 0;a < 36;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(1000);
	//---�������I
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	evFadeOut(2000);

//---���i��
	crfieldChangeMap(71,4,1,0);
	evFieldNoFlip(0,1);
//	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---�Ȃ񂾂ƁI�H
	crfieldChangeScene(0,7,10);
	npPos(0,7,8);
	npDir(0,NORTH);
	npPos(1,8,8);
	npDir(1,NORTH);
	npPos(2,8,6);
	npDir(2,SOUTH);
	evScene(0,7,9);

	evFrameWait(500);
	mes.ReadDraw(2);

	//---���߂�
	evFrameWait(500);
	mes.ReadDraw();

	//---�ǂ��������ƂȂ�
	evFrameWait(250);
	npMove(1,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(2);

	//---�킩��Ȃ�
	evFrameWait(500);
	mes.ReadDraw(3);

	//---�N���C�V������
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---���́E�E�E
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

//---���i��
	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---����
	crfieldChangeMap(70,10,1,0);
	npPos(0,13,3);
	npDir(0,NORTH);
	npDir(1,NORTH);
	crfieldChangeScene(10,13,6);
	evFieldNoFlip(0,1);
	evFadeIn(2000,RGB_MAKE(255,255,255));
//	evScene(10,13,6);

	evFrameWait(1000);

	//---�v���o�������H
	for(a = 0;a < 4;a ++){
		npMove(1,0,-1);
		evFrame();
		evFrameWait(500);
	}
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(0,WEST);
	evFrameWait(500);
	npDir(0,SOUTH);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---�Ă�
	evFadeOut(2000,RGB_MAKE(255,255,255));

	crfieldChangeMap(71,0,1,0);
	evFieldNoFlip(0,1);

	//---�Ȃ񂾂ƁI�H
	crfieldChangeScene(0,7,9);
	npPos(0,7,8);
	npDir(0,NORTH);
	npPos(1,8,7);
	npDir(1,NORTH);
	npPos(2,8,6);
	npDir(2,SOUTH);
	evFieldNoFlip(0,1);
	evFadeIn(2000,RGB_MAKE(255,255,255));

	evFrameWait(500);
	mes.ReadDraw(3);
	//---�킽��
	evFrameWait(500);
	npMove(0,0,-1);
	evFrame();
	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	//---�S�z�Ȃ�
	npDir(1,WEST);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	mes.ReadDraw(3);

	//---���͂���ł���
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

//---���i��
	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---���f�̐X
	crfieldChangeMap(35,5,1,0);
	evScene(5,9,11);
	
	evFrameWait(500);
	npDir(3,EAST);
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	npDir(3,NORTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---�N���C�V������
	npMove(3,0,-1);
	evFrame();
	npDir(0,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---�S�z�����
	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(100);
	npMove(3,1,0);
	evFrame();
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---����ł����́H
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	npDir(3,WEST);
	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(250);
	for(a = 0;a < 6;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(1000);

//---���i��
	evScene(6,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---����
	crfieldChangeMap(70,10,1,0);
	npPos(0,13,3);
	npDir(0,SOUTH);
	npPos(1,13,6);
	npDir(1,NORTH);
	crfieldChangeScene(10,13,6);
	evFieldNoFlip(0,1);
	evFadeIn(2000,RGB_MAKE(255,255,255));
//	evScene(10,13,6);

	evFrameWait(1000);

	mes.ReadDraw();
	//---����ȊO��
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(3);

	//---�V����
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---�ۑ����u
	evFadeOut(2000,RGB_MAKE(255,255,255));
	crfieldChangeMap(35,6,1,0);
	crfieldChangeScene(6,15,15);
	evFieldNoFlip(0,1);
	evFadeIn(2000,RGB_MAKE(255,255,255));

	evFrameWait(1000);
	mes.ReadDraw(2);
	crmusicFadeOut();
	evFrameWait(3500);
	mes.ReadDraw();
	evFrameWait(1000);
	crmusicPlay(CRMUSIC_SILENT);
	evFadeOut();

	//---�ڊo��
	crfieldChangeScene(4,9,4);

	em->Put(9,6,2,17);
	evReadObject(1,"LunarnFSlp.acf");
	npPos(0,10,2);
	npDir(0,NORTH);
	evFieldNoFlip(0,1);
	evFadeIn();

	evFrameWait(500);
	npDir(0,EAST);
	evFrameWait(500);
	npDir(0,NORTH);
	evFrameWait(100);
	npDir(0,EAST);
	evFrameWait(100);
	npDir(0,NORTH);
	evFrameWait(100);
	npDir(0,EAST);
	evFrameWait(500);

	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	//---�N���C�V���I
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(250);

	//---�ق���H
	evFrameWait(100);
	npDir(0,NORTH);
	evFrameWait(100);
	npDir(0,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

//---���i��
	evScene(6,15,15);	
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---�L��
	crfieldChangeScene(4,9,4);
	npPos(0,9,2);
	npDir(0,SOUTH);
	em->Put(9,6,2,17);
	evReadObject(1,"LunarnF.acf");

	evFieldNoFlip(0,1);
	evFadeIn();

	//---���i������
	evFrameWait(500);
	for(a = 0;a < 3;a ++){
		npMove(0,0,1);
		evFrame();
	}
	evFrameWait(500);
	em->Put(9,6,2,1024);
	crsoundPlay(CRSOUND_ATACK4);
	evFrameWait(500);

	for(a = 0;a < 10;a ++){
		mcMove(0,1);
		evFrame();
	}
	for(a = 0;a < 9;a ++){
		npMove(0,0,1);
		evFrame();
	}
	evFrameWait(500);
	npDir(0,WEST);
	evFrameWait(1000);
	npDir(0,SOUTH);
	evFrameWait(500);
	npDir(0,EAST);
	evFrameWait(1000);
	npDir(0,SOUTH);
	evFrameWait(500);
	//---�N�����Ȃ�
	mes.ReadDraw();
	evFrameWait(500);

	mcShow(1);
	npPos(0,0,0);
	npShow(0,0);
	evSet(166,1);

	mcDir(SOUTH);
//	evScene(4,9,14);

	crmusicPlay(CRMUSIC_OPENING);

	mes.CloseMessage();

	return 1;
}

//---�L���̒��A�K�[�[���Ƃ̏o�
CREVENTLONG4_API int creventKiokunoNaka_Gazell(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	crmusicFadeOut();

	npPos(0,15,44);
	npDir(0,SOUTH);
	npPos(1,14,51);
	npDir(1,NORTH);

	for(a = 0;a < 5;a ++){
		mcMove(0,1);
		evFrame();
	}
	npMove(1,0,-1);
	evFrame();

	evFrameWait(500);
	mes.OpenMessage("Fillgalt.msg",107);
	mes.ReadDraw(2);

//---���i��
	evFrameWait(500);
	evScene(4,15,15);
	evFrameWait(500);
	crmusicPlay(CRMUSIC_TITLE);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	evScene(3,15,49);

	//---���q���H
	evFrameWait(500);
	npDir(1,EAST);
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(1,1,0);
		else
			npMove(1,0,-1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
//	crmusicPlay(CRMUSIC_SILENT);
	mes.ReadDraw(2);

	//---����
	evFrameWait(500);
	mes.ReadDraw(3);

	//---�킽����
	evFrameWait(500);
	npMove(0,0,1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(3);

	evFrameWait(100);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

	//---�N���X�t�B�[���h��
	crfieldChangeMap(32,6,1,0);
//---���i��
	evScene(6,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	crfieldChangeScene(5,4,9);
	npPos(0,5,7);
	npDir(0,WEST);
	npPos(1,3,7);
	npDir(1,EAST);
	evReadObject(7,"Gazell.acf");
	evReadObject(12,"LunarnF.acf");

	evScene(5,4,9);
	evFrameWait(500);
	mes.ReadDraw();
	//---�ꂢ
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---���m��
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw(3);
	//---�t�B���K���g�H
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw();

	//---��N�E�E�E
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

//---���i��
	evScene(6,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	evScene(5,4,9);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();

	//---���O�́H
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(250);

//---���i��
	evScene(6,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	evScene(5,4,9);
	//---�����Ȃ���
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);


//---���i��
	evScene(6,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	evScene(5,4,9);
	//---�͂�����������E�E�E
	evFrameWait(1000);
	mes.ReadDraw(3);

	//---���ꂩ��
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

//---���i��
	evScene(6,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---���R��
	evScene(5,4,9);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

//---���i��
	evScene(6,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	evScene(5,4,9);
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(1000);
	//---�킽����
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);

	//---���i���ړ�
	for(a = 0;a < 3;a ++){
		if(a < 1)
			npMove(0,0,1);
		else
			npMove(0,-1,0);
		evFrame();
	}
	npDir(1,SOUTH);
	evFrameWait(150);
	npDir(0,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

//---���i��
	evScene(6,15,15);
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(1000);

	evScene(5,4,9);
	//---�Q������
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(1000);
	mes.ReadDraw(3);
	evFrameWait(500);

	//---�ł����̂܂܂ł�
	npDir(0,EAST);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	npDir(0,EAST);
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---���܂ł̋L�����E�E�E
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

//---���i��
	evScene(6,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);


	crfieldChangeScene(5,6,9);
	npPos(0,6,7);
	npDir(0,SOUTH);
	npPos(1,6,8);
	npDir(1,NORTH);
	evReadObject(12,"LunarnF2.acf");
	evScene(5,6,9);
	evFrameWait(1000);
	npDir(0,EAST);
	evFrameWait(500);
	npDir(0,SOUTH);
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(500);
	npDir(0,SOUTH);
	evFrameWait(500);

	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---�Q��
	npPos(0,13,9);
	npDir(0,WEST);
	npPos(1,12,9);
	npDir(1,EAST);
	evScene(5,12,11);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);
	//---���O
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---���i��
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

//---���i��
	evScene(6,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---�N���X�t�B�[���h
	crfieldChangeScene(5,12,11);
	npPos(0,14,9);
	npDir(0,SOUTH);
	npPos(1,13,9);
	npDir(1,EAST);
	evReadObject(7,"Gazell.acf");
	evReadObject(12,"LunarnSlp4.acf");
	evScene(5,12,11);

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
	crmusicFadeOut();
	evFadeOut(2000,RGB_MAKE(255,255,255));

	//---������
	crfieldChangeMap(70,10,1,0);
	npPos(0,13,3);
	npDir(0,SOUTH);
	npPos(1,13,6);
	npDir(1,NORTH);
	crfieldChangeScene(10,13,6);
	evFieldNoFlip();
	evFadeIn(2000,RGB_MAKE(255,255,255));

	crmusicPlay(CRMUSIC_INIT);
	evFrameWait(1000);

	mes.ReadDraw();
	//---�N���C�V���Ȃ́H
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	crmusicPlay(CRMUSIC_SILENT);

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---�N���X�e�B�[����
	evFrameWait(1000);
	npMove(1,0,-1);
	evFrame();
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	//---���肵
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1500);

	//---���_�̂̐�
	{
		mes.CreateNewMessage(0,160,144,20,4,1);
		mes.OpenMessage("Fillgalt.msg",108);
		mes.ReadDraw(1);

		evFrameWait(1000);
		mes.Paint();
		mes.ReadDraw(1);

		evFrameWait(1000);
		mes.Paint();
		mes.ReadDraw(1);
		evFrameWait(1000);
		mes.CloseMessage();
	}

	mes.OpenMessage("Fillgalt.msg",109);
	//---�͂��H
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(500);
	npDir(0,SOUTH);
	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(500);
	npDir(0,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npPos(3,25,4);
	npDir(3,NORTH);
	npPos(4,26,4);
	npDir(4,EAST);
	for(a = 0;a < 30;a ++){
		npMove(3,-1,0,0);
		npMove(4,-1,0,0);
		evFrame();
	}
	npPos(3,25,4);
	npDir(3,NORTH);
	npPos(4,26,4);
	npDir(4,EAST);
	for(a = 0;a < 30;a ++){
		npMove(3,-1,0,0);
		npMove(4,-1,0,0);
		evFrame();
	}

	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);

	npDir(0,WEST);
	evFrameWait(100);
	for(a = 0;a < 7;a ++){
		if(a < 1)
			npMove(0,-1,0);
		else if(a < 5)
			npMove(0,0,1);
		else if(a < 6)
			npMove(0,1,0);
		else
			npMove(0,0,1);
		evFrame();
	}
	//---�U��Ԃ�
	evFrameWait(500);
	npDir(0,EAST);
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(500);
	npDir(0,EAST);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(100);
	for(a = 0;a < 10;a ++){
		npMove(0,0,1);
		evFrame();
	}

	//---��������̐��_��
	int flag[20];
	for(a = 3,b = 3;a < 17;a += 2,b ++){
		c = eiRnd(12);
		if(a < 13){
			npPos(a,23 + c,b);
			npDir(a,NORTH);
			npPos(a + 1,23 + c + 1,b);
			npDir(a + 1,EAST);
			flag[a] = 0;
		} else {
			npPos(a,0 - c,b);
			npDir(a,WEST);
			npPos(a + 1,0 - c + 1,b);
			npDir(a + 1,SOUTH);
			flag[a] = 1;
		}
	}

	for(a = 0;a < 120;a ++){
		for(b = 3;b < 17;b += 2){
			if(flag[b] == 0){
				npMove(b,-1,0,0);
				npMove(b + 1,-1,0,0);
				if(npGet(b)->xGet() + eiRnd(6) < 0){
					npDir(b,WEST);
					npDir(b + 1,SOUTH);
					flag[b] = 1;
				}
			} else {
				npMove(b,1,0,0);
				npMove(b + 1,1,0,0);
				if(npGet(b)->xGet() + eiRnd(6) > 25){
					npDir(b,NORTH);
					npDir(b + 1,EAST);
					flag[b] = 0;
				}
			}
		}
		evFrame();
	}

	//---�����o�[�g�ݑւ�
	{
		pPartyInfo->PartyMember[0] = 0;
		pPartyInfo->PartyMember[1] = 1;
		pPartyInfo->PartyMember[2] = -1;
		pPartyInfo->PartyMember[3] = -1;
		pPartyInfo->PartyMember[4] = -1;
/*		pPartyInfo->PartyMember[2] = 2;
		pPartyInfo->PartyMember[3] = 3;
		pPartyInfo->PartyMember[4] = 4;
		crcharaLoadFace(-1);*/
		for(a = 0;a < 2;a ++){
			crcharaCheckBattleFieldPos(a);
		}
		crcharaLoadFace(-1);
	}

	crfieldChangeScene(9,12,4);
	npPos(0,12,12);
	npDir(0,SOUTH);
	npPos(1,12,3);
	npDir(1,SOUTH);
	evScene(9,12,4);

	evFrameWait(500);
	crmusicPlay(CRMUSIC_HEAT);
	evFrameWait(500);
	for(a = 0;a < 7;a ++){
		npMove(0,0,-1);
		evFrame();
	}
	//---���i���I
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(250);
	for(a = 0;a < 1;a ++){
		npMove(0,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(5);

	//---���_�̂�
	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);

	npPos(2,11,18);
	npDir(2,EAST);
	npPos(3,13,19);
	npDir(3,WEST);
	for(a = 0;a < 10;a ++){
		mcMove(0,1);
		evFrame();
	}
	for(a = 0;a < 3;a ++){
		npMove(2,1,0);
		npMove(3,-1,0);
		evFrame();
	}
//	evFrameWait(1000);
	for(a = 0;a < 10;a ++){
		mcMove(0,-1);
		evFrame();
	}
	npPos(2,0,0);
	npShow(2,0);
	npPos(3,0,0);
	npShow(3,0);

	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	npPos(0,0,0);
	npShow(0,0);
	npPos(1,0,0);
	npShow(1,0);
	mcDir(SOUTH);
	mcShow(1);
	crfieldSetMainCharacter(1);
	evScene(9,12,3);
	evSet(EV_MENU_MODE,0);

	mes.CloseMessage();

	return 1;
}

CREVENTLONG5_API int crevent_ThirdStart(void);

//---�L���̈�ՁA�E�o�I�I
CREVENTLONG4_API int creventKiokunoIseki_Dasshutu(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	//9,6   22,4
	crfieldChangeScene(7,9,7);
	npPos(1,21,4);
	npDir(1,WEST);
	npPos(2,22,4);
	npDir(2,WEST);
	npPos(3,9,6);
	npDir(3,SOUTH);
	em->Put(13,4,2,1024);
	em->Put(13,3,2,53);
	evScene(7,9,7);

	evFrameWait(500);
	for(a = 0;a < 10;a ++){
		npMove(1,-1,0);
		npMove(2,-1,0);
		if(a == 8)
			npDir(3,EAST);
		evFrame();
	}
	evFrameWait(250);
	mes.OpenMessage("Fillgalt.msg",110);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---���C�[���B
	evScene(0,8,17);
	npPos(0,8,6);
	npDir(0,SOUTH);
	npPos(1,8,5);
	npDir(1,SOUTH);
	npPos(2,8,4);
	npDir(2,SOUTH);
	npPos(3,8,3);
	npDir(3,SOUTH);

	for(a = 0;a < 9;a ++){
		npMove(0,0,1);
		npMove(1,0,1);
		npMove(2,0,1);
		npMove(3,0,1);
		if(a == 5)
			npDir(5,NORTH);
		if(a == 6)
			npDir(4,NORTH);
		evFrame();
	}
	for(a = 0;a < 4;a ++){
		if(a < 2)
			npMove(1,-1,0);
		else if(a < 3)
			npMove(1,0,1);

		if(a < 1)
			npMove(2,0,1);
		else if(a < 2)
			npMove(2,1,0);
		else
			npDir(2,SOUTH);
		if(a < 2){
		} else if(a < 4)
			npMove(3,0,1);

		if(a > 2)
			npMove(5,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(2);
	//---�f�r�܂ő����I
	evFrameWait(250);
	npMove(0,0,1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);

	//---���������܂�
	npDir(3,EAST);
	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	for(a = 0;a < 12;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(250);

	//---���_��
	int flag[20],flag2[20];
	for(a = 7,b = 4;a < 11;a += 2,b ++){
		c = eiRnd(12);
		flag2[a] = 0;
		if(a < 8){
			npPos(a,23 + c,b);
			npDir(a,NORTH);
			npPos(a + 1,23 + c + 1,b);
			npDir(a + 1,EAST);
			flag[a] = 0;
		} else {
			npPos(a,0 - c,b);
			npDir(a,WEST);
			npPos(a + 1,0 - c + 1,b);
			npDir(a + 1,SOUTH);
			flag[a] = 1;
		}
	}

	for(a = 0;a < 60;a ++){
		for(b = 7;b < 11;b += 2){
			if(flag2[b] >= 2)
				continue;

			if(flag[b] == 0){
				npMove(b,-1,0,0);
				npMove(b + 1,-1,0,0);
				if(npGet(b)->xGet() + eiRnd(6) < 0){
					npDir(b,WEST);
					npDir(b + 1,SOUTH);
					flag[b] = 1;
					flag2[b] ++;
				}
			} else {
				npMove(b,1,0,0);
				npMove(b + 1,1,0,0);
				if(npGet(b)->xGet() + eiRnd(6) > 25){
					npDir(b,NORTH);
					npDir(b + 1,EAST);
					flag[b] = 0;
					flag2[b] ++;
				}
			}
		}
		evFrame();
	}
	for(a = 0;a < 12;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(250);

	mes.ReadDraw();
	evFrameWait(250);

	//---�f�r
	crfieldChangeMap(59,1,1,0);
	crfieldChangeScene(1,6,7);
	npPos(0,8,5);
	npDir(0,EAST);
	npPos(1,8,8);
	npDir(1,EAST);
	npPos(2,4,4);
	npDir(2,SOUTH);
	npPos(3,9,4);
	npDir(3,EAST);
	npPos(4,9,3);
	npDir(4,EAST);
	npPos(5,4,5);
	npDir(5,EAST);
	em->Put(10,3,2,26);
	evScene(1,6,7);
	crsoundPlay(CRSOUND_GS_SOUND,EISOUND_PLAYLOOP);
	//---

	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.CloseMessage();

	//---���_�̂̐�
	{
		mes.CreateNewMessage(0,160,144,20,4,1);
		mes.OpenMessage("Fillgalt.msg",111);
		mes.ReadDraw(1);

		evFrameWait(1000);
		mes.Paint();
		mes.ReadDraw(1);
		evFrameWait(1000);
		mes.CloseMessage();
	}

	evFrameWait(500);
	npDir(0,SOUTH);
	evFrameWait(250);
	mes.OpenMessage("Fillgalt.msg",112);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---���������
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	em->Put(10,3,2,27);
	evFrameWait(500);
	crsoundStop(CRSOUND_GS_SOUND,0);
	crsoundPlay(CRSOUND_GS_FUMISUGI2,EISOUND_PLAYLOOP);
	evFrameWait(1000);


	npPos(0,8,5);
	npDir(0,EAST);
	npPos(1,11,8);
	npShow(1,0);
	npPos(2,4,4);
	npDir(2,SOUTH);
	npPos(3,9,4);
	npDir(3,EAST);
	npPos(4,9,3);
	npDir(4,EAST);
	npPos(5,3,6);
	npDir(5,EAST);
	em->Put(10,3,2,26);

	evFadeOut();
	evFill(0);
	et->Delay2(1000);
	crmusicFadeOut();
	et->Delay2(3000);
	crsoundStop(CRSOUND_GS_FUMISUGI2,0);
	crsoundPlay(CRSOUND_GS_SOUND,EISOUND_PLAYLOOP);
	et->Delay2(1000);
	crmusicPlay(CRMUSIC_SILENT);
	evScene(1,6,7);

	evFrameWait(3000);
	for(a = 0;a < 7;a ++){
		if(a < 5)
			npMove(1,-1,0);
		else
			npMove(1,0,-1);
		evFrame();
	}
	//---�Ȃ�Ƃ�
	for(a = 0;a < 2;a ++){
		npMove(2,1,0);
		evFrame();
	}
	evFrameWait(150);
	npDir(2,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();

	//---�݂�ȁE�E�E
	evFrameWait(1000);
	npDir(0,SOUTH);
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(2,EAST);
	evFrameWait(125);
	npDir(1,EAST);
	evFrameWait(125);
	npDir(4,SOUTH);
	evFrameWait(125);
	npDir(5,EAST);
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---��񕔏I���t���b�O
	evSet(160,1);
/*	{
		//---test
		mes.ReadDraw();
		while(1){
			if(crmainMainMenu(0) >= MAINLOOP_ENDLOOP)
				return MAINLOOP_ENDLOOP;
		}
	}*/

	return crevent_ThirdStart();
//	return 1;
}
