/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrEvent.cpp ...Event functions

-----------------------------------------------------------*/


#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CREVENT

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#include "CrBase.h"
#include "CrBattle.h"
#include "CrEvent.h"
#include "CrEvCom.h"

//---game info
#define CR_GAMEINFO_EXTERNPOINTER
#include "CrGameInfo.h"

#include "CrEvent_SubGameStart.cpp"

CREVENTLONG1_API int creventDoguri_FirstVisit(void);
CREVENTLONG5_API int creventGreatCrater_First(void);


void creventMapChangeCallback2(int map,int scene);

//---テスト用
CREVENT_API int creventCheckEvent_PartTest(int event,int map,int scene)
{
	CrMesManager mes;
	eiMapObject *pob = crfieldGetObjectPointer(event);

	if(map == 0){
		if(scene == 0){
		//---マニュアルイベント-----------------------------------
			if(event == 0){
				int ShopItem[] = {10,49,100,195,221,226,227,233,-1};
				crshopIntoShop(&ShopItem[0]);
				return 0;

				//---ソムヤード
				crfieldTurnToPlayer(pob);
				crfieldDrawFrame();

				if(pGameInfo->Event[0] <= 4){
					mes.FileMessage("TestMessage.msg",1,1);
				} else if(pGameInfo->Event[0] <= 6){
					mes.FileMessage("TestMessage.msg",1,2);
				} else {
					mes.FileMessage("TestMessage.msg",1,3);
				}
				pGameInfo->Event[0] ++;
		//---オートイベント-----------------------------------
			} else if(event == 200){
				//---シーン移動//12,20
				crfieldChangeSceneS(1,21,19);
			} else if(event == 201){
				//---テストの町
				crfieldChangeMapSceneS(1,0,5,14);
//				crfieldChangeSceneS(0,5,14);
			}
		} else if(scene == 1){
		//---オートイベント-----------------------------------
			if(event == 200){
				crfieldChangeSceneS(0,16,10);
			}
		}
	} else if(map == 1){
		if(scene == 0){
			char msgfile[] = "TestTown.msg";
			crfieldTurnToPlayer(pob);
			crfieldDrawFrame();

		//---マニュアルイベント-----------------------------------
			if(event == 0){
				mes.FileMessage(msgfile,event,pGameInfo->Event[0] % 2 + 1);
				pGameInfo->Event[0] ++;
			}
			if(event == 2 || event == 4 || event == 5 || event == 6){
				mes.FileMessage(msgfile,event,1);
			}
			if(event == 1){
				if(++pGameInfo->Event[event] <= 1){
					mes.FileMessage(msgfile,event,1);
				} else {
					mes.FileMessage(msgfile,event,2);
				}
			}
			if(event == 3){
				pGameInfo->Event[event] ++;
				if(pGameInfo->Event[event] >= 4)
					pGameInfo->Event[event] = 1;
				mes.FileMessage(msgfile,event,pGameInfo->Event[event]);
			}
		//---オートイベント-----------------------------------
			if(event == 200 || event == 201){
				//---フィールドへ
				crfieldChangeMapSceneS(0,0,13,8);
//				crfieldChangeSceneS(0,13,8);
			} else if(event == 202){
				//---To 1
				crfieldChangePlane(1);
			} else if(event == 203){
				//---To 3
				crfieldChangePlane(3);
			} else if(event == 204){
				//---To 1
				crfieldChangePlane(1);
			} else if(event == 205){
				//---To 3
				crfieldChangePlane(3);
			}
		}
	}

	return 0;
}

void creventMapSetTakarabako(int event,int ev_obj)
{
	if(evGet(event))
		npDir(ev_obj,EAST);
}

