/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrMainMenu.cpp ...MainMenu functions

-----------------------------------------------------------*/


#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CRMAINMANU

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#include "CrBase.h"
#include "CrBattle.h"
#include "CrEvent.h"
#include "CrEvCom.h"

//---game info
#define CR_GAMEINFO_EXTERNPOINTER
#include "CrGameInfo.h"

#define REDRAW_MENUSCENE(pwin) {\
		crcharaDrawStatus(pwin);\
		crcharaShowFace(512,48,0,4);\
		crbaseShowPlayTime(32,272);\
		crbaseShowMoney(32,320);\
}

void crmainMainMenu_HiddenInfo(void);

//---���C�����j���[��ʃN���A
void crmainClearMenu(int screen = 0x02)
{
	int x,y;

	for(y = 0;y < 480;y += pWallPaperCell->Data.ySize){
		for(x = 0;x < 640;x += pWallPaperCell->Data.xSize){
			if(screen & 0x01){
				pWallPaperCell->PutClip(ew->lpCell[0],x,y);
			}
			if(screen & 0x02){
				pWallPaperCell->PutClip(ew->lpCell[1],x,y);
			}
		}
	}
}

ei_s32 crmainGetMenuWindowStyle(void)
{
	return CRWIN_FRAME | CRWIN_BGFILL /* CRWIN_BGALPHA*/;
}

ei_s32 crmainGetMenuWindowFont(void)
{
	return EINORMAL_FONT;
}

#include "CrMainMenu_SubEquip.cpp"
#include "CrMainMenu_SubStatus.cpp"
#include "CrMainMenu_SubLearnMagic.cpp"
#include "CrMainMenu_SubBattle.cpp"
#include "CrMainMenu_SubSort.cpp"

//---�Z�[�u���j���[
int crmainMenuSave(void)
{
	int number;
	static eistr DataList[1024];
	CrSelectWindow menu;
	CRWIN_SELECTINFO info;

	//---���j���[�I�t�Z�b�g
	memset(&info,0,sizeof(info));
	info.Offset = crdataGetSystem()->SaveNumber;
	if(info.Offset < 0)
		info.Offset = 0;

	while(1){
		crbaseMenuReset();
		crmainClearMenu();
		memset(&DataList[0],0,sizeof(DataList));
		crfileGetSaveDataList(&DataList[0],0);
		menu.Create(32,32,32,22,"�ǂ��ɃZ�[�u���܂����H",DataList,1,58);
		ew->Refresh();
		crbaseMenuStart();

		number = menu.Select(&info);

		if(number != -1){
			eistr s[80];
			sprintf(s,"No.%d �ɃZ�[�u���܂��B�Z�[�u���܂����H",number);
			if(crbaseSelectYesNo(s,96,48 + number * 20 - 16) == 0){
				crdataGetSystem()->SaveNumber = number;
				if(crfileSaveData(number,SAVE_FILE_ID1,SAVE_FILE_ID2,1) == 0){
					//---�Z�[�u�ł��Ȃ�����
					CrMesManager mes;
					mes.CreateNewMessage();
					mes.Message("�Z�[�u�Ɏ��s���܂���\\c;");
					mes.Draw();
					mes.CloseMessage();
				}

				break;
			}
			continue;
		}
		break;
	}

	return MAINLOOP_NOMESSAGE;
}

//---���[�h���j���[
int crmainMenuLoad(void)
{
	int number,ret;
	static eistr DataList[1024];
	CrSelectWindow menu;
	CRWIN_SELECTINFO info;
	int mode = 0;

	//---���j���[�I�t�Z�b�g
	memset(&info,0,sizeof(info));

	crbaseMenuReset();
	crmainClearMenu();
	memset(&DataList[0],0,sizeof(DataList));
	crfileGetSaveDataList(&DataList[0],mode);

	do {
		menu.Create(32,32,32,22 + mode * 3,"�ǂ�����[�h���܂����H",DataList,1,58);
		ew->Refresh();
		crbaseMenuStart();
		number = menu.Select(&info);

		if(number != -1){

			ret = crfileLoadData(number,SAVE_FILE_ID1,SAVE_FILE_ID2,1);
			if(ret == 1){
				crbaseSetAllData();
				//---���[�h����
				ef->SetDirection(DIR_SOUTH);
			} else if(ret == 0){
				//---�W�J�ł��Ȃ�����
				CrMesManager mes;
				mes.CreateNewMessage();
				mes.Message("�Z�[�u�t�@�C�������Ă��܂�\\c;");
				mes.Draw();
				mes.CloseMessage();
			} else if(ret == 2){
				//---�t�@�C�����Ȃ����A���Ă�
			}

		} else {
			return MAINLOOP_CANCELMENU;
		}
		crbaseMenuReset();
	} while(ret == 0 || ret == 2);

	return MAINLOOP_RELOADMENU;
//	return MAINLOOP_NOMESSAGE;
}

