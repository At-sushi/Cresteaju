/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBase_MagicAPI.cpp ...MagicBase functions

-----------------------------------------------------------*/
#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBASE_MAGICAPI

#define EXTERN_EICLASS
#include "..\CrBase.h"

//---game info
#define CR_GAMEINFO_EXTERNPOINTER
#include "..\CrGameInfo.h"

//---魔法クラスを返す
CRBASE_MAGICAPI CrMagic *crmagicGetMagicClass(int number)
{
	return (pMagicInfo + number);
}

/*CRBASE_MAGICAPI int crbaseGetCharacterMagic(CrCharacter *pChara,int index)
{
	if(!pChara)
		return 0;

	return pChara->GetMagic(index);
}*/

CRBASE_MAGICAPI void SelectCharacterMagicCallBack(
	CrSelectWindow *pWin,eiCell *pCell,ei_u32 pmaterial)
{
	eistr str[100];
	MATERIALWINDOW_STYLE *pstyle = (MATERIALWINDOW_STYLE *)pmaterial;

	if(pstyle != NULL){
		if(pstyle->Data[0] == NULL)
			return;

		int old = eiSetFont(EISMALL_FONT);

		pCell->DrawFillBox(pWin->xGetTop() + 128,pWin->yGetTop() + 1,
			pWin->xGetTop() + 128 + 12 * 6,pWin->yGetTop() + 13,
			ep->ToRGB(CRCOLOR_BLACK));

		pCell->DrawText("MC:",pWin->xGetTop() + 128,pWin->yGetTop() + 1,ep->ToTextRGB(CRCOLOR_WHITE));

//		pWin->SetColor(crcharaGetStatusColor(((CrCharacter *)(pstyle->Data[0]))->GetMC(),((CrCharacter *)(pstyle->Data[0]))->GetMaxMC()));
		sprintf(str,"%4d",((CrCharacter *)(pstyle->Data[0]))->GetMC());
		pCell->DrawText(str,pWin->xGetTop() + 128 + 18,pWin->yGetTop() + 1,ep->ToTextRGB(crcharaGetStatusColor(((CrCharacter *)(pstyle->Data[0]))->GetMC(),((CrCharacter *)(pstyle->Data[0]))->GetMaxMC())));
		sprintf(str,"/%4d",((CrCharacter *)(pstyle->Data[0]))->GetMaxMC());
		pCell->DrawText(str,pWin->xGetTop() + 128 + 18 + 24,pWin->yGetTop() + 1,ep->ToTextRGB(CRCOLOR_WHITE));

		eiSetFont(old);
	}
}

//---------------------------------------------------
//---キャラクターの魔法選択
CRBASE_MAGICAPI int crmagicSelectCharacterMagic(
					CrCharacter *pChara,
					int scene,
					int sx,int sy,int pagesize,int width,int op1 /*= 0*/,int op2 /*= 0*/,
					int op3 /*= 0*/,int op4 /*= 0*/,int helppos /*= 0*/)
{
	int index,option[] = {op1 , op2 , op3 , op4};
	int a,last_index;
	CrSelectWindow menu;
	CrMessageWindow help;
	MATERIALWINDOW_STYLE Style;

	//---カーソル情報取得
	CRWIN_SELECTINFO *pInfo;
	if(scene == 0){
		pInfo = pChara->GetMagicFieldCursor();
	} else {
		pInfo = pChara->GetMagicBattleCursor();
	}

	for(a = 0,last_index = 0;a < MAGIC_MAX;a ++){
		if(pChara->GetMagic(a)){
			last_index = a + 1;
		}
	}
	if(last_index == 0)
		last_index = 1;
	last_index = ((last_index / pagesize) 
		+ ((last_index % pagesize) != 0 ? 1: 0)) * pagesize;

	memset(&Style,0,sizeof(Style));
	Style.Style = MATERIALWINDOW_STYLE_MAGICICON;
	//---index
	Style.pIndex = &pChara->CharaInfo.MagicTable[0];
	Style.IndexMax = last_index;
	Style.pSubItem[0] = &scene;
	//---material
	Style.pMaterial = pMagicInfo;
	Style.MaterialMax = MAGICMATERIAL_MAX;
	//---page
	Style.PageSize = pagesize;
	//---option
	Style.Option = &option[0];

	Style.pMenuTitleCallBack = SelectCharacterMagicCallBack;

	//---help
	Style.pHelpWindow = &help;
	Style.HelpWindowPos = helppos;
	//---Data
	Style.Data[0] = (ei_u32)pChara;

	index = crmateCreateAndSelectMaterialWindow(&menu,
		sx,sy,width,
		0/*mode*/,pInfo,&Style);

	if(index == -1)
		return index;

	return pChara->GetMagic(index);
}

//---------------------------------------------------
//---魔法が使用可能か
CRBASE_MAGICAPI int crmagicIsUseMagic(CrCharacter *pChara,int num,int scene /*= 0  0:field , 1:battle*/)
{
	if(num <= 0 || num >= MAGICMATERIAL_MAX)
		return 0;

	CrMagic *pMagic = crmagicGetMagicClass(num);
	if(pMagic->GetScene() != 2 && pMagic->GetScene() != scene)
		//---シーンが合わなければ
		return 0;
	if(pChara->GetMC() < pMagic->GetMC())
		//---ＭＣが足りなければ
		return 0;

	return 1;
}

//---魔法の基本値を得る
CRBASE_MAGICAPI int crmagicGetBaseValue(int number,CrCharacter *pChara)
{
	int value = 0;
	CrMagic *pMagic = crmagicGetMagicClass(number);
	if(pMagic == NULL)
		return 0;
	
	value = pMagic->GetDamage();

	switch(number){
	case 1:
	case 5:
		value += (pChara->GetLevel() / 2);
		break;
	case 3:
	case 7:
		value += (pChara->GetLevel());
		break;
	}

	return value;
}
