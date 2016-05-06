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
	//---�ϐ���������
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

//---�f�X�g���N�^
eiWindow::~eiWindow()
{
}

//---�E�B���h�E�����
HWND eiWindow::Create(HINSTANCE hInst,LPCSTR TitleName,
		LRESULT CALLBACK WindowFunc(HWND,UINT,WPARAM,LPARAM),int use_ddraw)
{
	int a;

	hThisInstance =  hInst;


	//---�E�B���h�E�N���X������������
	memset(&eiWS.WindowClass,0,sizeof(eiWS.WindowClass));
	
	eiWS.WindowClass.hInstance = hInst;
	eiWS.WindowClass.lpszClassName = eiWS.WindowName;

	if(::eiSystem.ScreenMode & DIRECTDRAW_FULLSCREEN){
		eiWS.Style = WS_POPUP;
	} else {
		eiWS.Style = WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX;
	}

	//---�^�C�g��
	eiWS.TitleName = TitleName;
	//---�T�C�Y
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

	//---�E�B���h�E�̃Z�������
	for(a = 0;a < 2;a ++){
		if(!Cell[a].Create(eiWS.xSize,eiWS.ySize,::eiSystem.ColorBit))
			return NULL;
		lpCell[a] = &Cell[a];
		if(use_ddraw){
			Cell[a].dib.Delete();
		}
	}
	//---�ۑ��p�Z�������
	for(a = 0;a < 2;a ++){
		if(!BackCell[a].Create(eiWS.xSize,eiWS.ySize,::eiSystem.ColorBit))
			return NULL;
		lpBackCell[a] = &BackCell[a];
		if(use_ddraw){
			BackCell[a].dib.Delete();
		}
	}

	//---�E�B���h�E�N���X��o�^
	if(!RegisterClassEx(&eiWS.WindowClass)){
		return NULL;
	}

	//---�E�B���h�E���쐬
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
		//---�E�B���h�E���쐬����Ă���΁A�\���A�X�V������
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

//---�t���b�v������
void eiWindow::Flip(void)
{
	int a,page = 1;
	HDC hdc;
	eiCell *ec;

	//---�X���b�h�`�F�b�N
	eiCheckThread();

	if(ShowFPSFlag)
		IncFPS();

	if((::eiSystem.ScreenMode & DIRECTDRAW_MODE) != 0){
		//---�t���b�v
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
			//---�p���b�g������Ȃ�g��
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
		//---�|�C���^�����ւ�
		ec = lpCell[0];
		lpCell[0] = lpCell[1];
		lpCell[1] = ec;
	}
}

//---��ʂ��X�V
void eiWindow::Refresh(void)
{
	int a,page = 1;
	HDC hdc;

	if(ShowFPSFlag)
		IncFPS();

	if((::eiSystem.ScreenMode & DIRECTDRAW_MODE) != 0){
#ifdef EIUSE_DIRECTDRAW
		//---����Blt
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
			//---�p���b�g������Ȃ�g��
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

//---�e�o�r�������邩�ǂ����\��
void eiWindow::ShowFPS(int flag)
{
	ShowFPSFlag = flag;
}

//---�e�o�r�v�Z
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

//---���������
void eiWindow::WaitVSync(void)
{
	if((::eiSystem.ScreenMode & DIRECTDRAW_MODE) != 0){
#ifdef EIUSE_DIRECTDRAW
		//---����Blt
		eiSurface[0].WaitVSync();
#endif
	} else {
		eiTime let;
		let.Delay(1);
	}
}

//---�E�B���h�E�Ƀp���b�g���Z�b�g����
int eiWindow::SetPalette(eiPalette *ep)
{
	if(!ep)
		return 0;

	lpPalette = ep;

	return 1;
}

//---�Z�����R�s�[����
void eiWindow::Copy(int src /*= 0*/)
{
	int dst = 1,x = 0,y = 0;
	RECT rect = {0,0,::eiSystem.xScreenSize,::eiSystem.yScreenSize};

	if(src == 1)
		dst = 0;

	if(src == 0){
		//---�E�B���h�E�̍���
		rect.left += ::eiWindowRect.left;
		rect.right += ::eiWindowRect.left;
		rect.top += ::eiWindowRect.top;
		rect.right += ::eiWindowRect.right;
	}
	if(dst == 0){
		//---�E�B���h�E�̍���
		x += ::eiWindowRect.left;
		y += ::eiWindowRect.top;
	}

	lpCell[src]->PutClip(lpCell[dst],x,y,&rect);
}

//---�o�b�N�O���E���h�փR�s�[
void eiWindow::CopyToBackground(int page /*= -1*/)
{
	int x = 0,y = 0;

	lpCell[1]->Put(lpBackCell[1],x,y);
}

//---�o�b�N�O���E���h����R�s�[
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

//---�T�C�Y�𐳂����Z�b�g
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

//---�N���C�A���g�̈�̃T�C�Y
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
//---���b�Z�[�W�����֐�
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
		//---�E�B���h�E�̃T�C�Y����
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
	case WM_MOUSEACTIVATE://�A�N�e�B�u�E�B���h�E���������ɗ����Ƃ�
		if(hwnd != (HWND)wParam)
			break;
		return MA_ACTIVATE;
	case WM_PAINT:
		if((::eiSystem.ScreenMode & DIRECTDRAW_FULLSCREEN) != 0){
			//---��̃y�C���g����
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
