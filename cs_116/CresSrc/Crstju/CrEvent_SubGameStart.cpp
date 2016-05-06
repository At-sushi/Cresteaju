ei_s32 opbatCallBack(int turn,int action,int number,
				  ei_u32 com,CrCharacter *chara)
{
	CR_BATTLECOMMAND *pCommand = (CR_BATTLECOMMAND *)com;
	CrBattleCharacter *pChara = (CrBattleCharacter *)chara;

	if(action == 0){
		return 1;
	}
	if(action == 1){
		if(number == 0){
			//---ガゼール
			pCommand->Main = BAT_COMMAND_WEAPON;
			pCommand->Sub[0] = 0;
			pCommand->Hit = 1;
			pCommand->Range = BAT_TARGET_ENEMYSINGLE;
			pCommand->Target = (ei_u32)crbatRandomSelect(pChara,BAT_TARGET_ENEMY);
		} else {
			pCommand->Main = BAT_COMMAND_WAIT;
		}
	}

	return 1;
}

ei_s32 opbatCallBack2(int turn,int action,int number,
				  ei_u32 com,CrCharacter *chara)
{
	CR_BATTLECOMMAND *pCommand = (CR_BATTLECOMMAND *)com;
	CrBattleCharacter *pChara = (CrBattleCharacter *)chara;
	static CrBattleCharacter *pGazell = NULL;

	if(action == 0){
		if(turn < 2)
			return 1;
		else
			return 0;
	}
	if(action == 1){
		memset(pCommand,0,sizeof(CR_BATTLECOMMAND));
		if(number == 0){
			//---ガゼール
			pGazell = pChara;
			if(turn < 1){
				pCommand->Main = BAT_COMMAND_WEAPON;
				pCommand->Sub[0] = 0;
				pCommand->Hit = 1;
				pCommand->Range = BAT_TARGET_ENEMYSINGLE;
				pCommand->Target = (ei_u32)crbatRandomSelect(pChara,BAT_TARGET_ENEMY);
			} else {
				pCommand->Main = BAT_COMMAND_WAIT;
			}
		} else {
			//---フォールン
			if(turn < 1){
				pCommand->Main = BAT_COMMAND_WAIT;
			} else {
				pCommand->Main = BAT_COMMAND_MAGIC;
				pCommand->Sub[0] = 31;
				pCommand->Hit = 1;
				pCommand->NoTurnTarget = 1;//---振り向かせない
				pCommand->Range = BAT_TARGET_FRIENDSINGLE;
				pCommand->Target = (ei_u32)(pGazell);
			}
		}
	}
	if(action == 2){
		if(turn == 1 && number == 1){
			//---フォールン
			CrMesManager mes;
			mes.CreateNewMessage(-1,-1,32,24,5);
			mes.OpenMessage("Opening.msg",7);
			mes.ReadMessage();
			mes.Draw();
			mes.CloseMessage();
		}
	}

	return 1;
}

//---サーフェイススワップ
void OpeningMakeSurface(int scene)
{
	eiDDSurface *pSurface = (eiGetSurfacePointer() + 2);

	crfieldPaletteChange(PALETTE_NIGHT);
	//---２枚目のキャラクターサーフェイスに転送
	RECT rect = {0,0,640,480};
	pSurface[0].Put(&pSurface[1],0,0,&rect,DDBLTFAST_WAIT);

	//---読み直し
	em->ReloadPattern();
	em->SetSurface();
}

//---サーフェイススワップ
void OpeningSwapSurface(void)
{
	int y;
	eiDDSurface *pSurface = (eiGetSurfacePointer() + 2);
	RECT rect = {0,0,640,480};

	for(y = 0;y < 480;y += 32){
		rect.top = y;
		rect.bottom = rect.top + 32;
		pSurface[0].Put(&pSurface[1],0,480 - 32,&rect,DDBLTFAST_WAIT);

		rect.top = y;
		rect.bottom = rect.top + 32;
		pSurface[1].Put(&pSurface[0],0,y,&rect,DDBLTFAST_WAIT);

		rect.top = 480 - 32;
		rect.bottom = rect.top + 32;
		pSurface[1].Put(&pSurface[1],0,y,&rect,DDBLTFAST_WAIT);
	}
}

