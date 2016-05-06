/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBattle_Special.cpp ...Battle Special functions

-----------------------------------------------------------*/

#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBATTLE_SPECIAL

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#define EXTERN_CRBATTLE
#include "..\CrBase.h"
#include "..\CrBattle.h"

#define CR_GAMEINFO_EXTERNPOINTER
#include "..\CrGameInfo.h"


//---必殺技
CRBATMAIN_API int crbatDoAction_SpecialAtack(CrSpecial *psp,
						CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int EnableCounter,int IsCounter,int Index)
{
	int a,b,count,max,prob = PROBMODE_100;

	//---ターゲットがいなかったら
	if(pChara->Command.Target == 0){
		return 0;
	}
	//---物理行動がとれなかったら
	if(!pChara->IsEnableMoveing()){
		return 0;
	}

	max = psp->GetSPAtackCount();

	//---スピード
	int old = 0;
	if(psp->GetNumber() == 14){
		old = crbatSetBattleSpeed(1);
	}
	//---ロックオン
	if(psp->GetNumber() == 11 || psp->GetNumber() == 12
		|| psp->GetNumber() == 15){
		crbatDoAnime_LockOn(pChara,pDamageInfo);
	}

	for(count = 0;count < max && crbatGetEnemyCount();count ++){
		if(psp->GetNumber() == 14){
			//---Ｒ－シューティング
			prob = 0;

			//---ランダム選択
			int point;
			CrBattleCharacter *pList[32];
			int start = BATTLECHARA_STARTENEMY,end = BATTLECHARA_MAX;

			if(pChara->GetNumber() >= BATTLECHARA_STARTENEMY){
				start = 0;
				end = BATTLECHARA_STARTENEMY - 1;
			}
			for(b = start , point = 0;b < end;b ++){
				if(pBtChara[b].DoExist()){
					pList[point] = &pBtChara[b];
					point ++;
				}
			}
			pDamageInfo->Damage[0] = 0;
			pDamageInfo->Miss[0] = 0;
			pDamageInfo->DontShowThisDamage[0] = 0;
			pChara->Command.Target = (ei_u32)pList[eiRnd(point)];
			if(pChara->GetNumber() < BATTLECHARA_STARTENEMY)
				pChara->Command.Range = BAT_TARGET_ENEMYSINGLE;
			else
				pChara->Command.Range = BAT_TARGET_FRIENDSINGLE;
		}

		//---衝突補正
		int range = (pChara->Command.Range & 0xffff0000) >> 16;
		//---ラインターゲットでなければ、衝突補正
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
		for(a = 1;pDamageInfo->pList[a] != NULL;a ++){
			//---補助ダメージ登録
			pDamageInfo->DamageRate[a] = psp->GetSubDamageRate();
		}

		//---攻撃値、防御値、計算方法、属性
		//---ダメージ計算
		int weapon = pChara->GetWeapon(pChara->Command.Sub[0]);
		int rate = psp->GetDamageRate(),critical = 0;
		int def_rate = 1000;

		if(psp->GetNumber() == 17){
			//---双扇打
			def_rate = 0;
		}

		//---武器に応じて追加効果
		crbatDoAction_AddWeaponEfectBefore(pDamageInfo,&rate,&def_rate,pChara,weapon);
		crbatCalcDamage(
			pDamageInfo,pChara,
			SRC_WEAPON,rate,
			DST_DEFENSE,def_rate,
			CALCMODE_ADD,500,
			psp->GetDamageDiffuse(),//---分散（１／１０００単位）
			weapon ? critemGetItemClass(weapon)->GetElement() : ELEMENT_PHYSICS,//---武器属性
//			ELEMENT_PHYSICS,
			PROBMODE_REAL | prob,pChara->GetBtHitProb(pChara->Command.Sub[0]),//---武器命中回避率、命中率
			DEFENSEMODE_REAL
			);

		//---アニメーション
		int option = 0;
		if(psp->GetNumber() == 8 || psp->GetNumber() == 9)
			option = 1;

		crbatDoAnime_Weapon(pChara,pDamageInfo,critical,option);
		//---武器に応じて追加効果
		crbatDoAction_AddWeaponEfectAfter(pDamageInfo,pChara,weapon);

		//---ダメージ表示
		crbatShowDamage(pDamageInfo);

		//---ダメージ結果加算
		crbatResultDamage(pDamageInfo);

		//---ダメージ結果表示
		crbatShowResult();
	}

	//---スピード
	if(psp->GetNumber() == 14){
		crbatSetBattleSpeed(old);
	}

	return 1;
}

