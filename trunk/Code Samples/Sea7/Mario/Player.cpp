#include "Player.h"
#include "ListTexture.h"
#include "Define.h"
#include <winbase.h>
#include "trace.h"
#include <stdlib.h>
#include "Bullet.h"
#include "TurleEnemy.h"
#include "BonusMushroom.h"
#include "PirhanaPlant.h"
#include "EndMap.h"
#include "ListSound.h"

Player::Player(void)
{

}

Player::Player( int left, int top )
{
}

void Player::Update()
{
	//If mario go out of life, it can not move any more.
	if (life < 0)
		return;

	//If mario go out screen.
	ProcessDying();

	//If mario finish the map, it stop.
	if (getEndMap && recRealArea.left > GlobalHandler::screen.right)
		return;


	DWORD now = GetTickCount();
	DWORD t = now - lastUpdate;
	lastUpdate = now;

	//v = v0 - 1 / 2 * g * t * t
	fYVelocity = fYOldVelocity - 15 * t / 100;
	fXVelocity = fXOldVelocity + acceleration * t / 100;

	fXVelocity = (fXVelocity < maxSpeed)?fXVelocity:maxSpeed;
	fXVelocity = (fXVelocity > -maxSpeed)?fXVelocity:(-maxSpeed);

	fXVelocity = ((fXOldVelocity*fXVelocity) >= 0)?fXVelocity:0;

	//If mario get end map, it go freely with max speed.
	fXVelocity = (getEndMap)?maxSpeed:fXVelocity;

	//	trace(L"Space %0.2f %0.2f", fXVelocity, fXOldVelocity);

	oldLeft = recRealArea.left;
	oldTop = recRealArea.top;

	int x = recRealArea.left;
//	int y = recRealArea.top;

	if (onGround == true)
		x += fXOldVelocity * t / 100 + acceleration * t * t / 100000 / 2;
	else
		x += fXVelocity * t / 100;
	

	int yDistance = fYOldVelocity * t / 100 + 7 * t * t / 100000;
//	trace(L"%d", yDistance);
	yDistance = (yDistance > 40)?40:yDistance;
	int y = recRealArea.top - yDistance;
		
	x = (x > 10)?x:10;

	UpdateRecReal(x, y);

//	//trace(L"%f %f %d %d %d", fXOldVelocity, fXVelocity, recDrawArea.left, t, recDrawArea.top);


	fYOldVelocity = fYVelocity;
	fXOldVelocity = fXVelocity;
	
	if ((int)oldTop != (int)recRealArea.top)
		onGround = false;
	else
		onGround = true;

	//if (recRealArea.right > 1023 && recRealArea.bottom > 434)
	//{
	//	int  a= 0;
	//	trace(L"%d", recRealArea.bottom);
	//}

	if (alive != DYING)
	{
		HandleCollisionQT();
		HandleCollisionDO();
	}

	////trace(L"Space %d %d %d", oldTop, recRealArea.top, onGround);
	UpdateSprite(false);
	CheckImmortal();

	GlobalHandler::UpdateScreen();
	UpdateCheckPoint();
//	trace(L"%d", lastCheckPoint);
}

void Player::Init( int outMode, int outLastCheckPoint, int outLife )
{
	try
	{
		sprite = new Sprite();
	}
	catch (...)
	{
	}

	InitFromFile(outMode, outLastCheckPoint, outLife);

	animatedRate = ListTexture::TT_MARIO_KID_ANIMATED_RATE;
	lastAnimate = GetTickCount();
	lastUpdate = GetTickCount();

	fYOldVelocity = fYVelocity = acceleration = 0;
	fXOldVelocity = fXVelocity = 0;

	onGround = false;

	oldDirect = true;
	times = 0;
	jumping = false;

	immortal = false;
	immortalRender = 0;
	beginImmortal = GetTickCount();
	timeInImmortal = 1500;

	hasStar = false;
	startHasStar = GetTickCount();
	timeHasStar = 10000;


	loop = false;
	beginLoop = GetTickCount();
	endMode = PLAYER_ADULT;
	rateLoop = 100;
	lastLoop = GetTickCount();
	timeInLoop = 1000;

	lastShot = GetTickCount();
	delayShot = 200;
	numOfBullet = 0;

	alive = ALIVE;

	getEndMap = false;
	maxSpeed = 20;

	trace(L"void Player::Init( int outMode, int outLastCheckPoint, int outLife )");
}

