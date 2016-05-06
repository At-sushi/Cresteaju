//---StringWindow--------------------------
CrStringWindow::CrStringWindow(int font /* = EINORMAL_FONT*/,
	int style /*= CRWIN_DEFAULT*/,
	int ptn /*= 0*/,int alpha /*= 175*/) : CrEmptyWindow(style,ptn,alpha)
{
	x = 0;
	y = 0;
	xSize = 8;
	ySize = 16;
	pLastString = NULL;

	if(font == EINORMAL_FONT){
		LineSize = 20;
	} else if(font == EILARGE_FONT){
		xSize = 12;
		ySize = 24;
		LineSize = 32;
	} else if(font == EISMALL_FONT){
		xSize = 6;
		ySize = 12;
		LineSize = 16;
	}

	Width = 80;
	Height = 20;
	Color = CRCOLOR_WHITE;
	Font = font;
	xOffset = CRWIN_FRAMESIZE;
	yOffset = CRWIN_FRAMESIZE;
}

CrStringWindow::~CrStringWindow()
{
}

//---�I�t�Z�b�g
void CrStringWindow::SetOffset(int x,int y)
{
	xOffset = x;
	yOffset = y;
}

//---���Z�b�g
void CrStringWindow::Reset(void)
{
	x = 0;
	y = 0;
}

int CrStringWindow::Create(int tx,int ty,int sx,int sy)
{
	int ret;

	ret = CrEmptyWindow::Create(tx,ty,sx,sy);
	//---�\���T�C�Y�v�Z
	Width = (Size.x - 1) * 2;
	Height = Size.y - 1;

	return ret;
}

void CrStringWindow::Paint(void)
{
	if(CreateFlag){
		CrEmptyWindow::Paint();
	}
}

//---�F�ݒ�
int CrStringWindow::SetColor(int col)
{
	Color = col;

	return 1;
}

//---�s�Ԑݒ�
int CrStringWindow::SetLineSize(int size)
{
	LineSize = size;

	return 1;
}

//---�|�W�V�����v�Z
void CrStringWindow::AddWord(int n /*= 1*/)
{
	x += n;
	if(x >= Width - (xOffset / 8)){
		do {
			x -= (Width - (xOffset / 8));
			AddLine();
		} while(x >= Width - (xOffset / 8));
	} else if(x < 0){
		do {
			x += (Width - (xOffset / 8));
			AddLine(-1);
		} while(x < 0);
	}
}

void CrStringWindow::AddLine(int n /*= 1*/)
{
	y += n;

	if(y >= Height){
		y = Height - 1;
	} else if(y <= 0){
		y = 0;
	}
}

//---���s
void CrStringWindow::AddReturn(int n /*= 1*/)
{
	int a;

	for(a = 0;a < n;a ++){
		AddLine(1);
		x = 0;
	}
}

int CrStringWindow::xGetCurrentPos(void)
{
	return x;
}

int CrStringWindow::yGetCurrentPos(void)
{
	return y;
}

void CrStringWindow::DrawLastString(void)
{
	if(pLastString){
		DrawText(pLastString);
	}
}

//---����������
void CrStringWindow::DrawText(int col,lpeistr lpString,
	int sx /*= CRWIN_STRING_CURRENTPOS*/,int sy /*= CRWIN_STRING_CURRENTPOS*/)
{
	DrawText(lpString,sx,sy,col);
}

void CrStringWindow::DrawText(lpeistr lpString,
	int sx /*= CRWIN_STRING_CURRENTPOS*/,int sy /*= CRWIN_STRING_CURRENTPOS*/,
	int col /*= -1*/)
{
	int page = GetDrawPage();

	if(!CreateFlag)
		return;

	if(col == -1)
		col = ep->ToTextRGB(Color/*CRCOLOR_WHITE*/);

	if(sx == CRWIN_STRING_CURRENTPOS){
		sx = xGetCurrentPos();
	}
	if(sy == CRWIN_STRING_CURRENTPOS){
		sy = yGetCurrentPos();
	}
	if(sx < 0)
		sx = 0;
	if(sy < 0)
		sy = 0;
	if(sx >= Width)
		sx = Width - 1;
	if(sy >= Height)
		sy = Height -1 ;

	int old = eiSetFont(Font);
	//---��ʂɕ\��
	ew->lpCell[page]->DrawText(
		lpString,
		(sx * xSize) + Top.x + xOffset + 1,
		(sy * LineSize) + Top.y + yOffset + 1,
		ep->ToTextRGB(CRCOLOR_BLACK),EI_TRANS);
	ew->lpCell[page]->DrawText(
		lpString,
		(sx * xSize) + Top.x + xOffset,//CRWIN_FRAMESIZE,
		(sy * LineSize) + Top.y + yOffset,//CRWIN_FRAMESIZE,
		col,EI_TRANS);
	eiSetFont(old);

	AddWord(strlen(lpString));
	pLastString = lpString;
}

