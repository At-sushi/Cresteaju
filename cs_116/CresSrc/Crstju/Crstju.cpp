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

//---�������`�F�b�N�N���X
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

//---Windows�ϐ�-------------------------------------
#ifdef EI_RUNWINDOWS
	char TitleName[]="Cresteaju";
//	char szWinName[]="Cresteaju";

	HINSTANCE hThisInst,hPrevInst;
	ei_u32 hMainThread;
	HANDLE hTimerTh;
	DWORD math;
#endif /* EI_RUNWINDOWS */

//---�o�[�W����
CRESTEAJU_VERSION CresteajuVersion = 
{
	1,16,//xxx.xx
	0,0//�o�[�W���������̃A���t�@�x�b�g
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


//---�Q�[�����̕ϐ��E�f�[�^--------------
//---�ϐ�
	int CrDebug = 0;//---DebugMode
#if (CR_DATAMODE == 1)
	int CrFileMode = EI_NORMALFILE;
#else
	int CrFileMode = EI_LINKEDFILE;
#endif
	CRESTEAJU_EXEINFO CrExeInfo;
	CRESTEAJU_SYSTEM CrSystem;
//---���������
	CRESTEAJU_INITIALIZE InitializeInfo;
	CR_INIFILE IniFile;

//---�f�[�^
	CRESTEAJU_GAMEDATA GameUsingData;
	CrCharacter CharacterInfo[PLAYER_MAX];
	CRESTEAJU_GAMEINFO GameInfo;
	CRESTEAJU_PARTYINFO PartyInfo;

CrMemoryCheck _MemoryCheck4;

	CrItem ItemInfo[ITEMMATERIAL_MAX];
	CrMagic MagicInfo[MAGICMATERIAL_MAX];
	CrSpecial SpecialInfo[SPECIALMATERIAL_MAX];

CrMemoryCheck _MemoryCheck5;
	//---�G�f�[�^
	CRESTEAJU_BATTLECHARAINFO EnemyBattleInfo[ENEMY_MAX];
	CRESTEAJU_CHARACTERINFO EnemyCharacterInfo[ENEMY_MAX];

CrMemoryCheck _MemoryCheck6;

//---�E�B���h�E�����p
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


//---�_�~�[�R�[�h
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
		ShowError("�Q�d�N���͂ł��܂���B�R���t�B�O�ƃQ�[���𓯎��ɋN�����邱�Ƃ��ł��܂���");
		return 0;
	}

	//---StartUp
	if(!CresteajuInitStartUp()){
		ShowError("",eiGetLastError());
		ShowError("�������Ɏ��s���܂���(1)");
		return 0;
	}

	//---�n�r�ʏ��������
#ifdef EI_RUNWINDOWS
	int res = CresteajuInitForOS(crdataGetInitialize(),hThisInst,hPrevInst,lpszArgs,nWinMode);
	if(!res){
		ShowError("",eiGetLastError());
		ShowError("�������Ɏ��s���܂���(2)");
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

	//---CRESTEAJU�̃V�X�e����������
	if(!CresteajuInitSystem(*crdataGetInitialize())/**crdataGetCrSystem()*/ ){
		ShowError("",eiGetLastError(),ew->hwnd);
		ShowError("�������Ɏ��s���܂���(3)",-1,ew->hwnd);
		CresteajuEnd(0);
		return 0;
	}

//	ShowCursor(FALSE);

	//---�X���b�h�쐬
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

//-------------���b�Z�[�W���[�v
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
//---���C���X���b�h

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

	//---���̃X���b�h�͏I�����܂����I�I
	hMainThread = NULL;

	//---�I�����b�Z�[�W
	normal_end = 1;
	if(!win_close){
		win_close = 1;
		//---�I�����b�Z�[�W�𑗂�
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
//---�^��p

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
//---���b�Z�[�W����
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

	//---�ǂ̒��x�̌덷������̂��͓�E�E�E
	case WM_TIMER:
		if(wParam == ID_PLAYTIMER){
			//---�N������
			if(++CrExeInfo.ExeRunningTime >= 19999999){
				CrExeInfo.ExeRunningTime = 1999999999;
			}
			//---�v���C����
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
		//---�^�C�}�[
		SetTimer(hwnd,ID_PLAYTIMER,1000,NULL);
		return eiDefaultWindowFunc(hwnd,message,wParam,lParam);

	case WM_CLOSE:
		eiDebugWriteFile("\n*******WM_CLOSE...\n");

		win_close = 1;

		//---�I�����M
		eiSetEndThread();
		if(eiGetRunThreadFlag() == 1){
			Sleep(100);
		}
		//---�r������҂�
		eiWaitCriticalSection(3000);
		{
			eiTime let;
			let.Reset();

			//---�R�c�`�撆��������҂�
			while(ceid3d.NowDrawing3D && let.Get() < 2000){
				Sleep(10);
			}

			let.Reset();
			//---�X���b�h�I���܂ő҂�
			while(eiGetRunThreadFlag() && let.Get() < 2000){
				Sleep(10);
			}
			//---�X���b�h���I�����Ă���
			if(eiGetRunThreadFlag() == 0){
				hMainThread = NULL;
			}
		}

		//---�^�C�}�[�폜
		KillTimer(hwnd,ID_PLAYTIMER);

		//---�X���b�h���I���������ǂ����`�F�b�N
		if(::hMainThread != NULL){
			//---���C���X���b�h���~�߂�
			eiDebugWriteFile("SuspendThread() \n");
			SuspendThread((HANDLE)::hMainThread);
#ifdef USE_WINAPI_THREAD
#endif /* USE_WINAPI_THREAD */
		}
		//---����3D�`�撆�Ȃ炻��𒆒f
		ceid3d.End();
		if(::hMainThread != NULL){
			//---���C���X���b�h�I��
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
			//---�o�g�����Ȃ�o�g���I������
			crbatEndBattle(NULL,1);
		}

		//---DirectX��m�ۂ�����\�[�X�����
//		ShowWindow(hwnd,SW_HIDE);
		CresteajuEnd(0);

		eiDebugWriteFile("\n*******WM_CLOSE...\n");

		//---�E�B���h�E���폜����
		eiSleep(500);
		//---�^�X�N�o�[�Ɏc���Ȃ����߁E�E�E
		ShowWindow(hwnd,SW_HIDE);
		ShowWindow(hwnd,SW_RESTORE);
//		eiSleep(2500);

		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		eiDebugWriteFile("\n*******WM_DESTROY...\n");

		//---DirectX��m�ۂ�����\�[�X�����
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
