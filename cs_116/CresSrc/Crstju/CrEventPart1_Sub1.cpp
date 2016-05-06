#define TREE_MAX 10

//---オープニンググラウンドシップ
void crevent_OpeningBGCallback(eiCell *pScrCell,int sx,int sy,int top_x,int top_y,int delta_t)
{
	static int delta = 0,tree_count = 0,
		prev_tree_count = 0,disable_count = 0,prev_delta;
	static int tx[TREE_MAX],ty[TREE_MAX],tflag[TREE_MAX];
	int a,x,y,d_add;

	delta_t = evtime.Get();
	evtime.Reset();

	if(delta_t <= 0)
		delta_t = 1;
	if(delta_t >= 320)
		delta_t = 320;
	delta += delta_t;

	tree_count += delta_t;
	disable_count -= delta_t;

	if(delta >= 320){
		delta = delta % 320;
	}
	d_add = delta / 10;

	for(y = 0;y <= sy;y ++){
		for(x = 0;x <= sx;x ++){
			pCell[CR_PTN_FIELD].PutClip(
				pScrCell,top_x + (x + 1) * 32 - d_add,top_y + y * 32);
		}
	}

//	d_add = (tree_count - prev_tree_count) / 10;
	for(a = 0;a < TREE_MAX;a ++){
		if(tflag[a]){
			if(delta < prev_delta){
				tx[a] -= 1;
			}

			if(tx[a] < -32){
				tflag[a] = 0;
			} else {
				pCell[CR_PTN_FIELD + 100].PutTransClip(
					pScrCell,top_x + (tx[a] * 32) - d_add,top_y + ty[a] * 32);
				pCell[CR_PTN_FIELD + 101].PutTransClip(
					pScrCell,top_x + (tx[a] * 32) - d_add,top_y + (ty[a] + 1) * 32);
			}
		} else {
			if(eiRnd(1000) < 5 && disable_count <= 0){
				tx[a] = 20;
				ty[a] = eiRnd(5);
				if(ty[a] == 4)
					ty[a] = 13;
				tflag[a] = 1;
				disable_count = 1000;
			}
		}
	}
	prev_tree_count = tree_count;
	prev_delta = delta;

//	evtime.Reset();
}

