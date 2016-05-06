//-------------------------------
//CrMaterial.h
//
#ifndef INCLUDE_CRMATERIAL_H

#define INCLUDE_CRMATERIAL_H

//---種類
#define CRMATERIAL_KIND_EMPTY 0
#define CRMATERIAL_KIND_ITEMCOUNT 1 //---アイテムの数
#define CRMATERIAL_KIND_ITEMVALUE 2 //---アイテムの値段
#define CRMATERIAL_KIND_ITEMKIND 3 //---アイテムの種類
#define CRMATERIAL_KIND_ITEMATACK 4 //---アイテムの攻撃力
#define CRMATERIAL_KIND_ITEMDEFENSE 5 //---アイテムの防御力
#define CRMATERIAL_KIND_ITEMACTION 6 //---アイテムの行動力
#define CRMATERIAL_KIND_ITEMHITPROB 7 //---アイテムの命中率
#define CRMATERIAL_KIND_ITEMAVOIDPROB 8 //---アイテムの回避率
#define CRMATERIAL_KIND_ITEMSELLVALUE 9 //---アイテムの売値

#define CRMATERIAL_KIND_NAME 51 
#define CRMATERIAL_KIND_INDEX 52

#define CRMATERIAL_KIND_MAGICLEVEL 101 
#define CRMATERIAL_KIND_MAGICSCENE 102 //---
#define CRMATERIAL_KIND_MAGICMC 103 //---
#define CRMATERIAL_KIND_MAGICELEMENT 104 //---

#define CRMATERIAL_MAGICLKIND_ATACK 1
#define CRMATERIAL_MAGICLKIND_RECOVERY 2
#define CRMATERIAL_MAGICLKIND_HELP 3

//---アイテム種類
#define CRMATERIAL_ITEMLKIND_ITEM 1
#define CRMATERIAL_ITEMLKIND_WEAPON 2
#define CRMATERIAL_ITEMLKIND_ARMOR 3
#define CRMATERIAL_ITEMLKIND_SHIELD 4
#define CRMATERIAL_ITEMLKIND_HELM 5
#define CRMATERIAL_ITEMLKIND_ACCESSORY 6

#define CRMATERIAL_ITEMKIND_ITEMMIN 1
	#define CRMATERIAL_ITEMKIND_MEDICINE 1 //---薬
	#define CRMATERIAL_ITEMKIND_BOOK 2 //---本
	#define CRMATERIAL_ITEMKIND_OHTER 3
#define CRMATERIAL_ITEMKIND_ITEMMAX 10

#define CRMATERIAL_ITEMKIND_WEAPONMIN 11
	#define CRMATERIAL_ITEMKIND_KNIFE 11
	#define CRMATERIAL_ITEMKIND_SMALLSWORD 12
	#define CRMATERIAL_ITEMKIND_MIDDLESWORD 13
	#define CRMATERIAL_ITEMKIND_LARGESWORD 14

	#define CRMATERIAL_ITEMKIND_GUN 21
	#define CRMATERIAL_ITEMKIND_SPGUN 22

	#define CRMATERIAL_ITEMKIND_OTHERWEAPON 29
#define CRMATERIAL_ITEMKIND_WEAPONMAX 30

//-------------------------------------------
#define CRMATERIAL_ITEMKIND_PROTECTORMIN 101

#define CRMATERIAL_ITEMKIND_ARMORMIN 101
	#define CRMATERIAL_ITEMKIND_SUIT 101
	#define CRMATERIAL_ITEMKIND_ARMOR 101
	#define CRMATERIAL_ITEMKIND_ROBE 101
#define CRMATERIAL_ITEMKIND_ARMORMAX 110

#define CRMATERIAL_ITEMKIND_SHIELDMIN 111
	#define CRMATERIAL_ITEMKIND_SMALLSHIELD 111
	#define CRMATERIAL_ITEMKIND_MIDDLESHIELD 112
#define CRMATERIAL_ITEMKIND_SHIELDMAX 120

#define CRMATERIAL_ITEMKIND_HELMETMIN 121
	#define CRMATERIAL_ITEMKIND_HELMET 121
	#define CRMATERIAL_ITEMKIND_HAT 122
#define CRMATERIAL_ITEMKIND_HELMETMAX 130

#define CRMATERIAL_ITEMKIND_PROTECTORMAX 140
//-------------------------------------------

#define CRMATERIAL_ITEMKIND_ACCESSORYMIN 141
	#define CRMATERIAL_ITEMKIND_ACCESSORY 141
#define CRMATERIAL_ITEMKIND_ACCESSORYMAX 150

//---ItemStatus
#define ITEMSTATUS_NOSELL 0x0001
#define ITEMSTATUS_NOSTRENGTH 0x0002

