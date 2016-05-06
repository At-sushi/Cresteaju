
static EID3DPARTICLEINFO ParticleGlobalInfo;
static float ParticleG,ParticleMoveSpeed;

EI_API void eiD3DParticle_SetG(float g)
{
	ParticleG = g;
}

EI_API void eiD3DParticle_GlobalMoveSpeed(float speed)
{
	ParticleMoveSpeed = speed;
}

EI_API void eiD3DParticle_GlobalVectorXYZ(float x,float y,float z)
{
	float r = (float)(1.00 / pow(x * x + y * y + z * z,0.3333333));

	ParticleGlobalInfo.vx = (float)(x * r);
	ParticleGlobalInfo.vy = (float)(y * r);
	ParticleGlobalInfo.vz = (float)(z * r);
}

EI_API void eiD3DParticle_GlobalVectorAngle(float xy_angle,float xy_z_angle,float r)
{
	float x,y,z,t;

	z = (float)(r * sin(xy_z_angle));
	t = (float)(r * cos(xy_z_angle));
	x = (float)(t * cos(xy_angle));
	y = (float)(t * sin(xy_angle));

	eiD3DParticle_GlobalVectorXYZ(x,y,z);
}

eiD3DParticle::eiD3DParticle(void)
{
	eimemset(&Info,0,sizeof(Info));
	Matrix.IdentityMatrix();
	SetWeight(1);
}

void eiD3DParticle::CreateTriangle(
		float x1,float y1,float z1,
		float x2,float y2,float z2,
		float x3,float y3,float z3)
{

	D3DVECTOR vNormal( D3DVAL(0.0f), D3DVAL(1.0f), D3DVAL(0.0f) );
	float tu[] = {0.0f,1.0f,0.0f},tv[] = {0.0f,0.0f,1.0f};

	memset(&Info,0,sizeof(Info));
	Matrix.IdentityMatrix();

	Info.Vertex[0] = D3DVERTEX(
		D3DVECTOR(x1,y1,z1), vNormal,D3DVAL(tu[0]),D3DVAL(tv[0]));
	Info.Vertex[1] = D3DVERTEX(
		D3DVECTOR(x2,y2,z2), vNormal,D3DVAL(tu[1]),D3DVAL(tv[1]));
	Info.Vertex[2] = D3DVERTEX(
		D3DVECTOR(x3,y3,z3), vNormal,D3DVAL(tu[2]),D3DVAL(tv[2]));

//	memcpy(&Info.StartVertex[0],&Info.Vertex[0],sizeof(Info.StartVertex));

	Matrix.IdentityMatrix();
}

//---パーティクル作成
void eiD3DParticle::CreateTriangle(float r)
{
	int a;
	float Offset = (float)((float)eiRnd(360) * 3.1415 / 180),
		angle = (float)((float)eiRnd(1000) / 1000);

	memset(&Info,0,sizeof(Info));
	Matrix.IdentityMatrix();

	D3DVECTOR vNormal( D3DVAL(0.0f), D3DVAL(0.0f), D3DVAL(1.0f) );
	D3DVECTOR p1;
	float tu[] = {0.0f,1.0f,0.0f},tv[] = {0.0f,0.0f,1.0f};

	for(a = 0;a < 3;a ++){
		p1.x = (float)(r * cos((a * 120) * (3.1415 / 180) + Offset));
		p1.y = (float)(r * sin((a * 120) * (3.1415 / 180) + Offset));
		p1.z = 0.0f;
		Info.Vertex[a] = D3DVERTEX( p1, vNormal,D3DVAL(tu[a]),D3DVAL(tv[a]));
	}
//	memcpy(&Info.StartVertex[0],&Info.Vertex[0],sizeof(Info.StartVertex));

	eiD3DMatrix temp1,temp2,temp3,temp4;

	temp1.RotateX((float)eiRnd(360) * 3.1415f / 180.0f);
	temp2.RotateY((float)eiRnd(360) * 3.1415f / 180.0f);
	temp3.RotateZ((float)eiRnd(360) * 3.1415f / 180.0f);

	temp4.MatrixMult(temp1,temp2);
	Matrix.IdentityMatrix();
	Matrix.MatrixMult(temp4,temp3);
}

