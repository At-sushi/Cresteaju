/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrMain.cpp ...Main loop

-----------------------------------------------------------*/

#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CRMAIN

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#include "CrBase.h"
#include "CrEvent.h"

//---game info
#define CR_GAMEINFO_EXTERNPOINTER
#include "CrGameInfo.h"

//---battle
#include "CrBattle.h"

#include "CrEvCom.h"

//---���C�����j���[
extern int crmainMainMenu(int mode);
//---�^�C�g��
extern int crtitTitle(void);
extern void crtitiShouLogo(void);

int crmainField(void);
int crmainCheckAutoEvent(int reset = 0);

CREVENTLONG5_API int crevent_ThirdStart(void);
CREVENTLONG6_API int creventSouthSnowField_First(void);


//---
extern int crmainMenuLoad(void);

//---Cresteaju���C���֐�
int CresteajuMain(void)
{
	crmusicPlay(CRMUSIC_INIT);

	//---�R�[���o�b�N�Z�b�g
	crfieldSetMapChangeCallBack(creventMapChangeCallback);

	//---�Ƃ肠�����N���A
	crbaseClearScreen(3);

	//---3D�t�@���N�V�����e�X�g
	crsysTest3DFunction();
	CrEmptyWindow win;
	win.TestWindow();
	ew->lpCell[1]->DrawFillBox(0,0,639,479,ep->ToRGB(CRCOLOR_BLACK));
	ew->lpCell[0]->DrawFillBox(0,0,639,479,ep->ToRGB(CRCOLOR_BLACK));

	int rate = crsysSetupDisplay();
	char s[80];
	sprintf(s,"RefreshRate = %d\nDrawRate = %d\n",rate,crdataGetSystem()->DrawRate);
	eiDebugWriteFile(s);

	//---�^�C�g�����[�v
	int ret;

	//---���S
//#if (CR_DEBUG == 0)
	crtitiShouLogo();
//#endif

	while(1){
		while(1){
			//---�R�[�h�^�C�g��
			crsysSetCodeMode(CODE_TITLE);

eiDebugWriteFile("(Main) title start.\n");
			ret = crtitTitle();
eiDebugWriteFile("(Main) title end.\n");

			//---�ǎ����[�h
			crbaseLoadWallPaper(1);
eiDebugWriteFile("(Main) crbaseLoadWallPaper end.\n");

			if(ret == 1){
				//---Continue;
				if(crmainMenuLoad() == MAINLOOP_CANCELMENU){
					continue;
				}
eiDebugWriteFile("(Main) crmainMenuLoad end.\n");
			} else if(ret == 0){
				//---New Game
				creventStartGame(0);
			} else {
				//---End Game
				RECT rect = {0,0,640,480};
				crmusicFadeOut();
				crefectScreenEfect_FadeOut(&rect,250);
				et->Delay2(250);

				return 1;
			}
			break;
		}
		//---�Ƃ肠�����N���A
eiDebugWriteFile("(Main) crbaseClearScreen start.\n");
		crbaseClearScreen(3);
eiDebugWriteFile("(Main) crbaseClearScreen end.\n");
		//---���C���t�B�[���h������

eiDebugWriteFile("(Main) crmainCheckAutoEvent start.\n");
		crmainCheckAutoEvent(1);
eiDebugWriteFile("(Main) crmainField start.\n");
		ret = crmainField();
		if(ret < MAINLOOP_ESCAPE){
			//---�Q�[�������I���łȂ����
			continue;
		}
		break;
	}
	crmusicStop();
	et->Delay2(250);

	return 1;
}

//---�t�B�[���h��ʂ�������
int crmainInitField(void)
{
	return 1;
}

