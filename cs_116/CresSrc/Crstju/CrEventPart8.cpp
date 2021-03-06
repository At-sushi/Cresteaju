/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrEventPart8.cpp ...Event functions

-----------------------------------------------------------*/


#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CREVENTPART8

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#include "CrBase.h"
#include "CrBattle.h"
#include "CrEvent.h"
#include "CrEvCom.h"

//---game info
#define CR_GAMEINFO_EXTERNPOINTER
#include "CrGameInfo.h"

#define DC_GET_SCENE() (evGet(186) + 2)

CREVENTLONG5_API int creventGreatCrater_Yokuryu(void);
CREVENTLONG5_API int creventGreatCrater_YokuryuBattle(void);
CREVENTLONG5_API int creventGreatCrater_Seishintai(void);
CREVENTLONG5_API int creventShinkiro_Saijokai(void);
CREVENTLONG5_API int creventHorobi_Koe(void);
CREVENTLONG5_API int creventHorobi_VSCopy(void);

CREVENTLONG6_API int creventWasurerareta_SP(void);
CREVENTLONG6_API int creventWasurerareta_MoveingMachin(void);
CREVENTLONG6_API int creventWasurerareta_VSFollne(void);
CREVENTLONG6_API int creventRyusa_Koegasuru(void);
CREVENTLONG6_API int creventRyusa_Gazell(void);
CREVENTLONG6_API int creventRyusa_Cindy(void);
CREVENTLONG6_API int creventKakutojo(void);

CREVENTLONG7_API int creventGotoKojinsai(void);

CREVENTLONG8_API int crevent_RyunohokoraBattle(void);

CREVENTLONG9_API int crevent_JuleOnsen(void);


