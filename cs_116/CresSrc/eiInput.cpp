/*-----------------------------------------------------------

   eiLibray
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   eiInput.cpp ...eiInput Class

-----------------------------------------------------------*/

eiInput::eiInput(void)
{
	eimemset(&Input[0],0,sizeof(Input));//sizeof(EIINPUTDATA) * EI_INPUTDEVICE_MAX);
	AnyKey = Escape = Space = Return = 0;
	eimemset(&MouseButton[0],0,sizeof(MouseButton));

	EnableInput(1);
}

//---������
int eiInput::Init(int mode /*= 0*/)
{
	InitJoystick();

	return 1;
}

void eiInput::EnableInput(int flag)
{
	Enable = flag;
}

//---�W���C�X�e�B�b�N��������
int eiInput::InitJoystick(int jm /*= 0*/)
{
	int a,b;
	MMRESULT mmres;

	a = joyGetNumDevs();
	if(a == 0){
//		eiDebugWriteFile("NoJoystick!\n");
		return 0;
	}

	for(b = 0;b < a;b ++){
	//---���ۂɎg����W���C�X�e�B�b�N�̐��𒲂ׂ�
		memset(&eiJoyInfo[b].JoyInfo,0,sizeof(eiJoyInfo[b].JoyInfo));
	
		mmres = joyGetDevCaps(b,&eiJoyInfo[b].JoyCaps,sizeof(JOYCAPS));
		if (mmres == JOYERR_NOERROR){
			eiJoyInfo[b].JoyInfo.dwSize = sizeof(JOYINFOEX);

			eiJoyInfo[b].JoyInfo.dwFlags=JOY_RETURNBUTTONS |
				JOY_RETURNX | JOY_RETURNY | JOY_USEDEADZONE;

			if(eiJoyInfo[b].JoyCaps.wCaps & JOYCAPS_HASZ)
				eiJoyInfo[b].JoyInfo.dwFlags |= JOY_RETURNZ;
			if(eiJoyInfo[b].JoyCaps.wCaps & JOYCAPS_HASR)
				eiJoyInfo[b].JoyInfo.dwFlags |= JOY_RETURNR;
			if(eiJoyInfo[b].JoyCaps.wCaps & JOYCAPS_HASU)
				eiJoyInfo[b].JoyInfo.dwFlags |= JOY_RETURNU;
			if(eiJoyInfo[b].JoyCaps.wCaps & JOYCAPS_HASV)
				eiJoyInfo[b].JoyInfo.dwFlags |= JOY_RETURNV;
			if(eiJoyInfo[b].JoyCaps.wCaps & JOYCAPS_HASPOV)
				eiJoyInfo[b].JoyInfo.dwFlags |= JOY_RETURNPOV;

		} else {
			a = b;
			break;
		}
	}

	JoyStickCount = a;
	if(jm == 0)
		jm = a;

	char s[80];
	sprintf(s,"(eiInput)JoyNum = %d \n",JoyStickCount);
	eiDebugWriteFile(s);

	if(a <= jm)
		JoyStickMax = a;
	else
		JoyStickMax = jm;
//---�W���C�X�e�B�b�N�̐���Ԃ�
	return a;
}

int eiInput::SetInputDevice(int num,int mode)
{
	//---�����T�|�[�g�ȏ�̃i���o�[��������
	if(num >= EI_INPUTDEVICE_MAX)
		return 0;

	Input[num].Flag = 1;
	Input[num].InputDevice = mode;

	return 1;
}

//---�W���C�X�e�B�b�N�̍��W��ϊ�
int eiInput::ChangeJoystickPos(int val,int min,int max,int range)
{
	if(min == max)
		return 0;

	val -= min;
	val = (range * val) / (max - min);

	return val;
}

