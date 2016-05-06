//----------------------------
CRBATTLEDLLMAIN_API DWORD crbatGetVersion(void);

CRBATTLE_API int crbatInitDLL(CRESTEAJU_GAMEDATA *pgameusingdata,
							 CRESTEAJU_GAMEINFO *pgame,
							 CRESTEAJU_PARTYINFO *pparty,
							 CrCharacter *pplayer,
							 CrItem *pitem,CrMagic *pmagic,
							 int *pdebug,int *pfilemode,
							 CRESTEAJU_SYSTEM *psystem,CRESTEAJU_INITIALIZE *pini,
							 CRESTEAJU_CHARACTERINFO *penemychara,CRESTEAJU_BATTLECHARAINFO *penemybat);

CRBATTLE_API int crbatGotoBattle(CR_BATTLEINFO *pInfo /*= NULL*/);
CRBATTLE_API int crbatEventBattle(CR_BATTLEINFO *pInfo = NULL);
CRBATTLE_API int crbatFieldBattle(int map,int area);
CRBATBASE_API int crbatSetBattleItemMode(int mode);
CRBATBASE_API int crbatGetBattleItemMode(void);

//---base
CRBATBASE_API int crbatSetBattleSpeed(int speed);
CRBATBASE_API int crbatGetBattleSpeed(void);
CRBATBASE_API int crbatSetBattleMagicMode(int mode);
CRBATBASE_API int crbatGetBattleMagicMode(void);
CRBATBASE_API int crbatSetBattleKizetuMode(int mode);
CRBATBASE_API int crbatGetBattleKizetuMode(void);

//---camera
CRBATBASE_API float crbatGetCameraAngle(float fcx,float fcy,float fdx,float fdy);
CRBATBASE_API int crbatSetCamera(int camera,float cx,float cy,float cz,float dx,float dy,float dz,float angle = 0.0f);
CRBATBASE_API int crbatSetCamera_ViewBattleField(int camera,float angle,int moving = 0,int run_time = 500);

CRBATBASE_API int crbatTranslatePos(float x,float y,float z,float *dx,float *dy,float *dz);
CRBATBASE_API void crbatPut3DCell(eiTextureCell *pCell,float sx,float sy,float sz,float limit = 0.50f);
CRBATBASE_API int crbatTranslate3DTo2D(
	float sx,float sy,float sz,
	float *dx ,float *dy ,float *dz ,float *rate);
CRBATBASE_API int crbatGetViewMode(void);
CRBATBASE_API void crbatSetViewMode(int mode);
//---
CRBATBASE_API int crbatGetEnemyCount(void);

//---status
CRBATBASE_API void crbatShowStatus(int x = -1,int y = -1,int mode = -1);
CRBATBASE_API void crbatDrawScreen(void);
CRBATBASE_API void crbatSetupCharaPattern(void);
CRBATBASE_API void crbatSetShowStatus(int show);
CRBATBASE_API int crbatEnableShowStatus(void);

//---init
CRBATINIT_API int crbatInitBattle(CR_BATTLEINFO *pInfo,int retry);
CRBATINIT_API int crbatEndBattle(CR_BATTLEINFO *pInfo,int thread_end);

//---command
CRBATCOMMAND_API int crbatInputCommand(int turn,CR_BATTLEINFO *pInfo);

//---２Ｄキャラクター描画構造体
class CRBATTLECLASS CrBattleObject
{
public:
	CrBattleObject(void);
	~CrBattleObject();
	void Init(void);

	void CreateTLVertexRect(float r,int alpha);

	void SetAlphaMode(int mode);
	void SetMoveSpeed(float speed);
	void SetMoveVectorXYZ(float x,float y,float z);
	void SetDrawMode(int mode);
	void SetXRate(float rate);
	void SetYRate(float rate);
	void SetTexture(eiTextureCell *pc);

	void SetCell(eiCell *pc);
	eiCell *GetCell(void);
	void SetPattern(int pattern);
	int GetPattern(void);
	void SetPos(float sx,float sy,float sz);
	float GetX(void);
	float GetY(void);
	float GetZ(void);

	//---アニメーション
	void SetAnime(int number);
	int DoAnime(float AddWorld);
	int Move(float AddWorld);

	BATTLEOBJECTINFO ObjectInfo;
};


//---バトルキャラクタークラス
class CRBATTLECLASS CrBattleCharacter:public CrCharacter
{
public:
	CrBattleCharacter(void);
	~CrBattleCharacter();

	int KindOf(void);
	void InitBattleCharacter(void);

	//---
	int DoExist(void);
	int DoExistExtend(void);
	void SetExistance(int exist);

