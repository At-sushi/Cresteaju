  //----------------------------------------------------
 //CRESTEAJU InputClass
//----------------------------------------------------

#define FILE_CRINPUT

#include "..\CrInput.h"
/*
int CrInput::InputDevice = 0,
	CrRepeat::AutoRepeatFirstTime = 300,
	CrRepeat::AutoRepeatNextTime = 100;
*/
//----------------------
//---RepeatClass
//----------------------

CrRepeat::CrRepeat(void)
{
	Mode = 0;
	Button = NULL;
	DownTime = 0;
	FirstDown = 0;
	PreviousButton = PreviousState = 0;

	AutoRepeatFirstTime = crdataGetSystem()->KeyWaitAfterPush;//300;
	AutoRepeatNextTime = crdataGetSystem()->KeyWaitDelay;//100;

	cet.Reset();
}

CrRepeat::~CrRepeat()
{
}

void CrRepeat::Set(int *button,int mode)
{
	Button = button;
	Mode = mode;
}

//---�{�^����������Ă��邩�ǂ������f
int CrRepeat::GetState(void)
{
	int time = cet.Get(),state = *Button;

	if(PreviousButton){
		//---�O�񉟂���Ă�����
		if(*Button){
			//---�����Ă��鎞�Ԃ��v���X
			DownTime += time;
			if(Mode & CRREPEAT_AUTOREPEAT){
				//---�I�[�g���s�[�g
				if(FirstDown && DownTime >= AutoRepeatFirstTime){
					state = 1;
					DownTime = 0;
					FirstDown = 0;
				} else if(FirstDown == 0 && DownTime >= AutoRepeatNextTime){
					state = 1;
					DownTime = 0;
					FirstDown = 0;
				} else {
					//---�܂����s�[�g���ԂłȂ����
					state = 0;
				}
			} else {
				if(DownTime >= AutoRepeatNextTime){
					state = 1;
					DownTime = 0;
					FirstDown = 0;
				} else {
					state = 0;
				}
			}
		}
	} else {
		//---�O�񉟂���Ă��Ȃ�������
		if(*Button){
			//---�t�@�[�X�g�_�E��
			FirstDown = 1;
			DownTime = 0;
			state = 1;
		} else {
			state = 0;
		}
	}

	cet.Reset();
	PreviousButton = *Button;
	PreviousState = state;

	return state;
}

//----------------------
//---InputClass
//----------------------

CrInput::CrInput(eiInput *input /*= NULL*/,int mode /* = CRINPUT_AUTOREPEAT*/)
{
	InputDevice = 0;

	cei = input;
	if(input == NULL)
		cei = ::ei;

	Mode = mode;

	//---���s�[�g�N���X
	Up.Set(&cei->Input[InputDevice].Up,mode);
	Down.Set(&cei->Input[InputDevice].Down,mode);
	Left.Set(&cei->Input[InputDevice].Left,mode);
	Right.Set(&cei->Input[InputDevice].Right,mode);
	Button[0].Set(&cei->Input[InputDevice].Button[0],mode);
	Button[1].Set(&cei->Input[InputDevice].Button[1],mode);
	Button[2].Set(&cei->Input[InputDevice].Button[2],mode);
	
	Return.Set(&cei->Return,mode);
	Space.Set(&cei->Space,mode);
	Escape.Set(&cei->Escape,mode);
}

CrInput::~CrInput()
{
}

//---����
void CrInput::Get(void)
{
	cei->Get();
}

//---�����L�[
int CrInput::IsDirection(int key)
{
	if(key == 0){
		return IsUp();
	} else if(key == 1){
		return IsRight();
	} else if(key == 2){
		return IsDown();
	} else if(key == 3){
		return IsLeft();
	}
	return 0;
}

int CrInput::IsUp(void)
{
	return Up.GetState();
}

int CrInput::IsDown(void)
{
	return Down.GetState();
}

int CrInput::IsLeft(void)
{
	return Left.GetState();
}

int CrInput::IsRight(void)
{
	return Right.GetState();
}

//---�{�^�����
int CrInput::IsButton(int key)
{
	int state = 0;

	if(key > 2)
		return 0;

	state = Button[key].GetState();
	if(key == 0)
		state |= Escape.GetState();
	else if(key == 1)
		state |= (Return.GetState() | Space.GetState());

	return state;
}

//---�����������܂ő҂�
void CrInput::WaitAnykey(void)
{
	Get();
	while(!(IsUp() || IsDown() || IsLeft() || IsRight()
		|| IsButton(0) | IsButton(1) || IsButton(2) || (cei->Quick && crdataGetDebug()))){

		Get();
		eiSleep(1);
	}
}
