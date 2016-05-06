/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBattle_EnemyAbility.cpp ...Battle Enemy functions

-----------------------------------------------------------*/

#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBATTLE_ENEMYABILITY

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#define EXTERN_CRBATTLE
#include "..\CrBase.h"
#include "..\CrBattle.h"

#define CR_GAMEINFO_EXTERNPOINTER
#include "..\CrGameInfo.h"

#include "CrBattle_EnemyAbility_Sub1.cpp"

CRBATANIME_API void crbatDoAnime_MagicWind(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,
										   int red,int green,int blue,int mode,int ambient);
CRBATANIME_API void crbatDoAnime_MagicHojo(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,
										   int cr,int cg,int cb);
CRBATANIME_API void crbatDoAnime_MagicFire4(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,int mode,int ambient);
CRBATANIME_API void crbatDoAnime_MagicRay(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,
										  int red,int green,int blue,float range,int mode);
CRBATANIME_API void crbatDoAnime_MagicThunder(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,int mode);
CRBATANIME_API void crbatDoAnime_MagiDarudaru(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,float move_speed,int r_time);
CRBATANIME_API void crbatDoAnime_MagicDiffusion3(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo);
CRBATANIME_API void crbatDoAnime_MagicSoul(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo);


//---����n
CRBATENEMYABILITY_API int crbatEnemy_Bunretu(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int ability)
{
	int rate = 1250;
	//---InfoWindow�����
	pWin->SetType(CRWIN_TYPE_NORMAL);

	switch(ability){
	case BAT_ECOM_BUNRETU:
		rate = 1000;
		crbatBWCreate(pWin,
			"����",BW_TOP | BW_CENTER);
		break;
	}

	//---�Փ˕␳
	crbatGetTargetChara(pChara,pChara->GetTarget(),
		pChara->Command.Range,&pDamageInfo->pList[0],1);

	if(pDamageInfo->pList[0] != NULL){
		//---�Փ˕␳�Ń^�[�Q�b�g���ς�����Ƃ��̂��߂�
		//---�L�����N�^�[�A���O���Đݒ�
		pDamageInfo->pList[0]->SetAngle(
			ANGLE(180) + pChara->GetCharaAngle(pDamageInfo->pList[0])
			);
	}

	crbatSetDamageMode(pDamageInfo,DAMAGEMODE_SUB);

	int a,x,y;
	for(a = BATTLECHARA_STARTENEMY;a < BATTLECHARA_STARTENEMY + BATTLE_ENEMYMAX;a ++){
		if(pBtChara[a].DoExist() == 0)
			break;
	}
	x = pChara->GetFieldX();
	y = pChara->GetFieldY() - 1;
	if(crbatIsThere(x,y)){
		y ++;
		x ++;
		if(crbatIsThere(x,y)){
			y ++;
			x --;
			if(crbatIsThere(x,y)){
				x --;
				y --;
			}
		}
	}
	if(a != BATTLECHARA_STARTENEMY + BATTLE_ENEMYMAX
		&& !crbatIsThere(x,y) && !pChara->GetBattleFlag(0)){
		//---�������􂵂Ȃ��悤��
		pChara->SetBattleFlag(0,1);
		//---�R�s�[
		memcpy(&pBtChara[a].CharaInfo,&pChara->CharaInfo,sizeof(pChara->CharaInfo));
		memcpy(&pBtChara[a].BattleInfo,&pChara->BattleInfo,sizeof(pChara->BattleInfo));
		memcpy(&pBtChara[a].OnlyInfo,&pChara->OnlyInfo,sizeof(pChara->OnlyInfo));

		pBtChara[a].BattleInfo.Existence = 1;
		pBtChara[a].BattleInfo.FriendOrEnemy = 0;
		pBtChara[a].SetFieldPos(x,y);

		for(a = 0;a < BATTLECHARA_PARTY_MAX;a ++){
			if(pBtChara[a].DoExist()){
				//---�o������G�̐�
				pBtChara[a].HistoryAddEnemyCount(1);
			}
		}
	}

	crbatDrawSceneWhile(500);
	crbatClearDrawingList();
	crbatAddDrawingListAll();
	crbatDrawSceneWhile(500);

	return 1;
}


//---�u���X�n
CRBATENEMYABILITY_API int crbatEnemy_Breath(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int ability)
{
	int damage = pChara->Command.Sub[3],element = 0;
	int red = 255,green = 255,blue = 255,mode = 0;
	//---InfoWindow�����
	pWin->SetType(CRWIN_TYPE_NORMAL);

	switch(ability){
	case BAT_ECOM_HONO2:
		mode = 1;
	case BAT_ECOM_HONO:
		crbatBWCreate(pWin,
			"��",BW_TOP | BW_CENTER);
		element = ELEMENT_FIRE;
		red = 255;
		green = 127;
		blue = 64;
		break;
	case BAT_ECOM_DAIKAEN:
		mode = 1;
		crbatBWCreate(pWin,
			"��Ή�",BW_TOP | BW_CENTER);
		element = ELEMENT_FIRE;
		red = 255;
		green = 127;
		blue = 64;
		pChara->SetBattleFlag(0,0);
		break;

	case BAT_ECOM_FUBUKI2:
		mode = 1;
	case BAT_ECOM_FUBUKI:
		crbatBWCreate(pWin,
			"����",BW_TOP | BW_CENTER);
		element = ELEMENT_AQUA;
		red = 128;
		green = 128;
		blue = 255;
		break;
	case BAT_ECOM_TOPPU2:
		mode = 1;
	case BAT_ECOM_TOPPU:
		crbatBWCreate(pWin,
			"�˕�",BW_TOP | BW_CENTER);
		element = ELEMENT_WIND;
		red = 32;
		green = 255;
		blue = 96;
		break;
	case BAT_ECOM_SUNAARASHI2:
		mode = 1;
	case BAT_ECOM_SUNAARASHI:
		crbatBWCreate(pWin,
			"����",BW_TOP | BW_CENTER);
		element = ELEMENT_EARTH;
		red = 255;
		green = 224;
		blue = 0;
		break;
	case BAT_ECOM_IKADUCHI2:
		mode = 1;
	case BAT_ECOM_IKADUCHI:
		crbatBWCreate(pWin,
			"�����Â�",BW_TOP | BW_CENTER);
		element = ELEMENT_THUNDER;
		red = 255;
		green = 255;
		blue = 0;
		break;

	case BAT_ECOM_CRFUBUKI:
		crbatBWCreate(pWin,
			"�łт̐���",BW_TOP | BW_CENTER);
		element = ELEMENT_AQUA;
		red = 128;
		green = 128;
		blue = 255;
		break;
	}

	crbatSetDamageMode(pDamageInfo,DAMAGEMODE_SUB);

	//---�U���l�A�h��l�A�v�Z���@�A����
	//---�_���[�W�v�Z
	crbatCalcDamage(
		pDamageInfo,pChara,
		SRC_DIRECT,pChara->Command.Sub[3],
		DST_NONE,1000,
		CALCMODE_ADD,1000,
		160,//---���U�i�P�^�P�O�O�O�P�ʁj
		element,
		PROBMODE_100,1000,//---���햽����𗦁A������
		DEFENSEMODE_REAL | DEFENSEMODE_BREATH
		);

	if(ability == BAT_ECOM_CRFUBUKI){
		int a;
		for(a = 0;pDamageInfo->pList[a] != NULL;a++){
			if(pDamageInfo->Damage[a] == 0){
				continue;
			}

			if(eiRnd(1000) < pDamageInfo->pList[a]->GetStatusChangeRate(250)){
				//---����
				pDamageInfo->pList[a]->AddBtStatus(BTST_NEMURI);
			}
			if(eiRnd(1000) < pDamageInfo->pList[a]->GetStatusChangeRate(300)){
				//---��
				pDamageInfo->pList[a]->AddBtStatus(BTST_DOKU);
			}
			if(eiRnd(1000) < pDamageInfo->pList[a]->GetStatusChangeRate(750)){
				//---�㉻
				pDamageInfo->pList[a]->AddBtStatus(BTST_JAKUKA);
			}
			if(eiRnd(1000) < pDamageInfo->pList[a]->GetStatusChangeRate(600)){
				//---�È�
				pDamageInfo->pList[a]->AddBtStatus(BTST_KURAYAMI);
			}
			if(eiRnd(1000) < pDamageInfo->pList[a]->GetStatusChangeRate(500)){
				//---�h��͒ቺ
				pDamageInfo->pList[a]->AddBtStatus(BTST_ZERO);
			}
		}
	}

//	//---�A�j���[�V����
//	crbatDoAnime_Weapon(pChara,pDamageInfo);

	switch(ability){
	case BAT_ECOM_IKADUCHI:
	case BAT_ECOM_IKADUCHI2:
		crbatDoAnime_MagicThunder(pChara,pDamageInfo,1);
		crbatDrawSceneWhile(100);
		break;
	default:
		crbatDoAnime_MagicWind(pChara,pDamageInfo,
			red,green,blue,0,1);
		crbatDrawSceneWhile(100);
		break;
	}

	//---�_���[�W�\��
	crbatShowDamage(pDamageInfo);
	//---�_���[�W���ʉ��Z
	crbatResultDamage(pDamageInfo);
	//---�_���[�W���ʕ\��
	crbatShowResult();

	return 1;
}


