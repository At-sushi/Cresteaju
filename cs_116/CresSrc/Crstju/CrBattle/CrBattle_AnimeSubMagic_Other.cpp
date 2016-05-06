
//---ディフュージョン
CRBATANIME_API void crbatDoAnime_MagicDiffusion3(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo)
{
	eiTime let;
	int AddWorld = 0,flag,begin_anime = 0;
	int a,b,c,anime3d = 0;
	float dis = 0;
	CrBattleCharacter *pDstChara[16];
	//= pDamageInfo->pList[0];

	eiD3DMaterial material[4];
	float addw = 0;
	int red = 255,green = 255,blue = 255;
	int mode = 3;

	int dst_count;

	if(crsysQuick()){
		//---クイック
		return;
	}

	for(a = 0,dst_count = 0;pDamageInfo->pList[a] != NULL;a ++){
		pDstChara[a] = pDamageInfo->pList[a];
		dst_count ++;
	}
	pDstChara[a] = NULL;

	for(a = 0;a < 4;a ++){
		material[a].Create();
		material[a].SetDeffuseColor(red ,green ,blue,192);
		material[a].SetEmissiveColor(red,green ,blue ,192);
		material[a].Set();
	}
	material[3].SetDeffuseColor(255 ,255 ,0,192);

	eiD3DParticle_SetG(0.00f);
	int count = 2 + dst_count * 10;
	for(a = 0;a < 2;a ++){
		if(a == 0){
			BatPart[a].CreateTriangle(
				0.0f,0.01f,0.0f,
				12.0f,0.01f,0.0f,
				0.0f,0.01f,12.0f);
		} else {
			BatPart[a].CreateTriangle(
				12.0f,0.01f,0.0f,
				0.0f,0.01f,12.0f,
				12.0f,0.01f,12.0f);
		}

		BatPart[a].SetWeight(0);
		BatPart[a].SetWorldPos(
			0,0,0
		);
		BatPart[a].SetRotationMode(1);
		BatPart[a].SetMoveSpeed(0.0f);
		BatPart[a].SetMoveRotation(0,0);
		BatPart[a].SetMoveVectorXYZ(
			0.0f,1.0f,0.0f
		);
	}

	//---球
	for(a = 2;a < 2 + dst_count;a ++){
		BatPart[a].CreateSphere(1.0f,12,12,0.0f,3.141592f);

		BatPart[a].SetWeight(0);
		BatPart[a].SetWorldPos(
			(float)(pDstChara[a - 2]->GetFieldX()),
			0.0f,
			(float)(pDstChara[a - 2]->GetFieldY())
		);
		BatPart[a].SetRotationMode(1);
		BatPart[a].SetMoveSpeed(0.0f);
		BatPart[a].SetMoveRotation(0,0);
		BatPart[a].SetMoveVectorXYZ(
			0.0f,1.0f,0.0f
		);
	}
	//---ランダムトライアングル
	int rtstart = 2 + dst_count;
	for(a = rtstart;a < rtstart + dst_count;a ++){
		BatPart[a].CreateSphere(1.0f,30,30,0,3.1415f);

		BatPart[a].SetWeight(1);
		BatPart[a].SetWorldPos(
			(float)(pDstChara[a - rtstart]->GetFieldX()),
			0.0f,
			(float)(pDstChara[a - rtstart]->GetFieldY())
		);
		BatPart[a].SetRotationMode(1);
		BatPart[a].SetMoveSpeed(0.0f);
		BatPart[a].SetMoveRotation(0,0);
		BatPart[a].SetMoveVectorXYZ(
			0.0f,1.0f,0.0f
		);

		for(c = 0;c < BatPart[a].Info.VertexCount / 2;c += 3){	
			BatPart[a].Info.pVertex[c].nx +=
				((float)(eiRnd(1000) - 500) / 2500.0f);
			BatPart[a].Info.pVertex[c].ny +=
				((float)(eiRnd(1000) - 500) / 2500.0f);
			BatPart[a].Info.pVertex[c].nz +=
				((float)(eiRnd(1000) - 500) / 2500.0f);
		}
	}

	//---閃
	int linestart = rtstart + dst_count;
	for(c = 0;c < dst_count;c ++){
		float x = (float)pDstChara[c]->GetFieldX();
		float y = (float)pDstChara[c]->GetFieldY();
		float height = (float)pDstChara[c]->GetCharaHeight() / 128.0f;
		float angle[2] = {ANGLE(eiRnd(360)) , ANGLE(eiRnd(360))};
		float dr = 12.0f,dangle = 0.05f;
		for(b = 0;b < 8;b ++){
			BatPart[linestart + c * 8 + b].CreateTriangle(
				0,0,0,
				x + (float)cos(angle[0]) * dr,
				0 + (float)cos(angle[1]) * dr,
				y + (float)sin(angle[0]) * dr,

				x + (float)cos(angle[0] + dangle) * dr,
				0 + (float)cos(angle[1]) * dr,
				y + (float)sin(angle[0] + dangle) * dr);

			BatPart[linestart + c * 8 + b].SetWeight(0);
			BatPart[linestart + c * 8 + b].SetWorldPos(
				(float)x,
				height,
				(float)y
			);
			BatPart[linestart + c * 8 + b].SetRotationMode(1);
			BatPart[linestart + c * 8 + b].SetMoveSpeed(0.0f);
			BatPart[linestart + c * 8 + b].SetMoveRotation(0,0);
			BatPart[linestart + c * 8 + b].SetMoveVectorXYZ(
				0.0f,1.0f,0.0f
			);
		}
	}

	let.Reset();
	flag = 1;
	addw = 0;

	int anime_flag = 0,t;
	float f = 0.005f,g,speed = 0.03f;
	while(flag){
		et->Reset();
		t = let.Get();

		if(anime_flag == 0){
			material[0].SetDeffuseColor(
				255,255,255, 160 * let.Get() / 1000);
		} else if(anime_flag == 1){
			material[0].SetDeffuseColor(
				255,255,255,160);
			material[1].SetDeffuseColor(
				255,224,224, let.Get() < 750 ? (96 * let.Get() / 750) : 128);

			f = 0.2f;
			g = 0.2f;
			g = 0.07f;
			for(c = 2;c < 2 + dst_count;c ++){
				for(a = 0;a < BatPart[c].Info.VertexCount;a += 3){	
					for(b = 0;b < 3;b ++){
						BatPart[c].Info.pVertex[a + b].x +=
							(BatPart[c].Info.pVertex[a + b].nx * addw * g * 0.60f);//0.05f
						BatPart[c].Info.pVertex[a + b].y +=
							(BatPart[c].Info.pVertex[a + b].ny * addw * g);
						BatPart[c].Info.pVertex[a + b].z +=
							(BatPart[c].Info.pVertex[a + b].nz * addw * g * 0.60f);
					}
				}
			}

			for(c = linestart;c < linestart + dst_count * 8;c ++){
				if(eiRnd(100) <= 25){
					float r = 12.0f,hr = (float)12,
						angle = ANGLE(eiRnd(360)),h_angle = ANGLE(eiRnd(360));
					BatPart[c].Info.Vertex[1].x = (float)cos(angle) * r;
					BatPart[c].Info.Vertex[1].z = (float)sin(angle) * r;
					BatPart[c].Info.Vertex[1].y = (float)sin(h_angle) * hr;
					BatPart[c].Info.Vertex[2].x = (float)cos(angle + ANGLE(1)) * r;
					BatPart[c].Info.Vertex[2].z = (float)sin(angle + ANGLE(1)) * r;
					BatPart[c].Info.Vertex[2].y = (float)sin(h_angle) * hr;
				}
			}
		} else if(anime_flag == 2){
			material[2].SetDeffuseColor(
				255,255,255,160 - (160 * let.Get() / 1800));
			material[0].SetDeffuseColor(
				255,255,255,255 - 255 * let.Get() / 1800);

			f = 0.20f;
			g = 0.30f;
			f = 0.02f - (t * 0.00006f);
//			g = f = 0;
			for(c = rtstart;c < rtstart + dst_count;c ++){
				for(a = 0;a < BatPart[c].Info.VertexCount;a += 3){	
					for(b = 0;b < 3;b ++){
						BatPart[c].Info.pVertex[a + b].x +=
							(BatPart[c].Info.pVertex[a].nx * addw * g);
						BatPart[c].Info.pVertex[a + b].y +=
							(BatPart[c].Info.pVertex[a].ny * addw * f);
						BatPart[c].Info.pVertex[a + b].z +=
							(BatPart[c].Info.pVertex[a].nz * addw * g);
					}
				}
			}
		}

		if(anime_flag == 0 && let.Get() > 1000){
			anime_flag = 1;
			let.Reset();
		} else if(anime_flag == 1 && let.Get() > 750){
			anime_flag = 2;
			let.Reset();
		} else if(anime_flag == 2 && let.Get() > 1800){
			flag = 0;
			let.Reset();

		}

crdataEnableRec(0);
		crbatDrawScene();

		if(eid3d->Begin()){
			eid3d->BeginAlphaBlend();
			crbatDraw_SetViewport(0);
			crbatDraw_SetMatrix(0);
			eid3d->SetTexture(NULL);

			crbatSetAddAlpha();
			eid3d->SetDrawMode(EID3D_DRAWMODE_CULLNONE);
//			eid3d->lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_ONE);
			for(c = 0;c < 2;c ++){
				eid3d->SetMaterial(&material[0]);
				BatPart[c].MoveFrame((float)addw);
				BatPart[c].Draw();
			}
			if(anime_flag == 1){
				eid3d->SetMaterial(&material[1]);
				for(c = 2;c < 2 + dst_count;c ++){
					BatPart[c].MoveFrame((float)addw);
					BatPart[c].Draw();
				}
				eid3d->SetMaterial(&material[3]);
				for(c = linestart;c < linestart + dst_count * 8;c ++){
					BatPart[c].MoveFrame((float)addw);
					BatPart[c].Draw();
				}
			}
			if(anime_flag == 2){
				eid3d->SetMaterial(&material[2]);
				for(c = rtstart;c < rtstart + dst_count;c ++){
					BatPart[c].MoveFrame((float)addw);
					BatPart[c].Draw(BatPart[c].Info.VertexCount / 2);
				}
			}

			eid3d->SetMaterial(NULL);
			eid3d->EndAlphaBlend();
			eid3d->End();
		}
crdataEnableRec(1);
		if(eiGetEndThread()){
			break;
		}
		crbatDrawRefresh();

		addw = (float)et->Get() / 10.0f;
	}
	material[0].Release();
	material[1].Release();
	material[2].Release();
	material[3].Release();

	for(a = 0;a < count;a ++){
		BatPart[a].Release();
	}
}

