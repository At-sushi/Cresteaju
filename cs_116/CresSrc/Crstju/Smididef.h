//------ivent
#define SMIDI_IVENT_SHORTMSG 1
#define SMIDI_IVENT_LONGMSG 2
#define SMIDI_IVENT_META 3
#define SMIDI_IVENT_EXCLUSIVE 4
#define SMIDI_IVENT_TEMPO 5
#define SMIDI_IVENT_ENDOFTRACK 6
#define SMIDI_IVENT_OTHER 31

//------error
#define SMIDI_NOERROR 0
//#define SMIDI_ER_NOTHING 0
#define SMIDI_ER_SOMETHING 1
#define SMIDI_ER_CANTOPEN 2
#define SMIDI_ER_NOMEMORY 3
#define SMIDI_ER_OVERTEMPO 5

//------other
#define SMIDI_TRACK_MAX 16
#define SMIDI_CONTROL_MAX 127

#define SMIDI_DELTACOUNT 1000

//-----play mode
#define SMIDI_LOOPPLAY 0x0001

#define SMIDI_SHORTMSG_BACKUP 0x01
#define SMIDI_SHORTMSG_SENDDATA 0x02

#define SMIDI_SHORTMSG_BACKUPONLY (SMIDI_SHORTMSG_BACKUP)
#define SMIDI_SHORTMSG_ALL 0xffff

//-----message
#define SMIDI_NOMESSAGE 0
#define SMIDI_MES_PLAY 1
#define SMIDI_MES_STOP 2
//#define SMIDI_MES_ 3
#define SMIDI_MES_EXIT 255

#define HEADER_SIZE 4

#define EFX_FLAG ((DWORD)0x00010000)

typedef struct MIDIFILEHEADER_TAG
{
	BYTE	Header[4];
	DWORD	HeaderLength;
	WORD	Format;
	WORD	Tracks;
	WORD	Division;
} MIDIFILEHEADER;
//--------------------------------------------------------------
//--------------------------------------------------------------

typedef struct SMIDI_TRACK_INFO_TAG{
	DWORD DrumTrack,Instrument;

	//ÉRÉìÉgÉçÅ[Éâ
	DWORD Control[SMIDI_CONTROL_MAX],ControlFlag[SMIDI_CONTROL_MAX];
	DWORD Program;
	DWORD  PitchBendHigh,PitchBendLow,PitchBendFlag;

	DWORD VibRate[2],VibDepth[2],VibDelay[2];
	DWORD TVFCutoff[2],TVFResonance[2];
	DWORD AtackTime[2],DecayTime[2],ReleaseTime[2];
	DWORD PitchBendSensitibity[2];

	//EFX
	DWORD EFXOn;

} SMIDI_TRACKINFO,*LPSMIDI_TRACKINFO;

typedef struct SMIDI_INFO_TAG{
	EIMEMORY hMidiData,hThisStruct;
	LPBYTE lpMidiData,lpStartMidiData,lpBuffer,
		lpBackMidiData;
	//ââëtèÓïÒ
	DWORD Tempo,Division,MasterVolume,
		LateForExclusiveDelta;//ÉGÉNÉXÉNÉãÅ[ÉVÉuëóêMÇ…ÇÊÇÈíxÇÍ;

	//ÇlÇhÇcÇhèÓïÒ
	SMIDI_TRACKINFO tr[SMIDI_TRACK_MAX];

	//ââëtÇ…ä÷Ç∑ÇÈÇ‡ÇÃ
	int Status,LastStatus,MidiDataSize;
	int DeltaTime,DeltaCount,MidiClock,NextDeltaTime,
		PlayCount,OffsetPlayCount;

	int PlayFlag,InitFlag,FirstPlayFlag;

	DWORD dwDeltaTime;
	int nBufSide,StreamStatus;

	//EFX
	DWORD EFXType,EFXParam[20],
		EFXReverb,EFXChorus,EFXDelay,
		EFXDepth1,EFXSource1,EFXDepth2,EFXSource2,
		EFXEQSwitch;

} SMIDI_STREAM,*LPSMIDI_STREAM;
