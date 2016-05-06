/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBattle_CPU.cpp ...Battle CPU Thinking functions

-----------------------------------------------------------*/

#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBATTLE_CPU

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#define EXTERN_CRBATTLE
#include "..\CrBase.h"
#include "..\CrBattle.h"

#define CR_GAMEINFO_EXTERNPOINTER
#include "..\CrGameInfo.h"

#define BATSORT_DIST 0
#define BATSORT_LP 1
#define BATSORT_MC 2

CRBATCPU_API void crbatCPU_SortList(CrBattleCharacter *pChara,CrBattleCharacter **ppList,int size,int mode,int dir)
{
	int a,b,flag;
	double now,next;
	CrBattleCharacter *pTemp;

	for(a = 0,flag = 1;a < size && flag;a ++){
		now = next = 0;
		flag = 0;
		for(b = 0;b < size - 1;b ++){
			if(mode == BATSORT_DIST){
				now = ppList[b]->GetDistance(pChara);
				next = ppList[b + 1]->GetDistance(pChara);
			} else if(mode == BATSORT_LP){
				now = (double)ppList[b]->GetLP() / (double)ppList[b]->GetMaxLP();
				next = (double)ppList[b + 1]->GetLP() / (double)ppList[b + 1]->GetMaxLP();
			}

			if((dir == 0 && now > next)
				|| (dir == 1 && now < next)){
				//---スワップ
				pTemp = ppList[b + 1];
				ppList[b + 1] = ppList[b];
				ppList[b] = pTemp;
				flag ++;
			}
		}
	}
}

//---防御
CRBATCPU_API void crbatCPUThink_SetDefense(CrBattleCharacter *pChara,int mode,int x = -1,int y = -1)
{
	int def_table[] = {BAT_SUBCOM_DEFENSE,BAT_SUBCOM_AVOID,
		BAT_SUBCOM_MAGICDEFENSE,BAT_SUBCOM_MOVE};

	pChara->Command.Main = BAT_COMMAND_DEFENSE;
	pChara->Command.Sub[0] = def_table[mode];

	if(mode == 3){
		//---移動
		if(x == -1){
			if(pChara->GetFieldX() < 3){
				x = pChara->GetFieldX() + eiRnd(8);
			} else if(pChara->GetFieldX() >= 9){
				x = pChara->GetFieldX() - eiRnd(8);
			} else {
				x = pChara->GetFieldX() + eiRnd(9) - 5;
			}
			if(x < 0)
				x = 0;
			if(x >= BATTLEFIELD_MAX_X)
				x = BATTLEFIELD_MAX_X - 1;

			if(pChara->GetFieldY() < 3){
				y = pChara->GetFieldY() + eiRnd(8);
			} else if(pChara->GetFieldY() >= 9){
				y = pChara->GetFieldY() - eiRnd(8);
			} else {
				y = pChara->GetFieldY() + eiRnd(9) - 5;
			}
			if(y < 0)
				y = 0;
			if(y >= BATTLEFIELD_MAX_Y)
				y = BATTLEFIELD_MAX_Y - 1;
		}

		while(crbatIsThere(x,y,pChara)){
			if(++x >= BATTLEFIELD_MAX_X){
				x = 0;
				if(++y >= BATTLEFIELD_MAX_Y){
					y = 0;
				}
			}
		}
		pChara->Command.Sub[1] = x;
		pChara->Command.Sub[2] = y;
	}
}

//---ＡＩに応じてターゲット選択
CRBATCPU_API void crbatCPUThink_SetAITarget(CrBattleCharacter *pChara,int mode,
											int atack_type = 0,int include_minasLP = 0,
											int force_mode = -1)
{
	int size;
	CrBattleCharacter *pList[32];
	int a,point[32],sum = 0,hit,iq = pChara->BattleInfo.Enemy.IQ;

	if(force_mode != -1){
		iq = force_mode;
	}

	size = crbatMakeCharaList(&pList[0],pChara,mode,include_minasLP);

	switch(iq){
	case 0:
		pChara->SetTarget(crbatRandomSelect(pChara,mode,include_minasLP));
		break;
	case 1:
		//---近いやつから攻撃
		crbatCPU_SortList(pChara,pList,size,BATSORT_DIST,0);
		for(a = 0,sum = 0;a < size;a ++){
			point[a] = sum + (size - a);
			sum += (size - a);//point[a];
		}
		hit = eiRnd(sum);
		for(a = 0;a < size;a ++){
			if(hit < point[a]){
				pChara->SetTarget(pList[a]);
//				eiMsgBox(pList[a]->GetName());
				break;
			}
		}
/*char s[2000];
sprintf(s,"%s,%s %d,%d",pChara->GetName(),pList[a]->GetName(),hit,size);
eiMsgBox(s);*/
		break;

	case 2:
		//---一番近いやつから攻撃
		crbatCPU_SortList(pChara,pList,size,BATSORT_DIST,0);
		pChara->SetTarget(pList[0]);
		break;

	case 3:
		//---完全ランダム
		pChara->SetTarget(crbatRandomSelect(pChara,mode));
		break;
	case 4:
		//---ＬＰ低いのを狙う
		crbatCPU_SortList(pChara,pList,size,BATSORT_LP,0);
		for(a = 0,sum = 0;a < size;a ++){
			point[a] = sum + (size - a);
			sum += (size - a);
		}
		hit = eiRnd(sum);
		pChara->SetTarget(pList[0]);
		for(a = 0;a < size;a ++){
			if(hit < point[a]){
				pChara->SetTarget(pList[a]);
				break;
			}
		}
		break;
	case 5:
		//---ＬＰが一番低いのを狙う
		crbatCPU_SortList(pChara,pList,size,BATSORT_LP,0);
		pChara->SetTarget(pList[0]);
		break;
	default:
		pChara->SetTarget(crbatRandomSelect(pChara,mode,include_minasLP));
		break;
	}
}