//---�I�[�g�C�x���g�`�F�b�N
int crmainCheckAutoEvent(int reset /* = 0*/)
{
	//---�O��̍��W
	static int pre_x = 0,pre_y = 0;
	//---�����̐^���̍��W
	int event,x = ef->xGet(),y = ef->yGet();
	eiMapObject *lpobject = &em->Data.Map[em->Data.ActiveMap]->lpObject[0];

	if(reset){
		//---�C�x���g���胊�Z�b�g
		pre_x = 0;
		pre_y = 0;
		return 0;
	}

	if(crfieldGetIgonoreEvent()){
		//---�C�x���g������������
		crfieldSetIgonoreEvent(0);
		pre_x = x;
		pre_y = y;
	} else if((pre_x != x || pre_y != y)){
		event = ef->IsThereObject(em,x,y);

		pre_x = x;
		pre_y = y;
		if(event != -1){
			//---��������I
			if(lpobject[event].GetStatus() & EF_OBJECT_ST_EVENTAUTO){
				//---�����C�x���g��������
				return creventCheckEvent(event);
			}
		}
	}

	return 0;
}

//---�}�j���A���C�x���g�`�F�b�N
int crmainCheckEvent(void)
{
	//---�����O�̍��W
	int event,x = ef->xGetForward(),y = ef->yGetForward();
	eiMapObject *lpobject = &em->Data.Map[em->Data.ActiveMap]->lpObject[0];

	event = ef->IsThereObject(em,x,y);
	if(event != -1){
		//---��������I
		if(!(lpobject[event].GetStatus() & EF_OBJECT_ST_EVENTAUTO)){
			//---�����C�x���g�łȂ�������
			return creventCheckEvent(event);
		}
	}

	return 0;
}

//---�L�[�{�[�h�`�F�b�N
int crmainCheckKey(void)
{
	//---����
	CrInput ci;

	ci.Get();

#if (CR_DEBUG == 1)
	if(ei->Escape){
		//---�G�X�P�[�v
		return MAINLOOP_ESCAPE;
	}
#endif/* CR_DEBUG == 1*/

	if(ci.IsButton(0) && !ef->xGetDelta() && !ef->yGetDelta()){
		if(evGet(EV_GS_NUMBER_STATUS) == 0 && evGet(EV_GS_SCENE_STATUS) == 0){
			//---���j���[
			int res;
			do {
				res = crmainMainMenu(0);
				//---���j���[�����[�h�Ȃ瑱����
			} while(res == MAINLOOP_RELOADMENU);

			return res;
		} else {
			//---�f�r�̒�
			evChangeToGroundShipScene();
		}
	}
	if(ci.IsButton(1) && !ef->xGetDelta() && !ef->yGetDelta()){
		if(evGet(EV_GS_NUMBER_STATUS) == 0){
			//---�C�x���g����
			int event = ef->IsThereObject(em,ef->xGet(),ef->yGet());
			if(NP_GS_NUMBER == event){
				//---�����ɂf�r
				evChangeGroundShip();
			} else {
				return crmainCheckEvent();
			}
		} else {
			//---�O���E���h�V�b�v�ɏ���Ă�΍~���
			if(crfieldGetMapNumber() == 10){
				int area = em->GetEnemyArea(ef->xGet(),ef->yGet());
				if(!evGet(204) && area == 14){
					//---�암��ጴ�����D
					creventSouthSnowField_First();
				}
			}
			evChangeGroundShip();
			ef->SetMoveSpeed(4);

			return MAINLOOP_NOMESSAGE;
		}
	}
	if(ei->Input[0].Button[2] && !ef->xGetDelta() && !ef->yGetDelta()){
		if(evGet(EV_GS_NUMBER_STATUS) == 0){
		} else {
			//---�O���E���h�V�b�v�ɏ���Ă�Βn�}
			evShowWorldMap(ef->xGet(),ef->yGet(),0,1);
		}
	}

#if (CR_DEBUG == 1)
	if(ei->Input[0].Button[2]){
	}
#endif

	return 0;
}

//---���j���[�`�F�b�N
int crmainCheckMenu(void)
{
	return 0;
}

