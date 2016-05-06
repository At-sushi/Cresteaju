/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBattle_Special.cpp ...Battle Special functions

-----------------------------------------------------------*/

#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBATTLE_SPECIAL

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#define EXTERN_CRBATTLE
#include "..\CrBase.h"
#include "..\CrBattle.h"

#define CR_GAMEINFO_EXTERNPOINTER
#include "..\CrGameInfo.h"


//---�K�E�Z
CRBATMAIN_API int crbatDoAction_SpecialAtack(CrSpecial *psp,
						CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int EnableCounter,int IsCounter,int Index)
{
	int a,b,count,max,prob = PROBMODE_100;

	//---�^�[�Q�b�g�����Ȃ�������
	if(pChara->Command.Target == 0){
		return 0;
	}
	//---�����s�����Ƃ�Ȃ�������
	if(!pChara->IsEnableMoveing()){
		return 0;
	}

	max = psp->GetSPAtackCount();

	//---�X�s�[�h
	int old = 0;
	if(psp->GetNumber() == 14){
		old = crbatSetBattleSpeed(1);
	}
	//---���b�N�I��
	if(psp->GetNumber() == 11 || psp->GetNumber() == 12
		|| psp->GetNumber() == 15){
		crbatDoAnime_LockOn(pChara,pDamageInfo);
	}

	for(count = 0;count < max && crbatGetEnemyCount();count ++){
		if(psp->GetNumber() == 14){
			//---�q�|�V���[�e�B���O
			prob = 0;

			//---�����_���I��
			int point;
			CrBattleCharacter *pList[32];
			int start = BATTLECHARA_STARTENEMY,end = BATTLECHARA_MAX;

			if(pChara->GetNumber() >= BATTLECHARA_STARTENEMY){
				start = 0;
				end = BATTLECHARA_STARTENEMY - 1;
			}
			for(b = start , point = 0;b < end;b ++){
				if(pBtChara[b].DoExist()){
					pList[point] = &pBtChara[b];
					point ++;
				}
			}
			pDamageInfo->Damage[0] = 0;
			pDamageInfo->Miss[0] = 0;
			pDamageInfo->DontShowThisDamage[0] = 0;
			pChara->Command.Target = (ei_u32)pList[eiRnd(point)];
			if(pChara->GetNumber() < BATTLECHARA_STARTENEMY)
				pChara->Command.Range = BAT_TARGET_ENEMYSINGLE;
			else
				pChara->Command.Range = BAT_TARGET_FRIENDSINGLE;
		}

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

		crbatSetDamageMode(pDamageInfo,DAMAGEMODE_SUB);
		for(a = 1;pDamageInfo->pList[a] != NULL;a ++){
			//---�⏕�_���[�W�o�^
			pDamageInfo->DamageRate[a] = psp->GetSubDamageRate();
		}

		//---�U���l�A�h��l�A�v�Z���@�A����
		//---�_���[�W�v�Z
		int weapon = pChara->GetWeapon(pChara->Command.Sub[0]);
		int rate = psp->GetDamageRate(),critical = 0;
		int def_rate = 1000;

		if(psp->GetNumber() == 17){
			//---�o���
			def_rate = 0;
		}

		//---����ɉ����Ēǉ�����
		crbatDoAction_AddWeaponEfectBefore(pDamageInfo,&rate,&def_rate,pChara,weapon);
		crbatCalcDamage(
			pDamageInfo,pChara,
			SRC_WEAPON,rate,
			DST_DEFENSE,def_rate,
			CALCMODE_ADD,500,
			psp->GetDamageDiffuse(),//---���U�i�P�^�P�O�O�O�P�ʁj
			weapon ? critemGetItemClass(weapon)->GetElement() : ELEMENT_PHYSICS,//---���푮��
//			ELEMENT_PHYSICS,
			PROBMODE_REAL | prob,pChara->GetBtHitProb(pChara->Command.Sub[0]),//---���햽����𗦁A������
			DEFENSEMODE_REAL
			);

		//---�A�j���[�V����
		int option = 0;
		if(psp->GetNumber() == 8 || psp->GetNumber() == 9)
			option = 1;

		crbatDoAnime_Weapon(pChara,pDamageInfo,critical,option);
		//---����ɉ����Ēǉ�����
		crbatDoAction_AddWeaponEfectAfter(pDamageInfo,pChara,weapon);

		//---�_���[�W�\��
		crbatShowDamage(pDamageInfo);

		//---�_���[�W���ʉ��Z
		crbatResultDamage(pDamageInfo);

		//---�_���[�W���ʕ\��
		crbatShowResult();
	}

	//---�X�s�[�h
	if(psp->GetNumber() == 14){
		crbatSetBattleSpeed(old);
	}

	return 1;
}

