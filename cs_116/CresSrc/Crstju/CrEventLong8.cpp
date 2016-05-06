/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrEventLong8.cpp ...Event functions

-----------------------------------------------------------*/


#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CREVENTLONG8

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


CREVENTLONG8_API int crevent_dumy3(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	return 1;
}

CREVENTLONG8_API int crevent_CarCdr(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	//---バトル
	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = CRMUSIC_BOSSBATTLE1;
	BattleInfo.Enemy[0].Enemy = 217;
	BattleInfo.Enemy[0].x = 4;
	BattleInfo.Enemy[0].y = 7;
	BattleInfo.Enemy[1].Enemy = 218;
	BattleInfo.Enemy[1].x = 7;
	BattleInfo.Enemy[1].y = 6;
	BattleInfo.Enemy[2].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	BattleInfo.FailOK = 1;
	BattleInfo.EnebleAvoid = 1;
	evField(0,1);

	if(crbatEventBattle(&BattleInfo) != BATRET_WIN){
		//---負け！
		crfieldChangeScene(8,7,11);
		evFrameWait(250);
		mcResetEvent();
		return 1;
	}

	evSet(245,1);
	evFrameWait(250);

	return 1;
}

CREVENTLONG8_API int crevent_HomotukoChika(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	//---バトル
	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = CRMUSIC_BOSSBATTLE1;
	BattleInfo.Enemy[0].Enemy = 220;
	BattleInfo.Enemy[0].x = 6;
	BattleInfo.Enemy[0].y = 7;
	BattleInfo.Enemy[1].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	BattleInfo.FailOK = 1;
	BattleInfo.EnebleAvoid = 1;
	evField(0,1);

	if(crbatEventBattle(&BattleInfo) != BATRET_WIN){
		//---負け！
		crfieldChangeScene(4,20,15);
		evFrameWait(250);
		mcResetEvent();
		return 1;
	}

	evSet(249,1);
	evFrameWait(250);

	return 1;
}

