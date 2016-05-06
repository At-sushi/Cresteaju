//-------------------------------------
eiD3DMatrix::eiD3DMatrix(void)
{
	lpd3dMatrix = NULL;
	hd3dMatrix= NULL;

	lpd3dMatrix = &d3dMatrix;
	eimemset(lpd3dMatrix,0,sizeof(d3dMatrix));

	SetCalcCamera(1.00f,1.00f,1.00f);
}

eiD3DMatrix::~eiD3DMatrix()
{
}

int eiD3DMatrix::Create(
	FLOAT m11,FLOAT m12,FLOAT m13,FLOAT m14,
	FLOAT m21,FLOAT m22,FLOAT m23,FLOAT m24,
	FLOAT m31,FLOAT m32,FLOAT m33,FLOAT m34,
	FLOAT m41,FLOAT m42,FLOAT m43,FLOAT m44)
{
	//---
	Set(0,0,m11);
	Set(0,1,m12);
	Set(0,2,m13);
	Set(0,3,m14);
	//---
	Set(1,0,m21);
	Set(1,1,m22);
	Set(1,2,m23);
	Set(1,3,m24);
	//---
	Set(2,0,m31);
	Set(2,1,m32);
	Set(2,2,m33);
	Set(2,3,m34);
	//---
	Set(3,0,m41);
	Set(3,1,m42);
	Set(3,2,m43);
	Set(3,3,m44);

	return 1;
}

//---任意の場所に行列の値をセット
void eiD3DMatrix::Set(int m,int n,FLOAT val)
{
	if(m == 0){
		if(n == 0)
			lpd3dMatrix->_11 = val;
		else if(n == 1)
			lpd3dMatrix->_12 = val;
		else if(n == 2)
			lpd3dMatrix->_13 = val;
		else if(n == 3)
			lpd3dMatrix->_14 = val;
	} else if(m == 1){
		if(n == 0)
			lpd3dMatrix->_21 = val;
		else if(n == 1)
			lpd3dMatrix->_22 = val;
		else if(n == 2)
			lpd3dMatrix->_23 = val;
		else if(n == 3)
			lpd3dMatrix->_24 = val;
	} else if(m == 2){
		if(n == 0)
			lpd3dMatrix->_31 = val;
		else if(n == 1)
			lpd3dMatrix->_32 = val;
		else if(n == 2)
			lpd3dMatrix->_33 = val;
		else if(n == 3)
			lpd3dMatrix->_34 = val;
	} else if(m == 3){
		if(n == 0)
			lpd3dMatrix->_41 = val;
		else if(n == 1)
			lpd3dMatrix->_42 = val;
		else if(n == 2)
			lpd3dMatrix->_43 = val;
		else if(n == 3)
			lpd3dMatrix->_44 = val;
	}
}

//---
FLOAT eiD3DMatrix::Get(int m,int n)
{
	FLOAT val;

	if(m == 0){
		if(n == 0)
			val = lpd3dMatrix->_11;
		else if(n == 1)
			val = lpd3dMatrix->_12;
		else if(n == 2)
			val = lpd3dMatrix->_13;
		else if(n == 3)
			val = lpd3dMatrix->_14;
	} else if(m == 1){
		if(n == 0)
			val = lpd3dMatrix->_21;
		else if(n == 1)
			val = lpd3dMatrix->_22;
		else if(n == 2)
			val = lpd3dMatrix->_23;
		else if(n == 3)
			val = lpd3dMatrix->_24;
	} else if(m == 2){
		if(n == 0)
			val = lpd3dMatrix->_31;
		else if(n == 1)
			val = lpd3dMatrix->_32;
		else if(n == 2)
			val = lpd3dMatrix->_33;
		else if(n == 3)
			val = lpd3dMatrix->_34;
	} else if(m == 3){
		if(n == 0)
			val = lpd3dMatrix->_41;
		else if(n == 1)
			val = lpd3dMatrix->_42;
		else if(n == 2)
			val = lpd3dMatrix->_43;
		else if(n == 3)
			val = lpd3dMatrix->_44;
	}

	return val;
}

