#include "Enemy.h"
#include "StaticObject.h"
#include "GlobalHandler.h"
#include "Define.h"
#include <list>
#include "trace.h"
#include "Score.h"
#include "Brick.h"

Enemy::Enemy(void)
{
	oldBrick = NULL;
	oldBrickTop = 0;
	preparing = false;
	alive = ALIVE;

	//Just init it, dont let it start to do anything.
	start = false;

	debug = false;
}

Enemy::~Enemy(void)
{
}

void Enemy::Update()
{
	DWORD now = GetTickCount();
	int t = now - lastUpdate;
	lastUpdate = now;

	if (preparing)
		PrepareToMove(t);
	else
	//If this enemy is not in preparing mode anymore.
	{
		//If this enemy can be death, then let accept it.
		if (alive == ALIVE)
			DieByHittinBrick();

		oldLeft = recRealArea.left;
		oldTop = recRealArea.top;

		//If this enemy is in DYING or INHELL mode, just do some little thing to pleasure it.
		if (alive == DYING || alive == INHELL)
		{
			if (now - beginDeath > deathTime)
				alive = INHELL;
			UpdateSpriteDying();
			return;
		}

		oldTop = recRealArea.top;
		oldLeft = recRealArea.left;
		Revive();
		NormalMove(t);

		HandleCollisionQT();
		HandleCollisionDO();
	}

	UpdateOtherObject();
	UpdateSprite();
	CheckOutScreen();

}

void Enemy::UpdateSprite()
{
	DWORD now = GetTickCount();
	if (now - lastAnimate > animatedRate)
	{
		sprite->Next();
		lastAnimate = now;
	}
}

void Enemy::HandleCollisionQT()
{
	if (!isSolid)
		return;
	
	while (true)
	{
		//check collision with quadtree and return the object which collide this.
		StaticObject* objCollision = GlobalHandler::quadTree->CheckCollision(this);

		if (objCollision == NULL)
			break;
		else
		{
			//for each kind of object in quadtree, we handle collide it differently.
			if (objCollision->iKind == PIPE_BODY || objCollision->iKind == PIPE_CAP)
				CollidePIPE(objCollision->iKind, objCollision->recRealArea);
			if (objCollision->iKind == GROUND)
				CollideGround(objCollision);
			if (objCollision->iKind == OUTCOIN)
				return;
			if (objCollision->iKind == ENDMAP)
				return;
		}
	}
}

void Enemy::HandleCollisionDO()
{
	if (!isSolid)
		return;

	liCollidedObj.clear();	
	while (true)
	{
		//check collision with dynamic object Manager and return the object which collide this.
		DynamicObject* objCollision = GlobalHandler::dynamicObjManager->CheckCollision(this,liCollidedObj);

		if (objCollision == NULL)
			break;
		else
		{
			liCollidedObj.push_back(objCollision);
			//if (objCollision->iKind == BRICK)
			//	CollideBrick(objCollision);
		}
	}

	list<DynamicObject*>::iterator it;
	for (it = liCollidedObj.begin(); it != liCollidedObj.end(); it ++)
	{
		if ((*it)->iKind == BRICK || (*it)->iKind == BRICK_BONUS_MUSHROOM || (*it)->iKind == BRICK_BONUS_GUN || (*it)->iKind == BRICK_BONUS_LIFE || (*it)->iKind == BRICK_BONUS_COIN || (*it)->iKind == HARDBRICK || (*it)->iKind == CROSS)
			CollideBrick((*it));
		else
			if ((*it)->iKind == MUSHROOM_ENEMY)
				CollideMushRoomEnemy((*it));
			if ((*it)->iKind == TURLE)
				CollideTurleEnemy((*it));
			if ((*it)->iKind == TURLEDEATH)
				CollideTurleDeath((*it));
			if ((*it)->iKind == PIRHANAPLANT)
				CollidePirhanaPlant((*it));
			else
			{
				oldBrick = NULL;
				oldBrickTop = 0;
			}
	}
}

void Enemy::CollidePIPE( int type, RECT rec )
{
	int objCollideCenter = (rec.right + rec.left)/2;
	if (type == PIPE_BODY)
	{
		if (oldLeft < objCollideCenter)
			UpdateRecReal(rec.left - recRealArea.right + recRealArea.left - 1, recRealArea.top);
		else
			UpdateRecReal(rec.right + 1, recRealArea.top);

		//Turn back.
		fXOldVelocity = -fXOldVelocity;
	}
	if (type == PIPE_CAP)
	{
		UpdateRecReal(recRealArea.left, rec.top - recRealArea.bottom + recRealArea.top);
		fYOldVelocity = 0;
		fXVelocity = fXOldVelocity = acceleration = 0;
		onGround = true;
	}
}

void Enemy::CollideGround( StaticObject* obj )
{
	//UpdateRecReal(recRealArea.left, obj->recRealArea.top - recRealArea.bottom + recRealArea.top);
	//fYVelocity = 0;
	//fYOldVelocity = 0;
	//onGround = true;

	if (oldTop + recRealArea.bottom - recRealArea.top < obj->recRealArea.top + 5)
	{
		Brick* collideBrick = (Brick*)obj;
		if (collideBrick->hasCollide == true)
		{
			MoveToHell();
		}
		UpdateRecReal(recRealArea.left, obj->recRealArea.top - recRealArea.bottom + recRealArea.top);
		fYVelocity = 0;
		fYOldVelocity = 0;
	}
	else
	{
		//Turn back.
		fXOldVelocity = -fXOldVelocity;

		int objCollideCenter = (obj->recRealArea.right + obj->recRealArea.left)/2;
		if (oldLeft < objCollideCenter)
			UpdateRecReal(obj->recRealArea.left - recRealArea.right + recRealArea.left - 1, recRealArea.top);
		else
			UpdateRecReal(obj->recRealArea.right + 1, recRealArea.top);
	}

	//fYVelocity = 0;
	//fYOldVelocity = 0;
	//onGround = true;

//	trace(L"void Enemy::CollideGround( StaticObject* obj )");
}

