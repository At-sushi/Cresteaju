//---—‹
CRBATANIME_API void crbatDoAnime_MagicThunder(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,int mode)
{
	eiTime let,let2;
	int AddWorld = 0,flag,begin_anime = 0;
	int a,b,c,anime3d = 0,tex_number = 0,x_rate,y_rate;
	float dis = 0;
//	CrBattleCharacter *pDstChara = pDamageInfo->pList[0];
	eiTextureCell tex[4];

	CrBattleCharacter *pDstChara[16];
	int dst_count;

	for(a = 0,dst_count = 0;pDamageInfo->pList[a] != NULL;a ++){
		pDstChara[a] = pDamageInfo->pList[a];
		dst_count ++;
	}
	pDstChara[a] = NULL;


	if(mode == 0){
		x_rate = 1;
		y_rate = 8;
	} else {
		x_rate = 8;
		y_rate = 8;
	}

	char s[80];
	for(a = 0;a < 4;a ++){
		if(mode == 0){
			sprintf(s,"%sThunder%d.acf",CR_DATADIR4,a + 1);
		} else {
			sprintf(s,"%sBThunder%d.acf",CR_DATADIR4,a + 1);
		}
		tex[a].ReadFile(s,CR_DATAFILE4,crdataGetFileMode());
		tex[a].Init(16);
		tex[a].Load(0);
	}

	eiD3DMaterial material;
	material.Create();
	material.SetDeffuseColor(0,127,255,127);
	material.SetEmissiveColor(0,127,255,127);
	material.Set();

	a = 0;

	for(a = 0;a < dst_count;a ++){

		pBtObject[a].CreateTLVertexRect(32,224);
		pBtObject[a].SetPos(
			(float)(pDstChara[a]->GetFieldX() + 0.3 * cos(pDstChara[a]->GetAngle())),
			(float)(pDstChara[a]->GetFieldY() + 0.3 * sin(pDstChara[a]->GetAngle())),
			(float)(pDstChara[a]->GetFieldZ() + 2.6) //2.8
			);
		pBtObject[a].SetDrawMode(1);
		pBtObject[a].SetTexture(&tex[0]);
		pBtObject[a].SetMoveVectorXYZ(
			(float)(pDstChara[a]->GetFieldX() - pChara->GetFieldX()),
			(float)(pDstChara[a]->GetFieldY() - pChara->GetFieldY()),
			(float)(pDstChara[a]->GetFieldZ() - pChara->GetFieldZ())
		);
		pBtObject[a].SetMoveSpeed(0);
		pBtObject[a].SetXRate((float)x_rate);
		pBtObject[a].SetYRate((float)y_rate);
		pBtObject[a].SetAlphaMode(1);


	//----------------------------------
		if(mode < 2)
			continue;

		BatPart[a].CreateRandomTriangle(0.5f,0.25f,1000);
		BatPart[a].SetMoveRotation(0,0);
		BatPart[a].SetWeight(1);
		BatPart[a].SetRotationMode(0);
		BatPart[a].SetMoveSpeed(0.0f);
		BatPart[a].SetWorldPos(
			(float)(pDstChara[a]->GetFieldX()),
			(float)(pDstChara[a]->GetFieldZ() + 1.0f),
			(float)(pDstChara[a]->GetFieldY())
			);
		BatPart[a].SetMoveVectorXYZ(
			(float)(0),
			(float)(-1),
			(float)(0)
		);
	}

	float addw = 0;

	eiD3DParticle_SetG(0.00f);

	let.Reset();
	let2.Reset();
	flag = 1;
	addw = 0;

	int anime_flag = 0,t,show_ver = 1,sound = 0;
	float f = 0.002f,speed = 0.03f,addt = 0;
	pSound[44].Play();
	pSound[45].Play();
	while(flag){
		et->Reset();
		t = let.Get();

		if(let.Get() > 500 && !sound){
			sound = 1;
//			pSound[47].Play();
		}
		if(anime_flag == 0){
			if(let.Get() > 1000){
				let.Reset();
				anime_flag = 2;
				flag = 0;
			}
		}

		//---‚ß‚ç‚ß‚ç
		if(let2.Get() > 50){
			if(++ tex_number >= 4)
				tex_number = 0;
			for(a = 0;a < dst_count;a ++){
				pBtObject[a].SetTexture(&tex[tex_number]);
			}
			let2.Reset();
		}

		if(anime_flag == 0 && mode >= 2){
			speed = (float)(0.04f + ((float)(t + addt) * 0.00065f));
			material.SetDeffuseColor(64,160,255,
				255 - (int)((float)t * (255.0f / 1000.0f)));
			material.SetEmissiveColor(16,40,64,255);
			for(c = 0;c < dst_count;c ++){
				BatPart[c].SetMoveSpeed(speed);
				f = (float)(0.04f + ((float)(t + addt) * 0.0005f));//0.1
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
			}
		}

		if(anime_flag == 2 && let.Get() > 1000){
			flag = 0;
		}
		

		crbatClearDrawingList();
		crbatAddDrawingListAll();
		if(anime_flag < 2){
			for(a = 0;a < dst_count;a ++){
				crbatAddDrawingList(&pBtObject[a],0,1);
			}
		}

crdataEnableRec(0);
		crbatDrawScene();
		if(anime_flag == 0 && mode >= 2){
			if(eid3d->Begin()){
				eid3d->BeginAlphaBlend();
				crbatDraw_SetViewport(0);
				crbatDraw_SetMatrix(0);
				eid3d->SetMaterial(&material);
				eid3d->SetTexture(NULL);
				crbatSetAddAlpha();

				for(a = 0;a < dst_count;a ++){
					BatPart[a].MoveFrame((float)addw);
				}
				eid3d->SetDrawMode(EID3D_DRAWMODE_CULLCW);
				for(a = 0;a < dst_count;a ++){
					BatPart[a].Draw(BatPart[a].Info.VertexCount / 2);
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

//	if(mode >= 2){
		for(a = 0;a < dst_count;a ++){
			BatPart[0].Release();
		}
//	}

	for(a = 0;a < 4;a ++){
		tex[a].ReleaseTexture();
	}
	material.Release();
}



//---—‹‚Q
CRBATANIME_API void crbatDoAnime_MagicThunder2(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,
										   int red,int green,int blue,int mode,int ice)
{
	eiTime let;
	int AddWorld = 0,flag,begin_anime = 0;
	int a,b,anime3d = 0;
	float dis = 0;
	CrBattleCharacter *pDstChara = pDamageInfo->pList[0];

	eiD3DMaterial material[2];
	float addw = 0;

	int tri_count = mode;

	material[0].Create();
	material[0].SetDeffuseColor(red,green,blue,127);
	material[0].SetEmissiveColor(red / 4,green / 4,blue / 4,127);
	material[0].Set();
	BatPart[0].CreateRandomTriangle(
		10.0f,0.70f,tri_count);
		//100 * (mode + 1));//150
	BatPart[0].SetWeight(0);
	BatPart[0].SetWorldPos(
		(float)(pDstChara->GetFieldX() + 0.0f),
		0.0f,
		(float)(pDstChara->GetFieldY() + 0.0f)
	);
	BatPart[0].SetRotationMode(1);
	BatPart[0].SetMoveSpeed(0.0f);
	BatPart[0].SetMoveRotation(0,0.005f);
	BatPart[0].SetMoveVectorXYZ(
		0.0f,1.0f,0.0f
	);

	eiD3DParticle_SetG(0.00f);

	let.Reset();
	flag = 1;
	addw = 0;


	int anime_flag = 0,t,run_time = 1500;
	float f = 0.005f,g,speed = 0.03f,now_rate;

	if(ice){
		crsoundPlay(CRSOUND_ICE1);
	}
	while(flag){
		et->Reset();
		t = let.Get();

		now_rate = (float)(run_time - t) / run_time;

		switch(anime3d){
		case 0:
			if(anime_flag == 0){
				material[0].SetDeffuseColor(red,green,blue,255 - (int)((float)let.Get() * 127.0f / (float)run_time));
				f = 0.02f;
				g = 0.03f;
				for(a = 0;a < BatPart[0].Info.VertexCount;a += 3){	
					for(b = 0;b < 3;b ++){
						BatPart[0].Info.pVertex[a + b].x =
							(now_rate * BatPart[0].Info.pStartVertex[a + b].x);// + (float)(b) * 0.1f);
						BatPart[0].Info.pVertex[a + b].y =
							(now_rate * BatPart[0].Info.pStartVertex[a + b].y);// + (float)(b)* 0.1f);
						BatPart[0].Info.pVertex[a + b].z =
							(now_rate * BatPart[0].Info.pStartVertex[a + b].z);// + (float)(b)* 0.1f);
					}
				}
			}

			if(anime3d == 0 && anime_flag == 0 && let.Get() > run_time){
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

			crbatSetAddAlpha();

			eid3d->SetMaterial(&material[0]);
			BatPart[0].MoveFrame(addw);
			BatPart[0].Draw();

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
	material[0].Release();

	BatPart[0].Release();
}
