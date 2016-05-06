CRBATCPU_API int crbatCPUThink5(CrBattleCharacter *pChara,int turn,int rnd)
{
	//----------------３部
	if(pChara->BattleInfo.Enemy.ActionType == 142){
		//---へルビースト
		if(rnd < 250 && !pChara->GetTurnAtack()){
			//---吹雪炎
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_FUBUKI,120);
		} else if(rnd < 600){
			//---噛みつく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 143){
		//---テカテカ
		if(rnd < 50 && !pChara->GetTurnAtack()){
			//---ベータスコール
			crbatCPUThink_SetMagicAtack(pChara,68);
		} else if(rnd < 400){
			//---サンダーボルト
			crbatCPUThink_SetMagicAtack(pChara,67);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 144){
		//---夢見草
		if(rnd < 250){
			//---スリーピング
			crbatCPUThink_SetMagicAtack(pChara,11,-1,0,NULL,1);
		} else if(rnd < 500){
			//---花粉
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAFUN,40);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 145){
		//---グラウンドキング
		if(rnd < 500 && pChara->GetBattleFlag(0) == 0
			&& pChara->GetBattleFlag(1) == 0 && pChara->GetLP() >= 400){
			//---流砂
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_RYUSA,10);
			pChara->SetBattleFlag(0,1);
		} else if(pChara->GetBattleFlag(0)){
			//---捕食
			pChara->SetBattleFlag(0,0);
			pChara->SetBattleFlag(1,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HOSHOKU);
		} else if(rnd < 333){
			//---砂嵐
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SUNAARASHI,160);
		} else if(rnd < 680){
			//---かみつく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 146){
		//---デスクラウド
		if(rnd < 200){
			//---パラライズ
			crbatCPUThink_SetMagicAtack(pChara,31);
		} else if(rnd < 400){
			//---スリーピング
			crbatCPUThink_SetMagicAtack(pChara,11);
		} else if(rnd < 600){
			//---ダークミスト
			crbatCPUThink_SetMagicAtack(pChara,14);
		} else if(rnd < 800){
			//---サイレンス
			crbatCPUThink_SetMagicAtack(pChara,15);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 147){
		if(pChara->GetLP() < 80
			&& pChara->GetBattleFlag(0) == 0){
			//---ＬＰチェンジ
			pChara->SetBattleFlag(0,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_LPCHANGE,1000);
		} else if(rnd < 300 && !pChara->GetTurnAtack()){
			//---砂嵐
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SUNAARASHI,100);
		} else if(rnd < 300){
			//---砂嵐
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SUNAARASHI,50);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 148){
		//---ヘルゲート
		if(rnd < 250 && !pChara->GetTurnAtack()){
			//---デスフォース
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,21);
		} else if(rnd < 250){
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 500 && !pChara->GetTurnAtack()){
			//---アクアソード
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,50);
		} else if(rnd < 600){
			//---セルフリーズ
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,49);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 149){
		//---スクラップアーマー
		if(rnd < 250){
			//---斬りかかる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 450){
			//---はげしく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 150){
		//---山の神
		if(pChara->GetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE)
		 && !(pBtChara[
			pChara->GetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE_TAISHO)
			].GetBtStatus() & BTST_ITAMIWAKE)){
			//---痛み分け対象が、痛み分け状態でなくなったら
			pChara->SetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE,0);
			pChara->SetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE_TAISHO,0);
			pChara->SetBattleFlag(1,0);
		}

		if((rnd < 120 || turn == 3)
			&& pChara->GetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE) == 0){
			pChara->SetBattleFlag(1,0);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_ITAMIWAKE);