//---�K�E�Z
CRBATMAIN_API int crbatDoAction_SpecialAtack_Double(CrSpecial *psp,
						CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int EnableCounter,int IsCounter,int Index)
{
	int a,count,max,prob = PROBMODE_100;

	//---�^�[�Q�b�g�����Ȃ�������
	if(pChara->Command.Target == 0){
		return 0;
	}
	//---�����s�����Ƃ�Ȃ�������
	if(!pChara->IsEnableMoveing()){
		return 0;
	}

	max = 2;

	//---���b�N�I��
	if(psp->GetNumber() == 11 || psp->GetNumber() == 15){
		crbatDoAnime_LockOn(pChara,pDamageInfo);
	}

	for(count = 0;count < max && crbatGetEnemyCount();count ++){
		pChara->Command.Sub[0] = count;

		//---�Փ˕␳
		crbatGetTargetChara(pChara,pChara->GetTarget(),
			pChara->Command.Range,&pDamageInfo->pList[0],1);
		if(pDamageInfo->pList[0] != NULL){
			//---�Փ˕␳�Ń^�[�Q�b�g���ς�����Ƃ��̂��߂�
			//---�L�����N�^�[�A���O���Đݒ�
			pDamageInfo->pList[0]->SetAngle(
				ANGLE(180) + pChara->GetCharaAngle(pDamageInfo->pList[0])
				);
		}

		crbatSetDamageMode(pDamageInfo,DAMAGEMODE_SUB);
		for(a = 1;pDamageInfo->pList[a] != NULL;a ++){
			//---�⏕�_���[�W�o�^
			pDamageInfo->DamageRate[a] = psp->GetSubDamageRate();
		}

		//---�U���l�A�h��l�A�v�Z���@�A����
		//---�_���[�W�v�Z
		int weapon = pChara->GetWeapon(pChara->Command.Sub[0]);
		int rate = psp->GetDamageRate(),critical = 0;
		int def_rate = 1000;

		if(psp->GetNumber() == 17){
			//---�o���
			def_rate = 0;
		}

		//---����ɉ����Ēǉ�����
		crbatDoAction_AddWeaponEfectBefore(pDamageInfo,&rate,&def_rate,pChara,weapon);
		crbatCalcDamage(
			pDamageInfo,pChara,
			SRC_WEAPON,rate,
			DST_DEFENSE,def_rate,
			CALCMODE_ADD,500,
			psp->GetDamageDiffuse(),//---���U�i�P�^�P�O�O�O�P�ʁj
			weapon ? critemGetItemClass(weapon)->GetElement() : ELEMENT_PHYSICS,//---���푮��
//			ELEMENT_PHYSICS,
			PROBMODE_REAL | prob,pChara->GetBtHitProb(pChara->Command.Sub[0]),//---���햽����𗦁A������
			DEFENSEMODE_REAL
			);

		//---�A�j���[�V����
		crbatDoAnime_Weapon(pChara,pDamageInfo,critical);
		//---����ɉ����Ēǉ�����
		crbatDoAction_AddWeaponEfectAfter(pDamageInfo,pChara,weapon);

		//---�_���[�W�\��
		crbatShowDamage(pDamageInfo);

		//---�_���[�W���ʉ��Z
		crbatResultDamage(pDamageInfo);

		//---�_���[�W���ʕ\��
		crbatShowResult();
	}

	return 1;
}

