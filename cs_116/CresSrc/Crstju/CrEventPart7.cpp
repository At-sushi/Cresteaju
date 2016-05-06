/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrEventPart7.cpp ...Event functions

-----------------------------------------------------------*/


#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CREVENTPART7

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#include "CrBase.h"
#include "CrBattle.h"
#include "CrEvent.h"
#include "CrEvCom.h"

//---game info
#define CR_GAMEINFO_EXTERNPOINTER
#include "CrGameInfo.h"

CREVENTLONG4_API int creventKiokunoNaka_Fuin(void);
CREVENTLONG4_API int creventKiokunoNaka_Gazell(void);
CREVENTLONG5_API int creventKaminoYama_Top(void);

CREVENTLONG5_API int creventSilverStar_Chocho(void);
CREVENTLONG5_API int creventSilverStar_YumiCome(void);
CREVENTLONG5_API int creventSunpias_YumiVSCrasive(void);


CREVENTLONG7_API int creventKojinsaiChushinbu(void);
CREVENTLONG7_API int creventKojinsaiOilLake(void);


CREVENTPART7_API int creventCheckEvent_Part7(int event,int map,int scene)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;
	eiMapObject *pob = crfieldGetObjectPointer(event);

	CR_BATTLEINFO BatInfo;
	memset(&BatInfo,0,sizeof(BatInfo));

	if(map == 71){
		//---‹L‰¯‚Ì’†
		if(scene == 0){
			//---•”‰®
			if(event == 200){
				mcDir(SOUTH);
				evScene(1,1,15);
			} else if(event == 1){
				//---ƒNƒŒƒCƒVƒ”
				int mes_scene = 1;

				npTurn(event);
				evField(0,1);
				if(evGet(165) >= 5){
					mes_scene = 2;
				}
				mes.FileMessage("Fillgalt.msg",event + 40,mes_scene);
				evField(0,1);
				if(evGet(165) >= 5){
					if(crbaseSelectYesNo("‹x‚İ‚Ü‚·‚©H",64,64) == 0){
						//---Ä‚Ñí‚¢‚ÖEEE
						return creventKiokunoNaka_Fuin();
					}
				}

				npReturn(event);
			} else if(event == 4){
				evField(0,1);
				mes.FileMessage("Fillgalt.msg",event + 40,1);
			} else if(event == 3){
				//---‚‚ğ‚µ‚Ü‚¤
				if(!evGet(163) && !evGet(164)){
					npTurn(event);
					evField(0,1);
					mes.FileMessage("Fillgalt.msg",event + 40,3);
				} else if(evGet(163) && !evGet(164)){
					int mes_scene = 1;

					npTurn(event);
					evField(0,1);
					mes.FileMessage("Fillgalt.msg",event + 40,mes_scene);

					evField(0,1);
					if(crbaseSelectYesNo("‚µ‚Ü‚¢‚Ü‚·‚©H",64,64) == 0){
						mes.FileMessage("Fillgalt.msg",event + 40,2);
						evSet(164,1);
					}
					npReturn(event);
				}
			}
		} else if(scene == 1){
			//---˜L‰º
			if(event == 200){
				mcDir(SOUTH);
				evScene(0,13,5);
			} else if(event == 201){
				mcDir(SOUTH);
				evScene(2,1,16);
			} else if(event <= 20){
				int mes_scene = 1;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("Fillgalt.msg",event,mes_scene);
				//---˜b‚µ‚½‰ñ”
				if(evGet(165) < 100000){
					evSet(165,evGet(165) + 1);
				}

				npReturn(event);
			}
		} else if(scene == 2){
			//---ƒƒr[
			if(event == 200){
				mcDir(SOUTH);
				evScene(1,53,15);
			} else if(event == 201){
				mcDir(SOUTH);
				evScene(3,2,2);
			} else if(event == 202 || event == 203){
				//---’Ê‚¹‚È‚¢
				evField(0,1);
				mes.FileMessage("Fillgalt.msg",35,1);

				mcMove(-1,0);
				evFrame();
				mcResetEvent();
			} else if(event <= 20){
				int mes_scene = 1;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("Fillgalt.msg",event + 30,mes_scene);

				npReturn(event);
				//---˜b‚µ‚½‰ñ”
				if(evGet(165) < 100000){
					evSet(165,evGet(165) + 1);
				}
			}
		} else if(scene == 3){
			//---‘qŒÉ
			if(event == 200){
				mcDir(SOUTH);
				evScene(2,17,32);
			} else if(event == 0){
				int mes_scene = 1;

				npTurn(event);
				evField(0,1);
				if(evGet(163)){
					mes_scene = 2;
				} else {
					evSet(163,1);
				}
				mes.FileMessage("Fillgalt.msg",event + 50,mes_scene);

				npReturn(event);
			} else if(event <= 1){
				int mes_scene = 1;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("Fillgalt.msg",event + 50,mes_scene);

				npReturn(event);
			}
		}
	} else if(map == 74){
		//---Œ¶˜f‚Ì÷ŠCi‹L‰¯‚Ì’†j
		if(scene == 3){
			//---X‚S
			if(event == 201){
				//---ˆâÕ‚Ö
				mcDir(NORTH);
				evMap(35,0,6,27);
			} else if((event == 203 || event == 204) && !evGet(168)){
				//---‚±‚±‚ÍEEEH
				evSet(168,1);
				mcDir(NORTH);
				evFrameWait(1200);
				mcDir(EAST);
				evFrameWait(1200);
				mcDir(SOUTH);
				evFrameWait(1200);
				mcDir(WEST);
				evFrameWait(1200);

				mes.FileMessage("Fillgalt.msg",105);
			} else if(event == 205 && !evGet(169)){
				evSet(169,1);
				mcDir(WEST);
				evFrameWait(1200);
				mcDir(NORTH);
				evFrameWait(1200);
				mcDir(EAST);
				evFrameWait(1200);
				mcDir(SOUTH);
				evFrameWait(1200);

				mes.FileMessage("Fillgalt.msg",106);
			} else if(event == 202){
				//---ƒKƒ[[ƒ‹‚Æ‰ï‚¤
				return creventKiokunoNaka_Gazell();
			}
		}
	}
	return 1;
}