void Player::OnKeyDown( int keyCode )
{
	if (alive == DYING || getEndMap == true)
		return;

	switch (keyCode)
	{
	case DIK_ESCAPE:
		GlobalHandler::gameState = GS_STARTGAMEOPTIONS;
		break;
	case DIK_UP:
		if (onGround == true)
		{
			//set V0.
			fYOldVelocity = 65;
			jumping = true;
			GlobalHandler::sound->Play(ListSound::SOUND_JUMP,FALSE);
		}
		break;
	case DIK_Z:
		if (hasGun == false)
			return;
		//If we run out of bullet.
		if (numOfBullet > 1)
			break;

		DWORD now = GetTickCount();
		if (now - lastShot < delayShot)
			break;
		lastShot = now;
		numOfBullet++;

		//Shot left or right.
		Bullet* bullet;
		if (oldDirect == true)
		{
			bullet = new Bullet(recRealArea.right - 10, recRealArea.top + height / 2 - 5);
			bullet->setDirect(RIGHT);
		}
		else
		{
			bullet = new Bullet(recRealArea.left + 10, recRealArea.top + height / 2 - 5);
			bullet->setDirect(LEFT);
		}

		GlobalHandler::dynamicObjManager->Add(bullet);
		GlobalHandler::sound->Play(ListSound::SOUND_FIREBALL,FALSE);
		break;
	}
}

void Player::ProcessInput()
{
	if (alive == DYING)
		return;

	if (GlobalHandler::directX->IsKeyDown(DIK_RIGHT) && !getEndMap)
	{
		if (onGround == false)
		{
			fXOldVelocity = 20;
			acceleration = 0;
		}
		else
			acceleration = 3;

		oldDirect = true;
	}
	else 
		if (GlobalHandler::directX->IsKeyDown(DIK_LEFT) && !getEndMap)
		{
			acceleration = -3;
			oldDirect = false;
		}
		else 
		{
			if (fXVelocity > 1)
				acceleration = -3;
			else
				if (fXVelocity < -1)
					acceleration = 3;
				else
					{
						acceleration = 0;
						fXOldVelocity = fXVelocity = 0;
					}
		}

//	HandleCollisionQT();
//	HandleCollisionDO();
}

void Player::UpdateSprite()
{
	if (alive == DYING)
	{
		sprite->Next(ListTexture::TT_MARIO_KID_DEATH_START, ListTexture::TT_MARIO_KID_DEATH_END);
		return;
	}

	if (onGround == false || jumping == true)
		if (oldDirect == true)
			sprite->setIndex(frame_jumping_right_start, frame_jumping_right_end);
		else
			if (oldDirect == false)
				sprite->setIndex(frame_jumping_left_start, frame_jumping_left_end);
			else{}
	else
		if (fXVelocity > 0)
			sprite->setIndex(frame_moving_right_start, frame_moving_right_end);
		else
			if (fXVelocity < 0)
				sprite->setIndex(frame_moving_left_start, frame_moving_left_end);
			else
				if (oldDirect == true)
					sprite->setIndex(frame_moving_right_start, frame_moving_right_start);
				else
					sprite->setIndex(frame_moving_left_start, frame_moving_left_start);
}

void Player::UpdateSprite( bool rightAway )
{
	//If this mario in death mode, dont update anything.
	if (alive == DYING)
		return;

	ChangeModeLoop();

	DWORD now = GetTickCount();
	animatedRate = 10 - abs(fXVelocity) / 2 + 5;

	bool update = (rightAway == true)?true:((now - lastAnimate) / 10 > animatedRate);
	if (update)
	{
		lastAnimate = now;
		if (onGround == false || jumping == true)
			if (oldDirect == true)
				sprite->Next(frame_jumping_right_start, frame_jumping_right_end);
			else
				if (oldDirect == false)	
					sprite->Next(frame_jumping_left_start, frame_jumping_left_end);
				else{}
		else
			if (fXOldVelocity > 0)
				sprite->Next(frame_moving_right_start, frame_moving_right_end);
			else
				if (fXOldVelocity < 0)
					sprite->Next(frame_moving_left_start, frame_moving_left_end);
				else
					if (oldDirect == true)
						sprite->Next(frame_moving_right_start, frame_moving_right_start);
					else
						sprite->Next(frame_moving_left_start, frame_moving_left_start);
	}
}

