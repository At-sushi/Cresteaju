#define EI_FIELD

#include "eiDef.h"
#include "eiClass.h"

#ifndef EILIBRARY_DLL
	#include "eiLib.h"
#endif

#include "eiFldDef.h"

eiWindow *fw;
eiPalette *fp;
eiTime *ft;
eiInput *fi;

eiCell *fCell,cMapWindow[32],*fObjectPattern,*lpFPPattern,*fDebugCell;

static int eiFieldAsciiTable[128];
static eiCell eiFieldAsciiCell[128];
static efDebugMode = 0;

//---������
EI_API int eiFieldInit(eiWindow *ew,eiPalette *ep,eiInput *ei,
					   eiTime *et,eiCell *ec,eiCell *ed)
{
	fw = ew;
	fp = ep;
	fi = ei;
	ft = et;
	fCell = ec;
	fDebugCell = ed;
	fObjectPattern = (fCell + EF_OBJECT_PATTERNOFFSET);

	return 1;
}

EI_API int eiFieldInitAscii(int y,int col,int page)
{
	int a,b,x;
	EISTR s[2] = {0,0};
	eiDDSurface *lpSurface = eiGetSurfacePointer();
	RECT rect;

	for(x = 0,a = 0;x < 128;x ++){
		b = 0;
		eiFieldAsciiCell[x].Create(8,16);
		if(x <= 31){
			eiFieldAsciiTable[x] = ' ';
		} else if(x <= 57){
			eiFieldAsciiTable[x] = a;
			s[0] = (EISTR)x;
			b = 1;
		} else if(x <= 64){
			eiFieldAsciiTable[x] = ' ';
		} else if(x <= 90){
			eiFieldAsciiTable[x] = a;
			s[0] = (EISTR)x;
			b = 1;
		} else if(x <= 96){
			eiFieldAsciiTable[x] = ' ';
		} else if(x <= 122){
			eiFieldAsciiTable[x] = a;
			s[0] = (EISTR)x;
			b = 1;
		}

		if(b == 1){
			rect.left = a * 8;
			rect.top = y;
			rect.right = 8 + a * 8;
			rect.bottom = 16 + y;
			eiFieldAsciiCell[x].SetSurface(&rect,page);
			eiFieldAsciiCell[x].DrawFillBox(0,0,7,15,fp->ToRGB(16));
			eiFieldAsciiCell[x].DrawText(s,0,0,col,EI_TRANS);
			a ++;
		}
	}

	return 1;
}

EI_API void eiFieldDrawText(eiCell *lpCell,EISTR *string,int sx,int sy,int mode = EI_TRANS)
{
	int a,x,length = strlen(string);
	EISTR s[2] = {0,0};
	eiDDSurface *lpSurface = eiGetSurfacePointer();

	for(x = 0;x < length;x ++,string ++){
		a = *string;
		a = a & 0x7f;
		if(mode == EI_TRANS)
			eiFieldAsciiCell[a].PutTransClip(lpCell,sx + x * 8,sy);
		else
			eiFieldAsciiCell[a].PutClip(lpCell,sx + x * 8,sy);
	}
}

//---���ʊ֐�

//---�L�����N�^�[�������Ă�������̍��W
EI_API int xGetForward(int x,int direction)
{
	if(direction == 1)
		x ++;
	if(direction == 3)
		x --;

	return x;
}

EI_API int yGetForward(int y,int direction)
{
	if(direction == 0)
		y --;
	if(direction == 2)
		y ++;

	return y;
}

#include "eiFldObj.cpp"
#include "eiFldMap.cpp"

//--------------------------------------------------
//--------------------------------------------------
//--------------------------------------------------

//--------------------------------------------------
//--------------------------------------------------
//--------------------------------------------------

//---������
eiField::eiField(void)
{
	eimemset(&Field,0,sizeof(Field));

	Field.x = 0;
	Field.y = 0;
	Field.xDelta = Field.yDelta = 0;
	Field.MoveSpeed = 4;

	Field.xSize = 15;
	Field.ySize = 13;
	Field.xTop = Field.yTop = 0;
	Field.PatternSize = 32;
	Field.Zoom = 100;// = 100%
	Field.ChangeRefresh = 1;
	Field.Debug = 0;

	SetDrawMode(EF_DRAW_AUTOCHANGE);
	SetDrawRate(100);

//	MainCharacterCallback = NULL;
	SetMoveEnything(1);
	SetMainCharacterCallback(NULL);
	SetMainCharacter(1);
	SetBGCallback(NULL);
	SetFGCallback(NULL);
	SetMarginOfErrorFPS(100);

	SetPlayerMove(1);
	SetPlayerPlane(EF_STDMAP);
}

int eiField::SetDebugMode(int mode)
{
	::efDebugMode = Field.Debug = mode;

	return 0;
}

//---�ړ��s�n����ʉ߂ł��邩
void eiField::SetMoveEnything(int mode /*= 1*/)
{
	MoveEnything = mode;
}

int eiField::GetMoveEnything(void)
{
	return MoveEnything;
}

//---�v���C���[�̑��싖�ݒ�
int eiField::SetPlayerMove(int mode)
{
	int old = Field.EnablePlayerMoveingFlag;

	Field.EnablePlayerMoveingFlag = mode;

	return old;
}

int eiField::GetPlayerMove(void)
{
	return Field.EnablePlayerMoveingFlag;
}

//---�v���C���[�v���[���̐ݒ�
int eiField::SetPlayerPlane(int plane)
{
	int old = GetPlayerPlane();

	Field.PlayerPlane = plane;

	return old;
}

