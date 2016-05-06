/*-----------------------------------------------------------

   eiLibray
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   eiPal.cpp ...eiPalette Class

-----------------------------------------------------------*/

//---------------------------
//	eiPalette
//	パレットを扱うクラス
//---------------------------

eiPalette::eiPalette(void)
{
	eimemset(&Palette[0],0,sizeof(Palette));//sizeof(PALETTEENTRY)*256);
}

eiPalette::~eiPalette(void)
{
}

//---パレット初期化
int eiPalette::Create(int col)
{
	ColorBits = col;
	PaletteNumber = 256;

	Palette[255].peRed = 255;
	Palette[255].peGreen = 255;
	Palette[255].peBlue = 255;

	if((::eiSystem.ScreenMode & DIRECTDRAW_MODE) == 0){
		return 1;
	}
//-------------------------------------------------------------
#ifdef EI_RUNWINDOWS
#ifdef EIUSE_DIRECTDRAW
	return DDPalette.Create();
#else
	return 1;
#endif
#endif
//-------------------------------------------------------------
}

int eiPalette::Release(void)
{
#ifdef EI_RUNWINDOWS
#ifdef EIUSE_DIRECTDRAW
	DDPalette.Release();
#endif
#endif
	return 1;
}

//---パレットの一括設定
void eiPalette::SetEntries(int start,int end)
{
//-------------------------------------------------------------
#ifdef EI_RUNWINDOWS
#ifdef EIUSE_DIRECTDRAW
	if(::eiSystem.ScreenMode & DIRECTDRAW_MODE){
		DDPalette.SetEntries(&Palette[0]);
	}
#endif
#endif
//-------------------------------------------------------------
}

//---パレットセット
void eiPalette::Set(int num,int red,int green,int blue,int mode/* = 1*/)
{
	Palette[num].peRed = (ei_u8)(red & 0xff);
	Palette[num].peGreen = (ei_u8)(green & 0xff);
	Palette[num].peBlue = (ei_u8)(blue & 0xff);

//-------------------------------------------------------------
#ifdef EI_RUNWINDOWS
#ifdef EIUSE_DIRECTDRAW
	if(::eiSystem.ScreenMode & DIRECTDRAW_MODE){
		DDPalette.Set(num,red,green,blue,mode);
	} else {
	}
#endif
#endif
//-------------------------------------------------------------
}

DWORD eiPalette::MakeTextRGB(int red,int green,int blue)
{
	if(::eiUseDirectText){
		return RGB(red,green,blue);
	} else {
		return MakeRGB(red,green,blue);
	}
}

DWORD eiPalette::ToTextRGB(int num)
{
	if(::eiUseDirectText){
		return RGB(Palette[num].peRed,Palette[num].peGreen,Palette[num].peBlue);
	} else {
		return ToRGB(num);
	}
}

//---パレットをＲＧＢに変換
DWORD eiPalette::ToRGB(int num)
{
	DWORD rgb,Mask[3] = {0xff,0xff,0xff};

	if(::eiSystem.ColorBit <= 8)
		//---変換する必要がなければ
		return num;

	rgb = //---red
		( (((DWORD)Palette[num].peRed >> (8 - ::eiSystem.RedBit)) & Mask[0])
		<< (::eiSystem.RedShift))
		//---green
		| ( (((DWORD)Palette[num].peGreen >> (8 - ::eiSystem.GreenBit)) & Mask[1])
		<< (::eiSystem.GreenShift))
		//---blue
		| ( (((DWORD)Palette[num].peBlue >> (8 - ::eiSystem.BlueBit)) & Mask[2])
		<< (::eiSystem.BlueShift));

	return rgb;

	return 1;
}

//---パレットをＲＧＢに変換
DWORD eiPalette::MakeRGB(int red,int green,int blue)
{
	DWORD rgb,Mask[3] = {0xff,0xff,0xff};

	if(::eiSystem.ColorBit <= 8)
		//---変換する必要がなければ
		return 0;

	rgb = //---red
		( (((DWORD)red >> (8 - ::eiSystem.RedBit)) & Mask[0])
		<< (::eiSystem.RedShift))
		//---green
		| ( (((DWORD)green >> (8 - ::eiSystem.GreenBit)) & Mask[1])
		<< (::eiSystem.GreenShift))
		//---blue
		| ( (((DWORD)blue >> (8 - ::eiSystem.BlueBit)) & Mask[2])
		<< (::eiSystem.BlueShift));

	return rgb;

	return 1;
}

//---ＤＩＢからパレットを設定
int eiPalette::ReadDIB(LPSTR name,LPSTR slname,int mode)
{
	int a;
	eiDib ed;
	
	if(ed.Read(name,slname,mode) == FALSE)
		return 0;
	
	for(a = 0; a < 256;a ++){
		Palette[a].peRed   = ed.lpRGB[a].rgbRed;
		Palette[a].peGreen = ed.lpRGB[a].rgbGreen;
		Palette[a].peBlue  = ed.lpRGB[a].rgbBlue;
		Palette[a].peFlags = 0;
	}

	SetEntries(0,PaletteNumber);

	ed.Delete();

	return 1;
}

//---フェードイン
void eiPalette::Fadein(int wait,int count,int efect)
{
//-------------------------------------------------------------
#ifdef EI_RUNWINDOWS
#ifdef EIUSE_DIRECTDRAW
	if(::eiSystem.ScreenMode & DIRECTDRAW_MODE){
		if(efect == 0)
			DDPalette.Fadein(wait,count,0);
		else if(efect == 1)
			DDPalette.Fadein(wait,count,1);
	}
#endif
#endif
//-------------------------------------------------------------
}

//---フェードアウト
void eiPalette::Fadeout(int wait,int count,int efect)
{
//-------------------------------------------------------------
#ifdef EI_RUNWINDOWS
#ifdef EIUSE_DIRECTDRAW
	if(::eiSystem.ScreenMode & DIRECTDRAW_MODE){
		if(efect == 0)
			DDPalette.Fadeout(wait,count,0);
		else if(efect == 1)
			DDPalette.Fadeout(wait,count,1);
	}
#endif
#endif
//-------------------------------------------------------------
}

//---パレットを一時的に黒くする
void eiPalette::Black(void)
{
//-------------------------------------------------------------
#ifdef EI_RUNWINDOWS
#ifdef EIUSE_DIRECTDRAW
	if(::eiSystem.ScreenMode & DIRECTDRAW_MODE){
		DDPalette.Black();
	}
#endif
#endif
//-------------------------------------------------------------
}
