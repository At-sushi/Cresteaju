/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBase_ShopAPI.cpp ...Shop functions

-----------------------------------------------------------*/
#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBASE_SHOPAPI

#define EXTERN_EICLASS
#include "..\CrBase.h"

//---game info
#define CR_GAMEINFO_EXTERNPOINTER
#include "..\CrGameInfo.h"

typedef struct
{
	int *pItems;
	int Select,Count,IndexCount,Mode;
} SHOP_INFO,*PSHOP_INFO;

static CrSelectWindow *pMenuWindow;
static CrStringWindow *pCharaWindow;
static MATERIALWINDOW_STYLE ShopStyle;
static CrMessageWindow *pShopHelp;
static CRWIN_SELECTINFO ShopBuy,ShopSell,ShopMenu;

void crshopShowItemInfo(CrItem *pItem,int number)
{
	int x = 32,y = 80,kind = pItem->GetMaterialKind();
	CrStringWindow ItemWin;
	eistr s[80];

	ItemWin.Create(x,y,12,12);
	ItemWin.Paint();

	if(pItem == NULL)
		return;
	if(*(pItem->GetName()) == NULL)
		return;

	ItemWin.AddReturn();
	ItemWin.DrawText(pItem->GetName());
	ItemWin.AddReturn();
	ItemWin.AddReturn();

	//---
	int a,b,having = 0;
	CrCharacter *pChara;

	having += critemGetItemCount(number);
	for(a = 0;a < MEMBER_MAX;a ++){
		pChara = crcharaGetPartyMember(a);
		if(pChara == NULL)
			continue;
		for(b = 0;b < EQ_ALL_MAX;b ++){
			if(number == pChara->GetEquipment(b)){
				having ++;
			}
		}
	}
	ItemWin.DrawText("�����Ă��鐔:");
	sprintf(s,"%3d%",having);
	ItemWin.SetColor(CRCOLOR_GREEN);
	ItemWin.DrawText(s);
	ItemWin.SetColor(CRCOLOR_WHITE);
	ItemWin.AddReturn();

	if(CRMATERIAL_ITEMKIND_WEAPONMIN <= kind && kind <= CRMATERIAL_ITEMKIND_WEAPONMAX){
		//---����
		ItemWin.DrawText("����^�C�v: ");
		sprintf(s,"%s",pItem->GetAtackKind() == 0 ? "����" : "�Ԑ�");
		ItemWin.SetColor(CRCOLOR_GREEN);
		ItemWin.DrawText(s);
		ItemWin.SetColor(CRCOLOR_WHITE);
		ItemWin.AddReturn();

		ItemWin.DrawText("�U����    : ");
		sprintf(s,"%d",pItem->GetAtack());
		ItemWin.SetColor(CRCOLOR_GREEN);
		ItemWin.DrawText(s);
		ItemWin.SetColor(CRCOLOR_WHITE);
		ItemWin.AddReturn();

		ItemWin.DrawText("������    : ");
		sprintf(s,"%d%%",pItem->GetHitProb() / 10);
		ItemWin.SetColor(CRCOLOR_GREEN);
		ItemWin.DrawText(s);
		ItemWin.SetColor(CRCOLOR_WHITE);
		ItemWin.AddReturn();

		ItemWin.DrawText("�s���͕ω�:");
		sprintf(s,"%+3.1f%%",(double)pItem->GetAction() / 10.0);
		ItemWin.SetColor(CRCOLOR_GREEN);
		ItemWin.DrawText(s);
		ItemWin.SetColor(CRCOLOR_WHITE);
		ItemWin.AddReturn();
	} if(CRMATERIAL_ITEMKIND_ARMORMIN <= kind && kind <= CRMATERIAL_ITEMKIND_HELMETMAX){
		//---�h��
		ItemWin.DrawText("�h���    : ");
		sprintf(s,"%d",pItem->GetDefense());
		ItemWin.SetColor(CRCOLOR_GREEN);
		ItemWin.DrawText(s);
		ItemWin.SetColor(CRCOLOR_WHITE);
		ItemWin.AddReturn();

		ItemWin.DrawText("���@�h��  : ");
		sprintf(s,"%d",pItem->GetMagicDefense());
		ItemWin.SetColor(CRCOLOR_GREEN);
		ItemWin.DrawText(s);
		ItemWin.SetColor(CRCOLOR_WHITE);
		ItemWin.AddReturn();

		ItemWin.DrawText("���    : ");
		sprintf(s,"%d%%",pItem->GetAvoidProb() / 10);
		ItemWin.SetColor(CRCOLOR_GREEN);
		ItemWin.DrawText(s);
		ItemWin.SetColor(CRCOLOR_WHITE);
		ItemWin.AddReturn();

		ItemWin.DrawText("�s���͒ቺ :");
		sprintf(s,"%+3.1f%%",(double)pItem->GetAction() / 10.0);
		ItemWin.SetColor(CRCOLOR_GREEN);
		ItemWin.DrawText(s);
		ItemWin.SetColor(CRCOLOR_WHITE);
		ItemWin.AddReturn();
	} else if(CRMATERIAL_ITEMKIND_ACCESSORYMIN <= kind && kind <= CRMATERIAL_ITEMKIND_ACCESSORYMAX){
		//---�A�N�Z�T��
		ItemWin.DrawText("�s���͒ቺ:");
		sprintf(s,"%+3.1f%%",(double)pItem->GetAction() / 10.0);
		ItemWin.SetColor(CRCOLOR_GREEN);
		ItemWin.DrawText(s);
		ItemWin.SetColor(CRCOLOR_WHITE);
		ItemWin.AddReturn();
	}

	ItemWin.Refresh();
}