#define PI 3.141592


void eiD3DParticle::CreateRandomTriangle(float r,float dr,int count)
{
	int a,b;
	float dis_x,dis_y,dis_z,div;
	D3DVERTEX *ver,*kver;

	memset(&Info,0,sizeof(Info));
	Matrix.IdentityMatrix();

	Info.hMemory = eiAllocMemory(count * sizeof(D3DVERTEX) * 4);
	Info.MemorySize = count * sizeof(D3DVERTEX) * 4;
	ver = Info.pVertex = (D3DVERTEX * )eiLockMemory(Info.hMemory);

	Info.hStartMemory = eiAllocMemory(count * sizeof(D3DVERTEX) * 4);
	kver = Info.pStartVertex = (D3DVERTEX * )eiLockMemory(Info.hStartMemory);

	for(b = 0;b < count;b ++){
		float Offset = (float)((float)eiRnd(360) * 3.1415 / 180),
			angle = (float)((float)eiRnd(1000) / 1000);

		D3DVECTOR vNormal( D3DVAL(0.0f), D3DVAL(1.0f), D3DVAL(0.0f) );
		D3DVECTOR p1;

		float tu[] = {0.0f,1.0f,0.0f},tv[] = {0.0f,0.0f,1.0f};

		dis_x = (float)(eiRnd(2000) - 1000) / 1000.0f * r;
		dis_y = (float)(eiRnd(2000) - 0) / 1000.0f * r;
		dis_z = (float)(eiRnd(2000) - 1000) / 1000.0f * r;
		for(a = 0;a < 3;a ++){
			p1.x = (float)eiRnd(5) / 5.0f * dr + dis_x;
			p1.y = (float)eiRnd(5) / 5.0f * dr + dis_y;
			p1.z = (float)eiRnd(5) / 5.0f * dr + dis_z;

			div = (float)sqrt(p1.x * p1.x + p1.y * p1.y + p1.z * p1.z);
			vNormal.x = (float)p1.x / div;
			vNormal.y = (float)p1.y / div;
			vNormal.z = (float)p1.z / div;
			div = (float)sqrt(vNormal.x * vNormal.x + vNormal.y * vNormal.y + vNormal.z * vNormal.z);

//---修正
//			vNormal = Normalize(D3DVECTOR(p1.x,p1.y,p1.z));
//			div2 = (float)sqrt(vNormal.x * vNormal.x + vNormal.y * vNormal.y + vNormal.z * vNormal.z);

			kver[a] = ver[a] = D3DVERTEX( p1, vNormal,D3DVAL(tu[a]),D3DVAL(tv[a]));

/*			char s[30];
			sprintf(s,"%f  %f\n",div / div2,div2);
			eiDebugWriteFile(s);*/

//			vNormal = -vNormal;
//			ver[a + 3] = D3DVERTEX( p1, vNormal,D3DVAL(tu[a]),D3DVAL(tv[a]));
		}
		kver += 3;
		ver += 3;
	}
	Info.VertexCount = count * 3;
}

