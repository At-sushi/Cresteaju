
//---���b�N�I��
CRBATANIME_API void crbatDoAnime_LockOn(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo)
{
	eiTime let,let2;
	int AddWorld = 0,flag = 1;
	int a;
	float dis = 0,prev_dis = 9999.0f;

	eiTextureCell tex;

	tex.ReadFile(CR_DATADIR4"LockOn.acf",CR_DATAFILE4,crdataGetFileMode());
	tex.Init(16);
	tex.Load();

	CrBattleCharacter *pDstChara[16];
	int dst_count,anime = 0;

	for(a = 0,dst_count = 0;pDamageInfo->pList[a] != NULL;a ++){
		pDstChara[a] = pDamageInfo->pList[a];
		dst_count ++;
	}

	for(a = 0;a < dst_count;a ++){
		pBtObject[a].CreateTLVertexRect(64,255);
		pBtObject[a].SetPos(
			(float)(pDstChara[a]->GetFieldX() + (float)(pChara->GetFieldX())) * 0.5f,
			(float)(pDstChara[a]->GetFieldY() + (float)(pChara->GetFieldY())) * 0.5f,
			1.0f
		);
		pBtObject[a].SetDrawMode(1);
		pBtObject[a].SetTexture(&tex);
		pBtObject[a].SetMoveVectorXYZ(
			(float)(pDstChara[a]->GetFieldX() - (float)(pChara->GetFieldX())),
			(float)(pDstChara[a]->GetFieldY() - (float)(pChara->GetFieldY())),
			((float)pDstChara[a]->GetCharaHeight() / 64.0f - 1.0f) * 0.50f - 0.50f//-0.5f
		);
		pBtObject[a].SetMoveSpeed(0.1f);
		pBtObject[a].SetAlphaMode(0);
		pBtObject[a].SetXRate(1.5f);
		pBtObject[a].SetYRate(1.5f);
	}

	anime = 0;
	AddWorld = 0;

	while(flag){
		let.Reset();

		crbatClearDrawingList();
		crbatAddDrawingListAll();

		crbatBeginAnime(); {
			for(a = 0;a < dst_count;a ++){
					crbatAddDrawingList(&pBtObject[a],0,1);
				if(anime == 0){
					pBtObject[a].Move((float)AddWorld * 0.04f);

					dis = (float)sqrt(
						(float)(
						(pBtObject[a].GetX() - (float)pDstChara[a]->GetFieldX()) * (pBtObject[a].GetX() - (float)pDstChara[a]->GetFieldX())
					+	(pBtObject[a].GetY() - (float)pDstChara[a]->GetFieldY()) * (pBtObject[a].GetY() - (float)pDstChara[a]->GetFieldY())
					+	(pBtObject[a].GetZ() - (float)pDstChara[a]->GetFieldZ()) * (pBtObject[a].GetZ() - (float)pDstChara[a]->GetFieldZ())
						)
					);
				}

/*				char s[40];
				sprintf(s,"%f\n",dis);
				eiDebugWriteFile(s);*/
			}
		} crbatEndAnime();

		if(dis > prev_dis && anime == 0){
			for(a = 0;a < dst_count;a ++){
				pBtObject[a].SetMoveSpeed(0);
				pBtObject[a].SetPos(
					(float)pDstChara[a]->GetFieldX(),
					(float)pDstChara[a]->GetFieldY(),
					pBtObject[a].GetZ()
				);
			}
			anime = 1;
			let2.Reset();
		}

		if(anime == 1){
			//---�k��
			int t = let2.Get();

			if(t >= 1000)
				t = 1000;

			for(a = 0;a < dst_count;a ++){
				pBtObject[a].SetXRate(0.5f + (float)(1000 - t) * 0.001f);
				pBtObject[a].SetYRate(0.5f + (float)(1000 - t) * 0.001f);
			}

			if(let2.Get() > 1250)
				flag = 0;
		}

		prev_dis = dis;
		
crdataEnableRec(0);
		crbatDrawScene();
crdataEnableRec(1);
		if(eiGetEndThread()){
			break;
		}
		crbatDrawRefresh();

		AddWorld = let.Get();
	}

	tex.ReleaseTexture();
}


