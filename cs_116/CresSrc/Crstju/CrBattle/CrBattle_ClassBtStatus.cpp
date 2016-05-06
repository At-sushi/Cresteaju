//--------------------------------------
//---BattleStatus
//---�s���\���H
ei_s32 CrBattleCharacter::IsEnableAction(void)
{
	//---���Ȃ�������s�����ւ��܂��Ȃ����
	if(!DoExist())
		return 0;

	//---�|��Ă�Ζ��������
	if(IsDown())
		return 0;

	return 1;
}

//---���@�͎g���邩�H
ei_s32 CrBattleCharacter::IsEnableMagic(void)
{
	//---���ق��Ă���
	if(GetBtStatus() & BTST_CHINMOKU)
		return 0;

	return 1 & IsEnableAction();
}

//---�����I�s���͂Ƃ�邩�H
ei_s32 CrBattleCharacter::IsEnableMoveing(void)
{
	//---�܂Ђ��Ă���
	if(GetBtStatus() & BTST_MAHI)
		return 0;

	return 1 & IsEnableAction();
}

//---�������邩
ei_s32 CrBattleCharacter::IsEnableEscape(void)
{
	//---��ჁA�����̓_��
	if(GetBtStatus() & BTST_MAHI)
		return 0;
	if(GetBtStatus() & BTST_KONRAN)
		return 0;

	return 1 & (IsDown() ? 0 : 1);
}

//---�|��Ă��Ȃ����H
ei_s32 CrBattleCharacter::IsDown(void)
{
	//---�C����
	if(IsKizetu())
		return 1;
	//---�Q�Ă��肵����
	if(GetBtStatus() & BTST_NEMURI)
		return 1;

	return 0;
}

//---�C�₵�Ă邩�H
ei_s32 CrBattleCharacter::IsKizetu(void)
{
	if(GetLP() <= 0)
		return 1;
	return 0;
}

ei_u32 CrBattleCharacter::GetBtStatus(void)
{
	return BattleInfo.Status;
}

static int ContinueTime[] = 
{
	-1,-1, 8,-1,
	-1, 8,-1, 8,
	-1,-1, 8, 1,
	-1,-1,-1,-1,
	//---plus status
	8,12,8,5,
	8,16,8,4,
	8,8,8,8,
	8,8,8,8
};

//---�X�e�[�^�X�������Ԃ𓾂�
int CrBattleCharacter::GetStatusContinueTime(ei_u32 status)
{
	int t = ContinueTime[GetBit(status)];

	if(t == -1)
		return t;

	//---�\�͂ɉ����Ď��Ԃ�ω�������
	if(status & 0xffff){
		//---�}�C�i�X�X�e�[�^�X
		if(Ability(BTAB_P_KAIFUKU2)){
//			t = (t * 2) / 3;
			t /= 2;
		} else if(Ability(BTAB_P_KAIFUKU1)){
//			t /= 2;
			t = (t * 2) / 3;
		} else if(Ability(BTAB_M_KAIFUKU)){
			t *= 2;
		}
	} else {
		//---�v���X�X�e�[�^�X
		if(Ability(BTAB_P_JIZOKU2)){
			t *= 2;
		} else if(Ability(BTAB_P_JIZOKU1)){
			t = (t * 15) / 10;
		} else if(Ability(BTAB_M_JIZOKU)){
			t /= 2;
		}
	}

	return t;
}

//---�X�e�[�^�X�N���A
void CrBattleCharacter::ClearBtStatus(ei_u32 status /*= 0*/)
{
	if(status == 0)
		BattleInfo.Status = 0;
	else
		BattleInfo.Status &= (~status);
}

int CrBattleCharacter::GetBit(ei_u32 status)
{
	int a = 0;
	for(a = 0;a < 32;a ++){
		if(status & (1 << a))
			return a;
	}
	return 0;
}

