/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrEventPart9.cpp ...Event functions

-----------------------------------------------------------*/


#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CREVENTPART9

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#include "CrBase.h"
#include "CrBattle.h"
#include "CrEvent.h"
#include "CrEvCom.h"

//---game info
#define CR_GAMEINFO_EXTERNPOINTER
#include "CrGameInfo.h"

CREVENTLONG8_API int crevent_CarCdr(void);
CREVENTLONG8_API int crevent_IllidiaMessage1(void);
CREVENTLONG8_API int crevent_IllidiaLunarnsRoom(void);
CREVENTLONG8_API int crevent_IllidiaLastBattle(void);
CREVENTLONG9_API int crevent_HomotukoChika(void);

CREVENTLONG_ENDING_API int crevent_EndingSorekara(void);
CREVENTLONG_ENDING_API int crevent_EndingMatsuri6(void);
CREVENTLONG_ENDING_API int crevent_EndingTheEnd(void);
CREVENTLONG9_API int crevent_TreiaSS2(void);

CREVENTLONG8_API int crevent_IllidiaDeen(void);


CREVENTPART9_API int creventCheckEvent_Part9(int event,int map,int scene)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;
	eiMapObject *pob = crfieldGetObjectPointer(event);

	CR_BATTLEINFO BatInfo;
	memset(&BatInfo,0,sizeof(BatInfo));

	if(map == 91){
		//---野原のタンス
		if(scene == 0){
			if(200 <= event && event <= 256){
				mcDir(SOUTH);
				evMap(10,0,137,176);
			} else if(event == 0 && !evGet(898)){
				//---タンス！
				evField(0,1);
				mes.FileMessage("NoharanoTansu.msg",100);
				//---タンス／本棚
				itemTansu(898,225);
			}
		}
	} else if(map == 92){
		//---イリーディア
		if(scene == 0){
			//---Ａ−１
			if(event == 200){
				//---中央山脈へ
				crmusicFadeOut();
				crsoundPlay(CRSOUND_KIDOU);
				evFadeOut(1000);
				et->Delay2(1200);
				crfieldChangeMap(38,10,1,1);
				crfieldChangeScene(10,10,18);
				evFieldNoFlip(0,1);
				evFadeIn(1000);
			} else if(event == 201){
				//---Ａ−２へ
				mcDir(SOUTH);
				evScene(1,2,3);
			} else if(event == 202){
				//---移動装置
				if(evGet(242)){
					//---皇宮へ
					mcDir(SOUTH);
					crsoundPlay(CRSOUND_KIDOU);
					evMap(95,2,4,6);
				} else {
					evField(0,1);
					mes.FileMessage("Illeadia.msg",22);
				}
			}
		} else if(scene == 1){
			//---Ａ−２
			if(event == 200){
				//---Ａ−１へ
				mcDir(SOUTH);
				evScene(0,4,17);
			} else if(event == 201){
				//---Ａ−３へ
				mcDir(SOUTH);
				evScene(2,3,3);
			} else if(event == 0){
				//---宝箱
				itemBox(600,248,event);
			}
		} else if(scene == 2){
			//---Ａ−３
			if(event == 200){
				//---Ａ−２へ
				mcDir(SOUTH);
				evScene(1,22,3);
			} else if(event == 201){
				//---Ａ−４へ
				mcDir(SOUTH);
				evScene(3,2,5);
			} else if(event == 0){
				//---宝箱
				itemBox(601,224,event);
			}
		} else if(scene == 3){
			//---Ａ−４
			if(event == 200){
				//---Ａ−３へ
				mcDir(SOUTH);
				evScene(2,10,24);
			} else if(event == 201){
				//---Ａ−５へ
				mcDir(SOUTH);
				evScene(4,7,3);
			}
		} else if(scene == 4){
			//---Ａ−５
			if(event == 200){
				//---Ａ−４へ
				mcDir(SOUTH);
				evScene(3,28,6);
			} else if(201 <= event && event <= 202){
				//---エリアＢへ
				if(!evGet(246)){
					return crevent_IllidiaMessage1();
				} else {
					mcDir(SOUTH);
					evScene(5,10,11);
				}
			}
		} else if(scene == 5){
			//---Ｂ−１
			if(event == 200){
				//---Ａ−５へ
				mcDir(NORTH);
				evScene(4,6,8);
			} else if(event == 201){
				//---Ｂ−２へ
				mcDir(SOUTH);
				evScene(6,7,4);
			} else if(event == 202){
				//---Ｂ−３へ
				mcDir(SOUTH);
				evScene(7,7,10);
			} else if(event == 203){
				//---倉庫へ
				mcDir(NORTH);
				evScene(8,7,14);
			} else if(event == 204){
				//---研究所へ
				mcDir(NORTH);
				evMap(93,7,14,15);
			} else if(event == 205){
				//---研究所へ（隠し通路）
				mcDir(SOUTH);
				evMap(93,7,10,5);
			} else if(event == 0){
				//---パネル
				evField(0,1);
				mes.FileMessage("Illeadia.msg",10);
			} else if(event == 1){
				//---回復の泉
				prtRecoveryAll();
				evField(0,1);
				mes.FileMessage("Illeadia.msg",11);
			} else if(event == 2){
				//---宝箱
				itemBox(602,225,event);
			} else if(event == 3){
				//---宝箱
				itemBox(603,169,event);
			} else if(event == 4){
				//---宝箱
				itemBox(604,228,event);
			} else if(event == 5){
				//---宝箱
				itemBox(622,224,event);
			}
		} else if(scene == 6){
			//---Ｂ−２
			if(event == 200){
				//---Ｂ−１へ
				mcDir(SOUTH);
				evScene(5,42,39);
			} else if(event == 201){
				//---Ｂ−３へ
				mcDir(SOUTH);
				evScene(7,7,5);
			}
		} else if(scene == 7){
			//---Ｂ−３
			if(event == 200){
				//---Ｂ−２へ
				mcDir(SOUTH);
				evScene(6,7,11);
			} else if(event == 201){
				//---Ｂ−１へ
				mcDir(SOUTH);
				evScene(5,41,50);
			}
		} else if(scene == 8){
			//---倉庫
			if(200 <= event && event <= 202){
				//---Ｂ−１へ
				mcDir(SOUTH);
				evScene(5,76,16);
			} else if(203 <= event && event <= 205
				&& !evGet(245)){
				//---カー＆クダー
				return crevent_CarCdr();
			} else if(event == 0){
				//---宝箱
				itemBox(605,135,event);
			} else if(event == 1){
				//---宝箱
				itemBox(606,70,event);
			} else if(event == 2){
				//---宝箱
				itemBox(607,224,event);
			}
		}
	} else if(map == 93){
		//---イリーディア・研究所
		if(scene == 0){
			//---部屋
			if(event == 200){
				mcDir(SOUTH);
				evScene(1,1,15);
			} else if(event == 0){
				//---盾
				if(evGet(164) && !evGet(241)){
					evField(0,1);
					mes.FileMessage("Illeadia.msg",15);
					evSet(241,1);
					critemAddItem(170,1);
				}
			}
		} else if(scene == 1){
			//---廊下
			if(event == 200){
				//---ルナンの部屋へ
				if(!evGet(247)){
					return crevent_IllidiaLunarnsRoom();
				} else {
					mcDir(SOUTH);
					evScene(0,13,5);
				}
			} else if(event == 201){
				mcDir(SOUTH);
				evScene(2,1,16);
			} else if(event == 202){
				//---出口へ
				mcDir(SOUTH);
				evScene(10,2,4);
			} else if(event == 12){
				//---壊れた天気予報
				evField(0,1);
				mes.FileMessage("Illeadia.msg",12);
			} else if(event == 0){
				//---宝箱
				itemBox(610,228,event);
			} else if(event <= 20){
				//---パネル
				evField(0,1);
				mes.FileMessage("Illeadia.msg",14);
			}
		} else if(scene == 2){
			//---ロビー
			if(event == 200){
				mcDir(SOUTH);
				evScene(1,53,15);
			} else if(event == 201){
				mcDir(SOUTH);
				evScene(3,2,2);
			} else if(event == 202){
				//---通路へ
				mcDir(SOUTH);
				evScene(6,2,5);
			} else if(event == 6){
				//---壊れた天気予報
				evField(0,1);
				mes.FileMessage("Illeadia.msg",13);
			} else if(event <= 10){
				//---パネル
				evField(0,1);
				mes.FileMessage("Illeadia.msg",14);
			}
		} else if(scene == 3){
			//---倉庫
			if(event == 200){
				mcDir(SOUTH);
				evScene(2,17,32);
			}
		} else if(scene == 6){
			//---通路
			if(event == 200){
				//---地下へ
				mcDir(SOUTH);
				evScene(9,3,7);
			} else if(event == 201){
				//---ロビーへ
				mcDir(SOUTH);
				evScene(2,45,16);
			}
		} else if(scene == 7){
			//---研究所入り口
			if(200 <= event && event <= 202){
				//---エリアＢへ
				mcDir(SOUTH);
				evMap(92,5,78,46);
			} else if(event == 203){
				//---２Ｆへ
				mcDir(SOUTH);
				evScene(8,3,3);
			} else if(event == 204){
				//---地下へ
				mcDir(SOUTH);
				evScene(9,7,3);
			} else if(event == 205){
				//---エリアＢへ（隠し通路）
				mcDir(SOUTH);
				evMap(92,5,74,37);
			} else if(event == 0 && !evGet(238)){
				//---隠し通路発見へ
				crsoundPlay(CRSOUND_ATACK4);
				em->Put(10,5,2,1024);
				evFrameWait(100);
				evSet(238,1);
			}
		} else if(scene == 8){
			//---研究所２Ｆ
			if(event == 200){
				//---入り口へ
				mcDir(SOUTH);
				evScene(7,5,7);
			} else if(event == 0){
				//---宝箱
				itemBox(608,137,event);
			} else if(event == 1){
				//---宝箱
				itemBox(609,228,event);
			}
		} else if(scene == 9){
			//---研究所地下
			if(event == 200){
				//---入り口へ
				mcDir(SOUTH);
				evScene(7,14,9);
			} else if(event == 201){
				//---通路へ
				mcDir(SOUTH);
				evScene(6,8,2);
			}
		} else if(scene == 10){
			//---研究所出口
			if(event == 200){
				//---廊下へ
				mcDir(SOUTH);
				evScene(1,10,26);
			} else if(event == 201){
				//---エリアＤへ
				mcDir(SOUTH);
				evMap(94,0,12,38);
			}
		}
	} else if(map == 94){
		//---イリーディア、エリアＤ
		if(scene == 0){
			//---Ｄ−１
			if(event == 200){
				//---研究所へ
				mcDir(NORTH);
				evMap(93,10,29,5);
			} else if(201 <= event && event <= 205){
				//---Ｄ−２へ
				mcDir(NORTH);
				evScene(1,23,50);
			} else if(event == 0){
				//---宝箱
				itemBox(611,239,event);//---竜の紋章
			}
		} else if(scene == 1){
			//---Ｄ−２（皇宮前）
			if(200 <= event && event <= 204){
				//---Ｄ−１へ
				mcDir(SOUTH);
				evScene(0,30,8);
			} else if(205 <= event && event <= 207){
				//---皇宮へ
				mcDir(NORTH);
				evMap(95,0,16,27);
			} else if(event == 208){
				//---移動装置へ
				mcDir(SOUTH);
				evScene(2,8,3);
			} else if(event == 209){
				//---宝物庫へ
				mcDir(NORTH);
				evScene(3,5,7);
			} else if(event == 0){
				//---回復の泉
				prtRecoveryAll();
				evField(0,1);
				mes.FileMessage("Illeadia.msg",11);
			} else if(event == 1){
				//---宝箱
				itemBox(612,184,event);//---プラスエクステンダー
			}
		} else if(scene == 2){
			//---移動装置
			if(event == 200){
				//---中央山脈・別の場所２へ
				crmusicFadeOut();
				crsoundPlay(CRSOUND_KIDOU);
				evFadeOut(1000);
				et->Delay2(1200);
				crfieldChangeMap(38,12,1,1);
				crfieldChangeScene(12,17,4);
				evFieldNoFlip(0,1);
				evFadeIn(1000);
			} else if(event == 201){
				//---Ｄ−２へ
				mcDir(SOUTH);
				evScene(1,4,43);
			}
		} else if(scene == 3){
			//---宝物庫
			if(event == 200){
				//---Ｄ−２へ
				mcDir(SOUTH);
				evScene(1,12,16);
			} else if(event == 201){
				//---宝物庫地下へ
				mcDir(SOUTH);
				evScene(4,2,3);
			}
		} else if(scene == 4){
			//---宝物庫地下
			if(event == 200){
				//---宝物庫へ
				mcDir(SOUTH);
				evScene(3,7,3);
			} else if(201 <= event && event <= 202
				&& !evGet(249)){
				//---バリアー２０００ボス！！
				return crevent_HomotukoChika();
			} else if(event == 0){
				//---宝箱
				itemBox(617,223,event);
			} else if(event == 1){
				//---宝箱
				itemBox(618,225,event);
			} else if(event == 2){
				//---宝箱
				itemBox(619,62,event);//---ソニックガン
			} else if(event == 3){
				//---宝箱
				itemBox(620,220,event);//---ダイヤ原石
			} else if(event == 4){
				//---宝箱
				itemBox(621,139,event);//---オウ・ティーヴァ
			}
		}
	} else if(map == 95){
		//---イリーディア、皇宮
		if(scene == 0){
			//---Ｅ−１
			if(200 <= event && event <= 202){
				//---エリアＤへ
				mcDir(SOUTH);
				evMap(94,1,23,11);
			} else if(event == 203){
				//---Ｅ−２へ
				mcDir(SOUTH);
				evScene(1,2,16);
			} else if(event == 204){
				//---Ｅ−２へ
				mcDir(SOUTH);
				evScene(1,21,16);
			}
		} else if(scene == 1){
			//---Ｅ−２
			if(event == 200){
				//---Ｅ−１へ
				mcDir(SOUTH);
				evScene(0,5,5);
			} else if(event == 201){
				//---Ｅ−１へ
				mcDir(SOUTH);
				evScene(0,29,5);
			} else if(event == 202){
				//---移動装置へ
				mcDir(SOUTH);
				evScene(2,7,3);
			} else if(event == 203){
				//---Ｅ−３へ
				mcDir(SOUTH);
				evScene(3,4,24);
			} else if(event == 2){
				evField(0,1);
				mes.FileMessage("Illeadia.msg",16);
			} else if(event == 0){
				//---宝箱
				itemBox(613,136,event);//---アーガイルプレート
			} else if(event == 1){
				//---宝箱
				itemBox(614,48,event);//---ミストラルジャック
			}
		} else if(scene == 2){
			//---移動装置
			if(event == 200){
				//---Ｅ−２へ
				mcDir(SOUTH);
				evScene(1,20,7);
			} else if(event == 201){
				//---移動装置
				if(evGet(242)){
					//---入り口
					mcDir(SOUTH);
					crsoundPlay(CRSOUND_KIDOU);
					evMap(92,0,17,4);
				} else {
					evField(0,1);
					mes.FileMessage("Illeadia.msg",22);
				}
			} else if(event == 0){
				evField(0,1);
				if(!evGet(242)){
					//---起動させるか？
					mes.FileMessage("Illeadia.msg",20);
					evField(0,1);
					if(crbaseSelectYesNo("起動させますか？",64,64) == 0){
						crsoundPlay(CRSOUND_KIDOU);
						evSet(242,1);
					}
				} else {
					mes.FileMessage("Illeadia.msg",21);
				}
			}
		} else if(scene == 3){
			//---Ｅ−３
			if(event == 200){
				//---Ｅ−２へ
				mcDir(SOUTH);
				evScene(1,12,2);
			} else if(event == 201){
				//---Ｅ−４へ
				mcDir(SOUTH);
				evScene(4,8,9);
			}
		} else if(scene == 4){
			//---Ｅ−４
			if(event == 200){
				//---Ｅ−３へ
				mcDir(SOUTH);
				evScene(3,4,2);
			} else if(201 <= event && event <= 203){
				//---Ｅ−５（王間）へ
				mcDir(NORTH);
				evScene(5,12,18);
			}
		} else if(scene == 5){
			//---Ｅ−５
			if(200 <= event && event <= 202){
				//---Ｅ−４へ
				mcDir(SOUTH);
				evScene(4,8,3);
			} else if(204 <= event && event <= 206
				&& !evGet(263)){
				//---ディーンの声
				return crevent_IllidiaDeen();
			} else if(event == 203){
				//---Ｅ−６へ
				mcDir(SOUTH);
				evScene(6,5,31);
			} else if(event == 0){
				//---宝箱
				itemBox(615,38,event);//---フィルガルト
			} else if(event == 1){
				//---宝箱
				itemBox(616,191,event);//---ルビートゥース
			}
		} else if(scene == 6){
			//---Ｅ−６
			if(event == 200){
				//---Ｅ−５へ
				mcDir(SOUTH);
				evScene(5,42,6);
			} else if(event == 202 || event == 203){
				//---To 1
				crfieldChangePlane(1);
			} else if(event == 204 || event == 205){
				//---To 3
				crfieldChangePlane(3);
			} else if(event == 206 || event == 207){
				//---To 1
				crfieldChangePlane(1);
			} else if(event == 208 || event == 209){
				//---To 3
				crfieldChangePlane(3);
			} else if(event == 201){
				//---Ｅ−７へ
				mcDir(SOUTH);
				evScene(7,16,2);
			} else if(event == 210){
				//---Ｅ−８へ
				mcDir(SOUTH);
				evScene(8,9,11);
			} else if(event == 0){
				//---ラストバトル！！
				return crevent_IllidiaLastBattle();
			}
		} else if(scene == 7){
			//---Ｅ−７
			if(event == 200){
				//---Ｅ−６へ
				mcDir(SOUTH);
				evScene(6,42,31);
			} else if(event == 201){
				//---Ｅ−８へ
				mcDir(SOUTH);
				evScene(8,23,11);
			}
		} else if(scene == 8){
			//---Ｅ−８
			if(event == 200){
				//---Ｅ−７へ
				mcDir(SOUTH);
				evScene(7,2,13);
			} else if(event == 201){
				//---Ｅ−６へ
				mcDir(SOUTH);
				evScene(6,22,42);
			}
		}
//----------------------------
	}

	return 1;
}


