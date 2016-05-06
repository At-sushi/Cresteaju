#ifndef INCLUDE_CRWINDOW_H

#define INCLUDE_CRWINDOW_H

//---Size
#define CRWIN_BASESIZE 16
#define CRWIN_FRAMESIZE 8
#define CRWIN_BORDERSIZE 2

#define CRWIN_BGFILL 0x0001 //---塗りつぶし
#define CRWIN_BGPATTERN 0x0002 //---パターン配置
#define CRWIN_BGALPHA 0x0010 //---半透明
#define CRWIN_BGGRADATION 0x0020 //---グラデーション
#define CRWIN_FRAME 0x0040 //---フレーム有り
#define CRWIN_DEFAULT 0x1000 //---標準ウィンドウ
#define CRWIN_CHANGEPAGE 0x2000 //---ページ切り替え可能なウィンドウ
#define CRWIN_BLACK 0x4000 //---真っ黒ウィンドウ


#define CRWIN_PALETTEGRADATION 32

#define CRWIN_TYPE_NORMAL 0
#define CRWIN_TYPE_GRAY 1
#define CRWIN_TYPE_RED 2

//---MessageWindow
#define CRWIN_MESSAGE_BUFFERSIZE 512

//---StringWindow
#define CRWIN_STRING_CURRENTPOS -1

//---SelectWindow
#define CRWIN_SELECT_HSPACE 16
#define CRWIN_SELECT_HEMPTY 16
#define CRWIN_SELECT_VERTOFFSET 16
#define CRWIN_SELECT_CURSORANIMEMAX 12
//---コールバック関数メッセージ
#define CRWIN_SELECT_MESMOVECURSOR 1 //---カーソルが動いた
#define CRWIN_SELECT_MESCHANGEPAGE 2 //---ページ切り替え
#define CRWIN_SELECT_MESSHOWHELP 3 //---ヘルプ表示
#define CRWIN_SELECT_MESPAINT 4 //---ペイント
#define CRWIN_SELECT_IDLE 5 //---アイドリング

//---MessageManager
#define CRMESMAN_WINDOWMAX 4

//---空のウィンドウ
class CRBASE_CLASS CrEmptyWindow
{
public:
	CrEmptyWindow(int style = CRWIN_DEFAULT,int ptn = 0,int alpha = 191);
	~CrEmptyWindow();

	void TestWindow(void);

	virtual int Create(int tx ,int ty,int sx,int sy);
	void Release(void);
	void SetType(int type);
	void SetStyle(int style);
	int GetStyle(void);
	void SetAlpha(int alpha);
	int GetDrawPage(void);
	void Refresh(void);
	void DrawFrame(void);
	void DrawBackground(void);
	void RestoreFromBackgroundCell(void);
	virtual void Paint(void);
	void WaitKey(int n = -1);

	int xGetTop(void);
	int yGetTop(void);

	void SetData(ei_u32 data);
	ei_u32 GetData(void);

	void SetPaintCallBack(void (*lpFunc)(eiCell *));

	ei_s32 GetPosX(void);
	ei_s32 GetPosY(void);
protected:
	EIPOINT Top,Size,Client;
	int CreateFlag;
	void (*lpPaintFunc)(eiCell *);
	RECT WindowRect;
	int Style,Alpha,Pattern;//---Alpha=0で完全透明
	ei_u32 Data;
	int WindowType;

	static int DefaultStyle;
};

//---文字表示ウィンドウ
class CRBASE_CLASS CrStringWindow : public CrEmptyWindow
{
public:
	CrStringWindow(int font = EINORMAL_FONT,
		int style = CRWIN_DEFAULT | CRWIN_CHANGEPAGE,int ptn = 0,int alpha = 191);
	~CrStringWindow();

	int Create(int tx,int ty,int sx,int sy);
	void Paint(void);
	void DrawText(lpeistr lpString,
		int sx = CRWIN_STRING_CURRENTPOS,int sy = CRWIN_STRING_CURRENTPOS,
		int col = -1);
	void DrawText(int col,lpeistr lpString,
		int sx = CRWIN_STRING_CURRENTPOS,int sy = CRWIN_STRING_CURRENTPOS);
	void SetOffset(int x,int y);

	void Reset(void);
	void AddWord(int n = 1);
	void AddLine(int n = 1);
	void AddReturn(int n = 1);
	int xGetCurrentPos(void);
	int yGetCurrentPos(void);

	int SetColor(int col);
	int SetLineSize(int size);

	void DrawLastString(void);
protected:
	int x,y,Page,Width,Height,LineSize,xSize,ySize,Color;
	int Font,xOffset,yOffset;
	eistr *pLastString;
};