//---���ڃ_���[�W�n
CRBATENEMYABILITY_API int crbatEnemy_DirectAtack(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int ability)
{
	int damage = pChara->Command.Sub[3],element = 0;
	int red = 255,green = 255,blue = 255;
	//---InfoWindow�����
	pWin->SetType(CRWIN_TYPE_NORMAL);

	switch(ability){
	case BAT_ECOM_EYEBEAM:
		crbatBWCreate(pWin,
			"�A�C�r�[��",BW_TOP | BW_CENTER);
		element = ELEMENT_NOELEMENT;
		red = 255;
		green = 0;
		blue = 0;
		break;
	case BAT_ECOM_MISTYBEAM:
		crbatBWCreate(pWin,
			"�~�X�e�B�r�[��",BW_TOP | BW_CENTER);
		element = ELEMENT_NOELEMENT;
		red = 64;
		green = 192;
		blue = 64;
		break;
	case BAT_ECOM_LAYZERBEAM:
		crbatBWCreate(pWin,
			"���[�U�[����",BW_TOP | BW_CENTER);
		element = ELEMENT_NOELEMENT;
		red = 64;
		green = 192;
		blue = 64;
		break;
	case BAT_ECOM_POWERBOMB:
		crbatBWCreate(pWin,
			"�p���[�{��",BW_TOP | BW_CENTER);
		element = ELEMENT_FIRE;
		break;
	case BAT_ECOM_KASCADEBOMB:
		crbatBWCreate(pWin,
			"�J�X�P�[�h�{��",BW_TOP | BW_CENTER);
		element = ELEMENT_FIRE;
		break;
	case BAT_ECOM_MIZUDEPPOU:
		crbatBWCreate(pWin,
			"���S�C",BW_TOP | BW_CENTER);
		element = ELEMENT_AQUA;
		red = 0;
		green = 128;
		blue = 255;
		break;
	case BAT_ECOM_KAENHOUSHA:
		crbatBWCreate(pWin,
			"�Ή�����",BW_TOP | BW_CENTER);
		element = ELEMENT_FIRE;
		break;
	case BAT_ECOM_JIBAKU1:
	case BAT_ECOM_JIBAKU2:
	case BAT_ECOM_JIBAKU4:
		crbatBWCreate(pWin,
			"����",BW_TOP | BW_CENTER);
		element = ELEMENT_NOELEMENT;
		break;
	case BAT_ECOM_JIBAKU3:
		crbatBWCreate(pWin,
			"�唚��",BW_TOP | BW_CENTER);
		element = ELEMENT_NOELEMENT;
		break;
	case BAT_ECOM_TAKISIDOBEAM:
		crbatBWCreate(pWin,
			"�^�L�V�[�h�r�[��",BW_TOP | BW_CENTER);
		element = ELEMENT_NOELEMENT;
		break;
	case BAT_ECOM_DANDYSPARK:
		crbatBWCreate(pWin,
			"���b�h�X�p�[�N",BW_TOP | BW_CENTER);
		element = ELEMENT_THUNDER;
		break;
	case BAT_ECOM_RIBONTUISTA:
		crbatBWCreate(pWin,
			"���{���c�C�X�^�[",BW_TOP | BW_CENTER);
		element = ELEMENT_WIND;
		break;

	case BAT_ECOM_CRESTEAJU1:
	case BAT_ECOM_CRESTEAJU2:
		crbatBWCreate(pWin,
			"�C���C�U�[",BW_TOP | BW_CENTER);
		element = ELEMENT_NOELEMENT;
		break;
	case BAT_ECOM_SINRYAKUHEI:
		crbatBWCreate(pWin,
			"���q�e",BW_TOP | BW_CENTER);
		element = ELEMENT_NOELEMENT;
		break;
	case BAT_ECOM_SINRYAKUHEI_BOMB:
		crbatBWCreate(pWin,
			"���j",BW_TOP | BW_CENTER);
		element = ELEMENT_NOELEMENT;
		red = 0;
		green = 128;
		blue = 255;
		break;

	case BAT_ECOM_ITAMIWAKE_DAMAGE:
		crbatBWCreate(pWin,
			"���O",BW_TOP | BW_CENTER);
		element = ELEMENT_NOELEMENT;
		break;
	case BAT_ECOM_RESERVE:
		crbatBWCreate(pWin,
			"���U�[�u",BW_TOP | BW_CENTER);
		element = ELEMENT_NOELEMENT;
		break;
	}

	crbatSetDamageMode(pDamageInfo,DAMAGEMODE_SUB);

	//---�U���l�A�h��l�A�v�Z���@�A����
	//---�_���[�W�v�Z
	int dm = pChara->Command.Sub[3],diff = 150;
	if(ability == BAT_ECOM_JIBAKU1 || ability == BAT_ECOM_JIBAKU2
		|| ability == BAT_ECOM_JIBAKU3 || ability == BAT_ECOM_JIBAKU4){
		dm = pChara->GetLP();
		if(ability == BAT_ECOM_JIBAKU3)
			dm *= 2;
		if(ability == BAT_ECOM_JIBAKU4)
			dm = pChara->Command.Sub[3];
		diff = 0;
	}
	if(ability == CRSOUND_ITAMIWAKE){
		diff = 0;
	}
	if(ability == BAT_ECOM_RESERVE){
		diff = 0;
		dm = pChara->GetMaxLP() - pChara->GetLP();
	}

	crbatCalcDamage(
		pDamageInfo,pChara,
		SRC_DIRECT,dm,
		DST_NONE,1000,
		CALCMODE_ADD,1000,
		diff,//---���U�i�P�^�P�O�O�O�P�ʁj
		element,
		PROBMODE_100,1000,//---���햽����𗦁A������
		DEFENSEMODE_REAL | DEFENSEMODE_BREATH
		);

	if(ability == BAT_ECOM_EYEBEAM
		|| ability == BAT_ECOM_MISTYBEAM
		|| ability == BAT_ECOM_TAKISIDOBEAM
		|| ability == BAT_ECOM_SINRYAKUHEI){
		crbatDoAnime_MagicRay(pChara,pDamageInfo,255,255,64,0.2f,2);
	} else if(ability == BAT_ECOM_LAYZERBEAM){
		crbatDoAnime_MagicRay(pChara,pDamageInfo,0,0,255,0.2f,2);
	} else if(ability == BAT_ECOM_MIZUDEPPOU){
		crbatDoAnime_MagicRay(pChara,pDamageInfo,0,0,255,0.2f,2);
	} else if(ability == BAT_ECOM_KAENHOUSHA){
		crbatDoAnime_MagicRay(pChara,pDamageInfo,255,0,0,0.2f,0);
	} else if(ability == BAT_ECOM_POWERBOMB || ability == BAT_ECOM_SINRYAKUHEI_BOMB){
		crbatDoAnime_MagicFire4(pChara,pDamageInfo,1,1);
	} else if(ability == BAT_ECOM_KASCADEBOMB
		|| ability == BAT_ECOM_JIBAKU1 || ability == BAT_ECOM_JIBAKU2
		|| ability == BAT_ECOM_JIBAKU3 || ability == BAT_ECOM_JIBAKU4){
		crbatDoAnime_MagicFire4(pChara,pDamageInfo,0,1);
	} else if(ability == BAT_ECOM_DANDYSPARK){
		crbatDoAnime_MagicThunder(pChara,pDamageInfo,1);
	} else if(ability == BAT_ECOM_RIBONTUISTA){
		crbatDoAnime_MagicWind(pChara,pDamageInfo,
			255,32,160,0,1);
//------------------------------------------------------------
	} else if(ability == BAT_ECOM_CRESTEAJU1
		|| ability == BAT_ECOM_CRESTEAJU2){
		crbatDoAnime_MagicDiffusion3(pChara,pDamageInfo);
//------------------------------------------------------------

	} else if(ability == BAT_ECOM_RESERVE){
		crbatDoAnime_MagicSoul(pChara,pDamageInfo);
	} else if(ability == BAT_ECOM_ITAMIWAKE_DAMAGE){
		crsoundPlay(CRSOUND_ITAMIWAKE);
		crbatDoAnime_MagicSoul(pChara,pDamageInfo);
	}

	//---�_���[�W�\��
	crbatShowDamage(pDamageInfo);
	//---�_���[�W���ʉ��Z
	crbatResultDamage(pDamageInfo);
	//---�_���[�W���ʕ\��
	crbatShowResult();

	return 1;
}


