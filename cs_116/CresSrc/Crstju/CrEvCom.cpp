/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrEvCom.cpp ...Event Command functions

-----------------------------------------------------------*/


#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CREVCOM

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#include "CrBase.h"
#include "CrEvCom.h"

//---game info
#define CR_GAMEINFO_EXTERNPOINTER
#include "CrGameInfo.h"

//---flag
CREVCOM_API ei_s32 evSet(ei_s32 number,ei_s32 flag)
{
	ei_s32 old = pGameInfo->Event[number];

	pGameInfo->Event[number] = flag;

	return old;
}

CREVCOM_API ei_s32 evGet(ei_s32 number)
{
	return pGameInfo->Event[number];
}

//---�I�u�W�F�N�g�t�@�C���ǂݍ���
CREVCOM_API int evReadObject(int number,eistr *name)
{
	eistr s[80];

	sprintf(s,CR_DATADIR2"%s",name);
	return em->ReadObject(s,CR_DATAFILE2,crdataGetFileMode(),number);
}

//---field
CREVCOM_API void evField(int wait_flag /* = 1*/,int force /*= 0*/)
{
	if(crfieldDrawField(force)){
		//---��ʂ��X�V���ꂽ��t���b�v
		ew->Flip();
	}
}

CREVCOM_API void evFieldNoFlip(int wait_flag /* = 1*/,int force /*= 0*/)
{
	if(crfieldDrawField(force)){
	}
}

CREVCOM_API void evFrame(int frame /*= 1*/,int wait_mode /*= 0x03*/)
{
	int a,b,flag,first = 1;
	LPMAP_DATA lpmap = em->Data.Map[em->GetActiveMap()];

//	ef->CalcRefreshRateAndWait(1);
	for(a = 0,flag = 1;a < frame;a ++,flag = 1){
		if(crsysQuick())
			break;

		while(flag){
			flag = 0;
			ef->Move(em,0);
			ef->MoveObject(em,1,0,0);

			if(wait_mode & 0x01){
				if(!(ef->Field.xDelta == 0 && ef->Field.yDelta == 0)){
					flag ++;
				}
			}
			if(wait_mode & 0x02){
				for(b = 0;b < EF_OBJECT_MAX;b ++){
					if(lpmap->lpObject[b].GetFlag()){
						if(!(lpmap->lpObject[b].Data.xDelta == 0 && lpmap->lpObject[b].Data.yDelta == 0)){
							flag ++;
						}
					}
				}
			}
			if(first){
				crfieldDoAnime();
				crfieldDrawField(1);
				ew->Flip();
			} else {
				if(crsysNotQuick()){
					crfieldDrawAndWait();
				}
			}
			first = 0;
		}
	}
}

//---wait
static eiTime evWaitTime;

CREVCOM_API void evReset(void)
{
	evWaitTime.Reset();
}

CREVCOM_API void evFrameWait(int wait,int now_start /*= 1*/)
{
	if(now_start){
		evReset();
	}
	if(crsysNotQuick()){
		while(evWaitTime.Get() < wait){
			ef->Move(em,0);
			ef->MoveObject(em,1,0,0);
			crfieldDrawAndWait();

			if(crsysQuick())
				break;
		}
	}
	evReset();
}

CREVCOM_API void evWait(int wait,int now_start /*= 0*/)
{
	if(now_start){
		evReset();
	}
	if(crsysNotQuick()){
		evWaitTime.Wait2(wait);
	}
	evReset();
}

CREVCOM_API void evDrawWait(int wait,int now_start /*= 0*/)
{
	if(now_start){
		evReset();
	}
	evFrame(1);
	if(crsysNotQuick()){
		evWait(wait);
	}
	evReset();
}

CREVCOM_API void evFadeOut(int run_time /* = 250*/,int color /*=-1*/)
{
	if(color == -1)
		color = RGB_MAKE(0,0,0);

	RECT rect = {
		32 + ef->Field.xTop,
		32 + ef->Field.yTop,
		32 + ef->Field.xTop + ef->Field.xSize * ef->Field.PatternSize,
		32 + ef->Field.yTop + ef->Field.ySize * ef->Field.PatternSize
	};

	crefectScreenChange_FadeOut(&rect,-1,run_time,color);
}

