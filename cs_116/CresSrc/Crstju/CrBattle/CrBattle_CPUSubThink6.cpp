
int crbatSelectCopysWeapon(CrBattleCharacter *pChara,int who,int force = 0)
{
	int a;
	int item = 0,wp[2] = {pChara->GetWeapon(0),pChara->GetWeapon(1)};
	CrItem *pItem[2] = {critemGetItemClass(wp[0]),critemGetItemClass(wp[1])};

	if(force){
		if(force == 1){
			//---剣
			for(a = 0;a < 2;a ++){
				if(pItem[a]->GetAtackKind() == 1){
					pChara->SetWeapon(a,0);
				}
			}
			item = crbatSelectCopysWeapon(pChara,who,0);
		} else if(force == 2){
			//---銃
			for(a = 0;a < 2;a ++){
				if(pItem[a]->GetAtackKind() == 0){
					pChara->SetWeapon(a,0);
				}
			}
			item = crbatSelectCopysWeapon(pChara,who,0);
		}

		//---直す
		for(a = 0;a < 2;a ++){
			pChara->SetWeapon(a,wp[a]);
		}

		return item;
	}

	switch(who){
	case 1:
		//---ルナン
		if(pItem[0]->GetAtack() < pItem[1]->GetAtack())
			item = 1;
		else
			item = 0;
		break;

	case 2:
		//---ディザ
		if(pItem[0]->GetMaterialKind() == pItem[1]->GetMaterialKind()){
			if(pItem[0]->GetAtack() < pItem[1]->GetAtack())
				item = 1;
			else
				item = 0;
		} else {
			if(pItem[0]->GetAtack() * 3 > pItem[1]->GetAtack() * 5)
				item = 0;
			else {
				if(pItem[0]->GetAtack() * 3 < pItem[1]->GetAtack() * 5)
					item = 1;
				else
					item = eiRnd(2);
			}
		}
		break;

	case 3:
		//---ナック
		if(pItem[0]->GetAtack() && pItem[1]->GetAtack())
			item = eiRnd(2);
		else if(!pItem[1]->GetAtack())
			item = 0;
		else
			item = 1;
		break;

	case 4:
		//---サヴィアー
		if(pItem[0]->GetMaterialKind() == pItem[1]->GetMaterialKind()){
			if(pItem[0]->GetAtack() < pItem[1]->GetAtack())
				item = 1;
			else
				item = 0;
		} else {
			if(pItem[0]->GetAtack() * 3 > pItem[1]->GetAtack() * 5)
				item = 0;
			else {
				if(pItem[0]->GetAtack() * 3 < pItem[1]->GetAtack() * 5)
					item = 1;
				else
					item = eiRnd(2);
			}
		}
		break;
	}

	return item;
}

static int copyCountMagic(ei_s32 *ptable)
{
	int a,b;

	for(a = 0,b = 0;a < MAGIC_MAX;a ++){
		if(ptable[a])
			b ++;
	}
	return b;
}

