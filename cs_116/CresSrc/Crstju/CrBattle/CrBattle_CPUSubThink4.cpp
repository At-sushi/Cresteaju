CRBATCPU_API int crbatCPUThink4(CrBattleCharacter *pChara,int turn,int rnd)
{
	if(pChara->BattleInfo.Enemy.ActionType == 119){
		//---補修装置
		if(pChara->GetLP() < 320 && pChara->GetBattleFlag(0) == 0){
			//---LPが３２０以下になったら移動開始
			int x,y;
			pChara->SetBattleFlag(0,1);
			crbatCPU_GetPlayerCharaSide(pChara,&x,&y);
			crbatCPUThink_SetDefense(pChara,3,x,y);
		} else if(pChara->GetBattleFlag(0)){
			//---爆発
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_JIBAKU1,0,pChara);
		} else if(rnd < 500 && pBtChara[BATTLECHARA_STARTENEMY].DoExist()){
			//---修理
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SHURI,0,&pBtChara[BATTLECHARA_STARTENEMY + 2]);
		} else if(rnd < 700 && pChara->GetBattleFlag(1) == 0
			 && pBtChara[BATTLECHARA_STARTENEMY].DoExist()){
			//---機能追加
			pChara->SetBattleFlag(1,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KINOUTUIKA,0,&pBtChara[BATTLECHARA_STARTENEMY + 2]);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 120){
		//---防衛システム
		if(turn == 0){
			//---バリアー展開
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_BARRIERTENKAI);
		} else if(turn == 1){
			//---カスケードボム準備
			pChara->SetBattleFlag(0,1);
			pChara->ResetPersonalTurn();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KASCADE_JUNBI);
		} else if(pChara->GetLP() < 2100
			&& pChara->GetBattleFlag(0) == 1){
			//---カスケードボム機能強化
			pChara->SetBattleFlag(0,2);
			pChara->ResetPersonalTurn();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KASCADE_KYOKA);
		} else if(pChara->GetLP() < 600
			&& pChara->GetBattleFlag(0) == 2){
			//---反物質全体
			pChara->ResetPersonalTurn();
			pChara->SetBattleFlag(0,3);
			pChara->AddPersonalTurn(3);
			pChara->SetBattleFlag(1,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HANBUSSHITU_ZENTAI);
/*			//---反物質準備
			pChara->SetBattleFlag(0,3);
			pChara->ResetPersonalTurn();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HANBUSSITU_JUNBI);*/
		} else if(pChara->GetBattleFlag(0) == 3
			&& pChara->GetBattleFlag(1) == 1){
			//---カスケードボム出力最大
			pChara->SetBattleFlag(0,4);
			pChara->ResetPersonalTurn();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KASCADE_SAIDAI);

