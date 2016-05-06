//---ダメージモードをセット
CRBATMAIN_API void crbatSetDamageMode(CR_BATTLE_DAMAGEINFO *pDamageInfo,int damage_mode)
{
	int count;
	CrBattleCharacter **ppList = &pDamageInfo->pList[0];

	for(count = 0; *ppList != NULL ; count ++,ppList ++){
//	for(count = 0,ppList = &pDamageInfo->pList[0];
//		*ppList != NULL; count ++,ppList ++){
		pDamageInfo->DamageMode[count] = damage_mode;

//		sprintf(s,"%d,%d",pDamageInfo->DamageMode[count],damage_mode);
//		eiMsgBox(s);
	}
}

static int BattleTurn;

CRBATMAIN_API void crbatSetTurn(int turn)
{
	BattleTurn = turn;
}

CRBATMAIN_API int crbatGetTurn(void)
{
	return BattleTurn;
}

//---ダメージ結果を影響させる
CRBATMAIN_API int crbatResultDamage(CR_BATTLE_DAMAGEINFO *pDamageInfo)
{
	int count,damage_mode;
	CrBattleCharacter **ppList;
	CrBattleCharacter *EnemyList[32];

	memset(&EnemyList[0],0,sizeof(EnemyList));

	for(count = 0,ppList = &pDamageInfo->pList[0];
			*ppList ; count ++,ppList ++){
		damage_mode = pDamageInfo->DamageMode[count];
		if(damage_mode == 0){
			damage_mode = pDamageInfo->DamageMode[0];
		}
		if(damage_mode == DAMAGEMODE_ADD){
			//---回復
			ppList[0]->ResultLP(pDamageInfo->Damage[count]);
			//--ルーインダメージ減少
			ppList[0]->AddRuinDamage(-pDamageInfo->Damage[count]);
		} else if(damage_mode == DAMAGEMODE_SUB){
			int PreviousLP = ppList[0]->GetLP();
			//---ダメージ
			//---バトルヒストリー
			ppList[0]->HistoryAddReceiveDamage(pDamageInfo->Damage[count]);
			if(ppList[0]->ResultLP(-pDamageInfo->Damage[count]) <= 0){
				//---ＬＰ＜＝なったら
				if(ppList[0]->IsFriend() == 0){
					//---敵なら
					ppList[0]->AddEnemyExperience();
					ppList[0]->AddEnemyMoney();

					//---アイテムを落とすなら
					if(ppList[0]->BattleInfo.Enemy.Item){
						BattleItem = ppList[0]->BattleInfo.Enemy.Item;
						BattleItemProb = ppList[0]->BattleInfo.Enemy.ItemProbability;
					}
				}
				if(PreviousLP >= 1 && ppList[0]->GetLP() <= 0){
					//---気絶回数
					ppList[0]->HistoryAddDeathCount();
				}
			} else {
				//---眠り、混乱回復（ダメージがある場合）
				if(pDamageInfo->Damage[count] > 0){
					if(ppList[0]->GetBtStatus() & BTST_NEMURI){
						if(eiRnd(1000) < ppList[0]->GetStatusRecoveryRate(400))
						ppList[0]->ClearBtStatus(BTST_NEMURI);
					}
					if(ppList[0]->GetBtStatus() & BTST_KONRAN){
						if(eiRnd(1000) < ppList[0]->GetStatusRecoveryRate(333))
						ppList[0]->ClearBtStatus(BTST_KONRAN);
					}
				}
			}
		} else if(damage_mode == DAMAGEMODE_ADDMC){
			//---ＭＣ回復
			ppList[0]->AddMC(pDamageInfo->Damage[count]);
		} else if(damage_mode == DAMAGEMODE_SUBMC){
			//---ＭＣ減少
			ppList[0]->AddMC(-pDamageInfo->Damage[count]);
		} else if(damage_mode == DAMAGEMODE_STATUS){
			//---ステータス
		}

		if(ppList[0]->BattleInfo.Enemy.Graphic == 223){
			//---クレイシヴ
			if(ppList[0]->GetBattleFlag(0) == 0 && crbatGetTurn() >= 1
				&& ppList[0]->GetMaxLP() - ppList[0]->GetLP() >= 3200){
				//---倒れる
				ppList[0]->Command.Main = BAT_COMMAND_WAIT;
				ppList[0]->SetBattleFlag(0,1);
				ppList[0]->SetBattleFlag(1,3);
				ppList[0]->SetCell(&BattleEnemyCell[1 * BATTLE_ENEMYPATTERNSIZE]);
			}
		}
	}

	//---パターン再設定
	crbatSetupCharaPattern();
	crbatClearDrawingList();
	crbatAddDrawingListAll();

	return 1;
}

