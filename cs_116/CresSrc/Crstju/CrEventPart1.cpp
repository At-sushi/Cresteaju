/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrEventPart1.cpp ...Event functions

-----------------------------------------------------------*/


#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CREVENTPART1

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

#include "CrEventPart1_Sub1.cpp"

CREVENTLONG9_API int crevent_WescaLuxthereFirstSleep(void);
CREVENTLONG9_API int crevent_WescaLuxthereSleep(void);
CREVENTLONG9_API int crevent_WescaLuxthereVS(void);


static eiCell WorldMapCell,WorldMapCell2;

void MapCallBack(eiCell *pCell)
{
	WorldMapCell2.PutClip(ew->lpCell[1],320 - 100,64);
	WorldMapCell.PutTransClip(ew->lpCell[1],320 - 100,64);
}

CREVENTPART1_API int creventCheckEvent_Part1(int event,int map,int scene)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;
	eiMapObject *pob = crfieldGetObjectPointer(event);

	CR_BATTLEINFO BatInfo;
	memset(&BatInfo,0,sizeof(BatInfo));

	if(map == 10){
	} else if(map == 11){
	//---オープニング
		if(scene == 0){
			evField(0,1);
			if((event == 201 || event == 202) && !evGet(1)){
				//---ここは・・・？
				evSet(1,1);
				evReset();
				mcDir(NORTH);
				evFrameWait(1200);
				mcDir(EAST);
				evFrameWait(1200);
				mcDir(SOUTH);
				evFrameWait(1200);
				mcDir(WEST);
				evFrameWait(1200);

				mes.FileMessage("Opening.msg",0);
			}
			if((event == 203) && !evGet(2)){
				evSet(2,1);
				evReset();
				mcDir(WEST);
				evFrameWait(1200);
				mcDir(NORTH);
				evFrameWait(1200);
				mcDir(EAST);
				evFrameWait(1200);
				mcDir(SOUTH);
				evFrameWait(1200);

				mes.FileMessage("Opening.msg",1);
			}
			if((event == 200)){
				//---オープニング
				creventOpening();
			}
		}
	} if(map == 13){
		//---ウェスカ西船着き場
		if(scene == 0){
			if(event == 200 || event == 201){
				//---フィールドへ
				crfieldChangeMapS(10,0);
				crfieldChangeSceneS(0,174,151);
			} else if(event == 202){
				//---おっと、こっからさきはダメですぜ
				mes.FileMessage("EastWesca.msg",0,1);

				mcMove(1,0);
				evFrame();
				mcResetEvent();
			} else if((0 <= event && event <= 6) || event == 10){
				//---人々
				int mes_scene = 1;

				npTurn(event);
				if(event == 10){
					npTurn(4);
				}
				evField(0,1);

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				mes.FileMessage("EastWesca.msg",event,mes_scene);
				npReturn(event);
				if(event == 10){
					npReturn(4);
				}
			} else if(event == 203){// && !evGet(3)){
				//---本棚
				itemTansu(800,221);
			}
		}
	} else if(map == 14){
		//---ウェスカ
		if(scene == 0){
			if(evGet(9) == 1 && evGet(15) == 0 && (event == 204 || event == 205)){
				mcShow(0);
				npPos(35,37,34);
				npDir(35,WEST);
				npPos(36,38,34);
				npDir(36,WEST);
				evScene(0,35,38);

				crmusicPlay(CRMUSIC_SS);

				for(a = 0;a < 2;a ++){
					npMove(35,-1,0);
					evFrame();
				}
				npDir(35,SOUTH);
				evFrameWait(500);

				//---あ！
				mes.OpenMessage("Wesca.msg",103);
				mes.ReadDraw();
				//---ん？
				evFrameWait(500);
				npDir(33,NORTH);
				evFrameWait(500);
				mes.ReadDraw(2);

				evFrameWait(500);
				npDir(34,NORTH);
				evFrameWait(1000);

				mes.ReadDraw();

				npMove(35,0,1);
				evFrame();

				mes.ReadDraw(2);

				for(a = 0;a < 3;a ++){
					if(a < 2)
						npMove(36,-1,0);
					else
						npMove(36,0,1);
					evFrame();
				}
				npDir(36,WEST);
				evFrameWait(500);
				//---こいつか？
				mes.ReadDraw();

				//---そうでげす
				evFrameWait(500);
				npDir(35,EAST);
				evFrameWait(500);
				mes.ReadDraw();

				evFrameWait(350);
				npDir(35,SOUTH);
				evFrameWait(300);
				npDir(36,SOUTH);
				evFrameWait(400);
				mes.ReadDraw();

				evFrameWait(1000);
				mes.ReadDraw();
				evFrameWait(500);
				npDir(36,WEST);
				evFrameWait(500);
				//---おじょうさま
				mes.ReadDraw(3);

				evFrameWait(500);
				npDir(36,SOUTH);
				evFrameWait(200);
				npMove(36,0,1);
				evFrame();
				mes.ReadDraw(3);
				//---表に出な
				evFrameWait(500);
				npDir(36,EAST);
				evFrameWait(300);
				npDir(36,NORTH);
				evFrameWait(300);
				for(a = 0;a < 1;a ++){
					npMove(36,0,-1);
					evFrame();
				}

				mes.ReadDraw(2);

				evFrameWait(500);
				npDir(36,EAST);
				evFrameWait(300);
				npDir(36,SOUTH);
				evFrameWait(300);
				mes.ReadDraw();

				evFrameWait(200);
				npDir(34,WEST);
				evFrameWait(300);
				npDir(33,EAST);
				evFrameWait(300);

				mes.ReadDraw(2);

				//---がたがたいうな！
				npMove(36,0,1);
				evFrame();
				mes.ReadDraw();
				evFrameWait(200);

				for(a = 0;a < 3;a ++){
					if(a < 1)
						npMove(33,0,-1);
					else
						npMove(33,1,0);
					evFrame();
				}
				npDir(33,NORTH);
				evFrameWait(250);
				npDir(34,NORTH);
				evFrameWait(250);
				mes.ReadDraw();

				npDir(36,WEST);
				evFrameWait(250);
				npDir(36,NORTH);
				evFrameWait(250);
				npMove(36,0,-1);
				evFrame();
				npDir(36,WEST);
				evFrameWait(250);
				mes.ReadDraw(3);

				evFrameWait(250);
				npDir(36,SOUTH);
				evFrameWait(250);
				//---よこしな
				mes.ReadDraw();

				evFrameWait(250);
				npDir(33,EAST);
				evFrameWait(250);
				npDir(33,SOUTH);
				evFrameWait(250);
				mes.ReadDraw();

				evFrameWait(250);
				npDir(33,EAST);
				evFrameWait(250);
				npDir(33,NORTH);
				evFrameWait(250);
				for(a = 0;a < 1;a ++){
					npMove(33,0,-1);
					evFrame();
				}
				evFrameWait(1000);
				for(a = 0;a < 1;a ++){
					npMove(33,0,1,0);
					evFrame();
				}
				evFrameWait(1000);
				mes.ReadDraw(4);
				evFrameWait(250);

				for(a = 0;a < 15;a ++){
					if(a < 1)
						npMove(33,1,0);
					else if(a < 3)
						npMove(33,0,-1);
					else
						npMove(33,1,0);

					if(a < 1)
						npMove(34,0,-1);
					else if(a < 2)
						npMove(34,1,0);
					else if(a < 4)
						npMove(34,0,-1);
					else
						npMove(34,1,0);


					if(a == 3)
						npDir(36,EAST);
					if(a == 1)
						npDir(35,EAST);
					evFrame();
				}

				npDir(36,SOUTH);
				evFrameWait(250);
				npDir(36,WEST);
				evFrameWait(250);

				mes.ReadDraw(2);
				evFrameWait(250);

				npPos(35,44,51);
				npDir(35,SOUTH);
				npPos(36,44,52);
				npDir(36,NORTH);
				evScene(0,44,52);
				crmusicPlay(CRMUSIC_TOWN1);
				evFrameWait(1000);
				mes.ReadDraw(9);

				evFrameWait(500);
				npDir(36,WEST);
				evFrameWait(500);
				npDir(36,SOUTH);
				evFrameWait(500);
				for(a = 0;a < 12;a ++){
					npMove(36,0,1);
					evFrame();
				}
				mcMove(0,-1);
				evFrame();
				for(a = 33;a <= 36;a ++){
					npPos(a,0,0);
					npShow(a,0);
				}
				mcDir(SOUTH);
				mcShow(1);

				mes.CloseMessage();
				//---ディザわかれる
				pPartyInfo->PartyMember[1] = -1;

				evSet(15,1);
			} else if(evGet(4) == 0 && (event == 204 || event == 205)){
				//---酒場＆シューティングスター
				for(a = 0;a < 4;a ++){
					mcMove(-1,0);
					if(a == 3)
						npDir(33,NORTH);
					evFrame(1,0x01);
				}
				evField(0,1);
				//---よぉ
				mes.OpenMessage("Wesca.msg",101);
				mes.ReadDraw();
				evFrameWait(700,1);
				//---無視してカウンターへ
				for(a = 0;a < (event == 204 ? 2 : 3);a ++){
					mcMove(0,-1);
					evFrame(1,0x01);
				}
				mcMove(-1,0);
				evFrame(1,0x01);
				npDir(33,EAST);
				evFrameWait(500,1);
				//---マスター来る
				for(a = 0;a < 3;a ++){
					if(a < 2)
						npMove(3,0,1);
					else
						npDir(3,EAST);
					evFrame();
				}
				evFrameWait(500,1);
				mes.ReadDraw(5);
				for(a = 0;a < 4;a ++){
					if(a < 1)
						npDir(3,NORTH);
					else if(a < 2)
						npMove(3,-1,0);
					else if(a < 3)
						npMove(3,0,-1);
					else
						npDir(3,WEST);
					evFrame();
				}
				evFrameWait(500,1);
				mes.ReadDraw(2);
				evFrameWait(1000,1);
				for(a = 0;a < 4;a ++){
					if(a < 1)
						npDir(3,SOUTH);
					else if(a < 2)
						npMove(3,1,0);
					else if(a < 3)
						npMove(3,0,1);
					else
						npDir(3,EAST);
					evFrame();
				}

				evFrameWait(500,1);
				//---トマトジュース！
				em->Put(31,32,2,59);
				evFrameWait(1000,1);
				mes.ReadDraw(7);
				npPos(14,31,32);
				mes.CloseMessage();

				evSet(4,1);
			} else if(evGet(4) == 1 && (event == 204 || event == 205)){
				mes.OpenMessage("Wesca.msg",102);
				for(a = 0;a < 7;a ++){
					mcMove(1,0);
					evFrame(1,0x01);
				}
				for(a = 0;a < 9 + (event == 205 ? 1 : 0);a ++){
					mcMove(0,-1);
					evFrame(1,0x01);
				}

				//---ウェイトプリーズ
				evField(0,1);
				mes.ReadDraw();

				evFrameWait(500,1);
				mcMove(0,-1);
				evFrame(1,0x01);
				evFrameWait(500,1);

				mes.ReadDraw();
				evFrameWait(500,1);

				mcDir(EAST);
				evFrameWait(500,1);
				mcDir(SOUTH);
				evFrameWait(500,1);

				crmusicPlay(CRMUSIC_SS);
				npPos(33,44,35);
				for(a = 0;a < 8;a ++){
					npMove(33,0,-1);
					evFrame();
				}
				mcShow(0);
				npPos(35,44,24);
				npDir(35,SOUTH);
				for(a = 0;a < 4;a ++){
					mcMove(0,1);
					evFrame(1,0x01);
				}

				npPos(34,44 + b,21);
				mes.ReadDraw(5);
				evFrameWait(500,1);
				mes.ReadDraw();
				for(a = 0;a < 1;a ++){
					npMove(34,0,1);
					evFrame();
				}
				evFrameWait(500,1);
				for(a = 0;a < 1;a ++){
					npMove(34,0,1);
					evFrame();
				}
				evFrameWait(500,1);
				//---ガツンといってやれガツンと
				evFill(ep->MakeRGB(255,255,255));
				crsoundPlay(CRSOUND_ATACK1);
				ew->Flip();
				evFrameWait(500,1);
				mes.ReadDraw();
				evFrameWait(100);
				evFadeOut(1000);
				et->Delay2(1000);
				evReadObject(14,"LunarnSlp2.acf");
				npPos(35,22,18);//22,13
				npDir(35,SOUTH);
				npPos(6,19,20);//19,15  
				npDir(6,SOUTH);
				evScene(0,20,22);//20,17
				crmusicPlay(CRMUSIC_TOWN1);

				evFrameWait(2000,1);
				npDir(35,WEST);
				evFrameWait(1000,1);

				mes.ReadDraw();
				evFrameWait(750,1);
				npDir(6,EAST);
				evFrameWait(750,1);
				mes.ReadDraw();
				evFrameWait(750,1);
				mes.ReadDraw();
				//---ルナンきょろきょろ
				evFrameWait(250);
				npDir(35,EAST);
				evFrameWait(500,1);
				npDir(35,WEST);
				evFrameWait(250,1);
				npDir(35,NORTH);
				evFrameWait(500,1);
				mes.ReadDraw(3);
				//---そんな！！
				evFrameWait(250,1);
				npDir(35,WEST);
				evFrameWait(500,1);
				npDir(35,SOUTH);
				evFrameWait(500,1);
				npDir(35,WEST);
				evFrameWait(250,1);
				mes.ReadDraw();
				evFrameWait(250);
				//---おばさんくる
				for(a = 0;a < 4;a ++){
					if(a < 2)
						npMove(6,0,-1);
					else
						npMove(6,1,0);
					evFrame();
				}
				mes.ReadDraw();
				evFrameWait(250);
				//---でも・・・
				npDir(35,NORTH);
				evFrameWait(500,1);
				mes.ReadDraw(4);
				evFrameWait(500);

				evFadeOut(500);
				prtRecoveryAll();
				npPos(6,19,20);//19,15
				npDir(6,EAST);
				npShow(35,0);
				mcShow(1);
				mcDir(WEST);
				evScene(0,20,20);//20,15

				evFrameWait(1000,1);
				mes.ReadDraw(9);
				evFrameWait(250);

				mes.CloseMessage();

				for(a = 33;a <= 35;a ++){
					npPos(a,0,0);
					npShow(a,0);
				}
				evSet(4,2);
			} else if(200 <= event && event <= 202){
				//---フィールドへ
				evMap(10,0,160,153);
			} else if(203 == event){
				//---宿屋２階へ//28,57  2,17
				evScene(1,2,17);
			} else if(event == 11){
				//---宿屋
				if(AFTER_KOJINSAI() && evGet(231) && evGet(232) == 0 && evGet(233) == 0){
					//---ウェスカの亡霊、おばさんの言葉
					return crevent_WescaLuxthereFirstSleep();
				} else if(AFTER_KOJINSAI() && evGet(231) && evGet(232) >= 1 && evGet(233) == 0){
					//---ウェスカの亡霊、２回目以降
					return crevent_WescaLuxthereSleep();
				} else {
					evYado(5);
				}
			} else if(event == 12){
				//---道具や
				int ShopItem[] = {221,226,227,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 13){
				//---武器や
				int ShopItem[] = {10,100,140,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 37){
				//---地図
				evShowWorldMap(160,153);
			} else if(event == 14 || (0 <= event && event <= 10) || (18 <= event && event < 200)){
				//---人々
				int mes_scene = 1;

				npTurn(event);
//				if(event == 10){
//					npTurn(4);
//				}
				evField(0,1);
				if(evGet(15) == 1){
					mes_scene = 3;
				} else if(evGet(4) == 2){
					mes_scene = 2;
				}

				if(event == 6 && evGet(15) == 1
					&& evGet(16) == 0 && evGet(21) == 0){
					mes.FileMessage("Wesca.msg",event,50);
					critemAddItem(196,1);
					evSet(21,1);
				}

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;
				mes.FileMessage("Wesca.msg",event,mes_scene);

				if(event == 24){
					//---魔法について
					int ret;
					CRWIN_SELECTINFO info;
					CrSelectWindow win;
					memset(&info,0,sizeof(info));
					do {
						crbaseMenuReset();
						win.Create(64,64,18,11,"何を教えてもらいますか？",
							"魔法の覚え方、その１;魔法の覚え方、その２;魔法の覚え方、その３;"
							"ＭＣについて;攻撃魔法;補助魔法;もういい;");
						win.Refresh();
						crbaseMenuStart();
						ret = win.Select(&info);
						if(ret == -1)
							ret = 6;
						evField(0,1);
						mes.FileMessage("Wesca.msg",event,102 + ret);
						if(ret != 6){
							mes.FileMessage("Wesca.msg",event,109);
						}
					} while(ret != 6);
				} else if(event == 5){
					//---地理
					if(crbaseSelectYesNo("教えてもらいますか？") == 0){
						WorldMapCell.ReadFile(CR_DATADIR1"WorldMap.acf",CR_DATAFILE1,
							crdataGetFileMode());
						evField(0,1);

						mes.OpenMessage("Wesca.msg",event);
						mes.lpWin[0]->SetPaintCallBack(MapCallBack);
						mes.SeekScene(102);

						mes.ReadMessage(1);
						mes.Draw();

						{
							RECT rect = {0,0,200,200};

							WorldMapCell2.ReadFile(CR_DATADIR1"WorldMap.acf",CR_DATAFILE1,
								crdataGetFileMode());
							WorldMapCell2.SetSurface(&rect,3);
						}

						RECT rect = {200,0,400,200};
						WorldMapCell.ReadFile(CR_DATADIR1"WorldMap_1.acf",CR_DATAFILE1,
							crdataGetFileMode());
						WorldMapCell.SetSurface(&rect,3);
						mes.ReadMessage(1);
						mes.Draw();

						WorldMapCell.ReadFile(CR_DATADIR1"WorldMap_2.acf",CR_DATAFILE1,
							crdataGetFileMode());
						WorldMapCell.SetSurface(&rect,3);
						mes.ReadMessage(1);
						mes.Draw();

						WorldMapCell.ReadFile(CR_DATADIR1"WorldMap_3.acf",CR_DATAFILE1,
							crdataGetFileMode());
						WorldMapCell.SetSurface(&rect,3);
						mes.ReadMessage(1);
						mes.Draw();

						WorldMapCell.ReadFile(CR_DATADIR1"WorldMap_4.acf",CR_DATAFILE1,
							crdataGetFileMode());
						WorldMapCell.SetSurface(&rect,3);
						mes.ReadMessage(1);
						mes.Draw();

						WorldMapCell.ReadFile(CR_DATADIR1"WorldMap_5.acf",CR_DATAFILE1,
							crdataGetFileMode());
						WorldMapCell.SetSurface(&rect,3);
						mes.ReadMessage(1);
						mes.Draw();

						//---わかったかな
						mes.ReadMessage(1);
						mes.Draw();

						mes.lpWin[0]->SetPaintCallBack(NULL);
						mes.CloseMessage();

						WorldMapCell.Release();
						WorldMapCell2.Release();

					} else {
						mes.FileMessage("Wesca.msg",event,101);
					}
				}
				npReturn(event);
//				if(event == 10){
//					npReturn(4);
//				}
			} else if(event == 257){
				//---タンス／本棚
				itemTansu(801,221);
			} else if(event == 258){
				//---タンス／本棚
				itemTansu(802,221);
			} else if(event == 259){
				//---タンス／本棚
				itemTansu(803,226);
			}
		} if(scene == 1){
			//---宿屋２階
			if(event == 202 && !evGet(233) && evGet(234) == 1 && evGet(235) && AFTER_KOJINSAI()){
				//---ルクスゼア！！
				return crevent_WescaLuxthereVS();
			} else if(event < 10){
				int mes_scene = 1;

				if(event <= 0)
					npTurn(event);
				if(event >= 5)
					event -= 3;
				evField(0,1);

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				if(event == 2){
					//---ディザに話した
					evSet(235,1);
				}

				mes.FileMessage("Wesca.msg",event + 50,mes_scene);
			} else if(200 == event){
				//---１階へ
				if(evGet(234) == 1){
					//---夜！
					evField(0,1);
					mes.FileMessage("Wesca.msg",116);
				} else {
					evScene(0,28,53);
				}
			} else if(event == 201){
				//---タンス／本棚
				itemTansu(804,223);
			}
		}
	}
	return 0;
}

CREVENTPART1_API int creventCheckEvent_Part1_2(int event,int map,int scene)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;
	eiMapObject *pob = crfieldGetObjectPointer(event);

	CR_BATTLEINFO BatInfo;
	memset(&BatInfo,0,sizeof(BatInfo));
	if(map == 16){
		//---セーネ
		if(scene == 0){
			if(200 <= event && event <= 202){
				if(evGet(17) == 1){
					//---宿屋に泊まろうかな
					evField(0,1);
					mes.FileMessage("Sene.msg",102);
					evFrameWait(250);
					mcMove(0,1);
					evFrame();
					mcResetEvent();
				} else {
					//---フィールドへ
					evMap(10,0,104,177);
				}
			} else if(event == 203){
				//---宿屋２階
				evScene(1,10,16);
			} else if(event == 204){
				//---町長２階
				evScene(2,13,2);
			} else if(event == 3){
				//---宿屋
				if(evGet(17) != 2){
					mes.FileMessage("Sene.msg",40,1);
					evSet(17,1);
					evYado(0,map,scene,callbackSene);
					//---キャンペーン中につきライフカプセル
					critemAddItem(221,1);
				} else {
					evYado(8,map,scene);
				}
			} else if(event == 4){
				//---酒場
				mes.FileMessage("Sene.msg",event,1);
			} else if(event == 5){
				//---道具屋
				int ShopItem[] = {10,49,100,140,195,174,221,226,227,-1};
				crshopIntoShop(ShopItem);
			} else if(222 == event){
				//---タンス
				itemTansu(805,221);
			} else if(223 == event){
				//---タンス
				itemTansu(806,195);
			} else if(2 <= event && event <= 100){
				//---人々
				int mes_scene = 1;

				if(event != 24)
					npTurn(event);
				evField(0,1);

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;
				else if(evGet(17) == 2)
					mes_scene = 3;

				if(evGet(17) == 0){
					mes.FileMessage("Sene.msg",event,2);
				} else {
					mes.FileMessage("Sene.msg",event,mes_scene);
				}
				if(event != 24)
					npReturn(event);

/*				if(evGet(17) == 0
					&& (event == 6 || event == 8 || event == 9
					|| event == 11 || event == 13 || event == 15)){
					evSet(17,1);
				}*/
			}
		} else if(scene == 1){
			//---宿屋２階
			if(200 == event){
				evScene(0,44,20);
			} else if(201 == event){
				//---タンス
				itemTansu(807,226);
			} else if(0 <= event){
				//---人々
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("Sene.msg",event + 50,mes_scene);
				npReturn(event);
			}
		} else if(scene == 2){
			//---町長２階
			if(200 == event){
				evScene(0,54,42);
			} else if(201 == event){
				//---タンス
				itemTansu(808,121);
			} else if(0 <= event){
				//---人々
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;
				else if(evGet(17) == 2)
					mes_scene = 2;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("Sene.msg",event + 60,mes_scene);
				npReturn(event);

				if(event == 0 && evGet(17) == 0){
					//---町長の誘拐話
					evSet(17,1);
				}
			}
		}
	} else if(map == 17){
		//---ウェスカ西の橋
		if(scene == 0){
			if(200 <= event && event <= 204){
				evMap(10,0,126,151);
			} else if(205 <= event && event <= 209){
				evMap(10,0,122,151);
				//---一度橋を渡るとクレイシブは出ない
				evSet(16,1);
			} else if(0 <= event){
				int mes_scene = 1;

				//---人々
				npTurn(event);
				evField(0,1);

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				if(event == 2 && evGet(16) == 0){
					//---クレイシヴと初対面
					mes.FileMessage("WescaWBrdg.msg",event,2);
					evSet(16,1);
				} else {
					mes.FileMessage("WescaWBrdg.msg",event,mes_scene);
				}
				npReturn(event);
			}
		} else if(scene == 1){
			if(200 <= event && event <= 211){
				if(evGet(9) == 1 && evGet(15) == 0){
					//---ディザの助言
					mes.FileMessage("WescaWBrdg.msg",100,1);
					evFrameWait(250);
				}
				evMap(10,0,126,151);
			} else if(0 <= event){
				//---人々
				npTurn(event);
				evField(0,1);
				mes.FileMessage("WescaWBrdg.msg",event + 50,1);
				npReturn(event);
			}
		}
	} else if(map == 18){
		//---ウェスカ北の森
		if(scene == 0){
			if(event == 0){
				//---宝箱
				itemBox(500,221,event);
			} else if(event == 1){
				//---宝箱
				itemBox(501,227,event);
			}
			if(event == 200){
				//---フィールドへ
				mcDir(SOUTH);
				evMap(10,0,151,143);
			} else if(event == 206){
				//---森３へ
				mcDir(SOUTH);
				evScene(2,61,12);
			} else if(event == 201 && evGet(4) == 2 && evGet(7) == 0){
				//---隠し通路
				evField(0,1);
				mes.FileMessage("WescaNForest.msg",101,1);
				for(a = 0;a < 10;a ++){
					if(a < 3)
						mcMove(-1,0);
					else if(a < 7)
						mcMove(0,1);
					else if(a < 10)
						mcMove(1,0);
					evFrame();
				}
				mcDir(NORTH);
				evFrameWait(250,1);
				mcDir(WEST);
				evFrameWait(250,1);
				npPos(2,54,21);
				for(a = 0;a < 9;a ++){
					npMove(2,-1,0);
					evFrame();
				}
				npDir(2,SOUTH);
				evFrameWait(1000,1);

				em->Put(45,22,1,0);
				em->Put(45,23,1,0);

				evFrameWait(1000,1);
				for(a = 0;a < 3;a ++){
					if(a < 2)
						npMove(2,0,1);
					else
						npMove(2,-1,0);
					evFrame();
				}
				npDir(2,NORTH);
				evFrameWait(250,1);
				npDir(2,EAST);
				evFrameWait(1000,1);

				em->Put(45,22,1,32);
				em->Put(45,23,1,33);
				evFrameWait(1000,1);
				npDir(2,SOUTH);
				evFrameWait(250,1);
				npDir(2,WEST);
				evFrameWait(250,1);

				for(a = 0;a < 20;a ++){
					if(a < 5)
						npMove(2,-1,0);
					else
						npMove(2,0,-1);
					evFrame();
				}
				npShow(2,0);
				mes.FileMessage("WescaNForest.msg",103,1);
				evSet(7,1);
			} else if(event == 202 && evGet(7) == 1 && evGet(8) == 0){
				//---隠し通路
				mes.FileMessage("WescaNForest.msg",102,1);
				evFrameWait(250,1);
				em->Put(45,22,1,0);
				em->Put(45,23,1,0);
				evSet(8,1);
			} else if(event == 205 && evGet(9) == 0){
				//---イベント準備
				npPos(2,34,49);
				npShow(2,1);
				npDir(2,EAST);
				npPos(3,36,49);
				npShow(3,1);
				npDir(3,WEST);
			} else if(event == 203 && evGet(10) == 0){
				mes.OpenMessage("WescaNForest.msg",104);
				mes.ReadDraw(2);
				mcDir(WEST);
				evFrameWait(500,1);
				mes.ReadDraw(3);
				mes.CloseMessage();
				evSet(10,1);
			} else if(event == 204 && evGet(10) == 1){
				//---エターナル発見！！
				creventWescaNForest1();
				evSet(10,2);
			}
		} else if(scene == 2){
			if(event == 200 && evGet(10) == 4){
				mcDir(EAST);
				evScene(0,19,53);
			} else if(event == 201){
				//---フィールドへ脱出　
				mcDir(SOUTH);
				evMap(10,0,151,143);
				evSet(10,4);
				evSet(9,1);
			} else if(event == 2){
				//---宝箱
				itemBox(502,223,event);
			} else if(event == 3){
				//---宝箱
				itemBox(503,221,event);
			} else if(event == 202 && evGet(10) == 2){
				//---野宿かね
				crfieldPaletteChange(PALETTE_SUNSET);
				mcShow(0);
				npPos(0,29,14);
				npDir(0,SOUTH);
				npPos(1,29,13);
				npDir(1,SOUTH);
				evScene(2,29,14);
				for(a = 0;a < 3;a ++){
					mcMove(0,1);
					evFrame();
				}

				evFrameWait(1000);
				npDir(0,WEST);
				evFrameWait(500);
				npDir(0,NORTH);
				evFrameWait(500);

				mes.OpenMessage("WescaNForest.msg",109);
				mes.ReadDraw(4);
				evFrameWait(250);

				npMove(0,0,1);
				evFrame();
				npDir(0,WEST);
				evFrameWait(300);
				npDir(0,SOUTH);
				evFrameWait(300);
				npDir(0,EAST);
				evFrameWait(500);
				npDir(0,SOUTH);
				evFrameWait(300);

				mes.ReadDraw();

				//---君の名は
				evFrameWait(500);
				npDir(0,WEST);
				evFrameWait(300);
				npDir(0,NORTH);
				evFrameWait(300);
				mes.ReadDraw();
				evFrameWait(250);

				for(a = 0;a < 9;a ++){
					if(a < 1)
						npMove(1,0,1);
					else if(a < 3)
						npMove(1,-1,0);
					else if(a < 6)
						npMove(1,0,1);
					else if(a < 8)
						npMove(1,1,0);
					else
						npDir(1,NORTH);

					if(a == 5)
						npDir(0,WEST);
					if(a == 7)
						npDir(0,SOUTH);

					evFrame();
				}
				evFrameWait(250);
				mes.ReadDraw(6);
				evFrameWait(250);
				npDir(1,WEST);
				evFrameWait(250);
				npMove(1,-1,0);
				evFrame();
				evFrameWait(750);

				//---だいじなん？
				mes.ReadDraw(2);
				evFrameWait(250);
				//---たわけっ
				npDir(1,NORTH);
				evFrameWait(250);
				for(a = 0;a < 2;a ++){
					npMove(1,0,-1);
					if(a == 1)
						npDir(0,WEST);
					evFrame();
				}
				npDir(1,EAST);
				evFrameWait(250);
				mes.ReadDraw(2);

				evFrameWait(500);
				npDir(1,SOUTH);
				evFrameWait(500);
				npMove(1,0,1);
				evFrameWait(500);
				npDir(0,SOUTH);
				evFrameWait(500);
				//---寝ましょう
				mes.ReadDraw();
				evFrameWait(500);

				em->ReloadPattern();
				prtRecoveryAll();
				npPos(1,30,15);
				npPos(0,28,16);
				npDir(0,EAST);
				npDir(1,SOUTH);

				evFadeOut(1000);
				evFieldNoFlip(0,1);
				evReset();
				evWait(1000);
				evFadeIn(1000);

				evFrameWait(1000);
				npDir(0,SOUTH);
				evFrameWait(500);
				mes.ReadDraw();

				npDir(1,WEST);
				evFrameWait(500);
				mes.ReadDraw();
				evFrameWait(1000);
				npDir(0,EAST);
				evFrameWait(1000);
				mes.ReadDraw();

				npDir(1,WEST);
				evFrameWait(500);
				for(a = 0;a < 2;a ++){
					npMove(1,-1,0);
					if(a == 1)
						npDir(0,EAST);
					evFrame();
				}
				evFrameWait(250);
				npDir(0,NORTH);
				evFrameWait(200);
				npDir(1,SOUTH);
				evFrameWait(200);
				mes.ReadDraw();

				evFrameWait(1000);
				mes.ReadDraw(3);
				evFrameWait(500);

				mes.CloseMessage();

				mcShow(1);
				npPos(0,0,0);
				npPos(1,0,0);
				npShow(0,0);
				npShow(1,0);
				evScene(2,29,17);

				evSet(10,3);
			}
		}
	} else if(map == 19){
		//---セーネ北西の森
		if(scene == 0){
			if(event == 200){
				mcDir(SOUTH);
				evMap(10,0,92,165);
			} else if(event == 202){
				//---森２へ
				mcDir(NORTH);
				evScene(1,12,31);
			} else if(0 <= event && event <= 2){
				//---人々
				npTurn(event);
				evField(0,1);
				mes.FileMessage("SeneNWForest.msg",event,0);
				npReturn(event);
			} else if(event == 3){
				itemBox(504,227,event);
			} else if(event == 4){
				//---宝箱
				itemBox(505,221,event);
			}
		} else if(scene == 1){
			if(event == 200){
				//---森１へ
				mcDir(SOUTH);
				evScene(0,39,10);
			} else if(event == 201){
				//---建物内部へ
				mcDir(NORTH);
				evScene(2,25,45);

				if(evGet(20) == 0){
					evFrameWait(1000,1);
					mes.FileMessage("SeneNWForest.msg",100);
					evSet(20,1);
				}
			}
		} else if(scene == 2){
			if(event == 200){
				//---森２へ
				mcDir(SOUTH);
				evScene(1,13,13);
			} else if(event <= 6){
				//---エターナル
				mes.FileMessage("SeneNWForest.msg",50 + evGet(18),0);
				if(evGet(18) < 4)
					evSet(18,evGet(18) + 1);
			} else if(7 <= event && event <= 15){
				//---本
				mes.FileMessage("SeneNWForest.msg",60 + event - 7,0);
			} else if((event == 201 || event == 202) && evGet(19) == 0){
				//---ルナン＆ディザ
				if(event == 202){
					mcMove(0,-1);
					evFrame();
				}
				mcShow(0);
				npPos(16,17,18);
				npShow(16,1);
				npDir(16,WEST);

				evFrameWait(1000,1);
				npMove(16,-1,0);
				evFrame();
				for(a = 0;a < 8;a ++){
					mcMove(-1,0);
					evFrame();
				}
				evFrameWait(1000,1);

				mes.OpenMessage("SeneNWForest.msg",101);
				mes.ReadDraw();
				evFrameWait(250);

				for(a = 0;a < 10;a ++){
					if(a < 3)
						npMove(16,0,-1);
					else if(a < 10)
						npMove(16,-1,0);
					evFrame();
				}
				evFrameWait(2000,1);
				//---ふりーず！！
				mes.ReadDraw();

				evFrameWait(250,1);
				npDir(16,SOUTH);
				evFrameWait(250,1);
				npDir(16,EAST);
				
				npPos(17,18,18);
				npShow(17,1);
				npDir(17,WEST);

				for(a = 0;a < 2;a ++){
					mcMove(1,0);
					evFrame();
				}
				evFrameWait(250);
				mes.ReadDraw();
				evFrameWait(500,1);
				for(a = 0;a < 1;a ++){
					npMove(17,-1,0);
					evFrame();
				}
				evFrameWait(500,1);
				mes.ReadDraw();

				evFrameWait(1000,1);
				mes.ReadDraw();
				evFrameWait(250);
				for(a = 0;a < 8;a ++){
					if(a < 3)
						npMove(17,0,-1);
					else
						npMove(17,-1,0);
					evFrame();
				}
				evFrameWait(250);
				mes.ReadDraw(3);

				evFrameWait(1000,1);
				npDir(16,SOUTH);
				evFrameWait(350,1);
				npDir(16,WEST);
				evFrameWait(2000,1);
				npDir(16,SOUTH);
				evFrameWait(350,1);
				npDir(16,EAST);
				evFrameWait(500,1);

				mes.ReadDraw(5);

				evFrameWait(1000,1);
				npDir(17,SOUTH);
				evFrameWait(500,1);
				npDir(17,EAST);
				evFrameWait(1000,1);
				//---かたきうちでおじゃる
				mes.ReadDraw();
				evFrameWait(500,1);
				mes.ReadDraw();

				evFrameWait(500,1);
				npDir(17,SOUTH);
				evFrameWait(250,1);
				npDir(17,WEST);
				evFrameWait(500,1);

				mes.ReadDraw(5);
				evFrameWait(250);

				mes.CloseMessage();
				//---ディザ再び！
				pPartyInfo->PartyMember[1] = 1;
				CrCharacter *pChara = crcharaGetPartyMember(1);
				if(pChara->GetLevel() < crcharaGetPartyMember(0)->GetLevel()){
					crcharaSetLevelStatus(1,crcharaGetPartyMember(0)->GetLevel());
					pChara->SetExperience(crcharaGetPartyMember(0)->GetExperience() - 2);
				} else {
					if(pChara->GetLevel() < 3){
						//---３より下だったら３に設定
						crcharaSetLevelStatus(1,3);
						pChara->SetLevelExperience();
					}
				}

				pChara->SetBattleFieldStartPos(4,4);
				crcharaLoadFace(-1);
				crcharaCheckBattleFieldPos(1);
				prtRecovery(1);

				mcShow(1);

				evSet(19,1);

				mcDir(SOUTH);
				evMap(10,0,92,165);
			}
		}
	} else if(map == 20){
		//---アネートへの山道
		if(scene == 0){
			if(200 <= event && event <= 203){
				mcDir(NORTH);
				evMap(10,0,110,203);
			} else if(event == 204){
				if(evGet(24) && evGet(78) != 1){
					//---クリアパス
					evField(0,1);
					if(crbaseSelectYesNo("アネート側へ移動しますか？",64,64) == 0){
						mcDir(SOUTH);
						evMap(10,0,112,209);
						return 0;
					} else {
						evSet(78,1);
					}
				}
				mcDir(SOUTH);
				evScene(1,22,30);
			} else if(0 <= event && event <= 50){
				//---人々
				npTurn(event);
				evField(0,1);
				mes.FileMessage("Mt_ToAneat.msg",event,0);
				npReturn(event);
			}
		} else if(scene == 1){
			if(event == 200){
				mcDir(SOUTH);
				evScene(0,12,7);
				evSet(78,1);
			} else if(event == 201){
				mcDir(SOUTH);
				evScene(2,1,4);
			} else if(event == 0){
				//---宝箱
				itemBox(506,221,event);
			}
		} else if(scene == 2){
			if(event == 200){
				mcDir(SOUTH);
				evScene(1,15,4);
			} else if(event == 201){
				mcDir(SOUTH);
				evScene(4,8,4);
			} else if(event == 0){
				//---宝箱
				itemBox(507,221,event);
			}
		} else if(scene == 4){
			if(event == 201){
				mcDir(SOUTH);
				evScene(2,20,31);
			} else if(event == 200){
				if(evGet(24) == 0){
					SeneAneatDangeon();
					evSet(24,1);
				} else {
					mcDir(SOUTH);
					evScene(5,10,12);
					evSet(78,2);
				}
			}
		} else if(scene == 5){
			if(event == 200){
				if(evGet(24) && evGet(78) != 2){
					//---クリアパス
					evField(0,1);
					if(crbaseSelectYesNo("セーネ側へ移動しますか？",64,64) == 0){
						mcDir(NORTH);
						evMap(10,0,110,203);
						return 0;
					} else {
						evSet(78,2);
					}
				}
				mcDir(SOUTH);
				evScene(4,10,15);
			} else if(201 <= event && event <= 203){
				mcDir(SOUTH);
				evMap(10,0,112,209);
			}
		}
	}
	return 0;
}