int creventOpening(void)
{
	int a = 0,b = 0,c = 0;
	CrMesManager mes;

	CR_BATTLEINFO BatInfo;
	memset(&BatInfo,0,sizeof(BatInfo));

			//---！、フォールン！
			mes.OpenMessage("Opening.msg",2);
			mes.ReadMessage();
			mes.Draw();

			for(a = 0;a < 5;a ++){
				mcMove(0,1);
				evFrame();
			}
			for(a = 0;a < 2;a ++){
				mcMove(-1,0);
				evFrame();
			}
			mcMove(0,1);
			evFrame(1);

			mcShow(0);
			npDir(1,SOUTH);
			for(a = 0;a < 3;a ++){
				mcMove(0,1);
				evFrame();

//				et->Delay2(500);
			}
			mes.ReadDraw();

			//---間を置いてフォールン振り向く
			evFrameWait(3000);
			npDir(0,WEST);
			evFrameWait(1000);
			npDir(0,NORTH);
			evFrameWait(2000);
			mes.ReadMessage();
			mes.Draw();

			evFrameWait(1000);
			mes.ReadDraw();

			//---エターナルのためだ
			evFrameWait(2000);
			mes.ReadDraw();

			mes.ReadDraw(5);
			evFrameWait(2000);
			mes.ReadMessage();
			mes.Draw();

			mes.CloseMessage();
			evFrameWait(500);

			//---バトル
			BatInfo.FailOK = 1;
			BatInfo.Music = 0;
			BatInfo.Mode = 0;
			BatInfo.ScreenEfect = 1;
			BatInfo.Enemy[0].Enemy = 11;
			BatInfo.Enemy[0].x = 6;
			BatInfo.Enemy[0].y = 10;
			BatInfo.Enemy[1].Enemy = -1;
			crbatEventBattle(&BatInfo);

			//---誰でもいい・・・
			crfieldChangeScene(1,10,10);
			evFrameWait(1000);
//			evFrame(60);
			mes.OpenMessage("Opening.msg",4);
			mes.ReadDraw();
			evFrameWait(1000);

			crmusicFadeOut(1);
			evFadeOut(2000);

			//---グラウンドシップの甲板
			crmusicStop();
			crfieldChangeMap(12,0,1,0);
			crfieldChangePos(18,22,1);
			ef->SetBGCallback(crevent_OpeningBGCallback);
			et->Delay2(1000);
			crsoundPlay(CRSOUND_GS_SOUND,1);
			et->Delay2(3000);

			//---
//			em->ReadObject(CR_DATADIR2"LunarnSlp.acf",CR_DATAFILE2,
//				crdataGetFileMode(),0);
			npDir(0,NORTH);
			npShow(0,0);

			npPos(9,16,21);
			npDir(9,NORTH);

			crfieldPaletteChange(PALETTE_NIGHT);

			evFieldNoFlip(0,1);
			evFadeIn(500);
//16,21,
			//---わあああああ
			for(b = 0;b < 1;b ++){
				mes.lpWin[0]->Clear();
				mes.lpWin[0]->Reset();
				mes.ReadMessage();
				et->Reset();
				for(a = 0;et->Get() < 3000 && crsysNotQuick();a ++){
					ef->Move(em,0);
					ef->MoveObject(em);
					crfieldDoAnime();
					crfieldDrawField(1);
					mes.lpWin[0]->Paint();
					mes.lpWin[0]->Draw(-1,0,0);
					mes.lpWin[0]->ResetReadBuffer();
					mes.lpWin[0]->ResetPos();
					ew->Flip();
					et->Delay(1);
				}
			}
			evFrameWait(2000,1);
			npDir(9,EAST);
			evFrameWait(3000,1);

			npPos(9,0,0);
			npShow(9,0);
//			em->ReloadPattern();
//			em->ReadObject(CR_DATADIR2"Lunarn.acf",CR_DATAFILE2,
//				crdataGetFileMode(),0);
//			crfieldPaletteChange(PALETTE_NIGHT);

			npDir(0,SOUTH);
			evFrameWait(2000,1);

			npDir(0,WEST);
			evFrameWait(1000,1);
			npDir(0,SOUTH);
			evFrameWait(1000,1);
			npDir(0,EAST);
			evFrameWait(1000,1);
			//---さっきのは・・・
			for(b = 0;b < 1;b ++){
				mes.lpWin[0]->Clear();
				mes.lpWin[0]->Reset();
				mes.ReadMessage();
				et->Reset();
				for(a = 0;et->Get() < 3000 && crsysNotQuick();a ++){
					ef->Move(em,0);
					ef->MoveObject(em);
					crfieldDoAnime();
					crfieldDrawField(1);
					mes.lpWin[0]->Paint();
					mes.lpWin[0]->Draw(-1,0,0);
					mes.lpWin[0]->ResetReadBuffer();
					mes.lpWin[0]->ResetPos();
					ew->Flip();

					et->Delay(1);
				}
			}
			evFrameWait(500,1);

			//---夢か・・・
			for(b = 0;b < 9;b ++){
				mes.lpWin[0]->Clear();
				mes.lpWin[0]->Reset();
				mes.ReadMessage();
				et->Reset();
				for(a = 0;et->Get() < ((b == 8) ? 3000 : 666) && crsysNotQuick();a ++){
//					et->Reset();
					ef->Move(em,0);
					ef->MoveObject(em);
					crfieldDoAnime();
					crfieldDrawField(1);
					mes.lpWin[0]->Paint();
					mes.lpWin[0]->Draw(-1,0,0);
					mes.lpWin[0]->ResetReadBuffer();
					mes.lpWin[0]->ResetPos();
					ew->Flip();

					et->Delay(1);
				}
			}
			//---ルナン甲板の先へ
			evFrameWait(1000,1);
			npDir(0,NORTH);
			evFrameWait(500,1);
			npMove(0,0,-1);
			evFrame(1);
			npMove(0,1,0);
			evFrame(1);
			npMove(0,1,0);
			evFrame(1);
			npDir(0,NORTH);
			evFrameWait(1000,1);
//			mcMove(1,0);
//			evFrame(1);
			evFrameWait(1000,1);
			for(b = 0;b < 1;b ++){
				//---手紙を・・・
				mes.lpWin[0]->Clear();
				mes.lpWin[0]->Reset();
				mes.ReadMessage();
				et->Reset();
				for(a = 0;et->Get() < 4000 && crsysNotQuick();a ++){
//					et->Reset();
					ef->Move(em,0);
					ef->MoveObject(em);
					crfieldDoAnime();
					crfieldDrawField(1);
					mes.lpWin[0]->Paint();
					mes.lpWin[0]->Draw(-1,0,0);
					mes.lpWin[0]->ResetReadBuffer();
					mes.lpWin[0]->ResetPos();
					ew->Flip();

					et->Delay(1);
				}
			}

			mes.CloseMessage();
			evFrameWait(1000);

			ef->SetBGCallback(NULL);
			evFadeOut(1000);
			crsoundStop(CRSOUND_GS_SOUND);

			//---回復
			prtRecoveryAll();
			//---マップロードし直す
			crfieldChangeMap(12,0,1,0);
			crfieldChangePos(38,16);
			evFieldNoFlip(0,1);
			crmusicPlay(CRMUSIC_FIELD1);
			evFadeIn();

			//---グラウンドシップ船着き場
			evFrameWait(2000,1);
			for(a = 0;a < 20;a ++){
				if(a < 11){
					npMove(4,0,1);
				} else if(a < 15){
					npMove(4,1,0);
				} else if(a == 18){
					npDir(4,WEST);
				}

				if(a < 4){
				} else if(a < 16){
					npMove(5,0,1);
				} else if(a < 19){
					npMove(5,1,0);
				}

				evFrame();
			}
			evFrameWait(500,1);
			//---ルナンが降りてくる
			for(a = 0;a < 34;a ++){
				if(a < 13){
					npMove(6,0,1);
				} else if(a < 15){
					npMove(6,1,0);
				} else if(a < 16){
					npMove(6,0,-1);
				} else if(a < 22){
					npMove(6,1,0);
				}

				if(a < 9){
				} else if(a < 23){
					npMove(8,0,1);
				} else if(a < 30){
					npMove(8,1,0);
				}

				if(a < 3){
				} else if(a < 17){
					npMove(7,0,1);
				} else if(a < 18){
					npMove(7,1,0);
				} else if(a < 19){
					npMove(7,0,1);
				} else {
					npMove(7,1,0);
				}

				evFrame(1);
			}

			for(a = 0;a < 6;a ++){
				mcMove(0,1);
				evFrame();
			}
			//---ふたりのはなし
//			mes.lpWin[0]->Clear();
//			mes.lpWin[0]->Reset();
			evFrameWait(500);
			mes.OpenMessage("Opening.msg",5);
			mes.ReadDraw(2);
			evFrameWait(500);

			npDir(4,SOUTH);
			evFrameWait(500,1);
			npDir(4,EAST);
			evFrameWait(250,1);
			npDir(4,NORTH);
			evFrameWait(500,1);
			npDir(4,WEST);
			evFrameWait(250,1);
			mes.ReadDraw(2);

			npDir(4,SOUTH);
			evFrameWait(500,1);
			npDir(4,EAST);
			evFrameWait(250,1);
			npDir(4,NORTH);
			evFrameWait(500,1);
			npDir(4,WEST);
			evFrameWait(250,1);
			mes.ReadDraw(2);
			evFrameWait(500);

			//---二人が去る
			for(a = 0;a < 16;a ++){
				npMove(4,1,0);
				npMove(5,1,0);
				evFrame();
			}
			npShow(4,0);
			npShow(5,0);
			npShow(7,0);

			//---サヴィアーとルナン
			for(a = 0;a < 3;a ++){
				mcMove(1,0);
				evFrame();
			}

			evFrameWait(500);
			mes.ReadDraw();
			evFrameWait(500,1);
			npDir(6,SOUTH);
			evFrameWait(250,1);
			npDir(6,WEST);
		evFrameWait(250,1);
		mes.ReadDraw(8);
		evFrameWait(500);

		mes.CloseMessage();

		//---サヴィアーゆく
		for(a = 0;a < 16;a ++){
			if(a < 1){
				npMove(8,0,1);
			} else {
				npMove(8,1,0);
			}
			evFrame();
		}
		evFrameWait(1000,1);
	//---ルナンもーゆく
	for(a = 0;a < 16;a ++){
		if(a < 1){
			npMove(6,0,1);
		} else {
			npMove(6,1,0);
		}
		evFrame();
	}

	//---アイテム設定、装備品
	pCharacterInfo[0].SetWeapon(0,1);
	pCharacterInfo[0].SetWeapon(1,0);
	pCharacterInfo[0].SetProtector(0,91);
	pCharacterInfo[0].SetProtector(1,0);
	pCharacterInfo[0].SetAccessory(0,0);
	pCharacterInfo[0].SetAccessory(1,0);
	pCharacterInfo[0].SetBattleFieldStartPos(6,3);

	for(a = 0;a < ITEM_MAX;a ++){
		pGameInfo->Item[a] = 0;
		pGameInfo->ItemCount[a] = 0;
	}
	pGameInfo->Item[0] = 221;
	pGameInfo->ItemCount[0] = 5;
	pGameInfo->Item[1] = 226;
	pGameInfo->ItemCount[1] = 2;
//	pGameInfo->Item[2] = 227;
//	pGameInfo->ItemCount[2] = 1;
	//---お金
	pGameInfo->Money = 50;

	//---場所移動
	crfieldChangeMapS(13,0,1);
	crfieldChangeSceneS(0,10,12);

	//---ルナンが来る
	evFrameWait(1000,1);
	for(a = 0;a < 10;a ++){
		npMove(7,1,0);
		evFrame();
	}
	npShow(7,0);
	npPos(7,0,0);
	mcShow(1);
	evFrame(1);

	return 0;
}

