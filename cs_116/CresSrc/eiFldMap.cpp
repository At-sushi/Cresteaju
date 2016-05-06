eiMap::eiMap(void)
{
	Init();
}

eiMap::~eiMap()
{
	Delete();
}

void eiMap::Init(void)
{
	eimemset(&Data,0,sizeof(Data));

	SetBasePlane(1);

	sprintf(Directory,"");
	FileMode = 0;
	sprintf(SLinkFileName,"");

	int a;
	//---�A�j���[�V�����E�X�e�[�^�X�ݒ�
	for(a = 0;a < EF_PATTERN_MAX;a ++){
		//---�A�j���[�V��������
		Data.Pattern[a].AnimeUpdata = Data.Pattern[a].NextAnime = (ei_s16)a;
		Data.Pattern[a].AnimeCount = 0;
		Data.Pattern[a].AnimeWait = 30;
		Data.Pattern[a].Status = 0;
	}

	InitObjectIndex();
}

//---�}�b�v���t�@�C���ɏ�������
int eiMap::Save(EISTR *name)
{
//	FILE *fp = fopen(name,"wb");
	EISTR Header[12] = "eiMapFormat";
	EISTR Format[3] = {'0',0,0};
	int a,b,Index[EF_MAP_MAX],IndexSize = EF_MAP_MAX;
	eiBitStream eb;

	eiFile File;
	eiMemoryFile MemoryFile;
	eiFile *pfile;

	//---���k�t���b�O
	Data.Compress = 0;//1
	
	//---�������ރt�@�C�����I�[�v��
	File.Open(name,EI_FILE_WRITE | EI_FILE_BINARY);
	if(Data.Compress == 0){
		//---���̂܂�
		pfile = &File;
	} else {
		//---���k
		pfile = &MemoryFile;
		MemoryFile.Alloc(65536);
		Format[0] = '1';
	}
	
	memset(&Index[0],0,sizeof(Index));

	File.Write(&Header[0],sizeof(EISTR),sizeof(Header));
	File.Write(&Format[0],sizeof(EISTR),sizeof(Format));
	//---Index
	File.Write(&IndexSize,sizeof(int),1);
	File.Write(&Index[0],sizeof(int),IndexSize);

	//---Map�\���̏�������
	if(Data.Compress == 0){
		File.Write(&Data,sizeof(Data),1);
	} else {
		eb.AllocNewBuffer(sizeof(Data) + 4096);
		eb.Compress(&Data,sizeof(Data));
		eb.WriteCompressFile(&File);
//		eb.WriteCompressFile(File.fp);
		eb.FreeBuffer();
	}

	for(a = 0;a < EF_MAP_MAX;a ++){
		if(IsUsedMap(a)){
			//---�g���Ă���MAP_DATA����������
			pfile->Write(Data.Map[a],sizeof(MAP_DATA),1);
			for(b = 0;b < EF_PLANE_MAX;b ++){
				if(IsUsedPlane(a,b)){
					//---�v���[�����g���Ă����
					pfile->Write(Data.Map[a]->Plane[b].lpData,1,
						Data.Map[a]->Plane[b].DataSize);
				}
			}
			//---�I�u�W�F�N�g�̃f�[�^����������
			for(b = 0;b < EF_OBJECT_MAX;b ++){
//				Data.Map[a]->lpObject[b].Save(fp);
				Data.Map[a]->lpObject[b].Save(pfile);
			}
		}
	}

	if(Data.Compress){
		//---���k�Ȃ�A�o�b�t�@�[����������
		eb.AllocNewBuffer(65536);
		eb.Compress(MemoryFile.GetMemory(),MemoryFile.GetSize());
//		eb.WriteCompressFile(File.fp);
		eb.WriteCompressFile(&File);
		eb.FreeBuffer();

/*		//---
		MemoryFile.Free();
		MemoryFile.Alloc(100000);

		eb.ReadCompressFile("test.t");
		eb.Decompress(MemoryFile.GetMemory());*/
	}

	File.Close();
	MemoryFile.Free();

	return 1;
}