void crshopDrawCharaWindow(CrStringWindow *pString,CrItem *pItem)
{
	int a,b,before[2],after;
	CrCharacter *pChara;

	pString->Paint();
	pString->Reset();

	int kind = pItem->GetMaterialKind() ;
	CrItem *pBeforeItem[2];
	char empty[12] = "         ";
	char s[80];

	pString->SetColor(CRCOLOR_WHITE);
	if(CRMATERIAL_ITEMKIND_WEAPONMIN <= kind && kind <= CRMATERIAL_ITEMKIND_WEAPONMAX){
		//---����
		pString->DrawText("           �U����");
	} else if(CRMATERIAL_ITEMKIND_ARMORMIN <= kind && kind <= CRMATERIAL_ITEMKIND_HELMETMAX){
		//---�h��
		pString->DrawText("          �h��@���h");
	}

//	pString->DrawText("           �U��  �h��");
	pString->AddReturn();
	if(pItem != NULL){
		for(a = 0;a < MEMBER_MAX;a ++){
			pChara = crcharaGetPartyMember(a);
			if(pChara == NULL)
				continue;

			pString->SetColor(CRCOLOR_WHITE);
			pString->DrawText(pChara->GetName());
//			pString->DrawText(&empty[12 - (strlen(pChara->GetName()) - 1)]);
			pString->DrawText(&empty[(strlen(pChara->GetName()) - 1)]);

			if(pItem->CanEquip(pChara->Who())){
				if(CRMATERIAL_ITEMKIND_WEAPONMIN <= kind && kind <= CRMATERIAL_ITEMKIND_WEAPONMAX){
					pBeforeItem[0] = critemGetItemClass(pChara->GetWeapon(0));
					pBeforeItem[1] = critemGetItemClass(pChara->GetWeapon(1));
					if(pItem->GetDamageStatus() == 0)
						//---�͂����Z���邩�ǂ���
						after = pChara->GetEqPower() + pItem->GetAtack();
					else
						after = pItem->GetAtack();
					for(b = 0;b < 2;b ++){
						before[b] = pChara->GetEqAtack(b);

						sprintf(s,"%+4d ",after - before[b]);

						if(pBeforeItem[b] == pItem){
							pString->SetColor(CRCOLOR_YELLOW);
							pString->DrawText("  �d ");
						} else if(before[b] < after){
							pString->SetColor(CRCOLOR_GREEN);
//							pString->DrawText("��");
							pString->DrawText(s);
						} else if(before[b] > after){
							pString->SetColor(CRCOLOR_RED);
//							pString->DrawText("��");
							pString->DrawText(s);
						} else {
							pString->SetColor(CRCOLOR_WHITE);
							pString->DrawText("  �� ");
						}
//						pString->DrawText("");
						pString->SetColor(CRCOLOR_WHITE);

					}
//					pString->DrawText("   �|");
					pString->AddReturn();
				//---�h��
				} else if(CRMATERIAL_ITEMKIND_ARMORMIN <= kind && kind <= CRMATERIAL_ITEMKIND_HELMETMAX){
					if(CRMATERIAL_ITEMKIND_ARMORMIN <= kind && kind <= CRMATERIAL_ITEMKIND_ARMORMAX){
						pBeforeItem[0] = critemGetItemClass(pChara->GetProtector(0));
					} else if(CRMATERIAL_ITEMKIND_SHIELDMIN <= kind && kind <= CRMATERIAL_ITEMKIND_SHIELDMAX){
						pBeforeItem[0] = critemGetItemClass(pChara->GetProtector(1));
					} else if(CRMATERIAL_ITEMKIND_HELMETMIN <= kind && kind <= CRMATERIAL_ITEMKIND_HELMETMAX){
						pBeforeItem[0] = critemGetItemClass(pChara->GetProtector(2));
					}
					after = pChara->GetEqDefense() - pBeforeItem[0]->GetDefense() + pItem->GetDefense();
					before[0] = pChara->GetEqDefense();

					sprintf(s,"%+4d ",after - before[0]);

					if(pBeforeItem[0] == pItem){
						pString->SetColor(CRCOLOR_YELLOW);
						pString->DrawText("  �d ");
					} else if(before[0] < after){
						pString->SetColor(CRCOLOR_GREEN);
						pString->DrawText(s);
					} else if(before[0] > after){
						pString->SetColor(CRCOLOR_RED);
						pString->DrawText(s);
					} else {
						pString->SetColor(CRCOLOR_WHITE);
						pString->DrawText("  �� ");
					}
					pString->SetColor(CRCOLOR_WHITE);
			//------------------------------------
					after = pChara->GetMagicDefense() - pBeforeItem[0]->GetMagicDefense() + pItem->GetMagicDefense();
					before[0] = pChara->GetMagicDefense();

					sprintf(s,"%+4d ",after - before[0]);

					if(pBeforeItem[0] == pItem){
						pString->SetColor(CRCOLOR_YELLOW);
						pString->DrawText("  �d ");
					} else if(before[0] < after){
						pString->SetColor(CRCOLOR_GREEN);
						pString->DrawText(s);
					} else if(before[0] > after){
						pString->SetColor(CRCOLOR_RED);
						pString->DrawText(s);
					} else {
						pString->SetColor(CRCOLOR_WHITE);
						pString->DrawText("  �� ");
					}
					pString->SetColor(CRCOLOR_WHITE);

					pString->AddReturn();
				} else if(CRMATERIAL_ITEMKIND_ACCESSORYMIN <= kind && kind <= CRMATERIAL_ITEMKIND_ACCESSORYMAX){
					pString->AddReturn();
				}
			} else {
				pString->SetColor(CRCOLOR_GRAY);
				pString->DrawText("�����s��");
				pString->AddReturn();
			}
		}
	}
}

