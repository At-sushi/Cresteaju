//---------------------------
//	eiLibrary補助関数
//---------------------------

#ifndef ONLY_USE_ALLOC

//---セマフォ
HANDLE hCriticalSection;

//---同期を取る
EI_API int eiWaitCriticalSection(ei_u32 WaitTime)
{
	if(WaitTime == 0)
		WaitTime = INFINITE;

	if(WaitForSingleObject(hCriticalSection,WaitTime) == WAIT_TIMEOUT)
		return -1;
	return 1;
}

EI_API int eiReleaseCriticalSection(void)
{
	return (int)ReleaseSemaphore(hCriticalSection,1,NULL);
}

#endif

#if _DEBUG
#define CHECK_EIMEMORY
#endif

#ifdef CHECK_EIMEMORY

#define MEMORYTABLE_MAX 10000
static EIMEMORY MemoryTable[MEMORYTABLE_MAX + 1];
static int MemoryInitFlag = 0,MaxMemoryTableCount = 0,
	MemorySizeTable[MEMORYTABLE_MAX + 1];

EI_API void eiMemoryOutputForDebug(void)
{
	int a;
	char s[80];

	eiDebugWriteFile("eiMemoryOutputForDebug******************\n");
	sprintf(s,"最大使用個数:%d\n",MaxMemoryTableCount);
	eiDebugWriteFile(s);
	for(a = 0;a < MEMORYTABLE_MAX;a ++){
		if(MemoryTable[a] != NULL){
			sprintf(s,"(eiMemoryOutputForDebug)Memory:%4d: %6d byte  %8x !!\n",a,MemorySizeTable[a],MemoryTable[a]);
			eiDebugWriteFile(s);
		}
	}
	eiDebugWriteFile("eiMemoryOutputForDebug******************\n");
}

EI_API void eiMemorySetPointerForDebug(void *pMemory)
{
	int a;

	for(a = 0;a < MEMORYTABLE_MAX && MemoryTable[a] != NULL;a ++){
	}
	MemoryTable[a] = (EIMEMORY)pMemory;
	MemorySizeTable[a] = -1;

	if(a > MaxMemoryTableCount)
		MaxMemoryTableCount = a;
}

EI_API void eiMemoryDeletePointerForDebug(void *pMemory)
{
	int a;
	for(a = 0;a < MEMORYTABLE_MAX && MemoryTable[a] != (EIMEMORY)pMemory;a ++){
	}
	MemoryTable[a] = NULL;
}

#else 

EI_API void eiMemoryOutputForDebug(void)
{
}

EI_API void eiMemorySetPointerForDebug(void *pMemory)
{
}

EI_API void eiMemoryDeletePointerForDebug(void *pMemory)
{
}

#endif /*CHECK_EIMEMORY*/

EI_API void eimemset(void *memory,int set,int size)
{
	int a;
	ei_u8 *p = (ei_u8 *)memory;

	for(a = 0;a < size;a ++){
		*(p + a) = (ei_u8)set; 
	}
}

//---メモリー確保
EI_API EIMEMORY eiAllocMemory(int size)
{
	EIMEMORY eiMem;

#ifdef USE_MALLOC
	eiMem = (EIMEMORY)malloc((size_t)size);
#else
	eiMem = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT,size);
#endif
	if(eiMem == NULL){
//		eiDebugWriteFile("(eiAllocMemory) Alloc error!!\n");
		return NULL;
	}

#ifdef CHECK_EIMEMORY
	{
		if(MemoryInitFlag == 0){
			memset(MemoryTable,0,sizeof(MemoryTable));
			MemoryInitFlag = 1;
		}
		int a;
		for(a = 0;a < MEMORYTABLE_MAX && MemoryTable[a] != NULL;a ++){
		}
		MemoryTable[a] = eiMem;
		MemorySizeTable[a] = size;
		if(a > MaxMemoryTableCount)
			MaxMemoryTableCount = a;
	}
#endif

	return eiMem;
}

//---メモリー確保
EI_API EIMEMORY eiReallocMemory(EIMEMORY eiMem,int size)
{
#ifdef USE_MALLOC
	eiMem = (EIMEMORY)realloc((void *)eiMem,(size_t)size);
#else
	eiMem = GlobalReAlloc(eiMem,size,GMEM_ZEROINIT);
#endif
	if(eiMem == NULL)
		return NULL;

	return eiMem;
}

