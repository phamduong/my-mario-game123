#include "Texture.h"
MTexture::MTexture(){}
MTexture::MTexture(LPDIRECT3DDEVICE9 d3ddev){
	this->d3ddev = d3ddev;
}

LPDIRECT3DTEXTURE9 MTexture::GetTexture(string filename){
	//Standard windows return value
	HRESULT result;
	
	//Get info from bitmap file
	result = D3DXGetImageInfoFromFile(filename.c_str(), &this->imageInfo);
	if(FAILED(result)){
		MessageBox(NULL, "Error when initialize texture", "Error", MB_OK);
		//exit(0);
		return NULL;
	}
	
	//Create texture by loading bitmap file
	result = D3DXCreateTextureFromFileEx(
		d3ddev,
		filename.c_str(),
		this->imageInfo.Width,
		this->imageInfo.Height,
		1,
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		 D3DCOLOR_XRGB(250,100,100),
		&this->imageInfo,
		NULL,
		&this->texture);
	
	//Make sure that the bitmap texture is loaded correctly
	if(result != D3D_OK){
		return NULL;
	}
	
	return texture;
}

D3DXIMAGE_INFO MTexture::GetImageInfo(){
	return this->imageInfo;
}