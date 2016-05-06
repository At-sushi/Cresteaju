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
	//---アニメーション・ステータス設定
	for(a = 0;a < EF_PATTERN_MAX;a ++){
		//---アニメーション無し
		Data.Pattern[a].AnimeUpdata = Data.Pattern[a].NextAnime = (ei_s16)a;
		Data.Pattern[a].AnimeCount = 0;
		Data.Pattern[a].AnimeWait = 30;
		Data.Pattern[a].Status = 0;
	}

	InitObjectIndex();
}

//---マップをファイルに書き込む
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

	//---圧縮フラッグ
	Data.Compress = 0;//1
	
	//---書き込むファイルをオープン
	File.Open(name,EI_FILE_WRITE | EI_FILE_BINARY);
	if(Data.Compress == 0){
		//---そのまま
		pfile = &File;
	} else {
		//---圧縮
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

	//---Map構造体書き込み
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
			//---使われているMAP_DATAを書き込み
			pfile->Write(Data.Map[a],sizeof(MAP_DATA),1);
			for(b = 0;b < EF_PLANE_MAX;b ++){
				if(IsUsedPlane(a,b)){
					//---プレーンが使われていれば
					pfile->Write(Data.Map[a]->Plane[b].lpData,1,
						Data.Map[a]->Plane[b].DataSize);
				}
			}
			//---オブジェクトのデータを書き込み
			for(b = 0;b < EF_OBJECT_MAX;b ++){
//				Data.Map[a]->lpObject[b].Save(fp);
				Data.Map[a]->lpObject[b].Save(pfile);
			}
		}
	}

	if(Data.Compress){
		//---圧縮なら、バッファーを書き込む
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

//---ファイルからマップを読み込む
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

	//---ディレクトリがあったらそれを取得
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
	//---古いのを消す
	Delete();
	Init();
	//---グローバル情報コピー
	if(directory[0] != NULL)
		sprintf(Directory,"%s",directory);
	FileMode = mode;
	if(slname != NULL)
		sprintf(SLinkFileName,"%s",slname);

	memset(&Index[0],0,sizeof(Index));

	//---情報
	file.Read(&Header[0],sizeof(EISTR),sizeof(Header));
	file.Read(&Format[0],sizeof(EISTR),sizeof(Format));
	if(strcmp(&Header[0],"eiMapFormat")){
		//---違ったら
		file.Close();
		return 0;
	}
	a = atoi(Format);
	if(a > 1){
		//---フォーマットタイプがサポート外だったら
		file.Close();
		return 0;
	}
	//---Index
	file.Read(&IndexSize,sizeof(int),1);
	file.Read(&Index[0],sizeof(int),IndexSize);

	//---Map構造体読み込み
//	MAPOLD old;
//	file.Read(&old,sizeof(old),1);
//	memcpy(&Data,&old,sizeof(old));
	if(a == 0){
		//---無圧縮
		file.Read(&Data,sizeof(Data),1);
	} else {
		//---圧縮
		eb.ReadCompressFile(&file);
//		eb.ReadCompressFile(file.fp);
		if(!eb.Decompress(&Data)){
			//---マップが壊れている！
//			eiDebugWriteFile("no map data(1)!!\n");
			file.Close();
			eb.FreeBuffer();
			return 0;
		}
		eb.FreeBuffer();
	}

	if(Data.Compress){
		//---圧縮されているのなら
		eb.ReadCompressFile(&file);
//		eb.ReadCompressFile(file.fp);
		MemoryFile.Alloc(eb.Buffer.OriginalSize + 4096);
		if(!eb.Decompress(MemoryFile.GetMemory())){
			//---マップが壊れている！
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
			//---一度クリアして作り直す
			Data.UseMap[a] = 0;
			Create(a);
			//---ポインタ保存
			lpob = Data.Map[a]->lpObject;
			//---使われているMAP_DATAを読み込み
			pfile->Read(Data.Map[a],sizeof(MAP_DATA),1);
			Data.Map[a]->lpObject = lpob;
			for(b = 0;b < EF_PLANE_MAX;b ++){
				if(IsUsedPlane(a,b)){
					//---フラグを一時クリア
					speed = GetPlaneSpeed(a,b);
					Data.Map[a]->UsePlane[b] = 0;
					//---プレーンを作る
					CreatePlane(a,b,
						Data.Map[a]->Plane[b].xSize,Data.Map[a]->Plane[b].ySize);
					SetPlaneSpeed(a,b,speed);
					//---プレーンデータ読み込み
					pfile->Read(Data.Map[a]->Plane[b].lpData,1,
						Data.Map[a]->Plane[b].DataSize);
				}
			}
			//---オブジェクトのデータを読み込み
			for(b = 0;b < EF_OBJECT_MAX;b ++){
				if(Data.Map[a]->lpObject[b].Load(pfile)){
				}
			}
		}
	}

	file.Close();
	eb.FreeBuffer();
	MemoryFile.Free();

	//---マップパターンを読み込む
	for(a = 0;a < EF_PATTERN_PAGEMAX;a ++){
		sprintf(&s[0],"%s%s",directory,&Data.PatternFileName[a][0]);
		ReadPattern(&s[0],slname,mode,a);
	}
	for(a = 0;a < EF_OBJECT_PATTERNMAX;a ++){
		sprintf(&s[0],"%s%s",directory,&Data.ObjectFileName[a][0]);
		ReadObject(&s[0],slname,mode,a);
	}

	//---アニメーション・ステータス設定
	for(a = 0;a < EF_PATTERN_MAX;a ++){
		Data.Pattern[a].AnimeCount = 0;
	}

	//---アクティブマップを0にする
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

//---パターンをリロード
void eiMap::ReloadPattern(void)
{
	int a;
	eistr s[80],*slname;

	if(SLinkFileName[0] == NULL)
		slname = NULL;
	else
		slname = SLinkFileName;

	//---マップパターンを読み込む
	for(a = 0;a < EF_PATTERN_PAGEMAX;a ++){
		sprintf(&s[0],"%s%s",Directory,&Data.PatternFileName[a][0]);
		ReadPattern(&s[0],slname,FileMode,a);
	}
	for(a = 0;a < EF_OBJECT_PATTERNMAX;a ++){
		sprintf(&s[0],"%s%s",Directory,&Data.ObjectFileName[a][0]);
		ReadObject(&s[0],slname,FileMode,a);
	}
}

//---フィールドで使うパターンをサーフェイスにセットする
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

	//サーフェイスにコピー
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

	//サーフェイスにコピー
	tx = EF_OBJECT_PATTERNSIZE * number;
	ty = ((tx / 20) * EF_PATTERN_SIZE) + EF_OBJECT_DDOFFSET;//20:Surface width
	tx = tx % 20;

	eiCellSetSurface(&fObjectPattern[number * EF_OBJECT_PATTERNSIZE],//&fCell[number * EF_OBJECT_PATTERNSIZE + EF_OBJECT_PATTERNOFFSET],
		tx * EF_PATTERN_SIZE,ty,
		32,32,EF_OBJECT_PATTERNSIZE,EF_OBJECT_SURFACEPAGE);
}

