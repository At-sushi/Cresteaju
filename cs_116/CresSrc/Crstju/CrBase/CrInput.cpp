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

//---ボタンが押されているかどうか判断
int CrRepeat::GetState(void)
{
	int time = cet.Get(),state = *Button;

	if(PreviousButton){
		//---前回押されていたら
		if(*Button){
			//---押している時間をプラス
			DownTime += time;
			if(Mode & CRREPEAT_AUTOREPEAT){
				//---オートリピート
				if(FirstDown && DownTime >= AutoRepeatFirstTime){
					state = 1;
					DownTime = 0;
					FirstDown = 0;
				} else if(FirstDown == 0 && DownTime >= AutoRepeatNextTime){
					state = 1;
					DownTime = 0;
					FirstDown = 0;
				} else {
					//---まだリピート時間でなければ
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
		//---前回押されていなかったら
		if(*Button){
			//---ファーストダウン
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

	//---リピートクラス
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

//---入力
void CrInput::Get(void)
{
	cei->Get();
}

//---方向キー
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

//---ボタン情報
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

//---何か押されるまで待つ
void CrInput::WaitAnykey(void)
{
	Get();
	while(!(IsUp() || IsDown() || IsLeft() || IsRight()
		|| IsButton(0) | IsButton(1) || IsButton(2) || (cei->Quick && crdataGetDebug()))){

		Get();
		eiSleep(1);
	}
}
