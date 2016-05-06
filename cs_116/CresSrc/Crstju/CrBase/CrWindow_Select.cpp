//---SelectWindow--------------------------
CrSelectWindow::CrSelectWindow(int font /*= EINORMAL_FONT*/,
	int style /*= CRWIN_DEFAULT | CRWIN_CHANGEPAGE*/,int ptn /*= 0*/,int alpha /*= 175*/) : CrStringWindow(font,style,ptn,alpha)
{
	lpSelectCallBack = NULL;
	lpDrawTextCallBack = NULL;

	CursorNumber = 0;
	AnimeNumber = 0;
	AnimeWait = 100;
	SaveBGNumber = 15;

	Page = 0;
}

CrSelectWindow::~CrSelectWindow()
{
}

int CrSelectWindow::Create(int tx,int ty,int sx,int sy,
						   eistr *title ,eistr *string,int horizon /* = 1*/,int h_size /*= 0*/)
{
	int ret;

	lpMenuString = string;
	lpMenuTitle = title;
	Horizon = horizon;
	HorizonSize = h_size;

	ret = CrStringWindow::Create(tx,ty,sx,sy);

	return ret;
}

void CrSelectWindow::SetMenuString(eistr *string)
{
	lpMenuString = string;
}

//---メニューを描く
void CrSelectWindow::DrawMenu(void)
{
	int index = 0,x = 0,y = 0,max_length = 0;
	int page = GetDrawPage();
	eistr *string = lpMenuString;
	eistr s[80],*p = &s[0];

	//---メニュー解析
	while(*string){
		p = &s[0];
		while(*string != ';' && *string != NULL){
			*p = *string;
			p ++;
			string ++;
		}
		if(*string == NULL)
			break;
		*p = 0;
		if(lpDrawTextCallBack){
			//---フック関数に渡す
			(*lpDrawTextCallBack)(ew->lpCell[page],&s[0],
				Top.x + CRWIN_FRAMESIZE + (HorizonSize * xSize * x)
					+ (CRWIN_SELECT_HSPACE * (x + 1)) + (CRWIN_SELECT_HEMPTY * x),
				Top.y + CRWIN_FRAMESIZE + (y * LineSize) + CRWIN_SELECT_VERTOFFSET,
				ep->ToTextRGB(CRCOLOR_WHITE),Data);
		} else {
			//---メニュー描画
/*			ew->lpCell[page]->DrawText(&s[0],
				Top.x + CRWIN_FRAMESIZE + (HorizonSize * xSize * x)
					+ (CRWIN_SELECT_HSPACE * (x + 1)) + (CRWIN_SELECT_HEMPTY * x),
				Top.y + CRWIN_FRAMESIZE + (y * LineSize) + CRWIN_SELECT_VERTOFFSET,
				ep->ToTextRGB(CRCOLOR_WHITE));
*/
//////////////////////////////////////////
			char str[4];
			int sx = 0,size,col = CRCOLOR_WHITE,
				table[] = {CRCOLOR_BLACK,CRCOLOR_BLUE,CRCOLOR_RED,CRCOLOR_PURPLE,
				CRCOLOR_GREEN,CRCOLOR_AQUA,CRCOLOR_YELLOW,CRCOLOR_WHITE};

			p = &s[0];
			if((int)strlen(p) > max_length)
				max_length = strlen(p);

			while(*p){
				if(_ismbblead((unsigned int)(*p))){
					//---2
					str[0] = *p;
					str[1] = *(p + 1);
					str[2] = 0;
					size = 2;
				} else {
					//---1
					if(*p == '\\'){
						p ++;
						col = table[*p - '0'];
						p ++;
						continue;
					} else {
						str[0] = *p;
						str[1] = 0;
						size = 1;
					}
				}
				ew->lpCell[page]->DrawText(str,
					(sx * 8) + Top.x + CRWIN_FRAMESIZE + (HorizonSize * xSize * x)
						+ (CRWIN_SELECT_HSPACE * (x + 1)) + (CRWIN_SELECT_HEMPTY * x) + 1,
					Top.y + CRWIN_FRAMESIZE + (y * LineSize) + CRWIN_SELECT_VERTOFFSET + 1,
					ep->ToTextRGB(CRCOLOR_BLACK));
				ew->lpCell[page]->DrawText(str,
					(sx * 8) + Top.x + CRWIN_FRAMESIZE + (HorizonSize * xSize * x)
						+ (CRWIN_SELECT_HSPACE * (x + 1)) + (CRWIN_SELECT_HEMPTY * x),
					Top.y + CRWIN_FRAMESIZE + (y * LineSize) + CRWIN_SELECT_VERTOFFSET,
					ep->ToTextRGB(col));

				p += size;
				sx += size;
			}
//////////////////////////////////////////
		}

		string ++;
		index ++;
		if(++x >= Horizon){
			x = 0;
			y ++;
		}
	}
	//---メニューの上限
	MenuCount = index;

	if(HorizonSize == 0)
		HorizonSize = max_length;
}

