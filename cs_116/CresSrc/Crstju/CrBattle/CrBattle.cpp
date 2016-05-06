/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBattle.cpp ...Battle functions

-----------------------------------------------------------*/

#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBATTLE

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#include "..\CrBase.h"
#include "..\CrBattle.h"

#ifdef MAKE_DLL
	#define CR_GAMEINFO_POINTER
#else
	#define CR_GAMEINFO_EXTERNPOINTER
#endif /*MAKE_DLL*/
#include "..\CrGameInfo.h"

//---��蒼���p
ei_s32 BtKeepItem[ITEM_MAX],BtKeepItemCount[ITEM_MAX];

//---�ϐ�
CR_BATFIELDVERTEX BattleField[BATTLEFIELD_VERTEXCOUNT_X][BATTLEFIELD_VERTEXCOUNT_Y];
//CR_BATTLEINFO BattleInfo;
CrBattleCharacter BattleChara[BATTLECHARA_MAX],*pBtChara,
	KeepChara[KEEPCHARA_MAX],*pKeepChara;
CrBattleCharacter BattleTempChara[4],*pBtTempChara;
CrBattleObject BattleObject[BATTLEOBJECT_MAX],*pBtObject;
CR_BATTLEVIEW CameraPos;

eiD3DMaterial BattleFieldMaterial,BattleParticleMaterial;
eiD3DParticle BatPart[BATTLE_PARTMAX];
eiD3DLight BatLight[8];

//---���_�o�b�t�@�[
eiD3DVertexBuffer vbSrc,vbDest;

//---���E
CR_BATTLEVIEW BattleView[BATTLE_VIEWMAX];
int BattleViewMode = BATTLE_VIEWMODE_SINGLE;
RECT BattleViewRect[BATTLE_VIEWMAX][6];
float HViewNumber[BATTLE_VIEWMAX] = {4.0f,4.0f,8.0f,8.0f, 1.0f,1.0f,1.0f,1.0f};
int ViewNumber[BATTLE_VIEWMAX] = {1,1,2,1 ,1,1,1,1};

//---Anime
ei_s32 AnimePatternCount[BATTLE_ANIMEMAX] = 
{
	4,4,4,4
};

ei_s32 AnimePatternSize[BATTLE_ANIMEMAX] = 
{
	64,64,64,64
};

ei_s32 BattleAnimeWait[BATTLE_ANIMEMAX] = 
{
	60,60,60,60
};

int PreviousAnimeNumber = -1;

//---Range
ei_s32 BattleLineRange[12] =
{
	2,3,4,5,6,7,8,9
};

ei_s32 BattleCircleRange[12] =
{
	4,6,7,9,10,12,14,16
};

//---�s�����̏�������p�����[�^
ei_s32 BattleActionSource[16] = 
{
	0,1,0,0, 0,0,0,0 //--- 1:Magic
};

//---�p�^�[��
eiCell BattleCharaCell[BATTLE_CHARAPATTERN * 5];
eiCell BattleEnemyCell[BATTLE_ENEMYPATTERN];
eiCell BattleBackgroundCell[BATTLE_BGCELLMAX];
eiCell BattleRadarCell;
eiCell BattleAnimeCell[ANIMEPATTERN_1];
eiCell BattleStatusCell[BATTLE_STATUSICONMAX];
//---�e�N�X�`���[
eiTextureCell BattleFieldCell[BATTLE_FIELDCELLMAX],ShadowCell;

//---
ei_s32 BattleExperience,BattleMoney,BattleItem,BattleItemProb,BattleStartTime;

#include "CrBattleSubTest.cpp"

//---DLL�̏�����
CRBATTLE_API int crbatInitDLL(CRESTEAJU_GAMEDATA *pgameusingdata,
							 CRESTEAJU_GAMEINFO *pgame,
							 CRESTEAJU_PARTYINFO *pparty,
							 CrCharacter *pplayer,
							 CrItem *pitem,CrMagic *pmagic,
							 int *pdebug,int *pfilemode,
							 CRESTEAJU_SYSTEM *psystem,CRESTEAJU_INITIALIZE *pini,
							 CRESTEAJU_CHARACTERINFO *penemychara,CRESTEAJU_BATTLECHARAINFO *penemybat)
{
	pGameUsingData = pgameusingdata;
	pGameInfo = pgame;
	pPartyInfo = pparty;
	pCharacterInfo = pplayer;
	pItemInfo = pitem;
	pMagicInfo = pmagic;

	pEnemyCharaInfo = penemychara;
	pEnemyBatInfo = penemybat;

	//---
	pBtChara = &BattleChara[0];
	pKeepChara = &KeepChara[0];
	pBtObject = &BattleObject[0];
	pBtTempChara = &BattleTempChara[0];
//	crdataSetPointer(pdebug,pfilemode,psystem,pini);

	return 1;
}