int eiField::GetPlayerPlane(void)
{
	return Field.PlayerPlane;
}

//---�E�B���h�E�ǂݍ���
int eiField::ReadWindow(EISTR *name,EISTR *slname,int mode)
{
/*	int a;

	a = eiCellReadPattern(&cMapWindow[0],
		name,slname,mode,
		0,8,32,32);
	if(!a)
		return 0;
	//�T�[�t�F�C�X�ɃR�s�[
	eiCellSetSurface(&cMapWindow[0],
		0,480 - 48,
		32,32,8);*/
	return 1;
}

ei_u32 eiField::SeekEfectPattern(eiMap *lpeimap,int start_plane,int end_plane,int x,int y)
{
	ei_u32 status = 0;
	int plane;

	//---�S�Ẵv���[���𒲂ׂĉe���̂���p�^�[����T��
	for(plane = start_plane;plane <= end_plane;plane ++){
		if(lpeimap->IsUsedPlane(lpeimap->Data.ActiveMap,plane)){
			status |= ( (lpeimap->GetPatternStatus(lpeimap->Get(x,y,plane))) & 0xff00);
/*			if((lpeimap->GetPatternStatus(lpeimap->Get(x,y,plane)) & EF_PATTERN_ST_UNDERNOWALK)){
				//---�ړ��s�}�b�v
				return 1;
			}*/
		}
	}

	return status;
}

//---x,y�Ƀv���C���[�������邩
int eiField::CanPlayerMove(eiMap *lpeimap,int x,int y)
{
	int plane = GetPlayerPlane();//---���݂���v���[��
	eiMapObject *lpobject = &lpeimap->Data.Map[lpeimap->Data.ActiveMap]->lpObject[0];
	int ob = IsThereObject(lpeimap,x,y);

	if(ob != -1){
		if(GetOverObject()){
			//---�I�u�W�F�N�g�z���s��
			return 0;
		}
		//---NP�ƏՓ�
		if(lpobject[ob].GetPlane() == plane 
			&& !(lpobject[ob].GetStatus() & EF_OBJECT_ST_RELCANOVER)){
			//---��ɂ̂�Ȃ��I�u�W�F�N�g��������
/*			char s[80];
			sprintf(s,"%d",ob);
			eiMsgBox(s);*/
			return 0;
		}
	}

	//---���݂̃v���[���𒲂ׂ�
	if(!(lpeimap->GetPatternStatus(lpeimap->Get(x,y,plane)) & EF_PATTERN_ST_WALK)){
		//---�ړ��s�}�b�v
		return 0;
	}
	if(SeekEfectPattern(lpeimap,plane + 1,plane + 1,x,y) & EF_PATTERN_ST_UNDERNOWALK){
		return 0;
	}

/*	//---�S�Ẵv���[���𒲂ׂĉe���̂���p�^�[����T��
	for(plane = EF_STDMAP + 1;plane < EF_PLANE_MAX;plane ++){
		if(lpeimap->IsUsedPlane(lpeimap->Data.ActiveMap,plane)){
			if((lpeimap->GetPatternStatus(lpeimap->Get(x,y,plane)) & EF_PATTERN_ST_UNDERNOWALK)){
				//---�ړ��s�}�b�v
				return 0;
			}
		}
	}*/

	return 1;
}

//---x,y�ɃI�u�W�F�N�g�����邩�ǂ���
int eiField::IsThereObject(eiMap *lpeimap,int x,int y,int object_number /*= -1*/)
{
	int a,plane,this_obj;
	eiMapObject *lpobject = &lpeimap->Data.Map[lpeimap->Data.ActiveMap]->lpObject[0];

	if(object_number == -1){
		plane = GetPlayerPlane();
	} else {
		plane = lpobject[object_number].GetPlane();
	}

	for(a = 0;a < lpeimap->GetMaxObjectIndex()/*EF_OBJECT_MAX*/;a ++){

		this_obj = lpeimap->ObjectIndex[a];
		if(this_obj == -1 || this_obj == object_number)
			continue;

		if((lpobject + this_obj) != NULL){
			if(lpobject[this_obj].Data.x == x && lpobject[this_obj].Data.y == y
				&& lpobject[this_obj].Data.Plane == plane)
				return this_obj;
		}
	}

	return -1;
}

