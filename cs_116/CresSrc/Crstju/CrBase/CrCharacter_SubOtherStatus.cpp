//--------------------------------------------
//---
ei_s32 CrCharacter::GetLevel(void)
{
	return CharaInfo.level;
}

ei_s32 CrCharacter::GetExperience(void)
{
	return CharaInfo.experience;
}

//---次のレベルまでの経験値
ei_s32 CrCharacter::GetNextExperience(int sub /* = 0*/)
{
	int level = GetLevel() + sub;
	int experience = pGameUsingData->LevelUpExperience[level];

	//---レベルが最高なら
	if(level >= 99)
		return 0;
	if(level > 40)
		level = 40;
	if(level < 1)
		level = 1;

	//---キャラクターごとの特性
	double temp_exp = experience;

	temp_exp = temp_exp
		* ((double)pGameUsingData->CharacterRateExperienceStart[Who()] * (double)(40 - level)
		+ (double)pGameUsingData->CharacterRateExperienceEnd[Who()] * (double)level)
		/ (double)(100 * 40);
	experience = (int)temp_exp;
/*
	experience = experience
		* (pGameUsingData->CharacterRateExperienceStart[Who()] * (40 - level)
		+ pGameUsingData->CharacterRateExperienceEnd[Who()] * level)
		/ (100 * 40);

	char s[80];
	sprintf(s,"%d,%d",GetExperience(),experience);
	eiMsgBox(s);
*/
	experience = experience - GetExperience();

	if(experience < 0)
		experience = 0;

	return experience;
}

//---魔法修得値
ei_s32 CrCharacter::GetMagicExperience(void)
{
	return CharaInfo.magic_experience;
}

ei_s32 CrCharacter::AddLevel(int level)
{
	return AddStatus(level,&CharaInfo.level,&LevelMax,&Zero);
}

ei_s32 CrCharacter::AddExperience(int experience)
{
	return AddStatus(experience,&CharaInfo.experience,&ExperienceMax,&Zero);
}

ei_s32 CrCharacter::SetExperience(int experience)
{
	ei_s32 old = GetExperience();

	CharaInfo.experience = experience;

	return old;
}

ei_s32 CrCharacter::AddMagicExperience(int experience)
{
	return AddStatus(experience,&CharaInfo.magic_experience,&MagicExpMax,&Zero);
}

//---
ei_s32 CrCharacter::GetPower(void)
{
	return CharaInfo.power;
}

ei_s32 CrCharacter::GetAgility(void)
{
	return CharaInfo.agility;
}

ei_s32 CrCharacter::GetVitality(void)
{
	return CharaInfo.vitality;
}

ei_s32 CrCharacter::GetSoul(void)
{
	return CharaInfo.soul;
}

ei_s32 CrCharacter::GetMagic(void)
{
	return CharaInfo.magic;
}

ei_s32 CrCharacter::GetMagicDefense(void)
{
	return CharaInfo.magic_defense;
}

ei_s32 CrCharacter::GetSubHitProb(void)
{
	return CharaInfo.sub_hit_prob;
}

//---レベルアップ
ei_s32 CrCharacter::SetLevelLP(void)
{
	int new_st;

	//---特性計算
	new_st = pGameUsingData->LevelUpLP[GetLevel()];
	new_st = (new_st * pGameUsingData->CharacterRateLP[Who()] + 50) / 100;
	CharaInfo.max_lp = new_st;

	return GetLP();
}

ei_s32 CrCharacter::SetLevelMC(void)
{
	int new_st;

	//---特性計算
	new_st = pGameUsingData->LevelUpMC[GetLevel()];
	new_st = ((int)((double)new_st * 1.10 + 0.50)* pGameUsingData->CharacterRateMC[Who()] + 50) / 100;
	CharaInfo.max_mc = new_st;

	return GetMC();
}