//---ＡＩに応じたターゲットで通常攻撃をする
CRBATCPU_API void crbatCPUThink_SetAtack(CrBattleCharacter *pChara,int tartget = -1)
{
	pChara->Command.Main = BAT_COMMAND_WEAPON;
	pChara->Command.Range = BAT_TARGET_FRIENDSINGLE;
	pChara->Command.Sub[0] = 0;

	crbatCPUThink_SetAITarget(pChara,BAT_TARGET_FRIEND);
}

//---ＡＩに応じたターゲットで通常攻撃をする
CRBATCPU_API void crbatCPUThink_SetAtack2(CrBattleCharacter *pChara,int weapon,CrBattleCharacter *ptarget = NULL)
{
	pChara->Command.Main = BAT_COMMAND_WEAPON;
	pChara->Command.Range = BAT_TARGET_FRIENDSINGLE;
	pChara->Command.Sub[0] = 0;
	pChara->Command.Sub[0] = weapon;

	crbatCPUThink_SetAITarget(pChara,BAT_TARGET_FRIEND);
	pChara->Command.Target = (ei_u32)ptarget;
}

/*
//---防御
CRBATCPU_API void crbatCPUThink_SetDefense(CrBattleCharacter *pChara,
				int mode = 0,int x = 0,int y = 0)
{
	pChara->Command.Main = BAT_COMMAND_DEFENSE;
	pChara->Command.Range = 0;
	pChara->Command.Sub[0] = mode
	pChara->Command.Sub[1] = x;
	pChara->Command.Sub[2] = y;

	crbatCPUThink_SetAITarget(pChara,BAT_TARGET_FRIEND);
}
*/
//---ＡＩに応じたターゲットで特殊攻撃をする
CRBATCPU_API void crbatCPUThink_SetAbility(CrBattleCharacter *pChara,int ability,int sub = 0,
						CrBattleCharacter *pForceDst = NULL)
{
	pChara->Command.Main = BAT_COMMAND_ENEMYABILITY;
	pChara->Command.Sub[0] = ability;

	switch(ability){
		//---痛み分け
	case BAT_ECOM_ITAMIWAKE_JIZOKU:
	case BAT_ECOM_ITAMIWAKE_KAIJO:
		pChara->Command.Range = BAT_TARGET_FRIENDSINGLE;
		crbatCPUThink_SetAITarget(pChara,BAT_TARGET_FRIEND);
		//---強制ターゲット
		pChara->SetTarget(
			&pBtChara[pChara->GetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE_TAISHO)]);
		return;

	case BAT_ECOM_KARA:
		//---殻
		pChara->AddBtStatus(BTST_WORLD);
		pChara->SetWorldTurn(1);
		pChara->Command.Range = BAT_TARGET_ENEMYSINGLE;
		pChara->SetTarget(pChara);
	case BAT_ECOM_KOUGOUSEI:
	case BAT_ECOM_SAISEI:
	case BAT_ECOM_SEICHOU:
	case BAT_ECOM_TAMERU:
	case BAT_ECOM_BARRIERTENKAI:
	case BAT_ECOM_KASCADE_JUNBI:
	case BAT_ECOM_KASCADE_KYOKA:
	case BAT_ECOM_HANBUSSITU_JUNBI:
	case BAT_ECOM_KASCADE_SAIDAI:
	case BAT_ECOM_NERU:
	case BAT_ECOM_SABORU:
	case BAT_ECOM_TOSO:
	case BAT_ECOM_KIDOU:
	case BAT_ECOM_BOSOKAISHI:
	case BAT_ECOM_CR_HENSHIN:
	case BAT_ECOM_CR_RUINJUNBI:
	case BAT_ECOM_IKIWOSUIKOMU:
	case BAT_ECOM_KIDOSASERU:
		//---自分自身
		pChara->Command.Range = BAT_TARGET_ENEMYSINGLE;
		pChara->SetTarget(pChara);
		return;

	case BAT_ECOM_KYUKETSU:
		pChara->Command.Range = BAT_TARGET_FRIENDSINGLE;
		break;
	case BAT_ECOM_NAGURU:
	case BAT_ECOM_KAMITUKU:
	case BAT_ECOM_KIRIKAKARU:
	case BAT_ECOM_PIERUZAN:
	case BAT_ECOM_TOSSHIN:
	case BAT_ECOM_HAGESHIKU:
	case BAT_ECOM_TOKASU:
	case BAT_ECOM_CHISSOKU_1_10:
	case BAT_ECOM_CHISSOKU_1_5:
	case BAT_ECOM_BUNRETU:
	case BAT_ECOM_CHOUONPA:
	case BAT_ECOM_LPCHANGE:
	case BAT_ECOM_SEKKINATACK:
	case BAT_ECOM_IREBACRASH:
	case BAT_ECOM_SAN:
	case BAT_ECOM_RARFIAATACK:
	case BAT_ECOM_HANBUSSHITU:
	case BAT_ECOM_ITAMIWAKE:
	case BAT_ECOM_TABERU:
	case BAT_ECOM_820:
	case BAT_ECOM_MCBUNKAI:
	case BAT_ECOM_KYUKETUKEN:
	case BAT_ECOM_SETUDAN:
	case BAT_ECOM_RESERVE:
	case BAT_ECOM_CR_SINGLEKOGEKI:
		pChara->Command.Sub[3] = sub;//---ダメージ
		pChara->Command.Range = BAT_TARGET_FRIENDSINGLE;
		break;
	//---circle4
	case BAT_ECOM_SHINSHOKU:
	case BAT_ECOM_SILENTBANISHA:
	case BAT_ECOM_ROUOU:
		pChara->Command.Range = BAT_TARGET_FRIENDRANGE | BAT_RANGE_CIRCLE4;
		break;

	//---Line1
	case BAT_ECOM_EYEBEAM:
	case BAT_ECOM_MIZUDEPPOU:
		pChara->Command.Range = BAT_TARGET_FRIENDRANGE | BAT_RANGE_LINE1;
		pChara->Command.Sub[3] = sub;//---ダメージ
		break;
	//---Line2
	case BAT_ECOM_KAENHOUSHA:
	case BAT_ECOM_TAKISIDOBEAM:
	case BAT_ECOM_SINRYAKUHEI:
	case BAT_ECOM_DANDYSPRASHER:
	case BAT_ECOM_ONSOKU:
	case BAT_ECOM_SOKUSHIKOUSEN:
	case BAT_ECOM_JAKUKAKOSEN:
		pChara->Command.Range = BAT_TARGET_FRIENDRANGE | BAT_RANGE_LINE2;
		pChara->Command.Sub[3] = sub;//---ダメージ
		break;
	//---Line3
	case BAT_ECOM_MISTYBEAM:
	case BAT_ECOM_LAYZERBEAM:
		pChara->Command.Range = BAT_TARGET_FRIENDRANGE | BAT_RANGE_LINE3;
		pChara->Command.Sub[3] = sub;//---ダメージ
		break;
	//---Line4
	case BAT_ECOM_CR_LINEKOGEKI:
		pChara->Command.Range = BAT_TARGET_FRIENDRANGE | BAT_RANGE_LINE7;
		pChara->Command.Sub[3] = sub;//---ダメージ
		break;

	//---Circle3
	case BAT_ECOM_ENGETUZAN:
	case BAT_ECOM_HOSHOKU:
	case BAT_ECOM_SINRYAKUHEI_BOMB:
	case BAT_ECOM_DANDYSPARK:
	case BAT_ECOM_DIVIDING:
		pChara->Command.Sub[3] = sub;//---ダメージ
		pChara->Command.Range = BAT_TARGET_FRIENDRANGE | BAT_RANGE_CIRCLE3;
		break;
	case BAT_ECOM_JURIASGIRI:
		pChara->Command.Range = BAT_TARGET_FRIENDRANGE | BAT_RANGE_LINE3;
		break;
	case BAT_ECOM_SHOGEKIHA:
		pChara->Command.Range = BAT_TARGET_FRIENDRANGE | BAT_RANGE_LINE3;
		break;
	case BAT_ECOM_KAITENATACK:
	case BAT_ECOM_NAGITAOSU:
	case BAT_ECOM_TOTUGEKI:
		pChara->Command.Range = BAT_TARGET_FRIENDRANGE | BAT_RANGE_LINE3;
		break;
		//---ブレス系
	case BAT_ECOM_HONO:
	case BAT_ECOM_FUBUKI:
	case BAT_ECOM_TOPPU:
	case BAT_ECOM_SUNAARASHI:
	case BAT_ECOM_IKADUCHI:
	case BAT_ECOM_MODOKUNOIKI:

	case BAT_ECOM_RIBONTUISTA:
		pChara->Command.Range = BAT_TARGET_FRIENDRANGE | BAT_RANGE_CIRCLE4;
		pChara->Command.Sub[3] = sub;//---ダメージ
		break;

	case BAT_ECOM_CRFUBUKI:
		pChara->Command.Range = BAT_TARGET_FRIENDRANGE | BAT_RANGE_CIRCLE4;
		pChara->Command.Sub[3] = sub;//---ダメージ
		break;

	//---ALL
	case BAT_ECOM_HONO2:
	case BAT_ECOM_FUBUKI2:
	case BAT_ECOM_TOPPU2:
	case BAT_ECOM_SUNAARASHI2:
	case BAT_ECOM_IKADUCHI2:
	case BAT_ECOM_DAIKONRAN:
	case BAT_ECOM_DAIKAEN:

	case BAT_ECOM_HANBUSSHITU_ZENTAI:
	case BAT_ECOM_AKUBI:
		pChara->Command.Range = BAT_TARGET_FRIENDALL;
		pChara->Command.Sub[3] = sub;//---ダメージ
		break;
	//---特殊攻撃系
	case BAT_ECOM_HOUSHI:
	case BAT_ECOM_SILENTBREATH:
	case BAT_ECOM_SLEEPBREATH:
	case BAT_ECOM_POISON:
	case BAT_ECOM_NEMURINOKONA:
	case BAT_ECOM_DARUDARUHA:
	case BAT_ECOM_KAFUN:
	case BAT_ECOM_SANSEIU:
		pChara->Command.Range = BAT_TARGET_FRIENDRANGE | BAT_RANGE_CIRCLE3;
		pChara->Command.Sub[3] = sub;//---ダメージ
		break;

	case BAT_ECOM_PINKMIST:
		pChara->Command.Range = BAT_TARGET_FRIENDALL;
		pChara->Command.Sub[3] = sub;//---ダメージ
		break;

	//---移動系
	case BAT_ECOM_RYUSA:
	case BAT_ECOM_GRAVITY:
	case BAT_ECOM_CR_ATUMERU:
		pChara->Command.Range = BAT_TARGET_FRIENDALL;
		pChara->Command.Sub[3] = sub;//---ダメージ
		break;
	case BAT_ECOM_CR_TOBASU:
		pChara->Command.Range = BAT_TARGET_FRIENDRANGE | BAT_RANGE_CIRCLE4;
		pChara->Command.Sub[3] = sub;//---ダメージ
		break;

	case BAT_ECOM_KONRANKOUSEN:
		pChara->Command.Range = BAT_TARGET_FRIENDRANGE | BAT_RANGE_LINE2;
		pChara->Command.Sub[3] = sub;//---ダメージ
		break;
	case BAT_ECOM_JENTLEFLASH:
		pChara->Command.Range = BAT_TARGET_FRIENDRANGE | BAT_RANGE_CIRCLE6;
		break;

	//---自爆！
	case BAT_ECOM_JIBAKU1:
		pChara->Command.Range = BAT_TARGET_FRIENDRANGE | BAT_RANGE_CIRCLE2;
		break;
	case BAT_ECOM_JIBAKU2:
		pChara->Command.Range = BAT_TARGET_FRIENDRANGE | BAT_RANGE_CIRCLE3;
		break;
	case BAT_ECOM_JIBAKU3:
		pChara->Command.Range = BAT_TARGET_FRIENDRANGE | BAT_RANGE_CIRCLE3;
		break;
	case BAT_ECOM_JIBAKU4:
		pChara->Command.Range = BAT_TARGET_FRIENDRANGE | BAT_RANGE_CIRCLE4;
		break;

	case BAT_ECOM_POWERBOMB:
		pChara->Command.Range = BAT_TARGET_FRIENDRANGE | BAT_RANGE_CIRCLE3;
		pChara->Command.Sub[3] = sub;//---ダメージ
		break;

	case BAT_ECOM_KASCADEBOMB:
		pChara->Command.Range = BAT_TARGET_FRIENDRANGE | BAT_RANGE_CIRCLE4;
		pChara->Command.Sub[3] = sub;//---ダメージ
		break;

	case BAT_ECOM_GURUGURUMEDAMA:
		pChara->Command.Range = BAT_TARGET_FRIENDSINGLE;
		break;
	case BAT_ECOM_GURUGURUHYPER:
		pChara->Command.Range = BAT_TARGET_FRIENDALL;
		break;

	case BAT_ECOM_NORIUTURU:
	case BAT_ECOM_NORIUTURU2:
		pChara->Command.Range = BAT_TARGET_ENEMYSINGLE;
		//---自分を抜かすため
		int keep = pChara->GetLP();
		pChara->SetLP(0);
		crbatCPUThink_SetAITarget(pChara,BAT_TARGET_ENEMY);
		pChara->SetLP(keep);
		return;
	}

	crbatCPUThink_SetAITarget(pChara,BAT_TARGET_FRIEND);
	//---強制ターゲット
	if(pForceDst != NULL){
		pChara->SetTarget(pForceDst);
	}
}

