#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <d3d9.h>
#include <d3dx9.h>

class MSprite
{
private:

protected:
	LPDIRECT3DTEXTURE9 texture;		//Texture for the sprite
	RECT rect;
	int curFrame;					//Current frame
	int totalFrame;					//Total frame
	int columnFrame;				//Number of columns
	int frameWidth;					//Sprite width
	int frameHeight;				//Sprite height
	int anidelay;					//Time delay before animation
	float anicurrent;					//Counter
public:
	MSprite();
	MSprite(int totalFrame, int columnFrame, int sourceWidth, int sourceHeight);
	~MSprite();

	void Init(LPDIRECT3DTEXTURE9 texture);
	void Draw(LPD3DXSPRITE, D3DXVECTOR2);
	void Position();
	void UpdateSprite();
	void UpdateSprite(float, int, int, int);
	void SetDelayTime(int);
	void SetCurrentSprite(int);
	float GetFrameWidth();
	float GetFrameHeight();
	LPDIRECT3DTEXTURE9 getTexture();
};

#endif