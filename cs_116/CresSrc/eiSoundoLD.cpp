/*-----------------------------------------------------------

   eiLibray
   Copyright(C) 1999- Shou/Shogo Kawai All rights reserved.

   eiSound.cpp ...eiSound Class(DirectSound)

-----------------------------------------------------------*/

LPDIRECTSOUND lpDS = NULL;
static int DSInitFlag = 0,DSMode = 0,DSVolume = 127,VolumeTable[256];

//---サウンドを初期化
EI_API int eiInitSound(eiWindow *ew,int mode /*= 0*/)
{
	HRESULT dsval;

	::DSMode = mode;

	if(!(mode & EISOUND_EMULATION)){
		//---エミュレーションでなければ
		dsval = DirectSoundCreate(NULL,&lpDS,NULL);
		if(dsval != DS_OK)
			return FALSE;
		dsval = lpDS->SetCooperativeLevel(ew->hwnd,DSSCL_NORMAL);
		if(dsval != DS_OK)
			return FALSE;
		::DSInitFlag = 1;
	}	
	return TRUE;
}

//---終了
EI_API int eiEndSound(void)
{
	if(lpDS != NULL){
		if(lpDS->Release() > 0){
			eiDebugWriteFile("(eiEndSound) Fail\n");
		}
		lpDS = NULL;
	}

	return 1;
}

//---ボリュームを設定
EI_API int eiSoundSetVolume(int vol)
{
	DSVolume = vol;

	int a;
	double rate = (double)DSVolume / (double)127;

	for(a = 0;a < 256;a ++){
		VolumeTable[a] = (int)( 
			(int)( (double)(a - 127) * rate) + 127
			);
	}

	return 1;
}

EI_API int eiSoundGetVolume(void)
{
	return DSVolume;
}

//-----------------------------------------------------
//---
eiSound::eiSound(void)
{
	memset(&wi,0,sizeof(wi));//;sizeof(WAVEINFO));
	ReadFlag = 0;

	lpwi = NULL;
	hMemory = NULL;
}

eiSound::~eiSound()
{
/*	FreeWaveInfo();
	
	if(hMemory){
		eiFreeMemory(hMemory);
	}
	hMemory = NULL;*/
}

//---Waveファイルを読み込み
BOOL eiSound::ReadWaveFile(EISTR *name,EISTR *slname,
						   int mode,LPBYTE lpmem,int size)
{
	eiFile file(slname);

	if(file.Open(name) == 0){
		return FALSE;
	}

	file.Read(lpmem,1,size);
	file.Close();

	return TRUE;
}

//---Waveファイルをメモリー上に読む
void* eiSound::GetWave(EISTR *name,EISTR *slname,int mode)
{
	EIMEMORY hmem;
	void *lpmem;
	char s[256];

	eiFile file(slname);
	int size;

	if(ReadFlag){
		return lpMemory;
	}

	//---ファイルサイズを調べる
	file.Open(name);
	size = file.GetSize();
	file.Close();
	if(size == 0){
		sprintf(s,"(eiSound::ReadWaveFile)No size (%s) %s\n",name,slname);
		eiDebugWriteFile(s);
		return NULL;
	}

	hmem = eiAllocMemory(size);
	if(hmem == NULL){
		eiFreeMemory(hmem);
		sprintf(s,"(eiSound::ReadWaveFile)Can't alloc memory (%s) %s\n",name,slname);
		eiDebugWriteFile(s);
		return NULL;
	}
	lpmem = eiLockMemory(hmem);
	lpMemory = (LPBYTE)lpmem;
	hMemory = hmem;
	
	if(ReadWaveFile(name,slname,mode,(BYTE *)lpmem,size) == FALSE){
		eiFreeMemory(hmem);
		hMemory = NULL;
		sprintf(s,"(eiSound::ReadWaveFile)Can't read file (%s) %s\n",name,slname);
		eiDebugWriteFile(s);
		return NULL;
	}

	ReadFlag = 1;

	return (void*)lpmem;
}

