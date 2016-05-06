/*-----------------------------------------------------------

   eiLibray
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   eiWindow.cpp ...eiWindow Class

-----------------------------------------------------------*/

//---------------------------
//	eiWindow
//---------------------------

eiWindow::eiWindow(void)
{
	//---変数を初期化
	eimemset(&eiWS,0,sizeof(eiWS));
	hwnd = NULL;
	hThisInstance = 0;

	eiWS.xTop = eiWS.yTop = CW_USEDEFAULT;
	eiWS.xSize = eiWS.ySize = CW_USEDEFAULT;

	eiWS.WindowName = "eiWindow";
	eiWS.IconName = IDI_APPLICATION;
	eiWS.smIconName = IDI_WINLOGO;
	eiWS.MenuName = NULL;

	eiWS.Style = WS_VISIBLE | WS_OVERLAPPEDWINDOW;

	lpPalette = 0;

	lpCell[0] = lpKeepCell[0] = &Cell[0];
	lpCell[1] = lpKeepCell[1] = &Cell[1];
	lpBackCell[0] = &BackCell[0];
	lpBackCell[1] = &BackCell[1];

	ShowFPSFlag = DrawFPS = FPS = 0;
}

//---デストラクタ
eiWindow::~eiWindow()
{
}

//---ウィンドウを作る
HWND eiWindow::Create(HINSTANCE hInst,LPCSTR TitleName,
		LRESULT CALLBACK WindowFunc(HWND,UINT,WPARAM,LPARAM),int use_ddraw)
{
	int a;

	hThisInstance =  hInst;


	//---ウィンドウクラスを初期化する
	memset(&eiWS.WindowClass,0,sizeof(eiWS.WindowClass));
	
	eiWS.WindowClass.hInstance = hInst;
	eiWS.WindowClass.lpszClassName = eiWS.WindowName;

	if(::eiSystem.ScreenMode & DIRECTDRAW_FULLSCREEN){
		eiWS.Style = WS_POPUP;
	} else {
		eiWS.Style = WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX;
	}

	//---タイトル
	eiWS.TitleName = TitleName;
	//---サイズ
	eiWS.xSize = ::eiSystem.xScreenSize;
	eiWS.ySize = ::eiSystem.yScreenSize;//CW_USEDEFAULT;

	eiWS.WindowClass.lpfnWndProc = WindowFunc;
	
	eiWS.WindowClass.cbSize = sizeof(WNDCLASSEX);

	eiWS.WindowClass.hIcon = NULL;//LoadIcon(hThisInstance,eiWS.IconName);
	eiWS.WindowClass.hIconSm = NULL;//LoadIcon(hThisInstance,eiWS.IconName);
	
	eiWS.WindowClass.hCursor =NULL;// LoadCursor(NULL,IDC_ARROW);

	eiWS.WindowClass.lpszMenuName = eiWS.MenuName;

	eiWS.WindowClass.cbClsExtra = 0;
	eiWS.WindowClass.cbWndExtra = 0;
	eiWS.WindowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	//---ウィンドウのセルを作る
	for(a = 0;a < 2;a ++){
		if(!Cell[a].Create(eiWS.xSize,eiWS.ySize,::eiSystem.ColorBit))
			return NULL;
		lpCell[a] = &Cell[a];
		if(use_ddraw){
			Cell[a].dib.Delete();
		}
	}
	//---保存用セルを作る
	for(a = 0;a < 2;a ++){
		if(!BackCell[a].Create(eiWS.xSize,eiWS.ySize,::eiSystem.ColorBit))
			return NULL;
		lpBackCell[a] = &BackCell[a];
		if(use_ddraw){
			BackCell[a].dib.Delete();
		}
	}

	//---ウィンドウクラスを登録
	if(!RegisterClassEx(&eiWS.WindowClass)){
		return NULL;
	}

	//---ウィンドウを作成
	hwnd = CreateWindowEx(
		NULL,
		eiWS.WindowName,
		eiWS.TitleName,
		eiWS.Style,
		eiWS.xTop,
		eiWS.yTop,
		eiWS.xSize,
		eiWS.ySize,
		NULL,
		NULL,
		hThisInstance,
		NULL
	);

	if(hwnd){
		//---ウィンドウが作成されていれば、表示、更新をする
		ShowWindow(hwnd,SW_RESTORE);
		UpdateWindow(hwnd);
	}

	return hwnd;
}

