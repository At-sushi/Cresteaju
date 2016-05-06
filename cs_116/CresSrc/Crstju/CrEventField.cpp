/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrEventField.cpp ...Event functions

-----------------------------------------------------------*/


#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CREVENTFIELD

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#include "CrBase.h"
#include "CrBattle.h"
#include "CrEvent.h"
#include "CrEvCom.h"

//---game info
#define CR_GAMEINFO_EXTERNPOINTER
#include "CrGameInfo.h"

static eiTime evtime;

CREVENTFIELD_API int creventCheckEvent_Field2(int event,int map,int scene);

CREVENTLONG1_API int creventAneat_Nack(void);
CREVENTLONG1_API int creventFeymarru_Asgray(void);
CREVENTLONG1_API int creventCresfield_Return(void);
CREVENTLONG1_API int creventCresfield_FukkatusaiShirase(void);
CREVENTLONG2_API int creventMarks_Follne(void);
CREVENTLONG3_API int creventAlsia_Satogaeri(void);
CREVENTLONG3_API int creventGreatCrater_Visit(void);
CREVENTLONG3_API int creventCenow_Visit(void);

//---
CREVENTLONG4_API int creventCresfield_Kenkokusengenmae(void);
CREVENTLONG4_API int creventTuria_FirstVisit(void);

CREVENTLONG5_API int creventSilverStar_First(void);
CREVENTLONG5_API int creventSunpias_First(void);
CREVENTLONG5_API int creventShinkiro_TobiraHiraku(void);

CREVENTLONG6_API int creventWasurerareta_First(void);
CREVENTLONG6_API int creventRyusa_TasukenikitaHatu(void);

//---
CREVENTLONG9_API int crevent_WescaLuxthereFirstVisit(void);

