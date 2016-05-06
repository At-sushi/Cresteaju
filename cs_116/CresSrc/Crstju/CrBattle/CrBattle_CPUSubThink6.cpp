
int crbatSelectCopysWeapon(CrBattleCharacter *pChara,int who,int force = 0)
{
	int a;
	int item = 0,wp[2] = {pChara->GetWeapon(0),pChara->GetWeapon(1)};
	CrItem *pItem[2] = {critemGetItemClass(wp[0]),critemGetItemClass(wp[1])};

	if(force){
		if(force == 1){
			//---��
			for(a = 0;a < 2;a ++){
				if(pItem[a]->GetAtackKind() == 1){
					pChara->SetWeapon(a,0);
				}
			}
			item = crbatSelectCopysWeapon(pChara,who,0);
		} else if(force == 2){
			//---�e
			for(a = 0;a < 2;a ++){
				if(pItem[a]->GetAtackKind() == 0){
					pChara->SetWeapon(a,0);
				}
			}
			item = crbatSelectCopysWeapon(pChara,who,0);
		}

		//---����
		for(a = 0;a < 2;a ++){
			pChara->SetWeapon(a,wp[a]);
		}

		return item;
	}

	switch(who){
	case 1:
		//---���i��
		if(pItem[0]->GetAtack() < pItem[1]->GetAtack())
			item = 1;
		else
			item = 0;
		break;

	case 2:
		//---�f�B�U
		if(pItem[0]->GetMaterialKind() == pItem[1]->GetMaterialKind()){
			if(pItem[0]->GetAtack() < pItem[1]->GetAtack())
				item = 1;
			else
				item = 0;
		} else {
			if(pItem[0]->GetAtack() * 3 > pItem[1]->GetAtack() * 5)
				item = 0;
			else {
				if(pItem[0]->GetAtack() * 3 < pItem[1]->GetAtack() * 5)
					item = 1;
				else
					item = eiRnd(2);
			}
		}
		break;

	case 3:
		//---�i�b�N
		if(pItem[0]->GetAtack() && pItem[1]->GetAtack())
			item = eiRnd(2);
		else if(!pItem[1]->GetAtack())
			item = 0;
		else
			item = 1;
		break;

	case 4:
		//---�T���B�A�[
		if(pItem[0]->GetMaterialKind() == pItem[1]->GetMaterialKind()){
			if(pItem[0]->GetAtack() < pItem[1]->GetAtack())
				item = 1;
			else
				item = 0;
		} else {
			if(pItem[0]->GetAtack() * 3 > pItem[1]->GetAtack() * 5)
				item = 0;
			else {
				if(pItem[0]->GetAtack() * 3 < pItem[1]->GetAtack() * 5)
					item = 1;
				else
					item = eiRnd(2);
			}
		}
		break;
	}

	return item;
}

static int copyCountMagic(ei_s32 *ptable)
{
	int a,b;

	for(a = 0,b = 0;a < MAGIC_MAX;a ++){
		if(ptable[a])
			b ++;
	}
	return b;
}