//---ディフュージョン
CRBATANIME_API void crbatDoAnime_MagicDiffusion4(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo)
{
	eiTime let;
	int AddWorld = 0,flag,begin_anime = 0;
	int a,b,c,anime3d = 0;
	float dis = 0;
	CrBattleCharacter *pDstChara[16];
	//= pDamageInfo->pList[0];

	eiD3DMaterial material[4];
	float addw = 0;
	int red = 255,green = 255,blue = 255;
	int mode = 3;

	int dst_count;
	for(a = 0,dst_count = 0;pDamageInfo->pList[a] != NULL;a ++){
		pDstChara[a] = pDamageInfo->pList[a];
		dst_count ++;
	}
	pDstChara[a] = NULL;
	dst_count = 1;

	for(a = 0;a < 4;a ++){
		material[a].Create();
		material[a].SetDeffuseColor(red ,green ,blue,192);
		material[a].SetEmissiveColor(red,green ,blue ,192);
		material[a].Set();
	}
	material[3].SetDeffuseColor(255 ,255 ,0,192);

	//---球
	for(a = 0;a < 1;a ++){
		BatPart[a].CreateSphere(0.5f,32,32,0.0f,3.141592f);

		BatPart[a].SetWeight(0);
		BatPart[a].SetWorldPos(
			(float)(pChara->GetFieldX()),
			1.0f,
			(float)(pChara->GetFieldY())
		);
		BatPart[a].SetRotationMode(1);
		BatPart[a].SetMoveSpeed(0.0f);
		BatPart[a].SetMoveRotation(0.25f,0.20f,0.01f);
		BatPart[a].SetMoveVectorXYZ(
			0.0f,1.0f,0.0f
		);
	}

	//---閃
	int linestart = 1;
	for(c = 0;c < dst_count;c ++){
		float x = (float)pChara->GetFieldX();
		float y = (float)pChara->GetFieldY();
		float height = 1.0f;//(float)pChara->GetCharaHeight() / 128.0f + 0.5;
		float angle[2] = {ANGLE(eiRnd(360)) , ANGLE(eiRnd(360))};
		float dr = 12.0f,dangle = 0.05f;
		for(b = 0;b < 8;b ++){
			BatPart[linestart + c * 8 + b].CreateTriangle(
				0,0,0,
				x + (float)cos(angle[0]) * dr,
				0 + (float)cos(angle[1]) * dr,
				y + (float)sin(angle[0]) * dr,

				x + (float)cos(angle[0] + dangle) * dr,
				0 + (float)cos(angle[1]) * dr,
				y + (float)sin(angle[0] + dangle) * dr);

			BatPart[linestart + c * 8 + b].SetWeight(0);
			BatPart[linestart + c * 8 + b].SetWorldPos(
				(float)x,
				height,
				(float)y
			);
			BatPart[linestart + c * 8 + b].SetRotationMode(1);
			BatPart[linestart + c * 8 + b].SetMoveSpeed(0.0f);
			BatPart[linestart + c * 8 + b].SetMoveRotation(0,0);
			BatPart[linestart + c * 8 + b].SetMoveVectorXYZ(
				0.0f,1.0f,0.0f
			);
		}
	}

	int bomb_start = linestart + 8 * dst_count,bomb_count = 1;
	for(a = bomb_start;a < bomb_start + bomb_count;a ++){
		BatPart[a].CreateSphere(2.5,48,48);
		BatPart[a].SetWorldPos(
			(float)pChara->GetFieldX(),
			1.0f,
			(float)pChara->GetFieldY());
		BatPart[a].SetRotationMode(1);
		BatPart[a].SetMoveRotation(0,0);
		BatPart[a].SetMoveSpeed(0);
		BatPart[a].SetMoveVectorXYZ(0,1,0);
		BatPart[a].SetWeight(1);
/*
		c = a;
		for(b = 0;b < BatPart[c].Info.VertexCount / 2;b += 3){	
			BatPart[c].Info.pVertex[b].nx +=
				((float)(eiRnd(1000) - 500) / 2500.0f);
			BatPart[c].Info.pVertex[b].ny +=
				((float)(eiRnd(1000) - 500) / 2500.0f);
			BatPart[c].Info.pVertex[b].nz +=
				((float)(eiRnd(1000) - 500) / 2500.0f);
		}*/

		b = BatPart[c].Info.VertexCount / 2;

		int d;
		for(;b < BatPart[c].Info.VertexCount;b += 3){	
/*			BatPart[c].Info.pVertex[b].nx +=
				((float)(eiRnd(1000) - 500) / 2500.0f);
			BatPart[c].Info.pVertex[b].nx *= 0.5f;

			BatPart[c].Info.pVertex[b].ny +=
				((float)(eiRnd(1000) - 500) / 2500.0f);
			BatPart[c].Info.pVertex[b].ny *= 0.5f;

			BatPart[c].Info.pVertex[b].nz +=
				((float)(eiRnd(1000) - 500) / 2500.0f);
			BatPart[c].Info.pVertex[b].nz *= 0.5f;*/

			for(d = 0;d < 3;d ++){
				BatPart[a].Info.pVertex[b + d].x *= 0.9f;
				BatPart[a].Info.pVertex[b + d].y *= 0.9f;
				BatPart[a].Info.pVertex[b + d].z *= 0.9f;
			}
		}
	}

	//--------------------------------------------
	EIMEMORY hmem = eiAllocMemory(sizeof(float) * BatPart[bomb_start].Info.VertexCount + 10000);
	float *pMoveData = (float *)eiLockMemory(hmem);
	c = bomb_start;
	for(a = 0;a < BatPart[c].Info.VertexCount / 2;a += 3){
		pMoveData[a + 0] = BatPart[c].Info.pVertex[a].nx + 
				((float)(eiRnd(1000) - 500) / 2500.0f);
		pMoveData[a + 1] = BatPart[c].Info.pVertex[a].ny + 
				((float)(eiRnd(1000) - 500) / 2500.0f);
		pMoveData[a + 2] = BatPart[c].Info.pVertex[a].nz + 
				((float)(eiRnd(1000) - 500) / 2500.0f);
	}

	for(;a < BatPart[c].Info.VertexCount;a += 3){
		pMoveData[a + 0] = BatPart[c].Info.pVertex[a].nx +
				((float)(eiRnd(1000) - 500) / 2500.0f);
		pMoveData[a + 0] *= 0.5f;

		pMoveData[a + 1] = BatPart[c].Info.pVertex[a].ny +
				((float)(eiRnd(1000) - 500) / 2500.0f);
		pMoveData[a + 1] *= 0.5f;

		pMoveData[a + 2] = BatPart[c].Info.pVertex[a].nz +
			((float)(eiRnd(1000) - 500) / 2500.0f);
		pMoveData[a + 2] *= 0.5f;
	}
	//--------------------------------------------

	int sred = 255,sgreen = 255,sblue = 255;
	int slash_count = 20,slash_num = 2;
	int slash_start = bomb_start + bomb_count;
	eiD3DMaterial slash_mat[60];
	float r = 20.0f,angle = 0,delta = ((float)ANGLE(360) / (float)slash_count);

	for(b = 0;b < slash_num;b ++){
		for(a = 0;a < slash_count;a ++ ){
			slash_mat[a + b * slash_count].Create();
			slash_mat[a + b * slash_count].SetDeffuseColor(
				sred,sgreen,sblue,
				(255 - 128 * b) * a / slash_count);
			slash_mat[a + b * slash_count].SetEmissiveColor(
				sred,sgreen,sblue,
				(255 - 128 * b) * a / slash_count);
		}
	}
	for(b = 0;b < slash_num;b ++){
		for(a = slash_start,angle = 0;a < slash_start + slash_count;a ++ , angle += delta){
			BatPart[a + b * slash_count].CreateTriangle(
				0,0,0,
				(float)cos(angle) * r,			0,(float)sin(angle) * r,
				(float)cos(angle + delta) * r,	0,(float)sin(angle + delta) * r);
			BatPart[a+ b * slash_count].SetWorldPos(
				(float)pChara->GetFieldX(),
				1.0f,
				(float)pChara->GetFieldY());
			BatPart[a + b * slash_count].SetRotationMode(1);
			if(b == 0)
				BatPart[a + b * slash_count].SetMoveRotation(0,0.12f);
			else
				BatPart[a + b * slash_count].SetMoveRotation(0,-0.16f);
			BatPart[a + b * slash_count].SetWeight(0);
			BatPart[a + b * slash_count].SetMoveSpeed(0);
			BatPart[a + b * slash_count].SetMoveVectorXYZ(0,1,0);
		}
	}

	int count = slash_start + slash_num * slash_count;

	eiD3DParticle_SetG(0.02f);

	let.Reset();
	flag = 1;
	addw = 0;

	int anime_flag = 0,t,sound_flag = 0;
	float f = 0.005f,g = 0,speed = 0.03f,temp[6];
	int slash_time[8] = {0,0,0,0 ,0,0,0,0}
		,prev_slash[8] =  {0,0,0,0 ,0,0,0,0};

	crsoundPlay(CRSOUND_DIFFUSION1,EISOUND_PLAYLOOP);
	crsoundPlay(CRSOUND_DIFFUSION2);
	while(flag){
		et->Reset();
		t = let.Get();

		if(anime_flag <= 2){
			for(c = linestart;c < linestart + 1 * 8;c ++){
				if(eiRnd(100) <= 25){
					float r = 12.0f,hr = (float)12,
						angle = ANGLE(eiRnd(360)),h_angle = ANGLE(eiRnd(360));
					BatPart[c].Info.Vertex[1].x = (float)cos(angle) * r;
					BatPart[c].Info.Vertex[1].z = (float)sin(angle) * r;
					BatPart[c].Info.Vertex[1].y = (float)sin(h_angle) * hr;
					BatPart[c].Info.Vertex[2].x = (float)cos(angle + ANGLE(1)) * r;
					BatPart[c].Info.Vertex[2].z = (float)sin(angle + ANGLE(1)) * r;
					BatPart[c].Info.Vertex[2].y = (float)sin(h_angle) * hr;
				}
			}
		}

		material[0].SetDeffuseColor(
			255,255,255, 128);
		material[0].SetEmissiveColor(
			255,255,255, 128);

		material[3].SetDeffuseColor(
			0,0,255, 160);
		if(anime_flag == 0){
			material[0].SetDeffuseColor(
				255 * t / 1000,255 * t / 1800 ,255, 128 * t / 2000);
			material[0].SetEmissiveColor(
				255 * t / 1000,255 * t / 1800 ,255, 128 * t / 2000);

			material[3].SetDeffuseColor(
				0,0,255, 160 * t / 2000);

		} else if(anime_flag == 1){
			for(b = 0;b < slash_num;b ++){
				if(!slash_time[b]){
					if(++ prev_slash[b] >= 2)
						prev_slash[b] = 0;

					slash_time[b] = t + 1;
					if(prev_slash[b] == 0){
						if(b == 0)
							angle = ANGLE((float)(eiRnd(100) - 50) / 100.0f);
						else
							angle = ANGLE(eiRnd(360));
					}
					for(a = 0;a < slash_count;a ++){
						BatPart[a + slash_start + b * slash_count].SetXAngle(angle);
					}
					angle = ANGLE(eiRnd(360));

					for(a = 0;a < slash_count;a ++){
						BatPart[a + slash_start + b * slash_count].SetYAngle(angle);
					}
				}
				if(slash_time[b]){
					if(t - slash_time[b] > 200 - b * 50){
						slash_time[b] = 0;
					}
				}
			}
		}

		if(anime_flag == 2){
			material[0].SetDeffuseColor(
				255,255,255,
//				t < 1500 ? 255 - (255 * t / 1500) : 0,
//				t < 2000 ? 255 - (255 * t / 2000) : 0,
				128 - 128 * t / 2000);
			material[0].SetEmissiveColor(
				255,
				t < 1600 ? 255 - (255 * t / 1600) : 0,
				t < 1200 ? 255 - (255 * t / 1200) : 0,
				128 - 128 * t / 2000);

			material[2].SetDeffuseColor(
				255,255 ,255,160 - (160 * t / 2000));
			material[3].SetDeffuseColor(
				0,0,255, 160 - (160 * t / 2000));

//			f -= (t * 0.0000006f);
			f = -(t * 0.00048f * 1.2f);
			g = 0.37f * 1.2f;

			temp[0] = addw * g;
			temp[1] = addw * f;
			for(c = bomb_start;c < bomb_start + bomb_count;c ++){
				for(a = 0;a < BatPart[c].Info.VertexCount;a += 3){	
/*					temp[3] = (BatPart[c].Info.pVertex[a].nx * temp[0]);
					temp[4] = (BatPart[c].Info.pVertex[a].ny * temp[0]);
					temp[5] = (BatPart[c].Info.pVertex[a].nz * temp[0]);
*/
					temp[3] = (pMoveData[a + 0] * temp[0]);
					temp[4] = (pMoveData[a + 1] * temp[0]);
					temp[5] = (pMoveData[a + 2] * temp[0]);

					for(b = 0;b < 3;b ++){
						BatPart[c].Info.pVertex[a + b].x +=
							(temp[3]);// * temp[0]);
						BatPart[c].Info.pVertex[a + b].y +=
							(temp[4]);//* temp[1]);
						BatPart[c].Info.pVertex[a + b].z +=
							(temp[5]);// * temp[0]);
					}
				}
			}
		}

		if(anime_flag == 1 && t > 800 && sound_flag == 0){
			crsoundPlay(CRSOUND_DIFFUSION4);
//			crsoundStop(CRSOUND_DIFFUSION3);
			sound_flag = 1;
		}

		if(anime_flag == 0 && t > 2000){
			anime_flag = 1;
			let.Reset();
			crsoundPlay(CRSOUND_DIFFUSION3);
			crsoundPlay(43);
		} else if(anime_flag == 1 && t > 1000){
			anime_flag = 2;
			let.Reset();
			crsoundStop(CRSOUND_DIFFUSION1,0);
		} else if(anime_flag == 2 && t > 2000){
			flag = 0;
			let.Reset();
		}

crdataEnableRec(0);
		crbatDrawScene();

		if(eid3d->Begin()){
			eid3d->BeginAlphaBlend();
			crbatDraw_SetViewport(0);
			crbatDraw_SetMatrix(0);
			eid3d->SetTexture(NULL);

			crbatSetAddAlpha();
			eid3d->SetDrawMode(EID3D_DRAWMODE_CULLNONE);

			if(anime_flag <= 2){
				for(c = 0;c < 1;c ++){
					eid3d->SetMaterial(&material[0]);
					BatPart[c].MoveFrame((float)addw);
					BatPart[c].Draw(BatPart[c].Info.VertexCount / 2);
				}
			}

			if(anime_flag == 0 || anime_flag == 2){
				eid3d->SetMaterial(&material[3]);
				for(c = linestart;c < linestart + dst_count * 8;c ++){
					BatPart[c].MoveFrame((float)addw);
					BatPart[c].Draw();
				}
			}
			if(anime_flag == 1){
				for(b = 0;b < slash_num;b ++){
					for(a = 0;a < slash_count;a ++){
						eid3d->SetMaterial(&slash_mat[a + b * slash_count]);
						BatPart[a + slash_start + slash_count * b].MoveFrame((float)addw);
						BatPart[a + slash_start + slash_count * b].Draw();
					}
				}
			}
			if(anime_flag == 2){
				eid3d->SetMaterial(&material[2]);
				for(c = bomb_start;c < bomb_start + bomb_count;c ++){
					BatPart[c].MoveFrame((float)addw);
					BatPart[c].Draw(BatPart[c].Info.VertexCount);
				}
			}

			eid3d->SetMaterial(NULL);
			eid3d->EndAlphaBlend();
			eid3d->End();
		}
crdataEnableRec(1);
		if(eiGetEndThread()){
			break;
		}
		crbatDrawRefresh();

		addw = (float)et->Get() / 10.0f;
	}

	eiUnlockMemory(hmem);
	eiFreeMemory(hmem);

	material[0].Release();
	material[1].Release();
	material[2].Release();
	material[3].Release();

	for(b = 0;b < slash_num;b ++){
		for(a = 0;a < slash_count;a ++ ){
			slash_mat[a + b * slash_count].Release();
		}
	}

	for(a = 0;a < count;a ++){
		BatPart[a].Release();
	}
}