//---�t�B�[���h�ړ�
int eiField::Move(eiMap *lpeimap,int key /*= 1*/,int fx /* = 0*/,int fy /* = 0*/)
{
	LPPLANE_DATA lpplane = &lpeimap->Data.Map[lpeimap->Data.ActiveMap]->Plane[EF_STDMAP];

	int sx = Field.x , sy = Field.y ,
		dx = 0,dy = 0 ,ax = 0,ay = 0, ex = 0,ey = 0;
	int speed = GetMoveSpeed(),flag = 0;
	static int Count = 0;
	static int LastLeft = 0,LastRight = 0,LastUp = 0,LastDown = 0;
	static int PrevLeft = 0,PrevRight = 0,PrevUp = 0,PrevDown = 0;

	//---���t���b�V�����[�g���I�ύX�J�E���^
	if(Field.RestCount){
		if(--Field.RestCount <= 0)
			//---�ύX���Ԃ��߂����烊�t���b�V�����[�g�����ɖ߂�
			Field.ChangeRefresh = 1;
	}

	//�����ړ����łȂ�������
	if((!Field.Move || fx || fy) && key/*�L�[����L��*/){
	//---�v���C���[���싖��
		//�L�[����
		fi->Get();

		if(fx || fy){
			fi->Input[0].Down = 0;
			fi->Input[0].Up = 0;
			fi->Input[0].Right = 0;
			fi->Input[0].Left = 0;
		}
		if(fx == 1){
			fi->Input[0].Right = 1;
		} else if(fx == -1){
			fi->Input[0].Left = 1;
		}
		if(fy == 1){
			fi->Input[0].Down = 1;
		} else if(fy == -1){
			fi->Input[0].Up = 1;
		}

		if(fi->Input[0].Up){
			if(!PrevUp){
				LastUp = ft->GetTime();
			}
			PrevUp = 1;
		} else {
			PrevUp = 0;
			LastUp = 0;
		}
		if(fi->Input[0].Down){
			if(!PrevDown){
				LastDown = ft->GetTime();
			}
			PrevDown = 1;
		} else {
			PrevDown = 0;
			LastDown = 0;
		}
		if(fi->Input[0].Left){
			if(!PrevLeft){
				LastLeft = ft->GetTime();
			}
			PrevLeft = 1;
		} else {
			PrevLeft = 0;
			LastLeft = 0;
		}
		if(fi->Input[0].Right){
			if(!PrevRight){
				LastRight = ft->GetTime();
			}
			PrevRight = 1;
		} else {
			PrevRight = 0;
			LastRight = 0;
		}
		if(
			(fi->Input[0].Up && !((flag)&& Field.xyMove == 0) && GetPlayerMove()) || fy
			){

			if((LastUp >= LastDown && LastUp >= LastLeft && LastUp >= LastRight)
				){
				//---��ԍŌ�ɉ����ꂽ�{�^���Ȃ�
				sy -= 1;
				dy = -EF_DELTA_MAX;
				ay = -1;
				flag ++;

				Field.Direction = 0;
			}
		}

		if(
			(fi->Input[0].Down && !((flag) && Field.xyMove == 0) && GetPlayerMove()) || fy
			){

			if((LastDown >= LastUp && LastDown >= LastLeft && LastDown >= LastRight)
				){
				//---��ԍŌ�ɉ����ꂽ�{�^���Ȃ�
				sy += 1;
				dy = EF_DELTA_MAX;
				ay = 1;
				flag ++;

				Field.Direction = 2;
			}
		}

		if(
			(fi->Input[0].Left && !((flag) && Field.xyMove == 0) && GetPlayerMove()) || fx
			){

			if((LastLeft >= LastUp && LastLeft >= LastDown && LastLeft >= LastRight)
				){
				//---��ԍŌ�ɉ����ꂽ�{�^���Ȃ�
				sx -= 1;
				dx = -EF_DELTA_MAX;
				ax = -1;
				flag ++;

				Field.Direction = 3;
			}
		}

		if(
			(fi->Input[0].Right && !((flag) && Field.xyMove == 0) && GetPlayerMove()) || fx
			){

			if((LastRight >= LastUp && LastRight >= LastDown && LastRight >= LastLeft)
				){
				//---��ԍŌ�ɉ����ꂽ�{�^���Ȃ�
				sx += 1;
				dx = EF_DELTA_MAX;
				ax = 1;
				flag ++;

				Field.Direction = 1;
			}
		}

		//---�ړ��͈͊O
		if((sx < 0 || sy < 0 ||
			sx >= lpplane->xSize || sy >= lpplane->ySize)){
				return Field.Count;
		}
		if(!GetMoveEnything()){
			if(!CanPlayerMove(lpeimap,sx,sy)){
/*				//---NP�ƏՓ�
				(IsThereObject(lpeimap,sx,sy) != -1)
				//---�ړ��s�}�b�v
				|| !(lpeimap->GetPatternStatus(lpeimap->Get(sx,sy,EF_STDMAP)) & EF_PATTERN_ST_WALK)

				){*/
				return Field.Count;
			}
		}

		if(flag){
			Field.Move = 1;

			Field.x      = sx;
			Field.y      = sy;

			Field.xDelta = dx;
			Field.yDelta = dy;

			Field.Count = 0;
		}

	}
	if(!Field.Move){
		//---�ړ����łȂ��Ȃ�߂�
//�R�����g�A�E�g2000/4/22
//		Field.MainCharacterAnime = 0;
//		MainCharacterAnime = 1;
//		MainCharacterAnimeCount = 0;
		return Field.Count;
	}

	if(fx || fy){
		return Field.Count;
	}
/*
	//---�A�j��
	static int MainCharacterAnime = 0,MainCharacterAnimeCount = 0;
	{
		static eiTime etMainCharaAnime;
		if(etMainCharaAnime.Get() >= 100){
//		if(++MainCharacterAnimeCount >= 12){
			if(++MainCharacterAnime >= 2){
				MainCharacterAnime = 0;
			}
			MainCharacterAnimeCount = 0;
			etMainCharaAnime.Reset();
		}
		Field.MainCharacterAnime = MainCharacterAnime;
	}
*/
	//�f���^�ړ�
	//---�����ړ��łȂ����
	if(Field.xDelta < 0){
		Field.xDelta += (1 * speed);
		Field.MoveDelta += (1 * speed);
		if(Field.xDelta > 0) //�R�����g�A�E�g2000/10/5����
			Field.xDelta = 0; //
	} else if(Field.xDelta > 0){
		Field.xDelta += (-1 * speed);
		Field.MoveDelta += (1 * speed);
		if(Field.xDelta < 0)
			Field.xDelta = 0;
	}
	
	if(Field.yDelta < 0){
		Field.yDelta += (1 * speed);
		Field.MoveDelta += (1 * speed);
		if(Field.yDelta > 0)
			Field.yDelta = 0;
	} else if(Field.yDelta > 0){
		Field.yDelta += (-1 * speed);
		Field.MoveDelta += (1 * speed);
		if(Field.yDelta < 0)
			Field.yDelta = 0;
	}

	Field.Count ++;

	if(Field.xDelta == 0
		&& Field.yDelta == 0){
		//�ړ����I�������Ȃ�
		Field.Move = 0;
		Field.Count = 0;
	}

	return Field.Count;
}

