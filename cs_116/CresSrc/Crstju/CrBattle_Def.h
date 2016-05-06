//---------------------------------------------------------
//---------------------------------------------------------

//---バトルファンクション返値
#define BATRET_OK 0
#define BATRET_WIN 1
#define BATRET_AVOID 2
#define BATRET_LOSE 3
#define BATRET_FORCEBREAK 10

#define BATSTART_NORMAL 0
#define BATSTART_SENSEI 1
#define BATSTART_FUIUCHI 2
#define BATSTART_BACKATACK 3
#define BATSTART_HASAMIUCHI 4

#define BATTLE_INFOWINDOW_FONT EINORMAL_FONT

//---角度・カメラ
#define ANGLE(x) ((float)(x) * (3.1415f / 180.0f))
#define CALC_ANGLE(x) {\
	if((x) < ANGLE(0)){\
		while((x) < ANGLE(0)){ x += ANGLE(360); }\
	} else if((x) >= ANGLE(360)){\
		while((x) >= ANGLE(360)){ x -= ANGLE(360); }\
	}\
}

//---座標補正変換
#define CRBAT_TRANSLATE_CHARA_X(x) ((BATTLEFIELD_MAX_X - 1) - x)
#define CRBAT_TRANSLATE_CHARA_Y(x) (x)

//	((x) < 0.0f ? ((x) + (float)3.141f) :((x) >= 3.1415f ? ((x) - (float)3.1415f) : (x)))
#define CAMERA_DEFAULT_Z 1.0f
#define CAMERA_DEFAULT_R 10.0f

//---バトルフィールド
#define BATTLEFIELD_PTN_SIZE 1
#define BATTLEFIELD_MAX_X 12
#define BATTLEFIELD_MAX_Y 12
#define BATTLEFIELD_PTN_PIXELSIZE 16

#define BATTLEFIELD_VERTEXCOUNT_X (BATTLEFIELD_MAX_X / BATTLEFIELD_PTN_SIZE)
#define BATTLEFIELD_VERTEXCOUNT_Y (BATTLEFIELD_MAX_Y / BATTLEFIELD_PTN_SIZE)

#define BATTLE_ZDEPTH 1000.0f

//-----------------------------
//---ビュー
#define BATTLE_VIEWMAX 8

#define BATTLE_VIEWMODE_FULLSCREEN 0
#define BATTLE_VIEWMODE_SINGLE 1
#define BATTLE_VIEWMODE_DOUBLE 2
#define BATTLE_VIEWMODE_HALF 3
#define BATTLE_VIEWMODE_TEMP 7

#define BATTLE_DRAWINGLISTMAX 128

//---BattleCharacter
#define BATTLECHARA_MAX 20
#define BATTLECHARA_PARTY_MAX 5
#define BATTLECHARA_STARTENEMY 5
#define KEEPCHARA_MAX (BATTLE_ENEMYMAX * 2)

#define CHARA_FRIEND 0
#define CHARA_ENEMY 5
#define BATTLE_ENEMYMAX 10

#define CHARSPEED_RUN 18.0f
#define CHARSPEED_WALK 7.0f
#define CHARSPEED_TOBU 18.0f

//---Pattern
#define BATTLE_CHARAPATTERN 32
#define BATTLE_CHARAALYAWSSURFACE 8
#define BATTLE_ENEMYPATTERNSIZE 32
#define BATTLE_ENEMYPATTERN (BATTLE_ENEMYMAX * 32)
#define BATTLE_FIELDCELLMAX 64
#define BATTLE_BGCELLMAX 4
#define BATTLE_STATUSICONMAX 12

#define BATTLE_ANIMEMAX 100
#define BATTLE_ANIMESURFACE 384

#define BATTLE_TEMPSURFACE_Y (32 * 2)
#define BATTLE_EXTCHARASURFACE (480 - 128)
#define BATTLE_EXTCHARASURFACE_MAX 20

