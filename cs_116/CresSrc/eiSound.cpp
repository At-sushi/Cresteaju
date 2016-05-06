/*-----------------------------------------------------------

   eiLibray
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   eiSound.cpp ...eiSound Class(DirectSound)

-----------------------------------------------------------*/

static LPDIRECTSOUND lpDS = NULL;
static int DSInitFlag = 0,DSMode = 0,DSVolume = 127,VolumeTable[256];
static double DSSetVolume = 0.0;

//---�T�E���h��������
EI_API int eiInitSound(eiWindow *ew,int mode /*= 0*/)
{
	HRESULT hres;

	::DSMode = mode;

	if(!(mode & EISOUND_EMULATION)){
		//---�G�~�����[�V�����łȂ����
		hres = DirectSoundCreate(NULL,&lpDS,NULL);
		if(hres != DS_OK)
			return FALSE;
		hres = lpDS->SetCooperativeLevel(ew->hwnd,DSSCL_NORMAL);
		if(hres != DS_OK)
			return FALSE;
		::DSInitFlag = 1;
	}	

	return TRUE;
}

//---�I��
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

//---�{�����[����ݒ�
EI_API int eiSoundSetVolume(int vol)
{
	vol += 128;

	::DSVolume = vol;

	double rad = 3.141592 / 180.0;
	DSSetVolume = DSBVOLUME_MIN - sin( (90.0 * rad) + ((255 - ::DSVolume) * 90.0 / 255.0f) * rad) * DSBVOLUME_MIN;

/*	int a;
	double rate = (double)DSVolume / (double)127;

	for(a = 0;a < 256;a ++){
		VolumeTable[a] = (int)( 
			(int)( (double)(a - 127) * rate) + 127
			);
	}
*/
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
	eimemset(&info,0,sizeof(info));
}

eiSound::~eiSound()
{
}

//---���
void eiSound::Release(void)
{
	//---
	Stop();

	int a;
	for(a = 0;a < info.BufferCount;a ++){
		if(info.lpDSBuffer[a] != NULL){
			if(info.lpDSBuffer[a]->Release() > 0){
				eiDebugWriteFile("(eiSound::Release) Release Fail\n");
			} else {
			}
			info.lpDSBuffer[a] = NULL;
		}
	}

	if(info.hPCMMemory != NULL){
		eiFreeMemory(info.hPCMMemory);
		info.hPCMMemory = NULL;
	}
	if(info.hWaveMemory != NULL){
		eiFreeMemory(info.hWaveMemory);
		info.hWaveMemory = NULL;
	}
}

//---��ʐݒ�
void eiSound::SetPan(void)
{
	if(DSInitFlag == 0){
		return;
	}
}

//---�~�߂�
int eiSound::Stop(void)
{
	if(!info.EnablePlay){
		return 1;
	}

	if(::DSMode & EISOUND_SILENCE){
		return 1;
	}
	if(DSInitFlag == 0){
		PlaySound(NULL,0,SND_PURGE);
		return 1;
	}

	LPDIRECTSOUNDBUFFER lpDSB = NULL;

	int a;
	for (a = 0;a < info.BufferCount;a ++){
		lpDSB = (LPDIRECTSOUNDBUFFER)info.lpDSBuffer[a];
		if(lpDSB != NULL){
			lpDSB->Stop();
			lpDSB->SetCurrentPosition(0);
		}
	}
	return TRUE;
}



