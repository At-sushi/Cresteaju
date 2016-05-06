int eiReleaseD3Device(void);

static BOOL bFoundHardwareDevice = FALSE; // ハードウェアデバイスが見つかったか？

#define EI_ENUMMAX 32

struct D3DDeviceInfo {
	D3DCOLORMODEL cm;
	int DeviceCount,
		HALNumber,
		HALTnLNumber,
		HELRGBNumber,
		HELMMXNumber,
		HELReferenceNumber;
	GUID Guid[EI_ENUMMAX];
	D3DDEVICEDESC7 DeviceDesc[EI_ENUMMAX];
	char DeviceName[EI_ENUMMAX][64];

	int UseNumber;
};

//------3Dデバイスを列挙
static HRESULT WINAPI eiD3DEnumDeviceCallBack(
	LPSTR lpDeviceDescription, LPSTR lpDeviceName, 
	LPD3DDEVICEDESC7 lpDeviceDesc, LPVOID lpContext) 
{
	D3DDeviceInfo* pInfo = (D3DDeviceInfo *)lpContext;

	{
		//---能力をコピー
		memcpy(&pInfo->DeviceDesc[pInfo->DeviceCount], lpDeviceDesc, sizeof(D3DDEVICEDESC7));

		pInfo->Guid[pInfo->DeviceCount] = lpDeviceDesc->deviceGUID;

		if(lpDeviceDesc->deviceGUID == IID_IDirect3DRefDevice){
			pInfo->HELReferenceNumber = pInfo->DeviceCount;
		} else if(lpDeviceDesc->deviceGUID == IID_IDirect3DHALDevice){
			pInfo->HALNumber = pInfo->DeviceCount;
		} else if(lpDeviceDesc->deviceGUID == IID_IDirect3DMMXDevice){
			pInfo->HELMMXNumber = pInfo->DeviceCount;
		} else if(lpDeviceDesc->deviceGUID == IID_IDirect3DTnLHalDevice){
			pInfo->HALTnLNumber = pInfo->DeviceCount;
		} else if(lpDeviceDesc->deviceGUID == IID_IDirect3DRGBDevice){
			pInfo->HELRGBNumber = pInfo->DeviceCount;
		}
//		pInfo->Guid[pInfo->DeviceCount] = IID_IDirect3DMMXDevice;
//		pInfo->Guid[pInfo->DeviceCount] = IID_IDirect3DTnLHalDevice;
//		pInfo->Guid[pInfo->DeviceCount] = IID_IDirect3DRGBDevice;

		char str[200];
		sprintf(str,"(eiFindD3DDevice) DeviceName :%s is %s\n",lpDeviceName,
			(lpDeviceDesc->dwDevCaps & D3DDEVCAPS_HWRASTERIZATION) ? "HAL" : "HEL");
		eiDebugWriteFile(str);

		//---名前をコピー
		sprintf(&pInfo->DeviceName[pInfo->DeviceCount][0],"%s",lpDeviceName);

		//---その他の能力
		if(lpDeviceDesc->dwDevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT){
			eiDebugWriteFile("        This device supports Hardware T&L.\n");
		}

		pInfo->DeviceCount ++;
	}


	if(eiDDInfo.UseHardware3D){
		if(lpDeviceDesc->dwDevCaps & D3DDEVCAPS_HWRASTERIZATION){
			//---それがＨＡＬだったら
			if ((lpDeviceDesc->dwDeviceZBufferBitDepth & DDBD_16) ||
				(lpDeviceDesc->dwDeviceZBufferBitDepth & DDBD_24) ||
				(lpDeviceDesc->dwDeviceZBufferBitDepth & DDBD_32)) {

//				pInfo->HALNumber = pInfo->DeviceCount - 1;
			}
			return D3DENUMRET_OK;
		}
	}

	if(!(lpDeviceDesc->dwDevCaps & D3DDEVCAPS_HWRASTERIZATION)){
		//---HEL
//		pInfo->HELRGBNumber = pInfo->DeviceCount - 1;
	}

	return D3DENUMRET_OK;
}

