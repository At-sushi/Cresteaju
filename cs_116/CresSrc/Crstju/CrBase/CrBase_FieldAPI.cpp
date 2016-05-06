/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBase.cpp ...FieldBase functions

-----------------------------------------------------------*/

#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBASE_FIELDAPI

#define EXTERN_EICLASS
#include "..\CrBase.h"

#define CR_GAMEINFO_EXTERNPOINTER
#include "..\CrGameInfo.h"

//-----------------------------------
static int MapMusicTable[] = 
{
	3,3,3,3,3,
	3,3,3,3,3,
//---10(filed),		11(opening),12,	13(�E�F�X�J���j,			14(�E�F�X�J)	15�i�N���X�t�B�[���h�j
	CRMUSIC_FIELD1,CRMUSIC_OPENING,CRMUSIC_FIELD1,CRMUSIC_FIELD1,CRMUSIC_TOWN1,CRMUSIC_TOWN1,
//---16(�Z�[�l�j	17�i���j	 18�i�E�F�X�J�k�̐X�j19�i�Z�[�l�k���̐X�j20�i�A�l�[�g�ւ̎R���j
	CRMUSIC_TOWN1,CRMUSIC_FIELD1,CRMUSIC_DANGEON1,CRMUSIC_DANGEON1,CRMUSIC_DANGEON1,
//---21(�A�l�[�g)�@22�i�h�[�O���j 23�i�r�r�{���j 24�i�h�[�O����̐X�j25�i�h�[�O����̈�Ձj
	CRMUSIC_TOWN1,CRMUSIC_VILLAGE1,CRMUSIC_DANGEON1,CRMUSIC_DANGEON1,CRMUSIC_DANGEON2,
//---26�i�t�F�C�}���j 27�i�f�r�D������j 28�i�n�̈�Ձj 29�i���̈�Ձj 30(�N���X�t�B�[���h���n)
	CRMUSIC_TOWNETERNAL,CRMUSIC_FIELD1,CRMUSIC_DANGEON2,CRMUSIC_DANGEON2,CRMUSIC_FIELD1,

//---31�i�������j32�i�N���X�t�B�[���h�j33�i�Ñ�}���فj,34�i���f�̐X�j,35�i���f�̈�Ձj
	CRMUSIC_DANGEON1,CRMUSIC_TOWNETERNAL,CRMUSIC_FIELD1,CRMUSIC_DANGEON3,CRMUSIC_OPENING,
//---36�i���C�N�E���[�h�j 37�i�g���C�A�j 38�i�����R���j39�i�m�[�X�e���A�j40�i�_�C�j
	CRMUSIC_DANGEON1,CRMUSIC_VILLAGE1,CRMUSIC_OILLAKE,CRMUSIC_TOWN2,CRMUSIC_VILLAGE1,
//---41�i�}�[�N�X�j42�i�_�C�̐X�j43�i�f�c�[�̓��A�j44�i�m�[�X�e���A�̓��A�j 45(�_�����΍̌@��)
	CRMUSIC_TOWN2,CRMUSIC_DANGEON1,CRMUSIC_DANGEON1,CRMUSIC_DANGEON1,CRMUSIC_FIELD1,
//---46�i�m�[�X�e���A�̈�Ձj47�i���j48�i���i���̖��j 49�i�S�E�A�j50�i�f�r�D������j
	CRMUSIC_DANGEON2,CRMUSIC_FIELD1,CRMUSIC_FIELD1,CRMUSIC_ZENUREN,CRMUSIC_FIELD1,

//---51�i�A���V�A�j52�i��N���[�^�[�j53�i�A���V�A�Ίݓ��A�j54�i�Z�m�E�j 55�i�[�r�A�}�C���j
	CRMUSIC_VILLAGE2,CRMUSIC_FIELD1,CRMUSIC_DANGEON1,CRMUSIC_FIELD1,CRMUSIC_TOWNETERNAL,
//---56�i�Y�B�j57�i�Y�B��Ձj	58�i�[�r�A�}�C���D������j 59�i�O���E���h�V�b�v�j60�i�f�r�N���X�t�B�[���h�j
	CRMUSIC_DANGEON1,CRMUSIC_DANGEON2,CRMUSIC_FIELD1,CRMUSIC_GS,CRMUSIC_FIELD1,

//---61�i�c�[���A�j,62�i�c�[���A�D������j63�i�n���ʘH�j64�i�G�^�[�i�������j65�i�����E�l�̉Ɓj
	CRMUSIC_TOWNETERNAL,CRMUSIC_FIELD1,CRMUSIC_DANGEON1,CRMUSIC_TOWNETERNAL,CRMUSIC_TOWN1,
//---66�i�Y��l�̉Ɓj67�i�W�[�_�C�`�j68�i�W�[�_�C�쓴�A�j69(�L���̈�ՊO) 70(�L���̈��)
	CRMUSIC_TOWN1,CRMUSIC_FIELD1,CRMUSIC_DANGEON1,CRMUSIC_FIELD1,CRMUSIC_DANGEON2,
//---71-74�i�L���̒��j75�i�o�C�c�j
	CRMUSIC_TITLE,CRMUSIC_FIELD1,CRMUSIC_TITLE,CRMUSIC_OPENING,CRMUSIC_TOWN1,
//---76�i�_�̎R�j77�i�V���o�[�X�^�[�j78�i�T���s�A�X�j79�i�T���s�A�X�̐X�j80�i��_�a�j
	CRMUSIC_FIELD1,CRMUSIC_TOWN1,CRMUSIC_SINCETHEDAY,CRMUSIC_SINCETHEDAY,CRMUSIC_ETERNAL,

//---81�i�����̈�Ձj82�i凋C�O�̓��j83�i��N���[�^�[�j84�i���[���N���C���j85�i�łт̈�Ձj
	CRMUSIC_DANGEON2,CRMUSIC_OILLAKE,CRMUSIC_DANGEON2,CRMUSIC_VILLAGE1,CRMUSIC_DANGEON2,

//---86�i�Y���ꂽ��Ձj87�i��ጴ�̉Ɓj88�i�����̓��A�j89�i�i����j90�i�����K�j
	CRMUSIC_NIGHT,CRMUSIC_VILLAGE1,CRMUSIC_DANGEON1,CRMUSIC_FIELD1,CRMUSIC_DANGEON2,
//---91�i�쌴�̃^���X�j92�`95�i�C���[�f�B�A�j
	CRMUSIC_FIELD1,CRMUSIC_METEOR,CRMUSIC_METEOR,CRMUSIC_METEOR,CRMUSIC_METEOR,

//---96 97�i�ю�������j98�i�g���C�A�̓��A�j
	CRMUSIC_FIELD1,CRMUSIC_TOWN1,CRMUSIC_DANGEON1,CRMUSIC_FIELD1,CRMUSIC_DANGEON2,
//---101�iED�F�ÈŁj
	CRMUSIC_SILENT,CRMUSIC_SILENT,CRMUSIC_SILENT,CRMUSIC_SILENT,CRMUSIC_SILENT
};

