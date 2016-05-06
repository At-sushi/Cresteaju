//---CRESTEAJU With SMIDI

#include "CrPch.h"
//#define MODE_DLL 1
//#define EILIBRARY_DLL 1

#include "..\..\..\eiDef.h"
#include "..\..\..\eiClass.h"
#include "..\..\..\eiLib.h"

#include "..\..\SMidiDef.h"

//-------version
WORD smidiVersion = (0 << 8) | (53);//0.53

//------------
HANDLE hsmidiThread;

int PlayMode = SMIDI_LOOPPLAY;
UINT MidiTimerID = 0 , InitFlag = 0 , ThreadFlag = 0;
HWND hUser;
LPSMIDI_STREAM lpsmidiActiveStream = NULL;
int TimerCount = 1 , FadeSpeed = 1 , VolumeFade = 0 , FadeCount = 0,
	FadeLimitVolume = 0;
DWORD ThreadID = 0x2214649;
int smidiMessage = 0 , SendMasterVolume = 0, SendAllControl = 0; 

BYTE MasterVolumeExclusive[20]={
	//--8
	0xf0,0x41,0x10,0x42,0x12,
	0x40,0x00,0x04},

	//--8
	EFXOn[16]={
	0xf0,0x41,0x10,0x42,0x12,
	0x40,0x00,0x22,
	},
	EFXType[16]={
	0xf0,0x41,0x10,0x42,0x12,
	0x40,0x03,0x00,
	},
	//--8
	EFXParam[16]={
	0xf0,0x41,0x10,0x42,0x12,
	0x40,0x03,0x00,
	}

;

BYTE SendMasterVolumeExclusive[20];

//ショートイベントのサイズ
BYTE StatusSize[] = {0,0,0,0, 0,0,0,0, 2,2,2,2, 1,1,2,0};

//----debug
int count=0,test1=0,test2,test3;

DWORD GetValData(BYTE **p);
DWORD GetValData2(BYTE *p, int *a);
DWORD LongByte(BYTE *p);
WORD ShortByte(BYTE *p);

SMIDI_TRACKINFO LastTrackData[SMIDI_TRACK_MAX];

#define smidiCheckPointer(x) \
	if(!x)\
		return SMIDI_ER_SOMETHING;\
	if(!x->lpMidiData)\
		return SMIDI_ER_SOMETHING;

#define SMIDITHREAD 1
#define _SMIDI_DLL_ 1

#ifdef MAKE_DLL
	#define SMIDIFUNC __declspec(dllexport)
#else
	#define SMIDIFUNC
#endif /* MAKE_DLL */

DWORD smidiThread(LPVOID param);
void smidiTimeCheck(void);
SMIDIFUNC int smidiStop(LPSMIDI_STREAM lpsmidi);

eiTime smidiet;

#include "smStream.cpp"
#include "smMsg.cpp"
#include "smPlay.cpp"
#include "smExtd.cpp"

//---セマフォ
HANDLE hsmidiSemaphore;

void smidiDLL_PROCESS_ATTACH(void)
{
	DWORD math = ThreadID;

	hsmidiThread = CreateThread(NULL,0,
		(LPTHREAD_START_ROUTINE)smidiThread,0,
		CREATE_NEW_PROCESS_GROUP,&math);
}

void smidiDLL_PROCESS_DETACH(void)
{
	ThreadFlag = 0;
	TerminateThread(hsmidiThread,0);
}

void smidiTimeCheck(void)
{
	int a,b;
	static int KeepTime = -1;

	if(KeepTime == -1)
		KeepTime = GetTickCount();

	a = GetTickCount();
	b = a - KeepTime;

	if(b >= TimerCount){
		//割り込み間隔だけ時間が過ぎていたら
		MidiTimerProc(b);
		KeepTime = a;
	}
}

