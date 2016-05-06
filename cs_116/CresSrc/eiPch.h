//-----------------------
#ifdef EI_PCH

#else

#define EI_PCH
#define EI_RUNWINDOWS

#define EIUSE_LINK
#define EIUSE_FILE
#define EIUSE_BITSTREAM
#define EIUSE_SUBFUNCTION
#define EIUSE_TIME
#define EIUSE_SOUND
#define EIUSE_DIRECTDRAW
#define EIUSE_DIRECT3D
#define EIUSE_PALETTE
#define EIUSE_WINDOW
#define EIUSE_CELL
#define EIUSE_DIB
#define EIUSE_INPUT
#define EIUSE_JOYSTICK
#define EIUSE_SCRIPT

#define DRAWTEXT_USE_DIBSECTION

#define USE_WINAPI_THREAD

#define VC_EXTRALEAN

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include <time.h>
#include <mbctype.h>
#include <io.h>

#ifndef D3D_OVERLOADS
	#define D3D_OVERLOADS
#endif /* D3D_OVERLOADS */
#ifndef STRICT
	#define STRICT
#endif /* STRICT */
#include <ddraw.h>
#ifdef EIUSE_DIRECT3D
	#include <d3d.h>
#endif /* EIUSE_DIRECT3D */
#ifdef EIUSE_SOUND
	#include <dsound.h>
#endif

#endif
