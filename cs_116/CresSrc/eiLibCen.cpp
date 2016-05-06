/*-----------------------------------------------------------

   eiLibray
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   eiLibCen.cpp ...eiLibrary Main

-----------------------------------------------------------*/

//--------------------
EI_API int eiGetClipingRect(LPRECT lpOut,LPRECT lpSrc,LPRECT lpDst,
					 int tx,int ty);
EI_API void eiDebugWriteFile(EISTR *s);
EI_API int eiSetLastError(int error);
EI_API int eiGetLastError(void);
EI_API int eiGetDebugMode(void);

EI_API void eiSwap(int *a,int *b);
EI_API int DrawTextMemory(LPBYTE lpMemory,int Direction,int MemorySize,int LineSize,
						  EISTR *String,int x,int y,int color,int efect);
EI_API int eiGetTime(void);
EI_API void eiChangePoint(int *x,int *y);
EI_API void eiChangeRect(LPRECT lpRect);

EI_API void eiCheckThread(void);


int eiFlag = 0;

/*//---バージョン、上位バイトが整数部分、下位バイトが小数部分
WORD eiLibraryVersion = (0 << 8) | (13);
*/

//-------------------------------------------------
//---システム構造体
EISYSTEMDATA eiSystem;

//-------------------------------------------------
//---文字列描画用DIB
eiDib eiDibDrawText;

//---フォント
HFONT eiFont[16];
EISIZE eiFontSize[8];
int eiUseDirectText;
//---カーソル
static HCURSOR hCursor[6];

//-------------------------------------------------
//---ウィンドウ
eiWindow *lpMainWindow;
RECT eiWindowRect;
HWND hMainWindow = NULL;

//---サーフェイスモード
int eiSurfaceMode[EI_SURFACE_MAX];

#ifdef EIUSE_LINK
	#include "eiLink.cpp"
#endif /* EI_USELINK */
#include "eiMath.cpp"
#include "eiDebug.cpp"
#include "eiSub.cpp"

#ifdef EIUSE_FILE
	#include "eiFile.cpp"
#endif

#ifdef EIUSE_BITSTREAM
	#include "eiBitStream.cpp"
#endif

//-------------------------------------------------------------
#ifdef EI_RUNWINDOWS
	#ifdef EIUSE_DIRECTDRAW
		#include "eiDDraw.cpp"
	#endif
#endif
//-------------------------------------------------------------

//-------------------------------------------------------------
#ifdef EI_RUNWINDOWS
	#ifdef EIUSE_SOUND
		#include "eiSound.cpp"
	#endif
#endif
//-------------------------------------------------------------

#ifdef EIUSE_DIB
	#include "eiDib.cpp"
#endif

#ifdef EIUSE_SCRIPT
	#include "eiScript.cpp"
#endif

#ifdef EIUSE_TIME
	#include "eiTime.cpp"
#endif

#ifdef EIUSE_CELL
	#include "eiCell.cpp"
	#ifdef EI_RUNWINDOWS
		#ifdef EIUSE_DIRECT3D
			#include "eiTextureCell.cpp"
	#endif
	#endif
#endif

#ifdef EIUSE_PALETTE
	#include "eiPal.cpp"
#endif

//-------------------------------------------------------------
#ifdef EI_RUNWINDOWS
	#ifdef EIUSE_INPUT
		#include "eiInput.cpp"
	#endif
#endif
//-------------------------------------------------------------

#ifdef EIUSE_WINDOW
	#include "eiWindow.cpp"
#endif

/*
//---eiLibraryのバージョン取得
EI_API WORD eiGetLibraryVersion(void)
{
	return eiLibraryVersion;
}*/

//---eiLiblaryシステム構造体のコピー
EI_API void eiGetLibrarySystemInfo(EISYSTEMDATA *sys)
{
	memcpy(sys,&eiSystem,sizeof(eiSystem));
}

