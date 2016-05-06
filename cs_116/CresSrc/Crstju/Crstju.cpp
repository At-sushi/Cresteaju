/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   Crstju.cpp ...CRESTEAJU entry point

-----------------------------------------------------------*/

#include "CrPch.h"
#include "resource.h"

#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CRSTJU

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#include "CrBase.h"
#include "CrBattle.h"

#define ID_PLAYTIMER 0x01
#define ID_MOVIETIMER 0x02

#ifdef EI_RUNWINDOWS
	LRESULT CALLBACK WindowFunc(HWND,UINT,WPARAM,LPARAM);
	BOOL CALLBACK DLGFunc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam);
	BOOL CALLBACK JukeFunc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam);
	BOOL CALLBACK JukeAboutFunc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam);
	#ifdef USE_WINAPI_THREAD
		DWORD MainThread(LPVOID param);
	#else
		void MainThread(void *pParam);
	#endif /* USE_WINAPI_THREAD */
#endif /* EI_RUNWINDOWS */

//---Extern Function
extern int CresteajuMain(void);

//---メモリチェッククラス
class CrMemoryCheck
{
	int test;
public:
	CrMemoryCheck(void)
	{
		test = 1;
	};

	~CrMemoryCheck()
	{
		if(test != 1){
			eiDebugWriteFile("***Memory was broken!!***\n");
		}
	};
};

CrMemoryCheck _MemoryCheck1;

//---Windows変数-------------------------------------
#ifdef EI_RUNWINDOWS
	char TitleName[]="Cresteaju";
//	char szWinName[]="Cresteaju";

	HINSTANCE hThisInst,hPrevInst;
	ei_u32 hMainThread;
	HANDLE hTimerTh;
	DWORD math;
#endif /* EI_RUNWINDOWS */

//---バージョン
CRESTEAJU_VERSION CresteajuVersion = 
{
	1,16,//xxx.xx
	0,0//バージョン末尾のアルファベット
};

CrMemoryCheck _MemoryCheck2;
//---------------------------------------
	//---eiLibrary Class---------
	eiWindow cew;
	eiCell cCell[2000];
CrMemoryCheck _MemoryCheck3;
	eiPalette cep;
	eiTime cet;
	eiInput cei;
	eiSound Sound[CRSOUND_SOUNDMAX];

	//---eiField Class-----------
	eiField cef[4];
	eiMap cem;

	//---3d
	eiD3D ceid3d;
	eiD3DMatrix cmatWorld,cmatView,cmatProjection;
	eiD3DViewport cViewport;
	eiD3DMaterial cBaseMaterial;


//---ゲーム内の変数・データ--------------
//---変数
	int CrDebug = 0;//---DebugMode
#if (CR_DATAMODE == 1)
	int CrFileMode = EI_NORMALFILE;
#else
	int CrFileMode = EI_LINKEDFILE;
#endif
	CRESTEAJU_EXEINFO CrExeInfo;
	CRESTEAJU_SYSTEM CrSystem;
//---初期化情報
	CRESTEAJU_INITIALIZE InitializeInfo;
	CR_INIFILE IniFile;

//---データ
	CRESTEAJU_GAMEDATA GameUsingData;
	CrCharacter CharacterInfo[PLAYER_MAX];
	CRESTEAJU_GAMEINFO GameInfo;
	CRESTEAJU_PARTYINFO PartyInfo;

CrMemoryCheck _MemoryCheck4;

	CrItem ItemInfo[ITEMMATERIAL_MAX];
	CrMagic MagicInfo[MAGICMATERIAL_MAX];
	CrSpecial SpecialInfo[SPECIALMATERIAL_MAX];

CrMemoryCheck _MemoryCheck5;
	//---敵データ
	CRESTEAJU_BATTLECHARAINFO EnemyBattleInfo[ENEMY_MAX];
	CRESTEAJU_CHARACTERINFO EnemyCharacterInfo[ENEMY_MAX];

CrMemoryCheck _MemoryCheck6;

//---ウィンドウ処理用
static int win_close = 0,normal_end = 0;


//---game info
#define CR_GAMEINFO_POINTER
#include "CrGameInfo.h"


//---------------------------------------
#if (CR_DEBUG == 1)
	#include "CrDebug.cpp"
#endif

//---------------------------------------

CrMemoryCheck _MemoryCheck7;