void eiWindow::Delete(void)
{
	int a;

	for(a = 0;a < 2;a ++){
		Cell[a].Release();
		BackCell[a].Release();
	}
}

void eiWindow::Release(void)
{
	Delete();
}

//---フリップをする
void eiWindow::Flip(void)
{
	int a,page = 1;
	HDC hdc;
	eiCell *ec;

	//---スレッドチェック
	eiCheckThread();

	if(ShowFPSFlag)
		IncFPS();

	if((::eiSystem.ScreenMode & DIRECTDRAW_MODE) != 0){
		//---フリップ
#ifdef EIUSE_DIRECTDRAW
		eiSurface[0].Flip();
#endif
	} else {
		//---WinAPI
		page = 0;
		if(&Cell[page] == lpCell[0]){
			page = 1;
		}

		hdc = GetDC(hwnd);
		if(lpPalette){
			//---パレットがあるなら使う
			for(a = 0;a < lpPalette->PaletteNumber;a ++){
				Cell[page].dib.lpRGB[a].rgbRed = 
								lpPalette->Palette[a].peRed;
				Cell[page].dib.lpRGB[a].rgbGreen = 
								lpPalette->Palette[a].peGreen;
				Cell[page].dib.lpRGB[a].rgbBlue = 
								lpPalette->Palette[a].peBlue;
			}
		}
		Cell[page].dib.CopyToDC(hdc,0,0);
		ReleaseDC(hwnd,hdc);
		//---ポインタを入れ替え
		ec = lpCell[0];
		lpCell[0] = lpCell[1];
		lpCell[1] = ec;
	}
}

//---画面を更新
void eiWindow::Refresh(void)
{
	int a,page = 1;
	HDC hdc;

	if(ShowFPSFlag)
		IncFPS();

	if((::eiSystem.ScreenMode & DIRECTDRAW_MODE) != 0){
#ifdef EIUSE_DIRECTDRAW
		//---強制Blt
		eiSurface[0].Flip(1);
#endif
	} else {
		//---WinAPI
		page = 0;
		if(&Cell[page] == lpCell[0]){
			page = 1;
		}

		hdc = GetDC(hwnd);
		if(lpPalette){
			//---パレットがあるなら使う
			for(a = 0;a < lpPalette->PaletteNumber;a ++){
				Cell[page].dib.lpRGB[a].rgbRed = 
								lpPalette->Palette[a].peRed;
				Cell[page].dib.lpRGB[a].rgbGreen = 
								lpPalette->Palette[a].peGreen;
				Cell[page].dib.lpRGB[a].rgbBlue = 
								lpPalette->Palette[a].peBlue;
			}
		}
		Cell[page].dib.CopyToDC(hdc,0,0);
		ReleaseDC(hwnd,hdc);
	}
}

//---ＦＰＳを見せるかどうか表示
void eiWindow::ShowFPS(int flag)
{
	ShowFPSFlag = flag;
}

//---ＦＰＳ計算
void eiWindow::IncFPS(void)
{
	static eiTime let;
	static int fps,show_fps,prev_time;
	char s[20];
	int now;

	fps ++;
	now = let.GetTime();

	if(now - prev_time >= 1000){
		show_fps = fps;
		fps = 0;
		prev_time = now;
	}
	sprintf(s,"%3d",show_fps);
#ifdef EIUSE_DIRECTDRAW
	(eiGetSurfacePointer() + 1)->DrawFillBox(0,0,24,16,0);
	(eiGetSurfacePointer() + 1)->DDSurfaceTextDirect(s,0,0,0xffffff);
#endif
}

//---同期を取る
void eiWindow::WaitVSync(void)
{
	if((::eiSystem.ScreenMode & DIRECTDRAW_MODE) != 0){
#ifdef EIUSE_DIRECTDRAW
		//---強制Blt
		eiSurface[0].WaitVSync();
#endif
	} else {
		eiTime let;
		let.Delay(1);
	}
}

//---ウィンドウにパレットをセットする
int eiWindow::SetPalette(eiPalette *ep)
{
	if(!ep)
		return 0;

	lpPalette = ep;

	return 1;
}

