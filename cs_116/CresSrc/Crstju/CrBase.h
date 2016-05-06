#ifndef INCLUDE_CRBASE_H

#define INCLUDE_CRBASE_H

//---------------------------------------------------------
//---------------------------------------------------------
#ifdef MAKE_DLL
	#ifdef FILE_CRBASEDLLMAIN
		#define CRBASEDLLMAIN_API __declspec(dllexport)
	#else
		#define CRBASEDLLMAIN_API extern
	#endif /*FILE_CRBASEDLLMAIN*/

	#ifdef FILE_CRBASE
		#define CRBASE_API __declspec(dllexport)
		#define CRBASE_CLASS __declspec(dllexport)
	#else
		#define CRBASE_API extern
		#define CRBASE_CLASS 
	#endif /*FILE_CRBASE*/

	#ifdef FILE_CRBASE_FIELDAPI
		#define CRBASE_FIELDAPI __declspec(dllexport)
	#else
		#define CRBASE_FIELDAPI extern
	#endif /*FILE_CRBASE_FIELDAPI*/

	#ifdef FILE_CRBASE_CHARAAPI
		#define CRBASE_CHARAAPI __declspec(dllexport)
	#else
		#define CRBASE_CHARAAPI extern
	#endif /*FILE_CRBASE_CHARAAPI*/

	#ifdef FILE_CRBASE_MATERIALAPI
		#define CRBASE_MATERIALAPI __declspec(dllexport)
	#else
		#define CRBASE_MATERIALAPI extern
	#endif /*FILE_CRBASE_MATERIALAPI*/

	#ifdef FILE_CRBASE_ITEMAPI
		#define CRBASE_ITEMAPI __declspec(dllexport)
	#else
		#define CRBASE_ITEMAPI extern
	#endif /*FILE_CRBASE_ITEMAPI*/

	#ifdef FILE_CRBASE_MAGICAPI
		#define CRBASE_MAGICAPI __declspec(dllexport)
	#else
		#define CRBASE_MAGICAPI extern
	#endif /*FILE_CRBASE_MAGICAPI*/

	#ifdef FILE_CRBASE_SHOPAPI
		#define CRBASE_SHOPAPI __declspec(dllexport)
	#else
		#define CRBASE_SHOPAPI extern
	#endif /*FILE_CRBASE_SHOPAPI*/

	#ifdef FILE_CRBASE_FILEAPI
		#define CRBASE_FILEAPI __declspec(dllexport)
	#else
		#define CRBASE_FILEAPI extern
	#endif /*FILE_CRBASE_FILEAPI*/

	#ifdef FILE_CRBASE_EFECTAPI
		#define CRBASE_EFECTAPI __declspec(dllexport)
	#else
		#define CRBASE_EFECTAPI extern
	#endif /*FILE_CRBASE_EFECTAPI*/

	#ifdef FILE_CRBASE_SOUNDAPI
		#define CRBASE_SOUNDAPI __declspec(dllexport)
	#else
		#define CRBASE_SOUNDAPI extern
	#endif /*FILE_CRBASE_SOUNDAPI*/

	#ifdef FILE_CRBASE_SCREENAPI
		#define CRBASE_SCREENAPI __declspec(dllexport)
	#else
		#define CRBASE_SCREENAPI extern
	#endif /*FILE_CRBASE_SCREENAPI*/

	#ifdef FILE_CRBASE_YARIKOMIAPI
		#define CRBASE_YARIKOMIAPI __declspec(dllexport)
	#else
		#define CRBASE_YARIKOMIAPI extern
	#endif /*FILE_CRBASE_YARIKOMIAPI*/
