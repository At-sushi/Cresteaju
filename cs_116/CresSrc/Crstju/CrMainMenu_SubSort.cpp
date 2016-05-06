
//---��ޕʃA�C�e���\�[�g��ޑI��
ei_s32 crmainmenuSort_ItemKind_Select(void)
{
	CrStackWindow win;
	ei_s32 in[16] = {CRMATERIAL_ITEMLKIND_ITEM,CRMATERIAL_ITEMLKIND_WEAPON,
		CRMATERIAL_ITEMLKIND_ARMOR,CRMATERIAL_ITEMLKIND_ACCESSORY,-1},
		out[16];

	crbaseMenuReset();
	win.Create(64,64,16,8,8,"��ޕ�",
		"�A�C�e��;����;�h��;�A�N�Z�T��;");
	win.Refresh();
	if(win.Select(in,out) == -1){
		return -1;
	}

	int a,b;
	ei_s32 sort_table[16];
	for(a = 0,b = 0;a < 4;a ++){
		if(out[a] == CRMATERIAL_ITEMLKIND_ARMOR){
			sort_table[b ++] = CRMATERIAL_ITEMLKIND_ARMOR;
			sort_table[b ++] = CRMATERIAL_ITEMLKIND_SHIELD;
			sort_table[b ++] = CRMATERIAL_ITEMLKIND_HELM;
		} else {
			sort_table[b ++] = out[a];
		}
	}
	sort_table[b] = -1;

	crmateSortMaterial(pGameInfo->Item,ITEM_MAX,pItemInfo,
		SORTMATERIAL_KINDTABLE | SORTMATERIAL_ITEM,sort_table);

	return 1;
}

//---�A�C�e���\�[�g
ei_s32 crmainmenuSort_Item(void)
{
	int ret;
	CrSelectWindow win;

	do{
		crbaseMenuReset();
		win.Create(48,48,11,9,"�A�C�e������",
		"���;���O�i�O����j;���O�i��납��j;����������;����������;");
		win.Refresh();
		crbaseMenuStart();

		ret = win.Select();

		if(ret == -1){
			return -1;
		} else if(ret == 0){
			if(crmainmenuSort_ItemKind_Select() == -1){
				ret = 0;
				continue;
			}
			break;
		} else if(ret <= 2){
			crmateSortMaterial(pGameInfo->Item,ITEM_MAX,pItemInfo,
				SORTMATERIAL_NAME | SORTMATERIAL_ITEM
				| (ret == 2 ? 0 : SORTMATERIAL_REVERSE),NULL);
			break;
		} else if(ret <= 4){
			crmateSortMaterial(pGameInfo->Item,ITEM_MAX,pItemInfo,
				SORTMATERIAL_VALUE | SORTMATERIAL_ITEM
				| (ret == 3 ? 0 : SORTMATERIAL_REVERSE),NULL);
			break;
		}
	} while(ret != -1);

	CrStringWindow end;

	end.Create(80,80,14,5);
	end.AddReturn();
	end.DrawText("�@�@�@�������܂���");
	end.Refresh();
	end.WaitKey();

	return 1;
}

//---��ޕʖ��@�\�[�g��ޑI��
ei_s32 crmainmenuSort_MagicKind_Select(int member)
{
	CrStackWindow win;
	ei_s32 in[16] = {CRMATERIAL_MAGICLKIND_ATACK,CRMATERIAL_MAGICLKIND_RECOVERY,
		CRMATERIAL_MAGICLKIND_HELP,-1},
		out[16];

	crbaseMenuReset();
	win.Create(80,80,16,8,8,"��ޕ�",
		"�U��;��;�⏕;");
	win.Refresh();
	if(win.Select(in,out) == -1){
		return -1;
	}

	int a,b;
	ei_s32 sort_table[16];
	for(a = 0,b = 0;a < 3;a ++){
		sort_table[b ++] = out[a];
	}
	sort_table[b] = -1;

/*	crmateSortMaterial(crcharaGetPartyMember(member)->CharaInfo.MagicTable,
		MAGIC_MAX,pMagicInfo,
		SORTMATERIAL_ELEMENT);
*/
	crmateSortMaterial(crcharaGetPartyMember(member)->CharaInfo.MagicTable,
		MAGIC_MAX,pMagicInfo,
		SORTMATERIAL_MAGICTABLE,sort_table);

	return 1;
}

//---���@�\�[�g
ei_s32 crmainmenuSort_MagicChara(int member)
{
	int ret;
	CrSelectWindow win;

	do{
		crbaseMenuReset();
		win.Create(64,64,14,12,crcharaGetPartyMember(member)->GetName(),
		"���;���O�i�O����j;���O�i��납��j;�l�b�i�Ⴂ���@����j;�l�b�i�������@����j;"
		"���x���i�Ⴂ���@����j;���x���i�������@����j;");
		win.Refresh();
		crbaseMenuStart();

		ret = win.Select();

		if(ret == -1){
			return -1;
		} else if(ret == 0){
			if(crmainmenuSort_MagicKind_Select(member) == -1){
				ret = 0;
				continue;
			}
			break;
		} else if(ret <= 2){
			crmateSortMaterial(crcharaGetPartyMember(member)->CharaInfo.MagicTable,
				MAGIC_MAX,pMagicInfo,
				SORTMATERIAL_NAME
				| (ret == 2 ? 0 : SORTMATERIAL_REVERSE),NULL);
			break;
		} else if(ret <= 4){
			crmateSortMaterial(crcharaGetPartyMember(member)->CharaInfo.MagicTable,
				MAGIC_MAX,pMagicInfo,
				SORTMATERIAL_MC
				| (ret == 3 ? 0 : SORTMATERIAL_REVERSE),NULL);
			break;
		} else if(ret <= 6){
			crmateSortMaterial(crcharaGetPartyMember(member)->CharaInfo.MagicTable,
				MAGIC_MAX,pMagicInfo,
				SORTMATERIAL_LEVEL
				| (ret == 5 ? 0 : SORTMATERIAL_REVERSE),NULL);
			break;
		}
	} while(ret != -1);

	CrStringWindow end;

	end.Create(96,96,14,5);
	end.AddReturn();
	end.DrawText("�@�@�@�������܂���");
	end.Refresh();
	end.WaitKey();

	return 1;
}

ei_s32 crmainmenuSort_Magic(void)
{
	int member;

	while(1){
		member = crcharaSelectMember(48,48,CRBASE_SELECTPLAYER_LP | CRBASE_SELECTPLAYER_MC,
			"�N�̖��@�𐮗����܂����H");

		if(member == -1)
			return -1;

		if(crmainmenuSort_MagicChara(member) != -1)
			break;
	}

	return 1;
}

//---����
ei_s32 crmainmenuSort(void)
{
	int ret;
	CrSelectWindow win;
	CRWIN_SELECTINFO Info;

	memset(&Info,0,sizeof(Info));

/*	do{
		crbaseMenuReset();
		crmainClearMenu();
		win.Create(32,32,10,5,"����������̂́H",
			"�A�C�e������;  ���@����  ;");
		win.Refresh();
		crbaseMenuStart();

		ret = win.Select(&Info);

		if(ret == 0){
			//---�A�C�e������
			crmainmenuSort_Item();
		} else if(ret == 1){
			//---���@����
			crmainmenuSort_Magic();
		}

	} while(ret != -1);*/

	crmainClearMenu();
	ew->Refresh();

	crmainmenuSort_Item();
	ret = 0;

	return 1;
}
