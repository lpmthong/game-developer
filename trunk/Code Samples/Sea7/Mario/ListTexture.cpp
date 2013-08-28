#include "ListTexture.h"

//LPDIRECT3DTEXTURE9	ListTexture::TT_MARIO_KID = NULL;

LPDIRECT3DTEXTURE9	ListTexture::TT_BRICK = NULL;
int					ListTexture::TT_BRICK_WIDTH;
int					ListTexture::TT_BRICK_HEIGHT;
int					ListTexture::TT_BRICK_COUNT;
int					ListTexture::TT_BRICK_SPRITEPERROW;

LPDIRECT3DTEXTURE9	ListTexture::TT_CLOUD = NULL;
int					ListTexture::TT_CLOUD_WIDTH;
int					ListTexture::TT_CLOUD_HEIGHT;
int					ListTexture::TT_CLOUD_COUNT;
int					ListTexture::TT_CLOUD_SPRITEPERROW;
int					ListTexture::TT_CLOUD_ANIMATED_RATE;


LPDIRECT3DTEXTURE9	ListTexture::TT_GRASS = NULL;
int					ListTexture::TT_GRASS_WIDTH;
int					ListTexture::TT_GRASS_HEIGHT;
int					ListTexture::TT_GRASS_COUNT;
int					ListTexture::TT_GRASS_SPRITEPERROW;
int					ListTexture::TT_GRASS_ANIMATED_RATE;


LPDIRECT3DTEXTURE9	ListTexture::TT_FENCE = NULL;
int					ListTexture::TT_FENCE_WIDTH;
int					ListTexture::TT_FENCE_HEIGHT;
int					ListTexture::TT_FENCE_COUNT;
int					ListTexture::TT_FENCE_SPRITEPERROW;

LPDIRECT3DTEXTURE9	ListTexture::TT_MUSHROOM_ENEMY = NULL;
int					ListTexture::TT_MUSHROOM_ENEMY_WIDTH;
int					ListTexture::TT_MUSHROOM_ENEMY_HEIGHT;
int					ListTexture::TT_MUSHROOM_ENEMY_COUNT;
int					ListTexture::TT_MUSHROOM_ENEMY_SPRITEPERROW;
int					ListTexture::TT_MUSHROOM_ENEMY_ANIMATED_RATE;

LPDIRECT3DTEXTURE9	ListTexture::TT_GROUND;
int					ListTexture::TT_GROUND_WIDTH;
int					ListTexture::TT_GROUND_HEIGHT;
int					ListTexture::TT_GROUND_COUNT;
int					ListTexture::TT_GROUND_SPRITEPERROW;

LPDIRECT3DTEXTURE9	ListTexture::TT_MARIO_KID;
int					ListTexture::TT_MARIO_KID_WIDTH;
int					ListTexture::TT_MARIO_KID_HEIGHT;
int					ListTexture::TT_MARIO_KID_COUNT;
int					ListTexture::TT_MARIO_KID_SPRITEPERROW;
int					ListTexture::TT_MARIO_KID_ANIMATED_RATE;
int					ListTexture::TT_MARIO_KID_MOVING_LEFT_START;
int					ListTexture::TT_MARIO_KID_MOVING_LEFT_END;
int					ListTexture::TT_MARIO_KID_MOVING_RIGHT_START;
int					ListTexture::TT_MARIO_KID_MOVING_RIGHT_END;
int					ListTexture::TT_MARIO_KID_JUMPING_LEFT_START;
int					ListTexture::TT_MARIO_KID_JUMPING_LEFT_END;
int					ListTexture::TT_MARIO_KID_JUMPING_RIGHT_START;
int					ListTexture::TT_MARIO_KID_JUMPING_RIGHT_END;
int					ListTexture::TT_MARIO_KID_DEATH_START;
int					ListTexture::TT_MARIO_KID_DEATH_END;


LPDIRECT3DTEXTURE9	ListTexture::TT_MARIO_ADULT;
int					ListTexture::TT_MARIO_ADULT_WIDTH;
int					ListTexture::TT_MARIO_ADULT_HEIGHT;
int					ListTexture::TT_MARIO_ADULT_COUNT;
int					ListTexture::TT_MARIO_ADULT_SPRITEPERROW;
int					ListTexture::TT_MARIO_ADULT_ANIMATED_RATE;
int					ListTexture::TT_MARIO_ADULT_MOVING_LEFT_START;
int					ListTexture::TT_MARIO_ADULT_MOVING_LEFT_END;
int					ListTexture::TT_MARIO_ADULT_MOVING_RIGHT_START;
int					ListTexture::TT_MARIO_ADULT_MOVING_RIGHT_END;
int					ListTexture::TT_MARIO_ADULT_JUMPING_LEFT_START;
int					ListTexture::TT_MARIO_ADULT_JUMPING_LEFT_END;
int					ListTexture::TT_MARIO_ADULT_JUMPING_RIGHT_START;
int					ListTexture::TT_MARIO_ADULT_JUMPING_RIGHT_END;
int					ListTexture::TT_MARIO_GUN_MOVING_LEFT_START;
int					ListTexture::TT_MARIO_GUN_MOVING_LEFT_END;
int					ListTexture::TT_MARIO_GUN_MOVING_RIGHT_START;
int					ListTexture::TT_MARIO_GUN_MOVING_RIGHT_END;
int					ListTexture::TT_MARIO_GUN_JUMPING_LEFT_START;
int					ListTexture::TT_MARIO_GUN_JUMPING_LEFT_END;
int					ListTexture::TT_MARIO_GUN_JUMPING_RIGHT_START;
int					ListTexture::TT_MARIO_GUN_JUMPING_RIGHT_END;