//---パターンを読み込み
int eiMap::ReadPattern(EISTR *name,EISTR *slname,int mode,int page)
{
	int a;

	if(page >= 4)
		return 1;

	//読み込み
	a = eiCellReadPattern(fCell,name,slname,mode,
		page * EF_PATTERN_PAGESIZE,EF_PATTERN_PAGESIZE,
		32,32);
	
	if(!a)
		return 0;
	//---ファイル名をコピー
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

	//サーフェイスにコピー
	SetPatternSurface(page);

/*	tx = EF_PATTERN_PAGESIZE * page;
	ty = (tx / 20) * EF_PATTERN_SIZE;//20:Surface width
	tx = tx % 20;

	eiCellSetSurface(&fCell[page * EF_PATTERN_PAGESIZE],
		tx * EF_PATTERN_SIZE,EF_PATTERN_DDOFFSET_Y + ty,
		32,32,EF_PATTERN_PAGESIZE);*/

	return 1;
}

//---オブジェクトパターン読み込み
int eiMap::ReadObject(EISTR *name,EISTR *slname,int mode,int number)
{
	int a;

	//読み込み
	a = eiCellReadPattern(fObjectPattern,//fCell,
		name,slname,mode,
		number * EF_OBJECT_PATTERNSIZE, //+ EF_OBJECT_PATTERNOFFSET,
		EF_OBJECT_PATTERNSIZE,
		32,32);
	
	if(!a)
		return 0;
	//---ファイル名をコピー
	//---ファイル名をコピー
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
/*	//サーフェイスにコピー
	tx = EF_OBJECT_PATTERNSIZE * number;
	ty = ((tx / 20) * EF_PATTERN_SIZE) + EF_OBJECT_DDOFFSET;//20:Surface width
	tx = tx % 20;

	eiCellSetSurface(&fObjectPattern[number * EF_OBJECT_PATTERNSIZE],//&fCell[number * EF_OBJECT_PATTERNSIZE + EF_OBJECT_PATTERNOFFSET],
		tx * EF_PATTERN_SIZE,ty,
		32,32,EF_OBJECT_PATTERNSIZE,EF_OBJECT_SURFACEPAGE);*/

	return 1;
}

