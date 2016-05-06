
//---member
#define SHOWSTATUS_ONLYONE 0x0001
#define SHOWSTATUS_PARTYMEMBER 0x0002
#define SHOWSTATUS_BATTLEMEMBER 0x0004
//---max
#define SHOWSTATUS_MAX_1 0x0100
#define SHOWSTATUS_MAX_4 0x0200
#define SHOWSTATUS_MAX_5 0x0400
#define SHOWSTATUS_MAX_8 0x0800
#define SHOWSTATUS_DEFAULT SHOWSTATUS_MAX_5
//---window size
#define SHOWSTATUS_SMALLSIZE  0x00010000 //Name,LP,SP,MC and Max
#define SHOWSTATUS_NORMALSIZE 0x00020000 //Name,LP,SP,MC and Max
#define SHOWSTATUS_LARGESIZE  0x00040000 // + Face
//---option
#define SHOWSTATUS_STATUSBAR  0x01000000

//---Character
#define CRBASE_SELECTPLAYER_LP 0x0001
#define CRBASE_SELECTPLAYER_MC 0x0002
#define CRBASE_SELECTPLAYER_MAGICEXP 0x0004
#define CRBASE_SELECTPLAYER_EXPERIENCE 0x0008

CRBASE_CHARAAPI int crcharaLoadFace(int number);
CRBASE_CHARAAPI void crcharaShowStatus(CrStringWindow *pwin,int x,int y,ei_u32 mode);
CRBASE_CHARAAPI void crcharaDrawStatus(CrStringWindow *pwin);
CRBASE_CHARAAPI CrCharacter *crcharaGetPartyMember(int num);
CRBASE_CHARAAPI int crcharaSelectMember(int x,int y,int mode = 0,
									   eistr *title = NULL,CRWIN_SELECTINFO *pInfo = NULL,
									   int (*lpFunc)(CrSelectWindow *,eiCell *,int,ei_u32,ei_u32,int) = NULL);
CRBASE_CHARAAPI int crcharaNextMember(int member);
CRBASE_CHARAAPI int crcharaPreviousMember(int member);
CRBASE_CHARAAPI int crcharaGetStatusColor(int value,int max);
CRBASE_CHARAAPI void crcharaShowFace(int x,int y,int start,int end);
CRBASE_CHARAAPI void crcharaSetLevelStatus(int number,int level);
CRBASE_CHARAAPI void crcharaCheckBattleFieldPos(int number);