//---�W���C�X�e�B�b�N����
void eiInput::GetJoystick(EIINPUTDATA *ed)
{
	MMRESULT mmres;
	int b,c,num = 0;

	if(ed->InputDevice & EI_INPUT_JOY1)
		num = 0;
	if(ed->InputDevice & EI_INPUT_JOY2)
		num = 1;
	if(ed->InputDevice & EI_INPUT_JOY3)
		num = 2;
	if(ed->InputDevice & EI_INPUT_JOY4)
		num = 3;

	mmres = joyGetPosEx(num,&eiJoyInfo[num].JoyInfo);
	if (mmres != JOYERR_NOERROR){
//		eiDebugWriteFile("err\n");
		return;
	}

	c = ChangeJoystickPos(
		eiJoyInfo[num].JoyInfo.dwXpos,
		eiJoyInfo[num].JoyCaps.wXmin,
		eiJoyInfo[num].JoyCaps.wXmax,
		640);
	//---------���E
	if(c < EI_JOY_MOVE_LEFT){
		ed->Left |= 1;
		AnyKey |= 1;
	}
	if(c > EI_JOY_MOVE_RIGHT){
		ed->Right |= 1;
		AnyKey |= 1;
	}
	//------�㉺
	c = ChangeJoystickPos(
		eiJoyInfo[num].JoyInfo.dwYpos,
		eiJoyInfo[num].JoyCaps.wYmin,
		eiJoyInfo[num].JoyCaps.wYmax,
		640);
	if(c < EI_JOY_MOVE_UP){
		ed->Up |= 1;
		AnyKey |= 1;
	}
	if(c > EI_JOY_MOVE_DOWN){
		ed->Down |= 1;
		AnyKey |= 1;
	}

	//---�{�^��
	for(b = 0;b < EI_JOY_BUTTON_MAX;b ++){
		if(((1 << b) & eiJoyInfo[num].JoyInfo.dwButtons) != 0){
			ed->Button[b] |= 1;
			AnyKey |= 1;
		}
	}
	
	return;
}

//---�L�[�{�[�h����
void eiInput::GetKey(EIINPUTDATA *ed)
{
	SHORT mask = (SHORT)0x8001;

	//--�N�C�b�N
	if(GetAsyncKeyState(0x41+('Q'-'A')) & mask){
		Quick = 1;
		AnyKey |= 1;
	}

	if((ed->InputDevice & EI_INPUT_SMALLKEY2)){
		if(GetAsyncKeyState(0x41+('T'-'A')) & mask){
			ed->Up |= 1;
			AnyKey |= 1;
		}
		if((GetAsyncKeyState(0x41+('B'-'A')) & mask)
			|| (GetAsyncKeyState(0x41+('V'-'A')) & mask)){
			ed->Down |= 1;
			AnyKey |= 1;
		}
		if(GetAsyncKeyState(0x41+('F'-'A')) & mask){
			ed->Left |= 1;
			AnyKey |= 1;
		}
		if(GetAsyncKeyState(0x41+('H'-'A')) & mask){
			ed->Right |= 1;
			AnyKey |= 1;
		}
	}
	if((ed->InputDevice & EI_INPUT_LARGEKEY)
		|| (ed->InputDevice & EI_INPUT_SMALLKEY1)){
		//---�e���L�[
		if(GetAsyncKeyState(VK_NUMPAD8) & mask){
			ed->Up |= 1;
			AnyKey |= 1;
		}
		if(GetAsyncKeyState(VK_NUMPAD2) & mask){
			ed->Down |= 1;
			AnyKey |= 1;
		}
		if(GetAsyncKeyState(VK_NUMPAD4) & mask){
			ed->Left |= 1;
			AnyKey |= 1;
		}
		if(GetAsyncKeyState(VK_NUMPAD6) & mask){
			ed->Right |= 1;
			AnyKey |= 1;
		}

		//---�J�[�\��
		if(GetAsyncKeyState(VK_UP) & mask){
			ed->Up |= 1;
			AnyKey |= 1;
		}
		if(GetAsyncKeyState(VK_DOWN) & mask){
			ed->Down |= 1;
			AnyKey |= 1;
		}
		if(GetAsyncKeyState(VK_LEFT) & mask){
			ed->Left |= 1;
			AnyKey |= 1;
		}
		if(GetAsyncKeyState(VK_RIGHT) & mask){
			ed->Right |= 1;
			AnyKey |= 1;
		}
	}

	if((ed->InputDevice & EI_INPUT_SMALLKEY1)){
	}
	if((ed->InputDevice & EI_INPUT_LARGEKEY)
		|| (ed->InputDevice & EI_INPUT_SMALLKEY2)){
		//---�{�^��
		if(GetAsyncKeyState(0x41+('Z'-'A')) & mask){
			ed->Button[0] |= 1;
			AnyKey |= 1;
		}
		if(GetAsyncKeyState(0x41+('X'-'A')) & mask){
			ed->Button[1] |= 1;
			AnyKey |= 1;
		}

		if(GetAsyncKeyState(0x41+('C'-'A')) & mask){
			ed->Button[2] |= 1;
			AnyKey |= 1;
		}

		if(GetAsyncKeyState(VK_NUMPAD0) & mask){
			ed->Button[0] |= 1;
			AnyKey |= 1;
		}
		if(GetAsyncKeyState(VK_RETURN) & mask){
			ed->Button[1] |= 1;
			AnyKey |= 1;
		}
		if(GetAsyncKeyState(VK_DECIMAL) & mask){
			ed->Button[2] |= 1;
			AnyKey |= 1;
		}
	}
}

