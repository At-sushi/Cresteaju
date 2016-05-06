//---吸血
CRBATENEMYABILITY_API int crbatEnemy_Kyuketsu(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int ability)
{
	//---InfoWindowを作る
	pWin->SetType(CRWIN_TYPE_NORMAL);
	if(ability == BAT_ECOM_KYUKETSU){
		crbatBWCreate(pWin,
			"吸血",BW_TOP | BW_CENTER);
	} else if(ability == BAT_ECOM_TABERU){
		crbatBWCreate(pWin,
			"食べる",BW_TOP | BW_CENTER);
	} else if(ability == BAT_ECOM_KYUKETUKEN){
		crbatBWCreate(pWin,
			"ドレインスラッシュ",BW_TOP | BW_CENTER);
	}

	//---衝突補正
	int range = (pChara->Command.Range & 0xffff0000) >> 16;
	if(!(9 <= range && range <= 15)){
		crbatGetTargetChara(pChara,pChara->GetTarget(),
			pChara->Command.Range,&pDamageInfo->pList[0],1);
	}
	if(pDamageInfo->pList[0] != NULL){
		//---衝突補正でターゲットが変わったときのための
		//---キャラクターアングル再設定
		pDamageInfo->pList[0]->SetAngle(
			ANGLE(180) + pChara->GetCharaAngle(pDamageInfo->pList[0])
			);
	}

	crbatSetDamageMode(pDamageInfo,DAMAGEMODE_SUB);

	//---攻撃値、防御値、計算方法、属性
	//---ダメージ計算
	int EnableCounter = 1,weapon = pChara->GetWeapon(pChara->Command.Sub[0]);
	if(weapon){
		//---間接攻撃だったらカウンター無し
		if(critemGetItemClass(weapon)->GetAtackKind() == 1){
			EnableCounter = 0;
		}
	} else if(!pChara->IsFriend()){
		if(pChara->BattleInfo.Enemy.AtackType == 1){
			//---敵間接攻撃
			EnableCounter = 0;
		}
	}

	crbatCalcDamage(
		pDamageInfo,pChara,
		SRC_WEAPON,1000,
		DST_DEFENSE,1000,
		CALCMODE_ADD,500,
		100,//---分散（１／１０００単位）
		weapon ? critemGetItemClass(weapon)->GetElement() : ELEMENT_PHYSICS,//---武器属性
		PROBMODE_REAL,pChara->GetBtHitProb(pChara->Command.Sub[0]),//---武器命中回避率、命中率
		DEFENSEMODE_REAL
		);

	//---アニメーション
	crbatDoAnime_Weapon(pChara,pDamageInfo,0);

	pDamageInfo->Damage[1] = pDamageInfo->Damage[0];
	pDamageInfo->pList[1] = pChara;
	pDamageInfo->pList[2] = NULL;
	pDamageInfo->DamageMode[1] = DAMAGEMODE_ADD;

	//---ダメージ表示
	crbatShowDamage(pDamageInfo);
	//---ダメージ結果加算
	crbatResultDamage(pDamageInfo);
	//---ダメージ結果表示
	crbatShowResult();

	//---カウンター
	crbatDoAction_CounterAtack(pDamageInfo,pChara,pWin,EnableCounter);

	return 1;
}

CRBATANIME_API void crbatDoAnime_MagicGroundCross(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,int mode);