void eiField::AnimeMainCharacter(int frame /* = 1*/)
{
	//---�A�j��
	static int MainCharacterAnime = 0,MainCharacterAnimeCount = 0;
	{

		MainCharacterAnimeCount += frame;
		if(MainCharacterAnimeCount >= 15){
			if(++MainCharacterAnime >= 2){
				MainCharacterAnime = 0;
			}
			MainCharacterAnimeCount = 0;
		}
		Field.MainCharacterAnime = MainCharacterAnime;
	}
}

//---��ʕ`��
int eiField::Draw(eiMap *lpeimap,int mode /* 1:force*/)
{
	int x,y,r,plane,addres;
	static EIFIELDDRAW efd[EF_PLANE_MAX];
	static int px,py;
	int ptn,speed,rate,
		BaseSpeed = lpeimap->GetPlaneSpeed(lpeimap->GetActiveMap(),lpeimap->GetBasePlane());
	int pSize = 32;
	RECT ClipingRect;
	int ZoomRate = Field.Zoom;
	double doublePutRate = (double)ZoomRate / 100;

	int CheckPtn = 0;

	LPMAP_DATA lpmap = lpeimap->Data.Map[lpeimap->GetActiveMap()];
	LPPLANE_DATA lpplane;

	//---
	if(mode == 0){
		if(Field.SkipCount > 0){
//			Field.SkipCount --;
			return -1;
		}
	}

	//---�`��͈͎w��
	ClipingRect.left = 32 + Field.xTop;
	ClipingRect.top = 32 + Field.yTop;
	ClipingRect.right = ClipingRect.left + Field.xSize * Field.PatternSize;
	ClipingRect.bottom = ClipingRect.top + Field.ySize * Field.PatternSize;
	fw->lpCell[1]->SetClipingRect(&ClipingRect);

	//---�p�^�[���J�E���g�N���A
	Field.PatternCount = 0;

	efd[0].Field.x = Field.x;
	efd[0].Field.y = Field.y;
	efd[0].ZoomRate = ZoomRate;
	efd[0].doublePutRate = doublePutRate;

	if(BGCallback != NULL){
		(*BGCallback)(fw->lpCell[1],
			Field.xSize,Field.ySize,
			Field.xTop,Field.yTop,0);
	}

	for(plane = 0;plane < EF_PLANE_MAX;plane ++){
/*		if(!lpeimap->Data.Map[lpeimap->Data.ActiveMap]->UsePlane[plane]){
			//���̃v���[�����g���ĂȂ���΃��[�v�����擪�ɖ߂�
			continue;
		}*/

		if(lpeimap->Data.Map[lpeimap->Data.ActiveMap]->UsePlane[plane]){
			lpplane = &lpmap->Plane[plane];
			if(lpplane->Show == 0){
				//---�\�����Ȃ����
				continue;
			}

			//---���W
			efd[plane].s.x = Field.x;//���S
			efd[plane].s.y = Field.y;
			efd[plane].Delta.x = Field.xDelta;//---�f���^�l
			efd[plane].Delta.y = Field.yDelta;
			//---�p�^�[���T�C�Y
			efd[plane].pSize = pSize = (int)(Field.PatternSize * ZoomRate / 100);

			//---�x�[�X�v���[�����猩���e�v���[���̑��Α��x
			speed = lpeimap->GetPlaneSpeed(lpeimap->GetActiveMap(),plane);
			rate = (speed * 100) / BaseSpeed;
		
			if(rate){
				r = 100 / rate;
				//---���Α��x�ɏ]���č��W��␳����
				efd[plane].f.x = efd[plane].f.y = 0;
				if(rate < 100){
					efd[plane].f.x = (efd[plane].s.x) % r;//((sx * rate) / 100);
					efd[plane].f.y = (efd[plane].s.y) % r;//((sx * rate) / 100);
				}
				efd[plane].Delta.x = ((efd[plane].Delta.x * rate) / 100) * ZoomRate / 100;
				efd[plane].Delta.y = ((efd[plane].Delta.y * rate) / 100) * ZoomRate / 100;
				if(efd[plane].f.x){
					efd[plane].Delta.x -= ((pSize / (100 / rate)) * efd[plane].f.x * ZoomRate / 100);
				}
				if(efd[plane].f.y){
					efd[plane].Delta.y -= ((pSize / (100 / rate)) * efd[plane].f.y * ZoomRate / 100);
				}
				efd[plane].s.x = ((efd[plane].s.x * rate) / 100);
				efd[plane].s.y = ((efd[plane].s.y * rate) / 100);
			}

			//---���S���W
			efd[plane].Center.x = (Field.xSize * EF_PATTERN_SIZE) / 2 - (pSize / 2);
			efd[plane].Center.y = (Field.ySize * EF_PATTERN_SIZE) / 2 - (pSize / 2);
			//---�ǂ̒��x�͈̔͂ŕ`���΂��������߂�
			efd[plane].Range.x = ((efd[plane].Center.x / pSize) + 2);
			efd[plane].Range.y = ((efd[plane].Center.y / pSize) + 2);
			//---�����Ȃ��v���[���̏ꍇ
			if(rate == 0){
				efd[plane].s.x = efd[plane].Range.x;
				efd[plane].s.y = efd[plane].Range.y;
				efd[plane].Delta.x = efd[plane].Delta.y = 0;
			}

			efd[plane].Offset.x = (Field.xTop + efd[plane].Delta.x) + efd[plane].Center.x;
			efd[plane].Offset.y = (Field.yTop + efd[plane].Delta.y) + efd[plane].Center.y;

			//---�t�B�[���h�`��
			for(y = -efd[plane].Range.y ; y <= efd[plane].Range.y ; y ++){
				py = y + efd[plane].s.y;
				if(py < 0 || py >= lpplane->ySize){
					//������ʂ���݂͂łĂ���
					if(plane != 1){
						continue;
					}
				}

				//�A�h���X
				addres = (py) * lpplane->xSize;
				
				if(Field.Zoom == 100){
//--------------------------------------------------
				//---��g�厞�̏���
					for(x = -efd[plane].Range.x;x <= efd[plane].Range.x;x ++){
						px = x + efd[plane].s.x;
						if(px < 0 || px >= lpplane->xSize
							|| py < 0 || py >= lpplane->ySize){
							//������ʂ���݂͂łĂ���
							if(plane == 1){
								fCell[lpeimap->Data.Pattern[lpmap->BlankPattern].AnimeUpdata
									/*lpmap->BlankPattern*/].PutTransClip(fw->lpCell[1],
									(x + 1) * 32 + efd[plane].Offset.x, 
									(y + 1) * 32 + efd[plane].Offset.y);
							}
							continue;
						}
						ptn = (int)(*(EFMAP *)(lpplane->lpData + addres + (px)));

						CheckPtn |= ptn;

						if(ptn == EF_PATTERN_TRANS)
							//---�����p�^�[���Ȃ�
							continue;

						ptn = lpeimap->Data.Pattern[ptn].AnimeUpdata;
/*						ptn = lpeimap->Data.Pattern
							[(int)(*(EFMAP *)
							(lpplane->lpData + addres + (px)))].AnimeUpdata;
*/

						fCell[ptn].PutClipSelect(fw->lpCell[1],
							(x + 1) * 32 + efd[plane].Offset.x,
							(y + 1) * 32 + efd[plane].Offset.y,
							NULL,plane - 1);
						//---�p�^�[���J�E���g�𑝂₷
						Field.PatternCount ++;
					}
				} else {
//--------------------------------------------------
				//---�g�厞�̏���
					for(x = -efd[plane].Range.x;x <= efd[plane].Range.x;x ++){
						px = x + efd[plane].s.x;
						if(px < 0 || px >= lpplane->xSize
							|| py < 0 || py >= lpplane->ySize){
							//������ʂ���݂͂łĂ���
							if(plane == 1){
								fCell[lpeimap->Data.Pattern[lpmap->BlankPattern].AnimeUpdata].PutExtend(fw->lpCell[1],
									(x * pSize) + efd[plane].Offset.x + 32, //+ (Field.xTop + efd[plane].Delta.x) + 32 + efd[plane].Center.x,
									(y * pSize) + efd[plane].Offset.y + 32,// + (Field.yTop + efd[plane].Delta.y) + 32 + efd[plane].Center.y,
									doublePutRate,doublePutRate,EI_TRANS);
							}
							continue;
						}
/*						if(px < 0 || px >= lpplane->xSize){
							//������ʂ���݂͂łĂ���
							if(plane == 1){
								fCell[lpeimap->Data.Pattern[lpmap->BlankPattern].AnimeUpdata].PutExtend(fw->lpCell[1],
									(x * pSize) + efd[plane].Offset.x + 32, //+ (Field.xTop + efd[plane].Delta.x) + 32 + efd[plane].Center.x,
									(y * pSize) + efd[plane].Offset.y + 32,// + (Field.yTop + efd[plane].Delta.y) + 32 + efd[plane].Center.y,
									doublePutRate,doublePutRate,EI_TRANS);
							}
							continue;
						}*/

						ptn = (int)(*(EFMAP *)(lpplane->lpData + addres + (px)));

						if(ptn == EF_PATTERN_TRANS)
							//---�����p�^�[���Ȃ�
							continue;

						ptn = lpeimap->Data.Pattern[ptn].AnimeUpdata;

						fCell[ptn].PutExtend(fw->lpCell[1],
							(x * pSize) + efd[plane].Offset.x + 32,// + (Field.xTop + efd[plane].Delta.x) + 32 + efd[plane].Center.x, 
							(y * pSize) + efd[plane].Offset.y + 32,// + (Field.yTop + efd[plane].Delta.y) + 32 + efd[plane].Center.y,
							doublePutRate,doublePutRate,EI_TRANS);
						//---�p�^�[���J�E���g�𑝂₷
						Field.PatternCount ++;
					}
				}
			}
		}

		if(plane == 0)
			continue;
		if(
			(  !lpeimap->Data.Map[lpeimap->Data.ActiveMap]->UsePlane[plane]
			&& !lpeimap->Data.Map[lpeimap->Data.ActiveMap]->UsePlane[plane - 1])){
			//���̃v���[�����g���ĂȂ���΃��[�v�����擪�ɖ߂�
			continue;
		}
		//---�`��v���[����������������
		if(plane % 2 == 0){
			//---�����v���C���[�v���[���ƈ�v���Ă���Ȃ�v���C���[�`��
			if(plane == GetPlayerPlane() || plane - 1 == GetPlayerPlane()){
				if(GetMainCharacter()){
					if(MainCharacterCallback){
						//---���C���L�����N�^�[�Ăяo��
						int cx,cy;

						cx = (Field.xSize * Field.PatternSize / 2) + Field.xTop;
						cy = (Field.ySize * Field.PatternSize / 2) + Field.yTop;
						(*MainCharacterCallback)(fw->lpCell[1],
							(Field.Direction * EF_OBJECT_PATTERNDIRECTIONSIZE) + Field.MainCharacterAnime,
							cx + 16,cy + 16,cx,cy);
					}
				}
			}
			//---�I�u�W�F�N�g��`��
			int number,this_object;

			for(number = 0;number < lpeimap->GetMaxObjectIndex()/*EF_OBJECT_MAX*/;number ++){
				//---�C���f�b�N�X����I�u�W�F�N�g�ԍ��𓾂�
				this_object = lpeimap->ObjectIndex[number];
				if(this_object == -1)
				continue;

				if(lpmap->lpObject[this_object].GetFlag()){
					if(plane == lpmap->lpObject[this_object].GetPlane() || plane - 1 == lpmap->lpObject[this_object].GetPlane()){
						//---�v���[������v�����Ȃ�
						if(::efDebugMode == 1
							|| lpmap->lpObject[this_object].GetPattern() != EF_OBJECT_TRANS){
							lpmap->lpObject[this_object].Put(&efd[0]);
						}
					}
				}
			}
		}
	}

	if(FGCallback != NULL){
		(*FGCallback)(fw->lpCell[1],
			Field.xSize,Field.ySize,
			Field.xTop,Field.yTop,0);
	}

	if(CheckPtn > 0x07ff){
		char s[80];
		sprintf(s,"(eiField::Draw) Pattern Error %d\n",CheckPtn);
		eiDebugWriteFile(s);
	}
/*	//---�I�u�W�F�N�g��`��
	int number;
	for(number = 0;number < EF_OBJECT_MAX;number ++){
		if(lpmap->lpObject[number].GetFlag()){
			if(::efDebugMode == 1
				|| lpmap->lpObject[number].GetPattern() != EF_OBJECT_TRANS){
				lpmap->lpObject[number].Put(&efd[0]);
			}
		}
	}*/
/*	if(GetMainCharacter()){
		if(MainCharacterCallback){
			//---���C���L�����N�^�[�Ăяo��
			int cx,cy;

			cx = (Field.xSize * Field.PatternSize / 2) + Field.xTop;
			cy = (Field.ySize * Field.PatternSize / 2) + Field.yTop;
			(*MainCharacterCallback)(fw->lpCell[1],
				(Field.Direction * EF_OBJECT_PATTERNDIRECTIONSIZE) + Field.MainCharacterAnime,
				cx + 16,cy + 16,cx,cy);
		}
	}*/

	//---�`��͈͎w��
	ClipingRect.left = 0;
	ClipingRect.top = 0;
	ClipingRect.right = 640;
	ClipingRect.bottom = 480;
	fw->lpCell[1]->SetClipingRect(&ClipingRect);

//	eiTime let;
//	let.Delay2(80);

/*	char s[80];
	static eiTime let;
	sprintf(s,"%3d,%3d\n",let.Get(),Field.PatternCount);
	eiDebugWriteFile(s);
	let.Get();
	let.Reset();*/
//	fw->Flip();

/*	//--�]���ȕ���������
	for(y = 0;y < Field.ySize + 2;y ++){//y = 1;y < aaa+1
		cMapWindow[0].Put(fw->lpCell[1],
			Field.xTop , y * Field.PatternSize);
		cMapWindow[0].Put(fw->lpCell[1],
			Field.xTop + ((Field.xSize + 1) * Field.PatternSize), y * Field.PatternSize);
	}
	for(x = 0;x < Field.xSize + 2;x ++){
		cMapWindow[1].Put(fw->lpCell[1],
			x * Field.PatternSize , Field.yTop);//+1
		cMapWindow[1].Put(fw->lpCell[1],
			x * Field.PatternSize , Field.yTop + ((Field.ySize + 1) * Field.PatternSize));//+1
	}

	cMapWindow[2].Put(fw->lpCell[1],
		Field.xTop , Field.yTop);
	cMapWindow[3].Put(fw->lpCell[1],
		Field.xTop + ((Field.xSize + 1) * Field.PatternSize), Field.yTop);
	cMapWindow[4].Put(fw->lpCell[1],
		Field.xTop , Field.yTop + ((Field.ySize + 1) * Field.PatternSize));
	cMapWindow[5].Put(fw->lpCell[1],
		Field.xTop + ((Field.xSize + 1) * Field.PatternSize),
		Field.yTop + ((Field.ySize + 1) * Field.PatternSize));
*/
	return 1; 
}

