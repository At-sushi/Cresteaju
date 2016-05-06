

static eistr 
	*TexForest[] = {"kusa1.acf","kusa2.acf","kusa3.acf",NULL},
	*TexTown[] = {"kusa1.acf","michi1.acf",NULL},
	*TexBill1[] = {"yuka1.acf",NULL},
	*TexDangeon1[] = {"tuchi1.acf","tuchi2.acf","tuchi3.acf",NULL},
	*TexIseki1[] = {"yuka1.acf","yuka1.acf","yuka1.acf",NULL},
	*TexIseki2[] = {"tuchi1.acf","tuchi2.acf","tuchi3.acf",NULL},
	*TexIseki3[] = {"yuka3_1.acf",NULL},
	*TexIshidatami[] = {"ishidatami1.acf","ishidatami1.acf","ishidatami1.acf",NULL},
	*TexTatemono1[] = {"yuka1.acf","yuka1.acf","yuka1.acf",NULL},
	*TexDesert[] = {"suna1.acf","suna2.acf",NULL},
	*TexSnow[] = {"snow1.acf","snow2.acf",NULL},
	*TexIllidia1[] = {"Ill_yuka1.acf","Ill_yuka2.acf",NULL},
	*TexKokyu[] = {"kokyu_yuka1.acf","kokyu_yuka2.acf",NULL}
;

static eistr **TextureKindTable[] = 
{
	TexForest,TexForest,TexForest,TexDesert,
	TexForest,TexForest,TexSnow,TexForest,
	TexDangeon1,TexForest,TexForest,TexForest,
	TexForest,TexForest,TexForest,TexTown  ,
	TexIseki1,TexIseki2,TexIshidatami,TexForest,

	//---20
	TexTatemono1,TexIseki3,TexDangeon1,TexTatemono1,
	TexForest,TexDangeon1,TexForest,TexBill1,
	//28
	TexDangeon1,TexForest,TexForest,TexDangeon1,
	//32
	TexIseki3,TexIllidia1,TexKokyu,TexKokyu,
	NULL
};
static eistr *BGFileTable[] =
{
	///0
	"FieldBG.acf","ForestBG.acf","","DesertBG.acf",
	"MountBG.acf","ForestBG.acf","SouthBG.acf","",
	"Dangeon1BG.acf","ForestBG.acf","ForestBG.acf","ForestBG.acf",
	"TownBG.acf","ForestBG.acf","ForestBG.acf","TownNightBG.acf",
	"Iseki1BG.acf","Iseki2BG.acf","GesuiBG.acf","",
	//20
	"BuildingBG.acf","HozonSochiBG.acf","MountBG.acf","Iseki1BG.acf",
	"EastBG.acf","TuriaBG.acf","GiedieBG.acf","TownBG.acf",
	//28
	"MountBG.acf","BeizBG.acf","JuleClaraBG.acf","Iseki1BG.acf",

	//32
	"HozonSochiBG.acf","IllidiaBG.acf","KokyuBG.acf","LastBattleBG.acf",
	NULL
};

static ei_s32 FieldTown[BATTLEFIELD_MAX_X][BATTLEFIELD_MAX_Y] = 
{
	{0,0,0,0, 0,0,0,1, 1,0,0,0},
	{0,0,0,0, 0,0,0,1, 1,0,0,0},
	{0,0,0,0, 0,0,0,1, 1,0,0,0},
	{0,0,0,0, 0,0,0,1, 1,0,0,0},

	{0,0,0,0, 0,0,0,1, 1,0,0,0},
	{0,0,0,0, 0,0,0,1, 1,0,0,0},
	{0,0,0,0, 0,0,0,1, 1,0,0,0},
	{0,0,0,0, 0,0,0,1, 1,0,0,0},

	{0,0,0,0, 0,0,0,1, 1,0,0,0},
	{0,0,0,0, 0,0,0,1, 1,0,0,0},
	{0,0,0,0, 0,0,0,1, 1,0,0,0},
	{0,0,0,0, 0,0,0,1, 1,0,0,0},
};

static ei_s32 *BtFieldMappingTable[] = 
{
	NULL,&FieldTown[0][0]
};


static ei_s32 BtFieldMappingFlag[] = 
{
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	1,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0
};// 0:random 1:map

