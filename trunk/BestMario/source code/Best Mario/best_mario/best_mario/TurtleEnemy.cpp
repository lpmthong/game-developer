#include "TurtleEnemy.h"
#include "GlobalHandler.h"
#include "ListSound.h"
#include "ListTexture.h"
#include "Define.h"

TurtleEnemy::TurtleEnemy(void){}

TurtleEnemy::~TurtleEnemy(void){}

TurtleEnemy::TurtleEnemy(int left, int top, int iid){

	sprite = new Sprite();
	
	old_Vx = -0.15f;	
	setAlive();

	UpdateRect(left, top);
	lastAnimate = GetTickCount();
	lastUpdate = GetTickCount();
	
	isSolid = true;
	deathTime = 1500;
	preparing = false;

	start = false;
}

void TurtleEnemy::setAlive(){

	sprite->Reset(ListTexture::TT_TURTLE_ENEMY, ListTexture::TT_TURTLE_ENEMY_WIDTH, ListTexture::TT_TURTLE_ENEMY_HEIGHT,
					ListTexture::TT_TURTLE_ENEMY_COUNT, ListTexture::TT_TURTLE_ENEMY_SPRITEPERROW);

	animatedRate = ListTexture::TT_TURTLE_ENEMY_ANIMATED_RATE;

	width = ListTexture::TT_TURTLE_ENEMY_WIDTH;
	height = ListTexture::TT_TURTLE_ENEMY_HEIGHT;

	isKind = TURTLE;

	Vx = old_Vx;
	Vy_old = 0.05f;

	alive = ALIVE;

	stopUpdateSprite = false;

	moving = true;

	onGround = false;
}

void TurtleEnemy::setDeath(){
	sprite->Reset(ListTexture::TT_TURTLE_DEATH, ListTexture::TT_TURTLE_DEATH_WIDTH, ListTexture::TT_TURTLE_DEATH_HEIGHT,
		ListTexture::TT_TURTLE_DEATH_COUNT, ListTexture::TT_TURTLE_DEATH_SPRITEPERROW);

	animatedRate = ListTexture::TT_TURTLE_DEATH_ANIMATED_RATE;

	width = ListTexture::TT_TURTLE_DEATH_WIDTH;
	height = ListTexture::TT_TURTLE_DEATH_HEIGHT;

	isKind = TURTLEDEATH;

	sprite->setIndex(1);

	UpdateRect(rectDraw.left, rectDraw.top + 30);

	beginDeath = GetTickCount();
	timeInDeath = 5000;
	stopUpdateSprite = true;

	old_Vx = Vx;
	Vx = Vy = 0;
	Vy_old = 0.05;

	onGround = false;
	moving = false;
}

void TurtleEnemy::UpdateSprite(){

	if (stopUpdateSprite)
		return;

	DWORD now = GetTickCount();
	if (now - lastAnimate > animatedRate)
	{		
		if (isKind == TURTLE)
		{
			if (Vx > 0)
				sprite->Next(0,1);
			else
				sprite->Next(2,3);
		}
		if (isKind == TURTLEDEATH)
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

void TurtleEnemy::UpdateSpriteDying(){
		
}

void TurtleEnemy::ProcessDying(){
	setDeath();
}

void TurtleEnemy::MoveToHell(){

	__super::MoveToHell();
	Vx = 0;
	Vy_old = 0.4f;
}

void TurtleEnemy::setDeathMoving(){

	if (rectDraw.left + width / 2 > GlobalHandler::player->rectDraw.left + GlobalHandler::player->width / 2)
	{
		Vx = 0.3f;
		UpdateRect(GlobalHandler::player->rectDraw.right + 1, rectDraw.top);
	}
	else
	{
		Vx = -0.3f;
		UpdateRect(GlobalHandler::player->rectDraw.left - rectDraw.right + rectDraw.left - 1, rectDraw.top);
	}
	stopUpdateSprite = false;
	moving = true;
}