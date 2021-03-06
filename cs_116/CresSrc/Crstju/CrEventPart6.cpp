/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrEventPart6.cpp ...Event functions

-----------------------------------------------------------*/


#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CREVENTPART6

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#include "CrBase.h"
#include "CrBattle.h"
#include "CrEvent.h"
#include "CrEvCom.h"

//---game info
#define CR_GAMEINFO_EXTERNPOINTER
#include "CrGameInfo.h"

CREVENTLONG4_API int creventTuria_MeetGazell(void);
CREVENTLONG4_API int creventTuria_BoueiSystem(void);
CREVENTLONG4_API int creventTuriaEternal_Follne(void);
CREVENTLONG4_API int creventTuriaEternal_Dasshutu(void);
CREVENTLONG4_API int creventGiedie_Lizel(void);
CREVENTLONG4_API int creventKiokunoIseki_Kessen(void);
CREVENTLONG4_API int creventKiokunoIseki_Taisho(void);
CREVENTLONG4_API int creventKiokunoIseki_OnlyLunarn(void);
CREVENTLONG4_API int creventKiokunoIseki_MemoryOve(void);
CREVENTLONG4_API int creventKiokunoIseki_Dasshutu(void);

CREVENTLONG9_API int crevent_TuriaEdo(void);


CREVENTPART6_API int creventCheckEvent_Part6(int event,int map,int scene)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;
	eiMapObject *pob = crfieldGetObjectPointer(event);

	CR_BATTLEINFO BatInfo;
	memset(&BatInfo,0,sizeof(BatInfo));

	if(map == 61){
		//---ツーリア
		if(scene == 0){
			if(200 <= event && event <= 203){
				//---フィールドへ
				if(evGet(142) && !evGet(143)){
					//---ツーリアから出られない！
					evField(0,1);

					mes.FileMessage("Turia.msg",103);

					mcMove(0,1);
					evFrame();
					mcResetEvent();
				} else {
					mcDir(NORTH);
					evMap(10,0,330,231);
				}
			} else if(event == 204){
				//---宿屋２階へ
				mcDir(SOUTH);
				evScene(1,18,2);
			} else if(event == 205){
				//---地下へ
				mcDir(SOUTH);
				evScene(2,3,3);
			} else if(event == 223){
				//---奴隷地下へ
				mcDir(NORTH);
				evScene(3,5,11);
			} else if(event == 226){
				//---エターナル建物２階へ
				mcDir(NORTH);
				evMap(64,3,6,29);
			} else if(event == 227 || event == 228){
				//---エターナル建物へ
				mcDir(NORTH);
				evMap(64,2,28,7);
			} else if(event == 206 && !(AFTER_YUMI())){
				//---奴隷領域へ
				//---入れない
				npTurn(36);
				evField(0,1);

				mes.FileMessage("Turia.msg",36);

				mcMove(-1,0);
				npReturn(36);
				evFrame();
				mcResetEvent();
			} else if(event == 207 && !(AFTER_YUMI())){
				//---エターナル領域へ
				//---入れない
				npTurn(37);
				evField(0,1);

				mes.FileMessage("Turia.msg",37);

				mcMove(0,-1);
				npReturn(37);
				evFrame();
				mcResetEvent();
			} else if(event == 48){
				if(evGet(142) && !evGet(143)){
					//---ガゼールとの再会
					return creventTuria_MeetGazell();
				}
			} else if(event == 40){
				//---宿
				if(evGet(142) && !evGet(143)){
					//---情報集め中
					evField(0,1);
					mes.FileMessage("Turia.msg",event,1);
				} else {
					evYado(320,map,scene);
				}
			} else if(event == 42){
				//---武器
				int ShopItem[] = {16,33,43,55,97,106,113,146,152,261,268,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 41){
				//---道具
				int ShopItem[] = {221,222,226,227,171,172,173,175,177,181,201,197,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 38){
				//---世界地図
				evShowWorldMap(330,231);
			} else if(event <= 57){
				int mes_scene = 1;

				if(evGet(252) && event == 57 && !evGet(253)){
					//---エド
					return crevent_TuriaEdo();
				}

				if(event == 25 || event == 28)
					npDir(event,EAST);
				else if(event == 34)
					npDir(event,SOUTH);
				else
					npTurn(event);

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				evField(0,1);
				mes.FileMessage("Turia.msg",event,mes_scene);

				if(event == 25)
					npDir(event,SOUTH);
				else if(event == 28)
					npDir(event,NORTH);
				else if(event == 34)
					npDir(event,SOUTH);
				else
					npReturn(event);
			} else if(event == 220){
				//---タンス／本棚
				itemTansu(862,223);
			} else if(event == 221){
				//---タンス／本棚
				itemTansu(863,232);
			} else if(event == 222){
				//---タンス／本棚　よんきゅう
				itemTansu(864,22);//132);

			} else if(event == 224){
				//---タンス／本棚　奴隷
				itemTansu(867,257);
			} else if(event == 225){
				//---タンス／本棚　奴隷
				itemTansu(868,90);
			}
		} else if(scene == 1){
			//---宿屋２階
			if(event == 200){
				//---１階へ
				mcDir(SOUTH);
				evScene(0,13,5);
			} else if(event == 201){
				//---タンス／本棚
				itemTansu(865,221);//243);
			} else if(event == 202){
				//---タンス／本棚
				itemTansu(866,222);
			}
		} else if(scene == 2){
			//---地下
			if(event == 200){
				//---地上へ
				mcDir(SOUTH);
				evScene(0,42,23);
			} else if(event == 201){
				//---地下通路へ
				if(evGet(143)){
					mcDir(SOUTH);
					evMap(63,0,2,3);
				}
			}
		} else if(scene == 3){
			//---奴隷地下
			if(event == 200){
				//---地上へ
				mcDir(SOUTH);
				evScene(0,96,40);
			} else if(event == 201){
				//---地下通路へ
				if(evGet(143)){
					mcDir(SOUTH);
					evMap(63,5,23,26);
				}
			}//223,96,40
		}//5,11,  201:4,3
	} else if(map == 62){
		//---ツーリア港
		if(scene == 0){
			if(200 <= event && event <= 202){
				//---フィールドへ
				mcDir(SOUTH);
				evMap(10,0,331,221);
			} else if(event == 203){
				//---入れない
				npTurn(1);
				evField(0,1);

				if(evGet(154) && !evGet(157)){
					//---ジーダイへ
					mes.FileMessage("TuriaPort.msg",20,2);
					evFrameWait(250);

					ef->SetMoveEnything(1);
					int keep = ef->SetMoveSpeed(2);
					mcDir(EAST);
					crfieldChangeMap(10,0,1);
					crfieldSetMainCharacter(5);
					evScene(0,332,221);
					evFrameWait(250);
					for(a = 0;a < 10;a ++){
						mcMove(1,0);
						evFrame();
					}
					for(a = 0;a < 2;a ++){
						mcMove(0,1);
						evFrame();
					}
					for(a = 0;a < 12;a ++){
						mcMove(1,0);
						evFrame();
					}
					ef->SetMoveSpeed(keep);
					ef->SetMoveEnything(0);
					evFrameWait(250);
					crfieldSetMainCharacter(1);

					evMap(67,0,28,12);
					mcDir(EAST);

					evSet(157,1);
				} else {
					mes.FileMessage("TuriaPort.msg",20,1);

					mcMove(-1,0);
					npReturn(1);
					evFrame();
					mcResetEvent();
				}
			} else if(event <= 10){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("TuriaPort.msg",event,mes_scene);

				npReturn(event);
			}	
		}
	} else if(map == 63){
		//---ツーリア地下通路
		if(scene == 0){
			if(event == 200){
				//---ツーリアへ
				mcDir(SOUTH);
				evMap(61,2,13,2);
			} else if(event == 201){
				//---Ｂ２−ツーリアへ
				mcDir(SOUTH);
				evScene(1,5,29);
			} else if(event == 0){
				//---宝箱
				itemBox(558,223,event);
			}
		} else if(scene == 1){
			//---Ｂ２−ツーリア
			if(event == 200){
				//---Ｂ１−ツーリアへ
				mcDir(SOUTH);
				evScene(0,33,24);
			} else if(event == 201){
				//---Ｂ３
				mcDir(SOUTH);
				evScene(2,3,40);
			} else if(event == 0){
				//---宝箱
				itemBox(559,227,event);
			} else if(event == 1){
				//---宝箱
				itemBox(560,43,event);
			}
		} else if(scene == 2){
			//---Ｂ３
			if(event == 200){
				//---Ｂ２−ツーリアへ
				mcDir(SOUTH);
				evScene(1,5,4);
			} else if(event == 201){
				//---Ｂ２−エターナルへ
				mcDir(SOUTH);
				evScene(4,39,25);
			} else if(event == 202){
				//---Ｂ２−奴隷へ
				mcDir(SOUTH);
				evScene(6,4,4);
			} else if(203 <= event && event <= 205
				&& !evGet(149)){
				//---ＶＳ防衛システム！！
				return creventTuria_BoueiSystem();
			} else if(206 <= event && event <= 208
				&& !evGet(150)){
				//---怪しいね
				evFrameWait(250);
				mes.FileMessage("TuriaChika.msg",103);
				evSet(150,1);
			} else if(event == 0){
				//---宝箱
				itemBox(561,61,event);
			}
//-------------------------------------
		} else if(scene == 3){
			//---Ｂ１−エターナル
			if(event == 200){
				//---Ｂ２−エターナルへ
				mcDir(SOUTH);
				evScene(4,4,21);
			} else if(event == 201){
				//---エターナル領内へ
				mcDir(SOUTH);
				evMap(64,2,4,29);
			} else if(event == 0){
				//---宝箱
				itemBox(562,132,event);
			}
		} else if(scene == 4){
			//---Ｂ２−エターナル
			if(event == 200){
				//---Ｂ３へ
				mcDir(SOUTH);
				evScene(2,40,50);
			} else if(event == 201){
				//---Ｂ２−エターナルへ
				mcDir(SOUTH);
				evScene(3,28,3);
			} else if(event == 202){
				//---タンス／本棚
				itemTansu(869,243);//---豆腐概論
			} else if(event == 203){
				//---タンス／本棚
				itemTansu(870,225);
			} else if(event == 0){
				//---宝箱
				itemBox(563,228,event);
			}
//-------------------------------------
		} else if(scene == 5){
			//---Ｂ１−奴隷
			if(event == 200){
				//---Ｂ２−奴隷へ
				mcDir(SOUTH);
				evScene(6,28,21);
			} else if(event == 201){
				//---奴隷領内へ
				mcDir(SOUTH);
				evMap(61,3,4,3);
			}
		} else if(scene == 6){
			//---Ｂ２−奴隷
			if(event == 200){
				//---Ｂ３へ
				mcDir(SOUTH);
				evScene(2,65,9);
			} else if(event == 201){
				//---Ｂ２−奴隷へ
				mcDir(SOUTH);
				evScene(5,3,3);
			}
		}
	} else if(map == 64){
		//---ツーリアエターナル建物
		if(scene == 0){
			//---Ｂ２Ｆ
			if(event == 200){
				//---Ｂ１Ｆ9
				mcDir(SOUTH);
				evScene(1,5,43);
			} else if(event <= 3){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("TuriaEternal.msg",event + 50,mes_scene);
				evSet(151 + (event - 1),1);
				npReturn(event);

				if(evGet(151) && evGet(152) && evGet(153)
					&& !evGet(155)){
					//---フォールン登場！
					return creventTuriaEternal_Follne();
				}
			} else if((event == 201 || event == 202) && !evGet(156)){
				//---泊まれそう
				evFrameWait(250);
				mcDir(NORTH);
				evFrameWait(500);
				mes.FileMessage("TuriaEternal.msg",102);
				evSet(156,1);
			} else if(203 <= event && event <= 205){
				//---泊まる？
				if(crbaseSelectYesNo("休憩しますか？",64,64) == 0){
					evFrameWait(100);
					evFadeOut();
					et->Delay2(200);
					prtRecoveryAll();
					mcDir(SOUTH);
					evFieldNoFlip(0,1);
					evFadeIn();
				}
			}
		} else if(scene == 1){
			//---Ｂ１Ｆ
			if(event == 200){
				mcDir(SOUTH);
				evScene(0,36,4);
			} else if(event == 201){
				mcDir(SOUTH);
				evScene(2,45,4);
			} else if((event == 203 || event == 204) && !evGet(154)){
				//---フォールン！！〜ツーリア脱出
				return creventTuriaEternal_Dasshutu();
			} else if(event <= 10){
				int mes_scene = 1;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("TuriaEternal.msg",event + 25,mes_scene);

				npReturn(event);
			} else if(event == 202){
				//---タンス／本棚
				itemTansu(872,213);
			}
		} else if(scene == 2){
			//---１Ｆ
			if(203 <= event && event <= 204){
				//---ツーリアへ
				mcDir(SOUTH);
				evMap(61,0,14,51);
			} else if(event == 200){//2,12  4,29
				//---Ｂ１Ｆへ
				mcDir(SOUTH);
				evScene(1,41,10);
			} else if(event == 201){
				//---２Ｆへ
				mcDir(SOUTH);
				evScene(3,53,4);
			} else if(event == 202){
				//---２Ｆへ
				mcDir(SOUTH);
				evScene(3,40,37);
			} else if(event <= 10){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("TuriaEternal.msg",event,mes_scene);

				npReturn(event);
			} else if(event == 205){
				//---タンス／本棚
				itemTansu(873,220);
			} else if(event == 206){//2,12  4,29  3,201
				//---地下通路へ
				evMap(63,3,2,12);
			}
		} else if(scene == 3){
			//---２Ｆ
			if(event == 200){
				//---１Ｆへ
				mcDir(SOUTH);
				evScene(2,51,4);
			} else if(event == 201){
				//---１Ｆへ
				mcDir(SOUTH);
				evScene(2,36,36);
			} else if(event == 202 || event == 203){
				//---外へ
				mcDir(SOUTH);
				evMap(61,0,7,61);
			} else if(event <= 10){
				int mes_scene = 1;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("TuriaEternal.msg",event + 20,mes_scene);

				npReturn(event);
			} else if(event == 204){
				//---タンス／本棚
				itemTansu(874,224);
			}
		}
	} else if(map == 65){
		//---豆腐職人
		if(scene == 0){
			if(200 <= event && event <= 202){
				mcDir(SOUTH);
				evMap(10,0,325,159);
			} else if(event == 203){
				//---タンス／本棚
				itemTansu(871,254);
			} else if(event == 0){
				int mes_scene = 1;
				int tofu = 0;

				npTurn(event);
				evField(0,1);
				if(!evGet(144)){
					//---最初
					mes.FileMessage("Tofu.msg",event,1);
					evSet(144,1);
				}

				tofu = critemGetItemCount(241) + critemGetItemCount(242) + critemGetItemCount(243);

				if(evGet(145) == 0){
					//---豆腐概論を持ってたら
					if(tofu){
						mes.FileMessage("Tofu.msg",event,2);
						if(tofu <= 2){
							//---足りない
							mes.FileMessage("Tofu.msg",event,3);
						} else {
							//---そろった
						}
					} else {
						//---なにも持ってない
						mes.FileMessage("Tofu.msg",event,1);
					}
				} else if(evGet(145) == 1){
					//---一冊渡してる
					if(tofu){
						mes.FileMessage("Tofu.msg",event,4);
						if(tofu <= 1){
							//---足りない
							mes.FileMessage("Tofu.msg",event,5);
						} else {
							//---そろった
						}
					} else {
						//---なにも持ってない
						mes.FileMessage("Tofu.msg",event,6);
					}
				} else if(evGet(145) == 2){
					//---２冊渡してる
					if(tofu){
						mes.FileMessage("Tofu.msg",event,4);
					} else {
						mes.FileMessage("Tofu.msg",event,6);
					}
				}

				//---ほんの数を減らす
				if(critemGetItemCount(241)){
					critemAddItem(241,-99);
					evSet(145,evGet(145) + 1);
				}
				if(critemGetItemCount(242)){
					critemAddItem(242,-99);
					evSet(145,evGet(145) + 1);
				}
				if(critemGetItemCount(243)){
					critemAddItem(243,-99);
					evSet(145,evGet(145) + 1);
				}

				if(evGet(145) == 3){
					//---揃った！！
					mes.OpenMessage("Tofu.msg",event);
					mes.SeekScene(20);

					mes.ReadDraw();

					evFrameWait(250);
					npDir(1,WEST);
					evFrameWait(250);
					mes.ReadDraw(4);

					evFrameWait(250);
					npDir(0,NORTH);
					evFrameWait(1000);
					mes.ReadDraw(3);
					evFrameWait(250);
					npTurn(0);
					evFrameWait(250);
					mes.ReadDraw();
					mes.CloseMessage();

					if(critemGetItemCount(236)){
						//---アルシアの天然水持ってる
					} else {
						mes.FileMessage("Tofu.msg",event,21);
					}
					evSet(145,5);
				}

				if(evGet(145) == 5){
					//---天然水待ち
					if(critemGetItemCount(236)){
						npDir(1,WEST);
						evField(0,1);

						critemAddItem(236,-1);
						mes.OpenMessage("Tofu.msg",0);
						mes.SeekScene(25);
						mes.ReadDraw(5);

						evFrameWait(250);
						npPos(0,7,4);
						npDir(0,NORTH);
						npPos(1,8,4);
						npDir(1,NORTH);
						mcDir(SOUTH);
						evScene(0,7,5);

						evFrameWait(500);
						mes.ReadDraw(1);
						evFrameWait(250);
						mcDir(EAST);
						evFrameWait(250);
						mcDir(NORTH);
						evFrameWait(250);
						mes.ReadDraw();

						evFrameWait(250);
						npDir(1,WEST);
						evFrameWait(250);
						npDir(0,EAST);
						evFrameWait(250);
						npDir(0,SOUTH);
						evFrameWait(250);

						mes.ReadDraw(18);
						evFrameWait(250);

						evReloadMap(0);
						npTurn(event);

						mcDir(SOUTH);
						evScene(0,7,8);
						evSet(145,6);

						mes.CloseMessage();
						return 1;
					} else {
						mes.FileMessage("Tofu.msg",event,22);
					}
				} else if(evGet(145) == 6){
					//---豆腐待ち
					mes.FileMessage("Tofu.msg",event,30);
					evField(0,1);
					evField(0,1);
					if(crbaseSelectYesNo("豆腐をもらいますか？",64,64) == 0){
						evField(0,1);
						evField(0,1);
						mes.FileMessage("Tofu.msg",event,32);
						evSet(145,7);
						//---豆腐を手に入れた時間
						evSet(146,pGameInfo->PlayAllSecond);
						critemAddItem(244,1);
					} else {
						evField(0,1);
						evField(0,1);
						mes.FileMessage("Tofu.msg",event,31);
					}
				} else if(evGet(145) == 7){
					mes.FileMessage("Tofu.msg",event,35);
					//---豆腐をもらった後
					if(critemGetItemCount(78) > 0 && !evGet(248)
						&& critemGetItemCount(244) == 0
						&& AFTER_KOJINSAI()){
						//---エストランテ
						//---伝説の豆腐を持ってない
						mes.OpenMessage("Tofu.msg",100,0);
						mes.ReadDraw(10);
						evFrameWait(250);

						npPos(0,7,4);
						npDir(0,NORTH);
						npPos(1,8,4);
						npDir(1,NORTH);
						mcDir(NORTH);
						evScene(0,7,5);

						evFrameWait(500);
						mes.ReadDraw(4);
						evFrameWait(500);
						npDir(0,EAST);
						evFrameWait(250);
						npDir(0,SOUTH);
						evFrameWait(500);
						mes.ReadDraw(9);
						evFrameWait(250);
						mes.CloseMessage();

						evReloadMap(0);
						npTurn(event);

						mcDir(SOUTH);
						evScene(0,7,8);

						critemAddItem(78,-1);
						critemAddItem(29,1);
						evSet(248,1);
					}
				}

				npReturn(event);

			} else if(event == 1){
				int mes_scene = 1;

				if(evGet(145) >= 6)
					mes_scene = 2;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("Tofu.msg",event,mes_scene);
				npReturn(event);
			}
		}
	}
	return 1;
}

//347-168,180

CREVENTPART6_API int creventCheckEvent_Part6_2(int event,int map,int scene)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;
	eiMapObject *pob = crfieldGetObjectPointer(event);

	if(map == 66){
		//---忘れ人の家
		if(scene == 0){
			if(200 <= event && event <= 201){
				mcDir(SOUTH);
				evMap(10,0,168,180);
			} else if(event <= 2){
				int mes_scene = 1;

				npTurn(event);
				evField(0,1);

				if(evGet(148)){
					//---忘れ物届けた後
					mes_scene = 3;
					mes.FileMessage("Wasure.msg",event,mes_scene);
				} else {
					if(critemGetItemCount(212) && event == 1){
						//---忘れ物お届け！
						mes.FileMessage("Wasure.msg",event,2);
						critemAddItem(212,-1);
						critemAddItem(211,1);
						evSet(148,1);
						evFrameWait(250);
						mcDir(SOUTH);
						evMap(10,0,168,180);
					} else {
						mes.FileMessage("Wasure.msg",event,mes_scene);
					}
				}
				npReturn(event);
			}
		}
	} else if(map == 67){
		//---ジーダイ港
		if(scene == 0){
			if(200 <= event && event <= 202){
				mcDir(SOUTH);
				evMap(10,0,355,223);
			} else if(event == 9){
				evYado(360,map,scene);
			} else if(event == 8){
				//---道具
				int ShopItem[] = {221,222,226,227,16,43,55,97,106,113,152,261,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 11){
				//---世界地図
				evShowWorldMap(355,223);
			} else if(event == 205){
				//---タンス／本棚
				itemTansu(875,224);
			} else if(event == 203 || event == 204){
				//---入れない
				npTurn(1);
				evField(0,1);

				mes.FileMessage("TuriaPort.msg",20,1);

				mcMove(1,0);
				npReturn(1);
				evFrame();
				mcResetEvent();
			} else if(event <= 10){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("Giedie.msg",event,mes_scene);
				npReturn(event);
			}
		}
	} else if(map == 68){
		//---ジーダイ南洞窟
		if(scene == 0){
			//---１Ｆ−１
			if(200 == event){
				mcDir(SOUTH);
				evMap(10,0,361,216);
			} else if(201 == event){
				mcDir(SOUTH);
				evScene(1,15,54);
			}
		} else if(scene == 1){
			//---２Ｆ
			if(200 == event){
				mcDir(SOUTH);
				evScene(0,14,3);
			} else if(201 == event){
				mcDir(SOUTH);
				evScene(2,14,46);
			} else if(event == 0){
				//---宝箱
				itemBox(564,222,event);
			} else if(event == 1){
				//---宝箱
				itemBox(565,223,event);
			}
		} else if(scene == 2){
			//---１Ｆ−２
			if(200 == event){
				mcDir(SOUTH);
				evScene(1,3,10);
			} else if(201 == event){
				mcDir(SOUTH);
				evMap(10,0,361,212);
			} else if(3 == event && !evGet(158)){
				//---エターナルが通行止め
				return creventGiedie_Lizel();
			}
		}
	} else if(map == 69){
		//---記憶の遺跡外部
		if(scene == 0){
			//---１Ｆ−１
			if(200 <= event && event <= 202){
				//---フィールドへ
				mcDir(SOUTH);
				evMap(10,0,365,179);
			} else if(203 <= event && event <= 204){
				//---フィールドへ
				mcDir(SOUTH);
				evMap(10,0,365,179);
			} else if(207 == event){
				//---内部へ
				mcDir(NORTH);
				evMap(70,0,4,20);
			} else if(205 <= event && event <= 206
				&& !evGet(159)){
				//---決戦エターナル！！
				return creventKiokunoIseki_Kessen();
			}
		}
	} else if(map == 70){
		//---記憶の遺跡
		if(scene == 0){
			//---１Ｆ
			if(event == 200){
				//---外へ
				if(!evGet(160)){
					evField(0,1);
					mes.FileMessage("KiokunoIseki.msg",105);
					mcMove(1,0);
					evFrame();
				} else {
					mcDir(SOUTH);
					evMap(69,0,16,24);
				}
			} else if(event == 201){
				//---Ｂ１へ
				mcDir(SOUTH);
				evScene(1,20,20);
			} else if(event == 6){
				prtRecoveryAll();
				evField(0,1);
				mes.FileMessage("KiokunoIseki.msg",event);
			} else if(event <= 5){
				int mes_scene = 1;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("KiokunoIseki.msg",event,mes_scene);

				npReturn(event);
			}
		} else if(scene == 1){
			//---Ｂ１
			if(event == 200){
				//---１Ｆへ
				mcDir(SOUTH);
				evScene(0,9,3);
			} else if(event == 201){
				//---小部屋へ
				mcDir(SOUTH);
				evScene(2,6,4);
			} else if(event == 202){
				//---Ｂ２へ
				mcDir(SOUTH);
				evScene(3,43,2);
			} else if(event == 0){
				//---宝箱
				itemBox(566,224,event);
			}
		} else if(scene == 2){
			//---小部屋
			if(event == 200){
				//---Ｂ１へ
				mcDir(SOUTH);
				evScene(1,12,2);
			} else if(event == 0){
				//---宝箱
				itemBox(567,25,event);
			} else if(event == 1){
				//---宝箱
				itemBox(568,225,event);
			}
		} else if(scene == 3){
			//---Ｂ２
			if(event == 200){
				//---Ｂ１へ
				mcDir(SOUTH);
				evScene(1,43,7);
			} else if(event == 201){
				//---Ｂ３へ
				mcDir(SOUTH);
				evScene(4,8,13);
			} else if(event == 0){
				//---宝箱
				itemBox(569,228,event);
			} else if(event == 1){
				//---宝箱
				itemBox(570,222,event);
			}
		} else if(scene == 4){
			//---Ｂ３
			if(event == 200){
				//---Ｂ２へ
				mcDir(SOUTH);
				evScene(3,2,27);
			} else if(event == 201){
				//---Ｂ４へ
				mcDir(SOUTH);
				evScene(5,6,34);
				if(evGet(161) <= 1){
					evSet(161,0);
				}
			} else if(202 <= event && event <= 207){
				//---滑る
				int x = 0,y = 0;
				switch(event){
				case 202:
				case 203:
				case 204:
					x = -1;
					break;
				case 205:
				case 206:
				case 207:
					y = -1;
					break;
				}
				mcMove(x,y,0);
				evFrame();
				mcResetEvent();
			} else if(event == 0){

				evField(0,1);
				mes.FileMessage("KiokunoIseki.msg",10);
			} else if(event == 1){
				//---宝箱
				itemBox(571,157,event);
			}
		} else if(scene == 5){
			//---Ｂ４
			if(event == 200){
				//---Ｂ３へ
				mcDir(SOUTH);
				evScene(4,37,10);
			} else if(event == 201){
				//---Ｂ５へ
				mcDir(SOUTH);
				evScene(6,18,14);
			} else if(202 <= event && event <= 204
				&& evGet(161) <= 1){
				//---無限ループ
				evSet(161,1);
				crfieldChangePos(-1,21);
			} else if(event == 0){
				evField(0,1);
				if(evGet(161) == 0){
					mes.FileMessage("KiokunoIseki.msg",11,1);
				} else {
					//---希望の道
					mes.FileMessage("KiokunoIseki.msg",11,2);
					evSet(161,2);
				}
			}
		} else if(scene == 6){
			//---Ｂ５
			if(event == 200){
				//---Ｂ４へ
				mcDir(SOUTH);
				evScene(5,6,3);
			} else if(event == 201){
				//---Ｂ６へ
				if(!evGet(162)){
					//---対称装置
					return creventKiokunoIseki_Taisho();
				} else {
					mcDir(SOUTH);
					evScene(7,12,21);
				}
			}
		} else if(scene == 7){
			//---Ｂ６
			if(event == 200){
				//---Ｂ２へ
				mcDir(SOUTH);
				evScene(6,18,18);
			} else if(event == 0){
				evField(0,1);
				mes.FileMessage("KiokunoIseki.msg",12);
			}
		} else if(scene == 8){
			//---Ｂ７
			if(event == 200){
				if(!evGet(160) && evGet(166)){
					//---脱出！
					return creventKiokunoIseki_Dasshutu();
				} else {
					evField(0,1);
					mes.FileMessage("KiokunoIseki.msg",108);
				}
			} else if(event == 201){
				mcDir(SOUTH);
				evScene(9,13,26);
			}
		} else if(scene == 9){
			//---Ｂ８
			if(event == 200){
				mcDir(SOUTH);
				evScene(8,48,2);
			} else if((201 <= event && event <= 203)&& !evGet(160)
				&& evGet(166)){
				//---そんな暇無し
				evField(0,1);
				mes.FileMessage("KiokunoIseki.msg",110);
				mcMove(0,-1);
				evFrame();
				mcResetEvent();
			} else if((201 <= event && event <= 203)&& !evGet(160)
				&& !evGet(166)){
				//---最深部へ・・・
				return creventKiokunoIseki_OnlyLunarn();
			}
		} else if(scene == 10){
			//---最深部
			if(event == 200 && !evGet(160)){
				//---ルナンの記憶
				return creventKiokunoIseki_MemoryOve();
			}
		}
	}

	return 1;
}
