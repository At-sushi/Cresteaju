/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrInit.cpp ...Initialize and end

-----------------------------------------------------------*/
//---DumyData
ei_u32 DumyData;
ei_u32 DumyAccess = 123456,*DumyPtr = &DumyAccess;

void CresteajuSetDefaultINIFile(LPCR_INIFILE ini);
int CresteajuReadINIFile(LPCR_INIFILE ini);
int CresteajuInit_ReadPattern(void);
int CresteajuInit_ReadData(void);
int CresteajuInit_ReadSound(void);
void CresteajuInit_DebugData(void);
int CresteajuInit_Direct3D(void);


//extern void eidbMsg(char *msg);
#define eidbMsg(x)

//---�I������
int CresteajuEnd(int src)
{
	int a;
	static int EndFlag = 0;

	if(EndFlag)
		return 1;

	EndFlag = 1;
//---�R�[�h�ݒ�
	crsysSetCodeMode(CODE_END);

eiDebugWriteFile("(CresteajuEnd) �~���[�W�b�N�I��\n");
	//---�~���[�W�b�N�I��
	crmusicEndMusic();

	//---�T�E���h���
eiDebugWriteFile("(CresteajuEnd) �T�E���h���\n");
	for(a = CRSOUND_SOUNDMAX - 1;a >= 0;a --){
		pSound[a].Release();
	}
	eiEndSound();

eiDebugWriteFile("(CresteajuEnd) �}�b�v���\n");
	//---�}�b�v���
	cem.Delete();

eiDebugWriteFile("(CresteajuEnd) �Z�����\n");
	//---�Z�����
	for(a = 1999;a >= 0;a --){
		pCell[a].Release();
	}
eiDebugWriteFile("(CresteajuEnd) �p���b�g���\n");
	//---�p���b�g���
	ep->Release();

	//---�R�c�I�u�W�F�N�g���
eiDebugWriteFile("(CresteajuEnd) �R�c�I�u�W�F�N�g���\n");
	cBaseMaterial.Release();
	if(pViewport != NULL)
		pViewport->Release();
eiDebugWriteFile("(CresteajuEnd) eid3d->EndDirect3D()�Ăяo��\n");
	eid3d->EndDirect3D();


eiDebugWriteFile("(CresteajuEnd) eiEnd�Ăяo��\n");
	//---�I��
	eiEnd();

	if(eiGetDebugMode()){
		eiMemoryOutputForDebug();
	}

	if(src == 0){
		eiDebugWriteFile("(CresteajuEnd) src:windows message\n");
	} else if(src == 1){
		eiDebugWriteFile("(CresteajuEnd) src:WinMain\n");
	}

	return 1;
}

//---�N�����̏��������
int CresteajuInitStartUp(void)
{
//---�R�[�h
	crsysSetCodeMode(CODE_STARTUP);

//---�N���X�|�C���^
	ew = &cew;
	ep = &cep;
	et = &cet;
	ei = &cei;
	ef = &cef[0];
	em = &cem;
	eid3d = &ceid3d;
	pViewport = &cViewport;
	pSound = &Sound[0];

//---Cell
	pCell = &cCell[0];
	pWindowCell = &pCell[CR_PTN_SYSTEM_WINDOW];
	pMenuCursorCell = &pCell[CR_PTN_SYSTEM_MENUCURSOR];
	pMainCharacterCell = &pCell[CR_PTN_SYSTEM_MAINCHARACTER];
//	pMenuIconCell = &pCell[CR_PTN_SYSTEM_MENUICON];
	pMessageIconCell = &pCell[CR_PTN_SYSTEM_MESSAGEICON];
	pItemIconCell = &pCell[CR_PTN_SYSTEM_ITEMICON];
	pMagicIconCell = &pCell[CR_PTN_SYSTEM_MAGICICON];
	pStatusBarCell = &pCell[CR_PTN_SYSTEM_STATUSBAR];
	pBalanceBarCell = &pCell[CR_PTN_SYSTEM_BALANCEBAR];
	pCharaFace = &pCell[CR_PTN_SYSTEM_CHARAFACE];
	pBattleCursorCell = &pCell[CR_PTN_SYSTEM_BATTLECURSOR];
	pBattleFontCell = &pCell[CR_PTN_SYSTEM_BATTLEFONT];
	pWallPaperCell = &pCell[CR_PTN_SYSTEM_WALLPAPER];

//---�|�C���^�Z�b�g
	pGameUsingData = &GameUsingData;
	pCharacterInfo = &CharacterInfo[0];
	pGameInfo = &GameInfo;
	pPartyInfo = &PartyInfo;
	pItemInfo = &ItemInfo[0];
	pMagicInfo = &MagicInfo[0];
	pSpecialInfo = &SpecialInfo[0];

	pEnemyBatInfo = &EnemyBattleInfo[0];
	pEnemyCharaInfo = &EnemyCharacterInfo[0];

	DumyData = (ei_u32)&DumyPtr;

//---�eDLL������
	crbaseInitDLL(&GameUsingData,
		&GameInfo,&PartyInfo,
		&CharacterInfo[0],&ItemInfo[0],&MagicInfo[0],
		&CrDebug,&CrFileMode,&CrSystem,&InitializeInfo,
		&CrExeInfo,
		&DumyData);

	crbatInitDLL(&GameUsingData,
		&GameInfo,&PartyInfo,
		&CharacterInfo[0],&ItemInfo[0],&MagicInfo[0],
		&CrDebug,&CrFileMode,&CrSystem,&InitializeInfo,
		&EnemyCharacterInfo[0],&EnemyBattleInfo[0]);

//---���ׂĂ̕ϐ���������
	memset(&InitializeInfo,0,sizeof(InitializeInfo));
	memset(&IniFile,0,sizeof(IniFile));
	//---�Q�[���ϐ�������
	memset(&GameUsingData,0,sizeof(GameUsingData));
	memset(&GameInfo,0,sizeof(GameInfo));
	memset(&PartyInfo,0,sizeof(PartyInfo));

	//---�o�[�W����
	GameUsingData.Version = CresteajuVersion;

	return 1;
}