/*		} else if(!pChara->GetPersonalTurn()
			&& pChara->GetBattleFlag(0) == 3 && pChara->GetBattleFlag(1) == 0){
			//---反物質全体
			pChara->AddPersonalTurn(3);
			pChara->SetBattleFlag(1,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HANBUSSHITU_ZENTAI);
*/
		} else if(rnd < 200 && !pChara->GetPersonalTurn()
			&& pChara->GetLP() < 2000){
			//---浸食
			pChara->AddPersonalTurn(2);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SHINSHOKU);
		} else if(rnd < 300){
			//---反物質
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HANBUSSHITU);
		} else if(rnd < 400 && pChara->GetBattleFlag(0) == 4){
			//---レーザー
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_LAYZERBEAM,120);
		} else if(rnd < 400 && pChara->GetPersonalTurn() <= 1){
			//---レーザー光線
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_LAYZERBEAM,90);
		} else if(rnd < 400){
			//---レーザー光線
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_LAYZERBEAM,55);
		} else if(rnd < 550 && pChara->GetBattleFlag(0) == 4){
			//---火炎放射
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAENHOUSHA,130);
		} else if(rnd < 550 && pChara->GetPersonalTurn() <= 1){
			//---火炎放射
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAENHOUSHA,110);
		} else if(rnd < 550){
			//---火炎放射
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAENHOUSHA,55);
		} else if((rnd < 850 || (turn + 1) % 4 == 0) && !pChara->GetPersonalTurn()
			&& pChara->GetBattleFlag(0) >= 1){
			//---カスケードボム
			pChara->AddPersonalTurn(3);
			if(pChara->GetBattleFlag(0) == 0){
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_POWERBOMB,120);
			} else if(pChara->GetBattleFlag(0) == 1){
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_KASCADEBOMB,140);
			} else if(pChara->GetBattleFlag(0) <= 3){
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_KASCADEBOMB,160);
			} else if(pChara->GetBattleFlag(0) == 4){
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_KASCADEBOMB,185);
			}
		} else if(rnd < 800 && pChara->GetBattleFlag(2) == 0
			&& crbatCPUGetEnemy() == 1){
			//---グラビティ
			pChara->SetBattleFlag(2,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_GRAVITY);
		} else if(rnd < 800){
			//---攻撃
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 950 && crbatCPU_PlayerIsBaraBara(pChara,2)
			&& crbatCPUGetEnemy() == 1){
			//---ばらばらになったら集める
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_GRAVITY);
		} else if(rnd < 900){
			//---スリープブレス
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,30);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	
	} else if(pChara->BattleInfo.Enemy.ActionType == 121){
		//---エターナル兵（戦士）
		if(crbatCPUGetEnemy() == 1){
			if(rnd < 500 && !pChara->GetPersonalTurn()){
				pChara->AddPersonalTurn(2);
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_ENGETUZAN);
			} else {
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
			}
		} else if(rnd < 300){
			//---斬りかかる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 500){
			//---激しく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else if(rnd < 700 && !pChara->GetTurnAtack()){
			//---円月斬
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_ENGETUZAN);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 122){
		//---エターナル兵（魔法使い）
		if(pChara->GetMC() < 100 || (pChara->GetBtStatus() & BTST_CHINMOKU)){
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else if(crbatCPUGetEnemy() == 1){
			//---自分一人
			if(rnd < 350 && !pChara->GetPersonalTurn()){
				pChara->AddPersonalTurn(2);
				crbatCPUThink_SetMagicAtack(pChara,44);
			} else if(rnd < 700 && !pChara->GetPersonalTurn()){
				pChara->AddPersonalTurn(2);
				crbatCPUThink_SetMagicAtack(pChara,50);
			} else {
				crbatCPUThink_SetMagicAtack(pChara,55);
			}
		} else if(rnd < 333 && !pChara->GetTurnAtack()){
			//---エクスプロージョン
			pChara->AddTurnAtack();
			if(!pChara->GetPersonalTurn()){
				pChara->AddPersonalTurn(2);
				crbatCPUThink_SetMagicAtack(pChara,44);
			} else {
				crbatCPUThink_SetMagicAtack(pChara,43);
			}
		} else if(rnd < 333){
			//---フレアウェイヴ
			crbatCPUThink_SetMagicAtack(pChara,43);
		} else if(rnd < 666 && !pChara->GetTurnAtack()){
			//---アクアソード
			pChara->AddTurnAtack();
			if(!pChara->GetPersonalTurn()){
				pChara->AddPersonalTurn(2);
				crbatCPUThink_SetMagicAtack(pChara,50);
			} else {
				crbatCPUThink_SetMagicAtack(pChara,49);
			}
		} else if(rnd < 900){
			//---ウィンドオーブ
			crbatCPUThink_SetMagicAtack(pChara,55);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 123){
		//---エターナル兵（僧侶）
		if(pChara->GetMC() < 50 || (pChara->GetBtStatus() & BTST_CHINMOKU)){
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else if(crbatCPUGetEnemy() == 1){
			//---自分一人
			if(rnd < 350){
				//---デスフォース
				crbatCPUThink_SetMagicAtack(pChara,21);
			} else if(rnd < 750){
				//---コンフュージョン
				crbatCPUThink_SetMagicAtack(pChara,18,-1,0,NULL,1);
			} else {
				crbatCPUThink_SetAtack(pChara);
			}
		} else if(rnd < 150){
			//---ライフウィンド
			crbatCPUThink_SetMagicAtack(pChara,7);
		} else if(rnd < 300){
			//---リカバリー３
			crbatCPUThink_SetMagicAtack(pChara,6);
		} else if(rnd < 450){
			//---プロテクション
			crbatCPUThink_SetMagicAtack(pChara,13);
		} else if(rnd < 600){
			//---フォースシールド
			crbatCPUThink_SetMagicAtack(pChara,17);
		} else if(rnd < 800){
			//---ダークミスト
			crbatCPUThink_SetMagicAtack(pChara,14);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 124){
		//---エターナル兵（特殊）
		if(crbatCPUGetEnemy() == 1){
			if(rnd < 400 && !pChara->GetPersonalTurn()){
				//---パワーボム
				pChara->AddPersonalTurn(2);
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_POWERBOMB,100);
			} else if(rnd < 750){
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,40);
			} else {
				//---サイレントブレス
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_SILENTBREATH,40);
			}
		} else if(rnd < 200){
			//---スリープブレス
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,40);
		} else if(rnd < 400){
			//---サイレントブレス
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SILENTBREATH,40);
		} else if(rnd < 800 && !pChara->GetTurnAtack()){
			//---パワーボム
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_POWERBOMB,100);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}

	//---
	} else if(pChara->BattleInfo.Enemy.ActionType == 126){
		//---エイノー
		if(rnd < 200){
			//---あくび
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_AKUBI);
		} else if(rnd < 400){
			//---だるだる波
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_DARUDARUHA);
		} else if(rnd < 600){
			//---寝る
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NERU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 127){
		//---ストレンジタキシード
		if(rnd < 333){
			//---タキシードビーム
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TAKISIDOBEAM,80);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 128){
		//---トーテムポール
		if(rnd < 200){
			//---サイレンス
			crbatCPUThink_SetMagicAtack(pChara,15);
		} else if(rnd < 500 && !pChara->GetTurnAtack()){
			//---ウィンドオーブ
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,55);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 131){
		//---エド
		if(turn == 0){
			//---レーザー光線
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_LAYZERBEAM,80,&pBtChara[0]);
		} else if(pChara->GetBattleFlag(1)){
			//---ためてたら、カスケードボム
			pChara->SetBattleFlag(1,0);
			pChara->AddPersonalTurn(3);
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KASCADEBOMB,220);
		} else if(pChara->GetPersonalTurn() >= 2){
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 100){
			//---混乱光線
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KONRANKOUSEN,30);
		} else if(rnd < 350){
			//---レーザー光線
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_LAYZERBEAM,80);
		} else if(rnd < 500){
			//---入れ歯クラッシュ
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_IREBACRASH);
		} else if(rnd < 600 && crbatCPUGetEnemy() == 1){
			//---反物質
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HANBUSSHITU);
		} else if(rnd < 600){
			//---とかす
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOKASU);
		} else if(rnd < 800 && !pChara->GetPersonalTurn()
			&& !pChara->GetTurnAtack()){
			//---カスケードボム
			pChara->AddPersonalTurn(3);
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KASCADEBOMB,120);
//			pChara->SetBattleFlag(0,1);
//			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TAMERU);
		} else if(rnd < 900 && crbatCPUGetEnemy() == 1){
			//---溜める
			pChara->SetBattleFlag(1,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TAMERU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 132){
		//---ラーフィア
		if(pChara->GetMC() < 70){
			//---ＭＣが少なくなったら通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else if(turn == 1){
			//---ウィンドオーブ
			crbatCPUThink_SetMagicAtack(pChara,55,-1,0,&pBtChara[0]);
		} else if(turn == 0){
			//---ターン最初
			//---エクステンド
			crbatCPUThink_SetMagicAtack(pChara,22,-1,0,pChara);
/*		} else if(pChara->GetLP() <= 400 && !pChara->GetBattleFlag(1)){
			//---リカバレイション
			pChara->SetBattleFlag(1,1);
			crbatCPUThink_SetMagicAtack(pChara,6);*/
		} else if(rnd < 333 && !pChara->GetTurnAtack()
			 && !pChara->GetPersonalTurn()){
			//---ダウンバースト
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,56);
		} else if(rnd < 333){
			//---ウィンドオーブ
			crbatCPUThink_SetMagicAtack(pChara,55);
		} else if(rnd < 666 && !pChara->GetTurnAtack() && !pChara->GetPersonalTurn()
			&& crbatCPUGetEnemy() == 1){
			//---ライジングサン
			pChara->AddPersonalTurn(2);
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,45);
		} else if(rnd < 666){
			//---エクスプロージョン
			crbatCPUThink_SetMagicAtack(pChara,44);
		} else if(rnd < 850){
			//---ベータスコール
			crbatCPUThink_SetMagicAtack(pChara,68);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 133){
		//---ストーンゴーレム
		if(rnd < 300){
			//---なぐる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGURU);
		} else if(rnd < 500){
			//---突進
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOSSHIN);
		} else if(rnd < 650 && pChara->GetTurnAtack() <= 1){
			//---なぎ倒す
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGITAOSU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 134){
		//---キラーボム
		if(pChara->GetBattleFlag(0)){
			//---爆発
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_JIBAKU1,0,pChara);
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
	} else if(pChara->BattleInfo.Enemy.ActionType == 135){
		//---エンシェントソード
		if(rnd < 280){
			//---斬りかかる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 400){
			//---突進
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else if(rnd < 700 && !pChara->GetPersonalTurn()
			&& turn == 0 && crbatCPUGetEnemy() > 1){
			//---パワーブースト
			pChara->AddPersonalTurn(10);
			crbatCPUThink_SetMagicAtack(pChara,19,BAT_TARGET_ME);
			pChara->Command.Target = (ei_u32)pChara;
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 136){
		//---グリーンドラゴン
		if(crbatCPUGetEnemy() == 1 && rnd < 500){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,140);
		} else if(rnd < 250 && !pChara->GetTurnAtack()){
			//---炎
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,140);
		} else if(rnd < 400){
			//---炎
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,75);
		} else if(rnd < 500){
			//---スリープブレス
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,30);
		} else if(rnd < 750){
			//---かみつく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 137){
		//---バナナくらげ
		if(rnd < 350){
			//---オーロラテイル
			crbatCPUThink_SetMagicAtack(pChara,23);
		} else if(rnd < 450){
			//---リカバレイション
			crbatCPUThink_SetMagicAtack(pChara,6);
		} else if(rnd < 550){
			//---ライフウィンド
			crbatCPUThink_SetMagicAtack(pChara,7);
		} else if(rnd < 600){
			//---エクステンド
			crbatCPUThink_SetMagicAtack(pChara,22);
		} else if(rnd < 750){
			//---ゼロシールド
			crbatCPUThink_SetMagicAtack(pChara,30,-1,0,NULL,1);
		} else {
			//---コンフュージョン
			crbatCPUThink_SetMagicAtack(pChara,18,-1,0,NULL,1);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 138){
		//---マジシャンボール
		if(rnd < 280 && !pChara->GetTurnAtack()
			&& pChara->GetPersonalTurn() == 0){
			//---ダウンバースト
			pChara->AddPersonalTurn(2);
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,56);
		} else if(rnd < 300){
			//---ウィンドオーブ
			crbatCPUThink_SetMagicAtack(pChara,55);
		} else if(rnd < 500 && !pChara->GetTurnAtack()){
			//---ベータスコール
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,68);
		} else if(rnd < 700){
			//---サンダーボルト
			crbatCPUThink_SetMagicAtack(pChara,67);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 140){
		//---侵略兵
		if(rnd < 500){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SINRYAKUHEI,255);
		} else {
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SINRYAKUHEI_BOMB,320);
		}
	}

	return crbatCPUThink5(pChara,turn,rnd);
}
