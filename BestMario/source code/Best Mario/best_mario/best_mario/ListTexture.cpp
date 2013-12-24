#include "ListTexture.h"
#include "GlobalHandler.h"

LPDIRECT3DTEXTURE9	ListTexture::TT_CLOUD = NULL;
int					ListTexture::TT_CLOUD_WIDTH;
int					ListTexture::TT_CLOUD_HEIGHT;
int					ListTexture::TT_CLOUD_COUNT;
int					ListTexture::TT_CLOUD_SPRITEPERROW;
int					ListTexture::TT_CLOUD_ANIMATED_RATE;

LPDIRECT3DTEXTURE9	ListTexture::TT_FENCE = NULL;
int					ListTexture::TT_FENCE_WIDTH;
int					ListTexture::TT_FENCE_HEIGHT;
int					ListTexture::TT_FENCE_COUNT;
int					ListTexture::TT_FENCE_SPRITEPERROW;

LPDIRECT3DTEXTURE9	ListTexture::TT_GRASS = NULL;
int					ListTexture::TT_GRASS_WIDTH;
int					ListTexture::TT_GRASS_HEIGHT;
int					ListTexture::TT_GRASS_COUNT;
int					ListTexture::TT_GRASS_SPRITEPERROW;
int					ListTexture::TT_GRASS_ANIMATED_RATE;

LPDIRECT3DTEXTURE9	ListTexture::TT_GROUND = NULL;
int					ListTexture::TT_GROUND_WIDTH;
int					ListTexture::TT_GROUND_HEIGHT;
int					ListTexture::TT_GROUND_COUNT;
int					ListTexture::TT_GROUND_SPRITEPERROW;

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

LPDIRECT3DTEXTURE9	ListTexture::TT_MOUNTAIN;
int					ListTexture::TT_MOUNTAIN_WIDTH;
int					ListTexture::TT_MOUNTAIN_HEIGHT;
int					ListTexture::TT_MOUNTAIN_COUNT;
int					ListTexture::TT_MOUNTAIN_SPRITEPERROW;

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

LPDIRECT3DTEXTURE9	ListTexture::TT_PIPE_1;
int					ListTexture::TT_PIPE_1_WIDTH;
int					ListTexture::TT_PIPE_1_HEIGHT;
int					ListTexture::TT_PIPE_1_COUNT;
int					ListTexture::TT_PIPE_1_SPRITEPERROW;

LPDIRECT3DTEXTURE9	ListTexture::TT_PIPE_2;
int					ListTexture::TT_PIPE_2_WIDTH;
int					ListTexture::TT_PIPE_2_HEIGHT;
int					ListTexture::TT_PIPE_2_COUNT;
int					ListTexture::TT_PIPE_2_SPRITEPERROW;

LPDIRECT3DTEXTURE9	ListTexture::TT_PIPE_3;
int					ListTexture::TT_PIPE_3_WIDTH;
int					ListTexture::TT_PIPE_3_HEIGHT;
int					ListTexture::TT_PIPE_3_COUNT;
int					ListTexture::TT_PIPE_3_SPRITEPERROW;

LPDIRECT3DTEXTURE9	ListTexture::TT_OUT_COIN;
int					ListTexture::TT_OUT_COIN_WIDTH;
int					ListTexture::TT_OUT_COIN_HEIGHT;
int					ListTexture::TT_OUT_COIN_COUNT;
int					ListTexture::TT_OUT_COIN_SPRITEPERROW;
int					ListTexture::TT_OUT_COIN_ANIMATED_RATE;

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

LPDIRECT3DTEXTURE9	ListTexture::TT_HARD_BRICK;
int					ListTexture::TT_HARD_BRICK_WIDTH;
int					ListTexture::TT_HARD_BRICK_HEIGHT;
int					ListTexture::TT_HARD_BRICK_COUNT;
int					ListTexture::TT_HARD_BRICK_SPRITEPERROW;

