
//---�f�[�^�R�s�[
CRBATINIT_API int crbatEndBattle_CopyCharaData(CR_BATTLEINFO *pInfo)
{
	int a;
	CrCharacter *pChara;

	//---�f�[�^�R�s�[
	for(a = 0;a < MEMBER_MAX;a ++){
		pChara = crcharaGetPartyMember(a);
		if(pChara != NULL){
			//---�����
			memcpy(&pChara->CharaInfo,&pBtChara[a].CharaInfo,sizeof(pBtChara[a].CharaInfo));

			//---�C�₵�Ă�����k�o���P�ɃZ�b�g
			if(pChara->GetLP() <= 0){
				pChara->SetLP(1);
			}
			//---�l�b�񕜃��Z�b�g
			pChara->SetLastUsingMagic();
			pChara->SetDisableMCCount(-1);
		}
	}

	return 1;
}

//---�L�����N�^�[�p�^�[����ǂݍ���
CRBATINIT_API int crbatReadCharaPattern(void)
{
	int a,c = 1;
	char s[80];
	CrCharacter *pChara;

	//---�X�e�[�^�X�A�C�R���ǂݍ���
	c &= eiCellReadPattern(
		&BattleStatusCell[0],
		CR_DATADIR1"BattleStatus.acf",CR_DATAFILE1,crdataGetFileMode(),
		0,BATTLE_STATUSICONMAX,32,32);
	eiCellSetSurface(
		&BattleStatusCell[0],
		BATTLE_STATUSICONSURFACE_X,BATTLE_STATUSICONSURFACE_Y,
		32,32,BATTLE_STATUSICONMAX);

	for(a = 0;a < MEMBER_MAX;a ++){
		pChara = crcharaGetPartyMember(a);
		if(pChara != NULL){
			eiDebugWriteFile(pChara->GetName());
			eiDebugWriteFile("\n");
			sprintf(s,"%s%s",CR_DATADIR4,pChara->GetBattleFileName());
/*		if(a == 0){
		} else if(a == 1){
			sprintf(s,"%s%s",CR_DATADIR4,"BatHiro.bmp");
		} else {
			sprintf(s,"%s%s",CR_DATADIR4,"BatRacis.bmp");
		}*/

			c &= eiCellReadPattern(
				&BattleCharaCell[0],
				s,CR_DATAFILE4,crdataGetFileMode(),
				a * BATTLE_CHARAPATTERN,BATTLE_CHARAPATTERN,32,32);
			eiCellSetSurface(
				&BattleCharaCell[a * BATTLE_CHARAPATTERN],
				(32 * BATTLE_CHARAALYAWSSURFACE * a) % 640,
				((32 * BATTLE_CHARAALYAWSSURFACE * a) / 640) * 32,
				32,32,BATTLE_CHARAALYAWSSURFACE);

			pBtChara[a].SetCell(&BattleCharaCell[a * BATTLE_CHARAPATTERN]);
		}
	}

	return c;
}


