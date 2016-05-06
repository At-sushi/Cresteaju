//
// eiLibrary
//

#ifdef EIDEF
#else

#define EIDEF

#ifdef EILIBRARY_DLL
	#define EI_API __declspec(dllexport)
#else
	#ifdef PACK_ALL
		#define EI_API
	#else
		#ifdef EILIBRARY_IMPORTDLL
			#define EI_API __declspec(dllimport)
		#else
			#define EI_API 
		#endif
	#endif
#endif

#define eiFunc EI_API

#include "eiLink.h"
#include "eiError.h"

//---メモリーテスト
#define CLASS_MEMORY_TEST

#define INIT_MEMORY_TEST(x) x=NULL

#define RELEASE_MEMORY_TEST(x) {\
	if(x != NULL){\
		unsigned char *pP = (unsigned char *)eiLockMemory(x);\
		if(pP != NULL){\
			if(pP[0] != 0 || pP[1] != 1 || pP[2] != 2 || pP[3] != 3\
			|| pP[4] != 4 || pP[5] != 5 || pP[6] != 6 || pP[7] != 7\
			|| pP[8] != 8 || pP[9] != 9 || pP[10] != 10 || pP[11] != 11\
			|| pP[12] != 12 || pP[13] != 13 || pP[14] != 14 || pP[15] != 15){\
				eiDebugWriteFile("memory error!!\n");\
			}\
			eiUnlockMemory(x);\
		}\
		eiFreeMemory(x);\
		x = NULL;\
	}\
}

#define ALLOC_MEMORY_TEST(x) {\
	x=eiAllocMemory(16);\
	unsigned char *pP = (unsigned char *)eiLockMemory(x);\
	if(pP != NULL){\
		pP[0] = 0;\
		pP[1] = 1;\
		pP[2] = 2;\
		pP[3] = 3;\
		pP[4] = 4;\
		pP[5] = 5;\
		pP[6] = 6;\
		pP[7] = 7;\
		pP[8] = 8;\
		pP[9] = 9;\
		pP[10] = 10;\
		pP[11] = 11;\
		pP[12] = 12;\
		pP[13] = 13;\
		pP[14] = 14;\
		pP[15] = 15;\
		eiUnlockMemory(x);\
	}\
}

//---本当はこんなことしちゃいけないんだろうな・・・
#ifndef DDBLT_WAIT
	#define DDBLT_WAIT 0
#endif
#ifndef DDBLT_KEYSRC
	#define DDBLT_KEYSRC 0
#endif

//---eiAllocMemoryの動作
#define USE_MALLOC
//---Memory
#ifdef USE_MALLOC
	typedef void * EIMEMORY;
#else
	typedef HGLOBAL EIMEMORY;
//	#define EIMEMORY HGLOBAL
#endif

//---DIBSection作成するかどうか
//#define DRAWTEXT_USE_DIBSECTION

//----------------------------------
//---eiInit
#define DIRECTDRAW_FULLSCREEN 0x0001
#define DIRECTDRAW_WINDOW 0x0002
#define DIRECTDRAW_MODE (0x0001 | 0x0002)
#define WINAPI_WINDOW 0x0004
#define DIRECTDRAW_FLIPBLT 0x0008

#define EICOLOR_8BIT 0x0100
#define EICOLOR_16BIT 0x0200
#define EICOLOR_24BIT 0x0400
#define EICOLOR_32BIT 0x0800

#define DIRECTDRAW_EMULATION 0x00010000
#define HALFSIZESCREEN 0x00020000
#define INIT_DIRECT3D 0x00100000
#define NOTUSE_HARDWARE3D 0x00200000
#define USE_3DRGBMODEL 0x00400000
#define USE_3DRAMPMODEL 0x00800000
#define NOUSE_ZBUFFER 0x01000000

//----------------------------------
//---eiSurface
#define EISURFACE_CALCCLIENT 0x0001
//---
#define ESCREATE_SYSTEMMEMORY 0x0001
#define ESCREATE_PRIMARYSURFACE 0x0002
#define ESCREATE_BACKSURFACE 0x0004
#define ESCREATE_ZBUFFER 0x0008
#define ESCREATE_3DCAPS 0x0010
#define ESCREATE_TEXTURE 0x0020
#define ESCREATE_TEMPTEXTURE 0x0040

//----------------------------------
//---File Mode
#define EI_NORMALFILE 0x0001
#define EI_LINKEDFILE 0x0002
#define EI_RESOURCEFILE 0x0004
#define EI_CLIPBOARD 0x0008

//----------------------------------
//---Graphic Output Mode
#define EI_PSET 0x0001
#define EI_TRANS 0x0002
#define EI_FORCEDDRAWPIXEL 0x0004
#define EI_COLORMATCH 0x0008
#define EI_ALPHA 0x0010

//----------------------------------
//---Surface Mode
#define EI_SURFACE_SYSTEMMEMORY 0x0001
//---
#define EI_SURFACE_MAX 128

//----------------------------------
//---eiDib
#define EIDIB_COLORTABLE_SIZE 1024
//---eiDib.Create
#define EIDIB_DIBSECTION 0x0001

//----------------------------------
//---Error
#define EI_NOERR 0
#define EI_ERR_UNSUPPORTED 1