//---�t�@�C������̓ǂݍ���
int eiSound::Read(EISTR *name,EISTR *slname,int mode,int BufferCount /* = 1*/)
{
	EIMEMORY hmem;
	BYTE *lpmem;
	char s[256];

	eiFile file(slname);
	int size,ret = 0;

//OutputDebugString(name);
//OutputDebugString("\n");

	//---�\���̏�����
	memset(&info,0,sizeof(info));
	info.BufferCount = BufferCount;
	info.BufferIndex = 0;

	//---�t�@�C���T�C�Y�𒲂ׂ�
	file.Open(name);
	size = file.GetSize();

	if(size == 0){
		file.Close();
		sprintf(s,"(eiSound::ReadWaveFile)No size (%s) %s\n",name,slname);
		eiDebugWriteFile(s);
		return 0;
	}

	//---Wave�t�@�C���T�C�Y���̃������[���m��
	hmem = eiAllocMemory(size);
	if(hmem == NULL){
		sprintf(s,"(eiSound::ReadWaveFile)Can't alloc memory (%s) %s\n",name,slname);
		eiDebugWriteFile(s);
		file.Close();
		return 0;
	}

	lpmem = (BYTE *)eiLockMemory(hmem);
	if(lpmem == NULL){
		eiDebugWriteFile("(eiSound::Read)lpmem == NULL\n");
		eiFreeMemory(hmem);
		file.Close();
		return 0;
	}

	//---�T�C�Y��������C�ɓǂݍ���
	file.Read(lpmem,size);
	file.Close();

	if(DSInitFlag == 0){
		info.hWaveMemory = hmem;
		info.lpWaveMemory = (BYTE *)lpmem;
		info.EnablePlay = 1;
		return 1;
	}

	//---���
	HMMIO hmm;
	MMCKINFO parent,child;
	MMIOINFO mmioinfo;

	memset(&parent,0,sizeof(parent));
	memset(&child,0,sizeof(child));
	memset(&mmioinfo,0,sizeof(mmioinfo));

	mmioinfo.pchBuffer = (char *)lpmem;
	mmioinfo.fccIOProc = FOURCC_MEM;
	mmioinfo.cchBuffer = size;

	hmm = mmioOpen((LPTSTR)NULL,&mmioinfo,MMIO_READ | MMIO_ALLOCBUF);
	do {
		if(hmm == NULL){
			eiDebugWriteFile("(eiSound::Read)hmm == NULL\n");
			break;
		}

		parent.fccType = mmioFOURCC('W','A','V','E');
		if(mmioDescend(hmm,&parent,NULL,MMIO_FINDRIFF)){
			eiDebugWriteFile("(eiSound::Read)WAVE Not Found\n");
			break;
		}

		child.ckid = mmioFOURCC('f','m','t',' ');
		if(mmioDescend(hmm,&child,&parent,0)){
			eiDebugWriteFile("(eiSound::Read)fmt NotFound\n");
			break;
		}

		//---�ǂݍ���
		if(mmioRead(hmm,(char *)&info.wf,sizeof(info.wf)) != sizeof(info.wf)){
			eiDebugWriteFile("(eiSound::Read)mmioRead failed\n");
			break;
		}

		//---�t�H�[�}�b�g�^�C�v���������
		if(info.wf.wFormatTag != WAVE_FORMAT_PCM){
			eiDebugWriteFile("(eiSound::Read)Not WAVE_FORMAT_PCM\n");
			break;
		}
	
		if(mmioAscend(hmm,&child,0)){
			eiDebugWriteFile("(eiSound::Read)mmioAscend failed.\n");
			break;
		}

		child.ckid = mmioFOURCC('d','a','t','a');
		if(mmioDescend(hmm,&child,&parent,MMIO_FINDCHUNK)){
			eiDebugWriteFile("(eiSound::Read)data mmioDescend failed.\n");
			break;
		}

		//---�o�b�l�������m��
		int memory_size = child.cksize;

		info.hPCMMemory = eiAllocMemory(memory_size);
		info.lpPCMMemory = (BYTE *)eiLockMemory(info.hPCMMemory);
		info.PCMMemorySize = child.cksize;

		if((DWORD)mmioRead(hmm,(char *)info.lpPCMMemory,child.cksize) != child.cksize){
			eiDebugWriteFile("(eiSound::Read)mmioRead failed.\n");
			break;
		}

		if(DSInitFlag){
			if(CreateBuffer()){
				FillBuffer();
			}
		}
		ret = 1;
	} while(0);

	if(mmioClose(hmm,0)){
		eiDebugWriteFile("(eiSound::Read)mmioClose failed.\n");
	}

	info.hWaveMemory = hmem;
	info.lpWaveMemory = (BYTE *)lpmem;

	return ret;
}

//static int testAllSize[2] = {0,0};

//---�o�b�t�@�[�ɃT�E���h���R�s�[����
int eiSound::FillBuffer(void)
{
	int buf = 0;
	LPVOID pwrite[2];
	DWORD len[2];
	HRESULT hres;

	info.EnablePlay = 0;

	if(info.lpPCMMemory == NULL){
		//---�o�b�l�f�[�^���Ȃ��I�I
		return 0;
	}

	hres = info.lpDSBuffer[buf]->Lock(0,info.PCMMemorySize,
		&pwrite[0],&len[0],
		&pwrite[1],&len[1],0);

	if(hres == DSERR_BUFFERLOST){
		info.lpDSBuffer[buf]->Restore();
//		info.lpDSBuffer[buf]->Release();

		hres = info.lpDSBuffer[buf]->Lock(0,info.PCMMemorySize,
			&pwrite[0],&len[0],
			&pwrite[1],&len[1],0);
		if(hres != DS_OK){
			eiDebugWriteFile("(eiSound::FillBuffer)Lock failed.\n");
			return 0;
		}
	} else if(hres != DS_OK) {
		eiDebugWriteFile("(eiSound::FillBuffer)Lock failed.\n");
		return 0;
	}

	memcpy(pwrite[0],info.lpPCMMemory,len[0]);
	if(pwrite[1] != NULL){
		memcpy(pwrite[1],info.lpPCMMemory + len[0],len[1]);
	}

	hres = info.lpDSBuffer[buf]->Unlock(pwrite[0],len[0],pwrite[1],len[1]);

	if(hres != DS_OK){
		eiDebugWriteFile("(eiSound::FillBuffer)Unlock failed.\n");
		return 0;
	}

	//---�Đ��\
	info.EnablePlay = 1;

	return 1;
}