CRBATINIT_API int crbatCopyData(void)
{
	int a,b,c = 0;
	CrCharacter *pChara;

	//---�f�[�^�R�s�[
	for(a = 0;a < MEMBER_MAX;a ++){
		pChara = crcharaGetPartyMember(a);
		if(pChara != NULL){
			//---�����
			memcpy(&pBtChara[a].CharaInfo,&pChara->CharaInfo,sizeof(pBtChara[a].CharaInfo));
//			memcpy(&pBtChara[a].BattleHistory,&pChara->BattleHistory,sizeof(pBtChara[a].BattleHistory));

			memset(&pBtChara[a].BattleInfo,0,sizeof(pBtChara[a].BattleInfo));
			memset(&pBtChara[a].OnlyInfo,0,sizeof(pBtChara[a].OnlyInfo));
			memset(&pBtChara[a].Command,0,sizeof(pBtChara[a].Command));

			//---����
			pBtChara[a].BattleInfo.Existence = 1;
		} else {
			//---���Ȃ�
			memset(&pBtChara[a].CharaInfo,0,sizeof(pBtChara[a].CharaInfo));
			memset(&pBtChara[a].OnlyInfo,0,sizeof(pBtChara[a].OnlyInfo));
			memset(&pBtChara[a].Command,0,sizeof(pBtChara[a].Command));

			pBtChara[a].BattleInfo.Existence = 0;
		}

		if(crdataGetSystem()->BattleCommandReset <= 1){
			//---�o�g�����ƃ��Z�b�g
			memset(&pBtChara[a].GetCharacterInfo()->BattleMenuCursor,0,
				sizeof(pBtChara[a].GetCharacterInfo()->BattleMenuCursor));
		}

		//---�����t���b�O
		pBtChara[a].BattleInfo.FriendOrEnemy = 1;
		pBtChara[a].SetType(CHARATYPE_NINGEN);
		//---�l�b
		pBtChara[a].ResetMagicTime(1);
		//---�G�������g
		for(b = 0;b < 16;b ++){
			pBtChara[a].BattleInfo.Element[b] = 1000;//---100%
		}

		//---�A�r���e�B�Z�b�g
		pBtChara[a].SetAbility(BTAB_S_CRITICAL1,1);
		if(pBtChara[a].Who() == 3){
			//---�i�b�N
			pBtChara[a].SetAbility(BTAB_S_KAIFUKUMAGIC_P,1);
		}
		if(pBtChara[a].Who() == 14){
			//---�N���X�e�B�[��
			pBtChara[a].SetAbility(BTAB_P_HENKA,1);
			pBtChara[a].SetAbility(BTAB_S_BARRIER200,1);
//			pBtChara[a].SetAbility(BTAB_S_FIRSTATACK,1);
		}

		//---�h��
		int uni[5] = {0,0,0,0,0};

		for(b = 0;b < EQ_WEAPON_MAX;b ++){
			switch(pBtChara[a].GetWeapon(b)){
			case 82:
				//---�����E�j�u���[�h
				uni[0] = 1;
				break;
			}
		}

		for(b = 0;b < EQ_PROTECTOR_MAX;b ++){
			switch(pBtChara[a].GetProtector(b)){
			case 132:
				//---�h�u�E�j�N���X
				uni[1] = 1;
				break;
			case 254:
				//---�E�j�}�����}�X�N
				uni[3] = 1;
				break;

			case 98:
				//---�o���A�X�[�c
				//---�o���A�Q�T
				pBtChara[a].SetAbility(BTAB_S_BARRIER25,1);
				break;
			case 116:
				//---�ӂ�ǂ��A�[�}�[
				//---�t�@�[�X�g�A�^�b�N
				pBtChara[a].SetAbility(BTAB_S_FIRSTATACK,1);
				break;
			case 118:
				//---��n�̈�
				//---�y�ϐ�
				pBtChara[a].BattleInfo.Element[ELEMENT_EARTH] = 0;
				break;
			case 119:
				//---�����̃��[�u
				pBtChara[a].SetAbility(BTAB_M_MC,1);
				break;
			case 127:
				//---�h���S���A�C�Y
				//---�u���X�O
				pBtChara[a].SetAbility(BTAB_P_BREATH0,1);
				break;
			case 133:
				//---���r���O�A�[�}�[
				//---�|�񕜁A�|�ω��A�|�l�b
				pBtChara[a].SetAbility(BTAB_M_KAIFUKU,1);
				pBtChara[a].SetAbility(BTAB_M_HENKA,1);
				pBtChara[a].SetAbility(BTAB_M_MC,1);

			case 126:
				//---�A�C�X�A�[�}�[
				pBtChara[a].BattleInfo.Element[ELEMENT_AQUA] /= 2;
				break;
			case 130:
				//---�ю��̃��[�u
				pBtChara[a].BattleInfo.Element[ELEMENT_AQUA] /= 4;
				break;
			case 131:
				//---�Z�[�^�[
				pBtChara[a].BattleInfo.Element[ELEMENT_AQUA] /= 3;
				break;

//-----------------------------------
			case 156:
				//---�z���C�g�V�[���h
				pBtChara[a].SetAbility(BTAB_S_AUTOGARD,1);
				break;
			case 157:
				//---����̏�
				//---�u���X�S�^�T
				pBtChara[a].SetAbility(BTAB_P_BREATH45,1);
				pBtChara[a].SetAbility(BTAB_P_SOKUSHI,1);
				pBtChara[a].SetAbility(BTAB_P_NEMURI,1);
				pBtChara[a].SetAbility(BTAB_P_DOKU,1);
				pBtChara[a].SetAbility(BTAB_P_KURAYAMI,1);
				pBtChara[a].SetAbility(BTAB_P_HENKA_23,1);
				break;
			case 158:
				//---�_�����΂̏�
				//---���ϐ�
				pBtChara[a].BattleInfo.Element[ELEMENT_FIRE] /= 2;
				break;
			case 159:
				//---�_�����΂̏��E�����
				//---���ϐ�
				pBtChara[a].BattleInfo.Element[ELEMENT_FIRE] = 0;
				break;
			case 164:
				//---���C�t�f�B�t�F���_�[
				pBtChara[a].SetAbility(BTAB_S_SAISEI1,1);
				break;
			case 165:
				//---���΃V�[���h
				//---����ϐ�
				pBtChara[a].BattleInfo.Element[ELEMENT_AQUA] = 
					(pBtChara[a].BattleInfo.Element[ELEMENT_AQUA] * 3) / 5;
				break;
			case 167:
				//---�q���E�j�K�[�h
				uni[2] = 1;
				//---���ϐ�
				pBtChara[a].BattleInfo.Element[ELEMENT_AQUA] = 0;
				break;
			case 168:
				//---���C�[���΂��̏�
				//---����ϐ�
				pBtChara[a].BattleInfo.Element[ELEMENT_AQUA] = 
					(pBtChara[a].BattleInfo.Element[ELEMENT_AQUA] * 4) / 5;
				break;
			}
		}

		//---�A�N�Z�T���[
		int b5 = 0,b25 = 0,b100 = 0,unimant = 0;
		for(b = 0;b < EQ_ACCESSORY_MAX;b ++){
			switch(pBtChara[a].GetAccessory(b)){
			case 171:
				//---�R�[�q�[�C�������O
				pBtChara[a].SetAbility(BTAB_P_NEMURI,1);
				break;
			case 172:
				//---������
				pBtChara[a].SetAbility(BTAB_P_MAHI,1);
				break;
			case 173:
				//---������ׂ��
				pBtChara[a].SetAbility(BTAB_P_CHINMOKU,1);
				break;
			case 174:
				//---�h�N�ۂ��ۂ�
				pBtChara[a].SetAbility(BTAB_P_DOKU,1);
				break;
			case 175:
				//---�Ȃ�ƃV�[��
				pBtChara[a].SetAbility(BTAB_P_KONRAN,1);
				break;
			case 176:
				//---�E�т̐S
				pBtChara[a].SetAbility(BTAB_S_NOCOUNTER,1);
				break;
			case 177:
				//---�񕜂P
				pBtChara[a].SetAbility(BTAB_P_KAIFUKU1,1);
				break;
			case 178:
				//---�񕜂Q
				pBtChara[a].SetAbility(BTAB_P_KAIFUKU2,1);
				break;
			case 179:
				//---�l�b�P
				pBtChara[a].SetAbility(BTAB_P_MC1,1);
				break;
			case 180:
				//---�l�b�Q
				pBtChara[a].SetAbility(BTAB_P_MC2,1);
				break;
			case 181:
				//---�u���X�S�^�T
				pBtChara[a].SetAbility(BTAB_P_BREATH45,1);
				break;
			case 182:
				//---�u���X�Q�^�R
				pBtChara[a].SetAbility(BTAB_P_BREATH23,1);
				break;
			case 183:
				//---�����P
				pBtChara[a].SetAbility(BTAB_P_JIZOKU1,1);
				break;
			case 184:
				//---�����Q
				pBtChara[a].SetAbility(BTAB_P_JIZOKU2,1);
				break;
			case 185:
				//---�N���e�B�J���Q
				pBtChara[a].SetAbility(BTAB_S_CRITICAL2,1);
				break;
			case 186:
				//---��l�̎��
				pBtChara[a].SetAbility(BTAB_P_NEMURI,1);
				pBtChara[a].SetAbility(BTAB_P_MAHI,1);
				pBtChara[a].SetAbility(BTAB_P_DOKU,1);
				break;
			case 187:
				//---�J�I�X�u���[�`
				pBtChara[a].SetAbility(BTAB_S_KAOS,1);
				break;

			case 188:
				//---�X�y���s�A�X
				pBtChara[a].SetAbility(BTAB_S_HOJOMAHO,1);
				break;
			case 189:
				//---�N���e�B�J���R
				pBtChara[a].SetAbility(BTAB_S_CRITICAL3,1);
				break;
			case 190:
				//---�l�t�̃N���[�o�[
				pBtChara[a].SetAbility(BTAB_P_SOKUSHI,1);
				break;
			case 192:
				//---����
				pBtChara[a].SetAbility(BTAB_S_COUNTER25,1);
				break;
			case 193:
				//---����
				pBtChara[a].SetAbility(BTAB_S_COUNTER50,1);
				break;
			case 194:
				//---�B�l�̑�
				pBtChara[a].SetAbility(BTAB_S_COUNTER75,1);
				break;
			case 196:
				//---���΂����̂��܂���
				pBtChara[a].SetAbility(BTAB_P_HENKA,1);
				break;
			case 197:
				//---��Őe���̃q�Q
				pBtChara[a].SetAbility(BTAB_P_HENKA_23,1);
				break;
			case 198:
				//---��Őe���̂��݂���
				pBtChara[a].SetAbility(BTAB_P_HENKA_12,1);
				break;
			case 199:
				//---����������
				pBtChara[a].SetAbility(BTAB_P_HENKA_14,1);
				break;
			case 200:
				//---�o���A�{�[���T
				pBtChara[a].SetAbility(BTAB_S_BARRIER5,1);
				b5 ++;
				if(b5 == 2){
					//---�o���A�[�P�O
					pBtChara[a].SetAbility(BTAB_S_BARRIER10,1);
				}
				break;
			case 201:
				//---�o���A�{�[���Q�T
				pBtChara[a].SetAbility(BTAB_S_BARRIER25,1);
				b25 ++;
				if(b25 == 2){
					//---�o���A�[�T�O
					pBtChara[a].SetAbility(BTAB_S_BARRIER50,1);
				}
				break;
			case 202:
				//---�o���A�{�[���P�O�O
				pBtChara[a].SetAbility(BTAB_S_BARRIER100,1);
				b100 ++;
				if(b100 == 2){
					//---�o���A�[�Q�O�O
					pBtChara[a].SetAbility(BTAB_S_BARRIER200,1);
				}
				break;
			case 204:
				//---�ڋʃC�������O�i�����␳���̊O���m���R�^�S�j
				pBtChara[a].SetBtSubHitProb(1000 - ((1000 - pBtChara[a].GetBtSubHitProb()) * 3) / 4);
				break;
			case 205:
				//---�Ԃ��o���_�i�i�����␳���̊O���m�������j
				pBtChara[a].SetBtSubHitProb(1000 - (1000 - pBtChara[a].GetBtSubHitProb()) / 2);
				break;
			case 206:
				//---���}�E�j�}���g
				uni[4] = 1;
				unimant ++;
				if(unimant == 2){
					//---�J�E���^�[�Q�T
					pBtChara[a].SetAbility(BTAB_S_COUNTER25,1);
				}
				break;
			case 207:
				//---��Έ����N
				pBtChara[a].SetAbility(BTAB_S_ANMIN,1);
				break;
			case 208:
				//---�����΂̎w��
//				pBtChara[a].SetAbility(BTAB_P_NEMURI,1);
//				pBtChara[a].SetAbility(BTAB_P_CHINMOKU,1);
				pBtChara[a].AddBtStatus(BTST_FSHIELD);
				break;
			case 273:
				//---��ȃl�b�N���X
				pBtChara[a].BattleInfo.Element[ELEMENT_THUNDER] = 0;
				break;
			case 274:
				//---��m�̘r��
				pBtChara[a].SetAbility(BTAB_P_KONRAN,1);
				pBtChara[a].SetAbility(BTAB_P_MAHI,1);
				pBtChara[a].SetAbility(BTAB_P_KURAYAMI,1);
				break;
			}
		}

		//---��ԕω��n�A�N�Z�T��
		for(b = 0;b < EQ_ACCESSORY_MAX;b ++){
			switch(pBtChara[a].GetAccessory(b)){
			case 191:
				//---���r�[�A�C
				for(c = ELEMENT_FIRE;c <= ELEMENT_OTHER;c ++){
					pBtChara[a].BattleInfo.Element[c] = 
						(pBtChara[a].BattleInfo.Element[c] * 75) / 100;
				}
				break;
			case 209:
				//---�����̎w��
				if(!pBtChara[a].Ability(BTAB_P_HENKA)){
//					pBtChara[a].SetAbility(BTAB_M_HENKA,1);
					pBtChara[a].SetAbility(BTAB_M_JIZOKU,1);
//					pBtChara[a].SetAbility(BTAB_M_KAIFUKU,1);
				}
				pBtChara[a].AddBtStatus(BTST_POWER);
				pBtChara[a].AddTurnStatus(BTST_POWER,1);
				pBtChara[a].AddBtStatus(BTST_KONRAN);
				break;
			case 210:
				//---�s�[�X�I�u���[��
				pBtChara[a].AddBtStatus(BTST_EXTEND);
				pBtChara[a].AddTurnStatus(BTST_EXTEND,1);
				break;
			}
		}

		if(uni[0] && uni[1] && uni[2] && uni[3] && uni[4]){
			pBtChara[a].SetAbility(BTAB_S_FIRSTESTATACK,1);
		}
	}

	return 1;
}
