#include "Player.h"
#include "GlobalHandler.h"
#include "Collision.h"
#include "ListSound.h"
#include "BonusMushroom.h"
#include "TurtleEnemy.h"
#include "PirhanaPlant.h"
#include "Bullet.h"
#include "EndMap.h"

Player::Player(void){}

Player::~Player(void){}

void Player::Init(int left, int top, int mode, int LastCheckPoint, int Life, int iid){

	sprite = new Sprite();
	InitFromFile(left, top, mode, LastCheckPoint, Life);
	Vx = Vx_old = 0;
	Vy = Vy_old = 0;
	acceleration = 0;

	id = iid;
	animatedRate = ListTexture::TT_MARIO_KID_ANIMATED_RATE;
	lastAnimate = GetTickCount();
	lastUpdate = GetTickCount();

	maxSpeed = 0.25f;

	alive = ALIVE;

	onGround = false;
	jumping = false;
	touchCross = false;
	oldDirect = true;

	loop = false;
	beginLoop = GetTickCount();
	endMode = PLAYER_ADULT;
	rateLoop = 100;
	lastLoop = GetTickCount();
	timeInLoop = 1000;

	hasStar = false;
	hasStarRender = false;
	timeHasStar = 10000;
	startHasStar = GetTickCount();

	immortal = false;
	immortalRender = 0;
	beginImmortal = GetTickCount();
	timeInImmortal = 1500;

	lastShot = GetTickCount();
	delayShot = 200;
	numOfBullet = 0;

	getEndMap = false;

	ConUpdate = false;
	start = true;
	trace(L"Player::Init(int mode,int LastCheckPoint, int Life)");
}

void Player::InitFromFile(int left, int top, int mode,int LastCheckPoint, int Life){
	
	hasGun = false;
	switch(mode)
	{
		case PLAYER_KID:
			setKid();
			break;
		case PLAYER_ADULT:
			setAdult();
			break;
		case PLAYER_ADULT_GUN:
			setGun();
			hasGun = true;
	}
	lastCheckPoint = LastCheckPoint;
	//checkpoint
	UpdateRect(left, top + 50);
	life = Life;	
	//trace(L"Player::InitFromFile(int mode,int LastCheckPoint, int Life)");
}

