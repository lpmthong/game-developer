#include "RedTurleEnemy.h"
#include "Sprite.h"
#include "ListTexture.h"
#include "Define.h"

RedTurleEnemy::RedTurleEnemy(void)
{
}

RedTurleEnemy::RedTurleEnemy( int left, int top )
{
	directBeforeDeath = -2;
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

	objAI = new DynamicObject();
//	objLeft = new TurleEnemy(left - 32, top);
//	objRight = new TurleEnemy(left + 32, top);
}

RedTurleEnemy::~RedTurleEnemy(void)
{
}

void RedTurleEnemy::setAlive()
{
	sprite->Reset(ListTexture::TT_RED_TURLE_ENEMY,
		ListTexture::TT_RED_TURLE_ENEMY_WIDTH,
		ListTexture::TT_RED_TURLE_ENEMY_HEIGHT,
		ListTexture::TT_RED_TURLE_ENEMY_COUNT,
		ListTexture::TT_RED_TURLE_ENEMY_SPRITEPERROW);

	animatedRate = ListTexture::TT_RED_TURLE_ENEMY_ANIMATED_RATE;

	width = ListTexture::TT_RED_TURLE_ENEMY_WIDTH;
	height = ListTexture::TT_RED_TURLE_ENEMY_HEIGHT;

	fYOldVelocity = 0;
	fXOldVelocity = directBeforeDeath;

	iKind = RED_TURLE;

	alive = ALIVE;

	stopUpdateSprite = false;
	moving = true;

	onGround = false;

}

void RedTurleEnemy::UpdateOtherObject()
{
	//if (fXOldVelocity < 0)
	//{
	//	objLeft->Update();
	//	objRight->UpdateRect(this->recDrawArea.left + 32, this->recDrawArea.top);
	//	trace(L"void RedTurleEnemy::UpdateOtherObject() %d %d", CheckOutGround(objLeft), objLeft->fYOldVelocity);
	//	if (CheckOutGround(objLeft) == true)
	//		fXOldVelocity = -fXOldVelocity;
	//}
	//else
	//{
	//	objRight->Update();
	//	objLeft->UpdateRect(this->recDrawArea.left - 32, this->recDrawArea.top);
	//	if (CheckOutGround(objRight) == true)
	//		fXOldVelocity = -fXOldVelocity;
	//}

	//obj->UpdateRect(this->recDrawArea.left, this->recDrawArea.bottom);
	//StaticObject* objCollision = GlobalHandler::quadTree->CheckCollision(obj);
	//if (objCollision == NULL)
	//	trace(L"here");

	//Move left.
}



void RedTurleEnemy::Render()
{
	RECT screen = GlobalHandler::screen;
	sprite->Render(GlobalHandler::directX->backbuffer, recDrawArea.left - screen.left, recDrawArea.top - screen.top);
//	objLeft->sprite->Render(GlobalHandler::directX->backbuffer, objLeft->recDrawArea.left - screen.left, objLeft->recDrawArea.top - screen.top);
//	objRight->sprite->Render(GlobalHandler::directX->backbuffer, objRight->recDrawArea.left - screen.left, objRight->recDrawArea.top - screen.top);
}

bool RedTurleEnemy::CheckOutGround( TurleEnemy* obj )
{
	//if (obj->fYOldVelocity > 0)
		return true;
	//else
	//	return false;
}

void RedTurleEnemy::CollideGround(StaticObject* obj)
{
	UpdateRecReal(recRealArea.left, obj->recDrawArea.top - recRealArea.bottom + recRealArea.top);
	fYVelocity = 0;
	fYOldVelocity = 0;
	onGround = true;

	if (fXOldVelocity < 0)
	{
		objAI->UpdateRect(recRealArea.left - 10, recRealArea.bottom + 10);
	}
	else //Move right
	{
		objAI->UpdateRect(recRealArea.right + 10, recRealArea.bottom + 10);
	}

//	liCollidedObj.clear();
//	DynamicObject* objDynamicCollision = GlobalHandler::dynamicObjManager->CheckCollision(objAI,liCollidedObj);
	
	StaticObject* objCollision = GlobalHandler::quadTree->CheckCollision(objAI);

	if (objCollision == NULL)
		fXOldVelocity = -fXOldVelocity;
}

void RedTurleEnemy::CollideBrick( DynamicObject* obj )
{
	__super::CollideBrick(obj);

	if (fXOldVelocity < 0)
	{
		objAI->UpdateRect(recRealArea.left - 5, recRealArea.bottom + 10);
	}
	else //Move right
	{
		objAI->UpdateRect(recRealArea.right + 5, recRealArea.bottom + 10);
	}

	list<DynamicObject*> holder;
	DynamicObject* objCollision = GlobalHandler::dynamicObjManager->CheckCollision(objAI, holder);

	if (objCollision == NULL)
		fXOldVelocity = -fXOldVelocity;
}

void RedTurleEnemy::setDeath()
{
	iKind = TURLEDEATH;
	trace(L"void TurleEnemy::setDeath");
	sprite->Reset(ListTexture::TT_RED_TURLE_DEATH,
		ListTexture::TT_RED_TURLE_DEATH_WIDTH,
		ListTexture::TT_RED_TURLE_DEATH_HEIGHT,
		ListTexture::TT_RED_TURLE_DEATH_COUNT,
		ListTexture::TT_RED_TURLE_DEATH_SPRITEPERROW);

	width = ListTexture::TT_RED_TURLE_DEATH_WIDTH;
	height = ListTexture::TT_RED_TURLE_DEATH_HEIGHT;

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
}
