#define CONFIGMESWIN_CREATE(y) mes.Create(256,y,20,9)

extern CRESTEAJU_VERSION CresteajuVersion;

int crmainSystem_VersionInfo(void)
{
	CrMessageWindow mes;
	eistr s[80];
	eistr laststr[8] = {' ','a','b','c','d','e'};

	crmainClearMenu();
	crbaseMenuReset();
	mes.Create(32,32,32,12);

	mes.SetColor(CRCOLOR_GREEN);
	mes.DrawText("Cresteaju");
	mes.AddReturn();
	mes.SetColor(CRCOLOR_WHITE);
	mes.DrawText("   Version ");
	sprintf(s,"%d.%02d%c",CresteajuVersion.Major,CresteajuVersion.Minor,
		laststr[CresteajuVersion.LastString]);
	mes.DrawText(s);
	mes.AddReturn();
	mes.DrawText("   Copyright(C) 2001 Shou/Shogo Kawai All rights reserved.");
	mes.AddReturn();
	mes.AddReturn();

	//---������
/*	mes.SetColor(CRCOLOR_YELLOW);
	mes.DrawText("   DirectDraw :");
	mes.SetColor(CRCOLOR_WHITE);
	if(eiIsDirectDrawHAL())
		mes.DrawText("HAL");
	else
		mes.DrawText("HEL");
	mes.AddReturn();*/

	mes.SetColor(CRCOLOR_YELLOW);
	mes.DrawText("   Direct3D         : ");
	mes.SetColor(CRCOLOR_WHITE);
	mes.DrawText(eiGetDDInfo()->Direct3DUsingDeviceName);
	mes.AddReturn();

	mes.SetColor(CRCOLOR_YELLOW);
	mes.DrawText("   VideoMemory Total: ");
	mes.SetColor(CRCOLOR_WHITE);
	sprintf(s,"%5d",eiGetDDMaxViedoMemory() / 1024);
	mes.DrawText(s);
	mes.AddReturn();

	mes.SetColor(CRCOLOR_YELLOW);
	mes.DrawText("               Use  : ");
	mes.SetColor(CRCOLOR_WHITE);
	sprintf(s,"%5d",(eiGetDDMaxViedoMemory() - eiGetDDFreeViedoMemory()) / 1024);
	mes.DrawText(s);
	mes.AddReturn();

	mes.SetColor(CRCOLOR_YELLOW);
	mes.DrawText("        RefreshRate : ");
	mes.SetColor(CRCOLOR_WHITE);
	sprintf(s,"%5d",crdataGetIniFile()->RuningRefreshRate);
	mes.DrawText(s);
	mes.AddReturn();

	

	ew->Refresh();

	crbaseMenuStart();

	CrInput ci;
	ci.WaitAnykey();

	return 1;
}


int crmainConfig_SetDrawRate(void)
{
	int ret;
	CrMessageWindow mes;
	CrDigitWindow win;

	crbaseMenuReset();
	win.Create(256,48,12,4,"",4);
	CONFIGMESWIN_CREATE(120);
	win.Refresh();
	mes.Message("���t���b�V�����[�g�ɑ΂����ʍX�V�����ł��B\\n;"
		"100�����t���b�V�����[�g�ɍ��킹�čX�V�A200�łQ��ɂP��̍X�V�ɂȂ�܂��B");
	mes.Draw(-1,0,0);
	mes.Refresh();

	crbaseMenuStart();
	win.SetRange(100,800);
	ret = win.GetDigit(crdataGetSystem()->DrawRate,2);
	crdataGetSystem()->DrawRate = ret;

	ef->SetDrawRate(crdataGetSystem()->DrawRate);

	return 0;
}

int crmainConfig_SetAutoChangeFPS(void)
{
	int ret;
	CrMessageWindow mes;
	CrSelectWindow win;
	CRWIN_SELECTINFO info;

	memset(&info,0,sizeof(info));
	info.Offset = 1 - crdataGetSystem()->AutoDrawFrame;

	crbaseMenuReset();
	win.Create(256,48,12,5,""," �n�m ;�n�e�e;");
	mes.Create(256,136,20,9);
	win.Refresh();
	mes.Message("��ʕ`��������I�ɒ��߂���@�\�ł��B\\n;"
		"�h�t�B�[���h�X�V�p�x �h���傫���l�̎��͂n�e�e�ɂ����������ꂢ�ɂȂ�܂��B");
	mes.Draw(-1,0,0);
	mes.Refresh();

	crbaseMenuStart();
	ret = win.Select(&info);
	if(ret != -1){
		crdataGetSystem()->AutoDrawFrame = 1 - ret;
		if(1 - ret == 0){
			ef->SetDrawMode(EF_DRAW_MANUAL);
		} else {
			ef->SetDrawMode(EF_DRAW_AUTOCHANGE);
		}
	}

	return 0;
}