//---必殺技
CRBATMAIN_API int crbatDoAction_SpecialAtack_Double(CrSpecial *psp,
						CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int EnableCounter,int IsCounter,int Index)
{
	int a,count,max,prob = PROBMODE_100;

	//---ターゲットがいなかったら
	if(pChara->Command.Target == 0){
		return 0;
	}
	//---物理行動がとれなかったら
	if(!pChara->IsEnableMoveing()){
		return 0;
	}

	max = 2;

	//---ロックオン
	if(psp->GetNumber() == 11 || psp->GetNumber() == 15){
		crbatDoAnime_LockOn(pChara,pDamageInfo);
	}

	for(count = 0;count < max && crbatGetEnemyCount();count ++){
		pChara->Command.Sub[0] = count;

		//---衝突補正
		crbatGetTargetChara(pChara,pChara->GetTarget(),
			pChara->Command.Range,&pDamageInfo->pList[0],1);
		if(pDamageInfo->pList[0] != NULL){
			//---衝突補正でターゲットが変わったときのための
			//---キャラクターアングル再設定
			pDamageInfo->pList[0]->SetAngle(
				ANGLE(180) + pChara->GetCharaAngle(pDamageInfo->pList[0])
				);
		}

		crbatSetDamageMode(pDamageInfo,DAMAGEMODE_SUB);
		for(a = 1;pDamageInfo->pList[a] != NULL;a ++){
			//---補助ダメージ登録
			pDamageInfo->DamageRate[a] = psp->GetSubDamageRate();
		}

		//---攻撃値、防御値、計算方法、属性
		//---ダメージ計算
		int weapon = pChara->GetWeapon(pChara->Command.Sub[0]);
		int rate = psp->GetDamageRate(),critical = 0;
		int def_rate = 1000;

		if(psp->GetNumber() == 17){
			//---双扇打
			def_rate = 0;
		}

		//---武器に応じて追加効果
		crbatDoAction_AddWeaponEfectBefore(pDamageInfo,&rate,&def_rate,pChara,weapon);
		crbatCalcDamage(
			pDamageInfo,pChara,
			SRC_WEAPON,rate,
			DST_DEFENSE,def_rate,
			CALCMODE_ADD,500,
			psp->GetDamageDiffuse(),//---分散（１／１０００単位）
			weapon ? critemGetItemClass(weapon)->GetElement() : ELEMENT_PHYSICS,//---武器属性
//			ELEMENT_PHYSICS,
			PROBMODE_REAL | prob,pChara->GetBtHitProb(pChara->Command.Sub[0]),//---武器命中回避率、命中率
			DEFENSEMODE_REAL
			);

		//---アニメーション
		crbatDoAnime_Weapon(pChara,pDamageInfo,critical);
		//---武器に応じて追加効果
		crbatDoAction_AddWeaponEfectAfter(pDamageInfo,pChara,weapon);

		//---ダメージ表示
		crbatShowDamage(pDamageInfo);

		//---ダメージ結果加算
		crbatResultDamage(pDamageInfo);

		//---ダメージ結果表示
		crbatShowResult();
	}

	return 1;
}