//---eiLibrary初期化
EI_API int eiInit(int ScreenMode /*= DIRECTDRAW_FULLSCREEN | EICOLOR_8BIT*/,
				  int xScreen /*= 640*/,int yScreen /*= 480*/,
				  int xBuffer /*= 640*/,int yBuffer /*= 480*/,
				  int Plane /*= 1*/,int xFont /*= 8*/,int yFont /*= 16*/,
				  char *FontName /*= "ＭＳ ゴシック"*/)
{
	int a;

	//---変数初期化
	eiUseDirectText = 0;
	lpMainWindow = NULL;
	//---構造体初期化
	memset(&::eiSystem,0,sizeof(::eiSystem));

	::eiSystem.ScreenMode = ScreenMode;
	::eiSystem.xScreenSize = xScreen;
	::eiSystem.yScreenSize = yScreen;
	::eiSystem.xBufferSize = xBuffer;
	::eiSystem.yBufferSize = yBuffer;
	::eiSystem.xFontSize = xFont;
	::eiSystem.yFontSize = yFont;
	::eiSystem.Plane = Plane;
	::eiSystem.TransColor = 16;
	::eiSystem.ClearColor = 16;
	::eiSystem.ColorBit = 8;
	::eiSystem.DisplayRefreshRate = 60;
	::eiSystem.DrawRefreshRate = 60;
	memset(&::eiWindowRect,0,sizeof(::eiWindowRect));

	::eiFlag = 1;
	//---ハーフサイズスクリーン
	if(::eiSystem.ScreenMode & HALFSIZESCREEN)
		::eiSystem.ScreenZoomRate = 1;

	//---乱数初期化
	eiInitRnd();

	//---三角関数初期化
//	eiInitSinTable();

	//カーソル読み込み

	hCursor[0] = LoadCursor(NULL,IDC_ARROW);
//	hCursor[1] = LoadCursor(NULL,IDC_WAIT);


	//---画面モード
	if(::eiSystem.ScreenMode & EICOLOR_8BIT){
		::eiSystem.ColorBit = 8;
	} else if(::eiSystem.ScreenMode & EICOLOR_16BIT){
		::eiSystem.ColorBit = 16;
	} else if(::eiSystem.ScreenMode & EICOLOR_24BIT){
		::eiSystem.ColorBit = 24;
	} else if(::eiSystem.ScreenMode & EICOLOR_32BIT){
		::eiSystem.ColorBit = 32;
	}

	//---フォント作成
	for(a = 0;a < 16;a ++){
		eiFont[a] = NULL;
	}

	eiFont[EINORMAL_FONT] = CreateFont(
			yFont,xFont,//16,8
			0,0,FW_NORMAL,
			FALSE,FALSE,FALSE,
			SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			NONANTIALIASED_QUALITY,
			FIXED_PITCH | FF_MODERN,
			FontName
	);
	eiFontSize[EINORMAL_FONT].x = xFont;
	eiFontSize[EINORMAL_FONT].y = yFont;
	if(!eiFont[EINORMAL_FONT]){
		::eiLastError = EIER_CANTCREATE_FONT;
		return 0;
	}
//32*32フォント作成
	eiFont[EILARGE_FONT] = CreateFont(
			(int)(yFont * 1.50),(int)(xFont * 1.50),//16,8
			0,0,FW_NORMAL,
			FALSE,FALSE,FALSE,
			SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			NONANTIALIASED_QUALITY,
			FIXED_PITCH | FF_MODERN,
			FontName
	);
	eiFontSize[EILARGE_FONT].x = (int)(xFont * 1.50);
	eiFontSize[EILARGE_FONT].y = (int)(yFont * 1.50);
	if(!eiFont[EILARGE_FONT]){
		::eiLastError = EIER_CANTCREATE_FONT;
		return 0;
	}
//12*12フォント作成
	eiFont[EISMALL_FONT] = CreateFont(
			(int)(yFont * 0.75),(int)(xFont * 0.75),//16,8
			0,0,FW_NORMAL,
			FALSE,FALSE,FALSE,
			SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			NONANTIALIASED_QUALITY,
			FIXED_PITCH | FF_MODERN,
			FontName
	);
	eiFontSize[EISMALL_FONT].x = (int)(xFont * 0.75);
	eiFontSize[EISMALL_FONT].y = (int)(yFont * 0.75);
	if(!eiFont[EISMALL_FONT]){
		::eiLastError = EIER_CANTCREATE_FONT;
		return 0;
	}
//32*32フォント作成
	eiFont[EI2WIDTH_FONT] = CreateFont(
			(int)(yFont * 1.00),(int)(xFont * 1.75),//16,8
			0,0,FW_NORMAL,
			FALSE,FALSE,FALSE,
			SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			NONANTIALIASED_QUALITY,
			FIXED_PITCH | FF_MODERN,
			FontName
	);
	eiFontSize[EI2WIDTH_FONT].x = (int)(xFont * 1.75);
	eiFontSize[EI2WIDTH_FONT].y = (int)(yFont * 1.00);
	if(!eiFont[EI2WIDTH_FONT]){
		::eiLastError = EIER_CANTCREATE_FONT;
		return 0;
	}

	//---セマフォ作成
	hCriticalSection = NULL;
	hCriticalSection = CreateSemaphore(NULL,1,1,NULL);

	return 1;
}