//---�Ό��g
CRBATMAIN_API int crbatDoAction_SpecialShogekiha(CrSpecial *psp,
						CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int EnableCounter,int mode)
{
	int a;

	//---�^�[�Q�b�g�����Ȃ�������
	if(pChara->Command.Target == 0){
		return 0;
	}
	//---�����s�����Ƃ�Ȃ�������
	if(!pChara->IsEnableMoveing()){
		return 0;
	}

	if(pDamageInfo->pList[0] != NULL){
		//---�Փ˕␳�Ń^�[�Q�b�g���ς�����Ƃ��̂��߂�
		//---�L�����N�^�[�A���O���Đݒ�
		pDamageInfo->pList[0]->SetAngle(
			ANGLE(180) + pChara->GetCharaAngle(pDamageInfo->pList[0])
			);
	}

	if(mode == 16){
		//---�i�b�N�I
		for(a = 0;a < MEMBER_MAX;a ++){
			if(pBtChara[a].DoExist()
				&& !pBtChara[a].IsDown()){
				//---�C�₵�ĂȂ�
				if(pBtChara[a].Who() == 6){
					//---���C�[����������A����
					pBtChara[a].AddBtStatus(BTST_EXTEND,1);
				}
			}
		}
	}
	for(a = 0;pDamageInfo->pList[a] != NULL;a ++){
		//---�⏕�_���[�W�o�^
		if(pDamageInfo->pList[a]->Command.Main == BAT_COMMAND_ENEMYABILITY
			&& pDamageInfo->pList[a]->Command.Sub[0] == BAT_ECOM_CR_HENSHIN){
			//---�ϐg
			continue;
		}
		if(pDamageInfo->pList[a]->BattleInfo.Enemy.Graphic == 223
			&& crbatGetTurn() == 1){
			//---�l�ԃN���C�V���E�Q�^�[����
			continue;
		}
		if(pDamageInfo->pList[a]->GetBtStatus() & BTST_WORLD){
			//---���[���h��������
			continue;
		}

		pDamageInfo->pList[a]->Command.Main = BAT_COMMAND_SKIP;
	}
	for(a = 0;a < BATTLECHARA_MAX;a ++){
		if(pBtChara[a].DoExist() == 0
			&& pBtChara[a].DoExistExtend()){
			//---�g�����݂�����
			pBtChara[a].Command.Main = BAT_COMMAND_SKIP;
		}
	}

	eiTextureCell tex;
	float range = 0;

	tex.ReadFile(CR_DATADIR4"warai.acf",CR_DATAFILE4,crdataGetFileMode());
	tex.Init(16);
	tex.Load();

	eiD3DMaterial material;
	material.Create();
	material.SetDeffuseColor(255,127,127,192);
	material.SetEmissiveColor(96,0,0,127);
	material.Set();

	int flag = 1,c,dst_count = 50;

	for(a = 0;a < dst_count;a ++){
		if(mode == 26){
			//---�Ռ��g
			pBtObject[a].CreateTLVertexRect(64,64);
		} else {
			//---���t�����܂̋���
			pBtObject[a].CreateTLVertexRect(32,32);
		}

		pBtObject[a].SetPos(
			(float)(pChara->GetFieldX()),
			(float)(pChara->GetFieldY())
			,
			0.2f
			);
		pBtObject[a].SetDrawMode(1);
		pBtObject[a].SetTexture(&tex);
		pBtObject[a].SetMoveVectorXYZ(
			(float)(eiRnd(1000) - 500) / 500.0f,
			(float)(eiRnd(1000) - 500) / 500.0f,
			0.01f + (float)eiRnd(1000) / 2000.0f 
		);
		pBtObject[a].SetMoveSpeed(0.1f);
		pBtObject[a].SetAlphaMode(1);
		pBtObject[a].SetXRate(1.0f);
		pBtObject[a].SetYRate(1.0f);
	}

	int t;
	float addw = 0;
	eiTime let;
	let.Reset();

	crsoundPlay(CRSOUND_HYURURIRA);
	while(flag){
		et->Reset();
		t = let.Get();

		crbatClearDrawingList();
		crbatAddDrawingListAll();

		if(t > 1500){
			flag = 0;
		}

		for(c = 0;c < dst_count;c ++){
			pBtObject[c].Move(addw);
			crbatAddDrawingList(&pBtObject[c],0,1);
		}
		crbatDrawScene();

crdataEnableRec(1);
		if(eiGetEndThread()){
			break;
		}
		crbatDrawRefresh();

		addw = (float)et->Get() / 10.0f;
	}

	for(c = 0;c < dst_count;c ++){
	}
	tex.ReleaseTexture();
	material.Release();

	crbatClearDrawingList();
	crbatAddDrawingListAll();

//	crbatDrawSceneWhile(750);
	if(pChara->GetNumber() < BATTLECHARA_PARTY_MAX){
		crbatBWCreate(pWin,"�G�͂��܂�̊����ɓ������~�߂��I",BW_TOP | BW_CENTER);
	} else {
		crbatBWCreate(pWin,"���܂�̊����ɓ������~�߂�ꂽ�I",BW_TOP | BW_CENTER);
	}
	crbatDrawSceneWhile(750);
/*	//---�A�j���[�V����
	crbatDoAnime_Weapon(pChara,pDamageInfo,critical);

	//---�_���[�W�\��
	crbatShowDamage(pDamageInfo);

	//---�_���[�W���ʉ��Z
	crbatResultDamage(pDamageInfo);

	//---�_���[�W���ʕ\��
	crbatShowResult();*/

	return 1;
}

