#ifdef EIUSE_DIRECT3D

static int TextureIndex[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 
	0, 0, 0, 0, 0, 2, 3, 0, 0, 0, 
	0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 
	0, 0, 5, 0, 0, 0, 0, 0, 0, 0
};

//---適切なテクスチャフォーマットを選択
EI_API int eiDDChooseTextureFormat(int bpp,EI_TEXTUREFORMAT *lpFormat)
{
	int a,c = 0;
	int color[] = {4,8,16,24,32 , -1};
	memset(lpFormat,0,sizeof(EI_TEXTUREFORMAT));

	if(bpp == -1)
		bpp = eiSystem.ColorBit;

	if(bpp == 16){
		if(((eiSurface[0].RedMask | eiSurface[0].GreenMask | eiSurface[0].BlueMask) & 0x8000) == 0){
			//---555
			bpp = 15;
		}
	}

	if(eiDDInfo.TextureFormat[TextureIndex[bpp]].bFound){
		//---もし指定された色数があれば
		memcpy(lpFormat,
			&eiDDInfo.TextureFormat[TextureIndex[bpp]],
			sizeof(eiDDInfo.TextureFormat[TextureIndex[bpp]]));
		eiDebugWriteFile("(eiDDChooseTextureFormat) 指定ビット数と一致しました\n");
		return bpp;
	} else {
		//---なかったら、それより大きくて、出来るだけ近い色数をさがす
		for(a = 0;color[a] != -1;a ++){
		}
		for(a --;a >= 0;a --){
//			if(color[a] < bpp)
//				continue;

			c = color[a];
			if(c == 16){
				if(((eiSurface[0].RedMask | eiSurface[0].GreenMask | eiSurface[0].BlueMask) & 0x8000) == 0)
					//---555
					c = 15;
				else
					//---565
					c = 16;
			}
			if(eiDDInfo.TextureFormat[TextureIndex[c]].bFound){
				memcpy(lpFormat, &eiDDInfo.TextureFormat[TextureIndex[c]],sizeof(eiDDInfo.TextureFormat[TextureIndex[c]]));
				eiDebugWriteFile("(eiDDChooseTextureFormat) 指定ビット数と一致しません\n");
				return c;
			}
		}
	}

	//---テクスチャ無し！！
	return 0;
}
#endif /* EIUSE_DIRECT3D */

//----------------------------------
//	eiDDSurface
//----------------------------------
eiDDSurface::eiDDSurface(void)
{
	eimemset(&DDSurfaceDesc,0,sizeof(DDSurfaceDesc));
	lpSurface = NULL;
	lpSurfaceOld = NULL;
	xSize = ySize = Color = 0;

#ifdef CLASS_MEMORY_TEST
	INIT_MEMORY_TEST(hDumy);
#endif
}

int eiDDSurface::Release(void)
{
	int r;

#ifdef CLASS_MEMORY_TEST
	RELEASE_MEMORY_TEST(hDumy);
#endif

	if(lpSurface != NULL){
		if((r = lpSurface->Release()) > 0){
			eiDebugWriteFile("(eiDDSurface::Release) lpSurface->Release() > 0\n");
			char s[80];
			sprintf(s,"%d\n",r);
			eiDebugWriteFile(s);
			return 0;
		}
		eiDebugWriteFile("(eiDDSurface::Release) lpSurface->Release().\n");
		lpSurface = NULL;
	}
	if(lpSurfaceOld != NULL){
		if(lpSurfaceOld->Release() > 0){
			eiDebugWriteFile("(eiDDSurface::Release) lpSurfaceOld->Release() > 0\n");
			return 0;
		}
		lpSurfaceOld = NULL;
	}

	return 1;
}

//---カラーキーを設定
int eiDDSurface::SetSrcBltColorKey(int StartCol,int EndCol)
{
	DDCOLORKEY ddc;
	HRESULT ddrval;

	if(Color > 8){
		//---ハイカラー以上だったら黒に近い青を透明色にする
		StartCol = EndCol = 0x0001;
	}

	ddc.dwColorSpaceLowValue = StartCol;
	ddc.dwColorSpaceHighValue = EndCol;
	ddrval = lpSurface->SetColorKey(DDCKEY_SRCBLT,&ddc);
	if(ddrval == DD_OK)
		return 1;

	return 0;
}

