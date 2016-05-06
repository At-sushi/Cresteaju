/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBattle_Main.cpp ...Battle Main functions

-----------------------------------------------------------*/

#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBATTLE_MAIN

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#define EXTERN_CRBATTLE
#include "..\CrBase.h"
#include "..\CrBattle.h"

#define CR_GAMEINFO_EXTERNPOINTER
#include "..\CrGameInfo.h"

#include "CrBattle_MainSubAfter.cpp"
#include "CrBattle_MainSubDamage.cpp"

CRBATMAIN_API int crbatDoAction_WeaponAtack(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int EnableCounter,int IsCounter);

int ResetTurn = 0;
CRBATMAIN_API void crbatResetTurn(int set)
{
	ResetTurn = set;
}

CRBATMAIN_API int crbatGetResetTurn(void)
{
	return ResetTurn;
}

//---MC�񕜃��[�g
//int AddMCRate[] = {0,8,12,14,16,18,20,20};
int AddMCRate[] = {0,6,10,12,14,16,18,18};

//---��ԕω���
CRBATMAIN_API void crbatAddTurnStatus(CrBattleCharacter *pChara)
{
	if(pChara->DoExist()){
		if(pChara->GetBtStatus() & BTST_NEMURI){
			if(eiRnd(1000) < pChara->GetStatusRecoveryRate(250))
				pChara->ClearBtStatus(BTST_NEMURI);

/*		} else if(pChara->GetBtStatus() & BTST_KURAYAMI){
			if(eiRnd(1000) < pChara->GetStatusRecoveryRate(50))
				pChara->ClearBtStatus(BTST_KURAYAMI);*/

		} else if(pChara->GetBtStatus() & BTST_KONRAN){
			if(eiRnd(1000) < pChara->GetStatusRecoveryRate(150))
				pChara->ClearBtStatus(BTST_KONRAN);

		} else if(pChara->GetBtStatus() & BTST_MAHI){
			if(eiRnd(1000) < pChara->GetStatusRecoveryRate(200))
				pChara->ClearBtStatus(BTST_MAHI);
		} else if(pChara->GetBtStatus() & BTST_CHINMOKU){
			if(eiRnd(1000) < pChara->GetStatusRecoveryRate(50))
				pChara->ClearBtStatus(BTST_CHINMOKU);
		}
	}
}

//---�^�[�����i��
CRBATMAIN_API void crbatAddTurn(int continue_battle)
{
	int a,b,turn,mc,dead;

	if(continue_battle){
		//---�k�o��
		for(a = 0;a < BATTLECHARA_MAX;a ++){
			if(pBtChara[a].DoExist() && !pBtChara[a].IsKizetu()){
				if(pBtChara[a].Ability(BTAB_S_SAISEI1)){
					pBtChara[a].ResultLP(
						pBtChara[a].GetMaxLP() / 10 > 0 ?
						+ (pBtChara[a].GetMaxLP() / 10) : 1);
				}
			}
		}
		//---�łłk�o������
		for(a = 0 ,dead = 0;a < BATTLECHARA_MAX;a ++){
			if(pBtChara[a].DoExist()){
				if(pBtChara[a].GetBtStatus() & BTST_DOKU){
					pBtChara[a].ResultLP(
						pBtChara[a].GetMaxLP() / 10 > 0 ?
						-(pBtChara[a].GetMaxLP() / 10) : 1);

					if(a >= BATTLECHARA_STARTENEMY){
						if(pBtChara[a].GetLP() <= 0)
							dead ++;
					}
				}
			}
		}
		if(dead){
			crbatShowResult();
		}
	}


	//---MC��
	for(a = 0;a < BATTLECHARA_MAX;a ++){
		if(
			(pBtChara[a].DoExist()
			&& pBtChara[a].IsKizetu() == 0)
			&& (pBtChara[a].GetDefenseCount() <= 0
				||
				(pBtChara[a].GetDefenseCount() <= 1
				&& pBtChara[a].Command.Main != BAT_COMMAND_DEFENSE)
				)
			){

			turn = pBtChara[a].AddFromLastMagic();
			if(turn >= 6)
				turn = 6;

			mc = pBtChara[a].GetMaxMC();
			mc = (mc * AddMCRate[turn]) * pBtChara[a].GetMCRate() / 1000;
			mc = mc / 100 + ((mc % 100) ? 1 : 0);
			//---�o�g���I�����Ȃ�񕜗ʔ���
			if(continue_battle == 0)
				mc /= 2;
			pBtChara[a].AddMC(mc);
		}
	}

	//---�X�e�[�^�X���킶��߂�
	for(a = 0;a < BATTLECHARA_MAX;a ++){
		for(b = 0;b < 32;b ++){
			if(pBtChara[a].DoExist()){
				if((1 << b) != BTST_KAOS){
					//---�J�I�X����Ȃ�������
					pBtChara[a].AddTurnStatus(1 << b);
				}
			}
		}
		crbatAddTurnStatus(&pBtChara[a]);
	}

	//---�R�}���h���Z�b�g
	for(a = 0;a < BATTLECHARA_MAX;a ++){
		if(pBtChara[a].DoExist()){
			//---�^�[���A�^�b�N���Z�b�g�i�ق�Ƃ͈�l�ł������ǁj
			pBtChara[a].ResetTurnAtack();
			//---�p�[�\�i���^�[���t���b�O�����炷
			pBtChara[a].AddPersonalTurn(-1);

			//---�I�[�g�K�[�h���Z�b�g
			pBtChara[a].SetAutoGard(0);

			//---�K�E�Z�^�[��
			pBtChara[a].SubSpecialDisable(1);

			if(pBtChara[a].Command.Main == BAT_COMMAND_SPECIAL
				&& pBtChara[a].Command.Sub[3]
				&& pBtChara[a].Command.Sub[BAT_SUBCOM_SPECIALNUMBER] == COUNTER_GATE){
				//---�J�E���^�[�E�Q�[�g
				if(pBtChara[a].Command.Sub[4] == 0){
					//---�l�b�����߂�
					int magic = pBtChara[a].Command.Sub[0];
					CrMagic *pMagic = crmagicGetMagicClass(magic);
					int use_mc = pMagic->GetMC();

					pBtChara[a].AddMC(use_mc);
				}
			}

			if(pBtChara[a].Command.Main == BAT_COMMAND_MAGIC
				&& pBtChara[a].Command.Sub[0] == 27){
				//---�J�I�X���[�h���g���Ă�
			} else {
				//---�����łȂ�������J�I�X���[�h�J�E���^���O
				pBtChara[a].ClearBtStatus(BTST_KAOS);
				pBtChara[a].ResetKaosTurn();
			}

			//---���[���h�J�E���g
			if(pBtChara[a].Command.Main == BAT_COMMAND_MAGIC
				&& pBtChara[a].Command.Sub[0] == 24){
				//---���[���h���g���Ă�
			} else {
				//---�����łȂ�������J�I�X���[�h�J�E���^���O
				pBtChara[a].SetWorldCountTurn(0);
			}

			//---���[���h�t���b�O����
			pBtChara[a].AddWorldTurn(-1);
			if(pBtChara[a].GetWorldTurn() <= 0){
				pBtChara[a].ClearBtStatus(BTST_WORLD);
			}
			//---�J�E���^�[�Q�[�g����
			pBtChara[a].ClearBtStatus(BTST_COUNTERGATE);

			if(pBtChara[a].Command.Main == BAT_COMMAND_DEFENSE){
				//---�h�䂵�Ă���f�B�t�F���X�J�E���^����
				pBtChara[a].AddDefenseCount();
			} else {
				pBtChara[a].ResetDefenseCount();
			}

			pBtChara[a].Command.Main = BAT_COMMAND_WAIT;
			//---�J�[�\�����Z�b�g
			if(crdataGetSystem()->BattleCommandReset == 0){
				//---�^�[�����ƃ��Z�b�g
				memset(&pBtChara[a].GetCharacterInfo()->BattleMenuCursor,0,
					sizeof(pBtChara[a].GetCharacterInfo()->BattleMenuCursor));
			}
		}
	}

	//---�p�^�[���Đݒ�
	crbatSetupCharaPattern();
}

typedef struct 
{
	ei_s32 x,y,col,px,py,ey;
	ei_s32 speed;
	ei_s32 flag;
} CRASIVE_DISAP;

#define CRDIS_MAX 1200

