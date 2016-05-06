/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrEventLong5.cpp ...Event functions

-----------------------------------------------------------*/


#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CREVENTLONG5

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#include "CrBase.h"
#include "CrBattle.h"
#include "CrEvent.h"
#include "CrEvCom.h"

//---game info
#define CR_GAMEINFO_EXTERNPOINTER
#include "CrGameInfo.h"

CREVENTLONG_ENDING_API int crevent_EndingArje(void);
CREVENTLONG_ENDING_API int crevent_EndingSorekara(void);
CREVENTLONG_ENDING_API int crevent_EndingMatsuri(void);
CREVENTLONG_ENDING_API int crevent_EndingMatsuri2(void);
CREVENTLONG_ENDING_API int crevent_EndingMatsuri3(void);
CREVENTLONG_ENDING_API int crevent_EndingMatsuri4(void);
CREVENTLONG_ENDING_API int crevent_EndingMatsuri5(void);
CREVENTLONG_ENDING_API int crevent_EndingMatsuri6(void);

CREVENTLONG_ENDING_API int crevent_EndingWorldAfter(void);
CREVENTLONG_ENDING_API int crevent_EndingTheEnd(void);


CREVENTLONG_ENDING_API int crevent_dumye(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	return 1;
}

//---クリア情報書き込み
CREVENTLONG_ENDING_API void crevent_WriteEndData(void)
{
	int number = crdataGetSystem()->SaveNumber;

	if(number == -1)
		return;

	int ningen_cr = evGet(261);
	int temp[MUSIC_MAX];
	memcpy(temp,pGameInfo->Music,sizeof(temp));

	int record = 0;
	int hour = pGameInfo->PlayHours,min = pGameInfo->PlayMinutes,sec = pGameInfo->PlaySeconds;
	if(evGet(260) == 0){
		record = 1;
	}
	if(hour < pGameInfo->MinClearHour){
		record = 1;
	} else if(hour == pGameInfo->MinClearHour){
		if(min < pGameInfo->MinClearMinute){
			record = 1;
		} else if(min == pGameInfo->MinClearMinute){
			if(sec < pGameInfo->MinClearSecond){
				record = 1;
			}
		}
	}

	crfileLoadData(number,SAVE_FILE_ID1,SAVE_FILE_ID2,1);

	evSet(262,ningen_cr);//---人間クレイシヴを倒した
	if(record){
		//---記録更新！
		pGameInfo->MinClearHour = hour;
		pGameInfo->MinClearMinute = min;
		pGameInfo->MinClearSecond = sec;
	}

	//---音楽
	memcpy(pGameInfo->Music,temp,sizeof(pGameInfo->Music));

	//---クリアフラッグ
	evSet(260,1);

	crfileSaveData(number,SAVE_FILE_ID1,SAVE_FILE_ID2,1);
}