//---終了
EI_API void eiEnd(void)
{
	int a;

	if(!::eiFlag)
		return;
	//---セマフォ
	CloseHandle(hCriticalSection);

	//---フォント削除
	for(a = 0;a < 16;a ++){
		if(eiFont[a] != NULL){
			DeleteObject(eiFont[a]);
			eiFont[a] = NULL;
		}
	}

#ifdef EIUSE_DIRECTDRAW
	//---DirectDraw終了
	if((::eiSystem.ScreenMode & DIRECTDRAW_MODE) != 0){
		eiDDEnd();
	}
#endif

#ifdef DRAWTEXT_USE_DIBSECTION
	//---DIBSectionを削除
	DeleteDC(eiDibDrawText.hMemoryDC);
	eiDibDrawText.Delete();
#endif /*DRAWTEXT_USE_DIBSECTION*/

	//---ハンドル解放
/*	DeleteObject(hCursor[1]);
	DeleteObject(hCursor[0]);
*/

	::eiFlag = 0;
}

//---DirectDrawの初期化・ディスプレイモード切替
EI_API int eiInitGraphicSystem(eiWindow *ew,int refresh_rate /*= 0*/)
{
	int a = 0,b,col = 8,mode = 0,DDInitMode = 0;
	HWND hwnd  = ew->hwnd;

//---debug
eiDebugWriteFile("(eiInitGraphicSystem) ;Start.\n");

	//---テキスト処理用のＤＩＢセクション作成
#ifdef DRAWTEXT_USE_DIBSECTION
	HDC hdc,mem_dc;
	
	hdc = GetDC(hwnd);
	mem_dc = CreateCompatibleDC(hdc);
	ReleaseDC(hwnd,hdc);

	if(!eiDibDrawText.Create(64,64,8,EIDIB_DIBSECTION)){
		//---ここのサイズを変えればさらに大きいフォントも表示可能
		::eiLastError = EIER_CANTCREATE_TEXTDIB;
		return 0;
	}
	eiDibDrawText.hMemoryDC = mem_dc;
//---debug
eiDebugWriteFile("(eiInitGraphicSystem) DrawTextDIB;Success\n");
#endif /*DRAWTEXT_USE_DIBSECTION*/


	if(::eiSystem.ScreenMode & EICOLOR_8BIT){
		col = 8;
		::eiSystem.ColorBit = 8;
	}
	if(::eiSystem.ScreenMode & EICOLOR_16BIT){
		col = 16;
		::eiSystem.ColorBit = 16;
	}
	if(::eiSystem.ScreenMode & EICOLOR_24BIT){
		col = 24;
		::eiSystem.ColorBit = 24;
	}
	if(::eiSystem.ScreenMode & EICOLOR_32BIT){
		col = 32;
		::eiSystem.ColorBit = 32;
	}
#ifdef EIUSE_DIRECTDRAW
	if(::eiSystem.ScreenMode & DIRECTDRAW_EMULATION)
		DDInitMode = DDCREATE_EMULATIONONLY;
#endif

	//---DirectDrawを使うなら初期化する
	if((::eiSystem.ScreenMode & DIRECTDRAW_MODE) != 0){
//-------------------------------------------------------------
#ifdef EI_RUNWINDOWS
#ifdef EIUSE_DIRECTDRAW
//---debug
eiDebugWriteFile("(eiInitGraphicSystem) DirectDraw Init;Start\n");

		//---DirectDraw初期化
		if(eiDDInit(hwnd,
			(::eiSystem.xScreenSize) >> (::eiSystem.ScreenZoomRate),
			(::eiSystem.yScreenSize) >> (::eiSystem.ScreenZoomRate),
			col,eiSystem.ScreenMode/*DDInitMode*/,
			refresh_rate) == FALSE){
			::eiLastError = EIER_CANTINIT_DIRECTDRAW;		
			return 0;
		}
//---debug
eiDebugWriteFile("(eiInitGraphicSystem) eiDDInit;Success\n");
		///---サーフェイス初期化
		if(eiDDSurfaceInit(hwnd) == FALSE){
//---debug
eiDebugWriteFile("(eiInitGraphicSystem) eiDDSurfaceInit;Failed\n");
			::eiLastError = EIER_CANTINIT_DDSURFACE;
			return 0;
		}
//---debug
eiDebugWriteFile("(eiInitGraphicSystem) eiDDSurfaceInit;Success\n");
		//---パターン用サーフェイスを初期化する
eidbMsg("(eiInitGraphicSystem) パターンサーフェイス作成前");
		for(b = 0;b < ::eiSystem.Plane + 1;b ++){
			if(eiSurfaceMode[b] & EI_SURFACE_SYSTEMMEMORY
				/*|| b >= ::eiSystem.Plane*/)
				mode = ESCREATE_SYSTEMMEMORY;
			else
				mode = 0;

			if(eiSurface[b + 2].Create(
				(::eiSystem.xBufferSize) >> (::eiSystem.ScreenZoomRate),
				(::eiSystem.yBufferSize) >> (::eiSystem.ScreenZoomRate),
				mode) == NULL){
//---debug
eiDebugWriteFile("(eiInitGraphicSystem) eiSurface[].Create;Failed\n");
			}
		}
eidbMsg("(eiInitGraphicSystem) パターンサーフェイス作成");
//---debug
eiDebugWriteFile("(eiInitGraphicSystem) Create DDSPattern;Success\n");

//透明色を設定
		eiSurface[0].SetSrcBltColorKey(::eiSystem.TransColor,::eiSystem.TransColor);
		eiSurface[1].SetSrcBltColorKey(::eiSystem.TransColor,::eiSystem.TransColor);

		for(b = 0;b < ::eiSystem.Plane + 1;b++){
			eiSurface[b + 2].SetSrcBltColorKey(::eiSystem.TransColor,::eiSystem.TransColor);
		}
//---debug
eiDebugWriteFile("(eiInitGraphicSystem) SetColorKey;Success\n");

		//---DirectDrawサーフェイスを、ewに設定
		for(b = 0;b < 2;b ++){
			SetRect(&ew->Cell[b].Data.rectSurface,
				0,0,eiSystem.xScreenSize  ,eiSystem.yScreenSize );
			ew->Cell[b].Data.SurfaceFlag = 1;
			ew->Cell[b].Data.SurfaceNumber = b;
			ew->Cell[b].pDDSurface = &eiSurface[b];
			ew->Cell[b].Data.Color = col;

			//---保存用バッファー
			if(b == 1){
				SetRect(&ew->BackCell[b].Data.rectSurface,
					0,0,eiSystem.xScreenSize  ,eiSystem.yScreenSize );
				ew->BackCell[b].Data.SurfaceFlag = 1;
				ew->BackCell[b].Data.SurfaceNumber = (::eiSystem.Plane + 2);
				ew->BackCell[b].pDDSurface = &eiSurface[::eiSystem.Plane + 2];
				ew->BackCell[b].Data.Color = col;
			}
		}
#endif
#endif
//-------------------------------------------------------------
	} else {
		if(col == 24){
			::eiSystem.RedBit = 8;
			::eiSystem.RedMask = 0x0000ff;
			::eiSystem.RedShift = 0;
			::eiSystem.GreenBit = 8;
			::eiSystem.GreenMask = 0x00ff00;
			::eiSystem.BlueShift = 8;
			::eiSystem.BlueBit = 8;
			::eiSystem.BlueMask = 0xff0000;
			::eiSystem.BlueShift = 16;
		}
	}
	//---マウスカーソルの表示を設定
	if((::eiSystem.ScreenMode & DIRECTDRAW_FULLSCREEN) != 0){
		ShowCursor(FALSE);
	}

	//---描画準備ＯＫ
	::eiSystem.Ready = 1;
	b = 0;

	return 1;
}