CRBATMAIN_API int crbatCrasiveDisapeare(CrBattleCharacter *pChara)
{
	int a,b,c;

	//---�N���C�V���̂����
	crbatDrawSceneWhile(500);
	eiTime let,let2;
	int t,y,addworld = 0,addr,sx,sy,flag = 1;
	eiDDSurface *pSurface = eiGetSurfacePointer();
	CrBattleCharacter *pcr = pChara;
	EILOCKEDCELL lc;
	int LineFlag[256],start,max_time = 16000;

	for(a = 0;a < 256;a ++){
		LineFlag[a] = -1;
	}

	EIMEMORY hMemory = eiAllocMemory(sizeof(CRASIVE_DISAP) * CRDIS_MAX);
	CRASIVE_DISAP *pdis = (CRASIVE_DISAP *)eiLockMemory(hMemory);
	memset(pdis,0,sizeof(CRASIVE_DISAP) * CRDIS_MAX);

	pcr->SetExistance(1);

	let.Reset();

//	crmusicFadeOut();

	while(let.Get() < 30000/*max_time*/ && flag == 1){
		let2.Reset();

		t = let.Get();

		y = 160 * (max_time - t) / max_time;

		pcr->SetZOffset(-(float)t / (float)max_time);

		for(a = 0,b = 0;a < 256;a ++){
			if(LineFlag[a] == 0)
				b ++;
		}
		if(b == 256){
			for(a = 0,b = 0;a < CRDIS_MAX;a ++){
				if(pdis[a].flag == 0)
					b ++;
			}
			if(b == CRDIS_MAX){
				flag = 0;
			}
		}

		for(a = 0;a < CRDIS_MAX;a ++){
			if(pdis[a].flag){
				pdis[a].px = pdis[a].x;
				pdis[a].py = pdis[a].y;
				pdis[a].y += (addworld * pdis[a].speed);

				if(pdis[a].y >= pdis[a].ey){
					pdis[a].flag = -1;
				}
			} else if(eiRnd(1000) < 100){
				pdis[a].flag = 1;
				pdis[a].speed = 3 + eiRnd(7);
				pdis[a].x = eiRnd(256);
				pdis[a].ey = (150 - t * 128 / max_time) * 256 + eiRnd(2560);
				if(pdis[a].ey < 32)
					pdis[a].ey = 32;

				if(LineFlag[pdis[a].x] == 0){
					c = eiRnd(1000);
					if(c < 333){
						for(b = 0;b < 10 && LineFlag[pdis[a].x] == 0;b ++){
							pdis[a].x = eiRnd(256);
						}
					} else if(c < 666){
						for(b = 0;b < 256 && LineFlag[pdis[a].x] == 0;b ++){
							pdis[a].x = b;//eiRnd(256);
						}
					} else {
						for(b = 255;b >= 0 && LineFlag[pdis[a].x] == 0;b --){
							pdis[a].x = b;
						}
					}
				}

				if(LineFlag[pdis[a].x] == -1){
					start = 159;
				} else {
					start = LineFlag[pdis[a].x];
					if(start == 0){
					}
				}
				for(b = start;b >= 0;b --){
					c = pcr->OnlyInfo.pDrawCell->dib.GetPixel(pdis[a].x,b);

					if(c != 16){
						pdis[a].y = b * 256;
						pdis[a].col = ep->MakeRGB(
							pcr->OnlyInfo.pDrawCell->dib.lpRGB[c].rgbRed
						  , pcr->OnlyInfo.pDrawCell->dib.lpRGB[c].rgbGreen
						  , pcr->OnlyInfo.pDrawCell->dib.lpRGB[c].rgbBlue);
						pcr->OnlyInfo.pDrawCell->dib.DrawPixel(pdis[a].x,b,16);
						LineFlag[pdis[a].x] = b;
						break;
					}
				}

				if(b <= 0){
					pdis[a].flag = 0;
					LineFlag[pdis[a].x] = 0;
				}
			}
		}

		eiEnableCheckThread(0);
		pcr->OnlyInfo.pDrawCell->Lock(&lc);

		sx = pcr->OnlyInfo.pDrawCell->Data.rectSurface.left;
		sy = pcr->OnlyInfo.pDrawCell->Data.rectSurface.top;

		for(a = 0;a < CRDIS_MAX;a ++){
			if(pdis[a].flag){

				if(pdis[a].flag == 1){
					addr = ((pdis[a].x + sx) << 1)
						+ (((pdis[a].y >> 8) + sy) * lc.LineSize);
					*(ei_u16 *)(lc.lpMemory + addr) = (ei_u16)pdis[a].col;
				}

				if(pdis[a].y != pdis[a].py || pdis[a].flag == -1){
					addr = ((pdis[a].px + sx) << 1)
						+ (((pdis[a].py >> 8) + sy) * lc.LineSize);
					*(ei_u16 *)(lc.lpMemory + addr) = (ei_u16)0x0001;

					if(pdis[a].flag == -1)
						pdis[a].flag = 0;
				}
			}
		}

		pcr->OnlyInfo.pDrawCell->UnLock();
		eiEnableCheckThread(1);

		crbatClearDrawingList();
		crbatAddDrawingListAll();

crdataEnableRec(0);
		crbatDrawScene();
crdataEnableRec(1);
		crbatDrawRefresh();

		addworld = let2.Get();
	}

//	crmusicStop();

	pcr->SetExistance(0);

	eiUnlockMemory(hMemory);
	eiFreeMemory(hMemory);

	return 1;
}

CRBATMAIN_API int crbatShowResult(void)
{
	int a,count;
	//---�������X�g
	CrBattleCharacter *pList[BATTLECHARA_MAX + 1];

	memset(&pList[0],0,sizeof(pList));

	for(a = 0,count = 0;a < BATTLECHARA_MAX;a ++){
		if(pBtChara[a].DoExist() == 0)
			continue;

		if(pBtChara[a].IsFriend() == 0){
			if(pBtChara[a].IsKizetu()){
				pList[count] = &pBtChara[a];
				count ++;
			}
		}
	}

	int EnemyListCount;
	for(a = 0,EnemyListCount = 0;a < count;a ++){
		//---���Ȃ��Ȃ�
		pList[a]->SetExistance(0);
//		if(pList[a]->GetType() != CHARATYPE_NINGEN){
			//---�l�ԂłȂ���΂Ƃт���
			EnemyListCount ++;
//		}
	}

	//---�N���C�V�������ꂽ
	if(EnemyListCount
		&& pList[0]->BattleInfo.Enemy.ActionType == 224){
		crbatCrasiveDisapeare(pList[0]);
	} else if(EnemyListCount && crsysNotQuick()){
	//---�����Ă���L�����������
		int one_part = 50,offset;

		if(pList[0]->BattleInfo.Enemy.ActionType == 223){
			//---�l�Ԃ̃N���C�V����|�����I
			pGameInfo->Event[261] = 1;
		}

		crbatClearDrawingList();
		crbatAddDrawingListAll();

		eiD3DParticle_SetG(0.01f);
		for(count = 0;count < EnemyListCount;count ++){
/*			if(pList[count]->GetType() == CHARATYPE_NINGEN){
				continue;
			}
*/
			offset = count * one_part;
			float x = (float)pList[count]->GetFieldX(),
				  y = (float)pList[count]->GetFieldY();
			float height =(float)pList[count]->GetCharaHeight() / 64.0f;
			for(a = 0;a < one_part;a ++){
				BatPart[a + offset].CreateTriangle(0.1f);
				BatPart[a + offset].SetWorldPos(
					x,
					height,
					y);
				//---���Ƃ���1000
				BatPart[a + offset].SetMoveVectorXYZ(
					(float)(eiRnd(300) - 150) / 100000,
					(float)(((float)(eiRnd(300) - 150) / 100000) / 2.0f),
					(float)(eiRnd(300) - 150) / 100000);
				BatPart[a + offset].SetMoveSpeed(0.5f);
				BatPart[a + offset].SetWeight(1);
			}
		}
		//---�ӂ��鉹
		crsoundPlay(CRSOUND_ENEMYDEAD);

		float Start = (float)et->GetTime(),AddWorld = 0;
		while(et->GetTime() - Start < 500.0f){
			et->Reset();

			BattleParticleMaterial.SetDeffuseColor(
				255,255,255,
				255 - (int)(255 * (et->GetTime() - Start) / 1000.0f));
crdataEnableRec(0);
			crbatDrawScene();
			if(eid3d->Begin()){
				eid3d->BeginAlphaBlend();
				crbatDraw_SetViewport(0);
				crbatDraw_SetMatrix(0);
				eid3d->SetMaterial(&BattleParticleMaterial);
				eid3d->SetTexture(NULL);

				for(a = 0;a < one_part * EnemyListCount;a ++){
					BatPart[a].MoveFrame(AddWorld);
					BatPart[a].Draw();
				}
				eid3d->SetMaterial(NULL);

				eid3d->EndAlphaBlend();
			}
			eid3d->End();

crdataEnableRec(1);
			crbatDrawRefresh();

			AddWorld = (float)et->Get() / 10.0f;
		}
	}

	return 1;
}

//---����ɉ����Č��ʂ�ǉ�
CRBATMAIN_API void crbatDoAction_AddWeaponEfectBefore(CR_BATTLE_DAMAGEINFO *pDamageInfo,
					int *pSrcRate,int *pDstRate,
					CrBattleCharacter *pChara,int weapon)
{
	int last;
	if(weapon == 0)
		return;

	for(last = 0;pDamageInfo->pList[last] != NULL;last ++){
	}

	switch(weapon){
	case 8:
		//---�h�䖳��
		//---�\�E���C�[�^�[
		*pDstRate = 0;

		break;
	}
}

