#ifndef EIWINDOW_H
#define EIWINDOW_H

//---ウィンドウ
class EI_API eiWindow
{
public:
	//---コンストラクタ
	eiWindow(void);
	~eiWindow();

	//---
	HWND Create(HINSTANCE hInst,LPCSTR TitleName,
		LRESULT CALLBACK WindowFunc(HWND,UINT,WPARAM,LPARAM),
		int use_ddraw);
	void Delete(void);
	void Release(void);
	int SetPalette(eiPalette *ep);

	//---転送制御
	void SetDrawScreenPrimaryCell(void);
	void SetDrawScreenBackCell(void);

	//---画面転送
	void Copy(int src = 0);
	void CopyToBackground(int page = -1);
	void CopyFromBackground(int page = -1);
	void Flip(void);
	void Refresh(void);
	void WaitVSync(void);
	void ShowFPS(int flag);
	void IncFPS(void);

	eiPalette *lpPalette;
	eiCell Cell[2],*lpCell[2],BackCell[2],*lpBackCell[2],*lpKeepCell[2];
	int ShowFPSFlag,FPS,DrawFPS;

//-------------------------------------------------------------
#ifdef EI_RUNWINDOWS
	HWND hwnd;
	HINSTANCE hThisInstance;
#endif
//-------------------------------------------------------------
	EIWINDOWSTYLE eiWS;
};

#endif /* EIWINDOW_H */
