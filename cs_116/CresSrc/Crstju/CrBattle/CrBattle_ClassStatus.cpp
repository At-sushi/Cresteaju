//------------------------------------------
//---ＬＰ計算
ei_s32 CrBattleCharacter::ResultLP(int number)
{
	int prev;

	prev = AddLP(number);

	if(IsKizetu()){
		//---気絶したら
		//---状態を全てリセット
		ClearBtStatus();
		//---コマンドを待機中に
		Command.Main = BAT_COMMAND_WAIT;

		if(crbatGetBattleKizetuMode() == 1){
			//---いなくなる
			BattleInfo.Existence = 0;
		}

		if(GetLP() == 0){
			return 0;
		}
		return -1;
	}
	if(prev <= 0 && !IsKizetu() /*0 < GetLP()*/){
		//---状態を全てリセット
		ClearBtStatus();
		//---コマンドを待機中に
		Command.Main = BAT_COMMAND_WAIT;
	}

	return 1;
}

//---即死
ei_s32 CrBattleCharacter::Sokushi(void)
{
	if(Ability(BTAB_P_SOKUSHI))
		return 0;

	ResultLP(-GetLP());
	HistoryAddDeathCount();

	return 1;
}


//---ＭＣ回復レート
ei_s32 CrBattleCharacter::GetMCRate(void)
{
	int rate;

	rate = 1000;

	if(GetBtStatus() & BTST_NEMURI){
		//---眠っていたら回復量増加
		rate = 1300;
	}

	if(Ability(BTAB_P_MC2)){
		//---ＭＣ○２
		rate = (rate * 140) / 100;
	} else if(Ability(BTAB_P_MC1)){
		//---ＭＣ○１
		rate = (rate * 120) / 100;
	} else if(Ability(BTAB_M_MC)){
		//---ＭＣ×
		rate = (rate * 50) / 100;
	}

	return rate;
}

//---ステータス変化の変化確率
ei_s32 CrBattleCharacter::GetStatusChangeRate(int rate)
{
	if(Ability(BTAB_P_HENKA)){
		rate = 0;
	} else if(Ability(BTAB_P_HENKA_14)){
		rate /= 4;
	} else if(Ability(BTAB_P_HENKA_12)){
		rate /= 2;
	} else if(Ability(BTAB_P_HENKA_23)){
		rate = (rate * 3) / 2;

	} else if(Ability(BTAB_M_HENKA)){
//		rate = rate + ((1000 - rate) / 2);
//		rate *= 2;
		if(rate + ((1000 - rate) / 2) > rate * 2)
			rate = rate + ((1000 - rate) / 2);
		else
			rate *= 2;
	}

	return rate;
}

//---ステータス以上が治る確率
ei_s32 CrBattleCharacter::GetStatusRecoveryRate(int rate)
{
	if(Ability(BTAB_P_KAIFUKU2)){
		rate *= 2;
	} else if(Ability(BTAB_P_KAIFUKU1)){
		rate = (rate * 15) / 10;
	} else if(Ability(BTAB_M_KAIFUKU)){
		rate = (rate * 5) / 10;
	}

	return rate;
}

//---最後に魔法を使って何ターン経ったか
void CrBattleCharacter::ResetMagicTime(int reset /*= 0*/)
{
	BattleInfo.FromLastMagic = 0;
}

ei_s32 CrBattleCharacter::AddFromLastMagic(void)
{
	int prev = BattleInfo.FromLastMagic;

	BattleInfo.FromLastMagic ++;

	return prev;
}

ei_s32 CrBattleCharacter::GetFromLastMagic(void)
{
	return BattleInfo.FromLastMagic;
}

//-----------------------------
ei_s32 CrBattleCharacter::GetBtAtack(int number)
{
	int value = CrCharacter::GetEqAtack(number);
	int status = BTST_POWER;

	if(GetBtStatus() & status){
		value = value + 
			(value * GetBtStatusContinue(status) / GetBtStatusContinueMax(status)
			 * 75) / 100;
	}

	//---extend
	status = BTST_EXTEND;
	if(GetBtStatus() & status){
		value = value + 
			(value * GetBtStatusContinue(status) / GetBtStatusContinueMax(status)
			* 25) / 100;
	}
	//---jakuka
	status = BTST_JAKUKA;
	if(GetBtStatus() & status){
		value = value - 
			(value * GetBtStatusContinue(status) / GetBtStatusContinueMax(status)
			* 25) / 100;
	}

	return value;
}