//---�n�r�ʂ̏�������Ɓi������́E�E�E�j
#ifdef EI_RUNWINDOWS
//---Windows //CRESTEEJU CRESTEAJU
int CresteajuInitForOS(CRESTEAJU_INITIALIZE *pInit,
		HINSTANCE hThisInst,HINSTANCE hPrevInst,
		LPSTR lpszArgs,int nWinMode)
{
	//---Windows�ŗL�ϐ�
	::hThisInst = hThisInst;
	::hPrevInst = hPrevInst;

	HDC hdc = GetDC(NULL);
	int bpp = GetDeviceCaps(hdc,BITSPIXEL);
	ReleaseDC(NULL,hdc);

	//---���������e�ݒ�
	pInit->RefreshRate = 0;
	if(bpp == 16 || bpp == 15){
		pInit->Init = DIRECTDRAW_FULLSCREEN | EICOLOR_16BIT;
		pInit->Init = DIRECTDRAW_WINDOW | EICOLOR_16BIT;
	} else if(bpp == 24){
		pInit->Init = DIRECTDRAW_WINDOW | EICOLOR_24BIT;
	} else {
		pInit->Init = DIRECTDRAW_WINDOW | EICOLOR_32BIT;
	}

	pInit->ScreenMode = 1;
//	pInit->Init = DIRECTDRAW_FULLSCREEN | EICOLOR_16BIT;
//	pInit->ScreenMode = 0;

#if (CR_DATAMODE == 0)
	pInit->Init = DIRECTDRAW_FULLSCREEN | EICOLOR_16BIT;
	pInit->ScreenMode = 0;
#endif

#if (CR_DEBUG == 0)
	pInit->Init = DIRECTDRAW_FULLSCREEN | EICOLOR_16BIT;
	pInit->ScreenMode = 0;
#endif

	//---�������
	if(lpszArgs){
		if(!strcmp("-c",lpszArgs) || !strcmp("/c",lpszArgs)){
			return 2;
		} else if(!strcmp("-j",lpszArgs) || !strcmp("/j",lpszArgs)){
			return 3;
		} else if(!strcmp("-d",lpszArgs) || !strcmp("/d",lpszArgs)){
			pInit->Init = DIRECTDRAW_FULLSCREEN | EICOLOR_16BIT;
			pInit->ScreenMode = 0;
		} else if(!strcmp("-d24",lpszArgs) || !strcmp("/d24",lpszArgs)){
			pInit->Init = DIRECTDRAW_FULLSCREEN | EICOLOR_24BIT;
			pInit->ScreenMode = 0;
		} else if(!strcmp("-d32",lpszArgs) || !strcmp("/d32",lpszArgs)){
			pInit->Init = DIRECTDRAW_FULLSCREEN | EICOLOR_32BIT;
			pInit->ScreenMode = 0;
		} else if(!strcmp("-wd",lpszArgs) || !strcmp("/wd",lpszArgs)){
			if(bpp == 16 || bpp == 15){
				pInit->Init = DIRECTDRAW_WINDOW | EICOLOR_16BIT;
			} else {
				pInit->Init = DIRECTDRAW_WINDOW | EICOLOR_32BIT;
			}
			pInit->ScreenMode = 1;
		} else if(!strcmp("-w",lpszArgs) || !strcmp("/w",lpszArgs)){
			pInit->Init = WINAPI_WINDOW | EICOLOR_8BIT;
			pInit->ScreenMode = 1;
		} else if(!strcmp("-r60",lpszArgs) || !strcmp("/r60",lpszArgs)){
			pInit->RefreshRate = 60;
		}
//#ifdef _DEBUG
#if (CR_DEBUG == 1)
//-----------------------------------------------------------------
		//---�f�o�b�N�p
		if(!strcmp("-h",lpszArgs) || !strcmp("/h",lpszArgs)){
			crdebugHtmlOut();
			return 0;
		}
		if(!strcmp("-make",lpszArgs) || !strcmp("/make",lpszArgs)){
			pItemInfo = &ItemInfo[0];
			pMagicInfo = &MagicInfo[0];
			
			crdebugMakeData(0);

			pInit->Init = DIRECTDRAW_WINDOW | EICOLOR_16BIT;
			pInit->ScreenMode = 1;
//-----------------------------------------------------------------
		}
#endif /* CR_DEBUG */
//#endif /* _DEBUG */
	}

	return 1;
}
#endif /* EI_RUNWINDOW */