//---オープニング
CREVENT_API void creventOpening(void)
{
	int a;
	CrMesManager mes;

	//---サウンド設定
	crmusicFadeOut(1);
	crefectScreenChange_FadeOut(NULL,-1,2000);
	crbaseClearScreen(0x03);

	et->Delay2(2000);

	//---クレスフィールド町中
	crfieldChangeMap(15,0,1,0);
	crfieldChangePos(37,10,1);
	OpeningMakeSurface(0);
	OpeningSwapSurface();
	mcShow(0);
	evFieldNoFlip(0,1);
	evFadeIn(1000);
	evFrameWait(2000,1);
	npPos(3,37,0);
	npShow(3,1);
	//---走ってくる
	for(a = 0;a < 24;a ++){
		npMove(3,0,1);
		evFrame();
	}

	evFadeOut(1000);
	crfieldChangeScene(1,8,11);
//	crfieldChangeMap(15,1,1,0);
//	crfieldChangePos(8,11,1);

	//---ルナン
	npPos(0,11,8);
	npDir(0,SOUTH);
	//---ガゼール
	npPos(1,13,10);
	npDir(1,WEST);
	//---フォールン
	npPos(5,3,10);
	npDir(5,EAST);

	npPos(2,7,8);
	npDir(2,SOUTH);
	npPos(3,11,12);
	npDir(3,NORTH);

	crmusicPlay(CRMUSIC_INIT);
	evFieldNoFlip(0,1);
	evFadeIn(1000);

	//---沈黙
	evFrameWait(4000,1);
	//---来たぞ！！
	npPos(4,14,17);
	npDir(4,NORTH);

	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(4,-1,0);
		else
			npMove(4,0,-1);
		evFrame();
	}
	for(a = 0;a < 5;a ++){
		if(a == 2)
			npDir(1,SOUTH);
		if(a == 3)
			npDir(3,SOUTH);

		mcMove(1,1);
		evFrame();
	}

	crmusicPlay(CRMUSIC_DRAGONBREATH);
	mes.OpenMessage("Opening.msg",6);
	mes.ReadDraw();

	for(a = 0;a < 5;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(1000,1);
	//---ついにきたか・・・
	mes.ReadDraw();

	for(a = 0;a < 5;a ++){
		npMove(4,0,-1);
		evFrame();
	}
	mes.ReadDraw();
	//---勝算ありじゃあ
	mes.ReadDraw();

	for(a = 0;a < 3;a ++){
		if(a < 2)
			npMove(0,1,0);
		else
			npDir(0,SOUTH);
		evFrame();
	}
	//---わたくしもたたかうでございます
	mes.ReadDraw();

	npDir(1,WEST);
	evFrameWait(500,1);
	npDir(1,NORTH);
	evFrameWait(500,1);
	mes.ReadDraw();

	for(a = 0;a < 6;a ++){
		if(a < 4)
			mcMove(-1,0);
		else
			mcMove(0,1);
		evFrame();
	}
	for(a = 0;a < 10;a ++){
		if(a < 1)
			npMove(1,1,0);
		else if(a < 4)
			npMove(1,0,1);
		else if(a < 9)
			npMove(1,-1,0);
		else
			npDir(1,NORTH);

		if(a == 5)
			npDir(4,SOUTH);
		if(a == 7)
			npDir(5,SOUTH);
		evFrame();
	}
	mes.ReadDraw();
	mes.ReadDraw();
	mes.ReadDraw();
	evFrameWait(1000,1);

	//---でも
	OpeningSwapSurface();
	evScene(2,37,20);
	evFrameWait(1000,1);
	for(a = 0;a < 8;a ++){
		npMove(0,-1,0);
		evFrame();
	}
	evFrameWait(500,1);
	mes.ReadDraw();
	evFrameWait(1000,1);

	OpeningSwapSurface();
	evScene(1,10,14);
	for(a = 0;a < 7;a ++){
		if(a < 6)
			npMove(1,-1,0);
		else
			npDir(1,NORTH);
		evFrame();
	}
	//---じゅんびおっけー？
	mes.ReadDraw();
evFrameWait(500);
for(a = 0;a < 6;a ++){
	mcMove(-1,0);
	evFrame();
}
evFrameWait(500);
npMove(5,0,1);
evFrame();
evFrameWait(500);
	mes.ReadDraw();
evFrameWait(500);
for(a = 0;a < 6;a ++){
	mcMove(1,0);
	evFrame();
}

	npPos(6,13,17);
	npDir(6,NORTH);
	for(a = 0;a < 6;a ++){
		if(a < 4)
			npMove(6,0,-1);
		else
			npMove(6,-1,0);
		if(a == 5)
			npDir(1,EAST);
		evFrame();
	}
	mes.ReadDraw();
	for(a = 0;a < 6;a ++){
		if(a < 5)
			npMove(1,1,0);
		else
			npMove(1,0,1);
		evFrame();
	}
	npDir(1,WEST);
	evFrameWait(250,1);
	npDir(1,NORTH);
	evFrameWait(1000,1);
	//---いくぞ！！
	mes.ReadDraw();
	evFrameWait(500,1);

	//---出撃
	for(a = 0;a < 50;a ++){
		if(a < 0){
		} else if(a < 3){
			npMove(1,0,1);
		} else if(a < 9){
			npMove(1,1,0);
		} else {
			npShow(1,0);
		}

		if(a < 4){
		} else if(a < 5){
			npMove(4,1,0);
		} else if(a < 11){
			npMove(4,0,1);
		} else {
			npShow(4,0);
		}

		if(a < 7){
		} else if(a < 10){
			npMove(6,1,0);
		} else if(a < 14){
			npMove(6,0,1);
		} else {
			npShow(6,0);
		}

		if(a < 8){
		} else if(a < 9){
			npMove(0,1,0);
		} else if(a < 18){
			npMove(0,0,1);
		} else {
			npShow(0,0);
		}

		if(a < 0){
		} else if(a < 5){
			npMove(2,-1,0);
		} else if(a < 10){
			npMove(2,0,1);
		} else if(a < 22){
			npMove(2,1,0);
		} else if(a < 26){
			npMove(2,0,1);
		} else {
			npShow(2,0);
		}

		if(a < 22){
		} else if(a < 25){
			npMove(3,1,0);
		} else if(a < 30){
			npMove(3,0,1);
		} else {
			npShow(3,0);
		}

		if(a < 21){
		} else if(a < 24){
			npMove(5,0,1);
		} else if(a < 35){
			npMove(5,1,0);
		} else if(a < 38){
			npMove(5,0,1);
		} else {
			npShow(5,0);
		}
		evFrame();
	}

	//---フォールンが
	OpeningSwapSurface();
	evScene(2,37,20);
	evFrameWait(1500,1);
	mes.ReadDraw();
	evFrameWait(1000,1);
	for(a = 0;a < 6;a ++){
		npMove(4,1,0);
		evFrame();
	}
	//---てえへんだ、てえへんだ
	mes.ReadDraw();
	npMove(1,0,1);
	evFrame();
	npDir(1,WEST);
	evFrame();
	mes.ReadDraw();
	mes.ReadDraw();

	evFrameWait(250);

	crfieldChangeScene(0,38,58);
	OpeningSwapSurface();
	npPos(12,34,60);
	npDir(12,EAST);
	npPos(13,35,61);
	npDir(13,EAST);
	evScene(0,38,58);

	npPos(0,44,63);
	npShow(0,0);
	npPos(1,44,63);
	npShow(1,0);
	npPos(2,44,63);
	npShow(2,0);
	npPos(3,44,63);
	npShow(3,0);
	npPos(4,44,63);
	npShow(4,0);
	npPos(5,44,63);
	npShow(5,0);
	npPos(14,44,63);
	npShow(14,0);
	evFrameWait(1000,1);
	//---出撃じゃああああああ
	for(a = 0;a < 50;a ++){
		if(a < 7){
			npMove(1,-1,0);
		} else {
			npMove(1,0,-1);
		}
		if(a < 4){
		} else if(a < 11){
			npMove(3,-1,0);
		} else {
			npMove(3,0,-1);
		}
		if(a < 6){
		} else if(a < 13){
			npMove(4,-1,0);
		} else {
			npMove(4,0,-1);
		}
		if(a < 11){
		} else if(a < 18){
			npMove(0,-1,0);
		} else {
			npMove(0,0,-1);
		}
		if(a < 15){
		} else if(a < 22){
			npMove(5,-1,0);
		} else {
			npMove(5,0,-1);
		}
		if(a < 17){
		} else if(a < 24){
			npMove(14,-1,0);
		} else {
			npMove(14,0,-1);
		}
		if(a < 10){
		} else if(a < 12){
			npMove(12,1,0);
		} else {
			npMove(12,0,-1);
		}
		if(a < 16){
		} else if(a < 17){
			npMove(13,1,0);
		} else {
			npMove(13,0,-1);
		}

		if(a < 25){
		} else if(a < 32){
			npMove(2,-1,0);
		} else if(a < 38){
			npMove(2,0,-1);
		} else if(a < 39){
			//---フォールン振り返る
			evFrameWait(2000,1);
			npDir(2,EAST);
			evFrameWait(500,1);
			npDir(2,SOUTH);
			evFrameWait(2000,1);
			npDir(2,EAST);
			evFrameWait(500,1);
			npDir(2,NORTH);
			evFrameWait(500,1);
		} else {
			npMove(2,0,-1);
		}
		evFrame();
	}
	for(a = 0;a < 15;a ++){
		npShow(a,0);
	}
/*	for(a = 0;a < 48;a ++){
		mcMove(0,-1);
		evFrame();
	}
*/
	//---睨み合い！！
//	crfieldChangeScene(0,37,10);

	npPos(0,35,11);
	npDir(0,NORTH);
	npPos(1,37, 9);
	npDir(1,NORTH);
	npPos(2,37,10);
	npDir(2,NORTH);
	npPos(3,36,10);
	npDir(3,NORTH);
	npPos(4,38,11);
	npDir(4,NORTH);
	npPos(5,39, 9);
	npDir(5,NORTH);
	//---et
	npPos(6,37, 7);
	npDir(6,SOUTH);
	npPos(7,36, 6);
	npDir(7,SOUTH);
	npPos(8,38, 7);
	npDir(8,SOUTH);
	npPos(9,36, 5);
	npDir(9,SOUTH);
	npPos(10,39, 6);
	npDir(10,SOUTH);
	npPos(11,37, 5);
	npDir(11,SOUTH);

//	OpeningSwapSurface();
	for(a = 0;a < 48;a ++){
		mcMove(0,-1);
		evFrame();
	}
//	evScene(0,37,10);

	evFrameWait(1000,1);
	mes.ReadDraw(2);

	//---ふざけないで
	evFrameWait(250);
	npMove(0,0,-1);
	evFrame();
	evFrameWait(250);

	mes.ReadDraw(3);

	npMove(1,0,-1);
	evFrame();
	evFrameWait(100);
//---戦い！！
	//---パーティー設定
	for(a = 0;a < MEMBER_MAX;a ++){
		pPartyInfo->PartyMember[a] = -1;
	}
	pPartyInfo->PartyMember[0] = 14;

	CR_BATTLEINFO BatInfo;
	memset(&BatInfo,0,sizeof(BatInfo));
	BatInfo.FailOK = 1;
	BatInfo.Music = 0;
	BatInfo.Mode = 0;
	BatInfo.ScreenEfect = 1;
	BatInfo.Enemy[0].Enemy = 12;
	BatInfo.Enemy[0].x = 5;
	BatInfo.Enemy[0].y = 10;
	BatInfo.Enemy[1].Enemy = 13;
	BatInfo.Enemy[1].x = 7;
	BatInfo.Enemy[1].y = 8;
	BatInfo.Enemy[2].Enemy = -1;
	BatInfo.DontShowAfterBattle = 1;
	BatInfo.lpTurnCallBack = opbatCallBack;
//pPartyInfo->PartyMember[1] = 15;
	crbatSetShowStatus(0);
	crbatEventBattle(&BatInfo);

	//---今度はフォールンと２人たっぐよ！
	OpeningMakeSurface(0);
	OpeningSwapSurface();
	npPos(6,0,0);
	npPos(7,0,0);
	evFrameWait(1000,1);
	mes.ReadDraw();
	npMove(1,0,-1);
	npMove(2,0,-1);
	evFrame();
	evFrameWait(100);
	pPartyInfo->PartyMember[1] = 15;

	memset(&BatInfo,0,sizeof(BatInfo));
	BatInfo.FailOK = 1;
	BatInfo.Music = 0;
	BatInfo.Mode = 0;
	BatInfo.ScreenEfect = 1;
	BatInfo.Enemy[0].Enemy = 14;
	BatInfo.Enemy[0].x = 5;
	BatInfo.Enemy[0].y = 10;
	BatInfo.Enemy[1].Enemy = 15;
	BatInfo.Enemy[1].x = 7;
	BatInfo.Enemy[1].y = 8;
	BatInfo.Enemy[2].Enemy = -1;
	BatInfo.DontShowAfterBattle = 1;
	BatInfo.lpTurnCallBack = opbatCallBack2;
	crbatEventBattle(&BatInfo);
	crbatSetShowStatus(1);

	//---フォールン、何すんじゃい
	OpeningMakeSurface(0);
	OpeningSwapSurface();
	evField(0,1);
	evFrameWait(1000,1);
	mes.ReadDraw();
	for(a = 0;a < 6;a ++){
		if(a < 1)
			npMove(2,0,-1);
		else if(a < 2)
			npMove(2,-1,0);
		else if(a < 4)
			npMove(2,0,-1);
		else if(a < 5)
			npMove(2,1,0);
		else
			npDir(2,SOUTH);
		evFrame();
	}
	evFrameWait(2000,1);
	//---フォールンが・・・
	OpeningSwapSurface();
	evScene(2,37,20);
	evFrameWait(1500,1);
	mes.ReadDraw();
	evFrameWait(1000,1);

	OpeningSwapSurface();
	evScene(0,37,10);
	evFrameWait(1000,1);
	for(a = 0;a < 4;a ++){
		if(a < 2)
			npMove(0,0,-1);
		else if(a < 3)
			npMove(0,1,0);
		else
			npDir(0,NORTH);
		evFrame();
	}
	mes.ReadDraw();
	evFrameWait(2000,1);
	//---すべてはエターナル
	mes.ReadDraw();
	evFrameWait(500,1);
	mes.ReadDraw();
	//---いいか！
	evFrameWait(500,1);
	npDir(2,WEST);
	evFrameWait(250,1);
	npDir(2,NORTH);
	evFrameWait(500,1);
	mes.ReadDraw();
	evFrameWait(500,1);
	npDir(2,WEST);
	evFrameWait(250,1);
	npDir(2,SOUTH);
	evFrameWait(500,1);
	//---はい、
	mes.ReadDraw();
	for(a = 0;a < 21;a ++){
		if(a < 3)
			npMove(8,0,1);
		else if(a < 4)
			npMove(8,1,0);
		else
			npMove(8,0,1);

		if(a < 2)
			npMove(9,0,1);
		else if(a < 3)
			npMove(9,-1,0);
		else
			npMove(9,0,1);

		if(a < 4){
		} else if(a < 6)
			npMove(10,0,1);
		else if(a < 7)
			npMove(10,-1,0);
		else if(a < 9)
			npMove(10,0,1);
		else if(a < 10)
			npMove(10,1,0);
		else
			npMove(10,0,1);

		if(a < 1)
			npMove(11,1,0);
		else if(a < 6)
			npMove(11,0,1);
		else if(a < 7)
			npMove(11,1,0);
		else
			npMove(11,0,1);
		evFrame();

		if(a < 10){
		} else if(a < 11)
			npDir(2,WEST);
		else if(a < 12)
			npDir(2,NORTH);
		else if(a < 14)
			npMove(2,0,-1);
		else if(a < 15)
			npDir(2,EAST);
		else if(a < 16)
			npDir(2,SOUTH);
	}
	mes.ReadDraw(2);
	evFrameWait(1000,1);

	//---不利な状況・・・
	OpeningSwapSurface();
	evScene(2,37,20);
	evFrameWait(1500,1);
	npMove(0,-1,0);
	evFrame();
	for(a = 0;a < 6;a ++){
		mcMove(-1,0);
		evFrame();
	}
	mes.ReadDraw();
	evFrameWait(1000,1);

	//---父さん大丈夫？
	OpeningSwapSurface();
	evScene(0,37,10);
	evFrameWait(1000,1);
	for(a = 0;a < 2;a ++){
		if(a < 1)
			npMove(0,0,-1);
		else
			npDir(0,EAST);
		evFrame();
	}
	mes.ReadDraw();

	evFrameWait(500,1);
	mes.ReadDraw();

	evFrameWait(1000,1);
	mes.ReadDraw(3);
	//---ガッツの一撃！
	for(a = 0;a < 2;a ++){
		npMove(1,0,-1);
		if(a == 1)
			npDir(0,NORTH);
		evFrame();
	}
	evFill(ep->MakeRGB(255,255,255));
	crsoundPlay(CRSOUND_ATACK1);
	ew->Flip();
	for(a = 0;a < 2;a ++){
		mcMove(0,-1);
		evFrame();
	}
	evFrameWait(500,1);
	mes.ReadDraw(2);
	evFrameWait(250,1);
	mes.ReadDraw();

	//---ぷりーず、うぇいと、あいるかむひやー
	evFrameWait(1500,1);
	for(a = 0;a < 10;a ++){
		if(a < 3)
			npMove(0,1,0);
		else if(a < 5)
			npMove(0,0,-1);
		else if(a < 10)
			npMove(0,1,0);
		evFrame();
	}
	npDir(0,NORTH);
	evFrameWait(200,1);
	npDir(0,WEST);
	evFrameWait(200,1);
	//---まっててちょんまげっ
	mes.ReadDraw();

	evFrameWait(200,1);
	npDir(0,NORTH);
	evFrameWait(200,1);
	npDir(0,EAST);
	evFrameWait(200,1);

	for(a = 0;a < 8;a ++){
		npMove(0,1,0);
		evFrame();
	}
	evFrameWait(500,1);

	OpeningSwapSurface();
	evScene(2,31,20);
	for(a = 0;a < 12;a ++){
		npMove(0,-1,0);
		evFrame();
	}
	mes.ReadDraw(3);
	evFrameWait(1000,1);
	//---私は
	npDir(0,NORTH);
	evFrameWait(250,1);
	npDir(0,EAST);
	evFrameWait(1000,1);
	mes.ReadDraw();
	evFrameWait(500,1);
	npDir(0,NORTH);
	evFrameWait(250,1);
	npDir(0,WEST);
	evFrameWait(250,1);

	for(a = 0;a < 8;a ++){
		mcMove(-1,0);
		evFrame();
	}

	int old = ef->SetMoveSpeed(2);
	for(a = 0;a < 12;a ++){
		npMove(0,-1,0);
		mcMove(-1,0);
		evFrame();
	}
	mes.ReadDraw();
	ef->SetMoveSpeed(old);

	//---グラウンドシップにお乗りこみ
	for(a = 0;a < 12;a ++){
		npMove(0,-1,0);
		evFrame();
	}

	crhistSubBattleCount();
	crhistSubBattleCount();

	mes.CloseMessage();
}