//---笑撃波
CRBATMAIN_API int crbatDoAction_SpecialShogekiha(CrSpecial *psp,
						CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int EnableCounter,int mode)
{
	int a;

	//---ターゲットがいなかったら
	if(pChara->Command.Target == 0){
		return 0;
	}
	//---物理行動がとれなかったら
	if(!pChara->IsEnableMoveing()){
		return 0;
	}

	if(pDamageInfo->pList[0] != NULL){
		//---衝突補正でターゲットが変わったときのための
		//---キャラクターアングル再設定
		pDamageInfo->pList[0]->SetAngle(
			ANGLE(180) + pChara->GetCharaAngle(pDamageInfo->pList[0])
			);
	}

	if(mode == 16){
		//---ナック！
		for(a = 0;a < MEMBER_MAX;a ++){
			if(pBtChara[a].DoExist()
				&& !pBtChara[a].IsDown()){
				//---気絶してない
				if(pBtChara[a].Who() == 6){
					//---ライゼルがいたら、強化
					pBtChara[a].AddBtStatus(BTST_EXTEND,1);
				}
			}
		}
	}
	for(a = 0;pDamageInfo->pList[a] != NULL;a ++){
		//---補助ダメージ登録
		if(pDamageInfo->pList[a]->Command.Main == BAT_COMMAND_ENEMYABILITY
			&& pDamageInfo->pList[a]->Command.Sub[0] == BAT_ECOM_CR_HENSHIN){
			//---変身
			continue;
		}
		if(pDamageInfo->pList[a]->BattleInfo.Enemy.Graphic == 223
			&& crbatGetTurn() == 1){
			//---人間クレイシヴ・２ターン目
			continue;
		}
		if(pDamageInfo->pList[a]->GetBtStatus() & BTST_WORLD){
			//---ワールドだったら
			continue;
		}

		pDamageInfo->pList[a]->Command.Main = BAT_COMMAND_SKIP;
	}
	for(a = 0;a < BATTLECHARA_MAX;a ++){
		if(pBtChara[a].DoExist() == 0
			&& pBtChara[a].DoExistExtend()){
			//---拡張存在も消す
			pBtChara[a].Command.Main = BAT_COMMAND_SKIP;
		}
	}

	eiTextureCell tex;
	float range = 0;

	tex.ReadFile(CR_DATADIR4"warai.acf",CR_DATAFILE4,crdataGetFileMode());
	tex.Init(16);
	tex.Load();

	eiD3DMaterial material;
	material.Create();
	material.SetDeffuseColor(255,127,127,192);
	material.SetEmissiveColor(96,0,0,127);
	material.Set();

	int flag = 1,c,dst_count = 50;

	for(a = 0;a < dst_count;a ++){
		if(mode == 26){
			//---衝撃波
			pBtObject[a].CreateTLVertexRect(64,64);
		} else {
			//---お師匠さまの教え
			pBtObject[a].CreateTLVertexRect(32,32);
		}

		pBtObject[a].SetPos(
			(float)(pChara->GetFieldX()),
			(float)(pChara->GetFieldY())
			,
			0.2f
			);
		pBtObject[a].SetDrawMode(1);
		pBtObject[a].SetTexture(&tex);
		pBtObject[a].SetMoveVectorXYZ(
			(float)(eiRnd(1000) - 500) / 500.0f,
			(float)(eiRnd(1000) - 500) / 500.0f,
			0.01f + (float)eiRnd(1000) / 2000.0f 
		);
		pBtObject[a].SetMoveSpeed(0.1f);
		pBtObject[a].SetAlphaMode(1);
		pBtObject[a].SetXRate(1.0f);
		pBtObject[a].SetYRate(1.0f);
	}

	int t;
	float addw = 0;
	eiTime let;
	let.Reset();

	crsoundPlay(CRSOUND_HYURURIRA);
	while(flag){
		et->Reset();
		t = let.Get();

		crbatClearDrawingList();
		crbatAddDrawingListAll();

		if(t > 1500){
			flag = 0;
		}

		for(c = 0;c < dst_count;c ++){
			pBtObject[c].Move(addw);
			crbatAddDrawingList(&pBtObject[c],0,1);
		}
		crbatDrawScene();

crdataEnableRec(1);
		if(eiGetEndThread()){
			break;
		}
		crbatDrawRefresh();

		addw = (float)et->Get() / 10.0f;
	}

	for(c = 0;c < dst_count;c ++){
	}
	tex.ReleaseTexture();
	material.Release();

	crbatClearDrawingList();
	crbatAddDrawingListAll();

//	crbatDrawSceneWhile(750);
	if(pChara->GetNumber() < BATTLECHARA_PARTY_MAX){
		crbatBWCreate(pWin,"敵はあまりの寒さに動きを止めた！",BW_TOP | BW_CENTER);
	} else {
		crbatBWCreate(pWin,"あまりの寒さに動きを止められた！",BW_TOP | BW_CENTER);
	}
	crbatDrawSceneWhile(750);
/*	//---アニメーション
	crbatDoAnime_Weapon(pChara,pDamageInfo,critical);

	//---ダメージ表示
	crbatShowDamage(pDamageInfo);

	//---ダメージ結果加算
	crbatResultDamage(pDamageInfo);

	//---ダメージ結果表示
	crbatShowResult();*/

	return 1;
}

