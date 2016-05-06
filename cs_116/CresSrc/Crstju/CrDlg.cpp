
#include <commctrl.h>

char *midi_type[] = {"GS/GMi•W€j","SC-88","SC-88Pro","SC-8820/SC-D70"};

BOOL CALLBACK DLGFunc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	SCROLLINFO si;
	static int sound_volume = 0,first = 1;
	LPCR_INIFILE ini = crdataGetIniFile();

	switch(message){
	case WM_INITDIALOG:
		//---DirectX
		SendDlgItemMessage(hwnd,IDC_DDHAL,BM_SETCHECK,
			ini->UseDirectDrawHardware,0);
		SendDlgItemMessage(hwnd,IDC_D3DHAL,BM_SETCHECK,
			ini->UseDirect3DHardware,0);
		SendDlgItemMessage(hwnd,IDC_DS,BM_SETCHECK,
			ini->UseDirectSound,0);
		SendDlgItemMessage(hwnd,IDC_ZBUFFER,BM_SETCHECK,
			ini->UseZBuffer,0);
		SendDlgItemMessage(hwnd,IDC_DRAWPRIMITIVEWAIT,BM_SETCHECK,
			ini->DrawPrimitiveWait,0);

		//---Midi
		SendDlgItemMessage(hwnd,IDC_MIDI,BM_SETCHECK,
			ini->UseMIDI,0);
		SendDlgItemMessage(hwnd,IDC_OFFSETPLAY,BM_SETCHECK,
			ini->OffsetPlay,0);
		if(first){
			SendDlgItemMessage(hwnd,IDC_MIDITYPE,CB_ADDSTRING,
				0,(LPARAM)midi_type[0]);
			SendDlgItemMessage(hwnd,IDC_MIDITYPE,CB_ADDSTRING,
				0,(LPARAM)midi_type[1]);
			SendDlgItemMessage(hwnd,IDC_MIDITYPE,CB_ADDSTRING,
				0,(LPARAM)midi_type[2]);
			SendDlgItemMessage(hwnd,IDC_MIDITYPE,CB_ADDSTRING,
				0,(LPARAM)midi_type[3]);
		}

		SendDlgItemMessage(hwnd,IDC_MIDITYPE,CB_SETCURSEL,
			ini->MIDIType,0);

		//---Sound
		SendDlgItemMessage(hwnd,IDC_SOUND,BM_SETCHECK,
			ini->UseSound,0);

		memset(&si,0,sizeof(si));
		si.cbSize = sizeof(si);
		si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
		si.nMin = 0;
		si.nMax = 127;
		si.nPage = 0;
		sound_volume = si.nPos = ini->Volume;
		SetScrollInfo(GetDlgItem(hwnd,IDC_VOLUME),SB_CTL,&si,1);

		//---Other
		SendDlgItemMessage(hwnd,IDC_JOY,BM_SETCHECK,
			ini->UseJoystick,0);
		SendDlgItemMessage(hwnd,IDC_TEXTURELINER,BM_SETCHECK,
			ini->TextureFilterLiner,0);
		SendDlgItemMessage(hwnd,IDC_WIRE,BM_SETCHECK,
			ini->Battle3DUseFilling ? 0 : 1,0);
		SendDlgItemMessage(hwnd,IDC_FORCEREFRESHRATE,BM_SETCHECK,
			ini->ForceRefreshRate_Over80,0);
//		SendDlgItemMessage(hwnd,IDC_WINDOW_RF_MODE,BM_SETCHECK,
//			ini->WindowRFMode,0);

		first = 0;

		return 1;

	case WM_HSCROLL:
		switch(LOWORD(wParam)){
		case SB_LINELEFT:
			sound_volume --;
			break;
		case SB_PAGELEFT:
			sound_volume -= 16;
			break;
		case SB_LINERIGHT:
			sound_volume ++;
			break;
		case SB_PAGERIGHT:
			sound_volume += 16;
			break;
		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			sound_volume = HIWORD(wParam);
			break;
		}

		if(sound_volume < 0)
			sound_volume = 0;
		if(sound_volume > 127)
			sound_volume = 127;

		memset(&si,0,sizeof(si));
		si.cbSize = sizeof(si);
		si.fMask = SIF_POS;
		si.nPos = sound_volume;
		SetScrollInfo((HWND)lParam,SB_CTL,&si,1);

		break;

	case WM_COMMAND:
		switch(LOWORD(wParam)){
		case IDOK:
			//---DirectX
			ini->UseDirectDrawHardware = SendDlgItemMessage(hwnd,IDC_DDHAL,BM_GETCHECK,0,0);
			ini->UseDirect3DHardware = SendDlgItemMessage(hwnd,IDC_D3DHAL,BM_GETCHECK,0,0);
			ini->UseDirectSound = SendDlgItemMessage(hwnd,IDC_DS,BM_GETCHECK,0,0);
			ini->UseZBuffer = SendDlgItemMessage(hwnd,IDC_ZBUFFER,BM_GETCHECK,0,0);
			ini->DrawPrimitiveWait = SendDlgItemMessage(hwnd,IDC_DRAWPRIMITIVEWAIT,BM_GETCHECK,0,0);

			//---Midi
			ini->UseMIDI = SendDlgItemMessage(hwnd,IDC_MIDI,BM_GETCHECK,0,0);
			ini->OffsetPlay = SendDlgItemMessage(hwnd,IDC_OFFSETPLAY,BM_GETCHECK,0,0);
			ini->MIDIType = SendDlgItemMessage(hwnd,IDC_MIDITYPE,CB_GETCURSEL,0,0);

			//---Sound
			ini->UseSound = SendDlgItemMessage(hwnd,IDC_SOUND,BM_GETCHECK,0,0);
			ini->Volume = sound_volume;

			//---Other
			ini->UseJoystick = SendDlgItemMessage(hwnd,IDC_JOY,BM_GETCHECK,0,0);
			ini->TextureFilterLiner = SendDlgItemMessage(hwnd,IDC_TEXTURELINER,BM_GETCHECK,0,0);
			ini->Battle3DUseFilling = SendDlgItemMessage(hwnd,IDC_WIRE,BM_GETCHECK,0,0) ? 0 : 1;
			if(ini->Battle3DUseFilling == 1)
				ini->Battle3DUseTexture = 1;
			ini->ForceRefreshRate_Over80 = SendDlgItemMessage(hwnd,IDC_FORCEREFRESHRATE,BM_GETCHECK,0,0);
//			ini->WindowRFMode = SendDlgItemMessage(hwnd,IDC_WINDOW_RF_MODE,BM_GETCHECK,0,0);

			EndDialog(hwnd,1);
			return 1;
		case IDCANCEL:
			EndDialog(hwnd,0);
			return 1;

		case IDDEFAULT:
			CresteajuSetDefaultINIFile(crdataGetIniFile());
			SendMessage(hwnd,WM_INITDIALOG,0,0);

			return 1;
		}
		break;
	}
	return 0;
}