CREVENTPART8_API int creventCheckEvent_Part8(int event,int map,int scene)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;
	eiMapObject *pob = crfieldGetObjectPointer(event);

	CR_BATTLEINFO BatInfo;
	memset(&BatInfo,0,sizeof(BatInfo));

	if(map == 81){
		//---流砂の遺跡
		if(scene == 0){
			if(200 <= event && event <= 315){
				//---フィールドへ
				mcDir(SOUTH);
				evMap(10,0,97,75);
			} else if(event == 323 && evGet(209)){
				//---南部大雪原クリア後なら、入れる
				mcDir(SOUTH);
				evScene(1,24,2);
			}
		} else if(scene == 1){
			//---Ｂ１
			if(event == 200){
				//---地上へ
				if(!evGet(218)){
					//---流砂の遺跡をクリアしてないと出られない
					evField(0,1);
					mes.FileMessage("RyusanoIseki.msg",103);
				} else {
					mcDir(SOUTH);
					evScene(0,18,12);
				}
			} else if(event == 201){
				//---Ｂ２へ
				mcDir(SOUTH);
				evScene(2,15,2);
			}
		} else if(scene == 2){
			//---Ｂ２
			if(event == 200){
				//---Ｂ１へ
				mcDir(SOUTH);
				evScene(1,17,12);
			} else if(event == 201){
				//---Ｂ３へ
				mcDir(SOUTH);
				evScene(3,21,45);
			} else if(202 <= event && event <= 204
				&& !evGet(214)){
				return creventRyusa_Koegasuru();
			}
		} else if(scene == 3){
			//---Ｂ３
			if(event == 200){
				//---Ｂ２へ
				mcDir(SOUTH);
				evScene(2,15,31);
			} else if(event == 201){
				//---Ｂ４へ
				mcDir(SOUTH);
				if(evGet(217) == 1 && evGet(218) == 0){
					//---降神祭前
					crmusicPlay(CRMUSIC_DANGEON2);
				}
				evScene(4,26,21);
			} else if(event == 202 && !evGet(215)){
				//---ガゼール救出！
				return creventRyusa_Gazell();
			} else if(event == 202 && evGet(215) && evGet(217) && !evGet(218)){
				//---降神祭へ
				npTurn(6);
				evField(0,1);
				mes.FileMessage("RyusanoIseki.msg",5,1);
				evFrameWait(100);
				if(crbaseSelectYesNo("降神祭へ行きますか？",64,64) == 0){
					//---降神祭へ！
					return creventGotoKojinsai();
				} else {
					evFrameWait(100);
					mcMove(0,-1);
					evFrame();
					mcResetEvent();
				}

			} else if(event == 27){
				//---武器
				int ShopItem[] = {6,18,35,45,57,99,108,115,148,154,263,270,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 28){
				//---道具
				int ShopItem[] = {221,222,226,227,171,172,173,174,175,198,183,158,-1};
				crshopIntoShop(ShopItem);
			} else if(event <= 26){
				int mes_scene = 1;

				if(event == 24 && evGet(219) && evGet(220) && evGet(221)
						&& !evGet(217)){
					//---マークス町長助けに来る！
					return creventRyusa_Cindy();
				} else {
					if(evGet(217))
						mes_scene = 2;

					npTurn(event);
					evField(0,1);
					mes.FileMessage("RyusanoIseki.msg",event,mes_scene);
					evField(0,1);
					if(event == 24){
						//---休憩
						if(crbaseSelectYesNo("休憩しますか？",64,64) == 0){
							evFadeOut();
							et->Delay2(500);
							evFieldNoFlip(0,1);
							prtRecoveryAll();
							evFadeIn();
						}
					}
					npReturn(event);
				}
			}
		} else if(scene == 4){
			//---Ｂ４
			if(event == 200){
				//---Ｂ３へ
				mcDir(SOUTH);
				if(evGet(217) == 1 && evGet(218) == 0){
					//---降神祭前
					crmusicPlay(CRMUSIC_DRAGONBREATH);
				}
				evScene(3,20,2);
			} else if(event == 201){
				//---歩いたフラッグ
				evSet(219,1);
			} else if(event == 202){
				evSet(220,1);
			} else if(event == 203){
				evSet(221,1);
			} else if(event == 0){
				//---宝箱
				itemBox(594,247,event);
			} else if(event == 1){
				//---宝箱
				itemBox(595,224,event);
			} else if(event == 2){
				//---宝箱
				itemBox(596,223,event);
			}
		}
	} else if(map == 82){
		//---蜃気楼の塔
		if(scene == 0){
			if(200 <= event && event <= 259){
				//---フィールドへ
				mcDir(SOUTH);
				evMap(10,0,55,27);
			} else if(event == 260){
				//---内部へ
				mcDir(NORTH);
				evScene(1,18,32);
			}
		} else if(scene == 1){
			//---１Ｆ
			if(200 <= event && event <= 201){
				//---外部へ
				mcDir(SOUTH);
				evScene(0,28,36);
			} else if(event == 202){
				//---２Ｆ−２へ
				mcDir(SOUTH);
				evScene(3,8,3);
			} else if(event == 203){
				//---２Ｆ−１へ
				mcDir(SOUTH);
				evScene(2,19,38);
			} else if(event == 204){
				//---２Ｆ−１へ
				mcDir(SOUTH);
				evScene(2,5,9);
			}
		} else if(scene == 2){
			//---２Ｆ−１
			if(event == 200){
				//---１Ｆへ
				mcDir(SOUTH);
				evScene(1,36,17);
			} else if(event == 201){
				//---１Ｆへ
				mcDir(SOUTH);
				evScene(1,19,2);
			} else if(event == 202){
				//---３Ｆへ
				mcDir(SOUTH);
				evScene(4,18,19);
			}
		} else if(scene == 3){
			//---２Ｆ−２
			if(event == 200){
				//---１Ｆへ
				mcDir(SOUTH);
				evScene(1,2,17);
			} else if(event == 0){
				//---宝箱
				itemBox(581,37,event);
			} else if(event == 1){
				//---宝箱
				itemBox(582,224,event);
			}
		} else if(scene == 4){
			//---３Ｆ
			if(event == 200){
				//---２Ｆ−１へ
				mcDir(SOUTH);
				evScene(2,4,25);
			} else if(event == 201){
				//---４Ｆへ
				mcDir(SOUTH);
				evScene(6,17,15);
			} else if(event == 0){
				//---宝箱
				itemBox(583,221,event);
			} else if(event == 1){
				//---宝箱
				itemBox(584,222,event);
			}
		} else if(scene == 6){
			//---４Ｆ
			if(event == 200){
				//---３Ｆへ
				mcDir(SOUTH);
				evScene(4,14,15);
			} else if(event == 201){
				//---５Ｆへ
				mcDir(SOUTH);
				evScene(5,18,9);
			} else if(event == 0){
				evField(0,1);
				mes.FileMessage("Shinkiro.msg",event + 1);
			} else if(event == 1 && !evGet(197)){
				//---まだ開いてなかったら
				evField(0,1);
				mes.FileMessage("Shinkiro.msg",event + 1);
			} else if(2 <= event && event <= 5){
				//---パネル
				int btn = evGet(193 + (event - 2));
				int sum = evGet(193) + evGet(194) + evGet(195) + evGet(196);
				eistr str[128];

				sprintf(str,"このパネルの入力されている数は: %2d \\n;"
							"                    残りの数は: %2d\\c;",btn,30 - sum);

				mes.CreateNewMessage();
				mes.Message(str);
				mes.Draw();
				mes.CloseMessage();


				CrDigitWindow win;
				evField(0,1);
				win.Create(240,288,12,5,NULL,2);

				crbaseMenuReset();
				crbaseMenuStart();
				win.SetRange(0,30 - sum + btn);
				int new_value = win.GetDigit(btn);

				if(new_value != -1){
					evSet(193 + (event - 2) , new_value);
				}

				crbaseMenuReset();
				crbaseMenuStart();

				if(evGet(193) == 3 && evGet(194) == 6
					&& evGet(195) == 9 && evGet(196) == 12
					&& !evGet(197)){
					//---開いた！
					npDelete(1);

					crsoundPlay(CRSOUND_ATACK4);
					em->Put(20,15,2,1024);
					evFrameWait(250);
					mes.FileMessage("Shinkiro.msg",10);

					evSet(197,1);
				}
			}
		} else if(scene == 5){
			//---５Ｆ
			if(event == 200){
				//---４Ｆへ
				mcDir(SOUTH);
				evScene(6,20,14);
			} else if(event == 201){
				//---６Ｆへ
				mcDir(SOUTH);
				evScene(10,20,20);
			} else if(event == 0){
				//---宝箱
				itemBox(585,227,event);
			}
		} else if(scene == 10){
			//---５−６Ｆ
			if(event == 200){
				//---５Ｆへ
				mcDir(SOUTH);
				evScene(5,22,7);
			} else if(event == 201){
				//---６Ｆへ
				mcDir(SOUTH);
				evScene(7,3,3);
			} else if(event == 0){
				//---宝箱
				itemBox(586,223,event);
			}
		} else if(scene == 7){
			//---６Ｆ
			if(event == 200){
				//---５Ｆへ
				mcDir(SOUTH);
				evScene(10,16,16);
			} else if(event == 201){
				//---７Ｆへ
				mcDir(SOUTH);
				evScene(8,8,8);
			}
		} else if(scene == 8){
			//---７Ｆ
			if(event == 200){
				//---６Ｆへ
				mcDir(SOUTH);
				evScene(7,8,8);
			} else if(event == 201){
				//---最上階へ
				if(!evGet(199)){
					return creventShinkiro_Saijokai();
				} else {
					mcDir(SOUTH);
					evScene(9,11,9);
				}
			}
		} else if(scene == 9){
			//---最上階
			if(event == 200){
				//---７Ｆへ
				mcDir(SOUTH);
				evScene(8,3,3);
			} else if(event == 6){
				evField(0,1);
				mes.FileMessage("Shinkiro.msg",20);
			}
		}
	} else if(map == 83){
		//---大クレーター
		if(scene == 1){
			if(event == 200){
				//---フィールドへ
				crfieldSetMainCharacter(3);
				evSet(EV_GS_NUMBER_STATUS,1);
				mcDir(EAST);
				evFadeOut(2000);
				crfieldChangeMap(10,0,1,1);
				crfieldChangeScene(0,227,53);
				evFieldNoFlip(0,1);
				evFadeIn(1000);
//				evMap(10,0,227,53);
			} else if(event == 201){
				//---Ｂ２へ
				int sc = DC_GET_SCENE();

				mcDir(SOUTH);
				evScene(sc,13,31);
			} else if(event == 0){
				//---宝箱
				itemBox(576,209,event);
			} else if(event == 1){
				//---宝箱
				itemBox(577,224,event);
			}
		} else if(scene == 2 || scene == 3){
			//---Ｂ２
			if(event == 200){
				//---Ｂ１へ
				mcDir(SOUTH);
				evScene(1,22,30);
			} else if(event == 201){
				//---Ｂ４へ
				mcDir(SOUTH);
				evScene(5,5,11);
			} else if(event == 202){
				//---ボタンへ
				mcDir(SOUTH);
				evScene(4,19,3);
			} else if(event == 0){
				//---宝箱
				itemBox(578,228,event);
			}
		} else if(scene == 4){
			//---ボタン
			if(event == 200){
				//---Ｂ２へ
				int sc = DC_GET_SCENE();

				mcDir(SOUTH);
				evScene(sc,30,11);
			} else if(event == 0){
				//---ボタン
				int sc = evGet(186);
				evField(0,1);
				mes.FileMessage("GreatCrater.msg",10 + sc);
				evField(0,1);
				if(crbaseSelectYesNo("操作しますか？",64,64) == 0){
					evSet(186,(evGet(186) + 1) & 0x01);
					evField(0,1);
					mes.FileMessage("GreatCrater.msg",12 + sc);
				}
			}
		} else if(scene == 5){
			//---Ｂ４
			if(event == 200){
				//---Ｂ２へ
				int sc = 3;

				mcDir(SOUTH);
				evScene(sc,8,17);
			} else if(event == 201){
				//---エレベーターへ
				mcDir(NORTH);
				evScene(7,8,22);

				evSet(187,1);
			}
		} else if(scene == 7){
			//---エレベーター
			if(event == 200){
				switch(evGet(187)){
				case 0:
					mcDir(SOUTH);
					evScene(10,11,3);
					break;
				case 1:
					mcDir(SOUTH);
					evScene(5,5,3);
					break;
				case 2:
					mcDir(SOUTH);
					evScene(8,8,3);
					break;
				case 3:
					mcDir(SOUTH);
					evScene(9,12,3);
					break;
				}
			} else if(event == 0){
				//---選択
				evField(0,1);
				mes.FileMessage("GreatCrater.msg",20 + evGet(187));
				mes.FileMessage("GreatCrater.msg",30);

				CrDigitWindow win;
				evField(0,1);
				win.Create(64,64,12,5,NULL,1);

				crbaseMenuReset();
				crbaseMenuStart();
				int new_f = win.GetDigit(evGet(187));

				if(new_f != evGet(187)){
					if(new_f <= 3){
						evFrameWait(250);

						npPos(2,8,16);
						npDir(2,NORTH);
						mcShow(0);

						int dir = 1;
						if(new_f > evGet(187))
							dir = -1;

						for(a = 0;a < 15;a ++){
							mcMove(0,dir);
							evFrame();
						}
						crfieldChangeScene(7,8,16 + (15 * (-dir)));
						for(a = 0;a < 15;a ++){
							mcMove(0,dir);
							evFrame();
						}

						npPos(2,0,0);
						npShow(2,0);
						mcShow(1);
						mcDir(NORTH);

						evSet(187,new_f);
					} else {
						evField(0,1);
						mes.FileMessage("GreatCrater.msg",31);
					}
				}
				evFrameWait(250);
			} else if(event == 1){
				evField(0,1);
				mes.FileMessage("GreatCrater.msg",35);
			}
		} else if(scene == 8){
			//---フロア２
			if(event == 200){
				//---エレベーターへ
				mcDir(NORTH);
				evScene(7,8,22);

				evSet(187,2);
			} else if(event == 0){
				//---宝箱
				itemBox(579,225,event);
			}
		} else if(scene == 9){
			//---フロア３
			if(event == 200){
				//---エレベーターへ
				mcDir(NORTH);
				evScene(7,8,22);

				evSet(187,3);
			}
		} else if(scene == 10){
			//---フロア０
			if(event == 200){
				//---エレベーターへ
				mcDir(NORTH);
				evScene(7,8,22);

				evSet(187,0);
			} else if(event == 201){
				//---実験室へ
				mcDir(NORTH);
				evScene(11,8,22);
			} else if(event == 0){
				//---宝箱
				itemBox(580,223,event);
			}
		} else if(scene == 11){
			//---実験室
			if(event == 200){
				//---フロア０へ
				mcDir(NORTH);
				evScene(10,16,22);
			} else if(event == 201){
				//---最深部へ
				if(!evGet(190)){
					return creventGreatCrater_Seishintai();
				} else {
					mcDir(SOUTH);
					evScene(12,10,9);
				}
			} else if(202 <= event && event <= 204
				&& !evGet(188)){
				return creventGreatCrater_Yokuryu();
			} else if(4 <= event && event <= 6
				&& !evGet(189)){
				//---翼竜バトル！
				return creventGreatCrater_YokuryuBattle();
			}
		} else if(scene == 12){
			//---最深部
			if(event == 200){
				//---実験室へ
				mcDir(SOUTH);
				evScene(11,8,2);
			}
		}
	} else if(map == 84){
		//---ユールクレイラ
		if(scene == 0){
			if(200 <= event && event <= 232){
				//---フィールドへ
				mcDir(SOUTH);
				evMap(10,0,80,316);
			} else if(event == 237){
				//---宿屋２階
				mcDir(SOUTH);
				evScene(2,11,2);
			} else if(event == 238){
				//---地下道入り口
				mcDir(SOUTH);
				evScene(1,10,32);
			} else if(event == 239){
				//---地下道三角
				mcDir(SOUTH);
				evScene(1,22,17);
			} else if(event == 240){
				//---地下道店
				mcDir(SOUTH);
				evScene(1,21,4);
			} else if(event == 245){
				//---温泉
				npTurn(17);
				evField(0,1);
				mes.FileMessage("JuleClara.msg",17);

				evFrameWait(250);
				mcMove(-1,0);
				npReturn(17);
				evFrame();
				mcResetEvent();

				if(evGet(256) == 0){
					return crevent_JuleOnsen();
				}
			} else if(event == 20){
				evYado(750);
			} else if(event == 21){
				//---武器
				int ShopItem[] = {6,18,35,45,57,99,108,115,148,154,263,270,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 22){
				//---道具
				int ShopItem[] = {221,222,226,227,171,172,173,174,175,198,183,178,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 23){
				//---世界地図
				evShowWorldMap(80,316);
			} else if(event <= 26){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("JuleClara.msg",event,mes_scene);
				npReturn(event);
			} else if(event == 241){
				//---タンス／本棚
				itemTansu(891,188);//---道具や
			} else if(event == 242){
				//---タンス／本棚
				itemTansu(892,225);
			} else if(event == 243){
				//---タンス／本棚
				itemTansu(893,222);
			} else if(event == 244){
				//---タンス／本棚
				itemTansu(894,232);
			}
		} else if(scene == 1){
			//---地下道
			if(event == 200){
				//---地下道入り口
				mcDir(SOUTH);
				evScene(0,38,55);
			} else if(event == 201){
				//---地下道三角
				mcDir(SOUTH);
				evScene(0,42,44);
			} else if(event == 202){
				//---地下道店
				mcDir(SOUTH);
				evScene(0,39,27);
			} else if(event <= 1){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("JuleClara.msg",event + 50,mes_scene);
				npReturn(event);
			}
		} else if(scene == 2){
			//---宿屋
			if(event == 200){
				//---１階へ
				mcDir(SOUTH);
				evScene(0,20,8);
			} else if(event <= 1){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("JuleClara.msg",event + 60,mes_scene);
				npReturn(event);
			} else if(event == 201){
				//---タンス／本棚
				itemTansu(895,223);
			}
		}
	} else if(map == 85){
		//---滅びの遺跡
		if(scene == 0){
			//---Ｂ１
			if(event == 200){
				//---フィールドへ
				mcDir(SOUTH);
				evMap(10,0,370,154);
			} else if(event == 201){
				//---Ｂ２へ
				mcDir(SOUTH);
				evScene(1,14,3);
			} else if(202 <= event && event <= 203
				&& !evGet(200)){
				//---
				return creventHorobi_Koe();
			} else if(event == 4){
				//---宝箱
				itemBox(587,222,event);
			} else if(event == 5){
				//---宝箱
				itemBox(588,226,event);
			}
		} else if(scene == 1){
			//---Ｂ２
			if(event == 200){
				//---Ｂ１へ
				mcDir(SOUTH);
				evScene(0,22,43);
			} else if(event == 201){
				//---Ｂ３へ
				mcDir(SOUTH);
				evScene(2,17,29);
			}
		} else if(scene == 2){
			//---Ｂ３
			if(event == 200){
				//---Ｂ２へ
				mcDir(SOUTH);
				evScene(1,32,10);
			} else if(event == 201/* && !evGet(201)*/){
				//---ＶＳコピー！
				return creventHorobi_VSCopy();
			}
		}
	}

	return 1;
}

CREVENTPART8_API int creventCheckEvent_Part8_2(int event,int map,int scene)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;
	eiMapObject *pob = crfieldGetObjectPointer(event);

	CR_BATTLEINFO BatInfo;
	memset(&BatInfo,0,sizeof(BatInfo));

	if(map == 86){
		//---忘れられた遺跡
		if(scene == 0){
			//---Ｂ１
			if(event == 200){
				//---フィールドへ
				mcDir(SOUTH);
				evMap(10,0,195,341);
			} else if(event == 201){
				//---Ｂ２へ
				mcDir(SOUTH);
				evScene(1,32,2);
			} else if(202 == event){
				if(!evGet(209)){
					evField(0,1);
					mes.FileMessage("Wasurerareta.msg",6);
				} else {//13,5
					mcDir(SOUTH);
					evScene(8,9,9);
				}
			} else if(4 == event){
				evField(0,1);
				mes.FileMessage("Wasurerareta.msg",5);
			}
		} else if(scene == 1){
			//---Ｂ２
			if(event == 200){
				//---Ｂ１へ
				mcDir(SOUTH);
				evScene(0,6,27);
			} else if(event == 201){
				//---Ｂ３へ
				mcDir(SOUTH);
				evScene(2,10,2);
			} else if(event == 0){
				//---宝箱
				itemBox(589,222,event);
			} else if(event == 1){
				//---宝箱
				itemBox(590,249,event);
			}
		} else if(scene == 2){
			//---Ｂ３
			if(event == 200){
				//---Ｂ２へ
				mcDir(SOUTH);
				evScene(1,27,56);
			} else if(event == 201){
				//---Ｂ４へ
				mcDir(SOUTH);
				evScene(3,5,3);
			} else if(202 <= event && event <= 203
				&& !evGet(207)){
				return creventWasurerareta_SP();
			} else if(4 <= event && event <= 5){
				evField(0,1);
				mes.FileMessage("Wasurerareta.msg",10 + event - 4);
			}
		} else if(scene == 3){
			//---Ｂ４
			if(event == 200){
				//---Ｂ３へ
				mcDir(SOUTH);
				evScene(2,10,38);
			} else if(event == 201){
				//---小部屋へ
				mcDir(SOUTH);
				evScene(4,7,3);
			} else if(event == 202){
				//---Ｂ５へ
				mcDir(SOUTH);
				evScene(5,3,18);
			} else if(event == 0){
				//---宝箱
				itemBox(591,223,event);
			}
		} else if(scene == 4){
			//---小部屋
			if(event == 200){
				//---Ｂ４へ
				mcDir(SOUTH);
				evScene(3,37,25);
			} else if(event == 0){
				//---宝箱
				itemBox(592,126,event);
			}
		} else if(scene == 5){
			//---Ｂ５
			if(event == 200){
				//---Ｂ４へ
				mcDir(SOUTH);
				evScene(3,52,46);
			} else if(event == 201){
				//---Ｂ６へ
				mcDir(SOUTH);
				evScene(6,15,3);
			} else if(202 <= event && event <= 203
				&& !evGet(208)){
				return creventWasurerareta_MoveingMachin();
			}
		} else if(scene == 6){
			//---Ｂ６
			if(event == 200){
				//---Ｂ５へ
				mcDir(SOUTH);
				evScene(5,44,24);
			} else if(event == 201){
				//---Ｂ７へ
				mcDir(SOUTH);
				evScene(7,5,36);
			} else if(event == 0){
				//---宝箱
				itemBox(593,228,event);
			}
		} else if(scene == 7){
			//---Ｂ７
			if(event == 200){
				//---Ｂ６へ
				mcDir(SOUTH);
				evScene(6,3,39);
			} else if(event == 201){
				//---最下層へ
				mcDir(SOUTH);
				evScene(8,14,21);
			} else if(204 <= event && event <= 205
				&& !evGet(210)){
				//---気配
				evSet(210,1);
				evField(0,1);
				mes.FileMessage("Wasurerareta.msg",105);
			} else if(202 <= event && event <= 203
				&& !evGet(209)){
				//---決戦！
				return creventWasurerareta_VSFollne();
			}
		} else if(scene == 8){
			//---最下層Ｂ７
			if(event == 200){
				//---Ｂ７へ
				mcDir(SOUTH);
				evScene(7,18,6);
			} else if(201 == event){
				mcDir(SOUTH);
				evScene(0,13,5);
			}
		}
	} else if(map == 87){
		//---大雪原の家
		if(scene == 0){
			if(200 <= event && event <= 202){
				mcDir(SOUTH);
				evMap(10,0,198,365);
			} else if(event <= 1){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("Setugen.msg",event,mes_scene);
				npReturn(event);
			} else if(event == 203){
				//---タンス／本棚
				itemTansu(896,232);
			} else if(event == 204){
				//---タンス／本棚
				itemTansu(897,232);
			}
		}
	} else if(map == 88){
		//---小島の洞窟
		if(scene == 0){
			if(event == 200){
				mcDir(SOUTH);
				evMap(10,0,368,63);
			} else if(event == 0){
				//---宝箱
				itemBox(597,220,event);
			} else if(event == 1){
				//---宝箱
				itemBox(598,163,event);
			} else if(event == 2){
				//---宝箱
				itemBox(599,224,event);
			}
		}
	} else if(map == 89){
		//---格闘場
		if(scene == 0){
			//---１Ｆ
			if(200 <= event && event <= 202){
				//---フィールドへ
				mcDir(SOUTH);
				evMap(10,0,299,227);
			} else if(event == 203){
				//---２Ｆへ
				mcDir(SOUTH);
				evScene(1,3,3);
			} else if(event == 204){
				//---２Ｆへ
				mcDir(SOUTH);
				evScene(1,20,3);
			} else if(event == 1){
				//---受付
				return creventKakutojo();
			} else if(event == 8){
				//---宿屋
				evYado(396);
			} else if(event <= 6){
				int mes_scene = 1;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("kakutojo.msg",event,mes_scene);
				npReturn(event);
			}
		} else if(scene == 1){
			//---２Ｆ
			if(event == 200){
				//---１Ｆへ
				mcDir(SOUTH);
				evScene(0,4,13);
			} else if(event == 201){
				//---１Ｆへ
				mcDir(SOUTH);
				evScene(0,21,13);
			} else if(event <= 6){
				int mes_scene = 1;

				npTurn(event);
				evField(0,1);
				if(event == 4 && !evGet(223)){
					mes_scene = 2;
					evSet(223,1);
				}
				mes.FileMessage("kakutojo.msg",event + 20,mes_scene);
				npReturn(event);
			}
		}
	} else if(map == 90){
		//---竜の祠
		if(scene == 0){
			if(200 <= event && event <= 202){
				//---フィールドへ
				mcDir(SOUTH);
				evMap(10,0,264,150);
			} else if(event == 203){
				if(!evGet(250) && critemGetItemCount(239)){
					//---竜の紋章を返す
					evField(0,1);
					mes.OpenMessage("RyunoHokora.msg",100);
					mes.ReadDraw(2);

					evFrameWait(1000);
					mes.ReadDraw();
					evFrameWait(1000);
					mes.ReadDraw();

					evFrameWait(500);
					mes.ReadDraw();

					evFrameWait(1000);
					mes.ReadDraw();
					evFrameWait(1000);
					mes.ReadDraw();

					evFrameWait(500);
					mes.ReadDraw();

					evFrameWait(1000);
					mes.ReadDraw(2);

					mes.CloseMessage();

					evSet(250,1);
					critemAddItem(239,-99);

					evFrameWait(500);
				}

				if(evGet(250) && !evGet(251)){
					//---戦い
					evField(0,1);
					mes.FileMessage("RyunoHokora.msg",11);
					evFrameWait(250);
					if(crbaseSelectYesNo("戦いますか？",64,64) == 0){
						//---戦い
						return crevent_RyunohokoraBattle();
					}
				} else {
					mes.FileMessage("RyunoHokora.msg",10);
				}
			}
		}
	}
	return 1;
}