//---球を作る
void eiD3DParticle::CreateSphere(float r,int x_div,int y_div
						,float start /*= 0.0f*/,float end /*= 6.283184f*/)
{
	int a,count = x_div * y_div * 2 * 12;
	double x,x_add = PI * 2 / (double)x_div;
	double y,y_add = PI * 2 / (double)y_div;
	double prev_pos_1[3] = {0.0,0.0,0.0},
		prev_pos_2[3] = {0.0,0.0,0.0};
	double dx,dy,dz,dd;
	float dr;
	D3DVERTEX *ver,*kver;;

	memset(&Info,0,sizeof(Info));
	Matrix.IdentityMatrix();

	Info.hMemory = eiAllocMemory(count * sizeof(D3DVERTEX));
	Info.MemorySize = count * sizeof(D3DVERTEX);
	ver = Info.pVertex = (D3DVERTEX * )eiLockMemory(Info.hMemory);

	Info.hStartMemory = eiAllocMemory(count * sizeof(D3DVERTEX));
	kver = Info.pStartVertex = (D3DVERTEX * )eiLockMemory(Info.hStartMemory);

	Info.VertexCount = count;

	count = 0;
	double hs = 1.0;
	for(a = 0;a < 2;a ++){
		if(a == 0)
			dr = r;
		else
			dr = -r;
		for(y = start;y < end;y += y_add){
			for(x = 0;x < PI * 2;x += x_add){
				//---
				dy = sin(y) * r * hs;
				dd = cos(y) * r;
				dx = cos(x) * (dd);
				dz = sin(x) * (dd);
				ver[0].nx = ver[0].x = (FLOAT)dx;
				ver[0].ny = ver[0].y = (FLOAT)dy;
				ver[0].nz = ver[0].z = (FLOAT)dz;
				ver[0].nx /= dr;
				ver[0].ny /= dr;
				ver[0].nz /= dr;
				ver[0].tu = D3DVAL(0.0);
				ver[0].tv = D3DVAL(0.0);
				kver[0] = ver[0];

				//---
				dy = sin(y) * r * hs;
				dd = cos(y) * r;
				dx = cos(x + x_add) * (dd);
				dz = sin(x + x_add) * (dd);
				ver[1].nx = ver[1].x = (FLOAT)dx;
				ver[1].ny = ver[1].y = (FLOAT)dy;
				ver[1].nz = ver[1].z = (FLOAT)dz;
				ver[1].nx /= dr;
				ver[1].ny /= dr;
				ver[1].nz /= dr;
				ver[1].tu = D3DVAL(1.0);
				ver[1].tv = D3DVAL(0.0);
				kver[1] = ver[1];
				//---
				dy = sin(y + y_add) * r * hs;
				dd = cos(y + y_add) * r;
				dx = cos(x) * (dd);
				dz = sin(x) * (dd);
				ver[2].nx = ver[2].x = (FLOAT)dx;
				ver[2].ny = ver[2].y = (FLOAT)dy;
				ver[2].nz = ver[2].z = (FLOAT)dz;
				ver[2].nx /= dr;
				ver[2].ny /= dr;
				ver[2].nz /= dr;
				ver[2].tu = D3DVAL(0.0);
				ver[2].tv = D3DVAL(1.0);
				kver[2] = ver[2];

				ver += 3;
				kver += 3;
				count += 3;

				//---------------------
				//---
				dy = sin(y) * r * hs;
				dd = cos(y) * r;
				dx = cos(x + x_add) * (dd);
				dz = sin(x + x_add) * (dd);
				ver[0].nx = ver[0].x = (FLOAT)dx;
				ver[0].ny = ver[0].y = (FLOAT)dy;
				ver[0].nz = ver[0].z = (FLOAT)dz;
				ver[0].nx /= dr;
				ver[0].ny /= dr;
				ver[0].nz /= dr;
				ver[0].tu = D3DVAL(1.0);
				ver[0].tv = D3DVAL(0.0);
				kver[0] = ver[0];
				//---
				dy = sin(y + y_add) * r * hs;
				dd = cos(y + y_add) * r;
				dx = cos(x) * (dd);
				dz = sin(x) * (dd);
				ver[1].nx = ver[1].x = (FLOAT)dx;
				ver[1].ny = ver[1].y = (FLOAT)dy;
				ver[1].nz = ver[1].z = (FLOAT)dz;
				ver[1].nx /= dr;
				ver[1].ny /= dr;
				ver[1].nz /= dr;
				ver[1].tu = D3DVAL(0.0);
				ver[1].tv = D3DVAL(1.0);
				kver[1] = ver[1];
				//---
				dy = sin(y + y_add) * r * hs;
				dd = cos(y + y_add) * r;
				dx = cos(x + x_add) * (dd);
				dz = sin(x + x_add) * (dd);
				ver[2].nx = ver[2].x = (FLOAT)dx;
				ver[2].ny = ver[2].y = (FLOAT)dy;
				ver[2].nz = ver[2].z = (FLOAT)dz;
				ver[2].nx /= dr;
				ver[2].ny /= dr;
				ver[2].nz /= dr;
				ver[2].tu = D3DVAL(1.0);
				ver[2].tv = D3DVAL(1.0);
				kver[2] = ver[2];


				ver += 3;
				kver += 3;
				count += 3;
			}
		}
	}
	Info.VertexCount = count;

	Matrix.IdentityMatrix();
}