//---------------------------------------------------------
//---------------------------------------------------------
#else
	#ifdef FILE_CRBASEDLLMAIN
		#define CRBASEDLLMAIN_API
	#else
		#define CRBASEDLLMAIN_API extern
	#endif /*FILE_CRBASEDLLMAIN*/

	#ifdef FILE_CRBASE
		#define CRBASE_API 
		#define CRBASE_CLASS 
	#else
		#define CRBASE_API extern
		#define CRBASE_CLASS 
	#endif /*FILE_CRBASE*/

	#ifdef FILE_CRBASE_FIELDAPI
		#define CRBASE_FIELDAPI 
	#else
		#define CRBASE_FIELDAPI extern
	#endif /*FILE_CRBASE_FIELDAPI*/

	#ifdef FILE_CRBASE_CHARAAPI
		#define CRBASE_CHARAAPI 
	#else
		#define CRBASE_CHARAAPI extern
	#endif /*FILE_CRBASE_CHARAAPI*/

	#ifdef FILE_CRBASE_MATERIALAPI
		#define CRBASE_MATERIALAPI 
	#else
		#define CRBASE_MATERIALAPI extern
	#endif /*FILE_CRBASE_MATERIALAPI*/

	#ifdef FILE_CRBASE_ITEMAPI
		#define CRBASE_ITEMAPI 
	#else
		#define CRBASE_ITEMAPI extern
	#endif /*FILE_CRBASE_ITEMAPI*/

	#ifdef FILE_CRBASE_MAGICAPI
		#define CRBASE_MAGICAPI 
	#else
		#define CRBASE_MAGICAPI extern
	#endif /*FILE_CRBASE_MAGICAPI*/

	#ifdef FILE_CRBASE_SHOPAPI
		#define CRBASE_SHOPAPI 
	#else
		#define CRBASE_SHOPAPI extern
	#endif /*FILE_CRBASE_SHOPAPI*/

	#ifdef FILE_CRBASE_FILEAPI
		#define CRBASE_FILEAPI 
	#else
		#define CRBASE_FILEAPI extern
	#endif /*FILE_CRBASE_FILEAPI*/

	#ifdef FILE_CRBASE_EFECTAPI
		#define CRBASE_EFECTAPI 
	#else
		#define CRBASE_EFECTAPI extern
	#endif /*FILE_CRBASE_EFECTAPI*/

	#ifdef FILE_CRBASE_SOUNDAPI
		#define CRBASE_SOUNDAPI
	#else
		#define CRBASE_SOUNDAPI extern
	#endif /*FILE_CRBASE_SOUNDAPI*/

	#ifdef FILE_CRBASE_SCREENAPI
		#define CRBASE_SCREENAPI 
	#else
		#define CRBASE_SCREENAPI extern
	#endif /*FILE_CRBASE_SCREENAPI*/

	#ifdef FILE_CRBASE_YARIKOMIAPI
		#define CRBASE_YARIKOMIAPI 
	#else
		#define CRBASE_YARIKOMIAPI extern
	#endif /*FILE_CRBASE_YARIKOMIAPI*/
#endif
//---------------------------------------------------------
//---------------------------------------------------------

//---下位ファイルインクルード
#include "CrSystem.h"
#include "CrObject.h"

#include "SMIDI.h"

//#ifndef FILE_CRBASE
	#include "CrWindow.h"
	#include "CrMessageManager.h"
	#include "CrInput.h"
//#endif /* FILE_CRBASE */

//---DLLMain
CRBASEDLLMAIN_API DWORD crbaseGetVersion(void);

//---CrBase----
CRBASE_API int crbaseInitDLL(CRESTEAJU_GAMEDATA *pgameusingdata,
							 CRESTEAJU_GAMEINFO *pgame,
							 CRESTEAJU_PARTYINFO *pparty,
							 CrCharacter *pplayer,
							 CrItem *pitem,CrMagic *pmagic,
							 int *pdebug,int *pfilemode,
							 CRESTEAJU_SYSTEM *psystem,CRESTEAJU_INITIALIZE *pini,
							 CRESTEAJU_EXEINFO *pexeInfo,
							 ei_u32 *pDumy);

CRBASE_API int crbaseSetAllData(int load_map = 0);
CRBASE_API CRESTEAJU_GAMEINFO *crbaseGetGameInfo(void);
CRBASE_API int crbaseLockCresteaju(void);
CRBASE_API int crbaseUnlockCresteaju(void);
//---menu
CRBASE_API void crbaseMenuReset(void);
CRBASE_API void crbaseMenuStart(int wait = -1);
CRBASE_API void crbaseInitMenuScene(void);
CRBASE_API void crbaseEndMenuScene(void);
CRBASE_API int crbaseSelectYesNo(eistr *pText = NULL,int x = -1,int y = -1);

//---money & walk
CRBASE_API int crbaseGetMoney(void);
CRBASE_API void crbaseSetMoney(int money);
CRBASE_API void crbaseAddMoney(int money);
CRBASE_API void crbaseShowMoney(int tx,int ty);
CRBASE_API void crbaseAddWalk(void);
CRBASE_API ei_s32 crbaseGetWalk(void);
//---play time
CRBASE_API void crbaseShowPlayTime(int tx,int ty,int refresh = 0);
CRBASE_API void crbaseCalcHour(int hour);
CRBASE_API void crbaseCalcMinute(int minute);
CRBASE_API void crbaseCalcSecond(int second);