//---�t�@�C������}�b�v��ǂݍ���
int eiMap::Load(EISTR *name,EISTR *slname /* = NULL*/,int mode /* = EI_NORMALFILE*/)
{
	eiFile file(slname),*pfile;
	eiMemoryFile MemoryFile;
	eiBitStream eb;
	EISTR Header[12] = "eiMapFormat";
	EISTR Format[3] = {'0',0,0};
	EISTR s[80];
	int a,b,Index[EF_MAP_MAX],IndexSize = EF_MAP_MAX;
	eiMapObject *lpob;
	int speed;

	//---�f�B���N�g�����������炻����擾
	static eistr directory[_MAX_PATH];
	sprintf(directory,"%s",name);
	eistr *start = &directory[0],*end = &directory[strlen(directory) - 1];
	while(start < end){
		if(*end == '\\'){
			*(end + 1) = 0;
			break;
		}
		end --;
	}
	if(start == end){
		sprintf(directory,"");
	} else {
	}

	if(!file.Open(name)){
		return 0;
	}
	//---�Â��̂�����
	Delete();
	Init();
	//---�O���[�o�����R�s�[
	if(directory[0] != NULL)
		sprintf(Directory,"%s",directory);
	FileMode = mode;
	if(slname != NULL)
		sprintf(SLinkFileName,"%s",slname);

	memset(&Index[0],0,sizeof(Index));

	//---���
	file.Read(&Header[0],sizeof(EISTR),sizeof(Header));
	file.Read(&Format[0],sizeof(EISTR),sizeof(Format));
	if(strcmp(&Header[0],"eiMapFormat")){
		//---�������
		file.Close();
		return 0;
	}
	a = atoi(Format);
	if(a > 1){
		//---�t�H�[�}�b�g�^�C�v���T�|�[�g�O��������
		file.Close();
		return 0;
	}
	//---Index
	file.Read(&IndexSize,sizeof(int),1);
	file.Read(&Index[0],sizeof(int),IndexSize);

	//---Map�\���̓ǂݍ���
//	MAPOLD old;
//	file.Read(&old,sizeof(old),1);
//	memcpy(&Data,&old,sizeof(old));
	if(a == 0){
		//---�����k
		file.Read(&Data,sizeof(Data),1);
	} else {
		//---���k
		eb.ReadCompressFile(&file);
//		eb.ReadCompressFile(file.fp);
		if(!eb.Decompress(&Data)){
			//---�}�b�v�����Ă���I
//			eiDebugWriteFile("no map data(1)!!\n");
			file.Close();
			eb.FreeBuffer();
			return 0;
		}
		eb.FreeBuffer();
	}

	if(Data.Compress){
		//---���k����Ă���̂Ȃ�
		eb.ReadCompressFile(&file);
//		eb.ReadCompressFile(file.fp);
		MemoryFile.Alloc(eb.Buffer.OriginalSize + 4096);
		if(!eb.Decompress(MemoryFile.GetMemory())){
			//---�}�b�v�����Ă���I
//			eiDebugWriteFile("no map data(2)!!\n");
			file.Close();
			eb.FreeBuffer();
			return 0;
		}

		pfile = &MemoryFile;
	} else {
		pfile = &file;
	}

	for(a = 0;a < EF_MAP_MAX;a ++){
		if(IsUsedMap(a)){
			//---��x�N���A���č�蒼��
			Data.UseMap[a] = 0;
			Create(a);
			//---�|�C���^�ۑ�
			lpob = Data.Map[a]->lpObject;
			//---�g���Ă���MAP_DATA��ǂݍ���
			pfile->Read(Data.Map[a],sizeof(MAP_DATA),1);
			Data.Map[a]->lpObject = lpob;
			for(b = 0;b < EF_PLANE_MAX;b ++){
				if(IsUsedPlane(a,b)){
					//---�t���O���ꎞ�N���A
					speed = GetPlaneSpeed(a,b);
					Data.Map[a]->UsePlane[b] = 0;
					//---�v���[�������
					CreatePlane(a,b,
						Data.Map[a]->Plane[b].xSize,Data.Map[a]->Plane[b].ySize);
					SetPlaneSpeed(a,b,speed);
					//---�v���[���f�[�^�ǂݍ���
					pfile->Read(Data.Map[a]->Plane[b].lpData,1,
						Data.Map[a]->Plane[b].DataSize);
				}
			}
			//---�I�u�W�F�N�g�̃f�[�^��ǂݍ���
			for(b = 0;b < EF_OBJECT_MAX;b ++){
				if(Data.Map[a]->lpObject[b].Load(pfile)){
				}
			}
		}
	}

	file.Close();
	eb.FreeBuffer();
	MemoryFile.Free();

	//---�}�b�v�p�^�[����ǂݍ���
	for(a = 0;a < EF_PATTERN_PAGEMAX;a ++){
		sprintf(&s[0],"%s%s",directory,&Data.PatternFileName[a][0]);
		ReadPattern(&s[0],slname,mode,a);
	}
	for(a = 0;a < EF_OBJECT_PATTERNMAX;a ++){
		sprintf(&s[0],"%s%s",directory,&Data.ObjectFileName[a][0]);
		ReadObject(&s[0],slname,mode,a);
	}

	//---�A�j���[�V�����E�X�e�[�^�X�ݒ�
	for(a = 0;a < EF_PATTERN_MAX;a ++){
		Data.Pattern[a].AnimeCount = 0;
	}

	//---�A�N�e�B�u�}�b�v��0�ɂ���
	SetActiveMap(0);
/*
//	if(MapNumber == 3){
		if(Data.UseMap[6] == 1){
			memcpy(Data.Map[6]->Plane[1].lpData,
				Data.Map[3]->Plane[1].lpData,
				Data.Map[3]->Plane[1].DataSize);
			memcpy(Data.Map[6]->Plane[2].lpData,
				Data.Map[3]->Plane[2].lpData,
				Data.Map[3]->Plane[2].DataSize);
		}
//	}
*/
	return 1;
}

