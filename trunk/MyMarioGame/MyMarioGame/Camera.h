#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "DxInput.h"
#include <windows.h>

class MCamera{
private:
	D3DXMATRIX viewport;
	D3DXVECTOR2 pos;
public:
	MCamera();
	~MCamera();
	void Update(MInput*, D3DXVECTOR2);
	D3DXMATRIX GetViewPort();
};

#endif