DWORD smidiThread(LPVOID param)
{
	//割り込みスタート
	ThreadFlag = 1;
	SetThreadPriority(GetCurrentThread(),THREAD_PRIORITY_HIGHEST);
	//SetThreadPriority(GetCurrentThread(),THREAD_PRIORITY_LOWEST);

	while(ThreadFlag){
		Sleep(TimerCount);

		smidiTimeCheck();
	}

	return 1;
}

int smidiCall(void)
{

	return 1;
}

//---初期化
SMIDIFUNC int smidiInit(HWND hwnd,int count)
{
	TIMECAPS TimeCap;
	DWORD math = ThreadID;
//	MMRESULT result;

//	if(hUser)
//		return SMIDI_ER_ALREADYUSED;

	if(InitFlag)
		return SMIDI_NOERROR;

	//タイマーの性能をチェック
	timeGetDevCaps(&TimeCap,sizeof(TimeCap));
	TimerCount = TimeCap.wPeriodMin;
	if(count <= 0)
		count = 1;
	if(count >= TimerCount)
		TimerCount = count;

	StreamInit();

	//割り込みスタート
//	MidiTimerID=result=timeSetEvent(TimerCount,1,(LPTIMECALLBACK)MidiTimerCallBack,
//		NULL,TIME_PERIODIC);
	smidiDLL_PROCESS_ATTACH();

	InitFlag = 1;
	hUser = hwnd;

	int a,b;
	for(a = 0;a < SMIDI_TRACK_MAX;a ++){
		for(b = 0;b < 2;b ++)
			LastTrackData[a].VibRate[b] = 64;
		for(b = 0;b < 2;b ++)
			LastTrackData[a].VibDepth[b] = 64;
		for(b = 0;b < 2;b ++)
			LastTrackData[a].VibDelay[b] = 64;

		for(b = 0;b < 2;b ++)
			LastTrackData[a].TVFCutoff[b] = 64;
		for(b = 0;b < 2;b ++)
			LastTrackData[a].TVFResonance[b] = 64;

		for(b = 0;b < 2;b ++)
			LastTrackData[a].AtackTime[b] = 64;
		for(b = 0;b < 2;b ++)
			LastTrackData[a].DecayTime[b] = 64;
		for(b = 0;b < 2;b ++)
			LastTrackData[a].ReleaseTime[b] = 64;
	}

	return SMIDI_NOERROR;
}

//---終了
SMIDIFUNC int smidiEnd(HWND hwnd)
{
	if(!InitFlag){
		//初期化されていなければ
		return SMIDI_ER_SOMETHING;
	}
	if(lpsmidiActiveStream){
		smidiStop(lpsmidiActiveStream);
	}

	if(MidiTimerID)
		timeKillEvent(MidiTimerID);

	smidiDLL_PROCESS_DETACH();

	InitFlag = 0;
	ThreadFlag = 0;
	Sleep(50);

	hUser = 0;

	return SMIDI_NOERROR;
}

//---ストリームに情報セット
SMIDIFUNC void smidiInitStreamInfo(LPSMIDI_STREAM lpsmidi)
{
	int a;
	lpsmidi->Division = 96;
	lpsmidi->Tempo = 500000;
	lpsmidi->MidiClock=lpsmidi->Tempo / lpsmidi->Division;
	lpsmidi->MasterVolume = 127;
	lpsmidi->lpBackMidiData = lpsmidi->lpMidiData;
	lpsmidi->FirstPlayFlag = 1;
//	lpsmidi->hMidiData = NULL;

	for(a = 0;a < SMIDI_TRACK_MAX;a++){
		//---バンクチェンジ
		lpsmidi->tr[a].Control[ 0] = 0;
		lpsmidi->tr[a].Control[32] = 0;
		lpsmidi->tr[a].ControlFlag[ 0] = 1;
		lpsmidi->tr[a].ControlFlag[32] = 1;
		lpsmidi->tr[a].Program = 0;

		lpsmidi->tr[a].VibRate[0] = 64;
		lpsmidi->tr[a].VibRate[1] = 64;
		lpsmidi->tr[a].VibDepth[0] = 64;
		lpsmidi->tr[a].VibDepth[1] = 64;
		lpsmidi->tr[a].VibDelay[0] = 64;
		lpsmidi->tr[a].VibDelay[1] = 64;

		lpsmidi->tr[a].TVFCutoff[0] = 64;
		lpsmidi->tr[a].TVFCutoff[1] = 64;
		lpsmidi->tr[a].TVFResonance[0] = 64;
		lpsmidi->tr[a].TVFResonance[1] = 64;

		lpsmidi->tr[a].AtackTime[0] = 64;
		lpsmidi->tr[a].AtackTime[1] = 64;
		lpsmidi->tr[a].DecayTime[0] = 64;
		lpsmidi->tr[a].DecayTime[1] = 64;
		lpsmidi->tr[a].ReleaseTime[0] = 64;
		lpsmidi->tr[a].ReleaseTime[1] = 64;

		lpsmidi->tr[a].PitchBendSensitibity[0] = 64;
		lpsmidi->tr[a].PitchBendSensitibity[1] = 64;
		
		lpsmidi->tr[a].PitchBendLow = 0;
		lpsmidi->tr[a].PitchBendHigh = 0x40;
	}
}