void creventMapChangeCallback(int map,int scene)
{
	int a;

	if(map == 0){
	} else if(map == 1){
	} else if(map == 10){
		if(scene == 0){
			//237,198
			if(evGet(171)&& !evGet(177)){
				//---ユミの故郷にＧＳ
				npPos(NP_GS_CANTNUMBER,46,207);
				npDir(NP_GS_CANTNUMBER,NORTH);
			} else if(evGet(170) && !evGet(171) /*ユミの過去まで*/){
				//---バイツにＧＳ
				npPos(NP_GS_CANTNUMBER,58,94);
				npDir(NP_GS_CANTNUMBER,NORTH);
			} else if(evGet(141) && !evGet(157) /*ジーダイ渡るまで*/){
				npPos(NP_GS_CANTNUMBER,326,235);
				npDir(NP_GS_CANTNUMBER,NORTH);
			} else if(evGet(136) && !evGet(140)){
				//---クレスフィールドにＧＳ
				npPos(NP_GS_CANTNUMBER,237,198);
				npDir(NP_GS_CANTNUMBER,NORTH);
			} else {
				npPos(NP_GS_CANTNUMBER,0,0);
				npDir(NP_GS_CANTNUMBER,NORTH);
			}
		}
	} else if(map == 14){
		//---ウェスカ
		if(scene == 0){
			if(evGet(4) == 0 || (evGet(9) == 1 && evGet(15) == 0)){
				//---盗賊達
				npPos(33,34,38);
				npDir(33,EAST);
				npPos(34,36,38);
				npDir(34,WEST);
			}

			if(AFTER_KOJINSAI()){
				//---エターナル消去
				npDelete(10);
				npDelete(22);
			}
		}
	} else if(map == 16){
		if(scene == 0){
			if(AFTER_KOJINSAI()){
				//---エターナル消去
				npDelete(11);
				npDelete(12);
			}
		}
	} else if(map == 17){
		//---ウェスカ西の橋
		if(evGet(15) == 1 && evGet(16) == 0){
			npPos(2,26,12);
			npDir(2,NORTH);
		}
	} else if(map == 18){
		//---ウェスカ北の森
		if(scene == 0){
			if(evGet(8) == 1){
				em->Put(45,22,1,0);
				em->Put(45,23,1,0);
			} else {
				evSet(8,0);
			}
			creventMapSetTakarabako(500,0);
			creventMapSetTakarabako(501,1);
		} else if(scene == 2){
			creventMapSetTakarabako(502,2);
			creventMapSetTakarabako(503,3);
		}
	} else if(map == 19){
		if(scene == 0){
			//---セーネ北西の森
			creventMapSetTakarabako(504,3);
			creventMapSetTakarabako(505,4);

			if(evGet(17) == 2){
				for(a = 0;a <= 2;a ++){
					npPos(a,0,0);
					npShow(a,0);
				}
			}
		} else if(scene == 2){
			if(evGet(33)){
				//---アネート到達後
				for(a = 0;a <= 6;a ++){
					npDelete(a);
				}
			}
		}
	} else if(map == 20){
		//---アネートへの山道
		if(scene == 0){
			if(evGet(19) == 1){
				npPos(0,0,0);
				npShow(0,0);
			}
		} else if(scene == 1){
			creventMapSetTakarabako(506,0);
		} else if(scene == 2){
			creventMapSetTakarabako(507,0);
		}
	} else if(map == 21){
		//---アネート
		if(scene == 0){
			if(evGet(71)){
				//---タゴサクどん
				npDelete(11);
			}
			if(AFTER_KOJINSAI()){
				//---エターナル消去
				npDelete(14);
				npDelete(13);
			}
		}
	} else if(map == 22){
		//---ドーグリ
		if(scene == 0){
			if(evGet(26) == 1){
				//---ＳＳ撃破後
				for(a = 14;a <= 19;a ++){
					npPos(a,0,0);
					npShow(a,0);
					eiMapObject *pObject = em->GetObject(a);
					pObject->Data.Status &= (~EF_OBJECT_ST_MOVERANDOM);
					pObject->Data.Status |= (EF_OBJECT_ST_MOVEFIXED);
				}
			}
			if(evGet(22) && evGet(25) == 0){
				creventDoguri_FirstVisit();
			}
			if(evGet(22) && evGet(25) <= 1){
				//---ライゼル
				npPos(23,21,22);
				npShow(23,1);
				npDir(23,SOUTH);
			}

			if(AFTER_YUMI()){
				//---たごさくどん
				npPos(36,6,6);
				npDir(36,NORTH);
			}
			if(AFTER_YUMI() && !(AFTER_KOJINSAI())){
				//---エターナル
				npPos(29,21,21);
				npDir(29,SOUTH);
			}
		} else if(scene == 1){
			//---宿屋２回のシンディ
			if(evGet(27) == 1){
				npPos(0,0,0);
				npShow(0,0);
			}
		}
	} else if(map == 23){
		//---ＳＳ本部
		if(scene == 0){
			if(evGet(28) == 1){
				//---扉開いてる
				npPos(0,0,0);
				npShow(0,0);//6,12
				em->Put(6,12,2,1024);
			}
		} else if(scene == 1){
			creventMapSetTakarabako(508,0);
			creventMapSetTakarabako(509,1);
		} else if(scene == 2){
			creventMapSetTakarabako(510,0);
			creventMapSetTakarabako(511,1);
		} else if(scene == 3){
			//---ＳＳ撃破後
			if(evGet(26) == 1){
				for(a = 0;a < 2;a ++){
					npPos(a,0,0);
					npShow(a,0);
				}
			}
			if(evGet(29) == 1){
				for(a = 2;a < 4;a ++){
					npPos(a,0,0);
					npShow(a,0);
				}
			}
		}
	} else if(map == 24){
		//---ドーグリ南の森
		if(scene == 0){
			creventMapSetTakarabako(512,0);
		}
	} else if(map == 25){
		//---ドーグリ南の遺跡
		if(scene == 0){
			creventMapSetTakarabako(513,0);
		}
		if(scene == 1){
			if(evGet(41)){
				em->Put(11,31,2,1024);
			}
		}
		if(scene == 2){
			creventMapSetTakarabako(514,4);
			creventMapSetTakarabako(515,5);
		}
	} else if(map == 26){
		//---フェイマル
		if(scene == 0){
			if(AFTER_YUMI()){
				npDelete(24);
			}

			if(AFTER_KOJINSAI()){
				for(a = 0;a <= 28;a ++){
					if(a != 16 && a != 27)
						npDelete(a);
				}
			}

		} else if(scene == 1){
			//---宿屋２回のシンディ
			if(evGet(57) && !evGet(58)){
				npPos(4,12,5);
				npDir(4,SOUTH);
			}
		} else if(scene == 3){
			//---エターナル建物１階
			if(AFTER_KOJINSAI()){
				for(a = 7;a <= 9;a ++){
					npDelete(a);
				}
			}
		} else if(scene == 4){
			//---エターナル建物２階
			if(!evGet(58)){
				npPos(4,12,14);
				npDir(4,WEST);
				npPos(5,9,12);
				npDir(5,SOUTH);
				npPos(6,9,16);
				npDir(6,NORTH);
				npPos(7,7,12);
				npDir(7,SOUTH);

				evReadObject(0,"Asgray.acf");
				evReadObject(1,"Follne.acf");
				evReadObject(2,"Rarfia.acf");
				evReadObject(3,"Edo.acf");
			}

			if(AFTER_YUMI()){
				em->Put(14,10,2,1024);
			}
		}
	} else if(map == 28){
		//---地の遺跡
		if(scene == 0){
			creventMapSetTakarabako(516,0);
		} else if(scene == 1){
			creventMapSetTakarabako(517,0);
			creventMapSetTakarabako(518,4);
		} else if(scene == 2){
			creventMapSetTakarabako(519,0);
			creventMapSetTakarabako(520,6);
			if(evGet(48)){
				em->Put(10,11,1,64);
			}
		}
	} else if(map == 29){
		//---水の遺跡
		if(scene == 0){
			creventMapSetTakarabako(521,0);
			creventMapSetTakarabako(522,2);
		} else if(scene == 1){
			creventMapSetTakarabako(523,0);
		} else if(scene == 3){
			creventMapSetTakarabako(524,5);
			creventMapSetTakarabako(525,8);
			creventMapSetTakarabako(526,10);
			creventMapSetTakarabako(527,13);
		}
	} else if(map == 30){
		//---クレスフィールド高地
		if(scene == 0){
			creventMapSetTakarabako(530,0);
		}  else if(scene == 1){
			creventMapSetTakarabako(531,0);
		}
	} else if(map == 31){
		//---フェイマル下水道
		if(scene == 0){
			creventMapSetTakarabako(528,0);
			creventMapSetTakarabako(529,1);
		}
	} else if(map == 32){
		//---クレスフィールド
		if(scene == 0){
			if(AFTER_KOJINSAI()){
				for(a = 0;a <= 40;a ++){
					if(a != 26 && a != 27){
						npDelete(a);
					}
				}
			} else if(AFTER_YUMI()){
				npPos(65,15,25);
				npDir(65,WEST);
				npPos(66,13,24);
				npDir(66,SOUTH);
			}
		} else if(scene == 1){
			//---議会
			if(AFTER_KOJINSAI()){
				for(a = 2;a <= 4;a ++){
					npDelete(a);
				}
			}
		}

		if(scene == 3){
			if((1 <= evGet(66) && evGet(66) < 2)){
				npPos(1,13,5);
				npDir(1,SOUTH);
				npPos(2,12,10);
				npDir(2,EAST);
				npPos(3,18,6);
				npDir(3,SOUTH);
				npPos(4,13,11);
				npDir(4,NORTH);
			} else if(1 <= evGet(139) && evGet(139) <= 2){
				npPos(2,3,11);
				npDir(2,NORTH);
			}
		}
		
		if(scene == 4 || scene == 3){
			//---シンディ
			if(evGet(137) && !evGet(138)){
				npPos(9,8,8);
				npDir(9,SOUTH);
				evReadObject(1,"Cindy.acf");
			}
		} else {
			evReadObject(1,"TwPpl0w.acf");
		}

		if(scene == 4){
			//---酒場
			if(AFTER_YUMI())
				npDelete(2);

			if(AFTER_KOJINSAI()){
				for(a = 0;a <= 2;a ++){
					npDelete(a);
				}
			}
		}
	} else if(map == 34){
		//---幻惑の樹海
		if(scene == 0){
			creventMapSetTakarabako(532,1);

			if(evGet(71)){
				int x,y;
				for(y = 0;y < 11;y ++){
					for(x = 46;x < 65;x ++){
						em->Put(x,y,2,1024);
					}
				}
			}
		} else if(scene == 1){
			creventMapSetTakarabako(533,0);
		} else if(scene == 2){
			creventMapSetTakarabako(534,0);
		} else if(scene == 4){
			creventMapSetTakarabako(535,0);
		}
	} else if(map == 35){
		//---保存装置
		if(scene == 4){
			if(!evGet(71)){
				//---１部クリア前
				em->Put(9,7,2,17);

				npPos(8,24,25);
				npShow(8,1);
				npDir(8,WEST);
			}
		}
	} else if(map == 38){
		//---中央山脈
		if(scene == 0){
			creventMapSetTakarabako(536,0);
			creventMapSetTakarabako(537,1);
		} else if(scene == 1){
			creventMapSetTakarabako(538,0);
		} else if(scene == 3){
			//---ユミ
			if(!evGet(106)){
				npPos(11,20,31);
				npDir(11,WEST);
			}
			if(AFTER_YUMI()){
				npDelete(1);
				npDelete(2);
			}
		} else if(scene == 5){
			creventMapSetTakarabako(539,0);
			creventMapSetTakarabako(540,1);
		} else if(scene == 6){
			//---物売り
			if(AFTER_KOJINSAI()){
				npPos(17,28,16);
				npDir(17,EAST);
				em->Put(28,16,1,118);
			}
		} else if(scene == 8){
			//---ファスラクリア
			evReadObject(14,"Fasra.acf");
			if(evGet(244)){
				npDelete(0);
			}
		} else if(scene == 11){
			//---別の場所
			if(evGet(230)){
				//---蒸発後 5,2 - 22,15
				int x,y;
				for(y = 2;y <= 15;y ++){
					for(x = 5;x <= 22;x ++){
						em->Put(x,y,2,1024);
					}
				}
			}
		}
	} else if(map == 39){
		//---ノーステリア
		if(scene == 0){
			if(AFTER_YUMI() && !evGet(205) && evGet(199)){
				//---ラディアントヘルムを売る人
				//---蜃気楼の塔クリア後
				npPos(51,37,22);
				npDir(51,SOUTH);
			}

			if(AFTER_KOJINSAI()){
				npDelete(14);
				npDelete(15);
			}

			if(evGet(99)){
				if(evGet(104) <= 1){
					//---入り口にて盗賊との会話
					npPos(41,32,48);
					npDir(41,NORTH);
				} else if(evGet(104) <= 2){
					npPos(42,36,22);
					npDir(42,SOUTH);
				}
			}
			if(evGet(104) == 3 && !evGet(106)){
				//---大陸教会で寝てる人
				npPos(49,12,6);
				npDir(49,NORTH);
			}
		} else if(scene == 4){
			if(evGet(116) && !evGet(117)){
				//---町長出張中
				npPos(0,0,0);
				npShow(0,0);
			}
		}
	} else if(map == 40){
		//---ダイ
		if(scene == 0){
			if(AFTER_YUMI() && !(AFTER_KOJINSAI())){
				npPos(20,27,39);
				npDir(20,SOUTH);
			}

			if(AFTER_YUMI()){
				npDelete(13);
			} else if(evGet(103)){
				npPos(13,32,11);
			} else {
				npPos(13,33,11);
			}
			npDir(13,SOUTH);

			if(evGet(98) != 2){
				npPos(14,21,27);
				npDir(14,SOUTH);
			}
		} else if(scene == 1){
			//---村長２階
			if(AFTER_YUMI()){
				npPos(1,3,5);
				npDir(1,WEST);
				eiMapObject *np = npGet(1);
				np->Data.GraphicNumber = 5;
				npPos(2,12,8);
				npDir(2,NORTH);
			} else if(evGet(99)){
				npPos(1,3,2);
				npDir(1,NORTH);
				npPos(2,4,4);
				npDir(2,NORTH);
			}
		}
	} else if(map == 41){
		//---マークス
		if(AFTER_KOJINSAI()){
			evReadObject(15,"Gazell.acf");
		}
		if(scene == 0){
			if(AFTER_KOJINSAI()){
				npPos(43,46,21);
				npDir(43,SOUTH);
				npPos(44,47,21);
				npDir(44,SOUTH);
				npPos(45,5,38);
				npDir(45,NORTH);
				npPos(46,46,38);
				npDir(46,WEST);
				npPos(47,25,39);
				npDir(47,WEST);
			}
			if(evGet(114) && !evGet(117)){
				npPos(32,43,37);
				npDir(32,NORTH);
				npPos(33,41,33);
				npDir(33,SOUTH);
				npPos(34,45,33);
				npDir(34,SOUTH);
			}
			if(evGet(118) && !evGet(160)){
				npPos(28,37,9);
				npDir(28,EAST);
			}
		} else if(scene == 1){
			if(AFTER_KOJINSAI()){
				npPos(4,4,7);
				npDir(4,SOUTH);
			}
		} else if(scene == 2){
			if(AFTER_KOJINSAI()){
				npPos(1,10,8);
				npDir(1,SOUTH);
			}
		}
	} else if(map == 44){
		//---ノーステリアの洞窟
		if(scene == 0){
			if(evGet(105)){
				em->Put(8,12,2,1024);
				npPos(0,0,0);
			}
			creventMapSetTakarabako(541,1);
			creventMapSetTakarabako(542,2);
		} else if(scene == 1){
			creventMapSetTakarabako(543,0);
		} else if(scene == 2){
			creventMapSetTakarabako(544,0);
		}
	} else if(map == 45){
		//---ダワン石採掘場
		if(scene == 0){
			if(evGet(120) && !evGet(118)){
				//---ライゼル
				npPos(8,13,7);
				npDir(8,NORTH);

				//---普通の人
				npPos(1,0,0);
				npShow(1,0);
				npPos(3,0,0);
				npShow(3,0);
				npPos(4,0,0);
				npShow(4,0);
			}
		}
	} else if(map == 46){
		//---ノーステリアの遺跡
		if(scene == 1){
			creventMapSetTakarabako(545,0);
			creventMapSetTakarabako(546,1);
			creventMapSetTakarabako(547,2);
		} else if(scene == 2){
			creventMapSetTakarabako(548,0);
			creventMapSetTakarabako(549,1);
		} else if(scene == 3){
			creventMapSetTakarabako(550,0);
		}
	} else if(map == 47){
		//---橋
		if(scene == 0){
			if(evGet(118)){
				//---エターナル消える
				npPos(0,0,0);
				npShow(0,0);
				npPos(1,0,0);
				npShow(1,0);
			}
			if(!evGet(239)){
				//---おねえちゃんの指輪
				npPos(4,27,12);
				npDir(4,NORTH);
			}
		}
	} else {
		creventMapChangeCallback2(map,scene);
	}
}

