DWORD MidiPlayProc(
			int FuncMode,
			int past_time,
			UINT uTimerID, UINT uMsg,
			DWORD dwUser, DWORD dw1, DWORD dw2);

//-----�e���|�ݒ�i�}�C�N���Z�J���h�Łj
int smidiSetTempoLowLevel(LPSMIDI_STREAM lpsmidi,int tempo)
{
	int tp;

	smidiCheckPointer(lpsmidi);

	tp = lpsmidi->Tempo;

	lpsmidi->Tempo = tempo;
	if(lpsmidi->Division)
		lpsmidi->MidiClock = lpsmidi->Tempo / lpsmidi->Division;

	return tp;
}

//-----�e���|�ݒ�i�ʏ�̂S�������Łj
SMIDIFUNC int smidiSetTempo(LPSMIDI_STREAM lpsmidi,int tempo)
{
	int tp,a;

	smidiCheckPointer(lpsmidi);

	if(tempo < 30 || tempo > 500)
		return SMIDI_ER_OVERTEMPO;

	tp = 60*1000000 / tempo;
	a = smidiSetTempoLowLevel(lpsmidi , tp);
	if(a)
		a = 60*1000000 / a;

	return a;
}

SMIDIFUNC int smidiStop(LPSMIDI_STREAM lpsmidi)
{
	smidiCheckPointer(lpsmidi);

	if(lpsmidiActiveStream != lpsmidi)
		return SMIDI_ER_SOMETHING;
	if(!lpsmidi->PlayFlag)
		return SMIDI_NOERROR;

	lpsmidi->PlayFlag = 0;
	lpsmidi->NextDeltaTime = lpsmidi->DeltaTime = 0;
	lpsmidi->DeltaCount = 0;
	VolumeFade = 0;

	smidiAllTrackSoundOff(lpsmidi);


	StreamStop();
	lpsmidiActiveStream = 0;

	//�t�F�[�h�C���A�A�E�g���~�߂�
	VolumeFade = 0;

	return SMIDI_NOERROR;
}