ei_s32 CrCharacter::SetLevelPower(void)
{
	int new_st;

	//---特性計算
	new_st = pGameUsingData->LevelUpStatus[GetLevel()];
	new_st = (new_st * pGameUsingData->CharacterRatePower[Who()] + 50) / 100;
	CharaInfo.power = new_st;

	return GetPower();
}

ei_s32 CrCharacter::SetLevelVitality(void)
{
	int new_st;

	//---特性計算
	new_st = pGameUsingData->LevelUpStatus[GetLevel()];
	new_st = ((int)((double)new_st * 0.50 + 0.50) * pGameUsingData->CharacterRateVitality[Who()] + 50) / 100;
	CharaInfo.vitality = new_st;

	return GetVitality();
}

ei_s32 CrCharacter::SetLevelAgility(void)
{
	int new_st;

	new_st = pGameUsingData->LevelUpStatus[GetLevel()];
	new_st = (new_st * pGameUsingData->CharacterRateAgility[Who()] + 50) / 100;
	CharaInfo.agility = new_st;

	return GetAgility();
}

ei_s32 CrCharacter::SetLevelSoul(void)
{
	int new_st;

	new_st = pGameUsingData->LevelUpStatus[GetLevel()];
	new_st = (new_st * pGameUsingData->CharacterRateSoul[Who()] + 50) / 100;
	CharaInfo.soul = new_st;

	return GetSoul();
}

ei_s32 CrCharacter::SetLevelMagic(void)
{
	int new_st;

	new_st = pGameUsingData->LevelUpStatus[GetLevel()];
	new_st = (new_st * pGameUsingData->CharacterRateMagic[Who()] + 50)/ 100;
	CharaInfo.magic = new_st;
	
	return GetMagic();
}

ei_s32 CrCharacter::SetLevelMagicExperience(int prev /* = -1*/)
{
	int new_st,level;

	if(prev == -1)
		level = GetLevel();
	else
		level = prev;

	new_st = pGameUsingData->LevelUpMagicExp[level];
	new_st = (new_st * pGameUsingData->CharacterRateMagicExp[Who()] + 50)/ 100;
	CharaInfo.magic_experience += new_st;

	if(prev != -1 && prev != GetLevel() - 1){
		SetLevelMagicExperience(prev + 1);
	}

	return GetMagicExperience();
}

//---このレベルの経験値
ei_s32 CrCharacter::SetLevelExperience(int prev /*= -1*/)
{
	AddExperience(GetNextExperience(-1));

	return GetExperience();
}

//-------------------------------------------------
ei_s32 CharaLerningMagic[PLAYERNAME_MAX][ELEMENT_MAX] = 
{
	//---無属性、回復、補助、火、水、土、風、雷
	//---ルナン
	{6,3,4,		5,4,5,5,5},
	//---ディザ
	{0,0,2,		5,0,3,0,3},
	//---ナック
	{0,6,6,		0,5,5,4,4},
	//---サヴィアー
	{0,0,5,		3,3,0,5,5},
	//---ユミ
	{0,0,4,		5,5,3,3,3},
	//---ライゼル
	{0,0,0,		0,0,0,0,0},
	//---シンディ
	{0,2,3,		3,3,5,3,3},
};

//---この属性のこのレベルの魔法を修得可能か？
ei_s32 CrCharacter::EnableLearningMagic(int element,int level)
{
	int value = CharaLerningMagic[Who() - 1][element - 1];

	if(level <= value)
		return 1;
	return 0;
}

//---攻撃魔法の威力
ei_s32 CrCharacter::GetMagicRate(int level)
{
	int rate,clevel = GetLevel(),master_level;

	level --;
	if(level < 0)
		level = 0;
	if(level >= 5)
		level = 5;

	master_level = pGameUsingData->Character100perMagicLevel[level];

	//---マスターレベル以上だったら１００％の威力
	if(master_level <= clevel)
		return 1000;

	rate = (clevel) * 1000 / master_level;

	return rate;
}