//---殴る
CRBATENEMYABILITY_API int crbatEnemy_ExtendAtack(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int ability)
{
	int rate = 1250,DstDefense = DST_DEFENSE,def_rate = 1000;
	//---InfoWindowを作る
	pWin->SetType(CRWIN_TYPE_NORMAL);

	switch(ability){
	case BAT_ECOM_NAGURU:
		rate = 1200;
		crbatBWCreate(pWin,
			"殴る",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_KAMITUKU:
		rate = 1150;
		crbatBWCreate(pWin,
			"噛みつく",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_KIRIKAKARU:
		rate = 1150;
		crbatBWCreate(pWin,
			"斬りかかる",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_PIERUZAN:
		rate = 1250;
		crbatBWCreate(pWin,
			"ピエール斬",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_JURIASGIRI:
		rate = 1000;
		crbatBWCreate(pWin,
			"ジュリアスの舞い",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_TOSSHIN:
		rate = 1500;
		crbatBWCreate(pWin,
			"突進",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_HAGESHIKU:
		rate = 1300;
		crbatBWCreate(pWin,
			"激しく斬りつける",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_KAITENATACK:
		rate = 1000;
		crbatBWCreate(pWin,
			"回転アタック",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_NAGITAOSU:
		rate = 1000;
		crbatBWCreate(pWin,
			"なぎ倒す",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_TOTUGEKI:
		rate = 1200;
		crbatBWCreate(pWin,
			"突撃",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_SHOGEKIHA:
		rate = 1000;
		crbatBWCreate(pWin,
			"衝撃波",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_CHOUONPA:
		rate = 1000;
		crbatBWCreate(pWin,
			"超音波",BW_TOP | BW_CENTER);
//		DstDefense = DST_NONE;
		def_rate = 0;
		break;
	case BAT_ECOM_ENGETUZAN:
		rate = 1000;
		crbatBWCreate(pWin,
			"円月斬",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_SEKKINATACK:
		rate = 2000;
		crbatBWCreate(pWin,
			"接近突撃",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_IREBACRASH:
		rate = 1300;
		crbatBWCreate(pWin,
			"入れ歯クラッシュ",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_HOSHOKU:
		rate = 1600;
		crbatBWCreate(pWin,
			"捕食",BW_TOP | BW_CENTER);
	case BAT_ECOM_SAN:
		rate = 1100;
		crbatBWCreate(pWin,
			"酸",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_DANDYSPRASHER:
		rate = 1100;
		crbatBWCreate(pWin,
			"ダンディスプラッシャー",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_ONSOKU:
		rate = 1500;
		crbatBWCreate(pWin,
			"音速斬り",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_SILENTBANISHA:
		rate = 1500;
		crbatBWCreate(pWin,
			"サイレント・バニッシャー",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_SETUDAN:
		rate = 1500;
		crbatBWCreate(pWin,
			"切断",BW_TOP | BW_CENTER);
		break;

	case BAT_ECOM_ROUOU:
		rate = 1700;
		crbatBWCreate(pWin,
			"埴輪楼桜剣",BW_TOP | BW_CENTER);
		break;

	case BAT_ECOM_CR_LINEKOGEKI:
		rate = 1400;
		crbatBWCreate(pWin,
			"プレートウェイヴ",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_CR_SINGLEKOGEKI:
		rate = 1800;
		crbatBWCreate(pWin,
			"切り裂く",BW_TOP | BW_CENTER);
		break;


	case BAT_ECOM_RARFIAATACK:
		rate = 1000;
		break;
	}

	//---衝突補正
	int range = (pChara->Command.Range & 0xffff0000) >> 16;
	if(!(9 <= range && range <= 15)){
		if(ability != BAT_ECOM_RARFIAATACK){
			crbatGetTargetChara(pChara,pChara->GetTarget(),
				pChara->Command.Range,&pDamageInfo->pList[0],1);
		}
	}

	if(pDamageInfo->pList[0] != NULL){
		//---衝突補正でターゲットが変わったときのための
		//---キャラクターアングル再設定
		pDamageInfo->pList[0]->SetAngle(
			ANGLE(180) + pChara->GetCharaAngle(pDamageInfo->pList[0])
			);
	}

	crbatSetDamageMode(pDamageInfo,DAMAGEMODE_SUB);

	//---攻撃値、防御値、計算方法、属性
	//---ダメージ計算
	int EnableCounter = 1,weapon = pChara->GetWeapon(pChara->Command.Sub[0]);
	if(weapon){
		//---間接攻撃だったらカウンター無し
		if(critemGetItemClass(weapon)->GetAtackKind() == 1){
			EnableCounter = 0;
		}
	} else if(!pChara->IsFriend()){
		if(pChara->BattleInfo.Enemy.AtackType == 1){
			//---敵間接攻撃
			EnableCounter = 0;
		}
	}

	int prob = pChara->GetBtHitProb(pChara->Command.Sub[0]),
		mode = PROBMODE_REAL;

/*	if(ability == BAT_ECOM_CR_LINEKOGEKI){
		prob = -1;
		mode = PROBMODE_100;
	}
*/
	crbatCalcDamage(
		pDamageInfo,pChara,
		SRC_WEAPON,rate,
		DstDefense,def_rate,
		CALCMODE_ADD,500,
		100,//---分散（１／１０００単位）
		weapon ? critemGetItemClass(weapon)->GetElement() : ELEMENT_PHYSICS,//---武器属性
		mode,prob,//---武器命中回避率、命中率
		DEFENSEMODE_REAL
		);

	//---アニメーション
	if(ability == BAT_ECOM_CR_LINEKOGEKI){
		crbatDoAnime_MagicGroundCross(pChara,pDamageInfo,0);
	} else {
		crbatDoAnime_Weapon(pChara,pDamageInfo,0);
	}

	//---ダメージ表示
	crbatShowDamage(pDamageInfo);
	//---ダメージ結果加算
	crbatResultDamage(pDamageInfo);

	if(ability == BAT_ECOM_SAN){
		if(pDamageInfo->Damage[0]){
			//---防御力減らす
			pDamageInfo->pList[0]->AddBtStatus(BTST_ZERO);
		}
	}

	//---ダメージ結果表示
	crbatShowResult();

	//---カウンター
	if(ability != BAT_ECOM_CR_LINEKOGEKI){
		crbatDoAction_CounterAtack(pDamageInfo,pChara,pWin,EnableCounter);
	}

	return 1;
}

//---ＬＰ減少系
CRBATENEMYABILITY_API int crbatEnemy_LPRateDamage(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int ability)
{
	int rate = 1250;
	int prob = PROBMODE_REAL;
	//---InfoWindowを作る
	pWin->SetType(CRWIN_TYPE_NORMAL);

	switch(ability){
	case BAT_ECOM_TOKASU:
		rate = 500;
		crbatBWCreate(pWin,
			"とかす",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_HANBUSSHITU:
	case BAT_ECOM_HANBUSSHITU_ZENTAI:
		rate = 950;
		crbatBWCreate(pWin,
			"反物質",BW_TOP | BW_CENTER);
		prob = PROBMODE_100;
		break;
	case BAT_ECOM_SHINSHOKU:
		rate = 500;
		crbatBWCreate(pWin,
			"浸食",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_820:
		rate = 820;
		crbatBWCreate(pWin,
			"疾走・８２０",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_DIVIDING:
		rate = 500;
		crbatBWCreate(pWin,
			"ディバイディング",BW_TOP | BW_CENTER);
		break;
	}

	//---衝突補正
	int range = (pChara->Command.Range & 0xffff0000) >> 16;
	if(!(9 <= range && range <= 15)){
		crbatGetTargetChara(pChara,pChara->GetTarget(),
			pChara->Command.Range,&pDamageInfo->pList[0],1);
	}

	if(pDamageInfo->pList[0] != NULL){
		//---衝突補正でターゲットが変わったときのための
		//---キャラクターアングル再設定
		pDamageInfo->pList[0]->SetAngle(
			ANGLE(180) + pChara->GetCharaAngle(pDamageInfo->pList[0])
			);
	}

	crbatSetDamageMode(pDamageInfo,DAMAGEMODE_SUB);

	//---攻撃値、防御値、計算方法、属性
	//---ダメージ計算
	int EnableCounter = 1,weapon = pChara->GetWeapon(pChara->Command.Sub[0]);
	if(weapon){
		//---間接攻撃だったらカウンター無し
		if(critemGetItemClass(weapon)->GetAtackKind() == 1){
			EnableCounter = 0;
		}
	} else if(!pChara->IsFriend()){
		if(pChara->BattleInfo.Enemy.AtackType == 1){
			//---敵間接攻撃
			EnableCounter = 0;
		}
	}

	crbatCalcDamage(
		pDamageInfo,pChara,
		DST_LP,rate,
		DST_NONE,1000,
		CALCMODE_ADD,1000,
		0,//---分散（１／１０００単位）
		ELEMENT_PHYSICS,//---武器属性
		prob,pChara->GetBtHitProb(pChara->Command.Sub[0]),//---武器命中回避率、命中率
		DEFENSEMODE_REAL
		);

	//---アニメーション
	crbatDoAnime_Weapon(pChara,pDamageInfo,0);

	//---ダメージ表示
	crbatShowDamage(pDamageInfo);
	//---ダメージ結果加算
	crbatResultDamage(pDamageInfo);
	//---ダメージ結果表示
	crbatShowResult();

	//---カウンター
	crbatDoAction_CounterAtack(pDamageInfo,pChara,pWin,EnableCounter);

	return 1;
}

//---即死系攻撃
CRBATENEMYABILITY_API int crbatEnemy_DeathAtack(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int ability)
{
	int rate = 1250;
	//---InfoWindowを作る
	pWin->SetType(CRWIN_TYPE_NORMAL);

	switch(ability){
	case BAT_ECOM_CHISSOKU_1_10:
		rate = 100;
		crbatBWCreate(pWin,
			"窒息",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_CHISSOKU_1_5:
		rate = 200;
		crbatBWCreate(pWin,
			"窒息",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_CHISSOKU_1_2:
		rate = 500;
		crbatBWCreate(pWin,
			"窒息",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_CHISSOKU_2_3:
		rate = 666;
		crbatBWCreate(pWin,
			"窒息",BW_TOP | BW_CENTER);
		break;
	}

	//---衝突補正
	int range = (pChara->Command.Range & 0xffff0000) >> 16;
	if(!(9 <= range && range <= 15)){
		crbatGetTargetChara(pChara,pChara->GetTarget(),
			pChara->Command.Range,&pDamageInfo->pList[0],1);
	}

	if(pDamageInfo->pList[0] != NULL){
		//---衝突補正でターゲットが変わったときのための
		//---キャラクターアングル再設定
		pDamageInfo->pList[0]->SetAngle(
			ANGLE(180) + pChara->GetCharaAngle(pDamageInfo->pList[0])
			);
	}

	crbatSetDamageMode(pDamageInfo,DAMAGEMODE_SUB);

	//---攻撃値、防御値、計算方法、属性
	//---ダメージ計算
	int EnableCounter = 1,weapon = pChara->GetWeapon(pChara->Command.Sub[0]);
	if(weapon){
		//---間接攻撃だったらカウンター無し
		if(critemGetItemClass(weapon)->GetAtackKind() == 1){
			EnableCounter = 0;
		}
	} else if(!pChara->IsFriend()){
		if(pChara->BattleInfo.Enemy.AtackType == 1){
			//---敵間接攻撃
			EnableCounter = 0;
		}
	}

	crbatCalcDamage(
		pDamageInfo,pChara,
		DST_LP,1000,
		DST_NONE,1000,
		CALCMODE_ADD,1000,
		0,//---分散（１／１０００単位）
		ELEMENT_PHYSICS,//---武器属性
		PROBMODE_REAL,rate,//---武器命中回避率、命中率
		DEFENSEMODE_REAL
		);

	//---アニメーション
	crbatDoAnime_Weapon(pChara,pDamageInfo,0);

	//---ダメージ表示
	crbatShowDamage(pDamageInfo);
	//---ダメージ結果加算
	crbatResultDamage(pDamageInfo);
	//---ダメージ結果表示
	crbatShowResult();

	//---カウンター
	crbatDoAction_CounterAtack(pDamageInfo,pChara,pWin,EnableCounter);

	return 1;
}