void Player::HandleCollisionQT()
{
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
				CollidePIPE(objCollision);
			if (objCollision->iKind == GROUND)
			{
				CollideGround(objCollision);
			}
			if (objCollision->iKind == OUTCOIN)
				CollideOutCoin(objCollision);
			if (objCollision->iKind == ENDMAP)
			{
				CollideEndMap(objCollision);
			}
		}
	}
}

void Player::HandleCollisionDO()
{
	list<DynamicObject*> liCollidedObj;
	numOfCollideObject = 0;
	sameColumn = false;

	while (true)
	{
		//check collision with dynamic object Manager and return the object which collide this.
		DynamicObject* objCollision = GlobalHandler::dynamicObjManager->CheckCollision(this, liCollidedObj);

		if (objCollision == NULL)
			break;
		else
		{
			liCollidedObj.push_back(objCollision);
			
			if (oldLeftCollidedObject == objCollision->recRealArea.left)
				sameColumn = true;
			else
			{
				oldLeftCollidedObject = objCollision->recRealArea.left;
			}
			
			numOfCollideObject++;
		}
	}
	oldLeftCollidedObject = 0;
	oldCollidedObject = -1;
	//numOfCollideObject = liCollidedObj.size();
	//trace(L"void Player::HandleCollisionDO() %d", numOfCollideObject);
	list<DynamicObject*>::iterator it;
	for (it = liCollidedObj.begin(); it != liCollidedObj.end(); it ++)
	{
		if (CheckCollisionAgain(*it) == false)
			continue;
		if ((*it)->iKind == BRICK || (*it)->iKind == BRICK_BONUS_MUSHROOM || (*it)->iKind == BRICK_BONUS_GUN || (*it)->iKind == BRICK_BONUS_LIFE || (*it)->iKind == BRICK_BONUS_COIN || (*it)->iKind == HARDBRICK || (*it)->iKind == CROSS || (*it)->iKind == BRICK_BONUS_LIFE_HIDDEN || (*it)->iKind == FALLING_CROSS || (*it)->iKind == BRICK_BONUS_STAR)
			CollideBrick(*it);
		if ((*it)->iKind == MUSHROOM_ENEMY)
			CollideMushRoomEnemy(*it);
		if ((*it)->iKind == BONUS_MUSHROOM)
			CollideBonus(*it);
		if ((*it)->iKind == TURLE || (*it)->iKind == RED_TURLE)
			CollideTurle(*it);
		if ((*it)->iKind == TURLEDEATH || (*it)->iKind == RED_TURLE_DEATH)
			CollideTurleDeath(*it);
		if ((*it)->iKind == PIRHANAPLANT)
			CollidePirhanaPlant(*it);
	}
}

void Player::setKid()
{
	sprite->Reset(ListTexture::TT_MARIO_KID,
		ListTexture::TT_MARIO_KID_WIDTH,
		ListTexture::TT_MARIO_KID_HEIGHT,
		ListTexture::TT_MARIO_KID_COUNT,
		ListTexture::TT_MARIO_KID_SPRITEPERROW);

	iKind = PLAYER_KID;

	width = ListTexture::TT_MARIO_KID_WIDTH;
	height = ListTexture::TT_MARIO_KID_HEIGHT;

	animatedRate = ListTexture::TT_MARIO_KID_ANIMATED_RATE;

	//frame index.
	frame_moving_left_start		= ListTexture::TT_MARIO_KID_MOVING_LEFT_START;
	frame_moving_left_end		= ListTexture::TT_MARIO_KID_MOVING_LEFT_END;
	frame_moving_right_start	= ListTexture::TT_MARIO_KID_MOVING_RIGHT_START;
	frame_moving_right_end		= ListTexture::TT_MARIO_KID_MOVING_RIGHT_END;
	frame_jumping_left_start	= ListTexture::TT_MARIO_KID_JUMPING_LEFT_START;
	frame_jumping_left_end		= ListTexture::TT_MARIO_KID_JUMPING_LEFT_END;
	frame_jumping_right_start	= ListTexture::TT_MARIO_KID_JUMPING_RIGHT_START;
	frame_jumping_right_end		= ListTexture::TT_MARIO_KID_JUMPING_RIGHT_END;

	UpdateSprite();
}

