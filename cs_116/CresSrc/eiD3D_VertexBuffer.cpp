//---頂点バッファー

eiD3DVertexBuffer::eiD3DVertexBuffer(void)
{
	lpD3DVertexBuffer = NULL;

	eimemset(&VBDesc,0,sizeof(VBDesc));	
	//---構造体初期化
	VBDesc.dwSize = sizeof(VBDesc);
	VBDesc.dwCaps |= D3DVBCAPS_SYSTEMMEMORY;
	VBDesc.dwFVF = D3DFVF_VERTEX;
	VBDesc.dwNumVertices = 1;

	Reset();
}

eiD3DVertexBuffer::~eiD3DVertexBuffer()
{
}

int eiD3DVertexBuffer::Create(int mode /*= 0*/,int VertexNumber /* = 1*/)
{
	VBDesc.dwNumVertices = VertexNumber;

	if(mode == 0){
		//---Src
	} else {
		//---Dst
		VBDesc.dwFVF = D3DFVF_TLVERTEX;
	}
	
	if(eiDDInfo.lpD3D->CreateVertexBuffer(&VBDesc,&lpD3DVertexBuffer,0) != D3D_OK){
		eiDebugWriteFile("(eiD3DVertexBuffer) Create failed\n");
		return 0;
	}
	eiDebugWriteFile("(eiD3DVertexBuffer) Create succes\n");

	return 1;
}

int eiD3DVertexBuffer::Release(void)
{
	int r;
	if(lpD3DVertexBuffer != NULL){
		if((r = lpD3DVertexBuffer->Release()) > 0){
			char s[80];
			eiDebugWriteFile("(eiD3DVertexBuffer) lpD3DVertexBuffer->Release() fail.\n");
			sprintf(s,"%d",r);
			eiDebugWriteFile(s);
		}
		lpD3DVertexBuffer = NULL;
		eiDebugWriteFile("(eiD3DVertexBuffer) lpD3DVertexBuffer->Release()\n");
	}

	return 1;
}

void *eiD3DVertexBuffer::Lock(void)
{
	D3DVERTEX *lpData = NULL;
	DWORD size = 0;

	if(lpD3DVertexBuffer != NULL){
		lpD3DVertexBuffer->Lock(DDLOCK_WAIT ,(void **)&lpData,&size);
	}

	return lpData;
}

void eiD3DVertexBuffer::Unlock(void)
{
	if(lpD3DVertexBuffer != NULL){
		lpD3DVertexBuffer->Unlock();
	}
}

//----------
void eiD3DVertexBuffer::Reset(void)
{
	Pointer = 0;
}

void eiD3DVertexBuffer::Set(float x,float y,float z)
{
	D3DVERTEX *lpData;

	lpData = (D3DVERTEX *)Lock();
	if(lpData != NULL){
		*(lpData + Pointer) = D3DVERTEX(
			D3DVECTOR(x,y,z),
			D3DVECTOR(0.0f,0.0f,0.0f),D3DVAL(0.0f),D3DVAL(0.0f));
		Unlock();

		Pointer ++;
	}
}

//---頂点計算
void eiD3DVertexBuffer::Process(eiD3DVertexBuffer *lpDestBuffer,int count /*= 1*/,int mode /*= 0*/)
{
	if(lpD3DVertexBuffer != NULL){
		lpDestBuffer->lpD3DVertexBuffer->ProcessVertices(
			D3DVOP_TRANSFORM,0,count,
			lpD3DVertexBuffer,0,eiDDInfo.lpD3DDevice,0);
	}
}