//---エクスティンクション
CRBATANIME_API void crbatDoAnime_MagicExtinction1(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo)
{
	eiTime let;
	int AddWorld = 0,flag,begin_anime = 0;
	int a,b,anime3d = 0;
	float dis = 0;
	int red = 192,green = 192,blue = 224;
	int lstart = 4,lcount = 9;
	CrBattleCharacter *pDstChara = pDamageInfo->pList[0];

	eiD3DMaterial material[12];
	float addw = 0;

	red = blue = green = 0;

	for(a = 0;a < lstart;a ++){
		material[a].Create();
		material[a].SetDeffuseColor(red,green,blue,127);
		material[a].SetEmissiveColor(red / 4,green / 4,blue / 4,255);
		material[a].d3dMaterial.dcvSpecular.r = D3DVAL(1.0);
		material[a].d3dMaterial.dcvSpecular.g = D3DVAL(1.0);
		material[a].d3dMaterial.dcvSpecular.b = D3DVAL(1.0);
		material[a].d3dMaterial.dcvSpecular.a = D3DVAL(1.0);
		material[a].d3dMaterial.dcvAmbient.r  = D3DVAL(0.0); 
		material[a].d3dMaterial.dcvAmbient.g  = D3DVAL(0.0); 
		material[a].d3dMaterial.dcvAmbient.b  = D3DVAL(0.0); 
		material[a].d3dMaterial.dcvAmbient.a  = D3DVAL(0.0);
		material[a].Set();
	}

	//---
	material[lstart].Create();
	material[lstart].SetDeffuseColor(255,255,255,192);
	material[lstart].SetEmissiveColor(255 / 4,255 / 4,255 / 4,192);
	material[lstart].Set();

	BatPart[0].CreateSphere(
		2.0f,16,16);
	BatPart[1].CreateSphere(
		4.0f,16,16);
	BatPart[2].CreateSphere(
		8.0f,16,16);
	BatPart[3].CreateSphere(
		16.0f,16,16);
	for(a = lstart;a < lcount;a ++){
		BatPart[a].CreateTriangle(0,0,0,0,0,0,0,0,0);
	}

	for(a = 0;a < lcount;a ++){
		BatPart[a].SetWeight(0);
		BatPart[a].SetWorldPos(
			(float)(pDstChara->GetFieldX() + 0.00f),
			(float)pDstChara->GetCharaHeight() / 128.0f,
			(float)(pDstChara->GetFieldY() + 0.00f)
		);
		BatPart[a].SetRotationMode(1);
		BatPart[a].SetMoveSpeed(0.0f);
		BatPart[a].SetMoveRotation(0,0.05f);
	}
	BatPart[0].SetMoveVectorXYZ(
		0.0f,1.0f,0.0f
	);
	BatPart[1].SetMoveVectorXYZ(
		0.0f,1.0f,0.0f
	);

	for(a = lstart;a < lcount;a ++){
		BatPart[a].SetMoveVectorXYZ(0,3.0f,0);
	}

	eiD3DParticle_SetG(0.00f);

	let.Reset();
	flag = 1;
	addw = 0;


	int c,anime_flag = 0,t,run_time = 4000;
	float f = 0.005f,g,speed = 0.03f,now_rate;

	crsoundPlay(CRSOUND_EXT3);
	crsoundPlay(CRSOUND_EXT1);
	while(flag){
		et->Reset();
		t = let.Get();

		now_rate = (float)(run_time - t) / run_time;

		if(anime_flag == 0){
			for(a = 0;a < lstart;a ++){
				material[a].SetDeffuseColor(red,green,blue,
					(int)((float)t * (255.0f / (float)((a + 1) * 2)) / (float)(run_time - 1)));
			}
			material[lstart - 1].SetDeffuseColor(red,green,blue,
				(int)((float)t * (160.0f) / (float)run_time));

			f = 0.02f;
			g = 0.02f;

			now_rate = (float)(run_time - 1000 - t) / (run_time - 1000);
			for(c = 0;c < lstart;c ++){
			for(a = 0;a < BatPart[c].Info.VertexCount;a += 3){	
				for(b = 0;b < 3;b ++){
					BatPart[c].Info.pVertex[a + b].x =
						(now_rate * BatPart[c].Info.pStartVertex[a + b].x);
					BatPart[c].Info.pVertex[a + b].y =
						(now_rate * BatPart[c].Info.pStartVertex[a + b].y);
					BatPart[c].Info.pVertex[a + b].z =
						(now_rate * BatPart[c].Info.pStartVertex[a + b].z);
				}
			}
			}

			now_rate = (float)(run_time - t) / run_time;
			c = lstart - 1;
			for(a = 0;a < BatPart[c].Info.VertexCount;a += 3){	
				for(b = 0;b < 3;b ++){
					BatPart[c].Info.pVertex[a + b].x =
						(now_rate * BatPart[c].Info.pStartVertex[a + b].x);
					BatPart[c].Info.pVertex[a + b].y =
						(now_rate * BatPart[c].Info.pStartVertex[a + b].y);
					BatPart[c].Info.pVertex[a + b].z =
						(now_rate * BatPart[c].Info.pStartVertex[a + b].z);
				}
			}

			for(a = lstart;a < lcount;a ++){
				if(eiRnd(100) <= 25){
					float r = 12.0f,hr = (float)eiRnd(10) + 5,
						angle = ANGLE(eiRnd(360)),h_angle = ANGLE(eiRnd(360));
					BatPart[a].Info.Vertex[1].x = (float)cos(angle) * r;
					BatPart[a].Info.Vertex[1].z = (float)sin(angle) * r;
					BatPart[a].Info.Vertex[1].y = (float)sin(h_angle) * hr;
					BatPart[a].Info.Vertex[2].x = (float)cos(angle + ANGLE(1)) * r;
					BatPart[a].Info.Vertex[2].z = (float)sin(angle + ANGLE(1)) * r;
					BatPart[a].Info.Vertex[2].y = (float)sin(h_angle) * hr;
				}
			}
		}

		if(anime3d == 0 && anime_flag == 0 && let.Get() > run_time){
			flag = 0;
		}

//		if(eiRnd(1000) < 10)
//			crsoundPlay(CRSOUND_EXT1);
//		else if(eiRnd(1000) < 10)
//			crsoundPlay(CRSOUND_EXT2);

crdataEnableRec(0);
		crbatDrawScene();

		if(eid3d->Begin()){
			eid3d->BeginAlphaBlend();
			crbatDraw_SetViewport(0);
			crbatDraw_SetMatrix(0);
			eid3d->SetTexture(NULL);


			eid3d->SetDrawMode(EID3D_DRAWMODE_CULLNONE);

			for(a = 0;a < lstart;a ++){
				if(a < lstart - 1 && t > 3000)
					continue;

				eid3d->SetMaterial(&material[a]);
				BatPart[a].MoveFrame(addw);
				BatPart[a].Draw(BatPart[a].Info.VertexCount / 2);
			}

			crbatSetAddAlpha();
			eid3d->SetMaterial(&material[lstart]);
			eid3d->SetDrawMode(EID3D_DRAWMODE_CULLNONE);

			crbatSetAddAlpha();
			for(a = lstart;a < lcount;a ++){
				BatPart[a].MoveFrame(addw);
				BatPart[a].Draw();
			}

			eid3d->SetMaterial(NULL);
			eid3d->EndAlphaBlend();
			eid3d->End();
		}
crdataEnableRec(1);
		if(eiGetEndThread()){
			break;
		}
		crbatDrawRefresh();

		addw = (float)et->Get() / 10.0f;
	}

	for(a = 0;a < lcount;a ++){
		material[a].Release();
		BatPart[a].Release();
	}
}