//---�C�x���g�o�g��
CRBATTLE_API int crbatEventBattle(CR_BATTLEINFO *pInfo /*= NULL*/)
{
	int ret;

	if(pInfo->MapNumber == 0){
		pInfo->MapNumber = crfieldGetMapNumber();
	}
	ret = crbatGotoBattle(pInfo);

	return ret;
}

//---�ʏ�퓬
CRBATTLE_API int crbatFieldBattle(int map,int area)
{
	int a = 0,EnemyCount = 0;
	CR_BATTLEINFO BattleInfo;

	memset(&BattleInfo,0,sizeof(BattleInfo));
	BattleInfo.Music = -1;
	BattleInfo.EnebleAvoid = 1;
	if(map == 10)
		BattleInfo.ScreenEfect = 1;
	else
		BattleInfo.ScreenEfect = 1;
	BattleInfo.lpTurnCallBack = NULL;
	BattleInfo.MapNumber = crfieldGetMapNumber();
	BattleInfo.SceneNumber = crfieldGetMapScene();
	BattleInfo.AreaNumber = area;

	//---�G���A�t�@�C�����J��
	int flag = 0,start = 0,max_count = 0,count = 0,target = 0;
	eiFile file(CR_DATAFILE3);
	eistr s[100],*p,*u;
	sprintf(s,"%sar%03d.txt",CR_DATADIR3,map);
	if(file.Open(s) == 0){
		return 0;
	}

	while(file.GetLine(&s[0],80)){
		p = &s[0];
		//---���s���^�u�폜
		while(*p != NULL){
			if(*p == '\t'){
				*p = ' ';
			}
			if(*p == '\n' || *p == '\r'){
				*p = NULL;
				break;
			}
			p ++;
		}

		if(flag == 0 && s[0] == ':'){
			//---�G���A�擾
			if(atoi(&s[1]) == area){
				start = file.GetAddres();
				flag = 1;
			}
		} else if(flag == 1){
			//---�G�p�^�[���̐��𐔂���
			if(s[0] == ':'){
				//---���̃G���A���o���炻���ŏI��
				//---�G���A�̓G�p�^�[���擪�Ƀ|�C���^���ڂ�
				file.Seek(start);
				flag = 2;
				count = 0;
				target = eiRnd(max_count);
			} else if(s[0] != NULL){
				//---�G��񂪂����
				max_count ++;
			}
		} else if(flag == 2){
			//---�T���o��
			if(s[0] != NULL){
				if(count == target){
					//---�^�[�Q�b�g������������
					flag = 3;
					break;
				}
				count ++;
			}
		}
//		eiDebugWriteFile(s);
	}
	file.Close();
//	eiDebugWriteFile("\n***********************\n");
//	eiDebugWriteFile(s);
//	eiDebugWriteFile("\n");

/*	char ss[100];
	sprintf(ss,"max = %d : tar = %d : area = %d : flag = %d \n",
		max_count,target,area,flag);
	eiDebugWriteFile(ss);*/
	if(flag != 3){
		eiDebugWriteFile("�G��񌟍��Ɏ��s���܂���\n");
		return 0;
	}
	//---���
	for(EnemyCount = 0,p = u = &s[0];;EnemyCount ++){
		//---�G�i���o�[
		for(;*p != '(';p ++);
		*p = NULL;
		BattleInfo.Enemy[EnemyCount].Enemy = atoi(u);
//		eiDebugWriteFile(u);
//		eiDebugWriteFile("\n");
		p ++;
		u = p;

		//---x
		for(;*p != ',';p ++);
		*p = NULL;
		BattleInfo.Enemy[EnemyCount].x = atoi(u);
		eiDebugWriteFile(u);
		eiDebugWriteFile("\n");
		p ++;
		u = p;

		//---x
		for(;*p != ')';p ++);
		*p = NULL;
		BattleInfo.Enemy[EnemyCount].y = atoi(u);
		eiDebugWriteFile(u);
		eiDebugWriteFile("\n");
		p ++;
		u = p;

		//---���̈ʒu�܂�
		for(;*p != ',' && *p != ';';p ++);
		if(*p == ';'){
			//---��͏I��
			break;
		}
		for(p ++;*p == ' ';p ++);
		u = p;
	}

	//---���E���]���邩�ǂ���
	int dir_mode = eiRnd(2);

//	EnemyCount = eiRnd(4) + 1;
	for(a = 0;a < EnemyCount + 1;a ++){
//		BattleInfo.Enemy[a].Enemy = 1;
//		BattleInfo.Enemy[a].x = (BATTLEFIELD_MAX_X - 2) * a / EnemyCount + 1;
//		BattleInfo.Enemy[a].y = BATTLEFIELD_MAX_Y / 2 + eiRnd((BATTLEFIELD_MAX_Y - 2) / 2) + 1;
		BattleInfo.Enemy[a].y += (BATTLEFIELD_MAX_Y / 2);

		if(dir_mode){
			BattleInfo.Enemy[a].x = BATTLEFIELD_MAX_X - BattleInfo.Enemy[a].x;
		}
	}
	BattleInfo.Enemy[EnemyCount + 1].Enemy = -1;

	int moriuni = 0;
	if(map == 42 && /*!pGameInfo->Event[211] &&*/ pGameInfo->Event[160]){
		//---�Q���N���A
		//---�_�C�̐X
		if(eiRnd(1000) < 100){
			moriuni = 1;
		}
	}

	if(moriuni){
		//---�����E�j�I
		for(a = 0;a < EnemyCount + 1;a ++){
			BattleInfo.Enemy[EnemyCount + 1].Enemy = -1;
		}
		BattleInfo.Enemy[0].Enemy = 216;
		BattleInfo.Enemy[1].Enemy = -1;
		EnemyCount = 1;
	} else {
		//---�I�t�Z�b�g�o�g�����i�����E�j�o�g���͖����j
		BattleInfo.EnableOffsetBattle = OFFSETBAT_ENABLEALL;
	}

	crbatGotoBattle(&BattleInfo);

	return 1;
}