//---�p�^�[���������[�h
void eiMap::ReloadPattern(void)
{
	int a;
	eistr s[80],*slname;

	if(SLinkFileName[0] == NULL)
		slname = NULL;
	else
		slname = SLinkFileName;

	//---�}�b�v�p�^�[����ǂݍ���
	for(a = 0;a < EF_PATTERN_PAGEMAX;a ++){
		sprintf(&s[0],"%s%s",Directory,&Data.PatternFileName[a][0]);
		ReadPattern(&s[0],slname,FileMode,a);
	}
	for(a = 0;a < EF_OBJECT_PATTERNMAX;a ++){
		sprintf(&s[0],"%s%s",Directory,&Data.ObjectFileName[a][0]);
		ReadObject(&s[0],slname,FileMode,a);
	}
}

//---�t�B�[���h�Ŏg���p�^�[�����T�[�t�F�C�X�ɃZ�b�g����
void eiMap::SetSurface(void)
{
	int a;

	for(a = 0;a < EF_PATTERN_PAGEMAX;a ++){
		SetPatternSurface(a);
	}
	for(a = 0;a < EF_OBJECT_PATTERNMAX;a ++){
		SetObjectSurface(a);
	}
}

void eiMap::SetPatternSurface(int page)
{
	int tx,ty;

	if(page >= 4)
		return;

	//�T�[�t�F�C�X�ɃR�s�[
	tx = EF_PATTERN_PAGESIZE * page;
	ty = (tx / 20) * EF_PATTERN_SIZE;//20:Surface width
	tx = tx % 20;

	eiCellSetSurface( &fCell[page * EF_PATTERN_PAGESIZE],
		tx * EF_PATTERN_SIZE,EF_PATTERN_DDOFFSET_Y + ty,
		32,32,EF_PATTERN_PAGESIZE,2);
}

void eiMap::SetObjectSurface(int number)
{
	int tx,ty;

	//�T�[�t�F�C�X�ɃR�s�[
	tx = EF_OBJECT_PATTERNSIZE * number;
	ty = ((tx / 20) * EF_PATTERN_SIZE) + EF_OBJECT_DDOFFSET;//20:Surface width
	tx = tx % 20;

	eiCellSetSurface(&fObjectPattern[number * EF_OBJECT_PATTERNSIZE],//&fCell[number * EF_OBJECT_PATTERNSIZE + EF_OBJECT_PATTERNOFFSET],
		tx * EF_PATTERN_SIZE,ty,
		32,32,EF_OBJECT_PATTERNSIZE,EF_OBJECT_SURFACEPAGE);
}

//---�p�^�[����ǂݍ���
int eiMap::ReadPattern(EISTR *name,EISTR *slname,int mode,int page)
{
	int a;

	if(page >= 4)
		return 1;

	//�ǂݍ���
	a = eiCellReadPattern(fCell,name,slname,mode,
		page * EF_PATTERN_PAGESIZE,EF_PATTERN_PAGESIZE,
		32,32);
	
	if(!a)
		return 0;
	//---�t�@�C�������R�s�[
	{
		static eistr directory[_MAX_PATH];
		sprintf(directory,"%s",name);
		eistr *start = &directory[0],*end = &directory[strlen(directory) - 1];
		while(start < end){
			if(*end == '\\'){
				*end = 0;
				sprintf(&Data.PatternFileName[page][0],"%s",(end + 1));
				break;
			}
			end --;
		}
		if(start == end){
			sprintf(&Data.PatternFileName[page][0],"%s",name);
		}
	}
//	sprintf(&Data.PatternFileName[page][0],"%s",name);

	//�T�[�t�F�C�X�ɃR�s�[
	SetPatternSurface(page);

/*	tx = EF_PATTERN_PAGESIZE * page;
	ty = (tx / 20) * EF_PATTERN_SIZE;//20:Surface width
	tx = tx % 20;

	eiCellSetSurface(&fCell[page * EF_PATTERN_PAGESIZE],
		tx * EF_PATTERN_SIZE,EF_PATTERN_DDOFFSET_Y + ty,
		32,32,EF_PATTERN_PAGESIZE);*/

	return 1;
}

