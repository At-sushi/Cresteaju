//---ステータスセット
void CrCharacter::SetLP(ei_s32 value)
{
	CharaInfo.lp = value;
}

void CrCharacter::SetMC(ei_s32 value)
{
	if(value < 0)
		value = 0;

	CharaInfo.mc = value;
}

void CrCharacter::SetBalance(ei_s32 value)
{
	CharaInfo.balance = value;
}


void CrCharacter::SetMaxLP(ei_s32 value)
{
	CharaInfo.max_lp = value;
}

void CrCharacter::SetMaxMC(ei_s32 value)
{
	CharaInfo.max_mc = value;
}

/*void CrCharacter::SetMaxBalance(ei_s32 value)
{
	CharaInfo.max_sp = value;
}*/

//---値を得る
ei_s32 CrCharacter::GetLP(void)
{
	return CharaInfo.lp;
}

ei_s32 CrCharacter::GetMC(void)
{
	return CharaInfo.mc;
}

ei_s32 CrCharacter::GetBalance(void)
{
	return CharaInfo.balance;
}


ei_s32 CrCharacter::GetMaxLP(void)
{
	return CharaInfo.max_lp;
}

ei_s32 CrCharacter::GetMaxMC(void)
{
	return CharaInfo.max_mc;
}

/*ei_s32 CrCharacter::GetMaxSP(void)
{
	return CharaInfo.max_sp;
}*/

//---ステータスの足し引き
ei_s32 CrCharacter::AddLP(ei_s32 value)
{
	return AddStatus(value,&CharaInfo.lp,&CharaInfo.max_lp,&LPMinStatus);
}

ei_s32 CrCharacter::AddMC(ei_s32 value)
{
	int ret = AddStatus(value,&CharaInfo.mc,&CharaInfo.max_mc,&LPMinStatus);

	if(GetMC() < 0)
		SetMC(0);

	if(value > 0){
		if(ret + value > GetMC()){
			//---廃棄！
			HistoryAddDestroyMC(ret + value - GetMC());
		}
	}

	return ret;
}

ei_s32 CrCharacter::AddBalance(ei_s32 value)
{
	return AddStatus(value,&CharaInfo.balance,&BalanceMaxStatus,&BalanceMinStatus);
}

//---最大値
ei_s32 CrCharacter::AddMaxLP(ei_s32 value)
{
	return AddStatus(value,&CharaInfo.max_lp,&LPMaxStatus,&LPMinStatus);
}

ei_s32 CrCharacter::AddMaxMC(ei_s32 value)
{
	return AddStatus(value,&CharaInfo.max_mc,&LPMaxStatus,&LPMinStatus);
}

/*ei_s32 CrCharacter::AddMaxSP(ei_s32 value)
{
	return AddStatus(value,&CharaInfo.max_sp,&LPMaxStatus,&LPMinStatus);
}
*/
