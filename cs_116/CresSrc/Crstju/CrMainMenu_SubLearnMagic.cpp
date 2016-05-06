
static CRWIN_SELECTINFO LearnMagicSelectChara,LearnMagicSelectLevelInfo;
//---魔法を覚えるのに必要な修得済み魔法の数
ei_s32 NeedToLearnCount_Recovery[8] =
{0,0,0,1,2,2,0,0};
ei_s32 NeedToLearnCount_Help[8] =
{0,0,0,1,3,5,0,0};
ei_s32 NeedToLearnCount_Other[8] =
{0,0,0,1,2,2,0,0};

DEFINE_ELEMENTSTRING();

#define LEARNMAGIC_TABLEMAX 33
#define LEARNMAGIC_LEVELMAX 6

typedef struct
{
	//---各レベルごとの覚えられる魔法
	ei_s32 MagicTable[LEARNMAGIC_TABLEMAX];
} LEARNMAGIC_MAGICTABLE;

typedef struct
{
	CrCharacter *pChara;
	LEARNMAGIC_MAGICTABLE Level[8];
	ei_s32 WhoHave[MAGICMATERIAL_MAX];//---誰か魔法を持っているか
} LEARNMAGIC_INFO, *LPLEARNMAGIC_INFO;

//---必要な魔法修得値を計算
int crmainLearnMagic_CalcMagicExp(CrCharacter *pChara,int level)
{
	int a,experience,count;

	for(a = 0,count = 0;a < MAGIC_MAX;a ++){
		if(crmagicGetMagicClass(pChara->GetMagic(a))->GetLevel() == level){
			count ++;
		}
	}

	experience = (10 * level);
	experience = experience + (experience * count * 50) / 100;

	return experience;
}

//---このレベルの魔法を覚えることができるか
int crmainLearnMagic_IsEnableToLearn(CrCharacter *pChara,int level)
{
	int m_exp = crmainLearnMagic_CalcMagicExp(pChara,level);

	if(pChara->GetMagicExperience() < m_exp){
		//---魔法修得値が足らなければ
		return 0;
	}

	return 1;
}

