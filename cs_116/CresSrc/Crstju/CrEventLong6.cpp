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


//---南部大雪原、初着船
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
	//---寒い
	mes.OpenMessage("GS.msg",101);
	mes.ReadDraw(2);
	//---なんなら
	evFrameWait(500);
	npMove(5,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---サヴィアー来る
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

	//--そういえば
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

	//---！
	evFrameWait(500);
	mes.ReadDraw();

	//---外寒そう
	evFrameWait(500);
	npDir(2,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---ディザが歩く
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

	//---そんな・・・
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(2,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---どうしよう
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	//---クレイシヴを！
	evFrameWait(500);
	npDir(0,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---違うの！
	evFrameWait(250);
	mes.ReadDraw(2);

	//---シルバーリングは・・・
	evFrameWait(250);
	mes.ReadDraw();

	//---なるほどね
	evFrameWait(500);
	mes.ReadDraw(3);

	//---え！？
	evFrameWait(250);
	npDir(2,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---くそ！
	evFrameWait(500);
	mes.ReadDraw();

	//---そうですね
	evFrameWait(500);
	mes.ReadDraw(3);

	//---ラーフィア達は
	evFrameWait(500);
	npDir(5,EAST);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---冗談じゃないぜ！
	evFrameWait(250);
	mes.ReadDraw(2);

	//---そうなると
	evFrameWait(1000);
	mes.ReadDraw();

	//---もし・・・
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

//---南部大雪原、忘れられた遺跡、はじめて
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


//---南部大雪原、忘れられた遺跡、シルバープラント
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
	//---読んでみるよ
	mes.ReadDraw();

	evFrameWait(250);
	npMove(2,-1,0);
	evFrame();
	evFrameWait(250);
	npDir(2,NORTH);
	//---シルバープラント
	evFrameWait(1500);
	mes.ReadDraw(2);
	//---ここで
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


//---南部大雪原、忘れられた遺跡、動いている機械
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

	//---なんだこりゃ
	mes.OpenMessage("Wasurerareta.msg",102);
	mes.ReadDraw();

	//---ルナン動く
	evFrameWait(250);
	npMove(0,1,0);
	evFrame();
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);

	//---何かの機械
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

	//---ぴこぴこ
	evFrameWait(500);
	npMove(2,0,-1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();

	//---なんで動いてるの？
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

//---南部大雪原、忘れられた遺跡、決戦フォールン
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

	//---フォールン！
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

	//---振り向く
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
	//---先生！
	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---なぜ
	evFrameWait(1000);
	mes.ReadDraw();

	//---アージェが！
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---なんで！？
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(1000);
	npDir(4,WEST);
	evFrameWait(1000);
	mes.ReadDraw();

	//---？
	evFrameWait(500);
	mes.ReadDraw();

	//---それだけだ
	evFrameWait(500);
	for(a = 0;a < 2;a ++){
		npMove(4,-1,0);
		evFrame();
		evFrameWait(500);
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);

	//---いい加減にしとけよ
	npMove(1,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---そろそろ
	evFrameWait(1000);
	npDir(4,NORTH);
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(1000);
	npMove(4,0,-1);
	evFrame();
	evFrameWait(1000);
	mes.ReadDraw();
	//---はい
	evFrameWait(500);
	npDir(5,WEST);
	evFrameWait(500);
	npDir(5,NORTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);

	//---待って！
	mes.ReadDraw();
	evFrameWait(2000);
	mes.ReadDraw(2);

	//---だって
	evFrameWait(500);
	npMove(0,0,-1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1500);
	mes.ReadDraw();

	//---歴史を変える？
	evFrameWait(500);
	mes.ReadDraw(3);
//	evFrameWait(2000);
//	mes.ReadDraw(3);

	//---クレイシヴ行く
	evFrameWait(500);
	for(a = 0;a < 4;a ++){
		npMove(4,0,-1);
		evFrame();
		evFrameWait(500);
	}
	npDelete(4);

	//---クレイシヴを倒すには
	mes.ReadDraw();
	evFrameWait(500);

	//---俺だ
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

	//---ナック来る
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

	//---奴隷も
	evFrameWait(500);
	mes.ReadDraw(2);

	//---すでに
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(250);
	npMove(1,0,-1);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---たくさん
	evFrameWait(500);
	mes.ReadDraw(3);

	//---出る？
	evFrameWait(500);
	mes.ReadDraw();

	//---許さない！
	evFrameWait(500);
	npMove(0,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(250);
	mes.ReadDraw();

	//---お前は
	evFrameWait(500);
	mes.ReadDraw();

	//---そうだな
	evFrameWait(500);
	npDir(5,WEST);
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	npDir(5,NORTH);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---強さ？
	evFrameWait(500);
	mes.ReadDraw();

	//---アズグレイは強かった
	evFrameWait(500);
	npDir(5,WEST);
	evFrameWait(250);
	npDir(5,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(3);
	//---そこまでして
	evFrameWait(250);
	npMove(3,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---誰よりも
	evFrameWait(500);
	mes.ReadDraw();

	//---みんなを助けに行くから
	evFrameWait(250);
	npMove(2,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	//---ルナンがうらやましい
	evFrameWait(1000);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw();
	//---そんなの
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---あなたって、
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

	//---バトル
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

	//---ぐっ
	evFrameWait(250);
	npMove(5,0,-1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);


	//---倒れる
	//---観念しな
	npMove(1,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	//---いいのかよ！
	evFrameWait(250);
//	npDir(1,EAST);
//	evFrameWait(250);
	mes.ReadDraw();

	//---そうね、でも
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---ルナンが行く
	evFrameWait(250);
	for(a = 0;a < 8;a ++){
		npMove(0,0,-1);
		evFrame();
	}
	npDir(3,WEST);
	evFrameWait(250);

	//---サヴィアー
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

	//---ナック
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
	//---だとよ
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

	//---最下層
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

	//---覚悟してもらうぜ
	evFrameWait(250);
	npMove(1,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---先生
	evFrameWait(250);
	npMove(3,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();
	//---黙ってないで！
	evFrameWait(250);
	npMove(2,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---ちょうど
	evFrameWait(2000);
	npMove(4,0,-1);
	evFrame();
	evFrameWait(2000);
	mes.ReadDraw();

	evFrameWait(1000);
	mcMove(0,-1);
	evFrame();

	evFrameWait(1000);

	//---振り向き、リングを見せる
	npDir(4,WEST);
	evFrameWait(500);
	npDir(4,SOUTH);
	evFrameWait(1000);

	evReadObject(5,"Crasive2.acf");
	evFrameWait(250);
	npPos(5,14,8);
	npDir(5,NORTH);
	evFrameWait(1000);

	//---あれは
	mes.ReadDraw();
	evFrameWait(500);
	npMove(0,0,1,0);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();

	//---どうしたんだよ！
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(150);
	npDir(2,EAST);
	evFrameWait(100);
	mes.ReadDraw(2);

	//---だったら！
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---クレイシヴ去る
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

	//---な・・・
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	//---ヒマはないぜ
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

//---全ウ連、モリウニ珍味！
CREVENTLONG6_API int creventZenuren_Moriuni(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	evField(0,1);
	mes.OpenMessage("Zenuren.msg",101);

	mes.ReadDraw(9);

	//---これはーーーーーーー
	evFrameWait(500);
	mes.ReadDraw(3);

	//---ぱく
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw(2);

	//---まずい
	evFrameWait(1000);
	mes.ReadDraw(12);
	evFrameWait(500);
	mes.ReadDraw(2);

	mes.CloseMessage();

	evSet(212,1);

	//---珍味減らし、ピースオブムーン
	critemAddItem(233,-1);
	critemAddItem(210,1);

	return 1;
}

//---流砂の遺跡、助けに来た初
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


//---流砂の遺跡、声がする
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
	//---ルナン歩く
	evFrameWait(250);
	npMove(0,0,1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);

	//---行ってやろうぜ
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

	//---みんな行く
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
	//---どうした？
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);

	mes.ReadDraw();

	//---みんな向く
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
	//---ルナン、歩く
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


//---流砂の遺跡、ガゼール救出！
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

	//---父さん！
	mes.OpenMessage("RyusanoIseki.msg",104);
	mes.ReadDraw();
	evFrameWait(250);

	npDir(11,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---エターナル振り向く
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

	//---なんだって言われてもなあ
	evFrameWait(250);
	npMove(1,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);

	//---こいつらは
	evFrameWait(500);
	npMove(9,0,1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw(4);

	//---わしは
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

	//---二人行く
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

	//---丁度いい
	evFrameWait(250);
	npMove(10,0,1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(4);
	evFrameWait(250);

	//---バトル
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

	//---バトル
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
	//---勝負は
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

	//---父さん大丈夫！？
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

	//---コンだけの人が
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

	//---ナック
	for(a = 0;a < 3;a ++){
		npMove(2,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---サヴィアー
	for(a = 0;a < 3;a ++){
		npMove(3,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---こんなところまで
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

	//---わたし・・・
	evFrameWait(1250);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---昔のこと
	evFrameWait(1000);
	mes.ReadDraw(2);

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---わたしには
	evFrameWait(500);
	mes.ReadDraw(2);
	//---成長したな
	evFrameWait(500);
	mes.ReadDraw(2);

	//---６年間
	evFrameWait(500);
	mes.ReadDraw(3);

	//---そんなふうに
	evFrameWait(800);
	mes.ReadDraw(2);
	//---おふこーす
	evFrameWait(500);
	mes.ReadDraw();

	//---さて、こんな場所から
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

	//---しまってる
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

	//---サヴィアー来る
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
	//---ディザも来る
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
	//---びくともしない
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
	//---気配
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

	//---クレイシヴ歩く
	for(a = 0;a < 6;a ++){
		npMove(22,0,-1);
		evFrame();
		evFrameWait(500);
	}
	mes.ReadDraw();

	//---内側から
	evFrameWait(1000);
	mes.ReadDraw();

	//---閉じこめる気？
	npPos(0,22,30);
	evFrameWait(500);
	for(a = 0;a < 5;a ++){
		npMove(0,0,1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();

	//---これで
	evFrameWait(2000);
	mes.ReadDraw();

	evFrameWait(1000);
	npDir(22,WEST);
	evFrameWait(1000);
	npDir(22,SOUTH);
	evFrameWait(1000);
	npMove(22,0,1);
	evFrame();
	//---待って！
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

	//---開かない
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

	//---ダメ！
	mes.ReadDraw(2);

	//---あーあ
	evFrameWait(500);
	for(a = 0;a < 10;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();

	//---奥
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

//---流砂の遺跡、シンディ登場！
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
	//---ちっくしょう！
	evFrameWait(500);
	mes.ReadDraw(2);

	//---音
	evFrameWait(500);
	crsoundPlay(CRSOUND_ANAAKU);
	evFrameWait(1000);

	//---開く
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

	//---シンディ登場
	evFrameWait(250);
	for(a = 0;a < 8;a ++){
		npMove(6,0,-1);
		evFrame();
	}
	crmusicPlay(CRMUSIC_DRAGONBREATH);
	evFrameWait(250);
	mes.ReadDraw(2);
	//---シンディさん！？
	evFrameWait(250);
	npMove(3,0,1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	mes.ReadDraw(3);

	//---あちこちの町で
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---マークス町長
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

	//---久しぶりだな
	evFrameWait(500);
	mes.ReadDraw(2);

	//---ライゼルよ
	evFrameWait(500);
	npMove(26,1,0);
	evFrame();
	evFrameWait(250);
	npDir(26,NORTH);
	evFrameWait(250);

	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	//---わしも
	evFrameWait(1000);
	mes.ReadDraw();

	//---シンディは、
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(26,EAST);
	evFrameWait(500);

	//---あの後
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw();

	//---もうずいぶん
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw(2);

	//---謝られるとなあ
	evFrameWait(500);
	npMove(1,-1,0);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw(2);


	//---そうか・・・
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---商人を
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

	//---クレスフィールドの方々は
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

//---格闘場
CREVENTLONG6_API int creventKakutojo(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	if(!evGet(222)){
		//---はじめて
		evField(0,1);
		mes.FileMessage("kakutojo.msg",50,1);
		evField(0,1);
		mes.FileMessage("kakutojo.msg",51,1);
		evField(0,1);
		evSet(222,1);
	}

	//---選択
	eistr *rankstr[] = {"Ｓ","Ａ","Ｂ","Ｃ","Ｄ","Ｅ","Ｆ"};
	int rank = evGet(224);
	eistr str[80],*p = str;

	if(rank == RANK_MAX + 1){
		//---Ｓランククリアなので無理！
		evField(0,1);
		mes.FileMessage("kakutojo.msg",57,1);
		return 1;
	}

	sprintf(p,"ランク%s に挑戦する;",rankstr[RANK_MAX - rank]);
	p += strlen(p);
	sprintf(p,"説明を聞く;");

	CrSelectWindow win;
	int sel,fan;

	fan = (rank + 1) * 2000;

//	fan = 0;
//	rank = 3;

	do {
		crbaseMenuReset();
		win.Create(64,64,16,5,"どうしますか？",str);
		win.Paint();
		win.Refresh();
		crbaseMenuStart();

		sel = win.Select();

		if(sel == 0){
			//---戦う！
			if(evGet(270 + rank) == 0){
				//---お金支払い
				eistr s[80];
				sprintf(s,
				"＊「ランク%sに、初挑戦ですね。\\n;　登録料は %d ファンとなります」\\c;",
				rankstr[RANK_MAX - rank],fan);

				mes.CreateNewMessage();
				mes.Message(s);
				mes.Draw();
				mes.CloseMessage();

				crbaseMenuReset();
				evField(0,1);

				crbaseShowMoney(64,160);
				CrSelectWindow selwin;
				selwin.Create(64,64,10,5,"払いますか？","払う;払わない;");
				ew->Refresh();

				if(selwin.Select() == 0){
					if(crbaseGetMoney() < fan){
						//---足りない！
						evField(0,1);
						mes.FileMessage("kakutojo.msg",52,1);
						return 1;
					}
					//---払った
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

			//---戦う人物選ぶ
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
			win.Create(64,64,16,9,"誰が戦いますか？",str);
			win.Paint();
			win.Refresh();
			crbaseMenuStart();

			sel = win.Select();

			if(sel == -1){
				//---中止
				crbaseMenuReset();
				crbaseMenuStart();
				return 1;
			}

			mcShow(0);
			evScene(2,15,15);

#define KAK_ENEMY 6
			//---バトル！
			CR_BATTLEINFO BattleInfo;
			//---f:こんなもん
			int class_f[4][KAK_ENEMY] = {//試合数、敵ナンバー
				{95,-1},
				{98,96,-1},
				{103,103,-1},
				{0}
			};
			//---e:もう少し強めでいいかも
			int class_e[5][KAK_ENEMY] = {//試合数、敵ナンバー
				{152,-1},
				{133,-1},
				{134,135,134,-1},
				{136,137,-1},
				{0}
			};
			//---d:
			int class_d[5][KAK_ENEMY] = {//試合数、敵ナンバー
				{143,-1},
				{147,149,-1},
				{228,151,-1},
				{229,230,-1},
				{0}
			};
			//---c:
			int class_c[5][KAK_ENEMY] = {//試合数、敵ナンバー
				{231,-1},
				{162,-1},
				{126,233,126,-1},
				{232,234,-1},
				{0}
			};
			//---b:
			int class_b[5][KAK_ENEMY] = {//試合数、敵ナンバー
				{192,-1},
				{237,237,-1},
				{151,127,204,84,-1},
				{236,193,-1},
				{0}
			};
			//---a:
			int class_a[5][KAK_ENEMY] = {//試合数、敵ナンバー
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
					//---負け！
					win = 0;
					break;
				}
				//---ＬＰとＭＣ回復
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
				//---負け
				evField(0,1);
				mes.FileMessage("kakutojo.msg",54,1);
			} else {
				//---勝ち！
				int item_list[] = {225,176,164,138,  75,187,228};
				mes.CreateNewMessage();
				sprintf(str,"＊「ランク%s勝利、おめでとうございます！　新たなる勝者の誕生です！！\\c;",
					rankstr[RANK_MAX - rank]);
				mes.Message(str);
				mes.Draw();

				mes.Message("＊「商品は、こちらになります」\\c;");
				mes.Draw();

				sprintf(str,"%sを手に入れた！\\c;",
					critemGetItemClass(item_list[rank])->GetName());
				mes.Message(str);
				mes.Draw();

				critemAddItem(item_list[rank]);

				rank ++;
				if(rank > RANK_MAX){
					//---完全制覇
					mes.Message("＊「ついに現れました！　全クラス完全制覇者！」\\c;");
					mes.Draw();
					mes.Message("＊「あなた方の強さは、大陸中に知られることでしょう。おめでとうございます！！」\\c;");
					mes.Draw();
				} else {
					mes.Message("＊「新たなるクラスへの挑戦、お待ちしています」\\c;");
					mes.Draw();
				}
				mes.CloseMessage();

				evSet(224,rank);
			}
			evFrameWait(150);

			//---元に戻す
			crcharaGetPartyMember(0)->SetBattleFieldStartPos(kx,ky);
			for(a = 0;a < MEMBER_MAX;a ++){
				pPartyInfo->PartyMember[a] = party[a] - 1;
			}
			sel = 0;
		} else if(sel == 1){
			//---説明
			evField(0,1);
			mes.FileMessage("kakutojo.msg",51,1);
		}
	} while(sel == 1);
	crbaseMenuReset();
	crbaseMenuStart();

	return 1;
}
