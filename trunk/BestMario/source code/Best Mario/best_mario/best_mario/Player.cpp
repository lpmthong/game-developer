#include "Player.h"
#include "GlobalHandler.h"
#include "Collision.h"

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

	onGround = false;
	jumping = false;
	oldDirect = true;

	ConUpdate = false;
	trace(L"Player::Init(int mode,int LastCheckPoint, int Life)");
}

void Player::InitFromFile(int mode,int LastCheckPoint, int Life){
	if (mode == PLAYER_KID)
		setKid();
	lastCheckPoint = LastCheckPoint;
	//cai nay de khi nao lam cai checkpoint da
	//UpdateRect(GlobalHandler::checkpoint[0][lastCheckPoint], GlobalHandler::checkpoint[1][lastCheckPoint]);
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

void Player::Render(){

	RECT screen = GlobalHandler::screen;
	sprite->Render(GlobalHandler::_directX->_backBuffer, rectDraw.left, rectDraw.top, screen.left, screen.bottom);

}

void Player::Update(){

	DWORD now = GetTickCount();
	DWORD t = now - lastUpdate;	
	lastUpdate = now;
	
	/*int x = rectDraw.left;
	int y = rectDraw.top;*/

	Vx = Vx_old + acceleration * t;
	Vy = Vy_old - 0.15f;

	Vx = (Vx < maxSpeed)?Vx:maxSpeed;
	Vx = (Vx > -maxSpeed)?Vx:(-maxSpeed);	
	
	/*x += Vx * t;
	y += Vy * t;*/	
	
	VxF = Vx * t;
	VyF = Vy * t;
	
	Vy_old = Vy;
	Vx_old = Vx;
	//UpdateRect(x, y);

	CollideWithStaticObj();

	UpdateSprite();
	GlobalHandler::UpdateScreen();

}

void Player::ProcessInput(){

	if (GlobalHandler::_directX->IsKeyDown(DIK_LEFT))
	{
		if (onGround == false)
		{
			Vx_old = -0.20f; // Khong co cai nay nhay len la khong sang phai trai dc
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
			Vx_old = 0.20f;
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
				Vy_old = 1.2f;
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
	
	trace(L"BFF x: %f, y: %f, w: %f, h: %f, vx: %f, vy: %f", (float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, VxF, VyF);
	Box broadphasebox = GlobalHandler::Physic->GetSweptBroadphaseBox(marioBox);	
	
	list<StaticObject*>::iterator it;
	for (it = GlobalHandler::listStaticObjRender.begin(); it != GlobalHandler::listStaticObjRender.end(); ++it)
	{
		Box staticBox((float)(*it)->rectDraw.left, (float)(*it)->rectDraw.top, (float)(*it)->width, (float)(*it)->height, 0.0f, 0.0f);
		
		if (GlobalHandler::Physic->AABBCheck(broadphasebox, staticBox))
		{
			ConUpdate = true;
			float normalx, normaly, collisiontime;
			collisiontime = GlobalHandler::Physic->SweptAABB(marioBox, staticBox,  normalx, normaly);
			trace(L"AABBCheck Vx: %f, Vy: %f, Time: %f, Normalx: %f, Normaly: %f, ID: %d",VxF, VyF, collisiontime, normalx, normaly,(*it)->id);
			if (collisiontime < 1.0f && collisiontime >= 0.0f)
			{				
				if ((*it)->isKind == GROUND)				
					CollideWithGround(normalx, normaly, collisiontime, (*it));		
				if ((*it)->isKind == PIPE_CAP || (*it)->isKind == PIPE_BODY)
					CollideWithPiPe(normalx, normaly, collisiontime, (*it));
				trace(L"X: %d, Y:%d, Time: %f, Normalx: %f, Normaly: %f, ID: %d", (int)marioBox.x, (int)marioBox.y, collisiontime, normalx, normaly,(*it)->id);
			}
			if (collisiontime == 1.0f)
			{
				ConUpdate = false;
				trace(L"Flag = false, CollisionTime: %f", collisiontime);
			}				
		}		
	}

	if (onGround == true)
	{
		Vy = 0;
		Vy_old = 0.15f;
	}

	if (ConUpdate == false)
	{
		marioBox.x += VxF;
		marioBox.y += VyF;
		UpdateRect((int)marioBox.x, (int)marioBox.y);
		trace(L"Update X: %d, Y: %d", (int)marioBox.x, (int)marioBox.y);
	}
}

void Player::CollideWithGround(float normalx, float normaly, float collisiontime, StaticObject *obj)
{
	//Va cham o tren
	if (normaly == 1.0f)
	{
		Vy = 0;
		Vy_old = 0.15f;		

		onGround = true;
		jumping =false;

		marioBox.x += VxF * collisiontime;
		marioBox.y += VyF * collisiontime;
		UpdateRect((int)marioBox.x, (int)marioBox.y + 1);

		UpdateSprite();
		UpdateMarioBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, 0, 0);
		VxF = 0;
		VyF = 0;

		trace(L"Cl x: %f, y: %f, w: %f, h: %f, vx: %f, vy: %f", marioBox.x, marioBox.y, marioBox.x, marioBox.h, marioBox.vx, marioBox.vy);
		trace(L"::CollideWithGround Up");
	}
	else
	{
		if (normaly == -1.0f)
		{
			
		}
		else
		{			
			marioBox.x += VxF * collisiontime;
			marioBox.y += VyF * collisiontime;
			UpdateRect((int)marioBox.x, (int)marioBox.y);
			trace(L"Check up: RectTop: %d, MBottom: %d",obj->rectDraw.top , (int)(marioBox.y - marioBox.h) );
			if (obj->rectDraw.top == (int)(marioBox.y - marioBox.h))
			{
				ConUpdate = false;
			} 
			else 
			{
				Vx = 0;
				Vx_old = 0;
			}								

			UpdateMarioBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, 0, 0);
			VxF = 0;
			VyF = 0;
			trace(L"::CollideWithGround Left or Right");			
		}
	}
}

void Player::CollideWithPiPe(float normalx, float normaly, float collisiontime,  StaticObject *obj)
{
	if (normaly == 1.0f)
	{
		Vy = 0;
		Vy_old = 0.15f;		

		onGround = true;
		jumping =false;

		marioBox.x += VxF * collisiontime;
		marioBox.y += VyF * collisiontime;
		UpdateRect((int)marioBox.x, (int)marioBox.y + 1);

		UpdateSprite();
		UpdateMarioBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, 0, 0);
		VxF = 0;
		VyF = 0;

		trace(L"Cl x: %f, y: %f, w: %f, h: %f, vx: %f, vy: %f", marioBox.x, marioBox.y, marioBox.x, marioBox.h, marioBox.vx, marioBox.vy);
		trace(L"::CollideWithPipe Up");
	}
	else
	{
		if (normaly == -1.0f)
		{

		}
		else
		{			
			marioBox.x += VxF * collisiontime;
			marioBox.y += VyF * collisiontime;
			UpdateRect((int)marioBox.x, (int)marioBox.y);
			Vx = 0;
			Vx_old = 0;											

			UpdateMarioBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, 0, 0);
			VxF = 0;
			VyF = 0;
			trace(L"::CollideWithPiPe Left or Right");			
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