#include "CrMainMenu_SubSystem.cpp"

//---�A�C�e��
int crmainMenuItem(void)
{
	int item,member;

	crmainClearMenu();

	do {
		CRWIN_SELECTINFO CharaSelInfo;
		memset(&CharaSelInfo,0,sizeof(CharaSelInfo));

		item = critemSelectItem(32,32,20,2,
			CRMATERIAL_KIND_ITEMCOUNT,0,0,0,0,&pGameInfo->SelectInfoItem);

		if(critemIsUseItem(item,0)){
			//---�ړ����Ɏg����A�C�e����������
			while(critemGetItemCount(item) >= 1){
				//---�A�C�e�����������
				if(item == 211){
					//---���̃I���S�[��
					crmusicMusicTest();
					crmainClearMenu();
					break;
				} else if((221 <= item && item <= 225)
					||(231 <= item && item <= 240)){
					//---���C�t�J�v�Z���`�G���_�[�J�v�Z��
					member = crcharaSelectMember(48,48,CRBASE_SELECTPLAYER_LP | CRBASE_SELECTPLAYER_MC,
						NULL,&CharaSelInfo);

					if(member != -1){
						CrCharacter *pChara = crcharaGetPartyMember(member);
						CrItem *pItem = critemGetItemClass(item);

						//---���^���d�l�h�~
						if(pItem->GetFreeData(0) && !pItem->GetFreeData(1)){
							//---LP
							if(pChara->GetLP() == pChara->GetMaxLP()){
								crsoundPlay(CRSOUND_BEEP_1);
								continue;
							}
						} else if(!pItem->GetFreeData(0) && pItem->GetFreeData(1)){
							//---MC
							if(pChara->GetMC() == pChara->GetMaxMC()){
								crsoundPlay(CRSOUND_BEEP_1);
								continue;
							}
						} else {
							if(pChara->GetLP() == pChara->GetMaxLP()
								&& pChara->GetMC() == pChara->GetMaxMC()){
								crsoundPlay(CRSOUND_BEEP_1);
								continue;
							}
						}
						//---�P���炷
						critemSubItem(item,1);

						pChara->AddLP(pItem->GetFreeData(0));
						pChara->AddMC(pItem->GetFreeData(1));
						crsoundPlay(CRSOUND_RICOVERY);

						continue;
					}
					break;
				}
			}
		} else if(item != -1){
			crsoundPlay(CRSOUND_BEEP_1);
		}
	} while(item != -1);

	return MAINLOOP_NOMESSAGE;
}