//---Screen
CRBASE_SCREENAPI void crbaseClearScreen(int mode = 0x03);
CRBASE_SCREENAPI void crbaseCopyFromFrontPage(void);
CRBASE_SCREENAPI void crbaseSaveFrontPage(int screen = 0);
CRBASE_SCREENAPI void crbaseLoadFrontPage(void);
CRBASE_SCREENAPI void crbaseLoadWallPaper(int number);
CRBASE_SCREENAPI void crbaseSetWallPaperSuraface(void);

//---CrBase_Field
#define PALETTE_NORMAL 1
#define PALETTE_SUNSET 2
#define PALETTE_NIGHT 3
#define PALETTE_FOG 4
#define PALETTE_MONO 5

CRBASE_FIELDAPI int crfieldGetMapNumber(void);
CRBASE_FIELDAPI int crfieldGetMapScene(void);

CRBASE_FIELDAPI int crfieldChangeMapSceneS(int number,int scene,int sx,int sy,int force = 0,int music = 1);
CRBASE_FIELDAPI int crfieldChangeMap(int number,int scene,int force = 0,int music = 1);
CRBASE_FIELDAPI int crfieldChangeMapS(int number,int scene,int force = 0,int music = 1);
CRBASE_FIELDAPI void crfieldChangeScene(int scene,int sx = -1,int sy = -1);
CRBASE_FIELDAPI void crfieldChangeSceneS(int scene,int sx = -1,int sy = -1);
CRBASE_FIELDAPI void crfieldChangePos(int sx,int sy,int plane = -1);
CRBASE_FIELDAPI void crfieldChangePosS(int sx,int sy,int plane = -1);
CRBASE_FIELDAPI void crfieldChangePlane(int plane);
CRBASE_FIELDAPI void crfieldChangeMapMusic(int force = 0);
CRBASE_FIELDAPI void crfieldSetMapChangeCallBack(void (*lpCallBack)(int,int));
CRBASE_FIELDAPI void crfieldLoadAddData(void);
CRBASE_FIELDAPI void crfieldSetFadeRect(RECT *rect);

CRBASE_FIELDAPI int crfieldDrawAndWait(void);
CRBASE_FIELDAPI int crfieldWaitField(int wait = 1);
CRBASE_FIELDAPI void crfieldDoAnime(int frame = 1);
CRBASE_FIELDAPI int crfieldDrawField(int mode = 0/* 0:auto 1:force*/);
CRBASE_FIELDAPI void crfieldDrawFieldWait(int mode = 0 /*0:auto 1:force*/);
CRBASE_FIELDAPI void crfieldMove(int sx = 0,int sy = 0,int speed = -1);
CRBASE_FIELDAPI void crfieldMoveAll(int sx = 0,int sy = 0,int speed = -1);
CRBASE_FIELDAPI eiMapObject *crfieldGetObjectPointer(int Number);
CRBASE_FIELDAPI void crfieldTurnToPlayer(eiMapObject *pObject);
CRBASE_FIELDAPI void crfieldDrawFrame(void);
CRBASE_FIELDAPI int crfieldBasicDrawField(void);

CRBASE_FIELDAPI void crfieldShowMainCharacter(int show);
CRBASE_FIELDAPI void crfieldSetMainCharacter(int number);
CRBASE_FIELDAPI int crfieldReadMainCharacter(eistr *name = NULL);
CRBASE_FIELDAPI void crfieldDrawMainCharacter(eiCell *,int dir,int x32,int y32,int cx,int cy);

CRBASE_FIELDAPI void crfieldSetFieldObject(void);
CRBASE_FIELDAPI void crfieldPaletteChange(int number);
CRBASE_FIELDAPI void crfieldPaletteChange_Cell(eiCell *pcell,int number);

CRBASE_FIELDAPI void crfieldSetIgonoreEvent(int mode);
CRBASE_FIELDAPI int crfieldGetIgonoreEvent(void);
CRBASE_FIELDAPI int crfieldCheckBattle(int reset = 0);

CRBASE_FIELDAPI void crfieldSetGroundShipPos(void);

CRBASE_FIELDAPI int crfieldSetMainCharacterSurface(void);

//--------------------------------------------------
//---CrBase_Chara
#include "Crbase_Chara.h"
//--------------------------------------------------
//---CrBase_Material
#include "Crbase_Material.h"
//--------------------------------------------------

//---CrBase_FileAPI
//--- save 6 load
#define SAVE_FILE_MAX 16
#define SAVE_FILE_ID1 0x12345678
#define SAVE_FILE_ID2 0xdfa05798

//---memory save file
#define MEMORYSAVEFILE_NUMBER 32

