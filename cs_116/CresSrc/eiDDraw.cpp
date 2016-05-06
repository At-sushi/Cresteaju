/*-----------------------------------------------------------

   eiLibray
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   eiDDraw.cpp ...DirectDraw

-----------------------------------------------------------*/
//------------------------
//	DirectDraw
//------------------------

//---�T�[�t�F�C�X
eiDDSurface eiSurface[32];
//---�y�o�b�t�@�[�i�Q�c�ł͎g�p�����j
eiDDSurface eiZBuffer[1];

EI_API EI_DDINFO eiDDInfo;

//---eiLibrary���g��DirectDraw�T�[�t�F�C�X�ւ̃|�C���^�𓾂�
EI_API eiDDSurface* eiGetSurfacePointer(void)
{
	return &eiSurface[0];
}

EI_API EI_DDINFO *eiGetDDInfo(void)
{
	return &eiDDInfo;
}

//---�r�b�g�V�t�g�l�𓾂�
int GetBitShift(DWORD data)
{
	int a;
	DWORD n = 0x0001;

	for(a = 0;a < 32;a ++,n = n << 1){
		if(data & n){
			//---0�łȂ����
			return a;
		}
	}
	return 0;
}

/*void eidbMsg(char *msg)
{
	MessageBox(hMainWindow,msg,"�G���[",MB_OK);
}*/

#define eidbMsg(x)

#include "eiDDSurface.cpp"
#include "eiDDPalette.cpp"

//---------------------------------------------------------------
//---------------------------------------------------------------