//---�I�u�W�F�N�g�p�^�[���ǂݍ���
int eiMap::ReadObject(EISTR *name,EISTR *slname,int mode,int number)
{
	int a;

	//�ǂݍ���
	a = eiCellReadPattern(fObjectPattern,//fCell,
		name,slname,mode,
		number * EF_OBJECT_PATTERNSIZE, //+ EF_OBJECT_PATTERNOFFSET,
		EF_OBJECT_PATTERNSIZE,
		32,32);
	
	if(!a)
		return 0;
	//---�t�@�C�������R�s�[
	//---�t�@�C�������R�s�[
	{
		static eistr directory[_MAX_PATH];
		sprintf(directory,"%s",name);
		eistr *start = &directory[0],*end = &directory[strlen(directory) - 1];
		while(start < end){
			if(*end == '\\'){
				*end = 0;
				sprintf(&Data.ObjectFileName[number][0],"%s",(end + 1));
				break;
			}
			end --;
		}
		if(start == end){
			sprintf(&Data.ObjectFileName[number][0],"%s",name);
		}
	}
//	sprintf(&Data.ObjectFileName[number][0],"%s",name);

	SetObjectSurface(number);
/*	//�T�[�t�F�C�X�ɃR�s�[
	tx = EF_OBJECT_PATTERNSIZE * number;
	ty = ((tx / 20) * EF_PATTERN_SIZE) + EF_OBJECT_DDOFFSET;//20:Surface width
	tx = tx % 20;

	eiCellSetSurface(&fObjectPattern[number * EF_OBJECT_PATTERNSIZE],//&fCell[number * EF_OBJECT_PATTERNSIZE + EF_OBJECT_PATTERNOFFSET],
		tx * EF_PATTERN_SIZE,ty,
		32,32,EF_OBJECT_PATTERNSIZE,EF_OBJECT_SURFACEPAGE);*/

	return 1;
}

//---�v���[�����폜
int eiMap::DeletePlane(int MapNumber,int PlaneNumber)
{
	LPPLANE_DATA lpplane = &Data.Map[MapNumber]->Plane[PlaneNumber];

	if(IsUsedPlane(MapNumber,PlaneNumber)){
		if(lpplane->hData){
			eiFreeMemory(lpplane->hData);

			lpplane->hData = 0;
			lpplane->lpData = 0;
		}
		Data.Map[MapNumber]->UsePlane[PlaneNumber] = 0;

		return 1;
	}

	return 0;
}

//---�}�b�v���폜
int eiMap::DeleteMap(int MapNumber)
{
	int a;
	LPMAP_DATA lpmap = Data.Map[MapNumber];

	if(IsUsedMap(MapNumber)){
		//---�v���[������
		for(a = 0;a < EF_PLANE_MAX;a ++){
			if(IsUsedPlane(MapNumber,a)){//lpmap->UsePlane[a]){
				DeletePlane(MapNumber,a);
				lpmap->UsePlane[a] = 0;
			}
		}
		//---�I�u�W�F�N�g����
		for(a = 0;a < EF_OBJECT_MAX;a ++){
			Data.Map[MapNumber]->lpObject[a].Delete();
		}
		eiMemoryDeletePointerForDebug(Data.Map[MapNumber]->lpObject);
		delete [] Data.Map[MapNumber]->lpObject;

		//---�t���b�O�N���A
		Data.UseMap[MapNumber] = 0;

		eiFreeMemory(Data.eiMemMap[MapNumber]);
		Data.eiMemMap[MapNumber] = NULL;

		return 1;
	}

	return 0;
}

//---�\���̂��폜
int eiMap::Delete(void)
{
	int a;

	for(a = 0;a < EF_MAP_MAX;a ++){
		if(IsUsedMap(a)){
			DeleteMap(a);
		}
	}
	
	Init();
	return 1;
}

//---�v���[�����쐬
int eiMap::CreatePlane(int MapNumber,int PlaneNumber,
							  int xSize,int ySize,int trans /* = 0*/)
{
	LPMAP_DATA lpmap = Data.Map[MapNumber];

	if(!IsPlaneRange(PlaneNumber))
		return 0;
	if(lpmap->UsePlane[PlaneNumber])
		return 0;

	LPPLANE_DATA plane = &lpmap->Plane[PlaneNumber];
	//�v���[���i���o�[�̃t���O�����Ă�
	plane->xSize = xSize;
	plane->ySize = ySize;
	plane->ScrollSpeed = 100;//�X�N���[���X�s�[�h:100�W�� //32;
	plane->Mode = 0;
	plane->Show = 1;//---������

	plane->DataSize = (xSize * ySize) * sizeof(EFMAP)   +1024;//�O�̂���
	//�������[�m��
	plane->hData = eiAllocMemory(plane->DataSize);
	if(!plane->hData){
		return 0;
	}
	plane->lpData = (LPEFMAP)eiLockMemory(plane->hData);
	memset(plane->lpData,0,plane->DataSize);
	if(!plane->lpData){
		//�������[�̃|�C���^�����炦�Ȃ�������
		eiFreeMemory(plane->hData);
		return 0;
	}

	lpmap->UsePlane[PlaneNumber] = 1;

	if(trans){
		//---�����F�ŃN���A
		int a;
		for(a = 0;a < plane->DataSize / 2;a ++){
			*(EFMAP *)(plane->lpData + a) = (EFMAP)EF_PATTERN_TRANS;
		}
	}
	return 1;
}