int creventWescaNForest1(void)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;

				crsoundPlay(CRSOUND_GASAGASA);
				for(a = 0;a < 2;a ++){
					mcMove(0,1);
					evFrame();
				}
				npDir(3,SOUTH);
				evFrameWait(150,1);
				npDir(3,EAST);
				evFrameWait(100,1);
				mes.OpenMessage("WescaNForest.msg",105);
				mes.ReadDraw(3);
				//---ほーほけきょ
				evFrameWait(1000,1);
				mcDir(WEST);
				evFrameWait(500,1);
				mes.ReadDraw();
				evFrameWait(1000,1);
				mes.ReadDraw(2);
				//---だれだー！？
				evFrameWait(1500,1);
				mes.ReadDraw();
				evFrameWait(250);

				int old = mcSpeed(2);
				for(a = 0;a < 6;a ++){
					if(a < 1)
						npMove(3,0,1);
					else if(a < 5)
						npMove(3,1,0);
					else
						npDir(3,SOUTH);

					if(a < 2)
						npMove(2,1,0);
					else if(a < 3)
						npMove(2,0,1);
					else
						npMove(2,1,0);

					if(a < 3){
					} else if(a < 6){
						mcMove(0,1);
					}
					evFrame();
				}
				//---にげろー
				evFrameWait(250);
				mes.ReadDraw();
				evFrameWait(250);
				mcSpeed(old);
				for(a = 0;a < 25;a ++){
					if(a < 1)
						mcMove(0,1);
					else if(a < 12)
						mcMove(-1,0);
					else if(a < 14)
						mcMove(0,-1);
					else if(a < 20)
						mcMove(-1,0);
					else if(a < 21)
						mcMove(0,-1);
					else if(a < 25)
						mcMove(-1,0);
					evFrame();
				}
				//---行き止まりさ
				mcShow(0);
				evScene(1,17,11);
				for(a = 0;a < 4;a ++){
					npPos(a,14,19);
					npShow(a,1);
				}
				npPos(1,12,10);
				for(a = 0;a < 25;a ++){
					if(a < 1)
						npMove(0,0,-1);
					else if(a < 4)
						npMove(0,1,0);
					else if(a < 15)
						npMove(0,0,-1);
					else if(a < 16){
//						evFrameWait(250);
						mes.ReadDraw();
						npDir(0,WEST);
					} else
						npDir(0,SOUTH);

					if(a < 10){
					} else if(a < 11)
						npMove(2,0,-1);
					else if(a < 14)
						npMove(2,1,0);
					else if(a < 22)
						npMove(2,0,-1);

					if(a < 13){
					} else if(a < 14)
						npMove(3,0,-1);
					else if(a < 17)
						npMove(3,1,0);
					else if(a < 23)
						npMove(3,0,-1);
					else if(a < 24)
						npMove(3,-1,0);
					else if(a < 25)
						npMove(3,0,-1);
					evFrame();
				}
				evFrameWait(250);
				mes.ReadDraw(3);
				evFrameWait(250);
				for(a = 0;a < 2;a ++){
					if(a < 1)
						npMove(3,0,-1);
					else
						npDir(3,EAST);
					evFrame();
				}
				evFrameWait(250);
				mes.ReadDraw(3);
				evFrameWait(1000,1);
				mes.ReadDraw(2);

				//---小悪党
				evFrameWait(1000,1);
				mes.ReadDraw();

				evFrameWait(500);
				npDir(3,EAST);
				evFrameWait(250);
				npDir(3,NORTH);
				evFrameWait(250);
				npDir(3,WEST);
				evFrameWait(250);
				mes.ReadDraw();

				evFrameWait(1000,1);
				mes.ReadDraw();

				evFrameWait(500);
				npDir(2,EAST);
				evFrameWait(250);
				npDir(2,NORTH);
				evFrameWait(250);
				npDir(2,WEST);
				evFrameWait(250);
				npDir(2,NORTH);
				evFrameWait(250);
				mes.ReadDraw();

				//---やめておくんだな！！
				evFrameWait(1000);
				mes.ReadDraw();

				npDir(2,EAST);
				evFrameWait(250);
				npDir(2,NORTH);
				evFrameWait(250);
				npDir(2,WEST);
				evFrameWait(250);
				npDir(2,NORTH);
				evFrameWait(250);
				mes.ReadDraw();

				//---がさがさ
				crsoundPlay(CRSOUND_GASAGASA);
				evFrameWait(250);
				npDir(2,WEST);
				crsoundPlay(CRSOUND_GASAGASA);
				evFrameWait(250);
				npDir(0,WEST);
				crsoundPlay(CRSOUND_GASAGASA);
				for(a = 0;a < 3;a ++){
					if(a < 2)
						npMove(1,0,-1);
					else
						npDir(1,EAST);
					evFrame();
				}
				evFrameWait(2000);
				mes.ReadDraw();
				evFrameWait(250);
				for(a = 0;a < 5;a ++){
					crsoundPlay(CRSOUND_GASAGASA);
					if(a < 1)
						npMove(1,0,1);
					else if(a < 4)
						npMove(1,1,0);
					evFrame();
				}
				evFrameWait(1000);
				mes.ReadDraw();

				evFrameWait(500);
				npDir(3,NORTH);
				evFrameWait(250);
				npDir(3,EAST);
				evFrameWait(250);
				mes.ReadDraw();

				evFrameWait(500);
				mes.ReadDraw();

				//---おれたちゃエターナルなのねん
				evFrameWait(500);
				npDir(3,NORTH);
				evFrameWait(250);
				npDir(3,WEST);
				evFrameWait(250);
				mes.ReadDraw();
				evFrameWait(250);

				for(a = 0;a < 2;a ++){
					if(a < 1)
						npMove(2,0,-1);
					else
						npDir(2,WEST);
					evFrame();
				}

				npDir(0,SOUTH);
				evFrameWait(250);

				mes.ReadDraw(3);

				evFrameWait(500);
				mes.ReadDraw();
				evFrameWait(250);
				for(a = 0;a < 1;a ++){
					npMove(1,1,0);
					npDir(3,NORTH);
					evFrame();
				}
				//---ぼこぼこ
				for(a = 0;a < 6;a ++){
					crsoundPlay(CRSOUND_ATACK2);

					evReset();
					evFill(ep->MakeRGB(255,255,255));
					ew->Flip();
					evWait(20,0);

					evReset();
					evField(0,1);
					evWait(130,0);

					if(a == 3){
						npMove(2,1,0,0);
						evFrame();
						npDir(1,SOUTH);
					}
					if(a == 5){
						npMove(3,0,1,0);
						evFrame();
					}
				}
				evFrameWait(250);
				for(a = 0;a < 3;a ++){
					if(a < 1)
						npMove(2,-1,0);
					else
						npMove(2,0,1);
					evFrame();
				}
				npDir(2,WEST);
				evFrameWait(250);
				npDir(2,NORTH);
				evFrameWait(250);
				mes.ReadDraw();

				//---しかし・・・本部へは？？
				evFrameWait(250);
				npDir(3,EAST);
				evFrameWait(250);
				mes.ReadDraw();

				evFrameWait(2000);
				npDir(2,WEST);
				evFrameWait(1000);
				mes.ReadDraw();
				evFrameWait(500);

				//---たいさーん
				for(a = 0;a < 16;a ++){
					npMove(2,0,1);
					if(a < 1)
						npMove(3,1,0);
					else
						npMove(3,0,1);
					evFrame();
				}

				//---うどんよ、うどん
				evFrameWait(250);
				mes.ReadDraw();
				evFrameWait(1000);
				mes.ReadDraw();
				evFrameWait(250);

				for(a = 0;a < 2;a ++){
					if(a < 1)
						npMove(1,1,0);
					else
						npDir(1,NORTH);
					evFrame();
				}
				npDir(1,EAST);
				evFrameWait(250);
				npDir(1,NORTH);
				evFrameWait(250);
				mes.ReadDraw(2);

				evFrameWait(500);
				mes.ReadDraw(2);

				mes.CloseMessage();

				evFrameWait(1000);

				mes.CreateNewMessage(0, 48,-1,16,-1);
				mes.CreateNewMessage(1,320,-1,17,-1);
				mes.OpenMessage("WescaNForest.msg",106,0);
				mes.OpenMessage("WescaNForest.msg",107,1);
				mes.ReadMessage(1,0);
				mes.ReadMessage(1,1);
				mes.Draw();
				mes.ReadMessage(1,0);
				mes.ReadMessage(1,1);
				evFrameWait(3000);
				mes.Draw();
				mes.CloseMessage(1);
				mes.CloseMessage(0);

				evFrameWait(250);
				npPos(0,17,10);
				npDir(0,NORTH);
				npPos(1,17,9);
				npDir(1,SOUTH);
				evScene(1,17,11);
				mes.OpenMessage("WescaNForest.msg",108);
				mes.ReadDraw(4);
				evFrameWait(500);
				mes.CloseMessage();

				mcShow(1);
				mcDir(SOUTH);
				evScene(2,61,12);

	//---ディザ仲間になる
	{
		pPartyInfo->PartyMember[1] = 1;
		crcharaSetLevelStatus(1,2);
		CrCharacter *pChara = crcharaGetPartyMember(1);
		pChara->SetWeapon(0,10);
		pChara->SetWeapon(1,0);
		pChara->SetProtector(0,100);
		pChara->SetProtector(1,0);
		pChara->SetAccessory(0,0);
		pChara->SetAccessory(1,0);
		pChara->SetBattleFieldStartPos(4,4);
		pChara->SetLevelExperience();
		crcharaLoadFace(-1);
		crcharaCheckBattleFieldPos(1);
	}

	prtRecovery(1);

	return 0;
}