void eiD3DMatrix::SetCalcCamera(float x,float y,float z)
{
	cx = x;
	cy = y;
	cz = z;
}

//---カメラ計算
void eiD3DMatrix::CalcCamera(D3DVECTOR from,D3DVECTOR at,D3DVECTOR world_up,float roll)
{
	eiD3DMatrix view;
	eiD3DMatrix rotz;
	D3DVECTOR  up, right, view_dir;
	
	IdentityMatrix();
	view.IdentityMatrix();
    
	view_dir = Normalize(at - from);
	right = CrossProduct(world_up, view_dir);
	up = CrossProduct(view_dir, right);
    
	right = Normalize(right);
	up = Normalize(up);
    
	view.Set(0, 0 ,right.x * cx);
	view.Set(1, 0 ,right.y * cy);
	view.Set(2, 0 ,right.z * cz);
	view.Set(0, 1 ,up.x * cx);
	view.Set(1, 1 ,up.y * cy);
	view.Set(2, 1 ,up.z * cz);
	view.Set(0, 2 ,view_dir.x * cx);
	view.Set(1, 2 ,view_dir.y * cy);
	view.Set(2, 2 ,view_dir.z * cz);

	view.Set(3, 0 ,-DotProduct(right, from));
	view.Set(3, 1 ,-DotProduct(up, from));
	view.Set(3, 2 ,-DotProduct(view_dir, from));

	if (roll != 0.0f) {
		rotz.RotateZ(-roll);
		MatrixMult(rotz, view); 
	} else {
		memcpy(lpd3dMatrix,view.lpd3dMatrix,sizeof(D3DMATRIX));
	}

/*
    D3DVECTOR vView = at - from;

    FLOAT fLength = Magnitude( vView );
    if( fLength < 1e-6f )
        return;

    vView /= fLength;

    FLOAT fDotProduct = DotProduct( world_up, vView );

    D3DVECTOR vUp = world_up - fDotProduct * vView;

    if( 1e-6f > ( fLength = Magnitude( vUp ) ) )
    {
        vUp = D3DVECTOR( 0.0f, 1.0f, 0.0f ) - vView.y * vView;

        if( 1e-6f > ( fLength = Magnitude( vUp ) ) )
        {
            vUp = D3DVECTOR( 0.0f, 0.0f, 1.0f ) - vView.z * vView;

            if( 1e-6f > ( fLength = Magnitude( vUp ) ) )
                return;
        }
    }

    vUp /= fLength;

    D3DVECTOR vRight = CrossProduct( vUp, vView );

    IdentityMatrix();
	lpd3dMatrix->_11 = vRight.x;
	lpd3dMatrix->_12 = vUp.x;
	lpd3dMatrix->_13 = vView.x;
	
	lpd3dMatrix->_21 = vRight.y;
	lpd3dMatrix->_22 = vUp.y;
	lpd3dMatrix->_23 = vView.y;
	
	lpd3dMatrix->_31 = vRight.z;
	lpd3dMatrix->_32 = vUp.z;
	lpd3dMatrix->_33 = vView.z;

	lpd3dMatrix->_41 = - DotProduct( from, vRight );
	lpd3dMatrix->_42 = - DotProduct( from, vUp );
	lpd3dMatrix->_43 = - DotProduct( from, vView );*/
}

