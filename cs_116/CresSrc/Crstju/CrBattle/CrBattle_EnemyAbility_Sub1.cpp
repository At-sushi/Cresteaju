//---�z��
CRBATENEMYABILITY_API int crbatEnemy_Kyuketsu(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int ability)
{
	//---InfoWindow�����
	pWin->SetType(CRWIN_TYPE_NORMAL);
	if(ability == BAT_ECOM_KYUKETSU){
		crbatBWCreate(pWin,
			"�z��",BW_TOP | BW_CENTER);
	} else if(ability == BAT_ECOM_TABERU){
		crbatBWCreate(pWin,
			"�H�ׂ�",BW_TOP | BW_CENTER);
	} else if(ability == BAT_ECOM_KYUKETUKEN){
		crbatBWCreate(pWin,
			"�h���C���X���b�V��",BW_TOP | BW_CENTER);
	}

	//---�Փ˕␳
	int range = (pChara->Command.Range & 0xffff0000) >> 16;
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

	//---�U���l�A�h��l�A�v�Z���@�A����
	//---�_���[�W�v�Z
	int EnableCounter = 1,weapon = pChara->GetWeapon(pChara->Command.Sub[0]);
	if(weapon){
		//---�ԐڍU����������J�E���^�[����
		if(critemGetItemClass(weapon)->GetAtackKind() == 1){
			EnableCounter = 0;
		}
	} else if(!pChara->IsFriend()){
		if(pChara->BattleInfo.Enemy.AtackType == 1){
			//---�G�ԐڍU��
			EnableCounter = 0;
		}
	}

	crbatCalcDamage(
		pDamageInfo,pChara,
		SRC_WEAPON,1000,
		DST_DEFENSE,1000,
		CALCMODE_ADD,500,
		100,//---���U�i�P�^�P�O�O�O�P�ʁj
		weapon ? critemGetItemClass(weapon)->GetElement() : ELEMENT_PHYSICS,//---���푮��
		PROBMODE_REAL,pChara->GetBtHitProb(pChara->Command.Sub[0]),//---���햽����𗦁A������
		DEFENSEMODE_REAL
		);

	//---�A�j���[�V����
	crbatDoAnime_Weapon(pChara,pDamageInfo,0);

	pDamageInfo->Damage[1] = pDamageInfo->Damage[0];
	pDamageInfo->pList[1] = pChara;
	pDamageInfo->pList[2] = NULL;
	pDamageInfo->DamageMode[1] = DAMAGEMODE_ADD;

	//---�_���[�W�\��
	crbatShowDamage(pDamageInfo);
	//---�_���[�W���ʉ��Z
	crbatResultDamage(pDamageInfo);
	//---�_���[�W���ʕ\��
	crbatShowResult();

	//---�J�E���^�[
	crbatDoAction_CounterAtack(pDamageInfo,pChara,pWin,EnableCounter);

	return 1;
}

CRBATANIME_API void crbatDoAnime_MagicGroundCross(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,int mode);