//---Initialize
int CresteajuEnd(int src);
int CresteajuInitStartUp(void);
#ifdef EI_RUNWINDOWS
int CresteajuInitForOS(CRESTEAJU_INITIALIZE *pInit,
		HINSTANCE hThisInst,HINSTANCE hPrevInst,
		LPSTR lpszArgs,int nWinMode);
int CresteajuInitSystem(CRESTEAJU_INITIALIZE init);
#endif /* EI_RUNWINDOWS */

//---------------------------------------
#include "CrError.cpp"
#include "CrInit.cpp"
#include "CrDlg.cpp"
#include "CrJuke.cpp"
//---------------------------------------


//---ダミーコード
int DumyMainCode(void)
{
	static int count = 0;

	if(++count >= 1000){
		Sleep(10);
		return 0;
	}
	return 1;
}

#ifdef EI_RUNWINDOWS


//---WinMain--------------------------------------
int WINAPI WinMain(HINSTANCE hThisInst,HINSTANCE hPrevInst,LPSTR lpszArgs,int nWinMode)
#endif /* EI_RUNWINDOWS */
{
	int ret;

	//---Lock
	if(!crbaseLockCresteaju()){
		ShowError("２重起動はできません。コンフィグとゲームを同時に起動することもできません");
		return 0;
	}

	//---StartUp
	if(!CresteajuInitStartUp()){
		ShowError("",eiGetLastError());
		ShowError("初期化に失敗しました(1)");
		return 0;
	}

	//---ＯＳ別初期化作業
#ifdef EI_RUNWINDOWS
	int res = CresteajuInitForOS(crdataGetInitialize(),hThisInst,hPrevInst,lpszArgs,nWinMode);
	if(!res){
		ShowError("",eiGetLastError());
		ShowError("初期化に失敗しました(2)");
		return 0;
	} else if(res == 2){
		//---Config
		memset(crdataGetIniFile(),0,sizeof(CR_INIFILE));
		CresteajuSetDefaultINIFile(crdataGetIniFile());
		CresteajuReadINIFile(crdataGetIniFile());

		int check = DialogBox( hThisInst,"CFG",NULL,(DLGPROC)DLGFunc);
		if(check == 1){
			CresteajuWriteINIFile(crdataGetIniFile());
		}

		return 0;
	} else if(res == 3){
		//---Juke
		return Juke();
	}
#endif /* EI_RUNWINDOWS */

	//---CRESTEAJUのシステムを初期化
	if(!CresteajuInitSystem(*crdataGetInitialize())/**crdataGetCrSystem()*/ ){
		ShowError("",eiGetLastError(),ew->hwnd);
		ShowError("初期化に失敗しました(3)",-1,ew->hwnd);
		CresteajuEnd(0);
		return 0;
	}

//	ShowCursor(FALSE);

	//---スレッド作成
#ifdef EI_RUNWINDOWS
	#ifdef USE_WINAPI_THREAD
		::hMainThread = CreateThread(NULL,0,
			(LPTHREAD_START_ROUTINE)MainThread,0,0,&math);
	#else
		::hMainThread = _beginthread(MainThread,0,NULL);
	#endif /* USE_WINAPI_THREAD */

	{
		char s[80];
		sprintf(s,"thread handle:%x\n",hMainThread);
		eiDebugWriteFile(s);
	}

//-------------メッセージループ
	ret = eiMessageLoop(ew);
//-------------

#endif /* EI_RUNWINDOWS */
	eiDebugWriteFile("\n*******after eiMessageLoop()...\n");

	CresteajuEnd(1);
	ew->Release();

	eiSleep(100);

	eiDebugWriteFile("(WinMain)End WinMain\n");

	//---Unlock
	crbaseUnlockCresteaju();

	return ret;
}

//---------------------------------------------
//---メインスレッド

#ifdef EI_RUNWINDOWS
	#ifdef USE_WINAPI_THREAD
		DWORD MainThread(LPVOID param)
	#else
		void MainThread(void *pParam)
	#endif /* USE_WINAPI_THREAD */