#define BATTLE_STATUSICONSURFACE_X 256
#define BATTLE_STATUSICONSURFACE_Y (480 - 32 * 3)

//---Object
#define BATTLEOBJECT_MAX 64

#define BATTLE_PARTMAX 1024

//---Command
#define BATTLE_COMMAND_LEFT (32)
#define BATTLE_COMMAND_TOP (256 + 32 + 0)

//---radar
//#define BATTLE_RADAR_X (640 - ((12 * BATTLEFIELD_PTN_PIXELSIZE) + 32))
//#define BATTLE_RADAR_Y (16 + 32)
#define BATTLE_RADAR_X (32)
#define BATTLE_RADAR_Y (16 + 32)

//---ダメージ計算
#define SRC_LEVEL     0
#define SRC_LP        1
#define SRC_MC        2
#define SRC_WEAPON    3
#define SRC_DEFENSE   4
#define SRC_MAGDEF    5
#define SRC_ACTION    6
#define SRC_POWER     7
#define SRC_AGILITY   8
#define SRC_VITALITY  9
#define SRC_SOUL      10
#define SRC_MAGIC     11
#define SRC_SUB6      12
#define SRC_SUB7      13
#define SRC_MAXLP     14
#define SRC_MAXMC     15
#define SRC_DIRECT    48
#define SRC_NONE      49

#define DST_LEVEL     50
#define DST_LP        51
#define DST_MC        52
#define DST_WEAPON    53
#define DST_DEFENSE   54
#define DST_MAGDEF    55
#define DST_ACTION    56
#define DST_POWER     57
#define DST_AGILITY   58
#define DST_VITALITY  59
#define DST_SOUL      60
#define DST_MAGIC     61
#define DST_SUB6      62
#define DST_SUB7      63
#define DST_MAXLP     64
#define DST_MAXMC     65
#define DST_DIRECT    98
#define DST_NONE      99

#define CALCMODE_ADD 0
#define CALCMODE_MULTI 1
#define CALCMODE_DIRECT 2
#define CALCMODE_PROB 3

#define DEFENSEMODE_REAL 0x01
#define DEFENSEMODE_MAGIC 0x02
#define DEFENSEMODE_BREATH 0x04

#define DAMAGE_MAX 99999
#define DAMAGEMODE_ADD 1
#define DAMAGEMODE_SUB 2
#define DAMAGEMODE_STATUS 3
#define DAMAGEMODE_ADDMC 4
#define DAMAGEMODE_SUBMC 5

#define PROBMODE_REAL 0
#define PROBMODE_MAGIC 1
#define PROBMODE_ORDER 2
#define PROBMODE_100 3

//---BattleWindow
#define BW_LEFT    0x0001
#define BW_TOP     0x0002
#define BW_RIGHT   0x0004
#define BW_BOTTOM  0x0008
#define BW_CENTER  0x0010

//---BattleStatus
//---minas
#define BTST_MINAS    0xffff
#define BTST_DOKU     0x0001
#define BTST_NEMURI   0x0002
#define BTST_KURAYAMI 0x0004
#define BTST_CHINMOKU 0x0008
#define BTST_KONRAN   0x0010
#define BTST_JAKUKA   0x0020
#define BTST_MAHI     0x0040
#define BTST_ZERO     0x0080
#define BTST_HYOTEKI  0x0100
#define BTST_SOKUSHI  0x0200
#define BTST_INVAL     0x0400
#define BTST_ITAMIWAKE 0x0800
//#define BTST_DOKU 0x0200
//#define BTST_DOKU 0x0400
//---plus
#define BTST_PLUS    0xffff0000
#define BTST_PROTECT 0x00010000
#define BTST_ACCEL   0x00020000
#define BTST_FSHIELD 0x00040000
#define BTST_POWER   0x00080000
#define BTST_EXTEND  0x00100000
#define BTST_SOUL    0x00200000
#define BTST_KAOS    0x00400000
#define BTST_REFLECT 0x00800000
#define BTST_REGION  0x01000000
#define BTST_DIST    0x02000000
#define BTST_WORLD   0x04000000
#define BTST_COUNTERGATE 0x08000000
#define BTST_PULS        0x70000000