CRBASE_FILEAPI int crfileGetSaveDataList(eistr *list,int mode);
CRBASE_FILEAPI int crfileSaveData(int number,ei_u32 id1,ei_u32 id2,int mode /*= 0*/);
CRBASE_FILEAPI int crfileLoadData(int number,ei_u32 id1,ei_u32 id2,int mode /*= 0*/);
CRBASE_FILEAPI int crfileGetSaveFileCount(void);

//--------------------------------------------------
//---CrBase_EfectAPI
CRBASE_EFECTAPI void crefectSetup3DEfect(void);
CRBASE_EFECTAPI void crefectScreenChange_FadeIn(RECT *pRect = NULL,int count = -1,int run_time = -1,int color = -1);
CRBASE_EFECTAPI void crefectScreenChange_FadeOut(RECT *pRect = NULL,int count = -1,int run_time = -1,int color = -1);
//CRBASE_EFECTAPI void crefectScreenChange(RECT *pRect = NULL,int count = -1);
CRBASE_EFECTAPI void crefectScreenChange_DualScreen(RECT *pRect = NULL,int count = -1);
CRBASE_EFECTAPI void crefectScreenChange_AlphaBlend(RECT *pRect = NULL,int count = -1);
CRBASE_EFECTAPI void crefectScreenEfect_Bomb(RECT *pRect = NULL,int count = -1,int vel = -1);
CRBASE_EFECTAPI void crefectScreenEfect_RotateZoom(RECT *pRect = NULL,int count = -1,int vel = -1);
CRBASE_EFECTAPI void crefectScreenEfect_FadeOut(RECT *pRect = NULL,int count = -1,int color = RGB(0,0,0),int mode = 0);
CRBASE_EFECTAPI void crefectScreenEfect_FadeIn(RECT *pRect = NULL,int count = -1,int color = RGB(0,0,0));
CRBASE_EFECTAPI void crefectSetFadeCallBack(int mode);

CRBASE_SCREENAPI int decode_image(eiCell *pdecode,eiCell *psrc,ei_u8 *pdif);

//--------------------------------------------------
//---CrBase_ShopAPI
#define SHOPMODE_BUY_ONLYONE 0x01
CRBASE_SHOPAPI int crshopIntoShop(int *pShopItem,int mode = 0,void (*pCallback)(void) = NULL);

//--------------------------------------------------
//---CrBase_SoundAPI
//---sound
CRBASE_SOUNDAPI void crsoundPlay(int number,int mode = 0);
CRBASE_SOUNDAPI void crsoundStop(int number,int mode = 0);
CRBASE_SOUNDAPI void crsoundAllStop(int number,int mode = 0);
//---music
CRBASE_SOUNDAPI eistr **crmusicGetTitleString(void);
CRBASE_SOUNDAPI int crmusicInitMusic(void);
CRBASE_SOUNDAPI int crmusicEndMusic(void);
CRBASE_SOUNDAPI void crmusicSetStream(int number);
CRBASE_SOUNDAPI void crmusicRestoreStream(int number);
CRBASE_SOUNDAPI void crmusicPlay(int number,int loop = 1,int mode = 0);
CRBASE_SOUNDAPI void crmusicStop(void);
CRBASE_SOUNDAPI void crmusicFadeIn(int speed = 20);
CRBASE_SOUNDAPI void crmusicFadeOut(int speed = 20);
CRBASE_SOUNDAPI void crmusicSetVolume(int volume);
CRBASE_SOUNDAPI int crmusicGetTimeFromStart(void);
CRBASE_SOUNDAPI void crmusicWait(int wait);
CRBASE_SOUNDAPI void crmusicMusicTest(void);
CRBASE_SOUNDAPI void crmusicSetWaitCallback(int mode);

//---history
CRBASE_API void crhistBattleCount(void);
CRBASE_API void crhistSubBattleCount(void);
CRBASE_API void crhistEscapeCount(void);
CRBASE_API void crhistAllGetMoney(int money);
CRBASE_API void crhistAllGetExperience(int exp);
CRBASE_API void crhistSetHistory(int number);

//---yarikomi
CRBASE_YARIKOMIAPI void crbaseYarikomi_Tansu(void);
CRBASE_YARIKOMIAPI void crbaseSetYarikomi(int number,int flag);
CRBASE_YARIKOMIAPI void crbaseYarikomi_Tansu(void);
CRBASE_YARIKOMIAPI void crbaseYarikomi_Hondana(void);
CRBASE_YARIKOMIAPI void crbaseYarikomi_Takarabako(void);
CRBASE_YARIKOMIAPI void crbaseYarikomi_Item(void);
CRBASE_YARIKOMIAPI void crbaseYarikomi_Magic(void);
CRBASE_YARIKOMIAPI void crbaseYarikomi_Money(void);


#endif /*INCLUDE_CRBASE_H*/