//---�V�����}�b�v�����
int eiMap::Create(int MapNumber,int xSize /*= - 1*/,int ySize/* = -1*/)
{
	int a;

	if(!IsMapRange(MapNumber))
		return 0;
	if(IsUsedMap(MapNumber) && xSize != -1)
		return 0;

	//---�������[�m��
	EIMEMORY eiMem = eiAllocMemory(sizeof(MAP_DATA));
	if(!eiMem)
		return 0;
	Data.Map[MapNumber] = (MAP_DATA *)eiLockMemory(eiMem);
	memset(Data.Map[MapNumber],0,sizeof(MAP_DATA));
	Data.eiMemMap[MapNumber] = eiMem;

	//�I�u�W�F�N�g������
	Data.Map[MapNumber]->lpObject = new eiMapObject[EF_OBJECT_MAX];
	eiMemorySetPointerForDebug(Data.Map[MapNumber]->lpObject);

	if(Data.Map[MapNumber]->lpObject == NULL){
		//---�m�ۂł��Ȃ�������
		eiFreeMemory(eiMem);
		return 0;
	}
	for(a = 0;a < EF_OBJECT_MAX;a ++){
		Data.Map[MapNumber]->lpObject[a].Init();
	}

	if(xSize != -1){
		//---�T�C�Y�w�肪����΃v���[���P�����
		if(!CreatePlane(MapNumber, 1 , xSize , ySize)){
			eiFreeMemory(eiMem);
			return 0;
		}
	}

	//�}�b�v�i���o�[�̃t���O�����Ă�
	Data.UseMap[MapNumber] = 1;
	//�A�N�e�B�u�}�b�v
	if(xSize != -1){
		//---�T�C�Y�w�肪�����
		SetActiveMap(MapNumber);
	}

	return 1;
}

//---�p�^�[����������
int eiMap::Put(int x,int y,int PlaneNumber,int Pattern)
{
	EFMAP Old;
	LPPLANE_DATA lpplane = &Data.Map[Data.ActiveMap]->Plane[PlaneNumber];

	if(!IsUsedPlane(GetActiveMap(),PlaneNumber))
		return 0;

	if(x < 0 || x >= lpplane->xSize
		|| y < 0 || y >= lpplane->ySize)
		return 0;

	Old = *(EFMAP *)(lpplane->lpData + x + (y * lpplane->xSize));
	*(EFMAP *)(lpplane->lpData + x + (y * lpplane->xSize)) = (EFMAP)Pattern;

	return (int)Old;
}

//---�p�^�[���ǂݍ���
int eiMap::Get(int x,int y,int PlaneNumber)
{
	EFMAP Ptn;
	LPPLANE_DATA lpplane = &Data.Map[Data.ActiveMap]->Plane[PlaneNumber];

	if(!IsUsedPlane(GetActiveMap(),PlaneNumber))
		return 0;

	if(x < 0 || x >= lpplane->xSize
		|| y < 0 || y >= lpplane->ySize)
		return 0;

	Ptn = *(EFMAP *)(lpplane->lpData + x + (y * lpplane->xSize));

	return (int)Ptn;
}

//---�I�u�W�F�N�g�̍ő吔
ei_s32 eiMap::GetMaxObject(void)
{
	return MaxObject;
}

//---�C���f�b�N�X�I�u�W�F�N�g�̍ő吔
ei_s32 eiMap::GetMaxObjectIndex(void)
{
	return MaxObjectIndex;
}

//---�C���f�b�N�X�ɒǉ�
void eiMap::AddObjectIndex(int number)
{
	int a;

	for(a = 0;a < EF_OBJECT_MAX;a ++){
		if(ObjectIndex[a] == -1){
			ObjectIndex[a] = number;
			if(MaxObjectIndex - 1 < a)
				MaxObjectIndex = a + 1;
			return;
		}
	}
}

//---�C���f�b�N�X�̏�����
void eiMap::InitObjectIndex(void)
{
	int a;

	//---�I�u�W�F�N�g�ő�l
	MaxObject = 0;
	MaxObjectIndex = 0;
	//---�I�u�W�F�N�g�C���f�b�N�X
	for(a = 0;a < EF_OBJECT_MAX;a ++){
		ObjectIndex[a] = -1;
	}
}

