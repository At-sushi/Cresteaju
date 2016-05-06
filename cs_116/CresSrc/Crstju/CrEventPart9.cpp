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
		//---�쌴�̃^���X
		if(scene == 0){
			if(200 <= event && event <= 256){
				mcDir(SOUTH);
				evMap(10,0,137,176);
			} else if(event == 0 && !evGet(898)){
				//---�^���X�I
				evField(0,1);
				mes.FileMessage("NoharanoTansu.msg",100);
				//---�^���X�^�{�I
				itemTansu(898,225);
			}
		}
	} else if(map == 92){
		//---�C���[�f�B�A
		if(scene == 0){
			//---�`�|�P
			if(event == 200){
				//---�����R����
				crmusicFadeOut();
				crsoundPlay(CRSOUND_KIDOU);
				evFadeOut(1000);
				et->Delay2(1200);
				crfieldChangeMap(38,10,1,1);
				crfieldChangeScene(10,10,18);
				evFieldNoFlip(0,1);
				evFadeIn(1000);
			} else if(event == 201){
				//---�`�|�Q��
				mcDir(SOUTH);
				evScene(1,2,3);
			} else if(event == 202){
				//---�ړ����u
				if(evGet(242)){
					//---�c�{��
					mcDir(SOUTH);
					crsoundPlay(CRSOUND_KIDOU);
					evMap(95,2,4,6);
				} else {
					evField(0,1);
					mes.FileMessage("Illeadia.msg",22);
				}
			}
		} else if(scene == 1){
			//---�`�|�Q
			if(event == 200){
				//---�`�|�P��
				mcDir(SOUTH);
				evScene(0,4,17);
			} else if(event == 201){
				//---�`�|�R��
				mcDir(SOUTH);
				evScene(2,3,3);
			} else if(event == 0){
				//---��
				itemBox(600,248,event);
			}
		} else if(scene == 2){
			//---�`�|�R
			if(event == 200){
				//---�`�|�Q��
				mcDir(SOUTH);
				evScene(1,22,3);
			} else if(event == 201){
				//---�`�|�S��
				mcDir(SOUTH);
				evScene(3,2,5);
			} else if(event == 0){
				//---��
				itemBox(601,224,event);
			}
		} else if(scene == 3){
			//---�`�|�S
			if(event == 200){
				//---�`�|�R��
				mcDir(SOUTH);
				evScene(2,10,24);
			} else if(event == 201){
				//---�`�|�T��
				mcDir(SOUTH);
				evScene(4,7,3);
			}
		} else if(scene == 4){
			//---�`�|�T
			if(event == 200){
				//---�`�|�S��
				mcDir(SOUTH);
				evScene(3,28,6);
			} else if(201 <= event && event <= 202){
				//---�G���A�a��
				if(!evGet(246)){
					return crevent_IllidiaMessage1();
				} else {
					mcDir(SOUTH);
					evScene(5,10,11);
				}
			}
		} else if(scene == 5){
			//---�a�|�P
			if(event == 200){
				//---�`�|�T��
				mcDir(NORTH);
				evScene(4,6,8);
			} else if(event == 201){
				//---�a�|�Q��
				mcDir(SOUTH);
				evScene(6,7,4);
			} else if(event == 202){
				//---�a�|�R��
				mcDir(SOUTH);
				evScene(7,7,10);
			} else if(event == 203){
				//---�q�ɂ�
				mcDir(NORTH);
				evScene(8,7,14);
			} else if(event == 204){
				//---��������
				mcDir(NORTH);
				evMap(93,7,14,15);
			} else if(event == 205){
				//---�������ցi�B���ʘH�j
				mcDir(SOUTH);
				evMap(93,7,10,5);
			} else if(event == 0){
				//---�p�l��
				evField(0,1);
				mes.FileMessage("Illeadia.msg",10);
			} else if(event == 1){
				//---�񕜂̐�
				prtRecoveryAll();
				evField(0,1);
				mes.FileMessage("Illeadia.msg",11);
			} else if(event == 2){
				//---��
				itemBox(602,225,event);
			} else if(event == 3){
				//---��
				itemBox(603,169,event);
			} else if(event == 4){
				//---��
				itemBox(604,228,event);
			} else if(event == 5){
				//---��
				itemBox(622,224,event);
			}
		} else if(scene == 6){
			//---�a�|�Q
			if(event == 200){
				//---�a�|�P��
				mcDir(SOUTH);
				evScene(5,42,39);
			} else if(event == 201){
				//---�a�|�R��
				mcDir(SOUTH);
				evScene(7,7,5);
			}
		} else if(scene == 7){
			//---�a�|�R
			if(event == 200){
				//---�a�|�Q��
				mcDir(SOUTH);
				evScene(6,7,11);
			} else if(event == 201){
				//---�a�|�P��
				mcDir(SOUTH);
				evScene(5,41,50);
			}
		} else if(scene == 8){
			//---�q��
			if(200 <= event && event <= 202){
				//---�a�|�P��
				mcDir(SOUTH);
				evScene(5,76,16);
			} else if(203 <= event && event <= 205
				&& !evGet(245)){
				//---�J�[���N�_�[
				return crevent_CarCdr();
			} else if(event == 0){
				//---��
				itemBox(605,135,event);
			} else if(event == 1){
				//---��
				itemBox(606,70,event);
			} else if(event == 2){
				//---��
				itemBox(607,224,event);
			}
		}
	} else if(map == 93){
		//---�C���[�f�B�A�E������
		if(scene == 0){
			//---����
			if(event == 200){
				mcDir(SOUTH);
				evScene(1,1,15);
			} else if(event == 0){
				//---��
				if(evGet(164) && !evGet(241)){
					evField(0,1);
					mes.FileMessage("Illeadia.msg",15);
					evSet(241,1);
					critemAddItem(170,1);
				}
			}
		} else if(scene == 1){
			//---�L��
			if(event == 200){
				//---���i���̕�����
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
				//---�o����
				mcDir(SOUTH);
				evScene(10,2,4);
			} else if(event == 12){
				//---��ꂽ�V�C�\��
				evField(0,1);
				mes.FileMessage("Illeadia.msg",12);
			} else if(event == 0){
				//---��
				itemBox(610,228,event);
			} else if(event <= 20){
				//---�p�l��
				evField(0,1);
				mes.FileMessage("Illeadia.msg",14);
			}
		} else if(scene == 2){
			//---���r�[
			if(event == 200){
				mcDir(SOUTH);
				evScene(1,53,15);
			} else if(event == 201){
				mcDir(SOUTH);
				evScene(3,2,2);
			} else if(event == 202){
				//---�ʘH��
				mcDir(SOUTH);
				evScene(6,2,5);
			} else if(event == 6){
				//---��ꂽ�V�C�\��
				evField(0,1);
				mes.FileMessage("Illeadia.msg",13);
			} else if(event <= 10){
				//---�p�l��
				evField(0,1);
				mes.FileMessage("Illeadia.msg",14);
			}
		} else if(scene == 3){
			//---�q��
			if(event == 200){
				mcDir(SOUTH);
				evScene(2,17,32);
			}
		} else if(scene == 6){
			//---�ʘH
			if(event == 200){
				//---�n����
				mcDir(SOUTH);
				evScene(9,3,7);
			} else if(event == 201){
				//---���r�[��
				mcDir(SOUTH);
				evScene(2,45,16);
			}
		} else if(scene == 7){
			//---�����������
			if(200 <= event && event <= 202){
				//---�G���A�a��
				mcDir(SOUTH);
				evMap(92,5,78,46);
			} else if(event == 203){
				//---�Q�e��
				mcDir(SOUTH);
				evScene(8,3,3);
			} else if(event == 204){
				//---�n����
				mcDir(SOUTH);
				evScene(9,7,3);
			} else if(event == 205){
				//---�G���A�a�ցi�B���ʘH�j
				mcDir(SOUTH);
				evMap(92,5,74,37);
			} else if(event == 0 && !evGet(238)){
				//---�B���ʘH������
				crsoundPlay(CRSOUND_ATACK4);
				em->Put(10,5,2,1024);
				evFrameWait(100);
				evSet(238,1);
			}
		} else if(scene == 8){
			//---�������Q�e
			if(event == 200){
				//---�������
				mcDir(SOUTH);
				evScene(7,5,7);
			} else if(event == 0){
				//---��
				itemBox(608,137,event);
			} else if(event == 1){
				//---��
				itemBox(609,228,event);
			}
		} else if(scene == 9){
			//---�������n��
			if(event == 200){
				//---�������
				mcDir(SOUTH);
				evScene(7,14,9);
			} else if(event == 201){
				//---�ʘH��
				mcDir(SOUTH);
				evScene(6,8,2);
			}
		} else if(scene == 10){
			//---�������o��
			if(event == 200){
				//---�L����
				mcDir(SOUTH);
				evScene(1,10,26);
			} else if(event == 201){
				//---�G���A�c��
				mcDir(SOUTH);
				evMap(94,0,12,38);
			}
		}
	} else if(map == 94){
		//---�C���[�f�B�A�A�G���A�c
		if(scene == 0){
			//---�c�|�P
			if(event == 200){
				//---��������
				mcDir(NORTH);
				evMap(93,10,29,5);
			} else if(201 <= event && event <= 205){
				//---�c�|�Q��
				mcDir(NORTH);
				evScene(1,23,50);
			} else if(event == 0){
				//---��
				itemBox(611,239,event);//---���̖��
			}
		} else if(scene == 1){
			//---�c�|�Q�i�c�{�O�j
			if(200 <= event && event <= 204){
				//---�c�|�P��
				mcDir(SOUTH);
				evScene(0,30,8);
			} else if(205 <= event && event <= 207){
				//---�c�{��
				mcDir(NORTH);
				evMap(95,0,16,27);
			} else if(event == 208){
				//---�ړ����u��
				mcDir(SOUTH);
				evScene(2,8,3);
			} else if(event == 209){
				//---�󕨌ɂ�
				mcDir(NORTH);
				evScene(3,5,7);
			} else if(event == 0){
				//---�񕜂̐�
				prtRecoveryAll();
				evField(0,1);
				mes.FileMessage("Illeadia.msg",11);
			} else if(event == 1){
				//---��
				itemBox(612,184,event);//---�v���X�G�N�X�e���_�[
			}
		} else if(scene == 2){
			//---�ړ����u
			if(event == 200){
				//---�����R���E�ʂ̏ꏊ�Q��
				crmusicFadeOut();
				crsoundPlay(CRSOUND_KIDOU);
				evFadeOut(1000);
				et->Delay2(1200);
				crfieldChangeMap(38,12,1,1);
				crfieldChangeScene(12,17,4);
				evFieldNoFlip(0,1);
				evFadeIn(1000);
			} else if(event == 201){
				//---�c�|�Q��
				mcDir(SOUTH);
				evScene(1,4,43);
			}
		} else if(scene == 3){
			//---�󕨌�
			if(event == 200){
				//---�c�|�Q��
				mcDir(SOUTH);
				evScene(1,12,16);
			} else if(event == 201){
				//---�󕨌ɒn����
				mcDir(SOUTH);
				evScene(4,2,3);
			}
		} else if(scene == 4){
			//---�󕨌ɒn��
			if(event == 200){
				//---�󕨌ɂ�
				mcDir(SOUTH);
				evScene(3,7,3);
			} else if(201 <= event && event <= 202
				&& !evGet(249)){
				//---�o���A�[�Q�O�O�O�{�X�I�I
				return crevent_HomotukoChika();
			} else if(event == 0){
				//---��
				itemBox(617,223,event);
			} else if(event == 1){
				//---��
				itemBox(618,225,event);
			} else if(event == 2){
				//---��
				itemBox(619,62,event);//---�\�j�b�N�K��
			} else if(event == 3){
				//---��
				itemBox(620,220,event);//---�_�C������
			} else if(event == 4){
				//---��
				itemBox(621,139,event);//---�I�E�E�e�B�[���@
			}
		}
	} else if(map == 95){
		//---�C���[�f�B�A�A�c�{
		if(scene == 0){
			//---�d�|�P
			if(200 <= event && event <= 202){
				//---�G���A�c��
				mcDir(SOUTH);
				evMap(94,1,23,11);
			} else if(event == 203){
				//---�d�|�Q��
				mcDir(SOUTH);
				evScene(1,2,16);
			} else if(event == 204){
				//---�d�|�Q��
				mcDir(SOUTH);
				evScene(1,21,16);
			}
		} else if(scene == 1){
			//---�d�|�Q
			if(event == 200){
				//---�d�|�P��
				mcDir(SOUTH);
				evScene(0,5,5);
			} else if(event == 201){
				//---�d�|�P��
				mcDir(SOUTH);
				evScene(0,29,5);
			} else if(event == 202){
				//---�ړ����u��
				mcDir(SOUTH);
				evScene(2,7,3);
			} else if(event == 203){
				//---�d�|�R��
				mcDir(SOUTH);
				evScene(3,4,24);
			} else if(event == 2){
				evField(0,1);
				mes.FileMessage("Illeadia.msg",16);
			} else if(event == 0){
				//---��
				itemBox(613,136,event);//---�A�[�K�C���v���[�g
			} else if(event == 1){
				//---��
				itemBox(614,48,event);//---�~�X�g�����W���b�N
			}
		} else if(scene == 2){
			//---�ړ����u
			if(event == 200){
				//---�d�|�Q��
				mcDir(SOUTH);
				evScene(1,20,7);
			} else if(event == 201){
				//---�ړ����u
				if(evGet(242)){
					//---�����
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
					//---�N�������邩�H
					mes.FileMessage("Illeadia.msg",20);
					evField(0,1);
					if(crbaseSelectYesNo("�N�������܂����H",64,64) == 0){
						crsoundPlay(CRSOUND_KIDOU);
						evSet(242,1);
					}
				} else {
					mes.FileMessage("Illeadia.msg",21);
				}
			}
		} else if(scene == 3){
			//---�d�|�R
			if(event == 200){
				//---�d�|�Q��
				mcDir(SOUTH);
				evScene(1,12,2);
			} else if(event == 201){
				//---�d�|�S��
				mcDir(SOUTH);
				evScene(4,8,9);
			}
		} else if(scene == 4){
			//---�d�|�S
			if(event == 200){
				//---�d�|�R��
				mcDir(SOUTH);
				evScene(3,4,2);
			} else if(201 <= event && event <= 203){
				//---�d�|�T�i���ԁj��
				mcDir(NORTH);
				evScene(5,12,18);
			}
		} else if(scene == 5){
			//---�d�|�T
			if(200 <= event && event <= 202){
				//---�d�|�S��
				mcDir(SOUTH);
				evScene(4,8,3);
			} else if(204 <= event && event <= 206
				&& !evGet(263)){
				//---�f�B�[���̐�
				return crevent_IllidiaDeen();
			} else if(event == 203){
				//---�d�|�U��
				mcDir(SOUTH);
				evScene(6,5,31);
			} else if(event == 0){
				//---��
				itemBox(615,38,event);//---�t�B���K���g
			} else if(event == 1){
				//---��
				itemBox(616,191,event);//---���r�[�g�D�[�X
			}
		} else if(scene == 6){
			//---�d�|�U
			if(event == 200){
				//---�d�|�T��
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
				//---�d�|�V��
				mcDir(SOUTH);
				evScene(7,16,2);
			} else if(event == 210){
				//---�d�|�W��
				mcDir(SOUTH);
				evScene(8,9,11);
			} else if(event == 0){
				//---���X�g�o�g���I�I
				return crevent_IllidiaLastBattle();
			}
		} else if(scene == 7){
			//---�d�|�V
			if(event == 200){
				//---�d�|�U��
				mcDir(SOUTH);
				evScene(6,42,31);
			} else if(event == 201){
				//---�d�|�W��
				mcDir(SOUTH);
				evScene(8,23,11);
			}
		} else if(scene == 8){
			//---�d�|�W
			if(event == 200){
				//---�d�|�V��
				mcDir(SOUTH);
				evScene(7,2,13);
			} else if(event == 201){
				//---�d�|�U��
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
		//---�ю�������
		if(scene == 0){
			if(200 <= event && event <= 201){
				//---�t�B�[���h��
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
					"���C�t�J�v�Z���r�@�@�Q��;"
					"�Z�[�^�[�@�@�@�@�@�@�T��;"
					"�ю��̃��[�u�@�@�@�@�V��;"
					"�C�[�O���X�J�[�t�@�@�W��;"
					"�}�W�b�N�J�v�Z���@�P�O��;"
					"�E�B�U�[�h�i�C�t�@�P�T��;"
					"���P�V�X�̐��t�@�@�Q�O��;";
				CrSelectWindow win;
				CrStringWindow keito;
				int sel;

				memset(&info,0,sizeof(info));

				win.Create(64,64,20,11,"�ǂ�ƌ������܂����H",str);

				do {
					crbaseMenuReset();

					keito.Create(64,256,10,2);
					keito.Reset();
					keito.SetColor(CRCOLOR_WHITE);
					keito.DrawText(" �ю� : ");
					sprintf(s,"%2d",critemGetItemCount(213));
					keito.SetColor(CRCOLOR_YELLOW);
					keito.DrawText(s);
					keito.SetColor(CRCOLOR_WHITE);
					keito.DrawText("��");
					keito.Refresh();

					win.Paint();
					win.Refresh();
					crbaseMenuStart();
					sel = win.Select(&info);

					if(sel != -1){
						int count = critemGetItemCount(213);

						if(count < kosu[sel]){
							//---����Ȃ�
							evField(0,1);
							mes.FileMessage("keito.msg",100);
							continue;
						} else {
							sprintf(s,"%s �ł����ł����H",critemGetItemClass(item_list[sel])->GetName());
							if(crbaseSelectYesNo(s,80,80) == 0){
								evField(0,1);
								mes.FileMessage("keito.msg",101);

								mes.CreateNewMessage();
								sprintf(s,"%s ����ɓ��ꂽ\\c;",critemGetItemClass(item_list[sel])->GetName());
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
		//---�g���C�A�̓��A
		if(scene == 0){
			if(200 == event){
				mcDir(SOUTH);
				evMap(10,0,253,150);
			} else if(201 == event && evGet(255) == 1
				&& AFTER_KOJINSAI()){
				//---�V���[�e�B���O�X�^�[�Q
				return crevent_TreiaSS2();
			}
		}
	} else if(map == 101){
		//---�G���f�B���O
		if(scene == 1){
			if(200 <= event && event <= 219){
				return crevent_EndingSorekara();
			}
		}
	} else if(map == 103){
		//---�G���f�B���O
		if(scene == 0){
			if(207 <= event && event <= 210){
//				return crevent_EndingTheEnd();
				return crevent_EndingMatsuri6();
			}
		}
	}
	return 1;
}
