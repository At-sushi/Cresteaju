#ifndef INCLUDE_CRINPUT_H

#define INCLUDE_CRINPUT_H

#define CRINPUT_AUTOREPEAT 0x0001
#define CRINPUT_CONSTANTREPEAT 0x0002

#define CRREPEAT_AUTOREPEAT CRINPUT_AUTOREPEAT
#define CRREPEAT_CONSTANTREPEAT CRINPUT_CONSTANTREPEAT

#define CRINPUT_BUTTONMAX 6

class CRBASE_CLASS CrRepeat
{
public:
	CrRepeat(void);
	~CrRepeat();
	void Set(int *button,int mode);
	int GetState(void);
	void SetRepeatTime(int First,int Next);

	eiTime cet;

private:
	int Mode,*Button,PreviousState,PreviousButton;
	int DownTime,FirstDown;
	/*static*/ int AutoRepeatFirstTime,AutoRepeatNextTime;
};

class CRBASE_CLASS CrInput 
{
public:
	CrInput(eiInput *input = NULL,int mode = CRINPUT_AUTOREPEAT);
	~CrInput();

	void Get(void);
	int IsDirection(int key);
	int IsUp(void);
	int IsDown(void);
	int IsLeft(void);
	int IsRight(void);
	int IsButton(int key);
	void WaitAnykey(void);

private:
	int Mode;
	eiInput *cei;
	CrRepeat Up,Down,Left,Right,Button[CRINPUT_BUTTONMAX],
		Space,Return,Escape;

	/*static*/ int InputDevice;
};

#endif /*INCLUDE_CRINPUT_H*/