//---ストリームを作る
SMIDIFUNC LPSMIDI_STREAM smidiCreateStream(void)
{
	LPSMIDI_STREAM lpsmidi;
	EIMEMORY hg;

	hg = eiAllocMemory(sizeof(SMIDI_STREAM) + 100);
	if(!hg)
		return 0;

	lpsmidi = (LPSMIDI_STREAM)eiLockMemory(hg);
	if(!lpsmidi){
		eiFreeMemory(hg);
		return 0;
	}
	memset(lpsmidi,0,sizeof(SMIDI_STREAM));

	lpsmidi->hThisStruct = hg;

	smidiInitStreamInfo(lpsmidi);

	return lpsmidi;
}

//---ストリームを削除する
SMIDIFUNC int smidiDeleteStream(LPSMIDI_STREAM lpsmidi)
{
	EIMEMORY hg1,hg2;

	if(lpsmidi == NULL)
		return SMIDI_ER_SOMETHING;
	
	if(lpsmidiActiveStream == lpsmidi){
		smidiStop(lpsmidi);
		//念のため
		Sleep(10);
	}

	hg1 = lpsmidi->hMidiData;
	hg2 = lpsmidi->hThisStruct;
	if(hg1 != NULL){
		//ＭＩＤＩバッファーが確保されているなら解放する
		eiFreeMemory(hg1);
	}
	//構造体を解放
	if(hg2 != NULL){
		eiFreeMemory(hg2);
	}
	
	return SMIDI_NOERROR;
}

//---ポインタを開始地点にあわせる
SMIDIFUNC int smidiSetStreamToStart(LPSMIDI_STREAM lpsmidi)
{
	smidiCheckPointer(lpsmidi);

	if(lpsmidi->PlayFlag)
		return SMIDI_ER_SOMETHING;

	//ポインタを開始地点にあわせる
	lpsmidi->lpMidiData = lpsmidi->lpStartMidiData;

	//デルタタイム読み込み
	lpsmidi->NextDeltaTime = GetValData(&lpsmidi->lpMidiData);
	lpsmidi->DeltaTime = lpsmidi->dwDeltaTime = lpsmidi->NextDeltaTime;
	lpsmidi->PlayCount = 0;
//	lpsmidi->lpLastMidiData = lpsmidi->lpMidiData;
	lpsmidi->lpBackMidiData = lpsmidi->lpMidiData;

	lpsmidi->FirstPlayFlag = 1;

	InitStreamData(lpsmidi);

	return SMIDI_NOERROR;
}

