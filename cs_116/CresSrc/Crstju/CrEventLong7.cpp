/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrEventLong7.cpp ...Event functions

-----------------------------------------------------------*/


#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CREVENTLONG7

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

CREVENTLONG7_API int creventKojinsaiChushinbu(void);
CREVENTLONG7_API int creventKojinsaiOilLake(void);
CREVENTLONG7_API int creventKojinsaiOilLakeNight(void);

CREVENTLONG7_API int crevent_dumy2(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	return 1;
}

//---降神祭、出発
CREVENTLONG7_API int creventGotoKojinsai(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	npDelete(24);
	npDelete(25);
	npDelete(27);
	npDelete(28);

	npPos(0,21,32);
	npDir(0,NORTH);
	npPos(1,22,32);
	npDir(1,NORTH);
	npPos(2,23,33);
	npDir(2,NORTH);
	npPos(3,19,33);
	npDir(3,NORTH);
	npPos(4,23,34);
	npDir(4,NORTH);
	npPos(5,20,33);
	npDir(5,NORTH);
	npPos(6,21,33);
	npDir(6,NORTH);

	npPos(23,21,30);
	npDir(23,SOUTH);
	npPos(26,20,29);
	npDir(26,SOUTH);

	evFadeOut();
	ef->xSet(21);
	ef->ySet(33);
	evFieldNoFlip(0,1);
	evFadeIn();
//	evScene(3,21,33);

	evSet(218,1);

	evFrameWait(500);

	mes.OpenMessage("RyusanoIseki.msg",106);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---ＧＳ
	crfieldChangeMap(59,1,1,0);
	crfieldChangeScene(1,6,7);

	npPos(0,6,5);
	npDir(0,EAST);

	evScene(1,6,7);
	crsoundPlay(CRSOUND_GS_SOUND,EISOUND_PLAYLOOP);
	evFrameWait(1000);
	//---すっ飛ばして
	mes.ReadDraw();

	evFrameWait(1000);
	em->Put(10,3,2,26);
	evFrameWait(250);
	em->Put(10,3,2,27);
	evFrameWait(250);
	crsoundStop(CRSOUND_GS_SOUND);
	crsoundPlay(CRSOUND_GS_FUMISUGI2,EISOUND_PLAYLOOP);
	evFrameWait(1000);

	//---準備
	npDir(1,NORTH);
	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	crsoundStop(CRSOUND_GS_FUMISUGI2);

	//---メニュー
	crmainMainMenu(1);
	crsoundPlay(CRSOUND_GS_FUMISUGI2,EISOUND_PLAYLOOP);
	evFrameWait(1000);
	
	crmusicFadeOut();
	evFadeOut(2000);
	et->Delay2(1000);
	crsoundStop(CRSOUND_GS_FUMISUGI2);
	et->Delay2(1000);
	crmusicPlay(CRMUSIC_SILENT);
	mes.CloseMessage();

	//---フィールド
	mcShow(1);
	crfieldChangeMap(10,0,1,0);
	crfieldSetMainCharacter(3);
	mcDir(SOUTH);
	evScene(0,42 - 5,244 - 30);
	for(a = 0;a < 10;a ++){
		mcMove(0,1);
		evFrame();
	}
	for(a = 0;a < 5;a ++){
		mcMove(1,0);
		evFrame();
	}
	for(a = 0;a < 20;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(250);
	evFadeOut(1000);
	mcShow(0);
	crfieldSetMainCharacter(1);

	//---大神殿！
	crfieldChangeMap(80,0,1,0);
	crfieldChangeScene(0,24,51);
	npDelete(3);
	npDelete(4);
	npDelete(5);
	evFieldNoFlip(0,1);
	evFadeIn(1000);

	evFrameWait(1000);

	npPos(6,24,60);
	npDir(6,NORTH);
	npPos(7,23,61);
	npDir(7,NORTH);
	npPos(8,25,62);
	npDir(8,NORTH);
	npPos(9,22,63);
	npDir(9,NORTH);
	npPos(10,26,62);
	npDir(10,NORTH);
	npPos(11,25,61);
	npDir(11,NORTH);
	npPos(12,22,61);
	npDir(12,NORTH);

	for(a = 0;a < 14;a ++){
		for(b = 6;b <= 12;b ++){
			if(b <= 7 && a < 13)
				npMove(b,0,-1);
			if(b >= 10 && a)
				npMove(b,0,-1);
			if(b == 8 && a)
				npMove(b,0,-1);
			if(b == 9 && a < 14)
				npMove(b,0,-1);
		}
		evFrame();
	}
	for(a = 0;a < 3;a ++){
		mcMove(0,-1);
		evFrame();
	}

	evFrameWait(500);
	mes.OpenMessage("Daishinden.msg",100);
	mes.ReadDraw();
	//---その降神祭を
	evFrameWait(500);
	mes.ReadDraw(3);

	evFrameWait(50);
	crmusicPlay(CRMUSIC_BREAKFORTUNE);
	evFrameWait(250);
	npMove(6,0,-1);
	evFrame();
	evFrameWait(250);

	//---バトル
	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = 0;
	BattleInfo.Enemy[0].Enemy = 186;
	BattleInfo.Enemy[0].x = 3;
	BattleInfo.Enemy[0].y = 8;
	BattleInfo.Enemy[1].Enemy = 187;
	BattleInfo.Enemy[1].x = 7;
	BattleInfo.Enemy[1].y = 6;
	BattleInfo.Enemy[2].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	evField(0,1);

	npDelete(0);
	npDelete(1);
	npDelete(2);

	npPos(12,23,47);

	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}

	evFrameWait(250);

	//---シンディ動く
	for(a = 0;a < 5;a ++){
		if(a < 2)
			npMove(12,0,-1);
		else if(a < 3)
			npMove(12,1,0);
		else
			npMove(12,0,-1);
		evFrame();
	}
	//---こっちよ
	evFrameWait(250);
	npDir(12,EAST);
	evFrameWait(250);
	npDir(12,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(12,WEST);
	evFrameWait(250);
	npDir(12,NORTH);
	evFrameWait(250);

	for(a = 0;a < 9;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(500);

	//---内部へ
	crfieldChangeScene(1,26,55);

	npPos(0,25,56);
	npPos(1,24,56);
	npPos(2,27,56);
	npPos(3,23,56);
	npPos(4,26,56);
	npPos(5,28,56);
	npPos(6,26,56);

	evScene(1,26,55);

	evFrameWait(500);

	for(a = 0;a < 16;a ++){
		if(a < 12){
			npMove(6,0,-1);
		}

		if(a >= 1 && a < 12){
			npMove(0,0,-1);
		}
		if(a >= 3 && a < 15){
			npMove(1,0,-1);
		}
		if(a >= 2 && a < 12){
			npMove(5,0,-1);
		}
		if(a >= 2 && a < 12){
			npMove(3,0,-1);
		}
		if(a >= 4 && a < 14){
			npMove(2,0,-1);
		}
		if(a >= 5 && a < 16){
			npMove(4,0,-1);
		}

		evFrame();
	}

	npDir(6,SOUTH);

	for(a = 0;a < 8;a ++){
		mcMove(0,-1);
		evFrame();
	}

	//---どっちからでも
	evFrameWait(500);
	mes.ReadDraw(2);

	//---戦力が
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---侵入者だ！
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---エターナル達
	npPos(7,42,44);
	npDir(7,WEST);
	npPos(8,43,45);
	npDir(8,WEST);
	npPos(9,42,46);
	npDir(9,WEST);
	for(a = 0;a < 18;a ++){
		if(a == 0){
			npDir(0,NORTH);
			npDir(5,EAST);
		}
		if(a == 1){
			npDir(0,EAST);
			npDir(4,EAST);
		}
		if(a == 2){
			npDir(6,EAST);
		}
		if(a == 3){
			npDir(2,EAST);
		}
		if(a == 4){
			npDir(3,EAST);
		}
		mcMove(1,0);
		evFrame();
	}
	evFrameWait(1000);
	for(a = 0;a < 18;a ++){
		mcMove(-1,0);
		evFrame();
	}

	//---ユミにおまかせ
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(4,1,0);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---わたしも！
	npMove(0,1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(3);
	evFrameWait(250);

	//---ここはわしらに
	npMove(5,1,0);
	evFrame();
	evFrameWait(250);
	npDir(5,NORTH);
	evFrameWait(250);
	npDir(5,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	//---シンディも
	evFrameWait(250);
	npDir(6,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	//---わかったわ
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(250);

	//---エターナル来る
	npPos(7,36,44);
	npPos(8,37,45);
	npPos(9,36,46);

	for(a = 0;a < 6;a ++){
		if(a < 5){
			npMove(7,-1,0);
			npMove(8,-1,0);
		}
		if(a)
			npMove(9,-1,0);
		if(a == 3)
			npDir(6,EAST);
		if(a == 4)
			npDir(5,NORTH);
		if(a == 5)
			npDir(5,EAST);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();

	//---行こうぜ
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(125);
	npDir(1,WEST);
	evFrameWait(125);
	npDir(0,WEST);
	evFrameWait(250);

	for(a = 0;a < 20;a ++){
		if(a)
			npMove(0,-1,0);
		npMove(1,-1,0);

		if(a == 0)
			npDir(3,NORTH);
		if(a == 2)
			npDir(3,WEST);
		if(a == 1)
			npDir(2,NORTH);
		if(a == 3)
			npDir(2,WEST);

		if(a >= 3)
			npMove(3,-1,0);
		if(a >= 4)
			npMove(2,-1,0);

		evFrame();
	}

	//----------------------------
	evFrameWait(250);

	npPos(0,8,29);
	npPos(1,7,29);
	npPos(2,6,30);
	npPos(3,9,30);

	npPos(10,7,8);
	npDir(10,SOUTH);
	npPos(11,9,7);
	npDir(11,SOUTH);
	evScene(1,7,18);

	evFrameWait(250);
	for(a = 0;a < 13;a ++){
		if(a)
			npMove(0,0,-1);
		if(a < 12)
			npMove(1,0,-1);
		if(a)
			npMove(2,0,-1);
		if(a)
			npMove(3,0,-1);

		if(a >= 6){
			npMove(10,0,1);
			npMove(11,0,1);
		}

		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);

	//---バトル
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = 0;
	BattleInfo.Enemy[0].Enemy = 189;
	BattleInfo.Enemy[0].x = 3;
	BattleInfo.Enemy[0].y = 9;
	BattleInfo.Enemy[1].Enemy = 188;
	BattleInfo.Enemy[1].x = 9;
	BattleInfo.Enemy[1].y = 7;
	BattleInfo.Enemy[2].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	evField(0,1);

	npDelete(10);
	npDelete(11);

	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}

	evFrameWait(500);
	for(a = 0;a < 10;a ++){
		mcMove(0,-1);
		evFrame();
	}
	for(a = 0;a < 9;a ++){
		mcMove(1,0);
		evFrame();
	}

	//---２Ｆへ
	crfieldChangeScene(2,5,13);
	npPos(0,5,3);
	npDir(0,SOUTH);
	npPos(1,4,3);
	npDir(1,SOUTH);
	npPos(2,3,3);
	npDir(2,SOUTH);
	npPos(3,6,3);
	npDir(3,SOUTH);

//	npPos(7,4,24);
//	npDir(7,NORTH);
	npPos(8,4/*5*/,23);
	npDir(8,NORTH);
	npPos(9,6,23);
	npDir(9,NORTH);

	evScene(2,5,13);

	evFrameWait(250);

	for(a = 0;a < 12;a ++){
		if(a >= 6 && a < 12)
			npMove(0,0,1);
		if(a >= 5 && a < 11)
			npMove(1,0,1);
		if(a >= 6 && a < 11)
			npMove(2,0,1);
		if(a >= 6 && a < 11)
			npMove(3,0,1);

//		if(a)
//			npMove(7,0,-1);
		if(a < 11)
			npMove(8,0,-1);
		if(a)
			npMove(9,0,-1);
		evFrame();
	}

	evFrameWait(250);
	mes.ReadDraw(6);
	evFrameWait(250);

	//---バトル
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = 0;
	BattleInfo.Enemy[0].Enemy = 191;
	BattleInfo.Enemy[0].x = 3;
	BattleInfo.Enemy[0].y = 9;
	BattleInfo.Enemy[1].Enemy = 186;
	BattleInfo.Enemy[1].x = 6;
	BattleInfo.Enemy[1].y = 7;
	BattleInfo.Enemy[2].Enemy = 188;
	BattleInfo.Enemy[2].x = 9;
	BattleInfo.Enemy[2].y = 7;
	BattleInfo.Enemy[3].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	evField(0,1);

//	npDelete(7);
	npDelete(8);
	npDelete(9);

	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}

	//---
	evFrameWait(250);
	for(a = 0;a < 20;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(250);

	//------------------------------------
	evScene(2,14,35);

	npPos(0,4,34);
	npPos(1,4,36);
	npPos(2,3,35);
	npPos(3,3,33);

	evFrameWait(250);
	for(a = 0;a < 11;a ++){
		if(a < 10)
			npMove(0,1,0);
		if(a >= 1)
			npMove(1,1,0);
		if(a < 10)
			npMove(2,1,0);
		if(a >= 1)
			npMove(3,1,0);
		evFrame();
	}
	mes.CloseMessage();

	//---どのくらいの数の
	evFrameWait(250);
	mes.OpenMessage("Daishinden.msg",101);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---おししょうさまたち
	evFrameWait(250);
	npDir(2,SOUTH);
	evFrameWait(250);
	npDir(2,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---騒がしくない？
	evFrameWait(500);
	npDir(0,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(1,EAST);
	npDir(2,SOUTH);
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);

	//---外
	evScene(0,24,32);

	for(a = 6;a <= 12;a ++){
		npDelete(a);
	}

	npPos(0,24,48);
	npDir(0,SOUTH);
	npPos(1,22,46);
	npDir(1,SOUTH);
	npPos(2,25,47);
	npDir(2,SOUTH);
	npPos(3,23,46);
	npDir(3,SOUTH);
	npPos(4,26,46);
	npDir(4,SOUTH);
	npPos(24,25,43);
	npDir(24,SOUTH);
	npPos(25,26,43);
	npDir(25,SOUTH);

	//---
	npPos(13,24,50);
	npDir(13,NORTH);
	npPos(14,23,51);
	npDir(14,NORTH);
	npPos(15,25,51);
	npDir(15,NORTH);
	evReadObject(7,"TwPpl3m.acf");
	npPos(23,26,51);
	npDir(23,NORTH);

	npPos(16,21,52);
	npDir(16,NORTH);
	npPos(17,23,52);
	npDir(17,NORTH);
	npPos(18,25,52);
	npDir(18,NORTH);
	npPos(19,27,52);
	npDir(19,NORTH);
	npPos(20,22,53);
	npDir(20,NORTH);
	npPos(21,24,53);
	npDir(21,NORTH);
	npPos(22,28,53);
	npDir(22,NORTH);

	npPos(26,20,54);
	npDir(26,NORTH);
	npPos(27,22,54);
	npDir(27,NORTH);
	npPos(28,23,54);
	npDir(28,NORTH);
	npPos(29,27,54);
	npDir(29,NORTH);

	npPos(30,21,55);
	npDir(30,NORTH);
	npPos(31,23,55);
	npDir(31,NORTH);
	npPos(32,26,55);
	npDir(32,NORTH);
	npPos(33,28,55);
	npDir(33,NORTH);

	npPos(34,20,56);
	npDir(34,NORTH);
	npPos(35,22,56);
	npDir(35,NORTH);
	npPos(36,23,56);
	npDir(36,NORTH);
	npPos(37,26,56);
	npDir(37,NORTH);

	npPos(38,21,57);
	npDir(38,NORTH);
	npPos(39,24,57);
	npDir(39,NORTH);
	npPos(40,25,57);
	npDir(40,NORTH);
	npPos(41,28,57);
	npDir(41,NORTH);

	npPos(42,22,58);
	npDir(42,NORTH);
	npPos(43,23,58);
	npDir(43,NORTH);
	npPos(44,26,58);
	npDir(44,NORTH);
	npPos(45,27,58);
	npDir(45,NORTH);

	//---誰だね
	evFrameWait(250);
	for(a = 0;a < 20;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---再び中
	evScene(2,14,35);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---責任
	evScene(0,24,52);
	evFrameWait(250);
	mes.ReadDraw();

	//---かわゆいこが
	evFrameWait(250);
	npMove(23,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---今こそ
	evFrameWait(250);
	npMove(14,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---んだす
	evFrameWait(250);
	npMove(15,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---またまた中へ
	evScene(2,14,35);
	//---みんな
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---おっし
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);


	npPos(10,23,34);
	npDir(10,WEST);
	npPos(11,24,36);
	npDir(11,WEST);

	//---挟み撃ち
	for(a = 0;a < 4;a ++){
		npMove(0,1,0);
		npMove(1,1,0);

		if(a == 0)
			npDir(2,EAST);
		if(a == 1)
			npDir(3,EAST);
		if(a >= 1)
			npMove(2,1,0);
		if(a >= 2)
			npMove(3,1,0);

		if(a){
			npMove(10,-1,0);
			npMove(11,-1,0);
		}
		evFrame();
	}
	for(a = 0;a < 4;a ++){
		mcMove(1,0);
		evFrame();
	}
	evFrameWait(250);

	npPos(12,8,34);
	npDir(12,WEST);
	evReadObject(12,"deathm.acf");
	npPos(13,8,35);
	npDir(13,WEST);
	for(a = 0;a < 5;a ++){
		npMove(12,1,0);
		npMove(13,1,0);
		if(a == 2)
			npDir(3,SOUTH);
		if(a == 4)
			npDir(3,WEST);
		evFrame();
	}
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);
	npDir(2,WEST);
	evFrameWait(250);

	//---さからうことは
	mes.ReadDraw(2);

	//---この新兵器
	evFrameWait(250);
	npDir(12,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(12,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);


	//---バトル
	memset(&BattleInfo,0,sizeof(BattleInfo));

	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = 0;
	BattleInfo.Enemy[0].Enemy = 186;//---上
	BattleInfo.Enemy[0].x = 3;
	BattleInfo.Enemy[0].y = 10;
	BattleInfo.Enemy[1].Enemy = 188;
	BattleInfo.Enemy[1].x = 8;
	BattleInfo.Enemy[1].y = 10;
	BattleInfo.Enemy[2].Enemy = 187;
	BattleInfo.Enemy[2].x = 3;
	BattleInfo.Enemy[2].y = 2;
	BattleInfo.Enemy[3].Enemy = 190;
	BattleInfo.Enemy[3].x = 9;
	BattleInfo.Enemy[3].y = 3;
	BattleInfo.Enemy[4].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	//---挟み撃ち！
	BattleInfo.Friend[3].x = 4;
	BattleInfo.Friend[3].y = 5;
	BattleInfo.Friend[2].x = 7;
	BattleInfo.Friend[2].y = 5;
	BattleInfo.Friend[1].x = 6;
	BattleInfo.Friend[1].y = 7;
	BattleInfo.Friend[0].x = 4;
	BattleInfo.Friend[0].y = 7;
	BattleInfo.EnableFriendPos = 1;
	BattleInfo.OffsetBattle = 0;//OFFSETBAT_HASAMIUCHI;
	evField(0,1);

	npDelete(10);
	npDelete(11);
	npDelete(12);
	npDelete(13);
	npDir(2,EAST);
	npDir(3,EAST);

	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}

	evFrameWait(250);
	for(a = 0;a < 4;a ++){
		mcMove(1,0);
		evFrame();
	}
	for(a = 0;a < 4;a ++){
		npMove(0,1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	//---この先が中心部？
	mes.ReadDraw();

	evFrameWait(250);
	for(a = 0;a < 3;a ++){
		npMove(1,1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	for(a = 0;a < 3;a ++){
		mcMove(0,-1);
		evFrame();
	}
	for(a = 0;a < 2;a ++){
		npMove(2,1,0);
		if(a)
			npMove(3,1,0);
		evFrame();
	}

	for(a = 0;a < 20;a ++){
		if(a < 6)
			npMove(0,0,-1);
		else
			npDelete(0);

		if(a < 9)
			npMove(1,0,-1);
		else
			npDelete(1);

		if(a < 5)
			npMove(2,1,0);
		else if(a < 12)
			npMove(2,0,-1);
		else
			npDelete(2);

		if(a < 4)
			npMove(3,1,0);
		else if(a < 9)
			npMove(3,0,-1);
		else
			npDelete(3);

		evFrame();
	}

	mes.CloseMessage();

	evReadObject(7,"Crasive.acf");

	return creventKojinsaiChushinbu();

//	return 1;
}

#define KJ_MAX 32

typedef struct
{
	int np;
	float x,y,sx,sy,cx,cy,ex,ey;
	int max_time,now_time,delay;
	int flag;
	int anime_count,anime_pos;
} KJ_SEISHIN;

typedef struct
{
	int np;
} SHINE;

void kj_Make(KJ_SEISHIN *pkj,int number,int delay,int mode = 0)
{
	int px,py,x = ef->xGet(),y = ef->yGet();
	int dx,dy;
	eiMapObject *ob;

	int cx = 27,cy = 20,ex,ey;

	if(mode == 1){
		//---クレイシヴの腕
		cy = 23;
		cx = 10;
	}

	memset(pkj,0,sizeof(KJ_SEISHIN));

	pkj->np = number;

	ob = npGet(number);

	dx = (ob->xGet() - cx);
	dy = (ob->yGet() - cy);

	px = (ob->xGet() - x) * 32 + 320 - 16;
	py = (ob->yGet() - y) * 32 + 240 - 16;
	ex = (cx - x) * 32 + 320 - 16;
	ey = (cy - y) * 32 + 240 - 16;

	pkj->x = (float)px;
	pkj->y = (float)py;
	pkj->sx = (float)px;
	pkj->sy = (float)py;
	pkj->cx = (float)px * 0.25f + (float)ex * 0.75f;
	pkj->cy = (float)ey - (float)dy * 8.0f;
	pkj->ex = (float)ex;
	pkj->ey = (float)ey;
	pkj->flag = 1;

	pkj->max_time = 1500 + eiRnd(1000);
	if(mode == 1){
		pkj->max_time = 1000;
		pkj->cx = 150.0f;
		pkj->cy = 180.0f;
	}
	pkj->now_time = pkj->max_time;
	pkj->delay = delay;

	pkj->anime_count = 0;
	pkj->anime_pos = 0;
}

void kj_Move(KJ_SEISHIN *pkj,int delta)
{
	//---ディレイ
	if(pkj->delay > 0){
		pkj->delay -= delta;
		if(pkj->delay <= 0){
			pkj->delay = 0;
		} else {
			return;
		}
	}

	pkj->now_time -= delta;
	if(pkj->now_time <= 0){
		//---終わり
		pkj->now_time = 0;
		pkj->flag = 0;
	}

	float norm = (float)(pkj->max_time - pkj->now_time) / (float)pkj->max_time;

	pkj->x = pkj->sx + ( -3*pkj->sx + 4*pkj->cx - pkj->ex) * norm
		+ (2*pkj->sx - 4*pkj->cx + 2*pkj->ex) * norm * norm;

	pkj->y = pkj->sy + ( -3*pkj->sy + 4*pkj->cy - pkj->ey) * norm
		+ (2*pkj->sy - 4*pkj->cy + 2*pkj->ey) * norm * norm;

	//---アニメ
	pkj->anime_count += delta;
	if(pkj->anime_count >= 100){
		pkj->anime_count -= 100;
		if(++pkj->anime_pos >= 3){
			pkj->anime_pos = 0;
		}
	}
}

int kj_GetEmpty(KJ_SEISHIN *pkj)
{
	int a;

	for(a = 0;a < KJ_MAX;a ++){
		if(pkj[a].flag == 0)
			return a;
	}

	return -1;
}

#define S_MAX 30

static KJ_SEISHIN kj[KJ_MAX + 2];
static eiCell kjcell[12];
static SHINE shine[S_MAX + 2];

//---輝き
void shine_Delete(int np)
{
	int a;
	eiMapObject *ob;

	for(a = 0;a < S_MAX;a ++){
		if(shine[a].np == np){
			ob = npGet(np);

			ob->SetPattern(ob->GetPattern() + 4);
			npDir(np,eiRnd(2) == 0 ? NORTH : SOUTH);

			npPos(100 + a,0,0);

			shine[a].np = 0;

			return;
		}
	}
}

void shine_Make(int np)
{
	int a;
	eiMapObject *ob;

	for(a = 0;a < S_MAX;a ++){
		if(shine[a].np == 0){
			shine[a].np = np;

			ob = npGet(np);
			npPos(100 + a,ob->xGet(),ob->yGet());
			npDir(100 + a,NORTH);

			return;
		}
	}
}

int shine_GetNewNP(int *pshine)
{
	int count,np = eiRnd(100);

	for(count = 0;pshine[np] == 1 && count < 100;count ++){
		if(++np >= 100)
			np = 0;
	}

	return np;
}

void kojinsai_seishintai(int kj_count,int *pshine,int run_time,int m_delay,int s_delay)
{
	int a,delta = 0,num;
	eiTime let,let2;

	let2.Reset();
	kj_count = 12;

	for(a = 0;a < kj_count;a ++){
		num = kj_GetEmpty(kj);

		kj_Make(&kj[num],shine_GetNewNP(pshine),a * s_delay + m_delay);
		shine_Make(kj[num].np);
		pshine[kj[num].np] = 1;
	}
	while(let2.Get() < run_time){
		let.Reset();

		for(a = 0;a < KJ_MAX;a ++){
			if(kj[a].flag){
				kj_Move(&kj[a],delta);

				if(kj[a].flag == 0 && kj[a].np != 0){
					shine_Delete(kj[a].np);
					kj[a].np = 0;
				}
			}
		}
		evFrameWait(10);

		delta = let.Get() + 1;
	}
}

void crevent_KojinsaiFGCallback(eiCell *pScrCell,int sx,int sy,int top_x,int top_y,int delta_t)
{
	int a;

	for(a = 0;a < KJ_MAX;a ++){
		if(kj[a].flag && kj[a].delay <= 0){
			kjcell[kj[a].anime_pos].PutTransClip(pScrCell,(int)kj[a].x,(int)kj[a].y);
		}
	}
}

//---降神祭、中心部
CREVENTLONG7_API int creventKojinsaiChushinbu(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
crmusicPlay(CRMUSIC_BREAKFORTUNE);

//----------------------------------------
	//---ステージ下に出る
	crfieldChangeScene(3,27,42);

	npPos(0,27,37);
	npDir(0,NORTH);
	npPos(1,26,37);
	npDir(1,NORTH);
	npPos(2,28,38);
	npDir(2,NORTH);
	npPos(3,27,38);
	npDir(3,NORTH);

	npPos(7,27,19);
	npDir(7,SOUTH);

	evScene(3,27,42);
	evFrameWait(250);

	for(a = 0;a < 5;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(1000);

	crmusicFadeOut();
	for(a = 0;a < 16;a ++){
		mcMove(0,-1);
		evFrame();
	}
	//---クレイシヴ！
	evFrameWait(1000);
	crmusicPlay(CRMUSIC_SILENT);
	mes.OpenMessage("Daishinden.msg",102);
	mes.ReadDraw();
	evFrameWait(2000);

	//---何か言ったらどうなの？
	for(a = 0;a < 16;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(500);
	npMove(0,0,-1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	for(a = 0;a < 16;a ++){
		mcMove(0,-1);
		evFrame();
	}
	//---見よ！
	evFrameWait(4000);
	npMove(7,0,1);
	evFrameWait(500);
	mes.ReadDraw();

	//---は
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	for(a = 0;a < 16;a ++){
		mcMove(0,1);
		evFrame();
	}
	//---何を今更
	evFrameWait(500);
	npMove(1,0,-1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	for(a = 0;a < 7;a ++){
		mcMove(0,-1);
		evFrame();
	}

	for(a = 8;a <= 99;a += 6){
		npDir(a,SOUTH);
		npDir(a + 3,SOUTH);
		evFrameWait(50);
	}
	for(a = 9;a <= 99;a += 6){
		npDir(a,SOUTH);
		npDir(a + 3,SOUTH);
		evFrameWait(50);
	}
	for(a = 10;a <= 99;a += 6){
		npDir(a,SOUTH);
		npDir(a + 3,SOUTH);
		evFrameWait(50);
	}

	evFrameWait(500);
	//---わーーーーーーー！！
	crmusicPlay(CRMUSIC_CRAYSIVE);
	crsoundPlay(CRSOUND_KANSEI,EISOUND_PLAYLOOP);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---すごい声、
	for(a = 0;a < 7;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(500);
	npMove(0,0,1,0);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---予言通り
	for(a = 0;a < 12;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(1000);
	mes.ReadDraw();

	for(a = 8;a <= 99;a += 6){
		npDir(a,NORTH);
		npDir(a + 3,NORTH);
		evFrameWait(50);
	}
	for(a = 9;a <= 99;a += 6){
		npDir(a,NORTH);
		npDir(a + 3,NORTH);
		evFrameWait(50);
	}
	for(a = 10;a <= 99;a += 6){
		npDir(a,NORTH);
		npDir(a + 3,NORTH);
		evFrameWait(50);
	}
	//---わーーーーーー！
	evFrameWait(100);
	mes.ReadDraw();

	//---耳が・・・
	evFrameWait(1000);
	mes.ReadDraw();

	//---永き
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---先生は・・・
	evFrameWait(1000);
	mes.ReadDraw();

	//---永き
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	//---うるさくて
	evFrameWait(1000);
	mes.ReadDraw();
//	evFrameWait(1000);

	//---初期化
	int npnum = 88;
	int np_shine[100];

	memset(kj,0,sizeof(kj));
	memset(shine,0,sizeof(shine));
	memset(np_shine,0,sizeof(np_shine));
	for(a = 0;a < 8;a ++){
		np_shine[a] = 1;
	}

	//---精神体
	eiCellReadPattern(kjcell,
		CR_DATADIR2"kj_seishin.acf",CR_DATAFILE2,crdataGetFileMode(),
		0,3,32,32);
	eiCellSetSurface(kjcell,
		0,240,32,32,3,3);

	evReadObject(12,"TwEtl1m_down.acf");
	evReadObject(13,"TwEtl1w_down.acf");
	evReadObject(14,"TwEtl2m_down.acf");
	evReadObject(15,"TwEtl2w_down.acf");
	//---光出す
	evReadObject(6,"ShinePeople.acf");


	evFrameWait(1000);

	ef->SetFGCallback(crevent_KojinsaiFGCallback);
	int delta = 0;
	eiTime let,let2;
	int kj_count = 0;

	shine_Make(npnum);
	np_shine[npnum] = 1;

	kj_Make(&kj[0],npnum,0);
	while(kj[0].now_time > 0){
		let.Reset();

		kj_Move(&kj[0],delta);
		evFrameWait(10);

		delta = let.Get() + 1;
	}
	//---
	evFrameWait(1000);
	//---倒れる
	shine_Delete(npnum);
	evFrameWait(500);

	//---なに！？
	mes.ReadDraw();

	//---みよ
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---次々と
	evFrameWait(500);

	//----------------------
	kojinsai_seishintai(12,np_shine,8000 ,1000,300);

/*	let2.Reset();
	kj_count = 12;

	for(a = 0;a < kj_count;a ++){
		kj_Make(&kj[a],shine_GetNewNP(np_shine),a * 300 + 1000);
		shine_Make(kj[a].np);
		np_shine[kj[a].np] = 1;
	}
	while(let2.Get() < 6000){
		let.Reset();

		for(a = 0;a < kj_count;a ++){
			kj_Move(&kj[a],delta);

			if(kj[a].flag == 0 && kj[a].np != 0){
				shine_Delete(kj[a].np);
				kj[a].np = 0;
			}
		}
		evFrameWait(10);

		delta = let.Get() + 1;
	}*/

	//---なんなの！？
	evFrameWait(500);
	mes.ReadDraw();

	//---
	kojinsai_seishintai(10,np_shine,7000 ,1000,300);

	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	for(a = 0;a < 12;a ++){
		mcMove(0,1);
		evFrame();
	}
	//---こころ？
	evFrameWait(1000);
	mes.ReadDraw();
	//---やめて！！
	evFrameWait(250);
	npMove(0,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);


	for(a = 0;a < 12;a ++){
		mcMove(0,-1);
		evFrame();
	}
	//---
	kojinsai_seishintai(10,np_shine,2000 ,1000,200);
	//---
	kojinsai_seishintai(10,np_shine,2000 ,500,200);
	//---
	kojinsai_seishintai(10,np_shine,2000 ,500,200);
	//---
	kojinsai_seishintai(10,np_shine,4000 ,500,200);

	ef->SetFGCallback(NULL);

	kjcell[2].Release();
	kjcell[1].Release();
	kjcell[0].Release();

	crmusicFadeOut();
	evFadeOut(500,RGB_MAKE(255,255,255));

	crsoundStop(CRSOUND_KANSEI);
	et->Delay2(5000);

//---みんな倒れている
	eiMapObject *np;
	for(a = 100;a < 100 + S_MAX;a ++){
		npPos(a,0,0);
	}
	for(a = 8;a <= 99;a ++){
		np = npGet(a);
		if(np->GetPattern() < 12){
			np->SetPattern(np->GetPattern() + 4);
			npDir(a,eiRnd(2) == 0 ? NORTH : SOUTH);
		}
	}

	crmusicPlay(CRMUSIC_SILENT);
	evFieldNoFlip(0,1);
	//-------------------------------------------------
	evFadeIn(2000,RGB_MAKE(255,255,255));

	evFrameWait(500);

	int old = ef->SetMoveSpeed(2);
/*	for(a = 0;a < 10;a ++){
		mcMove(1,0);
		evFrame();
	}
	for(a = 0;a < 6;a ++){
		mcMove(0,1);
		evFrame();
	}
	for(a = 0;a < 16;a ++){
		mcMove(-1,0);
		evFrame();
	}
	for(a = 0;a < 7;a ++){
		mcMove(0,1);
		evFrame();
	}*/
	for(a = 0;a < 13;a ++){
		mcMove(0,1);
		evFrame();
	}

	//---うそだよね
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();


	//---見よ
	for(a = 0;a < 17;a ++){
		mcMove(0,-1);
		evFrame();
	}

	//---ユミが来る
	evReadObject(6,"Cindy.acf");
	evFrameWait(1000);
	for(a = 0;a < 6;a ++){
		mcMove(1,0);
		evFrame();
	}
	npPos(4,37,16);
	npDir(4,SOUTH);
	npPos(5,37,16);
	npPos(6,37,16);
	for(a = 0;a < 6;a ++){
		if(a < 3)
			npMove(4,0,1);
		else if(a < 5)
			npMove(4,-1,0);
		else
			npDir(4,SOUTH);

		if(a < 2){
		} else if(a < 4)
			npMove(6,0,1);
		else if(a < 5)
			npMove(6,-1,0);

		if(a < 4){
		} else if(a < 6)
			npMove(5,0,1);
		else
			npMove(5,-1,0);

		evFrame();
	}
	//---これは・・・
	evFrameWait(500);
	mes.ReadDraw(2);

	//---カメラ、クレイシヴへ
	evFrameWait(1000);
	for(a = 0;a < 6;a ++){
		mcMove(-1,0);
		evFrame();
	}
	//---シルバーリング
	evReadObject(8,"Silver.acf");
	evReadObject(7,"Crasive2.acf");

	npDir(7,SOUTH);
	evFrameWait(1000);

	//---シルバーリングを出す
	evFrameWait(1000);
	np = npGet(100);
	np->SetPattern(8);
	npPos(100,27,20);
	npDir(100,EAST);
	npDir(7,NORTH);

	evFrameWait(500);
	npDir(4,WEST);
	evFrameWait(2000);
	mes.ReadDraw();

	evFrameWait(1000);

	ef->SetMoveSpeed(old);

	//---
	for(a = 0;a < 17;a ++){
		mcMove(0,1);
		evFrame();
	}
	//---シルバーリング！？
	evFrameWait(500);
	mes.ReadDraw(2);


	//---あまたの
	evFrameWait(500);
	for(a = 0;a < 13;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(500);
	npDir(7,SOUTH);
	evReadObject(7,"Crasive.acf");
	npPos(100,0,0);
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(1000);
	mes.ReadDraw();

	//---ふざけるなよ
	for(a = 0;a < 13;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(250);
	npMove(1,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---行くぞ
	for(a = 0;a < 13;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(1000);
	mes.ReadDraw();

	for(a = 0;a < 13;a ++){
		mcMove(0,1);
		evFrame();
	}
	//---馬鹿なこと
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	crmusicPlay(CRMUSIC_FATEDFORCE);
	npMove(0,0,-1);
	evFrame();
	//---ルナン！？
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	//---ディザ前に出る
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(1,0,-1);
		else
			npMove(1,1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(1,SOUTH);
	//---どいてくれる？
	evFrameWait(500);
	mes.ReadDraw();

	//--どうしたんだよ！？
	evFrameWait(250);
	mes.ReadDraw(2);

	//---お願い！！
	evFrameWait(1000);
	mes.ReadDraw(3);

	//---これが
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---そう
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---それはできない
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---わたしはそう生まれた
	evFrameWait(1000);
	mes.ReadDraw();

	//---何をしている
	evFrameWait(500);
	for(a = 0;a < 13;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();

	//---はい
	evFrameWait(500);
	for(a = 0;a < 13;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw(2);

	//---だったら、
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---ディザ、やめなさい！
	evFrameWait(250);
	for(a = 0;a < 13;a ++){
		mcMove(0,-1);
		evFrame();
	}
	for(a = 0;a < 5;a ++){
		if(a < 1)
			npMove(4,0,1);
		else if(a < 4)
			npMove(4,-1,0);
		else
			npMove(4,0,1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---本当に
	mes.ReadDraw(2);
	evFrameWait(500);

	//---・・・
	for(a = 0;a < 13;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(1000);
	mes.ReadDraw();
	//---どく
	evFrameWait(1000);
	npDir(1,EAST);
	evFrameWait(500);
	npMove(1,-1,0,0);
	evFrame();
	evFrameWait(1000);

	//---みんな、ごめん
	npMove(0,0,-1);
	evFrame();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

	old = ef->SetMoveSpeed(2);
	for(a = 0;a < 16;a ++){
		if(a < 3)
			npMove(0,0,-1);
		else if(a < 4)
			npMove(0,1,0);
		else if(a < 6)
			npMove(0,0,-1);
		else if(a < 7)
			npMove(0,-1,0);
		else if(a < 9)
			npMove(0,0,-1);
		else if(a < 10)
			npMove(0,-1,0);
		else if(a < 13)
			npMove(0,0,-1);
		else if(a < 14)
			npMove(0,1,0);
		else if(a < 16)
			npMove(0,0,-1);
		if(a > 2)
			mcMove(0,-1);
		if(a == 2)
			npDir(1,NORTH);
		if(a == 14){
			npDir(4,WEST);
			npDir(5,WEST);
			npDir(6,WEST);
		}
		evFrame();
	}
	ef->SetMoveSpeed(old);

	//---先生どこへ！？
	evFrameWait(1500);
	for(a = 0;a < 13;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(250);
	for(a = 0;a < 3;a ++){
		npMove(3,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---黒き絶望
	for(a = 0;a < 13;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(1000);
	npDir(7,WEST);
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(2000);

	//---クレイシヴ去る
	for(a = 0;a < 12;a ++){
		npMove(7,-1,0);
		evFrame();
		if(a < 2)
			evFrameWait(500);
		else
			evFrameWait(300);

		if(a == 1){
			npDir(0,WEST);
		} else if(a > 1){
			npMove(0,-1,0);
			evFrame();
		}
	}

	//---
	for(a = 0;a < 13;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(1000);
	npMove(2,0,-1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	//---オイルレイク？
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

	//---ぐずぐずしてないで！
	for(a = 0;a < 13;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(250);
	for(a = 0;a < 4;a ++){
		if(a < 3)
			npMove(4,-1,0);
		else
			npMove(4,0,1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	mes.CloseMessage();

	return creventKojinsaiOilLake();
}


//---行列セット
static eiD3DMatrix matWorld,matProjection,matView;

CRBATTLEDRAW_API void olSetMatrix(int number)
{

	//---ワールド行列初期化
	matWorld.IdentityMatrix();
	matWorld.Set(3,0,0.0f);
	matWorld.Set(3,1,0.0f);
	matWorld.Set(3,2,0.0f);

	eid3d->SetTransformWorld(&matWorld);

	//---ビュー行列設定
	matView.SetCalcCamera(1.00f,2.00f,1.00f);
	matView.CalcCamera(
		D3DVECTOR(0,5,-5),
		D3DVECTOR(0,0.0f,20),
		D3DVECTOR(0.0f,1.0f,0.0f),0);

	eid3d->SetTransformView(&matView);

	//---プロジェクション行列設定
	matProjection.CalcProjectionMatrix(0.25f,4000.0f,3.14f / 4.0f);
	eid3d->SetTransformProjection(&matProjection);
}

//extern eiD3DParticle BatPart[BATTLE_PARTMAX];

//---蒸発！
CREVENTLONG7_API int creventKojinsaiOilLake_Johatu(void)
{
	int a,c = 0;
	RECT rect = {0,0,640,480};
	eiCell src,bg;
	eiTextureCell mask;
	D3DTLVERTEX tex[4];
	eiTime let,let2;
	
	int r = 255,
		g = 255,
		b = 255;
	int alpha = 255;
	int Start,RunTime = 2000,flag,now;

	crefectSetup3DEfect();
	memset(&tex[0],0,sizeof(tex));

	for(a = 0;a < 4;a ++){
		tex[a].dvRHW = 1;
		tex[a].dcSpecular = 0;
	}

	tex[0].dvSX = (float)0;
	tex[0].dvSY = (float)0;
	tex[0].dvSZ = (float)0.0f;
	tex[0].tu = 0;
	tex[0].tv = 0;

	tex[1].dvSX = (float)639;
	tex[1].dvSY = (float)0;
	tex[1].dvSZ = (float)0.0f;
	tex[1].tu = 1.0f;
	tex[1].tv = 0;

	tex[2].dvSX = (float)0;
	tex[2].dvSY = (float)479;
	tex[2].dvSZ = (float)0.0f;
	tex[2].tu = 0;
	tex[2].tv = 192.0f / 256.0f;

	tex[3].dvSX = (float)639;
	tex[3].dvSY = (float)479;
	tex[3].dvSZ = (float)0.0f;
	tex[3].tu = 1.0f;
	tex[3].tv = 192.0f / 256.0f;


	evFadeOut(1000);

	//---画像
	src.ReadFile(CR_DATADIR1"OLbefore.acf",CR_DATAFILE1,crdataGetFileMode());
	//---復元
	decode_image(&bg,&src,NULL);
	src.SetSurface(&rect,3,0);
	src.Release();

	mask.ReadFile(CR_DATADIR1"OLmasktex.acf",CR_DATAFILE1,crdataGetFileMode());
	mask.Init(16);
	mask.Load(1);

	bg.Put(ew->lpCell[1],0,0);

	if(!crsysQuick()){
		crefectScreenEfect_FadeOut(&rect,1000,RGB_MAKE(0,0,0),1);
		et->Delay2(2000);
	}

	//---色が変わる
	for(Start = let.GetTime() , flag = 1;flag == 1;){
		now = let.GetTime() - Start;
		if(now >= RunTime){
			flag = 0;
			now = RunTime;
		}

		alpha = (int)( ((float)(now) / (float)RunTime) * 192.0f );
//		alpha = 255 - alpha;

		for(a = 0;a < 4;a ++){
			tex[a].dcColor = RGBA_MAKE(r,g,b,alpha);
		}

		pViewport->ClearAll();
		bg.Put(ew->lpCell[1],0,0);

		//---描画開始
		if(eid3d->Begin()){
			eid3d->BeginAlphaBlend();
			eid3d->SetTexture(&mask);
			eid3d->SetTextureColorkey(1);
			eid3d->SetDrawMode(EID3D_DRAWMODE_FILL);

			eid3d->DrawPrimitive( D3DPT_TRIANGLESTRIP,
				D3DFVF_TLVERTEX,&tex[0], 4, D3DDP_WAIT);

			//---描画終了
			eid3d->SetTextureColorkey(0);
			eid3d->SetTexture(NULL);
			eid3d->EndAlphaBlend();
			eid3d->End();
		}

		if(eiGetEndThread() || crsysQuick()){
			break;
		}

		//---フリップ
		ew->Flip();
		if(!eiGetFullScreen()){
			eiSleep(1);
		}
	}

	//---------------------------------------------------------
	//---カメラ設定
	int lm,z,x,y,ver_count = 0,max_x = 30,max_y = 36,t;
	eiD3DMaterial material;
	float addw = 0,speed = 0.0001f;
	eiD3DParticle *part = new eiD3DParticle[2000];

	material.Create();
	material.SetDeffuseColor(255,255,255,127);
	material.SetEmissiveColor(255,255,255,255);
	material.SetAmbientColor(255,255,255,127);
	material.Set();

	pViewport->SetRect((D3DRECT *)&rect);
	pViewport->Set();

	(eiGetSurfacePointer() + 1)->Put((eiGetSurfacePointer() + 3),0,0,NULL);

	for(y = 0;y < max_y;y ++){
		max_x = (int)((float)(y + 1) * 1.10f) + 2;
		lm = 1;
		if(y < 11)
			lm = 3;
		for(z = 0;z < lm;z ++){
		for(x = 0;x < max_x;x ++){
			memset(&part[ver_count].Info,0,sizeof(part[ver_count].Info));
			memset(&part[ver_count + 1].Info,0,sizeof(part[ver_count].Info));
			part[ver_count].CreateTriangle(
				-0.5f,0.01f,-0.5f,
				0.5f,0.01f,-0.5f,
				-0.5f,0.01f,0.5f);

			part[ver_count + 1].CreateTriangle(
				0.5f,0.01f,-0.5f,
				0.5f,0.01f,0.5f,
				-0.5f,0.01f,0.5f);

			for(a = 0;a < 2;a ++){
				part[ver_count + a].SetWorldPos(
					(float)((float)x - (float)(max_x / 2.0f)) * 2.0f + (float)z * 0.5f,
					0.0f,
					(float)y * 4.0f - 20.0f + (float)z * 0.5f
				);
				part[ver_count + a].SetRotationMode(1);
				part[ver_count + a].SetMoveSpeed(0.01f);
				part[ver_count + a].Info.data = (float)eiRnd(1000) / 10000.0f;
				part[ver_count + a].SetMoveSpeed(part[ver_count + a].Info.data);
				part[ver_count + a].SetMoveVectorXYZ(
					0.0f,
					0.15f,
					0.0f
				);
				part[ver_count + a].SetMoveRotation(
					(float)eiRnd(1000) / 50000.0f,
					(float)eiRnd(1000) / 50000.0f);
			}
			ver_count += 2;
		}
		}
	}
/*	char s[20];
	sprintf(s,"ver:%d\n",ver_count);
	eiDebugWriteFile(s);
*/
	let2.Reset();

	while(let2.Get() < 6000){
		let.Reset();

		t = let2.Get();
		if(t < 2500){
			material.SetDeffuseColor(255,255,255,
				(int)(127.0f * ((float)t / 2500.0f)));
		}

		if(eid3d->Begin()){
			pViewport->ClearZBuffer();
			eid3d->End();
		}

//		(eiGetSurfacePointer() + 3)->Put((eiGetSurfacePointer() + 1),0,0,NULL);
		(eiGetSurfacePointer() + 3)->PutExtend2((eiGetSurfacePointer() + 1),NULL,NULL,DDBLT_WAIT);

		if(eid3d->Begin()){
			eid3d->BeginAlphaBlend();
			crbatSetAddAlpha();
			//---行列セット
			olSetMatrix(0);
			eid3d->SetMaterial(&material);
			eid3d->SetTexture(NULL);
			eid3d->SetDrawMode(EID3D_DRAWMODE_CULLNONE);
			eid3d->SetAmbientLight(RGBA_MAKE(255,255,255,255));

			for(a = 0;a < ver_count;a ++){
				part[a].SetMoveSpeed(part[a].Info.data * t * 0.0002f + 0.001f);
				part[a].MoveFrame((float)addw);
				part[a].Draw();
			}

			eid3d->SetMaterial(NULL);
			eid3d->EndAlphaBlend();
			eid3d->End();
		}

		if(eiGetEndThread() || crsysQuick()){
			break;
		}

		ew->Flip();
		if(!eiGetFullScreen()){
			eiSleep(1);
		}

		addw = (float)let.Get() / 10.0f;
	}
	material.Release();

	for(a = 0;a < ver_count;a ++){
		part[a].Release();
	}
	delete []part;
	mask.ReleaseTexture();
	bg.Release();

	if(!crsysQuick()){
		crefectScreenEfect_FadeOut(&rect,2000,RGB_MAKE(255,255,255),0);
		et->Delay2(3000);
	}

	//--------------------------------
	//---画像
	src.ReadFile(CR_DATADIR1"OLafter.acf",CR_DATAFILE1,crdataGetFileMode());
	//---復元
	decode_image(&bg,&src,NULL);
	src.SetSurface(&rect,3,0);
	src.Release();

	bg.Put(ew->lpCell[1],0,0);

	if(!crsysQuick()){
		crefectScreenEfect_FadeOut(&rect,6000,RGB_MAKE(255,255,255),1);
		et->Delay2(3000);
	}

	if(!crsysQuick()){
		crefectScreenEfect_FadeOut(&rect,2000,RGB_MAKE(0,0,0),0);
		et->Delay2(500);
	}

	//---壁紙再設定
	crbaseSetWallPaperSuraface();

	return 1;
}

//---オイルレイク、蒸発！！
CREVENTLONG7_API int creventKojinsaiOilLake(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

crmusicPlay(CRMUSIC_FATEDFORCE);
	mcShow(0);

	//---ＧＳ
	crfieldChangeMap(59,1,1,0);
	crfieldChangeScene(1,6,7);
	npPos(5,6,5);
	npDir(5,EAST);

	evFadeOut();
	em->Put(10,3,2,27);
	evFieldNoFlip(0,1);
	evFadeIn();

	crsoundPlay(CRSOUND_GS_FUMISUGI2,EISOUND_PLAYLOOP);

	evFrameWait(1000);
	npDir(1,NORTH);
	evFrameWait(250);
	//---もっと速く！
	mes.OpenMessage("Daishinden.msg",103);
	mes.ReadDraw(2);

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

	//---中央山脈北側

	//---フィールド
	mcShow(1);
	crfieldChangeMap(10,0,1,0);
	crfieldSetMainCharacter(3);
	mcDir(EAST);
	crsoundStop(CRSOUND_GS_FUMISUGI2);
	evScene(0,190 - 60 - 10,107 - 15 - 15);

	ef->SetMoveEnything(1);
	for(a = 0;a < 10;a ++){
		mcMove(1,0);
		evFrame();
	}
	for(a = 0;a < 7;a ++){
		mcMove(0,1);
		evFrame();
	}
	for(b = 0;b < 3;b ++){
		for(a = 0;a < 20;a ++){
			mcMove(1,0);
			evFrame();
		}
		for(a = 0;a < 5;a ++){
			mcMove(0,1);
			evFrame();
		}
	}
	for(a = 0;a < 8;a ++){
		mcMove(0,1);
		evFrame();
	}
	ef->SetMoveEnything(0);
	evFrameWait(250);
	mcShow(0);
	crfieldSetMainCharacter(1);

	//---ＧＳ
	crfieldChangeMap(59,1,1,0);
	crfieldChangeScene(1,6,7);
	npPos(5,6,5);
	npDir(5,EAST);

	evFadeOut();
	em->Put(10,3,2,27);
	evFieldNoFlip(0,1);
	evFadeIn();

	crsoundPlay(CRSOUND_GS_FUMISUGI2,EISOUND_PLAYLOOP);

	evFrameWait(500);
	//---着きました
	mes.ReadDraw();
	evFrameWait(500);

	//---オイルレイクへ
	evFadeOut();
	crsoundStop(CRSOUND_GS_FUMISUGI2);

	crfieldChangeMap(38,3,1,0);
	crfieldChangeScene(3,30,11);
	crfieldPaletteChange(PALETTE_SUNSET);

	npDelete(0);
	npDelete(1);
	npDelete(2);
	npDelete(5);
	npDelete(6);

	evFieldNoFlip(0,1);
	evFadeIn();

	npPos(8,30,1);
	npDir(8,SOUTH);
	npPos(9,29,1);
	npDir(9,SOUTH);
	npPos(10,31,1);
	npDir(10,SOUTH);
	npPos(11,30,1);
	npDir(11,SOUTH);
	npPos(12,29,1);
	npDir(12,SOUTH);
	npPos(13,31,1);
	npDir(13,SOUTH);

	evFrameWait(500);
	for(a = 0;a < 11;a ++){
		if(a < 10)
			npMove(8,0,1);
		if(a > 0 && a < 10){
			npMove(9,0,1);
		}
		if(a > 1 && a < 10){
			npMove(10,0,1);
			npMove(11,0,1);
		}
		if(a > 3){
			npMove(12,0,1);
		}
		if(a > 4){
			npMove(13,0,1);
		}
		evFrame();
	}

	evFrameWait(1000);

	npPos(14,27,22);
	npDir(14,WEST);
	npPos(7,28,23);
	npDir(7,WEST);


	//---ルナン！！
	for(a = 0;a < 13;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();

	//---何を！
	for(a = 0;a < 13;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();

	//---やれ！
	for(a = 0;a < 13;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---ルナンが前に出る
	for(a = 0;a < 2;a ++){
		npMove(7,-1,0);
		evFrame();
		evFrameWait(500);
	}
	evFrameWait(1000);

	int old = ef->SetMoveSpeed(2);

	for(a = 0;a < 8;a ++){
		mcMove(-1,0);
		evFrame();
	}
	evFrameWait(500);

	//-----------------------------------------
	//---蒸発！！
	creventKojinsaiOilLake_Johatu();


	crfieldChangeScene(6,ef->xGet(),ef->yGet());

	npPos(14,27,22);
	npDir(14,WEST);
	npPos(7,26,23);
	npDir(7,WEST);

	npPos(8,29,18);
	npDir(8,SOUTH);
	npPos(9,30,16);
	npDir(9,SOUTH);
	npPos(10,31,17);
	npDir(10,SOUTH);
	npPos(11,40,22);
	npDir(11,WEST);
	npPos(12,28,17);
	npDir(12,SOUTH);
	npPos(13,31,16);
	npDir(13,SOUTH);

	npDelete(0);
	npDelete(1);
	npDelete(2);
	npDelete(5);
	npDelete(6);

	crbaseClearScreen(0x02);
	evFieldNoFlip(0,1);
	evFadeIn(1000);

	evFrameWait(1000);

	for(a = 0;a < 6;a ++){
		mcMove(1,0);
		evFrame();
	}
	for(a = 0;a < 4;a ++){
		mcMove(0,-1);
		evFrame();
	}

	//---蒸発しちゃった・・・
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw(2);

	//---クレイシヴ！
	evFrameWait(1000);
	npMove(8,0,1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();

	//---さぁ、
	ef->SetMoveSpeed(old);
	for(a = 0;a < 2;a ++){
		mcMove(0,1);
		evFrame();
	}
	for(a = 0;a < 2;a ++){
		mcMove(-1,0);
		evFrame();
	}
	evFrameWait(500);
	npMove(14,-1,0);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();

	//---そんなこと
	evFrameWait(500);
	npDir(8,WEST);
	evFrameWait(250);
	for(a = 0;a < 4;a ++){
			npMove(8,-1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(8,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---ダメです！
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(12,0,1);
		evFrame();
	}
	evFrameWait(250);
	npDir(12,WEST);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---邪魔をする者に
	evFrameWait(1000);
	mes.ReadDraw();

	//---ディザよ！
	evFrameWait(500);
	npMove(10,0,1);
	evFrame();
	evFrameWait(250);
	npDir(10,WEST);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(1000);
	npMove(7,-1,0);
	evFrame();
	evFrameWait(1000);
	npDir(7,NORTH);
	evFrameWait(500);

	//---じゃあ黙って
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npMove(8,0,1);
	evFrame();
	evFrameWait(500);
	//---そんなこと
	mes.ReadDraw(2);
	evFrameWait(250);

	//-----------------------------------------
	//---初期化
	int npnum = 14;

	memset(kj,0,sizeof(kj));

	//---腕
	eiCellReadPattern(kjcell,
		CR_DATADIR2"CrasiveUde.acf",CR_DATAFILE2,crdataGetFileMode(),
		0,8,32,32);
	eiCellSetSurface(kjcell,
		0,240,32,32,8,3);

	ef->SetFGCallback(crevent_KojinsaiFGCallback);
	int delta = 0;
	eiTime let,let2;
	int kj_count = 0;

	//---腕が飛ぶ
	em->SetObjectSurface(12);
	evReadObject(12,"Crasive3.acf");
	em->ReloadPattern();
	crfieldPaletteChange(PALETTE_SUNSET);

	crmusicStop();
	crsoundPlay(CRSOUND_ATACK4);
	evFill(ep->MakeRGB(255,255,255));
	ew->Flip();
	et->Delay2(20);

	kj_Make(&kj[0],npnum,0,1);
	let.Reset();
	let2.Reset();

	while(kj[0].now_time > 0){
		let.Reset();

		kj_Move(&kj[0],delta);
		evFrameWait(10);

		delta = let.Get() + 1;
	}
	//---
	ef->SetFGCallback(NULL);

	for(a = 0;a < 8;a ++){
		kjcell[a].Release();
	}
	evFrameWait(100);
	mes.ReadDraw();
	crmusicPlay(CRMUSIC_SILENT);

	//---なんだ！？
	evFrameWait(250);
	npDir(8,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---悪いわね
	evFrameWait(250);
	for(a = 0;a < 13;a ++){
		mcMove(1,0);
		evFrame();
	}
	npDir(10,SOUTH);
	npDir(12,SOUTH);
	evFrameWait(500);
	npMove(11,-1,0);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---クレイシヴ歩き出す
	for(a = 0;a < 13;a ++){
		mcMove(-1,0);
		evFrame();
	}
	evFrameWait(1000);
	npDir(14,SOUTH);
	evFrameWait(1000);
	npDir(14,EAST);
	evFrameWait(2000);
	npDir(14,SOUTH);
	evFrameWait(1000);
	npDir(14,WEST);
	evFrameWait(1000);
	for(a = 0;a < 3;a ++){
		npMove(14,-1,0);
		evFrame();
		if(a == 1)
			npDir(8,SOUTH);
		if(a == 2)
			npDir(12,WEST);
		evFrameWait(500);
	}
	evFrameWait(500);
	npDir(14,NORTH);
	evFrameWait(1000);
	for(a = 0;a < 2;a ++){
		npMove(14,0,-1);
		evFrame();
		evFrameWait(500);
		if(a == 1)
			npDir(8,WEST);
	}
	evFrameWait(500);
	//---ルナン倒れる
	evReadObject(1,"LunarnSlp3.acf");
	em->ReloadPattern();
	crfieldPaletteChange(PALETTE_SUNSET);
	npDir(7,NORTH);
	evFrameWait(250);
	npDir(8,SOUTH);
	evFrameWait(250);
	//---ルナン！
	mes.ReadDraw();
	npDir(12,SOUTH);
	evFrameWait(250);

	for(a = 0;a < 1;a ++){
		npMove(8,0,1);
		evFrame();
	}
	//---クレイシヴ去る
	for(a = 0;a < 1;a ++){
		npMove(14,0,-1);
		npMove(8,0,1);
		evFrame();
		evFrameWait(500);
	}
	evFrameWait(500);
	npDir(14,WEST);
	evFrameWait(500);
	for(a = 0;a < 8;a ++){
		npMove(14,-1,0);
		evFrame();
		if(a == 2)
			npDir(12,WEST);
		evFrameWait(500);
	}

	evFadeOut(2000);
	crfieldChangeScene(7,15,15);
	evFrameWait(1000);

	//---ルナン、ルナン！
	mes.ReadDraw();
	evFrameWait(4000);


	mes.CloseMessage();

	return creventKojinsaiOilLakeNight();
}

//---そして・・・
CREVENTLONG7_API int creventKojinsaiOilLakeNight(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	crmusicPlay(CRMUSIC_SILENT);

	evReloadMap(0);

	//---オイルレイクの宿屋
	crfieldChangeScene(6,40,29);
	evReadObject(1,"LunarnSlp2.acf");
	npPos(7,40,28);
	npDir(7,SOUTH);
	npPos(9,40,27);
	npDir(9,SOUTH);

	for(a = 0;a <= 6;a ++){
		npDelete(a);
	}
	crfieldPaletteChange(PALETTE_NIGHT);

	evFieldNoFlip(0,1);
	evFadeIn(2000);

	evFrameWait(2000);
	npDir(7,WEST);
	evFrameWait(250);
	npDir(7,SOUTH);
	evFrameWait(250);
	npDir(7,WEST);
	evFrameWait(500);

	mes.OpenMessage("Daishinden.msg",104);
	mes.ReadDraw();
	//---・・・
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---わたし
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---みんなは？
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);


	//---ルナン出てくる
	evScene(6,28,29);
	npPos(7,37,27);
	evReadObject(1,"Lunarn.acf");
	em->ReloadPattern();
	crfieldPaletteChange(PALETTE_NIGHT);
	evFrameWait(1000);
	int old = ef->SetMoveSpeed(2);
	for(a = 0;a < 16;a ++){
		if(a < 14)
			npMove(7,-1,0);
		if(a > 9)
			mcMove(-1,0);
		evFrame();
	}
	ef->SetMoveSpeed(old);

	evFrameWait(1000);
	//---画像
	RECT rect = {0,0,640,480};
	eiCell src,bg;

	crefectScreenEfect_FadeOut(&rect,1000,RGB_MAKE(0,0,0),0);
	src.ReadFile(CR_DATADIR1"OLnight.acf",CR_DATAFILE1,crdataGetFileMode());
	//---復元
	decode_image(&bg,&src,NULL);
	src.Release();
	bg.Put(ew->lpCell[1],0,0);

	crefectScreenEfect_FadeOut(&rect,1000,RGB_MAKE(0,0,0),1);
	et->Delay2(4000);
	bg.Release();

	crefectScreenEfect_FadeOut(&rect,1000,RGB_MAKE(0,0,0),0);
	crbaseClearScreen(0x02);
	evFieldNoFlip(0,1);

	evFadeIn(1000);

	//---わたしはずっと・・・
	evFrameWait(2000);
	mes.ReadDraw();

	//---この先に
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(2000);

	//---ディザが来る
	npPos(8,28,15);
	npDir(8,SOUTH);
	for(a = 0;a < 10;a ++){
		npMove(8,0,1);
		evFrame();
	}
	for(a = 0;a < 2;a ++){
		mcMove(1,0);
		evFrame();
	}
	evFrameWait(500);
	npDir(8,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	crmusicPlay(CRMUSIC_SEEK);

	//---ルナンの横に来る
	evFrameWait(250);
	npDir(8,SOUTH);
	evFrameWait(500);
	for(a = 0;a < 7;a ++){
		if(a < 3)
			npMove(8,0,1);
		else
			npMove(8,-1,0);
		evFrame();
	}
	evFrameWait(1000);
	mes.ReadDraw();

	//---さっきのことは
	evFrameWait(2000);
	mes.ReadDraw();
	//---なにがあったって
	evFrameWait(2500);
	mes.ReadDraw();

	//---なんだよ
	evFrameWait(3000);
	npMove(8,-1,0);
	evFrame();
	evFrameWait(250);
	npDir(8,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---わたしの力
	evFrameWait(2000);
	evFrameWait(250);
	npDir(7,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw();

	//---ずっと
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---そうか？
	evFrameWait(500);
	mes.ReadDraw();

	//---そうよ
	evFrameWait(250);
	mes.ReadDraw();

	//---ほら
	evFrameWait(250);
	npDir(7,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---じゃあ
	evFrameWait(1000);
	mes.ReadDraw();

	//---そんなの
	evFrameWait(250);
	npDir(7,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---だったら
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---オレは
	evFrameWait(1000);
	npDir(8,WEST);
	evFrameWait(500);
/*	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---お前は
	evFrameWait(1000);
	mes.ReadDraw();*/

	//---なんのために
	evFrameWait(500);
	npMove(8,-1,0);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(7,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	//---それは、お前が
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();

	//---ないだろ？
	evFrameWait(500);
	npDir(8,NORTH);
	evFrameWait(250);
	npMove(8,0,-1);
	evFrame();
	evFrameWait(250);
	npDir(8,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	//----・・・
	evFrameWait(2000);
	mes.ReadDraw();
	//---そうか、そうよね
	evFrameWait(3000);
	mes.ReadDraw();
	evFrameWait(2000);
	mes.ReadDraw();

	//---オレだって
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(8,SOUTH);
	evFrameWait(250);
	npMove(8,0,1);
	evFrame();
	evFrameWait(250);
	npDir(8,EAST);
	evFrameWait(250);
	npDir(8,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---でも、もしもは
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	npMove(7,-1,0);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();

	//---アージェごと
	evFrameWait(500);
	npDir(8,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	//---いよいよ
	evFrameWait(500);
	npDir(8,NORTH);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(8,EAST);
	evFrameWait(500);
	for(a = 0;a < 3;a ++){
		if(a == 0)
			npDir(7,SOUTH);
		if(a == 2)
			npDir(7,EAST);
		npMove(8,1,0);
		evFrame();
	}
	evFrameWait(100);
	mes.ReadDraw();

	//---なんだ？
	evFrameWait(250);
	npDir(8,NORTH);
	evFrameWait(250);
	npDir(8,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---ありがとう
	evFrameWait(1000);
	npMove(7,1,0);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	crmusicFadeOut();
	evFrameWait(1000);
	evFadeOut(2000);

	//---翌朝
	et->Delay2(1000);
	evReloadMap(1);

	crfieldChangeScene(6,32,28);
	npPos(7,31,26);
	npDir(7,SOUTH);
	npPos(8,33,26);
	npDir(8,SOUTH);
	npPos(9,32,28);
	npDir(9,NORTH);
	npPos(12,31,28);
	npDir(12,NORTH);
	evFieldNoFlip(0,1);

	evFadeIn(1000);

	evFrameWait(500);
	mes.ReadDraw(3);
	//---なんで？
	evFrameWait(250);
	npDir(9,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(12,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(12,NORTH);
	evFrameWait(250);
	npDir(9,NORTH);

	//---イリーディアへ
	npMove(7,0,1);
	evFrame();
	evFrameWait(250);
	npDir(7,WEST);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		if(a == 0)
			npDir(8,WEST);
		if(a == 1)
			npDir(9,WEST);
		npMove(7,-1,0);
		evFrame();
	}
	for(a = 0;a < 2;a ++){
		mcMove(-1,0);
		npDir(12,WEST);
		evFrame();
	}
	evFrameWait(250);
	npDir(7,SOUTH);
	evFrameWait(250);
	npDir(7,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);

	mes.CloseMessage();

	evSet(83,1);//---中央山脈突破フラグ
	evSet(218,1);
	evSet(230,1);

	prtRecoveryAll();
	evReloadMap(0);
	crfieldSetMainCharacter(1);
	mcShow(1);
	mcDir(WEST);
	evScene(6,23,19);

	//---ＧＳの位置
	evSet(EV_GS_NUMBERX,190);
	evSet(EV_GS_NUMBERY,106);

	return 1;
}