void Player::setKid(){
	sprite->Reset(ListTexture::TT_MARIO_KID,
		ListTexture::TT_MARIO_KID_WIDTH,
		ListTexture::TT_MARIO_KID_HEIGHT,
		ListTexture::TT_MARIO_KID_COUNT,
		ListTexture::TT_MARIO_KID_SPRITEPERROW);

	isKind = PLAYER_KID;
	hasGun = false;
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

	isKind = PLAYER_ADULT;
	hasGun = false;
	width = ListTexture::TT_MARIO_ADULT_WIDTH;
	height = ListTexture::TT_MARIO_ADULT_HEIGHT;

	animatedRate = ListTexture::TT_MARIO_ADULT_ANIMATED_RATE;

	//frame index.
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

	isKind = PLAYER_ADULT_GUN;
	hasGun = true;
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

void Player::Render(){

	if (immortal)
	{
		if (immortalRender == 1)
		{
			immortalRender++;
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
		else
		{
			hasStarRender = false;
		}

	RECT screen = GlobalHandler::screen;
	sprite->Render(GlobalHandler::_directX->_backBuffer, rectDraw.left, rectDraw.top, screen.left, screen.bottom);

}

void Player::Update(){

	if (life < 0)
		return;

	ProcessDying();

	//Neu ma mario no di het map roi thi dung co update nua
	if (getEndMap && rectDraw.left > GlobalHandler::screen.right)
		return;

	DWORD now = GetTickCount();
	DWORD t = now - lastUpdate;	
	lastUpdate = now;

	oldTop = rectDraw.top;

	Vx = Vx_old + acceleration * t;
	Vy = Vy_old - 0.05f;

	Vx = (Vx < maxSpeed)?Vx:maxSpeed;
	Vx = (Vx > -maxSpeed)?Vx:(-maxSpeed);

	Vx = (getEndMap)?maxSpeed:Vx;
	
	VxF = Vx * t;
	VyF = Vy * t;
	
	Vy_old = Vy;
	Vx_old = Vx;

	

	if (alive != DYING) // co cai nay khi chet thi no se vao ham ProcessDying
	{
		CollideWithStaticObj();
		CollideWithDynamicObj(t);
	}	

	if (ConUpdate == false)
	{						
		marioBox.x += VxF;
		marioBox.y += VyF;
		UpdateRect((int)marioBox.x, (int)marioBox.y);		
	}	

	if (oldTop != rectDraw.top && touchCross == false)
	{
		onGround = false;
	}	

	ChangeModeLoop();
	CheckImmortal();
	UpdateSprite();
	UpdateCheckPoint();
	GlobalHandler::UpdateScreen();

}

void Player::ProcessInput(){

	if (alive == DYING || getEndMap)
		return;

	if (GlobalHandler::_directX->IsKeyDown(DIK_LEFT))
	{
		if (onGround == false)
		{
			Vx_old = -0.30f; // Khong co cai nay nhay len la khong sang phai trai dc
			acceleration = 0;
		}
		else{
			acceleration = -0.003f;
		}		
		oldDirect = false;
	}
	else if (GlobalHandler::_directX->IsKeyDown(DIK_RIGHT))
	{
		if (onGround == false)
		{
			Vx_old = 0.30f;
			acceleration = 0;
		}
		else
		{
			acceleration = 0.003f;
		}
		//Vx = 30;
		//Vx_old = Vx;
		oldDirect = true;
	} else {
		acceleration = 0;
		Vx = Vx_old = 0;
	}

}

void Player::OnKeyDown(int keyCode){

	if (alive == DYING || getEndMap)
		return;

	switch(keyCode){
		case DIK_ESCAPE:			
			GlobalHandler::gameState = GS_GAMEOPTION;
			break;			
		case DIK_UP:
			if (jumping == false && onGround == true)
			{
				onGround = false;
				jumping = true;
				Vy_old = 0.75f;
				GlobalHandler::sound->Play(ListSound::SOUND_JUMP, FALSE);
			}			
			break;
		case DIK_Z:
			if (!hasGun)
				break;
			if (numOfBullet > 1)
				break;
			DWORD now = GetTickCount();
			if (now - lastShot < delayShot)
				break;
			lastShot = now;
			numOfBullet++;
			
			Bullet *bullet;
			if (oldDirect == true)
			{
				bullet = new Bullet(rectDraw.right - 10, rectDraw.top - 25);
				bullet->setDirect(RIGHT);
			}
			else
			{
				bullet = new Bullet(rectDraw.left + 10, rectDraw.top - 25);
				bullet->setDirect(LEFT);
			}

			GlobalHandler::dynamicObjManager->Add(bullet);
			GlobalHandler::sound->Play(ListSound::SOUND_FIREBALL, false);
			break;
	}
}

void Player::UpdateSprite()
{	
	if (alive == DYING)
	{
		sprite->Next(ListTexture::TT_MARIO_KID_DEATH_START, ListTexture::TT_MARIO_KID_DEATH_END);
		return;
	}
	
	DWORD now = GetTickCount();
	
	if (now - lastAnimate > 1000 / animatedRate)
	{
		lastAnimate = now;
		if (onGround == false || jumping == true)
		{
			if (oldDirect == true)
				sprite->Next(frame_jumping_right_start,frame_jumping_right_end);
			else if (oldDirect == false)
				sprite->Next(frame_jumping_left_start, frame_jumping_left_end);
		} 
		else 
		{
			if (Vx > 0.0f)
				sprite->Next(frame_moving_right_start, frame_moving_right_end);
			else
				if (Vx < 0.0f)
					sprite->Next(frame_moving_left_start, frame_moving_left_end);
				else
					if (oldDirect == true)
						sprite->Next(frame_moving_right_start, frame_moving_right_start);
					else
						sprite->Next(frame_moving_left_start, frame_moving_left_start);
		}
	}
}

void Player::CollideWithStaticObj(){	

	UpdateMarioBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, VxF, VyF);
	
	list<StaticObject*>::iterator it;
	for (it = GlobalHandler::listStaticObjRender.begin(); it != GlobalHandler::listStaticObjRender.end(); ++it)
	{
		if ((*it)->isSolid == true)
		{
			Box broadphasebox = GlobalHandler::Physic->GetSweptBroadphaseBox(marioBox);
			Box staticBox((float)(*it)->rectDraw.left, (float)(*it)->rectDraw.top, (float)(*it)->width, (float)(*it)->height, 0.0f, 0.0f);
		
			if (GlobalHandler::Physic->AABBCheck(broadphasebox, staticBox))
			{
				ConUpdate = true;
				float normalx, normaly, collisiontime;
				collisiontime = GlobalHandler::Physic->SweptAABB(marioBox, staticBox,  normalx, normaly);
				if (collisiontime < 1.0f && collisiontime >= 0.0f)
				{				
					if ((*it)->isKind == GROUND || (*it)->isKind == GROUNDUNDERMUSHROOM)			
						CollideWithGround(normalx, normaly, collisiontime, (*it));		
					if ((*it)->isKind == PIPE_1 || (*it)->isKind == PIPE_2 || (*it)->isKind == PIPE_3 ||
						(*it)->isKind == PIPE_4 || (*it)->isKind == PIPE_5)
						CollideWithPiPe(normalx, normaly, collisiontime, (*it));
					if ((*it)->isKind == HARDBRICK || (*it)->isKind == STATIC_CROSS)				
						CollideWithHardBrick(normalx, normaly, collisiontime, (*it));
					if ((*it)->isKind == OUTCOIN)				
						CollideWithCoin((*it));
					if ((*it)->isKind == BRICK || (*it)->isKind == BRICK_BONUS_COIN || (*it)->isKind == BRICK_BONUS_GUN || 
							(*it)->isKind == BRICK_BONUS_LIFE || (*it)->isKind == BRICK_BONUS_LIFE_HIDDEN || (*it)->isKind == BRICK_BONUS_MUSHROOM || 
								(*it)->isKind == BRICK_BONUS_STAR)				
						CollideWithBrick(normalx, normaly, collisiontime, (*it));
					if ((*it)->isKind == PIRHANAPLANT)
						CollideWithPirhanaPlant((*it));
					if ((*it)->isKind == ENDMAP)				
						CollideWithEndMap(normalx, normaly, collisiontime, (*it));
					if ((*it)->isKind == FALLING_CROSS)				
						CollideWithFallingCross(normalx, normaly, collisiontime, (*it));
				}
				if (collisiontime == 1.0f)
				{
					ConUpdate = false;
				}
			}
		}
		
	}	
	
}

void Player::CollideWithDynamicObj(int t){
	list<DynamicObject*> result;
	list<DynamicObject*>::iterator it;
	for (it = GlobalHandler::dynamicObjManager->listDynamicObj.begin(); it != GlobalHandler::dynamicObjManager->listDynamicObj.end(); ++it)
	{
		if ((this) != (*it))		
			if ((*it)->isSolid == true)
			{
				float Obj_VxF = (*it)->Vx * t;
				float Obj_VyF = (*it)->Vy * t;
				float VxFN = VxF - Obj_VxF;
				float VyFN = VyF - Obj_VyF;
				UpdateMarioBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, VxFN, VyFN);
				Box broadphasebox = GlobalHandler::Physic->GetSweptBroadphaseBox(marioBox);
				Box staticBox((float)(*it)->rectDraw.left, (float)(*it)->rectDraw.top, (float)(*it)->width, (float)(*it)->height, 0.0f, 0.0f);
				if (GlobalHandler::Physic->AABBCheck(broadphasebox, staticBox))
				{
					ConUpdate = true;
					float normalx, normaly, collisiontime;
					collisiontime = GlobalHandler::Physic->SweptAABB(marioBox, staticBox,  normalx, normaly);
					if (collisiontime < 1.0f && collisiontime >= 0.0f)
					{
						if ((*it)->isKind == BONUS_MUSHROOM)
							CollideWithBonusMushRoom((*it));
						if ((*it)->isKind == MUSHROOM_ENEMY)
							CollideWithMushRoomEnemy(normaly, (*it));
						if ((*it)->isKind == TURTLE || (*it)->isKind == RED_TURTLE)
							CollideWithTurtleEnemy(normaly, (*it));
						if ((*it)->isKind == TURTLEDEATH || (*it)->isKind == RED_TURTLE_DEATH)
							CollideWithTurtleDeath(normaly, (*it));						
						if ((*it)->isKind == BULLET)
							ConUpdate = false;
						if ((*it)->isKind == CROSS)
							CollideWithCross(normalx, normaly, collisiontime, (*it));
					}
					if (collisiontime == 1.0f)
						ConUpdate = false;
											
				}
			}		
	}

}

void Player::CollideWithGround(float normalx, float normaly, float collisiontime, StaticObject *obj)
{
	//Va cham o tren
	if (normaly == 1.0f)
	{		
		if (rectDraw.right < obj->rectDraw.left + 1)
		{
			ConUpdate = false;			
			return;
		}
		Vy = 0;
		Vy_old = 0.05f;		

		onGround = true;
		jumping = false;
		touchCross = false;
		
		marioBox.y += VyF * collisiontime;
		UpdateRect((int)marioBox.x, (int)marioBox.y);
		
		UpdateMarioBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, VxF, 0);
		
		VyF = 0;
		ConUpdate = false;

		//trace(L"Cl x: %f, y: %f, w: %f, h: %f, vx: %f, vy: %f", marioBox.x, marioBox.y, marioBox.w, marioBox.h, marioBox.vx, marioBox.vy);
		//trace(L"::CollideWithGround Up");
	}
	else
	{
		if (normaly == -1.0f)
		{
			Vy = 0;
			Vy_old = 0.05f;			

			marioBox.y += VyF * collisiontime;
			UpdateRect((int)marioBox.x, (int)marioBox.y);
			
			UpdateMarioBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, VxF, 0);

			//Set gia tri ve de ma tiep tuc xet va cham			
			VyF = 0;
			ConUpdate = false;

			//trace(L"Cl x: %f, y: %f, w: %f, h: %f, vx: %f, vy: %f", marioBox.x, marioBox.y, marioBox.x, marioBox.h, marioBox.vx, marioBox.vy);
			//trace(L"::CollideWithGround Down");
		}
		else
		{		
			if (rectDraw.top < obj->rectDraw.top + 30 && rectDraw.top > obj->rectDraw.top - 32)
			{
				if (normalx == -1.0f)
				{
					marioBox.x = obj->rectDraw.left - rectDraw.right + rectDraw.left;
					UpdateRect((int)marioBox.x, (int)marioBox.y);
				}
				else
				{
					marioBox.x = obj->rectDraw.right + 1;
					UpdateRect((int)marioBox.x, (int)marioBox.y);
				}

				Vx = Vx_old = acceleration = 0;			
				VxF = 0;			

				UpdateMarioBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, 0, VyF);
			}
			ConUpdate = false;			
			//trace(L"::CollideWithGround Left or Right");			
		}
	}
}

