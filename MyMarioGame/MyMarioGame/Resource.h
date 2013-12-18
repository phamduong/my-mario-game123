#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include "Texture.h"
#include "Sprite.h"

#define MARIO_BIG L"Resources/Images/big_player.png"
#define MARIO_SMALL L"Resources//Images//small_player.png"
#define MARIO_GUN L"Resources//Images//gunny_player.png"
#define BRICK L"Resources//Images//brick.png"
#define QUESTION L"Resources//Images//questions.png"
#define PIPEMEDIUM L"Resources//Images//medium_pipe.png"
#define PIPESMALL L"Resources//Images//small_pipe.png"
#define PIPEBIG L"Resources//Images//big_pipe.png"
#define BIGTREE L"Resources//Images//big_tree.png"
#define SMALLTREE L"Resources//Images//small_tree.png"
#define CLOUD L"Resources//Images//cloud.png"
#define GRASS L"Resources//Images//grass.png"
#define MOUNTAIN L"Resources//Images//moutain.png"
#define FENCE L"Resources//Images//fence.png"
#define FLOWER L"Resources//Images//flowers.png"
#define COIN L"Resources//Images//coin.png"
#define MUSHROOM L"Resources//Images//mushroom.png"
#define TURTLE L"Resources//Images//turtle.png"
#define TURTLESHIELD L"Resources//Images//turtle_shield.png"
#define ITEM L"Resources//Images//items.png"
#define BRICKBREAK L"Resources//Images//break_brick.png"
#define HOUSE L"Resources//Images//cattle.png"
#define BULLET L"Resources//Images//bullets.png"

enum ResourceID{
	MARIO_SMALL_ID,
	MARIO_BIG_ID,
	MARIO_GUN_ID,
	BRICK_ID,
	QUESTION_ID,
	PIPEMEDIUM_ID,
	PIPESMALL_ID,
	PIPEBIG_ID,
	BIGTREE_ID,
	SMALLTREE_ID,
	CLOUD_ID,
	MOUNTAIN_ID,
	GRASS_ID,
	FENCE_ID,
	FLOWER_ID,
	COIN_ID,
	HOUSE_ID,
	MUSHROOM_ID,
	TURTLE_ID,
	TURTLE_SHIELD_ID,
	BULLET_ID,
	ITEM_ID,
	BRICKBREAK_ID
};

class  MResource
{
private:
	MSprite *s_marioBig;
	MSprite *s_marioSmall;
	MSprite *s_marioGun;
	MSprite *s_brick;
	MSprite *s_question;
	MSprite *s_pipemedium;
	MSprite *s_pipesmall;
	MSprite *s_pipebig;
	MSprite *s_bigtree;
	MSprite *s_smalltree;
	MSprite *s_cloud;
	MSprite *s_mountain;
	MSprite *s_grass;
	MSprite *s_fence;
	MSprite *s_flower;
	MSprite *s_coin;
	MSprite *s_mushroom;
	MSprite *s_turtle;
	MSprite *s_turtleshield;
	MSprite *s_item;
	MSprite *s_brickbreak;
	MSprite *s_house;
	MSprite *s_bullet;

	MTexture *texture;

	static MResource *resource;
	/*static LPDIRECT3DDEVICE9 device;
	static HWND hWnd;*/
	//Singleton pattern so this can create only string object of this class
	 MResource();
public:
	~MResource();
	int InitResource(LPDIRECT3DDEVICE9);
	MSprite* GetResource(ResourceID);
	static MResource* GetInstance();
};


#endif