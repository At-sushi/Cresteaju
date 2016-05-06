
static CrEmptyWindow MainMenuBFWin;
static eiCell BFCell[8];

void crmainMenuBattle_LoadData(void)
{
	int x;
	eistr s[100];
	CrCharacter *pChara;

	for(x = 0;x < MEMBER_MAX;x ++){
		pChara = crcharaGetPartyMember(x);
		if(pChara != NULL){
			sprintf(s,"%s%s",CR_DATADIR4,pChara->GetBattleFileName());
			eiCellReadPattern(
				&BFCell[0],
				s,CR_DATAFILE4,crdataGetFileMode(),
				x,1,32,32);
		}
	}
}

void crmainMenuBattle_UnloadData(void)
{
	int x;

	for(x = 0;x < MEMBER_MAX;x ++){
		BFCell[x].Release();
	}
}

void crmainMenuBattle_DrawField(int blink)
{
	int a,x,y;
	int size = 33;
	int max_x = BATTLEFIELD_MAX_X - 2,max_y = BATTLEFIELD_MAX_Y / 2 -2;
	CrCharacter *pChara;

	MainMenuBFWin.Create(32,192,(32 * 14) / 16,(32 * 5) / 16);

	int x_top = MainMenuBFWin.xGetTop() + 72,
		y_top = MainMenuBFWin.yGetTop() + 16;

	ew->lpCell[1]->DrawText("前方↑",
		MainMenuBFWin.xGetTop() + 16,
		MainMenuBFWin.yGetTop() + 16,
		ep->ToTextRGB(CRCOLOR_WHITE));

	ew->lpCell[1]->DrawText("後方↓",
		MainMenuBFWin.xGetTop() + 16,
		MainMenuBFWin.yGetTop() + 16 + 32 * 3,
		ep->ToTextRGB(CRCOLOR_WHITE));

	for(y = 0;y < max_y;y ++){
		for(x = 0;x < max_x;x ++){
			ew->lpCell[1]->DrawFillBox(
				(x * size) + x_top,
				(y * size) + y_top,
				(x * size) + x_top + size - 1,
				(y * size) + y_top + size - 1,
				ep->MakeRGB(0,0,64)
			);
			ew->lpCell[1]->DrawBox(
				(x * size) + x_top,
				(y * size) + y_top,
				(x * size) + x_top + size,
				(y * size) + y_top + size,
				ep->MakeRGB(0,128,192)
			);
		}
	}
	//---キャラクター描画
	for(a = 0;a < MEMBER_MAX;a ++){
		pChara = crcharaGetPartyMember(a);
		if(pChara != NULL){

			x = (pChara->GetBattleFieldStartX() - 1);
			y = max_y - 1 - (pChara->GetBattleFieldStartY() - 1);

			BFCell[a].PutTrans(ew->lpCell[1],
				(x * size) + x_top + 1,
				(y * size) + y_top + 1
			);

			if(a == blink){
				pBattleCursorCell[5].PutTrans(ew->lpCell[1],
					(x * size) + x_top + 1,
					(y * size) + y_top + 1
				);
				pBattleCursorCell[5].PutTrans(ew->lpCell[1],
					(x * size) + x_top + 17,
					(y * size) + y_top + 1
				);
				pBattleCursorCell[5].PutTrans(ew->lpCell[1],
					(x * size) + x_top + 1,
					(y * size) + y_top + 17
				);
				pBattleCursorCell[5].PutTrans(ew->lpCell[1],
					(x * size) + x_top + 17,
					(y * size) + y_top + 17
				);
			}
		}
	}

	MainMenuBFWin.Refresh();
}

int crmainBattle_SelectCharaCallBack(CrSelectWindow *pwin,eiCell *pCell,int Message,ei_u32 Param1,ei_u32 Param2,int Param3)
{
	if(Message == CRWIN_SELECT_MESMOVECURSOR){
		//---カーソル移動
		int index = Param3;
		crmainMenuBattle_DrawField(index);
		return 1;
	}
	if(Message == CRWIN_SELECT_MESSHOWHELP){
		//---ヘルプ表示
		int index = Param3;
		crmainMenuBattle_DrawField(index);
		return 1;
	}

	return 0;
}