void Player::setAdult()
{
	sprite->Reset(ListTexture::TT_MARIO_ADULT,
		ListTexture::TT_MARIO_ADULT_WIDTH,
		ListTexture::TT_MARIO_ADULT_HEIGHT,
		ListTexture::TT_MARIO_ADULT_COUNT,
		ListTexture::TT_MARIO_ADULT_SPRITEPERROW);

	iKind = PLAYER_ADULT;

	width = ListTexture::TT_MARIO_ADULT_WIDTH;
	height = ListTexture::TT_MARIO_ADULT_HEIGHT;

	animatedRate = ListTexture::TT_MARIO_ADULT_ANIMATED_RATE;

	frame_moving_left_start		= ListTexture::TT_MARIO_ADULT_MOVING_LEFT_START;
	frame_moving_left_end		= ListTexture::TT_MARIO_ADULT_MOVING_LEFT_END;
	frame_moving_right_start	= ListTexture::TT_MARIO_ADULT_MOVING_RIGHT_START;
	frame_moving_right_end		= ListTexture::TT_MARIO_ADULT_MOVING_RIGHT_END;
	frame_jumping_left_start	= ListTexture::TT_MARIO_ADULT_JUMPING_LEFT_START;
	frame_jumping_left_end		= ListTexture::TT_MARIO_ADULT_JUMPING_LEFT_END;
	frame_jumping_right_start	= ListTexture::TT_MARIO_ADULT_JUMPING_RIGHT_START;
	frame_jumping_right_end		= ListTexture::TT_MARIO_ADULT_JUMPING_RIGHT_END;

	UpdateSprite();
}

void Player::setGun()
{
	sprite->Reset(ListTexture::TT_MARIO_ADULT,
		ListTexture::TT_MARIO_ADULT_WIDTH,
		ListTexture::TT_MARIO_ADULT_HEIGHT,
		ListTexture::TT_MARIO_ADULT_COUNT,
		ListTexture::TT_MARIO_ADULT_SPRITEPERROW);

	iKind = PLAYER_ADULT_GUN;

	width = ListTexture::TT_MARIO_ADULT_WIDTH;
	height = ListTexture::TT_MARIO_ADULT_HEIGHT;

	animatedRate = ListTexture::TT_MARIO_ADULT_ANIMATED_RATE;

	frame_moving_left_start		= ListTexture::TT_MARIO_GUN_MOVING_LEFT_START;
	frame_moving_left_end		= ListTexture::TT_MARIO_GUN_MOVING_LEFT_END;
	frame_moving_right_start	= ListTexture::TT_MARIO_GUN_MOVING_RIGHT_START;
	frame_moving_right_end		= ListTexture::TT_MARIO_GUN_MOVING_RIGHT_END;
	frame_jumping_left_start	= ListTexture::TT_MARIO_GUN_JUMPING_LEFT_START;
	frame_jumping_left_end		= ListTexture::TT_MARIO_GUN_JUMPING_LEFT_END;
	frame_jumping_right_start	= ListTexture::TT_MARIO_GUN_JUMPING_RIGHT_START;
	frame_jumping_right_end		= ListTexture::TT_MARIO_GUN_JUMPING_RIGHT_END;

	UpdateSprite();
}


