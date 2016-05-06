#ifndef EISOUND_H
#define EISOUND_H

#define EISOUND_PLAYLOOP 0x01

typedef struct {
	EIMEMORY hPCMMemory,hWaveMemory;
	BYTE *lpPCMMemory,*lpWaveMemory;

	DWORD PCMMemorySize;
	WAVEFORMATEX wf;
	int BufferCount;
	int BufferIndex;
	int EnablePlay;

	LPDIRECTSOUNDBUFFER lpDSBuffer[EISOUND_BUFFER_MAX];
} EISOUND_INFO, *LPEISOUND_INFO;

//---ƒTƒEƒ“ƒh
class EI_API eiSound
{
public:

	eiSound(void);
	~eiSound();

	void Release(void);

	int Read(EISTR *name,EISTR *slname,int mode,int BufferCount = 1);
	int Play(int PlayFlag = 0);
	int Stop(void);
	void SetPan(void);
private:
	int FillBuffer(void);
	int CreateBuffer(void);
	IDirectSoundBuffer* GetPlayBuffer(void);

	EISOUND_INFO info;
};

#endif /* EISOUND_H */
