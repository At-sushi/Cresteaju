//---テスト

CRBATTLE_API int crbatTest(void)
{
	D3DTLVERTEX ver[4];

	ver[0].sx = 50.0f;ver[0].sy = 50.0f;ver[0].sz = 0.0f;
	ver[0].tu = 0.0f;ver[0].tv = 0.0f;

	ver[1].sx = 110.0f;ver[1].sy = 50.0f;ver[1].sz = 0.0f;
	ver[1].tu = 1.0f;ver[1].tv = 0.0f;

	ver[2].sx = 50.0f;ver[2].sy = 410.0f;ver[2].sz = 0.0f;
	ver[2].tu = 0.0f;ver[2].tv = 1.0f;

	ver[3].sx = 110.0f;ver[3].sy = 410.0f;ver[3].sz = 0.0f;
	ver[3].tu = 1.0f;ver[3].tv = 1.0f;
	for(int a = 0;a < 4;a ++){
		ver[a].dcColor = RGBA_MAKE(255,255,255 / (a + 1),255);
		ver[a].dvRHW = RGBA_MAKE(255,0,0,0);
	}

//	int x,y;
	float sx = 6,sy = -5,sz = 3;
	eiD3DMatrix matWorld,matProjection;
	float AddWorld = 0.0f,Angle = ANGLE(90),rotate;
	eistr s[100];


	int debug_time = GetTickCount(),frame;

	ei->Get();

	pViewport->SetRect(32,32,256 + 32,256 + 32);
	pViewport->SetRect(32,32,640 - 64,256);
//	pViewport->SetRect(0,0,640,480);
	pViewport->Set();
	eid3d->SetAmbientLight(RGBA_MAKE(255,255,255,255));

	frame = 0;

	crbaseClearScreen();
	crbatShowStatus();
//	crbatSetViewMode(BATTLE_VIEWMODE_DOUBLE);
//	crbatSetViewMode(BATTLE_VIEWMODE_HALF);
	crbatSetCamera(
		1,
		-5.0f,4.0f,-5.0f,
		15.0f,0.0f,15.0f,
		0.0f);

	while(!ei->Input[0].Button[0] && !ei->Escape){
		ei->Get();

		if(ei->Input[0].Button[1]){
			sz += (float)(1.0 * AddWorld);
		}
		if(ei->Input[0].Button[2]){
			sz -= (float)(1.0 * AddWorld);
		}

		if(ei->Input[0].Left){
			Angle += (float)(0.5f * AddWorld);
		} else if(ei->Input[0].Right){
			Angle -= (float)(0.5f * AddWorld);
		}
		if(Angle > PI * 2.0f)
			Angle = 0.0f;
		if(Angle < 0.0f)
			Angle = PI * 2.0f;
		rotate = 0.0f;

		if(ei->Input[0].Up){
			sx += (float)(cos(Angle) * 1.0f * AddWorld);
			sy += (float)(sin(Angle) * 1.0f * AddWorld);
		} else if(ei->Input[0].Down){
			sx -= (float)(cos(Angle) * 1.0f * AddWorld);
			sy -= (float)(sin(Angle) * 1.0f * AddWorld);
		}

		crbatSetCamera(
			0,
			sx,sy,sz,
			(float)(sx + (cos(Angle) * 10.0f)),
			(float)(sy + (sin(Angle) * 10.0f)),
			(float)0.0f,
			rotate);
		crbatSetCamera(
			1,
			sx,sy,sz,
			(float)(sx + (cos(Angle) * 10.0f)),
			(float)(sy + (sin(Angle) * 10.0f)),
			(float)0.0f,
			rotate);

		et->Reset();
//---デバッグ計測用--------------------
		if(GetTickCount() - debug_time >= 1000){
			debug_time= GetTickCount();
			sprintf(s,"%d",frame);
			SetWindowText(ew->hwnd,s);
			frame = 0;
		}
		frame ++;
//		sprintf(s,"%f",BattleView[0].Angle);
//		SetWindowText(ew->hwnd,s);
//-------------------------------------
		crbatClearDrawingList();
		crbatAddDrawingListAll();
/*		crbatAddDrawingList(&pBtChara[0]);
		crbatAddDrawingList(&pBtChara[1]);
		crbatAddDrawingList(&pBtChara[2]);
		crbatAddDrawingList(&pBtChara[5]);
		crbatAddDrawingList(&pBtChara[6]);*/
		crbatDrawScene();

//		{
//			RECT rect = {32,32,640 - 32,256 + 32};
//			ew->lpCell[1]->SetClipingRect(&rect);
//			crbatPut3DCell(&BattleCharaCell[0],128.0f,0.0f,128.0f,0.50f);
//			crbatPut3DCell(&BattleCharaCell[20],68.0f,0.0f,198.0f,0.50f);
//			crbatPut3DCell(&BattleCharaCell[40],228.0f,0.0f,32.0f,0.50f);
//			SetRect(&rect,0,0,640,480);
//			ew->lpCell[1]->SetClipingRect(&rect);
//		}
		//---フリップ
//		ew->Flip();
		ew->Refresh();
		if(!eiGetFullScreen()){
//			et->Wait(1);
		}

		//---進める時間
		AddWorld = (float)et->Get() / 100.0f;

	}

	return 1;
}