//---エンディング、ラストバトル後
CREVENTLONG_ENDING_API int crevent_EndingAfterBattle(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	evFrameWait(1000);
	crmusicPlay(CRMUSIC_SILENT);
	evFrameWait(250);

	//---もう力は
	mes.OpenMessage("Ending.msg",100);
	mes.ReadDraw();

	evFrameWait(500);
	evFadeOut(250,RGB_MAKE(255,255,255));
	evFieldNoFlip(0,1);
	evFadeIn(250,RGB_MAKE(255,255,255));

	crmusicPlay(CRMUSIC_BEAWAKEN,0);
	evFrameWait(250);

	//---！
	mes.ReadDraw();

	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	npMove(1,1,0);
	evFrame();
	evFrameWait(250);
	npDir(1,NORTH);
	evFrameWait(250);
	npMove(1,0,-1);
	evFrame();
	evFrameWait(250);

	//---アージェ
	em->Put(22,2,2,117);
	em->Put(22,3,2,121);
	for(a = 0;a < 14;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(1000);
	for(a = 0;a < 14;a ++){
		mcMove(0,1);
		evFrame();
	}

	//---オレはここで
	evFrameWait(250);
	npMove(2,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---ディザも
	npDir(1,WEST);
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);
	npMove(1,0,1);
	evFrame();
	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(250);

	mes.ReadDraw();
	evFrameWait(250);

	//---わかった
	evFrameWait(1000);
	npDir(2,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	crmusicWait(23 * 1000);
	evFrameWait(500);
	//---急ぎましょう！
	mes.ReadDraw();
	evFrameWait(500);
	npDir(1,NORTH);
	evFrameWait(500);

	//---アージェの元へ
	for(a = 0;a < 14;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(500);

	npPos(1,22,15);
	npPos(2,21,16);
	npPos(3,23,17);
	npPos(4,22,17);

	for(a = 0;a < 11;a ++){
		if(a < 10)
			npMove(1,0,-1);
		if(a < 10)
			npMove(2,0,-1);
		if(a < 11)
			npMove(3,0,-1);
		if(a < 10)
			npMove(4,0,-1);
		evFrame();
	}

	evFrameWait(500);

	//---この中にアージェが
	mes.ReadDraw();
	crmusicWait(34 * 1000);
	//---どうやって
	evFrameWait(500);
	npDir(1,WEST);
	evFrameWait(500);
	npDir(1,NORTH);
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(500);
	npDir(1,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---わかりません！
	evFrameWait(250);
	npDir(4,EAST);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(4,1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(4,NORTH);
	evFrameWait(500);
	mes.ReadDraw();
	crmusicWait(44 * 1000);
	evFrameWait(250);

	//---くっそ！
	for(a = 0;a < 2;a ++){
		npMove(2,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	for(a = 0;a < 1;a ++){
		npMove(1,0,-1);
		evFrame();
	}
	//---みんな・・・
	evFrameWait(250);
	for(a = 0;a < 1;a ++){
		npMove(3,0,-1);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();
	crmusicWait(54 * 1000);
	evFrameWait(500);

	evFadeOut(2000,RGB_MAKE(255,255,255));
	et->Delay2(2000);
	crmusicWait(62 * 1000);
	mes.CloseMessage();

	return crevent_EndingArje();
}

//---エンディング、アージェとの会話
CREVENTLONG_ENDING_API int crevent_EndingArje(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	crfieldChangeMap(101,0,1,0);
	crfieldChangeScene(0,25,25);

	evFieldNoFlip(0,1);
	evFadeIn(4000,RGB_MAKE(255,255,255));

	evFrameWait(500);
	crmusicPlay(CRMUSIC_SILENT);
	evFrameWait(1000);

	mes.OpenMessage("Ending.msg",101);
	for(a = 0;a < 6;a++){
		evFrameWait(1000);
		mes.ReadDraw();
	}
	evFrameWait(2000);
	mes.ReadDraw();
	evFrameWait(2000);

	//---目を覚ます
	npPos(0,25,25);
	npDir(0,SOUTH);
	evScene(0,25,25);

	evFrameWait(250);
	crmusicPlay(CRMUSIC_STREAM);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(1000);

	//---辺りを見回す
	npDir(0,WEST);
	evFrameWait(1000);
	npDir(0,NORTH);
	evFrameWait(2000);
	mes.ReadDraw();

	//---時間が遅い
	evFrameWait(1000);
	npMove(0,0,-1);
	evFrame();
	evFrameWait(1000);
	npMove(0,0,-1);
	evFrame();
	evFrameWait(1000);
	npDir(0,EAST);
	evFrameWait(2000);
	npDir(0,NORTH);
	evFrameWait(2000);
	mes.ReadDraw();

	//---さすがは
	evFrameWait(2000);
	mes.ReadDraw(2);
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---よくわかって
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---すべては
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---淀み始めた
	evFrameWait(2000);
	mes.ReadDraw(2);

//	evFrameWait(500);
//	mes.ReadDraw();

	//---なんでそんなことを
	evFrameWait(1000);
	mes.ReadDraw();
	//---なぜだと？
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(2000);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();

	//---クレスティーユも分かるだろう
	evFrameWait(1000);
	for(a = 0;a < 6;a ++){
		evFrameWait(1000);
		mes.ReadDraw();
	}

	//---クレイシヴだって言うの？
	evFrameWait(500);
	npMove(0,0,1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw(2);

	//---分かる？
	evFrameWait(1000);
	mes.ReadDraw();

	//---私達は同じだ
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---そうよ
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---生きる？
	evFrameWait(1000);
	mes.ReadDraw();

	//---運命が
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(2);

	//---シルバーリングのない身で
	evFrameWait(1000);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	//---・・・
	evFrameWait(2000);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw(2);

	//---やがて止まる
	evFrameWait(1000);
	mes.ReadDraw();

	//---わたしはルナン！
	evFrameWait(500);
	npMove(0,0,1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---光に包まれる
	crmusicFadeOut();
	evFadeOut(2000,RGB_MAKE(255,255,255));

	mes.CloseMessage();

//	crfieldChangeScene(1,15,15);
//	return 1;
	return crevent_EndingSorekara();
}

//---エンディング・・・それから
CREVENTLONG_ENDING_API int crevent_EndingSorekara(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	et->Delay2(2000);
	crmusicStop();

	crfieldChangeScene(1,15,15);
	evFieldNoFlip(0,1);

	mes.OpenMessage("Ending.msg",102,0,0,0);
	mes.ReadDraw();
	evFrameWait(250);

	crfieldChangeMap(51,2,1,0);
	crfieldChangeScene(2,15,5);

	evReadObject(13,"DizzaSlp.acf");
	npPos(2,17,2);
	npDir(2,EAST);
	evFieldNoFlip(0,1);
	evFadeIn(250,RGB_MAKE(255,255,255));

	//---目が覚める
	evFrameWait(500);
	npDir(2,NORTH);
	evFrameWait(150);
	npDir(2,EAST);
	evFrameWait(150);
	npDir(2,NORTH);
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);

	//---ナック
	for(a = 0;a < 9;a ++){
		mcMove(-1,0);
		evFrame();
	}
	evFrameWait(500);
	npPos(3,2,2);
	npDir(3,EAST);

	evReadObject(13,"Dizza.acf");
	npPos(2,16,3);
	npDir(2,WEST);

	for(a = 0;a < 11;a ++){
		if(a < 7)
			npMove(3,1,0);
		else
			npMove(3,0,1);
		evFrame();
	}
	npDir(3,EAST);
	for(a = 0;a < 9;a ++){
		mcMove(1,0);
		evFrame();
	}
	evFrameWait(500);
	//---どうしたの？
	mes.ReadDraw();

	evFrameWait(500);
	npDir(2,SOUTH);
	evFrameWait(250);
	for(a = 0;a < 4;a ++){
		if(a < 3)
			npMove(2,0,1);
		else
			npMove(2,-1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(2,WEST);
	evFrameWait(250);
	//---ああ、夢の中で
	mes.ReadDraw();

	evFrameWait(500);
	for(a = 0;a < 3;a ++){
		npMove(3,1,0);
		evFrame();
	}
	evFrameWait(250);
	mes.ReadDraw();

	//---なんて・・・？
	evFrameWait(500);
	mes.ReadDraw(2);

	//---知ってるやつ
	evFrameWait(500);
	mes.ReadDraw();

	//---お師匠さま？
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---朝御飯
	evFrameWait(250);
	for(a = 0;a < 1;a ++){
		npMove(3,1,0);
		evFrame();
	}
	mes.ReadDraw(2);

	//---移動
	evFrameWait(250);
	npDir(3,NORTH);
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	for(a = 0;a < 9;a ++){
		mcMove(-1,0);
		evFrame();
	}

	for(a = 0;a < 15;a ++){
		if(a < 1){
		} else if(a < 7)
			npMove(2,-1,0);
		else if(a < 11)
			npMove(2,0,-1);
		else if(a < 15)
			npMove(2,-1,0);

		if(a < 4)
			npMove(3,-1,0);
		else if(a < 8)
			npMove(3,0,-1);
		else if(a < 13)
			npMove(3,-1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(250);
	//---楽しみ
	mes.ReadDraw(2);

	evFrameWait(500);
	mes.ReadDraw(3);

	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);

	for(a = 0;a < 5;a ++){
		if(a < 2)
			npMove(3,-1,0);
		else
			npDelete(3);
		if(a < 1){
		} else if(a < 4)
			npMove(2,-1,0);
		else
			npDelete(2);

		evFrame();
	}
	evFrameWait(1000);
	mes.CloseMessage();

	//---時は・・・
	evScene(4,15,15);
	evFrameWait(500);
	crmusicPlay(CRMUSIC_PEACE);
	mes.OpenMessage("Ending.msg",103,0,2,1);
	mes.ReadDraw();
	mes.CloseMessage();

	evFadeOut();

	return crevent_EndingMatsuri();
}

//---エンディング・・・ユミ
CREVENTLONG_ENDING_API int crevent_EndingMatsuri(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

//	crmusicPlay(CRMUSIC_PEACE);
	evFrameWait(500);

	crfieldChangeMap(102,0,1,0);
	crfieldChangeScene(0,19,18);
	npPos(0,19,5);
	npDir(0,SOUTH);

	evFieldNoFlip(0,1);
	evFadeIn();
	evFrameWait(1000);

	//---ユミ歩いてる
	for(a = 0;a < 10;a ++){
		npMove(0,0,1);
		evFrame();
	}
	evFrameWait(1000);

	//---独り言
	mes.OpenMessage("Ending.msg",104);
	mes.ReadDraw();

	evFrameWait(500);
	npMove(0,0,1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();

	//---みーんな！
	evFrameWait(500);
	npDir(0,EAST);
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---これって・・・
	evFrameWait(500);
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);

	//---まぁいいか
	npMove(0,0,1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	int old = ef->SetMoveSpeed(2);

	npPos(1,17,29);//---ピエール
	npDir(1,NORTH);
	npPos(2,17,28);//---ジュリアス
	npDir(2,SOUTH);

	for(a = 0;a < 13;a ++){
		if(a == 9)
			npDir(2,EAST);
		if(a == 11)
			npDir(1,EAST);
		if(a < 12)
			npMove(0,0,1);
		mcMove(0,1);
		evFrame();
	}
	//---ジュリアスナンパ！
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npMove(0,0,1);
	evFrame();
	npDir(1,SOUTH);//---ピエール
	evFrameWait(250);
	mes.ReadDraw();

	//---しかと！
	evFrameWait(250);
	npMove(0,0,1);
	npMove(2,1,0);
	evFrame();
	evFrameWait(250);
	npDir(2,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---なあに？
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---・・・
	evFrameWait(500);
	npDir(1,EAST);
	for(a = 0;a < 2;a ++){
		npMove(1,1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---だったら、一緒に！
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(250);
	npDir(0,SOUTH);
	evFrameWait(250);

	mcMove(0,1);
	npMove(0,0,1);
	evFrame();
	//---待ってくださいよ！
	evFrameWait(250);
	npMove(2,0,1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---エターナルもいなくなったのに？
	evFrameWait(250);
	npDir(0,WEST);
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	mes.ReadDraw(2);

	//---ふうん
	evFrameWait(500);
	mes.ReadDraw();

	//---ジュリアス振り返る
	evFrameWait(250);
	npDir(2,EAST);
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(500);
	npDir(2,EAST);
	evFrameWait(250);
	npDir(2,NORTH);
	evFrameWait(250);
	npDir(2,WEST);
	evFrameWait(250);

	for(a = 0;a < 6;a ++){
		if(a < 3)
			npMove(2,-1,0);
		else if(a < 5)
			npMove(2,0,1);
		else
			npDir(2,EAST);

		if(a == 0)
			npDir(1,WEST);
		else if(a < 2){
		} else if(a < 5)
			npMove(1,-1,0);
		else if(a < 6)
			npMove(1,0,1);

		if(a == 4)
			npDir(0,WEST);
		evFrame();
	}
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);

	//---男が来る
	npPos(3,19,24);
	npDir(3,SOUTH);
	for(a = 0;a < 4;a ++){
		npMove(3,0,1);
		if(a == 3)
			npDir(0,NORTH);
		evFrame();
	}

	//---きょろきょろ
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(500);
	npDir(3,SOUTH);
	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(500);
	npDir(3,SOUTH);
	evFrameWait(250);

	for(a = 0;a < 2;a ++){
		npMove(3,0,1);
		evFrame();
	}
	evFrameWait(250);
	//---こーゆうのを
	mes.ReadDraw();
	//---さぁ
	evFrameWait(1000);
	mes.ReadDraw(2);

	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(250);
	for(a = 0;a < 15;a ++){
		if(a < 1)
			npMove(3,-1,0);
		else
			npMove(3,0,1);

		if(a == 3)
			npDir(0,WEST);
		if(a == 6)
			npDir(0,SOUTH);
		evFrame();
	}
	//---何なの？
	evFrameWait(1000);
	npDir(0,WEST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	npDir(2,SOUTH);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(2,0,1);
		else
			npMove(2,1,0);
		evFrame();
	}
	evFrameWait(250);
	//---先物
	mes.ReadDraw(2);

	//---あーわかった
	evFrameWait(500);
	npDir(0,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);

	for(a = 0;a < 24;a ++){
		npMove(0,0,1);
		if(a < 4){
		} else if(a < 6)
			npMove(2,1,0);
		else
			npMove(2,0,1);

		if(a < 7){
			if(a == 4)
				npDir(1,SOUTH);
			if(a == 6)
				npDir(1,WEST);
		} else if(a < 8)
			npMove(1,-1,0);
		else if(a < 11)
			npMove(1,0,1);
		else if(a < 14)
			npMove(1,1,0);
		else
			npMove(1,0,1);

		evFrame();
	}
	evFrameWait(1000);
	ef->SetMoveSpeed(old);

	mes.CloseMessage();

	//---わたしは・・・
	evScene(1,15,15);
	evFrameWait(500);
	mes.OpenMessage("Ending.msg",105,0,2,1);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	mes.CloseMessage();

	evFadeOut();

	return crevent_EndingMatsuri2();
}


//---エンディング・・・サヴィアー＆シンディ
CREVENTLONG_ENDING_API int crevent_EndingMatsuri2(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	evScene(2,17,18);
	evFrameWait(2000);

	//---挙動不審
	npDir(0,WEST);
	evFrameWait(500);
	npDir(0,SOUTH);
	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(500);
	npDir(0,SOUTH);
	evFrameWait(500);

	mes.OpenMessage("Ending.msg",106);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();

	//---びしっと
	evFrameWait(500);
	npDir(0,WEST);
	evFrameWait(500);
	npDir(0,SOUTH);
	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(500);
	npDir(0,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---通りすがりの女の子
	evFrameWait(500);
	for(a = 0;a < 14;a ++){
		npMove(5,1,0);
		if(a >= 13)
			npMove(0,0,1);
		evFrame();
	}
	evFrameWait(100);
	mes.ReadDraw();

	//---悲鳴
	evFrameWait(250);
	npDir(5,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---逃げる
	evFrameWait(250);
	npDir(5,EAST);
	evFrameWait(250);
	for(a = 0;a < 10;a ++){
		npMove(5,1,0);
		evFrame();
	}
	for(a = 0;a < 8;a ++){
		if(a == 2)
			npDir(0,WEST);
		if(a < 7)
			npMove(1,0,1);
		if(a >= 5)
			npMove(0,-1,0);
		evFrame();
	}
/*	for(a = 0;a < 3;a ++){
		npMove(0,-1,0);
		evFrame();
	}*/
	evFrameWait(100);
	mes.ReadDraw();

	//---またもや
	evFrameWait(250);
	npDir(1,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	//---逃げる
	evFrameWait(250);
	npDir(1,SOUTH);
	evFrameWait(250);
	npDir(1,WEST);
	evFrameWait(250);

	int old = ef->SetMoveSpeed(2);
	for(a = 0;a < 16;a ++){
		if(a < 8)
			mcMove(-1,0);
		npMove(1,-1,0);
		evFrame();
	}
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);

	ef->SetMoveSpeed(old);

	//---シンディがいる
	npPos(3,18,17);
	npDir(3,WEST);
	for(a = 0;a < 8;a ++){
		mcMove(1,0);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();

	//---サヴィアー驚き
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(250);
	npMove(0,-1,0,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();
	//---そ、そうでしたよね
	evFrameWait(250);
	npMove(0,1,0);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);

	evFrameWait(250);
	mes.ReadDraw(2);

	//---クレスフィールドは
	evFrameWait(1000);
	mes.ReadDraw(2);

	//---・・・
	evFrameWait(1000);
	npDir(0,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	//---なにか
	evFrameWait(500);
	npDir(0,EAST);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---行きましょう
	evFrameWait(500);
	npDir(0,SOUTH);
	for(a = 0;a < 3;a ++){
		if(a < 1)
			npMove(0,0,1);
		else
			npMove(0,1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(0,NORTH);
	evFrameWait(250);
	npDir(3,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(0,EAST);
	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(250);
	for(a = 0;a < 15;a ++){
		if(a)
			npMove(0,1,0);
		npMove(3,1,0);
		evFrame();
	}
	evFrameWait(250);

	mes.CloseMessage();

	//---そのことを知ったら
	evScene(1,15,15);
	evFrameWait(500);
	mes.OpenMessage("Ending.msg",107,0,2,1);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	mes.CloseMessage();

	evFadeOut();

	return crevent_EndingMatsuri3();
}

//---エンディング・・・再会
CREVENTLONG_ENDING_API int crevent_EndingMatsuri3(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	crfieldChangeMap(103,0,1,0);
	npPos(17,44,35);
	npDir(17,NORTH);
	npPos(18,44,37);
	npDir(18,NORTH);
//	evFieldNoFlip(0,1);
	evScene(0,37,10);

	evFrameWait(1000);
	int old = ef->SetMoveSpeed(2);

	for(a = 0;a < 16;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(1000);
	for(a = 0;a < 20;a ++){
		if(a < 6)
			npMove(17,0,-1);
		else if(a < 7)
			npMove(17,-1,0);
		else if(a < 8)
			npMove(17,0,-1);
		else if(a < 9)
			npMove(17,-1,0);
		else if(a < 10)
			npMove(17,0,-1);
		else if(a < 11)
			npMove(17,-1,0);
		else if(a < 12)
			npMove(17,0,-1);
		else if(a < 17)
			npMove(17,-1,0);

		if(a < 8)
			npMove(18,0,-1);
		else if(a < 9)
			npMove(18,-1,0);
		else if(a < 10)
			npMove(18,0,-1);
		else if(a < 11)
			npMove(18,-1,0);
		else if(a < 12)
			npMove(18,0,-1);
		else if(a < 13)
			npMove(18,-1,0);
		else if(a < 14)
			npMove(18,0,-1);
		else if(a < 17)
			npMove(18,-1,0);

		if(a == 2)
			npMove(0,1,0);
		if(a == 8)
			npMove(8,-1,0);
		if(a == 12)
			npMove(7,0,1);
		evFrame();
	}

	evFrameWait(1000);
	npDir(17,NORTH);
	evFrameWait(500);
	npDir(17,WEST);
	evFrameWait(500);
	npDir(17,SOUTH);
	evFrameWait(500);
	npDir(17,EAST);
	evFrameWait(500);

	//---にぎわいを
	mes.OpenMessage("Ending.msg",108);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(18,NORTH);
	evFrameWait(500);
	npDir(18,WEST);
	evFrameWait(500);
	npDir(18,SOUTH);
	evFrameWait(1000);
	npDir(18,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	//---新しい
	evFrameWait(1000);
	npDir(17,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---ライゼル！
	npPos(15,37,6);
	npDir(15,SOUTH);
	for(a = 0;a < 15;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(500);

	npMove(15,0,1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();

	//---きょろきょろ
	evFrameWait(500);
	npDir(15,EAST);
	evFrameWait(500);
	npDir(15,SOUTH);
	evFrameWait(250);
	npDir(15,WEST);
	evFrameWait(500);
	npDir(15,SOUTH);
	evFrameWait(500);
	//---ゲリラライブ
	mes.ReadDraw();

	npPos(17,37,20);
	npPos(18,38,22);
	for(a = 0;a < 6;a ++){
		if(a < 2)
			npMove(15,0,1);

		if(a < 5)
			npMove(17,0,-1);
		npMove(18,0,-1);

		evFrame();
	}
	//---宣言！
	evFrameWait(250);
	mes.ReadDraw(2);
	evFrameWait(500);

	//---振り向く
	npDir(4,EAST);
	evFrameWait(250);
	npMove(4,1,0);
	evFrame();
	evFrameWait(250);
	npDir(4,NORTH);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(19,NORTH);
	evFrameWait(250);
	for(a = 0;a < 3;a ++){
		npMove(19,0,-1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();

	//---ガゼール話しかける
	evFrameWait(250);
	for(a = 0;a < 5;a ++){
		npMove(17,0,-1);
		evFrame();
		if(a == 3)
			evFrameWait(750);
	}
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);

	mes.CloseMessage();


	//---------------------------------------------------------
	//---場面変わってディザ達の再会
	npPos(11,50,20);
	npDir(11,EAST);
	npPos(12,52,20);
	npDir(12,WEST);

	npPos(13,41,19);
	npDir(13,EAST);
	npPos(16,42,18);
	npDir(16,EAST);
	evScene(0,51,21);

	evFrameWait(2000);

	//---サヴィアー＆シンディ来る
	for(a = 0;a < 6;a ++){
		npMove(13,1,0);
		npMove(16,1,0);
		evFrame();
	}
	evFrameWait(500);

	mes.OpenMessage("Ending.msg",109);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(11,NORTH);
	evFrameWait(250);
	npDir(11,WEST);
	evFrameWait(250);

	for(a = 0;a < 4;a ++){
		npMove(13,1,0);
		evFrame();
	}
	npDir(11,NORTH);
	evFrameWait(250);
	npDir(13,SOUTH);
	evFrameWait(500);
	//---ご無沙汰
	mes.ReadDraw(2);

	for(a = 0;a < 6;a ++){
		if(a < 1)
			npMove(16,1,0);
		else if(a < 4)
			npMove(16,0,1);
		else
			npMove(16,1,0);
		if(a == 4)
			npDir(11,EAST);
		evFrame();
	}
	evFrameWait(250);
	npDir(16,NORTH);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(11,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(11,EAST);
	evFrameWait(1800);

	//---ユミ
	npPos(14,42,18);
	npDir(14,EAST);
	for(a = 0;a < 5;a ++){
		npMove(14,1,0);
		evFrame();
	}
	npDir(13,WEST);
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(250);

	//---なんだ、ユミか
	evFrameWait(250);
	npDir(11,NORTH);
	evFrameWait(250);
	npDir(11,WEST);
	evFrameWait(250);
	mes.ReadDraw();

	//---失礼
	evFrameWait(250);
	npDir(14,SOUTH);
	evFrameWait(250);
	for(a = 0;a < 2;a ++){
		npMove(14,0,1);
		evFrame();
	}
	evFrameWait(250);
	npDir(14,EAST);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(14,NORTH);
	evFrameWait(250);
	for(a = 0;a < 10;a ++){
		if(a < 2)
			npMove(14,0,-1);
		else if(a < 8)
			npMove(14,1,0);
		else if(a < 10)
			npMove(14,0,1);

		if(a == 5)
			npDir(11,NORTH);
		if(a == 7)
			npDir(11,EAST);
		evFrame();
	}
	npDir(13,SOUTH);
	evFrameWait(500);
	npDir(14,WEST);
	evFrameWait(500);

	//---早いよね
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(13,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw(2);

	//---アージェが覚醒しなくて
	evFrameWait(500);
	mes.ReadDraw();

	//---みんなか・・・・
	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw(2);

	//---寒い
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(13,EAST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(1000);
	npDir(13,SOUTH);

	mes.CloseMessage();

	//---そのことを知ったら
	evScene(6,15,15);
	evFrameWait(500);
	mes.OpenMessage("Ending.msg",110,0,2,1);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	mes.CloseMessage();

	evFadeOut();

	ef->SetMoveSpeed(old);

	return crevent_EndingMatsuri4();
}

//---エンディング・・・祭りと寒波
CREVENTLONG_ENDING_API int crevent_EndingMatsuri4(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	evScene(0,51,21);

	//---お待たせしました
	evFrameWait(2000);
	mes.OpenMessage("Ending.msg",111);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(11,NORTH);
	evFrameWait(250);
	npDir(11,WEST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	//---会場
	//16,53
	ef->SetMoveEnything(1);
	for(a = 32;a < 100;a ++)
		npDelete(a);

	for(a = 0;a < 33;a ++){
		mcMove(-1,1);
		evFrame();
	}
	for(a = 0;a < 2;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(500);

	evReloadMap(0);
	evScene(0,18,56);

	//---宣言
	evFrameWait(1000);
	mes.ReadDraw();

	//---もうエターナルに
	evFrameWait(500);
	for(a = 0;a < 3;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---クレイシヴは
	evFrameWait(500);
	npDir(36,EAST);
	evFrameWait(250);
	npDir(36,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();

	//---もうなにも
	evFrameWait(500);
	npDir(38,WEST);
	evFrameWait(500);
	mes.ReadDraw();

	//---さて
	evFrameWait(500);
	for(a = 0;a < 2;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	npDir(36,WEST);
	evFrameWait(250);
	npDir(36,NORTH);
	evFrameWait(250);
	npDir(38,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---ある方が
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();

	//---ライゼルさん！
	evFrameWait(500);
	npDir(56,WEST);
	evFrameWait(250);
	npDir(56,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	for(a = 0;a < 4;a ++){
		npMove(57,0,1);
		if(a == 1)
			npDir(56,WEST);
		if(a == 3)
			npDir(56,SOUTH);
		evFrame();
	}
	for(a = 0;a < 1;a ++){
		npMove(37,0,-1);
		evFrame();
	}
	//---おししょうさまー！
	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500);

	mes.CloseMessage();

	//---これで
	evScene(6,15,15);
	evFrameWait(500);
	mes.OpenMessage("Ending.msg",112,0,2,1);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();
	mes.CloseMessage();

	evFadeOut();

	return crevent_EndingMatsuri5();
}

//---エンディング・・・そして
CREVENTLONG_ENDING_API int crevent_EndingMatsuri5(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);
	evScene(0,30,35);
	npPos(11,30,46);
	npDir(11,NORTH);

	evFrameWait(500);
	for(a = 0;a < 11;a ++){
		npMove(11,0,-1);
		evFrame();
	}
	evFrameWait(500);

	mes.OpenMessage("Ending.msg",113);
	mes.ReadDraw();

	//---今頃
	evFrameWait(500);
	npMove(11,0,-1);
	evFrame();
	evFrameWait(500);
	npDir(11,WEST);
	evFrameWait(500);
	npDir(11,SOUTH);
	evFrameWait(500);

	mes.ReadDraw();
	evFrameWait(2000);

	//---よそう
	npDir(11,WEST);
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	int old = ef->SetMoveSpeed(2);
	for(a = 0;a < 7;a ++){
		npMove(11,-1,0);
		evFrame();
	}
	for(a = 0;a < 12;a ++){
		if(a < 5)
			npMove(11,-1,0);
		mcMove(-1,0);

		if(a == 8)
			npDir(11,NORTH);

		evFrame();
	}
	//---なんだこの焦げ跡？
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	npMove(11,0,-1);
	evFrame();
	evFrameWait(500);
	mes.ReadDraw();
	crmusicFadeOut();

	//---ルナン！！
	evFrameWait(4000);
	mes.ReadDraw();
	evFrameWait(500);
	crmusicStop();

	ef->SetMoveSpeed(old);

	mes.CloseMessage();


	//---思い出さないで
	evScene(6,15,15);
	evFrameWait(500);
	mes.OpenMessage("Ending.msg",114,0,2,1);
	mes.ReadDraw();
	mes.CloseMessage();

	evFadeOut();

	//---なんで
	evScene(0,18,35);
	evFrameWait(1000);
	mes.OpenMessage("Ending.msg",115);
	mes.ReadDraw();
	evFrameWait(500);
	npDir(11,EAST);
	evFrameWait(250);
	npDir(11,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---みんな集める

	evFrameWait(500);

	npPos(11,37,16);
	npDir(11,SOUTH);

	npPos(12,37,18);
	npDir(12,NORTH);
	npPos(13,38,17);
	npDir(13,NORTH);
	npPos(14,35,16);
	npDir(14,EAST);
	npPos(15,39,16);
	npDir(15,WEST);
	npPos(16,36,18);
	npDir(16,NORTH);
	npDelete(4);
	npDelete(5);
	npDelete(19);

	evScene(0,37,19);
	evFrameWait(500);
	mes.ReadDraw();
	//---そうだよ！
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(1000);
	mes.ReadDraw();
	evFrameWait(1000);
	mes.ReadDraw();
	//---いいか、
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.CloseMessage();

	//-------------------------------------
	//---そんなに必死に
	evScene(6,15,15);
	evFrameWait(500);
	mes.OpenMessage("Ending.msg",116,0,2,1);
	mes.ReadDraw();
	mes.CloseMessage();

	evFadeOut();


	//---わしらは
	evScene(0,37,19);
	evFrameWait(500);
	npDir(15,SOUTH);
	evFrameWait(500);
	npDir(15,WEST);
	evFrameWait(500);
	mes.OpenMessage("Ending.msg",117);
	mes.ReadDraw(2);

	//---光に包まれて・・・
	evFrameWait(500);
	mes.ReadDraw(2);

	//---オレは
	evFrameWait(500);
	mes.ReadDraw(2);

	//---なにも
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---アージェは失敗したんじゃない
	evFrameWait(1000);
	mes.ReadDraw(3);

	//---じゃあ、ルナンは・・・
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);
	mes.ReadDraw();

	//---ディザが歩き出す
	evFrameWait(2000);
	npDir(11,EAST);
	evFrameWait(250);
	npDir(11,NORTH);
	evFrameWait(250);

	for(a = 0;a < 2;a ++){
		npMove(11,0,-1);
		if(a == 1)
			npDir(14,NORTH);
		evFrame();
	}
	npDir(15,NORTH);
	evFrameWait(250);

	//---お兄ちゃん！
	mes.ReadDraw(2);
	//---決まってるだろ
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(500);

	mes.CloseMessage();


	//-------------------------------------
	//---わたしを？
	evScene(6,15,15);
	evFrameWait(500);
	mes.OpenMessage("Ending.msg",118,0,2,1);
	mes.ReadDraw();
	mes.CloseMessage();

	evFadeOut();

	evScene(0,37,19);
	evFrameWait(500);
	mes.OpenMessage("Ending.msg",119);
	mes.ReadDraw();
	//---そうだ
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();

	//---じゃあ、なんで
	evFrameWait(500);
	npDir(11,WEST);
	evFrameWait(250);
	npDir(11,SOUTH);
	evFrameWait(250);
	mes.ReadDraw(3);
	evFrameWait(500);

	mes.CloseMessage();

	//-------------------------------------
	//---もうやめて
	evScene(6,15,15);
	evFrameWait(500);
	mes.OpenMessage("Ending.msg",120,0,2,1);
	mes.ReadDraw();
	mes.CloseMessage();

	evFadeOut();

//	evScene(0,37,19);
//	return 1;
	return crevent_EndingMatsuri6();
}

typedef struct
{
	eistr *str;
	int color;
} cres_end;

static cres_end ending_str[] = 
{
	{ "Cresteaju Staff",	1},
	{ "Special Thanks",		1},
	{ "AyanamiFC",			0},
	{ "MAMEO",				0},
	{ "Keisuke Urano",		0},
	{ "Choyusha.F",			0},
	{ "Onimutu",			0},
	{ "Ken Kaneuchi",		0},
	{ "Kuro",				0},
	{ "Hidehiko Takahashi",	0},
	{ "Producer",			1},
	{ "Shou",				0},
	{ "Cresteaju Copyright(C) 2001 Shou/Shogo Kawai all rights reserved.",	2}
};

#define ENDSTR_MAX 13

#define ENDST_WAIT 0
#define ENDST_APPEARE 1
#define ENDST_SHOW 2
#define ENDST_DELETE 3
#define ENDST_START 4
#define ENDST_END 5

static eiTime endet;
void crevent_EndingCB(eiCell *pScrCell,int sx,int sy,int top_x,int top_y,int delta_t)
{
	static int prev_time,status = ENDST_START,str_pos = 0;
	static int txt_cx = 320,txt_cy = 360;
/*
	char s[80];
	sprintf(s,"%d :%d,%d",endet.Get() / 1000,status,str_pos);
	ew->lpCell[1]->DrawFillBox(0,0,100,16,0);
	ew->lpCell[1]->DrawText(s,0,0,ep->ToTextRGB(CRCOLOR_WHITE));
*/
	static int start_time = 65000,div_time = 30000,//32600,
		app_time = 4000,delstart_time = 20000,delete_time = delstart_time + 4000,
		OneceDrawFlag = 0;

	int now_time = endet.Get(),run_time,len;
	int col = 0,rate = 0;

	static int line_pos = 0,line_startpos,line_flag = 0,line_endpos,line_lcolor = 0;

	int r[4] = {255,192,236,255},
		g[4] = {236,255,255,255},
		b[4] = {224,224,240,255};

	switch(status){
	case ENDST_START:
		if(now_time >= start_time){
			//---動作開始
			status = ENDST_APPEARE;

			line_pos = 320 - strlen(ending_str[str_pos].str) * 4 - 16 + 1;
			line_startpos = line_pos;
			line_endpos = 320 + strlen(ending_str[str_pos].str) * 4 + 16 + 1;
			line_flag = 1;
			line_lcolor = 1;
		}
		break;

	//---文字出現中
	case ENDST_APPEARE:
		run_time = (now_time - start_time) - str_pos * div_time;

		if(run_time >= 2400){
			line_flag = 0;
		}
		if(line_flag){
			line_pos = line_startpos + 
				((line_endpos - line_startpos) * (run_time >= 1000 ? 1000 : run_time) / 1000);

			line_lcolor = 255 * (run_time >= 1200 ? run_time - 1200 : 0) / 1200;

			int x,col;
			for(x = line_startpos;x < line_pos;x ++){
				col = (255 - line_lcolor) * (x - line_startpos) / (line_pos - line_startpos)
					+ line_lcolor;

				ew->lpCell[1]->DrawFillBox(
					x,
					txt_cy + 17,
					x + 1,
					txt_cy + 17,
					ep->MakeRGB(
						col,
						col,
						col)
				);
			}
		} else {
			ew->lpCell[1]->DrawFillBox(
				line_startpos,
				txt_cy + 17,
				line_endpos,
				txt_cy + 17,
				ep->MakeRGB(255,255,255)
			);
		}

		if(run_time >= app_time){
			//---次の状態へ
			status = ENDST_SHOW;
			OneceDrawFlag = 0;
			break;
		}

		rate = run_time * 255 / app_time;
		if(rate >= 255)
			rate = 255;
		len = strlen(ending_str[str_pos].str);
		ew->lpCell[1]->DrawText(
			ending_str[str_pos].str,
			txt_cx - len * 4,
			txt_cy,
			ep->MakeTextRGB(
				r[ending_str[str_pos].color] * rate / 255,
				g[ending_str[str_pos].color] * rate / 255,
				b[ending_str[str_pos].color] * rate / 255
			)
		);

		break;

	//---文字表示中
	case ENDST_SHOW:
		run_time = (now_time - start_time) - str_pos * div_time;
		if(run_time >= delstart_time){
			//---次の状態へ
			status = ENDST_DELETE;
			OneceDrawFlag = 0;
			break;
		}

		if(OneceDrawFlag <= 1){
			rate = 255;
			len = strlen(ending_str[str_pos].str);
			ew->lpCell[1]->DrawText(
				ending_str[str_pos].str,
				txt_cx - len * 4,
				txt_cy,
				ep->MakeTextRGB(
					r[ending_str[str_pos].color] * rate / 255,
					g[ending_str[str_pos].color] * rate / 255,
					b[ending_str[str_pos].color] * rate / 255
				)
			);
			OneceDrawFlag ++;
		}

		break;

	//---文字消去中
	case ENDST_DELETE:
		run_time = (now_time - start_time) - str_pos * div_time;
		if(run_time >= delete_time){
			//---次の状態へ
			status = ENDST_WAIT;
			OneceDrawFlag = 0;
			break;
		}

		rate = 255 - ((run_time - delstart_time) * 255 / (delete_time - delstart_time));
		if(rate <= 0)
			rate = 0;
		len = strlen(ending_str[str_pos].str);
		ew->lpCell[1]->DrawText(
			ending_str[str_pos].str,
			txt_cx - len * 4,
			txt_cy,
			ep->MakeTextRGB(
				r[ending_str[str_pos].color] * rate / 255,
				g[ending_str[str_pos].color] * rate / 255,
				b[ending_str[str_pos].color] * rate / 255
			)
		);

		rate = 255 - (
			((run_time - delstart_time) >= 2000 ? 2000 : (run_time - delstart_time))
			* 255 / (2000));
		ew->lpCell[1]->DrawFillBox(
			line_startpos,
			txt_cy + 17,
			line_endpos,
			txt_cy + 17,
			ep->MakeRGB(
				255 * rate / 255,
				255 * rate / 255,
				255 * rate / 255
			)
		);

		break;

	//---待機
	case ENDST_WAIT:
		run_time = (now_time - start_time) - str_pos * div_time;
		if(run_time >= div_time){
			//---次の状態へ
			status = ENDST_APPEARE;
			OneceDrawFlag = 0;
			str_pos ++;
			if(str_pos >= ENDSTR_MAX){
				//---終わり
				status = ENDST_END;
				break;
			}
			line_pos = 320 - strlen(ending_str[str_pos].str) * 4 - 16 + 1;
			line_startpos = line_pos;
			line_endpos = 320 + strlen(ending_str[str_pos].str) * 4 + 16 + 1;
			line_flag = 1;
			line_lcolor = 1;
			break;
		}

		if(OneceDrawFlag <= 1){
			col = 0;
			len = strlen(ending_str[str_pos].str);
			ew->lpCell[1]->DrawFillBox(
				txt_cx - len * 4 - 20,
				txt_cy,
				txt_cx + len * 4 + 36,
				txt_cy + 18,
				ep->MakeRGB(0,0,0)
			);
			ew->lpCell[1]->DrawFillBox(
				line_startpos,
				txt_cy + 17,
				line_endpos,
				txt_cy + 17,
				ep->MakeRGB(
					0,0,0
				)
			);
/*			(eiGetSurfacePointer() + 3)->DrawFillBox(
				txt_cx - len * 4,
				txt_cy,
				txt_cx + len * 4 + 16,
				txt_cy + 18,
				ep->MakeRGB(0,0,0)
			);*/
			OneceDrawFlag ++;
		}

		break;
	}

	prev_time = now_time;
}

CREVENTLONG_ENDING_API int crevent_EndingMatsuri6(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	mcShow(0);

	//---ではどうやって
	evScene(0,37,19);
	evFrameWait(500);
	mes.OpenMessage("Ending.msg",121);
	mes.ReadDraw(2);

	//---やみくもに
	evFrameWait(500);
	npMove(12,0,-1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();

	//---どいつもこいつも
	evFrameWait(500);

	ef->SetFGCallback(crevent_EndingCB);
	endet.Reset();

	crmusicPlay(CRMUSIC_NEVEREND,0);
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);

	mes.CloseMessage();


	//-------------------------------------
	//---じゃあどうすれば
	evScene(6,15,15);
	//13
	if(crmusicGetTimeFromStart() < 13000){
		evFrameWait(500);
	} else {
		evField(0,1);
	}
	mes.OpenMessage("Ending.msg",122,0,2,1);
	mes.ReadDraw();
	mes.CloseMessage();


	//---自分から
	evScene(0,37,19);
	//17
	if(crmusicGetTimeFromStart() < 17000){
		evFrameWait(500);
	} else {
		evField(0,1);
	}
	mes.OpenMessage("Ending.msg",123);
	mes.ReadDraw(2);
	//28
	if(crmusicGetTimeFromStart() < 28000){
		evFrameWait(500);
	} else {
		evField(0,1);
	}
	mes.CloseMessage();


	//-------------------------------------
	//---そうか・・・
	evScene(6,15,15);
	//30
	if(crmusicGetTimeFromStart() < 30000){
		evFrameWait(500);
	} else {
		evField(0,1);
	}
	mes.OpenMessage("Ending.msg",124,0,2,1);
	mes.ReadDraw();
	//35
	if(crmusicGetTimeFromStart() < 35000){
		evFrameWait(500);
	} else {
		evField(0,1);
	}
	mes.ReadDraw();
	//39
	if(crmusicGetTimeFromStart() < 39000){
		evFrameWait(500);
	} else {
		evField(0,1);
	}
	mes.ReadDraw();
	mes.CloseMessage();


	//---どうするの？
	evScene(0,37,19);
	//42
	if(crmusicGetTimeFromStart() < 42000){
		evFrameWait(500);
	} else {
		evField(0,1);
	}
	mes.OpenMessage("Ending.msg",125);
	mes.ReadDraw();
	//45
	crmusicWait(43 * 1000);
	if(crmusicGetTimeFromStart() < 45000){
		evFrameWait(500);
	} else {
		evField(0,1);
	}
	//---願うんだよ
	mes.ReadDraw();
	//48
	if(crmusicGetTimeFromStart() < 48000){
		evFrameWait(500);
	} else {
		evField(0,1);
	}
	mes.CloseMessage();


	//-------------------------------------
	//---願う？
	evScene(6,15,15);
	//50
	if(crmusicGetTimeFromStart() < 50000){
		evFrameWait(500);
	} else {
		evField(0,1);
	}
	mes.OpenMessage("Ending.msg",126,0,2,1);
	mes.ReadDraw();
	crmusicWait(50 * 1000 + 500);
	mes.CloseMessage();


	//---もう一度会いたいってな！
	evScene(0,37,19);
	//53
	if(crmusicGetTimeFromStart() < 53000){
		evFrameWait(500);
	} else {
		evField(0,1);
	}
	npMove(11,0,1);
	evFrame();
	evFrameWait(250);
	mes.OpenMessage("Ending.msg",127);
	mes.ReadDraw();
	crmusicWait(55 * 1000);
	if(crmusicGetTimeFromStart() < 57000){
		evFrameWait(500);
	} else {
		evField(0,1);
	}
	mes.CloseMessage();

	//-------------------------------------
	//---わたしは、みんなのところに、帰りたい
	evScene(6,15,15);
	//58
	if(crmusicGetTimeFromStart() < 58000){
		evFrameWait(500);
	} else {
		evField(0,1);
	}
	mes.OpenMessage("Ending.msg",128,0,2,1);
	mes.ReadDraw();
	mes.CloseMessage();

	if(crmusicGetTimeFromStart() < 60000){
		evFadeOut(1000,RGB_MAKE(255,255,255));
	} else {
		evFadeOut(500,RGB_MAKE(255,255,255));
	}

//	return 1;

	return crevent_EndingWorldAfter();
}

//---エンディング・・・風は時を越えて
CREVENTLONG_ENDING_API int crevent_EndingWorldAfter(void)
{
	int a = 0,b = 0,c = 0,num = 1,t;
	CrMesManager mes;

	mcShow(0);

	int old = ef->SetMoveSpeed(2),ysize = 9;;
	ef->SetFieldSize(17,ysize);
	ef->SetFieldTop(
		320 - ((17 + 2) * 32 / 2),
		0);
//		240 - ((ysize + 2) * 32 / 2));

	t = endet.Get();
	if(t < 64 * 1000)
		et->Delay2(1000);

	crfieldChangeMap(10,0,1,0);

	t = endet.Get();
	if(t < 65 * 1000){
		crfieldChangeScene(0,167,160);//160,153
	} else {
		crfieldChangeScene(0,160,153);//160,153
	}

	ew->lpCell[1]->DrawFillBox(0,0,639,479,ep->ToRGB(CRCOLOR_BLACK));
	evFieldNoFlip(0,1);
//	evScene(0,170,163);

	//---
	ef->SetFieldTop(
		320 - ((crdataGetIniFile()->FieldSizeX + 2) * 32 / 2),
		240 - ((crdataGetIniFile()->FieldSizeY + 2) * 32 / 2));
	ef->SetFieldSize(crdataGetIniFile()->FieldSizeX,crdataGetIniFile()->FieldSizeY);
	eiDDSurface *pSurface = eiGetSurfacePointer();
	pSurface[3].DrawFillBox(0,0,639,479,ep->MakeRGB(0,0,0));
	evFadeIn(1000,RGB_MAKE(255,255,255));

	RECT rect = {32,32, 32 + 32 * 18 ,32 + 32 * ef->Field.ySize};
	crfieldSetFadeRect(&rect);
	crefectSetFadeCallBack(1);
	crmusicSetWaitCallback(1);

	ef->SetFieldSize(17,ysize);
	ef->SetFieldTop(
		320 - ((17 + 2) * 32 / 2),
		0);
//		240 - ((ysize + 2) * 32 / 2));

	//---ウェスカ
//---Cresteaju staff
	if(t < 65 * 1000){
		evFrameWait(500);
		for(a = 0;a < 14;a ++){
			if(a < 7)
				mcMove(-1,0);
			else
				mcMove(0,-1);
			evFrame();
		}
	}
	evFrameWait(500);

	//---女の子
	crfieldChangeMap(104,0,1,0);
	evScene(0,44,57);
	evFrameWait(500);

	for(a = 0;a < 10;a ++){
		npMove(42,0,-1);
		evFrame();
	}
	evFrameWait(500);
	npDir(42,WEST);
	evFrameWait(500);
	npDir(42,NORTH);
	evFrameWait(250);
	npDir(42,EAST);
	evFrameWait(500);
	npDir(42,NORTH);
	evFrameWait(500);

	mes.OpenMessage("Ending.msg",129,0,3);
	mes.lpWin[0]->SetWaitMode(1);
	mes.ReadDraw();
	//---酒場ね
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	for(a = 0;a < 12;a ++){
		npMove(42,0,-1);
		evFrame();
	}
	evFrameWait(500);

	//---酒場
	evScene(0,34,32);
	npPos(42,44,35);
	evFrameWait(500);
	for(a = 0;a < 10;a ++){
		npMove(42,-1,0);
		if(a == 8)
			npDir(41,NORTH);
		if(a >= 5)
			mcMove(0,1);
		evFrame();
	}
	//---よう
	evFrameWait(100);
	mes.ReadDraw();
//1:30
	crmusicWait((1 * 60 + 30) * 1000  -1600);

	evFrameWait(50);
	for(a = 0;a < 7;a ++){
		if(a < 1)
			npMove(42,-1,0);
		else if(a < 6)
			npMove(42,0,-1);
		else
			npMove(42,-1,0);
		if(a >= 0 && a <= 4)
			mcMove(0,-1);
		else if(a >= 5)
			mcMove(-1,0);
		evFrame();
	}
	evFrameWait(250);

//	mes.ReadDraw(8);
	mes.ReadDraw(6);

	//---わかりました
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(500);
	npDir(3,SOUTH);
	evFrameWait(250);
	npDir(3,WEST);
	evFrameWait(500);

	npMove(3,-1,0);
	evFrame();
	evFrameWait(500);

	//---聞きたいんだけど
	mes.ReadDraw(1);

	evFrameWait(500);
	npDir(3,SOUTH);
	evFrameWait(250);
	npDir(3,EAST);
	evFrameWait(500);

	npMove(3,1,0);
	evFrame();
	evFrameWait(500);

	//---リンゴ
	em->Put(31,30,2,59);
	evFrameWait(500);
	mes.ReadDraw(5);

	//---観光？
	evFrameWait(750);
	mes.ReadDraw(9);

	//---ごちそうさま
	evFrameWait(750);
	mes.ReadDraw(2);
//3:17
	crmusicWait((3 * 60 + 17) * 1000   -500 -5500);
	evFrameWait(500);
	npDir(42,SOUTH);
	evFrameWait(250);
	npDir(42,EAST);
	evFrameWait(250);

	//---外
	npPos(40,43,35);
	npPos(41,44,34);
	evScene(0,44,43);
	npPos(42,44,35);
	evFrameWait(500);

	for(a = 0;a < 5;a ++){
		npMove(42,0,1);
		evFrame();
	}
	//---待てよ
	evFrameWait(100);
	mes.ReadDraw();

	//---しかと
	for(a = 0;a < 1;a ++){
		npMove(42,0,1);
		evFrame();
	}
	evFrameWait(100);
	mes.ReadDraw();

	//---さらに
	for(a = 0;a < 1;a ++){
		npMove(42,0,1);
		evFrame();
	}
	//---頼むから
	evFrameWait(100);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(42,WEST);
	evFrameWait(250);
	npDir(42,NORTH);
	evFrameWait(250);

	//---ＳＳ
	for(a = 0;a < 5;a ++){
		if(a < 1)
			mcMove(0,-1);
		if(a < 4)
			npMove(40,0,1);
		npMove(41,0,1);
		evFrame();
	}
	evFrameWait(500);

	//---何？
	mes.ReadDraw(5);

	//---おじさん！？
	mes.ReadDraw();
	npMove(40,0,1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);

	//---
	evFrameWait(250);
	npDir(42,EAST);
	evFrameWait(250);
	npDir(42,SOUTH);
	evFrameWait(250);
	npMove(42,0,1);
	evFrame();

	//---待てよ！
	evFrameWait(250);
	mes.ReadDraw();

	evFrameWait(250);
	npDir(42,EAST);
	evFrameWait(250);
	npDir(42,NORTH);
	evFrameWait(250);
	mes.ReadDraw();

	//---実は
	evFrameWait(500);
	mes.ReadDraw(3);
	//---その名も
//	evFrameWait(1000);
	evFrameWait(250);
	npMove(41,0,1);
	evFrame();
//	evFrameWait(250);

	evFrameWait(250);
	npDir(41,WEST);
	evFrameWait(150);
	npDir(41,NORTH);
	evFrameWait(150);
	npDir(41,EAST);
	evFrameWait(150);
	npDir(41,SOUTH);
	evFrameWait(150);

	mes.ReadDraw();

	//---大爆笑
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(250);
	npMove(41,0,1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw();
	//---現在会員数
	evFrameWait(250);
	npMove(40,0,1);
	evFrame();
	evFrameWait(250);
	mes.ReadDraw(2);

	//---どこまで
	evFrameWait(500);
	mes.ReadDraw();
	evFrameWait(250);

	//---じゃあね
	npDir(42,EAST);
	evFrameWait(250);
	npDir(42,SOUTH);
	evFrameWait(250);
	mes.ReadDraw();
//4:51
	crmusicWait( (4 * 60 + 53) * 1000 -1500 -3000);
	evFrameWait(250);

	for(a = 0;a < 16;a ++){
		if(a < 2){
		} else if(a < 14)
			npMove(42,0,1);
		mcMove(0,1);
		evFrame();
	}
	//---そういえば
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);

	for(a = 0;a < 12 - 3;a ++){
		npMove(42,0,1);
		evFrame();
	}
	evFrameWait(250);


	//-----------------------------------------------------------
	//---アネート
	//8,9
	crfieldChangeMap(10,0,1,0);

	t = endet.Get();
	if(t < 314 * 1000){
		evScene(0,146 - 12,229 - 4);
	} else {
		evScene(0,146 ,229);
	}

	if(t < 314 * 1000){
		evFrameWait(500);
		for(a = 0;a < 16;a ++){
			if(a < 4)
				mcMove(0,1);
			else
				mcMove(1,0);
			evFrame();
		}
	}
	evFrameWait(500);

	crfieldChangeMap(105,0,1,0);

	//---
	t = endet.Get();
	if(t < 319 * 1000){
		evScene(0,12,15);
		for(a = 0;a < 10;a ++){
			if(a < 6)
				mcMove(0,-1);
			else
				mcMove(-1,0);
			evFrame();
		}
	} else {
		evScene(0,12 - 4,15 - 6);
	}
	//---ご苦労様です
//	evScene(0,8,9);
	evFrameWait(500);
	mes.ReadDraw(2);

	//---手紙
	evFrameWait(500);
	npDir(36,NORTH);
	evFrameWait(250);
	for(a = 0;a < 3;a ++){
		if(a < 2)
			npMove(36,0,-1);
		else
			npMove(36,1,0);
		evFrame();
	}
	evFrameWait(250);
	npDir(36,NORTH);
	evFrameWait(500);

	//---若い
	mes.ReadDraw();
	evFrameWait(500);
	npDir(37,NORTH);
	evFrameWait(500);
	mes.ReadDraw();

	//---すみません
	evFrameWait(500);
	npDir(36,WEST);
	evFrameWait(250);
	npDir(36,SOUTH);
	evFrameWait(500);
	mes.ReadDraw();
//5:51
	crmusicWait( (5 * 60 + 52) * 1000 -4500 -2500);

	evFrameWait(500);
	npDir(36,WEST);
	evFrameWait(250);
	for(a = 0;a < 3;a ++){
		if(a < 1)
			npMove(36,-1,0);
		else
			npMove(36,0,1);
		if(a == 2)
			npDir(37,WEST);
		evFrame();
	}
	evFrameWait(250);
	npDir(36,EAST);
	evFrameWait(500);

	//---せんぱいに
	mes.ReadDraw(5);

	//---ウワサは
	evFrameWait(500);
	mes.ReadDraw(3);
	//---温泉とか
	evFrameWait(500);
	mes.ReadDraw(7);
	evFrameWait(500);


	//---さて
	evScene(0,34,42);
	evFrameWait(250);
	npPos(37,34,32 + 3);
	for(a = 0;a < 10 - 3;a ++){
		npMove(37,0,1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw();

	evFrameWait(500);
	mes.ReadDraw();
//7:06
	crmusicWait((7 * 60 + 3) * 1000);

	evFrameWait(500);
	for(a = 0;a < 7;a ++){
		mcMove(0,1);
		if(a < 6)
			npMove(37,0,1);
		evFrame();
	}
	//---わたしの大好きな
	evFrameWait(1000);
	mes.ReadDraw();
	mes.CloseMessage();
	evFrameWait(500);

	for(a = 0;a < 10;a ++){
		npMove(37,0,1);
		evFrame();
	}
	evFrameWait(500);

//235,169,  188,131
	crfieldChangeMap(10,0,1,0);
	crfieldChangeScene(0,188,131);
	//---グラウンドシップ消す
	eiMapObject *pObject = em->GetObject(NP_GS_NUMBER);
	pObject->SetPos(0,0,1);
	pObject->SetDirection(DIR_NORTH);

	t = endet.Get();
	if(t < 439 * 1000){
		evScene(0,188 + 16,131 + 16);
		evFrameWait(500);
		for(a = 0;a < 16;a ++){
			mcMove(-1,-1);
			evFrame();
		}
	} else {
		evScene(0,188 ,131 );
	}
	evFrameWait(500);

	//---オイルレイク
	crfieldChangeMap(38,6,1,0);

	evReadObject(1,"Mika.acf");
	npPos(7,23,27);
	npDir(7,WEST);
	npDelete(6);

	t = endet.Get();
	if(t < 448 * 1000){
		evScene(6,25,44);

		evFrameWait(500);
//7:22
		crmusicWait((7 * 60 + 24) * 1000);

		for(a = 0;a < 19;a ++){
			if(a < 17)
				mcMove(0,-1);
			else
				mcMove(-1,0);
			evFrame();
		}
	} else {
		evScene(6,25 - 2,44 - 17);
	}

//	evFrameWait(1000);
	for(a = 0;a < 10;a ++){
		mcMove(-1,0);
		evFrame();
	}
	evFrameWait(250);
//7:31
	crmusicWait((7 * 60 + 33) * 1000);

	crefectSetFadeCallBack(0);
	ef->SetFGCallback(NULL);
	crfieldSetFadeRect(NULL);

	ef->SetFieldTop(
		320 - ((crdataGetIniFile()->FieldSizeX + 2) * 32 / 2),
		240 - ((crdataGetIniFile()->FieldSizeY + 2) * 32 / 2));
	ef->SetFieldSize(crdataGetIniFile()->FieldSizeX,crdataGetIniFile()->FieldSizeY);
	ef->SetMoveSpeed(old);
	crmusicSetWaitCallback(0);

	return crevent_EndingTheEnd();
}

//---エンディング・・・the end
CREVENTLONG_ENDING_API int crevent_EndingTheEnd(void)
{
	int a = 0;
	CrMesManager mes;
	eiTime let;

	mcShow(0);

	//---画像
	RECT rect = {0,0,640,480};
	eiCell src,bg;
	eiCell theend;
	char s[80];

	crefectScreenEfect_FadeOut(&rect,1000,RGB_MAKE(0,0,0),0);

	et->Delay2(500);

	sprintf(s,CR_DATADIR1"theend.acf",a);
	theend.ReadFile(s,CR_DATAFILE1,crdataGetFileMode());
//	theend.Init(16);
//	theend.Load();

	//---7:37
	crmusicWait( (7 * 60 + 35) * 1000);

	for(a = 1;a <= 11;a ++){
		let.Reset();

		sprintf(s,CR_DATADIR1"end%02d.acf",a);

		src.ReadFile(s,CR_DATAFILE1,crdataGetFileMode());

		//---復元
		decode_image(&bg,&src,NULL);
		src.Release();
		if(a == 11){
			bg.SetSurface(&rect,3,0);
			(eiGetSurfacePointer() + 3)->DrawFillBox(0,0,639,0,ep->ToRGB(CRCOLOR_BLACK));
			(eiGetSurfacePointer() + 3)->DrawFillBox(639,0,639,479,ep->ToRGB(CRCOLOR_BLACK));
			bg.Put(ew->lpCell[1],0,0);
		} else {
			bg.Put(ew->lpCell[1],0,0);
			ew->lpCell[1]->DrawFillBox(0,0,639,0,ep->ToRGB(CRCOLOR_BLACK));
			ew->lpCell[1]->DrawFillBox(639,0,639,479,ep->ToRGB(CRCOLOR_BLACK));
		}


		if(a == 1){
			crefectScreenEfect_FadeOut(&rect,1000,RGB_MAKE(0,0,0),1);
		} else {
			ew->Flip();
		}

		let.Wait2(650);
		if(a < 11)
			bg.Release();
	}
	et->Delay2(1000);

	//---THE ENDの文字
	crmusicWait( (7 * 60 + 49) * 1000);

	RECT endrect = {
		320 - theend.Data.xSize / 2,240 - theend.Data.ySize,
		320 + theend.Data.xSize / 2,240};
	crefectScreenEfect_FadeOut(&rect,2000,RGB_MAKE(255,255,255),0);
//	crbaseClearScreen(0x03);
	ew->lpCell[1]->DrawFillBox(0,0,639,479,ep->ToRGB(CRCOLOR_BLACK));
//	ew->lpCell[0]->DrawFillBox(0,0,639,479,ep->ToRGB(CRCOLOR_WHITE));
	theend.Put(ew->lpCell[1],320 - theend.Data.xSize / 2,240 - theend.Data.ySize);
	crefectScreenEfect_FadeOut(&rect,2000,RGB_MAKE(255,255,255),1);

/*	let.Reset();
	int t,rate;
	D3DTLVERTEX tex[4];
	
	int r = 255,
		g = 255,
		b = 255;

	crefectSetup3DEfect();
	memset(&tex[0],0,sizeof(tex));

	for(a = 0;a < 4;a ++){
		tex[a].dvRHW = 1;
		tex[a].dcSpecular = 0;
	}

	tex[0].dvSX = (float)(320 - theend.Data.xSize / 2);
	tex[0].dvSY = (float)(240 - theend.Data.ySize + 1);
	tex[0].dvSZ = (float)0.0f;
	tex[0].tu = 0;
	tex[0].tv = 0;

	tex[1].dvSX = (float)(320 + theend.Data.xSize / 2 - 1);
	tex[1].dvSY = (float)(240 - theend.Data.ySize + 1);
	tex[1].dvSZ = (float)0.0f;
	tex[1].tu = 1.0f;
	tex[1].tv = 0;

	tex[2].dvSX = (float)(320 - theend.Data.xSize / 2);
	tex[2].dvSY = (float)240;
	tex[2].dvSZ = (float)0.0f;
	tex[2].tu = 0;
	tex[2].tv = 1.0f;

	tex[3].dvSX = (float)(320 + theend.Data.xSize / 2 - 1);
	tex[3].dvSY = (float)240;
	tex[3].dvSZ = (float)0.0f;
	tex[3].tu = 1.0f;
	tex[3].tv = 1.0f;


	do {
		t = let.Get();
		if(t > 2000)
			t = 2000;

		rate = t * 255 / 2000;
		for(a = 0;a < 4;a ++){
			tex[a].dcColor = RGBA_MAKE(r,g,b,rate);
		}

		pViewport->ClearAll();
		bg.Put(ew->lpCell[1],0,0);

		//---描画開始
		eid3d->Begin();
		eid3d->BeginAlphaBlend();
		eid3d->SetTexture(&theend);
		eid3d->SetTextureColorkey(1);
		eid3d->SetDrawMode(EID3D_DRAWMODE_FILL);

		eid3d->DrawPrimitive( D3DPT_TRIANGLESTRIP,
			D3DFVF_TLVERTEX,&tex[0], 4, D3DDP_WAIT);

		//---描画終了
		eid3d->SetTextureColorkey(0);
		eid3d->SetTexture(NULL);
		eid3d->EndAlphaBlend();
		eid3d->End();

		if(eiGetEndThread() || crsysQuick()){
			break;
		}

		//---フリップ
		ew->Flip();
		if(!eiGetFullScreen()){
			eiSleep(1);
		}
	} while(t < 2000);*/
	
	et->Delay2(1000);
	crmusicWait( (7 * 60 + 54) * 1000);

	CrInput ci;

	ci.Get();
	ci.WaitAnykey();

	crefectScreenEfect_FadeOut(&rect,2000,RGB_MAKE(0,0,0),0);
	crbaseClearScreen(0x02);
	et->Delay2(1000);

	bg.Release();
	theend.Release();

	//---クリア情報書き込み
	crevent_WriteEndData();

	return MAINLOOP_ENDLOOP;
}