#endif /* EI_RUNWINDOWS */
{	
	eiInitRnd();

	while(!eiGetCanDoDraw()){
		eiSleep(10);
	}
	eiDebugWriteFile("---------------Start MainThread---------------\n");

	CresteajuMain();

	eiDebugWriteFile("---------------End MainThread---------------\n");
#ifdef EI_RUNWINDOWS
	eiWaitCriticalSection(3000);

	//---このスレッドは終了しました！！
	hMainThread = NULL;

	//---終了メッセージ
	normal_end = 1;
	if(!win_close){
		win_close = 1;
		//---終了メッセージを送る
		PostMessage(ew->hwnd,WM_CLOSE,0,0);
	}

	eiReleaseCriticalSection();
#endif /* EI_RUNWINDOWS */

#ifdef USE_WINAPI_THREAD
		return 39492000;
#else

	eiDebugWriteFile("_endthread()\n");
	eiSetRunThreadFlag(0);
	_endthread();
#endif /* USE_WINAPI_THREAD */
}

//---------------------------------------
//---録画用

int MovieRec = 0,MovieRecNumber = 0;
int MovieXSize = 192,MovieYSize = 144;
eiDDSurface mrSurface;
eiDib mrDib;

void crReadyMovieRec(void)
{
	mrSurface.Create(MovieXSize,MovieYSize,0);//ESCREATE_SYSTEMMEMORY);
	mrDib.Create(MovieXSize,MovieYSize,24);
	MovieRecNumber = 0;

	eiDebugWriteFile("Rec Start\n");
	SetTimer(ew->hwnd,ID_MOVIETIMER,100,NULL);
}

void crFinishMovieRec(void)
{
	KillTimer(ew->hwnd,ID_MOVIETIMER);

	mrDib.Delete();
	mrSurface.Release();

	eiDebugWriteFile("Rec End\n");
}

void crDoMovieRec(void)
{
	RECT rect = {0,0,MovieXSize,MovieYSize},rect2 = {0,0,640,480};
	int x,y,line,bm_line;
	int pitch;
	ei_u8 *pMemory;
	ei_u16 data,r,g,b;

	while(!crdataIsEnableRec()){
		eiSleep(1);
	}
//	(eiGetSurfacePointer() + 1)->PutExtend(&mrSurface,0,0,&rect,DDBLT_WAIT,0.5,0.5);
	mrSurface.lpSurface->Blt(&rect,(eiGetSurfacePointer() + 1)->lpSurface,
		&rect2,DDBLT_WAIT,NULL);

//	(eiGetSurfacePointer() + 1)->lpSurface->Blt(&rect2,mrSurface.lpSurface,
//		&rect,DDBLT_WAIT,NULL);

	mrSurface.Lock(&pMemory,&pitch);

	for(y = 0;y < MovieYSize;y ++){
		line = y * pitch;
		bm_line = mrDib.GetAddres(0,y);
		for(x = 0;x < MovieXSize;x ++){
			data = *(ei_u16 *)(pMemory + line + (x * 2));
			r = (data >> 11) & 0x1f;
			g = (data >> 5) & 0x3f;
			b = (data >> 0) & 0x1f;

			*(ei_u8 *)(mrDib.lpBitmap + bm_line + (x * 3) + 0) = (ei_u8)(b << 3);
			*(ei_u8 *)(mrDib.lpBitmap + bm_line + (x * 3) + 1) = (ei_u8)(g << 2);
			*(ei_u8 *)(mrDib.lpBitmap + bm_line + (x * 3) + 2) = (ei_u8)(r << 3);
		}
	}

	mrSurface.UnLock();

	eistr name[80];
	sprintf(name,"movie\\bm%04d.bmp",MovieRecNumber++);
	mrDib.Save(name);
}

