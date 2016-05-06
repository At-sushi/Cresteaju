#ifndef EICELL_H
#define EICELL_H

//---セル
class EI_API eiCell
{
public:
	eiCell(void);
	~eiCell();
	int Create(int sx,int sy,int color = 8,int dib_mode = 0);
	int Release(void);
	int Delete(void);
	//---ファイル処理
	int ReadDIB(EISTR *name,EISTR *slname,int mode);
	int ReadFile(EISTR *name,EISTR *slname,int mode);
	//---クリッピング
	void SetClipingRect(LPRECT rect);

	//---転送関数
	void Clear(int col = 16);
	void SetSurface(LPRECT lpRect = NULL,int plane = 2,int trans = 1);
//	void SetSurface(LPRECT lpRect,eiSurface *lpTempSurface);
	int Put(eiCell *cell,int x,int y);
	int PutClip(eiCell *cell,int x,int y,LPRECT lpSrc = NULL,int efect = 0);
	int PutTrans(eiCell *cell,int x,int y);
	int PutClipSelect(eiCell *cell,int x,int y,LPRECT lpSrc,int trans,int efect = 0);
	int PutTransClip(eiCell *cell,int x,int y,LPRECT lpSrc = NULL,int efect = 0);
	int PutExtend(eiCell *cell,int x,int y,
							  double xRate = 1.00,double yRate = 1.00,
							  int efect = EI_PSET,LPRECT lpSrc = NULL);
//	int PutExtend2(eiCell *cell,LPRECT lpDst,int efect = EI_PSET,LPRECT lpSrc = NULL);
//							  int efect = EI_PSET,LPRECT lpSrc = NULL);
	int PutFile(int x,int y,
		EISTR *name,EISTR *slname,int mode);

	int Copy(eiCell *cell,int x,int y,LPRECT lpSrcRect);

	//---描画関数
	int DrawCalcPos(int &x1,int &y1,int &x2,int &y2);

	void DrawLine(int x1,int y1,int x2,int y2,int col,int efect = EI_PSET);
	void DrawBox(int x1,int y1,int x2,int y2,int col,int efect = EI_PSET);
	void DrawFillBox(int x1,int y1,int x2,int y2,int col,
		int efect = EI_PSET,int alpha = 255);
	//---アルファ値あり
	void DrawFillBoxAlpha(int x1,int y1,int x2,int y2,
		int col,int alpha = 255);
	
	void DrawText(EISTR *string,int x,int y,int color,int efect = EI_TRANS);
	void DrawTextDirect(EISTR *string,int x,int y,int color,int efect = EI_TRANS);
	//---点打ち
	void DrawPixel(int x,int y,int col,int efect = EI_PSET);
	int GetPixel(int x,int y,int efect = EI_PSET);

	//---ロック
	int Lock(EILOCKEDCELL *ec);
	void UnLock(void);

	CELLDATA Data;
	eiDib dib;
	EIMEMORY hDumy;
#ifdef EIUSE_DIRECTDRAW
	eiDDSurface *pDDSurface;
#endif
};

#ifdef EIUSE_DIRECTDRAW
//---テクスチャー
class EI_API eiTextureCell : public eiCell
{
public:
	eiTextureCell(void);
	~eiTextureCell();
	void Init(int color = 0);

	void SetTextureSurfaceColor(int color);
	int CreateTexture(int sx,int sy,int color);
	int CreateSurface(void);
	int CreatePalette(void);
	int CreateFromSurface(int sx,int sy,int color,eiDDSurface *pSurface,RECT *pSrcRect);
	int LoadFromSurface(eiDDSurface *pSurface,RECT *pRect);
	int Load(int trans = 1);
	int ReleaseTexture(void);
#ifdef EIUSE_DIRECT3D
	D3DTEXTUREHANDLE GetHandle(void);
#endif /* EIUSE_DIRECT3D */

	int TextureSurfaceColor;
	eiDDSurface Texture;
	eiDDPalette Palette;
	LPDIRECTDRAWSURFACE7 lpd3dTexture;
	EIMEMORY hDumy2;
};
#endif /* EIUSE_DIRECTDRAW */

#endif /* EICELL_H */
