/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBattle_Command.cpp ...Battle Input Command functions

-----------------------------------------------------------*/

#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBATTLE_COMMAND

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#define EXTERN_CRBATTLE
#include "..\CrBase.h"
#include "..\CrBattle.h"

#define CR_GAMEINFO_EXTERNPOINTER
#include "..\CrGameInfo.h"

static eistr BattleCommandString[1024];
static eistr *pBattleMenuString[] =
{
	"����U��","���@","�h��","�A�C�e��","�K�E�Z","�ҋ@"
};

static eistr *pBattleMenuSubItem[4][5] = 
{
	{"����P","����Q","�f��"},
	{"���@","�K�E�Z"},
	{"�h��","���","���@�h��","�ړ�"},
	{"�A�C�e��"}
};

static int BattleMenuItemCount[5] = 
{
	2,2,4,1,2
};

static int BattleMenuItemStringLength[5] = 
{
	24,10,12,10,24
};

typedef struct
{
	float Angle,Speed;
	ei_s32 Fade,Ramp;
	ei_s32 LastTime,StartTime,Camera,Mode;
	CrBattleCharacter *pChara;
} BATTLE_INPUT_BATORRUN;

//---�^�[�Q�b�g
typedef struct
{
	ei_s32 Range,SelectMode,SelectRange[4];
	CrBattleCharacter **ppList;
	CrBattleCharacter *pActionChara;//---�s���L�����N�^�[
} BATTLE_TARGETINFO;

int crbatCommandRotate_SelectCallBack(CrSelectWindow *pwin,eiCell *pCell,int Message,ei_u32 Param1,ei_u32 Param2,int Param3);
CRBATCOMMAND_API int crbatInputBattleOrRunaway(int first,BATTLE_INPUT_BATORRUN *pInfo,int set_data_only = 0,int reset_angle = 1,int not_command = 0);

extern int TargetField[BATTLEFIELD_MAX_X][BATTLEFIELD_MAX_Y];

//---�^�[�Q�b�g�L����
int crbatGetTarget_DrawRange(BATTLE_TARGETINFO *pTarInfo,CrBattleCharacter *pActionChara,CrBattleCharacter *pChara)
{
	int a;
		int x,y;
	CrBattleCharacter *pList[BATTLECHARA_MAX + 1];

	memset(&pList[0],0,sizeof(pList));

	crbatDrawRadar();

	if(pTarInfo->Range & BAT_TARGET_SINGLETARGET){
		//---�V���O���^�[�Q�b�g
		crbatDrawRadar_Cursor(pChara);
	} else if(pTarInfo->Range & BAT_TARGET_RANGETARGET){
		//---�����W�^�[�Q�b�g
		//---�L�����N�^�[����
		crbatGetTargetChara(pActionChara,pChara,pTarInfo->Range,&pList[0]);
		//---�͈͕\��
		for(y = 0;y < BATTLEFIELD_MAX_Y;y ++){
			for(x = 0;x < BATTLEFIELD_MAX_X;x ++){
				if(TargetField[x][y])
					crbatDrawRadar_Range(x,y);
			}
		}
		//---����ɂЂ�������L�����N�^�[
		for(a = 0;a < BATTLECHARA_MAX;a ++){
			if(pList[a]){
				crbatDrawRadar_Cursor(pList[a]);
			}
		}
	} else if(pTarInfo->Range & BAT_TARGET_ALLTARGET){
		//---�I�[���^�[�Q�b�g
		for(a = 0;a < BATTLECHARA_MAX;a ++){
			if(((pTarInfo->Range & BAT_TARGET_FRIENDALL) && a < BATTLECHARA_PARTY_MAX)
				|| ((pTarInfo->Range & BAT_TARGET_ENEMYALL) && a >= BATTLECHARA_STARTENEMY)){
				if(pBtChara[a].DoExist()){
					crbatDrawRadar_Cursor(&pBtChara[a]);
				}
			}
		}
	}

	return 1;
}


//---�R�[���o�b�N
int crbatGetTarget_SelectCallBack(CrSelectWindow *pwin,eiCell *pCell,int Message,ei_u32 Param1,ei_u32 Param2,int Param3)
{
	int *pPage = (int *)Param1;
	CrBattleCharacter *pChara;
	BATTLE_TARGETINFO *pTarInfo;

	if(Message == CRWIN_SELECT_MESMOVECURSOR){
		//---�J�[�\���ړ�
		pTarInfo = (BATTLE_TARGETINFO *)Param2;
		pChara = pTarInfo->ppList[Param3];

		crbatGetTarget_DrawRange(pTarInfo,pTarInfo->pActionChara,pChara);
		if(crsysGetScreenMode() == 1){
			int old = eiEnableCheckThread(0);
			ew->Refresh();
			eiEnableCheckThread(old);

//			crbatDrawRefresh();
		} else {
			RECT rect = { BATTLE_RADAR_X, BATTLE_RADAR_Y ,
				BATTLE_RADAR_X + 13 * 16,BATTLE_RADAR_Y + 13 * 16};
			ew->lpCell[1]->PutClip(
				ew->lpCell[0],BATTLE_RADAR_X,BATTLE_RADAR_Y,&rect);
		}

		return 1;
	}
	if(Message == CRWIN_SELECT_MESSHOWHELP){
		//---�w���v�\��
		int index = Param3;
		pTarInfo = (BATTLE_TARGETINFO *)Param2;

		return 1;
	} else if(Message == CRWIN_SELECT_MESCHANGEPAGE){
		//---�y�[�W�؂�ւ��i�͈͑I���j
		pTarInfo = (BATTLE_TARGETINFO *)Param2;

		int mode = pTarInfo->SelectMode;
		mode ++;
		mode &= 1;
		if(pTarInfo->SelectRange[mode] == -1)
			mode = 0;

		pTarInfo->Range = pTarInfo->SelectRange[mode];
		pTarInfo->SelectMode = mode;
		crsoundPlay(CRSOUND_BTN_B);
		return 1;
	} else if(Message == CRWIN_SELECT_MESPAINT){
	}

	//---�������Ȃ������ꍇ
	return 0;
}

