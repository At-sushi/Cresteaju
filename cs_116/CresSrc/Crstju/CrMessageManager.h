#ifndef INCLUDE_CRMESSAGEMANAGER_H

#define INCLUDE_CRMESSAGEMANAGER_H

#define CRMM_SEEK_SCENE 1

#define MESM_MODE1

//---メッセージウィンドウ管理
class CRBASE_CLASS CrMesManager
{
public:
	CrMesManager(void);
	~CrMesManager();
	void Init(void);

	//---メッセージ操作
	int OpenMessage(eistr *name,int number,int window = 0,int pos = 0,int style = 0);
	int CloseMessage(int window = 0);
	void Paint(int window = 0);
	int ReadMessage(int line = 1,int window = 0,int mode = 0);
	void ReadMessageAll(int window = 0);
	int ReadDraw(int line = 1,int window = 0,int mode = 0);
	void FileMessage(eistr *name,int number,int scene = 1,int window = 0);
	void SeekScene(int scene,int window = 0);
	void Message(eistr *lpString,int window = 0);
	//---ウィンドウ操作
	int CreateNewMessage(int window = -1,int tx = -1,int ty = -1,int sx = -1,int sy = -1,int alpha = 0,int style = 0);
	int DeleteMessage(int window = 0);
	//---キー入力
	void WaitKey(int window = 0);

	void Draw(int frame = -1);

//	eiFile *file[CRMESMAN_WINDOWMAX];
#ifdef MESM_MODE1
	CrMessageWindow *lpWin[CRMESMAN_WINDOWMAX];
#else
	CrMessageWindow MesWin[CRMESMAN_WINDOWMAX];
#endif

	eiFile file[CRMESMAN_WINDOWMAX];
	ei_s32 TopAddres[CRMESMAN_WINDOWMAX];
private:
	int CreateFlag[CRMESMAN_WINDOWMAX];
	int EndMessage[CRMESMAN_WINDOWMAX];
};

#endif /*INCLUDE_CRMESSAGEMANAGER_H*/