//------------------------------------------------

CRBATCPU_API ei_s32 crbatCPUThink_ReverseRange(ei_s32 target)
{
	int range;

	//---ターゲット反転
	range = BAT_TARGET_FRIEND;
	
	if(target & BAT_TARGET_ME){
		range = BAT_TARGET_ENEMYSINGLE;
	} else if(target & BAT_TARGET_FRIENDSINGLE){
		target = BAT_TARGET_ENEMYSINGLE;
		range = BAT_TARGET_ENEMY;
	} else if(target & BAT_TARGET_ENEMYSINGLE){
		target = BAT_TARGET_FRIENDSINGLE;
		range = BAT_TARGET_FRIEND;

	} else if(target & BAT_TARGET_FRIENDALL){
		target = BAT_TARGET_ENEMYALL;
		range = BAT_TARGET_ENEMY;
	} else if(target & BAT_TARGET_ENEMYALL){
		target = BAT_TARGET_FRIENDALL;
		range = BAT_TARGET_FRIEND;
	}

	else if(target & BAT_TARGET_FRIENDRANGE){
		target = (target & ~BAT_TARGET_FRIENDRANGE) | BAT_TARGET_ENEMYRANGE;
		range = BAT_TARGET_ENEMY;
	} else if(target & BAT_TARGET_ENEMYRANGE){
		target = (target & ~BAT_TARGET_ENEMYRANGE) | BAT_TARGET_FRIENDRANGE;
		range = BAT_TARGET_FRIEND;
	}

	return /*range |*/ target;
}

