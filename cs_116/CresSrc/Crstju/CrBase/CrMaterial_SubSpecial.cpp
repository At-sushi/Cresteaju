//--------------------------------------------------
//---魔法クラス

CrSpecial::CrSpecial(void) : CrMaterial()
{
	eimemset(&SpecialInfo,0,sizeof(SpecialInfo));
	SpecialInfo.Size = sizeof(SpecialInfo);
}

CrSpecial::~CrSpecial()
{
}

//---種類
int CrSpecial::KindOf(void)
{
	return CROBJECT_SPECIAL;
}

//---サイズ
int CrSpecial::SizeOf(void)
{
	return sizeof(CROBJECT_SPECIAL);
}

ei_s32 CrSpecial::GetData(int kind)
{
	if(kind == CRMATERIAL_KIND_NAME)
		return (ei_s32)GetName();
	return 0;
}

ei_s32 CrSpecial::GetMaterialKind(void)
{
	return 0;//MagicInfo.Element;
}

//--------------------------------------------------
ei_s32 CrSpecial::GetNumber(void)
{
	return SpecialInfo.Number;
}

ei_s32 CrSpecial::GetCommandType(void)
{
	return SpecialInfo.CommandType;
}

ei_s32 CrSpecial::GetLevel(void)
{
	return SpecialInfo.Level;
}

ei_s32 CrSpecial::GetWho(void)
{
	return SpecialInfo.Who;
}

ei_s32 CrSpecial::GetEvent(void)
{
	return SpecialInfo.Event;
}

ei_s32 CrSpecial::GetWeaponKind(void)
{
	return SpecialInfo.WeaponKind;
}

ei_s32 CrSpecial::GetWeaponNumber(int number)
{
	return SpecialInfo.WeaponNumber[number];
}

ei_s32 CrSpecial::GetDamage(void)
{
	return SpecialInfo.Damage;
}


ei_s32 CrSpecial::GetUseMC(void)
{
	return SpecialInfo.UseMC;
}

ei_s32 CrSpecial::GetResultLP(void)
{
	return SpecialInfo.ResultLP;
}

ei_s32 CrSpecial::GetResultMC(void)
{
	return SpecialInfo.ResultMC;
}

ei_s32 CrSpecial::GetAtackCount(void)
{
	return SpecialInfo.AtackCount;
}

ei_s32 CrSpecial::GetMagicCount(void)
{
	return SpecialInfo.MagicCount;
}

ei_s32 CrSpecial::GetAvoidCount(void)
{
	return SpecialInfo.AvoidCount;
}

ei_s32 CrSpecial::GetDefenseCount(void)
{
	return SpecialInfo.DefenseCount;
}

ei_s32 CrSpecial::GetGiveMissCount(void)
{
	return SpecialInfo.GiveMissCount;
}

ei_s32 CrSpecial::GetTarget(void)
{
	return SpecialInfo.Target;
}

ei_s32 CrSpecial::GetRange(void)
{
	return SpecialInfo.Range;
}


ei_s32 CrSpecial::GetDamageRate(void)
{
	return SpecialInfo.DamageRate;
}

ei_s32 CrSpecial::GetSubDamageRate(void)
{
	return SpecialInfo.SubDamageRate;
}

ei_s32 CrSpecial::GetSPAtackCount(void)
{
	return SpecialInfo.SPAtackCount;
}

ei_s32 CrSpecial::GetDamageDiffuse(void)
{
	return SpecialInfo.DamageDiffuse;
}

ei_s32 CrSpecial::GetDisableTurn(void)
{
	return SpecialInfo.DisableTurn;
}