//---Ｚバッファーを列挙
//---なるべく画面ビット数と同じか、ビット数の少ないのをさがす
HRESULT WINAPI eiEnumZBufferFormatsCallback( DDPIXELFORMAT* pddpf,
										  VOID* pddpfDesired )
{
	static int index = 0,find_bitdepth = 0;
	char s[255];

	if(NULL == pddpf || NULL == pddpfDesired )
		return D3DENUMRET_CANCEL;

	if( pddpf->dwFlags == ((DDPIXELFORMAT*)pddpfDesired)->dwFlags )
    {
/*		if(eiSystem.ColorBit == (int)pddpf->dwZBufferBitDepth){
			eiDDInfo.ZBufferDepth = pddpf->dwZBufferBitDepth;
			return D3DENUMRET_CANCEL;
		}*/

		if( pddpf->dwZBufferBitDepth > 0){
			sprintf(s,"(eiEnumZBufferFormatsCallback) z-buffer = %d\n",pddpf->dwZBufferBitDepth);
			eiDebugWriteFile(s);

			eiDDInfo.ZBufferEnumDepth[index] = pddpf->dwZBufferBitDepth;

			if( (eiSystem.ColorBit == (int)pddpf->dwZBufferBitDepth && find_bitdepth == 0)
			||  (eiDDInfo.ZBufferEnumDepth[index] <  (int)eiDDInfo.ZBufferDepth && find_bitdepth == 0)
			||  eiDDInfo.ZBufferDepth == 0){

				if(eiSystem.ColorBit ==  (int)pddpf->dwZBufferBitDepth && find_bitdepth == 0){
					//---画面の色数と同じだったら
					find_bitdepth = 1;
				}
				eiDDInfo.ZBufferDepth = eiDDInfo.ZBufferEnumDepth[index];
				//---使うんだったら能力をコピーする
				memcpy( pddpfDesired, pddpf, sizeof(DDPIXELFORMAT) );
				eiDebugWriteFile("最終候補...\n");
			}
			index ++;
		}
	}

	return D3DENUMRET_OK;
}

#define TEXTURE_INDEX_4 0
#define TEXTURE_INDEX_8 1
#define TEXTURE_INDEX_15 2
#define TEXTURE_INDEX_16 3
#define TEXTURE_INDEX_24 4
#define TEXTURE_INDEX_32 5

//---テクスチャフォーマットを列挙する
HRESULT CALLBACK EnumTextureFormatsCallback(LPDDPIXELFORMAT lpddpfPixelFormat, LPVOID lpContext)
{
	unsigned long m;
	int r, g, b;
	int a,index = 0;
	EI_TEXTUREFORMAT *lpFormat = (EI_TEXTUREFORMAT *)lpContext;
	
	if(lpddpfPixelFormat->dwFlags & DDPF_PALETTEINDEXED8){
		index = TEXTURE_INDEX_8;

		memcpy(&lpFormat[index].ddsd.ddpfPixelFormat, lpddpfPixelFormat,sizeof(DDPIXELFORMAT));
		lpFormat[index].bPalettized = TRUE;
		lpFormat[index].BPP = lpFormat[index].IndexBPP = 8;
		lpFormat[index].bFound = 1;
	} else if(lpddpfPixelFormat->dwFlags & DDPF_PALETTEINDEXED4){
		index = TEXTURE_INDEX_4;

		memcpy(&lpFormat[index].ddsd.ddpfPixelFormat, lpddpfPixelFormat,sizeof(DDPIXELFORMAT));
		lpFormat[index].bPalettized = TRUE;
		lpFormat[index].BPP = lpFormat[index].IndexBPP = 4;
		lpFormat[index].bFound = 1;
	} else if(lpddpfPixelFormat->dwFlags & DDPF_ALPHAPIXELS){
	    return DDENUMRET_OK;
	} else {
		for(a = 64,r = 0, m = lpddpfPixelFormat->dwRBitMask; !(m & 1) && a > 0;
			a --,r ++, m >>= 1);

		for(a = 64,r = 0; (m & 1) && a > 0; a --,r ++, m >>= 1);

		for(a = 64,g = 0, m = lpddpfPixelFormat->dwGBitMask; !(m & 1) && a > 0;
			a --,g ++, m >>= 1);

		for(a = 64,g = 0; (m & 1) && a > 0; a --,g ++, m >>= 1);

		for(a = 64,b = 0, m = lpddpfPixelFormat->dwBBitMask; !(m & 1) && a > 0;
			a --,b ++, m >>= 1);

		for(a = 64,b = 0; (m & 1) && a > 0; a --,b ++, m >>= 1);
		
		if(r + g + b == 15  && (r == 5 && g == 5 && b == 5)){
			index = TEXTURE_INDEX_15;
		} else if(r + g + b == 16 && (r == 5 && g == 6 && b == 5)){
			index = TEXTURE_INDEX_16;
		} else if(r + g + b == 24){
			index = TEXTURE_INDEX_24;
		} else if(r + g + b == 32){
			index = TEXTURE_INDEX_32;
		}
		memcpy(&lpFormat[index].ddsd.ddpfPixelFormat, lpddpfPixelFormat,sizeof(DDPIXELFORMAT));

		lpFormat[index].bPalettized = FALSE;
		lpFormat[index].IndexBPP = 0;

		lpFormat[index].BPP = r + g + b;
        lpFormat[index].RedBPP = r;
        lpFormat[index].GreenBPP = g;
        lpFormat[index].BlueBPP = b;
		lpFormat[index].bFound = 1;

		char str[200];
		sprintf(str,"(EnumTextureFormatsCallback)Texture Format R:%d G:%d B:%d \n",r,g,b);
		eiDebugWriteFile(str);
	}

    return DDENUMRET_OK;
}