//---情報を初期化
void crmainLearnMagicInitInfo(LEARNMAGIC_INFO *pInfo,CrCharacter *pChara)
{
	int a,b,level,count[8];
	CrMagic *pMagic;
	CrCharacter *pOther;

	memset(pInfo,0,sizeof(LEARNMAGIC_INFO));
	memset(&count[0],0,sizeof(count));

	pInfo->pChara = pChara;

	//---パーティー内ですでに覚えている魔法を全部調べる
	for(a = 0;a < MEMBER_MAX;a ++){
		pOther = crcharaGetPartyMember(a);
		if(pOther == NULL || pOther == pChara)
			//---誰もいないか自分自身だったら
			continue;
		for(b = 0;b < MAGICMATERIAL_MAX;b ++){
			if(pOther->HaveMagic(b)){
				//---その魔法を持っていれば記録
				pInfo->WhoHave[b] |= (1 << a);
			}
		}
	}

	//---ひとまず、全ての魔法をレベルごとに分ける
	for(a = 0;a < MAGICMATERIAL_MAX;a ++){
		pMagic = crmagicGetMagicClass(a);
		level = pMagic->GetLevel();
		if(level){
			//---魔法があるなら
			pInfo->Level[level].MagicTable[count[level]] = a;
			//---そのレベルのカウントを１つ増やす
			count[level] ++;
		}
	}

	//---そのキャラクターが持っている魔法を抜かす
	for(level = 1;level <= LEARNMAGIC_LEVELMAX;level ++){
		for(a = 0;a < LEARNMAGIC_TABLEMAX;a ++){
			if(pInfo->pChara->HaveMagic(pInfo->Level[level].MagicTable[a])){
				//---もしその魔法を持っていれば
//				pInfo->Level[level].MagicTable[a] = 0;
			} else {
				//---もしその魔法を覚えるのに条件が足りなければ
				pMagic = crmagicGetMagicClass(pInfo->Level[level].MagicTable[a]);
				if(pMagic->GetMaterialKind() == ELEMENT_RECOVERY){
					if(pChara->HaveMagicElement(ELEMENT_RECOVERY) < NeedToLearnCount_Recovery[level])
						pInfo->Level[level].MagicTable[a] = 0;
				} else if(pMagic->GetMaterialKind() == ELEMENT_HELP){
					if(pChara->HaveMagicElement(ELEMENT_HELP) < NeedToLearnCount_Help[level])
						pInfo->Level[level].MagicTable[a] = 0;
				} else {
					if(pChara->HaveMagicElement(pMagic->GetMaterialKind()) < NeedToLearnCount_Other[level])
						pInfo->Level[level].MagicTable[a] = 0;
				}
				//---ＭＣが足りない
/*				if(pChara->GetMaxMC() < pMagic->GetMC()){
						pInfo->Level[level].MagicTable[a] = 0;
				}
*/
				//---修得不能！
				if(pChara->EnableLearningMagic(pMagic->GetElement(),level) == 0){
					if(pChara->Who() == 1){
						//---ルナンでカオスワード
						if(pInfo->Level[level].MagicTable[a] == 27){
							continue;
						}
					}
					pInfo->Level[level].MagicTable[a] = 0;
				} else {
					if(pChara->Who() == 1){
						//---ルナン
						if(77 <= pInfo->Level[level].MagicTable[a] 
							&& pInfo->Level[level].MagicTable[a] <= 78){
							if(!evGet(201)){
								pInfo->Level[level].MagicTable[a] = 0;
							}
						}
						if(79 <= pInfo->Level[level].MagicTable[a]){
							pInfo->Level[level].MagicTable[a] = 0;
						}
					} else if(pChara->Who() == 3){
						//---ナック
						if(24 <= pInfo->Level[level].MagicTable[a] 
							&& pInfo->Level[level].MagicTable[a] <= 24){
							if(!evGet(203)){
								pInfo->Level[level].MagicTable[a] = 0;
							}
						}
					}
				}
			}
		}
		//---ソートする
		crmateSortMaterial(&pInfo->Level[level].MagicTable[0],
			LEARNMAGIC_TABLEMAX,pMagicInfo,
			SORTMATERIAL_MC,NULL);
	}
}

//---マジックリストを描く
void crmainLernMagic_DrawMagicList(LEARNMAGIC_INFO *pInfo,int level)
{
	int a,x_offset = 8,y_offset = 24;
	CrStringWindow win;

	level ++;
//	win.Create(272,48,16,26);
	win.Create(320,48,16,26);
	win.SetOffset(x_offset,y_offset);

	//---最初の部分
	for(a = 0;a < 20;a ++){
		win.DrawText("  ");
		win.SetColor(CRCOLOR_GREEN);
		pMagicIconCell[pMagicInfo[pInfo->Level[level].MagicTable[a]].GetMaterialKind()].PutTrans(
			ew->lpCell[1],
			win.xGetTop() + win.xGetCurrentPos() * 8 + x_offset,
			win.yGetTop() + win.yGetCurrentPos() * 20 + y_offset);
		win.DrawText(" ");
//		win.DrawText(ElementString[pMagicInfo[pInfo->Level[level].MagicTable[a]].GetMaterialKind()]);
		win.DrawText(" ");
		if(pInfo->pChara->HaveMagic(pInfo->Level[level].MagicTable[a]))
			win.SetColor(CRCOLOR_GRAY);
		else
			win.SetColor(CRCOLOR_WHITE);
		win.DrawText(
			crmagicGetMagicClass(pInfo->Level[level].MagicTable[a])->GetName()
			);
		win.AddReturn();
	}
	win.Refresh();
}

//---コールバック
int crmainLearnMagic_SelectLevelCallBack(CrSelectWindow *pwin,eiCell *pCell,int Message,ei_u32 Param1,ei_u32 Param2,int Param3)
{
	LEARNMAGIC_INFO *pInfo;

	if(Message == CRWIN_SELECT_MESMOVECURSOR){
		//---カーソル移動
		int index = Param3;
		pInfo = (LEARNMAGIC_INFO *)Param2;

		return 1;
	}
	if(Message == CRWIN_SELECT_MESSHOWHELP){
		//---ヘルプ表示
		int index = Param3;
		pInfo = (LEARNMAGIC_INFO *)Param2;

		crmainLernMagic_DrawMagicList(pInfo,index);
	}

	//---処理しなかった場合
	return 0;
}

