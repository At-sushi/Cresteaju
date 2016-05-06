//
#define EF_NOBLANK -1
#define EF_NOFIND -1
//
#define EF_DRAW_AUTOCHANGE 0
#define EF_DRAW_MANUAL 1

//---型宣言
#define EFMAP ei_u16
#define LPEFMAP lpei_u16

//---マップ
#define EF_MAP_MAX 64
#define EF_MAP_NOBLANK EF_NOBLANK
#define EF_MAP_ENEMYAREAMAX 30
#define EF_MAP_ENEMYAREASIZE 20

#define EF_MAP_ENEMYTYPE_NONE 0
#define EF_MAP_ENEMYTYPE_FIELD 1
#define EF_MAP_ENEMYTYPE_DANGEON1 2
#define EF_MAP_ENEMYTYPE_DANGEON2 3
#define EF_MAP_ENEMYTYPE_DANGEON3 4
#define EF_MAP_ENEMYTYPE_DANGEON4 5
#define EF_MAP_ENEMYTYPE_DANGEON5 6
//---プレーン
#define EF_PLANE_MAX 16

//---オブジェクト
#define EF_OBJECT_SURFACEPAGE 2
#define EF_OBJECT_DDOFFSET 0
#define EF_OBJECT_MAX 1024
#define EF_OBJECT_MOVEMACROMAX 32
#define EF_OBJECT_PATTERNSIZE 8
#define EF_OBJECT_PATTERNDIRECTIONSIZE (EF_OBJECT_PATTERNSIZE / 4)
#define EF_OBJECT_PATTERNMAX 16
#define EF_OBJECT_PATTERNOFFSET 256

#define EF_OBJECT_SPEEDMAX 256
#define EF_OBJECT_FREQMAX 10000

//---動き方
#define EF_OBJECT_ST_MOVERANDOM 0x0001
#define EF_OBJECT_ST_MOVEFIXED 0x0002
#define EF_OBJECT_ST_MOVEFOLLOW 0x0004
#define EF_OBJECT_ST_MOVERUNAWAY 0x0008
#define EF_OBJECT_ST_MOVEMACRO 0x0010
	//---不定期周期で動く
#define EF_OBJECT_ST_MOVERANDOMFREQ 0x0020
#define EF_OBJECT_ST_MOVE 0x00ff
//---プレイヤーとの関係
#define EF_OBJECT_ST_RELCANOVER 0x0100
#define EF_OBJECT_ST_RELUPPER 0x0200
#define EF_OBJECT_ST_RELLOWER 0x0400
#define EF_OBJECT_ST_RELAUTOSCROLL 0x0800
#define EF_OBJECT_ST_RELATION 0xff00
//---方向
#define EF_OBJECT_ST_DIRRANDOM 0x010000
#define EF_OBJECT_ST_DIRNORTH  0x020000
#define EF_OBJECT_ST_DIREAST   0x040000
#define EF_OBJECT_ST_DIRSOUTH  0x080000
#define EF_OBJECT_ST_DIRWEST   0x100000
#define EF_OBJECT_ST_DIRTRANS  0x200000
#define EF_OBJECT_ST_DIRECTION 0xff0000
//---アニメーション
#define EF_OBJECT_ST_ANIMEMOVE 0x01000000
#define EF_OBJECT_ST_ANIME     0x0f000000
//---イベント
#define EF_OBJECT_ST_EVENTAUTO 0x10000000
#define EF_OBJECT_ST_EVENT     0x30000000

#define DIR_NORTH 0
#define DIR_EAST 1
#define DIR_SOUTH 2
#define DIR_WEST 3
#define DIR_TRANS 4

//---パターン
#define EF_PATTERN_PAGEMAX 6
//---パターン属性
#define EF_PATTERN_ST_WALK 0x0001
#define EF_PATTERN_ST_OBJNOWALK 0x0002
#define EF_PATTERN_ST_UNDERNOWALK 0xff00

#define EF_PATTERN_MAX 1024
#define EF_PATTERN_PAGESIZE 32
#define EF_PATTERN_DDOFFSET_Y (32 * 7)
#define EF_PATTERN_TRANS EF_PATTERN_MAX
#define EF_OBJECT_TRANS EF_PATTERN_TRANS

#define EF_PLANE_SIZEMAX 512

//---ストリングの最大
#define EF_NAMEMAX 64

//大きさの基準
#define EF_STDMAP 1
#define EF_DELTA_MAX 32
#define EF_PATTERN_SIZE EF_DELTA_MAX