//---テクスチャフォーマットを集めて初期化
EI_API BOOL eiDDInitIMTextureFormats()
{
eidbMsg("(eiDDInitIMTextureFormats)テクスチャフォーマット初期化");
	memset(&eiDDInfo.TextureFormat[0],0,sizeof(eiDDInfo.TextureFormat));

	if( eiDDInfo.lpD3DDevice->EnumTextureFormats( EnumTextureFormatsCallback,
                                                  (LPVOID)&eiDDInfo.TextureFormat[0]) != DD_OK) {
		eiDebugWriteFile("(eiDDInitIMTextureFormats)Enumeration of texture formats failed.\n");
		return FALSE;
	}

	eiDebugWriteFile("(eiDDInitIMTextureFormats) Emum end\n");

eidbMsg("(eiDDInitIMTextureFormats)テクスチャフォーマット終了");

	return TRUE;
}

static D3DDeviceInfo deviceInfo;

//---Ｚバッファーを作る
int eiCreateZBuffer(void) 
{
	DWORD dwZBufferMemType = 0;

	if((eiSystem.ScreenMode & NOUSE_ZBUFFER)){
		return 1;
	}

	//---Ｚバッファーがいらないなら
	D3DDEVICEDESC7 ddDesc;
	eiDDInfo.lpD3DDevice->GetCaps(&ddDesc);
	if(ddDesc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_ZBUFFERLESSHSR )
		return 1;

	//---Ｚバッファー列挙
	eiDebugWriteFile("\n---------------------------------\n");
	eiDDInfo.ZBufferDepth = 0;

	memset(&eiDDInfo.ddpZBufferFormat,0, sizeof(eiDDInfo.ddpZBufferFormat));
	memset(&eiDDInfo.ZBufferEnumDepth[0],0,sizeof(eiDDInfo.ZBufferEnumDepth));

	eiDDInfo.ddpZBufferFormat.dwFlags = DDPF_ZBUFFER;
	eiDDInfo.lpD3D->EnumZBufferFormats(deviceInfo.Guid[deviceInfo.UseNumber],eiEnumZBufferFormatsCallback,
		(VOID*)&eiDDInfo.ddpZBufferFormat);

	eiDebugWriteFile("(eiFindD3DDevice) Use \"");
	eiDebugWriteFile(deviceInfo.DeviceName[deviceInfo.UseNumber]);
	eiDebugWriteFile("\"\n");
	if(deviceInfo.DeviceDesc[deviceInfo.UseNumber].dwDevCaps & D3DDEVCAPS_HWRASTERIZATION){
		//---Ｚバッファーはビデオメモリー
		dwZBufferMemType = 0;

		eiDebugWriteFile("(eiCreateZBuffer) Use HAL\n");
	} else {
		//---システム
		eiDDInfo.Use3DHEL = 1;
		dwZBufferMemType = ESCREATE_SYSTEMMEMORY;

		eiDDInfo.ZBufferDepth = 16;

		eiDebugWriteFile("(eiCreateZBuffer) Use HEL\n");
	}

//	eiDDInfo.ZBufferDepth = 0;
	//---Zバッファの作成
	if(eiDDInfo.ZBufferDepth && !(eiSystem.ScreenMode & NOUSE_ZBUFFER)){
		DDSURFACEDESC2 ddsd;

		memset(&ddsd, 0,sizeof( ddsd ) );
		ddsd.dwSize = sizeof( ddsd );
		eiDDInfo.lpBackBuffer->GetSurfaceDesc( &ddsd );
		
		if(!eiZBuffer[0].Create(ddsd.dwWidth,ddsd.dwHeight,
			dwZBufferMemType | ESCREATE_ZBUFFER,NULL)){
			eiDebugWriteFile("(eiCreateZBuffer) Can't Create ZBuffer\n");
			return 0;
		}

		char s[80];
		sprintf(s,"(eiCreateZBuffer) ZBuffer (Depth = %d) Create Succes\n",eiDDInfo.ZBufferDepth);
		eiDebugWriteFile(s);
	}

	if(eiDDInfo.lpD3DDevice->SetRenderTarget(eiDDInfo.lpBackBuffer,0)
		!= D3D_OK){
		eiDebugWriteFile("(eiCreateZBuffer) SetRenderTarget failed.\n");
	}

	eiDebugWriteFile("\n\n");

	return 1;
}