CREVCOM_API void evFadeIn(int run_time /* = 250 */,int color /*=-1*/)
{
	if(color == -1)
		color = RGB_MAKE(0,0,0);

	RECT rect = {
		32 + ef->Field.xTop,
		32 + ef->Field.yTop,
		32 + ef->Field.xTop + ef->Field.xSize * ef->Field.PatternSize ,
		32 + ef->Field.yTop + ef->Field.ySize * ef->Field.PatternSize 
	};

	crefectScreenChange_FadeIn(&rect,-1,run_time,color);
}

CREVCOM_API void evFill(int color)
{
	int
		left = 32 + ef->Field.xTop,
		top = 32 + ef->Field.yTop,
		right = left + ef->Field.xSize * ef->Field.PatternSize - 1,
		bottom = top + ef->Field.ySize * ef->Field.PatternSize - 1;

	ew->lpCell[1]->DrawFillBox(left,top,right,bottom,color);
}

CREVCOM_API void evMap(int map,int scene,int x,int y)
{
	crfieldChangeMap(map,scene);
	crfieldChangeSceneS(scene,x,y);
}

CREVCOM_API void evScene(int scene,int x,int y)
{
	crfieldChangeSceneS(scene,x,y);
}

CREVCOM_API int evReloadMap(int music)
{
	return crfieldChangeMap(crfieldGetMapNumber(),crfieldGetMapScene(),1,music);
}

CREVCOM_API void evReloadMapMusic(void)
{
	crfieldChangeMapMusic(1);
}

//---�_���W�����E�o�|�C���g
CREVCOM_API void evSetGatePoint(int x,int y,int dir,int map /*= 10*/,int scene /*= 0*/)
{
}

//---�^�C�}�[
static eiTime evtimer;

CREVCOM_API void evStartTimer(void)
{
	evtimer.Reset();
}

CREVCOM_API int evGetTimer(void)
{
	return evtimer.Get();
}

//---MainCharacter
CREVCOM_API void mcDir(int dir)
{
	ef->SetDirection(dir);
}

CREVCOM_API int mcSpeed(int speed)
{
	return ef->SetMoveSpeed(speed);
}

CREVCOM_API void mcMove(int sx,int sy,int dir /*= 1*/)
{
	int d = ef->GetDirection();

	crfieldMove(sx,sy);

	if(dir == 0){
		//---�����L�[�v
		ef->SetDirection(d);
	}
}

CREVCOM_API void mcShow(int show)
{
	crfieldShowMainCharacter(show);
}

extern int crmainCheckAutoEvent(int reset = 0);
CREVCOM_API void mcResetEvent(void)
{
	crmainCheckAutoEvent(1);
}

//---NP
CREVCOM_API eiMapObject *npGet(int np)
{
	return em->GetObject(np);
}

CREVCOM_API void npDir(int np,int dir)
{
	eiMapObject *pObject = em->GetObject(np);
	
	if(pObject != NULL)
		pObject->SetDirection(dir);
}

CREVCOM_API void npMove(int np,int sx,int sy,int dir /*= 1*/)
{
	eiMapObject *pObject = em->GetObject(np);
	
	if(pObject != NULL)
		pObject->MoveDelta(sx,sy);

	if(dir){
		if(sx == 1){
			npDir(np,EAST);
		} else if(sx == -1){
			npDir(np,WEST);
		} else if(sy == 1){
			npDir(np,SOUTH);
		} else if(sy == -1){
			npDir(np,NORTH);
		}
	}
}

CREVCOM_API void npPos(int np,int sx,int sy,int plane /*= -1*/)
{
	eiMapObject *pObject = em->GetObject(np);
	
	if(pObject != NULL)
		pObject->SetPos(sx,sy,plane);
}

CREVCOM_API void npShow(int np,int show)
{
	if(show == 0){
		npDir(np,DIR_TRANS);
	} else {
		npDir(np,DIR_SOUTH);
	}
}

//---�U������I
CREVCOM_API void npTurn(int np)
{
	eiMapObject *pObject = em->GetObject(np);
	
	if(pObject != NULL){
		pObject->SaveDir();
		crfieldTurnToPlayer(pObject);
	}
}

