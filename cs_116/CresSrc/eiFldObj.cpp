//--------------------------------------------------
//---�I�u�W�F�N�g
eiMapObject::eiMapObject(void)
{
}
eiMapObject::~eiMapObject()
{
}

int eiMapObject::Save(eiFile *pfile)
{
	//---�t���O��������
	pfile->Write(&Data.Flag,sizeof(int),1);
	
	if(Data.Flag){
		//---�t���O���P�Ȃ�
		pfile->Write(&Data,sizeof(Data),1);
	}
	return 1;
}

//---�t�@�C���ɏ�������
int eiMapObject::Save(FILE *fp)
{
	//---�t���O��������
	fwrite(&Data.Flag,sizeof(int),1,fp);
	
	if(Data.Flag){
		//---�t���O���P�Ȃ�
		fwrite(&Data,sizeof(Data),1,fp);
	}
	return 1;
}
//---�t�@�C������ǂݏo��
int eiMapObject::Load(eiFile *pfile/*FILE *fp*/)
{
	//---�t���O�ǂݍ���
	pfile->Read(&Data.Flag,sizeof(int),1);

	if(Data.Flag){
		pfile->Read(&Data,sizeof(Data),1);
		Data.MoveCount = eiRnd(Data.MoveFreq);
		if(Data.Status & EF_OBJECT_ST_DIRRANDOM){
			Data.Direction = eiRnd(4);
		}
		SaveDirection();

//		Data.AnimeWait = 20;
		//---test
//		pfile->Read(&Data,sizeof(int) * 12,1);
//		pfile->Read((BYTE *)(&Data) + sizeof(int) * 13,
//			sizeof(int) * 4 + sizeof(ei_u8) * EF_OBJECT_MOVEMACROMAX,1);

		return 1;
	}
	//---���Ȃ��I
	return 0;
}

void eiMapObject::Init(void)
{
	memset(&Data,0,sizeof(Data));
}

void eiMapObject::Delete(void)
{
	Init();
//	memset(&Data,0,sizeof(Data));
}

int eiMapObject::Create(int Number)
{
	memset(&Data,0,sizeof(Data));
	Data.Flag = 1;
	Data.Number = Number;
	Data.GraphicNumber = EF_OBJECT_TRANS;
	Data.Status = EF_OBJECT_ST_MOVEFIXED;
	Data.Plane = 1;
	Data.MoveSpeed = 30;

	Data.AnimeWait = 15;
	SaveDirection();

	return 1;
}

int eiMapObject::xGet(void)
{
	return Data.x;
}

int eiMapObject::yGet(void)
{
	return Data.y;
}

//---�I�u�W�F�N�g�̈ʒu��ݒ�
int eiMapObject::SetPos(int x,int y,int PlaneNumber)
{
	Data.x = x;
	Data.y = y;
	if(PlaneNumber != -1){
		Data.Plane = PlaneNumber;
	}

	return 1;
}

int eiMapObject::GetFlag(void)
{
	return Data.Flag;
}

//---�O���t�B�b�N�p�^�[����ݒ�
int eiMapObject::SetPattern(int Number)
{
	int Old = Data.GraphicNumber;

	Data.GraphicNumber = Number;

	return Old;
}

int eiMapObject::GetPattern(void)
{
	return Data.GraphicNumber;
}

//---���ׂẴf�[�^���Z�b�g
int eiMapObject::SetData(LPOBJECT_DATA lpData)
{
	memcpy(&Data,lpData,sizeof(Data));
	memset(&NoSaveData,0,sizeof(NoSaveData));
	SaveDirection();

	return 1;
}
int eiMapObject::GetData(LPOBJECT_DATA lpData)
{
	memcpy(lpData,&Data,sizeof(Data));

	return 1;
}

//---�X�e�[�^�X
int eiMapObject::SetStatus(int Status)
{
	int Old = Data.Status;

	Data.Status = Status;

	return Old;
}

int eiMapObject::GetStatus(void)
{
	return Data.Status;
}