//---フィールドでのイベント
CREVENTFIELD_API int creventCheckEvent_Field(int event,int map,int scene)
{
	int a = 0,b = 0,c = 0;
	CrMesManager mes;
//	eiMapObject *pob = crfieldGetObjectPointer(event);

//	CR_BATTLEINFO BatInfo;
//	memset(&BatInfo,0,sizeof(BatInfo));

	if(map == 10){
		//---フィールド
		if(scene == 0){
			if(event == NP_GS_NUMBER){
				//---グラウンドシップ乗り込み
				evChangeGroundShip();

			} else if(event == 200){
				//---ウェスカ東船着き場
				crfieldChangeMapS(13,0);
				crfieldChangeSceneS(0,23,31);
			} else if(0 <= event && event <= 10){
				//---立て札
				mes.FileMessage("Field.msg",event);
			} else if(14 <= event && event <= 15){
				//---立て札
				mes.FileMessage("Field.msg",event);
			} else if(event == 201){
				//---ウェスカ
				if(AFTER_KOJINSAI() && !evGet(231)){
					//---ウェスカの亡霊
					return crevent_WescaLuxthereFirstVisit();
				} else {
					mcDir(NORTH);
					evMap(14,0,44,58);
				}
			} else if(205 <= event && event <= 213){
				//---ウェスカ北の森
				mcDir(NORTH);
				evMap(18,0,6,27);//7,8);
				evSetGatePoint(151,143,SOUTH);
			} else if(event == 202){
				//---橋
				if(evGet(15) == 0){
					//---洪水
					evMap(17,1,28,15);
				} else {
					evMap(17,0,35,16);
				}
			} else if(event == 204){
				//---橋
				evMap(17,0,11,16);
			} else if(event == 203){
				//---セーネ
				mcDir(SOUTH);
				evMap(16,0,28,6);
				if(evGet(19) == 1 && evGet(32) == 0){
					//---土砂撤去終了
					evSet(32,1);
					npDir(6,EAST);
					evFrameWait(500);
					for(a = 0;a < 6;a ++){
						if(a < 3)
							npMove(6,1,0);
						else
							npMove(6,0,-1);
						evFrame();
					}
					evFrameWait(250);
					mes.FileMessage("Sene.msg",101);
					evFrameWait(250);
					npDir(6,WEST);
					evFrameWait(250);
					npMove(6,-1,0);
					evFrame();
				}
			} else if(214 <= event && event <= 222){
				//---セーネ北西の森
				mcDir(NORTH);
				evMap(19,0,45,52);
				evSetGatePoint(92,165,SOUTH);
			} else if(event == 223){
				//---アネートへの山道
				mcDir(NORTH);
				evMap(20,0,11,16);
				evSetGatePoint(110,203,NORTH);
				evSet(78,0);
			} else if(event == 224){
				//---アネートへの山道
				mcDir(NORTH);
				evMap(20,5,10,17);
				evSetGatePoint(112,209,SOUTH);
				evSet(78,0);
			} else if(event == 225){
				//---アネート
				if(evGet(43) == 0 && evGet(42) == 1){
					creventAneat_Nack();
				} else {
					mcDir(NORTH);
					evMap(21,0,34,49);
					if(evGet(33) == 0){
						evSet(33,1);
						evFrameWait(1000);
						mes.FileMessage("Aneat.msg",101);
					}
				}
			} else if(event == 226){
				//---ドーグリ
				mcDir(SOUTH);
				evMap(22,0,22,1);
			} else if(event == 227){
				//---ＳＳ本部
				mcDir(NORTH);
				evMap(23,0,8,23);
				evSetGatePoint(117,231,NORTH);
				//---117,231
			} else if(evGet(27) && 228 <= event && event <= 239){
				//---ドーグリ南の遺跡
				mcDir(EAST);
				evMap(24,0,9,4);
				evSetGatePoint(129,258,NORTH);
			} else if(event == 240){
				//---フェイマル
				mcDir(WEST);
				evMap(26,0,70,34);
				if(evGet(54) && evGet(56) && !evGet(57)){
					creventFeymarru_Asgray();
				}
//				evMap(30,0,11,10);
			} else if(event == 241){
				//---地の遺跡
				mcDir(NORTH);
				evMap(28,0,25,52);
				evSetGatePoint(191,171,SOUTH);
			} else if(event == 242){
				//---水の遺跡
				mcDir(NORTH);
				evMap(29,0,14,30);
				evSetGatePoint(172,199,SOUTH);//32,12
			} else if(event == 243){
				//---グラウンドシップ船着き場水の遺跡
				mcDir(WEST);
				evMap(27,2,32,19);
			} else if(event == 244){
				//---クレスフィールド高地
				mcDir(NORTH);
				evMap(30,0,17,72);
				evSetGatePoint(212,202,SOUTH);
				evSet(79,0);
				if(!evGet(58)){
					//---フェイマルクリアまでは越えられない
					evField(0,1);
					mes.FileMessage("CresfieldMount.msg",102);
					mcMove(0,1);
					evFrame();
					mcDir(WEST);
					evMap(10,0,212,202);
				}
			} else if(event == 245){
				//---クレスフィールド高地（クレスフィールド側）
				mcDir(NORTH);
				evMap(30,4,32,71);
				evSetGatePoint(219,200,SOUTH);
				evSet(79,0);
				if(evGet(136) && !evGet(140)){
					//---建国宣言時
					evField(0,1);
					mes.FileMessage("CresfieldMount.msg",104);
					mcMove(0,1);
					evFrame();
					mcDir(EAST);
					evMap(10,0,219,200);
				} else if(evGet(64) && !evGet(71)){
					//---図書館～１部終了まで戻れない
					evField(0,1);
					mes.FileMessage("CresfieldMount.msg",103);
					mcMove(0,1);
					evFrame();
					mcDir(EAST);
					evMap(10,0,219,200);
				}
			} else if(event == 246){
				//---クレスフィールド
				if(evGet(136) && !evGet(137)){
					//---建国宣言前、初
					return creventCresfield_Kenkokusengenmae();
				} else if(evGet(66) == 3 && !evGet(71)){
					//---復活祭中
					evField(0,1);
					mes.FileMessage("Cresfield.msg",114);
				} else if(evGet(64) && !evGet(65)){
					//---図書館行ってきたなら復活祭の知らせ
					return creventCresfield_FukkatusaiShirase();
				} else if(!evGet(63)){
					//---クレスフィールド最初
					creventCresfield_Return();
				} else {
					mcDir(SOUTH);
					evMap(32,0,37,7);
				}
			} else if(event == 247){
				//---古代図書館
				if(evGet(66) == 3 && !evGet(71)){
					//---復活祭中
					evField(0,1);
					mes.FileMessage("Cresfield.msg",115);
				} else {
					mcDir(NORTH);
					evMap(33,0,14,30);
				}
			} else if(event == 248){
				//---地下道
//				245,193 ,248
				mcDir(NORTH);
				evMap(36,0,9,24);
				evSetGatePoint(245,193,SOUTH);
			} else if(249 <= event && event <= 274){
				//---幻惑の森
				if(evGet(66) == 3){
					//---復活祭はじまったあと
					mcDir(SOUTH);
					evMap(34,0,65,8);
					evSetGatePoint(252,215,NORTH);

					if(!evGet(67)){
						mes.OpenMessage("GenwakuForest.msg",100);
						evFrameWait(500);
						mcDir(WEST);
						evFrameWait(500);
						mes.ReadDraw(2);
						evFrameWait(500);
						mcDir(SOUTH);
						evFrameWait(500);
						mes.ReadDraw();
						evFrameWait(500);
						mes.CloseMessage();
						evSet(67,1);
					}
				}
			} else if(event == 275){
				//---トレイア
				mcDir(SOUTH);
				evMap(37,0,53,2);
			} else if(event == 276){
				//---中央山脈
				if(evGet(83)){
					if(AFTER_KOJINSAI()){
						//---降神祭後
						if(crbaseSelectYesNo("中央部まで移動しますか？",64,64)
							== 0){
							mcDir(NORTH);
							evMap(38,6,25,42);
							return 1;
						}
					} else {
						if(crbaseSelectYesNo("オイルレイクまで移動しますか？",64,64)
							== 0){
							mcDir(NORTH);
							evMap(38,3,25,42);
							return 1;
						}
					}
				}
				mcDir(NORTH);
				evMap(38,0,29,52);
				evSetGatePoint(188,131,SOUTH);
			} else if(event == 277){
				//---中央山脈（北側）
				if(evGet(83)){
					if(AFTER_KOJINSAI()){
						//---降神祭後
						if(crbaseSelectYesNo("中央部まで移動しますか？",64,64)
							== 0){
							mcDir(SOUTH);
							evMap(38,6,30,10);
							return 1;
						}
					} else {
						if(crbaseSelectYesNo("オイルレイクまで移動しますか？",64,64)
							== 0){
							mcDir(SOUTH);
							evMap(38,3,30,10);
							return 1;
						}
					}
				}
				mcDir(SOUTH);
				evMap(38,5,33,8);
				evSetGatePoint(190,109,NORTH);
			} else if(event == 326){
				//---ノーステリアグラウンドシップ船着き場
				mcDir(NORTH);
				evMap(50,0,11,20);
			} else if(event == 278){
				//---ノーステリア
				mcDir(NORTH);
				evMap(39,0,31,56);

				if(evGet(99) && !evGet(104)){
					//---ノーステリアの盗賊
					evSet(104,1);
					evFrameWait(250);
					mes.FileMessage("NorthTereia.msg",100);
				}

				//---自由市売り物設定
				evSet(236,0);
				if(AFTER_YUMI() && eiRnd(1000) < 100
					&& !evGet(237)){
					//---さびた剣
					evSet(236,1);
				}
				// 40 % 30% 15% ,9%  ,3% 2% 0.9% 0.1%  
				for(a = 0;a < 5;a ++){
					int rnd = eiRnd(1000);

					if(rnd < 400){
						evSet(85 + a, 0);
					} else if(rnd < 700){
						evSet(85 + a, 1);
					} else if(rnd < 850){
						evSet(85 + a, 2);
					} else if(rnd < 940){
						evSet(85 + a, 3);

					} else if(rnd < 970){
						evSet(85 + a, 4);
					} else if(rnd < 990){
						evSet(85 + a, 5);
					} else if(rnd < 999){
						evSet(85 + a, 6);
					} else {
						evSet(85 + a, 7);
					}
				}

			} else if(event == 279){
				//---ダイ
				mcDir(NORTH);
				evMap(40,0,34,51);
			} else if(event == 280){
				//---マークス
				mcDir(SOUTH);
				evMap(41,0,26,1);
				//---フォールン登場
				if(evGet(114) && !evGet(119)){
					return creventMarks_Follne();
				}
			} else if(event == 281){
				//---ノーステリアの洞窟
				mcDir(SOUTH);
				evMap(44,0,9,5);
			} else if(event == 282){
				//---ノーステリアの遺跡
				mcDir(NORTH);
				evMap(46,0,20,37);
			} else if(event == 283){
				//---全ウ連
				mcDir(NORTH);
				evMap(49,0,12,25);
			} else if(event == 284){
				//---橋
				if(evGet(120) && !evGet(118)){
					//---マークスクリア前、ライゼル失踪中
					evField(0,1);
					mes.FileMessage("Field.msg",105);
					evField(0,1);
					mcMove(-1,0);
					evFrame();
					mcResetEvent();
				} else {
					mcDir(EAST);
					evMap(47,0,11,15);
				}
			} else if(event == 285){
				//---橋
				if(evGet(133) && !evGet(136)){
					//---橋通行できません
					evField(0,1);
					mes.FileMessage("Field.msg",101);
					evField(0,1);
					mcMove(0,1);
					evFrame();
					mcResetEvent();
				} else {
					mcDir(WEST);
					evMap(47,0,35,15);
				}
			} else if(event == 286){
				//---アルシア
				if(!evGet(121)){
					//---里帰り
					creventAlsia_Satogaeri();
				} else {
					mcDir(WEST);
					evMap(51,0,80,48);
				}
			} else if(event == 333){
				//---アルシア湖岸洞窟
				mcDir(SOUTH);
				evMap(53,0,19,4);
			} else if(327 <= event && event <= 332
				&& !evGet(121)){
				//---アルシアよっていこうぜ
				evField(0,1);
				mes.FileMessage("Field.msg",100);
				evField(0,1);
				mcMove(0,-1);
				evFrame();
				mcResetEvent();
			} else if(287 <= event && event <= 326){
				//---大クレーター
				if(!evGet(123) && !evGet(124)){
					creventGreatCrater_Visit();
				} else {
					if(287 <= event && event <= 296){
						mcDir(SOUTH);
						evMap(52,0,32,3);
					} else if(297 <= event && event <= 304){
						mcDir(WEST);
						evMap(52,0,62,31);
					} else if(305 <= event && event <= 315){
						mcDir(NORTH);
						evMap(52,0,31,63);
					} else {
						mcDir(EAST);
						evMap(52,0,2,31);
					}
				}
			} else if(334 <= event && event <= 338){
				//---セノウ
				if(!evGet(124)){
					//---セノウの初イベント
					creventCenow_Visit();
				} else if(event == 334){
					mcDir(NORTH);
					evMap(54,0,28,45);
				}
			} else if(339 == event){
				//---ゼビアマイン
				mcDir(NORTH);
				evMap(55,0,31,61);
			} else if(event == 340){
				//---ゼビアマイン船着き場
				mcDir(NORTH);
				evMap(58,0,11,20);
			}
		}
	}
	return creventCheckEvent_Field2(event,map,scene);
}

