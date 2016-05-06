/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrEventLong1.cpp ...Event functions

-----------------------------------------------------------*/


#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CREVENTLONG1

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#include "CrBase.h"
#include "CrBattle.h"
#include "CrEvent.h"
#include "CrEvCom.h"

//---game info
#define CR_GAMEINFO_EXTERNPOINTER
#include "CrGameInfo.h"

CREVENTLONG1_API int creventAneat_LunanChocho(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	//---町長＆ルナン
	mcShow(0);
	npPos(1,12,12);
	npDir(1,WEST);
	npPos(2,13,10);
	npDir(2,SOUTH);

	evScene(1,12,14);

	mes.OpenMessage("Aneat.msg",100);

	evFrameWait(1000);
	npMove(1,-1,0);
	evFrame();
	npDir(0,NORTH);
	evFrameWait(300);
	npDir(0,EAST);
	evFrameWait(300);
	mes.ReadDraw(4);
	evFrameWait(1000);
	mes.ReadDraw(4);
	//---なんで！！
	npMove(1,-1,0);
	evFrame();
	mes.ReadDraw(3);
	evFrameWait(700);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(1,SOUTH);
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	//---ルナン部屋を出る
	for(a = 0;a < 4;a ++){
		if(a < 3)
			npMove(1,1,0);
		else
			npMove(1,0,-1);
		evFrame();
		if(a == 2){
			npDir(1,NORTH);
			evFrameWait(1000);
		}
		if(a == 0)
			npDir(0,SOUTH);
		if(a == 1)
			npDir(0,WEST);
	}
	evFrameWait(500);
	mes.ReadDraw(3);
	//---おとしまえつけてやる！！
	npDir(2,EAST);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(2,1,0);
		else
			npMove(2,0,1);
		if(a == 1)
			npDir(1,EAST);
		evFrame();
	}
	//---やめて！
	mes.ReadDraw();
	evFrameWait(500);
	npDir(2,WEST);
	evFrameWait(500);
	mes.ReadDraw(5);

	evFrameWait(500);
	npDir(1,NORTH);
	evFrameWait(500);
	npDir(2,NORTH);
	npMove(1,0,-1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	//---
	npPos(1,0,0);
	npPos(2,0,0);
	npShow(1,0);
	npShow(2,0);

	//---酒場
	crmusicFadeOut();
	crfieldPaletteChange(PALETTE_NIGHT);
	crfieldChangeScene(0,41,11);
	npPos(27,41,10);
	npDir(27,NORTH);
	npPos(28,40,10);
	npDir(28,NORTH);
	npPos(29,36,7);
	npDir(29,EAST);
	em->Put(40,9,2,59);
	em->Put(41,9,2,59);
	evScene(0,41,11);

	evFrameWait(2000);
	crmusicStop();
	mes.ReadDraw(2);
	evFrameWait(500);
	em->Put(41,9,2,1024);
	evFrameWait(250);
	npDir(28,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);
	em->Put(41,9,2,1024);
	//---ぷはー
	evFrameWait(500);
	em->Put(41,9,2,59);
	evFrameWait(500);
	mes.ReadDraw(5);
	evFrameWait(500);
	npDir(28,NORTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);

	//---サヴィアーくる
	crmusicPlay(CRMUSIC_SAKABA);
	for(a = 0;a < 6;a ++){
		if(a < 3)
			npMove(29,0,1);
		else if(a < 6)
			npMove(29,1,0);
		evFrame();
	}
	mes.ReadDraw();
	//---けんかは・・・
	evFrameWait(500);
	npDir(28,WEST);
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	npDir(27,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	for(a = 0;a < 3;a ++){
		if(a < 1)
			npMove(29,0,1);
		else if(a < 3)
			npMove(29,1,0);

		if(a == 0)
			npDir(28,SOUTH);
		if(a == 1)
			npDir(27,WEST);
		if(a == 2)
			npDir(27,SOUTH);
		evFrame();
	}
	npDir(29,NORTH);
	evFrameWait(500);
	mes.ReadDraw(8);
	evFrameWait(500);

	//---翌朝
	em->ReloadPattern();
//	mcShow(1);
//	mcDir(NORTH);

	npPos(27,28,38);
	npDir(27,NORTH);
	npPos(28,27,38);
	npDir(28,NORTH);
	npPos(29,29,39);
	npDir(29,EAST);

	evFadeOut(1000);
	crfieldChangeScene(0,28,39);
	evFieldNoFlip(0,1);
	et->Delay2(1000);
	evFadeIn(1000);
//	evScene(0,28,39);
	crmusicPlay(CRMUSIC_TOWN1);
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(29,NORTH);
	evFrameWait(250);
	npDir(29,WEST);
	evFrameWait(250);
	mes.ReadDraw(4);
	evFrameWait(500);

	mes.CloseMessage();

	for(a = 27;a <= 29;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}

	mcShow(1);
	mcDir(SOUTH);
	evScene(0,28,38);


	//---サヴィアー仲間になる
	{
		pPartyInfo->PartyMember[2] = 3;
		crcharaSetLevelStatus(2,5);
		CrCharacter *pChara = crcharaGetPartyMember(2);
		pChara->SetWeapon(0,50);
		pChara->SetWeapon(1,10);
		pChara->SetProtector(0,101);
		pChara->SetProtector(1,140);
		pChara->SetAccessory(0,0);
		pChara->SetAccessory(1,0);
		pChara->SetBattleFieldStartPos(8,2);
		pChara->SetLevelExperience();
		crcharaLoadFace(-1);
		crcharaCheckBattleFieldPos(2);

		pChara->CharaInfo.MagicTable[0] = 65;
		pChara->AddMagicExperience(-15);
		pChara->CharaInfo.MagicTable[1] = 11;
		pChara->AddMagicExperience(-10);
	}
	prtRecoveryAll();

	evSet(22,1);

	return 1;
}

CREVENTLONG1_API int creventDoguri_FirstVisit(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	evSet(25,1);

	mcShow(0);
	npPos(25,22,6);
	npDir(25,NORTH);
	npPos(26,22,5);
	npDir(26,SOUTH);

	evScene(0,22,6);
	crmusicPlay(CRMUSIC_SS);
	evFrameWait(500);

	mes.OpenMessage("Doguri.msg",100);
	mes.ReadDraw(5);
	mes.CloseMessage();

	evFrameWait(1000);
	npDir(26,WEST);
	evFrameWait(500);
	npDir(26,NORTH);
	evFrameWait(500);

	for(a = 0;a < 10;a ++){
		npMove(26,0,-1);
		evFrame();
	}
	for(a = 25;a <= 26;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}

	mcShow(1);

	return 1;
}

//---ライゼル！！
CREVENTLONG1_API int creventDoguri_MeetLizel(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	npPos(20,21,21);
	npPos(21,20,21);
	npPos(22,22,21);
	for(a = 20;a <= 22;a ++){
		npDir(a,SOUTH);
	}
	evScene(0,21,22);
	crmusicPlay(CRMUSIC_LIZEL);
	npDir(23,NORTH);
	evFrameWait(1000);

	mes.OpenMessage("Doguri.msg",101);
	mes.ReadDraw(4);
	//---やばいんじゃないの？
	evFrameWait(500);
	npDir(20,WEST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(21,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	//---強行決行！！
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(21,SOUTH);
	evFrameWait(250);
	npDir(20,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---どかーん
	evFrameWait(500);
	npDir(23,WEST);
	evFrameWait(200);
	npDir(23,SOUTH);
	evFrameWait(200);
	npDir(23,EAST);
	evFrameWait(200);
	npDir(23,NORTH);
	evFrameWait(500);
	crmusicStop();
	mes.ReadDraw();
	crsoundPlay(CRSOUND_HYURURIRA);

	evFrameWait(3000);
	mes.ReadDraw();

	evFrameWait(250);
	crmusicRestoreStream(0);
//	crmusicPlay(CRMUSIC_LIZEL,1,CRMUSIC_LOADFORCE);
	mes.ReadDraw(6);
	evFrameWait(500);
	npDir(22,WEST);
	evFrameWait(500);
	mes.ReadDraw(5);

	evFrameWait(800);
	npDir(20,EAST);
	evFrameWait(300);
	npDir(20,NORTH);
	evFrameWait(300);
	for(a = 0;a < 3;a ++){
		npMove(20,0,-1);
		if(a == 1)
			npDir(21,EAST);
		if(a == 2){
			npDir(21,NORTH);
			npDir(22,WEST);
		}
		evFrame();
	}
	evFrameWait(200);
	npDir(22,NORTH);
	evFrameWait(700);

	for(a = 0;a < 2;a ++){
		npMove(21,0,-1);
		npMove(22,0,-1);
		if(a == 0)
			npDir(20,WEST);
		if(a == 1){
			npDir(20,SOUTH);
		}
		evFrame();
	}
	evFrameWait(750);
	//---民主的な話し合い
	mes.ReadDraw(2);
	mes.ReadDraw(3);
	evFrameWait(500);
	npDir(22,WEST);
	evFrameWait(1000);
	npDir(22,NORTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	//---ルナンが来る
	for(a = 0;a < 3;a ++){
		npMove(20,0,1);
		if(a == 0)
			npDir(21,EAST);
		if(a == 1){
			npDir(21,SOUTH);
			npDir(22,WEST);
		}
		if(a == 2)
			npDir(22,SOUTH);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.CloseMessage();

	for(a = 20;a <= 23;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}

	mcShow(1);
	evSet(25,2);
	evScene(0,21,22);

	//---ライゼル仲間になる
	{
		pPartyInfo->PartyMember[3] = 5;
		crcharaSetLevelStatus(3,5);
		CrCharacter *pChara = crcharaGetPartyMember(3);
		pChara->SetWeapon(0,89);
		pChara->SetProtector(0,101);
		pChara->SetProtector(1,140);
		pChara->SetAccessory(0,0);
		pChara->SetAccessory(1,0);
		pChara->SetBattleFieldStartPos(2,4);
		pChara->SetLevelExperience();
		crcharaLoadFace(-1);
		crcharaCheckBattleFieldPos(3);
	}
	prtRecovery(3);

	return 1;
}


CREVENTLONG1_API int creventVS_SS(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	npPos(4,13,7);
	npPos(5,14,8);
	npPos(6,12,7);
	npPos(7,12,8);
	for(a = 4;a <= 7;a ++){
		npDir(a,EAST);
	}
	evScene(3,14,8);
	crmusicPlay(CRMUSIC_SS);

	mes.OpenMessage("ss.msg",103);

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	npDir(0,WEST);
	evFrameWait(500);
	//---あっ
	mes.ReadDraw();
	
	evFrameWait(500);
	npDir(1,WEST);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---ディザ前に出る
	for(a = 0;a < 6;a ++){
		if(a < 5)
			npMove(5,1,0);
		else
			npMove(5,0,-1);
		if(a == 2)
			npDir(0,SOUTH);
		if(a == 3)
			npDir(1,SOUTH);
		evFrame();
	}
	evFrameWait(500);
	npDir(5,NORTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);

	//---ルナンも
	for(a = 0;a < 5;a ++){
		npMove(4,1,0);
		evFrame();
	}
	for(a = 0;a < 4;a ++){
		mcMove(1,0);
		evFrame();
	}
	evFrameWait(500);
	npDir(4,NORTH);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(5);

	//---伝説の盗賊
	evFrameWait(500);
	mes.ReadDraw(8);

	evFrameWait(500);
	npDir(0,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(1,WEST);
	evFrameWait(500);
	mes.ReadDraw();
	//---Ｊ＆Ｐ
	evFrameWait(500);
	npDir(0,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(1,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---ぷぷ
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(250);
	//---遠距離突っ込み・サヴィアー
	for(a = 0;a < 4;a ++){
		npMove(6,1,0);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();

	//---うるせえ
	evFrameWait(500);
	npDir(0,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(0,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.CloseMessage();

	//---バトル
	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.Music = CRMUSIC_BOSSBATTLE1;
	BattleInfo.Enemy[0].Enemy = 39;
	BattleInfo.Enemy[0].x = 4;
	BattleInfo.Enemy[0].y = 6;
	BattleInfo.Enemy[1].Enemy = 40;
	BattleInfo.Enemy[1].x = 8;
	BattleInfo.Enemy[1].y = 7;
	BattleInfo.Enemy[2].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	evField(0,1);
	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}

	evFrameWait(500);
	mes.OpenMessage("ss.msg",104);
	mes.ReadDraw(2);
	evFrameWait(250);
	for(a = 0;a < 17;a ++){
		if(a < 1)
			npMove(1,1,0);
		else if(a < 4)
			npMove(1,0,1);
		else
			npMove(1,1,0);

		if(a < 1){
		} else if(a < 4)
			npMove(0,1,0);
		else if(a < 8)
			npMove(0,0,1);
		else
			npMove(0,1,0);

		if(a == 10)
			npDir(4,EAST);
		if(a == 11)
			npDir(5,EAST);
		evFrame();
	}
	npPos(1,31,8);
	npPos(0,30,9);
	//---ルナンも追う
	int old = ef->SetMoveSpeed(2);
	for(a = 0;a < 13;a ++){
		if(a < 1)
			npMove(5,0,1);
		else if(a < 11)
			npMove(5,1,0);
		if(a < 1){
		} else if(a < 2)
			npMove(4,0,1);
		else if(a < 12)
			npMove(4,1,0);

		if(a > 1)
			mcMove(1,0);
		evFrame();
	}
	ef->SetMoveSpeed(old);
	evFrameWait(250);
	mes.ReadDraw(2);
	//---机の上に・・・
	evFrameWait(500);
	for(a = 0;a < 4;a ++){
		if(a < 3)
			npMove(1,1,0);
		else if(a < 4)
			npMove(1,0,-1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	for(a = 0;a < 8;a ++){
		if(a < 5)
			npMove(0,1,0);
		else if(a < 8)
			npMove(0,0,-1);
		evFrame();
	}
	evFrameWait(500);
	//---さがさないでね
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

	//---ドーグリ
	evSet(26,1);
	crfieldChangeMap(22,0,1);
	evReadObject(13,"Tozoku1.acf");
	evReadObject(14,"Tozoku2.acf");
	npPos(20,22,6);
	npPos(21,23,6);
	npPos(22,21,7);
	npPos(23,24,7);
	for(a = 20;a <= 23;a ++){
		npDir(a,NORTH);
	}

	npPos(27,22,5);
	npPos(28,23,5);
	for(a = 27;a <= 28;a ++){
		npDir(a,SOUTH);
	}
	evScene(0,22,7);
	evFrameWait(1000);
	mes.ReadDraw(5);

	evFrameWait(500);
	npDir(20,EAST);
	evFrameWait(500);
	//---そういう問題では・・・
	mes.ReadDraw(2);

	evFrameWait(500);
	npDir(20,NORTH);
	evFrameWait(500);
	mes.ReadDraw(10);

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	//---Ｊ＆Ｐ去る
	npDir(27,WEST);
	evFrameWait(300);
	npDir(27,NORTH);
	npDir(28,EAST);
	evFrameWait(300);
	npDir(28,NORTH);
	evFrameWait(300);
	for(a = 0;a < 15;a ++){
		npMove(27,0,-1);
		if(a > 1)
			npMove(28,0,-1);
		evFrame();
	}

	evFrameWait(250);
	npDir(21,WEST);
	evFrameWait(500);
	mes.ReadDraw();
	//---そうね
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

	mes.ReadDraw();
	evFrameWait(500);
	npDir(20,WEST);
	evFrameWait(200);
	npDir(21,SOUTH);
	evFrameWait(200);
	npDir(20,SOUTH);
	evFrameWait(200);
	npDir(23,WEST);
	evFrameWait(200);

	mes.ReadDraw(2);

	evFrameWait(500);
	npDir(20,EAST);
	evFrameWait(200);
	npDir(22,EAST);
	evFrameWait(200);
	npDir(21,EAST);
	evFrameWait(200);
	npDir(20,SOUTH);
	evFrameWait(200);
	for(a = 0;a < 1;a ++){
		npMove(20,0,1);
		evFrame();
	}
	evFrameWait(200);
	npDir(20,EAST);
	evFrameWait(500);

	mes.ReadDraw(2);
	evFrameWait(800);
	mes.ReadDraw(3);
	//---わかれなごみおしくも
	evFrameWait(250);
	crmusicPlay(CRMUSIC_LIZEL);
	evFrameWait(250);
	mes.ReadDraw();
	//---まさか・・・
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(150);
	npDir(23,NORTH);
	evFrameWait(150);
	npDir(23,EAST);
	evFrameWait(150);
	npDir(23,SOUTH);
	evFrameWait(150);
	npDir(23,WEST);
	evFrameWait(500);

	mes.ReadDraw(2);
	evFrameWait(250);

	for(a = 0;a < 16;a ++){
		npMove(20,0,1);
		if(a > 1)
			npMove(21,0,1);
		if(a > 2)
			npMove(22,0,1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(1000);
	crmusicPlay(CRMUSIC_VILLAGE1);

	npPos(20,34,33);
	npPos(21,35,33);
	npPos(22,35,34);
	npPos(10,33,33);
	for(a = 20;a <= 22;a ++){
		npDir(a,WEST);
	}
	npDir(10,EAST);
	evScene(0,34,34);

	evFrameWait(1000);
	mes.ReadDraw(3);
	npPos(26,34,25);
	npDir(26,SOUTH);
	evFrameWait(1000);
	//---エターナル登場
	for(a = 0;a < 7;a ++){
		npMove(26,0,1);
		if(a == 4)
			npDir(20,NORTH);
		if(a == 5)
			npDir(10,NORTH);
		if(a == 6)
			npDir(21,NORTH);
		if(a == 6)
			npDir(22,NORTH);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	for(a = 0;a < 1;a ++){
		npMove(10,0,-1);
		evFrame();
	}
	evFrameWait(250);
	npDir(10,EAST);
	evFrameWait(250);
	npDir(26,WEST);
	evFrameWait(500);

	mes.ReadDraw(2);
	//---私達よ
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(26,SOUTH);
	evFrameWait(500);

	evFrameWait(500);
	npDir(10,SOUTH);
	evFrameWait(500);
	npDir(10,EAST);
	evFrameWait(500);
	mes.ReadDraw(5);

	//---よくわかってるね
	evFrameWait(1000);
	mes.ReadDraw(5);
	evFrameWait(1000);
	//---ぐっばい
	mes.ReadDraw();
	evFrameWait(500);
	npDir(26,WEST);
	evFrameWait(500);
	npDir(26,NORTH);
	evFrameWait(500);
	for(a = 0;a < 10;a ++){
		npMove(26,0,-1);
		evFrame();
	}
	//---やなかんじ
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	for(a = 0;a < 1;a ++){
		npMove(10,0,1);
		evFrame();
	}
	evFrameWait(500);
	npDir(10,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	//---大丈夫よ
	evFrameWait(300);
	npDir(20,WEST);
	evFrameWait(100);
	npDir(21,WEST);
	evFrameWait(100);
	npDir(22,WEST);
	evFrameWait(200);

	mes.ReadDraw(12);
	evFrameWait(250);
	critemAddItem(214,1);

	mes.CloseMessage();
	for(a = 20;a <= 28;a ++){
		npShow(a,0);
		npPos(a,0,0);
	}
	mcShow(1);

	//---ライゼルはずれる
	prtRecoveryAll();
	pPartyInfo->PartyMember[3] = -1;

	mcDir(SOUTH);
	npPos(3,23,5);
	npPos(4,24,5);
	npDir(3,EAST);
	npDir(4,WEST);

	eiMapObject *pObject = em->GetObject(3);
	pObject->Data.Status &= (~EF_OBJECT_ST_MOVERANDOM);
	pObject->Data.Status |= (EF_OBJECT_ST_MOVEFIXED);
	pObject = em->GetObject(4);
	pObject->Data.Status &= (~EF_OBJECT_ST_MOVERANDOM);
	pObject->Data.Status |= (EF_OBJECT_ST_MOVEFIXED);

	evScene(0,36,24);

	return 1;
}

CREVENTLONG1_API int creventDoguri_DizzaCindy(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	npPos(20,22,8);
	npDir(20,NORTH);
	npPos(21,23,8);
	npDir(21,NORTH);
	npPos(22,21,9);
	npDir(22,NORTH);
	evScene(0,23,9);
	evFrameWait(250);
	mes.OpenMessage("Doguri.msg",102);
	mes.ReadDraw(2);
	evFrameWait(500);

	for(a = 0;a < 2;a ++){
		npMove(21,0,-1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);
	npDir(4,SOUTH);
	evFrameWait(250);

	//---そいつって・・・こんな感じ？
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(3);

	evFrameWait(500);
	//---ここでお別れよ
	npDir(21,WEST);
	evFrameWait(250);
	npDir(21,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	npMove(20,0,-1);
	evFrame();
	npMove(20,1,0);
	evFrame();
	npDir(20,NORTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---見つけました
	evFrameWait(1000);
	mes.ReadDraw();
	//---わたしもいく！
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(500);
	npDir(21,WEST);
	evFrameWait(250);
	for(a = 0;a < 4;a ++){
		if(a < 2)
			npMove(21,-1,0);
		else
			npMove(21,0,-1);
		evFrame();
	}
	evFrameWait(50);
	mes.ReadDraw();
	//---じゃあどうしろって？
	evFrameWait(250);
	npDir(21,EAST);
	evFrameWait(250);
	npDir(21,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---夜の酒場
	crfieldPaletteChange(PALETTE_NIGHT);
	npPos(20,6,7);
	npDir(20,SOUTH);
	npPos(21,5,8);
	npDir(21,EAST);
	npPos(22,7,8);
	npDir(22,WEST);
	npPos(24,11,4);
	npDir(24,WEST);
	evScene(0,9,9);
	crmusicPlay(CRMUSIC_SAKABA);

	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(500);
	npDir(20,EAST);
	evFrameWait(250);
	npDir(20,NORTH);
	evFrameWait(250);
	//---トマト！
	mes.ReadDraw();
	evFrameWait(500);
	npDir(20,EAST);
	evFrameWait(250);
	npDir(20,SOUTH);
	evFrameWait(500);
	mes.ReadDraw(13);
	evFrameWait(1000);
	mes.ReadDraw();
	//---ねえおじさん
	evFrameWait(500);
	npDir(20,EAST);
	evFrameWait(250);
	npDir(20,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	npDir(13,WEST);
	evFrameWait(500);
	for(a = 0;a < 2;a ++){
		npMove(13,-1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(13,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(13,EAST);
	evFrameWait(500);
	//---シンディちゃんご指名
	mes.ReadDraw(2);
	evFrameWait(500);
	for(a = 0;a < 3;a ++){
		npMove(13,1,0);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw(4);
	//---ルナン近づく
	evFrameWait(250);
	npDir(20,EAST);
	evFrameWait(250);
	for(a = 0;a < 7;a ++){
		if(a < 5)
			npMove(20,1,0);
		else
			npMove(20,0,-1);
		if(a == 4)
			npDir(22,NORTH);
		if(a == 5)
			npDir(24,SOUTH);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(20,WEST);
	evFrameWait(250);
	npDir(20,SOUTH);
	evFrameWait(250);

	for(a = 0;a < 12;a ++){
		if(a < 2)
			npMove(20,0,1);
		else if(a < 7)
			npMove(20,-1,0);
		else
			npDir(20,SOUTH);
		if(a == 4)
			npDir(22,WEST);
		if(a < 2){
		} else if(a < 7)
			npMove(24,0,1);
		else if(a < 12)
			npMove(24,-1,0);

		if(a == 9)
			npDir(22,SOUTH);
		if(a == 11)
			npDir(21,SOUTH);
		evFrame();
	}
	evFrameWait(250);
	npDir(24,NORTH);
	evFrameWait(500);
	//---ありがとさん
	mes.ReadDraw(5);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	//---拙者・・・
	mes.ReadDraw(3);
	evFrameWait(500);

	npDir(24,EAST);
	evFrameWait(250);
	for(a = 0;a < 4;a ++){
		if(a < 3)
			npMove(24,1,0);
		else
			npMove(24,0,-1);

		if(a == 2)
			npDir(20,EAST);
		if(a == 3){
			npDir(21,EAST);
			npDir(22,EAST);
		}
		evFrame();
	}
	evFrameWait(250);
	npDir(24,WEST);
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	npDir(24,NORTH);
	evFrameWait(250);
	npDir(24,EAST);
	evFrameWait(250);
	for(a = 0;a < 20;a ++){
		npMove(24,1,0);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(20,SOUTH);
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(3000);
	//---物静かな女性って・・・
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---翌朝
	em->ReloadPattern();
	npPos(20,16,6);
	npDir(20,SOUTH);
	npPos(21,15,6);
	npDir(21,SOUTH);
	npPos(22,17,6);
	npDir(22,SOUTH);
	npPos(24,16,7);
	npDir(24,NORTH);

	npDir(3,EAST);

	crmusicPlay(CRMUSIC_VILLAGE1);

	evScene(0,16,7);

	evFrameWait(250);
	mes.ReadDraw(5);
	evFrameWait(500);
	npDir(21,EAST);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	npDir(21,SOUTH);
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);

	mcShow(1);
	mcDir(SOUTH);
	for(a = 20;a <= 24;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	npPos(13,8,4);
	npDir(13,SOUTH);
	evScene(0,16,6);

	for(a = 3;a <= 4;a ++){
		eiMapObject *pObject = em->GetObject(a);
		pObject->Data.Status &= (~EF_OBJECT_ST_MOVEFIXED);
		pObject->Data.Status |= (EF_OBJECT_ST_MOVERANDOM);
	}
	npDir(3,EAST);

	mes.CloseMessage();

	//---シンディ仲間になる
	{
		pPartyInfo->PartyMember[3] = 6;
		crcharaSetLevelStatus(3,6);
		CrCharacter *pChara = crcharaGetPartyMember(3);
		pChara->SetWeapon(0,11);
		pChara->SetProtector(0,92);
		pChara->SetProtector(1,140);
		pChara->SetProtector(2,256);
		pChara->SetAccessory(0,0);
		pChara->SetAccessory(1,0);
		pChara->SetBattleFieldStartPos(2,3);
		pChara->SetLevelExperience();
		crcharaLoadFace(-1);
		crcharaCheckBattleFieldPos(3);

		pChara->CharaInfo.MagicTable[0] = 1;
		pChara->AddMagicExperience(-15);
		pChara->CharaInfo.MagicTable[1] = 59;
		pChara->AddMagicExperience(-10);
	}
	prtRecoveryAll();

	evSet(27,1);

	return 1;
}


ei_s32 DoguriIsekiCallBack(int turn,int action,int number,
				  ei_u32 com,CrCharacter *chara)
{
	CR_BATTLECOMMAND *pCommand = (CR_BATTLECOMMAND *)com;
	CrBattleCharacter *pChara = (CrBattleCharacter *)chara;
	int crnum = BATTLECHARA_STARTENEMY;

	if(action == 0){
		if(turn < 4)
			return 1;
		else
			return 0;
	}
	if(action == 1){
		if(number == 0){
			//---ディザ
			if(turn != 1){
				pCommand->Main = BAT_COMMAND_WEAPON;
				pCommand->Sub[0] = 0;
				pCommand->Hit = 0;
				pCommand->Range = BAT_TARGET_ENEMYSINGLE;
				pCommand->Target = (ei_u32)crbatRandomSelect(pChara,BAT_TARGET_ENEMY);
			} else {
				pCommand->Main = BAT_COMMAND_DEFENSE;
				pCommand->Sub[0] = BAT_SUBCOM_MOVE;
				pCommand->Sub[1] = 6;
				pCommand->Sub[2] = 7;
			}
		}
	}
	if(turn == 0){
		if(action == 3 && number == 0){
			crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);
			crbatBeginCameraObjectToObject(0,pChara,&pChara[crnum],
			ANGLE(270),
			-1.0f,-1.0f,500);
			crbatClearDrawingList();
			crbatAddDrawingListAll();
			crbatDoMovingCamera(500);

			CrMesManager mes;
			mes.CreateNewMessage(-1,-1,32,24,5);
			mes.OpenMessage("DoguriSouth_Iseki.msg",104);
			mes.ReadMessage();
			mes.Draw();
			mes.CloseMessage();
		}
		if(action == 2 && number == 0){
			crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);
			crbatBeginCameraObjectToObject(0,pChara,&pChara[crnum],
			ANGLE(270),
			-1.0f,-1.0f,500);
			crbatClearDrawingList();
			crbatAddDrawingListAll();
			crbatDoMovingCamera(500);

			CrMesManager mes;
			mes.CreateNewMessage(-1,-1,32,24,5);
			mes.OpenMessage("DoguriSouth_Iseki.msg",105);
			mes.ReadMessage();
			mes.Draw();
			mes.CloseMessage();
		}
	}
	if(turn == 3){
		if(action == 2 && number == 0){
			crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);
			crbatBeginCameraObjectToObject(0,pChara,&pChara[crnum],
			ANGLE(270),
			-1.0f,-1.0f,500);
			crbatClearDrawingList();
			crbatAddDrawingListAll();
			crbatDoMovingCamera(500);

			CrMesManager mes;
			mes.CreateNewMessage(-1,-1,32,24,5);
			mes.OpenMessage("DoguriSouth_Iseki.msg",107);
			mes.ReadMessage();
			mes.Draw();
			mes.CloseMessage();
		}
	}

	return 1;
}

//---クレイシブと初対面
CREVENTLONG1_API int creventDoguriIseki_Crasive(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	npPos(0,11,15);
	npPos(1,10,16);
	npPos(2,12,15);
	npPos(3,10,15);
	npPos(4,16,27);
	for(a = 0;a < 5;a ++){
		npDir(a,SOUTH);
	}
	em->Put(16,28,2,106);
	evScene(3,11,15);

	evFrameWait(1000);
	mes.OpenMessage("DoguriSouth_Iseki.msg",103);
	//---この部屋は？
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(2000);
	crsoundPlay(CRSOUND_BOOKPAGE);
	evFrameWait(1000);
	crsoundPlay(CRSOUND_BOOKPAGE);
	evFrameWait(300);
	crsoundPlay(CRSOUND_BOOKPAGE);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);

	//---ディザ駆け出す
	for(a = 0;a < 3;a ++){
		npMove(1,0,1);
		evFrame();
	}
	for(a = 0;a < 5;a ++){
		mcMove(0,1);
		evFrame();
	}
	//---誰だ！
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	for(a = 0;a < 9;a ++){
		if(a < 8)
			npMove(1,0,1);
		else
			npDir(1,EAST);

		evFrame();
	}
	for(a = 0;a < 8;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(2000);
	npMove(1,1,0);
	evFrameWait(1500);
	//---ようやく会えたな
	mes.ReadDraw();
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(250);

	for(a = 0;a < 12;a ++){
		if(a < 11)
			npMove(2,0,1);
		else
			npDir(2,EAST);
		evFrame();
	}
	evFrameWait(500);
	//---先生！
	mes.ReadDraw();
	evFrameWait(500);

	for(a = 0;a < 10;a ++){
		npMove(0,0,1);
		if(a)
			npMove(3,0,1);
		evFrame();
	}
	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(350);
	npDir(3,EAST);
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(1000);
	npMove(1,1,0);
	evFrame();
	evFrameWait(1000);
	mes.ReadDraw();

	//---・・・・・・
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	npMove(1,1,0);
	evFrame();
	evFrameWait(1000);
	mes.ReadDraw();

	//---ふーあーゆー？
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	for(a = 0;a < 1;a ++){
		npMove(1,1,0);
		evFrame();
	}
	evFrameWait(250);

	mes.CloseMessage();

	//---ディザ突撃！
//---戦い！！
	//---パーティー設定
	pPartyInfo->PartyMember[0] = 1;
	pPartyInfo->PartyMember[1] = -1;
	pPartyInfo->PartyMember[2] = -1;
	pPartyInfo->PartyMember[3] = -1;

	CR_BATTLEINFO BatInfo;
	memset(&BatInfo,0,sizeof(BatInfo));
	BatInfo.FailOK = 1;
	BatInfo.Music = CRMUSIC_BATTLE;
	BatInfo.Mode = 0;
	BatInfo.ScreenEfect = 1;
	BatInfo.Enemy[0].Enemy = 44;
	BatInfo.Enemy[0].x = 6;
	BatInfo.Enemy[0].y = 10;
	BatInfo.Enemy[1].Enemy = -1;
	BatInfo.DontShowAfterBattle = 1;
	BatInfo.lpTurnCallBack = DoguriIsekiCallBack;
	evField(0,1);
	npDir(4,WEST);
	crbatEventBattle(&BatInfo);
	crhistSubBattleCount();

	//---パーティー設定
	pPartyInfo->PartyMember[0] = 0;
	pPartyInfo->PartyMember[1] = 1;
	pPartyInfo->PartyMember[2] = 3;
	pPartyInfo->PartyMember[3] = 6;

	evFrameWait(1500);
	for(a = 0;a < 2;a ++){
		npMove(2,1,0);
		evFrame();
	}
	evFrameWait(500);
	mes.OpenMessage("DoguriSouth_Iseki.msg",108);
	mes.ReadDraw();
	evFrameWait(1000);
	npDir(4,NORTH);
	evFrameWait(500);
	for(a = 0;a < 1;a ++){
		npMove(4,0,-1);
		evFrame();
	}
	evFrameWait(500);
	npDir(4,WEST);
	evFrameWait(500);
	//---何か用か？
	mes.ReadDraw(2);
	evFrameWait(1000);
	npDir(4,NORTH);
	evFrameWait(500);
	npDir(4,EAST);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	//---クレイシヴが歩く
	for(a = 0;a < 15;a ++){
		if(a < 2)
			npMove(4,1,0);
		else if(a < 5)
			npMove(4,0,1);
		else if(a < 11)
			npMove(4,-1,0);
		else
			npMove(4,0,-1);

		if(a == 6)
			npDir(1,SOUTH);
		if(a == 7)
			npDir(2,SOUTH);
		if(a == 11)
			npDir(1,WEST);
		if(a == 13)
			npDir(2,WEST);

		if(a == 13)
			npDir(0,EAST);
		if(a == 14)
			npDir(3,EAST);

		evFrame();
		evFrameWait(500);
	}
	evFrameWait(1000);
	npDir(4,WEST);
	evFrameWait(1000);
	//---名前は？
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1500);
	npDir(4,NORTH);
	evFrameWait(1000);

	for(a = 0;a < 4;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(1000);
	for(a = 0;a < 3;a ++){
		npMove(4,0,-1);
		if(a == 1)
			npDir(0,NORTH);
		if(a == 2)
			npDir(3,NORTH);
		evFrame();
		evFrameWait(500);
	}
	//---どないすんねん！
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(3000);
	for(a = 0;a < 6;a ++){
		npMove(4,0,-1);
		if(a == 0)
			npDir(2,NORTH);
		if(a == 1)
			npDir(1,NORTH);
		evFrame();
		evFrameWait(500);
	}
	evFrameWait(2000);

	crfieldChangeMap(24,0,1,1);
	npPos(1,61,20);
	npDir(1,WEST);
	npPos(2,62,21);
	npDir(2,EAST);
	npPos(3,60,19);
	npDir(3,SOUTH);
	npPos(4,59,20);
	npDir(4,EAST);
	npPos(5,53,6);
	npDir(5,EAST);
	evScene(0,60,21);

	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(1000);
	npDir(1,SOUTH);
	evFrameWait(500);
	npDir(1,EAST);
	evFrameWait(500);
	//---ディザ？
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw(3);
	evFrameWait(1000);
	npDir(1,SOUTH);
	evFrameWait(500);
	npDir(1,WEST);
	evFrameWait(500);

	mes.ReadDraw(2);
	evFrameWait(500);
	npDir(4,SOUTH);
	evFrameWait(500);
	npDir(4,WEST);
	evFrameWait(500);
	//---シンディ？
	mes.ReadDraw(2);
	evFrameWait(300);
	npDir(4,NORTH);
	evFrameWait(300);
	npDir(4,EAST);
	evFrameWait(500);
	mes.ReadDraw(3);

	//---アサッシン登場
	for(a = 0;a < 16;a ++){
		if(a < 14)
			npMove(5,0,1);
		else
			npMove(5,1,0);
		if(a == 12)
			npDir(3,WEST);
		if(a == 13)
			npDir(4,SOUTH);
		if(a == 14)
			npDir(4,WEST);
		evFrame();
	}
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);
	npDir(2,WEST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	npMove(5,1,0);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(2000);
	mes.ReadDraw(3);
	evFrameWait(1000);
	mes.ReadDraw(8);

	evFrameWait(500);
	for(a = 0;a < 2;a ++){
		npMove(5,1,0);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);
	//---今度こそルナン？
	for(a = 0;a < 4;a ++){
		if(a < 1)
			npMove(5,0,1);
		else if(a < 4)
			npMove(5,1,0);
		if(a == 1)
			npDir(4,SOUTH);
		if(a == 3)
			npDir(4,EAST);
		if(a == 2)
			npDir(1,SOUTH);
		if(a == 2)
			npDir(3,SOUTH);
		evFrame();
	}
	evFrameWait(250);
	npDir(5,NORTH);
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);

	npDir(5,WEST);
	evFrameWait(500);
	for(a = 0;a < 3;a ++){
		npMove(5,-1,0);
		if(a == 1)
			npDir(1,WEST);
		if(a == 2)
			npDir(4,SOUTH);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---かわいいこ
	for(a = 0;a < 1;a ++){
		npMove(5,-1,0);
		npDir(4,WEST);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(1,0,1);
		else
			npMove(1,-1,0);
		npMove(5,-1,0);
		evFrame();
	}
	//---それわわたし！
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(5,NORTH);
	evFrameWait(250);
	npDir(5,EAST);
	evFrameWait(250);

	mes.ReadDraw(2);

	//---おーばかやろー！
	evFrameWait(250);
	npMove(2,-1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);

	for(a = 0;a < 2;a ++){
		npMove(5,1,0);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	for(a = 0;a < 2;a ++){
		npMove(5,1,0);
		evFrame();
	}
	evFrameWait(500);
	//---バトル
	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.Music = CRMUSIC_BOSSBATTLE1;
	BattleInfo.Enemy[0].Enemy = 48;
	BattleInfo.Enemy[0].x = 6;
	BattleInfo.Enemy[0].y = 6;
	BattleInfo.Enemy[1].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	evField(0,1);
	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}

	evFrameWait(500);
	for(a = 0;a < 2;a ++){
		npMove(5,-1,0,0);
		if(a == 1)
			npDir(3,WEST);
		evFrame();
	}
	evFrameWait(250);

	mes.ReadDraw();
	evFrameWait(500);
	for(a = 0;a < 4;a ++){
		if(a < 1)
			npMove(2,0,1);
		else if(a < 3)
			npMove(2,-1,0);
		else
			npMove(2,0,-1);
		evFrame();
	}
	evFrameWait(250);
	npDir(2,WEST);
	evFrameWait(250);

	mes.ReadDraw(2);
	evFrameWait(500);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npMove(2,-1,0);
	evFrame();
	evFrameWait(500);

	//---待たれよ！
	mes.ReadDraw(4);
	//---あとずさり
	npMove(5,-1,0,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(4);
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(2,SOUTH);
	evFrameWait(250);
	npDir(2,EAST);
	evFrameWait(250);
	mes.ReadDraw();
	//---私は？
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	npDir(2,SOUTH);
	evFrameWait(250);
	npDir(2,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---はて？
	evFrameWait(1000);
	npDir(5,NORTH);
	evFrameWait(500);
	npDir(5,EAST);
	evFrameWait(500);
	npDir(5,SOUTH);
	evFrameWait(500);
	npDir(5,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npMove(2,-1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(250);
	npDir(5,NORTH);
	evFrameWait(250);
	npDir(5,WEST);
	evFrameWait(250);
	//---アサッシン去る
	for(a = 0;a < 10;a ++){
		if(a == 3)
			npMove(5,0,-1);
		else
			npMove(5,-1,0);
		evFrame();
	}
	evFrameWait(250);

	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

	npDir(2,SOUTH);
	evFrameWait(150);
	npDir(4,SOUTH);
	evFrameWait(100);
	npDir(2,EAST);
	evFrameWait(250);
	npDir(4,EAST);
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);

	mes.ReadDraw(4);
	evFrameWait(250);

	mes.CloseMessage();

	mcShow(1);
	evSet(42,1);
	//---フィールドへ
	mcDir(NORTH);
	evMap(10,0,129,258);

	return 1;
}

//---アネートナック登場
CREVENTLONG1_API int creventAneat_Nack(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	crfieldChangeMap(21,1);
	npPos(1,14,2);
	evScene(1,10,12);

	mes.OpenMessage("Aneat.msg",102);

	evFrameWait(2000);
	for(a = 0;a < 10;a ++){
		if(a < 10)
			npMove(1,0,1);
		evFrame();
	}
	evFrameWait(500);
	npDir(1,WEST);
	evFrameWait(1000);

	for(a = 0;a < 3;a ++){
		npMove(1,-1,0);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(250);

	mes.ReadDraw(5);
	evFrameWait(1000);
	mes.ReadDraw(2);
	//---ルナン出ていく
	evFrameWait(500);
	npDir(1,NORTH);
	evFrameWait(300);
	npDir(1,EAST);
	evFrameWait(300);

	npMove(1,1,0);
	evFrame();
	evFrameWait(100);
	mes.ReadDraw(2);
	evFrameWait(700);
//	evMap(21,0,34,49);

	for(a = 0;a < 2;a ++){
		npMove(1,1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	for(a = 0;a < 10;a ++){
		npMove(1,0,-1);
		evFrame();
	}
	evFrameWait(1000);
	npPos(1,0,0);
	npShow(1,0);
	npDir(0,WEST);

	//---アネート町中
	crfieldChangeScene(0,16,19);
	npPos(27,13,10);
	npDir(27,NORTH);
	npPos(28,15,17);
	npDir(28,NORTH);
	npPos(29,18,18);
	npDir(29,WEST);
	npPos(32,16,19);
	npDir(32,SOUTH);
	evScene(0,16,19);

	evFrameWait(2000);
	for(a = 0;a < 7;a ++){
		if(a < 7)
			npMove(27,0,1);
		if(a == 6)
			npDir(28,WEST);
		evFrame();
	}

	evFrameWait(500);
	npDir(27,EAST);
	evFrameWait(1000);
	//---すんだのか？
	mes.ReadDraw(2);

	//---向こうの方で
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(29,SOUTH);
	evFrameWait(250);
	npDir(28,NORTH);
	evFrameWait(250);
	npDir(29,EAST);
	evFrameWait(120);
	npDir(27,EAST);
	evFrameWait(250);
	npDir(28,EAST);
	evFrameWait(500);

	mes.ReadDraw();

	//---ナックがからまれてる
	evFrameWait(500);
	npPos(31,46,18);
	npDir(31,WEST);
	npPos(33,45,18);
	npDir(33,EAST);
	npPos(34,46,17);
	npDir(34,SOUTH);
	evReadObject(0,"Tozoku1.acf");
	evReadObject(1,"Tozoku2.acf");
	for(a = 0;a < 30;a ++){
		mcMove(1,0);
		evFrame();
	}
	crmusicPlay(CRMUSIC_SS);
	evFrameWait(1000);

	mes.ReadDraw(2);
	npPos(27,36,18);
	npDir(27,EAST);
	npPos(28,35,17);
	npDir(28,EAST);
	npPos(29,35,19);
	npDir(29,EAST);
	evFrameWait(1000);

	//---トマトなら
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(33,NORTH);
	evFrameWait(125);
	npDir(34,WEST);
	evFrameWait(125);
	npDir(33,WEST);
	evFrameWait(250);

	for(a = 0;a < 5;a ++){
		mcMove(-1,0);
		evFrame();
	}
	evFrameWait(250);
	//---ね、ねえさん
	mes.ReadDraw();
	evFrameWait(250);
	for(a = 0;a < 5;a ++){
		mcMove(1,0);
		evFrame();
	}
	evFrameWait(250);
	for(a = 0;a < 9;a ++){
		if(a < 6)
			npMove(27,1,0);
		if(a > 0 && a < 6)
			npMove(28,1,0);
		if(a > 2 && a < 9)
		npMove(29,1,0);
		if(a < 7)
			npMove(32,1,0);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(4);
	evFrameWait(250);
	npMove(27,1,0);
	evFrame();
	evFrameWait(250);
	//---とびこみなさい！
	mes.ReadDraw(2);
	//---二人が去る
	evFrameWait(250);
	npDir(34,NORTH);
	evFrameWait(150);
	npDir(33,NORTH);
	evFrameWait(150);
	npDir(34,EAST);
	evFrameWait(150);

	for(a = 0;a < 12;a ++){
		npMove(34,1,0);
		if(a < 1)
			npMove(33,0,-1);
		else
			npMove(33,1,0);
		evFrame();
	}
	evFrameWait(1000);
	for(a = 0;a < 2;a ++){
		mcMove(-1,0);
		evFrame();
	}
	evFrameWait(500);
	npMove(31,-1,0);
	evFrame();
	evFrameWait(500);
	//---ありがとうございます
	mes.ReadDraw(3);
	evFrameWait(500);
	npDir(27,NORTH);
	evFrameWait(300);
	npDir(27,WEST);
	evFrameWait(300);
	mes.ReadDraw();
	evFrameWait(500);

	for(a = 0;a < 5;a ++){
		npMove(28,1,0);
		if(a == 2)
			npDir(27,NORTH);
		if(a == 3)
			npDir(27,EAST);
		if(a == 4)
			npDir(31,NORTH);
		evFrame();
	}
	evFrameWait(100);
	npDir(28,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---夜の酒場
	crfieldPaletteChange(PALETTE_NIGHT);
	npPos(31,38,10);
	npDir(31,NORTH);
	npPos(28,39,10);
	npDir(28,NORTH);
	npPos(27,40,10);
	npDir(27,NORTH);
	npPos(29,42,10);
	npDir(29,NORTH);
	npPos(32,43,10);
	npDir(32,NORTH);

	evScene(0,40,11);
	crmusicPlay(CRMUSIC_SAKABA);
	evFrameWait(2000);

	mes.ReadDraw(2);
	evFrameWait(500);
	npDir(31,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(31,NORTH);
	evFrameWait(500);
	mes.ReadDraw();
	//---あのなあ
	evFrameWait(500);
	npDir(28,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(28,NORTH);
	evFrameWait(1000);
	//---酒豪サヴィアー
	mes.ReadDraw(2);

	evFrameWait(1000);
	mes.ReadDraw(4);
	evFrameWait(2000);
	mes.ReadDraw(2);
	//---だめよ！
	evFrameWait(250);
	npDir(31,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(27,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	//---あたし、１６
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);
	npDir(31,NORTH);
	evFrameWait(500);
	npDir(27,NORTH);
	evFrameWait(1000);
	mes.ReadDraw(4);

	evFrameWait(250);
	npDir(27,WEST);
	evFrameWait(250);
	//---どゆこと？
	mes.ReadDraw(2);

	evFrameWait(250);
	npDir(27,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(28,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(29,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	//---うん、
	evFrameWait(500);
	npDir(31,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(27,NORTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();

	//---お兄ちゃん
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(28,NORTH);
	evFrameWait(300);
	npDir(28,WEST);
	evFrameWait(300);
	mes.ReadDraw(4);

	evFrameWait(300);
	npDir(27,WEST);

	//---しゃーないな
	evFrameWait(2000);
	mes.ReadDraw(3);

	evFrameWait(700);
	npDir(32,WEST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(29,NORTH);
	evFrameWait(250);
	npDir(29,EAST);
	evFrameWait(250);
	npDir(27,NORTH);
	evFrameWait(300);
	npDir(27,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	//---サヴィアー出陣！！
	evFrameWait(250);
	npDir(29,SOUTH);
	evFrameWait(250);
	for(a = 0;a < 4;a ++){
		if(a == 3)
			npDir(27,SOUTH);
		if(a == 2)
			npDir(32,SOUTH);
		if(a < 2)
			npMove(29,0,1);
		else
			npMove(29,-1,0);
		evFrame();
	}
	evFrameWait(500);
	npDir(29,NORTH);
	evFrameWait(500);
	//---徹夜の～
	mes.ReadDraw();
	evFrameWait(500);

	npDir(29,WEST);
	evFrameWait(250);
	npDir(29,SOUTH);
	evFrameWait(250);
	for(a = 0;a < 8;a ++){
		if(a == 1)
			npDir(28,SOUTH);
		if(a == 3)
			npDir(31,SOUTH);
		npMove(29,0,1);
		evFrame();
	}
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);


	crmusicPlay(CRMUSIC_TOWN1);
	em->ReloadPattern();
	evReadObject(0,"TwPpl0m.acf");
	evReadObject(1,"TwPpl0w.acf");
	mcShow(1);
	mcDir(SOUTH);
	//---サヴィアー
	npPos(29,28,39);
	npDir(29,NORTH);
	evScene(0,28,38);

	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);

	npPos(29,0,0);
	npShow(29,0);
	evScene(0,28,38);

	mes.CloseMessage();

	for(a = 27;a <= 34;a ++){
		if(a == 30)
			continue;

		npPos(a,0,0);
		npShow(a,0);
	}

	//---ナック仲間になる
	{
		pPartyInfo->PartyMember[3] = 2;
		pPartyInfo->PartyMember[4] = 6;
		crcharaSetLevelStatus(3,8);
		CrCharacter *pChara = crcharaGetPartyMember(3);
		pChara->SetWeapon(0,88);
		pChara->SetWeapon(1,0);
		pChara->SetProtector(0,109);
		pChara->SetProtector(1,140);
		pChara->SetProtector(2,256);
		pChara->SetAccessory(0,203);
		pChara->SetAccessory(1,0);
		pChara->SetBattleFieldStartPos(6,1);
		pChara->SetLevelExperience();
		crcharaLoadFace(-1);
		crcharaCheckBattleFieldPos(3);

		a = 0;
		pChara->CharaInfo.MagicTable[a ++] = 1;
		pChara->AddMagicExperience(-10);
		pChara->CharaInfo.MagicTable[a ++] = 2;
		pChara->AddMagicExperience(-20);
		pChara->CharaInfo.MagicTable[a ++] = 47;
		pChara->AddMagicExperience(-15);
		pChara->CharaInfo.MagicTable[a ++] = 60;
		pChara->AddMagicExperience(-30);
		pChara->CharaInfo.MagicTable[a ++] = 12;
		pChara->AddMagicExperience(-20);
	}
	prtRecoveryAll();
	evSet(43,1);

	return 1;
}

//---フェイマル、クレスティーユ復活の話
CREVENTLONG1_API int creventFaymarru_Cresteaju(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	npPos(31,64,34);
	npPos(32,63,34);
	npPos(33,64,33);
	npPos(34,65,35);
	npDir(31,EAST);
	npDir(32,WEST);
	npDir(33,EAST);
	npDir(34,EAST);
	evScene(0,64,34);
	mes.OpenMessage("Faymarru.msg",102);

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);

	//---ディザ走り出す
	for(a = 0;a < 10;a ++){
		npMove(32,-1,0);
		if(a == 2)
			npDir(31,NORTH);
		if(a == 3)
			npDir(31,WEST);
		if(a == 1)
			npDir(33,NORTH);
		if(a == 3)
			npDir(33,WEST);
		if(a == 3)
			npDir(34,SOUTH);
		if(a == 4)
			npDir(34,WEST);

		evFrame();
	}

	mes.ReadDraw();
	evFrameWait(1000);

	npPos(31,47,34);
	npPos(32,47,50);
	npPos(33,47,36);
	npPos(34,45,35);
	npDir(31,EAST);
	npDir(32,SOUTH);
	npDir(33,EAST);
	npDir(34,EAST);
	evScene(0,47,50);

	evFrameWait(500);
	for(a = 0;a < 15;a ++){
		npMove(31,0,1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();
	for(a = 0;a < 16;a ++){
		if(a < 13)
			npMove(34,0,1);
		else if(a < 14)
			npMove(34,1,0);
		else
			npDir(34,SOUTH);
		if(a < 12)
			npMove(33,0,1);
		else if(a < 13)
			npMove(33,1,0);
		else if(a < 14)
			npMove(33,0,1);
		evFrame();
	}

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);

	//---ルナン動く
	npPos(36,47,35);
	npDir(36,SOUTH);

	npDir(31,WEST);
	evFrameWait(300);
	npDir(31,NORTH);
	evFrameWait(300);

	int old = ef->SetMoveSpeed(2);

/*	for(a = 0;a < 5;a ++){
		npMove(31,0,-1);
		evFrame();
	}
	for(a = 0;a < 5;a ++){
		mcMove(0,-1);
		evFrame();
	}*/
	//---ぶつかる
	for(a = 0;a < 8;a ++){
		if(a > 2){
			mcMove(0,-1);
			npMove(31,0,-1);
		}
		npMove(36,0,1);
		evFrame();
	}
	ef->SetMoveSpeed(old);
	crsoundPlay(CRSOUND_ATACK4);

	evFrameWait(100);
	mes.ReadDraw(4);
	evFrameWait(500);
	//---エターナル去る
	npDir(36,WEST);
	evFrameWait(300);
	for(a = 0;a < 10;a ++){
		npMove(36,-1,0);

		if(a < 4){
		} else if(a < 6)
			npMove(31,0,-1);
		else
			npDir(31,WEST);
		evFrame();
	}

	npDir(34,WEST);
	evFrameWait(250);
	//---サヴィアー来る
	for(a = 0;a < 7;a ++){
		if(a < 1)
			npMove(34,-1,0);
		else if(a < 6)
			npMove(34,0,-1);
		else
			npDir(34,WEST);
		evFrame();
	}

	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	npDir(32,WEST);
	evFrameWait(150);
	npDir(33,WEST);
	evFrameWait(150);
	npDir(32,NORTH);
	evFrameWait(150);
	npDir(33,NORTH);
	evFrameWait(150);

	for(a = 0;a < 8;a ++){
		if(a < 2){
		} else if(a < 3)
			npMove(33,-1,0);
		else if(a < 8)
			npMove(33,0,-1);
		else
			npMove(33,1,0);

		if(a < 7)
			npMove(32,0,-1);
		evFrame();
	}

	evFrameWait(350);
	//---アズグレイを見たいでごわす
	mes.ReadDraw(2);
	evFrameWait(500);
	npDir(32,WEST);
	evFrameWait(150);
	npDir(31,SOUTH);
	evFrameWait(150);
	npDir(32,SOUTH);
	evFrameWait(250);

	mes.ReadDraw(2);
	evFrameWait(500);
	//---なんかいった？
	npDir(32,WEST);
	evFrameWait(250);
	npDir(32,NORTH);
	evFrameWait(250);
	mes.ReadDraw(2);
	//---遺跡見ましょう
	evFrameWait(500);
	npDir(34,NORTH);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(34,0,-1);
		else
			npDir(34,EAST);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	npPos(36,63,31);
	npDir(36,EAST);
	npPos(37,64,31);
	npDir(37,WEST);

	npPos(31,55,34);
	npPos(32,54,34);
	npPos(33,53,34);
	npPos(34,54,33);
	evScene(0,65,34);

	evFrameWait(500);
	for(a = 0;a < 12;a ++){
		npMove(31,1,0);
		npMove(32,1,0);
		npMove(33,1,0);
		npMove(34,1,0);
		evFrame();
	}

	evFrameWait(100);
	mes.ReadDraw(2);
	evFrameWait(500);
	for(a = 0;a < 20;a ++){
		if(a < 3)
			npMove(36,0,1);
		else
			npMove(36,-1,0);

		if(a < 1)
			npMove(37,-1,0);
		else if(a < 5)
			npMove(37,0,1);
		else
			npMove(37,-1,0);

		if(a == 4)
			npDir(31,NORTH);
		if(a == 5)
			npDir(31,WEST);
		if(a == 5)
			npDir(32,NORTH);
		if(a == 6)
			npDir(32,WEST);
		if(a == 4)
			npDir(33,SOUTH);
		if(a == 5)
			npDir(33,WEST);
		if(a == 6)
			npDir(34,NORTH);
		if(a == 7)
			npDir(34,WEST);
		evFrame();
	}

	evFrameWait(100);
	mes.ReadDraw(2);
	evFrameWait(500);
	//---ナックの説明
	npDir(33,NORTH);
	evFrameWait(300);
	npDir(33,EAST);
	evFrameWait(300);
	mes.ReadDraw();

	//---サヴィアーナトる
	evFrameWait(600);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(31,NORTH);
	evFrameWait(300);
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(31,0,-1);
		else
			npDir(31,WEST);
		evFrame();
	}

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---気になるお年頃
	evFrameWait(500);
	npDir(34,SOUTH);
	evFrameWait(300);
	npDir(34,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(300);
	npDir(32,NORTH);
	evFrameWait(300);
	npDir(33,NORTH);
	evFrameWait(300);

	mes.ReadDraw();
	evFrameWait(500);
	npDir(34,SOUTH);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	npDir(34,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	mes.CloseMessage();
	mcShow(1);
	evSet(52,1);
	for(a = 31;a <= 37;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	mcDir(EAST);
	evScene(0,69,34);

	return 1;
}

//---地の遺跡
CREVENTLONG1_API int creventChinoIseki(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	npPos(0,7,15);
	npPos(1,9,18);
	npPos(2,8,16);
	npPos(3,8,17);
	npDir(0,NORTH);
	npDir(1,NORTH);
	npDir(2,EAST);
	npDir(3,WEST);
	evScene(3,8,17);
	mes.OpenMessage("ChinoIseki.msg",101);

	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(500);

	npPos(0,11,13);
	npDir(0,NORTH);
	npPos(1,8,14);
	npDir(1,NORTH);
	npPos(2,6,11);
	npDir(2,NORTH);
	npPos(3,12,9);
	npDir(3,NORTH);
	evScene(3,10,12);

	evFrameWait(1500);
	mes.ReadDraw();
	evFrameWait(1500);
	//---読めるのすくないよね
	mes.ReadDraw();
	evFrameWait(500);
	for(a = 0;a < 4;a ++){
		if(a < 3)
			npMove(3,1,0);
		else
			npDir(3,NORTH);
		evFrame();
	}
	evFrameWait(1500);

	//---てつだいぷりーず
	for(a = 0;a < 6;a ++){
		if(a < 2)
			npMove(0,0,1);
		else if(a < 5)
			npMove(0,-1,0);
		else
			npDir(0,NORTH);

		if(a == 3)
			npDir(1,EAST);
		if(a == 5)
			npDir(1,SOUTH);

		evFrame();
	}
	for(a = 0;a < 3;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	npDir(1,WEST);
	evFrameWait(300);
	npDir(1,NORTH);
	evFrameWait(300);

	for(a = 0;a < 6;a ++){
		if(a < 1)
			npMove(1,0,-1);
		else if(a < 3){
		} else if(a < 6)
			npMove(1,-1,0,0);

		if(a < 1)
			npMove(0,0,-1);
		else if(a < 2)
			npMove(0,1,0);
		else if(a < 3)
			npMove(0,0,-1);
		else if(a < 6)
			npMove(0,-1,0);

		evFrame();
	}
	evFrameWait(500);
	//---てつだって
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(1,NORTH);
	evFrameWait(500);
	npDir(0,NORTH);
	evFrameWait(300);
	npDir(0,EAST);
	evFrameWait(300);

	//---ルナン移動
	for(a = 0;a < 11;a ++){
		if(a < 10)
			npMove(0,1,0);
		else
			npDir(0,NORTH);
		evFrame();
	}
	evFrameWait(2000);
	//---サヴィアー移動
	for(a = 0;a < 7;a ++){
		if(a < 3)
			npMove(2,-1,0);
		else if(a < 5)
			npMove(2,0,1);
		else if(a < 6)
			npMove(2,-1,0);
		else
			npDir(2,NORTH);
		evFrame();
	}
	evFrameWait(1500);
	//---ろくなのねーなー
	mes.ReadDraw();
	evFrameWait(2000);
	mes.ReadDraw();

	//---時の人・ディザ
	evFrameWait(250);
	npDir(2,EAST);
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(800);
	npDir(1,WEST);
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
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	npPos(0,9,15);
	npDir(0,NORTH);
	npPos(1,8,14);
	npDir(1,NORTH);
	npPos(2,9,13);
	npDir(2,SOUTH);
	npPos(3,10,15);
	npDir(3,NORTH);
	evScene(3,10,16);

	evFrameWait(1000);
	mes.ReadDraw(7);
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(1000);
	mes.ReadDraw();
	//---あたしこわい
	evFrameWait(500);
	npDir(3,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw(3);
	evFrameWait(500);

	mes.CloseMessage();

	evSet(54,1);

	mcShow(1);
	mcDir(SOUTH);
	evMap(10,0,191,172);

	if(evGet(54) && evGet(56)){
		mes.FileMessage("MizunoIseki.msg",102);
	}

	return 1;
}

//---水の遺跡
CREVENTLONG1_API int creventMizunoIseki_Iriguchi(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	//---昔の話
	mcShow(0);
	npPos(3,13,4);
	npDir(3,NORTH);
	npPos(4,14,3);
	npDir(4,NORTH);
	npPos(5,15,3);
	npDir(5,WEST);
	npPos(6,15,5);
	npDir(6,NORTH);
	evScene(0,14,5);

	mes.OpenMessage("MizunoIseki.msg",100);

	evFrameWait(500);
	npMove(4,0,-1);
	evFrame();

	npDir(4,WEST);
	evFrameWait(500);
	npDir(4,NORTH);
	evFrameWait(750);

	//---なつかしいな
	mes.ReadDraw();
	evFrameWait(500);
	npDir(5,NORTH);
	evFrameWait(250);
	npMove(5,0,-1);
	evFrame();
	npDir(5,WEST);
	evFrameWait(500);
	mes.ReadDraw(3);

	evFrameWait(500);
	npMove(6,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(500);
	npDir(4,WEST);
	evFrameWait(250);
	npDir(4,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw(2);
	//---昔のこと覚えてないから
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(200);
	npDir(6,WEST);
	evFrameWait(200);
	npDir(5,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(5,WEST);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---ルナン話す
	evFrameWait(300);
	npDir(5,SOUTH);
	evFrameWait(800);
	npDir(3,WEST);
	evFrameWait(400);
	npDir(3,SOUTH);
	evFrameWait(400);
	mes.ReadDraw(2);

	evFrameWait(1000);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw(2);

	//---そうか・・・
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(1000);
	npDir(3,EAST);
	evFrameWait(300);
	npDir(3,NORTH);
	evFrameWait(300);
	mes.ReadDraw(2);
	evFrameWait(500);

	mes.CloseMessage();

	mcShow(1);
	for(a = 3;a <= 6;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	evScene(0,14,3);
	evSet(55,1);

	return 1;//11,23
}

//---水の遺跡
CREVENTLONG1_API int creventMizunoIseki(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	npPos(15,11,20);
	npDir(15,SOUTH);
	npPos(16,10,20);
	npDir(16,SOUTH);
	npPos(17,10,18);
	npDir(17,SOUTH);
	npPos(18,11,19);
	npDir(18,SOUTH);
	evScene(3,11,19);

	evFrameWait(500);
	for(a = 0;a < 4;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(1000);
	mes.OpenMessage("MizunoIseki.msg",101);
	mes.ReadDraw(3);
	evFrameWait(500);


	npPos(15,8,21);
	npDir(15,NORTH);
	npPos(16,7,24);
	npDir(16,NORTH);
	npPos(17,11,23);
	npDir(17,EAST);
	npPos(18,15,26);
	npDir(18,EAST);
	evScene(3,11,26);

	evFrameWait(1000);
	npMove(15,-1,0);
	evFrame();
	npDir(15,NORTH);
	evFrameWait(1000);
	for(a = 0;a < 6;a ++){
		if(a < 1)
			npMove(18,1,0);
		else if(a < 5)
			npMove(18,0,-1);
		else
			npDir(18,EAST);
		evFrame();
	}
	evFrameWait(1000);
	npMove(16,1,0);
	evFrame();
	npDir(16,NORTH);
	evFrameWait(2000);

	//---なにもねえな
	mes.ReadDraw();
	evFrameWait(1000);
	for(a = 0;a < 3;a ++){
		if(a < 2)
			npMove(15,1,0);
		else
			npDir(15,SOUTH);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(18,NORTH);
	evFrameWait(150);
	npDir(17,NORTH);
	evFrameWait(150);
	npDir(18,WEST);
	evFrameWait(150);
	npDir(17,WEST);
	evFrameWait(200);
	mes.ReadDraw();
	evFrameWait(500);

	npDir(15,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	mes.ReadDraw();

	//---ディザ動く
	evFrameWait(300);
	npDir(16,EAST);
	evFrameWait(300);
	npMove(16,1,0);
	evFrame();
	npDir(16,NORTH);
	evFrameWait(300);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);
	npDir(16,EAST);
	evFrameWait(500);
	//---なにいってるんだ？
	mes.ReadDraw(2);
	evFrameWait(500);

	evFrameWait(500);
	npDir(17,SOUTH);
	evFrameWait(250);
	npDir(17,EAST);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---不思議よね
	evFrameWait(1500);
	npDir(15,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	npDir(16,NORTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	npDir(17,SOUTH);
	evFrameWait(300);
	npDir(17,WEST);
	evFrameWait(300);
	mes.ReadDraw(4);
	evFrameWait(500);

	mes.CloseMessage();

	evSet(56,1);
	mcShow(1);
	mcDir(SOUTH);//--14,32
	evMap(10,0,172,200);

	if(evGet(54) && evGet(56)){
		mes.FileMessage("MizunoIseki.msg",102);
	}

	return 1;
}

//---フェイマル・アズグレイ到着
CREVENTLONG1_API int creventFeymarru_Asgray(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	npPos(38,60,34);
	npDir(38,EAST);

	//---えきすとらおっさん現る
	for(a = 0;a < 9;a ++){
		npMove(38,1,0);
		evFrame();
	}

	mes.OpenMessage("Faymarru.msg",103);

	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	mcDir(SOUTH);
	evFrameWait(250);
	mcMove(0,1);
	evFrame();
	evFrameWait(250);
	mcDir(WEST);
	evFrameWait(250);
	mcDir(NORTH);

	evFrameWait(250);

	//---えきすとらおっさんさる
	for(a = 0;a < 10;a ++){
		npMove(38,1,0);
		evFrame();
	}

	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(1000);

	//---物陰より見物
	npPos(31,63,29);
	npPos(32,64,29);
	npPos(33,63,28);
	npPos(34,64,28);
	for(a = 31;a <= 34;a ++){
		npDir(a,SOUTH);
	}
	mcShow(0);
	//---人々
	npPos(7,63,33);
	npDir(7,SOUTH);
	npPos(8,65,33);
	npDir(8,SOUTH);
	npPos(9,60,33);
	npDir(9,SOUTH);
	npPos(10,58,33);
	npDir(10,SOUTH);
	npPos(11,54,33);
	npDir(11,SOUTH);
	npPos(12,53,33);
	npDir(12,SOUTH);

	npPos(15,52,35);
	npDir(15,NORTH);
	npPos(16,55,35);
	npDir(16,NORTH);
	npPos(17,57,35);
	npDir(17,NORTH);
	npPos(18,58,35);
	npDir(18,NORTH);
	npPos(25,64,35);
	npDir(25,NORTH);

	evScene(0,60,34);
	evFrameWait(3000);

	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(3000);

	npPos(39,74,34);
	for(a = 0;a < 19;a ++){
		if(a < 18)
			npMove(39,-1,0);
		else
			npMove(39,0,-1);
		evFrame();
	}
	evFrameWait(250);
	npDir(39,EAST);
	evFrameWait(250);
	npDir(39,SOUTH);
	evFrameWait(250);

	//---ディザの問題発言
	mes.ReadDraw(3);
	evFrameWait(125);
	npDir(31,EAST);
	evFrameWait(125);
	//---どつき
	crsoundPlay(34);
	evFrameWait(250);
	npDir(31,SOUTH);
	evFrameWait(125);
	mes.ReadDraw(3);

	evFrameWait(3000);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---幹部登場！
	npPos(40,72,34);
	npPos(41,71,34);
	npPos(43,73,34);
	npPos(44,73,35);
	npPos(42,74,33);

	evReadObject(7,"Asgray.acf");
	evReadObject(0,"Rarfia.acf");
	evReadObject(1,"Follne.acf");

	for(a = 40;a <= 44;a ++){
		npDir(a,WEST);
	}
	for(a = 0;a < 10;a ++){
		mcMove(1,0);
		evFrame();
	}
	crmusicPlay(CRMUSIC_ETERNAL);
	evFrameWait(1000);
	for(a = 0;a < 10;a ++){
		mcMove(-1,0);
		evFrame();
	}

	//---歩いてくる
	for(a = 0;a < 7;a ++){
		for(b = 40;b <= 44;b ++){
			if(!(a >= 6 && (b == 44 || b == 42)))
				npMove(b,-1,0);
			else if(b == 44)
				npMove(b,0,-1);
			else if(b == 42)
				npMove(b,0,1);
		}
		evFrame();
		npDir(42,WEST);
		npDir(44,WEST);
		evFrameWait(400);
	}

	for(a = 0;a < 5;a ++){
		for(b = 40;b <= 44;b ++){
			if(!(a <= 1 && (b == 44 || b == 42)))
				npMove(b,-1,0);
		}
		evFrame();
		evFrameWait(400);
	}

	evFrameWait(100);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(41,NORTH);
	evFrameWait(500);
	npDir(41,WEST);
	evFrameWait(250);
	npDir(41,SOUTH);
	evFrameWait(500);
	npDir(41,WEST);
	evFrameWait(500);

	//---お疲れでございます
	mes.ReadDraw();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(100);

	for(a = 0;a < 6;a ++){
		for(b = 40;b <= 44;b ++){
			npMove(b,-1,0);
		}
		evFrame();
		evFrameWait(400);
	}
	//---フォールン！！
	evFrameWait(100);
	mes.ReadDraw();
	evFrameWait(200);
	npDir(32,WEST);
	evFrameWait(200);
	mes.ReadDraw();
	evFrameWait(200);

	for(a = 0;a < 17;a ++){
		if(a % 2){
			for(b = 40;b <= 44;b ++){
				npMove(b,-1,0);
			}
		}
		if(a < 1)
			npMove(31,-1,0);
		else if(a < 2)
			npMove(31,0,-1);
		else if(a < 8)
			npMove(31,-1,0);
		else if(a < 12)
			npMove(31,0,1);
		else if(a < 13)
			npMove(31,-1,0);
		else if(a < 15)
			npMove(31,0,1);

		if(a == 10)
			npDir(32,SOUTH);
		if(a == 15){
			npMove(11,0,1);
			npDir(31,WEST);
		}
		if(a == 16)
			npDir(11,EAST);
		evFrame();
	}
	//---飛び出し禁止！
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(1000);

	//---宿屋の二階
	crfieldChangeMap(26,1,1);
	npPos(0,13,5);
	npDir(0,EAST);
	npPos(1,14,4);
	npDir(1,SOUTH);
	npPos(2,15,5);
	npDir(2,WEST);
	npPos(3,14,6);
	npDir(3,NORTH);
	evScene(1,14,6);
	crmusicPlay(CRMUSIC_TOWNETERNAL);

	evFrameWait(1000);
	mes.ReadDraw(3);
	//---暴走気味のルナン
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(250);
	mes.ReadDraw(2);
	//---出ていこうとするルナン
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);
	npMove(0,0,1);
	evFrame();
	npDir(3,WEST);
	evFrameWait(250);

	//---頭冷やせば？
	mes.ReadDraw();
	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);

	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---お兄ちゃん方法は？
	npDir(2,NORTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(250);

	mes.ReadDraw(2);

	//---シンディ来る
	npPos(4,2,11);
	for(a = 0;a < 12;a ++){
		if(a < 11)
			npMove(4,1,0);
		else
			npDir(4,NORTH);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(250);
	npDir(2,SOUTH);
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(300);
	npDir(0,EAST);
	evFrameWait(300);
	npDir(0,SOUTH);

	evFrameWait(1000);

	//---シンディにいきさつ話す
	npPos(0,13,5);
	npDir(0,EAST);
	npDir(2,WEST);
	npDir(3,NORTH);
	npPos(4,13,6);
	npDir(4,EAST);
	evScene(1,14,6);

	evFrameWait(500);
	mes.ReadDraw(2);
	//---シンディなとる
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);
	//---ほんと！？
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(250);

	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(300);
	mes.ReadDraw(4);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---夜！
	crmusicFadeOut();
	evFadeOut(2000);
	crfieldPaletteChange(PALETTE_NIGHT);
	crfieldChangeScene(0,15,41);
	npPos(31,15,40);
	npDir(31,WEST);
	npPos(32,26,42);
	npDir(32,WEST);
	npPos(16,0,0);
	npShow(16,0);

	et->Delay2(2000);
	crmusicStop();
	crsoundPlay(CRSOUND_WAVE1,1);
	et->Delay2(3000);
	evFieldNoFlip(0,1);
	evFadeIn(2000);
//	evScene(0,15,41);

	evFrameWait(1000);

	for(a = 0;a < 4;a ++){
		npMove(32,-1,0);
		evFrame();
	}
	evFrameWait(1000);
	for(a = 0;a < 8;a ++){
		if(a < 4)
			npMove(32,-1,0);
		else if(a < 7)
			npMove(32,0,-1);
		else
			npMove(32,-1,0);
		evFrame();
	}
	evFrameWait(500);

	//---こないなとこにいたんかえ？
	mes.ReadDraw();
	evFrameWait(500);
	for(a = 0;a < 2;a ++){
		npMove(32,-1,0);
		evFrame();
	}

	evFrameWait(500);
	npDir(32,SOUTH);
	evFrameWait(500);

//	evFrameWait(500);
//	mes.ReadDraw();

	evFrameWait(500);
	npDir(31,NORTH);
	crmusicPlay(CRMUSIC_SEEK);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(1000);

	mes.ReadDraw();
	evFrameWait(500);
	evFrameWait(500);
	//---あれ？
	mes.ReadDraw();
	evFrameWait(500);

	//---カンパイ！
	npDir(32,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(32,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---父さん以外の人に
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(700);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(32,WEST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);

	npDir(31,WEST);
	evFrameWait(3000);

	//---フェイマルの感想
	mes.ReadDraw(2);
	evFrameWait(2000);
	mes.ReadDraw(2);
	evFrameWait(500);
	npDir(32,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(32,WEST);
	evFrameWait(2000);

	//---クレイシヴのこと
	npDir(31,NORTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(32,SOUTH);
	evFrameWait(500);

	mes.ReadDraw(6);
	evFrameWait(800);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---飲み会
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(500);
	npDir(32,EAST);
	evFrameWait(250);
	npDir(32,NORTH);
	evFrameWait(250);
	mes.ReadDraw(3);

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	//---ディザ兄さん急行
	for(a = 0;a < 15;a ++){
		if(a < 3)
			npMove(32,0,-1);
		else if(a < 6)
			npMove(32,1,0);
		else
			npMove(32,0,-1);
		evFrame();
	}
	mes.ReadDraw();
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(1000);
	evFadeOut(2000);
	crsoundStop(CRSOUND_WAVE1);

	prtRecoveryAll();
	crfieldChangeMap(26,0,1);
	crfieldChangeScene(0,58,42);

	npPos(31,58,41);
	npDir(31,NORTH);
	npPos(32,57,41);
	npDir(32,WEST);
	npPos(33,58,40);
	npDir(33,SOUTH);
	npPos(34,57,39);
	npDir(34,SOUTH);

//	mcDir(SOUTH);
//	mcShow(1);

	evFieldNoFlip(0,1);
	evFadeIn();

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(31,WEST);
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);
	npDir(31,NORTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	mes.CloseMessage();

	npDelete(31);
	npDelete(32);
	npDelete(33);
	npDelete(34);

	mcShow(1);
	mcDir(NORTH);
	evScene(0,58,41);

	evSet(57,1);

	return 1;
}


//---フェイマル、会議を盗み聞き
CREVENTLONG1_API int creventFaymarru_EternalTatemono(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	evFrameWait(500);
	mcDir(SOUTH);
	evFrameWait(1000);

	mes.OpenMessage("Faymarru.msg",105);

	mes.ReadDraw(2);
	evFrameWait(500);

	//---会議
	mcShow(0);
	evScene(4,11,16);
	crmusicPlay(CRMUSIC_ETERNAL);
	evFrameWait(1500);
	mes.ReadDraw();

	//---ラーフィア
	evFrameWait(500);
	npDir(6,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(6,NORTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---ご苦労じゃった
	evFrameWait(500);
	mes.ReadDraw();

	//---よんきゅうべりーまっち
	evFrameWait(500);
	npDir(5,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(5,SOUTH);

	//---おちつけ
	evFrameWait(500);
	mes.ReadDraw(2);

	//---アズグレイ
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(6,EAST);
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(300);
	npDir(6,NORTH);
	evFrameWait(400);
	npDir(7,EAST);
	evFrameWait(600);
	//---エドの兵器開発
	mes.ReadDraw(2);
	evFrameWait(300);
	npDir(7,SOUTH);
	evFrameWait(300);

	mes.ReadDraw();
	evFrameWait(1000);

	//---わかった出そう
	mes.ReadDraw();
	evFrameWait(500);

	mes.ReadDraw(2);

	//---場所は特定できてまっちょ
	evFrameWait(300);
	npDir(5,EAST);
	evFrameWait(300);
	mes.ReadDraw(2);
	evFrameWait(300);
	npDir(5,SOUTH);
	evFrameWait(300);

	//---ルナン
	mes.ReadDraw();

	evFrameWait(300);
	npDir(6,EAST);
	evFrameWait(300);
	mes.ReadDraw(2);

	evFrameWait(300);
	npDir(6,NORTH);
	evFrameWait(300);

	mes.ReadDraw(2);

	//---アズグレイ
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(1000);
	mes.ReadDraw(2);

	//---準備おっけー
	evFrameWait(500);
	npDir(6,EAST);
	evFrameWait(300);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(4,NORTH);
	evFrameWait(500);
	npDir(4,EAST);
	evFrameWait(500);
	npMove(4,1,0);
	evFrame();
	evFrameWait(500);
	npDir(4,SOUTH);
	evFrameWait(500);
	npDir(4,WEST);
	evFrameWait(500);

	mes.ReadDraw(2);

	//---こら！
	evFrameWait(500);
	mes.ReadDraw();

	//---ルナン乱入！
	evFrameWait(250);
	em->Put(14,10,2,1024);

	npPos(0,14,9);
	npDir(0,SOUTH);
	npPos(1,14,9);
	npDir(1,SOUTH);
	evFrameWait(250);

	for(a = 0;a < 5;a ++){
		if(a == 1)
			npDir(5,EAST);
		if(a == 2)
			npDir(6,EAST);
		if(a == 4)
			npDir(7,EAST);

		if(a < 3)
			npMove(0,0,1);
		if(a > 2 && a < 5)
			npMove(1,0,1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(2);

	//---エターナルの人間でもないね
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(1000);
	npDir(4,NORTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(300);
	npDir(0,WEST);
	evFrameWait(300);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	//---そうか
	evFrameWait(1000);
	mes.ReadDraw(3);

	//---警備よこしな！
	evFrameWait(500);
	npDir(6,EAST);
	evFrameWait(300);
	npDir(6,SOUTH);
	evFrameWait(300);

	mes.ReadDraw();


	evFrameWait(300);
	npDir(0,SOUTH);
	evFrameWait(300);
	mes.ReadDraw(4);

	npPos(2,15,9);
	npDir(2,WEST);
	npPos(3,16,8);
	npDir(3,WEST);

	for(a = 0;a < 3;a ++){
		mcMove(0,-1);
		evFrame();
	}
	for(a = 0;a < 3;a ++){
		npMove(0,0,-1,0);
		npMove(1,0,-1);
		evFrame();
	}

	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	//---引き返すぞ！
	mes.ReadDraw();

	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(150);
	npDir(3,NORTH);
	evFrameWait(150);
	npDir(2,EAST);
	evFrameWait(150);
	npDir(3,EAST);
	evFrameWait(150);
	for(a = 0;a < 8;a ++){
		if(a > 1)
			npMove(0,1,0,0);
		if(a < 1)
			npMove(1,1,0);
		else if(a < 2)
			npMove(1,0,1);
		else
			npMove(1,1,0);

		npMove(2,1,0);
		npMove(3,1,0);
		evFrame();
	}

	mcDir(WEST);
	evScene(3,13,9);
	evFrameWait(250);
	npPos(0,12,17);
	npDir(0,NORTH);
	npPos(1,13,17);
	npDir(1,NORTH);

	npPos(3,20,9);
	npDir(3,WEST);
	npPos(2,21,9);
	npDir(2,EAST);
	npPos(4,21,8);
	npDir(4,WEST);
	npPos(5,22,8);
	npDir(5,WEST);
	for(a = 0;a < 8;a ++){
		npMove(2,-1,0,0);
		npMove(3,-1,0);
		npMove(4,-1,0);
		npMove(5,-1,0);

		if(a > 1){
			npMove(0,0,-1);
			npMove(1,0,-1);
		}
		evFrame();
	}
	evFrameWait(100);
	npDir(3,SOUTH);
	evFrameWait(250);
	npDir(4,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(100);

	//---バトル
	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.Music = CRMUSIC_BOSSBATTLE1;
	BattleInfo.Enemy[0].Enemy = 53;
	BattleInfo.Enemy[0].x = 5;
	BattleInfo.Enemy[0].y = 8;
	BattleInfo.Enemy[1].Enemy = 54;
	BattleInfo.Enemy[1].x = 8;
	BattleInfo.Enemy[1].y = 6;
	BattleInfo.Enemy[2].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	evField(0,1);
	npPos(0,0,0);
	npShow(0,0);
	npPos(1,0,0);
	npShow(1,0);
	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}

	npDir(3,WEST);
	evFrameWait(150);
	npDir(4,WEST);
	evFrameWait(150);
	npDir(3,NORTH);
	evFrameWait(150);
	npDir(4,NORTH);
	evFrameWait(150);

	for(a = 0;a < 14;a ++){
		if(a < 1)
			npMove(2,-1,0);
		else
			npMove(2,0,-1);
		npMove(3,0,-1);
		if(a > 2)
			npMove(4,0,-1);
		if(a < 3){
		} else if(a < 4)
			npMove(5,-1,0);
		else
			npMove(5,0,-1);
		evFrame();
	}

	crmusicFadeOut();
	evFrameWait(500);
	evScene(5,10,10);

	evFrameWait(500);
	mes.ReadDraw(5);
	crmusicStop();
	evFrameWait(1000);

	//---宿屋
	crfieldChangeScene(1,13,7);
	npPos(0,14,4);
	npDir(0,SOUTH);
	npPos(1,10,4);
	npDir(1,EAST);
	npPos(2,11,4);
	npDir(2,WEST);
	npPos(3,15,7);
	npDir(3,WEST);
	evScene(1,14,7);

	evFrameWait(1000);
	mes.ReadDraw(3);

	evFrameWait(500);
	npDir(1,SOUTH);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(1,0,1);
		if(a == 1)
			npDir(2,SOUTH);
		evFrame();
	}
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);

	mes.ReadDraw();

	//---ごめん
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(500);
	for(a = 0;a < 4;a ++){
		npMove(1,1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);

	mes.ReadDraw();

	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(2,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(1000);

	//---フェイマル入り口
	crfieldChangeScene(0,69,35);
	for(a = 0;a < 100;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	npPos(31,58,34);
	npDir(31,EAST);
	npPos(32,57,33);
	npDir(32,EAST);
	npPos(33,56,33);
	npDir(33,EAST);
	npPos(34,56,34);
	npDir(34,EAST);
	npPos(35,54,34);
	npDir(35,EAST);
	evScene(0,69,35);
	evFrameWait(1000);

	for(a = 0;a < 12;a ++){
		npMove(31,1,0);
		npMove(32,1,0);
		npMove(33,1,0);
		npMove(34,1,0);
		npMove(35,1,0);
		evFrame();
	}
	evFrameWait(200);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(31,NORTH);
	evFrameWait(100);
	npDir(32,SOUTH);
	evFrameWait(100);
	npDir(33,SOUTH);
	evFrameWait(100);
	npDir(34,NORTH);
	evFrameWait(100);
	npDir(31,WEST);
	evFrameWait(100);
	npDir(32,WEST);
	evFrameWait(100);
	npDir(33,WEST);
	evFrameWait(100);
	npDir(34,WEST);
	evFrameWait(250);

	mes.ReadDraw(2);

	//---残る
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(1000);
	npDir(35,SOUTH);
	evFrameWait(500);
	npDir(35,WEST);
	evFrameWait(500);
	//---シンディ去る
	for(a = 0;a < 10;a ++){
		npMove(35,-1,0);
		evFrame();
	}
	evFrameWait(3000);
	mes.ReadDraw(2);
	evFrameWait(500);
	npDir(32,SOUTH);
	evFrameWait(250);
	npDir(33,SOUTH);
	evFrameWait(250);
	npDir(33,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(31,NORTH);
	evFrameWait(500);
	mes.ReadDraw();
	//---出ていく
	
	evFrameWait(500);
	npDir(31,EAST);
	evFrameWait(250);
	npDir(32,EAST);
	evFrameWait(250);
	for(a = 0;a < 18;a ++){
		npMove(31,1,0);
		npMove(32,1,0);
		if(a > 0)
			npMove(33,1,0);
		if(a < 3)
			npDir(34,WEST);
		else if(a == 3)
			npDir(34,NORTH);
		else if(a == 4)
			npDir(34,EAST);
		else
			npMove(34,1,0);
		evFrame();
	}

	mes.CloseMessage();
	mcShow(1);
	evSet(58,1);

	prtRecoveryAll();
	mcDir(SOUTH);
	evMap(10,0,184,220);

	return 1;
}

//---クレスフィールド高地・精神体
CREVENTLONG1_API int creventCresMount_Seishintai(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	mcDir(EAST);
	crfieldChangeScene(3,9,15);
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
	evScene(3,9,15);

	evFrameWait(1000);
	for(a = 0;a < 1;a ++){
		npMove(3,1,0);
		evFrame();
	}
	evFrameWait(500);

	mes.OpenMessage("CresfieldMount.msg",100);

	mes.ReadDraw(2);
	evFrameWait(500);

	for(a = 0;a < 3;a ++){
		mcMove(1,0);
		evFrame();
	}
	for(a = 0;a < 3;a ++){
		npMove(3,1,0);
		evFrame();
	}
	npDir(3,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---ガイコツ！
	for(a = 0;a < 4;a ++){
		mcMove(0,-1);
		evFrame();
	}

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	for(a = 0;a < 4;a ++){
		npMove(7,0,1);
		evFrameWait(750);
	}
	evFrameWait(250);
	for(a = 0;a < 4;a ++){
		mcMove(0,1);
		evFrame();
	}

	//---こっちへ来るわ
	mes.ReadDraw();
	evFrameWait(500);
	for(a = 0;a < 3;a ++){
		npMove(7,0,1);
		evFrame();
	}
	//---バトル
	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.Music = CRMUSIC_BOSSBATTLE1;
	BattleInfo.Enemy[0].Enemy = 61;
	BattleInfo.Enemy[0].x = 5;
	BattleInfo.Enemy[0].y = 6;
	BattleInfo.Enemy[1].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	evField(0,1);
	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}

	//---
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

	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(300);
	npDir(3,SOUTH);
	evFrameWait(300);
	mes.ReadDraw();

	evFrameWait(250);
	//---ガイコツ動く
	npMove(7,0,1);
	evFrame();
	mes.ReadDraw();
	evFrameWait(250);

	evFill(ep->MakeRGB(64,64,255));
	crsoundPlay(CRSOUND_ATACK1);
	ew->Flip();
	npPos(7,0,0);
	npShow(7,0);
	evWait(50,1);
	evFieldNoFlip(0,1);
	evFadeIn(250);
	evFrameWait(1500);

	//---なんだったの
	npDir(3,WEST);
	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(700);
	npDir(3,WEST);
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npMove(4,0,-1);
	evFrame();
	npDir(4,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	npMove(6,0,-1);
	evFrame();
	evFrameWait(350);
	mes.ReadDraw();
	evFrameWait(500);

	for(a = 0;a < 1;a ++){
		npMove(5,0,-1);
		evFrame();
	}
	npDir(5,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	evFrameWait(2000);
	mes.ReadDraw(5);
	evFrameWait(500);

	mes.CloseMessage();

	evSet(59,1);
	mcShow(1);
	for(a = 3;a <= 10;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	evScene(3,12,16);

	return 1;
}

//---クレスフィールド高地・ライゼル！
CREVENTLONG1_API int creventCresMount_Lizel(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	npPos(3,28,15);
	npDir(3,NORTH);
	npPos(4,26,15);
	npDir(4,NORTH);
	npPos(5,29,15);
	npDir(5,NORTH);
	npPos(6,25,14);
	npDir(6,NORTH);

	npPos(8,37,16);
	npDir(8,NORTH);
	npPos(9,38,16);
	npDir(9,NORTH);

	evScene(3,28,16);

	evFrameWait(1000);
	mes.OpenMessage("CresfieldMount.msg",101);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(3,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);

	for(a = 0;a < 15;a ++){
		npMove(8,-1,0);
		npMove(9,-1,0);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(8,SOUTH);
	evFrameWait(250);
	npDir(8,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	//---振り向く
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(150);
	npDir(4,WEST);
	evFrameWait(150);
	npDir(5,WEST);
	evFrameWait(150);
	npDir(6,WEST);
	evFrameWait(250);
	mes.ReadDraw(3);

	evFrameWait(1200);
	//---殺人的ギャグってあれだよ
	mes.ReadDraw(2);
	evFrameWait(500);
	npDir(8,SOUTH);
	evFrameWait(250);

	for(a = 0;a < 10;a ++){
		if(a < 2)
			npMove(8,0,1);
		else
			npMove(8,-1,0);

		if(a < 1)
			npMove(9,-1,0);
		else if(a < 3)
			npMove(9,0,1);
		else
			npMove(9,-1,0);
		evFrame();
	}

	//---沈黙
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(1000);
	npDir(5,SOUTH);
	evFrameWait(250);
	for(a = 0;a < 3;a ++){
		if(a < 1)
			npMove(5,0,1);
		else
			npMove(5,-1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(5,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw(3);
	evFrameWait(2000);
	//---ややっ
	mes.ReadDraw();
	evFrameWait(500);

	npPos(11,39,15);
	npDir(11,WEST);
	npPos(2,40,13);
	for(a = 0;a < 10;a ++){
		mcMove(1,0);
		evFrame();
	}
	crmusicPlay(CRMUSIC_LIZEL);
	npDir(3,EAST);
	npDir(4,EAST);
	npDir(5,EAST);
	npDir(6,EAST);
	evFrameWait(2000);
	for(a = 0;a < 10;a ++){
		mcMove(-1,0);
		evFrame();
	}
	evFrameWait(500);
	//---ライゼル来る
	for(a = 0;a < 8;a ++){
		npMove(11,-1,0);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw(6);
	//---ナックです
	evFrameWait(500);
	for(a = 0;a < 2;a ++){
		npMove(5,1,0);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);
	npMove(4,1,0);
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	//---ギャグ
	mes.ReadDraw(4);
	evFrameWait(200);
	npDir(11,NORTH);
	evFrameWait(200);
	npDir(11,EAST);
	evFrameWait(200);
	npDir(11,SOUTH);
	evFrameWait(200);
	npDir(11,WEST);
	evFrameWait(200);

	mes.ReadDraw();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	mes.ReadDraw();

	//---どかーんっ
	crmusicStop();
	mes.ReadDraw();
	crsoundPlay(CRSOUND_HYURURIRA);
	evFrameWait(4000);
	crmusicRestoreStream(0);
	mes.ReadDraw(3);

	//---ディザ落下危機
	evFrameWait(250);
	npDir(4,NORTH);
	evFrameWait(500);
	npDir(4,EAST);
	evFrameWait(250);

	mes.ReadDraw();
	evFrameWait(250);

	//---ナックなんて
	npMove(3,1,0);
	evFrame();
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---なにごと？
	npDir(4,SOUTH);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(4,0,1);
		else
			npMove(4,1,0);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(2);

	//---サヴィアーのんなあほな
	npDir(6,SOUTH);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(6,0,1);
		else
			npMove(6,1,0);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(250);
	mes.ReadDraw(2);

	//---弟子にしてください！
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(5,1,0);
		else
			npMove(5,0,-1);
		evFrame();
	}
	npDir(3,EAST);
	evFrameWait(250);
	npDir(5,EAST);
	evFrameWait(250);
	mes.ReadDraw(3);

	evFrameWait(500);
	mes.ReadDraw(2);

	//---やめとけよ
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(4,1,0);
		evFrame();
	}
	npDir(4,NORTH);
	evFrameWait(250);
	mes.ReadDraw(1);
	evFrameWait(250);
	npDir(5,SOUTH);
	evFrameWait(250);

	//---やだ！
	mes.ReadDraw();
	evFrameWait(250);
	npDir(5,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	//---くぅー
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(500);
	npDir(3,SOUTH);
	evFrameWait(250);
	npMove(3,0,1);
	evFrame();
	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(500);
	npPos(2,40,13);

	npPos(3,37,16);
	npDir(3,SOUTH);
	npPos(4,36,14);
	npDir(4,SOUTH);
	npPos(5,38,15);
	npDir(5,SOUTH);
	npPos(6,35,16);
	npDir(6,SOUTH);
	npPos(11,37,17);
	npDir(11,NORTH);

	evScene(3,38,17);
	evFrameWait(500);
	mes.ReadDraw(6);
	evFrameWait(500);

	mes.CloseMessage();

	mcShow(1);
	mcDir(SOUTH);
	evSet(60,1);
	for(a = 3;a <= 11;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	crmusicPlay(CRMUSIC_FIELD1);
	evScene(3,38,17);

	//---ライゼル再び仲間になる
	{
		pPartyInfo->PartyMember[4] = 5;
		int level = crcharaGetPartyMember(0)->GetLevel();
		CrCharacter *pChara = crcharaGetPartyMember(4);

		if(level > pChara->GetLevel()){
			//---ルナンの方が高かったらレベルセット
			crcharaSetLevelStatus(4,level);
			pChara->SetLevelExperience();
		}
		pChara->SetWeapon(0,86);
		pChara->SetWeapon(1,0);
		pChara->SetProtector(0,134);
		pChara->SetProtector(1,168);
		pChara->SetProtector(2,255);
//		pChara->SetAccessory(0,203);
//		pChara->SetAccessory(1,0);
		pChara->SetBattleFieldStartPos(4,4);
		crcharaLoadFace(-1);
		crcharaCheckBattleFieldPos(4);
	}
	prtRecovery(4);

	return 1;
}


//---クレスフィールドへ帰る
CREVENTLONG1_API int creventCresfield_Return(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	crfieldChangeMap(32,0,1);
	npPos(18,37,6);
	npDir(18,SOUTH);
	npPos(19,38,5);
	npDir(19,SOUTH);
	npPos(20,36,4);
	npDir(20,SOUTH);
	npPos(21,35,5);
	npDir(21,SOUTH);
	npPos(22,39,5);
	npDir(22,SOUTH);

	evScene(0,37,9);

	evFrameWait(1000);
	mes.OpenMessage("Cresfield.msg",100);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);
	//---笑いのレベル
	evFrameWait(250);
	npDir(22,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	//---酒場に集合
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(18,EAST);
	evFrameWait(250);
	npDir(18,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);
	//---ナック、サヴィアー
	for(a = 0;a < 22;a ++){
		npMove(21,0,1);
		if(a)
			npMove(20,0,1);

		if(a == 7)
			npDir(22,SOUTH);
		if(a < 8){
		} else if(a < 11)
			npMove(22,0,1);
		else if(a < 12)
			npMove(22,-1,0);
		else
			npMove(22,0,1);

		if(a == 5)
			npDir(18,WEST);
		if(a == 6)
			npDir(18,SOUTH);
		evFrame();
	}
	for(a = 18;a <= 22;a ++){
		npPos(a,0,0);
	}

	mes.CloseMessage();

	npPos(18,44,28);
	npDir(18,EAST);
	npPos(19,43,27);
	npDir(19,NORTH);
	evScene(0,44,30);
	evFrameWait(1000);
	mes.OpenMessage("Cresfield.msg",101);
	mes.ReadDraw();
	mes.CloseMessage();
	evFrameWait(1000);

	npPos(18,36,43);
	npDir(18,SOUTH);
	npPos(19,37,43);
	npDir(19,SOUTH);
	evScene(0,37,48);
	evFrameWait(1000);
	mes.OpenMessage("Cresfield.msg",102);
	mes.ReadDraw(3);
	evFrameWait(1000);
	//---みんなどうしてるんだろ？
	npDir(18,WEST);
	evFrameWait(500);
	npDir(18,NORTH);
	evFrameWait(500);
	npDir(19,WEST);
	evFrameWait(500);
	mes.ReadDraw(2);
	mes.CloseMessage();
	evFrameWait(1000);

	mcShow(1);
	mcDir(NORTH);
	evSet(63,1);

	for(a = 18;a <= 22;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	evScene(0,37,43);

	pPartyInfo->PartyMember[2] = -1;
	pPartyInfo->PartyMember[3] = -1;
	pPartyInfo->PartyMember[4] = -1;
	crcharaLoadFace(-1);
	//---211 - 220

	return 1;
}

//---ルナンの家の前
CREVENTLONG1_API int creventCresfield_LunarnsHome(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	npPos(18,17,34);
	npDir(18,NORTH);
	npPos(19,18,34);
	npDir(19,WEST);
	evScene(0,18,34);

	evFrameWait(1000);
	mes.OpenMessage("Cresfield.msg",103);
	mes.ReadDraw();
	evFrameWait(1500);
	//---ここがわたしのいえ
	mes.ReadDraw();
	evFrameWait(500);
	npDir(19,NORTH);
	evFrameWait(1000);
	mes.ReadDraw();
	//---ん？焦げあと？
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);
	npDir(18,EAST);
	evFrameWait(500);
	mes.ReadDraw(3);

	//---前のことは覚えてないの？
	evFrameWait(500);
	npDir(18,NORTH);
	evFrameWait(800);
	npDir(19,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(1000);
	mes.ReadDraw(3);
	evFrameWait(1000);
	mes.ReadDraw(2);
	//---ハゲます
	evFrameWait(500);
	npDir(18,EAST);
	evFrameWait(500);
	mes.ReadDraw(4);
	evFrameWait(500);
	mes.CloseMessage();

	mcShow(1);
	npPos(18,0,0);
	npShow(18,0);
	npPos(19,0,0);
	npShow(19,0);
	evScene(0,18,34);
	evSet(62,1);

	return 1;
}

//---クレスフィールド酒場
CREVENTLONG1_API int creventCresfield_Sakaba(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	crfieldChangeScene(4,8,6);
	npPos(5,5,5);
	npDir(5,EAST);
	npPos(6,6,4);
	npDir(6,SOUTH);
	npPos(7,8,5);
	npDir(7,WEST);
	evScene(4,8,6);

	evFrameWait(1000);

	npPos(3,12,2);
	npPos(4,12,2);

	//---ルナンとディザがくる
	npDir(3,SOUTH);
	npMove(3,0,1);
	evFrame();
	npDir(4,SOUTH);
	npMove(3,0,1);
	npMove(4,0,1);
	evFrame();
	npMove(4,0,1);
	npMove(3,-1,0);
	evFrame();
	npDir(7,SOUTH);
	npMove(4,0,1);
	evFrame();
	npDir(4,WEST);
	evFrameWait(250);
	npDir(7,EAST);
	evFrameWait(250);
	npDir(6,EAST);
	evFrameWait(250);

	mes.OpenMessage("Cresfield.msg",108);
	mes.ReadDraw();
	evFrameWait(250);
	for(a = 0;a < 8;a ++){
		if(a < 4)
			npMove(3,-1,0);
		else
			npDir(3,SOUTH);
		if(a < 1)
			npMove(4,0,1);
		else if(a < 6)
			npMove(4,-1,0);
		else
			npDir(4,NORTH);

		if(a == 3)
			npDir(6,SOUTH);
		if(a == 5)
			npDir(7,SOUTH);
		if(a == 6)
			npDir(7,WEST);

		evFrame();
	}
	evFrameWait(500);

	mes.ReadDraw(4);
	evFrameWait(500);
	mes.ReadDraw(2);
	//---あ、でもルナンさんが・・・
	evFrameWait(250);
	npDir(6,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---わかりました
	evFrameWait(250);
	npDir(6,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);

	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---許可書持ってるから
	evFrameWait(250);
	npDir(6,EAST);
	evFrameWait(250);
	mes.ReadDraw(4);
	//---いっつあこせい！！
	evFrameWait(250);
	npDir(6,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	mes.CloseMessage();

	for(a = 3;a <= 7;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	mcShow(1);
	mcDir(SOUTH);
	evSet(61,1);
	evScene(4,8,5);

	pPartyInfo->PartyMember[2] = 3;
	pPartyInfo->PartyMember[3] = 2;
	pPartyInfo->PartyMember[4] = 5;
	//---バトル位置補正
	for(a = 2;a <= 4;a ++){
		crcharaCheckBattleFieldPos(a);
	}

	crcharaLoadFace(-1);

	return 1;
}

//---クレスフィールド図書館
CREVENTLONG1_API int creventCresfieldLibrary(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	npPos(4,14,18);
	npPos(5,11,19);
	npPos(6,12,17);
	npPos(7,13,17);
	npPos(8,16,19);
	for(a = 4;a <= 8;a ++){
		npDir(a,NORTH);
	}

	evScene(0,13,18);

	evFrameWait(1000);

	mes.OpenMessage("Library.msg",101);
	mes.ReadDraw(2);

	evFrameWait(500);
	npMove(7,0,-1);
	evFrame();
	evFrameWait(250);
	npDir(7,EAST);
	evFrameWait(250);
	npDir(7,SOUTH);
	evFrameWait(250);

	//---探してみましょう
	mes.ReadDraw(2);
	evFrameWait(1000);

	npPos(7,19,20);
	npDir(7,SOUTH);
	npPos(4,19,22);
	npDir(4,NORTH);
	npPos(5,17,22);
	npDir(5,NORTH);
	npPos(6,18,22);
	npDir(6,NORTH);
	npPos(8,20,22);
	npDir(8,NORTH);
	evScene(0,19,23);

	evFrameWait(1000);
	mes.ReadDraw(6);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw(4);

	//---そうだ、るなん
	evFrameWait(500);
	npDir(6,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(4,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(4);
	evFrameWait(500);

	npDir(5,WEST);
	evFrameWait(250);
	npDir(6,NORTH);
	evFrameWait(250);
	npDir(7,WEST);
	evFrameWait(250);
	npDir(6,WEST);
	evFrameWait(250);
	npDir(8,WEST);
	evFrameWait(250);
	npDir(8,SOUTH);
	evFrameWait(250);

	for(a = 0;a < 18;a ++){
		if(a < 3)
			npMove(5,-1,0);
		else
			npMove(5,0,1);

		if(a < 1)
			npMove(8,0,1);
		else if(a < 7)
			npMove(8,-1,0);
		else
			npMove(8,0,1);

		if(a < 6){
		} else if(a < 10)
			npMove(6,-1,0);
		else if(a < 11)
			npMove(6,0,1);
		else if(a == 11)
			npDir(6,EAST);


		if(a < 1){
		} else if(a < 6)
			npMove(7,-1,0);
		else
			npMove(7,0,1);

		evFrame();
	}
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	for(a = 0;a < 20;a ++){
		npMove(6,0,1);

		if(a < 15){
		} else if(a < 20)
			npMove(4,-1,0);
		else
			npMove(4,0,1);
		evFrame();
	}
	evFrameWait(100);
	//---るなんのこころ
	evScene(1,15,15);
	mes.ReadDraw(3);
	evFrameWait(500);
	evScene(0,19,23);
	evFrameWait(500);
	npDir(4,SOUTH);
	evFrameWait(500);
	//---考え過ぎよね
	mes.ReadDraw();
	evFrameWait(500);

	for(a = 0;a < 10;a ++){
		npMove(4,0,1);
		evFrame();
	}

	mes.CloseMessage();

	evSet(64,1);
	mcShow(1);
	mcDir(SOUTH);
	evMap(10,0,232,169);

	return 1;
}

//---復活祭の知らせ
CREVENTLONG1_API int creventCresfield_FukkatusaiShirase(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;


	mcDir(SOUTH);
	crfieldChangeMap(32,0);
	npPos(28,37,8);
	npDir(28,NORTH);
	evScene(0,37,7);

	evFrameWait(500);
	mes.OpenMessage("Cresfield.msg",110);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(28,WEST);
	evFrameWait(250);
	npDir(28,SOUTH);
	evFrameWait(250);

	for(a = 0;a < 10;a ++){
		npMove(28,0,1);
		evFrame();
	}
	npPos(28,0,0);
	npShow(28,0);
	mes.ReadDraw(3);
	mes.CloseMessage();

	evSet(65,1);

	return 1;
}

//---復活祭前夜
CREVENTLONG1_API int creventCresfield_FukkatusaiZennya(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	crmusicFadeOut();
	evFadeOut();
	mcShow(0);
	crfieldPaletteChange(PALETTE_NIGHT);
	crfieldChangeScene(4,10,7);
	et->Reset();
	npPos(6,12,8);
	npDir(6,SOUTH);

	em->Put(11,9,2,59);
	em->Put(12,9,2,59);
	em->Put(13,9,2,59);
	em->Put(14,9,2,59);
	npPos(2,0,0);
	npShow(2,0);

	evFieldNoFlip(0,1);
	et->Wait2(2000);
	crmusicStop();
	evFadeIn();

	crmusicPlay(CRMUSIC_SAKABA);
	evFrameWait(2000);//12,2 12,8
	npPos(3,12,2);
	npDir(3,SOUTH);
	evFrameWait(1000);
	npMove(3,0,1);
	evFrame();

	for(a = 0;a < 3;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(500);

	mes.OpenMessage("Cresfield.msg",112);
	mes.ReadDraw(2);
	evFrameWait(1000);

	for(a = 0;a < 7;a ++){
		if(a < 3)
			npMove(3,0,1);
		else if(a < 5)
			npMove(3,-1,0);
		else
			npMove(3,0,1);
		evFrame();
	}
	npDir(6,WEST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(3,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	//---一杯どう？
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---トマト
	evFrameWait(500);
	npDir(3,SOUTH);
	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	npDir(6,SOUTH);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---旅の目的？
	evFrameWait(2000);
	npDir(3,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(6,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	//---ドーグリで・・・
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	npDir(6,SOUTH);
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(800);
	mes.ReadDraw(3);

	//---いいんです！
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(6,WEST);
	evFrameWait(500);
	mes.ReadDraw(3);

	evFrameWait(300);
	npDir(6,NORTH);
	evFrameWait(300);
	npDir(3,NORTH);
	evFrameWait(500);

	//---みんな大変なんだよね
	crmusicFadeOut();
	evScene(6,15,15);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	evFadeOut();

	//---宿屋２階
	em->ReloadPattern();
	crmusicStop();
	mcShow(1);
	crfieldChangeScene(3,15,9);

	npPos(1,13,5);
	npDir(1,SOUTH);
	npPos(2,12,10);
	npDir(2,EAST);
	npPos(3,18,6);
	npDir(3,SOUTH);
	npPos(4,13,11);
	npDir(4,NORTH);

	evSet(65,2);
	evSet(66,1);

	return 1;
}

//---復活祭！！
CREVENTLONG1_API int creventCresfield_Fukkatusai(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	crmusicFadeOut();
	evFadeOut();
	mcShow(0);

	evScene(6,15,15);
	evFrameWait(1000);
	mes.OpenMessage("Cresfield.msg",113);
	mes.ReadDraw();
	evFrameWait(250);
	crmusicPlay(CRMUSIC_DRAGONBREATH);
	//---はじまった
	mes.ReadDraw();
	evFrameWait(1000);

	evReadObject(0,"Asgray.acf");

	crfieldChangeScene(0,58,51);
	for(a = 0;a < 50;a ++){
		npPos(a,0,0);
		npShow(a,0);
	}
	npPos(32,58,51);
	npDir(32,SOUTH);
	npPos(33,56,49);
	npDir(33,SOUTH);
	npPos(58,60,49);
	npDir(58,SOUTH);

	//---民衆
	for(a = 0;a < 18;a ++){
		if(a == 12)
			continue;
		npPos(a,54 + (a + 4) % 12  + (a < 5 ? eiRnd(2) - (a * 3) : 0),54 + (a + 4) / 12);
		npDir(a,NORTH);
	}
	for(a = 34;a <= 47;a ++){
		npPos(a,52 + (a * 2) % 14 + eiRnd(2),52 + (a * 2) / 14);
		npDir(a,NORTH);
	}
	for(a = 48;a <= 57;a ++){
		npPos(a,51 + (a * 3) % 15 + eiRnd(2),49 + (a * 3) / 15);
		npDir(a,NORTH);
	}

	//---ルナン達
	npPos(18,53,64);
	npDir(18,NORTH);
	npPos(19,52,64);
	npDir(19,NORTH);
	npPos(20,54,65);
	npDir(20,NORTH);

/*	evScene(0,37,6);

	evFrame();
	evFrame();
	for(a = 0;a < 12;a ++){
		mcMove(0,1);
		evFrame();
	}
	for(a = 0;a < 21;a ++){
		mcMove(1,0);
		evFrame();
	}
	for(a = 0;a < 36;a ++){
		mcMove(0,1);
		evFrame();
	}*/
	evScene(0,58,54);

	//---アズグレイ
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---永き幸せを！！
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	for(a = 0;a < 10;a ++){
		mcMove(0,1);
		evFrame();
	}
	//---ルナンとディザ
	evFrameWait(500);
	npDir(19,EAST);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	evScene(6,15,15);
	evFrameWait(1000);
	mes.ReadDraw(2);
	evFrameWait(1000);

	evScene(0,58,54);
	npDir(19,NORTH);

	//---クレスティーユ復活じゃあああ
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---アズグレイ移動
	evFrameWait(1000);
	npDir(32,EAST);
	evFrameWait(1000);
	for(a = 0;a < 4;a ++){
		npMove(32,1,0);
		evFrame();
		evFrameWait(1000);
	}
	npDir(32,NORTH);
	evFrameWait(1000);
	npMove(32,0,-1);
	evFrame();
	evFrameWait(1000);
	npDir(32,WEST);
	evFrameWait(1000);
	npDir(32,SOUTH);

	evFrameWait(1000);
	for(a = 0;a < 3;a ++){
		if(a < 2)
			npMove(33,0,1);
		else
			npMove(33,1,0);
		evFrame();
	}
	npDir(33,SOUTH);
	evFrameWait(500);

	//---瞑想だよーん
	mes.ReadDraw();
	evFrameWait(1000);
	npDir(32,WEST);
	evFrameWait(1000);
	npDir(32,NORTH);
	evFrameWait(1000);
	for(a = 0;a < 5;a ++){
		npMove(32,0,-1);
		evFrame();
		evFrameWait(1000);
	}
	evFrameWait(1000);
	//---交響楽団
	mes.ReadDraw();

	evFrameWait(1000);
	for(a = 0;a < 10;a ++){
		mcMove(0,1);
		evFrame();
	}

	//---サヴィアーが来る
	evFrameWait(2000);
	npPos(21,47,64);
	npDir(21,EAST);
	for(a = 0;a < 4;a ++){
		npMove(21,1,0);
		if(a == 2)
			npDir(19,WEST);
		if(a == 3)
			npDir(18,WEST);
		evFrame();
	}
	npDir(20,WEST);
	evFrameWait(500);
	mes.ReadDraw(4);

	evFrameWait(250);
	npDir(21,NORTH);
	evFrameWait(250);
	npDir(21,WEST);
	evFrameWait(250);

	for(a = 0;a < 10;a ++){
		npMove(18,-1,0);
		npMove(19,-1,0);
		npMove(21,-1,0);
		if(a)
			npMove(20,-1,0);
		evFrame();
	}
	evFrameWait(250);

	//---町の外
	crfieldChangeScene(7,12,13);
	npPos(4,12,10);
	npDir(4,WEST);

	npPos(0,12,26);
	npDir(0,NORTH);
	npPos(1,11,27);
	npDir(1,NORTH);
	npPos(2,14,27);
	npDir(2,NORTH);
	npPos(3,11,25);
	npDir(3,NORTH);
	evScene(7,12,13);

	evFrameWait(1000);
	for(a = 0;a < 14;a ++){
		npMove(0,0,-1);
		npMove(1,0,-1);
		npMove(2,0,-1);
		npMove(3,0,-1);

		if(a == 10)
			npDir(4,SOUTH);

		evFrame();
	}

	//---ライゼル
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);
	//---おまかせサヴィアー
	mes.ReadDraw();
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(2,0,-1);
		evFrame();
	}
	npDir(2,WEST);
	evFrameWait(250);
	//---すごい！
	mes.ReadDraw(2);
	evFrameWait(500);

	//---反応は・・・
	evFrameWait(90);
	npDir(3,WEST);
	evFrameWait(900);
	npDir(3,NORTH);
	evFrameWait(900);
	npDir(3,EAST);
	evFrameWait(900);
	npDir(3,SOUTH);
	evFrameWait(900);
	mes.ReadDraw(2);

	evFrameWait(1500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	npMove(3,-1,0);
	evFrame();
	evFrameWait(250);
	//---根本！！
	mes.ReadDraw();

	evFrameWait(100);
	npDir(0,WEST);
	evFrameWait(100);
	npDir(1,WEST);
	evFrameWait(100);
	npDir(4,WEST);
	evFrameWait(1700);

	mes.ReadDraw();

	//---みんなの非難
	evFrameWait(1000);
	mes.ReadDraw(3);
	evFrameWait(500);
	npDir(3,NORTH);
	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	//---像の耳ライゼル
	evFrameWait(250);
	npDir(4,SOUTH);
	evFrameWait(250);
	npDir(4,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(150);
	npDir(1,NORTH);
	evFrameWait(150);
	npDir(3,NORTH);
	evFrameWait(150);
	npDir(2,NORTH);
	evFrameWait(150);
	npDir(0,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(4,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(1500);
	mes.ReadDraw(2);

	//---追わないと
	evFrameWait(500);
	mes.ReadDraw(2);

	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---心当たりは？
	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);
	npMove(3,0,1);
	evFrame();
	npDir(3,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	//---南東？
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	npDir(2,WEST);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	mes.CloseMessage();
	evSet(66,3);

	mcShow(1);
	mcDir(SOUTH);
	evMap(10,0,235,194);

	return 1;
}

//---幻惑の樹海、遺跡、ラーフィアと
CREVENTLONG1_API int creventGenwaku_Rafia_Cresteaju(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	npPos(0,24,28);
	npPos(1,25,28);
	npPos(2,22,29);
	npPos(3,23,29);
	npPos(4,26,29);
	for(a = 0;a <= 4;a ++){
		npDir(a,NORTH);
	}
	evScene(4,24,29);
	crmusicPlay(CRMUSIC_ETERNAL);
	evFrameWait(500);
	npDir(8,SOUTH);
	evFrameWait(250);

	mes.OpenMessage("GenwakuForest.msg",105);
	mes.ReadDraw(2);

	//---やめてもらうぜ
	evFrameWait(500);
	npMove(1,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	npMove(3,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---いまさらなにを
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npMove(2,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---侵入者でーす！！
	evFrameWait(250);
	npDir(8,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	npMove(4,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(8,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	npMove(0,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	mes.CloseMessage();

	//---バトル
	CR_BATTLEINFO BattleInfo;
	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.Music = CRMUSIC_ETERNALBATTLE;
	BattleInfo.Enemy[0].Enemy = 67;
	BattleInfo.Enemy[0].x = 6;
	BattleInfo.Enemy[0].y = 8;
	BattleInfo.Enemy[1].Enemy = -1;
	BattleInfo.ScreenEfect = CRINTOBAT_BOSS1;
	if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
		return MAINLOOP_BATTLEFAIL;
	}

	mes.OpenMessage("GenwakuForest.msg",106);
	evSet(71,1);

	//--ラーフィア後ろに下がる
	evFrameWait(250);
	npMove(8,0,-1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);

	//---ラーフィア逃げる
	for(a = 0;a < 12;a ++){
		npMove(8,-1,0);

		if(a == 4)
			npDir(1,WEST);
		if(a == 5)
			npDir(0,WEST);
		if(a == 6)
			npDir(3,WEST);
		if(a == 7)
			npDir(2,WEST);
		if(a == 8)
			npDir(4,WEST);

		evFrame();
	}

	mes.ReadDraw(2);
	evFrameWait(250);
	//---アズグレイ
	npPos(6,9,13);
	npDir(6,SOUTH);
	npPos(7,10,12);
	npDir(7,SOUTH);
	npPos(8,9,14);
	npDir(8,NORTH);

	for(a = 0;a < 27;a ++){
		if(a < 15)
			mcMove(-1,0);
		else
			mcMove(0,-1);
		evFrame();
	}
	evFrameWait(4000);
	for(a = 0;a < 7;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(1000);
	for(a = 0;a < 7;a ++){
		mcMove(0,1);
		evFrame();
	}

	npPos(0,9,24);
	npPos(1,10,24);
	npPos(2,11,25);
	npPos(3,10,25);
	npPos(4,9,26);
	evFrameWait(500);
	for(a = 0;a < 10;a ++){
		if(a < 8){
			for(b = 0;b <= 4;b ++){
				npMove(b,0,-1);
			}
		} else if(a < 9)
			npMove(4,-1,0);
		else
			npMove(4,0,-1);

		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(3);

	evFrameWait(250);
	npDir(8,WEST);
	evFrameWait(250);
	npDir(8,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
	//---知りたいなら教えてやろう
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(8,WEST);
	evFrameWait(1000);
	for(a = 0;a < 10;a ++){
		if(a < 1)
			npMove(8,-1,0);
		else if(a < 3)
			npMove(8,0,-1);
		else if(a < 5)
			npMove(8,1,0);
		else
			npMove(8,0,-1);
		if(a < 4){
		} else if(a == 4)
			npDir(7,WEST);
		if(a == 5)
			npDir(7,NORTH);
		else
			npMove(7,0,-1);
		evFrame();
	}
	npPos(7,11,8);
	npDir(7,NORTH);
	npPos(8,11,9);
	npDir(8,WEST);
	//---説明
	evFrameWait(250);
	mes.ReadDraw();
	//---
	evFrameWait(250);
	npDir(6,WEST);
	evFrameWait(500);
	npMove(6,-1,0);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	//---
	evFrameWait(250);
	npDir(6,NORTH);
	evFrameWait(500);
	npMove(6,0,-1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	//---ふざけないで！
	mes.ReadDraw();
	evFrameWait(1000);
	//---
	evFrameWait(250);
	npDir(6,EAST);
	evFrameWait(500);
	npMove(6,1,0);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	//---
	evFrameWait(250);
	npDir(6,SOUTH);
	evFrameWait(500);
	npMove(6,0,1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(700);
	mes.ReadDraw();
	evFrameWait(250);
	npMove(0,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---どうあれそうなんだ
	mes.ReadDraw(2);
	//---りっぱだな
	evFrameWait(250);
	npMove(1,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);

	//---フィルガルトを作るまでは・・・
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

	//---もういい！！
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(6,EAST);
	evFrameWait(250);
	npDir(6,NORTH);
	evFrameWait(250);
	npMove(6,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	for(a = 0;a < 4;a ++){
		mcMove(0,-1);
		evFrame();
	}
	//---開く
	evFrameWait(1000);
	crsoundPlay(31);
	em->Put(9,7,2,1024);
	evFrameWait(250);
	for(a = 0;a < 9;a ++){
		npMove(6,0,-1);
		evFrame();
	}
	//---止めましょう
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	for(a = 0;a < 4;a ++){
		if(a < 3)
			npMove(0,0,-1);
		if(a)
			npMove(1,0,-1);
		if(a < 3)
			npMove(2,0,-1);
		if(a)
			npMove(3,0,-1);
		if(a)
			npMove(4,0,-1);
		evFrame();
	}
	npDir(7,WEST);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(7,-1,0);
		else
			npMove(7,0,1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw(3);
	evFrameWait(250);
	//---よくみておきなさい
	evFrameWait(250);
	npDir(8,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(250);
	npMove(0,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---ばかな
	evFrameWait(2000);
	crmusicStop();
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(7,WEST);
	evFrameWait(250);
	npDir(8,WEST);
	npDir(7,NORTH);
	evFrameWait(250);
	evFrameWait(2000);
	mes.ReadDraw(2);

	mes.ReadDraw();
	evFrameWait(250);
	npDir(7,WEST);
	evFrameWait(250);

	//---フォールンとラーフィア移動
	for(a = 0;a < 4;a ++){
		if(a < 1)
			npMove(7,-1,0);
		else
			npMove(7,0,-1);
		evFrame();
	}
	npPos(7,8,4);
	for(a = 0;a < 5;a ++){
		if(a < 2)
			npMove(8,-1,0);
		else
			npMove(8,0,-1);
		evFrame();
	}
	npPos(8,10,4);
	evFrameWait(1500);
	mes.ReadDraw();

	evFrameWait(250);
	for(a = 0;a < 6;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(5000);
	for(a = 0;a < 6;a ++){
		mcMove(0,1);
		evFrame();
	}
	//---ナック
	evFrameWait(500);
	npMove(2,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);
	//---どうやら思い通りにはいかなかったみたいね
	evFrameWait(500);
	npMove(0,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);

	for(a = 0;a < 13;a ++){
		if(a == 0)
			npDir(0,WEST);
		if(a == 1)
			npDir(0,SOUTH);
		if(a == 2)
			npDir(0,WEST);
		if(a == 3)
			npDir(0,NORTH);

		if(a == 2)
			npDir(1,EAST);
		if(a == 3)
			npDir(1,SOUTH);
		if(a == 4)
			npDir(1,EAST);
		if(a == 5)
			npDir(1,NORTH);

		if(a == 7)
			npDir(2,WEST);
		if(a == 8)
			npDir(2,NORTH);

		if(a == 4)
			npDir(3,WEST);
		if(a == 5)
			npDir(3,NORTH);

		if(a == 9)
			npDir(4,EAST);
		if(a == 10)
			npDir(4,NORTH);

		if(a < 1)
			npMove(7,1,0);
		else if(a < 5)
			npMove(7,0,1);
		else if(a < 6)
			npMove(7,-1,0);
		else
			npDir(7,SOUTH);
		if(a < 2){
		} else if(a < 3)
			npMove(8,-1,0);
		else if(a < 7)
			npMove(8,0,1);
		else if(a < 8)
			npMove(8,1,0);
		else
			npDir(8,SOUTH);

		if(a < 8){
		} else if(a < 13)
			npMove(6,0,1);
		evFrame();
	}
	//---誰だ！？
	evFrameWait(250);
	mes.ReadDraw();

	//---
	evFrameWait(1000);
	crmusicPlay(CRMUSIC_CRAYSIVE);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(8,WEST);
	evFrameWait(250);
	npDir(8,SOUTH);
	evFrameWait(250);
	npDir(8,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---みんな振り向く
	evFrameWait(1000);
	npDir(8,SOUTH);
	evFrameWait(500);
	npDir(1,WEST);
	evFrameWait(125);
	npDir(3,WEST);
	evFrameWait(125);
	npDir(1,SOUTH);
	evFrameWait(125);
	npDir(3,SOUTH);
	npDir(0,EAST);
	evFrameWait(125);
	npDir(4,EAST);
	evFrameWait(125);
	npDir(0,SOUTH);
	evFrameWait(125);
	npDir(4,SOUTH);
	evFrameWait(125);
	npDir(2,WEST);
	evFrameWait(250);
	npDir(2,SOUTH);
	evFrameWait(250);

	npPos(5,10,24);
	npDir(5,NORTH);
	for(a = 0;a < 12;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1500);
	for(a = 0;a < 11;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(500);
	for(a = 0;a < 6;a ++){
		npMove(5,0,-1);
//		if(a > 2)
			evFrameWait(500);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---目覚めのきっかけをつくるため
	evFrameWait(2000);
	for(a = 0;a < 3;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	for(a = 0;a < 3;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---クレイシヴ歩く
	npDir(5,WEST);
	evFrameWait(500);
	for(a = 0;a < 4;a ++){
		if(a < 1)
			npMove(5,-1,0);
		else
			npMove(5,0,-1);
		evFrame();
		evFrameWait(500);
		if(a == 0){
			npDir(5,NORTH);
			evFrameWait(500);
		}
	}
	evFrameWait(100);
	//---やるのか？
	mes.ReadDraw();
	evFrameWait(1000);
	for(a = 0;a < 1;a ++){
		npMove(5,0,-1);
		evFrame();
		evFrameWait(500);
	}
	//---先生は・・・
	npDir(3,WEST);
	evFrameWait(300);
	npDir(4,EAST);
	evFrameWait(200);
	mes.ReadDraw();

	evFrameWait(500);
	for(a = 0;a < 1;a ++){
		npMove(5,0,-1);
		evFrame();
		npDir(3,NORTH);
		evFrameWait(500);
	}
	npDir(4,NORTH);
	evFrameWait(300);
	npDir(2,WEST);
	evFrameWait(500);

	mes.ReadDraw();

	//---ディザの横
	evFrameWait(500);
	for(a = 0;a < 1;a ++){
		npMove(5,0,-1);
		evFrame();
		npDir(1,WEST);
		evFrameWait(500);
	}
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---なんなの
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(5,WEST);
	evFrameWait(500);
	for(a = 0;a < 1;a ++){
		npMove(5,-1,0);
		evFrame();
		npDir(1,WEST);
		evFrameWait(500);
	}
	npDir(1,NORTH);
	evFrameWait(500);
	npDir(5,NORTH);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	for(a = 0;a < 1;a ++){
		npMove(5,0,-1);
		evFrame();
		evFrameWait(500);
	}
	//---すでにめざめているっちゅーの
	evFrameWait(1000);
	mes.ReadDraw();

	//---ルナンの横に来る
	evFrameWait(1000);
	for(a = 0;a < 1;a ++){
		npMove(5,0,-1);
		evFrame();
		evFrameWait(500);
	}
	npDir(0,WEST);
	evFrameWait(1500);
	npDir(5,EAST);
	evFrameWait(500);
	//---そうであろう
	mes.ReadDraw();
	evFrameWait(1000);
	//---は？
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---今はルナン
	evFrameWait(500);
	npDir(5,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---昔の記憶
	crfieldChangeScene(5,9,14);
	evFrameWait(250);
	crfieldChangeScene(4,9,14);
	evFrameWait(700);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(2);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	crfieldChangeScene(5,9,14);
	evFrameWait(500);
	crfieldChangeScene(4,9,14);
	evFrameWait(1000);
	//---なにこれは・・・
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	//---クレイシヴが去る
	for(a = 0;a < 15;a ++){
		if(a < 2)
			npMove(5,0,1);
		else if(a < 3)
			npMove(5,1,0);
		else
			npMove(5,0,1);
		evFrame();
		evFrameWait(500);
		if(a == 1){
			npDir(5,EAST);
			evFrameWait(500);
		} else if(a == 2){
			npDir(5,EAST);
			evFrameWait(500);
		}

		if(a == 1)
			npDir(1,WEST);
		if(a == 3)
			npDir(1,SOUTH);
		if(a == 2)
			npDir(2,WEST);
		if(a == 3)
			npDir(2,SOUTH);
		if(a == 3)
			npDir(3,WEST);
		if(a == 4)
			npDir(3,SOUTH);
		if(a == 4)
			npDir(4,EAST);
		if(a == 5)
			npDir(4,SOUTH);
	}
	evFrameWait(500);
	mes.ReadDraw();

	//---追うぞ！
	evFrameWait(250);
	for(a = 0;a < 3;a ++){
		if(a < 1)
			npMove(6,0,1);
		else if(a < 2)
			npMove(6,-1,0);
		else
			npMove(6,0,1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	mes.ReadDraw(4);

	//---エターナル去る
	evFrameWait(250);
	for(a = 0;a < 20;a ++){
		if(a < 3)
			npMove(6,0,1);
		else if(a < 4)
			npMove(6,1,0);
		else
			npMove(6,0,1);

		if(a < 2){
		} else if(a < 5)
			npMove(7,0,1);
		else if(a < 6)
			npMove(7,1,0);
		else
			npMove(7,0,1);

		if(a < 4){
		} else if(a < 7)
			npMove(8,0,1);
		else if(a < 8)
			npMove(8,-1,0);
		else
			npMove(8,0,1);
		evFrame();
	}
	//---
	evFrameWait(1500);
	mes.ReadDraw(2);

	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	for(a = 0;a < 4;a ++){
		npMove(4,0,-1);
		evFrame();
	}
	//---真っ青
	npDir(4,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(1,-1,0);
		else
			npMove(1,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(2);

	//---記憶
	evFrameWait(500);
	crfieldChangeScene(5,9,14);
	evFrameWait(1000);
	crfieldChangeScene(4,9,14);
	evFrameWait(1000);

	mes.ReadDraw();
	evFrameWait(2000);
	crmusicFadeOut();
	evFadeOut(2000);

	//---気を失う
	crfieldChangeScene(6,15,15);
	evFrameWait(1000);
	crmusicStop();
	mes.ReadDraw();
	evFrameWait(1000);

	mes.CloseMessage();


	return 1;
}