//---rect
static int UseFadeRect = 0;
static RECT FadeRect;

//---�t�B�[���h�R�[���o�b�N
static eiCell FieldBGCell;
void BaseFieldCallBack(eiCell *pScrCell,int sx,int sy,int top_x,int top_y,int delta_t)
{
	int map = pGameInfo->MapNumber,scene = crfieldGetMapScene();

	if(map == 30){
		if(scene == 2 || scene == 3){
			FieldBGCell.PutExtend(ew->lpCell[1],0,0,2.00,2.00,EI_PSET);
		}
	} else if(map == 76){
		if(scene == 3 || scene == 4){
			FieldBGCell.PutExtend(ew->lpCell[1],0,0,2.00,2.00,EI_PSET);
		}
	} else if(map == 82){
		//---凋C�O�̓�
		if(scene == 9){
			FieldBGCell.PutExtend(ew->lpCell[1],0,0,2.00,2.00,EI_PSET);
		}
	}
}

static ei_s32 IgnoreEvent = 0;
static void (*lpMapChangeCallBack)(int,int) = NULL;

CRBASE_FIELDAPI void crfieldSetMapChangeCallBack(void (*lpCallBack)(int,int))
{
	lpMapChangeCallBack = lpCallBack;
}

//---�C�x���g���e�ɉ����ă}�b�v���e��ύX
CRBASE_FIELDAPI int crfieldSetMapEvent(int number,int scene)
{
	if(lpMapChangeCallBack != NULL){
		(*lpMapChangeCallBack)(number,scene);
	}
	return 1;
}

//---�C�x���g�����ݒ�
CRBASE_FIELDAPI void crfieldSetIgonoreEvent(int mode)
{
	IgnoreEvent = mode;
}

CRBASE_FIELDAPI int crfieldGetIgonoreEvent(void)
{
	return IgnoreEvent;
}

//---�}�b�v�i���o�[�擾
CRBASE_FIELDAPI int crfieldGetMapNumber(void)
{
	return pGameInfo->MapNumber;
}

//---�}�b�v�V�[���擾
CRBASE_FIELDAPI int crfieldGetMapScene(void)
{
	return pGameInfo->MapScene;
}