//---�T�E���h�o�b�t�@�[���쐬
int eiSound::CreateBuffer(void)
{
	DSBUFFERDESC dsbdesc;
	PCMWAVEFORMAT pcmwf;
	HRESULT hres;

	memset(&pcmwf,0,sizeof(pcmwf));
	pcmwf.wf.wFormatTag = WAVE_FORMAT_PCM;
	pcmwf.wf.nChannels = info.wf.nChannels;
	pcmwf.wf.nSamplesPerSec = info.wf.nSamplesPerSec;
	pcmwf.wf.nBlockAlign = info.wf.nBlockAlign;
	pcmwf.wf.nAvgBytesPerSec = pcmwf.wf.nSamplesPerSec * pcmwf.wf.nBlockAlign;
	pcmwf.wBitsPerSample = info.wf.wBitsPerSample;

/*	char s[100];
	sprintf(s,"%d ,%d ,%d\n",info.wf.nSamplesPerSec,info.wf.nBlockAlign,info.wf.wBitsPerSample);
	eiDebugWriteFile(s);*/

	memset(&dsbdesc,0,sizeof(dsbdesc));
	dsbdesc.dwSize = sizeof(dsbdesc);
	dsbdesc.dwFlags = DSBCAPS_STATIC
			| DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY;
	dsbdesc.dwBufferBytes = info.PCMMemorySize;
	dsbdesc.lpwfxFormat = (LPWAVEFORMATEX)&pcmwf;

	hres = lpDS->CreateSoundBuffer(&dsbdesc,&info.lpDSBuffer[0],NULL);
	if(hres != DS_OK){
		eiDebugWriteFile("(eiSound::CreateBuffer)CreateSoundBuffer failed.\n");
		return 0;
	}

	return 1;
}

//---�Đ�
int eiSound::Play(int PlayFlag /* = 0*/)
{
	HRESULT hres = 0;

	if(!info.EnablePlay){
		//---�Đ��s�\��Ԃ�������
		return 1;
	}

	if(::DSMode & EISOUND_SILENCE){
		//---�T�C�����X��������
		return 1;
	}

	if(DSInitFlag == 0){
		//-------DirectSound���g���Ȃ����
		if(PlayFlag & EISOUND_PLAYLOOP){
			//---���[�v�Đ�
			PlaySound((LPCSTR)info.lpWaveMemory,0,SND_LOOP | SND_MEMORY | SND_NOWAIT | SND_ASYNC);
		} else {
			PlaySound((LPCSTR)info.lpWaveMemory,0,SND_MEMORY | SND_NOWAIT | SND_ASYNC);
		}
		return TRUE;
	}

	if((!(PlayFlag & EISOUND_PLAYLOOP) || (info.BufferCount == 1))){

		LPDIRECTSOUNDBUFFER lpDSB = GetPlayBuffer();

		if(lpDSB != NULL){
			//---�{�����[��
			if(::DSVolume != 255){
				lpDSB->SetVolume((LONG)DSSetVolume);
			}

			hres = lpDSB->Play(0,0,
				(PlayFlag & EISOUND_PLAYLOOP) ? DSBPLAY_LOOPING : 0);
		}
	}

	if(hres == TRUE)
		return TRUE;
	else
		return FALSE;
}

//---�Đ��\�ȃo�b�t�@�[�𓾂�
IDirectSoundBuffer* eiSound::GetPlayBuffer(void)
{
	LPDIRECTSOUNDBUFFER lpDSB = NULL;
	HRESULT hres;
	DWORD status;

	if(!info.EnablePlay){
		return NULL;
	}

	while(1){
		lpDSB = info.lpDSBuffer[info.BufferIndex];

		if(lpDSB != NULL){
			hres = lpDSB->GetStatus(&status);
			if(hres != DS_OK)
				status = 0;
			if((status & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING){
				if(info.BufferCount > 1){

					info.BufferIndex ++;
					if(info.BufferIndex >= info.BufferCount){
						info.BufferIndex = 0;
					}

					lpDSB = info.lpDSBuffer[info.BufferIndex];
					hres = lpDSB->GetStatus(&status);

					if((hres == DS_OK) && 
						(status & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING){
						lpDSB->Stop();
						lpDSB->SetCurrentPosition(0);
					}
				} else {
					//---�����o�b�t�@�[��������Ȃ�
					Stop();
					//---�V�����Đ����Ȃ���
					continue;
				}
			}

			if(lpDSB != NULL && (status & DSBSTATUS_BUFFERLOST)){
				hres = lpDSB->Restore();
				if((hres != DS_OK) || !(FillBuffer()) ){
					lpDSB = NULL;
				}
			}
		}
		break;
	}

	return lpDSB;
}
