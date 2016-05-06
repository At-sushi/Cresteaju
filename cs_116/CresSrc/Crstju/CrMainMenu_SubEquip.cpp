#define STLEVEL "���x��"
#define STLP "LP"
#define STMC "MC"
#define STLP_L "�k�o"
#define STMC_L "�l�b"
#define STEXP "�o���l"
#define STNEXTEXP "���̃��x���܂�"
#define STMEXP "���@�C���l"
#define STKOUGEKI "�U����"
#define STBOUGYO "�h���"
#define STMBOUGYO "���@�h��"
#define STKOUDOU "�s����"

#define STCHIKARA "��"
#define STSUBAYASA "�f����"
#define STTAIRYOKU "�̗�"
#define STMARYOKU "����"
#define STSEISHINRYOKU "���_��"
#define STKAIHI "���"
#define STMKAIHI "���@���"
#define STMEICHU "������"

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
//---�w�肳�ꂽ��ނ̃A�C�e����I��
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
			//---�����ɂ����Ă����
			*pIndex = item;
			*pCount = count;
			temp[size] = item;
			temp2[size] = count;

			pIndex ++;
			pCount ++;
			size ++;
		}
	}

	//---�U���́A�h��͏��Ƀ\�[�g����
	if(max <= CRMATERIAL_ITEMKIND_WEAPONMAX){
		crmateSortMaterial(pStart,size,
			pItemInfo,SORTMATERIAL_ATACK | SORTMATERIAL_REVERSE);
	} else if(max <= CRMATERIAL_ITEMKIND_PROTECTORMAX){
		crmateSortMaterial(pStart,size,
			pItemInfo,SORTMATERIAL_DEFENSE | SORTMATERIAL_REVERSE);
	}

	//---�����ёւ�
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
//---�l����
	int tx = psel->xGetTop() + 240,ty = psel->yGetTop() + 1;
	int old = eiSetFont(EISMALL_FONT);

	if(kind <= 1){
		ew->lpCell[1]->DrawFillBox(tx ,ty,
			tx + 15 * 6,ty + 12,
			ep->ToRGB(CRCOLOR_BLACK));
		ew->lpCell[1]->DrawText("�U����   ������",
			tx,ty,
			ep->ToTextRGB(CRCOLOR_WHITE),EI_PSET);
	} else if(kind <= 4){
		ew->lpCell[1]->DrawFillBox(tx ,ty,
			tx + 15 * 6,ty + 12,
			ep->ToRGB(CRCOLOR_BLACK));
		ew->lpCell[1]->DrawText("�h���   ���",
			tx,ty,
			ep->ToTextRGB(CRCOLOR_WHITE),EI_PSET);
	}

	eiSetFont(old);
}

//-----------------------------------------------
//---�R�[���o�b�N
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

