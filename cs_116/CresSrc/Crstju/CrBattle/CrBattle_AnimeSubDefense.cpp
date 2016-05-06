//---移動アニメーション
CRBATANIME_API void crbatDoAnime_Move(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo)
{
	eiTime let;
	int AddWorld = 0,flag,begin_anime = 0,sound = 0;
	int anime,object;
	float dis;

	if(crsysQuick()){
		//---クイック
		return;
	}

	anime = 0;
	object = crbatInitAnimeScene(pChara,pDamageInfo,anime);

	//---その場にいる
	pChara->SetAnimeMoving(
		(float)pChara->Command.Sub[1],
		(float)pChara->Command.Sub[2],
		(float)pChara->GetFieldZ(),CHARSPEED_RUN);
	crbatLoadExtCharacter_Running(pChara);

	flag = 1;
	while(flag){
		let.Reset();

		crbatClearDrawingList();
		crbatAddDrawingListAll();

		crbatBeginAnime(); {
			dis = pChara->DoAnime((float)AddWorld);
			if(dis <= 0.0f){
				flag = 0;
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

//---移動アニメーション２
CRBATANIME_API void crbatDoAnime_Move2(CrBattleCharacter *pChara,CR_BATTLE_DAMAGEINFO *pDamageInfo,
				int *x,int *y,float speed)
{
	eiTime let;
	int AddWorld = 0,flag,begin_anime = 0,sound = 0;
	int a,anime,object;
	float dis;

	if(crsysQuick()){
		//---クイック
		return;
	}

	anime = 0;
	object = crbatInitAnimeScene(pChara,pDamageInfo,anime);
	int AnimePattern[] = {0,1000,-1,0};

	//---その場にいる
	for(a = 0;pDamageInfo->pList[a] != NULL;a ++){
		if(pDamageInfo->Damage[a]){
			pDamageInfo->pList[a]->BeginAnime(0);
			pDamageInfo->pList[a]->SetAnimeMoving(
				(float)(*(x + a)),
				(float)(*(y + a)),
				(float)pDamageInfo->pList[a]->GetFieldZ(),speed/*CHARSPEED_WALK*/);
			pDamageInfo->pList[a]->SetAnimePattern(AnimePattern);
		}
	}
//	crbatLoadExtCharacter_Running(pChara);

	int chara_move[BATTLECHARA_MAX];

	memset(chara_move,0,sizeof(chara_move));
	flag = 1;
	while(flag){
		flag = 0;
		let.Reset();

		crbatClearDrawingList();
		crbatAddDrawingListAll();

		crbatBeginAnime(); {
			for(a = 0;pDamageInfo->pList[a] != NULL;a ++){
				if(!pDamageInfo->Damage[a])
					continue;

				dis = 0;
				if(!chara_move[a]){
					dis = pDamageInfo->pList[a]->DoAnime((float)AddWorld);
				}

				if(!(dis <= 0.0f)){
					flag ++;
				} else {
					chara_move[a] = 1;
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

	for(a = 0;pDamageInfo->pList[a] != NULL;a ++){
		pDamageInfo->pList[a]->EndAnime();
	}
	crbatEndAnimeScene(pChara);
}