//---特殊能力
#define BTAB_P_DOKU 1
#define BTAB_P_NEMURI 2
#define BTAB_P_KURAYAMI 3
#define BTAB_P_CHINMOKU 4
#define BTAB_P_KONRAN 5
#define BTAB_P_MAHI 6
#define BTAB_P_SOKUSHI 7
#define BTAB_P_HENKA_23 12
#define BTAB_P_HENKA_12 13
#define BTAB_P_HENKA_14 14
#define BTAB_P_HENKA 15

#define BTAB_P_BUTURIKOUGEKI 16
#define BTAB_P_KAIFUKU1 17
#define BTAB_P_KAIFUKU2 18
#define BTAB_P_MC1 19
#define BTAB_P_MC2 20
#define BTAB_P_JIZOKU1 21
#define BTAB_P_JIZOKU2 22
#define BTAB_P_BREATH45 23
#define BTAB_P_BREATH23 24
#define BTAB_P_BREATH12 25
#define BTAB_P_BREATH0 26
#define BTAB_P_SUBETE 31
#define BTAB_S_SAISEI1 32
#define BTAB_S_SAISEI2 33
#define BTAB_S_BARRIER5 34
#define BTAB_S_BARRIER25 35
#define BTAB_S_BARRIER100 36
#define BTAB_S_BARRIER2000 37
#define BTAB_S_COUNTER25 38
#define BTAB_S_COUNTER50 39
#define BTAB_S_COUNTER75 40
#define BTAB_S_COUNTER100 41
#define BTAB_S_ATKDOKU 42
#define BTAB_S_ATKNEMURI 43
#define BTAB_S_ATKMAHI 44
#define BTAB_S_ATKKONRAN 45
#define BTAB_S_AUTOGARD 46
#define BTAB_S_CRITICAL1 47
#define BTAB_S_CRITICAL2 48
#define BTAB_S_CRITICAL3 49
#define BTAB_S_KAIFUKUMAGIC_P 50
#define BTAB_S_KAIFUKUMAGIC_M 51
#define BTAB_S_FIRSTATACK 52
#define BTAB_S_FIRSTESTATACK 53

#define BTAB_M_HENKA 58
#define BTAB_M_MC 59
#define BTAB_M_KAIFUKU 60
#define BTAB_M_JIZOKU 61
#define BTAB_M_SUBETE 62
#define BTAB_M_BOSS 63

#define BTAB_S_BARRIER10 64
#define BTAB_S_BARRIER50 65
#define BTAB_S_BARRIER200 66

#define BTAB_S_HOJOMAHO 67
#define BTAB_S_KAOS 68
#define BTAB_S_NOCOUNTER 69
#define BTAB_S_ANMIN 70
#define BTAB_P_ZERO 71

//---種族
#define CHARATYPE_NINGEN 0
#define CHARATYPE_DOBUTSU 1
#define CHARATYPE_SHOKUBUTSU 2
#define CHARATYPE_SEISHINTAI 3
#define CHARATYPE_JUNSEISHINTAI 4
#define CHARATYPE_BUSSHITSU 5
#define CHARATYPE_KIKAI 6
#define CHARATYPE_MUSHI 7
#define CHARATYPE_SEIREI 8
#define CHARATYPE_KAISANBUTU 9

//---
typedef struct
{
	ei_s32 Enemy;
	ei_s32 x,y;
} CR_BATENEMYINFO,*LPCR_BATENEMYINFO;

#define OFFSETBAT_DISABLEALL 0
#define OFFSETBAT_ENABLEALL 1
#define OFFSETBAT_NORMAL 256
#define OFFSETBAT_SENSEI 257
#define OFFSETBAT_FUIUCHI 258
#define OFFSETBAT_HASAMIUCHI 259