void eiD3DMatrix::CalcCamera2(D3DVECTOR vFrom,D3DVECTOR vAt, D3DVECTOR vWorldUp )
{
	D3DVECTOR vView = vAt - vFrom;
	FLOAT fLength = Magnitude( vView );
	if( fLength < 1e-6f )
		return;

	vView /= fLength;
	
	FLOAT fDotProduct = DotProduct( vWorldUp, vView ); 
	D3DVECTOR vUp = vWorldUp - fDotProduct * vView; 

	if( 1e-6f > ( fLength = Magnitude( vUp ))){
		vUp = D3DVECTOR( 0.0f, 1.0f, 0.0f ) - vView.y * vView; 
		// If we still have near-zero length, resort to a different axis.
		if( 1e-6f > ( fLength = Magnitude( vUp ))){
			vUp = D3DVECTOR( 0.0f, 0.0f, 1.0f ) - vView.z * vView; 
			if( 1e-6f > ( fLength = Magnitude( vUp ) ) )
				return;
		}
	}

	vUp /= fLength;
	D3DVECTOR vRight = CrossProduct( vUp, vView );

	IdentityMatrix();
	Set(0,0,vRight.x);
	Set(0,1,vUp.x);
	Set(0,2,vView.x);
	Set(1,0,vRight.y);
	Set(1,1,vUp.y);
	Set(1,2,vView.y);
	Set(2,0,vRight.z);
	Set(2,1,vUp.z);
	Set(2,2,vView.z); 
	// Do the translation values (rotations are still about the eyepoint)
	Set(3,0,- DotProduct( vFrom, vRight ));
	Set(3,1,- DotProduct( vFrom, vUp ));
	Set(3,2,- DotProduct( vFrom, vView));
}

void eiD3DMatrix::CalcProjectionMatrix(
			const float near_plane, // 近くのクリッピング平面までの距離
			const float far_plane, // 遠くのクリッピング平面までの距離
			const float fov) // ラジアン単位で表したビュー フィールドの角度
{
//HRESULT D3DUtil_SetProjectionMatrix( D3DMATRIX& mat, FLOAT fFOV, FLOAT fAspect,
//                                     FLOAT fNearPlane, FLOAT fFarPlane )
//{
	if(fabs(far_plane - near_plane) < 0.01f )
		return;
	if(fabs(sin(fov/2)) < 0.01f )
		return;

	FLOAT fAspect = 1.0f;
	FLOAT w = fAspect * ( cosf(fov / 2)/sinf(fov / 2) );
	FLOAT h =   1.0f  * ( cosf(fov / 2)/sinf(fov / 2) );
	FLOAT Q = far_plane / ( far_plane - near_plane );

	ZeroMatrix();
    lpd3dMatrix->_11 = w;
    lpd3dMatrix->_22 = h;
	lpd3dMatrix->_33 = Q;
	lpd3dMatrix->_34 = 1.0f;
	lpd3dMatrix->_43 = -Q*near_plane;

	return;

/*	float    c, s;//, Q;

	c = (float)cos(fov*0.5);
	s = (float)sin(fov*0.5);
	Q = s/(1.0f - near_plane/far_plane);

	ZeroMatrix();

	Set(0, 0,c);
	Set(1, 1,c);

	Set(2, 2,Q);
	Set(3, 2,-Q * near_plane);
	Set(2, 3, s);*/
}

//---単位行列を作る
void eiD3DMatrix::IdentityMatrix(void)
{
	//---
	lpd3dMatrix->_11 = 1;
	lpd3dMatrix->_12 = 0;
	lpd3dMatrix->_13 = 0;
	lpd3dMatrix->_14 = 0;
	//---
	lpd3dMatrix->_21 = 0;
	lpd3dMatrix->_22 = 1;
	lpd3dMatrix->_23 = 0;
	lpd3dMatrix->_24 = 0;
	//---
	lpd3dMatrix->_31 = 0;
	lpd3dMatrix->_32 = 0;
	lpd3dMatrix->_33 = 1;
	lpd3dMatrix->_34 = 0;
	//---
	lpd3dMatrix->_41 = 0;
	lpd3dMatrix->_42 = 0;
	lpd3dMatrix->_43 = 0;
	lpd3dMatrix->_44 = 1;
}