//---プレーンを削除
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

//---マップを削除
int eiMap::DeleteMap(int MapNumber)
{
	int a;
	LPMAP_DATA lpmap = Data.Map[MapNumber];

	if(IsUsedMap(MapNumber)){
		//---プレーン消去
		for(a = 0;a < EF_PLANE_MAX;a ++){
			if(IsUsedPlane(MapNumber,a)){//lpmap->UsePlane[a]){
				DeletePlane(MapNumber,a);
				lpmap->UsePlane[a] = 0;
			}
		}
		//---オブジェクト消去
		for(a = 0;a < EF_OBJECT_MAX;a ++){
			Data.Map[MapNumber]->lpObject[a].Delete();
		}
		eiMemoryDeletePointerForDebug(Data.Map[MapNumber]->lpObject);
		delete [] Data.Map[MapNumber]->lpObject;

		//---フラッグクリア
		Data.UseMap[MapNumber] = 0;

		eiFreeMemory(Data.eiMemMap[MapNumber]);
		Data.eiMemMap[MapNumber] = NULL;

		return 1;
	}

	return 0;
}

//---構造体を削除
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

//---プレーンを作成
int eiMap::CreatePlane(int MapNumber,int PlaneNumber,
							  int xSize,int ySize,int trans /* = 0*/)
{
	LPMAP_DATA lpmap = Data.Map[MapNumber];

	if(!IsPlaneRange(PlaneNumber))
		return 0;
	if(lpmap->UsePlane[PlaneNumber])
		return 0;

	LPPLANE_DATA plane = &lpmap->Plane[PlaneNumber];
	//プレーンナンバーのフラグをたてる
	plane->xSize = xSize;
	plane->ySize = ySize;
	plane->ScrollSpeed = 100;//スクロールスピード:100標準 //32;
	plane->Mode = 0;
	plane->Show = 1;//---見せる

	plane->DataSize = (xSize * ySize) * sizeof(EFMAP)   +1024;//念のため
	//メモリー確保
	plane->hData = eiAllocMemory(plane->DataSize);
	if(!plane->hData){
		return 0;
	}
	plane->lpData = (LPEFMAP)eiLockMemory(plane->hData);
	memset(plane->lpData,0,plane->DataSize);
	if(!plane->lpData){
		//メモリーのポインタがもらえなかったら
		eiFreeMemory(plane->hData);
		return 0;
	}

	lpmap->UsePlane[PlaneNumber] = 1;

	if(trans){
		//---透明色でクリア
		int a;
		for(a = 0;a < plane->DataSize / 2;a ++){
			*(EFMAP *)(plane->lpData + a) = (EFMAP)EF_PATTERN_TRANS;
		}
	}
	return 1;
}

