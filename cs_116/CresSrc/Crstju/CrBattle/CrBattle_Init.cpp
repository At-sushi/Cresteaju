/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBattle_Init.cpp ...Battle Initialize functions

-----------------------------------------------------------*/

#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBATTLE_INIT

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#define EXTERN_CRBATTLE
#include "..\CrBase.h"
#include "..\CrBattle.h"

#define CR_GAMEINFO_EXTERNPOINTER
#include "..\CrGameInfo.h"

#include "CrBattle_InitSubChara.cpp"

static int EnemySurfaceX,EnemySurfaceY,EnemyPatternNumber;
static KeepMusic;

//---�I�u�W�F�N�g���
CRBATINIT_API int crbatReleaseBattleObject(void)
{
	int a;

	//---�R�c�I�u�W�F�N�g���
	if(eid3d->Begin(0)){
		eid3d->SetMaterial(NULL);
		eid3d->SetTexture(NULL);
		eid3d->End(0);
	}

	BattleFieldMaterial.Release();
	BattleParticleMaterial.Release();

	if(crdataGetIniFile()->BattleShadow){
		ShadowCell.ReleaseTexture();
	}
	//---�e�N�X�`���[���
	for(a = 0;a < BATTLE_FIELDCELLMAX;a ++){
		BattleFieldCell[a].ReleaseTexture();
	}

	vbDest.Release();
	vbSrc.Release();

	//---�L�����N�^�[�p�^�[�����
	for(a = 0;a < BATTLE_CHARAPATTERN * 5;a ++){
		if(BattleCharaCell[a].Data.CreateFlag){
			BattleCharaCell[a].Release();
		}
	}
	for(a = 0;a < BATTLE_ENEMYPATTERN;a ++){
		if(BattleEnemyCell[a].Data.CreateFlag){
			BattleEnemyCell[a].Release();
		}
	}
	//----------------------
	for(a = 0;a < BATTLE_STATUSICONMAX;a ++){
		if(BattleStatusCell[a].Data.CreateFlag){
			BattleStatusCell[a].Release();
		}
	}
	for(a = 0;a < BATTLE_BGCELLMAX;a ++){
		BattleBackgroundCell[a].Release();
	}
	BattleRadarCell.Release();
//	crbatReleaseAnime();

	return 1;
}

//---�o�g���I��
CRBATINIT_API int crbatEndBattle(CR_BATTLEINFO *pInfo,int thread_end)
{
	int a;
	//---�r������ݒ�
	eiWaitCriticalSection(1000);

	eiDebugWriteFile("(crbatEndBattle)\n");
	//---��ʃN���A
	if(pInfo != NULL){
		if(pInfo->Result == BATRET_WIN || pInfo->Result == BATRET_AVOID){
			crefectScreenChange_FadeOut();
		} else if(pInfo->Result == BATRET_FORCEBREAK){
			crefectScreenChange_FadeOut(NULL,-1,250);
		} else if(pInfo->Result == BATRET_LOSE){
			//---����
			crefectScreenChange_FadeOut(NULL,-1,3000);
		}
	} else if(thread_end == 0){
		crefectScreenChange_FadeOut(NULL,-1,250);
	}
	crbaseClearScreen(3);

	crbatReleaseBattleObject();

	//---�t�B�[���h�I�u�W�F�N�g���ăZ�b�g
	if(thread_end == 0){//---�X���b�h�I���łȂ����
		crfieldSetFieldObject();

		//---�f�[�^����
		for(a = CHARA_ENEMY;a < CHARA_ENEMY + BATTLE_ENEMYMAX;a ++){
			memset(&pBtChara[a].CharaInfo,0,sizeof(pBtChara[a].CharaInfo));
				memset(&pBtChara[a].BattleInfo,0,sizeof(pBtChara[a].BattleInfo));
			memset(&pBtChara[a].OnlyInfo,0,sizeof(pBtChara[a].OnlyInfo));
		}

		//---�f�[�^�R�s�[
		if(pInfo != NULL){
			crbatEndBattle_CopyCharaData(pInfo);
		}

		//---���y
		if(pInfo != NULL){
			if(pInfo->Music != 0){
				if(crdataGetIniFile()->OffsetPlay){
					crmusicRestoreStream(0);
				} else {
					crmusicPlay(KeepMusic,1,CRMUSIC_LOADFORCE);
				}
			}
		}
		//---�ǉ��f�[�^�ēǍ�
		crfieldLoadAddData();

		//---�R�[�h�ݒ�
		crsysSetCodeMode(CODE_FIELD);
	}

	//---�r���������
	eiDebugWriteFile("(crbatEndBattle)end\n");
	eiReleaseCriticalSection();

	return 1;
}