class CROBJECT_API CrMaterial : public CrObject
{
public:
	CrMaterial(void);
	~CrMaterial();

	virtual int KindOf(void);
	virtual int SizeOf(void);

	//---特定の値を得る
	virtual ei_s32 GetData(int kind);
	//---マテリアル内での種類
	virtual ei_s32 GetMaterialKind(void);

	CRESTEAJU_MATERIALINFO *GetMaterialInfo(void);
	eistr *GetName(void);
	eistr *GetKanaName(void);
	eistr *GetHelp(void);

	CRESTEAJU_MATERIALINFO MaterialInfo;

	//---派生クラス用
	union {
		CRESTEAJU_ITEMINFO ItemInfo;
		CRESTEAJU_MAGICINFO MagicInfo;
		CRESTEAJU_SPECIALINFO SpecialInfo;
	};
private:
};

class CROBJECT_API CrItem : public CrMaterial
{
public:
	CrItem(void);
	~CrItem();

	int KindOf(void);
	int SizeOf(void);

	//---特定の値を得る
	ei_s32 GetData(int kind);
	//---マテリアル内での種類
	ei_s32 GetMaterialKind(void);

	//---値を得る
	ei_s32 GetValue(void);
	ei_s32 GetKind(void);
	ei_s32 GetScene(void);
	ei_s32 GetItemStatus(void);
	ei_s32 GetElement(void);
	ei_s32 GetSpecial(void);

	//---
	ei_s32 GetDamageStatus(void);
	ei_s32 GetAtackKind(void);
	ei_s32 GetSound(void);
	ei_s32 GetAnime(void);
	//---アイテム能力
	ei_s32 GetAtack(void);
	ei_s32 GetDefense(void);
	ei_s32 GetAction(void);
	ei_s32 GetMagicDefense(void);
	//---
	ei_s32 GetRange(void);
	ei_s32 GetTarget(void);
	//--能力変化
	ei_s32 GetPower(void);
	ei_s32 GetVitality(void);
	ei_s32 GetAgility(void);
	ei_s32 GetSoul(void);
	ei_s32 GetMagic(void);
	//---装備・使用可能者
	ei_s32 CanEquip(int character);
	ei_s32 CanUse(int character);
	//---
	ei_s32 GetEquipStatus(void);
	ei_s32 GetFreeData(int number);
	//---
	ei_s32 GetHitProb(void);
	ei_s32 GetAvoidProb(void);
	ei_s32 GetMagicAvoidProb(void);
};

class CROBJECT_API CrMagic : public CrMaterial
{
public:
	CrMagic(void);
	~CrMagic();

	int KindOf(void);
	int SizeOf(void);

	//---特定の値を得る
	ei_s32 GetData(int kind);
	//---マテリアル内での種類
	ei_s32 GetMaterialKind(void);

	//---
	ei_s32 GetLevel(void);
	ei_s32 GetMC(void);
	ei_s32 GetElement(void);
	ei_s32 GetKind(void);
	ei_s32 GetDiffuse(void);
	ei_s32 GetScene(void);
	ei_s32 GetTarget(int mode);
	ei_s32 GetRange(int mode);
	ei_s32 GetDamage(void);
	ei_s32 GetSubDamage(void);
	ei_s32 GetHitProb(void);
	ei_s32 GetSpecial(void);
	ei_s32 GetFreeData(int number);
};


class CROBJECT_API CrSpecial : public CrMaterial
{
public:
	CrSpecial(void);
	~CrSpecial();

	int KindOf(void);
	int SizeOf(void);

	//---特定の値を得る
	ei_s32 GetData(int kind);
	//---マテリアル内での種類
	ei_s32 GetMaterialKind(void);

	//---
	ei_s32 GetNumber(void);
	ei_s32 GetCommandType(void);
	ei_s32 GetLevel(void);
	ei_s32 GetWho(void);
	ei_s32 GetEvent(void);
	ei_s32 GetWeaponKind(void);
	ei_s32 GetWeaponNumber(int number);
	ei_s32 GetDamage(void);
	ei_s32 GetUseMC(void);
	ei_s32 GetResultLP(void);
	ei_s32 GetResultMC(void);

	ei_s32 GetAtackCount(void);
	ei_s32 GetMagicCount(void);
	ei_s32 GetAvoidCount(void);
	ei_s32 GetDefenseCount(void);
	ei_s32 GetGiveMissCount(void);

	ei_s32 GetTarget(void);
	ei_s32 GetRange(void);

	ei_s32 GetDamageRate(void);
	ei_s32 GetSubDamageRate(void);
	ei_s32 GetSPAtackCount(void);
	ei_s32 GetDamageDiffuse(void);
	ei_s32 GetDisableTurn(void);
};

#endif /*INCLUDE_CRMATERIAL_H*/