int crbatSelectCopysHojoMagic(CrBattleCharacter *pChara,int who)
{
	int magic = -1,mc = pChara->GetMC(),dst = -1;

	int use,rnd = eiRnd(1000);

	if((who == 3 && eiRnd(1000) < 500) || who == 4){
		//---フォースシールド
		use = 17;
		if(eiRnd(1000) < 800 && pChara->HaveMagic(use) && mc >= crmagicGetMagicClass(use)->GetMC()){
			magic = use;
			dst = eiRnd(4);
		}

		//---コンフュージョン
		use = 18;
		if(eiRnd(1000) < 400 && pChara->HaveMagic(use) && mc >= crmagicGetMagicClass(use)->GetMC()){
			magic = use;
			dst = -1;
		}

		//---エクステンド
		use = 22;
		if(eiRnd(1000) < 300 && pChara->HaveMagic(use) && mc >= crmagicGetMagicClass(use)->GetMC()
			&& pBtChara[BATTLECHARA_STARTENEMY + 1].DoExist()
			&& !pChara->GetBattleFlag(1)){
			magic = use;
			dst = 1;//---ディザ
		}

		//---サイレンス
		use = 15;
		if(eiRnd(1000) < 300 && pChara->HaveMagic(use) && mc >= crmagicGetMagicClass(use)->GetMC()){
			magic = use;
			dst = -1;
		}

		//---デスフォース
		use = 21;
		if(eiRnd(1000) < 700 && pChara->HaveMagic(use) && mc >= crmagicGetMagicClass(use)->GetMC()){
			magic = use;
			dst = -1;
		}

		//---オーロラテイル
		use = 23;
		if(eiRnd(1000) < 700 && pChara->HaveMagic(use) && mc >= crmagicGetMagicClass(use)->GetMC()){
			magic = use;
			dst = -1;
		}

		//---パワーブースト
		use = 19;
		if(eiRnd(1000) < 300 && pChara->HaveMagic(use) && mc >= crmagicGetMagicClass(use)->GetMC()
			&& pBtChara[BATTLECHARA_STARTENEMY + 1].DoExist()
			&& !pChara->GetBattleFlag(0)){
			magic = use;
			dst = 1;//---ディザ
			pChara->SetBattleFlag(0,1);
		}
		if(magic == 22){
			pChara->SetBattleFlag(1,1);
		}
	}

	if(who == 3){
		//---ワールド
		use = 24;
		if(eiRnd(1000) < 500 && pChara->HaveMagic(use) && mc >= 170
			&& pChara->GetWorldCountTurn() == 0){
			magic = use;
			dst = 5;
		}
	}

	if(magic != -1){
		if(dst == 5){
			crbatCPUThink_SetMagicAtack(pChara,magic);
		} else if(dst == -1){
			crbatCPUThink_SetMagicAtack(pChara,magic,-1,0,NULL,1);
		} else {
			crbatCPUThink_SetMagicAtack(pChara,magic,-1,0,&pBtChara[BATTLECHARA_STARTENEMY + dst]);
		}
		return magic;
	}

	return -1;
}

int crbatSelectCopysKaifukuMagic(CrBattleCharacter *pChara,int who)
{
	int magic = -1,mc = pChara->GetMC();

	ei_u32 st;
	int a,st_count,use,count = 0,index[4],list[4];
	CrBattleCharacter *ch;

	for(a = 0;a < 4;a ++){
		index[a] = list[a] = 0;

		ch = &pBtChara[BATTLECHARA_STARTENEMY + a];
		st = pBtChara[BATTLECHARA_STARTENEMY + a].GetBtStatus();

		if(ch->GetLP() * 100 / ch->GetMaxLP() < 70
			&& ch->GetLP() > 0){
			count ++;
		}
		if(st & 0xffff)
			index[a] ++;
	}
	for(a = 0,st_count = 0;a < 4;a ++){
		if(index[a]){
			list[st_count] = a;
			st_count ++;
		}
	}

	//---ライフシャワー
	use = 3;
	if(pChara->HaveMagic(use) && mc >= crmagicGetMagicClass(use)->GetMC()
		&& count >= 2 && !crbatCPU_PlayerIsBaraBara(pChara,2)){
		magic = use;
	}
	//---リカバレイション
	use = 6;
	if(pChara->HaveMagic(use) && mc >= crmagicGetMagicClass(use)->GetMC()
		&& count >= 1){
		magic = use;
	}

	//---ライフウィンド
	use = 7;
	if(pChara->HaveMagic(use) && mc >= crmagicGetMagicClass(use)->GetMC()
		&& count >= 2 && !crbatCPU_PlayerIsBaraBara(pChara,3)){
		magic = use;
	}

	use = 2;
	if(pChara->HaveMagic(use) && mc >= crmagicGetMagicClass(use)->GetMC()
		&& count <= 0 && st_count){
		//---キュアー
		crbatCPUThink_SetMagicAtack(pChara,2);
		pChara->Command.Target = (ei_u32)&pBtChara[BATTLECHARA_STARTENEMY + list[eiRnd(st_count)]];
		return 2;
	}

	if(magic != -1){
		crbatCPUThink_SetMagicAtack(pChara,magic);
		return magic;
	}
	return -1;
}