//---�V�X�e��������
int CresteajuInitSystem(CRESTEAJU_INITIALIZE init)
{
	int a,c = 1;
	HWND hwnd;

	//---�t�@�C���`�F�b�N
#if (CR_DATAMODE == 0)
	int check = 1;
	char *filename[] = {
		CR_DATAFILE1,CR_DATAFILE2,
		CR_DATAFILE3,CR_DATAFILE4,
		CR_MUSICFILE,CR_MESSAGEFILE1
	};
	FILE *fp;

	for(a = 0;a < 6;a ++){
		fp = fopen(filename[a],"rb");
		check &= (fp == NULL ? 0 : 1);
		if(fp != NULL){
			fclose(fp);
		}
	}
	if(check == 0){
		eiSetLastError(CRER_NOSYSTEMFILE);
		return 0;
	}
#endif

//---�R�[�h���[�h
	eiWaitCriticalSection(1000);
	crsysSetCodeMode(CODE_INITIALIZE);

//---�f�o�b�N���[�h
	CrDebug = 0;
	eiSetDebugMode(0);

//---�f�o�b�O�\�Ȃ�f�o�b�O���[�h�ɂ���
#if (CR_DEBUG == 1)
	{
		char s[80];
		FILE *fp = fopen("debuginfo.txt","r");
		if(fp){
			fgets(s,20,fp);
			if(!strcmp(s,"somyard2!")){
				eiSetDebugMode(CR_DEBUG);
				CrDebug = CR_DEBUG;
				eiSetDebugMode(1);
				CrDebug = 1;
/*#if (CR_DATAMODE == 0)
				eiSetDebugMode(0);
#endif*/
			}
			fclose(fp);
		}
	}
#else
		eiSetDebugMode(0);
#endif
//eiSetDebugMode(1);

	eiDebugInitFile();
/*	eistr temp[80];
	sprintf(temp,"cell:%d bytes dib:%d bytes file:%d bytes\n",sizeof(eiCell),sizeof(eiDib),sizeof(eiFile));
	eiDebugWriteFile(temp);*/
//---�Œ�ϐ�������
	crdataSetGameUsing(&GameUsingData);

//---INI�t�@�C���ǂݍ���
	memset(crdataGetIniFile(),0,sizeof(CR_INIFILE));
	CresteajuSetDefaultINIFile(crdataGetIniFile());
	CresteajuReadINIFile(crdataGetIniFile());

	if(!crdataGetIniFile()->UseDirectDrawHardware){
		//---DirectDraw�G�~�����[�V����
		InitializeInfo.Init |= DIRECTDRAW_EMULATION;
	}
	if(crdataGetIniFile()->HalfScreen){
		InitializeInfo.Init |= HALFSIZESCREEN;
	}
	if(!crdataGetIniFile()->UseZBuffer){
		InitializeInfo.Init |= NOUSE_ZBUFFER;
	}

	InitializeInfo.Init |= (INIT_DIRECT3D | USE_3DRGBMODEL);
	if(!InitializeInfo.IniFile.UseDirect3DHardware){
		InitializeInfo.Init |= NOTUSE_HARDWARE3D;
	}

/*	//---bpp
	int bpp = crdataGetIniFile()->BPP;
	if(bpp == 16){
		InitializeInfo.Init |= EICOLOR_16BIT;
	} else if(bpp == 24){
		InitializeInfo.Init |= EICOLOR_24BIT;
	} else if(bpp == 32){
		InitializeInfo.Init |= EICOLOR_32BIT;
	}*/

//---�V�X�e���f�[�^��������
	crdataInitData();

//---eiLibrary������
	if(!eiInit(InitializeInfo.Init,640,480,640,480,2,8,16)){
		eiSetLastError(CRER_CANT_INITEILIBRARY);
		return 0;
	}

//---�������t���b�V�����[�g�ݒ�CrSystem.cpp���ōĐݒ�����Ă�
	if(init.ScreenMode == 1){
		eiSetDisplayRefreshRate(85);
		eiSetDrawRefreshRate(85);
	} else {
		eiSetDisplayRefreshRate(60);
		eiSetDrawRefreshRate(60);
	}

	et->SetWaitCount(1000 / eiSetDrawRefreshRate(-1));

//-----------------------------------
//---�E�B���h�E�����
	hwnd = ew->Create(hThisInst,&TitleName[0],WindowFunc,1);
	if(hwnd == NULL){
		eiSetLastError(CRER_CANT_CREATEWINDOW);
		return 0;
	}
	//---�e�o�r�\��
	if(InitializeInfo.IniFile.ShowFPS){
		ew->ShowFPS(1);
	}

//---�O���t�B�b�N������
	if(!eiInitGraphicSystem(ew,InitializeInfo.RefreshRate)){

		eiSetLastError(CRER_CANT_INITDISPLAY);
		return 0;
	}
	eiSetDirectText(1);

	//---�t���b�v���[�h
	crdataGetIniFile()->FlipMode &= 0x01;
	eiSetFlipMode(crdataGetIniFile()->FlipMode);

	//---Direct3D
	if(!CresteajuInit_Direct3D()){

		eiSetLastError(CRER_CANT_INIT3D);
		return 0;
	}

//---�}�b�v�V�X�e��������
	eiFieldInit(ew,ep,ei,et,
		(pCell + CR_PTN_FIELD),NULL/*(Cell + CR_PTN_FIELD)*/);
	ef->SetDrawRate(100);/*100*/
	ef->SetDebugMode(0/*eiGetDebugMode()*/);
	ef->SetFieldTop(
		320 - ((crdataGetIniFile()->FieldSizeX + 2) * 32 / 2),
		240 - ((crdataGetIniFile()->FieldSizeY + 2) * 32 / 2));
	ef->SetFieldSize(crdataGetIniFile()->FieldSizeX,crdataGetIniFile()->FieldSizeY);
	ef->SetMarginOfErrorFPS(crdataGetIniFile()->MarginOfErrorFPS);
	if(crdataGetIniFile()->AutoChangeFPS){
		ef->SetDrawMode(EF_DRAW_AUTOCHANGE);
	} else {
		ef->SetDrawMode(EF_DRAW_MANUAL);
	}
eidbMsg("�}�b�v�������I��");

	//---�R�[���o�b�N�֐�
	ef->SetMainCharacterCallback(crfieldDrawMainCharacter);
//---�p���b�g
	{
		ep->Create();
		if(!ep->ReadDIB(CR_DATADIR1"CresteajuPalette.acf",CR_DATAFILE1,crdataGetFileMode())){
			eiSetLastError(CRER_CANT_READPALETTEFILE);

			return 0;
		}
		ew->SetPalette(ep);
	}
eidbMsg("�p���b�g�ǂݍ���");

//---�C���v�b�g�f�o�C�X�Z�b�g
	ei->Init();
	a = EI_INPUT_LARGEKEY;
	if(crdataGetIniFile()->UseJoystick){
		//---�W���C�X�e�B�b�N���g��
		a |= EI_INPUT_JOY1;
	}
	ei->SetInputDevice(0,a);
eidbMsg("�W���C�X�e�B�b�N������");
//---�T�E���h������
	{
		//---���y������
		if(crmusicInitMusic() == 0){
			eiSetLastError(CRER_CANT_INITMUSIC);
			return 0;
		}
		if(crdataGetIniFile()->UseDirectSound){
			//---�T�E���h������
			eiInitSound(ew);
			eiSoundSetVolume(crdataGetIniFile()->Volume);
		}
		if(CresteajuInit_ReadSound() == 0){
			eiSetLastError(CRER_CANT_READSOUNDFILE);
			return 0;
		}
	}
eidbMsg("�T�E���h������");

	if(CresteajuInit_ReadPattern() == 0){
		//---�p�^�[���𐳏�ɓǂݍ��߂Ȃ�����
		eiSetLastError(CRER_CANT_READPATTERNFILE);
		return 0;
	}

	if(CresteajuInit_ReadData() == 0){
		eiSetLastError(CRER_CANT_READDATAFILE);
		return 0;
	}

//---�����ݒ�
	GameInfo.TransWindow = 0;

//---�I�u�W�F�N�g���
	eiReleaseCriticalSection();
	return 1;
}

