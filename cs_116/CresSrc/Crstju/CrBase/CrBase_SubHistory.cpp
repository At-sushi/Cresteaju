//---ƒqƒXƒgƒŠ[
CRBASE_API void crhistBattleCount(void)
{
	if(++pGameInfo->BattleCount > 99999999){
		pGameInfo->BattleCount = 99999999;
	}
}

CRBASE_API void crhistSubBattleCount(void)
{
	if(--pGameInfo->BattleCount < 0){
		pGameInfo->BattleCount = 0;
	}
}

CRBASE_API void crhistEscapeCount(void)
{
	if(++pGameInfo->EscapeCount > 99999999){
		pGameInfo->EscapeCount = 99999999;
	}
}

CRBASE_API void crhistAllGetMoney(int money)
{
	pGameInfo->AllGetMoney += money;
	if(++pGameInfo->AllGetMoney > 99999999){
		pGameInfo->AllGetMoney = 99999999;
	}
}

CRBASE_API void crhistAllGetExperience(int exp)
{
	pGameInfo->AllGetExperience += exp;
	if(++pGameInfo->AllGetExperience > 99999999){
		pGameInfo->AllGetExperience = 99999999;
	}
}

CRBASE_API void crhistSetHistory(int number)
{
	pGameInfo->PlayHistory[number].Level = pCharacterInfo[0].GetLevel();
	pGameInfo->PlayHistory[number].Hour = pGameInfo->PlayHours;
	pGameInfo->PlayHistory[number].Minute = pGameInfo->PlayMinutes;
	pGameInfo->PlayHistory[number].Second = pGameInfo->PlaySeconds;
}