//---�z�[���[�N���X
CRBATMAIN_API int crbatDoAction_SpecialHoriCross(CrSpecial *psp,
						CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin)
{
	int a;

	//---�^�[�Q�b�g�����Ȃ�������
	if(pChara->Command.Target == 0){
		return 0;
	}
	//---�����s�����Ƃ�Ȃ�������
	if(!pChara->IsEnableMoveing()){
		return 0;
	}

	if(pDamageInfo->pList[0] != NULL){
		//---�Փ˕␳�Ń^�[�Q�b�g���ς�����Ƃ��̂��߂�
		//---�L�����N�^�[�A���O���Đݒ�
		pDamageInfo->pList[0]->SetAngle(
			ANGLE(180) + pChara->GetCharaAngle(pDamageInfo->pList[0])
			);
	}

	for(a = 0;pDamageInfo->pList[a] != NULL;a ++){
		//---�⏕�_���[�W�o�^
		if(pDamageInfo->pList[a]->GetLP() >= 0){
			pDamageInfo->pList[a]->SetAbility(BTAB_P_KAIFUKU2,1);
		}
	}

//	crbatDrawSceneWhile(250);
	crbatDoAnime_Magic(pChara,pDamageInfo,11);
//	crbatDrawSceneWhile(750);
	crbatBWCreate(pWin,"�l�b�񕜗ʂ�����",BW_TOP | BW_CENTER);
	crbatDrawSceneWhile(750);

/*	//---�A�j���[�V����
	crbatDoAnime_Weapon(pChara,pDamageInfo,critical);

	//---�_���[�W�\��
	crbatShowDamage(pDamageInfo);

	//---�_���[�W���ʉ��Z
	crbatResultDamage(pDamageInfo);

	//---�_���[�W���ʕ\��
	crbatShowResult();*/

	return 1;
}

CRBATCPU_API ei_s32 crbatCPUThink_ReverseRange(ei_s32 target);

