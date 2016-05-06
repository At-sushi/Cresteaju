//---------------------------------
//---���w�֐�

//---��Βl
EI_API int eiAbs(int n)
{
	if(n < 0)
		return -n;
	return n;
}

/*
//---�O�p�֐��e�[�u���̏�����
//---�T�C���E�R�T�C���E�^���W�F���g�̃e�[�u��
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

//---�O�p�֐�
EI_API int eiSin(int n)
{
	return eiSinTable[n];
}

//---�O�p�֐�
EI_API int eiCos(int n)
{
	return eiCosTable[n];
}

//---��̍��W�̊p�x�𒲂ׂ�
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

//---�p�x�𒼂�
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
