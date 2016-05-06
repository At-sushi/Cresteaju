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
		//---�L���̒�
		if(scene == 0){
			//---����
			if(event == 200){
				mcDir(SOUTH);
				evScene(1,1,15);
			} else if(event == 1){
				//---�N���C�V��
				int mes_scene = 1;

				npTurn(event);
				evField(0,1);
				if(evGet(165) >= 5){
					mes_scene = 2;
				}
				mes.FileMessage("Fillgalt.msg",event + 40,mes_scene);
				evField(0,1);
				if(evGet(165) >= 5){
					if(crbaseSelectYesNo("�x�݂܂����H",64,64) == 0){
						//---�Ăѐ킢�ցE�E�E
						return creventKiokunoNaka_Fuin();
					}
				}

				npReturn(event);
			} else if(event == 4){
				evField(0,1);
				mes.FileMessage("Fillgalt.msg",event + 40,1);
			} else if(event == 3){
				//---�������܂�
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
					if(crbaseSelectYesNo("���܂��܂����H",64,64) == 0){
						mes.FileMessage("Fillgalt.msg",event + 40,2);
						evSet(164,1);
					}
					npReturn(event);
				}
			}
		} else if(scene == 1){
			//---�L��
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
				//---�b������
				if(evGet(165) < 100000){
					evSet(165,evGet(165) + 1);
				}

				npReturn(event);
			}
		} else if(scene == 2){
			//---���r�[
			if(event == 200){
				mcDir(SOUTH);
				evScene(1,53,15);
			} else if(event == 201){
				mcDir(SOUTH);
				evScene(3,2,2);
			} else if(event == 202 || event == 203){
				//---�ʂ��Ȃ�
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
				//---�b������
				if(evGet(165) < 100000){
					evSet(165,evGet(165) + 1);
				}
			}
		} else if(scene == 3){
			//---�q��
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
		//---���f�̎��C�i�L���̒��j
		if(scene == 3){
			//---�X�S
			if(event == 201){
				//---��Ղ�
				mcDir(NORTH);
				evMap(35,0,6,27);
			} else if((event == 203 || event == 204) && !evGet(168)){
				//---�����́E�E�E�H
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
				//---�K�[�[���Ɖ
				return creventKiokunoNaka_Gazell();
			}
		}
	}
	return 1;
}