//---�^�[�Q�b�g�T�u����
int crbatGetTargetSub(CR_BATTLECOMMAND *pCommand,CrBattleCharacter *pChara,
					int option,eistr *string,
					CrBattleCharacter **ppList,
					int *width,int *height,int *win_width)
{
	int a,ret = 0,index,length = 0;
	eistr *p = string,temp1[16],temp2[16],temp3[16];
	int col[2];
	int table[] = {0,0,4,1,6,3,5,7,2};
	int select_mode = option;

	*width = 1;
	*win_width = 0;

	//---�I���\�I�u�W�F�N�g���X�g�����
	if(select_mode & BAT_TARGET_ME){
		index = 0;
		ppList[index] = pChara;
		sprintf(p,"%s;",pChara);
		if(*win_width <= (int)strlen(p))
			*win_width = (int)strlen(p) / 2;
		p += strlen(p);
		*p = NULL;

		index ++;
	}

	for(a = 0,index = 0;a < BATTLECHARA_MAX;a ++){
		if(a < CHARA_ENEMY){
			if((select_mode & BAT_TARGET_FRIEND) && pBtChara[a].DoExist()){
				ppList[index] = &pBtChara[a];
				index ++;
				//---���O
				if(!(select_mode & BAT_TARGET_ALLTARGET)){
					col[0] = crcharaGetStatusColor(pBtChara[a].GetLP(),pBtChara[a].GetMaxLP());
					col[1] = crcharaGetStatusColor(pBtChara[a].GetMC(),pBtChara[a].GetMaxMC());
					col[0] -= 16;
					col[1] -= 16;
					col[0] = table[col[0]];
					col[1] = table[col[1]];

					length = crbatGetBattleStatusString(&pBtChara[a],temp1);
					length = crbatGetBattlePlusStatusString(&pBtChara[a],temp2,length);
					crbatGetBattleResultStatusString(&pBtChara[a],temp3,length);

					sprintf(p,"%-11s \\%d%4d/\\7%4d \\%d%4d/\\7%4d  \\7%s\\4%s\\7%s;",
						pBtChara[a].GetName(),
						col[0],pBtChara[a].GetLP(),pBtChara[a].GetMaxLP(),
						col[1],pBtChara[a].GetMC(),pBtChara[a].GetMaxMC(),
						temp1,temp2,temp3);
					if(*win_width <= (int)strlen(p))
						*win_width = (int)strlen(p) / 2;
					p += strlen(p);
					*p = NULL;
				}
			}
		} else {
			if((select_mode & BAT_TARGET_ENEMY) && pBtChara[a].DoExist()){
				ppList[index] = &pBtChara[a];
				index ++;
				//---���O
				if(!(select_mode & BAT_TARGET_ALLTARGET)){
					sprintf(p,"%s;",pBtChara[a].GetName());
					if(*win_width <= (int)strlen(p))
						*win_width = (int)strlen(p) / 2;
					p += strlen(p);
					*p = NULL;
				}
			}
		}
	}

	*height = 3 + ((index / (*width)) * 20 / 16);

	if(select_mode & BAT_TARGET_ALLTARGET){
		//---�͈͂��S��
		*height = 4;
		if(select_mode & BAT_TARGET_FRIENDALL){
			sprintf(p,"�����S��;");
			p += strlen(p);
			*p = NULL;
		} else if(select_mode & BAT_TARGET_ENEMYALL){
			sprintf(p,"�G�S��;");
			p += strlen(p);
			*p = NULL;
		}
	}

	if(index >= 6){
		*width = 2;
		(*height) /= 2;
		(*height) += 2;
	}
	if(*win_width <= 14)
		*win_width = 14;

	return index;
}

//---�^�[�Q�b�g�I��
int crbatGetTarget(CR_BATTLECOMMAND *pCommand,CrBattleCharacter *pChara,
					int option = 0,int option2 = -1)
{
	int /*a,*/ret = 0,index;
	int width = 1,height,win_width = 0;
	CrBattleCharacter *pList[BATTLECHARA_MAX + 1];
	BATTLE_TARGETINFO TarInfo;
	static eistr string[1024]; 
	eistr *p = &string[0];
//	int col[2];
	int table[] = {0,0,4,1,6,3,5,7,2};
	int select_mode = option;

	//---�ϐ�������
	memset(&TarInfo,0,sizeof(TarInfo));
	memset(&pList[0],0,sizeof(pList));
	memset(&string[0],0,sizeof(string));

	TarInfo.ppList = &pList[0];
	TarInfo.Range = select_mode;
	TarInfo.pActionChara = pChara;
	TarInfo.SelectMode = 0;
	TarInfo.SelectRange[0] = option;
	TarInfo.SelectRange[1] = option2;
	TarInfo.SelectRange[2] = -1;

	index = crbatGetTargetSub(pCommand,pChara,select_mode,
		&string[0],&pList[0],&width,&height,&win_width);

	CrSelectWindow win;
	crbaseMenuReset();
	win.Create(
		BATTLE_COMMAND_LEFT + 64,BATTLE_COMMAND_TOP,
		/*14 * width*/win_width * width,height,"�Ώ�",
		string,width,(1 * win_width - 3) * 2/*22*/);
	win.SetSelectCallBack(crbatGetTarget_SelectCallBack);
	win.SetData((ei_u32)&TarInfo);//&pList[0]);
	if(option2 != -1){
		ew->lpCell[1]->DrawText("�����͈͐؂�ւ�",
			win.GetPosX() + 64 + 1,win.GetPosY() + 1,ep->ToTextRGB(CRCOLOR_BLACK));
		ew->lpCell[1]->DrawText("�����͈͐؂�ւ�",
			win.GetPosX() + 64,win.GetPosY(),ep->ToTextRGB(CRCOLOR_YELLOW));
	} else if((select_mode & BAT_TARGET_FRIEND) && !(select_mode & BAT_TARGET_FRIENDALL)){
		//---�����^�[�Q�b�g�ŁA�S�͈̔͂łȂ�
		ew->lpCell[1]->DrawText("LP/Max    MC/Max",
			win.GetPosX() + 136 + 1,win.GetPosY() + 1,ep->ToTextRGB(CRCOLOR_BLACK));
		ew->lpCell[1]->DrawText("LP/Max    MC/Max",
			win.GetPosX() + 136 ,win.GetPosY(),ep->ToTextRGB(CRCOLOR_YELLOW));
	}
	win.Refresh();

	crbaseMenuStart();
	ret = win.Select();

	if(ret != -1){
		pCommand->Target = (ei_u32)(pList[ret]);
		pCommand->Range = TarInfo.SelectRange[TarInfo.SelectMode];
		pCommand->Sub[CRBAT_SUBTARGET] = TarInfo.SelectMode;
//		pChara->SetTarget(pList[ret]);
	}

	//---�Q�c�t�B�[���h�ĕ`��
	crbatDrawRadar();
	crbatDrawRadar_Cursor(pChara);

	return ret;
}

