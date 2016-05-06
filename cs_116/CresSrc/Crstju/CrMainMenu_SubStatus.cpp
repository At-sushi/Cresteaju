


void crmainDrawStatusString(CrStringWindow *st1,char *string)
{
	char s[100];
	sprintf(s,"%-8s:  ",string);
	st1->SetColor(CRCOLOR_YELLOW);
	st1->DrawText(s);
}

void crmainDrawStatusValue(CrStringWindow *st1,int v1,int v2 = -1,int long_mode = 0)
{
	char s[100];

	if(long_mode == 0){
		if(v2 == -1)
			sprintf(s,"%4d",v1);
		else
			sprintf(s,"%4d / %4d",v1,v2);
	} else {
		if(v2 == -1)
			sprintf(s,"%8d",v1);
		else
			sprintf(s,"%8d / %8d",v1,v2);
	}

	st1->SetColor(CRCOLOR_WHITE);
	st1->DrawText(s);
}

//---ステータスを描く
void crmainDrawStatus(CrCharacter *pChara)
{
	int a;
	eistr s[80];
	//---ステータス
	CrStringWindow st1,st2;

	st1.Create(32,32 - 16,18,7);
	st2.Create(32,160 - 16,18,20);

	int old = eiSetFont(EISMALL_FONT);
	ew->lpCell[1]->DrawFillBox(
		st1.xGetTop() + 192,st1.yGetTop(),
		st1.xGetTop() + 192 + 72,st1.yGetTop() + 11,
		ep->ToTextRGB(CRCOLOR_BLACK));
	ew->lpCell[1]->DrawText("↑↓切り替え",
		st1.xGetTop() + 192 ,st1.yGetTop(),ep->ToTextRGB(CRCOLOR_WHITE));
	eiSetFont(old);

	st1.SetColor(CRCOLOR_GREEN);
	st1.DrawText(pChara->GetName());
	st1.AddReturn();
	crmainDrawStatusString(&st1,STLEVEL);
	crmainDrawStatusValue(&st1,pChara->GetLevel());
	st1.AddReturn();
	crmainDrawStatusString(&st1,STEXP);
	crmainDrawStatusValue(&st1,pChara->GetExperience(),pChara->GetNextExperience() + pChara->GetExperience(),1);
	st1.AddReturn();

	crmainDrawStatusString(&st1,"     "STNEXTEXP);
	int next = pChara->GetNextExperience() + pChara->GetExperience() - pChara->GetExperience();
	crmainDrawStatusValue(&st1,next,-1,1);
	st1.AddReturn();


	crmainDrawStatusString(&st1,STMEXP);
	crmainDrawStatusValue(&st1,pChara->GetMagicExperience());
	st1.AddReturn(2);

	//---
	crmainDrawStatusString(&st2,STLP_L);
	crmainDrawStatusValue(&st2,pChara->GetLP(),pChara->GetMaxLP());
	st2.AddReturn();

	crmainDrawStatusString(&st2,STMC_L);
	crmainDrawStatusValue(&st2,pChara->GetMC(),pChara->GetMaxMC());
	st2.AddReturn(2);


	crmainDrawStatusString(&st2,STKOUGEKI);
	if(pChara->GetWeapon(0)){
		crmainDrawStatusValue(&st2,pChara->GetEqAtack(0));
	}
	if(pChara->GetWeapon(0) && pChara->GetWeapon(1)){
		st2.SetColor(CRCOLOR_WHITE);
		st2.DrawText(" / ");
	}
	if(pChara->GetWeapon(1)){
		crmainDrawStatusValue(&st2,pChara->GetEqAtack(1));
	}
	st2.AddReturn();

	crmainDrawStatusString(&st2,STBOUGYO);
	crmainDrawStatusValue(&st2,pChara->GetEqDefense());
	st2.AddReturn();
	crmainDrawStatusString(&st2,STMBOUGYO);
	crmainDrawStatusValue(&st2,pChara->GetEqMagicDefense());
	st2.AddReturn();

	crmainDrawStatusString(&st2,STKOUDOU);
	crmainDrawStatusValue(&st2,pChara->GetEqAction());
	st2.AddReturn();

	crmainDrawStatusString(&st2,STKAIHI);
	crmainDrawStatusValue(&st2,pChara->GetEqAvoidProb() / 10);
	st2.DrawText("%");
	st2.AddReturn();
	crmainDrawStatusString(&st2,STMKAIHI);
	crmainDrawStatusValue(&st2,pChara->GetEqMagicAvoidProb() / 10);
	st2.DrawText("%");
	st2.AddReturn(2);


	crmainDrawStatusString(&st2,STCHIKARA);
	crmainDrawStatusValue(&st2,pChara->GetEqPower());
	st2.AddReturn();
	crmainDrawStatusString(&st2,STTAIRYOKU);
	crmainDrawStatusValue(&st2,pChara->GetEqVitality());
	st2.AddReturn();
	crmainDrawStatusString(&st2,STSUBAYASA);
	crmainDrawStatusValue(&st2,pChara->GetEqAgility());
	st2.AddReturn();
	crmainDrawStatusString(&st2,STSEISHINRYOKU);
	crmainDrawStatusValue(&st2,pChara->GetEqSoul());
	st2.AddReturn();
	crmainDrawStatusString(&st2,STMARYOKU);
	crmainDrawStatusValue(&st2,pChara->GetEqMagic());
	st2.AddReturn();

	//---装備品
	int number;
	CrItem *pItem;
	CrStringWindow st3;

	st3.Create(336,32 - 16,18,12);
	st3.DrawText("装備品");
	st3.AddReturn(2);

	for(a = 0;a < EQ_ALL_MAX;a ++){
		number = pChara->GetEquipment(a);
		if(a < EQ_WEAPON_MAX)
			st3.SetColor(CRCOLOR_GREEN);
		else if(a  < EQ_WEAPON_MAX + EQ_PROTECTOR_MAX)
			st3.SetColor(CRCOLOR_YELLOW);
		else
			st3.SetColor(CRCOLOR_AQUA);

		if(number){
			pItem = critemGetItemClass(number);
			if(a < EQ_WEAPON_MAX){
				//---武器
				sprintf(s,"%  -22s 攻撃:%3d",pItem->GetName(),pItem->GetAtack());
			} else {
				sprintf(s,"%  -22s",pItem->GetName());
			}
			st3.DrawText(s);
		}
		st3.AddReturn();
	}

	ew->Refresh();
}

