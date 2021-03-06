/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrEventPart3.cpp ...Event functions

-----------------------------------------------------------*/


#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CREVENTPART3

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#include "CrBase.h"
#include "CrBattle.h"
#include "CrEvent.h"
#include "CrEvCom.h"

//---game info
#define CR_GAMEINFO_EXTERNPOINTER
#include "CrGameInfo.h"

CREVENTLONG1_API int creventFaymarru_Cresteaju(void);
CREVENTLONG1_API int creventChinoIseki(void);
CREVENTLONG1_API int creventMizunoIseki_Iriguchi(void);
CREVENTLONG1_API int creventMizunoIseki(void);
CREVENTLONG1_API int creventFaymarru_EternalTatemono(void);
CREVENTLONG1_API int creventCresMount_Seishintai(void);
CREVENTLONG1_API int creventCresMount_Lizel(void);
CREVENTLONG1_API int creventCresfield_LunarnsHome(void);
CREVENTLONG1_API int creventCresfield_Sakaba(void);
CREVENTLONG1_API int creventCresfieldLibrary(void);
CREVENTLONG1_API int creventCresfield_FukkatusaiZennya(void);
CREVENTLONG1_API int creventCresfield_Fukkatusai(void);
CREVENTLONG1_API int creventGenwaku_Rafia_Cresteaju(void);
CREVENTLONG2_API int creventCresfield_StartChapter2(void);
CREVENTLONG2_API int creventCresfield_NackCome(void);

//---
CREVENTLONG4_API int creventCresfield_KenkokusengenCindy(void);
CREVENTLONG4_API int creventCresfield_KenkokusengenZennya(void);
CREVENTLONG4_API int creventCresfield_Kenkokusengen(void);
CREVENTLONG4_API int creventCresfield_GotoTulia(void);