LPDIRECT3DTEXTURE9	ListTexture::TT_BRICK_BREAK_LEFT;
int					ListTexture::TT_BRICK_BREAK_LEFT_WIDTH;
int					ListTexture::TT_BRICK_BREAK_LEFT_HEIGHT;
int					ListTexture::TT_BRICK_BREAK_LEFT_COUNT;
int					ListTexture::TT_BRICK_BREAK_LEFT_SPRITEPERROW;
int					ListTexture::TT_BRICK_BREAK_LEFT_ANIMATED_RATE;

LPDIRECT3DTEXTURE9	ListTexture::TT_PIPE_CAP;
int					ListTexture::TT_PIPE_CAP_WIDTH;
int					ListTexture::TT_PIPE_CAP_HEIGHT;
int					ListTexture::TT_PIPE_CAP_COUNT;
int					ListTexture::TT_PIPE_CAP_SPRITEPERROW;
					
LPDIRECT3DTEXTURE9	ListTexture::TT_PIPE_BODY;
int					ListTexture::TT_PIPE_BODY_WIDTH;
int					ListTexture::TT_PIPE_BODY_HEIGHT;
int					ListTexture::TT_PIPE_BODY_COUNT;
int					ListTexture::TT_PIPE_BODY_SPRITEPERROW;

LPDIRECT3DTEXTURE9	ListTexture::TT_BRICK_BONUS;
int					ListTexture::TT_BRICK_BONUS_WIDTH;
int					ListTexture::TT_BRICK_BONUS_HEIGHT;
int					ListTexture::TT_BRICK_BONUS_COUNT;
int					ListTexture::TT_BRICK_BONUS_SPRITEPERROW;
int					ListTexture::TT_BRICK_BONUS_ANIMATED_RATE;

LPDIRECT3DTEXTURE9	ListTexture::TT_BONUS_MUSHROOM;
int					ListTexture::TT_BONUS_MUSHROOM_WIDTH;
int					ListTexture::TT_BONUS_MUSHROOM_HEIGHT;
int					ListTexture::TT_BONUS_MUSHROOM_COUNT;
int					ListTexture::TT_BONUS_MUSHROOM_SPRITEPERROW;

LPDIRECT3DTEXTURE9	ListTexture::TT_EMPTY_BRICK;

LPDIRECT3DTEXTURE9	ListTexture::TT_FLOWER;
int					ListTexture::TT_FLOWER_WIDTH;
int					ListTexture::TT_FLOWER_HEIGHT;
int					ListTexture::TT_FLOWER_COUNT;
int					ListTexture::TT_FLOWER_SPRITEPERROW;
int					ListTexture::TT_FLOWER_ANIMATED_RATE;

LPDIRECT3DTEXTURE9	ListTexture::TT_BULLET;
int					ListTexture::TT_BULLET_WIDTH;
int					ListTexture::TT_BULLET_HEIGHT;
int					ListTexture::TT_BULLET_COUNT;
int					ListTexture::TT_BULLET_SPRITEPERROW;
int					ListTexture::TT_BULLET_ANIMATED_RATE;

LPDIRECT3DTEXTURE9	ListTexture::TT_TURLE_ENEMY;
int					ListTexture::TT_TURLE_ENEMY_WIDTH;					
int					ListTexture::TT_TURLE_ENEMY_HEIGHT;					
int					ListTexture::TT_TURLE_ENEMY_COUNT;					
int					ListTexture::TT_TURLE_ENEMY_SPRITEPERROW;			
int					ListTexture::TT_TURLE_ENEMY_ANIMATED_RATE;

LPDIRECT3DTEXTURE9	ListTexture::TT_TURLE_DEATH;
int					ListTexture::TT_TURLE_DEATH_WIDTH;					
int					ListTexture::TT_TURLE_DEATH_HEIGHT;					
int					ListTexture::TT_TURLE_DEATH_COUNT;					
int					ListTexture::TT_TURLE_DEATH_SPRITEPERROW;			
int					ListTexture::TT_TURLE_DEATH_ANIMATED_RATE;	

LPDIRECT3DTEXTURE9	ListTexture::TT_MARIO_TEXT;
int					ListTexture::TT_MARIO_TEXT_WIDTH;
int					ListTexture::TT_MARIO_TEXT_HEIGHT;