/*
 0:街道 ,  1:草原  ,  2:荒れ地 ,  3:砂漠,
 4:山   ,  5:森    ,  6:雪原 ,    7:
 8:洞窟1,  9:洞窟2 , 10:洞窟3  , 11:洞窟4
12:街  , 13:塔2   , 14:山道   ,
15:街夜 , 16:遺跡1 , 17:遺跡2  , 18:下水道 19:
20:建物 , 21:遺跡3 , 22:中央山脈, 23:遺跡4（火炎竜）
24:イーストプレーン , 25:ツーリア , 26:ジーダイ , 27:建国宣言
28:山道（地面荒れ地）,29:バイツ周辺 ,30:ユールクレイラ 31:流砂の遺跡
32:イリーディア（中）,33:イリーディア（外）,34:イリーディア（皇宮）35:ラストバトル
*/
static ei_s32 FieldBGTable[] = 
{
//---0:火炎竜 2:ラストバトル
	 0,23,35,0,0, 0,0,0,0,0,
//---10-14
	  0,  5,  0,  0,  20,
//---15-19
	 15,  5,  0,  5,  5,
//---20-24
	 8,   0,  0,  8,  5,
//---25-29
	 16, 20,  0, 16, 17,
//---30-34
	 4,  18,  27,  8,  5,
//---35-39
	 21, 8,  0,22, 5,

//---40-44
	 0 , 12,  5, 8, 8,
//---45-49
	 4 , 16, 17, 8, 5,

//---50-54
	 0 ,   5,  5, 8, 5,
//---55-59
	 8 ,   8,  16, 8, 5,
//---60-64
	 8 ,   8,  16,18, 18,
//---65-69
	 8 ,   8,  16, 8, 26,
//---70-74
	 21,  21,  16, 8, 18,
//---75-79
	 21,  28,  16, 8, 5,

//---80-84
	 20,  31,  16, 21, 18,
//---85-89
	 21,  21,  16, 8, 18,

//---90-94
	 21,  21,  32, 32, 32,
//---95-99
	 34,  21,  16, 8, 18,
};