//---キャラクター情報を表示
void crmainLearnMagic_DrawCharaInfo(LEARNMAGIC_INFO *pInfo)
{
	int a,x_offset = 8,y_offset = 24;
	CrStringWindow info;
	eistr temp[64];

	info.Create(48,276,13,12);
	info.SetOffset(x_offset,y_offset);
	info.SetColor(CRCOLOR_WHITE);
	info.DrawText("選択人物   :");
	info.SetColor(CRCOLOR_YELLOW);
	info.DrawText(pInfo->pChara->GetName());
	info.AddReturn();

	info.SetColor(CRCOLOR_WHITE);
	info.DrawText("最大MC     :");
	sprintf(temp,"%d",pInfo->pChara->GetMaxMC());
	info.SetColor(CRCOLOR_GREEN);
	info.DrawText(temp);
	info.AddReturn();

	info.SetColor(CRCOLOR_WHITE);
	info.DrawText("魔法修得値 :");
	sprintf(temp,"%d",pInfo->pChara->GetMagicExperience());
	info.SetColor(CRCOLOR_GREEN);
	info.DrawText(temp);
	info.AddReturn();

	info.SetColor(CRCOLOR_WHITE);
	info.DrawText("修得済み魔法数 :");
	int count = 0;
	for(a = 1;a < MAGICMATERIAL_MAX;a ++){
		if(pInfo->pChara->HaveMagic(a))
			count ++;
	}
	info.SetColor(CRCOLOR_GREEN);
	sprintf(temp,"%2d  ",count);
	info.DrawText(temp);
	info.AddReturn();
	info.AddReturn();
	DEFINE_ELEMENTSTRING();
	for(a = 1;a < 9;a ++){
		info.SetColor(CRCOLOR_WHITE);
		pMagicIconCell[a].PutTrans(
			ew->lpCell[1],
			info.xGetTop() + info.xGetCurrentPos() * 8 + x_offset,
			info.yGetTop() + info.yGetCurrentPos() * 20 + y_offset);
//		info.DrawText(ElementString[a]);
		info.DrawText("　");
		info.SetColor(CRCOLOR_GREEN);
		sprintf(temp,":%2d  ",pInfo->pChara->HaveMagicElement(a));
		info.DrawText(temp);
		if(a % 3 == 0){
			info.AddReturn();
		}
	}

	info.Refresh();
}

//---
int crmainLearnMagic_SelectCharaCallBack(CrSelectWindow *pwin,eiCell *pCell,int Message,ei_u32 Param1,ei_u32 Param2,int Param3)
{
	LEARNMAGIC_INFO Info;

	if(Message == CRWIN_SELECT_MESMOVECURSOR){
		//---カーソル移動
		int index = Param3;
		Info.pChara = crcharaGetPartyMember(index);
		crmainLearnMagic_DrawCharaInfo(&Info);

		return 1;
	}
	if(Message == CRWIN_SELECT_MESSHOWHELP){
		//---ヘルプ表示
		int index = Param3;

		Info.pChara = crcharaGetPartyMember(index);
		crmainLearnMagic_DrawCharaInfo(&Info);
	}

	return 0;
}