//---サーフェイス作成
int eiDDSurface::Create(int xs,int ys,int mode,eiDDSurface *esDst,int color_bit /*= 0*/)
{
	LPDIRECTDRAWSURFACE7 lpDDSurface = NULL;
	DDSURFACEDESC2 ddsd;
	HRESULT ddrval;

	//---メモリーテスト
#ifdef CLASS_MEMORY_TEST
	ALLOC_MEMORY_TEST(hDumy);
#endif

	memset(&ddsd,0,sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = 0;
	ddsd.dwHeight = ys;
	ddsd.dwWidth = xs;
	
	xSize = xs;
	ySize = ys;

	Color = eiDDInfo.DDSurfaceColor;
	//---システムメモリーにサーフェイスを作る
	if(mode & ESCREATE_SYSTEMMEMORY){
		ddsd.ddsCaps.dwCaps |= (DDSCAPS_SYSTEMMEMORY);
	}

	do {
		//---プライマリサーフェイス
		if(mode & ESCREATE_PRIMARYSURFACE){
			if((::eiSystem.ScreenMode & DIRECTDRAW_WINDOW) == 0){
				//---フルスクリーンだったら
				ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
				ddsd.dwBackBufferCount = 1;
				ddsd.ddsCaps.dwCaps |= DDSCAPS_PRIMARYSURFACE
					| DDSCAPS_FLIP | DDSCAPS_COMPLEX;

				if(eiDDInfo.Use3D){
					if((::eiSystem.ScreenMode & DIRECTDRAW_WINDOW) == 0){
						ddsd.ddsCaps.dwCaps |= DDSCAPS_3DDEVICE;
					}
				}
			} else {
				//---ウィンドウ表示
				ddsd.dwFlags = DDSD_CAPS;
				ddsd.ddsCaps.dwCaps |= DDSCAPS_PRIMARYSURFACE;
			}
		} else if(mode & ESCREATE_BACKSURFACE){
		//---バックサーフェイス
			if((::eiSystem.ScreenMode & DIRECTDRAW_WINDOW) == 0){
				ddsd.ddsCaps.dwCaps |= DDSCAPS_BACKBUFFER;
				ddrval = esDst->lpSurface->GetAttachedSurface(&ddsd.ddsCaps,&lpDDSurface);
				lpSurface = lpDDSurface;

				break;
//				goto LABEL;
			} else {
				ddsd.ddsCaps.dwCaps |= DDSCAPS_OFFSCREENPLAIN;
				if(eiDDInfo.Use3D){
					ddsd.ddsCaps.dwCaps |= DDSCAPS_3DDEVICE;
				}
			}
		} else if(mode & ESCREATE_ZBUFFER){
#ifdef EIUSE_DIRECT3D
			eiDebugWriteFile("ZBuffer Creating...start\n");
			//---ＺＢｕｆｆｅｒ
			memset(&ddsd, 0, sizeof( ddsd ) );
			ddsd.dwSize = sizeof( ddsd );
			eiSurface[1].lpSurface->GetSurfaceDesc( &ddsd );

			ddsd.dwWidth = eiSystem.xScreenSize;
			ddsd.dwHeight = eiSystem.yScreenSize;
			ddsd.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS 
							| DDSD_PIXELFORMAT;// | DDSD_ZBUFFERBITDEPTH;
			ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER;

			//---Ｚバッファーをどこに作るか
			if(mode & ESCREATE_SYSTEMMEMORY){
				ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
				eiDebugWriteFile("ZBuffer Create on SystemMemory\n");
			} else {
				ddsd.ddsCaps.dwCaps |= DDSCAPS_VIDEOMEMORY;
				eiDebugWriteFile("ZBuffer Create on VideoMemory\n");
			}

			ddsd.ddpfPixelFormat = eiDDInfo.ddpZBufferFormat;
			ddsd.ddpfPixelFormat.dwZBufferBitDepth = eiDDInfo.ZBufferDepth;
			ddsd.ddpfPixelFormat.dwFlags |= DDPF_ZBUFFER ;
			eiDebugWriteFile("ZBuffer Creating...finish\n");
		} else if(mode & ESCREATE_TEXTURE){
			//---テクスチャー
			EI_TEXTUREFORMAT format;

			if(color_bit == 0)
				color_bit = 8;
			if(!eiDDChooseTextureFormat(color_bit, &format)){
				lpSurface = NULL;
				return 0;
			}
			ddsd.ddpfPixelFormat = format.ddsd.ddpfPixelFormat;
/*		if(esDst != NULL){
			esDst->lpSurface->GetSurfaceDesc( &ddsd );
		}*/
			ddsd.dwFlags =
				  DDSD_CAPS
				| DDSD_HEIGHT
				| DDSD_WIDTH
				| DDSD_PIXELFORMAT
				| DDSD_TEXTURESTAGE;
//				| DDSD_CKSRCBLT;
			ddsd.dwTextureStage = 0;
			ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE;
			if(format.BPP == 8){
				ddsd.ddckCKSrcBlt.dwColorSpaceLowValue = 16;
				ddsd.ddckCKSrcBlt.dwColorSpaceHighValue = 16;
			} else {
				ddsd.ddckCKSrcBlt.dwColorSpaceLowValue = 0x0001;
				ddsd.ddckCKSrcBlt.dwColorSpaceHighValue = 0x0001;
			}

			//---テンポラリテクスチャーかどうか
			if((mode & ESCREATE_TEMPTEXTURE)){
				ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
					ddsd.ddsCaps.dwCaps2 = 0;
			} else {
				ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
			}

			Color = format.BPP;
			if(Color == 15)
				Color = 16;

			char ss[100];
			sprintf(ss,"テクスチャーカラー : %d\n",Color);
			eiDebugWriteFile(ss);

#endif /* EIUSE_DIRECT3D */
		} else {
			//---その他のサーフェイス
			ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
		}

		ddrval = eiDDInfo.lpDD->CreateSurface(&ddsd,&lpDDSurface,NULL);
		if(ddrval != DD_OK){
			eiDebugWriteFile("(eiDDSurface) Create fail , CreateSurface() = NULL\n");
eidbMsg("サーフェイス作成失敗");
			lpSurface = NULL;
			return NULL;
		}
	} while(0);

//LABEL:
	lpSurface = lpDDSurface;
	lpSurfaceOld = NULL;

	if(mode & ESCREATE_ZBUFFER){
		//---ＺＢｕｆｆｅｒならバックサーフェイスにアタッチ
		if(eiDDInfo.lpBackBuffer->AddAttachedSurface(lpSurface) != DD_OK){
			eiDebugWriteFile("ZBuffer AddAttachedSurface fail\n");
		}
	}

	//---サーフェイスの能力を取得
	DDSurfaceDesc.dwSize = sizeof(DDSurfaceDesc);
	DDSurfaceDesc.dwFlags = DDSD_PIXELFORMAT | DDSD_REFRESHRATE
		| DDSD_HEIGHT | DDSD_WIDTH;

char s[80];
sprintf(s,"Surface RefreshRate = %d \n",DDSurfaceDesc.dwRefreshRate);
eiDebugWriteFile(s);

	lpSurface->GetSurfaceDesc(&DDSurfaceDesc);
	//---マスク
	RedMask = DDSurfaceDesc.ddpfPixelFormat.dwRBitMask;
	GreenMask = DDSurfaceDesc.ddpfPixelFormat.dwGBitMask;
	BlueMask = DDSurfaceDesc.ddpfPixelFormat.dwBBitMask;
	//---システムカラー
	if(!::eiSystem.RedMask){
		::eiSystem.RedMask = RedMask;
		::eiSystem.GreenMask = GreenMask;
		::eiSystem.BlueMask = BlueMask;
	}
	if(Color >= 16){
		RedShift = GetBitShift(RedMask);
		GreenShift = GetBitShift(GreenMask);
		BlueShift = GetBitShift(BlueMask);
		if(Color == 16){
		//---ハイカラーの場合
//		if(GreenMask == 0x03e0){
			if(((RedMask | GreenMask | BlueMask) & 0x8000) == 0){
				//555 colors
				RedBit = 5;
				GreenBit = 5;
				BlueBit = 5;
			} else {
				//565 colors
				RedBit = 5;//11
				GreenBit = 6;//5
				BlueBit = 5;//0
			}
		} else {
			//---24,32bit
			RedBit = 8;
			GreenBit = 8; 
			BlueBit = 8;
		}
		if(!::eiSystem.RedShift){
			::eiSystem.RedShift = RedShift;
			::eiSystem.GreenShift = GreenShift;
			::eiSystem.BlueShift = BlueShift;
			::eiSystem.RedBit = RedBit;
			::eiSystem.GreenBit = GreenBit;
			::eiSystem.BlueBit = BlueBit;
		}
	}
sprintf(s,"x = %3d,y = %3d ,Color = %d\n%d  red = %x  , green = %x  , blue = %x\n\n",
		DDSurfaceDesc.dwWidth,DDSurfaceDesc.dwHeight,
		Color,DDSurfaceDesc.ddpfPixelFormat.dwRGBBitCount,
		RedMask,GreenMask,BlueMask);
eiDebugWriteFile(s);

	return 1;
}

//---テクスチャーオブジェクトを返す
LPDIRECTDRAWSURFACE7 eiDDSurface::GetDirect3DTexture(void)
{
	if(lpSurface == NULL)
		return NULL;

	return lpSurface;
}

//---矩形転送
HRESULT eiDDSurface::Put(eiDDSurface *esDst,int x,int y,LPRECT rect,int mode)
{
	HRESULT ddrval;
/*	RECT rect2;
	
	//---座標変換
	rect2.left = rect->left;
	rect2.top = rect->top;
	rect2.right = rect->right;
	rect2.bottom = rect->bottom;

	eiChangePoint(&x,&y);
	eiChangeRect(&rect2);
	rect = &rect2;*/

	if(SurfaceMode & EISURFACE_CALCCLIENT){
		//---ウィンドウモード
		rect->left += ::eiWindowRect.left;
		rect->right += ::eiWindowRect.left;
		rect->top += ::eiWindowRect.top;
		rect->bottom += ::eiWindowRect.top;
	}

	ddrval = esDst->lpSurface->BltFast(x,y,
		lpSurface,rect,mode);

	return ddrval;
}

//---矩形転送
HRESULT eiDDSurface::PutExtend(eiDDSurface *esDst,int x,int y,LPRECT rect,int mode,
			 double xRate,double yRate)
{
	HRESULT ddrval;
	RECT DestRect;
//	RECT rect2;
	double f;

/*	//---座標変換
	rect2.left = rect->left;
	rect2.top = rect->top;
	rect2.right = rect->right;
	rect2.bottom = rect->bottom;

	eiChangePoint(&x,&y);
	eiChangeRect(&rect2);
	rect = &rect2;*/

	if(SurfaceMode & EISURFACE_CALCCLIENT){
		//---ウィンドウモード
		rect->left += ::eiWindowRect.left;
		rect->right += ::eiWindowRect.left;
		rect->top += ::eiWindowRect.top;
		rect->bottom += ::eiWindowRect.top;
	}

	memcpy(&DestRect,rect,sizeof(RECT));
	DestRect.left = x;
	DestRect.top = y;
	DestRect.right = DestRect.left + (rect->right - rect->left);
	DestRect.bottom = DestRect.top + (rect->bottom - rect->top);

	f = (double)(DestRect.right-DestRect.left);
	f *= xRate;
	DestRect.right = DestRect.left + (int)f;
	f = (double)(DestRect.bottom-DestRect.top);
	f *= yRate;
	DestRect.bottom = DestRect.top + (int)f;

	ddrval = esDst->lpSurface->Blt(&DestRect,lpSurface,
		rect,mode,NULL);

	return ddrval;
}

//---矩形転送
HRESULT eiDDSurface::PutExtend2(eiDDSurface *esDst,LPRECT lpDstRect,
			LPRECT lpSrcRect,int mode)
{
	HRESULT ddrval;
/*	RECT rect2;

	//---座標変換
	rect2.left = lpDstRect->left;
	rect2.top = lpDstRect->top;
	rect2.right = lpDstRect->right;
	rect2.bottom = lpDstRect->bottom;

	eiChangeRect(&rect2);
	lpDstRect = &rect2;*/
	if(SurfaceMode & EISURFACE_CALCCLIENT){
		//---ウィンドウモード
		lpDstRect->left += ::eiWindowRect.left;
		lpDstRect->right += ::eiWindowRect.left;
		lpDstRect->top += ::eiWindowRect.top;
		lpDstRect->bottom += ::eiWindowRect.top;
	}

	ddrval = esDst->lpSurface->Blt(lpDstRect,lpSurface,lpSrcRect,mode,NULL);

	return ddrval;
}

//---線を描く
void eiDDSurface::DrawLineNextY(int xp,int yp,int dx,int dy,int dirVector,
					   int color,int efect)
{
	int k1,k2,errorTerm;
	int wc = color;

	k1 = dy << 2;
	k2 = k1 -(int)(dx << 2);
	errorTerm = k1 - (int)dx;

	DrawPixel(xp,yp,wc);
	while(dx--){
		if(errorTerm >= 0){
			yp++;
			errorTerm += k2;
		} else {
			errorTerm += k1;
		}
		xp += dirVector;

		DrawPixel(xp,yp,wc);
	}
}

void eiDDSurface::DrawLineNextX(int xp,int yp,int dx,int dy,int dirVector,
					   int color,int efect)
{
	int k1,k2,errorTerm;
	int wc = color;

	k1 = dx << 2;
	k2 = k1 -(int)(dy << 2);
	errorTerm = k1 - (int)dy;

	DrawPixel(xp,yp,wc);
	while(dy--){
		if(errorTerm >= 0){
			xp+= dirVector;
			errorTerm += k2;
		} else {
			errorTerm += k1;
		}
		yp ++;
		DrawPixel(xp,yp,wc);
	}
}

//---ラインを描く
void eiDDSurface::DrawLine(int x1,int y1,int x2,int y2,int col,int efect)
{
	int dx,dy,step;

	if(!lpSurface)
		return;

	if(y1 > y2){
		eiSwap(&y1,&y2);
		eiSwap(&x1,&x2);
	}

	dx = x2 - x1;
	dy = y2 - y1;
	if(dx > 0){
		step = 1;
	} else {
		dx = -dx;
		step = -1;
	}
	if(dx > dy){
		DrawLineNextY(x1,y1,dx,dy,step,col,efect);
	} else {
		DrawLineNextX(x1,y1,dx,dy,step,col,efect);
	}
}

//---箱を描く
void eiDDSurface::DrawBox(int x1,int y1,int x2,int y2,int col,int efect)
{
	if(!lpSurface)
		return;

	DrawLine(x1,y1,x2,y1,col,efect);
	DrawLine(x2,y1,x2,y2,col,efect);
	DrawLine(x2,y2,x1,y2,col,efect);
	DrawLine(x1,y2,x1,y1,col,efect);
}

//---箱を描き塗りつぶす
void eiDDSurface::DrawFillBox(int x1,int y1,int x2,int y2,int col,int efect)
{
/*	int x,y;
	int Pitch,Addres;
	LPBYTE lpMemory;

	Lock(&lpMemory,&Pitch);
	if(lpMemory == NULL)
		return;

	if(x1 > x2)
		eiSwap(&x1,&x2);
	if(y1 > y2)
		eiSwap(&y1,&y2);
	for(y = y1;y <= y2;y ++){
		Addres = (y * Pitch);
		if(Color == 8){
			for(x = x1;x <= x2;x ++){
				*(lpMemory + Addres + x) = (BYTE)col;
			}
		} else {
			for(x = x1;x <= x2;x ++){
				*(WORD *)(lpMemory + Addres + (x * 2)) = (WORD)col;
			}
		}
	}

	UnLock();
*/
	if(!lpSurface)
		return;

	if(x1 > x2)
		eiSwap(&x1,&x2);
	if(y1 > y2)
		eiSwap(&y1,&y2);

	DDBLTFX ddbltfx;
	ddbltfx.dwSize = sizeof(ddbltfx);
	ddbltfx.dwFillColor = col;
	HRESULT ddrval;

	RECT rect=
	{
		x1,y1,
		x2 + 1,y2 + 1
	};
	//---座標変換
	eiChangeRect(&rect);

	if(SurfaceMode & EISURFACE_CALCCLIENT){
		//---ウィンドウモード
		rect.left += ::eiWindowRect.left;
		rect.right += ::eiWindowRect.left;
		rect.top += ::eiWindowRect.top;
		rect.bottom += ::eiWindowRect.top;
	}

	while(1){
		ddrval = lpSurface->Blt(&rect,NULL,NULL,
			DDBLT_COLORFILL | DDBLT_WAIT,&ddbltfx);
		if(ddrval == DD_OK)
			break;
		if(ddrval != DDERR_WASSTILLDRAWING)
			return;
	}
}

//---フリップ
void eiDDSurface::Flip(int mode)
{
	HRESULT ddrval = DD_OK;
	RECT rect,SrcRect;
	
	//mode = 1:Blt

	if((::eiSystem.ScreenMode & DIRECTDRAW_FULLSCREEN)
		&& !(::eiSystem.ScreenMode & DIRECTDRAW_FLIPBLT) && mode == 0){
		//---ハードウェアフリップ
		ddrval = lpSurface->Flip(NULL,DDFLIP_WAIT);
	} else {
		//---Blt転送によるフリップ
		if((::eiSystem.ScreenMode & DIRECTDRAW_FULLSCREEN)){
/*			rect.left = 0;
			rect.top = 0;
			rect.right = 640;
			rect.bottom = 480;*/
			ddrval = eiSurface[0].lpSurface->Blt(
				NULL,eiSurface[1].lpSurface,
				NULL,DDBLT_WAIT,NULL);
		} else {
			rect.left = ::eiWindowRect.left;
			rect.top = ::eiWindowRect.top;

			rect.right = ::eiSystem.xScreenSize + rect.left;
			rect.bottom = ::eiSystem.yScreenSize + rect.top;

			SrcRect.left = SrcRect.top = 0;
			SrcRect.right = xSize;
			SrcRect.bottom = ySize;

			ddrval = eiSurface[0].lpSurface->Blt(
				&rect,eiSurface[1].lpSurface,
				&SrcRect,DDBLT_WAIT,NULL);
		}
	}
}

//---Vsync
void eiDDSurface::WaitVSync(void)
{
/*	if(::eiSystem.ScreenMode & DIRECTDRAW_FULLSCREEN){
		//---フルスクリーン
	} else {
	}*/
	eiDDInfo.lpDD->WaitForVerticalBlank(DDWAITVB_BLOCKBEGIN,NULL);
}

//---サーフェイスをロック
int eiDDSurface::Lock(LPBYTE *lpMemory,int *Pitch,LPRECT lpRect)
{
	DDSURFACEDESC2 DDSDesc;
	HRESULT ddrval;

	memset(&DDSDesc,0,sizeof(DDSDesc));

	DDSDesc.dwSize = sizeof(DDSDesc);
	while(1){
		ddrval = lpSurface->Lock(NULL,&DDSDesc,DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR,NULL);
		if(ddrval == DD_OK)
			break;
		if(ddrval != DDERR_WASSTILLDRAWING){
			return FALSE;
		}
		Sleep(1);
	}
	*Pitch = DDSDesc.lPitch;
	*lpMemory = (LPBYTE)DDSDesc.lpSurface;
	
	return TRUE;
}

//---ロックを解除
void eiDDSurface::UnLock(void)
{
	lpSurface->Unlock(NULL);
}

//---点打ち
void eiDDSurface::DrawPixel(int x,int y,int col,int efect)
{
	int Pitch,Addres;
	LPBYTE lpMemory;

	//---座標変換
	eiChangePoint(&x,&y);

	Lock(&lpMemory,&Pitch);
	Addres = (y * Pitch) + (x * (Color >> 3));

	if(Color == 8){
		*(lpMemory + Addres) = (BYTE)col;
	} else if(Color == 16){
		*(WORD *)(lpMemory + Addres) = (WORD)col;
	} else if(Color == 32){
		*(DWORD *)(lpMemory + Addres) = (DWORD)col;
	} else {
	}

	UnLock();
}

//---色読み込み
int eiDDSurface::GetPixel(int x,int y,int efect)
{
	int Pitch,Addres,col = 0;
	LPBYTE lpMemory;

	//---座標変換
	eiChangePoint(&x,&y);

	Lock(&lpMemory,&Pitch);
	Addres = (y * Pitch) + (x * (Color >> 3));

	if(Color == 8){
		col = *(lpMemory + Addres);
	} else if(Color == 16){
		col = *(WORD *)(lpMemory + Addres);
	} else if(Color == 32){
		col = (int)(*(DWORD *)(lpMemory + Addres));
	} else {
	}

	UnLock();

	return col;
}

//---サーフェイスにテキストを描く
int eiDDSurface::DDSurfaceText(EISTR *String,int x,int y,int color,int efect)
{
	int Pitch;
	LPBYTE lpMemory;

	//---座標変換
	eiChangePoint(&x,&y);

	Lock(&lpMemory,&Pitch);

	if(lpMemory){
		DrawTextMemory((lpMemory + (x *( Color / 8)) + (y * Pitch) ) ,1,Color / 8,Pitch,
			String,x,y,color,efect);
	}

	UnLock();

	return 1;
}

extern EI_API int eiEnableCheckThread(int enable);

int eiDDSurface::DDSurfaceTextDirect(EISTR *String,int x,int y,int color,int efect /*= EI_TRANS*/)
{
	HDC hdc;
	HRESULT res;

	int old = eiEnableCheckThread(0);

	res = lpSurface->GetDC(&hdc);

	if(res == DD_OK){
		HGDIOBJ hfont = SelectObject(hdc,eiFont[::eiSystem.ActiveFont]);

		SetTextColor(hdc,color/*RGB(255,255,255)*/);
		SetBkMode(hdc,TRANSPARENT);
//		SetBkColor(hdc,color255,255,255));

		TextOut(hdc,x,y,String,strlen(String));

		SelectObject(hdc,hfont);
		lpSurface->ReleaseDC(hdc);
	} else {
/*		eiDebugWriteFile("(eiDDSurface::DDSurfaceTextDirect)error\n");
		if(res == DDERR_DCALREADYCREATED)
			eiDebugWriteFile("      DDERR_DCALREADYCREATED\n");
		if(res == DDERR_GENERIC )
			eiDebugWriteFile("      DDERR_GENERIC \n");
		if(res == DDERR_INVALIDOBJECT )
			eiDebugWriteFile("      DDERR_INVALIDOBJECT \n");
		if(res == DDERR_INVALIDPARAMS )
			eiDebugWriteFile("      DDERR_INVALIDPARAMS \n");
		if(res == DDERR_INVALIDSURFACETYPE )
			eiDebugWriteFile("      DDERR_INVALIDSURFACETYPE \n");
		if(res == DDERR_WASSTILLDRAWING  )
			eiDebugWriteFile("      DDERR_WASSTILLDRAWING  \n");
		if(res == DDERR_SURFACELOST  )
			eiDebugWriteFile("      DDERR_SURFACELOST  \n");
		if(res == DDERR_UNSUPPORTED  )
			eiDebugWriteFile("      DDERR_UNSUPPORTED  \n");*/
	}

	eiEnableCheckThread(old);

	return 1;
}

//---復元
int eiDDSurface::Restore(void)
{
	if(lpSurface->IsLost() == DDERR_SURFACELOST){
		if(lpSurface->Restore() == DD_OK)
			return 1;
		return 0;
	}
	return 1;
}