//---ホーリークロス
CRBATMAIN_API int crbatDoAction_SpecialHoriCross(CrSpecial *psp,
						CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin)
{
	int a;

	//---ターゲットがいなかったら
	if(pChara->Command.Target == 0){
		return 0;
	}
	//---物理行動がとれなかったら
	if(!pChara->IsEnableMoveing()){
		return 0;
	}

	if(pDamageInfo->pList[0] != NULL){
		//---衝突補正でターゲットが変わったときのための
		//---キャラクターアングル再設定
		pDamageInfo->pList[0]->SetAngle(
			ANGLE(180) + pChara->GetCharaAngle(pDamageInfo->pList[0])
			);
	}

	for(a = 0;pDamageInfo->pList[a] != NULL;a ++){
		//---補助ダメージ登録
		if(pDamageInfo->pList[a]->GetLP() >= 0){
			pDamageInfo->pList[a]->SetAbility(BTAB_P_KAIFUKU2,1);
		}
	}

//	crbatDrawSceneWhile(250);
	crbatDoAnime_Magic(pChara,pDamageInfo,11);
//	crbatDrawSceneWhile(750);
	crbatBWCreate(pWin,"ＭＣ回復量が増加",BW_TOP | BW_CENTER);
	crbatDrawSceneWhile(750);

/*	//---アニメーション
	crbatDoAnime_Weapon(pChara,pDamageInfo,critical);

	//---ダメージ表示
	crbatShowDamage(pDamageInfo);

	//---ダメージ結果加算
	crbatResultDamage(pDamageInfo);

	//---ダメージ結果表示
	crbatShowResult();*/

	return 1;
}

CRBATCPU_API ei_s32 crbatCPUThink_ReverseRange(ei_s32 target);

//---カウンターゲート
CRBATMAIN_API int crbatDoAction_SpecialCounterGate(CrSpecial *psp,
						CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin)
{
	int a;

	//---ターゲットがいなかったら
	if(pChara->Command.Target == 0){
		return 0;
	}
	//---魔法がつかえなかったら
	if(!pChara->IsEnableMagic()){
		return 0;
	}

	for(a = 0;pDamageInfo->pList[a] != NULL;a ++){
		//---補助ダメージ登録
		if(pDamageInfo->pList[a]->GetLP() >= 0){
			pDamageInfo->pList[a]->AddBtStatus(BTST_COUNTERGATE);
			//---ワールド属性
			pChara->AddBtStatus(BTST_WORLD);
			if(!pChara->GetWorldTurn())
				pChara->SetWorldTurn(1);
		}
	}

	int magic = pChara->Command.Sub[0];
	CrMagic *pMagic = crmagicGetMagicClass(magic);

	int use_mc = pMagic->GetMC();
	if(pChara->GetMC() < use_mc)
		use_mc = pChara->GetMC();
	pChara->AddMC(-use_mc);
	pChara->Command.Sub[CRBAT_SUBTARGET] = 0;

	if(pChara->GetNumber() < BATTLECHARA_STARTENEMY)
		pChara->Command.Range = pMagic->GetTarget(0) | pMagic->GetRange(0);
	else
		pChara->Command.Range = crbatCPUThink_ReverseRange(pMagic->GetTarget(0) | pMagic->GetRange(0))
		| crmagicGetMagicClass(magic)->GetRange(0);


	//---画面更新
	crbatShowStatus();

	crbatDoAnime_Magic(pChara,pDamageInfo,11);
	crbatBWCreate(pWin,"強い魔力障壁が張られた",BW_TOP | BW_CENTER);
	crbatDrawSceneWhile(750);

	//---ＭＣ回復しないように！
	pChara->ResetMagicTime();

	return 1;
}

//---スマイル
CRBATMAIN_API int crbatDoAction_SpecialSmile(CrSpecial *psp,
						CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin)
{
	int a;

	//---ターゲットがいなかったら
	if(pChara->Command.Target == 0){
		return 0;
	}
	//---物理行動がとれなかったら
	if(!pChara->IsEnableMoveing()){
		return 0;
	}

	crbatBWCreate(pWin,"ユミは微笑んだ",BW_TOP | BW_CENTER);
	crbatDrawSceneWhile(750);

	for(a = 0;pDamageInfo->pList[a] != NULL;a ++){
		//---補助ダメージ登録
		//---麻痺
		pDamageInfo->pList[a]->AddBtStatus(BTST_MAHI);
	}
	crbatClearDrawingList();
	crbatAddDrawingListAll();
	crbatDrawSceneWhile(750);


	return 1;
}

