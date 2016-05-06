//---
//---CRESTEEJU 定義ファイル
//---

#ifndef INCLUDE_CRDEF

#define INCLUDE_CRDEF

//---Debug
#define CR_DEBUG 0
#define CR_DATAMODE 0
#define CR_LANUGAGE 0

#define NORMALIZE_CALC

#if (CR_DATAMODE == 1)
	#define CR_DATAFILE1 NULL
	#define CR_DATAFILE2 NULL
	#define CR_DATAFILE3 NULL
	#define CR_DATAFILE4 NULL
	#define CR_DATAFILE5 NULL
	#define CR_DATAFILE6 NULL
	#define CR_MUSICFILE NULL
	#define CR_MESSAGEFILE1 NULL
	#define CR_MESSAGEFILE2 NULL
	#define CR_MESSAGEFILE3 NULL

	#define CR_DATADIR1 "Data1\\"
	#define CR_DATADIR2 "Data2\\"
	#define CR_DATADIR3 "Data3\\"
	#define CR_DATADIR4 "Data4\\"
	#define CR_DATADIR5 "Data5\\"
	#define CR_DATADIR6 "Data6\\"
	#define CR_MUSICDIR "Music\\"
	#define CR_MESSAGEDIR1 "Message\\"
	#define CR_MESSAGEDIR2 "Message\\"
	#define CR_MESSAGEDIR3 "Message\\"
#else
	#define CR_DATAFILE1 "crdata01.dat"
	#define CR_DATAFILE2 "crdata02.dat"
	#define CR_DATAFILE3 "crdata03.dat"
	#define CR_DATAFILE4 "crdata04.dat"
	#define CR_DATAFILE5 "crdata05.dat"
	#define CR_DATAFILE6 "crdata06.dat"
	#define CR_MUSICFILE "crmusic.dat"
	#define CR_MESSAGEFILE1 "crmsg01.dat"
	#define CR_MESSAGEFILE2 "crmsg02.dat"
	#define CR_MESSAGEFILE3 "crmsg03.dat"

	#define CR_DATADIR1 ""
	#define CR_DATADIR2 ""
	#define CR_DATADIR3 ""
	#define CR_DATADIR4 ""
	#define CR_DATADIR5 ""
	#define CR_DATADIR6 ""
	#define CR_MUSICDIR ""
	#define CR_MESSAGEDIR1 ""
	#define CR_MESSAGEDIR2 ""
	#define CR_MESSAGEDIR3 ""
#endif /* (CR_CR_DATAMODE == 1) */

//---ビットストリームを使う
#define CRUSE_BITSTREAM

//---Color
#define CRCOLOR_BLACK 16
#define CRCOLOR_TRANSBLACK 17
#define CRCOLOR_GREEN 18
#define CRCOLOR_BLUE 19
#define CRCOLOR_YELLOW 20
#define CRCOLOR_PURPLE 21
#define CRCOLOR_AQUA 22
#define CRCOLOR_WHITE 23
#define CRCOLOR_RED 24
#define CRCOLOR_GRAY 25

//----------------------
//---Music
#define STREAM_MAX 4

#define CRMUSIC_INIT 0

//---disk1
#define CRMUSIC_TITLE 1
#define CRMUSIC_DRAGONBREATH 2
#define CRMUSIC_OPENING 3
#define CRMUSIC_FIELD1 4
#define CRMUSIC_BATTLE 5
#define CRMUSIC_FANFARE 6
#define CRMUSIC_TOWN1 7
#define CRMUSIC_SAKABA 8
#define CRMUSIC_DANGEON1 9
//---
#define CRMUSIC_SS 10
#define CRMUSIC_LIZEL 11
#define CRMUSIC_BOSSBATTLE1 12
#define CRMUSIC_LOSE 13
#define CRMUSIC_VILLAGE1 14
#define CRMUSIC_DANGEON2 15
#define CRMUSIC_TOWNETERNAL 16
#define CRMUSIC_ETERNAL 17
#define CRMUSIC_HEAT 18
#define CRMUSIC_SEEK 19
#define CRMUSIC_DANGEON3 20
#define CRMUSIC_CRAYSIVE 21

