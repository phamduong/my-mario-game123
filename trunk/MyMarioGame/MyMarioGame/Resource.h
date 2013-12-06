#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include "Texture.h"
#include "Sprite.h"

#define MARIO_BIG "Resources/Images/big_player.png"
#define MARIO_SMALL "Resources//Images//small_player.png"
#define MARIO_GUN "Resources//Images//gunny_player.png"
#define BRICK "Resources//Images//brick.png"
#define QUESTION "Resources//Images//questions.png"
#define PIPEMEDIUM "Resources//Images//medium_pipe.png"
#define PIPESMALL "Resources//Images//small_pipe.png"
#define PIPEBIG "Resources//Images//big_pipe.png"
#define BIGTREE "Resources//Images//big_tree.png"
#define SMALLTREE "Resources//Images//small_tree.png"
#define CLOUD "Resources//Images//cloud.png"
#define GRASS "Resources//Images//grass.png"
#define MOUNTAIN "Resources//Images//moutain.png"
#define FENCE "Resources//Images//fence.png"
#define FLOWER "Resources//Images//flowers.png"
#define COIN "Resources//Images//coin.png"
#define MUSHROOM "Resources//Images//mushroom.png"
#define TURTLE "Resources//Images//turtle.png"
#define TURTLESHIELD "Resources//Images//turtle_shield.png"
#define ITEM "Resources//Images//items.png"
#define BRICKBREAK "Resources//Images//break_brick.png"
#define HOUSE "Resources//Images//cattle.png"
#define BULLET "Resources//Images//bullets.png"

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