//---����U���A�j��
CRBATANIME_API void crbatDoAnime_Weapon(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,
										int critical,int option /*= 0*/)
{
	eiTime let,let2;
	eiTime criticalT;

	int AddWorld = 0,flag,begin_anime = 0,sound = 0;
	int a,anime,object;
	float dis;
	int anime_type = 0,anime_wait = 0;
	static ei_s32 AnimePattern[8] = {0,500,16,500,-1,0};

	int critical_flash = 0;

	if(crsysQuick()){
		//---�N�C�b�N
		return;
	}
/*
	if(critical){
		eiDebugWriteFile("anime:Critical!!\n");
	}
*/
//	crbatDoAnime_LockOn(pChara,pDamageInfo);

	int type = 0,dam0,weapon = pChara->GetWeapon(pChara->Command.Sub[0]),hit = 0;
	if(weapon){
		type = pItemInfo[weapon].GetAtackKind();
	} else if(!pChara->IsFriend()){
		if(pChara->BattleInfo.Enemy.AtackType == 1){
			//---�G�ԐڍU��
			type = 1;
		}
	}

	anime = 0;
	anime = critemGetItemClass(weapon)->GetAnime();
	if(!pChara->IsFriend()
		&& !(207 <= pChara->BattleInfo.Enemy.Graphic && pChara->BattleInfo.Enemy.Graphic <= 210)
		){
		anime = pChara->BattleInfo.Enemy.AtackAnime;
	}
	object = crbatInitAnimeScene(pChara,pDamageInfo,anime);

	eiTextureCell tex;
	CrBattleCharacter *pDstChara[16];
	int dst_count = 0;
//	float range = 0;
	if(option){
		tex.ReadFile(CR_DATADIR4"circle.acf",CR_DATAFILE4,crdataGetFileMode());
		tex.Init(16);
		tex.Load();

		for(a = 0,dst_count = 0;pDamageInfo->pList[a] != NULL;a ++){
			pDstChara[a] = pDamageInfo->pList[a];
			dst_count ++;
		}

		for(a = 0;a < dst_count;a ++){
			pBtObject[a].CreateTLVertexRect(64,255);
			pBtObject[a].SetPos(
				(float)(pDstChara[a]->GetFieldX()),
				(float)(pDstChara[a]->GetFieldY())
				,
				0.5f
				);
			pBtObject[a].SetDrawMode(1);
			pBtObject[a].SetTexture(&tex);
			pBtObject[a].SetMoveVectorXYZ(
				1,0,0
			);
			pBtObject[a].SetMoveSpeed(0);
			pBtObject[a].SetAlphaMode(0);
		}
	}

	//---���̏�ɂ���
	pChara->SetAnimeMoving(
		(float)pChara->GetFieldX(),
		(float)pChara->GetFieldY(),
		(float)pChara->GetFieldZ(),CHARSPEED_RUN);

	if(type == 1
		&& (CRMATERIAL_ITEMKIND_GUN == pItemInfo[weapon].GetKind()
		|| CRMATERIAL_ITEMKIND_SPGUN == pItemInfo[weapon].GetKind())){
		//---�ԐڍU�����e
		if(pChara->GetDrawType() == 0){
			crbatLoadExtCharacter_Gun(pChara);
			anime_type = 1;
			pChara->SetAnimePattern(&AnimePattern[0]);
		}

		int l_time = 1000;
		if(crbatGetBattleSpeed() == 1)
			l_time = 100;

		pChara->SetAnimeLimitTime((float)l_time);
		pChara->SetMoveSpeed(0.0f);
	}

	if(1/*pDamageInfo->pList[1] == NULL*/){
		//---�U���Ώۂ��P�̂����Œ��ڍU����������

		if(type == 0){
			//---���ڍU����������
			pChara->SetAnimeMoving(
				(float)pDamageInfo->pList[0]->GetFieldX(),
				(float)pDamageInfo->pList[0]->GetFieldY(),
				(float)pChara->GetFieldZ(),CHARSPEED_RUN,1);

			//---�A�j���[�V�������[�h
			crbatLoadExtCharacter_Running(pChara);
		}
	}

	flag = 1;
	dam0 = 0;
	let2.Reset();
	criticalT.Reset();
	while(flag){
		let.Reset();

		crbatClearDrawingList();
		crbatAddDrawingListAll();

		crbatBeginAnime(); {
			dis = pChara->DoAnime((float)AddWorld);

			if(anime_type == 0){
				if(dis < 1.0f){
					if(begin_anime == 0 && option){
						let2.Reset();
					}
					begin_anime = 1;
				}
			} else if(anime_type == 1){
				if(pChara->GetLeftTime() <= 0.0){
					if(begin_anime == 0 && option){
						let2.Reset();
					}
					begin_anime = 1;
				}
			}

			if(begin_anime){
				for(a = 0 ,flag = 0;a < object;a ++){					
					if(pDamageInfo->Miss[a] == 1){
						flag ++;
					}
				}
				for(a = 0 ,dam0 = 0;a < object;a ++){
					if(pDamageInfo->Damage[a] == 0 && pDamageInfo->Miss[a] == 0){
						//---�_���[�W�O�I
						dam0 ++;
					}
				}
				if(flag == object){
					//---�S�X�J
					sound = 1;
				}
				if(!sound){
					//---���ʉ���炷
					int sound_number = 1;

					if(pChara->IsFriend()){
						sound_number = pItemInfo[
							pChara->GetWeapon(pChara->Command.Sub[0])
							].GetSound();
					} else {
						sound_number = pChara->BattleInfo.Enemy.NormalSound;
					}

					if(dam0){
						//---�_���[�W�O
						crsoundPlay(CRSOUND_DAMAGE0,0);
					} else {
						crsoundPlay(sound_number,0);
					}
					sound ++;

					//---�N���e�B�J��
					hit = 1;
					criticalT.Reset();
				}
				//---�U���A�j���[�V�����J�n
				for(a = 0 , flag = 0;a < object;a ++){
					flag |= pBtObject[a].DoAnime((float)AddWorld);
					//---�đO�ʂɃA�j���[�V������\��
					crbatAddDrawingList(&pBtObject[a],-1,0,pDamageInfo->pList[a]);
				}
			}
		} crbatEndAnime();

		if(option && begin_anime){
			int t = let2.Get();
			float f = (float)pow((float)t,1.75);

			for(a = 0;a < dst_count;a ++){
				pBtObject[a].SetXRate(f / 1000.0f);
				pBtObject[a].SetYRate(f / 1000.0f);
				crbatAddDrawingList(&pBtObject[a],0,1);
			}
		}

crdataEnableRec(0);
		crbatDrawScene();
		if(critical && hit == 1){
			//---�N���e�B�J��
			if(criticalT.Get() <= 20 ||
				(critical_flash <= 1 && criticalT.Get() <= 100)){
				crbatDrawFlash(255,255,255);
				critical_flash ++;
			} else {
				hit = 2;
			}
		}

crdataEnableRec(1);
		if(eiGetEndThread()){
			break;
		}
		crbatDrawRefresh();

		AddWorld = let.Get();
	}
	if(option){
		tex.ReleaseTexture();
	}
	crbatEndAnimeScene(pChara);
}