//---disk2
#define CRMUSIC_OILLAKE 22
#define CRMUSIC_TOWN2 23
#define CRMUSIC_ZENUREN 24
#define CRMUSIC_LIZELPASSED 25
#define CRMUSIC_NATSU 26
#define CRMUSIC_VILLAGE2 27
#define CRMUSIC_ENDLESSP 28
#define CRMUSIC_GS 29
#define CRMUSIC_BREAKFORTUNE 30
#define CRMUSIC_SINCETHEDAY 31
#define CRMUSIC_BARRIER 32
#define CRMUSIC_NIGHT 33
#define CRMUSIC_SAMIT 34
#define CRMUSIC_FATEDFORCE 35
#define CRMUSIC_METEOR 36
#define CRMUSIC_HOPE 37
#define CRMUSIC_BEAWAKEN 38
#define CRMUSIC_STREAM 39
#define CRMUSIC_PEACE 40
#define CRMUSIC_NEVEREND 41
#define CRMUSIC_SILENT 42

#define CRMUSIC_FIELD2 0
#define CRMUSIC_ETERNALBATTLE CRMUSIC_DRAGONBREATH

//---再生フラッグ
#define CRMUSIC_LOADFORCE 0x01

//----------------------
//---Sound
#define CRSOUND_SOUNDMAX 96

#define CRSOUND_BTN_A 0
#define CRSOUND_BTN_B 1
#define CRSOUND_COUNT_1 2
#define CRSOUND_COUNT_2 3
#define CRSOUND_BEEP_1 4
#define CRSOUND_BEEP_2 5
#define CRSOUND_BUY 6 //---購入
#define CRSOUND_LOGO 7
#define CRSOUND_LEARNMAGIC 9 //---魔法修得
#define CRSOUND_RICOVERY 10
//---event 11-30
#define CRSOUND_GS_SOUND 11
#define CRSOUND_GASAGASA 12
#define CRSOUND_HYURURIRA 13
#define CRSOUND_BOOKPAGE 14
#define CRSOUND_WAVE1 15
#define CRSOUND_ANAAKU 16
#define CRSOUND_SUZU 17
#define CRSOUND_KIDOU 18
#define CRSOUND_MASINBTN 19
#define CRSOUND_GS_FUMISUGI1 20
#define CRSOUND_GS_FUMISUGI2 21
#define CRSOUND_GS_ENSTO 22
#define CRSOUND_MUSEN 23
#define CRSOUND_KIOKUNOISEKI_BARRIER 24
#define CRSOUND_GS_TUIRAKUMAE 25
#define CRSOUND_GS_TUIRAKU 26
#define CRSOUND_WATER 27
#define CRSOUND_KANSEI 28
#define CRSOUND_WARERU 29

#define CRSOUND_DOOR 34

//---小剣／ナイフ
#define CRSOUND_ATACK1 31
//---剣
#define CRSOUND_ATACK2 32
//---大剣
#define CRSOUND_ATACK3 33
//---殴る
#define CRSOUND_ATACK4 34
//---銃１
#define CRSOUND_ATACK5 35
//---銃２
#define CRSOUND_ATACK6 36
//---爪っぽいの
#define CRSOUND_ATACK7 37
//---ダメージ０
#define CRSOUND_DAMAGE0 38
#define CRSOUND_ENEMYDEAD 39

//---magic sound 40-70
//---40 - 43ファイアーボールの音
#define CRSOUND_FIRE1 40
#define CRSOUND_FIRE2 41
#define CRSOUND_FIRE3 42
//---43 魔法を唱える音
#define CRSOUND_MAGIC 43
#define CRSOUND_THUNDER1 44
#define CRSOUND_THUNDER2 45
#define CRSOUND_WIND1 46
#define CRSOUND_THUNDER3 47
#define CRSOUND_EAERTH1 48
#define CRSOUND_EAERTH2 49
#define CRSOUND_ICE1 50
#define CRSOUND_ICE2 51
#define CRSOUND_FIRE4 52
#define CRSOUND_FIRE5 53
#define CRSOUND_EARTHQUAKE 54
#define CRSOUND_UP 55
#define CRSOUND_DOWN 56
#define CRSOUND_DIFFUSION1 57
#define CRSOUND_DIFFUSION2 58
#define CRSOUND_DIFFUSION3 59
#define CRSOUND_DIFFUSION4 60
#define CRSOUND_EXT1 61
#define CRSOUND_EXT2 62
#define CRSOUND_EXT3 63
#define CRSOUND_RUIN1 64
#define CRSOUND_RUIN2 65