void eiD3DMatrix::MatrixMult(eiD3DMatrix a,eiD3DMatrix b)  
{
	ZeroMatrix();
	
//	int i,j,k;

	//---------------------------------------
	lpd3dMatrix->_11 = b.lpd3dMatrix->_11 * a.lpd3dMatrix->_11
					+  b.lpd3dMatrix->_12 * a.lpd3dMatrix->_21
					+  b.lpd3dMatrix->_13 * a.lpd3dMatrix->_31
					+  b.lpd3dMatrix->_14 * a.lpd3dMatrix->_41;

	lpd3dMatrix->_12 = b.lpd3dMatrix->_11 * a.lpd3dMatrix->_12
					+  b.lpd3dMatrix->_12 * a.lpd3dMatrix->_22
					+  b.lpd3dMatrix->_13 * a.lpd3dMatrix->_32
					+  b.lpd3dMatrix->_14 * a.lpd3dMatrix->_42;

	lpd3dMatrix->_13 = b.lpd3dMatrix->_11 * a.lpd3dMatrix->_13
					+  b.lpd3dMatrix->_12 * a.lpd3dMatrix->_23
					+  b.lpd3dMatrix->_13 * a.lpd3dMatrix->_33
					+  b.lpd3dMatrix->_14 * a.lpd3dMatrix->_43;

	lpd3dMatrix->_14 = b.lpd3dMatrix->_11 * a.lpd3dMatrix->_14
					+  b.lpd3dMatrix->_12 * a.lpd3dMatrix->_24
					+  b.lpd3dMatrix->_13 * a.lpd3dMatrix->_34
					+  b.lpd3dMatrix->_14 * a.lpd3dMatrix->_44;

	//---------------------------------------
	lpd3dMatrix->_21 = b.lpd3dMatrix->_21 * a.lpd3dMatrix->_11
					+  b.lpd3dMatrix->_22 * a.lpd3dMatrix->_21
					+  b.lpd3dMatrix->_23 * a.lpd3dMatrix->_31
					+  b.lpd3dMatrix->_24 * a.lpd3dMatrix->_41;

	lpd3dMatrix->_22 = b.lpd3dMatrix->_21 * a.lpd3dMatrix->_12
					+  b.lpd3dMatrix->_22 * a.lpd3dMatrix->_22
					+  b.lpd3dMatrix->_23 * a.lpd3dMatrix->_32
					+  b.lpd3dMatrix->_24 * a.lpd3dMatrix->_42;

	lpd3dMatrix->_23 = b.lpd3dMatrix->_21 * a.lpd3dMatrix->_13
					+  b.lpd3dMatrix->_22 * a.lpd3dMatrix->_23
					+  b.lpd3dMatrix->_23 * a.lpd3dMatrix->_33
					+  b.lpd3dMatrix->_24 * a.lpd3dMatrix->_43;

	lpd3dMatrix->_24 = b.lpd3dMatrix->_21 * a.lpd3dMatrix->_14
					+  b.lpd3dMatrix->_22 * a.lpd3dMatrix->_24
					+  b.lpd3dMatrix->_23 * a.lpd3dMatrix->_34
					+  b.lpd3dMatrix->_24 * a.lpd3dMatrix->_44;

	//---------------------------------------
	lpd3dMatrix->_31 = b.lpd3dMatrix->_31 * a.lpd3dMatrix->_11
					+  b.lpd3dMatrix->_32 * a.lpd3dMatrix->_21
					+  b.lpd3dMatrix->_33 * a.lpd3dMatrix->_31
					+  b.lpd3dMatrix->_34 * a.lpd3dMatrix->_41;

	lpd3dMatrix->_32 = b.lpd3dMatrix->_31 * a.lpd3dMatrix->_12
					+  b.lpd3dMatrix->_32 * a.lpd3dMatrix->_22
					+  b.lpd3dMatrix->_33 * a.lpd3dMatrix->_32
					+  b.lpd3dMatrix->_34 * a.lpd3dMatrix->_42;

	lpd3dMatrix->_33 = b.lpd3dMatrix->_31 * a.lpd3dMatrix->_13
					+  b.lpd3dMatrix->_32 * a.lpd3dMatrix->_23
					+  b.lpd3dMatrix->_33 * a.lpd3dMatrix->_33
					+  b.lpd3dMatrix->_34 * a.lpd3dMatrix->_43;

	lpd3dMatrix->_34 = b.lpd3dMatrix->_31 * a.lpd3dMatrix->_14
					+  b.lpd3dMatrix->_32 * a.lpd3dMatrix->_24
					+  b.lpd3dMatrix->_33 * a.lpd3dMatrix->_34
					+  b.lpd3dMatrix->_34 * a.lpd3dMatrix->_44;

	//---------------------------------------
	lpd3dMatrix->_41 = b.lpd3dMatrix->_41 * a.lpd3dMatrix->_11
					+  b.lpd3dMatrix->_42 * a.lpd3dMatrix->_21
					+  b.lpd3dMatrix->_43 * a.lpd3dMatrix->_31
					+  b.lpd3dMatrix->_44 * a.lpd3dMatrix->_41;

	lpd3dMatrix->_42 = b.lpd3dMatrix->_41 * a.lpd3dMatrix->_12
					+  b.lpd3dMatrix->_42 * a.lpd3dMatrix->_22
					+  b.lpd3dMatrix->_43 * a.lpd3dMatrix->_32
					+  b.lpd3dMatrix->_44 * a.lpd3dMatrix->_42;

	lpd3dMatrix->_43 = b.lpd3dMatrix->_41 * a.lpd3dMatrix->_13
					+  b.lpd3dMatrix->_42 * a.lpd3dMatrix->_23
					+  b.lpd3dMatrix->_43 * a.lpd3dMatrix->_33
					+  b.lpd3dMatrix->_44 * a.lpd3dMatrix->_43;

	lpd3dMatrix->_44 = b.lpd3dMatrix->_41 * a.lpd3dMatrix->_14
					+  b.lpd3dMatrix->_42 * a.lpd3dMatrix->_24
					+  b.lpd3dMatrix->_43 * a.lpd3dMatrix->_34
					+  b.lpd3dMatrix->_44 * a.lpd3dMatrix->_44;
/*
	for(i = 0;i< 4;i ++) {
		for(j = 0;j < 4;j ++) {
			for(k = 0;k < 4;k ++) {
//				Set(i, j,Get(i,j) + a.Get(j, k) * b.Get(k, i));
				Set(i, j,Get(i,j) + a.Get(k, j) * b.Get(i, k));
//				ret(i, j) += a(k, j) * b(i, k);
			}
		}
	}*/
}

