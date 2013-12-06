#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_
#include "Sprite.h"
#include "DxInput.h"
#include "Texture.h"
#include "DxGraphics.h"
#include "Camera.h"
#include "Resource.h"

#define TIMEDELAY 2f

class GameOject{
protected:
	D3DXVECTOR2 position;		//Object's position
	D3DXVECTOR2 velocity;		//Speed
	D3DXVECTOR2 accel;			//Acceleration

	//max
	D3DXVECTOR2 maxVelocity;
	D3DXVECTOR2 maxAccel;

	MSprite* sprite;			//Sprite
	RECT bound;					//Bound - maybe use for collision check
	bool isAlive;				//Dead or alive
	float showTime;				//Time it shows on screen
	bool showOrNot;				//Show or Not

public:
	GameOject();
	GameOject(D3DXVECTOR2);
	~GameOject();
	virtual void Init();
	virtual void UpdatePosition(MInput*, float);
	virtual void UpdateAnimation(MInput*, float);
	virtual void Update(MInput*, float, MCamera*); //Call 2 methods above
	virtual void Draw(LPD3DXSPRITE, MCamera*);

	//Getter
	D3DXVECTOR2 GetPosition() { return this->position;}
	D3DXVECTOR2 GetVelocity() { return this->velocity;}
	D3DXVECTOR2 GetAccelebration() { return this->accel;}
	RECT GetBound() {return this->bound;}

	//Setter
	void SetBound();
	void SetPosition(D3DXVECTOR2 pos) { this->position = pos;}
	void SetVelocity(D3DXVECTOR2 vel) { this->velocity = vel;}
	void SetAccel(D3DXVECTOR2 accel) {this->accel = accel;}
	void SetShow(bool show){this->showOrNot = show;}
	void SetMaxVelocity(D3DXVECTOR2 maxVelo){this->maxVelocity = maxVelo;}
	void SetMaxAccel(D3DXVECTOR2 maxAccel){this->maxAccel = maxAccel;}
};
#endif