//---�R�}���h���j���[����������
int crbatMakeMenuCommand(CrBattleCharacter *pChara,CR_BATTLECOMMAND *pCommand)
{
	int a;
	eistr *pString = &BattleCommandString[0];

	for(a = 0;a < 4 + (pChara->SpecialEnableUse() ? 1 : 0) - crbatGetBattleItemMode();
				a ++){
		if(a < 4 - crbatGetBattleItemMode()){
			if(a == 0 && !pChara->IsEnableMoveing()){
				//---�����s�����Ƃ�Ȃ�������ҋ@��\��
				sprintf(pString,"%-12s;",
					pBattleMenuString[5]);
			} else {
				sprintf(pString,"%-12s;",
					pBattleMenuString[a]);
			}
		} else {
			int index = pChara->GetEnableSpecial();
			CrSpecial *psp = &pSpecialInfo[index];
			//---�K�E�Z
			sprintf(pString,"%-20s;",
				psp->GetName());
		}
		pString += strlen(pString);
		*pString = NULL;
	}

	return a;
}

//---�t�B�[���h��ő��̃L�����N�^�[������ꏊ������
void crbatCalcFieldCharacter(ei_s32 *pField)
{
}

//---�ړ���I��
CRBATCOMMAND_API int crbatGetCharacterCommandDefenseMove(
								CR_BATTLECOMMAND *pCommand,
								CrBattleCharacter *pChara)
{
	int x,y,cx = pChara->GetFieldX(),cy = pChara->GetFieldY();
	ei_s32 field[BATTLEFIELD_MAX_X][BATTLEFIELD_MAX_Y];
	float dis;
	memset(&field[0][0],0,sizeof(field));

	crbaseMenuReset();

	//---�ړ��\�͈͂𒲂ׂ�
	for(y = 0;y < BATTLEFIELD_MAX_Y;y ++){
		for(x = 0;x < BATTLEFIELD_MAX_X;x ++){
			dis = (float)sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy));
			if(dis <= (float)pChara->GetBtMove()){
				//---�ړ��\�͈͂Ȃ�
				field[x][y] = 1;
			}
		}
	}
	//---���̃L�����N�^�[������ꏊ������
	crbatCalcFieldCharacter(&field[0][0]);
	int a;
	for(a = 0;a < BATTLECHARA_MAX;a ++){
		if(pBtChara[a].DoExist()){
//			*(pField + pBtChara[a].GetFieldX() + pBtChara[a].GetFieldY() * BATTLEFIELD_MAX_X)
//				= 0;
			field[pBtChara[a].GetFieldX()][pBtChara[a].GetFieldY()] = 0;
		}
	}
	//---�����̂Ƃ���͓�����
	field[pChara->GetFieldX()][pChara->GetFieldY()] = 1;

	memcpy(&TargetField[0][0],&field[0][0],sizeof(TargetField));
	for(y = 0;y < BATTLEFIELD_MAX_Y;y ++){
		for(x = 0;x < BATTLEFIELD_MAX_X;x ++){
			if(field[x][y])
				crbatDrawRadar_Range(x,y);
		}
	}

//	crbatDrawRadar_Range(pChara->GetFieldX(),pChara->GetFieldY());
//	crbatDrawRefresh();
	ew->Refresh();

	crbaseMenuStart();

	//---�I��
	//---����ǂ�
	CrBattleCharacter *ptempobj = &pBtTempChara[0];
	memcpy(&ptempobj->BattleInfo,&pChara->BattleInfo,sizeof(ptempobj->BattleInfo));
	memcpy(&ptempobj->OnlyInfo,&pChara->OnlyInfo,sizeof(ptempobj->OnlyInfo));

	int ret = 0,hx,hy,ax,ay;
	x = hx = pChara->GetFieldX();
	y = hy = pChara->GetFieldY();
	CrInput crin;
	crin.Get();
	et->Reset();
	while(1){
		crin.Get();

		if(crin.IsButton(0)){
			crsoundPlay(CRSOUND_BTN_A);
			ret = 0;
			break;
		}
		if(crin.IsButton(1)){
			crsoundPlay(CRSOUND_BTN_B);
			pCommand->Sub[1] = x;
			pCommand->Sub[2] = y;
			ret = 1;
			break;
		}
		//---
		ax = ay = 0;
		if(crin.IsUp()){
			y --;
			ay = -1;
		} else if(crin.IsDown()){
			y ++;
			ay = 1;
		} else if(crin.IsLeft()){
			x ++;
			ax = 1;
		} else if(crin.IsRight()){
			x --;
			ax = -1;
		}

		//----���W�␳
		//---�y�[�W�؂�ւ����������Ȃ������ꍇ
		while(x < 0 || x >= BATTLEFIELD_MAX_X
			|| y < 0 || y >= BATTLEFIELD_MAX_Y
			|| field[x][y] == 0){
			x += ax;
			y += ay;
			if(x < 0){
				for(x = BATTLEFIELD_MAX_X - 1;
					x >= 0 && field[x][y] == 0;x --);
			} else if(x >= BATTLEFIELD_MAX_X){
				for(x = 0;
					x < BATTLEFIELD_MAX_X && field[x][y] == 0;x ++);
			}
			if(y < 0){
				for(y = BATTLEFIELD_MAX_Y - 1;
					y >= 0 && field[x][y] == 0;y --);
			} else if(y >= BATTLEFIELD_MAX_X){
				for(y = 0;
					y < BATTLEFIELD_MAX_X && field[x][y] == 0;y ++);
			}
//			x = hx;
//			y = hy;
		}

		if(hx != x || hy != y){
			//---��������
			//---�O�̈ʒu������
			crbatDrawRadar();
			int sx,sy;
			for(sy = 0;sy < BATTLEFIELD_MAX_Y;sy ++){
				for(sx = 0;sx < BATTLEFIELD_MAX_X;sx ++){
					if(field[sx][sy]){
						crbatDrawRadar_Range(sx,sy);
					}
				}
			}
			ptempobj->SetFieldPos(x,y);

			crbatDrawRadar_Cursor(ptempobj);
			crbatDrawRefresh();
//			ew->Refresh();
		}

		hx = x;
		hy = y;

		eiSleep(1);
	}

	//---�Q�c�t�B�[���h�ĕ`��
	crbatDrawRadar();
	crbatDrawRadar_Cursor(pChara);

	return ret;
}