ei_s32 CrBattleCharacter::GetBtDefense(void)
{
	int value = CrCharacter::GetEqDefense();
	int status = BTST_PROTECT;

/*	if(GetBtStatus() & status){
		value = value + 
			value * GetBtStatusContinue(status) / GetBtStatusContinueMax(status);
	}*/

	status = BTST_ZERO;
	if(GetBtStatus() & status){
		value = value - (value * GetBtStatusContinue(status) / GetBtStatusContinueMax(status));
	}

	//---extend
	status = BTST_EXTEND;
	if(GetBtStatus() & status){
		value = value + 
			(value * GetBtStatusContinue(status) / GetBtStatusContinueMax(status)
			* 25) / 100;
	}
	//---jakuka
	status = BTST_JAKUKA;
	if(GetBtStatus() & status){
		value = value - 
			(value * GetBtStatusContinue(status) / GetBtStatusContinueMax(status)
			* 25) / 100;
	}

	return value;
}

ei_s32 CrBattleCharacter::GetBtMagicDefense(void)
{
	int value = CrCharacter::GetEqMagicDefense();
	int status = BTST_FSHIELD;

	if(!IsFriend()){
		value = CharaInfo.magic_defense;
	}

	if(crbatGetBattleMagicMode() == 1){
		value = 100 - (((100 - value) * 2) / 5);
	}

	if(value >= 100)
		value = 100;


/*	if(GetBtStatus() & status){
		value = value + 
			value * GetBtStatusContinue(status) / GetBtStatusContinueMax(status);
	}*/

	//---extend
	status = BTST_EXTEND;
	if(GetBtStatus() & status){
/*		value = value + 
			(value * GetBtStatusContinue(status) / GetBtStatusContinueMax(status)
			* 25) / 100;*/
		value = value + 
			((100 - value) * GetBtStatusContinue(status) / GetBtStatusContinueMax(status)
			* 25) / 100;
	}
	//---jakuka
	status = BTST_JAKUKA;
	if(GetBtStatus() & status){
/*		value = value - 
			(value * GetBtStatusContinue(status) / GetBtStatusContinueMax(status)
			* 25) / 100;*/
		value = value - 
			((100 - value) * GetBtStatusContinue(status) / GetBtStatusContinueMax(status)
			* 25) / 100;
	}

	return value;
}

ei_s32 CrBattleCharacter::GetBtAction(void)
{
	int value = CrCharacter::GetEqAction();
	int status = BTST_ACCEL;

	if(GetBtStatus() & status){
		value = value + 
			(value * GetBtStatusContinue(status) / GetBtStatusContinueMax(status)
			* 3);
	}

	//---extend
	status = BTST_EXTEND;
	if(GetBtStatus() & status){
		value = value + 
			(value * GetBtStatusContinue(status) / GetBtStatusContinueMax(status)
			* 25) / 100;
	}
	//---jakuka
	status = BTST_JAKUKA;
	if(GetBtStatus() & status){
		value = value - 
			(value * GetBtStatusContinue(status) / GetBtStatusContinueMax(status)
			* 25) / 100;
	}

	return value;
}

ei_s32 CrBattleCharacter::GetBtPower(void)
{
	return CrCharacter::GetEqPower();
}

ei_s32 CrBattleCharacter::GetBtVitality(void)
{
	return CrCharacter::GetEqVitality();
}

ei_s32 CrBattleCharacter::GetBtAgility(void)
{
	return CrCharacter::GetEqAgility();
}

ei_s32 CrBattleCharacter::GetBtSoul(void)
{
	int value = CrCharacter::GetEqSoul();
	int status = BTST_SOUL;

	if(GetBtStatus() & status){
		value = value + 
			(value * GetBtStatusContinue(status) / GetBtStatusContinueMax(status)
			* 4);
	}

	//---extend
	status = BTST_EXTEND;
	if(GetBtStatus() & status){
		value = value + 
			(value * GetBtStatusContinue(status) / GetBtStatusContinueMax(status)
			* 25) / 100;
	}
	//---jakuka
	status = BTST_JAKUKA;
	if(GetBtStatus() & status){
		value = value - 
			(value * GetBtStatusContinue(status) / GetBtStatusContinueMax(status)
			* 25) / 100;
	}

	return value;
}

ei_s32 CrBattleCharacter::GetBtMagic(void)
{
	int value = CrCharacter::GetEqMagic();
	int status = BTST_EXTEND;

	//---extend
	if(GetBtStatus() & status){
		value = value + 
			(value * GetBtStatusContinue(status) / GetBtStatusContinueMax(status)
			* 25) / 100;
	}
	//---jakuka
	status = BTST_JAKUKA;
	if(GetBtStatus() & status){
		value = value - 
			(value * GetBtStatusContinue(status) / GetBtStatusContinueMax(status)
			* 25) / 100;
	}

	return value;
}