//---���ʉ��ǂݍ���
int CresteajuInit_ReadSound(void)
{
	int a,c = 1;
	char s[80];

	//---���ʉ�
	if(crdataGetIniFile()->UseSound){
		int BufCount = 1;

		for(a = 0;a < CRSOUND_SOUNDMAX;a ++){
			sprintf(s,CR_DATADIR1"Sound%02d.wav",a);
			c |= pSound[a].Read(s,CR_DATAFILE1,crdataGetFileMode(),BufCount);
		}
	}

	if(c == 0)
		eiSetLastError(CRER_NOSYSTEMFILE);

	return c;
}

//---�Q�[���f�[�^�ǂݍ���
int CresteajuInit_ReadData(void)
{
	int a,c = 1;

	//---�f�[�^�ǂݍ���
	eiFile file;

	//---�A�C�e��
	{
		file.SetLinkFile(CR_DATAFILE1);
		if(file.Open(CR_DATADIR1"ItemData.dat") == 0){
			eiSetLastError(CRER_NOSYSTEMFILE);
			return 0;
		}

		for(a = 0;a < ITEMMATERIAL_MAX;a ++){
			file.Read(&pItemInfo[a].MaterialInfo,sizeof(pItemInfo[a].MaterialInfo),1);
			file.Read(&pItemInfo[a].ItemInfo,sizeof(pItemInfo[a].ItemInfo),1);
		}
		file.Close();
	}

	//---���@
	{
		file.SetLinkFile(CR_DATAFILE1);
		if(file.Open(CR_DATADIR1"MagicData.dat") == 0){
			eiSetLastError(CRER_NOSYSTEMFILE);
			return 0;
		}

		for(a = 0;a < MAGICMATERIAL_MAX;a ++){
			file.Read(&pMagicInfo[a].MaterialInfo,sizeof(pMagicInfo[a].MaterialInfo),1);
			file.Read(&pMagicInfo[a].MagicInfo,sizeof(pMagicInfo[a].MagicInfo),1);
		}
		file.Close();
	}

	//---�K�E�Z
	{
		file.SetLinkFile(CR_DATAFILE1);
		if(file.Open(CR_DATADIR1"SpecialData.dat") == 0){
			eiSetLastError(CRER_NOSYSTEMFILE);
			return 0;
		}

		for(a = 0;a < SPECIALMATERIAL_MAX;a ++){
			file.Read(&pSpecialInfo[a].MaterialInfo,sizeof(pSpecialInfo[a].MaterialInfo),1);
			file.Read(&pSpecialInfo[a].SpecialInfo,sizeof(pSpecialInfo[a].SpecialInfo),1);
		}
		file.Close();
	}

	//---�G
	{
		file.SetLinkFile(CR_DATAFILE3);
		if(file.Open(CR_DATADIR3"EnemyData.dat") == 0){
			eiSetLastError(CRER_NOSYSTEMFILE);
			return 0;
		}
		file.Read(&pEnemyBatInfo[0],sizeof(CRESTEAJU_BATTLECHARAINFO),ENEMY_MAX);
		file.Read(&pEnemyCharaInfo[0],sizeof(CRESTEAJU_CHARACTERINFO),ENEMY_MAX);
		file.Close();
	}

	if(c == 0)
		eiSetLastError(CRER_NOSYSTEMFILE);

	return c;
}