//---メモリー解放
EI_API EIMEMORY eiFreeMemory(EIMEMORY eiMem)
{
#ifdef CHECK_EIMEMORY
	int a;
	for(a = 0;a < MEMORYTABLE_MAX && MemoryTable[a] != eiMem;a ++){
	}
	MemoryTable[a] = NULL;
#endif

#ifdef USE_MALLOC
	free((void *)eiMem);
	return NULL;
#else
	return GlobalFree(eiMem);
#endif
}

//---メモリーをロック
EI_API LPVOID eiLockMemory(EIMEMORY eiMem)
{
#ifdef USE_MALLOC
	return (void *)eiMem;
#else
	return GlobalLock(eiMem);
#endif
}

//---メモリーをアンロック
EI_API int eiUnlockMemory(EIMEMORY eiMem)
{
#ifdef USE_MALLOC
	return 1;
#else
	return (int)GlobalUnlock(eiMem);
#endif
}

#ifndef ONLY_USE_ALLOC

//---文字列比較
EI_API int eiCompareString(eistr *st1,eistr *st2)
{
	int res = CompareString(LOCALE_USER_DEFAULT,0,
		st1,-1,st2,-1);

	if(res == CSTR_LESS_THAN){
		return -1;
	}
	if(res == CSTR_EQUAL){
		return 0;
	}
	if(res == CSTR_GREATER_THAN){
		return 1;
	}
	return 0;
}

//---ゲーム座標をスクリーン座標に変換
EI_API void eiChangePoint(int *x,int *y)
{
	if(!::eiSystem.ScreenZoomRate)
		return;
	*x = (*x) >> ::eiSystem.ScreenZoomRate;
	*y = (*y) >> ::eiSystem.ScreenZoomRate;
}

//---ゲーム座標をスクリーン座標に変換
EI_API void eiChangeRect(LPRECT lpRect)
{
	if(!::eiSystem.ScreenZoomRate)
		return;

	lpRect->left = lpRect->left >> ::eiSystem.ScreenZoomRate;
	lpRect->top = lpRect->top >> ::eiSystem.ScreenZoomRate;
	lpRect->right = lpRect->right >> ::eiSystem.ScreenZoomRate;
	lpRect->bottom = lpRect->bottom >> ::eiSystem.ScreenZoomRate;
}

//---マウス座標
EI_API void eiGetMousePoint(LPEIPOINT lpPoint)
{
	POINT p;

	p.x = lpPoint->x;
	p.y = lpPoint->y;
	GetCursorPos(&p);
	lpPoint->x = p.x;
	lpPoint->y = p.y;
}

//---スリープ
EI_API void eiSleep(int n)
{
	eiCheckThread();

	Sleep(n);
}

//---ウィンドウの座標
EI_API void eiGetWindowRect(LPRECT lpRect)
{
	memcpy(lpRect,&eiWindowRect,sizeof(eiWindowRect));
}

//---キーボード
EI_API void eiReadKey(UINT key1,UINT key2,int mode)
{
	char key_data = (char)(key1 & 0x7f);
	int key_on = 0;

	if(mode == 1)
		key_on = 1;

	if(key_data == 0x51 && key_on == 1){
		com_key |= KEY_Q;
	}
	if(key_data == 0x51 && key_on == 0){
		com_key &=~ KEY_Q;
	}	   
}

//---スワップ
EI_API void eiSwap(int *a,int *b)
{
	int c;

	c = *a;
	*a = *b;
	*b = c;
}

//---乱数初期化
EI_API void eiInitRnd(void)
{
	srand(time(NULL));
}

//---乱数発生
EI_API int eiRnd(int n)
{
	int a = rand();

	if(n == 0)
		return 0;

	a = a % n;
	return a;
}

