#define FONT_WIDTH 8
#define FONT_HEIGHT 16

//---指定された位置にウィンドウを作る
CRBATTLEDRAW_API void crbatBWCreate(CrStringWindow *pWin,eistr *pString,
				int pos /*= BW_CENTER | BW_TOP*/,int camera /*= 0*/)
{
	int x = 0,y = 0,tx,ty,cx,cy,str_x,str_y;

	str_x = (strlen(pString) * FONT_WIDTH / 16) + 2;
	str_y = 1;
	tx = BattleViewRect[BattleViewMode][camera].left;
	ty = BattleViewRect[BattleViewMode][camera].top;
	cx = BattleViewRect[BattleViewMode][camera].right;
	cy = BattleViewRect[BattleViewMode][camera].bottom;

	if(pos & BW_CENTER){
		x = tx + (cx / 2) - (str_x * 16 / 2);
		y = ty + (cy / 2) - (str_y * 16 / 2);
	}
	if(pos & BW_LEFT){
		x = tx + 16;
	}
	if(pos & BW_RIGHT){
		x = (tx + cx - 16)  - (str_x * 16);
	}
	if(pos & BW_TOP){
		y = ty + 16;
	}
	if(pos & BW_BOTTOM){
		y = (ty + cy - 16)  - (str_y * 16);
	}

	pWin->SetOffset(((str_x * 16) - (strlen(pString) * FONT_WIDTH)) / 2,
		18 + (FONT_HEIGHT == 16 ? 2 : 0));
	pWin->Create(x,y,str_x,str_y);
	pWin->DrawText(pString);
}