LPDIRECT3DTEXTURE9	ListTexture::TT_BRICK;
int					ListTexture::TT_BRICK_WIDTH;
int					ListTexture::TT_BRICK_HEIGHT;
int					ListTexture::TT_BRICK_COUNT;
int					ListTexture::TT_BRICK_SPRITEPERROW;

LPDIRECT3DTEXTURE9	ListTexture::TT_BRICK_BREAK_LEFT;
int					ListTexture::TT_BRICK_BREAK_LEFT_WIDTH;
int					ListTexture::TT_BRICK_BREAK_LEFT_HEIGHT;
int					ListTexture::TT_BRICK_BREAK_LEFT_COUNT;
int					ListTexture::TT_BRICK_BREAK_LEFT_SPRITEPERROW;
int					ListTexture::TT_BRICK_BREAK_LEFT_ANIMATED_RATE;

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

LPDIRECT3DTEXTURE9	ListTexture::TT_STAR;
int					ListTexture::TT_STAR_WIDTH;
int					ListTexture::TT_STAR_HEIGHT;
int					ListTexture::TT_STAR_COUNT;
int					ListTexture::TT_STAR_SPRITEPERROW;
int					ListTexture::TT_STARR_ANIMATED_RATE;

LPDIRECT3DTEXTURE9	ListTexture::TT_COIN_PICK;
int					ListTexture::TT_COIN_PICK_WIDTH;
int					ListTexture::TT_COIN_PICK_HEIGHT;
int					ListTexture::TT_COIN_PICK_COUNT;
int					ListTexture::TT_COIN_PICK_SPRITEPERROW;
int					ListTexture::TT_COIN_PICK_ANIMATED_RATE;


//text
LPDIRECT3DTEXTURE9	ListTexture::TT_MARIO_TEXT;
int					ListTexture::TT_MARIO_TEXT_WIDTH;
int					ListTexture::TT_MARIO_TEXT_HEIGHT;

LPDIRECT3DTEXTURE9	ListTexture::TT_COIN_TEXT;
int					ListTexture::TT_COIN_TEXT_WIDTH;
int					ListTexture::TT_COIN_TEXT_HEIGHT;

LPDIRECT3DTEXTURE9	ListTexture::TT_WORLD_TEXT;
int					ListTexture::TT_WORLD_TEXT_WIDTH;
int					ListTexture::TT_WORLD_TEXT_HEIGHT;

LPDIRECT3DTEXTURE9	ListTexture::TT_TIME_TEXT;
int					ListTexture::TT_TIME_TEXT_WIDTH;
int					ListTexture::TT_TIME_TEXT_HEIGHT;

LPDIRECT3DTEXTURE9	ListTexture::TT_NUMBER_TEXT;
int					ListTexture::TT_NUMBER_TEXT_WIDTH;
int					ListTexture::TT_NUMBER_TEXT_HEIGHT;
int					ListTexture::TT_NUMBER_TEXT_COUNT;
int					ListTexture::TT_NUMBER_TEXT_SPRITEPERROW;

ListTexture::ListTexture(void){}

ListTexture::~ListTexture(void){}