//---���ʃp�^�[���ǂݍ���
int CresteajuInit_ReadPattern(void)
{
	int c = 1;

	//---Window
	c &= eiCellReadPattern(pWindowCell,
		CR_DATADIR1"CrWindowPattern.acf",CR_DATAFILE1,crdataGetFileMode(),
		0,8,16,16);
	eiCellSetSurface(pWindowCell,
		CR_PTNSURFACE_WINDOW_X,CR_PTNSURFACE_WINDOW_Y,16,16,8);

	//---MenuCursor
	c &= eiCellReadPattern(pMenuCursorCell,
		CR_DATADIR1"CrMenuCursor.acf",CR_DATAFILE1,crdataGetFileMode(),
		0,16,16,16);
	eiCellSetSurface(pMenuCursorCell,
		CR_PTNSURFACE_MENUCURSOR_X,CR_PTNSURFACE_MENUCURSOR_Y,16,16,16);
	//---BattleCursor
	c &= eiCellReadPattern(pBattleCursorCell,
		CR_DATADIR1"CrBattleCursor.acf",CR_DATAFILE1,crdataGetFileMode(),
		0,8,16,16);
	eiCellSetSurface(pBattleCursorCell,
		CR_PTNSURFACE_BATTLECURSOR_X,CR_PTNSURFACE_BATTLECURSOR_Y,16,16,8);
	//---BattleFont
	c &= eiCellReadPattern(pBattleFontCell,
		CR_DATADIR1"CrBattleFont.acf",CR_DATAFILE1,crdataGetFileMode(),
		0,32,16,16);
	//---ItemIcon
	c &= eiCellReadPattern(pItemIconCell,
		CR_DATADIR1"ItemIcon.acf",CR_DATAFILE1,crdataGetFileMode(),
		0,16,16,16);
	eiCellSetSurface(pItemIconCell,
		CR_PTNSURFACE_ITEMICON_X,CR_PTNSURFACE_ITEMICON_Y,16,16,16);
	//---MagicIcon
	c &= eiCellReadPattern(pMagicIconCell,
		CR_DATADIR1"MagicIcon.acf",CR_DATAFILE1,crdataGetFileMode(),
		0,16,16,16);
	eiCellSetSurface(pMagicIconCell,
		CR_PTNSURFACE_MAGICICON_X,CR_PTNSURFACE_MAGICICON_Y,16,16,16);
	//---MessageIcon
	c &= eiCellReadPattern(pMessageIconCell,
		CR_DATADIR1"CrMessageIcon.acf",CR_DATAFILE1,crdataGetFileMode(),
		0,16,16,16);
	eiCellSetSurface(pMessageIconCell,
		CR_PTNSURFACE_MESSAGEICON_X,CR_PTNSURFACE_MESSAGEICON_Y,16,16,16);

	if(c == 0)
		eiSetLastError(CRER_NOSYSTEMFILE);

	return c;
}