//---計算に使われる値を探し出す
CRBATMAIN_API int crbatGetCalcData(CrBattleCharacter *pSrcChara,CrBattleCharacter *pDstChara,
					int calc,int rate)
{
	int data = 0;

	switch(calc){
	case SRC_NONE:
		data = 0;
		break;
	case SRC_LEVEL:
		data = pSrcChara->GetLevel();
		break;
	case SRC_LP:
		data = pSrcChara->GetLP();
		break;
	case SRC_MAXLP:
		data = pSrcChara->GetMaxLP();
		break;
	case SRC_MC:
		data = pSrcChara->GetMC();
		break;
	case SRC_MAXMC:
		data = pSrcChara->GetMaxMC();
		break;
	case SRC_WEAPON:
		data = pSrcChara->GetBtAtack(pSrcChara->Command.Sub[0]);
		break;
	case SRC_DEFENSE:
		data = pSrcChara->GetBtDefense();
		break;
	case SRC_POWER:
		data = pSrcChara->GetBtPower();
		break;
	case SRC_AGILITY:
		data = pSrcChara->GetBtAgility();
		break;
	case SRC_VITALITY:
		data = pSrcChara->GetBtVitality();
		break;
	case SRC_SOUL:
		data = pSrcChara->GetBtSoul();
		break;
	case SRC_MAGIC:
		data = pSrcChara->GetBtMagic();
		break;
	case SRC_MAGDEF:
		data = pSrcChara->GetBtMagicDefense();
		break;
	case SRC_SUB6:
		data = pSrcChara->GetCommandSub(6);
		break;
	case SRC_SUB7:
		data = pSrcChara->GetCommandSub(7);
		break;
	case SRC_DIRECT:
	case DST_DIRECT:
		data = rate;
		break;

	case DST_NONE:
		data = 0;
		break;
	case DST_LEVEL:
		data = pDstChara->GetLevel();
		break;
	case DST_LP:
		data = pDstChara->GetLP();
		break;
	case DST_MAXLP:
		data = pDstChara->GetMaxLP();
		break;
	case DST_MC:
		data = pDstChara->GetMC();
		break;
	case DST_MAXMC:
		data = pDstChara->GetMaxMC();
		break;
	case DST_WEAPON:
		data = pDstChara->GetBtAtack(pSrcChara->Command.Sub[0]);
		break;
	case DST_DEFENSE:
		data = pDstChara->GetBtDefense();
		break;
	case DST_POWER:
		data = pDstChara->GetBtPower();
		break;
	case DST_AGILITY:
		data = pDstChara->GetBtAgility();
		break;
	case DST_VITALITY:
		data = pDstChara->GetBtVitality();
		break;
	case DST_SOUL:
		data = pDstChara->GetBtSoul();
		break;
	case DST_MAGIC:
		data = pDstChara->GetBtMagic();
		break;
	case DST_MAGDEF:
		data = pDstChara->GetBtMagicDefense();
/*		char s[80];
		sprintf(s,"%d",data);
		eiMsgBox(s);*/
		break;
	case DST_SUB6:
		data = pDstChara->GetCommandSub(6);
		break;
	case DST_SUB7:
		data = pDstChara->GetCommandSub(7);
		break;

	default:
		data = 0;
		break;
	}

	return data;
}

