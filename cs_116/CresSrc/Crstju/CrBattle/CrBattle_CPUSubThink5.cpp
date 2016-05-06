CRBATCPU_API int crbatCPUThink5(CrBattleCharacter *pChara,int turn,int rnd)
{
	//----------------�R��
	if(pChara->BattleInfo.Enemy.ActionType == 142){
		//---�փ��r�[�X�g
		if(rnd < 250 && !pChara->GetTurnAtack()){
			//---���ቊ
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_FUBUKI,120);
		} else if(rnd < 600){
			//---���݂�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 143){
		//---�e�J�e�J
		if(rnd < 50 && !pChara->GetTurnAtack()){
			//---�x�[�^�X�R�[��
			crbatCPUThink_SetMagicAtack(pChara,68);
		} else if(rnd < 400){
			//---�T���_�[�{���g
			crbatCPUThink_SetMagicAtack(pChara,67);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 144){
		//---������
		if(rnd < 250){
			//---�X���[�s���O
			crbatCPUThink_SetMagicAtack(pChara,11,-1,0,NULL,1);
		} else if(rnd < 500){
			//---�ԕ�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAFUN,40);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 145){
		//---�O���E���h�L���O
		if(rnd < 500 && pChara->GetBattleFlag(0) == 0
			&& pChara->GetBattleFlag(1) == 0 && pChara->GetLP() >= 400){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_RYUSA,10);
			pChara->SetBattleFlag(0,1);
		} else if(pChara->GetBattleFlag(0)){
			//---�ߐH
			pChara->SetBattleFlag(0,0);
			pChara->SetBattleFlag(1,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HOSHOKU);
		} else if(rnd < 333){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SUNAARASHI,160);
		} else if(rnd < 680){
			//---���݂�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 146){
		//---�f�X�N���E�h
		if(rnd < 200){
			//---�p�����C�Y
			crbatCPUThink_SetMagicAtack(pChara,31);
		} else if(rnd < 400){
			//---�X���[�s���O
			crbatCPUThink_SetMagicAtack(pChara,11);
		} else if(rnd < 600){
			//---�_�[�N�~�X�g
			crbatCPUThink_SetMagicAtack(pChara,14);
		} else if(rnd < 800){
			//---�T�C�����X
			crbatCPUThink_SetMagicAtack(pChara,15);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 147){
		if(pChara->GetLP() < 80
			&& pChara->GetBattleFlag(0) == 0){
			//---�k�o�`�F���W
			pChara->SetBattleFlag(0,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_LPCHANGE,1000);
		} else if(rnd < 300 && !pChara->GetTurnAtack()){
			//---����
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SUNAARASHI,100);
		} else if(rnd < 300){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SUNAARASHI,50);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 148){
		//---�w���Q�[�g
		if(rnd < 250 && !pChara->GetTurnAtack()){
			//---�f�X�t�H�[�X
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,21);
		} else if(rnd < 250){
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 500 && !pChara->GetTurnAtack()){
			//---�A�N�A�\�[�h
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,50);
		} else if(rnd < 600){
			//---�Z���t���[�Y
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,49);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 149){
		//---�X�N���b�v�A�[�}�[
		if(rnd < 250){
			//---�a�肩����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 450){
			//---�͂�����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 150){
		//---�R�̐_
		if(pChara->GetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE)
		 && !(pBtChara[
			pChara->GetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE_TAISHO)
			].GetBtStatus() & BTST_ITAMIWAKE)){
			//---�ɂݕ����Ώۂ��A�ɂݕ�����ԂłȂ��Ȃ�����
			pChara->SetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE,0);
			pChara->SetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE_TAISHO,0);
			pChara->SetBattleFlag(1,0);
		}

		if((rnd < 120 || turn == 3)
			&& pChara->GetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE) == 0){
			pChara->SetBattleFlag(1,0);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_ITAMIWAKE);