//---バトル情報
typedef struct 
{
	ei_s32 (* lpTurnCallBack)(int ,int ,int ,ei_u32 ,CrCharacter *);//---ターンコールバック
	ei_s32 FailOK;//---負けてもいいか
	ei_s32 Music;//---音楽 (0:そのまま ,-1:ディフォルト)
	ei_s32 Mode;//---バトルモード
	ei_s32 ScreenEfect;//---バトル突入時のエフェクト 0:ディフォルト
	ei_s32 Result;//---バトル結果
	ei_s32 EnebleAvoid;//---逃げることができるか？
	ei_s32 FieldType,MapNumber,SceneNumber,AreaNumber;
	ei_s32 EnableOffsetBattle;//---先制攻撃や不意打ちの不可など
	ei_s32 DontShowAfterBattle;//---戦闘後の画面表示
	ei_s32 OffsetBattle;//---オフセットバトル
	ei_s32 ForceInputCommand;//---強制コマンド入力
	ei_s32 KeepEnemyNumber,LoadKeepEnemy,LoadKeepEnemyCount;//---敵保存
	ei_s32 LimitTurn;//---リミットターン

	CR_BATENEMYINFO Enemy[16];//---敵の配列

	ei_s32 EnableFriendPos;
	CR_BATENEMYINFO Friend[5];//---味方

} CR_BATTLEINFO , *LPCR_BATTLEINFO;

//---コマンド
#define BAT_COMMAND_WEAPON 0
#define BAT_COMMAND_MAGIC 1
#define BAT_COMMAND_DEFENSE 2
#define BAT_COMMAND_ITEM 3
#define BAT_COMMAND_SPECIAL 4
#define BAT_SUBCOM_SPECIALNUMBER 3
#define BAT_COMMAND_ENEMYABILITY 5
#define BAT_COMMAND_WAIT 6
#define BAT_COMMAND_SKIP 7

#define BAT_SUBCOM_DEFENSE 0
#define BAT_SUBCOM_AVOID 1
#define BAT_SUBCOM_MAGICDEFENSE 2
//#define BAT_SUBCOM_COUNTER 3
#define BAT_SUBCOM_MOVE 3

#define CRBAT_SUBTARGET 7

#define COUNTER_GATE 4

//---敵のコマンド
//---直接攻撃系
#define BAT_ECOM_KYUKETSU 1
#define BAT_ECOM_NAGURU 2
#define BAT_ECOM_KAMITUKU 3
#define BAT_ECOM_KIRIKAKARU 4
#define BAT_ECOM_PIERUZAN 5
#define BAT_ECOM_JURIASGIRI 6
#define BAT_ECOM_TOSSHIN 7
#define BAT_ECOM_KAITENATACK 8
#define BAT_ECOM_HAGESHIKU 9
#define BAT_ECOM_NAGITAOSU 10
#define BAT_ECOM_TOTUGEKI 11
#define BAT_ECOM_SHOGEKIHA 12
#define BAT_ECOM_CHOUONPA 13
#define BAT_ECOM_EYEBEAM 14
#define BAT_ECOM_ENGETUZAN 15
#define BAT_ECOM_SEKKINATACK 17
#define BAT_ECOM_IREBACRASH 18
#define BAT_ECOM_HOSHOKU 19
#define BAT_ECOM_SAN 20
#define BAT_ECOM_RARFIAATACK 21
#define BAT_ECOM_DANDYSPRASHER 22
#define BAT_ECOM_TABERU 23
#define BAT_ECOM_ONSOKU 24
#define BAT_ECOM_KYUKETUKEN 25
#define BAT_ECOM_SILENTBANISHA 26
#define BAT_ECOM_SETUDAN 27
#define BAT_ECOM_CR_LINEKOGEKI 28
#define BAT_ECOM_CR_SINGLEKOGEKI 29

