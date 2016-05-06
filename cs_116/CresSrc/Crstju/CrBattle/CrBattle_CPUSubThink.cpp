CRBATCPU_API int crbatCPUThink2(CrBattleCharacter *pChara,int turn,int rnd);
CRBATCPU_API int crbatCPUThink3(CrBattleCharacter *pChara,int turn,int rnd);
CRBATCPU_API int crbatCPUThink4(CrBattleCharacter *pChara,int turn,int rnd);
CRBATCPU_API int crbatCPUThink5(CrBattleCharacter *pChara,int turn,int rnd);

CRBATCPU_API int crbatCPUThink(CrBattleCharacter *pChara,int turn)
{
	int rnd = eiRnd(1000);
	
	//---�����������Ă���΁E�E�E
	if(pChara->GetBtStatus() & BTST_KONRAN){
		pChara->Command.Main = BAT_COMMAND_WAIT;
		return 1;
	}
	if(pChara->GetBtStatus() & BTST_NEMURI){
		//---�Q�Ă���
		pChara->Command.Main = BAT_COMMAND_WAIT;
		return 1;
	}
/*	if(pChara->GetBtStatus() & BTST_MAHI){
		//---���
		pChara->Command.Main = BAT_COMMAND_WAIT;
		return 1;
	}*/

	if(pChara->BattleInfo.Enemy.ActionType == 0){
		//---�ʏ�U��
		crbatCPUThink_SetAtack(pChara);
	} else if(pChara->BattleInfo.Enemy.ActionType == 11){
		//---�t�H�[����
		if(turn < 2){
			//---�����Ƃ܂�
			pChara->Command.Main = BAT_COMMAND_WAIT;
			if(turn == 1){
			}
		} else {
			crbatCPUThink_SetAtack(pChara);
		}

	} else if(pChara->BattleInfo.Enemy.ActionType == 12){
		//---�G�^�[�i����
		pChara->Command.Main = BAT_COMMAND_WEAPON;
		pChara->Command.Range = BAT_TARGET_FRIENDSINGLE;
		pChara->SetTarget(&pBtChara[0]);
	} else if(pChara->BattleInfo.Enemy.ActionType == 14){
		//---�G�^�[�i����
		if(turn < 1){
			pChara->Command.Main = BAT_COMMAND_WEAPON;
			pChara->Command.Range = BAT_TARGET_FRIENDSINGLE;
			pChara->SetTarget(&pBtChara[0]);
		} else {
			pChara->Command.Main = BAT_COMMAND_WAIT;
		}
//		pChara->Command.Main = BAT_COMMAND_WAIT;
	} else if(pChara->BattleInfo.Enemy.ActionType == 20){
		//---����ڂ�S�[�X�g
		if(rnd < 666){
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else {
			crbatCPUThink_SetMagicAtack(pChara,47);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 25){
		//---�u���b�h�C�[�^�[
		if(rnd < 666){
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else {
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KYUKETSU);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 28){
		//---���ʂ܂ǂ�
		if(rnd < 333){
			crbatCPUThink_SetMagicAtack(pChara,41);
		} else if(rnd < 666 && !pChara->GetTurnAtack()){
			//---�G�A�V���[�e�B���O
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,53);
		} else {
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 29){
		//---�ы�
		if(rnd < 500){
			crbatCPUThink_SetMagicAtack(pChara,1);
		} else {
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 30){
		//---�S�[�����p�[�c
		if(rnd < 800){
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else {
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGURU);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 31){
		//---�M���M��
		if(rnd < 333){
			crbatCPUThink_SetMagicAtack(pChara,41);
		} else {
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 33){
		//---���b�g�h�b�O
		if(rnd < 700){
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else {
			//---���݂�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 34){
		//---�ŉ�
		if(rnd < 750){
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else if(!pChara->GetTurnAtack()){
			//---�˕�
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOPPU,7);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 35){
		//---�c�E���[��
		//---�ʏ�U��
		if(rnd < 850){
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else {
			//---���݂�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 36){
		//---�E�B���X���b�O
		if(rnd < 200){
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 566){
			crbatCPUThink_SetMagicAtack(pChara,11);
		} else {
			crbatCPUThink_SetMagicAtack(pChara,14);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 39){
		//---�s�G�[��
		if(rnd < 300){
			//---�G�A�V���[�e�B���O
			crbatCPUThink_SetMagicAtack(pChara,53);
		} else if(rnd < 500){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 750){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_PIERUZAN);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 40){
		//---�W�����A�X
		if(rnd < 200){
			//---�X���[�s���O
			crbatCPUThink_SetMagicAtack(pChara,11);
		} else if(rnd < 500){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 750){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_JURIASGIRI);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 41){
		//---���U�[�h�}��
		if(rnd < 400){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 42){
		//---���X�g���[�t
		if(rnd < 200 && !pChara->GetTurnAtack()){
			//---�G�A�V���[�e�B���O
			crbatCPUThink_SetMagicAtack(pChara,53);
			pChara->AddTurnAtack();
		} else if(rnd < 400){
			//---�A�C�V���O
			crbatCPUThink_SetMagicAtack(pChara,47);
		} else if(rnd < 650){
			//---�T�C�����X
			crbatCPUThink_SetMagicAtack(pChara,15);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 43){
		//---�K�[�h
		if(rnd < 100){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOSSHIN);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 44){
		//---�N���C�V��
		pChara->Command.Main = BAT_COMMAND_WAIT;
/*		if(turn == 2){
			//---�N���C�V������ׂ�
			//---�J�����ړ�
			crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);
			crbatBeginCameraObjectToObject(0,pChara,&pBtChara[0],
			ANGLE(90),
			-1.0f,-1.0f,500);
			//---���X�g�ɕ`���̂�ǉ�
			crbatClearDrawingList();
			crbatAddDrawingListAll();
			crbatDoMovingCamera(500);

			CrMesManager mes;
			mes.CreateNewMessage(-1,-1,32,24,5);
			mes.OpenMessage("DoguriSouth_Iseki.msg",106);
			mes.ReadMessage();
			mes.Draw();
			mes.ReadMessage();
			mes.Draw();
			mes.CloseMessage();
		}*/
	} else if(pChara->BattleInfo.Enemy.ActionType == 48){
		//---�A�T�b�V��
		if(rnd < 150){
			//---�X���[�s���O
			crbatCPUThink_SetMagicAtack(pChara,11);
		} else if(rnd < 450){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 600){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOSSHIN);
		} else if(rnd < 750){
			//---���Q
			crbatCPUThink_SetMagicAtack(pChara,48);
		} else if(rnd < 900){
			//---���Q
			crbatCPUThink_SetMagicAtack(pChara,54);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 45){
		//---��̃o�i�i
		if(crbatCPUGetEnemy() == 1){
			if(rnd < 500){
				//---�R���t���[�W����
				crbatCPUThink_SetMagicAtack(pChara,18);
			} else {
				//---�[���V�[���h
				crbatCPUThink_SetMagicAtack(pChara,30);
			}
		} else if(rnd < 160){
			//---�X���[�s���O
			crbatCPUThink_SetMagicAtack(pChara,11);
		} else if(rnd < 350){
			//---�R���t���[�W����
			crbatCPUThink_SetMagicAtack(pChara,18);
		} else if(rnd < 480){
			//---�T�C�����X
			crbatCPUThink_SetMagicAtack(pChara,15);
		} else if(rnd < 640){
			//---�p���[�u�[�X�g
			crbatCPUThink_SetMagicAtack(pChara,19);
		} else if(rnd < 800){
			//---�[���V�[���h
			crbatCPUThink_SetMagicAtack(pChara,30);
		} else {
			//---���J�o���[
			crbatCPUThink_SetMagicAtack(pChara,18);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 46){
		//---�_�[�N�t�����[
		if(rnd < 650){
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 900){
			//---���݂�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---���C�U�[���C
			crbatCPUThink_SetMagicAtack(pChara,42);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 47){
		//---�T���h�V�F��
		//---�ʏ�U��
		crbatCPUThink_SetAtack(pChara);
	} else if(pChara->BattleInfo.Enemy.ActionType == 49){
		//---�A���[�o�[
		if(rnd < 300){
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 600){
			//---�Ƃ���
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOKASU);
		} else if(rnd < 900){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CHISSOKU_1_10);
		} else if(pChara->GetBattleFlag(0)){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_BUNRETU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 50){
		//---�A�C�X���X�L�[�g
		if(rnd < 400){
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 700){
			//---�z��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KYUKETSU);
		} else if(rnd < 870){
			//---�A�C�V���O
			crbatCPUThink_SetMagicAtack(pChara,47);
		} else if(!pChara->GetTurnAtack()){
			//---�A�C�X�u���X�g
			crbatCPUThink_SetMagicAtack(pChara,48);
			pChara->AddTurnAtack();
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 51){
		//---�X�P���g��
		if(rnd < 750){
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else {
			//---�X���[�s���O
			crbatCPUThink_SetMagicAtack(pChara,11);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 52){
		//---�����E���h�L
		if(rnd < 300){
			//---���݂�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else if(rnd < 600 && !pChara->GetTurnAtack()
			&& pChara->GetPersonalTurn() == 0){
			//---��
			pChara->AddTurnAtack();
			pChara->AddPersonalTurn(2);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,20);
		} else if(rnd < 600){
			//---���݂�
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,10);
		} else {
			//---�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 53){
		//---�G�^�[�i����
		if(rnd < 150){
			//---�X���[�s���O
			crbatCPUThink_SetMagicAtack(pChara,11);
		} else if(rnd < 400 && pChara->GetPersonalTurn() == 0){
			//---���Q
			crbatCPUThink_SetMagicAtack(pChara,54);
			pChara->AddPersonalTurn(2);
		} else if(rnd < 600 && pChara->GetPersonalTurn() == 0){
			//---�y�Q
			crbatCPUThink_SetMagicAtack(pChara,60);
			pChara->AddPersonalTurn(2);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 54){
		//---�G�^�[�i����
		if(rnd < 400){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 600 && pChara->GetPersonalTurn() == 0){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
			pChara->AddPersonalTurn(2);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 55){
		//---�h�u�E�j
		if(rnd < 500){
			//---��]�A�^�b�N
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAITENATACK);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 56){
		//---�n���V���W
		if(rnd < 350){
			//---���݂�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else if(rnd < 600){
			//---�E�q
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HOUSHI,6);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 57){
		//---�����L
		if(rnd < 500){
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 750){
			//---���C�U�[���C
			crbatCPUThink_SetMagicAtack(pChara,42);
		} else {
			//---���C�e�B���O�l�b�g
			crbatCPUThink_SetMagicAtack(pChara,66);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 58){
		//---�J�C����
		if(rnd < 250){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SEICHOU);
		} else if(rnd < 500 && pChara->GetLP() != pChara->GetMaxLP()){
			//---������
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KOUGOUSEI);
		} else if(rnd < 500){
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 750){
			//---�v���l�b�g
			crbatCPUThink_SetMagicAtack(pChara,60);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 59){
		//---���b�h�w��
		if(rnd < 300){
			//---�z��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KYUKETSU);
		} else if(rnd < 600){
			//---���݂�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 60){
		//---�t�F�C�N�~�X�g
		if(rnd < 200){
			//---�A�C�V���O
			crbatCPUThink_SetMagicAtack(pChara,47);
		} else if(rnd < 400){
			//---�A�V�b�h�~�X�g
			crbatCPUThink_SetMagicAtack(pChara,48);
		} else if(rnd < 550){
			//---�p�����C�Y
			crbatCPUThink_SetMagicAtack(pChara,31);
		} else if(rnd < 700){
			//---�R���t���[�W����
			crbatCPUThink_SetMagicAtack(pChara,18);
		} else if(rnd < 800){
			//---���J�o���[�Q
			crbatCPUThink_SetMagicAtack(pChara,3);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else {
		crbatCPUThink_SetAtack(pChara);
	}

	return crbatCPUThink2(pChara,turn,rnd);
}

