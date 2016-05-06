/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrEventLong9.cpp ...Event functions

-----------------------------------------------------------*/


#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CREVENTLONG9

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

CREVENTLONG9_API int crevent_WescaLuxthereVS(void);
CREVENTLONG9_API int crevent_WescaLuxthereSleepAfter(void);
CREVENTLONG9_API int crevent_WescaLuxthereVS(void);
CREVENTLONG9_API int crevent_AlsiaHashiObachanYubiwa(void);


CREVENTLONG9_API int crevent_dumy4(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	return 1;
}

//---�E�F�X�J�̖S��A�͂��߂ĖK�ꂽ
CREVENTLONG9_API int crevent_WescaLuxthereFirstVisit(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcDir(NORTH);
	crfieldChangeMap(14,0,1,1);
	npPos(38,44,55);
	npDir(38,EAST);
	npPos(39,45,55);
	npDir(39,WEST);
	evScene(0,44,58);

	evFrameWait(500);
	mes.OpenMessage("Wesca.msg",104);
	mes.ReadDraw(3);
	//---��l�A��������
	evFrameWait(250);
	npDir(38,NORTH);
	evFrameWait(500);
	for(a = 0;a < 12;a ++){
		npMove(38,0,-1);
		if(a < 1)
			npDir(39,NORTH);
		else if(a < 2)
			npDir(39,NORTH);
		else
			npMove(39,0,-1);
		evFrame();
	}
	npDelete(38);
	npDelete(39);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	mes.CloseMessage();

	evSet(231,1);

	return 1;
}

//---�E�F�X�J�̖S��A�ŏ��̏h
CREVENTLONG9_API int crevent_WescaLuxthereFirstSleep(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	evField(0,1);
	mes.OpenMessage("Wesca.msg",105);
	mes.ReadDraw(2);
	mes.CloseMessage();

	if(evYado(5,0,0,NULL,1) == 0){
		//---���܂����I
		mcShow(0);

		crmusicFadeOut();
		evFadeOut(1000);
		et->Delay2(2000);
		crfieldChangeScene(2,15,16);
		evFieldNoFlip(0,1);
		evFadeIn(1000);
		crmusicPlay(CRMUSIC_SILENT);

		evFrameWait(2000);
		npMove(0,0,1);
		evFrame();
		evFrameWait(1000);
		npDir(0,EAST);
		evFrameWait(1000);
		npDir(0,SOUTH);
		evFrameWait(250);
		npDir(0,WEST);
		evFrameWait(1000);
		npDir(0,SOUTH);
		evFrameWait(500);

		mes.OpenMessage("Wesca.msg",106);
		mes.ReadDraw();
		//---�ǂ������
		evFrameWait(2000);
		mes.ReadDraw();
		evFrameWait(2000);

		evFadeOut(1000);
		et->Delay2(2000);
		crfieldChangeScene(0,32,49);

		npPos(7,37,45);
		npDir(7,SOUTH);

		npPos(36,31,48);
		npDir(36,SOUTH);
		npPos(33,32,46);
		npDir(33,WEST);
		npPos(34,33,47);
		npDir(34,WEST);
		evReadObject(12,"Nack.acf");
		evReadObject(13,"Xavier.acf");

		evFieldNoFlip(0,1);
		evReloadMapMusic();
		evFadeIn(1000);

		evFrameWait(1000);
		npPos(35,28,53);
		npDir(35,EAST);
		for(a = 0;a < 6;a ++){
			if(a < 3)
				npMove(35,1,0);
			else
				npMove(35,0,-1);
			if(a == 3)
				npDir(33,SOUTH);
			if(a == 5)
				npDir(34,SOUTH);
			evFrame();
		}
		//---�悤�₭
		evFrameWait(250);
		mes.ReadDraw();

		evFrameWait(500);
		mes.ReadDraw(2);
		evFrameWait(250);
		//---��������
		npMove(33,0,1);
		evFrame();
		evFrameWait(250);
		mes.ReadDraw();
		evFrameWait(250);
		npDir(33,EAST);
		evFrameWait(250);
		mes.ReadDraw(2);
		evFrameWait(500);

		//---�������݂��񂾂��ǁE�E�E
		mes.ReadDraw(2);
		evFrameWait(500);

		mes.CloseMessage();

		prtRecoveryAll();
		CrCharacter *pChara;
		for(a = 0;a < MEMBER_MAX;a ++){
			pChara = crcharaGetPartyMember(a);
			if(pChara != NULL){
				pChara->SetLP(pChara->GetMaxLP() / 2);
				pChara->SetMC(pChara->GetMaxMC() / 2);
			}
		}

		npDelete(33);
		npDelete(34);
		npDelete(35);
		npDelete(36);

		mcShow(1);
		mcDir(SOUTH);
		evScene(0,34,49);

		evSet(232,1);
	}

	return 1;
}

