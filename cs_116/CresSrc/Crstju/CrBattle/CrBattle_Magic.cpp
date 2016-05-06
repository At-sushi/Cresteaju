/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBattle_Magic.cpp ...Battle Magic functions

-----------------------------------------------------------*/

#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBATTLE_MAGIC

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#define EXTERN_CRBATTLE
#include "..\CrBase.h"
#include "..\CrBattle.h"

#define CR_GAMEINFO_EXTERNPOINTER
#include "..\CrGameInfo.h"

//---補助魔法を影響させる
CRBATMAGIC_API void crbatEfectSubMagic(CrBattleCharacter *pSrcChara,int magic,CR_BATTLE_DAMAGEINFO *pDamageInfo,int kaos)
{
	CrBattleCharacter *pChara;
	CrBattleCharacter **ppList = &pDamageInfo->pList[0];
	int a,count,orora = 0;

	for(count = 0; *ppList ;ppList ++,count ++){
		pChara = ppList[0];
		if(pDamageInfo->Damage[count]){
			//---当たってれば
			switch(magic){
			//---スリーピング
			case 11:
				pChara->AddBtStatus(BTST_NEMURI,kaos);
				break;
			//---ディストーション
			case 12:
				pChara->AddBtStatus(BTST_DIST,kaos);
				break;
			//---プロテクション
			case 13:
				pChara->AddBtStatus(BTST_PROTECT,kaos);
				break;
			//---ダークミスト
			case 14:
				pChara->AddBtStatus(BTST_KURAYAMI,kaos);
				break;
			//---サイレンス
			case 15:
				pChara->AddBtStatus(BTST_CHINMOKU,kaos);
				break;
			//---アクセラレイション
			case 16:
				pChara->AddBtStatus(BTST_ACCEL,kaos);
				break;
			//---フォースシールド
			case 17:
				pChara->AddBtStatus(BTST_FSHIELD,kaos);
				break;
			//---コンフュージョン
			case 18:
				pChara->AddBtStatus(BTST_KONRAN,kaos);
				break;
			//---パワーブースト
			case 19:
				pChara->AddBtStatus(BTST_POWER,kaos);
				break;
			//---インフルエンス
			case 20:
				pChara->AddBtStatus(BTST_JAKUKA,kaos);
				break;
			//---デスフォース
			case 21:
/*				pChara->ResultLP(-pChara->GetLP());
//				pChara->SetLP(0);
				//---気絶回数
				pChara->HistoryAddDeathCount();*/
				if(crbatGetBattleMagicMode() == 1){
					//---マジックモードが１なら
					if(eiRnd(1000) < 500)
						continue;
				}
				pChara->Sokushi();
				break;
			//---エクステンド
			case 22:
				pChara->AddBtStatus(BTST_EXTEND,kaos);
				break;
			//---オーロラテイル
			case 23:
				if(eiRnd(1000) < 500){
					orora ++;
					pChara->AddBtStatus(BTST_NEMURI,kaos);
				}
				if(eiRnd(1000) < 500){
					orora ++;
					pChara->AddBtStatus(BTST_CHINMOKU,kaos);
				}
				if(eiRnd(1000) < 700){
					orora ++;
					pChara->AddBtStatus(BTST_KURAYAMI,kaos);
				}
				if(eiRnd(1000) < 600){
					orora ++;
					pChara->AddBtStatus(BTST_KONRAN,kaos);
				}
				if(eiRnd(1000) < 400){
					orora ++;
					pChara->AddBtStatus(BTST_ZERO,kaos);
				}
				if(eiRnd(1000) < 300){
					orora ++;
					pChara->AddBtStatus(BTST_MAHI,kaos);
				}
				if(eiRnd(1000) < 250){
					orora ++;
					pChara->AddBtStatus(BTST_JAKUKA,kaos);
				}
/*				if(eiRnd(1000) < 100){
					orora ++;
					if(!pChara->Ability(BTST_SOKUSHI)){
						pChara->SetLP(0);
						//---気絶回数
						pChara->HistoryAddDeathCount();
					}
				}*/
				if(orora == 0){
					pChara->AddBtStatus(BTST_NEMURI,kaos);
				}
//				pChara->AddBtStatus(BTST_REFLECT);
/*				{
					ei_s32 temp = pChara->GetLP();
					pChara->SetLP(pChara->GetMC());
					pChara->SetMC(temp);
				}*/
				break;
			//---ワールド
			case 24:
				pChara->AddBtStatus(BTST_WORLD);
				//---カオスターン分だけもつ
//				pChara->SetWorldTurn(1 + pSrcChara->GetKaosTurn());
				pChara->SetWorldTurn(1);
				break;
			//---インバリディティ
			case 25:
				//---いいステータスを消す
				for(a = 16;a < 32;a ++){
//					if(((1 << a) & BTST_KAOS) == 0){
						pChara->ClearBtStatus(1 << a);
						pChara->ResetKaosTurn();
//					}
				}
/*				if(pChara->GetBtStatus() & BTST_KAOS){
					//---カオスワード
					if(pChara->GetKaosTurn() == 1){
						pChara->ClearBtStatus(BTST_KAOS);
						pChara->ResetKaosTurn();
					} else {
						pChara->OnlyInfo.KAOSTurn --;
					}
				}*/
				break;
			//---ソウルセンス
			case 26:
				pChara->AddBtStatus(BTST_SOUL,kaos);
				break;
			//---カオスワード
			case 27:
				pChara->AddBtStatus(BTST_KAOS);
				pChara->AddKaosTurn();
				break;
			//---マーキング
			case 28:
				pChara->AddBtStatus(BTST_HYOTEKI);
				break;
			//---リージョン
			case 29:
				break;
			//---ゼロシールド
			case 30:
				pChara->AddBtStatus(BTST_ZERO,kaos);
				break;
			//---パラライズ
			case 31:
				pChara->AddBtStatus(BTST_MAHI,kaos);
				break;
			}
		}
	}

	if(magic == 21){
		CR_BATTLE_DAMAGEINFO info;
		CrBattleCharacter **ppList = &pDamageInfo->pList[0];

		memcpy(&info,pDamageInfo,sizeof(info));
		for(count = 0; *ppList ;ppList ++,count ++){
			info.Damage[count] = 0;
			info.DamageMode[count] = DAMAGEMODE_SUB;
		}

		crbatResultDamage(&info);
	}
}

