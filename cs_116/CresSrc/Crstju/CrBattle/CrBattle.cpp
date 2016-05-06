/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBattle.cpp ...Battle functions

-----------------------------------------------------------*/

#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBATTLE

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#include "..\CrBase.h"
#include "..\CrBattle.h"

#ifdef MAKE_DLL
	#define CR_GAMEINFO_POINTER
#else
	#define CR_GAMEINFO_EXTERNPOINTER
#endif /*MAKE_DLL*/
#include "..\CrGameInfo.h"

//---やり直し用
ei_s32 BtKeepItem[ITEM_MAX],BtKeepItemCount[ITEM_MAX];

//---変数
CR_BATFIELDVERTEX BattleField[BATTLEFIELD_VERTEXCOUNT_X][BATTLEFIELD_VERTEXCOUNT_Y];
//CR_BATTLEINFO BattleInfo;
CrBattleCharacter BattleChara[BATTLECHARA_MAX],*pBtChara,
	KeepChara[KEEPCHARA_MAX],*pKeepChara;
CrBattleCharacter BattleTempChara[4],*pBtTempChara;
CrBattleObject BattleObject[BATTLEOBJECT_MAX],*pBtObject;
CR_BATTLEVIEW CameraPos;

eiD3DMaterial BattleFieldMaterial,BattleParticleMaterial;
eiD3DParticle BatPart[BATTLE_PARTMAX];
eiD3DLight BatLight[8];

//---頂点バッファー
eiD3DVertexBuffer vbSrc,vbDest;

//---視界
CR_BATTLEVIEW BattleView[BATTLE_VIEWMAX];
int BattleViewMode = BATTLE_VIEWMODE_SINGLE;
RECT BattleViewRect[BATTLE_VIEWMAX][6];
float HViewNumber[BATTLE_VIEWMAX] = {4.0f,4.0f,8.0f,8.0f, 1.0f,1.0f,1.0f,1.0f};
int ViewNumber[BATTLE_VIEWMAX] = {1,1,2,1 ,1,1,1,1};

//---Anime
ei_s32 AnimePatternCount[BATTLE_ANIMEMAX] = 
{
	4,4,4,4
};

ei_s32 AnimePatternSize[BATTLE_ANIMEMAX] = 
{
	64,64,64,64
};

ei_s32 BattleAnimeWait[BATTLE_ANIMEMAX] = 
{
	60,60,60,60
};

int PreviousAnimeNumber = -1;

//---Range
ei_s32 BattleLineRange[12] =
{
	2,3,4,5,6,7,8,9
};

ei_s32 BattleCircleRange[12] =
{
	4,6,7,9,10,12,14,16
};

//---行動次の順序決定パラメータ
ei_s32 BattleActionSource[16] = 
{
	0,1,0,0, 0,0,0,0 //--- 1:Magic
};

//---パターン
eiCell BattleCharaCell[BATTLE_CHARAPATTERN * 5];
eiCell BattleEnemyCell[BATTLE_ENEMYPATTERN];
eiCell BattleBackgroundCell[BATTLE_BGCELLMAX];
eiCell BattleRadarCell;
eiCell BattleAnimeCell[ANIMEPATTERN_1];
eiCell BattleStatusCell[BATTLE_STATUSICONMAX];
//---テクスチャー
eiTextureCell BattleFieldCell[BATTLE_FIELDCELLMAX],ShadowCell;

//---
ei_s32 BattleExperience,BattleMoney,BattleItem,BattleItemProb,BattleStartTime;

#include "CrBattleSubTest.cpp"

//---DLLの初期化
CRBATTLE_API int crbatInitDLL(CRESTEAJU_GAMEDATA *pgameusingdata,
							 CRESTEAJU_GAMEINFO *pgame,
							 CRESTEAJU_PARTYINFO *pparty,
							 CrCharacter *pplayer,
							 CrItem *pitem,CrMagic *pmagic,
							 int *pdebug,int *pfilemode,
							 CRESTEAJU_SYSTEM *psystem,CRESTEAJU_INITIALIZE *pini,
							 CRESTEAJU_CHARACTERINFO *penemychara,CRESTEAJU_BATTLECHARAINFO *penemybat)
{
	pGameUsingData = pgameusingdata;
	pGameInfo = pgame;
	pPartyInfo = pparty;
	pCharacterInfo = pplayer;
	pItemInfo = pitem;
	pMagicInfo = pmagic;

	pEnemyCharaInfo = penemychara;
	pEnemyBatInfo = penemybat;

	//---
	pBtChara = &BattleChara[0];
	pKeepChara = &KeepChara[0];
	pBtObject = &BattleObject[0];
	pBtTempChara = &BattleTempChara[0];
//	crdataSetPointer(pdebug,pfilemode,psystem,pini);

	return 1;
}