void Player::CollideWithPiPe(float normalx, float normaly, float collisiontime,  StaticObject *obj)
{
	if (normaly == 1.0f)
	{		
		if (rectDraw.right < obj->rectDraw.left + 1)
		{
			ConUpdate = false;
			trace(L"Right: %d, OBJleft: %d", rectDraw.right , obj->rectDraw.left + 1);
			return;
		}
		Vy = 0;
		Vy_old = 0.05f;		

		onGround = true;
		jumping =false;
		touchCross = false;
		
		marioBox.y += VyF * collisiontime;
		UpdateRect((int)marioBox.x, (int)marioBox.y);
		
		UpdateMarioBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, VxF, 0);

		//Set gia tri ve de ma tiep tuc xet va cham
		//VxF = 0;
		VyF = 0;
		ConUpdate = false;
		
		//trace(L"Cl x: %f, y: %f, w: %f, h: %f, vx: %f, vy: %f", marioBox.x, marioBox.y, marioBox.x, marioBox.h, marioBox.vx, marioBox.vy);
		//trace(L"::CollideWithPipe Up");
	}
	else
	{
		if (normaly == -1.0f)
		{			
						
		}
		else
		{
			Vx = Vx_old = acceleration = 0;			
			VxF = 0;
			if (normalx == -1.0f)
			{
				marioBox.x = obj->rectDraw.left - rectDraw.right + rectDraw.left;
				UpdateRect((int)marioBox.x, (int)marioBox.y);
			}
			else
			{
				marioBox.x = obj->rectDraw.right + 1;
				UpdateRect((int)marioBox.x, (int)marioBox.y);
			}				

			UpdateMarioBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, 0, VyF);
						
			ConUpdate = false;
			//trace(L"::CollideWithPiPe Left or Right");		
		}
	}
}

