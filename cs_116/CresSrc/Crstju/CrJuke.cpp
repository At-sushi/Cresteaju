
int MusicFlag[100],MusicTable[100];

char *JukeComment[] = 
{
//---1
"�N���X�̋Ȃ̒��ł��A\
���́h�~�t�@�[���[�h�̃����f�B���܂��v�������сA\
���̋Ȃ�����n�߂܂����B\r\n\
���C���ƂȂ郁���f�B�[�́A���̋Ȃ̒��ł��g���Ă܂��B\r\n\
���́E�E�E���̋Ȃ̓��~�b�N�X�ł������肵�܂��B\
",

//---2
"���Ƃ��Ă͔��`�ɒ������A�薼����l�����Ȃł��B\
���̑��̂悤�ɗ͋����E�E�E���ǂ����͂킩��܂��񂪁A\
���X�A�N���X�ł̎g�������ǂ����悤���Y��ł����Ȃł��B\r\n\
�����ɃI�[�v�j���O�ɂ̂��Ă݂���A���������������肵�āA���̂܂�܎���܂��B\r\n\
�����āA�I�[�v�j���O�����ł͂��������Ȃ��̂ŁA�G�^�[�i����ł��g�����ƂƂȂ�܂����B",

//---3
"���̒��ɂ���悤�ȁA�ڂ���Ƃ��������ō��܂����B\
���i���̖��̒��A�����Č��f�̐X�̓����ꏊ�ł�����܂��B\r\n\
�i�F�����ł͓����ꏊ�ƖY��Ă��܂��Ă��A�ȂŋL�������т��邱�Ƃɂ��A\
�v���o�����Ƃ��ł��܂��B",

//---4
"�B��̃t�B�[���h�ȁB\r\n\
����A�t�B�[���h�Ȃ͂P�ł������Ƃ́A\
���̋Ȃ��ł������_�Ō��܂�܂����B�����Ă����ȂȂ񂾂���B\r\n\
���̋C�ɓ���悤�́A�G���f�B���O������킩��܂���ˁB",

//---5
"���g�e�b���񂩂�A�h�V�b�N�ȃo�g���Ȃ��h�Ƃ̗v�]�ō�����Ȃł��B\r\n\
���ʂ̃o�g���Ȃ����A�Z���ăV���v���ł��B\r\n\
����܂�Q�[���̐퓬�̋Ȃ��ۂ��Ȃ��̂�ڎw���Ă݂���ł����E�E�E\
������ƒ��r���[�����������B\r\n\
�����f�B�́A�{���T�b�N�X�����Ȃ�ł����A�f�l�^�f�r�łł͖ڗ����Ȃ����߁A\
�X�g�����O�X���d�˂Ă܂��B",

//---6
"�Ƃ��Ă����A���ȃ^�C�g���B�i�΁j\
���̒ʊw�H�ł���A��Ԃ悭�ʂ铹�������P�R�S�����B\
�C�����𑖂蔲����u���������̋Ȃł��B\r\n\
�������A�t�@���t�@�[���ƍ��킹�ăC���[�W���č��܂����B\
�Ƃ͂������̂́A�����܂����蒪�����Ԃ�����A����ȓ�������̂ł��B",

//---7
"�^�e��L2000�̗��̌�ɍ�����Ȃł��B\
�ƂĂ��L���A�����Ƒ������𑖂��Ă��܂����B\r\n\
���Ƃ����ƐÂ��ȗ��������Ȃł����A\
��̂悤�ȍ쐬���@����A����ȋȂɎd�オ���Ă܂��B",

//---8
"�Ȃ��h�����΁h�ł͂Ȃ��h���������΁h�Ȃ̂��H\
�@�����P�Ɍꊴ�������A�Ƃ������R����ł��B\r\n\
���������Ƃ��̋����ŁA�Ȗ������߂Ă��܂����Ƃ����΂��΁E�E�E",

//---9
"�����Ă̒ʂ肢��������ȋȂł��B\
�X�Ƃ����A�Ƃ��ŗ����̂ŁA����Ȃ���ł������ƁB",

//---10
"�����q������ɋ����o���A���r���[�ȓ����c�A�V���[�e�B���O�X�^�[�̃e�[�}�ł��B\
�O�����Ȃ�āA����Ŋm�F�ł��邩�ǂ����A���肬��̖��邳�B\
����Ȗ��邳�ɂ������炸�A��u�ŔR���s���Ă��܂��ނ�B�j�āB",

//---11
"�哹�|�l�i���́j�̃e�[�}�ȁB���̂��ۂ�����Ă݂܂����B\r\n\
�Ƃ͌������̂́A���͉��̂��قƂ�ǒm��Ȃ��̂ŁA\
���͂ɂ��܂ЂƂ����Ă��܂��܂����B\r\n\
���́E�E�E�̎��������Ƃ����ł��B\r\n\
�O�t�ɂ��Ȃ��Ă��Ԑ���オ�镔����\
�A�h�l�����C�[���@��w�̕��������h�ƉS���܂��B�S���܂��傤�B\r\n\
���̌�̔��t�����̕����́A��������肪����܂��B�Ђ����`�B",

//---12
"�����Ɏ�l���̖��O�Ƃ������Ă�ȁB\r\n\
���Ƃ��Ƃ́A�Ԃœ��̒��x�s����Ɍ������������Ƃ��͂��܂�ł��B\r\n\
���̋Ȃ��A��ʓI�ȃQ�[���̐퓬�ȂƂ͕��͋C��ς��悤�Ƃ��܂����B\
�������t�ŁA�ǂꂾ���Ⴄ�����f�B�[���o���邩�A\
�������������Ƃ������Ă݂܂����B",

//---13
"�S�ł̋ȁB�ł����邢�ł��B\r\n\
�S�ł�����Â��Ȃ�����āA�Q�[���I�[�o�[�A�ł͂Ȃ��āA\
�h����ꂳ�܁h�Ƃ������ƂŁA���������Ȓ��ɂ��܂����B\r\n\
�킢�̉S���x�[�X�ɂȂ��Ă邱�ƂɋC�Â������ȁH",

//---14
"�ŏ��A���̋Ȃ͂���܂���ł������A\
following the wind���ǂ��ɂ����ɂ͌��C�����č�������̂ł��B\
",

//---15
"�^�C�g���ƃQ�[�����Ŏg�����ʂɂ͊֌W���Ȃ��ł��B(^^;\r\n\
�������̖ڊo�߂́A�����Ƃ���Ȋ����Ȃ�ł��傤�B",

//---16
"�K����������Ȃ��l�B�̃e�[�}�B\r\n\
����The Eternal�ƃ����f�B�͈ꏏ�ł����A\
�������̕������Ƃ�����܂����B\
���C�̂Ȃ��ƁA�������邳��������Ɠ`����Ă���悤�ȋȂł��B\
�ł��A���͂��C�ɓ���B",

//---17
"�G�^�[�i���̃e�[�}�B�ł�����܂肩����@��Ȃ��Ă��킢�����ł����B�i�΁j\r\n\
�Ȏ��̂��A����قǖڗ����̂ł͂Ȃ��n���ł��B",

//---18
"�s���`���ۂ����ɗ����Ȃł��B\r\n\
���������ō������A�ւ����҂ȃo���h�̂悤�Ȋ����ɂȂ��Ă��܂��܂������A\
����͂���ŗǂ��Ƃ��܂��傤�B\r\n\
����Ȃ�Ă͌ꊴ�d���̃^�C�g���ł��ˁB",

//---19
"�����Ă�Ƃ��A�����Ă�Ƃ��A�����Ă�����Ƃ��������̂Ƃ��A\
����ȂƂ��ɂ��̋Ȃ�����Ă��܂��B\r\n\
�����Ă̒ʂ�AEndless Way�����ȂɂȂ��Ă܂��B",

//---20
"���������X�g�����O�X�I�����[�̋ȁB\
���f�̐X���������邽�߂ɁA���������̎g�p�ȂɂȂ��Ă܂��B",

//---21
"�N���C�V���̃e�[�}�B\r\n\
�s�C���ȁA�ł��߂������͋C��Y�킷�E�E�E���������������ō��܂����B\r\n\
�ł��A���̋Ȃ�����オ��O�ɁA���������̃C�x���g�͏I������Ⴄ�񂾂ȁB\
���ꂪ�B",

//---22
"�w�Z�ɂ��āA�ӂƌ������̕���������A\
��_������������Ɖ_�������オ���Ă܂����B\
�������������̂����̋Ȃł��B\r\n\
�Ђ�����A��������炵�����Ă܂��B",

//---23
"�hSunday Sunday�h�Ɠǂ݂܂��B�����R�[�h�Ɏw���\�����Ȃ������̂ŁA\
����ȏ������ɂȂ��Ă��܂��܂����B\
����BASIC�ň�������Ƃ��ꔭ�ł킩��܂��ˁB�i�΁j\r\n\
�܂��Apow(Sunday,2);�Ȃ�ď�������s�C���Ȃ��Ƃ��̏�Ȃ����E�E�E\r\n\
�R�A���n�̌y���ȋȂł��B���̒��ł͈�Ԃ̂��C�ɓ���ł��B",

//---24
"��x��������A��x�Ɠ����痣��Ȃ��ł��낤�ȁB\
�ō��̃C���p�N�g���ւ�܂��B\r\n\
���Ƃ��Ƃ̓N���X�Ŏg������͂Ȃ�������ł����A\
���܂�̌��I�ȉ��ɗU�f����A�}�[�`�A�����W��A\
�s�C�����𑝂��ăN���X�Ŏg�����ƂƂȂ�܂����B",

//---25
"�h��w�̕��h���R�[�_�[�o�[�W�����B\r\n\
���̏Ό��I�Ȃ�������̏Ռ��I�ȉߋ��̘b�ŗ����Ȃł��B\r\n\
�e�e�X��V�񂾂��Ƃɍ�����͓̂����̘b�B�i�΁j",

//---26
"�w�֒T���ł��g���܂����A\
����V�[���Ŏg�����Ƃ�ړI�ɍ��܂����B\r\n\
Endless Way�����ȂƂȂ��Ă܂��B",

//---27
"�ΖL���ȑ��A�A���V�A�̉��y�ł��B\r\n\
�����̂�т肵�ĂāA�����̋C�������̂�т肵�Ă���E�E�E\
����ȑ��ł����A\
�A���V�A�̃��f�����āA���̑�w�Ȃ�ł��E�E�E",

//---28
"Endless Way�̃s�A�m�o�[�W�����B\
�ӂƍ���Ă݂���A����܂����������ɁB\
�C�ɓ����Ă��܂����̂ł��̂܂�܎g�����ƂƂȂ�܂����B",

//---29
"�O���E���h�V�b�v�̋Ȃł��B\r\n\
�e�e�X��V�сA�����̉��y�ɔ��`�Ɋ������āA\
������������Ƃ����̂���낤�Ƃ����ӋC���݂ŏo���オ�����Ȃł��B\r\n\
�u���ɑ��蔲����̂ł͂Ȃ��āA�̂�т�Ɣ�Ԃ悤�ȁA����Ȋ����ł��B\r\n\
���̒��ł͂P�C�Q�𑈂��قǂ��C�ɓ���ł��B",

//---30
"���i�����h�^�����󂷁h�ƌ����Ă܂������A��ɋȂ̕�������A\
����ɍ��킹�ĉ�b�����܂����B\r\n\
�o�g���Ȃ��āA�g����ʂō\����ς��܂��B\
�h�킢�̉S�h�͒ʏ�̐퓬�ŗ����ȂȂ̂ŁA\
�ŏ�����ԃC���p�N�g������悤�ɁA\
�����������C�x���g�ő����ė����Ȃ́A�ȑS�̂łЂƂ܂Ƃ܂�ɂȂ�悤�ɂ��܂��B\r\n\
���̋ȁA���́A�J���I�P�ɍs�����痬��Ă����ȋȁE�E�E\
���C���[�W���č������ł��B",

//---31
"�h���̏�ǁh�̃A�����W�o�[�W�����ł��B\
�������͐����̂���Ȃł����A������̕��͂������Ǝ₵�������ɂ��܂����B",

//---32
"���̋Ȃ͂��Ȃ�Â��ł��B\
�N���X�̂����܂��Șb�������܂��ĂȂ����ɍ��܂����B\r\n\
���̏�ǂƂ́A\
�������Ԃ�����Ă��܂��l�Ɛl�Ƃ̊Ԃɂ��錩���Ȃ��ǂ̂��ƁB",

//---33
"�_���W�����p�Ƃ��č�����Ȃł��B\r\n\
�ǂ��Ŏg���Ƃ܂ł͍l���Ă��܂���ł������A\
���̗₽����������A�Y���ꂽ��ՂŎg�����ƂȂ�܂����B\r\n\
�^�C�g�������ɍ����Ă�̂́A�g����ʂɍ��킹�ĕύX��������B",

//---34
"������Ɖ��z�ȃC�x���g�ŗ���܂��B\
�I���S�[���̈�ԍŌ�̋ȂɂȂ�l�������񂶂�Ȃ����ȁB\r\n\
�h���������΁h�����Ȃł��B",

//---35
"�~�_�Ղň�ȍ��A�Ƃ����͍̂l���Ă܂������A\
�ŏ��̓W�����W�����ƁA�I�[�P�X�g�����ۂ��̂ł�������ł����B\r\n\
�ł����ꂾ�Ƃׂ��ׂ��Ȃ̂ŁA������Ǝ����ς��āA\
������Ⴂ���Ǝv�����炢�̋Ȃɂ��Ă݂܂����B\
�V���o�[�����O�����ォ�炸���Ɨ������A\
�o�b�N�~���[�W�b�N�I�Ȃ��̂�_���Ă݂�����ł��B\r\n\
�hFated Force���h���̗́h�Ƃ́A�m���Ă̒ʂ�A\
���i���̂��Ƃł��B",

//---36
"�����Ƃ����Ɛ̂ɖł񂾓`���̓s�B���̍L��ȓs�ɂ͂����N�����Ȃ��E�E�E\
����ȕ��͋C���o���悤�ɂ��܂����B�h�łсh���e�[�}�ł��B\r\n\
���ʂȉ��͏o���邾�������ĉ��̓��������o���悤�ɁA\
���@���ȃx�[�X�ŋ󔒊����o���Ă܂��B���Ԃ�B\r\n\
�^�C�g���̜a���J�́A�ȂƁA���̌��t�̎����͋C���猈�߂܂����B\
�a�����Đ̂���h�s�g�ȁh���ۂ̑O�G��Ƃ��ċ����ꂽ��A\
�h�`���a���T���h�Ƃ��A�h�łсh�̃C���[�W�����͎����Ă��܂����B",

//---37
"�ŏI����̋Ȃł��B\r\n\
�ǂ��������Ȃ��������E�E�E���Ȃ�Y�݂܂����B\
���y����ŁA����オ������艺����������Ⴂ�܂���ˁB\r\n\
��l���ǂ����]�ނ��A�s����͂܂�ŋt�ł��B\
��������߂邽�߂̋Ȃ��A����ł��B\r\n\
�ϐg�ƋȂ̕ς��ڂ��ꏏ�Ȃ̂́A������A�ȂɃ��b�Z�[�W�����킹������B�i�΁j",

//---38
"�i���ɖڊo�߂ʎҁA���ꂪ�ڊo�߂�Ƃ��A�����N����̂��E�E�E\r\n\
����̓C�x���g�̒������l���A�Z�߂ɍ��܂����B",

//---39
"�{���́A��Ɏ��̗���̒��ɂ����ł��B\
�ł��������������̂��A\
��������Ĉ�l�����ɂȂ����Ƃ��Ȃ̂�������܂���B\r\n\
",

//---40
"���̏�ʁA�߂����͂��Ȃ񂾂��ǁA���y�͖��邢�ł��B\
�����ɔ߂������y�𗬂��ĕ��͋C��������������A\
���������Ȃɂ̂��āA���邭�G���f�B���O�����Ăق����ł��B\r\n\
���E�ɂƂ��Ă͂�����̂悤�Ȃ��̂ł��A�N���ɂƂ��ẮA\
���ꂪ�ƂĂ���؂Ȃ��̂������肵�܂��B\r\n\
�����̂̂��Ƃ��v���o���āA���R�Ɖ̂�����Ă������ȁA\
����ȋȂ�ڎw���܂����B",

//---41
"Endless Way�����ȂƂȂ��Ă܂��B\
���������L���₵��������Y�킵�܂����A\
������͉������A�₷�炮�悤�ɁA\
�ł��邾���V���v���ɍ��܂����B\
�����f�B�������Ɋo���Ă��炦�邩�Ǝv���܂��B\r\n\
�Ȃ𕷂��I������Ƃ��ɁA�S���ق��ق��Ƃ���悤�ȁA\
����Ȃ��Ƃ���������Ă����΂��ꂵ���ł��B\r\n\
Cresteaju�̃Q�[���͂���ŏI���ł����A����͂܂��܂������͂��ł��B",
};

