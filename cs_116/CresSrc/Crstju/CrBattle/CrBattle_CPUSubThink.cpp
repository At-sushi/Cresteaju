CRBATCPU_API int crbatCPUThink2(CrBattleCharacter *pChara,int turn,int rnd);
CRBATCPU_API int crbatCPUThink3(CrBattleCharacter *pChara,int turn,int rnd);
CRBATCPU_API int crbatCPUThink4(CrBattleCharacter *pChara,int turn,int rnd);
CRBATCPU_API int crbatCPUThink5(CrBattleCharacter *pChara,int turn,int rnd);

CRBATCPU_API int crbatCPUThink(CrBattleCharacter *pChara,int turn)
{
	int rnd = eiRnd(1000);
	
	//---もし混乱していれば・・・
	if(pChara->GetBtStatus() & BTST_KONRAN){
		pChara->Command.Main = BAT_COMMAND_WAIT;
		return 1;
	}
	if(pChara->GetBtStatus() & BTST_NEMURI){
		//---寝てたら
		pChara->Command.Main = BAT_COMMAND_WAIT;
		return 1;
	}
/*	if(pChara->GetBtStatus() & BTST_MAHI){
		//---麻痺
		pChara->Command.Main = BAT_COMMAND_WAIT;
		return 1;
	}*/

	if(pChara->BattleInfo.Enemy.ActionType == 0){
		//---通常攻撃
		crbatCPUThink_SetAtack(pChara);
	} else if(pChara->BattleInfo.Enemy.ActionType == 11){
		//---フォールン
		if(turn < 2){
			//---じっとまつ
			pChara->Command.Main = BAT_COMMAND_WAIT;
			if(turn == 1){
			}
		} else {
			crbatCPUThink_SetAtack(pChara);
		}

	} else if(pChara->BattleInfo.Enemy.ActionType == 12){
		//---エターナル兵
		pChara->Command.Main = BAT_COMMAND_WEAPON;
		pChara->Command.Range = BAT_TARGET_FRIENDSINGLE;
		pChara->SetTarget(&pBtChara[0]);
	} else if(pChara->BattleInfo.Enemy.ActionType == 14){
		//---エターナル兵
		if(turn < 1){
			pChara->Command.Main = BAT_COMMAND_WEAPON;
			pChara->Command.Range = BAT_TARGET_FRIENDSINGLE;
			pChara->SetTarget(&pBtChara[0]);
		} else {
			pChara->Command.Main = BAT_COMMAND_WAIT;
		}
//		pChara->Command.Main = BAT_COMMAND_WAIT;
	} else if(pChara->BattleInfo.Enemy.ActionType == 20){
		//---しゃぼんゴースト
		if(rnd < 666){
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else {
			crbatCPUThink_SetMagicAtack(pChara,47);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 25){
		//---ブラッドイーター
		if(rnd < 666){
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else {
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KYUKETSU);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 28){
		//---仮面まどう
		if(rnd < 333){
			crbatCPUThink_SetMagicAtack(pChara,41);
		} else if(rnd < 666 && !pChara->GetTurnAtack()){
			//---エアシューティング
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,53);
		} else {
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 29){
		//---毛玉
		if(rnd < 500){
			crbatCPUThink_SetMagicAtack(pChara,1);
		} else {
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 30){
		//---ゴーレムパーツ
		if(rnd < 800){
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else {
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGURU);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 31){
		//---ギラギラ
		if(rnd < 333){
			crbatCPUThink_SetMagicAtack(pChara,41);
		} else {
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 33){
		//---ラットドッグ
		if(rnd < 700){
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else {
			//---かみつく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 34){
		//---毒蛾
		if(rnd < 750){
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else if(!pChara->GetTurnAtack()){
			//---突風
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOPPU,7);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 35){
		//---Ｄ・ワーム
		//---通常攻撃
		if(rnd < 850){
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else {
			//---かみつく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 36){
		//---ウィルスモッグ
		if(rnd < 200){
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 566){
			crbatCPUThink_SetMagicAtack(pChara,11);
		} else {
			crbatCPUThink_SetMagicAtack(pChara,14);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 39){
		//---ピエール
		if(rnd < 300){
			//---エアシューティング
			crbatCPUThink_SetMagicAtack(pChara,53);
		} else if(rnd < 500){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 750){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_PIERUZAN);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 40){
		//---ジュリアス
		if(rnd < 200){
			//---スリーピング
			crbatCPUThink_SetMagicAtack(pChara,11);
		} else if(rnd < 500){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 750){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_JURIASGIRI);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 41){
		//---リザードマン
		if(rnd < 400){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 42){
		//---ロストリーフ
		if(rnd < 200 && !pChara->GetTurnAtack()){
			//---エアシューティング
			crbatCPUThink_SetMagicAtack(pChara,53);
			pChara->AddTurnAtack();
		} else if(rnd < 400){
			//---アイシング
			crbatCPUThink_SetMagicAtack(pChara,47);
		} else if(rnd < 650){
			//---サイレンス
			crbatCPUThink_SetMagicAtack(pChara,15);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 43){
		//---ガード
		if(rnd < 100){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOSSHIN);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 44){
		//---クレイシヴ
		pChara->Command.Main = BAT_COMMAND_WAIT;
/*		if(turn == 2){
			//---クレイシヴしゃべる
			//---カメラ移動
			crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);
			crbatBeginCameraObjectToObject(0,pChara,&pBtChara[0],
			ANGLE(90),
			-1.0f,-1.0f,500);
			//---リストに描くのを追加
			crbatClearDrawingList();
			crbatAddDrawingListAll();
			crbatDoMovingCamera(500);

			CrMesManager mes;
			mes.CreateNewMessage(-1,-1,32,24,5);
			mes.OpenMessage("DoguriSouth_Iseki.msg",106);
			mes.ReadMessage();
			mes.Draw();
			mes.ReadMessage();
			mes.Draw();
			mes.CloseMessage();
		}*/
	} else if(pChara->BattleInfo.Enemy.ActionType == 48){
		//---アサッシン
		if(rnd < 150){
			//---スリーピング
			crbatCPUThink_SetMagicAtack(pChara,11);
		} else if(rnd < 450){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 600){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOSSHIN);
		} else if(rnd < 750){
			//---水２
			crbatCPUThink_SetMagicAtack(pChara,48);
		} else if(rnd < 900){
			//---風２
			crbatCPUThink_SetMagicAtack(pChara,54);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 45){
		//---謎のバナナ
		if(crbatCPUGetEnemy() == 1){
			if(rnd < 500){
				//---コンフュージョン
				crbatCPUThink_SetMagicAtack(pChara,18);
			} else {
				//---ゼロシールド
				crbatCPUThink_SetMagicAtack(pChara,30);
			}
		} else if(rnd < 160){
			//---スリーピング
			crbatCPUThink_SetMagicAtack(pChara,11);
		} else if(rnd < 350){
			//---コンフュージョン
			crbatCPUThink_SetMagicAtack(pChara,18);
		} else if(rnd < 480){
			//---サイレンス
			crbatCPUThink_SetMagicAtack(pChara,15);
		} else if(rnd < 640){
			//---パワーブースト
			crbatCPUThink_SetMagicAtack(pChara,19);
		} else if(rnd < 800){
			//---ゼロシールド
			crbatCPUThink_SetMagicAtack(pChara,30);
		} else {
			//---リカバリー
			crbatCPUThink_SetMagicAtack(pChara,18);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 46){
		//---ダークフラワー
		if(rnd < 650){
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 900){
			//---かみつく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---レイザーレイ
			crbatCPUThink_SetMagicAtack(pChara,42);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 47){
		//---サンドシェル
		//---通常攻撃
		crbatCPUThink_SetAtack(pChara);
	} else if(pChara->BattleInfo.Enemy.ActionType == 49){
		//---アメーバー
		if(rnd < 300){
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 600){
			//---とかす
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOKASU);
		} else if(rnd < 900){
			//---窒息
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CHISSOKU_1_10);
		} else if(pChara->GetBattleFlag(0)){
			//---分裂
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_BUNRETU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 50){
		//---アイスモスキート
		if(rnd < 400){
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 700){
			//---吸血
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KYUKETSU);
		} else if(rnd < 870){
			//---アイシング
			crbatCPUThink_SetMagicAtack(pChara,47);
		} else if(!pChara->GetTurnAtack()){
			//---アイスブラスト
			crbatCPUThink_SetMagicAtack(pChara,48);
			pChara->AddTurnAtack();
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 51){
		//---スケルトン
		if(rnd < 750){
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else {
			//---スリーピング
			crbatCPUThink_SetMagicAtack(pChara,11);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 52){
		//---リュウモドキ
		if(rnd < 300){
			//---噛みつく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else if(rnd < 600 && !pChara->GetTurnAtack()
			&& pChara->GetPersonalTurn() == 0){
			//---炎
			pChara->AddTurnAtack();
			pChara->AddPersonalTurn(2);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,20);
		} else if(rnd < 600){
			//---かみつく
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,10);
		} else {
			//---攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 53){
		//---エターナル兵
		if(rnd < 150){
			//---スリーピング
			crbatCPUThink_SetMagicAtack(pChara,11);
		} else if(rnd < 400 && pChara->GetPersonalTurn() == 0){
			//---風２
			crbatCPUThink_SetMagicAtack(pChara,54);
			pChara->AddPersonalTurn(2);
		} else if(rnd < 600 && pChara->GetPersonalTurn() == 0){
			//---土２
			crbatCPUThink_SetMagicAtack(pChara,60);
			pChara->AddPersonalTurn(2);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 54){
		//---エターナル兵
		if(rnd < 400){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 600 && pChara->GetPersonalTurn() == 0){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
			pChara->AddPersonalTurn(2);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 55){
		//---ドブウニ
		if(rnd < 500){
			//---回転アタック
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAITENATACK);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 56){
		//---地下シメジ
		if(rnd < 350){
			//---かみつく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else if(rnd < 600){
			//---胞子
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HOUSHI,6);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 57){
		//---下水貝
		if(rnd < 500){
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 750){
			//---レイザーレイ
			crbatCPUThink_SetMagicAtack(pChara,42);
		} else {
			//---ライティングネット
			crbatCPUThink_SetMagicAtack(pChara,66);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 58){
		//---カイワレ
		if(rnd < 250){
			//---成長
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SEICHOU);
		} else if(rnd < 500 && pChara->GetLP() != pChara->GetMaxLP()){
			//---光合成
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KOUGOUSEI);
		} else if(rnd < 500){
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 750){
			//---プラネット
			crbatCPUThink_SetMagicAtack(pChara,60);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 59){
		//---レッドヘル
		if(rnd < 300){
			//---吸血
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KYUKETSU);
		} else if(rnd < 600){
			//---かみつく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 60){
		//---フェイクミスト
		if(rnd < 200){
			//---アイシング
			crbatCPUThink_SetMagicAtack(pChara,47);
		} else if(rnd < 400){
			//---アシッドミスト
			crbatCPUThink_SetMagicAtack(pChara,48);
		} else if(rnd < 550){
			//---パラライズ
			crbatCPUThink_SetMagicAtack(pChara,31);
		} else if(rnd < 700){
			//---コンフュージョン
			crbatCPUThink_SetMagicAtack(pChara,18);
		} else if(rnd < 800){
			//---リカバリー２
			crbatCPUThink_SetMagicAtack(pChara,3);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else {
		crbatCPUThink_SetAtack(pChara);
	}

	return crbatCPUThink2(pChara,turn,rnd);
}

