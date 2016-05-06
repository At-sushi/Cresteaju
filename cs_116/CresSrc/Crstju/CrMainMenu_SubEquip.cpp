#define STLEVEL "レベル"
#define STLP "LP"
#define STMC "MC"
#define STLP_L "ＬＰ"
#define STMC_L "ＭＣ"
#define STEXP "経験値"
#define STNEXTEXP "次のレベルまで"
#define STMEXP "魔法修得値"
#define STKOUGEKI "攻撃力"
#define STBOUGYO "防御力"
#define STMBOUGYO "魔法防御"
#define STKOUDOU "行動力"

#define STCHIKARA "力"
#define STSUBAYASA "素早さ"
#define STTAIRYOKU "体力"
#define STMARYOKU "魔力"
#define STSEISHINRYOKU "精神力"
#define STKAIHI "回避率"
#define STMKAIHI "魔法回避"
#define STMEICHU "命中率"

typedef struct
{
	CrSelectWindow *pSelect;
	CrStringWindow *pStatus;
	CrCharacter *pChara;
	int member,kind;
} EQUIPCALLBACK_INFO;

void crmainMenuEquip_DrawStatusWindow(CrCharacter *pChara,CrStringWindow *pStatus,
									  CrItem *pItem = NULL,CrItem *pBeforeItem  = NULL,int kind = -1);
void crmainMenuEquip_DrawSelectWindow(CrCharacter *pChara,EQUIPCALLBACK_INFO *peqinfo);
void crmainMenuEquip_CreateStatusWindow(CrCharacter *pChara,EQUIPCALLBACK_INFO *peqinfo);
void crmainMenuEquip_CreateSelectWindow(CrCharacter *pChara,
			EQUIPCALLBACK_INFO *peqinfo);

//-----------------------------------------------
//---指定された種類のアイテムを選択
void crmainMenuEquip_SortItem(CrCharacter *pChara,
							  ei_s32 *pIndex,ei_s32 *pCount,int min,int max)
{
	int a,item,size,count;
	ei_s32 *pStart = pIndex,*pCountStart = pCount;
	static ei_s32 temp[ITEM_MAX],temp2[ITEM_MAX];

	memset(pIndex,0,sizeof(ei_s32) * ITEM_MAX);
	memset(pCount,0,sizeof(ei_s32) * ITEM_MAX);

	memset(temp,0,sizeof(temp));
	memset(temp2,0,sizeof(temp2));

	for(a = 0 , size = 0;a < ITEM_MAX;a ++){
		item = critemGetItemIndex(a);
		count = critemGetItemIndexCount(a);

		CrItem *pItem = critemGetItemClass(item);

		if(pItem->CanEquip(pChara->Who())
			&& min <= pItem->GetKind() && pItem->GetKind() <= max){
			//---条件にあっていれば
			*pIndex = item;
			*pCount = count;
			temp[size] = item;
			temp2[size] = count;

			pIndex ++;
			pCount ++;
			size ++;
		}
	}

	//---攻撃力、防御力順にソートする
	if(max <= CRMATERIAL_ITEMKIND_WEAPONMAX){
		crmateSortMaterial(pStart,size,
			pItemInfo,SORTMATERIAL_ATACK | SORTMATERIAL_REVERSE);
	} else if(max <= CRMATERIAL_ITEMKIND_PROTECTORMAX){
		crmateSortMaterial(pStart,size,
			pItemInfo,SORTMATERIAL_DEFENSE | SORTMATERIAL_REVERSE);
	}

	//---個数並び替え
	int b;
	for(a = 0;a < size;a ++){
		for(b = 0;b < size;b ++){
			if(pStart[a] == temp[b]){
				pCountStart[a] = temp2[b];
				continue;
			}
		}
	}
}