//---ＡＩに応じたターゲットで魔法攻撃をする
CRBATCPU_API void crbatCPUThink_SetMagicAtack(CrBattleCharacter *pChara,int magic,
		int tartget = -1,int ext_target = 0,CrBattleCharacter *pTargetChara = NULL,int range_mode = 0)
{
	int range;
	pChara->Command.Main = BAT_COMMAND_MAGIC;
	pChara->Command.Range = crmagicGetMagicClass(magic)->GetRange(range_mode);

	//---ターゲット反転
	range = BAT_TARGET_FRIEND;

	int target = tartget;
	
	if(target == -1){
		target = crmagicGetMagicClass(magic)->GetTarget(range_mode);
	}

	if(target == BAT_TARGET_ME){
//		target = BAT_TARGET_FRIENDALL;
		range = BAT_TARGET_ENEMY;
	} else if(target == BAT_TARGET_FRIENDSINGLE){
		target = BAT_TARGET_ENEMYSINGLE;
		range = BAT_TARGET_ENEMY;
	} else if(target == BAT_TARGET_ENEMYSINGLE){
		target = BAT_TARGET_FRIENDSINGLE;
		range = BAT_TARGET_FRIEND;

	} else if(target == BAT_TARGET_FRIENDALL){
		target = BAT_TARGET_ENEMYALL;
		range = BAT_TARGET_ENEMY;
	} else if(target == BAT_TARGET_ENEMYALL){
		target = BAT_TARGET_FRIENDALL;
		range = BAT_TARGET_FRIEND;
	}

	else if(target == BAT_TARGET_FRIENDRANGE){
		target = (target & ~BAT_TARGET_FRIENDRANGE) | BAT_TARGET_ENEMYRANGE;
		range = BAT_TARGET_ENEMY;
	} else if(target == BAT_TARGET_ENEMYRANGE){
		target = (target & ~BAT_TARGET_ENEMYRANGE) | BAT_TARGET_FRIENDRANGE;
		range = BAT_TARGET_FRIEND;
	}

	pChara->Command.Range |= target; 
	pChara->Command.Sub[0] = magic;

	if(target == BAT_TARGET_ME){
		//---自分自身
		pChara->Command.Target = (ei_u32)pChara;
	}

	if(magic < 10){
		//---回復
		crbatCPUThink_SetAITarget(pChara,range,1,0,5);
	} else {
		crbatCPUThink_SetAITarget(pChara,range,1);
	}

	//---強制ターゲット
	if(pTargetChara != NULL){
		if(pTargetChara->DoExist()
			&& pTargetChara->GetLP() > 0){
//			pChara->Command.Target = (ei_u32)pTargetChara;
			pChara->SetTarget(pTargetChara);
		}
	}
}