//---％ダメージ系
#define BAT_ECOM_TOKASU 50
#define BAT_ECOM_CHISSOKU_1_10 51
#define BAT_ECOM_BUNRETU 52
#define BAT_ECOM_CHISSOKU_1_5 53
#define BAT_ECOM_CHISSOKU_1_2 54
#define BAT_ECOM_CHISSOKU_2_3 55
#define BAT_ECOM_HANBUSSHITU 56
#define BAT_ECOM_SHINSHOKU 57
#define BAT_ECOM_HANBUSSHITU_ZENTAI 58
#define BAT_ECOM_820 59
#define BAT_ECOM_DIVIDING 60

//---特殊ブレス系
#define BAT_ECOM_HOUSHI 70
#define BAT_ECOM_SILENTBREATH 71
#define BAT_ECOM_SLEEPBREATH 72
#define BAT_ECOM_RYUSA 73
#define BAT_ECOM_NEMURINOKONA 74
#define BAT_ECOM_GRAVITY 75
#define BAT_ECOM_DARUDARUHA 76
#define BAT_ECOM_AKUBI 77
#define BAT_ECOM_KAFUN 78
#define BAT_ECOM_MODOKUNOIKI 79
#define BAT_ECOM_SANSEIU 80
#define BAT_ECOM_SABORU 81
#define BAT_ECOM_PINKMIST 82
#define BAT_ECOM_TOSO 83
#define BAT_ECOM_CR_ATUMERU 84
#define BAT_ECOM_CR_TOBASU 85

//---ブレス系
#define BAT_ECOM_HONO 101
#define BAT_ECOM_FUBUKI 102
#define BAT_ECOM_TOPPU 103
#define BAT_ECOM_SUNAARASHI 104
#define BAT_ECOM_IKADUCHI 105
#define BAT_ECOM_POISON 106

#define BAT_ECOM_HONO2 107
#define BAT_ECOM_FUBUKI2 108
#define BAT_ECOM_TOPPU2 109
#define BAT_ECOM_SUNAARASHI2 110
#define BAT_ECOM_IKADUCHI2 111
#define BAT_ECOM_DAIKAEN 112
#define BAT_ECOM_CRFUBUKI 113

//---直接ダメージ系
#define BAT_ECOM_POWERBOMB 115
#define BAT_ECOM_KASCADEBOMB 116
#define BAT_ECOM_MISTYBEAM 117
#define BAT_ECOM_LAYZERBEAM 118
#define BAT_ECOM_MIZUDEPPOU 119
#define BAT_ECOM_KAENHOUSHA 120
#define BAT_ECOM_JIBAKU1 121
#define BAT_ECOM_JIBAKU2 122
#define BAT_ECOM_TAKISIDOBEAM 123
#define BAT_ECOM_CRESTEAJU1 124
#define BAT_ECOM_CRESTEAJU2 125
#define BAT_ECOM_SINRYAKUHEI 126
#define BAT_ECOM_SINRYAKUHEI_BOMB 127
#define BAT_ECOM_ITAMIWAKE_DAMAGE 128
#define BAT_ECOM_DANDYSPARK 129
#define BAT_ECOM_RIBONTUISTA 130
#define BAT_ECOM_JIBAKU3 131
#define BAT_ECOM_JIBAKU4 132
#define BAT_ECOM_RESERVE 133
#define BAT_ECOM_ROUOU 134

//---状態変化系
#define BAT_ECOM_GURUGURUMEDAMA 230
#define BAT_ECOM_JENTLEFLASH 231
#define BAT_ECOM_KONRANKOUSEN 232
#define BAT_ECOM_ITAMIWAKE 233
#define BAT_ECOM_ITAMIWAKE_JIZOKU 234
#define BAT_ECOM_ITAMIWAKE_KAIJO 235
#define BAT_ECOM_MCBUNKAI 236
#define BAT_ECOM_GURUGURUHYPER 237
#define BAT_ECOM_SOKUSHIKOUSEN 238
#define BAT_ECOM_JAKUKAKOSEN 239
#define BAT_ECOM_DAIKONRAN 240