CREVENTPART3_API int creventCheckEvent_Part3(int event,int map,int scene)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;
	eiMapObject *pob = crfieldGetObjectPointer(event);

	CR_BATTLEINFO BatInfo;
	memset(&BatInfo,0,sizeof(BatInfo));

	if(map == 26){
		//---フェイマル
		if(scene == 0){
			if(200 <= event && event <= 202){
				mcDir(SOUTH);
				evMap(10,0,184,220);
			} else if(210 <= event && event <= 212
				&& evGet(52) == 0){
				return creventFaymarru_Cresteaju();
			} else if(event == 203 && evGet(57)){
				//---下水道
				mcDir(SOUTH);
				evMap(31,0,2,4);
				evSetGatePoint(39,14,SOUTH,26);//32,12
			} else if(event == 204 && evGet(57)){
				//---下水道
				mcDir(SOUTH);
				evMap(31,0,37,10);
				evSetGatePoint(39,14,SOUTH,26);//32,12
			} else if(event == 206 && (!AFTER_YUMI())){
				mes.FileMessage("Faymarru.msg",104);
				evFrameWait(250);
				mcMove(0,-1);
				evFrame();
				mcResetEvent();
			} else if(event == 207){
				//---一階へ
				mcDir(NORTH);
				evScene(1,2,11);
			} else if(event == 205){
				//---エターナル敷地Ｂ１へ
				mcDir(SOUTH);
				evScene(2,25,3);
			} else if(event == 280){
				//---エターナル敷地正面入り口Ｆ１へ
				mcDir(NORTH);
				evScene(3,13,22);
			} else if(event == 208){
				//---通せんぼ
				npTurn(27);
				evField(0,1);

				mes.FileMessage("Faymarru.msg",100,1);
				evField(0,1);
				if(crbaseSelectYesNo("アネートへ行きますか？",64,64) == 0){
					mcDir(SOUTH);
					evMap(21,0,57,13);
				} else {
					mcMove(0,1);
					evFrame();
					mcResetEvent();
					npReturn(27);
				}
			} else if(event == 209 && (!AFTER_YUMI())){
				//---エターナルの建物
				//---通せんぼ
				npTurn(18);
				evField(0,1);
				mes.FileMessage("Faymarru.msg",18,1);
				mcMove(0,1);
				evFrame();
				mcResetEvent();
				npReturn(18);
			} else if(event == 3){
				//---宿
				evYado(30,map,scene);
			} else if(event == 5){
				//---道具
				int ShopItem[] = {221,226,227,171,172,173,174,175,195,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 4){
				//---武器
				int ShopItem[] = {12,31,39,51,93,102,109,142,257,264,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 30){
				//---世界地図
				evShowWorldMap(184,220);
			} else if(6 <= event && event <= 50){
				//---町の人々
				int mes_scene = 1;


				npTurn(event);
				evField(0,1);

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;
				else if(evGet(57)){
					mes_scene = 2;
				}

				mes.FileMessage("Faymarru.msg",event,mes_scene);
				if(event == 24){
					//---エターナル説明大陸教会
					int ret;
					CRWIN_SELECTINFO info;
					CrSelectWindow win;
					memset(&info,0,sizeof(info));
					do {
						crbaseMenuReset();
						win.Create(64,64,18,9,"何を教えてもらいますか？",
							"エターナルって？;アズグレイって？;神って？;エターナルの仕組みって？;もういい;");
						win.Refresh();
						crbaseMenuStart();
						ret = win.Select(&info);
						if(ret == -1)
							ret = 4;
						evField(0,1);
						mes.FileMessage("Faymarru.msg",50,1 + ret);
					} while(ret != 4);
				}
				npReturn(event);
			} else if(event == 211){
			} else if(event == 214){
				//---タンス／本棚
				itemTansu(815,221);
			} else if(event == 215){
				//---タンス／本棚
				itemTansu(816,223);
			} else if(event == 216){
				//---タンス／本棚
				itemTansu(817,221);
			} else if(event == 217){
				//---タンス／本棚
				itemTansu(818,1);
			}
		} else if(scene == 1){
			if(event == 200){
				//---一階へ
				mcDir(NORTH);
				evScene(0,51,45);
			} else if(event == 201){
				//---タンス／本棚
				itemTansu(819,222);
			} else if(event == 4){
				//---シンディ
				npTurn(event);
				evField(0,1);
				mes.FileMessage("Faymarru.msg",54);
				npReturn(event);
			}
		} else if(scene == 2){
			//---エターナル敷地Ｂ１
			if(event == 200){
				//---外へ
				mcDir(SOUTH);
				evScene(0,60,13);
			} else if(event == 201){
				//---Ｆ１へ
				mcDir(SOUTH);
				evScene(3,1,2);
			} else if(event == 202){
				//---タンス／本棚
				itemTansu(820,221);
			}
		} else if(scene == 3){
			//---エターナル敷地Ｆ１
			if(event == 200 || event == 201){
				//---外へ
				mcDir(SOUTH);
				evScene(0,52,23);
			} else if(event == 202){
				//---Ｂ１へ
				mcDir(SOUTH);
				evScene(2,2,4);
			} else if(event == 203){
				//---Ｆ２へ
				mcDir(SOUTH);
				evScene(4,23,8);
			} else if(!evGet(58) && (event == 205 || event == 206)){
				//---とおせんぼ！
				evField(0,1);
				mes.FileMessage("Faymarru.msg",104);
				mcMove(0,-1);
				evFrame();
				mcResetEvent();
			} else if(event == 204){
				//---タンス／本棚
				itemTansu(821,213);
			} else if(event == 213){
				//---タンス／本棚
				itemTansu(885,224);
			} else if(7 <= event && event <= 10){
				//---町の人々
				int mes_scene = 1;

				npTurn(event);
				evField(0,1);

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				mes.FileMessage("Faymarru.msg",event + 60,mes_scene);
			}
		} else if(scene == 4){
			//---エターナル敷地Ｆ２
			if(event == 200){
				//---Ｆ１へ
				//---パターンリロード
				mcDir(SOUTH);
				crfieldChangeMap(26,3,1);
				evScene(3,24,8);
			} else if(event == 8){
				//---張り紙
				mes.FileMessage("Faymarru.msg",55);
			} else if((event == 202 || event == 203) && !evGet(58)){
				return creventFaymarru_EternalTatemono();
			} else if(event == 201){
				//---タンス／本棚
				itemTansu(822,241);
			} else if(event == 204){
				//---タンス／本棚
				itemTansu(886,225);
			} else if(9 <= event && event <= 11){
				int mes_scene = 1;

				npTurn(event);
				evField(0,1);

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				mes.FileMessage("Faymarru.msg",51 + event,mes_scene);
			} else if(event == 12){
				evShowWorldMap(184,220);
			}
		}
	} else if(map == 27){
		//---グラウンドシップ船着き場
		if(scene == 2){
			if(200 <= event && event <= 256){
				//---フィールドへ
				mcDir(SOUTH);
				evMap(10,0,208,200);
			} else if(257 <= event && event <= 259){
				//---船
				{
					int mes_scene = 1;

					if(AFTER_KOJINSAI())
						mes_scene = MESSAGE_KOJINSAI;
					else if(AFTER_YUMI())
						mes_scene = MESSAGE_YUMI;

					evField(0,1);
					mes.FileMessage("GSFaymarru.msg",100,mes_scene);
					evFrameWait(250);
					mcMove(1,0);
					evFrame();
					mcResetEvent();
				}
			} else if(event == 5){
				evField(0,1);
				mes.FileMessage("GSFaymarru.msg",event);
			}
		}
	} else if(map == 28){
		//---地の遺跡
		if(scene == 0){
			if(200 <= event && event <= 201){
				//---フィールドへ
				mcDir(SOUTH);
				evMap(10,0,191,171);
			} else if(203 <= event && event <= 205 && !evGet(53)){
				//---がいこつ！
				//---バトル
				CR_BATTLEINFO BattleInfo;
				memset(&BattleInfo,0,sizeof(BattleInfo));
				BattleInfo.MapNumber = crfieldGetMapNumber();
				BattleInfo.Music = CRMUSIC_BATTLE;
				BattleInfo.Enemy[0].Enemy = 51;
				BattleInfo.Enemy[0].x = 4;
				BattleInfo.Enemy[0].y = 6;
				BattleInfo.Enemy[1].Enemy = 51;
				BattleInfo.Enemy[1].x = 6;
				BattleInfo.Enemy[1].y = 7;
				BattleInfo.Enemy[2].Enemy = -1;
				BattleInfo.ScreenEfect = CRINTOBAT_NORMAL;
				evField(0,1);
				if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
					return 0;
				}

				npPos(3,15,20);
				npPos(4,14,19);
				npPos(5,15,21);
				npPos(6,16,21);
				for(a = 3;a <= 6;a ++){
					npDir(a,NORTH);
				}
				mcShow(0);
				evScene(0,15,21);

				mes.OpenMessage("ChinoIseki.msg",100);
				evFrameWait(1000);
				mes.ReadDraw();
				evFrameWait(500);
				mes.ReadDraw();

				evFrameWait(250);
				npDir(3,WEST);
				evFrameWait(100);
				npDir(4,EAST);
				evFrameWait(100);
				npDir(6,WEST);
				evFrameWait(100);
				npDir(3,SOUTH);
				evFrameWait(100);
				npDir(4,SOUTH);
				evFrameWait(250);

				mes.ReadDraw();
				evFrameWait(1000);
				mes.ReadDraw(13);
				evFrameWait(250);

				mes.CloseMessage();

				mcShow(1);
				for(a = 3;a <= 6;a ++){
					npPos(a,0,0);
					npShow(a,0);
				}
				evScene(0,15,21);
				evSet(53,1);
			} else if(event == 202){
				//---Ｆ１へ
				mcDir(NORTH);
				evScene(1,10,37);
			} else if(event == 0){
				//---宝箱
				itemBox(516,181,event);
			}
		} else if(scene == 1){
			if(200 <= event && event <= 201){
				//---外へ
				mcDir(SOUTH);
				evScene(0,15,16);
			} else if(event == 202){
				//---Ｆ２へ
				mcDir(SOUTH);
				//---ボタンリセット
				evSet(45,0);
				evSet(46,0);
				evSet(47,0);
				evScene(2,1,1);
			} else if(event == 0){
				//---宝箱
				itemBox(517,221,event);
			} else if(event == 4){
				//---宝箱
				itemBox(518,223,event);
			}
		} else if(scene == 2){
			if(200 == event){
				//---Ｆ１へ
				mcDir(SOUTH);
				evScene(1,10,3);//172,199
			} else if(event == 201){
				//---Ｆ３へ
				mcDir(SOUTH);
				evScene(3,9,27);
			} else if(event == 202){
				mes.FileMessage("ChinoIseki.msg",10);
			} else if(1 <= event && event <= 3){
				//---カラーボタン
				mes.FileMessage("ChinoIseki.msg",11 + (event - 1));
				evField(0,1);
				if(evGet(45 + (event - 1))){
					//---押されていたら
					if(crbaseSelectYesNo("スイッチをオフにしますか？",64,64) == 0){
						evSet(45 + (event - 1),0);
					}
					evFrameWait(250);
				} else {
					//---押されていなかったら
					if(crbaseSelectYesNo("スイッチをオンにしますか？",64,64) == 0){
						evSet(45 + (event - 1),1);
					}
					evFrameWait(250);
				}

				int color = (evGet(45) << 0) | (evGet(46) << 1) | (evGet(47) << 2);
				int change[] = {0,1,5,7, 6,2,0};

				if(color >= 4){
					npPos(5,15,2);
					npShow(4,0);
					npDir(5,color - 4);
				} else {
					npPos(4,15,2);
					npShow(5,0);
					npDir(4,color);
				}

				if(!evGet(45) && evGet(46) && evGet(47)){
					evSet(48,1);
					em->Put(10,11,1,64);
					evFrameWait(500);
					crsoundPlay(CRSOUND_ATACK4);
					mes.FileMessage("ChinoIseki.msg",14);
				}
			} else if(event == 0){
				//---宝箱
				itemBox(519,222,event);
			} else if(event == 6){
				//---宝箱
				itemBox(520,217,event);
			}
		} else if(scene == 3){
			if(200 == event){
				//---Ｆ２へ
				mcDir(NORTH);
				evScene(2,10,23);
			} else if(201 <= event && event <= 202 && !evGet(54)){
				//---地の遺跡最上階
				return creventChinoIseki();
			}
		}
	} else if(map == 29){
		//---水の遺跡
		if(scene == 0){
			if(200 <= event && event <= 202){
				mcDir(SOUTH);//--14,32
				evMap(10,0,172,199);
			} else if(208 <= event && event <= 210 && !evGet(55)){
				return creventMizunoIseki_Iriguchi();
			} else if(event == 203){
				//---Ｆ２へ
				mcDir(SOUTH);
				if(evGet(50) && evGet(51)){
					evScene(1,31,17);
				} else {
					evScene(2,31,17);
				}
			} else if(event == 204){
				//---To 1
				crfieldChangePlane(1);
			} else if(event == 205){
				//---To 3
				crfieldChangePlane(3);
			} else if(event == 206){
				//---To 1
				crfieldChangePlane(1);
			} else if(event == 207){
				//---To 3
				crfieldChangePlane(3);
			} else if(event == 0){
				//---宝箱
				itemBox(521,222,event);
			} else if(event == 2){
				//---宝箱
				itemBox(522,223,event);
			}
		} else if(scene == 1){
			if(event == 200){
				mcDir(SOUTH);
				evScene(0,25,22);
			} else if(event == 201){
				//---小部屋１
				mcDir(SOUTH);
				evScene(4,7,6);
			} else if(event == 202){
				//---小部屋２
				mcDir(SOUTH);
				evScene(5,3,10);
			} else if(event == 203){
				//---Ｆ３
				mcDir(SOUTH);
				evScene(3,11,2);
			} else if(event == 204){
				//---To 1
				crfieldChangePlane(1);
			} else if(event == 205){
				//---To 3
				crfieldChangePlane(3);
			} else if(event == 206){
				//---To 1
				crfieldChangePlane(1);
			} else if(event == 207){
				//---To 3
				crfieldChangePlane(3);
			} else if(event == 0){
				//---宝箱
				itemBox(523,175,event);
			}
		} else if(scene == 2){
			if(event == 200){
				mcDir(SOUTH);
				evScene(0,25,22);
			} else if(event == 201){
				//---小部屋１
				mcDir(SOUTH);
				evScene(4,7,6);
			} else if(event == 202){
				//---小部屋２
				mcDir(SOUTH);
				evScene(5,3,10);
			}
		} else if(scene == 3){
			if(event == 200){
				//---Ｆ３
				mcDir(SOUTH);
				evScene(1,2,4);
			} else if(201 <= event && event <= 202 && !evGet(56)){
				return creventMizunoIseki();
			} else if(event == 5){
				//---宝箱
				itemBox(524,221,event);
			} else if(event == 8){
				//---宝箱
				itemBox(525,257,event);
			} else if(event == 10){
				//---宝箱
				itemBox(526,200,event);
			} else if(event == 13){
				//---宝箱
				itemBox(527,217,event);
			}
		} else if(scene == 4){
			if(event == 200){
				//---小部屋１
				mcDir(SOUTH);
				if(evGet(50) && evGet(51)){
					evScene(1,20,4);
				} else {
					evScene(2,20,4);
				}
			} else if(event == 201 && !evGet(50)){
				mes.FileMessage("MizunoIseki.msg",10);
				evField(0,1);
				if(crbaseSelectYesNo("ボタンを押しますか？",64,64) == 0){
					evSet(50,1);
				}
				if(evGet(50) && evGet(51)){
					crsoundPlay(CRSOUND_WATER);
					evFrameWait(250);
					mes.FileMessage("MizunoIseki.msg",11);
				}
			}
		} else if(scene == 5){
			if(event == 200){
				//---小部屋２
				mcDir(SOUTH);
				if(evGet(50) && evGet(51)){
					evScene(1,5,23);
				} else {
					evScene(2,5,23);
				}
			} else if(event == 201 && !evGet(51)){
				mes.FileMessage("MizunoIseki.msg",10);
				evField(0,1);
				if(crbaseSelectYesNo("ボタンを押しますか？",64,64) == 0){
					evSet(51,1);
				}
				if(evGet(50) && evGet(51)){
					crsoundPlay(CRSOUND_WATER);
					evFrameWait(250);
					mes.FileMessage("MizunoIseki.msg",11);
				}
			}
		}
	}
	return 1;
}