//---�E�F�X�J�̖S��A�Ό�
CREVENTLONG9_API int crevent_WescaLuxthereSleep(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	evField(0,1);

	if(evYado(5,0,0,NULL,1) == 0){
		mcShow(0);

		crmusicFadeOut();
		evFadeOut(1000);
		et->Delay2(2000);
		crfieldChangeScene(3,15,15);
		evFieldNoFlip(0,1);
		evFadeIn();
		crmusicPlay(CRMUSIC_SILENT);
		evFrameWait(250);

		//---�Ό��Q��ڈȍ~
		if(evGet(232) >= 3)
			return crevent_WescaLuxthereSleepAfter();

		mes.OpenMessage("Wesca.msg",107);
		mes.ReadDraw();
		mes.CloseMessage();

		evFrameWait(1000);

		int sel;
		CrSelectWindow win;
		win.Create(64,64,16,7,"�g�E�E�E�g�}�g�E�E�E","���[;���ҁ[;��ɂ�;");
		do {
			win.Paint();
			win.Refresh();
			sel = win.Select();
		} while(sel == -1);
		
		evFrameWait(1000);

		if(sel <= 1){
			mes.OpenMessage("Wesca.msg",113 + sel);
			mes.ReadDraw();
			mes.CloseMessage();

			//---��
			evFrameWait(1000);

			mcShow(1);
			mcDir(WEST);
			evScene(0,31,46);
			evReloadMapMusic();
			evFrameWait(250);
			mes.FileMessage("Wesca.msg",115);
			evFrameWait(250);

			prtRecoveryAll();
			CrCharacter *pChara;
			for(a = 0;a < MEMBER_MAX;a ++){
				pChara = crcharaGetPartyMember(a);
				if(pChara != NULL){
					pChara->SetLP(pChara->GetMaxLP() / 2);
					pChara->SetMC(pChara->GetMaxMC() / 2);
				}
			}
			return 1;
		}

		//---�ڂ��o�߂�I
		crfieldChangeScene(1,11,6);
		evReadObject(14,"LunarnSlp5.acf");
		evReadObject(15,"DizzaSlp.acf");
		evReadObject(12,"NackSlp.acf");
		evReadObject(13,"XavierSlp.acf");
		crfieldPaletteChange(PALETTE_NIGHT);
		npDelete(0);
		npPos(1,11,2);
		npDir(1,EAST);
		npPos(2,11,8);
		npDir(2,EAST);
		npPos(5,11,9);
		npDir(5,EAST);
		npPos(3,12,2);
		npDir(3,EAST);
		npPos(6,12,3);
		npDir(6,EAST);
		npPos(4,12,8);
		npDir(4,EAST);
		npPos(7,12,9);
		npDir(7,EAST);

		evScene(1,11,6);

		//---���i���A�ڂ��o�܂�
		evFrameWait(1000);
		mes.OpenMessage("Wesca.msg",108);
		mes.ReadDraw();
		evFrameWait(500);
		npDir(1,NORTH);
		evFrameWait(500);
		mes.ReadDraw();
		evFrameWait(1000);
		mes.ReadDraw();
		evFrameWait(500);

		//---���i��
		evReadObject(14,"Lunan.acf");
		em->ReloadPattern();
		crfieldPaletteChange(PALETTE_NIGHT);
		evFrameWait(500);

//		npPos(1,10,2);
//		npDir(1,SOUTH);
		npDelete(1);

		evSet(232,2);//�Q���̂Q���
		//---
		evSet(234,1);//---��
		evSet(EV_MENU_MODE,2);
		//---���ԊO��
		pPartyInfo->PartyMember[1] = -1;
		pPartyInfo->PartyMember[2] = -1;
		pPartyInfo->PartyMember[3] = -1;

		em->ReloadPattern();
		crfieldPaletteChange(PALETTE_NIGHT);
		for(a = 0;a < 8;a ++){
			crfieldPaletteChange_Cell(&pMainCharacterCell[a],PALETTE_NIGHT);
		}
		crfieldSetMainCharacterSurface();

		mcShow(1);
		mcDir(SOUTH);
		evScene(1,10,2);

		return 1;
	}

	return 1;
}

//---�Q��̂R��ڈȍ~
CREVENTLONG9_API int crevent_WescaLuxthereSleepAfter(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

		crfieldChangeScene(1,11,6);
		evReadObject(14,"LunarnSlp5.acf");
		evReadObject(15,"DizzaSlp.acf");
		evReadObject(12,"NackSlp.acf");
		evReadObject(13,"XavierSlp.acf");
		crfieldPaletteChange(PALETTE_NIGHT);
		npDelete(0);
		npPos(1,11,2);
		npDir(1,EAST);
		npPos(2,11,8);
		npDir(2,EAST);
		npPos(5,11,9);
		npDir(5,EAST);
		npPos(3,12,2);
		npDir(3,EAST);
		npPos(6,12,3);
		npDir(6,EAST);
		npPos(4,12,8);
		npDir(4,EAST);
		npPos(7,12,9);
		npDir(7,EAST);

		evScene(1,11,6);
	evFrameWait(500);
	npDir(1,NORTH);
	evFrameWait(500);

	mes.OpenMessage("Wesca.msg",112);
	mes.ReadDraw();
	//---�������I�I
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	npPos(8,3,4);
	npDir(8,NORTH);
	npPos(1,3,7);
	npDir(1,NORTH);
	evReadObject(14,"Lunarn.acf");
	evReadObject(11,"Luxthere.acf");
	em->ReloadPattern();
	crfieldPaletteChange(PALETTE_NIGHT);
	evScene(1,3,7);
	evFrameWait(500);

	mes.ReadDraw();
	evFrameWait(250);

	mes.CloseMessage();

	return crevent_WescaLuxthereVS();
}