CREVCOM_API void npReturn(int np)
{
	eiMapObject *pObject = em->GetObject(np);
	
	if(pObject != NULL){
		pObject->RestoreDir();
	}
}

//---�����������Ȃ��悤�ɃZ�b�g
CREVCOM_API void npDelete(int np)
{
	eiMapObject *pObject = em->GetObject(np);
	
	if(pObject != NULL){
		npPos(np,0,0);
		npShow(np,0);

		pObject->Data.Status &= (~EF_OBJECT_ST_MOVERANDOM);
		pObject->Data.Status |= EF_OBJECT_ST_MOVEFIXED;
	}
}

//---�p�[�e�B�[��
CREVCOM_API void prtRecovery(int member)
{
	CrCharacter *pChara = crcharaGetPartyMember(member);

	if(pChara != NULL){
		pChara->SetLP(pChara->GetMaxLP());
		pChara->SetMC(pChara->GetMaxMC());
	}
}

//---�p�[�e�B�[�S����
CREVCOM_API void prtRecoveryAll(void)
{
	int a;

	for(a = 0;a < MEMBER_MAX;a ++){
		prtRecovery(a);
	}
}

CREVCOM_API void evKaifukunoIzumi(void)
{
	CrMesManager mes;

	evField(0,1);
	mes.FileMessage("EventMessage.msg",1);
	prtRecoveryAll();
}

//-----------------------------------------------------------------
//---��
CREVCOM_API int itemBox(int event,int item,int ev_obj)
{
	if(!evGet(event)){
		npDir(ev_obj,EAST);
		evField(0,1);
		itemGet(item,0);
		evSet(event,1);
		critemAddItem(item,1);
//		crbaseYarikomi_Takarabako();
		return item;
	}
	return 0;
}

//---�^���X
CREVCOM_API int itemTansu(int event,int item)
{
	if(event == 0 || evGet(event) == 0){
		//---���������肩�A�C�x���g�t���O���Ȃ��Ȃ�
		itemGet(item,1);
		evSet(event,1);
		critemAddItem(item,1);
//		crbaseYarikomi_Tansu();

		return item;
	}
	return 0;
}

//---�{�I
CREVCOM_API int itemHondana(int event,int item)
{
	if(!evGet(event)){
		itemGet(item,1);
		evSet(event,1);
		critemAddItem(item,1);
//		crbaseYarikomi_Hondana();

		return item;
	}
	return 0;
}

//---�Ȃɂ�����ɓ��ꂽ
CREVCOM_API void itemGet(int item,int mestype /*= 0*/)
{
	CrItem *pItem = critemGetItemClass(item);
	CrMesManager mes;
	char str[80];
	char *typestr[] = {"��ɓ��ꂽ","������"};

	if(pItem != NULL){
		mes.CreateNewMessage();
		sprintf(str,"%s ��%s\\c;",pItem->GetName(),typestr[mestype]);
		mes.Message(str);
		mes.Draw();
		mes.CloseMessage();
	}
}

//-------------------------------------------------
//---�h��
CREVCOM_API int evYado(int money,int map /*= 0*/,int scene /*= 0*/,int (*evCallBack)(void) /*= NULL*/,int mode /*= 0*/)
{
	CrMesManager mes;
	eistr s[128];
	int ret,fadein = 1;
	CrSelectWindow win;

	mes.CreateNewMessage();
	sprintf(s,"���u��������Ⴂ�܂��I@n;�@��� %d�t�@���ƂȂ�܂��B@n;�@���܂�܂����H�v@c;",money);
	mes.Message(s);
	mes.Draw();

	evFieldNoFlip(0,1);

	crbaseMenuReset();
	sprintf(s,"�ꔑ %d�t�@��",money);
	win.Create(96,72,10,5,s,"���܂�;��߂�;");
	crbaseShowMoney(272,72);
	ew->Refresh();
	crbaseMenuStart();

	ret = win.Select();

	crbaseMenuReset();
	crbaseMenuStart();

	if(ret == 0){
		if(crbaseGetMoney() < money){
			//---��������
			mes.Message("���u�܂��Ƃɐ\���󂠂�܂��񂪁A����������Ȃ��݂����ł���B�܂����Ă��������ˁB�v@c;");
			mes.Draw();
			ret = 1;
		} else {
			//---���܂���!
			crbaseAddMoney(-money);
			if(mode == 1)
				return ret;

			prtRecoveryAll();
			crefectScreenChange_FadeOut(NULL,0,250);

			//---�C�x���g�`�F�b�N
			if(map == 16 && scene == 0){
				if(evGet(17) == 1){
					fadein = (*evCallBack)();
				}
			} else if(map == 32 && scene == 0){
				if(evGet(65) == 1){
					fadein = (*evCallBack)();
				}
			}

			if(fadein){
				evFieldNoFlip(0,1);
				crefectScreenChange_FadeIn(NULL,0,250);
			}
		}
	} else {
		ret = 1;
	}
	mes.CloseMessage();

	return ret;
}


