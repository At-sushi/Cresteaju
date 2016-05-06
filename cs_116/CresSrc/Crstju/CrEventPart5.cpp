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
		//---�A���V�A
		if(scene == 0){
			if(200 <= event && event <= 203){
				//---�t�B�[���h��
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
				//--�f�B�U�̉�
				return creventAlsia_DizzasHome();
			} else if(event == 204){
				//---�h���Q�K
				mcDir(NORTH);
				evScene(1,17,12);
			} else if(event == 205){
				//---�f�B�U�Q�K
				mcDir(SOUTH);
				evScene(2,2,2);
			} else if(event == 206){
				//---���V�Q�K
				if(evGet(199) && !evGet(203)){
					//---凋C�O�̓��N���A�����[���h�܂�
					return creventAlsia_World();
				} else {
					mcDir(NORTH);
					evScene(3,12,11);
				}
			} else if(event == 0){
				//---�h
				if(evGet(121) && !evGet(122)){
					evField(0,1);
					mes.FileMessage("Alsia.msg",103);
				} else {
					evYado(166,map,scene);
				}
			} else if(event == 1){
				//---��������
				int ShopItem[] = {221,222,226,227,236,195,171,172,173,174,200,201,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 20){
				//---���E�n�}
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
					//---�A���V�A����
				}
				mes.FileMessage("Alsia.msg",event,mes_scene);
				npReturn(event);
			} else if(event == 207){
				//---�^���X�^�{�I
				itemTansu(849,223);
			} else if(event == 208){
				//---�^���X�^�{�I
				itemTansu(850,226);
			} else if(event == 209){
				//---�^���X�^�{�I
				itemTansu(851,222);
			}
		} else if(scene == 1){
			//---�h���Q�K
			if(event == 200){
				//---�P�K��
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
			//---�f�B�U�̉ƂQ�K
			if(event == 200){
				//---�P�K��
				mcDir(SOUTH);
				evScene(0,30,59);
			} else if(event <= 10){
				int mes_scene = 1;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("Alsia.msg",event + 60,mes_scene);
				npReturn(event);
			} else if(event == 201){
				//---�^���X�^�{�I
				itemTansu(852,23);
			} else if(event == 202){
				//---�^���X�^�{�I
				itemTansu(853,203);
			}
		} else if(scene == 3){
			//---���V�Q�K
			if(event == 200){
				//---�P�K��
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
				//---�^���X�^�{�I
				itemTansu(854,167);
			}
		}
	} else if(map == 52){
		//---��N���[�^�[
		if(scene == 0){
			if(200 <= event && event <= 262){
				//---�t�B�[���h��227,54 ,235,61,  219,61 , 227,69
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
		//---�A���V�A�Ίݓ��A
		if(scene == 0){
			if(event == 200){
				mcDir(SOUTH);
				evMap(10,0,189,63);
			} else if(201 <= event && event <= 205
				&& evGet(133) && !evGet(134)){
				//---�΂ǂڂ�
				return creventAlsia_IntoLake();
			} else if(205 <= event && event <= 231
				&& evGet(134)){
				//---�j���ł���
				evField(0,1);
				mes.FileMessage("AlsiaLake.msg",0);
				evField(0,1);
				mcDir(SOUTH);
				evScene(1,15,9);
			}
		} else if(scene == 1){
			//---�a�P�|�Q
			if(200 <= event && event <= 207){
				//---�j���ł��߂�
				evField(0,1);
				mes.FileMessage("AlsiaLake.msg",0);
				evField(0,1);
				mcDir(SOUTH);
				evScene(0,15,34);
			} else if(209 <= event && event <= 211
				&& !evGet(135)){
				//---�������
				evFrameWait(250);
				mes.FileMessage("AlsiaLake.msg",101);
				evSet(135,1);
			} else if(event == 208){
				mcDir(WEST);
				evScene(2,61,22);
			} else if(event == 5){
				//---��
				itemBox(556,219,event);
			} else if(event == 6){
				//---��
				itemBox(557,224,event);
			}
		} else if(scene == 2){
			//---�a�P�|�R
			if(event == 200){
				mcDir(EAST);
				evScene(1,15,44);
			} else if(201 <= event && event <= 205
				&& !evGet(136)){
				//---�O���E���h�V�b�v�Q�b�g�I�I
				return creventAlsia_GetGS();
			}
		}
	} else if(map == 54){
		//---�Z�m�E
		if(scene == 0){
			if(200 <= event && event <= 242){
				//---�t�B�[���h��
				mcDir(SOUTH);
				evMap(10,0,254,32);
			} else if(event <= 10){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = 6;

				if(event == 5 && !evGet(252)){
					//---���[�t�B�A
					return crevent_CenowRarfia();
				} else {
					npTurn(event);
					evField(0,1);
					mes.FileMessage("Cenow.msg",event,mes_scene);
					npReturn(event);
				}
			} else if(event == 243){
				//---�^���X�^�{�I
				itemTansu(855,179);
			}
		}
	} else if(map == 55){
		//---�[�r�A�}�C��
		if(scene == 0){
			if(200 <= event && event <= 202){
				//---�t�B�[���h��
				mcDir(SOUTH);
				evMap(10,0,293,69);
			} else if(event == 203){
				//---�Y�B��
				mcDir(NORTH);
				evMap(56,0,17,34);
			} else if(event == 205){
				//---�h���Q�K��
				mcDir(NORTH);
				evScene(1,15,12);
			} else if(event == 204){
				//---�f�B���}�@���
				mcDir(NORTH);
				evScene(2,10,14);
			} else if((event == 22 || event == 206) && !evGet(125)){
				//---�Y�B���w���I�I
				npTurn(22);
				return creventZevia_BuyMineSuit(event);
			} else if(event == 206 && (!evGet(126) && !evGet(127))){
				//---�ʂ��܂���I
				evField(0,1);
				mes.FileMessage("ZeviaMine.msg",22);
				evField(0,1);
				mcMove(0,1);
				evFrame();
				mcResetEvent();
			} else if((event == 210 || event == 211)
				&& evGet(125) && !evGet(127)){
				//---�Y�B�͂���H
				evField(0,1);
				mes.FileMessage("ZeviaMine.msg",101);
				evField(0,1);
				if(crbaseSelectYesNo("����܂����H",64,64) == 0){
					//---���C���L�������[�h
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
				//---����
				int ShopItem[] = {4,15,42,54,96,105,112,145,151,260,267,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 0){
				//---����
				int ShopItem[] = {221,222,226,227,171,172,173,175,177,181,201,197,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 23){
				//---���E�n�}
				evShowWorldMap(293,69);
			} else if(event <= 30){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;
				else if(evGet(127))
					//---�N���C�V�u���ꂽ����
					mes_scene = 3;
				else if(evGet(126))
					mes_scene = 2;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("ZeviaMine.msg",event,mes_scene);

				//---�f�B���}���
				if(event == 26 && evGet(127) && 
					(npGet(event)->xGet() == 16)){
					//---����
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
				//---�^���X�^�{�I
				itemTansu(856,223);
			} else if(event == 208){
				//---�^���X�^�{�I
				itemTansu(857,259);
			} else if(event == 209){
				//---�^���X�^�{�I
				itemTansu(858,213);
			}
		} else if(scene == 1){
			//---�h���Q�K
			if(event == 200){
				//---�P�K��
				if(evGet(132) && !evGet(133)){
					//---�T���B�A�[�Ƃ̍ĉ�
					return creventMine_Xavier();
				} else {
					mcDir(SOUTH);
					evScene(0,48,48);
				}
			} else if(event == 0){
				//---�h
				if(evGet(132) && !evGet(133)){
					//---���܂�Ȃ�
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
				//---�^���X�^�{�I
				itemTansu(859,227);
			}
		} else if(scene == 2){
			//---�f�B���}�@��
			if(200 <= event && event <= 201){
				//---�O��
				mcDir(SOUTH);
				evScene(0,16,43);
			} else if(event == 202){
				//---�Q�K��
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
			//---�f�B���}�@��Q�K
			if(event == 200){
				//---�P�K��
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
				//---�^���X�^�{�I
				itemTansu(860,225);
			} else if(event == 202){
				//---�^���X�^�{�I
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
		//---�Y�B
		if(scene == 0){
			if(200 <= event && event <= 202){
				//---�[�r�A�}�C����
				mcDir(SOUTH);
				evMap(55,0,31,8);
			} else if(event == 203){
				//---�a�Q��
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
			//---�a�Q
			if(event == 200){
				//---�a�P��
				mcDir(SOUTH);
				evScene(0,18,3);
			} else if(event == 201){
				//---�a�R��
				mcDir(SOUTH);
				evScene(2,11,33);
			} else if(event == 205 && !evGet(127)){
				//---���i���߂܂�I�I
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
			//---�a�R
			if(event == 200){
				//---�a�Q��
				mcDir(SOUTH);
				evScene(1,31,5);
			} else if(event == 201){
				//---�Y�B��Ղ�
				mcDir(SOUTH);
				evMap(57,0,20,35);
			}
		}
	} else if(map == 57){
		//---�Y�B���
		if(scene == 0){
			//---�a�P
			if(event == 200){
				//---�Y�B��
				mcDir(SOUTH);
				evMap(56,2,23,10);
			} else if(event == 201){
				//---�a�Q
				mcDir(SOUTH);
				evScene(1,21,48);
			} else if(event == 0){
				//---��
				itemBox(551,224,event);
			} else if(event == 1){
				//---��
				itemBox(552,219,event);
			} else if(event == 2){
				//---��
				itemBox(553,227,event);
			}
		} else if(scene == 1){
			//---�a�Q
			if(event == 200){
				//---�a�P��
				mcDir(SOUTH);
				evScene(0,4,25);
			} else if(event == 201){
				//---�a�P�|�Q��
				mcDir(SOUTH);
				evScene(2,24,21);
			} else if(event == 202){
				//---�a�P�|�R��
				mcDir(SOUTH);
				evScene(5,3,14);
			} else if(event == 0 && !evGet(132)){
				//---�t�@�X���N���A
				return creventMine_FasraCrear();
			} else if((event == 203 || event == 204)
				&& !evGet(128)){
				//---���ꂪ�E�E�E
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
			//---�a�P�|�Q
			if(event == 200){
				//---�a�Q��
				mcDir(SOUTH);
				evScene(1,45,18);
			} else if(event == 201){
				//---�a�O��
				mcDir(SOUTH);
				evScene(4,11,4);
				evSet(130,0);
			} else if(event == 202){
				//---��������
				mcDir(SOUTH);
				evScene(3,8,4);
			} else if(event == 0){
				//---��
				itemBox(554,223,event);
			}
		} else if(scene == 3){
			//---������
			if(event == 200){
				//---�a�P�|�Q��
				mcDir(SOUTH);
				evScene(2,24,4);
			} else if(event == 0){
				//---��
				itemBox(555,117,event);
			}
		} else if(scene == 4){
			//---�a�O
			if(event == 200){
				//---�a�Q��
				mcDir(SOUTH);
				evScene(2,21,40);
				evSet(130,0);
				evSet(131,0);
			} else if(event == 201){
				//---�a�P�|�R��
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
						//---�U��������I
						evField(0,1);
						mes.FileMessage("Mine.msg",80);
						evFrameWait(250);

						//---�o�g��
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
					//---����O�i�Z�b�g
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
					//---�^�C�}�[���Z�b�g
					evStartTimer();
					evSet(131,1);
				}
			}
		} else if(scene == 5){
			//---�a�P�|�R
			if(event == 200){
				//---�a�O��
				mcDir(SOUTH);
				evScene(4,7,28);
			} else if(event == 201){
				//---�a�Q��
				mcDir(SOUTH);
				evScene(1,22,20);
			}
		}
	} else if(map == 58){
		//---�[�r�A�}�C���O���E���h�V�b�v�D������
		if(scene == 0){
			if(200 <= event && event <= 201){
				//---�t�B�[���h��
				mcDir(SOUTH);
				evMap(10,0,297,77);
			} else if(event == 202){
				//---����Ȃ�
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
		//---�O���E���h�V�b�v
		if(scene == 0){
			if(event == 201){
				//---�O��
				if(evGet(170) && !evGet(171)){
					//---�o�C�c
					mcDir(SOUTH);
					evMap(10,0,57,94);
				}
			} else if(event == 200){
				mcDir(SOUTH);
				evScene(1,3,5);
			} else if(event <= 6
				|| /*���~�Q�Ă�*/(event == 16 && evGet(177) && !evGet(178)) && !evGet(209)){
				int mes_scene = 1;

				if(event == 16)
					event = 4;

				npTurn(event);
				evField(0,1);

				if(AFTER_KOJINSAI())
					mes_scene = 9;
				else if(evGet(209))
					//---�암��ጴ�N���A
					mes_scene = 8;
				else if(evGet(199))
					//---凋C�O�̓�
					mes_scene = 7;
				else if(evGet(190))
					//---��N���[�^�[�N���A
					mes_scene = 6;
				else if(AFTER_YUMI())
					//---���~�̉ߋ��̂���
					mes_scene = MESSAGE_YUMI;

				mes.FileMessage("GS.msg",event,mes_scene);
				npReturn(event);
			} else if(7 <= event && event <= 16){
				//---�Q��
				evField(0,1);
				if(crbaseSelectYesNo("�x�e���܂����H",64,64) == 0){
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
				//---�T���B�A�[
				int mes_scene = 1;
				npTurn(event);
				evField(0,1);

				if(AFTER_KOJINSAI())
					mes_scene = 9;
				else if(evGet(209))
					//---�암��ጴ�N���A
					mes_scene = 8;
				else if(evGet(199))
					//---凋C�O�̓�
					mes_scene = 7;
				else if(evGet(190))
					//---��N���[�^�[�N���A
					mes_scene = 6;
				else if(AFTER_YUMI())
					mes_scene = 1;//MESSAGE_YUMI;
				else if(evGet(173))
					mes_scene = 2;

				mes.FileMessage("GS.msg",event,mes_scene);
				npReturn(event);

			} else if(event == 7){
				//---���E�n�}
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
