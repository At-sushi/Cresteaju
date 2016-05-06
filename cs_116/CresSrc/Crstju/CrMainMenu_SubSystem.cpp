#define CONFIGMESWIN_CREATE(y) mes.Create(256,y,20,9)

extern CRESTEAJU_VERSION CresteajuVersion;

int crmainSystem_VersionInfo(void)
{
	CrMessageWindow mes;
	eistr s[80];
	eistr laststr[8] = {' ','a','b','c','d','e'};

	crmainClearMenu();
	crbaseMenuReset();
	mes.Create(32,32,32,12);

	mes.SetColor(CRCOLOR_GREEN);
	mes.DrawText("Cresteaju");
	mes.AddReturn();
	mes.SetColor(CRCOLOR_WHITE);
	mes.DrawText("   Version ");
	sprintf(s,"%d.%02d%c",CresteajuVersion.Major,CresteajuVersion.Minor,
		laststr[CresteajuVersion.LastString]);
	mes.DrawText(s);
	mes.AddReturn();
	mes.DrawText("   Copyright(C) 2001 Shou/Shogo Kawai All rights reserved.");
	mes.AddReturn();
	mes.AddReturn();

	//---動作情報
/*	mes.SetColor(CRCOLOR_YELLOW);
	mes.DrawText("   DirectDraw :");
	mes.SetColor(CRCOLOR_WHITE);
	if(eiIsDirectDrawHAL())
		mes.DrawText("HAL");
	else
		mes.DrawText("HEL");
	mes.AddReturn();*/

	mes.SetColor(CRCOLOR_YELLOW);
	mes.DrawText("   Direct3D         : ");
	mes.SetColor(CRCOLOR_WHITE);
	mes.DrawText(eiGetDDInfo()->Direct3DUsingDeviceName);
	mes.AddReturn();

	mes.SetColor(CRCOLOR_YELLOW);
	mes.DrawText("   VideoMemory Total: ");
	mes.SetColor(CRCOLOR_WHITE);
	sprintf(s,"%5d",eiGetDDMaxViedoMemory() / 1024);
	mes.DrawText(s);
	mes.AddReturn();

	mes.SetColor(CRCOLOR_YELLOW);
	mes.DrawText("               Use  : ");
	mes.SetColor(CRCOLOR_WHITE);
	sprintf(s,"%5d",(eiGetDDMaxViedoMemory() - eiGetDDFreeViedoMemory()) / 1024);
	mes.DrawText(s);
	mes.AddReturn();

	mes.SetColor(CRCOLOR_YELLOW);
	mes.DrawText("        RefreshRate : ");
	mes.SetColor(CRCOLOR_WHITE);
	sprintf(s,"%5d",crdataGetIniFile()->RuningRefreshRate);
	mes.DrawText(s);
	mes.AddReturn();

	

	ew->Refresh();

	crbaseMenuStart();

	CrInput ci;
	ci.WaitAnykey();

	return 1;
}


int crmainConfig_SetDrawRate(void)
{
	int ret;
	CrMessageWindow mes;
	CrDigitWindow win;

	crbaseMenuReset();
	win.Create(256,48,12,4,"",4);
	CONFIGMESWIN_CREATE(120);
	win.Refresh();
	mes.Message("リフレッシュレートに対する画面更新割合です。\\n;"
		"100がリフレッシュレートに合わせて更新、200で２回に１回の更新になります。");
	mes.Draw(-1,0,0);
	mes.Refresh();

	crbaseMenuStart();
	win.SetRange(100,800);
	ret = win.GetDigit(crdataGetSystem()->DrawRate,2);
	crdataGetSystem()->DrawRate = ret;

	ef->SetDrawRate(crdataGetSystem()->DrawRate);

	return 0;
}

int crmainConfig_SetAutoChangeFPS(void)
{
	int ret;
	CrMessageWindow mes;
	CrSelectWindow win;
	CRWIN_SELECTINFO info;

	memset(&info,0,sizeof(info));
	info.Offset = 1 - crdataGetSystem()->AutoDrawFrame;

	crbaseMenuReset();
	win.Create(256,48,12,5,""," ＯＮ ;ＯＦＦ;");
	mes.Create(256,136,20,9);
	win.Refresh();
	mes.Message("画面描画を自動的に調節する機能です。\\n;"
		"”フィールド更新頻度 ”が大きい値の時はＯＦＦにした方がきれいになります。");
	mes.Draw(-1,0,0);
	mes.Refresh();

	crbaseMenuStart();
	ret = win.Select(&info);
	if(ret != -1){
		crdataGetSystem()->AutoDrawFrame = 1 - ret;
		if(1 - ret == 0){
			ef->SetDrawMode(EF_DRAW_MANUAL);
		} else {
			ef->SetDrawMode(EF_DRAW_AUTOCHANGE);
		}
	}

	return 0;
}