//---光の雫
CRBATMAIN_API int crbatDoAction_SpecialHikari(CrSpecial *psp,
						CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin)
{
	int a;

	//---ターゲットがいなかったら
	if(pChara->Command.Target == 0){
		return 0;
	}
	//---物理行動がとれなかったら
	if(!pChara->IsEnableMoveing()){
		return 0;
	}

	crbatBWCreate(pWin,"光の雫",BW_TOP | BW_CENTER);

	crbatSetDamageMode(pDamageInfo,DAMAGEMODE_ADD);
	for(a = 0;pDamageInfo->pList[a] != NULL;a ++){
		pDamageInfo->Damage[a] = 
			pDamageInfo->pList[a]->GetMaxLP();// - pDamageInfo->pList[a]->GetLP();
	}

	crbatDoAnime_Magic(pChara,pDamageInfo,1);

	//---ダメージ表示
	crbatShowDamage(pDamageInfo);

	//---ダメージ結果加算
	crbatResultDamage(pDamageInfo);

	//---ダメージ結果表示
	crbatShowResult();

	return 1;
}

//---彗零星
CRBATMAIN_API int crbatDoAction_SpecialSuireisei(CrSpecial *psp,
						CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin)
{
	int a;

	//---ターゲットがいなかったら
	if(pChara->Command.Target == 0){
		return 0;
	}
	//---物理行動がとれなかったら
	if(!pChara->IsEnableMoveing()){
		return 0;
	}

	crbatBWCreate(pWin,"彗零星",BW_TOP | BW_CENTER);

	crbatSetDamageMode(pDamageInfo,DAMAGEMODE_ADDMC);
	for(a = 0;pDamageInfo->pList[a] != NULL;a ++){
		pDamageInfo->Damage[a] = pDamageInfo->pList[a]->GetMaxMC();
	}

	crbatDoAnime_Magic(pChara,pDamageInfo,1);

	//---ダメージ表示
	crbatShowDamage(pDamageInfo);

	//---ダメージ結果加算
	crbatResultDamage(pDamageInfo);

	//---ダメージ結果表示
	crbatShowResult();

	return 1;
}

//---必殺技
CRBATMAIN_API int crbatDoAction_Special(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin)
{
	int index = pChara->Command.Sub[3];
	CrSpecial *psp = &pSpecialInfo[index];

	//---ターゲットがいなかったら
	if(pChara->Command.Target == 0){
		return 0;
	}
	//---物理行動がとれなかったら
	if(!(index == 3 || index == 4)){
		if(!pChara->IsEnableMoveing()){
			return 0;
		}
	}

	//---InfoWindowを作る
	crbatBWCreate(pWin,psp->GetName(),BW_TOP | BW_CENTER);
	//---バトルヒストリープラス
	pChara->HistoryAddAction(BTHISTORY_SPECIAL);

	if(index == 4){
		//---カウンター・ゲート
		crbatDoAction_SpecialCounterGate(psp,pDamageInfo,pChara,
			pWin);
	} else if(psp->GetCommandType() == 0 && psp->GetNumber() == 15){
		//---ロックオン・ダブル
		crbatDoAction_SpecialAtack_Double(psp,pDamageInfo,pChara,
			pWin,0,0,
			index);
	} else if(psp->GetCommandType() == 0){
		//---武器攻撃
		crbatDoAction_SpecialAtack(psp,pDamageInfo,pChara,
			pWin,0,0,
			index);
	} else if(psp->GetCommandType() == 1){
		//---魔法
		crbatDoAction_Magic(pDamageInfo,pChara,pWin,psp->GetDamageRate());
	} else {
		if(index == 26 || index == 16){
			//---しょうげきは！、教え
			crbatDoAction_SpecialShogekiha(psp,pDamageInfo,pChara,
				pWin,0,index);
		} else if(index == 5){
			//---彗零星
			crbatDoAction_SpecialSuireisei(psp,pDamageInfo,pChara,pWin);
		} else if(index == 18){
			//---ホーリークロス
			crbatDoAction_SpecialHoriCross(psp,pDamageInfo,pChara,pWin);
		} else if(index == 19){
			//---光の雫
			crbatDoAction_SpecialHikari(psp,pDamageInfo,pChara,pWin);
		} else if(index == 23){
			//---スマイル
			crbatDoAction_SpecialSmile(psp,pDamageInfo,pChara,pWin);
		}
	}

	//---硬直ターンを指定し、ヒストリーをクリア
	if(index != 4){
		//---カウンターゲート以外、条件クリア
		pChara->SetSpecialDisable(psp->GetDisableTurn() + 1);
		pChara->SpecialClearHistory();
	}

	return 1;
}

