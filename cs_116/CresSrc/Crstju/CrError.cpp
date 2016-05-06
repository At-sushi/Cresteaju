//---CrError.cpp

#define CRER_NOSYSTEMFILE 10001

#define CRER_CANT_INITDISPLAY 10101
#define CRER_CANT_INIT3D 10102
#define CRER_CANT_INITEILIBRARY 10103
#define CRER_CANT_CREATEWINDOW 10104

#define CRER_CANT_INITSOUND 10201
#define CRER_CANT_INITMUSIC 10202

#define CRER_CANT_READFILE 10301
#define CRER_CANT_READPALETTEFILE 10302
#define CRER_CANT_READPATTERNFILE 10303
#define CRER_CANT_READSOUNDFILE 10304
#define CRER_CANT_READDATAFILE 10305

int crGetErrorString(eistr *str,int size,int code)
{
	switch(code)
	{
	case CRER_NOSYSTEMFILE:
		sprintf(str,"�N���ɕK�v�ȃt�@�C��������܂���");
		break;
	case CRER_CANT_INITDISPLAY:
		sprintf(str,"");
		break;
	case CRER_CANT_INIT3D:
		sprintf(str,"Direct3D���������ł��܂���ł���");
		break;
	case CRER_CANT_INITEILIBRARY:
		sprintf(str,"���C�u�����[���������ł��܂���ł���");
		break;
	case CRER_CANT_CREATEWINDOW:
		sprintf(str,"�E�B���h�E�����܂���ł���");
		break;
	case CRER_CANT_INITSOUND:
		sprintf(str,"�T�E���h���������ł��܂���ł���");
		break;
	case CRER_CANT_INITMUSIC:
		sprintf(str,"MIDI���������ł��܂���ł���");
		break;

	case CRER_CANT_READFILE:
		sprintf(str,"�t�@�C����ǂݍ��߂܂���ł���");
		break;
	case CRER_CANT_READPALETTEFILE:
		sprintf(str,"�p���b�g�t�@�C����ǂݍ��߂܂���ł���");
		break;
	case CRER_CANT_READPATTERNFILE:
		sprintf(str,"�p�^�[���t�@�C����ǂݍ��߂܂���ł���");
		break;
	case CRER_CANT_READSOUNDFILE:
		sprintf(str,"�T�E���h�t�@�C����ǂݍ��߂܂���ł���");
		break;
	case CRER_CANT_READDATAFILE:
		sprintf(str,"�f�[�^�t�@�C����ǂݍ��߂܂���ł���");
		break;
	default:
		*str = NULL;
		return 0;
	}
	return 1;
}

void ShowError(eistr *str,int code = -1,HWND hwnd = NULL)
{
	eistr temp[256];

	if(code != -1){
		if(!crGetErrorString(&temp[0],sizeof(temp),code)){
			sprintf(temp,"%s :  �G���[�R�[�h = %d",
				str != NULL ? str : "",code);
		}
	} else if(str != NULL){
		sprintf(temp,"%s",str);
	} else {
		temp[0] = NULL;
	}

	MessageBox(hwnd != NULL ? hwnd : NULL,temp,"�G���[",MB_OK);
}
