//-------------------------------------------------
//-------------------------------------------------
//---バトルダメージクラス
CrBattleDamage::CrBattleDamage(void)
{
	int a;

	for(a = 0;a < 5;a ++){
		Time[a] = 0;
	}
}

CrBattleDamage::~CrBattleDamage()
{
}

void CrBattleDamage::SetCharacter(CrBattleCharacter *pChara)
{
	int a;

	CenterX = pChara->GetFieldX();
	CenterY = pChara->GetFieldY();
	CenterZ = pChara->GetFieldZ();

	for(a = 0;a < 5;a ++){
		z[a] = -4.0f;
		dz[a] = -0.50f;
	}
}

void CrBattleDamage::SetDamage(int damage,int miss,int mode)
{
	int a,b,c,number;

	Damage = damage;
	DamageMode = mode;

	if(miss && mode <= DAMAGEMODE_SUB){
		Number[0] = BAT_DAMAGENULL;
		Number[1] = 20;
		Number[2] = 21;
		Number[3] = 22;
		Number[4] = 22;
		return;
	}

	if(damage == 0){
		Number[0] = BAT_DAMAGENULL;
		Number[1] = BAT_DAMAGENULL;
		Number[2] = BAT_DAMAGENULL;
		Number[3] = BAT_DAMAGENULL;
		Number[4] = 0;
		return;
	}

	//---数字パターンに変換
	for(a = 0,b = 10000,c = 0;a < 5;a ++,b /= 10){
		number = damage / b;
		damage -= (number * b);
		if(number){
			c ++;
		} else if(!number && c == 0){
			number = BAT_DAMAGENULL;
		}
		if((mode == DAMAGEMODE_ADD || mode == DAMAGEMODE_ADDMC) && number != BAT_DAMAGENULL){
			number += 10;
		}

		Number[a] = number;
	}

}

void CrBattleDamage::SetDelay(int del)
{
	int a,b;

	for(a = 0,b = 0;a < 5;a ++){
/*		if(Number[a] == BAT_DAMAGENULL){
			Delay[a] = 0;
			continue;
		}
*/
		Delay[a] = del + b * 20;
		b ++;
	}
}

//---時間を進める
int CrBattleDamage::AddWorld(float world)
{
	int a,flag = 1;
	float add;

	for(a = 0;a < 5;a ++){
		//---Delay
		add = world;
		if(Delay[a] > 0){
			Delay[a] -= (int)add;
			if(Delay[a] > 0){
				flag &= 0;
				continue;
			}
			add = (float)-Delay[a];
			Delay[a] = 0;
		}

		Time[a] += (int)add;
		z[a] = -4.0f + (-0.60f * (float)Time[a])
			+ (0.50f * 0.007f * (float)Time[a] * (float)Time[a]);
//		z[a] += ((float)add * dz[a]);
//		dz[a] += ((float)add * 0.007f);

		if(z[a] >= 0.0f){
			z[a] = 0.0f;
		} else {
			flag &= 0;
		}
	}

	return flag;
}

//---描く
void CrBattleDamage::Draw(void)
{
	int a,cx,cy,x,y,center;
	float px,py,pz;

	//---頂点バッファーをロックしてデータ書き込み
	{
		D3DVERTEX *pVer = (D3DVERTEX *)vbSrc.Lock();
		if(!pVer)
			return;

		crbatTranslatePos((float)CenterX,(float)CenterY,(float)CenterZ,&px,&py,&pz);
		pVer[0] = D3DVERTEX( D3DVECTOR(px,pz,py), D3DVECTOR(0.0f,0.0f,0.0f),D3DVAL(0.0f),D3DVAL(0.0f));
		vbSrc.Unlock();
	}

	//---座標変換
	vbSrc.Process(&vbDest,1);

	{
		D3DTLVERTEX *pDstVer = (D3DTLVERTEX *)vbDest.Lock();
		cx = (int)pDstVer[0].sx;
		cy = (int)pDstVer[0].sy;
		pz = pDstVer[0].sz;
		vbDest.Unlock();
	}
	if(pz < 0.50f){
		//---描く範囲内にあれば
		return;
	}

	RECT rect = BattleViewRect[BATTLE_VIEWMODE_SINGLE][0];
	rect.right += rect.left;
	rect.bottom += rect.top;
	ew->lpCell[1]->SetClipingRect(&rect);

	for(center = 0;Number[center] == BAT_DAMAGENULL;center ++){
	}

	for(a = 0;a < 5;a ++){
		if(Delay[a] > 0){
			continue;
		}
		x = cx - (8 * (5 + center)) + (16 * a);
		y = cy - 16;
		pBattleFontCell[Number[a]].PutTransClip(ew->lpCell[1],x,y + (int)z[a]);
	}

	RECT rect2 = {0,0,640,480};
	ew->lpCell[1]->SetClipingRect(&rect2);
}
