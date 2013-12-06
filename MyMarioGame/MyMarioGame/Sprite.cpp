#include "Sprite.h"

MSprite::MSprite(){

}

MSprite::~MSprite(){

}


MSprite::MSprite(int totalFrame, int frameInColumn, int sourceWidth, int sourceHeight){
	this->texture = NULL;
	this->totalFrame = totalFrame;
	this->curFrame = 0;
	this->frameWidth = sourceWidth / frameInColumn;
	this->frameHeight = sourceHeight / (totalFrame / frameInColumn);
}

void MSprite::Init(LPDIRECT3DTEXTURE9 texture){
	this->texture = texture;
	this->anicurrent = 0;
	this->anidelay = 0;
	this->curFrame = 0;
	//this->Position();
}

void MSprite::Draw(LPD3DXSPRITE spriteHandler, D3DXVECTOR2 tpos){
	D3DXVECTOR3 position = D3DXVECTOR3((float)tpos.x, (float)tpos.y, 0);
	spriteHandler->Draw(texture, &rect, NULL, &position, D3DCOLOR_XRGB(255, 255, 255));
}

void MSprite::Position(){
	rect.left = (curFrame % columnFrame) * frameWidth;
	rect.top = (curFrame / columnFrame) * frameHeight;
	rect.right =  rect.left + frameWidth;
	rect.bottom = rect.top + frameHeight;
}

void MSprite::UpdateSprite(){
	this->Position();
}

void MSprite::UpdateSprite(float time, int beginFrame, int endFrame, int flag){
	if(anidelay != 0){
		if(anicurrent  > anidelay){
			//If must change frame
			if(flag == 1){
				curFrame++;
				if(curFrame >= endFrame){
					curFrame = beginFrame;
				}
			}else if(flag == -1){
				curFrame--;
				if(curFrame <= endFrame){
					curFrame = beginFrame;
				}
			}
			Position();
			anicurrent = 0;
		}else{
			//Increase counter
			anicurrent+=time;
		}
	}
}

void MSprite::SetDelayTime(int delay){
	this->anidelay = delay;
}

void MSprite::SetCurrentSprite(int current){
	this->curFrame = current;
}

float MSprite::GetFrameWidth(){
	return (float)this->frameWidth;
}

float MSprite::GetFrameHeight(){
	return (float)this->frameHeight;
}