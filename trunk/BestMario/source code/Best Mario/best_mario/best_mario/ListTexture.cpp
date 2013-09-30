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
}