//---70-96
#define CRSOUND_GURUGURUMEDAMA 70
#define CRSOUND_BEAM 71
#define CRSOUND_AKUBI 72
#define CRSOUND_ITAMIWAKE 73

//---efect
#define CRINTOBAT_NORMAL 1
#define CRINTOBAT_BOSS1 1
#define CRINTOBAT_NONE 0


//----------------------
//---Pattern

#define CR_PTN_FIELD 1000
#define CR_PTN_SYSTEM 0
#define CR_PTN_SYSTEM_WINDOW (CR_PTN_SYSTEM + 0)
#define CR_PTN_SYSTEM_MENUCURSOR (CR_PTN_SYSTEM + 16)
//#define CR_PTN_SYSTEM_MENUICON (CR_PTN_SYSTEM + 50)
#define CR_PTN_SYSTEM_ITEMICON (CR_PTN_SYSTEM + 50)
#define CR_PTN_SYSTEM_MAGICICON (CR_PTN_SYSTEM + 70)
#define CR_PTN_SYSTEM_MESSAGEICON (CR_PTN_SYSTEM + 80)
#define CR_PTN_SYSTEM_STATUSBAR (CR_PTN_SYSTEM + 100)
#define CR_PTN_SYSTEM_BALANCEBAR (CR_PTN_SYSTEM + 105)
#define CR_PTN_SYSTEM_CHARAFACE (CR_PTN_SYSTEM + 110)
#define CR_PTN_SYSTEM_BATTLECURSOR (CR_PTN_SYSTEM + 120)
#define CR_PTN_SYSTEM_BATTLEFONT (CR_PTN_SYSTEM + 130)

#define CR_PTN_SYSTEM_MAINCHARACTER (200)
#define CR_PTN_SYSTEM_WALLPAPER (210)

//---Pattern Surface
#define CR_PTNSURFACE_SYSTEM_X 0
#define CR_PTNSURFACE_SYSTEM_Y 416
//---y = 0
//---共有
#define CR_PTNSURFACE_MAINCHARACTER_X (CR_PTNSURFACE_SYSTEM_X + (32 * 8))
#define CR_PTNSURFACE_MAINCHARACTER_Y (CR_PTNSURFACE_SYSTEM_Y + 0)
#define CR_PTNSURFACE_BATTLEFONT_X (CR_PTNSURFACE_SYSTEM_X + (32 * 8))
#define CR_PTNSURFACE_BATTLEFONT_Y (CR_PTNSURFACE_SYSTEM_Y + 0)

#define CR_PTNSURFACE_BATTLECURSOR_X (CR_PTNSURFACE_SYSTEM_X + (32 * 16))
#define CR_PTNSURFACE_BATTLECURSOR_Y (CR_PTNSURFACE_SYSTEM_Y + 0)
//---y = 32
#define CR_PTNSURFACE_MENUICON_X (CR_PTNSURFACE_SYSTEM_X + 0)
#define CR_PTNSURFACE_MENUICON_Y (CR_PTNSURFACE_SYSTEM_Y + 32)
#define CR_PTNSURFACE_ITEMICON_X (CR_PTNSURFACE_SYSTEM_X + 0)
#define CR_PTNSURFACE_ITEMICON_Y (CR_PTNSURFACE_SYSTEM_Y + 32)
#define CR_PTNSURFACE_MESSAGEICON_X (CR_PTNSURFACE_SYSTEM_X + 256)
#define CR_PTNSURFACE_MESSAGEICON_Y (CR_PTNSURFACE_SYSTEM_Y + 32)
#define CR_PTNSURFACE_WINDOW_X (CR_PTNSURFACE_SYSTEM_X + 256 + 256)
#define CR_PTNSURFACE_WINDOW_Y (CR_PTNSURFACE_SYSTEM_Y + 32)
//---y = 64
#define CR_PTNSURFACE_MENUCURSOR_X (CR_PTNSURFACE_SYSTEM_X + 0/*+ 16 * 16*/)
#define CR_PTNSURFACE_MENUCURSOR_Y (CR_PTNSURFACE_SYSTEM_Y + 48)
#define CR_PTNSURFACE_MAGICICON_X (CR_PTNSURFACE_SYSTEM_X + 320)
#define CR_PTNSURFACE_MAGICICON_Y (CR_PTNSURFACE_SYSTEM_Y + 48)
//---other
#define CR_PTNSURFACE_STATUSBAR_X (CR_PTNSURFACE_SYSTEM_X + (640 - 64))
#define CR_PTNSURFACE_STATUSBAR_Y (CR_PTNSURFACE_SYSTEM_Y + 32)
#define CR_PTNSURFACE_BALANCEBAR_X (CR_PTNSURFACE_SYSTEM_X + (640 - 64))
#define CR_PTNSURFACE_BALANCEBAR_Y (CR_PTNSURFACE_SYSTEM_Y + 48)
//---page3
#define CR_PTNSURFACE_WALLPAPER_X (0)
#define CR_PTNSURFACE_WALLPAPER_Y (0)