void eiD3DParticle::Release(void)
{
	if(Info.hMemory != NULL){
		eiFreeMemory(Info.hMemory);
		Info.hMemory = NULL;
		Info.pVertex = NULL;
	}
	if(Info.hStartMemory != NULL){
		eiFreeMemory(Info.hStartMemory);
		Info.hStartMemory = NULL;
		Info.pStartVertex = NULL;
	}
}

//---動く
float eiD3DParticle::MoveFrame(float AddWorld)
{
	//---移動ベクトルを重力などで可変させる
	//---重力
	Info.vy -= (ParticleG * AddWorld * Info.Weight);
	Info.vx += (ParticleGlobalInfo.vx * ParticleMoveSpeed * AddWorld);
	Info.vy += (ParticleGlobalInfo.vy * ParticleMoveSpeed * AddWorld);
	Info.vz += (ParticleGlobalInfo.vz * ParticleMoveSpeed * AddWorld);

	//---座標計算
	Info.wx += ((Info.vx * Info.MoveSpeed) * AddWorld);
	Info.wy += ((Info.vy * Info.MoveSpeed) * AddWorld);
	Info.wz += ((Info.vz * Info.MoveSpeed) * AddWorld);

	Info.AngleX += (Info.RotateX * AddWorld);
	Info.AngleY += (Info.RotateY * AddWorld);
	Info.AngleZ += (Info.RotateZ * AddWorld);

	return 0.0f;
}

void eiD3DParticle::SetWeight(int weight)
{
	Info.Weight = weight;
}

void eiD3DParticle::SetMoveSpeed(float speed)
{
	Info.MoveSpeed = speed;
}

//---移動ベクトル設定
void eiD3DParticle::SetMoveVectorXYZ(float x,float y,float z)
{
	//---正規化
	float r,s;
	
	s = (float)pow(x * x + y * y + z * z,0.3333333);//0.5じゃなくて
	if(s != 0){
		r = (float)(1.00 / s);
	} else {
		r = 0;
	}

	if(x == y && y == z && z == 0){
		Info.vx = 0;
		Info.vy = 0;
		Info.vz = 0;
	} else {
		Info.vx = (float)(x * r);
		Info.vy = (float)(y * r);
		Info.vz = (float)(z * r);
	}
}

void eiD3DParticle::SetMoveVectorAngle(float xy_angle,float xy_z_angle,float r)
{
	float x,y,z,t;

	z = (float)(r * sin(xy_z_angle));
	t = (float)(r * cos(xy_z_angle));
	x = (float)(t * cos(xy_angle));
	y = (float)(t * sin(xy_angle));

	SetMoveVectorXYZ(x,y,z);
}

void eiD3DParticle::SetMoveRotation(float xr,float yr)
{
	Info.RotateX = xr;
	Info.RotateY = yr;
}

void eiD3DParticle::SetMoveRotation(float xr,float yr,float zr)
{
	Info.RotateZ = zr;
	SetMoveRotation(xr,yr);
}

void eiD3DParticle::SetRotationMode(int mode)
{
	Info.RotationFlag = mode;
}


void eiD3DParticle::SetXAngle(float angle)
{
	Info.AngleX = angle;
}

void eiD3DParticle::SetYAngle(float angle)
{
	Info.AngleY = angle;
}

void eiD3DParticle::SetZAngle(float angle)
{
	Info.AngleZ = angle;
}