//---エクスティンクション
CRBATANIME_API void crbatDoAnime_MagicExtinction2(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo)
{
	eiTime let;
	int AddWorld = 0,flag,begin_anime = 0;
	int a,b,c,anime3d = 0;
	float dis = 0;
	int red = 0,green = 0,blue = 0;
	int lcount = 3;
	CrBattleCharacter *pDstChara = pDamageInfo->pList[0];

	eiD3DMaterial material[2];
	float addw = 0;

	material[0].Create();
	material[0].SetDeffuseColor(red,green,blue,255);
	material[0].SetEmissiveColor(red / 4,green / 4,blue / 4,255);
	material[0].d3dMaterial.dcvSpecular.r = D3DVAL(0.0);
	material[0].d3dMaterial.dcvSpecular.g = D3DVAL(0.0);
	material[0].d3dMaterial.dcvSpecular.b = D3DVAL(0.0);
	material[0].d3dMaterial.dcvSpecular.a = D3DVAL(0.0);
	material[0].d3dMaterial.dcvAmbient.r  = D3DVAL(0.0); 
	material[0].d3dMaterial.dcvAmbient.g  = D3DVAL(0.0); 
	material[0].d3dMaterial.dcvAmbient.b  = D3DVAL(0.0); 
	material[0].d3dMaterial.dcvAmbient.a  = D3DVAL(0.0);
	material[0].Set();

	//---
	material[1].Create();
	material[1].SetDeffuseColor(0,0,0,255);
	material[1].SetEmissiveColor(0,0,0,255);
	material[1].Set();

	BatPart[0].CreateRandomTriangle(0.6f,0.3f,5000);
	BatPart[1].CreateTriangle(
		0,0,0,
		12.0f,0, 0,
		0,0,12.0f
	);
	BatPart[2].CreateTriangle(
		12.0f,0 , 0,
		0,0,12.0f,
		12.0f,0,12.0f
	);
	for(a = 3;a < lcount;a ++){
		BatPart[a].CreateTriangle(0,0,0,0,0,0,0,0,0);
	}

	for(a = 0;a < lcount;a ++){
		BatPart[a].SetWeight(0);
		BatPart[a].SetWorldPos(
			(float)(pDstChara->GetFieldX() + 0.50f),
			1.0f,
			(float)(pDstChara->GetFieldY() + 0.50f)
		);
		BatPart[a].SetRotationMode(0);
		BatPart[a].SetMoveSpeed(0.0f);
		BatPart[a].SetMoveRotation(0,0);
	}
	BatPart[1].SetWorldPos(
		0,0.01f,0
	);
	BatPart[2].SetWorldPos(
		0,0.01f,0
	);

	for(a = 1;a < lcount;a ++){
		BatPart[a].SetMoveVectorXYZ(0,3.0f,0);
	}
	BatPart[0].SetWorldPos(
		(float)(pDstChara->GetFieldX() + 0.50f),
		-1.0f,
		(float)(pDstChara->GetFieldY() + 0.50f)
	);
	BatPart[0].SetWeight(0);
	BatPart[0].SetMoveRotation(0,0.2f);
	BatPart[0].SetRotationMode(1);

	eiD3DParticle_SetG(0.00f);

	//--------------------------------------------
	EIMEMORY hmem = eiAllocMemory(sizeof(float) * BatPart[0].Info.VertexCount + 10000);
	float *pMoveData = (float *)eiLockMemory(hmem);
	float div;
	c = 0;
	for(a = 0;a < BatPart[c].Info.VertexCount;a += 3){
		div = (float)(
				sqrt(BatPart[c].Info.pVertex[a].x * BatPart[c].Info.pVertex[a].x
				+ BatPart[c].Info.pVertex[a].y * BatPart[c].Info.pVertex[a].y
				+ BatPart[c].Info.pVertex[a].z * BatPart[c].Info.pVertex[a].z
				)
			);

		pMoveData[a + 0] = 
			(float)(BatPart[c].Info.pVertex[a].x * div);
		pMoveData[a + 1] = 
			(float)(BatPart[c].Info.pVertex[a].y * div);
		pMoveData[a + 2] = 
			(float)(BatPart[c].Info.pVertex[a].z * div);
	}
	//--------------------------------------------


	let.Reset();
	flag = 1;
	addw = 0;


	int anime_flag = 0,t,run_time = 2000;
	float f = 0.005f,g,speed = 0.03f,now_rate;

	crsoundPlay(CRSOUND_RUIN2);
	while(flag){
		et->Reset();
		t = let.Get();

		now_rate = ((float)(t) / run_time) * 100.0f;

		if(anime_flag == 0){
			material[0].SetDeffuseColor(0,0,0,255 - (int)((float)t * 255.0f / (float)run_time));
			if(t < 500){
				material[1].SetDeffuseColor(0,0,0,(int)((float)t * 127.0f / 500.0f));
			} else if(t < 1500){
				material[1].SetDeffuseColor(0,0,0,127);
			} else {
				material[1].SetDeffuseColor(0,0,0,127 - (int)((float)(t - 1500) * 127.0f / 500.0f));
			}
			f = 0.3f;
			g = 0.4f;

			c = 0;
			for(a = 0;a < BatPart[c].Info.VertexCount;a += 3){
				for(b = 0;b < 3;b ++){
/*					BatPart[c].Info.pVertex[a + b].x +=
						(BatPart[c].Info.pVertex[a].nx * addw * f);
					BatPart[c].Info.pVertex[a + b].y +=
						(BatPart[c].Info.pVertex[a].ny * addw * g);
					BatPart[c].Info.pVertex[a + b].z +=
						(BatPart[c].Info.pVertex[a].nz * addw * f);*/
					BatPart[c].Info.pVertex[a + b].x +=
						(pMoveData[a + 0] * addw * f);
					BatPart[c].Info.pVertex[a + b].y +=
						(pMoveData[a + 1] * addw * g);
					BatPart[c].Info.pVertex[a + b].z +=
						(pMoveData[a + 2] * addw * f);
				}
			}
		}

		if(anime3d == 0 && anime_flag == 0 && let.Get() > run_time){
			flag = 0;
		}

crdataEnableRec(0);
		crbatDrawScene();

		if(eid3d->Begin()){
			eid3d->BeginAlphaBlend();
			crbatDraw_SetViewport(0);
			crbatDraw_SetMatrix(0);
			eid3d->SetTexture(NULL);

			eid3d->SetDrawMode(EID3D_DRAWMODE_CULLNONE);
			eid3d->SetMaterial(&material[0]);
			BatPart[0].MoveFrame(addw);
			BatPart[0].Draw(BatPart[0].Info.VertexCount / 2);
			eid3d->SetMaterial(&material[1]);
			eid3d->SetDrawMode(EID3D_DRAWMODE_CULLNONE);

//			crbatSetAddAlpha();
			for(a = 1;a < lcount;a ++){
				BatPart[a].Draw();
			}

			eid3d->SetMaterial(NULL);
			eid3d->EndAlphaBlend();
			eid3d->End();
		}
crdataEnableRec(1);
		if(eiGetEndThread()){
			break;
		}
		crbatDrawRefresh();

		addw = (float)et->Get() / 10.0f;
	}

	eiUnlockMemory(hmem);
	eiFreeMemory(hmem);

	material[0].Release();
	material[1].Release();

	for(a = 0;a < lcount;a ++){
		BatPart[a].Release();
	}
}

