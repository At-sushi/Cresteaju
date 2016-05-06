//---ライト

static ei_u32 BattleLight,BattleLightFlag = 0;
static int BattleLightRed = 255,BattleLightGreen = 255 ,BattleLightBlue = 255;
static int BattleLightStartRed = 255,BattleLightStartGreen = 255 ,BattleLightStartBlue = 255;
static int BattleLightStartTime,BattleLightNowTime,BattleLightFadeTime;

CRBATTLEDRAW_API void crbatSetBattleLight(ei_u32 color)
{
	BattleLight = color;
}

CRBATTLEDRAW_API void crbatCalcLight(void)
{
	int color;

	BattleLightNowTime = et->GetTime() - BattleLightStartTime;

	if(BattleLightFlag && BattleLightNowTime < BattleLightFadeTime){
		color = RGBA_MAKE(
			BattleLightStartRed -   (int)((double)(BattleLightStartRed - BattleLightGreen) * ((double)BattleLightNowTime / (double)BattleLightFadeTime) ),
			BattleLightStartGreen - (int)((double)(BattleLightStartGreen - BattleLightGreen) * ((double)BattleLightNowTime / (double)BattleLightFadeTime) ),
			BattleLightStartBlue -  (int)((double)(BattleLightStartBlue - BattleLightBlue) * ((double)BattleLightNowTime / (double)BattleLightFadeTime) ),
			0);
		crbatSetBattleLight(color);
	} else if(BattleLightFlag){
		color = RGBA_MAKE(BattleLightRed,BattleLightGreen,BattleLightBlue,0);
		crbatSetBattleLight(color);
		BattleLightFlag = 0;
	}
}

//---フェードアウト
CRBATANIME_API void crbatStartFade(ei_s32 red,ei_s32 green,ei_s32 blue,int FadeTime)
{
	BattleLightNowTime = 0;
	BattleLightStartTime = et->GetTime();
	BattleLightFadeTime = FadeTime;

	BattleLightStartRed = BattleLightRed;
	BattleLightStartGreen = BattleLightGreen;
	BattleLightStartBlue = BattleLightBlue;
	BattleLightRed = red;
	BattleLightGreen = green;
	BattleLightBlue = blue;

	BattleLightFlag = 1;
}