//---�p���b�g��ς���
CRBASE_FIELDAPI void crfieldPaletteChange_Cell(eiCell *pcell,int number)
{
	int a = 0;
	int pal,r,g,b;

	{
		if(pcell[a].Data.CreateFlag){
			if(number == PALETTE_NIGHT){
				for(pal = 0;pal < 256;pal ++){
					r = pcell[a].dib.GetPaletteRed(pal) - 72;
					g = pcell[a].dib.GetPaletteGreen(pal) - 72;
					b = pcell[a].dib.GetPaletteBlue(pal);
					if(r < 0)
						r = 0;
					if(g < 0)
						g = 0;
					if(b > 255)
						b = 255;
					pcell[a].dib.SetPalette(pal,r,g,b);
				}
			} else if(number == PALETTE_SUNSET){
				for(pal = 0;pal < 256;pal ++){
					r = pcell[a].dib.GetPaletteRed(pal) + 16;
					g = pcell[a].dib.GetPaletteGreen(pal) - 32;
					b = pcell[a].dib.GetPaletteBlue(pal) - 24;
					if(r > 255)
						r = 255;
					if(g < 0)
						g = 0;
					if(b < 0)
						b = 0;
					pcell[a].dib.SetPalette(pal,r,g,b);
				}
			} else if(number == PALETTE_FOG){
				for(pal = 0;pal < 256;pal ++){
					r = pcell[a].dib.GetPaletteRed(pal) + 64;
					g = pcell[a].dib.GetPaletteGreen(pal) + 64;
					b = pcell[a].dib.GetPaletteBlue(pal) + 64;
					if(r > 255)
						r = 255;
					if(g > 255)
						g = 255;
					if(b > 255)
						b = 255;
					pcell[a].dib.SetPalette(pal,r,g,b);
				}
			} else if(number == PALETTE_MONO){
				int mono;
				for(pal = 0;pal < 256;pal ++){
					mono = (pcell[a].dib.GetPaletteRed(pal)
						+ pcell[a].dib.GetPaletteGreen(pal)
						+ pcell[a].dib.GetPaletteBlue(pal)) / 3;
					r = g = b = mono;
					pcell[a].dib.SetPalette(pal,r,g,b);
				}
			}
		}
	}
}

CRBASE_FIELDAPI void crfieldPaletteChange(int number)
{
	int a,pal,r,g,b;

	for(a = CR_PTN_FIELD;a < CR_PTN_FIELD + EF_OBJECT_PATTERNOFFSET + (EF_OBJECT_PATTERNSIZE * EF_OBJECT_PATTERNMAX);a ++){
		crfieldPaletteChange_Cell(&pCell[a],number);
	}
	for(a = 0;a < EF_PATTERN_PAGEMAX;a ++){
		em->SetPatternSurface(a);
	}
	for(a = 0;a < EF_OBJECT_PATTERNMAX;a ++){
		em->SetObjectSurface(a);
	}
	
	if(number == PALETTE_MONO && crfieldGetMapNumber() == 30){
		int mono;
		for(pal = 0;pal < 256;pal ++){
			mono = (FieldBGCell.dib.GetPaletteRed(pal)
				+ FieldBGCell.dib.GetPaletteGreen(pal)
				+ FieldBGCell.dib.GetPaletteBlue(pal)) / 3;
			r = g = b = mono;
			FieldBGCell.dib.SetPalette(pal,r,g,b);
		}
		RECT rect = {0,240,320,480};
		FieldBGCell.SetSurface(&rect,3);
	}
}

CRBASE_FIELDAPI void crfieldLoadAddData(void)
{
	int number = crfieldGetMapNumber();

	if(number == 30){
		//---�a�f��ǂݍ���
		//---�R�[���o�b�N�ݒ�
		ef->SetBGCallback(BaseFieldCallBack);
		FieldBGCell.ReadFile(CR_DATADIR1"FieldBGMount1.acf",CR_DATAFILE1,crdataGetFileMode());
		RECT rect = {0,240,320,480};
		FieldBGCell.SetSurface(&rect,3,0);
	} else if(number == 76){
		//---�a�f��ǂݍ���
		//---�R�[���o�b�N�ݒ�
		ef->SetBGCallback(BaseFieldCallBack);
		FieldBGCell.ReadFile(CR_DATADIR1"FieldBGMount2.acf",CR_DATAFILE1,crdataGetFileMode());
		RECT rect = {0,240,320,480};
		FieldBGCell.SetSurface(&rect,3,0);
	} else if(number == 82){
		//---�a�f��ǂݍ���
		//---�R�[���o�b�N�ݒ�
		ef->SetBGCallback(BaseFieldCallBack);
		FieldBGCell.ReadFile(CR_DATADIR1"FieldBGShinkiro.acf",CR_DATAFILE1,crdataGetFileMode());
		RECT rect = {0,240,320,480};
		FieldBGCell.SetSurface(&rect,3,0);
	} else {
//		FieldBGCell.Release();
	}
}