//---ステータス表示
int crmainMenuStatus(void)
{
	int c,member;
	static CRWIN_SELECTINFO info;
	CrCharacter *pChara;

	//---キャラクター選択
	while(1){
		crmainClearMenu();
//		crbaseClearScreen();
		member = crcharaSelectMember(32,32,0/*CRBASE_SELECTPLAYER_MC*/,"誰のステータス？",&info);
		if(member == -1)
			break;
		pChara = crcharaGetPartyMember(member);

		crmainClearMenu();
//		crbaseClearScreen();
		crmainDrawStatus(pChara);

		//---キー入力待ち
		crbaseMenuReset();
		CrInput input;
		input.Get();
		crbaseMenuStart();
		do {
			eiSleep(1);
			input.Get();
			
			c = 0;
			if(input.IsLeft() || input.IsUp()){
				member = crcharaPreviousMember(member);
				c = 1;
			} else if(input.IsRight() || input.IsDown()){
				member = crcharaNextMember(member);
				c = 1;
			}
			if(c){
				//---表示キャラ切り替え
				pChara = crcharaGetPartyMember(member);
				//crbaseClearScreen();
				crmainClearMenu();
				crmainDrawStatus(pChara);
			}
		} while(!(input.IsButton(0) || input.IsButton(1)));
	}

	return 1;
}