//-----------------------------------------------
//---�R�[���o�b�N
void crshopCallBack(CrSelectWindow *pwin,eiCell *pCell,ei_u32 data)
{
	MATERIALWINDOW_STYLE *pmaterial = (MATERIALWINDOW_STYLE *)data;
	int *pItems = (int *)pmaterial->Data[0];
	int index = pItems[pmaterial->Index];

	crshopDrawCharaWindow((CrStringWindow *)pmaterial->Data[1],
		critemGetItemClass(index));
	crshopShowItemInfo(critemGetItemClass(index),index);

/*	crmainMenuEquip_DrawStatusWindow((CrCharacter *)pmaterial->Data[0],
		(CrStringWindow *)pmaterial->Data[1],
		critemGetItemClass(pmaterial->pIndex[index]),
		(CrItem *)pmaterial->Data[2]);
*/
	((CrStringWindow *)pmaterial->Data[1])->Refresh();
}

void crshopShowMoney(void)
{
	crbaseShowMoney(32,32);
}

//---���蕨�E�B���h�E�����
void crshopCreateShopItems(int *pItems)
{
	static int option[] = {CRMATERIAL_KIND_ITEMVALUE , 0 , 0 , 0};
	static CrSelectWindow MenuWindow;
	static CrStringWindow CharaWindow;
	static CrMessageWindow Help;
	static CRWIN_SELECTINFO info;
	static int Items[32];
	int MaxIndex = 0,*p = pItems,index = 0;

	pMenuWindow = &MenuWindow;
	pCharaWindow = &CharaWindow;
	pShopHelp = &Help;

	//---�A�C�e���C���f�b�N�X�̍ő�������߂�
	memset(&Items[0],0,sizeof(Items));
	while(*p != -1){
		Items[MaxIndex] = *p;
		MaxIndex ++;
		p ++;
	}

	memset(&info,0,sizeof(info));
	memset(&ShopStyle,0,sizeof(ShopStyle));
	ShopStyle.Style = MATERIALWINDOW_STYLE_ITEMICON;
	//---index
	ShopStyle.pIndex = &Items[0];//&pGameInfo->Item[0];
	ShopStyle.IndexMax = MaxIndex;//ITEM_MAX;
//	Style.pSubItem[0] = &pGameInfo->ItemCount[0];
	//---material
	ShopStyle.pMaterial = pItemInfo;
	ShopStyle.MaterialMax = ITEMMATERIAL_MAX;
	//---page
	if(MaxIndex <= 12)
		ShopStyle.PageSize = MaxIndex;//12;
	else
		ShopStyle.PageSize = 12;
	ShopStyle.WindowHeight = 12;

	//---option
	ShopStyle.Option = &option[0];

	//---help
	ShopStyle.pHelpWindow = pShopHelp;
	//---callback
	ShopStyle.pCallBack = crshopCallBack;
	//---�����m�F�E�B���h�E
	pCharaWindow->Create(32,288,12,10);

	//---data 
	ShopStyle.Data[0] = (ei_u32)&Items[0];
	ShopStyle.Data[1] = (ei_u32)pCharaWindow;
	ShopStyle.Data[2] = 0;//(ei_u32 *)critemGetItemClass(before_item);

	index = crmateCreateMaterialWindow( pMenuWindow,
		256,32,1,
		0/*mode*/,&info,&ShopStyle);
}

