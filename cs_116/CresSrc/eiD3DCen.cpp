/*-----------------------------------------------------------

   eiLibray
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   eiD3DCen.cpp ...Direct3D

-----------------------------------------------------------*/

extern EI_DDINFO eiDDInfo;
extern eiDDSurface eiSurface[32];
extern eiDDSurface eiZBuffer[1];

static int InitDirect3DFlag = 0;
int eid3dWait = 0;

//extern void eidbMsg(char *msg);
#define eidbMsg(x)


#include "eiD3D_Device.cpp"
#include "eiD3D_Light.cpp"
#include "eiD3D_Material.cpp"
#include "eiD3D_ViewPort.cpp"
#include "eiD3D_Matrix.cpp"
#include "eiD3D_VertexBuffer.cpp"
#include "eiD3D_Particle.cpp"

int EI_API eiInitDirect3D(void)
{
	if(InitDirect3DFlag)
		return 1;

	InitDirect3DFlag = 1;

	if(!eiCreate3DDevice())
		//---３Ｄデバイスを作成
		return 0;

	return 1;
}

int EI_API eiEndDirect3D(void)
{
	if(InitDirect3DFlag == 0)
		return 1;

	eiReleaseD3Device();

	InitDirect3DFlag = 0;

	return 1;
}

//--------------------------------------------
//--------------------------------------------
//---Direct3D全体を管理するクラス
eiD3D::eiD3D(void)
{
	NowDrawing3D = 0;
	Wait = 0;
}

eiD3D::~eiD3D(void)
{
}

int eiD3D::InitDirect3D(void)
{
	int ret = eiInitDirect3D();

	if(!ret)
		return ret;

	Begin();
	eiDDInfo.lpD3DDevice->SetRenderState( D3DRENDERSTATE_DITHERENABLE, FALSE);
	eiDDInfo.lpD3DDevice->SetRenderState( D3DRENDERSTATE_SPECULARENABLE,FALSE);
	eiDDInfo.lpD3DDevice->SetRenderState( D3DRENDERSTATE_ZENABLE ,TRUE);
	eiDDInfo.lpD3DDevice->SetRenderState( D3DRENDERSTATE_ZWRITEENABLE ,TRUE);
	End();

	lpD3DDevice = eiDDInfo.lpD3DDevice;

	return ret;
}

int eiD3D::EndDirect3D(void)
{
	return eiEndDirect3D();
}


//---描画開始
int eiD3D::Begin(int wait /* = 1*/)
{
	HRESULT result = eiDDInfo.lpD3DDevice->BeginScene();

	if(result == D3D_OK){
		if(wait){
//			eiWaitCriticalSection(1);
		}
		NowDrawing3D = 1;
		return 1;
	} else {
		eiDebugWriteFile("(eiD3D::Begin) fail\n");
	}

	return 0;
}

//---描画終了
int eiD3D::End(int release /* = 1*/)
{
	if(NowDrawing3D){
		eiDDInfo.lpD3DDevice->EndScene();
		if(release){
//			eiReleaseCriticalSection();
		}
	}
	NowDrawing3D = 0;

	return 1;
}

//---DrawPrimitiveのウェイト指定
int eiD3D::GetWait(void)
{
	return Wait;
}

int eiD3D::SetWait(int wait)
{
	int old = GetWait();

	eid3dWait = Wait = wait;

	return old;
}

//---描画設定
int eiD3D::SetDrawMode(int mode)
{
	if(mode == EID3D_DRAWMODE_FILL){
		eiDDInfo.lpD3DDevice->SetRenderState(D3DRENDERSTATE_FILLMODE,D3DFILL_SOLID);
	} else if(mode == EID3D_DRAWMODE_LINE){
		eiDDInfo.lpD3DDevice->SetRenderState(D3DRENDERSTATE_FILLMODE,D3DFILL_WIREFRAME);
	} else if(mode == EID3D_DRAWMODE_POINT){
		eiDDInfo.lpD3DDevice->SetRenderState(D3DRENDERSTATE_FILLMODE,D3DFILL_POINT);
	} else if(mode == EID3D_DRAWMODE_CULLNONE){
		eiDDInfo.lpD3DDevice->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
	} else if(mode == EID3D_DRAWMODE_CULLCW){
		eiDDInfo.lpD3DDevice->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_CW);
	}

	return 1;
}