//---����ɉ����Č��ʂ�ǉ�
CRBATMAIN_API void crbatDoAction_AddWeaponEfectAfter(CR_BATTLE_DAMAGEINFO *pDamageInfo,
					CrBattleCharacter *pChara,int weapon)
{
	int last;
	if(weapon == 0)
		return;

	for(last = 0;pDamageInfo->pList[last] != NULL;last ++){
	}

	switch(weapon){
	case 46:
		//---�X���[�h�i�C�t
		pDamageInfo->Damage[last] = pDamageInfo->Damage[0] / 2;//---��P�^�[�Q�b�g
		pDamageInfo->DamageRate[last] = pDamageInfo->DamageRate[0];
		pDamageInfo->DamageMode[last] = DAMAGEMODE_ADD;
		pDamageInfo->pList[last] = pChara;
		pDamageInfo->pList[last + 1] = NULL;
		break;
	case 77:
		//---�u���b�h�\�[�h
		pDamageInfo->Damage[last] = pDamageInfo->Damage[0];//---��P�^�[�Q�b�g
		pDamageInfo->DamageRate[last] = pDamageInfo->DamageRate[0];
		pDamageInfo->DamageMode[last] = DAMAGEMODE_ADD;
		pDamageInfo->pList[last] = pChara;
		pDamageInfo->pList[last + 1] = NULL;
		break;

	case 79:
		//---�f�X�J�b�^�[
		if(pDamageInfo->pList[last - 1]->Ability(BTAB_P_SOKUSHI) == 0){
			if(eiRnd(1000) < 70){
				//---����
				pDamageInfo->Damage[last - 1] = pDamageInfo->pList[last - 1]->GetLP();
			}
		}
		break;
	}
}

CRBATMAIN_API int crbatDoAction_CounterAtack(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int EnableCounter)
{
	//---�J�E���^�[����
	int count;
	int counter;
	CrBattleCharacter **ppList;

	for(count = 0,ppList = &pDamageInfo->pList[0];
		*ppList != NULL; count ++,ppList ++){
		counter = 0;
		if(ppList[0]->Ability(BTAB_S_COUNTER100)){
			counter = 1;
		} else if(ppList[0]->Ability(BTAB_S_COUNTER75) && eiRnd(1000) < 750){
			counter = 1;
		} else if(ppList[0]->Ability(BTAB_S_COUNTER50) && eiRnd(1000) < 500){
			counter = 1;
		} else if(ppList[0]->Ability(BTAB_S_COUNTER25) && eiRnd(1000) < 250){
			counter = 1;
		}
		if(counter && EnableCounter
			&& (pDamageInfo->DamageMode[count] != DAMAGEMODE_ADD
				&& pDamageInfo->DamageMode[count] != DAMAGEMODE_ADDMC)
			&& pChara != ppList[0]){
			//---�����łȂ����Ƃ��J�E���^�[�̏���

			//---�J�E���^�[�I
			CR_BATTLE_DAMAGEINFO CounterDamageInfo;

			//---����͑�P����
			CR_BATTLECOMMAND keep_com;
			memcpy(&keep_com,&ppList[0]->Command,sizeof(keep_com));

			int keep = ppList[0]->Command.Sub[0];
			ppList[0]->Command.Sub[0] = 0;

			memset(&CounterDamageInfo,0,sizeof(CounterDamageInfo));
			CounterDamageInfo.pList[0] = pChara;
			CounterDamageInfo.pList[1] = NULL;
			ppList[0]->Command.Target = (ei_u32)pChara;
			if(ppList[0]->IsFriend())
				ppList[0]->Command.Range = BAT_TARGET_ENEMYSINGLE;
			else
				ppList[0]->Command.Range = BAT_TARGET_FRIENDSINGLE;
			crbatDoAction_WeaponAtack(&CounterDamageInfo,ppList[0],pWin,0,1);
			//---���ɖ߂�
			ppList[0]->Command.Sub[0] = keep;

			memcpy(&ppList[0]->Command,&keep_com,sizeof(ppList[0]->Command));
		}
	}

	return 1;
}

//---����U��
CRBATMAIN_API int crbatDoAction_WeaponAtack(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int EnableCounter,int IsCounter)
{
	//---�^�[�Q�b�g�����Ȃ�������
	if(pChara->Command.Target == 0){
		return 0;
	}
	//---�����s�����Ƃ�Ȃ�������
	if(!pChara->IsEnableMoveing()){
		return 0;
	}

	//---InfoWindow�����
	if(IsCounter){
		crbatBWCreate(pWin,
			"�J�E���^�[",BW_TOP | BW_CENTER);
	} else if(pChara->IsFriend()
		|| (207 <= pChara->BattleInfo.Enemy.Graphic && pChara->BattleInfo.Enemy.Graphic <= 210)
			){
		pWin->SetType(CRWIN_TYPE_NORMAL);
		if(pChara->GetWeapon(pChara->Command.Sub[0])){
			//---����𑕔����Ă����
			crbatBWCreate(pWin,
				critemGetItemClass(pChara->GetWeapon(pChara->Command.Sub[0]))->GetName(),BW_TOP | BW_CENTER);
		}
	}
	//---�o�g���q�X�g���[�v���X
//	if(!IsCounter)
	//---�J�E���^�[�ł��P��̍U���ƃJ�E���g
	pChara->HistoryAddAction(BTHISTORY_WEAPON);

	//---�Փ˕␳
	int range = (pChara->Command.Range & 0xffff0000) >> 16;
	//---���C���^�[�Q�b�g�łȂ���΁A�Փ˕␳
	if(!(9 <= range && range <= 15)){
		crbatGetTargetChara(pChara,pChara->GetTarget(),
			pChara->Command.Range,&pDamageInfo->pList[0],1);
	}
	if(pDamageInfo->pList[0] != NULL){
		//---�Փ˕␳�Ń^�[�Q�b�g���ς�����Ƃ��̂��߂�
		//---�L�����N�^�[�A���O���Đݒ�
		pDamageInfo->pList[0]->SetAngle(
			ANGLE(180) + pChara->GetCharaAngle(pDamageInfo->pList[0])
			);
	}

	//pChara->IsBtWeaponDirect(pChara->Command.Sub[0]));
	//---�_���[�W���[�h
//	pDamageInfo->DamageMode[0] = DAMAGEMODE_SUB;
	crbatSetDamageMode(pDamageInfo,DAMAGEMODE_SUB);

	//---�U���l�A�h��l�A�v�Z���@�A����
	//---�_���[�W�v�Z
	int weapon = pChara->GetWeapon(pChara->Command.Sub[0]);
	int rate = 1000,dst_rate = 1000,critical = 0,prob = 0;
	if(weapon){
		//---�ԐڍU����������J�E���^�[����
		if(critemGetItemClass(weapon)->GetAtackKind() == 1){
			EnableCounter = 0;
		}
		//---�m�n�J�E���^�[�\��
		if(pChara->Ability(BTAB_S_NOCOUNTER)){
			EnableCounter = 0;
		}
	} else if(!pChara->IsFriend()){
		if(pChara->BattleInfo.Enemy.AtackType == 1){
			//---�G�ԐڍU��
			EnableCounter = 0;
		}
	}
	//---�N���e�B�J������
	if(pChara->Ability(BTAB_S_CRITICAL1)
		|| pChara->Ability(BTAB_S_CRITICAL2)
		|| pChara->Ability(BTAB_S_CRITICAL3)){

		if(pChara->Ability(BTAB_S_CRITICAL3)){
			prob = 333;
		} else if(pChara->Ability(BTAB_S_CRITICAL2)){
			prob = 100;
		} else if(pChara->Ability(BTAB_S_CRITICAL1)){
			prob = 40;
		}

		//---�s���`�Ȃ�N���e�B�J�����A�b�v
		if(pChara->GetLP() * 100 / pChara->GetMaxLP() < 33){
			prob = prob * 13 / 10;
		} else if(pChara->GetLP() * 100 / pChara->GetMaxLP() < 10){
			prob = prob * 2;
		}
		if(eiRnd(1000) < prob){
			//---�N���e�B�J���q�b�g�I
			rate = 2000;
			critical = 1;

//			eiSleep(3000);
		}
	}

	//---����ɂ���Č��ʂ�ǉ�
	crbatDoAction_AddWeaponEfectBefore(pDamageInfo,&rate,&dst_rate,pChara,weapon);

	if(rate == 2000){
		eiDebugWriteFile("main:rate 2000!!\n");
	}

	crbatCalcDamage(
		pDamageInfo,pChara,
		SRC_WEAPON,rate,
		DST_DEFENSE,dst_rate,
		CALCMODE_ADD,500,
		100,//---���U�i�P�^�P�O�O�O�P�ʁj
		weapon ? critemGetItemClass(weapon)->GetElement() : ELEMENT_PHYSICS,//---���푮��
//		ELEMENT_PHYSICS,
		PROBMODE_REAL,pChara->GetBtHitProb(pChara->Command.Sub[0]),//---���햽����𗦁A������
		DEFENSEMODE_REAL
		);

	//---�A�j���[�V����
	crbatDoAnime_Weapon(pChara,pDamageInfo,critical);
	//---����ɂ���Č��ʂ�ǉ�
	crbatDoAction_AddWeaponEfectAfter(pDamageInfo,pChara,weapon);

	//---�_���[�W�\��
	crbatShowDamage(pDamageInfo);

	//---�_���[�W���ʉ��Z
	crbatResultDamage(pDamageInfo);
	CrBattleCharacter **ppList;
	int count;
	for(count = 0,ppList = &pDamageInfo->pList[0];
		*ppList != NULL; count ++,ppList ++){
		//---�q�X�g���[
		if(pDamageInfo->Miss[count]){
			pChara->HistoryAddGiveMissCount(1);
		}

		if(pDamageInfo->Damage[count] != 0){
			//---�\��
			if(pChara->Ability(BTAB_S_ATKDOKU)){
				//---��
				if(eiRnd(1000) < pDamageInfo->pList[count]->GetStatusChangeRate(333)){
					ppList[0]->AddBtStatus(BTST_DOKU);
				}
			}
			if(pChara->Ability(BTAB_S_ATKMAHI)){
				//---���
				if(eiRnd(1000) < pDamageInfo->pList[count]->GetStatusChangeRate(150)){
					ppList[0]->AddBtStatus(BTST_MAHI);
				}
			}
			if(pChara->Ability(BTAB_S_ATKKONRAN)){
				//---����
				if(eiRnd(1000) < pDamageInfo->pList[count]->GetStatusChangeRate(200)){
					ppList[0]->AddBtStatus(BTST_KONRAN);
				}
			}
		}
	}

	//---�_���[�W���ʕ\��
	crbatShowResult();

	crbatDoAction_CounterAtack(pDamageInfo,pChara,pWin,EnableCounter);

	return 1;
}

