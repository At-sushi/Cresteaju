CRBATCPU_API int crbatCPUThink7(CrBattleCharacter *pChara,int turn,int rnd)
{
	if(pChara->BattleInfo.Enemy.ActionType == 192){
		//---ブラッドソード
		if(rnd < 280){
			//---斬りかかる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 400){
			//---激しく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else if(rnd < 800){
			//---吸血
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KYUKETSU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 193){
		//---グラスバナナ
		if(rnd < 180){
			//---オーロラテイル
			crbatCPUThink_SetMagicAtack(pChara,23);
		} else if(rnd < 360){
			//---オーロラテイル（全）
			crbatCPUThink_SetMagicAtack(pChara,23,-1,0,NULL,1);
		} else if(rnd < 400){
			//---リカバレイション
			crbatCPUThink_SetMagicAtack(pChara,6);
		} else if(rnd < 500){
			//---ライフウィンド
			crbatCPUThink_SetMagicAtack(pChara,7);
		} else if(rnd < 600){
			//---エクステンド
			crbatCPUThink_SetMagicAtack(pChara,22);
		} else if(rnd < 800){
			//---プロテクション
			crbatCPUThink_SetMagicAtack(pChara,13);
		} else {
			//---インフルエンス
			crbatCPUThink_SetMagicAtack(pChara,20,-1,0,NULL,1);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 194){
		//---エージェント
		if(rnd < 280 && !pChara->GetTurnAtack()){
			//---パワーボム
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_POWERBOMB,200);
		} else if(rnd < 400){
			//---火炎放射
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAENHOUSHA,100);
		} else if(rnd < 550){
			//---スリープブレス
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,30);
		} else if(rnd < 700){
			//---サイレントブレス
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SILENTBREATH,50);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 195){
		//---ゴーレムウィザート
		if(rnd < 250 && !pChara->GetTurnAtack()){
			//---タイダルウェイヴ
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,51);
		} else if(rnd < 300){
			//---アクアソード
			crbatCPUThink_SetMagicAtack(pChara,50);
		} else if(rnd < 450){
			//---ベータスコール
			crbatCPUThink_SetMagicAtack(pChara,68);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 196){
		//---ディメイション
		if(pChara->GetLP() < 50 && rnd < 500){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_LPCHANGE,1000);
		} else if(rnd < 333){
			//---リザーブ
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_RESERVE);
		} else if(rnd < 460){
			//---反物質
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HANBUSSHITU);
		} else if(rnd < 600){
			//---ディバイディング
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_DIVIDING);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 197){
		//---アースドラゴン
		if(rnd < 250 && !pChara->GetTurnAtack()
			&& !pChara->GetPersonalTurn()){
			//---アースクウェイク
			pChara->AddTurnAtack();
			pChara->AddPersonalTurn(2);
			crbatCPUThink_SetMagicAtack(pChara,63);
		} else if(rnd < 333){
			//---砂嵐
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SUNAARASHI,130);
		} else if(rnd < 600){
			//---噛みつく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 198){
		//---フィルガルツナイト
		if(rnd < 170){
			//---斬りかかる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 320){
			//---激しく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else if(rnd < 470){
			//---なぎ倒す
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGITAOSU);
		} else if(rnd < 720){
			//---コンフュージョン
			crbatCPUThink_SetMagicAtack(pChara,18);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 199){
		//---時の亡霊
		if(rnd < 250 && !pChara->GetPersonalTurn()){
			//---デスフォース
			pChara->AddPersonalTurn(3);
			crbatCPUThink_SetMagicAtack(pChara,21);
		} else if(rnd < 500 && crbatCPUGetEnemy() > 1){
			//---のりうつる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NORIUTURU2);
		} else if(rnd < 700){
			//---ＭＣ分解
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_MCBUNKAI,50);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 200){
		//---レイム・ソウル
		if(pChara->GetBtStatus() & BTST_CHINMOKU){
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 200 && !pChara->GetTurnAtack()){
			//---ライジングサン
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,45);
		} else if(rnd < 250){
			//---エクスプロージョン
			crbatCPUThink_SetMagicAtack(pChara,44);
		} else if(rnd < 450 && !pChara->GetTurnAtack()){
			//---タイダルウェイヴ
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,51);
		} else if(rnd < 500){
			//---アクアソード
			crbatCPUThink_SetMagicAtack(pChara,50);
		} else if(rnd < 700){
			//---テラジャッジメント
			crbatCPUThink_SetMagicAtack(pChara,69);
		} else if(rnd < 750){
			//---ベータスコール
			crbatCPUThink_SetMagicAtack(pChara,68);
		} else if(rnd < 850 && !pChara->GetBattleFlag(0)){
			//---リカバレイション
			pChara->SetBattleFlag(0,1);
			crbatCPUThink_SetMagicAtack(pChara,6);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 201){
		//---アシウス
		if(rnd < 250 && !pChara->GetBattleFlag(0) && pChara->GetLP() > 400){
			//---パワーブースト（自分）
			pChara->SetBattleFlag(0,1);
			crbatCPUThink_SetMagicAtack(pChara,19,BAT_TARGET_ME,0,pChara);
			pChara->Command.Target = (ei_u32)pChara;
		} else if(rnd < 400){
			//---殴る
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGURU);
		} else if(rnd < 650){
			//---突進
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOSSHIN);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 202){
		//---ドラゴンロード
		if(rnd < 250 && !pChara->GetTurnAtack()
			&& !pChara->GetPersonalTurn()){
			//---大火炎
			pChara->AddTurnAtack();
			pChara->AddPersonalTurn(3);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO2,250);
		} else if(rnd < 400){
			//---炎
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,140);
		} else if(rnd < 600){
			//---かみつく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 203){
		//---埴輪貴族
		if(rnd < 250 && pChara->GetTurnAtack() <= 0
			&& !pChara->GetPersonalTurn()){
			//---埴輪楼桜剣
			pChara->AddTurnAtack();
			pChara->AddPersonalTurn(2);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_ROUOU);
		} else if(rnd < 350){
			//---音速斬り
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_ONSOKU);
		} else if(rnd < 500){
			//---斬りかかる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 700 && pChara->GetLP() < 200 && !pChara->GetBattleFlag(0)){
			//---再生
			pChara->SetBattleFlag(0,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SAISEI);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 213){
		//---バナナミュータント
		if(rnd < 250){
			//---ライジングサン
			pChara->SetBattleFlag(0,0);
			crbatCPUThink_SetMagicAtack(pChara,45);
		} else if(rnd < 500){
			//---テラジャッジメント
			pChara->SetBattleFlag(0,0);
			crbatCPUThink_SetMagicAtack(pChara,69);
		} else if(rnd < 750 + pChara->GetBattleFlag(0) * 250){
			//---スーパーセル
			pChara->SetBattleFlag(0,0);
			crbatCPUThink_SetMagicAtack(pChara,57);
		} else if(rnd < 950 && pChara->GetLP() > 600){
			//---カオスワード
			pChara->SetBattleFlag(0,1);
			crbatCPUThink_SetMagicAtack(pChara,27);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	//---------------------------------------------------
	} else if(pChara->BattleInfo.Enemy.ActionType == 217){
		//---カー
		if(rnd < 250 && pChara->GetTurnAtack() == 0
			&& !pChara->GetPersonalTurn()){
			//---炎
			pChara->AddTurnAtack();
			pChara->AddPersonalTurn(3);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,240);
		} else if(rnd < 300){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,120);
		} else if(rnd < 350){
			//---食べる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TABERU);
		} else if(rnd < 600){
			//---かみつく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else if(rnd < 700 && crbatCPUGetEnemy() > 1){
			//---寝る
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NERU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 218){
		//---クダー
		if(turn == 0){
			crbatCPUThink_SetMagicAtack(pChara,19,-1,0,&pBtChara[BATTLECHARA_STARTENEMY]);
		} else if(turn == 1){
			crbatCPUThink_SetMagicAtack(pChara,19,-1,0,&pBtChara[BATTLECHARA_STARTENEMY + 1]);
		} else if(rnd < 250 && pChara->GetTurnAtack() == 0
			&& !pChara->GetPersonalTurn()){
			//---吹雪
			pChara->AddTurnAtack();
			pChara->AddPersonalTurn(3);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_FUBUKI,200);
		} else if(rnd < 300){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGITAOSU);
		} else if(crbatCPUGetEnemy() > 1){
			if(rnd < 400){
				//---スリーピング
				crbatCPUThink_SetMagicAtack(pChara,11);
			} else if(rnd < 500){
				//---ダークミスト
				crbatCPUThink_SetMagicAtack(pChara,14);
			} else if(rnd < 600){
				//---サイレンス
				crbatCPUThink_SetMagicAtack(pChara,15);
			} else if(rnd < 700){
				//---コンフュージョン
				crbatCPUThink_SetMagicAtack(pChara,18);
			} else if(rnd < 800){
				//---パワーブースト
				crbatCPUThink_SetMagicAtack(pChara,19);
			} else if(rnd < 900){
				//---エクステンド
				crbatCPUThink_SetMagicAtack(pChara,22);
			} else {
				//---通常攻撃
				crbatCPUThink_SetAtack(pChara);
			}
		} else if(rnd < 350){
			//---プロテクション
			crbatCPUThink_SetMagicAtack(pChara,13);
		} else if(rnd < 450){
			//---フォースシールド
			crbatCPUThink_SetMagicAtack(pChara,17);
		} else if(rnd < 650){
			//---パワーブースト
			crbatCPUThink_SetMagicAtack(pChara,19);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 219){
		//---ドラゴンソウル
		if((pChara->GetBtStatus() & BTST_MAHI)){
			if(rnd < 250){
				//---ライジングサン
				crbatCPUThink_SetMagicAtack(pChara,45);
			} else if(rnd < 500){
				//---タイダルウェイヴ
				crbatCPUThink_SetMagicAtack(pChara,51);
			} else if(rnd < 750){
				//---スーパーセル
				crbatCPUThink_SetMagicAtack(pChara,57);
			} else {
				//---アースクウェイク
				crbatCPUThink_SetMagicAtack(pChara,63);
			}
		} else if(pChara->GetBattleFlag(0) == 1){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_DAIKAEN,5000);
		} else if(turn % 5 == 0 && turn != 0){
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_IKIWOSUIKOMU);
		} else if(rnd < 400 && pChara->GetPersonalTurn() == 0){
			//---ブレス
			pChara->AddPersonalTurn(2);
			int rnd2 = eiRnd(1000);
			if(rnd < 250){
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO2,275);
			} else if(rnd < 500){
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_FUBUKI2,275);
			} else if(rnd < 750){
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOPPU2,275);
			} else {
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_SUNAARASHI2,275);
			}
		} else if(rnd < 250){
			//---噛みつく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else if(rnd < 400){
			//---なぎ倒す
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGITAOSU);
		} else if(rnd < 500){
			//---ブレスリープブレス
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,100);
		} else if(rnd < 600){
			//---サイレントブレス
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SILENTBREATH,100);
		} else if(rnd < 700){
			//---衝撃波
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SHOGEKIHA);
		} else if(rnd < 900){
			//---超音波
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CHOUONPA);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 220){
		//---バリアー２０００
		if(rnd < 250){
			//---スリープブレス
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,10);
		} else if(rnd < 500){
			//---サイレントブレス
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SILENTBREATH,10);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}

		//---カオスワード使ってるのを探して攻撃
		int a;
		for(a = 0;a < 4;a ++){
			if(pBtChara[a].DoExist()){
				if(pBtChara[a].GetKaosTurn() > 0){
					pChara->Command.Target = (ei_u32)&pBtChara[a];
					break;
				}
			}
		}
	//---------------------------------------------------
	} else if(pChara->BattleInfo.Enemy.ActionType == 223){
		//---クレイシヴ
		if(turn == 0){
			pChara->Command.Main = BAT_COMMAND_WAIT;
			pChara->Command.Sub[0] = 0;
		} else if(turn == 1){
			//---スーパーセル
			pChara->AddPersonalTurn(3);
			pChara->SetBattleFlag(0,0);
			crbatCPUThink_SetMagicAtack(pChara,57);
			pChara->Command.Target = (ei_u32)&pBtChara[0];
			pChara->EnableFirstAtack(1);
		} else if(pChara->GetBattleFlag(0) == 1){
			//---倒れてる
			pChara->SetBattleFlag(1,pChara->GetBattleFlag(1) - 1);
			if(pChara->GetBattleFlag(1) == 1){
				//---変身
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_HENSHIN);
			} else {
				pChara->Command.Main = BAT_COMMAND_WAIT;
			}
		} else if(rnd < 300 && pChara->GetPersonalTurn() == 0){
			//---スーパーセル
			pChara->AddPersonalTurn(3);
			crbatCPUThink_SetMagicAtack(pChara,57);
		} else if(rnd < 500 && pChara->GetPersonalTurn() == 0){
			//---タイダルウェイヴ
			pChara->AddPersonalTurn(3);
			crbatCPUThink_SetMagicAtack(pChara,51);

		} else if(rnd < 100){
			//---スリーピング
			crbatCPUThink_SetMagicAtack(pChara,11,-1,0,NULL,1);
		} else if(rnd < 200){
			//---コンフュージョン
			crbatCPUThink_SetMagicAtack(pChara,18,-1,0,NULL,1);
		} else if(rnd < 300){
			//---インフルエンス
			crbatCPUThink_SetMagicAtack(pChara,20,-1,0,NULL,1);
		} else if(rnd < 400){
			//---ベータスコール
			crbatCPUThink_SetMagicAtack(pChara,68);
		} else if(rnd < 450){
			//---テラジャッジメント
			crbatCPUThink_SetMagicAtack(pChara,69);
		} else if(rnd < 500){
			//---ダイヤブレス
			crbatCPUThink_SetMagicAtack(pChara,62);
		} else if(rnd < 600){
			//---スリーピング
			crbatCPUThink_SetMagicAtack(pChara,11,-1,0,NULL,1);
		} else if(rnd < 700){
			//---コンフュージョン
			crbatCPUThink_SetMagicAtack(pChara,18,-1,0,NULL,1);
		} else if(rnd < 800){
			//---インフルエンス
			crbatCPUThink_SetMagicAtack(pChara,20,-1,0,NULL,1);
		} else if(rnd < 875){
			//---デスフォース
			crbatCPUThink_SetMagicAtack(pChara,21);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 224){
		//---クレイシヴ・変身後
		static int prev[2] = {0,0};
		int loop = 0;
		ei_s32 keep[BATLLECHARA_FLAG_MAX];

		memcpy(keep,pChara->OnlyInfo.Flags,sizeof(keep));
	do {
		CrBattleCharacter *pnear = crbatCPU_PlayerIsSekkin(pChara,1);

		loop ++;

		//---フラグを元に戻す
		memcpy(pChara->OnlyInfo.Flags,keep,sizeof(pChara->OnlyInfo.Flags));
		pChara->Command.Sub[0] = 0;

		if(pChara->GetBattleFlag(6) > 0){
			pChara->SetBattleFlag(6,pChara->GetBattleFlag(6) - 1);
		}
		//---ルーインカウンター
		if(pChara->GetBattleFlag(8) > 0){
			pChara->SetBattleFlag(8,pChara->GetBattleFlag(8) - 1);
		}
		//---ＬＰ減ったらカウンター
		if(pChara->GetLP() < 250){
			pChara->SetAbility(BTAB_S_COUNTER75,1);
		} else if(pChara->GetLP() < 1000){
			pChara->SetAbility(BTAB_S_COUNTER50,1);
			pChara->CharaInfo.magic = 148;
		} else if(pChara->GetLP() < 3000){
			pChara->SetAbility(BTAB_S_COUNTER25,1);
		} else if(pChara->GetLP() < 4000){
			pChara->CharaInfo.magic = 143;
		} else if(pChara->GetLP() < 8000){
			pChara->CharaInfo.magic = 138;
		}

		int a,c,st,live_friend;
		for(a = 0,c = 0,live_friend = 0;a < 4;a ++){
			if(pBtChara[a].IsKizetu() == 0)
				live_friend ++;

			st = pBtChara[a].GetBtStatus();
			if(st & BTST_POWER)
				c ++;
			if(st & BTST_EXTEND)
				c ++;
			if(st & BTST_FSHIELD)
				c ++;
			if(st & BTST_SOUL)
				c ++;
		}

		//----------------------------------------------------
		if(pChara->GetBattleFlag(3) == 1){
			//---ルーイン
			pChara->SetBattleFlag(8,2);
			pChara->SetBattleFlag(3,0);
			pChara->SetBattleFlag(12,1);
			pChara->AddPersonalTurn(2 - (pChara->GetLP() < 9000 ? 1 : 0));
			crbatCPUThink_SetMagicAtack(pChara,79);
		//----------------------------------------------------
		//---残り１２００を切ったら
		} else if(pChara->GetLP() <= 1200){
			pChara->SetBattleFlag(13,pChara->GetBattleFlag(13) + 1);
			if((rnd < 450 || pChara->GetBattleFlag(13) >= 2)
				&& (turn % 2) == 0){
				//---インフレーション
				pChara->SetBattleFlag(13,0);
				crbatCPUThink_SetMagicAtack(pChara,80);
			} else if((rnd < 450 || pChara->GetBattleFlag(13) >= 2)
				&& (turn % 2) == 1){
				//---プレートウェイヴ
				pChara->SetBattleFlag(13,0);
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_LINEKOGEKI);
			} else if(rnd < 650){
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_CRFUBUKI,200);
			} else if(rnd < 850){
				//---切り裂く
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_SINGLEKOGEKI);
			} else {
				//---オーロラテイル
				crbatCPUThink_SetMagicAtack(pChara,23,-1,0,NULL,1);
			}
		} else if(pChara->GetBattleFlag(4) == 0){
			//---変身後、最初のターン
			//---インバリディティ
			pChara->SetBattleFlag(4,1);
			crbatCPUThink_SetMagicAtack(pChara,25);
		} else if(pChara->GetBattleFlag(3) == 2){
			//---自分を攻撃
			pChara->SetBattleFlag(3,1);
			crbatCPUThink_SetAtack(pChara);
			pChara->Command.Target = (ei_u32)pChara;
		} else if(pnear != NULL && rnd < 500
			&& pChara->GetBattleFlag(10) <= 16){
			//---移動
			pChara->SetBattleFlag(10,pChara->GetBattleFlag(10) + 1);

//			crbatCPUThink_SetDefense(pChara,3);
			//---ソニックウェイヴ
			int old = pChara->BattleInfo.Enemy.IQ;
			pChara->BattleInfo.Enemy.IQ = 2;
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_TOBASU,800);
			pChara->BattleInfo.Enemy.IQ = old;

		} else if(rnd < 600 && crbatCPU_PlayerIsBaraBara(pChara,3)
			&& pChara->GetBattleFlag(14) <= 3){
			//---ばらばらになったら集める
			pChara->SetBattleFlag(14,pChara->GetBattleFlag(14) + 1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_GRAVITY);
		} else if(rnd < 150 + (pChara->GetBattleFlag(12) == 0 ? 350 : 0)
			&& pChara->GetBattleFlag(3) == 0
			&& pChara->GetBattleFlag(6) == 0
			&& pChara->GetBattleFlag(5) == 1
			&& pChara->GetBattleFlag(8) == 0
			&& pChara->GetLP() >= 6500){
			//---ルーイン準備
			pChara->SetBattleFlag(5,0);
			pChara->SetBattleFlag(6,3);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_RUINJUNBI);
		} else if(1600 < pChara->GetLP() && pChara->GetLP() < 4000 && pChara->GetBattleFlag(11) == 0){
			//---エクステンド
			pChara->SetBattleFlag(11,1);
			crbatCPUThink_SetMagicAtack(pChara,22);
		} else if(rnd < 250
			&& pChara->GetPersonalTurn() == 0 && pChara->GetLP() < 6500
			&& pChara->GetBattleFlag(9) == 0){
			//---プレートウェイヴ
			pChara->AddPersonalTurn(2);
			pChara->SetBattleFlag(9,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_LINEKOGEKI);
		} else if(rnd < 500 && pChara->GetPersonalTurn() == 0){
			//---インフレーション
			pChara->SetBattleFlag(5,1);
			pChara->SetBattleFlag(9,0);
			pChara->AddPersonalTurn(3 - (pChara->GetLP() < 3000 ? 1 : 0));
			crbatCPUThink_SetMagicAtack(pChara,80);
		} else if(rnd < 100){
			//---オーロラテイル
			if(eiRnd(1000) < 500){
				crbatCPUThink_SetMagicAtack(pChara,23);
			} else {
				crbatCPUThink_SetMagicAtack(pChara,23,-1,0,NULL,1);
			}
		} else if(rnd < 200 && live_friend > 2){
			//---吹雪
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CRFUBUKI,200);
		} else if(rnd < 250 && live_friend > 1){
			//---単体攻撃
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_SINGLEKOGEKI);
		} else if(rnd < 200 && pChara->GetLP() < 6000){
			//---単体攻撃
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_SINGLEKOGEKI);
		} else if(rnd < 150){
			//---ベータスコール
			crbatCPUThink_SetMagicAtack(pChara,68);
		} else if(rnd < 220 && live_friend > 2){
			//---スーパーセル
			crbatCPUThink_SetMagicAtack(pChara,57);
		} else if(rnd < 300 && live_friend > 2){
			//---吹雪
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CRFUBUKI,200);
		} else if(rnd < 370){
			if(pChara->GetLP() < 2000){
				//---プレートウェイヴ
				pChara->AddPersonalTurn(2);
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_LINEKOGEKI);
			} else {
				if(pChara->GetLP() < 9000 && eiRnd(1000) < 500 && live_friend > 1){
					//---単体攻撃
					crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_SINGLEKOGEKI);
				} else {
					//---通常攻撃
					crbatCPUThink_SetAtack(pChara);
				}
			}
		} else if(rnd < 530){
			//---吹雪
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CRFUBUKI,200);
		} else if(rnd < 650){// && pChara->GetBattleFlag(7) == 0){
			//---オーロラテイル
			pChara->SetBattleFieldStartPos(7,1);
			if(eiRnd(1000) < 500){
				crbatCPUThink_SetMagicAtack(pChara,23);
			} else {
				crbatCPUThink_SetMagicAtack(pChara,23,-1,0,NULL,1);
			}
/*		} else if(rnd < 650 && pChara->GetBattleFlag(7) == 1){
			//---インフルエンス
			pChara->SetBattleFieldStartPos(7,0);
			crbatCPUThink_SetMagicAtack(pChara,20,-1,0,NULL,1);*/
		} else if(rnd < 730){
			//---攻撃
			if(pChara->GetLP() < 5000 && pChara->GetPersonalTurn() == 0
				&& pChara->GetBattleFlag(9) == 0
				&& live_friend > 2){
				//---プレートウェイヴ
				pChara->AddPersonalTurn(2);
				pChara->SetBattleFlag(9,1);
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_LINEKOGEKI);
			} else {
				if((eiRnd(1000) < 500
					|| pChara->GetLP() < 5000)
					&& live_friend > 2){
					//---単体攻撃
					crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_SINGLEKOGEKI);
				} else {
					//---通常攻撃
					crbatCPUThink_SetAtack(pChara);
				}