//---���t���b�V�����[�g���E�F�C�g�̌v�Z
int eiField::CalcRefreshRateAndWait(int set /*= 0*/)
{
	static eiTime let;
	int x;
	int pass = let.Get() * 100,
		wait = (GetDrawRate() * Field.ChangeRefresh / 100);

	if(set){
		let.Reset();
		Field.SkipCount = 0;
		memset(&Field.PreviousWorkTime[0],0,sizeof(Field.PreviousWorkTime));
	}

	//---
	if(Field.SkipCount > 0){
		Field.SkipCount --;
//		let.Reset();
		return -1;
	}
	if(Field.DrawMode == EF_DRAW_AUTOCHANGE){
		int limit = (
				((1000 / eiSetDrawRefreshRate(-1))) * GetDrawRate() * Field.ChangeRefresh * GetMarginOfErrorFPS()
			) / 100;

/*		char s[80];
		sprintf(s,"%d   %d,%d,%d\n",limit,pass,Field.ChangeRefresh,GetMarginOfErrorFPS());
		eiDebugWriteFile(s);
*/
		if(pass > limit
			&& Field.PreviousWorkTime[0] > limit
			&& Field.PreviousWorkTime[0] > limit
			&& Field.PreviousWorkTime[0] > limit
			&& Field.PreviousWorkTime[0] > limit){
 			//---�ߋ��S��ɂ킽���ĕ`�掞�Ԃ�
			//---���t���b�V���^�C�����z���Ă����Ƃ�
			//---���t���b�V�����[�g�𔼕��ɂ���
			Field.RestCount = 60;
			Field.ChangeRefresh *= 2;

//			eiDebugWriteFile("!aa\n");
		}
	}
	//---����t�B�[���h�`���������΂���
	Field.SkipCount = Field.ChangeRefresh - 1;

	for(x = 0;x < 3;x ++)
		Field.PreviousWorkTime[x] = Field.PreviousWorkTime[x + 1];
	Field.PreviousWorkTime[x] = pass;

	let.Reset();

	return wait;
}