//---�E�q�n
CRBATENEMYABILITY_API int crbatEnemy_Houshi(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int ability)
{
	int a,damage = pChara->Command.Sub[3],element = 0;
	//---InfoWindow�����
	pWin->SetType(CRWIN_TYPE_NORMAL);

	switch(ability){
	case BAT_ECOM_HOUSHI:
		crbatBWCreate(pWin,
			"�E�q",BW_TOP | BW_CENTER);
		element = ELEMENT_WIND;
		break;
	case BAT_ECOM_SILENTBREATH:
		crbatBWCreate(pWin,
			"�T�C�����g�u���X",BW_TOP | BW_CENTER);
		element = ELEMENT_PHYSICS;
		break;
	case BAT_ECOM_SLEEPBREATH:
		crbatBWCreate(pWin,
			"�X���[�v�u���X",BW_TOP | BW_CENTER);
		element = ELEMENT_PHYSICS;
		break;
	case BAT_ECOM_POISON:
		crbatBWCreate(pWin,
			"�|�C�Y���u���X",BW_TOP | BW_CENTER);
		element = ELEMENT_PHYSICS;
		break;
	case BAT_ECOM_NEMURINOKONA:
		crbatBWCreate(pWin,
			"����̕�",BW_TOP | BW_CENTER);
		element = ELEMENT_PHYSICS;
		break;
	case BAT_ECOM_AKUBI:
		crbatBWCreate(pWin,
			"������",BW_TOP | BW_CENTER);
		element = ELEMENT_PHYSICS;
		break;
	case BAT_ECOM_DARUDARUHA:
		crbatBWCreate(pWin,
			"���邾��g",BW_TOP | BW_CENTER);
		element = ELEMENT_PHYSICS;
		break;
	case BAT_ECOM_KAFUN:
		crbatBWCreate(pWin,
			"�ԕ�",BW_TOP | BW_CENTER);
		element = ELEMENT_PHYSICS;
		break;
	case BAT_ECOM_MODOKUNOIKI:
		crbatBWCreate(pWin,
			"�ғł̑�",BW_TOP | BW_CENTER);
		element = ELEMENT_WIND;
		break;
	case BAT_ECOM_SANSEIU:
		crbatBWCreate(pWin,
			"�_���J",BW_TOP | BW_CENTER);
		element = ELEMENT_AQUA;
		break;
	case BAT_ECOM_SABORU:
		crbatBWCreate(pWin,
			"���ڂ�",BW_TOP | BW_CENTER);
		element = ELEMENT_AQUA;
		break;
	case BAT_ECOM_PINKMIST:
		crbatBWCreate(pWin,
			"�s���N�~�X�g",BW_TOP | BW_CENTER);
		element = ELEMENT_PHYSICS;
		break;
	case BAT_ECOM_TOSO:
		crbatBWCreate(pWin,
			"�����I",BW_TOP | BW_CENTER);
		element = ELEMENT_AQUA;
		break;
	}

	crbatSetDamageMode(pDamageInfo,DAMAGEMODE_SUB);

	//---�U���l�A�h��l�A�v�Z���@�A����
	//---�_���[�W�v�Z
	crbatCalcDamage(
		pDamageInfo,pChara,
		SRC_DIRECT,pChara->Command.Sub[3],
		DST_NONE,1000,
		CALCMODE_ADD,1000,
		160,//---���U�i�P�^�P�O�O�O�P�ʁj
		element,
		PROBMODE_100,1000,//---���햽����𗦁A������
		DEFENSEMODE_REAL | DEFENSEMODE_BREATH
		);

//	//---�A�j���[�V����
	if(ability == BAT_ECOM_AKUBI){
		crsoundPlay(CRSOUND_AKUBI);
		crbatDrawSceneWhile(1000);
	} else if(ability == BAT_ECOM_DARUDARUHA){
		crbatDrawSceneWhile(500);
		crbatBWCreate(pWin,
			"���u���邢�Ȃ��v",BW_TOP | BW_CENTER);
		crbatDoAnime_MagiDarudaru(pChara,pDamageInfo,0.05f,2000);
//		crbatDrawSceneWhile(500);
	} else if(ability == BAT_ECOM_KAFUN){
		crbatDoAnime_MagicWind(pChara,pDamageInfo,
			255,192,0,0,1);
	} else if(ability == BAT_ECOM_SANSEIU){
		crbatDoAnime_Weapon(pChara,pDamageInfo,0);
	} else if(ability == BAT_ECOM_SABORU){
		crbatDrawSceneWhile(500);
		crbatBWCreate(pWin,
			"���u���[�A����Ȑ킢�A���ڂ낤���v",BW_TOP | BW_CENTER);
		crbatDrawSceneWhile(1000);
//		crbatDoAnime_MagiDarudaru(pChara,pDamageInfo,0.05f,2000);
	} else if(ability == BAT_ECOM_TOSO){
		crbatDrawSceneWhile(750);
	} else if(ability == BAT_ECOM_PINKMIST){
		if(crsysQuick())
			return 1;
		crbatDrawSceneWhile(100);
		RECT rect = BattleViewRect[BattleViewMode][0];

		rect.right += rect.left;
		rect.bottom += rect.top;
		crefectScreenEfect_FadeOut(&rect,800,RGB_MAKE(255,170,224));
		crbatDrawSceneWhile(100);
	} else {
		crbatDoAnime_MagicWind(pChara,pDamageInfo,
			0,255,0,0,1);
	}

	//---�_���[�W�\��
	if(ability != BAT_ECOM_AKUBI && ability != BAT_ECOM_DARUDARUHA
		 && ability != BAT_ECOM_SABORU && ability != BAT_ECOM_PINKMIST
		 && ability != BAT_ECOM_TOSO){
		crbatShowDamage(pDamageInfo);
		//---�_���[�W���ʉ��Z
		crbatResultDamage(pDamageInfo);
	}

	switch(ability){
	case BAT_ECOM_MODOKUNOIKI:
		for(a = 0;pDamageInfo->pList[a] != NULL;a++){
			pDamageInfo->pList[a]->AddBtStatus(BTST_DOKU);
		}
		break;
	case BAT_ECOM_HOUSHI:
		for(a = 0;pDamageInfo->pList[a] != NULL;a++){
			if(eiRnd(1000) < pDamageInfo->pList[a]->GetStatusChangeRate(500)){
				//---����
				pDamageInfo->pList[a]->AddBtStatus(BTST_NEMURI);
			}
			if(eiRnd(1000) < pDamageInfo->pList[a]->GetStatusChangeRate(500)){
				//---��
				pDamageInfo->pList[a]->AddBtStatus(BTST_DOKU);
			}
		}
		break;
	case BAT_ECOM_KAFUN:
		for(a = 0;pDamageInfo->pList[a] != NULL;a++){
			if(eiRnd(1000) < pDamageInfo->pList[a]->GetStatusChangeRate(400)){
				//---���
				pDamageInfo->pList[a]->AddBtStatus(BTST_MAHI);
			}
			if(eiRnd(1000) < pDamageInfo->pList[a]->GetStatusChangeRate(400)){
				//---��
				pDamageInfo->pList[a]->AddBtStatus(BTST_DOKU);
			}
			if(eiRnd(1000) < pDamageInfo->pList[a]->GetStatusChangeRate(400)){
				//---����
				pDamageInfo->pList[a]->AddBtStatus(BTST_KONRAN);
			}
		}
		break;
	case BAT_ECOM_SLEEPBREATH:
	case BAT_ECOM_NEMURINOKONA:
	case BAT_ECOM_AKUBI:
		for(a = 0;pDamageInfo->pList[a] != NULL;a++){
			if(eiRnd(1000) < pDamageInfo->pList[a]->GetStatusChangeRate(500)){
				//---����
				pDamageInfo->pList[a]->AddBtStatus(BTST_NEMURI);
			}
		}
		break;
	case BAT_ECOM_DARUDARUHA:
		for(a = 0;pDamageInfo->pList[a] != NULL;a++){
			if(eiRnd(1000) < pDamageInfo->pList[a]->GetStatusChangeRate(700)){
				//---�ҋ@
				pDamageInfo->pList[a]->Command.Main = BAT_COMMAND_SKIP;
			}
		}
		break;
	case BAT_ECOM_SILENTBREATH:
		for(a = 0;pDamageInfo->pList[a] != NULL;a++){
			if(eiRnd(1000) < pDamageInfo->pList[a]->GetStatusChangeRate(500)){
				//---����
				pDamageInfo->pList[a]->AddBtStatus(BTST_CHINMOKU);
			}
		}
		break;
	case BAT_ECOM_POISON:
		for(a = 0;pDamageInfo->pList[a] != NULL;a++){
			if(eiRnd(1000) < pDamageInfo->pList[a]->GetStatusChangeRate(500)){
				//---��
				pDamageInfo->pList[a]->AddBtStatus(BTST_DOKU);
			}
		}
		break;
	case BAT_ECOM_SANSEIU:
		for(a = 0;pDamageInfo->pList[a] != NULL;a++){
			if(eiRnd(1000) < pDamageInfo->pList[a]->GetStatusChangeRate(1000)){
				//---�[��
				pDamageInfo->pList[a]->AddBtStatus(BTST_ZERO);
			}
		}
		break;
	case BAT_ECOM_PINKMIST:
		for(a = 0;pDamageInfo->pList[a] != NULL;a++){
			if(eiRnd(1000) < pDamageInfo->pList[a]->GetStatusChangeRate(500)){
				//---����
				pDamageInfo->pList[a]->AddBtStatus(BTST_KONRAN);
			}
		}
		break;
	}

	//---�_���[�W���ʕ\��
	crbatShowResult();

	return 1;
}

