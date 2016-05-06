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

//---�A�C�e���N���X��Ԃ�
CRBASE_ITEMAPI CrItem *critemGetItemClass(int number)
{
//	return pGameInfo->ItemInfo[number];
	return (pItemInfo + number);
}

//---�w�肳�ꂽ�A�C�e���̃C���f�b�N�X��Ԃ�
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


//---�w�肳�ꂽ�C���f�b�N�X�̃A�C�e����Ԃ�
CRBASE_ITEMAPI int critemGetItemIndex(int index)
{
//	if(index == -1)
//		return -1;

	if(index < 0 || index >= ITEM_MAX)
		return 0;

	return pGameInfo->Item[index];
}

//---�w�肳�ꂽ�C���f�b�N�X�ɃA�C�e�����Z�b�g����
CRBASE_ITEMAPI void critemSetItemIndex(int index,int num)
{
	if(index < 0 || index >= ITEM_MAX)
		return;

	pGameInfo->Item[index] = num; 
}

//---�w�肳�ꂽ�i���o�[�̃A�C�e���̌���Ԃ�
CRBASE_ITEMAPI int critemGetItemCount(int num)
{
	int index = critemSerchItem(num);

	if(index != -1){
		return critemGetItemIndexCount(index);
	}

	return 0;
}

//---�w�肳�ꂽ�C���f�b�N�X�̃A�C�e���̌���Ԃ�
CRBASE_ITEMAPI int critemGetItemIndexCount(int index)
{
	if(index < 0 || index >= ITEM_MAX)
		return 0;

	return pGameInfo->ItemCount[index];
}

//---�w�肳�ꂽ�C���f�b�N�X�ɃA�C�e���̌����Z�b�g����
CRBASE_ITEMAPI void critemSetItemIndexCount(int index,int count)
{
	if(index < 0 || index >= ITEM_MAX)
		return;
	pGameInfo->ItemCount[index] = count; 
}

//---�w�肳�ꂽ�A�C�e����T���A�C���f�b�N�X��Ԃ�
CRBASE_ITEMAPI int critemSerchItem(int num)
{
	int a;

	for(a = 0;a < ITEM_MAX;a ++){
		if(critemGetItemIndex(a) == num)
			return a;
	}

	return -1;
}

//---�u�����N�X�y�[�X��T��
CRBASE_ITEMAPI int critemSerchBlank(void)
{
	int a;

	for(a = 0;a < ITEM_MAX;a ++){
		if(critemGetItemIndex(a) == 0){
			//---�����O�ɂ��Ă���
			critemSetItemIndexCount(a,0);
			return a;
		}
	}

	return -1;
}

//---�A�C�e���𑝂₷
CRBASE_ITEMAPI void critemAddItem(int num,int count /*= 1*/)
{
	int index;

	//---��A�C�e���������牽�����Ȃ�
	if(num == 0)
		return;

	index = critemSerchItem(num);
	if(index == -1){
		//---�ړI�̃A�C�e�����Ȃ�������󂫃X�y�[�X��T��
		index = critemSerchBlank();
		if(index != -1){
			critemSetItemIndex(index,num);
			critemSetItemIndexCount(index,0);
		}
	} 

	if(index != -1){
		critemSetItemIndexCount(index , critemGetItemIndexCount(index) + count);
		if(critemGetItemIndexCount(index) > ITEMCOUNT_MAX){
			//---��������z������
			critemSetItemIndexCount(index , ITEMCOUNT_MAX);
		}
		if(critemGetItemIndexCount(index) <= 0){
			//---�A�C�e�����Ȃ��Ȃ�����
			critemSetItemIndexCount(index , 0);
			critemSetItemIndex(index , 0);
		}
	}
}

//---�A�C�e�������炷
CRBASE_ITEMAPI void critemSubItem(int num,int count /*= 1*/)
{
	critemAddItem(num,-count);
}

//---------------------------------------------------
//---�A�C�e���I��
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
//---�A�C�e�����g�p�\��
CRBASE_ITEMAPI int critemIsUseItem(int num,int scene /*= 0  0:field , 1:battle*/)
{
	if(num <= 0 || num >= ITEM_MAX)
		return 0;

	CrItem *pItem = critemGetItemClass(num);
	if(pItem->GetScene() != 2 && pItem->GetScene() != scene)
		//---�V�[��������Ȃ����
		return 0;

	return 1;
}