//----------------------------------
//---------eiInput
#define EI_INPUTDEVICE_MAX 8
#define EI_INPUTBUTTON_MAX 16

#define EI_INPUT_KEY 0x00ff
#define EI_INPUT_LARGEKEY 0x0001
#define EI_INPUT_SMALLKEY1 0x0002
#define EI_INPUT_SMALLKEY2 0x0004

#define EI_INPUT_JOYSTICK 0xff00
#define EI_INPUT_JOY1 0x0100
#define EI_INPUT_JOY2 0x0200
#define EI_INPUT_JOY3 0x0400
#define EI_INPUT_JOY4 0x0800

#define EI_JOY_BUTTON_MAX 16
#define EI_JOY_MOVE_UP 280
#define EI_JOY_MOVE_DOWN 360
#define EI_JOY_MOVE_LEFT 280
#define EI_JOY_MOVE_RIGHT 360

#define KEY_Q 0x0020

typedef struct
{
#ifdef EIUSE_JOYSTICK
	JOYCAPS JoyCaps;
	JOYINFOEX JoyInfo;
#endif
} EIJOYINFO, *LPEIJOYINFO;


//----------------------------------
//---Script
#define EISCRIPT_DATAMAX 8
#define EISCRIPT_DEFINEMAX 16
#define EISCRIPT_BUFFER_MAX 32000
#define EISCRIPT_STRINGBUFFER_MAX 10000

//----------------------------------
//---Font
#define EINORMAL_FONT 0
#define EILARGE_FONT 1
#define EISMALL_FONT 2
#define EI2WIDTH_FONT 3

//----------------------------------
//---Sound
#define EISOUND_EMULATION 0x0001
#define EISOUND_SILENCE 0x0010
#define EISOUND_BUFFER_MAX 8

//----------------------------------
//---Console
#define EICONSOLE_BUFFER_MAX 256
#define EICONSOLE_WHITE 31
#define EICONSOLE_BLACK 16
#define EICONSOLE_BLUE 17
#define EICONSOLE_RED 18
#define EICONSOLE_GREEN 19
#define EICONSOLE_YELLOW 20

//---型宣言
#define EISTR char
#define LPEISTR char *
#define eistr EISTR
#define lpeistr LPEISTR
#define eibool short
#define lpeibool short *

#define ei_s8 char
#define lpei_s8 char *
#define ei_u8 unsigned char
#define lpei_u8 unsigned char *

#define ei_s16 short
#define lpei_s16 short *
#define ei_u16 unsigned short
#define lpei_u16 unsigned short *

#define ei_s32 int
#define lpei_s32 int *
#define ei_u32 unsigned int
#define lpei_u32 unsigned int *


typedef struct
{
	char String[80];
} EICONSOLE_STRING;

//---ポイント
typedef struct
{
	int x , y;
} EIPOINT,*LPEIPOINT;
//---サイズ
typedef struct
{
	int x , y;
} EISIZE,*LPEISIZE;

//---ストリング
typedef struct
{
	char String[32];
} EISTRING,*LPEISTRING;

//---スクリプト結果
typedef struct
{
	int Number;
	int Data[EISCRIPT_DATAMAX];
} EISCRIPT_RESULT ,*LPEISCRIPT_RESULT;

typedef struct
{
	int Ready;

	int ScreenMode,xScreenSize,yScreenSize,ScreenZoomRate;
	int xBufferSize,yBufferSize;
	int Plane,xFontSize,yFontSize;
	int TransColor,ClearColor,ColorBit;
	int ActiveFont;
	int RedShift,GreenShift,BlueShift;
	int RedBit,GreenBit,BlueBit;
	DWORD RedMask,GreenMask,BlueMask;
	int DisplayRefreshRate,DrawRefreshRate;
	HINSTANCE hThisInst;
} EISYSTEMDATA;

typedef struct
{
	LPBYTE lpMemory;
	int LineSize;
	int PixelSize;
} EILOCKEDCELL;

typedef struct
{
	int Flag;
	int InputDevice;
	int Up,Down,Left,Right;
	int Button[EI_INPUTBUTTON_MAX];
} EIINPUTDATA;

typedef struct
{
	int xSize,ySize,Color,CreateFlag;
//	int Counter[16];
	//---Clip
	RECT rectClip;

	//---DirectDraw Surface
	RECT rectSurface;
	int SurfaceFlag,SurfaceNumber;

} CELLDATA;

typedef struct
{
	WNDCLASSEX WindowClass;
	int xTop,yTop;//スクリーン座標
	int xSize,ySize;//ウィンドウサイズ
	int MouseCursol,CreateKeepBitmap;
	int Style;
	
	LPCSTR TitleName,WindowName;
	LPCSTR MenuName,IconName,smIconName;

} EIWINDOWSTYLE;

typedef struct {
    WORD palVersion;
    WORD palNumEntries;
    PALETTEENTRY palPalEntry[256];
} LOGPALETTE_256;

#ifdef EIUSE_SOUND
typedef struct {
	LPBYTE lpWaveData;
	DWORD dwWaveSize;
	int bufCount;
	int bufferIndex;

	LPWAVEFORMATEX lpwfmx;
	LPDIRECTSOUNDBUFFER lpDSBuffer[EISOUND_BUFFER_MAX];

	LPBYTE lpMemory;
} WAVEINFO, *LPWAVEINFO;
#endif

#endif
