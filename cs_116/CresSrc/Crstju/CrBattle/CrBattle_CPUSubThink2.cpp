
CRBATCPU_API int crbatCPUThink2(CrBattleCharacter *pChara,int turn,int rnd)
{
	if(pChara->BattleInfo.Enemy.ActionType == 61){
		//---�����_�����O�\�E��
		if(rnd < 150){
			//---�a�肩����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 250){
			//---�������a�����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else if(rnd < 300){
			//---�ˌ�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOTUGEKI);
		} else if(rnd < 550){
			//---�Ȃ��|��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGITAOSU);
		} else if(rnd < 750){
			//---�A�C�X�k�Q
			crbatCPUThink_SetMagicAtack(pChara,48);
			pChara->Command.Sub[CRBAT_SUBTARGET] = 1;
		} else if(rnd < 850){
			//---�C���t���G���X
			crbatCPUThink_SetMagicAtack(pChara,20);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 62){
		//---�n�C���U�[�h
		if(rnd < 333){
			//---�a�肩����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 500){
			//---�������a�����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 63){
		//---�׋��k
		if(rnd < 300 && !pChara->GetTurnAtack()){
			//---�X�g���[���N���E
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,54);
		} else if(rnd < 400){
			//---�G�A�V���[�e�B���O
			crbatCPUThink_SetMagicAtack(pChara,53);
		} else if(rnd < 600 && pChara->GetTurnAtack() <= 1){
			//---���C�U�[���C
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,42);
		} else if(rnd < 750){
			//---�X���[�s���O
			crbatCPUThink_SetMagicAtack(pChara,11);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 64){
		//---�Ԍ͂��
		if(rnd < 200){
			//---�[���V�[���h
			crbatCPUThink_SetMagicAtack(pChara,30);
		} else if(rnd < 450){
			//---�f�B�X�g�[�V����
			crbatCPUThink_SetMagicAtack(pChara,12);
		} else if(rnd < 650){
			//---�����x���Q
			crbatCPUThink_SetMagicAtack(pChara,66);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 65){
		//---�����c����
		if(rnd < 400){
			//---�Ƃ���
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOKASU);
		} else if(rnd < 600){
			//---�p���[�u�[�X�g
			crbatCPUThink_SetMagicAtack(pChara,19);
			pChara->Command.Target = (ei_u32)pChara;
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 66){
		//---�_�u���e�C��
		if(rnd < 333 && !pChara->GetTurnAtack() && !pChara->GetPersonalTurn()){
			//---����
			pChara->AddTurnAtack();
			pChara->AddPersonalTurn(3);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_FUBUKI,30	);
		} else if(rnd < 550){
			//---���݂�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 67){
		//---���[�t�B�A
		if(pChara->GetMC() < 70){
			//---�l�b�����Ȃ��Ȃ�����ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else if(pChara->GetLP() < 170 && pChara->GetBattleFlag(1) == 0){
			//---�k�o�����������
			crbatCPUThink_SetMagicAtack(pChara,6);
			pChara->SetBattleFlag(1,pChara->GetBattleFlag(1) + 1);
		} else if(turn == 0){
			//---�^�[���ŏ�
			//---�G�N�X�e���h
			crbatCPUThink_SetMagicAtack(pChara,22);
		} else if(rnd < 250 && pChara->GetBattleFlag(0) == 0
			&& turn != 1){
			//---�T�C�����X
			pChara->SetBattleFlag(0,1);
			crbatCPUThink_SetMagicAtack(pChara,15,-1,0,&pBtChara[0]);
		} else if(rnd < 500 || turn == 1){
			//---�E�B���h�I�[��
			if(pChara->GetBattleFlag(2) == 0){
				crbatCPUThink_SetMagicAtack(pChara,55);
//				pChara->SetBattleFlag(2,2);
			} else {
				//---�ʏ�U��
				crbatCPUThink_SetAtack(pChara);
			}
		} else if(rnd < 700){
			//---�T���_�[�{���g
			if(pChara->GetBattleFlag(2) == 0){
				crbatCPUThink_SetMagicAtack(pChara,67);
//				pChara->SetBattleFlag(2,2);
			} else {
				crbatCPUThink_SetMagicAtack(pChara,66);
			}
		} else if(rnd < 900){
			//---�Z���t���[�Y
			if(pChara->GetBattleFlag(2) == 0){
				crbatCPUThink_SetMagicAtack(pChara,49);
//				pChara->SetBattleFlag(2,2);
			} else {
				crbatCPUThink_SetMagicAtack(pChara,47 + eiRnd(2));
			}
		} else if(rnd < 975){
			//---�f�X�t�H�[�X
			if(pChara->GetBattleFlag(7) == 0){
				crbatCPUThink_SetMagicAtack(pChara,21);
				pChara->SetBattleFlag(7,1);
			} else {
				//---�E�B���h�I�[��
				if(pChara->GetBattleFlag(2) == 0){
					crbatCPUThink_SetMagicAtack(pChara,55);
//					pChara->SetBattleFlag(2,2);
				} else {
					//---�ʏ�U��
					crbatCPUThink_SetAtack(pChara);
				}
			}
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}

		if(pChara->GetBattleFlag(2) > 0){
			pChara->SetBattleFlag(2,pChara->GetBattleFlag(2) - 1);
		}
//---------------�Q��
	} else if(pChara->BattleInfo.Enemy.ActionType == 68){
		//---���i���R
		if(rnd < 350){
			//---���݂�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else if(rnd < 600){
			//---�E�q
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HOUSHI,10);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 69){
		//---�t���[�e�B���O�A�C
		if(rnd < 200){
			//---�_�[�N�~�X�g
			crbatCPUThink_SetMagicAtack(pChara,14);
		} else if(rnd < 400){
			//---�A�C�X�k���Q
			crbatCPUThink_SetMagicAtack(pChara,48);
		} else if(rnd < 700 && !pChara->GetTurnAtack()){
			//---�A�C�X�k���R
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,49);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 70){
		//---�f�V�x��
		if(rnd < 350){
			//---�z��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KYUKETSU);
		} else if(rnd < 500){
			//---�Ռ��g
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SHOGEKIHA,6);
		} else if(rnd < 700){
			//---�����g
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CHOUONPA,6);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 72){
		//---�X�g�[���u���C�J�[
		if(rnd < 350){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGURU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 74){
		//---�f�X���b�Z���W���[
		if(rnd < 300){
			//---�f�X�t�H�[�X
			crbatCPUThink_SetMagicAtack(pChara,21);
		} else if(rnd < 500){
			//---�p�����C�Y
			crbatCPUThink_SetMagicAtack(pChara,31);
		} else if(rnd < 750){
			//---�t���A�E�F�C��
			crbatCPUThink_SetMagicAtack(pChara,43);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 75){
		//---���}�E�j
		if(rnd < 550){
			//---��]�A�^�b�N
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAITENATACK);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 76){
		//---�s�J�s�J
		if(rnd < 250){
			//---�T���_�[�{���g
			crbatCPUThink_SetMagicAtack(pChara,66);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 77){
		//---�[�Ă��o�i�i
		if(rnd < 200){
			//---���C�t�V�����[
			crbatCPUThink_SetMagicAtack(pChara,5);
		} else if(rnd < 350){
			//---�p���[�u�[�X�g
			crbatCPUThink_SetMagicAtack(pChara,19);
		} else if(rnd < 500){
			//---�V�[���h�u���C�N
			crbatCPUThink_SetMagicAtack(pChara,30);
		} else if(rnd < 700){
			//---�R���t���[�W����
			crbatCPUThink_SetMagicAtack(pChara,18);
		} else if(rnd < 900){
			//---�X���[�s���O
			crbatCPUThink_SetMagicAtack(pChara,11);
		} else {
			//---�_�[�N�~�X�g
			crbatCPUThink_SetMagicAtack(pChara,14);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 78){
		//---�v���[�����[��
		if(rnd < 250){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SUNAARASHI,50);
		} else if(rnd < 400){
			//---���݂�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else if(rnd < 500){
			//---�����P�^�Q
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CHISSOKU_1_2);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 80){
		//---�X�̐�
		if(rnd < 200){
			//---�f�B�X�g�[�V����
			crbatCPUThink_SetMagicAtack(pChara,12);
		} else if(rnd < 400){
			//---�A�V�b�h�~�X�g
			crbatCPUThink_SetMagicAtack(pChara,48);
		} else if(rnd < 550){
			//---�p�����C�Y
			crbatCPUThink_SetMagicAtack(pChara,31);
		} else if(rnd < 750){
			//---���J�o���[�Q
			crbatCPUThink_SetMagicAtack(pChara,3);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 81){
		//---���H��
			crbatCPUThink_SetAtack(pChara);
	} else if(pChara->BattleInfo.Enemy.ActionType == 82){
		//---�N���[�o�[
		if(rnd < 250){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SEICHOU);
		} else if(rnd < 500 && pChara->GetLP() != pChara->GetMaxLP()){
			//---������
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KOUGOUSEI);
		} else if(rnd < 500){
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 800 && pChara->GetTurnAtack() <= 1){
			//---�O���X�V�[�h
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,61);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	}

	return crbatCPUThink3(pChara,turn,rnd);
}
