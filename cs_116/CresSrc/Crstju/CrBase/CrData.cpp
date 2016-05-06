#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRDATA

#include "..\CrData.h"

int *pDebug,*pFileMode;
CRESTEAJU_SYSTEM *pSystem;
CRESTEAJU_INITIALIZE *pInitialize;

//---レベルアップ用データ宣言
ei_s32 LevelUpStatus[100] = 
{
	0,8,10,12,14, 16,18,20,23,26,
	29,32,35,38,41, 44,47,50,53,56,

	60,64,68,72,76, 80,84,88,92,96,
	100,104,108,112,116, 120,124,128,133,138,

	143,148,152,156,160, 163,166,169,172,174,
	176,178,180,181,182, 183,184,185,186,186,
	
	188,189,190,191,192, 193,194,195,196,197,
	198,199,200,201,202, 203,204,205,206,207,
	
	208,209,210,211,212, 213,214,215,216,217,
	218,219,220,221,222, 223,224,225,226,227
};

ei_s32 LevelUpLP[100] = 
{
	 0,23,26,31, 35,  41, 46, 53, 59, 67,
	76,86,97,108,120, 132,145,158,173,187,

	202,229,245,263,282, 301,322,344,366,389,
	413,437,461,475,502, 528,554,582,611,640,

	665,686,704,717,732, 748,760,774,789,802,
	816,829,843,856,869, 880,892,904,911,920,

	 931, 938, 942, 949, 952,   957, 962, 969, 977, 980,
	 987, 990, 996, 999,1006,  1010,1013,1017,1020,1024,

	1027,1029,1032,1037,1040,  1041,1046,1050,1051,1052,
	1057,1062,1070,1077,1081,  1092,1103,1111,1120,1136
};

ei_s32 LevelUpMC[100] = 
{
	0,9,10,12,14,    16,18,21,24,27,
	30,33,36,39,42,  45,48,51,54,57,

	 60, 64, 68, 72, 76,   80, 84, 88, 92, 96,
	100,105,110,115,120,  125,130,135,140,145,

	150,154,158,162,166,  170,173,176,179,182,
	187,190,193,195,198,  201,203,206,208,210,

	214,216,219,221,225,  228,232,233,235,238,
	240,243,246,248,251,  253,255,258,259,262,

	263,264,266,268,269,  270,272,273,276,277,
	279,280,281,282,284,  286,287,290,294,299
};

ei_s32 LevelUpMagicExp[100] = 
{
	 0,10,10,10,10,  10,15,15,15,15,
	20,20,20,25,25,  25,25,30,30,30,

	35,35,35,35,40,  40,40,45,45,45,
	45,50,50,50,50,  50,50,50,50,50,

	50,50,50,50,50,  50,45,40,40,35,
	34,34,34,34,34,  33,33,33,33,33,

	32,32,32,32,32,  31,31,31,31,31,
	30,30,30,30,30,  30,30,30,30,30,

	29,28,27,26,25,  24,23,22,21,20,
	19,18,17,16,15,  14,12,10,10,10,

//	 5, 5, 5, 5, 5,   5, 5, 5, 5, 5,
//	 5, 5, 5, 5, 5,   5, 5, 5, 5, 5
};

ei_s32 LevelUpExperience[101] = 
{
	0,15,36,72,129,                      220,353,530,742,1001,
	1300,1690,2190,2850,3705,            4810,6250,8000,10100,12720,

	15870,19670,24190,29510,35700,       42840,51400,61680,74000,88800,
	106560,127870,153400,184000,216000,  248000,279000,306000,336000,369000,

	405000,445000,480000,510000, 547000, 570000,600000,620000,640000,650000,
	660000,670000,680000,690000,700000,  700000,700000,700000,700000,700000,

	700000,700000,700000,700000,700000,  700000,700000,700000,700000,700000,
	700000,700000,700000,700000,700000,  700000,700000,700000,700000,700000,

	700000,700000,700000,700000,700000,  700000,700000,700000,700000,700000,
	700000,700000,700000,700000,700000,  700000,700000,700000,700000,700000
};

