#include "Kitty.h"

Kitty::Kitty(LPD3DXSPRITE SpriteHandler, int _PosX)
{
	_SpriteHandler = SpriteHandler;
	PosX = _PosX;
	PosY = GROUND_Y;
	Vx = 0;
	Vy = 0;
	Vx_last = 1.0f;
	kitty_right = new Sprite(_SpriteHandler,KITTY_IMAGE_RIGHT,91,60,6,3);
	kitty_left = new Sprite(_SpriteHandler,KITTY_IMAGE_LEFT,91,60,6,3);
	right = true;
}
void Kitty::MoveLeft()
{
	Vx = -KITTY_SPEED;
	Vx_last = Vx;
}
void Kitty::MoveRight()
{
	Vx = KITTY_SPEED;
	Vx_last = Vx;
}
void Kitty::Jump()
{
	if (PosY >= GROUND_Y)
	{
		Vy -= 3.0f;
	}
}
void Kitty::NotMove()
{
	Vx = 0;
	kitty_left->Reset();
	kitty_right->Reset();
}
void Kitty::Update(int t)
{
	PosX += Vx * t;
	PosY += Vy * t;
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		if (Vx > 0) kitty_right->Next();
		if (Vx < 0) kitty_left->Next();
		last_time = now;
	}
	if (PosY < GROUND_Y) 
		Vy += 0.5f;
	else 
	{
		PosY = GROUND_Y;
		Vy = 0;
	}
}
void Kitty::Render(int t)
{
	Update(t);
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	
	if (Vx > 0)
		kitty_right->Render(PosX,PosY);
	else 
		if (Vx < 0)
			kitty_left->Render(PosX,PosY);
		else 
			if (Vx_last < 0)
				kitty_left->Render(PosX,PosY);
			else 
				kitty_right->Render(PosX,PosY);
	_SpriteHandler->End();
}
void Kitty::AutoMove()
{
	if (right == true)
	{
		if (PosX <= 710)
		{
			MoveRight();
		}
		else
		{
			NotMove();
			right = false;
		}		
	}
	if(right == false)
	{
		if (PosX >= 0)
		{
			MoveLeft();
		}
		else
		{	
			NotMove();
			right = true;
		}
	}
}