//---���@
int crmainMenuMagic(void)
{
	int magic,member;
	static CRWIN_SELECTINFO info;
	CrCharacter *pChara,*pDstChara;
	CrMagic *pMagic;

	//---�L�����N�^�[�I��
	while(1){
		CRWIN_SELECTINFO CharaSelInfo;
		memset(&CharaSelInfo,0,sizeof(CharaSelInfo));

		crmainClearMenu();
		member = crcharaSelectMember(32,32,CRBASE_SELECTPLAYER_MC,"�N�̖��@�H",&info);
		if(member == -1)
			break;
		pChara = crcharaGetPartyMember(member);

		do {
			magic = crmagicSelectCharacterMagic(pChara,
				0, 32,48,20,2,CRMATERIAL_KIND_MAGICMC);

			if(crmagicIsUseMagic(pChara,magic,0)){
				while(1){
					pMagic = crmagicGetMagicClass(magic);
					//---�l�b�������I�I
					if(pChara->GetMC() < pMagic->GetMC())
						break;

					if(magic == 1 || magic == 3 || magic == 6){
						//---���J�o���[
						member = crcharaSelectMember(48,48,CRBASE_SELECTPLAYER_LP | CRBASE_SELECTPLAYER_MC,
							NULL,&CharaSelInfo);
						if(member == -1)
							break;
						if(member != -1){
							pDstChara = crcharaGetPartyMember(member);
							if(pDstChara->GetLP() == pDstChara->GetMaxLP()){
								crsoundPlay(CRSOUND_BEEP_1);
								continue;
							}

							pDstChara->AddLP(crmagicGetBaseValue(magic,pChara));
							pChara->AddMC(-pMagic->GetMC());
							//---���@�o�ߏ����Z�b�g
							pChara->SetLastUsingMagic();
							pChara->SetDisableMCCount(-1);

							crsoundPlay(CRSOUND_RICOVERY);
						}
						continue;
/*					} else if(magic == 5 || magic == 7){
						//---���C�t�V�����[�A���C�t�E�B���h
						for(member = 0;member < MEMBER_MAX;member ++){
							pDstChara = crcharaGetPartyMember(member);
							if(pDstChara == NULL)
								continue;

							pDstChara->AddLP(crmagicGetBaseValue(magic));
						}
						crsoundPlay(CRSOUND_RICOVERY);

						//---���@�o�ߏ����Z�b�g
						pChara->SetLastUsingMagic();
						pChara->SetDisableMCCount(-1);
						pChara->AddMC(-pMagic->GetMC());
						continue;*/
					}
				}
			} else if(magic != -1){
				//---�g���Ȃ����@��������r�[�v
				crsoundPlay(CRSOUND_BEEP_1);
			}
		} while(magic != -1);
	}

	return MAINLOOP_NOMESSAGE;
}

#define STR_DECODE(OUT,STR) \
			for(a = 0;a < (int)strlen(STR) + 1;a ++){\
				OUT[a] = STR[a];\
				if(a != (int)strlen(STR)\
					&& a % 2 == 1){\
					OUT[a] --;\
				}\
			}