//---�h��
CRBATMAIN_API int crbatDoAction_Defense(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin)
{
	//---�o�g���q�X�g���[�v���X
	pChara->HistoryAddAction(BTHISTORY_DEFENSE);

	if(pChara->Command.Sub[0] == BAT_SUBCOM_MOVE){
		//---�ړ���������

		if(crbatIsThere(pChara->Command.Sub[1],pChara->Command.Sub[2])
			|| !pChara->IsEnableMoveing()){
			//---���������ɒN��������
			return 1;
		}

		//---InfoWindow�����
		if(pChara->IsFriend()){
			pWin->SetType(CRWIN_TYPE_NORMAL);
			crbatBWCreate(pWin,
				"�ړ�",BW_TOP | BW_CENTER);
		}
		//---�A�j���[�V����
		crbatDoAnime_Move(pChara,pDamageInfo);

		//---�ړ�
		pChara->SetFieldPos(pChara->Command.Sub[1],pChara->Command.Sub[2]);
		//---�t�B�[���h���S������
		{
//			CrBattleCharacter tempobj;
			pBtTempChara[1].InitBattleCharacter();
			pBtTempChara[1].SetFieldPos(BATTLEFIELD_MAX_X / 2,BATTLEFIELD_MAX_Y / 2);
			pChara->SetAngle(pChara->GetCharaAngle(&pBtTempChara[1]));
		}
	}

	return 1;
}

//---�A�C�e��
CRBATMAIN_API int crbatDoAction_Item(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin)
{
	int item = pChara->Command.Sub[0];
	CrItem *pItem = critemGetItemClass(item);

	//---�^�[�Q�b�g�����Ȃ�������
	if(pChara->Command.Target == 0){
		return 0;
	}
	//---�����s�����Ƃ�Ȃ�������
	if(!pChara->IsEnableMoveing()){
		return 0;
	}

	//---�A�C�e�����Ȃ�������
	if(critemGetItemCount(item) <= 0){
		return 0;
	}

	//---�o�g���q�X�g���[�v���X
	pChara->HistoryAddAction(BTHISTORY_ITEM);

	//---InfoWindow�����
	if(pChara->IsFriend()){
		pWin->SetType(CRWIN_TYPE_NORMAL);
		crbatBWCreate(pWin,
			pItem->GetName(),BW_TOP | BW_CENTER);
	}
	//---�o�g���q�X�g���[�v���X
//	pChara->HistoryAddAction(BTHISTORY_WEAPON);
/*
	if(pDamageInfo->pList[0] != NULL){
		//---�Փ˕␳�Ń^�[�Q�b�g���ς�����Ƃ��̂��߂�
		//---�L�����N�^�[�A���O���Đݒ�
		pDamageInfo->pList[0]->SetAngle(
			ANGLE(180) + pChara->GetCharaAngle(pDamageInfo->pList[0])
			);
	}*/

	//---�A�C�e�����g��
	if((221 <= item && item <= 225) || (231 <= item && item <= 240)
		|| (item == 244)){
		int a;
		int free[2] = {pItem->GetFreeData(0),pItem->GetFreeData(1)};
		crbatSetDamageMode(pDamageInfo,DAMAGEMODE_ADD);

		if(pDamageInfo->pList[0] != NULL){
			for(a = 0;a < 2;a ++){
				if(a == 0)
					crbatSetDamageMode(pDamageInfo,DAMAGEMODE_ADD);
				else
					crbatSetDamageMode(pDamageInfo,DAMAGEMODE_ADDMC);
				if(free[a]){
					//---�_���[�W�v�Z
					crbatCalcDamage(
						pDamageInfo,pChara,
						SRC_DIRECT,free[a],
						DST_NONE,0,
						CALCMODE_ADD,1000,
						100,//---���U�i�P�^�P�O�O�O�P�ʁj
						0,
						PROBMODE_100,0,0
					);
//					//---�A�j���[�V����
					crbatDoAnime_Kaifuku(pChara,pDamageInfo);
					//---�_���[�W�\��
					crbatShowDamage(pDamageInfo);
					//---�_���[�W���ʉ��Z
					crbatResultDamage(pDamageInfo);
					//---�_���[�W���ʕ\��
					crbatShowResult();
				}
			}
		}
	} else if(item == 226){
		//---�L���A�[�J�v�Z��
		crbatDrawSceneWhile(500);
		if(pDamageInfo->pList[0] != NULL){
			pDamageInfo->pList[0]->CureStatus();
		}
		crbatDoAnime_Kaifuku(pChara,pDamageInfo);
		//---�_���[�W���ʕ\��
		crbatShowResult();
		crbatDrawSceneWhile(500);
	} else if(item == 227 || item == 228){
		//---���P�V�X�̓V���A���t
		if(pDamageInfo->pList[0] != NULL){
			if(pDamageInfo->pList[0]->GetLP() > 0){
				//---�C�₵�ĂȂ�������߂�
				return 1;
			}
			int damage;

			if(item == 227)
				damage = pDamageInfo->pList[0]->GetMaxLP() * 333 / 1000;
			else
				damage = pDamageInfo->pList[0]->GetMaxLP();

			crbatSetDamageMode(pDamageInfo,DAMAGEMODE_ADD);

			if(pDamageInfo->pList[0] != NULL){
				pDamageInfo->Damage[0] = damage;
//				//---�A�j���[�V����
				crbatDoAnime_Kaifuku(pChara,pDamageInfo);
				//---�_���[�W�\��
				crbatShowDamage(pDamageInfo);
				//---�_���[�W���ʉ��Z
				crbatResultDamage(pDamageInfo);
				//---�_���[�W���ʕ\��
				crbatShowResult();
			}
			if(item == 227)
				pDamageInfo->pList[0]->SetLP(pDamageInfo->pList[0]->GetMaxLP() * 333 / 1000);
			else
				pDamageInfo->pList[0]->SetLP(pDamageInfo->pList[0]->GetMaxLP());
		}
	} else if(item == 229){
		//---���葐
		crbatDrawSceneWhile(500);
		if(pDamageInfo->pList[0] != NULL){
			pDamageInfo->pList[0]->AddBtStatus(BTST_NEMURI);
		}
		//---�_���[�W���ʕ\��
		crbatShowResult();
		crbatDrawSceneWhile(500);
	} else if(item == 245){
		//---����������
		if(pDamageInfo->pList[0] != NULL){
			int damage;

			damage = pDamageInfo->pList[0]->GetMaxLP();

			crbatSetDamageMode(pDamageInfo,DAMAGEMODE_SUB);

			if(pDamageInfo->pList[0] != NULL){
				pDamageInfo->Damage[0] = damage;
				//---�_���[�W�\��
				crbatShowDamage(pDamageInfo);
				//---�_���[�W���ʉ��Z
				crbatResultDamage(pDamageInfo);
				//---�_���[�W���ʕ\��
				crbatShowResult();
			}
		}
	} else if(item == 246){
		//---����������
		if(pDamageInfo->pList[0] != NULL){
			int old = pChara->GetWeapon(0);

			pChara->SetWeapon(0,246);
			pChara->Command.Main = BAT_COMMAND_WEAPON;
			pChara->Command.Sub[0] = 0;

			int result =
				crbatDoAction_WeaponAtack(pDamageInfo,pChara,pWin,0,0);

			pChara->SetWeapon(0,old);
		}
	}
	//---�A�C�e�������炷
	critemAddItem(item,-1);

	return 1;
}

