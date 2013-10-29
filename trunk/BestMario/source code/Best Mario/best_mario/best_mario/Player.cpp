#include "GlobalHandler.h"
#include "Player.h"
#include "ListTexture.h"
#include "Define.h"

Player::Player(void){}

Player::~Player(void){}

void Player::Init(int mode,int LastCheckPoint, int Life){

	sprite = new Sprite();
	InitFromFile(mode, LastCheckPoint, Life);
	Vx = 0;
	Vy = 0;
	acceleration = 0;

	animatedRate = ListTexture::TT_MARIO_KID_ANIMATED_RATE;
	lastAnimate = GetTickCount();
	lastUpdate = GetTickCount();

	maxSpeed = 30;

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

	Vx = Vx_old + acceleration * t / 100;
	Vx = (Vx < maxSpeed)?Vx:maxSpeed;
	Vx = (Vx > -maxSpeed)?Vx:(-maxSpeed);

	int k = Vx * t / 100;

	x += k;
	y += Vy * t / 100;

	if (y > 88)
	{
		Vy -= 10;
	} else {
		y = 88;
		Vy = 0;
		jumping = false;
		onGround = true;
	}

	Vy_old = Vy;
	Vx_old = Vx;

	UpdateRectReal(x, y);
	UpdateSprite();
	GlobalHandler::UpdateScreen();
	trace(L"X: %d , Y: %d, A: %d, VX: %d, K:%d", x, y, acceleration, Vx, k);
}

void Player::ProcessInput(){

	if (GlobalHandler::_directX->IsKeyDown(DIK_LEFT))
	{
		if (onGround == false)
		{
			Vx_old = -25; // Khong co cai nay nhay len la khong sang phai trai dc
			acceleration = 0;
		}
		else{
			acceleration = -3;
		}
		//Vx = -30;32
		//Vx_old = Vx;
		oldDirect = false;
	}
	else if (GlobalHandler::_directX->IsKeyDown(DIK_RIGHT))
	{
		if (onGround == false)
		{
			Vx_old = 25;
			acceleration = 0;
		}
		else
		{
			acceleration = 3;
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
				Vy = 90;
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
			if (Vx > 0)
				sprite->Next(frame_moving_right_start, frame_moving_right_end);
			else
				if (Vx < 0)
					sprite->Next(frame_moving_left_start, frame_moving_left_end);
				else
					if (oldDirect == true)
						sprite->Next(frame_moving_right_start, frame_moving_right_start);
					else
						sprite->Next(frame_moving_left_start, frame_moving_left_start);
		}
	}
}