#include "CrBattle_InitSubScene.cpp"

static int EnemyOffsetX = -1,EnemyOffsetY = -1,EnemyOffsetSizeY = -1;

//---�G�̃p�^�[���ǂݍ���
CRBATINIT_API int crbatReadEnemyPattern(int number,int type,int retry)
{

	char s[80];
	sprintf(&s[0],CR_DATADIR3"eg%03d.acf",number);

#if (CR_DEBUG == 1)
	eiDebugWriteFile(s);
	eiDebugWriteFile(" reading....\n");
#endif
	if(number == 223){
		//---���X�g�o�g���I
		int start = 0;

		sprintf(&s[0],CR_DATADIR3"eg223.acf");
		eiCellReadPattern(&BattleEnemyCell[start * BATTLE_ENEMYPATTERNSIZE],
			s,CR_DATAFILE3,crdataGetFileMode(),
			0,4,32,32);
		eiCellSetSurface(&BattleEnemyCell[start * BATTLE_ENEMYPATTERNSIZE],
			0,256,32,32,4,3);
		start ++;

		sprintf(&s[0],CR_DATADIR3"eg223_2.acf");
		eiCellReadPattern(&BattleEnemyCell[start * BATTLE_ENEMYPATTERNSIZE],
			s,CR_DATAFILE3,crdataGetFileMode(),
			0,4,32,32);
		eiCellSetSurface(&BattleEnemyCell[start * BATTLE_ENEMYPATTERNSIZE],
			128,256,32,32,4,3);
		start ++;

		sprintf(&s[0],CR_DATADIR3"eg223_3.acf");
		eiCellReadPattern(&BattleEnemyCell[start * BATTLE_ENEMYPATTERNSIZE],
			s,CR_DATAFILE3,crdataGetFileMode(),
			0,4,32,32);
		eiCellSetSurface(&BattleEnemyCell[start * BATTLE_ENEMYPATTERNSIZE],
			256,256,32,32,4,3);
		start ++;

		sprintf(&s[0],CR_DATADIR3"eg224.acf");
		eiCellReadPattern(&BattleEnemyCell[start * BATTLE_ENEMYPATTERNSIZE],
			s,CR_DATAFILE3,crdataGetFileMode(),
			0,4,256,160);
		eiCellSetSurface(&BattleEnemyCell[start * BATTLE_ENEMYPATTERNSIZE],
			0,256 + 32,256,160,2,3);
		eiCellSetSurface(&BattleEnemyCell[start * BATTLE_ENEMYPATTERNSIZE + 2],
			0,0,256,160,2,4);
		start ++;

		EnemyPatternNumber ++;
//		EnemyPatternNumber = start;
	} else if(/*!retry*/1){

		int a,y,size,ptn_size = 32;
		eiCell temp;
		if(!temp.ReadFile(s,CR_DATAFILE3,crdataGetFileMode())){
			eiDebugWriteFile("(crbatReadEnemyPattern) can't read file.\n");
			return 0;
		}
		//---�K�v�ȃZ�������
		if(type == DRAWTYPE_4_ANIME){
			for(a = 0;a < 32;a ++){
				BattleEnemyCell[EnemyPatternNumber * ptn_size + a].Create(
				32,32,8);
			}
		} else {
			for(a = 0;a < 4;a ++){
				BattleEnemyCell[EnemyPatternNumber * ptn_size + a].Create(
				temp.Data.xSize / 4,temp.Data.ySize,8);
			}
		}

		//---�T�[�t�F�C�X�ɃZ�b�g
		int use_offset = 0;
		RECT rect;
		use_offset = 0;
		if(EnemyOffsetX + temp.Data.xSize < 640
			&& EnemyOffsetX != -1
			&& EnemyOffsetSizeY >= temp.Data.ySize){
			//---�L�����p
			SetRect(&rect,
				EnemyOffsetX,EnemyOffsetY,
				EnemyOffsetX + temp.Data.xSize,
				EnemyOffsetY + temp.Data.ySize);
			use_offset = 1;
			EnemyOffsetX = -1;
			EnemyOffsetY = -1;
		} else {
			SetRect(&rect,
				EnemySurfaceX,EnemySurfaceY,
				EnemySurfaceX + temp.Data.xSize,
				EnemySurfaceY + temp.Data.ySize);
		}

		//---�p�^�[�����P���̊G�Ƃ��ăT�[�t�F�C�X�ɃZ�b�g
		temp.SetSurface(&rect,3);
		size = temp.Data.xSize / 4;

		if(EnemySurfaceX + temp.Data.xSize < 320 && !use_offset){
			//---�܂��g����I
			EnemyOffsetX = EnemySurfaceX + temp.Data.xSize;
			EnemyOffsetY = EnemySurfaceY;
			EnemyOffsetSizeY = temp.Data.ySize;
		}
	
		if(type == DRAWTYPE_4_ANIME){
			size = BATTLE_ENEMYPATTERNSIZE;
			for(a = 0,y = 0;a < 32;a ++){
				if(a == 16)
					y += 32;
				BattleEnemyCell[EnemyPatternNumber * ptn_size + a].Data.SurfaceFlag = 1;
				BattleEnemyCell[EnemyPatternNumber * ptn_size + a].Data.SurfaceNumber = 3;
				BattleEnemyCell[EnemyPatternNumber * ptn_size + a].pDDSurface = temp.pDDSurface;

				BattleEnemyCell[EnemyPatternNumber * ptn_size + a].Data.rectSurface.left   = rect.left   + (size * (a - (y ? 16 : 0)));
				BattleEnemyCell[EnemyPatternNumber * ptn_size + a].Data.rectSurface.right  = rect.left/*rect.right*/  + (size * (a  - (y ? 16 : 0)) + 1);
				BattleEnemyCell[EnemyPatternNumber * ptn_size + a].Data.rectSurface.top    = rect.top + y;
				BattleEnemyCell[EnemyPatternNumber * ptn_size + a].Data.rectSurface.bottom = rect.top + y + 32;//rect.bottom + y;
			}
		} else {
			for(a = 0;a < 4;a ++){
				BattleEnemyCell[EnemyPatternNumber * ptn_size + a].Data.SurfaceFlag = 1;
				BattleEnemyCell[EnemyPatternNumber * ptn_size + a].Data.SurfaceNumber = 3;
				BattleEnemyCell[EnemyPatternNumber * ptn_size + a].pDDSurface = temp.pDDSurface;

				BattleEnemyCell[EnemyPatternNumber * ptn_size + a].Data.rectSurface.left   = rect.left   + (size * a);
				BattleEnemyCell[EnemyPatternNumber * ptn_size + a].Data.rectSurface.right  = rect.right  + (size * (a + 1));
				BattleEnemyCell[EnemyPatternNumber * ptn_size + a].Data.rectSurface.top    = rect.top;
				BattleEnemyCell[EnemyPatternNumber * ptn_size + a].Data.rectSurface.bottom = rect.bottom;
			}
		}

		//---�T�[�t�F�C�X���W�𑫂�
		if(!use_offset){
			EnemySurfaceY += temp.Data.ySize;
		}
		EnemyPatternNumber ++;

		temp.Release();
	} else {
		EnemyPatternNumber ++;
	}

	return (EnemyPatternNumber - 1);
}

