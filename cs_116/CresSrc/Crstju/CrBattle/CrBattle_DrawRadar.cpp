//------------------------------------
//---レーダー

//---キャラクターを描く
CRBATTLEDRAW_API int crbatDrawRadar_Character(int tx,int ty)
{
	int sx,sy;
	int size = BATTLEFIELD_PTN_PIXELSIZE;
	double rate = 0.50;
	eiCell *pCell = ew->lpCell[1];//&BattleRadarCell;

	for(int a = 0;a < BATTLECHARA_MAX;a ++){
		if(pBtChara[a].DoExist()){
			sx = CRBAT_TRANSLATE_CHARA_X(pBtChara[a].GetFieldX());
			sy = CRBAT_TRANSLATE_CHARA_Y(pBtChara[a].GetFieldY());

			sx = ((sx * size) + (size / 2))
				- (int)(((double)pBtChara[a].GetCharaWidth() * rate) / 2);
			sy = ((sy * size) + (size / 2))
				- (int)(((double)pBtChara[a].GetCharaHeight() * rate) / 2);

//			if(pBtChara[a].GetCharaWidth())
//				rate = 16.000 / (double)pBtChara[a].GetCharaWidth();

			pBtChara[a].GetCell()->PutExtend(
				pCell,
				sx + tx,sy + ty,
				rate,rate,EI_TRANS);
		}
	}

	return 1;
}

//---フィールドを描く
CRBATTLEDRAW_API int crbatDrawRadar_Field(int tx,int ty)
{
	int sx,sy;
	eiCell *pCell = ew->lpCell[1];//&BattleRadarCell;
	RECT rect = {1,1,16,16};//---ミレニアムのバグのため(^^;

	if(tx == -1)
		tx = BATTLE_RADAR_X;
	if(ty == -1)
		ty = BATTLE_RADAR_Y;

	for(sy = 0;sy < BATTLEFIELD_MAX_Y;sy ++){
		for(sx = 0;sx < BATTLEFIELD_MAX_X;sx ++){
			BattleFieldCell[BattleField[(BATTLEFIELD_MAX_X - 1)- sx][sy].TextureNumber].PutExtend(
				pCell,
				tx + (sx * BATTLEFIELD_PTN_PIXELSIZE),
				ty + (sy * BATTLEFIELD_PTN_PIXELSIZE),0.50,0.50,
				EI_PSET,&rect);
/*			BattleFieldCell[BattleField[sx][sy].TextureNumber].Put(
				pCell,
				tx + (sx * BATTLEFIELD_PTN_PIXELSIZE),
				ty + (sy * BATTLEFIELD_PTN_PIXELSIZE));*/
		}
	}

	return 1;
}

//---レーダー上にカーソルが現れる
CRBATTLEDRAW_API int crbatDrawRadar_Appeare(CrBattleCharacter *pChara,int run_time /*= 250*/,int tx /*= -1*/,int ty /*= -1*/)
{
	return crbatDrawRadar_Cursor(pChara,tx,ty);
}

//---レーダー上にカーソルを描く
CRBATTLEDRAW_API int crbatDrawRadar_Cursor(CrBattleCharacter *pChara,int tx /*= -1*/,int ty /*= -1*/)
{
	int sx[2],sy[2],dx,dy,ex,ey;
	double rate = 0.500;
	int size = BATTLEFIELD_PTN_PIXELSIZE;

	if(tx == -1)
		tx = BATTLE_RADAR_X;
	if(ty == -1)
		ty = BATTLE_RADAR_Y;

	sx[0] = sx[1] = CRBAT_TRANSLATE_CHARA_X(pChara->GetFieldX());
	sy[0] = sy[1] = CRBAT_TRANSLATE_CHARA_Y(pChara->GetFieldY());
	sx[0] = ((sx[0] * size) + (size / 2))
		- (int)(((double)pChara->GetCharaWidth() * rate) / 2);
	sy[0] = ((sy[0] * size) + (size / 2))
		- (int)(((double)pChara->GetCharaHeight() * rate) / 2);
	sx[1] = ((sx[1] * size) + (size / 2))
		+ (int)(((double)pChara->GetCharaWidth() * rate) / 2);
	sy[1] = ((sy[1] * size) + (size / 2))
		+ (int)(((double)pChara->GetCharaHeight() * rate) / 2);

	sx[0] -= 8;
	sy[0] -= 8;
	sx[1] -= 8;
	sy[1] -= 8;

	dx = (sx[1] - sx[0]) - 8;
	dy = (sy[1] - sy[0]) - 8;

	pBattleCursorCell[0].PutTrans(ew->lpCell[1],sx[0] + tx,sy[0] + ty);
	pBattleCursorCell[1].PutTrans(ew->lpCell[1],sx[1] + tx,sy[0] + ty);
	pBattleCursorCell[2].PutTrans(ew->lpCell[1],sx[0] + tx,sy[1] + ty);
	pBattleCursorCell[3].PutTrans(ew->lpCell[1],sx[1] + tx,sy[1] + ty);

	for(ex = 0;ex < dx;ex += 16){
		for(ey = 0;ey < dy;ey += 16){
			pBattleCursorCell[4].PutTrans(ew->lpCell[1],
				(sx[0] + 8) + ex + tx, (sy[0] + 8) + ey + ty);
		}
	}

	return 1;
}

//---レーダー画面に範囲表示
CRBATTLEDRAW_API int crbatDrawRadar_Range(int x,int y,int tx /*= -1*/,int ty /*= -1*/)
{
	if(tx == -1)
		tx = BATTLE_RADAR_X;
	if(ty == -1)
		ty = BATTLE_RADAR_Y;

	pBattleCursorCell[5].PutTrans(
		ew->lpCell[1],
		tx + (CRBAT_TRANSLATE_CHARA_X(x) * BATTLEFIELD_PTN_PIXELSIZE),
		ty + (CRBAT_TRANSLATE_CHARA_Y(y) * BATTLEFIELD_PTN_PIXELSIZE));
	return 1;
}

//---レーダーを描く
CRBATTLEDRAW_API int crbatCreateRadar(int tx /*= -1*/,int ty /*= -1*/)
{
	if(tx == -1)
		tx = BATTLE_RADAR_X;
	if(ty == -1)
		ty = BATTLE_RADAR_Y;

	//---消す
	ew->lpCell[1]->DrawFillBox(
		tx - 24,
		ty - 24,
		tx + (BATTLEFIELD_MAX_X * BATTLEFIELD_PTN_PIXELSIZE) + 24,
		ty + (BATTLEFIELD_MAX_Y * BATTLEFIELD_PTN_PIXELSIZE) + 24,
		ep->ToRGB(CRCOLOR_BLACK));

	crbatDrawRadar_Field(tx,ty);
	crbatDrawRadar_Character(tx,ty);

	return 1;
}

//---描いてあったレーダーをコピーする
CRBATTLEDRAW_API int crbatDrawRadar(int tx /*= -1*/,int ty /*= -1*/)
{
	return crbatCreateRadar(tx,ty);

/*	if(tx == -1)
		tx = BATTLE_RADAR_X;
	if(ty == -1)
		ty = BATTLE_RADAR_Y;

	BattleRadarCell.Put(ew->lpCell[1],tx,ty);

	return 1;*/
}
