#ifndef EI_LIB_H

#define EI_LIB_H

//---Init
#ifdef EI_LIB

#else

extern EI_API int eiInit(int ScreenMode = DIRECTDRAW_FULLSCREEN | EICOLOR_8BIT,
				int xScreen = 640,int yScreen = 480,
				int xBuffer = 640,int yBuffer = 480,
				int Plane = 1,int xFont = 8,int yFont = 16,
				char *FontName = "ÇlÇr ÉSÉVÉbÉN");
extern EI_API void eiEnd(void);
extern EI_API WORD eiGetLibraryVersion(void);
extern EI_API void eiGetLibrarySystemInfo(EISYSTEMDATA *sys);
//---thread
extern EI_API void eiSetEndThread(void);
extern EI_API ei_s32 eiGetEndThread(void);
extern EI_API ei_s32 eiGetRunThreadFlag(void);
extern EI_API void eiSetRunThreadFlag(int flag);
extern EI_API void eiCheckThread(void);
extern EI_API int eiEnableCheckThread(int enable);

//---Message
extern EI_API LRESULT CALLBACK eiDefaultWindowFunc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam);
extern EI_API int eiMessageLoop(eiWindow *ew,int (*MainCode)(void) = NULL);

//---Graphic System
extern EI_API int eiInitGraphicSystem(eiWindow *ew,int refresh_rate = 0);
extern EI_API int eiGetCanDoDraw(void);

//---Pattern
extern EI_API int eiCellReadPattern(eiCell *cell,LPSTR name,LPSTR slname,int mode,
							int top,int num,int sx,int sy);
extern EI_API void eiCellSetSurface(eiCell *cell,int x,int y,
					  int sx,int sy,int num ,int plane = 2);
#ifdef EIUSE_DIRECTDRAW
extern EI_API int eiTextureCellReadPattern(eiTextureCell *cell,EISTR *name,EISTR *slname,int mode,
							int top,int num,int sx,int sy);
extern EI_API void eiTextureCellSetSurface(eiTextureCell *cell,int x,int y,
					  int sx,int sy,int num ,int plane = 2);
#endif /* EIUSE_DIRECTDRAW */

//---Screen
extern EI_API int eiGetFullScreen(void);
extern EI_API void eiSetSurfaceMode(int number,int mode);
extern EI_API int eiSetDisplayRefreshRate(int rate);
extern EI_API int eiSetDrawRefreshRate(int rate);
extern EI_API int eiSetFlipMode(int mode);
extern EI_API void eiGetWindowRect(LPRECT lpRect);

//---Other
extern EI_API HCURSOR eiSetCursor(int num);
extern EI_API int eiSetFont(int number);
extern EI_API void eiSetWindowSize(HWND hwnd,int xs,int ys);
extern EI_API void eiGetClient(HWND hwnd);
extern EI_API void eiSleep(int n);
extern EI_API int eiSetDirectText(int mode);
extern EI_API int eiCompareString(eistr *st1,eistr *st2);

//---DirectDraw
#ifdef EIUSE_DIRECTDRAW
	extern EI_API int eiDDInit(HWND hwnd,int xs,int ys,int color,int mode,int refresh_rate);
	extern EI_API int eiDDSurfaceInit(HWND hwnd);
	extern EI_API eiDDSurface* eiGetSurfacePointer(void);
	extern EI_API BOOL eiDDInitIMTextureFormats();
	extern EI_API EI_DDINFO *eiGetDDInfo(void);
#endif /*EIUSE_DIRECTDRAW*/

//---Math
extern EI_API void eiSwap(int *a,int *b);
extern EI_API int eiAbs(int n);
extern EI_API int eiRnd(int n);
extern EI_API void eiInitRnd(void);
extern EI_API int eiSin(int n);
extern EI_API int eiCos(int n);
extern EI_API int eiGetAngle(int x1,int y1,int x2,int y2);
extern EI_API void eiCheckAngle(int *n);

extern EI_API int eiGetStringItem(EISTR *find_str,EISTR *in_str,EISTR *out_str,int *out_ad);

//---Memory
extern EI_API void eimemset(void *memory,int set,int size);
extern EI_API EIMEMORY eiAllocMemory(int size);
extern EI_API EIMEMORY eiReallocMemory(EIMEMORY eiMem,int size);
extern EI_API EIMEMORY eiFreeMemory(EIMEMORY eiMem);
extern EI_API LPVOID eiLockMemory(EIMEMORY eiMem);
extern EI_API int eiUnlockMemory(EIMEMORY eiMem);
extern EI_API void eiMemoryOutputForDebug(void);
extern EI_API void eiMemorySetPointerForDebug(void *pMemory);
extern EI_API void eiMemoryDeletePointerForDebug(void *pMemory);

//----Semaphore
extern EI_API int eiWaitCriticalSection(ei_u32 WaitTime);
extern EI_API int eiReleaseCriticalSection(void);

//---3D
extern int EI_API eiInitDirect3D(void);
extern int EI_API eiEndDirect3D(void);

//---sound
extern EI_API int eiInitSound(eiWindow *ew,int mode = 0);
extern EI_API int eiEndSound(void);
extern EI_API int eiSoundSetVolume(int vol);
extern EI_API int eiSoundGetVolume(void);

//---debug
extern EI_API void eiDebugWriteFile(EISTR *s);
extern EI_API int eiSetDebugMode(int mode);
extern EI_API int eiGetDebugMode(void);
extern EI_API void eiDebugInitFile(void);
extern EI_API int eiSetLastError(int error);
extern EI_API int eiGetLastError(void);
extern EI_API int eiMsgBox(eistr *string = NULL,eistr *title = NULL,
						   int mode = MB_OK);

extern int eiSinTable[360],eiCosTable[360],eiaTanTable[1024];
extern EISYSTEMDATA eiSystem;

#endif /* EI_LIB */
#endif /* EI_LIB_H */