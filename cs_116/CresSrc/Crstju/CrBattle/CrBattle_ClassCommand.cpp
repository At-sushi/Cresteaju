//----------------------------------------------
//---�R�}���h����
void CrBattleCharacter::ClearCommand(void)
{
	memset(&Command,0,sizeof(Command));
}

//---�R�}���h���Z�b�g
void CrBattleCharacter::ResetCommand(void)
{
	Command.Main = BAT_COMMAND_WAIT;
	memset(&Command.Sub[0],0,sizeof(Command.Sub));
}

//---�R�}���h���Z�b�g
void CrBattleCharacter::SetCommand(ei_s32 maincom,ei_s32 target,ei_s32 *sub /*= NULL*/)
{
	int number = 0;

	Command.Main = maincom;
	Command.Target = target;
	if(sub){
		while(*sub != -1){
			Command.Sub[number] = *sub;
			number ++;
			sub ++;
		}
	}
}

CR_BATTLECOMMAND CrBattleCharacter::GetCommand(void)
{
	return Command;
}

ei_s32 CrBattleCharacter::GetCommandMain(void)
{
	return Command.Main;
}

ei_s32 CrBattleCharacter::GetCommandTarget(void)
{
	return Command.Target;
}

ei_s32 CrBattleCharacter::GetCommandSub(int number)
{
	return Command.Sub[number];
}

//---�R�}���h���͉\���H
ei_s32 CrBattleCharacter::IsEnableCommandInput(void)
{
	//---�����������疳��
	if(GetBtStatus() & BTST_KONRAN)
		return 0;

	//---���Ƃ͍s���\�Ɠ���
	return IsEnableAction();
}

//---�^�[�Q�b�g
CrBattleCharacter *CrBattleCharacter::GetTarget(void)
{
	return (CrBattleCharacter *)Command.Target;
}

void CrBattleCharacter::SetTarget(CrBattleCharacter *pChara)
{
	Command.Target = (ei_u32)pChara;
}