CREVENTPART9_API int creventCheckEvent_Part9_2(int event,int map,int scene)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;
	eiMapObject *pob = crfieldGetObjectPointer(event);

	CR_BATTLEINFO BatInfo;
	memset(&BatInfo,0,sizeof(BatInfo));

	if(map == 96){
		if(scene == 0){
		}
	} else if(map == 97){
		//---毛糸屋さん
		if(scene == 0){
			if(200 <= event && event <= 201){
				//---フィールドへ
				mcDir(SOUTH);
				evMap(10,0,322,46);
			} else if(event == 0){
				npTurn(event);
				evField(0,1);

//				critemAddItem(213,99);

				mes.FileMessage("keito.msg",event);
				evField(0,1);

				int kosu[] = {2,5,7,8,10,15,20},
					item_list[] = {222,131,130,275,223,47,228};
				CRWIN_SELECTINFO info;
				eistr s[80];
				eistr str[] =
					"ライフカプセルＳ　　２個;"
					"セーター　　　　　　５個;"
					"毛糸のローブ　　　　７個;"
					"イーグルスカーフ　　８個;"
					"マジックカプセル　１０個;"
					"ウィザードナイフ　１５個;"
					"ラケシスの聖杯　　２０個;";
				CrSelectWindow win;
				CrStringWindow keito;
				int sel;

				memset(&info,0,sizeof(info));

				win.Create(64,64,20,11,"どれと交換しますか？",str);

				do {
					crbaseMenuReset();

					keito.Create(64,256,10,2);
					keito.Reset();
					keito.SetColor(CRCOLOR_WHITE);
					keito.DrawText(" 毛糸 : ");
					sprintf(s,"%2d",critemGetItemCount(213));
					keito.SetColor(CRCOLOR_YELLOW);
					keito.DrawText(s);
					keito.SetColor(CRCOLOR_WHITE);
					keito.DrawText("個");
					keito.Refresh();

					win.Paint();
					win.Refresh();
					crbaseMenuStart();
					sel = win.Select(&info);

					if(sel != -1){
						int count = critemGetItemCount(213);

						if(count < kosu[sel]){
							//---足りない
							evField(0,1);
							mes.FileMessage("keito.msg",100);
							continue;
						} else {
							sprintf(s,"%s でいいですか？",critemGetItemClass(item_list[sel])->GetName());
							if(crbaseSelectYesNo(s,80,80) == 0){
								evField(0,1);
								mes.FileMessage("keito.msg",101);

								mes.CreateNewMessage();
								sprintf(s,"%s を手に入れた\\c;",critemGetItemClass(item_list[sel])->GetName());
								mes.Message(s);
								mes.Draw();
								mes.CloseMessage();

								critemAddItem(213,-kosu[sel]);
								critemAddItem(item_list[sel],1);

								break;
							}
							continue;
						}
					}
					break;
				} while(1);

				crbaseMenuReset();
				crbaseMenuStart();

				npReturn(event);
			} else if(event == 1){
				evField(0,1);
				npTurn(event);
				evField(0,1);
				mes.FileMessage("keito.msg",event);
				npReturn(event);
			}
		}
	} else if(map == 98){
		//---トレイアの洞窟
		if(scene == 0){
			if(200 == event){
				mcDir(SOUTH);
				evMap(10,0,253,150);
			} else if(201 == event && evGet(255) == 1
				&& AFTER_KOJINSAI()){
				//---シューティングスター２
				return crevent_TreiaSS2();
			}
		}
	} else if(map == 101){
		//---エンディング
		if(scene == 1){
			if(200 <= event && event <= 219){
				return crevent_EndingSorekara();
			}
		}
	} else if(map == 103){
		//---エンディング
		if(scene == 0){
			if(207 <= event && event <= 210){
//				return crevent_EndingTheEnd();
				return crevent_EndingMatsuri6();
			}
		}
	}
	return 1;
}