	//---グラフィック管理
	void SetCell(eiCell *pc);
	eiCell *GetCell(void);
	void SetPattern(int number);
	void SetPatternAuto(void);
	int GetPattern(void);
	void SetDrawType(int type);
	int GetDrawType(void);

	//---アニメーション
	int GetAnimeMode(void);
	void BeginAnimeAtack(void);
	void BeginAnimeGun(void);
	void BeginAnimeMagic(void);
	void BeginAnimeItem(void);
	void BeginAnime(int anime);
	void EndAnime(void);
	float DoAnime(float AddWorld);
	void SetAnimePattern(ei_s32 *pAnime);
	void SetAnimeLimitTime(float limit);
	float GetLeftTime(void);
	void SetAnimeMoving(float x,float y,float z,float speed = CHARSPEED_RUN,int mode = 0);
	void SetMoveSpeed(float speed);
	int IsAnime(void);

	int SetNotShow(int show);
	int DontShow(void);

	float GetAnimeX(void);
	float GetAnimeY(void);
	float GetAnimeZ(void);

	//---座標管理
	void SetFieldPos(ei_s32 sx,ei_s32 sy,ei_s32 sz = 0);
	ei_s32 GetFieldX(void);
	ei_s32 GetFieldY(void);
	ei_s32 GetFieldZ(void);
	ei_s32 GetCharaWidth(void);
	ei_s32 GetCharaHeight(void);
	void SetAngle(float angle);
	float GetAngle(void);
	float GetCharaAngle(CrBattleCharacter *pChara);
	float GetDistance(CrBattleCharacter *pChara);
	void SetZOffset(float offset);
	float GetZOffset(void);

	//---カメラ
	void MoveCamera(float angle,float r,int run_time,int camera = 0);
	void BeginMovingCameraFront(int camera = 0);
	void BeginMovingCameraAngle(float angle,float r,int camera = 0);
	void SetCameraFront(int camera = 0);
	void SetCameraAngle(float angle,float r,int camera = 0);
	void GetCameraAngle(float angle,float r,
		float *cx,float *cy,float *cz,float *dx,float *dy,float *dz);
	//---判別
	ei_s32 IsFriend(void);
	ei_s32 GetNumber(void);
	ei_s32 GetType(void);//---種族
	void SetType(int type);

	//---command
	void ResetCommand(void);
	void ClearCommand(void);
	void SetCommand(ei_s32 maincom,ei_s32 target,ei_s32 *sub = NULL);
	CR_BATTLECOMMAND GetCommand(void);
	ei_s32 GetCommandMain(void);
	ei_s32 GetCommandTarget(void);
	ei_s32 GetCommandSub(int number);
	ei_s32 IsEnableCommandInput(void);

	CrBattleCharacter *GetTarget(void);
	void SetTarget(CrBattleCharacter *pChara);

	//---battle
	ei_s32 ResultLP(int number);
	ei_s32 Sokushi(void);

	ei_s32 GetBtAtack(int number);
	ei_s32 GetBtDefense(void);
	ei_s32 GetBtMagicDefense(void);
	ei_s32 GetBtAction(void);

	ei_s32 GetBtPower(void);
	ei_s32 GetBtVitality(void);
	ei_s32 GetBtAgility(void);
	ei_s32 GetBtSoul(void);
	ei_s32 GetBtMagic(void);

	ei_s32 GetBtHitProb(int number);
	ei_s32 GetBtMagicHitProb(CrMagic *pMagic);
	ei_s32 GetBtSubHitProb(void);//---命中補正率
	ei_s32 SetBtSubHitProb(int value);//---命中補正率
	ei_s32 GetBtAvoidProb(void);
	ei_s32 GetBtMagicAvoidProb(void);

	ei_s32 GetBtWeaponAnime(int number);
	ei_s32 IsBtWeaponDirect(int number);

	ei_s32 GetBtMove(void);//---移動力

	//---Element
	ei_s32 GetBtElement(int element);
	//---Magic
	void ResetMagicTime(int reset = 0);
	ei_s32 AddFromLastMagic(void);
	ei_s32 GetFromLastMagic(void);
	//---defense count
	void ResetDefenseCount(void);
	void AddDefenseCount();
	ei_s32 GetDefenseCount(void);

