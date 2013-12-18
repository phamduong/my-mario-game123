#include "DxGraphics.h"

//Initialize graphic ojbects
MGraphics::MGraphics(){
	d3d = NULL;
	d3ddev = NULL;
	backbuffer = NULL;
}

//Deconstructor
MGraphics::~MGraphics(){
	
}

void MGraphics::RealeaseDevice(){
	if(d3d != NULL){
		d3d->Release();
		d3d = NULL;
	}
	if(d3ddev != NULL){
		d3ddev->Release();
		d3ddev = NULL;
	}
	if(backbuffer != NULL){
		backbuffer->Release();
		backbuffer = NULL;
	}
}

int MGraphics::InitDirect3D(HWND hWnd, int width, int height, int fullscreen){
	//Initialize Direct3D
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if(d3d == NULL){ 
		return 0;
	}

	//Set Direct3d presentation parameters
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = (!fullscreen);
	d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat =  D3DFMT_D16;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//Create Direct3DDevice
	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	if(d3ddev == NULL){
		//MessageBox(hWnd, "Error creating Direct3dDevice", "Error", MB_OK);
		return 0;
	}

	//Clear backbuffer to black
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0 , 0, 0), 1.0f, 0);

	//Create pointer to backbuffer
	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);

	return 1;
}


LPDIRECT3DSURFACE9 MGraphics::LoadSurface(LPCWSTR filename, D3DCOLOR transcolor){
	LPDIRECT3DSURFACE9 image = NULL;
	D3DXIMAGE_INFO info;
	HRESULT result;

	//Get width and height from bitmap file
	result = D3DXGetImageInfoFromFile(filename, &info);
	if(result != D3D_OK){
		return NULL;
	}

	//create surface
	result = d3ddev->CreateOffscreenPlainSurface(
		info.Width,
		info.Height,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&image,
		NULL);
	if(result != D3D_OK){
		return NULL;
	}

	//Load surface from file into new created surface
	result = D3DXLoadSurfaceFromFile(
		image,
		NULL,
		NULL,
		filename,
		NULL,
		D3DX_DEFAULT,
		transcolor,
		NULL);
	if (result != D3D_OK){
		return NULL;
	}

	return image;
}


LPDIRECT3DDEVICE9 MGraphics::GetD3DDevice(){
	return this->d3ddev;
}

void MGraphics::BeginRender(){
	if(d3ddev != NULL){
		d3ddev->BeginScene();
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(67,188,236), 1.0f, 0);
	}
}

void MGraphics::EndRender(){
	d3ddev->EndScene();
	d3ddev->Present(NULL, NULL, NULL, NULL);
}

