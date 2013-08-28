#include "Bullet.h"
#include "ListTexture.h"
#include "Define.h"
#include "Score.h"

Bullet::Bullet(void)
{
}

Bullet::Bullet( int left, int top )
{
	sprite = new Sprite(ListTexture::TT_BULLET, 
						ListTexture::TT_BULLET_WIDTH, 
						ListTexture::TT_BULLET_HEIGHT, 
						ListTexture::TT_BULLET_COUNT, 
						ListTexture::TT_BULLET_SPRITEPERROW);

	width = ListTexture::TT_BULLET_WIDTH;
	height = ListTexture::TT_BULLET_HEIGHT;

	UpdateRect(left, top, ListTexture::TT_BULLET_WIDTH, ListTexture::TT_BULLET_HEIGHT);
	animatedRate = ListTexture::TT_BULLET_ANIMATED_RATE;
	//	map_level = 2;

	lastAnimate = GetTickCount();
	lastUpdate = GetTickCount();

	iKind = BULLET;
	isSolid = true;

	fXOldVelocity = fYOldVelocity = 0;
	fXOldVelocity = 10;

	//Just init it, dont let it start to do anything.
	start = false;
}

Bullet::~Bullet(void)
{
}

void Bullet::CollidePIPE( int type, RECT rec )
{
	int objCollideCenter = (rec.right + rec.left)/2;
	if (type == PIPE_BODY)
	{
		if (oldLeft < objCollideCenter)
			UpdateRecReal(rec.left - recRealArea.right + recRealArea.left - 1, recRealArea.top);
		else
			UpdateRecReal(rec.right + 1, recRealArea.top);

		ProcessDying();
	}
	if (type == PIPE_CAP)
	{
		UpdateRecReal(recRealArea.left, rec.top - recRealArea.bottom + recRealArea.top);
		fYOldVelocity = 0;
	}
}

void Bullet::CollideGround( StaticObject* obj )
{
	UpdateRecReal(recRealArea.left, obj->recRealArea.top - recRealArea.bottom + recRealArea.top);
	fYOldVelocity = 30;

	trace(L"void Bullet::CollideGround( int top )");
}

void Bullet::CollideBrick( DynamicObject* obj )
{
	//UpdateRecReal(recRealArea.left, obj->recRealArea.top - recRealArea.bottom + recRealArea.top);
	//fYOldVelocity = 30;
	if (oldTop + recRealArea.bottom - recRealArea.top < obj->recRealArea.top + 5)
	{
		UpdateRecReal(recRealArea.left, obj->recRealArea.top - recRealArea.bottom + recRealArea.top);
		fYOldVelocity = 30;
	}
	else
		if (oldTop > obj->recRealArea.bottom - 5)
		{
			//Set position to be right under collided object.
			UpdateRecReal(recRealArea.left, obj->recRealArea.bottom + 1);
			ProcessDying();
		}
		else
		{
			ProcessDying();
		}
}

void Bullet::ProcessDying()
{
	__super::ProcessDying();

	fXOldVelocity = 0;
	animatedRate = 30;
	deathTime = 100;

	GlobalHandler::player->numOfBullet--;
}

void Bullet::UpdateSpriteDying()
{
	DWORD now = GetTickCount();
	if (now - lastAnimate > animatedRate)
	{
		sprite->setDistanceFromTop(ListTexture::TT_BULLET_WIDTH);
		sprite->setWidthHeight(31,31);
		sprite->Next(0,2);
		lastAnimate = now;
	}
}

void Bullet::CollideMushRoomEnemy( DynamicObject* obj )
{
	ProcessDying();

	((Enemy*)obj)->MoveToHell();
}

void Bullet::CheckOutScreen()
{
	if (GlobalHandler::CheckRectInRect(recRealArea, GlobalHandler::screen) == false)
	{
		GlobalHandler::player->numOfBullet--;
		alive = INHELL;
	}
}

void Bullet::setDirect( int dir )
{
	if (dir == LEFT)
		fXOldVelocity = -10;
	else
		fXOldVelocity = 10;
}

void Bullet::CollideTurleEnemy( DynamicObject* obj )
{
	ProcessDying();

	((Enemy*)obj)->MoveToHell();
}

void Bullet::MoveToHell()
{

}

void Bullet::CollidePirhanaPlant( DynamicObject* obj )
{
	//Add score for player.
	Score* score = new Score(recDrawArea.left, recDrawArea.top);
	score->setScore(200);
	GlobalHandler::dynamicObjManager->Add(score);

	ProcessDying();
	obj->alive = INHELL;
}