int crmainConfig_SetKeyWaitAfterPush(void)
{
	int ret;
	CrMessageWindow mes;
	CrDigitWindow win;

	crbaseMenuReset();
	win.Create(256,144,12,4,"",4);
	CONFIGMESWIN_CREATE(216);
	win.Refresh();
	mes.Message("�ŏ��ɃL�[��������Ăǂ̂��炢�o���Ă���L�[���s�[�g���J�n���邩�̐ݒ�ł��B\\n;"
		"�P�ʂ̓~���b�ł��B");
	mes.Draw(-1,0,0);
	mes.Refresh();

	crbaseMenuStart();
	win.SetRange(50,2000);
	ret = win.GetDigit(crdataGetSystem()->KeyWaitAfterPush,2);
	crdataGetSystem()->KeyWaitAfterPush = ret;

	return 0;
}

int crmainConfig_SetKeyWaitDelay(void)
{
	int ret;
	CrMessageWindow mes;
	CrDigitWindow win;

	crbaseMenuReset();
	win.Create(256,144,12,4,"",4);
	CONFIGMESWIN_CREATE(216);
	win.Refresh();
	mes.Message("�L�[���s�[�g�̊Ԋu�ł��B\\n;"
		"�P�ʂ̓~���b�ł��B");
	mes.Draw(-1,0,0);
	mes.Refresh();

	crbaseMenuStart();
	win.SetRange(100,2000);
	ret = win.GetDigit(crdataGetSystem()->KeyWaitDelay,2);
	crdataGetSystem()->KeyWaitDelay = ret;

	return 0;
}

int crmainConfig_SetMenuWait(void)
{
	int ret;
	CrMessageWindow mes;
	CrDigitWindow win;

	crbaseMenuReset();
	et->Reset();
	win.Create(256,144,12,4,"",4);
	CONFIGMESWIN_CREATE(216);
	win.Refresh();
	mes.Message("���j���[�؂芷�����̑҂����Ԃł��B"
		"�Ԋu���Z���ƃE�B���h�E�̐؂�ւ����X���[�Y�ɂȂ�܂����A�L�[�����������Ȃ肷���Ď��̃��j���[���I�����Ă��܂����Ƃ�����܂��B\\n;"
		"�P�ʂ̓~���b�ł��B");
	mes.Draw(-1,0,0);
	mes.Refresh();

	et->Wait2(350);
//	crbaseMenuStart();
	win.SetRange(50,2000);
	ret = win.GetDigit(crdataGetSystem()->MenuWaitTime,2);
	crdataGetSystem()->MenuWaitTime = ret;

	return 0;
}

int crmainConfig_SetBattleAngle(void)
{
	int ret;
	CrMessageWindow mes;
	CrSelectWindow win;
	CRWIN_SELECTINFO info;

	crbaseMenuReset();
	win.Create(256,212,12,8,"","�T�C�h�r���[�P;�������_;�T�C�h�r���[�Q;�G���_;");
	mes.Create(256,128,20,5);
	win.Refresh();
	mes.Message("�퓬�ł̎��_�ł�");
	mes.Draw(-1,0,0);
	mes.Refresh();

	crbaseMenuStart();
	memset(&info,0,sizeof(info));
	info.Offset = crdataGetSystem()->BattleCameraAngle;
	ret = win.Select(&info);
	if(ret != -1){
		crdataGetSystem()->BattleCameraAngle = ret;
	}

	return 0;
}

int crmainConfig_SetBattleCameraMoving(void)
{
	int ret;
	CrMessageWindow mes;
	CrSelectWindow win;
	CRWIN_SELECTINFO info;

	crbaseMenuReset();
	win.Create(256,212,12,6,"","�؂�ւ���;�X���[�Y�Ɉړ�;");
	mes.Create(256,128,20,5);
	win.Refresh();
	mes.Message("�퓬���̃J�����ړ������炩�ɂ��邩�A�؂�ւ��ɂ��邩�̐ݒ�ł��B\\n;");
	mes.Draw(-1,0,0);
	mes.Refresh();

	crbaseMenuStart();
	memset(&info,0,sizeof(info));
	info.Offset = crdataGetSystem()->BattleMoveCamera;
	ret = win.Select(&info);
	if(ret != -1){
		crdataGetSystem()->BattleMoveCamera = ret;
	}

	return 0;
}

int crmainConfig_SetBattleCommandReset(void)
{
	int ret;
	CrMessageWindow mes;
	CrSelectWindow win;
	CRWIN_SELECTINFO info;

	crbaseMenuReset();
	win.Create(256,212,16,7,"","�^�[�����ƂɃ��Z�b�g����;�o�g�����ƂɃ��Z�b�g����;���Z�b�g���Ȃ�;");
	mes.Create(256,128,20,5);
	win.Refresh();
	mes.Message("�퓬���̃R�}���h��ۑ����邩�A�����Z�b�g���邩�̐ݒ�ł�\\n;");
	mes.Draw(-1,0,0);
	mes.Refresh();

	crbaseMenuStart();
	memset(&info,0,sizeof(info));
	info.Offset = crdataGetSystem()->BattleCommandReset;
	ret = win.Select(&info);
	if(ret != -1){
		crdataGetSystem()->BattleCommandReset = ret;
	}

	return 0;
}

