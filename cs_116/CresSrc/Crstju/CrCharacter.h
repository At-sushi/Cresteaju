//-------------------------------
//CrCharacter.h
//
#ifndef INCLUDE_CRCHARACTER_H

#define INCLUDE_CRCHARACTER_H


class CROBJECT_API CrCharacter:public CrObject
{
public:
	CrCharacter(void);
	~CrCharacter();

	int KindOf(void);

	CRESTEAJU_CHARACTERINFO *GetCharacterInfo(void);
	CRESTEAJU_CHARACTER_BATTLEINFO *GetCharacterBattleHistory(void);

	//---
	int Who(void);
	void SetWho(int num);
	//---
	eistr *GetName(void);

	//---
	CRWIN_SELECTINFO *GetMagicBattleCursor(void);
	CRWIN_SELECTINFO *GetMagicFieldCursor(void);

	ei_s32 SetProtect(int flag);
	ei_s32 IsProtected(void);

	//---magic
	ei_s32 GetMagic(int index); //---インデックスの魔法を返す
	int HaveMagic(int number); //---numberの魔法を所持しているか
	int CanUseMagic(int number); //---魔法を使えるか
	void AddMagic(int number);//---魔法を覚える
	int HaveMagicElement(int element);//---同じ属性の魔法を何個覚えているか
	ei_s32 EnableLearningMagic(int element,int level);//---属性・レベルで修得可能か判断

	void SetLastUsingMagic(void);
	void CountSinceUsingMagic(int count);
	
	//---equipment
	ei_s32 GetEquipment(int number);
	void SetEquipment(int number,int item);
	ei_s32 GetWeapon(int number);
	ei_s32 IsWeaponEnableToAtack(int number,int mode);
	ei_s32 GetAnotherWeapon(int item_number,int dumy);
	ei_s32 GetAnotherWeapon(int number);
	void SetWeapon(int number,int item);
	ei_s32 GetProtector(int number);
	void SetProtector(int number,int item);
	ei_s32 GetAccessory(int number);
	void SetAccessory(int number,int item);

	//---
	ei_s32 CalcAtack(CrItem *pItem);
	//---after equipment
	ei_s32 GetEqAtack(int number);
	ei_s32 GetEqDefense(void);
	ei_s32 GetEqMagicDefense(void);
	ei_s32 GetEqAction(void);

	ei_s32 GetEqPower(void);
	ei_s32 GetEqVitality(void);
	ei_s32 GetEqAgility(void);
	ei_s32 GetEqSoul(void);
	ei_s32 GetEqMagic(void);

	ei_s32 GetEqHitProb(int number);
	ei_s32 GetEqSubHitProb(void);
	ei_s32 GetEqAvoidProb(void);
	ei_s32 GetEqMagicAvoidProb(void);

	//---LevelUp...
	ei_s32 SetLevelLP(void);
	ei_s32 SetLevelMC(void);
	ei_s32 SetLevelPower(void);
	ei_s32 SetLevelVitality(void);
	ei_s32 SetLevelAgility(void);
	ei_s32 SetLevelSoul(void);
	ei_s32 SetLevelMagic(void);
	ei_s32 SetLevelMagicExperience(int prev = -1);
	ei_s32 SetLevelExperience(int prev = -1);

	ei_s32 AddLevel(int level);
	ei_s32 AddExperience(int experience);
	ei_s32 SetExperience(int experience);
	ei_s32 AddMagicExperience(int experience);

	//---Status
	ei_s32 GetLevel(void);
	ei_s32 GetExperience(void);
	ei_s32 GetNextExperience(int sub = 0);
	ei_s32 GetMagicExperience(void);
	ei_s32 GetMagicRate(int level);
	//---
	ei_s32 GetPower(void);
	ei_s32 GetAgility(void);
	ei_s32 GetVitality(void);
	ei_s32 GetSoul(void);
	ei_s32 GetMagic(void);
	ei_s32 GetMagicDefense(void);

	ei_s32 GetSubHitProb(void);


