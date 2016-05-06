CRBATCPU_API int crbatCPUThink4(CrBattleCharacter *pChara,int turn,int rnd)
{
	if(pChara->BattleInfo.Enemy.ActionType == 119){
		//---��C���u
		if(pChara->GetLP() < 320 && pChara->GetBattleFlag(0) == 0){
			//---LP���R�Q�O�ȉ��ɂȂ�����ړ��J�n
			int x,y;
			pChara->SetBattleFlag(0,1);
			crbatCPU_GetPlayerCharaSide(pChara,&x,&y);
			crbatCPUThink_SetDefense(pChara,3,x,y);
		} else if(pChara->GetBattleFlag(0)){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_JIBAKU1,0,pChara);
		} else if(rnd < 500 && pBtChara[BATTLECHARA_STARTENEMY].DoExist()){
			//---�C��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SHURI,0,&pBtChara[BATTLECHARA_STARTENEMY + 2]);
		} else if(rnd < 700 && pChara->GetBattleFlag(1) == 0
			 && pBtChara[BATTLECHARA_STARTENEMY].DoExist()){
			//---�@�\�ǉ�
			pChara->SetBattleFlag(1,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KINOUTUIKA,0,&pBtChara[BATTLECHARA_STARTENEMY + 2]);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 120){
		//---�h�q�V�X�e��
		if(turn == 0){
			//---�o���A�[�W�J
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_BARRIERTENKAI);
		} else if(turn == 1){
			//---�J�X�P�[�h�{������
			pChara->SetBattleFlag(0,1);
			pChara->ResetPersonalTurn();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KASCADE_JUNBI);
		} else if(pChara->GetLP() < 2100
			&& pChara->GetBattleFlag(0) == 1){
			//---�J�X�P�[�h�{���@�\����
			pChara->SetBattleFlag(0,2);
			pChara->ResetPersonalTurn();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KASCADE_KYOKA);
		} else if(pChara->GetLP() < 600
			&& pChara->GetBattleFlag(0) == 2){
			//---�������S��
			pChara->ResetPersonalTurn();
			pChara->SetBattleFlag(0,3);
			pChara->AddPersonalTurn(3);
			pChara->SetBattleFlag(1,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HANBUSSHITU_ZENTAI);
/*			//---����������
			pChara->SetBattleFlag(0,3);
			pChara->ResetPersonalTurn();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HANBUSSITU_JUNBI);*/
		} else if(pChara->GetBattleFlag(0) == 3
			&& pChara->GetBattleFlag(1) == 1){
			//---�J�X�P�[�h�{���o�͍ő�
			pChara->SetBattleFlag(0,4);
			pChara->ResetPersonalTurn();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KASCADE_SAIDAI);