//---�R��
CREVENTPART7_API int creventCheckEvent_Part7_2(int event,int map,int scene)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;
	eiMapObject *pob = crfieldGetObjectPointer(event);

	if(map == 75){
		//---�o�C�c
		if(scene == 0){
			if(200 <= event && event <= 202){
				//---�t�B�[���h��
				mcDir(SOUTH);
				evMap(10,0,33,119);
			} else if(event == 203){
				//---�h���Q�K
				mcDir(SOUTH);
				evScene(1,4,9);
			} else if(event == 204){
				//---���ƂQ�K
				mcDir(SOUTH);
				evScene(2,3,3);
			} else if(event == 0){
				evYado(380);
			} else if(event == 1){
				//---����
				int ShopItem[] = {5,17,44,34,56,98,107,114,147,153,262,269,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 2){
				//---����
				int ShopItem[] = {221,222,226,227,171,172,173,174,175,198,183,178,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 21){
				//---���E�n�}
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
				//---�^���X�^�{�I
				itemTansu(876,213);
			} else if(event == 206){
				//---�^���X�^�{�I
				itemTansu(877,223);
			} else if(event == 207){
				//---�^���X�^�{�I
				itemTansu(878,232);
			}
		} else if(scene == 1){
			//---�h���Q�K
			if(event == 200){
				//---�P�K��
				mcDir(SOUTH);
				evScene(0,28,31);
			} else if(event == 201){
				//---�^���X�^�{�I
				itemTansu(879,224);
			}
		} else if(scene == 2){
			//---���ƂQ�K
			if(event == 200){
				//---�P�K��
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
				//---�^���X�^�{�I
				itemTansu(880,221);
			}
		}
	} else if(map == 76){
		//---�_�̎R
		if(scene == 0){
			if(200 <= event && event <= 204){
				mcDir(SOUTH);
				evMap(10,0,39,115);
			} else if(event == 205){
				//---���A��
				mcDir(NORTH);
				evScene(1,11,43);
			} else if(event == 0){
				//---��
				itemBox(572,228,event);
			}
		} else if(scene == 1){
			//---���A
			if(200 == event){
				//---�O���P��
				mcDir(SOUTH);
				evScene(0,29,4);
			} else if(event == 201){
				//---�O���Q��
				mcDir(SOUTH);
				evScene(2,9,23);

				if(!evGet(172)){
					//---���_�̂̐�
					evSet(172,1);
					evFrameWait(700);
					//---���_�̂̐�
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
				//---��
				itemBox(573,223,event);
			}
		} else if(scene == 2){
			//---�O���Q
			if(200 == event){
				//---���A��
				mcDir(NORTH);
				evScene(1,38,17);
			} else if(201 <= event && event <= 203){
				//---�O���R��
				mcDir(NORTH);
				evScene(3,9,30);
			} else if(event == 204){
				//---�B��������
				mcDir(WEST);
				evScene(5,15,11);
			}
		} else if(scene == 3){
			//---�O���R
			if(200 <= event && event <= 201){
				//---�O���Q��
				mcDir(SOUTH);
				evScene(2,41,8);
			} else if(202 <= event && event <= 203){
				//---�����
				mcDir(NORTH);
				evScene(4,17,38);
			}
		} else if(scene == 4){
			//---����
			if(200 <= event && event <= 201){
				//---�O���Q��
				mcDir(SOUTH);
				evScene(3,56,13);
			} else if(202 <= event && event <= 203
				&& !evGet(173)){
				//---���_�́I
				return creventKaminoYama_Top();
			}
		} else if(scene == 5){
			//---�B������
			if(event == 200){
				//---�O���Q��
				mcDir(EAST);
				evScene(2,33,18);
			} else if(event == 0){
				//---��
				itemBox(574,225,event);
			} else if(event == 1){
				//---��
				itemBox(575,80,event);
			}
		}
	} else if(map == 77){
		//---�V���o�[�X�^�[
		if(scene == 0){
			if(200 <= event && event <= 202){
				//---�t�B�[���h��
				if(evGet(174) == 1){
					//---�݁[�Ƃ��傤���傤
					evField(0,1);
					mes.FileMessage("SilverStar.msg",103);
					evField(0,1);
					mcMove(0,-1);
					evFrame();
					mcResetEvent();
				} else if(evGet(174) == 2){
					//---���~�����C�[��
					return creventSilverStar_YumiCome();
				} else {
					mcDir(SOUTH);
					evMap(10,0,59,175);
				}
			} else if(event == 203){
				//---�h���Q�K
				mcDir(SOUTH);
				evScene(1,14,12);
			} else if(event == 204){
				//---�����Q�K
				if(evGet(174) == 1){
					//---�����Ƃ��b
					return creventSilverStar_Chocho();
				} else {
					mcDir(SOUTH);
					evScene(2,11,2);
				}
			} else if(event == 0){
				evYado(420);
			} else if(event == 1){
				//---����
				int ShopItem[] = {5,17,44,67,56,98,107,114,147,153,262,269,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 2){
				//---����
				int ShopItem[] = {221,222,226,227,171,172,173,174,175,198,183,178,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 19){
				//---���E�n�}
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
				//---�^���X�^�{�I
				itemTansu(881,232);
			} else if(event == 206){
				//---�^���X�^�{�I
				itemTansu(882,216);
			} else if(event == 207){
				//---�^���X�^�{�I
				itemTansu(884,225);
			}
		} else if(scene == 1){
			//---�h���Q�K
			if(event == 200){
				//---�P�K��
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
				//---�^���X�^�{�I
				itemTansu(883,223);
			}
		} else if(scene == 2){
			//---�����Q�K
			if(event == 200){
				//---�P�K��
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
		//---�T���s�A�X
		if(scene == 0){
			if(200 <= event && event <= 228){
				//---�t�B�[���h��
				mcDir(SOUTH);
				evMap(10,0,44,208);
			} else if(229 <= event && event <= 231){
				//---�X��
				mcDir(NORTH);
				evMap(79,0,6,24);
			}
		}
	} else if(map == 79){
		//---�T���s�A�X�̐X
		if(scene == 0){
			//---�X
			if(200 <= event && event <= 201){
				//---�T���s�A�X��
				if(evGet(176) && !evGet(177)){
					//---��
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
				//---���
				mcDir(EAST);
				evScene(1,10,5);
			}
		} else if(scene == 1){
			//---��
			if(200 <= event && event <= 201){
				//---�X��
				mcDir(WEST);
				evScene(0,47,23);
			} else if(202 <= event && event <= 203){
				//---�t�B�[���h��
				mcDir(SOUTH);
				evMap(10,0,44,208);
			} else if(204 <= event && event <= 206
				&& evGet(174) == 3 && !evGet(177)){
				//---���~�΃N���C�V��
				return creventSunpias_YumiVSCrasive();
			}
		}
	} else if(map == 80){
		//---��_�a
		if(scene == 0){
			if(200 <= event && event <= 208){
				//---�t�B�[���h��
				mcDir(SOUTH);
				evMap(10,0,40,244);
			} else if(209 <= event && event <= 211){
				//---������
				mcDir(NORTH);
				evScene(1,26,55);
			} else if(event <= 10){
				//---�l
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
			//---�P�e
			if(200 <= event && event <= 205){
				//---�O��
				mcDir(SOUTH);
				evScene(0,24,39);
			} else if(event == 206){
				//---�Q�e�֍�
				mcDir(SOUTH);
				evScene(2,12,5);
			} else if(event == 207){
				//---�Q�e�։E
				mcDir(SOUTH);
				evScene(2,31,5);
			}
		} else if(scene == 2){
			//---�Q�e
			if(event == 200){
				//---�P�e�֍�
				mcDir(SOUTH);
				evScene(1,16,8);
			} else if(event == 201){
				//---�P�e�։E
				mcDir(SOUTH);
				evScene(1,35,8);
			} else if(202 <= event && event <= 203){
				//---�X�e�[�W�֍�
				mcDir(SOUTH);
				evScene(3,17,16);
			} else if(204 <= event && event <= 205){
				//---�X�e�[�W�։E
				mcDir(SOUTH);
				evScene(3,37,16);
			} else if(206 <= event && event <= 209){
				//---�X�e�[�W�։�
				if(!evGet(230))
					return creventKojinsaiChushinbu();

				mcDir(NORTH);
				evScene(3,27,37);
			}
		} else if(scene == 3){
			//---�X�e�[�W
			if(event == 200){
				//---�Q�e�֍�
				mcDir(NORTH);
				evScene(2,14,11);
			} else if(event == 201){
				//---�Q�e�։E
				mcDir(NORTH);
				evScene(2,29,11);
			} else if(202 <= event && event <= 204){
				//---�Q�e�։�
				if(!evGet(230))
					return creventKojinsaiOilLake();

				mcDir(SOUTH);
				evScene(2,22,29);
			}
		}
	}
	return 1;
}
