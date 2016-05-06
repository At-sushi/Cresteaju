//---バトル終了後の処理

#define LEVELUP_STATUS(mode,string,old_st,new_st) \
{\
	if(mode == 0){\
		levelup_window.DrawText("       ");\
	} else {\
		levelup_window.DrawText("   ");\
	}\
	levelup_window.DrawText(string" :");\
	sprintf(&s[0]," %4d ",old_st);\
	levelup_window.SetColor(CRCOLOR_YELLOW);\
	levelup_window.DrawText(s);\
	levelup_window.SetColor(CRCOLOR_WHITE);\
	levelup_window.DrawText("+");\
	levelup_window.SetColor(CRCOLOR_GREEN);\
	sprintf(&s[0]," %4d ",new_st - old_st);\
	levelup_window.DrawText(s);\
	levelup_window.SetColor(CRCOLOR_WHITE);\
	levelup_window.AddReturn();\
}

//---勝った！！
CRBATMAIN_API int crbatWin(int turn,int bt_time,CR_BATTLEINFO *pInfo)
{
	int a,style;
	int AddWorld = 0,action = 0,item_get = 0,wait = 200,levelup = 0;
	int tx = 320 - 15 * 8,ty = 64;
	int levelup_flag[8],member = 0;
	int lv_lp[8],lv_mc[8],lv_power[8],lv_vitality[8],lv_agility[8],
		lv_soul[8],lv_magic[8],lv_magicexp[8];
	CrStringWindow win_window,get_window,item_window,
		levelup_window,next_window;
	eistr s[80];
	float Angle = ANGLE(0);
	eiTime let;

	for(a = 0,member = 0;a < MEMBER_MAX;a ++){
		if(crcharaGetPartyMember(a) != NULL)
			member ++;
	}

	//---音楽切り替え
	if(pInfo->Music != 0){
		crmusicPlay(CRMUSIC_FANFARE,1,CRMUSIC_LOADFORCE);
	}
	if(pBtChara[BATTLECHARA_STARTENEMY].BattleInfo.Enemy.ActionType == 224){
		//---クレイシヴ
		crmusicFadeOut();
	}

	//---アイテムを落とすかどうか
	if(eiRnd(10000) < BattleItemProb){
		//---アイテムゲット
		item_get = 1;
		critemAddItem(BattleItem,1);

/*		if(BattleItem == 30){
			//---アルティネクスを手に入れた
			pGameInfo->Event[264] = 1;
		}*/
	}
	if(bt_time > 999999){
		bt_time = 999999;
	}

	win_window.Create(tx,ty,15,2);
	get_window.Create(tx,ty + 48,15,7);
	levelup_window.Create(320 - 19 * 8,56,19,12);
	next_window.Create(320 - 16 * 8,96,16,3 + (member * 20) / 16);
	member = 0;
	if(item_get){
		int length = 10 + (strlen(critemGetItemClass(BattleItem)->GetName()) / 2);
		item_window.Create(320 - (length * 8),112,length ,2);
	}
	if(crsysGetExtentionLevel() < 3){
		style = CRWIN_BGFILL;
	} else {
		style = CRWIN_BGFILL | CRWIN_BGALPHA;
	}
	win_window.SetStyle(style);
	get_window.SetStyle(style);
	item_window.SetStyle(style);
	levelup_window.SetStyle(style);
	next_window.SetStyle(style);

	//---カメラ切り替え
	crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);
	crbatSetCamera_ViewBattleField(0,Angle,1,500);

	//---ヒストリー
	crhistAllGetExperience(BattleExperience);
	crhistAllGetMoney(BattleMoney);
	//---お金
	crbaseAddMoney(BattleMoney);
	//---経験値
	for(a = 0;a < BATTLECHARA_PARTY_MAX;a ++){
		levelup_flag[a] = 0;
		if(pBtChara[a].DoExist()){
			if(pBtChara[a].GetLP() > 0){
				//---気絶してなければ経験値を手に入れる
				pBtChara[a].AddExperience(BattleExperience);

				if(pBtChara[a].GetNextExperience() <= 0 && pBtChara[a].GetLevel() < 99){
					//---レベルアップ
					levelup_flag[levelup] = a;

					pBtChara[a].AddLevel(1);
					lv_lp[a] = pBtChara[a].GetMaxLP();
					pBtChara[a].SetLevelLP();

					lv_mc[a] = pBtChara[a].GetMaxMC();
					pBtChara[a].SetLevelMC();

					lv_power[a] = pBtChara[a].GetPower();
					pBtChara[a].SetLevelPower();

					lv_vitality[a] = pBtChara[a].GetVitality();
					pBtChara[a].SetLevelVitality();

					lv_agility[a] = pBtChara[a].GetAgility();
					pBtChara[a].SetLevelAgility();

					lv_soul[a] = pBtChara[a].GetSoul();
					pBtChara[a].SetLevelSoul();

					lv_magic[a] = pBtChara[a].GetMagic();
					pBtChara[a].SetLevelMagic();

					lv_magicexp[a] = pBtChara[a].GetMagicExperience();
					pBtChara[a].SetLevelMagicExperience();

					levelup ++;
				}
			}
		}
	}

	member = 0;
	while(1){
		let.Reset();

		wait -= AddWorld;
		if(wait < 0 || crsysQuick())
			wait = 0;
		ei->Get();
		if(ei->AnyKey && wait == 0){
			if(action == 2 && levelup){
				//---レベルアップ
				member ++;
				if(--levelup <= 0){
					action ++;
				}
			} else {
				action ++;
			}

			wait = 250;
			if(action == 1 && item_get == 0){
				action ++;
			}
			if(action == 2 && levelup == 0){
				action ++;
			}

			if(action == 3){
				break;
			}
		}

		crbatClearDrawingList();
		crbatAddDrawingListAll();

		Angle += (float)((float)AddWorld * 0.0004f);
		if(crsysGetExtentionLevel() >= 3){
			crbatSetCamera_ViewBattleField(0,Angle);
		}
crdataEnableRec(0);
		crbatDrawScene();

		if(action == 0){
			win_window.Reset();
			win_window.Paint();
			win_window.DrawText("     戦闘に勝利した！！");

			get_window.Reset();
			get_window.Paint();
			get_window.SetColor(CRCOLOR_WHITE);
			get_window.DrawText("     経験値   :");
			sprintf(&s[0],"%6d",BattleExperience);
			get_window.SetColor(CRCOLOR_GREEN);
			get_window.DrawText(s);
			get_window.AddReturn();

			get_window.SetColor(CRCOLOR_WHITE);
			get_window.DrawText("     お金     :");
			sprintf(&s[0],"%6d",BattleMoney);
			get_window.SetColor(CRCOLOR_YELLOW);
			get_window.DrawText(s);
			get_window.AddReturn();
			get_window.AddReturn();

			get_window.SetColor(CRCOLOR_WHITE);
			get_window.DrawText("     ターン数 :");
			sprintf(&s[0],"%6d",turn);
			get_window.DrawText(s);
			get_window.AddReturn();

			get_window.SetColor(CRCOLOR_WHITE);
			get_window.DrawText("     戦闘時間 :");
			sprintf(&s[0],"%6d",bt_time);
			get_window.DrawText(s);
		} else if(action == 1){
			//---アイテムゲット
			item_window.Reset();
			item_window.Paint();

			item_window.SetColor(CRCOLOR_GREEN);
			item_window.DrawText(critemGetItemClass(BattleItem)->GetName());
			item_window.SetColor(CRCOLOR_WHITE);
			item_window.DrawText(" を手に入れた！");
		} else if(action == 2){
			int chara = levelup_flag[member];
			//---レベルアップ
			levelup_window.Reset();
			levelup_window.Paint();

			levelup_window.SetColor(CRCOLOR_WHITE);
			levelup_window.DrawText("    ");
			levelup_window.DrawText(pBtChara[chara].GetName());
			levelup_window.DrawText("はレベル");
			levelup_window.SetColor(CRCOLOR_GREEN);
			sprintf(&s[0]," %d ",pBtChara[chara].GetLevel());
			levelup_window.DrawText(s);
			levelup_window.SetColor(CRCOLOR_WHITE);
			levelup_window.DrawText("になった");
			levelup_window.AddReturn();

			LEVELUP_STATUS(0,"LP    ",lv_lp[chara],pBtChara[chara].GetMaxLP());
			LEVELUP_STATUS(0,"MC    ",lv_mc[chara],pBtChara[chara].GetMaxMC());
			LEVELUP_STATUS(0,"筋力  ",lv_power[chara],pBtChara[chara].GetPower());
			LEVELUP_STATUS(0,"耐久力",lv_vitality[chara],pBtChara[chara].GetVitality());
			LEVELUP_STATUS(0,"敏捷性",lv_agility[chara],pBtChara[chara].GetAgility());
			LEVELUP_STATUS(0,"精神力",lv_soul[chara],pBtChara[chara].GetSoul());
			LEVELUP_STATUS(0,"魔力  ",lv_magic[chara],pBtChara[chara].GetMagic());
			LEVELUP_STATUS(1,"魔法修得値",lv_magicexp[chara],pBtChara[chara].GetMagicExperience());
		} else if(action == 3){
			//---次のレベルまでの経験値
			next_window.Reset();
			next_window.Paint();

			next_window.DrawText(" 次のレベルまで...");
			next_window.AddReturn();
			for(a = 0;a < BATTLECHARA_PARTY_MAX;a ++){
				if(pBtChara[a].DoExist()){
					next_window.SetColor(CRCOLOR_WHITE);
					sprintf(&s[0],"     %-10s :",pBtChara[a].GetName());
					next_window.DrawText(s);
					next_window.SetColor(CRCOLOR_YELLOW);
					sprintf(&s[0],"%7d",pBtChara[a].GetNextExperience());
					next_window.DrawText(s);
					next_window.AddReturn();
				}
			}
		}
crdataEnableRec(1);
		ew->Refresh();

		AddWorld = let.Get();
	}

	return 1;
}

