#include "Player.h"
#include "GlobalHandler.h"
#include "Collision.h"
#include "ListSound.h"

Player::Player(void){}

Player::~Player(void){}

void Player::Init(int mode,int LastCheckPoint, int Life){

	sprite = new Sprite();
	InitFromFile(mode, LastCheckPoint, Life);
	Vx = Vx_old = 0;
	Vy = Vy_old = 0;
	acceleration = 0;

	animatedRate = ListTexture::TT_MARIO_KID_ANIMATED_RATE;
	lastAnimate = GetTickCount();
	lastUpdate = GetTickCount();

	maxSpeed = 0.25f;

	alive = ALIVE;

	onGround = false;
	jumping = false;
	oldDirect = true;

	ConUpdate = false;
	trace(L"Player::Init(int mode,int LastCheckPoint, int Life)");
}

void Player::InitFromFile(int mode,int LastCheckPoint, int Life){
	
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
	//cai nay de khi nao lam cai checkpoint da
	//UpdateRect(GlobalHandler::checkpoint[0][lastCheckPoint], GlobalHandler::checkpoint[1][lastCheckPoint]);
	life = Life;
	UpdateRect(0, 470);
	//trace(L"Player::InitFromFile(int mode,int LastCheckPoint, int Life)");
}

void Player::setKid(){
	sprite->Reset(ListTexture::TT_MARIO_KID,
		ListTexture::TT_MARIO_KID_WIDTH,
		ListTexture::TT_MARIO_KID_HEIGHT,
		ListTexture::TT_MARIO_KID_COUNT,
		ListTexture::TT_MARIO_KID_SPRITEPERROW);

	isKind = PLAYER_KID;

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

	RECT screen = GlobalHandler::screen;
	sprite->Render(GlobalHandler::_directX->_backBuffer, rectDraw.left, rectDraw.top, screen.left, screen.bottom);

}

void Player::Update(){

	DWORD now = GetTickCount();
	DWORD t = now - lastUpdate;	
	lastUpdate = now;	

	Vx = Vx_old + acceleration * t;
	Vy = Vy_old - 0.05f;

	Vx = (Vx < maxSpeed)?Vx:maxSpeed;
	Vx = (Vx > -maxSpeed)?Vx:(-maxSpeed);		
	
	VxF = Vx * t;
	VyF = Vy * t;
	
	Vy_old = Vy;
	Vx_old = Vx;	

	CollideWithStaticObj();

	if (ConUpdate == false)
	{						
		marioBox.x += VxF;
		marioBox.y += VyF;
		UpdateRect((int)marioBox.x, (int)marioBox.y);
		//trace(L"Update X: %d, Y: %d", (int)marioBox.x, (int)marioBox.y);
	}

	UpdateSprite();
	GlobalHandler::UpdateScreen();

}

void Player::ProcessInput(){

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
	switch(keyCode){
		case DIK_UP:
			if (jumping == false)
			{
				onGround = false;
				jumping = true;
				Vy_old = 0.75f;
				GlobalHandler::sound->Play(ListSound::SOUND_JUMP, FALSE);
			}			
			break;
	}
}

