#include "MushroomEnemy.h"
#include "ListTexture.h"

MushroomEnemy::MushroomEnemy(void)
{
}

MushroomEnemy::MushroomEnemy( int left, int top ) : Enemy()
{
	sprite = new Sprite(ListTexture::TT_MUSHROOM_ENEMY,
						ListTexture::TT_MUSHROOM_ENEMY_WIDTH,	
						ListTexture::TT_MUSHROOM_ENEMY_HEIGHT,
						ListTexture::TT_MUSHROOM_ENEMY_COUNT,		
						ListTexture::TT_MUSHROOM_ENEMY_SPRITEPERROW);


	width = ListTexture::TT_MUSHROOM_ENEMY_WIDTH;
	height = ListTexture::TT_MUSHROOM_ENEMY_HEIGHT;
	UpdateRect(left, top, ListTexture::TT_MUSHROOM_ENEMY_WIDTH, ListTexture::TT_MUSHROOM_ENEMY_HEIGHT);
//	map_level = 2;

	animatedRate = ListTexture::TT_CLOUD_ANIMATED_RATE;
	lastAnimate = GetTickCount();
	lastUpdate = GetTickCount();

	iKind = MUSHROOM_ENEMY;
	isSolid = true;

	fYOldVelocity = 0;
	fXOldVelocity = -4;

	alive = ALIVE;

	deathTime = 1500;

	preparing = false;

	//Just init it, dont let it start to do anything.
	start = false;

}

MushroomEnemy::~MushroomEnemy(void)
{
}

void MushroomEnemy::MoveToHell()
{
	__super::MoveToHell();

	fYOldVelocity = 50;
	fYVelocity = 0;
	fXOldVelocity = 0;

	trace(L"void MushroomEnemy::MoveToHell()");
}

void MushroomEnemy::UpdateSprite()
{
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

//	trace(L"void MushroomEnemy::UpdateSprite() %d", recRealArea.bottom);
}