int JukeCheck(void)
{
	int a;

	FILE *fp = fopen("cresjuke.exe","rb");
	if(fp == NULL)
		return 0;

	struct _finddata_t fd;
	_findfirst("cresjuke.exe",&fd);

	EIMEMORY hmem = eiAllocMemory(fd.size + 10000);
	if(hmem == NULL){
		fclose(fp);
		return 0;
	}

	ei_u8 *pdata = (ei_u8 *)eiLockMemory(hmem);

	fread(pdata,1,fd.size,fp);

	fclose(fp);


	//---�`�F�b�N
	for(a = 0;a < (int)fd.size;a ++){
		if(pdata[a] == 'c'){
			if(strcmp((char *)(pdata + a),"cres_juke__") == 0){
				break;
			}
		}
	}

	eiFreeMemory(hmem);

	if(a == (int)fd.size)
		return 0;

	return 1;
}

eiCell JukeCell[8],JukeLogo[10];

int Juke(void)
{
	int a,b,check,item = 0;
	char s[100];
	int NowHour,NowMinute;
	char *file_name[] = {
		"Asgray.acf","Rarfia.acf","Crasive.acf","Follne.acf",
		"Dizza.acf","Lunarn.acf","Lizel.acf",
		"Xavier.acf","Yumi.acf","Cindy.acf","Edo.acf",
		"uni.acf","Tozoku1.acf","Tozoku2.acf","Nack.acf"
	};

	if(JukeCheck() == 0){
		return 0;
	}

	_tzset();
	_strtime(s);
	s[2] = 0;
	s[5] = 0;
	NowHour = atoi(&s[0]);
	NowMinute = atoi(&s[3]);

	//--------------------------------------
	int charat = NowHour / 2;
	if(((NowHour == 7 || NowHour == 19) && NowMinute == 9)){
		charat = 14;
	}
	sprintf(s,CR_DATADIR2"%s",file_name[charat]);
	eiCellReadPattern(JukeCell,
		s,CR_DATAFILE2,EI_LINKEDFILE,
		0,8,32,32);

	for(a = 0;a < 10;a ++){
		sprintf(s,CR_DATADIR1"logo%02d.acf",a);
		JukeLogo[a].ReadFile(s,CR_DATAFILE1,EI_LINKEDFILE);
	}
	//--------------------------------------

	crdataSetGameUsing(&GameUsingData);
	CresteajuReadINIFile(crdataGetIniFile());
	crdataGetIniFile()->UseMIDI = 1;
	//--------------------------------------

	if(crmusicInitMusic() == 0){
		return 0;
	}

	//--------------------------------------
	memset(MusicFlag,0,sizeof(MusicFlag));
	memset(MusicTable,0,sizeof(MusicTable));

	for(a = 0;a < 16;a ++){
		crfileLoadData(a,SAVE_FILE_ID1,SAVE_FILE_ID2,16);

		for(b = 0;strcmp(crmusicGetTitleString()[b],"-silent-") != 0;b ++){
			if(pGameInfo->Music[b])
				MusicFlag[b] = 1;
		}

		if(critemGetItemCount(211) > 0){
			item = 1;
		}
	}
	//--------------------------------------

	if(item){
		check = DialogBox( hThisInst,"Juke",NULL,(DLGPROC)JukeFunc);
	} else {
		ShowError("CresJuke!!���g����Z�[�u�f�[�^������܂���");
	}

	//--------------------------------------
	for(a = 0;a < 8;a ++){
		JukeCell[a].Release();
	}
	for(a = 0;a < 10;a ++){
		JukeLogo[a].Release();
	}
	crmusicEndMusic();

	return 0;
}

