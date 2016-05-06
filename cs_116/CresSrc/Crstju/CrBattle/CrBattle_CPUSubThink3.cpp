
CRBATCPU_API int crbatCPUThink3(CrBattleCharacter *pChara,int turn,int rnd)
{
	if(pChara->BattleInfo.Enemy.ActionType == 83){
		//---�\�[�h�E���t
		if(rnd < 333){
			//---���݂�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 84){
		//---�~�X�e�B�W�F���g��
		if(rnd < 333){
			//---�~�X�e�B�r�[��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_MISTYBEAM,60);
		} else if(rnd < 600){
			//---�W�F���g���t���b�V��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_JENTLEFLASH);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 85){
		//---���r���O�A�[�}�[
		if(rnd < 333){
			//---�a�肩����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 600){
			//---������
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else if(rnd < 700){
			//---�Ȃ��|��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGITAOSU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 86){
		//---���b�h�{�[��
		if(rnd < 250 && !pChara->GetTurnAtack()
			&& pChara->GetPersonalTurn() == 0){
			//---�˕�
			pChara->AddTurnAtack();
			pChara->AddPersonalTurn(3);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SUNAARASHI,60);
		} else if(rnd < 250
			&& pChara->GetPersonalTurn() <= 1){
			pChara->AddPersonalTurn(1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SUNAARASHI,30);
		} else if(rnd < 450){
			//---�X���[�s���O�i�S�j
			crbatCPUThink_SetMagicAtack(pChara,11,-1,0,NULL,1);
		} else if(pChara->GetLP() < 50
			&& pChara->GetBattleFlag(0) == 0){
			//---�k�o�`�F���W
			pChara->SetBattleFlag(0,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_LPCHANGE,1000);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 87){
		//---���C���Y�K�[�f�B�A
		//---�΂�΂炾������_�E���o�[�X�g
		if(pChara->GetBattleFlag(2)){
			rnd = (rnd * 2) / 3;
		}
		pChara->SetBattleFlag(2,0);

		if(pChara->GetBtStatus() & BTST_CHINMOKU){
			//---���ق�������ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else if(pChara->GetMC() < 100){
			//---�l�b���Ȃ��Ȃ�����ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else if(crbatCPU_PlayerIsBaraBara(pChara,2)
			&& rnd < 400){
			//---�_�E���o�[�X�g
			crbatCPUThink_SetMagicAtack(pChara,56);
		} else if(rnd < 400 && !pChara->GetPersonalTurn()){
			//---�G�N�X�v���[�W����
			pChara->AddPersonalTurn(2);
			crbatCPUThink_SetMagicAtack(pChara,44);
		} else if(rnd < 250){
			//---���C�U�[���C
			crbatCPUThink_SetMagicAtack(pChara,42);
		} else if(rnd < 500 && !pChara->GetPersonalTurn()){
			//---�x�[�^�X�R�[��
			pChara->AddPersonalTurn(2);
			crbatCPUThink_SetMagicAtack(pChara,68);
		} else if(rnd < 650){
			//---�t���A�E�F�C��
			crbatCPUThink_SetMagicAtack(pChara,43);
		} else if(rnd < 800){
			//---�C���t���G���X
			crbatCPUThink_SetMagicAtack(pChara,20,-1,0,NULL,1);
			pChara->SetBattleFlag(2,1);
		} else if(rnd < 900){
			//---�T�C�����X
			crbatCPUThink_SetMagicAtack(pChara,15,-1,0,NULL,1);
			pChara->SetBattleFlag(2,1);
		} else if(rnd < 1000){
			//---�R���t���[�W����
			crbatCPUThink_SetMagicAtack(pChara,18);
			pChara->SetBattleFlag(2,1);
		} else if(!pChara->GetBattleFlag(0)){
			//---�v���e�N�V����
			pChara->SetBattleFlag(0,1);
			pChara->SetBattleFlag(2,1);
			crbatCPUThink_SetMagicAtack(pChara,13);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 88){
		//---�v�`�T�C�N����
		if(rnd < 200){
			//---�˕�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOPPU,30);
		} else if(rnd < 500 && !pChara->GetTurnAtack()){
			//---�E�B���h�I�[�u
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,55);
		} else if(rnd < 500){
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 700){
			//---�Ռ��g
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SHOGEKIHA);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
//		crbatCPUThink_SetMagicAtack(pChara,23);
	} else if(pChara->BattleInfo.Enemy.ActionType == 89){
		//---����
		if(rnd < 333){
			//---���J�o���[�Q
			crbatCPUThink_SetMagicAtack(pChara,3);
		} else if(rnd < 500){
			//---�X���[�s���O
			crbatCPUThink_SetMagicAtack(pChara,11);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 90){
		//---�_�[�N�A�C
		if(rnd < 333){
			//---�A�C�r�[��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_EYEBEAM,50);
		} else if(rnd < 666){
			//---���邮��ڋ�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_GURUGURUMEDAMA,50);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 91){
		//---����
		CrBattleCharacter *pnear = crbatCPU_PlayerIsSekkin(pChara,0);

		if(pnear != NULL && rnd < 500){
			//--�߂Â���������
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SEKKINATACK,0,pnear);
		} else if(pnear != NULL && rnd < 700){
			//---�ړ�
			crbatCPUThink_SetDefense(pChara,3);
		} else if(rnd < 333){
			//---�a�肩����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 530 && !pChara->GetPersonalTurn()){
			//---�~���a
			pChara->AddPersonalTurn(3);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_ENGETUZAN);
		} else if(rnd < 650){
			//---�_�[�N�~�X�g
			crbatCPUThink_SetMagicAtack(pChara,14);
		} else if(rnd < 800){
			//---�[���V�[���h�i�͈́j
			crbatCPUThink_SetMagicAtack(pChara,30,-1,0,NULL,1);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 92){
		//---�O���X�G�X�J���S
		if(rnd < 150){
			//---�k
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KARA);
		} else if(rnd < 400){
			//---�n����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOKASU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 93){
		//---�d�p�m
		if(rnd < 333 && !pChara->GetTurnAtack()){
			//---�O���X�V�[�h
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,61,-1,0,NULL,1);
		} else if(rnd < 333){
			//---�X�g���[���N���E
			crbatCPUThink_SetMagicAtack(pChara,54);
		} else if(rnd < 500){
			//---�f�X�t�H�[�X
			crbatCPUThink_SetMagicAtack(pChara,21);
		} else if(rnd < 750){
			//---�R���t���[�W����
			crbatCPUThink_SetMagicAtack(pChara,18);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 94){
		//---�a�n��
		if(rnd < 750 && pChara->GetBattleFlag(0) == 0
			&& pChara->GetBattleFlag(1) == 0){
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
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SUNAARASHI,60);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 95){
		//---�u���[���U�[�h
		if(rnd < 150){
			//---������
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else if(rnd < 350){
			//---�a�肩����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 96){
		//---�|�C�Y���K�X
		if(rnd < 333 && !pChara->GetTurnAtack()){
			//---�ۂ�����Ԃꂷ
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_POISON,30);
		} else if(rnd < 333){
			//---�X���[�s���O
			crbatCPUThink_SetMagicAtack(pChara,11);
		} else if(rnd < 500){
			//---�_�[�N�~�X�g
			crbatCPUThink_SetMagicAtack(pChara,11);
		} else if(rnd < 650){
			//---�v���e�N�V����
			crbatCPUThink_SetMagicAtack(pChara,13);
		} else if(rnd < 800){
			//---�t�H�[�X�V�[���h
			crbatCPUThink_SetMagicAtack(pChara,17);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 97){
		//---�}�C�����[�o
		if(rnd < 300){
			//---�Ƃ���
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOKASU);
		} else if(rnd < 500){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CHISSOKU_1_5);
		} else if(!pChara->GetBattleFlag(0) && rnd < 550){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_BUNRETU);
		} else if(rnd < 700){
			//---�_
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SAN);
		} else if(rnd < 800){
			//---�Đ�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SAISEI);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 98){
		//---�[�r�A�����E
		if(rnd < 250){
			//---���݂�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else if(rnd < 566 && !pChara->GetTurnAtack()
			&& pChara->GetPersonalTurn() == 0){
			//---���
			pChara->AddTurnAtack();
			pChara->AddPersonalTurn(2);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_IKADUCHI,70);
		} else if(rnd < 566){
			//---���
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_IKADUCHI,30);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 99){
		//---�N���C�V���A�����錾
		if(turn < 3){
			pChara->Command.Main = BAT_COMMAND_WAIT;
		} else {
			//---�X�[�p�[�Z��
			pChara->Command.Hit = 1;
			crbatCPUThink_SetMagicAtack(pChara,57);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 100){
		//---�Ή���
		if(pChara->GetBattleFlag(0) && pChara->Command.Main != BAT_COMMAND_WAIT){
			//---���C�W���O�T��
			if(pChara->GetBtStatus() & BTST_CHINMOKU){
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO2,100);
			} else {
				crbatCPUThink_SetMagicAtack(pChara,45,-1,0,NULL,1);
			}
			pChara->SetBattleFlag(0,0);
			pChara->SetBattleFlag(1,1);
			pChara->AddPersonalTurn(5);
		} else if(pChara->GetBattleFlag(1)){
			//---���C�W���O�T������
			if(pChara->GetBtStatus() & BTST_CHINMOKU){
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,30);
			} else {
				//---���@���g����
				crbatCPUThink_SetMagicAtack(pChara,3);
			}
			pChara->SetBattleFlag(1,0);
		} else if((turn + 2) && !((turn + 2) % 6)){
			//---���߂�
			pChara->SetBattleFlag(0,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TAMERU);
		} else if(rnd < 333 && !pChara->GetPersonalTurn()){
			//---��
			pChara->AddPersonalTurn(3);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,90);
		} else if(rnd < 400){
			//---��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,45);
		} else if(rnd < 650 && (pChara->GetBtStatus() & BTST_MAHI)){
			//---��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,45);
		} else if(rnd < 650){
			//---���݂�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else if(rnd < 800 && 
			((pChara->GetBtStatus() & BTST_MAHI) || (pChara->GetBtStatus() & BTST_CHINMOKU))){
			//---��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,65);
		} else if(rnd < 800){
			if(crbatCPU_UseInvalidity(pChara) > eiRnd(3)){
				//---�C���o���f�B�e�B
				crbatCPUThink_SetMagicAtack(pChara,25);
			} else {
				//---�ʏ�U��
				crbatCPUThink_SetAtack(pChara);
			}
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 101){
		//---�N���V�W�~
		if(rnd < 250){
			//---���S�C
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_MIZUDEPPOU,70);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 102){
		//---�������\
		if(rnd < 250 && !pChara->GetTurnAtack()){
			//---����
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_FUBUKI,60);
		} else if(rnd < 250){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_FUBUKI,25);
		} else if(rnd < 400){
			//---����̕�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NEMURINOKONA,15);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 103){
		//---�N���o
		if(rnd < 350){
			//---���݂�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 104){
		//---�G�^�[�i�����i��m�j
		if(rnd < 333){
			//---�a�肩����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 600){
			//---������
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 105){
		//---�G�^�[�i�����i���@�g���j
		if(rnd < 200){
			//---�p�����C�Y
			crbatCPUThink_SetMagicAtack(pChara,11);//,-1,0,NULL,1);
		} else if(rnd < 350 && !pChara->GetTurnAtack()){
			//---�E�B���h�I�[��
			pChara->AddTurnAtack();
			if(!pChara->GetPersonalTurn()){
				pChara->AddPersonalTurn(2);
				crbatCPUThink_SetMagicAtack(pChara,55);
			} else {
				crbatCPUThink_SetMagicAtack(pChara,54);
			}
		} else if(rnd < 500){
			//---�t���A�E�F�C��
			crbatCPUThink_SetMagicAtack(pChara,43);
		} else if(rnd < 750){
			//---�X�g���[���N���E
			crbatCPUThink_SetMagicAtack(pChara,54);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 106){
		//---�G�^�[�i�����i����j
		if(rnd < 150){
			//---�X���[�v�u���X
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,20);
		} else if(rnd < 300){
			//---�T�C�����g�u���X
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SILENTBREATH,20);
		} else if(rnd < 500 && !pChara->GetTurnAtack()){
			//---�p���[�{��
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_POWERBOMB,50);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 107){
		//---�G�^�[�i�����i�m���j
		if(rnd < 150){
			//---���C�t�E�B���h
			crbatCPUThink_SetMagicAtack(pChara,5);
		} else if(rnd < 300){
			//---���J�o���[�Q
			crbatCPUThink_SetMagicAtack(pChara,3);
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
	} else if(pChara->BattleInfo.Enemy.ActionType == 108){
		//---�G�h
		if(pChara->GetBattleFlag(0)){
			//---���߂Ă���A�J�X�P�[�h�{��
			pChara->SetBattleFlag(0,0);
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KASCADEBOMB,160);
		} else if(rnd < 150){
			//---��������
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KONRANKOUSEN,20);
		} else if(rnd < 400){
			//---���[�U�[����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_LAYZERBEAM,65);
		} else if(rnd < 550){
			//---���ꎕ�N���b�V��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_IREBACRASH);
		} else if(rnd < 700){
			//---�Ƃ���
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOKASU);
		} else if(rnd < 900 && !pChara->GetPersonalTurn()){
			//---���߂�
			pChara->AddPersonalTurn(2);
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KASCADEBOMB,85);
//			pChara->SetBattleFlag(0,1);
//			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TAMERU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 109){
		//---���[�t�B�A
		if(turn == 0){
			//---�G�N�X�e���h
			crbatCPUThink_SetMagicAtack(pChara,
				22,-1,0,&pBtChara[BATTLECHARA_STARTENEMY + 1]);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_RARFIAATACK);
			pChara->Command.Target = (ei_u32)&pBtChara[1];//---�f�B�U�^�[�Q�b�g
			pBtChara[1].SetAbility(BTAB_S_BARRIER100,1);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 110){
		//---�A�Y�O���C
		//---�f�X�t�H�[�X
		if(turn == 0){
			crbatCPUThink_SetMagicAtack(pChara,21,-1,0,&pBtChara[2]);
		} else {
			crbatCPUThink_SetMagicAtack(pChara,21,-1,0,&pBtChara[0]);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 111){
		//---�n�C�v���b�V���[
		if(rnd < 200){
			//---�˕�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOPPU,65);
		} else if(rnd < 400){
			//---�E�B���h�I�[�u
			crbatCPUThink_SetMagicAtack(pChara,55);
		} else if(rnd < 600){
			//---�Ռ��g
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SHOGEKIHA);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 112){
		//---�S�[�X�g�c���[
		if(rnd < 333){
			//---�z��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KYUKETSU);
		} else if(rnd < 450){
			//---�C���t���G���X
			crbatCPUThink_SetMagicAtack(pChara,20);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 113){
		//---���o�t
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
			//---�_�C���u���X
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,62);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 114){
		//---�E�H�b�`���[
		if(rnd < 250){
			//---�Ή�����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAENHOUSHA,80);
		} else if(rnd < 500 && !pChara->GetTurnAtack()){
			//---�p���[�{��
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_POWERBOMB,96);
		} else if(rnd < 700 && !pChara->GetTurnAtack()){
			//---�˕�
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOPPU,80);
		} else if(rnd < 700){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAENHOUSHA,60);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 115){
		//---���^���n���h
		if(rnd < 450){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGURU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 116){
		//---�Z���T�[�q
		if(rnd < 250){
			//---�Ö��K�X
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,30);
		} else if(rnd < 500){
			//---�|�C�Y���K�X
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_POISON,50);
		} else if(rnd < 750){
			//---�T�C�����g�K�X
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SILENTBREATH,30);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 117){
		//---�Z���T�[�f
		if(rnd < 200){
			//---�p���[�u�[�X�g
			crbatCPUThink_SetMagicAtack(pChara,19);
		} else if(rnd < 400){
			//---�v���e�N�V����
			crbatCPUThink_SetMagicAtack(pChara,13);
		} else if(rnd < 600){
			//---���J�o���[�Q
			crbatCPUThink_SetMagicAtack(pChara,3);
		} else if(rnd < 800){
			//---�f�B�X�g�[�V����
			crbatCPUThink_SetMagicAtack(pChara,12);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 118){
		//---�Z���T�[�a
		if(rnd < 333 && !pChara->GetTurnAtack()){
			//---�Z���t���[�Y
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,49);
		} else if(rnd < 333){
			crbatCPUThink_SetMagicAtack(pChara,48);
		} else if(rnd < 700 && !pChara->GetTurnAtack()){
			//---�O���X�V�[�h
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,61);
		} else if(rnd < 700){
			crbatCPUThink_SetMagicAtack(pChara,60);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	}

	return crbatCPUThink4(pChara,turn,rnd);
}