//---MessageWindow--------------------------
CrMessageWindow::CrMessageWindow(int font /*= EINORMAL_FONT*/,
	int style /*= CRWIN_DEFAULT*/,
	int ptn /*= 0*/,int alpha /*= 175*/) : CrStringWindow(font,style,ptn,alpha)
{
	//---�����o�b�t�@�[������
	eimemset(&MessageBuffer[0],0,sizeof(MessageBuffer));
	lpWriteBuffer = &MessageBuffer[0];
	lpReadBuffer = &MessageBuffer[0];

	CurrentColor = CRCOLOR_WHITE;

	WaitMode = 0;
}

CrMessageWindow::~CrMessageWindow()
{
}

//---�E�F�C�g���[�h
void CrMessageWindow::SetWaitMode(int mode)
{
	WaitMode = mode;
}

int CrMessageWindow::GetWaitMode(void)
{
	return WaitMode;
}

int CrMessageWindow::Create(int tx /*= -1*/,int ty /*= -1*/,
							int sx /*= -1*/,int sy /*= -1*/)
{
	int ret;
	
	if(tx == -1){
		//---�W���̃��b�Z�[�W�E�B���h�E
		tx = ty = 0;
		sx = 32;
		sy = 16;
	}

	ret = CrStringWindow::Create(tx,ty,sx,sy);
	SetOffset(16,16);

	return ret;
}

//---�N���A
void CrMessageWindow::Clear(void)
{
	//---�����o�b�t�@�[������
	eimemset(&MessageBuffer[0],0,sizeof(MessageBuffer));
	lpWriteBuffer = &MessageBuffer[0];
	lpReadBuffer = &MessageBuffer[0];

	//---�����ʒu������
	x = y = 0;
	CurrentColor = CRCOLOR_WHITE;

	CrEmptyWindow::Paint();
}

void CrMessageWindow::ResetReadBuffer(void)
{
	lpReadBuffer = &MessageBuffer[0];
}

void CrMessageWindow::ResetWriteBuffer(void)
{
	lpWriteBuffer = &MessageBuffer[0];
}

void CrMessageWindow::ResetPos(void)
{
	x = y = 0;
}

void CrMessageWindow::Call_CallBack(void)
{
	if(ef->FGCallback != NULL){
		RECT rect = {0,0,640,32 + ef->Field.ySize * 32};
//		eiDDSurface *pSurface = eiGetSurfacePointer();

//		pSurface[3].Put(&pSurface[1],0,0,&rect,DDBLTFAST_WAIT);
		(*ef->FGCallback)(ew->lpCell[1],0,0,0,0,0);

		rect.left = 0;
		rect.right = 639;
		rect.top = 360;
		rect.bottom = 380;
		if(eiGetFullScreen()){
/*2000/9/9
			pSurface[1].PutExtend2(&pSurface[0],&rect,&rect,DDBLT_WAIT);
*/
			ew->lpCell[1]->Copy(ew->lpCell[0],rect.left,rect.top,&rect);

//			pSurface[1].Put(&pSurface[0],0,360,&rect,DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
		} else {
			ew->Refresh();
		}

		eiCheckThread();
//		ew->Flip();
	}
	eiSleep(1);
}

