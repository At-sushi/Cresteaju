
CRBATCPU_API int crbatCPUThink3(CrBattleCharacter *pChara,int turn,int rnd)
{
	if(pChara->BattleInfo.Enemy.ActionType == 83){
		//---ソードウルフ
		if(rnd < 333){
			//---噛みつく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 84){
		//---ミスティジェントル
		if(rnd < 333){
			//---ミスティビーム
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_MISTYBEAM,60);
		} else if(rnd < 600){
			//---ジェントルフラッシュ
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_JENTLEFLASH);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 85){
		//---リビングアーマー
		if(rnd < 333){
			//---斬りかかる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 600){
			//---激しく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else if(rnd < 700){
			//---なぎ倒す
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGITAOSU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 86){
		//---レッドボーン
		if(rnd < 250 && !pChara->GetTurnAtack()
			&& pChara->GetPersonalTurn() == 0){
			//---突風
			pChara->AddTurnAtack();
			pChara->AddPersonalTurn(3);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SUNAARASHI,60);
		} else if(rnd < 250
			&& pChara->GetPersonalTurn() <= 1){
			pChara->AddPersonalTurn(1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SUNAARASHI,30);
		} else if(rnd < 450){
			//---スリーピング（全）
			crbatCPUThink_SetMagicAtack(pChara,11,-1,0,NULL,1);
		} else if(pChara->GetLP() < 50
			&& pChara->GetBattleFlag(0) == 0){
			//---ＬＰチェンジ
			pChara->SetBattleFlag(0,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_LPCHANGE,1000);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 87){
		//---ルインズガーディア
		//---ばらばらだったらダウンバースト
		if(pChara->GetBattleFlag(2)){
			rnd = (rnd * 2) / 3;
		}
		pChara->SetBattleFlag(2,0);

		if(pChara->GetBtStatus() & BTST_CHINMOKU){
			//---沈黙だったら通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else if(pChara->GetMC() < 100){
			//---ＭＣがなくなったら通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else if(crbatCPU_PlayerIsBaraBara(pChara,2)
			&& rnd < 400){
			//---ダウンバースト
			crbatCPUThink_SetMagicAtack(pChara,56);
		} else if(rnd < 400 && !pChara->GetPersonalTurn()){
			//---エクスプロージョン
			pChara->AddPersonalTurn(2);
			crbatCPUThink_SetMagicAtack(pChara,44);
		} else if(rnd < 250){
			//---レイザーレイ
			crbatCPUThink_SetMagicAtack(pChara,42);
		} else if(rnd < 500 && !pChara->GetPersonalTurn()){
			//---ベータスコール
			pChara->AddPersonalTurn(2);
			crbatCPUThink_SetMagicAtack(pChara,68);
		} else if(rnd < 650){
			//---フレアウェイヴ
			crbatCPUThink_SetMagicAtack(pChara,43);
		} else if(rnd < 800){
			//---インフルエンス
			crbatCPUThink_SetMagicAtack(pChara,20,-1,0,NULL,1);
			pChara->SetBattleFlag(2,1);
		} else if(rnd < 900){
			//---サイレンス
			crbatCPUThink_SetMagicAtack(pChara,15,-1,0,NULL,1);
			pChara->SetBattleFlag(2,1);
		} else if(rnd < 1000){
			//---コンフュージョン
			crbatCPUThink_SetMagicAtack(pChara,18);
			pChara->SetBattleFlag(2,1);
		} else if(!pChara->GetBattleFlag(0)){
			//---プロテクション
			pChara->SetBattleFlag(0,1);
			pChara->SetBattleFlag(2,1);
			crbatCPUThink_SetMagicAtack(pChara,13);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 88){
		//---プチサイクロン
		if(rnd < 200){
			//---突風
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOPPU,30);
		} else if(rnd < 500 && !pChara->GetTurnAtack()){
			//---ウィンドオーブ
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,55);
		} else if(rnd < 500){
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 700){
			//---衝撃波
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SHOGEKIHA);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
//		crbatCPUThink_SetMagicAtack(pChara,23);
	} else if(pChara->BattleInfo.Enemy.ActionType == 89){
		//---糸玉
		if(rnd < 333){
			//---リカバリー２
			crbatCPUThink_SetMagicAtack(pChara,3);
		} else if(rnd < 500){
			//---スリーピング
			crbatCPUThink_SetMagicAtack(pChara,11);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 90){
		//---ダークアイ
		if(rnd < 333){
			//---アイビーム
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_EYEBEAM,50);
		} else if(rnd < 666){
			//---ぐるぐる目玉
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_GURUGURUMEDAMA,50);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 91){
		//---盗賊
		CrBattleCharacter *pnear = crbatCPU_PlayerIsSekkin(pChara,0);

		if(pnear != NULL && rnd < 500){
			//--近づきすぎたら
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SEKKINATACK,0,pnear);
		} else if(pnear != NULL && rnd < 700){
			//---移動
			crbatCPUThink_SetDefense(pChara,3);
		} else if(rnd < 333){
			//---斬りかかる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 530 && !pChara->GetPersonalTurn()){
			//---円月斬
			pChara->AddPersonalTurn(3);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_ENGETUZAN);
		} else if(rnd < 650){
			//---ダークミスト
			crbatCPUThink_SetMagicAtack(pChara,14);
		} else if(rnd < 800){
			//---ゼロシールド（範囲）
			crbatCPUThink_SetMagicAtack(pChara,30,-1,0,NULL,1);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 92){
		//---グラスエスカルゴ
		if(rnd < 150){
			//---殻
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KARA);
		} else if(rnd < 400){
			//---溶かす
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOKASU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 93){
		//---妖術士
		if(rnd < 333 && !pChara->GetTurnAtack()){
			//---グラスシード
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,61,-1,0,NULL,1);
		} else if(rnd < 333){
			//---ストリームクロウ
			crbatCPUThink_SetMagicAtack(pChara,54);
		} else if(rnd < 500){
			//---デスフォース
			crbatCPUThink_SetMagicAtack(pChara,21);
		} else if(rnd < 750){
			//---コンフュージョン
			crbatCPUThink_SetMagicAtack(pChara,18);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 94){
		//---蟻地獄
		if(rnd < 750 && pChara->GetBattleFlag(0) == 0
			&& pChara->GetBattleFlag(1) == 0){
			//---流砂
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_RYUSA,10);
			pChara->SetBattleFlag(0,1);
		} else if(pChara->GetBattleFlag(0)){
			//---捕食
			pChara->SetBattleFlag(0,0);
			pChara->SetBattleFlag(1,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HOSHOKU);
		} else if(rnd < 350){
			//---砂嵐
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SUNAARASHI,60);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 95){
		//---ブルーリザード
		if(rnd < 150){
			//---激しく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else if(rnd < 350){
			//---斬りかかる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 96){
		//---ポイズンガス
		if(rnd < 333 && !pChara->GetTurnAtack()){
			//---ぽいずんぶれす
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_POISON,30);
		} else if(rnd < 333){
			//---スリーピング
			crbatCPUThink_SetMagicAtack(pChara,11);
		} else if(rnd < 500){
			//---ダークミスト
			crbatCPUThink_SetMagicAtack(pChara,11);
		} else if(rnd < 650){
			//---プロテクション
			crbatCPUThink_SetMagicAtack(pChara,13);
		} else if(rnd < 800){
			//---フォースシールド
			crbatCPUThink_SetMagicAtack(pChara,17);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 97){
		//---マインムーバ
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
	} else if(pChara->BattleInfo.Enemy.ActionType == 98){
		//---ゼビアリュウ
		if(rnd < 250){
			//---かみつく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else if(rnd < 566 && !pChara->GetTurnAtack()
			&& pChara->GetPersonalTurn() == 0){
			//---稲妻
			pChara->AddTurnAtack();
			pChara->AddPersonalTurn(2);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_IKADUCHI,70);
		} else if(rnd < 566){
			//---稲妻
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_IKADUCHI,30);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 99){
		//---クレイシヴ、建国宣言
		if(turn < 3){
			pChara->Command.Main = BAT_COMMAND_WAIT;
		} else {
			//---スーパーセル
			pChara->Command.Hit = 1;
			crbatCPUThink_SetMagicAtack(pChara,57);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 100){
		//---火炎竜
		if(pChara->GetBattleFlag(0) && pChara->Command.Main != BAT_COMMAND_WAIT){
			//---ライジングサン
			if(pChara->GetBtStatus() & BTST_CHINMOKU){
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO2,100);
			} else {
				crbatCPUThink_SetMagicAtack(pChara,45,-1,0,NULL,1);
			}
			pChara->SetBattleFlag(0,0);
			pChara->SetBattleFlag(1,1);
			pChara->AddPersonalTurn(5);
		} else if(pChara->GetBattleFlag(1)){
			//---ライジングサン直後
			if(pChara->GetBtStatus() & BTST_CHINMOKU){
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,30);
			} else {
				//---魔法が使える
				crbatCPUThink_SetMagicAtack(pChara,3);
			}
			pChara->SetBattleFlag(1,0);
		} else if((turn + 2) && !((turn + 2) % 6)){
			//---ためる
			pChara->SetBattleFlag(0,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TAMERU);
		} else if(rnd < 333 && !pChara->GetPersonalTurn()){
			//---炎
			pChara->AddPersonalTurn(3);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,90);
		} else if(rnd < 400){
			//---炎
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,45);
		} else if(rnd < 650 && (pChara->GetBtStatus() & BTST_MAHI)){
			//---炎
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,45);
		} else if(rnd < 650){
			//---かみつく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else if(rnd < 800 && 
			((pChara->GetBtStatus() & BTST_MAHI) || (pChara->GetBtStatus() & BTST_CHINMOKU))){
			//---炎
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HONO,65);
		} else if(rnd < 800){
			if(crbatCPU_UseInvalidity(pChara) > eiRnd(3)){
				//---インバリディティ
				crbatCPUThink_SetMagicAtack(pChara,25);
			} else {
				//---通常攻撃
				crbatCPUThink_SetAtack(pChara);
			}
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 101){
		//---クロシジミ
		if(rnd < 250){
			//---水鉄砲
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_MIZUDEPPOU,70);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 102){
		//---お化け蚕
		if(rnd < 250 && !pChara->GetTurnAtack()){
			//---吹雪
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_FUBUKI,60);
		} else if(rnd < 250){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_FUBUKI,25);
		} else if(rnd < 400){
			//---眠りの粉
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NEMURINOKONA,15);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 103){
		//---クルバ
		if(rnd < 350){
			//---噛みつく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 104){
		//---エターナル兵（戦士）
		if(rnd < 333){
			//---斬りかかる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 600){
			//---激しく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 105){
		//---エターナル兵（魔法使い）
		if(rnd < 200){
			//---パラライズ
			crbatCPUThink_SetMagicAtack(pChara,11);//,-1,0,NULL,1);
		} else if(rnd < 350 && !pChara->GetTurnAtack()){
			//---ウィンドオーヴ
			pChara->AddTurnAtack();
			if(!pChara->GetPersonalTurn()){
				pChara->AddPersonalTurn(2);
				crbatCPUThink_SetMagicAtack(pChara,55);
			} else {
				crbatCPUThink_SetMagicAtack(pChara,54);
			}
		} else if(rnd < 500){
			//---フレアウェイヴ
			crbatCPUThink_SetMagicAtack(pChara,43);
		} else if(rnd < 750){
			//---ストリームクロウ
			crbatCPUThink_SetMagicAtack(pChara,54);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 106){
		//---エターナル兵（特殊）
		if(rnd < 150){
			//---スリープブレス
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,20);
		} else if(rnd < 300){
			//---サイレントブレス
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SILENTBREATH,20);
		} else if(rnd < 500 && !pChara->GetTurnAtack()){
			//---パワーボム
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_POWERBOMB,50);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 107){
		//---エターナル兵（僧侶）
		if(rnd < 150){
			//---ライフウィンド
			crbatCPUThink_SetMagicAtack(pChara,5);
		} else if(rnd < 300){
			//---リカバリー２
			crbatCPUThink_SetMagicAtack(pChara,3);
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
	} else if(pChara->BattleInfo.Enemy.ActionType == 108){
		//---エド
		if(pChara->GetBattleFlag(0)){
			//---ためてたら、カスケードボム
			pChara->SetBattleFlag(0,0);
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KASCADEBOMB,160);
		} else if(rnd < 150){
			//---混乱光線
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KONRANKOUSEN,20);
		} else if(rnd < 400){
			//---レーザー光線
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_LAYZERBEAM,65);
		} else if(rnd < 550){
			//---入れ歯クラッシュ
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_IREBACRASH);
		} else if(rnd < 700){
			//---とかす
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOKASU);
		} else if(rnd < 900 && !pChara->GetPersonalTurn()){
			//---ためる
			pChara->AddPersonalTurn(2);
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KASCADEBOMB,85);
//			pChara->SetBattleFlag(0,1);
//			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TAMERU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 109){
		//---ラーフィア
		if(turn == 0){
			//---エクステンド
			crbatCPUThink_SetMagicAtack(pChara,
				22,-1,0,&pBtChara[BATTLECHARA_STARTENEMY + 1]);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_RARFIAATACK);
			pChara->Command.Target = (ei_u32)&pBtChara[1];//---ディザターゲット
			pBtChara[1].SetAbility(BTAB_S_BARRIER100,1);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 110){
		//---アズグレイ
		//---デスフォース
		if(turn == 0){
			crbatCPUThink_SetMagicAtack(pChara,21,-1,0,&pBtChara[2]);
		} else {
			crbatCPUThink_SetMagicAtack(pChara,21,-1,0,&pBtChara[0]);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 111){
		//---ハイプレッシャー
		if(rnd < 200){
			//---突風
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOPPU,65);
		} else if(rnd < 400){
			//---ウィンドオーブ
			crbatCPUThink_SetMagicAtack(pChara,55);
		} else if(rnd < 600){
			//---衝撃波
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SHOGEKIHA);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 112){
		//---ゴーストツリー
		if(rnd < 333){
			//---吸血
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KYUKETSU);
		} else if(rnd < 450){
			//---インフルエンス
			crbatCPUThink_SetMagicAtack(pChara,20);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 113){
		//---黒双葉
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
			//---ダイヤブレス
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,62);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 114){
		//---ウォッチャー
		if(rnd < 250){
			//---火炎放射
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAENHOUSHA,80);
		} else if(rnd < 500 && !pChara->GetTurnAtack()){
			//---パワーボム
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_POWERBOMB,96);
		} else if(rnd < 700 && !pChara->GetTurnAtack()){
			//---突風
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOPPU,80);
		} else if(rnd < 700){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAENHOUSHA,60);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 115){
		//---メタルハンド
		if(rnd < 450){
			//---殴る
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGURU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 116){
		//---センサーＲ
		if(rnd < 250){
			//---催眠ガス
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,30);
		} else if(rnd < 500){
			//---ポイズンガス
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_POISON,50);
		} else if(rnd < 750){
			//---サイレントガス
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SILENTBREATH,30);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 117){
		//---センサーＧ
		if(rnd < 200){
			//---パワーブースト
			crbatCPUThink_SetMagicAtack(pChara,19);
		} else if(rnd < 400){
			//---プロテクション
			crbatCPUThink_SetMagicAtack(pChara,13);
		} else if(rnd < 600){
			//---リカバリー２
			crbatCPUThink_SetMagicAtack(pChara,3);
		} else if(rnd < 800){
			//---ディストーション
			crbatCPUThink_SetMagicAtack(pChara,12);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 118){
		//---センサーＢ
		if(rnd < 333 && !pChara->GetTurnAtack()){
			//---セルフリーズ
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,49);
		} else if(rnd < 333){
			crbatCPUThink_SetMagicAtack(pChara,48);
		} else if(rnd < 700 && !pChara->GetTurnAtack()){
			//---グラスシード
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,61);
		} else if(rnd < 700){
			crbatCPUThink_SetMagicAtack(pChara,60);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	}

	return crbatCPUThink4(pChara,turn,rnd);
}