//---�G�̃f�[�^��ǂݍ���
CRBATINIT_API int crbatReadEnemy(CR_BATTLEINFO *pInfo,CR_BATENEMYINFO *pEnemyInfo,int retry)
{
	int a,b,number = CHARA_ENEMY,enemy = 1,enemy_count,keep_count;
	int testenemy[] = {11,1,1,-1,1,-1};
	int ReadBitmap[32],ReadNumber[32],count;
	CR_BATENEMYINFO *pEnemy = pEnemyInfo;

	EnemyOffsetX = -1;
	EnemyOffsetY = -1;
	for(a = 0;a < 32;a ++){
		ReadBitmap[a] = -1;
	}
	memset(&ReadNumber[0],0,sizeof(ReadNumber));

	//---�f�[�^�R�s�[
	for(a = CHARA_ENEMY;a < CHARA_ENEMY + BATTLE_ENEMYMAX;a ++){
		memset(&pBtChara[a].CharaInfo,0,sizeof(pBtChara[a].CharaInfo));
		memset(&pBtChara[a].BattleInfo,0,sizeof(pBtChara[a].BattleInfo));
		memset(&pBtChara[a].OnlyInfo,0,sizeof(pBtChara[a].OnlyInfo));
		pBtChara[a].BattleInfo.Existence = 0;
		pBtChara[a].BattleInfo.FriendOrEnemy = 0;
	}

	int start = 0,end = 0;
	if(pInfo->LoadKeepEnemy){
		start = pInfo->LoadKeepEnemy - 1;
		end = start + pInfo->LoadKeepEnemyCount;
	}

	for(count = 0,enemy_count = 0,keep_count = 0;
		pEnemy->Enemy != -1;pEnemy ++,number ++,enemy_count ++){
		if(pInfo->LoadKeepEnemy == 0){
			enemy = pEnemy->Enemy;

			memcpy(&pBtChara[number].CharaInfo,&pEnemyCharaInfo[enemy],sizeof(pBtChara[number].CharaInfo));
			memcpy(&pBtChara[number].BattleInfo,&pEnemyBatInfo[enemy],sizeof(pBtChara[number].BattleInfo));

			if(207 <= enemy && enemy <= 210){
				//---���i��
				int src = enemy - 207;
				memcpy(&pBtChara[number].CharaInfo,&pBtChara[src].CharaInfo,sizeof(pBtChara[number].CharaInfo));
//				memcpy(&pBtChara[number].BattleInfo,&pBtChara[src].BattleInfo,sizeof(pBtChara[number].BattleInfo));
				memcpy(pBtChara[number].BattleInfo.Ability,pBtChara[src].BattleInfo.Ability,sizeof(pBtChara[number].BattleInfo.Ability));
				memcpy(pBtChara[number].BattleInfo.Element,pBtChara[src].BattleInfo.Element,sizeof(pBtChara[number].BattleInfo.Element));
				memcpy(&pBtChara[number].BattleInfo.Status,&pBtChara[src].BattleInfo.Status,sizeof(pBtChara[number].BattleInfo.Status));
				memcpy(pBtChara[number].BattleInfo.StatusContinue,pBtChara[src].BattleInfo.StatusContinue,sizeof(pBtChara[number].BattleInfo.StatusContinue));
				memcpy(pBtChara[number].BattleInfo.StatusContinueMax,pBtChara[src].BattleInfo.StatusContinueMax,sizeof(pBtChara[number].BattleInfo.StatusContinueMax));
				pBtChara[number].CharaInfo.force_AvoidProb = pBtChara[src].GetEqAvoidProb();
				pBtChara[number].CharaInfo.force_MagicAvoidProb = pBtChara[src].GetEqMagicDefense();
				pBtChara[number].CharaInfo.magic_defense = pBtChara[src].GetEqMagicDefense();

				pBtChara[number].SetLP(pBtChara[number].GetMaxLP());
				pBtChara[number].SetMC(pBtChara[number].GetMaxMC());

				if(pGameInfo->Event[201]){
					//---��񏟂��Ă���A�A�C�e������
					pBtChara[number].BattleInfo.Enemy.Item = 0;
					pBtChara[number].BattleInfo.Enemy.ItemProbability = 0;
				}

				switch(enemy){
				case 207:
					sprintf(pBtChara[number].CharaInfo.Name,"���i���E�V���h�E");
					break;
				case 208:
					sprintf(pBtChara[number].CharaInfo.Name,"�f�B�U�E�V���h�E");
					break;
				case 209:
					sprintf(pBtChara[number].CharaInfo.Name,"�i�b�N�E�V���h�E");
					break;
				case 210:
					sprintf(pBtChara[number].CharaInfo.Name,"�T���B�A�[�E�V���h�E");
					break;
				}
			}
		} else {
			//---�ǂݍ��ݏI��
			if(keep_count >= end)
				break;
			if(pKeepChara[start + keep_count].GetLP() <= 0){
				pEnemy --;
				number --;
				enemy_count --;
				keep_count ++;
				continue;
			}
			memcpy(&pBtChara[number].CharaInfo,
				&pKeepChara[start + keep_count].CharaInfo,
				sizeof(pBtChara[number].CharaInfo));

			memcpy(&pBtChara[number].BattleInfo,
				&pKeepChara[start + keep_count].BattleInfo,
				sizeof(pBtChara[number].BattleInfo));

//			eiDebugWriteFile("load:");
//			eiDebugWriteFile(pKeepChara[start + keep_count].GetName());
//			eiDebugWriteFile("\n");
			keep_count ++;
		}

		//---�푰�ɉ����Ĕ\�͒ǉ�
		if(pBtChara[number].Ability(BTAB_M_BOSS)){
			//---�{�X����
			pBtChara[number].SetAbility(BTAB_P_HENKA_12,1);
			pBtChara[number].SetAbility(BTAB_P_SOKUSHI,1);
		} else if(pBtChara[number].GetType() == CHARATYPE_DOBUTSU
			|| pBtChara[number].GetType() == CHARATYPE_SHOKUBUTSU){
			//---�{�X�����łȂ��������A��
			pBtChara[number].SetAbility(BTAB_M_HENKA,1);
		}

		if(pBtChara[number].GetType() == CHARATYPE_SEISHINTAI){
			pBtChara[number].SetAbility(BTAB_P_SOKUSHI,1);
			pBtChara[number].SetAbility(BTAB_P_DOKU,1);
			pBtChara[number].SetAbility(BTAB_P_NEMURI,1);
			pBtChara[number].SetAbility(BTAB_P_MAHI,1);
		}
		if(pBtChara[number].GetType() == CHARATYPE_JUNSEISHINTAI){
//			pBtChara[number].SetAbility(BTAB_P_KURAYAMI,1);
			pBtChara[number].SetAbility(BTAB_P_DOKU,1);
			pBtChara[number].SetAbility(BTAB_P_KONRAN,1);
			pBtChara[number].SetAbility(BTAB_P_NEMURI,1);
			pBtChara[number].SetAbility(BTAB_P_SOKUSHI,1);
			pBtChara[number].SetAbility(BTAB_P_MAHI,1);

			pBtChara[number].SetAbility(BTAB_P_HENKA,1);
		}
		//---����
		if(pBtChara[number].GetType() == CHARATYPE_BUSSHITSU){
			pBtChara[number].SetAbility(BTAB_P_DOKU,1);
			pBtChara[number].SetAbility(BTAB_P_NEMURI,1);
			pBtChara[number].SetAbility(BTAB_P_SOKUSHI,1);
//			pBtChara[number].SetAbility(BTAB_P_MAHI,1);
		}

		//---����I
		pBtChara[number].BattleInfo.Existence = 1;
		//---�g������
		if(pBtChara[number].BattleInfo.Enemy.ExistenceExtend){
			pBtChara[number].BattleInfo.ExistenceExtend = 1;
			pBtChara[number].BattleInfo.Existence = 0;
		}
		pBtChara[number].SetDrawType(pBtChara[number].BattleInfo.Enemy.GraphicType);

		//---�y�I�t�Z�b�g
		pBtChara[number].SetZOffset((float)(pBtChara[number].BattleInfo.Enemy.ZOffset) / 100.0f);

		for(a = 0;a < 32;a ++){
			if(ReadBitmap[a] == pBtChara[number].BattleInfo.Enemy.Graphic){
				//---���łɂ��̃O���t�B�b�N��ǂݍ���ł����
				break;
			}
		}

/*		if(207 <= pBtChara[number].BattleInfo.Enemy.Graphic
			&& pBtChara[number].BattleInfo.Enemy.Graphic <= 210){
			//---�R�s�[
			pBtChara[number].SetCell(pBtChara[pBtChara[number].BattleInfo.Enemy.Graphic - 207].GetCell());
		} else */if(a == 32){
			//---�p�^�[����ǂݍ���ł�����N���X�ɓo�^
			ReadBitmap[count] = pBtChara[number].BattleInfo.Enemy.Graphic;

			b = crbatReadEnemyPattern(
				pBtChara[number].BattleInfo.Enemy.Graphic,
				pBtChara[number].BattleInfo.Enemy.GraphicType,
				retry);
			ReadNumber[count] = b;

			pBtChara[number].SetCell(&BattleEnemyCell[b * BATTLE_ENEMYPATTERNSIZE]);
			count ++;
		} else {
			pBtChara[number].SetCell(&BattleEnemyCell[ReadNumber[a] * BATTLE_ENEMYPATTERNSIZE]);
		}

	}
	for(a = 0;a < BATTLECHARA_PARTY_MAX;a ++){
		if(pBtChara[a].DoExist()){
			//---�o������G�̐�
			pBtChara[a].HistoryAddEnemyCount(enemy_count);
		}
	}

	return 1;
}