void Player::CollideWithHardBrick(float normalx, float normaly, float collisiontime, StaticObject *obj)
{
	if (normaly == 1.0f)
	{	
		if (rectDraw.right < obj->rectDraw.left + 2 || rectDraw.left > obj->rectDraw.right - 2)
		{
			ConUpdate = false;			
			return;
		}
		Vy = 0;
		Vy_old = 0.05f;		

		onGround = true;
		jumping =false;
		touchCross = false;

		marioBox.y += VyF * collisiontime;
		UpdateRect((int)marioBox.x, (int)marioBox.y);

		UpdateSprite();
		UpdateMarioBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, VxF, 0);

		//Set gia tri ve de ma tiep tuc xet va cham
		//VxF = 0;
		VyF = 0;
		ConUpdate = false;

		//trace(L"Cl x: %f, y: %f, w: %f, h: %f, vx: %f, vy: %f", marioBox.x, marioBox.y, marioBox.x, marioBox.h, marioBox.vx, marioBox.vy);
		//trace(L"::CollideWithHardBrick Up");
	}
	else
	{
		if (normaly == -1.0f)
		{		
			if (rectDraw.right < obj->rectDraw.left + 2 || rectDraw.left > obj->rectDraw.right - 2)
			{
				ConUpdate = false;				
				return;
			}
			Vy = 0;
			Vy_old = 0.05f;			

			marioBox.y += VyF * collisiontime;
			UpdateRect((int)marioBox.x, (int)marioBox.y);

			UpdateSprite();
			UpdateMarioBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, VxF, 0);

			//Set gia tri ve de ma tiep tuc xet va cham			
			VyF = 0;
			ConUpdate = false;

			//trace(L"Cl x: %f, y: %f, w: %f, h: %f, vx: %f, vy: %f", marioBox.x, marioBox.y, marioBox.x, marioBox.h, marioBox.vx, marioBox.vy);
			//trace(L"::CollideWithHardBrick Down");
		}
		else
		{
			if (rectDraw.top < obj->rectDraw.top + 30 && rectDraw.top > obj->rectDraw.top - 32)
			{
				if (normalx == -1.0f)
				{
					marioBox.x = obj->rectDraw.left - rectDraw.right + rectDraw.left;
					UpdateRect((int)marioBox.x, (int)marioBox.y);
				}
				else
				{
					marioBox.x = obj->rectDraw.right + 1;
					UpdateRect((int)marioBox.x, (int)marioBox.y);
				}

				Vx = Vx_old = acceleration = 0;			
				VxF = 0;

				UpdateMarioBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, 0, VyF);
			}
			ConUpdate = false;
			//trace(L"::CollideWithHardBrickLeft or Right");		
		}
	}
}