//---新しいマップを作る
int eiMap::Create(int MapNumber,int xSize /*= - 1*/,int ySize/* = -1*/)
{
	int a;

	if(!IsMapRange(MapNumber))
		return 0;
	if(IsUsedMap(MapNumber) && xSize != -1)
		return 0;

	//---メモリー確保
	EIMEMORY eiMem = eiAllocMemory(sizeof(MAP_DATA));
	if(!eiMem)
		return 0;
	Data.Map[MapNumber] = (MAP_DATA *)eiLockMemory(eiMem);
	memset(Data.Map[MapNumber],0,sizeof(MAP_DATA));
	Data.eiMemMap[MapNumber] = eiMem;

	//オブジェクト初期化
	Data.Map[MapNumber]->lpObject = new eiMapObject[EF_OBJECT_MAX];
	eiMemorySetPointerForDebug(Data.Map[MapNumber]->lpObject);

	if(Data.Map[MapNumber]->lpObject == NULL){
		//---確保できなかったら
		eiFreeMemory(eiMem);
		return 0;
	}
	for(a = 0;a < EF_OBJECT_MAX;a ++){
		Data.Map[MapNumber]->lpObject[a].Init();
	}

	if(xSize != -1){
		//---サイズ指定があればプレーン１を作る
		if(!CreatePlane(MapNumber, 1 , xSize , ySize)){
			eiFreeMemory(eiMem);
			return 0;
		}
	}

	//マップナンバーのフラグをたてる
	Data.UseMap[MapNumber] = 1;
	//アクティブマップ
	if(xSize != -1){
		//---サイズ指定があれば
		SetActiveMap(MapNumber);
	}

	return 1;
}

//---パターン書き込み
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

//---パターン読み込み
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

//---オブジェクトの最大数
ei_s32 eiMap::GetMaxObject(void)
{
	return MaxObject;
}

//---インデックスオブジェクトの最大数
ei_s32 eiMap::GetMaxObjectIndex(void)
{
	return MaxObjectIndex;
}

//---インデックスに追加
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

//---インデックスの初期化
void eiMap::InitObjectIndex(void)
{
	int a;

	//---オブジェクト最大値
	MaxObject = 0;
	MaxObjectIndex = 0;
	//---オブジェクトインデックス
	for(a = 0;a < EF_OBJECT_MAX;a ++){
		ObjectIndex[a] = -1;
	}
}

//---インデックスから削除
void eiMap::DeleteObjectIndex(int number)
{
	int a;

	for(a = 0;a < EF_OBJECT_MAX;a ++){
		if(ObjectIndex[a] == number){
			ObjectIndex[a] = -1;
			//---どうせゲーム中にオブジェクトがへることはないから
			//---最大値はほっとく^^;
		}
	}
}

//---オブジェクトのポインタを得る
int eiMap::GetObjectPointer(int Number,eiMapObject *lpObject)
{
	if(Data.Map[GetActiveMap()]->lpObject[Number].GetFlag() == 0){
		lpObject = NULL;
		return 0;
	}

	lpObject = &Data.Map[GetActiveMap()]->lpObject[Number];

	return 1;
}

//---ブランクオブジェクトを得る
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

//---オブジェクトをセット
int eiMap::SetObject(int number,int x,int y,int plane,
							int kind/* = 0*/,int mode /*= 0*/)
{
	Data.Map[GetActiveMap()]->lpObject[number].Create(number);
	Data.Map[GetActiveMap()]->lpObject[number].SetPos(x,y,plane);

	//---オブジェクト最大値更新
	if(MaxObject < number)
		MaxObject = number;
	AddObjectIndex(number);

	return number;
}

//---オブジェクトを削除
int eiMap::DeleteObject(int number)
{
	Data.Map[GetActiveMap()]->lpObject[number].Delete();
	DeleteObjectIndex(number);

	return 1;
}

//---オブジェクトのステータスを設定
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

//---オブジェクトのステータスを得る
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

//---指定した座標にオブジェクトがあるか
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

//---アクティブオブジェクトの設定
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

//---オブジェクトのアニメーション
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

//---アニメの位置
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

//---オブジェクトのポインタを得る
eiMapObject* eiMap::GetObject(int Number,int MapNumber /*= -1*/)
{
	int map = MapNumber;
	
	if(MapNumber == -1)
		map = GetActiveMap();

	if(Number < 0 || Number >= EF_OBJECT_MAX)
		return NULL;
	return &Data.Map[map]->lpObject[Number];
}

//---アクティブマップ設定
int eiMap::SetActiveMap(int MapNumber)
{
	int a = Data.ActiveMap,b;

	Data.ActiveMap = MapNumber;

	//---インデックスを作る
	InitObjectIndex();
	for(b = 0;b < EF_OBJECT_MAX;b ++){
		if(Data.Map[Data.ActiveMap]->lpObject[b].Data.Flag){
			//---オブジェクトがあったら、最大値をそれに合わせる
			MaxObject = b;
			//---インデックス登録
			AddObjectIndex(b);
		}
	}

	return a;
}