//---セーネの宿屋
int callbackSene(void)
{
	int a;
	CrMesManager mes;

	crfieldPaletteChange(PALETTE_NIGHT);
	mcShow(0);
	crmusicFadeOut();
	crfieldChangeScene(1,5,10);

	npShow(1,1);
	npDir(1,SOUTH);
	npPos(1,5,6);
	et->Delay2(1000);

	evFieldNoFlip(0,1);
	evFadeIn(500);

	evFrameWait(2000,1);
	crmusicStop();
	npDir(1,WEST);
	evFrameWait(1000,1);
	mes.OpenMessage("Sene.msg",100);
	mes.ReadDraw(3);
	evFrameWait(1000,1);

	em->ReloadPattern();
	mcDir(NORTH);
	npPos(1,0,0);
	npShow(1,0);
	mcShow(1);

	//---夜が明ける
	evScene(0,41,13);
	crmusicPlay(CRMUSIC_TOWN1,1,CRMUSIC_LOADFORCE);
	npPos(23,38,26);
	npPos(24,37,26);
	npDir(23,WEST);
	npDir(24,EAST);

	evFrameWait(250);
	mes.ReadDraw();
	evFrameWait(500,1);
	mes.ReadDraw();
	mcDir(EAST);
	evFrameWait(250,1);
	mcDir(SOUTH);
	evFrameWait(250,1);
	mes.ReadDraw();
	evFrameWait(250);

	for(a = 0;a < 10;a ++){
		if(a < 3)
			mcMove(-1,0);
		else
			mcMove(0,1);
		evFrame();
	}
	evFrameWait(250);
//--------------------------------
	int x = ef->xGet(),y = ef->yGet();
	npPos(27,x,y);
	npDir(27,SOUTH);
	mcShow(0);
	evFrameWait(250);

	for(a = 0;a < 5;a ++){
		mcMove(0,1);
		evFrame();
	}
	evFrameWait(500);
	mes.ReadDraw(3);
	evFrameWait(500);
	for(a = 0;a < 5;a ++){
		npMove(27,0,1);
		evFrame();
	}
	evFrameWait(500);
//--------------------------------

/*	mes.ReadDraw(3);
	for(a = 0;a < 5;a ++){
		mcMove(0,1);
		evFrame();
	}*/

	mes.ReadDraw(2);
	evFrameWait(250,1);
	npDir(23,NORTH);
	evFrameWait(250,1);
	mes.ReadDraw();
	evFrameWait(250);
	npDir(23,WEST);

	mes.CloseMessage();
	evSet(17,2);


	npDelete(27);
	mcShow(1);
	mcDir(SOUTH);

	return 0;
}