//---サーフェイスの設定
EI_API void eiSetSurfaceMode(int number,int mode)
{
	if(number >= EI_SURFACE_MAX)
		return;

	eiSurfaceMode[number] = mode;
}

//---フルスクリーンか、ウィンドウ表示かを得る
EI_API int eiGetFullScreen(void)
{
	if(eiSystem.ScreenMode & DIRECTDRAW_FULLSCREEN)
		return 1;
	return 0;
}

//---描画可能かどうか
EI_API int eiGetCanDoDraw(void)
{
	return eiSystem.Ready;
}

//-------------------------------------------------------------
//---スレッド終了送信
static ei_s32 eiEndThreadFlag = 0,eiRunThreadFlag = 1,eiEnableCheckThreadFlag = 1;

//---チェック許可
EI_API int eiEnableCheckThread(int enable)
{
	int old = eiEnableCheckThreadFlag;

	if(enable != -1){
		eiEnableCheckThreadFlag = enable;
	}

	return old;
}

EI_API void eiSetEndThread(void)
{
	eiEndThreadFlag = 1;
}

EI_API ei_s32 eiGetRunThreadFlag(void)
{
	return eiRunThreadFlag;
}

//---スレッドチェック
EI_API ei_s32 eiGetEndThread(void)
{
	return eiEndThreadFlag;
}

