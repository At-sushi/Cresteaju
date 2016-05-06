//---バトルヒストリー

//---スペシャルヒストリークリア
void CrCharacter::SpecialClearHistory(void)
{
	memset(&CharaInfo.SpecialHistory,0,sizeof(CharaInfo.SpecialHistory));
}

//---必殺技が使用可能かどうか、可能ならそのナンバーを返す
ei_s32 CrCharacter::SpecialEnableUse(void)
{
	if(GetEnableSpecial())
		return 1;

	return 0;
}

//---使用可能な必殺技のインデックスを返す
ei_s32 CrCharacter::GetEnableSpecial(void)
{
	int a,b,c,index = 0,flag,double_gun = 0;
	CrSpecial *psp = &pSpecialInfo[1];

	if(GetWeapon(0)){
		if(pItemInfo[GetWeapon(0)].GetAtackKind() == 1){
			if(GetWeapon(1)){
				if(pItemInfo[GetWeapon(1)].GetAtackKind() == 1){
					double_gun = 1;
				}
			}
		}
	}

//	char s[80];
	for(a = 1;a < SPECIALMATERIAL_MAX;a ++,psp ++){
		flag = 1;

		//---空インデックスだったら
		if(*(psp->GetName()) == NULL){
			continue;
		}

		if(psp->GetWho() != Who()){
			flag = 0;
		}

		if(GetLevel() < psp->GetLevel() && psp->GetLevel()){
			flag = 0; 
		}
		if(pGameInfo->Event[psp->GetEvent()] == 0 && psp->GetEvent()){
			flag = 0;
		}

		if(psp->GetWeaponKind() == 3){
			//---ダブルガン
			if(double_gun == 0)
				flag = 0;
		} else if(psp->GetWeaponKind()){
			//---剣
			for(b = 0,c = 0;b < 2;b ++){
				if(GetWeapon(b)){
					if(pItemInfo[GetWeapon(b)].GetAtackKind() == psp->GetWeaponKind() - 1)
						c = 1;
				}
			}
			if(c == 0){
				flag = 0;
			}
		}

		//---ダメージ
		if(GetMaxLP()){
			if(SpecialGetReceiveDamage() * 1000 / GetMaxLP() < psp->GetDamage()
				&& psp->GetDamage()){
				flag = 0;
			}
		}
		//---使用ＭＣ
		if(GetMaxMC()){
			if(SpecialGetUseMC() * 1000 / GetMaxMC() < psp->GetUseMC()
				&& psp->GetUseMC()){
				flag = 0;
			}
		}
		//---残りＬＰ
		if(GetMaxLP()){
			if(GetLP()  * 1000 / GetMaxLP() > psp->GetResultLP()
				&& psp->GetResultLP()){
				flag = 0;
			}
		}
		//---残りＭＣ
		if(GetMaxMC()){
			if(GetMC() * 1000 / GetMaxMC() > psp->GetResultMC()
				&& psp->GetResultMC()){
				flag = 0;
			}
		}

		//---攻撃回数
		if(SpecialHistoryGetAction(BTHISTORY_WEAPON) < psp->GetAtackCount()
			&& psp->GetAtackCount()){
			flag = 0;
		}
		//---魔法回数
		if(SpecialHistoryGetAction(BTHISTORY_MAGIC) < psp->GetMagicCount()
			&& psp->GetMagicCount()){
			flag = 0;
		}
		//---回避回数
		if(SpecialGetReceiveMissCount() < psp->GetAvoidCount()
			&& psp->GetAvoidCount()){
			flag = 0;
		}
		//---防御回数
		if(SpecialHistoryGetAction(BTHISTORY_DEFENSE) < psp->GetDefenseCount()
			&& psp->GetDefenseCount()){
			flag = 0;
		}
		//---与えたミス回数
		if(SpecialGetGiveMissCount() < psp->GetGiveMissCount()
			&& psp->GetGiveMissCount()){
			flag = 0;
		}

		//---使用可能！
		if(flag == 1){
			index = a;
		}
	}

	return index;
}

#define HIST_MAX 999999999