ei_s32 CharacterRateExperienceStart[PLAYER_MAX + 1] = 
{
	0,100, 98,103, 92, 98,103,104    ,0,0,0,0,0,100,100,100
//	0,100, 98,107, 90, 98,103,104
};
//---ルナン、ディザ、ナック、サヴィアー、ユミ、ライゼル、シンディ
ei_s32 CharacterRateExperienceEnd[PLAYER_MAX + 1] = 
{
	0,100,102, 95,107, 98,105, 99    ,0,0,0,0,0,100,100,100
//	0,100,102, 95,110, 98,105, 99
};

ei_s32 CharacterRateLP[PLAYER_MAX + 1] = 
{
//	0,100,135, 71, 85, 55,155,110    
	0,100,135, 73, 87, 55,155,110    ,0,0,0,0,0,100,100,100//2/12変更
};

ei_s32 CharacterRateMC[PLAYER_MAX + 1] = 
{
	0,200, 60,175,110, 75,  0,120    ,0,0,0,0,0,100,100,100// 11/17変更
//	0,200, 60,150,110, 75,  0,120
};

ei_s32 CharacterRatePower[PLAYER_MAX + 1] = 
{
	 0,75,200, 40,100, 60,180,110    ,0,0,0,0,0,100,100,100
};

ei_s32 CharacterRateVitality[PLAYER_MAX + 1] = 
{
	 0,100,150, 60,120, 80,130, 80   ,0,0,0,0,0,100,100,100
//	 0,70,150, 30,110, 55,130, 80 //1/17変更
};

ei_s32 CharacterRateAgility[PLAYER_MAX + 1] = 
{
	 0,80,150,115, 60, 70, 30, 100   ,0,0,0,0,0,100,100,100
};

ei_s32 CharacterRateSoul[PLAYER_MAX + 1] = 
{
	0,125, 65, 90,160, 50, 40,100    ,0,0,0,0,0,100,100,100
};

ei_s32 CharacterRateMagic[PLAYER_MAX + 1] = 
{
	0,150, 75,135,115,115, 10, 90   ,0,0,0,0,0,100,100,100// 11/17変更
//	0,150, 75,135,105,115, 10, 90 
//	0,150, 50,130, 75,100, 10, 80
};//

ei_s32 CharacterRateMagicExp[PLAYER_MAX + 1] = 
{
	0,140,30,137,90,65,0,68    ,0,0,0,0,0,100,100,100// 11/17変更
//	0,140,30,137,90,60,0,50
//	0,200,75,150,100,70,0,50
};

ei_s32 Character100perMagicLevel[6] = 
{
//	1,3,6,12,15,18
	1,1,1,1,1,1
};

//---ゲーム中に使う固定変数（レベルアップとかのセット
CRDATA void crdataSetGameUsing(CRESTEAJU_GAMEDATA *pdata)
{
	pdata->LevelUpExperience = &LevelUpExperience[0];
	pdata->LevelUpLP = &LevelUpLP[0];
	pdata->LevelUpMagicExp = &LevelUpMagicExp[0];
	pdata->LevelUpMC = &LevelUpMC[0];
	pdata->LevelUpStatus = &LevelUpStatus[0];

	pdata->CharacterRateAgility = CharacterRateAgility;
	pdata->CharacterRateExperienceEnd = CharacterRateExperienceEnd;
	pdata->CharacterRateExperienceStart = CharacterRateExperienceStart;
	pdata->CharacterRateLP = CharacterRateLP;
	pdata->CharacterRateMagic = CharacterRateMagic;
	pdata->CharacterRateMagicExp = CharacterRateMagicExp;
	pdata->CharacterRateMC = CharacterRateMC;
	pdata->CharacterRatePower = CharacterRatePower;
	pdata->CharacterRateSoul = CharacterRateSoul;
	pdata->CharacterRateVitality = CharacterRateVitality;
	pdata->Character100perMagicLevel = Character100perMagicLevel;

	int a,test,test2;

	for(a = 1,test = 0,test2 = 0;a < 100;a ++){
		LevelUpExperience[a] += LevelUpExperience[a - 1];
		test += LevelUpMagicExp[a];
		if(a <= 40)
			test2 += LevelUpMagicExp[a];
//	sprintf(s,"level %d = %d\n",a,LevelUpExperience[a]);
//	eiDebugWriteFile(s);
	}

	char s[80];
	sprintf(s,"MagicExp = %d,%d\n",test,test2);
	eiDebugWriteFile(s);
}