//---�C���f�b�N�X����폜
void eiMap::DeleteObjectIndex(int number)
{
	int a;

	for(a = 0;a < EF_OBJECT_MAX;a ++){
		if(ObjectIndex[a] == number){
			ObjectIndex[a] = -1;
			//---�ǂ����Q�[�����ɃI�u�W�F�N�g���ւ邱�Ƃ͂Ȃ�����
			//---�ő�l�͂ق��Ƃ�^^;
		}
	}
}

//---�I�u�W�F�N�g�̃|�C���^�𓾂�
int eiMap::GetObjectPointer(int Number,eiMapObject *lpObject)
{
	if(Data.Map[GetActiveMap()]->lpObject[Number].GetFlag() == 0){
		lpObject = NULL;
		return 0;
	}

	lpObject = &Data.Map[GetActiveMap()]->lpObject[Number];

	return 1;
}

//---�u�����N�I�u�W�F�N�g�𓾂�
int eiMap::GetBlankObject(int start /*= 0*/)
{
	int a;

	for(a = start;a < EF_OBJECT_MAX;a ++){
		if(Data.Map[GetActiveMap()]->lpObject[a].GetFlag() == 0){
			return a;
		}
	}
	for(a = 0;a < start;a ++){
		if(Data.Map[GetActiveMap()]->lpObject[a].GetFlag() == 0){
			return a;
		}
	}

	return EF_NOBLANK;
}

//---�I�u�W�F�N�g���Z�b�g
int eiMap::SetObject(int number,int x,int y,int plane,
							int kind/* = 0*/,int mode /*= 0*/)
{
	Data.Map[GetActiveMap()]->lpObject[number].Create(number);
	Data.Map[GetActiveMap()]->lpObject[number].SetPos(x,y,plane);

	//---�I�u�W�F�N�g�ő�l�X�V
	if(MaxObject < number)
		MaxObject = number;
	AddObjectIndex(number);

	return number;
}

//---�I�u�W�F�N�g���폜
int eiMap::DeleteObject(int number)
{
	Data.Map[GetActiveMap()]->lpObject[number].Delete();
	DeleteObjectIndex(number);

	return 1;
}

//---�I�u�W�F�N�g�̃X�e�[�^�X��ݒ�
//int eiMap::SetObjectStatus(int Number,int GraphicNumber,int Status,int Direction,int Plane)
int eiMap::SetObjectStatus(int Number,LPOBJECT_DATA lpData)
{
	int map = GetActiveMap();

	if(!Data.Map[map]->lpObject[Number].GetFlag())
		return 0;

	if(lpData)
		Data.Map[map]->lpObject[Number].SetData(lpData);

	return 1;
}

//---�I�u�W�F�N�g�̃X�e�[�^�X�𓾂�
//int eiMap::GetObjectStatus(int Number,int *lpGraphicNumber,int *lpStatus,int *lpDirection,int *lpPlane)
int eiMap::GetObjectStatus(int Number,LPOBJECT_DATA lpData)
{
	int map = GetActiveMap();

	if(!Data.Map[map]->lpObject[Number].GetFlag())
		return 0;

	if(lpData)
		Data.Map[map]->lpObject[Number].GetData(lpData);

	return 1;
}

//---�w�肵�����W�ɃI�u�W�F�N�g�����邩
int eiMap::IsObject(int x,int y,int plane /*= -1*/,int map /* = -1 */)
{
	int a,b = 0;

	if(map == -1)
		map = GetActiveMap();

	for(a = 0;a < EF_OBJECT_MAX;a ++){
		if(Data.Map[map]->lpObject[a].IsThere(x,y,plane)){
			b ++;
			return a;
		}
	}

	return EF_NOFIND;
}

//---�A�N�e�B�u�I�u�W�F�N�g�̐ݒ�
int eiMap::SetActiveObject(int Number)
{
	int Old = Data.Map[GetActiveMap()]->ActiveObject;

	Data.Map[GetActiveMap()]->ActiveObject = Number;

	return Old;
}

int eiMap::GetActiveObject(void)
{
	return Data.Map[GetActiveMap()]->ActiveObject;
}

//---�I�u�W�F�N�g�̃A�j���[�V����
int eiMap::DoObjectAnime(int frame/* = 1*/)
{
	int a,map = GetActiveMap();

	for(a = 0;a < EF_OBJECT_MAX;a ++){
		if(Data.Map[map]->lpObject[a].GetFlag()){
			Data.Map[map]->lpObject[a].DoAnime(frame);
		}
	}

	return 1;
}

