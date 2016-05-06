SMIDIFUNC int smidiShortMessage(LPSMIDI_STREAM lpsmidi,int mode,BYTE d1,BYTE d2,BYTE d3)
{
	int a,code,ch,c = 0;
	BYTE data1 = d2,data2 = d3,msb,lsb;

	code = d1;
	ch = d1 & 0x0f;
	code=code & 0xf0;
if((mode & SMIDI_SHORTMSG_BACKUP)){
	if(code == 0xb0){
		//コントロールチェンジ
		if(data1 == 100)
			data1 = 98;
		if(data1 == 101)
			data1 = 99;
		if(data1 < 128){
			//値を保存
			if( !((data1 == 6 || data1 == 38) /*&& data2 == 0x7f*/)){
				lpsmidi->tr[ch].Control[data1] = data2;
				lpsmidi->tr[ch].ControlFlag[data1] = 1;
			}

		}
		if(data1 == 6 || data1 == 38){
			if(data1 == 6){
				c=0;
			} else if(data1 == 38){
				c=1;
			}
			//Data MSB
			msb = (BYTE)lpsmidi->tr[ch].Control[99];
			lsb = (BYTE)lpsmidi->tr[ch].Control[98];

			if(msb == 0x01 && lsb == 0x08){
				//ビブラートレイト
				lpsmidi->tr[ch].VibRate[c] = data2;
				LastTrackData[ch].VibRate[c] = data2;
			} else if(msb == 0x01 && lsb == 0x09){
				//ビブラートデプス
				lpsmidi->tr[ch].VibDepth[c] = data2;
				LastTrackData[ch].VibDepth[c] = data2;
			} else if(msb == 0x01 && lsb == 0x0a){
				//ビブラートディレイ
				lpsmidi->tr[ch].VibDelay[c] = data2;
				LastTrackData[ch].VibDelay[c] = data2;

			} else if(msb == 0x01 && lsb == 0x20){
				//ＴＶＦカットオフ周波数
				lpsmidi->tr[ch].TVFCutoff[c] = data2;
				LastTrackData[ch].TVFCutoff[c] = data2;
			} else if(msb == 0x01 && lsb == 0x21){
				//ＴＶＦレゾナンス
				lpsmidi->tr[ch].TVFResonance[c] = data2;
				LastTrackData[ch].TVFResonance[c] = data2;

			} else if(msb == 0x01 && lsb == 0x63){
				//アタックタイム
				lpsmidi->tr[ch].AtackTime[c] = data2;
				LastTrackData[ch].AtackTime[c] = data2;
			} else if(msb == 0x01 && lsb == 0x64){
				//ディケイタイム
				lpsmidi->tr[ch].DecayTime[c] = data2;
				LastTrackData[ch].DecayTime[c] = data2;
			} else if(msb == 0x01 && lsb == 0x66){
				//リリースタイム
				lpsmidi->tr[ch].ReleaseTime[c] = data2;
				LastTrackData[ch].ReleaseTime[c] = data2;

			} else if(msb == 0x00 && lsb == 0x00){
				//ピッチベンドセンシティビティー
				lpsmidi->tr[ch].PitchBendSensitibity[c] = data2;

			}
		}
	} else if(code == 0xc0){
		//プログラムチェンジ
		lpsmidi->tr[ch].Program = data1;
	} else if(code == 0xe0){
		//ピッチベンド
		lpsmidi->tr[ch].PitchBendHigh = data2;
		lpsmidi->tr[ch].PitchBendLow = data1;
	}
}
//	a = AcShortMsgEvent((BYTE)d1,(BYTE)d2,(BYTE)d3);
	DWORD		dwMsg;
	MMRESULT	ret;
	int err;
	
	a = 0;
	if((mode & SMIDI_SHORTMSG_SENDDATA)){
		dwMsg = MAKELONG( MAKEWORD( d1, d2 ), MAKEWORD( d3, 0 ) );
		ret = midiOutShortMsg( (HMIDIOUT)hStream, dwMsg );
		a = ret;
		switch( ret ) {
		case MMSYSERR_NOERROR:
			err = SMIDI_NOERROR;
			break;
		default:
			err = SMIDI_ER_SOMETHING;
			break;
		}
	}

	return a;
}

