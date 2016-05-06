/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBase_SoundAPI.cpp ...Sound and Music functions

-----------------------------------------------------------*/
#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBASE_SOUNDAPI

#define EXTERN_EICLASS
#include "..\CrBase.h"

//---game info
#define CR_GAMEINFO_EXTERNPOINTER
#include "..\CrGameInfo.h"

CRBASE_SOUNDAPI void crsoundPlay(int number,int mode /*= 0*/)
{
	if(crdataGetIniFile()->UseSound){
		pSound[number].Play(mode == 0 ? 0 : EISOUND_PLAYLOOP);
	}
}

CRBASE_SOUNDAPI void crsoundStop(int number,int mode /*= 0*/)
{
	if(crdataGetIniFile()->UseSound){
		pSound[number].Stop();
	}
}

CRBASE_SOUNDAPI void crsoundAllStop(int number,int mode /*= 0*/)
{
	if(crdataGetIniFile()->UseSound){
		pSound[number].Stop();
	}
}
//---------------------------------------------------
//---------------------------------------------------
//---�~���[�W�b�N
LPSMIDI_STREAM pMidiStream[STREAM_MAX];
static int MusicMode = 0,StreamNumber = 0,MusicNumber[STREAM_MAX] = {-1,-1,-1,-1};

static eistr *MidiGS[] = 
{
	"Init","WindRmx_GS","DBreath_GS","Generat_GS","Endless_GS",
	"BtlSong_GS","route134_GS","Follow_GS","Sakaba_GS","Street_GS",
	"Star_GS","Lizel_GS","LunnarR_GS","ItsTime_88","Tomato_GS",
	"dreaming_GS","Happiness_GS","Eternal_GS","Heat_GS","seek_GS",
	"Forest_GS","faraway_GS","Cloud_GS","Sunday_GS","uni_GS",
	"passed","natsu_GS","sunset_GS","EndlessP_88","Yurikago_GS",
	"Fortune_GS","since_GS","Barrier_GS","Night_GS","samit_88",
	"Force_GS","meteor_GS","hope_GS","BeAwake_GS","InStream_GS",
	"piece_GS","NeverEnd_GS",
	"silent"
};

static eistr *Midi88[] = 
{
	"Init","WindRmx_88","DBreath_88","Generat_88","Endless_88",
	"BtlSong_88","route134_88","Follow_88","Sakaba_88","Street_88",
	"Star_88","Lizel_88","LunnarR_88","ItsTime_88","Tomato_88",
	"dreaming_88","Happiness_88","Eternal_88","Heat","seek",
	"Forest","faraway_88","Cloud_88","Sunday_88","uni_88",
	"passed","natsu_88","sunset_88","EndlessP_88","Yurikago_88",
	"Fortune_88","since_88","Barrier_88","Night_88","samit_88",
	"Force_88","meteor_88","hope_88","BeAwake_88","InStream_88",
	"piece_88","NeverEnd_88",
	"silent"
};

static eistr *Midi8820[] = 
{
	"Init","WindRmx","DBreath","Generat","Endless",
	"BtlSong","route134_8820","Follow","Sakaba","Street",
	"Star","Lizel","LunnarR_8820","ItsTime","Tomato",
	"dreaming","Happiness","Eternal","Heat","seek",
	"Forest","faraway_8820","Cloud","Sunday","uni",
	"passed","natsu","sunset","EndlessP","Yurikago",
	"Fortune","since","Barrier","Night","samit",
	"Force","meteor","hope","BeAwake","InStream",
	"piece","NeverEnd_8820",
	"silent"
};

static eistr *Midi88Pro[] = 
{
	"Init","WindRmx","DBreath","Generat","Endless",
	"BtlSong","route134","Follow","Sakaba","Street",
	"Star","Lizel","LunnarR","ItsTime","Tomato",
	"dreaming","Happiness","Eternal","Heat","seek",
	"Forest","faraway","Cloud","Sunday","uni",
	"passed","natsu","sunset","EndlessP","Yurikago",
	"Fortune","since","Barrier","Night","samit",
	"Force","meteor","hope","BeAwake","InStream",
	"piece","NeverEnd",
	"silent"
};