//---魔法
CRBATMAGIC_API int crbatDoAction_Magic(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int ext_rate /*= 1000*/,int refrection /*= 1*/)
{
	int a;

	//---ターゲットがいなかったら
	if(pChara->Command.Target == 0){
		return 0;
	}
	if(!pChara->IsEnableMagic()){
		//---魔法行動がとれなかったら
		return 0;
	}

	//---ターゲットがもう倒れてたら
	CrBattleCharacter *pDst = (CrBattleCharacter *)pChara->Command.Target;
	if(!pDst->DoExist()){
		return 0;
	}

	int magic = pChara->Command.Sub[0],mode = pChara->Command.Sub[CRBAT_SUBTARGET];
	CrMagic *pMagic = crmagicGetMagicClass(magic);

	//---魔法名表示
	crbatBWCreate(pWin,
		pMagic->GetName(),
		BW_TOP | BW_CENTER);

	//---魔法カウンターリセット
	pChara->ResetMagicTime();

/*	if(refrection){
		int find = -1;

		for(a = 0;pDamageInfo->pList[a] != NULL;a ++){
			if(pChara == pDamageInfo->pList[a]
				&& pChara->GetBtStatus() & BTST_REFLECT){
				//---自分自身にかけていたら、誰かに飛ばす
				int list = 0;
				CrBattleCharacter *ptemp[BATTLECHARA_MAX];
				memset(ptemp,0,sizeof(ptemp));

				for(b = 0;b < BATTLECHARA_MAX;b ++){
					if(pBtChara[b].DoExist()){
						//---bのキャラが、ダメージリストにあるかどうか調べる
						for(c = 0;pDamageInfo->pList[c] != NULL;c ++){
							if(pDamageInfo->pList[c] == &pBtChara[b]){
								break;
							}
						}
						if(pDamageInfo->pList[c] == NULL){
							//---ダメージリストになかったらリストに追加
							ptemp[list] = pDamageInfo->pList[c];
							list ++;
						}
					}
				}
				if(list){
					//---代わり
					pDamageInfo->pList[a] = ptemp[eiRnd(list)];
				} else {
					eiMsgBox("k");
				}
			}
		}

		for(a = 0;pDamageInfo->pList[a] != NULL;a ++){
			if(pDamageInfo->pList[a]->GetBtStatus() & BTST_REFLECT){
				for(b = a;pDamageInfo->pList[b] != NULL;b ++){
				}

				if(pChara != pDamageInfo->pList[a]

				pDamageInfo->pList[b] = pChara;
				pDamageInfo->pList[b + 1] = NULL;
				find = b;
				break;
			}
		}
	}*/

	//-----------------------------------
	int world = crmagicGetMagicClass(24)->GetMC();
	for(a = 0;a < pChara->GetWorldCountTurn();a ++){
		crmagicGetMagicClass(24)->MagicInfo.UseMC += world;
	}

	int use_mc = pMagic->GetMC();

	crmagicGetMagicClass(24)->MagicInfo.UseMC = world;


	if(pChara->GetBtStatus() & BTST_COUNTERGATE){
		//---カウンターゲートなら使用しない
		use_mc = 0;
	}

	if(pChara->GetMC() < use_mc){
		//---ＭＣが足りない！！
		//---魔法表示
		crbatDrawScene();
		crbatDrawRefresh();
//		ew->Refresh();
		et->Delay2(750);
		//---ＭＣが足りない！表示
		crbatSetDrawSceneCallback(NULL);
		CrStringWindow InfoWindow(BATTLE_INFOWINDOW_FONT,CRWIN_BGFILL);

		InfoWindow.SetType(CRWIN_TYPE_NORMAL);
		crbatBWCreate(&InfoWindow,"ＭＣが足りない！",BW_CENTER | BW_TOP);
		crbatDrawScene();
		InfoWindow.Paint();
		InfoWindow.Reset();
		InfoWindow.DrawLastString();
//		crbatDrawScene();
//		crbatDrawRefresh();
		ew->Refresh();
		et->Delay2(750);
		return 0;
	} else {
		//---使用ＭＣをひく
		pChara->AddMC(-use_mc);
		//---画面更新
		crbatShowStatus();
		crbatDrawScene();
//		ew->Refresh();

		//---バトルヒストリープラス
		pChara->HistoryAddAction(BTHISTORY_MAGIC);
		pChara->HistoryAddUseMC(pMagic->GetMC());

		int kaos = 1,rate;

		for(a = 0;a < pChara->GetKaosTurn() && a < 256;a ++){
//			kaos = kaos * 2;
			kaos ++;
		}
/*		char s[80];
		sprintf(s,"%d",kaos);
		eiMsgBox(s);*/
		//---カオスワードリセット
		if(magic != 27){
			//---カオスワードでなければ
			pChara->ClearBtStatus(BTST_KAOS);
			pChara->ResetKaosTurn();
		}

		if(pMagic->GetKind() == MAGICKIND_DAMAGE){
			//---ダメージ計算
			//---攻撃値、防御値、計算方法、属性
			int prob_mode = PROBMODE_MAGIC,prob = pMagic->GetHitProb();

			//---回復かダメージか？
			if(pMagic->GetElement() == ELEMENT_RECOVERY){
				//---回復魔法
				crbatSetDamageMode(pDamageInfo,DAMAGEMODE_ADD);
				prob_mode = PROBMODE_100;
				prob = 1000;
				if(pChara->Ability(BTAB_S_KAIFUKUMAGIC_P)){
					prob = 1200;
				}
				prob = (prob * ext_rate) / 1000;

				rate = (prob)
						* (pChara->GetMagicRate(pMagic->GetLevel()) / 1000);
				rate = rate * kaos;
				if(rate <= 0)
					rate = 999999999;
				if(rate > 999999999)
					rate = 999999999;

				if(magic == 4){
					//---リザレクション
					pDamageInfo->Damage[0] = pDamageInfo->pList[0]->GetMaxLP();
					if(pDamageInfo->pList[0]->GetLP() <= 0){
						pDamageInfo->Damage[0] += (-pDamageInfo->pList[0]->GetLP());
					}
					if(pDamageInfo->pList[0]->GetLP() > 0){
						//---気絶してなかったら最大ＬＰの１／１０
						pDamageInfo->Damage[0] = pDamageInfo->pList[0]->GetMaxLP() / 10;
					}
				} else if(magic == 2){
					//---キュアー
					pDamageInfo->pList[0]->CureStatus();
				} else if(magic == 6){
					//---リカバリー３
					pDamageInfo->Damage[0] = pDamageInfo->pList[0]->GetMaxLP();
					if(pDamageInfo->pList[0]->IsKizetu()){
						//---気絶中
						pDamageInfo->Damage[0] = pDamageInfo->pList[0]->GetMaxLP() / 10;
					}
				} else {
//					prob = (prob * ext_rate) / 1000;
					crbatCalcDamage(
						pDamageInfo,pChara,
						SRC_DIRECT,rate,//prob,
						DST_DIRECT,0,
						CALCMODE_ADD,crmagicGetBaseValue(magic,pChara),//pMagic->GetDamage(),
						pMagic->GetDiffuse(),//---分散（１／１０００単位）
						pMagic->GetElement(),
						PROBMODE_MAGIC,pChara->GetBtMagicHitProb(pMagic),
						/*pMagic->GetHitProb(),*///---武器命中回避率、命中率
						DEFENSEMODE_REAL | DEFENSEMODE_MAGIC
						);
				}
			} else {
				//---攻撃魔法
				prob = (prob * ext_rate) / 1000;
				crbatSetDamageMode(pDamageInfo,DAMAGEMODE_SUB);
				for(a = 1;pDamageInfo->pList[a] != NULL;a ++){
					//---補助ダメージ登録
					pDamageInfo->DamageRate[a] = (pMagic->GetSubDamage() * ext_rate) / 1000;
				}

				rate = ((pMagic->GetDamage() * ext_rate / 1000)
						* pChara->GetMagicRate(pMagic->GetLevel()) / 1000)
						/ (mode == 0 ? 1 : 2);//---サブ範囲だったら威力半減
				rate = rate * kaos;
				if(rate <= 0)
					rate = 999999999;
				if(rate > 999999999)
					rate = 999999999;

				int src_mode = SRC_MAGIC,dst_mode = DST_MAGDEF,
					def_mode = DEFENSEMODE_REAL | DEFENSEMODE_MAGIC,
					src_rate = 1000,dst_rate = 1000,
					magic_prob = pChara->GetBtMagicHitProb(pMagic);
				prob_mode = PROBMODE_MAGIC;

				if(magic == 79){
					//---ルーイン
					rate = pChara->GetRuinDamage();
//					prob_mode = PROBMODE_100;
					src_mode = SRC_DIRECT;
					dst_mode = DST_NONE;
					src_rate = 1000;//pChara->GetMaxLP() - pChara->GetLP();//GetRuinDamage();
//					dst_rate = 0;
//					rate = 1000;

					pChara->ResetRuinDamage();
				}

				crbatCalcDamage(
					pDamageInfo,pChara,
					src_mode,src_rate,
					dst_mode,dst_rate,
					CALCMODE_MULTI/*ADD*/,rate,

					pMagic->GetDiffuse(),//---分散（１／１０００単位）
					pMagic->GetElement(),
					prob_mode,pChara->GetBtMagicHitProb(pMagic),
					def_mode
					);
			}

			//---アニメーション
			crbatDoAnime_Magic(pChara,pDamageInfo,0);
			if(magic != 2){
				//---キュアーでなければ
				//---ダメージ表示
				crbatShowDamage(pDamageInfo);
				//---ダメージ結果加算
				crbatResultDamage(pDamageInfo);
			}
		} else {
			int magic_status[] = {
				0,0,0,0,0, 0,0,0,0,0,
				0,BTST_NEMURI,BTST_PULS,BTST_PULS,BTST_KURAYAMI,
				BTST_CHINMOKU,BTST_PULS,BTST_PULS,BTST_KONRAN,BTST_PULS,
				BTST_JAKUKA,BTST_SOKUSHI,BTST_PULS,BTST_PULS,BTST_PULS,
				BTST_INVAL,BTST_PULS,BTST_PULS,BTST_HYOTEKI,0,
				BTST_ZERO,BTST_MAHI,0,0,0
			};
			int prob_mode;

			//---月光唱か、カオスワードならなら必ず効く
			if(ext_rate > 1000)// || kaos > 1)
				prob_mode = PROBMODE_100;
			else
				prob_mode = PROBMODE_MAGIC;

			if(magic == 24){
				//---ワールド
				pChara->AddWorldCountTurn(1);
			}

			//---補助魔法
			crbatCalcDamage(
				pDamageInfo,pChara,
				SRC_LEVEL,1000,
				DST_LEVEL,1000,
				CALCMODE_PROB,pMagic->GetDamage() / (mode == 0 ? 1 : 2),
				0,//---分散（１／１０００単位）
				magic_status[magic],
//				pMagic->GetElement(),
				prob_mode/*PROBMODE_MAGIC*/,pMagic->GetHitProb(),//---武器命中回避率、命中率
				DEFENSEMODE_MAGIC
				);

			//---アニメーション
			crbatDoAnime_Magic(pChara,pDamageInfo,0);
			//---状態変化
			crbatEfectSubMagic(pChara,magic,pDamageInfo,kaos);
			//---ダメージ表示
			crbatShowDamage(pDamageInfo);
		}
		//---ダメージ結果表示
		crbatShowResult();
	}

/*	if(magic != 27){
		//---カオスワード以外だったら使用者のカオスワードクリア
		pChara->ClearBtStatus(BTST_KAOS);
		pChara->ResetKaosTurn();
	}*/

	return 1;
}