//---�`�惂�[�h�ݒ�
int eiField::SetDrawRate(int rate)
{
	int Old = GetDrawRate();

	Field.DrawRate = rate;

	return Old;
}
int eiField::GetDrawRate(void)
{
	return Field.DrawRate;
}
int eiField::SetDrawMode(int mode)
{
	int Old = GetDrawMode();

	Field.DrawMode = mode;

	return Old;
}
int eiField::GetDrawMode(void)
{
	return Field.DrawMode;
}

//---���t���b�V�����[�g�̎��������l�𓾂�
int eiField::GetAutoChangeStatus(void)
{
	return Field.ChangeRefresh;
}

//---�T�C�Y�𓾂�
int eiField::GetPatternSize(void)
{
	return Field.PatternSize;
}

int eiField::xGetFieldSize(void)
{
	return Field.xSize;
}

int eiField::yGetFieldSize(void)
{
	return Field.ySize;
}

int eiField::xGetFieldTop(void)
{
	return Field.xTop;
}

int eiField::yGetFieldTop(void)
{
	return Field.yTop;
}

int eiField::xGet(void)
{
	return Field.x;
}

int eiField::yGet(void)
{
	return Field.y;
}

int eiField::xGetDelta(void)
{
	return Field.xDelta;
}

int eiField::yGetDelta(void)
{
	return Field.yDelta;
}