void Player::UpdateSprite()
{	
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
	
	//trace(L"BFF x: %f, y: %f, w: %f, h: %f, vx: %f, vy: %f", (float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, VxF, VyF);		
	
	list<StaticObject*>::iterator it;
	for (it = GlobalHandler::listStaticObjRender.begin(); it != GlobalHandler::listStaticObjRender.end(); ++it)
	{
		Box broadphasebox = GlobalHandler::Physic->GetSweptBroadphaseBox(marioBox);
		Box staticBox((float)(*it)->rectDraw.left, (float)(*it)->rectDraw.top, (float)(*it)->width, (float)(*it)->height, 0.0f, 0.0f);
		
		if (GlobalHandler::Physic->AABBCheck(broadphasebox, staticBox))
		{
			ConUpdate = true;
			float normalx, normaly, collisiontime;
			collisiontime = GlobalHandler::Physic->SweptAABB(marioBox, staticBox,  normalx, normaly);
			//trace(L"Broadphasebox: X: %f, Y: %f, W: %f, H: %f", broadphasebox.x, broadphasebox.y, broadphasebox.w, broadphasebox.h);
			//trace(L"AABBCheck X: %d, Y: %d, OBJX: %d, OBJY: %d, Vx: %f, Vy: %f, Time: %f, Normalx: %f, Normaly: %f, ID: %d", rectDraw.left, rectDraw.top, (*it)->rectDraw.left, (*it)->rectDraw.top, marioBox.vx, marioBox.vy, collisiontime, normalx, normaly,(*it)->id);
			if (collisiontime < 1.0f && collisiontime >= 0.0f)
			{				
				if ((*it)->isKind == GROUND)				
					CollideWithGround(normalx, normaly, collisiontime, (*it));		
				if ((*it)->isKind == PIPE_1 || (*it)->isKind == PIPE_2 || (*it)->isKind == PIPE_3)
					CollideWithPiPe(normalx, normaly, collisiontime, (*it));
				if ((*it)->isKind == HARDBRICK)				
					CollideWithHardBrick(normalx, normaly, collisiontime, (*it));
				if ((*it)->isKind == OUTCOIN)				
					CollideWithCoin((*it));
				if ((*it)->isKind == BRICK || (*it)->isKind == BRICK_BONUS_COIN || (*it)->isKind == BRICK_BONUS_GUN || 
						(*it)->isKind == BRICK_BONUS_LIFE || (*it)->isKind == BRICK_BONUS_LIFE_HIDDEN || (*it)->isKind == BRICK_BONUS_MUSHROOM || 
							(*it)->isKind == BRICK_BONUS_STAR)				
					CollideWithBrick(normalx, normaly, collisiontime, (*it));
				//trace(L"X: %d, Y:%d, Time: %f, Normalx: %f, Normaly: %f, ID: %d, Type: %d", (int)marioBox.x, (int)marioBox.y, collisiontime, normalx, normaly,(*it)->id, (*it)->isKind);
			}
			if (collisiontime == 1.0f)
			{
				ConUpdate = false;
				//trace(L"Flag = false, CollisionTime: %f", collisiontime);
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
		jumping =false;

		//marioBox.x += VxF * collisiontime;
		marioBox.y += VyF * collisiontime;
		UpdateRect((int)marioBox.x, (int)marioBox.y + 1);

		UpdateSprite();
		UpdateMarioBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, VxF, 0);
		
		//Set gia tri ve de ma tiep tuc xet va cham
		//VxF = 0;
		VyF = 0;
		ConUpdate = false;

		//trace(L"Cl x: %f, y: %f, w: %f, h: %f, vx: %f, vy: %f", marioBox.x, marioBox.y, marioBox.x, marioBox.h, marioBox.vx, marioBox.vy);
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

			UpdateSprite();
			UpdateMarioBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, VxF, 0);

			//Set gia tri ve de ma tiep tuc xet va cham			
			VyF = 0;
			ConUpdate = false;

			//trace(L"Cl x: %f, y: %f, w: %f, h: %f, vx: %f, vy: %f", marioBox.x, marioBox.y, marioBox.x, marioBox.h, marioBox.vx, marioBox.vy);
			//trace(L"::CollideWithGround Down");
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
		
		marioBox.y += VyF * collisiontime;
		UpdateRect((int)marioBox.x, (int)marioBox.y);

		UpdateSprite();
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
			//marioBox.x += VxF * collisiontime;
			//marioBox.y += VyF * collisiontime;
			//UpdateRect((int)marioBox.x, (int)marioBox.y);			

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
		if (rectDraw.right < obj->rectDraw.left + 1)
		{
			ConUpdate = false;			
			return;
		}
		Vy = 0;
		Vy_old = 0.05f;		

		onGround = true;
		jumping =false;

		marioBox.y += VyF * collisiontime;
		UpdateRect((int)marioBox.x, (int)marioBox.y + 1);

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
			if (rectDraw.right < obj->rectDraw.left + 1)
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
			//marioBox.x += VxF * collisiontime;
			//marioBox.y += VyF * collisiontime;
			//UpdateRect((int)marioBox.x, (int)marioBox.y);
			Vx = Vx_old = acceleration = 0;			
			VxF = 0;

			UpdateMarioBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, 0, VyF);

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
		if (rectDraw.right < obj->rectDraw.left + 1)
		{
			ConUpdate = false;			
			return;
		}
		Vy = 0;
		Vy_old = 0.05f;		

		onGround = true;
		jumping =false;

		marioBox.y += VyF * collisiontime;
		UpdateRect((int)marioBox.x, (int)marioBox.y + 1);

		UpdateSprite();
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
			if (rectDraw.right < obj->rectDraw.left + 1)
			{
				ConUpdate = false;				
				return;
			}
			obj->ProcessCollision(isKind);			
			
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
			//trace(L"::CollideWithBrick Down");
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
			//trace(L"::CollideWithBrickLeft or Right");		
		}
	}
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