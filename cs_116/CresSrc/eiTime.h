#ifndef EITIME_H
#define EITIME_H

//---
class EI_API eiTime
{
public:
	eiTime(void);

	int SetWaitCount(int count);
	int GetTime(void);
	int Reset(void);
	int Wait(int wait,int mode = 1);
	void Delay(int wait,int mode = 1);
	int Get(void);

	int Wait2(int wait);
	void Delay2(int wait);

	int Count,LastCount,BaseCount;
};

#endif /* EITIME_H */