//---ポインタをセット
CRDATA void crdataSetPointer(int *pdebug,int *pfilemode,
							 CRESTEAJU_SYSTEM *psystem,CRESTEAJU_INITIALIZE *pini)
{
	pDebug = pdebug;
	pFileMode = pfilemode;
	pSystem = psystem;
	pInitialize = pini;
}

//---変数を初期値に設定
CRDATA void crdataInitData(void)
{
	/*CrDebug = CR_DEBUG;
	CrFileMode = EI_NORMALFILE;*/

	memset(pSystem,0,sizeof(CRESTEAJU_SYSTEM));

	pSystem->DrawCenterCharacter = 1;
//	pSystem->DisplayRefreshRate = 60;
	pSystem->DrawRate = 100;
	pSystem->AutoDrawFrame = 1;

	//---キーボード設定
	pSystem->KeyWaitDelay = 150;//4;
	pSystem->KeyWaitAfterPush = 200;//12;

	pSystem->MenuWaitTime = 250;//16;

	int alpha[4] = {192,160,160,128};

	//---
	pSystem->WindowColor[0][0] = RGBA_MAKE(  0,  0,160,alpha[0]);
	pSystem->WindowColor[0][1] = RGBA_MAKE(  0,128,192,alpha[1]);
	pSystem->WindowColor[0][2] = RGBA_MAKE(  0,  0, 32,alpha[2]);
	pSystem->WindowColor[0][3] = RGBA_MAKE(  0, 64, 96,alpha[3]);
	//---
	pSystem->WindowColor[1][0] = RGBA_MAKE(  0,  0,  0,alpha[0]);
	pSystem->WindowColor[1][1] = RGBA_MAKE( 64, 64, 64,alpha[1]);
	pSystem->WindowColor[1][2] = RGBA_MAKE( 16, 16, 16,alpha[2]);
	pSystem->WindowColor[1][3] = RGBA_MAKE( 32, 32, 32,alpha[3]);
	//---
	pSystem->WindowColor[2][0] = RGBA_MAKE(  0,  0,  0,alpha[0]);
	pSystem->WindowColor[2][1] = RGBA_MAKE( 64, 64, 64,alpha[1]);
	pSystem->WindowColor[2][2] = RGBA_MAKE( 16, 16, 16,alpha[2]);
	pSystem->WindowColor[2][3] = RGBA_MAKE( 32, 32, 32,alpha[3]);
	//---
	pSystem->WindowColor[3][0] = RGBA_MAKE(  0,  0,  0,alpha[0]);
	pSystem->WindowColor[3][1] = RGBA_MAKE(  0,  0,  0,alpha[1]);
	pSystem->WindowColor[3][2] = RGBA_MAKE(  0,  0,  0,alpha[2]);
	pSystem->WindowColor[3][3] = RGBA_MAKE(  0,  0,  0,alpha[3]);
//	pSystem->Init = 0;

	pSystem->BattleMoveCamera = 1;
	pSystem->BattleCameraAngle = 0;//---サイド
	pSystem->BattleMoveCamera_AsInputCommand = 1;
	pSystem->BattleMoveCameraTime_AsInputCommand = 500;
	pSystem->BattleCommandReset = 0;

	//---セーブデータナンバー
	pSystem->SaveNumber = -1;
}

CRDATA CR_INIFILE *crdataGetIniFile(void)
{
	return &pInitialize->IniFile;
}

CRDATA CRESTEAJU_SYSTEM *crdataGetSystem(void)
{
	return pSystem;
}

CRDATA CRESTEAJU_INITIALIZE *crdataGetInitialize(void)
{
	return pInitialize;
}

CRDATA int crdataGetDebug(void)
{
	return *pDebug;
}

CRDATA int crdataGetFileMode(void)
{
	return *pFileMode;
}

int MovieEnable = 1;
CRDATA void crdataEnableRec(int mode)
{
	MovieEnable = mode;
}

CRDATA int crdataIsEnableRec(void)
{
	return MovieEnable;
}