//---�R���t�B�O
int crmainMenuSystemConfig(void)
{
	int ret;
	CrSelectWindow win;
	eistr string[512];
	static CRWIN_SELECTINFO info;
	//---���j���[�֐��e�[�u��
	int (*MenuTable[])(void) = {
		NULL,
		NULL,
		crmainConfig_SetDrawRate,crmainConfig_SetAutoChangeFPS,
		NULL,
		crmainConfig_SetKeyWaitAfterPush,crmainConfig_SetKeyWaitDelay,
		crmainConfig_SetMenuWait,
		NULL,
		crmainConfig_SetBattleAngle,crmainConfig_SetBattleCameraMoving,
		crmainConfig_SetBattleCommandReset,
		NULL,
		NULL,NULL
	};

	eistr *battlecamera[] = {
		"�T�C�h�r���[�P","�������_","�T�C�h�r���[�Q","�G���_"
	};

	do {
		crmainClearMenu();
		crbaseMenuReset();
		sprintf(string,
			"�S�Ă̐ݒ��W���ɖ߂�;"
			"\\4�t�B�[���h�ݒ�...;\\7"
			"    �t�B�[���h�X�V�p�x        : \\6%d\\7;"
			"    �t�B�[���h�`��̎����ύX  : \\6%s\\7;"
			"\\4�L�[�{�[�h�ݒ�...\\7;"
			"    �L�[�{�[�h���s�[�g�J�n����    : \\6%d\\7�~���b;"
			"    �L�[�{�[�h���s�[�g�Ԋu        :\\6%d\\7�~���b;"
			"    ���j���[�؂芷�����̑҂�����  :\\6%d\\7�~���b;"
			"\\4�퓬�ݒ�...\\7;"
			"    �o�g�����_      :  \\6%s\\7;"
			"    �J�����ړ�      :  \\6%s\\7;"
			"    �o�g���R�}���h  :  \\6%s\\7;"
			,crdataGetSystem()->DrawRate,
			crdataGetSystem()->AutoDrawFrame ? "ON" : "OFF",
			crdataGetSystem()->KeyWaitAfterPush,
			crdataGetSystem()->KeyWaitDelay,
			crdataGetSystem()->MenuWaitTime,
			battlecamera[crdataGetSystem()->BattleCameraAngle],
			crdataGetSystem()->BattleMoveCamera ? "�X���[�Y" : "�؂�ւ�",
			crdataGetSystem()->BattleCommandReset == 0 ? "�^�[�����ƂɃ��Z�b�g" : 
		(crdataGetSystem()->BattleCommandReset == 1 ? "�퓬���ƂɃ��Z�b�g" : "���Z�b�g���Ȃ�")
			);
		win.Create(32,32,28,17,"�R���t�B�O",string);
//		win.Refresh();
		ew->Refresh();

		crbaseMenuStart();
		ret = win.Select(&info);
		if(ret != -1){
			if(ret == 0){
				//---�f�B�t�H���g�I�I
				crdataInitData();
			} else if(MenuTable[ret] != NULL){
				(*MenuTable[ret])();
			}
		}

	} while(ret != -1);

	return MAINLOOP_NOMESSAGE;
}

//---�V�X�e��
int crmainMenuSystem(void)
{
	int ret;
	CrSelectWindow win;
	static CRWIN_SELECTINFO info;

	memset(&info,0,sizeof(info));

	do {
		crmainClearMenu();
		crbaseMenuReset();
		if(evGet(260) == 0){
			//---�N���A�O
			win.Create(32,32,10,9,"�V�X�e�����j���[","�R���t�B�O; �Z �[ �u ; �� �[ �h ;�o�[�W����;�Q�[���I��;",
				1,12);
		} else {
			win.Create(32,32,10,10,"�V�X�e�����j���[","�R���t�B�O; �Z �[ �u ; �� �[ �h ;�o�[�W����; �f �[ �^ ;�Q�[���I��;",
				1,12);
		}
		ew->Refresh();

		crbaseMenuStart();
		ret = win.Select(&info);

		if(ret == 0){
			crmainMenuSystemConfig();
		} else if(ret == 1){
			crmainMenuSave();
		} else if(ret == 2){
			if(crmainMenuLoad() == MAINLOOP_RELOADMENU)
				return MAINLOOP_RELOADMENU;
		} else if(ret == 3){
			crmainSystem_VersionInfo();
		} else if(ret == 4 && evGet(260) == 1){
			crmainMainMenu_HiddenInfo();
		} else if(ret == 4 + (evGet(260) == 1 ? 1 : 0)){
			//---�I��
			CrSelectWindow win2;

			crbaseMenuReset();
			win2.Create(48,48,14,5,"�{���ɏI�����܂����H","����ς葱����;�I���;");
			win2.Refresh();
			crbaseMenuStart();
			if(win2.Select(&info) == 1){
				return MAINLOOP_ENDLOOP;
			}
		}

	} while(ret != -1);

	return MAINLOOP_NOMESSAGE;
}