int eiField::xSet(int x)
{
	Field.x = x;
	return 1;
}

int eiField::ySet(int y)
{
	Field.y = y;
	return 1;
}

int eiField::SetMoveSpeed(int speed)
{
	int old = GetMoveSpeed();

	Field.MoveSpeed = speed;

	return old;
}

int eiField::GetMoveSpeed(void)
{
	return Field.MoveSpeed;
}

//---�t�B�[���h�f���^
int eiField::GetMoveDelta(void)
{
	return Field.MoveDelta;
}

int eiField::SetMoveDelta(int delta)
{
	int a = Field.MoveDelta;

	Field.MoveDelta = delta;

	return a;
}

void eiField::SetDirection(int dir)
{
	Field.Direction = dir;
}

int eiField::GetDirection(void)
{
	return Field.Direction;
}

//---�g��{���w��
int eiField::SetFieldZoom(int zoom)
{
	int a = Field.Zoom;

	Field.Zoom = zoom;

	return a;
}

int eiField::GetFieldZoom(void)
{
	return Field.Zoom;
}

void eiField::SetFieldSize(int sx,int sy)
{
	Field.xSize = sx;
	Field.ySize = sy;
}

void eiField::SetFieldTop(int sx,int sy)
{
	Field.xTop = sx;
	Field.yTop = sy;
}

//---���W���t�B�[���h�\����ʏ�ɂ��邩�ǂ������ׂ�
int eiField::IsOnFieldWindow(int sx,int sy)
{
	if(sx < (xGetFieldTop() + Field.PatternSize)
		|| sx >= (xGetFieldTop() + (xGetFieldSize() + 1) * Field.PatternSize)
		|| sy < (yGetFieldTop() + Field.PatternSize)
		|| sy >= (yGetFieldTop() + (yGetFieldSize() + 1) * Field.PatternSize) ){
		//---�t�B�[���h��Ɏw�肳�ꂽ���W���Ȃ��I
		return 0;
	}

	return 1;
}

//---�t�B�[���h�E�B���h�E���W�ɕϊ�
int eiField::CalcFieldWindowPos(LPEIPOINT lpPoint)//(int *x,int *y)
{
	int sx = lpPoint->x,sy = lpPoint->y;

	if(!IsOnFieldWindow(sx,sy))
		return 0;

	sx -= (xGetFieldTop() + GetPatternSize());
	sy -= (yGetFieldTop() + GetPatternSize());

	lpPoint->x = sx;
	lpPoint->y = sy;

	return 1;
}

