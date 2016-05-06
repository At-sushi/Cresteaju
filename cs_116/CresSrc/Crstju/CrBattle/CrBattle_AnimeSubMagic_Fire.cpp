CRBATANIME_API void crbatDoAnime_MagicFireBall(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo)
{
	eiTime let;
	int AddWorld = 0,flag,begin_anime = 0;
	int a,b,anime3d = 0;
	float dis = 0;
	CrBattleCharacter *pDstChara = pDamageInfo->pList[0];

	eiD3DMaterial material;
	float addw = 0;
/*	eiD3DLight light[2];

	for(a = 0;a < 2;a ++){
		if(a == 0){
			light[a].Create(D3DLIGHT_DIRECTIONAL);
			light[a].SetDirection(
				(float)(pDstChara->GetFieldX() - pChara->GetFieldX()),
				1.0f,
				(float)(pDstChara->GetFieldY() - pChara->GetFieldY())
			);
			light[a].SetColor(255,255,255,255);
		} else {
			light[a].Create();
			light[a].SetColor(20,20,20,255);
		}
		light[a].SetPos(
			(float)pChara->GetFieldX(),
			1.0f,
			(float)pChara->GetFieldY());
		light[a].SetAttenuation(0.3f,0.2f,0.9f);
		if(eid3d->Begin()){
			eid3d->SetLight(&light[a],a);
			eid3d->End();
		}
	}
*/
	material.Create();
	material.SetDeffuseColor(255,32,0,127);
	material.SetEmissiveColor(64,0,0,127);
	material.Set();

	eiD3DParticle_SetG(0.00f);

	BatPart[0].CreateSphere(0.05f,12,12);
	BatPart[0].SetMoveRotation(0,0);
	BatPart[0].SetWeight(1);
	BatPart[0].SetWorldPos(
		(float)(pChara->GetFieldX() + 0.3 * cos(pChara->GetAngle())),
		(float)(pChara->GetFieldZ() + 0.7),
		(float)(pChara->GetFieldY() + 0.3 * sin(pChara->GetAngle()))
	);
	BatPart[0].SetRotationMode(0);
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
	float dx,dy,pdist = 0,dist = 0;
	while(flag){
		et->Reset();
		t = let.Get();

		switch(anime3d){
		case 0:
			dx = (float)BatPart[0].Info.wx - (float)pDstChara->GetFieldX();
			dy = (float)BatPart[0].Info.wz - (float)pDstChara->GetFieldY();
			dist = (float)dx * dx + (float)dy * dy;
			if(dist < 1.0f
				|| pdist < dist || let.Get() > 2000){
				anime_flag = 2;
				eiD3DParticle_SetG(0.02f);
				let.Reset();
			}
			pdist = dist; 

			if(anime_flag >= 1){
				BatPart[0].SetMoveSpeed(speed);
				speed = (float)(0.04f + ((float)let.Get() * 0.00005));
			}
			if(anime_flag == 0){
				if(let.Get() > 500){
					anime_flag = 1;
					dx = (float)BatPart[0].Info.wx - (float)pDstChara->GetFieldX();
					dy = (float)BatPart[0].Info.wz - (float)pDstChara->GetFieldY();
					pdist = (float)dx * dx + (float)dy * dy;
				}
				material.SetDeffuseColor(255,32,0,(int)( (float)t * 192.0f / 500.0f) );
				f = 0.006f;
				for(a = 0;a < BatPart[0].Info.VertexCount / 2;a += 3){
					for(b = 0;b < 3;b ++){
						BatPart[0].Info.pVertex[a + b].x +=
							(BatPart[0].Info.pVertex[a + b].nx * addw * f);
						BatPart[0].Info.pVertex[a + b].y +=
							(BatPart[0].Info.pVertex[a + b].ny * addw * f);
						BatPart[0].Info.pVertex[a + b].z +=
							(BatPart[0].Info.pVertex[a + b].nz * addw * f);

					}
				}
				for(;a < BatPart[0].Info.VertexCount;a += 3){
					for(b = 0;b < 3;b ++){
						BatPart[0].Info.pVertex[a + b + 3].x -=
							(BatPart[0].Info.pVertex[a + b + 3].nx * addw * f);
						BatPart[0].Info.pVertex[a + b + 3].y -=
							(BatPart[0].Info.pVertex[a + b + 3].ny * addw * f);
						BatPart[0].Info.pVertex[a + b + 3].z -=
							(BatPart[0].Info.pVertex[a + b + 3].nz * addw * f);
					}
				}
			}
			if(anime_flag == 2){
				material.SetDeffuseColor(255,32,0,192 - (int)((float)t * (192.0f / 1000.0f)));
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
			break;
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
			eid3d->SetTexture(NULL);
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
/*	if(eid3d->Begin()){
		eid3d->SetLight(NULL,0);
		eid3d->SetLight(NULL,1);
		eid3d->End();
	}
	light[1].Release();
	light[0].Release();*/
	material.Release();

	BatPart[0].Release();
}

//---ファイアーボール
CRBATANIME_API void crbatDoAnime_MagicFire2(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,int mode)
{
	eiTime let,let2;
	int AddWorld = 0,flag,begin_anime = 0;
	int a,b,c,anime3d = 0,tex_number = 0;
	float dis = 0;
	CrBattleCharacter *pDstChara[16];
	int dst_count;

	for(a = 0,dst_count = 0;pDamageInfo->pList[a] != NULL;a ++){
		pDstChara[a] = pDamageInfo->pList[a];
		dst_count ++;
	}
	pDstChara[a] = NULL;

	eiTextureCell tex[4];
	float range = 0,dr;

	char s[80];
	for(a = 0;a < 4;a ++){
		sprintf(s,"%sFireBall%d.acf",CR_DATADIR4,a + 1);
		tex[a].ReadFile(s,CR_DATAFILE4,crdataGetFileMode());
		tex[a].Init(16);
		tex[a].Load();
	}

	eiD3DMaterial material;
	material.Create();
	material.SetDeffuseColor(255,127,127,127);
	material.SetEmissiveColor(96,0,0,127);
	material.Set();

	if(mode == 0)
		dr = 0.3f;
	else
		dr = -1.6f;

	pBtObject[0].CreateTLVertexRect(48,224);
	pBtObject[0].SetPos(
		(float)(pChara->GetFieldX() + 0.3 * cos(pChara->GetAngle())),
		(float)(pChara->GetFieldY() + 0.3 * sin(pChara->GetAngle()))
		,
		mode == 0 ?
		(float)(pChara->GetFieldZ() + 0.7) :
		(float)(pChara->GetFieldZ() + 0.5)
		);
	pBtObject[0].SetDrawMode(1);
	pBtObject[0].SetTexture(&tex[0]);
	pBtObject[0].SetMoveVectorXYZ(
		(float)(pDstChara[0]->GetFieldX() - pChara->GetFieldX()),
		(float)(pDstChara[0]->GetFieldY() - pChara->GetFieldY()),
		(float)(pDstChara[0]->GetFieldZ() - pChara->GetFieldZ())
	);
	pBtObject[0].SetMoveSpeed(0);
	pBtObject[0].SetAlphaMode(1);
	//----------------------------------
	for(a = 0;a < dst_count;a ++){
		BatPart[a].CreateSphere(0.4f,12,12);
//		BatPart[a].CreateSphere(range,12,12);
		BatPart[a].SetMoveRotation(0,0);
		BatPart[a].SetWeight(1);
		BatPart[a].SetRotationMode(0);
		BatPart[a].SetMoveSpeed(0.0f);
		BatPart[a].SetWorldPos(
			(float)(pChara->GetFieldX() + 0.3 * cos(pChara->GetAngle())),
			mode == 0 ?
			(float)(pChara->GetFieldZ() + 0.7) :
			(float)(pChara->GetFieldZ() + 0.5),
			(float)(pChara->GetFieldY() + 0.3 * sin(pChara->GetAngle()))
			);
		BatPart[a].SetMoveVectorXYZ(
			(float)(pDstChara[a]->GetFieldX() - pChara->GetFieldX()),
			(float)(pDstChara[a]->GetFieldZ() - pChara->GetFieldZ()),
			(float)(pDstChara[a]->GetFieldY() - pChara->GetFieldY())
		);
	}
	float addw = 0;

	eiD3DParticle_SetG(0.00f);

	let.Reset();
	let2.Reset();
	flag = 1;
	addw = 0;

	int sound = 0,anime_flag = 0,t,show_ver = 1;
	float f = 0.002f,speed = 0.03f,dx,dy,addt = 0,dist,pdist;
	crsoundPlay(CRSOUND_FIRE2);
	if(mode == 0){
		f = 0.002f;
		range = 0;
	} else if(mode == 1){
		f = 0.004f;
		range = 1.0f;
	}

	dx = (float)pBtObject[0].ObjectInfo.x - (float)pDstChara[0]->GetFieldX();
	dy = (float)pBtObject[0].ObjectInfo.y - (float)pDstChara[0]->GetFieldY();
	pdist = (float)dx * dx + (float)dy * dy;
	while(flag){
		et->Reset();
		t = let.Get();

		pBtObject[0].SetXRate(1 + range);
		pBtObject[0].SetYRate(1 + range);
		if(anime_flag == 0){
			pBtObject[0].SetXRate(f * t);
			pBtObject[0].SetYRate(f * t);
			if(let.Get() > 500){
				let.Reset();
				anime_flag = 1;
			}
		}
		if(anime_flag == 1){
			if(sound == 0){
				crsoundPlay(CRSOUND_FIRE1);
				sound = 1;
			}
			pBtObject[0].SetMoveSpeed(speed);
			speed = (float)(0.04f + ((float)let.Get() * 0.0005));
		}

		dx = (float)pBtObject[0].ObjectInfo.x - (float)pDstChara[0]->GetFieldX();
		dy = (float)pBtObject[0].ObjectInfo.y - (float)pDstChara[0]->GetFieldY();
		dist = (float)dx * dx + (float)dy * dy;
		if((dist < 1.0f || pdist < dist) && anime_flag == 1){
			crsoundPlay(CRSOUND_FIRE3);
			anime_flag = 2;
			addt = (float)let.Get();
			eiD3DParticle_SetG(0.02f);
			let.Reset();
			for(a = 0;a < dst_count;a ++){
				if(mode == 0){
					BatPart[a].SetWorldPos(
						(float)(pBtObject[0].ObjectInfo.x),
						(float)(pBtObject[0].ObjectInfo.z),
						(float)(pBtObject[0].ObjectInfo.y)
					);
				} else {
					BatPart[a].SetWorldPos(
						(float)(pDstChara[a]->GetFieldX() + dr * cos(pChara->GetAngle())),
						(float)(pDstChara[a]->GetFieldZ() + 0.1f),
						(float)(pDstChara[a]->GetFieldY() + dr * sin(pChara->GetAngle()))
					);
				}
			}
		}
		pdist = dist;

		//---めらめら
		if(let2.Get() > 50){
			if(++ tex_number >= 4)
				tex_number = 0;
			pBtObject[0].SetTexture(&tex[tex_number]);
			let2.Reset();
		}

		if(anime_flag == 2){
			speed = (float)(0.04f + ((float)(let.Get() + addt) * 0.0005));
			for(c = 0;c < dst_count;c ++){
				BatPart[c].SetMoveSpeed(speed);
			}
			material.SetDeffuseColor(255,64,0,192 - (int)((float)t * (192.0f / 1000.0f)));
			f = 0.10f;
			for(c = 0;c < dst_count;c ++){
				for(a = 0;a < BatPart[c].Info.VertexCount / 2;a += 3){
					for(b = 0;b < 3;b ++){
						BatPart[c].Info.pVertex[a + b].x +=
							(BatPart[c].Info.pVertex[a].nx * addw * f);
						BatPart[c].Info.pVertex[a + b].y +=
							(BatPart[c].Info.pVertex[a].ny * addw * f);
						BatPart[c].Info.pVertex[a + b].z +=
							(BatPart[c].Info.pVertex[a].nz * addw * f);
					}
				}
				for(;a < BatPart[c].Info.VertexCount;a += 3){
					for(b = 0;b < 3;b ++){
						BatPart[c].Info.pVertex[a + b + 3].x -=
							(BatPart[c].Info.pVertex[a].nx * addw * f);
						BatPart[c].Info.pVertex[a + b + 3].y -=
							(BatPart[c].Info.pVertex[a].ny * addw * f);
						BatPart[c].Info.pVertex[a + b + 3].z -=
							(BatPart[c].Info.pVertex[a].nz * addw * f);
					}
				}
			}
		}

		if(anime_flag == 2 && let.Get() > 1000){
			flag = 0;
		}
		
		pBtObject[0].Move(addw);

		crbatClearDrawingList();
		crbatAddDrawingListAll();
		if(anime_flag < 2){
			crbatAddDrawingList(&pBtObject[0],0,1);
		}

crdataEnableRec(0);
		crbatDrawScene();
		if(anime_flag == 2){
			if(eid3d->Begin()){
				eid3d->BeginAlphaBlend();
				crbatDraw_SetViewport(0);
				crbatDraw_SetMatrix(0);
				eid3d->SetMaterial(&material);
				eid3d->SetTexture(NULL);

				for(c = 0;c < dst_count;c ++){
					BatPart[c].MoveFrame((float)addw);
				}
				eid3d->SetDrawMode(EID3D_DRAWMODE_CULLCW);
//				eid3d->lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_ONE);
				crbatSetAddAlpha();
				if(anime3d == 0 && anime_flag <= 1){
					for(c = 0;c < dst_count;c ++){
						BatPart[c].Draw(BatPart[c].Info.VertexCount / 2);
					}
				} else {
					for(c = 0;c < dst_count;c ++){
						BatPart[c].Draw();
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

	crbatClearDrawingList();
	crbatAddDrawingListAll();

	for(a = 0;a < 4;a ++){
		tex[a].ReleaseTexture();
	}
	material.Release();
	for(a = 0;a < dst_count;a ++){
		BatPart[a].Release();
	}
}


//---フレアウェイヴ
CRBATANIME_API void crbatDoAnime_MagicFire3(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,int mode)
{
	eiTime let,let2;
	int AddWorld = 0,flag,begin_anime = 0;
	int a,b,c,anime3d = 0,tex_number = 0;
	float dis = 0;
	CrBattleCharacter *pDstChara[16];
	int dst_count;

	for(a = 0,dst_count = 0;pDamageInfo->pList[a] != NULL;a ++){
		pDstChara[a] = pDamageInfo->pList[a];
		dst_count ++;
	}
	pDstChara[a] = NULL;
	dst_count = 1;

	float range = 0,dr;

	eiD3DMaterial material;
	material.Create();
	material.SetDeffuseColor(255,127,127,127);
	material.SetEmissiveColor(96,0,0,127);
	material.Set();

	//----------------------------------
	for(a = 0;a < dst_count;a ++){
		BatPart[a].CreateSphere(0.4f,16,16);
//		BatPart[a].CreateSphere(range,12,12);
		BatPart[a].SetMoveRotation(0,0);
		BatPart[a].SetWeight(1);
		BatPart[a].SetRotationMode(0);
		BatPart[a].SetMoveSpeed(0.0f);
		if(mode == 0){
			dr = 0.3f;
		} else {
			dr = 0.6f;
		}
		BatPart[a].SetWorldPos(
			(float)(pChara->GetFieldX() + dr * cos(pChara->GetAngle())),
			mode == 0 ?
			(float)(pChara->GetFieldZ() + 0.7) :
			(float)(pChara->GetFieldZ() + 0.3),
			(float)(pChara->GetFieldY() + dr * sin(pChara->GetAngle()))
			);
		BatPart[a].SetMoveVectorXYZ(
			(float)(pDstChara[a]->GetFieldX() - pChara->GetFieldX()),
			(float)(pDstChara[a]->GetFieldZ() - pChara->GetFieldZ()),
			(float)(pDstChara[a]->GetFieldY() - pChara->GetFieldY())
		);
	}
	float addw = 0;

	eiD3DParticle_SetG(0.00f);

	let.Reset();
	let2.Reset();
	flag = 1;
	addw = 0;

	int sound = 0,anime_flag = 0,t,show_ver = 1;
	float f = 0.002f,speed = 0.03f,addt = 0;
	crsoundPlay(CRSOUND_FIRE2);
	if(mode == 0){
		f = 0.002f;
		range = 0;
	} else if(mode == 1){
		f = 0.004f;
		range = 1.0f;
	}

	anime_flag = 2;
	while(flag){
		et->Reset();
		t = let.Get();

		if(anime_flag == 1){
			if(sound == 0){
				crsoundPlay(CRSOUND_FIRE1);
				sound = 1;
			}
			speed = (float)(0.04f + ((float)let.Get() * 0.0005));
		}

		if(anime_flag == 2){
			speed = (float)(0.04f + ((float)(let.Get() + addt) * 0.0005));
			for(c = 0;c < dst_count;c ++){
				BatPart[c].SetMoveSpeed(speed);
			}
			material.SetDeffuseColor(255,64,0,192 - (int)((float)t * (192.0f / 1000.0f)));
			f = 0.05f;
			for(c = 0;c < dst_count;c ++){
				for(a = 0;a < BatPart[c].Info.VertexCount / 2;a += 3){
					for(b = 0;b < 3;b ++){
						BatPart[c].Info.pVertex[a + b].x +=
							(BatPart[c].Info.pVertex[a].nx * addw * f);
						BatPart[c].Info.pVertex[a + b].y +=
							(BatPart[c].Info.pVertex[a].ny * addw * f);
						BatPart[c].Info.pVertex[a + b].z +=
							(BatPart[c].Info.pVertex[a].nz * addw * f);
					}
				}
				for(;a < BatPart[c].Info.VertexCount;a += 3){
					for(b = 0;b < 3;b ++){
						BatPart[c].Info.pVertex[a + b + 3].x -=
							(BatPart[c].Info.pVertex[a].nx * addw * f);
						BatPart[c].Info.pVertex[a + b + 3].y -=
							(BatPart[c].Info.pVertex[a].ny * addw * f);
						BatPart[c].Info.pVertex[a + b + 3].z -=
							(BatPart[c].Info.pVertex[a].nz * addw * f);
					}
				}
			}
		}

		if(anime_flag == 2 && let.Get() > 3000){
			flag = 0;
		}

		crbatClearDrawingList();
		crbatAddDrawingListAll();

crdataEnableRec(0);
		crbatDrawScene();
		if(anime_flag == 2){
			if(eid3d->Begin()){
				eid3d->BeginAlphaBlend();
				crbatDraw_SetViewport(0);
				crbatDraw_SetMatrix(0);
				eid3d->SetMaterial(&material);
				eid3d->SetTexture(NULL);

				for(c = 0;c < dst_count;c ++){
					BatPart[c].MoveFrame((float)addw);
				}
				eid3d->SetDrawMode(EID3D_DRAWMODE_CULLCW);
//				eid3d->lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_ONE);
				crbatSetAddAlpha();
				if(anime3d == 0 && anime_flag <= 1){
					for(c = 0;c < dst_count;c ++){
						BatPart[c].Draw(BatPart[c].Info.VertexCount / 2);
					}
				} else {
					for(c = 0;c < dst_count;c ++){
						BatPart[c].Draw();
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

	crbatClearDrawingList();
	crbatAddDrawingListAll();

	material.Release();
	for(a = 0;a < dst_count;a ++){
		BatPart[a].Release();
	}
}

//---エクスプロージョン
CRBATANIME_API void crbatDoAnime_MagicFire4(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,int mode,int ambient)
{
	eiTime let,let2;
	int AddWorld = 0,flag,begin_anime = 0;
	int a,b = 0,c,anime3d = 0,tex_number = 0;
	float dis = 0;
	CrBattleCharacter *pDstChara[16];
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
	dst_count = 1;

	eiD3DMaterial material;
	material.Create();
	material.SetDeffuseColor(255,127,0,0);
	material.SetEmissiveColor(96,0,0,127);
	if(ambient)
		material.SetAmbientColor(255,127,0,0);
	material.Set();

	int tri_count = 0;
	if(mode == 0)
		tri_count = 1000;
	else if(mode == 1)
		tri_count = 250;

	float r = 0.3f,angle,hangle,
		speed = 0.1f;

	if(mode == 1){
		speed = 0.07f;
		r = 0.15f;
	}

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
			(float)(pDstChara[0]->GetFieldX()),
			(float)(0.0f),
			(float)(pDstChara[0]->GetFieldY())
			);
		BatPart[a].SetMoveVectorXYZ(
			(float)((float)(eiRnd(200) - 100) / 100),
			(float)((float)(eiRnd(100) + 10) / 100),
			(float)((float)(eiRnd(200) - 100) / 100)
		);
		BatPart[a].SetMoveSpeed(speed);
	}
	float addw = 0;

	eiD3DParticle_SetG(0.01f);

	let.Reset();
	let2.Reset();
	flag = 1;
	addw = 0;

	int sound = 0,anime_flag = 0,t,show_ver = 1;
	float f = 0.002f,addt = 0;
	crsoundPlay(CRSOUND_FIRE2);

	anime_flag = 2;
	while(flag){
		et->Reset();
		t = let.Get();

		if(anime_flag == 2){
			material.SetDeffuseColor(255,64,0,255 - (int)((float)t * (255.0f / 2000.0f)));
		}

		if(anime_flag == 2 && let.Get() > 2000){
			flag = 0;
		}

		crbatClearDrawingList();
		crbatAddDrawingListAll();

crdataEnableRec(0);
		crbatDrawScene();
		if(anime_flag == 2){
			if(eid3d->Begin()){
				eid3d->BeginAlphaBlend();
				crbatDraw_SetViewport(0);
				crbatDraw_SetMatrix(0);
				eid3d->SetMaterial(&material);
				eid3d->SetTexture(NULL);

				for(c = 0;c < tri_count;c ++){
					BatPart[c].MoveFrame((float)addw);
				}
				eid3d->SetDrawMode(EID3D_DRAWMODE_CULLCW);
				crbatSetAddAlpha();
//				eid3d->lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_ONE);

				for(c = 0;c < tri_count;c ++){
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

	crbatClearDrawingList();
	crbatAddDrawingListAll();

	material.Release();
	for(a = 0;a < tri_count;a ++){
		BatPart[a].Release();
	}
}

//---ライジングサン
CRBATANIME_API void crbatDoAnime_MagicFire5(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,int mode)
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

	eiTextureCell tex[4];
	float range = 0,dr;
	char s[80];
	for(a = 0;a < 4;a ++){
		sprintf(s,"%sFire%d.acf",CR_DATADIR4,a + 1);
		tex[a].ReadFile(s,CR_DATAFILE4,crdataGetFileMode());
		tex[a].Init(16);
		tex[a].Load();
	}

	eiD3DMaterial material;
	material.Create();
	material.SetDeffuseColor(255,127,0,0);
	material.SetEmissiveColor(96,0,0,127);
	material.Set();

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
			BatPart[a].CreateSphere(3.0f,60,60,0,3.1415f);
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
//	eistr s[100];
//	sprintf(s,"%d : %d",BatPart[a].Info.VertexCount,BatPart[a].Info.MemorySize);
//	eiMsgBox(s);
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
	float fast = 0,fast2 = 0;
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
			material.SetDeffuseColor(255,64,0,(int)((float)t * (255.0f / 2000.0f)));
		}
		if(anime_flag == 2){
			BatPart[0].SetMoveRotation(0,0);
			BatPart[1].SetMoveRotation(0,0);
//			f = 0.15f;
//			g = 0.17f;
			material.SetDeffuseColor(255,64,0,255 - (int)((float)t * (255.0f / 2000.0f)));
		}

		if(anime_flag == 0 && let.Get() > 2000){
//			flag = 0;
			crsoundPlay(CRSOUND_FIRE5);
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
				eid3d->SetMaterial(&material);
				eid3d->SetTexture(&tex[tex_number]);

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
				eid3d->SetMaterial(&material);
				eid3d->SetTexture(&tex[tex_number]);
					eid3d->SetDrawMode(EID3D_DRAWMODE_CULLNONE);
				crbatSetAddAlpha();

				c = 2;
//				f -= (t * 0.0000006f);
				f = -(t * 0.00006f);
				g = 0.07f;
				fast = addw * g;
				fast2 = addw * f;
				for(a = 0;a < BatPart[c].Info.VertexCount / 2;a += 3){	
					for(b = 0;b < 3;b ++){
/*						BatPart[c].Info.pVertex[a + b].x +=
							(BatPart[c].Info.pVertex[a].nx * fast);
						BatPart[c].Info.pVertex[a + b].y +=
							(BatPart[c].Info.pVertex[a].ny * fast2);
						BatPart[c].Info.pVertex[a + b].z +=
							(BatPart[c].Info.pVertex[a].nz * fast);*/

						BatPart[c].Info.pVertex[a + b].x +=
							(pMoveData[a + 0] * fast);
						BatPart[c].Info.pVertex[a + b].y +=
							(pMoveData[a + 1] * fast2);
						BatPart[c].Info.pVertex[a + b].z +=
							(pMoveData[a + 2] * fast);
					}
				}

				BatPart[2].MoveFrame((float)addw);
				BatPart[2].Draw(BatPart[2].Info.VertexCount / 2);

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
	material.Release();
	for(a = 0;a < 3;a ++){
		BatPart[a].Release();
	}
}

//---レイザーレイ
CRBATANIME_API void crbatDoAnime_MagicRay(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,
										  int red,int green,int blue,float range,int mode)
{
	eiTime let;
	int AddWorld = 0,flag,begin_anime = 0;
	int a,b,c,anime3d = 0,count = 8;
	float dis = 0,dx,dz;
	CrBattleCharacter *pDstChara = pDamageInfo->pList[0];

	eiD3DMaterial material[8];
	float addw = 0;

	if(crsysQuick()){
		//---クイック
		return;
	}

	for(a = 0;a < 8;a ++){
		material[a].Create();
		material[a].SetDeffuseColor(red,green,blue,192 / (a + 1));
		material[a].SetEmissiveColor(red / 4,green / 4,blue / 4,192 / (a + 1));
		material[a].Set();
	}

	eiD3DParticle_SetG(0.00f);
	dx = (float)(pDstChara->GetFieldX() - pChara->GetFieldX());
	dz = (float)(pDstChara->GetFieldY() - pChara->GetFieldY());

	for(c = 0;c < count;c ++){
		BatPart[c * 2].CreateTriangle(
			0,0,0,
			0,range,0,
			dx,0,dz);
		BatPart[c * 2 + 1].CreateTriangle(
			dx,range,dz,
			0,range,0,
			dx,0,dz);
		for(a = 0;a < 2;a ++){
			BatPart[c * 2 + a].SetMoveRotation(0,0);
			BatPart[c * 2 + a].SetWeight(1);
			BatPart[c * 2 + a].SetWorldPos(
				(float)(pChara->GetFieldX() + 0.3 * cos(pChara->GetAngle())),
				(float)(pChara->GetFieldZ() + 0.3),
				(float)(pChara->GetFieldY() + 0.3 * sin(pChara->GetAngle()))
			);
			BatPart[c * 2 + a].SetRotationMode(1);
			BatPart[c * 2 + a].SetMoveRotation(0,0);
			BatPart[c * 2 + a].SetMoveSpeed(0.08f - (float)(c * 0.008f));
			BatPart[c * 2 + a].SetMoveVectorXYZ(
				(float)(pDstChara->GetFieldX() - pChara->GetFieldX()),
				(float)(pDstChara->GetFieldZ() - pChara->GetFieldZ()),
				(float)(pDstChara->GetFieldY() - pChara->GetFieldY())
			);
		}
	}

	D3DVERTEX vertex[6 * 10];

	for(a = 0;a < 2;a ++){
		for(b = 0;b < 3;b ++){
			vertex[a * 3 + b] = BatPart[a].Info.Vertex[b];
			BatPart[a].Info.Vertex[b].x /= 1000.0f;
			BatPart[a].Info.Vertex[b].z /= 1000.0f;
		}
	}

	//---フィールド
	int x,y,dst_x,dst_y;
	float Width = 3.0,fWidth = (float)Width / 32.0f;
	dst_x = pDstChara->GetFieldX();
	dst_y = pDstChara->GetFieldY();
	//---範囲フィールドを計算
	crbatGetTargetChara(pChara,pDstChara,pChara->Command.Range,NULL);
	//---範囲表示
	int ver_count = count * 2;
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
					BatPart[ver_count + a].SetMoveSpeed(0);
					BatPart[ver_count + a].SetMoveVectorXYZ(
						0.0f,
						1.0f,
						0.0f
					);
					BatPart[ver_count + a].SetMoveRotation(0,0);
				}
				ver_count += 2;
			}
		}
	}

	let.Reset();
	flag = 1;
	addw = 0;

	int anime_flag = 0,t;
	float f = 0.005f,speed = 0.03f;

	switch(mode){
	case 0:
		crsoundPlay(CRSOUND_FIRE2);
		break;
	case 1:
		crsoundPlay(CRSOUND_ICE2);
		break;
	case 2:
		crsoundPlay(CRSOUND_BEAM);
		break;
	}

	while(flag){
		et->Reset();
		t = let.Get();

		if(anime_flag == 0){
			for(c = 0;c < count;c ++){
				for(a = 0;a < 2;a ++){
					for(b = 0;b < 3;b ++){
						BatPart[c * 2 + a].Info.Vertex[b].x +=
							(vertex[a * 3 + b].x *
							((float)((count - c - 1) * 0.0002 + 0.0005f) * t));
						BatPart[c * 2 + a].Info.Vertex[b].z +=
							(vertex[a * 3 + b].z *
							((float)((count - c - 1) * 0.0002 + 0.0005f) * t));
					}
				}
			}
			if(let.Get() > 1000){
				anime_flag = 1;
				flag = 0;
			}
		}
crdataEnableRec(0);
		crbatDrawScene();

		if(eid3d->Begin()){
			eid3d->BeginAlphaBlend();
			crbatDraw_SetViewport(0);
			crbatDraw_SetMatrix(0);

			eid3d->SetDrawMode(EID3D_DRAWMODE_CULLCW);
			crbatSetAddAlpha();
//			eid3d->lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_ONE);
			eid3d->SetMaterial(&material[3]);
			for(c = count * 2;c < ver_count;c ++){
				BatPart[c].Draw();
			}
			for(c = 0;c < count;c ++){
				eid3d->SetMaterial(&material[c]);
				eid3d->SetTexture(NULL);

				BatPart[c * 2].MoveFrame((float)addw);
				BatPart[c * 2 + 1].MoveFrame((float)addw);
				BatPart[c * 2].Draw();
				BatPart[c * 2 + 1].Draw();
			}

			eid3d->SetTexture(NULL);
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
	for(a = 0;a < 8;a ++){
		material[a].Release();
	}

	for(a = 0;a < 2 * count;a ++){
		BatPart[a].Release();
	}
}