//---セルをコピーする
void eiWindow::Copy(int src /*= 0*/)
{
	int dst = 1,x = 0,y = 0;
	RECT rect = {0,0,::eiSystem.xScreenSize,::eiSystem.yScreenSize};

	if(src == 1)
		dst = 0;

	if(src == 0){
		//---ウィンドウの左上
		rect.left += ::eiWindowRect.left;
		rect.right += ::eiWindowRect.left;
		rect.top += ::eiWindowRect.top;
		rect.right += ::eiWindowRect.right;
	}
	if(dst == 0){
		//---ウィンドウの左上
		x += ::eiWindowRect.left;
		y += ::eiWindowRect.top;
	}

	lpCell[src]->PutClip(lpCell[dst],x,y,&rect);
}

//---バックグラウンドへコピー
void eiWindow::CopyToBackground(int page /*= -1*/)
{
	int x = 0,y = 0;

	lpCell[1]->Put(lpBackCell[1],x,y);
}

//---バックグラウンドからコピー
void eiWindow::CopyFromBackground(int page /*= -1*/)
{
	int x = 0,y = 0;

	lpBackCell[1]->PutClip(lpCell[1],x,y);
}

void eiWindow::SetDrawScreenPrimaryCell(void)
{
	lpCell[0] = lpKeepCell[0];
	lpCell[1] = lpKeepCell[1];
}

void eiWindow::SetDrawScreenBackCell(void)
{
	lpCell[0] = lpBackCell[0];
	lpCell[1] = lpBackCell[1];
}

//---サイズを正しくセット
void eiSetWindowSize(HWND hwnd,int xs,int ys)
{
	RECT rect,rect2;
	int x,y;

	SetRect(&rect,0,0,xs,ys);
	AdjustWindowRectEx(&rect,
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
		GetMenu(hwnd) != NULL,
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX);
	SetWindowPos(hwnd,NULL,0,0,
		rect.right-rect.left,rect.bottom-rect.top,
		SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);

	GetWindowRect(hwnd,&rect2);
	x = rect2.left;
	y = rect2.top;
	rect2.right = rect2.right - rect2.left;
	rect2.bottom = rect2.bottom - rect2.top;

	GetClientRect(hwnd,&rect);

	rect.right = rect2.right + (xs-rect.right);
	rect.bottom = rect2.bottom + (ys-rect.bottom);

	MoveWindow(hwnd,x,y,rect.right,rect.bottom,TRUE);

}

//---クライアント領域のサイズ
void eiGetClient(HWND hwnd)
{
	POINT point;

	point.x = 0,point.y = 0;
	ClientToScreen(hwnd,&point);
	
	::eiWindowRect.left = point.x;
	::eiWindowRect.top = point.y;
}

//-------------------------------------------------------------
#ifdef EI_RUNWINDOWS
//
//---メッセージ処理関数
EI_API LRESULT CALLBACK eiDefaultWindowFunc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT paintst;

	switch(message){
	case WM_KEYDOWN:
		eiReadKey((int)wParam,lParam,1);		
		break;
	case WM_KEYUP:
		eiReadKey((int)wParam,lParam,0);
		break;
	
	case WM_SHOWWINDOW:
		//---ウィンドウのサイズ調整
		if((int)wParam == TRUE){
			if((int)lParam == 0){
			}
			eiSetWindowSize(hwnd,::eiSystem.xScreenSize,::eiSystem.yScreenSize);
			eiGetClient(hwnd);
		}
		break;
	case WM_ACTIVATE:
		if(LOWORD(wParam) != WA_INACTIVE){
		}
		break;
	case WM_MOUSEACTIVATE://アクティブウィンドウがこっちに来たとき
		if(hwnd != (HWND)wParam)
			break;
		return MA_ACTIVATE;
	case WM_PAINT:
		if((::eiSystem.ScreenMode & DIRECTDRAW_FULLSCREEN) != 0){
			//---空のペイント処理
			hdc = BeginPaint(hwnd,&paintst);
			EndPaint(hwnd,&paintst);
			break;
		} else {
			//---
			hdc = BeginPaint(hwnd,&paintst);
			EndPaint(hwnd,&paintst);
		}
		break;
	case WM_MOVE:
		eiGetClient(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd,message,wParam,lParam);
	}
	return 0;
}
#endif
//-------------------------------------------------------------
