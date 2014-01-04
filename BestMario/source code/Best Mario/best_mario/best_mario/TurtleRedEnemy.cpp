#include "TurtleRedEnemy.h"
#include "GlobalHandler.h"


TurtleRedEnemy::TurtleRedEnemy(void){}

TurtleRedEnemy::~TurtleRedEnemy(void){}

TurtleRedEnemy::TurtleRedEnemy(int left, int top, int iid){

	sprite = new Sprite();

	old_Vx = -0.15f;	
	setAlive();
	id = iid;
	UpdateRect(left, top);
	lastAnimate = GetTickCount();
	lastUpdate = GetTickCount();

	isSolid = true;
	deathTime = 1500;
	preparing = false;

	start = false;
}

void TurtleRedEnemy::setAlive(){

	__super::setAlive();

	sprite->Reset(ListTexture::TT_RED_TURTLE_ENEMY, ListTexture::TT_RED_TURTLE_ENEMY_WIDTH, ListTexture::TT_RED_TURTLE_ENEMY_HEIGHT,
		ListTexture::TT_RED_TURTLE_ENEMY_COUNT, ListTexture::TT_RED_TURTLE_ENEMY_SPRITEPERROW);

	animatedRate = ListTexture::TT_RED_TURTLE_ENEMY_ANIMATED_RATE;

	width = ListTexture::TT_RED_TURTLE_ENEMY_WIDTH;
	height = ListTexture::TT_RED_TURTLE_ENEMY_HEIGHT;

	isKind = RED_TURTLE;

}

void TurtleRedEnemy::setDeath(){

	__super::setDeath();

	sprite->Reset(ListTexture::TT_RED_TURTLE_DEATH, ListTexture::TT_RED_TURTLE_DEATH_WIDTH, ListTexture::TT_RED_TURTLE_DEATH_HEIGHT,
		ListTexture::TT_RED_TURTLE_DEATH_COUNT, ListTexture::TT_RED_TURTLE_DEATH_SPRITEPERROW);

	animatedRate = ListTexture::TT_RED_TURTLE_DEATH_ANIMATED_RATE;

	width = ListTexture::TT_RED_TURTLE_DEATH_WIDTH;
	height = ListTexture::TT_RED_TURTLE_DEATH_HEIGHT;

	isKind = RED_TURTLE_DEATH;
}

void TurtleRedEnemy::UpdateSprite(){

	if (stopUpdateSprite)
		return;

	DWORD now = GetTickCount();
	if (now - lastAnimate > animatedRate)
	{		
		if (isKind == RED_TURTLE)
		{
			if (Vx > 0)
				sprite->Next(0,1);
			else
				sprite->Next(2,3);
		}
		if (isKind == RED_TURTLE_DEATH)
		{
			sprite->Next(0,2);
		}
		if (alive == DYING2)
		{
			setDeath();
			sprite->Next(3,3);
		}
		lastAnimate = now;
	}

}