//---�h��I��
CRBATCOMMAND_API int crbatGetCharacterCommandDefense(
								CR_BATTLECOMMAND *pCommand,
								CrBattleCharacter *pChara)
{
	int ret = 0;
	CrSelectWindow win;

	if(!pChara->IsEnableMoveing()){
		crsoundPlay(CRSOUND_BEEP_1);
		return -1;
	}

	crbaseMenuReset();
	memset(&pChara->GetCharacterInfo()->BattleDefenseSubItem,0,sizeof(pChara->GetCharacterInfo()->BattleDefenseSubItem));

	do {
		win.Create(
			BATTLE_COMMAND_LEFT + 32,
			BATTLE_COMMAND_TOP,
			2 + BattleMenuItemStringLength[pCommand->Main] / 2,
			3 + ((20 * BattleMenuItemCount[pCommand->Main]) / 16),
			pBattleMenuString[pCommand->Main],
			"�h��;���;���@�h��;�ړ�;");
		win.Refresh();
		crbaseMenuStart();

		pCommand->Sub[0] = ret = win.Select(
			&pChara->GetCharacterInfo()->BattleDefenseSubItem);

		if(pCommand->Sub[0] == BAT_SUBCOM_MOVE){
			if(!crbatGetCharacterCommandDefenseMove(pCommand,pChara)){
				continue;
			}
		}

		crbaseMenuReset();
		break;
	} while(1);


	return ret;
}

//---����I��
CRBATCOMMAND_API int crbatGetCharacterCommandWeapon(
								CR_BATTLECOMMAND *pCommand,
								CrBattleCharacter *pChara,
								int mode,int force_range)
{
	int a;
	CrSelectWindow win;
	eistr string[100],*p = &string[0];
	CRWIN_SELECTINFO *pInfo;

	pInfo = &pChara->GetCharacterInfo()->BattleAtackSubItem;
	if(mode != 0){
		pInfo = NULL;
	}

	if(!pChara->IsEnableMoveing()){
		crsoundPlay(CRSOUND_BEEP_1);
		return -1;
	}

	crbaseMenuReset();

	if(pChara->IsWeaponEnableToAtack(0,mode) == 0 && pChara->IsWeaponEnableToAtack(1,mode) == 0){
		//---�f��
		sprintf(p,"�f��;");
	} else if(pChara->IsWeaponEnableToAtack(0,mode) && pChara->IsWeaponEnableToAtack(1,mode)){
		for(a = 0;a < BattleMenuItemCount[pCommand->Main];a ++){
			sprintf(p,"%s;",
				critemGetItemClass(pChara->GetWeapon(a))->GetName());
			p += strlen(p);
			*p = NULL;
		}
	} else {
		if(pChara->IsWeaponEnableToAtack(0,mode)){
			sprintf(p,"%s;",
				critemGetItemClass(pChara->GetWeapon(0))->GetName());
		} else {
			sprintf(p,"%s;",
				critemGetItemClass(pChara->GetWeapon(1))->GetName());
		}
	}

/*	for(a = 0;a < BattleMenuItemCount[pCommand->Main];a ++){
		sprintf(p,"%s;",
			pChara->GetWeapon(a)
			? critemGetItemClass(pChara->GetWeapon(a))->GetName() : "�f��");
		p += strlen(p);
		*p = NULL;
	}*/

	//---�I��
	int ret = 0,target = -1,range,force_select_range = 0;
	while(1){
		crbaseMenuReset();

		win.Create(
			BATTLE_COMMAND_LEFT + 32,
			BATTLE_COMMAND_TOP,
			2 + BattleMenuItemStringLength[pCommand->Main] / 2,
			3 + ((20 * BattleMenuItemCount[pCommand->Main]) / 16),
			pBattleMenuString[pCommand->Main],string);
		win.Refresh();
		crbaseMenuStart();

		pCommand->Sub[0] = ret = win.Select(pInfo);

		if(pChara->IsWeaponEnableToAtack(0,mode) == 0 && pChara->IsWeaponEnableToAtack(1,mode)){
			//---���j���[�␳
			if(ret == 0)
				pCommand->Sub[0] = ret = 1;
		}

		if(!force_range 
			&& critemGetItemClass(pChara->GetWeapon(pCommand->Sub[0]))->GetTarget() != BAT_TARGET_ENEMYSINGLE){
			//---����̃^�[�Q�b�g���G��̈ȊO�Ȃ�
			force_select_range = 
				/*force_range = */critemGetItemClass(pChara->GetWeapon(pCommand->Sub[0]))->GetTarget()
				| critemGetItemClass(pChara->GetWeapon(pCommand->Sub[0]))->GetRange(); 
		}

		if(ret != -1){
			//---�U���Ώۃ^�[�Q�b�g�I��
			range = pCommand->Range = BAT_TARGET_ENEMYSINGLE;
			if(force_select_range){
				range = pCommand->Range = force_select_range;
				//---����ω��̂��߁A�����߂�
				force_select_range = 0;
			}
			if(force_range){
				range = pCommand->Range = force_range;
			}
			target = crbatGetTarget(pCommand,pChara,
				range/*�����ŕ���ɂ��I��͈͂̕ω�*/);
			if(target == -1)
				continue;
		}
		break;
	}
	
	return ret;
}

//---���@�I��
CRBATCOMMAND_API int crbatGetCharacterCommandMagic(
				CR_BATTLECOMMAND *pCommand,CrBattleCharacter *pChara,
				int select_target)
{
	int a,ret = 0,target = -1,range[2];
	int world = crmagicGetMagicClass(24)->GetMC();

	if(!pChara->IsEnableMagic()){
		crsoundPlay(CRSOUND_BEEP_1);
		return -1;
	}

	for(a = 0;a < pChara->GetWorldCountTurn();a ++){
		crmagicGetMagicClass(24)->MagicInfo.UseMC += world;
	}

	while(1){
		pCommand->Sub[0] = ret = crmagicSelectCharacterMagic(
			pChara,1,
			64,BATTLE_COMMAND_TOP,10,2,
			CRMATERIAL_KIND_MAGICMC,0,0,0,
			1);
		pCommand->Sub[1] = 0;//---�P�O�O���q�b�g

		CrMagic *pMagic = crmagicGetMagicClass(0);
		if(ret != -1){
			pMagic = crmagicGetMagicClass(ret);
		}

		if(crmagicIsUseMagic(pChara,ret,1)
			&& (select_target == 1
				|| (select_target == 0 && ((pMagic->GetTarget(0) | pMagic->GetRange(0)) & BAT_TARGET_ENEMY))
				)
			){
			//---�I���������@���g����Ȃ�
			//---���@�̑Ώ�
			range[0] = pCommand->Range = 
				crmagicGetMagicClass(ret)->GetTarget(0) | crmagicGetMagicClass(ret)->GetRange(0); 
			range[1] = crmagicGetMagicClass(ret)->GetTarget(1) | crmagicGetMagicClass(ret)->GetRange(1); 
			//---�T�u�^�[�Q�b�g����
			if(range[1] == 0)
				range[1] = -1;
			//---�Ώۃ^�[�Q�b�g�I��
			if((range[0] & BAT_TARGET_ME) || select_target == 0){
				//---����
				pCommand->Target = (ei_u32)(pChara);
				range[0] = BAT_TARGET_ME;
				pCommand->Range = range[0];
				pCommand->Sub[CRBAT_SUBTARGET] = 0;
				target = 1;
			} else {
				target = crbatGetTarget(pCommand,pChara,range[0],range[1]);
			}
			if(target == -1)
				continue;

			break;
		} else {
			if(ret != -1){
				crsoundPlay(CRSOUND_BEEP_1);
			} else {
				//---�L�����Z�����ꂽ
				ret = -1;
				break;
			}
		}
	}

	crmagicGetMagicClass(24)->MagicInfo.UseMC = world;

	return ret;
}