void crmainMenuEquip_DrawSubItem(CrSelectWindow *psel,int kind)
{
//---値説明
	int tx = psel->xGetTop() + 240,ty = psel->yGetTop() + 1;
	int old = eiSetFont(EISMALL_FONT);

	if(kind <= 1){
		ew->lpCell[1]->DrawFillBox(tx ,ty,
			tx + 15 * 6,ty + 12,
			ep->ToRGB(CRCOLOR_BLACK));
		ew->lpCell[1]->DrawText("攻撃力   命中率",
			tx,ty,
			ep->ToTextRGB(CRCOLOR_WHITE),EI_PSET);
	} else if(kind <= 4){
		ew->lpCell[1]->DrawFillBox(tx ,ty,
			tx + 15 * 6,ty + 12,
			ep->ToRGB(CRCOLOR_BLACK));
		ew->lpCell[1]->DrawText("防御力   回避率",
			tx,ty,
			ep->ToTextRGB(CRCOLOR_WHITE),EI_PSET);
	}

	eiSetFont(old);
}

//-----------------------------------------------
//---コールバック
void crmainMenuEquip_CallBack(CrSelectWindow *psel,eiCell *pCell,ei_u32 data)
{
	MATERIALWINDOW_STYLE *pmaterial = (MATERIALWINDOW_STYLE *)data;
	int index = pmaterial->Index,kind = (int)pmaterial->Data[3];
	CrStringWindow *pwin = (CrStringWindow *)pmaterial->Data[1];

	crmainMenuEquip_DrawStatusWindow((CrCharacter *)pmaterial->Data[0],
		(CrStringWindow *)pmaterial->Data[1],
		/*pmaterial->pIndex[index] == 0 ? NULL :*/ critemGetItemClass(pmaterial->pIndex[index]),
		(CrItem *)pmaterial->Data[2],
		(int)pmaterial->Data[3]);

//	crmainMenuEquip_DrawSubItem(psel,kind);

	((CrStringWindow *)pmaterial->Data[1])->Refresh();
}

//---コールバック
int crmainMenuEquip_SelectEquipmentCallBack(
			CrSelectWindow *pwin,eiCell *pCell,
			int Message,ei_u32 Param1,ei_u32 Param2,int Param3)
{
	int *pPage = (int *)Param1,page;
	EQUIPCALLBACK_INFO *peqinfo = (EQUIPCALLBACK_INFO *)Param2;

	if(Message == CRWIN_SELECT_MESMOVECURSOR){
		//---アイテム説明
		CrMessageWindow help;
		int index = Param3;
		CrItem *pItem = NULL;
		
		if(index < 7){
			pItem = critemGetItemClass(peqinfo->pChara->GetEquipment(index));
		}

		help.Create(240 + 16,224 - 8,24,4);
//		help.Create(496,72,8,12);
		if(pItem != NULL){
			help.SetOffset(16,8);
			help.Message(pItem->GetHelp());
			help.Draw(-1,0,0);
		}
		help.Refresh();
		return 1;
	}
	if(Message == CRWIN_SELECT_MESSHOWHELP){
		return 1;
	} else if(Message == CRWIN_SELECT_MESCHANGEPAGE){
		//---ページ切り替え
		page = *pPage + Param3;
		while(crcharaGetPartyMember(page) == NULL){
			page += Param3;
			if(page > MEMBER_MAX)
				page = 0;
			else if(page < 0)
				page = MEMBER_MAX - 1;
		}
		*pPage = page;
		peqinfo->pChara = crcharaGetPartyMember(page);
		peqinfo->member = page;

		crmainMenuEquip_CreateSelectWindow(peqinfo->pChara,peqinfo);
		crmainMenuEquip_CreateStatusWindow(peqinfo->pChara,peqinfo);

		crmainMenuEquip_DrawSelectWindow(peqinfo->pChara,peqinfo);
		crmainMenuEquip_DrawStatusWindow(peqinfo->pChara,peqinfo->pStatus);

		ew->Refresh();
		return 1;
	} else if(Message == CRWIN_SELECT_MESPAINT){
	}

	//---処理しなかった場合
	return 0;
}

