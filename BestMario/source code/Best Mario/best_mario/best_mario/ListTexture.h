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

	//Tien khong nam trong gach
	static LPDIRECT3DTEXTURE9	TT_OUT_COIN;
	static int					TT_OUT_COIN_WIDTH;
	static int					TT_OUT_COIN_HEIGHT;
	static int					TT_OUT_COIN_COUNT;
	static int					TT_OUT_COIN_SPRITEPERROW;
	static int					TT_OUT_COIN_ANIMATED_RATE;

	//Mario nho
	static LPDIRECT3DTEXTURE9	TT_MARIO_KID;
	static int					TT_MARIO_KID_WIDTH;
	static int					TT_MARIO_KID_HEIGHT;
	static int					TT_MARIO_KID_COUNT;
	static int					TT_MARIO_KID_SPRITEPERROW;
	static int					TT_MARIO_KID_ANIMATED_RATE;
	static int					TT_MARIO_KID_MOVING_LEFT_START;
	static int					TT_MARIO_KID_MOVING_LEFT_END;
	static int					TT_MARIO_KID_MOVING_RIGHT_START;
	static int					TT_MARIO_KID_MOVING_RIGHT_END;
	static int					TT_MARIO_KID_JUMPING_LEFT_START;
	static int					TT_MARIO_KID_JUMPING_LEFT_END;
	static int					TT_MARIO_KID_JUMPING_RIGHT_START;
	static int					TT_MARIO_KID_JUMPING_RIGHT_END;
	static int					TT_MARIO_KID_DEATH_START;
	static int					TT_MARIO_KID_DEATH_END;

public:
	static void CreateAllTexture();
	ListTexture(void);
	~ListTexture(void);
};
