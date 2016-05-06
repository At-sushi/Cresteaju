/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBase_ItemAPI.cpp ...ItemBase functions

-----------------------------------------------------------*/
#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBASE_ITEMAPI

#define EXTERN_EICLASS
#include "..\CrBase.h"

//---game info
#define CR_GAMEINFO_EXTERNPOINTER
#include "..\CrGameInfo.h"

//---アイテムクラスを返す
CRBASE_ITEMAPI CrItem *critemGetItemClass(int number)
{
//	return pGameInfo->ItemInfo[number];
	return (pItemInfo + number);
}

//---指定されたアイテムのインデックスを返す
CRBASE_ITEMAPI int critemGetIndex(int number)
{
	if(number < 0 || number >= ITEM_MAX)
		return 0;

	int a;

	for(a = 0;a < ITEM_MAX;a ++){
		if(pGameInfo->Item[a] == number)
			return a;
	}
	return -1;
}


//---指定されたインデックスのアイテムを返す
CRBASE_ITEMAPI int critemGetItemIndex(int index)
{
//	if(index == -1)
//		return -1;

	if(index < 0 || index >= ITEM_MAX)
		return 0;

	return pGameInfo->Item[index];
}

//---指定されたインデックスにアイテムをセットする
CRBASE_ITEMAPI void critemSetItemIndex(int index,int num)
{
	if(index < 0 || index >= ITEM_MAX)
		return;

	pGameInfo->Item[index] = num; 
}

//---指定されたナンバーのアイテムの個数を返す
CRBASE_ITEMAPI int critemGetItemCount(int num)
{
	int index = critemSerchItem(num);

	if(index != -1){
		return critemGetItemIndexCount(index);
	}

	return 0;
}

//---指定されたインデックスのアイテムの個数を返す
CRBASE_ITEMAPI int critemGetItemIndexCount(int index)
{
	if(index < 0 || index >= ITEM_MAX)
		return 0;

	return pGameInfo->ItemCount[index];
}

//---指定されたインデックスにアイテムの個数をセットする
CRBASE_ITEMAPI void critemSetItemIndexCount(int index,int count)
{
	if(index < 0 || index >= ITEM_MAX)
		return;
	pGameInfo->ItemCount[index] = count; 
}

//---指定されたアイテムを探し、インデックスを返す
CRBASE_ITEMAPI int critemSerchItem(int num)
{
	int a;

	for(a = 0;a < ITEM_MAX;a ++){
		if(critemGetItemIndex(a) == num)
			return a;
	}

	return -1;
}

//---ブランクスペースを探す
CRBASE_ITEMAPI int critemSerchBlank(void)
{
	int a;

	for(a = 0;a < ITEM_MAX;a ++){
		if(critemGetItemIndex(a) == 0){
			//---個数を０個にしておく
			critemSetItemIndexCount(a,0);
			return a;
		}
	}

	return -1;
}

//---アイテムを増やす
CRBASE_ITEMAPI void critemAddItem(int num,int count /*= 1*/)
{
	int index;

	//---空アイテムだったら何もしない
	if(num == 0)
		return;

	index = critemSerchItem(num);
	if(index == -1){
		//---目的のアイテムがなかったら空きスペースを探す
		index = critemSerchBlank();
		if(index != -1){
			critemSetItemIndex(index,num);
			critemSetItemIndexCount(index,0);
		}
	} 

	if(index != -1){
		critemSetItemIndexCount(index , critemGetItemIndexCount(index) + count);
		if(critemGetItemIndexCount(index) > ITEMCOUNT_MAX){
			//---個数上限を越えたら
			critemSetItemIndexCount(index , ITEMCOUNT_MAX);
		}
		if(critemGetItemIndexCount(index) <= 0){
			//---アイテムがなくなったら
			critemSetItemIndexCount(index , 0);
			critemSetItemIndex(index , 0);
		}
	}
}

//---アイテムを減らす
CRBASE_ITEMAPI void critemSubItem(int num,int count /*= 1*/)
{
	critemAddItem(num,-count);
}

//---------------------------------------------------
//---アイテム選択
CRBASE_ITEMAPI int critemSelectItem(int sx,int sy,int pagesize,int width,int op1 /*= 0*/,int op2 /*= 0*/,
					 int op3 /*= 0*/,int op4 /*= 0*/,int helppos /*= 0*/,CRWIN_SELECTINFO *pInfo /*= NULL*/)
{
	int index,option[] = {op1 , op2 , op3 , op4};
	int a,last_index;
	CrSelectWindow menu;
	CrMessageWindow help;
	MATERIALWINDOW_STYLE Style;

	memset(&Style,0,sizeof(Style));
	Style.Style = MATERIALWINDOW_STYLE_ITEMICON;

	for(a = 0,last_index = 0;a < ITEM_MAX;a ++){
		if(critemGetItemIndex(a)){
			last_index = a + 1;
		}
	}
	if(last_index == 0)
		last_index = 1;
	last_index = ((last_index / pagesize) 
		+ ((last_index % pagesize) != 0 ? 1: 0)) * pagesize;

	//---index
	Style.pIndex = &pGameInfo->Item[0];
	Style.IndexMax = last_index;
	Style.pSubItem[0] = &pGameInfo->ItemCount[0];
	//---material
	Style.pMaterial = pItemInfo;
	Style.MaterialMax = ITEM_MAX;
	//---page
	Style.PageSize = pagesize;
	//---option
	Style.Option = &option[0];

	//---help
	Style.pHelpWindow = &help;
	Style.HelpWindowPos = helppos;

	index = crmateCreateAndSelectMaterialWindow(&menu,
		sx,sy,width,
		0/*mode*/,pInfo,&Style);

	if(index == -1)
		return index;

	return critemGetItemIndex(index);
}

//---------------------------------------------------
//---アイテムが使用可能か
CRBASE_ITEMAPI int critemIsUseItem(int num,int scene /*= 0  0:field , 1:battle*/)
{
	if(num <= 0 || num >= ITEM_MAX)
		return 0;

	CrItem *pItem = critemGetItemClass(num);
	if(pItem->GetScene() != 2 && pItem->GetScene() != scene)
		//---シーンが合わなければ
		return 0;

	return 1;
}