void ListTexture::CreateAllTexture(){

	ListTexture::TT_CLOUD								= GlobalHandler::_directX->LoadTextureFromFile("Media\\cloud.bmp",0);
	ListTexture::TT_CLOUD_WIDTH							= 64;
	ListTexture::TT_CLOUD_HEIGHT						= 45;
	ListTexture::TT_CLOUD_COUNT							= 2;
	ListTexture::TT_CLOUD_SPRITEPERROW					= 2;
	ListTexture::TT_CLOUD_ANIMATED_RATE 				= 500;

	ListTexture::TT_FENCE								= GlobalHandler::_directX->LoadTextureFromFile("Media\\fence.bmp",0);
	ListTexture::TT_FENCE_WIDTH							= 140;
	ListTexture::TT_FENCE_HEIGHT						= 32;
	ListTexture::TT_FENCE_COUNT							= 1;
	ListTexture::TT_FENCE_SPRITEPERROW					= 1;

	ListTexture::TT_GRASS								= GlobalHandler::_directX->LoadTextureFromFile("Media\\grass.bmp",0);
	ListTexture::TT_GRASS_WIDTH							= 64;
	ListTexture::TT_GRASS_HEIGHT						= 32;
	ListTexture::TT_GRASS_COUNT							= 2;
	ListTexture::TT_GRASS_SPRITEPERROW					= 2;
	ListTexture::TT_GRASS_ANIMATED_RATE 				= 300;

	ListTexture::TT_GROUND								= GlobalHandler::_directX->LoadTextureFromFile("Media\\ground.png", 0);
	ListTexture::TT_GROUND_WIDTH						= 32;
	ListTexture::TT_GROUND_HEIGHT						= 32;
	ListTexture::TT_GROUND_COUNT						= 7;
	ListTexture::TT_GROUND_SPRITEPERROW					= 7;

	ListTexture::TT_HIGH_TREE							= GlobalHandler::_directX->LoadTextureFromFile("Media\\tree_high.bmp",0);
	ListTexture::TT_HIGH_TREE_WIDTH						= 32;
	ListTexture::TT_HIGH_TREE_HEIGHT					= 96;
	ListTexture::TT_HIGH_TREE_COUNT						= 1;
	ListTexture::TT_HIGH_TREE_SPRITEPERROW				= 1;

	ListTexture::TT_LOW_TREE							= GlobalHandler::_directX->LoadTextureFromFile("Media\\tree_low.bmp",0);
	ListTexture::TT_LOW_TREE_WIDTH						= 32;
	ListTexture::TT_LOW_TREE_HEIGHT						= 64;
	ListTexture::TT_LOW_TREE_COUNT						= 1;
	ListTexture::TT_LOW_TREE_SPRITEPERROW				= 1;

	ListTexture::TT_MOUNTAIN							= GlobalHandler::_directX->LoadTextureFromFile("Media\\mountain.bmp",0);
	ListTexture::TT_MOUNTAIN_WIDTH						= 310;
	ListTexture::TT_MOUNTAIN_HEIGHT						= 128;
	ListTexture::TT_MOUNTAIN_COUNT						= 1;
	ListTexture::TT_MOUNTAIN_SPRITEPERROW				= 1;

	ListTexture::TT_PIPE_CAP							= GlobalHandler::_directX->LoadTextureFromFile("Media\\pipe_cap.bmp", 0);
	ListTexture::TT_PIPE_CAP_WIDTH						= 64;
	ListTexture::TT_PIPE_CAP_HEIGHT						= 32;
	ListTexture::TT_PIPE_CAP_COUNT						= 1;
	ListTexture::TT_PIPE_CAP_SPRITEPERROW				= 1;

	ListTexture::TT_PIPE_BODY							= GlobalHandler::_directX->LoadTextureFromFile("Media\\pipe_body.bmp", 0);
	ListTexture::TT_PIPE_BODY_WIDTH						= 64;
	ListTexture::TT_PIPE_BODY_HEIGHT					= 32;
	ListTexture::TT_PIPE_BODY_COUNT						= 1;
	ListTexture::TT_PIPE_BODY_SPRITEPERROW				= 1;

	ListTexture::TT_PIPE_1								= GlobalHandler::_directX->LoadTextureFromFile("Media\\pipe1.png", 0);
	ListTexture::TT_PIPE_1_WIDTH						= 75;
	ListTexture::TT_PIPE_1_HEIGHT						= 50;
	ListTexture::TT_PIPE_1_COUNT						= 1;
	ListTexture::TT_PIPE_1_SPRITEPERROW					= 1;

	ListTexture::TT_PIPE_2								= GlobalHandler::_directX->LoadTextureFromFile("Media\\pipe2.png", 0);
	ListTexture::TT_PIPE_2_WIDTH						= 75;
	ListTexture::TT_PIPE_2_HEIGHT						= 100;
	ListTexture::TT_PIPE_2_COUNT						= 1;
	ListTexture::TT_PIPE_2_SPRITEPERROW					= 1;

	ListTexture::TT_PIPE_3								= GlobalHandler::_directX->LoadTextureFromFile("Media\\pipe3.png", 0);
	ListTexture::TT_PIPE_3_WIDTH						= 75;
	ListTexture::TT_PIPE_3_HEIGHT						= 200;
	ListTexture::TT_PIPE_3_COUNT						= 1;
	ListTexture::TT_PIPE_3_SPRITEPERROW					= 1;

	ListTexture::TT_OUT_COIN							= GlobalHandler::_directX->LoadTextureFromFile("Media\\coin.bmp",0);
	ListTexture::TT_OUT_COIN_WIDTH						= 19;
	ListTexture::TT_OUT_COIN_HEIGHT						= 29;
	ListTexture::TT_OUT_COIN_COUNT						= 2;
	ListTexture::TT_OUT_COIN_SPRITEPERROW				= 2;
	ListTexture::TT_OUT_COIN_ANIMATED_RATE				= 100;

	ListTexture::TT_MARIO_KID							= GlobalHandler::_directX->LoadTextureFromFile("Media\\mario.bmp", 0);;
	ListTexture::TT_MARIO_KID_WIDTH						= 31;
	ListTexture::TT_MARIO_KID_HEIGHT					= 31;
	ListTexture::TT_MARIO_KID_COUNT						= 7;
	ListTexture::TT_MARIO_KID_SPRITEPERROW				= 2;
	ListTexture::TT_MARIO_KID_ANIMATED_RATE				= 25; // 200
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

	ListTexture::TT_MARIO_ADULT							= GlobalHandler::_directX->LoadTextureFromFile("Media\\mario_growup.bmp", 0);
	ListTexture::TT_MARIO_ADULT_WIDTH					= 31;
	ListTexture::TT_MARIO_ADULT_HEIGHT					= 60;
	ListTexture::TT_MARIO_ADULT_COUNT					= 16;
	ListTexture::TT_MARIO_ADULT_SPRITEPERROW			= 3;
	ListTexture::TT_MARIO_ADULT_ANIMATED_RATE			= 25; //200
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


	ListTexture::TT_HARD_BRICK							= GlobalHandler::_directX->LoadTextureFromFile("Media\\hardbrick.bmp",0);
	ListTexture::TT_HARD_BRICK_WIDTH					= 32;
	ListTexture::TT_HARD_BRICK_HEIGHT					= 32;
	ListTexture::TT_HARD_BRICK_COUNT					= 1;
	ListTexture::TT_HARD_BRICK_SPRITEPERROW				= 1;

	ListTexture::TT_BRICK								= GlobalHandler::_directX->LoadTextureFromFile("Media\\brick.bmp",0);
	ListTexture::TT_BRICK_WIDTH							= 32;
	ListTexture::TT_BRICK_HEIGHT						= 32;
	ListTexture::TT_BRICK_COUNT							= 1;
	ListTexture::TT_BRICK_SPRITEPERROW					= 1;

	ListTexture::TT_BRICK_BREAK_LEFT					= GlobalHandler::_directX->LoadTextureFromFile("Media\\brick_broke_left.bmp", 0);
	ListTexture::TT_BRICK_BREAK_LEFT_WIDTH				= 16;
	ListTexture::TT_BRICK_BREAK_LEFT_HEIGHT				= 16;
	ListTexture::TT_BRICK_BREAK_LEFT_COUNT				= 4;
	ListTexture::TT_BRICK_BREAK_LEFT_SPRITEPERROW		= 4;
	ListTexture::TT_BRICK_BREAK_LEFT_ANIMATED_RATE		= 70;

	ListTexture::TT_BRICK_BONUS							= GlobalHandler::_directX->LoadTextureFromFile("Media\\brick_bonus.png", 0);
	ListTexture::TT_BRICK_BONUS_WIDTH					= 32;
	ListTexture::TT_BRICK_BONUS_HEIGHT					= 32;
	ListTexture::TT_BRICK_BONUS_COUNT					= 3;
	ListTexture::TT_BRICK_BONUS_SPRITEPERROW			= 3;
	ListTexture::TT_BRICK_BONUS_ANIMATED_RATE			= 130;

	ListTexture::TT_BONUS_MUSHROOM						= GlobalHandler::_directX->LoadTextureFromFile("Media\\bonus_mushroom.bmp", 0);
	ListTexture::TT_BONUS_MUSHROOM_WIDTH				= 32;
	ListTexture::TT_BONUS_MUSHROOM_HEIGHT				= 32;
	ListTexture::TT_BONUS_MUSHROOM_COUNT				= 2;
	ListTexture::TT_BONUS_MUSHROOM_SPRITEPERROW			= 2;

	ListTexture::TT_EMPTY_BRICK							= GlobalHandler::_directX->LoadTextureFromFile("Media\\empty_brick.bmp", 0);

	ListTexture::TT_FLOWER								= GlobalHandler::_directX->LoadTextureFromFile("Media\\sprite_flower.bmp", 0);
	ListTexture::TT_FLOWER_WIDTH						= 32;
	ListTexture::TT_FLOWER_HEIGHT						= 32;
	ListTexture::TT_FLOWER_COUNT						= 4;
	ListTexture::TT_FLOWER_SPRITEPERROW					= 4;
	ListTexture::TT_FLOWER_ANIMATED_RATE				= 200;

	ListTexture::TT_STAR								= GlobalHandler::_directX->LoadTextureFromFile("Media\\bonus_star.png", 0);
	ListTexture::TT_STAR_WIDTH							= 32;
	ListTexture::TT_STAR_HEIGHT							= 32;
	ListTexture::TT_STAR_COUNT							= 4;
	ListTexture::TT_STAR_SPRITEPERROW					= 4;
	ListTexture::TT_STARR_ANIMATED_RATE					= 80;

	ListTexture::TT_COIN_PICK							= GlobalHandler::_directX->LoadTextureFromFile("Media\\coin_pickup.bmp",0);
	ListTexture::TT_COIN_PICK_WIDTH						= 32;
	ListTexture::TT_COIN_PICK_HEIGHT					= 32;
	ListTexture::TT_COIN_PICK_COUNT						= 4;
	ListTexture::TT_COIN_PICK_SPRITEPERROW				= 4;
	ListTexture::TT_COIN_PICK_ANIMATED_RATE				= 100;


	//text
	ListTexture::TT_MARIO_TEXT							= GlobalHandler::_directX->LoadTextureFromFile("Media\\text_mario.png",0);
	ListTexture::TT_MARIO_TEXT_WIDTH					= 95;
	ListTexture::TT_MARIO_TEXT_HEIGHT					= 16;


	ListTexture::TT_COIN_TEXT							= GlobalHandler::_directX->LoadTextureFromFile("Media\\coin_count.png",0);
	ListTexture::TT_COIN_TEXT_WIDTH						= 27;
	ListTexture::TT_COIN_TEXT_HEIGHT					= 16;

	ListTexture::TT_WORLD_TEXT							= GlobalHandler::_directX->LoadTextureFromFile("Media\\text_world.bmp",0);
	ListTexture::TT_WORLD_TEXT_WIDTH					= 79;
	ListTexture::TT_WORLD_TEXT_HEIGHT					= 16;
	
	ListTexture::TT_TIME_TEXT							= GlobalHandler::_directX->LoadTextureFromFile("Media\\text_time.bmp",0);
	ListTexture::TT_TIME_TEXT_WIDTH						= 64;
	ListTexture::TT_TIME_TEXT_HEIGHT					= 16;

	ListTexture::TT_NUMBER_TEXT							= GlobalHandler::_directX->LoadTextureFromFile("Media\\number.png",0);
	ListTexture::TT_NUMBER_TEXT_WIDTH					= 15;
	ListTexture::TT_NUMBER_TEXT_HEIGHT					= 16;
	ListTexture::TT_NUMBER_TEXT_COUNT					= 11;
	ListTexture::TT_NUMBER_TEXT_SPRITEPERROW			= 11;
}