//---�A�C�e���I��
CRBATCOMMAND_API int crbatGetCharacterCommandItem(
				CR_BATTLECOMMAND *pCommand,CrBattleCharacter *pChara)
{
	int ret,target,range;

	if(!pChara->IsEnableMoveing()){
		crsoundPlay(CRSOUND_BEEP_1);
		return -1;
	}
	while(1){
		pCommand->Sub[0] = ret = critemSelectItem(
			48,BATTLE_COMMAND_TOP,10,2,
			CRMATERIAL_KIND_ITEMCOUNT,0,0,0,
			1,&pGameInfo->BattleSelectItem);

		if(!critemIsUseItem(ret,1)){
			//---�A�C�e�����g���Ȃ����
			if(ret != -1){
				crsoundPlay(CRSOUND_BEEP_1);
			}
			return -1;
		}
		if((221 <= ret && ret <= 229)
			|| (231 <= ret && ret <= 240)
			|| (244 <= ret && ret <= 245)){
			//---���C�t�J�v�Z���`���P�V�X�̓V��
			//---�`��������������
			range = BAT_TARGET_FRIENDSINGLE;
			target = crbatGetTarget(pCommand,pChara,range);
			if(target != -1){
				return ret;
			}
		}
		if(246 == ret){
			//---����������
			range = BAT_TARGET_ENEMYSINGLE;
			target = crbatGetTarget(pCommand,pChara,range);
			if(target != -1){
				return ret;
			}
		}
	}
	return ret;
}

//---�K�E�Z
CRBATCOMMAND_API int crbatGetCharacterCommandSpecial(
				CR_BATTLECOMMAND *pCommand,CrBattleCharacter *pChara)
{
	int ret = 0/*,target,range*/;
	int index = pChara->GetEnableSpecial();
	CrSpecial *psp;

	psp = &pSpecialInfo[index];

	if(!pChara->IsEnableMoveing()){
		if(!(index == 3 || index == 4)){
			//---�������A�J�E���^�[�Q�[�g�ł͂Ȃ�
			crsoundPlay(CRSOUND_BEEP_1);
			return -1;
		}
	}
	if((index == 3 || index == 4)){
		if(!pChara->IsEnableMagic()){
			crsoundPlay(CRSOUND_BEEP_1);
			return -1;
		}
	}

	if(psp->GetCommandType() == 0){
		//---����K�E�Z
		int kind = psp->GetWeaponKind();

		if(kind == 3){
//		if(kind != 3){
			//---�U���Ώۃ^�[�Q�b�g�I��
			pCommand->Sub[0] = 0;

			CrSelectWindow win;
			crbaseMenuReset();
			win.Create(
				BATTLE_COMMAND_LEFT + 32,
				BATTLE_COMMAND_TOP,
				14,
				4,
				"","�����̕�����g���܂�;");
			win.Refresh();
			crbaseMenuStart();
			int sub_ret = win.Select();
			if(sub_ret == -1){
				return -1;
			}

			int range = pCommand->Range = BAT_TARGET_ENEMYSINGLE;
			int target = crbatGetTarget(pCommand,pChara,range);

			if(target == -1)
				return -1;
		} else {
			ret = crbatGetCharacterCommandWeapon(pCommand,pChara,
				kind,psp->GetRange() | psp->GetTarget());
		}
	} else if(psp->GetCommandType() == 1){
		int select_target = 1;
		if(index == 4){
			select_target = 0;
		}
		ret = crbatGetCharacterCommandMagic(pCommand,pChara,select_target);
	} else {
		ret = crbatGetTarget(pCommand,pChara,
			psp->GetRange() | psp->GetTarget());
	}

	//---�g�p�K�E�Z�L��
	pCommand->Sub[BAT_SUBCOM_SPECIALNUMBER] = index;

	if(ret == -1){
		//---�L�����Z��
		return -1;
	}

	return ret;
}

//---�L�����N�^�[�R�}���h�I�����R�[���o�b�N
int crbatCommand_CharaCommandCallBack(
	CrSelectWindow *pwin,eiCell *pCell,int Message,ei_u32 Param1,ei_u32 Param2,int Param3)
{
	if(Message == CRWIN_SELECT_MESCHANGEPAGE){
		BATTLE_INPUT_BATORRUN *pInfo = (BATTLE_INPUT_BATORRUN *)Param2;

		eiTime let;
		let.Reset();

		ei->Get();
		while(let.Get() <= 150){
			ei->Get();

			if(!(ei->Input[0].Left || ei->Input[0].Right)){
				return 0;
			}
		}

		//---�y�[�W�؂�ւ�
		crbatSetViewMode(BATTLE_VIEWMODE_SINGLE);

		crbatClearDrawingList();
		crbatAddDrawingListAll();

		crbatInputBattleOrRunaway(0,NULL,0,1,1);

		//---���X�g�ɖ����݂̂�o�^
		crbatClearDrawingList();
		crbatAddDrawingListFriend();

		pInfo->pChara->SetCameraFront();

		//---�`��
		crbatDraw_Clear();
		crbatSetViewMode(BATTLE_VIEWMODE_HALF);

		//---�y�N���b�v��ݒ�
		{
			float old = crbatSetDrawingZClip(0.90f);
			crbatClearDrawingList();
			crbatAddDrawingListFriend();
			crbatDrawScene();
			crbatDrawRadar();
			crbatDrawRadar_Cursor(pInfo->pChara);
			crbatSetDrawingZClip(old);

			crbatClearDrawingList();
			crbatAddDrawingListFriend();
		}

		ew->Refresh();
		ew->Refresh();

		crbaseMenuReset();
		crbaseMenuStart();

		return 1;
	}

	return 0;
}