//---３Ｄデバイスを見つける
LPGUID eiFindD3DDevice(D3DCOLORMODEL cm) 
{
	static D3DFINDDEVICERESULT result;
	HRESULT error;
//	DWORD dwZBufferMemType;

	int DeviceNumber = -1;

	eiDebugWriteFile("\n\n");
	if (FAILED(eiDDInfo.lpDD->QueryInterface(IID_IDirect3D7, (void**) &eiDDInfo.lpD3D))){
		eiDebugWriteFile("(eiFindD3DDevice) Failed to QueryInterface Direct3D7 from DirectDraw\n");
		return NULL;
	}

	//---デバイスを列挙
	bFoundHardwareDevice = FALSE;
	memset(&deviceInfo, 0, sizeof(deviceInfo));
	deviceInfo.cm = cm;
	deviceInfo.HALNumber = -1;
	deviceInfo.HALTnLNumber = -1;
	deviceInfo.HELRGBNumber = -1;
	deviceInfo.HELMMXNumber = -1;
	deviceInfo.HELReferenceNumber = -1;
	deviceInfo.DeviceCount = 0;
	error = eiDDInfo.lpD3D->EnumDevices(eiD3DEnumDeviceCallBack, &deviceInfo);
	//---一番適するのを選ぶ
	{
		if(deviceInfo.HELReferenceNumber != -1){
			//---Reference HELがあれば、それを使う
			DeviceNumber = deviceInfo.HELReferenceNumber;
			eiDDInfo.Use3DHEL = 1;
		}
		if(deviceInfo.HELRGBNumber != -1){
			//---RGB HELがあれば、それを使う
			DeviceNumber = deviceInfo.HELRGBNumber;
			eiDDInfo.Use3DHEL = 1;
		}
		if(deviceInfo.HELMMXNumber != -1){
			//---MMX HELがあれば、それを使う
			DeviceNumber = deviceInfo.HELMMXNumber;
			eiDDInfo.Use3DHEL = 1;
		}
		if(deviceInfo.HALNumber != -1 && eiDDInfo.UseHardware3D){
			//---HALがあれば、それを使う
			DeviceNumber = deviceInfo.HALNumber;
			eiDDInfo.Use3DHEL = 0;
		}
		if(deviceInfo.HALTnLNumber != -1 && eiDDInfo.UseHardware3D){
			//---T&Lがあれば、それを使う
			DeviceNumber = deviceInfo.HALTnLNumber;
			eiDDInfo.Use3DHEL = 0;
		}
	}
	if(DeviceNumber == -1){
		eiDebugWriteFile("(eiFindD3DDevice) cannot find 3DDevice\n");
		return 0;
	}
	deviceInfo.UseNumber = DeviceNumber;
	sprintf(&eiDDInfo.Direct3DUsingDeviceName[0],"%s",&deviceInfo.DeviceName[DeviceNumber][0]);

/*	//---Ｚバッファー列挙
	eiDDInfo.ZBufferDepth = 0;
	memset(&eiDDInfo.ddpZBufferFormat,0, sizeof(eiDDInfo.ddpZBufferFormat));
	memset(&eiDDInfo.ZBufferEnumDepth[0],0,sizeof(eiDDInfo.ZBufferEnumDepth));
	eiDDInfo.ddpZBufferFormat.dwFlags = DDPF_ZBUFFER;
	eiDDInfo.lpD3D->EnumZBufferFormats(deviceInfo.Guid[DeviceNumber],eiEnumZBufferFormatsCallback,
		(VOID*)&eiDDInfo.ddpZBufferFormat);

	eiDebugWriteFile("(eiFindD3DDevice) Use \"");
	eiDebugWriteFile(deviceInfo.DeviceName[DeviceNumber]);
	eiDebugWriteFile("\"\n");
	if(deviceInfo.DeviceDesc[DeviceNumber].dwDevCaps & D3DDEVCAPS_HWRASTERIZATION){
		//---Ｚバッファーはビデオメモリー
		dwZBufferMemType = 0;

		eiDebugWriteFile("(eiFindD3DDevice) Use HAL\n");
	} else {
		//---システム
		eiDDInfo.Use3DHEL = 1;
		dwZBufferMemType = ESCREATE_SYSTEMMEMORY;

		eiDDInfo.ZBufferDepth = 16;

		eiDebugWriteFile("(eiFindD3DDevice) Use HEL\n");
	}

//	eiDDInfo.ZBufferDepth = 0;
	//---Zバッファの作成
	if(eiDDInfo.ZBufferDepth && !(eiSystem.ScreenMode & NOUSE_ZBUFFER)){
		DDSURFACEDESC2 ddsd;

		memset(&ddsd, 0,sizeof( ddsd ) );
		ddsd.dwSize = sizeof( ddsd );
		eiDDInfo.lpBackBuffer->GetSurfaceDesc( &ddsd );
		
		if(!eiZBuffer[0].Create(ddsd.dwWidth,ddsd.dwHeight,
			dwZBufferMemType | ESCREATE_ZBUFFER,NULL)){
			eiDebugWriteFile("(eiFindD3DDevice) Can't Create ZBuffer\n");
			return 0;
		}

		char s[80];
		sprintf(s,"(eiFindD3DDevice) ZBuffer (Depth = %d) Create Succes\n",eiDDInfo.ZBufferDepth);
		eiDebugWriteFile(s);
	}*/

	eiDebugWriteFile("\n\n");

	return &deviceInfo.Guid[DeviceNumber];
}

