#ifndef _GAME_H_
#define _GAME_H_

#include "DxGraphics.h"
#include "DxInput.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Timer.h"
#include "Camera.h"
#include "Mario.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 640
#define FULLSCREEN 0

class MarioGame
{
private:
	MGraphics *dxgraphic;
	MInput *dxinput;
	MTimer *timer;
	MCamera *camera;

	Mario *mario;

public:
	LPD3DXSPRITE spriteHandler;
	int GameInit(HWND);
	int GameRun(HWND, MSG);
	void GameEnd();
	void UpdateWorld(float);
	void DrawWorld();
	MarioGame();
	~MarioGame();
};

#endif