eiD3DMaterial *pGmaterial = NULL;
eiTextureCell *pGtex = NULL;

void RuinCallBack(eiCell *pCell,int mode)
{
	if(eid3d->Begin()){
		eid3d->BeginAlphaBlend();

		crbatDraw_SetViewport(0);
		crbatDraw_SetMatrix(0);

		eid3d->SetDrawMode(EID3D_DRAWMODE_CULLNONE);
		eid3d->SetMaterial(&pGmaterial[0]);
		eid3d->SetTexture(&pGtex[0]);
		eid3d->SetTextureColorkey(1);

		BatPart[0].Draw();
		BatPart[1].Draw();

		eid3d->SetTextureColorkey(0);

		eid3d->SetMaterial(&pGmaterial[1]);
		eid3d->SetDrawMode(EID3D_DRAWMODE_CULLNONE);

		eid3d->SetMaterial(NULL);
		eid3d->SetTexture(NULL);
		eid3d->EndAlphaBlend();
		eid3d->End();
	}
}

//---ルーイン
CRBATANIME_API void crbatDoAnime_MagicRuin(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo)
{
	eiTime let;
	int AddWorld = 0,flag,begin_anime = 0;
	int a,b,c,anime3d = 0;
	float dis = 0;
	int red = 192,green = 192,blue = 224;
	int lcount = 1;
	CrBattleCharacter *pDstChara = pDamageInfo->pList[0];

	eiD3DMaterial material[2];
	float addw = 0;

	red = blue = green = 0;

	eiTextureCell tex[40];
	float range = 0,dr = 4.0f;

	pGmaterial = material;
	pGtex = tex;

	char s[80];
	sprintf(s,"%sshadow2.acf",CR_DATADIR4);
	tex[0].ReadFile(s,CR_DATAFILE4,crdataGetFileMode());
	tex[0].Init(16);
	tex[0].Load();

	BatPart[0].CreateTriangle(
		-dr,0,-dr,
		dr,0,-dr,
		dr,0,dr);
	BatPart[0].Info.Vertex[0].tu = 0;
	BatPart[0].Info.Vertex[0].tv = 0;
	BatPart[0].Info.Vertex[1].tu = 1;
	BatPart[0].Info.Vertex[1].tv = 0;
	BatPart[0].Info.Vertex[2].tu = 1;
	BatPart[0].Info.Vertex[2].tv = 1;

	BatPart[1].CreateTriangle(
		-dr,0,-dr,
		-dr,0,dr,
		dr,0,dr);
	BatPart[1].Info.Vertex[0].tu = 0;
	BatPart[1].Info.Vertex[0].tv = 0;
	BatPart[1].Info.Vertex[1].tu = 0;
	BatPart[1].Info.Vertex[1].tv = 1;
	BatPart[1].Info.Vertex[2].tu = 1;
	BatPart[1].Info.Vertex[2].tv = 1;

	for(a = 0;a < 2;a ++){
		BatPart[a].SetMoveSpeed(0);
		BatPart[a].SetRotationMode(0);
		BatPart[a].SetWeight(0);
		BatPart[a].SetWorldPos(
			(float)pDstChara->GetFieldX(),
			0.01f,
			(float)pDstChara->GetFieldY());
		BatPart[a].SetMoveRotation(0,0,0);
	}

	for(a = 2;a < 2 + lcount;a ++){
		BatPart[a].CreateSphere(3.0f,20,20,5.0f,6.0f);
//		BatPart[a].CreateRandomTriangle(0.1f,0.5f,1000);
		BatPart[a].SetMoveSpeed(0);
		BatPart[a].SetRotationMode(1);
		BatPart[a].SetWeight(0);
		BatPart[a].SetWorldPos(
			(float)pDstChara->GetFieldX(),
			1.01f,
			(float)pDstChara->GetFieldY());
		BatPart[a].SetMoveRotation(0,0.01f,0);

		for(b = 0;b < BatPart[a].Info.VertexCount / 2;b ++){
			BatPart[a].Info.pVertex[b].y = 0;

//			BatPart[a].Info.pVertex[b].ny += (float)(
//				(float)eiRnd(1000) / 1000.0f - 0.5f);

/*			BatPart[a].Info.pVertex[b].ny = -(2 - 
				BatPart[a].Info.pVertex[b].nx * BatPart[a].Info.pVertex[b].nx
			  + BatPart[a].Info.pVertex[b].nz * BatPart[a].Info.pVertex[b].nz
			  );

			BatPart[a].Info.pVertex[b].nx += (float)(
				(float)eiRnd(1000) / 10000.0f - 0.05f);
			BatPart[a].Info.pVertex[b].nz += (float)(
				(float)eiRnd(1000) / 10000.0f - 0.05f);*/
		}
	}

	material[0].Create();
	material[0].SetDeffuseColor(red,green,blue,127);
	material[0].SetEmissiveColor(red / 4,green / 4,blue / 4,255);
	material[0].d3dMaterial.dcvSpecular.r = D3DVAL(1.0);
	material[0].d3dMaterial.dcvSpecular.g = D3DVAL(1.0);
	material[0].d3dMaterial.dcvSpecular.b = D3DVAL(1.0);
	material[0].d3dMaterial.dcvSpecular.a = D3DVAL(1.0);
	material[0].d3dMaterial.dcvAmbient.r  = D3DVAL(0.0); 
	material[0].d3dMaterial.dcvAmbient.g  = D3DVAL(0.0); 
	material[0].d3dMaterial.dcvAmbient.b  = D3DVAL(0.0); 
	material[0].d3dMaterial.dcvAmbient.a  = D3DVAL(0.0);
	material[0].Set();

	//---
	material[1].Create();
	material[1].SetDeffuseColor(0,0,0,192);
	material[1].SetEmissiveColor(0 / 4,0 / 4,0 / 4,192);
	material[1].Set();

	eiD3DParticle_SetG(0.00f);

	let.Reset();
	flag = 1;
	addw = 0;

	crbatSetDrawSceneCallback2(RuinCallBack);

	int anime_flag = 0,t,run_time = 3000,col;
	float f = 0.005f,g,speed = 0.03f,now_rate;
	float temp[8];

	crsoundPlay(CRSOUND_RUIN1);

	while(flag){
		et->Reset();
		t = let.Get();

		now_rate = (float)(run_time - t) / run_time;

		if(anime_flag == 0){
			col = t * 255 / 500;
			material[0].SetDeffuseColor(255,255,255,col);
			material[1].SetDeffuseColor(0,0,0,col / 3);

			if(let.Get() > 500){
				let.Reset();
				anime_flag = 1;
			}
		} else if(anime_flag == 1){
			if(t < 1500){
				material[0].SetDeffuseColor(255,255,255,255);
				material[1].SetDeffuseColor(0,0,0,255);
//				material[1].SetDeffuseColor(255,255,255,255);
			} else {
				col = (500 - (t - 1500)) * 255 / 500;
				material[0].SetDeffuseColor(255,255,255,col);
				material[1].SetDeffuseColor(0,0,0,col / 4);
			}

			f = -(t * 0.0070f);
			g = -(t * 0.000048f);//1.37f * 1.2f;

			temp[0] = addw * g;
			temp[1] = addw * f;
			c = 2;
			for(a = 0;a < BatPart[c].Info.VertexCount / 2;a += 3){	
				temp[3] = (BatPart[c].Info.pVertex[a].nx * temp[1]);
				temp[4] = (BatPart[c].Info.pVertex[a].ny * temp[0]);
				temp[5] = (BatPart[c].Info.pVertex[a].nz * temp[1]);

				for(b = 0;b < 3;b ++){
					BatPart[c].Info.pVertex[a + b].x +=
						(temp[3]);
//					BatPart[c].Info.pVertex[a + b].y +=
//						(temp[4]);
					BatPart[c].Info.pVertex[a + b].z +=
						(temp[5]);
				}
			}

			if(let.Get() > 2000)
				flag = 0;
		}

		crbatClearDrawingList();
		crbatAddDrawingListAll();

crdataEnableRec(0);

		crbatDrawScene();

		if(eid3d->Begin()){
			eid3d->BeginAlphaBlend();

			crbatDraw_SetViewport(0);
			crbatDraw_SetMatrix(0);

			eid3d->SetDrawMode(EID3D_DRAWMODE_CULLNONE);
			eid3d->SetMaterial(&material[1]);
			eid3d->SetTexture(NULL);

			BatPart[2].MoveFrame(addw);
			BatPart[2].Draw(BatPart[2].Info.VertexCount / 2);

			eid3d->SetMaterial(NULL);
			eid3d->SetTexture(NULL);
			eid3d->EndAlphaBlend();
			eid3d->End();
		}

crdataEnableRec(1);
		if(eiGetEndThread()){
			crbatSetDrawSceneCallback2(NULL);
			break;
		}
		crbatDrawRefresh();

		addw = (float)et->Get() / 10.0f;
	}
	material[0].Release();
	material[1].Release();

	for(a = 0;a < 2 + lcount;a ++){
		BatPart[a].Release();
	}

/*	for(a = 0;a < lcount;a ++){
		BatPart[a].Release();
	}*/

	tex[0].ReleaseTexture();
	crbatSetDrawSceneCallback2(NULL);
}