//---���邮��ڋ�
CRBATENEMYABILITY_API int crbatEnemy_GuruGuruMedama(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int ability)
{
	int a,damage = pChara->Command.Sub[3],element;
	//---InfoWindow�����
	pWin->SetType(CRWIN_TYPE_NORMAL);

	switch(ability){
	case BAT_ECOM_GURUGURUMEDAMA:
		crbatBWCreate(pWin,
			"���邮��ڋ�",BW_TOP | BW_CENTER);
		element = ELEMENT_NOELEMENT;
		break;
	case BAT_ECOM_GURUGURUHYPER:
		crbatBWCreate(pWin,
			"���邮��ڋʃn�C�p�[",BW_TOP | BW_CENTER);
		element = ELEMENT_NOELEMENT;
		break;
	case BAT_ECOM_JENTLEFLASH:
		crbatBWCreate(pWin,
			"�W�F���g���t���b�V��",BW_TOP | BW_CENTER);
		element = ELEMENT_NOELEMENT;
		break;
	case BAT_ECOM_KONRANKOUSEN:
		crbatBWCreate(pWin,
			"��������",BW_TOP | BW_CENTER);
		element = ELEMENT_NOELEMENT;
		break;

	case BAT_ECOM_ITAMIWAKE:
	case BAT_ECOM_ITAMIWAKE_JIZOKU:
		crbatBWCreate(pWin,
			"�ɂݕ���",BW_TOP | BW_CENTER);
		element = ELEMENT_NOELEMENT;
		break;
	case BAT_ECOM_ITAMIWAKE_KAIJO:
		crbatBWCreate(pWin,
			"�ɂݕ����@����",BW_TOP | BW_CENTER);
		element = ELEMENT_NOELEMENT;
		break;

	case BAT_ECOM_MCBUNKAI:
		crbatBWCreate(pWin,
			"�l�b����",BW_TOP | BW_CENTER);
		element = ELEMENT_NOELEMENT;
		break;
	case BAT_ECOM_SOKUSHIKOUSEN:
		crbatBWCreate(pWin,
			"��������",BW_TOP | BW_CENTER);
		element = ELEMENT_NOELEMENT;
		break;
	case BAT_ECOM_JAKUKAKOSEN:
		crbatBWCreate(pWin,
			"�㉻����",BW_TOP | BW_CENTER);
		element = ELEMENT_NOELEMENT;
		break;
	case BAT_ECOM_DAIKONRAN:
		crbatBWCreate(pWin,
			"�卬���I�I",BW_TOP | BW_CENTER);
		element = ELEMENT_NOELEMENT;
		break;
	}

	crbatSetDamageMode(pDamageInfo,DAMAGEMODE_SUB);


	switch(ability){
	case BAT_ECOM_GURUGURUMEDAMA:
	case BAT_ECOM_GURUGURUHYPER:
		crsoundPlay(CRSOUND_GURUGURUMEDAMA);
		crbatDrawSceneWhile(1000);

		for(a = 0;pDamageInfo->pList[a] != NULL;a++){
			if(eiRnd(1000) < pDamageInfo->pList[a]->GetStatusChangeRate(1000)){
				//---����
				pDamageInfo->pList[a]->AddBtStatus(BTST_KONRAN);
			}
		}
		break;
	case BAT_ECOM_DAIKONRAN:
		crsoundPlay(CRSOUND_AKUBI);
		crbatDrawSceneWhile(1000);
		for(a = 0;pDamageInfo->pList[a] != NULL;a++){
			pDamageInfo->pList[a]->AddBtStatus(BTST_KONRAN);
		}
		pChara->AddBtStatus(BTST_KONRAN);
		break;

	case BAT_ECOM_JENTLEFLASH:
		crbatDrawSceneWhile(200);
		crbatAnime_Flash(pChara,pDamageInfo,500,255,255,255);
		crbatDrawSceneWhile(300);

		for(a = 0;pDamageInfo->pList[a] != NULL;a++){
			if(eiRnd(1000) < pDamageInfo->pList[a]->GetStatusChangeRate(250)){
				//---�È�
				pDamageInfo->pList[a]->AddBtStatus(BTST_KURAYAMI);
			}
		}
		break;

	case BAT_ECOM_KONRANKOUSEN:
		crbatDoAnime_MagicRay(pChara,pDamageInfo,128,255,64,0.2f,2);

		for(a = 0;pDamageInfo->pList[a] != NULL;a++){
			if(eiRnd(1000) < pDamageInfo->pList[a]->GetStatusChangeRate(500)){
				//---����
				pDamageInfo->pList[a]->AddBtStatus(BTST_KONRAN);
			}
		}
		break;

	case BAT_ECOM_ITAMIWAKE_JIZOKU:
		if(pBtChara[pChara->GetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE_TAISHO)].IsKizetu()){
			//---�Ώۂ��C�₵�Ă���Ȃɂ����Ȃ�
			return 1;
		}
	case BAT_ECOM_ITAMIWAKE:
		crsoundPlay(CRSOUND_ITAMIWAKE);
		crbatDoAnime_MagicHojo(pChara,pDamageInfo,192,0,0);

		for(a = 0;pDamageInfo->pList[a] != NULL;a++){
			if(!(pDamageInfo->pList[a]->GetBtStatus() & BTST_WORLD)){
				//---���[���h�ȊO��������
				pDamageInfo->pList[a]->AddBtStatus(BTST_ITAMIWAKE);
				//---�ɂݕ����Ώ�
				pDamageInfo->pList[a]->SetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE_YARARE,pChara->GetNumber());

				//---�����t���b�O
				pChara->SetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE,1);
				pChara->SetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE_TAISHO,pDamageInfo->pList[a]->GetNumber());
			}
		}
		break;
	case BAT_ECOM_ITAMIWAKE_KAIJO:
		//---�ɂݕ�������
		crbatDoAnime_MagicHojo(pChara,pDamageInfo,192,0,0);
		crbatDrawSceneWhile(500);

		pBtChara[pChara->GetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE_TAISHO)].ClearBtStatus(BTST_ITAMIWAKE);
		pBtChara[pChara->GetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE_TAISHO)].SetBattleFlag(
			BATLLECHARA_FLAG_ITAMIWAKE,0);

		pChara->SetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE,0);
		pChara->SetBattleFlag(BATLLECHARA_FLAG_ITAMIWAKE_TAISHO,0);

		break;

	case BAT_ECOM_MCBUNKAI:
		crbatDrawSceneWhile(500);
		crsoundPlay(CRSOUND_DOWN);
		for(a = 0;pDamageInfo->pList[a] != NULL;a++){
			if(!(pDamageInfo->pList[a]->GetBtStatus() & BTST_WORLD)){
				pDamageInfo->Damage[a] = eiRnd(20) + damage;
				pDamageInfo->DamageMode[a] = DAMAGEMODE_SUBMC;
			}
		}
		//---�_���[�W�\��
		crbatShowDamage(pDamageInfo);
		//---�_���[�W���ʉ��Z
		crbatResultDamage(pDamageInfo);
		break;

	case BAT_ECOM_SOKUSHIKOUSEN:
		crbatDoAnime_MagicRay(pChara,pDamageInfo,0,64,128,0.2f,2);
		crbatDrawSceneWhile(100);

		for(a = 0;pDamageInfo->pList[a] != NULL;a++){
			if(eiRnd(1000) < pDamageInfo->pList[a]->GetStatusChangeRate(500)
				&& !pDamageInfo->pList[a]->Ability(BTAB_P_SOKUSHI)){
				//---����
				pDamageInfo->pList[a]->Sokushi();
			}
		}
		break;
	case BAT_ECOM_JAKUKAKOSEN:
		crbatDoAnime_MagicRay(pChara,pDamageInfo,0,64,128,0.2f,2);
		crbatDrawSceneWhile(100);

		for(a = 0;pDamageInfo->pList[a] != NULL;a++){
			if(eiRnd(1000) < pDamageInfo->pList[a]->GetStatusChangeRate(900)){
				pDamageInfo->pList[a]->AddBtStatus(BTST_JAKUKA);
			}
		}
		break;
	}

	//---�_���[�W���ʕ\��
	crbatShowResult();

	return 1;
}