/*		} else if(pChara->GetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE) == 1
			&& rnd < 600 + (pChara->GetBattleFlag(1) * 200)){
			pChara->SetBattleFlag(1,pChara->GetBattleFlag(1) + 1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_ITAMIWAKE_JIZOKU);
		} else if(pChara->GetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE) == 1){
			pChara->SetBattleFlag(1,0);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_ITAMIWAKE_KAIJO);*/
		} else 

		if(rnd < 220
			&& crbatCPUGetEnemy() == 1
			&& !(pChara->GetBtStatus() & BTST_CHINMOKU)){
			//---�f�X�t�H�[�X
			crbatCPUThink_SetMagicAtack(pChara,21);
		} else if(rnd < 250){
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 480 && !pChara->GetPersonalTurn()
			&& !pChara->GetTurnAtack()
			&& !(pChara->GetBtStatus() & BTST_CHINMOKU)){
			//---�A�[�X�N�E�F�C�N
			pChara->AddTurnAtack();
			pChara->AddPersonalTurn(4);
			crbatCPUThink_SetMagicAtack(pChara,63);
		} else if(rnd < 500 && pChara->GetPersonalTurn() <= 2
			&& !(pChara->GetBtStatus() & BTST_CHINMOKU)){
			//---�_�C���u���X
			crbatCPUThink_SetMagicAtack(pChara,62);

		} else if(rnd < 500
			&& (pChara->GetBtStatus() & BTST_CHINMOKU)){
			//---���فA�������a�����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else if(rnd < 630 && pChara->GetPersonalTurn() <= 2
			&& !pChara->GetTurnAtack()){
			//---�ғł̑�
			pChara->AddTurnAtack();
			pChara->AddPersonalTurn(2);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_MODOKUNOIKI,100);
		} else if(rnd < 730
			&& !(pChara->GetBtStatus() & BTST_CHINMOKU)){
			//---�C���o���f�B�e�B
			crbatCPUThink_SetMagicAtack(pChara,25);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 151){
		//---���b�h�_���f�B
		if(rnd < 333){
			//---�_���f�B�X�p�[�N
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_DANDYSPARK,102);
		} else if(rnd < 600){
			//---�_���f�B�X�v���b�V���[
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_DANDYSPRASHER);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 152){
		//---����
		if(rnd < 333){
			//---���J�o���C�V����
			crbatCPUThink_SetMagicAtack(pChara,6);
		} else if(rnd < 500){
			//---�X���[�s���O
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,11,-1,0,NULL,1);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 153){
		//---�E�j�}����
		if(rnd < 600){
			//---��]�A�^�b�N
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAITENATACK);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 154){
		//---�\�[�h�L���[
		if(rnd < 100){
			//---�k
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KARA);
		} else if(rnd < 350){
			//---�n����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOKASU);
		} else if(rnd < 600){
			//---�H�ׂ�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TABERU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 155){
		//---�N���C�V��
		if(turn == 4 || turn == 6){
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else if(turn == 7){
			//---�X�[�p�[�Z��
			pChara->Command.Hit = 1;
			crbatCPUThink_SetMagicAtack(pChara,57);
		} else {
			pChara->Command.Main = BAT_COMMAND_WAIT;
		}

	} else if(pChara->BattleInfo.Enemy.ActionType == 156){
		//---�A�C�`���[
		if(rnd < 200){
			//---���邮��ڋ�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_GURUGURUMEDAMA);
		} else if(rnd < 500){
			//---�A�C�r�[��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_EYEBEAM,100);
		} else if(rnd < 600){
			//---�R���t���[�W����
			crbatCPUThink_SetMagicAtack(pChara,18,-1,0,NULL,1);
		} else if(rnd < 900){
			//---�Z���t���[�Y
			crbatCPUThink_SetMagicAtack(pChara,49);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 157){
		//---�E�B���O�i�C�g
		if(rnd < 250){
			//---���肩����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 500){
			//---������
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 158){
		//---�g���l�[�h
		if(rnd < 180 && !pChara->GetTurnAtack() && !pChara->GetPersonalTurn()){
			//---�_�E���o�[�X�g
			pChara->AddPersonalTurn(3);
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,56);
		} else if(rnd < 360){
			//---�˕�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOPPU,60);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 159){
		//---�]�E�����V
		if(rnd < 300){
			//---�Ƃ���
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOKASU);
		} else if(rnd < 500){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CHISSOKU_1_2);
		} else if(!pChara->GetBattleFlag(0) && rnd < 550){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_BUNRETU);
		} else if(rnd < 700){
			//---�_���J
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SANSEIU,50);
		} else if(rnd < 800){
			//---�Đ�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SAISEI);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 160){
		//---�L���[�{��
		if(pChara->GetBattleFlag(0)){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_JIBAKU2,0,pChara);
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
	} else if(pChara->BattleInfo.Enemy.ActionType == 161){
		//---���r�[�h���S��
		pChara->SetBattleFlag(0,0);
		pChara->SetBattleFlag(2,0);

		if(pChara->GetBattleFlag(1)
			&& !(pChara->GetBtStatus() & BTST_CHINMOKU)){
			//---�J�I�X���[�h�E���@
			pChara->SetBattleFlag(1,0);
			pChara->SetBattleFlag(2,1);
			pChara->AddPersonalTurn(4);
			crbatCPUThink_SetMagicAtack(pChara,51);
		} else if(rnd < 220 + (
				(pChara->GetBtStatus() & BTST_CHINMOKU) ? 200 : 0
			)
			&& !pChara->GetPersonalTurn()){
			//---�R���{��
			pChara->AddPersonalTurn(4);
			pChara->SetBattleFlag(0,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,110);
//			crbatCPUThink_SetMagicAtack(pChara,56);
		} else if(rnd < 330){
			//---��
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,95);
		} else if(rnd < 680 && !pChara->GetPersonalTurn()
			&& !(pChara->GetBtStatus() & BTST_CHINMOKU)){
			//---�J�I�X���[�h
			pChara->SetBattleFlag(1,1);
			crbatCPUThink_SetMagicAtack(pChara,27);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}	
	} else if(pChara->BattleInfo.Enemy.ActionType == 184){
		//---���r�[�h���S��
		pChara->SetBattleFlag(0,0);

		if(pBtChara[BATTLECHARA_STARTENEMY].GetBattleFlag(1)
			|| pBtChara[BATTLECHARA_STARTENEMY].GetBattleFlag(2)){
			//---�J�I�X���[�h��������ҋ@
			pChara->Command.Main = BAT_COMMAND_WAIT;
		} else if(pBtChara[BATTLECHARA_STARTENEMY].GetBattleFlag(0)){
			//---�R���{����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_FUBUKI,110);
		} else if(rnd < 350
//			&& !(pBtChara[BATTLECHARA_STARTENEMY].Command.Main == BAT_COMMAND_ENEMYABILITY
//				&& pBtChara[BATTLECHARA_STARTENEMY].Command.Sub[0] == BAT_ECOM_HONO)
			&& !pChara->GetTurnAtack()){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_FUBUKI,80);
		} else if(rnd < 480 && !pBtChara[BATTLECHARA_STARTENEMY].GetBattleFlag(1)
			&& !(pChara->GetBtStatus() & BTST_CHINMOKU)){
			int flag  = pChara->GetBattleFlag(1);

			switch(flag){
			case 0:
				//---�A�N�Z�����C�V����
				crbatCPUThink_SetMagicAtack(pChara,16,-1,0,&pBtChara[BATTLECHARA_STARTENEMY]);
				break;
			case 1:
				//---�\�E���Z���X
				crbatCPUThink_SetMagicAtack(pChara,26,-1,0,&pBtChara[BATTLECHARA_STARTENEMY]);
				break;
			case 2:
				//---�t�H�[�X�V�[���h
				crbatCPUThink_SetMagicAtack(pChara,17,-1,0,&pBtChara[BATTLECHARA_STARTENEMY]);
				break;
			case 3:
				//---�v���e�N�V����
				crbatCPUThink_SetMagicAtack(pChara,13,-1,0,&pBtChara[BATTLECHARA_STARTENEMY]);
				break;
			case 4:
				//---�G�N�X�e���h
				crbatCPUThink_SetMagicAtack(pChara,22,-1,0,&pBtChara[BATTLECHARA_STARTENEMY]);
				break;
			}
			if(++flag >= 5)
				flag = 0;
			pChara->SetBattleFlag(1,flag);
		} else if(rnd < 750){
			//---�E�F�C�g
			pChara->Command.Main = BAT_COMMAND_WAIT;
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}	
	} else if(pChara->BattleInfo.Enemy.ActionType == 162){
		//---����
		if(rnd < 250 && pChara->GetTurnAtack() <= 1){
			//---�����a��
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_ONSOKU);
		} else if(rnd < 333){
			//---�a�肩����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 666){
			//---�����E�W�Q�O
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_820);
		} else if(rnd < 800 && pChara->GetLP() < 200){
			//---�Đ�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SAISEI);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 163){
		//---�S�[�����v���[�X�g
		if(crbatCPUGetEnemy() == 1){
			if(rnd < 500){
				//---�Z���t���[�Y
				crbatCPUThink_SetMagicAtack(pChara,49);
			} else {
				crbatCPUThink_SetAtack(pChara);
			}
		} else if(pChara->GetBtStatus() & BTST_CHINMOKU){
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 150){
			//---���C�t�E�B���h
			crbatCPUThink_SetMagicAtack(pChara,7);
		} else if(rnd < 300){
			//---�T�C�����X
			crbatCPUThink_SetMagicAtack(pChara,15,-1,0,NULL,1);
		} else if(rnd < 400){
			//---�_�[�N�~�X�g
			crbatCPUThink_SetMagicAtack(pChara,14,-1,0,NULL,1);
		} else if(rnd < 500){
			//---�p�����C�Y
			crbatCPUThink_SetMagicAtack(pChara,31);
		} else if(rnd < 600){
			//---�G�N�X�e���h
			crbatCPUThink_SetMagicAtack(pChara,22);
		} else if(rnd < 800 && pChara->GetTurnAtack()){
			//---�A�N�A�\�[�h
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,50);
		} else if(rnd < 800){
			//---�Z���t���[�Y
			crbatCPUThink_SetMagicAtack(pChara,49);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 164){
		//---�y���\�i�h�[��
		if(pChara->GetBtStatus() & BTST_CHINMOKU){
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 300 && !pChara->GetTurnAtack()){
			//---�G�N�X�v���[�W����
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,44);
		} else if(rnd < 300){
			//---�t���A�E�F�C��
			crbatCPUThink_SetMagicAtack(pChara,43);
		} else if(rnd < 600 && !pChara->GetTurnAtack()){
			//---�_�E���o�[�X�g
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,56);
		} else if(rnd < 600){
			//---�E�B���h�I�[�u
			crbatCPUThink_SetMagicAtack(pChara,55);
		} else if(rnd < 700){
			//---�f�X�t�H�[�X
			crbatCPUThink_SetMagicAtack(pChara,21);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 165){
		//---�_�[�N�s���[
		if(rnd < 300 && !pChara->GetTurnAtack()){
			//---�x�[�^�X�R�[��
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,68);
		} else if(rnd < 300){
			//---�T���_�[�{���g
			crbatCPUThink_SetMagicAtack(pChara,67);
		} else if(rnd < 700){
			//---�l�b����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_MCBUNKAI,25);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 166){
		//---�ō��b
		if(rnd < 300){
			//---���݂�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	}

	return crbatCPUThink6(pChara,turn,rnd);
}
