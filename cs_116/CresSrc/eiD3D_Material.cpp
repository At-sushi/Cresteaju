#define EI_COLOR_VALUEMAX 255

eiD3DMaterial::eiD3DMaterial(void)
{
	eimemset(&d3dMaterial, 0,sizeof(d3dMaterial)); 
//	d3dMaterial.dwSize = sizeof(d3dMaterial); 

	d3dMaterial.dcvDiffuse.r  = D3DVAL(1.0);
	d3dMaterial.dcvDiffuse.g  = D3DVAL(1.0); 
	d3dMaterial.dcvDiffuse.b  = D3DVAL(1.0);
	d3dMaterial.dcvDiffuse.a  = D3DVAL(1.0);

	d3dMaterial.dcvAmbient.r  = D3DVAL(1.0); 
	d3dMaterial.dcvAmbient.g  = D3DVAL(1.0); 
	d3dMaterial.dcvAmbient.b  = D3DVAL(1.0); 
	d3dMaterial.dcvAmbient.a  = D3DVAL(1.0);

	d3dMaterial.dcvSpecular.r = D3DVAL(1.0); 
	d3dMaterial.dcvSpecular.g = D3DVAL(1.0); 
	d3dMaterial.dcvSpecular.b = D3DVAL(1.0); 
	d3dMaterial.dcvSpecular.a = D3DVAL(1.0);

	d3dMaterial.dcvEmissive.r = D3DVAL(0.0);
	d3dMaterial.dcvEmissive.g = D3DVAL(0.0);
	d3dMaterial.dcvEmissive.b = D3DVAL(0.0);
	d3dMaterial.dcvEmissive.a = D3DVAL(0.0);

	d3dMaterial.dvPower       = D3DVAL(20.0); 
}

eiD3DMaterial::~eiD3DMaterial()
{
}

int eiD3DMaterial::Create(void)
{
	Set();
	return 1;
}

void eiD3DMaterial::Release(void)
{
}

//---表面色
void eiD3DMaterial::SetEmissiveColor(int red,int green,int blue,int alpha)
{
	d3dMaterial.dcvEmissive.r  = (FLOAT)red / (FLOAT)EI_COLOR_VALUEMAX;
	d3dMaterial.dcvEmissive.g  = (FLOAT)green / (FLOAT)EI_COLOR_VALUEMAX; 
	d3dMaterial.dcvEmissive.b  = (FLOAT)blue / (FLOAT)EI_COLOR_VALUEMAX;
	d3dMaterial.dcvEmissive.a  = (FLOAT)alpha / (FLOAT)EI_COLOR_VALUEMAX;
}

//---表面色
void eiD3DMaterial::SetDeffuseColor(int red,int green,int blue,int alpha)
{
	d3dMaterial.dcvDiffuse.r  = (FLOAT)red / (FLOAT)EI_COLOR_VALUEMAX;
	d3dMaterial.dcvDiffuse.g  = (FLOAT)green / (FLOAT)EI_COLOR_VALUEMAX; 
	d3dMaterial.dcvDiffuse.b  = (FLOAT)blue / (FLOAT)EI_COLOR_VALUEMAX;
	d3dMaterial.dcvDiffuse.a  = (FLOAT)alpha / (FLOAT)EI_COLOR_VALUEMAX;
}

//---表面色
void eiD3DMaterial::SetAmbientColor(int red,int green,int blue,int alpha)
{
	d3dMaterial.dcvAmbient.r  = (FLOAT)red / (FLOAT)EI_COLOR_VALUEMAX;
	d3dMaterial.dcvAmbient.g  = (FLOAT)green / (FLOAT)EI_COLOR_VALUEMAX; 
	d3dMaterial.dcvAmbient.b  = (FLOAT)blue / (FLOAT)EI_COLOR_VALUEMAX;
	d3dMaterial.dcvAmbient.a  = (FLOAT)alpha / (FLOAT)EI_COLOR_VALUEMAX;
}

//---テクスチャをセット
void eiD3DMaterial::SetTexture(eiTextureCell *lpTexture)
{
}

void eiD3DMaterial::Set(void)
{
	HRESULT ddrval;

	ddrval = eiDDInfo.lpD3DDevice->SetMaterial(&d3dMaterial);
	if(ddrval != D3D_OK){
		eiDebugWriteFile("(eiD3DMaterial) Set fail\n");
	}
}

D3DMATERIALHANDLE eiD3DMaterial::GetHandle(void)
{
	D3DMATERIALHANDLE hmat = 0;

	return hmat;
}