//---セーネ・アネート間ディザとの会話
void SeneAneatDangeon(void)
{
	int a;
	CrMesManager mes;

	mcShow(0);
	evScene(5,10,15);
	npPos(0,10,12);
	npPos(1,10,12);

	evFrameWait(500);
	for(a = 0;a < 5;a ++){
		if(a < 1)
			npShow(1,1);
		if(a < 3)
			npMove(1,0,1);

		if(a == 3)
			npShow(0,1);
		if(a >= 2 && a < 4)
			npMove(0,0,1);

		evFrame();
	}
	evFrameWait(500);

	mes.OpenMessage("ToAneatWay.msg",100);

	mes.ReadDraw();
	evFrameWait(500);
	npDir(1,WEST);
	evFrameWait(300);
	npDir(1,NORTH);
	evFrameWait(500);
	mes.ReadDraw(12);
	evFrameWait(1000);
	mes.ReadDraw(5);

	mes.CloseMessage();

	evFrameWait(500);
	npDir(1,WEST);
	evFrameWait(300);
	npDir(1,SOUTH);
	evFrameWait(500);

	for(a = 0;a < 15;a ++){
		npMove(1,0,1);
		if(a >= 1)
			npMove(0,0,1);
		evFrame();
	}

	mcDir(SOUTH);
	mcShow(1);
	evMap(10,0,112,209);
}