//---アクティブマップ取得
int eiMap::GetActiveMap(void)
{
	return Data.ActiveMap;
}

//---スクロールの基準となるプレーンを設定
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

//---プレーンスクロールスピード設定
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

//---ブランクプレーンを返す
int eiMap::GetBlankPlaneNumber(int MapNumber)
{
	int a;

	for(a = 0;a < EF_PLANE_MAX;a ++){
		if(!IsUsedPlane(MapNumber,a))
			return a;
	}

	return EF_MAP_NOBLANK;
}

//---ブランクマップを返す
int eiMap::GetBlankMapNumber(void)
{
	int a;

	for(a = 0;a < EF_MAP_MAX;a ++){
		if(!IsUsedMap(a))
			return a;
	}

	return EF_MAP_NOBLANK;
}

//---プレーンサイズ
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

//---マップのサイズ（プレーン１のサイズを返す）
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

//---領域外の塗りつぶしパターン
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

//---グループの名前
void eiMap::SetGroupName(EISTR *Name)
{
	sprintf(&Data.GroupName[0],"%s",Name);
}
//---
EISTR *eiMap::GetGroupName(void)
{
	return &Data.GroupName[0];
}
//---マップの名前をセット
void eiMap::SetMapName(int MapNumber,EISTR *Name)
{
	sprintf(&Data.Map[MapNumber]->Name[0],"%s",Name);
}
//---
EISTR *eiMap::GetMapName(int MapNumber)
{
	return &Data.Map[MapNumber]->Name[0];
}

//---使われているプレーンか？
int eiMap::IsUsedPlane(int MapNumber,int PlaneNumber)
{
	if(IsMapRange(MapNumber) && IsPlaneRange(PlaneNumber)){
		if(IsUsedMap(MapNumber))
			return Data.Map[MapNumber]->UsePlane[PlaneNumber];
	}
	return 0;
}

//---使われているマップか？
int eiMap::IsUsedMap(int MapNumber)
{
	if(IsMapRange(MapNumber)){
		return Data.UseMap[MapNumber];
	}
	return 0;
}

//--正しい範囲内のマップナンバーか？
int eiMap::IsMapRange(int MapNumber)
{
	if(MapNumber < 0 || MapNumber >= EF_MAP_MAX)
		return 0;
	return 1;
}

//--正しい範囲内のプレーンナンバーか？
int eiMap::IsPlaneRange(int PlaneNumber)
{
	if(PlaneNumber < 0 || PlaneNumber >= EF_PLANE_MAX)
		return 0;
	return 1;
}

//---パターンの属性
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

//---マップパターンをアニメーションする
int eiMap::DoPatternAnime(int frame /*= 1*/)
{
	int number,ptn;

	for(number = 0;number < EF_PATTERN_MAX;number ++){
		//---現在のアニメーションパターン
		ptn = Data.Pattern[number].AnimeUpdata;
		//---カウントを増やす
		Data.Pattern[number].AnimeCount += (ei_s16)frame;

		if(Data.Pattern[number].AnimeCount >= Data.Pattern[ptn].AnimeWait){
			Data.Pattern[number].AnimeCount = 0;
			//---次のアニメーション
			Data.Pattern[number].AnimeUpdata = Data.Pattern[ptn].NextAnime;
		}
	}

	return 1;
}

//---パターンデータをセット
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

//---アクティブパターン設定
int eiMap::SetActivePattern(int Number)
{
	int a = Data.ActivePattern;

	Data.ActivePattern = Number;

	return a;
}

//---アクティブパターン
int eiMap::GetActivePattern(void)
{
	return Data.ActivePattern;
}

//---敵出現タイプ
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

//---敵出現マップ
int eiMap::GetEnemyArea(int x,int y)
{
	int data;

	data = Data.Map[GetActiveMap()]->EnemyArea[x / EF_MAP_ENEMYAREASIZE][y / EF_MAP_ENEMYAREASIZE];

	return data;
}