//---フィールドでのイベント
CREVENTFIELD_API int creventCheckEvent_Field2(int event,int map,int scene)
{
	int a = 0,b = 0,c = 0;
	CrMesManager mes;

	if(map == 10){
		//---フィールド
		if(scene == 0){
			if(341 <= event && event <= 344){
				//---ツーリア
				if(evGet(154) && !evGet(157)){
					//---ツーリア脱出からジーダイ渡るまで入れない
					evField(0,1);
					mes.FileMessage("Field.msg",103);
					evField(0,1);
//					mcMove(0,1);
//					evFrame();
//					mcResetEvent();
				} else if(!evGet(142)){
					return creventTuria_FirstVisit();
				} else {
					mcDir(SOUTH);
					evMap(61,0,19,1);
				}
			} else if(345 == event){
				//---ツーリア港
				mcDir(EAST);
				evMap(62,0,6,19);
			} else if(346 == event){
				//---豆腐職人の家
				mcDir(NORTH);
				evMap(65,0,7,11);
			} else if(347 == event){
				//---忘れ人の家
				mcDir(NORTH);
				evMap(66,0,7,10);
			} else if(348 == event){
				//---ジーダイ港
				mcDir(WEST);
				evMap(67,0,44,22);
			} else if(349 == event){
				//---ジーダイ洞窟南
				mcDir(SOUTH);
				evMap(68,0,4,44);
			} else if(350 == event){
				//---ジーダイ洞窟北
				mcDir(SOUTH);
				evMap(68,2,5,3);
			} else if(351 == event){
				//---記憶の遺跡
				mcDir(NORTH);
				evMap(69,0,23,59);
//---------------------------------------------------------
//---３部
			} else if(
				NP_GS_CANTNUMBER == event
				&& evGet(170) && !evGet(171) /*ユミの過去まで*/){
				//---バイツＧＳ
				//ＧＳの中へ
				mcDir(NORTH);
				evMap(59,0,13,11);
			} else if(352 <= event && event <= 357){
				//---まだ進めない！
				if(!evGet(173)){
					evField(0,1);
					mes.FileMessage("Field.msg",104);
					mcMove(0,-1);
					evFrame();
					mcResetEvent();
				}
			} else if(358 == event){
				//---バイツ
				mcDir(NORTH);
				evMap(75,0,23,36);
			} else if(359 == event){
				//---神の山
				mcDir(NORTH);
				evMap(76,0,26,34);
			} else if(360 == event){
				//---シルバースター
				if(evGet(174) == 0){
					return creventSilverStar_First();
				} else {
					mcDir(NORTH);
					evMap(77,0,30,44);
				}
			} else if(361 == event){
				//---サンピアス
				if(evGet(174) == 3 && !evGet(176)){
					return creventSunpias_First();
				} else {
					mcDir(NORTH);
					evMap(78,0,27,43);
				}
			} else if(362 == event){
				//---大神殿
				mcDir(NORTH);
				evMap(80,0,24,59);
			} else if(363 == event){
				//---流砂の遺跡
				if(evGet(209) && !evGet(213)){
					//---助けに来た、初
					return creventRyusa_TasukenikitaHatu();
//					crfieldChangeMap(81,0,1,1);
//					evScene(0,16,23);
				} else if(!evGet(181) && !evGet(209)){
					//---初めて（南部大雪原クリアまで）
					crfieldChangeMap(81,0,1,1);
					mcShow(0);
					npPos(0,15,22);
					npDir(0,NORTH);
					npPos(1,14,23);
					npDir(1,NORTH);
					npPos(2,18,22);
					npDir(2,NORTH);
					npPos(3,17,23);
					npDir(3,NORTH);
					evScene(0,16,23);
					evFrameWait(250);
					mes.FileMessage("RyusanoIseki.msg",100);
					evFrameWait(250);
					mcShow(1);
					mcDir(NORTH);
					for(a = 0;a <= 4;a ++){
						npDelete(a);
					}
					evScene(0,15,22);

					evSet(181,1);
				} else {
					mcDir(NORTH);
					evMap(81,0,16,23);
				}
			} else if(364 == event){
				//55,27
				//---蜃気楼の塔
				if(evGet(190) && !evGet(198)){
					return creventShinkiro_TobiraHiraku();
				} else {
					mcDir(NORTH);
					evMap(82,0,28,47);
				}
			} else if(365 == event){
				//---ユールクレイラ
				mcDir(EAST);
				evMap(84,0,2,20);

			} else if(366 == event){
				//---滅びの遺跡
				mcDir(SOUTH);
				evMap(85,0,22,1);
			} else if(367 == event){
				//---忘れられた遺跡
				if(!evGet(206)){
					return creventWasurerareta_First();
				} else {
					mcDir(SOUTH);
					evMap(86,0,7,3);
				}
			} else if(368 == event){
				//---南部大雪原の家
				mcDir(SOUTH);
				evMap(87,0,10,14);
			} else if(369 == event){
				//---小島の洞窟
				mcDir(SOUTH);
				evMap(88,0,4,5);
			} else if(370 == event){
				//---格闘場
				if(evGet(154) && !evGet(157)){
					//---ツーリア脱出からジーダイ渡るまで入れない
					evField(0,1);
					mes.FileMessage("Field.msg",103);
					evField(0,1);
				} else {
					mcDir(NORTH);
					evMap(89,0,12,25);
				}
			} else if(371 == event){
				//---竜の祠
				mcDir(NORTH);
				evMap(90,0,7,20);
			} else if(372 == event){
				//---野原のタンス
				mcDir(NORTH);
				evMap(91,0,11,17);
			} else if(event == 373){
				//---中央山脈、別の場所
				mcDir(NORTH);
				evMap(38,11,16,29);
			} else if(event == 374){
				//---毛糸屋さん
				mcDir(NORTH);
				evMap(97,0,11,13);
			} else if(event == 375){
				//---トレイアの洞窟
				mcDir(NORTH);
				evMap(98,0,11,27);
			}
		}
	}

	return 1;
}
