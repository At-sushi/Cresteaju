
//---データコピー
CRBATINIT_API int crbatEndBattle_CopyCharaData(CR_BATTLEINFO *pInfo)
{
	int a;
	CrCharacter *pChara;

	//---データコピー
	for(a = 0;a < MEMBER_MAX;a ++){
		pChara = crcharaGetPartyMember(a);
		if(pChara != NULL){
			//---いれば
			memcpy(&pChara->CharaInfo,&pBtChara[a].CharaInfo,sizeof(pBtChara[a].CharaInfo));

			//---気絶していたらＬＰを１にセット
			if(pChara->GetLP() <= 0){
				pChara->SetLP(1);
			}
			//---ＭＣ回復リセット
			pChara->SetLastUsingMagic();
			pChara->SetDisableMCCount(-1);
		}
	}

	return 1;
}

//---キャラクターパターンを読み込み
CRBATINIT_API int crbatReadCharaPattern(void)
{
	int a,c = 1;
	char s[80];
	CrCharacter *pChara;

	//---ステータスアイコン読み込み
	c &= eiCellReadPattern(
		&BattleStatusCell[0],
		CR_DATADIR1"BattleStatus.acf",CR_DATAFILE1,crdataGetFileMode(),
		0,BATTLE_STATUSICONMAX,32,32);
	eiCellSetSurface(
		&BattleStatusCell[0],
		BATTLE_STATUSICONSURFACE_X,BATTLE_STATUSICONSURFACE_Y,
		32,32,BATTLE_STATUSICONMAX);

	for(a = 0;a < MEMBER_MAX;a ++){
		pChara = crcharaGetPartyMember(a);
		if(pChara != NULL){
			eiDebugWriteFile(pChara->GetName());
			eiDebugWriteFile("\n");
			sprintf(s,"%s%s",CR_DATADIR4,pChara->GetBattleFileName());
/*		if(a == 0){
		} else if(a == 1){
			sprintf(s,"%s%s",CR_DATADIR4,"BatHiro.bmp");
		} else {
			sprintf(s,"%s%s",CR_DATADIR4,"BatRacis.bmp");
		}*/

			c &= eiCellReadPattern(
				&BattleCharaCell[0],
				s,CR_DATAFILE4,crdataGetFileMode(),
				a * BATTLE_CHARAPATTERN,BATTLE_CHARAPATTERN,32,32);
			eiCellSetSurface(
				&BattleCharaCell[a * BATTLE_CHARAPATTERN],
				(32 * BATTLE_CHARAALYAWSSURFACE * a) % 640,
				((32 * BATTLE_CHARAALYAWSSURFACE * a) / 640) * 32,
				32,32,BATTLE_CHARAALYAWSSURFACE);

			pBtChara[a].SetCell(&BattleCharaCell[a * BATTLE_CHARAPATTERN]);
		}
	}

	return c;
}