//---�E�F�X�J�̖S��A�Ό�
CREVENTLONG9_API int crevent_WescaLuxthereVS(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	//---���ԊO��
	pPartyInfo->PartyMember[1] = -1;
	pPartyInfo->PartyMember[2] = -1;
	pPartyInfo->PartyMember[3] = -1;

	if(evGet(232) <= 2){
		//---�ŏ��I
		npPos(1,3,9);
		npDir(1,WEST);
		mcShow(0);

		evReadObject(14,"Lunarn.acf");
		evReadObject(11,"Luxthere.acf");
		em->ReloadPattern();
		crfieldPaletteChange(PALETTE_NIGHT);

		mes.OpenMessage("Wesca.msg",109);
		mes.ReadDraw();
		//---���I�H
		evFrameWait(250);
		npDir(1,NORTH);
		evFrameWait(250);
		npDir(1,EAST);
		evFrameWait(250);
		mes.ReadDraw();

		evFrameWait(500);
		mes.ReadDraw();
		evFrameWait(500);
		mes.ReadDraw();
		//---�ł��݂�ȁE�E�E
		evFrameWait(1000);
		mes.ReadDraw();

		//---�C�z�I
		evFrameWait(250);
		npDir(1,NORTH);
		evFrameWait(250);
		mes.ReadDraw();
		evFrameWait(250);

		for(a = 0;a < 2;a ++){
			npMove(1,0,-1);
			evFrame();
		}
		evFrameWait(500);
		mes.ReadDraw();
		evFrameWait(500);
		for(a = 0;a < 2;a ++){
			mcMove(0,-1);
			evFrame();
		}
		evFrameWait(500);

		//---�䂪�����
		mes.ReadDraw();
		evFrameWait(500);

		//---���N�X�[�A
		npPos(8,3,0);
		npDir(8,NORTH);
		evFrameWait(500);
		for(a = 0;a < 4;a ++){
			npMove(8,0,1,0);
			evFrame();
		}
		//---���Ȃ�
		evFrameWait(500);
		mes.ReadDraw();

		evFrameWait(1000);
		mes.ReadDraw(2);

		//---�����E�E�E
		evFrameWait(1000);
		mes.ReadDraw(2);
		evFrameWait(1000);
		mes.ReadDraw();
		evFrameWait(250);

		mes.CloseMessage();
	}

	//---�悱���I�I
	eiMapObject *ob = npGet(8);
	ob->Data.MoveSpeed = 2;
	for(a = 0;a < 1;a ++){
		npMove(8,0,1,0);
		evFrame();
	}
	ob->Data.MoveSpeed = 1;
	evFrameWait(50);

	//---�o�g���I�I
	//---�o�g��
	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = CRMUSIC_BOSSBATTLE1;
	BattleInfo.Enemy[0].Enemy = 215;
	BattleInfo.Enemy[0].x = 6;
	BattleInfo.Enemy[0].y = 8;
	BattleInfo.Enemy[1].Enemy = -1;
	BattleInfo.FailOK = 1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	evField(0,1);

	npDir(8,EAST);

	//---
	evSet(234,0);//---��
	evSet(EV_MENU_MODE,0);

	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		//---���ԉ�����
		pPartyInfo->PartyMember[1] = 1;
		pPartyInfo->PartyMember[2] = 2;
		pPartyInfo->PartyMember[3] = 3;

		et->Delay2(1000);
		prtRecoveryAll();
		evReloadMap(1);
		crfieldSetMainCharacter(1);
		for(a = 1;a <= 8;a ++){
			npDelete(a);
		}
		//---�����I
		//---��
		CrCharacter *pChara;
		for(a = 0;a < MEMBER_MAX;a ++){
			pChara = crcharaGetPartyMember(a);
			if(pChara != NULL){
				pChara->SetLP(pChara->GetMaxLP() / 2);
				pChara->SetMC(pChara->GetMaxMC() / 2);
			}
		}

		mcShow(1);
		mcDir(WEST);
		crfieldChangeScene(0,31,46);
		evFieldNoFlip(0,1);
		evFadeIn(500);

		evFrameWait(250);
		mes.FileMessage("Wesca.msg",111);
		evFrameWait(250);
		evSet(232,3);

		return 1;
	}

	//---���ԉ�����
	pPartyInfo->PartyMember[1] = 1;
	pPartyInfo->PartyMember[2] = 2;
	pPartyInfo->PartyMember[3] = 3;

	evFrameWait(1500);
	mes.OpenMessage("Wesca.msg",110);
	mes.ReadDraw();
	//---���N�X�[�A
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	npMove(1,0,-1);
	evFrame();
	//---��Ɏ��
	evFrameWait(1000);
	npDelete(8);
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(500);
	evFadeOut(1000);
	et->Delay2(1000);
	for(a = 1;a <= 8;a ++){
		npDelete(a);
	}
	//---��
	evReloadMap(1);
	crfieldSetMainCharacter(1);
	prtRecoveryAll();

	crfieldChangeScene(0,34,49);
	evReadObject(14,"Lunarn.acf");
	evReadObject(15,"Dizza.acf");
	evReadObject(12,"Nack.acf");
	evReadObject(13,"Xavier.acf");
	npPos(35,34,47);
	npDir(35,SOUTH);
	npPos(36,35,48);
	npDir(36,WEST);
	npPos(33,33,49);
	npDir(33,NORTH);
	npPos(34,34,48);
	npDir(34,NORTH);
	evFieldNoFlip(0,1);
	evFadeIn(1000);
//	evScene(0,34,49);

	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);

	for(a = 33;a <= 36;a ++){
		npDelete(a);
	}

	mes.CloseMessage();

	mcShow(1);
	mcDir(SOUTH);
	evScene(0,34,47);

	//---���N�X�[�A�A��ɓ��ꂽ
	evSet(233,1);
	critemAddItem(9,1);

	return 1;
}

//---------------------------------------------
#define YB_SIZE 3
int yubiwaGetField(int x,int y,int dir,int field[YB_SIZE][YB_SIZE])
{
	switch(dir){
	case 0:
		y --;
		x --;
		break;
	case 1:
		x ++;
		y --;
		break;
	case 2:
		x ++;
		y ++;
		break;
	case 3:
		x --;
		y ++;
		break;
	}
	if(x < 0 || y < 0 || x >= YB_SIZE || y >= YB_SIZE)
		return 0;
	return field[x][y];
}

eiTime stet,subet;
eiCell dizzacell[24];
static int styb_x,styb_y,dizza_ptn = 0,sub_ptn = 0,prv_x = 0,prv_y = 0,stdelta = 0,stdir = 0,first = 0;

void yubiwa_CallBack(eiCell *pScrCell,int sx,int sy,int top_x,int top_y,int delta_t)
{
	int x,y,px,py;

	if(first){
		stet.Reset();
		first = 0;
	}

	stdelta = stet.Get();
	if(stdelta >= 1000)
		stdelta = 1000;

	if(subet.Get() > 400){
		subet.Reset();
		sub_ptn = (sub_ptn + 1) & 0x01;
	}

	x = (styb_x - 1) * 30 + (styb_y - 1) * 30;
	y = (styb_y - 1) * 30 - (styb_x - 1) * 30;
	px = (prv_x - 1) * 30 + (prv_y - 1) * 30;
	py = (prv_y - 1) * 30 - (prv_x - 1) * 30;

	x = (x * stdelta + px * (1000 - stdelta)) / 1000;
	y = (y * stdelta + py * (1000 - stdelta)) / 1000;
	dizzacell[stdir * 2 + dizza_ptn * 8 + sub_ptn].PutTransClip(pScrCell,320 + x - 16,240 + y - 16);
}

int yubiwaMove(int *px,int *py,int life)
{
	int enable[5] = {1,1,1,1,2};
	int a,x = *px,y = *py,select,b;
	eistr *str[5] = {"�k��","�k��","�쓌","�쐼","����"};
	eistr temp[160],*p;
	CrSelectWindow win;

	crbaseMenuReset();

	if(y == 0)
		enable[0] = 0;
	if(x == YB_SIZE - 1)
		enable[1] = 0;
	if(y == YB_SIZE - 1)
		enable[2] = 0;
	if(x == 0)
		enable[3] = 0;

	//---���j���[������
	for(a = 0,p = temp;a < 4;a ++){
		if(enable[a]){
			sprintf(p,"%s �ɓ�����;",str[a]);
			p += strlen(p);
		}
	}
	sprintf(p,"����������Ă݂�;");
	p += strlen(p);

//	char s[80];
//	sprintf(s,"%d,%d  %d",x,y,life);

	win.Create(64,64,16,9,"���[�ƂˁE�E�E",temp);
	do {
		win.Paint();
		win.Refresh();

		crbaseMenuStart();

		select = win.Select();
	} while(select == -1);

	for(a = 0,b = 0;a < 5;a ++){
		if(enable[a]){
			if(b == select){
				prv_x = x;
				prv_y = y;

				if(a == 0)
					y --;
				if(a == 1)
					x ++;
				if(a == 2)
					y ++;
				if(a == 3)
					x --;
				stdir = a;
				if(a < 4){
					//---�ړ�
					styb_x = x;
					styb_y = y;
					stdelta = 0;
					stet.Reset();
					subet.Reset();

					ef->SetFGCallback(yubiwa_CallBack);
					first = 1;
					evScene(2,15,15);
					stet.Reset();
					subet.Reset();
					evFrameWait(1000);
					ef->SetFGCallback(NULL);
					evScene(0,26,13);
				}

				if(a == 4){
					return 4;
				}
			}
			b ++;
		}
	}

	*px = x;
	*py = y;

	return select;
}