//---Waveファイル解析
BOOL eiSound::UnpackWaveChunk(void *pRIFFBytes, LPWAVEFORMATEX *lpwfmx, 
				  LPBYTE *lpChunkData,DWORD *lpCkSize )
{
	DWORD *dwChunkBitsPtr;
	DWORD *dwChunkTailPtr;
	DWORD dwChunkID;
	DWORD dwType;
	DWORD dwLength;

	if (lpwfmx)
		*lpwfmx = NULL;

	if (lpChunkData)
		*lpChunkData = NULL;

	if (lpCkSize)
		*lpCkSize = 0;

	dwChunkBitsPtr = (DWORD*)pRIFFBytes;

	dwChunkID = *dwChunkBitsPtr++;	

	dwLength = *dwChunkBitsPtr++;

	dwType = *dwChunkBitsPtr++;

	if (dwChunkID!=mmioFOURCC('R','I','F','F')){
		eiDebugWriteFile("UnpackWaveChunk Not RIFF\n");
		return FALSE;
	}

	if (dwType!=mmioFOURCC('W','A','V','E')){
		eiDebugWriteFile("UnpackWaveChunk Not WaveFile\n");
		return FALSE;
	}

	dwChunkTailPtr = (DWORD*)((BYTE*)dwChunkBitsPtr + dwLength-4);

	while(1){

		dwType = *dwChunkBitsPtr++;
		dwLength = *dwChunkBitsPtr++;

		switch(dwType){
		case mmioFOURCC('f','m','t',' '):
			if (lpwfmx && !*lpwfmx){
				if (dwLength < sizeof(WAVEFORMAT)){
					eiDebugWriteFile("UnpackWaveChunk Not WAVEFORMAT\n");
					return FALSE;
				}

				*lpwfmx = (LPWAVEFORMATEX)dwChunkBitsPtr;

				if ( (!lpChunkData || *lpChunkData) 
					&& (!lpCkSize || *lpCkSize))
					return TRUE;

			}
			break;

		case mmioFOURCC('d','a','t','a'):
			if ((lpChunkData && !*lpChunkData) ||
				(lpCkSize && !*lpCkSize)){
				if (lpChunkData)
					*lpChunkData = (LPBYTE)dwChunkBitsPtr;

				if (lpCkSize)
					*lpCkSize = dwLength;

				if (!lpwfmx || *lpwfmx)
					return TRUE;
			}
			break;
		}
		dwChunkBitsPtr = (DWORD*)((BYTE*)dwChunkBitsPtr + ((dwLength+1)&~1));
		if (dwChunkBitsPtr >= dwChunkTailPtr)
			break;
	}

	eiDebugWriteFile("UnpackWaveChunk Error\n");
	return FALSE;
}

//---Waveデータを書き込む
BOOL eiSound::WriteWaveData( LPDIRECTSOUNDBUFFER lpDSB, LPBYTE lpWaveData, DWORD dwWriteBytes )
{
	int a;
	HRESULT dsval;

	if (lpDSB && lpWaveData && dwWriteBytes){
		LPVOID lpAudioPtr1, lpAudioPtr2;
		DWORD dwAudioBytes1, dwAudioBytes2;

		dsval = lpDSB->Lock(0, dwWriteBytes, &lpAudioPtr1, &dwAudioBytes1, &lpAudioPtr2, &dwAudioBytes2, 0);
		if (dsval == DS_OK){
			if(DSVolume == 127){
				CopyMemory(lpAudioPtr1, lpWaveData, dwAudioBytes1);
			} else {
				for(a = 0;a < (int)dwAudioBytes1;a ++){
					((BYTE *)(lpAudioPtr1))[a] = VolumeTable[lpWaveData[a]];
				}
			}

			if( dwAudioBytes2 != 0){
				if(DSVolume == 127){
					CopyMemory(lpAudioPtr2, lpWaveData + dwAudioBytes1, dwAudioBytes2);
				} else {
					for(a = 0;a < (int)dwAudioBytes2;a ++){
						((BYTE *)(lpAudioPtr2))[a] = VolumeTable[(lpWaveData + dwAudioBytes1)[a]];
					}
				}
			}

			lpDSB->Unlock(lpAudioPtr1, dwAudioBytes1, lpAudioPtr2, dwAudioBytes2);
			return TRUE;
		}
	}

	eiDebugWriteFile("WriteWaveData Fail\n");
	return FALSE;
}