//---space
#define VSPACE_MATERIAL 20
#define VSPACE_STATUS 32

//---player & party
#define LEVEL_MAX 99
#define PLAYER_MAX 16
#define MEMBER_MAX 5
#define PLAYERNAME_MAX 16

#define EQ_WEAPON_MAX 2 //---装備武器の数
#define EQ_PROTECTOR_MAX 3 //---装備防具の数
#define EQ_ACCESSORY_MAX 2
#define EQ_ALL_MAX (EQ_WEAPON_MAX + EQ_PROTECTOR_MAX + EQ_ACCESSORY_MAX)

//---item
#define ITEM_MAX 300 //---アイテムの数
#define ITEMMATERIAL_MAX ITEM_MAX
#define OLD1_ITEM_MAX 270
#define ITEMCOUNT_MAX 99 //---アイテムの個数上限
//---magic
#define MAGIC_MAX 100 //---一人の魔法上限
#define MAGICMATERIAL_MAX 100 //---魔法の数
//---skil
#define SKIL_MAX 8
#define SKILMATERIAL_MAX 100 //---特殊技の数
//---special
#define SPECIALMATERIAL_MAX 64 //---特殊技の数

//---money
#define MONEY_MAX 9999999
#define MONEY_NAME "ファン"

//---element
#define ELEMENT_MAX 16
#define ELEMENT_NOMAGIC 0
#define ELEMENT_NOELEMENT 1
#define ELEMENT_RECOVERY 2
#define ELEMENT_HELP 3
#define ELEMENT_FIRE 4
#define ELEMENT_AQUA 5
#define ELEMENT_EARTH 6
#define ELEMENT_WIND 7
#define ELEMENT_THUNDER 8
#define ELEMENT_SOUL 9
#define ELEMENT_CHANGE 10
#define ELEMENT_PHYSICS 11
#define ELEMENT_BREATH 12
#define ELEMENT_OTHER 13

#define DEFINE_ELEMENTSTRING() eistr *ElementString[] = \
{\
	"　","－","回","補",\
	"火","水","土","風",\
	"雷","精","変","他",\
		"end"\
}\

//---magic kind
#define MAGICKIND_DAMAGE 0
#define MAGICKIND_SUB 1

//---direction
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

//---status
//#define

//---Enemy
#define ENEMY_MAX 300

//---WallPaper & Music
#define WALLPAPER_MAX 32
#define MUSIC_MAX 64

//---Graphic Extention
#define CR_EXTENTION_LOWEST 1
#define CR_EXTENTION_LOW 2
#define CR_EXTENTION_NORMAL 3
#define CR_EXTENTION_HIGH 4
#define CR_EXTENTION_HIGHEST 5

//---main loop
#define MAINLOOP_NOMESSAGE 0
#define MAINLOOP_CANCELMENU 10
#define MAINLOOP_RELOADMENU 20

#define MAINLOOP_ENDLOOP 1000
#define MAINLOOP_MENUEND 1001
#define MAINLOOP_BATTLEFAIL 1002
#define MAINLOOP_ESCAPE 1003

