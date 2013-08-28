#pragma once

#include "GlobalHandler.h"

class ListTexture
{
public:
//	static LPDIRECT3DTEXTURE9	TT_MARIO_KID;

	static LPDIRECT3DTEXTURE9	TT_BRICK;
	static int					TT_BRICK_WIDTH;
	static int					TT_BRICK_HEIGHT;
	static int					TT_BRICK_COUNT;
	static int					TT_BRICK_SPRITEPERROW;

	static LPDIRECT3DTEXTURE9	TT_CLOUD;
	static int					TT_CLOUD_WIDTH;
	static int					TT_CLOUD_HEIGHT;
	static int					TT_CLOUD_COUNT;
	static int					TT_CLOUD_SPRITEPERROW;
	static int					TT_CLOUD_ANIMATED_RATE;

	static LPDIRECT3DTEXTURE9	TT_GRASS;
	static int					TT_GRASS_WIDTH;
	static int					TT_GRASS_HEIGHT;
	static int					TT_GRASS_COUNT;
	static int					TT_GRASS_SPRITEPERROW;
	static int					TT_GRASS_ANIMATED_RATE;

	static LPDIRECT3DTEXTURE9	TT_FENCE;
	static int					TT_FENCE_WIDTH;
	static int					TT_FENCE_HEIGHT;
	static int					TT_FENCE_COUNT;
	static int					TT_FENCE_SPRITEPERROW;

	static LPDIRECT3DTEXTURE9	TT_MUSHROOM_ENEMY;
	static int					TT_MUSHROOM_ENEMY_WIDTH;
	static int					TT_MUSHROOM_ENEMY_HEIGHT;
	static int					TT_MUSHROOM_ENEMY_COUNT;
	static int					TT_MUSHROOM_ENEMY_SPRITEPERROW;
	static int					TT_MUSHROOM_ENEMY_ANIMATED_RATE;

	static LPDIRECT3DTEXTURE9	TT_GROUND;
	static int					TT_GROUND_WIDTH;
	static int					TT_GROUND_HEIGHT;
	static int					TT_GROUND_COUNT;
	static int					TT_GROUND_SPRITEPERROW;

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


	static LPDIRECT3DTEXTURE9	TT_BRICK_BREAK_LEFT;
	static int					TT_BRICK_BREAK_LEFT_WIDTH;
	static int					TT_BRICK_BREAK_LEFT_HEIGHT;
	static int					TT_BRICK_BREAK_LEFT_COUNT;
	static int					TT_BRICK_BREAK_LEFT_SPRITEPERROW;
	static int					TT_BRICK_BREAK_LEFT_ANIMATED_RATE;

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

	static LPDIRECT3DTEXTURE9	TT_BULLET;
	static int					TT_BULLET_WIDTH;
	static int					TT_BULLET_HEIGHT;
	static int					TT_BULLET_COUNT;
	static int					TT_BULLET_SPRITEPERROW;
	static int					TT_BULLET_ANIMATED_RATE;

	static LPDIRECT3DTEXTURE9	TT_TURLE_ENEMY;
	static int					TT_TURLE_ENEMY_WIDTH;					
	static int					TT_TURLE_ENEMY_HEIGHT;					
	static int					TT_TURLE_ENEMY_COUNT;					
	static int					TT_TURLE_ENEMY_SPRITEPERROW;			
	static int					TT_TURLE_ENEMY_ANIMATED_RATE;			

	static LPDIRECT3DTEXTURE9	TT_TURLE_DEATH;
	static int					TT_TURLE_DEATH_WIDTH;					
	static int					TT_TURLE_DEATH_HEIGHT;					
	static int					TT_TURLE_DEATH_COUNT;					
	static int					TT_TURLE_DEATH_SPRITEPERROW;			
	static int					TT_TURLE_DEATH_ANIMATED_RATE;			

	static LPDIRECT3DTEXTURE9	TT_MARIO_TEXT;
	static int					TT_MARIO_TEXT_WIDTH;
	static int					TT_MARIO_TEXT_HEIGHT;

	static LPDIRECT3DTEXTURE9	TT_GAMEOVER_TEXT;
	static int					TT_GAMEOVER_TEXT_WIDTH;
	static int					TT_GAMEOVER_TEXT_HEIGHT;

	static LPDIRECT3DTEXTURE9	TT_TIME_TEXT;
	static int					TT_TIME_TEXT_WIDTH;
	static int					TT_TIME_TEXT_HEIGHT;

	static LPDIRECT3DTEXTURE9	TT_WORLD_TEXT;
	static int					TT_WORLD_TEXT_WIDTH;
	static int					TT_WORLD_TEXT_HEIGHT;

	static LPDIRECT3DTEXTURE9	TT_COIN_COUNT;
	static int					TT_COIN_COUNT_WIDTH;
	static int					TT_COIN_COUNT_HEIGHT;

	static LPDIRECT3DTEXTURE9	TT_NUMBER;
	static int					TT_NUMBER_WIDTH;
	static int					TT_NUMBER_HEIGHT;
	static int					TT_NUMBER_COUNT;
	static int					TT_NUMBER_SPRITEPERROW;

	static LPDIRECT3DTEXTURE9	TT_COIN_PICK;
	static int					TT_COIN_PICK_WIDTH;
	static int					TT_COIN_PICK_HEIGHT;
	static int					TT_COIN_PICK_COUNT;
	static int					TT_COIN_PICK_SPRITEPERROW;
	static int					TT_COIN_PICK_ANIMATED_RATE;

