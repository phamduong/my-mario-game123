#ifndef _DXGRAPHICS_H_
#define _DXGRAPHICS_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>

class MGraphics{
private: 
	LPDIRECT3D9 d3d;
	LPDIRECT3DSURFACE9 backbuffer;
	
public:	
	LPDIRECT3DDEVICE9 d3ddev;
	MGraphics();
	~MGraphics();
	int InitDirect3D(HWND, int, int, int);
	LPDIRECT3DDEVICE9 GetD3DDevice();
	LPDIRECT3DSURFACE9 LoadSurface(LPCWSTR, D3DCOLOR);
	void BeginRender();
	void EndRender();
	void RealeaseDevice();
};

#endif