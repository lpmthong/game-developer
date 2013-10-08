#include "ListTexture.h"

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

	ListTexture::TT_OUT_COIN							= GlobalHandler::_directX->LoadTextureFromFile("Media\\coin.bmp",0);
	ListTexture::TT_OUT_COIN_WIDTH						= 19;
	ListTexture::TT_OUT_COIN_HEIGHT						= 29;
	ListTexture::TT_OUT_COIN_COUNT						= 2;
	ListTexture::TT_OUT_COIN_SPRITEPERROW				= 2;
	ListTexture::TT_OUT_COIN_ANIMATED_RATE				= 100;

	ListTexture::TT_MARIO_KID							= GlobalHandler::_directX->LoadTextureFromFile("Media\\mario.bmp", 0);;
	ListTexture::TT_MARIO_KID_WIDTH						= 32;
	ListTexture::TT_MARIO_KID_HEIGHT					= 32;
	ListTexture::TT_MARIO_KID_COUNT						= 7;
	ListTexture::TT_MARIO_KID_SPRITEPERROW				= 2;
	ListTexture::TT_MARIO_KID_ANIMATED_RATE				= 30; // 200
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
}