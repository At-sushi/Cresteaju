
//---ステータスを表示するかどうか
static int batShowStatus = 1;

CRBATBASE_API void crbatSetShowStatus(int show)
{
	batShowStatus = show;
}

CRBATBASE_API int crbatEnableShowStatus(void)
{
	return batShowStatus;
}

//---キャラクターパターンをセットアップ
CRBATBASE_API void crbatSetupCharaPattern(void)
{
	int a;

	for(a = 0;a < BATTLECHARA_MAX;a ++){
		if(pBtChara[a].IsFriend()){
			pBtChara[a].SetPatternAuto();
		}
	}
}

CRBATBASE_API int crbatGetBattleStatusString(CrBattleCharacter *pChara,eistr *pstr)
{
	int b;
	//---Status
	ei_u32 status = pChara->GetBtStatus();

	pstr[0] = NULL;
	b = 0;
	if(pChara->IsKizetu() && b < 3){
		sprintf(&pstr[b * 2],"気絶");
		b += 2;
	}
	if(status & BTST_ITAMIWAKE && b < 4){
		sprintf(&pstr[b * 2],"痛");
		b ++;
	}
	if(status & BTST_JAKUKA && b < 4){
		sprintf(&pstr[b * 2],"弱");
		b ++;
	}
	if(status & BTST_ZERO && b < 4){
		sprintf(&pstr[b * 2],"低");
		b ++;
	}
	if(status & BTST_HYOTEKI && b < 4){
		sprintf(&pstr[b * 2],"的");
		b ++;
	}
	if(status & BTST_CHINMOKU && b < 4){
		sprintf(&pstr[b * 2],"黙");
		b ++;
	}
	if(status & BTST_KONRAN && b < 4){
		sprintf(&pstr[b * 2],"混");
		b ++;
	}
	if(status & BTST_MAHI && b < 4){
		sprintf(&pstr[b * 2],"痺");
		b ++;
	}
	if(status & BTST_KURAYAMI && b < 4){
		sprintf(&pstr[b * 2],"闇");
		b ++;
	}
	if(status & BTST_DOKU && b < 4){
		sprintf(&pstr[b * 2],"毒");
		b ++;
	}
	if(status & BTST_NEMURI && b < 4){
		sprintf(&pstr[b * 2],"眠");
		b ++;
	}

	pstr[b * 2] = NULL;

	return b;
}

CRBATBASE_API int crbatGetBattlePlusStatusString(CrBattleCharacter *pChara,eistr *pstr,int b)
{
	int c = 0;

	pstr[0] = NULL;
	if(b >= 4)
		return b;

	//---Status
	ei_u32 status = pChara->GetBtStatus();

	if(status & BTST_PROTECT && b < 4){
		sprintf(&pstr[c * 2],"守");
		b ++;
		c ++;
	}
	if(status & BTST_ACCEL && b < 4){
		sprintf(&pstr[c * 2],"素");
		b ++;
		c ++;
	}
	if(status & BTST_FSHIELD && b < 4){
		sprintf(&pstr[c * 2],"魔");
		b ++;
		c ++;
	}
	if(status & BTST_POWER && b < 4){
		sprintf(&pstr[c * 2],"攻");
		b ++;
		c ++;
	}
	if(status & BTST_EXTEND && b < 4){
		sprintf(&pstr[c * 2],"強");
		b ++;
		c ++;
	}
	if(status & BTST_SOUL && b < 4){
		sprintf(&pstr[c * 2],"精");
		b ++;
		c ++;
	}
	if(status & BTST_KAOS && b < 1){
		sprintf(&pstr[c * 2],"カオス");
		b += 3;
		c += 3;
	}
	if(status & BTST_DIST && b < 4){
		sprintf(&pstr[c * 2],"回");
		b ++;
		c ++;
	}

	pstr[c * 2] = NULL;

	return b;
}

CRBATBASE_API int crbatGetBattleResultStatusString(CrBattleCharacter *pChara,eistr *pstr,int b)
{
	int c = 0;

	pstr[0] = NULL;
	if(b >= 4)
		return b;

	for(;b < 4;b ++){
		sprintf(&pstr[c * 2],"－");
		c ++;
	}
	pstr[c * 2] = NULL;

	return b;
}