//---能力上昇系
#define BAT_ECOM_KOUGOUSEI 500
#define BAT_ECOM_SAISEI 501
#define BAT_ECOM_LPCHANGE 502
#define BAT_ECOM_SHURI 503
#define BAT_ECOM_KINOUTUIKA 504
#define BAT_ECOM_BARRIERTENKAI 505
#define BAT_ECOM_KASCADE_JUNBI 506
#define BAT_ECOM_KASCADE_KYOKA 507
#define BAT_ECOM_HANBUSSITU_JUNBI 508
#define BAT_ECOM_KASCADE_SAIDAI 509
#define BAT_ECOM_NERU 510
#define BAT_ECOM_NORIUTURU 511
#define BAT_ECOM_KIDOU 512
#define BAT_ECOM_BOSOKAISHI 513
#define BAT_ECOM_NORIUTURU2 514
#define BAT_ECOM_CR_HENSHIN 515
#define BAT_ECOM_CR_RUINJUNBI 516
#define BAT_ECOM_IKIWOSUIKOMU 517
#define BAT_ECOM_KIDOSASERU 518

#define BAT_ECOM_SEICHOU 600
#define BAT_ECOM_KARA 601

#define BAT_ECOM_TAMERU 999

//---ターゲット、レンジ
#define BAT_TARGET_FRIENDSINGLE 0x0001
#define BAT_TARGET_ENEMYSINGLE  0x0002
#define BAT_TARGET_SINGLE       0x0004
#define BAT_TARGET_SINGLETARGET 0x000f

#define BAT_TARGET_FRIENDALL    0x0010
#define BAT_TARGET_ENEMYALL     0x0020
#define BAT_TARGET_ALL          0x0040
#define BAT_TARGET_ALLTARGET    0x00f0

#define BAT_TARGET_FRIENDRANGE  0x0100
#define BAT_TARGET_ENEMYRANGE   0x0200
#define BAT_TARGET_RANGE        0x0400
#define BAT_TARGET_RANGETARGET  0x0f00

#define BAT_TARGET_ME 0x1000

#define BAT_TARGET_FRIEND (BAT_TARGET_FRIENDSINGLE | BAT_TARGET_FRIENDALL | BAT_TARGET_FRIENDRANGE)
#define BAT_TARGET_ENEMY (BAT_TARGET_ENEMYSINGLE | BAT_TARGET_ENEMYALL | BAT_TARGET_ENEMYRANGE)

//---Range
#define BAT_RANGE_CIRCLE1 (0 << 16)
#define BAT_RANGE_CIRCLE2 (1 << 16)
#define BAT_RANGE_CIRCLE3 (2 << 16)
#define BAT_RANGE_CIRCLE4 (3 << 16)
#define BAT_RANGE_CIRCLE5 (4 << 16)
#define BAT_RANGE_CIRCLE6 (5 << 16)
#define BAT_RANGE_CIRCLE7 (6 << 16)
#define BAT_RANGE_LINE1 (9 << 16)
#define BAT_RANGE_LINE2 (10 << 16)
#define BAT_RANGE_LINE3 (11 << 16)
#define BAT_RANGE_LINE4 (12 << 16)
#define BAT_RANGE_LINE5 (13 << 16)
#define BAT_RANGE_LINE6 (14 << 16)
#define BAT_RANGE_LINE7 (15 << 16)
#define BAT_RANGE_CIRCLESTART 0
#define BAT_RANGE_LINESTART 9

//---Damage
#define BAT_DAMAGE_MISS -1

#define BAT_DAMAGENULL 31

//---カメラウェイト
#define WAIT_AFTERMOVECAMERA 500