//--------------------------S�����̂̓X�^���_�[�g�ŁA��ʌ��ʊ܂�
//---�}�b�v�؂�ւ�
CRBASE_FIELDAPI int crfieldChangeMap(int number,int scene,
						int force /*= 0 :����*/,int music /*= 1*/)
{
	char s[80];
	static int MapNumber = -1;

	if(number == MapNumber && force == 0/*�������[�h*/){
		//---�O��Ɠ����}�b�v�������珈���������̂��߂Ƀ��[�h���Ȃ�
		//---�V�[�������ς���
		em->SetActiveMap(scene);
		return 2;
	}
	pGameInfo->MapNumber = MapNumber = number;
	pGameInfo->MapScene = scene;

	if(number <= 9)
		sprintf(s,CR_DATADIR2"CrMap_00%d.map",number);
	else if(number <= 99)
		sprintf(s,CR_DATADIR2"CrMap_0%d.map",number);
	else
		sprintf(s,CR_DATADIR2"CrMap_%d.map",number);

	//---�}�b�v���[�h
	em->Load(s,CR_DATAFILE2,crdataGetFileMode()/*::CrFileMode*/);
	em->SetActiveMap(scene);

	if(number == 10){
		//---�t�B�[���h��������O���E���h�V�b�v
		crfieldSetGroundShipPos();
	}
	//---�C�x���g�ɍ��킹�ă}�b�v���e�ύX
	crfieldSetMapEvent(number,scene);

	//---���y���[�h
	if(music){
		crfieldChangeMapMusic();
	}
	//---�ǉ��f�[�^�ǂݍ���
	crfieldLoadAddData();

	//---�v���[���͂P�ɐݒ�
	crfieldChangePlane(1);

	return 1;
}

CRBASE_FIELDAPI int crfieldChangeMapSceneS(int number,int scene,int sx,int sy,int force /*= 0 :����*/,int music /*= 1*/)
{
	crfieldChangeMapS(number,scene,force,music);
	crfieldChangeSceneS(scene,sx,sy);

	return 1;
}

CRBASE_FIELDAPI int crfieldChangeMapS(int number,int scene,int force /*= 0 :����*/,int music /*= 1*/)
{
	crfieldChangeMap(number,scene,force,music);
	return 1;
}

//---�}�b�v�V�[���؂芷��
CRBASE_FIELDAPI void crfieldChangeScene(int scene,int sx /*= -1*/,int sy /*= -1*/)
{
	//---�V�[���؂芷��
	em->SetActiveMap(scene);
	pGameInfo->MapScene = scene;

	crfieldChangePos(sx,sy,1);

	//---�C�x���g�ɍ��킹�ă}�b�v���e�ύX
	crfieldSetMapEvent(pGameInfo->MapNumber,scene);

/*	if(sx != -1){
		ef->xSet(sx);
		pGameInfo->FieldX = sx;
	}
	if(sy != -1){
		ef->ySet(sy);
		pGameInfo->FieldY = sy;
	}

	//---�f�t�H���g�Ńv���[���͂P
	crfieldChangePlane(1);*/
}

CRBASE_FIELDAPI void crfieldSetFadeRect(RECT *rect)
{
	if(rect != NULL){
		FadeRect = *rect;
		UseFadeRect = 1;
	} else {
		UseFadeRect = 0;
	}
}

CRBASE_FIELDAPI void crfieldChangeSceneS(int scene,int sx /*= -1*/,int sy /*= -1*/)
{
	if(!UseFadeRect)
		crefectScreenChange_FadeOut();
	else
		crefectScreenChange_FadeOut(&FadeRect);

	crfieldChangeScene(scene,sx,sy);
	crfieldDrawField(1);

	if(!UseFadeRect)
		crefectScreenChange_FadeIn();
	else
		crefectScreenChange_FadeIn(&FadeRect);
}

//---���W�؂�ւ�
CRBASE_FIELDAPI void crfieldChangePos(int sx,int sy,int plane /*= -1*/)
{
	if(sx != -1){
		ef->xSet(sx);
		pGameInfo->FieldX = sx;
	}
	if(sy != -1){
		ef->ySet(sy);
		pGameInfo->FieldY = sy;
	}

	if(plane != -1){
		crfieldChangePlane(plane);
	}

	//---�C�x���g����
	crfieldSetIgonoreEvent(1);
	//---�G�������Z�b�g
	crfieldCheckBattle(0);
}

CRBASE_FIELDAPI void crfieldChangePosS(int sx,int sy,int plane /*= -1*/)
{
	crfieldChangePos(sx,sy,plane);
}

CRBASE_FIELDAPI void crfieldChangePlane(int plane)
{
	ef->SetPlayerPlane(plane);
	pGameInfo->FieldPlane = plane;
}

//---------------------------------------------------------

//---�t�B�[���h�A�j���[�V����
CRBASE_FIELDAPI void crfieldDoAnime(int frame /*= 1*/)
{
	ef->AnimeMainCharacter(frame);
	em->DoObjectAnime(frame);
	em->DoPatternAnime(frame);
}