//---ＭＩＤＩファイル読み込み
SMIDIFUNC int smidiOpenFile(LPSMIDI_STREAM lpsmidi,LPSTR name,LPSTR slname,int mode)
{
	int size = 0;
//	struct _finddata_t file_find;
	EIMEMORY hg,hkeep;

	eiFile file;
	if(mode == 2)
		file.SetLinkFile(NULL);
	else
		file.SetLinkFile(slname);

	MIDIFILEHEADER Header;
	eiBitStream eb;
	EIMEMORY hMemory = NULL;
	ei_u8 *pMemory = NULL;

	smidiStop(lpsmidi);

	//---ファイルオープン
	if(mode != 2){
		if(file.Open(name) == 0){
			return SMIDI_ER_CANTOPEN;
		}
	}

	if(mode == 0){
		size = file.GetSize();
	} else if(mode == 2){
		//---midipak
		size = (int)slname;
//		size = file.GetSize();
	} else if(mode == 1){
		//---ezarc
		char temp[3];
		file.Read(&temp[0],1,3);
		eb.ReadCompressFile(&file);
		size = eb.Buffer.OriginalSize;
		hMemory = eiAllocMemory(size + 1024);
		pMemory = (ei_u8 *)eiLockMemory(hMemory);
		if(pMemory == NULL){
			file.Close();
			return SMIDI_ER_CANTOPEN;
		}

		eb.Decompress(pMemory);
	}

	//もしすでにバッファーがあるなら解放
	if(lpsmidi->hMidiData){
		eiUnlockMemory(lpsmidi->hMidiData);
		lpsmidi->lpMidiData = NULL;
		eiFreeMemory(lpsmidi->hMidiData);
	}
	//メモリ解放
	hkeep = lpsmidi->hThisStruct;
	memset(lpsmidi,0,sizeof(LPSMIDI_STREAM));
	lpsmidi->hThisStruct = hkeep;

	//メモリ割り当て
	if(mode == 2){
		lpsmidi->hMidiData = hg = (EIMEMORY)name;
	} else {
		lpsmidi->hMidiData = hg = eiAllocMemory(size+100);
		if(hg == NULL){
			//確保できないなら
			file.Close();
			return SMIDI_ER_NOMEMORY;
		}
	}

	lpsmidi->lpBuffer = lpsmidi->lpMidiData = (LPBYTE)eiLockMemory(hg);
	if(lpsmidi->lpMidiData == NULL){
		file.Close();
		return SMIDI_ER_NOMEMORY;
	}

	//---読み込み
	if(mode == 0){
		file.Read(lpsmidi->lpMidiData, 1 , size);
	} else if(mode == 1){
		memcpy(lpsmidi->lpMidiData, pMemory,size);
		eb.FreeBuffer();
		eiFreeMemory(hMemory);
	} else if(mode == 2){
		//---すでに読み込んである
	}

	if(mode != 2){
		file.Close();
	}

	lpsmidi->MidiDataSize = size;
	//構造体を初期化
	smidiInitStreamInfo(lpsmidi);

	//ヘッダーチェック
	if(memcmp(lpsmidi->lpMidiData, "MThd", 4)) {
		return 4;
	}
	memcpy(&Header, lpsmidi->lpMidiData, sizeof(MIDIFILEHEADER));

	//分解能
	lpsmidi->Division=(DWORD)( 
		( (Header.Division & 0xff00) >> 8) |
		( (Header.Division & 0x00ff) << 8) );
	if(lpsmidi->Division == 0)
		lpsmidi->Division = 48;

	Header.HeaderLength = (WORD)(LongByte((BYTE*)&(Header.HeaderLength)));
	if((Header.Format = (WORD)(ShortByte((BYTE*)&(Header.Format))) > 0)) {
		return 13;
	}
	Header.Tracks = (WORD)(ShortByte((BYTE*)&(Header.Tracks)));
	if((Header.Division = (WORD)(ShortByte((BYTE*)&(Header.Division))) > 1920)) {
		return 14;
	}

	lpsmidi->lpMidiData += (Header.HeaderLength+sizeof(DWORD)+HEADER_SIZE);

	if(memcmp(lpsmidi->lpMidiData,"MTrk", 4)) {
		//---ＭＩＤＩファイルじゃない！
		return SMIDI_ER_SOMETHING;
	}

	lpsmidi->lpMidiData += HEADER_SIZE;

	lpsmidi->MidiDataSize = LongByte(lpsmidi->lpMidiData);
	lpsmidi->lpMidiData += sizeof(DWORD);
	lpsmidi->lpStartMidiData = lpsmidi->lpMidiData;
	
	smidiSetStreamToStart(lpsmidi);
/*	//デルタタイム読み込み
	lpsmidi->NextDeltaTime = GetValData(&lpsmidi->lpMidiData);
	lpsmidi->DeltaTime = lpsmidi->NextDeltaTime;*/

	return SMIDI_NOERROR;
}

