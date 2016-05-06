#define FILE_CRMATERIAL_SUBITEM

//--------------------------------------------------
//---アイテムクラス

CrItem::CrItem(void) : CrMaterial()
{
	eimemset(&ItemInfo,0,sizeof(ItemInfo));
}

CrItem::~CrItem()
{
}

//---種類
int CrItem::KindOf(void)
{
	return CROBJECT_ITEM;
}

//---サイズ
int CrItem::SizeOf(void)
{
	return sizeof(CROBJECT_ITEM);
}

ei_s32 CrItem::GetData(int kind)
{
	if(kind == CRMATERIAL_KIND_NAME)
		return (ei_s32)GetName();
	if(kind == CRMATERIAL_KIND_INDEX)
		return ItemInfo.Index;

	if(kind == CRMATERIAL_KIND_ITEMVALUE)
		return GetValue();
	if(kind == CRMATERIAL_KIND_ITEMKIND)
		return GetMaterialKind();

	if(kind == CRMATERIAL_KIND_ITEMATACK)
		return GetAtack();
	if(kind == CRMATERIAL_KIND_ITEMDEFENSE)
		return GetDefense();
	if(kind == CRMATERIAL_KIND_ITEMACTION)
		return GetAction();
	if(kind == CRMATERIAL_KIND_ITEMHITPROB)
		return GetHitProb();
	if(kind == CRMATERIAL_KIND_ITEMAVOIDPROB)
		return GetAvoidProb();

	return 0;
}

ei_s32 CrItem::GetMaterialKind(void)
{
	return ItemInfo.Kind;
}

//--------------------------------------------------
//---
ei_s32 CrItem::GetValue(void)
{
	return ItemInfo.Value;
}

ei_s32 CrItem::GetKind(void)
{
	return ItemInfo.Kind;
}

ei_s32 CrItem::GetScene(void)
{
	return ItemInfo.Scene;
}

ei_s32 CrItem::GetItemStatus(void)
{
	return ItemInfo.ItemStatus;
}

ei_s32 CrItem::GetElement(void)
{
	return ItemInfo.Element;
}

ei_s32 CrItem::GetSpecial(void)
{
	return ItemInfo.Special;
}

ei_s32 CrItem::GetAnime(void)
{
	return ItemInfo.Anime;
}
//--------------------------------------------------
ei_s32 CrItem::GetAtack(void)
{
	if(GetData(CRMATERIAL_KIND_INDEX) == 22){
		//---包丁－４９
		int value = pCrExeInfo->ExeRunningTime;

		if(value > 64800)
			value = 64800;
		value = (value / 900) * 3;
		return value;
	}

	return ItemInfo.Atack;
}

ei_s32 CrItem::GetDefense(void)
{
	return ItemInfo.Defense;
}

ei_s32 CrItem::GetAction(void)
{
	return ItemInfo.Action;
}

//--------------------------------------------------
ei_s32 CrItem::GetPower(void)
{
	return ItemInfo.Power;
}

ei_s32 CrItem::GetVitality(void)
{
	return ItemInfo.Vitality;
}

ei_s32 CrItem::GetAgility(void)
{
	return ItemInfo.Agility;
}

ei_s32 CrItem::GetSoul(void)
{
	return ItemInfo.Soul;
}

ei_s32 CrItem::GetMagic(void)
{
	return ItemInfo.Magic;
}

ei_s32 CrItem::GetMagicDefense(void)
{
	return ItemInfo.MagicDefense;
}

//--------------------------------------------------
//---ダメージステータス（力加算かどうか）
ei_s32 CrItem::GetDamageStatus(void)
{
	return ItemInfo.DamageStatus;
}

//---直接／間接
ei_s32 CrItem::GetAtackKind(void)
{
	return ItemInfo.AtackKind;
}

//---効果音
ei_s32 CrItem::GetSound(void)
{
	return ItemInfo.Sound;
}

//---ターゲット
ei_s32 CrItem::GetTarget(void)
{
	return ItemInfo.Target;
}

//---範囲
ei_s32 CrItem::GetRange(void)
{
	return ItemInfo.Range;
}

//--------------------------------------------------
//---装備可能か
ei_s32 CrItem::CanEquip(int character)
{
	character = 1 << (character - 1);

	if(ItemInfo.Equipment & character)
		return 1;

	return 0;
}

//---使用可能か
ei_s32 CrItem::CanUse(int character)
{
	character = 1 << character;

	if(ItemInfo.User & character)
		return 1;

	return 0;
}

//--------------------------------------------------
ei_s32 CrItem::GetHitProb(void)
{
	return ItemInfo.HitProb;
}

ei_s32 CrItem::GetAvoidProb(void)
{
	return ItemInfo.AvoidProb;
}

ei_s32 CrItem::GetMagicAvoidProb(void)
{
	return ItemInfo.MagicAvoidProb;
}

//---フリーデータ
ei_s32 CrItem::GetFreeData(int number)
{
	return ItemInfo.FreeData[number];
}