//---�L�����N�^�[�̃R�}���h����
CRBATCOMMAND_API int crbatGetCharacterCommand(CrBattleCharacter *pChara,int cansel)
{
	int res,sub = -1,max;
	CrSelectWindow win;
	CR_BATTLECOMMAND Command;

	//------------
	BATTLE_INPUT_BATORRUN Info;

	memset(&Command,0,sizeof(Command));

	Info.Angle = ANGLE(180);
	Info.Speed = 0.0004f;
	Info.Camera = 0;
	Info.Mode = 1;
	Info.pChara = pChara;
	Info.Fade = 0;

	//---�R�}���h���͂ł��Ȃ���Ԃ�������
	if(!pChara->IsEnableCommandInput())
		return 0;

	if(cansel && crdataGetSystem()->BattleCommandReset == 0){
		//---�^�[�����ƃ��Z�b�g
		//---�L�����Z���Ŗ߂��Ă�����R�}���h���Z�b�g
		memset(&pChara->GetCharacterInfo()->BattleMenuCursor,0,
			sizeof(pChara->GetCharacterInfo()->BattleMenuCursor));
	}

	while(sub == -1){
		memset(&Command,0,sizeof(Command));

		//---���j���[�A�C�e���R�s�[
		max = crbatMakeMenuCommand(pChara,&Command);

		//---��ʕ`��
		crbatDraw_ClearMenuArea();
		crbatShowStatus();

		if(max == 4 - crbatGetBattleItemMode()){
			win.Create( BATTLE_COMMAND_LEFT,BATTLE_COMMAND_TOP,11,8,
				pChara->GetName(),BattleCommandString,1,10);
		} else {
			win.Create( BATTLE_COMMAND_LEFT,BATTLE_COMMAND_TOP,16,9,
				pChara->GetName(),BattleCommandString,1,20);
		}
		win.SetSelectCallBack(crbatCommand_CharaCommandCallBack);
		win.SetData((ei_u32)&Info);

		ew->Refresh();
//		crbatDrawRefresh();
		crbaseMenuStart();

		Info.LastTime = et->GetTime();
		res = win.Select(&pChara->GetCharacterInfo()->BattleMenuCursor);
		if(!pChara->IsEnableMoveing()){
			//---�����I�s���s�\
			if(res == 0){
				res = BAT_COMMAND_WAIT;
				sub = 0;
			}
		}
		if(crbatGetBattleItemMode() == 1){
			if(res == 3)
				res = 4;
		}
		Command.Main = res;

		crbatDraw_CopyScreen();

		if(res == -1){
			//---�L�����Z��
			return res;
		}
		if(res == 0){
			//---�T�u�A�C�e���I��
			sub = crbatGetCharacterCommandWeapon(&Command,pChara,0,0);
		} else if(res == 1){
			//---���@�I��
			sub = crbatGetCharacterCommandMagic(&Command,pChara,1);
		} else if(res == 2){
			//---�h��I��
			sub = crbatGetCharacterCommandDefense(&Command,pChara);
		} else if(res == 3){
			//---�A�C�e���I��
			sub = crbatGetCharacterCommandItem(&Command,pChara);
		} else if(res == 4){
			//---�K�E�Z
			sub = crbatGetCharacterCommandSpecial(&Command,pChara);
		}
		crbaseMenuReset();
	}

	pChara->Command = Command;

//	//---�R�s�[������
//	memcpy(&pChara->CharaInfo.BattleMenuItem[0],&CommandMenu.MenuItem[0],sizeof(CommandMenu.MenuItem[0]));

	return 1;
}

//---���邭��܉�
int crbatCommandRotate_SelectCallBack(CrSelectWindow *pwin,eiCell *pCell,int Message,ei_u32 Param1,ei_u32 Param2,int Param3)
{
	int AddWorld,Now;
	BATTLE_INPUT_BATORRUN *pInfo = (BATTLE_INPUT_BATORRUN *)Param2;

	if(crsysGetExtentionLevel() < 3){
		//---�O���t�B�b�N���x�����Ⴏ���
		if(pInfo->Fade == 1){
			pInfo->Fade = 0;
			crbatSetBattleLight(RGBA_MAKE(255,255,255,255));

			int old = eiEnableCheckThread(0);
			crbatDrawScene();
			eiEnableCheckThread(old);

			if(crsysGetScreenMode() == 0){
				RECT rect = BattleViewRect[BattleViewMode][0];

				rect.right += rect.left;
				rect.bottom += rect.top;
				ew->lpCell[1]->PutClip(ew->lpCell[0],rect.left,rect.top,&rect);
			} else {
//				crbatDrawRefresh();
				int old = eiEnableCheckThread(0);
				ew->Refresh();
				eiEnableCheckThread(old);
			}
		}
		return 0;
	}

	if(Message == CRWIN_SELECT_IDLE){
		Now = et->GetTime();
		AddWorld = Now - pInfo->LastTime;
		pInfo->LastTime = Now;

		if(pInfo->Fade == 1){
			int Color = (int)((float)(Now - pInfo->StartTime) / (float)1000 * 255);
			if(Now - pInfo->StartTime > 1000)
				Color = 255;

			crbatSetBattleLight(RGBA_MAKE(Color,Color,Color,255));
		}

		pInfo->Angle += (float)((float)AddWorld * (pInfo->Speed));
		if(pInfo->Mode == 0){
			crbatSetCamera_ViewBattleField(pInfo->Camera,pInfo->Angle);
		} if(pInfo->Mode == 1){
			pInfo->pChara->SetCameraAngle(pInfo->Angle,5.0f,pInfo->Camera);
		}

crdataEnableRec(0);
		int old = eiEnableCheckThread(0);
		crbatDrawScene();
		eiEnableCheckThread(old);

		if(crsysGetScreenMode() == 0){
			RECT rect = BattleViewRect[BattleViewMode][0];

			rect.right += rect.left;
			rect.bottom += rect.top;
//			ew->lpCell[1]->PutClip(ew->lpCell[0],rect.left,rect.top,&rect);

			eiDDSurface *pSurface = eiGetSurfacePointer();
			pSurface[1].PutExtend2(&pSurface[0],&rect,&rect,DDBLT_WAIT);
		} else {
			int old = eiEnableCheckThread(0);
			crbatDrawRefresh();
			eiEnableCheckThread(old);
//			ew->Refresh();
		}
crdataEnableRec(1);

		return 1;
	}

	return 0;
}