//---ワールド座標
void eiD3DParticle::SetWorldPos(float x,float y,float z)
{
	Info.wx = x;
	Info.wy = y;
	Info.wz = z;
}

static eiD3DMatrix prtmat,submat1,submat2,submat3,submat4,submat5,submat6;
static eiD3D prteid3d;

void eiD3DParticle::Draw(int ver_count /*= -1*/)
{

	if(Info.RotationFlag == 0){
		*prtmat.lpd3dMatrix = *Matrix.lpd3dMatrix;
//		prtmat.Move(Info.wx,Info.wy,Info.wz);
//		prtmat.IdentityMatrix();
		prtmat.Set(3,0,Info.wx + prtmat.Get(3,0));
		prtmat.Set(3,1,Info.wy + prtmat.Get(3,1));
		prtmat.Set(3,2,Info.wz + prtmat.Get(3,2));
	} else {
		submat1.IdentityMatrix();
		submat1.Set(3,0,Info.wx);
		submat1.Set(3,1,Info.wy);
		submat1.Set(3,2,Info.wz);

		if(Info.AngleX == 0){
			submat3.IdentityMatrix();
			submat3.RotateY(Info.AngleY);
			prtmat.MatrixMult(submat1,submat3);
		} else if(Info.AngleY == 0){
			submat2.IdentityMatrix();
			submat2.RotateX(Info.AngleX);
			prtmat.MatrixMult(submat1,submat2);
		} else {
			if(Info.AngleZ == 0){
				submat2.IdentityMatrix();
				submat2.RotateX(Info.AngleX);
				submat3.IdentityMatrix();
				submat3.RotateY(Info.AngleY);

				submat4.MatrixMult(submat2,submat3);
				prtmat.MatrixMult(submat1,submat4);
			} else {
				submat2.IdentityMatrix();
				submat2.RotateX(Info.AngleX);
				submat3.IdentityMatrix();
				submat3.RotateY(Info.AngleY);
				submat4.IdentityMatrix();
				submat4.RotateZ(Info.AngleZ);

				submat5.MatrixMult(submat2,submat3);
				submat6.MatrixMult(submat4,submat5);
				prtmat.MatrixMult(submat1,submat6);
			}
		}

//		prtmat.MatrixMult(submat1,submat4);
	}

	prteid3d.SetTransformWorld(&prtmat);

//	prteid3d.SetDrawMode(EID3D_DRAWMODE_LINE);
	if(Info.DrawMode == 0){
		if(Info.pVertex != NULL){
			if(ver_count == -1){
				ver_count = Info.VertexCount;
			}

			int a,max = ver_count,count;

			for(a = 0;a < max;a += 999){
				count = 999;
				if(a + 999 >= ver_count){
					count = max - a;
				}
				eiDDInfo.lpD3DDevice->DrawPrimitive(
					D3DPT_TRIANGLELIST,D3DFVF_VERTEX,
					&Info.pVertex[a], count,(eid3dWait ? D3DDP_WAIT : 0));

/*				for(int b = a;b < a + count;b ++){
					float div = (float)sqrt(
						Info.pVertex[b].nx * Info.pVertex[b].nx
						+ Info.pVertex[b].ny * Info.pVertex[b].ny
						+ Info.pVertex[b].nz * Info.pVertex[b].nz
					);
					if(!(0.98 <= div && div <= 1.02)){
						eiDebugWriteFile("not normalized\n");
					}
				}*/
			}

/*			eiDDInfo.lpD3DDevice->DrawPrimitive(
				D3DPT_TRIANGLELIST,D3DFVF_VERTEX,
				&Info.pVertex[0], ver_count,(eid3dWait ? D3DDP_WAIT : 0));
*/
		} else {
			eiDDInfo.lpD3DDevice->DrawPrimitive(
				D3DPT_TRIANGLELIST,D3DFVF_VERTEX,
				&Info.Vertex[0], 3,(eid3dWait ? D3DDP_WAIT : 0));
		}
	} else {
	}
}