//---DirectDraw������������
int eiDDInit(HWND hwnd,int xs,int ys,int color,int mode,int refresh_rate)
{
	HRESULT ddrval = 0;

	hMainWindow = hwnd;

	memset(&eiDDInfo,0,sizeof(eiDDInfo));
	eiDDInfo.DDSurfaceColor = 8;
	if(mode & INIT_DIRECT3D)
		eiDDInfo.Use3D = 1;

	if(!(mode & NOTUSE_HARDWARE3D))
		eiDDInfo.UseHardware3D = 1;
	if(mode & DIRECTDRAW_WINDOW)
		eiDDInfo.UseWindow = 1;

	if(mode & DIRECTDRAW_EMULATION/*DDCREATE_EMULATIONONLY*/){
		//---�\�t�g�E�F�A�G�~�����[�V����
//		ddrval = DirectDrawCreate((struct _GUID *)DDCREATE_EMULATIONONLY,&eiDDInfo.lpDDOld,NULL);
		ddrval = DirectDrawCreateEx((struct _GUID *)DDCREATE_EMULATIONONLY,(void **)&eiDDInfo.lpDD,IID_IDirectDraw7,NULL);
		eiDDInfo.DDHEL = 1;
	} else {
		if((mode & INIT_DIRECT3D) && (mode & DIRECTDRAW_FULLSCREEN)){
			//---�R�c���g���ăt���X�N���[���Ȃ�f�o�C�X���
//			ddrval = DirectDrawEnumerate(eiDDEnumCallback,&eiDDInfo.lpDD);
		}
		if(!eiDDInfo.lpDD){
			ddrval = DirectDrawCreateEx(NULL,(void **)&eiDDInfo.lpDD,IID_IDirectDraw7,NULL);
		}
	}

	if(ddrval != DD_OK){
		eiDebugWriteFile("(eiDDInit) DirectDrawCreate;Fail\n");
		return FALSE;
	}

	eiDDInfo.lpDDOld = NULL;
/*	//---DirectDraw4�����
	ddrval = eiDDInfo.lpDDOld->QueryInterface(IID_IDirectDraw4, (LPVOID *)&eiDDInfo.lpDD);
	if(ddrval != DD_OK){
		eiDebugWriteFile("(eiDDInit) QueryInterface(IID_IDirectDraw4);Fail\n");
		return FALSE;
	}
	eiDebugWriteFile("(eiDDInit) QueryInterface;\n");*/

#ifdef EIUSE_DIRECT3D
	if((mode & INIT_DIRECT3D)){
		//---�R�c�̏ꍇ�̓J���[���f��
	    DDCAPS DriverCaps, HELCaps;

		memset(&DriverCaps, 0, sizeof(DriverCaps));
		DriverCaps.dwSize = sizeof(DriverCaps);

		memset(&HELCaps, 0, sizeof(HELCaps));
		HELCaps.dwSize = sizeof(HELCaps);

		eiDDInfo.lpDD->GetCaps(&DriverCaps, &HELCaps);

		eiDDInfo.ColorModel = D3DCOLOR_RGB;

		if(eiDDInfo.UseHardware3D){
			if (DriverCaps.dwCaps & DDCAPS_3D && 
				DriverCaps.ddsCaps.dwCaps & DDSCAPS_TEXTURE ) {
				//---RGB
				eiDDInfo.ColorModel = D3DCOLOR_RGB;
				eiDebugWriteFile("(eiDDInit) RGBModel ( Hard )\n");
			}
		}
	}
#endif /* EIUSE_DIRECT3D */

	eiDebugWriteFile("(eiDDInit) DirectDrawCreate;Success\n");
	if((::eiSystem.ScreenMode & DIRECTDRAW_FULLSCREEN) != 0){
		//---�t���X�N���[��
		ddrval = eiDDInfo.lpDD->SetCooperativeLevel(hwnd,
			DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
	} else {
		//---�E�B���h�E
		ddrval = eiDDInfo.lpDD->SetCooperativeLevel(hwnd,
			DDSCL_NORMAL);
	}
	if(ddrval != DD_OK){
		eiDebugWriteFile("(eiDDInit) SetCooperativelLevel;Fail\n");
		return FALSE;
	}
	eiDebugWriteFile("(eiDDInit) SetCooperativelLevel;\n");
eidbMsg("(eiDDInit) SetCooperativelLevel");

	if((::eiSystem.ScreenMode & DIRECTDRAW_FULLSCREEN) != 0){
		ddrval = eiDDInfo.lpDD->SetDisplayMode(xs,ys,color,
				refresh_rate,0);
		if(ddrval != DD_OK){
#ifdef EI_LIB
	eiDebugWriteFile("(eiDDInit) SetDisplayMode;Fail\n");
#endif
eidbMsg("(eiDDInit) SetDisplayMode ���s");

			return FALSE;
		}
	}
	eiDebugWriteFile("(eiDDInit) SetDisplayMode\n");
eidbMsg("(eiDDInit) SetDisplayMode Success");

	eiDDInfo.DDSurfaceColor = color;

	eiDebugWriteFile("(eiDDInit) Finish;\n");

	return TRUE;
}

//---�f�B�X�v���C���[�h�����ɖ߂�
int eiDDRestoreDisplayMode(void)
{
	if(eiDDInfo.lpDD->RestoreDisplayMode() != DD_OK){
		eiDebugWriteFile("(eiDDRestoreDisplayMode) Finish;Fail\n");
		return 0;
	}

	return 1;
}

//---DirectDraw�̎g�p���I����
int eiDDEnd(void)
{
	int a;
	char s[80];

	if((::eiSystem.ScreenMode & DIRECTDRAW_MODE) == 0){
		//---DirectDraw���g���ĂȂ����
		return 1;
	}
	
/*	if(eiDDInfo.lpDD->SetCooperativeLevel(lpMainWindow->hwnd, DDSCL_NORMAL ) != DD_OK){
			eiDebugWriteFile("(eiDDEnd) SetCooperativeLevel.Fail\n");
	}
*/
	if(eiDDInfo.lpDDClipper != NULL){
		//---�N���b�p�[�����
		eiSurface[0].lpSurface->SetClipper(NULL);
		if(eiDDInfo.lpDDClipper->Release() > 0){
			eiDebugWriteFile("(eiDDEnd) iDDInfo.lpDDClipper->Release() > 0\n");
		}
		eiDDInfo.lpDDClipper = NULL;
		eiDebugWriteFile("(eiDDEnd) iDDInfo.lpDDClipper->Release().\n");
	}

	//---�T�[�t�F�C�X�����
	for(a = 31;a >= 2;a --){
		eiSurface[a].DrawFillBox(0,0,eiSurface[a].xSize - 1,eiSurface[a].ySize - 1,0);
		if(eiSurface[a].Release() == 0){
			sprintf(s,"%d\n",a);
			eiDebugWriteFile(s);
		}
	}
	eiDebugWriteFile("(eiDDEnd) eiSurface[a + 2]->Release.\n");

	for(a = 1;a >= 0;a --){
//		eiSurface[a].DrawFillBox(0,0,eiSurface[a].xSize - 1,eiSurface[a].ySize - 1,0);
		if(eiSurface[a].Release() == 0){
			sprintf(s,"%d\n",a);
			eiDebugWriteFile(s);
		}
	}
	eiDebugWriteFile("(eiDDEnd) eiSurface[a].Release.\n");

	//---�f�B�X�v���C���[�h����
	if((::eiSystem.ScreenMode & DIRECTDRAW_FULLSCREEN) != 0){
		eiDDRestoreDisplayMode();
		eiDebugWriteFile("(eiDDEnd) eiDDRestoreDisplayMode.\n");
	}

/*	if(eiDDInfo.lpDDPalette){
		eiDDInfo.lpDDPalette->Release();
		eiDDInfo.lpDDPalette = NULL;
	}*/
//	eiDebugWriteFile("(eiDDEnd) lpDDPalette->Release.\n");

#ifdef EIUSE_DIRECT3D
	//---Direct3D�̉��
	if(eiDDInfo.lpD3D){
		int count;
		if((count = eiDDInfo.lpD3D->Release()) > 0){
			eiDebugWriteFile("(eiDDEnd) lpD3D->Release > 0\n");
		}
		sprintf(s,"%d\n",count);
		eiDebugWriteFile(s);
		eiDebugWriteFile("(eiDDEnd) lpD3D->Release.\n");
	}
	if(eiDDInfo.lpD3DOld){
		if(eiDDInfo.lpD3DOld->Release()  > 0){
			eiDebugWriteFile("(eiDDEnd) lpD3DOld->Release > 0\n");
		}
		eiDebugWriteFile("(eiDDEnd) lpD3DOld->Release.\n");
	}
#endif /* EIUSE_DIRECT3D */

	//---DirectDraw�I�u�W�F�N�g�����
	if(eiDDInfo.lpDD != NULL){
		if((a = eiDDInfo.lpDD->Release()) > 0){
			eiDebugWriteFile("(eiDDEnd) lpDD->Release > 0!!\n");
			sprintf(s,"%d\n",a);
			eiDebugWriteFile(s);
		}
	}
	eiDebugWriteFile("(eiDDEnd) lpDD->Release.\n");

	if(eiDDInfo.lpDDOld != NULL){
		if(eiDDInfo.lpDDOld->Release() > 0){
			eiDebugWriteFile("(eiDDEnd) lpDDOld->Release > 0!!\n");
		}
		eiDebugWriteFile("(eiDDEnd) lpDDOld->Release.\n");
	}

	return TRUE;
}

//---�T�[�t�F�C�X��������
int eiDDSurfaceInit(HWND hwnd)
{
	RECT rect;
	HRESULT ddrval;
	int a = 0,mode = 0;

	rect.left = rect.top = 0;
	rect.right = ::eiSystem.xScreenSize;
	rect.bottom = ::eiSystem.yScreenSize;

//---------------------------------------
	//---�v���C�}���T�[�t�F�C�X�쐬
	mode = ESCREATE_PRIMARYSURFACE;
eidbMsg("(eiDDSurfaceInit) �v���C�}���T�[�t�F�C�X�쐬�O");
	eiSurface[0].Create(::eiSystem.xScreenSize,::eiSystem.yScreenSize,
		mode);
eidbMsg("(eiDDSurfaceInit) �v���C�}���T�[�t�F�C�X�쐬�I");
	eiSurface[0].SurfaceMode |= EISURFACE_CALCCLIENT;
	eiDDInfo.lpPrimaryBuffer = eiSurface[0].lpSurface;

	//---�o�b�N�T�[�t�F�C�X�쐬
	mode = ESCREATE_BACKSURFACE;
eidbMsg("(eiDDSurfaceInit) �o�b�N�T�[�t�F�C�X�擾�O");
	eiSurface[1].Create(::eiSystem.xScreenSize,::eiSystem.yScreenSize,
		mode,&eiSurface[0]);
eidbMsg("(eiDDSurfaceInit) �o�b�N�T�[�t�F�C�X�擾�I");
	eiDDInfo.lpBackBuffer = eiSurface[1].lpSurface;

	//----------------clipper
	if((::eiSystem.ScreenMode & DIRECTDRAW_WINDOW) != 0){
		//---�E�B���h�E���[�h�̐ݒ�
		ddrval = eiDDInfo.lpDD->CreateClipper(0,&eiDDInfo.lpDDClipper,NULL);
		if(ddrval != DD_OK){
			return FALSE;
		}
		ddrval = eiDDInfo.lpDDClipper->SetHWnd(0,hwnd);
		if(ddrval != DD_OK){
			return FALSE;
		}
		eiSurface[0].lpSurface->SetClipper(eiDDInfo.lpDDClipper);
		if(ddrval != DD_OK){
			return FALSE;
		}
	} else {
	}

	return TRUE;
}

EI_API int eiGetDDMaxViedoMemory(void)
{
	DWORD total_mem = 0,free_mem = 0;
	DDSCAPS2 ddsCaps2;

	memset(&ddsCaps2,0,sizeof(ddsCaps2));
	ddsCaps2.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_LOCALVIDMEM;
//		| DDSCAPS_OFFSCREENPLAIN | DDSCAPS_PRIMARYSURFACE;

	eiDDInfo.lpDD->GetAvailableVidMem(&ddsCaps2, &total_mem, &free_mem); 

	return total_mem;
}

EI_API int eiGetDDFreeViedoMemory(void)
{
	DWORD total_mem,free_mem;
	DDSCAPS2 ddsCaps2;

	memset(&ddsCaps2,0,sizeof(ddsCaps2));
	ddsCaps2.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_LOCALVIDMEM;

	eiDDInfo.lpDD->GetAvailableVidMem(&ddsCaps2, &total_mem, &free_mem); 

	return free_mem;
}

EI_API int eiIsDirectDrawHAL(void)
{
/*	DDCAPS ddcap;

	memset(&ddcap,0,sizeof(ddcap));
	ddcap.dwSize = sizeof(ddcap);

	if(ddcap.dwCaps & DDCAPS_NOHARDWARE)
		return 0;*/
	if(eiDDInfo.DDHEL)
		return 0;
	return 1;
}