SMIDIFUNC int smidiLongMessage(LPSMIDI_STREAM lpsmidi,LPBYTE lpbuffer,int size)
{
	int a = 0;
	BYTE efxparam[30];
	DWORD s;
	
	if(!memcmp(lpbuffer,&MasterVolumeExclusive[0],8)){
		//マスターボリューム
		lpsmidi->MasterVolume = lpbuffer[8];
	}

//	a = AcSysExEvent(lpbuffer,(WORD)size);

	//DWORD の１６ビット目は設定フラッグ
	if(size >= 8){
		if(!memcmp(lpbuffer,&EFXType[0],8)){
			//ＥＦＸタイプ
			lpsmidi->EFXType = EFX_FLAG | 
				(lpbuffer[8] << 8) | (lpbuffer[9]);
		}
	}
	if(size >= 8){
		if(!memcmp(lpbuffer,&EFXOn[0],6) && (lpbuffer[6] & 0x40) 
			&& lpbuffer[7] == 0x22){
			//ＥＦＸオン、オフ
			a = lpbuffer[6] & 0x0f;
			//channel 1 -> 0
			a--;
			lpsmidi->tr[a].EFXOn = 1;
		}
	}

	if(size >= 8){
		memcpy(&efxparam[0],&EFXParam[0],11);
		for(a = 0;a < 20;a++){
			efxparam[7] = (BYTE)(a+3);
			if(!memcmp(lpbuffer,&efxparam[0],8)){
				//ＥＦＸパラメータ
				lpsmidi->EFXParam[a] = lpbuffer[8] | EFX_FLAG;
				break;
			}
		}
	}

	if(size >= 8){
		for(a = 0x17;a <= 0x1f;a++){
			efxparam[7] = (BYTE)a;
			if(!memcmp(lpbuffer,&efxparam[0],8)){
				//ＥＦＸパラメータ
				s = lpbuffer[8] | EFX_FLAG;

				switch(a){
				case 0x17:
					lpsmidi->EFXReverb = s;
					break;
				case 0x18:
					lpsmidi->EFXChorus = s;
					break;
				case 0x19:
					lpsmidi->EFXDelay = s;
					break;
				case 0x1b:
					lpsmidi->EFXSource1 = s;
					break;
				case 0x1c:
					lpsmidi->EFXDepth1 = s;
					break;
				case 0x1d:
					lpsmidi->EFXSource2 = s;
					break;
				case 0x1e:
					lpsmidi->EFXDepth2 = s;
					break;
				case 0x1f:
					lpsmidi->EFXEQSwitch = s;
					break;
				}
			}
		}
	}

	return SMIDI_NOERROR;
}

int smidiCheckSum(LPBYTE lpbuffer,int size)
{
	int a,c=0;

	for(a = 0;a < size;a++){
		c+=lpbuffer[a];
	}
	c =c % 128;
	c = 128 - c;

	return c;
}

int smidiSetEFXPart(LPSMIDI_STREAM lpsmidi,int ch,int mode)
{
	BYTE ex[20],s;

	memcpy(&ex[0],&EFXOn[0],8);
	s = (BYTE)(ch | 0x40); 
	ex[6] = s;

	return SMIDI_NOERROR;
}

//ハードボリューム
int smidiSetMasterVolume2(LPSMIDI_STREAM lpsmidi,int vl)
{
	BYTE ex[12];

	memcpy(&ex[0],&MasterVolumeExclusive[0],8);

	ex[8]=(BYTE)vl;
	ex[9]=(BYTE)smidiCheckSum(&ex[5],4);
	ex[10]=0xf7;

	SendMasterVolume = 1;

	memcpy(&SendMasterVolumeExclusive[0],&ex[0],11);

//	return smidiLongMessage(lpsmidi,&ex[0],11);

//	midiOutSetVolume(hStream,vl);
	return SMIDI_NOERROR;
}