static CrStringWindow NameWindow(BATTLE_INFOWINDOW_FONT,CRWIN_BGFILL | /*CRWIN_FRAME |*/CRWIN_BGALPHA);
static CrStringWindow InfoWindow(BATTLE_INFOWINDOW_FONT,CRWIN_BGFILL | /*CRWIN_FRAME |*/CRWIN_BGALPHA);

CRBATMAIN_API void crbatDoActionDrawSceneCallback(eiCell *pCell,int mode)
{
	if(mode == 0){
		NameWindow.Paint();
		NameWindow.Reset();
		NameWindow.DrawLastString();
		InfoWindow.Paint();
		InfoWindow.Reset();
		InfoWindow.DrawLastString();
	}
}

//---�s������
CRBATMAIN_API int crbatDoAction(CrBattleCharacter *pChara,int turn,int ext_data,int EnableCounter)
{
	int ret = 0,enemy,add_enemy,do_exist_ex = 0;
	CrBattleCharacter *pOriginal = &pBtChara[BATTLECHARA_STARTENEMY];
	CRESTEAJU_BATTLECHARAINFO KeepBattleInfo;
	CR_BATTLEONLYINFO KeepOnlyInfo;

	crbatClearDrawingList();
	crbatAddDrawingListAll();

	//---�g������
	if(pChara->DoExistExtend() && !pChara->DoExist()){
		memcpy(&KeepBattleInfo,&pChara->BattleInfo,sizeof(KeepBattleInfo));
		memcpy(&KeepOnlyInfo,&pChara->OnlyInfo,sizeof(KeepOnlyInfo));

		memcpy(&pChara->BattleInfo,&pOriginal->BattleInfo,sizeof(pChara->BattleInfo));
		memcpy(&pChara->CharaInfo,&pOriginal->CharaInfo,sizeof(pChara->CharaInfo));
		memcpy(&pChara->OnlyInfo,&pOriginal->OnlyInfo,sizeof(pChara->OnlyInfo));
		do_exist_ex = 1;
		pOriginal->BattleInfo.Existence = 0;
	}

	//---�s���ł��Ȃ���������ǂ�
	if(pChara->IsEnableAction() == 0){
		//---��ԕω��񕜁i�b�o�t���񕜌シ���s�����Ȃ��悤�Ɂj
//		crbatAddTurnStatus(pChara);

		if(do_exist_ex){
			//---�g�����݂����ɖ߂�
			memcpy(&pOriginal->BattleInfo,&pChara->BattleInfo,sizeof(pOriginal->BattleInfo));
			memcpy(&pChara->BattleInfo,&KeepBattleInfo,sizeof(pChara->BattleInfo));
			memcpy(&pChara->OnlyInfo,&KeepOnlyInfo,sizeof(pChara->OnlyInfo));

			pChara->BattleInfo.Existence = 0;
			pChara->BattleInfo.ExistenceExtend = 1;
			pOriginal->BattleInfo.Existence = 1;
		}

		return BATRET_OK;
	}
	//---��ԕω���
//	crbatAddTurnStatus(pChara);

	if(pChara->IsFriend() == 0){
		//---�G�Ȃ�s���O
//		crbatCPUThink(pChara,turn);
		crbatCPUBeforeAction(pChara,turn);
	}

	if(pChara->GetBtStatus() & BTST_KONRAN){
		//---������
		CrBattleCharacter *pTemp = crbatRandomSelect(pChara,BAT_TARGET_FRIEND | BAT_TARGET_ENEMY);
		if(pTemp == pChara){
			if(pChara->IsFriend()){
				pTemp = crbatRandomSelect(pChara,BAT_TARGET_ENEMY);
			} else {
				pTemp = crbatRandomSelect(pChara,BAT_TARGET_FRIEND);
			}
		}
		pChara->Command.Target = (ei_u32)pTemp;
		pChara->Command.Main = BAT_COMMAND_WEAPON;
		pChara->Command.Sub[0] = 0;

		if(pChara->IsFriend()){
			pChara->Command.Range = BAT_TARGET_ENEMYSINGLE;
			pChara->Command.Sub[0] = eiRnd(2);
			if(pChara->GetWeapon(0) == 0 && pChara->GetWeapon(1) == 0)
				pChara->Command.Sub[0] = 0;
			else if(pChara->GetWeapon(0) == 0)
				pChara->Command.Sub[0] = 1;
			else if(pChara->GetWeapon(1) == 0)
				pChara->Command.Sub[0] = 0;
		} else {
			pChara->Command.Range = BAT_TARGET_FRIENDSINGLE;
		}

		pChara->Command.Range = BAT_TARGET_FRIENDSINGLE | BAT_TARGET_ENEMYSINGLE;

/*		CrBattleCharacter *pTarget = (CrBattleCharacter *)pChara->Command.Target;
		if(pTarget != NULL){
			if(pTarget->IsFriend()){
				//---���������_���I��
				crbatRandomSelect(pChara,BAT_TARGET_FRIEND);
			} else {
				crbatRandomSelect(pChara,BAT_TARGET_ENEMY);
			}
		}*/
	}

	if(pChara->Command.Main == BAT_COMMAND_WAIT){
		//---�ҋ@��������߂�
		if(do_exist_ex){
			//---�g�����݂����ɖ߂�
			memcpy(&pOriginal->BattleInfo,&pChara->BattleInfo,sizeof(pOriginal->BattleInfo));
			memcpy(&pChara->BattleInfo,&KeepBattleInfo,sizeof(pChara->BattleInfo));
			memcpy(&pChara->OnlyInfo,&KeepOnlyInfo,sizeof(pChara->OnlyInfo));

			pChara->BattleInfo.Existence = 0;
			pChara->BattleInfo.ExistenceExtend = 1;
			pOriginal->BattleInfo.Existence = 1;
		}
		return BATRET_OK;
	}

	if(pChara->Command.Main == BAT_COMMAND_DEFENSE
		&& pChara->Command.Sub[0] != BAT_SUBCOM_MOVE){
		//---�h��ňړ��łȂ�������߂�
		//---�o�g���q�X�g���[�v���X
		pChara->HistoryAddAction(BTHISTORY_DEFENSE);

		if(do_exist_ex){
			//---�g�����݂����ɖ߂�
			memcpy(&pOriginal->BattleInfo,&pChara->BattleInfo,sizeof(pOriginal->BattleInfo));
			memcpy(&pChara->BattleInfo,&KeepBattleInfo,sizeof(pChara->BattleInfo));
			memcpy(&pChara->OnlyInfo,&KeepOnlyInfo,sizeof(pChara->OnlyInfo));

			pChara->BattleInfo.Existence = 0;
			pChara->BattleInfo.ExistenceExtend = 1;
			pOriginal->BattleInfo.Existence = 1;
		}

		return BATRET_OK;
	}

	crbatSetDrawSceneCallback(crbatDoActionDrawSceneCallback);

//-------------------�^�[�Q�b�g
	CR_BATTLE_DAMAGEINFO DamageInfo;
	CrBattleCharacter *pCenter = NULL;

	memset(&DamageInfo,0,sizeof(DamageInfo));
	
	{
		memset(&DamageInfo,0,sizeof(DamageInfo));

		if(pChara->Command.Main == BAT_COMMAND_DEFENSE){
			//---�L�����N�^�[�̌����𐳂�������
			pBtTempChara[0].InitBattleCharacter();
			pBtTempChara[0].SetFieldPos(pChara->Command.Sub[1],pChara->Command.Sub[2]);
			pChara->SetAngle(pChara->GetCharaAngle(&pBtTempChara[0]));
			DamageInfo.pList[0] = &pBtTempChara[0];
			DamageInfo.pList[1] = NULL;
		} else if(pChara->Command.Target == 0){
/*	char s[80];
	sprintf(s,"%d",pChara->GetNumber());
	eiMsgBox(s);*/
			if(do_exist_ex){
				//---�g�����݂����ɖ߂�
				memcpy(&pOriginal->BattleInfo,&pChara->BattleInfo,sizeof(pOriginal->BattleInfo));
				memcpy(&pChara->BattleInfo,&KeepBattleInfo,sizeof(pChara->BattleInfo));
				memcpy(&pChara->OnlyInfo,&KeepOnlyInfo,sizeof(pChara->OnlyInfo));

				pChara->BattleInfo.Existence = 0;
				pChara->BattleInfo.ExistenceExtend = 1;
				pOriginal->BattleInfo.Existence = 1;
			}

			return 0;
		} else {
			//---�^�[�Q�b�g����
			crbatGetTargetChara(pChara,pChara->GetTarget(),
				pChara->Command.Range,&DamageInfo.pList[0]);

			pChara->Command.Target = (ei_u32)DamageInfo.pList[0];
			if(!pChara->Command.NoTurnTarget){
				//---�L�����N�^�[�̌����𐳂�������
				crbatSetAllCharacterDirection(pChara,&DamageInfo.pList[0]);
			}
		}
//		eiMsgBox(DamageInfo.pList[0]->GetName());
		//---�J�����ړ�
		if(crbatSetCameraWithObject(pChara,&DamageInfo.pList[0],
			500,&pCenter)){

			if(!pChara->Command.NoTurnTarget
				&& pCenter != NULL){
				//---�L�����N�^�[�̌����𐳂�������
				pChara->SetAngle(pCenter->GetCharaAngle(pChara) + ANGLE(180));
			}

			crbatDoMovingCamera(500);
			et->Wait2(WAIT_AFTERMOVECAMERA);
		} else {
			if(!pChara->Command.NoTurnTarget
				&& pCenter != NULL){
				//---�L�����N�^�[�̌����𐳂�������
				pChara->SetAngle(pCenter->GetCharaAngle(pChara) + ANGLE(180));
			}

			crbatDrawScene();
			crbatDrawRefresh();
//			ew->Refresh();
			et->Wait2(WAIT_AFTERMOVECAMERA);
		}
		//---NameWindow�����
		NameWindow.SetType(CRWIN_TYPE_NORMAL);
		if(pChara->IsFriend() && pChara->Who() == 14){
			crbatBWCreate(&NameWindow,"�N���X�e�B�[��",BW_LEFT | BW_BOTTOM);
		} else {
			crbatBWCreate(&NameWindow,pChara->GetName(),BW_LEFT | BW_BOTTOM);
		}
	}
//--------------------------------------
	//---������G�̐�
	enemy = crbatGetEnemyCount();
	int counter_gate = 0,result = 0;

	//---�s������
	if(pChara->Command.Main == BAT_COMMAND_WEAPON){
		//---����U��
		result = crbatDoAction_WeaponAtack(&DamageInfo,pChara,&InfoWindow,1,0);
//		counter_gate = 1;
		if(DamageInfo.pList[0] != NULL
		//---���肪�����ɑ΂��āA�G�Ȃ�
			&& pChara->IsFriend() != DamageInfo.pList[0]->IsFriend()){
			counter_gate = 1;
		}
	} else if(pChara->Command.Main == BAT_COMMAND_MAGIC){
		//---���@�g�p
		int ext_rate = 1000;
		//---�J�E���^�[�Q�[�g�p
		if(ext_data != 0){
			ext_rate = ext_data;
		}
		result = crbatDoAction_Magic(&DamageInfo,pChara,&InfoWindow,ext_rate);
		if(DamageInfo.pList[0] != NULL
		//---���肪�����ɑ΂��āA�G�Ȃ�
			&& pChara->IsFriend() != DamageInfo.pList[0]->IsFriend()){
			counter_gate = 1;
		}
	} else if(pChara->Command.Main == BAT_COMMAND_DEFENSE){
		//---�h��
		result = crbatDoAction_Defense(&DamageInfo,pChara,&InfoWindow);
	} else if(pChara->Command.Main == BAT_COMMAND_ITEM){
		//---�A�C�e��
		result = crbatDoAction_Item(&DamageInfo,pChara,&InfoWindow);
	} else if(pChara->Command.Main == BAT_COMMAND_SPECIAL){
		//---�K�E�Z
		result = crbatDoAction_Special(&DamageInfo,pChara,&InfoWindow);
		if(DamageInfo.pList[0] != NULL
		//---���肪�����ɑ΂��āA�G�Ȃ�
			&& pChara->IsFriend() != DamageInfo.pList[0]->IsFriend()){
			counter_gate = 1;
		}
	} else if(pChara->Command.Main == BAT_COMMAND_ENEMYABILITY){
		//---�G�̓���U��
		result = crbatDoAction_EnemyAbility(&DamageInfo,pChara,&InfoWindow);
		counter_gate = 1;

		if(pChara->Command.Sub[0] == BAT_ECOM_CRESTEAJU2){
			//---�N���X�e�B�[��
			crbatSetDrawSceneCallback(NULL);
			NameWindow.Release();
			InfoWindow.Release();
			return 1;

		} else if(pChara->Command.Sub[0] == BAT_ECOM_SABORU
			|| pChara->Command.Sub[0] == BAT_ECOM_TOSO){

			crbatSetDrawSceneCallback(NULL);
			NameWindow.Release();
			InfoWindow.Release();
			//---�����I��
			return BATRET_FORCEBREAK;
		}
	}
	counter_gate &= EnableCounter;

	crbatSetDrawSceneCallback(NULL);

	if(do_exist_ex){
		//---�g�����݂����ɖ߂�
		memcpy(&pOriginal->BattleInfo,&pChara->BattleInfo,sizeof(pOriginal->BattleInfo));
		memcpy(&pChara->BattleInfo,&KeepBattleInfo,sizeof(pChara->BattleInfo));
		memcpy(&pChara->OnlyInfo,&KeepOnlyInfo,sizeof(pChara->OnlyInfo));

		pChara->BattleInfo.Existence = 0;
		pChara->BattleInfo.ExistenceExtend = 1;
		pOriginal->BattleInfo.Existence = 1;
	}

	//---�p�^�[���Đݒ�
	crbatSetupCharaPattern();
	//---���X�g�X�V
	crbatClearDrawingList();
	crbatAddDrawingListAll();

	//---���̍s���̌��ʁA�c��̓G�̐�
	add_enemy = enemy - crbatGetEnemyCount();
	//---�|�����G�̐�
	pChara->HistoryAddFinishEnemyCount(add_enemy);

	//---��ʍX�V
	crbatShowStatus();
	crbatDrawScene();
	crbatDrawRefresh();
	//ew->Refresh();

	NameWindow.Release();
	InfoWindow.Release();

	//---�I�[�g�K�[�h
	if(pChara->Ability(BTAB_S_AUTOGARD)
		&& pChara->Command.Main != BAT_COMMAND_WAIT
		&& pChara->Command.Main != BAT_COMMAND_DEFENSE){
		//---�R�}���h���A�E�F�C�g�Ɩh��ȊO
/*		pChara->Command.Main = BAT_COMMAND_DEFENSE;
		pChara->Command.Sub[0] = BAT_SUBCOM_DEFENSE;*/
		pChara->SetAutoGard(1);
	}

	//-------------------------------------
	int a;
	for(a = 0;DamageInfo.pList[a] != NULL;a ++){
		if(counter_gate && result
			&& pChara->GetLP() > 0
			&& (DamageInfo.pList[a]->GetBtStatus() & BTST_COUNTERGATE)
			&& DamageInfo.DamageMode[a] != DAMAGEMODE_ADD
			&& DamageInfo.DamageMode[a] != DAMAGEMODE_ADDMC
				){
			//---�J�E���^�[�Q�[�g�҂����āA�_���[�W���񕜈ȊO�Ȃ�
			CrBattleCharacter *pcg = DamageInfo.pList[a];
			pcg->Command.Main = BAT_COMMAND_MAGIC;
			pcg->Command.Target = (ei_u32)pChara;

			if(pChara->DoExist() == 0 && pChara->DoExistExtend() == 1){
				//---�g�����݂�������A���̌��ɂ���
				pcg->Command.Target = (ei_u32)&pBtChara[BATTLECHARA_STARTENEMY];
			}

			if(pcg->IsEnableMagic()){
				//---���@���g�����ԂȂ�

				CrSpecial *psp = &pSpecialInfo[4];
				crbatDoAction(pcg,turn,psp->GetDamageRate(),0);
				//---�����N���A
				pcg->SetSpecialDisable(psp->GetDisableTurn());
				pcg->SpecialClearHistory();

				//---�g����
				pcg->Command.Sub[4] = 1;
			}

			return ret;
		}

		//---�ɂݕ���
		int com = DamageInfo.pList[a]->Command.Main,
			sub = DamageInfo.pList[a]->Command.Sub[0];
		if(EnableCounter
			&& DamageInfo.pList[a]->GetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE)
			&& result
/*			&& com == BAT_COMMAND_ENEMYABILITY
			&&  (sub == BAT_ECOM_ITAMIWAKE
			  || sub == BAT_ECOM_ITAMIWAKE_JIZOKU
			  || sub == BAT_ECOM_ITAMIWAKE_KAIJO)*/
			&& pChara->GetLP() > 0
			&& DamageInfo.Damage[a] > 0
			&& DamageInfo.DamageMode[a] != DAMAGEMODE_ADD
			&& DamageInfo.DamageMode[a] != DAMAGEMODE_ADDMC
			//---�Ώۂ��v���C���[�ɂȂ��Ă邩�`�F�b�N�A�|�C���^�֘A���܂߂�
			&& 0 <= DamageInfo.pList[a]->GetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE_TAISHO)
			&& DamageInfo.pList[a]->GetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE_TAISHO) <= 4
			&& !pBtChara[DamageInfo.pList[a]->GetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE_TAISHO)].IsKizetu()){


			CrBattleCharacter *pcg = DamageInfo.pList[a];
			CR_BATTLECOMMAND com;
			int keepmain = pcg->Command.Main,
				keep_sub[4] = {pcg->Command.Sub[0] , 0, 0, pcg->Command.Sub[3]};

			memcpy(&com,&pcg->Command,sizeof(com));
			pcg->Command.Main = BAT_COMMAND_ENEMYABILITY;
			pcg->Command.Range = BAT_TARGET_FRIENDSINGLE;
			pcg->Command.Target = (ei_u32)&pBtChara[pcg->GetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE_TAISHO)];
			pcg->Command.Sub[0] = BAT_ECOM_ITAMIWAKE_DAMAGE;
			pcg->Command.Sub[3] = DamageInfo.Damage[a];

			if(pcg->IsEnableMoveing()
			&& (pBtChara[pcg->GetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE_TAISHO)].GetBtStatus() & BTST_ITAMIWAKE)){
				//---�s���\��ԂŁA���O�Ώۂ��C�₵�Ă��Ȃ��Ȃ�
				crbatDoAction(pcg,turn,0,1);
			}

			memcpy(&pcg->Command,&com,sizeof(pcg->Command));
		}
	}

	return ret;
}