int crbatSelectCopysHojoMagic(CrBattleCharacter *pChara,int who)
{
	int magic = -1,mc = pChara->GetMC(),dst = -1;

	int use,rnd = eiRnd(1000);

	if((who == 3 && eiRnd(1000) < 500) || who == 4){
		//---�t�H�[�X�V�[���h
		use = 17;
		if(eiRnd(1000) < 800 && pChara->HaveMagic(use) && mc >= crmagicGetMagicClass(use)->GetMC()){
			magic = use;
			dst = eiRnd(4);
		}

		//---�R���t���[�W����
		use = 18;
		if(eiRnd(1000) < 400 && pChara->HaveMagic(use) && mc >= crmagicGetMagicClass(use)->GetMC()){
			magic = use;
			dst = -1;
		}

		//---�G�N�X�e���h
		use = 22;
		if(eiRnd(1000) < 300 && pChara->HaveMagic(use) && mc >= crmagicGetMagicClass(use)->GetMC()
			&& pBtChara[BATTLECHARA_STARTENEMY + 1].DoExist()
			&& !pChara->GetBattleFlag(1)){
			magic = use;
			dst = 1;//---�f�B�U
		}

		//---�T�C�����X
		use = 15;
		if(eiRnd(1000) < 300 && pChara->HaveMagic(use) && mc >= crmagicGetMagicClass(use)->GetMC()){
			magic = use;
			dst = -1;
		}

		//---�f�X�t�H�[�X
		use = 21;
		if(eiRnd(1000) < 700 && pChara->HaveMagic(use) && mc >= crmagicGetMagicClass(use)->GetMC()){
			magic = use;
			dst = -1;
		}

		//---�I�[�����e�C��
		use = 23;
		if(eiRnd(1000) < 700 && pChara->HaveMagic(use) && mc >= crmagicGetMagicClass(use)->GetMC()){
			magic = use;
			dst = -1;
		}

		//---�p���[�u�[�X�g
		use = 19;
		if(eiRnd(1000) < 300 && pChara->HaveMagic(use) && mc >= crmagicGetMagicClass(use)->GetMC()
			&& pBtChara[BATTLECHARA_STARTENEMY + 1].DoExist()
			&& !pChara->GetBattleFlag(0)){
			magic = use;
			dst = 1;//---�f�B�U
			pChara->SetBattleFlag(0,1);
		}
		if(magic == 22){
			pChara->SetBattleFlag(1,1);
		}
	}

	if(who == 3){
		//---���[���h
		use = 24;
		if(eiRnd(1000) < 500 && pChara->HaveMagic(use) && mc >= 170
			&& pChara->GetWorldCountTurn() == 0){
			magic = use;
			dst = 5;
		}
	}

	if(magic != -1){
		if(dst == 5){
			crbatCPUThink_SetMagicAtack(pChara,magic);
		} else if(dst == -1){
			crbatCPUThink_SetMagicAtack(pChara,magic,-1,0,NULL,1);
		} else {
			crbatCPUThink_SetMagicAtack(pChara,magic,-1,0,&pBtChara[BATTLECHARA_STARTENEMY + dst]);
		}
		return magic;
	}

	return -1;
}

int crbatSelectCopysKaifukuMagic(CrBattleCharacter *pChara,int who)
{
	int magic = -1,mc = pChara->GetMC();

	ei_u32 st;
	int a,st_count,use,count = 0,index[4],list[4];
	CrBattleCharacter *ch;

	for(a = 0;a < 4;a ++){
		index[a] = list[a] = 0;

		ch = &pBtChara[BATTLECHARA_STARTENEMY + a];
		st = pBtChara[BATTLECHARA_STARTENEMY + a].GetBtStatus();

		if(ch->GetLP() * 100 / ch->GetMaxLP() < 70
			&& ch->GetLP() > 0){
			count ++;
		}
		if(st & 0xffff)
			index[a] ++;
	}
	for(a = 0,st_count = 0;a < 4;a ++){
		if(index[a]){
			list[st_count] = a;
			st_count ++;
		}
	}

	//---���C�t�V�����[
	use = 3;
	if(pChara->HaveMagic(use) && mc >= crmagicGetMagicClass(use)->GetMC()
		&& count >= 2 && !crbatCPU_PlayerIsBaraBara(pChara,2)){
		magic = use;
	}
	//---���J�o���C�V����
	use = 6;
	if(pChara->HaveMagic(use) && mc >= crmagicGetMagicClass(use)->GetMC()
		&& count >= 1){
		magic = use;
	}

	//---���C�t�E�B���h
	use = 7;
	if(pChara->HaveMagic(use) && mc >= crmagicGetMagicClass(use)->GetMC()
		&& count >= 2 && !crbatCPU_PlayerIsBaraBara(pChara,3)){
		magic = use;
	}

	use = 2;
	if(pChara->HaveMagic(use) && mc >= crmagicGetMagicClass(use)->GetMC()
		&& count <= 0 && st_count){
		//---�L���A�[
		crbatCPUThink_SetMagicAtack(pChara,2);
		pChara->Command.Target = (ei_u32)&pBtChara[BATTLECHARA_STARTENEMY + list[eiRnd(st_count)]];
		return 2;
	}

	if(magic != -1){
		crbatCPUThink_SetMagicAtack(pChara,magic);
		return magic;
	}
	return -1;
}