CRBATINIT_API int crbatCopyData(void)
{
	int a,b,c = 0;
	CrCharacter *pChara;

	//---データコピー
	for(a = 0;a < MEMBER_MAX;a ++){
		pChara = crcharaGetPartyMember(a);
		if(pChara != NULL){
			//---いれば
			memcpy(&pBtChara[a].CharaInfo,&pChara->CharaInfo,sizeof(pBtChara[a].CharaInfo));
//			memcpy(&pBtChara[a].BattleHistory,&pChara->BattleHistory,sizeof(pBtChara[a].BattleHistory));

			memset(&pBtChara[a].BattleInfo,0,sizeof(pBtChara[a].BattleInfo));
			memset(&pBtChara[a].OnlyInfo,0,sizeof(pBtChara[a].OnlyInfo));
			memset(&pBtChara[a].Command,0,sizeof(pBtChara[a].Command));

			//---いる
			pBtChara[a].BattleInfo.Existence = 1;
		} else {
			//---いない
			memset(&pBtChara[a].CharaInfo,0,sizeof(pBtChara[a].CharaInfo));
			memset(&pBtChara[a].OnlyInfo,0,sizeof(pBtChara[a].OnlyInfo));
			memset(&pBtChara[a].Command,0,sizeof(pBtChara[a].Command));

			pBtChara[a].BattleInfo.Existence = 0;
		}

		if(crdataGetSystem()->BattleCommandReset <= 1){
			//---バトルごとリセット
			memset(&pBtChara[a].GetCharacterInfo()->BattleMenuCursor,0,
				sizeof(pBtChara[a].GetCharacterInfo()->BattleMenuCursor));
		}

		//---味方フラッグ
		pBtChara[a].BattleInfo.FriendOrEnemy = 1;
		pBtChara[a].SetType(CHARATYPE_NINGEN);
		//---ＭＣ
		pBtChara[a].ResetMagicTime(1);
		//---エレメント
		for(b = 0;b < 16;b ++){
			pBtChara[a].BattleInfo.Element[b] = 1000;//---100%
		}

		//---アビリティセット
		pBtChara[a].SetAbility(BTAB_S_CRITICAL1,1);
		if(pBtChara[a].Who() == 3){
			//---ナック
			pBtChara[a].SetAbility(BTAB_S_KAIFUKUMAGIC_P,1);
		}
		if(pBtChara[a].Who() == 14){
			//---クレスティーユ
			pBtChara[a].SetAbility(BTAB_P_HENKA,1);
			pBtChara[a].SetAbility(BTAB_S_BARRIER200,1);
//			pBtChara[a].SetAbility(BTAB_S_FIRSTATACK,1);
		}

		//---防具
		int uni[5] = {0,0,0,0,0};

		for(b = 0;b < EQ_WEAPON_MAX;b ++){
			switch(pBtChara[a].GetWeapon(b)){
			case 82:
				//---モリウニブレード
				uni[0] = 1;
				break;
			}
		}

		for(b = 0;b < EQ_PROTECTOR_MAX;b ++){
			switch(pBtChara[a].GetProtector(b)){
			case 132:
				//---ドブウニクロス
				uni[1] = 1;
				break;
			case 254:
				//---ウニマリモマスク
				uni[3] = 1;
				break;

			case 98:
				//---バリアスーツ
				//---バリア２５
				pBtChara[a].SetAbility(BTAB_S_BARRIER25,1);
				break;
			case 116:
				//---ふんどしアーマー
				//---ファーストアタック
				pBtChara[a].SetAbility(BTAB_S_FIRSTATACK,1);
				break;
			case 118:
				//---大地の衣
				//---土耐性
				pBtChara[a].BattleInfo.Element[ELEMENT_EARTH] = 0;
				break;
			case 119:
				//---呪縛のローブ
				pBtChara[a].SetAbility(BTAB_M_MC,1);
				break;
			case 127:
				//---ドラゴンアイズ
				//---ブレス０
				pBtChara[a].SetAbility(BTAB_P_BREATH0,1);
				break;
			case 133:
				//---リビングアーマー
				//---－回復、－変化、－ＭＣ
				pBtChara[a].SetAbility(BTAB_M_KAIFUKU,1);
				pBtChara[a].SetAbility(BTAB_M_HENKA,1);
				pBtChara[a].SetAbility(BTAB_M_MC,1);

			case 126:
				//---アイスアーマー
				pBtChara[a].BattleInfo.Element[ELEMENT_AQUA] /= 2;
				break;
			case 130:
				//---毛糸のローブ
				pBtChara[a].BattleInfo.Element[ELEMENT_AQUA] /= 4;
				break;
			case 131:
				//---セーター
				pBtChara[a].BattleInfo.Element[ELEMENT_AQUA] /= 3;
				break;

//-----------------------------------
			case 156:
				//---ホワイトシールド
				pBtChara[a].SetAbility(BTAB_S_AUTOGARD,1);
				break;
			case 157:
				//---精霊の盾
				//---ブレス４／５
				pBtChara[a].SetAbility(BTAB_P_BREATH45,1);
				pBtChara[a].SetAbility(BTAB_P_SOKUSHI,1);
				pBtChara[a].SetAbility(BTAB_P_NEMURI,1);
				pBtChara[a].SetAbility(BTAB_P_DOKU,1);
				pBtChara[a].SetAbility(BTAB_P_KURAYAMI,1);
				pBtChara[a].SetAbility(BTAB_P_HENKA_23,1);
				break;
			case 158:
				//---ダワン石の盾
				//---炎耐性
				pBtChara[a].BattleInfo.Element[ELEMENT_FIRE] /= 2;
				break;
			case 159:
				//---ダワン石の盾・限定版
				//---炎耐性
				pBtChara[a].BattleInfo.Element[ELEMENT_FIRE] = 0;
				break;
			case 164:
				//---ライフディフェンダー
				pBtChara[a].SetAbility(BTAB_S_SAISEI1,1);
				break;
			case 165:
				//---爆笑シールド
				//---吹雪耐性
				pBtChara[a].BattleInfo.Element[ELEMENT_AQUA] = 
					(pBtChara[a].BattleInfo.Element[ELEMENT_AQUA] * 3) / 5;
				break;
			case 167:
				//---ヒヤウニガード
				uni[2] = 1;
				//---水耐性
				pBtChara[a].BattleInfo.Element[ELEMENT_AQUA] = 0;
				break;
			case 168:
				//---ライゼル笑いの盾
				//---吹雪耐性
				pBtChara[a].BattleInfo.Element[ELEMENT_AQUA] = 
					(pBtChara[a].BattleInfo.Element[ELEMENT_AQUA] * 4) / 5;
				break;
			}
		}

		//---アクセサリー
		int b5 = 0,b25 = 0,b100 = 0,unimant = 0;
		for(b = 0;b < EQ_ACCESSORY_MAX;b ++){
			switch(pBtChara[a].GetAccessory(b)){
			case 171:
				//---コーヒーイヤリング
				pBtChara[a].SetAbility(BTAB_P_NEMURI,1);
				break;
			case 172:
				//---正座帯
				pBtChara[a].SetAbility(BTAB_P_MAHI,1);
				break;
			case 173:
				//---おしゃべりんぐ
				pBtChara[a].SetAbility(BTAB_P_CHINMOKU,1);
				break;
			case 174:
				//---ドクぽいぽい
				pBtChara[a].SetAbility(BTAB_P_DOKU,1);
				break;
			case 175:
				//---なるとシール
				pBtChara[a].SetAbility(BTAB_P_KONRAN,1);
				break;
			case 176:
				//---忍びの心
				pBtChara[a].SetAbility(BTAB_S_NOCOUNTER,1);
				break;
			case 177:
				//---回復１
				pBtChara[a].SetAbility(BTAB_P_KAIFUKU1,1);
				break;
			case 178:
				//---回復２
				pBtChara[a].SetAbility(BTAB_P_KAIFUKU2,1);
				break;
			case 179:
				//---ＭＣ１
				pBtChara[a].SetAbility(BTAB_P_MC1,1);
				break;
			case 180:
				//---ＭＣ２
				pBtChara[a].SetAbility(BTAB_P_MC2,1);
				break;
			case 181:
				//---ブレス４／５
				pBtChara[a].SetAbility(BTAB_P_BREATH45,1);
				break;
			case 182:
				//---ブレス２／３
				pBtChara[a].SetAbility(BTAB_P_BREATH23,1);
				break;
			case 183:
				//---持続１
				pBtChara[a].SetAbility(BTAB_P_JIZOKU1,1);
				break;
			case 184:
				//---持続２
				pBtChara[a].SetAbility(BTAB_P_JIZOKU2,1);
				break;
			case 185:
				//---クリティカル２
				pBtChara[a].SetAbility(BTAB_S_CRITICAL2,1);
				break;
			case 186:
				//---狩人の守り
				pBtChara[a].SetAbility(BTAB_P_NEMURI,1);
				pBtChara[a].SetAbility(BTAB_P_MAHI,1);
				pBtChara[a].SetAbility(BTAB_P_DOKU,1);
				break;
			case 187:
				//---カオスブローチ
				pBtChara[a].SetAbility(BTAB_S_KAOS,1);
				break;

			case 188:
				//---スペルピアス
				pBtChara[a].SetAbility(BTAB_S_HOJOMAHO,1);
				break;
			case 189:
				//---クリティカル３
				pBtChara[a].SetAbility(BTAB_S_CRITICAL3,1);
				break;
			case 190:
				//---四つ葉のクローバー
				pBtChara[a].SetAbility(BTAB_P_SOKUSHI,1);
				break;
			case 192:
				//---白帯
				pBtChara[a].SetAbility(BTAB_S_COUNTER25,1);
				break;
			case 193:
				//---黒帯
				pBtChara[a].SetAbility(BTAB_S_COUNTER50,1);
				break;
			case 194:
				//---達人の帯
				pBtChara[a].SetAbility(BTAB_S_COUNTER75,1);
				break;
			case 196:
				//---おばちゃんのおまもり
				pBtChara[a].SetAbility(BTAB_P_HENKA,1);
				break;
			case 197:
				//---頑固親父のヒゲ
				pBtChara[a].SetAbility(BTAB_P_HENKA_23,1);
				break;
			case 198:
				//---頑固親父のもみあげ
				pBtChara[a].SetAbility(BTAB_P_HENKA_12,1);
				break;
			case 199:
				//---けっかい石
				pBtChara[a].SetAbility(BTAB_P_HENKA_14,1);
				break;
			case 200:
				//---バリアボール５
				pBtChara[a].SetAbility(BTAB_S_BARRIER5,1);
				b5 ++;
				if(b5 == 2){
					//---バリアー１０
					pBtChara[a].SetAbility(BTAB_S_BARRIER10,1);
				}
				break;
			case 201:
				//---バリアボール２５
				pBtChara[a].SetAbility(BTAB_S_BARRIER25,1);
				b25 ++;
				if(b25 == 2){
					//---バリアー５０
					pBtChara[a].SetAbility(BTAB_S_BARRIER50,1);
				}
				break;
			case 202:
				//---バリアボール１００
				pBtChara[a].SetAbility(BTAB_S_BARRIER100,1);
				b100 ++;
				if(b100 == 2){
					//---バリアー２００
					pBtChara[a].SetAbility(BTAB_S_BARRIER200,1);
				}
				break;
			case 204:
				//---目玉イヤリング（命中補正率の外れる確率３／４）
				pBtChara[a].SetBtSubHitProb(1000 - ((1000 - pBtChara[a].GetBtSubHitProb()) * 3) / 4);
				break;
			case 205:
				//---赤いバンダナ（命中補正率の外れる確率半分）
				pBtChara[a].SetBtSubHitProb(1000 - (1000 - pBtChara[a].GetBtSubHitProb()) / 2);
				break;
			case 206:
				//---ヤマウニマント
				uni[4] = 1;
				unimant ++;
				if(unimant == 2){
					//---カウンター２５
					pBtChara[a].SetAbility(BTAB_S_COUNTER25,1);
				}
				break;
			case 207:
				//---絶対安眠君
				pBtChara[a].SetAbility(BTAB_S_ANMIN,1);
				break;
			case 208:
				//---魔晶石の指輪
//				pBtChara[a].SetAbility(BTAB_P_NEMURI,1);
//				pBtChara[a].SetAbility(BTAB_P_CHINMOKU,1);
				pBtChara[a].AddBtStatus(BTST_FSHIELD);
				break;
			case 273:
				//---稲妻ネックレス
				pBtChara[a].BattleInfo.Element[ELEMENT_THUNDER] = 0;
				break;
			case 274:
				//---戦士の腕輪
				pBtChara[a].SetAbility(BTAB_P_KONRAN,1);
				pBtChara[a].SetAbility(BTAB_P_MAHI,1);
				pBtChara[a].SetAbility(BTAB_P_KURAYAMI,1);
				break;
			}
		}

		//---状態変化系アクセサリ
		for(b = 0;b < EQ_ACCESSORY_MAX;b ++){
			switch(pBtChara[a].GetAccessory(b)){
			case 191:
				//---ルビーアイ
				for(c = ELEMENT_FIRE;c <= ELEMENT_OTHER;c ++){
					pBtChara[a].BattleInfo.Element[c] = 
						(pBtChara[a].BattleInfo.Element[c] * 75) / 100;
				}
				break;
			case 209:
				//---狂乱の指輪
				if(!pBtChara[a].Ability(BTAB_P_HENKA)){
//					pBtChara[a].SetAbility(BTAB_M_HENKA,1);
					pBtChara[a].SetAbility(BTAB_M_JIZOKU,1);
//					pBtChara[a].SetAbility(BTAB_M_KAIFUKU,1);
				}
				pBtChara[a].AddBtStatus(BTST_POWER);
				pBtChara[a].AddTurnStatus(BTST_POWER,1);
				pBtChara[a].AddBtStatus(BTST_KONRAN);
				break;
			case 210:
				//---ピースオブムーン
				pBtChara[a].AddBtStatus(BTST_EXTEND);
				pBtChara[a].AddTurnStatus(BTST_EXTEND,1);
				break;
			}
		}

		if(uni[0] && uni[1] && uni[2] && uni[3] && uni[4]){
			pBtChara[a].SetAbility(BTAB_S_FIRSTESTATACK,1);
		}
	}

	return 1;
}
