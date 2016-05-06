#ifndef INCLUDE_CRBATTLE_H

#define INCLUDE_CRBATTLE_H

//---------------------------------------------------------
//---------------------------------------------------------
#ifdef MAKE_DLL
	#ifdef FILE_CRBATTLEDLLMAIN
		#define CRBATTLEDLLMAIN_API __declspec(dllexport)
	#else
		#define CRBATTLEDLLMAIN_API extern
	#endif /*FILE_CRBATTLEDLLMAIN*/

	#ifdef FILE_CRBATTLE
		#define CRBATTLE_API __declspec(dllexport)
	#else
		#define CRBATTLE_API extern
	#endif /*FILE_CRBATTLE*/

	#ifdef FILE_CRBATTLE_BASE
		#define CRBATBASE_API __declspec(dllexport)
	#else
		#define CRBATBASE_API extern
	#endif /*FILE_CRBATBASE*/

	#ifdef FILE_CRBATTLE_INIT
		#define CRBATINIT_API __declspec(dllexport)
	#else
		#define CRBATINIT_API extern
	#endif /*FILE_CRBATINIT*/

	#ifdef FILE_CRBATTLE_CLASS
		#define CRBATTLECLASS __declspec(dllexport)
	#else
		#define CRBATTLECLASS
	#endif /*FILE_CRBATTLE_CLASS*/

	#ifdef FILE_CRBATTLE_DRAW
		#define CRBATTLEDRAW_API __declspec(dllexport)
	#else
		#define CRBATTLEDRAW_API
	#endif /*FILE_CRBATTLE_DRAW*/

	#ifdef FILE_CRBATTLE_COMMAND
		#define CRBATCOMMAND_API __declspec(dllexport)
	#else
		#define CRBATCOMMAND_API
	#endif /*FILE_CRBATTLE_COMMAND*/

	#ifdef FILE_CRBATTLE_MAIN
		#define CRBATMAIN_API __declspec(dllexport)
	#else
		#define CRBATMAIN_API
	#endif /*FILE_CRBATTLE_MAIN*/

	#ifdef FILE_CRBATTLE_ANIME
		#define CRBATANIME_API __declspec(dllexport)
	#else
		#define CRBATANIME_API
	#endif /*FILE_CRBATTLE_ANIME*/

	#ifdef FILE_CRBATTLE_CPU
		#define CRBATCPU_API __declspec(dllexport)
	#else
		#define CRBATCPU_API
	#endif /*FILE_CRBATTLE_CPU*/

	#ifdef FILE_CRBATTLE_MAGIC
		#define CRBATMAGIC_API __declspec(dllexport)
	#else
		#define CRBATMAGIC_API
	#endif /*FILE_CRBATTL_MAGIC*/

	#ifdef FILE_CRBATTLE_ENEMY
		#define CRBATENEMY_API __declspec(dllexport)
	#else
		#define CRBATENEMY_API
	#endif /*FILE_CRBATTL_ENEMY*/

	#ifdef FILE_CRBATTLE_ENEMYABILITY
		#define CRBATENEMYABILITY_API __declspec(dllexport)
	#else
		#define CRBATENEMYABILITY_API
	#endif /*FILE_CRBATTLE_ENEMYABILITY*/

	#ifdef FILE_CRBATTLE_SPECIAL
		#define CRBATSPECIAL_API __declspec(dllexport)
	#else
		#define CRBATSPECIAL_API
	#endif /*FILE_CRBATTLE_SPECIAL*/
