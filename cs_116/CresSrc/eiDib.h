#ifndef EIDIB_H
#define EIDIB_H

//---DIB
class EI_API eiDib
{
public:
	eiDib(void);
	~eiDib();

	void Init(void);
	void Delete(void/*int mode = 1 */);
	int Create(int hx,int hy,int color,int mode = 0);

	int GetAddres(int x,int y);
#ifdef EIUSE_DIRECTDRAW
		int CopyToDDSurface(eiDDSurface *esDst,int x,int y,LPRECT lpRect = NULL,int trans = 1);
		int CopyDDSurfaceTo(eiDDSurface *esDst,int x,int y,LPRECT lpRect = NULL);
#endif
	
	int Read(EISTR *name,EISTR *slname,int mode);
	int Save(EISTR *name);
	int Put(eiDib *dib,int dx,int dy,LPRECT lpRect,int efect = 0);
	int PutTrans(eiDib *dib,int dx,int dy,LPRECT lpRect,int efect = 0);

	int PutClip(eiDib *dib,int x,int y,LPRECT lpSrc = NULL);
	int PutTransClip(eiDib *dib,int x,int y,LPRECT lpSrc = NULL);
	int PutExtend(eiDib *dib,int x,int y,
							  double xRate,double yRate,int efect);
	int CopyToDC(HDC hdc,int x,int y,double rx = 1.000,double ry = 1.000,LPRECT lpRect = NULL);

	int DibText(EISTR *String,int x,int y,int color,int efect = EI_TRANS);

	void DrawLineNextX(int xp,int yp,int dx,int dy,int dirVector,
					   int color,int mode);
	void DrawLineNextY(int xp,int yp,int dx,int dy,int dirVector,
					   int color,int mode);
	void DrawLine(int x1,int y1,int x2,int y2,
			   int col,int mode);
	void DrawBox(int x1,int y1,int x2,int y2,
			   int col,int mode = 0);
	void DrawFillBox(int x1,int y1,int x2,int y2,
			   int col,int mode = 0);
	int DrawPixel(int x,int y,int col,int efect = EI_PSET);
	int GetPixel(int x,int y,int efect = EI_PSET);

	//---パレット
	int ToRGB(int num,int bit = 0);
	int MakeRGB(int red,int green,int blue,int bit = 0);
	int SeekNearColor(int red,int green,int blue);
	int CopyPalette(eiDib *lpDib);
	int SetPalette(int num,int red,int green,int blue);
	int GetPaletteRed(int num);
	int GetPaletteGreen(int num);
	int GetPaletteBlue(int num);

	//---test
	void CheckMemory(void);

	LPBYTE lpBitmap;
	LPBITMAPINFO lpBitmapInfo;
	LPBITMAPINFOHEADER lpbih;
	LPRGBQUAD lpRGB;
	EIMEMORY hgBitmap,hgBitmapInfo;
	HBITMAP hBitmap;
	//---DIBSection用
	HDC hMemoryDC;
	HWND hwnd;

	int xSize,ySize,Color;
	int LineSize,BitmapSize,TransColor,InfoSize;

//	eistr FileName[32];
};

#endif /* EIDIB_H */
