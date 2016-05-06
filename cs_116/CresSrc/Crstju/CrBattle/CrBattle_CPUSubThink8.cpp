CRBATCPU_API int crbatCPUThink8(CrBattleCharacter *pChara,int turn,int rnd)
{
	if(pChara->BattleInfo.Enemy.ActionType == 215){
		//---ルクスゼア
		if(rnd < 150){
			//---斬りかかる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 350){
			//---吸血
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KYUKETSU);
		} else if(rnd < 480){
			//---サイレンス
			crbatCPUThink_SetMagicAtack(pChara,15);
		} else if(rnd < 550){
			//---インフルエンス
			crbatCPUThink_SetMagicAtack(pChara,20);
		} else if(rnd < 700){
			//---スーパーセル
			crbatCPUThink_SetMagicAtack(pChara,57);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 228){
		//---ウォーターゴースト
		if(rnd < 250){
			//---アクアソード
			crbatCPUThink_SetMagicAtack(pChara,50);
		} else if(rnd < 400){
			//---セルフリーズ
			crbatCPUThink_SetMagicAtack(pChara,49);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 229){
		//---テイルビースト
		if(rnd < 333){
			//---噛みつく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 230){
		//---爆弾草
		if(pChara->GetBattleFlag(0)){
			//---大爆発
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_JIBAKU3,0,pChara);
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
	} else if(pChara->BattleInfo.Enemy.ActionType == 231){
		//---ミドリムシ
		if(rnd < 300){
			//---とかす
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOKASU);
		} else if(rnd < 500){
			//---窒息
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_CHISSOKU_1_5);
		} else if(!pChara->GetBattleFlag(0) && rnd < 550){
			//---分裂
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_BUNRETU);
		} else if(rnd < 700){
			//---酸
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SAN);
		} else if(rnd < 800){
			//---再生
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SAISEI);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 232){
		//---バトルセンサー
		if(rnd < 250){
			//---パワーボム
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_POWERBOMB,100);
		} else if(rnd < 450){
			//---スリープブレス
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,30);
		} else if(rnd < 650){
			//---サイレントブレス
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SILENTBREATH,30);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 233){
		//---マツタケウィザート
		if(rnd < 333){
			//---ベータスコール
			crbatCPUThink_SetMagicAtack(pChara,68);
		} else if(rnd < 500){
			//---インフルエンス
			crbatCPUThink_SetMagicAtack(pChara,20);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 234){
		//---パワーハンド
		if(rnd < 250){
			//---殴る
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGURU);
		} else if(rnd < 500){
			//---突進
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOSSHIN);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 236){
		//---ライリュウ
		if(rnd < 333){
			//---かみなり
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_IKADUCHI,300);
		} else if(rnd < 600){
			//---かみつく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 237){
		//---ファーシェル
		if(rnd < 250){
			//---アクアソード
			crbatCPUThink_SetMagicAtack(pChara,50);
		} else if(rnd < 500){
			//---水鉄砲
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_MIZUDEPPOU,150);
		} else if(rnd < 700){
			//---リカバレイション
			crbatCPUThink_SetMagicAtack(pChara,6);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 238){
		//---ミンクボール
		if(rnd < 250){
			//---スリーピング
			crbatCPUThink_SetMagicAtack(pChara,11);
		} else if(rnd < 450){
			//---パワーブースト
			crbatCPUThink_SetMagicAtack(pChara,19);
		} else if(rnd < 700){
			//---きりかかる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 240){
		//---バトルクラウン
		if(rnd < 333){
			//---ライジングサン
			crbatCPUThink_SetMagicAtack(pChara,45);
		} else if(rnd < 666){
			//---テラジャッジメント
			crbatCPUThink_SetMagicAtack(pChara,69);
		} else if(rnd < 750){
			//---デスフォース
			crbatCPUThink_SetMagicAtack(pChara,21);
		} else if(rnd < 900){
			//---コンフュージョン
			crbatCPUThink_SetMagicAtack(pChara,18);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 241){
		//---ダークパラディン
		if(rnd < 250){
			//---激しく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else if(rnd < 500){
			//---きりかかる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 242){
		//---ストレングス
		if(rnd < 200){
			//---突進
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOSSHIN);
		} else if(rnd < 400){
			//---なぎ倒す
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGITAOSU);
		} else if(rnd < 600){
			//---殴る
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGURU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	}
	return 1;
}