int CresteajuInit_Direct3D(void)
{
	int a;
//---Direct3D-----------------------------
	if(!eid3d->InitDirect3D()){
		return 0;
	}
eidbMsg("(CresteajuInit_Direct3D) begin");
	for(a = 0;a < 16;a ++){
		if(eid3d->Begin()){
			break;
		}
		eiSleep(100);
	}
	if(a == 16){
		return 0;
	}

	eid3d->InitTextureState();

	if(!pViewport->Create()){
		eid3d->End();
eidbMsg("(CresteajuInit_Direct3D) pViewport can't create");
		return 0;
	}
	if(!cBaseMaterial.Create()){
		eid3d->End();
eidbMsg("(CresteajuInit_Direct3D) cBaseMaterial can't create");
		return 0;
	}

	eid3d->AddViewport(pViewport);
	pViewport->Set();
	eid3d->SetCurrentViewport(pViewport);

	cmatWorld.Create(
		D3DVAL( 1.0), D3DVAL( 0.0), D3DVAL( 0.0), D3DVAL( 0.0), 
		D3DVAL( 0.0), D3DVAL( 1.0), D3DVAL( 0.0), D3DVAL( 0.0), 
		D3DVAL( 0.0), D3DVAL( 0.0), D3DVAL( 1.0), D3DVAL( 0.0), 
		D3DVAL( 0.0), D3DVAL( 0.0), D3DVAL( 0.0), D3DVAL( 1.0));
	cmatView.Create(
		D3DVAL( 1.0), D3DVAL( 0.0), D3DVAL( 0.0), D3DVAL( 0.0), 
		D3DVAL( 0.0), D3DVAL( 1.0), D3DVAL( 0.0), D3DVAL( 0.0), 
		D3DVAL( 0.0), D3DVAL( 0.0), D3DVAL( 1.0), D3DVAL( 0.0), 
		D3DVAL( 0.0), D3DVAL( 0.0), D3DVAL(10.0), D3DVAL( 1.0));
	cmatProjection.Create(
		D3DVAL( 2.0), D3DVAL( 0.0), D3DVAL( 0.0), D3DVAL( 0.0), 
		D3DVAL( 0.0), D3DVAL( 2.0), D3DVAL( 0.0), D3DVAL( 0.0), 
		D3DVAL( 0.0), D3DVAL( 0.0), D3DVAL( 1.0), D3DVAL( 1.0), 
		D3DVAL( 0.0), D3DVAL( 0.0), D3DVAL(-1.0), D3DVAL( 0.0));
	cmatProjection.CalcProjectionMatrix(0.01f,100.0f,1.57f);
	eid3d->SetTransformWorld(&cmatWorld);
	eid3d->SetTransformView(&cmatView);
	eid3d->SetTransformProjection(&cmatProjection);

	eid3d->SetMaterial(&cBaseMaterial);
	eid3d->SetAmbientLight(RGBA_MAKE(255,255,255,255));
//----------------------------------------------------
	//---�e�N�X�`�����[�h
	if(crdataGetIniFile()->TextureFilterLiner){
		eid3d->SetTextureFilter(EID3D_TEXFILTER_LINER);
	} else {
		eid3d->SetTextureFilter(EID3D_TEXFILTER_POINT);
	}
//----------------------------------------------------
	if(crdataGetIniFile()->DrawPrimitiveWait){
		eid3d->SetWait(1);
	}


	eid3d->End();
eidbMsg("(CresteajuInit_Direct3D) end");

	return 1;
}