//---負けた！
CRBATMAIN_API int crbatLose(int turn,int bt_time,CR_BATTLEINFO *pInfo)
{
	int style,ret;
	float Angle = ANGLE(0);
	CrStringWindow win;
	CrSelectWindow sel;
	CrInput ci;

	//---音楽切り替え
	if(pInfo->Music != 0){
		crmusicPlay(CRMUSIC_LOSE,1,CRMUSIC_LOADFORCE);
	}

	win.Create(224,64,12,2);

	//---カメラ切り替え
	crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);
	crbatSetCamera_ViewBattleField(0,Angle,1,500);

	if(crsysGetExtentionLevel() < 3){
		style = CRWIN_BGFILL;
	} else {
		style = CRWIN_BGFILL | CRWIN_BGALPHA;
	}

	win.SetStyle(style);
	win.Reset();
	win.Paint();
	win.DrawText("戦いに負けた...");

	ew->Refresh();
	et->Reset();
	while(1){
		ei->Get();
		if(et->Get() >= 1000 || ei->AnyKey){
			break;
		}
		eiCheckThread();
		eiSleep(1);
	}
//	ci.WaitAnykey();

	crbaseMenuReset();
	crbaseMenuStart();
	do {
		sel.Create(
			BATTLE_COMMAND_LEFT,BATTLE_COMMAND_TOP,11,5,
			"もう一度戦いますか？","戦う;ゲームを終了する;");
		sel.Refresh();
		ret = sel.Select();
	} while(ret == -1);

	if(ret == 0){
		//---88Pro,8820だったら
		if(crdataGetIniFile()->MIDIType >= 2){
			crmusicPlay(CRMUSIC_INIT);
			et->Delay2(1000);
		}
	}

	return ret;
}

CRBATMAIN_API int crbatAvoid(void)
{
	return 1;
}
