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


//---ゼビアマイン、サヴィアーとの再会
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

	//---ルナン向く
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

	//---驚きルナン
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	//---久方ぶりの再会
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

	//---なんで
	evFrameWait(500);
	mes.ReadDraw(2);
	//---バビロスキーさんに
	evFrameWait(250);
	npDir(31,NORTH);
	evFrameWait(250);
	npDir(31,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---バビロスキー
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

	//---調べごとは
	evFrameWait(250);
	npDir(28,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(29,SOUTH);
	evFrameWait(150);
	npDir(30,SOUTH);
	evFrameWait(150);

	//---でもその前に近況を
	evFrameWait(250);
	npDir(31,SOUTH);
	evFrameWait(250);
	npDir(31,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	//---この変な人は
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(31,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	//---この人はね
	evFrameWait(250);
	npDir(29,WEST);
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---はぁ・・・
	mes.ReadDraw();
	evFrameWait(500);

	//---報告
	npDir(29,SOUTH);
	npDir(31,EAST);
	evReloadMapMusic();
	evScene(0,43,46);
	evFrameWait(1000);
	mes.ReadDraw(3);

	//---間違い
	evFrameWait(250);
	mes.ReadDraw();

	//---誰も神ではない
	evFrameWait(500);
	mes.ReadDraw(2);
	//---説明
	evFrameWait(500);
	mes.ReadDraw(5);

	//---言い伝えは
	evFrameWait(250);
	npDir(31,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	//---そうか・・・
	evFrameWait(250);
	npDir(31,EAST);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---両手が・・・
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(250);

	mes.CloseMessage();

	if(crbaseSelectYesNo("言い伝えを聞きますか？",64,64) == 0){
		mes.FileMessage("ZeviaMine.msg",104);
	}

	evFrameWait(500);
	mes.OpenMessage("ZeviaMine.msg",105);
	mes.ReadDraw(2);

	//---戦いに負けたってこと？
	evFrameWait(500);
	mes.ReadDraw(3);
	//---わからんす
	evFrameWait(500);
	mes.ReadDraw(2);

	//---お気楽でいいわね
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
	//---ユミの説明
	evFrameWait(300);
	mes.ReadDraw(2);

	evFrameWait(300);
	mes.ReadDraw(5);

	//---伝説は
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);
	//---神聖なる裁きは？
	evFrameWait(250);
	mes.ReadDraw(2);

	//---大ニュース
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
	//---マスター、何だって？
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

	//---うそでしょ・・・
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

	//---おかしいな
	mes.ReadDraw(2);

	//---いきますか？
	evFrameWait(250);
	npDir(31,NORTH);
	evFrameWait(250);
	npDir(31,EAST);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---今から戻るのは
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
	//---手に入れる
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	//---今夜は土ばーっと
	crmusicPlay(CRMUSIC_SAKABA);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);

	//---翌朝
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

	//---アルシアへ！
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

	//---サヴィアー再び仲間になる
	{
		pPartyInfo->PartyMember[3] = 3;
		pPartyInfo->PartyMember[4] = 4;

		int level = crcharaGetPartyMember(0)->GetLevel();
		CrCharacter *pChara = crcharaGetPartyMember(3);

		if(level > pChara->GetLevel() && level < 30){
			//---ルナンの方が高かったらレベルセット
			crcharaSetLevelStatus(3,level + 1);
			pChara->SetLevelExperience();
		} else if(level > pChara->GetLevel() && level >= 30){
			//---レベル３０以上だったら
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

	//---アルシア湖岸洞窟
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

//---アルシア湖岸洞窟、湖どぼん
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

	//---サヴィアー湖へ
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
	//---ニアピン
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();
	//---泳げますよね
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
	//---あーもう！
	mes.ReadDraw();
	//---じろじろ
	evFrameWait(500);
	npDir(1,SOUTH);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw(3);

	//---全然知らなかった
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

//---アルシア湖岸洞窟、グラウンドシップゲット！！
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
	//---あれって！
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

	//---グラウンドシップ
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

	//---その通り
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

	//---なんで・・・
	evFrameWait(500);
	npMove(0,-1,0);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw(3);

	//---理由
	evFrameWait(500);
	mes.ReadDraw(3);

	//---ボロ・・・
	evFrameWait(500);
	mes.ReadDraw();

	//---ああああ！ひどい！
	evFrameWait(500);
	npMove(3,1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);

	//---見かけはボロでも
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	//---お乗り込み9,4 6:6

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
	//---操縦したい！
	mes.ReadDraw();
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---まにゅある？
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---ルナン挑戦！！
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
	//---クラッチ踏んだ
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	//---ギヤＲ
	evFrameWait(1000);
	em->Put(10,3,2,24);
	evFrameWait(1000);
	//---アクセル踏む
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

	//---エンスト
	evFrameWait(1000);
	crsoundStop(CRSOUND_GS_SOUND);
	crsoundPlay(CRSOUND_GS_ENSTO);

	//---止まったけど？
	evFrameWait(2000);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---交代！
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
	//---発進！！
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

	//---フィールド！！
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

	//---なんでわたしのときは？
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---甲板出る！
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

	//---ギアいくつ？
	mes.ReadDraw(2);
	evFrameWait(500);
	npMove(4,1,0);
	evFrameWait(250);
	npDir(4,NORTH);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---クレスフィールドへ

	crfieldSetMainCharacter(1);

	crfieldChangeMap(10,0,1,0);
	mcShow(1);
	crfieldSetMainCharacter(3);
	mcDir(EAST);
	ef->SetMoveEnything(1);
	evScene(0,x,y);

	//---フィールド！！
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

//---クレスフィールド、建国宣言前
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

	//---サヴィアーたずねる
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

	//---サヴィアー戻ってくる
	npDir(21,NORTH);
	evFrameWait(250);

	for(a = 0;a < 4;a ++){
		npMove(21,0,-1);
		if(a == 3)
			npDir(3,SOUTH);
		evFrame();
	}
	evFrameWait(250);

	//---会議
	mes.ReadDraw(2);

	//---どうするのよ
	evFrameWait(500);
	npDir(22,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	//---そういえばお前なんでいるんだ？
	evFrameWait(250);
	npDir(19,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(18,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	//---勝手に
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

//---クレスフィールド、建国宣言シンディと再会
CREVENTLONG4_API int creventCresfield_KenkokusengenCindy(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	npTurn(9);
	evFrameWait(150);

	mes.OpenMessage("Cresfield.msg",132);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---みんなでなかよく？
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

	//---ちょっと気まずい
	evFrameWait(2000);
	//---サヴィアーの話題ふり
	evFrameWait(250);
	npDir(6,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	//---さらに
	evFrameWait(3000);
	mes.ReadDraw();
	evFrameWait(2000);
	mes.ReadDraw();

	//---シンディ去る
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

	//---相変わらず
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

	//---宿屋２階にて
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
	//---どうやって防ぐの？
	evFrameWait(500);
	mes.ReadDraw(2);
	//---サヴィアーの助言
	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(250);

	//---オレも・・・
	evFrameWait(500);
	npDir(1,NORTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(250);
	mes.ReadDraw(2);
	//---ルナン・・・
	evFrameWait(500);
	mes.ReadDraw();

	//---建国宣言しても・・・
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

//---クレスフィールド、建国宣言前夜～建国宣言ナックと一緒
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

	//---ルナン歩いてくる
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

	//---ディザがいる
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
	//---ディザなんで・・・
	crmusicPlay(CRMUSIC_SEEK);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	//---ディザって何で・・・
	evFrameWait(500);
	mes.ReadDraw(2);
	//---そういうもんなの
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	//---ディザもやっぱり無理だとおもった？
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(250);
	mes.ReadDraw(2);
	//---そう・・・
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
	//---ディザに会えて
	mes.ReadDraw(2);

	//---そうじゃなくて
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

	//---手なんて
	evFrameWait(500);
	mes.ReadDraw();
	//---だけど・・・
	evFrameWait(500);
	npDir(18,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---みんなにはみんなの
	evFrameWait(500);
	npDir(18,WEST);
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw();
	//---そうよね
	evFrameWait(1000);
	mes.ReadDraw();
	//---でもよ
	evFrameWait(500);
	mes.ReadDraw(2);
	//---ちょっとお困り
	evFrameWait(500);
	npDir(19,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(19,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	//---まずはエターナルに
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---もしも・・・
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
	//---そうだなあ
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(19,EAST);
	evFrameWait(500);
	crmusicFadeOut();
	evFadeOut(2000);


	//---翌日宿屋２階にて
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
	//---わたしここにいる
	evFrameWait(500);
	mes.ReadDraw();
	//---どうせなら
	evFrameWait(500);
	npMove(4,1,0);
	evFrameWait(250);
	npDir(4,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	//---いい
	evFrameWait(500);
	mes.ReadDraw(2);
	//---頼んだ
	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	//---言ってきます
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
	//---ごめんね
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
	//---はずす
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
			//---ラーフィア
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

//---クレスフィールド、建国宣言クレイシヴ現る
CREVENTLONG4_API int creventCresfield_Kenkokusengen(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	evFrameWait(250);
	mes.OpenMessage("Cresfield.msg",135);
	mes.ReadDraw(3);
	//---でも
	evFrameWait(500);
	mes.ReadDraw(4);

	//---ディザが来る
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

	//---どうしたの
	mes.ReadDraw();
	evFrameWait(250);
	crmusicPlay(CRMUSIC_CRAYSIVE);
	mes.ReadDraw(3);
	evFrameWait(250);

	//---会場
	crfieldChangeScene(0,20,20);
	//---民衆
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
	//---３人来る
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
	//---アズグレイが・・・
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
	//---あなたなにを・・・
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---バトル！
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
	sprintf(pCharacterInfo[a].CharaInfo.Name,"ラーフィア");
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
	sprintf(pCharacterInfo[a].CharaInfo.Name,"フォールン");
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
	//---ファスラクリアを掲げる
	npMove(62,0,1);
	evFrame();
	evFrameWait(2000);

	//---ファスラクリアを見せる
	evReadObject(3,"Crasive2.acf");
	evFrameWait(1000);
	npDir(62,SOUTH);
	npPos(63,58,52);
	npDir(63,NORTH);
	npPos(64,58,51);
	npDir(64,EAST);
	evFrameWait(2000);

	//---空高く！
	npDir(62,NORTH);
	npPos(63,58,52);
	npDir(63,SOUTH);
	npPos(64,58,51);
	npDir(64,WEST);
	evFrameWait(1000);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw();

	//---民衆
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	//---民衆
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---ルナン
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

	//---再び舞台
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
	//---剣をしまう
	npShow(63,0);
	npShow(64,0);
	evFrameWait(500);

	evReadObject(3,"Crasive.acf");
	npDir(62,SOUTH);
	//---何も言うことはないな
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

	//---去る
	for(a = 0;a < 6;a ++){
		npMove(62,0,-1);
		evFrame();
		evFrameWait(500);
	}
	crmusicFadeOut();
	evFrameWait(1000);

	//---宿屋会議
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
	//---乗っ取り！
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
	//---これでエターナルが
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);

	//---シンディ来る
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

	//---ナックの敵対心
	npPos(5,4,9);
	npDir(5,SOUTH);
	npDir(0,SOUTH);
	evScene(3,3,11);
	evFrameWait(500);
	mes.ReadDraw(2);
	//---ディザの発言
	evFrameWait(500);
	npDir(1,SOUTH);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(250);

	//---父親さがしてるって
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw(2);
	//---サヴィアー
	evFrameWait(500);
	npDir(3,SOUTH);
	evFrameWait(500);
	mes.ReadDraw(2);
	//---行ってみようぜ
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(250);
	mes.ReadDraw();
	//---みんなありがとう
	evFrameWait(500);
	mes.ReadDraw();

	//---私も
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
	//---私も行きたい
	evFrameWait(500);
	mes.ReadDraw(2);

	//---ドーグリで
	evFrameWait(500);
	mes.ReadDraw(4);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---わかったわ
	evFrameWait(500);
	mes.ReadDraw(2);
	//---オレはどっちでも
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(2,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	//---サヴィアーうっかり本音
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

//---クレスフィールド、グラウンドシップ落書き事件
CREVENTLONG4_API int creventCresfield_GotoTulia(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	evMap(60,0,11,17);
	evFrameWait(250);

	mes.OpenMessage("Cresfield.msg",137);
	mes.ReadDraw(2);
	//---落書き！！
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
	//---ほんとだ
	mes.ReadDraw();

	evFrameWait(500);
	for(a = 0;a < 2;a ++){
		npMove(0,0,-1);
		evFrame();
	}
	evFrameWait(1000);
	mes.ReadDraw();
	//---心当たりが・・・
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

	//---ツーリアへ
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

	//---フィールド！！
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

	//---ツーリア到着！！
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

//---ツーリア、初潜入
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

	//---さっそく
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


	//---私は戻るわ
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
	//---この町は・・・
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---ディザ切れ気味
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

	//---仲裁
	evFrameWait(250);
	npDir(43,WEST);
	evFrameWait(250);
	npDir(43,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---ユミ去ろうとする
	npDir(48,EAST);
	evFrameWait(250);
	npDir(48,NORTH);
	evFrameWait(250);
	npMove(48,0,-1);
	evFrame();
	evFrameWait(100);
	mes.ReadDraw();
	//---振り返る
	evFrameWait(500);
	npDir(48,WEST);
	evFrameWait(250);
	npDir(48,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---サヴィアー尋問
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

	//---言いました
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw(2);
	//---だから言ってるじゃない
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	mes.ReadDraw(3);
	//---言いたいことはそれだけ？
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

	//---ユミ去る
	evFrameWait(250);
	npDir(48,EAST);
	evFrameWait(250);
	npDir(48,NORTH);
	evFrameWait(250);
	for(a = 0;a < 7;a ++){
		npMove(48,0,-1);
		evFrame();
	}
	//---せいせいしたぜ
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(44,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	//---うん
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

	//---そうね・・・
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

	//---シンディ仲間になる
	{
		pPartyInfo->PartyMember[3] = 3;
		pPartyInfo->PartyMember[4] = 6;

		int level = crcharaGetPartyMember(0)->GetLevel();
		CrCharacter *pChara = crcharaGetPartyMember(4);

		if(level > pChara->GetLevel() && level < 34){
			//---ルナンの方が高かったらレベルセット
			crcharaSetLevelStatus(4,level + 1);
			pChara->SetLevelExperience();
		} else if(level > pChara->GetLevel() && level >= 34){
			//---レベル３４以上だったら
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

//---ツーリア、ガゼールとの再会
CREVENTLONG4_API int creventTuria_MeetGazell(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	evSet(143,1);

	evFrameWait(250);
	mes.OpenMessage("Turia.msg",101);
	mes.ReadDraw();

	//---ガゼール振り返る
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
	//---ルナンも
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
	//---みんなが
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	//---町のみんなは？
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(1000);
	//---気持ちは分かるが
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---そちらの方は？
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

	//---なあおやじさん
	evFrameWait(250);
	npMove(44,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);
	//---なしてそげなことを
	evFrameWait(250);
	npDir(43,WEST);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---反乱？
	evFrameWait(500);
	mes.ReadDraw(2);
	//---父さんは？
	evFrameWait(250);
	npDir(43,NORTH);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();
	//---ヤジ
	evFrameWait(250);
	npDir(14,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(14,SOUTH);
	evFrameWait(250);

	mes.ReadDraw();

	//---ガゼール動く
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

	//---父さん！！
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
	//---セノウで・・・
	evFrameWait(700);
	mes.ReadDraw();
	//---なにが？
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---何があろうと
	evFrameWait(1000);
	npMove(48,-1,0);
	evFrame();
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();
	//---望んだこと
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(350);
	npDir(48,SOUTH);
	evFrameWait(350);
	npDir(48,EAST);
	evFrameWait(350);
	//---ガゼール行く
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
	//---酒場へ
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.CloseMessage();

	npPos(48,0,0);
	npShow(48,0);

	//---酒場//11,22
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
	//---どうだった？
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(44,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(5);

	//---ルナンどうしたの？
	evFrameWait(250);
	npDir(45,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	//---ちょっとあってな
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

	//---話の続き
	evFrameWait(250);
	mes.ReadDraw(3);

	//---行くの？
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

	//---ええ
	evFrameWait(700);
	mes.ReadDraw(3);
	//---そうなんだけどね・・・
	evFrameWait(500);
	mes.ReadDraw(2);
	//---なんでもない
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

	//---入り口へ
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

	//---助けられると
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);
	//---はっと気づく
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---肝心なのは
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---シンディさんは
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

//---ツーリア、防衛システム
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

	//---バトル
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

	//---倒した！
	evFrameWait(250);
	mes.OpenMessage("TuriaChika.msg",101);
	mes.ReadDraw(2);
	evFrameWait(250);

	//---壁がせり上がる
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

	//---な、なに！？
	npDir(4,EAST);
	evFrameWait(100);
	npDir(1,WEST);
	evFrameWait(100);
	mes.ReadDraw();

	//---わな！？
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

	//---どうにかならない
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
	//---ごめんなさい
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---でかしたな
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

	//---カメラ戻ってシンディ黙る
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
	//---ディザお怒り
	for(a = 0;a < 2;a ++){
		npMove(2,0,1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();

	//---シンディは
	evFrameWait(500);
	mes.ReadDraw(2);
	//---１つで
	evFrameWait(500);
	mes.ReadDraw();

	//---これで父さんに
	evFrameWait(1000);
	npMove(5,0,1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);

	//---クズ
	evFrameWait(250);
	npMove(1,0,1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(3);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---クレイシヴ様の
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(7,WEST);
	evFrameWait(500);
	npDir(7,SOUTH);
	evFrameWait(500);
	//---行くぞ
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

	//---催眠ガス
	crsoundPlay(CRSOUND_WIND1);
	evFadeOut(200,RGB_MAKE(255,255,255));
	evFieldNoFlip(0,1);
	evFadeIn(200,RGB_MAKE(255,255,255));

	evFrameWait(750);
	npDir(2,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---気を失う

	mes.CloseMessage();

	//---シンディはずれる
	{
		CrCharacter *pChara = crcharaGetPartyMember(4);
		if(pChara != NULL){
			//---初期装備でなければ外す
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

	//---暗闇の中
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

	//---目が覚める
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

	//---ルナンが目を覚ます
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(0,EAST);
	evFrameWait(1000);
//	mes.ReadDraw();

	//---目覚めたか
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

	//---持ち物も
	evFrameWait(500);
	npDir(2,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(2);

	//---事情があればいいのか？
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
//---ツーリア建物、フォールン現る
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

	//---目覚めは？
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw(2);

	//---クレスティーユよ
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw(2);

	//---そしてお前らも
	evFrameWait(500);
	mes.ReadDraw(2);

	//---とりいだしたるは
	evFrameWait(500);
	mes.ReadDraw();
	npPos(5,6,6);
	npDir(5,NORTH);

	//---まさか・・・
	evFrameWait(1000);
	mes.ReadDraw(3);
	//---話し続ける
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw(3);

	//---生命兵器は
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---精神体
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	//---クレスフィールド高地

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
	//---ガイコツ動く
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

	//---ふたたび
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

	//---うそでしょ
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(250);
	npMove(1,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(4);

	//---いいわ
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---結果なんて・・・
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---ルナン歩く
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
	//---ルナン！！
	mes.ReadDraw(3);
	evFrameWait(500);
	mes.ReadDraw();

	//---自覚してるなら
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);
	npPos(5,0,0);
	npShow(5,0);
	evFrameWait(250);
	npDir(4,EAST);
	evFrameWait(250);
	//---フォールン去る
	crmusicFadeOut();
	for(a = 0;a < 14;a ++){
		npMove(4,1,0);
		evFrame();
	}
	crmusicPlay(CRMUSIC_SILENT);

	//---あのときのが弱かったんだよ
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

	//---今のわたしなら
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1500);
	mes.ReadDraw();

	//---無線機
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

	//---それで先生が
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

	//---ルナン・・・
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

	//---わたし
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

	//---だけどなあ
	evFrameWait(500);
	npDir(1,WEST);
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(250);

	//---鍵の前へ
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
	//---ナック移動
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

	//---眼鏡を外して
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	//---あく
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

//---ツーリア建物、脱出！
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

	//---おとなしく
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

	//---絶望だ
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

	//---そんな運命！！
	//---壊してやる
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
	//---バトル
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
	//---フォールンは？
	mes.ReadDraw(2);

	//---準備をして
	evFrameWait(250);
	npMove(6,1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---一回だけメニューを開ける
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	crmainMainMenu(1);
	evFrameWait(500);

	//---場所移動
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
	//---バトル
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

	//---行く
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

	//---１Ｆ
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

	//---いたぞ！！
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

	//---カメラ移動
	for(a = 0;a < 12;a ++){
		mcMove(0,1);
		evFrame();
	}
	npPos(13,35,27);
	npPos(14,36,27);

	//---！
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

	//---挟み撃ち！？
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

	//---挟み撃ちバトル！
	//---バトル
	memset(&BattleInfo,0,sizeof(BattleInfo));

	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.Music = 0;
	BattleInfo.Enemy[0].Enemy = 122;//---上
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
	//---挟み撃ち！
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

	//---２Ｆ
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


/*	//---きりなし！
	evFrameWait(250);
	mes.OpenMessage("TuriaEternal.msg",106);
	mes.ReadDraw();
	mes.CloseMessage();

	evFrameWait(250);
	//---魔法、僧侶、特殊
	//---バトル
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

	//---こっちは？
	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(250);
	mes.OpenMessage("TuriaEternal.msg",107);
	mes.ReadDraw();
	evFrameWait(250);

	//---壁
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

	//---そっちへ無理ですね
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

	//---気をつけて
	evFrameWait(250);
	npMove(3,0,1);
	evFrame();
	evFrameWait(100);
	npDir(3,WEST);
	evFrameWait(250);
	mes.ReadDraw(4);

	//---いくわよ！
	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	//---は、はい
	evFrameWait(250);
	npDir(4,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(4,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---二人行く
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

	//---ルナンとナックもいく
	for(a = 0;a < 8;a ++){
		npMove(1,-1,0);
		if(a)
			npMove(2,-1,0);
		evFrame();
	}

	evFrameWait(250);

	//---ルナンとディザ
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

	//---いたぞ！
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


	//---逃げる
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

	//---外へ
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
	//---あ！
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

	//---エターナルが来る
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
	//---ちょこまかと
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();
	//---絶対に
	evFrameWait(1000);
	mes.ReadDraw();
	//---何言って
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

	//---ルナンを落とす
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

//---ツーリア建物、ユミと爆風
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

	//---顔が出る
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
	//---せき込む
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

	//---上がろうとする
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

	//---上がる
	npPos(45,0,0);
	npPos(43,40,42);
	npDir(43,EAST);
	evScene(0,40,45);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(43,NORTH);

	//---爆音！
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

	//---ユミがいる
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

	//---みんなは！？
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

	//---分散処理ってやつ
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

	//---グラウンドシップ
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
	//---平気よ
	evFrameWait(500);
	mes.ReadDraw(2);

	//---ちゃんと
	evFrameWait(500);
	mes.ReadDraw(3);

	//---落ち着いて
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

	//---飲めば？
	npMove(4,0,1);
	evFrame();
	evFrameWait(250);
	npDir(4,EAST);
	evFrameWait(250);
	em->Put(21,6,2,13);
	evFrameWait(250);
	mes.ReadDraw();

	//---常套手段
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();

	//---もらう
	evFrameWait(700);
	em->Put(21,6,2,1024);
	evFrameWait(2000);
	em->Put(21,6,2,13);
	evFrameWait(500);
	//---トマトが一番
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(2);

	//---明日の昼までに
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
	//---何を言って・・・
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

	//---ゆっくり休みなさい
	crfieldChangeScene(2,15,15);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(2000);

	//---目が覚める 5,7
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

	//---あれ
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

	//---ナック
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
	//---今何時でい！？
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---起きて
	evReadObject(0,"Lunarn.acf");
	npPos(0,12,7);
	npDir(0,SOUTH);
	npPos(2,12,8);
	npDir(2,NORTH);
	evScene(0,12,9);
	crmusicPlay(CRMUSIC_ENDLESSP);
	evFrameWait(500);
	mes.ReadDraw();

	//---ナックはいつもどってきたの？
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
	//---ジーダイへ！
	evFrameWait(1500);
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---みんなは
	evFrameWait(250);
	npMove(2,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(2);

	//---ナック・・・
	evFrameWait(1000);
	mes.ReadDraw();
	//---冷たくても
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);

	//---ＧＳで
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(2,EAST);
	evFrameWait(250);
	npDir(2,SOUTH);
	evFrameWait(250);
	//---つっこみ
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

	//---パーティー外す
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

//---ライゼル参上！！
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

	//---作戦会議
	evFrameWait(250);
	npPos(0,25,25);
	npDir(0,EAST);
	npPos(1,26,25);
	npDir(1,WEST);
	evScene(2,25,27);

	//---どうしようか？
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	evScene(3,15,15);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---わたし達だけじゃ・・・
	evScene(2,25,27);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	evScene(3,15,15);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---でも
	evScene(2,25,27);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	evScene(3,15,15);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---やったろうじゃない！！
	evScene(2,25,27);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);

	//---カメラ移動
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
	//---どうしても
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);

	//---バトル
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

	//---く・・・
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(250);

	//---エターナルが来る
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

	//---その罪の重さを
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---謎の声
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

	//---おろかなり
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

	//---笑いの道
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---寒波現る
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

	//---お前も刃向かうのか？
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
	//---本来なら
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw(3);

	//---いざいかん！！
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);

	//---ライゼル再び仲間になる
	{
		pPartyInfo->PartyMember[2] = 5;
		pPartyInfo->PartyMember[4] = -1;

		int level = crcharaGetPartyMember(0)->GetLevel();
		CrCharacter *pChara = crcharaGetPartyMember(2);

		if(level < 25 && pChara->GetLevel() < 25){
			crcharaSetLevelStatus(2,25);
			pChara->SetLevelExperience();
		} else if(level > pChara->GetLevel() && level < 35){
			//---ルナンの方が高かったらレベルセット
			crcharaSetLevelStatus(2,level + 1);
			pChara->SetLevelExperience();
		} else if(level > pChara->GetLevel() && level >= 35){
			//---レベル３５以上だったら
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

	//---バトル
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

	//---逃げる
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
	//---やったあ！
	evFrameWait(250);
	npMove(1,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---おっちゃんはどうして？
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(2,WEST);
	evFrameWait(250);
	npDir(2,SOUTH);
	evFrameWait(250);

	//---ご理由
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);

	//---ところで・・・
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

//---記憶の遺跡、決戦エターナル！！
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

	//---エド
	evFrameWait(1000);
	npMove(6,0,1);
	evFrame();
	evFrameWait(50);
	npDir(6,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	//---なんじゃ？
	evFrameWait(500);
	npDir(7,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	//---そうじゃのう
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---見つかる！
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

	//---振り向く
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

	//---戦い！
	evFrameWait(250);

	//-------------------
	//---バトル
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

	//---誰かいるの！？
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---やむえん
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);

	//---行くわよ！
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

	//---おそいかかる
	npMove(8,0,1);
	npMove(13,0,1);
	evFrame();
	evFrameWait(250);


	//---戦い！
	//-------------------
	//---バトル
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

	//---まだこんなにいっぱい
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

	//---そんなこと言ってると
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

	//---またせたな
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

	//---何人集まろうと
	for(a = 0;a < 10;a ++){
		mcMove(-1,0);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);

	//---オレはじじいを
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

	//---ライフカプセルＳ
	critemAddItem(222,10);
	//---マジック
	critemAddItem(223,3);
	//---ラケシス
	critemAddItem(227,4);
	//---エルダー
	critemAddItem(225,1);
	//---キュアー
	critemAddItem(226,5);
	//---メニュー・ディザ
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
					//---ディザの武器
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
					//---サヴィアーの武器
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
			//---ディザの方が高かったらレベルセット
			crcharaSetLevelStatus(2,level);
			pChara->SetLevelExperience();
		} else if(level > pChara->GetLevel() && level >= 40){
			//---レベル４０以上だったら
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


	//---メニュー・ルナン
	{
		pPartyInfo->PartyMember[0] = 0;
		pPartyInfo->PartyMember[1] = 2;
		pPartyInfo->PartyMember[2] = 5;
		pPartyInfo->PartyMember[3] = -1;
		crcharaLoadFace(-1);
	}
	crmainMainMenu(1);

	//---いくぜ！
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

	//---バトル
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
		//---負け！
		fail ++;
		dizza ++;
	}

	//---パーティー組み替え
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
		//---負け！
		fail ++;
		lunarn ++;
		if(fail >= 2){
			//---２パーティーとも負けたら
			return MAINLOOP_BATTLEFAIL;
		}
	}

	if(dizza){
		//---ディザパーティーが負けてたら
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
			//---負け！
			return MAINLOOP_BATTLEFAIL;
		}
	} else if(lunarn){
		//---ルナンパーティーが負けてたら
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
			//---負け！
			return MAINLOOP_BATTLEFAIL;
		}
	}

	//---------------------------------------
	//---戦いの後
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

	//---遺跡の中
	evScene(0,8,19);
	evFrameWait(500);
	mes.ReadDraw();


	//---どうやって？
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

	//---見つけにくい
	evFrameWait(500);
	npDir(5,EAST);
	evFrameWait(250);
	npDir(4,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	//---船で？
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---６人で？
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

	//---そうね
	evFrameWait(500);
	mes.ReadDraw();

	//---ユミとライゼル
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

	//---ユミ？
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

	//---やめ
	evFrameWait(2000);
	npDir(4,WEST);
	evFrameWait(500);
	npDir(4,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---ケチ
	evFrameWait(250);
	mes.ReadDraw();

	//---ルナンよ！
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

	//---パーティーセット
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
//---記憶の遺跡、対称のプレート
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

	//---何か書いてある
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

	//---あっちにも同じプレートが
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

	//---お試し
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
	//---どうぞ
	evFrameWait(500);
	for(a = 0;a < 10;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();

	//---乗る
	evFrameWait(500);
	for(a = 0;a < 12;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(500);
	npMove(2,0,1);
	evFrame();
	evFrameWait(250);

	//---開く
	em->Put(13,4,2,1024);
	em->Put(13,3,2,1024);
	crsoundPlay(CRSOUND_ATACK4);
	evFrameWait(250);

	//---開いた！
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

	//---ディザがどく
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

	//---作戦会議
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
	//---ディザさんが
	evFrameWait(500);
	mes.ReadDraw(2);

	//---一番
	evFrameWait(500);
	mes.ReadDraw(2);

	//---ディザいい？
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

	//---パーティー減らす
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

//---記憶の遺跡、ルナン一人で・・・
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

	//---ディザがいこうとする
	evFrameWait(500);
	npMove(1,0,1);
	evFrame();

	//---フラッシュ
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

	//---どうしたの？
	npDir(0,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---ルナン入ってみる
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
	//---もう一回フラッシュ
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

	//---クレイシヴの声
	mes.ReadDraw();
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);
	crmusicPlay(CRMUSIC_CRAYSIVE);
	evFrameWait(250);

	mes.ReadDraw(2);

	//---再び
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

	//---私行く
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(500);
	mes.ReadDraw();
	//---気をつけろよ
	evFrameWait(250);
	npDir(1,EAST);
	npMove(1,1,0);
	evFrame();
	evFrameWait(150);
	npDir(1,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---ルナン
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
	//---そうね
	mes.ReadDraw();
	//---次に会うときは
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	//---行って来る
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(1000);
	//---ルナン歩く
	for(a = 0;a < 3;a ++){
		npMove(0,0,1);
		evFrame();
	}
	evFrameWait(250);

	//---パーティー
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
				//---クレスティーユ
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
				//---クレスティーユ
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
				//---クレスティーユ
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

//---記憶の遺跡、メモリーオーブ
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

	//---オーブは私の後ろだ
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
	//---ふーあーゆー？
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---なんのために
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---オーブを手にすれば
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(1000);

	//---ルナン、メモリーオーブの方へ
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
	//---これが・・・
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---迷わない
	evFrameWait(1500);
	mes.ReadDraw();
	evFrameWait(250);
	npMove(0,0,-1);
	evFrame();
	//---教えて
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	mes.CloseMessage();

//-----------------------------------------
	//---ルナンの記憶へ
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

	//---目が覚めたか
	npDir(1,EAST);
	evFrameWait(500);
	mes.OpenMessage("Fillgalt.msg",100);
	mes.ReadDraw();
	evFrameWait(500);

	//---クレスティーユ歩く
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
	//---試験
	mes.ReadDraw();
	evFrameWait(500);

	//---この日は
	evScene(4,15,15);
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);

	//---パーティーセット
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
	//---バトル
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

	//---なんで戦ってたんだろう
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	evScene(5,7,8);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---そうだ、陛下より
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

	//---ルナン
	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(1000);

	//---クレイシヴと
	crfieldChangeScene(0,7,10);
	npPos(0,6,9);
	npDir(0,WEST);
	npDir(1,EAST);
	evScene(0,7,10);

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---浮かない顔
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);


	//---ルナン
	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---初参戦
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

	//---怒るクレイシヴ
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


	//---ルナン
	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---失敗作
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
	//---それにひきかえ
	mes.ReadDraw(2);
	evFrameWait(500);

	//---ルナン
	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---ちがう！
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

	//---行くぞ
	evFrameWait(250);
	npDir(2,EAST);
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

	//---二人行く
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

//---ルナン
	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(1000);


	//----------------------------------------------------
	//---バトル
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


	//---よく働いた
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
	//---二人歩く
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

/*	//---男去る
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

//---ルナン
	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---廊下
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
	//---ひそひそ話し
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);

	for(a = 0;a <= 3;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}

//---ルナン
	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---クレイシヴと
	crfieldChangeScene(0,7,10);
	npPos(0,6,9);
	npDir(0,WEST);
	npPos(1,4,9);
	npDir(1,EAST);
	evScene(0,7,10);

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);

//---ルナン
	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	evScene(0,7,10);
	evFrameWait(500);
	mes.ReadDraw();
	//---せめて
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	//---私に
	evFrameWait(500);
	npDir(1,NORTH);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(250);
	mes.ReadDraw();

	//---ああ、ここにいられるだけ
	evFrameWait(500);
	npDir(1,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

//---ルナン
	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw(3);
	evFrameWait(1000);

	//---クレイシヴと
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

//---ルナン
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

//---記憶の中、そして封印へ
CREVENTLONG4_API int creventKiokunoNaka_Fuin(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

//---ルナン
	evScene(4,15,15);
	evFrameWait(1000);
	mes.OpenMessage("Fillgalt.msg",102);
	mes.ReadDraw();
	evFrameWait(1000);


	//---これからのは・・・
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

	//---はい
	evFrameWait(1000);
	mes.ReadDraw();
	//---つれていくのか？
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
	//---望んでない！
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(250);

//---ルナン
	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---荒野
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
	//---バトル
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
	//---バトル
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
	
	//---クレスティーユバトル終了
	crbatSetShowStatus(1);

	//---大きな穴
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
	//---いたぞ！
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	evFadeOut(2000);

//---ルナン
	crfieldChangeMap(71,4,1,0);
	evFieldNoFlip(0,1);
//	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---なんだと！？
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

	//---命令だ
	evFrameWait(500);
	mes.ReadDraw();

	//---どういうことなんだ
	evFrameWait(250);
	npMove(1,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(2);

	//---わからない
	evFrameWait(500);
	mes.ReadDraw(3);

	//---クレイシヴ動く
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---次の・・・
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

//---ルナン
	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---現実
	crfieldChangeMap(70,10,1,0);
	npPos(0,13,3);
	npDir(0,NORTH);
	npDir(1,NORTH);
	crfieldChangeScene(10,13,6);
	evFieldNoFlip(0,1);
	evFadeIn(2000,RGB_MAKE(255,255,255));
//	evScene(10,13,6);

	evFrameWait(1000);

	//---思い出したか？
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

	//---再び
	evFadeOut(2000,RGB_MAKE(255,255,255));

	crfieldChangeMap(71,0,1,0);
	evFieldNoFlip(0,1);

	//---なんだと！？
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
	//---わたし
	evFrameWait(500);
	npMove(0,0,-1);
	evFrame();
	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	//---心配ない
	npDir(1,WEST);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	mes.ReadDraw(3);

	//---私はこれでいい
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

//---ルナン
	evScene(4,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---幻惑の森
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

	//---クレイシヴ歩く
	npMove(3,0,-1);
	evFrame();
	npDir(0,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---心配するな
	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(100);
	npMove(3,1,0);
	evFrame();
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---それでいいの？
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

//---ルナン
	evScene(6,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---現実
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
	//---それ以外の
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(3);

	//---老いた
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---保存装置
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

	//---目覚め
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
	//---クレイシヴ！
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(250);

	//---ほこり？
	evFrameWait(100);
	npDir(0,NORTH);
	evFrameWait(100);
	npDir(0,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

//---ルナン
	evScene(6,15,15);	
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---記憶
	crfieldChangeScene(4,9,4);
	npPos(0,9,2);
	npDir(0,SOUTH);
	em->Put(9,6,2,17);
	evReadObject(1,"LunarnF.acf");

	evFieldNoFlip(0,1);
	evFadeIn();

	//---ルナン歩く
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
	//---誰もいない
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

//---記憶の中、ガゼールとの出会い
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

//---ルナン
	evFrameWait(500);
	evScene(4,15,15);
	evFrameWait(500);
	crmusicPlay(CRMUSIC_TITLE);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	evScene(3,15,49);

	//---迷子か？
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

	//---何を
	evFrameWait(500);
	mes.ReadDraw(3);

	//---わたしが
	evFrameWait(500);
	npMove(0,0,1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(3);

	evFrameWait(100);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

	//---クレスフィールドへ
	crfieldChangeMap(32,6,1,0);
//---ルナン
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
	//---苦い
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---兵士が
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw(3);
	//---フィルガルト？
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw();

	//---千年・・・
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

//---ルナン
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

	//---名前は？
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(250);

//---ルナン
	evScene(6,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	evScene(5,4,9);
	//---いいなだな
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);


//---ルナン
	evScene(6,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	evScene(5,4,9);
	//---力があったから・・・
	evFrameWait(1000);
	mes.ReadDraw(3);

	//---これから
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

//---ルナン
	evScene(6,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---自由だ
	evScene(5,4,9);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

//---ルナン
	evScene(6,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	evScene(5,4,9);
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(1000);
	//---わたしを
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);

	//---ルナン移動
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

//---ルナン
	evScene(6,15,15);
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(1000);

	evScene(5,4,9);
	//---参ったな
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(1000);
	mes.ReadDraw(3);
	evFrameWait(500);

	//---でもこのままでは
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

	//---今までの記憶を・・・
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

//---ルナン
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

	//---寝る
	npPos(0,13,9);
	npDir(0,WEST);
	npPos(1,12,9);
	npDir(1,EAST);
	evScene(5,12,11);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);
	//---名前
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---ルナン
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

//---ルナン
	evScene(6,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---クレスフィールド
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

	//---気づいたか！？
	mes.ReadDraw();
	evFrameWait(1000);
	crmusicFadeOut();
	evFadeOut(2000,RGB_MAKE(255,255,255));

	//---現実へ
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
	//---クレイシヴなの？
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

	//---クレスティーユよ
	evFrameWait(1000);
	npMove(1,0,-1);
	evFrame();
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	//---眠りし
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1500);

	//---精神体の声
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
	//---はぁ？
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
	//---振り返る
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

	//---たくさんの精神体
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

	//---メンバー組み替え
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
	//---ルナン！
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(250);
	for(a = 0;a < 1;a ++){
		npMove(0,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(5);

	//---精神体が
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

//---記憶の遺跡、脱出！！
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

	//---ライゼル達
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
	//---ＧＳまで早く！
	evFrameWait(250);
	npMove(0,0,1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);

	//---すぐそこまで
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

	//---精神体
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

	//---ＧＳ
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

	//---精神体の声
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

	//---しつこいわね
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
	//---なんとか
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

	//---みんな・・・
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

	//---第二部終了フラッグ
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
