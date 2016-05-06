
//---２進数文字列から整数に変換
int crdebugStringToBin(eistr *string)
{
	int ret = 0,bin = 1;

	while(*string){
		if(*string == '1')
			ret |= bin;

		bin <<= 1;
		string ++;
	}

	return ret;
}

//---文字列から固有値に変換
int crdebugStringToInt(eistr *string,eistr **strtable,int *inttable)
{
	int c = 0;

	while(strcmp(strtable[c],"end") != 0){
		if(strcmp(strtable[c],string) == 0){
			//---一致したら
			return inttable[c];
		}
		c ++;
	}
	return 0;
}

//---文字列をわける
int crdebugMakeStringData(eistr *buffer,eistr **str,eistr **option)
{
	eistr *center;

	center = strrchr(buffer,':');
	if(!center)
		return 0;

	*str = buffer;
	*center = 0;
	*option = center + 1;

	center ++;
	while(*center){
		if(*center == '\n' || *center == '\r'){
			*center = 0;
		}
		center ++;
	}

	return 1;
}

//-----------------------------------------------------

static eistr *ElementString[] = 
{
	"  ","無","回復","補助",
	"火","水","土","風",
	"雷","精","変","物理",
		"end"
};

static int ElementInt[] = 
{
	ELEMENT_NOMAGIC,ELEMENT_NOELEMENT,ELEMENT_RECOVERY,ELEMENT_HELP,
	ELEMENT_FIRE,ELEMENT_AQUA,ELEMENT_EARTH,ELEMENT_WIND,
	ELEMENT_THUNDER,ELEMENT_SOUL,ELEMENT_CHANGE,ELEMENT_PHYSICS,
	ELEMENT_BREATH,ELEMENT_OTHER,
};
//-------------------------------------------------------

#include "Make\CrDebug_Magic.cpp"
#include "Make\CrDebug_Item.cpp"
#include "Make\CrDebug_Enemy.cpp"
#include "Make\CrDebug_Special.cpp"
#include "Make\CrDebug_htmlOut.cpp"

//---データ作成
int crdebugMakeData(int mode)
{
//	crdebugCreateItemData("Make\\ItemKaihatu.txt",0);
	crdebugCreateItemData("Make\\ItemSSword.txt",0);
	crdebugCreateItemData("Make\\ItemSword.txt",0);
	crdebugCreateItemData("Make\\ItemLSword.txt",0);
	crdebugCreateItemData("Make\\ItemKnife.txt",0);
	crdebugCreateItemData("Make\\ItemGun1.txt",0);
	crdebugCreateItemData("Make\\ItemGun2.txt",0);
	crdebugCreateItemData("Make\\ItemWeaponOther.txt",0);

	crdebugCreateItemData("Make\\ItemSuit.txt",0);
	crdebugCreateItemData("Make\\ItemArmor.txt",0);
	crdebugCreateItemData("Make\\ItemRobe.txt",0);

	crdebugCreateItemData("Make\\ItemSShield.txt",0);
	crdebugCreateItemData("Make\\ItemLShield.txt",0);

	crdebugCreateItemData("Make\\ItemHead.txt",0);
	crdebugCreateItemData("Make\\ItemAccessory.txt",0);

	crdebugCreateItemData("Make\\ItemItem.txt",0);

	FILE *fp = fopen("Data1\\ItemData.dat","wb");
	int a;

	for(a = 0;a < ITEMMATERIAL_MAX;a ++){
		fwrite(&pItemInfo[a].MaterialInfo,sizeof(pItemInfo[a].MaterialInfo),1,fp);
		fwrite(&pItemInfo[a].ItemInfo,sizeof(pItemInfo[a].ItemInfo),1,fp);
	}
	fclose(fp);

	//---
	for(a = 0;a < MAGICMATERIAL_MAX;a ++){
		pMagicInfo[a].MagicInfo.Element = ELEMENT_NOMAGIC;
	}
//	crdebugCreateMagicData("Make\\MagicKaihatu.txt",0);
	crdebugCreateMagicData("Make\\MagicHi.txt",0);
	crdebugCreateMagicData("Make\\MagicMizu.txt",0);
	crdebugCreateMagicData("Make\\MagicTuchi.txt",0);
	crdebugCreateMagicData("Make\\MagicKaze.txt",0);
	crdebugCreateMagicData("Make\\MagicKaminari.txt",0);
//	crdebugCreateMagicData("Make\\MagicSeisin.txt",0);
	crdebugCreateMagicData("Make\\MagicKaifuku.txt",0);
	crdebugCreateMagicData("Make\\MagicHojo.txt",0);
	crdebugCreateMagicData("Make\\MagicOther.txt",0);

	fp = fopen("Data1\\MagicData.dat","wb");
	for(a = 0;a < MAGICMATERIAL_MAX;a ++){
		fwrite(&pMagicInfo[a].MaterialInfo,sizeof(pMagicInfo[a].MaterialInfo),1,fp);
		fwrite(&pMagicInfo[a].MagicInfo,sizeof(pMagicInfo[a].MagicInfo),1,fp);
	}
	fclose(fp);

	//---
	memset(&pEnemyBatInfo[0],0,sizeof(CRESTEAJU_BATTLECHARAINFO) * ENEMY_MAX);
	memset(&pEnemyCharaInfo[0],0,sizeof(CRESTEAJU_CHARACTERINFO) * ENEMY_MAX);
	crdebugCreateEnemyData("Make\\EnemyKaihatu.txt",0);
	crdebugCreateEnemyData("Make\\Enemy00.txt",0);
	crdebugCreateEnemyData("Make\\Enemy01.txt",0);
	crdebugCreateEnemyData("Make\\Enemy02.txt",0);
	crdebugCreateEnemyData("Make\\Enemy03.txt",0);
	crdebugCreateEnemyData("Make\\Enemy04.txt",0);
	crdebugCreateEnemyData("Make\\Enemy05.txt",0);
	crdebugCreateEnemyData("Make\\Enemy06.txt",0);

	fp = fopen("Data3\\EnemyData.dat","wb");
	fwrite(&pEnemyBatInfo[0],sizeof(CRESTEAJU_BATTLECHARAINFO),ENEMY_MAX,fp);
	fwrite(&pEnemyCharaInfo[0],sizeof(CRESTEAJU_CHARACTERINFO),ENEMY_MAX,fp);

	fclose(fp);

	//---
	crdebugCreateSpecialData("Make\\Special.txt",0);

	fp = fopen("Data1\\SpecialData.dat","wb");
	for(a = 0;a < SPECIALMATERIAL_MAX;a ++){
		fwrite(&pSpecialInfo[a].MaterialInfo,sizeof(pSpecialInfo[a].MaterialInfo),1,fp);
		fwrite(&pSpecialInfo[a].SpecialInfo,sizeof(pSpecialInfo[a].SpecialInfo),1,fp);
	}
	fclose(fp);

	return 1;
}
