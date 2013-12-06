#ifndef _MARIO_H_
#define _MARIO_H_
#include "GameObject.h"
#include "Sprite.h"
#include "DxInput.h"
#include "Camera.h"
#include "Resource.h"

#define TIMEANIMATION 1.6f
#define VELONORMAL 40.0f
#define GROUND_Y 50

enum MarioAction
{
	m_action_normal,
	m_action_jump,
	m_action_run,
	m_action_down
};

enum MarioStatus
{
	m_status_small,
	m_status_big,
	m_status_gun
};

class Mario : public GameOject
{
private:
	MSprite *mSpriteSmall;
	MSprite *mSpriteBig;
	MSprite *mSpriteGun;
	
	int direction;						//Mario's direction
	MarioAction action;					//Current action
	MarioStatus startStatus;			//Start status
	MarioStatus curStatus;				//Current status
public:
	Mario();
	~Mario();

	void Init();
	//void UpdatePosition(MInput*, float);
	void UpdateAnimation(MInput*, float);
	void Update(MInput*, float, MCamera*);
	void Draw(LPD3DXSPRITE, MCamera*);
};

#endif