int crbatSelectCopysAtackMagic(CrBattleCharacter *pChara,int who)
{
	int a;
	int magic = -1,mc = pChara->GetMC(),limit,l = 0,low = 0;
	ei_s32 table[MAGIC_MAX];

	switch(who){
	case 1:
		l = 80;
		low = 3;
		break;
	case 2:
		l = 80;
		low = 4;
		break;
	case 3:
		l = 70;
		low = 3;
		break;
	case 4:
		l = 50;
		low = 4;
		break;
	}
	limit = (mc * l) / 100;

	//---テーブルコピー
	memcpy(table,pChara->CharaInfo.MagicTable,sizeof(table));

	//---魔法が無くなったら
	if(!copyCountMagic(table))
		return -1;

	crmateSortMaterial(table,
		MAGIC_MAX,pMagicInfo,
		SORTMATERIAL_MC,NULL);

	//---自分のＭＣのｌ％以下の魔法のみを集める
	int element;
	for(a = 0;a < MAGIC_MAX;a ++){
		element = crmagicGetMagicClass(table[a])->GetMaterialKind();

		if(!(ELEMENT_FIRE <= element && element <= ELEMENT_THUNDER)
			&& !(element == ELEMENT_NOELEMENT)){
			//---攻撃魔法以外を外す
			table[a] = 0;
		}
		//---ディフュージョン＆エクスティンクション、両方使えたら、エクスティンクションを外す
		if(table[a] == 77 && pChara->HaveMagic(77) && pChara->HaveMagic(78)){
			table[a] = 0;
		}
		//---エクスティンクションだけもっていたら、ランダム使用
		if(table[a] == 77 && !pChara->HaveMagic(78) && eiRnd(1000) < 500){
			table[a] = 0;
		}

		if(crmagicGetMagicClass(table[a])->GetMC() > limit){
			memset(&table[a],0,sizeof(ei_s32) * (MAGIC_MAX - a));
			break;
		}
	}

	//---魔法が無くなったら
	if(!copyCountMagic(table))
		return -1;

	//---魔法をレベルごとに分ける
	crmateSortMaterial(table,
		MAGIC_MAX,pMagicInfo,
		SORTMATERIAL_LEVEL | SORTMATERIAL_REVERSE,NULL);

	int level = crmagicGetMagicClass(table[0])->GetLevel();
	if(level < low)
		return -1;
	//---使える最高レベルの魔法を集める
	for(a = 0;a < MAGIC_MAX;a ++){
		if(crmagicGetMagicClass(table[a])->GetLevel() < level){
			memset(&table[a],0,sizeof(ei_s32) * (MAGIC_MAX - a));
			break;
		}
	}
	//---aまでの魔法を選べる

	magic = table[eiRnd(a)];
	crbatCPUThink_SetMagicAtack(pChara,magic);
	
	return magic;
}

int crbatSelectCopysAtackSpecial(CrBattleCharacter *pChara,int who)
{
	int item = crbatSelectCopysWeapon(pChara,who);
	int index = pChara->GetEnableSpecial();
	CrSpecial *psp;
	psp = &pSpecialInfo[index];

	if(pChara->GetBtStatus() & BTST_MAHI){
		return -1;
	}

	switch(index){
	case 16:
		//---お師匠様
		crbatCPUThink_SetAtack2(pChara,item,&pBtChara[2]);

		pChara->Command.Main = BAT_COMMAND_SPECIAL;
		pChara->Command.Sub[BAT_SUBCOM_SPECIALNUMBER] = index;
		pChara->Command.Range = BAT_TARGET_FRIENDALL;
///		pChara->Command.Target = (ei_u32)pChara;
		return index;

	case 17:
		//---そうせんだ
	case 18:
		//---ホーリークロスは使わない
		return -1;
	case 19:
		//---光の雫
		pChara->Command.Main = BAT_COMMAND_SPECIAL;
		pChara->Command.Sub[BAT_SUBCOM_SPECIALNUMBER] = index;
		pChara->Command.Range = BAT_TARGET_ENEMYALL;
		pChara->Command.Target = (ei_u32)pChara;
		return index;

	case 1:
	case 2:
		//---ルナン必殺技
		return -1;
	case 6:
	case 7:
	case 8:
	case 9:
		//---剣
		item = crbatSelectCopysWeapon(pChara,who,1);
		if(pChara->GetWeapon(item) == 0){
			return -1;
		}
		crbatCPUThink_SetAtack2(pChara,item,&pBtChara[2]);

		pChara->Command.Main = BAT_COMMAND_SPECIAL;
		pChara->Command.Sub[BAT_SUBCOM_SPECIALNUMBER] = index;
		pChara->Command.Range = crbatCPUThink_ReverseRange(psp->GetTarget() | psp->GetRange());

		return index;

	case 14:
		//---Ｒ－シューティング
		return -1;
	case 11:
	case 12:
	case 15:
		//---銃
		item = crbatSelectCopysWeapon(pChara,who,2);
		if(pChara->GetWeapon(item) == 0){
			return -1;
		}
		crbatCPUThink_SetAtack2(pChara,item,&pBtChara[2]);

		pChara->Command.Main = BAT_COMMAND_SPECIAL;
		pChara->Command.Sub[BAT_SUBCOM_SPECIALNUMBER] = index;
		pChara->Command.Range = crbatCPUThink_ReverseRange(psp->GetTarget()| psp->GetRange());

		return index;

	case 3:
	case 4:
		//---月光唱、カウンターゲート
		if(pChara->GetBtStatus() & BTST_CHINMOKU){
			return -1;
		}
		if(crbatSelectCopysAtackMagic(pChara,1) != -1){
			pChara->Command.Main = BAT_COMMAND_SPECIAL;
			pChara->Command.Sub[BAT_SUBCOM_SPECIALNUMBER] = index;

			if(index == 4){
				pChara->Command.Target = (ei_u32)pChara;
				pChara->Command.Range = BAT_TARGET_ENEMY;
			}

			return index;
		}
		return -1;
	}

	return -1;
}