//---３Ｄオブジェクト生成
CRBATINIT_API int crbatCreate3DObject(CR_BATTLEINFO *pInfo,int retry)
{
//---フィールドタイプ判別
	int field_number = crfieldGetMapNumber(),field_tip = em->Get(ef->xGet(),ef->yGet(),ef->GetPlayerPlane());

//	pInfo->MapNumber = field_number;
	field_number = pInfo->MapNumber;

	if(field_number == 10){
		//---フィールドタイプ
		pInfo->FieldType = 0;
		switch(pInfo->AreaNumber){
		case 7:
		case 8:
			//---イーストプレーン
			pInfo->FieldType = 24;
			break;
		case 9:
			//---ツーリア
			pInfo->FieldType = 25;
			break;
		case 10:
			//---ジーダイ
			pInfo->FieldType = 26;
			break;
		case 11:
		case 17:
			//---バイツ周辺
			pInfo->FieldType = 29;
			break;
		case 13:
		case 16:
			//---ユールクレイラ
			pInfo->FieldType = 30;
			break;
		case 14:
			//---雪原
			pInfo->FieldType = 6;
			break;
			//---砂漠
		case 15:
			pInfo->FieldType = 3;
			break;
		default:
			pInfo->FieldType = 0;
			break;
		}
	} else {
		//---ダンジョン
		pInfo->FieldType = -1;
		if(field_number == 76){
			//---神の山
			if(pInfo->SceneNumber == 1 || pInfo->SceneNumber == 5){
				pInfo->FieldType = 8;
			}
		} else if(field_number == 80 && pInfo->SceneNumber == 0){
			//---大神殿外
			pInfo->FieldType = 12;
		} else if(field_number == 92){
			//---イリーディア
			if(pInfo->SceneNumber == 5){
				pInfo->FieldType = 33;
			}
		} else if(field_number == 94){
			//---イリーディア
			if(pInfo->SceneNumber == 0 || pInfo->SceneNumber == 1){
				pInfo->FieldType = 33;
			}
		}
	}
	int field_type = pInfo->FieldType;

	if(field_type == -1){
		//---ＢＧタイプを決定
		field_type = FieldBGTable[pInfo->MapNumber];
	}
	if(pInfo->MapNumber == 64){
		//---エターナルの建物
		if(pInfo->SceneNumber >= 2){
			field_type = 20;
		}
	}
//-----------------------------------------
	int a,alpha = 255,texture_num;
	eistr **table = TextureKindTable[field_type];
	eistr str[80];
	RECT rect;

	//---ＢＧ読み込み
	{
		sprintf(str,"%s%s",CR_DATADIR4,BGFileTable[field_type]);
		BattleBackgroundCell[0].ReadFile(str,CR_DATAFILE4,crdataGetFileMode());
		RECT rect1 = {0,0,640,256},rect2 = {0,0,320,128},rect3 = {0,0,640,128};

//		BattleBackgroundCell[0].SetSurface(&rect3,3);
		BattleBackgroundCell[0].SetSurface(&rect2,2,0);//trans = 0;

		(eiGetSurfacePointer() + 2)->PutExtend(
			(eiGetSurfacePointer() + 3),
			0,0,
			&rect2,DDBLT_WAIT,2.00,2.00);
		(eiGetSurfacePointer() + 2)->PutExtend(
			(eiGetSurfacePointer() + 3),
			0,0,
			&rect2,DDBLT_WAIT,2.00,2.00);
		BattleBackgroundCell[0].Data.SurfaceNumber = 3;
		BattleBackgroundCell[0].Data.rectSurface =
		BattleBackgroundCell[0].Data.rectClip = rect1;
		BattleBackgroundCell[0].pDDSurface = (eiGetSurfacePointer() + 3);
	}

	//-------
	BattleFieldMaterial.Create();
	BattleParticleMaterial.Create();
	BattleParticleMaterial.SetDeffuseColor(255,255,255,255);
	eiDebugWriteFile("(crbatCreate3DObject) BattleFieldMaterial.Create();\n");
	if(crdataGetIniFile()->AlphaBattleField)
		alpha = 192;
	BattleFieldMaterial.SetDeffuseColor(255,255,255,alpha);
	eiDebugWriteFile("(crbatCreate3DObject) BattleFieldMaterial.SetDeffuseColor\n");
	BattleFieldMaterial.Set();
	eiDebugWriteFile("(crbatCreate3DObject)BattleFieldMaterial.Set()\n");

	//---マテリアルをセット
	if(eid3d->Begin(0)){
		eid3d->SetMaterial(&BattleFieldMaterial);
		eid3d->End(0);
	}
	eiDebugWriteFile("(crbatCreate3DObject) eid3d->SetMaterial(&BattleFieldMaterial)\n");

	//---テクスチャー読み込み
	for(a = 0, texture_num = 0;table[a] != NULL;a ++, texture_num ++){
		sprintf(str,"%s%s",CR_DATADIR4,table[a]);
		BattleFieldCell[a].ReadFile(str,CR_DATAFILE4,crdataGetFileMode());
		eiDebugWriteFile("(crbatCreate3DObject) BattleFieldCell[0].ReadFile\n");
		BattleFieldCell[a].Init(16);
		BattleFieldCell[a].Load();
		//---テクスチャを通常サーフェイスにもセット
		rect.left = a * 32;
		rect.top = 256 + 64;
		rect.right = rect.left + 32;
		rect.bottom = rect.top + 32;
		BattleFieldCell[a].SetSurface(&rect);
	}
	//---影テクスチャ読み込み
	if(crdataGetIniFile()->BattleShadow){
		ShadowCell.ReadFile(CR_DATADIR4"shadow.acf",CR_DATAFILE4,crdataGetFileMode());
		ShadowCell.Init(16);
		ShadowCell.Load();
	}

	//---ドローリストクリア
	crbatClearDrawingList();

	//---頂点バッファー
	vbSrc.Create(0,BATTLE_DRAWINGLISTMAX);
	vbSrc.Set(8.5,1.0,8.5);
	vbDest.Create(1,BATTLE_DRAWINGLISTMAX);

	//---バトルフィールド生成
	if(!retry){
		int x,y;
		for(y = 0;y < BATTLEFIELD_VERTEXCOUNT_Y;y ++){
			for(x = 0;x < BATTLEFIELD_VERTEXCOUNT_X;x ++){
				if(BtFieldMappingFlag[field_type] == 0){
					BattleField[x][y].TextureNumber = eiRnd(texture_num);
				} else {
					BattleField[x][y].TextureNumber = 
						*(BtFieldMappingTable[BtFieldMappingFlag[field_type]] + y * BATTLEFIELD_MAX_X + x);
				}
			}
		}
	}

	return 1;
}
