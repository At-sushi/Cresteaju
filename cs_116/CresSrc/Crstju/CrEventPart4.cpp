/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrEventPart4.cpp ...Event functions

-----------------------------------------------------------*/


#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CREVENTPART4

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#include "CrBase.h"
#include "CrBattle.h"
#include "CrEvent.h"
#include "CrEvCom.h"

//---game info
#define CR_GAMEINFO_EXTERNPOINTER
#include "CrGameInfo.h"

CREVENTLONG2_API int creventTreia_LunarnCrasive(void);
CREVENTLONG2_API int creventOilLake_Yumi(void);
CREVENTLONG2_API int creventDai_MemoryOveNusumareru(void);
CREVENTLONG2_API int creventNorthTereia_JiyuichiOve(int event);
CREVENTLONG2_API int creventNorthTereia_NightTozoku(void);
CREVENTLONG2_API int creventNorthTereiaDokutsu_Otoshiana(void);
CREVENTLONG2_API int creventNorthTereiaIseki_Nikki(void);
CREVENTLONG2_API int creventNorthTereiaIseki_Saishinbu(void);
CREVENTLONG2_API int creventNorthTereiaIseki_KirokuPanel(int mode);
CREVENTLONG2_API int creventMarks_LizelAndChocho(void);
CREVENTLONG2_API int creventDai_NisenoOve(void);
CREVENTLONG2_API int creventMarks_LizelEternal(void);

//------------------------------------------------
CREVENTLONG5_API int creventNorthTereia_Xavier(void);
CREVENTLONG5_API int creventDai_ReturnOve(void);

CREVENTLONG6_API int creventZenuren_Moriuni(void);

CREVENTLONG9_API int crevent_AlsiaHashiObachanYubiwa(void);
CREVENTLONG9_API int crevent_TreiaTooLongHappy(void);


//---�K�т���
void eventCallBack_SabitaKen(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

	evFrameWait(500);
	mes.FileMessage("NorthTereia.msg",108);

	critemAddItem(78,1);
	evSet(236,0);
	evSet(237,1);
}