//---������̕\��
void crshopShowShopItems(SHOP_INFO *pInfo)
{
	crshopCreateShopItems(pInfo->pItems);
	pMenuWindow->Paint();
}

//---���蕨�I��
void crshopSelectShopItems(SHOP_INFO *pInfo)
{
//	crbaseMenuReset();
	crshopCreateShopItems(pInfo->pItems);

	ew->Refresh();
	crbaseMenuStart();
	int index = pMenuWindow->Select(&ShopBuy);

	if(index == -1){
		pInfo->Select = index;
		return;
	}
	if(index >= pInfo->IndexCount){
		pInfo->Select = -1;
		return;
	}
		
	index = index + ShopStyle.Page * ShopStyle.PageSize;

	pInfo->Select = index;
}

//---�����I
void crshopBuyShopItems(SHOP_INFO *pInfo)
{
	CrItem *pItem = ::critemGetItemClass(pInfo->pItems[pInfo->Select]);
	int money = pInfo->Count * pItem->GetValue();

	crbaseAddMoney(-money);
	critemAddItem(pInfo->pItems[pInfo->Select],pInfo->Count);
}

//---����I
void crshopSellShopItems(SHOP_INFO *pInfo)
{
	CrItem *pItem = ::critemGetItemClass(pInfo->Select);
	int money = pInfo->Count * (pItem->GetValue() / 2);

	crbaseAddMoney(money);
	critemSubItem(pInfo->Select,pInfo->Count);

/*	if(pInfo->Select == 30){
		pGameInfo->Event[265] = 1;
	}*/
}