//---
IDirectSoundBuffer* eiSound::MakeSoundBuffer(void *pRIFFBytes,LPDIRECTSOUND lpDS,EISTR *name,EISTR *slname,int mode)
{
	LPDIRECTSOUNDBUFFER lpDSB;
	DSBUFFERDESC dsbd;
	LPBYTE lpWaveData;
	HRESULT dsval;
//	void *pRIFFBytes;
    
	lpDSB = NULL;
	memset(&dsbd, 0x00, sizeof(dsbd));

//	pRIFFBytes = GetWave(name,slname,0);

	if (pRIFFBytes != NULL){
		if(UnpackWaveChunk(pRIFFBytes, &dsbd.lpwfxFormat, &lpWaveData, &dsbd.dwBufferBytes) == FALSE){
			eiDebugWriteFile("MakeSoundBuffer UnpackWaveChunk Fail");
		}

		dsbd.dwSize = sizeof(dsbd);
		dsbd.dwFlags = DSBCAPS_STATIC
			| DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY;

		dsval = lpDS->CreateSoundBuffer( &dsbd, &lpDSB, NULL );
		if (dsval == DS_OK){
			if (WriteWaveData(lpDSB, lpWaveData, dsbd.dwBufferBytes) == FALSE){
				lpDSB->Release();
			    lpDSB = NULL;
			}
		} else {
			eiDebugWriteFile("MakeSoundBuffer Fail\n");
			lpDSB = NULL;
		}
	}

    return (IDirectSoundBuffer*)lpDSB;
}  

//---読み込み
int eiSound::Read(EISTR *name,EISTR *slname,int mode,int bufCount)
{
	void* pRIFFBytes;
	int wiSize;

	if (bufCount < 1)
		bufCount = 1;

	wiSize = sizeof(WAVEINFO) + (bufCount - 1) * sizeof(LPDIRECTSOUNDBUFFER);

	lpwi = &wi;

	if (lpwi == NULL)
		return 0;
	
	lpwi->bufCount = bufCount;

	pRIFFBytes = GetWave(name,slname,mode);
	lpwi->lpMemory = (LPBYTE)pRIFFBytes;

	if(pRIFFBytes != NULL){
		if(DSInitFlag == 0){
			return 1;
		}

		UnpackWaveChunk(pRIFFBytes,&lpwi->lpwfmx,&lpwi->lpWaveData,&lpwi->dwWaveSize);

		int a;

		for (a = 0;a < lpwi->bufCount;a ++){
			HRESULT dsval;

			if(a){
				dsval = lpDS->DuplicateSoundBuffer(lpwi->lpDSBuffer[0], &lpwi->lpDSBuffer[a]);
			} else if(dsval != DS_OK){
				lpwi->lpDSBuffer[a] = MakeSoundBuffer(pRIFFBytes,lpDS,name,slname,mode);

				if (lpwi->lpDSBuffer[a] == NULL){
					FreeWaveInfo();					
					break;
				}
			}
		}
	} else {
		lpwi = NULL;
	}

	return 1;
}

void eiSound::Release(void)
{
	//---
	Stop();

	FreeWaveInfo();
	//---メモリー解放
	if(hMemory != NULL){
		eiFreeMemory(hMemory);
	}
	hMemory = NULL;
}

void eiSound::FreeWaveInfo(void)
{
	int a;

	if(lpwi != NULL){
		for(a = 0;a < lpwi->bufCount;a ++){
			if(lpwi->lpDSBuffer[a] != NULL){
				if(lpwi->lpDSBuffer[a]->Release() > 0){
					eiDebugWriteFile("(eiSound::FreeWaveInfo) Release Fail\n");
				} else {
				}
				lpwi->lpDSBuffer[a] = NULL;
			}
		}
	}
}