LPDIRECT3DTEXTURE9	ListTexture::TT_GAMEOVER_TEXT;
int					ListTexture::TT_GAMEOVER_TEXT_WIDTH;
int					ListTexture::TT_GAMEOVER_TEXT_HEIGHT;

LPDIRECT3DTEXTURE9	ListTexture::TT_TIME_TEXT;
int					ListTexture::TT_TIME_TEXT_WIDTH;
int					ListTexture::TT_TIME_TEXT_HEIGHT;

LPDIRECT3DTEXTURE9	ListTexture::TT_WORLD_TEXT;
int					ListTexture::TT_WORLD_TEXT_WIDTH;
int					ListTexture::TT_WORLD_TEXT_HEIGHT;

LPDIRECT3DTEXTURE9	ListTexture::TT_COIN_COUNT;
int					ListTexture::TT_COIN_COUNT_WIDTH;
int					ListTexture::TT_COIN_COUNT_HEIGHT;

LPDIRECT3DTEXTURE9	ListTexture::TT_NUMBER;
int					ListTexture::TT_NUMBER_WIDTH;
int					ListTexture::TT_NUMBER_HEIGHT;
int					ListTexture::TT_NUMBER_COUNT;
int					ListTexture::TT_NUMBER_SPRITEPERROW;

LPDIRECT3DTEXTURE9	ListTexture::TT_COIN_PICK;
int					ListTexture::TT_COIN_PICK_WIDTH;
int					ListTexture::TT_COIN_PICK_HEIGHT;
int					ListTexture::TT_COIN_PICK_COUNT;
int					ListTexture::TT_COIN_PICK_SPRITEPERROW;
int					ListTexture::TT_COIN_PICK_ANIMATED_RATE;

LPDIRECT3DTEXTURE9	ListTexture::TT_OUT_COIN;
int					ListTexture::TT_OUT_COIN_WIDTH;
int					ListTexture::TT_OUT_COIN_HEIGHT;
int					ListTexture::TT_OUT_COIN_COUNT;
int					ListTexture::TT_OUT_COIN_SPRITEPERROW;
int					ListTexture::TT_OUT_COIN_ANIMATED_RATE;

LPDIRECT3DTEXTURE9	ListTexture::TT_HARD_BRICK;
int					ListTexture::TT_HARD_BRICK_WIDTH;
int					ListTexture::TT_HARD_BRICK_HEIGHT;
int					ListTexture::TT_HARD_BRICK_COUNT;
int					ListTexture::TT_HARD_BRICK_SPRITEPERROW;

LPDIRECT3DTEXTURE9	ListTexture::TT_PIRHANA_PLANT;
int					ListTexture::TT_PIRHANA_PLANT_WIDTH;
int					ListTexture::TT_PIRHANA_PLANT_HEIGHT;
int					ListTexture::TT_PIRHANA_PLANT_COUNT;
int					ListTexture::TT_PIRHANA_PLANT_SPRITEPERROW;
int					ListTexture::TT_PIRHANA_PLANT_ANIMATED_RATE;

LPDIRECT3DTEXTURE9	ListTexture::TT_END_MAP;
int					ListTexture::TT_END_MAP_WIDTH;
int					ListTexture::TT_END_MAP_HEIGHT;
int					ListTexture::TT_END_MAP_COUNT;
int					ListTexture::TT_END_MAP_SPRITEPERROW;

LPDIRECT3DTEXTURE9	ListTexture::TT_MENU_BACKGROUND;
LPDIRECT3DTEXTURE9	ListTexture::TT_MENU_OPTIONS;

LPDIRECT3DTEXTURE9	ListTexture::TT_MOUNTAIN;
int					ListTexture::TT_MOUNTAIN_WIDTH;
int					ListTexture::TT_MOUNTAIN_HEIGHT;
int					ListTexture::TT_MOUNTAIN_COUNT;
int					ListTexture::TT_MOUNTAIN_SPRITEPERROW;

LPDIRECT3DTEXTURE9	ListTexture::TT_HIGH_TREE;
int					ListTexture::TT_HIGH_TREE_WIDTH;
int					ListTexture::TT_HIGH_TREE_HEIGHT;
int					ListTexture::TT_HIGH_TREE_COUNT;
int					ListTexture::TT_HIGH_TREE_SPRITEPERROW;

LPDIRECT3DTEXTURE9	ListTexture::TT_LOW_TREE;
int					ListTexture::TT_LOW_TREE_WIDTH;
int					ListTexture::TT_LOW_TREE_HEIGHT;
int					ListTexture::TT_LOW_TREE_COUNT;
int					ListTexture::TT_LOW_TREE_SPRITEPERROW;

LPDIRECT3DTEXTURE9	ListTexture::TT_OPTION;

LPDIRECT3DTEXTURE9	ListTexture::TT_CHANGE_MAP;
LPDIRECT3DTEXTURE9	ListTexture::TT_WORLD;
int					ListTexture::TT_WORLD_WIDTH;
int					ListTexture::TT_WORLD_HEIGHT;
LPDIRECT3DTEXTURE9	ListTexture::TT_WORLD_NUMBER;
int					ListTexture::TT_WORLD_NUMBER_WIDTH;
int					ListTexture::TT_WORLD_NUMBER_HEIGHT;
int					ListTexture::TT_WORLD_NUMBER_COUNT;
int					ListTexture::TT_WORLD_NUMBER_SPRITEPERROW;