	//---Status
	ei_s32 IsEnableAction(void);
	ei_s32 IsEnableMagic(void);
	ei_s32 IsEnableMoveing(void);
	ei_s32 IsEnableEscape(void);
	ei_s32 IsDown(void);
	ei_s32 IsKizetu(void);
	ei_u32 GetBtStatus(void);
	ei_u32 GetBtStatusContinue(int status);
	ei_u32 GetBtStatusContinueMax(int status);
	void AddTurnStatus(int status,int turn = 1);
	void ClearBtStatus(ei_u32 status = 0);
	void AddBtStatus(ei_u32 status , int ext = 1);
	int GetBit(ei_u32 status);
	int GetStatusContinueTime(ei_u32 status);
	void CureStatus(void);

	ei_s32 Ability(ei_s32 ability);
	void SetAbility(ei_s32 ability,int flag);

	ei_s32 GetMCRate(void);
	ei_s32 GetStatusChangeRate(int rate);
	ei_s32 GetStatusRecoveryRate(int rate);

	ei_s32 SetBattleFlag(int number,int flag);
	ei_s32 GetBattleFlag(int number);

	ei_u32 GetFirstAtack(void);
	void EnableFirstAtack(int enable);
	ei_u32 GetFirstestAtack(void);
	void EnableFirstestAtack(int enable);

	//---共通ターンフラッグ
	ei_s32 GetTurnAtack(void);
	void AddTurnAtack(int value = 1);
	void ResetTurnAtack(void);
	//---パーソナルターンフラッグ
	ei_s32 GetPersonalTurn(void);
	void AddPersonalTurn(int value = 1);
	void ResetPersonalTurn(void);

	//---カオスターン
	void AddKaosTurn(void);
	void ResetKaosTurn(void);
	ei_s32 GetKaosTurn(void);
	//---ワールドターン
	void SetWorldTurn(int turn);
	void AddWorldTurn(int value);
	ei_s32 GetWorldTurn(void);
	void SetWorldCountTurn(int turn);
	void AddWorldCountTurn(int value);
	ei_s32 GetWorldCountTurn(void);
	//---オートガード
	void SetAutoGard(int set);
	ei_s32 GetAutoGard(void);

	//---special
	ei_s32 SetSpecialDisable(int turn);
	ei_s32 SubSpecialDisable(int sub);
	ei_s32 GetSpecialDisable(void);
	ei_s32 SpecialEnableUse(void);
	ei_s32 GetEnableSpecial(void);

	//---battle history
	void HistoryAddReceiveDamage(int damage);
	void AddRuinDamage(int damage);
	void ResetRuinDamage(void);
	ei_s32 GetRuinDamage(void);

	//---Enemy
	void AddEnemyExperience(void);
	void AddEnemyMoney(void);

	CRESTEAJU_BATTLECHARAINFO BattleInfo;
	CR_BATTLEONLYINFO OnlyInfo;
	CR_BATTLECOMMAND Command;
	CrBattleObject StatusObject[BATTLE_STATUSICONMAX];
	static ei_s32 TurnAtack;
};


//---２Ｄキャラクター描画構造体
class CRBATTLECLASS CrBattleDamage
{
public:
	CrBattleDamage(void);
	~CrBattleDamage();

	void SetCharacter(CrBattleCharacter *pChara);
	void SetDamage(int damage,int miss,int mode);
	void SetDelay(int del);
	int AddWorld(float world);
	void Draw(void);

	ei_s32 CenterX,CenterY,CenterZ;
	float z[5],dz[5];
	ei_s32 Delay[5],Damage,DamageMode,Time[5];
	ei_s32 Number[5];
};

//---ダメージ情報
typedef struct
{
	ei_s32 Damage[BATTLECHARA_MAX + 1],Miss[BATTLECHARA_MAX + 1],
		DamageMode[BATTLECHARA_MAX + 1],
		DamageRate[BATTLECHARA_MAX + 1],DontShowThisDamage[BATTLECHARA_MAX + 1];
	CrBattleCharacter *pList[BATTLECHARA_MAX + 1];
} CR_BATTLE_DAMAGEINFO;

