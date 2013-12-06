#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
using namespace std;
class MTexture{
private:
	D3DXIMAGE_INFO imageInfo;
	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DDEVICE9 d3ddev;
public:
	MTexture();
	MTexture(LPDIRECT3DDEVICE9);
	~MTexture();
	LPDIRECT3DTEXTURE9 GetTexture(string);
	D3DXIMAGE_INFO GetImageInfo();
};

#endif