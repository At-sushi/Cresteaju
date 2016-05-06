/*-----------------------------------------------------------

   eiLibray
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   eiDDPalette.cpp ...DirectDrawPalette

-----------------------------------------------------------*/

eiDDPalette::eiDDPalette(void)
{
	eimemset(&PaletteEntries[0],0,sizeof(PaletteEntries));//sizeof(PALETTEENTRY) * 256);
	eimemset(&KeepEntries[0],0,sizeof(KeepEntries));//sizeof(PALETTEENTRY) * 256);
	eimemset(&BackEntries[0],0,sizeof(BackEntries));//sizeof(PALETTEENTRY) * 256);
	WaitCount = 0;

	lpPalette = NULL;
#ifdef CLASS_MEMORY_TEST
	INIT_MEMORY_TEST(hDumy);
#endif
}

int eiDDPalette::Create(int mode /*= 1*/)
{
	HDC hdc;
	static RGBQUAD rgb[256];
	LOGPALETTE_256 logp;
	static PALETTEENTRY pe[256];
	int a;

	PaletteMode = mode;

#ifdef CLASS_MEMORY_TEST
	ALLOC_MEMORY_TEST(hDumy);
#endif
	//---パレット作成

	memset(&rgb[0],0,sizeof(rgb));
	memset(&pe[0],0,sizeof(pe));

	if(PaletteMode){
		//---システムパレット読み込み
		hdc = GetDC(NULL);

		logp.palVersion = 0x300;
		logp.palNumEntries = 256;
		GetSystemPaletteEntries(hdc,0,10,&logp.palPalEntry[0]);
		for(a = 0;a < 10;a ++) {
			rgb[a].rgbRed = logp.palPalEntry[a].peRed;
			rgb[a].rgbGreen = logp.palPalEntry[a].peGreen;
			rgb[a].rgbBlue = logp.palPalEntry[a].peBlue;
			rgb[a].rgbReserved = 0;
		}
		GetSystemPaletteEntries(hdc, 246, 10, &logp.palPalEntry[246]);
		for(a = 246;a < 256;a ++) {
			rgb[a].rgbRed=logp.palPalEntry[a].peRed;
			rgb[a].rgbGreen=logp.palPalEntry[a].peGreen;
			rgb[a].rgbBlue=logp.palPalEntry[a].peBlue;
			rgb[a].rgbReserved = 0;
		}
		ReleaseDC(NULL,hdc);

		for(a = 0;a < 256;a++){
			pe[a].peRed = rgb[a].rgbRed;
			pe[a].peGreen = rgb[a].rgbGreen;
			pe[a].peBlue = rgb[a].rgbBlue;
			pe[a].peFlags = PC_NOCOLLAPSE | PC_RESERVED;
		}
		if((::eiSystem.ScreenMode & DIRECTDRAW_WINDOW) != 0){
			//フルスクリーンでなければ
			for(a = 0; a < 10;a ++){
				//Windowsのシステムパレット
				pe[a].peFlags = PC_EXPLICIT;
				pe[a].peRed = (ei_u8)a;
				pe[a].peGreen = 0;
				pe[a].peBlue = 0;

				pe[a+246].peFlags = PC_EXPLICIT;
				pe[a+246].peRed = (ei_u8)(a+246);
				pe[a+246].peGreen = 0;
				pe[a+246].peBlue = 0;
			}
		}
	}

	eiDDInfo.lpDD->CreatePalette(DDPCAPS_8BIT | DDPCAPS_ALLOW256,
			pe,&lpPalette,NULL);

	if(lpPalette == NULL)
		return 0;

	if(lpPalette && mode == 1){
		eiSurface[0].lpSurface->SetPalette(lpPalette);
		eiSurface[1].lpSurface->SetPalette(lpPalette);

		eiDDInfo.lpDDPalette = lpPalette;
	}

	return 1;
}

int eiDDPalette::Release(void)
{
//	eiDebugWriteFile("(eiDDPalette::Release) Start\n");
#ifdef CLASS_MEMORY_TEST
	RELEASE_MEMORY_TEST(hDumy);
#endif

	if(lpPalette != NULL){
		if(lpPalette->Release() > 0){
			eiDebugWriteFile("(eiDDPalette::Release) Fail\n");
		}
		lpPalette = NULL;
		eiDebugWriteFile("(eiDDPalette::Release) lpPalette->Release().\n");
	}
//	eiDebugWriteFile("(eiDDPalette::Release) End\n");

	return 1;
}

//---パレットを一括セット
void eiDDPalette::SetEntries(LPPALETTEENTRY pe)
{
	int a;

	for(a = 0;a < 256;a ++){
		pe[a].peFlags = PC_NOCOLLAPSE | PC_RESERVED;
	}
	if(PaletteMode){
		if((::eiSystem.ScreenMode & DIRECTDRAW_WINDOW) != 0){
			for(a = 0;a < 10;a ++){
				//Windowsのシステムパレット
				pe[a].peFlags = PC_EXPLICIT;
				pe[a].peRed = 0;
				pe[a].peGreen = 0;
				pe[a].peBlue = 0;

				pe[a+246].peFlags = PC_EXPLICIT;
				pe[a+246].peRed = 0;
				pe[a+246].peGreen = 0;
				pe[a+246].peBlue = 0;
			}
		}
	}

	memcpy(&PaletteEntries[0],pe,sizeof(PALETTEENTRY)*256);

	if(!lpPalette)
		return;

	lpPalette->SetEntries(0,0,256,&PaletteEntries[0]);
}