//---�L�[�{�[�h����
void eiInput::GetMouse(void)
{
	POINT point;

	if(GetAsyncKeyState(VK_LBUTTON)){
		MouseButton[0] |= 1;
		AnyKey |= 1;
	}
	if(GetAsyncKeyState(VK_RBUTTON)){
		MouseButton[1] |= 1;
		AnyKey |= 1;
	}
	//---�}�E�X���W
	eiGetMousePoint(&MousePos);

	point.x = point.y = 0;
	if(::lpMainWindow)
		::ClientToScreen(::lpMainWindow->hwnd,&point);

	if((::eiSystem.ScreenMode & DIRECTDRAW_WINDOW)
		|| (::eiSystem.ScreenMode & WINAPI_WINDOW)){
		MousePos.x -= point.x;
		MousePos.y -= point.y;
	}
}

//---����
int eiInput::Get(void)
{
	int num;
	SHORT mask = (SHORT)0x8000;

	//---�X���b�h�`�F�b�N
	eiCheckThread();

	//---�}�E�X���͂��N���A
	memset(&MouseButton[0],0,sizeof(MouseButton));
	memset(&MousePos,0,sizeof(MousePos));
	//---�}�E�X����
	GetMouse();

	AnyKey = Escape = Space = Return = Quick = 0;

	for(num = 0;num < EI_INPUTDEVICE_MAX;num ++){
		if(!Input[num].Flag)
			continue;

		//---���͒l���N���A����
		memset(&Input[num].Button[0],0,sizeof(Input[num].Button));//sizeof(int) * EI_INPUTBUTTON_MAX);
		Input[num].Up = Input[num].Down = Input[num].Left = Input[num].Right = 0;

		//---���͕s�Ȃ�
		if(Enable == 0){
			continue;
		}

		if(Input[num].InputDevice & EI_INPUT_KEY){
			GetKey(&Input[num]);
		}
		if(Input[num].InputDevice & EI_INPUT_JOYSTICK){
			GetJoystick(&Input[num]);
		}
	}

	//---���͕s�Ȃ�
	if(Enable == 0){
		return 1;
	}

	if(GetAsyncKeyState(VK_ESCAPE) & mask){
		Escape = 1;
		AnyKey |= 1;
	}
	if(GetAsyncKeyState(VK_RETURN) & mask){
		Return = 1;
		AnyKey |= 1;
	}
	if(GetAsyncKeyState(VK_SPACE) & mask){
		Space = 1;
		AnyKey |= 1;
	}
	if(GetAsyncKeyState(0x41 + ('Q' - 'A')) & mask){
		Quick = 1;
		AnyKey |= 1;
	}

	return 1;
}

//---�}�E�X�J�[�\���̍��W�𓾂�
void eiInput::GetMousePosition(LPEIPOINT lpPoint)
{
	GetMouse();

	lpPoint->x = MousePos.x;
	lpPoint->y = MousePos.y;
}