void Enemy::CollideBrick( DynamicObject* obj )
{
//	if (obj->iKind == HARDBRICK)
//		int a  = 0;
//	trace(L"%d %d", oldTop, obj->recRealArea.top);
	if (oldTop + recRealArea.bottom - recRealArea.top < obj->recRealArea.top + 5)
	{
		Brick* collideBrick = (Brick*)obj;
		if (collideBrick->hasCollide == true)
		{
			MoveToHell();
		}
		UpdateRecReal(recRealArea.left, obj->recRealArea.top - recRealArea.bottom + recRealArea.top);
		fYVelocity = 0;
		fYOldVelocity = 0;
	}
	else
		{
			//Turn back.
			fXOldVelocity = -fXOldVelocity;

			int objCollideCenter = (obj->recRealArea.right + obj->recRealArea.left)/2;
			if (oldLeft < objCollideCenter)
				UpdateRecReal(obj->recRealArea.left - recRealArea.right + recRealArea.left - 1, recRealArea.top);
			else
				UpdateRecReal(obj->recRealArea.right + 1, recRealArea.top);
		}

	fYVelocity = 0;
	fYOldVelocity = 0;
	oldBrick = obj;
	oldBrickTop = obj->recRealArea.top;
	onGround = true;
}

void Enemy::ProcessDying()
{
	isSolid = false;
	beginDeath = GetTickCount();
	alive = DYING;
}

void Enemy::DieByHittinBrick()
{
	//if (oldTop - recRealArea.top > 0)
	//	if (oldTop - recRealArea.top < 4)
	//{
	//	trace(L"void Enemy::DieByHittinBrick()");
	//	MoveToHell();
	//}
}

void Enemy::MoveToHell()
{
	isSolid = false;
	alive = DYING2;
	trace(L"void Enemy::MoveToHell()");

	//Add score for player.
	Score* score = new Score(recDrawArea.left, recDrawArea.top);
	score->setScore(200);
	GlobalHandler::dynamicObjManager->Add(score);
}

void Enemy::PrepareToMove(int t)
{

}

void Enemy::NormalMove(int t)
{
	oldTop = recRealArea.top;

	fYVelocity = fYOldVelocity - 15 * t / 100;

	int x = recRealArea.left;
	x += fXOldVelocity;
	//	int y = recRealArea.top;

	int y = recRealArea.top - fYOldVelocity * t / 100 - 7 * t * t / 100000;
//	trace(L"void Enemy::NormalMove(int t) %d", y);
	UpdateRecReal(x, y);
	//	trace(L"%0.2f 0.2f", fYOldVelocity, fYVelocity);
	fYOldVelocity = fYVelocity;

	if (y > SCREEN_HEIGHT)
		alive = INHELL;

}

void Enemy::UpdateSpriteDying()
{
	DWORD now = GetTickCount();
	if (now - lastAnimate > animatedRate)
	{
		sprite->Next(3,3);
		lastAnimate = now;
	}
}

void Enemy::CollideMushRoomEnemy( DynamicObject* obj )
{
	debug = true;
	if (iKind == TURLEDEATH && fYVelocity == 0 && fXOldVelocity != 0)
	{
		((Enemy*)obj)->MoveToHell();
		return;
	}	

	trace(L"void Enemy::CollideMushRoomEnemy( DynamicObject* obj )");

	int objCollideCenter = (obj->recRealArea.right + obj->recRealArea.left)/2;

	if (oldLeft < objCollideCenter)
		UpdateRecReal(obj->recRealArea.left - recRealArea.right + recRealArea.left, recRealArea.top);
	else
		UpdateRecReal(obj->recRealArea.right, recRealArea.top);

	//Turn back.
	fXOldVelocity = -fXOldVelocity;

	obj->fXOldVelocity = -obj->fXOldVelocity;
}

void Enemy::CheckOutScreen()
{
	if (recRealArea.top > SCREEN_HEIGHT)
		alive = INHELL;
}

void Enemy::CollideTurleEnemy( DynamicObject* obj )
{
	int objCollideCenter = (obj->recRealArea.right + obj->recRealArea.left)/2;

	if (oldLeft < objCollideCenter)
		UpdateRecReal(obj->recRealArea.left - recRealArea.right + recRealArea.left, recRealArea.top);
	else
		UpdateRecReal(obj->recRealArea.right, recRealArea.top);

	//Turn back.
	fXOldVelocity = -fXOldVelocity;

	obj->fXOldVelocity = -obj->fXOldVelocity;

//	trace(L"void Enemy::CollideTurleEnemy( DynamicObject* obj )");
}

void Enemy::Revive()
{

}

void Enemy::CollideTurleDeath( DynamicObject* obj )
{
	trace(L"void Enemy::CollideTurleDeath( DynamicObject* obj )");
	if (obj->fXOldVelocity != 0 || obj->fXVelocity != 0)
	{
		MoveToHell();
		//ProcessDying();
//		trace(L"MovetoHell");
		return;
	}	
}

void Enemy::CollidePirhanaPlant( DynamicObject* obj )
{

}

void Enemy::UpdateOtherObject()
{
}
