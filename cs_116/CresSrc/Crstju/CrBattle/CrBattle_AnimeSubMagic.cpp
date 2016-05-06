
//---魔法使用前の共通エフェクト
CRBATANIME_API void crbatAnime_PreMagic(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo)
{
//	crbatStartFade(127,127,127,500);
	crbatStartFade(64,64,64,500);
	crbatDrawSceneWhile(250);
	crsoundPlay(CRSOUND_MAGIC);
	crbatAnime_EfectLiner(pChara,pDamageInfo);
}

//---魔法使用後の共通エフェクト
CRBATANIME_API void crbatAnime_AfterMagic(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo)
{
	crbatStartFade(255,255,255,250);
	crbatDrawSceneWhile(250);
}

extern int TargetField[BATTLEFIELD_MAX_X][BATTLEFIELD_MAX_Y];

#include "CrBattle_AnimeSubMagic_Fire.cpp"
#include "CrBattle_AnimeSubMagic_Thunder.cpp"
#include "CrBattle_AnimeSubMagic_Other.cpp"
#include "CrBattle_AnimeSubMagic_Mizu.cpp"
#include "CrBattle_AnimeSubMagic_Tuchi.cpp"


//---だるだるは
CRBATANIME_API void crbatDoAnime_MagiDarudaru(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,float move_speed,int r_time)
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

	dr = 0.3f;

	//----------------------------------
	for(a = 0;a < dst_count;a ++){
		BatPart[a].CreateSphere(0.6f,12,12, 0.5f,3.5f);
		BatPart[a].SetMoveRotation(0,0);
		BatPart[a].SetWeight(0);
		BatPart[a].SetRotationMode(0);
		BatPart[a].SetMoveSpeed(0.0f);
		BatPart[a].SetWorldPos(
			(float)(pChara->GetFieldX()),
			(float)(pChara->GetFieldZ() + 0.0),
			(float)(pChara->GetFieldY())
			);
		BatPart[a].SetMoveVectorXYZ(
			(float)(pDstChara[a]->GetFieldX() - pChara->GetFieldX()),
			(float)(pDstChara[a]->GetFieldZ() - pChara->GetFieldZ()),
			(float)(pDstChara[a]->GetFieldY() - pChara->GetFieldY())
		);
	}
	float addw = 0;

	eiD3DParticle_SetG(0.0f);

	let.Reset();
	let2.Reset();
	flag = 1;
	addw = 0;

	int sound = 0,anime_flag = 0,t,show_ver = 1;
	float f = 0.002f,g,speed = 0.03f;

	f = 0.002f;
	range = 0;

	while(flag){
		et->Reset();
		t = let.Get();


		material.SetDeffuseColor(255,64,0,192 - (int)((float)t * (192.0f / 1000.0f)));

		f = move_speed;
		g = -0.0000001f * t * t + f;
		for(c = 0;c < dst_count;c ++){
			for(a = 0;a < BatPart[c].Info.VertexCount / 2;a += 3){
				for(b = 0;b < 3;b ++){
					BatPart[c].Info.pVertex[a + b].x +=
						(BatPart[c].Info.pVertex[a].nx * addw * f);
					BatPart[c].Info.pVertex[a + b].y +=
						(BatPart[c].Info.pVertex[a].ny * addw * g);//f);
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

		if(anime_flag == 0 && let.Get() > r_time){
			flag = 0;
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
				eid3d->SetTexture(NULL);

				for(c = 0;c < dst_count;c ++){
					BatPart[c].MoveFrame((float)addw);
				}
				eid3d->SetDrawMode(EID3D_DRAWMODE_CULLCW);
				crbatSetAddAlpha();

				c = 0;
				BatPart[c].Draw(BatPart[c].Info.VertexCount / 2);

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


//---風
CRBATANIME_API void crbatDoAnime_MagicWind(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,
										   int red,int green,int blue,int mode,int ambient)
{
	eiTime let;
	int AddWorld = 0,flag,begin_anime = 0;
	int a,b,anime3d = 0;
	float dis = 0;
	CrBattleCharacter *pDstChara = pDamageInfo->pList[0];

	eiD3DMaterial material[2];
	float addw = 0;

	if(crsysQuick()){
		//---クイック
		return;
	}

	material[0].Create();
	material[0].SetDeffuseColor(red,green,blue,127);
	if(ambient)
		material[0].SetAmbientColor(red,green,blue,127);
	material[0].SetEmissiveColor(red / 4,green / 4,blue / 4,127);
	material[0].Set();
	material[1].Create();
	material[1].SetDeffuseColor(red / 3,green / 3,blue / 3,127);
	if(ambient)
		material[1].SetAmbientColor(red / 3,green / 3,blue / 3,127);
	material[1].SetEmissiveColor(red / 8,green / 8,blue / 8,127);
	material[1].Set();

	eiD3DParticle_SetG(0.00f);
	int count = 2;
	for(a = 0;a < count;a ++){
		if(a == 0){
			BatPart[a].CreateRandomTriangle(
				1.00f,0.25f,
				100 * (mode + 1));//150
		} else {
			BatPart[a].CreateSphere(0.5f,15,15,0.0f,3.141592f);
		}
		BatPart[a].SetWeight(0);
		BatPart[a].SetWorldPos(
			(float)(pDstChara->GetFieldX()),
			0.0f,
			(float)(pDstChara->GetFieldY())
		);
		BatPart[a].SetRotationMode(1);
		BatPart[a].SetMoveSpeed(0.0f);
		if(a == 0)
			BatPart[a].SetMoveRotation(0,0.15f);
		else
			BatPart[a].SetMoveRotation(0,-0.15f);
		BatPart[a].SetMoveVectorXYZ(
			0.0f,1.0f,0.0f
		);
	}

	//--------------------------------------------
	EIMEMORY hmem = eiAllocMemory(sizeof(float) * BatPart[0].Info.VertexCount + 10000);
	float *pMoveData = (float *)eiLockMemory(hmem);
	float div;
	int c = 0;
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
	float f = 0.005f,g,speed = 0.03f;
	pSound[46].Play();
	while(flag){
		et->Reset();
		t = let.Get();

		switch(anime3d){
		case 0:
			if(anime_flag == 0){
				material[0].SetDeffuseColor(red,green,blue,255 - (int)((float)let.Get() * 127.0f / 2000.0f));
				material[1].SetDeffuseColor(red / 3,green / 3,blue / 3,
					(mode * 17) - (int)((float)let.Get() * ((mode * 17) / 2) / 2000.0f));
				f = 0.02f;
				g = 0.02f + (float)((float)mode * 0.01f);
				c = 0;
				for(a = 0;a < BatPart[c].Info.VertexCount;a += 3){	
					for(b = 0;b < 3;b ++){
/*						BatPart[c].Info.pVertex[a + b].x +=
							(BatPart[c].Info.pVertex[a].nx * addw * g);
						BatPart[c].Info.pVertex[a + b].y +=
							(BatPart[c].Info.pVertex[a].ny * addw * f);
						BatPart[c].Info.pVertex[a + b].z +=
							(BatPart[c].Info.pVertex[a].nz * addw * g);
*/
						BatPart[c].Info.pVertex[a + b].x +=
							(pMoveData[a + 0] * addw * g);
						BatPart[c].Info.pVertex[a + b].y +=
							(pMoveData[a + 1] * addw * f);
						BatPart[c].Info.pVertex[a + b].z +=
							(pMoveData[a + 2] * addw * g);
					}
				}
				c = 1;
				for(a = 0;a < BatPart[c].Info.VertexCount;a += 3){	
					for(b = 0;b < 3;b ++){
						BatPart[c].Info.pVertex[a + b].x +=
							(BatPart[c].Info.pVertex[a + b].nx * addw * g);
						BatPart[c].Info.pVertex[a + b].y +=
							(BatPart[c].Info.pVertex[a + b].ny * addw * g);
						BatPart[c].Info.pVertex[a + b].z +=
							(BatPart[c].Info.pVertex[a + b].nz * addw * g);
					}
				}
			}

			if(anime3d == 0 && anime_flag == 0 && let.Get() > 2000){
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
				eid3d->SetMaterial(&material[c]);
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

	eiUnlockMemory(hmem);
	eiFreeMemory(hmem);

	material[0].Release();
	material[1].Release();

	BatPart[0].Release();
	BatPart[1].Release();
}

//---補助
CRBATANIME_API void crbatDoAnime_MagicHojo(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,
										   int cr,int cg,int cb)
{
	eiTime let;
	int AddWorld = 0,flag,begin_anime = 0;
	int a,b,c,anime3d = 0;
	float dis = 0;
//	CrBattleCharacter *pDstChara = pDamageInfo->pList[0];
	CrBattleCharacter *pDstChara[16];
	int dst_count;

	for(a = 0,dst_count = 0;pDamageInfo->pList[a] != NULL;a ++){
		pDstChara[a] = pDamageInfo->pList[a];
		dst_count ++;
	}
	pDstChara[a] = NULL;

	eiD3DMaterial material;
	float addw = 0;

	material.Create();
	material.SetDeffuseColor(cr,cg,cb,127);
	material.SetEmissiveColor(cr,cg,cb,127);
	material.Set();

	eiD3DParticle_SetG(0.00f);

	float r = 1.0f,delta = 0.0075f;
	float dx,dz;
	for(c = 0;c < dst_count;c ++){
		for(a = 0;a < 2;a ++){
			BatPart[c * 8 + a * 4].CreateTriangle(
				(float)cos(ANGLE((a * 180 + 0))) * r,  0.01f,(float)sin(ANGLE((a * 180 + 0))) * r,
				(float)cos(ANGLE((a * 180 + 120))) * r,0.01f,(float)sin(ANGLE((a * 180 + 120))) * r,
				(float)cos(ANGLE((a * 180 + 240))) * r,0.01f,(float)sin(ANGLE((a * 180 + 240))) * r);

			for(b = 0;b < 3;b ++){
				dx = (float)cos(ANGLE((a * 180 + b * 120))) * r;
				dz = (float)sin(ANGLE((a * 180 + b * 120))) * r;

				BatPart[c * 8 + a * 4 + b + 1].CreateTriangle(
					dx + (float)cos(ANGLE((a * 180 + b * 120)) + ANGLE(90)) * delta,
					0,
					dz + (float)sin(ANGLE((a * 180 + b * 120)) + ANGLE(90)) * delta,

					dx + (float)cos(ANGLE((a * 180 + b * 120)) - ANGLE(90)) * delta,
					0,
					dz + (float)sin(ANGLE((a * 180 + b * 120)) - ANGLE(90)) * delta,

					dx,0,dz);
			}
		}
		for(a = 0;a < 8;a ++){
			BatPart[c * 8 + a].SetWeight(0);
			BatPart[c * 8 + a].SetWorldPos(
				(float)(pDstChara[c]->GetFieldX()),
				(float)(pDstChara[c]->GetFieldZ() ),
				(float)(pDstChara[c]->GetFieldY())
			);
			BatPart[c * 8 + a].SetRotationMode(1);
			BatPart[c * 8 + a].SetMoveRotation(0,0.05f);
			BatPart[c * 8 + a].SetMoveSpeed(0);
			BatPart[c * 8 + a].SetMoveVectorXYZ(
				(float)(pDstChara[c]->GetFieldX() - pChara->GetFieldX()),
				(float)(pDstChara[c]->GetFieldZ() - pChara->GetFieldZ()),
				(float)(pDstChara[c]->GetFieldY() - pChara->GetFieldY())
			);
		}
		BatPart[c * 8 + 0].SetRotationMode(1);
		BatPart[c * 8 + 4].SetRotationMode(1);
	}

	let.Reset();
	flag = 1;
	addw = 0;

	int anime_flag = 0,t;
	float f = 0.005f,speed = 0.03f;
	while(flag){
		et->Reset();
		t = let.Get();

		if(anime_flag >= 1){
			if(let.Get() > 1000){
				flag = 0;
			}
		}
		material.SetDeffuseColor(cr,cg,cb,127);
		material.SetEmissiveColor(cr / 2,cg / 2,cb / 2,127);

		if(anime_flag == 0){
			if(let.Get() > 500){
				anime_flag = 1;
			}
			material.SetDeffuseColor(cr,cg,cb,(int)( (float)t * 127.0f / 750.0f));
			material.SetEmissiveColor(cr / 2,cg / 2,cb / 2,(int)( (float)t * 127.0f / 750.0f));
		}

		for(c = 0;c < dst_count;c ++){
			for(a = 0;a < 2;a ++){
				for(b = 0;b < 3;b ++){
					BatPart[c * 8 + a * 4 + b + 1].Info.Vertex[2].y = (float)t * 0.002f;
				}
			}
		}

crdataEnableRec(0);
		crbatDrawScene();

		if(eid3d->Begin()){
			eid3d->BeginAlphaBlend();
			crbatSetAddAlpha();
			crbatDraw_SetViewport(0);
			crbatDraw_SetMatrix(0);
			eid3d->SetMaterial(&material);
			eid3d->SetTexture(NULL);

			for(c = 0;c < dst_count;c ++){
				for(a = 0;a < 8;a ++){
					BatPart[c * 8 + a].MoveFrame((float)addw);
				}
			}
			eid3d->SetDrawMode(EID3D_DRAWMODE_CULLNONE);
			for(c = 0;c < dst_count;c ++){
				for(a = 0;a < 8;a ++){
					BatPart[c * 8 + a].Draw();
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
	material.Release();

	for(c = 0;c < dst_count;c ++){
		for(a = 0;a < 8;a ++){
			BatPart[c * 8 + a].Release();
		}
	}
}

CRBATANIME_API void crbatDoAnime_MagicSoul(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo)
{
	eiTime let;
	int AddWorld = 0,flag,begin_anime = 0;
	int a,anime3d = 0;
	float dis = 0;
	CrBattleCharacter *pDstChara = pDamageInfo->pList[0];
	int cr = 0,cg = 0,cb = 255;

	eiD3DMaterial material;
	float addw = 0;

	material.Create();
	material.SetDeffuseColor(cr,cg,cb,127);
	material.SetEmissiveColor(cr,cg,cb,127);
	material.Set();

	eiD3DParticle_SetG(0.00f);

	float r = 1.0f,delta = 0.0075f;
	for(a = 0;a < 1;a ++){
		BatPart[a * 4].CreateTriangle(
			(float)cos(ANGLE((a * 180 + 0))) * r,  0,(float)sin(ANGLE((a * 180 + 0))) * r,
			(float)cos(ANGLE((a * 180 + 120))) * r,0,(float)sin(ANGLE((a * 180 + 120))) * r,
			(float)cos(ANGLE((a * 180 + 240))) * r,0,(float)sin(ANGLE((a * 180 + 240))) * r);

	}
	for(a = 0;a < 1;a ++){
		BatPart[a].SetWeight(0);
		BatPart[a].SetWorldPos(
			(float)(pDstChara->GetFieldX()),
			(float)(pDstChara->GetFieldZ() + 0.5f),
			(float)(pDstChara->GetFieldY())
		);
		BatPart[a].SetRotationMode(1);
		BatPart[a].SetMoveRotation(0,0.05f);
		BatPart[a].SetMoveSpeed(0);
		BatPart[a].SetMoveVectorXYZ(
			(float)(pDstChara->GetFieldX() - pChara->GetFieldX()),
			(float)(pDstChara->GetFieldZ() - pChara->GetFieldZ()),
			(float)(pDstChara->GetFieldY() - pChara->GetFieldY())
		);
	}
	BatPart[0].SetRotationMode(1);
	BatPart[0].SetMoveRotation(0.05f,0.05f);

	let.Reset();
	flag = 1;
	addw = 0;

	int anime_flag = 0,t;
	float f = 0.005f,speed = 0.03f;
	while(flag){
		et->Reset();
		t = let.Get();

		if(anime_flag >= 1){
			if(let.Get() > 1500){
				flag = 0;
			}
		}
		material.SetDeffuseColor(cr,cg,cb,224);
		material.SetEmissiveColor(cr / 2,cg / 2,cb / 2,224);

		if(anime_flag == 0){
			if(let.Get() > 500){
				anime_flag = 1;
			}
			material.SetDeffuseColor(cr,cg,cb,(int)( (float)t * 224.0f / 750.0f));
			material.SetEmissiveColor(cr / 2,cg / 2,cb / 2,(int)( (float)t * 224.0f / 750.0f));
		}

		crbatDrawScene();

		if(eid3d->Begin()){
			eid3d->BeginAlphaBlend();
			crbatSetAddAlpha();
//			eid3d->lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_ONE);
			crbatDraw_SetViewport(0);
			crbatDraw_SetMatrix(0);
			eid3d->SetMaterial(&material);
			eid3d->SetTexture(NULL);

			for(a = 0;a < 1;a ++){
				BatPart[a].MoveFrame((float)addw);
			}
			eid3d->SetDrawMode(EID3D_DRAWMODE_CULLNONE);
			for(a = 0;a < 1;a ++){
				BatPart[a].Draw();
			}
			eid3d->SetMaterial(NULL);
			eid3d->EndAlphaBlend();
			eid3d->End();
		}
		if(eiGetEndThread()){
			break;
		}
		crbatDrawRefresh();

		addw = (float)et->Get() / 10.0f;
	}
	material.Release();

	for(a = 0;a < 1;a ++){
		BatPart[a].Release();
	}
}


//---魔法攻撃アニメ
CRBATANIME_API void crbatDoAnime_Magic(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,int force_number)
{
	eiTime let;
	int a,AddWorld = 0,begin_anime = 0;
	int anime,object,anime3d = 0;
	int magic = pChara->Command.Sub[0];
	float dis = 0;
	CrBattleCharacter *pDstChara;

	if(force_number)
		magic = force_number;

	if(crsysQuick()){
		//---クイック
		return;
	}
//----例外処理この間
	pDstChara = pDamageInfo->pList[0];
	for(a = 0;a < 2;a ++){
		if(a == 0){
			BatLight[a].Create(D3DLIGHT_DIRECTIONAL);
			BatLight[a].SetDirection(
				(float)(pDstChara->GetFieldX() - pChara->GetFieldX()),
				1.0f,
				(float)(pDstChara->GetFieldY() - pChara->GetFieldY())
			);
			BatLight[a].SetColor(255,255,255,255);
		} else {
			BatLight[a].Create();
			BatLight[a].SetColor(20,20,20,255);
		}
		BatLight[a].SetPos(
			(float)pChara->GetFieldX(),
			1.0f,
			(float)pChara->GetFieldY());
		BatLight[a].SetAttenuation(0.3f,0.2f,0.9f);
		if(eid3d->Begin()){
			eid3d->SetLight(&BatLight[a],a);
			eid3d->End();
		}
	}

	anime = 1;
	object = crbatInitAnimeScene(pChara,pDamageInfo,anime);

	//---その場にいる
	pChara->SetAnimeMoving(
		(float)pChara->GetFieldX(),
		(float)pChara->GetFieldY(),
		(float)pChara->GetFieldZ(),CHARSPEED_RUN);

	//---魔法エフェクト前のアニメーション
	crbatLoadExtCharacter_Magic(pChara);
	if(pChara->GetDrawType() == DRAWTYPE_4_ANIME){
		pChara->SetPattern(20);
	}
	crbatAnime_PreMagic(pChara,pDamageInfo);
	if(pChara->GetDrawType() == DRAWTYPE_4_ANIME){
		pChara->SetPattern(0);
	}

	switch(magic){
	case 41:
		crbatDoAnime_MagicFire2(pChara,pDamageInfo,0);
		break;
	case 42:
		//---レイザーレイ
		crbatDoAnime_MagicRay(pChara,pDamageInfo,255,64,0,0.1f,0);
		break;
	case 43:
		crbatDoAnime_MagicFire2(pChara,pDamageInfo,1);
		break;
	case 44:
		crbatDoAnime_MagicFire4(pChara,pDamageInfo,0,0);
		break;
	case 45:
		crbatDoAnime_MagicFire5(pChara,pDamageInfo,0);
		break;
//----------------------------
	case 47:
	case 48:
	case 49:
		crbatDoAnime_MagicWater(pChara,pDamageInfo,magic - 47);
		break;
	case 50:
		//---アクアソード
		crbatDoAnime_MagicThunder2(pChara,pDamageInfo,128,255,255,800,1);
		crbatDoAnime_MagicRay(pChara,pDamageInfo,128,255,255,0.1f,1);
		break;
	case 51:
		crbatDoAnime_MagicWater2(pChara,pDamageInfo);
		break;

	case 53:
	case 54:
	case 55:
	case 56:
	case 57:
		crbatDoAnime_MagicWind(pChara,pDamageInfo,127,255,127,magic - 53,0);
		break;

//----------------------------
	//---土
	case 59:
		crbatDoAnime_MagicTsuchi(pChara,pDamageInfo,0);
		break;
	case 60:
		crbatDoAnime_MagicTsuchi(pChara,pDamageInfo,1);
		break;
	case 61:
		crbatDoAnime_MagicTsuchi2(pChara,pDamageInfo,255,128,0,1);
		break;
	case 62:
		crbatDoAnime_MagicTsuchi2(pChara,pDamageInfo,255,128,0,2);
		break;
	case 63:
		crbatDoAnime_MagicEarthQuake(pChara,pDamageInfo,0);
		break;

//----------------------------
	//---雷
	case 65:
		crbatDoAnime_MagicThunder(pChara,pDamageInfo,0);
		break;
	case 66:
		crbatDoAnime_MagicThunder(pChara,pDamageInfo,0);
		break;
	case 67:
		crbatDoAnime_MagicThunder2(pChara,pDamageInfo,64,160,255,300,0);
		crbatDoAnime_MagicThunder(pChara,pDamageInfo,0);
		break;
	case 68:
		crbatDoAnime_MagicThunder2(pChara,pDamageInfo,64,160,255,600,0);
		crbatDoAnime_MagicThunder(pChara,pDamageInfo,1);
		break;
	case 69:
		crbatDoAnime_MagicThunder2(pChara,pDamageInfo,64,160,255,1200,0);
		crbatDoAnime_MagicThunder(pChara,pDamageInfo,1);
		break;

	case 71:
		crbatDoAnime_MagicSoul(pChara,pDamageInfo);
		break;
	case 77:
		crbatDoAnime_MagicExtinction1(pChara,pDamageInfo);
		break;
	case 78:
		crbatDoAnime_MagicDiffusion4(pChara,pDamageInfo);
		break;
	case 79:
		crbatDoAnime_MagicRuin(pChara,pDamageInfo);
		crbatDoAnime_MagicExtinction2(pChara,pDamageInfo);
		break;
	case 80:
		crbatDoAnime_MagicInfretion(pChara,pDamageInfo,0);
		break;

	default:
		if(0 <= magic && magic <= 10){
			crbatDoAnime_MagicHojo(pChara,pDamageInfo,
				192,255,255);
			crbatDoAnime_Kaifuku(pChara,pDamageInfo);
		} else {
			switch(magic){
			case 11:
			case 14:
			case 15:
			case 18:
			case 20:
			case 21:
			case 23:
			case 25:
			case 30:
			case 31:
				crbatDoAnime_MagicHojo(pChara,pDamageInfo,
					255,16,64);
				break;

			default:
				crbatDoAnime_MagicHojo(pChara,pDamageInfo,
					0,64,255);
				break;
			}

		}
/*		if(11 <= magic && magic <= 31){
			crbatDoAnime_MagicHojo(pChara,pDamageInfo,
				255,16,64);
//				0,127,255);
		}*/
	}


	crbatEndAnimeScene(pChara);
	crbatAnime_AfterMagic(pChara,pDamageInfo);

	//---ライトを解放
	if(eid3d->Begin()){
		eid3d->SetLight(NULL,0);
		eid3d->SetLight(NULL,1);
		eid3d->SetMaterial(NULL);
		eid3d->End();
	}
	BatLight[1].Release();
	BatLight[0].Release();
}

