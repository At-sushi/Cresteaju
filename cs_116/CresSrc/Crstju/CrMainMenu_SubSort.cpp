
//---種類別アイテムソート種類選択
ei_s32 crmainmenuSort_ItemKind_Select(void)
{
	CrStackWindow win;
	ei_s32 in[16] = {CRMATERIAL_ITEMLKIND_ITEM,CRMATERIAL_ITEMLKIND_WEAPON,
		CRMATERIAL_ITEMLKIND_ARMOR,CRMATERIAL_ITEMLKIND_ACCESSORY,-1},
		out[16];

	crbaseMenuReset();
	win.Create(64,64,16,8,8,"種類別",
		"アイテム;武器;防具;アクセサリ;");
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

//---アイテムソート
ei_s32 crmainmenuSort_Item(void)
{
	int ret;
	CrSelectWindow win;

	do{
		crbaseMenuReset();
		win.Create(48,48,11,9,"アイテム整理",
		"種類;名前（前から）;名前（後ろから）;安い物から;高い物から;");
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
	end.DrawText("　　　整理しました");
	end.Refresh();
	end.WaitKey();

	return 1;
}

//---種類別魔法ソート種類選択
ei_s32 crmainmenuSort_MagicKind_Select(int member)
{
	CrStackWindow win;
	ei_s32 in[16] = {CRMATERIAL_MAGICLKIND_ATACK,CRMATERIAL_MAGICLKIND_RECOVERY,
		CRMATERIAL_MAGICLKIND_HELP,-1},
		out[16];

	crbaseMenuReset();
	win.Create(80,80,16,8,8,"種類別",
		"攻撃;回復;補助;");
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

//---魔法ソート
ei_s32 crmainmenuSort_MagicChara(int member)
{
	int ret;
	CrSelectWindow win;

	do{
		crbaseMenuReset();
		win.Create(64,64,14,12,crcharaGetPartyMember(member)->GetName(),
		"種類;名前（前から）;名前（後ろから）;ＭＣ（低い魔法から）;ＭＣ（高い魔法から）;"
		"レベル（低い魔法から）;レベル（高い魔法から）;");
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
	end.DrawText("　　　整理しました");
	end.Refresh();
	end.WaitKey();

	return 1;
}

ei_s32 crmainmenuSort_Magic(void)
{
	int member;

	while(1){
		member = crcharaSelectMember(48,48,CRBASE_SELECTPLAYER_LP | CRBASE_SELECTPLAYER_MC,
			"誰の魔法を整理しますか？");

		if(member == -1)
			return -1;

		if(crmainmenuSort_MagicChara(member) != -1)
			break;
	}

	return 1;
}

//---整理
ei_s32 crmainmenuSort(void)
{
	int ret;
	CrSelectWindow win;
	CRWIN_SELECTINFO Info;

	memset(&Info,0,sizeof(Info));

/*	do{
		crbaseMenuReset();
		crmainClearMenu();
		win.Create(32,32,10,5,"整理するものは？",
			"アイテム整理;  魔法整理  ;");
		win.Refresh();
		crbaseMenuStart();

		ret = win.Select(&Info);

		if(ret == 0){
			//---アイテム整理
			crmainmenuSort_Item();
		} else if(ret == 1){
			//---魔法整理
			crmainmenuSort_Magic();
		}

	} while(ret != -1);*/

	crmainClearMenu();
	ew->Refresh();

	crmainmenuSort_Item();
	ret = 0;

	return 1;
}