//---変身
CRBATANIME_API void crbatDoAnime_MagicCrasiveHenshin(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo)
{
	eiTime let;
	int AddWorld = 0,flag,begin_anime = 0;
	int a,b,c,anime3d = 0,count;
	float dis = 0;
	CrBattleCharacter *pDstChara[16];
	//= pDamageInfo->pList[0];

	eiD3DMaterial material[4];
	float addw = 0;
	int red = 255,green = 255,blue = 255;
	int mode = 3;

	if(crsysQuick()){
		return;
	}

	int dst_count;
	for(a = 0,dst_count = 0;pDamageInfo->pList[a] != NULL;a ++){
		pDstChara[a] = pDamageInfo->pList[a];
		dst_count ++;
	}
	pDstChara[a] = NULL;
	dst_count = 1;

	for(a = 0;a < 4;a ++){
		material[a].Create();
		material[a].SetDeffuseColor(red ,green ,blue,192);
		material[a].SetEmissiveColor(red,green ,blue ,192);
		material[a].Set();
	}
	material[2].SetDeffuseColor(255 ,255 ,0,192);
	material[3].SetDeffuseColor(255 ,255 ,0,192);

	//---球
	for(a = 0;a < 1;a ++){
		BatPart[a].CreateSphere(0.5f,32,32,0.0f,3.141592f);

		BatPart[a].SetWeight(0);
		BatPart[a].SetWorldPos(
			(float)(pChara->GetFieldX()),
			0.0f,
			(float)(pChara->GetFieldY())
		);
		BatPart[a].SetRotationMode(1);
		BatPart[a].SetMoveSpeed(0.0f);
		BatPart[a].SetMoveRotation(0.25f,0.20f,0.01f);
		BatPart[a].SetMoveVectorXYZ(
			0.0f,1.0f,0.0f
		);
	}

	//---閃
	int linestart = 1;
	for(c = 0;c < dst_count;c ++){
		float x = (float)pChara->GetFieldX();
		float y = (float)pChara->GetFieldY();
		float height = 0.0f;//(float)pChara->GetCharaHeight() / 128.0f + 0.5;
		float angle[2] = {ANGLE(eiRnd(360)) , ANGLE(eiRnd(360))};
		float dr = 12.0f,dangle = 0.05f;
		for(b = 0;b < 8;b ++){
			BatPart[linestart + c * 8 + b].CreateTriangle(
				0,0,0,
				x + (float)cos(angle[0]) * dr,
				0 + (float)cos(angle[1]) * dr,
				y + (float)sin(angle[0]) * dr,

				x + (float)cos(angle[0] + dangle) * dr,
				0 + (float)cos(angle[1]) * dr,
				y + (float)sin(angle[0] + dangle) * dr);

			BatPart[linestart + c * 8 + b].SetWeight(0);
			BatPart[linestart + c * 8 + b].SetWorldPos(
				(float)x,
				height,
				(float)y
			);
			BatPart[linestart + c * 8 + b].SetRotationMode(1);
			BatPart[linestart + c * 8 + b].SetMoveSpeed(0.0f);
			BatPart[linestart + c * 8 + b].SetMoveRotation(0,0);
			BatPart[linestart + c * 8 + b].SetMoveVectorXYZ(
				0.0f,1.0f,0.0f
			);
		}
	}

	int bomb_start = linestart + 8 * dst_count,bomb_count = 1;
	for(a = bomb_start;a < bomb_start + bomb_count;a ++){
		BatPart[a].CreateSphere(2.5,48,48);
		BatPart[a].SetWorldPos(
			(float)pChara->GetFieldX(),
			1.0f,
			(float)pChara->GetFieldY());
		BatPart[a].SetRotationMode(1);
		BatPart[a].SetMoveRotation(0,0);
		BatPart[a].SetMoveSpeed(0);
		BatPart[a].SetMoveVectorXYZ(0,1,0);
		BatPart[a].SetWeight(1);

		c = a;
		for(b = 0;b < BatPart[c].Info.VertexCount / 2;b += 3){	
			BatPart[c].Info.pVertex[b].nx +=
				((float)(eiRnd(1000) - 500) / 2500.0f);
			BatPart[c].Info.pVertex[b].ny +=
				((float)(eiRnd(1000) - 500) / 2500.0f);
			BatPart[c].Info.pVertex[b].nz +=
				((float)(eiRnd(1000) - 500) / 2500.0f);
		}

		int d;
		for(;b < BatPart[c].Info.VertexCount;b += 3){	
			BatPart[c].Info.pVertex[b].nx +=
				((float)(eiRnd(1000) - 500) / 2500.0f);
			BatPart[c].Info.pVertex[b].nx *= 0.5f;

			BatPart[c].Info.pVertex[b].ny +=
				((float)(eiRnd(1000) - 500) / 2500.0f);
			BatPart[c].Info.pVertex[b].ny *= 0.5f;

			BatPart[c].Info.pVertex[b].nz +=
				((float)(eiRnd(1000) - 500) / 2500.0f);
			BatPart[c].Info.pVertex[b].nz *= 0.5f;

			for(d = 0;d < 3;d ++){
				BatPart[a].Info.pVertex[b + d].x *= 0.9f;
				BatPart[a].Info.pVertex[b + d].y *= 0.9f;
				BatPart[a].Info.pVertex[b + d].z *= 0.9f;
			}
		}
	}
	count = a;

	eiD3DParticle_SetG(0.02f);

	let.Reset();
	flag = 1;
	addw = 0;

	int anime_flag = 0,t,sound_flag = 0;
	float f = 0.005f,g = 0,speed = 0.03f;
	int slash_time[8] = {0,0,0,0 ,0,0,0,0}
		,prev_slash[8] =  {0,0,0,0 ,0,0,0,0};

//	crsoundPlay(CRSOUND_DIFFUSION1,EISOUND_PLAYLOOP);
//	crsoundPlay(CRSOUND_DIFFUSION2);
	while(flag){
		et->Reset();
		t = let.Get();

		if(anime_flag <= 2){
			for(c = linestart;c < linestart + 1 * 8;c ++){
				if(eiRnd(100) <= 25){
					float r = 12.0f,hr = (float)12,
						angle = ANGLE(eiRnd(360)),h_angle = ANGLE(eiRnd(360));
					BatPart[c].Info.Vertex[1].x = (float)cos(angle) * r;
					BatPart[c].Info.Vertex[1].z = (float)sin(angle) * r;
					BatPart[c].Info.Vertex[1].y = (float)sin(h_angle) * hr;
					BatPart[c].Info.Vertex[2].x = (float)cos(angle + ANGLE(1)) * r;
					BatPart[c].Info.Vertex[2].z = (float)sin(angle + ANGLE(1)) * r;
					BatPart[c].Info.Vertex[2].y = (float)sin(h_angle) * hr;
				}
			}
		}

		material[0].SetDeffuseColor(
			255,255,255, 128);
		material[0].SetEmissiveColor(
			255,255,255, 128);

		material[3].SetDeffuseColor(
			0,0,255, 160);
		if(anime_flag == 0){
			material[0].SetDeffuseColor(
				255 * t / 3000,255 * t / 1800 ,255, 128 * t / 6000);
			material[0].SetEmissiveColor(
				255 * t / 3000,255 * t / 1800 ,255, 128 * t / 6000);
			material[3].SetDeffuseColor(
				0,0,255, 160 * t / 6000);
		}

		if(anime_flag == 0 && t > 6000){
			anime_flag = 1;
			let.Reset();
//			crsoundPlay(CRSOUND_DIFFUSION3);
//			crsoundPlay(43);
			flag = 0;
		}

crdataEnableRec(0);
		crbatDrawScene();

		if(eid3d->Begin()){
			eid3d->BeginAlphaBlend();
			crbatDraw_SetViewport(0);
			crbatDraw_SetMatrix(0);
			eid3d->SetTexture(NULL);

			crbatSetAddAlpha();
			eid3d->SetDrawMode(EID3D_DRAWMODE_CULLNONE);

			if(anime_flag <= 2){
				for(c = 0;c < 1;c ++){
					eid3d->SetMaterial(&material[0]);
					BatPart[c].MoveFrame((float)addw);
					BatPart[c].Draw(BatPart[c].Info.VertexCount / 2);
				}
			}

			if(anime_flag == 0 || anime_flag == 2){
				eid3d->SetMaterial(&material[3]);
				for(c = linestart;c < linestart + dst_count * 8;c ++){
					BatPart[c].MoveFrame((float)addw);
					BatPart[c].Draw();
				}
			}
			eid3d->SetMaterial(NULL);
			eid3d->EndAlphaBlend();
			eid3d->End();
		}

		if(t > 3000){
			D3DTLVERTEX ver[4];
			RECT rect = BattleViewRect[BattleViewMode][0];
			rect.right += rect.left;
			rect.bottom += rect.top;

			memset(&ver[0],0,sizeof(ver));
			ver[0].sx = ver[2].sx = (float)(rect.left);
			ver[0].sy = ver[1].sy = (float)(rect.top);
			ver[1].sx = ver[3].sx = (float)(rect.right);
			ver[2].sy = ver[3].sy = (float)(rect.bottom);

			int alpha = 255 * (t - 3000) / 3000;
			if(alpha > 255)
				alpha = 255;
			for(a = 0;a < 4;a ++){
				ver[a].dcColor = RGBA_MAKE(255,255,255,alpha);
				ver[a].rhw = 1;
			}

			if(eid3d->Begin()){
				eid3d->BeginAlphaBlend();
				crbatSetAddAlpha();

				eid3d->DrawPrimitive(
					D3DPT_TRIANGLESTRIP,D3DFVF_TLVERTEX,
					&ver[0],4,D3DDP_WAIT);
				eid3d->EndAlphaBlend();
				eid3d->End();
			}
		}

crdataEnableRec(1);
		if(eiGetEndThread()){
			break;
		}
		crbatDrawRefresh();

		addw = (float)et->Get() / 10.0f;
	}
	material[0].Release();
	material[1].Release();
	material[2].Release();
	material[3].Release();

	for(a = 0;a < count;a ++){
		BatPart[a].Release();
	}
//	pChara->SetNotShow(1);
//	pChara->SetNotShow(0);
}


