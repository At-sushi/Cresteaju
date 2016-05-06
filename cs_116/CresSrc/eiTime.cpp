/*-----------------------------------------------------------

   eiLibray
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   eiTime.cpp ...eiTime Class

-----------------------------------------------------------*/

eiTime::eiTime(void)
{
	Count = LastCount = 0;

	SetWaitCount(16);

	Reset();
}

//---ベースカウントを設定（ミリ秒）
int eiTime::SetWaitCount(int count)
{
	int a = BaseCount;

	if(!count)
		count = 0;
	BaseCount = count;

	return a;
}

//---現在時間を得る
int eiTime::GetTime(void)
{
	int time;

	time = eiGetTime();

	return time;
}

//---ウェイトをリセット
int eiTime::Reset(void)
{
	int a;

	//前回この関数が呼ばれてからどのくらい時間がたっているか
	a = GetTime() - LastCount;
	if(a < 0)
		a = 0;
	//今の時間
	LastCount = Count = GetTime();

	return 0;
}

//---リセットされてからどのくらい時間が経ったか
int eiTime::Get(void)
{
	return GetTime() - LastCount;
}

//---ウェイト（リフレッシュレート基準のウェイト）
int eiTime::Wait(int wait,int mode)
{
	int a,c = 1;

	if(mode == 1)
		c = BaseCount;//16;
	if((com_key & KEY_Q) != 0 && eiGetDebugMode() == 1)
		return 0;

	while(1){
		a = GetTime();
		a = a - Count;
		if(a >= wait * c)
			break;

		eiCheckThread();
		eiSleep(1);
	}
	a = Count;
	Count = 0;

	return a;
}

//---ウェイト２（ミリ秒単位でのウェイト）
int eiTime::Wait2(int wait)
{
	int a;

	if((com_key & KEY_Q) != 0 && eiGetDebugMode() == 1)
		return 0;

	while(1){
		a = GetTime();
		a = a - Count;
		if(a >= wait)
			break;

		eiCheckThread();
		eiSleep(1);
	}
	a = Count;
	Count = 0;

	return a;
}

//---ディレイ（２との区別はウェイトと同じ）
void eiTime::Delay(int wait,int mode)
{
	int a,b,c = 1;

	if(mode == 1)
		c = BaseCount;
	if((com_key & KEY_Q) != 0 && eiGetDebugMode() == 1)
		return;

	b = GetTime();
	while(1){
		a = GetTime();
		a = a - b;
		if(a >= wait * c)
			break;

		eiCheckThread();
		eiSleep(1);
	}
}

void eiTime::Delay2(int wait)
{
	int a,b;

	if((com_key & KEY_Q) != 0 && eiGetDebugMode() == 1)
		return;

	b = GetTime();
	while(1){
		a = GetTime();
		a = a - b;
		if(a >= wait)
			break;

		eiCheckThread();
		eiSleep(1);
	}
}