//---最強
void crmainMenuEquip_Saikyo(CrCharacter *pChara,int mode)
{
	int a,b,value,sel_value,selected,item_count = 0,kind_start = 0,kind_end;
	static int item_table[ITEM_MAX];
	int kind,sel_kind,
		kind_table[] = {
		CRMATERIAL_ITEMKIND_WEAPONMIN,CRMATERIAL_ITEMKIND_WEAPONMAX,
		CRMATERIAL_ITEMKIND_WEAPONMIN,CRMATERIAL_ITEMKIND_WEAPONMAX,
		CRMATERIAL_ITEMKIND_KNIFE,CRMATERIAL_ITEMKIND_MIDDLESWORD,
		CRMATERIAL_ITEMKIND_LARGESWORD,CRMATERIAL_ITEMKIND_LARGESWORD,
		CRMATERIAL_ITEMKIND_GUN,CRMATERIAL_ITEMKIND_SPGUN,
		0,0,
		0,0,
		0,0,

		CRMATERIAL_ITEMKIND_ARMORMIN,CRMATERIAL_ITEMKIND_ARMORMAX,
		CRMATERIAL_ITEMKIND_SHIELDMIN,CRMATERIAL_ITEMKIND_SHIELDMAX,
		CRMATERIAL_ITEMKIND_HELMETMIN,CRMATERIAL_ITEMKIND_HELMETMAX
	};

	if(mode == 0){
		kind_start = 0;
	} else if(mode == 1){
		kind_start = EQ_WEAPON_MAX;
	}
	kind_end = EQ_WEAPON_MAX + EQ_PROTECTOR_MAX;

	//---ひとまず、アクセサリー以外外す
	for(a = kind_start;a < kind_end;a ++){
		critemAddItem(pChara->GetEquipment(a),1);
		pChara->SetEquipment(a,0);
	}

	memset(item_table,0,sizeof(item_table));

	for(a = kind_start;a < kind_end;a ++){
		//---種類ごとにアイテムを集める
		item_count = 0;
		sel_kind = a;

		if(a < EQ_WEAPON_MAX){
			switch(pChara->Who()){
			case 1:
				//---ルナン
				if(a == 0)
					sel_kind = 2;
				if(a == 1)
					sel_kind = 4;
				break;
			case 2:
				//---ディザ
				if(a == 0)
					sel_kind = 2;
				if(a == 1)
					sel_kind = 3;
				break;
			case 3:
				//---ナック
				if(a == 0)
					sel_kind = 0;
				if(a == 1)
					sel_kind = 7;
				break;
			case 4:
				//---サヴィアー
				if(a == 0)
					sel_kind = 4;
				if(a == 1)
					sel_kind = 2;
				break;
			case 5:
				//---ユミ
				if(a == 0)
					sel_kind = 0;
				if(a == 1)
					sel_kind = 7;
				break;
			case 6:
				//---ライゼル
				if(a == 0)
					sel_kind = 3;
				if(a == 1)
					sel_kind = 0;
				break;
			case 7:
				//---シンディ
				if(a == 0)
					sel_kind = 2;
				if(a == 1)
					sel_kind = 4;
				break;
			}
			sel_kind *= 2;
		} else {
			//---防具
			sel_kind = 8 + (a - EQ_WEAPON_MAX);
			sel_kind *= 2;
		}

		for(b = 0;b < ITEM_MAX;b ++){
			kind = critemGetItemClass(critemGetItemIndex(b))->GetKind();

			if(kind_table[sel_kind] <= kind && kind <= kind_table[sel_kind + 1]){
				//---同じ種類なら
				if(critemGetItemClass(critemGetItemIndex(b))->CanEquip(pChara->Who())){
					//---装備できれば
					item_table[item_count] = critemGetItemIndex(b);
					item_count ++;
				}
			}
		}

		if(item_count == 0)
			//---もし、その種類のアイテムがなにもなかったら
			continue;

		selected = 0;
		for(b = 1;b < item_count;b ++){
			if(a < EQ_WEAPON_MAX){
				value = critemGetItemClass(item_table[b])->GetAtack();
				sel_value = critemGetItemClass(item_table[selected])->GetAtack();
			} else {
				value = critemGetItemClass(item_table[b])->GetDefense();
				sel_value = critemGetItemClass(item_table[selected])->GetDefense();
			}
			if(value > sel_value){
				//---いま調べた方が強かったら
				selected = b;
			}
		}

		//---選ばれたのを装備
		pChara->SetEquipment(a,item_table[selected]);
		if(item_table[selected] != 0){
			critemSubItem(item_table[selected]);
		} else {
		}
	}
}