void CrCharacter::HistoryAddAction(int action)
{
	if(CharaInfo.BattleHistory.ActionCount < HIST_MAX)
		CharaInfo.BattleHistory.ActionCount ++;
	if(CharaInfo.SpecialHistory.ActionCount < HIST_MAX)
		CharaInfo.SpecialHistory.ActionCount ++;

	switch(action){
	case BTHISTORY_WEAPON:
		if(CharaInfo.BattleHistory.WeaponCount < HIST_MAX)
			CharaInfo.BattleHistory.WeaponCount ++;
		if(CharaInfo.SpecialHistory.WeaponCount < HIST_MAX)
			CharaInfo.SpecialHistory.WeaponCount ++;
		break;

	case BTHISTORY_MAGIC:
		if(CharaInfo.BattleHistory.MagicCount < HIST_MAX)
			CharaInfo.BattleHistory.MagicCount ++;
		if(CharaInfo.SpecialHistory.MagicCount < HIST_MAX)
			CharaInfo.SpecialHistory.MagicCount ++;
		break;

	case BTHISTORY_DEFENSE:
		if(CharaInfo.BattleHistory.DefenseCount < HIST_MAX)
			CharaInfo.BattleHistory.DefenseCount ++;
		if(CharaInfo.SpecialHistory.DefenseCount < HIST_MAX)
			CharaInfo.SpecialHistory.DefenseCount ++;
		break;

	case BTHISTORY_ITEM:
		if(CharaInfo.BattleHistory.ItemCount < HIST_MAX)
			CharaInfo.BattleHistory.ItemCount ++;
		if(CharaInfo.SpecialHistory.ItemCount < HIST_MAX)
			CharaInfo.SpecialHistory.ItemCount ++;
		break;

	case BTHISTORY_SPECIAL:
		if(CharaInfo.BattleHistory.SpecialCount < HIST_MAX)
			CharaInfo.BattleHistory.SpecialCount ++;
		if(CharaInfo.SpecialHistory.SpecialCount < HIST_MAX)
			CharaInfo.SpecialHistory.SpecialCount ++;
		break;
	default:
		break;
	}
}

ei_s32 CrCharacter::HistoryGetAction(int action)
{
	int data = 0;

	switch(action){
	case BTHISTORY_ACTION:
	data = CharaInfo.BattleHistory.ActionCount;
		break;
	case BTHISTORY_WEAPON:
	data = CharaInfo.BattleHistory.WeaponCount;
		break;
	case BTHISTORY_MAGIC:
	data = CharaInfo.BattleHistory.MagicCount;
		break;
	case BTHISTORY_DEFENSE:
	data = CharaInfo.BattleHistory.DefenseCount;
		break;
	case BTHISTORY_ITEM:
	data = CharaInfo.BattleHistory.ItemCount;
		break;
	case BTHISTORY_SPECIAL:
	data = CharaInfo.BattleHistory.SpecialCount;
		break;
	default:
		break;
	}
	return data;
}

ei_s32 CrCharacter::SpecialHistoryGetAction(int action)
{
	int data = 0;

	switch(action){
	case BTHISTORY_ACTION:
	data = CharaInfo.SpecialHistory.ActionCount;
		break;
	case BTHISTORY_WEAPON:
	data = CharaInfo.SpecialHistory.WeaponCount;
		break;
	case BTHISTORY_MAGIC:
	data = CharaInfo.SpecialHistory.MagicCount;
		break;
	case BTHISTORY_DEFENSE:
	data = CharaInfo.SpecialHistory.DefenseCount;
		break;
	case BTHISTORY_ITEM:
	data = CharaInfo.SpecialHistory.ItemCount;
		break;
	case BTHISTORY_SPECIAL:
	data = CharaInfo.SpecialHistory.SpecialCount;
		break;
	default:
		break;
	}
	return data;
}


void CrCharacter::HistoryAddDeathCount(void)
{
	if(CharaInfo.BattleHistory.DeathCount < HIST_MAX)
		CharaInfo.BattleHistory.DeathCount ++;
	if(CharaInfo.SpecialHistory.DeathCount < HIST_MAX)
		CharaInfo.SpecialHistory.DeathCount ++;
}

ei_s32 CrCharacter::HistoryGetDeathCount(void)
{
	return CharaInfo.BattleHistory.DeathCount;
}

ei_s32 CrCharacter::SpecialGetDeathCount(void)
{
	return CharaInfo.SpecialHistory.DeathCount;
}

void CrCharacter::HistoryAddGiveDamage(int damage)
{
	if(CharaInfo.BattleHistory.GiveDamage < HIST_MAX)
		CharaInfo.BattleHistory.GiveDamage += damage;
	if(CharaInfo.BattleHistory.GiveDamage > HIST_MAX)
		CharaInfo.BattleHistory.GiveDamage = HIST_MAX;

	if(CharaInfo.SpecialHistory.GiveDamage < HIST_MAX)
		CharaInfo.SpecialHistory.GiveDamage += damage;
	if(CharaInfo.SpecialHistory.GiveDamage > HIST_MAX)
		CharaInfo.SpecialHistory.GiveDamage = HIST_MAX;
}

ei_s32 CrCharacter::HistoryGetGiveDamage(void)
{
	return CharaInfo.BattleHistory.GiveDamage;
}

ei_s32 CrCharacter::SpecialGetGiveDamage(void)
{
	return CharaInfo.SpecialHistory.GiveDamage;
}

void CrCharacter::HistoryAddReceiveDamage(int damage)
{
	if(CharaInfo.BattleHistory.ReceiveDamage < HIST_MAX)
		CharaInfo.BattleHistory.ReceiveDamage += damage;
	if(CharaInfo.BattleHistory.ReceiveDamage > HIST_MAX)
		CharaInfo.BattleHistory.ReceiveDamage = HIST_MAX;

	if(CharaInfo.SpecialHistory.ReceiveDamage < HIST_MAX)
		CharaInfo.SpecialHistory.ReceiveDamage += damage;
	if(CharaInfo.SpecialHistory.ReceiveDamage > HIST_MAX)
		CharaInfo.SpecialHistory.ReceiveDamage = HIST_MAX;
}