//---�B�����\��
void crmainMainMenu_HiddenInfo(void)
{
	int member;
	CrCharacter *pChara;
	CrSelectWindow win;
	eistr str[500],*p = str,s[80];
	CRWIN_SELECTINFO sinfo;

	memset(&sinfo,0,sizeof(sinfo));

	crbaseSetWallPaperSuraface();
	crbaseInitMenuScene();

	for(member = 0;member <= 6/*PLAYERNAME_MAX*/;member ++){
		sprintf(p,"%s;",pCharacterInfo[member].GetName());
		p += strlen(p);
		*p = NULL;
	}

	win.Create(32,32,12,12,"",str);

	do {
		CrInput ci;

		crbaseMenuReset();
		crmainClearMenu(0x02);
		ew->Refresh();
		win.Paint();
		win.Refresh();
		crbaseMenuStart();
		member = win.Select(&sinfo);

		ci.Get();

		int max = 7,h_member = -1;

		while(member != -1){
			ci.Get();
			if(ci.IsUp()){
				if(--member < 0)
					member = max - 1;
			} else if(ci.IsDown()){
				if(++member >= max)
					member = 0;
			} else if((ci.IsButton(0) || ci.IsButton(1))
				&& h_member != -1){
				member = -1;
				break;
			}

			if(member != h_member){

			CrStringWindow info,info2;
				h_member = member;
			info.Create(32,8,18,29);
			info.Paint();

			info2.Create(336,8,18,29);
			info2.Paint();

			info2.AddReturn();
			sprintf(s,"����������          : %10d",pGameInfo->WalkCount);
			info2.DrawText(s);
			info2.AddReturn();
			info2.AddReturn();
			sprintf(s,"�퓬��            : %10d",pGameInfo->BattleCount);
			info2.DrawText(s);
			info2.AddReturn();
			sprintf(s,"��������          : %10d",pGameInfo->EscapeCount);
			info2.DrawText(s);
			info2.AddReturn();
			sprintf(s,"�퓬�œ�������      : %10d",pGameInfo->AllGetMoney);
			info2.DrawText(s);
			info2.AddReturn();
			sprintf(s,"�퓬�œ����o���l    : %10d",pGameInfo->AllGetExperience);
			info2.DrawText(s);
			info2.AddReturn();
			info2.AddReturn();
			sprintf(s,"�Z�[�u��          : %10d",pGameInfo->SaveCount);
			info2.DrawText(s);
			info2.AddReturn();
			info2.AddReturn();

			int a,b,count = 0;
			for(a = 500 , count = 0;a <= 622;a ++){
				if(evGet(a)){
					count ++;
				} else {
					char s[80];
					sprintf(s,"%d\n",a);
					eiDebugWriteFile(s);
				}
			}
			if((float)count / (float)(a - 500) * 100.0f >= 100.0f){
				sprintf(s,"�󔠉����          :    %3.2f%%",100.0f);
			} else {
				sprintf(s,"�󔠉����          :    %3.3f%%",(float)count / (float)(a - 500) * 100.0f);
			}
			info2.DrawText(s);
			info2.AddReturn();

			for(a = 800 , count = 0;a <= 898;a ++){
				if(evGet(a)){
					count ++;
				} else {
					char s[80];
					sprintf(s,"%d\n",a);
					eiDebugWriteFile(s);
				}
			}
			if((float)count / (float)(a - 800) * 100.0f >= 100.0f){
				sprintf(s,"�^���X�����        :    %3.2f%%",100.0f);
			} else {
				sprintf(s,"�^���X�����        :    %3.3f%%",(float)count / (float)(a - 800) * 100.0f);
			}
			info2.DrawText(s);
			info2.AddReturn();
			info2.AddReturn();

			//---�����Y
			int shisan = crbaseGetMoney(),soitem = 0;
			for(a = 1;a < ITEM_MAX;a ++){
				shisan += (critemGetItemCount(a) * critemGetItemClass(a)->GetValue());
				soitem += critemGetItemCount(a);
			}
			for(a = 0;a < MEMBER_MAX;a ++){
				CrCharacter *pChara = crcharaGetPartyMember(a);
				if(pChara != NULL){
					for(b = 0;b < EQ_ALL_MAX;b ++){
						if(pChara->GetEquipment(b) != 0){
							shisan += (critemGetItemClass(pChara->GetEquipment(b))->GetValue());
							soitem ++;
						}
					}
				}
			}
			sprintf(s,"���A�C�e����        : %10d",soitem);
			info2.DrawText(s);
			info2.AddReturn();
			sprintf(s,"�����Y              : %10d",shisan);
			info2.DrawText(s);
			info2.AddReturn();
			info2.AddReturn();


			sprintf(s,"�ŒZ�N���A����      :  %3d:%02d:%02d",
				pGameInfo->MinClearHour,pGameInfo->MinClearMinute,pGameInfo->MinClearSecond);
			info2.DrawText(s);
			info2.AddReturn();

			char spflag1[] = {"�F�O���D�W����m�Ղ݂͂ݓ}����"};
			STR_DECODE(s,spflag1);
			info2.AddReturn();
			if(evGet(262)){
				info2.DrawText(s);
			}
/*
			char spflag2[] = {"�F�B���f�C�m�O�Y���ʓ��낾"};
			STR_DECODE(s,spflag2);
			info2.AddReturn();
			if(critemGetItemCount(30)){
				evSet(264,1);
			}
			if(evGet(264)){
				info2.DrawText(s);
			}

			char spflag3[] = {"�F�B���f�C�m�O�Y�񔅂ł��݂�"};
			STR_DECODE(s,spflag3);
			info2.AddReturn();
			if(evGet(265)){
				info2.DrawText(s);
			}*/
			info2.AddReturn();

			//---------------------------------------------------
			pChara = &pCharacterInfo[member];
			
			info.SetColor(CRCOLOR_GREEN);
			info.DrawText(pChara->GetName());
			info.AddReturn();
			info.SetColor(CRCOLOR_WHITE);

			sprintf(s,"�s����             : %9d",pChara->CharaInfo.BattleHistory.ActionCount);
			info.DrawText(s);
			info.AddReturn();
			sprintf(s,"�C���             : %9d",pChara->CharaInfo.BattleHistory.DeathCount);
			info.DrawText(s);
			info.AddReturn();
			sprintf(s,"�h���             : %9d",pChara->CharaInfo.BattleHistory.DefenseCount);
			info.DrawText(s);
			info.AddReturn();
			sprintf(s,"�o������G�̐�       : %9d",pChara->CharaInfo.BattleHistory.EnemyCount);
			info.DrawText(s);
			info.AddReturn();
			sprintf(s,"�Ƃǂ߂��������G�̐� : %9d",pChara->CharaInfo.BattleHistory.FinishEnemyCount);
			info.DrawText(s);
			info.AddReturn();
			sprintf(s,"�^�����_���[�W       : %9d",pChara->CharaInfo.BattleHistory.GiveDamage);
			info.DrawText(s);
			info.AddReturn();
			sprintf(s,"����U���~�X��     : %9d",pChara->CharaInfo.BattleHistory.GiveMissCount);
			info.DrawText(s);
			info.AddReturn();
/*			sprintf(s,"�~�X���󂯂���     : %d",pChara->CharaInfo.BattleHistory.ReceiveMissCount);
			info.DrawText(s);
			info.AddReturn();*/
//			info.AddReturn();

			sprintf(s,"����U����         : %9d",pChara->CharaInfo.BattleHistory.WeaponCount);
			info.DrawText(s);
			info.AddReturn();
			sprintf(s,"���@�g�p��         : %9d",pChara->CharaInfo.BattleHistory.MagicCount);
			info.DrawText(s);
			info.AddReturn();
			sprintf(s,"�A�C�e�����g������ : %9d",pChara->CharaInfo.BattleHistory.ItemCount);
			info.DrawText(s);
			info.AddReturn();
			sprintf(s,"�K�E�Z��           : %9d",pChara->CharaInfo.BattleHistory.SpecialCount);
			info.DrawText(s);
			info.AddReturn();
			sprintf(s,"�󂯂��_���[�W       : %9d",pChara->CharaInfo.BattleHistory.ReceiveDamage);
			info.DrawText(s);
			info.AddReturn();

			info.AddReturn();
			sprintf(s,"�ŗ�                 :   %3.2f%%",
				100.0f - ((float)pChara->CharaInfo.BattleHistory.GiveMissCount * 100.0f
				/ (float)pChara->CharaInfo.BattleHistory.WeaponCount));
			info.DrawText(s);
			info.AddReturn();
			sprintf(s,"����U����           :   %3.2f%%",
				((float)pChara->CharaInfo.BattleHistory.WeaponCount * 100.0f
				/ (float)pChara->CharaInfo.BattleHistory.ActionCount));
			info.DrawText(s);
			info.AddReturn();
			sprintf(s,"���@��               :   %3.2f%%",
				((float)pChara->CharaInfo.BattleHistory.MagicCount * 100.0f
				/ (float)pChara->CharaInfo.BattleHistory.ActionCount));
			info.DrawText(s);
			info.AddReturn();
			sprintf(s,"�h�䗦               :   %3.2f%%",
				((float)pChara->CharaInfo.BattleHistory.DefenseCount * 100.0f
				/ (float)pChara->CharaInfo.BattleHistory.ActionCount));
			info.DrawText(s);
			info.AddReturn();
			sprintf(s,"�A�C�e����           :   %3.2f%%",
				((float)pChara->CharaInfo.BattleHistory.ItemCount * 100.0f
				/ (float)pChara->CharaInfo.BattleHistory.ActionCount));
			info.DrawText(s);
			info.AddReturn();

			sprintf(s,"�C��w��             :   %3.2f%",
				((float)pChara->CharaInfo.BattleHistory.DeathCount * 100.0f
				/ (float)pChara->CharaInfo.BattleHistory.ActionCount));
			info.DrawText(s);
			info.AddReturn();

			sprintf(s,"�_���[�W�w��         :   %3.2f%",
				((float)pChara->CharaInfo.BattleHistory.GiveDamage / 10.0f
				/ (float)pChara->CharaInfo.BattleHistory.ActionCount));
			info.DrawText(s);
			info.AddReturn();

			sprintf(s,"�p���l�b             : %9d",
				pChara->CharaInfo.BattleHistory.UseMC);
			info.DrawText(s);
			info.AddReturn();

			info.Refresh();
			info2.Refresh();

			}
			eiSleep(10);

			crbaseMenuReset();
			crbaseMenuStart();

//			ci.WaitAnykey();
		}
	} while(member != -1);
}

