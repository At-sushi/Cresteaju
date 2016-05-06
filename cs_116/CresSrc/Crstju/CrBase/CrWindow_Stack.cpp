
CrStackWindow::CrStackWindow(int font /*= EINORMAL_FONT*/,int style /*= CRWIN_DEFAULT */,
							 int ptn /*= 0*/,int alpha/* = 191*/)
							 : CrSelectWindow(font,style,ptn,alpha)
{
	eimemset(MenuFlag,0,sizeof(MenuFlag));
	eimemset(MenuString,0,sizeof(MenuString));
	eimemset(pMenuStart,0,sizeof(pMenuStart));

	int a;
	for(a = 0;a < 16;a ++){
		Stack[a] = -1;
	}

	MenuString[0] = NULL;
	EndString[0] = NULL;

	pStackStart = NULL;
}

CrStackWindow::~CrStackWindow()
{
}

void CrStackWindow::CreateMenu(eistr *pstr,int mode,int stack_size /* = 0*/)
{
	eistr *in;
	int number;

	if(mode == 0){
		for(in = pStackStart , number = 0;*in != NULL;in ++){
			if(!MenuFlag[number]){
				//---まだ残っていたら、そのメニューをコピーする
				*pstr = *in;
				pstr ++;
			}
			if(*in == ';'){
				number ++;
			}
		}
	} else if(stack_size){
		for(number = 0;number < stack_size;number ++){
			for(in = pMenuStart[Stack[number]];*in != ';';in ++){
				*pstr = *in;
				pstr ++;
			}
			*pstr = ';';
			pstr ++;
		}
	}

	if(*(pstr - 1) != ';'){
		*pstr = ';';
		pstr ++;
	}
	*pstr = NULL;
}

int CrStackWindow::Create(int tx,int ty,int sx,int sy,int vpos,
	eistr *title ,eistr *string,int horizon /*= 1*/,int h_size /*= 0*/)
{
	pStackStart = string;

	//---メニュー解析
	eistr *in;
	int number;
	for(in = string , number = 0 ,pMenuStart[0] = in;
		*in != NULL;in ++){

		if(*in == ';'){
			number ++;
			pMenuStart[number] = in + 1;
		}
	}

	CreateMenu(MenuString,0);
//	CreateMenu(EndString,1);
	VPos = vpos;

	return CrSelectWindow::Create(tx,ty,sx,sy,title,MenuString,horizon,h_size);
}

void CrStackWindow::Paint(void)
{
	CrSelectWindow::Paint();

	//---スタック部分を書く
	int line;
	int page = GetDrawPage();
	int col = CRCOLOR_YELLOW;
	eistr *str = EndString,*start = str;

	ew->lpCell[page]->DrawLine(
			(VPos * 16) + Top.x + CRWIN_FRAMESIZE - 4,
			Top.y + CRWIN_FRAMESIZE + 4,
			(VPos * 16) + Top.x + CRWIN_FRAMESIZE - 4,
			(Top.y + Size.y * 16) + CRWIN_FRAMESIZE - 16,
			ep->ToRGB(CRCOLOR_WHITE));

	for(line = 0;*str != NULL;line ++ ,str ++){
		for(start = str;*str != ';';str ++){
		}

		*str = NULL;
		ew->lpCell[page]->DrawText(start,
			(VPos * 16) + Top.x + CRWIN_FRAMESIZE + (HorizonSize * xSize * 0)
				+ (CRWIN_SELECT_HSPACE * (0 + 1)) + (CRWIN_SELECT_HEMPTY * 0) + 1,
			Top.y + CRWIN_FRAMESIZE + (line * LineSize) + CRWIN_SELECT_VERTOFFSET + 1,
			ep->ToTextRGB(CRCOLOR_BLACK));
		ew->lpCell[page]->DrawText(start,
			(VPos * 16) + Top.x + CRWIN_FRAMESIZE + (HorizonSize * xSize * 0)
				+ (CRWIN_SELECT_HSPACE * (0 + 1)) + (CRWIN_SELECT_HEMPTY * 0),
			Top.y + CRWIN_FRAMESIZE + (line * LineSize) + CRWIN_SELECT_VERTOFFSET,
			ep->ToTextRGB(col));
		*str = ';';
	}
}

int CrStackWindow::Select(ei_s32 *pInTable,ei_s32 *pOutTable,CRWIN_SELECTINFO *pInfo /*= NULL*/)
{
	int a,num,ret;
	int stack_pos = 0,stack_size;

	//---スタックサイズ
	for(stack_size = 0;pInTable[stack_size] != -1;stack_size ++){
	}

	while(1){
		//---作り直す
		crbaseMenuReset();
		CreateMenu(MenuString,0);
		CreateMenu(EndString,1,stack_pos);
		CrSelectWindow::SetMenuString(MenuString);

		Paint();
		Refresh();
		crbaseMenuStart();

		ret = CrSelectWindow::Select(NULL);


		if(ret == -1){
			if(stack_pos == 0){
				//---キャンセルされた
				return -1;
			}
			stack_pos --;
			MenuFlag[Stack[stack_pos]] = 0;
			Stack[stack_pos] = -1;

			continue;
		}
		for(a = 0 , num = 0;a < stack_size;a ++){
			if(ret == num && MenuFlag[a] == 0){
				//---元のメニューのa番目がプッシュされた
				Stack[stack_pos] = a;
				MenuFlag[a] = 1;
				break;
			}
			if(MenuFlag[a] == 0){
				num ++;
			}
		}
		
		if(++ stack_pos >= stack_size){
			//---スタックを全部移動した
			break;
		}
	}
	CreateMenu(MenuString,0);
	CreateMenu(EndString,1,stack_pos);
	CrSelectWindow::SetMenuString(MenuString);
	Paint();
	Refresh();

	//---結果を書き込む
	for(a = 0;a < stack_size;a ++){
		pOutTable[a] = pInTable[Stack[a]];
	}

	return 1;
}