SMIDIFUNC int smidiPlay(LPSMIDI_STREAM lpsmidi)
{
	if(!lpsmidi)
		return SMIDI_ER_SOMETHING;
	if(!lpsmidi->lpMidiData)
		return SMIDI_ER_SOMETHING;
	if(lpsmidi->PlayFlag)
		return SMIDI_ER_SOMETHING;

	if(lpsmidiActiveStream){
		if(lpsmidiActiveStream != lpsmidi && lpsmidiActiveStream->PlayFlag)
			//�����łȂ��N�������t���Ȃ�~�߂�
			smidiStop(lpsmidiActiveStream);
	}

	lpsmidiActiveStream = lpsmidi;

	//�}�X�^�[�{�����[�����Z�b�g
	smidiSetMasterVolume2(lpsmidi,lpsmidi->MasterVolume);

	StreamClose();
	StreamOpen();

	if(!lpsmidi->FirstPlayFlag){
		//���񉉑t�łȂ����
		smidiSendAllControl(lpsmidi);
		Sleep(400);
	} else {
		//---���񉉑t
		int a,tr;

		//�s�b�`�x���h�A�G�N�X�v���b�V������߂�
		for(a = 0;a < SMIDI_TRACK_MAX;a ++){
			smidiResetControl(lpsmidi,a);
			Sleep(1);

			tr = a;
			//NRPN
			//---------------------
			if(LastTrackData[tr].VibRate[0] != 64){
				smidiSendNRPN(lpsmidi,tr,0x01,0x08,
					lpsmidi->tr[tr].VibRate[0],
					lpsmidi->tr[tr].VibRate[1]);
				Sleep(1);
			}
			//---------------------
			if(LastTrackData[tr].VibDepth[0] != 64){
				smidiSendNRPN(lpsmidi,tr,0x01,0x09,
					lpsmidi->tr[tr].VibDepth[0],
					lpsmidi->tr[tr].VibDepth[1]);
				Sleep(1);
			}
			//---------------------
			if(LastTrackData[tr].VibDelay[0] != 64){
				smidiSendNRPN(lpsmidi,tr,0x01,0x0a,
					lpsmidi->tr[tr].VibDelay[0],
					lpsmidi->tr[tr].VibDelay[1]);
				Sleep(1);
			}

			//---------------------
			if(LastTrackData[tr].TVFCutoff[0] != 64){
				smidiSendNRPN(lpsmidi,tr,0x01,0x20,
					lpsmidi->tr[tr].TVFCutoff[0],
					lpsmidi->tr[tr].TVFCutoff[1]);
				Sleep(1);
			}
			//---------------------
			if(LastTrackData[tr].TVFResonance[0] != 64){
				smidiSendNRPN(lpsmidi,tr,0x01,0x21,
					lpsmidi->tr[tr].TVFResonance[0],
					lpsmidi->tr[tr].TVFResonance[1]);
				Sleep(1);
			}

			//---------------------
			if(LastTrackData[tr].AtackTime[0] != 64){
				smidiSendNRPN(lpsmidi,tr,0x01,0x63,
					lpsmidi->tr[tr].AtackTime[0],
					lpsmidi->tr[tr].AtackTime[1]);
				Sleep(1);
			}
			//---------------------
			if(LastTrackData[tr].DecayTime[0] != 64){
				smidiSendNRPN(lpsmidi,tr,0x01,0x64,
					lpsmidi->tr[tr].DecayTime[0],
					lpsmidi->tr[tr].DecayTime[1]);
				Sleep(1);
			}
			//---------------------
			if(LastTrackData[tr].ReleaseTime[0] != 64){
				smidiSendNRPN(lpsmidi,tr,0x01,0x66,
					lpsmidi->tr[tr].ReleaseTime[0],
					lpsmidi->tr[tr].ReleaseTime[1]);
				Sleep(1);
			}
		}
//		Sleep(100);

/*		for(int tr = 0;tr < 16;tr ++){
			BYTE msg = 0xe0 | (tr & 0x0f);
			smidiShortMessage(lpsmidi,SMIDI_SHORTMSG_ALL,msg,0x00,0x40);
		}*/
	}
	StreamReady(lpsmidi);

	lpsmidi->FirstPlayFlag = 0;
	
	Sleep(50);
	VolumeFade = 0;
	StreamPlay();
	
	//---�J�E���g�J�n
	smidiet.Reset();

	lpsmidi->PlayFlag = 1;

	return SMIDI_NOERROR;
}

#define SMIDI_FUNCMODE_TIMER 0
#define SMIDI_FUNCMODE_CALLBACK 1

//-----------------------------------------------------------
//---------�̐S�v�̉��t�֐�
//-----------------------------------------------------------
DWORD MidiTimerProc(int past_time)
{
	return MidiPlayProc(SMIDI_FUNCMODE_TIMER,past_time,0,0,0,0,0);
}

DWORD CALLBACK MidiTimerCallBack(UINT uTimerID, UINT uMsg,
							DWORD dwUser, DWORD dw1, DWORD dw2)
{
	return MidiPlayProc(SMIDI_FUNCMODE_CALLBACK,0,
		uTimerID,uMsg,dwUser,dw1,dw2);
}

/*
#ifdef SMIDITHREAD
DWORD MidiTimerProc(int past_time)
#else
DWORD CALLBACK MidiTimerProc(UINT uTimerID, UINT uMsg,
							DWORD dwUser, DWORD dw1, DWORD dw2)
#endif*/