//
#define EF_WINDOW_OFFSET 0

typedef struct
{
	EIPOINT Delta;
	EIPOINT Center;
	EIPOINT Range;
	EIPOINT Field;
	EIPOINT s;
	EIPOINT f;
	EIPOINT Offset;

	int ZoomRate,pSize;
	double doublePutRate;
} EIFIELDDRAW,*LPEIFIELDDRAW;

typedef struct
{
	int x,y;
	int xDelta,yDelta;
	int xSymbol,ySymbol;
	int Direction,MainCharacterAnime;

	int Move,Count;

	int DrawRate,DrawMode,SkipCount,
		PreviousWorkTime[4],RestCount,ChangeRefresh;
	int LimitCount,PatternCount;
	int Debug;

	//---
	int xyMove,MoveMode,MoveDelta;

	int xSize,ySize,MoveSpeed;
	int xTop,yTop,PatternSize;
	int Zoom;

	int EnablePlayerMoveingFlag,PlayerPlane,CantOverObject;
} FIELD,*LPFIELD;

//---プレーンデータ
typedef struct 
{
	int xSize,ySize,ScrollSpeed,Mode,Show;//,DrawMode;
	EIMEMORY hData;
	LPEFMAP lpData;
	int DataSize;

} PLANE_DATA,*LPPLANE_DATA;

//---オブジェクトデータ
typedef struct
{
	int Flag;//use or no use
	int x,y,Plane,xDelta,yDelta;
	int GraphicNumber,Status,Number,Direction;
	int MoveSpeed,MoveFreq,MoveCount;
	int AnimePos,AnimeCount,AnimeWait,AnimeFlag;
	ei_u8 MoveMacro[EF_OBJECT_MOVEMACROMAX];

} OBJECT_DATA,*LPOBJECT_DATA;

//---保存する必要のないデータ
typedef struct
{
	ei_s32 KpDirection,KpDirection2;
} OBJECT_NOSAVE_DATA,*LPOBJECT_NOSAVE_DATA;

//---オブジェクトクラス
class EI_API eiMapObject
{
public:
	eiMapObject(void);
	~eiMapObject();

	void Init(void);
	void Delete(void);
	int GetFlag(void);
	int Create(int Number);

	int Put(LPEIFIELDDRAW lpefd);
	int xGet(void);
	int yGet(void);
	int SetPos(int x,int y,int PlaneNumber);
	int SetPattern(int Number);
	int GetPattern(void);
	int SetStatus(int Status);
	int GetStatus(void);
	int SetPlane(int Plane);
	int GetPlane(void);
	int SetDirection(int Direction);
	int GetDirection(void);
	void SaveDirection(void);
	void RestoreDirection(void);
	void SaveDir(void);
	void RestoreDir(void);
	int IsThere(int x,int y,int plane = -1);
	//---アニメーション
	int StartAnime(int force = 0);
	int EndAnime(int force = 0);
	int DoAnime(int frame = 1);
	int SetAnimePos(int Pos);
	int GetAnimePos(void);
	//---オブジェクトの移動
	int Move(int frame = 1);
	int MoveDelta(int dx,int dy);
	int AddMoveCount(int frame);

	//---座標
	int xGetForward(void);
	int yGetForward(void);

	int SetData(LPOBJECT_DATA lpData);
	int GetData(LPOBJECT_DATA lpData);

	int Save(FILE *fp);
	int Save(eiFile *pfile);
	int Load(eiFile *pfile/*FILE *fp*/);

	OBJECT_DATA Data;
	//---保存する必要のないデータ
	OBJECT_NOSAVE_DATA NoSaveData;
};

//---マップデータ
typedef struct
{
	int UsePlane[EF_PLANE_MAX];
	PLANE_DATA Plane[EF_PLANE_MAX];

	//オブジェクト
	int ActiveObject;
	eiMapObject *lpObject;//[EF_OBJECT_MAX];
	EISTR Name[EF_NAMEMAX];
	int BlankPattern;
	ei_u8 EnemyArea[EF_MAP_ENEMYAREAMAX][EF_MAP_ENEMYAREAMAX];

} MAP_DATA,*LPMAP_DATA;

//---パターンデータ
typedef struct
{
	int Status;
	ei_s16 NextAnime,AnimeUpdata,AnimeWait,AnimeCount;
} MAP_PATTERNDATA,*LPMAP_PATTERNDATA;

