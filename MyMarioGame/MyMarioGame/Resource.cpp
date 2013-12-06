#include "Resource.h"
MResource* MResource::resource = NULL;

MResource::MResource(){
	s_marioBig = new MSprite( 10,5, 235, 180);
	s_marioSmall = new MSprite(12 ,6, 282 , 120 );
	s_marioGun = new MSprite(10,5, 235, 180);
	s_brick = new MSprite(2,2,100,50);
	s_question = new MSprite(3,3,150,50);
	s_pipesmall = new MSprite(1,1,75,100);
	s_pipemedium = new MSprite(1,1,75,150);
	s_pipebig = new MSprite(1,1,72,198);
	s_bigtree = new MSprite(1,1,31,90);
	s_smalltree = new MSprite(1,1,27,60);
	s_grass = new MSprite(2,2,128,29);
	s_mountain = new MSprite(1,1,311,127);
	s_cloud = new MSprite(2,2,128,50);
	s_fence = new MSprite(1,1,141,32);
	s_flower = new MSprite(4,4,200,50);
	s_coin = new MSprite(7,7,315,50);
	s_house = new MSprite(1,1,297,413);
	s_mushroom = new MSprite(4,4,186,47);
	s_turtle = new MSprite(4,2,95,142);
	s_turtleshield = new MSprite(3,3,149,44);
	s_bullet = new MSprite(10,10,340,34);
	s_item = new MSprite(8,4,200,100);
	s_brickbreak = new MSprite(1,1,25,25);
}

int MResource::InitResource(LPDIRECT3DDEVICE9 _d3ddev){
	/*device = _d3ddev;
	hWnd = _hWnd;*/
	texture = new MTexture(_d3ddev);
	if(texture == NULL){
		return 0;
	}
	s_marioBig->Init(texture->GetTexture(MARIO_BIG));
	s_marioSmall->Init(texture->GetTexture(MARIO_SMALL));
	s_marioGun->Init(texture->GetTexture(MARIO_GUN));
	s_brick->Init(texture->GetTexture(BRICK));
	s_question->Init(texture->GetTexture(QUESTION));
	s_pipesmall->Init(texture->GetTexture(PIPESMALL));
	s_pipemedium->Init(texture->GetTexture(PIPEMEDIUM));
	s_pipebig->Init(texture->GetTexture(PIPEBIG));
	s_flower->Init(texture->GetTexture(FLOWER));
	s_coin->Init(texture->GetTexture(COIN));
	s_mushroom->Init(texture->GetTexture(MUSHROOM));
	s_turtle->Init(texture->GetTexture(TURTLE));
	s_turtleshield->Init(texture->GetTexture(TURTLESHIELD));
	s_bullet->Init(texture->GetTexture(BULLET));
	s_item->Init(texture->GetTexture(ITEM));
	s_brickbreak->Init(texture->GetTexture(BRICKBREAK));
	//static object
	s_bigtree->Init(texture->GetTexture(BIGTREE));
	s_smalltree->Init(texture->GetTexture(SMALLTREE));
	s_cloud->Init(texture->GetTexture(CLOUD));
	s_grass->Init(texture->GetTexture(GRASS));
	s_mountain->Init(texture->GetTexture(MOUNTAIN));
	s_fence->Init(texture->GetTexture(FENCE));
	s_house->Init(texture->GetTexture(HOUSE));

	//Done
	return 1;
}

MSprite* MResource::GetResource(ResourceID id){
	switch (id)
	{
	case MARIO_BIG_ID:
		{
			return new MSprite(*s_marioBig);
			break;
		}
	case MARIO_SMALL_ID:
		{
			return new MSprite(*s_marioSmall);
			break;
		}
	case MARIO_GUN_ID:
		{
			return new MSprite(*s_marioGun);
			break;
		}
	case BRICK_ID:
		{
			return new MSprite(*s_brick);
			break;
		}
	case QUESTION_ID:
		{
			return new MSprite(*s_question);
			break;
		}
	case PIPESMALL_ID:
		{
			return new MSprite(*s_pipesmall);
			break;
		}
	case PIPEMEDIUM_ID:
		{
			return new MSprite(*s_pipemedium);
			break;
		}
	case PIPEBIG_ID:
		{
			return new MSprite(*s_pipebig);
			break;
		}
		//static
	case BIGTREE_ID:
		{
			return new MSprite(*s_bigtree);
			break;
		}
	case SMALLTREE_ID:
		{
			return new MSprite(*s_smalltree);
			break;
		}
	case CLOUD_ID:
		{
			return new MSprite(*s_cloud);
			break;
		}
	case MOUNTAIN_ID:
		{
			return new MSprite(*s_mountain);
			break;
		}
	case GRASS_ID:
		{
			return new MSprite(*s_grass);
			break;
		}
	case FENCE_ID:
		{
			return new MSprite(*s_fence);
			break;
		}
	case FLOWER_ID:
		{
			return new MSprite(*s_flower);
			break;
		}
	case COIN_ID:
		{
			return new MSprite(*s_coin);
			break;
		}
	case HOUSE_ID:
		{
			return new MSprite(*s_house);
			break;
		}
	case MUSHROOM_ID:
		{
			return new MSprite(*s_mushroom);
			break;
		}
	case TURTLE_ID:
		{
			return new MSprite(*s_turtle);
			break;
		}
	case TURTLE_SHIELD_ID:
		{
			return new MSprite(*s_turtleshield);
			break;
		}
	case BULLET_ID:
		{
			return new MSprite(*s_bullet);
			break;
		}
	case ITEM_ID:
		{
			return new MSprite(*s_item);
			break;
		}
	case BRICKBREAK_ID:
		{
			return new MSprite(*s_brickbreak);
			break;
		}

	default:
		{
			return NULL;
			break;
		}
	}
}

MResource* MResource::GetInstance(){
	if(resource == NULL){
		resource = new MResource();
	}
	return resource;
}

MResource::~MResource(){

}