static eistr *MusicTitle[] = 
{
	"-","���������͂��߂�Ƃ�","Dragon Breath","Generator","Endless Way",
	"�킢�̉S","route 134","following the wind","����������","Cloudy Street",
	"�O�����̗��ꐯ","��w�̕�","Lunar Road","It's time you had a rest","�g�}�g�������āA�Ђ�͂���",
	"end of long dreaming","�i���K���̉���","The Eternal","Heat a Heart","seek a way",
	"���[���X","�������ƁA��������","�_�̗N���ꏊ","Sunday^2","�S�E�A�{���̃e�[�}",
	"�u�����肵�ߋ�","�Ȃ�","sunset","endless way piano version","��肩���ɗ�������",
	"BREAK A FORTUNE","since that day","���̏��","Silver Night","����̃T�~�b�g",
	"FATED FORCE","�a���J","�]�݂����̉ʂĂ�","Never be awaken","IN THE STREAM",
	"���E�̂�����","���͎����z����",
	"-silent-"
};

#if (CR_DATAMODE == 1)
	static eistr *MidiLinkFileName = "";
#else
	static eistr *MidiLinkFileName = "CrMusic.dat";
#endif

static eistr **MidiTable = &MidiGS[0];

CRBASE_SOUNDAPI eistr **crmusicGetTitleString(void)
{
	return &MusicTitle[0];
}

CRBASE_SOUNDAPI int crmusicInitMusic(void)
{
	int a;

	if(!crdataGetIniFile()->UseMIDI){
		return 1;
	}

	if(smidiInit(NULL,3) != SMIDI_NOERROR){
		return 0;
	}

	for(a = 0;a < STREAM_MAX;a ++){
		pMidiStream[a] = smidiCreateStream();

		if(pMidiStream[a] == NULL)
			return 0;
	}

	StreamNumber = 0;
	MusicNumber[0] = MusicNumber[1] = -1;

	switch(crdataGetIniFile()->MIDIType){
	case 0:
		MidiTable = &MidiGS[0];
		break;
	case 1:
		MidiTable = &Midi88[0];
		break;
	case 2:
		MidiTable = &Midi88Pro[0];
		break;
	case 3:
		MidiTable = &Midi8820[0];
		break;
	}

	return 1;
}

CRBASE_SOUNDAPI int crmusicEndMusic(void)
{
	int a;

	if(!crdataGetIniFile()->UseMIDI){
		return 1;
	}

	crmusicStop();
	for(a = 0;a < STREAM_MAX;a ++){
		smidiDeleteStream(pMidiStream[a]);
		pMidiStream[a] = NULL;
	}

	smidiEnd(NULL);

	return 1;
}

CRBASE_SOUNDAPI void crmusicSetStream(int number)
{
	if(!crdataGetIniFile()->UseMIDI){
		return;
	}

	StreamNumber = number;
}

CRBASE_SOUNDAPI void crmusicRestoreStream(int number)
{
	if(!crdataGetIniFile()->UseMIDI){
		return;
	}
//	crmusicStop();
	crmusicSetStream(number);
	smidiPlay(pMidiStream[number]);

	pGameInfo->MusicNumber = MusicNumber[number];
}

#define PKM_BUFFER_SIZE 2048
#define TYPE_COUNT 4