//---�J�E���^�[�Q�[�g
CRBATMAIN_API int crbatDoAction_SpecialCounterGate(CrSpecial *psp,
						CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin)
{
	int a;

	//---�^�[�Q�b�g�����Ȃ�������
	if(pChara->Command.Target == 0){
		return 0;
	}
	//---���@�������Ȃ�������
	if(!pChara->IsEnableMagic()){
		return 0;
	}

	for(a = 0;pDamageInfo->pList[a] != NULL;a ++){
		//---�⏕�_���[�W�o�^
		if(pDamageInfo->pList[a]->GetLP() >= 0){
			pDamageInfo->pList[a]->AddBtStatus(BTST_COUNTERGATE);
			//---���[���h����
			pChara->AddBtStatus(BTST_WORLD);
			if(!pChara->GetWorldTurn())
				pChara->SetWorldTurn(1);
		}
	}

	int magic = pChara->Command.Sub[0];
	CrMagic *pMagic = crmagicGetMagicClass(magic);

	int use_mc = pMagic->GetMC();
	if(pChara->GetMC() < use_mc)
		use_mc = pChara->GetMC();
	pChara->AddMC(-use_mc);
	pChara->Command.Sub[CRBAT_SUBTARGET] = 0;

	if(pChara->GetNumber() < BATTLECHARA_STARTENEMY)
		pChara->Command.Range = pMagic->GetTarget(0) | pMagic->GetRange(0);
	else
		pChara->Command.Range = crbatCPUThink_ReverseRange(pMagic->GetTarget(0) | pMagic->GetRange(0))
		| crmagicGetMagicClass(magic)->GetRange(0);


	//---��ʍX�V
	crbatShowStatus();

	crbatDoAnime_Magic(pChara,pDamageInfo,11);
	crbatBWCreate(pWin,"�������͏�ǂ�����ꂽ",BW_TOP | BW_CENTER);
	crbatDrawSceneWhile(750);

	//---�l�b�񕜂��Ȃ��悤�ɁI
	pChara->ResetMagicTime();

	return 1;
}

//---�X�}�C��
CRBATMAIN_API int crbatDoAction_SpecialSmile(CrSpecial *psp,
						CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin)
{
	int a;

	//---�^�[�Q�b�g�����Ȃ�������
	if(pChara->Command.Target == 0){
		return 0;
	}
	//---�����s�����Ƃ�Ȃ�������
	if(!pChara->IsEnableMoveing()){
		return 0;
	}

	crbatBWCreate(pWin,"���~�͔��΂�",BW_TOP | BW_CENTER);
	crbatDrawSceneWhile(750);

	for(a = 0;pDamageInfo->pList[a] != NULL;a ++){
		//---�⏕�_���[�W�o�^
		//---���
		pDamageInfo->pList[a]->AddBtStatus(BTST_MAHI);
	}
	crbatClearDrawingList();
	crbatAddDrawingListAll();
	crbatDrawSceneWhile(750);


	return 1;
}

//---���̎�
CRBATMAIN_API int crbatDoAction_SpecialHikari(CrSpecial *psp,
						CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin)
{
	int a;

	//---�^�[�Q�b�g�����Ȃ�������
	if(pChara->Command.Target == 0){
		return 0;
	}
	//---�����s�����Ƃ�Ȃ�������
	if(!pChara->IsEnableMoveing()){
		return 0;
	}

	crbatBWCreate(pWin,"���̎�",BW_TOP | BW_CENTER);

	crbatSetDamageMode(pDamageInfo,DAMAGEMODE_ADD);
	for(a = 0;pDamageInfo->pList[a] != NULL;a ++){
		pDamageInfo->Damage[a] = 
			pDamageInfo->pList[a]->GetMaxLP();// - pDamageInfo->pList[a]->GetLP();
	}

	crbatDoAnime_Magic(pChara,pDamageInfo,1);

	//---�_���[�W�\��
	crbatShowDamage(pDamageInfo);

	//---�_���[�W���ʉ��Z
	crbatResultDamage(pDamageInfo);

	//---�_���[�W���ʕ\��
	crbatShowResult();

	return 1;
}