void Player::CollideWithCoin(StaticObject *obj)
{
	CollectCoin();
	GlobalHandler::quadTree->RemoveObj(obj);
	GlobalHandler::sound->Play(ListSound::SOUND_COIN, false);
	ConUpdate = false;
	//trace(L"::CollideWithCoin");
}

void Player::CollectCoin(){
	GlobalHandler::playerCoin ++;
	if (GlobalHandler::playerCoin == 100)
	{
		GlobalHandler::playerCoin = 0;
		life++;
		GlobalHandler::sound->Play(ListSound::SOUND_LIFE, false);
	}
}

void Player::CollideWithBrick(float normalx, float normaly, float collisiontime, StaticObject *obj)
{
	if (normaly == 1.0f)
	{	
		if (rectDraw.right < obj->rectDraw.left + 2 || rectDraw.left > obj->rectDraw.right - 2)
		{
			ConUpdate = false;			
			return;
		}
		Vy = 0;
		Vy_old = 0.05f;		

		onGround = true;
		jumping =false;
		touchCross = false;

		marioBox.y += VyF * collisiontime;
		UpdateRect((int)marioBox.x, (int)marioBox.y);
		
		UpdateMarioBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, VxF, 0);

		//Set gia tri ve de ma tiep tuc xet va cham
		//VxF = 0;
		VyF = 0;
		ConUpdate = false;

		//trace(L"Cl x: %f, y: %f, w: %f, h: %f, vx: %f, vy: %f", marioBox.x, marioBox.y, marioBox.x, marioBox.h, marioBox.vx, marioBox.vy);
		//trace(L"::CollideWithBrick Up");
	}
	else
	{
		if (normaly == -1.0f)
		{		
			if (rectDraw.right < obj->rectDraw.left + 2 || rectDraw.left > obj->rectDraw.right - 2)
			{
				ConUpdate = false;				
				return;
			}
			obj->ProcessCollision(isKind);			
			
			Vy = 0;
			Vy_old = 0.05f;			

			marioBox.y += VyF * collisiontime;
			UpdateRect((int)marioBox.x, (int)marioBox.y);
			
			UpdateMarioBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, VxF, 0);

			//Set gia tri ve de ma tiep tuc xet va cham			
			VyF = 0;
			ConUpdate = false;

			//trace(L"Cl x: %f, y: %f, w: %f, h: %f, vx: %f, vy: %f", marioBox.x, marioBox.y, marioBox.x, marioBox.h, marioBox.vx, marioBox.vy);
			//trace(L"::CollideWithBrick Down");
		}
		else
		{
			if (rectDraw.top < obj->rectDraw.top + 30 && rectDraw.top > obj->rectDraw.top - 32)
			{
				if (normalx == -1.0f)
				{
					marioBox.x = obj->rectDraw.left - rectDraw.right + rectDraw.left;
					UpdateRect((int)marioBox.x, (int)marioBox.y);
				}
				else
				{
					marioBox.x = obj->rectDraw.right + 1;
					UpdateRect((int)marioBox.x, (int)marioBox.y);
				}

				Vx = Vx_old = acceleration = 0;			
				VxF = 0;

				UpdateMarioBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, 0, VyF);
			}
			ConUpdate = false;
			//trace(L"::CollideWithBrickLeft or Right");		
		}
	}
}