//---�񕜃A�j��
CRBATANIME_API void crbatDoAnime_Kaifuku(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo)
{
	eiTime let;
	int AddWorld = 0,flag,begin_anime = 0,sound = 0;
	int a,object;
	int anime_type = 0,anime_wait = 0;
	static ei_s32 AnimePattern[8] = {0,500,16,500,-1,0};

	if(crsysQuick()){
		//---�N�C�b�N
		return;
	}

	object = crbatInitAnimeScene(pChara,pDamageInfo,3);

	flag = 1;
	while(flag){
		let.Reset();

		crbatClearDrawingList();
		crbatAddDrawingListAll();

		crbatBeginAnime(); {
			begin_anime = 1;

			if(begin_anime){
				if(!sound){
					//---���ʉ���炷
					crsoundPlay(CRSOUND_RICOVERY,0);
					sound ++;
				}
				//---�U���A�j���[�V�����J�n
				for(a = 0 , flag = 0;a < object;a ++){
					flag |= pBtObject[a].DoAnime((float)AddWorld);
					//---�đO�ʂɃA�j���[�V������\��
					crbatAddDrawingList(&pBtObject[a],-1,0,pDamageInfo->pList[a]);
				}
			}
		} crbatEndAnime();

crdataEnableRec(0);
		crbatDrawScene();

crdataEnableRec(1);
		if(eiGetEndThread()){
			break;
		}
		crbatDrawRefresh();

		AddWorld = let.Get();
	}
	crbatEndAnimeScene(pChara);
}