void CrSelectWindow::Paint(void)
{
	CrStringWindow::Paint();

	//---タイトルがあれば描く
	if(lpMenuTitle){
		if(strlen(lpMenuTitle)){
			int old = eiSetFont(EISMALL_FONT);

			ew->lpCell[GetDrawPage()]->DrawFillBox(
				Top.x + CRWIN_FRAMESIZE,
				Top.y,
				Top.x + CRWIN_FRAMESIZE + strlen(lpMenuTitle) * 6,
				Top.y + 11,ep->ToTextRGB(CRCOLOR_BLACK));
			ew->lpCell[GetDrawPage()]->DrawText(lpMenuTitle,
				Top.x + CRWIN_FRAMESIZE ,
				Top.y,
				ep->ToTextRGB(CRCOLOR_WHITE));

			eiSetFont(old);
		}
	}
	DrawMenu();
	//---コールバック呼び出し
	if(lpSelectCallBack){
		(*lpSelectCallBack)(this,ew->lpCell[1],CRWIN_SELECT_MESPAINT,Data,Top.x,Top.y);
	}
}

//---メニュー選択
int CrSelectWindow::Select(CRWIN_SELECTINFO *pInfo /* = NULL*/)
{
	CrInput crin;
	eiTime let;

	int c,flag;
	int first = 1,ret = -1,index = 0,x = 0,y = 0,hx = -1,hy = -1;
	int max_x = Horizon,
		max_y = (MenuCount / Horizon) + (MenuCount % Horizon ? 1 : 0);

//	SaveCursorBG(index);
//	DrawCursor(index);
//	DrawSelectIndex(index);

	//---一回空読み
	crin.Get();
	let.Reset();
	while(1){
		crin.Get();

		if(lpSelectCallBack){
			(*lpSelectCallBack)(this,ew->lpCell[1],CRWIN_SELECT_IDLE,0,Data,0);
		}
		if(first){
			//---初回のみ・・・ここでオフセット位置とかを決める
			x = 0;
			y = 0;

			if(pInfo != NULL){
				//---情報があればオフセット位置
				x = (pInfo->Offset % Horizon);
				y = pInfo->Offset / Horizon;
				Page = pInfo->Page;

				if(x >= max_x)
					x = 0;
				if(y >= max_y)
					y = 0;
			}
		}

		if(!first){
			if(crin.IsButton(0)){
				//---キャンセル
				crsoundPlay(CRSOUND_BTN_A);
				ret = -1;
				break;
			}
			if(crin.IsButton(1) && x + (y * Horizon) < MenuCount){
				//---決定
				crsoundPlay(CRSOUND_BTN_B);
				ret = x + (y * Horizon);
				break;
			}
			//---
			if(crin.IsUp()){
				y --;
			}
			if(crin.IsDown()){
				y ++;
			}
			if(crin.IsLeft()){
				x --;
			}
			if(crin.IsRight()){
				x ++;
			}
		}

		//---ページ切り替えがある場合
		flag = 0;
		if((x < 0 || x >= max_x)
			&& lpSelectCallBack /*&& (Style & CRWIN_CHANGEPAGE)*/){
			if(x < 0)
				c = -1;
			else
				c = 1;

			flag = (*lpSelectCallBack)(this,ew->lpCell[1],CRWIN_SELECT_MESCHANGEPAGE,(ei_u32)&Page,Data,c);
		}
		//----座標補正
		//---ページ切り替えが発生しなかった場合
		if(x < 0){
			x = max_x - 1;
		}
		if(x >= max_x){
			x = 0;
		}

		if(y < 0){
			y = max_y - 1;
		}
		if(y >= max_y){
			y = 0;
		}
		if(x + y * max_x >= MenuCount){
			x = hx;
			y = hy;
		}

		if(hx != x || hy != y || flag){
			//---動いたら
			if(hx != -1 && hy != -1){
				//---前の位置を消す
				EraseSelectIndex(hx + (hy * Horizon));
				LoadCursorBG(hx + (hy * Horizon));
			}

			index = x + (y * Horizon);
			//---カーソル
			SaveCursorBG(index);
			AnimeCursor(&let);
			DrawCursor(index);
			//---メニュー
			DrawSelectIndex(index);

			if(lpSelectCallBack){
				//---コールバック関数が設定されているなら呼び出す
				(*lpSelectCallBack)(this,ew->lpCell[1],CRWIN_SELECT_MESMOVECURSOR,(ei_u32)&Page,Data,index);
				(*lpSelectCallBack)(this,ew->lpCell[1],CRWIN_SELECT_MESSHOWHELP,(ei_u32)&Page,Data,index);
			}
			if(lpPaintFunc){
				(*lpPaintFunc)(ew->lpCell[1]);
			}
		} else if(AnimeCursor(&let)){
			//---カーソルアニメーション
			LoadCursorBG(index);
			DrawCursor(index);
			if(!eiGetFullScreen()){
				DrawSelectIndex(index);
			}
		}

		hx = x;
		hy = y;

		if(!first)
			eiSleep(1);
		first = 0;
	}

	if(pInfo && ret != -1){
		//---カーソル情報保存
		pInfo->Offset = x + (y * Horizon);
		pInfo->Page = Page;
	}

	return ret;
}