//---�t�B�[���h��`���ăE�F�C�g�����
CRBASE_FIELDAPI int crfieldDrawAndWait(void)
{
	static NextWait = 0;
	static eiTime MainFieldTime;
	int wait;
/*
	if(NextWait){
		//---�t�B�[���h�E�F�C�g���K�v�Ȃ�
		if(MainFieldTime.Get() <= NextWait){
			//---���t���b�V�����[�g��񕪂����҂�
//			eiSleep((100000 / eiSetDrawRefreshRate(-1)) / 100);
			wait = (int)(
				1000.0 / (double)eiSetDrawRefreshRate(-1)
				* (double)crsysGetFieldDrawRate() / 100.0
				);
			MainFieldTime.Wait2(wait);
			return 0;
		}
		NextWait = 0;
	}*/

	crfieldDoAnime();
	//---draw & wait
	if(crfieldDrawField()){
		if(NextWait){
			//---�t�B�[���h�E�F�C�g���K�v�Ȃ�
			if(MainFieldTime.Get() <= NextWait){
				//---���t���b�V�����[�g��񕪂����҂�
				wait = (int)(
					1000.0 / (double)eiSetDrawRefreshRate(-1)
					* (double)crsysGetFieldDrawRate() / 100.0
					);
				MainFieldTime.Wait2(wait);
			}
			NextWait = 0;
		}

		//---�t�B�[���h�E�F�C�g�擾
		NextWait = crfieldWaitField(0);
		MainFieldTime.Reset();
	}
	return 0;
}

//---�t�B�[���h�E�F�C�g
CRBASE_FIELDAPI int crfieldWaitField(int wait /*= 1*/)
{
	static int WaitTime = 0;
	
	WaitTime = ef->CalcRefreshRateAndWait() * (100000 / eiSetDrawRefreshRate(-1)) / 100;

/*	char s[80];
	sprintf(s,"%d %d : %d\n",WaitTime,eiSetDrawRefreshRate(-1),ef->CalcRefreshRateAndWait());
	eiDebugWriteFile(s);*/

	if(WaitTime >= 0){
		ew->Flip();
		if((ef->GetAutoChangeStatus() != 1
			|| !(ef->GetDrawRate() == 100 && eiGetFullScreen())
			|| crdataGetIniFile()->ForceRefreshRate != 0)
			/*&& /*WaitFlag &&*/
			/*!ei->MouseButton[0]*/){
			if(crsysNotQuick()){
				if(wait){
					et->Wait2(WaitTime);
				}
				return WaitTime;
			}
		}
	}

	return 0;
}

//---�t�B�[���h��`��
CRBASE_FIELDAPI int crfieldDrawField(int mode /*= 0 0:auto 1:force*/)
{
	static int KeepDrawRate = crsysGetFieldDrawRate();
	static int Count = 0,QuickFlag = 0;
	static int PrevDeltaX = 1,PrevDeltaY = 1;
	int DrawRate = crsysGetFieldDrawRate();
	int DrawMainCharacter = crsysGetDrawMainCharacter();// ���S�Ƀ��C���L�����N�^�[��`����

//	KeepDrawRate = crsysGetFieldDrawRate();

	if(crsysQuick()){//---�������ςɂȂ錴��
		//---�N�C�b�N����
		if(QuickFlag == 0){
			KeepDrawRate = crsysGetFieldDrawRate();
		}
		QuickFlag = 1;
		ef->SetDrawRate(1600);
		crdataGetSystem()->DrawRate = 1600;
	} else {
		if(QuickFlag == 1){
			ef->SetDrawRate(KeepDrawRate);
			crdataGetSystem()->DrawRate = KeepDrawRate;
			DrawRate = KeepDrawRate;
			Count = 0;
		}
		QuickFlag = 0;
	}

	Count += 100;

	//---�O�񓮂��Ă��āA���񓮂��Ă��Ȃ��������΂ɕ`�悷��
	//---��������΁A�P�}�X�������Ƃ��K���`�悳���
	if((PrevDeltaX && !ef->xGetDelta())
		|| (PrevDeltaY && !ef->yGetDelta()) ){
		mode = 1;
	}
	PrevDeltaX = ef->xGetDelta();
	PrevDeltaY = ef->yGetDelta();

	if(Count >= DrawRate || mode == 1){
		Count -= DrawRate;

crdataEnableRec(0);
		ef->Draw(em,mode);
crdataEnableRec(1);
		return 1;
	}

	return 0;
}

//---�t�B�[���h��`���ăE�F�C�g���Ƃ�
CRBASE_FIELDAPI void crfieldDrawFieldWait(int mode /*= 0 0:auto 1:force*/)
{
	crfieldDrawField(mode);
	crfieldWaitField();
}

//---��{�I�ȃt�B�[���h�X�N���[��
CRBASE_FIELDAPI int crfieldBasicDrawField(void)
{
	crfieldDoAnime();
	//---draw & wait
	if(crfieldDrawField())
		crfieldWaitField();

	return 0;
}

//---��ʂ��X�N���[��
CRBASE_FIELDAPI void crfieldMove(int sx /*= 0*/,int sy /*= 0*/,int speed /*= -1*/)
{
	ef->Move(em,1,sx,sy);
}

//-------------------------------------------
//---�S���܂Ƃ߂��\���֐�
CRBASE_FIELDAPI void crfieldMoveAll(int sx /*= 0*/,int sy /*= 0*/,int speed /*= -1*/)
{
	crfieldMove(sx,sy,speed);
	crfieldDrawAndWait();
}

//---�P�t���[�������S�ɕ`��
CRBASE_FIELDAPI void crfieldDrawFrame(void)
{
	crfieldDoAnime();
	crfieldDrawField(1);
	ew->Flip();
}

