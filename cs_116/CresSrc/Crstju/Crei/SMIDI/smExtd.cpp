BYTE smidic2Env[4096];
PROCESS_INFORMATION ProcessInfo;

int smidiCreateProcess(void)
{
	STARTUPINFO sti;

	memset(&sti,0,sizeof(sti));
	memset(&ProcessInfo,0,sizeof(ProcessInfo));

	sti.cb = sizeof(sti);
	sti.dwFlags = STARTF_USESHOWWINDOW;
	sti.wShowWindow = SW_RESTORE;
	
	if(!CreateProcess(NULL,"SMidiC2.exe /s",
		NULL,NULL,0,
		CREATE_NEW_PROCESS_GROUP,NULL,NULL,
		&sti,&ProcessInfo))
		return SMIDI_ER_SOMETHING;

	return SMIDI_NOERROR;
}

int smidiTerminateProcess(void)
{
	smidiMessage = SMIDI_MES_EXIT;
	Sleep(50);
	TerminateProcess(ProcessInfo.hProcess,0);

	return SMIDI_NOERROR;
}

int smidiCreateThread(void)
{
	DWORD math = ThreadID;

	hsmidiThread = CreateThread(NULL,0,
		(LPTHREAD_START_ROUTINE)smidiThread,0,
		CREATE_NEW_PROCESS_GROUP,&math);

	if(hsmidiThread)
		return SMIDI_NOERROR;

	return SMIDI_ER_SOMETHING;
}

int smidiTerminateThread(void)
{
	ThreadFlag=0;
	TerminateThread(hsmidiThread,0);

	Sleep(50);

	return SMIDI_NOERROR;
}

int smidiGetMessage(void)
{
	return smidiMessage;
}

int smidiGetInitFlag(void)
{
	return InitFlag;
}
