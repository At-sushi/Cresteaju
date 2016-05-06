/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrEventPart2.cpp ...Event functions

-----------------------------------------------------------*/


#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CREVENTPART2

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

CREVENTLONG1_API int creventAneat_LunanChocho(void);
CREVENTLONG1_API int creventDoguri_MeetLizel(void);
CREVENTLONG1_API int creventVS_SS(void);
CREVENTLONG1_API int creventDoguri_DizzaCindy(void);
CREVENTLONG1_API int creventDoguriIseki_Crasive(void);

//-------------
CREVENTLONG5_API int creventDoguri_Muraokoshi(void);
CREVENTLONG5_API int creventDoguri_Sain(void);
CREVENTLONG5_API int creventDoguri_Moriuni(void);

CREVENTLONG9_API int crevent_AneatMoonlightSamit(void);


CREVENTPART2_API int creventCheckEvent_Part2(int event,int map,int scene)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;
	eiMapObject *pob = crfieldGetObjectPointer(event);

	CR_BATTLEINFO BatInfo;
	memset(&BatInfo,0,sizeof(BatInfo));

	if(map == 21){
		//---�A�l�[�g
		if(scene == 0){
			if(200 <= event && event <= 203){
				mcDir(SOUTH);
				evMap(10,0,146,229);
			} else if(event == 204){
				//---�����Q�K17,5
				mcDir(SOUTH);
				evScene(1,14,2);
			} else if(event == 207){
				//---�ʂ����
				npTurn(26);
				evField(0,1);
				if(evGet(43)){
					mes.FileMessage("Aneat.msg",26,100);
					evField(0,1);
					if(crbaseSelectYesNo("�t�F�C�}���֍s���܂����H",64,64) == 0){
						if(evGet(44) == 0){
							//---���t�F�C�}���I�@�V���f�B�͂����
							//148,229-183,220

							evFrameWait(250);

							ef->SetMoveEnything(1);
							int keep = ef->SetMoveSpeed(2);
							mcDir(EAST);
							crfieldChangeMap(10,0,1);
							crfieldSetMainCharacter(5);
							evScene(0,148,229);
							evFrameWait(250);
							for(a = 0;a < 20;a ++){
								mcMove(1,0);
								evFrame();
							}
							for(a = 0;a < 9;a ++){
								mcMove(0,-1);
								evFrame();
							}
							for(a = 0;a < 15;a ++){
								mcMove(1,0);
								evFrame();
							}
							ef->SetMoveSpeed(keep);
							ef->SetMoveEnything(0);
							evFrameWait(250);
							crfieldSetMainCharacter(1);

							crfieldChangeMap(26,0,1,1);
							mcShow(0);

							npPos(31,15,15);
							npDir(31,SOUTH);
							npPos(32,14,14);
							npDir(32,SOUTH);
							npPos(33,16,14);
							npDir(33,SOUTH);
							npPos(34,14,15);
							npDir(34,SOUTH);
							npPos(35,15,16);
							npDir(35,NORTH);
							evScene(0,15,16);

							evFrameWait(500);
							mes.OpenMessage("Faymarru.msg",101);
							mes.ReadDraw(4);
							mes.CloseMessage();
							evFrameWait(500);

							evSet(44,1);
							for(a = 31;a <= 35;a ++){
								npPos(a,0,0);
								npShow(a,0);
							}
							mcShow(1);
							//---�V���f�B�͂����
							pPartyInfo->PartyMember[4] = -1;
							mcDir(SOUTH);
							evScene(0,14,14);
						} else {
							mcDir(SOUTH);
							evMap(26,0,14,14);
						}
					} else {
						mcMove(0,1);
						evFrame();
						mcResetEvent();
						npReturn(26);
					}
				} else {
					mes.FileMessage("Aneat.msg",26,0);
					mcMove(0,1);
					evFrame();
					mcResetEvent();
					npReturn(26);
				}
			} else if(event == 0){
				//---�h
				if(AFTER_KOJINSAI() && !evGet(254)){
					//---����̃T�~�b�g
					return crevent_AneatMoonlightSamit();
				} else {
					evYado(16,map,scene);
				}
			} else if(event == 1){
				//---����
				int ShopItem[] = {221,226,227,171,172,174,195,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 3){
				//---����
				int ShopItem[] = {2,10,11,92,101,141,256,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 35){
				//---�n�}
				evShowWorldMap(146,229);
			} else if(0 <= event && event <= 50){
				//---���̐l�X
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);

				mes.FileMessage("Aneat.msg",event,mes_scene);
				if(event == 16){
					//---�嗤����
					int ret;
					CRWIN_SELECTINFO info;
					CrSelectWindow win;
					memset(&info,0,sizeof(info));
					do {
						crbaseMenuReset();
						win.Create(64,64,18,9,"���������Ă��炢�܂����H",
							"�t�B���K���g���āH;�嗤������āH;�̂ɉ����������́H;�嗤����̐_�T�}���āH;��������;");
						win.Refresh();
						crbaseMenuStart();
						ret = win.Select(&info);
						if(ret == -1)
							ret = 4;
						evField(0,1);
						mes.FileMessage("Aneat.msg",50,1 + ret);
					} while(ret != 4);
				}
				npReturn(event);
			} else if(event == 211){
				//---�^���X�^�{�I
				itemTansu(809,221);
			} else if(event == 212){
				//---�^���X�^�{�I
				itemTansu(810,213);
			} else if(event == 213 && evGet(23) == 0){
				//---�N���̖Y�ꕨ
				mes.OpenMessage("Aneat.msg",event);
				mes.ReadDraw(3);
				mcDir(NORTH);
				evFrameWait(250);

				evScene(0,28,38);
				mes.ReadDraw(9);
				mes.CloseMessage();

				critemAddItem(212,1);
				evSet(23,1);
			}
		} else if(scene == 1){
			if(event == 200){
				//---�����Q�K17,5
				mcDir(SOUTH);
				evScene(0,17,5);
			} else if(event == 201){
				if(evGet(22) == 0){
					return creventAneat_LunanChocho();
				} else {
				}
			} else if(event == 0){
				//---����
				int mes_scene = 2;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);
				if(!evGet(43)){
					mes.FileMessage("Aneat.msg",51 + event,1);
				} else {
					mes.FileMessage("Aneat.msg",51 + event,mes_scene);
				}
				npReturn(event);
			} else if(event == 202){
				//---�^���X�^�{�I
				itemTansu(811,216);
			}
		}
	} else if(map == 22){
		//---�h�[�O��
		//---22,1
		if(scene == 0){
			if(200 <= event && event <= 202){
				if(evGet(27) && !evGet(34)){
					//---�V���f�B�̈ē�
					mes.FileMessage("Doguri.msg",103);
					evField(0,1);
				}
				mcDir(SOUTH);
				evMap(10,0,127,250);
			} else if(event == 203){
				mcDir(WEST);
				evScene(1,12,2);
			} else if(event == 0){
				//---����
				int ShopItem[] = {2,10,11,92,101,141,256,221,226,227,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 1){
				//---�h
				evYado(12,map,scene);
			} else if(event == 204){
				//---�^���X�^�{�I
				itemTansu(812,221);
			} else if(event == 205){
				//---�^���X�^�{�I
				itemTansu(813,90);
			} else if(event == 23){
				//---���C�[���̘H��V���[
				if(evGet(25) <= 1){
					return creventDoguri_MeetLizel();
				}
			} else if((234 <= event && event <= 239)
				&& evGet(27) == 0 && evGet(26) == 1){
				//---�f�B�U�����ށE�V���f�B����
				return creventDoguri_DizzaCindy();

			} else if((event == 207 || event == 208)
				&& !evGet(182) && AFTER_YUMI()){
				//---�h�[�O��������
				return creventDoguri_Muraokoshi();
			} else if((event == 207 || event == 208)
				&& !evGet(183) && AFTER_YUMI()
				&& critemGetItemCount(214) == 0){
				//---�h�[�O�������T�C������
				return creventDoguri_Sain();
			} else if((event == 207 || event == 208)
				&& !evGet(184) && AFTER_YUMI()
				&& critemGetItemCount(214) == 0){
				//---�h�[�O�������E�j�u���[�h������
				return creventDoguri_Moriuni();

			} else if(0 <= event && event <= 36){
				int mes_scene = 2;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);
				if(evGet(26) == 0){
					mes.FileMessage("Doguri.msg",event);
				} else {
					mes.FileMessage("Doguri.msg",event,mes_scene);
				}

				npReturn(event);
			}
		} else if(scene == 1){
			if(event == 200){
				mcDir(NORTH);
				evScene(0,17,12);
			} else if(0 <= event && event <= 10){
				npTurn(event);
				evField(0,1);
				mes.FileMessage("Doguri.msg",event + 50);
				npReturn(event);
			} else if(event == 202){
				//---�^���X�^�{�I
				itemTansu(814,226);
			}
		}
	} else if(map == 23){
		//---�r�r�{��
		if(scene == 0){
			if(event == 200){
				//---�t�B�[���h��
				mcDir(SOUTH);
				evMap(10,0,117,231);
			} else if(event == 201){
				mcDir(SOUTH);
				evScene(1,51,21);
				//---�T���B�A�[�̖��@���
				if(evGet(30) == 0){
					evSet(30,1);
					mes.FileMessage("ss.msg",105);
					if(crbaseSelectYesNo("�����Ă��炢�܂����H",64,64) == 0){
						do {
							mes.FileMessage("ss.msg",106);
						} while(crbaseSelectYesNo("�킩��܂������H",64,64) != 0);
					} else {
						mes.FileMessage("ss.msg",107);
					}
				}
			} else if(event == 202){
				//---�������t�́H
				if(evGet(25) == 2 && evGet(28) == 0){
					evField(0,1);
					mes.OpenMessage("ss.msg",101);
					mes.ReadDraw(6);

					evFrameWait(500);
					em->Put(6,12,2,1024);
					evFrameWait(500);

					for(a = 0;a < 2;a ++){
						mcMove(0,-1);
						evFrame();
					}
					evFrameWait(250);
					mcDir(EAST);
					evFrameWait(500);
					mes.ReadDraw(2);

					mes.CloseMessage();
					evFrameWait(250);

					CR_BATTLEINFO BattleInfo;
					memset(&BattleInfo,0,sizeof(BattleInfo));
					BattleInfo.MapNumber = map;
					BattleInfo.Music = -1;
					BattleInfo.Enemy[0].Enemy = 37;
					BattleInfo.Enemy[0].x = 6;
					BattleInfo.Enemy[0].y = 6;
					BattleInfo.Enemy[1].Enemy = -1;
					BattleInfo.ScreenEfect = CRINTOBAT_NORMAL;
					evField(0,1);
					if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
						return MAINLOOP_BATTLEFAIL;
					}

					npPos(0,0,0);
					npShow(0,0);
					evSet(28,1);
				} else if(evGet(28) == 0){
					evField(0,1);
					mes.FileMessage("ss.msg",100);
				}
			}
		} else if(scene == 1){
			if(event == 200){
				mcDir(SOUTH);
				evScene(0,10,3);
			} else if(event == 201){
				mcDir(SOUTH);
				evScene(2,15,20);
			} else if(event == 0){
				//---��
				itemBox(508,227,event);
			} else if(event == 1){
				//---��
				itemBox(509,223,event);
			}
		} else if(scene == 2){
			if(event == 200){
				mcDir(SOUTH);
				evScene(1,26,3);
			} else if(event == 201){
				mcDir(NORTH);
				evScene(3,11,25);

				//---
				if(evGet(29) == 0){
					//---�����聕�艺
					evFrameWait(500);
					for(a = 0;a < 2;a ++){
						mcMove(0,-1);
						evFrame();
					}
					mcMove(-1,0);
					evFrame();
					evFrameWait(300);
					npDir(2,EAST);
					evFrameWait(125);
					npDir(3,SOUTH);
					evFrameWait(250);
					npDir(3,EAST);
					evFrameWait(250);

					evField(0,1);
					mes.OpenMessage("ss.msg",102);
					mes.ReadDraw(4);
					mes.CloseMessage();
					evFrameWait(250);

					CR_BATTLEINFO BattleInfo;
					memset(&BattleInfo,0,sizeof(BattleInfo));
					BattleInfo.MapNumber = map;
					BattleInfo.Music = -1;
					BattleInfo.Enemy[0].Enemy = 37;
					BattleInfo.Enemy[0].x = 5;
					BattleInfo.Enemy[0].y = 6;
					BattleInfo.Enemy[1].Enemy = 38;
					BattleInfo.Enemy[1].x = 8;
					BattleInfo.Enemy[1].y = 7;
					BattleInfo.Enemy[2].Enemy = -1;
					BattleInfo.ScreenEfect = CRINTOBAT_NORMAL;
					evField(0,1);
					for(a = 2;a < 4;a ++){
						npPos(a,0,0);
						npShow(a,0);
					}
					if(crbatEventBattle(&BattleInfo) == BATRET_LOSE){
						return MAINLOOP_BATTLEFAIL;
					}

					evSet(29,1);
				}
			} else if(event == 0){
				//---��
				itemBox(510,216,event);
			} else if(event == 1){
				//---��
				itemBox(511,223,event);
			}
		} else if(scene == 3){
			if(event == 200){
				mcDir(SOUTH);
				evScene(2,15,35);
			} else if((event == 201 || event == 202) && evGet(26) == 0){
				//---�u�r�V���[�e�B���O�X�^�[
				return creventVS_SS();
			}
		}
	} else if(map == 24){
		//---�h�[�O����̐X
		if(scene == 0){
			if(event == 200){
				//---�t�B�[���h��
				mcDir(NORTH);
				evMap(10,0,129,258);
			} else if(event == 201){
				//---��Փ�����
				mcDir(NORTH);
				evMap(25,0,19,25);
				if(evGet(34) == 0){
					evSet(34,1);
					mes.FileMessage("DoguriSouth_Iseki.msg",100);
				}
			} else if(event == 0){
				//---��
				itemBox(512,186,event);
			}
		}//---19,31
	} else if(map == 25){
		if(scene == 0){
			//---�h�[�O����̈��
			if(event == 200 || event == 201){
				//---�X��
				mcDir(SOUTH);
				evMap(24,0,60,18);
			} else if(event == 202){
				if(evGet(35) == 0){
					evSet(35,1);
/*
					npPos(0,12,7);
					npDir(0,SOUTH);
					npPos(1,12,8);
					npDir(1,NORTH);
					npPos(2,10,8);
					npDir(2,EAST);
					npPos(3,11,7);
					npDir(3,NORTH);
					mcShow(0);
					evScene(1,19,31);*/
					mcShow(0);
					crfieldChangeScene(1,19,31);

					npPos(0,19,30);
					npDir(0,NORTH);
					npPos(1,19,29);
					npDir(1,NORTH);
					npPos(2,21,31);
					npDir(2,EAST);
					npPos(3,17,30);
					npDir(3,WEST);
					mcShow(0);
					evScene(1,19,31);

					mes.OpenMessage("DoguriSouth_Iseki.msg",101);
					evFrameWait(1000);
					npDir(0,EAST);
					evFrameWait(1000);
					npDir(0,SOUTH);
					evFrameWait(300);
					npDir(0,WEST);
					evFrameWait(700);
					npDir(0,SOUTH);
					evFrameWait(500);
					mes.ReadDraw(3);
					evFrameWait(1000);
					npDir(0,EAST);
					evFrameWait(500);
					npDir(0,NORTH);
					evFrameWait(500);
					mes.ReadDraw();

					npDir(2,NORTH);
					evFrameWait(250);
					npDir(3,NORTH);
					evFrameWait(300);
					mes.ReadDraw();
					evFrameWait(1000);
					//---�m��Ȃ��H
					mes.ReadDraw();
					evFrameWait(500);
					mes.ReadDraw(2);
					evFrameWait(500);
					mes.ReadDraw();
					evFrameWait(500);
					mes.ReadDraw();
					evFrameWait(500);

					mes.CloseMessage();
					for(a = 0;a < 4;a ++){
						npPos(a,0,0);
						npShow(a,0);
					}
					mcShow(1);
				}
				mcDir(SOUTH);
				evScene(1,19,31);
			} else if(event == 0){
				//---��
				itemBox(513,223,event);
			}
		} else if(scene == 1){
			int yes;
			if(event == 200){
				mcDir(SOUTH);
				evScene(0,13,25);
			} else if(event == 201){
				mcDir(SOUTH);
				evScene(2,4,18);
			} else if(event == 202){
				//---��
				if(evGet(40) == 0){
					mes.FileMessage("DoguriSouth_Iseki.msg",1);
				} else {
					if(evGet(41) == 0){
						crsoundPlay(CRSOUND_DOOR);
					}
					em->Put(11,31,2,1024);
					evSet(41,1);
				}
			} else if(event == 203){
				//---��
				evField(0,1);
				mes.FileMessage("DoguriSouth_Iseki.msg",2);
			} else if(event == 204){
				//---�X�C�b�`�P
				evField(0,1);
				mes.FileMessage("DoguriSouth_Iseki.msg",3);
				yes = crbaseSelectYesNo("�X�C�b�`�������܂����H",96,64);
				if(yes == 0){
					if(!evGet(38) && !evGet(39)){
						evSet(37,1);
					} else {
						evSet(37,0);
						evSet(38,0);
						evSet(39,0);
					}
					mes.FileMessage("DoguriSouth_Iseki.msg",8);
				}
			} else if(event == 205){
				//---�X�C�b�`�Q
				evField(0,1);
				mes.FileMessage("DoguriSouth_Iseki.msg",4);
				yes = crbaseSelectYesNo("�X�C�b�`�������܂����H",96,64);
				if(yes == 0){
					if(evGet(37) && !evGet(39)){
						evSet(38,1);
					} else {
						evSet(37,0);
						evSet(38,0);
						evSet(39,0);
					}
					mes.FileMessage("DoguriSouth_Iseki.msg",8);
				}
			} else if(event == 206){
				//---�X�C�b�`�R
				evField(0,1);
				mes.FileMessage("DoguriSouth_Iseki.msg",5);
				yes = crbaseSelectYesNo("�X�C�b�`�������܂����H",96,64);
				if(yes == 0){
					if(evGet(37) && evGet(38)){
						evSet(39,1);
						evSet(40,1);
						//---�����J��
						evField(0,1);
						mes.FileMessage("DoguriSouth_Iseki.msg",8);
						evFrameWait(500);
						crsoundPlay(CRSOUND_ATACK4);
						evFrameWait(500);
						mes.FileMessage("DoguriSouth_Iseki.msg",6);
					} else {
						mes.FileMessage("DoguriSouth_Iseki.msg",8);
						evSet(37,0);
						evSet(38,0);
						evSet(39,0);
					}
				}
			}
		} else if(scene == 2){
			if(event == 200){
				mcDir(SOUTH);
				evScene(1,6,31);
			} else if(event == 201){
				mcDir(SOUTH);
				evScene(3,13,3);
			} else if(event == 202){
				//---�g�C���͂�����
				if(evGet(36) == 0){
					mes.FileMessage("DoguriSouth_Iseki.msg",102);
					evSet(36,1);
				} else {
					mes.FileMessage("DoguriSouth_Iseki.msg",7);
				}
			} else if(event == 4){
				//---��
				itemBox(514,216,event);
			} else if(event == 5){
				//---��
				itemBox(515,172,event);
			}
		} else if(scene == 3){
			if(event == 200){
				mcDir(SOUTH);
				evScene(2,25,4);
			} else if(event == 201 && evGet(42) == 0){
				return creventDoguriIseki_Crasive();
			}
		}
	}
	return 1;
}