CRBATCPU_API int crbatCPUThink6(CrBattleCharacter *pChara,int turn,int rnd)
{
	if(pChara->BattleInfo.Enemy.ActionType == 168){
		//---ムクジャラナイト
		if(rnd < 333){
			//---斬りかかる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 169){
		//---フク
		if(rnd < 250){
			//---だるだる波
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_DARUDARUHA);
		} else if(rnd < 400){
			//---寝る
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NERU);
		} else if(rnd < 650){
			//---あくび
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_AKUBI);
		} else if(rnd < 700){
			//---さぼる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SABORU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 170){
		//---カイワレ大帝
		if(rnd < 250){
			//---成長
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SEICHOU);
		} else if(rnd < 400 && pChara->GetLP() != pChara->GetMaxLP()){
			//---光合成
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KOUGOUSEI);
		} else if(rnd < 400){
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 750 && pChara->GetTurnAtack() <= 1){
			//---ダイヤブレス
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,62,-1,0,NULL,1);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 204){
		//---ピンクリボン
		if(rnd < 200){
			//---ピンクミスト
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_PINKMIST);
		} else if(rnd < 400){
			//---リボンツイスター
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_RIBONTUISTA,90);
		} else if(rnd < 550){
			//---エクステンド
			crbatCPUThink_SetMagicAtack(pChara,22);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 205){
		//---コアステラス
		if(rnd < 300 && !pChara->GetTurnAtack()){
			//---いかづち
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_IKADUCHI,130);
		} else if(rnd < 250){
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 500){
			//---かみつく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 206){
		//---エノキタイクーン
		if(rnd < 300){
			//---胞子
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HOUSHI,30);
		} else if(rnd < 500){
			//---たべる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TABERU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 211){
		//---ディガーン
		if(rnd < 200){
			//---ぐるぐる目玉ハイパー
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_GURUGURUHYPER);
		} else if(rnd < 400){
			//---即死光線
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SOKUSHIKOUSEN);
		} else if(rnd < 700){
			//---アイビーム
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_EYEBEAM,250);
		} else if(rnd < 500 && !(pChara->GetBtStatus() & BTST_PROTECT)){
			//---プロテクション
			crbatCPUThink_SetMagicAtack(pChara,13);
		} else if(rnd < 750 && !pChara->GetPersonalTurn()
			&& turn >= 2){
			//---タイダルウェイヴ
			pChara->AddPersonalTurn(5);
			crbatCPUThink_SetMagicAtack(pChara,51);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
//-------------------------------------
	} else if(pChara->BattleInfo.Enemy.ActionType == 207){
		//---ルナンコピー
		int item = crbatSelectCopysWeapon(pChara,1);

		if(pChara->GetBattleFlag(0) > 0){
			pChara->SetBattleFlag(0,pChara->GetBattleFlag(0) - 1);
		} else if(pChara->GetMC() < 30){
			pChara->SetBattleFlag(0,3);
		}

		if(rnd < 900 && crbatSelectCopysAtackSpecial(pChara,1) != -1){
			//---必殺技
		} else if(!(pChara->GetBtStatus() & BTST_CHINMOKU)
			&& crbatCPUGetEnemy() <= 2 && rnd < 500){
			//---回復魔法
			if(crbatSelectCopysKaifukuMagic(pChara,1) == -1){
				//---通常攻撃
				crbatCPUThink_SetAtack2(pChara,item,&pBtChara[2]);
			}
		} else if((pChara->GetBtStatus() & BTST_CHINMOKU)
			|| pChara->GetBattleFlag(0) > 0){
			//---通常攻撃
			if(turn % 2 == 1 && crbatCPUGetEnemy() > 1){
				pChara->Command.Main = BAT_COMMAND_DEFENSE;
				pChara->Command.Sub[0] = BAT_SUBCOM_DEFENSE;
			} else {
				crbatCPUThink_SetAtack2(pChara,item,&pBtChara[2]);
			}
		} else if(rnd < 1000){
			if(crbatSelectCopysAtackMagic(pChara,1) == -1){
				//---通常攻撃
				crbatCPUThink_SetAtack2(pChara,item,&pBtChara[2]);
			}
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack2(pChara,item,&pBtChara[2]);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 208){
		//---ディザコピー
		int item = crbatSelectCopysWeapon(pChara,2);

		if(rnd < 900 && crbatSelectCopysAtackSpecial(pChara,2) != -1){
			//---必殺技
		} else if(((pChara->GetBtStatus() & BTST_MAHI) || rnd < 200)
			&& turn != 0
			&& !((pChara->GetBtStatus() & BTST_POWER)
				|| (pChara->GetBtStatus() & BTST_EXTEND)
				)){
			if(crbatSelectCopysAtackMagic(pChara,2) == -1){
				//---通常攻撃
				crbatCPUThink_SetAtack2(pChara,item,&pBtChara[2]);
			}
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack2(pChara,item,&pBtChara[2]);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 209){
		//---ナックコピー
		int item = crbatSelectCopysWeapon(pChara,3);

		if(rnd < 900 && crbatSelectCopysAtackSpecial(pChara,3) != -1){
			//---必殺技
		} else if(pChara->GetBtStatus() & BTST_CHINMOKU){
			//---通常攻撃
			crbatCPUThink_SetAtack2(pChara,item);

		} else if((rnd < 333 && turn >= 1)
			|| turn == 1){
			if(crbatSelectCopysKaifukuMagic(pChara,3) == -1){
				if(crbatSelectCopysHojoMagic(pChara,3) == -1){
					//---通常攻撃
					crbatCPUThink_SetAtack2(pChara,item);
				}
			}
		} else if(rnd < 666 && turn % 2 == 0){
			if(crbatSelectCopysHojoMagic(pChara,3) == -1){
				if(crbatSelectCopysKaifukuMagic(pChara,3) == -1){
					//---通常攻撃
					crbatCPUThink_SetAtack2(pChara,item);
				}
			}
		} else if(rnd < 1000 && turn % 2 == 0){
			if(crbatSelectCopysAtackMagic(pChara,3) == -1){
				//---通常攻撃
				crbatCPUThink_SetAtack2(pChara,item);
			}
		} else if(turn % 2 == 0 && crbatCPUGetEnemy() > 1){
			pChara->Command.Main = BAT_COMMAND_DEFENSE;
			pChara->Command.Sub[0] = BAT_SUBCOM_DEFENSE;
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack2(pChara,item);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 210){
		//---サヴィアーコピー
		int item = crbatSelectCopysWeapon(pChara,4);

		if(rnd < 900 && crbatSelectCopysAtackSpecial(pChara,4) != -1){
			//---必殺技
		} else if(rnd < 250 - (turn == 0 ? 150 : 0)
			&& !(pChara->GetBtStatus() & BTST_CHINMOKU)){
			if(crbatSelectCopysAtackMagic(pChara,4) == -1){
				//---通常攻撃
				if(crbatSelectCopysHojoMagic(pChara,4) == -1){
					crbatCPUThink_SetAtack2(pChara,item);
				}
			}
		} else if(rnd < 800 + (turn == 0 ? 200 : 0)
			&& !(pChara->GetBtStatus() & BTST_CHINMOKU)){
			if(crbatSelectCopysHojoMagic(pChara,4) == -1){
				//---通常攻撃
				crbatCPUThink_SetAtack2(pChara,item);
			}
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack2(pChara,item);
		}
//------------------------------------------------------
	} else if(pChara->BattleInfo.Enemy.ActionType == 172){
		//---ヒヤウニ
		if(rnd < 600){
			//---回転アタック
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAITENATACK);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 173){
		//---ミノタウロス
		if(rnd < 250){
			//---なぐる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGURU);
		} else if(rnd < 400){
			//---突進
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOSSHIN);
		} else if(rnd < 550){
			//---なぎ倒す
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGITAOSU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 174){
		//---アイスポール
		if(rnd < 200){
			//---サイレンス
			crbatCPUThink_SetMagicAtack(pChara,15,-1,0,NULL,1);
		} else if(rnd < 400){
			//---コンフュージョン
			crbatCPUThink_SetMagicAtack(pChara,18,-1,0,NULL,1);
		} else if(rnd < 650){
			//---アクアソード
			crbatCPUThink_SetMagicAtack(pChara,50);
		} else if(rnd < 800){
			//---ＭＣ分解
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_MCBUNKAI,30);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 175){
		//---ブリザード
		if(rnd < 300 && !pChara->GetTurnAtack()){
			//---吹雪
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_FUBUKI,130);
		} else if(rnd < 500){
			//---吹雪
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_FUBUKI,70);
		} else if(rnd < 700){
			//---スリープブレス
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,35);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 176){
		//---ホワイトデス
		if(rnd < 200 && !pChara->GetPersonalTurn()){
			//---デスフォース
			pChara->AddPersonalTurn(3);
			crbatCPUThink_SetMagicAtack(pChara,21);
		} else if(rnd < 600 && pChara->GetLP() < 100){
			//---ＬＰチェンジ
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_LPCHANGE,750);
		} else if(rnd < 500){
			//---とかす
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOKASU);
		} else if(rnd < 700 && crbatCPUGetEnemy() > 1){
			//---のりうつる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NORIUTURU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 177){
		//---氷雪竜
		if(rnd < 300 && !pChara->GetTurnAtack()
			&& !pChara->GetPersonalTurn()){
			//---吹雪
			pChara->AddTurnAtack();
			pChara->AddPersonalTurn(2);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_FUBUKI,190);
		} else if(rnd < 350){
			//---吹雪
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_FUBUKI,100);
		} else if(rnd < 666){
			//---かみつく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KAMITUKU);
		} else if(rnd < 800 && pChara->GetLP() < 300
			&& pChara->GetBattleFlag(0) <= 1){
			//---リカバレイション
			pChara->SetBattleFlag(0,pChara->GetBattleFlag(0) + 1);
			crbatCPUThink_SetMagicAtack(pChara,6);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 178){
		//---フォールン
		CrBattleCharacter *pnear = crbatCPU_PlayerIsSekkin(pChara,0);

		if(pnear != NULL && rnd < 500
			&& pChara->GetBattleFlag(10) == 0){
			//---移動
			pChara->SetBattleFlag(10,pChara->GetBattleFlag(10) + 1);
			crbatCPUThink_SetDefense(pChara,3);
		} else if(rnd < 300 && pChara->GetLP() < 700 && pChara->GetBattleFlag(0) <= 2
			&& !(pChara->GetBtStatus() & BTST_CHINMOKU)){
			//---リカバライズ
			pChara->SetBattleFlag(0,pChara->GetBattleFlag(0) + 1);
			crbatCPUThink_SetMagicAtack(pChara,3);
		} else if(rnd < 333){
			//---ドレインスラッシュ
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KYUKETUKEN);
		} else if((rnd < 700 && !pChara->GetPersonalTurn())
			|| (turn <= 1 && !pChara->GetPersonalTurn())){
			//---サイレント・バニッシャー
			pChara->AddPersonalTurn(3);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SILENTBANISHA);
		} else if(rnd < 650 && pChara->GetBattleFlag(1) == 0){
			//---パラライズ
			pChara->SetBattleFlag(1,1);
			crbatCPUThink_SetMagicAtack(pChara,31,-1,0,NULL,1);
		} else if(rnd < 650){
			//---インフルエンス
			pChara->SetBattleFlag(1,0);
			crbatCPUThink_SetMagicAtack(pChara,20,-1,0,NULL,1);
		} else if(rnd < 800){
			//---ゼロシールド
			crbatCPUThink_SetMagicAtack(pChara,30,-1,0,NULL,1);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 179){
		//---メタルゴーレム
		if(rnd < 200){
			//---なぐる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGURU);
		} else if(rnd < 400){
			//---突進
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOSSHIN);
		} else if(rnd < 550){
			//---なぎ倒す
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NAGITAOSU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 180){
		//---サンドマスター
		if(rnd < 333 && pChara->GetBattleFlag(0) == 0
			&& pChara->GetBattleFlag(1) == 0 && pChara->GetLP() >= 400){
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
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SUNAARASHI2,180);
		} else if(rnd < 700){
			//---食べる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TABERU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 181){
		//---言霊
		if(rnd < 250 && !pChara->GetTurnAtack()){
			//---ダイヤブレス
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,62,-1,0,NULL,1);
		} else if(rnd < 300){
			//---グラスシード
			crbatCPUThink_SetMagicAtack(pChara,61,-1,0,NULL,1);
		} else if(rnd < 500){
			//---パラライズ
			crbatCPUThink_SetMagicAtack(pChara,31);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 182){
		//---サンドウッド
		if(rnd < 250){
			//---インフルエンス
			crbatCPUThink_SetMagicAtack(pChara,20,-1,0,NULL,1);
		} else if(rnd < 350){
			//---ダークミスト
			crbatCPUThink_SetMagicAtack(pChara,14,-1,0,NULL,1);
		} else if(rnd < 500){
			//---エクステンド
			crbatCPUThink_SetMagicAtack(pChara,22);
		} else if(rnd < 750){
			//---リカバレイション
			crbatCPUThink_SetMagicAtack(pChara,6);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 183){
		//---流砂の使者
		if(rnd < 600 && pChara->GetLP() < 100){
			//---ＬＰチェンジ
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_LPCHANGE,750);
		} else if(rnd < 250){
			//---砂嵐
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SUNAARASHI,100);
		} else if(rnd < 666){
			//---吸血
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KYUKETSU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 186){
		//---エターナル兵
		if(rnd < 333 && !pChara->GetTurnAtack()){
			//---円月斬
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_ENGETUZAN);
		} else if(rnd < 350){
			//---斬りかかる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIRIKAKARU);
		} else if(rnd < 550){
			//---激しく
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_HAGESHIKU);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 187){
		//---エターナル魔道兵
		if(pBtChara[BATTLECHARA_STARTENEMY + 3].BattleInfo.Enemy.ActionType == 190
			&& turn == 0){
			//---デスマシーンを起こす
			pChara->Command.Main = BAT_COMMAND_WAIT;
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIDOSASERU);
			pChara->Command.Target = (ei_u32)&pBtChara[BATTLECHARA_STARTENEMY + 3];
		} else if((pChara->GetBtStatus() & BTST_CHINMOKU)
			|| pChara->GetMC() <= 120){
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		} else if(rnd < 333 && !pChara->GetTurnAtack()){
			//---テラジャッジメント
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,69);
		} else if(rnd < 333){
			crbatCPUThink_SetMagicAtack(pChara,68);
		} else if(rnd < 666){
			//---スーパーセル
			pChara->AddTurnAtack();
			crbatCPUThink_SetMagicAtack(pChara,57);
		} else if(rnd < 666 && !pChara->GetTurnAtack()){
			crbatCPUThink_SetMagicAtack(pChara,56);

		} else if(rnd < 750){
			//---サイレンス
			crbatCPUThink_SetMagicAtack(pChara,15,-1,0,NULL,1);
		} else if(rnd < 860){
			//---コンフュージョン
			crbatCPUThink_SetMagicAtack(pChara,18,-1,0,NULL,1);
		} else if(rnd < 950){
			//---ゼロシールド
			crbatCPUThink_SetMagicAtack(pChara,30,-1,0,NULL,1);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 188){
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
		} else if(rnd < 200){
			//---ライフウィンド
			crbatCPUThink_SetMagicAtack(pChara,7);
		} else if(rnd < 300){
			//---リカバリー３
			crbatCPUThink_SetMagicAtack(pChara,6);
		} else if(rnd < 450){
			//---プロテクション
			crbatCPUThink_SetMagicAtack(pChara,13);
		} else if(rnd < 600){
			//---エクステンド
			crbatCPUThink_SetMagicAtack(pChara,17);
		} else if(rnd < 800){
			//---オーロラテイル
			crbatCPUThink_SetMagicAtack(pChara,14);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 189){
		//---エターナル兵（特殊）
		if(crbatCPUGetEnemy() == 1){
			if(rnd < 400 && !pChara->GetPersonalTurn()){
				//---パワーボム
				pChara->AddPersonalTurn(2);
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_POWERBOMB,120);
			} else if(rnd < 750){
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,50);
			} else {
				//---サイレントブレス
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_SILENTBREATH,50);
			}
		} else if(rnd < 100){
			//---スリープブレス
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,50);
		} else if(rnd < 400){
			//---サイレントブレス
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SILENTBREATH,50);
		} else if(rnd < 700 && !pChara->GetTurnAtack()){
			//---パワーボム
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_POWERBOMB,120);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 190){
		//---デスマシーン
		if(crbatCPUGetEnemy() == 1 && pChara->GetBattleFlag(0) == 0){
			pChara->SetBattleFlag(0,1);
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_BOSOKAISHI);
		} else if(turn == 0){
			pChara->Command.Main = BAT_COMMAND_WAIT;
		} else if(turn == 1){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_KIDOU);
		} else if(crbatCPUGetEnemy() == 1){
			if(rnd < 200){
				//---ポイズンブレス
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_POISON,100);
			} else if(rnd < 500 && !pChara->GetTurnAtack()){
				//---切断
				pChara->AddTurnAtack();
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_SETUDAN);
			} else if(rnd < 850 && !pChara->GetTurnAtack()
				&& !pChara->GetPersonalTurn()){
				//---カスケードボム
				pChara->AddTurnAtack();
				pChara->AddPersonalTurn(3);
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_KASCADEBOMB,240);
			} else if(rnd < 750){
				//---弱化光線
				crbatCPUThink_SetAbility(pChara,BAT_ECOM_JAKUKAKOSEN,50);
			} else {
				//---通常攻撃
				crbatCPUThink_SetAtack(pChara);
			}
		} else if(rnd < 200){
			//---ポイズンブレス
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_POISON,50);
		} else if(rnd < 500 && !pChara->GetTurnAtack()){
			//---切断
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SETUDAN);
		} else if(rnd < 750){
			//---弱化光線
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_JAKUKAKOSEN,50);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 191){
		//---センサーアイ・α
		if(pChara->GetBattleFlag(0)){
			//---大爆発
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_JIBAKU1,0,pChara);
		} else if(pChara->GetLP() < 200 || crbatCPUGetEnemy() == 1){
			//---移動
			int x,y;
			pChara->SetBattleFlag(0,1);
			crbatCPU_GetPlayerCharaSide(pChara,&x,&y);
			crbatCPUThink_SetDefense(pChara,3,x,y);
		} else if(rnd < 200){
			//---スリープブレス
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SLEEPBREATH,50);
		} else if(rnd < 400){
			//---サイレントブレス
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SILENTBREATH,50);
		} else if(rnd < 800){
			//---アイビーム
			pChara->AddTurnAtack();
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_EYEBEAM,160);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	//-----------------------------------------------
	} else if(pChara->BattleInfo.Enemy.ActionType == 212){
		//---シロエイノー
		if(rnd < 80 * turn){
			//---さぼる
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_SABORU);
		} else if(rnd < 250){
			//---だるだる波
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_DARUDARUHA);
		} else if(rnd < 300){
			//---寝る
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_NERU);
		} else if(rnd < 550){
			//---混乱
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_DAIKONRAN);
		} else if(rnd < 1000){
			//---あくび
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_AKUBI);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 216){
		//---モリウニ
		if(rnd < 9999){
			crbatCPUThink_SetAbility(pChara,BAT_ECOM_TOSO);
		} else {
			//---通常攻撃
			crbatCPUThink_SetAtack(pChara);
		}
	}

	return crbatCPUThink7(pChara,turn,rnd);
}