//---動作モード
#define CODE_OTHER 0
#define CODE_STARTUP 1
#define CODE_INITIALIZE 2
#define CODE_TITLE 5
#define CODE_OPENING 6
#define CODE_FIELD 10
#define CODE_BATTLE 11
#define CODE_DEMO1 30
#define CODE_DEMO2 31
#define CODE_DEMO3 32
#define CODE_DEMO4 33
#define CODE_DEMO5 34
#define CODE_END 255

//---Macro
#define PI 3.1415f

//---PlayHistory
#define PLAYHISTORY_MAX 32
#define YARIKOMI_MAX 64

//---セレクトウィンドウの情報
typedef struct
{
	int Offset;//---メニュー上のオフセット
	int Index;//---ページを含めたインデックス
	int Page;//---ページ
} CRWIN_SELECTINFO,*LPCRWIN_SELECTINFO;

//-----------------------------------------
//---Save File header
typedef struct
{
	eistr Type[2];
	ei_u32 FileVersion;
	eistr HeadString[128];
} CRESTEAJU_HEADER, *LPCRESTEAJU_HEADER;

//---実行ファイル起動情報
typedef struct
{
	ei_s32 ExeRunningTime;
} CRESTEAJU_EXEINFO ,*LPCRESTEAJU_EXEINFO;

//---INIファイル情報
typedef struct
{
	int FullScreen,GDIOnly;
	int ForceFPS,ForceRefreshRate,ForceRefreshRate_Over80,AutoChangeFPS,BaseCount,
		MarginOfErrorFPS,FlipMode,HalfScreen,BPP,ShowFPS,
		WindowRFMode,DrawPrimitiveWait;
	int RuningRefreshRate;
	int FieldSizeX,FieldSizeY;
	int UseDirectDrawHardware,UseDirectSound,UseDirect3DHardware;
	int TextureFilterLiner,UseZBuffer,UseHardwareTransform;
	int UseMIDI,OffsetPlay,MIDIType;
	int UseSound,Volume;
	int UseJoystick;
	int ExtentionLevel;

	int Battle3DUseTexture,Battle3DUseFilling,
		AlphaBattleField,FogBattleField,BattleViewAngle,BattleShadow;
	int EnableAddAlpha;

	eistr SaveDir[_MAX_PATH];
	int AutoSave;
} CR_INIFILE,*LPCR_INIFILE;

//---初期化情報
typedef struct
{
	int Init,ScreenMode,DebugMode,RefreshRate;
	CR_INIFILE IniFile;
} CRESTEAJU_INITIALIZE,*LPCRESTEAJU_INITIALIZE;

//---システム情報
typedef struct
{
	//---フィールド描画
	ei_s32 DrawRate,/*DisplayRefreshRate,*/DrawCenterCharacter,AutoDrawFrame;
	//---ウェイト
	ei_s32 MenuWaitTime;
	//---キーボード
	ei_s32 KeyWaitDelay,KeyWaitAfterPush;
	//---ウィンドウカラー
	ei_s32 WindowColor[8][4];
	//---セーブデータファイルナンバー
	ei_s32 SaveNumber;
	//---メニュー
	ei_s32 MenuReset;

	ei_s32 Dumy1[8];

	//---バトル設定
	ei_s32 BattleMoveCamera,//---バトル時のカメラの移動
		BattleCameraAngle,//---標準カメラアングルの設定
		BattleMoveCamera_AsInputCommand,//--コマンド入力時のカメラ移動
		BattleMoveCameraTime_AsInputCommand,//---コマンド入力時のカメラ移動時間
		BattleCommandReset;//---バトルコマンドのリセット設定

	ei_s32 Dumy2[8];
} CRESTEAJU_SYSTEM,*LPCRESTEAJU_SYSTEM;

typedef struct
{
	ei_s16 Major,Minor,LastString,Language;
} CRESTEAJU_VERSION,*LPCRESTEAJU_VERSION;

//---ゲーム使用データ
typedef struct
{
	ei_s32 *LevelUpExperience,*LevelUpMagicExp,
		*LevelUpLP,*LevelUpMC,*LevelUpStatus;

	ei_s32 *CharacterRateExperienceStart,
		*CharacterRateExperienceEnd,
		*CharacterRateLP,*CharacterRateMC,
		*CharacterRatePower,*CharacterRateVitality,
		*CharacterRateAgility,*CharacterRateSoul,
		*CharacterRateMagic,*CharacterRateMagicExp,
		*Character100perMagicLevel;

	CRESTEAJU_VERSION Version;
} CRESTEAJU_GAMEDATA,*LPCRESTEAJU_GAMEDATA;