void creventMapChangeCallback2(int map,int scene)
{
	int a;

	if(map == 51){
		//---アルシア
		if(scene == 0){
			if(AFTER_KOJINSAI()){
				npDelete(14);
			}
			if(evGet(121) && !evGet(122)){
				//---お墓の花
				em->Put(59,17,2,98);
			}
		} else if(scene == 1){
			if(AFTER_YUMI()){
				npDelete(0);
			}
		}
	} else if(map == 53){
		//---アルシア湖岸洞窟
		if(scene == 1){
			creventMapSetTakarabako(556,5);
			creventMapSetTakarabako(557,6);
		} else if(scene == 2){
			if(evGet(136)){
				int x,y;
				for(y = 8;y < 18;y ++){
					for(x = 8;x < 30;x ++){
						em->Put(x,y,2,1024);
					}
				}
			}
		}
	} else if(map == 54){
		if(scene == 0){
			if(AFTER_KOJINSAI()){
				npPos(5,19,23);
				npDir(5,NORTH);
			}
		}
	} else if(map == 55){
		//---ゼビアマイン
		if(scene == 0){
			if(evGet(126)){
				//---ルナン一人で炭坑に入る
				npPos(28,33,22);
				npDir(28,NORTH);
				npPos(29,32,22);
				npDir(29,NORTH);
			} else if(evGet(127) && !(AFTER_YUMI())){
				//---クレイシブが現れた跡
				npPos(22,0,0);
				npShow(22,0);
			}

			if(AFTER_KOJINSAI()){
				npDelete(11);
				npDelete(12);
				npDelete(13);
			}
		} else if(scene == 1){
			if(AFTER_KOJINSAI()){
				npDelete(2);
			}
		}
	} else if(map == 56){
		//---炭坑
		if(scene == 0){
			if(AFTER_YUMI()){
				npDelete(3);
				npDelete(4);
			} else if(evGet(127)){
				//---クレイシブ現れた跡
				for(a = 2;a < 10;a ++){
					npPos(a,0,0);
					npShow(a,0);
				}
			}
		} else if(scene == 1){
			if(evGet(126)){
				//---ルナン一人で炭坑に入る
				npPos(5,18,9);
				npDir(5,WEST);
				npPos(6,8,18);
				npDir(6,SOUTH);
				npPos(7,8,19);
				npDir(7,NORTH);
			}

			if(AFTER_YUMI()){
				npDelete(2);
				npDelete(3);
			} else if(evGet(127)){
				//---クレイシブ現れた跡
				for(a = 0;a < 10;a ++){
					npPos(a,0,0);
					npShow(a,0);
				}
			}
		}
	} else if(map == 57){
		//---炭坑
		if(scene == 0){
			creventMapSetTakarabako(551,0);
			creventMapSetTakarabako(552,1);
			creventMapSetTakarabako(553,2);
		} else if(scene == 1){
			creventMapSetTakarabako(132,0);
		} else if(scene == 2){
			creventMapSetTakarabako(554,0);
		} else if(scene == 3){
			creventMapSetTakarabako(555,0);
		} else if(scene == 4){
			if(!evGet(129)){
				//---振り返りの通路
				em->Put(7,28,2,80);
			}
		}
	} else if(map == 59){
		//---グラウンドシップ
		if(scene == 0){
			if(evGet(177)){
				if(!evGet(209)){
					//---南部大雪原クリア前まではユミ寝てる
					evReadObject(4,"YumiSlp.acf");
					npPos(4,15,7);
					npDir(4,SOUTH);
					npPos(2,15,6);
					npDir(2,SOUTH);
					npPos(5,20,6);
					npDir(5,EAST);
				} else {
					npPos(4,20,6);
					npDir(4,EAST);
					npPos(2,19,8);
					npDir(2,WEST);
					npPos(5,17,8);
					npDir(5,EAST);
				}

			}
		} else if(scene == 1){
			if(AFTER_KOJINSAI()){
				npPos(1,9,6);
				npDir(1,EAST);
				npPos(3,9,4);
				npDir(3,EAST);
				npPos(6,5,7);
				npDir(6,NORTH);
			} else if(evGet(177)  && !(AFTER_KOJINSAI())){
				npPos(1,9,6);
				npDir(1,EAST);
				npPos(3,9,4);
				npDir(3,EAST);
			} else if(evGet(170) && !evGet(171)){
				//---ユミの過去まで
				npPos(4,9,4);
				npDir(4,EAST);
				npPos(5,9,3);
				npDir(5,SOUTH);
			}

			if(AFTER_YUMI()){
				//---ギア
				em->Put(10,3,2,25);
			}
		}
	} else if(map == 61){
		//---ツーリア
		if(scene == 0){
			if(evGet(142) && !evGet(143)){
				//---ツーリア、ガゼール
				npPos(48,56,35);
				npDir(48,NORTH);
			}

			if(AFTER_KOJINSAI() && evGet(252)){
				//---エド
				npPos(57,65,19);
				npDir(57,NORTH);
				evReadObject(1,"Edo.acf");
			}

			if(AFTER_KOJINSAI()){
				npDelete(4);
				npDelete(10);
				npDelete(11);
				npDelete(12);
				npDelete(13);
				npDelete(14);
				npDelete(15);
				npDelete(16);
				npDelete(37);
			}
			if(AFTER_YUMI()){
				//---奴隷地管理人
				npDelete(36);
				//---奴隷
				for(a = 49;a <= 53;a ++){
					npDelete(a);
				}
			}
		}
	} else if(map == 63){
		//---ツーリア地下通路
		if(scene == 0){
			creventMapSetTakarabako(558,0);
		} else if(scene == 1){
			creventMapSetTakarabako(559,0);
			creventMapSetTakarabako(560,1);
		} else if(scene == 2){
			creventMapSetTakarabako(561,0);
			if(!evGet(149)){
				npPos(6,53,24);
				npDir(6,NORTH);
			}
		} else if(scene == 3){
			creventMapSetTakarabako(562,0);
		} else if(scene == 4){
			creventMapSetTakarabako(563,0);
		}
	} else if(map == 64){
		//---ツーリア、エターナル建物
		if(scene == 0){
			if(!evGet(155)){
				//---牢屋！
				em->Put(6,8,2,97);
			}
		} else if(scene == 1){
			if(!evGet(154)){
				//---ツーリアクリア前
				for(a = 0;a <= 1;a ++){
					npPos(a,0,0);
					npShow(a,0);
				}
				npPos(2,10,25);
				npDir(2,NORTH);
				npPos(3,12,28);
				npDir(3,SOUTH);
				npPos(4,13,25);
				npDir(4,WEST);
			}

			if(AFTER_KOJINSAI()){
				npDelete(0);
				npDelete(1);
			}
		} else if(scene == 2){
			if(AFTER_KOJINSAI()){
				for(a = 2;a <= 7;a ++){	
					npDelete(a);
				}
			}
		} else if(scene == 3){
			if(AFTER_KOJINSAI()){
				npDelete(0);
			}
		}
	} else if(map == 68){
		//---ジーダイ南の洞窟
		if(scene == 1){
			creventMapSetTakarabako(564,0);
			creventMapSetTakarabako(565,1);
		} else if(scene == 2){
			if(!evGet(158)){
				//---エターナルセット
				npPos(3,21,15);
				npDir(3,SOUTH);
			}
		}
	} else if(map == 70){
		//---記憶の遺跡
		if(scene == 0){
			if(evGet(159) && !evGet(160)){
				//---第２部クリア前
				npPos(4,11,17);
				npDir(4,WEST);
				npPos(5,9,19);
				npDir(5,NORTH);
			}
		} else if(scene == 1){
			creventMapSetTakarabako(566,0);
		} else if(scene == 2){
			creventMapSetTakarabako(567,0);
			creventMapSetTakarabako(568,1);
		} else if(scene == 3){
			creventMapSetTakarabako(569,0);
			creventMapSetTakarabako(570,1);
		} else if(scene == 4){
			creventMapSetTakarabako(571,1);
		}
	} else if(map == 75){
		//---バイツ
		if(AFTER_KOJINSAI()){
			npDelete(10);
			npDelete(11);
			npDelete(12);
			npDelete(13);
		}
	} else if(map == 76){
		//---神の山
		if(scene == 0){
			creventMapSetTakarabako(572,0);
		} else if(scene == 1){
			creventMapSetTakarabako(573,0);
		} else if(scene == 5){
			creventMapSetTakarabako(574,0);
			creventMapSetTakarabako(575,1);
		}
	} else if(map == 77){
		//---シルバースター
		if(scene == 0){
			if(AFTER_KOJINSAI()){
				npDelete(12);
				npDelete(13);
			}
		} else if(scene == 1){
			if(AFTER_KOJINSAI()){
				npDelete(0);
			}
		}
	} else if(map == 80){
		//---大神殿
		if(scene == 0){
			if(AFTER_KOJINSAI()){
				for(a = 0;a <= 10;a ++){
					npDelete(a);
				}
			}
		} else if(scene == 3){
			//---人々
			if(AFTER_KOJINSAI()){
				for(a = 0;a <= 99;a ++){
					npDelete(a);
				}
			} else {
				for(a = 8;a <= 99;a ++){
					npDir(a,NORTH);
				}
			}
		}
	} else if(map == 81){
		//---流差の遺跡
		if(scene == 0){
			if(evGet(209)){
				//---忘れられた遺跡をクリアしたら
				int x,y;
					for(y = 11;y <= 13;y ++){
					for(x = 17;x <= 19;x ++){
						em->Put(x,y,1,3);
					}
				}
				em->Put(18,12,1,31);
			} else {
			}
		} else if(scene == 3){
			if(!evGet(215) || evGet(218)){
				//---助ける前か、流砂の遺跡クリアだったら
				//---クレスフィールドの人消去々
				for(a = 12;a <= 40;a ++){
					npDelete(a);
				}
				
				if(!evGet(215)){
					npPos(12,10,24);
					npDir(12,EAST);
					npPos(13,13,21);
					npDir(13,SOUTH);
					npPos(14,17,15);
					npDir(14,SOUTH);
					npPos(15,12,20);
					npDir(15,WEST);
					npPos(16,22,15);
					npDir(16,EAST);
				}
			}
			if(evGet(215) && !evGet(217)){
				//---閉じこめ
				em->Put(21,36,2,113);
				em->Put(21,37,2,113);
			}

			//---助けに来て、また遺跡の中
			if(evGet(217) && !evGet(218)){
				//---マークスの人々
				evReadObject(14,"Cindy.acf");

				npPos(6,20,35);
				npDir(6,EAST);
				npPos(26,9,26);
				npDir(26,WEST);
				npPos(28,24,35);
				npDir(28,NORTH);
				npPos(27,25,35);
				npDir(27,NORTH);
			}
		} else if(scene == 4){
			creventMapSetTakarabako(594,0);
			creventMapSetTakarabako(595,1);
			creventMapSetTakarabako(596,2);
		}
	} else if(map == 82){
		//---蜃気楼の塔
		if(scene == 0){
			//---入り口
			if(evGet(198)){
				em->Put(28,35,1,6);
			}
		} else if(scene == 3){
			creventMapSetTakarabako(581,0);
			creventMapSetTakarabako(582,1);
		} else if(scene == 4){
			creventMapSetTakarabako(583,0);
			creventMapSetTakarabako(584,1);
		} else if(scene == 5){
			creventMapSetTakarabako(585,0);
		} else if(scene == 10){
			creventMapSetTakarabako(586,0);
		} else if(scene == 6){
			if(evGet(197)){
				//---扉開いていたら
				npDelete(1);
				em->Put(20,15,2,1024);
			}
		} else if(scene == 9){
			if(!evGet(199)){
				npPos(4,10,14);
				npDir(4,NORTH);
				npPos(5,11,14);
				npDir(5,NORTH);
			}
		}
	} else if(map == 83){
		//---大クレーター
		if(scene == 1){
			creventMapSetTakarabako(576,0);
			creventMapSetTakarabako(577,1);
		} else if(scene == 2 || scene == 3){
			creventMapSetTakarabako(578,0);
		} else if(scene == 8){
			creventMapSetTakarabako(579,0);
		} else if(scene == 10){
			creventMapSetTakarabako(580,0);
		} else if(scene == 11){
			if(!evGet(189)){
				//---翼竜
				npPos(4,7,8);
				npDir(4,NORTH);
				npPos(5,8,8);
				npDir(5,EAST);
				npPos(6,9,8);
				npDir(6,SOUTH);
			}
		}
	} else if(map == 84){
		//---ユールクレイラ
		if(scene == 0){
			if(AFTER_KOJINSAI()){
				npDelete(11);
			}
		}
	} else if(map == 85){
		//---滅びの遺跡
		if(scene == 0){
			creventMapSetTakarabako(587,4);
			creventMapSetTakarabako(588,5);
		}
	} else if(map == 86){
		//---忘れられた遺跡
		if(scene == 1){
			creventMapSetTakarabako(589,0);
			creventMapSetTakarabako(590,1);
		} else if(scene == 3){
			creventMapSetTakarabako(591,0);
		} else if(scene == 4){
			creventMapSetTakarabako(592,0);
		} else if(scene == 6){
			creventMapSetTakarabako(593,0);
		} else if(scene == 7){
			if(!evGet(209)){
				npPos(4,20,20);
				npDir(4,NORTH);
				npPos(5,19,21);
				npDir(5,NORTH);
			}
		}
	} else if(map == 88){
		//---小島の洞窟
		if(scene == 0){
			creventMapSetTakarabako(597,0);
			creventMapSetTakarabako(598,1);
			creventMapSetTakarabako(599,2);
		}
	} else if(map == 92){
		//---イリーディア
		if(scene == 0){
		} else if(scene == 1){
			creventMapSetTakarabako(600,0);
		} else if(scene == 2){
			creventMapSetTakarabako(601,0);
		} else if(scene == 5){
			creventMapSetTakarabako(602,2);
			creventMapSetTakarabako(603,3);
			creventMapSetTakarabako(604,4);
			creventMapSetTakarabako(622,5);
		} else if(scene == 8){
			creventMapSetTakarabako(605,0);
			creventMapSetTakarabako(606,1);
			creventMapSetTakarabako(607,2);
		}
	} else if(map == 93){
		//---イリーディア・研究所
		if(scene == 0){
		} else if(scene == 7){
			if(evGet(238)){
				//---壁壊した
				em->Put(10,5,2,1024);
			}
		} else if(scene == 8){
			creventMapSetTakarabako(608,0);
			creventMapSetTakarabako(609,1);
		} else if(scene == 1){
			creventMapSetTakarabako(610,0);
		}
	} else if(map == 94){
		//---イリーディア・エリアＤ
		if(scene == 0){
			creventMapSetTakarabako(611,0);
		} else if(scene == 1){
			creventMapSetTakarabako(612,1);
		} else if(scene == 4){
			//---宝物庫地下
			creventMapSetTakarabako(617,0);
			creventMapSetTakarabako(618,1);
			creventMapSetTakarabako(619,2);
			creventMapSetTakarabako(620,3);
			creventMapSetTakarabako(621,4);
		}
	} else if(map == 95){
		//---イリーディア・皇宮
		if(scene == 0){
		} else if(scene == 1){
			creventMapSetTakarabako(613,0);
			creventMapSetTakarabako(614,1);
		} else if(scene == 5){
			creventMapSetTakarabako(615,0);
			creventMapSetTakarabako(616,1);
		}
	} else if(map == 98){
		//---トレイアの洞窟
		if(scene == 0){
			if(AFTER_KOJINSAI() && evGet(255) < 2){
				//---扉
				em->Put(13,14,2,19);
			}
		}
	}
}

