#include "Mario.h"

Mario::Mario()
{
	Init();
}

Mario::~Mario()
{
}

void Mario::Init(){
	GameOject::Init();
	this->position = D3DXVECTOR2(50, 300);
	this->maxAccel = D3DXVECTOR2(15.0f,240.0f);
	this->maxVelocity = D3DXVECTOR2(100.0f,50.0f);
	this->action = m_action_normal;
	this->startStatus = m_status_big;
	this->direction = 1;
	this->mSpriteSmall = MResource::GetInstance()->GetResource(MARIO_SMALL_ID);
	this->mSpriteBig = MResource::GetInstance()->GetResource(MARIO_BIG_ID);
	this->mSpriteGun = MResource::GetInstance()->GetResource(MARIO_GUN_ID);
	switch (startStatus)
	{
	case m_status_small:
		sprite = mSpriteSmall;
		this->curStatus = m_status_small;
		break;
	case m_status_big:
		sprite = mSpriteBig;
		this->curStatus = m_status_big;
		break;
	case m_status_gun:
		sprite = mSpriteGun;
		this->curStatus = m_status_gun;
		break;
	default:
		break;
	}
	GameOject::SetBound();
}

void Mario::UpdateAnimation(MInput* input, float time){
	if (velocity.x == 0 && velocity.y == 0){
		//If in normal state
		if(direction == 1){
			//If go forward
			sprite->SetCurrentSprite(0);
			sprite->UpdateSprite(time, 1, 3, 1);
		}else if(direction == -1){
			//If go back
			sprite->SetCurrentSprite(9);
			sprite->UpdateSprite(time, 8, 6, -1);
		}
	} 
	else if (velocity.x != 0 && velocity.y == 0 && action != m_action_down)
	{
		//If run
		if(direction == 1){
			sprite->UpdateSprite(time, 1, 2, 1);
		}else if(direction == -1){
			sprite->UpdateSprite(time, 8, 6, -1);
		}
	}else if(velocity.y != 0){
		//If jump
		if(direction == 1){
			sprite->SetCurrentSprite(1);
			sprite->UpdateSprite();
		}else if(direction == -1){
			sprite->SetCurrentSprite(8);
			sprite->UpdateSprite();
		}
	}else if(action == m_action_down){
		//If sit down
		if(direction == 1){
			sprite->SetCurrentSprite(4);
			sprite->UpdateSprite();
		}else if(direction == -1){
			sprite->SetCurrentSprite(5);
			sprite->UpdateSprite();
		}
	}
}

void Mario::Update(MInput* input, float time, MCamera* camera){
	UpdateAnimation(input, time);

	if(input->KeyDown(DIK_RIGHT)){
		//MessageBox(NULL, "asd", "Error", MB_OK);
		direction = 1;
		velocity.x = VELONORMAL;
		action = m_action_run;
	}
	if(input->KeyDown(DIK_LEFT)){
		direction = -1;
		velocity.x = VELONORMAL;
		action = m_action_run;
	}
	if(input->KeyDown(DIK_SPACE)){
//		velocity.y =
	}
	GameOject::Update(input, time, camera);
	camera->Update(input, position);
}

void Mario::Draw(LPD3DXSPRITE spriteHandler, MCamera* camera){
	GameOject::Draw(spriteHandler, camera);
}