//---イベントバトル
CRBATTLE_API int crbatEventBattle(CR_BATTLEINFO *pInfo /*= NULL*/)
{
	int ret;

	if(pInfo->MapNumber == 0){
		pInfo->MapNumber = crfieldGetMapNumber();
	}
	ret = crbatGotoBattle(pInfo);

	return ret;
}

//---通常戦闘
CRBATTLE_API int crbatFieldBattle(int map,int area)
{
	int a = 0,EnemyCount = 0;
	CR_BATTLEINFO BattleInfo;

	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.Music = -1;
	BattleInfo.EnebleAvoid = 1;
	if(map == 10)
		BattleInfo.ScreenEfect = 1;
	else
		BattleInfo.ScreenEfect = 1;
	BattleInfo.lpTurnCallBack = NULL;
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.AreaNumber = area;

	//---エリアファイルを開く
	int flag = 0,start = 0,max_count = 0,count = 0,target = 0;
	eiFile file(CR_DATAFILE3);
	eistr s[100],*p,*u;
	sprintf(s,"%sar%03d.txt",CR_DATADIR3,map);
	if(file.Open(s) == 0){
		return 0;
	}

	while(file.GetLine(&s[0],80)){
		p = &s[0];
		//---改行＆タブ削除
		while(*p != NULL){
			if(*p == '\t'){
				*p = ' ';
			}
			if(*p == '\n' || *p == '\r'){
				*p = NULL;
				break;
			}
			p ++;
		}

		if(flag == 0 && s[0] == ':'){
			//---エリア取得
			if(atoi(&s[1]) == area){
				start = file.GetAddres();
				flag = 1;
			}
		} else if(flag == 1){
			//---敵パターンの数を数える
			if(s[0] == ':'){
				//---次のエリアが出たらそこで終了
				//---エリアの敵パターン先頭にポインタを移す
				file.Seek(start);
				flag = 2;
				count = 0;
				target = eiRnd(max_count);
			} else if(s[0] != NULL){
				//---敵情報があれば
				max_count ++;
			}
		} else if(flag == 2){
			//---探し出す
			if(s[0] != NULL){
				if(count == target){
					//---ターゲットが見つかったら
					flag = 3;
					break;
				}
				count ++;
			}
		}
//		eiDebugWriteFile(s);
	}
	file.Close();
//	eiDebugWriteFile("\n***********************\n");
//	eiDebugWriteFile(s);
//	eiDebugWriteFile("\n");

/*	char ss[100];
	sprintf(ss,"max = %d : tar = %d : area = %d : flag = %d \n",
		max_count,target,area,flag);
	eiDebugWriteFile(ss);*/
	if(flag != 3){
		eiDebugWriteFile("敵情報検索に失敗しました\n");
		return 0;
	}
	//---解析
	for(EnemyCount = 0,p = u = &s[0];;EnemyCount ++){
		//---敵ナンバー
		for(;*p != '(';p ++);
		*p = NULL;
		BattleInfo.Enemy[EnemyCount].Enemy = atoi(u);
//		eiDebugWriteFile(u);
//		eiDebugWriteFile("\n");
		p ++;
		u = p;

		//---x
		for(;*p != ',';p ++);
		*p = NULL;
		BattleInfo.Enemy[EnemyCount].x = atoi(u);
		eiDebugWriteFile(u);
		eiDebugWriteFile("\n");
		p ++;
		u = p;

		//---x
		for(;*p != ')';p ++);
		*p = NULL;
		BattleInfo.Enemy[EnemyCount].y = atoi(u);
		eiDebugWriteFile(u);
		eiDebugWriteFile("\n");
		p ++;
		u = p;

		//---次の位置まで
		for(;*p != ',' && *p != ';';p ++);
		if(*p == ';'){
			//---解析終了
			break;
		}
		for(p ++;*p == ' ';p ++);
		u = p;
	}

	//---左右反転するかどうか
	int dir_mode = eiRnd(2);

//	EnemyCount = eiRnd(4) + 1;
	for(a = 0;a < EnemyCount + 1;a ++){
//		BattleInfo.Enemy[a].Enemy = 1;
//		BattleInfo.Enemy[a].x = (BATTLEFIELD_MAX_X - 2) * a / EnemyCount + 1;
//		BattleInfo.Enemy[a].y = BATTLEFIELD_MAX_Y / 2 + eiRnd((BATTLEFIELD_MAX_Y - 2) / 2) + 1;
		BattleInfo.Enemy[a].y += (BATTLEFIELD_MAX_Y / 2);

		if(dir_mode){
			BattleInfo.Enemy[a].x = BATTLEFIELD_MAX_X - BattleInfo.Enemy[a].x;
		}
	}
	BattleInfo.Enemy[EnemyCount + 1].Enemy = -1;

	int moriuni = 0;
	if(map == 42 && /*!pGameInfo->Event[211] &&*/ pGameInfo->Event[160]){
		//---２部クリア
		//---ダイの森
		if(eiRnd(1000) < 100){
			moriuni = 1;
		}
	}

	if(moriuni){
		//---モリウニ！
		for(a = 0;a < EnemyCount + 1;a ++){
			BattleInfo.Enemy[EnemyCount + 1].Enemy = -1;
		}
		BattleInfo.Enemy[0].Enemy = 216;
		BattleInfo.Enemy[1].Enemy = -1;
		EnemyCount = 1;
	} else {
		//---オフセットバトル許可（モリウニバトルは無し）
		BattleInfo.EnableOffsetBattle = OFFSETBAT_ENABLEALL;
	}

	crbatGotoBattle(&BattleInfo);

	return 1;
}