//---�s���͂����_�͂��ǂ�����
int GetBattleActionSource(int com,CrBattleCharacter *pChara)
{
	if(com != BAT_COMMAND_SPECIAL){
		return BattleActionSource[com];
	}

	CrSpecial *psp;

	psp = &pSpecialInfo[pChara->Command.Sub[BAT_SUBCOM_SPECIALNUMBER]];
	//---�R�}���h�^�C�v�����@�������琸�_
	if(psp->GetCommandType() == 1)
		return 1;

	return 0;
}

//---���X�g�����
CRBATMAIN_API int crbatMakeActionList(CrBattleCharacter **ppList)
{
	int a,b,c,index,first_count,count;
	CrBattleCharacter *pHitChara[BATTLECHARA_MAX + 1],*pRestChara[BATTLECHARA_MAX + 1];

	memset(&pHitChara[0],0,sizeof(pHitChara));

	for(a = 0,index = 0,first_count = 0;a < BATTLECHARA_MAX;a ++){
		if(pBtChara[a].DoExist()){
			if(pBtChara[a].Command.Main == BAT_COMMAND_MAGIC
				&& pBtChara[a].Command.Sub[0] == 24){
				//---���[���h�g�p�Ȃ�t�@�[�X�g�A�^�b�N
				pBtChara[a].EnableFirstAtack(1);
			}
			if(pBtChara[a].Command.Main == BAT_COMMAND_SPECIAL
				&& pBtChara[a].Command.Sub[BAT_SUBCOM_SPECIALNUMBER] == 4){
				//---�J�E���^�[�Q�[�g�Ȃ�
				pBtChara[a].EnableFirstAtack(1);
			}
		}
	}

	//---���X�g�ɃL�����N�^�[���W�߂�
	for(a = 0,index = 0,first_count = 0;a < BATTLECHARA_MAX;a ++){
		if(pBtChara[a].DoExistExtend()){
			ppList[index] = &pBtChara[a];

			if(pBtChara[a].GetFirstAtack()){
				//---�ŏ��ɍs���ł���
				pHitChara[first_count] = &pBtChara[a]; 
				first_count ++;
			} else {
				//---����
				pRestChara[index] = &pBtChara[a];
				index ++;
			}
		}
	}
	//---�t�@�[�X�g�A�^�b�N���m��f�������ɕ��ёւ�
	for(a = 0;a < first_count;a ++){
		int src[2];

		for(b = a;b < first_count - 1;b ++){
			for(c = 0;c < 2;c ++){
				if(GetBattleActionSource(pHitChara[b + c]->Command.Main,pHitChara[b + c]) == 0){
					src[c] = pHitChara[b + c]->GetBtAction();
				} else {
					src[c] = pHitChara[b + c]->GetBtSoul();
				}
			}
			if(pHitChara[b + 1]->GetFirstestAtack()
				|| (src[0] < src[1] && !pHitChara[b]->GetFirstestAtack())){
				//---������ԑ����s������Ȃ炩�A���̕����f�����Ȃ�
				CrBattleCharacter *ptemp = pHitChara[b];
				pHitChara[b] = pHitChara[b + 1];
				pHitChara[b + 1] = ptemp;
			}
		}
	}

	//---�s�����ɕ��ёւ���
	b = 0;count = 0;
	while(pRestChara[0] != NULL){
		int ave,src;
		double f,dif,hensachi[BATTLECHARA_MAX + 1];
		int hit,flag[BATTLECHARA_MAX + 1],min[BATTLECHARA_MAX + 1],max[BATTLECHARA_MAX + 1];
		//---�s���͂̕��ς����߂�
		for(a = 0,ave = 0;a < index - count;a ++){
//			if(GetBattleActionSource[ppList[a]->Command.Main] == 0){
			if(GetBattleActionSource(pRestChara[a]->Command.Main,pRestChara[a]) == 0){
//				ave += ppList[a]->GetBtAction();
				ave += pRestChara[a]->GetBtAction();
			} else {
//				ave += ppList[a]->GetBtSoul();
				ave += pRestChara[a]->GetBtSoul();
			}

			flag[a] = 1;//---�܂����
			min[a] = 0;
			max[a] = 0;
		}
		ave /= (index - count);
		//---�W���΍������߂�
		for(a = 0,dif = 0.0f;a < (index - count);a ++){
//			if(GetBattleActionSource[ppList[a]->Command.Main] == 0){
			if(GetBattleActionSource(pRestChara[a]->Command.Main,pRestChara[a]) == 0){
//				src = ppList[a]->GetBtAction();
				src = pRestChara[a]->GetBtAction();
			} else {
//				src = ppList[a]->GetBtSoul();
				src = pRestChara[a]->GetBtSoul();
			}

			dif += (double)((src - ave) * (src - ave));
		}
		dif = sqrt(dif);

		//---�΍��l
		for(a = 0;a < (index - count);a ++){
//			if(GetBattleActionSource[ppList[a]->Command.Main] == 0){
			if(GetBattleActionSource(pRestChara[a]->Command.Main,pRestChara[a]) == 0){
//				src = ppList[a]->GetBtAction();
				src = pRestChara[a]->GetBtAction();
			} else {
//				src = ppList[a]->GetBtSoul();
				src = pRestChara[a]->GetBtSoul();
			}

			f = (fabs((double)src - ave)) / (dif);
/*			f = f * 30.000;���v�Z
			if(src - ave >= 0)
				hensachi[a] = (50.000 + f) * 1.00;
			else
				hensachi[a] = (50.000 - f) * 1.00;*/
			f = f * 70.000;
			if(src - ave >= 0)
				hensachi[a] = (60.000 + f) * 1.00;
			else
				hensachi[a] = (60.000 - f) * 1.00;
			if(hensachi[a] < 1)
				hensachi[a] = 1;
		}

		char s[80];
//		for(b = 0,count = 0;b < index;b ++){
			eiDebugWriteFile("\n\n");
			for(a = 0;a < (index - count);a ++){
				min[a] = 0;
				max[a] = 0;
			}

			for(a = 0,c = -1;a < (index - count);a ++){
				//---�m���͈͂����߂�
				if(flag[a]){
					if(c != -1){
						min[a] = max[c];
					}
					max[a] = (int)((double)min[a] + hensachi[a]);
					c = a;

					sprintf(s,"%16s:%3d,%f        %d-%d\n",pRestChara[a]->GetName(),ppList[a]->GetBtAction(),hensachi[a],min[a],max[a]);
					eiDebugWriteFile(s);
				}
			}
			for(a = 0;a < (index - count);a ++){
				sprintf(s,"%14s:%3d%%\n",pRestChara[a]->GetName(),(max[a] - min[a]) * 100 / max[(index - count) - 1] );
				eiDebugWriteFile(s);
			}

			//---���I�ҁI�I
			hit = eiRnd(max[(index - count) - 1]);
			for(a = 0;a < (index - count);a ++){
				if(flag[a]){
					if(min[a] <= hit && hit < max[a]){
						//---�������I�I
						pHitChara[count + first_count] = pRestChara[a];
						pRestChara[a] = NULL;
//						pHitChara[count] = ppList[a];
						flag[a] = 0;
						count ++;
						break;
					}
				}
			}
//		}

		//---�c��L�������X�g���܂����
		int rest_flag = 1;
		while(rest_flag){
			rest_flag = 0;
			for(a = 0;a < index;a ++){
				if(pRestChara[a] == NULL){
					for(b = a + 1;b < index;b ++){
						if(pRestChara[b] != NULL){
							//---�L�������l�߂�
							pRestChara[a] = pRestChara[b];
							pRestChara[b] = NULL;
							rest_flag ++;
							break;
						}
					}
				}
			}
		}
	}

	//---�t�@�[�X�g�A�^�b�N����
	for(a = 0,index = 0,first_count = 0;a < BATTLECHARA_MAX;a ++){
		if(pBtChara[a].DoExist()){
			pBtChara[a].EnableFirstAtack(0);
			pBtChara[a].EnableFirstestAtack(0);
		}
	}

	memcpy(ppList,&pHitChara[0],sizeof(pHitChara));

	return index;
}