//---ステータス変化系の防御判定
CRBATMAIN_API int crbatCalcStatus(CrBattleCharacter *pChara,int status)
{
	if((status & BTST_DOKU) && pChara->Ability(BTAB_P_DOKU)){
		//---対毒
		return 0;
	}
	if((status & BTST_NEMURI) && pChara->Ability(BTAB_P_NEMURI)){
		//---対眠り
		return 0;
	}
	if((status & BTST_KURAYAMI) && pChara->Ability(BTAB_P_KURAYAMI)){
		//---対暗闇
		return 0;
	}
	if((status & BTST_CHINMOKU) && pChara->Ability(BTAB_P_CHINMOKU)){
		//---対沈黙
		return 0;
	}
	if((status & BTST_KONRAN) && pChara->Ability(BTAB_P_KONRAN)){
		//---対混乱
		return 0;
	}
	if(((status & BTST_JAKUKA) || (status & BTST_ZERO)) && pChara->Ability(BTAB_P_HENKA)){
		//---対弱化、対防御力低下
		return 0;
	}
	if((status & BTST_MAHI) && pChara->Ability(BTAB_P_MAHI)){
		//---対麻痺
		return 0;
	}
	if((status & BTST_SOKUSHI) && pChara->Ability(BTAB_P_SOKUSHI)){
		//---対即死
		return 0;
	}

	return 1;
}