void Player::CollidePIPE(StaticObject* obj)
{
//	getEndMap = true;
//	GlobalHandler::endMap = true;
	if (oldTop + recRealArea.bottom - recRealArea.top < obj->recRealArea.top + 5)
	{
		UpdateRecReal(recRealArea.left, obj->recRealArea.top - recRealArea.bottom + recRealArea.top);
		fYVelocity = 0;
		fYOldVelocity = 0;

		onGround = true;
		jumping =false;
		UpdateSprite();

	}
	//else
	//	if (oldTop > obj->recRealArea.bottom - 5)
	//	{
	//		//Set position to be right under collided object.
	//		UpdateRecReal(recRealArea.left, obj->recRealArea.bottom + 1);
	//		fYOldVelocity = 0;
	//		fYVelocity = 0;
	//	}
		else
		{
			fXVelocity = fXOldVelocity = acceleration = 0;
			int objCollideCenter = (obj->recRealArea.right + obj->recRealArea.left)/2;
			if (oldLeft < objCollideCenter)
				UpdateRecReal(obj->recRealArea.left - recRealArea.right + recRealArea.left - 1, recRealArea.top);
			else
				UpdateRecReal(obj->recRealArea.right + 1, recRealArea.top);
			return;
		}
//
//	if (oldTop + recRealArea.bottom - recRealArea.top < obj->recRealArea.top + 5)
//	{
////		if (obj->iKind == PIPE_CAP)
//			UpdateRecReal(recRealArea.left, obj->recRealArea.top - recRealArea.bottom + recRealArea.top);
////		else
////			UpdateRecReal(recRealArea.left, recRealArea.top - 38);
//		fYVelocity = 0;
//		fYOldVelocity = 0;
//
//		onGround = true;
//		jumping =false;
//		UpdateSprite();
//
//	}
//	else
//		if (oldTop > obj->recRealArea.bottom - 5)
//		{
//			//Set position to be right under collided object.
//			UpdateRecReal(recRealArea.left, obj->recRealArea.bottom + 1);
//			fYOldVelocity = 0;
//			fYVelocity = 0;
//		}
//		else
//		{
//			int objCollideCenter = (obj->recRealArea.right + obj->recRealArea.left)/2;
//			if (oldLeft < objCollideCenter)
//				UpdateRecReal(obj->recRealArea.left - recRealArea.right + recRealArea.left - 1, recRealArea.top);
//			else
//				UpdateRecReal(obj->recRealArea.right + 1, recRealArea.top);
//			return;
//		}


		//Object collision process its handling collision.
		//obj->ProcessCollision(this->iKind);

	//int objCollideCenter = (obj->recRealArea.right + obj->recRealArea.left)/2;
	//if (obj->iKind == PIPE_BODY)
	//{
	//	if (oldLeft < objCollideCenter)
	//		UpdateRecReal(obj->recRealArea.left - recRealArea.right + recRealArea.left - 1, recRealArea.top);
	//	else
	//		UpdateRecReal(obj->recRealArea.right + 1, recRealArea.top);

	//	//when it meet pipe body, clear x velocity so that when it want to turn back, it can do immediately.
	//	fXOldVelocity = 0;
	//}
	//if (obj->iKind == PIPE_CAP)
	//{
	//	if (fYVelocity > 0)
	//		if (oldLeft < objCollideCenter)
	//			UpdateRecReal(obj->recRealArea.left - recRealArea.right + recRealArea.left - 1, recRealArea.top);
	//		else
	//			UpdateRecReal(obj->recRealArea.right + 1, recRealArea.top);

	//	if (fYVelocity < 0)
	//	{
	//		UpdateRecReal(recRealArea.left, obj->recRealArea.top - recRealArea.bottom + recRealArea.top);
	//		fYVelocity = 0;
	//		fYOldVelocity = 0;

	//		if (onGround == false)
	//		{
	//			onGround = true;
	//			jumping =false;
	//			UpdateSprite();
	//		}
	//		else{}
	//	}
	//}
}

void Player::CollideGround( StaticObject *obj )
{
	//check mario is on object.
	if (oldTop + recRealArea.bottom - recRealArea.top < obj->recRealArea.top + 5)
	{
		UpdateRecReal(recRealArea.left, obj->recRealArea.top - recRealArea.bottom + recRealArea.top);
		fYVelocity = 0;
		fYOldVelocity = 0;

		onGround = true;
		jumping =false;
		UpdateSprite();

	}
	else
		//check mario is under object.
		if (oldTop > obj->recRealArea.bottom - 5 && numOfCollideObject < 2)
		{
			//Set position to be right under collided object.
			UpdateRecReal(recRealArea.left, obj->recRealArea.bottom + 1);
			fYOldVelocity = 0;
			fYVelocity = 0;
		}
		else
		{
			int objCollideCenter = (obj->recRealArea.right + obj->recRealArea.left)/2;

			//mario is left.
			if (oldLeft < objCollideCenter)
				UpdateRecReal(obj->recRealArea.left - recRealArea.right + recRealArea.left, recRealArea.top);
			else
				//mario is right.
				UpdateRecReal(obj->recRealArea.right, recRealArea.top);
			return;
		}
}

