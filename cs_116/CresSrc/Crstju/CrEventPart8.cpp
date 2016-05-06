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
		//---�����̈��
		if(scene == 0){
			if(200 <= event && event <= 315){
				//---�t�B�[���h��
				mcDir(SOUTH);
				evMap(10,0,97,75);
			} else if(event == 323 && evGet(209)){
				//---�암��ጴ�N���A��Ȃ�A�����
				mcDir(SOUTH);
				evScene(1,24,2);
			}
		} else if(scene == 1){
			//---�a�P
			if(event == 200){
				//---�n���
				if(!evGet(218)){
					//---�����̈�Ղ��N���A���ĂȂ��Əo���Ȃ�
					evField(0,1);
					mes.FileMessage("RyusanoIseki.msg",103);
				} else {
					mcDir(SOUTH);
					evScene(0,18,12);
				}
			} else if(event == 201){
				//---�a�Q��
				mcDir(SOUTH);
				evScene(2,15,2);
			}
		} else if(scene == 2){
			//---�a�Q
			if(event == 200){
				//---�a�P��
				mcDir(SOUTH);
				evScene(1,17,12);
			} else if(event == 201){
				//---�a�R��
				mcDir(SOUTH);
				evScene(3,21,45);
			} else if(202 <= event && event <= 204
				&& !evGet(214)){
				return creventRyusa_Koegasuru();
			}
		} else if(scene == 3){
			//---�a�R
			if(event == 200){
				//---�a�Q��
				mcDir(SOUTH);
				evScene(2,15,31);
			} else if(event == 201){
				//---�a�S��
				mcDir(SOUTH);
				if(evGet(217) == 1 && evGet(218) == 0){
					//---�~�_�ՑO
					crmusicPlay(CRMUSIC_DANGEON2);
				}
				evScene(4,26,21);
			} else if(event == 202 && !evGet(215)){
				//---�K�[�[���~�o�I
				return creventRyusa_Gazell();
			} else if(event == 202 && evGet(215) && evGet(217) && !evGet(218)){
				//---�~�_�Ղ�
				npTurn(6);
				evField(0,1);
				mes.FileMessage("RyusanoIseki.msg",5,1);
				evFrameWait(100);
				if(crbaseSelectYesNo("�~�_�Ղ֍s���܂����H",64,64) == 0){
					//---�~�_�ՂցI
					return creventGotoKojinsai();
				} else {
					evFrameWait(100);
					mcMove(0,-1);
					evFrame();
					mcResetEvent();
				}

			} else if(event == 27){
				//---����
				int ShopItem[] = {6,18,35,45,57,99,108,115,148,154,263,270,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 28){
				//---����
				int ShopItem[] = {221,222,226,227,171,172,173,174,175,198,183,158,-1};
				crshopIntoShop(ShopItem);
			} else if(event <= 26){
				int mes_scene = 1;

				if(event == 24 && evGet(219) && evGet(220) && evGet(221)
						&& !evGet(217)){
					//---�}�[�N�X���������ɗ���I
					return creventRyusa_Cindy();
				} else {
					if(evGet(217))
						mes_scene = 2;

					npTurn(event);
					evField(0,1);
					mes.FileMessage("RyusanoIseki.msg",event,mes_scene);
					evField(0,1);
					if(event == 24){
						//---�x�e
						if(crbaseSelectYesNo("�x�e���܂����H",64,64) == 0){
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
			//---�a�S
			if(event == 200){
				//---�a�R��
				mcDir(SOUTH);
				if(evGet(217) == 1 && evGet(218) == 0){
					//---�~�_�ՑO
					crmusicPlay(CRMUSIC_DRAGONBREATH);
				}
				evScene(3,20,2);
			} else if(event == 201){
				//---�������t���b�O
				evSet(219,1);
			} else if(event == 202){
				evSet(220,1);
			} else if(event == 203){
				evSet(221,1);
			} else if(event == 0){
				//---��
				itemBox(594,247,event);
			} else if(event == 1){
				//---��
				itemBox(595,224,event);
			} else if(event == 2){
				//---��
				itemBox(596,223,event);
			}
		}
	} else if(map == 82){
		//---凋C�O�̓�
		if(scene == 0){
			if(200 <= event && event <= 259){
				//---�t�B�[���h��
				mcDir(SOUTH);
				evMap(10,0,55,27);
			} else if(event == 260){
				//---������
				mcDir(NORTH);
				evScene(1,18,32);
			}
		} else if(scene == 1){
			//---�P�e
			if(200 <= event && event <= 201){
				//---�O����
				mcDir(SOUTH);
				evScene(0,28,36);
			} else if(event == 202){
				//---�Q�e�|�Q��
				mcDir(SOUTH);
				evScene(3,8,3);
			} else if(event == 203){
				//---�Q�e�|�P��
				mcDir(SOUTH);
				evScene(2,19,38);
			} else if(event == 204){
				//---�Q�e�|�P��
				mcDir(SOUTH);
				evScene(2,5,9);
			}
		} else if(scene == 2){
			//---�Q�e�|�P
			if(event == 200){
				//---�P�e��
				mcDir(SOUTH);
				evScene(1,36,17);
			} else if(event == 201){
				//---�P�e��
				mcDir(SOUTH);
				evScene(1,19,2);
			} else if(event == 202){
				//---�R�e��
				mcDir(SOUTH);
				evScene(4,18,19);
			}
		} else if(scene == 3){
			//---�Q�e�|�Q
			if(event == 200){
				//---�P�e��
				mcDir(SOUTH);
				evScene(1,2,17);
			} else if(event == 0){
				//---��
				itemBox(581,37,event);
			} else if(event == 1){
				//---��
				itemBox(582,224,event);
			}
		} else if(scene == 4){
			//---�R�e
			if(event == 200){
				//---�Q�e�|�P��
				mcDir(SOUTH);
				evScene(2,4,25);
			} else if(event == 201){
				//---�S�e��
				mcDir(SOUTH);
				evScene(6,17,15);
			} else if(event == 0){
				//---��
				itemBox(583,221,event);
			} else if(event == 1){
				//---��
				itemBox(584,222,event);
			}
		} else if(scene == 6){
			//---�S�e
			if(event == 200){
				//---�R�e��
				mcDir(SOUTH);
				evScene(4,14,15);
			} else if(event == 201){
				//---�T�e��
				mcDir(SOUTH);
				evScene(5,18,9);
			} else if(event == 0){
				evField(0,1);
				mes.FileMessage("Shinkiro.msg",event + 1);
			} else if(event == 1 && !evGet(197)){
				//---�܂��J���ĂȂ�������
				evField(0,1);
				mes.FileMessage("Shinkiro.msg",event + 1);
			} else if(2 <= event && event <= 5){
				//---�p�l��
				int btn = evGet(193 + (event - 2));
				int sum = evGet(193) + evGet(194) + evGet(195) + evGet(196);
				eistr str[128];

				sprintf(str,"���̃p�l���̓��͂���Ă��鐔��: %2d \\n;"
							"                    �c��̐���: %2d\\c;",btn,30 - sum);

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
					//---�J�����I
					npDelete(1);

					crsoundPlay(CRSOUND_ATACK4);
					em->Put(20,15,2,1024);
					evFrameWait(250);
					mes.FileMessage("Shinkiro.msg",10);

					evSet(197,1);
				}
			}
		} else if(scene == 5){
			//---�T�e
			if(event == 200){
				//---�S�e��
				mcDir(SOUTH);
				evScene(6,20,14);
			} else if(event == 201){
				//---�U�e��
				mcDir(SOUTH);
				evScene(10,20,20);
			} else if(event == 0){
				//---��
				itemBox(585,227,event);
			}
		} else if(scene == 10){
			//---�T�|�U�e
			if(event == 200){
				//---�T�e��
				mcDir(SOUTH);
				evScene(5,22,7);
			} else if(event == 201){
				//---�U�e��
				mcDir(SOUTH);
				evScene(7,3,3);
			} else if(event == 0){
				//---��
				itemBox(586,223,event);
			}
		} else if(scene == 7){
			//---�U�e
			if(event == 200){
				//---�T�e��
				mcDir(SOUTH);
				evScene(10,16,16);
			} else if(event == 201){
				//---�V�e��
				mcDir(SOUTH);
				evScene(8,8,8);
			}
		} else if(scene == 8){
			//---�V�e
			if(event == 200){
				//---�U�e��
				mcDir(SOUTH);
				evScene(7,8,8);
			} else if(event == 201){
				//---�ŏ�K��
				if(!evGet(199)){
					return creventShinkiro_Saijokai();
				} else {
					mcDir(SOUTH);
					evScene(9,11,9);
				}
			}
		} else if(scene == 9){
			//---�ŏ�K
			if(event == 200){
				//---�V�e��
				mcDir(SOUTH);
				evScene(8,3,3);
			} else if(event == 6){
				evField(0,1);
				mes.FileMessage("Shinkiro.msg",20);
			}
		}
	} else if(map == 83){
		//---��N���[�^�[
		if(scene == 1){
			if(event == 200){
				//---�t�B�[���h��
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
				//---�a�Q��
				int sc = DC_GET_SCENE();

				mcDir(SOUTH);
				evScene(sc,13,31);
			} else if(event == 0){
				//---��
				itemBox(576,209,event);
			} else if(event == 1){
				//---��
				itemBox(577,224,event);
			}
		} else if(scene == 2 || scene == 3){
			//---�a�Q
			if(event == 200){
				//---�a�P��
				mcDir(SOUTH);
				evScene(1,22,30);
			} else if(event == 201){
				//---�a�S��
				mcDir(SOUTH);
				evScene(5,5,11);
			} else if(event == 202){
				//---�{�^����
				mcDir(SOUTH);
				evScene(4,19,3);
			} else if(event == 0){
				//---��
				itemBox(578,228,event);
			}
		} else if(scene == 4){
			//---�{�^��
			if(event == 200){
				//---�a�Q��
				int sc = DC_GET_SCENE();

				mcDir(SOUTH);
				evScene(sc,30,11);
			} else if(event == 0){
				//---�{�^��
				int sc = evGet(186);
				evField(0,1);
				mes.FileMessage("GreatCrater.msg",10 + sc);
				evField(0,1);
				if(crbaseSelectYesNo("���삵�܂����H",64,64) == 0){
					evSet(186,(evGet(186) + 1) & 0x01);
					evField(0,1);
					mes.FileMessage("GreatCrater.msg",12 + sc);
				}
			}
		} else if(scene == 5){
			//---�a�S
			if(event == 200){
				//---�a�Q��
				int sc = 3;

				mcDir(SOUTH);
				evScene(sc,8,17);
			} else if(event == 201){
				//---�G���x�[�^�[��
				mcDir(NORTH);
				evScene(7,8,22);

				evSet(187,1);
			}
		} else if(scene == 7){
			//---�G���x�[�^�[
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
				//---�I��
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
			//---�t���A�Q
			if(event == 200){
				//---�G���x�[�^�[��
				mcDir(NORTH);
				evScene(7,8,22);

				evSet(187,2);
			} else if(event == 0){
				//---��
				itemBox(579,225,event);
			}
		} else if(scene == 9){
			//---�t���A�R
			if(event == 200){
				//---�G���x�[�^�[��
				mcDir(NORTH);
				evScene(7,8,22);

				evSet(187,3);
			}
		} else if(scene == 10){
			//---�t���A�O
			if(event == 200){
				//---�G���x�[�^�[��
				mcDir(NORTH);
				evScene(7,8,22);

				evSet(187,0);
			} else if(event == 201){
				//---��������
				mcDir(NORTH);
				evScene(11,8,22);
			} else if(event == 0){
				//---��
				itemBox(580,223,event);
			}
		} else if(scene == 11){
			//---������
			if(event == 200){
				//---�t���A�O��
				mcDir(NORTH);
				evScene(10,16,22);
			} else if(event == 201){
				//---�Ő[����
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
				//---�����o�g���I
				return creventGreatCrater_YokuryuBattle();
			}
		} else if(scene == 12){
			//---�Ő[��
			if(event == 200){
				//---��������
				mcDir(SOUTH);
				evScene(11,8,2);
			}
		}
	} else if(map == 84){
		//---���[���N���C��
		if(scene == 0){
			if(200 <= event && event <= 232){
				//---�t�B�[���h��
				mcDir(SOUTH);
				evMap(10,0,80,316);
			} else if(event == 237){
				//---�h���Q�K
				mcDir(SOUTH);
				evScene(2,11,2);
			} else if(event == 238){
				//---�n���������
				mcDir(SOUTH);
				evScene(1,10,32);
			} else if(event == 239){
				//---�n�����O�p
				mcDir(SOUTH);
				evScene(1,22,17);
			} else if(event == 240){
				//---�n�����X
				mcDir(SOUTH);
				evScene(1,21,4);
			} else if(event == 245){
				//---����
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
				//---����
				int ShopItem[] = {6,18,35,45,57,99,108,115,148,154,263,270,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 22){
				//---����
				int ShopItem[] = {221,222,226,227,171,172,173,174,175,198,183,178,-1};
				crshopIntoShop(ShopItem);
			} else if(event == 23){
				//---���E�n�}
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
				//---�^���X�^�{�I
				itemTansu(891,188);//---�����
			} else if(event == 242){
				//---�^���X�^�{�I
				itemTansu(892,225);
			} else if(event == 243){
				//---�^���X�^�{�I
				itemTansu(893,222);
			} else if(event == 244){
				//---�^���X�^�{�I
				itemTansu(894,232);
			}
		} else if(scene == 1){
			//---�n����
			if(event == 200){
				//---�n���������
				mcDir(SOUTH);
				evScene(0,38,55);
			} else if(event == 201){
				//---�n�����O�p
				mcDir(SOUTH);
				evScene(0,42,44);
			} else if(event == 202){
				//---�n�����X
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
			//---�h��
			if(event == 200){
				//---�P�K��
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
				//---�^���X�^�{�I
				itemTansu(895,223);
			}
		}
	} else if(map == 85){
		//---�łт̈��
		if(scene == 0){
			//---�a�P
			if(event == 200){
				//---�t�B�[���h��
				mcDir(SOUTH);
				evMap(10,0,370,154);
			} else if(event == 201){
				//---�a�Q��
				mcDir(SOUTH);
				evScene(1,14,3);
			} else if(202 <= event && event <= 203
				&& !evGet(200)){
				//---
				return creventHorobi_Koe();
			} else if(event == 4){
				//---��
				itemBox(587,222,event);
			} else if(event == 5){
				//---��
				itemBox(588,226,event);
			}
		} else if(scene == 1){
			//---�a�Q
			if(event == 200){
				//---�a�P��
				mcDir(SOUTH);
				evScene(0,22,43);
			} else if(event == 201){
				//---�a�R��
				mcDir(SOUTH);
				evScene(2,17,29);
			}
		} else if(scene == 2){
			//---�a�R
			if(event == 200){
				//---�a�Q��
				mcDir(SOUTH);
				evScene(1,32,10);
			} else if(event == 201/* && !evGet(201)*/){
				//---�u�r�R�s�[�I
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
		//---�Y���ꂽ���
		if(scene == 0){
			//---�a�P
			if(event == 200){
				//---�t�B�[���h��
				mcDir(SOUTH);
				evMap(10,0,195,341);
			} else if(event == 201){
				//---�a�Q��
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
			//---�a�Q
			if(event == 200){
				//---�a�P��
				mcDir(SOUTH);
				evScene(0,6,27);
			} else if(event == 201){
				//---�a�R��
				mcDir(SOUTH);
				evScene(2,10,2);
			} else if(event == 0){
				//---��
				itemBox(589,222,event);
			} else if(event == 1){
				//---��
				itemBox(590,249,event);
			}
		} else if(scene == 2){
			//---�a�R
			if(event == 200){
				//---�a�Q��
				mcDir(SOUTH);
				evScene(1,27,56);
			} else if(event == 201){
				//---�a�S��
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
			//---�a�S
			if(event == 200){
				//---�a�R��
				mcDir(SOUTH);
				evScene(2,10,38);
			} else if(event == 201){
				//---��������
				mcDir(SOUTH);
				evScene(4,7,3);
			} else if(event == 202){
				//---�a�T��
				mcDir(SOUTH);
				evScene(5,3,18);
			} else if(event == 0){
				//---��
				itemBox(591,223,event);
			}
		} else if(scene == 4){
			//---������
			if(event == 200){
				//---�a�S��
				mcDir(SOUTH);
				evScene(3,37,25);
			} else if(event == 0){
				//---��
				itemBox(592,126,event);
			}
		} else if(scene == 5){
			//---�a�T
			if(event == 200){
				//---�a�S��
				mcDir(SOUTH);
				evScene(3,52,46);
			} else if(event == 201){
				//---�a�U��
				mcDir(SOUTH);
				evScene(6,15,3);
			} else if(202 <= event && event <= 203
				&& !evGet(208)){
				return creventWasurerareta_MoveingMachin();
			}
		} else if(scene == 6){
			//---�a�U
			if(event == 200){
				//---�a�T��
				mcDir(SOUTH);
				evScene(5,44,24);
			} else if(event == 201){
				//---�a�V��
				mcDir(SOUTH);
				evScene(7,5,36);
			} else if(event == 0){
				//---��
				itemBox(593,228,event);
			}
		} else if(scene == 7){
			//---�a�V
			if(event == 200){
				//---�a�U��
				mcDir(SOUTH);
				evScene(6,3,39);
			} else if(event == 201){
				//---�ŉ��w��
				mcDir(SOUTH);
				evScene(8,14,21);
			} else if(204 <= event && event <= 205
				&& !evGet(210)){
				//---�C�z
				evSet(210,1);
				evField(0,1);
				mes.FileMessage("Wasurerareta.msg",105);
			} else if(202 <= event && event <= 203
				&& !evGet(209)){
				//---����I
				return creventWasurerareta_VSFollne();
			}
		} else if(scene == 8){
			//---�ŉ��w�a�V
			if(event == 200){
				//---�a�V��
				mcDir(SOUTH);
				evScene(7,18,6);
			} else if(201 == event){
				mcDir(SOUTH);
				evScene(0,13,5);
			}
		}
	} else if(map == 87){
		//---��ጴ�̉�
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
				//---�^���X�^�{�I
				itemTansu(896,232);
			} else if(event == 204){
				//---�^���X�^�{�I
				itemTansu(897,232);
			}
		}
	} else if(map == 88){
		//---�����̓��A
		if(scene == 0){
			if(event == 200){
				mcDir(SOUTH);
				evMap(10,0,368,63);
			} else if(event == 0){
				//---��
				itemBox(597,220,event);
			} else if(event == 1){
				//---��
				itemBox(598,163,event);
			} else if(event == 2){
				//---��
				itemBox(599,224,event);
			}
		}
	} else if(map == 89){
		//---�i����
		if(scene == 0){
			//---�P�e
			if(200 <= event && event <= 202){
				//---�t�B�[���h��
				mcDir(SOUTH);
				evMap(10,0,299,227);
			} else if(event == 203){
				//---�Q�e��
				mcDir(SOUTH);
				evScene(1,3,3);
			} else if(event == 204){
				//---�Q�e��
				mcDir(SOUTH);
				evScene(1,20,3);
			} else if(event == 1){
				//---��t
				return creventKakutojo();
			} else if(event == 8){
				//---�h��
				evYado(396);
			} else if(event <= 6){
				int mes_scene = 1;

				npTurn(event);
				evField(0,1);
				mes.FileMessage("kakutojo.msg",event,mes_scene);
				npReturn(event);
			}
		} else if(scene == 1){
			//---�Q�e
			if(event == 200){
				//---�P�e��
				mcDir(SOUTH);
				evScene(0,4,13);
			} else if(event == 201){
				//---�P�e��
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
		//---�����K
		if(scene == 0){
			if(200 <= event && event <= 202){
				//---�t�B�[���h��
				mcDir(SOUTH);
				evMap(10,0,264,150);
			} else if(event == 203){
				if(!evGet(250) && critemGetItemCount(239)){
					//---���̖�͂�Ԃ�
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
					//---�킢
					evField(0,1);
					mes.FileMessage("RyunoHokora.msg",11);
					evFrameWait(250);
					if(crbaseSelectYesNo("�킢�܂����H",64,64) == 0){
						//---�킢
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