//---インフレーション
CRBATANIME_API void crbatDoAnime_MagicInfretion(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,int mode)
{
	eiTime let,let2;
	int AddWorld = 0,flag,begin_anime = 0;
	int a,b = 0,c,anime3d = 0,tex_number = 0;
	float dis = 0;
	CrBattleCharacter *pDstChara[16];
	int dst_count;

	for(a = 0,dst_count = 0;pDamageInfo->pList[a] != NULL;a ++){
		pDstChara[a] = pDamageInfo->pList[a];
		dst_count ++;
	}
	pDstChara[0] = pDamageInfo->pList[eiRnd(dst_count)];
	pDstChara[a] = NULL;
	dst_count = 1;

	eiTextureCell tex[4];
	float range = 0,dr;
	char s[80];
	for(a = 0;a < 4;a ++){
		sprintf(s,"%sFire%d.acf",CR_DATADIR4,a + 1);
		tex[a].ReadFile(s,CR_DATAFILE4,crdataGetFileMode());
		tex[a].Init(16);
		tex[a].Load();
	}

	eiD3DMaterial material[2];
	material[0].Create();
	material[0].SetDeffuseColor(255,127,0,0);
	material[0].SetEmissiveColor(96,0,0,127);
	material[0].Set();
	material[1].Create();
	material[1].SetDeffuseColor(127,127,255,127);
	material[1].SetEmissiveColor(127,127,255,127);
	material[1].Set();

	if(mode == 0)
		dr = 0.3f;
	else
		dr = -1.6f;

	int tri_count,tri_start = 32;
	if(mode == 0)
		tri_count = 1000;
	else if(mode == 1)
		tri_count = 250;

	float r = 0.5f,
		speed = 0.2f;

	if(mode == 1){
		speed = 0.07f;
		r = 0.15f;
	}

	//----------------------------------
	for(a = 0;a < 3;a ++){
		if(a < 2)
			BatPart[a].CreateSphere(0.1f,12,12);
		else
			BatPart[a].CreateSphere(1.0f,60,60,0,3.1415f);
		BatPart[a].SetWorldPos(
			(float)(pDstChara[0]->GetFieldX()),
			(float)(0),
			(float)(pDstChara[0]->GetFieldY())
			);
		BatPart[a].SetMoveSpeed(0);
		BatPart[a].SetRotationMode(1);
		BatPart[a].SetMoveRotation(0,0);
		BatPart[a].SetMoveSpeed(0.0f);

		BatPart[a].SetMoveVectorXYZ(
			0,1.0f,0
		);
	}

	//---閃
	int linestart = 3,linecount = 8;
	for(c = 0;c < dst_count;c ++){
		float x = (float)pDstChara[0]->GetFieldX();
		float y = (float)pDstChara[0]->GetFieldY();
		float height = 0.0f;//(float)pChara->GetCharaHeight() / 128.0f + 0.5;
		float angle[2] = {ANGLE(eiRnd(360)) , ANGLE(eiRnd(360))};
		float dr = 20.0f,dangle = 0.01f;
		for(b = 0;b < linecount;b ++){
			BatPart[linestart + c * linecount + b].CreateTriangle(
				0,0,0,
				x + (float)cos(angle[0]) * dr,
				0 + (float)cos(angle[1]) * dr,
				y + (float)sin(angle[0]) * dr,

				x + (float)cos(angle[0] + dangle) * dr,
				0 + (float)cos(angle[1]) * dr,
				y + (float)sin(angle[0] + dangle) * dr);

			BatPart[linestart + c * linecount + b].SetWeight(0);
			BatPart[linestart + c * linecount + b].SetWorldPos(
				(float)x,
				height,
				(float)y
			);
			BatPart[linestart + c * linecount + b].SetRotationMode(1);
			BatPart[linestart + c * linecount + b].SetMoveSpeed(0.0f);
			BatPart[linestart + c * linecount + b].SetMoveRotation(0,0);
			BatPart[linestart + c * linecount + b].SetMoveVectorXYZ(
				0.0f,0.0f,0.0f
			);
		}
	}

	//--------------------------------------------
	EIMEMORY hmem = eiAllocMemory(sizeof(float) * BatPart[2].Info.VertexCount + 10000);
	float *pMoveData = (float *)eiLockMemory(hmem);
	c = 2;
	for(a = 0;a < BatPart[c].Info.VertexCount / 2;a += 3){	
		pMoveData[a + 0] = BatPart[c].Info.pVertex[a].nx +
			((float)(eiRnd(1000) - 500) / 2500.0f);
		pMoveData[a + 1] = BatPart[c].Info.pVertex[a].ny +
			((float)(eiRnd(1000) - 500) / 2500.0f);
		pMoveData[a + 2] = BatPart[c].Info.pVertex[a].nz +
			((float)(eiRnd(1000) - 500) / 2500.0f);
	}
	//--------------------------------------------

	float addw = 0;

	eiD3DParticle_SetG(0.01f);

	let.Reset();
	let2.Reset();
	flag = 1;
	addw = 0;

	int sound = 0,anime_flag = 0,t,show_ver = 1;
	float f = 0.015f,g = 0.017f,addt = 0,spx = 0,spy = 0;
	float fast = 0,fast2 = 0,rate;
	crsoundPlay(CRSOUND_FIRE4);

	anime_flag = 0;
	while(flag){
		et->Reset();
		t = let.Get();

		if(anime_flag == 0){
			spx = t * 0.0005f;
			spy = t * 0.0001f;
			BatPart[0].SetMoveRotation(spx,spy);
//			BatPart[0].SetMoveRotation(0,0);
			BatPart[1].SetMoveRotation(-spx * 0.5f,-spy * 0.5f);

			rate = (float)t / 2000.0f;

			material[0].SetDeffuseColor(255,
				64 + (int)(191.0f * rate),
				(int)(160.0f * rate),
				(int)(rate * 255.0f)
			);
		}

		if(anime_flag <= 2){
			//---光
			for(c = linestart;c < linestart + 1 * linecount;c ++){
				if(eiRnd(100) <= 40 + anime_flag * 20){
					float r = 20.0f,hr = (float)20.0f,
						angle = ANGLE(eiRnd(360)),h_angle = ANGLE(eiRnd(360));
					BatPart[c].Info.Vertex[1].x = (float)cos(angle) * r;
					BatPart[c].Info.Vertex[1].z = (float)sin(angle) * r;
					BatPart[c].Info.Vertex[1].y = (float)sin(h_angle) * hr;
					BatPart[c].Info.Vertex[2].x = (float)cos(angle + ANGLE(1)) * r;
					BatPart[c].Info.Vertex[2].z = (float)sin(angle + ANGLE(1)) * r;
					BatPart[c].Info.Vertex[2].y = (float)sin(h_angle) * hr;
				}
			}
		}
		if(anime_flag == 2){
			BatPart[0].SetMoveRotation(0,0);
			BatPart[1].SetMoveRotation(0,0);
//			f = 0.15f;
//			g = 0.17f;
			material[0].SetDeffuseColor(255,64,0,255 - (int)((float)t * (255.0f / 2000.0f)));
			material[1].SetDeffuseColor(127,127,255,127 - (int)((float)t * (127.0f / 2000.0f)));
		}

		if(anime_flag == 0 && let.Get() > 2000){
//			flag = 0;
			crsoundPlay(CRSOUND_DIFFUSION4/*CRSOUND_FIRE5*/);
			anime_flag = 2;
			let.Reset();
			f = 0;

			c = 2;
/*			for(a = 0;a < BatPart[c].Info.VertexCount / 2;a += 3){	
				BatPart[c].Info.pVertex[a].nx +=
					((float)(eiRnd(1000) - 500) / 2500.0f);
				BatPart[c].Info.pVertex[a].ny +=
					((float)(eiRnd(1000) - 500) / 2500.0f);
				BatPart[c].Info.pVertex[a].nz +=
					((float)(eiRnd(1000) - 500) / 2500.0f);
			}*/
		}

		if(anime_flag == 2 && let.Get() > 2000){
			flag = 0;
		}

		//---めらめら
		if(let2.Get() > 50){
			if(++ tex_number >= 4)
				tex_number = 0;
			let2.Reset();
		}

		crbatClearDrawingList();
		crbatAddDrawingListAll();

crdataEnableRec(0);
		crbatDrawScene();
		if(anime_flag == 0){
			if(eid3d->Begin()){
				eid3d->BeginAlphaBlend();
				crbatDraw_SetViewport(0);
				crbatDraw_SetMatrix(0);
				eid3d->SetMaterial(&material[0]);
//				eid3d->SetTexture(&tex[tex_number]);
				eid3d->SetTexture(NULL);

				eid3d->SetDrawMode(EID3D_DRAWMODE_CULLNONE);
				crbatSetAddAlpha();

				c = 1;
				fast = addw * g;
				for(a = 0;a < BatPart[c].Info.VertexCount / 2;a += 3){	
					for(b = 0;b < 3;b ++){
						BatPart[c].Info.pVertex[a + b].x +=
							(BatPart[c].Info.pVertex[a + b].nx * fast);
						BatPart[c].Info.pVertex[a + b].y +=
							(BatPart[c].Info.pVertex[a + b].ny * fast);
						BatPart[c].Info.pVertex[a + b].z +=
							(BatPart[c].Info.pVertex[a + b].nz * fast);
					}
				}
				c = 0;
				fast = addw * f;
				for(a = 0;a < BatPart[c].Info.VertexCount / 2;a += 3){	
					for(b = 0;b < 3;b ++){
						BatPart[c].Info.pVertex[a + b].x +=
							(BatPart[c].Info.pVertex[a + b].nx * fast);
						BatPart[c].Info.pVertex[a + b].y +=
							(BatPart[c].Info.pVertex[a + b].ny * fast);
						BatPart[c].Info.pVertex[a + b].z +=
							(BatPart[c].Info.pVertex[a + b].nz * fast);
					}
				}

				for(a = 0;a < 2;a ++){
					BatPart[a].MoveFrame(addw);
					BatPart[a].Draw(BatPart[a].Info.VertexCount / 2);
				}

				//---line
				eid3d->SetMaterial(&material[1]);
				for(c = linestart;c < linestart + dst_count * linecount;c ++){
					BatPart[c].MoveFrame((float)addw);
					BatPart[c].Draw();
				}

				eid3d->SetTexture(NULL);
				eid3d->SetMaterial(NULL);
				eid3d->EndAlphaBlend();
				eid3d->End();
			}
		}
		if(anime_flag == 2){
			if(eid3d->Begin()){
				eid3d->BeginAlphaBlend();
				crbatDraw_SetViewport(0);
				crbatDraw_SetMatrix(0);
				eid3d->SetMaterial(&material[0]);
//				eid3d->SetTexture(&tex[tex_number]);
				eid3d->SetTexture(NULL);
				eid3d->SetDrawMode(EID3D_DRAWMODE_CULLNONE);
				crbatSetAddAlpha();

				c = 2;
//				f -= (t * 0.0000006f);
				f = 0.14f -(t * 0.00006f);
				g = 0.14f;// - t * 0.0001f;
/*				fast = addw * g;
				fast2 = addw * f;
				for(a = 0;a < BatPart[c].Info.VertexCount / 2;a += 3){	
					for(b = 0;b < 3;b ++){
						BatPart[c].Info.pVertex[a + b].x +=
							(BatPart[c].Info.pVertex[a].nx * fast);
						BatPart[c].Info.pVertex[a + b].y +=
							(BatPart[c].Info.pVertex[a].ny * fast2);
						BatPart[c].Info.pVertex[a + b].z +=
							(BatPart[c].Info.pVertex[a].nz * fast);
					}
				}*/
				float temp[6];

				temp[0] = addw * g;
				temp[1] = addw * f;
				{
					c = 2;
					for(a = 0;a < BatPart[c].Info.VertexCount;a += 3){	
/*						temp[3] = (BatPart[c].Info.pVertex[a].nx * temp[0]);
						temp[4] = (BatPart[c].Info.pVertex[a].ny * temp[1]);
						temp[5] = (BatPart[c].Info.pVertex[a].nz * temp[0]);
*/
						temp[3] = (pMoveData[a + 0] * temp[0]);
						temp[4] = (pMoveData[a + 1] * temp[1]);
						temp[5] = (pMoveData[a + 2] * temp[0]);

						for(b = 0;b < 3;b ++){
							BatPart[c].Info.pVertex[a + b].x +=
								(temp[3]);// * temp[0]);
							BatPart[c].Info.pVertex[a + b].y +=
								(temp[4]);//* temp[1]);
							BatPart[c].Info.pVertex[a + b].z +=
							(temp[5]);// * temp[0]);
						}
					}
				}


				BatPart[2].MoveFrame((float)addw);
				BatPart[2].Draw(BatPart[2].Info.VertexCount);

				//---line
				eid3d->SetMaterial(&material[1]);
				for(c = linestart;c < linestart + dst_count * linecount;c ++){
					BatPart[c].MoveFrame((float)addw);
					BatPart[c].Draw();
				}

				eid3d->SetTexture(NULL);
				eid3d->SetMaterial(NULL);
				eid3d->EndAlphaBlend();
				eid3d->End();
			}
		}
crdataEnableRec(1);
		if(eiGetEndThread()){
			break;
		}
		crbatDrawRefresh();

		addw = (float)et->Get() / 10.0f;
	}

	eiUnlockMemory(hmem);
	eiFreeMemory(hmem);

	crbatClearDrawingList();
	crbatAddDrawingListAll();

	for(a = 0;a < 4;a ++){
		tex[a].ReleaseTexture();
	}
	for(a = 0;a < 2;a ++){
		material[a].Release();
	}
	for(a = 0;a < 3 + linecount;a ++){
		BatPart[a].Release();
	}
}