//-------------------------------------------
//---テクスチャステイト初期化
void eiD3D::InitTextureState(void)
{
	eiDDInfo.lpD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	eiDDInfo.lpD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	eiDDInfo.lpD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
	eiDDInfo.lpD3DDevice->SetTextureStageState( 0, D3DTSS_ADDRESS,   D3DTADDRESS_CLAMP);

	SetTextureFilter(EID3D_TEXFILTER_LINER);

	//---ポリゴンの塗り方
	D3DDEVICEDESC7 desc;

	memset(&desc,0,sizeof(desc));
	eiDDInfo.lpD3DDevice->GetCaps(&desc);

	if(desc.dpcTriCaps.dwShadeCaps & D3DSHADE_GOURAUD){
		eiDDInfo.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SHADEMODE,D3DSHADE_GOURAUD);
	} else {
		eiDDInfo.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SHADEMODE,D3DSHADE_FLAT);
	}
}

//---テクスチャモード
void eiD3D::SetTextureFilter(int mode)
{
	if(mode == EID3D_TEXFILTER_POINT){
		eiDDInfo.lpD3DDevice->SetTextureStageState( 0, D3DTSS_MINFILTER, D3DTFN_POINT);
		eiDDInfo.lpD3DDevice->SetTextureStageState( 0, D3DTSS_MAGFILTER, D3DTFG_POINT);
	} else if(mode == EID3D_TEXFILTER_LINER){
		eiDDInfo.lpD3DDevice->SetTextureStageState( 0, D3DTSS_MINFILTER, D3DTFN_LINEAR);
		eiDDInfo.lpD3DDevice->SetTextureStageState( 0, D3DTSS_MAGFILTER, D3DTFG_LINEAR);
	}
}

//---テクスチャをセット
void eiD3D::SetTexture(eiTextureCell *lpTexture)
{
	if(lpTexture == NULL){
		eiDDInfo.lpD3DDevice->SetTexture(0,NULL);
		return;
	}

	if(lpTexture->lpd3dTexture == NULL){
		eiDDInfo.lpD3DDevice->SetTexture(0,NULL);
		return;
	}

	if(eiDDInfo.lpD3DDevice->SetTexture(0,lpTexture->lpd3dTexture) != D3D_OK){
		eiDebugWriteFile("(eiD3D) SetTexture fail\n");
	}
	eiDDInfo.lpD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
	eiDDInfo.lpD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,  D3DTOP_MODULATE );

//	eiDDInfo.lpD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
//	eiDDInfo.lpD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
//	eiDDInfo.lpD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );

//	eiDDInfo.lpD3DDevice->SetTextureStageState( 0, D3DTSS_ADDRESS,   D3DTADDRESS_CLAMP );

//    eiDDInfo.lpD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
}

void eiD3D::SetTextureColorkey(int mode /*= 0*/)
{
	if(mode)
		eiDDInfo.lpD3DDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE,TRUE);
	else
		eiDDInfo.lpD3DDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE,FALSE);
}

//--------------------------------------
void eiD3D::AddViewport(eiD3DViewport *lpViewport)
{
	if(lpViewport == NULL){
		if(eiDDInfo.lpD3DDevice->SetViewport(NULL) != DD_OK){
			eiDebugWriteFile("(eiD3D) AddViewport fail\n");
		}
	} else {
		if(eiDDInfo.lpD3DDevice->SetViewport(&lpViewport->d3dViewPort) != DD_OK){
			eiDebugWriteFile("(eiD3D) AddViewport fail\n");
		}
	}
}

void eiD3D::SetCurrentViewport(eiD3DViewport *lpViewport)
{
}

//---ライトをセット
void eiD3D::SetLight(eiD3DLight *lpLight,int index /*= 0*/)
{
	HRESULT ddrval;

	if(lpLight != NULL){
		ddrval = eiDDInfo.lpD3DDevice->SetLight(index,&lpLight->d3dLightStruct);
		ddrval = eiDDInfo.lpD3DDevice->LightEnable(index,1);
	} else {
//		ddrval = eiDDInfo.lpD3DDevice->SetLight(index,NULL);
		ddrval = eiDDInfo.lpD3DDevice->LightEnable(index,0);
	}
}

//----------------------------------------
//---変換行列設定
void eiD3D::SetTransform(eiD3DMatrix *lpMatrix,D3DTRANSFORMSTATETYPE mode)
{
	if(lpMatrix != NULL){
		if(eiDDInfo.lpD3DDevice->SetTransform(mode,lpMatrix->lpd3dMatrix) != DD_OK){
			eiDebugWriteFile("(eiD3D) SetTransform fail\n");
		}
	} else {
/*		if(eiDDInfo.lpD3DDevice->SetTransform(mode,NULL) != DD_OK){
			eiDebugWriteFile("(eiD3D) SetTransform fail\n");
		}*/
	}
}

void eiD3D::SetTransformWorld(eiD3DMatrix *lpMatrix)
{
	if(lpMatrix != NULL){
		SetTransform(lpMatrix,D3DTRANSFORMSTATE_WORLD);
	} else {
		SetTransform(NULL,D3DTRANSFORMSTATE_WORLD);
	}
}