//---�A�j���̈ʒu
int eiMap::SetObjectAnimePos(int Number,int Pos/* = 1*/)
{
	int map = GetActiveMap();

	if(!Data.Map[map]->lpObject[Number].GetFlag())
		return 0;

	return Data.Map[map]->lpObject[Number].SetAnimePos(Pos);
}

int eiMap::GetObjectAnimePos(int Number)
{
	int map = GetActiveMap();

	if(!Data.Map[map]->lpObject[Number].GetFlag())
		return 0;

	return Data.Map[map]->lpObject[Number].GetAnimePos();
}

//---�I�u�W�F�N�g�̃|�C���^�𓾂�
eiMapObject* eiMap::GetObject(int Number,int MapNumber /*= -1*/)
{
	int map = MapNumber;
	
	if(MapNumber == -1)
		map = GetActiveMap();

	if(Number < 0 || Number >= EF_OBJECT_MAX)
		return NULL;
	return &Data.Map[map]->lpObject[Number];
}

//---�A�N�e�B�u�}�b�v�ݒ�
int eiMap::SetActiveMap(int MapNumber)
{
	int a = Data.ActiveMap,b;

	Data.ActiveMap = MapNumber;

	//---�C���f�b�N�X�����
	InitObjectIndex();
	for(b = 0;b < EF_OBJECT_MAX;b ++){
		if(Data.Map[Data.ActiveMap]->lpObject[b].Data.Flag){
			//---�I�u�W�F�N�g����������A�ő�l������ɍ��킹��
			MaxObject = b;
			//---�C���f�b�N�X�o�^
			AddObjectIndex(b);
		}
	}

	return a;
}

//---�A�N�e�B�u�}�b�v�擾
int eiMap::GetActiveMap(void)
{
	return Data.ActiveMap;
}

//---�X�N���[���̊�ƂȂ�v���[����ݒ�
int eiMap::SetBasePlane(int PlaneNumber)
{
	int Old = GetBasePlane();

	Data.BasePlane = PlaneNumber;

	return Old;
}
int eiMap::GetBasePlane(void)
{
	return Data.BasePlane;
}

//---�v���[���X�N���[���X�s�[�h�ݒ�
int eiMap::SetPlaneSpeed(int MapNumber,int PlaneNumber,int Speed)
{
	int speed = GetPlaneSpeed(MapNumber,PlaneNumber);

	if(IsUsedPlane(MapNumber,PlaneNumber)){
		if(Speed < 0 || Speed > 1000)
			Speed = 0;

		Data.Map[MapNumber]->Plane[PlaneNumber].ScrollSpeed = Speed;
	}

	return speed;
}
//---
int eiMap::GetPlaneSpeed(int MapNumber,int PlaneNumber)
{
	if(IsUsedPlane(MapNumber,PlaneNumber)){
		return Data.Map[MapNumber]->Plane[PlaneNumber].ScrollSpeed;
	}
	return 0;
}

//---�u�����N�v���[����Ԃ�
int eiMap::GetBlankPlaneNumber(int MapNumber)
{
	int a;

	for(a = 0;a < EF_PLANE_MAX;a ++){
		if(!IsUsedPlane(MapNumber,a))
			return a;
	}

	return EF_MAP_NOBLANK;
}

//---�u�����N�}�b�v��Ԃ�
int eiMap::GetBlankMapNumber(void)
{
	int a;

	for(a = 0;a < EF_MAP_MAX;a ++){
		if(!IsUsedMap(a))
			return a;
	}

	return EF_MAP_NOBLANK;
}

//---�v���[���T�C�Y
int eiMap::xGetPlaneSize(int MapNumber,int PlaneNumber)
{
	if(IsUsedPlane(MapNumber,PlaneNumber)){
		return Data.Map[MapNumber]->Plane[PlaneNumber].xSize;
	}
	return 0;
}
//---
int eiMap::yGetPlaneSize(int MapNumber,int PlaneNumber)
{
	if(IsUsedPlane(MapNumber,PlaneNumber)){
		return Data.Map[MapNumber]->Plane[PlaneNumber].ySize;
	}
	return 0;
}

//---�}�b�v�̃T�C�Y�i�v���[���P�̃T�C�Y��Ԃ��j
int eiMap::xGetMapSize(int MapNumber)
{
	if(IsUsedMap(MapNumber)){
		return xGetPlaneSize(MapNumber,1);
	}
	return 0;
}
//---
int eiMap::yGetMapSize(int MapNumber)
{
	if(IsUsedMap(MapNumber)){
		return yGetPlaneSize(MapNumber,1);
	}
	return 0;
}

//---�̈�O�̓h��Ԃ��p�^�[��
int eiMap::SetBlankPattern(int MapNumber,int Number)
{
	if(IsMapRange(MapNumber)){
		int Old = Data.Map[MapNumber]->BlankPattern;

		Data.Map[MapNumber]->BlankPattern = Number;

		return Old;
	}
	return 0;
}
int eiMap::GetBlankPattern(int MapNumber)
{
	if(IsMapRange(MapNumber)){
		return Data.Map[MapNumber]->BlankPattern;
	}
	return 0;
}