//---プレイヒストリー
typedef struct
{
	ei_s32 Level;
	ei_s32 Hour,Minute,Second;
} CRESTEAJU_PLAYHISTORY;

#define EV_GS_NUMBERX 1000
#define EV_GS_NUMBERY 1001
#define EV_GS_NUMBER_STATUS 1002
#define EV_MENU_MODE 1003
#define EV_GS_SCENE_STATUS 1004
#define EV_GS_SCENE_KEEPX 1005
#define EV_GS_SCENE_KEEPY 1006
#define NP_GS_NUMBER 11
#define NP_GS_EVNUMBER 12
#define NP_GS_CANTNUMBER 13

//---ゲーム情報
typedef struct
{
	ei_s32 Size;

	//---グローバルステータス
	ei_s32 PlayHours,PlayMinutes,PlaySeconds,PlayAllSecond;//---プレイ時間
	ei_s32 MusicNumber;//---現在のＢＧＭ
	ei_s32 TelX,TelY,TelPlane,TelSceneNumber,TelMapNumber;//---テレポート
	ei_s32 MapNumber,MapScene,FieldX,FieldY,FieldPlane;//---現在位置
	ei_s32 MainCharacterNumber;//---主人公キャラナンバー

	//---ゲーム設定
	ei_s32 TransWindow;//---透過ウィンドウ使用か
	ei_s32 ViewSizeX,ViewSizeY;//---フィールド表示サイズ

	//---イベント
	ei_s32 Event[1024];
	//---アイテム
	ei_s32 Item[ITEM_MAX],ItemCount[ITEM_MAX];
	//---所持金、歩数
	ei_s32 Money,WalkCount;

	//---アイテムウィンドウ情報
	CRWIN_SELECTINFO SelectInfoItem,BattleSelectItem;

//---コレクション
	//---壁紙
	ei_s32 WallPaper[WALLPAPER_MAX];
	ei_s32 UseWallPaper;
	//---音楽
	ei_s32 Music[MUSIC_MAX];

//---データ
	CRESTEAJU_PLAYHISTORY PlayHistory[PLAYHISTORY_MAX];//---プレイヒストリー
	ei_s32 EscapeCount;//---逃げた回数
	ei_s32 BattleCount;//---戦った回数
	ei_s32 AllGetMoney;//---戦闘勝利で得たお金
	ei_s32 AllGetExperience;//---戦闘で得た経験値
	ei_s32 MinClearHour,MinClearMinute,MinClearSecond;//---最短クリア時間
	ei_s32 SaveCount;//---セーブ回数
	ei_s32 Yarikomi[YARIKOMI_MAX];//---やりこみ記録

} CRESTEAJU_GAMEINFO,*LPCRESTEAJU_GAMEINFO;

//---オールドゲーム情報-----------------------------
typedef struct
{
	ei_s32 Size;

	//---グローバルステータス
	ei_s32 PlayHours,PlayMinutes,PlaySeconds,PlayAllSecond;//---プレイ時間
	ei_s32 MusicNumber;//---現在のＢＧＭ
	ei_s32 TelX,TelY,TelPlane,TelSceneNumber,TelMapNumber;//---テレポート
	ei_s32 MapNumber,MapScene,FieldX,FieldY,FieldPlane;//---現在位置
	ei_s32 MainCharacterNumber;//---主人公キャラナンバー

	//---ゲーム設定
	ei_s32 TransWindow;//---透過ウィンドウ使用か
	ei_s32 ViewSizeX,ViewSizeY;//---フィールド表示サイズ

	//---イベント
	ei_s32 Event[1024];
	//---アイテム
	ei_s32 Item[OLD1_ITEM_MAX],ItemCount[OLD1_ITEM_MAX];
	//---所持金、歩数
	ei_s32 Money,WalkCount;

	//---アイテムウィンドウ情報
	CRWIN_SELECTINFO SelectInfoItem,BattleSelectItem;

//---コレクション
	//---壁紙
	ei_s32 WallPaper[WALLPAPER_MAX];
	ei_s32 UseWallPaper;
	//---音楽
	ei_s32 Music[MUSIC_MAX];

//---データ
	CRESTEAJU_PLAYHISTORY PlayHistory[PLAYHISTORY_MAX];//---プレイヒストリー
	ei_s32 EscapeCount;//---逃げた回数
	ei_s32 BattleCount;//---戦った回数
	ei_s32 AllGetMoney;//---戦闘勝利で得たお金
	ei_s32 AllGetExperience;//---戦闘で得た経験値
	ei_s32 MinClearHour,MinClearMinute,MinClearSecond;//---最短クリア時間
	ei_s32 SaveCount;//---セーブ回数
	ei_s32 Yarikomi[YARIKOMI_MAX];//---やりこみ記録

} OLD1_CRESTEAJU_GAMEINFO,*LPOLD1_CRESTEAJU_GAMEINFO;
//---オールドゲーム情報-------------------------------------