void CresteajuSetDefaultINIFile(LPCR_INIFILE ini)
{
	memset(ini,0,sizeof(CR_INIFILE));

	//---System
	memset(&ini->SaveDir[0],0,sizeof(ini->SaveDir));

	ini->ExtentionLevel = 3;
	ini->AutoSave = 0;
	//---Windows
	ini->FullScreen = 1;
	ini->GDIOnly = 0;
	//---MIDI & Sound
	ini->OffsetPlay = 1;
	ini->UseMIDI = 1;
	ini->MIDIType= 0;
	ini->Volume = 127;
	ini->UseSound = 1;
	//---DirectX
	ini->UseDirectDrawHardware = 1;
	ini->UseDirectSound = 1;
	ini->UseDirect3DHardware = 1;
	ini->TextureFilterLiner = 1;
	ini->UseZBuffer = 1;
	ini->UseHardwareTransform = 0;
	ini->DrawPrimitiveWait = 0;
	//---Field
	ini->FieldSizeX = 17;
	ini->FieldSizeY = 13;
	//---Display
	ini->HalfScreen = 0;
	ini->BaseCount = 100;
	ini->FlipMode = 1;
	ini->ForceFPS = 0;
	ini->ForceRefreshRate = 0;
	ini->ForceRefreshRate_Over80 = 1;
	ini->MarginOfErrorFPS = 200;
	ini->BPP = 16;
	ini->WindowRFMode = 0;
	//---Input
	ini->UseJoystick = 1;

	//---Battle
	ini->Battle3DUseTexture = 1;
	ini->Battle3DUseFilling = 1;
	ini->AlphaBattleField = 0;
	ini->FogBattleField = 0;
	ini->BattleViewAngle = 0;
	ini->BattleShadow = 1;

	//---3DFunction
	ini->EnableAddAlpha = 0;
}

//---INI�t�@�C���ɏ�������
int CresteajuWriteINIFile(LPCR_INIFILE ini)
{
	FILE *fp = fopen("cres.ini","w");

	if(fp == NULL)
		return 0;

	if(ini->SaveDir[0] != NULL){
		fprintf(fp,"SaveFileDirectory = %s\n",ini->SaveDir[0]);
	}
	if(ini->AutoSave){
		fprintf(fp,"AutoSave = %d\n",ini->AutoSave);
	}
	if(ini->ShowFPS){
		fprintf(fp,"ShowFPS = %d\n",ini->ShowFPS);
	}
	if(ini->MarginOfErrorFPS != 200){
		fprintf(fp,"MarginOfErrorFPS = %d\n",ini->MarginOfErrorFPS);
	}
/*	if(ini->OutputDebugFile){
		fprintf(fp,"OutputDebugFile = %d",ini->AutoSave);
	}*/

	//---DirectX
	fprintf(fp,"\n[DirectX]\n");
	fprintf(fp,"UseDirectDrawHardware = %d\n",ini->UseDirectDrawHardware);
	fprintf(fp,"UseDirect3DHardware = %d\n",ini->UseDirect3DHardware);
	fprintf(fp,"UseDirectSound = %d\n",ini->UseDirectSound);
	fprintf(fp,"UseZBuffer = %d\n",ini->UseZBuffer);
	fprintf(fp,"DrawPrimitiveWait = %d\n",ini->DrawPrimitiveWait);

	//---Midi
	fprintf(fp,"\n[MIDI]\n");
	fprintf(fp,"OffsetPlay = %d\n",ini->OffsetPlay);
	fprintf(fp,"UseMIDI = %d\n",ini->UseMIDI);
	fprintf(fp,"MIDIType = %d\n",ini->MIDIType);

	//---Sound
	fprintf(fp,"\n[Sound]\n");
	fprintf(fp,"UseSound = %d\n",ini->UseSound);
	fprintf(fp,"Volume = %d\n",ini->Volume);

	//---Other
	fprintf(fp,"\n[Other]\n");
	fprintf(fp,"UseJoystick = %d\n",ini->UseJoystick);
	fprintf(fp,"TextureFilterLiner = %d\n",ini->TextureFilterLiner);
	fprintf(fp,"Battle3DUseFilling = %d\n",ini->Battle3DUseFilling);
	fprintf(fp,"ForceRefreshRate = %d\n",ini->ForceRefreshRate);
	fprintf(fp,"ForceRefreshRate_Over80 = %d\n",ini->ForceRefreshRate_Over80);
//	fprintf(fp,"WindowRFMode = %d\n",ini->WindowRFMode);

	fclose(fp);

	return 1;
}