void Player::CollideWithEndMap(float normalx, float normaly, float collisiontime, StaticObject *obj){
	EndMap* endMap = ((EndMap*)obj);
	endMap->isSolid = false;

	getEndMap = true;
	Vx = Vx_old = maxSpeed;
	ConUpdate = false;
}

void Player::CollideWithFallingCross(float normalx, float normaly, float collisiontime, StaticObject *obj){

	if (normaly == 1.0f)
	{	
		if (rectDraw.right < obj->rectDraw.left + 2 || rectDraw.left > obj->rectDraw.right - 2)
		{
			ConUpdate = false;			
			return;
		}
		Vy = 0;
		Vy_old = 0.05f;		

		onGround = true;
		jumping =false;
		touchCross = true;

		marioBox.y += VyF * collisiontime;
		UpdateRect((int)marioBox.x, (int)marioBox.y);

		UpdateSprite();
		UpdateMarioBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, VxF, 0);
		
		VyF = 0;
		ConUpdate = false;

	}
	else
	{
		if (normaly == -1.0f)
		{		
			if (rectDraw.right < obj->rectDraw.left + 2 || rectDraw.left > obj->rectDraw.right - 2)
			{
				ConUpdate = false;				
				return;
			}
			Vy = 0;
			Vy_old = 0.05f;			

			marioBox.y += VyF * collisiontime;
			UpdateRect((int)marioBox.x, (int)marioBox.y);

			UpdateSprite();
			UpdateMarioBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, VxF, 0);

			//Set gia tri ve de ma tiep tuc xet va cham			
			VyF = 0;
			ConUpdate = false;
			
		}
		else
		{			
			if (normalx == -1.0f)
			{
				marioBox.x = obj->rectDraw.left - rectDraw.right + rectDraw.left;
				UpdateRect((int)marioBox.x, (int)marioBox.y);
			}
			else
			{
				marioBox.x = obj->rectDraw.right + 1;
				UpdateRect((int)marioBox.x, (int)marioBox.y);
			}

			Vx = Vx_old = acceleration = 0;			
			VxF = 0;

			UpdateMarioBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, 0, VyF);

			ConUpdate = false;
					
		}
	}
	obj->ProcessCollision(isKind);
}