//---‚R•”
CREVENTPART7_API int creventCheckEvent_Part7_2(int event,int map,int scene)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;
	eiMapObject *pob = crfieldGetObjectPointer(event);

	if(map == 75){
		//---ƒoƒCƒc
		if(scene == 0){
			if(200 <= event && event <= 202){
				//---ƒtƒB[ƒ‹ƒh‚Ö
				mcDir(SOUTH);
				evMap(10,0,33,119);
			} else if(event == 203){
				//---h‰®‚QŠK
				mcDir(SOUTH);
				evScene(1,4,9);
			} else if(event == 204){
				//---–¯‰Æ‚QŠK
				mcDir(SOUTH);
				evScene(2,3,3);
			} else if(event == 0){
				evYado(380);
			} else if(event == 1){
				//---•Ší
				int ShopItem[] = {5,17,44,34,56,98,107,114,147,153,262,269,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 2){
				//---“¹‹ï
				int ShopItem[] = {221,222,226,227,171,172,173,174,175,198,183,178,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 21){
				//---¢ŠE’n}
				evShowWorldMap(33,119);
			} else if(event <= 20){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("Beiz.msg",event,mes_scene);
				npReturn(event);
			} else if(event == 205){
				//---ƒ^ƒ“ƒX^–{’I
				itemTansu(876,213);
			} else if(event == 206){
				//---ƒ^ƒ“ƒX^–{’I
				itemTansu(877,223);
			} else if(event == 207){
				//---ƒ^ƒ“ƒX^–{’I
				itemTansu(878,232);
			}
		} else if(scene == 1){
			//---h‰®‚QŠK
			if(event == 200){
				//---‚PŠK‚Ö
				mcDir(SOUTH);
				evScene(0,28,31);
			} else if(event == 201){
				//---ƒ^ƒ“ƒX^–{’I
				itemTansu(879,224);
			}
		} else if(scene == 2){
			//---–¯‰Æ‚QŠK
			if(event == 200){
				//---‚PŠK‚Ö
				mcDir(SOUTH);
				evScene(0,5,6);
			} else if(event <= 2){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("Beiz.msg",event + 50,mes_scene);
				npReturn(event);
			} else if(event == 201){
				//---ƒ^ƒ“ƒX^–{’I
				itemTansu(880,221);
			}
		}
	} else if(map == 76){
		//---_‚ÌR
		if(scene == 0){
			if(200 <= event && event <= 204){
				mcDir(SOUTH);
				evMap(10,0,39,115);
			} else if(event == 205){
				//---“´ŒA‚Ö
				mcDir(NORTH);
				evScene(1,11,43);
			} else if(event == 0){
				//---•ó” 
				itemBox(572,228,event);
			}
		} else if(scene == 1){
			//---“´ŒA
			if(200 == event){
				//---ŠO•”‚P‚Ö
				mcDir(SOUTH);
				evScene(0,29,4);
			} else if(event == 201){
				//---ŠO•”‚Q‚Ö
				mcDir(SOUTH);
				evScene(2,9,23);

				if(!evGet(172)){
					//---¸_‘Ì‚Ìº
					evSet(172,1);
					evFrameWait(700);
					//---¸_‘Ì‚Ìº
					{
						mes.CreateNewMessage(0,160,144,20,4,1);
						mes.OpenMessage("KaminoYama.msg",100);
						mes.ReadDraw();

						evFrameWait(250);
						mes.Paint();
						mes.ReadDraw();
						mes.CloseMessage();
					}
					evFrameWait(250);
					mcMove(0,1);
					evFrame();
					evFrameWait(250);
					mes.FileMessage("KaminoYama.msg",101);
					evFrameWait(1000);
					{
						mes.CreateNewMessage(0,160,144,20,4,1);
						mes.OpenMessage("KaminoYama.msg",102);
						mes.ReadDraw();

						evFrameWait(250);
						mes.Paint();
						mes.ReadDraw();
						evFrameWait(250);
						mes.Paint();
						mes.ReadDraw();
						mes.CloseMessage();
					}
					evFrameWait(250);
					mes.FileMessage("KaminoYama.msg",103);
				}
			} else if(event == 0){
				//---•ó” 
				itemBox(573,223,event);
			}
		} else if(scene == 2){
			//---ŠO•”‚Q
			if(200 == event){
				//---“´ŒA‚Ö
				mcDir(NORTH);
				evScene(1,38,17);
			} else if(201 <= event && event <= 203){
				//---ŠO•”‚R‚Ö
				mcDir(NORTH);
				evScene(3,9,30);
			} else if(event == 204){
				//---‰B‚µ•”‰®‚Ö
				mcDir(WEST);
				evScene(5,15,11);
			}
		} else if(scene == 3){
			//---ŠO•”‚R
			if(200 <= event && event <= 201){
				//---ŠO•”‚Q‚Ö
				mcDir(SOUTH);
				evScene(2,41,8);
			} else if(202 <= event && event <= 203){
				//---’¸ã‚Ö
				mcDir(NORTH);
				evScene(4,17,38);
			}
		} else if(scene == 4){
			//---’¸ã
			if(200 <= event && event <= 201){
				//---ŠO•”‚Q‚Ö
				mcDir(SOUTH);
				evScene(3,56,13);
			} else if(202 <= event && event <= 203
				&& !evGet(173)){
				//---¸_‘ÌI
				return creventKaminoYama_Top();
			}
		} else if(scene == 5){
			//---‰B‚µ•”‰®
			if(event == 200){
				//---ŠO•”‚Q‚Ö
				mcDir(EAST);
				evScene(2,33,18);
			} else if(event == 0){
				//---•ó” 
				itemBox(574,225,event);
			} else if(event == 1){
				//---•ó” 
				itemBox(575,80,event);
			}
		}
	} else if(map == 77){
		//---ƒVƒ‹ƒo[ƒXƒ^[
		if(scene == 0){
			if(200 <= event && event <= 202){
				//---ƒtƒB[ƒ‹ƒh‚Ö
				if(evGet(174) == 1){
					//---‚İ[‚Æ‚¿‚å‚¤‚¿‚å‚¤
					evField(0,1);
					mes.FileMessage("SilverStar.msg",103);
					evField(0,1);
					mcMove(0,-1);
					evFrame();
					mcResetEvent();
				} else if(evGet(174) == 2){
					//---ƒ†ƒ~•ƒ‰ƒCƒ[ƒ‹
					return creventSilverStar_YumiCome();
				} else {
					mcDir(SOUTH);
					evMap(10,0,59,175);
				}
			} else if(event == 203){
				//---h‰®‚QŠK
				mcDir(SOUTH);
				evScene(1,14,12);
			} else if(event == 204){
				//---’¬’·‚QŠK
				if(evGet(174) == 1){
					//---’¬’·‚Æ‚¨˜b
					return creventSilverStar_Chocho();
				} else {
					mcDir(SOUTH);
					evScene(2,11,2);
				}
			} else if(event == 0){
				evYado(420);
			} else if(event == 1){
				//---•Ší
				int ShopItem[] = {5,17,44,67,56,98,107,114,147,153,262,269,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 2){
				//---“¹‹ï
				int ShopItem[] = {221,222,226,227,171,172,173,174,175,198,183,178,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 19){
				//---¢ŠE’n}
				evShowWorldMap(59,175);
			} else if(event <= 20){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("SilverStar.msg",event,mes_scene);
				npReturn(event);
			} else if(event == 205){
				//---ƒ^ƒ“ƒX^–{’I
				itemTansu(881,232);
			} else if(event == 206){
				//---ƒ^ƒ“ƒX^–{’I
				itemTansu(882,216);
			} else if(event == 207){
				//---ƒ^ƒ“ƒX^–{’I
				itemTansu(884,225);
			}
		} else if(scene == 1){
			//---h‰®‚QŠK
			if(event == 200){
				//---‚PŠK‚Ö
				mcDir(SOUTH);
				evScene(0,37,24);
			} else if(event <= 2){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("SilverStar.msg",event + 60,mes_scene);
				npReturn(event);
			} else if(event == 201){
				//---ƒ^ƒ“ƒX^–{’I
				itemTansu(883,223);
			}
		} else if(scene == 2){
			//---’¬’·‚QŠK
			if(event == 200){
				//---‚PŠK‚Ö
				mcDir(SOUTH);
				evScene(0,54,18);
			} else if(event <= 2){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("SilverStar.msg",event + 50,mes_scene);
				npReturn(event);
			}
		}
	} else if(map == 78){
		//---ƒTƒ“ƒsƒAƒX
		if(scene == 0){
			if(200 <= event && event <= 228){
				//---ƒtƒB[ƒ‹ƒh‚Ö
				mcDir(SOUTH);
				evMap(10,0,44,208);
			} else if(229 <= event && event <= 231){
				//---X‚Ö
				mcDir(NORTH);
				evMap(79,0,6,24);
			}
		}
	} else if(map == 79){
		//---ƒTƒ“ƒsƒAƒX‚ÌX
		if(scene == 0){
			//---X
			if(200 <= event && event <= 201){
				//---ƒTƒ“ƒsƒAƒX‚Ö
				if(evGet(176) && !evGet(177)){
					//---‰œ
					evField(0,1);
					mes.FileMessage("Sunpias.msg",107);
					evField(0,1);
					mcMove(0,-1);
					evFrame();
					mcResetEvent();
				} else {
					mcDir(SOUTH);
					evMap(78,0,21,7);
				}
			} else if(202 <= event && event <= 203){
				//---•æ‚Ö
				mcDir(EAST);
				evScene(1,10,5);
			}
		} else if(scene == 1){
			//---•æ
			if(200 <= event && event <= 201){
				//---X‚Ö
				mcDir(WEST);
				evScene(0,47,23);
			} else if(202 <= event && event <= 203){
				//---ƒtƒB[ƒ‹ƒh‚Ö
				mcDir(SOUTH);
				evMap(10,0,44,208);
			} else if(204 <= event && event <= 206
				&& evGet(174) == 3 && !evGet(177)){
				//---ƒ†ƒ~‘ÎƒNƒŒƒCƒVƒ”
				return creventSunpias_YumiVSCrasive();
			}
		}
	} else if(map == 80){
		//---‘å_“a
		if(scene == 0){
			if(200 <= event && event <= 208){
				//---ƒtƒB[ƒ‹ƒh‚Ö
				mcDir(SOUTH);
				evMap(10,0,40,244);
			} else if(209 <= event && event <= 211){
				//---“à•”‚Ö
				mcDir(NORTH);
				evScene(1,26,55);
			} else if(event <= 10){
				//---l
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("Daishinden.msg",event,mes_scene);
				npReturn(event);
			}
		} else if(scene == 1){
			//---‚P‚e
			if(200 <= event && event <= 205){
				//---ŠO‚Ö
				mcDir(SOUTH);
				evScene(0,24,39);
			} else if(event == 206){
				//---‚Q‚e‚Ö¶
				mcDir(SOUTH);
				evScene(2,12,5);
			} else if(event == 207){
				//---‚Q‚e‚Ö‰E
				mcDir(SOUTH);
				evScene(2,31,5);
			}
		} else if(scene == 2){
			//---‚Q‚e
			if(event == 200){
				//---‚P‚e‚Ö¶
				mcDir(SOUTH);
				evScene(1,16,8);
			} else if(event == 201){
				//---‚P‚e‚Ö‰E
				mcDir(SOUTH);
				evScene(1,35,8);
			} else if(202 <= event && event <= 203){
				//---ƒXƒe[ƒW‚Ö¶
				mcDir(SOUTH);
				evScene(3,17,16);
			} else if(204 <= event && event <= 205){
				//---ƒXƒe[ƒW‚Ö‰E
				mcDir(SOUTH);
				evScene(3,37,16);
			} else if(206 <= event && event <= 209){
				//---ƒXƒe[ƒW‚Ö‰º
				if(!evGet(230))
					return creventKojinsaiChushinbu();

				mcDir(NORTH);
				evScene(3,27,37);
			}
		} else if(scene == 3){
			//---ƒXƒe[ƒW
			if(event == 200){
				//---‚Q‚e‚Ö¶
				mcDir(NORTH);
				evScene(2,14,11);
			} else if(event == 201){
				//---‚Q‚e‚Ö‰E
				mcDir(NORTH);
				evScene(2,29,11);
			} else if(202 <= event && event <= 204){
				//---‚Q‚e‚Ö‰º
				if(!evGet(230))
					return creventKojinsaiOilLake();

				mcDir(SOUTH);
				evScene(2,22,29);
			}
		}
	}
	return 1;
}