//---アイテム選択
int crmainMenuEquip_SelectItem(CrCharacter *pChara,CrStringWindow *pString,int kind,int before_item,int sx,int sy,int number)
{
	static ei_s32 ItemIndex[ITEM_MAX],ItemCount[ITEM_MAX];
	int index,option[] = {0 , 0 , 0 , 0};
	CrSelectWindow menu;
	CrMessageWindow help;
	MATERIALWINDOW_STYLE Style;
	int KindTable[] = {
		CRMATERIAL_ITEMKIND_WEAPONMIN,CRMATERIAL_ITEMKIND_WEAPONMAX,
		CRMATERIAL_ITEMKIND_ARMORMIN,CRMATERIAL_ITEMKIND_ARMORMAX,
		CRMATERIAL_ITEMKIND_SHIELDMIN,CRMATERIAL_ITEMKIND_SHIELDMAX,
		CRMATERIAL_ITEMKIND_HELMETMIN,CRMATERIAL_ITEMKIND_HELMETMAX,
		CRMATERIAL_ITEMKIND_ACCESSORYMIN,CRMATERIAL_ITEMKIND_ACCESSORYMAX
	};
	int a,pagesize,last_index;

	//---必要なアイテムを選び出す
	crmainMenuEquip_SortItem(pChara,&ItemIndex[0],&ItemCount[0],KindTable[kind * 2],KindTable[(kind * 2) + 1]);

	memset(&Style,0,sizeof(Style));

	option[0] = CRMATERIAL_KIND_ITEMCOUNT;
	if(kind == 0){
		//---武器
		option[1] = CRMATERIAL_KIND_ITEMATACK;
		option[2] = CRMATERIAL_KIND_ITEMHITPROB;
	} else /*if(kind <= 3)*/{
		//---防具
		option[1] = CRMATERIAL_KIND_ITEMDEFENSE;
		option[2] = CRMATERIAL_KIND_ITEMAVOIDPROB;
	}
//		option[1] = CRMATERIAL_KIND_ITEMATACK;
//		option[2] = CRMATERIAL_KIND_ITEMHITPROB;

	//---アイテムリストのサイズを求める
	pagesize = 6;
	for(a = 0,last_index = 0;a < ITEM_MAX;a ++){
		if(ItemIndex[a]){
			last_index = a + 1;
		}
	}
	if(last_index == 0)
		last_index = 1;
	last_index = ((last_index / pagesize) 
		+ ((last_index % pagesize) != 0 ? 1: 0)) * pagesize;

	Style.Style = MATERIALWINDOW_STYLE_ITEMICON;
	//---index
	Style.pIndex = &ItemIndex[0];
	Style.IndexMax = last_index;
//	Style.pSubItem[0] = &pGameInfo->ItemCount[0];
	Style.pSubItem[0] = &ItemCount[0];
	//---material
	Style.pMaterial = pItemInfo;
	Style.MaterialMax = ITEMMATERIAL_MAX;
	//---page
	Style.PageSize = pagesize;//6;
	//---option
	Style.Option = &option[0];
	Style.ShowOption = 1;
	//---data 
	Style.Data[0] = (ei_u32)pChara;
	Style.Data[1] = (ei_u32)pString;
	Style.Data[2] = (ei_u32)critemGetItemClass(before_item);
	Style.Data[3] = number;

	//---help
	Style.pHelpWindow = &help;
	//---callback
	Style.pCallBack = crmainMenuEquip_CallBack;

//	pItemInfo[0].GetMaterialKind();

	index = crmateCreateAndSelectMaterialWindow(&menu,
		sx,sy,1,
		0/*mode*/,NULL/*info*/,&Style);

	if(index == -1)
		return -1;

	return ItemIndex[index];
}