//---------------------------------------------------------
static eistr PushAndPopMainCharacter[_MAX_PATH];
static ei_s32 MainCharacterShowFlag = 1;

//---���C���L�����N�^�[��\�������邩�ǂ���
CRBASE_FIELDAPI void crfieldShowMainCharacter(int show)
{
	ef->SetMoveEnything(0);
	if(show == 0){
		ef->SetMoveEnything(1);
	}
	MainCharacterShowFlag = show;

	if(show == 0){
//		ef->SetMoveSpeed(oldSpeed);
	}
}

//---���C���L�����N�^�[�t�@�C����ۑ�
CRBASE_FIELDAPI void crfieldPushMainCharacter(void)
{
}

//---���C���L�����N�^�[�t�@�C���𕜌�
CRBASE_FIELDAPI void crfieldPopMainCharacter(void)
{
}

//---
CRBASE_FIELDAPI void crfieldSetMainCharacter(int number)
{
	static eistr *CharaNameTable[] = {"trans.acf","Lunarn.acf",
		"TwMin2m.acf","GroundShip.acf","GroundShipRise.acf",
		"Ship.acf","LunarnF.acf"};
	static int oldSpeed = 4;

	pGameInfo->MainCharacterNumber = number;

/*	if(pGameInfo->Event[177] == 1){
		if(number == 3){
			oldSpeed = ef->SetMoveSpeed(8);
		} else {
			ef->SetMoveSpeed(4);
		}
	}*/

	crfieldReadMainCharacter(CharaNameTable[number]);
}

CRBASE_FIELDAPI int crfieldSetMainCharacterSurface(void)
{
	eiCellSetSurface(pMainCharacterCell,
		CR_PTNSURFACE_MAINCHARACTER_X,CR_PTNSURFACE_MAINCHARACTER_Y,32,32,8);

	return 1;
}

//---���C���L�����N�^�[���[�h
CRBASE_FIELDAPI int crfieldReadMainCharacter(eistr *name /*= NULL*/)
{
	int c = 1;
	eistr temp[_MAX_PATH];

	if(name == NULL){
		//---�f�B�t�H���g
		sprintf(temp,"%sObj_Default.acf",CR_DATADIR2,name);
	} else {
		sprintf(temp,"%s%s",CR_DATADIR2,name);
	}
	c &= eiCellReadPattern(pMainCharacterCell,
		temp,CR_DATAFILE2,crdataGetFileMode()/*::CrFileMode*/,0,8,32,32);

	crfieldSetMainCharacterSurface();

	return c;
}

//---���C���L�����N�^�[�`��R�[���o�b�N
CRBASE_FIELDAPI void crfieldDrawMainCharacter(eiCell *lpCell,int dir,int x32,int y32,int cx,int cy)
{
	if(MainCharacterShowFlag){
		pMainCharacterCell[dir].PutTransClip(lpCell,x32,y32);
	}
}

//----------------------------------------
//---�I�u�W�F�N�g�̃|�C���^�[�𓾂�
CRBASE_FIELDAPI eiMapObject *crfieldGetObjectPointer(int Number)
{
	return em->GetObject(Number);
}

//---�I�u�W�F�N�g�̕������v���C���[�Ɍ�������
CRBASE_FIELDAPI void crfieldTurnToPlayer(eiMapObject *pObject)
{
	int sx = pObject->xGet() - ef->xGet(),
		sy = pObject->yGet() - ef->yGet();

	if(sx  < 0)
		pObject->SetDirection(DIR_EAST);
	if(sx > 0)
		pObject->SetDirection(DIR_WEST);
	if(sy < 0)
		pObject->SetDirection(DIR_SOUTH);
	if(sy > 0)
		pObject->SetDirection(DIR_NORTH);
}

#define AFTER_YUMI() (pGameInfo->Event[177] == 1)
#define AFTER_KOJINSAI() (pGameInfo->Event[230] == 1)

//---�t�B�[���h�I�u�W�F�N�g���Z�b�g
CRBASE_FIELDAPI void crfieldSetFieldObject(void)
{
	em->SetSurface();

	eiCellSetSurface(pMainCharacterCell,
		CR_PTNSURFACE_MAINCHARACTER_X,CR_PTNSURFACE_MAINCHARACTER_Y,32,32,8);

	//---�ǎ�
	pWallPaperCell->SetSurface();
}

