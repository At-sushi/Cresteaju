
#define SHORTMSG (MEVT_SHORTMSG << 24)
#define LONGMSG (MEVT_LONGMSG << 24)

#define MIDIBUF_MAX_BYTES 10000

#define MIDI_STATUS_STOPPING 2
#define MIDI_STATUS_WAITINGFOREND 1

HMIDISTRM hStream = NULL;
MIDIHDR MidiHdr[2];
BYTE MidiBuf[2][MIDIBUF_MAX_BYTES];
int nBufSide;
HANDLE hMidiData;
LPBYTE pLoopStart = NULL;
BOOL Initialized = FALSE;

void FillBuffer(int side);

void InitStreamData(LPSMIDI_STREAM lpsmidi)
{
	lpsmidi->LastStatus = 0x80;
	lpsmidi->OffsetPlayCount = 0;
}
int smidiSetMasterVolume2(LPSMIDI_STREAM lpsmidi,int vl);

void StreamReady(LPSMIDI_STREAM lpsmidi)
{
	MIDIPROPTIMEDIV mptd;
	MIDIPROPTEMPO mpt;

	if(lpsmidi->lpBackMidiData){
		lpsmidi->lpMidiData = lpsmidi->lpBackMidiData;
	}

	nBufSide = 0;
	FillBuffer(0);
	FillBuffer(1);
	nBufSide = 0;
	lpsmidi->StreamStatus = 0;
	mpt.cbStruct = sizeof(mpt);
	mpt.dwTempo = lpsmidi->Tempo;
	mptd.cbStruct = sizeof(mptd);
	mptd.dwTimeDiv = lpsmidi->Division;
	midiStreamProperty(hStream, (LPBYTE)&mptd, MIDIPROP_SET|MIDIPROP_TIMEDIV);
	midiStreamProperty(hStream, (LPBYTE)&mpt, MIDIPROP_SET|MIDIPROP_TEMPO);
}

void CALLBACK MidiProc(HMIDIOUT h, WORD uMsg, int dwUser, int dw1, int dw2)
{
	if(!lpsmidiActiveStream)
		return;

	if(uMsg == MOM_DONE){
		if(lpsmidiActiveStream->StreamStatus){
			return;
		}

		FillBuffer(nBufSide);
		nBufSide++;
		nBufSide &= 1;
		lpsmidiActiveStream->nBufSide = nBufSide;
	}
}

int StreamGetPoint(void)
{
	MMTIME mt;

	mt.wType = TIME_MIDI;

	midiStreamPosition(hStream,&mt,sizeof(mt));

	return mt.u.midi.songptrpos;
}

int StreamClose(void)
{
	int i;

	if(!hStream)
		return 0;

	for(i = 0; i < 2; i++){
		if(hStream != NULL){
			midiOutUnprepareHeader((HMIDIOUT)hStream, &MidiHdr[i], sizeof(MIDIHDR));
		}
	}
	midiStreamClose(hStream);

	hStream = 0;
	Initialized = FALSE;

	return 0;
}

int Finish()
{
	if (!Initialized)
		return 0;
	StreamClose();
	Initialized = FALSE;
	return 0;
}

int StreamOpen(void)
{
	int i;
	UINT a;

	if(hStream)
		return 0;
	i = -1;
	a = (UINT)i;
	a = MIDI_MAPPER;

	if(midiStreamOpen(&hStream, &a,
		1, (DWORD)MidiProc, 0, CALLBACK_FUNCTION)
		!= MMSYSERR_NOERROR){

		Finish();
		return 1;
	}

	for(i = 0; i < 2; i++){
		MidiHdr[i].lpData = (char*)MidiBuf[i];
		MidiHdr[i].dwBufferLength = MIDIBUF_MAX_BYTES;
		MidiHdr[i].dwFlags = 0;
		midiOutPrepareHeader((HMIDIOUT)hStream, &MidiHdr[i], sizeof(MIDIHDR));
	}

	return 0;
}

int StreamInit()
{
	if(Initialized)
		return 0;
	Initialized = TRUE;

	return StreamOpen();
}

int StreamPlay()
{
	if(StreamInit())
		return 1;

	midiStreamRestart(hStream);
	return 0;
}

