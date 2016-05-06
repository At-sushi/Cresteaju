/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrEventLong2.cpp ...Event functions

-----------------------------------------------------------*/


#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CREVENTLONG2

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

//---第２部スタート
CREVENTLONG2_API int creventCresfield_StartChapter2(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	crfieldChangeMap(32,6,1,0);
	evScene(6,15,15);
	evFrameWait(5000);

	mes.OpenMessage("Cresfield.msg",116);
	for(a = 0;a < 5;a ++){
		mes.ReadDraw();
		evFrameWait(2000);
	}
	evFrameWait(2000);

	crfieldChangeScene(3,16,12);
	evReadObject(12,"LunarnSlp2.acf");
	npPos(0,18,11);
	npDir(0,SOUTH);
	evFieldNoFlip(0,1);
	evFadeIn(2000);

	//---ルナン目を覚ます
	evFrameWait(2000);
	npDir(0,WEST);
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(1000);
	npDir(0,NORTH);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	mes.CloseMessage();

	npPos(0,0,0);
	npShow(0,0);
	mcShow(1);
	mcDir(SOUTH);
	evSet(77,1);
	evReadObject(12,"Lunarn.acf");
	evScene(3,16,11);

	return 1;
}

//---第２部ナックが様子を見に来る
CREVENTLONG2_API int creventCresfield_NackCome(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	evFrameWait(1000);

	//---ナックが階段から来る
	npPos(2,14,2);
	npDir(2,SOUTH);
	evFrameWait(500);
	npDir(2,EAST);
	evFrameWait(250);
	mes.OpenMessage("Cresfield.msg",121);
	mes.ReadDraw();

	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(2,1,0);
		evFrame();
	}
	npDir(2,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(2,WEST);
	evFrameWait(250);
	//---ナックが一階へ行く
	for(a = 0;a < 2;a ++){
		npMove(2,-1,0);
		evFrame();
	}
	npShow(2,0);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---みんなでお話
	mcShow(0);
	npPos(0,13,9);
	npDir(0,SOUTH);
	npPos(1,14,10);
	npDir(1,WEST);
	npPos(2,12,10);
	npDir(2,EAST);
	npPos(3,13,11);
	npDir(3,NORTH);
	npPos(4,12,11);
	npDir(4,NORTH);
	evScene(3,13,11);
	crmusicPlay(CRMUSIC_TOWNETERNAL);
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(1000);
	mes.ReadDraw(4);
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(250);

	mes.ReadDraw();

	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(1);
	evFrameWait(500);
	npDir(1,NORTH);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---夜のクレスフィールド
	crmusicFadeOut();
	evFadeOut(2000);
	crfieldChangeScene(0,14,35);
	for(a = 0;a < 50;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	npPos(18,14,35);
	npDir(18,NORTH);
	npPos(10,16,26);
	npDir(10,SOUTH);
	crfieldPaletteChange(PALETTE_NIGHT);
	evFieldNoFlip(0,1);
	evFadeIn(2000);
	crmusicStop();

	evFrameWait(4000);
	for(a = 0;a < 6;a ++){
		if(a < 4)
			npMove(10,0,1);
		else
			npMove(10,-1,0);
		evFrame();
	}
	evFrameWait(500);
	npDir(10,SOUTH);
	evFrameWait(500);

	//---おばさん
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	npMove(10,0,1);
	evFrame();
	evFrameWait(500);

	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(10,EAST);
	evFrameWait(250);
	npDir(10,NORTH);
	evFrameWait(250);

	//---おばさん家に入る
	for(a = 0;a < 7;a ++){
		if(a < 1)
			npMove(10,0,-1);
		else if(a < 3)
			npMove(10,1,0);
		else
			npMove(10,0,-1);
		evFrame();
	}
	//---ルナン沈黙
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(2000);

	//---ナック登場
	npPos(20,26,33);
	npDir(20,WEST);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(18,EAST);
	for(a = 0;a < 6;a ++){
		mcMove(1,0);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	crmusicPlay(CRMUSIC_SEEK);
	for(a = 0;a < 12;a ++){
		npMove(20,-1,0);
		if(a == 10)
			npDir(18,NORTH);
		evFrame();
	}
	evFrameWait(250);
	npDir(20,SOUTH);
	evFrameWait(100);
	npMove(20,0,1);
	evFrame();
	evFrameWait(250);
	for(a = 0;a < 5;a ++){
		mcMove(-1,0);
		evFrame();
	}
	evFrameWait(250);

	//---ナックとルナンの会話
	mes.ReadDraw(7);
	evFrameWait(1000);
	//---そうだったんだ
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);
	//---あたしたちって・・・
	evFrameWait(500);
	npDir(20,WEST);
	evFrameWait(500);
	npDir(20,NORTH);
	evFrameWait(500);
	npMove(20,0,-1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(20,EAST);
	evFrameWait(500);
	npDir(20,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---ごめん
	evFrameWait(1000);
	mes.ReadDraw(3);
	evFrameWait(1000);
	npMove(18,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(5);

	//---宿へ帰る
	evFrameWait(500);
	npDir(18,EAST);
	evFrameWait(250);
	npDir(20,EAST);
	evFrameWait(250);
	for(a = 0;a < 20;a ++){
		npMove(18,1,0);
		if(a > 1)
			npMove(20,1,0);
		evFrame();
	}
	evFrameWait(250);

	crfieldChangeMap(32,3,13,10);
	npPos(0,13,9);
	npDir(0,SOUTH);
	npPos(1,14,10);
	npDir(1,NORTH);
	npPos(2,12,10);
	npDir(2,NORTH);
	npPos(3,13,11);
	npDir(3,NORTH);
	npPos(4,12,11);
	npDir(4,NORTH);
	evScene(3,13,11);
	crmusicPlay(CRMUSIC_TOWNETERNAL);

	evFrameWait(500);
	mes.ReadDraw(5);
	evFrameWait(500);
	mes.ReadDraw();

	//---サヴィアーの方に振り向く
	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(125);
	npDir(2,EAST);
	evFrameWait(125);
	npDir(4,EAST);
	evFrameWait(125);
	npDir(1,SOUTH);
	evFrameWait(125);
	npDir(2,SOUTH);
	evFrameWait(250);

	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw(3);
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);

	//---サヴィアー出口の方へ
	npDir(3,EAST);
	for(a = 0;a < 8;a ++){
		if(a < 2)
			npMove(3,1,0);
		else if(a < 6)
			npMove(3,0,-1);
		else if(a < 8)
			npMove(3,-1,0);

		if(a == 4)
			npDir(0,EAST);
		if(a == 5)
			npDir(0,NORTH);
		if(a == 2)
			npDir(4,NORTH);
		if(a == 3)
			npDir(1,EAST);
		if(a == 5)
			npDir(1,NORTH);
		if(a == 4)
			npDir(2,EAST);
		if(a == 6)
			npDir(2,NORTH);

		evFrame();
	}
	evFrameWait(125);
	npDir(3,SOUTH);
	evFrameWait(250);

	mes.ReadDraw(3);
	//---サヴィアー行く
	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(250);
	for(a = 0;a < 8;a ++){
		if(a < 3)
			npMove(3,1,0);
		else
			npMove(3,0,-1);
		evFrame();
	}
	npShow(3,0);
	npPos(3,0,0);
	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(500);
	//---オレらは
	mes.ReadDraw();
	evFrameWait(500);
	npDir(0,EAST);
	evFrameWait(150);
	npDir(2,EAST);
	evFrameWait(150);
	npDir(0,SOUTH);
	evFrameWait(150);
	
	mes.ReadDraw(4);
	evFrameWait(500);

	mes.CloseMessage();

	for(a = 0;a <= 4;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}

	prtRecoveryAll();
	//---サヴィアー外す
	{
		pPartyInfo->PartyMember[2] = 2;
		pPartyInfo->PartyMember[3] = 5;
		pPartyInfo->PartyMember[4] = -1;
		crcharaLoadFace(-1);
	}

	mcShow(1);
	mcDir(SOUTH);
	evScene(3,13,9);
//47,0,64,10
	evSet(77,2);

	return 1;
}

//---トレイアの夜
CREVENTLONG2_API int creventTreia_LunarnCrasive(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	evField(0,1);
	mes.OpenMessage("Treia.msg",103);
	mes.ReadDraw();

	crmusicFadeOut();
	evFrameWait(1000);
	crfieldPaletteChange(PALETTE_NIGHT);

	mcShow(0);
	npPos(22,24,38);
	npDir(22,SOUTH);
	npPos(23,26,38);
	npDir(23,SOUTH);
	npPos(24,27,39);
	npDir(24,SOUTH);
	npPos(26,48,24);
	npDir(26,WEST);
	for(a = 0;a <= 21;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	evScene(0,25,40);

	evFrameWait(2000);
	crmusicStop();
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	//---おっさんは？
	evFrameWait(1000);
	npDir(23,WEST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(22,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	//---笑いの道は厳しいものなり
	evFrameWait(500);
	npDir(24,WEST);
	evFrameWait(500);
	mes.ReadDraw();
	//---わたし、呼んでくる
	evFrameWait(500);
	mes.ReadDraw();

	//---ルナン歩く
	evFrameWait(500);
	npDir(22,NORTH);
	evFrameWait(250);
	int old = ef->SetMoveSpeed(2);
	for(a = 0;a < 33;a ++){
		if(a == 2)
			npDir(24,SOUTH);
		if(a == 3)
			npDir(23,SOUTH);

		if(a < 8){
			npMove(22,0,-1);
			mcMove(0,-1);
		} else if(a < 17){
			npMove(22,1,0);
			mcMove(1,0);
		} else if(a < 23){
			npMove(22,0,-1);
			mcMove(0,-1);
		} else if(a < 33){
			npMove(22,1,0);
			if(a < 25)
				mcMove(1,0);
		}
		evFrame();
	}
	ef->SetMoveSpeed(old);

	//---ルナンびっくり
	evFrameWait(100);
	mes.ReadDraw();
	evFrameWait(250);

	for(a = 0;a < 10;a ++){
		mcMove(1,0);
		evFrame();
	}
	crmusicPlay(CRMUSIC_CRAYSIVE);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);
	//---クレイシヴが喋る
	mes.ReadDraw();

	evFrameWait(500);
	npMove(26,-1,0);
	evFrame();
	//---声が出ない
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(1000);
	mes.ReadDraw();
	//---わたしは・・・
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(3);

	//---故郷だって
	for(a = 0;a < 5;a ++){
		evFrameWait(1000);
		mes.ReadDraw();
	}
	//---クレイシヴターン
	npDir(26,NORTH);
	evFrameWait(500);
	npDir(26,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();
	//---クレイシヴ歩く
	evFrameWait(500);
	for(a = 0;a < 2;a ++){
		npMove(26,1,0);
		evFrame();
		evFrameWait(500);
	}
	evFrameWait(500);
	//---やがてわかるだろう
	mes.ReadDraw();
	evFrameWait(500);
	for(a = 0;a < 12;a ++){
		if(a < 4)
			npMove(26,1,0);
		else
			npMove(26,0,-1);
		evFrame();
		evFrameWait(500);
		if(a == 3){
			npDir(26,NORTH);
			evFrameWait(500);
		}
		if(a == 9)
			crmusicFadeOut();
	}
	evFrameWait(500);
	crmusicStop();
	mes.ReadDraw();
	evFrameWait(2000);

	//---ディザが来る
	npPos(23,34,24);
	npDir(23,EAST);
	for(a = 0;a < 5;a ++){
		npMove(23,1,0);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	for(a = 0;a < 2;a ++){
		npMove(23,1,0);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	//---回り込む
	npDir(23,NORTH);
	for(a = 0;a < 5;a ++){
		if(a < 1)
			npMove(23,0,-1);
		else if(a < 4)
			npMove(23,1,0);
		else
			npMove(23,0,1);
		evFrame();
	}
	evFrameWait(250);
	npDir(23,WEST);
	evFrameWait(250);

	//---ルナン？
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	//---クレイシヴ・・・
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(1000);
	mes.ReadDraw(4);
	evFrameWait(500);

	//---宿屋
	crfieldChangeScene(1,11,7);
	npPos(0,11,7);
	npDir(0,NORTH);
	npPos(1,11,5);
	npDir(1,SOUTH);
	npPos(2,10,6);
	npDir(2,EAST);
	npPos(3,12,6);
	npDir(3,WEST);
	evScene(1,11,7);

	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw(3);
	//---ルナン、顔色良くないよ
	evFrameWait(500);
	npDir(2,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---ほんとにクレスティーユだったら
	evFrameWait(1000);
	mes.ReadDraw(3);

	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(1000);
	mes.ReadDraw();

	//---一人厳禁
	evFrameWait(500);
	npDir(3,SOUTH);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---翌朝
	crfieldChangeMap(37,0,1,1);

	npPos(22,50,29);
	npDir(22,SOUTH);
	npPos(23,49,30);
	npDir(23,NORTH);
	npPos(24,51,31);
	npDir(24,NORTH);
	npPos(25,50,31);
	npDir(25,NORTH);

	evScene(0,50,32);
	evFrameWait(500);

	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(3);

	evFrameWait(500);
	npDir(24,WEST);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();
	prtRecoveryAll();
	evSet(80,0);

	evFrameWait(500);

	mcShow(1);
	mcDir(SOUTH);
	npDelete(22);
	npDelete(23);
	npDelete(24);
	npDelete(25);
	evScene(0,50,29);

	mes.CloseMessage();

	return 1;
}

//---オイルレイク・ユミ登場！！
CREVENTLONG2_API int creventOilLake_Yumi(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	crfieldChangeScene(3,25,42);

	npPos(7,25,41);
	npDir(7,NORTH);
	npPos(8,24,41);
	npDir(8,NORTH);
	npPos(9,24,42);
	npDir(9,NORTH);
	npPos(10,23,42);
	npDir(10,NORTH);

	npPos(11,20,31);
	npDir(11,WEST);

	evScene(3,25,42);

	evFrameWait(500);
	mes.OpenMessage("CentralMount.msg",101);
	mes.ReadDraw();
	evFrameWait(500);

	//---オイルレイク映す
	for(a = 0;a < 12;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(3000);
	for(a = 0;a < 12;a ++){
		mcMove(0,1);
		evFrame();
	}

	mes.ReadDraw(3);
	evFrameWait(1000);
	mes.ReadDraw(4);

	//---ナックがユミ発見
	evFrameWait(500);
	npDir(9,EAST);
	evFrameWait(250);
	for(a = 0;a < 6;a ++){
		if(a < 2)
			npMove(9,1,0);
		else
			npMove(9,0,-1);
		evFrame();
	}
	for(a = 0;a < 5;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	//---みてみっか
	evFrameWait(250);
	for(a = 0;a < 3;a ++){
		npMove(8,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	for(a = 0;a < 5;a ++){
		mcMove(0,1);
		evFrame();
	}
	//---二人行く
	for(a = 0;a < 6;a ++){
		npMove(8,0,-1);
		if(a)
			npMove(9,0,-1);
		evFrame();
	}
	//---ディザ、ナック！
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---おっちゃん
	evFrameWait(250);
	npDir(10,EAST);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(10,1,0);
		else
			npMove(10,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(1000);
	npDir(7,WEST);
	evFrameWait(250);
	//---そうね
	mes.ReadDraw();
	evFrameWait(250);
	npDir(7,NORTH);
	evFrameWait(250);

	npPos(8,23,31);
	npDir(8,WEST);
	npPos(9,24,32);
	npDir(9,WEST);

	for(a = 0;a < 12;a ++){
		if(a < 8)
			mcMove(0,-1);
		else
			mcMove(-1,0);
		evFrame();
	}

	for(a = 0;a < 7;a ++){
		npMove(7,0,-1);
		if(a)
			npMove(10,0,-1);
		evFrame();
	}
	evFrameWait(100);
	npDir(7,WEST);
	evFrameWait(100);
	npDir(10,WEST);
	evFrameWait(100);

	//---女性！！
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---ディザ近づく
	for(a = 0;a < 2;a ++){
		npMove(8,-1,0);
		evFrame();
		evFrameWait(250);
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(11,SOUTH);
	evFrameWait(500);
	npDir(11,EAST);
	evFrameWait(500);
	//---くくく
	mes.ReadDraw();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npMove(8,1,0,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);

	//---リトライ
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(500);
	//---ディザぶちきれ

	npMove(8,-1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(4);
	evFrameWait(250);
	//---な、なんだとう！？
	mes.ReadDraw(2);

	//---ルナン仲裁
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	for(a = 0;a < 6;a ++){
		if(a < 4)
			npMove(7,-1,0);
		else
			npMove(7,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(7,WEST);
	evFrameWait(250);
	for(a = 0;a < 1;a ++){
		npMove(7,-1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(7,NORTH);
	evFrameWait(250);

	mes.ReadDraw();
	//---研究中に話しかけるのも・・・
	evFrameWait(250);
	npDir(11,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(11,WEST);
	evFrameWait(250);
	npDir(11,SOUTH);
	evFrameWait(250);
	npDir(11,EAST);
	evFrameWait(250);
	npDir(11,SOUTH);
	evFrameWait(250);
	//---あーやだやだ
	mes.ReadDraw(3);

	evFrameWait(250);
	//---ダンディなライゼル
	for(a = 0;a < 5;a ++){
		if(a < 1)
			npMove(10,-1,0);
		else
			npMove(10,0,-1);
		evFrame();
	}
	evFrameWait(250);
	npDir(10,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(11,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	//---い、いやあ・・・
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();

	//---おもろいわね
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(11,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---わかったわね
	evFrameWait(250);
	npDir(11,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(11,SOUTH);
	evFrameWait(250);

	//---ルナン、いこうぜ
	evFrameWait(250);
	npDir(8,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(11,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(8,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---行くわよ！
	evFrameWait(250);
	npDir(7,EAST);
	evFrameWait(250);
	npMove(7,1,0);
	evFrame();
	evFrameWait(250);
	npDir(7,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	mes.CloseMessage();

	mcShow(1);
	evSet(84,1);

	for(a = 7;a <= 10;a ++){ 
		npPos(a,0,0);
		npShow(a,0);
	}

	mcDir(WEST);
	evScene(3,23,31);

	return 1;
}

//---オーブ盗まれる！
CREVENTLONG2_API int creventDai_MemoryOveNusumareru(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	evFrameWait(500);
	mes.OpenMessage("Dai.msg",100);
	crmusicPlay(CRMUSIC_HEAT);
	mes.ReadDraw(2);
	evFrameWait(250);

	for(a = 0;a < 36;a ++){
		npPos(a,0,0);
	}
	mcShow(0);
	evScene(0,29,29);
	npPos(13,24,18);
	eiMapObject *np = npGet(13);
	np->Data.MoveSpeed = 4;

	npPos(16,32,18);
	npPos(17,33,19);
	npPos(18,34,16);
	npPos(19,32,17);

	for(a = 0;a < 41;a ++){
		if(a > 30 && a < 41){
			for(b = 16;b <= 19;b ++){
				npMove(b,0,1);
			}
		}

		if(a < 6)
			npMove(13,0,1);
		else if(a < 9)
			npMove(13,-1,0);
		else if(a < 15)
			npMove(13,0,1);
		else if(a < 26)
			npMove(13,1,0);
		else
			npMove(13,0,1);

		evFrame();
	}
	np->Data.MoveSpeed = 2;

	evFrameWait(100);
	mes.ReadDraw();
	evFrameWait(250);

	//---村長が！！
	mes.ReadDraw();
	evFrameWait(100);
	npDir(19,WEST);
	evFrameWait(100);
	npDir(17,WEST);
	evFrameWait(100);
	npDir(16,WEST);
	evFrameWait(100);
	npDir(18,WEST);
	evFrameWait(250);

	for(a = 0;a < 17;a ++){
		if(a < 9)
			mcMove(-1,0);
		else
			mcMove(0,-1);
		evFrame();
	}

	for(a = 0;a < 30;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	//---村長宅
	evFadeOut();
	crfieldChangeScene(1,8,7);
	npPos(0,5,4);
	npDir(0,NORTH);
	npPos(2,4,4);
	npDir(2,EAST);

	evFieldNoFlip(0,1);
	evFadeIn();

	evFrameWait(500);

	//---ディザ
	npPos(4,12,3);
	npDir(4,SOUTH);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(4,0,1);
		evFrame();
	}
	npDir(4,WEST);
	//---ルナン
	npPos(3,12,3);
	npDir(3,SOUTH);
	evFrameWait(250);
	npMove(3,0,1);
	evFrame();
	evFrameWait(100);
	npDir(3,WEST);
	evFrameWait(250);

	mes.ReadDraw();
	//---ライゼルのしっかりしろ！
	npPos(6,12,3);
	npDir(6,WEST);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(6,-1,0);
		evFrame();
	}
	//---ナック
	npPos(5,12,3);
	npDir(5,WEST);

	for(a = 0;a < 9;a ++){
		if(a < 1)
			npMove(6,0,1);
		else if(a < 5)
			npMove(6,-1,0);

		if(a < 2)
			npMove(5,-1,0);
		else if(a < 3)
			npMove(5,0,1);
		else if(a < 6)
			npMove(5,-1,0);
		else if(a < 7)
			npMove(5,0,1);
		else if(a < 9)
			npMove(5,-1,0);

		evFrame();
	}
	evFrameWait(150);
	npDir(5,NORTH);
	evFrameWait(150);
	//---しっかりするんじゃ
	mes.ReadDraw(3);
	evFrameWait(250);
	//---わたしも手伝う
	for(a = 0;a < 8;a ++){
		if(a < 5)
			npMove(3,-1,0);
		else if(a < 6)
			npMove(3,0,-1);
		else if(a < 8)
			npMove(3,-1,0);
		evFrame();
	}
	evFrameWait(150);
	npDir(3,SOUTH);
	evFrameWait(150);
	mes.ReadDraw(2);

	//---さがしてくる
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(6,NORTH);
	evFrameWait(150);
	npDir(6,EAST);
	evFrameWait(150);
	mes.ReadDraw(3);

	evFrameWait(250);
	npDir(4,NORTH);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(4,0,-1);
		evFrame();
	}
	evFrameWait(100);
	npShow(4,0);
	evFrameWait(1000);

	//---村長ベッドへ
	crmusicPlay(CRMUSIC_VILLAGE1);
	evFadeOut();
	npPos(0,0,0);
	npShow(0,0);

	npPos(1,3,2);
	npDir(1,NORTH);
	npPos(2,4,4);
	npDir(2,NORTH);

	npPos(3,5,3);
	npDir(3,WEST);
	npPos(5,4,2);
	npDir(5,WEST);
	npPos(6,5,4);
	npDir(6,NORTH);
	evFieldNoFlip(0,1);
	evFadeIn();

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(5,SOUTH);
	evFrameWait(500);
	//---絶対安静
	mes.ReadDraw();
	evFrameWait(1000);

	//---ディザ
	npPos(4,12,3);
	npDir(4,SOUTH);
	evFrameWait(250);
	for(a = 0;a < 4;a ++){
		if(a < 1)
			npMove(4,0,1);
		else
			npMove(4,-1,0);

		if(a == 1)
			npDir(3,SOUTH);
		if(a == 2)
			npDir(3,EAST);
		if(a == 2)
			npDir(5,EAST);
		if(a == 3)
			npDir(6,EAST);
		if(a == 3)
			npDir(2,EAST);

		evFrame();
	}
	evFrameWait(250);
	//---どう？
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(6,SOUTH);
	evFrameWait(250);
	npDir(6,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(200);
	npDir(3,SOUTH);
	evFrameWait(200);
	npDir(5,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(3);

	//---追うんだろ？
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(6,NORTH);
	evFrameWait(250);
	mes.ReadDraw(4);
	evFrameWait(500);
	npDir(3,SOUTH);
	evFrameWait(500);

	mes.ReadDraw();
	evFrameWait(500);

	for(a = 0;a < 10;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}

	mes.CloseMessage();
	evSet(99,1);
	mcDir(SOUTH);
	mcShow(1);
	evReloadMap(0);
	evScene(1,7,4);

	return 1;
}

//---自由市でオーブが！！
CREVENTLONG2_API int creventNorthTereia_JiyuichiOve(int event)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	int dir;

	//---方向
	if(event <= 219)
		dir = 0;
	else if(event <= 223)
		dir = 1;
	else
		dir = 2;

	evFrameWait(100);
	mes.OpenMessage("NorthTereia.msg",102);
	mes.ReadDraw(2);
	evFrameWait(250);
	
	//---急行！！
	npPos(42,36,22);
	npDir(42,SOUTH);
	mcShow(0);
	evReloadMap(0);
	evScene(0,36,24);

	if(dir == 0){
		npPos(45,41,34);
		npDir(45,WEST);

		for(a = 0;a < 14;a ++){
			if(a < 4)
				npMove(45,-1,0);
			else if(a < 10)
				npMove(45,0,-1);
			else if(a < 11)
				npMove(45,-1,0);
			else if(a < 14)
				npMove(45,0,-1);
			evFrame();
		}
	} else if(dir == 1){
		npPos(45,29,16);
		npDir(45,SOUTH);

		for(a = 0;a < 16;a ++){
			if(a < 4)
				npMove(45,0,1);
			else if(a < 5)
				npMove(45,1,0);
			else if(a < 10)
				npMove(45,0,1);
			else if(a < 16)
				npMove(45,1,0);
			evFrame();
		}
		npDir(45,NORTH);
	} else {
		npPos(45,23,25);
		npDir(45,EAST);

		for(a = 0;a < 13;a ++){
			npMove(45,1,0);
			evFrame();
		}
		npDir(45,NORTH);
	}

	evFrameWait(250);
	npDir(42,WEST);
	evFrameWait(250);
	npDir(42,SOUTH);
	evFrameWait(250);
	npDir(42,EAST);
	evFrameWait(250);
	npDir(42,SOUTH);
	evFrameWait(250);

	mes.ReadDraw(3);

	//---逃げる
	evFrameWait(250);
	npDir(42,WEST);
	evFrameWait(250);
	for(a = 0;a < 24;a ++){
		if(a < 7)
			npMove(42,-1,0);
		else
			npMove(42,0,-1);

		if(a < 6){
		} else if(a < 13)
			npMove(45,-1,0);
		else
			npMove(45,0,-1);

		evFrame();

		if(a == 4)
			npDir(45,WEST);
		if(a == 5){
			mes.ReadDraw();
		}
	}

	//---見失う
	npPos(45,29,13);
	npDir(45,NORTH);
	npPos(46,19,13);
	npDir(46,NORTH);
	npPos(47,17,12);
	npDir(47,NORTH);
	npPos(48,18,14);
	npDir(48,NORTH);

	evReadObject(7,"TwPpl2m_down.acf");
	evScene(0,29,14);

	evFrameWait(1000);
	npDir(45,EAST);
	evFrameWait(250);
	npDir(45,NORTH);
	evFrameWait(250);
	npDir(45,WEST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---みんなくる
	for(a = 0;a < 9;a ++){
		for(b = 46;b <= 48;b ++){
			npMove(b,1,0);
		}
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(1000);
	mes.ReadDraw(2);
	//---ルナン振り返る
	evFrameWait(250);
	npDir(45,NORTH);
	evFrameWait(250);
	npDir(45,EAST);
	evFrameWait(250);

	npPos(49,45,8);
	npDir(49,NORTH);

	//---男が倒れてる
	for(a = 0;a < 14;a ++){
		mcMove(1,0);
		evFrame();
	}

	for(a = 0;a < 17;a ++){
		for(b = 45; b <= 48;b ++){
			if(b <= 46 && a < 16)
				npMove(b,1,0);
			else if(b >= 47 && a)
				npMove(b,1,0);
		}
		if(a == 16)
			npDir(45,NORTH);
		evFrame();
	}
	npDir(46,NORTH);
	evFrameWait(100);
	npDir(47,NORTH);
	evFrameWait(100);
	npDir(48,NORTH);
	evFrameWait(250);

	mes.ReadDraw();
	evFrameWait(250);
	//---ルナン近づく
	for(a = 0;a < 3;a ++){
		npMove(45,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---うばわれたでげす
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(700);
	mes.ReadDraw();
	evFrameWait(1000);

	//---ベッド
	evReadObject(7,"TwPpl2m_Slp.acf");
	npPos(49,12,6);
	npDir(49,NORTH);

	npPos(47,18,12);
	npDir(47,SOUTH);
	npPos(45,17,13);
	npDir(45,NORTH);
	npPos(46,18,13);
	npDir(46,NORTH);
	npPos(48,19,13);
	npDir(48,NORTH);

	npPos(47,12,8);
	npDir(47,WEST);
	npDir(25,EAST);
	evScene(0,11,11);
	evFrameWait(2000);

	for(a = 0;a < 7;a ++){
		mcMove(1,0);
		evFrame();
	}
	for(a = 0;a < 4;a ++){
		mcMove(0,1);
		evFrame();
	}

	for(a = 0;a < 10;a ++){
		if(a < 3)
			npMove(47,0,1);
		else if(a < 9)
			npMove(47,1,0);
		else if(a < 10)
			npMove(47,0,1);

		if(a == 3)
			npDir(45,WEST);
		if(a == 7)
			npDir(45,NORTH);
		if(a == 5)
			npDir(46,WEST);
		if(a == 8)
			npDir(46,NORTH);
		if(a == 1)
			npDir(48,WEST);
		if(a == 6)
			npDir(48,NORTH);

		evFrame();
	}
	evFrameWait(500);

	mes.ReadDraw(2);
	evFrameWait(1000);
	mes.ReadDraw(6);
	evFrameWait(500);

	for(a = 45;a <= 48;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	mcShow(1);
	mcDir(SOUTH);
	evScene(0,18,13);

	evSet(104,3);
	npPos(42,0,0);
	npShow(42,0);

	return 1;
}

//---ノーステリア、夜の襲撃
CREVENTLONG2_API int creventNorthTereia_NightTozoku(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mes.OpenMessage("NorthTereia.msg",104);
	mes.ReadDraw(2);
	evFrameWait(250);

	//---ルナンの夢
	crmusicFadeOut();
	evFadeOut(2000);

	crfieldChangeMap(48,0,1,0);
	crfieldChangeScene(0,8,8);
	crmusicStop();
	mcShow(0);
	evFieldNoFlip(0,1);
	evWait(2000,1);
	evFadeIn(2000);
	evFrameWait(2000);

	//---さあいくぞ
	npPos(2,13,5);
	npDir(2,WEST);
	evFrameWait(500);
	npMove(2,-1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(0,NORTH);
	evFrameWait(500);
	npDir(0,EAST);
	evFrameWait(500);
	npDir(1,EAST);
	evFrameWait(500);
	npMove(1,1,0);
	evFrame();
	evFrameWait(500);

	mes.ReadDraw();
	evFrameWait(500);

	for(a = 0;a < 6;a ++){
		npMove(2,-1,0);
		if(a == 4)
			npDir(1,NORTH);
		if(a == 5)
			npDir(0,NORTH);
		evFrame();
	}
	evFrameWait(250);
	npDir(2,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	//---夢フェードアウト
	evFadeOut(2000);
	crfieldChangeMap(39,1,1,0);
	crfieldChangeScene(1,17,18);
	evReadObject(2,"NTTozoku.acf");
	evReadObject(7,"Lunarn.acf");
	evReadObject(12,"LunarnSlp2.acf");
	evReadObject(14,"NackSlp.acf");
	crfieldPaletteChange(PALETTE_NIGHT);

	npPos(0,13,14);
	npDir(0,SOUTH);
	npPos(2,14,14);
	npDir(2,SOUTH);

	em->Put(9,17,2,40);
	evFieldNoFlip(0,1);
	evWait(2000,1);
	evFadeIn(2000);

	//---宿屋
	evFrameWait(3000);
	npDir(0,WEST);
	evFrameWait(2000);

	mes.ReadDraw();

	evFrameWait(3000);
	npDir(0,NORTH);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

	//---ルナンベッドから立つ
	npPos(0,0,0);
	npShow(0,0);
	npPos(5,12,14);
	npShow(5,SOUTH);
	evScene(1,17,18);

	evFrameWait(1000);

	for(a = 0;a < 3;a ++){
		npMove(5,0,1);
		evFrame();
	}
	evFrameWait(500);
	npDir(5,WEST);
	evFrameWait(1000);
	//---ふーあーゆー
	mes.ReadDraw();

	evFrameWait(3000);
	mes.ReadDraw();

	evFrameWait(1000);
	npMove(5,-1,0);
	evFrame();
	evFrameWait(1000);
	mes.ReadDraw();

	//---あいむでぃざ
	evFrameWait(1000);
	mes.ReadDraw();

	//---こんな夜中に
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npMove(5,-1,0);
	evFrame();
	evFrameWait(500);

	//---ドア開ける
	npPos(4,8,17);
	npDir(4,EAST);
	em->Put(9,17,2,1024);

	//---とびこみ
	crmusicPlay(CRMUSIC_HEAT);
	evFrameWait(250);
	npMove(4,1,0);
	evFrame();
	evFrameWait(150);

	//---ルナン後ずさる
	npMove(5,1,0,0);
	evFrame();
	npMove(4,1,0);
	evFrame();
	evFrameWait(150);
	mes.ReadDraw(2);

	evFrameWait(250);
	npMove(5,1,0,0);
	evFrame();
	evFrameWait(500);

	npMove(4,1,0);
	evFrame();
	evFrameWait(250);

	npMove(5,0,-1,0);
	evFrame();
	evFrameWait(250);
	npDir(5,SOUTH);
	//---ナック密かに目覚める
	npDir(2,WEST);
	evFrameWait(500);

	npMove(4,1,0);
	evFrame();
	evFrameWait(250);
	npDir(4,NORTH);
	evFrameWait(1000);

	//---どうした！？
	mes.ReadDraw();

	//---盗賊窓へ
	evFrameWait(250);
	for(a = 0;a < 4;a ++){
		if(a < 1)
			npMove(4,0,1,0);
		else
			npMove(4,1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(4,NORTH);
	evFrameWait(150);
	npDir(4,WEST);
	evFrameWait(150);

	mes.ReadDraw();
	evFrameWait(250);
	for(a = 0;a < 4;a ++){
		npMove(4,1,0,0);
		evFrame();
	}
	npShow(4,0);
	evFrameWait(250);

	//---かなり遅い人
	npPos(1,8,17);
	npDir(1,EAST);
	npPos(3,7,17);
	npDir(3,EAST);
	evFrameWait(250);

	crmusicFadeOut();
	for(a = 0;a < 3;a ++){
		npMove(1,1,0);
		npMove(3,1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(5,WEST);
	evFrameWait(1000);

	evReloadMap(0);
	crfieldPaletteChange(PALETTE_NIGHT);
	npPos(5,13,6);
	npShow(5,0);

	crmusicStop();
	crfieldChangeScene(1,0,0);
	npPos(0,13,16);
	npDir(0,SOUTH);
	npPos(1,14,17);
	npDir(1,WEST);
	npPos(2,13,18);
	npDir(2,NORTH);
	npPos(3,12,17);
	npDir(3,EAST);
	evScene(1,17,18);
	evFrameWait(1000);

	mes.ReadDraw(7);
	evFrameWait(500);

	//---夜が明ける
	prtRecoveryAll();
	evReloadMap(1);
	mcShow(1);
	mcDir(NORTH);
	evScene(0,12,39);

	evSet(105,1);
	mes.CloseMessage();

	return 1;
}

//---ノーステリアの洞窟、落とし穴
CREVENTLONG2_API int creventNorthTereiaDokutsu_Otoshiana(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	npPos(1,13,13);
	npDir(1,NORTH);
	npPos(2,12,13);
	npDir(2,WEST);
	npPos(3,14,12);
	npDir(3,WEST);
	npPos(4,11,13);
	npDir(4,WEST);

	evScene(2,12,13);

	evFrameWait(500);
	mes.OpenMessage("NTDangeon.msg",100);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(2,NORTH);
	evFrameWait(300);
	npDir(2,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(4,NORTH);
	evFrameWait(300);
	npDir(4,EAST);
	evFrameWait(500);

	evFrameWait(500);
	crsoundPlay(CRSOUND_ANAAKU);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

	//---穴が空く
	crsoundPlay(CRSOUND_ATACK4);
	em->Put(13,13,1,16);
	evFrameWait(250);
	npShow(1,0);
	evFrameWait(250);

	crsoundPlay(CRSOUND_ATACK4);
	em->Put(12,13,1,16);
	evFrameWait(250);
	npShow(2,0);
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);

	crsoundPlay(CRSOUND_ATACK4);
	em->Put(13,12,1,16);
	evFrameWait(50);
	crsoundPlay(CRSOUND_ATACK4);
	em->Put(14,13,1,16);
	evFrameWait(250);
	crsoundPlay(CRSOUND_ATACK4);
	em->Put(14,12,1,16);
	evFrameWait(250);
	npShow(3,0);
	evFrameWait(250);

	evFrameWait(1000);

	//---下の階へ
	crfieldChangeScene(3,19,16);
	npPos(0,18,12);
	npDir(0,EAST);
	npPos(1,16,13);
	npDir(1,EAST);
	npPos(2,21,11);
	npDir(2,SOUTH);
	evScene(3,19,16);
	evFrameWait(1000);

	mes.ReadDraw(3);
	evFrameWait(1000);
	npDir(1,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(0,SOUTH);
	evFrameWait(1000);

	//---ライゼル外す
	pPartyInfo->PartyMember[3] = -1;
	
	//---バトル
	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.Music = CRMUSIC_BATTLE;
	BattleInfo.Enemy[0].Enemy = 83;
	BattleInfo.Enemy[0].x = 6;
	BattleInfo.Enemy[0].y = 7;
	BattleInfo.Enemy[1].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	evField(0,1);
	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}

	//---盗賊登場
	npPos(4,18,26);
	npDir(4,NORTH);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(300);
	npDir(0,SOUTH);
	evFrameWait(200);
	npDir(2,SOUTH);
	evFrameWait(500);
	for(a = 0;a < 10;a ++){
		npMove(4,0,-1);
		evFrame();
	}
	//---このやろう
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw(4);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(3);

	evFrameWait(300);
	npMove(1,0,1);
	evFrame();
	evFrameWait(500);

	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(4);
	evFrameWait(500);

	//---バトル
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.Music = CRMUSIC_BOSSBATTLE1;
	BattleInfo.Enemy[0].Enemy = 91;
	BattleInfo.Enemy[0].x = 7;
	BattleInfo.Enemy[0].y = 9;
	BattleInfo.Enemy[1].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	evField(0,1);

	npPos(0,17,14);
	npDir(0,NORTH);
	npPos(1,19,13);
	npDir(1,NORTH);
	npPos(2,21,14);
	npDir(2,NORTH);
	npPos(4,19,11);
	npDir(4,SOUTH);
	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}

	evFrameWait(1000);
	//---ぐ
	mes.ReadDraw();
	evFrameWait(1000);
	mcMove(0,-1);
	evFrame();
	evFrameWait(500);
	//---ノーステリアいこうか
	mes.ReadDraw();

	evFrameWait(500);
	npMove(1,0,-1);
	evFrame();
	evFrameWait(500);
	//---なんてな
	mes.ReadDraw();
	evFrameWait(250);
	npMove(4,0,-1,0);
	evFrame();

	//---穴が空く
	crsoundPlay(CRSOUND_ATACK4);
	em->Put(19,10,1,16);
	evFrameWait(100);
	npShow(4,0);
	evFrameWait(250);

	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);

	//---追うぞ
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npMove(1,0,-1);
	evFrame();
	evFrameWait(250);

	//---下の階から
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);

	//---例の音楽
	crmusicPlay(CRMUSIC_LIZEL);
	evFrameWait(1500);
	npDir(0,EAST);
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(700);
	mes.ReadDraw();
	evFrameWait(1000);
	npMove(2,0,-1);
	evFrame();
	evFrameWait(300);
	//---お師匠様！？
	mes.ReadDraw();
	evFrameWait(2000);
	
	crmusicStop();
	evFrameWait(3000);
	mes.ReadDraw();
	evFrameWait(1000);
	crmusicPlay(CRMUSIC_DANGEON1);
	//---悲鳴
	mes.ReadDraw();
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---ライゼル加える
	pPartyInfo->PartyMember[3] = 5;
	pPartyInfo->PartyMember[4] = -1;

	//---ノーステリア
	crfieldChangeMap(39,4,1,1);
	npPos(0,4,3);

	npPos(2,10,14);
	npDir(2,SOUTH);
	npPos(3,9,15);
	npDir(3,EAST);
	npPos(4,12,15);
	npDir(4,WEST);
	npPos(5,11,16);
	npDir(5,NORTH);
	evScene(4,11,17);

	//---おっちゃん運いいね
	evFrameWait(1500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	npDir(5,WEST);
	evFrameWait(500);
	mes.ReadDraw();
	//---いいわ・・・
	evFrameWait(500);
	mes.ReadDraw(3);

	//---議長来る
	for(a = 0;a < 15;a ++){
		if(a < 12)
			npMove(0,0,1);
		else
			npMove(0,1,0);

		if(a == 10)
			npDir(3,NORTH);
		if(a == 11)
			npDir(3,WEST);
		if(a == 12)
			npDir(2,WEST);
		if(a == 13)
			npDir(5,WEST);

		evFrame();
	}
	evFrameWait(500);


	mes.ReadDraw(3);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(4);

	//---なぜそのようなことを
	evFrameWait(500);
	mes.ReadDraw(4);

	//---いいの
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npMove(0,1,0);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw(5);
	evFrameWait(500);

	//---それじゃ、失礼します
	for(a = 3;a <= 5;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	npPos(0,11,15);
	npDir(0,WEST);
	npPos(2,10,15);
	npDir(2,EAST);
	evScene(4,10,16);
	evFrameWait(500);
	mes.ReadDraw();

	npDir(2,NORTH);
	evFrameWait(250);
	npDir(2,WEST);
	evFrameWait(250);

	for(a = 0;a < 2;a ++){
		npMove(2,-1,0);
		evFrame();
	}
	evFrameWait(250);
	//---ガゼールさんも・・・
	mes.ReadDraw(2);

	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);
	npDir(2,EAST);
	evFrameWait(500);
	//---ありがとう
	mes.ReadDraw();

	evFrameWait(500);
	npDir(2,NORTH);
	evFrameWait(250);
	npDir(2,WEST);
	evFrameWait(250);

	for(a = 0;a < 15;a ++){
		if(a < 4)
			npMove(2,-1,0);
		else
			npMove(2,0,-1);
		evFrame();
	}
	npPos(2,0,0);
	npShow(2,0);

	mcShow(1);
	mcDir(SOUTH);
	evSet(106,1);
	prtRecoveryAll();
	evScene(0,22,6);

	mes.CloseMessage();

	return 1;
}

//---ノーステリアの遺跡、日記
CREVENTLONG2_API int creventNorthTereiaIseki_Nikki(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	crfieldChangeScene(3,12,8);
	npPos(1,11,5);
	npDir(1,SOUTH);
	npPos(2,12,5);
	npDir(2,SOUTH);
	npPos(3,13,5);
	npDir(3,SOUTH);
	npPos(4,13,6);
	npDir(4,SOUTH);
	evScene(3,14,7);

	evFrameWait(500);
	for(a = 0;a < 2;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(500);
	mes.OpenMessage("NorthTereiaIseki.msg",104);
	mes.ReadDraw();

	evFrameWait(250);
	npMove(2,0,1);
	evFrame();
	evFrameWait(250);
	//---本があるぞ
	mes.ReadDraw(2);
	evFrameWait(500);

	//---読書
	npPos(1,10,7);
	npDir(1,SOUTH);
	npPos(2,11,7);
	npDir(2,WEST);
	npPos(3,10,9);
	npDir(3,NORTH);
	npPos(4,11,8);
	npDir(4,WEST);
	evScene(3,12,9);

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---日記
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw(3);
	evFrameWait(500);

	//---他のは？
	mes.ReadDraw(2);
	evFrameWait(1500);
	mes.ReadDraw(5);

	//---なるほどね
	evFrameWait(1000);
	mes.ReadDraw(3);

	//---ダメね
	evFrameWait(2000);
	mes.ReadDraw();

	//---大陸協会の
	evFrameWait(1000);
	mes.ReadDraw(11);

	//---でもまだ
	evFrameWait(1000);
	mes.ReadDraw(12);

	//---！
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(1000);
	mes.ReadDraw(4);
	//---ルナン・・・
	evFrameWait(1000);
	mes.ReadDraw(2);

	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(1000);
	mes.ReadDraw(3);
	evFrameWait(500);


	mes.CloseMessage();

	for(a = 1;a <= 4;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}

	mcDir(SOUTH);
	mcShow(1);
	evScene(3,12,8);
	evSet(110,1);

	return 1;
}

//---ノーステリアの遺跡、記録パネル
CREVENTLONG2_API int creventNorthTereiaIseki_KirokuPanel(int mode)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	while(1){
		int res;
		eistr str[250],*p = str,*title[] = {
			"生命兵器　ＣＲ－Ｅについて","ＣＲ－Ｅの実践投入","ＣＲ－Ｅの経過",
			"先日の戦闘について","今後について"
		};

		crbaseMenuReset();

		for(a = evGet(113);a >= 0;a --){
			sprintf(p,"%s;",title[a]);
			p += (strlen(title[a]) + 1);
		}

		CrSelectWindow win;
		win.Create(64,64,16,9,"選択してください",str);
		win.Refresh();
		crbaseMenuStart();

		res = win.Select();
		if(res == -1 && mode == 0){
			break;
		}

		if(res != -1){
			mes.FileMessage("NorthTereiaIseki.msg",107 + (evGet(113) - res));
		}
		if(res == 0 && mode == 1){
			//---次の項目
			if(evGet(113) == 4){
				break;
			} else {
				mes.FileMessage("NorthTereiaIseki.msg",112 + evGet(113) - 1);
				evSet(113,evGet(113) + 1);
			}
		}
	}
	crbaseMenuReset();
	crbaseMenuStart();

	return 1;
}

//---ノーステリアの遺跡、最深部
CREVENTLONG2_API int creventNorthTereiaIseki_Saishinbu(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	evFrameWait(500);
	mes.OpenMessage("NorthTereiaIseki.msg",106);
	mes.ReadDraw();
	evFrameWait(500);

	//---バトル
	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.Music = CRMUSIC_BOSSBATTLE1;
	BattleInfo.Enemy[0].Enemy = 87;
	BattleInfo.Enemy[0].x = 5;
	BattleInfo.Enemy[0].y = 8;
	BattleInfo.Enemy[1].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	evField(0,1);

	//---
	mcShow(0);
	crfieldChangeScene(4,9,17);
	npPos(0,9,16);
	npDir(0,SOUTH);
	npPos(1,9,17);
	npDir(1,SOUTH);
	npPos(2,8,17);
	npDir(2,SOUTH);
	npPos(3,8,16);
	npDir(3,SOUTH);

	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}

	//---ここを守ってたの
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	for(a = 0;a < 1;a ++){
		npMove(2,0,1);
		evFrame();
	}
	evFrameWait(250);
	npDir(2,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---ディザ動く
	evFrameWait(250);
	for(a = 0;a < 1;a ++){
		npMove(1,0,1);
		evFrame();
	}
	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(250);

	//---ルナン
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(0,0,1);
		npMove(2,-1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(0,WEST);
	npDir(2,NORTH);
	evFrameWait(250);
	for(a = 0;a < 1;a ++){
		npMove(2,0,-1);
		evFrame();
	}
	//---あ
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(250);
	for(a = 0;a < 1;a ++){
		npMove(3,0,1);
		evFrame();
	}
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	for(a = 0;a < 4;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(1000);
	//---研究所
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw(3);

	evFrameWait(500);
	npDir(3,SOUTH);
	evFrameWait(250);
	//---あれに見えるは
	mes.ReadDraw();

	//---ライゼル移動
	evFrameWait(250);
	for(a = 0;a < 4;a ++){
		if(a == 0)
			npDir(2,EAST);
		if(a == 1)
			npDir(2,SOUTH);
		if(a == 2)
			npDir(0,SOUTH);
		if(a == 3)
			npDir(1,SOUTH);
		npMove(3,0,1);
		evFrame();
	}

	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(100);
	for(a = 0;a < 1;a ++){
		npMove(3,-1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(500);

	//---起動
	crsoundPlay(CRSOUND_MASINBTN);
	evFrameWait(500);
	crsoundPlay(CRSOUND_KIDOU);
	evFrameWait(1500);
	em->Put(7,20,2,108);
	evFrameWait(1500);
	mes.ReadDraw();
	evFrameWait(500);
	//---触れたら・・・
	mes.ReadDraw();
	evFrameWait(500);

	//---みんな集合
	npPos(0,8,21);
	npDir(0,WEST);
	npPos(1,8,22);
	npDir(1,NORTH);
	npPos(2,6,21);
	npDir(2,EAST);
	evScene(4,7,22);
	evFrameWait(500);

	//---本の代わり？
	mes.ReadDraw(2);
	evFrameWait(1000);
	crsoundPlay(CRSOUND_MASINBTN);
	evFrameWait(1000);

	mes.ReadDraw();

	//---内容
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(1000);
	mes.ReadDraw(2);

	//---続き
	evFrameWait(1000);
	mes.ReadDraw();

	//---これがわたし？
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(250);
	mes.ReadDraw();

	//---そんなことって！
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(700);
	mes.ReadDraw();


	//---ライゼル振り向く
	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw(2);

	//---別のもの
	evFrameWait(500);
	npDir(3,NORTH);
	evFrameWait(500);
	crsoundPlay(CRSOUND_MASINBTN);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(0,WEST);
	evFrameWait(200);
	mes.CloseMessage();

	//---選択
	evSet(113,1);
	creventNorthTereiaIseki_KirokuPanel(1);

	evFrameWait(500);
	mes.OpenMessage("NorthTereiaIseki.msg",115);
	//---どういうこと？
	mes.ReadDraw(3);
	evFrameWait(500);
	npDir(3,EAST);
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	npDir(1,WEST);
	evFrameWait(500);
	//---さあな
	mes.ReadDraw();
	evFrameWait(500);
	npDir(1,NORTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---あれは
	evFrameWait(500);
	npDir(0,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(250);
	npDir(2,SOUTH);
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);

	for(a = 0;a < 3;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	for(a = 0;a <= 3;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	mcShow(1);
	mcDir(SOUTH);
	evScene(4,7,21);
	mes.CloseMessage();

	evSet(112,1);

	return 1;
}

//---マークス、フォールン登場
CREVENTLONG2_API int creventMarks_Follne(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	npPos(29,26,12);
	npDir(29,NORTH);

	for(a = 0;a < 10;a ++){
		npMove(29,0,-1);
		evFrame();
	}
	crmusicPlay(CRMUSIC_ETERNAL);
	mes.OpenMessage("Marks.msg",101);
	mes.ReadDraw(4);
	evFrameWait(700);
	mes.ReadDraw();

	//---フォールンしかと
	evFrameWait(500);
	npDir(29,WEST);
	for(a = 0;a < 16;a ++){
		if(a < 1)
			npMove(29,-1,0);
		else
			npMove(29,0,-1);
		evFrame();
	}
	evFrameWait(500);
	crmusicPlay(CRMUSIC_TOWN2);

	mes.ReadDraw(5);
	evFrameWait(500);
	npPos(29,0,0);
	npShow(29,0);
	mes.CloseMessage();

	evSet(119,1);

	return 1;
}

//---マークス、ライゼルと町長と顔を忘れられたダイの村人Ａ
CREVENTLONG2_API int creventMarks_LizelAndChocho(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	evField(0,1);
	mes.OpenMessage("Marks.msg",102);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(15,EAST);
	evFrameWait(250);
	//---終わったみたいだな
	mes.ReadDraw();
	evFrameWait(250);

	for(a = 0;a < 12;a ++){
		if(a < 2)
			npMove(15,1,0);
		else if(a < 4)
			npMove(15,0,1);
		else
			npMove(15,1,0);
		evFrame();
	}
	evFrameWait(250);

	mcMove(1,0);
	evFrame();
	evFrameWait(250);

	//---ライゼルはいるのを渋る
	npPos(25,36,38);
	npDir(25,NORTH);
	npPos(26,35,37);
	npDir(26,NORTH);
	npPos(27,36,36);
	npDir(27,WEST);
	npPos(28,33,35);
	npDir(28,EAST);
	mcShow(0);
	evScene(0,34,38);

	//---どうしたの？
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw(2);

	evFrameWait(250);
	//---町長登場
	for(a = 0;a < 6;a ++){
		if(a == 2)
			npMove(32,0,1);
		else
			npMove(32,-1,0);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	evFrameWait(250);
	npDir(25,EAST);
	npDir(27,SOUTH);
	evFrameWait(150);
	npDir(26,EAST);
	evFrameWait(250);

	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	//---やはりこの町は
	mes.ReadDraw();
	//---どうする？
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---難しく考えるなよ
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	npMove(32,-1,0);
	evFrame();
	evFrameWait(250);

	//---おっちゃん
	evFrameWait(500);
	npDir(25,NORTH);
	evFrameWait(250);
	npDir(25,WEST);
	evFrameWait(250);
	npMove(25,-1,0);
	evFrame();
	evFrameWait(250);
	npDir(25,NORTH);
	evFrameWait(250);

	mes.ReadDraw();
	evFrameWait(250);
	npMove(32,-1,0);
	evFrame();
	evFrameWait(250);
	npDir(32,NORTH);
	evFrameWait(250);

	//---ライゼルはいる
	for(a = 0;a < 2;a ++){
		npMove(28,1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(28,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);

	//---お前は・・・
	evFrameWait(1000);
	mes.ReadDraw();
	//--知り合いなのか？
	evFrameWait(250);
	npDir(26,SOUTH);
	evFrameWait(500);
	npDir(26,EAST);
	evFrameWait(250);
	npDir(26,NORTH);
	evFrameWait(500);

	mes.ReadDraw();

	//---いまさらなにをしに
	evFrameWait(1000);
	mes.ReadDraw();

	//---
	evFrameWait(250);
	npDir(26,EAST);
	evFrameWait(250);
	npDir(26,SOUTH);
	evFrameWait(250);
	npDir(25,EAST);
	evFrameWait(500);
	mes.ReadDraw(3);

	evFrameWait(250);
	mes.ReadDraw(4);

	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(250);

	//---議会から出る
	evReloadMap(0);
	npPos(25,27,29);
	npDir(25,NORTH);
	npPos(26,26,30);
	npDir(26,NORTH);
	npPos(27,25,29);
	npDir(27,NORTH);
	npPos(28,25,27);
	npDir(28,SOUTH);
	evScene(0,27,32);

	evFrameWait(500);
	mes.ReadDraw();
	//---昔
	evFrameWait(1000);
	mes.ReadDraw(4);
	evFrameWait(1000);
	mes.ReadDraw(3);
	//---すまない
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(28,EAST);
	evFrameWait(500);
	npDir(28,NORTH);

	//---呼び止める声
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(26,EAST);
	evFrameWait(150);
	npDir(25,EAST);
	evFrameWait(150);
	npDir(26,SOUTH);
	npDir(27,EAST);
	evFrameWait(150);
	npDir(25,SOUTH);
	npDir(28,EAST);
	evFrameWait(150);
	npDir(27,SOUTH);
	evFrameWait(150);
	npDir(28,SOUTH);
	evFrameWait(250);

	npPos(34,36,35);
	npDir(34,WEST);
	for(a = 0;a < 12;a ++){
		if(a < 9)
			npMove(34,-1,0);
		else
			npMove(34,0,-1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw(3);

	//---だれ？
	evFrameWait(1000);
	mes.ReadDraw(5);
	evFrameWait(500);
	//---何のようなんだ？
	mes.ReadDraw(4);
	evFrameWait(500);

	//---ダイへ
	evFadeOut(1000);
	et->Delay2(1000);

	mcShow(1);
	crfieldChangeMap(40,0,1,1);
	npPos(14,34,50);
	npDir(14,SOUTH);
	mcDir(NORTH);

	crfieldChangeScene(0,34,51);
	evFieldNoFlip(0,1);
	evFadeIn(1000);
//	evScene(0,34,51);

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(14,WEST);
	evFrameWait(250);
	npDir(14,NORTH);
	evFrameWait(250);

	//---走りゆく村人
	for(a = 0;a < 15;a ++){
		npMove(14,0,-1);
		evFrame();
	}
	npPos(14,0,0);
	npShow(14,0);
	evSet(117,1);
	evSet(120,0);

	mes.CloseMessage();

	return 1;
}

//---ダイ、偽のオーブ
CREVENTLONG2_API int creventDai_NisenoOve(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;


	crfieldChangeScene(1,5,7);

	npDir(1,EAST);
	npPos(2,2,4);
	npDir(2,NORTH);

	npPos(3,4,2);
	npDir(3,WEST);
	npPos(4,3,4);
	npDir(4,NORTH);
	npPos(5,4,3);
	npDir(5,WEST);
	npPos(6,5,4);
	npDir(6,WEST);
	mcShow(0);

	evFieldNoFlip(0,1);
//	evFadeIn();
	evScene(1,5,7);
	evFrameWait(250);
	npDir(1,EAST);

	evFrameWait(1000);
	mes.OpenMessage("Dai.msg",103);
	mes.ReadDraw(4);

	//---オーブなんですが・・・
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	//---偽物なんです
	evFrameWait(2000);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(2);

	//---ガラス玉
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---見ての通り寂れた村
	evFrameWait(1000);
	mes.ReadDraw(3);

	//---振り回されてたのか？
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(3,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---申し訳ありません
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(3,WEST);
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(1000);

	//---夜！
	crmusicFadeOut();
	evFadeOut(1000);

	crfieldChangeScene(0,48,16);
	npPos(16,48,14);
	npDir(16,NORTH);
	npPos(18,49,14);
	npDir(18,NORTH);
	crfieldPaletteChange(PALETTE_NIGHT);
	for(a = 0;a <= 15;a ++){
		npPos(a,0,0);
	}

	et->Delay2(1000);
	evFieldNoFlip(0,1);
	evFadeIn(1000);
//	evScene(0,48,16);

	evFrameWait(2000);
	crmusicStop();
	mes.ReadDraw();
	//---オーブの事なんてなかったみたい
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(1000);
	npDir(18,WEST);
	evFrameWait(500);
	mes.ReadDraw(2);
	//---お師匠様
	evFrameWait(1000);
	npDir(18,NORTH);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---悪いことするような人じゃ
	evFrameWait(1000);
	npDir(18,WEST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(16,EAST);
	evFrameWait(500);

	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(16,SOUTH);
	evFrameWait(500);
	for(a = 0;a < 15;a ++){
		npMove(16,0,1);
		if(a == 0){
		} else if(a < 2)
			npMove(18,-1,0);
		else
			npMove(18,0,1);
		evFrame();
	}
	evFrameWait(500);

	//---夜が明ける
	//---微睡みのルナン
	evScene(2,16,16);
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---目を覚ます
	evReloadMap(1);
	crfieldChangeScene(0,27,43);
	npPos(16,28,40);
	npDir(16,WEST);
	npPos(17,26,40);
	npDir(17,EAST);
	npPos(18,28,41);
	npDir(18,WEST);
	evScene(0,27,43);

	evFrameWait(500);
	mes.ReadDraw(3);

	//---しょぼんでちゃダメよ
	evFrameWait(500);
	npDir(16,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(250);
	npDir(16,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(18,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---どうにかしたかったんじゃないかな
	evFrameWait(500);
	mes.ReadDraw(3);

	evFrameWait(500);
	mes.CloseMessage();

	//---ライゼル外す
	{
		pPartyInfo->PartyMember[3] = -1;
		crcharaLoadFace(-1);
	}
	mcShow(1);
	mcDir(SOUTH);
	for(a = 16;a <= 19;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	prtRecoveryAll();
	evScene(0,26,41);
	evReloadMapMusic();

	evSet(120,1);

	return 1;
}


//---マークス、ライゼルの過去とエターナル襲撃
CREVENTLONG2_API int creventMarks_LizelEternal(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	npPos(5,15,14);
	npDir(5,NORTH);
	npPos(6,16,14);
	npDir(6,NORTH);
	npPos(7,15,13);
	npDir(7,NORTH);
	npPos(8,13,7);
	npDir(8,NORTH);
	mcShow(0);
	evScene(0,14,9);

	crmusicFadeOut();
	evFrameWait(2000);
	for(a = 0;a < 6;a ++){
		mcMove(0,1);
		evFrame();
	}
	crmusicStop();
	evFrameWait(250);
	npMove(7,0,-1);
	evFrame();
	evFrameWait(250);
	//---おししょうさま！
	mes.OpenMessage("Marks.msg",104);
	mes.ReadDraw();

	//---ライゼル振り向く
	for(a = 0;a < 3;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(1000);
	npDir(8,EAST);
	evFrameWait(500);
	npDir(8,SOUTH);
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	for(a = 0;a < 8;a ++){
		if(a < 2)
			npMove(7,-1,0);
		else if(a < 5)
			npMove(7,0,-1);

		if(a == 0){
		} else if(a < 2)
			npMove(5,0,-1);
		else if(a < 5)
			npMove(5,-1,0);
		else if(a < 8)
			npMove(5,0,-1);

		if(a < 2){
		} else if(a < 4)
			npMove(6,0,-1);
		else if(a < 5)
			npMove(6,-1,0);
		else if(a < 8)
			npMove(6,0,-1);

		evFrame();
	}
	for(a = 0;a < 1;a ++){
		mcMove(0,-1);
		evFrame();
	}
	//---教えてよ
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(2000);
	mes.ReadDraw();
	//---ライゼル向こうを向く
	evFrameWait(500);
	npDir(8,WEST);
	evFrameWait(500);
	npDir(8,NORTH);
	crmusicPlay(CRMUSIC_LIZELPASSED);
	evFrameWait(1000);
	mes.ReadDraw();

	//---賞金稼ぎ？
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw(3);

	//---あの人達も・・・
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw(5);

	//---町長って・・・
	evFrameWait(1000);
	mes.ReadDraw(2);
	//---でもよ
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(2000);
	mes.ReadDraw(3);
	//---なめていた
	evFrameWait(2000);
	mes.ReadDraw();

	evFrameWait(2000);
	mes.ReadDraw(3);

	evFrameWait(3000);
	mes.ReadDraw();

	//---お師匠様・・・
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---でもひどいわ！！
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw(2);
	//---エターナルの事じゃ
	evFrameWait(500);
	mes.ReadDraw();

	//---暴れん坊ライゼル
	evFrameWait(500);
	npMove(6,0,-1);
	evFrame();
	evFrameWait(1000);
	mes.ReadDraw(3);

	evFrameWait(500);
	for(a = 0;a < 2;a ++){
		npMove(5,0,-1);
		evFrame();
	}
	//---ルナンのいいこと
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(500);
	npDir(6,WEST);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---あたしいつまでも！！
	evFrameWait(500);
	npMove(7,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---すまない・・・
	evFrameWait(2000);
	npDir(8,EAST);
	evFrameWait(500);
	npDir(8,SOUTH);
	evFrameWait(1000);
	mes.ReadDraw();

	//---エターナルが来た！！
	evFrameWait(1000);
	npPos(0,0,0);
	npShow(0,0);
	npPos(2,0,0);
	npShow(2,0);
	crmusicPlay(CRMUSIC_HEAT);
	mes.ReadDraw(2);

	evFrameWait(500);
	npDir(6,SOUTH);
	evFrameWait(150);
	npDir(5,EAST);
	evFrameWait(150);
	npDir(7,EAST);
	evFrameWait(150);
	npDir(5,SOUTH);
	evFrameWait(150);
	npDir(7,SOUTH);
	evFrameWait(250);

	mes.ReadDraw(3);
	evFrameWait(500);

	//---エターナルと鉢合わせ
	evScene(0,51,37);
	npPos(5,40,35);
	npDir(5,WEST);
	npPos(6,41,36);
	npDir(6,WEST);
	npPos(7,39,36);
	npDir(7,WEST);
	npPos(8,38,34);
	npDir(8,WEST);

	npPos(9,57,28);
	npDir(9,SOUTH);
	npPos(10,56,27);
	npDir(10,SOUTH);
	for(a = 0;a < 10;a ++){
		for(b = 5;b <= 8;b ++){
			npMove(b,1,0);
		}
		if(a < 7){
			npMove(9,0,1);
			npMove(10,0,1);
		} else {
			npMove(9,-1,0);
			npMove(10,-1,0);
		}
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(4);
	evFrameWait(250);

	//---ライゼル仲間になる
	{
		pPartyInfo->PartyMember[3] = 5;
		pPartyInfo->PartyMember[4] = -1;
		crcharaLoadFace(-1);
		crcharaCheckBattleFieldPos(3);
	}

	//---バトル
	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.Music = CRMUSIC_BATTLE;
	BattleInfo.Enemy[0].Enemy = 105;
	BattleInfo.Enemy[0].x = 5;
	BattleInfo.Enemy[0].y = 6;
	BattleInfo.Enemy[1].Enemy = 104;
	BattleInfo.Enemy[1].x = 8;
	BattleInfo.Enemy[1].y = 8;
	BattleInfo.Enemy[2].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_NORMAL;
	evField(0,1);

	npPos(9,0,0);
	npShow(9,0);
	npPos(10,0,0);
	npShow(10,0);

	EVBATTLE(BattleInfo);
	
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(6,NORTH);
	evFrameWait(250);
	npDir(6,WEST);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---一回だけメニューを開ける
	crmainMainMenu(1);

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(6,NORTH);
	evFrameWait(250);
	npDir(6,EAST);
	evFrameWait(500);

	//---マークスへ
	crfieldChangeMap(41,0,1,0);
	for(a = 0;a < 40;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	npPos(35,25,8);
	npDir(35,WEST);
	npPos(36,27,15);
	npDir(36,NORTH);
	npPos(37,23,16);
	npDir(37,SOUTH);
	npPos(38,28,18);
	npDir(38,NORTH);
	npPos(39,24,24);
	npDir(39,EAST);
	npPos(40,31,21);
	npDir(40,WEST);
	evReadObject(7,"Edo.acf");
	npPos(29,31,35);
	npDir(29,EAST);
	npPos(42,30,32);
	npDir(42,SOUTH);
	npPos(41,29,34);
	npDir(41,EAST);

	evScene(0,26,1);
	//---町の中エターナルだらけ
	evFrameWait(500);
	for(a = 0;a < 33;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(500);
	npPos(41,0,0);
	npShow(41,0);
	npPos(42,0,0);
	npShow(42,0);


	npPos(25,17,54);
	npDir(25,NORTH);
	npPos(26,16,53);
	npDir(26,NORTH);
	npPos(27,16,55);
	npDir(27,NORTH);
	npPos(28,17,55);
	npDir(28,NORTH);

	npPos(35,17,39);
	npDir(35,NORTH);
	npPos(36,19,40);
	npDir(36,EAST);
	npPos(37,16,38);
	npDir(37,SOUTH);
	evScene(0,17,43);

	for(a = 0;a < 13;a ++){
		for(b = 25;b <= 28;b ++){
			npMove(b,0,-1);
		}
		if(a == 7)
			npDir(35,EAST);
		if(a == 8)
			npDir(35,SOUTH);
		if(a == 5)
			npDir(36,SOUTH);
		evFrame();
	}
	evFrameWait(250);

	//---魔法、僧侶、戦士
	//---バトル
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.Music = CRMUSIC_BATTLE;
	BattleInfo.Enemy[0].Enemy = 105;
	BattleInfo.Enemy[0].x = 4;
	BattleInfo.Enemy[0].y = 9;
	BattleInfo.Enemy[1].Enemy = 104;
	BattleInfo.Enemy[1].x = 6;
	BattleInfo.Enemy[1].y = 6;
	BattleInfo.Enemy[2].Enemy = 107;
	BattleInfo.Enemy[2].x = 9;
	BattleInfo.Enemy[2].y = 8;
	BattleInfo.Enemy[3].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_NORMAL;
	evField(0,1);

	npPos(35,29,40);
	npDir(35,WEST);
	npPos(36,30,39);
	npDir(36,WEST);
	npPos(37,0,0);
	npShow(37,0);
	npPos(38,32,41);
	npDir(38,WEST);

	EVBATTLE(BattleInfo);

	evFrameWait(250);
	for(a = 0;a < 10;a ++){
		npMove(35,-1,0);
		npMove(36,-1,0);
		npMove(38,-1,0);
		if(a == 5)
			npDir(28,EAST);
		if(a == 6)
			npDir(26,EAST);
		if(a == 7)
			npDir(27,EAST);
		if(a == 6)
			npDir(25,EAST);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---魔法、僧侶、特殊
	//---バトル
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.Music = CRMUSIC_BATTLE;
	BattleInfo.Enemy[0].Enemy = 105;
	BattleInfo.Enemy[0].x = 3;
	BattleInfo.Enemy[0].y = 10;
	BattleInfo.Enemy[1].Enemy = 106;
	BattleInfo.Enemy[1].x = 6;
	BattleInfo.Enemy[1].y = 6;
	BattleInfo.Enemy[2].Enemy = 107;
	BattleInfo.Enemy[2].x = 10;
	BattleInfo.Enemy[2].y = 9;
	BattleInfo.Enemy[3].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_NORMAL;

	npPos(35,0,0);
	npShow(35,0);
	npPos(36,30,32);
	npDir(36,SOUTH);
	npPos(35,29,34);
	npDir(35,EAST);
	npPos(37,0,0);
	npShow(37,0);
	npPos(38,0,0);
	npShow(38,0);

	EVBATTLE(BattleInfo);

	npPos(29,30,35);
	npDir(29,EAST);
	//---町長
	npPos(32,32,35);
	npDir(32,WEST);
	//---edo
	evReadObject(7,"Edo.acf");

	//---町長とエド
	for(a = 0;a < 18;a ++){
		if(a < 6)
			mcMove(0,-1);
		else
			mcMove(1,0);
		evFrame();
	}
	evFrameWait(250);
	npMove(32,-1,0);
	evFrame();
	crsoundPlay(CRSOUND_ATACK2);
	evFrameWait(250);
	crsoundPlay(CRSOUND_ATACK2);
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);

	crsoundPlay(CRSOUND_FIRE2);
	evFill(ep->MakeRGB(255,0,0));
	ew->Flip();
	evWait(100,1);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	npMove(32,1,0,0);
	evFrame();
	//---町長倒れる
	evFrameWait(250);
	evReadObject(4,"TwPpl2m_down.acf");
	npDir(32,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---やめて
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);

	npPos(25,16,35);
	npDir(25,WEST);
	npPos(26,18,34);
	npDir(26,WEST);
	npPos(27,16,33);
	npDir(27,WEST);
	npPos(28,17,36);
	npDir(28,WEST);

	for(a = 0;a < 9;a ++){
		for(b = 25;b <= 28;b ++){
			npMove(b,1,0);
		}
		if(a == 2)
			npDir(29,SOUTH);
		if(a == 4)
			npDir(29,WEST);
		if(a == 3)
			npDir(35,SOUTH);
		if(a == 4)
			npDir(35,WEST);
		if(a == 6)
			npDir(36,WEST);
		evFrame();
	}
	evFrameWait(250);

	mes.ReadDraw(5);
	//---言うてくれるの
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	//---わしにできること
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);

	//---僧侶、エド、特殊
	//---バトル
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.Music = CRMUSIC_ETERNALBATTLE;
	BattleInfo.Enemy[0].Enemy = 105;
	BattleInfo.Enemy[0].x = 4;
	BattleInfo.Enemy[0].y = 6;
	BattleInfo.Enemy[1].Enemy = 108;
	BattleInfo.Enemy[1].x = 6;
	BattleInfo.Enemy[1].y = 9;
	BattleInfo.Enemy[2].Enemy = 107;
	BattleInfo.Enemy[2].x = 8;
	BattleInfo.Enemy[2].y = 6;
	BattleInfo.Enemy[3].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;

	EVBATTLE(BattleInfo);
	//---じいさんのまけ
	evFrameWait(250);
	npMove(29,1,0,0);
	evFrameWait(350);

	mes.ReadDraw(3);
	evFrameWait(500);
	mes.ReadDraw();

	//---去る
	evFrameWait(250);
	npDir(29,NORTH);
	evFrameWait(250);
	//---じいさん去る
	for(a = 0;a < 15;a ++){
		npMove(29,0,-1);
		if(a == 2)
			npDir(36,NORTH);
		if(a == 3)
			npDir(35,NORTH);

		if(a > 4)
			npMove(36,0,-1);
		if(a > 5)
			npMove(35,0,-1);

		if(a == 6)
			npDir(25,NORTH);
		if(a == 7)
			npDir(26,NORTH);
		evFrame();
	}
	//---ナック近寄る
	for(a = 0;a < 8;a ++){
		if(a < 7)
			npMove(27,1,0);
		else
			npMove(27,0,1);
		if(a == 5)
			npDir(25,EAST);
		if(a == 6)
			npDir(26,EAST);
		evFrame();
	}
	//---手当するから
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(1000);
	mes.ReadDraw(2);

	//---何よ、その言い方！
	for(a = 0;a < 3;a ++){
		npMove(25,1,0);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(4);

	//---黙れ！
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);

	//---宿屋
	evReloadMap(1);
	npPos(25,45,14);
	npDir(25,WEST);
	npPos(26,35,14);
	npDir(26,WEST);
	npPos(27,34,14);
	npDir(27,EAST);
	npPos(28,25,12);
	npDir(28,EAST);
	evScene(0,34,15);
	evFrameWait(1000);

	//---ルナン来る
	for(a = 0;a < 8;a ++){
		npMove(25,-1,0);
		if(a == 4)
			npDir(26,SOUTH);
		if(a == 5)
			npDir(26,EAST);
		if(a == 7)
			npDir(27,SOUTH);
		evFrame();
	}
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(27,0,1);
		else
			npDir(27,EAST);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---ライゼル来る
	for(a = 0;a < 9;a ++){
		npMove(28,1,0);
		if(a == 4)
			npDir(27,NORTH);
		if(a == 5)
			npDir(26,NORTH);
		evFrame();
	}
	npDir(28,SOUTH);
	npMove(27,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	//---ルナン歩く
	for(a = 0;a < 6;a ++){
		if(a < 1)
			npMove(25,0,1);
		else if(a < 5)
			npMove(25,-1,0);
		else
			npMove(25,0,-1);
		evFrame();
	}
	//---みんな・・・
	evFrameWait(250);
	mes.ReadDraw(2);
	//---今回のことは・・・
	evFrameWait(500);
	mes.ReadDraw(5);

	//---わしを一人に
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---一緒じゃないといや！
	npMove(27,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(3);

	//---ライブ敢行
	evFrameWait(1000);
	crmusicPlay(CRMUSIC_LIZEL);
	npDir(28,WEST);
	evFrameWait(150);
	npDir(28,NORTH);
	evFrameWait(150);
	npDir(28,EAST);
	evFrameWait(150);
	npDir(28,SOUTH);
	evFrameWait(150);
	mes.ReadDraw(4);
	evFrameWait(500);

	//---ところ変わって
	evFrameWait(250);

	//---ライゼル外す
	{
		CrCharacter *pChara = crcharaGetPartyMember(3);

		if(pChara->GetWeapon(0)){
			critemAddItem(pChara->GetWeapon(0),1);
			pChara->SetWeapon(0,0);
		}
		if(pChara->GetWeapon(1)){
			critemAddItem(pChara->GetWeapon(1),1);
			pChara->SetWeapon(1,0);
		}

		if(pChara->GetProtector(0)){
			critemAddItem(pChara->GetProtector(0),1);
			pChara->SetProtector(0,0);
		}
		if(pChara->GetProtector(1)){
			critemAddItem(pChara->GetProtector(1),1);
			pChara->SetProtector(1,0);
		}
		if(pChara->GetProtector(2)){
			critemAddItem(pChara->GetProtector(2),1);
			pChara->SetProtector(2,0);
		}

		if(pChara->GetAccessory(0)){
			critemAddItem(pChara->GetAccessory(0),1);
			pChara->SetAccessory(0,0);
		}
		if(pChara->GetAccessory(1)){
			critemAddItem(pChara->GetAccessory(1),1);
			pChara->SetAccessory(1,0);
		}
		crcharaLoadFace(-1);
	}
	prtRecoveryAll();
	pPartyInfo->PartyMember[3] = -1;

	npPos(25,26,14);
	npDir(25,NORTH);
	npPos(26,27,13);
	npDir(26,NORTH);
	npPos(27,26,12);
	npDir(27,NORTH);

	npPos(30,25,2);
	npDir(30,EAST);
	npPos(32,26,-6);
	npDir(32,SOUTH);
	npPos(6,22,3);
	npDir(6,EAST);
	evScene(0,27,5);
	evReloadMapMusic();

	evFrameWait(1000);
	//---ルナン達歩いてくる
	for(a = 0;a < 8;a ++){
		npMove(25,0,-1);
		npMove(26,0,-1);
		npMove(27,0,-1);
		evFrame();
	}
	evFrameWait(250);
	npDir(27,EAST);
	evFrameWait(250);
	npDir(27,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(5);

	//---男が来る
	evFrameWait(250);
	for(a = 0;a < 8;a ++){
		npMove(32,0,1);
		evFrame();
	}
	evFrameWait(250);
	npDir(32,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(27,WEST);
	evFrameWait(250);
	npDir(27,NORTH);
	evFrameWait(250);

	mes.ReadDraw(2);
	//---男達行く
	evFrameWait(500);
	for(a = 0;a < 12;a ++){
		npMove(30,0,1);
		if(a < 1)
			npMove(32,-1,0);
		else
			npMove(32,0,1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(3);
	evFrameWait(250);
	npDir(27,EAST);
	evFrameWait(250);
	npDir(27,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);

	for(a = 25;a <= 32;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	mcDir(SOUTH);
	mcShow(1);
	evScene(0,26,4);

	npPos(28,37,9);
	npDir(28,EAST);

	mes.CloseMessage();

	evSet(118,1);

	return 1;
}