/*		} else if(pChara->GetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE) == 1
			&& rnd < 600 + (pChara->GetBattleFlag(1) * 200)){
			pChara->SetBattleFlag(1,pChara->GetBattleFlag(1) + 1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_ITAMIWAKE_JIZOKU);
		} else if(pChara->GetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE) == 1){
			pChara->SetBattleFlag(1,0);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_ITAMIWAKE_KAIJO);*/
		} else 

		if(rnd < 220
			&& crbatCPUGetEnemy() == 1
			&& !(pChara->GetBtStatus() & BTST_CHINMOKU)){
			//---デスフォース
			crbatCPUThink_SetMagicAtack(pChara,21);
		} else if(rnd < 250){
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 480 && !pChara->GetPersonalTurn()
			&& !pChara->GetTurnAtack()
			&& !(pChara->GetBtStatus() & BTST_CHINMOKU)){
			//---アースクウェイク
			pChara->AddTurnAtack();
			pChara->AddPersonalTurn(4);
			crbatCPUThink_SetMagicAtack(pChara,63);
		} else if(rnd < 500 && pChara->GetPersonalTurn() <= 2
			&& !(pChara->GetBtStatus() & BTST_CHINMOKU)){
			//---ダイヤブレス
			crbatCPUThink_SetMagicAtack(pChara,62);

		} else if(rnd < 500
			&& (pChara->GetBtStatus() & BTST_CHINMOKU)){
			//---沈黙、激しく斬りつける
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else if(rnd < 630 && pChara->GetPersonalTurn() <= 2
			&& !pChara->GetTurnAtack()){
			//---猛毒の息
			pChara->AddTurnAtack();
			pChara->AddPersonalTurn(2);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_MODOKUNOIKI,100);
		} else if(rnd < 730
			&& !(pChara->GetBtStatus() & BTST_CHINMOKU)){
			//---インバリディティ
			crbatCPUThink_SetMagicAtack(pChara,25);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 151){
		//---レッドダンディ
		if(rnd < 333){
			//---ダンディスパーク
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_DANDYSPARK,102);
		} else if(rnd < 600){
			//---ダンディスプラッシャー
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_DANDYSPRASHER);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 152){
		//---絹玉
		if(rnd < 333){
			//---リカバレイション
			crbatCPUThink_SetMagicAtack(pChara,6);
		} else if(rnd < 500){
			//---スリーピング
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,11,-1,0,NULL,1);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 153){
		//---ウニマリモ
		if(rnd < 600){
			//---回転アタック
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAITENATACK);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 154){
		//---ソードキラー
		if(rnd < 100){
			//---殻
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KARA);
		} else if(rnd < 350){
			//---溶かす
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOKASU);
		} else if(rnd < 600){
			//---食べる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TABERU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 155){
		//---クレイシヴ
		if(turn == 4 || turn == 6){
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else if(turn == 7){
			//---スーパーセル
			pChara->Command.Hit = 1;
			crbatCPUThink_SetMagicAtack(pChara,57);
		} else {
			pChara->Command.Main = BAT_COMMAND_WAIT;
		}

	} else if(pChara->BattleInfo.Enemy.ActionType == 156){
		//---アイチャー
		if(rnd < 200){
			//---ぐるぐる目玉
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_GURUGURUMEDAMA);
		} else if(rnd < 500){
			//---アイビーム
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_EYEBEAM,100);
		} else if(rnd < 600){
			//---コンフュージョン
			crbatCPUThink_SetMagicAtack(pChara,18,-1,0,NULL,1);
		} else if(rnd < 900){
			//---セルフリーズ
			crbatCPUThink_SetMagicAtack(pChara,49);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 157){
		//---ウィングナイト
		if(rnd < 250){
			//---きりかかる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 500){
			//---激しく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 158){
		//---トルネード
		if(rnd < 180 && !pChara->GetTurnAtack() && !pChara->GetPersonalTurn()){
			//---ダウンバースト
			pChara->AddPersonalTurn(3);
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,56);
		} else if(rnd < 360){
			//---突風
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOPPU,60);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 159){
		//---ゾウリムシ
		if(rnd < 300){
			//---とかす
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOKASU);
		} else if(rnd < 500){
			//---窒息
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CHISSOKU_1_2);
		} else if(!pChara->GetBattleFlag(0) && rnd < 550){
			//---分裂
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_BUNRETU);
		} else if(rnd < 700){
			//---酸性雨
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SANSEIU,50);
		} else if(rnd < 800){
			//---再生
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SAISEI);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 160){
		//---キラーボム
		if(pChara->GetBattleFlag(0)){
			//---爆発
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_JIBAKU2,0,pChara);
		} else if(rnd < 600){
			//---移動
			int x,y;
			pChara->SetBattleFlag(0,1);
			crbatCPU_GetPlayerCharaSide(pChara,&x,&y);
			crbatCPUThink_SetDefense(pChara,3,x,y);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 161){
		//---ルビードラゴン
		pChara->SetBattleFlag(0,0);
		pChara->SetBattleFlag(2,0);

		if(pChara->GetBattleFlag(1)
			&& !(pChara->GetBtStatus() & BTST_CHINMOKU)){
			//---カオスワード・魔法
			pChara->SetBattleFlag(1,0);
			pChara->SetBattleFlag(2,1);
			pChara->AddPersonalTurn(4);
			crbatCPUThink_SetMagicAtack(pChara,51);
		} else if(rnd < 220 + (
				(pChara->GetBtStatus() & BTST_CHINMOKU) ? 200 : 0
			)
			&& !pChara->GetPersonalTurn()){
			//---コンボ炎
			pChara->AddPersonalTurn(4);
			pChara->SetBattleFlag(0,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,110);
//			crbatCPUThink_SetMagicAtack(pChara,56);
		} else if(rnd < 330){
			//---炎
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,95);
		} else if(rnd < 680 && !pChara->GetPersonalTurn()
			&& !(pChara->GetBtStatus() & BTST_CHINMOKU)){
			//---カオスワード
			pChara->SetBattleFlag(1,1);
			crbatCPUThink_SetMagicAtack(pChara,27);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}	
	} else if(pChara->BattleInfo.Enemy.ActionType == 184){
		//---ルビードラゴン
		pChara->SetBattleFlag(0,0);

		if(pBtChara[BATTLECHARA_STARTENEMY].GetBattleFlag(1)
			|| pBtChara[BATTLECHARA_STARTENEMY].GetBattleFlag(2)){
			//---カオスワードだったら待機
			pChara->Command.Main = BAT_COMMAND_WAIT;
		} else if(pBtChara[BATTLECHARA_STARTENEMY].GetBattleFlag(0)){
			//---コンボ吹雪
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_FUBUKI,110);
		} else if(rnd < 350
//			&& !(pBtChara[BATTLECHARA_STARTENEMY].Command.Main == BAT_COMMAND_ENEMYABILITY
//				&& pBtChara[BATTLECHARA_STARTENEMY].Command.Sub[0] == BAT_ECOM_HONO)
			&& !pChara->GetTurnAtack()){
			//---吹雪
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_FUBUKI,80);
		} else if(rnd < 480 && !pBtChara[BATTLECHARA_STARTENEMY].GetBattleFlag(1)
			&& !(pChara->GetBtStatus() & BTST_CHINMOKU)){
			int flag  = pChara->GetBattleFlag(1);

			switch(flag){
			case 0:
				//---アクセラレイション
				crbatCPUThink_SetMagicAtack(pChara,16,-1,0,&pBtChara[BATTLECHARA_STARTENEMY]);
				break;
			case 1:
				//---ソウルセンス
				crbatCPUThink_SetMagicAtack(pChara,26,-1,0,&pBtChara[BATTLECHARA_STARTENEMY]);
				break;
			case 2:
				//---フォースシールド
				crbatCPUThink_SetMagicAtack(pChara,17,-1,0,&pBtChara[BATTLECHARA_STARTENEMY]);
				break;
			case 3:
				//---プロテクション
				crbatCPUThink_SetMagicAtack(pChara,13,-1,0,&pBtChara[BATTLECHARA_STARTENEMY]);
				break;
			case 4:
				//---エクステンド
				crbatCPUThink_SetMagicAtack(pChara,22,-1,0,&pBtChara[BATTLECHARA_STARTENEMY]);
				break;
			}
			if(++flag >= 5)
				flag = 0;
			pChara->SetBattleFlag(1,flag);
		} else if(rnd < 750){
			//---ウェイト
			pChara->Command.Main = BAT_COMMAND_WAIT;
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}	
	} else if(pChara->BattleInfo.Enemy.ActionType == 162){
		//---埴輪
		if(rnd < 250 && pChara->GetTurnAtack() <= 1){
			//---音速斬り
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_ONSOKU);
		} else if(rnd < 333){
			//---斬りかかる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 666){
			//---疾走・８２０
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_820);
		} else if(rnd < 800 && pChara->GetLP() < 200){
			//---再生
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SAISEI);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 163){
		//---ゴーレムプリースト
		if(crbatCPUGetEnemy() == 1){
			if(rnd < 500){
				//---セルフリーズ
				crbatCPUThink_SetMagicAtack(pChara,49);
			} else {
				crbatCPUThink_SetAtack(pChara);
			}
		} else if(pChara->GetBtStatus() & BTST_CHINMOKU){
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 150){
			//---ライフウィンド
			crbatCPUThink_SetMagicAtack(pChara,7);
		} else if(rnd < 300){
			//---サイレンス
			crbatCPUThink_SetMagicAtack(pChara,15,-1,0,NULL,1);
		} else if(rnd < 400){
			//---ダークミスト
			crbatCPUThink_SetMagicAtack(pChara,14,-1,0,NULL,1);
		} else if(rnd < 500){
			//---パラライズ
			crbatCPUThink_SetMagicAtack(pChara,31);
		} else if(rnd < 600){
			//---エクステンド
			crbatCPUThink_SetMagicAtack(pChara,22);
		} else if(rnd < 800 && pChara->GetTurnAtack()){
			//---アクアソード
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,50);
		} else if(rnd < 800){
			//---セルフリーズ
			crbatCPUThink_SetMagicAtack(pChara,49);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 164){
		//---ペルソナドール
		if(pChara->GetBtStatus() & BTST_CHINMOKU){
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 300 && !pChara->GetTurnAtack()){
			//---エクスプロージョン
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,44);
		} else if(rnd < 300){
			//---フレアウェイヴ
			crbatCPUThink_SetMagicAtack(pChara,43);
		} else if(rnd < 600 && !pChara->GetTurnAtack()){
			//---ダウンバースト
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,56);
		} else if(rnd < 600){
			//---ウィンドオーブ
			crbatCPUThink_SetMagicAtack(pChara,55);
		} else if(rnd < 700){
			//---デスフォース
			crbatCPUThink_SetMagicAtack(pChara,21);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 165){
		//---ダークピラー
		if(rnd < 300 && !pChara->GetTurnAtack()){
			//---ベータスコール
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,68);
		} else if(rnd < 300){
			//---サンダーボルト
			crbatCPUThink_SetMagicAtack(pChara,67);
		} else if(rnd < 700){
			//---ＭＣ分解
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_MCBUNKAI,25);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 166){
		//---闇黒獣
		if(rnd < 300){
			//---かみつく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	}

	return crbatCPUThink6(pChara,turn,rnd);
}
