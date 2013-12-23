#pragma once
#include <d3d9.h>
#include <d3dx9.h>

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

	static LPDIRECT3DTEXTURE9	TT_PIPE_1;
	static int					TT_PIPE_1_WIDTH;
	static int					TT_PIPE_1_HEIGHT;
	static int					TT_PIPE_1_COUNT;
	static int					TT_PIPE_1_SPRITEPERROW;

	static LPDIRECT3DTEXTURE9	TT_PIPE_2;
	static int					TT_PIPE_2_WIDTH;
	static int					TT_PIPE_2_HEIGHT;
	static int					TT_PIPE_2_COUNT;
	static int					TT_PIPE_2_SPRITEPERROW;

	static LPDIRECT3DTEXTURE9	TT_PIPE_3;
	static int					TT_PIPE_3_WIDTH;
	static int					TT_PIPE_3_HEIGHT;
	static int					TT_PIPE_3_COUNT;
	static int					TT_PIPE_3_SPRITEPERROW;


	//Tien khong nam trong gach
	static LPDIRECT3DTEXTURE9	TT_OUT_COIN;
	static int					TT_OUT_COIN_WIDTH;
	static int					TT_OUT_COIN_HEIGHT;
	static int					TT_OUT_COIN_COUNT;
	static int					TT_OUT_COIN_SPRITEPERROW;
	static int					TT_OUT_COIN_ANIMATED_RATE;

	//Mario
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

	static LPDIRECT3DTEXTURE9	TT_MARIO_ADULT;
	static int					TT_MARIO_ADULT_WIDTH;
	static int					TT_MARIO_ADULT_HEIGHT;
	static int					TT_MARIO_ADULT_COUNT;
	static int					TT_MARIO_ADULT_SPRITEPERROW;
	static int					TT_MARIO_ADULT_ANIMATED_RATE;
	static int					TT_MARIO_ADULT_MOVING_LEFT_START;
	static int					TT_MARIO_ADULT_MOVING_LEFT_END;
	static int					TT_MARIO_ADULT_MOVING_RIGHT_START;
	static int					TT_MARIO_ADULT_MOVING_RIGHT_END;
	static int					TT_MARIO_ADULT_JUMPING_LEFT_START;
	static int					TT_MARIO_ADULT_JUMPING_LEFT_END;
	static int					TT_MARIO_ADULT_JUMPING_RIGHT_START;
	static int					TT_MARIO_ADULT_JUMPING_RIGHT_END;
	static int					TT_MARIO_GUN_MOVING_LEFT_START;
	static int					TT_MARIO_GUN_MOVING_LEFT_END;
	static int					TT_MARIO_GUN_MOVING_RIGHT_START;
	static int					TT_MARIO_GUN_MOVING_RIGHT_END;
	static int					TT_MARIO_GUN_JUMPING_LEFT_START;
	static int					TT_MARIO_GUN_JUMPING_LEFT_END;
	static int					TT_MARIO_GUN_JUMPING_RIGHT_START;
	static int					TT_MARIO_GUN_JUMPING_RIGHT_END;

	//Hard Brick
	static LPDIRECT3DTEXTURE9	TT_HARD_BRICK;
	static int					TT_HARD_BRICK_WIDTH;
	static int					TT_HARD_BRICK_HEIGHT;
	static int					TT_HARD_BRICK_COUNT;
	static int					TT_HARD_BRICK_SPRITEPERROW;

	//Brick
	static LPDIRECT3DTEXTURE9	TT_BRICK;
	static int					TT_BRICK_WIDTH;
	static int					TT_BRICK_HEIGHT;
	static int					TT_BRICK_COUNT;
	static int					TT_BRICK_SPRITEPERROW;

	//Brick Break
	static LPDIRECT3DTEXTURE9	TT_BRICK_BREAK_LEFT;
	static int					TT_BRICK_BREAK_LEFT_WIDTH;
	static int					TT_BRICK_BREAK_LEFT_HEIGHT;
	static int					TT_BRICK_BREAK_LEFT_COUNT;
	static int					TT_BRICK_BREAK_LEFT_SPRITEPERROW;
	static int					TT_BRICK_BREAK_LEFT_ANIMATED_RATE;

	//Bonus Brick
	static LPDIRECT3DTEXTURE9	TT_BRICK_BONUS;
	static int					TT_BRICK_BONUS_WIDTH;
	static int					TT_BRICK_BONUS_HEIGHT;
	static int					TT_BRICK_BONUS_COUNT;
	static int					TT_BRICK_BONUS_SPRITEPERROW;
	static int					TT_BRICK_BONUS_ANIMATED_RATE;

	static LPDIRECT3DTEXTURE9	TT_BONUS_MUSHROOM;			
	static int					TT_BONUS_MUSHROOM_WIDTH;		
	static int					TT_BONUS_MUSHROOM_HEIGHT;		
	static int					TT_BONUS_MUSHROOM_COUNT;		
	static int					TT_BONUS_MUSHROOM_SPRITEPERROW;	

	static LPDIRECT3DTEXTURE9	TT_EMPTY_BRICK;

	static LPDIRECT3DTEXTURE9	TT_FLOWER;
	static int					TT_FLOWER_WIDTH;
	static int					TT_FLOWER_HEIGHT;
	static int					TT_FLOWER_COUNT;
	static int					TT_FLOWER_SPRITEPERROW;
	static int					TT_FLOWER_ANIMATED_RATE;

	static LPDIRECT3DTEXTURE9	TT_STAR;
	static int					TT_STAR_WIDTH;
	static int					TT_STAR_HEIGHT;
	static int					TT_STAR_COUNT;
	static int					TT_STAR_SPRITEPERROW;
	static int					TT_STARR_ANIMATED_RATE;

	static LPDIRECT3DTEXTURE9	TT_COIN_PICK;
	static int					TT_COIN_PICK_WIDTH;
	static int					TT_COIN_PICK_HEIGHT;
	static int					TT_COIN_PICK_COUNT;
	static int					TT_COIN_PICK_SPRITEPERROW;
	static int					TT_COIN_PICK_ANIMATED_RATE;

public:
	static void CreateAllTexture();
	ListTexture(void);
	~ListTexture(void);
};
