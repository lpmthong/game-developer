#include "BrickBreak.h"
#include "GlobalHandler.h"
#include "ListSound.h"

BrickBreak::BrickBreak(void){}
BrickBreak::~BrickBreak(void){}

BrickBreak::BrickBreak(int left, int top){
	sprite = new Sprite(ListTexture::TT_BRICK_BREAK_LEFT,
						ListTexture::TT_BRICK_BREAK_LEFT_WIDTH,
						ListTexture::TT_BRICK_BREAK_LEFT_HEIGHT,
						ListTexture::TT_BRICK_BREAK_LEFT_COUNT,
						ListTexture::TT_BRICK_BREAK_LEFT_SPRITEPERROW);
	width = ListTexture::TT_BRICK_BREAK_LEFT_WIDTH;
	height = ListTexture::TT_BRICK_BREAK_LEFT_HEIGHT;
	animatedRate = ListTexture::TT_BRICK_BREAK_LEFT_ANIMATED_RATE;

	UpdateRect(left, top, ListTexture::TT_BRICK_BREAK_LEFT_WIDTH, ListTexture::TT_BRICK_BREAK_LEFT_HEIGHT);
	isKind = BRICK_BREAK;
	isSolid = false;
	setType(BB_LEFT_TOP);
	//acceleration = 0.15f;
	lastUpdate = GetTickCount();	
}

void BrickBreak::setType(int type)
{
	switch(type)
	{
		case BB_LEFT_TOP:
			Vx = -0.2f;
			Vy_old = 1.2f;
			break;
		case BB_LEFT_BOTTOM:
			Vx = -0.2f;
			Vy_old = 0.9f;
			break;
		case BB_RIGHT_TOP:
			Vx = 0.2f;
			Vy_old = 1.2f;
			break;
		case BB_RIGHT_BOTTOM:
			Vx = 0.2f;
			Vy_old = 0.9f;
			break;
	}
}

void BrickBreak::Update()
{
	UpdateSprite();

	DWORD now = GetTickCount();
	DWORD t = now - lastUpdate;
	lastUpdate = now;

	int x = rectDraw.left;
	int y = rectDraw.top;

	Vy = Vy_old - 0.15f;

	x += Vx * t;
	y += Vy * t;

	UpdateRect(x, y);

	Vy_old = Vy;

	if (y < 100 )
		isKind = BRICK_BREAK_DISAPPEAR;
		//GlobalHandler::dynamicObjManager->Remove(this);
}

void BrickBreak::UpdateSprite(){
	DWORD now = GetTickCount();
	if (now - lastAnimate > animatedRate)
	{
		sprite->Next();
		lastAnimate = now;
	}
}
