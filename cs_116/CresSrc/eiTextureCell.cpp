/*-----------------------------------------------------------

   eiLibray
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   eiTextureCell.cpp ...eiTextureClass(Direct3D)

-----------------------------------------------------------*/

eiTextureCell::eiTextureCell(void) : eiCell()
{
	Init();
}

eiTextureCell::~eiTextureCell()
{
}

//---初期化
void eiTextureCell::Init(int color /*= 0*/)
{
#ifdef CLASS_MEMORY_TEST
	INIT_MEMORY_TEST(hDumy2);
#endif

	lpd3dTexture = NULL;
	TextureSurfaceColor = color;
	if(color){
		TextureSurfaceColor = color;
	}

	if(eiSurface[0].Color != 0 && color == 0){
		//---サーフェイスが存在していれば、それと同じビット数
		TextureSurfaceColor = eiSurface[0].Color;
//		if(TextureSurfaceColor > 24)
//			TextureSurfaceColor = 24;
	}
}

void eiTextureCell::SetTextureSurfaceColor(int color)
{
	TextureSurfaceColor = color;
}

//---テクスチャを作成
int eiTextureCell::CreateTexture(int sx,int sy,int color)
{
	Create(sx,sy,color);

#ifdef CLASS_MEMORY_TEST
	ALLOC_MEMORY_TEST(hDumy2);
#endif
	return 1;
}

//---テクスチャ用のサーフェイスを作成
int eiTextureCell::CreateSurface(void)
{
	//---テクスチャーサーフェイスを確保
	if(!Texture.Create(Data.xSize,Data.ySize,
		ESCREATE_TEXTURE | (eiDDInfo.Use3DHEL ? (ESCREATE_TEMPTEXTURE | ESCREATE_SYSTEMMEMORY): 0),
		NULL,TextureSurfaceColor/*Data.Color*/)){
		eiDebugWriteFile("(eiTextureCell) CreateSurface faild\n");
		return 0;
	}

	//---テクスチャインターフェイス
	lpd3dTexture = Texture.GetDirect3DTexture();
	if(!lpd3dTexture){
		eiDebugWriteFile("(eiTextureCell) Texture.GetDirect3DTexture failed\n");
		return 0;
	}

	return 1;
}

//---パレットを作る
int eiTextureCell::CreatePalette(void)
{
	int a;

	if(Palette.Create(0)){
		static PALETTEENTRY pe[256];

		for(a = 0;a < 256;a ++){
			pe[a].peFlags = PC_NOCOLLAPSE | PC_RESERVED;
			pe[a].peRed = dib.lpRGB[a].rgbRed;
			pe[a].peGreen = dib.lpRGB[a].rgbGreen;
			pe[a].peBlue = dib.lpRGB[a].rgbBlue;
		}
		Palette.SetEntries(&pe[0]);
	}

	return 1;
}

//---コピーする
int eiTextureCell::LoadFromSurface(eiDDSurface *pSurface,RECT *pRect)
{
	HRESULT result;
	RECT DstRect = {0,0,Data.xSize,Data.ySize};

//	if((result = Texture.lpSurface->Blt(NULL, pSurface->lpSurface, NULL, DDBLT_WAIT, NULL )) != DD_OK){
	if((result = Texture.lpSurface->Blt(&DstRect, pSurface->lpSurface, pRect, DDBLT_WAIT, NULL )) != DD_OK){
		eiDebugWriteFile("(eiTextureCell) LoadFromSurface fail\n");
		return 0;
	}

	return 1;
}

int eiTextureCell::CreateFromSurface(int sx,int sy,int color,eiDDSurface *pSurface,RECT *pSrcRect)
{
	CreateTexture(sx,sy,color);
	CreateSurface();
	if(Data.Color <= 8){//TextureSurfaceColor/*8*/){
		if(CreatePalette()){
			Texture.lpSurface->SetPalette(Palette.lpPalette);
		}
	}

	return LoadFromSurface(pSurface,pSrcRect);
}

//---テクスチャーをロードする
int eiTextureCell::Load(int trans /*= 1*/)
{
	int surface_color = TextureSurfaceColor;

	if(!Data.CreateFlag){
		eiDebugWriteFile("(eiTextureCell) Not Created!!\n");
		return 0;
	}

	eiDDSurface TempSurface;

	//---テクスチャーサーフェイスを確保
	if(!CreateSurface()){
		return 0;
	}
	Texture.SetSrcBltColorKey(16,16);
//	eiDebugWriteFile("(eiTextureCell) Texture.Create Succes\n");

	//---エミュレーションでなければテンポラリサーフェイスを作る
	if(!TempSurface.Create(Data.xSize,Data.ySize,
		ESCREATE_TEXTURE | ESCREATE_TEMPTEXTURE | ESCREATE_SYSTEMMEMORY,
		&Texture,TextureSurfaceColor)){
		Texture.Release();
		eiDebugWriteFile("::::::::::::1\n");
		return 0;
	}
//	eiDebugWriteFile("(eiTextureCell) TempSurface.Create Succes\n");

	if(Data.Color <= 8 && TempSurface.Color <= 8){
		//---パレット
		if(CreatePalette()){
			TempSurface.lpSurface->SetPalette(Palette.lpPalette);
			Texture.lpSurface->SetPalette(Palette.lpPalette);
		}
	}

	//---テンポラリサーフェイスへコピーする
	dib.CopyToDDSurface(&TempSurface,0,0,NULL,trans);
//	eiDebugWriteFile("(eiTextureCell) dib.CopyToDDSurface end\n");

	RECT rect = {0,0,Data.xSize,Data.ySize};

	if(!LoadFromSurface(&TempSurface,&rect)){
		eiDebugWriteFile("(eiTextureCell) load fail\n");
	}

	//---いらなくなったのを解放
	TempSurface.Release();

	//---サーフェイスセット
	Data.SurfaceFlag = 1;
	Data.SurfaceNumber = 2;
	pDDSurface = &Texture;

//	eiDebugWriteFile("(eiTextureCell) Create succes\n");

	return 1;
}

int eiTextureCell::ReleaseTexture(void)
{
	Texture.Release();
	Palette.Release();
//	eiDebugWriteFile("(eiTextureCell) Texture.Release\n");

	eiCell::Release();

#ifdef CLASS_MEMORY_TEST
	RELEASE_MEMORY_TEST(hDumy2);
#endif

	return 1;
}

//---テクスチャのハンドル
D3DTEXTUREHANDLE eiTextureCell::GetHandle(void)
{
	return 0;
}