//-----------------------------------------------
//---装備ウィンドウを作る
void crmainMenuEquip_CreateSelectWindow(CrCharacter *pChara,
			EQUIPCALLBACK_INFO *peqinfo)
{
	int a;
	static eistr buf[512];
	eistr title[64];
	eistr *p = &buf[0],temp[64],empty[MATERIALWINDOW_STRINGSIZE + 1],
		*ProtectName[] = {" 体 "," 盾 "," 頭 "};
	CrItem *pItem;

	//---空文字列初期化
	memset(&empty[0],' ',sizeof(empty));
	empty[MATERIALWINDOW_STRINGSIZE] = 0;

	//---武器
	for(a = 0;a < EQ_WEAPON_MAX;a ++){
		pItem = critemGetItemClass(pChara->GetWeapon(a));
		sprintf(&temp[0],"\\4武器:\\7 %s%s  \\4%4d\\7 , \\6%2d%%\\7;",
			pItem->GetName(),
			&empty[strlen(pItem->GetName())],
			pChara->CalcAtack(pItem),pItem->GetHitProb() / 10);
		sprintf(p,"%s",temp);

		p += strlen(temp);
	}
	//---防具
	for(a = 0;a < EQ_PROTECTOR_MAX;a ++){
		pItem = critemGetItemClass(pChara->GetProtector(a));
		sprintf(&temp[0],"\\6%s:\\7 %s%s  \\4%4d\\7 , \\6%2d%%\\7;",
			ProtectName[a],
			pItem->GetName(),
			&empty[strlen(pItem->GetName())],
			pItem->GetDefense(),pItem->GetAvoidProb() / 10);
		sprintf(p,"%s",temp);

		p += strlen(temp);
	}
	//---アクセサリー
	for(a = 0;a < EQ_ACCESSORY_MAX;a ++){
		pItem = critemGetItemClass(pChara->GetAccessory(a));
		sprintf(&temp[0],"\\5装飾:\\7 %s%s ;",//\\4%4d\\7 , \\6%2d%%\\7;",
			pItem->GetName(),
			&empty[strlen(pItem->GetName())]);
		sprintf(p,"%s",temp);

		p += strlen(temp);
	}

	sprintf(p,"      装備を最強にする;      防具を最強にする;");

	sprintf(title,"%-12s  ←人物切り替え→",peqinfo->pChara->GetName());

	peqinfo->pSelect->Create(32,48,28,14,title,//peqinfo->pChara->GetName(),
		buf,1,24);
	peqinfo->pSelect->SetData((ei_u32)peqinfo);
	peqinfo->pSelect->SetSelectCallBack(crmainMenuEquip_SelectEquipmentCallBack);
}

//---ステータスウィンドウを作る
void crmainMenuEquip_CreateStatusWindow(CrCharacter *pChara,EQUIPCALLBACK_INFO *peqinfo)
{
	peqinfo->pStatus->Create(48,288,28,10);
}

//---装備ウィンドウを描く
void crmainMenuEquip_DrawSelectWindow(CrCharacter *pChara,EQUIPCALLBACK_INFO *peqinfo)
{
}