//---�o�g���G���g���[�|�C���g
CRBATTLE_API int crbatGotoBattle(CR_BATTLEINFO *pInfo)
{
	CR_BATTLEINFO *pBattleInfo = NULL;// = &info;
	int ret;

	if(pInfo != NULL){
		pBattleInfo = pInfo;
	}
	if(pInfo->Music != 0){
		//---���y�t�F�[�h�A�E�g
//		crmusicFadeOut();
	}

	eiDebugWriteFile("*******************************************************\n");
	//---��ʌ���
	RECT ScreenRect = {
		(640 - 32 * crdataGetInitialize()->IniFile.FieldSizeX) / 2,//80,
		(480 - 32 * crdataGetInitialize()->IniFile.FieldSizeY) / 2,//32,
		640 - (640 - 32 * crdataGetInitialize()->IniFile.FieldSizeX) / 2,//80 + 480,
		480 - (480 - 32 * crdataGetInitialize()->IniFile.FieldSizeY) / 2};//32 + 416 };
	if(pInfo->ScreenEfect == 1){
		if(crsysGetExtentionLevel() >= CR_EXTENTION_NORMAL){
//			crefectScreenEfect_FadeOut(&ScreenRect,125,RGB(255,255,255),0);
		}
		//---�o���[���I
		crefectScreenEfect_Bomb(&ScreenRect);
	} else if(pInfo->ScreenEfect == 2){
		if(crsysGetExtentionLevel() >= CR_EXTENTION_NORMAL){
//			crefectScreenEfect_FadeOut(&ScreenRect,125,RGB(255,255,255),0);
		}
		//---�Y�[���I
		crefectScreenEfect_RotateZoom(&ScreenRect);
	}

	//---�X���b�h�`�F�b�N�I
	eiCheckThread();

	//---�����ݒ�
	crbatInitBattle(pBattleInfo,0);
	//---�o�g���J�E���g�𑝂₷
	crhistBattleCount();

#if (CR_DEBUG == 1)
	if(crdataGetDebug()){
		ei->Get();
		if(ei->Return){
//			crbatTest();
		}
	}
#endif /* (CR_DEBUG == 1) */

	//---���[���h�l�b�ۑ�
	int world = crmagicGetMagicClass(24)->MagicInfo.UseMC;

	ret = crbatBattleMain(pBattleInfo);
	if(ret == BATRET_AVOID){
		//---��������
		crhistEscapeCount();
	}

	//---���[���h�l�b���A
	crmagicGetMagicClass(24)->MagicInfo.UseMC = world;

	//---�ۑ�����K�v������Ȃ炷��
	if(pInfo->KeepEnemyNumber){
		int a,b,num = pInfo->KeepEnemyNumber - 1;
		for(a = BATTLECHARA_STARTENEMY,b = 0;a < BATTLECHARA_STARTENEMY + BATTLE_ENEMYMAX;a ++,b ++){
			memcpy(&pKeepChara[num + b].CharaInfo,
				&pBtChara[a].CharaInfo
				,sizeof(pBtChara[a].CharaInfo));

			memcpy(&pKeepChara[num + b].OnlyInfo,
				&pBtChara[a].OnlyInfo
				,sizeof(pBtChara[a].OnlyInfo));

			memcpy(&pKeepChara[num + b].BattleInfo,
				&pBtChara[a].BattleInfo
				,sizeof(pBtChara[a].BattleInfo));

//			eiDebugWriteFile("hozonn:");
//			eiDebugWriteFile(pBtChara[a].GetName());
//			eiDebugWriteFile("\n");
		}
	}

	crbatEndBattle(pBattleInfo,0);

	return ret;
}