//---���W��������
CRBATINIT_API int crbatSetStartPos(CR_BATTLEINFO *pInfo)
{
/*	pBtChara[0].SetFieldPos(6,4,0);
	pBtChara[1].SetFieldPos(4,3,0);
	pBtChara[2].SetFieldPos(8,1,0);

	pBtChara[5].SetFieldPos(8,9,0);
	pBtChara[6].SetFieldPos(7,6,0);
	pBtChara[7].SetFieldPos(3,8,0);
	pBtChara[8].SetFieldPos(10,4,0);
	pBtChara[9].SetFieldPos(6,0,0);
*/
	int a;

	for(a = 0;a < BATTLECHARA_PARTY_MAX;a ++){
		if(pBtChara[a].DoExist()){
			if(pInfo->OffsetBattle == BATSTART_BACKATACK){
				//---�o�b�N�A�^�b�N
				pBtChara[a].SetFieldPos(
					pBtChara[a].GetBattleFieldStartX(),
					(5 - (pBtChara[a].GetBattleFieldStartY())),
					0);
			} else if(pInfo->OffsetBattle == BATSTART_HASAMIUCHI){
				//---���݌���
				pBtChara[a].SetFieldPos(
					pBtChara[a].GetBattleFieldStartX(),
					pBtChara[a].GetBattleFieldStartY() + 3,
					0);
			} else {
				pBtChara[a].SetFieldPos(
					pBtChara[a].GetBattleFieldStartX(),
					pBtChara[a].GetBattleFieldStartY(),
					0);
			}
		}
	}
	for(a = BATTLECHARA_STARTENEMY;a < BATTLECHARA_PARTY_MAX + BATTLE_ENEMYMAX;a ++){
		if(pBtChara[a].DoExist()){
			//---�G�̃|�W�V�����ݒ�
			pBtChara[a].SetFieldPos(
				pInfo->Enemy[a - BATTLECHARA_STARTENEMY].x,
				pInfo->Enemy[a - BATTLECHARA_STARTENEMY].y,
				0);
		}
	}

	if(pInfo->EnableFriendPos){
		//---�݂����ʒu����\
		for(a = 0;a < MEMBER_MAX;a ++){
			if(pBtChara[a].DoExist()){
				pBtChara[a].SetFieldPos(pInfo->Friend[a].x,pInfo->Friend[a].y);
			}
		}
	}

	crbatSetCharaAngleToRandomAll();
	return 1;
}