void crmainMenuEquip_DrawStatusWindow(CrCharacter *pChara,CrStringWindow *pStatus,
									  CrItem *pItem /*= NULL*/,CrItem *pBeforeItem /* = NULL*/,int kind /*= -1*/)
{
	int a,before[8],after[8];
	eistr *title[] = {STKOUGEKI,STBOUGYO,STMBOUGYO,STKOUDOU,
		STSEISHINRYOKU,STKAIHI,STMKAIHI},
		temp[64];

	pStatus->Reset();
	pStatus->Paint();

	for(a = 0;a < 7;a ++){
		sprintf(&temp[0],"%-10s:",title[a]);
		pStatus->SetColor(CRCOLOR_GREEN);
		pStatus->DrawText(temp);

		if(a == 0){
			before[a] = 0;
			if(kind == 0 || kind == 1)
				before[a] = pChara->GetEqAtack(kind);
		}
//		if(a == 0)
//			before[a] = pChara->GetEqPower();
		else if(a == 1)
			before[a] = pChara->GetEqDefense();
		else if(a == 2)
			before[a] = pChara->GetEqMagicDefense();
		else if(a == 3)
			before[a] = pChara->GetEqAction();
		else if(a == 4)
			before[a] = pChara->GetEqSoul();
		else if(a == 5)
			before[a] = pChara->GetEqAvoidProb() / 10;
		else if(a == 6)
			before[a] = pChara->GetEqMagicAvoidProb() / 10;

		if(a == 0 && (kind != 0 && kind != 1)){
			sprintf(&temp[0]," %4d / %4d",pChara->GetEqAtack(0),pChara->GetEqAtack(1));
			pStatus->SetColor(CRCOLOR_WHITE);
			pStatus->DrawText(temp);
		} else if(!(kind > 1 && a == 0)){
			sprintf(&temp[0]," %4d%s",before[a],a < 5 ? " ":"%");
			pStatus->SetColor(CRCOLOR_WHITE);
			pStatus->DrawText(temp);
		}

		if(pItem){
			//---能力変化後表示
			if(!(kind > 1 && a == 0)){
				pStatus->SetColor(CRCOLOR_WHITE);
				pStatus->DrawText("  → ");
			}

			if(a == 0){
//				after[a] = before[a] + pItem->GetPower() - pBeforeItem->GetPower();
				if(pItem->GetAtackKind() == 0){
					after[a] = pItem->GetAtack() + pChara->GetPower();
				} else {
					after[a] = pItem->GetAtack();
				}
			} else if(a == 1){
				after[a] = before[a] + pItem->GetDefense() - pBeforeItem->GetDefense();
			} else if(a == 2){
				after[a] = before[a] + pItem->GetMagicDefense() - pBeforeItem->GetMagicDefense();
			} else if(a == 3){
				int c,rate;
				for(c = 0,rate = 0;c < EQ_ALL_MAX;c ++){
					rate += pItemInfo[pChara->GetEquipment(c)].GetAction();
				}
				rate += (pItem->GetAction() - pBeforeItem->GetAction());
				after[a] =	(pChara->GetAgility() + (pChara->GetAgility() * rate / 1000));
//				after[a] = before[a] + pItem->GetAction() - pBeforeItem->GetAction();
			} else if(a == 4){
				after[a] = before[a] + pItem->GetSoul() - pBeforeItem->GetSoul();
			} else if(a == 5){
				after[a] = before[a] + (pItem->GetAvoidProb()) / 10 - (pBeforeItem->GetAvoidProb()) / 10;
			} else if(a == 6){
				after[a] = before[a] + (pItem->GetMagicAvoidProb()) / 10 - (pBeforeItem->GetMagicAvoidProb()) / 10;
			}

			if(after[a] < 0)
				after[a] = 0;

			if(before[a] < after[a])
				pStatus->SetColor(CRCOLOR_GREEN);
			else if(before[a] == after[a])
				pStatus->SetColor(CRCOLOR_WHITE);
			else
				pStatus->SetColor(CRCOLOR_RED);

			if(!(kind > 1 && a == 0)){
				sprintf(&temp[0]," %4d%s",after[a],a < 5 ? " ":"%");
				pStatus->DrawText(temp);
			}
		}

		pStatus->AddReturn();
	}
}

//---交換か外すかを選択
CRBASE_ITEMAPI int crmainMenuEquip_SelectAction(int sx,int sy,int item)
{
	int a;
	CrSelectWindow select;

	crbaseMenuReset();
	select.Create(sx,sy,15,6,critemGetItemClass(item)->GetName(),"装備;はずす;戻る;",1,14);
	ew->Refresh();
	crbaseMenuStart();

	a = select.Select();
	if(a == 2)
		a = -1;
	return a;
}