//---ステータスウィンドウ描画
CRBATBASE_API void crbatDrawStatus(CrStringWindow *pwin)
{
	int a;
	eistr temp[64];
	int vspace = 32,baroffset = 2,num = pwin->GetData();
	int statusbar = 0;//((mode & SHOWSTATUS_STATUSBAR) != 0);
	CrBattleCharacter *pChara;

	if(!crbatEnableShowStatus())
		return;

	pwin->Reset();
	pwin->SetColor(CRCOLOR_YELLOW);
	pwin->DrawText("Name            LP/ Max     MC/ Max    Status");
	pwin->SetColor(CRCOLOR_WHITE);

	for(a = 0;a < num;a ++){
		pwin->AddReturn();

		pChara = &pBtChara[a];
		if(pChara->DoExist()){
			//---名前
			sprintf(temp,"%s",pChara->GetName());
			pwin->SetColor(CRCOLOR_WHITE);
			pwin->DrawText(temp);
			pwin->AddWord(13 - (strlen(temp) - 1));

			//---LP
			sprintf(temp,"%4d",pChara->GetLP());
			pwin->SetColor(crcharaGetStatusColor(pChara->GetLP(),pChara->GetMaxLP()));
			pwin->DrawText(temp);

			pwin->SetColor(CRCOLOR_WHITE);
			pwin->DrawText("/");

			sprintf(temp,"%4d",pChara->GetMaxLP());
			pwin->DrawText(temp);
			pwin->AddWord(3);

			//---MC
			sprintf(temp,"%4d",pChara->GetMC());
			pwin->SetColor(crcharaGetStatusColor(pChara->GetMC(),pChara->GetMaxMC()));
			pwin->DrawText(temp);

			pwin->SetColor(CRCOLOR_WHITE);
			pwin->DrawText("/");

			sprintf(temp,"%4d",pChara->GetMaxMC());
			pwin->DrawText(temp);
			pwin->AddWord(3);

			int length = crbatGetBattleStatusString(pChara,temp);
			pwin->SetColor(CRCOLOR_WHITE);
			pwin->DrawText(temp);

			length = crbatGetBattlePlusStatusString(pChara,temp,length);
			if(length > 0){
				pwin->SetColor(CRCOLOR_GREEN);
				pwin->DrawText(temp);
			}
			if(crbatGetBattleResultStatusString(pChara,temp,length) > 0){
				pwin->SetColor(CRCOLOR_WHITE);
				pwin->DrawText(temp);
			}
		}
	}
}

//---ステータスウィンドウ作成
CRBATBASE_API void crbatShowStatus2(CrStringWindow *pwin,int x,int y,ei_u32 mode)
{
	//---XXXX LP/Max SP/Max MC/Max
	//   
	int a,sx = 20,sy = 20,num = 0;
	int vspace = 32,baroffset = 2;
	int statusbar = ((mode & SHOWSTATUS_STATUSBAR) != 0);

	if(!crbatEnableShowStatus())
		return;

	if((mode & SHOWSTATUS_NORMALSIZE) || (mode & SHOWSTATUS_SMALLSIZE)){
		sx = (12 + 4 + 9 + 1 + 9 + 1 + 9) / 2  + 3; 
	}
	if((mode & SHOWSTATUS_NORMALSIZE)){
		vspace = 32;
	} else if((mode & SHOWSTATUS_SMALLSIZE)){
		vspace = 24;
	}
	
	if(mode & SHOWSTATUS_MAX_1)
		num = 1;
	if(mode & SHOWSTATUS_MAX_4)
		num = 4;
	if(mode & SHOWSTATUS_MAX_5)
		num = 5;
	if(mode & SHOWSTATUS_MAX_8)
		num = 8;

	pwin->SetData(num);
	sy = (vspace * (num)) / 16 + 3;

	for(a = 0;a < 1;a ++){
		pwin->Create(x,y,sx,sy);
		pwin->SetLineSize(vspace);

		//---中身を描画
		crbatDrawStatus(pwin);
		pwin->Refresh();
	}
}

//---ステータス表示
CRBATBASE_API void crbatShowStatus(int x /*= -1*/,int y /*= -1*/,int mode /*= -1*/)
{
	CrStringWindow win;

	if(!crbatEnableShowStatus())
		return;

	if(x == -1)
		x = 224;
	if(y == -1)
		y = 256 + 32;
	if(mode == -1)
		mode = SHOWSTATUS_DEFAULT | SHOWSTATUS_SMALLSIZE | SHOWSTATUS_PARTYMEMBER;
	
	crbatShowStatus2(&win,x,y,mode);
}