CRBASE_SOUNDAPI void crmusicPlay(int number,int loop /*= 1*/,int mode /*= 0*/)
{
	//---�Ȃ�����������
	if(::pGameInfo->Music[number] <= 999999){
		::pGameInfo->Music[number] ++;
		::pGameInfo->Music[CRMUSIC_SILENT] = 1;
	}
	if(!crdataGetIniFile()->UseMIDI){
		return;
	}

/*	if(number == MusicNumber[StreamNumber]
		&& !pMidiStream[StreamNumber]->PlayFlag){
		//---�����i���o�[�Ŏ~�܂��Ă�����
	}*/
	if(number == MusicNumber[StreamNumber] && !(mode & CRMUSIC_LOADFORCE)){
		//---�������[�h�łȂ��A�����i���o�[��������
		return;
	}

	pGameInfo->MusicNumber = MusicNumber[StreamNumber] = number;

	int pkm_type = 0;
	char name[80];
	EIMEMORY hMemory,hMidi;
	ei_u8 *pMemory,*point,*pMidi,*pmidipoint;
	eiBitStream eb;

	sprintf(name,CR_MUSICDIR"%s",MidiTable[number]);
	if(name[strlen(name) - 2] == 'G' && name[strlen(name) - 1] == 'S'){
		pkm_type = 2;
	} else if(name[strlen(name) - 2] == '8' && name[strlen(name) - 1] == '8'){
		pkm_type = 1;
	} else if(name[strlen(name) - 2] == '2' && name[strlen(name) - 1] == '0'){
		pkm_type = 3;
	}

	//---midipak�t�@�C��
	eiFile file(MidiLinkFileName);
	sprintf(name,CR_MUSICDIR"%sp.ezp",Midi88Pro[number]);

	if(file.Open(name)){
		int size;
		int a,pkm_size[TYPE_COUNT];
		int flag ,count,buf_size,read_size;
#if (CR_DEBUG == 1)
		eiTime let;
#endif
		{
			char temp[3];
			file.Read(&temp[0],1,3);
			eb.ReadCompressFile(&file);
			size = eb.Buffer.OriginalSize;
			hMemory = eiAllocMemory(size + 1024);
			pMemory = (ei_u8 *)eiLockMemory(hMemory);
			if(pMemory == NULL){
				file.Close();
			}

#if (CR_DEBUG == 1)
			let.Reset();
#endif
			eb.Decompress(pMemory);
#if (CR_DEBUG == 1)
			char s[80];
			sprintf(s,"%s : %dms\n",MusicTitle[number],let.Get());
			eiDebugWriteFile(s);
#endif
		}

		//---�e�t�@�C���T�C�Y
		point = pMemory;
		for(a = 0;a < TYPE_COUNT;a ++){
			pkm_size[a] = *(ei_s32 *)point;
			point += sizeof(ei_s32);
		}

/*		eiDebugWriteFile("---------------------------------\n");
		char s[80];
		sprintf(s,"%d ,%d , %d \n",size,pkm_type,pkm_size[pkm_type]);
		eiDebugWriteFile(s);
*/
		hMidi = eiAllocMemory(pkm_size[pkm_type] + 1024);
		pmidipoint = pMidi = (ei_u8 *)eiLockMemory(hMidi);

		//---�t�@�C�������o��
		flag = 1;
		read_size = 0;
		do {
			count = *(ei_s8 *)point;
			point += sizeof(ei_s8);

			buf_size = *(ei_s32 *)point;
			point += sizeof(ei_s32);
/*			char ss[80];
			sprintf(ss,"::%d,%d\n",count,buf_size);
			eiDebugWriteFile(ss);
*/
			if(count == pkm_type && buf_size){
				//---�����t�@�C����������
				memcpy(pmidipoint,point,buf_size);
				read_size += buf_size;
				pmidipoint += buf_size;
			}

			point += buf_size;

			//---�I������
			if(count == pkm_type && !buf_size){
				flag = 0;
			}
			if(read_size >= pkm_size[pkm_type]){
				flag = 0;
			}
		} while(flag);

/*		FILE *fp;
		fp = fopen("test.mid","wb");
		fwrite(pMidi,1,pkm_size[pkm_type],fp);
		fclose(fp);
*/
		eb.FreeBuffer();
		eiUnlockMemory(hMemory);
		eiFreeMemory(hMemory);

		eiUnlockMemory(hMidi);

		//---hMidi�̊Ǘ���smidi�ɂ܂�����
		if(smidiOpenFile(pMidiStream[StreamNumber],
			(LPSTR)hMidi,
			(LPSTR)pkm_size[pkm_type],
			2)
			!= SMIDI_NOERROR){
		}

		smidiPlay(pMidiStream[StreamNumber]);
		smidiSetPlayMode(loop == 1 ? SMIDI_LOOPPLAY : 0);
	}

return;
/*
//	char name[80];
	sprintf(name,CR_MUSICDIR"%s.ezp",MidiTable[number]);
	if(smidiOpenFile(pMidiStream[StreamNumber],name,MidiLinkFileName,1)
		!= SMIDI_NOERROR){
	}


	smidiPlay(pMidiStream[StreamNumber]);
	smidiSetPlayMode(SMIDI_LOOPPLAY);
*/
}