//---�t�B�[���h���_��������
CRBATINIT_API int crbatInitFieldVertex(void)
{
	int a,x,y;

	D3DVECTOR vNormal( D3DVAL(0.0f), D3DVAL(1.0f), D3DVAL(0.0f) );
	D3DVECTOR vNormal2( D3DVAL(0.0f), D3DVAL(-1.0f), D3DVAL(0.0f) );
	D3DVECTOR p1(D3DVAL(-0.5f) , D3DVAL(0.0f) , D3DVAL(-0.5f));
	D3DVECTOR p2( D3DVAL(0.5f) , D3DVAL(0.0f) , D3DVAL(-0.5f));
	D3DVECTOR p3(D3DVAL(-0.5f) , D3DVAL(0.0f) , D3DVAL( 0.5f));
	D3DVECTOR p4( D3DVAL(0.5f) , D3DVAL(0.0f) , D3DVAL( 0.5f));
/*
	D3DVECTOR vNormal( D3DVAL(0.0f), D3DVAL(1.0f), D3DVAL(0.0f) );
	D3DVECTOR vNormal2( D3DVAL(0.0f), D3DVAL(-1.0f), D3DVAL(0.0f) );
	D3DVECTOR p1(D3DVAL(-0.5f) , D3DVAL(-0.5f) , D3DVAL(0.0f));
	D3DVECTOR p2( D3DVAL(0.5f) , D3DVAL(-0.5f) , D3DVAL(0.0f));
	D3DVECTOR p3(D3DVAL(-0.5f) , D3DVAL(0.5f) , D3DVAL( 0.0f));
	D3DVECTOR p4( D3DVAL(0.5f) , D3DVAL(0.5f) , D3DVAL( 0.0f));
*/
	for(y = 0;y < BATTLEFIELD_VERTEXCOUNT_Y;y ++){
		for(x = 0;x < BATTLEFIELD_VERTEXCOUNT_X;x ++){
			BattleField[x][y].Vertex[0] = D3DVERTEX( p1, vNormal,D3DVAL(0.0f),D3DVAL(0.0f));
			BattleField[x][y].Vertex[1] = D3DVERTEX( p2, vNormal,D3DVAL(1.0f),D3DVAL(0.0f));
			BattleField[x][y].Vertex[2] = D3DVERTEX( p3, vNormal,D3DVAL(0.0f),D3DVAL(1.0f));
			BattleField[x][y].Vertex[3] = D3DVERTEX( p4, vNormal,D3DVAL(1.0f),D3DVAL(1.0f));

			for(a = 0;a < 4;a ++){
				BattleField[x][y].Vertex[a].x += (float)((float)x * 1.0f);
				BattleField[x][y].Vertex[a].z += (float)((float)y * 1.0f);
			}

//			BattleField[x][y].TextureNumber = eiRnd(2);
		}
	}

	return 1;
}