//---�w�֒T���I�I
int yubiwaSagashi(void)
{
	CrMesManager mes;
	eistr *str[5] = {"��","�k","��","��","����"};

	int a,dz_x = 1,dz_y = 1,life = 10,turn,find = 0;
	int field[YB_SIZE][YB_SIZE];

	dizza_ptn = 0;

	eiCellReadPattern(dizzacell,
		CR_DATADIR2"Dizza_swim.acf",CR_DATAFILE2,crdataGetFileMode(),
		0,8,32,32);
	eiCellSetSurface(dizzacell,
		0,320,32,32,8,3);

	eiCellReadPattern(&dizzacell[8],
		CR_DATADIR2"Dizza_obore.acf",CR_DATAFILE2,crdataGetFileMode(),
		0,8,32,32);
	eiCellSetSurface(&dizzacell[8],
		0,320 + 32,32,32,8,3);

	eiCellReadPattern(&dizzacell[16],
		CR_DATADIR2"Dizza_find.acf",CR_DATAFILE2,crdataGetFileMode(),
		0,8,32,32);
	eiCellSetSurface(&dizzacell[16],
		0,320 + 64,32,32,8,3);

	memset(&field[0][0],0,sizeof(field));
	//---�w��
	field[eiRnd(YB_SIZE)][eiRnd(YB_SIZE)] = 1;

	while(life > 0){
		turn = yubiwaMove(&dz_x,&dz_y,life);

		if(turn == 4)
			life -= 3;
		else
			life --;

		if(life <= 0)
			life = 0;

		if(turn == 4){
			//---����
			if(field[dz_x][dz_y] == 1){
				//---���������I
//				evFrameWait(250);
//				mes.FileMessage("EPBldg.msg",135);

				stdir = 2;
				dizza_ptn = 0;
				evFrameWait(250);

				ef->SetFGCallback(yubiwa_CallBack);
				evScene(2,15,15);
				evFrameWait(500);
				ef->SetFGCallback(NULL);

				mes.FileMessage("EPBldg.msg",135);

				ef->SetFGCallback(yubiwa_CallBack);
				evFrameWait(500);
				stdir = 0;
				dizza_ptn = 2;
				subet.Reset();
				evFrameWait(2000);
				ef->SetFGCallback(NULL);
				evScene(0,26,13);
				evFrameWait(1000);

				find = 1;
				break;
			} else {
				//---����
				evFrameWait(250);
				for(a = 0;a < 4;a ++){
					if(yubiwaGetField(dz_x,dz_y,a,field) == 1){
						//---���̕����Ɍ�������
						mes.FileMessage("EPBldg.msg",130 + a);
						break;
					}
				}
				if(a == 4){
					mes.FileMessage("EPBldg.msg",134);
				}
			}
		}

		evFrameWait(250);
		if(life == 0){
			stdir = 2;
			dizza_ptn = 0;
			evFrameWait(250);

			ef->SetFGCallback(yubiwa_CallBack);
			evScene(2,15,15);
			evFrameWait(500);
			mes.FileMessage("EPBldg.msg",110 + life);
			evFrameWait(500);

			subet.Reset();
			stdir = 0;
			dizza_ptn = 1;
			evFrameWait(250);
			stdir = 1;
			dizza_ptn = 1;
			evFrameWait(250);
			stdir = 2;
			dizza_ptn = 1;
			evFrameWait(250);
			stdir = 3;
			dizza_ptn = 1;
			evFrameWait(500);

			ef->SetFGCallback(NULL);
			evFrameWait(500);
			stdir = 0;
			dizza_ptn = 0;
			evScene(0,26,13);
			evFrameWait(1000);
		} else {
			mes.FileMessage("EPBldg.msg",110 + life);
		}
		evFrameWait(250);
	}
	evFrameWait(250);

	for(a = 0;a < 24;a ++){
		dizzacell[a].Release();
	}

	return find;
}