//---����
int eiMapObject::GetDirection(void)
{
	return Data.Direction;
}

int eiMapObject::SetDirection(int Direction)
{
	int Old = Data.Direction;

	NoSaveData.KpDirection = Data.Direction = Direction;

	return Old;
}

//---�����ۑ�
void eiMapObject::SaveDir(void)
{
	NoSaveData.KpDirection2 = GetDirection();
}

void eiMapObject::RestoreDir(void)
{
	SetDirection(NoSaveData.KpDirection2);
}

//---�����ۑ�
void eiMapObject::SaveDirection(void)
{
	NoSaveData.KpDirection = GetDirection();
}

void eiMapObject::RestoreDirection(void)
{
	SetDirection(NoSaveData.KpDirection);
}

//---�I�u�W�F�N�g�̑�����v���[��
int eiMapObject::SetPlane(int Plane)
{
	int Old = Data.Plane;

	Data.Plane = Plane;

	return Old;
}

int eiMapObject::GetPlane(void)
{
	return Data.Plane;
}

//---�I�u�W�F�N�g�̍��W�����A���A�������������H
int eiMapObject::IsThere(int x,int y,int plane/* = -1*/)
{
	if(Data.x == x && Data.y == y){
		if(plane == -1)
			return 1;
		if(Data.Plane == plane)
			return 1;
	}
	return 0;
}

//---�����̍��W
int eiMapObject::xGetForward(void)
{
	return ::xGetForward(Data.x,Data.Direction);
}

int eiMapObject::yGetForward(void)
{
	return ::yGetForward(Data.y,Data.Direction);
}

//---�A�j���[�V����
//---�A�j���[�V�����J�n
int eiMapObject::StartAnime(int force/* = 0*/)
{
	Data.AnimeFlag = 1;
	Data.AnimeCount = 0;
	Data.AnimeWait = 0;
	Data.AnimePos = 0;

	return 1;
}

//---�A�j���[�V�����I��
int eiMapObject::EndAnime(int force/* = 0*/)
{
	if((Data.Status & EF_OBJECT_ST_ANIMEMOVE) && force == 0)
		//---��ɃA�j���[�V�����ŋ����͂��Ȃ����
		return 0;

	Data.AnimeFlag = 0;

	return 1;
}

//---�A�j���[�V����
int eiMapObject::DoAnime(int frame/* = 1*/)
{
	if(Data.AnimeFlag || (Data.Status & EF_OBJECT_ST_ANIMEMOVE)){
		Data.AnimeCount += frame;
		if(Data.AnimeCount >= Data.AnimeWait){
			Data.AnimeCount = 0;
			Data.AnimePos ++;
			if(Data.AnimePos >= EF_OBJECT_PATTERNDIRECTIONSIZE){
				Data.AnimePos = 0;
			}
			return 1;
		}
	}

	return 0;
}

//---�A�j���[�V�����ʒu���Z�b�g
int eiMapObject::SetAnimePos(int Pos)
{
	int Old = Data.AnimePos;

	Data.AnimePos = Pos;

	return Old;
}

int eiMapObject::GetAnimePos(void)
{
	return Data.AnimePos;
}

int eiMapObject::Move(int frame /*= 1*/)
{
	if(Data.xDelta < 0){
		Data.xDelta += (frame * Data.MoveSpeed);
		if(Data.xDelta > 0)
			Data.xDelta = 0;
	}
	if(Data.xDelta > 0){
		Data.xDelta -= (frame * Data.MoveSpeed);
		if(Data.xDelta < 0)
			Data.xDelta = 0;
	}
	//---
	if(Data.yDelta < 0){
		Data.yDelta += (frame * Data.MoveSpeed);
		if(Data.yDelta > 0)
			Data.yDelta = 0;
	}
	if(Data.yDelta > 0){
		Data.yDelta -= (frame * Data.MoveSpeed);
		if(Data.yDelta < 0)
			Data.yDelta = 0;
	}

	return 1;
}