void eiD3DMatrix::ZeroMatrix(void)
{
	//---
	lpd3dMatrix->_11 = 0;
	lpd3dMatrix->_12 = 0;
	lpd3dMatrix->_13 = 0;
	lpd3dMatrix->_14 = 0;
	//---
	lpd3dMatrix->_21 = 0;
	lpd3dMatrix->_22 = 0;
	lpd3dMatrix->_23 = 0;
	lpd3dMatrix->_24 = 0;
	//---
	lpd3dMatrix->_31 = 0;
	lpd3dMatrix->_32 = 0;
	lpd3dMatrix->_33 = 0;
	lpd3dMatrix->_34 = 0;
	//---
	lpd3dMatrix->_41 = 0;
	lpd3dMatrix->_42 = 0;
	lpd3dMatrix->_43 = 0;
	lpd3dMatrix->_44 = 0;
}

//---回転
void eiD3DMatrix::RotateX(const float rads)
{
    float cosine, sine;

	cosine = (FLOAT)cos(rads);
	sine = (FLOAT)sin(rads);
	
	IdentityMatrix();
	Set(1,1 ,cosine);
	Set(2,2 ,cosine);
	Set(1,2 ,-sine);
	Set(2,1 ,sine);
}

void eiD3DMatrix::RotateY(const float rads)
{
	float cosine, sine;
	
	cosine = (FLOAT)cos(rads);
	sine = (FLOAT)sin(rads);
	
	IdentityMatrix();
	Set(0,0 ,cosine);
	Set(2,2 ,cosine);
	Set(0,2 ,sine);
	Set(2,0 ,-sine);
}

void eiD3DMatrix::RotateZ(const float rads)
{
	float cosine, sine;

	cosine = (FLOAT)cos(rads);
	sine = (FLOAT)sin(rads);
    
	IdentityMatrix();
	Set(0,0 ,cosine);
	Set(1,1 ,cosine);
	Set(0,1 ,-sine);
	Set(1,0 ,sine);
}

//---平行移動
void eiD3DMatrix::Move(float x,float y,float z)
{
	IdentityMatrix();

	Set(3,0,x);
	Set(3,1,y);
	Set(3,2,z);
}