void Player::CollideBrick( DynamicObject* obj )
{
	if (oldTop + recRealArea.bottom - recRealArea.top < obj->recRealArea.top + 5 && sameColumn == false)
	{
		UpdateRecReal(recRealArea.left, obj->recRealArea.top - recRealArea.bottom + recRealArea.top);
		fYVelocity = 0;
		fYOldVelocity = 0;

		onGround = true;
		jumping =false;
		UpdateSprite();
//		trace(L"void Player::CollideBrick( DynamicObject* obj ) up");

	}
	else
		if (oldTop > obj->recRealArea.bottom - 5 && sameColumn == false)
		{
			//Set position to be right under collided object.
			UpdateRecReal(recRealArea.left, obj->recRealArea.bottom + 1);
			fYOldVelocity = 0;
			fYVelocity = 0;
//			trace(L"void Player::CollideBrick( DynamicObject* obj ) under");
		}
		else
		{
			fXVelocity = fXOldVelocity = acceleration = 0;
			int objCollideCenter = (obj->recRealArea.right + obj->recRealArea.left)/2;
			if (oldLeft < objCollideCenter)
			{
				UpdateRecReal(obj->recRealArea.left - recRealArea.right + recRealArea.left, recRealArea.top);
//				trace(L"void Player::CollideBrick( DynamicObject* obj ) left");
			}
			else
			{
				UpdateRecReal(obj->recRealArea.right, recRealArea.top);
//				trace(L"void Player::CollideBrick( DynamicObject* obj ) right");
			}
			return;
		}

		//Object collision process its handling collision.
		obj->ProcessCollision(this->iKind);
}

void Player::CollideMushRoomEnemy(DynamicObject* enemy)
{
	if (!immortal)
	{
		if (!KillEnemy(enemy))
		{
			Die();
		}
		else
		{
			Score* score = new Score(recRealArea.left, recRealArea.top);
			score->setScore(200);
			GlobalHandler::dynamicObjManager->Add(score);

			GlobalHandler::sound->Play(ListSound::SOUND_MIP, false);
		}
	}
}

void Player::Render()
{
	//when in immortal mode, if immortalRender equal 0 or 1 we draw mario. If immortalRender equal 2 or 3, we dont draw it.
	if (immortal == true)
	{
		if (immortalRender == 2)
		{
			immortalRender ++;
			return;
		}
		if (immortalRender == 3)
		{
			immortalRender = 0;
			return;
		}
		immortalRender++;
	}

	if (hasStar)
		if (!hasStarRender)
		{
			hasStarRender = true;
			return;
		}
	hasStarRender = false;
	RECT screen = GlobalHandler::screen;
	sprite->Render(GlobalHandler::directX->backbuffer, recDrawArea.left - screen.left, recDrawArea.top - screen.top);
}

void Player::CheckImmortal()
{
	if (immortal == true)
	{
		DWORD now = GetTickCount();
		if (now - beginImmortal > timeInImmortal)
			immortal = false;
	}

	if (hasStar == true)
	{
		DWORD now = GetTickCount();
		if (now - startHasStar > timeHasStar)
			hasStar = false;
	}
}

void Player::ChangeModeLoop()
{
	if (loop)
	{
		DWORD now = GetTickCount();
		if (now - beginLoop > timeInLoop)
		{
			loop = false;
			if (kindLoop != endMode)
				ChangeMode(endMode);

			return;
		}

		if (now - lastLoop > rateLoop)
		{
			if (kindLoop == startMode)
			{
				ChangeMode(endMode);
				kindLoop = endMode;
			}
			else
			{
				ChangeMode(startMode);
				kindLoop = startMode;
			}

			iKind = endMode;
			lastLoop = now;
		}
	}
}

void Player::ChangeMode( int mode )
{
	if (kindLoop == PLAYER_KID)
	{
		UpdateRect(recDrawArea.left - ListTexture::TT_MARIO_ADULT_WIDTH + ListTexture::TT_MARIO_KID_WIDTH,
			recDrawArea.top - ListTexture::TT_MARIO_ADULT_HEIGHT + ListTexture::TT_MARIO_KID_HEIGHT);
		if (mode == PLAYER_ADULT)
			setAdult();
		else
			setGun();
	}
	else
		if (kindLoop == PLAYER_ADULT || kindLoop == PLAYER_ADULT_GUN)
		{
			if (mode == PLAYER_KID)
			{
				setKid();
				UpdateRect(recDrawArea.left + ListTexture::TT_MARIO_ADULT_WIDTH - ListTexture::TT_MARIO_KID_WIDTH,
					recDrawArea.top + ListTexture::TT_MARIO_ADULT_HEIGHT - ListTexture::TT_MARIO_KID_HEIGHT);
			}
			else
				if (mode == PLAYER_ADULT)
					setAdult();
				else
					setGun();
		}
}