int eiCreate3DDevice(void)
{
	LPGUID guid;

	guid = FALSE;
	guid = eiFindD3DDevice(eiDDInfo.ColorModel); //デバイスを探す
	if(!guid){
		eiReleaseD3Device();
		eiDebugWriteFile("(eiCreate3DDevice) Fail to Direct3D create \n ");
		return 0;
	}
eidbMsg("(eiCreate3DDevice)eiFindD3DDevice");

	if(eiDDInfo.lpD3D->CreateDevice(*guid,eiDDInfo.lpBackBuffer, &eiDDInfo.lpD3DDevice) != D3D_OK){
		eiDebugWriteFile("(eiCreate3DDevice) Can't Create Direct3DDevice3 from Direct3D2\n");
		eiReleaseD3Device();
eidbMsg("CreateDevice失敗");
		return 0;
	}
eidbMsg("(eiCreate3DDevice)CreateDevice");

	//---Ｚバッファー作成
	if(eiCreateZBuffer() == 0){
		return 0;
	}

eidbMsg("(eiCreate3DDevice)CreateZBuffer");

	//---デバイスの能力を取得
	eiDDInfo.lpD3DDevice->GetCaps(&eiDDInfo.D3DDeviceDesc);
	{
		char s[80];

		sprintf(s,"\tTexMinWidth = (%d , %d)\n",
			eiDDInfo.D3DDeviceDesc.dwMinTextureWidth,
			eiDDInfo.D3DDeviceDesc.dwMaxTextureWidth
			);
		eiDebugWriteFile(s);
		sprintf(s,"\tTexMinHeight = (%d , %d)\n",
			eiDDInfo.D3DDeviceDesc.dwMinTextureWidth,
			eiDDInfo.D3DDeviceDesc.dwMaxTextureWidth
			);
		eiDebugWriteFile(s);

		sprintf(s,"\tAddAlpha %c\n",
			eiDDInfo.D3DDeviceDesc.dpcTriCaps.dwDestBlendCaps
			& D3DPBLENDCAPS_ONE ? 't' : 'f'
			);
		eiDebugWriteFile(s);
	}
eidbMsg("(eiCreate3DDevice)デバイスの能力を取得");

	//---テクスチャフォーマット初期化
	eiDDInitIMTextureFormats();

	return 1;
}