//---誰かそこにいるか
int crmainManuBattle_IsThere(int my,int x,int y)
{
	int a;
	CrCharacter *pChara;
	int max_x = BATTLEFIELD_MAX_X - 2,max_y = BATTLEFIELD_MAX_Y / 2 -2;

	for(a = 0;a < MEMBER_MAX;a ++){
		if(a == my){
			continue;
		}
		pChara = crcharaGetPartyMember(a);
		if(pChara != NULL){
			if(x + 1 == pChara->GetBattleFieldStartX()
				&& max_y - y == pChara->GetBattleFieldStartY()){
				return 1;
			}
		}
	}
	return 0;
}

//---戦闘設定
int crmainMenuBattle(void)
{
	int member;
	static CRWIN_SELECTINFO info;

	crmainMenuBattle_LoadData();

	crmainClearMenu();

	do {
		crmainMenuBattle_DrawField(-1);

		member = crcharaSelectMember( 32,32,
			CRBASE_SELECTPLAYER_LP | CRBASE_SELECTPLAYER_MC,
			"バトルフィールド位置設定",&info,
			crmainBattle_SelectCharaCallBack);

		if(member != -1){
			//---移動させる
			int x,y,hx = -1,hy = -1,ax,ay;
			int kx,ky;
			int size = 33;
			int max_x = BATTLEFIELD_MAX_X - 2,max_y = BATTLEFIELD_MAX_Y / 2 -2;
			CrCharacter *pChara = crcharaGetPartyMember(member);
			CrInput ci;
			int x_top = MainMenuBFWin.xGetTop() + 16,
			y_top = MainMenuBFWin.yGetTop() + 16;
			ci.Get();

			kx = x = (pChara->GetBattleFieldStartX() - 1);
			ky = y = max_y - 1 - (pChara->GetBattleFieldStartY() - 1);

			crbaseMenuReset();
			crbaseMenuStart();

			while(1){
				ci.Get();
				if(ci.IsButton(0)){
					crsoundPlay(CRSOUND_BTN_A);
					pChara->SetBattleFieldStartPos(kx + 1,max_y - ky);
					break;
				}
				if(ci.IsButton(1)){
					//---決定
					crsoundPlay(CRSOUND_BTN_B);
					break;
				}

				ax = ay = 0;
				if(ci.IsLeft())
					ax --;
				if(ci.IsRight())
					ax ++;
				if(ci.IsUp())
					ay --;
				if(ci.IsDown())
					ay ++;

				if(ax){
					for(x += ax;;x += ax){
						if(x >= max_x){
							x = 0;
						}
						if(x < 0){
							x = max_x - 1;
						}
						if(!crmainManuBattle_IsThere(member,x,y))
							break;
					}
				} else if(ay){
					for(y += ay;;y += ay){
						if(y >= max_y){
							y = 0;
						}
						if(y < 0){
							y = max_y - 1;
						}
						if(!crmainManuBattle_IsThere(member,x,y))
							break;
					}
				}

				if(x < 0){
					for(x = max_x;;x --){
						if(!crmainManuBattle_IsThere(member,x,y))
							break;
					}
				}
				if(x >= max_x){
					for(x = 0;;x ++){
						if(!crmainManuBattle_IsThere(member,x,y))
							break;
					}
				}

				if(y < 0){
					for(y = max_y;;y --){
						if(!crmainManuBattle_IsThere(member,x,y))
							break;
					}
				}
				if(y >= max_y){
					for(y = 0;;y ++){
						if(!crmainManuBattle_IsThere(member,x,y))
							break;
					}
				}

				pChara->SetBattleFieldStartPos(x + 1,max_y - y);

				if(x != hx || y != hy){
					crmainMenuBattle_DrawField(member);
					pBattleCursorCell[5].PutTrans(ew->lpCell[1],
						(x * size) + x_top + 1,
						(y * size) + y_top + 1
					);
					pBattleCursorCell[5].PutTrans(ew->lpCell[1],
						(x * size) + x_top + 17,
						(y * size) + y_top + 1
					);
					pBattleCursorCell[5].PutTrans(ew->lpCell[1],
						(x * size) + x_top + 1,
						(y * size) + y_top + 17
					);
					pBattleCursorCell[5].PutTrans(ew->lpCell[1],
						(x * size) + x_top + 17,
						(y * size) + y_top + 17
					);
				}

				hx = x;
				hy = y;
			}
		}
	} while(member != -1);

	crmainMenuBattle_UnloadData();

	return MAINLOOP_NOMESSAGE;
}