//---ばらばらか？
CRBATCPU_API int crbatCPU_PlayerIsBaraBara(CrBattleCharacter *pChara,int range)
{
	//---サークル３で、プレイヤー同士が一人も重ならないと、ばらばらと判断
	CR_BATTLE_DAMAGEINFO DamageInfo;
	ei_u32 range_table[] = {BAT_RANGE_CIRCLE1,BAT_RANGE_CIRCLE2,BAT_RANGE_CIRCLE3,BAT_RANGE_CIRCLE4,BAT_RANGE_CIRCLE5};
	
	int a,b,flag;

	if(range > 3)
		range = 3;

	for(a = 0,flag = 0;a < BATTLECHARA_PARTY_MAX;a ++){
		if(!pBtChara[a].DoExist())
			continue;
		memset(&DamageInfo,0,sizeof(DamageInfo));

		//---ターゲット検索
		crbatGetTargetChara(pChara,&pBtChara[a],
			range_table[range] | BAT_TARGET_FRIENDRANGE,
			&DamageInfo.pList[0],0);

		for(b = 0;DamageInfo.pList[b] != NULL;b ++){
			if(b > 0){
				//---重なってる！
				flag ++;
			}
		}
	}

	return (flag ? 0 : 1);
}

//---近くに接近してるのはいるか？
CRBATCPU_API CrBattleCharacter* crbatCPU_PlayerIsSekkin(CrBattleCharacter *pChara,int range)
{
	//---サークル１で、誰かいるか
	CR_BATTLE_DAMAGEINFO DamageInfo;
	ei_u32 range_table[] = {BAT_RANGE_CIRCLE1,BAT_RANGE_CIRCLE2,BAT_RANGE_CIRCLE3};
	CrBattleCharacter *pnear = NULL;
	int a,flag = 0;

	if(range >= 3)
		range = 2;
	{
		memset(&DamageInfo,0,sizeof(DamageInfo));

		//---ターゲット検索
		crbatGetTargetChara(pChara,pChara,
			range_table[range] | BAT_TARGET_FRIENDRANGE,
			&DamageInfo.pList[0],0);

		for(a = 1;DamageInfo.pList[a] != NULL;a ++){
			if(DamageInfo.pList[a] != NULL
				&& !DamageInfo.pList[a]->IsDown()){
				//---重なってる！
				flag ++;
				pnear = DamageInfo.pList[a];

				break;
			}
		}
	}

	return pnear;
}