	static LPDIRECT3DTEXTURE9	TT_OUT_COIN;
	static int					TT_OUT_COIN_WIDTH;
	static int					TT_OUT_COIN_HEIGHT;
	static int					TT_OUT_COIN_COUNT;
	static int					TT_OUT_COIN_SPRITEPERROW;
	static int					TT_OUT_COIN_ANIMATED_RATE;

	static LPDIRECT3DTEXTURE9	TT_HARD_BRICK;
	static int					TT_HARD_BRICK_WIDTH;
	static int					TT_HARD_BRICK_HEIGHT;
	static int					TT_HARD_BRICK_COUNT;
	static int					TT_HARD_BRICK_SPRITEPERROW;

	static LPDIRECT3DTEXTURE9	TT_PIRHANA_PLANT;
	static int					TT_PIRHANA_PLANT_WIDTH;
	static int					TT_PIRHANA_PLANT_HEIGHT;
	static int					TT_PIRHANA_PLANT_COUNT;
	static int					TT_PIRHANA_PLANT_SPRITEPERROW;
	static int					TT_PIRHANA_PLANT_ANIMATED_RATE;

	static LPDIRECT3DTEXTURE9	TT_END_MAP;
	static int					TT_END_MAP_WIDTH;
	static int					TT_END_MAP_HEIGHT;
	static int					TT_END_MAP_COUNT;
	static int					TT_END_MAP_SPRITEPERROW;

	static LPDIRECT3DTEXTURE9	TT_MENU_BACKGROUND;
	static LPDIRECT3DTEXTURE9	TT_MENU_OPTIONS;

	static LPDIRECT3DTEXTURE9	TT_MOUNTAIN;
	static int					TT_MOUNTAIN_WIDTH;
	static int					TT_MOUNTAIN_HEIGHT;
	static int					TT_MOUNTAIN_COUNT;
	static int					TT_MOUNTAIN_SPRITEPERROW;

	static LPDIRECT3DTEXTURE9	TT_HIGH_TREE;
	static int					TT_HIGH_TREE_WIDTH;
	static int					TT_HIGH_TREE_HEIGHT;
	static int					TT_HIGH_TREE_COUNT;
	static int					TT_HIGH_TREE_SPRITEPERROW;

	static LPDIRECT3DTEXTURE9	TT_LOW_TREE;
	static int					TT_LOW_TREE_WIDTH;
	static int					TT_LOW_TREE_HEIGHT;
	static int					TT_LOW_TREE_COUNT;
	static int					TT_LOW_TREE_SPRITEPERROW;

	static LPDIRECT3DTEXTURE9	TT_OPTION;

	static LPDIRECT3DTEXTURE9	TT_CHANGE_MAP;
	static LPDIRECT3DTEXTURE9	TT_WORLD;
	static int					TT_WORLD_WIDTH;
	static int					TT_WORLD_HEIGHT;
	static LPDIRECT3DTEXTURE9	TT_WORLD_NUMBER;
	static int					TT_WORLD_NUMBER_WIDTH;
	static int					TT_WORLD_NUMBER_HEIGHT;
	static int					TT_WORLD_NUMBER_COUNT;
	static int					TT_WORLD_NUMBER_SPRITEPERROW;

	static LPDIRECT3DTEXTURE9	TT_CROSS;
	static int					TT_CROSS_WIDTH;
	static int					TT_CROSS_HEIGHT;
	static LPDIRECT3DTEXTURE9	TT_FALLING_CROSS;

	static LPDIRECT3DTEXTURE9	TT_STARTGAMEOPTION_BACKGROUND;

	static LPDIRECT3DTEXTURE9	TT_RED_TURLE_ENEMY;
	static int					TT_RED_TURLE_ENEMY_WIDTH;					
	static int					TT_RED_TURLE_ENEMY_HEIGHT;					
	static int					TT_RED_TURLE_ENEMY_COUNT;					
	static int					TT_RED_TURLE_ENEMY_SPRITEPERROW;			
	static int					TT_RED_TURLE_ENEMY_ANIMATED_RATE;			

	static LPDIRECT3DTEXTURE9	TT_RED_TURLE_DEATH;
	static int					TT_RED_TURLE_DEATH_WIDTH;					
	static int					TT_RED_TURLE_DEATH_HEIGHT;					
	static int					TT_RED_TURLE_DEATH_COUNT;					
	static int					TT_RED_TURLE_DEATH_SPRITEPERROW;			
	static int					TT_RED_TURLE_DEATH_ANIMATED_RATE;

	static LPDIRECT3DTEXTURE9	TT_GROUND_MUSHROOM;
	static int					TT_GROUND_MUSHROOM_WIDTH;
	static int					TT_GROUND_MUSHROOM_HEIGHT;
	static int					TT_GROUND_MUSHROOM_COUNT;
	static int					TT_GROUND_MUSHROOM_SPRITEPERROW;

	static LPDIRECT3DTEXTURE9	TT_GROUND_UNDER_MUSHROOM;
	static int					TT_GROUND_UNDER_MUSHROOM_WIDTH;
	static int					TT_GROUND_UNDER_MUSHROOM_HEIGHT;
	static int					TT_GROUND_UNDER_MUSHROOM_COUNT;
	static int					TT_GROUND_UNDER_MUSHROOM_SPRITEPERROW;

	static LPDIRECT3DTEXTURE9	TT_STAR;
	static int					TT_STAR_WIDTH;
	static int					TT_STAR_HEIGHT;
	static int					TT_STAR_COUNT;
	static int					TT_STAR_SPRITEPERROW;
	static int					TT_STARR_ANIMATED_RATE;

public:
	static void CreateAllTexture();
	ListTexture(void);
	~ListTexture(void);
};