//---解放する
int eiReleaseD3Device(void)
{

	int r = 0;
	//---Ｚバッファーのアタッチを解除
//	eiSurface[0].lpSurface->Restore();
//	eiSurface[1].lpSurface->Restore();
//	eiZBuffer[0].lpSurface->Restore();
/*	if((r = eiSurface[1].lpSurface->DeleteAttachedSurface(0,eiZBuffer[0].lpSurface)) != DD_OK){
		eiDebugWriteFile("(eiReleaseD3Device) DeleteAttachedSurface Fail\n");

		if(r == DDERR_CANNOTDETACHSURFACE)
			eiDebugWriteFile("DDERR_CANNOTDETACHSURFACE\n");
		if(r == DDERR_INVALIDOBJECT)
			eiDebugWriteFile("DDERR_INVALIDOBJECT\n");
		if(r == DDERR_INVALIDPARAMS)
			eiDebugWriteFile("DDERR_INVALIDPARAMS\n");
		if(r == DDERR_SURFACELOST)
			eiDebugWriteFile("DDERR_SURFACELOST\n");
		if(r == DDERR_SURFACENOTATTACHED)
			eiDebugWriteFile("DDERR_SURFACENOTATTACHED\n");
	}
	eiDebugWriteFile("(eiReleaseD3Device) DeleteAttachedSurface()\n");
*/
	//---Ｚバッファー解放
	if(eiZBuffer[0].Release() == 0){
		eiDebugWriteFile("(eiReleaseD3Device) ZBuffer Release Fail\n");
	} else {
		eiDebugWriteFile("(eiReleaseD3Device) ZBuffer Released\n");
	}

eiDebugWriteFile("(eiReleaseD3Device) Start\n");
	if(eiDDInfo.lpD3DDevice != NULL){
		if(eiDDInfo.lpD3DDevice->Release() > 0){
			eiDebugWriteFile("(eiReleaseD3Device) lpD3DDevice Fail\n");
		}
		eiDebugWriteFile("(eiReleaseD3Device) lpD3DDevice Released\n");
		eiDDInfo.lpD3DDevice = NULL;
	}
	if(eiDDInfo.lpD3DDevice2 != NULL){
		if(eiDDInfo.lpD3DDevice2->Release() > 0){
			eiDebugWriteFile("(eiReleaseD3Device) lpD3DDevice2 Fail\n");
		}
		eiDebugWriteFile("(eiReleaseD3Device) lpD3DDevice2 Released\n");
		eiDDInfo.lpD3DDevice2 = NULL;
	}


eiDebugWriteFile("(eiReleaseD3Device) End\n");
	return 1;
}