/*�����邱�Ƃ��o���邩*/
CRBATCOMMAND_API int crbatIsEnableRunaway(CR_BATTLEINFO *pInfo,int turn)
{
	int a,count,dlevel,prob;
	double plevel,elevel;

	if(!pInfo->EnebleAvoid)
		return 0;

	if(pInfo->OffsetBattle == BATSTART_SENSEI && turn == 0){
		return 1;
	}

	for(a = 0,plevel = 0,count = 0;a < 5;a ++){
		if(pBtChara[a].DoExist()){
			plevel += pBtChara[a].GetLevel();
			count ++;
		}
	}
	if(count){
		plevel /= count;
	}

	for(a = BATTLECHARA_STARTENEMY,elevel = 0,count = 0;a < BATTLECHARA_STARTENEMY + BATTLE_ENEMYMAX;a ++){
		if(pBtChara[a].DoExist()){
			elevel += pBtChara[a].GetLevel();
			count ++;
		}
	}
	if(count){
		elevel /= count;
	}
	dlevel = (int)(plevel - elevel + 0.5);
	
	if(dlevel < -5){
		prob = 20;
	} else if(dlevel > 5){
		prob = 95;
	} else {
		int prob_table[] = {25,32,39,46,53, 60, 66,72,78,84,90};
		prob = prob_table[dlevel + 5];
	}
	prob *= 10;

	if(count == 1){
		//---�G���P��
		prob = 1000 - ((1000 - prob) / 2);
	} else if(count >= 4){
		//---�G���S�̈ȏ�
		prob = prob * 3 / 2;
	}

	if(eiRnd(1000) < prob)
		return 1;

	return 0;
}

//---�키�������邩��I��
CRBATCOMMAND_API int crbatInputBattleOrRunaway(int first,BATTLE_INPUT_BATORRUN *pInfo,int set_data_only/*= 0*/,int reset_angle /*= 1*/,int not_command /*= 0*/)
{
	int ret;
	CrSelectWindow win;
	static BATTLE_INPUT_BATORRUN Info;

	int a,flag;
	for(a = 0,flag = 0;a < BATTLECHARA_PARTY_MAX;a ++){
		if(pBtChara[a].IsEnableEscape())
			flag ++;
	}
	if(!flag){
		//---�N�������\�łȂ���ΐ퓬�������s
		return 0;
	}

	memset(&Info,0,sizeof(Info));

	if(reset_angle || pInfo == NULL){
		Info.Angle = ANGLE(90);
	} else {
		Info.Angle = pInfo->Angle;
	}
	Info.Speed = 0.0004f;
	Info.Camera = 0;
	Info.Mode = 0;
	Info.Fade = first;
	Info.Ramp = 0;
	Info.StartTime = et->GetTime();

	if(set_data_only){
		//---���Z�b�g�̂�
		*pInfo = Info;
		return 0;
	}

	if(not_command == 0){
		do {
			crbaseMenuReset();
			win.Create(BATTLE_COMMAND_LEFT,BATTLE_COMMAND_TOP,
				10,5,"�ǂ�����H","�키;������;",1,10);
			win.SetData((ei_u32)&Info);
			win.SetSelectCallBack(crbatCommandRotate_SelectCallBack);
			win.Refresh();
			crbaseMenuStart();

			Info.LastTime = et->GetTime();
			ret = win.Select();

			Info.Fade = 0;
			crbatSetBattleLight(RGBA_MAKE(255,255,255,255));
#if(CR_DEBUG == 1)
			if(crdataGetDebug() && ret == -1){
				eiSleep(300);
				ei->Get();
				if(ei->Input[0].Button[1]){
					return ret;
				}
			}
#endif
			crbatDraw_CopyScreen();
		} while(ret == -1);

		if(pInfo != NULL){
			*pInfo = Info;
		}
	} else {
		eiTime let;

		ei->Get();
		let.Reset();

		while(1/*let.Get() < 10000*/){
			ei->Get();

			crbatCommandRotate_SelectCallBack(NULL,ew->lpCell[1],
				CRWIN_SELECT_IDLE,0,(ei_u32)&Info,0);

			if(let.Get() >= crdataGetSystem()->MenuWaitTime){
				if(!(ei->Input[0].Left || ei->Input[0].Right)){
					break;
				}
/*				if(ei->AnyKey){
					break;
				}*/
			}

			eiSleep(1);
		}
	}

	return ret;
}

static CrStringWindow InfoWindow(EINORMAL_FONT,CRWIN_BGFILL | /*CRWIN_FRAME |*/CRWIN_BGALPHA);
CRBATMAIN_API void crbatNotAvoidDrawSceneCallback(eiCell *pCell,int mode)
{
	if(mode == 0){
		InfoWindow.Paint();
		InfoWindow.Reset();
		InfoWindow.DrawLastString();
	}
}