//---�񕜌n�E�h��n
CRBATENEMYABILITY_API int crbatEnemy_Kaifuku(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int ability)
{
	//---InfoWindow�����
	pWin->SetType(CRWIN_TYPE_NORMAL);
	switch(ability){
	case BAT_ECOM_KOUGOUSEI:
		crbatBWCreate(pWin,
			"������",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_SAISEI:
		crbatBWCreate(pWin,
			"�Đ�",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_LPCHANGE:
		crbatBWCreate(pWin,
			"�k�o�`�F���W",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_TAMERU:
		crbatBWCreate(pWin,
			"���߂�",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_KARA:
		crbatBWCreate(pWin,
			"�k",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_SHURI:
		if(((CrBattleCharacter *)pChara->Command.Target)->IsFriend())
			return 1;
		crbatBWCreate(pWin,
			"�C��",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_BARRIERTENKAI:
		crsoundPlay(CRSOUND_UP);
		crbatBWCreate(pWin,
			"��C���u�ɂ��o���A�[�W�J",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_KASCADE_JUNBI:
		crsoundPlay(CRSOUND_UP);
		crbatBWCreate(pWin,
			"�J�X�P�[�h�{�������J�n",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_KASCADE_KYOKA:
		crsoundPlay(CRSOUND_UP);
		crbatBWCreate(pWin,
			"�J�X�P�[�h�{�������J�n",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_HANBUSSITU_JUNBI:
		crsoundPlay(CRSOUND_UP);
		crbatBWCreate(pWin,
			"�������[�U",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_KASCADE_SAIDAI:
		crsoundPlay(CRSOUND_UP);
		crbatBWCreate(pWin,
			"�J�X�P�[�h�{���o�͍ő�ɐݒ�",BW_TOP | BW_CENTER);
		break;

	case BAT_ECOM_NERU:
		crbatBWCreate(pWin,
			"�Q��",BW_TOP | BW_CENTER);
		break;

	case BAT_ECOM_KIDOU:
		crsoundPlay(CRSOUND_UP);
		crbatBWCreate(pWin,
			"�N��",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_BOSOKAISHI:
		crsoundPlay(CRSOUND_UP);
		crbatBWCreate(pWin,
			"���߂Ȃ��E�E�E�\���J�n",BW_TOP | BW_CENTER);
		break;

	case BAT_ECOM_CR_RUINJUNBI:
		crbatBWCreate(pWin,
			"�Ñ㖂�@�@���[�C���A�r���J�n",BW_TOP | BW_CENTER);
		pChara->SetBattleFlag(3,2);
		pChara->ResetRuinDamage();
		break;

	case BAT_ECOM_IKIWOSUIKOMU:
		crbatBWCreate(pWin,
			"�傫�������z������",BW_TOP | BW_CENTER);
		pChara->SetBattleFlag(0,1);
		break;

	case BAT_ECOM_KIDOSASERU:
		crbatBWCreate(pWin,
			"�f�X�}�V�[���A�N������",BW_TOP | BW_CENTER);
		pChara->SetBattleFlag(0,1);
		break;

	}

	if(ability == BAT_ECOM_LPCHANGE){
		crbatCalcDamage(
			pDamageInfo,pChara,
			SRC_LEVEL,1000,
			DST_LEVEL,1000,
			CALCMODE_PROB,1,
			0,//---���U�i�P�^�P�O�O�O�P�ʁj
			BTST_JAKUKA,
			PROBMODE_MAGIC,500,//pChara->Command.Sub[3],//---���햽����𗦁A������
			DEFENSEMODE_MAGIC
		);
		if(pDamageInfo->Miss[0] == 0){
			//---�����I�I
			int temp = pChara->GetLP();
			pChara->SetLP(pDamageInfo->pList[0]->GetLP());
			pDamageInfo->pList[0]->SetLP(temp);
		}
		//---�A�j���[�V����
		crbatDoAnime_MagicHojo(pChara,pDamageInfo,192,0,0);

		//---�_���[�W�\��
		crbatShowDamage(pDamageInfo);
		//---�_���[�W���ʕ\��
		crbatShowResult();
	} else if(ability == BAT_ECOM_KOUGOUSEI || ability == BAT_ECOM_SAISEI
		|| ability == BAT_ECOM_SHURI){
		crbatSetDamageMode(pDamageInfo,DAMAGEMODE_ADD);
		//---�U���l�A�h��l�A�v�Z���@�A����
		//---�_���[�W�v�Z
		int lp = pChara->GetMaxLP();

		if(ability == BAT_ECOM_SHURI){
			lp = 200;
		}
		crbatCalcDamage(
			pDamageInfo,pChara,
				SRC_DIRECT,lp,
			DST_NONE,1000,
			CALCMODE_ADD,1000,
			0,//---���U�i�P�^�P�O�O�O�P�ʁj
			ELEMENT_PHYSICS,//---���푮��
			PROBMODE_100,1000,
			0
			);

		//---�_���[�W�\��
		crbatShowDamage(pDamageInfo);
		//---�_���[�W���ʉ��Z
		crbatResultDamage(pDamageInfo);
		//---�_���[�W���ʕ\��
		crbatShowResult();
	} else if(ability == BAT_ECOM_TAMERU || ability == BAT_ECOM_IKIWOSUIKOMU){
		crsoundPlay(CRSOUND_UP);
		crbatDrawSceneWhile(1200);
	} else if(ability == BAT_ECOM_NERU){
		crbatDrawSceneWhile(500);
		pDamageInfo->pList[0]->AddBtStatus(BTST_NEMURI);
		crbatDrawSceneWhile(500);
	} else if(ability == BAT_ECOM_CR_RUINJUNBI){
		crbatDrawSceneWhile(500);
		crbatAnime_PreMagic(pChara,pDamageInfo);
		crbatDrawSceneWhile(500);
		crbatAnime_AfterMagic(pChara,pDamageInfo);
	} else {
		crbatDrawSceneWhile(1000);
	}

	return 1;
}

//---�\�͕ω��n
CRBATENEMYABILITY_API int crbatEnemy_Seichou(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int ability)
{
	//---InfoWindow�����
	pWin->SetType(CRWIN_TYPE_NORMAL);
	switch(ability){
	case BAT_ECOM_SEICHOU:
		crbatBWCreate(pWin,
			"����",BW_TOP | BW_CENTER);

		if(pChara->GetBattleFlag(0) <= 1){
			//---�����͂Q��܂�

			pChara->AddMaxLP(pChara->GetMaxLP() * 333 / 1000);
//			pChara->AddLP(pChara->GetMaxLP() * 333 / 1000);
			pChara->AddMaxMC(pChara->GetMaxMC() * 333 / 1000);
//			pChara->AddMC(pChara->GetMaxMC() * 333 / 1000);

			pChara->CharaInfo.power = (pChara->CharaInfo.power * 1333 / 1000);
			pChara->CharaInfo.agility = (pChara->CharaInfo.agility * 1333 / 1000);
			pChara->CharaInfo.soul = (pChara->CharaInfo.soul * 1333 / 1000);
			pChara->CharaInfo.magic = (pChara->CharaInfo.magic * 1333 / 1000);
			pChara->CharaInfo.level ++;

			pChara->SetBattleFlag(0,pChara->GetBattleFlag(0) + 1);
		}
		break;

	case BAT_ECOM_KINOUTUIKA:
		crbatBWCreate(pWin,
			"�@�\�ǉ�",BW_TOP | BW_CENTER);
		break;
	case BAT_ECOM_NORIUTURU:
	case BAT_ECOM_NORIUTURU2:
		if(pChara == pDamageInfo->pList[0])
			return 1;
		crbatBWCreate(pWin,
			"�̂肤��",BW_TOP | BW_CENTER);
		break;
	}

	//---�Փ˕␳
	crbatGetTargetChara(pChara,pChara->GetTarget(),
		pChara->Command.Range,&pDamageInfo->pList[0],1);
	if(pDamageInfo->pList[0] != NULL){
		//---�Փ˕␳�Ń^�[�Q�b�g���ς�����Ƃ��̂��߂�
		//---�L�����N�^�[�A���O���Đݒ�
		pDamageInfo->pList[0]->SetAngle(
			ANGLE(180) + pChara->GetCharaAngle(pDamageInfo->pList[0])
			);
	}

	crsoundPlay(CRSOUND_UP);
	if(ability != BAT_ECOM_NORIUTURU && ability != BAT_ECOM_NORIUTURU2)
		crbatDrawSceneWhile(1000);
	else
		crbatDrawSceneWhile(250);

	switch(ability){
	case BAT_ECOM_NORIUTURU:
	case BAT_ECOM_NORIUTURU2:
		pChara->Command.Sub[1] = pDamageInfo->pList[0]->GetFieldX();
		pChara->Command.Sub[2] = pDamageInfo->pList[0]->GetFieldY();
		crbatDoAnime_Move(pChara,pDamageInfo);

		pDamageInfo->pList[0]->AddMaxLP(pChara->GetLP());
		pDamageInfo->pList[0]->AddLP(pChara->GetLP());
		pDamageInfo->pList[0]->BattleInfo.Enemy.Experience += pChara->BattleInfo.Enemy.Experience;
		pDamageInfo->pList[0]->BattleInfo.Enemy.Money += pChara->BattleInfo.Enemy.Money;

		if(ability == BAT_ECOM_NORIUTURU){
			pDamageInfo->pList[0]->CharaInfo.power += 80;
			pDamageInfo->pList[0]->CharaInfo.vitality += 50;
			pDamageInfo->pList[0]->CharaInfo.agility += 50;
			pDamageInfo->pList[0]->CharaInfo.magic += 10;
			pDamageInfo->pList[0]->CharaInfo.magic_defense += 5;
		} else {
			pDamageInfo->pList[0]->CharaInfo.power += 150;
			pDamageInfo->pList[0]->CharaInfo.vitality += 100;
			pDamageInfo->pList[0]->CharaInfo.agility += 100;
			pDamageInfo->pList[0]->CharaInfo.magic += 15;
			pDamageInfo->pList[0]->CharaInfo.magic_defense += 6;
		}


		pChara->SetFieldPos(pDamageInfo->pList[0]->GetFieldX(),pDamageInfo->pList[0]->GetFieldY());

		pChara->SetLP(0);
		pChara->BattleInfo.Existence = 0;
		crbatClearDrawingList();
		crbatAddDrawingListAll();
		crbatDrawSceneWhile(250);

		break;

	case BAT_ECOM_KINOUTUIKA:

/*		pChara->CharaInfo.power += 30;
		crbatBWCreate(pWin,
			"�U���͂t�o",BW_TOP | BW_CENTER);
		crbatDrawSceneWhile(1000);
*/
		crsoundPlay(CRSOUND_UP);
		pDamageInfo->pList[0]->CharaInfo.agility += 30;
		crbatBWCreate(pWin,
			"�s���͂t�o",BW_TOP | BW_CENTER);
		crbatDrawSceneWhile(1000);

		crsoundPlay(CRSOUND_UP);
		pDamageInfo->pList[0]->CharaInfo.vitality += 20;
		crbatBWCreate(pWin,
			"�h��͂t�o",BW_TOP | BW_CENTER);
		crbatDrawSceneWhile(1000);

		int rnd = eiRnd(1000);

		crsoundPlay(CRSOUND_UP);
		if(rnd < 250){
			pDamageInfo->pList[0]->BattleInfo.Element[ELEMENT_FIRE] = 0;
			crbatBWCreate(pWin,
				"��������",BW_TOP | BW_CENTER);
			crbatDrawSceneWhile(1000);
		} else if(rnd < 500){
			pDamageInfo->pList[0]->BattleInfo.Element[ELEMENT_AQUA] = 0;
			crbatBWCreate(pWin,
				"��������",BW_TOP | BW_CENTER);
			crbatDrawSceneWhile(1000);
		} else if(rnd < 750){
			pDamageInfo->pList[0]->BattleInfo.Element[ELEMENT_EARTH] = 0;
			crbatBWCreate(pWin,
				"�y������",BW_TOP | BW_CENTER);
			crbatDrawSceneWhile(1000);
		} else {
			pDamageInfo->pList[0]->BattleInfo.Element[ELEMENT_WIND] = 0;
			crbatBWCreate(pWin,
				"��������",BW_TOP | BW_CENTER);
			crbatDrawSceneWhile(1000);
		}

		break;
	}

	return 1;
}

//---�ړ�
CRBATENEMYABILITY_API int crbatEnemy_Ido(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int ability)
{
	int a,damage = pChara->Command.Sub[3],element = 0;
	//---InfoWindow�����
	pWin->SetType(CRWIN_TYPE_NORMAL);

	switch(ability){
	case BAT_ECOM_RYUSA:
		crbatBWCreate(pWin,
			"����",BW_TOP | BW_CENTER);
		element = ELEMENT_NOELEMENT;

		break;

	case BAT_ECOM_GRAVITY:
		crbatBWCreate(pWin,
			"�O���r�e�B",BW_TOP | BW_CENTER);
		element = ELEMENT_NOELEMENT;

		break;

	case BAT_ECOM_CR_ATUMERU:
		crbatBWCreate(pWin,
			"�O���r�e�B",BW_TOP | BW_CENTER);
		element = ELEMENT_NOELEMENT;

		break;

	case BAT_ECOM_CR_TOBASU:
		crbatBWCreate(pWin,
			"�˗�",BW_TOP | BW_CENTER);
		element = ELEMENT_NOELEMENT;

		break;
	}

	crbatSetDamageMode(pDamageInfo,DAMAGEMODE_SUB);

	int x[BATTLECHARA_MAX],y[BATTLECHARA_MAX],kx[BATTLECHARA_MAX],ky[BATTLECHARA_MAX];
	float dx,dy,angle,dis = 2.0f;

	switch(ability){
	case BAT_ECOM_RYUSA:
	case BAT_ECOM_GRAVITY:
	case BAT_ECOM_CR_TOBASU:
	case BAT_ECOM_CR_ATUMERU:
//		crsoundPlay(CRSOUND_GURUGURUMEDAMA);
		crbatDrawSceneWhile(1000);

		if(ability == BAT_ECOM_GRAVITY){
			dis = 4.0f;
		}
		if(ability == BAT_ECOM_CR_TOBASU){
			dis = 8.0f;
		}

		crbatCalcDamage(
			pDamageInfo,pChara,
			SRC_LEVEL,1000,
			DST_LEVEL,1000,
			CALCMODE_PROB,1,
			0,//---���U�i�P�^�P�O�O�O�P�ʁj
			0,
			PROBMODE_100,1000,//---���햽����𗦁A������
			0
		);

		if(ability == BAT_ECOM_RYUSA){
			crsoundPlay(CRSOUND_FIRE1);
		} else if(ability == BAT_ECOM_GRAVITY || ability == BAT_ECOM_CR_ATUMERU){
			crsoundPlay(CRSOUND_DOWN);
		} else if(ability == BAT_ECOM_CR_TOBASU){
			crbatDoAnime_Weapon(pChara,pDamageInfo,1);
		}

		for(a = 0;pDamageInfo->pList[a] != NULL;a++){
			pDamageInfo->Damage[a] = 1;
			if(pDamageInfo->pList[a]->GetBtStatus() & BTST_WORLD){
				pDamageInfo->Damage[a] = 0;
			}

			dx = (float)pChara->GetFieldX() - pDamageInfo->pList[a]->GetFieldX();
			dx = dx * dx;
			dy = (float)pChara->GetFieldY() - pDamageInfo->pList[a]->GetFieldY();
			dy = dy * dy;
			angle = pChara->GetCharaAngle(pDamageInfo->pList[a]);

			if(pDamageInfo->Damage[a]){
//				&& dx + dy >= 4.0f){

				if(ability == BAT_ECOM_CR_TOBASU){
					if(dx + dy <= 64.0f){
						x[a] = (int)((float)cos(angle) * dis) + pChara->GetFieldX();
						y[a] = (int)((float)sin(angle) * dis) + pChara->GetFieldY();
					} else {
						x[a] = pChara->GetFieldX();
						y[a] = pChara->GetFieldY();
					}
				} else if(dx + dy >= 4.0f){
					x[a] = (int)((float)cos(angle) * dis) + pChara->GetFieldX();
					y[a] = (int)((float)sin(angle) * dis) + pChara->GetFieldY();
				} else {
					x[a] = pChara->GetFieldX();
					y[a] = pChara->GetFieldY();
				}

				if(x[a] < 0)
					x[a] = 0;
				if(x[a] >= BATTLEFIELD_MAX_X)
					x[a] = BATTLEFIELD_MAX_X - 1;
				if(y[a] < 0)
					y[a] = 0;
				if(y[a] >= BATTLEFIELD_MAX_Y)
					y[a] = BATTLEFIELD_MAX_Y - 1;

				int loop = 0;

				while(crbatIsThere(x[a],y[a],pDamageInfo->pList[a])){
					//---�N�����Ȃ��Ȃ�܂�
					if(loop <= 1){
						if(1 <= x[a] && x[a] <= 6)
							x[a] --;
						else if(7 <= x[a] && x[a] <= 10)
							x[a] ++;
						else if(1 <= y[a] && y[a] <= 6)
							y[a] --;
						else if(7 <= y[a] && y[a] <= 10)
							y[a] --;
					} else {
						if(0 <= x[a] && x[a] <= 6)
							x[a] --;
						else if(7 <= x[a] && x[a] <= 11)
							x[a] ++;
						else if(0 <= y[a] && y[a] <= 6)
							y[a] --;
						else if(7 <= y[a] && y[a] <= 11)
							y[a] --;
					}

					if(x[a] < 0)
						x[a] = 7;
					if(y[a] < 0)
						y[a] = 7;
					if(x[a] >= BATTLEFIELD_MAX_X)
						x[a] = 6;
					if(y[a] >= BATTLEFIELD_MAX_Y)
						y[a] = 6;

					loop ++;
				}
				kx[a] = pDamageInfo->pList[a]->GetFieldX();
				ky[a] = pDamageInfo->pList[a]->GetFieldY();
				pDamageInfo->pList[a]->SetFieldPos(x[a],y[a]);
			} else {
				pDamageInfo->Damage[a] = 0;
			}
		}

		//---�t�B�[���h�ʒu�����ɖ߂�
		for(a = 0;pDamageInfo->pList[a] != NULL;a++){
			if(pDamageInfo->Damage[a]){
				pDamageInfo->pList[a]->SetFieldPos(kx[a],ky[a]);
			}
		}

		crbatDoAnime_Move2(pChara,pDamageInfo,x,y,
			ability == BAT_ECOM_CR_TOBASU ? CHARSPEED_TOBU : CHARSPEED_WALK);

		for(a = 0;pDamageInfo->pList[a] != NULL;a++){
			if(pDamageInfo->Damage[a]){
				pDamageInfo->pList[a]->SetFieldPos(x[a],y[a]);
				pDamageInfo->DontShowThisDamage[a] = 0;
				pDamageInfo->Miss[a] = 0;
			}
		}
		break;

	}

	//---�_���[�W
	if(ability == BAT_ECOM_CR_TOBASU){
		crbatSetDamageMode(pDamageInfo,DAMAGEMODE_SUB);

		//---�U���l�A�h��l�A�v�Z���@�A����
		//---�_���[�W�v�Z
		crbatCalcDamage(
			pDamageInfo,pChara,
			SRC_DIRECT,pChara->Command.Sub[3],
			DST_NONE,1000,
			CALCMODE_ADD,1000,
			160,//---���U�i�P�^�P�O�O�O�P�ʁj
			element,
			PROBMODE_100,1000,//---���햽����𗦁A������
			DEFENSEMODE_REAL
		);

		crbatClearDrawingList();
		crbatAddDrawingListAll();
		crbatShowDamage(pDamageInfo);
		//---�_���[�W���ʉ��Z
		crbatResultDamage(pDamageInfo);
	}

	//---�_���[�W���ʕ\��
	crbatShowResult();

	return 1;
}

//---�ړ�
CRBATENEMYABILITY_API int crbatEnemy_Cresteaju(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int ability)
{
	crbatDrawSceneWhile(1000);

	RECT rect = {0,0,640,480};
	crefectScreenEfect_FadeOut(&rect,2000,RGB_MAKE(255,255,255));
	et->Delay2(1000);

	return 1;
}

CRBATANIME_API void crbatDoAnime_MagicCrasiveHenshin(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo);

//---�N���C�V���ϐg
CRBATENEMYABILITY_API int crbatEnemy_CrHenshin(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int ability)
{
	int enemy = 224;

	crbatDrawSceneWhile(1000);

	crbatDoAnime_MagicCrasiveHenshin(pChara,pDamageInfo);
	crbatDrawFlash(255,255,255);
	crbatDrawRefresh();

	et->Delay2(1000);

	pChara->SetCell(&BattleEnemyCell[3 * BATTLE_ENEMYPATTERNSIZE]);

	crbatAnime_Flash(pChara,pDamageInfo,1000,255,255,255);

	memcpy(&pChara->CharaInfo,&pEnemyCharaInfo[enemy],sizeof(pChara->CharaInfo));
	memcpy(&pChara->BattleInfo,&pEnemyBatInfo[enemy],sizeof(pChara->BattleInfo));
	memset(&pChara->CharaInfo.eq_weapon[0],0,sizeof(pChara->CharaInfo.eq_weapon));
	memset(&pChara->CharaInfo.eq_protector[0],0,sizeof(pChara->CharaInfo.eq_protector));
	memset(&pChara->Command,0,sizeof(pChara->Command));

	pChara->SetAbility(BTAB_P_HENKA_12,1);
	pChara->SetAbility(BTAB_P_SOKUSHI,1);
	pChara->SetCell(&BattleEnemyCell[3 * BATTLE_ENEMYPATTERNSIZE]);
	pChara->BattleInfo.Existence = 1;
	pChara->SetDrawType(pChara->BattleInfo.Enemy.GraphicType);
	//---�y�I�t�Z�b�g
	pChara->SetZOffset((float)(pChara->BattleInfo.Enemy.ZOffset) / 100.0f);

	//---�ϐg����
	pChara->SetBattleFlag(0,2);
	pChara->SetBattleFlag(1,0);

	crbatResetTurn(1);

	crbatClearDrawingList();
	crbatAddDrawingListAll();

	int live = pChara->GetBattleFlag(2);
	crbatDrawSceneWhile(1000);
	pChara->SetAngle(pChara->GetCharaAngle(&pBtChara[live]));
	crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);
	crbatBeginCameraObjectToObject(0,pChara,&pBtChara[live],
		ANGLE(180),
		-1.0f,-1.0f,500);
	crbatDoMovingCamera(2000);

/*
	int sx = pChara->GetFieldX() , sy = pChara->GetFieldY();
	int cx = pBtChara[live].GetFieldX() , cy = pBtChara[live].GetFieldY();
	int dx = cx - sx, dy = cy - sy;

	float fx,fy;

	if(dx == 0){
	} else {

	}

	pChara->BeginAnime(0);
	pChara->SetAnimeMoving(
		(float)pBtChara[live].GetFieldX(),
		(float)pBtChara[live].GetFieldY(),
		(float)pChara->GetFieldZ(),CHARSPEED_RUN,1);

	eiTime let,let2;
	int AddWorld = 0,flag,begin_anime = 0,sound = 0;
	float dis;
	int anime_type = 0,anime_wait = 0;

//	pChara->SetAnimeLimitTime(1000.0f);
//	pChara->SetMoveSpeed(0.0f);

	let2.Reset();
	flag = 1;
	while(flag){
		let.Reset();
		if(let2.Get() > 1000)
			break;

		crbatClearDrawingList();
		crbatAddDrawingListAll();

		crbatBeginAnime(); {
			dis = pChara->DoAnime((float)AddWorld);
		} crbatEndAnime();

crdataEnableRec(0);
		crbatDrawScene();
crdataEnableRec(1);

		if(eiGetEndThread()){
			break;
		}
		crbatDrawRefresh();

		AddWorld = let.Get();
	}
	pChara->EndAnime();*/

	return 1;
}

//---�G�̓���U��
CRBATENEMYABILITY_API int crbatDoAction_EnemyAbility(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin)
{
	int sub = pChara->Command.Sub[0];

	//---�^�[�Q�b�g�����Ȃ�������
	if(pChara->Command.Target == 0){
		return 0;
	}
	//---�����s�����Ƃ�Ȃ�������
	if(!pChara->IsEnableMoveing()){
		return 0;
	}

	switch(sub){
	//---�k�o�z���n�U��
	case BAT_ECOM_KYUKETSU:
	case BAT_ECOM_TABERU:
	case BAT_ECOM_KYUKETUKEN:
		return crbatEnemy_Kyuketsu(pDamageInfo,pChara,pWin,sub);

	//---���ڍU��
	case BAT_ECOM_NAGURU:
	case BAT_ECOM_KAMITUKU:
	case BAT_ECOM_KIRIKAKARU:
	case BAT_ECOM_PIERUZAN:
	case BAT_ECOM_JURIASGIRI:
	case BAT_ECOM_TOSSHIN:
	case BAT_ECOM_KAITENATACK:
	case BAT_ECOM_HAGESHIKU:
	case BAT_ECOM_NAGITAOSU:
	case BAT_ECOM_TOTUGEKI:
	case BAT_ECOM_SHOGEKIHA:
	case BAT_ECOM_CHOUONPA:
	case BAT_ECOM_ENGETUZAN:
	case BAT_ECOM_SEKKINATACK:
	case BAT_ECOM_IREBACRASH:
	case BAT_ECOM_HOSHOKU:
	case BAT_ECOM_SAN:
	case BAT_ECOM_RARFIAATACK:
	case BAT_ECOM_DANDYSPRASHER:
	case BAT_ECOM_ONSOKU:
	case BAT_ECOM_SILENTBANISHA:
	case BAT_ECOM_SETUDAN:
	case BAT_ECOM_ROUOU:
	case BAT_ECOM_CR_LINEKOGEKI:
	case BAT_ECOM_CR_SINGLEKOGEKI:
		return crbatEnemy_ExtendAtack(pDamageInfo,pChara,pWin,sub);

	//---�u���X�n�U��
	case BAT_ECOM_HONO:
	case BAT_ECOM_FUBUKI:
	case BAT_ECOM_TOPPU:
	case BAT_ECOM_SUNAARASHI:
	case BAT_ECOM_IKADUCHI:
	case BAT_ECOM_HONO2:
	case BAT_ECOM_FUBUKI2:
	case BAT_ECOM_TOPPU2:
	case BAT_ECOM_SUNAARASHI2:
	case BAT_ECOM_IKADUCHI2:
	case BAT_ECOM_DAIKAEN:
	case BAT_ECOM_CRFUBUKI:
		return crbatEnemy_Breath(pDamageInfo,pChara,pWin,sub);

	//---���ڃ_���[�W�n
	case BAT_ECOM_EYEBEAM:
	case BAT_ECOM_MISTYBEAM:
	case BAT_ECOM_POWERBOMB:
	case BAT_ECOM_KASCADEBOMB:
	case BAT_ECOM_LAYZERBEAM:
	case BAT_ECOM_MIZUDEPPOU:
	case BAT_ECOM_KAENHOUSHA:
	case BAT_ECOM_JIBAKU1:
	case BAT_ECOM_JIBAKU2:
	case BAT_ECOM_JIBAKU3:
	case BAT_ECOM_JIBAKU4:
	case BAT_ECOM_TAKISIDOBEAM:
	case BAT_ECOM_CRESTEAJU1:
	case BAT_ECOM_SINRYAKUHEI:
	case BAT_ECOM_SINRYAKUHEI_BOMB:
	case BAT_ECOM_ITAMIWAKE_DAMAGE:
	case BAT_ECOM_DANDYSPARK:
	case BAT_ECOM_RIBONTUISTA:
	case BAT_ECOM_RESERVE:

		return crbatEnemy_DirectAtack(pDamageInfo,pChara,pWin,sub);

	//---�E�q�n�U��
	case BAT_ECOM_POISON:
	case BAT_ECOM_HOUSHI:
	case BAT_ECOM_SILENTBREATH:
	case BAT_ECOM_SLEEPBREATH:
	case BAT_ECOM_NEMURINOKONA:
	case BAT_ECOM_DARUDARUHA:
	case BAT_ECOM_AKUBI:
	case BAT_ECOM_KAFUN:
	case BAT_ECOM_MODOKUNOIKI:
	case BAT_ECOM_SANSEIU:
	case BAT_ECOM_SABORU:
	case BAT_ECOM_PINKMIST:
	case BAT_ECOM_TOSO:
		return crbatEnemy_Houshi(pDamageInfo,pChara,pWin,sub);

	//---�k�o�����n�U��
	case BAT_ECOM_TOKASU:
	case BAT_ECOM_HANBUSSHITU:
	case BAT_ECOM_SHINSHOKU:
	case BAT_ECOM_HANBUSSHITU_ZENTAI:
	case BAT_ECOM_820:
	case BAT_ECOM_DIVIDING:
		return crbatEnemy_LPRateDamage(pDamageInfo,pChara,pWin,sub);

	//---�����n�U��
	case BAT_ECOM_CHISSOKU_1_10:
	case BAT_ECOM_CHISSOKU_1_5:
	case BAT_ECOM_CHISSOKU_1_2:
	case BAT_ECOM_CHISSOKU_2_3:
		return crbatEnemy_DeathAtack(pDamageInfo,pChara,pWin,sub);

	//---����n
	case BAT_ECOM_BUNRETU:
		return crbatEnemy_Bunretu(pDamageInfo,pChara,pWin,sub);

	//---�񕜌n�E�h��
	case BAT_ECOM_KOUGOUSEI:
	case BAT_ECOM_SAISEI:
	case BAT_ECOM_LPCHANGE:
	case BAT_ECOM_TAMERU:
	case BAT_ECOM_KARA:
	case BAT_ECOM_SHURI:
	case BAT_ECOM_BARRIERTENKAI:
	case BAT_ECOM_KASCADE_JUNBI:
	case BAT_ECOM_KASCADE_KYOKA:
	case BAT_ECOM_HANBUSSITU_JUNBI:
	case BAT_ECOM_KASCADE_SAIDAI:

	case BAT_ECOM_NERU:
	case BAT_ECOM_KIDOU:
	case BAT_ECOM_BOSOKAISHI:
	case BAT_ECOM_CR_RUINJUNBI:
	case BAT_ECOM_IKIWOSUIKOMU:
	case BAT_ECOM_KIDOSASERU:
		return crbatEnemy_Kaifuku(pDamageInfo,pChara,pWin,sub);

	case BAT_ECOM_CR_HENSHIN:
		return crbatEnemy_CrHenshin(pDamageInfo,pChara,pWin,sub);

	//---�\�͕ω��n
	case BAT_ECOM_SEICHOU:
	case BAT_ECOM_KINOUTUIKA:
	case BAT_ECOM_NORIUTURU:
	case BAT_ECOM_NORIUTURU2:
		return crbatEnemy_Seichou(pDamageInfo,pChara,pWin,sub);
	case BAT_ECOM_GURUGURUMEDAMA:
	case BAT_ECOM_GURUGURUHYPER:
	case BAT_ECOM_JENTLEFLASH:
	case BAT_ECOM_KONRANKOUSEN:
	case BAT_ECOM_ITAMIWAKE:
	case BAT_ECOM_ITAMIWAKE_JIZOKU:
	case BAT_ECOM_ITAMIWAKE_KAIJO:
	case BAT_ECOM_MCBUNKAI:
	case BAT_ECOM_SOKUSHIKOUSEN:
	case BAT_ECOM_JAKUKAKOSEN:
	case BAT_ECOM_DAIKONRAN:
		return crbatEnemy_GuruGuruMedama(pDamageInfo,pChara,pWin,sub);

	case BAT_ECOM_RYUSA:
	case BAT_ECOM_GRAVITY:
	case BAT_ECOM_CR_ATUMERU:
	case BAT_ECOM_CR_TOBASU:
		return crbatEnemy_Ido(pDamageInfo,pChara,pWin,sub);

	case BAT_ECOM_CRESTEAJU2:
		return crbatEnemy_Cresteaju(pDamageInfo,pChara,pWin,sub);
	}

	return 1;
}

