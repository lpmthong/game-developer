#include "Player.h"
#include "GlobalHandler.h"
#include "Box.h"
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
	trace(L"Player::Init(int mode,int LastCheckPoint, int Life)");
}

void Player::InitFromFile(int mode,int LastCheckPoint, int Life){
	if (mode == PLAYER_KID)
		setKid();
	lastCheckPoint = LastCheckPoint;
	//cai nay de khi nao lam cai checkpoint da
	//UpdateRect(GlobalHandler::checkpoint[0][lastCheckPoint], GlobalHandler::checkpoint[1][lastCheckPoint]);
	UpdateRect(15, 470);
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
	int x = rectReal.left;
	int y = rectReal.top;

	Vx = Vx_old + acceleration * t;
	Vy = Vy_old - 0.15f;

	Vx = (Vx < maxSpeed)?Vx:maxSpeed;
	Vx = (Vx > -maxSpeed)?Vx:(-maxSpeed);	
	
	CollideWithStaticObj(Vx / t, Vy / t);	

	x += Vx * t;
	y += Vy * t;

	if (y <= 152)
	{	
		y = 152;
		Vy = 0;
		jumping = false;
		onGround = true;
	}

	Vy_old = Vy;
	Vx_old = Vx;

	UpdateRectReal(x, y);
	UpdateSprite();
	GlobalHandler::UpdateScreen();
	//trace(L"X: %d , Y: %d, A: %d, VX: %d, K:%d", x, y, acceleration, Vx, k);
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

void Player::CollideWithStaticObj(float vx, float vy){

	float normalx, normaly;
	Box marioBox((float)rectReal.left, (float)rectReal.top, (float)width, (float)height, vx, vy);
	trace(L"x: %f, y: %f, w: %f, h: %f, vx: %f, vy: %f", (float)rectReal.left, (float)rectReal.top, (float)width, (float)height, vx, vy);
	Box broadphasebox = GlobalHandler::Physic->GetSweptBroadphaseBox(marioBox);
	return;

	list<StaticObject*>::iterator it;
	for (it = GlobalHandler::listStaticObjRender.begin(); it != GlobalHandler::listStaticObjRender.end(); ++it)
	{
		Box staticBox((float)(*it)->rectReal.left, (float)(*it)->rectReal.top, (float)(*it)->width, (float)(*it)->height, 0.0f, 0.0f);


		//trace(L"ID: %d, Type: %d", (*it)->id, (*it)->isKind);
	}
	trace(L"HET VONG LAP");
}