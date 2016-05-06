//---“y
CRBATANIME_API void crbatDoAnime_MagicTsuchi(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,int mode)
{
	eiTime let;
	int AddWorld = 0,flag,begin_anime = 0;
	int a,b,anime3d = 0;
	float dis = 0;
	CrBattleCharacter *pDstChara = pDamageInfo->pList[0];

	eiD3DMaterial material;
	float addw = 0;

	material.Create();
	material.SetDeffuseColor(192,162,0,255);
	material.SetEmissiveColor(64,0,0,127);
	material.Set();

	eiD3DParticle_SetG(0.00f);

	BatPart[0].CreateSphere(0.05f,8,8);
	BatPart[0].SetWeight(1);
	BatPart[0].SetWorldPos(
		(float)(pChara->GetFieldX() + 0.3 * cos(pChara->GetAngle())),
		(float)(pChara->GetFieldZ() + 0.7),
		(float)(pChara->GetFieldY() + 0.3 * sin(pChara->GetAngle()))
	);
	BatPart[0].SetRotationMode(1);
	BatPart[0].SetMoveRotation(0.05f,0.05f);
	BatPart[0].SetMoveSpeed(0.0f);
	BatPart[0].SetMoveVectorXYZ(
		(float)(pDstChara->GetFieldX() - pChara->GetFieldX()),
		(float)(pDstChara->GetFieldZ() - pChara->GetFieldZ()),
		(float)(pDstChara->GetFieldY() - pChara->GetFieldY())
	);

	let.Reset();
	flag = 1;
	addw = 0;

	int anime_flag = 0,t;
	float f = 0.005f,speed = 0.03f;
	float dx,dy,hdis = 9999,distanse;
	int sound = 0;
	crsoundPlay(49);
	while(flag){
		et->Reset();
		t = let.Get();

		dx = (float)BatPart[0].Info.wx - (float)pDstChara->GetFieldX();
		dy = (float)BatPart[0].Info.wz - (float)pDstChara->GetFieldY();
		distanse = (float)dx * dx + (float)dy * dy;
		if((distanse < 1.0f
			|| hdis < distanse) && anime_flag == 1){
			anime_flag = 2;
			eiD3DParticle_SetG(0.06f);
			let.Reset();
			if(!sound){
				crsoundPlay(48);
				sound = 1;
			}
		}

		hdis = (float)dx * dx + (float)dy * dy;

		if(anime_flag >= 1){
			BatPart[0].SetMoveSpeed(speed);
			speed = (float)(0.04f + ((float)let.Get() * 0.00005));
		}
		if(anime_flag == 0){
			if(let.Get() > 500){
				anime_flag = 1;
			}
			material.SetDeffuseColor(192,162,0,(int)( (float)t * 255.0f / 500.0f) );
			f = 0.012f;
			for(a = 0;a < BatPart[0].Info.VertexCount / 2;a += 3){
				for(b = 0;b < 3;b ++){
					BatPart[0].Info.pVertex[a + b].x +=
						(BatPart[0].Info.pVertex[a + b].nx * addw * f * (1.0f + (float)mode * 0.25f));
					BatPart[0].Info.pVertex[a + b].y +=
						(BatPart[0].Info.pVertex[a + b].ny * addw * f * (1.0f + (float)mode * 0.25f));
					BatPart[0].Info.pVertex[a + b].z +=
						(BatPart[0].Info.pVertex[a + b].nz * addw * f * (1.0f + (float)mode * 0.25f));
					}
			}
			for(;a < BatPart[0].Info.VertexCount;a += 3){
				for(b = 0;b < 3;b ++){
					BatPart[0].Info.pVertex[a + b + 3].x -=
						(BatPart[0].Info.pVertex[a + b + 3].nx * addw * f * (1 + (float)mode * 0.25f));
					BatPart[0].Info.pVertex[a + b + 3].y -=
						(BatPart[0].Info.pVertex[a + b + 3].ny * addw * f * (1 + (float)mode * 0.25f));
						BatPart[0].Info.pVertex[a + b + 3].z -=
						(BatPart[0].Info.pVertex[a + b + 3].nz * addw * f * (1 + (float)mode * 0.25f));
				}
			}
		}
		if(anime_flag == 2){
			BatPart[0].SetRotationMode(0);
			BatPart[0].SetMoveRotation(0,0);
			material.SetDeffuseColor(192,162,0,255 - (int)((float)t * (255.0f / 1000.0f)));
			f = 0.10f;
			for(a = 0;a < BatPart[0].Info.VertexCount / 2;a += 3){
				for(b = 0;b < 3;b ++){
					BatPart[0].Info.pVertex[a + b].x +=
						(BatPart[0].Info.pVertex[a].nx * addw * f);
					BatPart[0].Info.pVertex[a + b].y +=
						(BatPart[0].Info.pVertex[a].ny * addw * f);
					BatPart[0].Info.pVertex[a + b].z +=
						(BatPart[0].Info.pVertex[a].nz * addw * f);
				}
			}
			for(;a < BatPart[0].Info.VertexCount;a += 3){
				for(b = 0;b < 3;b ++){
					BatPart[0].Info.pVertex[a + b + 3].x -=
						(BatPart[0].Info.pVertex[a].nx * addw * f);
					BatPart[0].Info.pVertex[a + b + 3].y -=
						(BatPart[0].Info.pVertex[a].ny * addw * f);
					BatPart[0].Info.pVertex[a + b + 3].z -=
						(BatPart[0].Info.pVertex[a].nz * addw * f);
				}
			}
		}

		if(anime3d == 0 && anime_flag == 2 && let.Get() > 1000){
			flag = 0;
		}

crdataEnableRec(0);
		crbatDrawScene();

		if(eid3d->Begin()){
			eid3d->BeginAlphaBlend();
			crbatDraw_SetViewport(0);
			crbatDraw_SetMatrix(0);
			eid3d->SetMaterial(&material);
			eid3d->SetTexture(NULL);

			BatPart[0].MoveFrame((float)addw);
			eid3d->SetDrawMode(EID3D_DRAWMODE_CULLCW);
			if(anime3d == 0 && anime_flag <= 1){
				BatPart[0].Draw(BatPart[0].Info.VertexCount / 2);
			} else {
				BatPart[0].Draw();
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
	material.Release();

	BatPart[0].Release();
}

//---“y
CRBATANIME_API void crbatDoAnime_MagicTsuchi2(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,
										   int red,int green,int blue,int mode)
{
	eiTime let;
	int AddWorld = 0,flag,begin_anime = 0;
	int a,b,anime3d = 0;
	float dis = 0;
	CrBattleCharacter *pDstChara = pDamageInfo->pList[0];

	eiD3DMaterial material[2];
	float addw = 0;

	material[0].Create();
	material[0].SetDeffuseColor(red,green,blue,127);
	material[0].SetEmissiveColor(red / 4,green / 4,blue / 4,127);
	material[0].Set();
	material[1].Create();
	material[1].SetDeffuseColor(red / 3,green / 3,blue / 3,127);
	material[1].SetEmissiveColor(red / 8,green / 8,blue / 8,127);
	material[1].Set();

	eiD3DParticle_SetG(-1.00f);

	int count = 2;
	for(a = 0;a < count;a ++){
		BatPart[a].CreateRandomTriangle(
			1.00f,0.15f,
			150 * (mode + 1));//150
		BatPart[a].SetWeight(0);
		if(a == 0){
			BatPart[a].SetWeight(1);
		}
		BatPart[a].SetWorldPos(
			(float)(pDstChara->GetFieldX()),
			0.0f,
			(float)(pDstChara->GetFieldY())
		);
		BatPart[a].SetRotationMode(1);
		BatPart[a].SetMoveSpeed(0.0f);
		if(a == 0)
			BatPart[a].SetMoveRotation(0,-0.15f);
		else
			BatPart[a].SetMoveRotation(0,0.15f);
		BatPart[a].SetMoveVectorXYZ(
			0.0f,1.0f,0.0f
		);
	}

	let.Reset();
	flag = 1;
	addw = 0;

	int c,sound = 0;
	int anime_flag = 0,t;
	float f = 0.005f,g,speed = 0.03f;
	crsoundPlay(49);
	while(flag){
		et->Reset();
		t = let.Get();

		switch(anime3d){
		case 0:
			if(t > 500){
				if(!sound){
					crsoundPlay(48);
					sound = 1;
				}
			}
			if(anime_flag == 0){
				material[0].SetDeffuseColor(red,green,blue,255 - (int)((float)let.Get() * 127.0f / 2000.0f));
				material[1].SetDeffuseColor(red / 3,green / 3,blue / 3,
					(mode * 17) - (int)((float)let.Get() * ((mode * 17) / 2) / 2000.0f));
				f = 0.010f;
				g = 0.010f + (float)((float)mode * 0.005f);
				c = 0;

#ifdef NORMALIZE_CALC
				f = 0.020f;
				g = 0.020f + (float)((float)mode * 0.005f);
#endif
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
				c = 1;
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

			if(anime3d == 0 && anime_flag == 0 && let.Get() > 1500){
				flag = 0;
			}
			break;
		}
crdataEnableRec(0);
		crbatDrawScene();

		if(eid3d->Begin()){
			eid3d->BeginAlphaBlend();
			crbatDraw_SetViewport(0);
			crbatDraw_SetMatrix(0);
			eid3d->SetTexture(NULL);

//			eid3d->SetDrawMode(EID3D_DRAWMODE_CULLCW);
			crbatSetAddAlpha();
//			eid3d->lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_ONE);
			for(c = 0;c < count;c ++){
				eid3d->SetMaterial(&material[0]);
				BatPart[c].MoveFrame((float)addw);
				BatPart[c].Draw();
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

	BatPart[0].Release();
	BatPart[1].Release();
}


//---“y
CRBATANIME_API void crbatDoAnime_MagicEarthQuake(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,int mode)
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
	pDstChara[a] = NULL;
	dst_count = 1;

	eiD3DMaterial material;
	material.Create();
	material.SetDeffuseColor(255,127,127,127);
	material.SetEmissiveColor(96,0,0,127);
	material.Set();

	int tri_count = 1000;
	float r = 0.25f,angle,hangle;

	//----------------------------------
	for(a = 0;a < tri_count;a ++){
		angle = ANGLE(eiRnd(360));
		hangle = ANGLE(eiRnd(360));
		BatPart[a].CreateTriangle(
			0.0,0.0,0.0,
			(float)(r * cos(angle)),
			(float)(r * cos(hangle)),
			(float)(r * sin(angle)),
			(float)(r * cos(angle + ANGLE(60))),
			(float)(r * cos(hangle + ANGLE(60))),
			(float)(r * sin(angle + ANGLE(60)))
			);

		BatPart[a].SetMoveRotation(0,0);
		BatPart[a].SetWeight(1);
		BatPart[a].SetRotationMode(0);

		BatPart[a].SetWorldPos(
			(float)((float)(eiRnd(1100) + 50) / 100.0f),
			(float)(-0.5f - (float)(eiRnd(100) / 100.0f)),
			(float)((float)(eiRnd(1100) + 50)/ 100.0f)
			);
		BatPart[a].SetMoveVectorXYZ(
			(float)((float)(eiRnd(200) - 100) / 1000),
			(float)((float)(eiRnd(100) + 10) / 100),
			(float)((float)(eiRnd(200) - 100) / 1000)
		);
		BatPart[a].SetMoveSpeed((float)eiRnd(1000) / 10000.0f);
	}

	for(a = tri_count;a < tri_count + 2;a ++){
		if(a == tri_count){
			BatPart[a].CreateTriangle(
				- 0.0f,0.01f,-0.0f,
				12.0f,0.001f,-0.0f,
				-0.0f,0.01f,12.0f);
		} else {
			BatPart[a].CreateTriangle(
				12.0f,0.01f,-0.0f,
				-0.0f,0.001f,12.0f,
				12.0f,0.01f,12.0f);
		}

		BatPart[a].SetWeight(0);
		BatPart[a].SetWorldPos(
			0,0,0
		);
		BatPart[a].SetRotationMode(0);
		BatPart[a].SetMoveSpeed(0.0f);
		BatPart[a].SetMoveRotation(0,0);
		BatPart[a].SetMoveVectorXYZ(
			0.0f,1.0f,0.0f
		);
	}

	float addw = 0;

	eiD3DParticle_SetG(-0.010f);

	let.Reset();
	let2.Reset();
	flag = 1;
	addw = 0;

	int sound = 0,anime_flag = 0,t,show_ver = 1;
	float f = 0.002f,speed = 0.03f,addt = 0;
	crsoundPlay(CRSOUND_FIRE2);

	anime_flag = 0;
//	crsoundPlay(CRSOUND_EARTHQUAKE);
	while(flag){
		et->Reset();
		t = let.Get();

		if(anime_flag == 0){
			material.SetDeffuseColor(160,255,0,(int)((float)t * (255.0f / 1000.0f)));
		}
		if(anime_flag == 2){
			int dm = let.Get();

			if(dm < 2000)
				dm = 100;
			else
				dm = (3200 - dm) / 10;
			material.SetDeffuseColor(160,255,0,255 - (int)((float)t * (128.0f / 3000.0f)));
			//---—h‚ç‚·
			crbatDraw_SetWorldMatrixDelta(
				(float)eiRnd(dm) / 200.0f,
				(float)eiRnd(dm) / 200.0f,
				(float)eiRnd(dm) / 200.0f);
		}

		if(anime_flag == 0 && let.Get() > 1000){
			anime_flag = 2;
			let.Reset();
			crsoundPlay(CRSOUND_EARTHQUAKE);
		}
		if(anime_flag == 2 && let.Get() > 3000){
			flag = 0;
		}

		crbatClearDrawingList();
		crbatAddDrawingListAll();

crdataEnableRec(0);
		crbatDrawScene();

		if(anime_flag <= 2){
			if(eid3d->Begin()){
				eid3d->BeginAlphaBlend();
				crbatDraw_SetViewport(0);
				crbatDraw_SetMatrix(0);
				eid3d->SetMaterial(&material);
				eid3d->SetTexture(NULL);

				if(anime_flag == 2){
					for(c = 0;c < tri_count;c ++){
						BatPart[c].MoveFrame((float)addw);
						if(BatPart[c].Info.wy > 6.0f)
							BatPart[c].Info.wy = 0;
					}
				}
				eid3d->SetDrawMode(EID3D_DRAWMODE_CULLNONE);
				crbatSetAddAlpha();

				if(anime_flag == 2){
					for(c = 0;c < tri_count;c ++){
						BatPart[c].Draw();
					}
				} else {
					BatPart[tri_count].Draw();
					BatPart[tri_count + 1].Draw();
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

	crbatDraw_SetWorldMatrixDelta(0,0,0);

	crbatClearDrawingList();
	crbatAddDrawingListAll();

	material.Release();
	for(a = 0;a < tri_count + 2;a ++){
		BatPart[a].Release();
	}
}



//---“y
CRBATANIME_API void crbatDoAnime_MagicGroundCross(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,int mode)
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
	pDstChara[a] = NULL;
	dst_count = 1;

	eiD3DMaterial material;
	material.Create();
	material.SetDeffuseColor(255,127,127,127);
	material.SetEmissiveColor(96,0,0,127);
	material.Set();

	int tri_count = 1000;
	float r = 0.25f,angle,hangle;

	//----------------------------------
	for(a = 0;a < tri_count;a ++){
		angle = ANGLE(eiRnd(360));
		hangle = ANGLE(eiRnd(360));
		BatPart[a].CreateTriangle(
			0.0,0.0,0.0,
			(float)(r * cos(angle)),
			(float)(r * cos(hangle)),
			(float)(r * sin(angle)),
			(float)(r * cos(angle + ANGLE(60))),
			(float)(r * cos(hangle + ANGLE(60))),
			(float)(r * sin(angle + ANGLE(60)))
			);

		BatPart[a].SetMoveRotation(0,0);
		BatPart[a].SetWeight(1);
		BatPart[a].SetRotationMode(0);

		BatPart[a].SetWorldPos(
			(float)((float)(eiRnd(1100) + 50) / 100.0f),
			(float)(-0.5f - (float)(eiRnd(100) / 100.0f)),
			(float)((float)(eiRnd(1100) + 50)/ 100.0f)
			);
		BatPart[a].SetMoveVectorXYZ(
			(float)((float)(eiRnd(200) - 100) / 1000),
			(float)((float)(eiRnd(100) + 10) / 100),
			(float)((float)(eiRnd(200) - 100) / 1000)
		);
		BatPart[a].SetMoveSpeed((float)eiRnd(1000) / 10000.0f);
	}

	for(a = tri_count;a < tri_count + 2;a ++){
		if(a == tri_count){
			BatPart[a].CreateTriangle(
				- 0.0f,0.01f,-0.0f,
				12.0f,0.001f,-0.0f,
				-0.0f,0.01f,12.0f);
		} else {
			BatPart[a].CreateTriangle(
				12.0f,0.01f,-0.0f,
				-0.0f,0.001f,12.0f,
				12.0f,0.01f,12.0f);
		}

		BatPart[a].SetWeight(0);
		BatPart[a].SetWorldPos(
			0,0,0
		);
		BatPart[a].SetRotationMode(0);
		BatPart[a].SetMoveSpeed(0.0f);
		BatPart[a].SetMoveRotation(0,0);
		BatPart[a].SetMoveVectorXYZ(
			0.0f,1.0f,0.0f
		);
	}

	float addw = 0;

	eiD3DParticle_SetG(-0.010f);

	let.Reset();
	let2.Reset();
	flag = 1;
	addw = 0;

	int sound = 0,anime_flag = 0,t,show_ver = 1;
	float f = 0.002f,speed = 0.03f,addt = 0,
		cx = (float)pChara->GetFieldX(),cy = (float)pChara->GetFieldY();
	crsoundPlay(CRSOUND_FIRE2);

	anime_flag = 2;
	crsoundPlay(CRSOUND_EARTHQUAKE);
	while(flag){
		et->Reset();
		t = let.Get();

		if(anime_flag == 0){
			material.SetDeffuseColor(160,255,255,(int)((float)t * (255.0f / 1000.0f)));
		}
		if(anime_flag == 2){
			int dm = let.Get();

			if(dm < 2000)
				dm = 100;
			else
				dm = (3200 - dm) / 10;
			material.SetDeffuseColor(160,255,255,255 - (int)((float)t * (128.0f / 3000.0f)));
			//---—h‚ç‚·
			crbatDraw_SetWorldMatrixDelta(
				(float)eiRnd(dm) / 200.0f,
				(float)eiRnd(dm) / 200.0f,
				(float)eiRnd(dm) / 200.0f);
		}

		if(anime_flag == 0 && let.Get() > 1000){
			anime_flag = 2;
			let.Reset();
		}
		if(anime_flag == 2 && let.Get() > 3000){
			flag = 0;
		}

		crbatClearDrawingList();
		crbatAddDrawingListAll();

crdataEnableRec(0);
		crbatDrawScene();

		if(anime_flag <= 2){
			if(eid3d->Begin()){
				eid3d->BeginAlphaBlend();
				crbatDraw_SetViewport(0);
				crbatDraw_SetMatrix(0);
				eid3d->SetMaterial(&material);
				eid3d->SetTexture(NULL);

				eid3d->SetDrawMode(EID3D_DRAWMODE_CULLNONE);
				crbatSetAddAlpha();

				if(anime_flag == 2){
					for(c = 0;c < tri_count;c ++){
						if((BatPart[c].Info.wx - cx) * (BatPart[c].Info.wx - cx)
							+ (BatPart[c].Info.wz - cy) * (BatPart[c].Info.wz - cy)
							< (float)t * 0.05f){
							BatPart[c].MoveFrame((float)addw);
							if(BatPart[c].Info.wy > 6.0f)
								BatPart[c].Info.wy = 0;

							BatPart[c].Draw();
						}
					}
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

	crbatDraw_SetWorldMatrixDelta(0,0,0);

	crbatClearDrawingList();
	crbatAddDrawingListAll();

	material.Release();
	for(a = 0;a < tri_count + 2;a ++){
		BatPart[a].Release();
	}
}