//---drawing
CRBATTLEDRAW_API void crbatDraw_SetViewport(int number);
CRBATTLEDRAW_API void crbatDraw_SetMatrix(int number);
CRBATTLEDRAW_API void crbatDraw_SetWorldMatrixDelta(float x,float y,float z);
CRBATTLEDRAW_API void crbatSetBattleLight(ei_u32 color);
CRBATTLEDRAW_API float crbatSetDrawingZClip(float z);
CRBATTLEDRAW_API float crbatGetDrawingZClip(void);
CRBATTLEDRAW_API void crbatClearDrawingList(void);
CRBATTLEDRAW_API void crbatAddDrawingList(CrBattleCharacter *pChara,int view = -1,int front = 0);
CRBATTLEDRAW_API void crbatAddDrawingList(CrBattleObject *pObject,int view = -1,int front = 0,CrBattleCharacter *pChara = NULL);
CRBATTLEDRAW_API void crbatAddDrawingListAll(int view = -1);
CRBATTLEDRAW_API void crbatAddDrawingListFriend(int view = -1);
CRBATTLEDRAW_API void crbatAddDrawingListEnemy(int view = -1);
CRBATTLEDRAW_API void crbatSetDrawSceneCallback(void(*pFunc)(eiCell *,int));
CRBATTLEDRAW_API void crbatSetDrawSceneCallback2(void(*pFunc)(eiCell *,int));
CRBATTLEDRAW_API int crbatDrawRefresh(void);
CRBATTLEDRAW_API int crbatDrawScene(void);
CRBATTLEDRAW_API int crbatDrawSceneWhile(int DrawTime);
CRBATTLEDRAW_API void crbatDraw_Clear(void);
CRBATTLEDRAW_API void crbatDraw_ClearMenuArea(void);
CRBATTLEDRAW_API void crbatDraw_CopyScreen(void);
CRBATTLEDRAW_API void crbatDoMovingCamera(int run_time = 500);
CRBATTLEDRAW_API void crbatBeginMovingCamera(int camera,float cx,float cy,float cz,float dx,float dy,float dz);
CRBATTLEDRAW_API void crbatMoveCamera(int camera,float cx,float cy,float cz,
								  float dx,float dy,float dz,int run_time = 500);
CRBATTLEDRAW_API int crbatSetCameraWithObject(CrBattleCharacter *pChara,
						CrBattleCharacter **ppList,int run_time = 500,
						CrBattleCharacter **ppReturnCenter = NULL);
CRBATTLEDRAW_API void crbatBeginCameraObjectToObject(
					int camera,
					CrBattleCharacter *pSrc,CrBattleCharacter *pDst,
					float RotateAngle,float DeltaSrcR = -1,float DeltaDstR = -1,
					int run_time = 250);
CRBATTLEDRAW_API int crbatCreateRadar(int tx = -1,int ty = -1);
CRBATTLEDRAW_API int crbatDrawRadar(int tx = -1,int ty = -1);
CRBATTLEDRAW_API int crbatDrawRadar_Cursor(CrBattleCharacter *pChara,int tx = -1,int ty = -1);
CRBATTLEDRAW_API int crbatDrawRadar_Appeare(CrBattleCharacter *pChara,int run_time = 250,int tx = -1,int ty = -1);
CRBATTLEDRAW_API int crbatDrawRadar_Range(int x,int y,int tx = -1,int ty = -1);
CRBATTLEDRAW_API int crbatShowDamage(CR_BATTLE_DAMAGEINFO *pDamageInfo);
CRBATTLEDRAW_API void crbatCopyScene(void);
CRBATTLEDRAW_API void crbatDrawSceneFast(void);

CRBATTLEDRAW_API void crbatChangeSlowView(int DstMode,int run_time = 200);
CRBATTLEDRAW_API void crbatDrawFlash(int r,int g,int b);

CRBATANIME_API void crbatStartFade(ei_s32 red,ei_s32 green,ei_s32 blue,int FadeTime);
CRBATANIME_API void crbatAnime_Flash(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,
			int RunTime,int r,int g,int b);

CRBATTLEDRAW_API void crbatSetAddAlpha(void);
CRBATTLEDRAW_API int crbatIsEnableAddAlpha(void);

//---BattleWindow
CRBATTLEDRAW_API void crbatBWCreate(CrStringWindow *pWin,eistr *pString,
				int pos = BW_CENTER | BW_TOP,int camera = 0);

//---base
CRBATBASE_API int crbatGetTargetChara(CrBattleCharacter *pSrc,CrBattleCharacter *pChara,ei_s32 Range,
					 	CrBattleCharacter **ppList,int Crash = 0);
CRBATBASE_API int crbatMakeCharaList(CrBattleCharacter **ppList,
				CrBattleCharacter *pSrc,int mode,
				int include_minasLP = 0);
CRBATBASE_API CrBattleCharacter* crbatRandomSelect(CrBattleCharacter *pSrc,int mode,
												  int include_minasLP = 0);
void crbatSetAllCharacterDirection(CrBattleCharacter *pChara,CrBattleCharacter **ppList);
CRBATBASE_API int crbatIsThere(ei_s32 x,ei_s32 y,CrBattleCharacter *pChara  = NULL);
CRBATBASE_API int crbatIsThere(CrBattleCharacter *pChara);
CRBATBASE_API int crbatIsFieldRange(ei_s32 x,ei_s32 y);
//---
CRBATBASE_API void crbatSetCharaAngleToCenter(CrBattleCharacter *pChara);
CRBATBASE_API void crbatSetCharaAngleToCenterAll(void);
CRBATBASE_API void crbatSetCharaAngleToRandomAll(void);
CRBATBASE_API void crbatSetCharaAngleToRandom(CrBattleCharacter *pChara);