DWORD MidiPlayProc(
			int FuncMode,
			int past_time,
			UINT uTimerID, UINT uMsg,
			DWORD dwUser, DWORD dw1, DWORD dw2)
{
	LPSMIDI_STREAM lpsmidi=lpsmidiActiveStream;
	int a,c,extype=0,delta_size = 0,loop_count,lp;
	static BYTE exclusive[512];
	LPBYTE lpevent;
	int size,event;
	WORD data1=0,data2=0;
	UINT sub;
	static KeepTime = -1;
	
	if(lpsmidi == NULL){
		//�|�C���^���m�t�k�k�Ȃ�
		VolumeFade = 0;
		return 1;
	}
	if(!lpsmidi->PlayFlag){
		//�Đ����łȂ��Ȃ�
		//---�{�����[���ω��Ȃǂ��I�t
		VolumeFade = 0;
		return 1;
	}

//------------------------�{�����[���A�t�F�[�h�C���A�A�E�g
	if(VolumeFade){
		FadeCount+=past_time;
		if(FadeCount >= FadeSpeed){
			if(VolumeFade == 1){
				if(++lpsmidi->MasterVolume >= (DWORD)FadeLimitVolume){
					lpsmidi->MasterVolume = FadeLimitVolume;
					VolumeFade = 0;
				}
				smidiSetMasterVolume(lpsmidi , lpsmidi->MasterVolume);
			} else if(VolumeFade == 2){
				a = lpsmidi->MasterVolume;
				if(--a <= FadeLimitVolume){
					a = FadeLimitVolume;
					VolumeFade = 0;
				}
				lpsmidi->MasterVolume = a;
				smidiSetMasterVolume(lpsmidi , lpsmidi->MasterVolume);
			}
			FadeCount = 0;
		}
	}

	LPBYTE lpMidiData = lpsmidi->lpBackMidiData;
	int count;
	
	//���݂̃X�g���[���̈ʒu
	count = StreamGetPoint();
//------------------------���t����

static int Status = 0,LastStatus = 0x80,DeltaTime;

while(((int)(lpsmidi->PlayCount - lpsmidi->OffsetPlayCount)
	  / ((int)lpsmidi->Division / 4) ) <= count){
	
	if(lpsmidi->LateForExclusiveDelta){
		//�G�N�X�N���[�V�u���M�ɂ�鉉�t�̒x����C��
		lpsmidi->LateForExclusiveDelta--;
	} else {
		lpsmidi->PlayCount++;
		lpsmidi->DeltaTime--;
	}

	if(lpsmidi->DeltaTime > 0){
		//�܂����̃C�x���g�܂Ŏ��Ԃ������
			continue;
	}

	while(1){
		event=0;
		data1=0;
		data2=0;

		if(lpsmidi->lpBackMidiData - lpsmidi->lpStartMidiData >= lpsmidi->MidiDataSize){
			break;
		}

		Status = *(lpsmidi->lpBackMidiData);//---����
		lpevent = lpsmidi->lpBackMidiData;

		if(!(Status & 0x80)){
			Status = LastStatus;
		} else {
			if((Status & 0xf0) != 0xf0){
				lpsmidi->lpBackMidiData ++;
				LastStatus = Status;
			}
		}
		c = Status;
		do {
			if((c & 0xf0) != 0xf0){
		//---------�ʏ탁�b�Z�[�W---------------------------
				size = StatusSize[Status >> 4];

				event = SMIDI_IVENT_SHORTMSG;
				data1 = data2 = 0;
				if (size >= 0) {
				}
				if(size >= 1){
					data1 = *(BYTE *)(lpsmidi->lpBackMidiData);
				}
				if(size >= 2){
					data2 = *(BYTE *)(lpsmidi->lpBackMidiData+1);
				}
			} else {
				switch(Status){
				case 0xf0:
					//�G�N�X�N���[�V�u
					event = SMIDI_IVENT_LONGMSG;
					extype = 1;
					size = GetValData2(lpsmidi->lpBackMidiData+1, &a);
					delta_size=a;

					lpevent = lpsmidi->lpBackMidiData;
					lpsmidi->lpBackMidiData += size + a + 1;
					continue;
//					goto ReadDelta1;
				case 0xf7:
					//�G�N�X�N���[�V�u
					event = SMIDI_IVENT_LONGMSG;
					extype = 0;
					size = GetValData2(lpsmidi->lpBackMidiData+1, &a);
					delta_size = a;

					lpevent = lpsmidi->lpBackMidiData+1+a;
					lpsmidi->lpBackMidiData += size + a + 1;
					continue;
//					goto ReadDelta1;
				case 0xf1:
					event = SMIDI_IVENT_OTHER;
				case 0xf3:
					event= SMIDI_IVENT_OTHER;
					size = 2;
					break;
				case 0xF2:
					event = SMIDI_IVENT_OTHER;
					size = 3;
					break;
				case 0xff:
					//���^�C�x���g
					event = SMIDI_IVENT_META;
					size = GetValData2(lpsmidi->lpBackMidiData + 2, &a) + 1;
					size += a + 1;
					switch (lpsmidi->lpBackMidiData[1]){
					case 0x01:
					case 0x02:
					case 0x03:
					case 0x04:
					case 0x05:
					case 0x06:
					case 0x07:
/*					if (lpsmidi->lpBackMidiData[2] == 1) {
						if (lpsmidi->lpBackMidiData[3] == 'S') {
							//>lpLoopStart = lpDataPointer;
						} else if (lpsmidi->lpBackMidiData[3] == 'E') {
	//						if (pLoopStart != NULL)
	//							pDataPointer = pLoopStart;
						}
					}*/
						break;
					case 0x2f://�I��
						event=SMIDI_IVENT_ENDOFTRACK;
						if((PlayMode & SMIDI_LOOPPLAY)){
							//���[�v�v���C������Ȃ�
							lpsmidi->lpBackMidiData = lpsmidi->lpStartMidiData;
							lpsmidi->DeltaTime = GetValData(&lpsmidi->lpBackMidiData);
//							DeltaCount = DeltaTime = 0;
//							loop_count=1;
//							goto PLAY_START;
						} else {
//							smidiStop(lpsmidi);
						}

						//---�֐��I������
						loop_count=0;
						//�Ō�̌����ʒu��ۑ�
						lp=0;
						return 1;
//						goto EndRead;
					case 0x51:
						event=SMIDI_IVENT_TEMPO;
					
						c = (long)((((DWORD)*(lpsmidi->lpBackMidiData + 3)) << 16)
							+ (((WORD)*(lpsmidi->lpBackMidiData + 4)) << 8)
							+ *(lpsmidi->lpBackMidiData + 5));
						smidiSetTempoLowLevel(lpsmidi,c);
						lpsmidi->MidiClock = lpsmidi->Tempo / lpsmidi->Division;
						break;
					case 0x21: //port
						break;
					}
					lpsmidi->lpBackMidiData += size;
					continue;
//					goto ReadDelta1;
				default:
					size = 1;
				
					break;
				}
			}
			lpsmidi->lpBackMidiData += size;
		} while(0);

//ReadDelta1:
		//���b�Z�[�W���M
		sub=0;
		if(event == SMIDI_IVENT_SHORTMSG){
			smidiShortMessage(
				lpsmidi,SMIDI_SHORTMSG_BACKUPONLY,
				(BYTE)Status,
				(BYTE)data1 & 0x7f,
				(BYTE)data2 & 0x7f);
		} else if(event == SMIDI_IVENT_LONGMSG){
			if(extype == 1){
				memcpy(&exclusive[1],lpevent +(delta_size+1),size);
				exclusive[0]=*lpevent;
				size++;
			} else {
				memcpy(&exclusive[0],lpevent ,size);
			}
			smidiLongMessage(lpsmidi,&exclusive[0],size);
		}

		a = GetValData(&lpsmidi->lpBackMidiData);

		lpsmidi->DeltaTime = a;

		if(lpsmidi->DeltaTime){
			//�f���^�^�C�����O�łȂ�������ʂ���
			break;
		}

		break;
	}
//	lpsmidi->lpLastMidiData = lpsmidi->lpBackMidiData;
}

//EndRead:

	//---�֐��I������
	loop_count=0;

	//�Ō�̌����ʒu��ۑ�
	lp=0;
	return 1;
}