#ifdef EI_RUNWINDOWS
//---メッセージ処理
LRESULT CALLBACK WindowFunc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	int mode;
	static int sleep_flag = 0;

	switch(message){
	case WM_ACTIVATEAPP:
		if((BOOL)wParam == FALSE && !win_close && !normal_end
			&& eiGetFullScreen() == 1){
			win_close = 1;
			PostMessage(hwnd,WM_CLOSE,0,0);
		}
		break;

	case WM_ACTIVATE:
		if(LOWORD(wParam) == WA_INACTIVE){
			sleep_flag = 1;
			ei->EnableInput(0);
//			SuspendThread((HANDLE)::hMainThread);
//			eiDebugWriteFile("suspend\n");
		} else {
			ei->EnableInput(1);
			if(sleep_flag){
				{
					CrInput ci;
					ci.Get();
				}
//				ResumeThread((HANDLE)::hMainThread);
//				eiDebugWriteFile("resume\n");
			}
			sleep_flag = 0;
		}
		break;

	//---どの程度の誤差があるのかは謎・・・
	case WM_TIMER:
		if(wParam == ID_PLAYTIMER){
			//---起動時間
			if(++CrExeInfo.ExeRunningTime >= 19999999){
				CrExeInfo.ExeRunningTime = 1999999999;
			}
			//---プレイ時間
			if(++GameInfo.PlayAllSecond >= 1999999999){
				GameInfo.PlayAllSecond = 1999999999;
			}
			if(++GameInfo.PlaySeconds >= 60){
				GameInfo.PlaySeconds = 0;
				if(++GameInfo.PlayMinutes >= 60){
					GameInfo.PlayMinutes = 0;
					if(++GameInfo.PlayHours > 999){
						GameInfo.PlayHours = 999;
					}
				}
			}
		} else if(wParam == ID_MOVIETIMER){
			crDoMovieRec();
		}
		break;

	case WM_KEYDOWN:
/*		if(crdataGetDebug()){
			if((int)wParam == VK_F1 && !MovieRec){
				MovieRec = 1;
				crReadyMovieRec();
			} else if((int)wParam == VK_F2 && MovieRec){
				MovieRec = 0;
				crFinishMovieRec();
			}
		}*/

		mode = crsysGetCodeMode();
		if((int)wParam == VK_F9
			&& (mode != CODE_INITIALIZE && mode != CODE_END)
			&& !win_close){
			win_close = 1;
			crmusicStop();
			PostMessage(hwnd,WM_CLOSE,0,0);
		} else {
			return eiDefaultWindowFunc(hwnd,message,wParam,lParam);
		}

		break;

	case WM_CREATE:
		//---タイマー
		SetTimer(hwnd,ID_PLAYTIMER,1000,NULL);
		return eiDefaultWindowFunc(hwnd,message,wParam,lParam);

	case WM_CLOSE:
		eiDebugWriteFile("\n*******WM_CLOSE...\n");

		win_close = 1;

		//---終了送信
		eiSetEndThread();
		if(eiGetRunThreadFlag() == 1){
			Sleep(100);
		}
		//---排他制御待ち
		eiWaitCriticalSection(3000);
		{
			eiTime let;
			let.Reset();

			//---３Ｄ描画中だったら待つ
			while(ceid3d.NowDrawing3D && let.Get() < 2000){
				Sleep(10);
			}

			let.Reset();
			//---スレッド終了まで待つ
			while(eiGetRunThreadFlag() && let.Get() < 2000){
				Sleep(10);
			}
			//---スレッドが終了してたら
			if(eiGetRunThreadFlag() == 0){
				hMainThread = NULL;
			}
		}

		//---タイマー削除
		KillTimer(hwnd,ID_PLAYTIMER);

		//---スレッドが終了したかどうかチェック
		if(::hMainThread != NULL){
			//---メインスレッドを止める
			eiDebugWriteFile("SuspendThread() \n");
			SuspendThread((HANDLE)::hMainThread);
#ifdef USE_WINAPI_THREAD
#endif /* USE_WINAPI_THREAD */
		}
		//---もし3D描画中ならそれを中断
		ceid3d.End();
		if(::hMainThread != NULL){
			//---メインスレッド終了
			eiDebugWriteFile("TerminateThread() \n");
			eiEnableCheckThread(0);
			eiSetRunThreadFlag(0);
			TerminateThread((HANDLE)::hMainThread,0);
#ifdef USE_WINAPI_THREAD
#endif /* USE_WINAPI_THREAD */
			hMainThread = NULL;
		}

		eiReleaseCriticalSection();

		if(crsysGetCodeMode() == CODE_BATTLE){
			//---バトル中ならバトル終了処理
			crbatEndBattle(NULL,1);
		}

		//---DirectXや確保したりソースを解放
//		ShowWindow(hwnd,SW_HIDE);
		CresteajuEnd(0);

		eiDebugWriteFile("\n*******WM_CLOSE...\n");

		//---ウィンドウを削除する
		eiSleep(500);
		//---タスクバーに残さないため・・・
		ShowWindow(hwnd,SW_HIDE);
		ShowWindow(hwnd,SW_RESTORE);
//		eiSleep(2500);

		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		eiDebugWriteFile("\n*******WM_DESTROY...\n");

		//---DirectXや確保したりソースを解放
//		CresteajuEnd(0);

		PostQuitMessage(0);

		eiDebugWriteFile("\n*******WM_DESTROY...\n");
		break;

	default:
		return eiDefaultWindowFunc(hwnd,message,wParam,lParam);
	}

	return 0;
}

#endif /* EI_RUNWINDOWS */