void Player::CollideWithBonusMushRoom(DynamicObject *obj){

	BonusMushroom* bonus = (BonusMushroom*)obj;
	loop = true;
	beginLoop = GetTickCount();
	startMode = endMode = kindLoop = isKind;

	if (bonus->getBonusType() == STAR)
	{
		loop = false;
		hasStar = true;
		startHasStar = GetTickCount();
	}

	if (bonus->getBonusType() == GROWUP)
	{
		if (isKind == PLAYER_KID)
		{
			startMode = kindLoop = PLAYER_KID;
			endMode = PLAYER_ADULT;

			GlobalHandler::sound->Play(ListSound::SOUND_POWERUP, false);
		}
	}

	if (bonus->getBonusType() == GUN)
	{
		if (isKind == PLAYER_KID)
		{
			startMode = kindLoop = PLAYER_KID;
			endMode = PLAYER_ADULT;

			GlobalHandler::sound->Play(ListSound::SOUND_POWERUP, false);
		}
		if (isKind == PLAYER_ADULT)
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

	if (bonus->getBonusType() == LIFE)
	{
		life++;
		GlobalHandler::sound->Play(ListSound::SOUND_LIFE, false);
		loop = false;
	}

	GlobalHandler::listRemove.push_back(obj);
	ConUpdate = false;
}

void Player::CollideWithTurtleEnemy(float normaly,DynamicObject *obj){

	if (!immortal)
	{		
		if (!KillEnemy(obj, normaly))
		{
			Die();
		}
		else
		{
			Score* score = new Score(rectDraw.left, rectDraw.top);
			score->setScore(200);
			GlobalHandler::dynamicObjManager->Add(score);

			GlobalHandler::sound->Play(ListSound::SOUND_MIP, false);
		}
	}
	ConUpdate = false;

}

void Player::CollideWithTurtleDeath(float normaly, DynamicObject *obj){

	if (hasStar)
	{
		((Enemy*)obj)->MoveToHell();	
		return;
	}
	
	TurtleEnemy* turtle = ((TurtleEnemy*)obj);

	if (turtle->Vx == 0.0f && turtle->Vy == 0.0f && turtle->onGround == true)
	{		
		turtle->setDeathMoving();
		GlobalHandler::sound->Play(ListSound::SOUND_KICK, false);
		ConUpdate = false;
		return;
	}

	if (turtle->Vx != 0.0f )
	{		
		Die();
		ConUpdate = false;
		return;
	}
	ConUpdate = false;
}

void Player::CollideWithMushRoomEnemy(float normaly,DynamicObject *obj)
{	
	if (!immortal)
	{		
		if (!KillEnemy(obj, normaly))
		{
			Die();
		}
		else
		{
			Score* score = new Score(rectDraw.left, rectDraw.top);
			score->setScore(200);
			GlobalHandler::dynamicObjManager->Add(score);

			GlobalHandler::sound->Play(ListSound::SOUND_MIP, false);
		}
	}
	ConUpdate = false;
}

void Player::CollideWithPirhanaPlant(StaticObject *obj){
	PirhanaPlant *pirhanaPlant = ((PirhanaPlant*)obj);
	if (hasStar)
	{
		GlobalHandler::quadTree->RemoveObj(pirhanaPlant);
		return;
	}
	
	//trace(L"Rect L: %d, T: %d, R: %d, B: %d", pirhanaPlant->rectDraw.left, pirhanaPlant->rectDraw.top, pirhanaPlant->rectDraw.right, pirhanaPlant->rectDraw.bottom);
	if (pirhanaPlant->appear != 0)
	{
		Die();
	}
	ConUpdate = false;
}

void Player::CollideWithCross(float normalx, float normaly, float collisiontime, DynamicObject *obj){
	
	if (normaly == 1.0f)
	{
		
		Vy = 0.0f;
		Vy_old = 0.0f;		

		onGround = true;
		jumping = false;
		touchCross = true;

		marioBox.y += VyF * collisiontime;
		UpdateRect((int)marioBox.x, (int)marioBox.y);

		UpdateMarioBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, VxF, 0);

		VyF = 0;
		ConUpdate = false;

		//trace(L"Cl x: %f, y: %f, w: %f, h: %f, vx: %f, vy: %f", marioBox.x, marioBox.y, marioBox.w, marioBox.h, marioBox.vx, marioBox.vy);
		//trace(L"::CollideWithGround Up");
	}
	else
		ConUpdate = false;
}