//---�X�e�[�^�X�ǉ�
void CrBattleCharacter::AddBtStatus(ei_u32 status,int ext /* = 1*/)
{
	int bit = GetBit(status);

	//---�C�⒆��������֌W�Ȃ�
	if(IsKizetu())
		return;

	//---����\�͂��l��
	if((GetBtStatus() & BTST_WORLD) && (status & BTST_MINAS)){
		//---���[���h
		return;
	}
	if(Ability(BTAB_P_DOKU) && (status & BTST_DOKU)){
		return;
	}
	if(Ability(BTAB_P_NEMURI) && (status & BTST_NEMURI)){
		return;
	}
	if(Ability(BTAB_P_CHINMOKU) && (status & BTST_CHINMOKU)){
		return;
	}
	if(Ability(BTAB_P_KONRAN) && (status & BTST_KONRAN)){
		return;
	}
	if(Ability(BTAB_P_MAHI) && (status & BTST_MAHI)){
		return;
	}

	if(Ability(BTAB_P_HENKA) && (status & BTST_JAKUKA)){
		return;
	}

	if(Ability(BTAB_P_HENKA) && (status & BTST_ZERO)){
		return;
	}
	if(Ability(BTAB_P_ZERO) && (status & BTST_ZERO)){
		return;
	}

	if(Ability(BTAB_P_HENKA) && (status & BTST_KURAYAMI)){
		return;
	}
	if(Ability(BTAB_P_KURAYAMI) && (status & BTST_KURAYAMI)){
		return;
	}

	if(status & BTST_NEMURI){
		//---���肾������R�}���h���Z�b�g
		ResetCommand();
	}

	BattleInfo.Status |= status;

	int max = GetStatusContinueTime(status);
	
	if(max > 0)
		max *= ext;

	BattleInfo.StatusContinueMax[bit] =
		BattleInfo.StatusContinue[bit] = max;//GetStatusContinueTime(status);

	if(BattleInfo.StatusContinue[bit] >= 1){
		//---�g�����^�[���𔲂�������
		BattleInfo.StatusContinue[bit] ++;
	}
}

//---��������
ei_u32 CrBattleCharacter::GetBtStatusContinue(int status)
{
	int bit = GetBit(status);
	int value = BattleInfo.StatusContinue[bit];

//	if(BattleInfo.StatusContinue[bit] > BattleInfo.StatusContinueMax[bit])
//		return BattleInfo.StatusContinueMax[bit];
	if(value > (ei_s32)GetBtStatusContinueMax(status))
		return GetBtStatusContinueMax(status);

//	return BattleInfo.StatusContinue[bit];
	return value;
}

ei_u32 CrBattleCharacter::GetBtStatusContinueMax(int status)
{
	int value = BattleInfo.StatusContinueMax[GetBit(status)];

	return value;//BattleInfo.StatusContinueMax[GetBit(status)];
}

//---�^�[����i�߂�
void CrBattleCharacter::AddTurnStatus(int status,int turn /*= 1*/)
{
	int bit = GetBit(status);

	if(BattleInfo.StatusContinue[bit] != -1){
		//---�i�v������ԂłȂ����
		BattleInfo.StatusContinue[bit] -= turn;
		if(BattleInfo.StatusContinue[bit] < 0){
			//---�O�ȉ��ɂȂ�΂��̃X�e�[�^�X�I��
			BattleInfo.StatusContinue[bit] = 0;
			ClearBtStatus(status);
		}
	}
}

//---�푰
ei_s32 CrBattleCharacter::GetType(void)
{
	return BattleInfo.BaseType;
}

void CrBattleCharacter::SetType(int type)
{
	BattleInfo.BaseType = type;
}

//---�A�r���e�B�Z�b�g
void CrBattleCharacter::SetAbility(ei_s32 ability,int flag)
{
	ei_u32 temp = (ei_u32)ability;

	BattleInfo.Ability[temp / 32] = 
		(BattleInfo.Ability[temp / 32] & (~(1 << (temp % 32))) )
	| (flag << (temp % 32));
}

//---����\�͂�����
ei_s32 CrBattleCharacter::Ability(ei_s32 ability)
{
	ei_u32 temp = (ei_u32)ability;
	ei_s32 ret = 0;

	if(ability < 15){
		//---�ω�
		ret |= Ability(BTAB_P_HENKA);
	}
	if(ability < 31){
		//---���ׂ�
		ret |= Ability(BTAB_P_SUBETE);
	}

	if(BattleInfo.Ability[temp / 32] & (1 << (temp % 32))){
		ret |= 1;
	}

	return ret;
}

//---------------------------------
//---�f�t�F���X�J�E���g
void CrBattleCharacter::ResetDefenseCount(void)
{
	OnlyInfo.DefenseCount = 0;
}

void CrBattleCharacter::AddDefenseCount()
{
	OnlyInfo.DefenseCount ++;
}

ei_s32 CrBattleCharacter::GetDefenseCount(void)
{
	return OnlyInfo.DefenseCount;
}

//---�T�u�t���b�O
ei_s32 CrBattleCharacter::SetBattleFlag(int number,int flag)
{
	int old;

	if(number >= BATLLECHARA_FLAG_MAX)
		return 0;

	old = OnlyInfo.Flags[number];
	OnlyInfo.Flags[number] = flag;

	return old;
}

ei_s32 CrBattleCharacter::GetBattleFlag(int number)
{
	if(number >= BATLLECHARA_FLAG_MAX)
		return 0;
	return OnlyInfo.Flags[number];
}

