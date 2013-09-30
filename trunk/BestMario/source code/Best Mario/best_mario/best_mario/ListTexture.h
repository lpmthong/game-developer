#pragma once
#include "GlobalHandler.h"

class ListTexture{
public:

	//May(Cloud)
	static LPDIRECT3DTEXTURE9	TT_CLOUD;
	static int					TT_CLOUD_WIDTH;
	static int					TT_CLOUD_HEIGHT;
	static int					TT_CLOUD_COUNT;
	static int					TT_CLOUD_SPRITEPERROW;
	static int					TT_CLOUD_ANIMATED_RATE;

	//Hang rao(Fence)
	static LPDIRECT3DTEXTURE9	TT_FENCE;
	static int					TT_FENCE_WIDTH;
	static int					TT_FENCE_HEIGHT;
	static int					TT_FENCE_COUNT;
	static int					TT_FENCE_SPRITEPERROW;

	//Co (grass)
	static LPDIRECT3DTEXTURE9	TT_GRASS;
	static int					TT_GRASS_WIDTH;
	static int					TT_GRASS_HEIGHT;
	static int					TT_GRASS_COUNT;
	static int					TT_GRASS_SPRITEPERROW;
	static int					TT_GRASS_ANIMATED_RATE;

	//Mat dat (ground)
	static LPDIRECT3DTEXTURE9	TT_GROUND;
	static int					TT_GROUND_WIDTH;
	static int					TT_GROUND_HEIGHT;
	static int					TT_GROUND_COUNT;
	static int					TT_GROUND_SPRITEPERROW;

	//Cay cao
	static LPDIRECT3DTEXTURE9	TT_HIGH_TREE;
	static int					TT_HIGH_TREE_WIDTH;
	static int					TT_HIGH_TREE_HEIGHT;
	static int					TT_HIGH_TREE_COUNT;
	static int					TT_HIGH_TREE_SPRITEPERROW;

	//Cay thap
	static LPDIRECT3DTEXTURE9	TT_LOW_TREE;
	static int					TT_LOW_TREE_WIDTH;
	static int					TT_LOW_TREE_HEIGHT;
	static int					TT_LOW_TREE_COUNT;
	static int					TT_LOW_TREE_SPRITEPERROW;

	//Nui
	static LPDIRECT3DTEXTURE9	TT_MOUNTAIN;
	static int					TT_MOUNTAIN_WIDTH;
	static int					TT_MOUNTAIN_HEIGHT;
	static int					TT_MOUNTAIN_COUNT;
	static int					TT_MOUNTAIN_SPRITEPERROW;

	//Ong nuoc
	static LPDIRECT3DTEXTURE9	TT_PIPE_CAP;
	static int					TT_PIPE_CAP_WIDTH;
	static int					TT_PIPE_CAP_HEIGHT;
	static int					TT_PIPE_CAP_COUNT;
	static int					TT_PIPE_CAP_SPRITEPERROW;

	static LPDIRECT3DTEXTURE9	TT_PIPE_BODY;
	static int					TT_PIPE_BODY_WIDTH;
	static int					TT_PIPE_BODY_HEIGHT;
	static int					TT_PIPE_BODY_COUNT;
	static int					TT_PIPE_BODY_SPRITEPERROW;

public:
	static void CreateAllTexture();
	ListTexture(void);
	~ListTexture(void);
};