bool Player::KillEnemy( DynamicObject* enemy )
{
	if (hasStar)
	{
		((Enemy*)enemy)->MoveToHell();
		return true;
	}

	//Mario can kill enemy if he is on falling down mode.
	if (fYVelocity < -20)
	{
		//Change enemy to a harmless thing and let it kill itself.
		enemy->ProcessDying();
		enemy->Update();
		
		fYOldVelocity = 20;
		return true;
	}
	return false;
}

void Player::CollideBonus( DynamicObject* obj )
{
	BonusMushroom* bonus = (BonusMushroom*)obj;
	loop = true;
	beginLoop = GetTickCount();
	startMode = endMode = kindLoop = iKind;

	if (bonus->getBonusType() == STAR)
	{
		loop = false;
		hasStar = true;
		startHasStar = GetTickCount();
	///	immortal = true;
	}

	if (bonus->getBonusType() == GUN)
	{
		if (iKind == PLAYER_KID)
		{
			startMode = kindLoop = PLAYER_KID;
			endMode = PLAYER_ADULT;

			GlobalHandler::sound->Play(ListSound::SOUND_POWERUP, false);
		}
		if (iKind == PLAYER_ADULT)
		{
			if (hasGun == false)
			{
				startMode = kindLoop = PLAYER_ADULT;
				endMode = PLAYER_ADULT_GUN;
				hasGun = true;
				
				GlobalHandler::sound->Play(ListSound::SOUND_POWERUP, false);
			}
		}
	}
	if (bonus->getBonusType() == GROWUP)
	{
		if (iKind == PLAYER_KID)
		{
			startMode = kindLoop = PLAYER_KID;
			endMode = PLAYER_ADULT;

			GlobalHandler::sound->Play(ListSound::SOUND_POWERUP, false);
		}
	}
	if (bonus->getBonusType() == LIFE)
	{
		life++;
		GlobalHandler::sound->Play(ListSound::SOUND_LIFE, false);
		loop = false;
	}

	GlobalHandler::dynamicObjManager->Remove(obj);
}

void Player::CollideTurle( DynamicObject* turle )
{
	CollideMushRoomEnemy(turle);
}
void Player::CollideTurleDeath( DynamicObject* enemy )
{	
	if (hasStar)
		((Enemy*)enemy)->MoveToHell();

	if (enemy->fYVelocity == 0 && onGround == true && enemy->fXOldVelocity == 0)
	{
		((TurleEnemy*)(enemy))->setDeathMoving();

		GlobalHandler::sound->Play(ListSound::SOUND_KICK, false);
		trace(L"void Player::CollideTurleDeath( DynamicObject* enemy ) moving");
		return;
	}

	if (enemy->fYVelocity == 0 && enemy->fXOldVelocity != 0)
	{
		Die();
		trace(L"void Player::CollideTurleDeath( DynamicObject* enemy ) die");
		return;
	}
}

void Player::DieRightAway()
{
	fYOldVelocity = 50;
	fXOldVelocity = 0;
	fXVelocity = 0;
	acceleration = 0;
	life --;

	//This game is over.
	if (life < 0)
		GlobalHandler::txt->gameOver = true;

	alive = DYING;
	setKid();

	GlobalHandler::sound->Stop(ListSound::SOUND_BACKGROUND);
	GlobalHandler::sound->Play(ListSound::SOUND_DEAD, false);
}