/*		} else if(!pChara->GetPersonalTurn()
			&& pChara->GetBattleFlag(0) == 3 && pChara->GetBattleFlag(1) == 0){
			//---�������S��
			pChara->AddPersonalTurn(3);
			pChara->SetBattleFlag(1,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HANBUSSHITU_ZENTAI);
*/
		} else if(rnd < 200 && !pChara->GetPersonalTurn()
			&& pChara->GetLP() < 2000){
			//---�Z�H
			pChara->AddPersonalTurn(2);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SHINSHOKU);
		} else if(rnd < 300){
			//---������
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HANBUSSHITU);
		} else if(rnd < 400 && pChara->GetBattleFlag(0) == 4){
			//---���[�U�[
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_LAYZERBEAM,120);
		} else if(rnd < 400 && pChara->GetPersonalTurn() <= 1){
			//---���[�U�[����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_LAYZERBEAM,90);
		} else if(rnd < 400){
			//---���[�U�[����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_LAYZERBEAM,55);
		} else if(rnd < 550 && pChara->GetBattleFlag(0) == 4){
			//---�Ή�����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAENHOUSHA,130);
		} else if(rnd < 550 && pChara->GetPersonalTurn() <= 1){
			//---�Ή�����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAENHOUSHA,110);
		} else if(rnd < 550){
			//---�Ή�����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAENHOUSHA,55);
		} else if((rnd < 850 || (turn + 1) % 4 == 0) && !pChara->GetPersonalTurn()
			&& pChara->GetBattleFlag(0) >= 1){
			//---�J�X�P�[�h�{��
			pChara->AddPersonalTurn(3);
			if(pChara->GetBattleFlag(0) == 0){
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_POWERBOMB,120);
			} else if(pChara->GetBattleFlag(0) == 1){
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_KASCADEBOMB,140);
			} else if(pChara->GetBattleFlag(0) <= 3){
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_KASCADEBOMB,160);
			} else if(pChara->GetBattleFlag(0) == 4){
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_KASCADEBOMB,185);
			}
		} else if(rnd < 800 && pChara->GetBattleFlag(2) == 0
			&& crbatCPUGetEnemy() == 1){
			//---�O���r�e�B
			pChara->SetBattleFlag(2,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_GRAVITY);
		} else if(rnd < 800){
			//---�U��
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 950 && crbatCPU_PlayerIsBaraBara(pChara,2)
			&& crbatCPUGetEnemy() == 1){
			//---�΂�΂�ɂȂ�����W�߂�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_GRAVITY);
		} else if(rnd < 900){
			//---�X���[�v�u���X
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,30);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	
	} else if(pChara->BattleInfo.Enemy.ActionType == 121){
		//---�G�^�[�i�����i��m�j
		if(crbatCPUGetEnemy() == 1){
			if(rnd < 500 && !pChara->GetPersonalTurn()){
				pChara->AddPersonalTurn(2);
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_ENGETUZAN);
			} else {
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
			}
		} else if(rnd < 300){
			//---�a�肩����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 500){
			//---������
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else if(rnd < 700 && !pChara->GetTurnAtack()){
			//---�~���a
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_ENGETUZAN);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 122){
		//---�G�^�[�i�����i���@�g���j
		if(pChara->GetMC() < 100 || (pChara->GetBtStatus() & BTST_CHINMOKU)){
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else if(crbatCPUGetEnemy() == 1){
			//---������l
			if(rnd < 350 && !pChara->GetPersonalTurn()){
				pChara->AddPersonalTurn(2);
				crbatCPUThink_SetMagicAtack(pChara,44);
			} else if(rnd < 700 && !pChara->GetPersonalTurn()){
				pChara->AddPersonalTurn(2);
				crbatCPUThink_SetMagicAtack(pChara,50);
			} else {
				crbatCPUThink_SetMagicAtack(pChara,55);
			}
		} else if(rnd < 333 && !pChara->GetTurnAtack()){
			//---�G�N�X�v���[�W����
			pChara->AddTurnAtack();
			if(!pChara->GetPersonalTurn()){
				pChara->AddPersonalTurn(2);
				crbatCPUThink_SetMagicAtack(pChara,44);
			} else {
				crbatCPUThink_SetMagicAtack(pChara,43);
			}
		} else if(rnd < 333){
			//---�t���A�E�F�C��
			crbatCPUThink_SetMagicAtack(pChara,43);
		} else if(rnd < 666 && !pChara->GetTurnAtack()){
			//---�A�N�A�\�[�h
			pChara->AddTurnAtack();
			if(!pChara->GetPersonalTurn()){
				pChara->AddPersonalTurn(2);
				crbatCPUThink_SetMagicAtack(pChara,50);
			} else {
				crbatCPUThink_SetMagicAtack(pChara,49);
			}
		} else if(rnd < 900){
			//---�E�B���h�I�[�u
			crbatCPUThink_SetMagicAtack(pChara,55);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 123){
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
		} else if(rnd < 150){
			//---���C�t�E�B���h
			crbatCPUThink_SetMagicAtack(pChara,7);
		} else if(rnd < 300){
			//---���J�o���[�R
			crbatCPUThink_SetMagicAtack(pChara,6);
		} else if(rnd < 450){
			//---�v���e�N�V����
			crbatCPUThink_SetMagicAtack(pChara,13);
		} else if(rnd < 600){
			//---�t�H�[�X�V�[���h
			crbatCPUThink_SetMagicAtack(pChara,17);
		} else if(rnd < 800){
			//---�_�[�N�~�X�g
			crbatCPUThink_SetMagicAtack(pChara,14);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 124){
		//---�G�^�[�i�����i����j
		if(crbatCPUGetEnemy() == 1){
			if(rnd < 400 && !pChara->GetPersonalTurn()){
				//---�p���[�{��
				pChara->AddPersonalTurn(2);
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_POWERBOMB,100);
			} else if(rnd < 750){
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,40);
			} else {
				//---�T�C�����g�u���X
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_SILENTBREATH,40);
			}
		} else if(rnd < 200){
			//---�X���[�v�u���X
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,40);
		} else if(rnd < 400){
			//---�T�C�����g�u���X
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SILENTBREATH,40);
		} else if(rnd < 800 && !pChara->GetTurnAtack()){
			//---�p���[�{��
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_POWERBOMB,100);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}

	//---
	} else if(pChara->BattleInfo.Enemy.ActionType == 126){
		//---�G�C�m�[
		if(rnd < 200){
			//---������
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_AKUBI);
		} else if(rnd < 400){
			//---���邾��g
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_DARUDARUHA);
		} else if(rnd < 600){
			//---�Q��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NERU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 127){
		//---�X�g�����W�^�L�V�[�h
		if(rnd < 333){
			//---�^�L�V�[�h�r�[��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TAKISIDOBEAM,80);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 128){
		//---�g�[�e���|�[��
		if(rnd < 200){
			//---�T�C�����X
			crbatCPUThink_SetMagicAtack(pChara,15);
		} else if(rnd < 500 && !pChara->GetTurnAtack()){
			//---�E�B���h�I�[�u
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,55);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 131){
		//---�G�h
		if(turn == 0){
			//---���[�U�[����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_LAYZERBEAM,80,&pBtChara[0]);
		} else if(pChara->GetBattleFlag(1)){
			//---���߂Ă���A�J�X�P�[�h�{��
			pChara->SetBattleFlag(1,0);
			pChara->AddPersonalTurn(3);
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KASCADEBOMB,220);
		} else if(pChara->GetPersonalTurn() >= 2){
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 100){
			//---��������
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KONRANKOUSEN,30);
		} else if(rnd < 350){
			//---���[�U�[����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_LAYZERBEAM,80);
		} else if(rnd < 500){
			//---���ꎕ�N���b�V��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_IREBACRASH);
		} else if(rnd < 600 && crbatCPUGetEnemy() == 1){
			//---������
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HANBUSSHITU);
		} else if(rnd < 600){
			//---�Ƃ���
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOKASU);
		} else if(rnd < 800 && !pChara->GetPersonalTurn()
			&& !pChara->GetTurnAtack()){
			//---�J�X�P�[�h�{��
			pChara->AddPersonalTurn(3);
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KASCADEBOMB,120);
//			pChara->SetBattleFlag(0,1);
//			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TAMERU);
		} else if(rnd < 900 && crbatCPUGetEnemy() == 1){
			//---���߂�
			pChara->SetBattleFlag(1,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TAMERU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 132){
		//---���[�t�B�A
		if(pChara->GetMC() < 70){
			//---�l�b�����Ȃ��Ȃ�����ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else if(turn == 1){
			//---�E�B���h�I�[�u
			crbatCPUThink_SetMagicAtack(pChara,55,-1,0,&pBtChara[0]);
		} else if(turn == 0){
			//---�^�[���ŏ�
			//---�G�N�X�e���h
			crbatCPUThink_SetMagicAtack(pChara,22,-1,0,pChara);
/*		} else if(pChara->GetLP() <= 400 && !pChara->GetBattleFlag(1)){
			//---���J�o���C�V����
			pChara->SetBattleFlag(1,1);
			crbatCPUThink_SetMagicAtack(pChara,6);*/
		} else if(rnd < 333 && !pChara->GetTurnAtack()
			 && !pChara->GetPersonalTurn()){
			//---�_�E���o�[�X�g
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,56);
		} else if(rnd < 333){
			//---�E�B���h�I�[�u
			crbatCPUThink_SetMagicAtack(pChara,55);
		} else if(rnd < 666 && !pChara->GetTurnAtack() && !pChara->GetPersonalTurn()
			&& crbatCPUGetEnemy() == 1){
			//---���C�W���O�T��
			pChara->AddPersonalTurn(2);
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,45);
		} else if(rnd < 666){
			//---�G�N�X�v���[�W����
			crbatCPUThink_SetMagicAtack(pChara,44);
		} else if(rnd < 850){
			//---�x�[�^�X�R�[��
			crbatCPUThink_SetMagicAtack(pChara,68);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 133){
		//---�X�g�[���S�[����
		if(rnd < 300){
			//---�Ȃ���
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGURU);
		} else if(rnd < 500){
			//---�ːi
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOSSHIN);
		} else if(rnd < 650 && pChara->GetTurnAtack() <= 1){
			//---�Ȃ��|��
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGITAOSU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 134){
		//---�L���[�{��
		if(pChara->GetBattleFlag(0)){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_JIBAKU1,0,pChara);
		} else if(rnd < 600){
			//---�ړ�
			int x,y;
			pChara->SetBattleFlag(0,1);
			crbatCPU_GetPlayerCharaSide(pChara,&x,&y);
			crbatCPUThink_SetDefense(pChara,3,x,y);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 135){
		//---�G���V�F���g�\�[�h
		if(rnd < 280){
			//---�a�肩����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 400){
			//---�ːi
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else if(rnd < 700 && !pChara->GetPersonalTurn()
			&& turn == 0 && crbatCPUGetEnemy() > 1){
			//---�p���[�u�[�X�g
			pChara->AddPersonalTurn(10);
			crbatCPUThink_SetMagicAtack(pChara,19,BAT_TARGET_ME);
			pChara->Command.Target = (ei_u32)pChara;
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 136){
		//---�O���[���h���S��
		if(crbatCPUGetEnemy() == 1 && rnd < 500){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,140);
		} else if(rnd < 250 && !pChara->GetTurnAtack()){
			//---��
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,140);
		} else if(rnd < 400){
			//---��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,75);
		} else if(rnd < 500){
			//---�X���[�v�u���X
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,30);
		} else if(rnd < 750){
			//---���݂�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 137){
		//---�o�i�i���炰
		if(rnd < 350){
			//---�I�[�����e�C��
			crbatCPUThink_SetMagicAtack(pChara,23);
		} else if(rnd < 450){
			//---���J�o���C�V����
			crbatCPUThink_SetMagicAtack(pChara,6);
		} else if(rnd < 550){
			//---���C�t�E�B���h
			crbatCPUThink_SetMagicAtack(pChara,7);
		} else if(rnd < 600){
			//---�G�N�X�e���h
			crbatCPUThink_SetMagicAtack(pChara,22);
		} else if(rnd < 750){
			//---�[���V�[���h
			crbatCPUThink_SetMagicAtack(pChara,30,-1,0,NULL,1);
		} else {
			//---�R���t���[�W����
			crbatCPUThink_SetMagicAtack(pChara,18,-1,0,NULL,1);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 138){
		//---�}�W�V�����{�[��
		if(rnd < 280 && !pChara->GetTurnAtack()
			&& pChara->GetPersonalTurn() == 0){
			//---�_�E���o�[�X�g
			pChara->AddPersonalTurn(2);
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,56);
		} else if(rnd < 300){
			//---�E�B���h�I�[�u
			crbatCPUThink_SetMagicAtack(pChara,55);
		} else if(rnd < 500 && !pChara->GetTurnAtack()){
			//---�x�[�^�X�R�[��
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,68);
		} else if(rnd < 700){
			//---�T���_�[�{���g
			crbatCPUThink_SetMagicAtack(pChara,67);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 140){
		//---�N����
		if(rnd < 500){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SINRYAKUHEI,255);
		} else {
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SINRYAKUHEI_BOMB,320);
		}
	}

	return crbatCPUThink5(pChara,turn,rnd);
}