//---修得魔法レベルの選択
int crmainLearnMagicSelectLevel(LEARNMAGIC_INFO *pInfo)
{
	int a,color,ret = -1;
	CrSelectWindow win;
	eistr string[256],*p = &string[0],title[128];
	eistr *levelstr[] = {
#if CR_LANUGAGE == 0
		"","レベル１","レベル２","レベル３","レベル４","レベル５","レベル６"
#endif
	};

	crbaseMenuReset();

	int max = LEARNMAGIC_LEVELMAX - 1;

	if(pInfo->pChara->Who() == 1){
		//---ルナン
		if(evGet(201)){
			max ++;
		}
	} else if(pInfo->pChara->Who() == 3){
		//---ナック
		if(evGet(203)){
			max ++;
		}
	}

	for(a = 1;a <= max;a ++){
		if(crmainLearnMagic_IsEnableToLearn(pInfo->pChara,a))
			color = 7;
		else
			color = 2;
		sprintf(p,"\\%d%s  \\%d%4d;",color,levelstr[a],
			color == 7 ? 4 : 2,
			crmainLearnMagic_CalcMagicExp(pInfo->pChara,a));
		p += strlen(p);
	}

	sprintf(title,"%-10s   必要魔法修得値",
		pInfo->pChara->GetName(),
		pInfo->pChara->GetMagicExperience());

	win.SetData((ei_u32)pInfo);
	win.SetSelectCallBack(crmainLearnMagic_SelectLevelCallBack);
	win.Create( 64,48,12,11,title,string);
	crmainLearnMagic_DrawCharaInfo(pInfo);

//		"レベル１;レベル２;レベル３;レベル４;レベル５;レベル６;修得魔法一覧;");

//	ew->lpCell[1]->DrawText("a",win.xGetTop()+  128,win.yGetTop(),ep->ToTextRGB(CRCOLOR_WHITE));

	win.Refresh();
	crbaseMenuStart();
	ret = win.Select(&LearnMagicSelectLevelInfo);

	if(ret != -1 && ret < 6){
		if(crmainLearnMagic_IsEnableToLearn(pInfo->pChara,ret + 1)){
			//---このレベルの魔法を覚えられるのであったら
			return ret;
		} else {
//			crsoundPlay(CRSOUND_BEEP_1);
			return ret;
		}
	}

	return -1;
}

//---コールバック
void crmainLearnMagic_SelectMagicCallBack(CrSelectWindow *psel,eiCell *pCell,ei_u32 data)
{
	int tx = psel->xGetTop() + 240,ty = psel->yGetTop() + 1;
	int old = eiSetFont(EISMALL_FONT);

	ew->lpCell[1]->DrawFillBox(tx ,ty,
		tx + 6 * 6,ty + 12,
		ep->ToRGB(CRCOLOR_BLACK));
	ew->lpCell[1]->DrawText("消費MC",
		tx,ty,
		ep->ToTextRGB(CRCOLOR_WHITE),EI_PSET);

	eiSetFont(old);
}

//---覚える魔法を選択
int crmainLearnMagicSelectMagic(LEARNMAGIC_INFO *pInfo,int level)
{
	int scene = 11;

	int index,option[] = {
//		CRMATERIAL_KIND_MAGICELEMENT ,
		CRMATERIAL_KIND_MAGICMC ,0, 0 , 0};
	CrSelectWindow menu;
	CrMessageWindow help;
	MATERIALWINDOW_STYLE Style;

	memset(&Style,0,sizeof(Style));
	Style.Style = MATERIALWINDOW_STYLE_MAGICICON;
	//---index
	Style.pIndex = &pInfo->Level[level].MagicTable[0];
	Style.IndexMax = LEARNMAGIC_TABLEMAX;
	Style.pSubItem[0] = &scene;//---scene
	//---material
	Style.pMaterial = pMagicInfo;
	Style.MaterialMax = MAGICMATERIAL_MAX;
	//---page
	Style.PageSize = LEARNMAGIC_TABLEMAX / 3;
	//---option
	Style.Option = &option[0];
	Style.ShowOption = 1;

	//---Callback
//	Style.pCallBack = crmainLearnMagic_SelectMagicCallBack;

	//---help
	Style.pHelpWindow = &help;
	Style.HelpWindowPos = 0;
	//---data
	Style.Data[0] = (ei_u32)pInfo->pChara;

	while(1){
		index = crmateCreateAndSelectMaterialWindow(
			&menu,
			/*272*/320,48,1,
			0/*mode*/,NULL,&Style);

		if(index != -1 
			&& pInfo->pChara->HaveMagic(pInfo->Level[level].MagicTable[index])
			){
			//---すでに覚えてる魔法なら
			continue;
		}

		if(!crmainLearnMagic_IsEnableToLearn(pInfo->pChara,level)){
			//---修得値が足りなかったら
			index = -1;
			break;
		}

		break;
	}

	return index;
}