	//---LP,SP,MC
	void SetLP(ei_s32 value);
	void SetMC(ei_s32 value);
	void SetBalance(ei_s32 value);
	void SetMaxLP(ei_s32 value);
	void SetMaxMC(ei_s32 value);
//	void SetMaxBalance(ei_s32 value);
	ei_s32 AddLP(ei_s32 value);
	ei_s32 AddMC(ei_s32 value);
	ei_s32 AddBalance(ei_s32 value);
	ei_s32 AddMaxLP(ei_s32 value);
	ei_s32 AddMaxMC(ei_s32 value);
//	ei_s32 AddMaxBalance(ei_s32 value);
	ei_s32 GetLP(void);
	ei_s32 GetMC(void);
	ei_s32 GetBalance(void);
	ei_s32 GetMaxLP(void);
	ei_s32 GetMaxMC(void);
	//---
	ei_s32 GetMaxBalance(void);
	ei_s32 GetMaxBalanceBody(void);
	ei_s32 GetMaxBalanceSoul(void);

	//---
	ei_s32 AddStatus(ei_s32 add,ei_s32 *value,ei_s32 *max_value,ei_s32 *min_value);

	//---BattleField
	void SetBattleFieldStartPos(ei_s32 x,ei_s32 y);
	ei_s32 GetBattleFieldStartX(void);
	ei_s32 GetBattleFieldStartY(void);
	eistr *GetBattleFileName(void);

	//---BattleHistory
	void HistoryAddAction(int action);//---一回行動した
	ei_s32 HistoryGetAction(int action);//---行動回数取得
	ei_s32 SpecialHistoryGetAction(int action);//---必殺技用

	void HistoryAddDeathCount(void);
	ei_s32 HistoryGetDeathCount(void);
	ei_s32 SpecialGetDeathCount(void);

	void HistoryAddGiveDamage(int damage);
	ei_s32 HistoryGetGiveDamage(void);
	ei_s32 SpecialGetGiveDamage(void);

	void HistoryAddReceiveDamage(int damage);
	ei_s32 HistoryGetReceiveDamage(void);
	ei_s32 SpecialGetReceiveDamage(void);

	void HistoryAddEnemyCount(int count);
	ei_s32 HistoryGetEnemyCount(void);
	ei_s32 SpecialGetEnemyCount(void);

	void HistoryAddFinishEnemyCount(int count);
	ei_s32 HistoryGetFinishEnemyCount(void);
	ei_s32 SpecialGetFinishEnemyCount(void);

	void SpecialClearHistory(void);
	ei_s32 SpecialEnableUse(void);
	ei_s32 GetEnableSpecial(void);

	void HistoryAddGiveMissCount(int count);
	ei_s32 HistoryGetGiveMissCount(void);
	ei_s32 SpecialGetGiveMissCount(void);

	void HistoryAddReceiveMissCount(int count);
	ei_s32 HistoryGetReceiveMissCount(void);
	ei_s32 SpecialGetReceiveMissCount(void);

	void HistoryAddRealAvoidCount(int count);
	ei_s32 HistoryGetRealAvoidCount(void);
	ei_s32 SpecialGetRealAvoidCount(void);

	void HistoryAddMagicAvoidCount(int count);
	ei_s32 HistoryGetMagicAvoidCount(void);
	ei_s32 SpecialGetMagicAvoidCount(void);

	void HistoryAddUseMC(int count);
	ei_s32 HistoryGetUseMC(void);
	ei_s32 SpecialGetUseMC(void);

	void HistoryAddDestroyMC(int count);
	ei_s32 HistoryGetDestroyMC(void);

	//---フィールドＭＣ
	void SetDisableMCCount(int count);
	void SubDisableMCCount(void);
	ei_s32 GetDisableMCCount(void);
	ei_s32 AddDeltaMC(int delta);
	void SetDeltaMC(int delta);
	ei_s32 GetDeltaMC(void);

	CRESTEAJU_CHARACTERINFO CharaInfo;
//	CRESTEAJU_CHARACTER_BATTLEINFO BattleHistory;

private:
	/*static*/ ei_s32 LPMaxStatus,LPMinStatus,
		BalanceMaxStatus,BalanceMinStatus,
			LevelMax,ExperienceMax,MagicExpMax,Zero;
};

#endif /*INCLUDE_CRCHARACTER_H*/