//---メッセージウィンドウ
class CRBASE_CLASS CrMessageWindow : public CrStringWindow
{
public:
	CrMessageWindow(int font = EINORMAL_FONT,
		int style = CRWIN_DEFAULT,int ptn = 0,int alpha = 191);
	~CrMessageWindow();

	int Create(int tx = -1,int ty = -1,int sx = -1,int sy = -1);
	//---メッセージ
	void Message(lpeistr lpString);
	int Draw(int frame = -1,int wait = 1,int refresh = 1);
	//---バッファー操作
	void WriteBuffer(eistr **message);
	int ReadBuffer(eistr *message,int *size);
	void Clear(void);
	void ResetReadBuffer(void);
	void ResetWriteBuffer(void);
	void ResetPos(void);
	//---
	int CalcWaitKeyCursorPosX(void);
	int CalcWaitKeyCursorPosY(void);
	void KeepWaitKeyCursor(void);
	void RestoreWaitKeyCursor(void);
	void WaitKey(void);

	void SetWaitMode(int mode);
	int GetWaitMode(void);
	void Call_CallBack(void);

protected:
	eistr MessageBuffer[CRWIN_MESSAGE_BUFFERSIZE];
	eistr *lpReadBuffer,*lpWriteBuffer;
	int CurrentColor,CurrentFont;
	int ResetFlag,WaitMode;
};

//---選択ウィンドウ
class CRBASE_CLASS CrSelectWindow : public CrStringWindow
{
public:
	CrSelectWindow(int font = EINORMAL_FONT,
		int style = CRWIN_DEFAULT,int ptn = 0,int alpha = 191);
	~CrSelectWindow();

	int Create(int tx,int ty,int sx,int sy,
		eistr *title ,eistr *string,int horizon = 1,int h_size = 0);
	void SetMenuString(eistr *string);
	void DrawMenu(void);
	void Paint(void);
	//---選択
	int Select(CRWIN_SELECTINFO *pInfo = NULL);
	void EraseSelectIndex(int index);
	void DrawSelectIndex(int index);
	//---カーソルアニメ
	int xGetCursor(int index);
	int yGetCursor(int index);
	void SaveCursorBG(int index);
	void LoadCursorBG(int index);
	void DrawCursor(int index);
	int AnimeCursor(eiTime *let);

	//---コールバック
	int SetSelectCallBack(int (*lpFunc)(CrSelectWindow *,eiCell *,int,ei_u32,ei_u32,int));
	int SetDrawTextCallBack(void (*lpFunc)(eiCell *,eistr *,int ,int ,int ,ei_u32));

protected:
	int MenuCount,Horizon,HorizonSize,
		CursorNumber,AnimeNumber,AnimeWait,SaveBGNumber;
	eistr *lpMenuString,*lpMenuTitle;
	//---
	void (*lpDrawTextCallBack)(eiCell *,eistr *,int ,int ,int ,ei_u32);//x,y,col,mode
	int (*lpSelectCallBack)(CrSelectWindow *,eiCell *,int,ei_u32,ei_u32,int);//message,param(index,case...)
};

//---スタックウィンドウ
class CRBASE_CLASS CrStackWindow : public CrSelectWindow
{
public:
	CrStackWindow(int font = EINORMAL_FONT,int style = CRWIN_DEFAULT ,int ptn = 0,int alpha = 191);
	~CrStackWindow();

	int Create(int tx,int ty,int sx,int sy,int vpos,
		eistr *title ,eistr *string,int horizon = 1,int h_size = 0);
	void Paint(void);
	void CreateMenu(eistr *pstr,int mode,int stack_size = 0); 
	int Select(ei_s32 *pInTable,ei_s32 *pOutTable,CRWIN_SELECTINFO *pInfo = NULL);
protected:
	ei_s32 VPos,MenuFlag[16],Stack[16];
	eistr *pStackStart,*pMenuStart[16],MenuString[256],EndString[256];
};

//---数字入力ウィンドウ
class CRBASE_CLASS CrDigitWindow : public CrStringWindow
{
public:
	CrDigitWindow(int style = CRWIN_DEFAULT ,int ptn = 0,int alpha = 191);
	~CrDigitWindow();

	int Create(int tx,int ty,int sx,int sy,eistr *phelp = NULL,int limit = 4);
	void Paint(void);

	void Draw(void);
	void SetRange(ei_s32 low,ei_s32 high);
	int GetDigit(int def_digit,int def_pos = 0);
protected:
	void SetCounter(int digit);
	int GetCounter(void);

	ei_s32 DefaultDigit,Limit,Counter[12],Pos;
	ei_s32 Low,High;
	eistr *pHelpString;
};

#endif /*INCLUDE_CRWINDOW_H*/
