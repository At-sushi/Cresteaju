//-------------------------------------------------------------
#ifdef EI_RUNWINDOWS

#ifndef EIDDRAW_H
#define EIDDRAW_H

#ifdef EIUSE_DIRECT3D

typedef struct {
    DDSURFACEDESC ddsd;
    BOOL bPalettized;
	BOOL bFound;
	int FindBPP,BPP;
    int RedBPP;
    int BlueBPP;
    int GreenBPP;
    int IndexBPP;
} EI_TEXTUREFORMAT;

#endif /* EIUSE_DIRECT3D */

typedef struct
{
	int UseHardware3D,Use3D,Use3DHEL,UseWindow;
	int DDSurfaceColor;
	int ZBufferDepth,ZBufferEnumDepth[32];

#ifdef EIUSE_DIRECT3D
	D3DCOLORMODEL ColorModel;
	EI_TEXTUREFORMAT TextureFormat[64];
	DDPIXELFORMAT ddpZBufferFormat;

	eistr Direct3DUsingDeviceName[256];

	D3DDEVICEDESC7 D3DDeviceDesc;
#endif /* EIUSE_DIRECT3D */

	LPDIRECTDRAW lpDDOld;
	LPDIRECTDRAW7 lpDD;

	LPDIRECTDRAWPALETTE lpDDPalette;
	LPDIRECTDRAWCLIPPER lpDDClipper;

#ifdef EIUSE_DIRECT3D
	LPDIRECT3D7 lpD3D;
	LPDIRECT3D lpD3DOld;
	LPDIRECT3DDEVICE7 lpD3DDevice;
	LPDIRECT3DDEVICE2 lpD3DDevice2;
	LPGUID lpD3DDeviceGuid;
#endif /* EIUSE_DIRECT3D */

	LPDIRECTDRAWSURFACE7 lpPrimaryBuffer,lpBackBuffer;
	int DDHEL;

} EI_DDINFO, *LPEI_DDINFO;

//---サーフェイス
class EI_API eiDDSurface
{
public:
	eiDDSurface(void);
	int Create(int xs,int ys,int mode,eiDDSurface *esDst = NULL,int color_bit = 0);
	int Release(void);

	LPDIRECTDRAWSURFACE7 GetDirect3DTexture(void);

	int Restore(void);

	int SetSrcBltColorKey(int StartCol,int EndCol);
//	DWORD PaletteToSurfaceRGB(LPRGBQUAD lpRGB);

	HRESULT Put(eiDDSurface *esDst,int x,int y,LPRECT rect,int mode = 0);
	HRESULT PutExtend(eiDDSurface *esDst,int x,int y,LPRECT rect,int mode,
			 double xRate,double yRate);
	HRESULT eiDDSurface::PutExtend2(eiDDSurface *esDst,LPRECT lpDstRect,
			LPRECT lpSrcRect,int mode);
	
	void DrawPixel(int x,int y,int col,int efect = EI_PSET);
	int GetPixel(int x,int y,int efect = EI_PSET);
	void DrawFillBox(int x1,int y1,int x2,int y2,int col,int efect = EI_PSET);
	void DrawBox(int x1,int y1,int x2,int y2,int col,int efect = EI_PSET);
	void DrawLine(int x1,int y1,int x2,int y2,int col,int efect = EI_PSET);
	void DrawLineNextX(int xp,int yp,int dx,int dy,int dirVector,int color,int efect);
	void DrawLineNextY(int xp,int yp,int dx,int dy,int dirVector,int color,int efect);

	int DDSurfaceText(EISTR *String,int x,int y,int color,int efect = EI_TRANS);
	int DDSurfaceTextDirect(EISTR *String,int x,int y,int color,int efect = EI_TRANS);

	int Lock(LPBYTE *lpMemory,int *Pitch,LPRECT lpRect = NULL);
	void UnLock(void);
	void Flip(int mode = 0);
	void WaitVSync(void);

	LPDIRECTDRAWSURFACE lpSurfaceOld;
	LPDIRECTDRAWSURFACE7 lpSurface;
	int xSize,ySize,Color,SurfaceMode;
	DWORD RedMask,GreenMask,BlueMask,
		RedShift,GreenShift,BlueShift,
		RedBit,GreenBit,BlueBit;
	DDSURFACEDESC2 DDSurfaceDesc;
	EIMEMORY hDumy;
};

//---パレット
class EI_API eiDDPalette
{
public:
	eiDDPalette(void);
	int Create(int mode = 1);
	int Release(void);
	int SetSurface(eiDDSurface *lpSurface);
	void SetEntries(LPPALETTEENTRY pe);
	int Set(int number,int red,int green,int blue,int mode = 0);
	void Black(void);
	void Fadein(int wait,int count,int efect);
	void Fadeout(int wait,int count,int efect);
	void Push(void);
	void Pop(void);

	LPDIRECTDRAWPALETTE lpPalette;
	PALETTEENTRY PaletteEntries[256],KeepEntries[256],BackEntries[256];
	int PaletteMode;
	int WaitCount;
	eiTime Wait;
	EIMEMORY hDumy;
};

EI_API int eiIsDirectDrawHAL(void);
EI_API int eiGetDDMaxViedoMemory(void);
EI_API int eiGetDDFreeViedoMemory(void);

#endif /* EIDDRAW_H */
#endif /*EI_RUNWINDOWS */
//-------------------------------------------------------------