//---�l�b��
void crmainMCCheck(void)
{
	int a,dmc;
	CrCharacter *pChara;

	for(a = 0;a < MEMBER_MAX;a ++){
		pChara = crcharaGetPartyMember(a);
		if(pChara == NULL)
			continue;

		pChara->SubDisableMCCount();
		if(pChara->GetDisableMCCount() > 0)
			continue;

		dmc = (pChara->GetMaxMC() * 1000) / 60;//50 3/8:->60
/*		if(pChara->GetProtector(0) == 119){
			//---�����̃��[�u
			dmc /= 2;
		}*/
		dmc = pChara->AddDeltaMC(dmc);
		if(dmc >= 10000){
			pChara->SetDeltaMC(dmc % 10000);
			pChara->AddMC(dmc / 10000);
		}
	}
}

//---�t�B�[���h�ړ�
int crmainMoveField(void)
{
	//---field move & do animation
	ef->Move(em);
	ef->MoveObject(em);

	//---�����J�E���g
	{
		static keep_x = 0,keep_y = 0;
		if((keep_x != ef->xGet() || keep_y != ef->yGet())
			/*&& evGet(EV_GS_NUMBER_STATUS) == 0/*�f�r�ł͂Ȃ�*/){
			pGameInfo->WalkCount ++;
		}
		keep_x = ef->xGet();
		keep_y = ef->yGet();
	}

#if (CR_DEBUG == 1)
	if(ei->Input[0].Button[2]){
		RECT rect = {0,0,640,480};
		if(ei->Quick){
			(eiGetSurfacePointer() + 3)->Put((eiGetSurfacePointer() + 1),0,0,&rect,DDBLTFAST_WAIT);
		} else {
			(eiGetSurfacePointer() + 2)->Put((eiGetSurfacePointer() + 1),0,0,&rect,DDBLTFAST_WAIT);
		}
		ew->Flip();
	} else {
#endif
		crfieldDrawAndWait();

#if (CR_DEBUG == 1)
		char s[80];
		sprintf(s,"    (%3d,%3d) Delta(%3d,%3d) , MapNumber = %2d \"%s\"",
			ef->xGet(),ef->yGet(),
			ef->xGetDelta(),ef->yGetDelta(),
			crfieldGetMapNumber(),
			em->GetGroupName() /*,em->GetEnemyType()*/);
		ew->lpCell[1]->DrawFillBox(0,0,320,16,ep->ToTextRGB(CRCOLOR_BLACK));
		ew->lpCell[1]->DrawText(s,0,0,ep->ToTextRGB(CRCOLOR_WHITE));

#endif

#if (CR_DEBUG == 1)
	}
#endif

	return 0;
}

//---�t�B�[���h�E�F�C�g
int crmainFieldWait(void)
{
	return 0;
}

//---�o�g���`�F�b�N
int crmainCheckBattle(void)
{
	int type = em->GetEnemyType();
	int area = em->GetEnemyArea(ef->xGet(),ef->yGet());

	if(type && area){
		if(ef->GetMoveDelta() >= 32){
			crmainMCCheck();
		}

		if(crfieldCheckBattle()){
#if (CR_DEBUG == 1)
			ei->Get();
			if(!(ei->Input[0].Button[1] == 1 && crdataGetDebug())){
#endif
				return crbatFieldBattle(crfieldGetMapNumber(),area);
#if (CR_DEBUG == 1)
			}
#endif
		}
	}

	return 0;
}