//				crbatCPUThink_SetAtack(pChara);
			}
		} else if(rnd < 800
			&& pChara->GetLP() < 4000
			&& live_friend > 2){
			//---プレートウェイヴ
			pChara->AddPersonalTurn(2);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_LINEKOGEKI);
		} else if(rnd < 800 && live_friend > 2){
			//---スーパーセル
			crbatCPUThink_SetMagicAtack(pChara,57);
		} else if(rnd < 800){
			//---ベータスコール
			crbatCPUThink_SetMagicAtack(pChara,68);
		} else {
			if(rnd < 950 && eiRnd(1000) < c * 500){
				//---インバリディティ
				crbatCPUThink_SetMagicAtack(pChara,25);
			} else {
				if(pChara->GetLP() < 5000 && pChara->GetPersonalTurn() == 0
					&& pChara->GetBattleFlag(9) == 0){
					//---プレートウェイヴ
					pChara->AddPersonalTurn(2);
					pChara->SetBattleFlag(9,1);
					crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_LINEKOGEKI);
				} else if(pChara->GetLP() < 9000 && eiRnd(1000) < 500){
					//---単体攻撃
					crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_SINGLEKOGEKI);
				} else if(pChara->GetLP() < 5500 && live_friend > 1){
					//---単体攻撃
					crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_SINGLEKOGEKI);
				} else {
					//---通常攻撃
					crbatCPUThink_SetAtack(pChara);
				}
			}
		}

		CrBattleCharacter *pKaos = NULL;
		for(a = 0;a < 4 && loop <= 1;a ++){
			if(pBtChara[a].DoExist() && !pBtChara[a].IsKizetu()
				 && (pBtChara[a].GetBtStatus() & BTST_KAOS)){
				if(pBtChara[a].GetKaosTurn() >= 3
					&& pChara->GetBattleFlag(3) == 0
					&& pChara->GetBattleFlag(6) == 0
					&& !(pChara->Command.Main == BAT_COMMAND_MAGIC && pChara->Command.Sub[0] != 79)
					&& eiRnd(1000) < 500){
					//---インバリディティ
					crbatCPUThink_SetMagicAtack(pChara,25);
					break;
				}

				if(pBtChara[a].GetKaosTurn() >= 2){
					pKaos = &pBtChara[a];
					break;
				}
			}
		}
		if(pKaos != NULL && pChara->Command.Target != (ei_u32)pChara){
			//---カオスワード２で、ターゲットが自分でなければ、再設定
			pChara->Command.Target = (ei_u32)pKaos;
		}

//		crbatCPUThink_SetAbility(pChara,BAT_ECOM_CR_LINEKOGEKI);
//		crbatCPUThink_SetMagicAtack(pChara,80);
		rnd = eiRnd(1000);
	} while(pChara->Command.Main == prev[0] && pChara->Command.Sub[0] == prev[1]
		&& loop <= 10);

		prev[0] = pChara->Command.Main;
		prev[1] = pChara->Command.Sub[0];
	}
	return crbatCPUThink8(pChara,turn,rnd);
}