//---���I��
int crshopSelectItemCount(SHOP_INFO *pInfo,int mode)
{
	CrStringWindow win1,win2;
	CrItem *pItem;
	int hx = 0,x = 1,max = 50,index,having = 0;
	eistr s[100];
	CrInput ci;

	if(pInfo->Select == -1)
		//---�L�����Z������Ă����
		return -1;
	//---�k���A�C�e���Ȃ�Ζ߂�
	if(mode == 0){
		if(pInfo->pItems[pInfo->Select] == 0)
			return -1;
	} else {
		if(pInfo->Select == 0)
			return -1;
	}


	//---�莝���̐�
	if(mode == 0){
		index = ::critemSerchItem(pInfo->pItems[pInfo->Select]);
	} else {
		index = pInfo->Select;
	}

	if(index == -1){
		having = 0;
	} else {
		if(mode == 0)
			having = ::critemGetItemCount(pInfo->pItems[pInfo->Select]);
		else
			having = ::critemGetItemCount(index);
	}

	//---�I�����ꂽ�A�C�e��
	if(mode == 0){
		pItem = ::critemGetItemClass(pInfo->pItems[pInfo->Select]);
		crshopShowItemInfo(pItem,pInfo->pItems[pInfo->Select]);

		//---��������̏��
		if(pItem->GetValue() != 0)
			max = crbaseGetMoney() / pItem->GetValue();
		else
			max = ITEMCOUNT_MAX;
		if(max > ITEMCOUNT_MAX)
			max = ITEMCOUNT_MAX;
		if(max > ITEMCOUNT_MAX - having){
			max = ITEMCOUNT_MAX - having;
		}
		if(pInfo->Mode & SHOPMODE_BUY_ONLYONE){
			max = 1;
		}
		if(max == 0){
			//---�����Ȃ�
			crbaseMenuReset();
			win1.Create(160,64,19,5);
			win1.AddReturn();
			if(having == ITEMCOUNT_MAX)
				win1.DrawText("        ����ȏ㎝�Ă܂���I�I");
			else
				win1.DrawText("        ����������܂���I�I");
			ew->Refresh();
			crbaseMenuStart();
			ci.WaitAnykey();

			return 0;
		}
	} else {
		pItem = ::critemGetItemClass(pInfo->Select);
		max = ::critemGetItemCount(pInfo->Select);
	}

	crbaseMenuReset();

//	win1.Create(160,64,19,5);
//	win2.Create(160,160,19,6);
	win1.Create(272,64,19,5);
	win2.Create(272,160,19,6);
	ew->Refresh();
	crbaseMenuStart();

	while(1){
		ci.Get();
		if(ci.IsButton(0)){
			crsoundPlay(CRSOUND_BTN_A);
			return -1;
		}
		if(ci.IsButton(1)){
			crsoundPlay(CRSOUND_BTN_B);
			break;
		}

		if(ci.IsDown()){
			x --;
		} else if(ci.IsLeft()){
			x -= 5;
		} else if(ci.IsUp()){
			x ++;
		} else if(ci.IsRight()){
			x += 5;
		}

		if(x < 1)
			x = max;
		if(x > max)
			x = 1;

		if(x != hx){
			crsoundPlay(CRSOUND_COUNT_1);

			//---��ʂ�`��
			win1.Reset();
			win1.Paint();
			win2.Reset();
			win2.Paint();

			win1.SetColor(CRCOLOR_WHITE);
			sprintf(&s[0],"   %-26s",pItem->GetName());
			win1.AddReturn();
			win1.DrawText(s);
			//---��
			win1.SetColor(CRCOLOR_YELLOW);
			sprintf(&s[0],"%3d��",x);
			win1.DrawText(s);

			ew->lpCell[1]->DrawLine(
				win1.xGetTop() + 32,
				win1.yGetTop() + 45,
				win1.xGetTop() + 288,
				win1.yGetTop() + 45,
				ep->ToRGB(CRCOLOR_WHITE));

			win1.SetColor(CRCOLOR_WHITE);
			win1.AddReturn();
			win1.DrawText("                  �l�i�F");
			if(mode == 0)
				sprintf(&s[0],"%8d",pItem->GetValue() * x);
			else
				sprintf(&s[0],"%8d",(pItem->GetValue() / 2) * x);
			win1.SetColor(CRCOLOR_GREEN);
			win1.DrawText(s);

			win2.SetColor(CRCOLOR_WHITE);
			win2.AddReturn();
			sprintf(&s[0],"                �����Ă��鐔 ");
			win2.DrawText(s);
			win2.SetColor(CRCOLOR_GREEN);
			sprintf(&s[0],"%3d��",having);
			win2.DrawText(s);

			win2.SetColor(CRCOLOR_WHITE);
			sprintf(&s[0],"                    �����Ō��I��");
			win2.AddReturn();
			win2.AddReturn();
			win2.DrawText(s);

			win1.Refresh();
			win2.Refresh();
		}

		hx = x;
		eiSleep(1);
	}

	pInfo->Count = x;

	return 1;
}

