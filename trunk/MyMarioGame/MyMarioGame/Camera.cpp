#include "Camera.h"

MCamera::MCamera(){
	pos = D3DXVECTOR2(0, 800);
}

void MCamera::Update(MInput* input, D3DXVECTOR2 _pos){
	pos.x = (float)_pos.x - 400;
	if(pos.x < 0){
		pos.x = 0;
	}

	if(pos.x > 3200){
		pos.x = 3200;
	}
}

D3DXMATRIX MCamera::GetViewPort(){
	D3DXMatrixIdentity(&viewport);
	/*D3DXMatrixAffineTransformation(
	&viewport, 1, 
	&D3DXVECTOR3(0,0,0), 
	&D3DXQUATERNION(0, 0, 0, 0),
	&D3DXVECTOR3((float)pos.x, (float)pos.y, 0));*/
	viewport._22 = -1;
	viewport._41 = -pos.x;
	viewport._42 = pos.y;
	return viewport;
}

MCamera::~MCamera(){

}