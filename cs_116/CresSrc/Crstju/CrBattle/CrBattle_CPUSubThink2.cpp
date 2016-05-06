
CRBATCPU_API int crbatCPUThink2(CrBattleCharacter *pChara,int turn,int rnd)
{
	if(pChara->BattleInfo.Enemy.ActionType == 61){
		//---ワンダリングソウル
		if(rnd < 150){
			//---斬りかかる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 250){
			//---激しく斬りつける
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else if(rnd < 300){
			//---突撃
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOTUGEKI);
		} else if(rnd < 550){
			//---なぎ倒す
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGITAOSU);
		} else if(rnd < 750){
			//---アイスＬ２
			crbatCPUThink_SetMagicAtack(pChara,48);
			pChara->Command.Sub[CRBAT_SUBTARGET] = 1;
		} else if(rnd < 850){
			//---インフルエンス
			crbatCPUThink_SetMagicAtack(pChara,20);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 62){
		//---ハイリザード
		if(rnd < 333){
			//---斬りかかる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 500){
			//---激しく斬りつける
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 63){
		//---邪教徒
		if(rnd < 300 && !pChara->GetTurnAtack()){
			//---ストリームクロウ
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,54);
		} else if(rnd < 400){
			//---エアシューティング
			crbatCPUThink_SetMagicAtack(pChara,53);
		} else if(rnd < 600 && pChara->GetTurnAtack() <= 1){
			//---レイザーレイ
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,42);
		} else if(rnd < 750){
			//---スリーピング
			crbatCPUThink_SetMagicAtack(pChara,11);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 64){
		//---赤枯れ木
		if(rnd < 200){
			//---ゼロシールド
			crbatCPUThink_SetMagicAtack(pChara,30);
		} else if(rnd < 450){
			//---ディストーション
			crbatCPUThink_SetMagicAtack(pChara,12);
		} else if(rnd < 650){
			//---雷レベル２
			crbatCPUThink_SetMagicAtack(pChara,66);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 65){
		//---モリツムリ
		if(rnd < 400){
			//---とかす
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOKASU);
		} else if(rnd < 600){
			//---パワーブースト
			crbatCPUThink_SetMagicAtack(pChara,19);
			pChara->Command.Target = (ei_u32)pChara;
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 66){
		//---ダブルテイル
		if(rnd < 333 && !pChara->GetTurnAtack() && !pChara->GetPersonalTurn()){
			//---吹雪
			pChara->AddTurnAtack();
			pChara->AddPersonalTurn(3);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_FUBUKI,30	);
		} else if(rnd < 550){
			//---噛みつく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 67){
		//---ラーフィア
		if(pChara->GetMC() < 70){
			//---ＭＣが少なくなったら通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else if(pChara->GetLP() < 170 && pChara->GetBattleFlag(1) == 0){
			//---ＬＰが減ったら回復
			crbatCPUThink_SetMagicAtack(pChara,6);
			pChara->SetBattleFlag(1,pChara->GetBattleFlag(1) + 1);
		} else if(turn == 0){
			//---ターン最初
			//---エクステンド
			crbatCPUThink_SetMagicAtack(pChara,22);
		} else if(rnd < 250 && pChara->GetBattleFlag(0) == 0
			&& turn != 1){
			//---サイレンス
			pChara->SetBattleFlag(0,1);
			crbatCPUThink_SetMagicAtack(pChara,15,-1,0,&pBtChara[0]);
		} else if(rnd < 500 || turn == 1){
			//---ウィンドオーヴ
			if(pChara->GetBattleFlag(2) == 0){
				crbatCPUThink_SetMagicAtack(pChara,55);
//				pChara->SetBattleFlag(2,2);
			} else {
				//---通常攻撃
				crbatCPUThink_SetAtack(pChara);
			}
		} else if(rnd < 700){
			//---サンダーボルト
			if(pChara->GetBattleFlag(2) == 0){
				crbatCPUThink_SetMagicAtack(pChara,67);
//				pChara->SetBattleFlag(2,2);
			} else {
				crbatCPUThink_SetMagicAtack(pChara,66);
			}
		} else if(rnd < 900){
			//---セルフリーズ
			if(pChara->GetBattleFlag(2) == 0){
				crbatCPUThink_SetMagicAtack(pChara,49);
//				pChara->SetBattleFlag(2,2);
			} else {
				crbatCPUThink_SetMagicAtack(pChara,47 + eiRnd(2));
			}
		} else if(rnd < 975){
			//---デスフォース
			if(pChara->GetBattleFlag(7) == 0){
				crbatCPUThink_SetMagicAtack(pChara,21);
				pChara->SetBattleFlag(7,1);
			} else {
				//---ウィンドオーヴ
				if(pChara->GetBattleFlag(2) == 0){
					crbatCPUThink_SetMagicAtack(pChara,55);
//					pChara->SetBattleFlag(2,2);
				} else {
					//---通常攻撃
					crbatCPUThink_SetAtack(pChara);
				}
			}
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}

		if(pChara->GetBattleFlag(2) > 0){
			pChara->SetBattleFlag(2,pChara->GetBattleFlag(2) - 1);
		}
//---------------２部
	} else if(pChara->BattleInfo.Enemy.ActionType == 68){
		//---白ナメコ
		if(rnd < 350){
			//---かみつく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else if(rnd < 600){
			//---胞子
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HOUSHI,10);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 69){
		//---フローティングアイ
		if(rnd < 200){
			//---ダークミスト
			crbatCPUThink_SetMagicAtack(pChara,14);
		} else if(rnd < 400){
			//---アイスＬｖ２
			crbatCPUThink_SetMagicAtack(pChara,48);
		} else if(rnd < 700 && !pChara->GetTurnAtack()){
			//---アイスＬｖ３
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,49);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 70){
		//---デシベル
		if(rnd < 350){
			//---吸血
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KYUKETSU);
		} else if(rnd < 500){
			//---衝撃波
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SHOGEKIHA,6);
		} else if(rnd < 700){
			//---超音波
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CHOUONPA,6);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 72){
		//---ストーンブレイカー
		if(rnd < 350){
			//---殴る
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGURU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 74){
		//---デスメッセンジャー
		if(rnd < 300){
			//---デスフォース
			crbatCPUThink_SetMagicAtack(pChara,21);
		} else if(rnd < 500){
			//---パラライズ
			crbatCPUThink_SetMagicAtack(pChara,31);
		} else if(rnd < 750){
			//---フレアウェイヴ
			crbatCPUThink_SetMagicAtack(pChara,43);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 75){
		//---ヤマウニ
		if(rnd < 550){
			//---回転アタック
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAITENATACK);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 76){
		//---ピカピカ
		if(rnd < 250){
			//---サンダーボルト
			crbatCPUThink_SetMagicAtack(pChara,66);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 77){
		//---夕焼けバナナ
		if(rnd < 200){
			//---ライフシャワー
			crbatCPUThink_SetMagicAtack(pChara,5);
		} else if(rnd < 350){
			//---パワーブースト
			crbatCPUThink_SetMagicAtack(pChara,19);
		} else if(rnd < 500){
			//---シールドブレイク
			crbatCPUThink_SetMagicAtack(pChara,30);
		} else if(rnd < 700){
			//---コンフュージョン
			crbatCPUThink_SetMagicAtack(pChara,18);
		} else if(rnd < 900){
			//---スリーピング
			crbatCPUThink_SetMagicAtack(pChara,11);
		} else {
			//---ダークミスト
			crbatCPUThink_SetMagicAtack(pChara,14);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 78){
		//---プレーンワーム
		if(rnd < 250){
			//---砂嵐
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SUNAARASHI,50);
		} else if(rnd < 400){
			//---噛みつく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else if(rnd < 500){
			//---窒息１／２
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CHISSOKU_1_2);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 80){
		//---森の精
		if(rnd < 200){
			//---ディストーション
			crbatCPUThink_SetMagicAtack(pChara,12);
		} else if(rnd < 400){
			//---アシッドミスト
			crbatCPUThink_SetMagicAtack(pChara,48);
		} else if(rnd < 550){
			//---パラライズ
			crbatCPUThink_SetMagicAtack(pChara,31);
		} else if(rnd < 750){
			//---リカバリー２
			crbatCPUThink_SetMagicAtack(pChara,3);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 81){
		//---月食花
			crbatCPUThink_SetAtack(pChara);
	} else if(pChara->BattleInfo.Enemy.ActionType == 82){
		//---クローバー
		if(rnd < 250){
			//---成長
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SEICHOU);
		} else if(rnd < 500 && pChara->GetLP() != pChara->GetMaxLP()){
			//---光合成
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KOUGOUSEI);
		} else if(rnd < 500){
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 800 && pChara->GetTurnAtack() <= 1){
			//---グラスシード
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,61);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	}

	return crbatCPUThink3(pChara,turn,rnd);
}