//---�퓬�I�����ǂ����𔻒肷��
CRBATMAIN_API int crbatCheckResult(void)
{
	int a,flag;
	
	for(a = 0,flag = 0;a < BATTLECHARA_PARTY_MAX;a ++){
		if(pBtChara[a].GetLP() > 0){
			//---���ꂩ�k�o���O�Ȃ�퓬�p���\
			flag ++;
		}
	}

	if(flag == 0){
		//---�����I
		return BATRET_LOSE;
	}

	for(a = BATTLECHARA_STARTENEMY,flag = 0;a < BATTLECHARA_STARTENEMY + BATTLE_ENEMYMAX;a ++){
		if(pBtChara[a].DoExist()){
			flag ++;
		}
	}

	if(flag == 0){
		//---�����I
		return BATRET_WIN;
	}

	return BATRET_OK;
}

//---�o�g���J�n�I
CRBATMAIN_API int crbatStartBattle(int turn,CR_BATTLEINFO *pInfo)
{
	int index,ret = 0;
	CrBattleCharacter *pList[BATTLECHARA_MAX + 1];//---�s�����ԃ��X�g
	//---�G�̎v�l
	for(index = BATTLECHARA_STARTENEMY;index < BATTLECHARA_MAX;index ++){
		if(pBtChara[index].DoExist() || pBtChara[index].DoExistExtend()){
			pBtChara[index].Command.Main = BAT_COMMAND_WAIT;
			//---�搧�U���łP�^�[���ڂ�������ҋ@
			if(turn == 0
				&& pInfo->OffsetBattle == BATSTART_SENSEI)
				continue;

			crbatCPUThink(&pBtChara[index],turn);
		}
	}
	//---�s�����X�g�����
	memset(&pList[0],0,sizeof(pList));
	crbatMakeActionList(&pList[0]);

/*	int a;char s[80];
	for(a = 0;a < 10;a ++){
		sprintf(s,"%d:%s = %d\n",a,
			crmagicGetMagicClass(pBtChara[0].CharaInfo.MagicTable[a])->GetName(),
			crmagicGetMagicClass(pBtChara[0].CharaInfo.MagicTable[a])->GetScene());
		eiDebugWriteFile(s);
	}*/

	index = 0;
	for(index = 0;pList[index] != NULL;index ++){
//	while(pList[index]){
		if(pList[index]->Command.Main == BAT_COMMAND_SKIP){
			//---�X�L�b�v�Ȃ�Ƃ΂�
			continue;
		}

		//---�s���O
		if(pInfo->lpTurnCallBack != NULL){
			//---�R�[���o�b�N������΂�����Ă�
			(*pInfo->lpTurnCallBack)(turn,3,pList[index]->GetNumber(),
				(ei_u32)(&pList[index]->Command),(CrCharacter *)pList[index]);
		}

//---�s�����ɕK���`�F�b�N---------------------------------
		if(pBtChara[BATTLECHARA_STARTENEMY + 2].DoExist()){
			if(pBtChara[BATTLECHARA_STARTENEMY + 2].BattleInfo.Enemy.ActionType == 120){
				//---�h�q�V�X�e��
				if(pBtChara[BATTLECHARA_STARTENEMY + 1].DoExist()
					&& pBtChara[BATTLECHARA_STARTENEMY].DoExist()){
					//---�o���A�[�Q�O�O
					pBtChara[BATTLECHARA_STARTENEMY + 2].SetAbility(BTAB_S_BARRIER100,0);
					pBtChara[BATTLECHARA_STARTENEMY + 2].SetAbility(BTAB_S_BARRIER200,1);
				} else if(pBtChara[BATTLECHARA_STARTENEMY + 1].DoExist()
					|| pBtChara[BATTLECHARA_STARTENEMY].DoExist()){
					//---�o���A�[�P�O�O
					pBtChara[BATTLECHARA_STARTENEMY + 2].SetAbility(BTAB_S_BARRIER100,1);
					pBtChara[BATTLECHARA_STARTENEMY + 2].SetAbility(BTAB_S_BARRIER200,0);
				} else {
					//---�o���A�[����
					pBtChara[BATTLECHARA_STARTENEMY + 2].SetAbility(BTAB_S_BARRIER100,0);
					pBtChara[BATTLECHARA_STARTENEMY + 2].SetAbility(BTAB_S_BARRIER200,0);
				}
			}
		}
//---------------------------------------------------

		//---�s���I
		if(!(pInfo->OffsetBattle == BATSTART_SENSEI
			&& pList[index]->IsFriend() == 0 && turn == 0))
			ret = crbatDoAction(pList[index],turn,0,1);
		else
			ret = BATRET_OK;


		//---�s����
		if(pInfo->lpTurnCallBack != NULL){
			//---�R�[���o�b�N������΂�����Ă�
			int sub_ret;
			sub_ret = (*pInfo->lpTurnCallBack)(turn,2,pList[index]->GetNumber(),
				(ei_u32)(&pList[index]->Command),(CrCharacter *)pList[index]);

			if(sub_ret == 0){
				ret = BATRET_FORCEBREAK;
			}
		}

		if(ret != BATRET_OK){
			break;
		}

		//---�o�g�����ʂ��`�F�b�N
		ret = crbatCheckResult();
		if(ret != BATRET_OK){
			break;
		}

		if(crbatGetResetTurn()){
			//---�^�[�����Z�b�g
			crbatResetTurn(0);
			ret = BATRET_OK;
			break;
		}

//		index ++;
	}

	return ret;
}