//---INI�t�@�C����ǂ�
int CresteajuReadINIFile(LPCR_INIFILE ini)
{
	char t[256];
	FILE *fp;

	int outputfile = 0;

	fp = fopen("cres.ini","r");
	if(fp != NULL){
		while(fgets(&t[0],128,fp)){
			//---System
			eiGetStringItem("SaveFileDirectory",&t[0],&ini->SaveDir[0],NULL);
			eiGetStringItem("AutoSave",&t[0],NULL,&ini->AutoSave);
			eiGetStringItem("OutputDebugFile",&t[0],NULL,&outputfile);
			//---Windows
			eiGetStringItem("FullScreen",&t[0],NULL,&ini->FullScreen);
			eiGetStringItem("GDIOnly",&t[0],NULL,&ini->GDIOnly);
			//---MIDI
			eiGetStringItem("OffsetPlay",&t[0],NULL,&ini->OffsetPlay);
			eiGetStringItem("UseMIDI",&t[0],NULL,&ini->UseMIDI);
			eiGetStringItem("MIDIType",&t[0],NULL,&ini->MIDIType);
//			eiGetStringItem("MIDIYMF724",&t[0],NULL,&ini->MIDIYMF724);
			//---Sound
			eiGetStringItem("UseSound",&t[0],NULL,&ini->UseSound);
			eiGetStringItem("Volume",&t[0],NULL,&ini->Volume);
			//---DirectX
			eiGetStringItem("UseDirectDrawHardware",&t[0],NULL,&ini->UseDirectDrawHardware);
			eiGetStringItem("UseDirect3DHardware",&t[0],NULL,&ini->UseDirect3DHardware);
			eiGetStringItem("UseDirectSound",&t[0],NULL,&ini->UseDirectSound);
			eiGetStringItem("TextureFilterLiner",&t[0],NULL,&ini->TextureFilterLiner);
			eiGetStringItem("UseZBuffer",&t[0],NULL,&ini->UseZBuffer);
			eiGetStringItem("UseHardwareTransform",&t[0],NULL,&ini->UseHardwareTransform);
			eiGetStringItem("EnableAddAlpha",&t[0],NULL,&ini->EnableAddAlpha);
			eiGetStringItem("DrawPrimitiveWait",&t[0],NULL,&ini->DrawPrimitiveWait);
			//---Field
			eiGetStringItem("FieldSizeX",&t[0],NULL,&ini->FieldSizeX);
			eiGetStringItem("FieldSizeY",&t[0],NULL,&ini->FieldSizeY);
			if(ini->FieldSizeX > 17)
				ini->FieldSizeX = 17;
			if(ini->FieldSizeY > 13)
				ini->FieldSizeY = 13;
			if(ini->FieldSizeX < 5)
				ini->FieldSizeX = 5;
			if(ini->FieldSizeY < 5)
				ini->FieldSizeY = 5;
			//---Display
			eiGetStringItem("ForceRefreshRate",&t[0],NULL,&ini->ForceRefreshRate);
			eiGetStringItem("ForceRefreshRate_Over80",&t[0],NULL,&ini->ForceRefreshRate_Over80);
			eiGetStringItem("WindowRFMode",&t[0],NULL,&ini->WindowRFMode);
			eiGetStringItem("ForceFPS",&t[0],NULL,&ini->ForceFPS);
			eiGetStringItem("AutoChangeFPS",&t[0],NULL,&ini->AutoChangeFPS);
			eiGetStringItem("BaseCount",&t[0],NULL,&ini->BaseCount);
			eiGetStringItem("MarginOfErrorFPS",&t[0],NULL,&ini->MarginOfErrorFPS);
			eiGetStringItem("FlipMode",&t[0],NULL,&ini->FlipMode);
			eiGetStringItem("HalfScreen",&t[0],NULL,&ini->HalfScreen);
			eiGetStringItem("BPP",&t[0],NULL,&ini->BPP);
			eiGetStringItem("ShowFPS",&t[0],NULL,&ini->ShowFPS);
			//---Input
			eiGetStringItem("UseJoystick",&t[0],NULL,&ini->UseJoystick);

			eiGetStringItem("ExtentionLevel",&t[0],NULL,&ini->ExtentionLevel);
//			eiGetStringItem("",&t[0],NULL,&HighColor);
			//---Battle
			eiGetStringItem("Battle3DUseTexture",&t[0],NULL,&ini->Battle3DUseTexture);
			eiGetStringItem("Battle3DUseFilling",&t[0],NULL,&ini->Battle3DUseFilling);
			eiGetStringItem("AlphaBattleField",&t[0],NULL,&ini->AlphaBattleField);
			eiGetStringItem("FogBattleField",&t[0],NULL,&ini->FogBattleField);
			eiGetStringItem("BattleShadow",&t[0],NULL,&ini->BattleShadow);
//			eiGetStringItem("BattleViewAngle",&t[0],NULL,&ini->BattleViewAngle);
		}
		fclose(fp);
	}

	//---�I�[�g�Z�b�g�A�b�v
	if(ini->UseDirectDrawHardware == 0){
		ini->UseDirect3DHardware = 0;
	}
	if(ini->UseDirect3DHardware == 0){
		ini->AlphaBattleField = 0;
	}

	if(ini->Battle3DUseFilling == 0){
		ini->Battle3DUseTexture= 0;
	}

#if(CR_DEBUG == 1)
	if(outputfile){
		eiSetDebugMode(CR_DEBUG);
	}
#endif

	return 1;
}

void CresteajuInit_DebugData(void)
{
#if _DEBUG
#endif
}