//---アニメ
#define BAT_ANIME_ATACK 1
#define BAT_ANIME_GUN 2
#define BAT_ANIME_MAGIC 3
#define BAT_ANIME_ITEM 4

#define ANIMEPATTERN_1 16

#define DRAWTYPE_4_ANIME 0
#define DRAWTYPE_4 1
#define DRAWTYPE_2 2
#define DRAWTYPE_1 3

//---コマンド
typedef struct
{
	ei_s32 Main;//---命令
	ei_s32 Range,SubRange;//---対象
	ei_s32 Sub[8];//---サブアイテム
	ei_u32 Target,SubTarget;

	ei_s32 Hit,NoTurnTarget;
} CR_BATTLECOMMAND,*LPCR_BATTLECOMMAND;

//---------------------------------------------
#define BATLLECHARA_FLAG_MAX 16
#define BATLLECHARA_FLAG_ITAMIWAKE 15
#define BATLLECHARA_FLAG_ITAMIWAKE_TAISHO 14
#define BATLLECHARA_FLAG_ITAMIWAKE_YARARE 13

typedef struct
{
	ei_s32 x,y,z;
	float Angle;
	ei_s32 Pattern,DrawType,AnimeMode,Show;
	eiCell *pCell,*pDrawCell;
	//---Anime
	float ax,ay,az,dx,dy,dz,MoveSpeed,MoveAngle;
	float DeltaTime,LimitTime;
	float ZOffset;
	ei_s32 AnimeFlag;
	ei_s32 AnimeCount;
	ei_s32 OldPattern,AnimePos,*pAnime;

	//---status
	ei_s32 RuinDamage;
	ei_s32 DefenseCount,SpecialDisable,FirstAtack,FirstestAtack;
	ei_s32 KAOSTurn,WorldTurn,PersonalTurn,WorldCountTurn,AutoGard;
	ei_s32 Flags[BATLLECHARA_FLAG_MAX];
} CR_BATTLEONLYINFO ,*LPCR_BATTLEONLYINFO;

typedef struct
{
	eiCell *pCell;
	ei_s32 DrawMode,Pattern,AnimeMode,AnimeMax,AnimeWait,AlphaMode;
	float x,y,z,dx,dy,dz,vx,vy,vz,MoveSpeed;
	float DeltaTime,LimitTime;
	ei_s32 Show;

	float RSize,XRate,YRate;
	D3DTLVERTEX tlVertex[4];
	eiTextureCell *pTex;
} BATTLEOBJECTINFO, *LPBATTLEOBJECTINFO;

//---フィールド頂点
typedef struct
{
	D3DVERTEX Vertex[4];
//	D3DLVERTEX Vertex[4];
	int TextureNumber;
} CR_BATFIELDVERTEX , *LPCR_BATFIELDVERTEX;

//---視界座標構造体
typedef struct
{
	eiD3DMatrix matCamera;
	float cx,cy,cz;
	float dx,dy,dz;
	float org_cx,org_cy,org_cz;
	float org_dx,org_dy,org_dz;
	float Angle;
} CR_BATTLEVIEW , *LPCR_BATTLEVIEW;

typedef struct st_cr_battle_drawchara
{
	ei_s32 Flag,Type,ViewNumber,CannotDraw;//---ビューナンバー
	ei_s32 PatternMode;//---パターンモード（角度でパターンを切り換えるか）
	ei_s32 MustBeFront;//---常に一番上に描画されるか
	ei_s32 DrawMode;//---２Ｄか、ポリゴンか
	float Limit;//---視点リミット
	float cx,cy,cz,src_x,src_y,src_z;//---座標、下の座標
	float XRate,YRate;//---拡大率
	eiCell *pCell;//---描くべきセル
	BATTLEOBJECTINFO *pObjectInfo;//---ObjectInfoへのポインタ

	st_cr_battle_drawchara *pAfterDraw;
	void *pData;
} CR_BATTLE_DRAWCHARA , *LPCR_BATTLE_DRAWCHARA;
