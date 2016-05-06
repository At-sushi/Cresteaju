//-----------------------------------------------------
//-----------------------------------------------------
//--- Direct3D


#define EID3D_DRAWMODE_FILL 0
#define EID3D_DRAWMODE_LINE 1
#define EID3D_DRAWMODE_POINT 2
#define EID3D_DRAWMODE_CULLNONE 3
#define EID3D_DRAWMODE_CULLCW 4
#define EID3D_DRAWMODE_TEXTUREDECAL 5
#define EID3D_DRAWMODE_TEXTUREMODULATE 6

#define EID3D_TEXFILTER_POINT 0
#define EID3D_TEXFILTER_LINER 1

//---構造体
typedef struct 
{
	D3DVERTEX Vertex[6];
	D3DVECTOR MoveVector,MoveVectorCount;
	FLOAT Rotate[3],RotateCount[3];
	int TexNumber;
} EI_TRIANGLE_VERTEX;


//---マテリアル
class EI_API eiD3DMaterial
{
public:
	eiD3DMaterial(void);
	~eiD3DMaterial();
	int Create(void);
	void Release(void);
	void Set(void);
	void SetTexture(eiTextureCell *lpTexture);
	void SetDeffuseColor(int red,int green,int blue,int alpha);
	void SetEmissiveColor(int red,int green,int blue,int alpha);
	void SetAmbientColor(int red,int green,int blue,int alpha);

	D3DMATERIALHANDLE GetHandle(void);

//private:
	D3DMATERIAL7 d3dMaterial;
	EIMEMORY hDumy;
};

//---ライト
class EI_API eiD3DLight
{
public:
	eiD3DLight(void);
	~eiD3DLight();
	int Create(int mode = D3DLIGHT_POINT);
	void Release(void);
	void Set(void);
	void SetColor(FLOAT red ,FLOAT green ,FLOAT blue,FLOAT alpha);
	void SetPos(FLOAT x,FLOAT y ,FLOAT z);
	void SetDirection(FLOAT x,FLOAT y,FLOAT z);
	void SetAttenuation(FLOAT at1,FLOAT at2,FLOAT at3);

//private:
	D3DLIGHT7 d3dLightStruct;
	EIMEMORY hDumy;
};

//---ビューポート
class EI_API eiD3DViewport
{
public:
	eiD3DViewport(void);
	~eiD3DViewport();

	int Create(LPD3DRECT lpRect = NULL);
	void Release(void);
	void Set(void);
	void SetRect(LPD3DRECT lpRect);
	void SetRect(int x1,int y1,int x2,int y2);
	void SetBackground(eiD3DMaterial *lpMaterial);
	void AddLight(eiD3DLight *lpLight);

	void ClearAll(LPD3DRECT lpRect = NULL);
	void ClearZBuffer(LPD3DRECT lpRect = NULL);
	void ClearBackground(LPD3DRECT lpRect = NULL);

	//---ビューポートの範囲内にあるか
	int InViewport(float x,float y);

	void GetRect(LPD3DRECT *lpRect);
	//---
	void Flip(LPD3DRECT lpRect = NULL);

	D3DVIEWPORT7 d3dViewPort;

	D3DRECT ViewRect;
	EIMEMORY hDumy;
};

//---行列
class EI_API eiD3DMatrix
{
public:
	eiD3DMatrix(void);
	~eiD3DMatrix();

	int Create(
		FLOAT m11,FLOAT m12,FLOAT m13,FLOAT m14,
		FLOAT m21,FLOAT m22,FLOAT m23,FLOAT m24,
		FLOAT m31,FLOAT m32,FLOAT m33,FLOAT m34,
		FLOAT m41,FLOAT m42,FLOAT m43,FLOAT m44);
	void Set(int m,int n,FLOAT val);
	FLOAT Get(int m,int n);
	
	void SetCalcCamera(float x,float y,float z);
	void CalcCamera(D3DVECTOR from,D3DVECTOR at,D3DVECTOR world_up,float roll);
	void CalcCamera2(D3DVECTOR vFrom,D3DVECTOR vAt, D3DVECTOR vWorldUp);
	void CalcProjectionMatrix(const float near_plane,const float far_plane,const float fov);
	void IdentityMatrix(void);
	void MatrixMult(eiD3DMatrix a,eiD3DMatrix b);
	void ZeroMatrix(void);

	void RotateX(const float rads);
	void RotateY(const float rads);
	void RotateZ(const float rads);
	
	void Move(float x,float y,float z);

	D3DMATRIX *lpd3dMatrix;
	D3DMATRIX d3dMatrix;
	EIMEMORY hd3dMatrix;
	float cx,cy,cz;
	EIMEMORY hDumy;
};

