//---物質クラス

#define FILE_CRMATERIAL

CrMaterial::CrMaterial(void) : CrObject()
{
	eimemset(&MaterialInfo,0,sizeof(MaterialInfo));
	MaterialInfo.Size = sizeof(MaterialInfo);
}

CrMaterial::~CrMaterial()
{
}

//---種類
int CrMaterial::KindOf(void)
{
	return CROBJECT_MATERIAL;
}

//---サイズ
int CrMaterial::SizeOf(void)
{
	return sizeof(CROBJECT_MATERIAL);
}

//---特定の値
ei_s32 CrMaterial::GetData(int kind)
{
	return 0;
}

//---マテリアル内での種類
ei_s32 CrMaterial::GetMaterialKind(void)
{
	return 0;
}

//----------------------------------
//---
CRESTEAJU_MATERIALINFO *CrMaterial::GetMaterialInfo(void)
{
	return &MaterialInfo;
}

eistr *CrMaterial::GetName(void)
{
	return &MaterialInfo.Name[0];
}

eistr *CrMaterial::GetKanaName(void)
{
	return &MaterialInfo.KanaName[0];
}

eistr *CrMaterial::GetHelp(void)
{
	return &MaterialInfo.Help[0];
}

#include "CrMaterial_SubItem.cpp"
#include "CrMaterial_SubMagic.cpp"
#include "CrMaterial_SubSpecial.cpp"

