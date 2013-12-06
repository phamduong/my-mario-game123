#include "GameObject.h"

GameOject::GameOject(){
	this->position = D3DXVECTOR2(0, 0);
	Init();
}

GameOject::GameOject(D3DXVECTOR2 pos){
	this->position = pos;
	Init();
}

void GameOject::Init(){
	this->isAlive = true;
	this->showTime = 0;
	this->showOrNot = true;
	this->velocity = D3DXVECTOR2(0, 0);
	this->accel = D3DXVECTOR2(0, 0);
}

void GameOject::SetBound(){
	bound.left = (long)this->position.x;
	bound.top = (long)this->position.y;
	bound.right = (long)(bound.left + sprite->GetFrameWidth());
	bound.bottom = (long)(bound.top + sprite->GetFrameHeight());
}

void GameOject::UpdatePosition(MInput* input, float time){
	//this->velocity = this->accel * time;
	this->position += this->velocity * time;
//	SetBound();
}

void GameOject::UpdateAnimation(MInput* input, float time){
	
}

void GameOject::Update(MInput* input, float time, MCamera* camera){
	UpdatePosition(input, time);
	//sprite->UpdateSprite();
}



void  GameOject::Draw(LPD3DXSPRITE spriteHandler, MCamera* camera){
	D3DXMATRIX matScale;
	D3DXMatrixIdentity(&matScale);
	D3DXMatrixTransformation2D(
		&matScale, 
		&D3DXVECTOR2(position.x + (sprite->GetFrameWidth() / 2), position.y + (sprite->GetFrameHeight()/2)),
		0.0f,
		&D3DXVECTOR2(1.f, -1.f),
		NULL,
		0.0f,
		NULL);
	D3DXMatrixMultiply(&matScale, &matScale, &camera->GetViewPort());
	spriteHandler->SetTransform(&matScale);
	sprite->Draw(spriteHandler, position);
}

GameOject::~GameOject(){

}