//---�a�됯
CRBATMAIN_API int crbatDoAction_SpecialSuireisei(CrSpecial *psp,
						CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin)
{
	int a;

	//---�^�[�Q�b�g�����Ȃ�������
	if(pChara->Command.Target == 0){
		return 0;
	}
	//---�����s�����Ƃ�Ȃ�������
	if(!pChara->IsEnableMoveing()){
		return 0;
	}

	crbatBWCreate(pWin,"�a�됯",BW_TOP | BW_CENTER);

	crbatSetDamageMode(pDamageInfo,DAMAGEMODE_ADDMC);
	for(a = 0;pDamageInfo->pList[a] != NULL;a ++){
		pDamageInfo->Damage[a] = pDamageInfo->pList[a]->GetMaxMC();
	}

	crbatDoAnime_Magic(pChara,pDamageInfo,1);

	//---�_���[�W�\��
	crbatShowDamage(pDamageInfo);

	//---�_���[�W���ʉ��Z
	crbatResultDamage(pDamageInfo);

	//---�_���[�W���ʕ\��
	crbatShowResult();

	return 1;
}

//---�K�E�Z
CRBATMAIN_API int crbatDoAction_Special(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin)
{
	int index = pChara->Command.Sub[3];
	CrSpecial *psp = &pSpecialInfo[index];

	//---�^�[�Q�b�g�����Ȃ�������
	if(pChara->Command.Target == 0){
		return 0;
	}
	//---�����s�����Ƃ�Ȃ�������
	if(!(index == 3 || index == 4)){
		if(!pChara->IsEnableMoveing()){
			return 0;
		}
	}

	//---InfoWindow�����
	crbatBWCreate(pWin,psp->GetName(),BW_TOP | BW_CENTER);
	//---�o�g���q�X�g���[�v���X
	pChara->HistoryAddAction(BTHISTORY_SPECIAL);

	if(index == 4){
		//---�J�E���^�[�E�Q�[�g
		crbatDoAction_SpecialCounterGate(psp,pDamageInfo,pChara,
			pWin);
	} else if(psp->GetCommandType() == 0 && psp->GetNumber() == 15){
		//---���b�N�I���E�_�u��
		crbatDoAction_SpecialAtack_Double(psp,pDamageInfo,pChara,
			pWin,0,0,
			index);
	} else if(psp->GetCommandType() == 0){
		//---����U��
		crbatDoAction_SpecialAtack(psp,pDamageInfo,pChara,
			pWin,0,0,
			index);
	} else if(psp->GetCommandType() == 1){
		//---���@
		crbatDoAction_Magic(pDamageInfo,pChara,pWin,psp->GetDamageRate());
	} else {
		if(index == 26 || index == 16){
			//---���傤�����́I�A����
			crbatDoAction_SpecialShogekiha(psp,pDamageInfo,pChara,
				pWin,0,index);
		} else if(index == 5){
			//---�a�됯
			crbatDoAction_SpecialSuireisei(psp,pDamageInfo,pChara,pWin);
		} else if(index == 18){
			//---�z�[���[�N���X
			crbatDoAction_SpecialHoriCross(psp,pDamageInfo,pChara,pWin);
		} else if(index == 19){
			//---���̎�
			crbatDoAction_SpecialHikari(psp,pDamageInfo,pChara,pWin);
		} else if(index == 23){
			//---�X�}�C��
			crbatDoAction_SpecialSmile(psp,pDamageInfo,pChara,pWin);
		}
	}

	//---�d���^�[�����w�肵�A�q�X�g���[���N���A
	if(index != 4){
		//---�J�E���^�[�Q�[�g�ȊO�A�����N���A
		pChara->SetSpecialDisable(psp->GetDisableTurn() + 1);
		pChara->SpecialClearHistory();
	}

	return 1;
}