CRBASE_SOUNDAPI void crmusicStop(void)
{
	if(!crdataGetIniFile()->UseMIDI){
		return;
	}
	smidiStop(pMidiStream[StreamNumber]);
}

CRBASE_SOUNDAPI void crmusicFadeIn(int speed /* = 20*/)
{
	if(!crdataGetIniFile()->UseMIDI){
		return;
	}

	smidiFadeIn(127,0,speed);
}

CRBASE_SOUNDAPI void crmusicFadeOut(int speed /* = 20*/)
{
	if(!crdataGetIniFile()->UseMIDI){
		return;
	}

	smidiFadeOut(0,127,speed);
}

CRBASE_SOUNDAPI void crmusicSetVolume(int volume)
{
	if(!crdataGetIniFile()->UseMIDI){
		return;
	}
}

static int UseWaitCallback = 0;

CRBASE_SOUNDAPI void crmusicSetWaitCallback(int mode)
{
	UseWaitCallback = mode;
}

CRBASE_SOUNDAPI int crmusicGetTimeFromStart(void)
{
	return smidiGetPlayTime(pMidiStream[StreamNumber]);
}

CRBASE_SOUNDAPI void crmusicWait(int wait)
{
	int t;

	while((t = smidiGetPlayTime(pMidiStream[StreamNumber])) < wait){
		eiSleep(10);
		if(crsysQuick())
			return;

		if(UseWaitCallback){
			if(ef->FGCallback != NULL){
				(*ef->FGCallback)(ew->lpCell[1],0,0,0,0,0);
				ew->Flip();
			}
		}

#if (CR_DEBUG == 1)
		{
			char s[80];
			sprintf(s,"(crmusicWait) wait %d:%d\n",t,wait);
			eiDebugWriteFile(s);
		}
#endif
	}
/*	int shosetsu,clock,all_clock;

	if(!crdataGetIniFile()->UseMIDI){
		return;
	}

	do {
		smidiGetPoint(pMidiStream[StreamNumber],&shosetsu,&clock,&all_clock);
	} while(shosetsu < wait);*/
}

//---�~���[�W�b�N�e�X�g
CRBASE_SOUNDAPI void crmusicMusicTest(void)
{
	int a,music_num,sel,music = pGameInfo->MusicNumber;
	eistr *pstr,*pstart;
	EIMEMORY hMemory;
	CrSelectWindow win;
	CRWIN_SELECTINFO info;
	memset(&info,0,sizeof(info));

	hMemory = eiAllocMemory(10000);
	if(hMemory == NULL)
		return;
	pstart = pstr = (eistr *)eiLockMemory(hMemory);

	for(music_num = 1;strcmp(MusicTitle[music_num],"-silent-") != 0;music_num ++){
	}
	if(music_num % 2 == 0)
		music_num ++;

	for(a = 1;a < music_num;a ++){
		if(pGameInfo->Music[a]){
			sprintf(pstr,"%s;",MusicTitle[a]);
			pstr += (strlen(MusicTitle[a]) + 1);
		} else {
			sprintf(pstr,"  ;",MusicTitle[a]);
			pstr += (strlen("  ") + 1);
		}
	}
	win.Create(32,16,36,28,"�Ȃ�I��ł�������",pstart,2,26);

	do {
		crbaseMenuReset();
		crbaseMenuStart();
		win.Paint();
		win.Refresh();
		sel = win.Select(&info);

		if(sel != -1 && pGameInfo->Music[sel + 1]){
			crmusicPlay(CRMUSIC_INIT);
			et->Delay2(1200);
			crmusicPlay(sel + 1);
		}
	} while(sel != -1);

	crmusicPlay(CRMUSIC_INIT);
	et->Delay2(1200);
	crmusicPlay(music);

	eiUnlockMemory(hMemory);
	eiFreeMemory(hMemory);
}