//---その魔法を覚えて良いか確認
int crmainLearnMagicCheck(LEARNMAGIC_INFO *pInfo,int magic)
{
	int a,b;
	CrStringWindow win;
	CrSelectWindow select;
	eistr s[120];
	CrMagic *pMagic = crmagicGetMagicClass(magic);

	if(magic == 0){
		return -1;
	}
	if(pMagic == NULL){
		return -1;
	}

	//---ＭＣが足りなければ覚えられない
	if(pInfo->pChara->GetMaxMC() < pMagic->GetMC()){
		win.Create(336,72,16,3);
		win.DrawText("最大ＭＣが足りません！！");
		win.Refresh();
		et->Delay2(500);

		CrInput ci;
		ci.WaitAnykey();
		return -1;
	}

	crbaseMenuReset();
//	win.Create(272,48,20,15);
	win.Create(32,32,18,15);
	{
		win.AddReturn();

		win.SetColor(CRCOLOR_WHITE);
		win.DrawText("魔法名     : ");
		win.SetColor(CRCOLOR_GREEN);
		win.DrawText(pMagic->GetName());
		win.AddReturn();

		eistr *scene[] = {"移動中","戦闘中","常時"};
		win.SetColor(CRCOLOR_WHITE);
		win.DrawText("使用シーン : ");
		win.SetColor(CRCOLOR_GREEN);
		win.DrawText(scene[pMagic->GetScene()]);
		win.AddReturn();

		win.SetColor(CRCOLOR_WHITE);
		win.DrawText("使用MC     : ");
		win.SetColor(CRCOLOR_GREEN);
		sprintf(&s[0],"%3d",pMagic->GetMC());
		win.DrawText(s);
		win.AddReturn();

		eistr *element[] = {
			"　","無し","回復","補助","火",
			"水","土","風","雷",
			"精神","変化","物理","その他"};
		win.SetColor(CRCOLOR_WHITE);
		win.DrawText("属性       : ");
		win.SetColor(CRCOLOR_GREEN);
		win.DrawText(element[pMagic->GetElement()]);
		win.AddReturn();

		win.SetColor(CRCOLOR_WHITE);
		win.DrawText("対象       : ");
		win.SetColor(CRCOLOR_GREEN);
		switch(pMagic->GetTarget(0)){
		case BAT_TARGET_ME:
			sprintf(&s[0],"自分");
			break;
		case BAT_TARGET_FRIENDSINGLE:
			sprintf(&s[0],"味方１人");
			break;
		case BAT_TARGET_ENEMYSINGLE:
			sprintf(&s[0],"敵１人");
			break;
		case BAT_TARGET_FRIENDALL:
			sprintf(&s[0],"味方全体");
			break;
		case BAT_TARGET_ENEMYALL:
			sprintf(&s[0],"敵全体");
			break;
		case BAT_TARGET_FRIENDRANGE:
			sprintf(&s[0],"味方範囲");
			break;
		case BAT_TARGET_ENEMYRANGE:
			sprintf(&s[0],"敵範囲");
			break;
		}
		win.DrawText(s);
		win.AddReturn();

		win.AddReturn();
		win.SetColor(CRCOLOR_WHITE);
		win.DrawText("パーティー内修得済み人物");
		win.AddReturn();
		for(a = 0,b = 0;a < MEMBER_MAX;a ++){
			CrCharacter *pChara = crcharaGetPartyMember(a);
			if(pChara != NULL && pChara != pInfo->pChara){
				if(pChara->HaveMagic(magic)){
					b ++;
					win.SetColor(CRCOLOR_YELLOW);
					sprintf(&s[0],"%-12s  ",pChara->GetName());
					win.DrawText(s);
					if(b % 2 == 0)
						win.AddReturn();
				}
			}
		}
		crmainLearnMagic_DrawCharaInfo(pInfo);
	}
	win.Refresh();
//	select.Create(64,64,11,5,"この魔法を修得しますか？",
//		"修得する;やめる;",1,14);
	select.Create(320,64,11,5,"この魔法を修得しますか？",
		"修得する;やめる;",1,14);
	select.Refresh();

	crbaseMenuStart();
	et->Delay2(300);

	return select.Select();
}