//---�R�[���o�b�N�Ńv���C���Ԃ�\��
int crmainMainMenu_SelectCallBack(CrSelectWindow *pwin,eiCell *pCell,int Message,ei_u32 Param1,ei_u32 Param2,int Param3)
{
	if(Message == CRWIN_SELECT_IDLE){
		crbaseShowPlayTime(32,272,1);
		return 1;
	}
	return 0;
}

//----���C�����j���[
int crmainMainMenu(int mode)
{
	int sel = 0,res;
	CrSelectWindow menu;
	CrStringWindow status;
	static CRWIN_SELECTINFO info;

	memset(&info,0,sizeof(info));
	//---�ǎ��Z�b�g
	crbaseSetWallPaperSuraface();

	//---���j���[�֐��e�[�u��
	int (*MenuTable[12])(void) = {
		crmainMenuItem,crmainMenuMagic,
		crmainMenuEquip,crmainLearnMagic,
		crmainMenuBattle,crmainMenuStatus,
		crmainmenuSort,crmainMenuSystem,
		crmainMenuSave
	};

	if(evGet(EV_MENU_MODE) == 1){
		//---�V�X�e���ȊO�g���Ȃ�
		mode = 2;
		memset(MenuTable,NULL,sizeof(MenuTable));
		MenuTable[0] = crmainMenuSystem;
		MenuTable[1] = crmainMenuSave;
	} else if(evGet(EV_MENU_MODE) == 2){
		//---�V�X�e���_��
		mode = 1;
	}

	if(mode == 1){
		MenuTable[10] = NULL;
		MenuTable[11] = NULL;
	}

	crbaseInitMenuScene();
	crmainClearMenu(0x02);
/*	crbaseMenuReset();
	if(pGameInfo->TransWindow == 0){
		//---����ʃN���A
		crmainClearMenu(0x02);
	}
	crbaseSaveFrontPage(1);*/
	//---�K�v�ȃE�B���h�E��\��
	eistr *menustr = NULL;

	if(mode == 0){
		menustr = " �A�C�e�� ;�@���@�@�@;�@���@���@; ���@�C�� ;�@��@���@;�X�e�[�^�X;�@���@���@; �V�X�e�� ; �Z �[ �u ;";
	} else if(mode == 1){
		menustr = " �A�C�e�� ;�@���@�@�@;�@���@���@; ���@�C�� ;�@��@���@;�X�e�[�^�X;�@���@���@;";
	} else if(mode == 2){
		menustr = " �V�X�e�� ; �Z �[ �u ;";
	}

	int sy = 14;

	if(mode == 1){
		sy = 11;
	} else if(mode == 2){
		//---�V�X�e���I�����[
		sy = 5;
	}

	menu.Create(32,32,9,sy,
		"���C�����j���[",menustr,1,12);
	menu.SetSelectCallBack(crmainMainMenu_SelectCallBack);
	if(mode != 2){
		//---�ʏ�
		crcharaShowStatus(&status,
			224,32,
			SHOWSTATUS_DEFAULT
			| SHOWSTATUS_LARGESIZE /*SHOWSTATUS_NORMALSIZE*/
			| SHOWSTATUS_PARTYMEMBER);
		REDRAW_MENUSCENE(&status);
	} else {
		//---�V�X�e���I�����[
		crbaseShowPlayTime(32,272);
	}

	//---
	while(sel != -1){
		ew->Refresh();
//		menu.Refresh();
		crbaseMenuStart();

		sel = menu.Select(&info);

#if(CR_DEBUG == 1)
		if(ei->Input[0].Button[2]){
			crmainMainMenu_HiddenInfo();
		}
#endif

		if(sel != -1 && MenuTable[sel]){
			res = (*MenuTable[sel])();
			if(res == MAINLOOP_ENDLOOP){
				RECT rect = {0,0,640,480};
				crefectScreenEfect_FadeOut(&rect,500);
				return res;
			}
			if(res == MAINLOOP_RELOADMENU){
				//---���j���[�����[�g
				return res;
			}
		}

		//---�ĕ`��
		if(sel != -1){
			crbaseMenuReset();
			if(pGameInfo->TransWindow == 0){
				crmainClearMenu();
			}
			menu.Paint();
			if(mode != 2){
				crcharaShowStatus(&status,
					224,32,
					SHOWSTATUS_DEFAULT
					| SHOWSTATUS_LARGESIZE /*SHOWSTATUS_NORMALSIZE*/
					| SHOWSTATUS_PARTYMEMBER);
//				status.Paint();
				REDRAW_MENUSCENE(&status)
			} else {
				//---�V�X�e���I�����[
				crbaseShowPlayTime(32,272);
			}
		}
	}

	crbaseEndMenuScene();
	//---AutoSave
	if(crdataGetIniFile()->AutoSave && (mode == 0 || mode == 2)){
		//---�I�[�g�Z�[�u�ŁA�V�X�e�����j���[�\�Ȃ�
		crfileSaveData(SAVE_FILE_MAX,SAVE_FILE_ID1,SAVE_FILE_ID2,1);
	}

	ei->Get();

	return MAINLOOP_NOMESSAGE;
}
