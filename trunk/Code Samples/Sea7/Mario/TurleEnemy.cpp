#include "TurleEnemy.h"
#include "ListTexture.h"
#include "Define.h"

TurleEnemy::TurleEnemy(void)
{
}

TurleEnemy::TurleEnemy( int left, int top )
{
	directBeforeDeath = -4;
	sprite = new Sprite();
	setAlive();

	UpdateRect(left, top);

	
	lastAnimate = GetTickCount();
	lastUpdate = GetTickCount();

	isSolid = true;


	deathTime = 1500;

	preparing = false;

	//Just init it, dont let it start to do anything.
	start = false;

}

TurleEnemy::~TurleEnemy(void)
{
}

void TurleEnemy::UpdateSprite()
{
	if (stopUpdateSprite)
		return;

	DWORD now = GetTickCount();
	if (now - lastAnimate > animatedRate)
	{
		if (iKind == TURLEDEATH)
		{
			
		}
		if (fXOldVelocity > 0)
			sprite->Next(0,1);
		else
			sprite->Next(2,3);
		lastAnimate = now;
	}
}

void TurleEnemy::MoveToHell()
{
	__super::MoveToHell();
	trace(L"void TurleEnemy::MoveToHell()");

	fXOldVelocity = 0;
//	if (iKind == TURLE)
		fYOldVelocity = 0;
//	else
//		fYOldVelocity = 50;
	fYVelocity = 0;
}

void TurleEnemy::UpdateSpriteDying()
{
	DWORD now = GetTickCount();
	if (now - lastAnimate > animatedRate)
	{
		if (alive == DYING2)
		{
			sprite->Reset(ListTexture::TT_TURLE_DEATH,
				ListTexture::TT_TURLE_DEATH_WIDTH,
				ListTexture::TT_TURLE_DEATH_HEIGHT,
				ListTexture::TT_TURLE_DEATH_COUNT,
				ListTexture::TT_TURLE_DEATH_SPRITEPERROW);

			sprite->Next(3,3);
		}
		lastAnimate = now;
	}
}

void TurleEnemy::ProcessDying()
{
	setDeath();
	trace(L"void TurleEnemy::ProcessDying()");
}

void TurleEnemy::setDeath()
{
	iKind = TURLEDEATH;
	trace(L"void TurleEnemy::setDeath");
	sprite->Reset(ListTexture::TT_TURLE_DEATH,
		ListTexture::TT_TURLE_DEATH_WIDTH,
		ListTexture::TT_TURLE_DEATH_HEIGHT,
		ListTexture::TT_TURLE_DEATH_COUNT,
		ListTexture::TT_TURLE_DEATH_SPRITEPERROW);

	width = ListTexture::TT_TURLE_DEATH_WIDTH;
	height = ListTexture::TT_TURLE_DEATH_HEIGHT;

	sprite->setIndex(1);
	UpdateRect(recDrawArea.left, recDrawArea.top - 30);
	oldTop = recRealArea.top;

	beginDeath = GetTickCount();
	timeInDeath = 7500;

	stopUpdateSprite = true;
	directBeforeDeath = fXOldVelocity;
	fXOldVelocity = 0;
	fYOldVelocity = 0;

	moving = false;

//	trace(L"void TurleEnemy::setDeath()");
}

void TurleEnemy::setAlive()
{
	sprite->Reset(ListTexture::TT_TURLE_ENEMY,
		ListTexture::TT_TURLE_ENEMY_WIDTH,
		ListTexture::TT_TURLE_ENEMY_HEIGHT,
		ListTexture::TT_TURLE_ENEMY_COUNT,		
		ListTexture::TT_TURLE_ENEMY_SPRITEPERROW);

	animatedRate = ListTexture::TT_TURLE_ENEMY_ANIMATED_RATE;

	width = ListTexture::TT_TURLE_ENEMY_WIDTH;
	height = ListTexture::TT_TURLE_ENEMY_HEIGHT;

	fYOldVelocity = 0;
	fXOldVelocity = directBeforeDeath;

	iKind = TURLE;

	alive = ALIVE;

	stopUpdateSprite = false;
	moving = true;

	onGround = false;
}

void TurleEnemy::Revive()
{
	DWORD now = GetTickCount();

	if (now - beginDeath > timeInDeath && iKind == TURLEDEATH && moving == false)
		setAlive();
}

void TurleEnemy::setDeathMoving()
{
	if (recRealArea.left + width / 2 > GlobalHandler::player->recRealArea.left + GlobalHandler::player->width / 2)
	{
		fXOldVelocity = 15;
		UpdateRecReal(GlobalHandler::player->recRealArea.right + 1, recRealArea.top);
	}
	else
	{
		fXOldVelocity = -15;
		UpdateRecReal(GlobalHandler::player->recRealArea.left - recRealArea.right + recRealArea.left - 1, recRealArea.top);
	}
	moving = true;
}