CREVENT_API void creventInitCharaInfo(void)
{
	int a = 0;
	/*
	ルナン、ディザ、ナック、サヴィアー、ユミ、ライゼル、シンディ
	*/

	//---------------------------------
	a = 0;
	memset(&pCharacterInfo[a].CharaInfo,0,sizeof(pCharacterInfo[a].CharaInfo));
	sprintf(pCharacterInfo[a].CharaInfo.Name,"ルナン");
	pCharacterInfo[a].SetWho(a + 1);
	pCharacterInfo[a].SetMaxLP(23);
	pCharacterInfo[a].SetLP(23);
	pCharacterInfo[a].SetMaxMC(20);
	pCharacterInfo[a].SetMC(20);
	pCharacterInfo[a].SetWeapon(0,1);
	pCharacterInfo[a].SetProtector(0,91);
	pCharacterInfo[a].SetBattleFieldStartPos(6,3);
	pCharacterInfo[a].CharaInfo.level = 1;
	pCharacterInfo[a].CharaInfo.power = 7;
	pCharacterInfo[a].CharaInfo.vitality = 3;
	pCharacterInfo[a].CharaInfo.agility = 6;
	pCharacterInfo[a].CharaInfo.soul = 10;
	pCharacterInfo[a].CharaInfo.magic = 12;

	pCharacterInfo[a].CharaInfo.magic_experience = 10;

	pCharacterInfo[a].CharaInfo.sub_hit_prob = 333;
/*
	pCharacterInfo[a].SetMaxLP(9999);
	pCharacterInfo[a].SetLP(9999);
	pCharacterInfo[a].SetMaxMC(9999);
	pCharacterInfo[a].SetMC(9999);
	pCharacterInfo[a].CharaInfo.magic_experience = 9999;
	critemAddItem(256,10);
	critemAddItem(171,99);
	critemAddItem(140,8);
	critemAddItem(92,5);
	critemAddItem(2,1);
	critemAddItem(10,3);
*/
	//---ファイアーボール
	pCharacterInfo[a].CharaInfo.MagicTable[0] = 41;

	//---------------------------------
	a = 1;
	memset(&pCharacterInfo[a].CharaInfo,0,sizeof(pCharacterInfo[a].CharaInfo));
	sprintf(pCharacterInfo[a].CharaInfo.Name,"ディザ");
	pCharacterInfo[a].SetWho(a + 1);
	pCharacterInfo[a].SetBattleFieldStartPos(6,3);
	pCharacterInfo[a].CharaInfo.level = 1;
	pCharacterInfo[a].CharaInfo.magic_experience = 0;
	pCharacterInfo[a].CharaInfo.sub_hit_prob = 10;

	//---------------------------------
	a = 2;
	memset(&pCharacterInfo[a].CharaInfo,0,sizeof(pCharacterInfo[a].CharaInfo));
	sprintf(pCharacterInfo[a].CharaInfo.Name,"ナック");
	pCharacterInfo[a].SetWho(a + 1);
	pCharacterInfo[a].CharaInfo.level = 1;
	pCharacterInfo[a].CharaInfo.magic_experience = 0;
	pCharacterInfo[a].CharaInfo.sub_hit_prob = 250;

	//---------------------------------
	a = 3;
	memset(&pCharacterInfo[a].CharaInfo,0,sizeof(pCharacterInfo[a].CharaInfo));
	sprintf(pCharacterInfo[a].CharaInfo.Name,"サヴィアー");
	pCharacterInfo[a].SetWho(a + 1);
	pCharacterInfo[a].CharaInfo.level = 1;
	pCharacterInfo[a].CharaInfo.magic_experience = 0;
	pCharacterInfo[a].CharaInfo.sub_hit_prob = 900;

	//---------------------------------
	a = 4;
	memset(&pCharacterInfo[a].CharaInfo,0,sizeof(pCharacterInfo[a].CharaInfo));
	sprintf(pCharacterInfo[a].CharaInfo.Name,"ユミ");
	pCharacterInfo[a].SetWho(a + 1);
	pCharacterInfo[a].CharaInfo.level = 1;
	pCharacterInfo[a].CharaInfo.magic_experience = 0;
	pCharacterInfo[a].CharaInfo.sub_hit_prob = 700;

	//---------------------------------
	a = 5;
	memset(&pCharacterInfo[a].CharaInfo,0,sizeof(pCharacterInfo[a].CharaInfo));
	sprintf(pCharacterInfo[a].CharaInfo.Name,"ライゼル");
	pCharacterInfo[a].SetWho(a + 1);
	pCharacterInfo[a].CharaInfo.level = 1;
	pCharacterInfo[a].CharaInfo.magic_experience = 0;
	pCharacterInfo[a].CharaInfo.sub_hit_prob = 50;

	//---------------------------------
	a = 6;
	memset(&pCharacterInfo[a].CharaInfo,0,sizeof(pCharacterInfo[a].CharaInfo));
	sprintf(pCharacterInfo[a].CharaInfo.Name,"シンディ");
	pCharacterInfo[a].SetWho(a + 1);
	pCharacterInfo[a].CharaInfo.level = 1;
	pCharacterInfo[a].CharaInfo.magic_experience = 0;
	pCharacterInfo[a].CharaInfo.sub_hit_prob = 150;

	//---------------------------------
	a = 13;//---ルナン過去
	memset(&pCharacterInfo[a].CharaInfo,0,sizeof(pCharacterInfo[a].CharaInfo));
	sprintf(pCharacterInfo[a].CharaInfo.Name,"ルナン");
	pCharacterInfo[a].SetWho(a + 1);
	pCharacterInfo[a].CharaInfo.level = 1;
	pCharacterInfo[a].CharaInfo.magic_experience = 0;
	pCharacterInfo[a].CharaInfo.sub_hit_prob = 333;

	//---------------------------------
	a = 14;
	memset(&pCharacterInfo[a].CharaInfo,0,sizeof(pCharacterInfo[a].CharaInfo));
	sprintf(pCharacterInfo[a].CharaInfo.Name,"ガゼール");
	pCharacterInfo[a].SetWho(a + 1);
	pCharacterInfo[a].SetMaxLP(592);
	pCharacterInfo[a].SetLP(592);
	pCharacterInfo[a].SetMaxMC(112);
	pCharacterInfo[a].SetMC(112);
	pCharacterInfo[a].SetWeapon(0,13);
	pCharacterInfo[a].SetProtector(0,91);
	pCharacterInfo[a].SetBattleFieldStartPos(5,5);
	pCharacterInfo[a].CharaInfo.level = 32;
	pCharacterInfo[a].CharaInfo.power = 250;
	pCharacterInfo[a].CharaInfo.vitality = 125;
	pCharacterInfo[a].CharaInfo.agility = 99;
	pCharacterInfo[a].CharaInfo.soul = 98;
	pCharacterInfo[a].CharaInfo.magic = 76;

	pCharacterInfo[a].CharaInfo.magic_experience = 0;
	pCharacterInfo[a].CharaInfo.sub_hit_prob = 100;
	//---------------------------------
	a = 15;
	memset(&pCharacterInfo[a].CharaInfo,0,sizeof(pCharacterInfo[a].CharaInfo));
	sprintf(pCharacterInfo[a].CharaInfo.Name,"フォールン");
	pCharacterInfo[a].SetWho(a + 1);
	pCharacterInfo[a].SetMaxLP(323);
	pCharacterInfo[a].SetLP(323);
	pCharacterInfo[a].SetMaxMC(176);
	pCharacterInfo[a].SetMC(176);
	pCharacterInfo[a].SetWeapon(0,1);
	pCharacterInfo[a].SetProtector(0,91);
	pCharacterInfo[a].SetBattleFieldStartPos(6,3);
	pCharacterInfo[a].CharaInfo.level = 28;
	pCharacterInfo[a].CharaInfo.power = 120;
	pCharacterInfo[a].CharaInfo.vitality = 130;
	pCharacterInfo[a].CharaInfo.agility = 198;
	pCharacterInfo[a].CharaInfo.soul = 120;
	pCharacterInfo[a].CharaInfo.magic = 66;

	pCharacterInfo[a].CharaInfo.magic_experience = 0;
	pCharacterInfo[a].CharaInfo.sub_hit_prob = 500;
	pCharacterInfo[a].CharaInfo.MagicTable[0] = 31;
}

