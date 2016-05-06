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

//---�x�[�X�J�E���g��ݒ�i�~���b�j
int eiTime::SetWaitCount(int count)
{
	int a = BaseCount;

	if(!count)
		count = 0;
	BaseCount = count;

	return a;
}

//---���ݎ��Ԃ𓾂�
int eiTime::GetTime(void)
{
	int time;

	time = eiGetTime();

	return time;
}

//---�E�F�C�g�����Z�b�g
int eiTime::Reset(void)
{
	int a;

	//�O�񂱂̊֐����Ă΂�Ă���ǂ̂��炢���Ԃ������Ă��邩
	a = GetTime() - LastCount;
	if(a < 0)
		a = 0;
	//���̎���
	LastCount = Count = GetTime();

	return 0;
}

//---���Z�b�g����Ă���ǂ̂��炢���Ԃ��o������
int eiTime::Get(void)
{
	return GetTime() - LastCount;
}

//---�E�F�C�g�i���t���b�V�����[�g��̃E�F�C�g�j
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

//---�E�F�C�g�Q�i�~���b�P�ʂł̃E�F�C�g�j
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

//---�f�B���C�i�Q�Ƃ̋�ʂ̓E�F�C�g�Ɠ����j
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