LPDIRECT3DTEXTURE9	ListTexture::TT_CROSS;
int					ListTexture::TT_CROSS_WIDTH;
int					ListTexture::TT_CROSS_HEIGHT;
LPDIRECT3DTEXTURE9	ListTexture::TT_FALLING_CROSS;

LPDIRECT3DTEXTURE9	ListTexture::TT_STARTGAMEOPTION_BACKGROUND;

LPDIRECT3DTEXTURE9	ListTexture::TT_RED_TURLE_ENEMY;
int					ListTexture::TT_RED_TURLE_ENEMY_WIDTH;					
int					ListTexture::TT_RED_TURLE_ENEMY_HEIGHT;					
int					ListTexture::TT_RED_TURLE_ENEMY_COUNT;					
int					ListTexture::TT_RED_TURLE_ENEMY_SPRITEPERROW;			
int					ListTexture::TT_RED_TURLE_ENEMY_ANIMATED_RATE;

LPDIRECT3DTEXTURE9	ListTexture::TT_RED_TURLE_DEATH;
int					ListTexture::TT_RED_TURLE_DEATH_WIDTH;					
int					ListTexture::TT_RED_TURLE_DEATH_HEIGHT;					
int					ListTexture::TT_RED_TURLE_DEATH_COUNT;					
int					ListTexture::TT_RED_TURLE_DEATH_SPRITEPERROW;			
int					ListTexture::TT_RED_TURLE_DEATH_ANIMATED_RATE;

LPDIRECT3DTEXTURE9	ListTexture::TT_GROUND_MUSHROOM;
int					ListTexture::TT_GROUND_MUSHROOM_WIDTH;
int					ListTexture::TT_GROUND_MUSHROOM_HEIGHT;
int					ListTexture::TT_GROUND_MUSHROOM_COUNT;
int					ListTexture::TT_GROUND_MUSHROOM_SPRITEPERROW;

LPDIRECT3DTEXTURE9	ListTexture::TT_GROUND_UNDER_MUSHROOM;
int					ListTexture::TT_GROUND_UNDER_MUSHROOM_WIDTH;
int					ListTexture::TT_GROUND_UNDER_MUSHROOM_HEIGHT;
int					ListTexture::TT_GROUND_UNDER_MUSHROOM_COUNT;
int					ListTexture::TT_GROUND_UNDER_MUSHROOM_SPRITEPERROW;

LPDIRECT3DTEXTURE9	ListTexture::TT_STAR;
int					ListTexture::TT_STAR_WIDTH;
int					ListTexture::TT_STAR_HEIGHT;
int					ListTexture::TT_STAR_COUNT;
int					ListTexture::TT_STAR_SPRITEPERROW;
int					ListTexture::TT_STARR_ANIMATED_RATE;

ListTexture::ListTexture(void)
{
}

ListTexture::~ListTexture(void)
{
}