ei_s32 CrCharacter::HistoryGetReceiveDamage(void)
{
	return CharaInfo.BattleHistory.ReceiveDamage;
}

ei_s32 CrCharacter::SpecialGetReceiveDamage(void)
{
	return CharaInfo.SpecialHistory.ReceiveDamage;
}

void CrCharacter::HistoryAddUseMC(int count)
{
//	CharaInfo.BattleHistory.UseMC += count;
	CharaInfo.SpecialHistory.UseMC += count;
	if(CharaInfo.SpecialHistory.UseMC > HIST_MAX)
		CharaInfo.SpecialHistory.UseMC = HIST_MAX;
}

ei_s32 CrCharacter::HistoryGetUseMC(void)
{
	return CharaInfo.BattleHistory.UseMC;
}

ei_s32 CrCharacter::SpecialGetUseMC(void)
{
	return CharaInfo.SpecialHistory.UseMC;
}

void CrCharacter::HistoryAddDestroyMC(int count)
{
	CharaInfo.BattleHistory.UseMC += count;
	if(CharaInfo.BattleHistory.UseMC > HIST_MAX)
		CharaInfo.BattleHistory.UseMC = HIST_MAX;
}

ei_s32 CrCharacter::HistoryGetDestroyMC(void)
{
	return CharaInfo.BattleHistory.UseMC;
}

void CrCharacter::HistoryAddEnemyCount(int count)
{
	CharaInfo.BattleHistory.EnemyCount += count;
	if(CharaInfo.BattleHistory.EnemyCount > HIST_MAX)
		CharaInfo.BattleHistory.EnemyCount = HIST_MAX;

	CharaInfo.SpecialHistory.EnemyCount += count;
	if(CharaInfo.SpecialHistory.EnemyCount > HIST_MAX)
		CharaInfo.SpecialHistory.EnemyCount = HIST_MAX;
}

ei_s32 CrCharacter::HistoryGetEnemyCount(void)
{
	return CharaInfo.BattleHistory.EnemyCount;
}

ei_s32 CrCharacter::SpecialGetEnemyCount(void)
{
	return CharaInfo.SpecialHistory.EnemyCount;
}

void CrCharacter::HistoryAddFinishEnemyCount(int count)
{
	CharaInfo.BattleHistory.FinishEnemyCount += count;
	if(CharaInfo.BattleHistory.FinishEnemyCount > HIST_MAX)
		CharaInfo.BattleHistory.FinishEnemyCount = HIST_MAX;

	CharaInfo.SpecialHistory.FinishEnemyCount += count;
	if(CharaInfo.SpecialHistory.FinishEnemyCount > HIST_MAX)
		CharaInfo.SpecialHistory.FinishEnemyCount = HIST_MAX;
}

ei_s32 CrCharacter::HistoryGetFinishEnemyCount(void)
{
	return CharaInfo.BattleHistory.FinishEnemyCount;
}

ei_s32 CrCharacter::SpecialGetFinishEnemyCount(void)
{
	return CharaInfo.SpecialHistory.FinishEnemyCount;
}

void CrCharacter::HistoryAddGiveMissCount(int count)
{
	CharaInfo.BattleHistory.GiveMissCount += count;
	if(CharaInfo.BattleHistory.GiveMissCount > HIST_MAX)
		CharaInfo.BattleHistory.GiveMissCount = HIST_MAX;

	CharaInfo.SpecialHistory.GiveMissCount += count;
	if(CharaInfo.SpecialHistory.GiveMissCount > HIST_MAX)
		CharaInfo.SpecialHistory.GiveMissCount = HIST_MAX;
}

ei_s32 CrCharacter::HistoryGetGiveMissCount(void)
{
	return CharaInfo.BattleHistory.GiveMissCount;
}

ei_s32 CrCharacter::SpecialGetGiveMissCount(void)
{
	return CharaInfo.SpecialHistory.GiveMissCount;
}


void CrCharacter::HistoryAddReceiveMissCount(int count)
{
	CharaInfo.BattleHistory.ReceiveMissCount += count;
	if(CharaInfo.BattleHistory.ReceiveMissCount > HIST_MAX)
		CharaInfo.BattleHistory.ReceiveMissCount = HIST_MAX;

	CharaInfo.SpecialHistory.ReceiveMissCount += count;
	if(CharaInfo.SpecialHistory.ReceiveMissCount > HIST_MAX)
		CharaInfo.SpecialHistory.ReceiveMissCount = HIST_MAX;
}

ei_s32 CrCharacter::HistoryGetReceiveMissCount(void)
{
	return CharaInfo.BattleHistory.ReceiveMissCount;
}

ei_s32 CrCharacter::SpecialGetReceiveMissCount(void)
{
	return CharaInfo.SpecialHistory.ReceiveMissCount;
}