int crbatSelectCopysAtackMagic(CrBattleCharacter *pChara,int who)
{
	int a;
	int magic = -1,mc = pChara->GetMC(),limit,l = 0,low = 0;
	ei_s32 table[MAGIC_MAX];

	switch(who){
	case 1:
		l = 80;
		low = 3;
		break;
	case 2:
		l = 80;
		low = 4;
		break;
	case 3:
		l = 70;
		low = 3;
		break;
	case 4:
		l = 50;
		low = 4;
		break;
	}
	limit = (mc * l) / 100;

	//---�e�[�u���R�s�[
	memcpy(table,pChara->CharaInfo.MagicTable,sizeof(table));

	//---���@�������Ȃ�����
	if(!copyCountMagic(table))
		return -1;

	crmateSortMaterial(table,
		MAGIC_MAX,pMagicInfo,
		SORTMATERIAL_MC,NULL);

	//---�����̂l�b�̂����ȉ��̖��@�݂̂��W�߂�
	int element;
	for(a = 0;a < MAGIC_MAX;a ++){
		element = crmagicGetMagicClass(table[a])->GetMaterialKind();

		if(!(ELEMENT_FIRE <= element && element <= ELEMENT_THUNDER)
			&& !(element == ELEMENT_NOELEMENT)){
			//---�U�����@�ȊO���O��
			table[a] = 0;
		}
		//---�f�B�t���[�W�������G�N�X�e�B���N�V�����A�����g������A�G�N�X�e�B���N�V�������O��
		if(table[a] == 77 && pChara->HaveMagic(77) && pChara->HaveMagic(78)){
			table[a] = 0;
		}
		//---�G�N�X�e�B���N�V�������������Ă�����A�����_���g�p
		if(table[a] == 77 && !pChara->HaveMagic(78) && eiRnd(1000) < 500){
			table[a] = 0;
		}

		if(crmagicGetMagicClass(table[a])->GetMC() > limit){
			memset(&table[a],0,sizeof(ei_s32) * (MAGIC_MAX - a));
			break;
		}
	}

	//---���@�������Ȃ�����
	if(!copyCountMagic(table))
		return -1;

	//---���@�����x�����Ƃɕ�����
	crmateSortMaterial(table,
		MAGIC_MAX,pMagicInfo,
		SORTMATERIAL_LEVEL | SORTMATERIAL_REVERSE,NULL);

	int level = crmagicGetMagicClass(table[0])->GetLevel();
	if(level < low)
		return -1;
	//---�g����ō����x���̖��@���W�߂�
	for(a = 0;a < MAGIC_MAX;a ++){
		if(crmagicGetMagicClass(table[a])->GetLevel() < level){
			memset(&table[a],0,sizeof(ei_s32) * (MAGIC_MAX - a));
			break;
		}
	}
	//---a�܂ł̖��@��I�ׂ�

	magic = table[eiRnd(a)];
	crbatCPUThink_SetMagicAtack(pChara,magic);
	
	return magic;
}

int crbatSelectCopysAtackSpecial(CrBattleCharacter *pChara,int who)
{
	int item = crbatSelectCopysWeapon(pChara,who);
	int index = pChara->GetEnableSpecial();
	CrSpecial *psp;
	psp = &pSpecialInfo[index];

	if(pChara->GetBtStatus() & BTST_MAHI){
		return -1;
	}

	switch(index){
	case 16:
		//---���t���l
		crbatCPUThink_SetAtack2(pChara,item,&pBtChara[2]);

		pChara->Command.Main = BAT_COMMAND_SPECIAL;
		pChara->Command.Sub[BAT_SUBCOM_SPECIALNUMBER] = index;
		pChara->Command.Range = BAT_TARGET_FRIENDALL;
///		pChara->Command.Target = (ei_u32)pChara;
		return index;

	case 17:
		//---��������
	case 18:
		//---�z�[���[�N���X�͎g��Ȃ�
		return -1;
	case 19:
		//---���̎�
		pChara->Command.Main = BAT_COMMAND_SPECIAL;
		pChara->Command.Sub[BAT_SUBCOM_SPECIALNUMBER] = index;
		pChara->Command.Range = BAT_TARGET_ENEMYALL;
		pChara->Command.Target = (ei_u32)pChara;
		return index;

	case 1:
	case 2:
		//---���i���K�E�Z
		return -1;
	case 6:
	case 7:
	case 8:
	case 9:
		//---��
		item = crbatSelectCopysWeapon(pChara,who,1);
		if(pChara->GetWeapon(item) == 0){
			return -1;
		}
		crbatCPUThink_SetAtack2(pChara,item,&pBtChara[2]);

		pChara->Command.Main = BAT_COMMAND_SPECIAL;
		pChara->Command.Sub[BAT_SUBCOM_SPECIALNUMBER] = index;
		pChara->Command.Range = crbatCPUThink_ReverseRange(psp->GetTarget() | psp->GetRange());

		return index;

	case 14:
		//---�q�|�V���[�e�B���O
		return -1;
	case 11:
	case 12:
	case 15:
		//---�e
		item = crbatSelectCopysWeapon(pChara,who,2);
		if(pChara->GetWeapon(item) == 0){
			return -1;
		}
		crbatCPUThink_SetAtack2(pChara,item,&pBtChara[2]);

		pChara->Command.Main = BAT_COMMAND_SPECIAL;
		pChara->Command.Sub[BAT_SUBCOM_SPECIALNUMBER] = index;
		pChara->Command.Range = crbatCPUThink_ReverseRange(psp->GetTarget()| psp->GetRange());

		return index;

	case 3:
	case 4:
		//---�������A�J�E���^�[�Q�[�g
		if(pChara->GetBtStatus() & BTST_CHINMOKU){
			return -1;
		}
		if(crbatSelectCopysAtackMagic(pChara,1) != -1){
			pChara->Command.Main = BAT_COMMAND_SPECIAL;
			pChara->Command.Sub[BAT_SUBCOM_SPECIALNUMBER] = index;

			if(index == 4){
				pChara->Command.Target = (ei_u32)pChara;
				pChara->Command.Range = BAT_TARGET_ENEMY;
			}

			return index;
		}
		return -1;
	}

	return -1;
}

