//-------------------------------------------------
//-------------------------------------------------
CrBattleObject::CrBattleObject(void)
{
	Init();
}

CrBattleObject::~CrBattleObject()
{
/*	memset(&ObjectInfo,0,sizeof(ObjectInfo));
	ObjectInfo.x = ObjectInfo.y = ObjectInfo.z = 
		ObjectInfo.dx = ObjectInfo.dy = ObjectInfo.dz = 0.0f;

	ObjectInfo.XRate = 1.0f;
	ObjectInfo.YRate = 1.0f;*/
}

void CrBattleObject::Init(void)
{
	eimemset(&ObjectInfo,0,sizeof(ObjectInfo));

	pCell = NULL;
	ObjectInfo.pTex = NULL;

	ObjectInfo.x = ObjectInfo.y = ObjectInfo.z = 
		ObjectInfo.dx = ObjectInfo.dy = ObjectInfo.dz = 0.0f;

	ObjectInfo.XRate = 1.0f;
	ObjectInfo.YRate = 1.0f;
}

void CrBattleObject::CreateTLVertexRect(float r,int alpha)
{
	int a;
	ObjectInfo.RSize = r;
	ObjectInfo.DrawMode = 1;

	for(a = 0;a < 4;a ++){
		ObjectInfo.tlVertex[a].color = RGBA_MAKE(255,255,255,alpha);
		ObjectInfo.tlVertex[a].dvRHW = D3DVAL(1.0);
	}

	ObjectInfo.tlVertex[0].sx = -r / 2;
	ObjectInfo.tlVertex[0].sy = -r / 2;
	ObjectInfo.tlVertex[0].sz = 0;
	ObjectInfo.tlVertex[0].tu = D3DVALUE(0.0);
	ObjectInfo.tlVertex[0].tv = D3DVALUE(0.0);

	ObjectInfo.tlVertex[1].sx = r / 2;
	ObjectInfo.tlVertex[1].sy = -r / 2;
	ObjectInfo.tlVertex[1].sz = 0;
	ObjectInfo.tlVertex[1].tu = D3DVALUE(1.0);
	ObjectInfo.tlVertex[1].tv = D3DVALUE(0.0);

	ObjectInfo.tlVertex[2].sx = -r / 2;
	ObjectInfo.tlVertex[2].sy = r / 2;
	ObjectInfo.tlVertex[2].sz = 0;
	ObjectInfo.tlVertex[2].tu = D3DVALUE(0.0);
	ObjectInfo.tlVertex[2].tv = D3DVALUE(1.0);

	ObjectInfo.tlVertex[3].sx = r / 2;
	ObjectInfo.tlVertex[3].sy = r / 2;
	ObjectInfo.tlVertex[3].sz = 0;
	ObjectInfo.tlVertex[3].tu = D3DVALUE(1.0);
	ObjectInfo.tlVertex[3].tv = D3DVALUE(1.0);
}

void CrBattleObject::SetAlphaMode(int mode)
{
	ObjectInfo.AlphaMode = mode;
}

void CrBattleObject::SetDrawMode(int mode)
{
	ObjectInfo.DrawMode = mode;
}

void CrBattleObject::SetXRate(float rate)
{
	ObjectInfo.XRate = rate;
}

void CrBattleObject::SetYRate(float rate)
{
	ObjectInfo.YRate = rate;
}

void CrBattleObject::SetTexture(eiTextureCell *pc)
{
	ObjectInfo.pTex = pc;
}

void CrBattleObject::SetCell(eiCell *pc)
{
	ObjectInfo.pCell = pc;
}

eiCell *CrBattleObject::GetCell(void)
{
	return ObjectInfo.pCell;
}

void CrBattleObject::SetPattern(int pattern)
{
	ObjectInfo.Pattern = pattern;
}

int CrBattleObject::GetPattern(void)
{
	return ObjectInfo.Pattern;
}

void CrBattleObject::SetPos(float sx,float sy,float sz)
{
	ObjectInfo.x = sx;
	ObjectInfo.y = sy;
	ObjectInfo.z = sz;
}

float CrBattleObject::GetX(void)
{
	return ObjectInfo.x;
}

float CrBattleObject::GetY(void)
{
	return ObjectInfo.y;
}

float CrBattleObject::GetZ(void)
{
	return ObjectInfo.z;
}


//---移動ベクトル設定
void CrBattleObject::SetMoveVectorXYZ(float x,float y,float z)
{
	//---正規化
	float r = (float)(1.00 / pow(x * x + y * y + z * z,0.333333));

	ObjectInfo.vx = (float)(x * r);
	ObjectInfo.vy = (float)(y * r);
	ObjectInfo.vz = (float)(z * r);
}
//----------------------------------------
//---アニメーション種類を設定
void CrBattleObject::SetAnime(int number)
{
	ObjectInfo.Pattern = 0;
	ObjectInfo.AnimeMode = number;
	ObjectInfo.AnimeMax = AnimePatternCount[number];
	ObjectInfo.AnimeWait = BattleAnimeWait[number];

	SetCell(&BattleAnimeCell[0]);
}

void CrBattleObject::SetMoveSpeed(float speed)
{
	ObjectInfo.MoveSpeed = speed;
}

int CrBattleObject::Move(float AddWorld)
{
	ObjectInfo.x += (float)((float)ObjectInfo.MoveSpeed * ObjectInfo.vx * (float)AddWorld);
	ObjectInfo.y += (float)((float)ObjectInfo.MoveSpeed * ObjectInfo.vy * (float)AddWorld);
	ObjectInfo.z += (float)((float)ObjectInfo.MoveSpeed * ObjectInfo.vz * (float)AddWorld);

	return 1;
}

//---フレームが動く
int CrBattleObject::DoAnime(float AddWorld)
{
/*	//---移動ベクトル
	ObjectInfo.x += (float)((float)OnlyInfo.MoveSpeed * (float)cos(OnlyInfo.MoveAngle) * (float)AddWorld );
	ObjectInfo.y += (float)((float)OnlyInfo.MoveSpeed * (float)sin(OnlyInfo.MoveAngle) * (float)AddWorld );
*/
	ObjectInfo.DeltaTime += (float)AddWorld;
	ObjectInfo.LimitTime -= (float)AddWorld;

	//---アニメーション
	if(ObjectInfo.AnimeWait){
		if(ObjectInfo.DeltaTime >= ObjectInfo.AnimeWait){
			ObjectInfo.DeltaTime = 0.0f;
			if(ObjectInfo.Pattern < ObjectInfo.AnimeMax){
				ObjectInfo.Pattern ++;
			} else {
				//---アニメーション終了
				return 0;
			}
		}
	}

/*	if(ObjectInfo.LimitTime <= 0.0f){
		//---到達している
		//---座標を目標地点にする
		ObjectInfo.ax = OnlyInfo.dx;
		ObjectInfo.ay = OnlyInfo.dy;

		return 0;
	}*/

	return 1;
}