//ソフトボリューム
SMIDIFUNC int smidiSetMasterVolume(LPSMIDI_STREAM lpsmidi,int vl)
{
	int a = 0,b;

	for(a = 0;a < SMIDI_TRACK_MAX;a++){
		b = 127 - lpsmidi->tr[a].Control[7];
		b = vl - b;
		if(b < 0)
			b = 0;
		if(b > 127)
			b = 127;

		smidiShortMessage(lpsmidi,SMIDI_SHORTMSG_SENDDATA,
			(BYTE)(0xb0 | a),0x07,(BYTE)b);

//		eiMsgBox("a");
	}
	return 0;
}

SMIDIFUNC int smidiProgram(LPSMIDI_STREAM lpsmidi,int ch,int program)
{
	int a;
	BYTE msg=0xc0 | (ch & 0x0f);

	a = smidiShortMessage(lpsmidi,SMIDI_SHORTMSG_ALL,msg,(BYTE)program,0);

	return a;
}

/*int smidiPitchBend(LPSMIDI_STREAM lpsmidi,int ch,int pitch)
{
	int a;
	BYTE msg=0xe0 | (ch & 0x0f),
		d1=(BYTE)((pitch & 0xff00) >,d2=(BYTE)(pitch & 0x00ff);

	a = smidiShortMessage(lpsmidi,msg,d1,d2);

	return a;
}*/

SMIDIFUNC int smidiControl(LPSMIDI_STREAM lpsmidi,int ch,int number,BYTE d1)
{
	int a;
	BYTE msg=0xb0 | (ch & 0x0f);

	a = smidiShortMessage(lpsmidi,SMIDI_SHORTMSG_ALL,msg,(BYTE)number,d1);

	return a;
}

SMIDIFUNC int smidiAllSoundOff(LPSMIDI_STREAM lpsmidi,int ch)
{
	return smidiControl(lpsmidi,ch,0x78,0x00);
}

SMIDIFUNC int smidiAllTrackSoundOff(LPSMIDI_STREAM lpsmidi)
{
	int a;

	for(a = 0;a < SMIDI_TRACK_MAX;a++){
		smidiAllSoundOff(lpsmidi,a);
	}

	return SMIDI_NOERROR;
}

SMIDIFUNC int smidiResetControl(LPSMIDI_STREAM lpsmidi,int ch)
{
	return smidiControl(lpsmidi,ch,0x79,0x00);
}

SMIDIFUNC int smidiAllTrackResetControl(LPSMIDI_STREAM lpsmidi)
{
	int a;

	for(a = 0;a < SMIDI_TRACK_MAX;a++){
		smidiResetControl(lpsmidi,a);
	}

	return SMIDI_NOERROR;
}

int smidiSendNRPN(LPSMIDI_STREAM lpsmidi,int ch,int msb,int lsb,int vh,int vl)
{
	int msg=0xb0 | (ch & 0x0f);

	smidiShortMessage(lpsmidi,SMIDI_SHORTMSG_ALL,(BYTE)msg,99,(BYTE)msb);
	smidiShortMessage(lpsmidi,SMIDI_SHORTMSG_ALL,(BYTE)msg,98,(BYTE)lsb);

	smidiShortMessage(lpsmidi,SMIDI_SHORTMSG_ALL,(BYTE)msg, 6,(BYTE)vh);
	smidiShortMessage(lpsmidi,SMIDI_SHORTMSG_ALL,(BYTE)msg,38,(BYTE)vl);

	smidiShortMessage(lpsmidi,SMIDI_SHORTMSG_ALL,(BYTE)msg,101,(BYTE)0x7f);
	smidiShortMessage(lpsmidi,SMIDI_SHORTMSG_ALL,(BYTE)msg,100,(BYTE)0x7f);
	return SMIDI_NOERROR;
}

