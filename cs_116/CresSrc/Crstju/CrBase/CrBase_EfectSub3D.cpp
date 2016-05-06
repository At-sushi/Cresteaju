#define EFECT_MODE_1

CRBASE_EFECTAPI void crefectScreenEfect_Bomb(RECT *pRect /*= NULL*/,int count /*= -1*/,int vel /*= -1*/)
{
	eiDebugWriteFile("Begin:crefectScreenEfect_Bomb\n");
	eiWaitCriticalSection(1000);

	eiD3DMaterial Material;
	crefectSetup3DEfect();

	Material.Create();
	Material.SetDeffuseColor(255,255,255,255);

	int tx = 80,ty = 32;
	int sx = pRect->right - pRect->left,
		sy = pRect->bottom - pRect->top,
		size = 16,scale = 0;

	if(crsysGetExtentionLevel() < 3){
		size = 32;
	}
	size = 16;
	float rate = ((float)size / 16);

	int UseTex = 1,a,b,x,y,tri_count = ((sx / size) * (sy / size)) * 2;
	int RunTime = 1000;
	float ex = 1.0f,ey = 1.0f;
#ifdef EFECT_MODE_1
	float ay = 0.658f,//0.669
#else
	float ay = 0.5f,//0.5// 0.669f,
#endif
		dx = -(float)sx / (float)size / 2.0f,
		dy = -(float)sy / (float)size / 2.0f;//0.5778f;
	//---移動速度
	int vel_x = 600,vel_y = 600,vel_z = 1000;
	//---分割するテクスチャの大きさ
	int t_size_x = 256,t_size_y = 256;//256,64
	//---１ラインのテクスチャ数
	int x_line = sx / t_size_x , y_add = t_size_y / size;
	if(sx % t_size_x)
		x_line ++;
	//---テクスチャ１個に収まるパターン数
	int x_count = sx / size,
		y_count = sy / size;
	float u,v,
//		eu = 1.0f / (float)(sx / size),
//		ev = 1.0f / (float)(sy / size);
		eu = 1.0f / (float)x_count,
		ev = 1.0f / (float)y_count;

	D3DVECTOR vNormal( 0.0f, 0.0f, -1.0f );

	static D3DVECTOR MoveVector[2400];
	static EI_TRIANGLE_VERTEX Vertex[2400];
	static float Distanse[2400];

	D3DVECTOR *pMoveVector = &MoveVector[0];//new D3DVECTOR[tri_count + 32];
	EI_TRIANGLE_VERTEX *pVertex = &Vertex[0];//new EI_TRIANGLE_VERTEX[tri_count + 32];
	float *pDistanse = &Distanse[0];//new float[tri_count + 32];
#ifdef EFECT_MODE_1
	eiTextureCell *pTex = new eiTextureCell[1];
	eiMemorySetPointerForDebug(pTex);
#endif
	if(count != -1)
		RunTime = count;

crdataEnableRec(0);

	int time2;
#ifdef EFECT_MODE_1
//---テクスチャを作る--------------------
	int time1;
//	eiSetDebugMode(0);
	et->Reset();
	RECT CopyRect = {0,0,640,480};
	CopyRect = *pRect;
	if(eiGetSurfacePointer()->Color == 16){
//		pTex[0].Init(16);
	} else {
//		pTex[0].Init(32);
	}
	pTex[0].Init(16);

	if(pTex[0].CreateFromSurface(
		t_size_x >> scale,t_size_y >> scale,16,
		(eiGetSurfacePointer() + 1),
		&CopyRect) == 0){
		//---テクスチャが画面からコピーできない場合
		UseTex = 0;
	}
//------------------------------------

	time1 = et->Get();
	char s[80];
	sprintf(s,"tex_time:%d\n",time1);
	eiDebugWriteFile(s);
//	eiSetDebugMode(1);
	et->Reset();
#endif

	//---頂点データを作る
	for(y = 0,a = 0;y < sy / size;y ++){
		v = (float)(1.0f / ((float)sy / (float)size) * (float)y);
		for(x = 0;x < sx / size;x ++,a += 2){
			u = (float)(1.0f / ((float)sx / (float)size) * (float)x);
			D3DVECTOR p1(-0.5f * rate ,-ay * rate  , 0.0f);
			D3DVECTOR p2( 0.5f * rate  ,-ay * rate  , 0.0f);
			D3DVECTOR p3(-0.5f * rate  , ay * rate  , 0.0f);
			D3DVECTOR p4( 0.5f * rate  , ay * rate  , 0.0f);

			pVertex[a].Vertex[0] = D3DVERTEX( p1, vNormal, u     , v     );//0.0f, 0.0f );
			pVertex[a].Vertex[1] = D3DVERTEX( p2, vNormal, u + eu, v     );//1.0f, 0.0f );
			pVertex[a].Vertex[2] = D3DVERTEX( p3, vNormal, u     , v + ev);//0.0f, 1.0f );

			pVertex[a].Vertex[3] = D3DVERTEX( p1, -vNormal, u     ,v      );//0.0f, 0.0f );
			pVertex[a].Vertex[4] = D3DVERTEX( p3, -vNormal, u     ,v + ev );//0.0f, 1.0f );
			pVertex[a].Vertex[5] = D3DVERTEX( p2, -vNormal, u + eu,v      );//1.0f, 0.0f );

			pDistanse[a] = pDistanse[a + 1] = (
				(x - ((float)sx / size / 2)) * (x - ((float)sx / size / 2))
				+ (y - ((float)sy / size / 2)) * (y - ((float)sy / size / 2))
				);

			//---回転
			pVertex[a].Rotate[1] = 0.0f;
			pVertex[a].RotateCount[1] = (float)eiRnd(100) / 1000.00f + 0.10f;
			if(eiRnd(100) < 50)
				pVertex[a].Rotate[1] = -pVertex[a].Rotate[1];

			//--------------------
			pVertex[a + 1].Vertex[0] = D3DVERTEX( p2, vNormal, u + eu , v     );//1.0f, 0.0f );
			pVertex[a + 1].Vertex[1] = D3DVERTEX( p3, vNormal, u      , v + ev);//0.0f, 1.0f );
			pVertex[a + 1].Vertex[2] = D3DVERTEX( p4, vNormal, u + eu , v + ev);//1.0f, 1.0f );

			pVertex[a + 1].Vertex[3] = D3DVERTEX( p2, -vNormal, u + eu , v     );//1.0f, 0.0f );
			pVertex[a + 1].Vertex[4] = D3DVERTEX( p4, -vNormal, u + eu , v + ev);//1.0f, 1.0f );
			pVertex[a + 1].Vertex[5] = D3DVERTEX( p3, -vNormal, u      , v + ev);//0.0f, 1.0f );

			//---回転
			pVertex[a + 1].Rotate[1] = 0.0f;
			pVertex[a + 1].RotateCount[1] = (float)eiRnd(100) / 1000.00f + 0.01f;
			if(eiRnd(100) < 50)
				pVertex[a + 1].Rotate[1] = -pVertex[a + 1].Rotate[1];

			for(b = 0;b < 2;b ++){
				pVertex[a + b].TexNumber = 0;
				//---位置ベクトル
				pVertex[a + b].MoveVector = D3DVECTOR(
					(float)(x * ex + dx) * rate ,
					(float)(y * ey * ay * 2.0f  + dy) * rate ,0.0f);
				//---移動ベクトル
				pVertex[a + b].MoveVectorCount = D3DVECTOR(
					((float)x - ((float)sx / size / 2)) / 250.00f
					+ (float)(eiRnd(vel_x) - (vel_x >> 1)) / 10000.00f,
					((float)y - ((float)sy / size / 2)) / 250.00f
					+ (float)(eiRnd(vel_y) - (vel_y >> 1)) / 10000.00f,
					0.51f
//					(float)(-eiRnd(vel_z)) / 1000.00f + 0.01f
					);
			}
		}
	}

	sprintf(s,"pol:%d\n",a);
	eiDebugWriteFile(s);

	time2 = et->Get();

//	sprintf(s,"%d  %d",time1,time2);
//	SetWindowText(ew.hwnd,s);

	eiD3DMatrix matCamera,matWorld,matTemp1,matTemp2,matTemp3,matTemp4;

/*	eiD3DMatrix matProjection;
	matProjection.CalcProjectionMatrix(0.5f,100.0f,3.14f / 4.0f);
	eid3d->SetTransformProjection(&matProjection);
*/
	matWorld.IdentityMatrix();
/*	matCamera.CalcCamera(
		D3DVECTOR(-0.5f,-0.5f, 40.0f / (size / 16)),
		D3DVECTOR(-0.5f,-0.5f,-20.0f),
		D3DVECTOR(0.0f,1.0f,0.0f),3.14f);*/
	matCamera.CalcCamera(
		D3DVECTOR(-0.5f,3.5f, 47.75f / (16 / 16)),
		D3DVECTOR(-0.5f,3.5f,-20.0f),
		D3DVECTOR(0.0f,1.0f,0.0f),3.14f);
crdataEnableRec(1);

	int debug_time = GetTickCount(),frame = 0;
	int Start,Color,Now;
	float AddWorld = 0.0f,tsin,tcos;
//	RunTime = 5000;

	ew->lpCell[1]->DrawFillBox(
		(640 - (32 * crdataGetInitialize()->IniFile.FieldSizeX)) / 2, //80,32,
		(480 - (32 * crdataGetInitialize()->IniFile.FieldSizeY)) / 2,
		(640 - (32 * crdataGetInitialize()->IniFile.FieldSizeX)) / 2 + (32 * crdataGetInitialize()->IniFile.FieldSizeX),
		(480 - (32 * crdataGetInitialize()->IniFile.FieldSizeY)) / 2 + (32 * crdataGetInitialize()->IniFile.FieldSizeY),
		/*80 + 479,32 + 415,*/ep->ToRGB(CRCOLOR_WHITE));
	ew->Refresh();

	crsoundPlay(CRSOUND_WARERU);

	for(Start = et->GetTime();et->GetTime() - Start < RunTime;){
		et->Reset();
		Now = et->GetTime() - Start;

//---デバッグ計測用--------------------
		if(GetTickCount() - debug_time >= 1000){
/*			char s[80];
			debug_time= GetTickCount();
			sprintf(s,"%d",frame);
			SetWindowText(ew->hwnd,s);
			frame = 0;*/
		}
		frame ++;
//-------------------------------------

crdataEnableRec(0);
		pViewport->ClearAll();
		eid3d->SetTransformView(&matCamera);

		//---描画開始
		if(eid3d->Begin(0)){
			eid3d->SetDrawMode(EID3D_DRAWMODE_FILL);
			if(crsysGetExtentionLevel() <= 1){
				eid3d->SetDrawMode(EID3D_DRAWMODE_LINE);
			} else {
				eid3d->SetDrawMode(EID3D_DRAWMODE_CULLNONE);
			}
//			eid3d->BeginAlphaBlend();
//			eid3d->lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_ONE);

			//---ライト設定
			if(Now < RunTime / 2)
				Color = 255;
			else
				Color = 255 - (int)((float)(Now - RunTime / 2) / (float)(RunTime / 2) * 255);
			eid3d->SetAmbientLight(RGBA_MAKE(Color,Color,Color,255));
			eid3d->SetMaterial(&Material);

			eid3d->SetTexture(NULL);
			for(a = 0;a < tri_count;a ++){
				//---余計なのをクリップ
				if(pDistanse[a] >= (float)(RunTime - Now) * 0.6 + 10)
					continue;

				//---回転
				pVertex[a].Rotate[1] += (pVertex[a].RotateCount[1] * AddWorld * 0.1f);
				while(pVertex[a].Rotate[1] > 6.282f){
					pVertex[a].Rotate[1] -= 6.282f;
				}
				while(pVertex[a].Rotate[1] < 0.0f){
					pVertex[a].Rotate[1] += 6.282f;
				}

				tsin = (float)sin(pVertex[a].Rotate[1]);
				tcos = (float)cos(pVertex[a].Rotate[1]);

				//---平行移動
				pVertex[a].MoveVector.dvX += (pVertex[a].MoveVectorCount.dvX * AddWorld);
				pVertex[a].MoveVector.dvY += (pVertex[a].MoveVectorCount.dvY * AddWorld);
				pVertex[a].MoveVector.dvZ += (pVertex[a].MoveVectorCount.dvZ * AddWorld);
				matTemp1.Move(pVertex[a].MoveVector.dvX, pVertex[a].MoveVector.dvY,pVertex[a].MoveVector.dvZ);

				//---0
				matWorld.Set(0,0 ,tcos);
				matWorld.Set(0,1 ,0);
				matWorld.Set(0,2 ,tsin);
				matWorld.Set(0,3 ,0);
				//---1
				matWorld.Set(1,0 ,0);
				matWorld.Set(1,1 ,1);
				matWorld.Set(1,2 ,0);
				matWorld.Set(1,3 ,0);
				//---2
				matWorld.Set(2,0 ,-tsin);
				matWorld.Set(2,1 ,0);
				matWorld.Set(2,2 ,tcos);
				matWorld.Set(2,3 ,0);
				//---3
				matWorld.Set(3,0 ,pVertex[a].MoveVector.dvX);
				matWorld.Set(3,1 ,pVertex[a].MoveVector.dvY);
				matWorld.Set(3,2 ,pVertex[a].MoveVector.dvZ);
				matWorld.Set(3,3 ,1);
				eid3d->SetTransformWorld(&matWorld);
#ifdef EFECT_MODE_1
				if(UseTex){
					eid3d->SetTexture(&pTex[pVertex[a].TexNumber]);
				}
#endif
				eid3d->DrawPrimitive( D3DPT_TRIANGLELIST,
					D3DFVF_VERTEX,pVertex[a].Vertex, 3, 0);
			}
			//---描画終了
			eid3d->SetTexture(NULL);
			eid3d->SetMaterial(NULL);
//			eid3d->EndAlphaBlend();245,193 ,248
			eid3d->End(0);
		}
crdataEnableRec(1);

		//---フリップ
//eiSleep(1);
		if(eiGetEndThread() == 1){
			break;
		}
		ew->Flip();
		if(!eiGetFullScreen()){
//			et->Wait(1);
		}
//		if(frame == 1)
//			Sleep(1000);

		//---進める時間
		AddWorld = (float)et->Get() / 10.0f / (size / 16);// + ((float)Start - et->Get()) / 500000;
	}

crdataEnableRec(0);
	pViewport->ClearAll();
	Material.Release();

#ifdef EFECT_MODE_1
	//---テクスチャ解放
	pTex[0].ReleaseTexture();
	eiMemoryDeletePointerForDebug(pTex);
	delete[] pTex;
#endif
/*	delete[] pDistanse;
	delete[] pVertex;
	delete[] pMoveVector;*/

crdataEnableRec(1);
	eiReleaseCriticalSection();
	eiDebugWriteFile("End:crefectScreenEfect_Bomb\n");
}

