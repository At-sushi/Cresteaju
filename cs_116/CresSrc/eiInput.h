#ifndef EIINPUT_H
#define EIINPUT_H

//---“ü—Í‘•’u
class EI_API eiInput
{
public:
	eiInput(void);
	
	int Init(int mode = 0);
	void EnableInput(int flag);
	int InitJoystick(int jm = 0);

	int GetDeviceNumber(int kind);
	int SetInputDevice(int num,int mode);
	
	int ChangeJoystickPos(int val,int min,int max,int range);
	void GetJoystick(EIINPUTDATA *ed);
	
	void GetKey(EIINPUTDATA *ed);
	void GetMouse(void);
	int Get(void);
	void GetMousePosition(LPEIPOINT lpPoint);

	EIINPUTDATA Input[EI_INPUTDEVICE_MAX];
	int Escape,Return,Space,Quick,AnyKey;
	int MouseButton[4];
	EIPOINT MousePos;
	
	EIJOYINFO eiJoyInfo[10];
	int JoyStickCount,JoyStickMax;
	int Enable;
};

#endif /* EIINPUT_H */