//---eiMap構造体
typedef struct
{
	EISTR GroupName[EF_NAMEMAX];
	EISTR PatternFileName[EF_PATTERN_PAGEMAX][32];
	EISTR ObjectFileName[EF_OBJECT_PATTERNMAX][32];
	int UseMap[EF_MAP_MAX];
	MAP_PATTERNDATA Pattern[EF_PATTERN_MAX];
	int ActiveMap,ActivePattern;
	int BasePlane;

	MAP_DATA *Map[EF_MAP_MAX];
	EIMEMORY eiMemMap[EF_MAP_MAX];

	int EnemyType;
	int Compress;
	int Reserved[15];
} MAP,*LPMAP;

/*typedef struct
{
	EISTR GroupName[EF_NAMEMAX];
	EISTR PatternFileName[EF_PATTERN_PAGEMAX][32];
	EISTR ObjectFileName[EF_OBJECT_PATTERNMAX][32];
	int UseMap[EF_MAP_MAX];
	MAP_PATTERNDATA Pattern[EF_PATTERN_MAX];
	int ActiveMap,ActivePattern;
	int BasePlane;

	MAP_DATA *Map[EF_MAP_MAX];
	EIMEMORY eiMemMap[EF_MAP_MAX];
} MAPOLD,*LPMAPOLD;*/

//---マップ管理クラス
class EI_API eiMap
{
public:
	eiMap(void);
	~eiMap();
	void Init(void);

	int Save(EISTR *name);
	int Load(EISTR *name,EISTR *slname = NULL,int mode = EI_NORMALFILE);
	int ReadPattern(EISTR *name,EISTR *slname,int mode,int page);
	int ReadObject(EISTR *name,EISTR *slname,int mode,int number);
	void ReloadPattern(void);

	int Create(int MapNumber,int xSize = -1,int ySize = -1);

	int DeletePlane(int MapNumber,int PlaneNumber);
	int DeleteMap(int MapNumber);
	int Delete(void);
	int CreatePlane(/*LPMAP_DATA lpmap*/int MapNumber,int PlaneNumber,
							  int xSize,int ySize,int trans = 0);
	//---サーフェイスにセット
	void SetSurface(void);
	void SetPatternSurface(int page);
	void SetObjectSurface(int number);
	//---バッファ書き込み読み込み
	int Put(int x,int y,int PlaneNumber,int Pattern);
	int Get(int x,int y,int PlaneNumber);

	//---オブジェクト
	ei_s32 GetMaxObject(void);
	ei_s32 GetMaxObjectIndex(void);
	void InitObjectIndex(void);
	void AddObjectIndex(int number);
	void DeleteObjectIndex(int number);
	int GetObjectPointer(int Number,eiMapObject *lpObject);
	int GetBlankObject(int start = 0);
	int SetActiveObject(int Number);
	int GetActiveObject(void);
	int SetObject(int number,int x,int y,int plane,int kind = 0,int mode = 0);
	int DeleteObject(int number);
	int SetObjectStatus(int Number,LPOBJECT_DATA lpData);
	int GetObjectStatus(int Number,LPOBJECT_DATA lpData);
	int IsObject(int x,int y,int plane = -1,int map = -1);

	int DoObjectAnime(int frame = 1);
	int SetObjectAnimePos(int Number,int frame = 1);
	int GetObjectAnimePos(int Number);

	eiMapObject* GetObject(int Number,int MapNumber = -1);

	//---マップ設定
	int SetActiveMap(int MapNumber);
	int GetActiveMap(void);
	void SetGroupName(EISTR *Name);
	void SetMapName(int MapNumber,EISTR *Name);
	EISTR *GetGroupName(void);
	EISTR *GetMapName(int MapNumber);
	int GetBlankPlaneNumber(int MapNumber);
	int GetBlankMapNumber(void);
	int SetBasePlane(int PlaneNumber);
	int GetBasePlane(void);
	int SetBlankPattern(int MapNumber,int Number);
	int GetBlankPattern(int MapNumber);
	int SetPlaneSpeed(int MapNumber,int PlaneNumber,int Speed);
	int GetPlaneSpeed(int MapNumber,int PlaneNumber);
	int xGetMapSize(int MapNumber);
	int yGetMapSize(int MapNumber);
	int xGetPlaneSize(int MapNumber,int PlaneNumber);
	int yGetPlaneSize(int MapNumber,int PlaneNumber);
	int IsUsedPlane(int MapNumber,int PlaneNumber);
	int IsUsedMap(int MapNumber);
	int IsMapRange(int MapNumber);
	int IsPlaneRange(int PlaneNumber);
	int GetEnemyType(void);
	int SetEnemyType(int type);
	int GetEnemyArea(int x,int y);