void ListTexture::CreateAllTexture()
{
//	ListTexture::TT_MARIO_KID				= GlobalHandler::directX->LoadTextureFromFile("Images\\Mario.png",0);
	
	ListTexture::TT_BRICK							= GlobalHandler::directX->LoadTextureFromFile("Media\\brick.bmp",0);
	ListTexture::TT_BRICK_WIDTH						= 32;
	ListTexture::TT_BRICK_HEIGHT					= 32;
	ListTexture::TT_BRICK_COUNT						= 1;
	ListTexture::TT_BRICK_SPRITEPERROW				= 1;

	ListTexture::TT_CLOUD							= GlobalHandler::directX->LoadTextureFromFile("Media\\cloud.bmp",0);
	ListTexture::TT_CLOUD_WIDTH						= 64;
	ListTexture::TT_CLOUD_HEIGHT					= 45;
	ListTexture::TT_CLOUD_COUNT						= 2;
	ListTexture::TT_CLOUD_SPRITEPERROW				= 2;
	ListTexture::TT_CLOUD_ANIMATED_RATE 			= 300;

	ListTexture::TT_GRASS							= GlobalHandler::directX->LoadTextureFromFile("Media\\grass.bmp",0);
	ListTexture::TT_GRASS_WIDTH						= 64;
	ListTexture::TT_GRASS_HEIGHT					= 32;
	ListTexture::TT_GRASS_COUNT						= 2;
	ListTexture::TT_GRASS_SPRITEPERROW				= 2;
	ListTexture::TT_GRASS_ANIMATED_RATE 			= 300;

	ListTexture::TT_FENCE							= GlobalHandler::directX->LoadTextureFromFile("Media\\fence.bmp",0);
	ListTexture::TT_FENCE_WIDTH						= 140;
	ListTexture::TT_FENCE_HEIGHT					= 32;
	ListTexture::TT_FENCE_COUNT						= 1;
	ListTexture::TT_FENCE_SPRITEPERROW				= 1;

	ListTexture::TT_MUSHROOM_ENEMY					= GlobalHandler::directX->LoadTextureFromFile("Media\\enemy_musroom.bmp", 0);
	ListTexture::TT_MUSHROOM_ENEMY_WIDTH			= 32;
	ListTexture::TT_MUSHROOM_ENEMY_HEIGHT			= 32;
	ListTexture::TT_MUSHROOM_ENEMY_COUNT			= 4;
	ListTexture::TT_MUSHROOM_ENEMY_SPRITEPERROW		= 2;
	ListTexture::TT_MUSHROOM_ENEMY_ANIMATED_RATE	= 30;

	ListTexture::TT_GROUND							= GlobalHandler::directX->LoadTextureFromFile("Media\\ground.png", 0);
	ListTexture::TT_GROUND_WIDTH					= 32;
	ListTexture::TT_GROUND_HEIGHT					= 32;
	ListTexture::TT_GROUND_COUNT					= 7;
	ListTexture::TT_GROUND_SPRITEPERROW				= 7;

	ListTexture::TT_MARIO_KID							= GlobalHandler::directX->LoadTextureFromFile("Media\\mario.bmp", 0);;
	ListTexture::TT_MARIO_KID_WIDTH						= 32;
	ListTexture::TT_MARIO_KID_HEIGHT					= 32;
	ListTexture::TT_MARIO_KID_COUNT						= 7;
	ListTexture::TT_MARIO_KID_SPRITEPERROW				= 2;
	ListTexture::TT_MARIO_KID_ANIMATED_RATE				= 200;
	ListTexture::TT_MARIO_KID_MOVING_LEFT_START			= 2;
	ListTexture::TT_MARIO_KID_MOVING_LEFT_END			= 3;
	ListTexture::TT_MARIO_KID_MOVING_RIGHT_START		= 0;
	ListTexture::TT_MARIO_KID_MOVING_RIGHT_END			= 1;
	ListTexture::TT_MARIO_KID_JUMPING_LEFT_START		= 5;
	ListTexture::TT_MARIO_KID_JUMPING_LEFT_END			= 5;
	ListTexture::TT_MARIO_KID_JUMPING_RIGHT_START		= 4;
	ListTexture::TT_MARIO_KID_JUMPING_RIGHT_END			= 4;
	ListTexture::TT_MARIO_KID_DEATH_START				= 6;
	ListTexture::TT_MARIO_KID_DEATH_END					= 6;

	ListTexture::TT_MARIO_ADULT							= GlobalHandler::directX->LoadTextureFromFile("Media\\mario_growup.bmp", 0);
	ListTexture::TT_MARIO_ADULT_WIDTH					= 32;
	ListTexture::TT_MARIO_ADULT_HEIGHT					= 60;
	ListTexture::TT_MARIO_ADULT_COUNT					= 16;
	ListTexture::TT_MARIO_ADULT_SPRITEPERROW			= 3;
	ListTexture::TT_MARIO_ADULT_ANIMATED_RATE			= 200;
	ListTexture::TT_MARIO_ADULT_MOVING_LEFT_START		= 3;
	ListTexture::TT_MARIO_ADULT_MOVING_LEFT_END			= 5;
	ListTexture::TT_MARIO_ADULT_MOVING_RIGHT_START		= 0;
	ListTexture::TT_MARIO_ADULT_MOVING_RIGHT_END		= 2;
	ListTexture::TT_MARIO_ADULT_JUMPING_LEFT_START		= 13;
	ListTexture::TT_MARIO_ADULT_JUMPING_LEFT_END		= 13;
	ListTexture::TT_MARIO_ADULT_JUMPING_RIGHT_START		= 12;
	ListTexture::TT_MARIO_ADULT_JUMPING_RIGHT_END		= 12;
	ListTexture::TT_MARIO_GUN_MOVING_LEFT_START			= 9;
	ListTexture::TT_MARIO_GUN_MOVING_LEFT_END			= 11;
	ListTexture::TT_MARIO_GUN_MOVING_RIGHT_START		= 6;
	ListTexture::TT_MARIO_GUN_MOVING_RIGHT_END			= 8;
	ListTexture::TT_MARIO_GUN_JUMPING_LEFT_START		= 15;
	ListTexture::TT_MARIO_GUN_JUMPING_LEFT_END			= 15;
	ListTexture::TT_MARIO_GUN_JUMPING_RIGHT_START		= 14;
	ListTexture::TT_MARIO_GUN_JUMPING_RIGHT_END			= 14;

	ListTexture::TT_BRICK_BREAK_LEFT					= GlobalHandler::directX->LoadTextureFromFile("Media\\brick_broke_left.bmp", 0);
	ListTexture::TT_BRICK_BREAK_LEFT_WIDTH				= 16;
	ListTexture::TT_BRICK_BREAK_LEFT_HEIGHT				= 16;
	ListTexture::TT_BRICK_BREAK_LEFT_COUNT				= 4;
	ListTexture::TT_BRICK_BREAK_LEFT_SPRITEPERROW		= 4;
	ListTexture::TT_BRICK_BREAK_LEFT_ANIMATED_RATE		= 70;

	ListTexture::TT_PIPE_CAP							= GlobalHandler::directX->LoadTextureFromFile("Media\\pipe_cap.bmp", 0);
	ListTexture::TT_PIPE_CAP_WIDTH						= 64;
	ListTexture::TT_PIPE_CAP_HEIGHT						= 32;
	ListTexture::TT_PIPE_CAP_COUNT						= 1;
	ListTexture::TT_PIPE_CAP_SPRITEPERROW				= 1;

	ListTexture::TT_PIPE_BODY							= GlobalHandler::directX->LoadTextureFromFile("Media\\pipe_body.bmp", 0);
	ListTexture::TT_PIPE_BODY_WIDTH						= 64;
	ListTexture::TT_PIPE_BODY_HEIGHT					= 32;
	ListTexture::TT_PIPE_BODY_COUNT						= 1;
	ListTexture::TT_PIPE_BODY_SPRITEPERROW				= 1;

	ListTexture::TT_BRICK_BONUS							= GlobalHandler::directX->LoadTextureFromFile("Media\\brick_bonus.png", 0);
	ListTexture::TT_BRICK_BONUS_WIDTH					= 32;
	ListTexture::TT_BRICK_BONUS_HEIGHT					= 32;
	ListTexture::TT_BRICK_BONUS_COUNT					= 3;
	ListTexture::TT_BRICK_BONUS_SPRITEPERROW			= 3;
	ListTexture::TT_BRICK_BONUS_ANIMATED_RATE			= 130;

	ListTexture::TT_BONUS_MUSHROOM						= GlobalHandler::directX->LoadTextureFromFile("Media\\bonus_mushroom.bmp", 0);
	ListTexture::TT_BONUS_MUSHROOM_WIDTH				= 32;
	ListTexture::TT_BONUS_MUSHROOM_HEIGHT				= 32;
	ListTexture::TT_BONUS_MUSHROOM_COUNT				= 2;
	ListTexture::TT_BONUS_MUSHROOM_SPRITEPERROW			= 2;

	ListTexture::TT_EMPTY_BRICK							= GlobalHandler::directX->LoadTextureFromFile("Media\\empty_brick.bmp", 0);

	ListTexture::TT_FLOWER								= GlobalHandler::directX->LoadTextureFromFile("Media\\sprite_flower.bmp", 0);
	ListTexture::TT_FLOWER_WIDTH						= 32;
	ListTexture::TT_FLOWER_HEIGHT						= 32;
	ListTexture::TT_FLOWER_COUNT						= 4;
	ListTexture::TT_FLOWER_SPRITEPERROW					= 4;
	ListTexture::TT_FLOWER_ANIMATED_RATE				= 200;

	ListTexture::TT_BULLET								= GlobalHandler::directX->LoadTextureFromFile("Media\\bullet.png", 0);
	ListTexture::TT_BULLET_WIDTH						= 17;
	ListTexture::TT_BULLET_HEIGHT						= 17;
	ListTexture::TT_BULLET_COUNT						= 4;
	ListTexture::TT_BULLET_SPRITEPERROW					= 4;
	ListTexture::TT_BULLET_ANIMATED_RATE				= 200;

	ListTexture::TT_TURLE_ENEMY							= GlobalHandler::directX->LoadTextureFromFile("Media\\enemy_turle.bmp", 0);
	ListTexture::TT_TURLE_ENEMY_WIDTH					= 32;
	ListTexture::TT_TURLE_ENEMY_HEIGHT					= 47;
	ListTexture::TT_TURLE_ENEMY_COUNT					= 4;
	ListTexture::TT_TURLE_ENEMY_SPRITEPERROW			= 2;
	ListTexture::TT_TURLE_ENEMY_ANIMATED_RATE			= 80;

	ListTexture::TT_TURLE_DEATH							= GlobalHandler::directX->LoadTextureFromFile("Media\\turle_death.png", 0);
	ListTexture::TT_TURLE_DEATH_WIDTH					= 33;
	ListTexture::TT_TURLE_DEATH_HEIGHT					= 32;
	ListTexture::TT_TURLE_DEATH_COUNT					= 4;
	ListTexture::TT_TURLE_DEATH_SPRITEPERROW			= 4;
	ListTexture::TT_TURLE_DEATH_ANIMATED_RATE			= 80;

	ListTexture::TT_MARIO_TEXT							= GlobalHandler::directX->LoadTextureFromFile("Media\\text_mario.png",0);
	ListTexture::TT_MARIO_TEXT_WIDTH					= 95;
	ListTexture::TT_MARIO_TEXT_HEIGHT					= 16;

	ListTexture::TT_GAMEOVER_TEXT						= GlobalHandler::directX->LoadTextureFromFile("Media\\text_gameover.bmp",0);
	ListTexture::TT_GAMEOVER_TEXT_WIDTH					= 141;
	ListTexture::TT_GAMEOVER_TEXT_HEIGHT				= 25;

	ListTexture::TT_TIME_TEXT							= GlobalHandler::directX->LoadTextureFromFile("Media\\text_time.bmp",0);
	ListTexture::TT_TIME_TEXT_WIDTH						= 64;
	ListTexture::TT_TIME_TEXT_HEIGHT					= 16;

	ListTexture::TT_WORLD_TEXT							= GlobalHandler::directX->LoadTextureFromFile("Media\\text_world.bmp",0);
	ListTexture::TT_WORLD_TEXT_WIDTH					= 79;
	ListTexture::TT_WORLD_TEXT_HEIGHT					= 16;

	ListTexture::TT_COIN_COUNT							= GlobalHandler::directX->LoadTextureFromFile("Media\\coin_count.png",0);
	ListTexture::TT_COIN_COUNT_WIDTH					= 27;
	ListTexture::TT_COIN_COUNT_HEIGHT					= 16;
	
	ListTexture::TT_NUMBER								= GlobalHandler::directX->LoadTextureFromFile("Media\\number.png",0);
	ListTexture::TT_NUMBER_WIDTH						= 15;
	ListTexture::TT_NUMBER_HEIGHT						= 16;
	ListTexture::TT_NUMBER_COUNT						= 11;
	ListTexture::TT_NUMBER_SPRITEPERROW					= 11;

	ListTexture::TT_COIN_PICK							= GlobalHandler::directX->LoadTextureFromFile("Media\\coin_pickup.bmp",0);
	ListTexture::TT_COIN_PICK_WIDTH						= 32;
	ListTexture::TT_COIN_PICK_HEIGHT					= 32;
	ListTexture::TT_COIN_PICK_COUNT						= 4;
	ListTexture::TT_COIN_PICK_SPRITEPERROW				= 4;
	ListTexture::TT_COIN_PICK_ANIMATED_RATE				= 100;

	ListTexture::TT_OUT_COIN							= GlobalHandler::directX->LoadTextureFromFile("Media\\coin.bmp",0);
	ListTexture::TT_OUT_COIN_WIDTH						= 19;
	ListTexture::TT_OUT_COIN_HEIGHT						= 29;
	ListTexture::TT_OUT_COIN_COUNT						= 2;
	ListTexture::TT_OUT_COIN_SPRITEPERROW				= 2;
	ListTexture::TT_OUT_COIN_ANIMATED_RATE				= 100;

	ListTexture::TT_HARD_BRICK							= GlobalHandler::directX->LoadTextureFromFile("Media\\hardbrick.bmp",0);
	ListTexture::TT_HARD_BRICK_WIDTH					= 32;
	ListTexture::TT_HARD_BRICK_HEIGHT					= 32;
	ListTexture::TT_HARD_BRICK_COUNT					= 1;
	ListTexture::TT_HARD_BRICK_SPRITEPERROW				= 1;

	ListTexture::TT_PIRHANA_PLANT						= GlobalHandler::directX->LoadTextureFromFile("Media\\pirhana_plant.png",0);
	ListTexture::TT_PIRHANA_PLANT_WIDTH					= 28;
	ListTexture::TT_PIRHANA_PLANT_HEIGHT				= 35;
	ListTexture::TT_PIRHANA_PLANT_COUNT					= 2;
	ListTexture::TT_PIRHANA_PLANT_SPRITEPERROW			= 2;
	ListTexture::TT_PIRHANA_PLANT_ANIMATED_RATE			= 200;

	ListTexture::TT_END_MAP								= GlobalHandler::directX->LoadTextureFromFile("Media\\end_map.png",0);
	ListTexture::TT_END_MAP_WIDTH						= 31;
	ListTexture::TT_END_MAP_HEIGHT						= 288;
	ListTexture::TT_END_MAP_COUNT						= 3;
	ListTexture::TT_END_MAP_SPRITEPERROW				= 3;

	ListTexture::TT_MENU_BACKGROUND						= GlobalHandler::directX->LoadTextureFromFile("Media\\menu_background.jpg",0);
	ListTexture::TT_MENU_OPTIONS						= GlobalHandler::directX->LoadTextureFromFile("Media\\options.png",0);

	ListTexture::TT_MOUNTAIN							= GlobalHandler::directX->LoadTextureFromFile("Media\\mountain.bmp",0);
	ListTexture::TT_MOUNTAIN_WIDTH						= 310;
	ListTexture::TT_MOUNTAIN_HEIGHT						= 128;
	ListTexture::TT_MOUNTAIN_COUNT						= 1;
	ListTexture::TT_MOUNTAIN_SPRITEPERROW				= 1;

	ListTexture::TT_HIGH_TREE							= GlobalHandler::directX->LoadTextureFromFile("Media\\tree_high.bmp",0);
	ListTexture::TT_HIGH_TREE_WIDTH						= 32;
	ListTexture::TT_HIGH_TREE_HEIGHT					= 96;
	ListTexture::TT_HIGH_TREE_COUNT						= 1;
	ListTexture::TT_HIGH_TREE_SPRITEPERROW				= 1;

	ListTexture::TT_LOW_TREE							= GlobalHandler::directX->LoadTextureFromFile("Media\\tree_low.bmp",0);
	ListTexture::TT_LOW_TREE_WIDTH						= 32;
	ListTexture::TT_LOW_TREE_HEIGHT						= 64;
	ListTexture::TT_LOW_TREE_COUNT						= 1;
	ListTexture::TT_LOW_TREE_SPRITEPERROW				= 1;

	ListTexture::TT_OPTION								= GlobalHandler::directX->LoadTextureFromFile("Media\\Option.jpg",0);

	ListTexture::TT_CHANGE_MAP							= GlobalHandler::directX->LoadTextureFromFile("Media\\changeMap.jpg",0);
	ListTexture::TT_WORLD								= GlobalHandler::directX->LoadTextureFromFile("Media\\world.png",0);
	ListTexture::TT_WORLD_WIDTH							= 208;
	ListTexture::TT_WORLD_HEIGHT						= 53;
	ListTexture::TT_WORLD_NUMBER						= GlobalHandler::directX->LoadTextureFromFile("Media\\map_number.png",0);
	ListTexture::TT_WORLD_NUMBER_WIDTH					= 26;
	ListTexture::TT_WORLD_NUMBER_HEIGHT					= 44;
	ListTexture::TT_WORLD_NUMBER_COUNT					= 9;
	ListTexture::TT_WORLD_NUMBER_SPRITEPERROW			= 9;

	ListTexture::TT_CROSS								= GlobalHandler::directX->LoadTextureFromFile("Media\\cross.png",0);
	ListTexture::TT_CROSS_WIDTH							= 96;
	ListTexture::TT_CROSS_HEIGHT						= 18;
	ListTexture::TT_FALLING_CROSS								= GlobalHandler::directX->LoadTextureFromFile("Media\\FallingCross.png",0);

	ListTexture::TT_STARTGAMEOPTION_BACKGROUND			= GlobalHandler::directX->LoadTextureFromFile("Media\\startGameOptions.jpg",0);

	ListTexture::TT_RED_TURLE_ENEMY						= GlobalHandler::directX->LoadTextureFromFile("Media\\red_enemy_turle.png", 0);
	ListTexture::TT_RED_TURLE_ENEMY_WIDTH				= 32;
	ListTexture::TT_RED_TURLE_ENEMY_HEIGHT				= 47;
	ListTexture::TT_RED_TURLE_ENEMY_COUNT				= 4;
	ListTexture::TT_RED_TURLE_ENEMY_SPRITEPERROW		= 2;
	ListTexture::TT_RED_TURLE_ENEMY_ANIMATED_RATE		= 80;

	ListTexture::TT_RED_TURLE_DEATH						= GlobalHandler::directX->LoadTextureFromFile("Media\\red_turle_death.png", 0);
	ListTexture::TT_RED_TURLE_DEATH_WIDTH				= 33;
	ListTexture::TT_RED_TURLE_DEATH_HEIGHT				= 32;
	ListTexture::TT_RED_TURLE_DEATH_COUNT				= 4;
	ListTexture::TT_RED_TURLE_DEATH_SPRITEPERROW		= 4;
	ListTexture::TT_RED_TURLE_DEATH_ANIMATED_RATE		= 80;

	ListTexture::TT_GROUND_MUSHROOM						= GlobalHandler::directX->LoadTextureFromFile("Media\\MushRoomGround.png", 0);
	ListTexture::TT_GROUND_MUSHROOM_WIDTH				= 32;
	ListTexture::TT_GROUND_MUSHROOM_HEIGHT				= 35;
	ListTexture::TT_GROUND_MUSHROOM_COUNT				= 3;
	ListTexture::TT_GROUND_MUSHROOM_SPRITEPERROW		= 3;

	ListTexture::TT_GROUND_UNDER_MUSHROOM				= GlobalHandler::directX->LoadTextureFromFile("Media\\GroundUnderMushRoom.jpg", 0);
	ListTexture::TT_GROUND_UNDER_MUSHROOM_WIDTH			= 32;
	ListTexture::TT_GROUND_UNDER_MUSHROOM_HEIGHT		= 32;
	ListTexture::TT_GROUND_UNDER_MUSHROOM_COUNT			= 3;
	ListTexture::TT_GROUND_UNDER_MUSHROOM_SPRITEPERROW	= 3;

	ListTexture::TT_STAR								= GlobalHandler::directX->LoadTextureFromFile("Media\\bonus_star.png", 0);
	ListTexture::TT_STAR_WIDTH							= 32;
	ListTexture::TT_STAR_HEIGHT							= 32;
	ListTexture::TT_STAR_COUNT							= 4;
	ListTexture::TT_STAR_SPRITEPERROW					= 4;
	ListTexture::TT_STARR_ANIMATED_RATE					= 80;
}														