//---選択中のメニュー
void CrSelectWindow::DrawSelectIndex(int index)
{
	int x,y,tx,ty,page = 0;

	x = index % Horizon;
	y = index / Horizon;

	tx = Top.x + CRWIN_FRAMESIZE + (HorizonSize * xSize * x)
				+ (CRWIN_SELECT_HSPACE * (x + 1)
				+ (CRWIN_SELECT_HEMPTY * x));
	ty = Top.y + (CRWIN_FRAMESIZE + CRWIN_SELECT_VERTOFFSET) + (y * LineSize) + ySize;

	ew->lpCell[page]->DrawFillBox(
		tx,ty,tx + (xSize * HorizonSize),ty,ep->ToRGB(CRCOLOR_WHITE));
}

void CrSelectWindow::EraseSelectIndex(int index)
{
	int x,y,tx,ty,page = 0;

	x = index % Horizon;
	y = index / Horizon;

	tx = Top.x + CRWIN_FRAMESIZE + (HorizonSize * xSize * x)
				+ (CRWIN_SELECT_HSPACE * (x + 1)
				+ (CRWIN_SELECT_HEMPTY * x));
	ty = Top.y + (CRWIN_FRAMESIZE + CRWIN_SELECT_VERTOFFSET) + (y * LineSize) + ySize;

	RECT rect = {tx,ty,tx + (xSize * HorizonSize) + 1,ty + 1};

	if(eiGetFullScreen()){
		ew->lpCell[1]->PutClip(ew->lpCell[0],tx,ty,&rect);
	} else {
		ew->Refresh();
//		ew->lpCell[1]->PutExtend(ew->lpCell[0],tx,ty,
//			1.000,1.000,EI_PSET,&rect);
	}
}

//------------------------
//---カーソル
int CrSelectWindow::xGetCursor(int index)
{
	return Top.x + CRWIN_FRAMESIZE + (HorizonSize * xSize * (index % Horizon))
		+ (CRWIN_SELECT_HSPACE * (index % Horizon) + (CRWIN_SELECT_HEMPTY * (index % Horizon)));
}

int CrSelectWindow::yGetCursor(int index)
{
	return Top.y + (CRWIN_FRAMESIZE + CRWIN_SELECT_VERTOFFSET) + ((index / Horizon) * LineSize);
}

void CrSelectWindow::SaveCursorBG(int index)
{
	int tx = xGetCursor(index),ty = yGetCursor(index);
	RECT rect = {tx,ty,tx + 16,ty + 16};

	ew->lpCell[1]->PutClip(&pMenuCursorCell[SaveBGNumber],0,0,&rect);
}

void CrSelectWindow::LoadCursorBG(int index)
{
	int tx = xGetCursor(index),ty = yGetCursor(index);
	RECT rect = {tx,ty,tx + 16,ty + 16};

	pMenuCursorCell[SaveBGNumber].PutClip(ew->lpCell[1],tx,ty);

	if(eiGetFullScreen()){
//		ew->lpCell[1]->PutClip(ew->lpCell[0],tx,ty,&rect);

/*2000/9/9
		eiDDSurface *pSurface = eiGetSurfacePointer();
		pSurface[1].PutExtend2(&pSurface[0],&rect,&rect,DDBLT_WAIT);
*/
		ew->lpCell[1]->Copy(ew->lpCell[0],rect.left,rect.top,&rect);
	}
}

//---カーソルを描く
void CrSelectWindow::DrawCursor(int index)
{
	int tx = xGetCursor(index),ty = yGetCursor(index),page = 0;
	RECT rect = {tx,ty,tx + 16,ty + 16};

	pMenuCursorCell[AnimeNumber].PutTransClip(ew->lpCell[1],tx,ty);

	if(eiGetFullScreen()){
/*2000/9/9
		eiDDSurface *pSurface = eiGetSurfacePointer();
		pSurface[1].PutExtend2(&pSurface[0],&rect,&rect,DDBLT_WAIT);
*/
		ew->lpCell[1]->Copy(ew->lpCell[0],rect.left,rect.top,&rect);

//		ew->lpCell[1]->PutClip(ew->lpCell[0],tx,ty,&rect);
	} else {
		ew->Refresh();
	}
}

//---カーソルアニメーション
int CrSelectWindow::AnimeCursor(eiTime *let)
{
	if(let->Get() >= AnimeWait){
		let->Reset();
		if(++AnimeNumber >= CRWIN_SELECT_CURSORANIMEMAX){
			AnimeNumber = 0;
		}
		return 1;
	}
	return 0;
}

//---選択コールバック
int CrSelectWindow::SetSelectCallBack(int (*lpFunc)(CrSelectWindow *,eiCell *,int,ei_u32,ei_u32,int))
{
	lpSelectCallBack = lpFunc;

	return 1;
}

//---メニュー描画コールバック
int CrSelectWindow::SetDrawTextCallBack(void (*lpFunc)(eiCell *,eistr *,int ,int ,int ,ei_u32))
{
	lpDrawTextCallBack = lpFunc;

	return 1;
}