	//---パターン
	int SetActivePattern(int Number);
	int GetActivePattern(void);
	int DoPatternAnime(int frame = 1);
	int SetPatternStatus(int Number,int Status);
	int GetPatternStatus(int Number);
	int SetPatternData(int Number,MAP_PATTERNDATA *lpData);
	int GetPatternData(int Number,MAP_PATTERNDATA *lpData);

	MAP Data;
	eistr Directory[_MAX_PATH],SLinkFileName[_MAX_PATH];
	ei_s32 FileMode,MaxObject,MaxObjectIndex,ObjectIndex[EF_OBJECT_MAX];
};

class EI_API eiField
{
public:
	eiField(void);
	SetDebugMode(int mode);

	//---Move Mode
	void SetMoveEnything(int mode = 1);//Anyの間違い^^;
	int GetMoveEnything(void);

	//---Object
	int MoveObject(eiMap *lpeimap,int frame = 1,int not_random = 0,int new_move = 1);

	void SetFieldSize(int sx,int sy);
	int GetPatternSize(void);
	int xGetFieldSize(void);
	int yGetFieldSize(void);
	int xGetFieldTop(void);
	int yGetFieldTop(void);
	void SetFieldTop(int sx,int sy);
	int SetFieldZoom(int zoom);
	int GetFieldZoom(void);

	//---posision
	int xGet(void);
	int yGet(void);
	int xSet(int x);
	int ySet(int y);
	int xGetDelta(void);
	int yGetDelta(void);
	int GetMoveDelta(void);
	int SetMoveDelta(int delta);
	int SetPlayerPlane(int plane);
	int GetPlayerPlane(void);
	void SetDirection(int dir);
	int GetDirection(void);
	int SetMoveSpeed(int speed);
	int GetMoveSpeed(void);


	int ReadWindow(EISTR *name,EISTR *slname,int mode);
	//---Moving
	int Move(eiMap *lpmap,int key = 1,int fx  = 0,int fy  = 0);
	int SetPlayerMove(int mode);
	int GetPlayerMove(void);
	//---drawing
	int Draw(eiMap *lpeimap,int mode);
	//---object
	int IsThereObject(eiMap *lpeimap,int x,int y,int object_number = -1);
	int CanPlayerMove(eiMap *lpeimap,int x,int y);
	ei_u32 SeekEfectPattern(eiMap *lpeimap,int start_plane,int end_plane,int x,int y);

	int IsOnFieldWindow(int sx,int sy);
	int CalcFieldWindowPos(LPEIPOINT lpPoint);//(int *x,int *y);
	int CalcScreenToMap(eiMap *lpmap,LPEIPOINT lpPoint);//,int *x,int *y);

	//---Refresh & Wait
	int CalcRefreshRateAndWait(int set = 0);
	int SetDrawRate(int rate);
	int GetDrawRate(void);
	int SetDrawMode(int mode);
	int GetDrawMode(void);
	int GetAutoChangeStatus(void);
	int SetMarginOfErrorFPS(int margin);
	int GetMarginOfErrorFPS(void);

	//---MainCharacter
	int SetOverObject(int mode);
	int GetOverObject(void);
	int SetMainCharacter(int mode);
	int GetMainCharacter(void);
	void SetMainCharacterCallback(void (*func)(eiCell *,int ,int, int, int, int));
	void AnimeMainCharacter(int frame = 1);
	//---Callback
	void SetBGCallback(void (*func)(eiCell *,int ,int, int, int, int));
	void SetFGCallback(void (*func)(eiCell *,int ,int, int, int, int));

	int xGetForward(void);
	int yGetForward(void);

	FIELD Field;

	void (*MainCharacterCallback)(eiCell *,int ,int ,int ,int ,int );
	void (*BGCallback)(eiCell *,int ,int ,int ,int ,int );
	void (*FGCallback)(eiCell *,int ,int ,int ,int ,int );
private:
	int DrawMainCharacter,MoveEnything,MarginOfErrorFPS;
};

//---関数
#ifndef EI_FIELD
	extern EI_API int eiFieldInit(eiWindow *ew,eiPalette *ep,
		eiInput *ei,eiTime *et,eiCell *ec,eiCell *ed);
	extern EI_API int eiFieldInitAscii(int y,int col,int page);
	extern EI_API void eiFieldDrawText(eiCell *lpCell,EISTR *string,int sx,int sy,int mode = EI_TRANS);
#endif