//---�R�}���h����
CRBATCOMMAND_API int crbatInputCommand(int turn,CR_BATTLEINFO *pInfo)
{
	int a,member,cansel,first,party,view_mode = 0,battle_first;
	BATTLE_INPUT_BATORRUN BatOrRunInfo;

//	//---�S�����S�I
//	crbatSetCharaAngleToCenterAll();
	//---�S���̌�����␳
	crbatSetCharaAngleToRandomAll();
	do {
		//---�S�̕\��
//		crbatSetViewMode(BATTLE_VIEWMODE_SINGLE);
		crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);
		if(!turn && !view_mode){
			crbatSetCamera_ViewBattleField(0,ANGLE(90));
			battle_first = 1;
		} else {
			if(pInfo->lpTurnCallBack == NULL || pInfo->ForceInputCommand == 1){
				crbatSetCamera_ViewBattleField(0,ANGLE(90),1,500);
			}
			battle_first = 0;
		}
		view_mode = 1;
		crbatClearDrawingList();
		crbatAddDrawingListAll();
		for(a = 0;a < 2;a ++){
			crbaseClearScreen(2);
			if(!battle_first)
				crbatDrawScene();
			crbatShowStatus();

//			ew->Refresh();
			crbatDrawRefresh();
		}
		//---�키�������邩�̑I��
		if(pInfo->lpTurnCallBack != NULL && pInfo->ForceInputCommand == 0){
			//---�R�[���o�b�N����������
			crbatSetBattleLight(RGBA_MAKE(255,255,255,255));
			party = (*pInfo->lpTurnCallBack)(turn,0,0,0,NULL);
			if(party == 0){
				return BATRET_FORCEBREAK;
			}
			party = 0;
		} else if(turn == 0 && 
			(pInfo->OffsetBattle != BATSTART_NORMAL)){
			//---�I�t�Z�b�g�o�g��
			eistr *str = NULL;

			party = crbatInputBattleOrRunaway(battle_first,&BatOrRunInfo,1);

			if(pInfo->OffsetBattle == BATSTART_SENSEI){
				str = "�搧�U���̃`�����X";
			} else if(pInfo->OffsetBattle == BATSTART_FUIUCHI){
				str = "�s�ӑł����I";
			} else if(pInfo->OffsetBattle == BATSTART_BACKATACK){
				str = "�o�b�N�A�^�b�N�I�I";
			} else if(pInfo->OffsetBattle == BATSTART_HASAMIUCHI){
				str = "���݌��������ꂽ�I";
			}
			
			InfoWindow.SetType(CRWIN_TYPE_NORMAL);
			crbatBWCreate(&InfoWindow,str,BW_CENTER | BW_TOP);

			crbatSetDrawSceneCallback(crbatNotAvoidDrawSceneCallback);

			eiTime let;
			let.Reset();
			while(let.Get() < 1500){
				crbatCommandRotate_SelectCallBack(NULL,ew->lpCell[1],
					CRWIN_SELECT_IDLE,0,(ei_u32)&BatOrRunInfo,0);
			}
			crbatSetDrawSceneCallback(NULL);

			//---�搧�U���łȂ���΃R�}���h���͖�������
			if(pInfo->OffsetBattle != BATSTART_SENSEI)
				return BATRET_OK;

			battle_first = 0;
			party = crbatInputBattleOrRunaway(battle_first,&BatOrRunInfo,0,0);
		} else {
			party = crbatInputBattleOrRunaway(battle_first,&BatOrRunInfo);
		}

		if(party == 1){
			//---�������邩�ǂ���
			if(crbatIsEnableRunaway(pInfo,turn)){
				return BATRET_AVOID;
			} else {
				//---�������Ȃ�
				for(member = 0;member < MEMBER_MAX;member ++){
					if(pBtChara[member].DoExist()){
						pBtChara[member].Command.Main = BAT_COMMAND_WAIT;
					}
				}

				crbatDraw_ClearMenuArea();
				crbatShowStatus();
				crbatDraw_CopyScreen();

				InfoWindow.SetType(CRWIN_TYPE_NORMAL);
				crbatBWCreate(&InfoWindow,"�������Ȃ��I�I",BW_CENTER | BW_TOP);

				crbatSetDrawSceneCallback(crbatNotAvoidDrawSceneCallback);

				eiTime let;
				let.Reset();
				while(let.Get() < 1000){
					crbatCommandRotate_SelectCallBack(NULL,ew->lpCell[1],
						CRWIN_SELECT_IDLE,0,(ei_u32)&BatOrRunInfo,0);
				}
				crbatSetDrawSceneCallback(NULL);
				return BATRET_OK;
			}
		}

#if(CR_DEBUG == 1)
		if(crdataGetDebug()){
			if(party == -1){
				return BATRET_FORCEBREAK;
			}
		}
#endif
		if(pInfo->lpTurnCallBack != NULL && pInfo->ForceInputCommand == 0){
			//---�R�[���o�b�N���Ăяo��
			for(member = 0,first = 1;member < MEMBER_MAX;first = 0,member ++){
				if(pBtChara[member].DoExist()){
					(*pInfo->lpTurnCallBack)(turn,1,member,
							(ei_u32)(&pBtChara[member].Command),&pBtChara[member]);
				}
			}
		} else {
			//---���[�_�[�쐬
			for(member = 0;member < MEMBER_MAX;member ++){
				if(pBtChara[member].IsEnableCommandInput())
					break;
			}
			if(member != MEMBER_MAX){
				//---�R�}���h���͂ł�����A���[�_�[��`��
				crbatCreateRadar();
			}

			for(member = 0,first = 1,cansel = 0;member < MEMBER_MAX;first = 0,member ++){
				if(pBtChara[member].DoExist()){
					//---�����Ă�l��{��
					for(; member < MEMBER_MAX
						&&!pBtChara[member].IsEnableCommandInput()
						;member ++){
					}
					if(member == MEMBER_MAX){
						//---�N��������l�����Ȃ�������
						break;
					}

					//---���X�g�ɖ����݂̂�o�^
					crbatClearDrawingList();
					crbatAddDrawingListFriend();

					//---�n�[�t
					crbatChangeSlowView(BATTLE_VIEWMODE_HALF);
//					crbatSetViewMode(BATTLE_VIEWMODE_HALF);

					//---�J�������Z�b�g
					if(first){
//						pBtChara[member].SetCameraFront();
						if(crdataGetSystem()->BattleMoveCamera_AsInputCommand)
							pBtChara[member].MoveCamera(ANGLE(180),5.0f,crdataGetSystem()->BattleMoveCameraTime_AsInputCommand);
						else
							pBtChara[member].SetCameraFront();
					} else {
						if(crdataGetSystem()->BattleMoveCamera_AsInputCommand){
							pBtChara[member].SetCameraFront();
//							pBtChara[member].MoveCamera(ANGLE(180),5.0f,crdataGetSystem()->BattleMoveCameraTime_AsInputCommand);
						} else {
							pBtChara[member].SetCameraFront();
						}
					}
					//---�`��
					crbaseClearScreen(2);

					//---�y�N���b�v��ݒ�
					{
						float old = crbatSetDrawingZClip(0.90f);
						crbatClearDrawingList();
						crbatAddDrawingListFriend();
						crbatDrawScene();
						crbatDrawRadar();
						crbatDrawRadar_Cursor(&pBtChara[member]);
						crbatSetDrawingZClip(old);

						crbatClearDrawingList();
						crbatAddDrawingListFriend();

						crbatShowStatus();
					}

					//---�R�}���h����
					if(crbatGetCharacterCommand(&pBtChara[member],cansel) == -1){
						//---�L�����Z��
						cansel = 1;
						if(member == 0){
							break;
						} else {
							for(member --;0 <= member
								&& !pBtChara[member].IsEnableCommandInput()
								;member --){
							}
							if(member == -1){
								member = 0;
								break;
							}
							member --;
//							member -= 2;
						}
						continue;
					}
					cansel = 0;
				}
			}
		}
	} while(!member);

	crbatDraw_ClearMenuArea();
	crbatShowStatus();
	crbatDraw_CopyScreen();

	return BATRET_OK;
}
