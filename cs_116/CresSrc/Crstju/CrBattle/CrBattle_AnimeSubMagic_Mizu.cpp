CRBATANIME_API void crbatDoAnime_MagicWater(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,int mode)
{
	eiTime let;
	int AddWorld = 0,flag,begin_anime = 0;
	int a,anime3d = 0;
	float dis = 0;
	CrBattleCharacter *pDstChara = pDamageInfo->pList[0];

	eiD3DMaterial material;
	float addw = 0;

	material.Create();
	material.SetDeffuseColor(127,255,255,192);
	material.SetEmissiveColor(0,32,64,127);
	material.Set();

	eiD3DParticle_SetG(0.00f);

	int x,y,dst_x,dst_y;
	float Width = 3.0,fWidth = (float)Width / 32.0f;
	dst_x = pDstChara->GetFieldX();
	dst_y = pDstChara->GetFieldY();
	//---範囲フィールドを計算
	crbatGetTargetChara(pChara,pDstChara,pChara->Command.Range,NULL);
	//---範囲表示
	int ver_count = 0;
	for(y = 0;y < BATTLEFIELD_MAX_Y;y ++){
		for(x = 0;x < BATTLEFIELD_MAX_X;x ++){
			if(TargetField[x][y]){
				memset(&BatPart[ver_count].Info,0,sizeof(BatPart[ver_count].Info));
				memset(&BatPart[ver_count + 1].Info,0,sizeof(BatPart[ver_count].Info));
				BatPart[ver_count].CreateTriangle(
					0.0f,0.01f,0.0f,
					1.0f,0.01f,0.0f,
					0.0f,0.01f,1.0f);

				BatPart[ver_count + 1].CreateTriangle(
					1.0f,0.01f,0.0f,
					1.0f,0.01f,1.0f,
					0.0f,0.01f,1.0f);

				for(a = 0;a < 2;a ++){
					BatPart[ver_count + a].SetWorldPos(
						(float)x,
						0.0f,
						(float)y
					);
					BatPart[ver_count + a].SetRotationMode(1);
					BatPart[ver_count + a].SetMoveSpeed(0.01f);
					BatPart[ver_count + a].SetMoveVectorXYZ(
						0.0f,
						1.0f,
						0.0f
					);
					BatPart[ver_count + a].SetMoveRotation(
						(float)eiRnd(100) / 5000.0f,
						(float)eiRnd(100) / 5000.0f);
				}
				ver_count += 2;
			}
		}
	}


	let.Reset();
	flag = 1;
	addw = 0;

	int anime_flag = 0,t;
	float f = 0.005f,speed = 0.01f;

	crsoundPlay(CRSOUND_ICE1);
	while(flag){
		et->Reset();
		t = let.Get();

		switch(anime3d){
		case 0:
			if(anime_flag == 0 && let.Get() > 750){
				let.Reset();
				anime_flag = 1;
				crsoundPlay(CRSOUND_ICE2);
			}
			if(anime_flag == 1 && let.Get() > 1500){
				flag = 0;
			}
			break;
		}
		if(anime_flag == 0){
			material.SetDeffuseColor(127,255,255,(int)((float)let.Get() * 192.0f / 750.0f));
		} else {
			material.SetDeffuseColor(127,255,255,192);
		}

crdataEnableRec(0);
		crbatDrawScene();

		if(eid3d->Begin()){
			eid3d->BeginAlphaBlend();
			crbatDraw_SetViewport(0);
			crbatDraw_SetMatrix(0);
			eid3d->SetMaterial(&material);
			eid3d->SetTexture(NULL);
//			eid3d->lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_ONE);

			eid3d->SetDrawMode(EID3D_DRAWMODE_CULLCW);

			speed = 0.01f + (float)let.Get() * 0.00003f;
			for(a = 0;a < ver_count;a ++){
				if(anime_flag == 1){
					BatPart[a].SetMoveSpeed(speed);
					BatPart[a].MoveFrame((float)addw);
				}
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
	material.Release();

	for(a = 0;a < ver_count;a ++){
		BatPart[a].Release();
	}
}


CRBATANIME_API void crbatDoAnime_MagicWater2(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo)
{
	eiTime let,let2;
	int AddWorld = 0,flag,begin_anime = 0;
	int a,b,anime3d = 0;
	float dis = 0;
	CrBattleCharacter *pDstChara = pDamageInfo->pList[0];

	eiD3DMaterial material;
	float addw = 0;

	material.Create();
	material.SetDeffuseColor(127,255,255,192);
	material.SetEmissiveColor(0,32,64,127);
	material.Set();


	int x,y,dst_x,dst_y;
	float Width = 3.0,fWidth = (float)Width / 32.0f;
	dst_x = pDstChara->GetFieldX();
	dst_y = pDstChara->GetFieldY();
	//---範囲フィールドを計算
	crbatGetTargetChara(pChara,pDstChara,pChara->Command.Range,NULL);
	//---範囲表示
	int ver_count = 0;
	for(y = 0;y < BATTLEFIELD_MAX_Y;y ++){
		for(x = 0;x < BATTLEFIELD_MAX_X;x ++){
			if(TargetField[x][y]){
				memset(&BatPart[ver_count].Info,0,sizeof(BatPart[ver_count].Info));
				memset(&BatPart[ver_count + 1].Info,0,sizeof(BatPart[ver_count].Info));
				BatPart[ver_count].CreateTriangle(
					0.0f,0.01f,0.0f,
					1.0f,0.01f,0.0f,
					0.0f,0.01f,1.0f);

				BatPart[ver_count + 1].CreateTriangle(
					1.0f,0.01f,0.0f,
					1.0f,0.01f,1.0f,
					0.0f,0.01f,1.0f);

				for(a = 0;a < 2;a ++){
					BatPart[ver_count + a].SetWorldPos(
						(float)x,
						0.0f,
						(float)y
					);
					BatPart[ver_count + a].SetRotationMode(0);
					BatPart[ver_count + a].SetMoveSpeed(0.01f);
					BatPart[ver_count + a].SetMoveVectorXYZ(
						0.0f,
						0.15f,
						0.0f
					);
					BatPart[ver_count + a].SetMoveRotation(0,0);
				}
				ver_count += 2;
			}
		}
	}

	int tri = ver_count;

	BatPart[tri].CreateRandomTriangle(
		2.00f,0.400f,4000);
	BatPart[tri].SetRotationMode(0);
	BatPart[tri].SetWeight(1);
	BatPart[tri].SetMoveSpeed(0.01f);
	BatPart[tri].SetMoveVectorXYZ(0,-1.0f,0);
	BatPart[tri].SetWorldPos(6,0,6);
	eiD3DParticle_SetG(0.050f);
	eiD3DParticle_GlobalMoveSpeed(0.1f);

	//--------------------------------------------
	EIMEMORY hmem = eiAllocMemory(sizeof(float) * BatPart[tri].Info.VertexCount + 10000);
	float *pMoveData = (float *)eiLockMemory(hmem);
	int c = tri;
	float div;
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

	int anime_flag = 0,t;
	float f = 0.005f,g,speed = 0.01f;

	crsoundPlay(50);
	while(flag){
		let2.Reset();
		t = let.Get();

		switch(anime3d){
		case 0:
			if(anime_flag == 0 && let.Get() > 750){
				let.Reset();
				anime_flag = 1;
				crsoundPlay(51);
			}
			if(anime_flag == 1 && let.Get() > 1000){
				let.Reset();
				anime_flag = 2;
/*				for(a = 0;a < ver_count;a ++){
					BatPart[a].SetMoveVectorXYZ(
						0.0f,
						0.0f,
						0.0f);
				}*/
			}
			if(anime_flag == 2 && let.Get() > 3000){
				flag = 0;
			}
			break;
		}
		if(anime_flag == 0){
			material.SetDeffuseColor(127,255,255,(int)((float)let.Get() * 192.0f / 750.0f));
		} else {
			material.SetDeffuseColor(127,255,255,192);
		}

crdataEnableRec(0);
		crbatDrawScene();

		if(eid3d->Begin()){
			eid3d->BeginAlphaBlend();
			crbatDraw_SetViewport(0);
			crbatDraw_SetMatrix(0);
			eid3d->SetMaterial(&material);
			eid3d->SetTexture(NULL);

			eid3d->SetDrawMode(EID3D_DRAWMODE_CULLCW);

			if(anime_flag == 2){
				int c = tri;
				f = 0.0025f;
				g = 0.0050f;

				for(a = 0;a < BatPart[c].Info.VertexCount;a += 3){	
					for(b = 0;b < 3;b ++){
/*						BatPart[c].Info.pVertex[a + b].x +=
							(BatPart[c].Info.pVertex[a].nx * addw * g);
						BatPart[c].Info.pVertex[a + b].y +=
							((BatPart[c].Info.pVertex[a].ny) * addw * f);
						BatPart[c].Info.pVertex[a + b].z +=
							(BatPart[c].Info.pVertex[a].nz * addw * g);
*/
						BatPart[c].Info.pVertex[a + b].x +=
							(pMoveData[a] * addw * g);
						BatPart[c].Info.pVertex[a + b].y +=
							(pMoveData[a + 1] * addw * f);
						BatPart[c].Info.pVertex[a + b].z +=
							(pMoveData[a + 2] * addw * g);
					}
				}
				BatPart[tri].MoveFrame((float)addw);

				crbatSetAddAlpha();
				BatPart[tri].Draw();
			}
			speed = 0.01f + (float)let.Get() * 0.00003f;
			for(a = 0;a < ver_count;a ++){
				if(anime_flag){
					BatPart[a].SetMoveSpeed(speed);
					BatPart[a].MoveFrame((float)addw);
				}
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

		addw = (float)let2.Get() / 10.0f;
	}

	eiUnlockMemory(hmem);
	eiFreeMemory(hmem);

	material.Release();

	for(a = 0;a < ver_count + 1;a ++){
		BatPart[a].Release();
	}
}