CRBATBASE_API int crbatGetBattleStatusString(CrBattleCharacter *pChara,eistr *pstr);
CRBATBASE_API int crbatGetBattlePlusStatusString(CrBattleCharacter *pChara,eistr *pstr,int b);
CRBATBASE_API int crbatGetBattleResultStatusString(CrBattleCharacter *pChara,eistr *pstr,int b);

//---main
CRBATMAIN_API int crbatBattleMain(CR_BATTLEINFO *pInfo);
CRBATMAIN_API void crbatResetTurn(int set);
CRBATMAIN_API int crbatGetResetTurn(void);
CRBATMAIN_API void crbatSetTurn(int turn);
CRBATMAIN_API int crbatGetTurn(void);
CRBATMAIN_API int crbatCalcDamage(CR_BATTLE_DAMAGEINFO *pDamageInfo,
			CrBattleCharacter *pSrcChara,
			int src,int src_rate,int dst,int dst_rate,
			int calc_mode,int calc_rate,int diffusse,int element,
			int prob_mode,int proberb,int defense_mode);
CRBATMAIN_API int crbatResultDamage(CR_BATTLE_DAMAGEINFO *pDamageInfo);
CRBATMAIN_API int crbatShowResult(void);
CRBATMAIN_API int crbatGetCalcData(CrBattleCharacter *pSrcChara,CrBattleCharacter *pDstChara,int calc);
CRBATMAIN_API void crbatSetDamageMode(CR_BATTLE_DAMAGEINFO *pDamageInfo,int damage_mode);
CRBATMAIN_API void crbatDoAction_AddWeaponEfectBefore(CR_BATTLE_DAMAGEINFO *pDamageInfo,
					int *pSrcRate,int *pDstRate,
					CrBattleCharacter *pChara,int weapon);
CRBATMAIN_API void crbatDoAction_AddWeaponEfectAfter(CR_BATTLE_DAMAGEINFO *pDamageInfo,
					CrBattleCharacter *pChara,int weapon);
CRBATMAIN_API int crbatDoAction_CounterAtack(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int EnableCounter);

//---CPU
CRBATCPU_API int crbatCPUThink(CrBattleCharacter *pChara,int turn);
CRBATCPU_API int crbatCPUBeforeAction(CrBattleCharacter *pChara,int turn);

//---Anime
CRBATANIME_API void crbatBeginAnime(void);
CRBATANIME_API void crbatEndAnime(void);
CRBATANIME_API int crbatLoadExtCharacter_Jumping(CrBattleCharacter *pChara);
CRBATANIME_API int crbatLoadExtCharacter(CrBattleCharacter *pChara,int start,int number);
CRBATANIME_API int crbatLoadExtCharacter_Running(CrBattleCharacter *pChara);
CRBATANIME_API int crbatLoadExtCharacter_Magic(CrBattleCharacter *pChara);
CRBATANIME_API int crbatLoadExtCharacter_Item(CrBattleCharacter *pChara);
CRBATANIME_API int crbatLoadExtCharacter_Gun(CrBattleCharacter *pChara);

CRBATANIME_API void crbatDoAnime_Weapon(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,int critical,int option = 0);
CRBATANIME_API void crbatDoAnime_Kaifuku(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo);
CRBATANIME_API void crbatDoAnime_Magic(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,int force_number);
CRBATANIME_API void crbatDoAnime_Move(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo);
CRBATANIME_API void crbatDoAnime_Move2(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,
				int *x,int *y,float speed);
CRBATANIME_API void crbatDoAnime_LockOn(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo);
CRBATANIME_API int crbatLoadAnime(int number);
CRBATANIME_API int crbatReleaseAnime(void);
CRBATANIME_API void crbatAnime_PreMagic(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo);
CRBATANIME_API void crbatAnime_AfterMagic(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo);
CRBATANIME_API void crbatAnime_Fade(ei_s32 red,ei_s32 green,ei_s32 blue,int FadeTime);

//---Magic
CRBATMAGIC_API int crbatDoAction_Magic(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int ext_rate = 1000,int refrection = 1);
//---EnemyAbility
CRBATENEMYABILITY_API int crbatDoAction_EnemyAbility(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin);

//---special
CRBATMAIN_API int crbatDoAction_Special(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin);