int smidiSendRPN(LPSMIDI_STREAM lpsmidi,int ch,int msb,int lsb,int vh,int vl)
{
	int msg=0xb0 | (ch & 0x0f);

	smidiShortMessage(lpsmidi,SMIDI_SHORTMSG_ALL,(BYTE)msg,101,(BYTE)msb);
	smidiShortMessage(lpsmidi,SMIDI_SHORTMSG_ALL,(BYTE)msg,100,(BYTE)lsb);

	smidiShortMessage(lpsmidi,SMIDI_SHORTMSG_ALL,(BYTE)msg, 6,(BYTE)vh);
	smidiShortMessage(lpsmidi,SMIDI_SHORTMSG_ALL,(BYTE)msg,38,(BYTE)vl);

	smidiShortMessage(lpsmidi,SMIDI_SHORTMSG_ALL,(BYTE)msg,101,(BYTE)0x7f);
	smidiShortMessage(lpsmidi,SMIDI_SHORTMSG_ALL,(BYTE)msg,100,(BYTE)0x7f);
	return SMIDI_NOERROR;
}

SMIDIFUNC int smidiSendAllControl(LPSMIDI_STREAM lpsmidi)
{
	int tr,ctl;
	BYTE msg;
	
	for(tr = 0;tr < SMIDI_TRACK_MAX;tr++){
		//コントロール
		smidiResetControl(lpsmidi,tr);
		for(ctl = 0;ctl < SMIDI_CONTROL_MAX;ctl++){
//			if(ctl == 98 || ctl == 99 //NRPN MSB/LSB
//				|| ctl == 100 || ctl == 101 //RPN MSB/LSB
			if(ctl == 6 || ctl == 38) //Data Entry
				continue;
			if(lpsmidi->tr[tr].ControlFlag[ctl]){
				//もしコントローラが書き込まれていたなら
				smidiControl(lpsmidi,tr,ctl,(BYTE)lpsmidi->tr[tr].Control[ctl]);
			}
		}
		//プログラム
		smidiProgram(lpsmidi,tr,lpsmidi->tr[tr].Program);
		//ピッチベンド
//		if(lpsmidi->tr[tr].PitchBendFlag){
			msg=0xe0 | (tr & 0x0f);
			smidiShortMessage(lpsmidi,SMIDI_SHORTMSG_ALL,msg,
				(BYTE)lpsmidi->tr[tr].PitchBendLow,(BYTE)lpsmidi->tr[tr].PitchBendHigh);
//		}

		//NRPN
		//---------------------
		smidiSendNRPN(lpsmidi,tr,0x01,0x08,
			lpsmidi->tr[tr].VibRate[0],
			lpsmidi->tr[tr].VibRate[1]);
		//---------------------
		smidiSendNRPN(lpsmidi,tr,0x01,0x09,
			lpsmidi->tr[tr].VibDepth[0],
			lpsmidi->tr[tr].VibDepth[1]);
		//---------------------
		smidiSendNRPN(lpsmidi,tr,0x01,0x0a,
			lpsmidi->tr[tr].VibDelay[0],
			lpsmidi->tr[tr].VibDelay[1]);

		//---------------------
		smidiSendNRPN(lpsmidi,tr,0x01,0x20,
			lpsmidi->tr[tr].TVFCutoff[0],
			lpsmidi->tr[tr].TVFCutoff[1]);
		//---------------------
		smidiSendNRPN(lpsmidi,tr,0x01,0x21,
			lpsmidi->tr[tr].TVFResonance[0],
			lpsmidi->tr[tr].TVFResonance[1]);

		//---------------------
		smidiSendNRPN(lpsmidi,tr,0x01,0x63,
			lpsmidi->tr[tr].AtackTime[0],
			lpsmidi->tr[tr].AtackTime[1]);
		//---------------------
		smidiSendNRPN(lpsmidi,tr,0x01,0x64,
			lpsmidi->tr[tr].DecayTime[0],
			lpsmidi->tr[tr].DecayTime[1]);
		//---------------------
		smidiSendNRPN(lpsmidi,tr,0x01,0x66,
			lpsmidi->tr[tr].ReleaseTime[0],
			lpsmidi->tr[tr].ReleaseTime[1]);


		//---------------------
		smidiSendRPN(lpsmidi,tr,0x00,0x00,
			lpsmidi->tr[tr].PitchBendSensitibity[0],
			lpsmidi->tr[tr].PitchBendSensitibity[1]);

		Sleep(10);
	}
	//マスターボリューム
//	smidiSetMasterVolume(lpsmidi,lpsmidi->MasterVolume);

	return SMIDI_NOERROR;
}