//---パレットをセット
int eiDDPalette::Set(int number,int red,int green,int blue,int mode)
{
	if((::eiSystem.ScreenMode & DIRECTDRAW_WINDOW) != 0
		&& (number <= 9 || number >= 246))
		return 0;

	PaletteEntries[number].peRed = (ei_u8)red;
	PaletteEntries[number].peGreen = (ei_u8)green;
	PaletteEntries[number].peBlue = (ei_u8)blue;
	PaletteEntries[number].peFlags = PC_NOCOLLAPSE | PC_RESERVED;

	if(mode == 1){
		if(!lpPalette)
			return 0;
		lpPalette->SetEntries(0,number,1,&PaletteEntries[number]);
	}
	return 0;
}

//---フェードアウト
void eiDDPalette::Fadeout(int wait,int count,int efect)
{
	int a,b;

	if(!lpPalette)
		return;

	memcpy(&BackEntries[0],&PaletteEntries[0],sizeof(PALETTEENTRY)*256);

	if(efect == 0){
		for(a = 0;a < count;a ++){
			Wait.Reset();
			for(b = 0;b < 256;b ++){
				if(BackEntries[b].peRed < count){
					BackEntries[b].peRed = 0;
				} else if(BackEntries[b].peRed > 0){
					BackEntries[b].peRed -= (count);
				}
				if(BackEntries[b].peGreen < count){
					BackEntries[b].peGreen = 0;
				} else if(BackEntries[b].peGreen > 0){
					BackEntries[b].peGreen -= (count);
				}
				if(BackEntries[b].peBlue < count){
					BackEntries[b].peBlue = 0;
				} else if(BackEntries[b].peBlue > 0){
					BackEntries[b].peBlue -= (count);
				}
			}
			if(!((com_key & KEY_Q) && a != 15 && debug == 1)){ 
				lpPalette->SetEntries(0,0,256,&BackEntries[0]);
				Wait.Wait(wait);
			}
		}
	} else {
		for(a = 0;a < count;a ++){
			Wait.Reset();
			for(b = 0;b < 256;b ++){
				if(BackEntries[b].peRed + count <= 255){
					BackEntries[b].peRed += (count);
				} else if(BackEntries[b].peRed + count > 255){
					BackEntries[b].peRed = 255;
				}
				
				if(BackEntries[b].peGreen + count <= 255){
					BackEntries[b].peGreen += (count);
				} else if(BackEntries[b].peGreen + count > 255){
					BackEntries[b].peGreen = 255;
				}

				if(BackEntries[b].peBlue + count <= 255){
					BackEntries[b].peBlue += (count);
				} else if(BackEntries[b].peBlue + count > 255){
					BackEntries[b].peBlue = 255;
				}
			}
			if(!((com_key & KEY_Q) && a != count -1 && debug == 1)){ 
				lpPalette->SetEntries(0,0,256,&BackEntries[0]);
				Wait.Wait(wait);
			}
		}
	}
}