//---���ˁ[�����̎w�ւ�T���I�I
CREVENTLONG9_API int crevent_AlsiaHashiObachanYubiwa(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	npPos(5,25,12);
	npDir(5,EAST);
	npPos(6,24,13);
	npDir(6,EAST);
	npPos(7,25,14);
	npDir(7,EAST);
	evScene(0,25,14);

	evFrameWait(250);
	mes.OpenMessage("EPBldg.msg",101);
	mes.ReadDraw();

	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		mcMove(1,0);
		evFrame();
	}
	evFrameWait(250);
	npMove(5,1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---�w�ւ�
	evFrameWait(250);
	npDir(4,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---����ہ[����ƁH
	for(a = 0;a < 2;a ++){
		npMove(7,1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(7,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(4,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---���������[��
	npDir(6,NORTH);
	evFrameWait(250);
	for(a = 0;a < 1;a ++){
		npMove(6,0,-1);
		evFrame();
	}
	for(a = 0;a < 1;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);

	//---�U�����
	npDir(5,NORTH);
	evFrameWait(250);
	npDir(5,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---�Ȃ񂾁H
	evFrameWait(250);
	npDir(6,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	//---������[�H
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	mes.ReadDraw();

	//---����
	evFrameWait(500);
	npDir(4,WEST);
	evFrameWait(1500);
	mes.ReadDraw();


	evFrameWait(500);
	npDelete(6);
	npDir(4,NORTH);
	npDir(5,NORTH);
	npPos(7,25,12);
	npDir(7,NORTH);

	evScene(0,26,13);
	crmusicPlay(CRMUSIC_NATSU);
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	mes.CloseMessage();

	if(yubiwaSagashi()){
		//---�����I
		evSet(240,1);
		evSet(239,1);

		npPos(4,25,13);
		npDir(4,EAST);
		npPos(5,26,12);
		npDir(5,WEST);
		npPos(6,26,13);
		npDir(6,WEST);
		npPos(7,26,14);
		npDir(7,WEST);
		evScene(0,26,15);
		evReloadMapMusic();

		mes.OpenMessage("EPBldg.msg",140);
		mes.ReadDraw(2);
		//---�撣�����̂́E�E�E
		evFrameWait(500);
		npDir(6,NORTH);
		evFrameWait(500);
		mes.ReadDraw();

		//---�����
		evFrameWait(500);
		mes.ReadDraw();
		evFrameWait(500);
		npDir(6,WEST);
		evFrameWait(500);
		mes.ReadDraw(4);
		evFrameWait(500);
		mes.ReadDraw();
		//---���ꂶ�Ⴀ
		evFrameWait(500);
		mes.ReadDraw();
		evFrameWait(250);
		npDir(4,SOUTH);
		evFrameWait(250);
		npDir(4,WEST);
		evFrameWait(250);
		for(a = 0;a < 12;a ++){
			npMove(4,-1,0);
			evFrame();
		}
		npDelete(4);
		evFrameWait(250);
		//---�����N
		critemAddItem(207,1);

		npDelete(5);
		npDelete(6);
		npDelete(7);
		mcShow(1);
		mcDir(SOUTH);
		evScene(0,26,13);

		mes.CloseMessage();
	} else {
		evSet(239,1);

		npPos(4,25,13);
		npDir(4,EAST);
		npPos(5,26,12);
		npDir(5,WEST);
		npPos(6,26,13);
		npDir(6,WEST);
		npPos(7,26,14);
		npDir(7,WEST);
		evScene(0,26,15);
		evReloadMapMusic();

		mes.OpenMessage("EPBldg.msg",141);
		mes.ReadDraw();
		//---�J��
		evFrameWait(500);
		npDir(6,NORTH);
		evFrameWait(500);
		mes.ReadDraw();

		//---�����A������ł�
		evFrameWait(500);
		mes.ReadDraw();
		//---����H
		evFrameWait(500);
		npDir(6,WEST);
		evFrameWait(500);
		mes.ReadDraw();

		//---���ꂶ�Ⴀ
		evFrameWait(500);
		mes.ReadDraw();
		evFrameWait(250);
		npDir(4,SOUTH);
		evFrameWait(250);
		npDir(4,WEST);
		evFrameWait(250);
		for(a = 0;a < 12;a ++){
			npMove(4,-1,0);
			evFrame();
		}
		npDelete(4);
		evFrameWait(250);
		npDir(5,SOUTH);
		evFrameWait(500);
		mes.ReadDraw();
		
		//---�A���V�A��
		evFrameWait(500);
		npDir(7,NORTH);
		evFrameWait(500);
		mes.ReadDraw(2);
		evFrameWait(500);

		npDelete(5);
		npDelete(6);
		npDelete(7);
		mcShow(1);
		mcDir(SOUTH);
		evScene(0,26,13);

		mes.CloseMessage();
	}

	return 1;
}

CREVENTLONG9_API int crevent_RyunohokoraBattle(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	evField(0,1);

	//---�o�g��
	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = CRMUSIC_BOSSBATTLE1;
	BattleInfo.Enemy[0].Enemy = 219;
	BattleInfo.Enemy[0].x = 6;
	BattleInfo.Enemy[0].y = 8;
	BattleInfo.Enemy[1].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	BattleInfo.FailOK = 1;
	BattleInfo.EnebleAvoid = 1;
	evField(0,1);

	if(crbatEventBattle(&BattleInfo) != BATRET_WIN){
		//---�����I
		evFrameWait(250);
		mes.OpenMessage("RyunoHokora.msg",13);
		mes.ReadDraw();
		mes.CloseMessage();
		evFrameWait(250);
		return 1;
	}

	evSet(251,1);

	evFrameWait(250);
	mes.OpenMessage("RyunoHokora.msg",12);
	
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	mes.CloseMessage();
	evFrameWait(250);

	//---�h���S���A�C�Y
	critemAddItem(127,1);

	return 1;
}

//---�Z�m�E�̃��[�t�B�A
CREVENTLONG9_API int crevent_CenowRarfia(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	npPos(0,19,24);
	npDir(0,NORTH);
	npPos(1,18,25);
	npDir(1,NORTH);
	npPos(2,20,25);
	npDir(2,NORTH);
	npPos(4,21,25);
	npDir(4,NORTH);
	evScene(0,19,26);

	evFrameWait(250);
	npDir(5,EAST);
	evFrameWait(250);
	npDir(5,SOUTH);
	evFrameWait(250);

	mes.OpenMessage("Cenow.msg",101);
	mes.ReadDraw(2);

	//---����
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---������
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---���ӔC���
	evFrameWait(1000);
	npDir(5,EAST);
	evFrameWait(500);
	npDir(5,NORTH);
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);

	//---���Ⴂ���Ȃ��ł�
	evFrameWait(500);
	npDir(5,WEST);
	evFrameWait(250);
	npDir(5,SOUTH);
	evFrameWait(500);
	mes.ReadDraw(3);

	evFrameWait(500);
	mes.ReadDraw(2);
	//---���l
	evFrameWait(500);
	mes.ReadDraw();

	//---�����
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw(3);

	//---���Ⴂ������
	evFrameWait(500);
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);

	npDelete(0);
	npDelete(1);
	npDelete(2);
	npDelete(4);

	mes.CloseMessage();

	mcShow(1);
	mcDir(SOUTH);
	evSet(252,1);

	evScene(0,19,25);

	return 1;
}

//---�c�[���A�̃G�h
CREVENTLONG9_API int crevent_TuriaEdo(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	npPos(43,65,20);
	npDir(43,NORTH);
	npPos(44,66,21);
	npDir(44,NORTH);
	npPos(45,64,20);
	npDir(45,NORTH);
	npPos(46,64,21);
	npDir(46,NORTH);
	evScene(0,65,22);

	evFrameWait(500);
	npDir(57,EAST);
	evFrameWait(500);
	npDir(57,SOUTH);
	evFrameWait(500);

	mes.OpenMessage("Turia.msg",104);
	mes.ReadDraw();

	//---�Ȃ񂶂�
	evFrameWait(1000);
	mes.ReadDraw(4);

	//---�킵�Ⴀ
	evFrameWait(1000);
	mes.ReadDraw(3);

	evFrameWait(500);
	mes.ReadDraw();
	//---���ȁH
	evFrameWait(500);
	mes.ReadDraw(4);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw(2);

	evFrameWait(500);
	npDir(57,EAST);
	evFrameWait(500);
	npDir(57,NORTH);

	evFrameWait(500);
	mes.ReadDraw();
	mes.CloseMessage();

	evFrameWait(500);

	npDelete(43);
	npDelete(44);
	npDelete(45);
	npDelete(46);

	mcShow(1);
	mcDir(SOUTH);
	evScene(0,65,20);

	evSet(253,1);

	return 1;
}


//---���i���K��
CREVENTLONG9_API int crevent_TreiaTooLongHappy(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	evReadObject(15,"Xavier.acf");
	npPos(22,45,32);
	npDir(22,SOUTH);
	npPos(23,44,32);
	npDir(23,SOUTH);
	npPos(24,46,32);
	npDir(24,SOUTH);
	npPos(25,43,32);
	npDir(25,SOUTH);

	evScene(0,45,34);

	evFrameWait(500);
	npDir(24,WEST);
	evFrameWait(500);
	mes.OpenMessage("Treia.msg",104);
	mes.ReadDraw(2);

	evFrameWait(500);
	npDir(24,SOUTH);
	evFrameWait(500);

	mes.ReadDraw(4);

	//---�ǂ����E�E�E
	evFrameWait(500);
	npDir(7,WEST);
	evFrameWait(500);
	npDir(7,SOUTH);
	evFrameWait(500);

	npMove(7,0,1);
	evFrame();
	evFrameWait(1000);

	npDir(7,WEST);
	evFrameWait(500);
	npDir(7,NORTH);
	evFrameWait(500);

	npMove(7,0,-1);
	evFrame();
	evFrameWait(500);

	for(a = 43;a <= 46;a ++){
		em->Put(a,33,2,59);
		evFrameWait(500);
	}
	evFrameWait(500);
	mes.ReadDraw();

	//---���C�Ȃ���
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(8);

	//---�����A�ނ��
	evFrameWait(500);
	mes.ReadDraw(2);

	//---����
	evFrameWait(2000);
	npDir(24,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	//---���O�Ⴂ
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---�ŁA
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(24,SOUTH);
	evFrameWait(500);
	mes.ReadDraw(6);
	evFrameWait(500);

	mes.CloseMessage();

	evSet(255,1);

	mcShow(1);
	mcDir(SOUTH);
	npDelete(22);
	npDelete(23);
	npDelete(24);
	npDelete(25);
	evScene(0,45,32);

	return 1;
}

//---�V���[�e�B���O�X�^�[�Q
CREVENTLONG9_API int crevent_TreiaSS2(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	npPos(0,13,15);
	npDir(0,NORTH);
	npPos(1,12,15);
	npDir(1,NORTH);
	npPos(2,14,16);
	npDir(2,NORTH);
	npPos(3,13,16);
	npDir(3,NORTH);
	npPos(5,13,13);
	npDir(5,SOUTH);
	npPos(4,13,8);
	npDir(4,SOUTH);
	evScene(0,13,20);

	evFrameWait(250);

	mes.OpenMessage("Treia.msg",105);
	mes.ReadDraw();

	//---��������
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();

	//---�E�E�E
	evFrameWait(500);
	mes.ReadDraw(3);

	//---���J��
	evFrameWait(500);
	em->Put(13,14,2,1024);
	evFrameWait(500);
	crmusicPlay(CRMUSIC_SS);

	for(a = 0;a < 3;a ++){
		mcMove(0,-1);
		evFrame();
	}
	//---���Ƃ�����
	npMove(5,0,-1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npMove(0,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);

	//---�吺�����ĂȂ񂾁[�H
	evFrameWait(500);
	for(a = 0;a < 2;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(250);
	for(a = 0;a < 3;a ++){
		npMove(4,0,1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	//---����
	evFrameWait(500);
	npMove(4,0,-1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);

	npPos(0,14,7);
	npDir(0,NORTH);
	npPos(1,13,7);
	npDir(1,NORTH);
	npPos(2,15,8);
	npDir(2,NORTH);
	npPos(3,12,7);
	npDir(3,NORTH);

	npPos(4,13,5);
	npDir(4,SOUTH);
	npPos(5,14,5);
	npDir(5,SOUTH);

	evScene(0,14,7);

	//---�Ȃ�ŉ��B��
	evFrameWait(500);
	mes.ReadDraw(2);

	//---�g���C�A�̐l��
	evFrameWait(500);
	mes.ReadDraw();

	//---�킩��₵��
	evFrameWait(500);
	mes.ReadDraw(2);

	//---���Ⴀ�A�_�C��
	evFrameWait(500);
	npDir(4,EAST);
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	npDir(4,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

/*	//---������
	evFrameWait(250);
	npMove(0,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();*/

	//---������A
	evFrameWait(500);
	mes.ReadDraw(2);

	//---�������A�f���炵���H
	evFrameWait(500);
	npDir(3,EAST);
	evFrameWait(500);
	npDir(3,NORTH);
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(500);
	npDir(3,NORTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---���ꂩ��E�E�E
	evFrameWait(500);
	mes.ReadDraw(4);

	//---����ς�
	evFrameWait(500);
	mes.ReadDraw(2);

	//---���ꂩ���
	evFrameWait(500);
	mes.ReadDraw(4);

	//---��������
	evFrameWait(250);
	npMove(4,0,-1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);

	//---�E�������
	evFrameWait(500);
	mes.ReadDraw();
	//---�s�G�[���I
	evFrameWait(250);
	npDir(5,WEST);
	evFrameWait(250);
	npDir(5,NORTH);
	evFrameWait(250);
	npMove(5,0,-1);
	evFrame();
	evFrameWait(250);
	npDir(5,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---�����āA
	evScene(1,10,10);
	evFrameWait(500);
	mes.ReadDraw(4);

	evFrameWait(500);
	npDir(4,WEST);
	evFrameWait(250);
	npDir(5,WEST);
	evFrameWait(250);
	npDir(4,SOUTH);
	evFrameWait(250);
	npDir(5,SOUTH);
	evFrameWait(250);
	npMove(4,0,1);
	evFrame();
	npMove(5,0,1);
	evFrame();

	//---�ӂƖ߂�
	evFrameWait(250);
	npDir(4,WEST);
	evFrameWait(250);
	npDir(4,NORTH);
	evFrameWait(500);

	//---�O�`���炢�́H
	mes.ReadDraw();
	evFrameWait(250);
	npMove(0,0,1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	mes.CloseMessage();

	mcShow(1);
	mcDir(SOUTH);
	evMap(10,0,253,150);
	evSet(255,2);

	return 1;
}

//---����̃T�~�b�g
CREVENTLONG9_API int crevent_AneatMoonlightSamit(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	if(evYado(16,0,0,NULL,1) == 0){
		//---���܂����I
		mcShow(0);

		npPos(27,28,38);
		npDir(27,NORTH);
		npPos(28,26,40);
		npDir(28,NORTH);
		npPos(29,29,39);
		npDir(29,NORTH);
		npPos(31,27,40);
		npDir(31,NORTH);

		evScene(0,28,40);

		evFrameWait(500);
		mes.OpenMessage("Aneat.msg",103);
		mes.ReadDraw();
		//---�f�B�U���i�b�N�s��
		evFrameWait(500);
		npDir(28,WEST);
		evFrameWait(250);
		for(a = 0;a < 13;a ++){
			npMove(28,-1,0);
			if(a < 2){
			} else if(a < 4)
				npDir(31,WEST);
			else
				npMove(31,-1,0);
			evFrame();
		}

		npDir(27,WEST);
		evFrameWait(250);
		npDir(27,SOUTH);
		evFrameWait(250);
		npMove(27,0,1);
		npDir(29,WEST);
		evFrame();

		//---���i������
		evFrameWait(250);
		mes.ReadDraw();
		//---�Ȃ�
		evFrameWait(250);
		npDir(27,EAST);
		evFrameWait(250);
		mes.ReadDraw(2);

		//---�ցH
		evFrameWait(500);
		mes.ReadDraw();
		evFrameWait(250);
		crmusicFadeOut();
		evFrameWait(500);

		//---���̔�
		evFadeOut(1000);

		crfieldPaletteChange(PALETTE_NIGHT);

		npPos(27,41,10);
		npDir(27,NORTH);
		npPos(29,42,10);
		npDir(29,NORTH);

		et->Delay2(1000);

		crfieldChangeScene(0,41,12);
		evFieldNoFlip(0,1);
		evFadeIn(1000);

		evFrameWait(500);
		crmusicPlay(CRMUSIC_SAMIT);
		evFrameWait(500);

		//---�g�}�g
		mes.ReadDraw(3);
		evFrameWait(500);

		em->Put(42,9,2,59);
		evFrameWait(500);
		em->Put(41,9,2,59);
		evFrameWait(1000);

		//---�ŁA�Ȃ�Ȃ́H
		mes.ReadDraw();

		evFrameWait(500);
		mes.ReadDraw(2);

		//---�V���f�B�������
		evFrameWait(1000);
		mes.ReadMessage(1);
		mes.Draw();

		mes.CreateNewMessage(1,192,320,15,4);
		mes.OpenMessage("Aneat.msg",104,1);
		mes.ReadMessage(1,1);
		mes.lpWin[1]->Draw(-1,1,1);

		mes.CloseMessage(1);

		//---�g�}�g�W���[�X��
		evFrameWait(500);
		npDir(27,EAST);
		evFrameWait(500);
		mes.ReadDraw(2);

		//---�V���f�B��
		evFrameWait(500);
		npDir(27,NORTH);
		evFrameWait(1000);
		mes.ReadDraw();

		evFrameWait(500);
		mes.ReadDraw();

		//---�ǂ̕ӂ��H
		evFrameWait(1000);
		mes.ReadDraw();
		//---�ǂ��_
		for(a = 0;a < 2;a ++){
			evFrameWait(1000);
			mes.ReadDraw(2);
		}
		//---�Ƃɂ������ɂ�
		evFrameWait(500);
		npDir(29,WEST);
		evFrameWait(250);
		mes.ReadDraw();

		evFrameWait(500);
		npDir(29,NORTH);
		evFrameWait(500);

		//---����Ƃ킽����
		mes.ReadDraw();
		evFrameWait(500);
		mes.ReadDraw();

		//---���̋C����́H
		evFrameWait(500);
		npDir(27,EAST);
		evFrameWait(500);
		mes.ReadDraw();
		evFrameWait(500);
		npDir(27,SOUTH);
		evFrameWait(250);
		npDir(29,WEST);
		evFrameWait(250);
		mes.ReadDraw(2);

		//---�����H
		evFrameWait(500);
		npDir(27,EAST);
		evFrameWait(500);
		mes.ReadDraw(3);

		//---�킩������
		evFrameWait(500);
		mes.ReadDraw(3);
		evFrameWait(500);

		//---�E���T�������
		npPos(28,32,18);
		for(a = 0;a < 9;a ++){
			npMove(28,1,0);
			evFrame();
		}
		npDir(27,SOUTH);
		evFrameWait(250);
		npDir(28,NORTH);
		evFrameWait(250);
		npDir(29,SOUTH);
		for(a = 0;a < 5;a ++){
			npMove(28,0,-1);
			evFrame();
		}
		evFrameWait(250);
		mes.ReadDraw(2);
		evFrameWait(500);


		//---�R�l��
		npDir(27,NORTH);
		npPos(28,40,10);
		npDir(28,NORTH);
		npDir(29,EAST);
		evScene(0,41,12);

		evFrameWait(1000);
		mes.ReadDraw();
		//---�ق�A
		evFrameWait(500);
		npDir(27,EAST);
		evFrameWait(500);
		mes.ReadDraw(2);

		//----�v���[���g
		evFrameWait(500);
		mes.ReadDraw();

		evFrameWait(250);
		npDir(29,NORTH);
		evFrameWait(250);
		npDir(29,WEST);
		evFrameWait(250);
		mes.ReadDraw();

		evFrameWait(250);
		npDir(27,NORTH);
		evFrameWait(250);
		npDir(27,WEST);
		evFrameWait(250);
		mes.ReadDraw();

		//---�ł��Ȃɂ�
		evFrameWait(500);
		mes.ReadDraw();

		//---�������A���i��
		evFrameWait(500);
		npDir(28,EAST);
		evFrameWait(250);
		mes.ReadDraw();
		evFrameWait(500);
		npDir(29,WEST);
		evFrameWait(500);
		npDir(27,SOUTH);
		evFrameWait(1000);
		npDir(27,WEST);
		evFrameWait(500);

		//---������
		mes.ReadDraw(2);

		evFrameWait(1000);
		mes.ReadDraw();
		//---�I����
		evFrameWait(1000);
		npDir(28,NORTH);
		evFrameWait(500);
		mes.ReadDraw(2);

		//---�Ƃ��Ƃ�
		evFrameWait(1000);
		mes.ReadDraw();
		evFrameWait(250);
		npDir(29,WEST);
		evFrameWait(250);
		mes.ReadDraw();

		evFrameWait(500);
		npDir(27,NORTH);
		evFrameWait(500);
		mes.ReadDraw();
		//---�������
		evFrameWait(500);
		mes.ReadDraw();

		//---��������O����
		evFrameWait(500);
		mes.ReadDraw();
		evFrameWait(500);
		npDir(27,EAST);
		evFrameWait(500);
		mes.ReadDraw(2);

		//---���e����
		evFrameWait(500);
		npDir(28,EAST);
		evFrameWait(500);
		mes.ReadDraw();

		evFrameWait(250);
		npDir(27,NORTH);
		evFrameWait(250);
		npDir(27,WEST);
		evFrameWait(250);
		//---�ジ����
		npMove(28,-1,0,0);
		evFrame();
		evFrameWait(250);
		mes.ReadDraw(2);

		evFrameWait(250);
		mes.ReadDraw();

		//---�M������_���I
		evFrameWait(250);
		npDir(27,NORTH);
		evFrameWait(250);
		npDir(27,EAST);
		evFrameWait(250);
		mes.ReadDraw();

		//---��l
		evFrameWait(500);
		npMove(28,1,0);
		evFrame();
		evFrameWait(250);
		mes.ReadDraw(2);

		//---�ӂ���
		evFrameWait(500);
		mes.ReadDraw(3);

		evFrameWait(1000);
		mes.ReadDraw();

		evFrameWait(1000);
		mes.ReadDraw();

		//---���J���I
		evFrameWait(500);
		npDir(29,NORTH);
		crmusicPlay(CRMUSIC_SAKABA);
		evFrameWait(500);
		mes.ReadDraw(2);

		evFrameWait(250);
		npDir(29,WEST);
		evFrameWait(250);
		mes.ReadDraw(2);

		//---���t�I
		evFrameWait(500);
		npDir(29,NORTH);
		evFrameWait(500);
		mes.ReadDraw();
		evFrameWait(1000);

		//---����
		evReloadMap(1);

		npPos(27,27,39);
		npDir(27,SOUTH);
		npPos(28,28,39);
		npDir(28,SOUTH);
		npPos(29,29,40);
		npDir(29,SOUTH);
		npPos(31,28,41);
		npDir(31,NORTH);

		evScene(0,28,41);

		evFrameWait(500);
		//---���{��̃i�b�N
		mes.ReadDraw(3);
		evFrameWait(500);
		mes.ReadDraw();
		evFrameWait(500);

		npDelete(27);
		npDelete(28);
		npDelete(29);
		npDelete(31);

		mes.CloseMessage();

		mcShow(1);
		mcDir(SOUTH);
		evScene(0,27,39);

		evSet(254,1);
	}

	return 1;
}

//---���[���N���C���Ɖ���ƃ��i��
CREVENTLONG9_API int crevent_JuleOnsen(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

/*	mcDir(NORTH);
	evFrameWait(500);
	mcDir(EAST);
	evFrameWait(500);*/

	mcShow(0);
	npPos(27,34,5);
	npDir(27,EAST);
	npPos(28,33,6);
	npDir(28,EAST);
	npPos(29,32,4);
	npDir(29,SOUTH);
	npPos(30,33,5);
	npDir(30,SOUTH);

	evScene(0,34,8);

	//---����H
	evFrameWait(250);
	mes.OpenMessage("JuleClara.msg",100);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(30,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	//---������Ɗ���
	evFrameWait(250);
	npDir(28,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(30,SOUTH);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---������������
	evFrameWait(500);
	npDir(27,NORTH);
	evFrameWait(250);
	npDir(27,WEST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);


	//---����
	evReadObject(12,"LunarnOnsen.acf");
	evReadObject(14,"NackOnsen.acf");
	npPos(27,68,18);
	npDir(27,SOUTH);
	npPos(29,70,18);
	npDir(29,EAST);
	evScene(0,69,19);
	crmusicPlay(CRMUSIC_NATSU);

	//---�L�X
	evFrameWait(1000);
	npDir(29,NORTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	for(a = 0;a < 3;a ++){
		if(a < 1)
			npMove(29,0,-1);
		else if(a < 2)
			npMove(29,-1,0);
		else
			npMove(29,0,1);

		evFrame();

		evFrameWait(500);
		if(a < 1)
			npDir(29,WEST);
		else if(a < 2)
			npDir(29,SOUTH);
		else
			npDir(29,WEST);
		evFrameWait(500);
	}

	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---�́[
	evFrameWait(1500);
	npDir(27,WEST);
	evFrameWait(500);
	npDir(27,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();

	//---�����āA
	evFrameWait(500);
	npDir(27,EAST);
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(1000);
	mes.ReadDraw();


	//---���ꂾ���̂���
	evFrameWait(1500);
	npDir(27,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(29,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---�N���X�t�B�[���h�ɂ�
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(29,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	//---�j������
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	crsoundPlay(CRSOUND_FIRE1);
	evFrameWait(500);
	npDir(29,NORTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---�ዾ��
	evFrameWait(500);
	crsoundPlay(CRSOUND_EAERTH1);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();

	//---��������
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---
	evReloadMap(1);

	npPos(27,29,12);
	npDir(27,SOUTH);
	npPos(28,28,13);
	npDir(28,EAST);
	npPos(29,30,13);
	npDir(29,WEST);
	npPos(30,29,14);
	npDir(30,NORTH);

	evScene(0,29,15);

	//---�Ȃ�ŕԎ���
	evFrameWait(500);
	npDir(28,NORTH);
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);
	npDir(28,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	//---����͂Ƃ������A
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	npDir(29,NORTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---�s������
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	mes.CloseMessage();

	npDelete(27);
	npDelete(28);
	npDelete(29);
	npDelete(30);
	evSet(256,1);

	mcShow(1);
	mcDir(SOUTH);
	evScene(0,29,12);

	return 1;
}