//---ボタンイベント
CREVENT_API int creventCheckEvent(int event)
{
	int map = crfieldGetMapNumber(),scene = crfieldGetMapScene();

	if(evGet(EV_GS_NUMBER_STATUS)){
		//---グラウンドシップに乗ってたら
		if(map == 10){
			if(scene == 0){
				if(287 <= event && event <= 326){
					if(AFTER_YUMI() && !evGet(185)
						&& evGet(EV_GS_NUMBER_STATUS) == 1){
						//---ＧＳ着船！
						return creventGreatCrater_First();
					} else {
						crfieldSetMainCharacter(1);
						evSet(EV_GS_NUMBER_STATUS,0);
						mcDir(SOUTH);
						mcShow(1);
						evFadeOut(2000);
						crfieldChangeMap(83,1,1,1);
						crfieldChangeScene(1,39,4);
						evFieldNoFlip(0,1);
						evFadeIn(1000);
					}
				}
			}
		}
		return 0;
	}

	if(map <= 9){
		//---テスト
		return creventCheckEvent_PartTest(event,map,scene);
	} else if(map == 10){
		return creventCheckEvent_Field(event,map,scene);
	} else if(map <= 15){
		return creventCheckEvent_Part1(event,map,scene);
	} else if(map <= 20){
		return creventCheckEvent_Part1_2(event,map,scene);
	} else if(map <= 25){
		return creventCheckEvent_Part2(event,map,scene);
	} else if(map <= 29){
		return creventCheckEvent_Part3(event,map,scene);
	} else if(map <= 35){
		return creventCheckEvent_Part3_2(event,map,scene);
	} else if(map <= 40){
		return creventCheckEvent_Part4(event,map,scene);
	} else if(map <= 45){
		return creventCheckEvent_Part4_2(event,map,scene);
	} else if(map <= 50){
		return creventCheckEvent_Part4_3(event,map,scene);
	} else if(map <= 55){
		return creventCheckEvent_Part5(event,map,scene);
	} else if(map <= 60){
		return creventCheckEvent_Part5_2(event,map,scene);
	} else if(map <= 65){
		return creventCheckEvent_Part6(event,map,scene);
	} else if(map <= 70){
		return creventCheckEvent_Part6_2(event,map,scene);
	} else if(map <= 74){
		return creventCheckEvent_Part7(event,map,scene);
	} else if(map <= 80){
		return creventCheckEvent_Part7_2(event,map,scene);
	} else if(map <= 85){
		return creventCheckEvent_Part8(event,map,scene);
	} else if(map <= 90){
		return creventCheckEvent_Part8_2(event,map,scene);
	} else if(map <= 95){
		return creventCheckEvent_Part9(event,map,scene);
	} else if(map <= 110){
		return creventCheckEvent_Part9_2(event,map,scene);
	}

	return 0;
}
