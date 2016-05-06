//---キャラクタークラス

/*ei_s32 CrCharacter::LPMaxStatus = 9999,CrCharacter::LPMinStatus = -999,
	CrCharacter::BalanceMaxStatus = 125,CrCharacter::BalanceMinStatus = 75;
*/

#include "CrCharacter_SubLPStatus.cpp"
#include "CrCharacter_SubOtherStatus.cpp"
#include "CrCharacter_SubEquipSt.cpp"
#include "CrCharacter_SubBattleSt.cpp"
#include "CrCharacter_SubBattleHistory.cpp"

CrCharacter::CrCharacter(void) : CrObject()
{
	eimemset(&CharaInfo,0,sizeof(CharaInfo));

	LPMaxStatus = 9999;
	LPMinStatus = -999;
	BalanceMaxStatus = 125;
	BalanceMinStatus = 75;
	LevelMax = 99;
	ExperienceMax = 99999999;
	MagicExpMax = 9999;
	Zero = 0;
}

CrCharacter::~CrCharacter()
{
}

int CrCharacter::KindOf(void)
{
	return CROBJECT_CHARACTER;
}

//---誰か
int CrCharacter::Who(void)
{
	return CharaInfo.Who;
}

void CrCharacter::SetWho(int num)
{
	CharaInfo.Who = num;
}

//---名前
eistr *CrCharacter::GetName(void)
{
	return &CharaInfo.Name[0];
}

CRESTEAJU_CHARACTERINFO *CrCharacter::GetCharacterInfo(void)
{
	return &CharaInfo;
}

CRESTEAJU_CHARACTER_BATTLEINFO *CrCharacter::GetCharacterBattleHistory(void)
{
	return &CharaInfo.BattleHistory;
}

//---保護設定
ei_s32 CrCharacter::SetProtect(int flag)
{
	int old = IsProtected();

	CharaInfo.Protect = flag;

	return old;
}

//---保護されているかどうか
ei_s32 CrCharacter::IsProtected(void)
{
	return CharaInfo.Protect;
}

//---バトルフィールド初期位置
void CrCharacter::SetBattleFieldStartPos(ei_s32 x,ei_s32 y)
{
	CharaInfo.BattleX = x;
	CharaInfo.BattleY = y;
}

//---バトルフィールド初期位置
ei_s32 CrCharacter::GetBattleFieldStartX(void)
{
	return CharaInfo.BattleX;
}

ei_s32 CrCharacter::GetBattleFieldStartY(void)
{
	return CharaInfo.BattleY;
}

//---バトルファイル名
static eistr *CharaBattleFileName[] = 
{
	"0",
	"BatLunarn.acf","BatDizza.acf","BatNack.acf","BatXavier.acf",
	"BatYumi.acf","BatLizel.acf","BatCindy.acf","",
	"9","10","11","12",
	"BatRarfia.acf","BatLunarnF.acf","BatGazell.acf","BatFollne.acf",
	"17","18"
};

eistr *CrCharacter::GetBattleFileName(void)
{
	return CharaBattleFileName[Who()];

/*	switch(Who()){

	case 1:
		return "BatLunarn.acf";
	case 2:
		return "BatDizza.acf";
	case 3:
		return "BatNack.acf";
	case 4:
		return "BatXavier.acf";
	case 5:
		return "BatYumi.acf";
	case 6:
		return "BatLizel.acf";
	case 7:
		return "BatCindy.acf";

	case 13:
		return "BatRarfia.acf";
	case 14:
		return "BatLunarnF.acf";
	case 15:
		return "BatGazell.acf";
	case 16:
		return "BatFollne.acf";

	default:
		break;
	}

	return "BatAlya.acf";*/
}

//----------------------------------------------
//---カーソル情報
CRWIN_SELECTINFO *CrCharacter::GetMagicBattleCursor(void)
{
	return &CharaInfo.MagicBattleCursor;
}

CRWIN_SELECTINFO *CrCharacter::GetMagicFieldCursor(void)
{
	return &CharaInfo.MagicFieldCursor;
}

//----------------------------------------------
//---インデックスの魔法を返す
ei_s32 CrCharacter::GetMagic(int index)
{
	if(index < 0 || index >= MAGIC_MAX)
		return 0;

	return CharaInfo.MagicTable[index];
}

//---numberの魔法を所持しているか
int CrCharacter::HaveMagic(int number)
{
	int a;

	if(number == 0)
		//---空魔法
		return 0;

	for(a = 0;a < MAGIC_MAX;a ++){
		if(GetMagic(a) == number)
			return 1;
	}

	return 0;
}

//---同じ属性の魔法を何個覚えているか
int CrCharacter::HaveMagicElement(int element)
{
	int a,count;
	CrMagic *pMagic = pMagicInfo;

	for(a = 0 , count = 0;a < MAGIC_MAX;a ++){
		if(GetMagic(a)){
			if(pMagic[GetMagic(a)].GetMaterialKind() == element){
				count ++;
			}
		}
	}

	return count;
}

//---numberの魔法を使えるか
int CrCharacter::CanUseMagic(int number)
{
//	if(GetMC() < 
	return 0;
}

//---新しい魔法を覚える
void CrCharacter::AddMagic(int number)
{
	int a;

	for(a = 0;a < MAGIC_MAX;a ++){
		if(CharaInfo.MagicTable[a] == 0){
			CharaInfo.MagicTable[a] = number;
			break;
		}
	}
}

//---最後に魔法を使ってからどのくらい経ったか
void CrCharacter::SetLastUsingMagic(void)
{
	CharaInfo.since_lastusingmagic = 0;
	CharaInfo.usingmagic_subcount = 0;
}

void CrCharacter::CountSinceUsingMagic(int count)
{
}

//---ＭＣ回復不可能歩数セット
void CrCharacter::SetDisableMCCount(int count)
{
	if(count == -1)
		count = 15;
	CharaInfo.DisableMCCount = count;
}

void CrCharacter::SubDisableMCCount(void)
{
	if(CharaInfo.DisableMCCount > 0)
		CharaInfo.DisableMCCount --;
}

ei_s32 CrCharacter::GetDisableMCCount(void)
{
	return CharaInfo.DisableMCCount;
}

ei_s32 CrCharacter::AddDeltaMC(int delta)
{
	CharaInfo.DeltaMC += delta;

	return CharaInfo.DeltaMC;
}

void CrCharacter::SetDeltaMC(int delta)
{
	CharaInfo.DeltaMC = delta;
}

ei_s32 CrCharacter::GetDeltaMC(void)
{
	return CharaInfo.DeltaMC;
}

//------------------------------------------------------
//---ステータスを足し引きする
ei_s32 CrCharacter::AddStatus(ei_s32 add,ei_s32 *value,ei_s32 *max_value,ei_s32 *min_value)
{
	int c = *value,pre = *value;

	c = *value + add;
	*value = c;

	if(max_value != NULL){
		//---最大値を超えたら
		if(c >= *max_value)
			*value = *max_value;
	}
	if(min_value != NULL){
		//---最小値を下回ったら
		if(c <= *min_value)
			*value = *min_value;
	}

	return pre;
}