//---���b�Z�[�W��\��
int CrMessageWindow::Draw(int frame /*= -1*/,int wait /*= 1*/,int refresh /*= 1*/)
{
	int a,size,f;
	eistr s[32] = {' ',NULL} , t[16],*p = &t[0];
	eiTime let,let2;

	if(ResetFlag){
//		CrEmptyWindow::Paint();
		ResetFlag = 0;
	}

	if(frame == -1)
		frame = 99999;

	//---��ʂ�ۑ����Ă���
/*	RECT screen_rect = {
		32 + ef->Field.xTop,
		32 + ef->Field.yTop,
		32 + ef->Field.xTop + ef->Field.xSize * ef->Field.PatternSize,
		32 + ef->Field.yTop + ef->Field.ySize * ef->Field.PatternSize
	};*/
	if(GetWaitMode() == 1){
/*		RECT rect = {0,0,640,32 + ef->Field.ySize * 32};
		eiDDSurface *pSurface = eiGetSurfacePointer();
		pSurface[1].Put(&pSurface[3],0,0,&rect,DDBLTFAST_WAIT);*/
	}

	for(f = 0;f < frame && s[0];f ++){
		ReadBuffer(&s[0],&size);

		let.Reset();
		let2.Reset();
		p = &t[0];

		if(size == 2){
		} else {
			//---�P�o�C�g����
			if(s[0] == '\\' || s[0] == '@'){
				//---���䕶��
				a = 0;
				ReadBuffer(&t[0],NULL);
				while(*p != ';' && *p != NULL && a < 32){
					s[a] = *p;
					a ++;

					ReadBuffer(&t[0],NULL);
				}
				s[a] = 0;

				//---�F
				if(!strcmp(&s[0],"ColorRed")){
					CurrentColor = CRCOLOR_RED;
				} else if(!strcmp(&s[0],"ColorBlue")){
					CurrentColor = CRCOLOR_BLUE;
				} else if(!strcmp(&s[0],"ColorGreen")){
					CurrentColor = CRCOLOR_GREEN;
				} else if(!strcmp(&s[0],"ColorYellow")){
					CurrentColor = CRCOLOR_YELLOW;
				} else if(!strcmp(&s[0],"ColorPurple")){
					CurrentColor = CRCOLOR_PURPLE;
				} else if(!strcmp(&s[0],"ColorAqua")){
					CurrentColor = CRCOLOR_AQUA;
				} else if(!strcmp(&s[0],"ColorWhite")){
					CurrentColor = CRCOLOR_WHITE;
				//---�t�H���g
				} else if(!strcmp(&s[0],"FontNormal")){
					CurrentFont = EINORMAL_FONT;
				//---��������
				} else if(!strcmp(&s[0],"n")){
					AddReturn();//---���s
				} else if(!strcmp(&s[0],"c")){
					WaitKey();
					ResetFlag = 1;
					x = y = 0;
					Paint();
//					Clear();//---�N���A�[���L�[�E�F�C�g
				} else if(!strcmp(&s[0],"Clear") || !strcmp(&s[0],"v")){
					ResetFlag = 1;
					x = y = 0;
				//---�`�搧��
				} else if(!strcmp(&s[0],"p")){
					Paint();
				//---���Ԑ���
				} else if(!strcmp(&s[0],"w")){
					//---�E�F�C�g
					if(crsysNotQuick()){
						if(GetWaitMode() == 0){
							et->Delay2(250);
						} else {
							int wt = 250;

							while(let2.Get() < wt){
								Call_CallBack();
							}
						}
					}
				} else if(!strcmp(&s[0],"wt")){
					//---���Ԏw��E�F�C�g
					char wait[8] = {0},*u = &wait[0];
					ReadBuffer(&t[0],NULL);
					while(*p != ';' && *p != NULL){
						*u = *p;
						u ++;

						ReadBuffer(&t[0],NULL);
					}
					if(crsysNotQuick()){
						if(GetWaitMode() == 0){
							et->Delay2(atoi(wait));
						} else {
							//---��Ƀt���b�v
							int wt = atoi(wait);

							while(let2.Get() < wt){
								Call_CallBack();
							}
						}
					}
				//---�L�[���͑҂�
				} else if(!strcmp(&s[0],"k")){
					WaitKey();
				}

//				eiDebugWriteFile(s);

				continue;
			}
		}
		//---������������
//		x = xGetCurrentPos();
//		y = yGetCurrentPos();
//		DrawText(&s[0],x,y,
//			ep->ToTextRGB(CurrentColor));
		DrawText(&s[0],CRWIN_STRING_CURRENTPOS,CRWIN_STRING_CURRENTPOS,
			ep->ToTextRGB(CurrentColor));
//		AddWord();

		//---��ʍX�V
		if(refresh){
			Refresh();
		}
		//---�E�F�C�g
		if(GetWaitMode() == 1){
			Call_CallBack();
		}
		if(wait){
			let.Wait2(13);
		}
	}

	//---�����񂪏I��������ǂ���
	if(s[0] == 0)
		return 0;

	return 1;
}

