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

//---ウェスカの亡霊、はじめて訪れた
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
	//---二人、立ち去る
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

//---ウェスカの亡霊、最初の宿
CREVENTLONG9_API int crevent_WescaLuxthereFirstSleep(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	evField(0,1);
	mes.OpenMessage("Wesca.msg",105);
	mes.ReadDraw(2);
	mes.CloseMessage();

	if(evYado(5,0,0,NULL,1) == 0){
		//---泊まった！
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
		//---どうやって
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
		//---ようやく
		evFrameWait(250);
		mes.ReadDraw();

		evFrameWait(500);
		mes.ReadDraw(2);
		evFrameWait(250);
		//---あたしも
		npMove(33,0,1);
		evFrame();
		evFrameWait(250);
		mes.ReadDraw();
		evFrameWait(250);
		npDir(33,EAST);
		evFrameWait(250);
		mes.ReadDraw(2);
		evFrameWait(500);

		//---いい夢みたんだけど・・・
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

//---ウェスカの亡霊、対決
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

		//---対決２回目以降
		if(evGet(232) >= 3)
			return crevent_WescaLuxthereSleepAfter();

		mes.OpenMessage("Wesca.msg",107);
		mes.ReadDraw();
		mes.CloseMessage();

		evFrameWait(1000);

		int sel;
		CrSelectWindow win;
		win.Create(64,64,16,7,"ト・・・トマト・・・","ぐー;すぴー;んにゃ;");
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

			//---朝
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

		//---目が覚める！
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

		//---ルナン、目を覚ます
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

		//---ルナン
		evReadObject(14,"Lunan.acf");
		em->ReloadPattern();
		crfieldPaletteChange(PALETTE_NIGHT);
		evFrameWait(500);

//		npPos(1,10,2);
//		npDir(1,SOUTH);
		npDelete(1);

		evSet(232,2);//寝たの２回目
		//---
		evSet(234,1);//---夜
		evSet(EV_MENU_MODE,2);
		//---仲間外す
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

//---寝るの３回目以降
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
	//---そうだ！！
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

//---ウェスカの亡霊、対決
CREVENTLONG9_API int crevent_WescaLuxthereVS(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	//---仲間外す
	pPartyInfo->PartyMember[1] = -1;
	pPartyInfo->PartyMember[2] = -1;
	pPartyInfo->PartyMember[3] = -1;

	if(evGet(232) <= 2){
		//---最初！
		npPos(1,3,9);
		npDir(1,WEST);
		mcShow(0);

		evReadObject(14,"Lunarn.acf");
		evReadObject(11,"Luxthere.acf");
		em->ReloadPattern();
		crfieldPaletteChange(PALETTE_NIGHT);

		mes.OpenMessage("Wesca.msg",109);
		mes.ReadDraw();
		//---何！？
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
		//---でもみんな・・・
		evFrameWait(1000);
		mes.ReadDraw();

		//---気配！
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

		//---我が夢より
		mes.ReadDraw();
		evFrameWait(500);

		//---ルクスゼア
		npPos(8,3,0);
		npDir(8,NORTH);
		evFrameWait(500);
		for(a = 0;a < 4;a ++){
			npMove(8,0,1,0);
			evFrame();
		}
		//---夢なら
		evFrameWait(500);
		mes.ReadDraw();

		evFrameWait(1000);
		mes.ReadDraw(2);

		//---名剣・・・
		evFrameWait(1000);
		mes.ReadDraw(2);
		evFrameWait(1000);
		mes.ReadDraw();
		evFrameWait(250);

		mes.CloseMessage();
	}

	//---よこせ！！
	eiMapObject *ob = npGet(8);
	ob->Data.MoveSpeed = 2;
	for(a = 0;a < 1;a ++){
		npMove(8,0,1,0);
		evFrame();
	}
	ob->Data.MoveSpeed = 1;
	evFrameWait(50);

	//---バトル！！
	//---バトル
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
	evSet(234,0);//---夜
	evSet(EV_MENU_MODE,0);

	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		//---仲間加える
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
		//---負け！
		//---朝
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

	//---仲間加える
	pPartyInfo->PartyMember[1] = 1;
	pPartyInfo->PartyMember[2] = 2;
	pPartyInfo->PartyMember[3] = 3;

	evFrameWait(1500);
	mes.OpenMessage("Wesca.msg",110);
	mes.ReadDraw();
	//---ルクスゼア
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	npMove(1,0,-1);
	evFrame();
	//---手に取る
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
	//---朝
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

	//---ルクスゼア、手に入れた
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
	eistr *str[5] = {"北西","北東","南東","南西","潜る"};
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

	//---メニュー文字列
	for(a = 0,p = temp;a < 4;a ++){
		if(enable[a]){
			sprintf(p,"%s に動いて;",str[a]);
			p += strlen(p);
		}
	}
	sprintf(p,"そこを潜ってみて;");
	p += strlen(p);

//	char s[80];
//	sprintf(s,"%d,%d  %d",x,y,life);

	win.Create(64,64,16,9,"えーとね・・・",temp);
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
					//---移動
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

//---指輪探し！！
int yubiwaSagashi(void)
{
	CrMesManager mes;
	eistr *str[5] = {"西","北","東","南","潜る"};

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
	//---指輪
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
			//---潜る
			if(field[dz_x][dz_y] == 1){
				//---見つかった！
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
				//---周囲
				evFrameWait(250);
				for(a = 0;a < 4;a ++){
					if(yubiwaGetField(dz_x,dz_y,a,field) == 1){
						//---この方向に見つかった
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

//---おねーちゃんの指輪を探せ！！
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

	//---指輪を
	evFrameWait(250);
	npDir(4,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---いんぽーたんと？
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

	//---けっこう深い
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

	//---振り向く
	npDir(5,NORTH);
	evFrameWait(250);
	npDir(5,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---なんだ？
	evFrameWait(250);
	npDir(6,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	//---きゃんゆー？
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	mes.ReadDraw();

	//---沈黙
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
		//---成功！
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
		//---頑張ったのは・・・
		evFrameWait(500);
		npDir(6,NORTH);
		evFrameWait(500);
		mes.ReadDraw();

		//---お礼に
		evFrameWait(500);
		mes.ReadDraw();
		evFrameWait(500);
		npDir(6,WEST);
		evFrameWait(500);
		mes.ReadDraw(4);
		evFrameWait(500);
		mes.ReadDraw();
		//---それじゃあ
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
		//---安眠君
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
		//---労を
		evFrameWait(500);
		npDir(6,NORTH);
		evFrameWait(500);
		mes.ReadDraw();

		//---いえ、いいんです
		evFrameWait(500);
		mes.ReadDraw();
		//---だろ？
		evFrameWait(500);
		npDir(6,WEST);
		evFrameWait(500);
		mes.ReadDraw();

		//---それじゃあ
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
		
		//---アルシアに
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

	//---バトル
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
		//---負け！
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

	//---ドラゴンアイズ
	critemAddItem(127,1);

	return 1;
}

//---セノウのラーフィア
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

	//---服が
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---そうよ
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---無責任よね
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

	//---勘違いしないでね
	evFrameWait(500);
	npDir(5,WEST);
	evFrameWait(250);
	npDir(5,SOUTH);
	evFrameWait(500);
	mes.ReadDraw(3);

	evFrameWait(500);
	mes.ReadDraw(2);
	//---旅人
	evFrameWait(500);
	mes.ReadDraw();

	//---勝手に
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw(3);

	//---じゃいこうか
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

//---ツーリアのエド
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

	//---なんじゃ
	evFrameWait(1000);
	mes.ReadDraw(4);

	//---わしゃあ
	evFrameWait(1000);
	mes.ReadDraw(3);

	evFrameWait(500);
	mes.ReadDraw();
	//---反省？
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


//---超永い幸せ
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

	//---どうぞ・・・
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

	//---元気ないな
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(8);

	//---いえ、彼らは
	evFrameWait(500);
	mes.ReadDraw(2);

	//---沈黙
	evFrameWait(2000);
	npDir(24,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	//---名前違い
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---で、
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

//---シューティングスター２
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

	//---もしもし
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();

	//---・・・
	evFrameWait(500);
	mes.ReadDraw(3);

	//---扉開く
	evFrameWait(500);
	em->Put(13,14,2,1024);
	evFrameWait(500);
	crmusicPlay(CRMUSIC_SS);

	for(a = 0;a < 3;a ++){
		mcMove(0,-1);
		evFrame();
	}
	//---あとずさる
	npMove(5,0,-1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npMove(0,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);

	//---大声だしてなんだー？
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
	//---驚く
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

	//---なんで俺達が
	evFrameWait(500);
	mes.ReadDraw(2);

	//---トレイアの人が
	evFrameWait(500);
	mes.ReadDraw();

	//---わかりやした
	evFrameWait(500);
	mes.ReadDraw(2);

	//---じゃあ、ダイで
	evFrameWait(500);
	npDir(4,EAST);
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	npDir(4,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

/*	//---つっこみ
	evFrameWait(250);
	npMove(0,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();*/

	//---姐さん、
	evFrameWait(500);
	mes.ReadDraw(2);

	//---ここが、素晴らしい？
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

	//---あれから・・・
	evFrameWait(500);
	mes.ReadDraw(4);

	//---やっぱり
	evFrameWait(500);
	mes.ReadDraw(2);

	//---これからは
	evFrameWait(500);
	mes.ReadDraw(4);

	//---ぐごげふ
	evFrameWait(250);
	npMove(4,0,-1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);

	//---ウリ文句も
	evFrameWait(500);
	mes.ReadDraw();
	//---ピエール！
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

	//---そして、
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

	//---ふと戻る
	evFrameWait(250);
	npDir(4,WEST);
	evFrameWait(250);
	npDir(4,NORTH);
	evFrameWait(500);

	//---外伝くらいは？
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

//---月夜のサミット
CREVENTLONG9_API int crevent_AneatMoonlightSamit(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	if(evYado(16,0,0,NULL,1) == 0){
		//---泊まった！
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
		//---ディザ＆ナック行く
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

		//---ルナンさん
		evFrameWait(250);
		mes.ReadDraw();
		//---なに
		evFrameWait(250);
		npDir(27,EAST);
		evFrameWait(250);
		mes.ReadDraw(2);

		//---へ？
		evFrameWait(500);
		mes.ReadDraw();
		evFrameWait(250);
		crmusicFadeOut();
		evFrameWait(500);

		//---その晩
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

		//---トマト
		mes.ReadDraw(3);
		evFrameWait(500);

		em->Put(42,9,2,59);
		evFrameWait(500);
		em->Put(41,9,2,59);
		evFrameWait(1000);

		//---で、なんなの？
		mes.ReadDraw();

		evFrameWait(500);
		mes.ReadDraw(2);

		//---シンディさんって
		evFrameWait(1000);
		mes.ReadMessage(1);
		mes.Draw();

		mes.CreateNewMessage(1,192,320,15,4);
		mes.OpenMessage("Aneat.msg",104,1);
		mes.ReadMessage(1,1);
		mes.lpWin[1]->Draw(-1,1,1);

		mes.CloseMessage(1);

		//---トマトジュースが
		evFrameWait(500);
		npDir(27,EAST);
		evFrameWait(500);
		mes.ReadDraw(2);

		//---シンディが
		evFrameWait(500);
		npDir(27,NORTH);
		evFrameWait(1000);
		mes.ReadDraw();

		evFrameWait(500);
		mes.ReadDraw();

		//---どの辺が？
		evFrameWait(1000);
		mes.ReadDraw();
		//---良い点
		for(a = 0;a < 2;a ++){
			evFrameWait(1000);
			mes.ReadDraw(2);
		}
		//---とにもかくにも
		evFrameWait(500);
		npDir(29,WEST);
		evFrameWait(250);
		mes.ReadDraw();

		evFrameWait(500);
		npDir(29,NORTH);
		evFrameWait(500);

		//---それとわたしと
		mes.ReadDraw();
		evFrameWait(500);
		mes.ReadDraw();

		//---その気あるの？
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

		//---そお？
		evFrameWait(500);
		npDir(27,EAST);
		evFrameWait(500);
		mes.ReadDraw(3);

		//---わかったわ
		evFrameWait(500);
		mes.ReadDraw(3);
		evFrameWait(500);

		//---ウワサをすれば
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


		//---３人で
		npDir(27,NORTH);
		npPos(28,40,10);
		npDir(28,NORTH);
		npDir(29,EAST);
		evScene(0,41,12);

		evFrameWait(1000);
		mes.ReadDraw();
		//---ほら、
		evFrameWait(500);
		npDir(27,EAST);
		evFrameWait(500);
		mes.ReadDraw(2);

		//----プレゼント
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

		//---でもなにを
		evFrameWait(500);
		mes.ReadDraw();

		//---そうだ、ルナン
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

		//---そうね
		mes.ReadDraw(2);

		evFrameWait(1000);
		mes.ReadDraw();
		//---オレが
		evFrameWait(1000);
		npDir(28,NORTH);
		evFrameWait(500);
		mes.ReadDraw(2);

		//---とっとと
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
		//---投げやり
		evFrameWait(500);
		mes.ReadDraw();

		//---何もする前から
		evFrameWait(500);
		mes.ReadDraw();
		evFrameWait(500);
		npDir(27,EAST);
		evFrameWait(500);
		mes.ReadDraw(2);

		//---爆弾発言
		evFrameWait(500);
		npDir(28,EAST);
		evFrameWait(500);
		mes.ReadDraw();

		evFrameWait(250);
		npDir(27,NORTH);
		evFrameWait(250);
		npDir(27,WEST);
		evFrameWait(250);
		//---後ずさる
		npMove(28,-1,0,0);
		evFrame();
		evFrameWait(250);
		mes.ReadDraw(2);

		evFrameWait(250);
		mes.ReadDraw();

		//---信じちゃダメ！
		evFrameWait(250);
		npDir(27,NORTH);
		evFrameWait(250);
		npDir(27,EAST);
		evFrameWait(250);
		mes.ReadDraw();

		//---一人
		evFrameWait(500);
		npMove(28,1,0);
		evFrame();
		evFrameWait(250);
		mes.ReadDraw(2);

		//---砕けろ
		evFrameWait(500);
		mes.ReadDraw(3);

		evFrameWait(1000);
		mes.ReadDraw();

		evFrameWait(1000);
		mes.ReadDraw();

		//---お開き！
		evFrameWait(500);
		npDir(29,NORTH);
		crmusicPlay(CRMUSIC_SAKABA);
		evFrameWait(500);
		mes.ReadDraw(2);

		evFrameWait(250);
		npDir(29,WEST);
		evFrameWait(250);
		mes.ReadDraw(2);

		//---乾杯！
		evFrameWait(500);
		npDir(29,NORTH);
		evFrameWait(500);
		mes.ReadDraw();
		evFrameWait(1000);

		//---翌朝
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
		//---お怒りのナック
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

//---ユールクレイラと温泉とルナン
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

	//---温泉？
	evFrameWait(250);
	mes.OpenMessage("JuleClara.msg",100);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(30,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	//---ちょっと期待
	evFrameWait(250);
	npDir(28,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(30,SOUTH);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---せっかくだし
	evFrameWait(500);
	npDir(27,NORTH);
	evFrameWait(250);
	npDir(27,WEST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);


	//---温泉
	evReadObject(12,"LunarnOnsen.acf");
	evReadObject(14,"NackOnsen.acf");
	npPos(27,68,18);
	npDir(27,SOUTH);
	npPos(29,70,18);
	npDir(29,EAST);
	evScene(0,69,19);
	crmusicPlay(CRMUSIC_NATSU);

	//---広々
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

	//---はー
	evFrameWait(1500);
	npDir(27,WEST);
	evFrameWait(500);
	npDir(27,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();

	//---だって、
	evFrameWait(500);
	npDir(27,EAST);
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(1000);
	mes.ReadDraw();


	//---これだけのお湯
	evFrameWait(1500);
	npDir(27,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(29,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---クレスフィールドにも
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(29,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	//---男湯から
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	crsoundPlay(CRSOUND_FIRE1);
	evFrameWait(500);
	npDir(29,NORTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---眼鏡が
	evFrameWait(500);
	crsoundPlay(CRSOUND_EAERTH1);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();

	//---そっちは
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

	//---なんで返事を
	evFrameWait(500);
	npDir(28,NORTH);
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);
	npDir(28,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	//---それはともかく、
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	npDir(29,NORTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---行こうぜ
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