//---ゲームを始める
CREVENT_API void creventStartGame(int mode)
{
	int a;

	//---ゲームで使う変数初期化
	memset(pGameInfo,0,sizeof(CRESTEAJU_GAMEINFO));
	memset(pPartyInfo,0,sizeof(CRESTEAJU_PARTYINFO));

	//---システム情報初期化
	crdataInitData();
	crsysSetSystemInfo();
	pGameInfo->TransWindow = 0;
	creventInitCharaInfo();

	//---オープニング
	creventOpening();

	//---マップロード
	crfieldChangeMap(11,0,1,0);
	crfieldChangePos(15,15,1);
	//---主人公設定
	crfieldSetMainCharacter(1);

	//---フィールドモードの設定
	ei->Get();
	ef->Field.Zoom = 100;
	ef->SetMoveEnything(0);

	//---壁紙設定
	pGameInfo->UseWallPaper = 1;
	pGameInfo->WallPaper[0] = 1;
	pGameInfo->WallPaper[1] = 1;

	//---パーティー設定
	for(a = 0;a < MEMBER_MAX;a ++){
		pPartyInfo->PartyMember[a] = -1;
	}
	pPartyInfo->PartyMember[0] = 0;

	//---ウィンドウ状態
	pGameInfo->TransWindow = 0;

	//---フェードアウト
	crmusicFadeOut(1);
	crefectScreenChange_FadeOut(NULL,-1,2000);
	et->Delay2(2000);
	//---音楽リセット
	crmusicPlay(CRMUSIC_INIT);

	crsoundPlay(CRSOUND_GS_SOUND,1);
	et->Delay2(5000);
	crsoundStop(CRSOUND_GS_SOUND);
	et->Delay2(1000);

	//---最後にデータをまとめてセット
	crbaseSetAllData(0);
//	creventOpening();
/*
	pCharacterInfo[0].SetMaxLP(9999);
	pCharacterInfo[0].SetLP(9999);
	pCharacterInfo[0].SetMaxMC(9999);
	pCharacterInfo[0].SetMC(9999);
	pCharacterInfo[0].CharaInfo.magic_experience = 9999;
	pCharacterInfo[0].CharaInfo.MagicTable[0] = 1;
	pCharacterInfo[1].CharaInfo.MagicTable[0] = 2;
*/
/*	for(a = 0;a < 80;a ++){
		pCharacterInfo[0].CharaInfo.MagicTable[a] = a;
	}*/
/*	pCharacterInfo[0].CharaInfo.MagicTable[1] = 42;
	pCharacterInfo[0].CharaInfo.MagicTable[2] = 43;
	pCharacterInfo[0].CharaInfo.MagicTable[3] = 44;
	pCharacterInfo[0].CharaInfo.MagicTable[4] = 45;*/
}