//---�o�b�t�@�[�ɏ�������
void CrMessageWindow::WriteBuffer(eistr **message)
{
	int u = (int)(**message);

	if(_ismbblead((unsigned int)u)){
		//---�Q�o�C�g����
		*lpWriteBuffer = **message;
		lpWriteBuffer ++;
		(*message) ++;
		*lpWriteBuffer = **message;
		lpWriteBuffer ++;
		(*message) ++;
	} else {
		//---�P�o�C�g����
		*lpWriteBuffer = **message;
		lpWriteBuffer ++;
		(*message) ++;
	}
	if(lpWriteBuffer - &MessageBuffer[0] >= CRWIN_MESSAGE_BUFFERSIZE - 16){
		//---�z������
		lpWriteBuffer = &MessageBuffer[0];
	}
}

//---�o�b�t�@�[����ǂݏo��
int CrMessageWindow::ReadBuffer(eistr *message,int *size)
{
	int u = (int)(*lpReadBuffer);

	if(u != 0 && _ismbblead((unsigned int)u)){
		//---�Q�o�C�g����
		*message = *lpReadBuffer;
		lpReadBuffer ++;
		message ++;
		*message = *lpReadBuffer;
		lpReadBuffer ++;
		message ++;

		if(size)
			*size = 2;
	} else {
		//---�P�o�C�g����
		*message = *lpReadBuffer;
		lpReadBuffer ++;
		message ++;

		if(size)
			*size = 1;
	}
	*message = 0;

	if(lpReadBuffer - &MessageBuffer[0] >= CRWIN_MESSAGE_BUFFERSIZE - 16){
		//---�z������
		lpReadBuffer = &MessageBuffer[0];
	}

	return 1;
}

//---���b�Z�[�W���o�b�t�@�[�ɏ�������
void CrMessageWindow::Message(lpeistr lpString)
{
	int sx = xGetCurrentPos(),sy = yGetCurrentPos();

	eistr s;
	do {
		s = *lpString;
		//---�o�b�t�@�[�Ƀ��b�Z�[�W����������
		WriteBuffer(&lpString);
	} while(s);
}

int CrMessageWindow::CalcWaitKeyCursorPosX(void)
{
	int sx = xGetCurrentPos();

	sx = (sx * xSize) + Top.x + /*CRWIN_FRAMESIZE +*/ xOffset;

	return sx;
}

int CrMessageWindow::CalcWaitKeyCursorPosY(void)
{
	int sy = yGetCurrentPos();

	sy = (sy * LineSize) + Top.y + /*CRWIN_FRAMESIZE +*/yOffset;

	return sy;
}

void CrMessageWindow::KeepWaitKeyCursor(void)
{
	int sx = CalcWaitKeyCursorPosX() ,sy = CalcWaitKeyCursorPosY();
	RECT rect = {sx,sy,sx + 16,sy + 16};

	ew->lpCell[1]->PutClip((pMessageIconCell + 12),0,0,&rect);
}

void CrMessageWindow::RestoreWaitKeyCursor(void)
{
	int sx = CalcWaitKeyCursorPosX() ,sy = CalcWaitKeyCursorPosY();

	pMessageIconCell[12].PutClip(ew->lpCell[1],sx,sy);
}

//---�L�[���͑҂��i�J�[�\�����邭��j
void CrMessageWindow::WaitKey(void)
{
	int cur = 0,Wait = 0,MaxWait = 8;
	eiTime et;
	CrInput ci;

	if(crsysNotQuick()){
		et.Reset();
		et.Wait2(crsysGetWaitKeyDelay());
	}

	ci.Get();
	KeepWaitKeyCursor();
	while(1){
		et.Reset();
		ci.Get();
		if(ci.IsButton(0) || ci.IsButton(1)
			|| ci.IsLeft() || ci.IsRight()
			|| ci.IsUp() || ci.IsDown()
			|| (crsysQuick()/*ei->Quick && crdataGetDebug()*/))
			break;

		if(++Wait >= MaxWait){
			Wait = 0;
			if(++cur >= 12)
				cur = 0;

			RestoreWaitKeyCursor();
			pMessageIconCell[cur].PutTransClip(ew->lpCell[1],CalcWaitKeyCursorPosX(),CalcWaitKeyCursorPosY());
			ew->Refresh();
		}

		et.Wait2(10);
	}

	crsoundPlay(CRSOUND_BTN_B);
	if(crsysNotQuick()){
		et.Reset();
		et.Wait2(crsysGetWaitKeyAfterPush());
	}
}