CREVENTLONG8_API int crevent_IllidiaMessage1(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	crfieldChangeScene(5,10,13);
	npPos(6,10,12);
	npDir(6,SOUTH);
	npPos(7,9,12);
	npDir(7,SOUTH);
	npPos(8,11,12);
	npDir(8,SOUTH);
	npPos(9,8,12);
	npDir(9,WEST);

	evScene(5,10,13);

	evFrameWait(500);
	npDir(8,EAST);
	evFrameWait(1000);
	npDir(8,SOUTH);
	evFrameWait(500);

	mes.OpenMessage("Illeadia.msg",100);
	mes.ReadDraw();
	evFrameWait(500);

	//---たくさんの人が
	npMove(6,0,1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw(2);

	//---でもどこかで
	evFrameWait(500);
	npDir(9,SOUTH);
	evFrameWait(250);
	npDir(9,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	//---あの時は・・・
	evFrameWait(1000);
	mes.ReadDraw(2);

	evFrameWait(500);
	npMove(7,0,1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.CloseMessage();

	for(a = 6;a <= 9;a ++){
		npDelete(a);
	}

	mcShow(1);
	mcDir(SOUTH);
	evScene(5,10,13);

	evSet(246,1);

	return 1;
}

//---ルナンの部屋
CREVENTLONG8_API int crevent_IllidiaLunarnsRoom(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	crfieldChangeScene(0,8,9);
	npPos(1,10,5);
	npDir(1,WEST);
	npPos(2,11,4);
	npDir(2,WEST);
	npPos(3,12,6);
	npDir(3,SOUTH);
	npPos(4,12,5);
	npDir(4,NORTH);

	evScene(0,8,9);

	evFrameWait(1000);
	npMove(1,-1,0);
	evFrame();
	evFrameWait(500);

	//---ここは・・・
	mes.OpenMessage("Illeadia.msg",101);
	mes.ReadDraw();
	evFrameWait(250);
	mes.ReadDraw();

	//---わたしの
	evFrameWait(1000);
	npMove(1,-1,0);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(4,WEST);
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---わたしはずっと
	evFrameWait(500);
	npDir(1,SOUTH);
	evFrameWait(1000);
	npMove(1,0,1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();

	//---本当に
	evFrameWait(1000);
	npMove(1,0,1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw();

	//---こんなところに
	evFrameWait(500);
	npDir(1,EAST);
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(1,0,-1);
		evFrame();
	}
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);

	mes.CloseMessage();

	for(a = 1;a <= 4;a ++){
		npDelete(a);
	}

	evSet(247,1);
	mcShow(1);
	mcDir(SOUTH);
	evScene(0,8,5);

	return 1;
}

CREVENTLONG_ENDING_API int crevent_EndingAfterBattle(void);

CREVENTLONG8_API int crevent_IllidiaLastBattle(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	crmusicFadeOut();
	mcShow(0);

	npPos(1,22,19);
	npDir(1,NORTH);
	npPos(2,21,20);
	npDir(2,NORTH);
	npPos(3,23,20);
	npDir(3,NORTH);
	npPos(4,22,21);
	npDir(4,NORTH);

	evScene(6,22,20);

	evFrameWait(250);

	//---クレイシヴ！
	mes.OpenMessage("Illeadia.msg",110);
	mes.ReadDraw();

//	evFrameWait(1000);
//	npDir(0,WEST);
	evFrameWait(500);
	npDir(0,SOUTH);
	evFrameWait(1000);

	crmusicPlay(CRMUSIC_CRAYSIVE);

	//---アージェ写す
	for(a = 0;a < 14;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(2000);
	for(a = 0;a < 14;a ++){
		mcMove(0,1);
		evFrame();
	}

	//---まだ
	evFrameWait(500);
	npMove(2,0,-1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();

	//---すでに
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	npMove(4,0,-1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npMove(3,0,-1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();

	//---戦うこと以外で
	evFrameWait(500);
	mes.ReadDraw(3);
	//---違いはない
	evFrameWait(1000);
	mes.ReadDraw(3);

	//---アージェこそが
	evFrameWait(1000);
	npDir(0,EAST);
	evFrameWait(500);
	npDir(0,NORTH);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);

	//---私に
	evFrameWait(1000);
	npDir(0,WEST);
	evFrameWait(500);
	npDir(0,SOUTH);
	evFrameWait(1000);
	mes.ReadDraw();
	//---覚悟は
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);

	npMove(1,0,-1);
	evFrame();
	evFrameWait(250);

	mes.CloseMessage();

	//------------------ラストバトル
	//---バトル
	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = 2;
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = 0;//CRMUSIC_HOPE;
	BattleInfo.Enemy[0].Enemy = 223;
	BattleInfo.Enemy[0].x = 6;
	BattleInfo.Enemy[0].y = 8;
	BattleInfo.Enemy[1].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	BattleInfo.FailOK = 1;
//	BattleInfo.EnebleAvoid = 1;
	evField(0,1);

	npDelete(0);

	npPos(5,20,17);
	npDir(5,NORTH);
	npPos(6,21,17);
	npDir(6,EAST);
	npPos(7,20,18);
	npDir(7,SOUTH);
	npPos(8,21,18);
	npDir(8,WEST);

	npPos(1,21,19);
	npDir(1,NORTH);
	npPos(2,20,20);
	npDir(2,NORTH);
	npPos(3,24,20);
	npDir(3,NORTH);
	npPos(4,22,20);
	npDir(4,NORTH);

	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		//---負け！
		et->Delay2(500);
		return MAINLOOP_BATTLEFAIL;
	}
	if(evGet(261) == 1){
		npDelete(5);
		npDelete(6);
		npDelete(7);
		npDelete(8);
		npPos(0,20,17);
		npDir(0,SOUTH);
	}

	return crevent_EndingAfterBattle();
}

CREVENTLONG8_API int crevent_IllidiaDeen(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	npPos(2,12,15);
	npDir(2,NORTH);
	npPos(3,11,15);
	npDir(3,NORTH);
	npPos(4,12,16);
	npDir(4,NORTH);
	npPos(5,13,16);
	npDir(5,NORTH);

	evScene(5,12,15);

	//---クレスティーユよ
	evFrameWait(250);
	{
		mes.CreateNewMessage(0,160,144,20,4,1);
		mes.OpenMessage("Illeadia.msg",130);
		mes.ReadDraw();
		mes.CloseMessage();
	}
	//---誰！？
	evFrameWait(250);
	npMove(2,0,-1);
	evFrame();
	evFrameWait(250);

	mes.FileMessage("Illeadia.msg",131);
	evFrameWait(250);


	//---統べる者
	evFrameWait(1000);
	{
		mes.CreateNewMessage(0,160,144,20,4,1);
		mes.OpenMessage("Illeadia.msg",132);
		mes.ReadDraw();
		mes.CloseMessage();
	}
	evFrameWait(1000);
	mes.FileMessage("Illeadia.msg",133);
	evFrameWait(500);

	for(a = 0;a < 6;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(250);
	for(a = 0;a < 8;a ++){
		if(a < 5)
			npMove(2,0,-1);
		if(a && a < 6)
			npMove(3,0,-1);
		if(a && a < 7)
			npMove(4,0,-1);
		if(a >= 2)
			npMove(5,0,-1);
		evFrame();
	}
	evFrameWait(1000);

	for(a = 0;a < 5;a ++){
		mes.CreateNewMessage(0,160,144,20,4,1);
		mes.OpenMessage("Illeadia.msg",134 + a * 2);
		mes.ReadDraw();
		mes.CloseMessage();

		if(a == 2){
			evFrameWait(500);
			npMove(3,0,-1);
			evFrame();
			evFrameWait(250);
		} else {
			evFrameWait(1000);
		}
		mes.FileMessage("Illeadia.msg",135 + a * 2);
		evFrameWait(1500);
	}

	//---牢獄に
	evFrameWait(1500);
	{
		mes.CreateNewMessage(0,160,144,20,4,1);
		mes.OpenMessage("Illeadia.msg",144);
		mes.ReadDraw();
		mes.CloseMessage();
	}
	evFrameWait(500);
	{
		mes.CreateNewMessage(0,160,144,20,4,1);
		mes.OpenMessage("Illeadia.msg",145);
		mes.ReadDraw();
		mes.CloseMessage();
	}

	evFrameWait(1000);
	mes.FileMessage("Illeadia.msg",146);

	//---クレスティーユとクレイシヴ
	evFrameWait(2000);
	for(a = 0;a < 4;a ++){
		mes.CreateNewMessage(0,160,144,20,4,1);
		mes.OpenMessage("Illeadia.msg",148 + a);
		mes.ReadDraw();
		mes.CloseMessage();
		evFrameWait(1000);
	}

	//---行ってやろうぜ
	evFrameWait(1000);
	npDir(3,EAST);
	evFrameWait(500);
	mes.OpenMessage("Illeadia.msg",152);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	mes.CloseMessage();
	evFrameWait(500);

	mcShow(1);
	mcDir(NORTH);

	npDelete(2);
	npDelete(3);
	npDelete(4);
	npDelete(5);

	evScene(5,12,9);

	evSet(263,1);

	return 1;
}
