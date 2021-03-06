/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrEventPart5.cpp ...Event functions

-----------------------------------------------------------*/


#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CREVENTPART5

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#include "CrBase.h"
#include "CrBattle.h"
#include "CrEvent.h"
#include "CrEvCom.h"

//---game info
#define CR_GAMEINFO_EXTERNPOINTER
#include "CrGameInfo.h"

CREVENTLONG3_API int creventAlsia_DizzasHome(void);
CREVENTLONG3_API int creventZevia_BuyMineSuit(int event);
CREVENTLONG3_API int creventMine_DizzaHead(void);
CREVENTLONG3_API int creventMine_FasraCrear(void);
CREVENTLONG4_API int creventMine_Xavier(void);
CREVENTLONG4_API int creventAlsia_IntoLake(void);
CREVENTLONG4_API int creventAlsia_GetGS(void);

CREVENTLONG5_API int creventZeviaMine_DiyamaOve(void);
CREVENTLONG5_API int creventAlsia_World(void);

CREVENTLONG9_API int crevent_CenowRarfia(void);


CREVENTPART5_API int creventCheckEvent_Part5(int event,int map,int scene)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;
	eiMapObject *pob = crfieldGetObjectPointer(event);

	CR_BATTLEINFO BatInfo;
	memset(&BatInfo,0,sizeof(BatInfo));

	if(map == 51){
		//---アルシア
		if(scene == 0){
			if(200 <= event && event <= 203){
				//---フィールドへ
				if(evGet(121) && !evGet(122)){
					evField(0,1);
					mes.FileMessage("Alsia.msg",101);
					evField(0,1);
					mcMove(-1,0);
					evFrame();
					mcResetEvent();
				} else {
					mcDir(SOUTH);
					evMap(10,0,190,57);
				}
			} else if(210 <= event && event <= 212
				&& evGet(121) && !evGet(122)){
				//--ディザの家
				return creventAlsia_DizzasHome();
			} else if(event == 204){
				//---宿屋２階
				mcDir(NORTH);
				evScene(1,17,12);
			} else if(event == 205){
				//---ディザ２階
				mcDir(SOUTH);
				evScene(2,2,2);
			} else if(event == 206){
				//---長老２階
				if(evGet(199) && !evGet(203)){
					//---蜃気楼の塔クリア＆ワールドまだ
					return creventAlsia_World();
				} else {
					mcDir(NORTH);
					evScene(3,12,11);
				}
			} else if(event == 0){
				//---宿
				if(evGet(121) && !evGet(122)){
					evField(0,1);
					mes.FileMessage("Alsia.msg",103);
				} else {
					evYado(166,map,scene);
				}
			} else if(event == 1){
				//---万屋道具
				int ShopItem[] = {221,222,226,227,236,195,171,172,173,174,200,201,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 20){
				//---世界地図
				evShowWorldMap(190,57);
			} else if(event <= 30){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);

				if(event == 21){
					//---アルシア瓦版
				}
				mes.FileMessage("Alsia.msg",event,mes_scene);
				npReturn(event);
			} else if(event == 207){
				//---タンス／本棚
				itemTansu(849,223);
			} else if(event == 208){
				//---タンス／本棚
				itemTansu(850,226);
			} else if(event == 209){
				//---タンス／本棚
				itemTansu(851,222);
			}
		} else if(scene == 1){
			//---宿屋２階
			if(event == 200){
				//---１階へ
				mcDir(SOUTH);
				evScene(0,75,66);
			} else if(event <= 10){
				int mes_scene = 1;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("Alsia.msg",event + 50,mes_scene);
				npReturn(event);
			}
		} else if(scene == 2){
			//---ディザの家２階
			if(event == 200){
				//---１階へ
				mcDir(SOUTH);
				evScene(0,30,59);
			} else if(event <= 10){
				int mes_scene = 1;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("Alsia.msg",event + 60,mes_scene);
				npReturn(event);
			} else if(event == 201){
				//---タンス／本棚
				itemTansu(852,23);
			} else if(event == 202){
				//---タンス／本棚
				itemTansu(853,203);
			}
		} else if(scene == 3){
			//---長老２階
			if(event == 200){
				//---１階へ
				mcDir(SOUTH);
				evScene(0,30,23);
			} else if(event <= 10){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("Alsia.msg",event + 70,mes_scene);
				npReturn(event);
			} else if(event == 201){
				//---タンス／本棚
				itemTansu(854,167);
			}
		}
	} else if(map == 52){
		//---大クレーター
		if(scene == 0){
			if(200 <= event && event <= 262){
				//---フィールドへ227,54 ,235,61,  219,61 , 227,69
				mcDir(NORTH);
				evMap(10,0,227,54);
			} else if(263 <= event && event <= 323){
				mcDir(EAST);
				evMap(10,0,235,61);
			} else if(324 <= event && event <= 384){
				mcDir(SOUTH);
				evMap(10,0,227,69);
			} else {
				mcDir(WEST);
				evMap(10,0,219,61);
			}
		}
	} else if(map == 53){
		//---アルシア湖岸洞窟
		if(scene == 0){
			if(event == 200){
				mcDir(SOUTH);
				evMap(10,0,189,63);
			} else if(201 <= event && event <= 205
				&& evGet(133) && !evGet(134)){
				//---湖どぼん
				return creventAlsia_IntoLake();
			} else if(205 <= event && event <= 231
				&& evGet(134)){
				//---泳いでいく
				evField(0,1);
				mes.FileMessage("AlsiaLake.msg",0);
				evField(0,1);
				mcDir(SOUTH);
				evScene(1,15,9);
			}
		} else if(scene == 1){
			//---Ｂ１−２
			if(200 <= event && event <= 207){
				//---泳いでお戻り
				evField(0,1);
				mes.FileMessage("AlsiaLake.msg",0);
				evField(0,1);
				mcDir(SOUTH);
				evScene(0,15,34);
			} else if(209 <= event && event <= 211
				&& !evGet(135)){
				//---くしゃみ
				evFrameWait(250);
				mes.FileMessage("AlsiaLake.msg",101);
				evSet(135,1);
			} else if(event == 208){
				mcDir(WEST);
				evScene(2,61,22);
			} else if(event == 5){
				//---宝箱
				itemBox(556,219,event);
			} else if(event == 6){
				//---宝箱
				itemBox(557,224,event);
			}
		} else if(scene == 2){
			//---Ｂ１−３
			if(event == 200){
				mcDir(EAST);
				evScene(1,15,44);
			} else if(201 <= event && event <= 205
				&& !evGet(136)){
				//---グラウンドシップゲット！！
				return creventAlsia_GetGS();
			}
		}
	} else if(map == 54){
		//---セノウ
		if(scene == 0){
			if(200 <= event && event <= 242){
				//---フィールドへ
				mcDir(SOUTH);
				evMap(10,0,254,32);
			} else if(event <= 10){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = 6;

				if(event == 5 && !evGet(252)){
					//---ラーフィア
					return crevent_CenowRarfia();
				} else {
					npTurn(event);
					evField(0,1);
					mes.FileMessage("Cenow.msg",event,mes_scene);
					npReturn(event);
				}
			} else if(event == 243){
				//---タンス／本棚
				itemTansu(855,179);
			}
		}
	} else if(map == 55){
		//---ゼビアマイン
		if(scene == 0){
			if(200 <= event && event <= 202){
				//---フィールドへ
				mcDir(SOUTH);
				evMap(10,0,293,69);
			} else if(event == 203){
				//---炭坑へ
				mcDir(NORTH);
				evMap(56,0,17,34);
			} else if(event == 205){
				//---宿屋２階へ
				mcDir(NORTH);
				evScene(1,15,12);
			} else if(event == 204){
				//---ディヤマ邸宅へ
				mcDir(NORTH);
				evScene(2,10,14);
			} else if((event == 22 || event == 206) && !evGet(125)){
				//---炭坑服購入！！
				npTurn(22);
				return creventZevia_BuyMineSuit(event);
			} else if(event == 206 && (!evGet(126) && !evGet(127))){
				//---通しません！
				evField(0,1);
				mes.FileMessage("ZeviaMine.msg",22);
				evField(0,1);
				mcMove(0,1);
				evFrame();
				mcResetEvent();
			} else if((event == 210 || event == 211)
				&& evGet(125) && !evGet(127)){
				//---炭坑はいる？
				evField(0,1);
				mes.FileMessage("ZeviaMine.msg",101);
				evField(0,1);
				if(crbaseSelectYesNo("入りますか？",64,64) == 0){
					//---メインキャラロード
					crfieldSetMainCharacter(2);
					evSet(126,1);

					npPos(28,33,22);
					npDir(28,NORTH);
					npPos(29,32,22);
					npDir(29,NORTH);

					pPartyInfo->PartyMember[1] = -1;
					pPartyInfo->PartyMember[2] = -1;

					mcDir(SOUTH);
					evScene(0,33,21);
					evFrameWait(500);
					mes.FileMessage("ZeviaMine.msg",102);
					evFrameWait(250);
				} else {
					evField(0,1);
					mcMove(0,1);
					evFrame();
					mcResetEvent();
				}

			} else if(event == 1){
				//---武器
				int ShopItem[] = {4,15,42,54,96,105,112,145,151,260,267,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 0){
				//---道具
				int ShopItem[] = {221,222,226,227,171,172,173,175,177,181,201,197,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 23){
				//---世界地図
				evShowWorldMap(293,69);
			} else if(event <= 30){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;
				else if(evGet(127))
					//---クレイシブ現れたあと
					mes_scene = 3;
				else if(evGet(126))
					mes_scene = 2;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("ZeviaMine.msg",event,mes_scene);

				//---ディヤマ門番
				if(event == 26 && evGet(127) && 
					(npGet(event)->xGet() == 16)){
					//---動く
					if(ef->xGet() != 15){
						evFrameWait(250);
						npDir(26,WEST);
						evFrameWait(250);
						npMove(26,-1,0);
					} else {
						evFrameWait(250);
						npDir(26,EAST);
						evFrameWait(250);
						npMove(26,1,0);
					}
					evFrame();
				}

				npReturn(event);
			} else if(event == 207){
				//---タンス／本棚
				itemTansu(856,223);
			} else if(event == 208){
				//---タンス／本棚
				itemTansu(857,259);
			} else if(event == 209){
				//---タンス／本棚
				itemTansu(858,213);
			}
		} else if(scene == 1){
			//---宿屋２階
			if(event == 200){
				//---１階へ
				if(evGet(132) && !evGet(133)){
					//---サヴィアーとの再会
					return creventMine_Xavier();
				} else {
					mcDir(SOUTH);
					evScene(0,48,48);
				}
			} else if(event == 0){
				//---宿
				if(evGet(132) && !evGet(133)){
					//---泊まれない
					evField(0,1);
					mes.FileMessage("ZeviaMine.msg",59,1);
				} else {
					evYado(250,map,scene);
				}
			} else if(event <= 10){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("ZeviaMine.msg",event + 50,mes_scene);
				npReturn(event);
			} else if(event == 201){
				//---タンス／本棚
				itemTansu(859,227);
			}
		} else if(scene == 2){
			//---ディヤマ邸宅
			if(200 <= event && event <= 201){
				//---外へ
				mcDir(SOUTH);
				evScene(0,16,43);
			} else if(event == 202){
				//---２階へ
				mcDir(NORTH);
				evScene(3,11,17);
			} else if(event <= 10){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("ZeviaMine.msg",event + 60,mes_scene);
				npReturn(event);
			}
		} else if(scene == 3){
			//---ディヤマ邸宅２階
			if(event == 200){
				//---１階へ
				mcDir(SOUTH);
				evScene(2,10,11);
			} else if(203 <= event && event <= 204
				&& AFTER_YUMI() && !evGet(191)){
				return creventZeviaMine_DiyamaOve();
			} else if(event <= 10){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("ZeviaMine.msg",event + 70,mes_scene);
				npReturn(event);
			} else if(event == 201){
				//---タンス／本棚
				itemTansu(860,225);
			} else if(event == 202){
				//---タンス／本棚
				itemTansu(861,219);
			}
		}
	}
	return 1;
}


CREVENTPART5_API int creventCheckEvent_Part5_2(int event,int map,int scene)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;
	eiMapObject *pob = crfieldGetObjectPointer(event);

	CR_BATTLEINFO BatInfo;
	memset(&BatInfo,0,sizeof(BatInfo));

	if(map == 56){
		//---炭坑
		if(scene == 0){
			if(200 <= event && event <= 202){
				//---ゼビアマインへ
				mcDir(SOUTH);
				evMap(55,0,31,8);
			} else if(event == 203){
				//---Ｂ２へ
				mcDir(SOUTH);
				evScene(1,16,23);
			} else if(event <= 10){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = 6;
				else if(AFTER_YUMI())
					mes_scene = 5;
				else if(evGet(127))
					mes_scene = 2;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("Mine.msg",event,mes_scene);
				npReturn(event);
			}
		} else if(scene == 1){
			//---Ｂ２
			if(event == 200){
				//---Ｂ１へ
				mcDir(SOUTH);
				evScene(0,18,3);
			} else if(event == 201){
				//---Ｂ３へ
				mcDir(SOUTH);
				evScene(2,11,33);
			} else if(event == 205 && !evGet(127)){
				//---ルナン捕まる！！
				return creventMine_DizzaHead();
			} else if(event <= 10){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = 6;
				else if(AFTER_YUMI())
					mes_scene = 5;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("Mine.msg",event + 10,mes_scene);
				npReturn(event);
			}
		} else if(scene == 2){
			//---Ｂ３
			if(event == 200){
				//---Ｂ２へ
				mcDir(SOUTH);
				evScene(1,31,5);
			} else if(event == 201){
				//---炭坑遺跡へ
				mcDir(SOUTH);
				evMap(57,0,20,35);
			}
		}
	} else if(map == 57){
		//---炭坑遺跡
		if(scene == 0){
			//---Ｂ１
			if(event == 200){
				//---炭坑へ
				mcDir(SOUTH);
				evMap(56,2,23,10);
			} else if(event == 201){
				//---Ｂ２
				mcDir(SOUTH);
				evScene(1,21,48);
			} else if(event == 0){
				//---宝箱
				itemBox(551,224,event);
			} else if(event == 1){
				//---宝箱
				itemBox(552,219,event);
			} else if(event == 2){
				//---宝箱
				itemBox(553,227,event);
			}
		} else if(scene == 1){
			//---Ｂ２
			if(event == 200){
				//---Ｂ１へ
				mcDir(SOUTH);
				evScene(0,4,25);
			} else if(event == 201){
				//---Ｂ１−２へ
				mcDir(SOUTH);
				evScene(2,24,21);
			} else if(event == 202){
				//---Ｂ１−３へ
				mcDir(SOUTH);
				evScene(5,3,14);
			} else if(event == 0 && !evGet(132)){
				//---ファスラクリア
				return creventMine_FasraCrear();
			} else if((event == 203 || event == 204)
				&& !evGet(128)){
				//---あれが・・・
				npPos(1,ef->xGet(),39);
				npDir(1,NORTH);
				mcShow(0);

				for(a = 0;a < 18;a ++){
					mcMove(0,-1);
					evFrame();
				}
				evFrameWait(2000);
				for(a = 0;a < 18;a ++){
					mcMove(0,1);
					evFrame();
				}
				evFrameWait(500);
				mes.FileMessage("Mine.msg",102);
				npPos(1,0,0);
				npShow(1,0);
				mcShow(1);
				mcDir(NORTH);

				evSet(128,1);
			}
		} else if(scene == 2){
			//---Ｂ１−２
			if(event == 200){
				//---Ｂ２へ
				mcDir(SOUTH);
				evScene(1,45,18);
			} else if(event == 201){
				//---Ｂ０へ
				mcDir(SOUTH);
				evScene(4,11,4);
				evSet(130,0);
			} else if(event == 202){
				//---小部屋へ
				mcDir(SOUTH);
				evScene(3,8,4);
			} else if(event == 0){
				//---宝箱
				itemBox(554,223,event);
			}
		} else if(scene == 3){
			//---小部屋
			if(event == 200){
				//---Ｂ１−２へ
				mcDir(SOUTH);
				evScene(2,24,4);
			} else if(event == 0){
				//---宝箱
				itemBox(555,117,event);
			}
		} else if(scene == 4){
			//---Ｂ０
			if(event == 200){
				//---Ｂ２へ
				mcDir(SOUTH);
				evScene(2,21,40);
				evSet(130,0);
				evSet(131,0);
			} else if(event == 201){
				//---Ｂ１−３へ
				mcDir(SOUTH);
				evScene(5,19,4);
				evSet(130,0);
				evSet(131,0);
			} else if(event == 0){
				evField(0,1);
				mes.FileMessage("Mine.msg",50);
			} else if(!evGet(129)){
				if(202 <= event && event <= 221){
					if(event < evGet(130)){
						//---振り向いた！
						evField(0,1);
						mes.FileMessage("Mine.msg",80);
						evFrameWait(250);

						//---バトル
						CR_BATTLEINFO BattleInfo;
						memset(&BattleInfo,0,sizeof(BattleInfo));
						BattleInfo.MapNumber = crfieldGetMapNumber();
						BattleInfo.Music = CRMUSIC_BATTLE;
						BattleInfo.Enemy[0].Enemy = 98;
						BattleInfo.Enemy[0].x = 4;
						BattleInfo.Enemy[0].y = 6;
						BattleInfo.Enemy[1].Enemy = 98;
						BattleInfo.Enemy[1].x = 7;
						BattleInfo.Enemy[1].y = 8;
						BattleInfo.Enemy[2].Enemy = -1;
						BattleInfo.ScreenEfect = CRINTOBAT_NORMAL;
						evField(0,1);
						mcDir(SOUTH);
						crfieldChangeScene(4,7,4);
						evSet(130,0);
						evSet(131,0);
						if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
							return MAINLOOP_BATTLEFAIL;
						}
						return 1;
					}
				}

				if(202 <= event && event <= 221){
					//---一歩前進セット
					evSet(130,event);
				}
				if(event == 203){
					evField(0,1);
					mes.FileMessage("Mine.msg",60);
				} else if(event == 205){
					evField(0,1);
					mes.FileMessage("Mine.msg",61);
				} else if(event == 207){
					evField(0,1);
					mes.FileMessage("Mine.msg",62);
				} else if(event == 210){
					evField(0,1);
					mes.FileMessage("Mine.msg",63);
				} else if(event == 213){
					evField(0,1);
					mes.FileMessage("Mine.msg",64);
				} else if(event == 215){
					evField(0,1);
					mes.FileMessage("Mine.msg",65);
				} else if(event == 218){
					evField(0,1);
					mes.FileMessage("Mine.msg",66);
				} else if(event == 221){
					evField(0,1);
					mes.FileMessage("Mine.msg",67);
//				} else if(event == 221){
					//---タイマーリセット
					evStartTimer();
					evSet(131,1);
				}
			}
		} else if(scene == 5){
			//---Ｂ１−３
			if(event == 200){
				//---Ｂ０へ
				mcDir(SOUTH);
				evScene(4,7,28);
			} else if(event == 201){
				//---Ｂ２へ
				mcDir(SOUTH);
				evScene(1,22,20);
			}
		}
	} else if(map == 58){
		//---ゼビアマイングラウンドシップ船着き場
		if(scene == 0){
			if(200 <= event && event <= 201){
				//---フィールドへ
				mcDir(SOUTH);
				evMap(10,0,297,77);
			} else if(event == 202){
				//---入れない
				npTurn(0);
				evField(0,1);

				mes.FileMessage("ZeviaGS.msg",0);

				mcMove(0,1);
				npReturn(0);
				evFrame();
				mcResetEvent();
			} else if(event <= 3){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("ZeviaGS.msg",event,mes_scene);
				npReturn(event);
			}
		}
	} else if(map == 59){
		//---グラウンドシップ
		if(scene == 0){
			if(event == 201){
				//---外へ
				if(evGet(170) && !evGet(171)){
					//---バイツ
					mcDir(SOUTH);
					evMap(10,0,57,94);
				}
			} else if(event == 200){
				mcDir(SOUTH);
				evScene(1,3,5);
			} else if(event <= 6
				|| /*ユミ寝てる*/(event == 16 && evGet(177) && !evGet(178)) && !evGet(209)){
				int mes_scene = 1;

				if(event == 16)
					event = 4;

				npTurn(event);
				evField(0,1);

				if(AFTER_KOJINSAI())
					mes_scene = 9;
				else if(evGet(209))
					//---南部大雪原クリア
					mes_scene = 8;
				else if(evGet(199))
					//---蜃気楼の塔
					mes_scene = 7;
				else if(evGet(190))
					//---大クレータークリア
					mes_scene = 6;
				else if(AFTER_YUMI())
					//---ユミの過去のあと
					mes_scene = MESSAGE_YUMI;

				mes.FileMessage("GS.msg",event,mes_scene);
				npReturn(event);
			} else if(7 <= event && event <= 16){
				//---寝る
				evField(0,1);
				if(crbaseSelectYesNo("休憩しますか？",64,64) == 0){
					evFadeOut();
					prtRecoveryAll();
					evFieldNoFlip(0,1);
					et->Delay2(500);
					evFadeIn();
				}
			}
		} else if(scene == 1){
			if(event == 200){
				mcDir(SOUTH);
				evScene(0,5,7);
			} else if(event <= 6){
				//---サヴィアー
				int mes_scene = 1;
				npTurn(event);
				evField(0,1);

				if(AFTER_KOJINSAI())
					mes_scene = 9;
				else if(evGet(209))
					//---南部大雪原クリア
					mes_scene = 8;
				else if(evGet(199))
					//---蜃気楼の塔
					mes_scene = 7;
				else if(evGet(190))
					//---大クレータークリア
					mes_scene = 6;
				else if(AFTER_YUMI())
					mes_scene = 1;//MESSAGE_YUMI;
				else if(evGet(173))
					mes_scene = 2;

				mes.FileMessage("GS.msg",event,mes_scene);
				npReturn(event);

			} else if(event == 7){
				//---世界地図
				if(evGet(170) && !evGet(171)){
					evShowWorldMap(57,94);
				} else {
					evShowWorldMap(evGet(EV_GS_SCENE_KEEPX),evGet(EV_GS_SCENE_KEEPY),0,0);
				}
			}
		}
	}
	return 1;
}
