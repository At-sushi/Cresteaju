
eiD3DViewport::eiD3DViewport(void)
{
	eimemset(&d3dViewPort,0,sizeof(d3dViewPort));

	d3dViewPort.dwX = 0;
	d3dViewPort.dwY = 0;
	d3dViewPort.dwWidth = 640;
	d3dViewPort.dwHeight = 480;

	float inv_aspect = (float) d3dViewPort.dwHeight / d3dViewPort.dwWidth;

	d3dViewPort.dvMinZ = 0.0f;
	d3dViewPort.dvMaxZ = 1.0f;
}

eiD3DViewport::~eiD3DViewport(void)
{
}

int eiD3DViewport::Create(LPD3DRECT lpRect /*= NULL*/)
{
	//---ビューポートの範囲
	if(lpRect != NULL){
		SetRect(lpRect);
	} else {
		ViewRect.x1 = ViewRect.y1 = 0;
		ViewRect.x2 = eiSystem.xScreenSize;
		ViewRect.y2 = eiSystem.yScreenSize;
	}
 
	return 1;
}

void eiD3DViewport::Release(void)
{
}

void eiD3DViewport::Set(void)
{
	HRESULT ddrval;
	
	ddrval = eiDDInfo.lpD3DDevice->SetViewport(&d3dViewPort);
	if(ddrval != D3D_OK){
		eiDebugWriteFile("(eiD3DViewport) Set fail\n");
		if(ddrval == DDERR_INVALIDPARAMS)
			eiDebugWriteFile("(eiD3DViewport) パラメータが正しくない\n");
	}
}

//---範囲をセット
void eiD3DViewport::SetRect(LPD3DRECT lpRect)
{
	ViewRect = *lpRect;

	d3dViewPort.dwX = lpRect->x1;
	d3dViewPort.dwY = lpRect->y1;
	d3dViewPort.dwWidth = lpRect->x2;
	d3dViewPort.dwHeight = lpRect->y2;

	float inv_aspect = (float) d3dViewPort.dwHeight / d3dViewPort.dwWidth;

	d3dViewPort.dvMinZ = 0.0f;
	d3dViewPort.dvMaxZ = 1.0f;
}

void eiD3DViewport::SetRect(int x1,int y1,int x2,int y2)
{
	D3DRECT rect = {x1,y1,x2,y2};

	SetRect(&rect);
}

//---バックグラウンドマテリアル
void eiD3DViewport::SetBackground(eiD3DMaterial *lpMaterial)
{
}

//---ライトを追加
void eiD3DViewport::AddLight(eiD3DLight *lpLight)
{
	HRESULT ddrval;

//	ddrval = lpd3dViewport->AddLight(lpLight->lpd3dLight); 
	ddrval = eiDDInfo.lpD3DDevice->SetLight(0,&lpLight->d3dLightStruct);
	ddrval = eiDDInfo.lpD3DDevice->LightEnable(0,1);
//	ddrval = eiDDInfo.lpD3DDevice->SetRenderState(D3DRENDERSTATE_LIGHTING ,1);
}

//---全部消去！
void eiD3DViewport::ClearAll(LPD3DRECT lpRect /*= NULL*/)
{
	D3DRECT rect = {ViewRect.x1,ViewRect.y1,ViewRect.x1 + ViewRect.x2,ViewRect.y1 + ViewRect.y2};

	if(lpRect == NULL){
		lpRect = &rect;
	}

	ClearBackground(lpRect);
	ClearZBuffer(lpRect);
}

void eiD3DViewport::ClearZBuffer(LPD3DRECT lpRect /*= NULL*/)
{
	D3DRECT rect = {ViewRect.x1,ViewRect.y1,ViewRect.x1 + ViewRect.x2,ViewRect.y1 + ViewRect.y2};

	if(lpRect == NULL){
		lpRect = &rect;
	}

	if(eiDDInfo.lpD3DDevice->Clear(
		1, lpRect,D3DCLEAR_ZBUFFER,0,D3DVALUE(1.0),0) != D3D_OK){
		eiDebugWriteFile("(eiD3DViewport) ClearZBuffer fail\n");
	}
}

void eiD3DViewport::ClearBackground(LPD3DRECT lpRect /*= NULL*/)
{
	D3DRECT rect = {ViewRect.x1,ViewRect.y1,ViewRect.x1 + ViewRect.x2,ViewRect.y1 + ViewRect.y2};

	if(lpRect == NULL){
		lpRect = &rect;
	}

	if(eiDDInfo.lpD3DDevice->Clear(
		1, lpRect,D3DCLEAR_TARGET,0,D3DVALUE(1.0),0) != D3D_OK){
		eiDebugWriteFile("(eiD3DViewport) ClearBackground fail\n");
	}
}


void eiD3DViewport::GetRect(LPD3DRECT *lpRect)
{
	static D3DRECT rect;
	
	rect.x1 = ViewRect.x1;
	rect.y1 = ViewRect.y1;
	rect.x2 = ViewRect.x1 + ViewRect.x2;
	rect.y2 = ViewRect.y1 + ViewRect.y2;

	*lpRect = &rect;
}

//---フリップする
void eiD3DViewport::Flip(LPD3DRECT lpRect /*= NULL*/)
{
	LPD3DRECT rect;

	GetRect(&rect);

	(eiGetSurfacePointer() + 1)->PutExtend(
		(eiGetSurfacePointer() + 0),rect->x1,rect->y1,(LPRECT)rect,DDBLT_WAIT,1.00,1.00);
}

//---ビューポートの範囲内に座標があるか
int eiD3DViewport::InViewport(float x,float y)
{
	LPD3DRECT rect;

	GetRect(&rect);

	if(rect->x1 <= (int)x && (int)x <= rect->x2
		&& rect->y1 <= (int)y && (int)y <= rect->y2)
		return 1;

	return 0;
}