//---------------------------------------------------------
//---------------------------------------------------------
#else

	#ifdef FILE_CRBATTLEDLLMAIN
		#define CRBATTLEDLLMAIN_API
	#else
		#define CRBATTLEDLLMAIN_API extern
	#endif /*FILE_CRBATTLEDLLMAIN*/

	#ifdef FILE_CRBATTLE
		#define CRBATTLE_API
	#else
		#define CRBATTLE_API extern
	#endif /*FILE_CRBATTLE*/

	#ifdef FILE_CRBATTLE_BASE
		#define CRBATBASE_API 
	#else
		#define CRBATBASE_API extern
	#endif /*FILE_CRBATBASE*/

	#ifdef FILE_CRBATTLE_INIT
		#define CRBATINIT_API 
	#else
		#define CRBATINIT_API extern
	#endif /*FILE_CRBATINIT*/

	#ifdef FILE_CRBATTLE_CLASS
		#define CRBATTLECLASS
	#else
		#define CRBATTLECLASS
	#endif /*FILE_CRBATTLE_CLASS*/

	#ifdef FILE_CRBATTLE_DRAW
		#define CRBATTLEDRAW_API extern
	#else
		#define CRBATTLEDRAW_API
	#endif /*FILE_CRBATTLE_DRAW*/

	#ifdef FILE_CRBATTLE_COMMAND
		#define CRBATCOMMAND_API extern
	#else
		#define CRBATCOMMAND_API
	#endif /*FILE_CRBATTLE_COMMAND*/

	#ifdef FILE_CRBATTLE_MAIN
		#define CRBATMAIN_API extern
	#else
		#define CRBATMAIN_API
	#endif /*FILE_CRBATTLE_MAIN*/

	#ifdef FILE_CRBATTLE_ANIME
		#define CRBATANIME_API extern
	#else
		#define CRBATANIME_API
	#endif /*FILE_CRBATTLE_ANIME*/

	#ifdef FILE_CRBATTLE_CPU
		#define CRBATCPU_API extern
	#else
		#define CRBATCPU_API
	#endif /*FILE_CRBATTLE_CPU*/

	#ifdef FILE_CRBATTLE_MAGIC
		#define CRBATMAGIC_API extern
	#else
		#define CRBATMAGIC_API
	#endif /*FILE_CRBATTL_MAGIC*/

	#ifdef FILE_CRBATTLE_ENEMY
		#define CRBATENEMY_API extern
	#else
		#define CRBATENEMY_API
	#endif /*FILE_CRBATTL_ENEMY*/

	#ifdef FILE_CRBATTLE_ENEMYABILITY
		#define CRBATENEMYABILITY_API extern
	#else
		#define CRBATENEMYABILITY_API
	#endif /*FILE_CRBATTLE_ENEMYABILITY*/

	#ifdef FILE_CRBATTLE_SPECIAL
		#define CRBATSPECIAL_API extern
	#else
		#define CRBATSPECIAL_API
	#endif /*FILE_CRBATTLE_SPECIAL*/
#endif

#include "CrBattle_Def.h"
#include "CrBattle_Func.h"


#ifdef EXTERN_CRBATTLE
	extern ei_s32 BtKeepItem[ITEM_MAX],BtKeepItemCount[ITEM_MAX];

	extern D3DVERTEX BattleFieldVertex[BATTLEFIELD_VERTEXCOUNT_X * BATTLEFIELD_VERTEXCOUNT_Y * 4];
	extern CR_BATFIELDVERTEX BattleField[BATTLEFIELD_VERTEXCOUNT_X][BATTLEFIELD_VERTEXCOUNT_Y];
	extern CR_BATTLEINFO BattleInfo;
	extern CrBattleCharacter *pBtChara,*pKeepChara;
	extern CrBattleCharacter TempBattleChara[4],*pBtTempChara;
	extern CrBattleObject *pBtObject;
	extern eiD3DMaterial BattleFieldMaterial,BattleParticleMaterial;
	extern eiD3DVertexBuffer vbSrc,vbDest;

//-------------------
	extern CR_BATTLEVIEW BattleView[BATTLE_VIEWMAX];
	extern int BattleViewMode;
	extern RECT BattleViewRect[BATTLE_VIEWMAX][6];
	extern float HViewNumber[BATTLE_VIEWMAX];
	extern int ViewNumber[BATTLE_VIEWMAX];
//-------------------
	extern eiCell BattleCharaCell[BATTLE_CHARAPATTERN * 5];
	extern eiCell BattleEnemyCell[BATTLE_ENEMYPATTERN];
	extern eiCell BattleBackgroundCell[BATTLE_BGCELLMAX];
	extern eiTextureCell BattleFieldCell[BATTLE_FIELDCELLMAX],ShadowCell;
	extern eiCell BattleRadarCell;
	extern eiCell BattleAnimeCell[ANIMEPATTERN_1];
	extern eiCell BattleStatusCell[BATTLE_STATUSICONMAX];

	extern ei_s32 BattleExperience,BattleMoney,BattleItem,
		BattleItemProb,BattleStartTime;
	extern ei_s32 BattleLineRange[12],BattleCircleRange[12];
	extern ei_s32 BattleActionSource[16];

	extern int AnimePatternCount[BATTLE_ANIMEMAX];
	extern int AnimePatternSize[BATTLE_ANIMEMAX];
	extern ei_s32 BattleAnimeWait[BATTLE_ANIMEMAX];
	extern int PreviousAnimeNumber;

	extern eiD3DParticle BatPart[BATTLE_PARTMAX];
	extern eiD3DLight BatLight[8];
#endif

#endif /*INCLUDE_CRBATTLE_H*/