//---ダメージを計算
CRBATMAIN_API int crbatCalcDamage(CR_BATTLE_DAMAGEINFO *pDamageInfo,
			CrBattleCharacter *pSrcChara,
			int src,int src_rate,int dst,int dst_rate,
			int calc_mode,int calc_rate,int diffusse,int element,
			int prob_mode,int proberb,int defense_mode)
{
	int src_value,dst_value,damage = 0,count,hit = 0,miss = 0;
	CrBattleCharacter **ppList = &pDamageInfo->pList[0];
/*
char s[100];
sprintf(s,"\ndamage src:%s\n",pSrcChara->GetName());
eiDebugWriteFile(s);
sprintf(s,"damage rate:%4d , %4d\n",src_rate,dst_rate);
eiDebugWriteFile(s);
*/
	for(count = 0; *ppList != NULL ; count ++,ppList ++){
		//---ミスカウンタリセット
		miss = 0;

		if(pDamageInfo->DamageRate[count] == 0){
			//---ディフォルトのダメージ
			pDamageInfo->DamageRate[count] = 1000;
		}

		src_value = crbatGetCalcData(pSrcChara,*ppList,src,src_rate);
		if(src != SRC_DIRECT)
			src_value = src_value * src_rate / 1000;
		dst_value = crbatGetCalcData(pSrcChara,*ppList,dst,dst_rate);
		if(dst != DST_DIRECT)
			dst_value = dst_value * dst_rate / 1000;

		hit = pSrcChara->Command.Hit;
		if(prob_mode == PROBMODE_100){
			hit = 1;
		}
/*
sprintf(s,"\t dst:%s\n",ppList[0]->GetName());
eiDebugWriteFile(s);
sprintf(s,"\t val:%4d , %4d\n",src_value,dst_value);
eiDebugWriteFile(s);
*/
		if(calc_mode == CALCMODE_ADD){
			damage = (src_value - dst_value) * calc_rate / 1000;
			damage = damage * pDamageInfo->DamageRate[count] / 1000;
		} else if(calc_mode == CALCMODE_MULTI){
			if(dst_value > 100)
				dst_value = 100;
			if(dst_value < 0)
				dst_value = 0;
			damage = (src_value * calc_rate / 100) * (100 - dst_value) / 1000;
			damage = damage * pDamageInfo->DamageRate[count] / 1000;
		} else if(calc_mode == CALCMODE_DIRECT){
			damage = src_value;
			damage = damage * pDamageInfo->DamageRate[count] / 1000;
		} else if(calc_mode == CALCMODE_PROB){
			damage = 1;
		}

		//---ダメージ幅
		if(damage < 0)
			damage = 0;
		if(damage == 0 && calc_mode != CALCMODE_PROB){
			//---防御力が高すぎたらミスか１だったら（確率計算モード以外）
			damage = eiRnd(2);
		}

		//---回復だったら気絶状態を考慮
		if(pDamageInfo->DamageMode[count] == DAMAGEMODE_ADD
			&& (*ppList)->GetLP() <= 0){
			damage /= 10;
		}

		//---属性計算
		if(calc_mode != CALCMODE_PROB){
			damage = (damage * (*ppList)->GetBtElement(element)) / 1000;
		}

		//---命中判定
		if(proberb == -1){
			//---確実命中
			hit = 1;
		}
/*
sprintf(s,"\t damage:%4d\n",damage);
eiDebugWriteFile(s);
*/
		//---カオスワード判定
		if(ppList[0]->GetKaosTurn()
			&& pDamageInfo->DamageMode[count] != DAMAGEMODE_ADD
			&& pDamageInfo->DamageMode[count] != DAMAGEMODE_ADDMC
			&& calc_mode != CALCMODE_PROB
			&& (ppList[0]->GetBtStatus() & BTST_KAOS)
			){
			//---カオスワード使用中
			int a;
			for(a = 0//---カオスブローチ持っていたら、ターン数－１
				;a < ppList[0]->GetKaosTurn() - (ppList[0]->Ability(BTAB_S_KAOS) ? 1 : 0)
				;a ++){
//				damage = damage * 2;
				damage += damage;
				if(damage > 99999)
					damage = 99999;
			}
		}

		if(defense_mode & DEFENSEMODE_BREATH){
			//---ブレス
			if((*ppList)->Ability(BTAB_P_BREATH0)){
				damage = 0;
			} else if((*ppList)->Ability(BTAB_P_BREATH12)){
				damage /= 2;
			} else if((*ppList)->Ability(BTAB_P_BREATH23)){
				damage = damage * 2 / 3;
			} else if((*ppList)->Ability(BTAB_P_BREATH45)){
				damage = damage * 4 / 5;
			}
		}

		if(!(proberb > eiRnd(1000)) && !hit/*必ず当たるフラッグ*/){
			//---外れたら
			if(pSrcChara->GetBtSubHitProb() > eiRnd(1000)){
				//---命中補正でもどーにもならなかったら
				if(!(proberb > eiRnd(1000))){
					//---ハズレ！
					damage = 0;
					miss = 1;
				}
			} else {
				//---ハズレ！
				damage = 0;
				miss = 1;
			}
		}
		//---通常回避判定
		if(/*damage &&*/ calc_mode != CALCMODE_PROB && !hit/*ヒットフラッグが０なら*/){
			int avoid_prob = 0;
			if(prob_mode == PROBMODE_REAL){
				//---物理的回避
				avoid_prob = (*ppList)->GetBtAvoidProb();
			} else if(prob_mode == PROBMODE_MAGIC){
				//---魔法的回避
				avoid_prob = (*ppList)->GetBtMagicAvoidProb();
			} else {
				//---その他
				avoid_prob = 0;
			}
			if(avoid_prob > eiRnd(1000)){
				//---回避成功！
				damage = 0;
				miss = 1;
			}
		} else if(calc_mode == CALCMODE_PROB){
			//---変化系攻撃
			if(hit){
				damage = 1;
			} else {
				//---確率判定
				int dlevel = src_value - dst_value;
				int prob;

				if(pSrcChara->IsFriend() && dlevel < 0)
					prob = dlevel * 30 + 700;
				else
					prob = dlevel * 50 + 700;


				if(prob > 1000)
					prob = 1000;
				if(prob < 100)
					prob = 100;
				//---＋補助魔法
				if(pSrcChara->Ability(BTAB_S_HOJOMAHO)){
					prob = prob + ((1000 - prob) / 2);
				}

				if(prob_mode == PROBMODE_MAGIC){
					if(ppList[0]->GetBtStatus() & BTST_FSHIELD){
						//---フォースシールドで、魔法確率判定の場合
						prob = prob -
							(prob * 50 *
							ppList[0]->GetBtStatusContinue(BTST_FSHIELD) / ppList[0]->GetBtStatusContinueMax(BTST_FSHIELD)
							) / 100;
					}
				}

				if(damage){
					if(eiRnd(1000) < ppList[0]->GetStatusChangeRate(prob)){
						damage = 1;
					} else {
						damage = 0;
						miss = 1;
					}
				}
/*				char s[80];
				sprintf(s,"%d",ppList[0]->GetStatusChangeRate(prob));
				eiMsgBox(s);*/
				//---アビリティを考慮
//				damage &= crbatCalcStatus((*ppList),element);

				if(!damage){
					miss = 1;
				}
			}
		}

		if(damage != 0 && calc_mode != CALCMODE_PROB){
			//---分散
			if(damage > 3 && diffusse && (damage * diffusse) / 1000 <= 0){
				//---分散が小さくなりすぎたら
				damage = damage + eiRnd(3) - 1;
			} else {
				damage = damage + (eiRnd(damage * diffusse / 1000) - (damage * diffusse / 2000));
			}
/*			if(ppList[0]->Ability(BTAB_P_BUTURIKOUGEKI) && element == ELEMENT_PHYSICS){
				//---物理攻撃無効
				damage = 0;
			}*/
		}


		if(pDamageInfo->DamageMode[count] == DAMAGEMODE_ADD
		|| pDamageInfo->DamageMode[count] == DAMAGEMODE_ADDMC){

			if(ppList[0]->Command.Main == BAT_COMMAND_DEFENSE
				&& ppList[0]->Command.Sub[0] == BAT_SUBCOM_DEFENSE){
				//---回復量増量２割り増し
				damage += (damage * 2 / 10);
			}
		}

		//---防御、魔法防御
		if(pDamageInfo->DamageMode[count] != DAMAGEMODE_ADD/*回復モード以外*/
		&& pDamageInfo->DamageMode[count] != DAMAGEMODE_ADDMC
		&& (ppList[0]->Command.Main == BAT_COMMAND_DEFENSE
			|| ppList[0]->GetAutoGard())){

			if((defense_mode & DEFENSEMODE_MAGIC)
				&& ppList[0]->Command.Sub[0] == BAT_SUBCOM_MAGICDEFENSE
				&& ppList[0]->Command.Main == BAT_COMMAND_DEFENSE){

				//---魔法防御可能なら
				if(calc_mode != CALCMODE_PROB){
					damage /= 4;
				} else if(damage && !hit){
					//---確率計算で魔法防御可能なら１／２の確率で回避
					damage = eiRnd(2);
					if(!damage){
						miss = 1;
					}
				}
			} else if(defense_mode & DEFENSEMODE_REAL){
				if(ppList[0]->Command.Sub[0] == BAT_SUBCOM_DEFENSE
					|| ppList[0]->GetAutoGard()){
					//---物理防御可能なら
					damage /= 2;
				} else if(ppList[0]->Command.Sub[0] == BAT_SUBCOM_MOVE){
					//---移動中なら２／３
					damage = damage * 2 / 3;
				}
			}
		}

		if((defense_mode == DEFENSEMODE_REAL)
			&& pDamageInfo->DamageMode[count] != DAMAGEMODE_ADD
			&& pDamageInfo->DamageMode[count] != DAMAGEMODE_ADDMC){
			//---物理防御だけ可能＆回復でないなら、プロテクション考慮
			int status = BTST_PROTECT;

			if(ppList[0]->GetBtStatus() & status){
				damage = damage - (damage * ppList[0]->GetBtStatusContinue(status) / ppList[0]->GetBtStatusContinueMax(status)) / 2;
			}
		}
		if((defense_mode & DEFENSEMODE_MAGIC)
			&& (pDamageInfo->DamageMode[count] != DAMAGEMODE_ADD
				&& pDamageInfo->DamageMode[count] != DAMAGEMODE_ADDMC
			&& calc_mode != CALCMODE_PROB)){
			//---魔法攻撃＆回復魔法でない＆確率モードでないなら、マジックシールド考慮
			int status = BTST_FSHIELD;

			if(ppList[0]->GetBtStatus() & status){
				damage = damage - (damage * ppList[0]->GetBtStatusContinue(status) / ppList[0]->GetBtStatusContinueMax(status)) / 2;
			}
		}

		//---バリア考慮
		if(pDamageInfo->DamageMode[count] != DAMAGEMODE_ADD
			&& pDamageInfo->DamageMode[count] != DAMAGEMODE_ADDMC
			&& calc_mode != CALCMODE_PROB){
			if(ppList[0]->Ability(BTAB_S_BARRIER5) && damage <= 5){
				damage = 0;
			}
			if(ppList[0]->Ability(BTAB_S_BARRIER10) && damage <= 10){
				damage = 0;
			}
			if(ppList[0]->Ability(BTAB_S_BARRIER25) && damage <= 25){
				damage = 0;
			}
			if(ppList[0]->Ability(BTAB_S_BARRIER50) && damage <= 50){
				damage = 0;
			}
			if(ppList[0]->Ability(BTAB_S_BARRIER100) && damage <= 100){
				damage = 0;
			}
			if(ppList[0]->Ability(BTAB_S_BARRIER200) && damage <= 200){
				damage = 0;
			}
			if(ppList[0]->Ability(BTAB_S_BARRIER2000) && damage <= 2000){
				damage = 0;
			}
		}

		if(prob_mode == PROBMODE_MAGIC){
			//---リフレクション判定
			if(ppList[0]->GetBtStatus() & BTST_REFLECT){
				damage = 0;
			}
		}

		//---ワールド判定
		if(ppList[0]->GetBtStatus() & BTST_WORLD){
			if(calc_mode == CALCMODE_PROB){
				if(!(element & BTST_PULS)){
					//---プラス変化でなければワールド有効
					damage = 0;
				}
			} else if(pDamageInfo->DamageMode[count] != DAMAGEMODE_ADD
					&& pDamageInfo->DamageMode[count] != DAMAGEMODE_ADDMC){
				//---ダメージモードが加算でなければ
				damage = 0;
			}
		}
		//---安眠君
		if((ppList[0]->GetBtStatus() & BTST_NEMURI) && ppList[0]->Ability(BTAB_S_ANMIN)){
			if(calc_mode == CALCMODE_PROB){
			} else if(pDamageInfo->DamageMode[count] != DAMAGEMODE_ADD
					&& pDamageInfo->DamageMode[count] != DAMAGEMODE_ADDMC){
				//---ダメージモードが加算でなければ
				damage = 0;
			}
		}

		//---ダメージ最大値
		if(damage > 99999)
			damage = 99999;

		if(calc_mode == CALCMODE_PROB && damage){
			//---確率計算で、ミスの場合だけダメージ表示
			pDamageInfo->DontShowThisDamage[count] = 1;
		}

		//---ダメージを入れる
		if(miss){
			//---ミスしてたら
			damage = 0;
			pDamageInfo->Miss[count] = 1;
		}
		pDamageInfo->Damage[count] = damage;
		if(pDamageInfo->DamageMode[count] == DAMAGEMODE_SUB){
			//---バトルヒストリー
			pSrcChara->HistoryAddGiveDamage(damage);
		}
		if(miss && calc_mode != CALCMODE_PROB){
			//---バトルヒストリー
//			pSrcChara->HistoryAddGiveMissCount(1);
			ppList[0]->HistoryAddReceiveMissCount(1);
		}
	}

/*	char s[80];
	sprintf(s,"src:(%d,%d)  , dst:(%d,%d)  , calc_rate:%d  , %d\n",
		src_value,src_rate,dst_value,dst_rate,
		calc_rate,damage);
	eiDebugWriteFile(s);*/

	return damage;
}