void Player::ProcessDying()
{
	if (recRealArea.top > SCREEN_HEIGHT || recRealArea.top < -100)
	{
		if (alive == ALIVE)
		{
			DieRightAway();
			return;
		}

		UpdateRect(GlobalHandler::checkpoint[0][lastCheckPoint], GlobalHandler::checkpoint[1][lastCheckPoint]);
		GlobalHandler::UpdateScreen();
		alive = ALIVE;
		setKid();

		GlobalHandler::sound->Play(ListSound::SOUND_BACKGROUND, true);
	}

	if (recRealArea.left >= GlobalHandler::screen.right)
	{
		GlobalHandler::levelTime --;
		GlobalHandler::playerScore += 100;

		if (GlobalHandler::levelTime < 0)
		{
			GlobalHandler::mapLevel++;
			GlobalHandler::gameState = GS_CHANGEMAP;
		}
	}
}

void Player::CollideOutCoin( StaticObject* coin )
{
	CollectCoin();

	GlobalHandler::quadTree->RemoveObj(coin);
	GlobalHandler::sound->Play(ListSound::SOUND_COIN, false);
}

void Player::CollectCoin()
{
	GlobalHandler::playerCoin ++;
	if (GlobalHandler::playerCoin == 100)
	{
		GlobalHandler::playerCoin = 0;
		life++;

		GlobalHandler::sound->Play(ListSound::SOUND_LIFE, false);
	}

}

void Player::Die()
{
	//If mario in immortal mode, it cant die.
	if (immortal == true)
		return;

	if (iKind == PLAYER_ADULT || iKind == PLAYER_ADULT_GUN)
	{
		/*if (iKind == PLAYER_ADULT)
			startMode = PLAYER_ADULT;
		else
			startMode = PLAYER_ADULT_GUN;*/
		startMode = kindLoop = iKind;

		endMode = PLAYER_KID;
		immortal = true;
		loop = true;
		beginImmortal = GetTickCount();
		beginLoop = GetTickCount();
	}
	if (iKind == PLAYER_KID)
	{
		DieRightAway();
	}
}

void Player::CollidePirhanaPlant(DynamicObject* obj)
{
	if (hasStar)
		obj->alive = INHELL;

	if (((PirhanaPlant*)obj)->appear != 0)
		Die();
}

void Player::CollideEndMap( StaticObject* obj )
{
	EndMap* endMap = (EndMap*)obj;
	endMap->isSolid = false;
	getEndMap = true;

	acceleration = 0;
	fXOldVelocity = fXVelocity = maxSpeed;
}

void Player::UpdateCheckPoint()
{
	if (lastCheckPoint < GlobalHandler::checkpoint_index - 1 && recRealArea.left > GlobalHandler::checkpoint[0][lastCheckPoint + 1])
		lastCheckPoint++;
}

void Player::setLife( int l )
{
	life = l;
}

void Player::setCheckPoint( int cp )
{
	lastCheckPoint = cp;
}

void Player::InitFromFile( int outMode, int outLastCheckPoint, int outLife )
{
	hasGun = false;
	if (outMode == PLAYER_KID)
		setKid();
	else if (outMode == PLAYER_ADULT)
		setAdult();
	else
	{
		setGun();
		hasGun = true;
	}
	lastCheckPoint = outLastCheckPoint;
	UpdateRect(GlobalHandler::checkpoint[0][lastCheckPoint], GlobalHandler::checkpoint[1][lastCheckPoint]);
	life = outLife;
}

bool Player::CheckCollisionAgain( DynamicObject* obj )
{
	if (CheckRectInRect(this->recRealArea, obj->recRealArea) == true ||
		CheckRectInRect(obj->recRealArea, this->recRealArea) == true)
		return true;
	
	return false;
}

bool Player::CheckRectInRect( RECT mainRect, RECT checkRect )
{
	if (CheckPointInRect(checkRect.left, checkRect.top, mainRect) ||
		CheckPointInRect(checkRect.right - 1, checkRect.top, mainRect) ||
		CheckPointInRect(checkRect.left, checkRect.bottom - 1, mainRect) ||
		CheckPointInRect(checkRect.right - 1, checkRect.bottom - 1, mainRect) ||
		(mainRect.top>=checkRect.top&&mainRect.bottom<=checkRect.bottom&&checkRect.left<=mainRect.left&&checkRect.right>=mainRect.right))
		return true;
	return false;
}

// Check to see if point(x,y) is in the rect.
bool Player::CheckPointInRect( int x, int y, RECT rect )
{
	if ((x >= rect.left) &&
		(x < rect.right) &&
		(y >= rect.top) &&
		(y < rect.bottom))
		return true;
	return false;
}
Player::~Player(void)
{
}