void StreamStop()
{
	int a;

	if(!lpsmidiActiveStream)
		return;

	lpsmidiActiveStream->StreamStatus = 1;

	a = StreamGetPoint();
	lpsmidiActiveStream->OffsetPlayCount +=( a * ((int)lpsmidiActiveStream->Division / 4) );

	midiStreamStop(hStream);
	Finish();
}

#define END_FUNC() {\
	MidiHdr[side].dwFlags = MHDR_PREPARED;\
	if ((mmr = midiStreamOut(hStream, &MidiHdr[side], sizeof(MIDIHDR)))\
		!= MMSYSERR_NOERROR) {\
	}\
}

void FillBuffer(int side)
{
	int			i, a,tempo;
	long 		la;
//	unsigned	status;
	MIDIEVENT*	pmevt;
	BYTE*		p;
	MMRESULT	mmr;
	LPSMIDI_STREAM lpsmidi = lpsmidiActiveStream;

	if(!lpsmidi)
		return;
	
	MidiHdr[side].dwBytesRecorded = 0;
	while(1){
		if(SendMasterVolume){
			//マスターボリューム
			int bytes, pb;

			SendMasterVolume = 0;

			//la = GetValData2(lpsmidi->lpMidiData+1, &a);
			la = 10;
			bytes = la + 1;
			pb = 12 + ((bytes + 3) & 0xFFFC);
			if (MidiHdr[side].dwBytesRecorded + pb >= MIDIBUF_MAX_BYTES) {
				//---関数終了処理
				END_FUNC();
				return;
//				break;
			}
			pmevt = (MIDIEVENT*)(MidiBuf[side] + MidiHdr[side].dwBytesRecorded);
			MidiHdr[side].dwBytesRecorded += pb;
			pmevt->dwDeltaTime = 0;//deltatime;
			pmevt->dwStreamID = 0;
			pmevt->dwEvent = MEVT_F_LONG|LONGMSG|bytes;
			p = (BYTE*)&pmevt->dwParms;
			*(p++) = 0xF0;
			memcpy(p,&SendMasterVolumeExclusive[1], la);
			p += la;
			memset(p, 0, pb - 12 - bytes);
			
			lpsmidi->LateForExclusiveDelta += 0;
			//lpsmidi->lpMidiData += la + a + 1;
			//goto ReadDelta1;
			continue;
		}
/*		if(SendAllControl){
			la = StatusSize[lpsmidi->Status >> 4];
			if (MidiHdr[side].dwBytesRecorded + 12 >= MIDIBUF_MAX_BYTES) {
				break;
			}
			pmevt = (MIDIEVENT*)(MidiBuf[side] + MidiHdr[side].dwBytesRecorded);
			MidiHdr[side].dwBytesRecorded += 12;
			pmevt->dwDeltaTime = 0;
			pmevt->dwStreamID = 0;
			pmevt->dwEvent = MEVT_F_SHORT|SHORTMSG;
			pmevt->dwEvent |= lpsmidi->Status;

			SendAllControl = 0;
		}*/

		if(!((lpsmidi->Status = *lpsmidi->lpMidiData) & 0x80)){
			lpsmidi->Status = lpsmidi->LastStatus;
		} else {
			if((lpsmidi->Status & 0xF0) != 0xF0) {
				lpsmidi->lpMidiData++;
				lpsmidi->LastStatus = lpsmidi->Status;
			}
		}

		do {
			if((i = lpsmidi->Status & 0xF0) != 0xF0){
				la = StatusSize[lpsmidi->Status >> 4];
				if(MidiHdr[side].dwBytesRecorded + 12 >= MIDIBUF_MAX_BYTES){
					//---関数終了処理
					END_FUNC();
					return;
				}
				pmevt = (MIDIEVENT*)(MidiBuf[side] + MidiHdr[side].dwBytesRecorded);
				MidiHdr[side].dwBytesRecorded += 12;
				pmevt->dwDeltaTime = lpsmidi->dwDeltaTime;
			
				lpsmidi->dwDeltaTime = 0;

				pmevt->dwStreamID = 0;
				pmevt->dwEvent = MEVT_F_SHORT|SHORTMSG;
				if(la == 0){
					pmevt->dwEvent |= lpsmidi->Status;
				} else if(la == 1){
					pmevt->dwEvent |= (((WORD)*(BYTE*)lpsmidi->lpMidiData) << 8) | lpsmidi->Status;
				} else if(la == 2){
					pmevt->dwEvent |= (((DWORD)*(WORD*)lpsmidi->lpMidiData)<< 8) | lpsmidi->Status;
				}
			} else {
				int bytes, pb;
				switch(lpsmidi->Status){
				case 0xF0://エクスクルーシブ
					la = GetValData2(lpsmidi->lpMidiData+1, &a);
					bytes = la + 1;
					pb = 12 + ((bytes + 3) & 0xFFFC);
					if(MidiHdr[side].dwBytesRecorded + pb >= MIDIBUF_MAX_BYTES){
						lpsmidi->lpMidiData--;
						break;
					}
					pmevt = (MIDIEVENT*)(MidiBuf[side] + MidiHdr[side].dwBytesRecorded);
					MidiHdr[side].dwBytesRecorded += pb;
					pmevt->dwDeltaTime = lpsmidi->dwDeltaTime;
					lpsmidi->dwDeltaTime = 0;
					pmevt->dwStreamID = 0;
					pmevt->dwEvent = MEVT_F_LONG|LONGMSG|bytes;
					p = (BYTE*)&pmevt->dwParms;
					*(p++) = 0xF0;
					memcpy(p, lpsmidi->lpMidiData+2, la);
					p += la;
					memset(p, 0, pb - 12 - bytes);
					lpsmidi->lpMidiData += la + a + 1;
					continue;
//					goto ReadDelta1;
				case 0xF7://エクスクルーシブ
					la = GetValData2(lpsmidi->lpMidiData+1, &a);
					lpsmidi->lpMidiData += la + a + 1;
					continue;
//					goto ReadDelta1;
				case 0xF1:
				case 0xF3:
					la = 2;
					break;
				case 0xF2:
					la = 3;
					break;
				case 0xFF:
					//メタイベント
					la = GetValData2(lpsmidi->lpMidiData + 2, &a) + 1;
					la += a + 1;
					switch (lpsmidi->lpMidiData[1]){
					case 0x01:
					case 0x02:
					case 0x03:
					case 0x04:
					case 0x05:
					case 0x06:
					case 0x07:
						break;
					case 0x2F:
						if((PlayMode & SMIDI_LOOPPLAY)){
							//---ループプレイをするなら
							lpsmidi->lpMidiData = lpsmidi->lpStartMidiData;
							lpsmidi->dwDeltaTime = GetValData(&lpsmidi->lpMidiData);
							break;
						} else {
							lpsmidi->StreamStatus = MIDI_STATUS_WAITINGFOREND;
//							smidiStop(lpsmidi);
						}
						//---関数終了処理
						END_FUNC();
						return;
//						goto EndRead;

						case 0x51:
						tempo = (long)((((DWORD)*(lpsmidi->lpMidiData + 3)) << 16)
							+ (((WORD)*(lpsmidi->lpMidiData + 4)) << 8)
							+ *(lpsmidi->lpMidiData + 5));
						if(MidiHdr[side].dwBytesRecorded + 12 >= MIDIBUF_MAX_BYTES){
							break;
						}
						pmevt = (MIDIEVENT*)(MidiBuf[side] + MidiHdr[side].dwBytesRecorded);
						MidiHdr[side].dwBytesRecorded += 12;
						pmevt->dwDeltaTime = lpsmidi->dwDeltaTime;
						lpsmidi->dwDeltaTime = 0;
						pmevt->dwStreamID = 0;
						pmevt->dwEvent = MEVT_F_SHORT|((DWORD)MEVT_TEMPO<<24)|tempo;
						break;
					case 0x21: //port
						break;
					}
					lpsmidi->lpMidiData += la;
					continue;
//					goto ReadDelta1;
				default:
					la = 1;
					break;
				}
			}
			lpsmidi->lpMidiData += la;
		} while(0);

//ReadDelta1:
		lpsmidi->dwDeltaTime += GetValData(&lpsmidi->lpMidiData);
	}
//EndRead:
	//---関数終了処理
	END_FUNC();
}
