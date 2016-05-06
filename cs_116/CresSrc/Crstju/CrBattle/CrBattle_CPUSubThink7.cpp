CRBATCPU_API int crbatCPUThink7(CrBattleCharacter *pChara,int turn,int rnd)
{
	if(pChara->BattleInfo.Enemy.ActionType == 192){
		//---�u���b�h�\�[�h
		if(rnd < 280){
			//---�a�肩����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 400){
			//---������
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else if(rnd < 800){
			//---�z��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KYUKETSU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 193){
		//---�O���X�o�i�i
		if(rnd < 180){
			//---�I�[�����e�C��
			crbatCPUThink_SetMagicAtack(pChara,23);
		} else if(rnd < 360){
			//---�I�[�����e�C���i�S�j
			crbatCPUThink_SetMagicAtack(pChara,23,-1,0,NULL,1);
		} else if(rnd < 400){
			//---���J�o���C�V����
			crbatCPUThink_SetMagicAtack(pChara,6);
		} else if(rnd < 500){
			//---���C�t�E�B���h
			crbatCPUThink_SetMagicAtack(pChara,7);
		} else if(rnd < 600){
			//---�G�N�X�e���h
			crbatCPUThink_SetMagicAtack(pChara,22);
		} else if(rnd < 800){
			//---�v���e�N�V����
			crbatCPUThink_SetMagicAtack(pChara,13);
		} else {
			//---�C���t���G���X
			crbatCPUThink_SetMagicAtack(pChara,20,-1,0,NULL,1);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 194){
		//---�G�[�W�F���g
		if(rnd < 280 && !pChara->GetTurnAtack()){
			//---�p���[�{��
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_POWERBOMB,200);
		} else if(rnd < 400){
			//---�Ή�����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAENHOUSHA,100);
		} else if(rnd < 550){
			//---�X���[�v�u���X
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,30);
		} else if(rnd < 700){
			//---�T�C�����g�u���X
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SILENTBREATH,50);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 195){
		//---�S�[�����E�B�U�[�g
		if(rnd < 250 && !pChara->GetTurnAtack()){
			//---�^�C�_���E�F�C��
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,51);
		} else if(rnd < 300){
			//---�A�N�A�\�[�h
			crbatCPUThink_SetMagicAtack(pChara,50);
		} else if(rnd < 450){
			//---�x�[�^�X�R�[��
			crbatCPUThink_SetMagicAtack(pChara,68);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 196){
		//---�f�B���C�V����
		if(pChara->GetLP() < 50 && rnd < 500){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_LPCHANGE,1000);
		} else if(rnd < 333){
			//---���U�[�u
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_RESERVE);
		} else if(rnd < 460){
			//---������
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HANBUSSHITU);
		} else if(rnd < 600){
			//---�f�B�o�C�f�B���O
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_DIVIDING);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 197){
		//---�A�[�X�h���S��
		if(rnd < 250 && !pChara->GetTurnAtack()
			&& !pChara->GetPersonalTurn()){
			//---�A�[�X�N�E�F�C�N
			pChara->AddTurnAtack();
			pChara->AddPersonalTurn(2);
			crbatCPUThink_SetMagicAtack(pChara,63);
		} else if(rnd < 333){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SUNAARASHI,130);
		} else if(rnd < 600){
			//---���݂�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 198){
		//---�t�B���K���c�i�C�g
		if(rnd < 170){
			//---�a�肩����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 320){
			//---������
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else if(rnd < 470){
			//---�Ȃ��|��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGITAOSU);
		} else if(rnd < 720){
			//---�R���t���[�W����
			crbatCPUThink_SetMagicAtack(pChara,18);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 199){
		//---���̖S��
		if(rnd < 250 && !pChara->GetPersonalTurn()){
			//---�f�X�t�H�[�X
			pChara->AddPersonalTurn(3);
			crbatCPUThink_SetMagicAtack(pChara,21);
		} else if(rnd < 500 && crbatCPUGetEnemy() > 1){
			//---�̂肤��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NORIUTURU2);
		} else if(rnd < 700){
			//---�l�b����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_MCBUNKAI,50);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 200){
		//---���C���E�\�E��
		if(pChara->GetBtStatus() & BTST_CHINMOKU){
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 200 && !pChara->GetTurnAtack()){
			//---���C�W���O�T��
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,45);
		} else if(rnd < 250){
			//---�G�N�X�v���[�W����
			crbatCPUThink_SetMagicAtack(pChara,44);
		} else if(rnd < 450 && !pChara->GetTurnAtack()){
			//---�^�C�_���E�F�C��
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,51);
		} else if(rnd < 500){
			//---�A�N�A�\�[�h
			crbatCPUThink_SetMagicAtack(pChara,50);
		} else if(rnd < 700){
			//---�e���W���b�W�����g
			crbatCPUThink_SetMagicAtack(pChara,69);
		} else if(rnd < 750){
			//---�x�[�^�X�R�[��
			crbatCPUThink_SetMagicAtack(pChara,68);
		} else if(rnd < 850 && !pChara->GetBattleFlag(0)){
			//---���J�o���C�V����
			pChara->SetBattleFlag(0,1);
			crbatCPUThink_SetMagicAtack(pChara,6);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 201){
		//---�A�V�E�X
		if(rnd < 250 && !pChara->GetBattleFlag(0) && pChara->GetLP() > 400){
			//---�p���[�u�[�X�g�i�����j
			pChara->SetBattleFlag(0,1);
			crbatCPUThink_SetMagicAtack(pChara,19,BAT_TARGET_ME,0,pChara);
			pChara->Command.Target = (ei_u32)pChara;
		} else if(rnd < 400){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGURU);
		} else if(rnd < 650){
			//---�ːi
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOSSHIN);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 202){
		//---�h���S�����[�h
		if(rnd < 250 && !pChara->GetTurnAtack()
			&& !pChara->GetPersonalTurn()){
			//---��Ή�
			pChara->AddTurnAtack();
			pChara->AddPersonalTurn(3);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO2,250);
		} else if(rnd < 400){
			//---��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,140);
		} else if(rnd < 600){
			//---���݂�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 203){
		//---���֋M��
		if(rnd < 250 && pChara->GetTurnAtack() <= 0
			&& !pChara->GetPersonalTurn()){
			//---���֘O����
			pChara->AddTurnAtack();
			pChara->AddPersonalTurn(2);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_ROUOU);
		} else if(rnd < 350){
			//---�����a��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_ONSOKU);
		} else if(rnd < 500){
			//---�a�肩����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 700 && pChara->GetLP() < 200 && !pChara->GetBattleFlag(0)){
			//---�Đ�
			pChara->SetBattleFlag(0,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SAISEI);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 213){
		//---�o�i�i�~���[�^���g
		if(rnd < 250){
			//---���C�W���O�T��
			pChara->SetBattleFlag(0,0);
			crbatCPUThink_SetMagicAtack(pChara,45);
		} else if(rnd < 500){
			//---�e���W���b�W�����g
			pChara->SetBattleFlag(0,0);
			crbatCPUThink_SetMagicAtack(pChara,69);
		} else if(rnd < 750 + pChara->GetBattleFlag(0) * 250){
			//---�X�[�p�[�Z��
			pChara->SetBattleFlag(0,0);
			crbatCPUThink_SetMagicAtack(pChara,57);
		} else if(rnd < 950 && pChara->GetLP() > 600){
			//---�J�I�X���[�h
			pChara->SetBattleFlag(0,1);
			crbatCPUThink_SetMagicAtack(pChara,27);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	//---------------------------------------------------
	} else if(pChara->BattleInfo.Enemy.ActionType == 217){
		//---�J�[
		if(rnd < 250 && pChara->GetTurnAtack() == 0
			&& !pChara->GetPersonalTurn()){
			//---��
			pChara->AddTurnAtack();
			pChara->AddPersonalTurn(3);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,240);
		} else if(rnd < 300){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,120);
		} else if(rnd < 350){
			//---�H�ׂ�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TABERU);
		} else if(rnd < 600){
			//---���݂�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else if(rnd < 700 && crbatCPUGetEnemy() > 1){
			//---�Q��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NERU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 218){
		//---�N�_�[
		if(turn == 0){
			crbatCPUThink_SetMagicAtack(pChara,19,-1,0,&pBtChara[BATTLECHARA_STARTENEMY]);
		} else if(turn == 1){
			crbatCPUThink_SetMagicAtack(pChara,19,-1,0,&pBtChara[BATTLECHARA_STARTENEMY + 1]);
		} else if(rnd < 250 && pChara->GetTurnAtack() == 0
			&& !pChara->GetPersonalTurn()){
			//---����
			pChara->AddTurnAtack();
			pChara->AddPersonalTurn(3);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_FUBUKI,200);
		} else if(rnd < 300){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGITAOSU);
		} else if(crbatCPUGetEnemy() > 1){
			if(rnd < 400){
				//---�X���[�s���O
				crbatCPUThink_SetMagicAtack(pChara,11);
			} else if(rnd < 500){
				//---�_�[�N�~�X�g
				crbatCPUThink_SetMagicAtack(pChara,14);
			} else if(rnd < 600){
				//---�T�C�����X
				crbatCPUThink_SetMagicAtack(pChara,15);
			} else if(rnd < 700){
				//---�R���t���[�W����
				crbatCPUThink_SetMagicAtack(pChara,18);
			} else if(rnd < 800){
				//---�p���[�u�[�X�g
				crbatCPUThink_SetMagicAtack(pChara,19);
			} else if(rnd < 900){
				//---�G�N�X�e���h
				crbatCPUThink_SetMagicAtack(pChara,22);
			} else {
				//---�ʏ�U��
				crbatCPUThink_SetAtack(pChara);
			}
		} else if(rnd < 350){
			//---�v���e�N�V����
			crbatCPUThink_SetMagicAtack(pChara,13);
		} else if(rnd < 450){
			//---�t�H�[�X�V�[���h
			crbatCPUThink_SetMagicAtack(pChara,17);
		} else if(rnd < 650){
			//---�p���[�u�[�X�g
			crbatCPUThink_SetMagicAtack(pChara,19);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 219){
		//---�h���S���\�E��
		if((pChara->GetBtStatus() & BTST_MAHI)){
			if(rnd < 250){
				//---���C�W���O�T��
				crbatCPUThink_SetMagicAtack(pChara,45);
			} else if(rnd < 500){
				//---�^�C�_���E�F�C��
				crbatCPUThink_SetMagicAtack(pChara,51);
			} else if(rnd < 750){
				//---�X�[�p�[�Z��
				crbatCPUThink_SetMagicAtack(pChara,57);
			} else {
				//---�A�[�X�N�E�F�C�N
				crbatCPUThink_SetMagicAtack(pChara,63);
			}
		} else if(pChara->GetBattleFlag(0) == 1){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_DAIKAEN,5000);
		} else if(turn % 5 == 0 && turn != 0){
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_IKIWOSUIKOMU);
		} else if(rnd < 400 && pChara->GetPersonalTurn() == 0){
			//---�u���X
			pChara->AddPersonalTurn(2);
			int rnd2 = eiRnd(1000);
			if(rnd < 250){
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO2,275);
			} else if(rnd < 500){
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_FUBUKI2,275);
			} else if(rnd < 750){
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOPPU2,275);
			} else {
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_SUNAARASHI2,275);
			}
		} else if(rnd < 250){
			//---���݂�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else if(rnd < 400){
			//---�Ȃ��|��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGITAOSU);
		} else if(rnd < 500){
			//---�u���X���[�v�u���X
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,100);
		} else if(rnd < 600){
			//---�T�C�����g�u���X
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SILENTBREATH,100);
		} else if(rnd < 700){
			//---�Ռ��g
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SHOGEKIHA);
		} else if(rnd < 900){
			//---�����g
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CHOUONPA);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 220){
		//---�o���A�[�Q�O�O�O
		if(rnd < 250){
			//---�X���[�v�u���X
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,10);
		} else if(rnd < 500){
			//---�T�C�����g�u���X
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SILENTBREATH,10);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}

		//---�J�I�X���[�h�g���Ă�̂�T���čU��
		int a;
		for(a = 0;a < 4;a ++){
			if(pBtChara[a].DoExist()){
				if(pBtChara[a].GetKaosTurn() > 0){
					pChara->Command.Target = (ei_u32)&pBtChara[a];
					break;
				}
			}
		}
	//---------------------------------------------------
	} else if(pChara->BattleInfo.Enemy.ActionType == 223){
		//---�N���C�V��
		if(turn == 0){
			pChara->Command.Main = BAT_COMMAND_WAIT;
			pChara->Command.Sub[0] = 0;
		} else if(turn == 1){
			//---�X�[�p�[�Z��
			pChara->AddPersonalTurn(3);
			pChara->SetBattleFlag(0,0);
			crbatCPUThink_SetMagicAtack(pChara,57);
			pChara->Command.Target = (ei_u32)&pBtChara[0];
			pChara->EnableFirstAtack(1);
		} else if(pChara->GetBattleFlag(0) == 1){
			//---�|��Ă�
			pChara->SetBattleFlag(1,pChara->GetBattleFlag(1) - 1);
			if(pChara->GetBattleFlag(1) == 1){
				//---�ϐg
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_HENSHIN);
			} else {
				pChara->Command.Main = BAT_COMMAND_WAIT;
			}
		} else if(rnd < 300 && pChara->GetPersonalTurn() == 0){
			//---�X�[�p�[�Z��
			pChara->AddPersonalTurn(3);
			crbatCPUThink_SetMagicAtack(pChara,57);
		} else if(rnd < 500 && pChara->GetPersonalTurn() == 0){
			//---�^�C�_���E�F�C��
			pChara->AddPersonalTurn(3);
			crbatCPUThink_SetMagicAtack(pChara,51);

		} else if(rnd < 100){
			//---�X���[�s���O
			crbatCPUThink_SetMagicAtack(pChara,11,-1,0,NULL,1);
		} else if(rnd < 200){
			//---�R���t���[�W����
			crbatCPUThink_SetMagicAtack(pChara,18,-1,0,NULL,1);
		} else if(rnd < 300){
			//---�C���t���G���X
			crbatCPUThink_SetMagicAtack(pChara,20,-1,0,NULL,1);
		} else if(rnd < 400){
			//---�x�[�^�X�R�[��
			crbatCPUThink_SetMagicAtack(pChara,68);
		} else if(rnd < 450){
			//---�e���W���b�W�����g
			crbatCPUThink_SetMagicAtack(pChara,69);
		} else if(rnd < 500){
			//---�_�C���u���X
			crbatCPUThink_SetMagicAtack(pChara,62);
		} else if(rnd < 600){
			//---�X���[�s���O
			crbatCPUThink_SetMagicAtack(pChara,11,-1,0,NULL,1);
		} else if(rnd < 700){
			//---�R���t���[�W����
			crbatCPUThink_SetMagicAtack(pChara,18,-1,0,NULL,1);
		} else if(rnd < 800){
			//---�C���t���G���X
			crbatCPUThink_SetMagicAtack(pChara,20,-1,0,NULL,1);
		} else if(rnd < 875){
			//---�f�X�t�H�[�X
			crbatCPUThink_SetMagicAtack(pChara,21);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 224){
		//---�N���C�V���E�ϐg��
		static int prev[2] = {0,0};
		int loop = 0;
		ei_s32 keep[BATLLECHARA_FLAG_MAX];

		memcpy(keep,pChara->OnlyInfo.Flags,sizeof(keep));
	do {
		CrBattleCharacter *pnear = crbatCPU_PlayerIsSekkin(pChara,1);

		loop ++;

		//---�t���O�����ɖ߂�
		memcpy(pChara->OnlyInfo.Flags,keep,sizeof(pChara->OnlyInfo.Flags));
		pChara->Command.Sub[0] = 0;

		if(pChara->GetBattleFlag(6) > 0){
			pChara->SetBattleFlag(6,pChara->GetBattleFlag(6) - 1);
		}
		//---���[�C���J�E���^�[
		if(pChara->GetBattleFlag(8) > 0){
			pChara->SetBattleFlag(8,pChara->GetBattleFlag(8) - 1);
		}
		//---�k�o��������J�E���^�[
		if(pChara->GetLP() < 250){
			pChara->SetAbility(BTAB_S_COUNTER75,1);
		} else if(pChara->GetLP() < 1000){
			pChara->SetAbility(BTAB_S_COUNTER50,1);
			pChara->CharaInfo.magic = 148;
		} else if(pChara->GetLP() < 3000){
			pChara->SetAbility(BTAB_S_COUNTER25,1);
		} else if(pChara->GetLP() < 4000){
			pChara->CharaInfo.magic = 143;
		} else if(pChara->GetLP() < 8000){
			pChara->CharaInfo.magic = 138;
		}

		int a,c,st,live_friend;
		for(a = 0,c = 0,live_friend = 0;a < 4;a ++){
			if(pBtChara[a].IsKizetu() == 0)
				live_friend ++;

			st = pBtChara[a].GetBtStatus();
			if(st & BTST_POWER)
				c ++;
			if(st & BTST_EXTEND)
				c ++;
			if(st & BTST_FSHIELD)
				c ++;
			if(st & BTST_SOUL)
				c ++;
		}

		//----------------------------------------------------
		if(pChara->GetBattleFlag(3) == 1){
			//---���[�C��
			pChara->SetBattleFlag(8,2);
			pChara->SetBattleFlag(3,0);
			pChara->SetBattleFlag(12,1);
			pChara->AddPersonalTurn(2 - (pChara->GetLP() < 9000 ? 1 : 0));
			crbatCPUThink_SetMagicAtack(pChara,79);
		//----------------------------------------------------
		//---�c��P�Q�O�O��؂�����
		} else if(pChara->GetLP() <= 1200){
			pChara->SetBattleFlag(13,pChara->GetBattleFlag(13) + 1);
			if((rnd < 450 || pChara->GetBattleFlag(13) >= 2)
				&& (turn % 2) == 0){
				//---�C���t���[�V����
				pChara->SetBattleFlag(13,0);
				crbatCPUThink_SetMagicAtack(pChara,80);
			} else if((rnd < 450 || pChara->GetBattleFlag(13) >= 2)
				&& (turn % 2) == 1){
				//---�v���[�g�E�F�C��
				pChara->SetBattleFlag(13,0);
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_LINEKOGEKI);
			} else if(rnd < 650){
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_CRFUBUKI,200);
			} else if(rnd < 850){
				//---�؂��
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_SINGLEKOGEKI);
			} else {
				//---�I�[�����e�C��
				crbatCPUThink_SetMagicAtack(pChara,23,-1,0,NULL,1);
			}
		} else if(pChara->GetBattleFlag(4) == 0){
			//---�ϐg��A�ŏ��̃^�[��
			//---�C���o���f�B�e�B
			pChara->SetBattleFlag(4,1);
			crbatCPUThink_SetMagicAtack(pChara,25);
		} else if(pChara->GetBattleFlag(3) == 2){
			//---�������U��
			pChara->SetBattleFlag(3,1);
			crbatCPUThink_SetAtack(pChara);
			pChara->Command.Target = (ei_u32)pChara;
		} else if(pnear != NULL && rnd < 500
			&& pChara->GetBattleFlag(10) <= 16){
			//---�ړ�
			pChara->SetBattleFlag(10,pChara->GetBattleFlag(10) + 1);

//			crbatCPUThink_SetDefense(pChara,3);
			//---�\�j�b�N�E�F�C��
			int old = pChara->BattleInfo.Enemy.IQ;
			pChara->BattleInfo.Enemy.IQ = 2;
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_TOBASU,800);
			pChara->BattleInfo.Enemy.IQ = old;

		} else if(rnd < 600 && crbatCPU_PlayerIsBaraBara(pChara,3)
			&& pChara->GetBattleFlag(14) <= 3){
			//---�΂�΂�ɂȂ�����W�߂�
			pChara->SetBattleFlag(14,pChara->GetBattleFlag(14) + 1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_GRAVITY);
		} else if(rnd < 150 + (pChara->GetBattleFlag(12) == 0 ? 350 : 0)
			&& pChara->GetBattleFlag(3) == 0
			&& pChara->GetBattleFlag(6) == 0
			&& pChara->GetBattleFlag(5) == 1
			&& pChara->GetBattleFlag(8) == 0
			&& pChara->GetLP() >= 6500){
			//---���[�C������
			pChara->SetBattleFlag(5,0);
			pChara->SetBattleFlag(6,3);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_RUINJUNBI);
		} else if(1600 < pChara->GetLP() && pChara->GetLP() < 4000 && pChara->GetBattleFlag(11) == 0){
			//---�G�N�X�e���h
			pChara->SetBattleFlag(11,1);
			crbatCPUThink_SetMagicAtack(pChara,22);
		} else if(rnd < 250
			&& pChara->GetPersonalTurn() == 0 && pChara->GetLP() < 6500
			&& pChara->GetBattleFlag(9) == 0){
			//---�v���[�g�E�F�C��
			pChara->AddPersonalTurn(2);
			pChara->SetBattleFlag(9,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_LINEKOGEKI);
		} else if(rnd < 500 && pChara->GetPersonalTurn() == 0){
			//---�C���t���[�V����
			pChara->SetBattleFlag(5,1);
			pChara->SetBattleFlag(9,0);
			pChara->AddPersonalTurn(3 - (pChara->GetLP() < 3000 ? 1 : 0));
			crbatCPUThink_SetMagicAtack(pChara,80);
		} else if(rnd < 100){
			//---�I�[�����e�C��
			if(eiRnd(1000) < 500){
				crbatCPUThink_SetMagicAtack(pChara,23);
			} else {
				crbatCPUThink_SetMagicAtack(pChara,23,-1,0,NULL,1);
			}
		} else if(rnd < 200 && live_friend > 2){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CRFUBUKI,200);
		} else if(rnd < 250 && live_friend > 1){
			//---�P�̍U��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_SINGLEKOGEKI);
		} else if(rnd < 200 && pChara->GetLP() < 6000){
			//---�P�̍U��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_SINGLEKOGEKI);
		} else if(rnd < 150){
			//---�x�[�^�X�R�[��
			crbatCPUThink_SetMagicAtack(pChara,68);
		} else if(rnd < 220 && live_friend > 2){
			//---�X�[�p�[�Z��
			crbatCPUThink_SetMagicAtack(pChara,57);
		} else if(rnd < 300 && live_friend > 2){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CRFUBUKI,200);
		} else if(rnd < 370){
			if(pChara->GetLP() < 2000){
				//---�v���[�g�E�F�C��
				pChara->AddPersonalTurn(2);
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_LINEKOGEKI);
			} else {
				if(pChara->GetLP() < 9000 && eiRnd(1000) < 500 && live_friend > 1){
					//---�P�̍U��
					crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_SINGLEKOGEKI);
				} else {
					//---�ʏ�U��
					crbatCPUThink_SetAtack(pChara);
				}
			}
		} else if(rnd < 530){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CRFUBUKI,200);
		} else if(rnd < 650){// && pChara->GetBattleFlag(7) == 0){
			//---�I�[�����e�C��
			pChara->SetBattleFieldStartPos(7,1);
			if(eiRnd(1000) < 500){
				crbatCPUThink_SetMagicAtack(pChara,23);
			} else {
				crbatCPUThink_SetMagicAtack(pChara,23,-1,0,NULL,1);
			}
/*		} else if(rnd < 650 && pChara->GetBattleFlag(7) == 1){
			//---�C���t���G���X
			pChara->SetBattleFieldStartPos(7,0);
			crbatCPUThink_SetMagicAtack(pChara,20,-1,0,NULL,1);*/
		} else if(rnd < 730){
			//---�U��
			if(pChara->GetLP() < 5000 && pChara->GetPersonalTurn() == 0
				&& pChara->GetBattleFlag(9) == 0
				&& live_friend > 2){
				//---�v���[�g�E�F�C��
				pChara->AddPersonalTurn(2);
				pChara->SetBattleFlag(9,1);
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_LINEKOGEKI);
			} else {
				if((eiRnd(1000) < 500
					|| pChara->GetLP() < 5000)
					&& live_friend > 2){
					//---�P�̍U��
					crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_SINGLEKOGEKI);
				} else {
					//---�ʏ�U��
					crbatCPUThink_SetAtack(pChara);
				}