//---���E�n�}�\��
CREVCOM_API void evShowWorldMap(int x,int y,int symbol /* = 0*/,int citygide /*= 0*/)
{
	eiCell WorldMapCell,batu;
	int a,b,ox = 120,oy = 40,ptn = 0,first = 1,flag;
	CrInput ci;

	int city_cur = -1,max_city,sx,sy,nearest,dist;
	eiTime let;
	CrStringWindow win;
	eistr *citystr[] = 
	{
		"�E�F�X�J",
		"�Z�[�l",
		"�A�l�[�g",
		"�h�[�O��",
		"�t�F�C�}��",
		"�N���X�t�B�[���h",

		"�g���C�A",
		"�m�[�X�e���A",
		"�_�C",
		"�}�[�N�X",

		"�A���V�A",
		"�[�r�A�}�C��",
		"�c�[���A",

		"�o�C�c",
		"�V���o�[�X�^�[",
		"���[���N���C��"

	};
	int citypos[] = {
160,153,
104,177,
146,229,
127,250,
184,220,
235,194,

236,159,
202,94,
245,110,
163,71,

190,57,
293,69,
330,231,

33,119,
59,175,
80,316,
-1,-1
	};

	int movepos[] = {
160,154,
104,178,
146,230,
127,251,
184,221,
235,195,

236,160,
202,95,
245,111,
163,72,

191,57,
293,76,
330,233,

33,120,
62,175,
80,317,
-1,-1
	};

	for(a = 0,max_city = 0;citypos[a * 2] != -1;a ++,max_city ++){
	}
	if(evGet(199) == 0){
		//---凋C�O�̓��N���A�O���[���N���C���ɂ܂������Ȃ�
		citypos[(max_city - 1) * 2] = -1;
		citypos[(max_city - 1) * 2 + 1] = -1;
		max_city --;
	}
	//---��ԋ߂��������߂�
	for(a = 0,nearest = 0,dist = 9999999;citypos[a * 2] != -1;a ++){
		b = (x - citypos[a * 2]) * (x - citypos[a * 2])
			+ (y - citypos[a * 2 + 1]) * (y - citypos[a * 2 + 1]);
		if(b < dist){
			//---�������̕����߂��I
			nearest = a;
			dist = b;
		}
	}

	crbaseMenuReset();
	WorldMapCell.ReadFile(CR_DATADIR1"WorldMapL.acf",CR_DATAFILE1,
		crdataGetFileMode());

	batu.ReadFile(CR_DATADIR1"batu.acf",CR_DATAFILE1,
		crdataGetFileMode());

	evField(0,1);
	for(a = 0;a < 2;a ++){
		WorldMapCell.Put(ew->lpCell[1],ox,oy);
		ew->Flip();
	}
	crbaseMenuStart();

	et->Reset();
	let.Reset();
	ci.Get();
	flag = 1;
	while(flag){
		ci.Get();
		if(ei->AnyKey && citygide == 0){
			flag = 0;
		} else if(citygide){
/*			if(ci.IsButton(0) || ci.IsButton(2)
				|| ei->Input[0].Button[0] || ei->Input[0].Button[2]){
				flag = 0;
			}*/
			if(ci.IsButton(0)){// || ei->Input[0].Button[0]){
				flag = 0;
			} else if(ci.IsButton(2)){
				//---�����ꗗ
				CrStringWindow win;
				win.Create(224,64,12,21);
				for(a = 0;a < max_city;a ++){
					win.DrawText(citystr[a]);
					win.AddReturn();
				}
				win.Refresh();

				crbaseMenuReset();
				crbaseMenuStart();

				ci.WaitAnykey();

				crbaseMenuReset();
				crbaseMenuStart();

				ci.Get();
			} else if(ci.IsButton(1)){// || ei->Input[0].Button[1]){
				//---�ړ�
				if(city_cur != -1){
					if(crbaseSelectYesNo("�ړ����܂����H",128,64) == 0){
						crsoundPlay(CRSOUND_GS_SOUND);
						evFrameWait(500);
						mcDir(EAST);
						evScene(0,movepos[city_cur * 2],movepos[city_cur * 2 + 1]);
						break;
					}
					crbaseMenuReset();
					crbaseMenuStart();
					flag = 1;
				} else {
					flag = 0;
				}
			}

			if(ci.IsUp() || ci.IsLeft()){
				if(city_cur == -1){
					city_cur = nearest;
				} else if(-- city_cur < 0){
					city_cur = max_city - 1;
				}
			}
			if(ci.IsDown() || ci.IsRight()){
				if(city_cur == -1){
					city_cur = nearest;
				} else if(++ city_cur >= max_city){
					city_cur = 0;
				}
			}
		}

		if(et->Get() > 500){
			ptn = (ptn + 1) & 0x01;
			et->Reset();
		}
		WorldMapCell.Put(ew->lpCell[1],ox,oy);
		if(symbol == 0){
			pMainCharacterCell[4 + ptn].PutExtend(
				ew->lpCell[1],
				ox + x - 8,  oy + y - 8,
				0.5,0.5,EI_PSET);
		} else if(symbol == 1){
			batu.PutClip(
				ew->lpCell[1],
				ox + x - 8,  oy + y - 8);
		}

		if(citygide){
			//---���̈ʒu�\��
			int col,size = 1;
			col = let.Get() % (1024);
			if(col >= 512)
				col = 1023 - col;
			col /= 2;

			for(a = 0;citypos[a * 2] != -1;a ++){
				size = 1;
				if(city_cur == a){
					size = 3;

					ew->lpCell[1]->DrawFillBox(
						citypos[a * 2] - size + ox,citypos[a * 2 + 1] - size + oy,
						citypos[a * 2] + size + ox,citypos[a * 2 + 1] + size + oy,
						ep->MakeRGB(0,0,0));
					ew->lpCell[1]->DrawFillBox(
						citypos[a * 2] - size + ox + 1,citypos[a * 2 + 1] - size + oy + 1,
						citypos[a * 2] + size + ox - 1,citypos[a * 2 + 1] + size + oy - 1,
						ep->MakeRGB(col,col,col));
				} else {
					ew->lpCell[1]->DrawFillBox(
						citypos[a * 2] - size + ox,citypos[a * 2 + 1] - size + oy,
						citypos[a * 2] + size + ox,citypos[a * 2 + 1] + size + oy,
						ep->MakeRGB(col,col,col));
				}
			}
			//---�����\��
			if(city_cur != -1){
				int length = strlen(citystr[city_cur]);

				length = length / 2 + 2;

				sx = citypos[city_cur * 2];
				sy = citypos[city_cur * 2 + 1];
				if(sy < 330){
					sy += 8;
				} else {
					sy -= 40;
				}
				sx -= 8;
				if(sx + length * 16 > 390){
					sx = 390 - length * 16;
				}
				win.Create(sx + ox,sy + oy ,length,2);
				win.Paint();
				win.Reset();
				win.DrawText(citystr[city_cur]);
			}
		}

		ew->Flip();
		if(first && symbol == 1){
			eiSleep(500);
			ci.Get();
		}
		eiSleep(1);
		first = 0;
	}
	
	crbaseMenuReset();
	crbaseMenuStart();

	batu.Release();
	WorldMapCell.Release();
}