//---���C��
CRBATMAIN_API int crbatBattleMain(CR_BATTLEINFO *pInfo)
{
	int ret = 0;
	int turn;
	while(1){
		BattleStartTime = et->GetTime();

		for(turn = 0,ret = BATRET_OK;; turn ++){
			crbatSetTurn(turn);

			ei->Get();
#ifdef CR_DEBUG
//			if(ei->Input[0].Button[2])
//				break;
#endif
			//---�R�}���h����
			ret = crbatInputCommand(turn,pInfo);
			if(ret == BATRET_FORCEBREAK){
				break;
			}
			if(ret == BATRET_AVOID){
				break;
			}

			//---�o�g���I
			crbaseClearScreen(2);
			crbatShowStatus();
			ret = crbatStartBattle(turn,pInfo);

			//---�^�[����i�߂�
			crbatAddTurn(ret == BATRET_OK ? 1 : 0);
			crbatShowStatus();

			//---�o�g���p���łȂ���ΏI��
			if(ret != BATRET_OK){
				break;
			}

			//---������x�o�g�����ʂ��`�F�b�N�i�łƂ��̂��߁j
			ret = crbatCheckResult();
			if(ret != BATRET_OK){
				break;
			}

			//---�^�[�����~�b�g
			if(turn + 1 >= pInfo->LimitTurn && pInfo->LimitTurn){
				//---����������
				ret = BATRET_AVOID;
				break;
			}
		}

		//---�o�g���I��
		if(ret == BATRET_WIN){
			//---����
			if(!pInfo->DontShowAfterBattle){
				//---������̉�ʂ�������Ȃ�
				crbatWin(turn + 1,(et->GetTime() - BattleStartTime) / 1000,pInfo);
			}
		} else if(ret == BATRET_AVOID){
		//---������
			crbatAvoid();
		} else if(ret == BATRET_LOSE){
			//---������
			if(pInfo->FailOK){
				//---�����n�j�Ȃ炻�̂܂܂�����
				pInfo->Result = ret;
				if(pBtChara[BATTLECHARA_STARTENEMY].BattleInfo.Enemy.ActionType == 224){
					//---���X�g�o�g��
					crmusicFadeOut();
				}
				return ret;
			} else if(crbatLose(turn + 1,(et->GetTime() - BattleStartTime) / 1000,pInfo) == 0){
				crefectScreenChange_FadeOut(NULL,-1,1000);
				//---�������키��������A���[�h����������
//				crfileLoadData(MEMORYSAVEFILE_NUMBER,SAVE_FILE_ID1,SAVE_FILE_ID2,1);
				memcpy(pGameInfo->Item,BtKeepItem,sizeof(pGameInfo->Item));
				memcpy(pGameInfo->ItemCount,BtKeepItemCount,sizeof(pGameInfo->ItemCount));

				//---�����ݒ�
				crbatInitBattle(pInfo,1);
				continue;
			}
		}
		break;
	}

	crbatClearDrawingList();
	crbatAddDrawingListAll();

	pInfo->Result = ret;
	return ret;
}