//---����
CRBATENEMYABILITY_API int crbatEnemy_ExtendAtack(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int ability)
{
	int rate = 1250,DstDefense = DST_DEFENSE,def_rate = 1000;
	//---InfoWindow�����
	pWin->SetType(CRWIN_TYPE_NORMAL);

	switch(ability){
	case BAT_ECOM_NAGURU:
		rate = 1200;
		crbatBWCreate(pWin,
			"����",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_KAMITUKU:
		rate = 1150;
		crbatBWCreate(pWin,
			"���݂�",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_KIRIKAKARU:
		rate = 1150;
		crbatBWCreate(pWin,
			"�a�肩����",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_PIERUZAN:
		rate = 1250;
		crbatBWCreate(pWin,
			"�s�G�[���a",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_JURIASGIRI:
		rate = 1000;
		crbatBWCreate(pWin,
			"�W�����A�X�̕���",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_TOSSHIN:
		rate = 1500;
		crbatBWCreate(pWin,
			"�ːi",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_HAGESHIKU:
		rate = 1300;
		crbatBWCreate(pWin,
			"�������a�����",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_KAITENATACK:
		rate = 1000;
		crbatBWCreate(pWin,
			"��]�A�^�b�N",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_NAGITAOSU:
		rate = 1000;
		crbatBWCreate(pWin,
			"�Ȃ��|��",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_TOTUGEKI:
		rate = 1200;
		crbatBWCreate(pWin,
			"�ˌ�",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_SHOGEKIHA:
		rate = 1000;
		crbatBWCreate(pWin,
			"�Ռ��g",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_CHOUONPA:
		rate = 1000;
		crbatBWCreate(pWin,
			"�����g",BW_TOP | BW_CENTER);
//		DstDefense = DST_NONE;
		def_rate = 0;
		break;
	case BAT_ECOM_ENGETUZAN:
		rate = 1000;
		crbatBWCreate(pWin,
			"�~���a",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_SEKKINATACK:
		rate = 2000;
		crbatBWCreate(pWin,
			"�ڋߓˌ�",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_IREBACRASH:
		rate = 1300;
		crbatBWCreate(pWin,
			"���ꎕ�N���b�V��",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_HOSHOKU:
		rate = 1600;
		crbatBWCreate(pWin,
			"�ߐH",BW_TOP | BW_CENTER);
	case BAT_ECOM_SAN:
		rate = 1100;
		crbatBWCreate(pWin,
			"�_",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_DANDYSPRASHER:
		rate = 1100;
		crbatBWCreate(pWin,
			"�_���f�B�X�v���b�V���[",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_ONSOKU:
		rate = 1500;
		crbatBWCreate(pWin,
			"�����a��",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_SILENTBANISHA:
		rate = 1500;
		crbatBWCreate(pWin,
			"�T�C�����g�E�o�j�b�V���[",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_SETUDAN:
		rate = 1500;
		crbatBWCreate(pWin,
			"�ؒf",BW_TOP | BW_CENTER);
		break;

	case BAT_ECOM_ROUOU:
		rate = 1700;
		crbatBWCreate(pWin,
			"���֘O����",BW_TOP | BW_CENTER);
		break;

	case BAT_ECOM_CR_LINEKOGEKI:
		rate = 1400;
		crbatBWCreate(pWin,
			"�v���[�g�E�F�C��",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_CR_SINGLEKOGEKI:
		rate = 1800;
		crbatBWCreate(pWin,
			"�؂��",BW_TOP | BW_CENTER);
		break;


	case BAT_ECOM_RARFIAATACK:
		rate = 1000;
		break;
	}

	//---�Փ˕␳
	int range = (pChara->Command.Range & 0xffff0000) >> 16;
	if(!(9 <= range && range <= 15)){
		if(ability != BAT_ECOM_RARFIAATACK){
			crbatGetTargetChara(pChara,pChara->GetTarget(),
				pChara->Command.Range,&pDamageInfo->pList[0],1);
		}
	}

	if(pDamageInfo->pList[0] != NULL){
		//---�Փ˕␳�Ń^�[�Q�b�g���ς�����Ƃ��̂��߂�
		//---�L�����N�^�[�A���O���Đݒ�
		pDamageInfo->pList[0]->SetAngle(
			ANGLE(180) + pChara->GetCharaAngle(pDamageInfo->pList[0])
			);
	}

	crbatSetDamageMode(pDamageInfo,DAMAGEMODE_SUB);

	//---�U���l�A�h��l�A�v�Z���@�A����
	//---�_���[�W�v�Z
	int EnableCounter = 1,weapon = pChara->GetWeapon(pChara->Command.Sub[0]);
	if(weapon){
		//---�ԐڍU����������J�E���^�[����
		if(critemGetItemClass(weapon)->GetAtackKind() == 1){
			EnableCounter = 0;
		}
	} else if(!pChara->IsFriend()){
		if(pChara->BattleInfo.Enemy.AtackType == 1){
			//---�G�ԐڍU��
			EnableCounter = 0;
		}
	}

	int prob = pChara->GetBtHitProb(pChara->Command.Sub[0]),
		mode = PROBMODE_REAL;

/*	if(ability == BAT_ECOM_CR_LINEKOGEKI){
		prob = -1;
		mode = PROBMODE_100;
	}
*/
	crbatCalcDamage(
		pDamageInfo,pChara,
		SRC_WEAPON,rate,
		DstDefense,def_rate,
		CALCMODE_ADD,500,
		100,//---���U�i�P�^�P�O�O�O�P�ʁj
		weapon ? critemGetItemClass(weapon)->GetElement() : ELEMENT_PHYSICS,//---���푮��
		mode,prob,//---���햽����𗦁A������
		DEFENSEMODE_REAL
		);

	//---�A�j���[�V����
	if(ability == BAT_ECOM_CR_LINEKOGEKI){
		crbatDoAnime_MagicGroundCross(pChara,pDamageInfo,0);
	} else {
		crbatDoAnime_Weapon(pChara,pDamageInfo,0);
	}

	//---�_���[�W�\��
	crbatShowDamage(pDamageInfo);
	//---�_���[�W���ʉ��Z
	crbatResultDamage(pDamageInfo);

	if(ability == BAT_ECOM_SAN){
		if(pDamageInfo->Damage[0]){
			//---�h��͌��炷
			pDamageInfo->pList[0]->AddBtStatus(BTST_ZERO);
		}
	}

	//---�_���[�W���ʕ\��
	crbatShowResult();

	//---�J�E���^�[
	if(ability != BAT_ECOM_CR_LINEKOGEKI){
		crbatDoAction_CounterAtack(pDamageInfo,pChara,pWin,EnableCounter);
	}

	return 1;
}

//---�k�o�����n
CRBATENEMYABILITY_API int crbatEnemy_LPRateDamage(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int ability)
{
	int rate = 1250;
	int prob = PROBMODE_REAL;
	//---InfoWindow�����
	pWin->SetType(CRWIN_TYPE_NORMAL);

	switch(ability){
	case BAT_ECOM_TOKASU:
		rate = 500;
		crbatBWCreate(pWin,
			"�Ƃ���",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_HANBUSSHITU:
	case BAT_ECOM_HANBUSSHITU_ZENTAI:
		rate = 950;
		crbatBWCreate(pWin,
			"������",BW_TOP | BW_CENTER);
		prob = PROBMODE_100;
		break;
	case BAT_ECOM_SHINSHOKU:
		rate = 500;
		crbatBWCreate(pWin,
			"�Z�H",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_820:
		rate = 820;
		crbatBWCreate(pWin,
			"�����E�W�Q�O",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_DIVIDING:
		rate = 500;
		crbatBWCreate(pWin,
			"�f�B�o�C�f�B���O",BW_TOP | BW_CENTER);
		break;
	}

	//---�Փ˕␳
	int range = (pChara->Command.Range & 0xffff0000) >> 16;
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

	//---�U���l�A�h��l�A�v�Z���@�A����
	//---�_���[�W�v�Z
	int EnableCounter = 1,weapon = pChara->GetWeapon(pChara->Command.Sub[0]);
	if(weapon){
		//---�ԐڍU����������J�E���^�[����
		if(critemGetItemClass(weapon)->GetAtackKind() == 1){
			EnableCounter = 0;
		}
	} else if(!pChara->IsFriend()){
		if(pChara->BattleInfo.Enemy.AtackType == 1){
			//---�G�ԐڍU��
			EnableCounter = 0;
		}
	}

	crbatCalcDamage(
		pDamageInfo,pChara,
		DST_LP,rate,
		DST_NONE,1000,
		CALCMODE_ADD,1000,
		0,//---���U�i�P�^�P�O�O�O�P�ʁj
		ELEMENT_PHYSICS,//---���푮��
		prob,pChara->GetBtHitProb(pChara->Command.Sub[0]),//---���햽����𗦁A������
		DEFENSEMODE_REAL
		);

	//---�A�j���[�V����
	crbatDoAnime_Weapon(pChara,pDamageInfo,0);

	//---�_���[�W�\��
	crbatShowDamage(pDamageInfo);
	//---�_���[�W���ʉ��Z
	crbatResultDamage(pDamageInfo);
	//---�_���[�W���ʕ\��
	crbatShowResult();

	//---�J�E���^�[
	crbatDoAction_CounterAtack(pDamageInfo,pChara,pWin,EnableCounter);

	return 1;
}

//---�����n�U��
CRBATENEMYABILITY_API int crbatEnemy_DeathAtack(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int ability)
{
	int rate = 1250;
	//---InfoWindow�����
	pWin->SetType(CRWIN_TYPE_NORMAL);

	switch(ability){
	case BAT_ECOM_CHISSOKU_1_10:
		rate = 100;
		crbatBWCreate(pWin,
			"����",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_CHISSOKU_1_5:
		rate = 200;
		crbatBWCreate(pWin,
			"����",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_CHISSOKU_1_2:
		rate = 500;
		crbatBWCreate(pWin,
			"����",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_CHISSOKU_2_3:
		rate = 666;
		crbatBWCreate(pWin,
			"����",BW_TOP | BW_CENTER);
		break;
	}

	//---�Փ˕␳
	int range = (pChara->Command.Range & 0xffff0000) >> 16;
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

	//---�U���l�A�h��l�A�v�Z���@�A����
	//---�_���[�W�v�Z
	int EnableCounter = 1,weapon = pChara->GetWeapon(pChara->Command.Sub[0]);
	if(weapon){
		//---�ԐڍU����������J�E���^�[����
		if(critemGetItemClass(weapon)->GetAtackKind() == 1){
			EnableCounter = 0;
		}
	} else if(!pChara->IsFriend()){
		if(pChara->BattleInfo.Enemy.AtackType == 1){
			//---�G�ԐڍU��
			EnableCounter = 0;
		}
	}

	crbatCalcDamage(
		pDamageInfo,pChara,
		DST_LP,1000,
		DST_NONE,1000,
		CALCMODE_ADD,1000,
		0,//---���U�i�P�^�P�O�O�O�P�ʁj
		ELEMENT_PHYSICS,//---���푮��
		PROBMODE_REAL,rate,//---���햽����𗦁A������
		DEFENSEMODE_REAL
		);

	//---�A�j���[�V����
	crbatDoAnime_Weapon(pChara,pDamageInfo,0);

	//---�_���[�W�\��
	crbatShowDamage(pDamageInfo);
	//---�_���[�W���ʉ��Z
	crbatResultDamage(pDamageInfo);
	//---�_���[�W���ʕ\��
	crbatShowResult();

	//---�J�E���^�[
	crbatDoAction_CounterAtack(pDamageInfo,pChara,pWin,EnableCounter);

	return 1;
}