//---ループプレイか、一回限りか指定
SMIDIFUNC int smidiSetPlayMode(int mode)
{
	int a;

	a = PlayMode;
	PlayMode = mode;

	return a;
}

SMIDIFUNC int smidiGetPlayMode(void)
{
	return PlayMode;
}

SMIDIFUNC WORD smidiGetVersion(void)
{
	return smidiVersion;
}

//---フェードイン
SMIDIFUNC void smidiFadeIn(int max,int start,int speed)
{
	if(!lpsmidiActiveStream)
		return;

	if(max < 0 || max > 127)
		max = 127;
	if(start != -1){
		if(start < 0)
			start = 0;
		if(start > max)
			start = max;
	}

	if(max == -1)
		FadeLimitVolume = lpsmidiActiveStream->MasterVolume;
	else
		FadeLimitVolume = max;

	if(start != -1)
		lpsmidiActiveStream->MasterVolume = start;

	FadeSpeed = speed;
	VolumeFade = 1;
}

//---フェードアウト
SMIDIFUNC void smidiFadeOut(int min,int start,int speed)
{
	if(!lpsmidiActiveStream)
		return;

	if(min < 0 || min > 127)
		min = 0;
	if(start != -1){
		if(start > 127)
			start = 127;
		if(start < min)
			start = min;
	}

	if(min == -1)
		FadeLimitVolume = 0;
	else
		FadeLimitVolume = min;

	if(start != -1)
		lpsmidiActiveStream->MasterVolume = start;

	FadeSpeed = speed;
	VolumeFade = 2;
}

SMIDIFUNC int smidiGetPlayTime(LPSMIDI_STREAM lpsmidi)
{
	int t = smidiet.Get();

	return t;
}

SMIDIFUNC int smidiGetPoint(LPSMIDI_STREAM lpsmidi,int *shosetu,
				int *clock,int *all_clock)
{
	int a;

	smidiCheckPointer(lpsmidi);

/*	a = lpsmidi->PlayCount;
	*shosetu = a / (lpsmidi->Division * 4);
	*clock = a - (*shosetu * lpsmidi->Division);
	*all_clock = a;*/
	//ポイントを得る
	//４分音符１個が４クロック
	a = StreamGetPoint();
	*shosetu = a / 16;
	*clock = a - (*shosetu * 16);
	*all_clock = a;

	return SMIDI_NOERROR;
}

DWORD GetValData(BYTE **p)
{
	DWORD val = 0;
	BYTE dat;
	int i;
	for (i = 0; i < 4; i++) {
		dat = *((*p)++);
		val = (val << 7) + (dat & 0x7F);
		if ((dat & 0x80) == 0)
			break;
	}
	return val;
}

DWORD GetValData2(BYTE *p, int *a)
{
	DWORD val = 0;
	BYTE dat;
	int i;
	*a = 0;
	for (i = 0; i < 4; i++) {
		dat = *(p++);
		val = (val << 7) + (dat & 0x7F);
		(*a)++;
		if ((dat & 0x80) == 0)
			break;
	}
	return val;
}

DWORD LongByte(BYTE *p)
{
	int i;
	BYTE buf[4];
	for (i = 0; i < 4; i++) {
		buf[i] = p[3 - i];
	}
	return *(DWORD *)buf;
}

WORD ShortByte(BYTE *p)
{
	return ((WORD)*p << 8) + *(p + 1);
}