int crmainConfig_SetKeyWaitAfterPush(void)
{
	int ret;
	CrMessageWindow mes;
	CrDigitWindow win;

	crbaseMenuReset();
	win.Create(256,144,12,4,"",4);
	CONFIGMESWIN_CREATE(216);
	win.Refresh();
	mes.Message("最初にキーが押されてどのくらい経ってからキーリピートを開始するかの設定です。\\n;"
		"単位はミリ秒です。");
	mes.Draw(-1,0,0);
	mes.Refresh();

	crbaseMenuStart();
	win.SetRange(50,2000);
	ret = win.GetDigit(crdataGetSystem()->KeyWaitAfterPush,2);
	crdataGetSystem()->KeyWaitAfterPush = ret;

	return 0;
}

int crmainConfig_SetKeyWaitDelay(void)
{
	int ret;
	CrMessageWindow mes;
	CrDigitWindow win;

	crbaseMenuReset();
	win.Create(256,144,12,4,"",4);
	CONFIGMESWIN_CREATE(216);
	win.Refresh();
	mes.Message("キーリピートの間隔です。\\n;"
		"単位はミリ秒です。");
	mes.Draw(-1,0,0);
	mes.Refresh();

	crbaseMenuStart();
	win.SetRange(100,2000);
	ret = win.GetDigit(crdataGetSystem()->KeyWaitDelay,2);
	crdataGetSystem()->KeyWaitDelay = ret;

	return 0;
}

int crmainConfig_SetMenuWait(void)
{
	int ret;
	CrMessageWindow mes;
	CrDigitWindow win;

	crbaseMenuReset();
	et->Reset();
	win.Create(256,144,12,4,"",4);
	CONFIGMESWIN_CREATE(216);
	win.Refresh();
	mes.Message("メニュー切り換え時の待ち時間です。"
		"間隔が短いとウィンドウの切り替えがスムーズになりますが、キー反応が早くなりすぎて次のメニューも選択してしまうことがあります。\\n;"
		"単位はミリ秒です。");
	mes.Draw(-1,0,0);
	mes.Refresh();

	et->Wait2(350);
//	crbaseMenuStart();
	win.SetRange(50,2000);
	ret = win.GetDigit(crdataGetSystem()->MenuWaitTime,2);
	crdataGetSystem()->MenuWaitTime = ret;

	return 0;
}

int crmainConfig_SetBattleAngle(void)
{
	int ret;
	CrMessageWindow mes;
	CrSelectWindow win;
	CRWIN_SELECTINFO info;

	crbaseMenuReset();
	win.Create(256,212,12,8,"","サイドビュー１;味方視点;サイドビュー２;敵視点;");
	mes.Create(256,128,20,5);
	win.Refresh();
	mes.Message("戦闘での視点です");
	mes.Draw(-1,0,0);
	mes.Refresh();

	crbaseMenuStart();
	memset(&info,0,sizeof(info));
	info.Offset = crdataGetSystem()->BattleCameraAngle;
	ret = win.Select(&info);
	if(ret != -1){
		crdataGetSystem()->BattleCameraAngle = ret;
	}

	return 0;
}

int crmainConfig_SetBattleCameraMoving(void)
{
	int ret;
	CrMessageWindow mes;
	CrSelectWindow win;
	CRWIN_SELECTINFO info;

	crbaseMenuReset();
	win.Create(256,212,12,6,"","切り替える;スムーズに移動;");
	mes.Create(256,128,20,5);
	win.Refresh();
	mes.Message("戦闘時のカメラ移動を滑らかにするか、切り替えにするかの設定です。\\n;");
	mes.Draw(-1,0,0);
	mes.Refresh();

	crbaseMenuStart();
	memset(&info,0,sizeof(info));
	info.Offset = crdataGetSystem()->BattleMoveCamera;
	ret = win.Select(&info);
	if(ret != -1){
		crdataGetSystem()->BattleMoveCamera = ret;
	}

	return 0;
}

int crmainConfig_SetBattleCommandReset(void)
{
	int ret;
	CrMessageWindow mes;
	CrSelectWindow win;
	CRWIN_SELECTINFO info;

	crbaseMenuReset();
	win.Create(256,212,16,7,"","ターンごとにリセットする;バトルごとにリセットする;リセットしない;");
	mes.Create(256,128,20,5);
	win.Refresh();
	mes.Message("戦闘時のコマンドを保存するか、いつリセットするかの設定です\\n;");
	mes.Draw(-1,0,0);
	mes.Refresh();

	crbaseMenuStart();
	memset(&info,0,sizeof(info));
	info.Offset = crdataGetSystem()->BattleCommandReset;
	ret = win.Select(&info);
	if(ret != -1){
		crdataGetSystem()->BattleCommandReset = ret;
	}

	return 0;
}