//---パーティー情報
typedef struct
{
	ei_s32 Size;

	ei_s32 PartyMember[MEMBER_MAX],BattleMember[MEMBER_MAX];
} CRESTEAJU_PARTYINFO,*LPCRESTEAJU_PARTYINFO;

//------Chatacter Information

#define BTHISTORY_ACTION 0
#define BTHISTORY_WEAPON 1
#define BTHISTORY_MAGIC 2
#define BTHISTORY_ITEM 3
#define BTHISTORY_DEFENSE 4
#define BTHISTORY_SPECIAL 5

//---バトルヒストリー
typedef struct
{
	//---使用ＭＣ
	ei_s32 UseMC;

	//---行動別カウント
	ei_s32 ActionCount,WeaponCount,MagicCount,ItemCount,
		DefenseCount,SpecialCount,
		RealAvoid,MagicAvoid;
	//---ステータスカウント
	ei_s32 DeathCount;//---気絶回数
	ei_s32 GiveMissCount,ReceiveMissCount;

	//---出会った敵の数、倒した敵の数、与えたダメージ、与えられたダメージ
	ei_s32 EnemyCount,FinishEnemyCount,GiveDamage,ReceiveDamage;
} CRESTEAJU_CHARACTER_BATTLEINFO,*LPCRESTEAJU_CHARACTER_BATTLEINFO;

//--基本変数
//---キャラクター
typedef struct
{
	ei_s32 Size;

	eistr Name[32];

	ei_s32 Who;//---誰か
	//---Public Status
	ei_s32 level,experience,magic_experience;
	ei_s32 lp,sp,mc,balance,max_lp,max_sp,max_mc;
	ei_s32 power,agility,vitality,soul,magic,magic_defense;
	//---force status　装備品に関係なく強制的にこのステータスにする
	ei_s32 force_HitProb,force_AvoidProb,force_MagicAvoidProb;
	//---Hidden Status
	ei_s32 sub_hit_prob;//---命中補正率
	ei_s32 since_lastusingmagic,usingmagic_subcount;//---最後に魔法を使ってからどのくらい経ったか

	//---バトルフィールド
	ei_s32 BattleX,BattleY;
	ei_s32 Protect;//---保護されてるか？（装備変更不可など・・・）

	//---装備
	ei_s32 eq_weapon[EQ_WEAPON_MAX],eq_protector[EQ_PROTECTOR_MAX],
		eq_accessory[EQ_ACCESSORY_MAX];

	ei_s32 m_weapon,m_status,pinch;

	//---魔法
	ei_s32 MagicTable[MAGIC_MAX];
//	//---特殊技
//	ei_s32 SkilTable[SKIL_MAX];

	//---カーソル保存
	CRWIN_SELECTINFO MagicBattleCursor,MagicFieldCursor,
		SpecialBattleCursor,BattleMenuCursor,
		BattleAtackSubItem,BattleDefenseSubItem;
	ei_s32 BattleMenuItem[8]; //---バトルメニュー

	CRESTEAJU_CHARACTER_BATTLEINFO BattleHistory,SpecialHistory;

	//---フィールドでのＭＣ回復
	ei_s32 DeltaMC,DisableMCCount;

	ei_s32 reserved[32];
} CRESTEAJU_CHARACTERINFO,*LPCRESTEAJU_CHARACTERINFO;


