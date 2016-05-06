//--------------------------------------------------
//---魔法クラス

CrMagic::CrMagic(void) : CrMaterial()
{
	eimemset(&MagicInfo,0,sizeof(MagicInfo));
	MagicInfo.Size = sizeof(MagicInfo);
}

CrMagic::~CrMagic()
{
}

//---種類
int CrMagic::KindOf(void)
{
	return CROBJECT_MAGIC;
}

//---サイズ
int CrMagic::SizeOf(void)
{
	return sizeof(CROBJECT_MAGIC);
}

ei_s32 CrMagic::GetData(int kind)
{
	if(kind == CRMATERIAL_KIND_NAME)
		return (ei_s32)GetName();
	if(kind == CRMATERIAL_KIND_INDEX)
		return MagicInfo.Index;

	if(kind == CRMATERIAL_KIND_MAGICLEVEL)
		return MagicInfo.Level;
	if(kind == CRMATERIAL_KIND_MAGICSCENE)
		return MagicInfo.Scene;
	if(kind == CRMATERIAL_KIND_MAGICMC)
		return MagicInfo.UseMC;
	if(kind == CRMATERIAL_KIND_MAGICELEMENT)
		return MagicInfo.Element;

	return 0;
}

ei_s32 CrMagic::GetMaterialKind(void)
{
	return MagicInfo.Element;
}

//--------------------------------------------------
//---レベル
ei_s32 CrMagic::GetLevel(void)
{
	return MagicInfo.Level;
}

ei_s32 CrMagic::GetMC(void)
{
	return MagicInfo.UseMC;
}

//---魔法の種類
ei_s32 CrMagic::GetKind(void)
{
	return MagicInfo.Kind;
}

//---魔法の属性
ei_s32 CrMagic::GetElement(void)
{
	return MagicInfo.Element;
}

//---使用シーン
ei_s32 CrMagic::GetScene(void)
{
	return MagicInfo.Scene;
}

//---分散度
ei_s32 CrMagic::GetDiffuse(void)
{
	return MagicInfo.Diffuse;
}

//---基本ダメージ
ei_s32 CrMagic::GetDamage(void)
{
	return MagicInfo.Damage;
}

//---補助ダメージ
ei_s32 CrMagic::GetSubDamage(void)
{
	return MagicInfo.SubDamage;
}

ei_s32 CrMagic::GetHitProb(void)
{
	return MagicInfo.HitProb;
}

ei_s32 CrMagic::GetSpecial(void)
{
	return MagicInfo.Special;
}

ei_s32 CrMagic::GetFreeData(int number)
{
	return MagicInfo.FreeData[number];
}

ei_s32 CrMagic::GetTarget(int mode)
{
	return MagicInfo.Target[mode];
}

ei_s32 CrMagic::GetRange(int mode)
{
	return MagicInfo.Range[mode];
}