//---�o�g����������
CRBATINIT_API int crbatInitBattle(CR_BATTLEINFO *pInfo,int retry)
{
	int a,b;
	int check = 1;
	int OffsetX = 32,OffsetY = 16,Width = 640 - 64,Height = 256;

	char s[80];
	eiTime let;

	//---���y�ۑ�
	if(!retry){
		KeepMusic = pGameInfo->MusicNumber;
	}

	let.Reset();

	//---�r������ݒ�
	eiWaitCriticalSection(1000);
	eiDebugWriteFile("(crbatInitBattle) eiWaitCriticalSection\n");
	//---�R�[�h�ݒ�
	crsysSetCodeMode(CODE_BATTLE);

	sprintf(s,"\t0,time:%d\n",let.Get());
	eiDebugWriteFile(s);
	//---���y
	if(pInfo->Music == -1){
		pInfo->Music = CRMUSIC_BATTLE;
	}
	if(pInfo->Music != 0){
		if(crdataGetIniFile()->OffsetPlay)
			crmusicSetStream(1);
		eiDebugWriteFile("(crbatInitBattle) crmusicSetStream\n");
		crmusicPlay(pInfo->Music,1,CRMUSIC_LOADFORCE);
		eiDebugWriteFile("(crbatInitBattle) crmusicPlay\n");
	} else if(retry){
		crmusicPlay(KeepMusic,1,CRMUSIC_LOADFORCE);
	}

	if(!retry){
		//---���g���C�Z�[�u
//		crfileSaveData(MEMORYSAVEFILE_NUMBER,SAVE_FILE_ID1,SAVE_FILE_ID2,1);
		memcpy(BtKeepItem,pGameInfo->Item,sizeof(BtKeepItem));
		memcpy(BtKeepItemCount,pGameInfo->ItemCount,sizeof(BtKeepItemCount));
	}

	//---�ϐ�������
	if(!retry){
		memset(&BattleField[0][0],0,sizeof(BattleField));
	}
	{
		//---�G�p�^�[���z�u���W
		::EnemySurfaceX = 0;
		::EnemySurfaceY = 272;
		::EnemyPatternNumber = 0;

		::BattleExperience = 0;
		::BattleMoney = 0;
		::BattleItem = 0;
		::BattleItemProb = 0;

		::PreviousAnimeNumber = -1;//---�O��̃A�j���[�V����
	}
	eiDebugWriteFile("(crbatInitBattle) �ϐ�������\n");

	//---�r���[�|�[�g�͈͏�����

	//---�t���X�N���[���r���[
	{
		BattleViewRect[BATTLE_VIEWMODE_FULLSCREEN][0].left = OffsetX;
		BattleViewRect[BATTLE_VIEWMODE_FULLSCREEN][0].top = OffsetY;
		BattleViewRect[BATTLE_VIEWMODE_FULLSCREEN][0].right = Width;
		BattleViewRect[BATTLE_VIEWMODE_FULLSCREEN][0].bottom = 480 - 64;
	}

	//---�V���O���r���[
	{
		BattleViewRect[BATTLE_VIEWMODE_SINGLE][0].left = OffsetX;
		BattleViewRect[BATTLE_VIEWMODE_SINGLE][0].top = OffsetY;
		BattleViewRect[BATTLE_VIEWMODE_SINGLE][0].right = Width;
		BattleViewRect[BATTLE_VIEWMODE_SINGLE][0].bottom = Height;
	}

	{
		//---�_�u���r���[
		BattleViewRect[BATTLE_VIEWMODE_DOUBLE][0].left = OffsetX;
		BattleViewRect[BATTLE_VIEWMODE_DOUBLE][0].top = OffsetY;
		BattleViewRect[BATTLE_VIEWMODE_DOUBLE][0].right = 320 - (32 + 8);
		BattleViewRect[BATTLE_VIEWMODE_DOUBLE][0].bottom = Height;

		BattleViewRect[BATTLE_VIEWMODE_DOUBLE][1].left = 320 + 8;
		BattleViewRect[BATTLE_VIEWMODE_DOUBLE][1].top = OffsetY;
		BattleViewRect[BATTLE_VIEWMODE_DOUBLE][1].right = 320 - (32 + 8);
		BattleViewRect[BATTLE_VIEWMODE_DOUBLE][1].bottom = Height;
	}
	//---�n�[�t�r���[
	{
		BattleViewRect[BATTLE_VIEWMODE_HALF][0].left = 32 + (16 * 12) + 32;//OffsetX;
		BattleViewRect[BATTLE_VIEWMODE_HALF][0].top = OffsetY;
		BattleViewRect[BATTLE_VIEWMODE_HALF][0].right = 352;//320 - (32 + 8);
		BattleViewRect[BATTLE_VIEWMODE_HALF][0].bottom = Height;
	}

	sprintf(s,"\t1,time:%d\n",let.Get());
	eiDebugWriteFile(s);

	//---���_������
	if(!retry){
		check &= crbatInitFieldVertex();
		eiDebugWriteFile("(crbatInitBattle) crbatInitFieldVertex\n");
	}

	sprintf(s,"\t2,time:%d\n",let.Get());
	eiDebugWriteFile(s);

	if(!retry){
		//---�R�c�I�u�W�F�N�g������
		check &= crbatCreate3DObject(pInfo,retry);
		eiDebugWriteFile("(crbatInitBattle) crbatCreate3DObject\n");

		sprintf(s,"\t3,time:%d\n",let.Get());
		eiDebugWriteFile(s);
	}

	//---�f�[�^�R�s�[
	check &= crbatCopyData();
	eiDebugWriteFile("(crbatInitBattle) crbatCopyData\n");

	//---�G�L�����N�^�[�ǂݍ���
	check &= crbatReadEnemy(pInfo,&pInfo->Enemy[0],retry);
	eiDebugWriteFile("(crbatInitBattle) crbatReadEnemy\n");

	sprintf(s,"\t4,time:%d\n",let.Get());
	eiDebugWriteFile(s);

	//---�����L�����N�^�[�ǂݍ���
	check &= crbatReadCharaPattern();
	eiDebugWriteFile("(crbatInitBattle) crbatReadCharaPattern\n");

	eiCellSetSurface(pBattleFontCell,
		CR_PTNSURFACE_BATTLEFONT_X,CR_PTNSURFACE_BATTLEFONT_Y,16,16,16);
	eiDebugWriteFile("(crbatInitBattle) pBattleFontCell\n");
	eiCellSetSurface(&pBattleFontCell[16],
		CR_PTNSURFACE_BATTLEFONT_X,CR_PTNSURFACE_BATTLEFONT_Y + 16,16,16,16);
	eiDebugWriteFile("(crbatInitBattle) pBattleFontCell[16]\n");

	sprintf(s,"\t5,time:%d\n",let.Get());
	eiDebugWriteFile(s);

	//---�X�e�[�^�X�A�C�R���p�̃Z�����Z�b�g
	for(a = 0;a < BATTLECHARA_MAX;a ++){
		for(b = 0;b < BATTLE_STATUSICONMAX;b ++){
			pBtChara[a].StatusObject[b].SetAnime(0);
			pBtChara[a].StatusObject[b].SetCell(&BattleStatusCell[b]);
			pBtChara[a].StatusObject[b].SetPattern(0);
		}
	}
/*	sprintf(s,"aa:%x,%x\n",pBtChara[0].StatusObject[1].GetCell(),&BattleStatusCell[1]);
	eiDebugWriteFile(s);
	sprintf(s,"aa:%x,%x\n",pBtChara[5].StatusObject[0].GetCell(),&BattleStatusCell[0]);
	eiDebugWriteFile(s);
	sprintf(s,"aa:%x,%x\n",pBtChara[5].StatusObject[1].GetCell(),&BattleStatusCell[1]);
	eiDebugWriteFile(s);
*/
	//---�I�t�Z�b�g�o�g������
	if(!retry){
		int taka = 0;
		CrCharacter *pChara;

		for(a = 0;a < MEMBER_MAX;a ++){
			pChara = crcharaGetPartyMember(a);
			if(pChara != NULL){
				if(pChara->GetAccessory(0) == 275
					|| pChara->GetAccessory(1) == 275){
					//---�C�[�O���X�J�[�t
					taka = 1;
				}
			}
		}

		pInfo->OffsetBattle = BATSTART_NORMAL;
		if(pInfo->EnableOffsetBattle == OFFSETBAT_ENABLEALL){
			//---�I�t�Z�b�g�o�g���ݒ�
			int rnd = eiRnd(1000);

			if(rnd < 50){
				//---�搧�U��
				pInfo->OffsetBattle = BATSTART_SENSEI;
			} else if(rnd < 100){
				rnd = eiRnd(taka == 0 ? 1000 : 3000);
				if(rnd < 700){
					pInfo->OffsetBattle = BATSTART_FUIUCHI;
				} else if(rnd < 1000){
					pInfo->OffsetBattle = BATSTART_BACKATACK;
				}
			}
		}
	}

	//---���W�z�u
	check &= crbatSetStartPos(pInfo);
	eiDebugWriteFile("(crbatInitBattle) crbatSetStartPos\n");

	//---�Z�b�g�J����
	crbatSetCamera(0,64.0f,64.0f,32.0f,200.0f,200.0f,0.0f);
	eiDebugWriteFile("(crbatInitBattle) crbatSetCamera\n");

	//---�r���������
	eiReleaseCriticalSection();
	eiDebugWriteFile("(crbatInitBattle) eiReleaseCriticalSection\n");

	sprintf(s,"\t6,time:%d\n",let.Get());
	eiDebugWriteFile(s);

	return check;
}