CREVENTPART4_API int creventCheckEvent_Part4(int event,int map,int scene)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;
	eiMapObject *pob = crfieldGetObjectPointer(event);

	CR_BATTLEINFO BatInfo;
	memset(&BatInfo,0,sizeof(BatInfo));

	if(map == 36){
		//---���C�N���[�h
		if(scene == 0){
			if(event == 200 || event == 201){
				//---�t�B�[���h��
				mcDir(SOUTH);
				evMap(10,0,245,193);
			} else if(event == 202){
				if(evGet(136) && !evGet(140)){
					//---�����錾��
					evField(0,1);
					mes.FileMessage("LakeRoad.msg",101);
					evFrameWait(250);
					mcMove(0,1);
					evFrame();
					mcResetEvent();
				} else if(!evGet(71)){
					//---�P���N���A�O��
					evField(0,1);
					mes.FileMessage("LakeRoad.msg",100);
					evFrameWait(250);
					mcMove(0,1);
					evFrame();
					mcResetEvent();
				} else {
					//---�a�P�|�P��
					mcDir(SOUTH);
					evScene(1,4,43);
				}
			} else if(event < 10){
				npTurn(event);
				evField(0,1);
				mes.FileMessage("LakeRoad.msg",event);
				npReturn(event);
			}
		} else if(scene == 1){
			//---�a�P�|�P
			if(event == 200){
				//---�N���X�t�B�[���h��
				mcDir(SOUTH);
				evScene(0,10,10);
			} else if(event == 201){
				//---�a�Q��
				mcDir(SOUTH);
				evScene(2,13,46);
			}
		} else if(scene == 2){
			//---�a�Q
			if(event == 200){
				//---�a�P�|�P��
				mcDir(SOUTH);
				evScene(1,16,2);
			} else if(event == 201){
				//---�a�P�|�Q��
				mcDir(SOUTH);
				evScene(3,23,43);
			}
		} else if(scene == 3){
			//---�a�P�|�Q
			if(event == 200){
				//---�a�Q��
				mcDir(SOUTH);
				evScene(2,15,4);
			} else if(event == 201){
				//---�g���C�A��
				if(!evGet(81)){
					//---�͂��߂Ẵg���C�A�A�h���܂肽���t���b�O
					evSet(80,1);
					evSet(81,1);

					crfieldChangeMap(37,0,1,1);
					mcShow(0);

					npPos(22,58,10);
					npDir(22,WEST);
					npPos(23,59,9);
					npDir(23,WEST);
					npPos(24,58,11);
					npDir(24,SOUTH);
					npPos(25,60,11);
					npDir(25,SOUTH);
					evScene(0,60,11);
					evFrameWait(1000);
					mes.FileMessage("Treia.msg",101);
					evFrameWait(500);

					mcShow(1);
					mcDir(SOUTH);
					npDelete(22);
					npDelete(23);
					npDelete(24);
					npDelete(25);
					evScene(0,58,10);
				} else {
					mcDir(SOUTH);
					evMap(37,0,60,10);
				}
			}
		}
	} else if(map == 37){
		//---�g���C�A
		if(scene == 0){
			//---
			if(200 <= event && event <= 202){
				//---�t�B�[���h��
				if(evGet(80)){
					evField(0,1);
					mes.FileMessage("Treia.msg",102);
					mcMove(0,1);
					evFrame();
					mcResetEvent();
				} else {
					mcDir(SOUTH);
					evMap(10,0,236,159);
				}
			} else if(event == 203){
				//---���C�N���[�h��
				mcDir(SOUTH);
				evMap(36,3,8,4);
			} else if(event == 204){
				//---�h���Q�K��
				mcDir(EAST);
				evScene(1,2,2);
			} else if(event == 0){
				//---�h
				if(evGet(80)){
					//---�C�x���g�h
					return creventTreia_LunarnCrasive();
				} else {
					evYado(64,map,scene);
				}
			} else if(event == 1){
				//---����
				int ShopItem[] = {3,13,52,94,103,110,143,149,258,265,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 2){
				//---����
				int ShopItem[] = {221,226,227,171,172,173,174,175,177,200,195,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 21){
				//---���E�n�}
				evShowWorldMap(236,159);
			} else if(event <= 50){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				if(event == 17
					&& AFTER_KOJINSAI()
					&& evGet(255) == 0){
					//---���i���K��
					return crevent_TreiaTooLongHappy();
				}
				if(event == 17 && evGet(255) == 1){
					mes_scene = 7;
				}

				npTurn(event);
				evField(0,1);
				mes.FileMessage("Treia.msg",event,mes_scene);
				npReturn(event);
			} else if(event == 205){
				//---�^���X�^�{�I
				itemTansu(827,232);
			} else if(event == 206){
				//---�^���X�^�{�I
				itemTansu(828,226);
			} else if(event == 207){
				//---�^���X�^�{�I
				itemTansu(829,227);
			}
		} else if(scene == 1){
			if(event == 200){
				//---�h���P�K��
				mcDir(EAST);
				evScene(0,42,28);
			} else if(event == 201){
				//---�^���X�^�{�I
				itemTansu(830,223);
			}
		}
	} else if(map == 38){
		//---�����R��
		if(scene == 0){
			//---�R�P
			if(200 <= event && event <= 202){
				mcDir(SOUTH);
				evMap(10,0,188,131);
			} else if(203 <= event && event <= 204){
				mcDir(NORTH);
				evScene(1,43,48);
				//---�f�B�U�E���Ȃ�^�f�u���I
				if(!evGet(82)){
					evFrameWait(500);
					mes.FileMessage("CentralMount.msg",100);
					evSet(82,1);
				}
			} else if(event == 0){
				//---��
				itemBox(536,227,event);
			} else if(event == 1){
				//---��
				itemBox(537,224,event);
			}
		} else if(scene == 1){
			//---�R�Q
			if(200 <= event && event <= 201){
				mcDir(SOUTH);
				evScene(0,8,9);
			} else if(202 <= event && event <= 203){
				mcDir(NORTH);
				evScene(2,20,8);
			} else if(204 <= event && event <= 206){
				//---�R�P��
				mcDir(WEST);
				evScene(2,38,24);
			} else if(207 <= event && event <= 208){
				//---�I�C�����C�N��
				if(AFTER_KOJINSAI()){
					//---�~�_�Ռ�
					mcDir(NORTH);
					evScene(6,25,42);
				} else {
					if(!evGet(84)){
						creventOilLake_Yumi();
					} else {
						mcDir(NORTH);
						evScene(3,25,42);
					}
				}
			} else if(event == 209){
				//---To 1
				crfieldChangePlane(1);
			} else if(event == 210){
				//---To 3
				crfieldChangePlane(3);
			} else if(event == 211){
				//---To 1
				crfieldChangePlane(1);
			} else if(event == 212){
				//---To 3
				crfieldChangePlane(3);
			} else if(event == 0){
				//---��
				itemBox(538,222,event);
			}
		} else if(scene == 2){
			//---�R�R
			if(200 <= event && event <= 201){
				mcDir(SOUTH);
				evScene(1,9,8);
			} else if(202 <= event && event <= 204){
				mcDir(EAST);
				evScene(1,10,23);
			}
		} else if(scene == 3){
			//---�I�C�����C�N
			if(200 <= event && event <= 203){
				//---�R�Q��
				if(evGet(83)){
					if(crbaseSelectYesNo("�쑤�܂ňړ����܂����H",64,64)
						== 0){
						mcDir(SOUTH);
						evMap(10,0,188,131);
						return 1;
					}
				}
				mcDir(SOUTH);
				evScene(1,44,9);
			} else if(204 <= event && event <= 206){
				//---�R�S��
				if(evGet(83)){
					if(crbaseSelectYesNo("�k���܂ňړ����܂����H",64,64)
						== 0){
						mcDir(NORTH);
						evMap(10,0,190,109);
						return 1;
					}
				}
				mcDir(NORTH);
				evScene(4,10,41);
			} else if(event == 0){
				npTurn(event);
				evField(0,1);
				mes.FileMessage("CentralMount.msg",event);
				npReturn(event);

				evYado(78,map,scene);
			} else if(event <= 11){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("CentralMount.msg",event,mes_scene);
				npReturn(event);
			}
		} else if(scene == 4){
			//---�R�S
			if(200 <= event && event <= 202){
				//---�I�C�����C�N
				mcDir(SOUTH);
				if(AFTER_KOJINSAI()){
					//---�~�_�Ռ�
					evScene(6,30,10);
				} else {
					evScene(3,30,10);
				}
			} else if(203 <= event && event <= 204){
				//---�R�T��
				mcDir(NORTH);
				evScene(5,16,40);
			}
		} else if(scene == 5){
			//---�R�T
			if(200 <= event && event <= 201){
				//---�R�S��
				mcDir(SOUTH);
				evScene(4,43,9);
			} else if(202 <= event && event <= 203){
				//---�t�B�[���h��
				mcDir(NORTH);
				evMap(10,0,190,109);
				evSet(83,1);//---�����R���˔j�t���b�O
			} else if(event == 0){
				//---��
				itemBox(539,225,event);
			} else if(event == 1){
				//---��
				itemBox(540,223,event);
			}
		} else if(scene == 6){
			//---�I�C�����C�N�E������
			if(200 <= event && event <= 203){
				//---�R�Q��
				if(evGet(83)){
					if(crbaseSelectYesNo("�쑤�܂ňړ����܂����H",64,64)
						== 0){
						mcDir(SOUTH);
						evMap(10,0,188,131);
						return 1;
					}
				}
				mcDir(SOUTH);
				evScene(1,44,9);
			} else if(204 <= event && event <= 206){
				//---�R�S��
				if(evGet(83)){
					if(crbaseSelectYesNo("�k���܂ňړ����܂����H",64,64)
						== 0){
						mcDir(NORTH);
						evMap(10,0,190,109);
						return 1;
					}
				}
				mcDir(NORTH);
				evScene(4,10,41);
			} else if(207 <= event && event <= 208){
				//---������
				{
					eiCell src,bg;
					RECT rect = {0,0,640,480};

					crefectScreenEfect_FadeOut(&rect,500,RGB_MAKE(0,0,0),0);

					src.ReadFile(CR_DATADIR1"OLnoon.acf",CR_DATAFILE1,crdataGetFileMode());
					decode_image(&bg,&src,NULL);
					src.Release();
					bg.Put(ew->lpCell[1],0,0);

					crefectScreenEfect_FadeOut(&rect,500,RGB_MAKE(0,0,0),1);

					CrInput ci;
					eiTime let;

					ci.Get();
					ci.Get();
					let.Reset();
					while(!(ci.IsButton(0) || ci.IsButton(1)
						|| ci.IsDown() || ci.IsUp()
						|| ci.IsLeft() || ci.IsRight())
						&& let.Get() < 2000){
						eiSleep(10);
						ci.Get();
					}

					crefectScreenEfect_FadeOut(&rect,500,RGB_MAKE(0,0,0),0);
				}

				mcDir(WEST);
				crfieldChangeScene(8,46,8);
				ew->lpCell[1]->DrawFillBox(0,0,639,479,ep->ToRGB(CRCOLOR_BLACK));
				evFieldNoFlip(0,1);
				evFadeIn();
			} else if(event == 0){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("CentralMount.msg",event,mes_scene);
				npReturn(event);

				evYado(78,map,scene);
			} else if(event == 17){
				//---�����
				npTurn(event);
				evField(0,1);
				mes.FileMessage("CentralMount.msg",event);
				npReturn(event);

				int ShopItem[] = {122,123,124,161,162,221,222,226,227,-1};
				crshopIntoShop(ShopItem);
			} else if(event <= 11){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("CentralMount.msg",event,mes_scene);
				npReturn(event);
			}
		} else if(scene == 8){
			//---����
			if(200 <= event && event <= 201){
				mcDir(EAST);
				evScene(6,11,25);
			} else if(event == 202){
				mcDir(NORTH);
				evScene(9,8,23);
			} else if(event == 0){
				//---�t�@�X���N���A��ɓ��ꂽ�I
				evField(0,1);
				mes.FileMessage("CentralMount.msg",103);
				evSet(244,1);
				npDelete(0);
				critemAddItem(27,1);
			}
		} else if(scene == 9){
			//---��������
			if(event == 200){
				mcDir(SOUTH);
				evScene(8,18,26);
			} else if(event == 201){
				mcDir(SOUTH);
				evScene(10,11,5);
			}
		} else if(scene == 10){
			//---���������ړ����u
			if(event == 200){
				mcDir(SOUTH);
				evScene(9,8,4);
			} else if(event == 201){
				crmusicFadeOut();
				crsoundPlay(CRSOUND_KIDOU);
				evFadeOut(1000);
				et->Delay2(1200);
				crfieldChangeMap(92,0,1,1);
				crfieldChangeScene(0,4,4);
				evFieldNoFlip(0,1);
				evFadeIn(1000);
			}
		} else if(scene == 11){
			//---�ʂ̏ꏊ
			if(event == 200){
				//---�t�B�[���h��
				mcDir(SOUTH);
				evMap(10,0,168,127);
			} else if(event == 201){
				//---�ʂ̏ꏊ�Q��
				mcDir(SOUTH);
				evScene(12,3,3);
			} else if(202 <= event && event <= 207 && !evGet(243)
				&& !evGet(230)){
				//---�͂��߂āI
				evField(0,1);
				mes.FileMessage("CentralMount.msg",102);
				evSet(243,1);
			}
		} else if(scene == 12){
			//---�ʂ̏ꏊ�Q
			if(event == 200){
				//---�ʂ̏ꏊ��
				mcDir(SOUTH);
				evScene(11,12,4);
			} else if(event == 201){
				if(evGet(242)){
					//---�C���[�f�B�A��
					crmusicFadeOut();
					crsoundPlay(CRSOUND_KIDOU);
					evFadeOut(1000);
					et->Delay2(1200);
					crfieldChangeMap(94,2,1,1);
					crfieldChangeScene(2,3,8);
					evFieldNoFlip(0,1);
					evFadeIn(1000);
				} else {
					evField(0,1);
					mes.FileMessage("Illeadia.msg",22);
				}
			}
		}
	} else if(map == 39){
		//---�m�[�X�e���A
		if(scene == 0){
			if(200 <= event && event <= 205){
				//---�t�B�[���h��
				if(evGet(104) == 3 && !evGet(105)){
					//---�^�_�h���s�ցE�f�B�U��
					evField(0,1);
					mes.FileMessage("NorthTereia.msg",103);
					mcMove(0,-1);
					evFrame();
					mcResetEvent();
					return 1;
				} else if(evGet(105) && !evGet(106)){
					//---���̓��A�ւf��
					evField(0,1);
					mes.FileMessage("NorthTereia.msg",105);
					evField(0,1);
				}
				mcDir(SOUTH);
				evMap(10,0,202,94);
			} else if((event == 213 || event == 214)
				&& evGet(114) && !evGet(116)
				&& !evGet(117)){
				//---�c���}�[�N�X�֍s��
				if(npGet(9)->yGet() == 48){
					npMove(9,0,1);
				}
				mcMove(0,-1);
				evFrame();

				for(a = 0;a < (event == 213 ? 2 : 1);a ++){
					mcMove(1,0);
					evFrame();
				}
				evFrameWait(250);
				mcDir(EAST);
				evFrameWait(250);
				mes.OpenMessage("NorthTereia.msg",106);
				mes.ReadDraw();
				evFrameWait(250);

				//---
				npPos(50,41,48);
				npDir(50,WEST);
				npPos(41,42,48);
				npDir(41,WEST);
				for(a = 0;a < 7;a ++){
					npMove(50,-1,0);
					npMove(41,-1,0);
					evFrame();
				}
				mes.ReadDraw(6);
				evFrameWait(250);
				//---��l�s��
				for(a = 0;a < 16;a ++){
					if(a < 1)
						npMove(50,0,1);
					else if(a < 4)
						npMove(50,-1,0);
					else
						npMove(50,0,1);

					if(a < 1)
						npMove(41,-1,0);
					else if(a < 2)
						npMove(41,0,1);
					else if(a < 5)
						npMove(41,-1,0);
					else
						npMove(41,0,1);

					if(a == 2)
						mcDir(SOUTH);

					evFrame();
				}

				mes.ReadDraw(2);
				npPos(41,0,0);
				npPos(50,0,0);
				npShow(41,0);
				npShow(50,0);
				mes.CloseMessage();
				evSet(116,1);

			} else if((event == 213 || event == 214)
				&& evGet(104) == 1){
				//---������ɂē����Ƃ̉�b
				evFrameWait(100);
				npDir(41,WEST);
				evFrameWait(250);

				for(a = 0;a < 2;a ++){
					npMove(41,-1,0);
					evFrame();
					if(npGet(41)->xGet() == ef->xGet())
						break;
				}
				evFrameWait(250);
				npDir(41,SOUTH);
				evFrameWait(250);
				mes.OpenMessage("NorthTereia.msg",101);
				mes.ReadDraw(3);
				evFrameWait(250);
				npDir(41,EAST);
				evFrameWait(250);
				for(a = 0;a < 15;a ++){
					npMove(41,1,0);
					evFrame();
				}
				npPos(41,0,0);
				npShow(a,0);
				mes.ReadDraw(2);
				mes.CloseMessage();

				npPos(42,36,22);
				npDir(42,SOUTH);
				evSet(104,2);
			} else if((215 <= event && event <= 228)
				&& evGet(104) == 2){
				//---���R�s�ŃI�[�u���I�I
				return creventNorthTereia_JiyuichiOve(event);
			} else if(event == 209){
				//---�T���B�A�[����
				mcDir(NORTH);
				evScene(2,9,9);
			} else if(event == 208){
				//---�h��
				mcDir(SOUTH);
				evScene(1,2,2);
			} else if(event == 206){
				//---�n�����P
				mcDir(SOUTH);
				evScene(3,19,16);
			} else if(event == 207){
				//---�n�����Q
				mcDir(SOUTH);
				evScene(3,4,4);
			} else if(event == 210){
				//---�c��
				mcDir(SOUTH);
				evScene(4,4,3);

			} else if(event == 51){
				//---���f�B�A���g�w�����I
				npTurn(event);
				evField(0,1);
				int scene = 1;
				if(evGet(205))
					scene = 5;

				mes.FileMessage("NorthTereia.msg",event,scene);
				evField(0,1);
				if(!evGet(205)){
					if(crbaseSelectYesNo("�����Ă݂܂����H",64,64) == 0){
						evField(0,1);
						if(crbaseGetMoney() >= 12000){
							evSet(205,1);
							mes.FileMessage("NorthTereia.msg",event,2);
							critemAddItem(250,1);
							crbaseAddMoney(-12000);
						} else {
							mes.FileMessage("NorthTereia.msg",event,4);
						}
					} else {
						evField(0,1);
						mes.FileMessage("NorthTereia.msg",event,3);
					}
				}
				npReturn(event);
			} else if(event == 4){
				//---�h
				if(evGet(104) == 3 && !evGet(105)){
					//---��̏P��
					return creventNorthTereia_NightTozoku();
				} else {
					evYado(130,map,scene);
				}
			} else if(event == 6){
				//---����
				int ShopItem[] = {14,32,41,53,95,104,111,144,150,259,266,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 7){
				//---����
				int ShopItem[] = {221,222,226,227,171,172,173,174,177,201,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 33){
				//---���E�n�}
				evShowWorldMap(202,94);
			} else if(event <= 50){
				npTurn(event);
				evField(0,1);

				int ms = 1;

				if(AFTER_KOJINSAI())
					ms = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					ms = MESSAGE_YUMI;
				else if(evGet(106))
					ms = 3;
				else if(evGet(104) == 2)
					ms = 2;

				mes.FileMessage("NorthTereia.msg",event,ms);

				if(38 <= event && event <= 42){
					//---���R�s
					int Jiyuichi[][8][12] = {
						{
							//---�񕜁A�A�N�Z�T��
							{221,222,174,-1},
							{222,226,227,-1},
							{221,222,226,227,175,177,-1},
							{222,227,181,182,-1},//���̂��낱�A�����̊p

							{221,222,197,185,273,-1},//��ȃl�b�N���X
							{222,274,-1},//��m�̘r�ցA
							{178,184,182,-1},//�G���W�F���o���h�A�����̊p�A�v���X�G�N�X�e���_�[
							{222,228,199,-1},//���P�V�X�̐��t�A���E��
						},
						{
							//---����
							{1,14,-1},
							{10,11,12,13,14,-1},
							{50,3,2,-1},
							{10,12,13,-1},

							{4,51,-1},//�}�C�����[�X
							{3,21,-1},//�X�g�[���\�[�h
							{4,21,112,-1},//�}�C�����[�X���X�g�[���\�[�h�A�A�N�A�}�������[�u
							{4,15,61,-1}//�f���v���P�C�^�[�A�T�u�}�V���K��
						},
						{
							//---�h��
							{91,94,102,-1},
							{111,102,-1},
							{100,101,102,103,104,-1},
							{158,158,158,158, 158,158,158,158,-1},

							{260,151,-1},//�A�N�e�B�u�V�[���h
							{265,-1},
							{120,159,-1},//�E�B�U�[�h�X�[�c�A�_�����΂̏��E�����
							{106,146,-1}//�c�[���A�A�C�e��
						}
					};
					evField(0,1);

					if(evGet(236)){
						//---���т���
						Jiyuichi[event - 38][evGet(85 + event - 38)][0] = 240;
						crshopIntoShop(Jiyuichi[event - 38][evGet(85 + event - 38)],0,eventCallBack_SabitaKen);
					} else {
						crshopIntoShop(Jiyuichi[event - 38][evGet(85 + event - 38)],0);
					}
				}
				npReturn(event);
			} else if(event == 211){
				//---�^���X�^�{�I
				itemTansu(831,227);
			} else if(event == 212){
				//---�^���X�^�{�I
				itemTansu(832,242);
			} else if((event == 229 || event == 230)
				&& (!evGet(180) && AFTER_YUMI())){
				//---�T���B�A�[�̗��A��
				return creventNorthTereia_Xavier();
			}
		} else if(scene == 1){
			//---�h���Q�K
			if(event == 200){
				//---�P�K��
				mcDir(SOUTH);
				evScene(0,5,36);
			} else if(event == 201){
				//---�^���X�^�{�I
				itemTansu(833,223);
			}
		} else if(scene == 2){
			//---�T���B�A�[����
			if(event == 200){
				//---�P�K��
				mcDir(SOUTH);
				evScene(0,13,28);
			} else if(event == 201){
				//---�^���X�^�{�I
				itemTansu(834,205);
			}
		} else if(scene == 3){
			//---�n����
			if(event == 200){
				//---�n���
				mcDir(SOUTH);
				evScene(0,38,40);
			} else if(event == 201){
				//---�n���
				mcDir(SOUTH);
				evScene(0,30,33);
			} else if(event <= 10){
				npTurn(event);
				evField(0,1);
				mes.FileMessage("NorthTereia.msg",event + 70);
				npReturn(event);
			}
		} else if(scene == 4){
			//---�c��
			if(event == 200){
				//---�n���
				mcDir(SOUTH);
				evScene(0,22,5);
			} else if(event <= 10){
				npTurn(event);
				evField(0,1);

				int ms = 1;

				if(AFTER_KOJINSAI())
					ms = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					ms = MESSAGE_YUMI;
				else if(evGet(106))
					ms = 3;

				mes.FileMessage("NorthTereia.msg",event + 60,ms);
				npReturn(event);
			} else if(event == 201){
				//---�^���X�^�{�I
				itemTansu(835,222);
			}
		}
	} else if(map == 40){
		//---�_�C
		if(scene == 0){
			if(200 <= event && event <= 202){
				//---�t�B�[���h��
				if(evGet(117) && !evGet(120)){
					//---������ɍs����
					evField(0,1);
					mes.FileMessage("Dai.msg",101);
					mcMove(0,-1);
					evFrame();
					mcResetEvent();
				} else {
					mcDir(SOUTH);
					evMap(10,0,245,110);
				}
			} else if(event == 203){
				//---�_�C�̐X��
				if(evGet(117) && !evGet(120)){
					//---������ɍs����
					evField(0,1);
					mes.FileMessage("Dai.msg",102);
					mcMove(0,1);
					evFrame();
					mcResetEvent();
				} else {
					mcDir(NORTH);
					evMap(42,0,39,57);
				}
			} else if(event == 204){
				//---�����Q�K
				if(evGet(117) && !evGet(120)){
					//---�U��̃I�[�u
					return creventDai_NisenoOve();
				} else {
					mcDir(SOUTH);
					evScene(1,12,3);
				}
			} else if(event == 0){
				//---�h
				if(evGet(117) && !evGet(120)){
					//---������ɍs����
					evField(0,1);
					mes.FileMessage("Dai.msg",101);
				} else {
					evYado(27,map,scene);
				}
			} else if(event == 1){
				//---����
				int ShopItem[] = {14,32,95,104,111,144,221,222,226,227,-1};
				crshopIntoShop(ShopItem);
			} else if(event <= 20){
				npTurn(event);
				evField(0,1);
				if(!evGet(97) && event == 14){
					//---�Ƃ̔Ԑl
					evSet(97,1);

					mcShow(0);
					npPos(16,21,28);
					npDir(16,NORTH);
					npPos(17,20,28);
					npDir(17,NORTH);
					npPos(18,21,29);
					npDir(18,NORTH);
					npPos(19,22,29);
					npDir(19,NORTH);
					evScene(0,21,30);
					
					evFrameWait(250);

					mes.FileMessage("Dai.msg",event,2);
					evFrameWait(250);

					npDelete(16);
					npDelete(17);
					npDelete(18);
					npDelete(19);

					mcShow(1);
					mcDir(SOUTH);
					evScene(0,21,28);

				} else if(evGet(97) && event == 13){
					//---�X�̓�����̐l�ǂ�
					mes.FileMessage("Dai.msg",event,2);
					if(!evGet(103)){
						evFrameWait(250);
						if(npGet(event)->xGet() <= ef->xGet()){
							//---���ɓ���
							npMove(event,-1,0);
						} else {
							npMove(event,1,0);
						}
						evSet(103,1);
						evFrame();
					}
				} else {
					int mes_scene = 1;

					if(AFTER_KOJINSAI())
						mes_scene = MESSAGE_KOJINSAI;
					else if(AFTER_YUMI())
						mes_scene = MESSAGE_YUMI;
					else if(evGet(120))
						mes_scene = 4;
					else if(evGet(99))
						mes_scene = 3;
					mes.FileMessage("Dai.msg",event,mes_scene);
				}
				npReturn(event);
			} else if(event == 205){
				//---�^���X�^�{�I
				itemTansu(836,116);
			} else if(event == 206){
				//---�^���X�^�{�I
				itemTansu(837,222);
			}
		} else if(scene == 1){
			//---�����Q�K
			if(event == 200){
				//---�P�K��
				mcDir(SOUTH);
				evScene(0,25,18);
			} else if(event == 202 && AFTER_YUMI()
				&& !evGet(192) && evGet(191) && critemGetItemCount(215)){
				return creventDai_ReturnOve();
			} else if(event <= 10){
				int mes_scene = 1;

				npTurn(event);
				evField(0,1);


				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;
				else if(evGet(120))
					mes_scene = 4;
				mes.FileMessage("Dai.msg",event + 50,mes_scene);
				npReturn(event);
			} else if(event == 201){
				//---�^���X�^�{�I
				itemTansu(838,213);
			}
		}
	}

	return 1;
}

CREVENTPART4_API int creventCheckEvent_Part4_2(int event,int map,int scene)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;
	eiMapObject *pob = crfieldGetObjectPointer(event);

	CR_BATTLEINFO BatInfo;
	memset(&BatInfo,0,sizeof(BatInfo));

	if(map == 41){
		//---�}�[�N�X
		if(scene == 0){
			if(200 <= event && event <= 202){
				if(evGet(119) && !evGet(117)){
					//---�����ɉ�܂��傤��
					evField(0,1);
					mes.FileMessage("Marks.msg",103);
					mcMove(0,1);
					evFrame();
					mcResetEvent();
				} else {
					mcDir(SOUTH);
					evMap(10,0,163,71);
				}
			} else if(207 <= event && event <= 208){
				//---�_�����΍̐Ώ�
				mcDir(SOUTH);
				evMap(45,0,57,25);
			} else if(event == 204){
				//---�����ƂQ�K
				mcDir(SOUTH);
				evScene(2,2,2);
			} else if(event == 205){
				//---�h���Q�K
				mcDir(NORTH);
				evScene(1,2,12);
			} else if(event == 0){
				//---�h
				evYado(120,map,scene);
			} else if(event == 1){
				//---����
				int ShopItem[] = {14,32,41,53,95,104,111,144,150,158,259,266,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 2){
				//---����
				int ShopItem[] = {221,222,226,227,171,172,173,174,177,201,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 206){
				//---�c��֓���Ȃ�
				if(!evGet(120)){
					npDir(15,NORTH);
					evField(0,1);

					if(evGet(119) && !evGet(117)){
						//---���C�[���c��ւ͂���̂��a��
						return creventMarks_LizelAndChocho();
					} else {
						mes.FileMessage("Marks.msg",100);
						mcMove(-1,0);
						evFrame();
						mcResetEvent();
						npDir(15,WEST);
					}
				}
			} else if(event == 24){
				//---���E�n�}
				evShowWorldMap(163,71);
			} else if(event <= 47){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;
				else if(evGet(118))
					mes_scene = 3;
				else if(evGet(120) && !evGet(118))
					//---���C�[����������
					mes_scene = 2;

				if(event == 28)
					crmusicPlay(CRMUSIC_LIZEL);

				npTurn(event);
				evField(0,1);
				mes.FileMessage("Marks.msg",event,mes_scene);
				npReturn(event);
			} else if(event == 209){
				//---�^���X�^�{�I
				itemTansu(839,259);
			} else if(event == 210){
				//---�^���X�^�{�I
				itemTansu(840,173);
			}
		} else if(scene == 1){
			//---�h���Q�K�i����j
			if(event == 200){
				//---�P�K��
				mcDir(NORTH);
				evScene(0,30,15);
			} else if(event <= 20){
				int mes_scene = 1;

				npTurn(event);
				evField(0,1);

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;
				else if(evGet(118))
					mes_scene = 3;
				mes.FileMessage("Marks.msg",event + 50,mes_scene);
				npReturn(event);
			}
		} else if(scene == 2){
			//---�����ƂQ�K
			if(event == 200){
				//---�P�K��
				mcDir(NORTH);
				evScene(0,36,32);
			} else if(event == 201){
				//---�^���X�^�{�I
				itemTansu(841,223);
			} else if(event == 202){
				//---�^���X�^�{�I
				itemTansu(842,226);
			} else if(event <= 20){
				int mes_scene = 1;

				npTurn(event);
				evField(0,1);

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;
				else if(evGet(118))
					mes_scene = 3;
				mes.FileMessage("Marks.msg",event + 60,mes_scene);
				npReturn(event);
			}
		}
	} else if(map == 42){
		//---�_�C�̐X
		if(scene == 0){
			//---�X�P
			if(event == 200){
				//---����
				mcDir(SOUTH);
				evMap(40,0,33,9);

				if(!evGet(99) && evGet(98) == 2){
					//---�I�[�u���܂��I�I
					return creventDai_MemoryOveNusumareru();
				}
			} else if(event == 201){
				mcDir(NORTH);
				evScene(1,18,28);
			}
		} else if(scene == 1){
			//---�X�Q
			if(event == 200){
				mcDir(SOUTH);
				evScene(0,26,8);
			} else if(event == 201){
				//---�f�c�[�̓��A
				mcDir(SOUTH);
				evMap(43,0,13,3);

				if(evGet(98) == 0){
					evFrameWait(500);
					mes.FileMessage("Detoe.msg",100);
					evSet(98,1);
				}
			}
		}
	} else if(map == 43){
		//---�f�c�[�̓��A
		if(scene == 0){
			if(event == 200){
				//---�_�C�̐X��
				mcDir(SOUTH);
				evMap(42,1,17,12);
			} else if((event == 201 || event == 202)
				&& evGet(98) < 2){
				//---���@����

				mcShow(0);
				npPos(0,10,20);
				npDir(0,WEST);
				npPos(1,9,19);
				npDir(1,SOUTH);
				npPos(2,10,21);
				npDir(2,WEST);
				npPos(3,9,21);
				npDir(3,NORTH);
				evScene(0,10,21);

				evFrameWait(1000);
//				mcMove(-1,0);
//				evFrame();
//				evFrameWait(500);

				mes.OpenMessage("Detoe.msg",101);
				mes.ReadDraw();
				evFrameWait(500);
//				mcMove(-1,0);
//				evFrame();
				evFrameWait(500);
				mes.ReadDraw(3);
				mes.CloseMessage();
				evFrameWait(500);

				mcShow(1);
				mcDir(SOUTH);
				npDelete(0);
				npDelete(1);
				npDelete(2);
				npDelete(3);
				evScene(0,10,20);

				evSet(98,2);
			}
		}
	} else if(map == 44){
		//---�m�[�X�e���A�̓��A
		if(scene == 0){
			if(event == 200){
				//---�t�B�[���h��
				mcDir(SOUTH);
				evMap(10,0,220,93);
			} else if(event == 201){
				//---�a�Q��
				mcDir(SOUTH);
				evScene(1,27,18);
			} else if(event == 0){
				//--�y��
				evField(0,1);
				mes.FileMessage("NtDangeon.msg",event);
			} else if(event == 1){
				//---��
				itemBox(541,224,event);
			} else if(event == 2){
				//---��
				itemBox(542,227,event);
			}
		} else if(scene == 1){
			//---�a�Q
			if(event == 200){
				//---�a�P��
				mcDir(SOUTH);
				evScene(0,2,36);
			} else if(event == 201){
				//---�a�R
				mcDir(SOUTH);
				evScene(2,12,28);
			} else if(event == 0){
				//---��
				itemBox(543,177,event);
			}
		} else if(scene == 2){
			//---�a�R
			if(event == 200){
				//---�a�Q��
				mcDir(SOUTH);
				evScene(1,21,38);
			} else if(event == 201){
				//---�a�S��
				mcDir(SOUTH);
				evScene(3,9,9);
			} else if(event == 202 && !evGet(106)){
				//---���Ƃ����I�I
				return creventNorthTereiaDokutsu_Otoshiana();
			} else if(event == 0){
				//---��
				itemBox(544,223,event);
			}
		} else if(scene == 3){
			//---�a�S
			if(event == 200){
				//---�a�R��
				mcDir(SOUTH);
				evScene(2,7,5);
			} else if(event == 201){
				//---�a�T��
				mcDir(SOUTH);
				evScene(4,8,26);
			}
		} else if(scene == 4){
			//---�a�T
			if(event == 200){
				//---�a�S��
				mcDir(SOUTH);
				evScene(3,9,35);
			}
		}
	} else if(map == 45){
		//---�_�����΍̌@��
		if(scene == 0){
			if(200 <= event && event <= 201){
				//---�}�[�N�X��
				mcDir(NORTH);
				evMap(41,0,17,46);
			} else if(202 <= event && event <= 203
				&& evGet(120) && !evGet(118)){
				//---���C�[���̉ߋ�
				return creventMarks_LizelEternal();
			} else if(event <= 30){
				int mes_scene = 1;

				if(evGet(120) && !evGet(118))
					mes_scene = 2;
				npTurn(event);
				evField(0,1);
				mes.FileMessage("MarksDawang.msg",event,mes_scene);
				npReturn(event);
			}
		}
	}
	return 1;
}

CREVENTPART4_API int creventCheckEvent_Part4_3(int event,int map,int scene)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;
	eiMapObject *pob = crfieldGetObjectPointer(event);

	CR_BATTLEINFO BatInfo;
	memset(&BatInfo,0,sizeof(BatInfo));

	if(map == 46){
		//---�m�[�X�e���A�̈��
		if(scene == 0){
			if(event == 200){
				//---�t�B�[���h��
				mcDir(SOUTH);
				evMap(10,0,166,91);
			} else if(202 <= event && event <= 206
				&& evGet(100) == 0 && !evGet(106)){
				{
					//---���_�̂̐�
					evFrameWait(250);
					mes.OpenMessage("NorthTereiaIseki.msg",100);
					mes.ReadDraw();
					evFrameWait(250);
					mcDir(WEST);
					evFrameWait(250);
					mcDir(SOUTH);
					evFrameWait(250);
					mcDir(WEST);
					evFrameWait(250);
					mcDir(NORTH);
					evFrameWait(250);
					mcDir(EAST);
					evFrameWait(250);
					mcDir(SOUTH);
					evFrameWait(250);
					mes.ReadDraw(2);

					evFrameWait(1000);
					mes.ReadDraw();
					evFrameWait(500);
					mes.ReadDraw();
					evFrameWait(500);

					evSet(100,1);
				}
			} else if(202 <= event && event <= 206
				&& evGet(106)){
				if(!evGet(109)){
					//---���_�̂𕕂���
					evFrameWait(250);
					mes.OpenMessage("NorthTereiaIseki.msg",103);
					mes.ReadDraw();
					evFrameWait(250);
					mes.ReadDraw();

					//---��
					crmusicFadeOut();
					evFrameWait(1000);
					crsoundPlay(CRSOUND_SUZU);
					evFrameWait(4000);
					crsoundPlay(CRSOUND_SUZU);
					evFrameWait(4500);
					crmusicFadeIn();
					evFrameWait(1000);
					mes.ReadDraw();
					evFrameWait(1000);
					mes.ReadDraw();

					evFrameWait(1000);
					mes.ReadDraw(2);

					mes.CloseMessage();
					evSet(109,1);
				}
			} else if(event == 201){
				if(evGet(106)){
					//---�����P�e��
					mcDir(NORTH);
					evScene(1,29,46);
				} else {
					//---�܂��܂������
					mcDir(SOUTH);
					evScene(0,18,20);
					evFrameWait(500);
					if(!evGet(101)){
						//---�_���������E�E�E
						evFrameWait(250);
						mes.FileMessage("NorthTereiaIseki.msg",101);
						evSet(101,1);
					} else {
						mes.FileMessage("NorthTereiaIseki.msg",102);
					}
				}
			}
		} else if(scene == 1){
			//---�����P�e
			if(200 <= event && event <= 202){
				if(evGet(112) && !evGet(114)){
					//---�m�[�X�e���A�̈�ՃN���A�I
					//---���i���̐S
					mcShow(0);
					crmusicFadeOut();
					evScene(5,10,10);
					evFrameWait(1500);
					crmusicStop();

					mes.OpenMessage("NorthTereiaIseki.msg",116);
					mes.ReadDraw();
					evFrameWait(1000);
					mes.ReadDraw();
					evFrameWait(1250);
					mes.CloseMessage();

					evSet(114,1);
					mcShow(1);
					mcDir(SOUTH);
					evMap(10,0,166,91);
				} else {
					//---�O��
					mcDir(SOUTH);
					evScene(0,18,20);
				}
			} else if(event == 203){
				//---�Q�e��
				mcDir(SOUTH);
				crfieldChangeScene(2,25,33);
				em->Put(25,26,2,96);
				evScene(2,25,33);
				evSet(108,0);
			} else if(event == 204){
				//---�Q�e��
				mcDir(SOUTH);
				crfieldChangeScene(2,25,23);
				em->Put(25,26,2,96);
				evScene(2,25,23);
			} else if(event == 205){
				//---�a�P��
				if(!evGet(110)){
					return creventNorthTereiaIseki_Nikki();
				} else {
					mcDir(SOUTH);
					evScene(3,12,4);
				}
			} else if(event == 206 && evGet(112)){
				//---�a�Q�փG���x�[�^�[
				mcDir(SOUTH);
				evScene(4,7,25);
			} else if(event == 3){
				//---���莆
				evField(0,1);
				mes.FileMessage("NorthTereiaIseki.msg",4);
			} else if(event == 0){
				//---��
				itemBox(545,224,event);
			} else if(event == 1){
				//---��
				itemBox(546,183,event);
			} else if(event == 2){
				//---��
				itemBox(547,223,event);
			}
		} else if(scene == 2){
			//---�����Q�e
			if(event == 200){
				//---�P�e��
				mcDir(SOUTH);
				evScene(1,29,34);
				evSet(108,0);
			} else if(event == 201){
				//---�P�e��
				mcDir(SOUTH);
				evScene(1,29,24);
			} else if(event == 2){
				//---���莆
				evField(0,1);
				mes.FileMessage("NorthTereiaIseki.msg",2);
			} else if(event == 202){
				//---��
				if(evGet(108)){
					if(em->Get(25,26,2) == 96){
						evField(0,1);
						mes.FileMessage("NorthTereiaIseki.msg",3);
					}
				} else {
					crsoundPlay(CRSOUND_DOOR);
					em->Put(25,26,2,1024);
				}
			} else if(203 <= event && event <= 217){
				//---�낤�����̑O��ʂ����I
				evSet(108,1);
			} else if(event == 218){
				//---���Z�b�g
				evSet(108,0);
			} else if(event == 0){
				//---��
				itemBox(548,46,event);
			} else if(event == 1){
				//---��
				itemBox(549,227,event);
			}
		} else if(scene == 3){
			//---�a�P
			if(event == 200){
				//---�P�e��
				mcDir(SOUTH);
				evScene(1,25,12);
			} else if(event == 201){
				//---�a�Q��
					mcDir(SOUTH);
					evScene(4,10,3);
			} else if(event == 0){
				//---��
				itemBox(550,225,event);
			}
		} else if(scene == 4){
			//---�a�Q
			if(event == 200){
				//---�a�P��
				mcDir(SOUTH);
				evScene(3,5,23);
			} else if(event == 205){
				//---�P�e�փG���x�[�^�[
				mcDir(SOUTH);
				evScene(1,29,39);
			} else if((event == 201 || event == 202)
				&& !evGet(111)){
				//---���_�̂̒���
				evField(0,1);
				evFrameWait(500);
				mes.OpenMessage("NorthTereiaIseki.msg",105);
				mes.ReadDraw(2);
				evFrameWait(500);
				mes.ReadDraw(2);
				evFrameWait(1000);
				mes.ReadDraw();
				evFrameWait(1000);
				mes.ReadDraw();
				mes.CloseMessage();

				evSet(111,1);
			} else if((event == 203 || event == 204)
				&& !evGet(112)){
				return creventNorthTereiaIseki_Saishinbu();
			} else if(event == 4){
				evField(0,1);
				mes.FileMessage("NorthTereiaIseki.msg",5);
			} else if(event == 5){
				//---�p�l��
				crsoundPlay(CRSOUND_MASINBTN);
				evFrameWait(500);
				crsoundPlay(CRSOUND_KIDOU);
				evFrameWait(500);
				em->Put(7,20,2,108);
				creventNorthTereiaIseki_KirokuPanel(0);
			}
		}
	} else if(map == 47){
		//---��
		if(scene == 0){
			if(200 <= event && event <= 204){
				mcDir(EAST);
				evMap(10,0,203,48);
			} else if(205 <= event && event <= 209){
				mcDir(WEST);
				evMap(10,0,199,48);
			} else if(210 <= event && event <= 212
				&& !evGet(118)){
				//---����n��Ȃ��I�I
				if(!evGet(102)){
					evField(0,1);
					mes.OpenMessage("EpBldg.msg",100);
					mes.ReadDraw();
					evFrameWait(250);
					mcDir(NORTH);
					evFrameWait(250);
					mes.ReadDraw(7);
					mes.CloseMessage();
					evSet(102,1);
				} else {
					evField(0,1);
					mes.FileMessage("EpBldg.msg",0);
				}

				evField(0,1);
				mcMove(-1,0);
				evFrame();
				mcResetEvent();
			} else if(213 <= event && event <= 217
				&& !evGet(239)){
				//---���˂������̎w�ւ�T���I�I
				return crevent_AlsiaHashiObachanYubiwa();
			} else if(event <= 10){
				int mes_scene = 1;

				if(AFTER_KOJINSAI())
					mes_scene = MESSAGE_KOJINSAI;
				else if(AFTER_YUMI())
					mes_scene = MESSAGE_YUMI;
				else if(evGet(118))
					mes_scene = 2;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("EpBldg.msg",event,mes_scene);
				npReturn(event);
			}
		}
	} else if(map == 49){
		//---�S�E�A
		if(scene == 0){
			if(200 <= event && event <= 202){
				//---�t�B�[���h��
				mcDir(SOUTH);
				evMap(10,0,290,144);
			} else if(event == 203){
				//---�P�e��
				mcDir(NORTH);
				evScene(1,11,17);
			} else if(event <= 2){
				npTurn(event);
				evField(0,1);
				int mes_scene = 1;
				if(evGet(212))
					mes_scene = 5;

				mes.FileMessage("Zenuren.msg",event + 30,mes_scene);
				npReturn(event);
			}
		} else if(scene == 1){
			if(event == 200){
				//---�O��
				mcDir(SOUTH);
				evScene(0,12,15);
			} else if(event == 201){
				//---�Q�e��
				mcDir(SOUTH);
				evScene(2,11,12);
			} else if(event <= 10){
				if(event != 1)
					npTurn(event);
				evField(0,1);

				int mes_scene = 1;
				if(evGet(212))
					mes_scene = 5;

				mes.FileMessage("Zenuren.msg",event,mes_scene);
				if(event != 1)
					npReturn(event);
			} else if(event == 202){
				//---�^���X�^�{�I
				itemTansu(843,232);
			} else if(event == 203){
				//---�^���X�^�{�I
				itemTansu(844,232);
			}
		} else if(scene == 2){
			if(event == 200){
				//---�P�e��
				mcDir(SOUTH);
				evScene(1,19,16);
			} else if(event <= 10){
				npTurn(event);
				evField(0,1);

				if(event == 0 && !evGet(212)
					&& critemGetItemCount(233) >= 1){
					//---�����E�j����
					return creventZenuren_Moriuni();
				} else {

					int mes_scene = 1;
					if(evGet(212))
						mes_scene = 5;

					mes.FileMessage("Zenuren.msg",event + 20,mes_scene);
				}
				npReturn(event);
			} else if(event == 201){
				//---�^���X�^�{�I
				itemTansu(845,232);
			} else if(event == 202){
				//---�^���X�^�{�I
				itemTansu(0,206);
				if(evGet(107) == 0){
					//---�`���̃E�j�O�b�Y
					evFrameWait(250);
					npDir(0,NORTH);
					evFrameWait(250);

					mes.OpenMessage("Zenuren.msg",100);
					mes.ReadDraw();
					evFrameWait(250);
					mcDir(WEST);
					evFrameWait(250);
					mcDir(SOUTH);
					evFrameWait(250);

					mes.ReadDraw(7);

					evSet(107,1);
				}
			} else if(event == 203){
				//---�^���X�^�{�I
				itemTansu(846,232);
			} else if(event == 204){
				//---�^���X�^�{�I
				itemTansu(847,235);
			} else if(event == 205){
				//---�^���X�^�{�I
				itemTansu(848,232);
			}
		}
	} else if(map == 50){
		//---�O���E���h�V�b�v�D������
		if(scene == 0){
			if(200 <= event && event <= 201){
				//---�t�B�[���h��
				mcDir(SOUTH);
				evMap(10,0,196,87);
			} else if(event == 202){
				//---����Ȃ�
				npTurn(0);
				evField(0,1);

				mes.FileMessage("NTGS.msg",0);

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

				if(event == 2 && !evGet(115)){
					mes.FileMessage("NTGS.msg",4);
					evSet(115,1);
				} else {
					mes.FileMessage("NTGS.msg",event,mes_scene);
				}
				npReturn(event);
			}
		}
	}

	return 1;
}