EI_API void eiCheckThread(void)
{
	//---チェックしない
	if(eiEnableCheckThreadFlag == 0)
		return;

	if(eiEndThreadFlag == 1 && eiRunThreadFlag == 1){
		eiRunThreadFlag = 0;
		eiDebugWriteFile("eiLibrary::_endthread()\n");
#ifdef USE_WINAPI_THREAD
#else
		_endthread();
#endif /* USE_WINAPI_THREAD */
	}
}

EI_API void eiSetRunThreadFlag(int flag)
{
	eiRunThreadFlag = 0;
}
//-------------------------------------------------------------

//---メッセージループ
EI_API int eiMessageLoop(eiWindow *ew,int (*MainCode)(void) /*= NULL*/)
{
//-------------------------------------------------------------
#ifdef EI_RUNWINDOWS

	int RunCode = 1;
	MSG msg;

	lpMainWindow = ew;

	if(MainCode == NULL){
		//---メッセージループ用の関数がなければ
		while(GetMessage(&msg,NULL,0,0)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	} else {
		while(1){
			if(PeekMessage(&msg,NULL,0,0,PM_NOREMOVE)){
				if(!GetMessage(&msg,NULL,0,0))
					break;
				if(msg.message == WM_DESTROY || msg.message == WM_CLOSE)
					RunCode = 0;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			} else {
				if(RunCode){
					if(MainCode() == 0){//---メッセージループ関数呼び出し
						//---これ以上メッセージループを続ける必要がなければ
						//---WM_DESTROY送信
						PostMessage(ew->hwnd,WM_DESTROY,0,0);
						RunCode = 0;
					}
				}
			}
		}
	}

	return msg.wParam;

#endif
//-------------------------------------------------------------
}

//---クリッピング計算
EI_API int eiGetClipingRect(LPRECT lpOut,LPRECT lpSrc,LPRECT lpDst,
					 int tx,int ty)
{
	//---２つの領域が重ならなければ
/*	if( (lpDst->right < lpSrc->left + tx)
		|| (lpDst->bottom < lpSrc->top + ty) )
		return 0;*/
	if( (lpDst->right < tx)
		|| (lpDst->bottom < ty) )
		return 0;
	//---
	if(tx < lpDst->left)
		lpOut->left = lpDst->left - (lpSrc->left + tx);
	 else
		lpOut->left = lpSrc->left;

	if(lpDst->right < (lpSrc->right - lpSrc->left) + tx)
		lpOut->right = lpDst->right - (lpSrc->left + tx);
	else
		lpOut->right = lpSrc->right;

	//-----------------------------------
	if(ty < lpDst->top)
		lpOut->top = lpDst->top - (lpSrc->top + ty);
	else
		lpOut->top  = lpSrc->top;

	if(lpDst->bottom < (lpSrc->bottom - lpSrc->top) + ty)
		lpOut->bottom = lpDst->bottom - (lpSrc->top + ty);
	else
		lpOut->bottom = lpSrc->bottom;

	return 1;
}

//---フリップ設定
EI_API int eiSetFlipMode(int mode)
{
	int Old = ::eiSystem.ScreenMode;

	if(Old & DIRECTDRAW_FLIPBLT){
		Old = 0;
	} else {
		Old = 1;
	}

	if(mode == 1){
		//---ハードウェアフリップ
		 ::eiSystem.ScreenMode &= (~DIRECTDRAW_FLIPBLT);
	} else {
		//---Blt転送によるフリップ
		 ::eiSystem.ScreenMode |= (DIRECTDRAW_FLIPBLT);
	}

	return Old;
}

//---リフレッシュレート
EI_API int eiSetDisplayRefreshRate(int rate)
{
	int Old = ::eiSystem.DisplayRefreshRate;

	if(rate != -1){
		::eiSystem.DisplayRefreshRate = rate;
	}

	return Old;
}

EI_API int eiSetDrawRefreshRate(int rate)
{
	int Old = ::eiSystem.DrawRefreshRate;

	if(rate != -1){
		::eiSystem.DrawRefreshRate = rate;
	}

	return Old;
}