//---魔法修得
int crmainLearnMagic(void)
{
	int ret,member,level,magic;
	CrCharacter *pChara;
	LEARNMAGIC_INFO Information;
//	CrMagic *pMagic;

	memset(&LearnMagicSelectChara,0,sizeof(LearnMagicSelectChara));
	memset(&LearnMagicSelectLevelInfo,0,sizeof(LearnMagicSelectLevelInfo));

	//---キャラクター選択
	while(1){
		crmainClearMenu();
		member = crcharaSelectMember(32,32,CRBASE_SELECTPLAYER_MAGICEXP,
			"誰？",&LearnMagicSelectChara,
			crmainLearnMagic_SelectCharaCallBack/*コールバック*/);
		if(member == -1)
			break;
		pChara = crcharaGetPartyMember(member);

		while(1){
			//---魔法情報を初期化
			crmainLearnMagicInitInfo(&Information,pChara);
			//---画面半分を消す
//			RECT rect = {272,0,640,480};
			RECT rect = {0,0,640,480};
			ew->lpCell[1]->SetClipingRect(&rect);
			crmainClearMenu();
			SetRect(&rect,0,0,640,480);
			ew->lpCell[1]->SetClipingRect(&rect);
//			ew->lpCell[1]->DrawFillBox(272,0,639,479,ep->ToRGB(CRCOLOR_BLACK));
			ew->Refresh();
			//---レベル選択
			ret = level = crmainLearnMagicSelectLevel(&Information);
			if(ret != -1){
				//---レベル選択をしていれば
				level ++;
				//---画面半分を消す
//				RECT rect = {272,0,640,480};
				RECT rect = {320,0,640,480};
				ew->lpCell[1]->SetClipingRect(&rect);
				crmainClearMenu();
				SetRect(&rect,0,0,640,480);
				ew->lpCell[1]->SetClipingRect(&rect);
				//ew->lpCell[1]->DrawFillBox(272,0,639,479,ep->ToRGB(CRCOLOR_BLACK));
				ew->Refresh();

				ret = crmainLearnMagicSelectMagic(&Information,level);
				if(ret != -1){
					//---確認する
					RECT rect = {0,0,272,479};
					ew->lpCell[1]->SetClipingRect(&rect);
					crmainClearMenu();
					SetRect(&rect,0,0,640,480);
					ew->lpCell[1]->SetClipingRect(&rect);
//					ew->lpCell[1]->DrawFillBox(0,0,271,479,ep->ToRGB(CRCOLOR_BLACK));
					ew->Refresh();
					magic = Information.Level[level].MagicTable[ret];
					ret = crmainLearnMagicCheck(&Information,magic);
					if(/*ret != -1*/!(ret == -1 || ret == 1)){
						//---覚えた！
/*						char s[80];
						eiDebugWriteFile(Information.pChara->GetName());
						sprintf(s,"\n%d\n",crmainLearnMagic_CalcMagicExp(Information.pChara,level));
						eiDebugWriteFile(s);*/
						Information.pChara->AddMagicExperience(
							-crmainLearnMagic_CalcMagicExp(Information.pChara,level));
						Information.pChara->AddMagic(magic);

						ei_s32 sort_table[16] = {CRMATERIAL_MAGICLKIND_RECOVERY,CRMATERIAL_MAGICLKIND_ATACK,CRMATERIAL_MAGICLKIND_HELP,-1};
						crmateSortMaterial(pChara->CharaInfo.MagicTable,
							MAGIC_MAX,pMagicInfo,
							SORTMATERIAL_MAGICTABLE,sort_table
						);
					}
					continue;
				} else {
					continue;
				}
			}
			break;
		}
	}

	return 1;
}