//---�R�[���o�b�N
int crmainMenuEquip_SelectEquipmentCallBack(
			CrSelectWindow *pwin,eiCell *pCell,
			int Message,ei_u32 Param1,ei_u32 Param2,int Param3)
{
	int *pPage = (int *)Param1,page;
	EQUIPCALLBACK_INFO *peqinfo = (EQUIPCALLBACK_INFO *)Param2;

	if(Message == CRWIN_SELECT_MESMOVECURSOR){
		//---�A�C�e������
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
		//---�y�[�W�؂�ւ�
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

	//---�������Ȃ������ꍇ
	return 0;
}

//---�ŋ�
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

	//---�ЂƂ܂��A�A�N�Z�T���[�ȊO�O��
	for(a = kind_start;a < kind_end;a ++){
		critemAddItem(pChara->GetEquipment(a),1);
		pChara->SetEquipment(a,0);
	}

	memset(item_table,0,sizeof(item_table));

	for(a = kind_start;a < kind_end;a ++){
		//---��ނ��ƂɃA�C�e�����W�߂�
		item_count = 0;
		sel_kind = a;

		if(a < EQ_WEAPON_MAX){
			switch(pChara->Who()){
			case 1:
				//---���i��
				if(a == 0)
					sel_kind = 2;
				if(a == 1)
					sel_kind = 4;
				break;
			case 2:
				//---�f�B�U
				if(a == 0)
					sel_kind = 2;
				if(a == 1)
					sel_kind = 3;
				break;
			case 3:
				//---�i�b�N
				if(a == 0)
					sel_kind = 0;
				if(a == 1)
					sel_kind = 7;
				break;
			case 4:
				//---�T���B�A�[
				if(a == 0)
					sel_kind = 4;
				if(a == 1)
					sel_kind = 2;
				break;
			case 5:
				//---���~
				if(a == 0)
					sel_kind = 0;
				if(a == 1)
					sel_kind = 7;
				break;
			case 6:
				//---���C�[��
				if(a == 0)
					sel_kind = 3;
				if(a == 1)
					sel_kind = 0;
				break;
			case 7:
				//---�V���f�B
				if(a == 0)
					sel_kind = 2;
				if(a == 1)
					sel_kind = 4;
				break;
			}
			sel_kind *= 2;
		} else {
			//---�h��
			sel_kind = 8 + (a - EQ_WEAPON_MAX);
			sel_kind *= 2;
		}

		for(b = 0;b < ITEM_MAX;b ++){
			kind = critemGetItemClass(critemGetItemIndex(b))->GetKind();

			if(kind_table[sel_kind] <= kind && kind <= kind_table[sel_kind + 1]){
				//---������ނȂ�
				if(critemGetItemClass(critemGetItemIndex(b))->CanEquip(pChara->Who())){
					//---�����ł����
					item_table[item_count] = critemGetItemIndex(b);
					item_count ++;
				}
			}
		}

		if(item_count == 0)
			//---�����A���̎�ނ̃A�C�e�����Ȃɂ��Ȃ�������
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
				//---���ܒ��ׂ���������������
				selected = b;
			}
		}

		//---�I�΂ꂽ�̂𑕔�
		pChara->SetEquipment(a,item_table[selected]);
		if(item_table[selected] != 0){
			critemSubItem(item_table[selected]);
		} else {
		}
	}
}

//---�A�C�e���I��
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

	//---�K�v�ȃA�C�e����I�яo��
	crmainMenuEquip_SortItem(pChara,&ItemIndex[0],&ItemCount[0],KindTable[kind * 2],KindTable[(kind * 2) + 1]);

	memset(&Style,0,sizeof(Style));

	option[0] = CRMATERIAL_KIND_ITEMCOUNT;
	if(kind == 0){
		//---����
		option[1] = CRMATERIAL_KIND_ITEMATACK;
		option[2] = CRMATERIAL_KIND_ITEMHITPROB;
	} else /*if(kind <= 3)*/{
		//---�h��
		option[1] = CRMATERIAL_KIND_ITEMDEFENSE;
		option[2] = CRMATERIAL_KIND_ITEMAVOIDPROB;
	}
//		option[1] = CRMATERIAL_KIND_ITEMATACK;
//		option[2] = CRMATERIAL_KIND_ITEMHITPROB;

	//---�A�C�e�����X�g�̃T�C�Y�����߂�
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
//---�����E�B���h�E�����
void crmainMenuEquip_CreateSelectWindow(CrCharacter *pChara,
			EQUIPCALLBACK_INFO *peqinfo)
{
	int a;
	static eistr buf[512];
	eistr title[64];
	eistr *p = &buf[0],temp[64],empty[MATERIALWINDOW_STRINGSIZE + 1],
		*ProtectName[] = {" �� "," �� "," �� "};
	CrItem *pItem;

	//---�󕶎��񏉊���
	memset(&empty[0],' ',sizeof(empty));
	empty[MATERIALWINDOW_STRINGSIZE] = 0;

	//---����
	for(a = 0;a < EQ_WEAPON_MAX;a ++){
		pItem = critemGetItemClass(pChara->GetWeapon(a));
		sprintf(&temp[0],"\\4����:\\7 %s%s  \\4%4d\\7 , \\6%2d%%\\7;",
			pItem->GetName(),
			&empty[strlen(pItem->GetName())],
			pChara->CalcAtack(pItem),pItem->GetHitProb() / 10);
		sprintf(p,"%s",temp);

		p += strlen(temp);
	}
	//---�h��
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
	//---�A�N�Z�T���[
	for(a = 0;a < EQ_ACCESSORY_MAX;a ++){
		pItem = critemGetItemClass(pChara->GetAccessory(a));
		sprintf(&temp[0],"\\5����:\\7 %s%s ;",//\\4%4d\\7 , \\6%2d%%\\7;",
			pItem->GetName(),
			&empty[strlen(pItem->GetName())]);
		sprintf(p,"%s",temp);

		p += strlen(temp);
	}

	sprintf(p,"      �������ŋ��ɂ���;      �h����ŋ��ɂ���;");

	sprintf(title,"%-12s  ���l���؂�ւ���",peqinfo->pChara->GetName());

	peqinfo->pSelect->Create(32,48,28,14,title,//peqinfo->pChara->GetName(),
		buf,1,24);
	peqinfo->pSelect->SetData((ei_u32)peqinfo);
	peqinfo->pSelect->SetSelectCallBack(crmainMenuEquip_SelectEquipmentCallBack);
}