CRBATCPU_API int crbatCPUThink6(CrBattleCharacter *pChara,int turn,int rnd)
{
	if(pChara->BattleInfo.Enemy.ActionType == 168){
		//---���N�W�����i�C�g
		if(rnd < 333){
			//---�a�肩����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 169){
		//---�t�N
		if(rnd < 250){
			//---���邾��g
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_DARUDARUHA);
		} else if(rnd < 400){
			//---�Q��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NERU);
		} else if(rnd < 650){
			//---������
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_AKUBI);
		} else if(rnd < 700){
			//---���ڂ�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SABORU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 170){
		//---�J�C�������
		if(rnd < 250){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SEICHOU);
		} else if(rnd < 400 && pChara->GetLP() != pChara->GetMaxLP()){
			//---������
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KOUGOUSEI);
		} else if(rnd < 400){
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 750 && pChara->GetTurnAtack() <= 1){
			//---�_�C���u���X
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,62,-1,0,NULL,1);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 204){
		//---�s���N���{��
		if(rnd < 200){
			//---�s���N�~�X�g
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_PINKMIST);
		} else if(rnd < 400){
			//---���{���c�C�X�^�[
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_RIBONTUISTA,90);
		} else if(rnd < 550){
			//---�G�N�X�e���h
			crbatCPUThink_SetMagicAtack(pChara,22);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 205){
		//---�R�A�X�e���X
		if(rnd < 300 && !pChara->GetTurnAtack()){
			//---�����Â�
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_IKADUCHI,130);
		} else if(rnd < 250){
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 500){
			//---���݂�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 206){
		//---�G�m�L�^�C�N�[��
		if(rnd < 300){
			//---�E�q
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HOUSHI,30);
		} else if(rnd < 500){
			//---���ׂ�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TABERU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 211){
		//---�f�B�K�[��
		if(rnd < 200){
			//---���邮��ڋʃn�C�p�[
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_GURUGURUHYPER);
		} else if(rnd < 400){
			//---��������
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SOKUSHIKOUSEN);
		} else if(rnd < 700){
			//---�A�C�r�[��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_EYEBEAM,250);
		} else if(rnd < 500 && !(pChara->GetBtStatus() & BTST_PROTECT)){
			//---�v���e�N�V����
			crbatCPUThink_SetMagicAtack(pChara,13);
		} else if(rnd < 750 && !pChara->GetPersonalTurn()
			&& turn >= 2){
			//---�^�C�_���E�F�C��
			pChara->AddPersonalTurn(5);
			crbatCPUThink_SetMagicAtack(pChara,51);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
//-------------------------------------
	} else if(pChara->BattleInfo.Enemy.ActionType == 207){
		//---���i���R�s�[
		int item = crbatSelectCopysWeapon(pChara,1);

		if(pChara->GetBattleFlag(0) > 0){
			pChara->SetBattleFlag(0,pChara->GetBattleFlag(0) - 1);
		} else if(pChara->GetMC() < 30){
			pChara->SetBattleFlag(0,3);
		}

		if(rnd < 900 && crbatSelectCopysAtackSpecial(pChara,1) != -1){
			//---�K�E�Z
		} else if(!(pChara->GetBtStatus() & BTST_CHINMOKU)
			&& crbatCPUGetEnemy() <= 2 && rnd < 500){
			//---�񕜖��@
			if(crbatSelectCopysKaifukuMagic(pChara,1) == -1){
				//---�ʏ�U��
				crbatCPUThink_SetAtack2(pChara,item,&pBtChara[2]);
			}
		} else if((pChara->GetBtStatus() & BTST_CHINMOKU)
			|| pChara->GetBattleFlag(0) > 0){
			//---�ʏ�U��
			if(turn % 2 == 1 && crbatCPUGetEnemy() > 1){
				pChara->Command.Main = BAT_COMMAND_DEFENSE;
				pChara->Command.Sub[0] = BAT_SUBCOM_DEFENSE;
			} else {
				crbatCPUThink_SetAtack2(pChara,item,&pBtChara[2]);
			}
		} else if(rnd < 1000){
			if(crbatSelectCopysAtackMagic(pChara,1) == -1){
				//---�ʏ�U��
				crbatCPUThink_SetAtack2(pChara,item,&pBtChara[2]);
			}
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack2(pChara,item,&pBtChara[2]);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 208){
		//---�f�B�U�R�s�[
		int item = crbatSelectCopysWeapon(pChara,2);

		if(rnd < 900 && crbatSelectCopysAtackSpecial(pChara,2) != -1){
			//---�K�E�Z
		} else if(((pChara->GetBtStatus() & BTST_MAHI) || rnd < 200)
			&& turn != 0
			&& !((pChara->GetBtStatus() & BTST_POWER)
				|| (pChara->GetBtStatus() & BTST_EXTEND)
				)){
			if(crbatSelectCopysAtackMagic(pChara,2) == -1){
				//---�ʏ�U��
				crbatCPUThink_SetAtack2(pChara,item,&pBtChara[2]);
			}
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack2(pChara,item,&pBtChara[2]);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 209){
		//---�i�b�N�R�s�[
		int item = crbatSelectCopysWeapon(pChara,3);

		if(rnd < 900 && crbatSelectCopysAtackSpecial(pChara,3) != -1){
			//---�K�E�Z
		} else if(pChara->GetBtStatus() & BTST_CHINMOKU){
			//---�ʏ�U��
			crbatCPUThink_SetAtack2(pChara,item);

		} else if((rnd < 333 && turn >= 1)
			|| turn == 1){
			if(crbatSelectCopysKaifukuMagic(pChara,3) == -1){
				if(crbatSelectCopysHojoMagic(pChara,3) == -1){
					//---�ʏ�U��
					crbatCPUThink_SetAtack2(pChara,item);
				}
			}
		} else if(rnd < 666 && turn % 2 == 0){
			if(crbatSelectCopysHojoMagic(pChara,3) == -1){
				if(crbatSelectCopysKaifukuMagic(pChara,3) == -1){
					//---�ʏ�U��
					crbatCPUThink_SetAtack2(pChara,item);
				}
			}
		} else if(rnd < 1000 && turn % 2 == 0){
			if(crbatSelectCopysAtackMagic(pChara,3) == -1){
				//---�ʏ�U��
				crbatCPUThink_SetAtack2(pChara,item);
			}
		} else if(turn % 2 == 0 && crbatCPUGetEnemy() > 1){
			pChara->Command.Main = BAT_COMMAND_DEFENSE;
			pChara->Command.Sub[0] = BAT_SUBCOM_DEFENSE;
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack2(pChara,item);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 210){
		//---�T���B�A�[�R�s�[
		int item = crbatSelectCopysWeapon(pChara,4);

		if(rnd < 900 && crbatSelectCopysAtackSpecial(pChara,4) != -1){
			//---�K�E�Z
		} else if(rnd < 250 - (turn == 0 ? 150 : 0)
			&& !(pChara->GetBtStatus() & BTST_CHINMOKU)){
			if(crbatSelectCopysAtackMagic(pChara,4) == -1){
				//---�ʏ�U��
				if(crbatSelectCopysHojoMagic(pChara,4) == -1){
					crbatCPUThink_SetAtack2(pChara,item);
				}
			}
		} else if(rnd < 800 + (turn == 0 ? 200 : 0)
			&& !(pChara->GetBtStatus() & BTST_CHINMOKU)){
			if(crbatSelectCopysHojoMagic(pChara,4) == -1){
				//---�ʏ�U��
				crbatCPUThink_SetAtack2(pChara,item);
			}
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack2(pChara,item);
		}
//------------------------------------------------------
	} else if(pChara->BattleInfo.Enemy.ActionType == 172){
		//---�q���E�j
		if(rnd < 600){
			//---��]�A�^�b�N
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAITENATACK);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 173){
		//---�~�m�^�E���X
		if(rnd < 250){
			//---�Ȃ���
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGURU);
		} else if(rnd < 400){
			//---�ːi
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOSSHIN);
		} else if(rnd < 550){
			//---�Ȃ��|��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGITAOSU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 174){
		//---�A�C�X�|�[��
		if(rnd < 200){
			//---�T�C�����X
			crbatCPUThink_SetMagicAtack(pChara,15,-1,0,NULL,1);
		} else if(rnd < 400){
			//---�R���t���[�W����
			crbatCPUThink_SetMagicAtack(pChara,18,-1,0,NULL,1);
		} else if(rnd < 650){
			//---�A�N�A�\�[�h
			crbatCPUThink_SetMagicAtack(pChara,50);
		} else if(rnd < 800){
			//---�l�b����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_MCBUNKAI,30);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 175){
		//---�u���U�[�h
		if(rnd < 300 && !pChara->GetTurnAtack()){
			//---����
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_FUBUKI,130);
		} else if(rnd < 500){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_FUBUKI,70);
		} else if(rnd < 700){
			//---�X���[�v�u���X
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,35);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 176){
		//---�z���C�g�f�X
		if(rnd < 200 && !pChara->GetPersonalTurn()){
			//---�f�X�t�H�[�X
			pChara->AddPersonalTurn(3);
			crbatCPUThink_SetMagicAtack(pChara,21);
		} else if(rnd < 600 && pChara->GetLP() < 100){
			//---�k�o�`�F���W
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_LPCHANGE,750);
		} else if(rnd < 500){
			//---�Ƃ���
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOKASU);
		} else if(rnd < 700 && crbatCPUGetEnemy() > 1){
			//---�̂肤��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NORIUTURU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 177){
		//---�X�ᗳ
		if(rnd < 300 && !pChara->GetTurnAtack()
			&& !pChara->GetPersonalTurn()){
			//---����
			pChara->AddTurnAtack();
			pChara->AddPersonalTurn(2);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_FUBUKI,190);
		} else if(rnd < 350){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_FUBUKI,100);
		} else if(rnd < 666){
			//---���݂�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else if(rnd < 800 && pChara->GetLP() < 300
			&& pChara->GetBattleFlag(0) <= 1){
			//---���J�o���C�V����
			pChara->SetBattleFlag(0,pChara->GetBattleFlag(0) + 1);
			crbatCPUThink_SetMagicAtack(pChara,6);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 178){
		//---�t�H�[����
		CrBattleCharacter *pnear = crbatCPU_PlayerIsSekkin(pChara,0);

		if(pnear != NULL && rnd < 500
			&& pChara->GetBattleFlag(10) == 0){
			//---�ړ�
			pChara->SetBattleFlag(10,pChara->GetBattleFlag(10) + 1);
			crbatCPUThink_SetDefense(pChara,3);
		} else if(rnd < 300 && pChara->GetLP() < 700 && pChara->GetBattleFlag(0) <= 2
			&& !(pChara->GetBtStatus() & BTST_CHINMOKU)){
			//---���J�o���C�Y
			pChara->SetBattleFlag(0,pChara->GetBattleFlag(0) + 1);
			crbatCPUThink_SetMagicAtack(pChara,3);
		} else if(rnd < 333){
			//---�h���C���X���b�V��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KYUKETUKEN);
		} else if((rnd < 700 && !pChara->GetPersonalTurn())
			|| (turn <= 1 && !pChara->GetPersonalTurn())){
			//---�T�C�����g�E�o�j�b�V���[
			pChara->AddPersonalTurn(3);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SILENTBANISHA);
		} else if(rnd < 650 && pChara->GetBattleFlag(1) == 0){
			//---�p�����C�Y
			pChara->SetBattleFlag(1,1);
			crbatCPUThink_SetMagicAtack(pChara,31,-1,0,NULL,1);
		} else if(rnd < 650){
			//---�C���t���G���X
			pChara->SetBattleFlag(1,0);
			crbatCPUThink_SetMagicAtack(pChara,20,-1,0,NULL,1);
		} else if(rnd < 800){
			//---�[���V�[���h
			crbatCPUThink_SetMagicAtack(pChara,30,-1,0,NULL,1);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 179){
		//---���^���S�[����
		if(rnd < 200){
			//---�Ȃ���
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGURU);
		} else if(rnd < 400){
			//---�ːi
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOSSHIN);
		} else if(rnd < 550){
			//---�Ȃ��|��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGITAOSU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 180){
		//---�T���h�}�X�^�[
		if(rnd < 333 && pChara->GetBattleFlag(0) == 0
			&& pChara->GetBattleFlag(1) == 0 && pChara->GetLP() >= 400){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_RYUSA,10);
			pChara->SetBattleFlag(0,1);
		} else if(pChara->GetBattleFlag(0)){
			//---�ߐH
			pChara->SetBattleFlag(0,0);
			pChara->SetBattleFlag(1,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HOSHOKU);
		} else if(rnd < 350){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SUNAARASHI2,180);
		} else if(rnd < 700){
			//---�H�ׂ�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TABERU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 181){
		//---����
		if(rnd < 250 && !pChara->GetTurnAtack()){
			//---�_�C���u���X
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,62,-1,0,NULL,1);
		} else if(rnd < 300){
			//---�O���X�V�[�h
			crbatCPUThink_SetMagicAtack(pChara,61,-1,0,NULL,1);
		} else if(rnd < 500){
			//---�p�����C�Y
			crbatCPUThink_SetMagicAtack(pChara,31);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 182){
		//---�T���h�E�b�h
		if(rnd < 250){
			//---�C���t���G���X
			crbatCPUThink_SetMagicAtack(pChara,20,-1,0,NULL,1);
		} else if(rnd < 350){
			//---�_�[�N�~�X�g
			crbatCPUThink_SetMagicAtack(pChara,14,-1,0,NULL,1);
		} else if(rnd < 500){
			//---�G�N�X�e���h
			crbatCPUThink_SetMagicAtack(pChara,22);
		} else if(rnd < 750){
			//---���J�o���C�V����
			crbatCPUThink_SetMagicAtack(pChara,6);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 183){
		//---�����̎g��
		if(rnd < 600 && pChara->GetLP() < 100){
			//---�k�o�`�F���W
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_LPCHANGE,750);
		} else if(rnd < 250){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SUNAARASHI,100);
		} else if(rnd < 666){
			//---�z��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KYUKETSU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 186){
		//---�G�^�[�i����
		if(rnd < 333 && !pChara->GetTurnAtack()){
			//---�~���a
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_ENGETUZAN);
		} else if(rnd < 350){
			//---�a�肩����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 550){
			//---������
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 187){
		//---�G�^�[�i��������
		if(pBtChara[BATTLECHARA_STARTENEMY + 3].BattleInfo.Enemy.ActionType == 190
			&& turn == 0){
			//---�f�X�}�V�[�����N����
			pChara->Command.Main = BAT_COMMAND_WAIT;
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIDOSASERU);
			pChara->Command.Target = (ei_u32)&pBtChara[BATTLECHARA_STARTENEMY + 3];
		} else if((pChara->GetBtStatus() & BTST_CHINMOKU)
			|| pChara->GetMC() <= 120){
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 333 && !pChara->GetTurnAtack()){
			//---�e���W���b�W�����g
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,69);
		} else if(rnd < 333){
			crbatCPUThink_SetMagicAtack(pChara,68);
		} else if(rnd < 666){
			//---�X�[�p�[�Z��
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,57);
		} else if(rnd < 666 && !pChara->GetTurnAtack()){
			crbatCPUThink_SetMagicAtack(pChara,56);

		} else if(rnd < 750){
			//---�T�C�����X
			crbatCPUThink_SetMagicAtack(pChara,15,-1,0,NULL,1);
		} else if(rnd < 860){
			//---�R���t���[�W����
			crbatCPUThink_SetMagicAtack(pChara,18,-1,0,NULL,1);
		} else if(rnd < 950){
			//---�[���V�[���h
			crbatCPUThink_SetMagicAtack(pChara,30,-1,0,NULL,1);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 188){
		//---�G�^�[�i�����i�m���j
		if(pChara->GetMC() < 50 || (pChara->GetBtStatus() & BTST_CHINMOKU)){
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else if(crbatCPUGetEnemy() == 1){
			//---������l
			if(rnd < 350){
				//---�f�X�t�H�[�X
				crbatCPUThink_SetMagicAtack(pChara,21);
			} else if(rnd < 750){
				//---�R���t���[�W����
				crbatCPUThink_SetMagicAtack(pChara,18,-1,0,NULL,1);
			} else {
				crbatCPUThink_SetAtack(pChara);
			}
		} else if(rnd < 200){
			//---���C�t�E�B���h
			crbatCPUThink_SetMagicAtack(pChara,7);
		} else if(rnd < 300){
			//---���J�o���[�R
			crbatCPUThink_SetMagicAtack(pChara,6);
		} else if(rnd < 450){
			//---�v���e�N�V����
			crbatCPUThink_SetMagicAtack(pChara,13);
		} else if(rnd < 600){
			//---�G�N�X�e���h
			crbatCPUThink_SetMagicAtack(pChara,17);
		} else if(rnd < 800){
			//---�I�[�����e�C��
			crbatCPUThink_SetMagicAtack(pChara,14);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 189){
		//---�G�^�[�i�����i����j
		if(crbatCPUGetEnemy() == 1){
			if(rnd < 400 && !pChara->GetPersonalTurn()){
				//---�p���[�{��
				pChara->AddPersonalTurn(2);
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_POWERBOMB,120);
			} else if(rnd < 750){
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,50);
			} else {
				//---�T�C�����g�u���X
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_SILENTBREATH,50);
			}
		} else if(rnd < 100){
			//---�X���[�v�u���X
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,50);
		} else if(rnd < 400){
			//---�T�C�����g�u���X
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SILENTBREATH,50);
		} else if(rnd < 700 && !pChara->GetTurnAtack()){
			//---�p���[�{��
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_POWERBOMB,120);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 190){
		//---�f�X�}�V�[��
		if(crbatCPUGetEnemy() == 1 && pChara->GetBattleFlag(0) == 0){
			pChara->SetBattleFlag(0,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_BOSOKAISHI);
		} else if(turn == 0){
			pChara->Command.Main = BAT_COMMAND_WAIT;
		} else if(turn == 1){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIDOU);
		} else if(crbatCPUGetEnemy() == 1){
			if(rnd < 200){
				//---�|�C�Y���u���X
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_POISON,100);
			} else if(rnd < 500 && !pChara->GetTurnAtack()){
				//---�ؒf
				pChara->AddTurnAtack();
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_SETUDAN);
			} else if(rnd < 850 && !pChara->GetTurnAtack()
				&& !pChara->GetPersonalTurn()){
				//---�J�X�P�[�h�{��
				pChara->AddTurnAtack();
				pChara->AddPersonalTurn(3);
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_KASCADEBOMB,240);
			} else if(rnd < 750){
				//---�㉻����
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_JAKUKAKOSEN,50);
			} else {
				//---�ʏ�U��
				crbatCPUThink_SetAtack(pChara);
			}
		} else if(rnd < 200){
			//---�|�C�Y���u���X
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_POISON,50);
		} else if(rnd < 500 && !pChara->GetTurnAtack()){
			//---�ؒf
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SETUDAN);
		} else if(rnd < 750){
			//---�㉻����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_JAKUKAKOSEN,50);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 191){
		//---�Z���T�[�A�C�E��
		if(pChara->GetBattleFlag(0)){
			//---�唚��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_JIBAKU1,0,pChara);
		} else if(pChara->GetLP() < 200 || crbatCPUGetEnemy() == 1){
			//---�ړ�
			int x,y;
			pChara->SetBattleFlag(0,1);
			crbatCPU_GetPlayerCharaSide(pChara,&x,&y);
			crbatCPUThink_SetDefense(pChara,3,x,y);
		} else if(rnd < 200){
			//---�X���[�v�u���X
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,50);
		} else if(rnd < 400){
			//---�T�C�����g�u���X
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SILENTBREATH,50);
		} else if(rnd < 800){
			//---�A�C�r�[��
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_EYEBEAM,160);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	//-----------------------------------------------
	} else if(pChara->BattleInfo.Enemy.ActionType == 212){
		//---�V���G�C�m�[
		if(rnd < 80 * turn){
			//---���ڂ�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SABORU);
		} else if(rnd < 250){
			//---���邾��g
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_DARUDARUHA);
		} else if(rnd < 300){
			//---�Q��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NERU);
		} else if(rnd < 550){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_DAIKONRAN);
		} else if(rnd < 1000){
			//---������
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_AKUBI);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 216){
		//---�����E�j
		if(rnd < 9999){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOSO);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	}

	return crbatCPUThink7(pChara,turn,rnd);
}