//---�O���[�v�̖��O
void eiMap::SetGroupName(EISTR *Name)
{
	sprintf(&Data.GroupName[0],"%s",Name);
}
//---
EISTR *eiMap::GetGroupName(void)
{
	return &Data.GroupName[0];
}
//---�}�b�v�̖��O���Z�b�g
void eiMap::SetMapName(int MapNumber,EISTR *Name)
{
	sprintf(&Data.Map[MapNumber]->Name[0],"%s",Name);
}
//---
EISTR *eiMap::GetMapName(int MapNumber)
{
	return &Data.Map[MapNumber]->Name[0];
}

//---�g���Ă���v���[�����H
int eiMap::IsUsedPlane(int MapNumber,int PlaneNumber)
{
	if(IsMapRange(MapNumber) && IsPlaneRange(PlaneNumber)){
		if(IsUsedMap(MapNumber))
			return Data.Map[MapNumber]->UsePlane[PlaneNumber];
	}
	return 0;
}

//---�g���Ă���}�b�v���H
int eiMap::IsUsedMap(int MapNumber)
{
	if(IsMapRange(MapNumber)){
		return Data.UseMap[MapNumber];
	}
	return 0;
}

//--�������͈͓��̃}�b�v�i���o�[���H
int eiMap::IsMapRange(int MapNumber)
{
	if(MapNumber < 0 || MapNumber >= EF_MAP_MAX)
		return 0;
	return 1;
}

//--�������͈͓��̃v���[���i���o�[���H
int eiMap::IsPlaneRange(int PlaneNumber)
{
	if(PlaneNumber < 0 || PlaneNumber >= EF_PLANE_MAX)
		return 0;
	return 1;
}

//---�p�^�[���̑���
int eiMap::SetPatternStatus(int Number,int Status)
{
	if(Number >= EF_PATTERN_MAX)
		return 0;

	int Old = Data.Pattern[Number].Status;

	Data.Pattern[Number].Status = Status;

	return Old;
}

int eiMap::GetPatternStatus(int Number)
{
	if(Number == EF_PATTERN_TRANS)
		return 0;
	if(Number >= EF_PATTERN_MAX)
		return 0;

	return Data.Pattern[Number].Status;
}

//---�}�b�v�p�^�[�����A�j���[�V��������
int eiMap::DoPatternAnime(int frame /*= 1*/)
{
	int number,ptn;

	for(number = 0;number < EF_PATTERN_MAX;number ++){
		//---���݂̃A�j���[�V�����p�^�[��
		ptn = Data.Pattern[number].AnimeUpdata;
		//---�J�E���g�𑝂₷
		Data.Pattern[number].AnimeCount += (ei_s16)frame;

		if(Data.Pattern[number].AnimeCount >= Data.Pattern[ptn].AnimeWait){
			Data.Pattern[number].AnimeCount = 0;
			//---���̃A�j���[�V����
			Data.Pattern[number].AnimeUpdata = Data.Pattern[ptn].NextAnime;
		}
	}

	return 1;
}

//---�p�^�[���f�[�^���Z�b�g
int eiMap::SetPatternData(int Number,MAP_PATTERNDATA *lpData)
{
	if(Number >= EF_PATTERN_MAX)
		return 0;

	memcpy(&Data.Pattern[Number],lpData,sizeof(MAP_PATTERNDATA));

	return 1;
}

int eiMap::GetPatternData(int Number,MAP_PATTERNDATA *lpData)
{
	if(Number >= EF_PATTERN_MAX){
		return 0;
	}

	memcpy(lpData,&Data.Pattern[Number],sizeof(MAP_PATTERNDATA));

	return 1;
}

//---�A�N�e�B�u�p�^�[���ݒ�
int eiMap::SetActivePattern(int Number)
{
	int a = Data.ActivePattern;

	Data.ActivePattern = Number;

	return a;
}

//---�A�N�e�B�u�p�^�[��
int eiMap::GetActivePattern(void)
{
	return Data.ActivePattern;
}

//---�G�o���^�C�v
int eiMap::GetEnemyType(void)
{
	return Data.EnemyType;
}

int eiMap::SetEnemyType(int type)
{
	int a = Data.EnemyType;

	Data.EnemyType = type;

	return a;
}

//---�G�o���}�b�v
int eiMap::GetEnemyArea(int x,int y)
{
	int data;

	data = Data.Map[GetActiveMap()]->EnemyArea[x / EF_MAP_ENEMYAREASIZE][y / EF_MAP_ENEMYAREASIZE];

	return data;
}