IDirectSoundBuffer* eiSound::GetAvailableBuf(void)
{
	LPDIRECTSOUNDBUFFER lpDSB;
	HRESULT hres;
	DWORD dwStatus;

LABEL1:

	if (lpwi ==NULL)
		return NULL;
	
	if (lpDSB = lpwi->lpDSBuffer[lpwi->bufferIndex]){
		hres = lpDSB->GetStatus(&dwStatus);
		if (hres != DS_OK)
			dwStatus = 0;
		if ((dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING){
			if (lpwi->bufCount > 1){
				if (++lpwi->bufferIndex >= lpwi->bufCount)
					lpwi->bufferIndex = 0;
				lpDSB = lpwi->lpDSBuffer[lpwi->bufferIndex];
				hres = lpDSB->GetStatus(&dwStatus);

				if ((hres == DS_OK)&&(dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING){
					lpDSB->Stop();
					lpDSB->SetCurrentPosition(0);
				}
			} else {
				//---もしバッファーが一つだけなら
				lpDSB = NULL;
				Stop();
				//---新しく再生しなおす
				goto LABEL1;
			}
		}

		if (lpDSB && (dwStatus & DSBSTATUS_BUFFERLOST)){
			hres = lpDSB->Restore();
			if ((hres != DS_OK) ||
				!WriteWaveData(lpDSB, lpwi->lpWaveData, lpwi->dwWaveSize)){
				lpDSB = NULL;// ==
			}
		}
	}

	return lpDSB;
}

//---再生
BOOL eiSound::Play(DWORD PlayFlag /* = 0*/)
{
	HRESULT dsval;

	if(::DSMode & EISOUND_SILENCE){
		//---サイレンスだったら
		return 1;
	}

	if(lpwi == NULL)
		return FALSE;

	if(DSInitFlag == 0){
		//-------DirectSoundが使えなければ
		if(PlayFlag & EISOUND_PLAYLOOP){
			//---ループ再生
			PlaySound((LPCSTR)lpwi->lpMemory,0,SND_LOOP | SND_MEMORY | SND_NOWAIT | SND_ASYNC);
		} else {
			PlaySound((LPCSTR)lpwi->lpMemory,0,SND_MEMORY | SND_NOWAIT | SND_ASYNC);
		}
		return TRUE;
	}

	if((!(PlayFlag & EISOUND_PLAYLOOP) || (lpwi->bufCount == 1))){
		LPDIRECTSOUNDBUFFER lpDSB = GetAvailableBuf();
		if (lpDSB != NULL){
			dsval = lpDSB->Play(0,0,
				(PlayFlag & EISOUND_PLAYLOOP) ? DSBPLAY_LOOPING : 0);
		} 
	}

	if(dsval == TRUE)
		return TRUE;
	else
		return FALSE;
}

//---定位設定
void eiSound::SetPan(void)
{
    LPDIRECTSOUNDBUFFER lpDSB = GetAvailableBuf();

	if(::DSMode & EISOUND_SILENCE){
		return;
	}
    if (lpDSB){
        lpDSB->SetPan( (LONG)((20000 * 320) / 640) - 10000);

        lpDSB->Play( 0, 0, 0);
    }
}

//---止める
BOOL eiSound::Stop(void)
{			  
	if (lpwi == NULL)
		return FALSE;
	if(::DSMode & EISOUND_SILENCE){
		return 1;
	}
	if(DSInitFlag == 0){
		PlaySound(NULL,0,SND_PURGE);
		return 1;
	}

	LPDIRECTSOUNDBUFFER lpDSB;

	int a;
	for (a = 0;a < lpwi->bufCount;a ++){
		lpDSB = (LPDIRECTSOUNDBUFFER)lpwi->lpDSBuffer[a];
		lpDSB->Stop();
		lpDSB->SetCurrentPosition(0);
	}
	return TRUE;
}