CRBASE_EFECTAPI void crefectScreenEfect_RotateZoom(RECT *pRect /*= NULL*/,int count /*= -1*/,int vel /*= -1*/)
{
	eiWaitCriticalSection(1000);

	eiD3DMaterial Material;
	crefectSetup3DEfect();

	Material.Create();

	int tx = 80,ty = 32;
	int sx = pRect->right - pRect->left,
		sy = pRect->bottom - pRect->top,
		size = 16,scale = 0;

	if(crsysGetExtentionLevel() < 3){
		size = 32;
	}

	int a,b,x,y,tri_count = ((sx / size) * (sy / size)) * 2;
	int RunTime = 1000;
	float ex = 1.0f,ey = 1.0f;
#ifdef EFECT_MODE_1
	float ay = 0.658f,//0.669
#else
	float ay = 0.5f,//0.5// 0.669f,
#endif
		dx = -(float)sx / (float)size / 2.0f,
		dy = -(float)sy / (float)size / 2.0f;//0.5778f;
	//---移動速度
	int vel_x = 600,vel_y = 600,vel_z = 1000;
	//---分割するテクスチャの大きさ
	int t_size_x = 512,t_size_y = 256;//256,64
	//---１ラインのテクスチャ数
	int x_line = sx / t_size_x , y_add = t_size_y / size;
	if(sx % t_size_x)
		x_line ++;
	//---テクスチャ１個に収まるパターン数
	int x_count = sx / size,
		y_count = sy / size;
	float u,v,
		eu = 1.0f / (float)x_count,
		ev = 1.0f / (float)y_count;

	D3DVECTOR vNormal( 0.0f, 0.0f, -1.0f );

	static D3DVECTOR MoveVector[1800];
	static EI_TRIANGLE_VERTEX Vertex[1800];
	static float Distanse[1800];

	D3DVECTOR *pMoveVector = &MoveVector[0];//new D3DVECTOR[tri_count + 32];
	EI_TRIANGLE_VERTEX *pVertex = &Vertex[0];//new EI_TRIANGLE_VERTEX[tri_count + 32];
	float *pDistanse = &Distanse[0];//new float[tri_count + 32];
#ifdef EFECT_MODE_1
	eiTextureCell *pTex = new eiTextureCell[tri_count];
#endif
	if(count != -1)
		RunTime = count;

	int time2;
#ifdef EFECT_MODE_1
	//---テクスチャを作る
	int time1;
//	eiSetDebugMode(0);
	et->Reset();
	RECT CopyRect = {0,0,640,480};
	CopyRect = *pRect;
	pTex[0].CreateFromSurface(
		t_size_x >> scale,t_size_y >> scale,16,
		(eiGetSurfacePointer() + 1),
		&CopyRect);
	time1 = et->Get();
	char s[80];
	sprintf(s,"tex_time:%d\n",time1);
	eiDebugWriteFile(s);
//	eiSetDebugMode(1);
	et->Reset();
#endif


	//---頂点データを作る
	for(y = 0,a = 0;y < sy / size;y ++){
		v = (float)(1.0f / ((float)sy / (float)size) * (float)y);
		for(x = 0;x < sx / size;x ++,a += 2){
			u = (float)(1.0f / ((float)sx / (float)size) * (float)x);
			D3DVECTOR p1(-0.5f ,-ay , 0.0f);
			D3DVECTOR p2( 0.5f ,-ay , 0.0f);
			D3DVECTOR p3(-0.5f , ay , 0.0f);
			D3DVECTOR p4( 0.5f , ay , 0.0f);

			pVertex[a].Vertex[0] = D3DVERTEX( p1, vNormal, u     , v     );//0.0f, 0.0f );
			pVertex[a].Vertex[1] = D3DVERTEX( p2, vNormal, u + eu, v     );//1.0f, 0.0f );
			pVertex[a].Vertex[2] = D3DVERTEX( p3, vNormal, u     , v + ev);//0.0f, 1.0f );

			pVertex[a].Vertex[3] = D3DVERTEX( p1, -vNormal, u     ,v      );//0.0f, 0.0f );
			pVertex[a].Vertex[4] = D3DVERTEX( p3, -vNormal, u     ,v + ev );//0.0f, 1.0f );
			pVertex[a].Vertex[5] = D3DVERTEX( p2, -vNormal, u + eu,v      );//1.0f, 0.0f );

			pDistanse[a] = pDistanse[a + 1] = (
				(x - ((float)sx / size / 2)) * (x - ((float)sx / size / 2))
				+ (y - ((float)sy / size / 2)) * (y - ((float)sy / size / 2))
				);

			//---回転
			pVertex[a].Rotate[1] = 0.0f;
			pVertex[a].RotateCount[1] = (float)eiRnd(100) / 1000.00f + 0.10f;
			if(eiRnd(100) < 50)
				pVertex[a].Rotate[1] = -pVertex[a].Rotate[1];

			//--------------------
			pVertex[a + 1].Vertex[0] = D3DVERTEX( p2, vNormal, u + eu , v     );//1.0f, 0.0f );
			pVertex[a + 1].Vertex[1] = D3DVERTEX( p3, vNormal, u      , v + ev);//0.0f, 1.0f );
			pVertex[a + 1].Vertex[2] = D3DVERTEX( p4, vNormal, u + eu , v + ev);//1.0f, 1.0f );

			pVertex[a + 1].Vertex[3] = D3DVERTEX( p2, -vNormal, u + eu , v     );//1.0f, 0.0f );
			pVertex[a + 1].Vertex[4] = D3DVERTEX( p4, -vNormal, u + eu , v + ev);//1.0f, 1.0f );
			pVertex[a + 1].Vertex[5] = D3DVERTEX( p3, -vNormal, u      , v + ev);//0.0f, 1.0f );

			//---回転
			pVertex[a + 1].Rotate[1] = 0.0f;
			pVertex[a + 1].RotateCount[1] = (float)eiRnd(100) / 1000.00f + 0.01f;
			if(eiRnd(100) < 50)
				pVertex[a + 1].Rotate[1] = -pVertex[a + 1].Rotate[1];

			for(b = 0;b < 2;b ++){
				pVertex[a + b].TexNumber = 0;
				//---位置ベクトル
				pVertex[a + b].MoveVector = D3DVECTOR(
					(float)x * ex + dx,
					(float)y * ey * ay * 2.0f  + dy ,0.0f);
				//---移動ベクトル
				pVertex[a + b].MoveVectorCount = D3DVECTOR(
//					(float)(eiRnd(vel_x) - (vel_x >> 1)) / 1000.00f,
//					(float)(eiRnd(vel_y) - (vel_y >> 1)) / 1000.00f,
					((float)x - ((float)sx / size / 2)) / 250.00f
					+ (float)(eiRnd(vel_x) - (vel_x >> 1)) / 10000.00f,
					((float)y - ((float)sy / size / 2)) / 250.00f
					+ (float)(eiRnd(vel_y) - (vel_y >> 1)) / 10000.00f,
					0.51f
//					(float)(-eiRnd(vel_z)) / 1000.00f + 0.01f
					);
			}
		}
	}

	time2 = et->Get();

//	sprintf(s,"%d  %d",time1,time2);
//	SetWindowText(ew.hwnd,s);

	eiD3DMatrix matCamera,matWorld,matTemp1,matTemp2,matTemp3,matTemp4;

	matWorld.IdentityMatrix();
/*	matCamera.CalcCamera(
		D3DVECTOR(-0.5f,-0.5f, 40.0f / (size / 16)),
		D3DVECTOR(-0.5f,-0.5f,-20.0f),
		D3DVECTOR(0.0f,1.0f,0.0f),3.14f);*/
	matCamera.CalcCamera(
		D3DVECTOR(-0.5f,3.5f, 47.75f / (size / 16)),
		D3DVECTOR(-0.5f,3.5f,-20.0f),
		D3DVECTOR(0.0f,1.0f,0.0f),3.14f);

	matWorld.IdentityMatrix();

	eid3d->SetAmbientLight(RGBA_MAKE(255,255,255,255));

	int debug_time = GetTickCount(),frame = 0;
	int Start,Now,Color;
	float AddWorld = 0.0f,Zoom = 47.75f / (size / 16),Rotate = 3.14f,
		Velo = (Zoom) / RunTime;
//	RunTime = 5000;
	for(Start = et->GetTime();et->GetTime() - Start < RunTime;){
		et->Reset();
		Now = et->GetTime() - Start;

//---デバッグ計測用--------------------
		if(GetTickCount() - debug_time >= 1000){
			debug_time= GetTickCount();
			sprintf(s,"%d",frame);
/*			SetWindowText(ew->hwnd,s);*/
			frame = 0;
		}
		frame ++;
//-------------------------------------
		Zoom -= (Velo * AddWorld);
		Rotate += (0.01f * AddWorld);
		while(Rotate > 6.283f){
			Rotate -= 6.283f;
		}

		matCamera.CalcCamera(
			D3DVECTOR(-0.5f,3.5f, Zoom / (size / 16)),
			D3DVECTOR(-0.5f,3.5f,-20.0f),
			D3DVECTOR(0.0f,1.0f,0.0f),Rotate);

		pViewport->ClearAll();
		eid3d->SetTransformView(&matCamera);
		//---描画開始
		if(eid3d->Begin(0)){
			eid3d->SetDrawMode(EID3D_DRAWMODE_FILL);
			eid3d->SetDrawMode(EID3D_DRAWMODE_CULLNONE);

			//---ライト設定
			if(Now < RunTime / 2)
				Color = 255;
			else
				Color = 255 - (int)((float)(Now - RunTime / 2) / (float)(RunTime / 2) * 255);
			eid3d->SetAmbientLight(RGBA_MAKE(Color,Color,Color,255));
			eid3d->SetMaterial(&Material);

			for(a = 0;a < tri_count;a ++){
				//---行列設定
				matWorld.IdentityMatrix();
				matWorld.Set(3,0 ,pVertex[a].MoveVector.dvX);
				matWorld.Set(3,1 ,pVertex[a].MoveVector.dvY);
				matWorld.Set(3,2 ,pVertex[a].MoveVector.dvZ);
				matWorld.Set(3,3 ,1);

				eid3d->SetTransformWorld(&matWorld);
				eid3d->SetTexture(&pTex[pVertex[a].TexNumber]);

				eid3d->DrawPrimitive( D3DPT_TRIANGLELIST,
					D3DFVF_VERTEX,pVertex[a].Vertex, 6,0);
			}
			eid3d->SetTexture(NULL);
			eid3d->SetMaterial(NULL);
			//---描画終了
			eid3d->End(0);
		}

		//---フリップ
		ew->Flip();
		if(!eiGetFullScreen()){
//			et->Wait(1);
		}
		//---進める時間
		AddWorld = (float)et->Get();
	}

	pViewport->ClearAll();
	Material.Release();
#ifdef EFECT_MODE_1
	pTex[0].ReleaseTexture();
	delete[] pTex;
#endif

	eiReleaseCriticalSection();
}