#define CPU_UI_ALL 0x7fff0000

//---インバリディティを使うときか
CRBATCPU_API int crbatCPU_UseInvalidity(CrBattleCharacter *pChara,ei_u32 mode = CPU_UI_ALL)
{
	int use = 0;
	int a;

	for(a = 0;a < BATTLECHARA_PARTY_MAX;a ++){
		if(pBtChara[a].DoExist() && !pBtChara[a].IsKizetu()){
			//---気絶でなければ
			if(pBtChara[a].GetBtStatus() & mode){
				use ++;
			}
		}
	}

	return use;
}

//---プレイヤーキャラクターの横の座標
CRBATCPU_API CrBattleCharacter *crbatCPU_GetPlayerCharaSide(CrBattleCharacter *pChara,ei_s32 *px,ei_s32 *py)
{
	int a,count,pointer = 0;
	CrBattleCharacter *list[BATTLECHARA_PARTY_MAX + 1],*you;
	int x[] = {-1,0,1, -1,1, -1,0,1,255},
		y[] = {-1,-1,-1, 0,0, 1,1,1,255};
	int cx,cy;

	*px = 0;
	*py = 0;
	memset(list,0,sizeof(list));

	for(a = 0,count = 0;a < BATTLECHARA_PARTY_MAX;a ++){
		if(pBtChara[a].DoExist() && pBtChara[a].IsFriend()){
			//---リストに追加
			list[count] = &pBtChara[a];
			count ++;
		}
	}

	//---誰もいない！（んなことないだろうけど）
	if(count == 0)
		return NULL;

	you = list[eiRnd(count)];

	do {
		cx = x[pointer] + you->GetFieldX();
		cy = y[pointer] + you->GetFieldY();
		if(++pointer >= 8)
			pointer = 0;
	//---誰かいるか、範囲外だったら続ける
	} while(crbatIsThere(cx,cy,pChara) || crbatIsFieldRange(cx,cy) == 0);

	*px = cx;
	*py = cy;

	return you;
}

//---敵の数
CRBATCPU_API int crbatCPUGetEnemy(void)
{
	int a,count;
	for(a = BATTLECHARA_STARTENEMY , count = 0;a < BATTLECHARA_STARTENEMY + BATTLE_ENEMYMAX;a ++){
		if(pBtChara[a].DoExist()){
			count ++;
		}
	}
	return count;
}