//---����A�C�e����I��
int crshopSelectSellItem(SHOP_INFO *pInfo)
{
	int index = critemSelectItem(
		256,32,10,1,
		CRMATERIAL_KIND_ITEMCOUNT,CRMATERIAL_KIND_ITEMSELLVALUE,0,0,0,&ShopSell);

	pInfo->Select = index;

	return index;
}

//---�s���I��
int crshopSelectBuyOrSall(void)
{
	CrSelectWindow win;

	crbaseMenuReset();
	win.Create(32,80,12,6,"�ǂ�����H"," ���� ; ���� ; �o�� ;",1,12);
	ew->Refresh();
	crbaseMenuStart();

	return win.Select(&ShopMenu);
}

int crshopYesNo(SHOP_INFO *pShopInfo,eistr *pString)
{
	int result;
	CrSelectWindow win;
	char str[100];

	crbaseMenuReset();
	sprintf(str,"%s �𔄂�H",critemGetItemClass(pShopInfo->Select)->GetName());
	win.Create(288,72,14,5,str,"����;����σ_���I;");
	win.Refresh();
	crbaseMenuStart();
	result = win.Select();
	if(result == 0){
		result = 1;
	} else {
		result = 0;
	}

	return result;
}

//---�V���b�v�֐�
CRBASE_SHOPAPI int crshopIntoShop(int *pShopItem,int mode /*= 0*/,void (*pCallback)(void) /*= NULL*/)
{
	int action,result;
	CrSelectWindow items;
	SHOP_INFO ShopInfo;
	int a,ShopItems[32];

	a = 0;
	memset(&ShopItems[0],0,sizeof(ShopItems));
	memset(&ShopBuy,0,sizeof(ShopBuy));
	memset(&ShopSell,0,sizeof(ShopSell));
	memset(&ShopMenu,0,sizeof(ShopMenu));
	do {
		ShopItems[a] = *pShopItem;
		pShopItem ++;
		a ++;
	} while(*(pShopItem - 1) != -1);
	ShopInfo.pItems = &ShopItems[0];//pShopItem;
	ShopInfo.IndexCount = a - 1;
	ShopInfo.Mode = mode;

	crbaseInitMenuScene();
	crbaseClearScreen(0x02);

	while(1){
		//---�ĕ`��
		crshopShowMoney();
		crshopShowShopItems(&ShopInfo);

		//---�s���I��
		action = crshopSelectBuyOrSall();
		if(action == 2 || action == -1)
			//---�X����o��
			break;

		crbaseMenuReset();
		if(action == 0){
			while(1){
				//---�����I
				crbaseClearScreen(0x02);
				crshopShowMoney();
				crshopSelectShopItems(&ShopInfo);
				if(ShopInfo.Select == -1)
					break;
				if(ShopInfo.pItems[ShopInfo.Select] == 240){
					//---�K�т����I
					crbaseEndMenuScene();
					(*pCallback)();
					return 0;
				}

				result = crshopSelectItemCount(&ShopInfo,0);
				crbaseMenuReset();
				if(result == 1){
					//---�i����I��ŁA�����I��ł���΁A����
					crshopBuyShopItems(&ShopInfo);
					continue;
				} else if(result == 0){
					//---����������Ȃ����
					continue;
				} else if(result == -1){
					//---�L�����Z��
					continue;
				}
				break;
			}
		} else if(action == 1){
			//---����
			do {
				result = 0;
				crbaseClearScreen(0x02);
				crshopShowMoney();

				if(crshopSelectSellItem(&ShopInfo) == -1)
					break;
				result = crshopSelectItemCount(&ShopInfo,1);
				if(result != -1){
					result = crshopYesNo(&ShopInfo,"�����Ă����ł��傤���H");
				}

				if(result == 1){
					//---����
					crshopSellShopItems(&ShopInfo);
					et->Reset();
					CrStringWindow stwin;
					stwin.Create(288,80,14,5);
					stwin.Paint();
					stwin.AddReturn();
					stwin.DrawText("  ���肪�Ƃ��������܂��I");
					stwin.Refresh();
					et->Wait2(500);
					result = 0;
				}
				crbaseMenuReset();

			} while(result != 1);
		}

		crbaseMenuReset();
		crbaseClearScreen(0x02);
	}

	crbaseEndMenuScene();

	return action;
}