void JukePlay(HWND hwnd,int number)
{
	SetDlgItemText(hwnd,IDC_COMMENT,JukeComment[number - 1]);

	if(crdataGetIniFile()->MIDIType >= 0){
		crmusicPlay(CRMUSIC_INIT);
		eiSleep(1500);
	}

	crmusicPlay(number,1,CRMUSIC_LOADFORCE);
}

#define JUKETIMER_ID 256
#define LOGOTIMER_ID 255

void JukeEnd(HWND hwnd)
{
	KillTimer(hwnd,JUKETIMER_ID);
	KillTimer(hwnd,LOGOTIMER_ID);

	EndDialog(hwnd,1);
}

extern LPSMIDI_STREAM pMidiStream[STREAM_MAX];

BOOL CALLBACK JukeFunc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	int a,tempo,offset = 0;
	static logo_num = 0,logo_mode = 0;
	static int TimerTempo = 120,Character = 0,AnimePos = 0;
	static int first = 1,number = 0,max,PlayFlag = 0;
	HWND hpic;
	HDC hdc;
	POINT point,cur;

	switch(message){
	case WM_TIMER:

		if(wParam == LOGOTIMER_ID){
			hpic = GetDlgItem(hwnd,IDC_CRESLOGO);
			hdc = GetDC(hpic);

			if(logo_mode == 0){
				if(++ logo_num >= 9){
					logo_num = 9;
					logo_mode = 1;
				}
/*			} else if(logo_mode == 1){
				if(-- logo_num <= 7){
					logo_mode = 0;
				}*/
			}

			JukeLogo[logo_num].dib.CopyToDC(hdc,0,0);

			ReleaseDC(hpic,hdc);

			return 1;
		}

		if(PlayFlag){
			offset = 4;
		} else {
			offset = 4;
		}

		hpic = GetDlgItem(hwnd,IDC_CHARA);
		hdc = GetDC(hpic);

		point.x = 16;
		point.y = 16;
		ClientToScreen(hpic,&point);
		GetCursorPos(&cur);
		cur.x -= point.x;
		cur.y -= point.y;
		if(cur.y < 0 && eiAbs(cur.x) < eiAbs(cur.y))
			offset = 0;
		else if(0 < cur.x && eiAbs(cur.y) < eiAbs(cur.x))
			offset = 2;
		else if(0 < cur.y && eiAbs(cur.x) < eiAbs(cur.y))
			offset = 4;
		else// if(0 < cur.x && eiAbs(cur.y) < eiAbs(cur.x))
			offset = 6;

		JukeCell[AnimePos + offset].dib.CopyToDC(hdc,0,0);
		ReleaseDC(hpic,hdc);

		if(PlayFlag && pMidiStream[0] != NULL){
			tempo = pMidiStream[0]->Tempo;
			if(tempo != 0){
				if(60 * 1000000 / tempo){
					if(60 * 1000000 / tempo != TimerTempo){
						int t = (tempo / (1000 * 60));
						if(t != 0){
							TimerTempo = 1000 / t;
							if(TimerTempo != 0){
								KillTimer(hwnd,JUKETIMER_ID);
								SetTimer(hwnd,JUKETIMER_ID,(60 * 1000 / TimerTempo) / 2,NULL);
							}
						}
					}
				}
			}
		}

		if(PlayFlag){
			if(++AnimePos >= 2)
				AnimePos = 0;
		}

		return 1;

	case WM_INITDIALOG:
		if(first){

			SetTimer(hwnd,JUKETIMER_ID,100,NULL);
			SetTimer(hwnd,LOGOTIMER_ID,200,NULL);
			crmusicPlay(CRMUSIC_INIT);
			eiSleep(1500);

			for(a = 1,max = 0;strcmp(crmusicGetTitleString()[a],"-silent-") != 0;a ++){
				if(MusicFlag[a]){
					SendDlgItemMessage(hwnd,IDC_LIST,CB_ADDSTRING,
						0,(LPARAM)crmusicGetTitleString()[a]);

					MusicTable[max] = a;

					max ++;
				}
			}
			first = 0;
		}

		SendDlgItemMessage(hwnd,IDC_LIST,CB_SETCURSEL,
			0,0);

		return 1;
	case WM_CLOSE:
		JukeEnd(hwnd);
		return 1;

	case WM_COMMAND:
		switch(LOWORD(wParam)){
		case IDOK:
		case IDC_JUKEEND:
			JukeEnd(hwnd);
			return 1;

		case IDC_STOP:
			crmusicStop();
			PlayFlag = 0;
			return 1;

		case IDC_PLAY:
			number = SendDlgItemMessage(hwnd,IDC_LIST,CB_GETCURSEL,
				0,0);
			JukePlay(hwnd,MusicTable[number]);
			PlayFlag = 1;
			return 1;

		case IDC_BEFORE:
			number = SendDlgItemMessage(hwnd,IDC_LIST,CB_GETCURSEL,
				0,0);
			if(--number < 0)
				number = max - 1;
			SendDlgItemMessage(hwnd,IDC_LIST,CB_SETCURSEL,
				number,0);
			JukePlay(hwnd,MusicTable[number]);
			PlayFlag = 1;
			return 1;

		case IDC_NEXT:
			number = SendDlgItemMessage(hwnd,IDC_LIST,CB_GETCURSEL,
				0,0);
			if(++number >= max)
				number = 0;
			SendDlgItemMessage(hwnd,IDC_LIST,CB_SETCURSEL,
				number,0);
			JukePlay(hwnd,MusicTable[number]);
			PlayFlag = 1;

			return 1;


		case IDC_ABOUT:
			DialogBox( hThisInst,"JukeAbout",hwnd,(DLGPROC)JukeAboutFunc);
			return 1;

		}
		break;
	}
	return 0;
}


BOOL CALLBACK JukeAboutFunc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch(message){
	case WM_CLOSE:
		EndDialog(hwnd,1);
		return 1;

	case WM_COMMAND:
		switch(LOWORD(wParam)){
		case IDOK:
			EndDialog(hwnd,1);
			return 1;
		}
	}
	return 0;
}
