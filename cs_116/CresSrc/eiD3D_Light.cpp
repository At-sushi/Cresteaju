
eiD3DLight::eiD3DLight(void)
{

	eimemset(&d3dLightStruct, 0,sizeof(d3dLightStruct)); 

    d3dLightStruct.dltType = D3DLIGHT_PARALLELPOINT;//D3DLIGHT_POINT; 
    d3dLightStruct.dvPosition.dvX  = D3DVAL( 1.0);
    d3dLightStruct.dvPosition.dvY  = D3DVAL(-1.0); 
    d3dLightStruct.dvPosition.dvZ  = D3DVAL(-1.0); 
    d3dLightStruct.dvDirection.dvX  = D3DVAL( 0.0);
    d3dLightStruct.dvDirection.dvY  = D3DVAL( 0.0); 
    d3dLightStruct.dvDirection.dvZ  = D3DVAL( 1.0); 
    d3dLightStruct.dvAttenuation0  = D3DVAL( 1.0); 
    d3dLightStruct.dvAttenuation1  = D3DVAL( 0.0); 
    d3dLightStruct.dvAttenuation2  = D3DVAL( 0.0);

	d3dLightStruct.dvRange = D3DLIGHT_RANGE_MAX;

	d3dLightStruct.dcvDiffuse.dvR = 255;
	d3dLightStruct.dcvDiffuse.dvG = 255;
	d3dLightStruct.dcvDiffuse.dvB = 255;
	d3dLightStruct.dcvDiffuse.dvA = 255;
}

eiD3DLight::~eiD3DLight()
{
}

//---ƒ‰ƒCƒg‚ðì‚é
int eiD3DLight::Create(int mode /* = D3DLIGHT_POINT*/)
{
	d3dLightStruct.dltType = (enum _D3DLIGHTTYPE)mode; 
	SetColor(D3DVAL( 1.0),D3DVAL( 1.0),D3DVAL( 1.0),D3DVAL( 1.0));

	return 1;
}

void eiD3DLight::Release(void)
{
}

void eiD3DLight::Set(void)
{
	eiDDInfo.lpD3DDevice->SetLight(0,&d3dLightStruct);
}

void eiD3DLight::SetColor(FLOAT red ,FLOAT green ,FLOAT blue,FLOAT alpha)
{
	d3dLightStruct.dcvDiffuse.dvR = red;
	d3dLightStruct.dcvDiffuse.dvG = green;
	d3dLightStruct.dcvDiffuse.dvB = blue;
	d3dLightStruct.dcvDiffuse.dvA = alpha;

	Set();
}

void eiD3DLight::SetPos(FLOAT x,FLOAT y ,FLOAT z)
{
	d3dLightStruct.dvPosition.dvX = x; 
	d3dLightStruct.dvPosition.dvY = y; 
	d3dLightStruct.dvPosition.dvZ = z; 

	Set();
}

void eiD3DLight::SetDirection(FLOAT x,FLOAT y,FLOAT z)
{
	d3dLightStruct.dvDirection.dvX = x;
	d3dLightStruct.dvDirection.dvY = y; 
	d3dLightStruct.dvDirection.dvZ = z; 

	Set();
}

void eiD3DLight::SetAttenuation(FLOAT at1,FLOAT at2,FLOAT at3)
{
	d3dLightStruct.dvAttenuation0 = at1; 
	d3dLightStruct.dvAttenuation1 = at2;
	d3dLightStruct.dvAttenuation2 = at3; 

	Set();
}