//---バトルエントリーポイント
CRBATTLE_API int crbatGotoBattle(CR_BATTLEINFO *pInfo)
{
	CR_BATTLEINFO *pBattleInfo = NULL;// = &info;
	int ret;

	if(pInfo != NULL){
		pBattleInfo = pInfo;
	}
	if(pInfo->Music != 0){
		//---音楽フェードアウト
//		crmusicFadeOut();
	}

	eiDebugWriteFile("*******************************************************\n");
	//---画面効果
	RECT ScreenRect = {
		(640 - 32 * crdataGetInitialize()->IniFile.FieldSizeX) / 2,//80,
		(480 - 32 * crdataGetInitialize()->IniFile.FieldSizeY) / 2,//32,
		640 - (640 - 32 * crdataGetInitialize()->IniFile.FieldSizeX) / 2,//80 + 480,
		480 - (480 - 32 * crdataGetInitialize()->IniFile.FieldSizeY) / 2};//32 + 416 };
	if(pInfo->ScreenEfect == 1){
		if(crsysGetExtentionLevel() >= CR_EXTENTION_NORMAL){
//			crefectScreenEfect_FadeOut(&ScreenRect,125,RGB(255,255,255),0);
		}
		//---バリーン！
		crefectScreenEfect_Bomb(&ScreenRect);
	} else if(pInfo->ScreenEfect == 2){
		if(crsysGetExtentionLevel() >= CR_EXTENTION_NORMAL){
//			crefectScreenEfect_FadeOut(&ScreenRect,125,RGB(255,255,255),0);
		}
		//---ズーム！
		crefectScreenEfect_RotateZoom(&ScreenRect);
	}

	//---スレッドチェック！
	eiCheckThread();

	//---初期設定
	crbatInitBattle(pBattleInfo,0);
	//---バトルカウントを増やす
	crhistBattleCount();

#if (CR_DEBUG == 1)
	if(crdataGetDebug()){
		ei->Get();
		if(ei->Return){
//			crbatTest();
		}
	}
#endif /* (CR_DEBUG == 1) */

	//---ワールドＭＣ保存
	int world = crmagicGetMagicClass(24)->MagicInfo.UseMC;

	ret = crbatBattleMain(pBattleInfo);
	if(ret == BATRET_AVOID){
		//---逃げたら
		crhistEscapeCount();
	}

	//---ワールドＭＣ復帰
	crmagicGetMagicClass(24)->MagicInfo.UseMC = world;

	//---保存する必要があるならする
	if(pInfo->KeepEnemyNumber){
		int a,b,num = pInfo->KeepEnemyNumber - 1;
		for(a = BATTLECHARA_STARTENEMY,b = 0;a < BATTLECHARA_STARTENEMY + BATTLE_ENEMYMAX;a ++,b ++){
			memcpy(&pKeepChara[num + b].CharaInfo,
				&pBtChara[a].CharaInfo
				,sizeof(pBtChara[a].CharaInfo));

			memcpy(&pKeepChara[num + b].OnlyInfo,
				&pBtChara[a].OnlyInfo
				,sizeof(pBtChara[a].OnlyInfo));

			memcpy(&pKeepChara[num + b].BattleInfo,
				&pBtChara[a].BattleInfo
				,sizeof(pBtChara[a].BattleInfo));

//			eiDebugWriteFile("hozonn:");
//			eiDebugWriteFile(pBtChara[a].GetName());
//			eiDebugWriteFile("\n");
		}
	}

	crbatEndBattle(pBattleInfo,0);

	return ret;
}