//---フェードイン
void eiDDPalette::Fadein(int wait,int count,int efect)
{
	int a,b,sub = 1;
	PALETTEENTRY pe[256],temp_pe[256];

	if(!lpPalette)
		return;
	if(count <= 0)
		count = 16;

//	memset(&Flag[0],0,sizeof(Flag));
	memcpy(&BackEntries[0],&PaletteEntries[0],sizeof(BackEntries));//sizeof(PALETTEENTRY)*256);
	for(a = 0;a < 256;a ++){
		pe[a].peRed =	PaletteEntries[a].peRed;
		pe[a].peGreen =	PaletteEntries[a].peGreen;
		pe[a].peBlue =	PaletteEntries[a].peBlue;
		
		if(efect == 0){
			temp_pe[a].peRed =		0;
			temp_pe[a].peGreen =	0;
			temp_pe[a].peBlue =		0;
		} else {
			temp_pe[a].peRed =		255;
			temp_pe[a].peGreen =	255;
			temp_pe[a].peBlue =		255;
		}

		if(a <= 9 || a >= 246
			&& (::eiSystem.ScreenMode & DIRECTDRAW_WINDOW)){
			pe[a].peFlags = PC_EXPLICIT;
			temp_pe[a].peFlags = PC_EXPLICIT;
			pe[a].peRed = (ei_u8)a;
			temp_pe[a].peRed = (ei_u8)a;
		} else {
			pe[a].peFlags=PC_NOCOLLAPSE | PC_RESERVED;
			temp_pe[a].peFlags=PC_NOCOLLAPSE | PC_RESERVED;
		}

		if(efect == 0){
			pe[a].peRed =	(ei_u8)(count-(PaletteEntries[a].peRed / count) - 1);
			pe[a].peGreen =	(ei_u8)(count-(PaletteEntries[a].peGreen / count) - 1);
			pe[a].peBlue =	(ei_u8)(count-(PaletteEntries[a].peBlue / count) - 1);

			temp_pe[a].peRed = (ei_u8)(PaletteEntries[a].peRed % count);
			temp_pe[a].peGreen = (ei_u8)(PaletteEntries[a].peGreen % count);
			temp_pe[a].peBlue = (ei_u8)(PaletteEntries[a].peBlue % count);
		} else if(efect == 1){
			pe[a].peRed =	(ei_u8)(PaletteEntries[a].peRed / count);
			pe[a].peGreen =	(ei_u8)(PaletteEntries[a].peGreen / count);
			pe[a].peBlue =	(ei_u8)(PaletteEntries[a].peBlue / count);
		}
	}

	if(efect == 1)
		sub = -1;
	for(a = 0;a < count;a ++){
		Wait.Reset();
		for(b = 0;b < 256;b ++){
			if(pe[b].peRed <= 0){
				if(efect == 1 && temp_pe[b].peRed - count < 0){
					temp_pe[b].peRed = 0;
				} else {
					if((int)temp_pe[b].peRed + (count * sub) > 255)
						temp_pe[b].peRed = 255;
					else
						temp_pe[b].peRed += (count * sub);
				}
				if(efect == 0){
					if(temp_pe[b].peRed > BackEntries[b].peRed)
						temp_pe[b].peRed = BackEntries[b].peRed;
				} else {
					if(temp_pe[b].peRed < BackEntries[b].peRed)
						temp_pe[b].peRed = BackEntries[b].peRed;
				}
			}
			if(pe[b].peGreen <= 0){
				if(efect == 1 && temp_pe[b].peGreen - count < 0){
					temp_pe[b].peGreen = 0;
				} else {
					if((int)temp_pe[b].peGreen + (count * sub) > 255)
						temp_pe[b].peGreen = 255;
					else
						temp_pe[b].peGreen += (count * sub);
				}

				if(efect == 0){
					if(temp_pe[b].peGreen > BackEntries[b].peGreen)
						temp_pe[b].peGreen = BackEntries[b].peGreen;
				} else {
					if(temp_pe[b].peGreen < BackEntries[b].peGreen)
						temp_pe[b].peGreen = BackEntries[b].peGreen;
				}
			}
			if(pe[b].peBlue <= 0){
				if(efect == 1 && temp_pe[b].peBlue - count < 0){
					temp_pe[b].peBlue = 0;
				} else {
					if((int)temp_pe[b].peBlue+ (count * sub) > 255)
						temp_pe[b].peBlue = 255;
					else
						temp_pe[b].peBlue += (count * sub);
				}
				if(efect == 0){
					if(temp_pe[b].peBlue > BackEntries[b].peBlue)
						temp_pe[b].peBlue = BackEntries[b].peBlue;
				} else {
					if(temp_pe[b].peBlue < BackEntries[b].peBlue)
						temp_pe[b].peBlue = BackEntries[b].peBlue;
				}
			}
			if(pe[b].peRed > 0)
				pe[b].peRed--;
			if(pe[b].peGreen > 0)
				pe[b].peGreen--;
			if(pe[b].peBlue > 0)
				pe[b].peBlue--;
		}
		if(!((com_key & KEY_Q) && a != count -1 && debug == 1)){ 
			lpPalette->SetEntries(0,0,256,&temp_pe[0]);
			Wait.Wait(wait);
		}
	}
}

//---パレットを真っ黒にする
void eiDDPalette::Black(void)
{
	int a;
	
	if(!lpPalette)
		return;

	for(a = 0;a < 256;a ++){
		BackEntries[a].peRed = 0;
		BackEntries[a].peGreen = 0;
		BackEntries[a].peBlue = 0;
		BackEntries[a].peFlags = PC_NOCOLLAPSE | PC_RESERVED;
	}
	if((::eiSystem.ScreenMode & DIRECTDRAW_WINDOW) != 0){
		for(a = 0;a < 10;a ++){
			//Windowsのシステムパレット
			BackEntries[a].peFlags = PC_EXPLICIT;
			BackEntries[a].peRed = (ei_u8)a;
			BackEntries[a].peGreen = 0;
			BackEntries[a].peBlue = 0;

			BackEntries[a+246].peFlags = PC_EXPLICIT;
			BackEntries[a+246].peRed = (ei_u8)(a+246);
			BackEntries[a+246].peGreen = 0;
			BackEntries[a+246].peBlue = 0;
		}
	}
	lpPalette->SetEntries(0,0,256,&BackEntries[0]);
}

void eiDDPalette::Push(void)
{
	memcpy(&KeepEntries[0],&PaletteEntries[0],sizeof(PALETTEENTRY)*256);
}

void eiDDPalette::Pop(void)
{
	memcpy(&PaletteEntries[0],&KeepEntries[0],sizeof(PALETTEENTRY)*256);
}