CREVENTPART3_API int creventCheckEvent_Part3_2(int event,int map,int scene)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;
	eiMapObject *pob = crfieldGetObjectPointer(event);

	CR_BATTLEINFO BatInfo;
	memset(&BatInfo,0,sizeof(BatInfo));

	if(map == 30){
		//---クレスフィールド高地
		if(scene == 0){
			if(200 <= event && event <= 206){
				//---フィールドへ
				mcDir(WEST);
				evMap(10,0,212,202);
			} else if(event == 207 || event == 208){
				//---２へ
				mcDir(NORTH);
				evScene(1,7,62);
			} else if(event == 0){
				//---宝箱
				itemBox(530,217,event);
			} else if((209 <= event && event <= 212) && evGet(63)
				&& evGet(79) != 1){
				//---クリアパス
				evField(0,1);
				if(crbaseSelectYesNo("クレスフィールド側へ移動しますか？",64,64) == 0){
					mcDir(SOUTH);
					evMap(10,0,219,200);
					return 0;
				} else {
					evSet(79,1);
				}
			}
		} else if(scene == 1){
			if(200 == event || event == 201){
				//---１へ
				mcDir(SOUTH);
				evScene(0,13,10);
				evSet(79,1);
			} else if(202 == event || event == 203){
				//---３へ
				mcDir(NORTH);
				evScene(2,5,26);
			} else if(event == 0){
				//---宝箱
				itemBox(531,227,event);
			}
		} else if(scene == 2){
			if(200 == event || event == 201){
				//---２へ
				mcDir(SOUTH);
				evScene(1,36,9);
			} else if(202 == event || event == 203){
				if(!evGet(59)){
					//---精神体
					return creventCresMount_Seishintai();
				} else {
					//---宿場へ
					mcDir(EAST);
					evScene(3,9,15);
				}
			}
		} else if(scene == 3){
			//---宿場
			if(200 == event || event == 201){
				//---３へ
				mcDir(WEST);
				evScene(2,60,38);
			} else if(202 == event || event == 203){
				//---４へ
				mcDir(EAST);
				evScene(4,9,10);
				evSet(79,2);
			} else if((204 == event || event == 205) && !evGet(60)){
				//---ライゼル再び！
				return creventCresMount_Lizel();
			} else if(0 <= event && event <= 2){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);

				mes.FileMessage("CresfieldMount.msg",event,mes_scene);
				if(event == 0){
					evYado(49);
				}

				npReturn(event);
			}
		} else if(scene == 4){
			//---４へ
			if(200 == event || event == 201){
				//---３へ
				mcDir(WEST);
				evScene(3,54,21);
			} else if(202 <= event && event <= 204){
				//---フィールドへ
				mcDir(EAST);
				evMap(10,0,219,200);
			} else if((205 <= event && event <= 208) && evGet(63)
				&& evGet(79) != 2){
				//---クリアパス
				evField(0,1);
				if(crbaseSelectYesNo("フェイマル側へ移動しますか？",64,64) == 0){
					mcDir(SOUTH);
					evMap(10,0,212,202);
					return 0;
				} else {
					evSet(79,2);
				}
			}
		}
	} else if(map == 31){
		//---下水道
		if(scene == 0){
			if(event == 200){
				//---フェイマルへ
				mcDir(SOUTH);
				evMap(26,0,39,14);
			} else if(event == 201){
				//---B2へ
				mcDir(SOUTH);
				evScene(1,13,2);
			} else if(event == 202){
				//---B2へ
				mcDir(SOUTH);
				evScene(1,3,25);
			} else if(event == 203){
				//---フェイマルへ
				if(evGet(58) && (!AFTER_YUMI())){
					mes.FileMessage("FaymarruGesuido.msg",100);
				} else {
					mcDir(SOUTH);
					evMap(26,0,63,14);
				}
			} else if(event == 0){
				//---宝箱
				itemBox(528,227,event);
			} else if(event == 1){
				//---宝箱
				itemBox(529,213,event);
			}
		} else if(scene == 1){
			if(event == 200){
				//---B1へ
				mcDir(SOUTH);
				evScene(0,17,3);
			} else if(event == 201){
				//---B1へ
				mcDir(SOUTH);
				evScene(0,5,30);
			}
		}
	} else if(map == 32){
		//---クレスフィールド
		if(scene == 0){
			if(200 <= event && event <= 204){
				//---フィールドへ
				if(evGet(137) && !evGet(138)){
					evField(0,1);
					mes.FileMessage("Cresfield.msg",131);
					mcMove(0,1);
					evFrame();
					mcResetEvent();
				} else if(!evGet(61)){
					evField(0,1);
					mes.FileMessage("Cresfield.msg",105);
					if(evGet(62)){
						mes.FileMessage("Cresfield.msg",107);
					}
					evFrameWait(250);
					mcMove(0,1);
					evFrame();
					mcResetEvent();
				} else {
					mcDir(SOUTH);
					evMap(10,0,235,194);
				}
			} else if(event == 27){
				//---世界地図
				evShowWorldMap(235,194);
			} else if(
				((3 <= event && event <= 35))
				&& (event != 23 && event != 24 && event != 25)){
				int mes_scene = 3;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);

				if(evGet(136)){
					//---ＧＳ手に入れた後
					mes.FileMessage("Cresfield.msg",event,mes_scene);
				} else if(evGet(71)){
					//---２部
					mes.FileMessage("Cresfield.msg",event,2);
				} else {
					mes.FileMessage("Cresfield.msg",event);
				}

				npReturn(event);
			} else if(65 <= event && event <= 66){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);

				mes.FileMessage("Cresfield.msg",event - 65 + 31,mes_scene);

				npReturn(event);
			} else if((211 <= event && event <= 220)
				&& !evGet(62)){
				//---ルナンの家の前
				return creventCresfield_LunarnsHome();
			} else if(event == 207 && (!AFTER_YUMI())){
				//---通せんぼ
				npTurn(15);
				evField(0,1);
				mes.FileMessage("Cresfield.msg",15);
				evFrameWait(250);
				mcMove(0,-1);
				evFrame();
				mcResetEvent();
				npReturn(15);
			} else if((208 <= event && event <= 210)
				 && (!AFTER_YUMI())){
				//---ルナンが家に入りたくない
				evField(0,1);
				mes.FileMessage("Cresfield.msg",106);
				if(!evGet(61)){
					mes.FileMessage("Cresfield.msg",107);
				}
				evFrameWait(250);
				mcMove(0,1);
				evFrame();
				mcResetEvent();
			} else if(event == 205){
				//---酒場
/*				if(evGet(137) && !evGet(138)){
					//---シンディとの再会、建国宣言前夜
					return creventCresfield_KenkokusengenZenya();
				} else */if(!evGet(61) && evGet(62)){
					//---町を巡った感想
					return creventCresfield_Sakaba();
				} else {
					mcDir(SOUTH);
					evScene(4,12,2);
				}
			} else if(event == 225){
				//---議会２階へ
				mcDir(NORTH);
				evScene(1,14,17);
			} else if(event == 206){
				//---宿屋
				mcDir(SOUTH);
				evScene(3,14,2);
			} else if(event == 221){
				//---ルナン２階
				mcDir(SOUTH);
				evScene(5,2,2);
			} else if(event == 23){
				//---宿
				if(evGet(137) && !evGet(138)){
					//---建国宣言前、シンディと会う前
					evField(0,1);
					mes.FileMessage("Cresfield.msg",1);
					evField(0,1);
				} else if(evGet(138) && !evGet(139)){
					//---建国宣言前
					evField(0,1);
					mes.FileMessage("Cresfield.msg",133);
					evField(0,1);
					if(crbaseSelectYesNo("泊まりますか？",64,64) == 0){
						return creventCresfield_KenkokusengenZennya();
					}
				} else if(!evGet(61)){
					//---止まれましぇん
					evField(0,1);
					mes.FileMessage("Cresfield.msg",109);
				} else if(evGet(65) == 1){
					evField(0,1);
					mes.FileMessage("Cresfield.msg",111);
					evYado(30,map,scene,creventCresfield_FukkatusaiZennya);
				} else {
					evYado(30,map,scene);
				}
			} else if(event == 24){
				//---道具
				int ShopItem[] = {221,226,227,171,172,173,174,175,177,200,195,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 25){
				//---武器
				int ShopItem[] = {3,13,40,52,94,103,110,143,149,258,265,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 222){
				//---タンス／本棚
				itemTansu(823,218);
			} else if(event == 223){
				//---タンス／本棚
				itemTansu(824,227);
			} else if(event == 224){
				//---タンス／本棚
				itemTansu(825,226);
//----------------------------------------３部
			} else if(event == 226){
				//---タンス／本棚
				itemTansu(887,228);
			} else if(event == 227){//---ルナンの家１階
				//---タンス／本棚
				itemTansu(888,39);
			}
		} else if(scene == 1){
			//---議会２階
			if(event == 200){
				//---１階へ
				mcDir(SOUTH);
				evScene(0,44,63);
			} else if(event <= 4){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);

				mes.FileMessage("Cresfield.msg",event + 80,mes_scene);
			} else if(event == 201){
				//---タンス／本棚
				itemTansu(889,182);
			}
		} else if(scene == 3){
			//---宿屋２階
			if(event == 200){
				//---一階へ
				if(evGet(140) && !evGet(141)){
					//---ツーリアへ
					return creventCresfield_GotoTulia();
				} else if(evGet(66) == 2){
					//---復活祭！！
					return creventCresfield_Fukkatusai();
				} else {
					mcDir(SOUTH);
					evScene(0,56,12);
				}
			} else if(event == 201){
				//---タンス／本棚
				itemTansu(826,232);
			} else if((event == 202 || event == 203) && evGet(77) == 1){
				//---第２部スタートナックが来る
				return creventCresfield_NackCome();
/*				evField(0,1);
				npDir(1,EAST);
				mes.FileMessage("Cresfield.msg",120);

				mcMove(0,1);
				evFrame();
				mcResetEvent();
*/
			} else if((event == 202 || event == 203) && evGet(66) == 1){
				//---復活祭
				evField(0,1);
				npDir(1,EAST);
				evFrameWait(500);
				mes.FileMessage("Cresfield.msg",65);
				evFrameWait(250);
				if(crbaseSelectYesNo("復活祭へ行きますか？",64,64) == 0){
					evSet(66,2);
					for(a = 0;a <= 4;a ++){
						npPos(a,0,0);
						npShow(a,0);
					}
					mcDir(SOUTH);
					evScene(3,16,4);
				} else {
					mcMove(0,1);
					evFrame();
					mcResetEvent();
				}
			} else if((event == 204 || event == 205)
				&& (1 <= evGet(139) && evGet(139) <= 2)){
				evFrameWait(250);
				mes.FileMessage("Cresfield.msg",136);
				mcMove(0,1);
				evFrame();
				mcResetEvent();
			} else if(event <= 20 && evGet(139) == 1){
				//---建国宣言
				npTurn(event);
				evField(0,1);
				mes.FileMessage("Cresfield.msg",event + 60,16);
				evSet(139,2);
				npReturn(event);
			} else if(event <= 20 && evGet(139) == 2){
				//---建国宣言
				npTurn(event);
				//---クレイシヴ現る！
				return creventCresfield_Kenkokusengen();
			} else if(event <= 20){
				//---復活祭メンバー
				npTurn(event);
				evField(0,1);
				mes.FileMessage("Cresfield.msg",event + 60,evGet(72 + (event - 1)) + 1);
				if(evGet(72 + (event - 1)) < 4){
					evSet(72 + (event - 1),evGet(72 + (event - 1)) + 1);
				}
				npReturn(event);
			}
		} else if(scene == 4){
			//---酒場
			if(event == 200){
				mcDir(SOUTH);
				evScene(0,54,12);
			} else if(event == 9 && evGet(137) && !evGet(138)){
				return creventCresfield_KenkokusengenCindy();
			} else if(1 <= event && event <= 20){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("Cresfield.msg",40 + event,mes_scene);

				npReturn(event);
			}
		} else if(scene == 5){
			//---ルナン２階
			if(event == 200){
				mcDir(SOUTH);
				evScene(0,10,23);
			} else if(event == 202){
				//---タンス／本棚
				itemTansu(890,213);
			} else if(event == 201 && !evGet(179)){
				//---ルナン、ベッド下
				evField(0,1);
				mes.FileMessage("Cresfield.msg",144);
				critemAddItem(208);
				evSet(179,1);
			}
		}
	} else if(map == 33){
		//---古代図書館
		if(scene == 0){
			if(200 <= event && event <= 201){
				//---フィールドへ
				mcDir(SOUTH);
				evMap(10,0,232,169);
			} else if(event <= 50){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("Library.msg",event,mes_scene);
				npReturn(event);
			} else if(event == 202){
				//---通せんぼ！
				int xavier = 0;
				for(a = 0;a < MEMBER_MAX;a ++){
					if(crcharaGetPartyMember(a) != NULL){
						if(crcharaGetPartyMember(a)->Who() == 4)
							xavier = 1;
					}
				}
				if(!evGet(61) || !xavier/*サヴィアーいない*/){
					npTurn(0);
					evField(0,1);
					mes.FileMessage("Library.msg",event);
					evFrameWait(250);
					mcDir(WEST);
					evFrameWait(250);
					mes.FileMessage("Library.msg",100);

					evFrameWait(250);
					mcMove(0,1);
					evFrame();
					mcResetEvent();
					npReturn(0);
				} else if(!evGet(64)){
					return creventCresfieldLibrary();
				}
			}
		}
	} else if(map == 34){
		//---幻惑の樹海
		if(scene == 0){
			//---森１
			if(event == 200){
				//---フィールドへ
				mcDir(NORTH);
				evMap(10,0,252,215);
			} else if(event == 201){
				//---森２へ
				mcDir(SOUTH);
				evScene(1,4,14);
			} else if(event == 202){
				//---森５へ
				mcDir(WEST);
				evScene(4,21,19);
			} else if(event == 0){
				//---回復の泉
				evKaifukunoIzumi();
			} else if(event == 1){
				//---宝箱
				itemBox(532,223,event);
			}
		} else if(scene == 1){
			//---森２
			if(event == 200){
				//---森１へ
				mcDir(NORTH);
				evScene(0,19,51);
			} else if(event == 201){
				//---森３へ
				mcDir(SOUTH);
				evScene(2,50,9);
			} else if(event == 0){
				//---宝箱
				itemBox(533,224,event);
			}
		} else if(scene == 2){
			//---森３
			if(event == 200){
				//---森２へ
				mcDir(NORTH);
				evScene(1,62,64);
			} else if(event == 201){
				//---森４へ
				mcDir(WEST);
				evScene(3,43,50);
				crfieldChangeMapMusic();
			} else if(event == 0){
				//---宝箱
				itemBox(534,24,event);
			}
		} else if(scene == 3){
			//---森４
			if(event == 200){
				//---森３へ
				mcDir(EAST);
				evScene(2,9,19);
				crfieldChangeMapMusic();
			} else if(event == 201){
				//---遺跡へ
				mcDir(NORTH);
				evMap(35,0,6,27);
				evSetGatePoint(252,215,NORTH);

				if(!evGet(76)){
					evFrameWait(1000);
					mes.FileMessage("GenwakuForest.msg",104);
					evSet(76,1);
				}
			} else if(event == 202 && !evGet(68)){
				evFrameWait(1000);
				mes.FileMessage("GenwakuForest.msg",101);
				evSet(68,1);
			} else if(event == 203 && !evGet(69)){
				evFrameWait(700);
				mes.FileMessage("GenwakuForest.msg",102);
				evSet(69,1);
			} else if((event == 204 || event == 205) && !evGet(70)){
				evFrameWait(500);
				mes.FileMessage("GenwakuForest.msg",103);
				evSet(70,1);
			}
		} else if(scene == 4){
			//---森５
			if(event == 200){
				//---森１へ
				mcDir(EAST);
				evScene(0,9,32);
			} else if(event == 0){
				//---宝箱
				itemBox(535,185,event);
			}
		}
	} else if(map == 35){
		//---保存装置
		if(scene == 0){
			//---Ｂ１
			if(event == 200){
				//---幻惑の樹海へ
				if(evGet(166) && !evGet(160)){
					//---記憶の中
					mcDir(SOUTH);
					if(evGet(167)){
						evMap(74,3,24,11);
					} else {
						//---まぶしい！
						crfieldChangeMap(74,3,1,0);
						crfieldChangeScene(3,24,11);
						evFieldNoFlip(0,1);
						evFadeIn(1000,RGB_MAKE(255,255,255));

						evFrameWait(250);
						mes.FileMessage("Fillgalt.msg",104);
						evSet(167,1);
					}
				} else {
					mcDir(SOUTH);
					evMap(34,3,24,11);
				}
			} else if(event == 201){
				//---Ｂ２へ
				mcDir(SOUTH);
				evScene(1,9,2);
			}
		} else if(scene == 1){
			//---Ｂ２
			if(event == 200){
				//---Ｂ１へ
				mcDir(SOUTH);
				evScene(0,8,3);
			} else if(event == 201){
				//---Ｂ３へ
				mcDir(SOUTH);
				evScene(2,3,3);
			}
		} else if(scene == 2){
			//---Ｂ３
			if(event == 200){
				//---Ｂ２へ
				mcDir(SOUTH);
				evScene(1,20,22);
			} else if(event == 201){
				//---Ｂ４へ
				mcDir(SOUTH);
				evScene(3,5,5);
			}
		} else if(scene == 3){
			//---Ｂ４
			if(event == 200){
				//---Ｂ２へ
				mcDir(SOUTH);
				evScene(2,6,6);
			} else if(event == 201){
				//---Ｂ４へ
				mcDir(SOUTH);
				evScene(4,8,37);
			}
		} else if(scene == 4){
			//---Ｂ５
			if(event == 200){
				//---Ｂ４へ
				mcDir(SOUTH);
				evScene(3,3,3);
			} else if(event == 201 && !evGet(71)){
				//---ラーフィア見張り
				int ret = creventGenwaku_Rafia_Cresteaju();

				if(ret != 1)
					return ret;
				//---第２部へ
				creventCresfield_StartChapter2();
			}
		}
	}
	return 1;
}