//---�X�e�[�^�X�E�B���h�E�����
void crmainMenuEquip_CreateStatusWindow(CrCharacter *pChara,EQUIPCALLBACK_INFO *peqinfo)
{
	peqinfo->pStatus->Create(48,288,28,10);
}

//---�����E�B���h�E��`��
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
			//---�\�͕ω���\��
			if(!(kind > 1 && a == 0)){
				pStatus->SetColor(CRCOLOR_WHITE);
				pStatus->DrawText("  �� ");
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

//---�������O������I��
CRBASE_ITEMAPI int crmainMenuEquip_SelectAction(int sx,int sy,int item)
{
	int a;
	CrSelectWindow select;

	crbaseMenuReset();
	select.Create(sx,sy,15,6,critemGetItemClass(item)->GetName(),"����;�͂���;�߂�;",1,14);
	ew->Refresh();
	crbaseMenuStart();

	a = select.Select();
	if(a == 2)
		a = -1;
	return a;
}

//---����
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
		//---�L�����I��
		if(pGameInfo->TransWindow == 0){
			crmainClearMenu();
		}
		MemberInfo.Offset = eqinfo.member;
		eqinfo.member = crcharaSelectMember(32,32,0,"�����ґI��",&MemberInfo);
		if(eqinfo.member == -1){
			break;
		}
		eqinfo.pChara = crcharaGetPartyMember(eqinfo.member);
		memset(&SelectInfo,0,sizeof(SelectInfo));
		SelectInfo.Page = eqinfo.member;

		//---�������
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

			//---�����i�I��
			ew->Refresh();
			crbaseMenuStart();
			sel = eqinfo.pSelect->Select(&SelectInfo);
			if(sel == -1){
				break;
//				continue;
			}
			eqinfo.kind = sel;

			//---�������O�����I��
			if(sel <= 6){
				action = crmainMenuEquip_SelectAction(224,48,eqinfo.pChara->GetEquipment(sel));
				if(action == -1)
					continue;
//					goto SELECT_EQUIP;
			} else if(sel == 7){
				//---�ŋ�
				crmainMenuEquip_Saikyo(eqinfo.pChara,0);
				continue;
//				goto SELECT_EQUIP;
			} else if(sel == 8){
				//---�h��ŋ�
				crmainMenuEquip_Saikyo(eqinfo.pChara,1);
				continue;
//				goto SELECT_EQUIP;
			}

			if(action == 0){
				//---��������A�C�e����I��
				int sel_kind;
					if(sel < EQ_WEAPON_MAX)
					sel_kind = 0;
				else if(sel < EQ_WEAPON_MAX + EQ_PROTECTOR_MAX)
					//---�h��
					sel_kind = (sel - 1);
				else
					//---�A�N�Z�T���[
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
					//---����
					critemAddItem(eqinfo.pChara->GetEquipment(sel),1);
					//---���ւ�
					eqinfo.pChara->SetEquipment(sel,item);
					if(item != 0){
						//---�A�C�e���̌������炷
						critemSubItem(item,1);
					}
				} else if(action == 1){
					//---�O��
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
