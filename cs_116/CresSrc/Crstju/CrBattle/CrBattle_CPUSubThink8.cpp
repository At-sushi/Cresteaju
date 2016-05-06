CRBATCPU_API int crbatCPUThink8(CrBattleCharacter *pChara,int turn,int rnd)
{
	if(pChara->BattleInfo.Enemy.ActionType == 215){
		//---���N�X�[�A
		if(rnd < 150){
			//---�a�肩����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 350){
			//---�z��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KYUKETSU);
		} else if(rnd < 480){
			//---�T�C�����X
			crbatCPUThink_SetMagicAtack(pChara,15);
		} else if(rnd < 550){
			//---�C���t���G���X
			crbatCPUThink_SetMagicAtack(pChara,20);
		} else if(rnd < 700){
			//---�X�[�p�[�Z��
			crbatCPUThink_SetMagicAtack(pChara,57);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 228){
		//---�E�H�[�^�[�S�[�X�g
		if(rnd < 250){
			//---�A�N�A�\�[�h
			crbatCPUThink_SetMagicAtack(pChara,50);
		} else if(rnd < 400){
			//---�Z���t���[�Y
			crbatCPUThink_SetMagicAtack(pChara,49);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 229){
		//---�e�C���r�[�X�g
		if(rnd < 333){
			//---���݂�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 230){
		//---���e��
		if(pChara->GetBattleFlag(0)){
			//---�唚��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_JIBAKU3,0,pChara);
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
	} else if(pChara->BattleInfo.Enemy.ActionType == 231){
		//---�~�h�����V
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
	} else if(pChara->BattleInfo.Enemy.ActionType == 232){
		//---�o�g���Z���T�[
		if(rnd < 250){
			//---�p���[�{��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_POWERBOMB,100);
		} else if(rnd < 450){
			//---�X���[�v�u���X
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,30);
		} else if(rnd < 650){
			//---�T�C�����g�u���X
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SILENTBREATH,30);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 233){
		//---�}�c�^�P�E�B�U�[�g
		if(rnd < 333){
			//---�x�[�^�X�R�[��
			crbatCPUThink_SetMagicAtack(pChara,68);
		} else if(rnd < 500){
			//---�C���t���G���X
			crbatCPUThink_SetMagicAtack(pChara,20);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 234){
		//---�p���[�n���h
		if(rnd < 250){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGURU);
		} else if(rnd < 500){
			//---�ːi
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOSSHIN);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 236){
		//---���C�����E
		if(rnd < 333){
			//---���݂Ȃ�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_IKADUCHI,300);
		} else if(rnd < 600){
			//---���݂�
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 237){
		//---�t�@�[�V�F��
		if(rnd < 250){
			//---�A�N�A�\�[�h
			crbatCPUThink_SetMagicAtack(pChara,50);
		} else if(rnd < 500){
			//---���S�C
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_MIZUDEPPOU,150);
		} else if(rnd < 700){
			//---���J�o���C�V����
			crbatCPUThink_SetMagicAtack(pChara,6);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 238){
		//---�~���N�{�[��
		if(rnd < 250){
			//---�X���[�s���O
			crbatCPUThink_SetMagicAtack(pChara,11);
		} else if(rnd < 450){
			//---�p���[�u�[�X�g
			crbatCPUThink_SetMagicAtack(pChara,19);
		} else if(rnd < 700){
			//---���肩����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 240){
		//---�o�g���N���E��
		if(rnd < 333){
			//---���C�W���O�T��
			crbatCPUThink_SetMagicAtack(pChara,45);
		} else if(rnd < 666){
			//---�e���W���b�W�����g
			crbatCPUThink_SetMagicAtack(pChara,69);
		} else if(rnd < 750){
			//---�f�X�t�H�[�X
			crbatCPUThink_SetMagicAtack(pChara,21);
		} else if(rnd < 900){
			//---�R���t���[�W����
			crbatCPUThink_SetMagicAtack(pChara,18);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 241){
		//---�_�[�N�p���f�B��
		if(rnd < 250){
			//---������
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else if(rnd < 500){
			//---���肩����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 242){
		//---�X�g�����O�X
		if(rnd < 200){
			//---�ːi
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOSSHIN);
		} else if(rnd < 400){
			//---�Ȃ��|��
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGITAOSU);
		} else if(rnd < 600){
			//---����
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGURU);
		} else {
			//---�ʏ�U��
			crbatCPUThink_SetAtack(pChara);
		}
	}
	return 1;
}