//---頂点バッファー
class EI_API eiD3DVertexBuffer
{
public:
	eiD3DVertexBuffer(void);
	~eiD3DVertexBuffer();

	int Create(int mode = 0,int VertexNumber = 1);
	int Release(void);
	void *Lock(void);
	void Unlock(void);

	void Reset(void);
	void Set(float x,float y,float z);
	void Process(eiD3DVertexBuffer *lpDestBuffer,int count = 1,int mode = 0);

	int Pointer;
	D3DVERTEXBUFFERDESC VBDesc;
	LPDIRECT3DVERTEXBUFFER7 lpD3DVertexBuffer;
	EIMEMORY hDumy;
};

//---
class EI_API eiD3D
{
public:
	eiD3D(void);
	~eiD3D();

	int InitDirect3D(void);
	int EndDirect3D(void);

	//---描画
	int Begin(int wait = 1);
	int End(int release = 1);
	int GetWait(void);
	int SetWait(int wait);
	void BeginAlphaBlend(void);
	void EndAlphaBlend(void);
	int SetDrawMode(int mode);

	//---テクスチャ
	void InitTextureState(void);
	void SetTexture(eiTextureCell *lpTexture);
	void SetTextureFilter(int mode);
	void SetTextureColorkey(int mode = 0);
	//---フォグ
	void SetFog(int mode);
	void SetFogColor(D3DCOLOR col);
	//---ライト
	void SetMaterial(eiD3DMaterial *pMaterial);
	void SetAmbientLight(D3DCOLOR col);

	//---
	void AddViewport(eiD3DViewport *lpViewport);
	void SetCurrentViewport(eiD3DViewport *lpViewport);
	void SetLight(eiD3DLight *lpLight,int index = 0);

	void SetTransform(eiD3DMatrix *lpMatrix,D3DTRANSFORMSTATETYPE mode);
	void SetTransformWorld(eiD3DMatrix *lpMatrix);
	void SetTransformView(eiD3DMatrix *lpMatrix);
	void SetTransformProjection(eiD3DMatrix *lpMatrix);

	//---Drawing
	HRESULT DrawPrimitive(D3DPRIMITIVETYPE dptPrimitiveType, 
		DWORD  dwVertexTypeDesc,LPVOID lpvVertices,                 
		DWORD  dwVertexCount, DWORD  dwFlags);

	//---現在描画中か
	int NowDrawing3D;
	int Wait;
	LPDIRECT3DDEVICE7 lpD3DDevice;
};

typedef struct 
{
	ei_s32 Weight,RotationFlag,DrawMode;
	D3DVERTEX Vertex[3];//,StartVertex[3];

	float wx,wy,wz;
	float vx,vy,vz;
	float MoveSpeed;
	float AngleX,AngleY,AngleZ;
	float RotateX,RotateY,RotateZ;
	float RSize;
	float data;

	EIMEMORY hMemory,hStartMemory;
	D3DVERTEX *pVertex,*pStartVertex;
	int VertexCount,MemorySize;
} EID3DPARTICLEINFO;


//---パーティクル管理関数
EI_API void eiD3DParticle_SetG(float g);
EI_API void eiD3DParticle_GlobalVectorXYZ(float x,float y,float z);
EI_API void eiD3DParticle_GlobalVectorAngle(float xy_angle,float xy_z_angle,float r);
EI_API void eiD3DParticle_GlobalMoveSpeed(float speed);

//---パーティクル
class EI_API eiD3DParticle
{
public:
	eiD3DParticle(void);

	void CreateTriangle(float r);
	void CreateRandomTriangle(float r,float dr,int count);
	void CreateTriangle(
		float x1,float y1,float z1,
		float x2,float y2,float z2,
		float x3,float y3,float z3);
	void CreateSphere(float r,int x_div,int y_div,float start = 0.0f,float end = 6.283184f);
	void Release(void);

	float MoveFrame(float AddWorld);
	void SetWeight(int weight);
	void SetMoveSpeed(float speed);
	void SetMoveVectorXYZ(float x,float y,float z);
	void SetMoveVectorAngle(float xy_angle,float xy_z_angle,float r);
	void SetMoveRotation(float xr,float yr);
	void SetMoveRotation(float xr,float yr,float zr);
	void SetRotationMode(int mode);

	void SetXAngle(float angle);
	void SetYAngle(float angle);
	void SetZAngle(float angle);
	void SetWorldPos(float x,float y,float z);

	void Draw(int ver_count = -1);

	eiD3DMatrix Matrix;

	EID3DPARTICLEINFO Info;
};