void eiD3D::SetTransformView(eiD3DMatrix *lpMatrix)
{
	if(lpMatrix != NULL){
		SetTransform(lpMatrix,D3DTRANSFORMSTATE_VIEW);
	} else {
		SetTransform(NULL,D3DTRANSFORMSTATE_VIEW);
	}
}

void eiD3D::SetTransformProjection(eiD3DMatrix *lpMatrix)
{
	SetTransform(lpMatrix,D3DTRANSFORMSTATE_PROJECTION);
}

//----------------------------------------
//---アルファブレンド
void eiD3D::BeginAlphaBlend(void)
{
	eiDDInfo.lpD3DDevice->SetRenderState(D3DRENDERSTATE_BLENDENABLE,TRUE);
	eiDDInfo.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,TRUE); // アルファブレンド有効化

	eiDDInfo.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND,D3DBLEND_SRCALPHA);     // ソースブレンド設定
	eiDDInfo.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_INVSRCALPHA); // ディスティネーション設定

//	eiDDInfo.lpD3DDevice->SetRenderState(D3DRENDERSTATE_TEXTUREFACTOR,D3DTOP_BLENDFACTORALPHA);

//	eiDDInfo.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND,D3DBLEND_BOTHSRCALPHA);     // ソースブレンド設定
}

void eiD3D::EndAlphaBlend(void)
{
	eiDDInfo.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,FALSE);
	eiDDInfo.lpD3DDevice->SetRenderState(D3DRENDERSTATE_BLENDENABLE,FALSE);
}

//---フォグ
void eiD3D::SetFog(int mode)
{
	if(mode == 1){
		D3DCOLOR col;
		col = RGBA_MAKE(255,255,255,0);
		SetFogColor(col);

		//---フォグモード
		eiDDInfo.lpD3DDevice->SetRenderState(D3DRENDERSTATE_FOGTABLEMODE,D3DFOG_LINEAR);
		//---フォグ密度
		eiDDInfo.lpD3DDevice->SetRenderState(D3DRENDERSTATE_FOGTABLEDENSITY,0);

		eiDDInfo.lpD3DDevice->SetRenderState(D3DRENDERSTATE_FOGENABLE,TRUE);
	} else {
		eiDDInfo.lpD3DDevice->SetRenderState(D3DRENDERSTATE_FOGENABLE,FALSE);
	}
}

//---フォグカラー
void eiD3D::SetFogColor(D3DCOLOR col)
{
	eiDDInfo.lpD3DDevice->SetRenderState(D3DRENDERSTATE_FOGCOLOR,col);
}

//----------------------------------------
//---ライト
void eiD3D::SetAmbientLight(D3DCOLOR col)
{
	eiDDInfo.lpD3DDevice->SetRenderState(D3DRENDERSTATE_AMBIENT,col);
//	eiDDInfo.lpD3DDevice->SetRenderState(D3DRENDERSTATE_LIGHTING ,1);
}
//---マテリアルをセット
void eiD3D::SetMaterial(eiD3DMaterial *pMaterial)
{
	if(pMaterial != NULL){
		if(eiDDInfo.lpD3DDevice->SetMaterial(&pMaterial->d3dMaterial) != D3D_OK){
			eiDebugWriteFile("(SetMaterial) failed 1\n");
		}
	} else {
/*		if(eiDDInfo.lpD3DDevice->SetMaterial(NULL) != D3D_OK){
			eiDebugWriteFile("(SetMaterial) failed 2\n");
		}*/
	}
}

//----------------------------------------
HRESULT eiD3D::DrawPrimitive(D3DPRIMITIVETYPE dptPrimitiveType, 
		DWORD  dwVertexTypeDesc,LPVOID lpvVertices,                 
		DWORD  dwVertexCount, DWORD  dwFlags)
{
/*	if(dwVertexTypeDesc == D3DFVF_VERTEX){
		D3DVERTEX *ver = (D3DVERTEX *)lpvVertices;

		for(int b = 0;b < (int)dwVertexCount;b ++){
			float div = (float)sqrt(
				ver[b].nx * ver[b].nx
				+ ver[b].ny * ver[b].ny
				+ ver[b].nz * ver[b].nz
			);
			if(!(0.98 <= div && div <= 1.02)){
				eiDebugWriteFile("not normalized\n");
			}
		}
	}*/

	return eiDDInfo.lpD3DDevice->DrawPrimitive(dptPrimitiveType,dwVertexTypeDesc,
		lpvVertices,dwVertexCount,
		dwFlags | (GetWait() ? D3DDP_WAIT : 0));// | D3DDP_DONOTUPDATEEXTENTS);
}