//---装備
int crmainMenuEquip(void)
{
	static CRWIN_SELECTINFO SelectInfo,MemberInfo;
	int sel,action = 0,item;
	CrSelectWindow select;
	CrStringWindow status;
	EQUIPCALLBACK_INFO eqinfo;

	eqinfo.member = 0;
	eqinfo.pChara = NULL;
	eqinfo.pSelect = &select;
	eqinfo.pStatus = &status;
	memset(&MemberInfo,0,sizeof(MemberInfo));
	memset(&SelectInfo,0,sizeof(SelectInfo));

	while(1){
		//---キャラ選択
		if(pGameInfo->TransWindow == 0){
			crmainClearMenu();
		}
		MemberInfo.Offset = eqinfo.member;
		eqinfo.member = crcharaSelectMember(32,32,0,"装備者選択",&MemberInfo);
		if(eqinfo.member == -1){
			break;
		}
		eqinfo.pChara = crcharaGetPartyMember(eqinfo.member);
		memset(&SelectInfo,0,sizeof(SelectInfo));
		SelectInfo.Page = eqinfo.member;

		//---装備画面
//SELECT_EQUIP:
		do {
			crbaseMenuReset();
//			crbaseClearScreen();
			if(pGameInfo->TransWindow == 0){
				RECT rect = {240,0,640,480};
				ew->lpCell[1]->SetClipingRect(&rect);
				crmainClearMenu();
				SetRect(&rect,0,0,640,480);
				ew->lpCell[1]->SetClipingRect(&rect);

//				ew->lpCell[1]->DrawFillBox(240,0,639,479,ep->ToRGB(CRCOLOR_BLACK));
			}

			crmainMenuEquip_CreateSelectWindow(eqinfo.pChara,&eqinfo);
			crmainMenuEquip_CreateStatusWindow(eqinfo.pChara,&eqinfo);

			crmainMenuEquip_DrawSelectWindow(eqinfo.pChara,&eqinfo);
			crmainMenuEquip_DrawStatusWindow(eqinfo.pChara,eqinfo.pStatus);

			//---装備品選択
			ew->Refresh();
			crbaseMenuStart();
			sel = eqinfo.pSelect->Select(&SelectInfo);
			if(sel == -1){
				break;
//				continue;
			}
			eqinfo.kind = sel;

			//---交換か外すか選択
			if(sel <= 6){
				action = crmainMenuEquip_SelectAction(224,48,eqinfo.pChara->GetEquipment(sel));
				if(action == -1)
					continue;
//					goto SELECT_EQUIP;
			} else if(sel == 7){
				//---最強
				crmainMenuEquip_Saikyo(eqinfo.pChara,0);
				continue;
//				goto SELECT_EQUIP;
			} else if(sel == 8){
				//---防具最強
				crmainMenuEquip_Saikyo(eqinfo.pChara,1);
				continue;
//				goto SELECT_EQUIP;
			}

			if(action == 0){
				//---装備するアイテムを選択
				int sel_kind;
					if(sel < EQ_WEAPON_MAX)
					sel_kind = 0;
				else if(sel < EQ_WEAPON_MAX + EQ_PROTECTOR_MAX)
					//---防具
					sel_kind = (sel - 1);
				else
					//---アクセサリー
					sel_kind = 4;
//				item = crmainMenuEquip_SelectItem(pChara,&status,sel <= 1 ? 0 : (sel - 1),pChara->GetEquipment(sel),240,48,sel);
				item = crmainMenuEquip_SelectItem(
					eqinfo.pChara,
					eqinfo.pStatus,sel_kind,
					eqinfo.pChara->GetEquipment(sel),240 + 16,48,sel);
			} else {
				item = 0;
			}

			if(item != -1){
				if(action == 0){
					//---交換
					critemAddItem(eqinfo.pChara->GetEquipment(sel),1);
					//---取り替え
					eqinfo.pChara->SetEquipment(sel,item);
					if(item != 0){
						//---アイテムの個数を減らす
						critemSubItem(item,1);
					}
				} else if(action == 1){
					//---外す
					critemAddItem(eqinfo.pChara->GetEquipment(sel),1);
					eqinfo.pChara->SetEquipment(sel,0);
				}
			}
			continue;
//			goto SELECT_EQUIP;
		} while(1);
	}

	return 1;
}