//---���C�����[�v
int crmainField(void)
{
	int ret = 0,check = 1;

eiDebugWriteFile("(Field) start.\n");

	//---�R�[�h�ݒ�
	crsysSetCodeMode(CODE_FIELD);

	ei->Get();
	ef->Field.Zoom = 100;
	//---�Ƃ肠�����A�s���߃��[�h
	ef->SetMoveEnything(0);

eiDebugWriteFile("(Field) crmainInitField start.\n");
	crmainInitField();
	//---���`��
eiDebugWriteFile("(Field) crfieldDrawField start.\n");
	crfieldDrawField(1);

eiDebugWriteFile("(Field) crefectScreenChange_FadeIn start.\n");
	crefectScreenChange_FadeIn();


	//---�R���X�^�[�g
	if(evGet(160) && !evGet(170)){
		crevent_ThirdStart();
	}

	while(check){
		et->Reset();
		//---�L�[�`�F�b�N�i�C�x���g�Ȃǂ��j
		ret = crmainCheckKey();
		if(ret >= MAINLOOP_ENDLOOP)
			break;

		//---���j���[
		ret = crmainCheckMenu();
		if(ret >= MAINLOOP_ENDLOOP)
			break;
		
		//---�t�B�[���h�ړ�
		ret = crmainMoveField();
		if(ret >= MAINLOOP_ENDLOOP)
			break;

		//---�t�B�[���h�E�F�C�g
		ret = crmainFieldWait();
		if(ret >= MAINLOOP_ENDLOOP)
			break;

		//---�����C�x���g�`�F�b�N
		if(ef->xGetDelta() == 0 && ef->yGetDelta() == 0){
			ret = crmainCheckAutoEvent();
			if(ret >= MAINLOOP_ENDLOOP)
				break;
		} else {
			crfieldSetIgonoreEvent(0);
		}

		if(evGet(130) == 221 && evGet(131)){
			//---�U��Ԃ�̒ʘH
			if(evGetTimer() > 10 * 500){
				evSet(129,1);
				evSet(130,0);
				evSet(131,0);
				em->Put(7,28,2,1024);
				crsoundPlay(CRSOUND_ANAAKU);
			}
		}
		//---�`���̓���
		int tofu = critemGetItemCount(244);
		int area = em->GetEnemyArea(ef->xGet(),ef->yGet());
		if(tofu){
			//---�`���̓���������
			if((crfieldGetMapNumber() == 10 && area == 14)
				|| (crfieldGetMapNumber() == 86)
				|| (crfieldGetMapNumber() == 87)){
				//---�암��ጴ���A�Y���ꂽ��Ղ��A��ጴ�̉ƂȂ�
				if(evGet(147) == 0){
					//---�J�E���g�J�n�I
					evSet(147,pGameInfo->PlayAllSecond);
					//---����J�E���g���Z�b�g
					evSet(146,pGameInfo->PlayAllSecond);
				}
				if(pGameInfo->PlayAllSecond - evGet(147) > (30 * 60)){
					//---�R�O���ȏ㊦���ꏊ�ɂ���
					critemAddItem(244,-tofu);
					critemAddItem(246,tofu);
				}
			} else if(crfieldGetMapNumber() != 59){
				//---�O���E���h�V�b�v�ł͂Ȃ�
				//---�J�E���g���Z�b�g
				evSet(147,0);
				if(pGameInfo->PlayAllSecond - evGet(146) > (2 * 60 * 60)
					/*&& �Q���Ԉȏ㊦���ꏊ�łȂ�*/){
					//---�������I�I
					critemAddItem(244,-tofu);
					critemAddItem(245,tofu);
				}
			}
		}

		//---�o�g������
		if(evGet(EV_GS_NUMBER_STATUS) == 0){
			ret = crmainCheckBattle();
			if(ret >= MAINLOOP_ENDLOOP)
				break;
		}
	}

	return ret;
}

/*	eiCell bm;
	bm.Create(192,40,8);
	bm.dib.SetPalette(0,0,0,0);
	int a;
	for(a = 1;a < 16;a ++){
		bm.dib.SetPalette(a,a * 16 + 15,a * 16 + 15,a * 16 + 15);
	}

	bm.DrawFillBox(0,0,191,39,0);
	double y,x,x2;
	for(y = -20;y < 20;y += 0.01){
		x = ((y * y * y) ) * 0.011;
		x = -x;
		x2 = ((y * y * y)) * 0.007;
		x2 = -x2;
		bm.DrawPixel((int)x2 + 96 + 64,(int)y + 20,11);
		bm.DrawPixel((int)x + 96 + 32,(int)y + 20,15);
	}
	
	bm.dib.Save("banner");*/
