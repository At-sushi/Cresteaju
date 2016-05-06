//---------------------------------
//---数学関数

//---絶対値
EI_API int eiAbs(int n)
{
	if(n < 0)
		return -n;
	return n;
}

/*
//---三角関数テーブルの初期化
//---サイン・コサイン・タンジェントのテーブル
int eiSinTable[360],eiCosTable[360],eiaTanTable[1024];
void eiInitSinTable(void)
{
	int a;
	double f,rd = 3.141592 / 128.00000;

	for(a = 0;a < 256;a ++){
		f = sin((double)a * rd);
		f = f * 256.000;
		eiSinTable[a] = (int)f;

		f = cos((double)a * rd);
		f = f * 256.000;
		eiCosTable[a] = (int)f;

	}

	for(a = 0;a < 800;a ++){
		f = atan((double)a / 16);
		f = (f / rd);
		eiaTanTable[a] = (int)f;
	}
}

//---三角関数
EI_API int eiSin(int n)
{
	return eiSinTable[n];
}

//---三角関数
EI_API int eiCos(int n)
{
	return eiCosTable[n];
}

//---二つの座標の角度を調べる
EI_API int eiGetAngle(int x1,int y1,int x2,int y2)
{
	int c,sx,sy;

	sx = x1 - x2;
	sy = y1 - y2;
	if(sx != 0){
		c = (eiAbs(sy) << 4) / eiAbs(sx);
		if(c < 800)
			c = eiaTanTable[c];
		else
			c = 64;

		if(sx > 0 && sy > 0)
			c += 128;
		else if(sx > 0 && sy < 0)
			c = (128 - c);
		else if(sx < 0 && sy > 0)
			c = (256 - c);
	} else {
		if(sy < 0)
			c = 64;
		else 
			c = 192;
	}

	return c;
}

//---角度を直す
EI_API void eiCheckAngle(int *n)
{
	if(*n < 0){
		*n += 256;
	}
	if(*n >= 256){
		*n -= 256;
	}
}
*/