//---ＣＰＵ行動前
CRBATCPU_API int crbatCPUBeforeAction(CrBattleCharacter *pChara,int turn)
{
	int a;

	if(pChara->BattleInfo.Enemy.ActionType == 11){
		//---フォールン
		if(turn < 2){
			pChara->Command.Main = BAT_COMMAND_WAIT;
			if(turn == 1){
				//---おしゃべりフォールン
				//---カメラ移動
				crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);
				crbatBeginCameraObjectToObject(0,pChara,&pBtChara[0],
				ANGLE(90),
				-1.0f,-1.0f,500);
				//---リストに描くのを追加
				crbatClearDrawingList();
				crbatAddDrawingListAll();
				crbatDoMovingCamera(500);

				CrMesManager mes;
				mes.CreateNewMessage(-1,-1,32,24,5);
				mes.OpenMessage("Opening.msg",3);
				mes.ReadMessage();
				mes.Draw();
				mes.ReadMessage();
				mes.Draw();
				mes.CloseMessage();
			}
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 44){
		//---クレイシヴ
		pChara->Command.Main = BAT_COMMAND_WAIT;
		if(turn == 2){
			//---クレイシヴしゃべる
			//---カメラ移動
			crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);
			crbatBeginCameraObjectToObject(0,pChara,&pBtChara[0],
			ANGLE(90),
			-1.0f,-1.0f,500);
			//---リストに描くのを追加
			crbatClearDrawingList();
			crbatAddDrawingListAll();
			crbatDoMovingCamera(500);

			CrMesManager mes;
			mes.CreateNewMessage(-1,-1,32,24,5);
			mes.OpenMessage("DoguriSouth_Iseki.msg",106);
			mes.ReadMessage();
			mes.Draw();
			mes.ReadMessage();
			mes.Draw();
			mes.CloseMessage();
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 67){
		//---ラーフィア
/*		if(pChara->Command.Main == BAT_COMMAND_MAGIC
			&& pChara->Command.Sub[0] == 3
			&& pChara->GetBattleFlag(5) == 0){

			pChara->SetBattleFlag(5,1);

			//---カメラ移動
			crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);
			crbatBeginCameraObjectToObject(0,pChara,pChara,
				ANGLE(90),
				-1.0f,-1.0f,500);
			//---リストに描くのを追加
			crbatClearDrawingList();
			crbatAddDrawingListAll();
			crbatDoMovingCamera(500);

			CrMesManager mes;
			mes.CreateNewMessage(-1,-1,32,24,5);
			mes.OpenMessage("GenwakuForest.msg",122);
			mes.ReadMessage();
			mes.Draw();
			mes.CloseMessage();
		} else*/ if(pChara->Command.Main == BAT_COMMAND_MAGIC
			&& pChara->Command.Sub[0] == 55
			&& pChara->GetBattleFlag(3) == 0){
			//---ウィンドオーヴ

			pChara->SetBattleFlag(3,1);

			//---カメラ移動
			crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);
			crbatBeginCameraObjectToObject(0,pChara,(CrBattleCharacter *)pChara->Command.Target,
				ANGLE(90),
				-1.0f,-1.0f,500);
			//---リストに描くのを追加
			crbatClearDrawingList();
			crbatAddDrawingListAll();
			crbatDoMovingCamera(500);

			CrMesManager mes;
			mes.CreateNewMessage(-1,-1,32,24,5);
			mes.OpenMessage("GenwakuForest.msg",120);
			mes.ReadMessage();
			mes.Draw();
			mes.CloseMessage();
		} else if(pChara->Command.Main == BAT_COMMAND_WEAPON
			&& pChara->GetBattleFlag(6) == 0){

			pChara->SetBattleFlag(6,1);

			//---カメラ移動
			crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);
			crbatBeginCameraObjectToObject(0,pChara,(CrBattleCharacter *)pChara->Command.Target,
				ANGLE(90),
				-1.0f,-1.0f,500);
			//---リストに描くのを追加
			crbatClearDrawingList();
			crbatAddDrawingListAll();
			crbatDoMovingCamera(500);

			CrMesManager mes;
			mes.CreateNewMessage(-1,-1,32,24,5);
			mes.OpenMessage("GenwakuForest.msg",123);
			mes.ReadMessage();
			mes.Draw();
			mes.CloseMessage();
		} else if(pChara->Command.Main == BAT_COMMAND_MAGIC
			&& pChara->Command.Sub[0] == 67
			&& pChara->GetBattleFlag(4) == 0){

			pChara->SetBattleFlag(4,1);

			//---カメラ移動
			crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);
			crbatBeginCameraObjectToObject(0,pChara,(CrBattleCharacter *)pChara->Command.Target,
				ANGLE(90),
				-1.0f,-1.0f,500);
			//---リストに描くのを追加
			crbatClearDrawingList();
			crbatAddDrawingListAll();
			crbatDoMovingCamera(500);

			CrMesManager mes;
			mes.CreateNewMessage(-1,-1,32,24,5);
			mes.OpenMessage("GenwakuForest.msg",121);
			mes.ReadMessage();
			mes.Draw();
			mes.CloseMessage();
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 131){
		//---エド
		if(turn == 0 && !pChara->GetBattleFlag(0)
			&& pBtChara[0].Who() == 2 && !pBtChara[0].IsDown()){
			pChara->SetBattleFlag(0,1);

			//---カメラ移動
			pChara->SetAngle(pChara->GetCharaAngle((CrBattleCharacter *)pChara->Command.Target));
			((CrBattleCharacter *)(pChara->Command.Target))->SetAngle(
				((CrBattleCharacter *)(pChara->Command.Target))->GetCharaAngle(pChara)
				);

			crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);
			crbatBeginCameraObjectToObject(0,pChara,(CrBattleCharacter *)pChara->Command.Target,
				ANGLE(90),
				-1.0f,-1.0f,500);
			//---リストに描くのを追加
			crbatClearDrawingList();
			crbatAddDrawingListAll();
			crbatDoMovingCamera(500);

			CrMesManager mes;
			mes.CreateNewMessage(-1,-1,32,24,5);
			mes.OpenMessage("KiokunoIseki.msg",101);
			for(a = 0;a < 7;a ++){
				mes.ReadMessage();
				mes.Draw();
			}
			mes.CloseMessage();
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 132){
		//---ラーフィア
		if(turn == 1 && !pChara->GetBattleFlag(0)
			&& pBtChara[0].Who() == 1 && !pBtChara[0].IsDown()){
			pChara->SetBattleFlag(0,1);

			//---カメラ移動
			pChara->SetAngle(pChara->GetCharaAngle((CrBattleCharacter *)pChara->Command.Target));
			((CrBattleCharacter *)(pChara->Command.Target))->SetAngle(
				((CrBattleCharacter *)(pChara->Command.Target))->GetCharaAngle(pChara)
				);

			crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);
			crbatBeginCameraObjectToObject(0,pChara,(CrBattleCharacter *)pChara->Command.Target,
				ANGLE(90),
				-1.0f,-1.0f,500);
			//---リストに描くのを追加
			crbatClearDrawingList();
			crbatAddDrawingListAll();
			crbatDoMovingCamera(500);

			CrMesManager mes;
			mes.CreateNewMessage(-1,-1,32,24,5);
			mes.OpenMessage("KiokunoIseki.msg",102);
			for(a = 0;a < 8;a ++){
				mes.ReadMessage();
				mes.Draw();
			}
			mes.CloseMessage();
		}
	} else if(pChara->BattleInfo.Enemy.ActionType == 223){
		//---クレイシヴ
//		pChara->Command.Main = BAT_COMMAND_WAIT;
		if(turn == 0){
		} else if(turn == 1){
			if(!pChara->IsDown()){
				crmusicFadeOut();

				//---カメラ移動
				pChara->SetAngle(pChara->GetCharaAngle((CrBattleCharacter *)pChara->Command.Target));
				crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);
				crbatBeginCameraObjectToObject(0,pChara,((CrBattleCharacter *)pChara->Command.Target),
				ANGLE(90),
				-1.0f,-1.0f,500);
				//---リストに描くのを追加
				crbatClearDrawingList();
				crbatAddDrawingListAll();
				crbatDoMovingCamera(500);

				CrMesManager mes;
				mes.CreateNewMessage(-1,-1,32,24,5);
				mes.OpenMessage("Illeadia.msg",114);
				for(a = 0;a < 1;a ++){
					mes.ReadMessage();
					mes.Draw();
				}
				mes.CloseMessage();

				crmusicPlay(CRMUSIC_BARRIER);
			}
		} else if(pChara->GetBattleFlag(1) == 2){
			crmusicFadeOut();
			if(!pBtChara[1].IsDown() && !(pBtChara[1].GetBtStatus() & BTST_KONRAN)){
				//---カメラ移動
				crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);
				crbatBeginCameraObjectToObject(0,pChara,&pBtChara[1],
				ANGLE(90),
				-1.0f,-1.0f,500);
				//---リストに描くのを追加
				crbatClearDrawingList();
				crbatAddDrawingListAll();
				crbatDoMovingCamera(500);

				CrMesManager mes;
				mes.CreateNewMessage(-1,-1,32,24,5);
				mes.OpenMessage("Illeadia.msg",111);
				mes.ReadMessage();
				mes.Draw();
				mes.CloseMessage();

				if(!pBtChara[3].IsDown() && !(pBtChara[3].GetBtStatus() & BTST_KONRAN)){
					//---カメラ移動
					crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);
					crbatBeginCameraObjectToObject(0,pChara,&pBtChara[3],
					ANGLE(90),
					-1.0f,-1.0f,500);
					//---リストに描くのを追加
					crbatClearDrawingList();
					crbatAddDrawingListAll();
					crbatDoMovingCamera(500);

					CrMesManager mes;
					mes.CreateNewMessage(-1,-1,32,24,5);
					mes.OpenMessage("Illeadia.msg",115);
					mes.ReadMessage();
					mes.Draw();
					mes.CloseMessage();
					if(!pBtChara[2].IsDown() && !(pBtChara[2].GetBtStatus() & BTST_KONRAN)){
						//---カメラ移動
						crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);
						crbatBeginCameraObjectToObject(0,pChara,&pBtChara[2],
						ANGLE(90),
						-1.0f,-1.0f,500);
						//---リストに描くのを追加
						crbatClearDrawingList();
						crbatAddDrawingListAll();
						crbatDoMovingCamera(500);

						CrMesManager mes;
						mes.CreateNewMessage(-1,-1,32,24,5);
						mes.OpenMessage("Illeadia.msg",116);
						mes.ReadMessage();
						mes.Draw();
						mes.CloseMessage();
					}
				}
			}
			crmusicPlay(CRMUSIC_SILENT);
		} else if(pChara->GetBattleFlag(1) == 1){
			//---カメラ移動
			int live = -1,down_only = 0;
			for(a = 0;a < 4;a ++){
				if(!pBtChara[a].IsDown()){
					live = a;
					break;
				}
			}
			if(live == -1){
				down_only = 1;
				for(a = 0;a < 4;a ++){
					if(!pBtChara[a].IsKizetu()){
						live = a;
						break;
					}
				}
			}
			pChara->SetBattleFlag(2,live);

			crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);

			crmusicPlay(CRMUSIC_HOPE);
			crbatClearDrawingList();
			crbatAddDrawingListAll();
			crbatDrawSceneWhile(500);

			crbatBeginCameraObjectToObject(0,pChara,&pBtChara[live],
			ANGLE(180),
			-1.0f,-1.0f,500);
			//---リストに描くのを追加
			crbatClearDrawingList();
			crbatAddDrawingListAll();

			crbatDoMovingCamera(2000);
			if(down_only == 0){
				CrMesManager mes;
				mes.CreateNewMessage(-1,-1,32,24,5);
				mes.OpenMessage("Illeadia.msg",120 + live);
				for(a = 0;a < 1;a ++){
					mes.ReadMessage();
					mes.Draw();
				}
				mes.CloseMessage();
			}
			crbatDrawSceneWhile(2000);

			CrMesManager mes2;
			mes2.CreateNewMessage(-1,-1,32,24,5);
			mes2.OpenMessage("Illeadia.msg",113);
			for(a = 0;a < 5;a ++){
				mes2.ReadMessage();
				mes2.Draw();
			}
			mes2.CloseMessage();
		}
	}

	return 1;
}

#include "CrBattle_CPUSubThink8.cpp"
#include "CrBattle_CPUSubThink7.cpp"
#include "CrBattle_CPUSubThink6.cpp"
#include "CrBattle_CPUSubThink5.cpp"
#include "CrBattle_CPUSubThink4.cpp"
#include "CrBattle_CPUSubThink3.cpp"
#include "CrBattle_CPUSubThink2.cpp"
#include "CrBattle_CPUSubThink.cpp"
