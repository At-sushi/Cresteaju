//----------------------------------------------
//---装備能力
ei_s32 CrCharacter::GetEqAtack(int number)
{
/*	int a,value = GetPower();

	for(a = 0;a < EQ_ALL_MAX;a ++){
		value += pItemInfo[GetEquipment(a)].GetAtack();
	}*/

	int value = 0;
	CrItem *pItem = &pItemInfo[GetEquipment(number)];

	if(pItem != NULL){
		if(pItem->GetDamageStatus() == 0){
			//---直接武器
			value = GetPower() + pItem->GetAtack();
		} else {
			//---間接武器
			value = pItem->GetAtack();
		}
		//value = CalcAtack(&pItemInfo[GetEquipment(number)]);
	}

	if(value < 0)
		value = 0;

	return value;
}

ei_s32 CrCharacter::GetEqDefense(void)
{
	int a,value = GetVitality();

	for(a = 0;a < EQ_ALL_MAX;a ++){
		value += pItemInfo[GetEquipment(a)].GetDefense();
	}

	if(value < 0)
		value = 0;

	return value;
}

ei_s32 CrCharacter::GetEqMagicDefense(void)
{
	int a,value = 0;

	for(a = 0;a < EQ_ALL_MAX;a ++){
		value += pItemInfo[GetEquipment(a)].GetMagicDefense();
	}

	if(value < 0)
		value = 0;

	return value;
}

ei_s32 CrCharacter::GetEqAction(void)
{
	int a,value = GetAgility(),rate;

	for(a = 0,rate = 0;a < EQ_ALL_MAX;a ++){
//		value += pItemInfo[GetEquipment(a)].GetAction();
		rate += pItemInfo[GetEquipment(a)].GetAction();
	}

	value = GetAgility() + (GetAgility() * rate / 1000);

	if(value < 0)
		value = 0;

	return value;
}

ei_s32 CrCharacter::GetEqPower(void)
{
	int a,value = GetPower();

	for(a = 0;a < EQ_ALL_MAX;a ++){
		value += pItemInfo[GetEquipment(a)].GetPower();
	}

	if(value < 0)
		value = 0;

	return value;
}

ei_s32 CrCharacter::GetEqVitality(void)
{
	return GetVitality();;
}

ei_s32 CrCharacter::GetEqAgility(void)
{
	return GetAgility();
}

ei_s32 CrCharacter::GetEqSoul(void)
{
	int a,value = GetSoul();

	for(a = 0;a < EQ_ALL_MAX;a ++){
		value += pItemInfo[GetEquipment(a)].GetSoul();
	}

	if(value < 0)
		value = 0;

	return value;
}

ei_s32 CrCharacter::GetEqMagic(void)
{
	int a,value = GetMagic();

	for(a = 0;a < EQ_ALL_MAX;a ++){
		value += pItemInfo[GetEquipment(a)].GetMagic();
	}

	if(value < 0)
		value = 0;

	return value;
}

//---確率
ei_s32 CrCharacter::GetEqHitProb(int number)
{
	int value = 0;

	//---強制値があれば
	if(CharaInfo.force_HitProb)
		return CharaInfo.force_HitProb;

	if(GetWeapon(number)){
//		value = pItemInfo[GetWeapon(number)].GetAvoidProb();
		value = pItemInfo[GetWeapon(number)].GetHitProb();
	} else {
		//---武器無しの場合
		value = 500;
	}

	if(value > 1000)
		value = 1000;
	if(value < 0)
		value = 0;

	return value;
}

//---命中補正率
ei_s32 CrCharacter::GetEqSubHitProb(void)
{
	return GetSubHitProb();
}

ei_s32 CrCharacter::GetEqAvoidProb(void)
{
	int a,value = 0;

	//---強制値があれば
	if(CharaInfo.force_AvoidProb){
		return CharaInfo.force_AvoidProb;
	}

	for(a = 0;a < EQ_ALL_MAX;a ++){
		value += pItemInfo[GetEquipment(a)].GetAvoidProb();
	}

	if(value > 1000)
		value = 1000;
	if(value < 0)
		value = 0;

	return value;
}

ei_s32 CrCharacter::GetEqMagicAvoidProb(void)
{
	int a,value = 0;

	//---強制値があれば
	if(CharaInfo.force_MagicAvoidProb)
		return CharaInfo.force_MagicAvoidProb;

	for(a = 0;a < EQ_ALL_MAX;a ++){
		value += pItemInfo[GetEquipment(a)].GetMagicAvoidProb();
	}

	if(value > 1000)
		value = 1000;
	if(value < 0)
		value = 0;

	return value;
}

//---------------------------------------------------
//---装備品取得
ei_s32 CrCharacter::GetEquipment(int number)
{
	if(number < EQ_WEAPON_MAX){
		return GetWeapon(number);
	}

	number -= EQ_WEAPON_MAX;

	if(number < EQ_PROTECTOR_MAX){
		return GetProtector(number);
	}

	number -= EQ_PROTECTOR_MAX;

	return GetAccessory(number);
}

void CrCharacter::SetEquipment(int number,int item)
{
	if(number < EQ_WEAPON_MAX){
		SetWeapon(number,item);
		return;
	}

	number -= EQ_WEAPON_MAX;

	if(number < EQ_PROTECTOR_MAX){
		SetProtector(number,item);
		return;
	}

	number -= EQ_PROTECTOR_MAX;

	SetAccessory(number,item);
}

//---武器
ei_s32 CrCharacter::GetWeapon(int number)
{
	return CharaInfo.eq_weapon[number];
}

void CrCharacter::SetWeapon(int number,int item)
{
	CharaInfo.eq_weapon[number] = item;
}

//---攻撃可能武器か？
ei_s32 CrCharacter::IsWeaponEnableToAtack(int number,int mode)
{
	if(mode == 0){
		if(GetWeapon(number))
			return 1;
	} else {
		if(GetWeapon(number) && pItemInfo[GetWeapon(number)].GetAtackKind() == mode - 1)
			return 1;
	}
	return 0;
}

//---もう一方の武器を得る
ei_s32 CrCharacter::GetAnotherWeapon(int item_number,int dumy)
{
	if(GetWeapon(0) == item_number)
		return GetWeapon(1);

	if(GetWeapon(1) == item_number)
		return GetWeapon(0);

	return 0;
}

ei_s32 CrCharacter::GetAnotherWeapon(int number)
{
	return GetWeapon(number ? 0 : 1); 
}

//-------------------------------------
//---防具
ei_s32 CrCharacter::GetProtector(int number)
{
	return CharaInfo.eq_protector[number];
}

void CrCharacter::SetProtector(int number,int item)
{
	CharaInfo.eq_protector[number] = item;
}

//---アクセサリー
ei_s32 CrCharacter::GetAccessory(int number)
{
	return CharaInfo.eq_accessory[number];
}

void CrCharacter::SetAccessory(int number,int item)
{
	CharaInfo.eq_accessory[number] = item;
}

//---装備後攻撃力計算
ei_s32 CrCharacter::CalcAtack(CrItem *pItem)
{
	if(pItem != NULL){
		int value = 0,kind = pItem->GetKind();

		if(CRMATERIAL_ITEMKIND_WEAPONMIN <= kind && kind <= CRMATERIAL_ITEMKIND_WEAPONMAX){
			//---武器なら
			if(pItem->GetDamageStatus() == 0){
				//---直接武器
				value = GetPower() + pItem->GetAtack();
			} else {
				//---間接武器
				value = pItem->GetAtack();
			}
		}

		return value;
	}

	return -1;
}