//---コンフィグ
int crmainMenuSystemConfig(void)
{
	int ret;
	CrSelectWindow win;
	eistr string[512];
	static CRWIN_SELECTINFO info;
	//---メニュー関数テーブル
	int (*MenuTable[])(void) = {
		NULL,
		NULL,
		crmainConfig_SetDrawRate,crmainConfig_SetAutoChangeFPS,
		NULL,
		crmainConfig_SetKeyWaitAfterPush,crmainConfig_SetKeyWaitDelay,
		crmainConfig_SetMenuWait,
		NULL,
		crmainConfig_SetBattleAngle,crmainConfig_SetBattleCameraMoving,
		crmainConfig_SetBattleCommandReset,
		NULL,
		NULL,NULL
	};

	eistr *battlecamera[] = {
		"サイドビュー１","味方視点","サイドビュー２","敵視点"
	};

	do {
		crmainClearMenu();
		crbaseMenuReset();
		sprintf(string,
			"全ての設定を標準に戻す;"
			"\\4フィールド設定...;\\7"
			"    フィールド更新頻度        : \\6%d\\7;"
			"    フィールド描画の自動変更  : \\6%s\\7;"
			"\\4キーボード設定...\\7;"
			"    キーボードリピート開始時間    : \\6%d\\7ミリ秒;"
			"    キーボードリピート間隔        :\\6%d\\7ミリ秒;"
			"    メニュー切り換え時の待ち時間  :\\6%d\\7ミリ秒;"
			"\\4戦闘設定...\\7;"
			"    バトル視点      :  \\6%s\\7;"
			"    カメラ移動      :  \\6%s\\7;"
			"    バトルコマンド  :  \\6%s\\7;"
			,crdataGetSystem()->DrawRate,
			crdataGetSystem()->AutoDrawFrame ? "ON" : "OFF",
			crdataGetSystem()->KeyWaitAfterPush,
			crdataGetSystem()->KeyWaitDelay,
			crdataGetSystem()->MenuWaitTime,
			battlecamera[crdataGetSystem()->BattleCameraAngle],
			crdataGetSystem()->BattleMoveCamera ? "スムーズ" : "切り替え",
			crdataGetSystem()->BattleCommandReset == 0 ? "ターンごとにリセット" : 
		(crdataGetSystem()->BattleCommandReset == 1 ? "戦闘ごとにリセット" : "リセットしない")
			);
		win.Create(32,32,28,17,"コンフィグ",string);
//		win.Refresh();
		ew->Refresh();

		crbaseMenuStart();
		ret = win.Select(&info);
		if(ret != -1){
			if(ret == 0){
				//---ディフォルト！！
				crdataInitData();
			} else if(MenuTable[ret] != NULL){
				(*MenuTable[ret])();
			}
		}

	} while(ret != -1);

	return MAINLOOP_NOMESSAGE;
}

//---システム
int crmainMenuSystem(void)
{
	int ret;
	CrSelectWindow win;
	static CRWIN_SELECTINFO info;

	memset(&info,0,sizeof(info));

	do {
		crmainClearMenu();
		crbaseMenuReset();
		if(evGet(260) == 0){
			//---クリア前
			win.Create(32,32,10,9,"システムメニュー","コンフィグ; セ ー ブ ; ロ ー ド ;バージョン;ゲーム終了;",
				1,12);
		} else {
			win.Create(32,32,10,10,"システムメニュー","コンフィグ; セ ー ブ ; ロ ー ド ;バージョン; デ ー タ ;ゲーム終了;",
				1,12);
		}
		ew->Refresh();

		crbaseMenuStart();
		ret = win.Select(&info);

		if(ret == 0){
			crmainMenuSystemConfig();
		} else if(ret == 1){
			crmainMenuSave();
		} else if(ret == 2){
			if(crmainMenuLoad() == MAINLOOP_RELOADMENU)
				return MAINLOOP_RELOADMENU;
		} else if(ret == 3){
			crmainSystem_VersionInfo();
		} else if(ret == 4 && evGet(260) == 1){
			crmainMainMenu_HiddenInfo();
		} else if(ret == 4 + (evGet(260) == 1 ? 1 : 0)){
			//---終了
			CrSelectWindow win2;

			crbaseMenuReset();
			win2.Create(48,48,14,5,"本当に終了しますか？","やっぱり続ける;終わる;");
			win2.Refresh();
			crbaseMenuStart();
			if(win2.Select(&info) == 1){
				return MAINLOOP_ENDLOOP;
			}
		}

	} while(ret != -1);

	return MAINLOOP_NOMESSAGE;
}