//---敵情報
typedef struct
{
	ei_s32 Size;

	ei_s32 ExistenceExtend;
	ei_s32 IQ,AtackType,Graphic,GraphicType,MoveType,ActionType,
		NormalSound,AtackAnime;

	ei_s32 ItemProbability,Item;
	ei_s32 Money,Experience;
	ei_s32 ZOffset;
} CRESTEAJU_ENEMYINFO;

#define BATTLESTATUS_MAX 32

#define AB_XXX1 0
#define AB_XXX2 1
#define AB_XXX3 2
//--- ...つづく

//---バトルキャラクター情報
typedef struct
{
	ei_s32 Size;

	ei_s32 FriendOrEnemy;//---敵味方の区別
	ei_s32 Existence,ExistenceExtend,BaseType;//---このキャラが存在するかどうか、種族
	ei_s32 Element[16];//---弱点
	ei_u32 Ability[4];//---特殊能力

	ei_s32 FieldX,FieldY;//---座標

	ei_s32 Status;//---状態
	//---持続期間
	ei_s32 StatusContinue[BATTLESTATUS_MAX],
		StatusContinueMax[BATTLESTATUS_MAX];

	ei_s32 FromLastMagic;//---最後に魔法を使ってから何ターン経ったか

	//---敵キャラクター情報
	CRESTEAJU_ENEMYINFO Enemy;
} CRESTEAJU_BATTLECHARAINFO , *LPCRESTEAJU_BATTLECHARAINFO;

//------------------------------------------
//---メインオブジェクト情報
typedef struct
{
	ei_s32 Size;
	eistr Name[32],KanaName[64],Help[64];

	ei_s32 *pSort[8];//---継承クラスからのソート、表示用ポインタ
} CRESTEAJU_MATERIALINFO,*LPCRESTEAJU_MATERIALINFO;

//---アイテム
typedef struct
{
	ei_s32 Size;

	ei_s32 Index,Kind,Value,ItemStatus,Element,Special,Scene;
	//種類、値段、ステータス（属性）、属性（火・水・・・）、スペシャル

	ei_s32 DamageStatus,//---ダメージ種類（攻撃力＋力／攻撃力のみ）
		AtackKind,Anime,//---攻撃種類（直接／間接）、アニメーション
		Atack,Defense,Action,MagicDefense,
		Power,Vitality,Agility,Soul,Magic,
		Equipment,User;//---装備可能者、使用可能者
	ei_u32 EquipStatus;//---装備防御（追加防御効果）
	ei_s32 FreeData[4];//---フリーデータ部分
	ei_s32 Sound;//---サウンド
	ei_s32 Range,Target;//---効果範囲、対象（敵味方）

	ei_s32 ClassDefenseRate[16];//---属性防御率
	ei_s32 HitProb,AvoidProb,MagicAvoidProb;//---回避率、命中率,魔法回避率
		
} CRESTEAJU_ITEMINFO,*LPCRESTEAJU_ITEMINFO;

//---魔法情報
typedef struct
{
	ei_s32 Size;

	ei_s32 Index,Level,UseMC,Element,Kind,Damage,SubDamage,HitProb,Special;
	ei_s32 Diffuse; //---分散度
	ei_s32 Range[2],Target[2];//---効果範囲、対象（敵味方）
	ei_s32 Scene;//---使用シーン
	ei_s32 FreeData[4];

} CRESTEAJU_MAGICINFO,*LPCRESTEAJU_MAGICINFO;

//---必殺技情報
typedef struct
{
	ei_s32 Size;

	ei_s32 Index,Number,CommandType,
		Level,Who,Event,//---レベル、誰が、条件イベント
		WeaponKind,//---武器の種類
		WeaponNumber[4],//---使用可能武器
		SPAtackCount,//---攻撃回数

		Damage,UseMC,ResultLP,ResultMC,
		AtackCount,MagicCount,AvoidCount,GiveMissCount,DefenseCount,

		Range,Target;

	ei_s32 DamageRate,SubDamageRate,DamageDiffuse,DisableTurn;

} CRESTEAJU_SPECIALINFO,*LPCRESTEAJU_SPECIALINFO;

//---MessageFile
#include "CrMessageFile.h"

#endif /* INCLUDE_CRDEF */