//---�}�b�v�f�B�t�H���g�̃~���[�W�b�N�ɂ���
CRBASE_FIELDAPI void crfieldChangeMapMusic(int force /* = 0*/)
{
	if(crfieldGetMapNumber() == 22 && pGameInfo->Event[26] == 0){
		//---�h�[�O��
		crmusicPlay(CRMUSIC_SS);
	} else if(crfieldGetMapNumber() == 32 && (pGameInfo->Event[139] == 1 || pGameInfo->Event[139] == 2)){
		//---�N���X�t�B�[���h�����錾
//		crmusicStop();
		crmusicPlay(CRMUSIC_SILENT);
	} else if(crfieldGetMapNumber() == 32 && (pGameInfo->Event[66] == 1 || pGameInfo->Event[66] == 2)){
		//---�N���X�t�B�[���h�����Ւ��O
//		crmusicStop();
		crmusicPlay(CRMUSIC_SILENT);
	} else if(crfieldGetMapNumber() == 32 && (pGameInfo->Event[77] == 1)){
		//---��Q���X�^�[�g����N���X�t�B�[���h�h��
//		crmusicStop();
		crmusicPlay(CRMUSIC_SILENT);
	} else if(crfieldGetMapNumber() == 34 && crfieldGetMapScene() == 3){
		crmusicPlay(CRMUSIC_OPENING);
	} else if(crfieldGetMapNumber() == 59 && pGameInfo->Event[170] == 1 && pGameInfo->Event[171] == 0){
		//---�O���E���h�V�b�v�A�o�C�c
		crmusicPlay(CRMUSIC_FIELD1);
	} else if(crfieldGetMapNumber() == 64 && pGameInfo->Event[154] == 0){
		//---�c�[���A�A�G�^�[�i�������A�S���̒�
		crmusicPlay(CRMUSIC_SILENT);
	} else if(crfieldGetMapNumber() == 70 && crfieldGetMapScene() >= 10){
		//---�L���̈�ՁA�Ő[��
		crmusicPlay(CRMUSIC_CRAYSIVE);
	} else if(crfieldGetMapNumber() == 70 && crfieldGetMapScene() >= 8
		&& pGameInfo->Event[160] == 0 && pGameInfo->Event[166] == 1){
		//---�L���̈�ՁA�E�o
		crmusicPlay(CRMUSIC_HEAT);
	} else if(crfieldGetMapNumber() == 70 && crfieldGetMapScene() >= 8){
		//---�L���̈�ՁA�[���ꏊ
		crmusicPlay(CRMUSIC_SILENT);
/*	} else if(crfieldGetMapNumber() == 35
		&& pGameInfo->Event[166] == 1 && pGameInfo->Event[160] == 0){
		//---�ۑ����u�A�L���̒�
		crmusicPlay(CRMUSIC_SILENT);*/
	} else if(crfieldGetMapNumber() == 10 && pGameInfo->Event[EV_GS_NUMBER_STATUS] == 1){
		//---�f�r
		crmusicPlay(CRMUSIC_GS);
//---------------------------------------------
	} else if(crfieldGetMapNumber() == 26 && AFTER_KOJINSAI()){
		//---�t�F�C�}��
		crmusicPlay(CRMUSIC_SILENT);
	} else if(crfieldGetMapNumber() == 32 && AFTER_KOJINSAI()){
		//---�N���X�t�B�[���h
		crmusicPlay(CRMUSIC_SILENT);
	} else if(crfieldGetMapNumber() == 55 && AFTER_KOJINSAI()){
		//---�[�r�A�}�C��
		crmusicPlay(CRMUSIC_TOWN1);
	} else if(crfieldGetMapNumber() == 61 && AFTER_KOJINSAI()){
		//---�c�[���A
		crmusicPlay(CRMUSIC_TOWN1);
	} else if(crfieldGetMapNumber() == 64 && AFTER_KOJINSAI()){
		//---�G�^�[�i���A�c�[���A����
		crmusicPlay(CRMUSIC_SILENT);
	} else if(crfieldGetMapNumber() == 80 && 
		AFTER_KOJINSAI()){
		//---��_�a�A�~�_�Ռ�
		crmusicPlay(CRMUSIC_SILENT);
	} else if(crfieldGetMapNumber()
		&& pGameInfo->Event[217] == 1 && pGameInfo->Event[218] == 0){
		//---�����̈��
		crmusicPlay(CRMUSIC_DRAGONBREATH);
	} else {
		if(force)
			crmusicPlay(MapMusicTable[crfieldGetMapNumber()],1,CRMUSIC_LOADFORCE);
		else
			crmusicPlay(MapMusicTable[crfieldGetMapNumber()]);
	}
}

//--�G�Ƒ������邩�ǂ���
CRBASE_FIELDAPI int crfieldCheckBattle(int reset /* = 0*/)
{
	static WalkCount = 0;
	static prevX = 0,prevY = 0;
	int 
/*		FieldEncountProb[]   =  { 0, 2, 4, 6, 8,12,16,20,24,28,
								 32,36,40,44,46,48,52,56,58,60,
								 60,60,60,60,60,60,60,60,60,60},*/
		FieldEncountProb[]   =  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
								 10,11,12,13,14,15,16,17,18,19,
								 20,21,22,23,24,25,26,28,32,40},
