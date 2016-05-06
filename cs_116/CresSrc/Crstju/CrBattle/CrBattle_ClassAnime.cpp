//---アニメーション中か？
int CrBattleCharacter::IsAnime(void)
{
	return OnlyInfo.AnimeFlag;
}

float CrBattleCharacter::GetAnimeX(void)
{
	return OnlyInfo.ax;
}

float CrBattleCharacter::GetAnimeY(void)
{
	return OnlyInfo.ay;
}

float CrBattleCharacter::GetAnimeZ(void)
{
	return OnlyInfo.az;
}

//---アニメーションパターンを定義
void CrBattleCharacter::SetAnimePattern(ei_s32 *pAnime)
{
	OnlyInfo.pAnime = pAnime;
	OnlyInfo.AnimeCount = 0;
	OnlyInfo.AnimePos = 0;
}

//---アニメーションを開始
void CrBattleCharacter::BeginAnime(int anime)
{
	static ei_s32 DefaultPattern[8];

	OnlyInfo.AnimeFlag = 1;
	OnlyInfo.AnimeMode = anime;
	OnlyInfo.DeltaTime = 0.0f;

	OnlyInfo.ax = (float)GetFieldX();
	OnlyInfo.ay = (float)GetFieldY();
	OnlyInfo.az = (float)GetFieldZ();
	
	//---デフォルトパターンをセット
/*	OnlyInfo.OldPattern = GetPattern();
	DefaultPattern[0] = GetPattern();
	DefaultPattern[1] = 1000;
	DefaultPattern[2] = -1;
	DefaultPattern[3] = 0;
	if(IsFriend()){
		DefaultPattern[0] = GetPattern();
		DefaultPattern[1] = 100;
		DefaultPattern[2] = GetPattern() + 1;
		DefaultPattern[3] = 100;
		DefaultPattern[4] = -1;
		DefaultPattern[5] = 0;
	}
	SetAnimePattern(&DefaultPattern[0]);*/
}

//---アニメーションを終了
void CrBattleCharacter::EndAnime(void)
{
	OnlyInfo.AnimeFlag = 0;
	OnlyInfo.AnimeMode = 0;
	OnlyInfo.pAnime = NULL;
	SetPattern(OnlyInfo.OldPattern);
}

//---フレームが動く
float CrBattleCharacter::DoAnime(float AddWorld)
{
	//---移動ベクトル
	OnlyInfo.ax += (float)((float)OnlyInfo.MoveSpeed * (float)cos(OnlyInfo.MoveAngle) * (float)AddWorld );
	OnlyInfo.ay += (float)((float)OnlyInfo.MoveSpeed * (float)sin(OnlyInfo.MoveAngle) * (float)AddWorld );

	OnlyInfo.DeltaTime += (float)AddWorld;
	OnlyInfo.LimitTime -= (float)AddWorld;

	if(OnlyInfo.LimitTime <= 0.0f){
		//---到達している
		//---座標を目標地点にする
		OnlyInfo.ax = OnlyInfo.dx;
		OnlyInfo.ay = OnlyInfo.dy;

		return 0.0f;
	}

	//---パターンアニメーション
	if(OnlyInfo.pAnime != NULL){
		OnlyInfo.AnimeCount += (int)AddWorld;
		if(OnlyInfo.AnimeCount >= OnlyInfo.pAnime[1 + OnlyInfo.AnimePos * 2]){
			//---パターン更新
			OnlyInfo.AnimeCount = 0;
			OnlyInfo.AnimePos ++;
			if(OnlyInfo.pAnime[OnlyInfo.AnimePos * 2] == -1){
				//---パターンの最後だったら先頭に戻る
				OnlyInfo.AnimePos = 0;
			}
			SetPattern(OnlyInfo.pAnime[OnlyInfo.AnimePos * 2]);
		}
	}

/*	char s[100];
	sprintf(s,"%f : %f,%f\n",OnlyInfo.LimitTime,GetAnimeX(),GetAnimeY());
	eiDebugWriteFile(s);
*/
	//---残りの距離を返す
	return (float)sqrt(
		(OnlyInfo.ax - OnlyInfo.dx) * (OnlyInfo.ax - OnlyInfo.dx)
		+  (OnlyInfo.ay - OnlyInfo.dy) * (OnlyInfo.ay - OnlyInfo.dy));
}

//---リミットタイム
void CrBattleCharacter::SetAnimeLimitTime(float limit)
{
	OnlyInfo.LimitTime = limit;
}

//---残りリミットタイム
float CrBattleCharacter::GetLeftTime(void)
{
	return OnlyInfo.LimitTime;
}

void CrBattleCharacter::SetMoveSpeed(float speed)
{
	OnlyInfo.MoveSpeed = speed;
}

//---移動方向、スピードを設定
void CrBattleCharacter::SetAnimeMoving(float x,float y,float z,float speed /*= 20.0f一秒間に進む距離 */,
									   int mode /*= 0*/ /*対象座標の直前で止まるかどうか*/)
{
	OnlyInfo.dx = x;
	OnlyInfo.dy = y;
	OnlyInfo.dz = z;
	OnlyInfo.MoveAngle = crbatGetCameraAngle(GetAnimeX(),GetAnimeY(),x,y);
	SetMoveSpeed(speed / 1000.000f);

	if(mode == 1){
		//---対象座標の直前で止まるなら
		OnlyInfo.dx -= (float)(cos(OnlyInfo.MoveAngle) * 0.75f);
		OnlyInfo.dy -= (float)(sin(OnlyInfo.MoveAngle) * 0.75f);
	}
	//---到達時間（ミリ秒）
	SetAnimeLimitTime((float)(
		sqrt(
		   (OnlyInfo.dx - OnlyInfo.ax) * (OnlyInfo.dx - OnlyInfo.ax)
		 + (OnlyInfo.dy - OnlyInfo.ay) * (OnlyInfo.dy - OnlyInfo.ay))
		 / speed * 1000.000f
		));

	static AnimePattern[8];
	
	if(IsFriend()){
		//---ディフォルトのアニメーション
		AnimePattern[0] = 8;
		AnimePattern[1] = 100;
		AnimePattern[2] = 12;
		AnimePattern[3] = 100;
		AnimePattern[4] = -1;
		AnimePattern[5] = 0;
		SetAnimePattern(&AnimePattern[0]);
	}

/*	char s[100];
	sprintf(s,"lim:%f ,sp:%f\n",OnlyInfo.LimitTime,OnlyInfo.MoveSpeed);
	eiDebugWriteFile(s);
	sprintf(s,"%f , %f,%f\n",OnlyInfo.MoveAngle,GetAnimeX(),GetAnimeY());
	eiDebugWriteFile(s);*/
}
