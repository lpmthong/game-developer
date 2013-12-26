#include "MushroomEnemy.h"
#include "GlobalHandler.h"
#include "ListTexture.h"
#include "Define.h"

MushroomEnemy::MushroomEnemy(void){}

MushroomEnemy::~MushroomEnemy(void){}

MushroomEnemy::MushroomEnemy(int left, int top, int iid){

	sprite = new Sprite(ListTexture::TT_MUSHROOM_ENEMY, ListTexture::TT_MUSHROOM_ENEMY_WIDTH, ListTexture::TT_MUSHROOM_ENEMY_HEIGHT,
						ListTexture::TT_MUSHROOM_ENEMY_COUNT, ListTexture::TT_MUSHROOM_ENEMY_SPRITEPERROW);

	id = iid;
	isKind = MUSHROOM_ENEMY;
	width = ListTexture::TT_MUSHROOM_ENEMY_WIDTH;
	height = ListTexture::TT_MUSHROOM_ENEMY_HEIGHT;

	UpdateRect(left, top , ListTexture::TT_MUSHROOM_ENEMY_WIDTH, ListTexture::TT_MUSHROOM_ENEMY_HEIGHT);

	animatedRate = ListTexture::TT_MUSHROOM_ENEMY_ANIMATED_RATE;
	lastUpdate = GetTickCount();
	lastAnimate = GetTickCount();

	isSolid = true;

	Vx = -0.1f;
	Vy = 0;
	Vy_old = 0.05f;

	deathTime = 1500;
	preparing = false;

	alive = ALIVE;
	start = false;
}

void MushroomEnemy::MoveToHell(){
	__super::MoveToHell();
	
	Vx = 0;
	Vy_old = 0.4f;
}

void MushroomEnemy::UpdateSprite(){
	DWORD now = GetTickCount();

	if (now - lastAnimate > animatedRate)
	{
		if (alive == DYING2)
		{
			sprite->Next(2,2);
			return;
		}
		sprite->Next(0,1);
		lastAnimate = now;
	}
}