/*		DangeonEncountProb1[] = { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
								  1, 1, 1, 1, 1, 2, 2, 2, 2, 2,
								  3, 3, 4, 4, 5, 6, 8,16,20,36},//---�ύX�O:40
								  */
		DangeonEncountProb1[] = { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
								  1, 1, 1, 1, 1, 2, 2, 2, 2, 2,
								  3, 3, 4, 4, 5, 6, 8,16,20,32},//---�ύX�O:40
		DangeonEncountProb2[] = { 0, 1, 1, 1, 1, 1, 2, 3, 4, 5,
								  6, 7, 8, 9,10,12,14,16,20,24},
		DangeonEncountProb3[] = { 0, 1, 1, 1, 1, 1, 2, 3, 4, 5,
								  6, 7, 8, 9,10,12,14,16,18,20},
		DangeonEncountProb4[] = { 0, 1, 1, 1, 1, 1, 2, 3, 4, 5,
								  6, 7, 8, 9,10,12,14,16,18,20},
		DangeonEncountProb5[] = { 0, 1, 1, 1, 1, 1, 2, 3, 4, 5,
								  6, 7, 8, 9,10,12,14,16,18,20},
		*Encount[] = {NULL,FieldEncountProb,
		DangeonEncountProb1,DangeonEncountProb2,
		DangeonEncountProb3,DangeonEncountProb4,
		DangeonEncountProb5
	};

	int type = em->GetEnemyType();
	int area = em->GetEnemyArea(ef->xGet(),ef->yGet());

	//---

	if(reset == 1){
		WalkCount = 0;
		return 0;
	}

	//---�c�[���A�A�G�^�[�i�������A�S�����̓o�g������
	if(crfieldGetMapNumber() == 64 && !pGameInfo->Event[155])
		return 0;
/*
	int a,b,enc = 0; 
	for(a = 0,enc = 0,b = 0;a < 10000;a ++,WalkCount = 0,b = 0){
		while(1){
			if(eiRnd(1000) < (Encount[type])[WalkCount]){
				//---�G���J�E���g�I�I
				enc += b;
				break;
			}
			b ++;
			if(++WalkCount >= 30)
				WalkCount = 29;
		}
	}
	char s[100];
	sprintf(s,"all:%d ,av:%f\n",enc,(double)enc / 10000);
	eiDebugWriteFile(s);
*/
	if(type && area
		&& (prevX != ef->xGet() || prevY != ef->yGet())
		&& ef->GetMoveDelta() >= 32){

		static hosu = 0;
		hosu ++;
/*		char s[100];
		sprintf(s,"a:%d  ,%d\n",ef->GetMoveDelta(),(Encount[type])[WalkCount]);	
		eiDebugWriteFile(s);*/
		if(eiRnd(1000) < (Encount[type])[WalkCount]){
			//---�G���J�E���g�I�I
//			sprintf(s,"hosu:%d\n",hosu);
//			eiDebugWriteFile(s);
//			char ss[1200];
//			sprintf(ss,"%d : %d",WalkCount,hosu);
//			eiMsgBox(ss);
			hosu = 0;

			WalkCount = 0;
			ef->SetMoveDelta(0);
			prevX = ef->xGet();
			prevY = ef->yGet();
			return 1;
		}
//	}
//	if(ef->GetMoveDelta() >= 32){
		//---���ȏ㓮������f���^�l�����Z�b�g
		ef->SetMoveDelta(0);

		if(++WalkCount >= 30)
			WalkCount = 29;

		prevX = ef->xGet();
		prevY = ef->yGet();
	}

	return 0;
}

//---�O���E���h�V�b�v�̈ʒu�ݒ�
CRBASE_FIELDAPI void crfieldSetGroundShipPos(void)
{
	int x,y,status = pGameInfo->Event[EV_GS_NUMBER_STATUS];
	eiMap map;
	eistr s[80];

	if(status == 0){
		//---����
		x = pGameInfo->Event[EV_GS_NUMBERX];
		y = pGameInfo->Event[EV_GS_NUMBERY];

		crfieldSetMainCharacter(1);

		sprintf(s,CR_DATADIR2"CrMap_010.map");
		map.Load(s,CR_DATAFILE2,crdataGetFileMode());
		memcpy(&em->Data.Pattern[0],&map.Data.Pattern[0],sizeof(map.Data.Pattern));
		map.Delete();
	} else {
		//---��荞�ݒ�
		x = 0;
		y = 0;
		crfieldSetMainCharacter(3);

		if(pGameInfo->Event[199] == 0){
			sprintf(s,CR_DATADIR2"GS1.map");
		} else {
			//---�C��\
			sprintf(s,CR_DATADIR2"GS2.map");
		}
		map.Load(s,CR_DATAFILE2,crdataGetFileMode());
		memcpy(&em->Data.Pattern[0],&map.Data.Pattern[0],sizeof(map.Data.Pattern));
		map.Delete();
	}

	//---�O���E���h�V�b�v�̏ꏊ
	eiMapObject *pObject = em->GetObject(NP_GS_NUMBER);
	pObject->SetPos(x,y,1);
	pObject->SetDirection(DIR_NORTH);

//	pObject = em->GetObject(NP_GS_EVNUMBER);
//	pObject->SetPos(x,y,1);
}