//---�O���E���h�V�b�v�����֐؂芷��
CREVCOM_API void evChangeToGroundShipScene(void)
{
	int status = evGet(EV_GS_SCENE_STATUS);

	if(status == 0){
		//---������
		//---�ʒu�ۑ�
		evSet(EV_GS_SCENE_KEEPX,ef->xGet());
		evSet(EV_GS_SCENE_KEEPY,ef->yGet());
		evSet(EV_GS_NUMBER_STATUS,0);

		mcDir(SOUTH);
		crfieldSetMainCharacter(1);
		evMap(59,1,5,5);

		evSet(EV_GS_SCENE_STATUS,1);
	} else {
		evSet(EV_GS_NUMBER_STATUS,1);

		mcDir(EAST);
		crfieldSetMainCharacter(3);
		evMap(10,0,evGet(EV_GS_SCENE_KEEPX),evGet(EV_GS_SCENE_KEEPY));

		evSet(EV_GS_SCENE_STATUS,0);
	}
}

//---�O���E���h�V�b�v�ւ̏��~��
CREVCOM_API void evChangeGroundShip(void)
{
	int a,status = evGet(EV_GS_NUMBER_STATUS);
	CrMesManager mes;

	ei->Get();

	if(status == 0){
		//---��荞��
		status = 1;
		evSet(EV_GS_NUMBER_STATUS,status);
		evFrameWait(100);
		crfieldSetGroundShipPos();

		crfieldSetMainCharacter(4);
		crmusicPlay(CRMUSIC_GS);
		for(a = 0;a < 4;a ++){
			mcDir(a);
			evFrameWait(150);
		}
		mcDir(EAST);
		crfieldSetMainCharacter(3);

		evFrameWait(250);
	} else {
		int ob = ef->IsThereObject(em,ef->xGet(),ef->yGet());
		eiMap map;
		eistr s[80];

		sprintf(s,CR_DATADIR2"CrMap_010.map");
		map.Load(s,CR_DATAFILE2,crdataGetFileMode());
		int ptn = em->Get(ef->xGet(),ef->yGet(),1);

		//---�I�u�W�F�N�g�����邩�A�����Ȃ��ꏊ�Ȃ�
		if(ob == -1 && (map.Data.Pattern[ptn].Status & EF_PATTERN_ST_WALK)){
			//---�~�����ꏊ�Ȃ�
			status = 0;
			evSet(EV_GS_NUMBERX,ef->xGet());
			evSet(EV_GS_NUMBERY,ef->yGet());
			evSet(EV_GS_NUMBER_STATUS,status);

			evFrameWait(100);
			crfieldSetMainCharacter(4);
			for(a = 3;a >= 0;a --){
				mcDir(a);
				evFrameWait(150);
			}
			mcDir(SOUTH);
			crmusicPlay(CRMUSIC_FIELD1);

			crfieldSetGroundShipPos();

			evFrameWait(250);
		} else {
			evField(0,1);
			mes.FileMessage("Field.msg",102);
			evField(0,1);
		}

		map.Delete();
	}

	ei->Get();
}

//---��ʂ�h�炷
CREVCOM_API void evShake(int run_time,int delta /* = 16*/)
{
	int interval = 50;
	eiTime let,let2;
	eiDDSurface *pSurface = eiGetSurfacePointer();
	RECT rect = {
		32 + ef->Field.xTop,
		32 + ef->Field.yTop,
		32 + ef->Field.xTop + ef->Field.xSize * ef->Field.PatternSize ,
		32 + ef->Field.yTop + ef->Field.ySize * ef->Field.PatternSize 
	};
	RECT rect2 = {0,0,640,480};
	int x,y;

	let.Reset();

	while(let.Get() < run_time){
		let2.Reset();

		evFieldNoFlip();

		x = (eiRnd(delta) - (delta / 2)) + 32 + ef->Field.xTop;
		y = (eiRnd(delta) - (delta / 2)) + 32 + ef->Field.yTop;
		pSurface[4].DrawFillBox(0,0,639,479,0);
		pSurface[1].Put(&pSurface[4],x,y,&rect);
		pSurface[4].Put(&pSurface[1],0,0,&rect2);

		ew->Flip();

		let2.Wait2(interval);
	}
	evField(0,1);
}