void Player::ChangeMode(int mode){
	if (kindLoop == PLAYER_KID)
	{					
		if (mode == PLAYER_ADULT)
			setAdult();
		else
			setGun();
		UpdateRect(rectDraw.left, rectDraw.top + 28, ListTexture::TT_MARIO_ADULT_WIDTH, ListTexture::TT_MARIO_ADULT_HEIGHT);		
	}
	else
		if (kindLoop == PLAYER_ADULT || kindLoop == PLAYER_ADULT_GUN)
		{
			if (mode == PLAYER_KID)
			{								
				setKid();							
				UpdateRect(rectDraw.left, rectDraw.top - 28, ListTexture::TT_MARIO_KID_WIDTH, ListTexture::TT_MARIO_KID_HEIGHT);
			}
			else
				if (mode == PLAYER_ADULT)
					setAdult();
				else
					setGun();
		}
}

void Player::ChangeModeLoop(){
	if (loop)
	{
		DWORD now = GetTickCount();
		if (now - beginLoop > timeInLoop)
		{	
			loop = false;
			if (kindLoop != endMode) //No ko o dang cuoi thji chuyen no ve
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
			isKind = endMode;
			lastLoop = now;
		}
	}
}

bool Player::KillEnemy(DynamicObject *enemy, float normaly)
{
	if (hasStar)
	{
		((Enemy*)enemy)->MoveToHell();
		return true;
	}
	
	if (normaly == 1.0f)
	{				
		enemy->ProcessDying();
		enemy->Update();
		
		Vy_old = 0.4f;
		return true;
	}

	return false;
}

void Player::DieRightAway(){

	Vx = Vx_old = Vy = acceleration = 0;
	Vy_old = 0.5f;
	life--;

	alive = DYING;
	setKid();

	GlobalHandler::sound->Stop(ListSound::SOUND_BACKGROUND);
	GlobalHandler::sound->Play(ListSound::SOUND_DEAD, false);
}

void Player::Die(){
	if (immortal)
		return;
	if (isKind == PLAYER_ADULT || isKind == PLAYER_ADULT_GUN)
	{
		startMode = kindLoop = isKind;
		endMode = PLAYER_KID;
		beginLoop = GetTickCount();
		loop = true;

		immortal = true;
		beginImmortal = GetTickCount();
	}
	if (isKind == PLAYER_KID)
		DieRightAway();
}

void Player::ProcessDying(){
	if (rectDraw.top < 32)
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

	if (rectDraw.left >= GlobalHandler::screen.right)
	{
		GlobalHandler::time --;
		GlobalHandler::playerScore += 100;

		if (GlobalHandler::time < 0)
		{
			GlobalHandler::mapLevel = GlobalHandler::nextMap;
			GlobalHandler::newGame = false;
			GlobalHandler::lifeEndMap = life;
			GlobalHandler::gameState = GS_CHANGEMAP;
		}
	}
}

void Player::CheckImmortal(){

	if (immortal)
	{
		DWORD now = GetTickCount();
		if (now - beginImmortal > timeInImmortal)
			immortal = false;
	}

	if (hasStar)
	{
		DWORD now = GetTickCount();
		if (now - startHasStar > timeHasStar)
			hasStar = false;
	}
}

void Player::UpdateCheckPoint(){
	if (lastCheckPoint < GlobalHandler::checkpoint_index - 1 && rectDraw.left > GlobalHandler::checkpoint[0][lastCheckPoint + 1])
		lastCheckPoint++;
}

void Player::UpdateMarioBox(float ix, float iy, float iw, float ih, float ivx, float ivy)
{
	marioBox.x = ix;
	marioBox.y = iy;
	marioBox.w = iw;
	marioBox.h = ih;
	marioBox.vx = ivx;
	marioBox.vy = ivy;
}