//---武器命中率
ei_s32 CrBattleCharacter::GetBtHitProb(int number)
{
	int value = CrCharacter::GetEqHitProb(number);
	int status = BTST_KURAYAMI;

	if(GetBtStatus() & status){
//		value = value / 3;
		value = value - 
			(value * GetBtStatusContinue(status) / GetBtStatusContinueMax(status)
			* 80) / 100;
	}

	if(value >= 1000)
		value = 1000;
	else if(value < 0)
		value = 0;

	return value;
}

//---魔法命中率
ei_s32 CrBattleCharacter::GetBtMagicHitProb(CrMagic *pMagic)
{
	int value = pMagic->GetHitProb();
	int status = BTST_KURAYAMI;

	if(value != -1){
		if(GetBtStatus() & status){
			value = value - 
				(value * GetBtStatusContinue(status) / GetBtStatusContinueMax(status)
				* 50) / 100;
		}
	}

	if(value >= 1000)
		value = 1000;

	return value;
}

ei_s32 CrBattleCharacter::GetBtAvoidProb(void)
{
	int value;
	int status = BTST_DIST;

	value = CrCharacter::GetEqAvoidProb();

	if(Command.Main == BAT_COMMAND_DEFENSE){
		if(Command.Sub[0] == BAT_SUBCOM_AVOID){
			//---回避
//			value += 500;
			value = value + 
				((1000 - value)
				* 500 / 1000);
		}
	}

	//---ディストーション
	status = BTST_DIST;
	if(GetBtStatus() & status){
//		value = value + 
//			(666 * GetBtStatusContinue(status) / GetBtStatusContinueMax(status));
		value = value + 
			((1000 - value)
			* 666 / 1000)
			* GetBtStatusContinue(status) / GetBtStatusContinueMax(status);
	}

	if(value >= 1000)
		value = 1000;
	else if(value < 0)
		value = 0;

	return value;
}

ei_s32 CrBattleCharacter::GetBtSubHitProb(void)
{
	return CrCharacter::GetEqSubHitProb();
}

ei_s32 CrBattleCharacter::SetBtSubHitProb(int value)
{
	int old = GetBtSubHitProb();

	CharaInfo.sub_hit_prob = value;

	return old;
}

ei_s32 CrBattleCharacter::GetBtMagicAvoidProb(void)
{
	int value;
	int status = BTST_DIST;

	value = CrCharacter::GetEqMagicAvoidProb();

	if(Command.Main == BAT_COMMAND_DEFENSE){
		if(Command.Sub[0] == BAT_SUBCOM_AVOID){
			//---回避
//			value += 333;
			value = value + 
				((1000 - value)
				* 250 / 1000);

			if(value >= 1000){
				value = 1000;
			}
		}
	}

	//---ディストーション
	status = BTST_DIST;
	if(GetBtStatus() & status){
		value = value + 
			((1000 - value)
			* 250 / 1000)
			* GetBtStatusContinue(status) / GetBtStatusContinueMax(status);
	}

	if(value >= 1000)
		value = 1000;
	else if(value < 0)
		value = 0;

	return value;
}

//---武器アニメーション
ei_s32 CrBattleCharacter::GetBtWeaponAnime(int number)
{
	int weapon = CrCharacter::GetWeapon(number);

	if(weapon == 0){
		return 0;
	}
	return critemGetItemClass(weapon)->GetAnime();
}

//---武器が直接攻撃か？
ei_s32 CrBattleCharacter::IsBtWeaponDirect(int number)
{
	if(IsFriend()){
		//---武器の攻撃種類
		return critemGetItemClass(GetWeapon(number))->GetAtackKind();
	}

	return 1;
}

//---属性防御率
ei_s32 CrBattleCharacter::GetBtElement(int element)
{
	return BattleInfo.Element[element];
}

//---移動力
ei_s32 CrBattleCharacter::GetBtMove(void)
{
	int move = 5;

	return move;
}

//---必殺技使用不可能期間
ei_s32 CrBattleCharacter::SetSpecialDisable(int turn)
{
	OnlyInfo.SpecialDisable = turn;

	return GetSpecialDisable();
}

ei_s32 CrBattleCharacter::SubSpecialDisable(int sub)
{
	OnlyInfo.SpecialDisable -= sub;

	if(OnlyInfo.SpecialDisable < 0)
		OnlyInfo.SpecialDisable = 0;

	return GetSpecialDisable();
}

ei_s32 CrBattleCharacter::GetSpecialDisable(void)
{
	return OnlyInfo.SpecialDisable;
}

ei_s32 CrBattleCharacter::SpecialEnableUse(void)
{
	if(GetSpecialDisable())
		return 0;

	return CrCharacter::SpecialEnableUse();
}

ei_s32 CrBattleCharacter::GetEnableSpecial(void)
{
	if(GetSpecialDisable())
		return 0;

	return CrCharacter::GetEnableSpecial();
}