//---文字列検索
EI_API int eiGetStringItem(EISTR *find_str,EISTR *in_str,EISTR *out_str,int *out_ad)
{
	EISTR *s = in_str;
	EISTR *p,*q;
	int c = 0;
	EISTR t[80];
	
	p = in_str;
	in_str = q = &t[0];

	while(*p){
		if(*p != ' ' && *p != '\n' && *p != '\r' && *p != '\t'){
			//---スペース、改行、以外だったらコピーする
			*q = *p;
			q++;
		}
		p++;
	}

	*q = NULL;
	p = &t[0];

	if(*p == ';' || *p == '[')
		//コメントなら戻る
		return 0;
	while(*p){
		//---'='を探す
		if(*p == '=')
			break;
		p ++;	
	}
	if(*p != '=')
		return 0;

	//---'='を消して文字列を２つにわける
	*p = NULL;
	p ++;

	if(strcmp(in_str,find_str)){
		//文字が検索と一致しないなら
		return 0;
	}

	//---実際の値を得る
	c = atoi(p);
	if(out_str){
		strcpy(out_str,p);
	}
	if(out_ad)
		*out_ad = c;

	return 1;
}

//---テキストモード設定
EI_API int eiSetDirectText(int mode)
{
	int a = eiUseDirectText;

	eiUseDirectText = mode;

	return a;
}

//---フォント設定
EI_API int eiSetFont(int number)
{
	int a = ::eiSystem.ActiveFont;

	::eiSystem.ActiveFont = number;

	return a;
}

/*//---カーソル設定
EI_API HCURSOR eiSetCursor(int num)
{
	return SetCursor(hCursor[num]);
}
*/

//---時間を得る
EI_API int eiGetTime(void)
{
	return GetTickCount();
}

//---メモリー上ににテキストを描く
EI_API int DrawTextMemory(LPBYTE lpMemory,int Direction,int MemorySize,int LineSize,
						  EISTR *String,int x,int y,int color,int efect)
{
	RECT rect;
	int a,b,c,size;
	EISTR t[4],u;
	HDC hdc = eiDibDrawText.hMemoryDC;
	LPBYTE lpKeepMemory = lpMemory;

	if(hdc == NULL)
		return 0;

	SelectObject(hdc,eiFont[::eiSystem.ActiveFont]);
	SelectObject(hdc,eiDibDrawText.hBitmap);

	SetTextColor(hdc,RGB(0,0,0));
	SetBkColor(hdc,RGB(255,255,255));

	while(*String != NULL){
		u = *(EISTR *)String;
		if(_ismbblead((unsigned int)u)){
			//---２バイト文字
			t[0] = *(EISTR *)String;
			String ++;
			t[1] = *(EISTR *)String;
			t[2] = 0;
			t[3] = 0;
			String ++;
			size = 2;
		} else {
			//---１バイト文字
			t[0] = *(EISTR *)String;
			t[1] = 0;
			t[2] = 0;
			t[3] = 0;
			String ++;	
			size = 1;
		}
		rect.left = rect.top = 0;
		rect.bottom = eiFontSize[::eiSystem.ActiveFont].y;
		rect.right = eiFontSize[::eiSystem.ActiveFont].x * strlen(&t[0]);
		
		//---背景を消す
		eiDibDrawText.DrawFillBox(0,0,eiFontSize[::eiSystem.ActiveFont].x,
			eiFontSize[::eiSystem.ActiveFont].y,
			255,EI_PSET);

		DrawText(hdc,&t[0],strlen(&t[0]),&rect,DT_CENTER); 
		
		lpMemory = lpKeepMemory;
		lpKeepMemory += (size * eiFontSize[::eiSystem.ActiveFont].x * MemorySize);
		for(a = 0;
			a < eiFontSize[::eiSystem.ActiveFont].y ; a ++){
			if(Direction == -1){
				lpMemory -= LineSize;
			} else {
				lpMemory += (LineSize);
			}
			for(b = 0 ; b < (int)(eiFontSize[::eiSystem.ActiveFont].x * strlen(&t[0])) ; b ++){
				c = eiDibDrawText.GetPixel(b,a);

				if(MemorySize <= 1){
					if(c == 0){
						*(lpMemory + b) = (BYTE)color;
					} else if(efect == EI_PSET){
						*(lpMemory + b) = (BYTE)0;
					}
				} else {
					if(c == 0){
						*(WORD *)(lpMemory + b * 2) = (WORD)color;
					} else if(efect == EI_PSET){
						*(WORD *)(lpMemory + b * 2) = (WORD)0;
					}
				}
			}
		}
		x += (size * eiFontSize[::eiSystem.ActiveFont].x);
	}
	return 1;
}

#endif