//--�L���A�[
void CrBattleCharacter::CureStatus(void)
{
	int a;
	ei_u32 st;

	//---�}�C�i�X�X�e�[�^�X���N���A����
	for(a = 1 , st = 1;a < 16;a ++ , st = st << 1){
		ClearBtStatus(st);
	}
}


//---�t�@�[�X�g�A�^�b�N
ei_u32 CrBattleCharacter::GetFirstAtack(void)
{
	if(Ability(BTAB_S_FIRSTATACK))
		return 1;
	if(GetFirstestAtack())
		return 1;

	return OnlyInfo.FirstAtack;
}

void CrBattleCharacter::EnableFirstAtack(int enable)
{
	OnlyInfo.FirstAtack = enable;
}

//---��ԑ����t�@�[�X�g�A�^�b�N
ei_u32 CrBattleCharacter::GetFirstestAtack(void)
{
	if(Ability(BTAB_S_FIRSTESTATACK))
		return 1;

	return OnlyInfo.FirstestAtack;
}

void CrBattleCharacter::EnableFirstestAtack(int enable)
{
	OnlyInfo.FirstestAtack = enable;
}

//---�^�[���A�^�b�N�t���b�O
ei_s32 CrBattleCharacter::TurnAtack = 0;

ei_s32 CrBattleCharacter::GetTurnAtack(void)
{
	return TurnAtack;
}

void CrBattleCharacter::AddTurnAtack(int value /*= 1*/)
{
	TurnAtack += value;
}

void CrBattleCharacter::ResetTurnAtack(void)
{
	TurnAtack = 0;
}

//---�J�I�X���[�h�^�[����
void CrBattleCharacter::AddKaosTurn(void)
{
	OnlyInfo.KAOSTurn ++;
}

void CrBattleCharacter::ResetKaosTurn(void)
{
	OnlyInfo.KAOSTurn = 0;
}

ei_s32 CrBattleCharacter::GetKaosTurn(void)
{
	return OnlyInfo.KAOSTurn;
}

ei_s32 CrBattleCharacter::GetPersonalTurn(void)
{
	return OnlyInfo.PersonalTurn;
}

void CrBattleCharacter::AddPersonalTurn(int value /*= 1*/)
{
	OnlyInfo.PersonalTurn += value;

	if(OnlyInfo.PersonalTurn < 0)
		OnlyInfo.PersonalTurn = 0;
}

void CrBattleCharacter::ResetPersonalTurn(void)
{
	OnlyInfo.PersonalTurn = 0;
}

//---�q�X�g���[
void CrBattleCharacter::HistoryAddReceiveDamage(int damage)
{
	CrCharacter::HistoryAddReceiveDamage(damage);

	AddRuinDamage(damage);
}

void CrBattleCharacter::AddRuinDamage(int damage)
{
	OnlyInfo.RuinDamage += damage;

	if(OnlyInfo.RuinDamage < 0)
		OnlyInfo.RuinDamage = 0;
	if(OnlyInfo.RuinDamage > 99999)
		OnlyInfo.RuinDamage = 99999;
}

//---���[�C���_���[�W�N���A
void CrBattleCharacter::ResetRuinDamage(void)
{
	OnlyInfo.RuinDamage = 0;
}

ei_s32 CrBattleCharacter::GetRuinDamage(void)
{
	return OnlyInfo.RuinDamage;
}

//---���[���h�^�[��
void CrBattleCharacter::SetWorldTurn(int turn)
{
	OnlyInfo.WorldTurn = turn;
}

void CrBattleCharacter::AddWorldTurn(int value)
{
	OnlyInfo.WorldTurn += value;
	if(OnlyInfo.WorldTurn < 0)
		OnlyInfo.WorldTurn = 0;
}

ei_s32 CrBattleCharacter::GetWorldTurn(void)
{
	return OnlyInfo.WorldTurn;
}

//---
void CrBattleCharacter::SetWorldCountTurn(int turn)
{
	OnlyInfo.WorldCountTurn = turn;
}

void CrBattleCharacter::AddWorldCountTurn(int value)
{
	OnlyInfo.WorldCountTurn += value;
	if(OnlyInfo.WorldCountTurn < 0)
		OnlyInfo.WorldCountTurn = 0;
}

ei_s32 CrBattleCharacter::GetWorldCountTurn(void)
{
	return OnlyInfo.WorldCountTurn;
}

//---�I�[�g�K�[�h
void CrBattleCharacter::SetAutoGard(int set)
{
	OnlyInfo.AutoGard = set;
}

ei_s32 CrBattleCharacter::GetAutoGard(void)
{
	return OnlyInfo.AutoGard;
}