//---��ʍ��W����}�b�v���W�֕ϊ�
int eiField::CalcScreenToMap(eiMap *lpmap,LPEIPOINT lpPoint)//,int *x,int *y)
{
	if(!CalcFieldWindowPos(lpPoint))//&sx,&sy))
		return 0;

	int sx = lpPoint->x,sy = lpPoint->y;

	//---���S���O�ɂ���
	sx = (sx / (GetPatternSize() * Field.Zoom / 100) )
			- (xGetFieldSize() * 100 / Field.Zoom / 2);

	sy = (sy / (GetPatternSize()  * Field.Zoom / 100) )
		- (yGetFieldSize() * 100 / Field.Zoom / 2);

	sx = Field.x + sx;
	sy = Field.y + sy;

	lpPoint->x = sx;
	lpPoint->y = sy;

	return 1;
}

//---�L�����N�^�[��`�����ǂ���
int eiField::SetMainCharacter(int mode)
{
	int old = DrawMainCharacter;

	DrawMainCharacter = mode;

	return old;
}

int eiField::GetMainCharacter(void)
{
	return DrawMainCharacter;
}

void eiField::SetMainCharacterCallback(void (*func)(eiCell *,int ,int, int, int, int))
{
	MainCharacterCallback = func;
}

//---�R�[���o�b�N�ݒ�
void eiField::SetBGCallback(void (*func)(eiCell *,int ,int, int, int, int))
{
	BGCallback = func;
}

void eiField::SetFGCallback(void (*func)(eiCell *,int ,int, int, int, int))
{
	FGCallback = func;
}

int eiField::SetMarginOfErrorFPS(int margin)
{
	int old = MarginOfErrorFPS;

	MarginOfErrorFPS = margin;

	return old;
}

int eiField::GetMarginOfErrorFPS(void)
{
	return MarginOfErrorFPS;
}


//---�L�����N�^�[�������Ă�������̍��W
int eiField::xGetForward(void)
{
	return ::xGetForward(Field.x,Field.Direction);
}

int eiField::yGetForward(void)
{
	return ::yGetForward(Field.y,Field.Direction);
}

//---�I�u�W�F�N�g�𓮂���
int eiField::MoveObject(eiMap *lpeimap,int frame /*= 1*/,int not_random /*= 0*/,int new_move /*= 1*/)
{
	int num,sx,sy,dir,status,this_obj;
	eiMapObject *lpobject = &lpeimap->Data.Map[lpeimap->Data.ActiveMap]->lpObject[0];
	LPPLANE_DATA lpplane = &lpeimap->Data.Map[lpeimap->Data.ActiveMap]->Plane[EF_STDMAP];

	for(num = 0;num < lpeimap->GetMaxObjectIndex()/*EF_OBJECT_MAX*/;num ++){
		this_obj = lpeimap->ObjectIndex[num];
		if(this_obj == -1)
			continue;

/*		char s[80];
		sprintf(s,"%d\n",this_obj);
		eiDebugWriteFile(s);
*/
		if((lpobject + this_obj) != NULL){
			//---�������X�g�A
			lpobject[this_obj].RestoreDirection();
			if(!not_random && lpobject[this_obj].AddMoveCount(frame)
				&& new_move){
				//---�����I
				dir = 0;
				status = lpobject[this_obj].GetStatus();
				if(status & EF_OBJECT_ST_MOVEFIXED){
					//---�Œ肾�����玟�̃I�u�W�F�N�g��
					continue;
				} else if(status & EF_OBJECT_ST_MOVERANDOM){
					//---�����_���ړ�
					dir = eiRnd(4);
				}
				lpobject[this_obj].SetDirection(dir);

				//---�ڕW���W�֓����邩
				sx = lpobject[this_obj].xGetForward();
				sy = lpobject[this_obj].yGetForward();

				//---�ړ��͈͊O
				if((sx < 0 || sy < 0 ||
					sx >= lpplane->xSize || sy >= lpplane->ySize)){
					continue;
				}
				{//---�����Ŏ��R���[�h�Ɛ��񃂁[�h�̋�ʂ�����
					if(
						//---Player�ƏՓ�
						(Field.x == sx && Field.y == sy)
						//---Object�ƏՓ�
						|| (IsThereObject(lpeimap,sx,sy,this_obj) != -1)
						//---�ړ��s�}�b�v
						||(
						 !(lpeimap->GetPatternStatus(lpeimap->Get(sx,sy,EF_STDMAP)) & (EF_PATTERN_ST_WALK))
						 || (lpeimap->GetPatternStatus(lpeimap->Get(sx,sy,EF_STDMAP)) & (EF_PATTERN_ST_OBJNOWALK))
						 )
						){
						continue;
					}
					if(SeekEfectPattern(lpeimap,lpobject[this_obj].GetPlane() + 1,lpobject[this_obj].GetPlane() + 1,
							sx,sy) & EF_PATTERN_ST_UNDERNOWALK){
						continue;
					}
				}
				//---���ۂɓ�����
				lpobject[this_obj].MoveDelta(sx - lpobject[this_obj].Data.x,sy - lpobject[this_obj].Data.y);
			}
			lpobject[this_obj].Move(frame);
			lpobject[this_obj].SaveDirection();
		}
	}

	return 1;
}

//---�C�x���g�z���s�\���H
int eiField::SetOverObject(int mode)
{
	int old = Field.CantOverObject;

	Field.CantOverObject = mode;

	return old;
}

int eiField::GetOverObject(void)
{
	return Field.CantOverObject;
}