//				crbatCPUThink_SetAtack(pChara);
			}
		} else if(rnd < 800
			&& pChara->GetLP() < 4000
			&& live_friend > 2){
			//---�v���[�g�E�F�C��
			pChara->AddPersonalTurn(2);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_LINEKOGEKI);
		} else if(rnd < 800 && live_friend > 2){
			//---�X�[�p�[�Z��
			crbatCPUThink_SetMagicAtack(pChara,57);
		} else if(rnd < 800){
			//---�x�[�^�X�R�[��
			crbatCPUThink_SetMagicAtack(pChara,68);
		} else {
			if(rnd < 950 && eiRnd(1000) < c * 500){
				//---�C���o���f�B�e�B
				crbatCPUThink_SetMagicAtack(pChara,25);
			} else {
				if(pChara->GetLP() < 5000 && pChara->GetPersonalTurn() == 0
					&& pChara->GetBattleFlag(9) == 0){
					//---�v���[�g�E�F�C��
					pChara->AddPersonalTurn(2);
					pChara->SetBattleFlag(9,1);
					crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_LINEKOGEKI);
				} else if(pChara->GetLP() < 9000 && eiRnd(1000) < 500){
					//---�P�̍U��
					crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_SINGLEKOGEKI);
				} else if(pChara->GetLP() < 5500 && live_friend > 1){
					//---�P�̍U��
					crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_SINGLEKOGEKI);
				} else {
					//---�ʏ�U��
					crbatCPUThink_SetAtack(pChara);
				}
			}
		}

		CrBattleCharacter *pKaos = NULL;
		for(a = 0;a < 4 && loop <= 1;a ++){
			if(pBtChara[a].DoExist() && !pBtChara[a].IsKizetu()
				 && (pBtChara[a].GetBtStatus() & BTST_KAOS)){
				if(pBtChara[a].GetKaosTurn() >= 3
					&& pChara->GetBattleFlag(3) == 0
					&& pChara->GetBattleFlag(6) == 0
					&& !(pChara->Command.Main == BAT_COMMAND_MAGIC && pChara->Command.Sub[0] != 79)
					&& eiRnd(1000) < 500){
					//---�C���o���f�B�e�B
					crbatCPUThink_SetMagicAtack(pChara,25);
					break;
				}

				if(pBtChara[a].GetKaosTurn() >= 2){
					pKaos = &pBtChara[a];
					break;
				}
			}
		}
		if(pKaos != NULL && pChara->Command.Target != (ei_u32)pChara){
			//---�J�I�X���[�h�Q�ŁA�^�[�Q�b�g�������łȂ���΁A�Đݒ�
			pChara->Command.Target = (ei_u32)pKaos;
		}

//		crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_LINEKOGEKI);
//		crbatCPUThink_SetMagicAtack(pChara,80);
		rnd = eiRnd(1000);
	} while(pChara->Command.Main == prev[0] && pChara->Command.Sub[0] == prev[1]
		&& loop <= 10);

		prev[0] = pChara->Command.Main;
		prev[1] = pChara->Command.Sub[0];
	}
	return crbatCPUThink8(pChara,turn,rnd);
}