//---�I�u�W�F�N�g�̈ړ�
int eiMapObject::MoveDelta(int dx,int dy)
{
	Data.x += dx;
	Data.y += dy;

	if(dx == -1){
		Data.xDelta = EF_DELTA_MAX;
	} else if(dx == 1){
		Data.xDelta = -EF_DELTA_MAX;
	}

	if(dy == -1){
		Data.yDelta = EF_DELTA_MAX;
	} else if(dy == 1){
		Data.yDelta = -EF_DELTA_MAX;
	}

	return 1;
}

//---����J�E���^
int eiMapObject::AddMoveCount(int frame)
{
	//---���쒆�Ȃ�߂�
	if(Data.xDelta || Data.yDelta)
		return 0;

	Data.MoveCount += frame;
	if(Data.MoveCount >= Data.MoveFreq || (Data.MoveFreq == 0)){
		//---�����K�v������
		Data.MoveCount = 0;
		return 1;
	}

	return 0;
}

//---�I�u�W�F�N�g��`��
int eiMapObject::Put(LPEIFIELDDRAW lpefd)
{
	int x,y,plane;
	EISTR s[8];

	if(Data.GraphicNumber == EF_OBJECT_TRANS && ::efDebugMode == 0)
		return 0;

	//---���ߕ�����������
	if(Data.Direction == DIR_TRANS && ::efDebugMode == 0)
		return 0;

	plane = Data.Plane;
	x = (Data.x - lpefd[0].Field.x);
	y = (Data.y - lpefd[0].Field.y);

	if(-lpefd[plane].Range.x <= x && x <= lpefd[plane].Range.x
		&& -lpefd[plane].Range.y <= y && y <= lpefd[plane].Range.y){
		//---�`��
		if(Data.GraphicNumber != EF_OBJECT_TRANS){
			if(lpefd[0].ZoomRate == 100){
				fObjectPattern[Data.AnimePos + (Data.Direction * EF_OBJECT_PATTERNDIRECTIONSIZE)
					+ (Data.GraphicNumber * EF_OBJECT_PATTERNSIZE)].PutTransClip(
					fw->lpCell[1],
					((x) * 32 + Data.xDelta) + lpefd[plane].Offset.x + 32, 
					((y) * 32 + Data.yDelta) + lpefd[plane].Offset.y + 32);
			} else {
				fObjectPattern[Data.AnimePos + (Data.Direction * EF_OBJECT_PATTERNDIRECTIONSIZE)
					+ Data.GraphicNumber * EF_OBJECT_PATTERNSIZE].PutExtend(
					fw->lpCell[1],
					(x * lpefd[plane].pSize) + lpefd[plane].Offset.x + 32,
					(y * lpefd[plane].pSize) + lpefd[plane].Offset.y + 32,
					lpefd[0].doublePutRate,lpefd[0].doublePutRate,EI_TRANS);
			}
		}
		//---�f�o�b�O�p
		if(::efDebugMode){
			if(lpefd[0].ZoomRate == 100){
				fDebugCell[2].PutTransClip(fw->lpCell[1],
					(x) * 32 + lpefd[plane].Offset.x + 32, 
					(y) * 32 + lpefd[plane].Offset.y + 32);
			} else {
				fDebugCell[2].PutExtend(
					fw->lpCell[1],
					(x * lpefd[plane].pSize) + lpefd[plane].Offset.x + 32,
					(y * lpefd[plane].pSize) + lpefd[plane].Offset.y + 32,
					lpefd[0].doublePutRate,lpefd[0].doublePutRate,EI_TRANS);
			}
			sprintf(&s[0],"%d",Data.Number);
			eiFieldDrawText(fw->lpCell[1],s,
				(x * lpefd[plane].pSize) + lpefd[plane].Offset.x + 32,
				(y * lpefd[plane].pSize) + lpefd[plane].Offset.y + 32 + 14,
			EI_TRANS);
		}
	}

	return 1;
}
