#include "BrickBreak.h"
#include "GlobalHandler.h"
#include "Define.h"
#include "ListTexture.h"
#include "ListSound.h"

BrickBreak::BrickBreak(void)
{
}

BrickBreak::BrickBreak( int left, int top ) : DynamicObject()
{
	sprite = new Sprite(ListTexture::TT_BRICK_BREAK_LEFT,
						ListTexture::TT_BRICK_BREAK_LEFT_WIDTH,
						ListTexture::TT_BRICK_BREAK_LEFT_HEIGHT,
						ListTexture::TT_BRICK_BREAK_LEFT_COUNT,
						ListTexture::TT_BRICK_BREAK_LEFT_SPRITEPERROW);

	width = ListTexture::TT_BRICK_BREAK_LEFT_WIDTH;
	height = ListTexture::TT_BRICK_BREAK_LEFT_HEIGHT;

	UpdateRect(left, top, ListTexture::TT_BRICK_BREAK_LEFT_WIDTH, ListTexture::TT_BRICK_BREAK_LEFT_HEIGHT);
	//	map_level = 2;

	iKind = BRICK_BREAK;
	isSolid = false;

	animatedRate = ListTexture::TT_BRICK_BREAK_LEFT_ANIMATED_RATE;

//	lastCollide = GetTickCount();
//	hasCollide = false;

//	dis = 3;
	acceleration = 15;
//	fXOldVelocity = -5;
//	fYOldVelocity = -20;
	setType(BB_RIGHT_BOTTOM);
	lastUpdate = GetTickCount();

	GlobalHandler::sound->Play(ListSound::SOUND_BRICKBREAKED, false);
}

BrickBreak::~BrickBreak(void)
{
}

void BrickBreak::Update()
{
	UpdateSprite();

	DWORD now = GetTickCount();
	DWORD t = now - lastUpdate;
	lastUpdate = now;

	fYVelocity = fYOldVelocity + acceleration * t / 100;
	fXVelocity = fXOldVelocity + acceleration * t / 100;

	fXVelocity = (fXVelocity < 20)?fXVelocity:20;
	fXVelocity = (fXVelocity > -20)?fXVelocity:(-20);

//	oldLeft = recRealArea.left;
//	oldTop = recRealArea.top;

	int x = recRealArea.left;
	int y = recRealArea.top;
	x+=fXOldVelocity;
//	x += fXOldVelocity * t / 100 + acceleration * t * t / 100000 / 2;

	y += fYOldVelocity * t / 100 + acceleration * t * t / 100000 / 2;
//	int y = recRealArea.top - fYOldVelocity * t / 100 - 7 * t * t / 100000;

	//int x = recRealArea.left + 1;
	//int y = recRealArea.top + 1;
	fYOldVelocity = fYVelocity;
//	fXOldVelocity = fXVelocity;

	UpdateRecReal(x, y);

	if (y > SCREEN_HEIGHT)
		iKind = BRICK_BREAK_DISAPPEAR;
}

void BrickBreak::UpdateSprite()
{
	DWORD now = GetTickCount();
	if (now - lastAnimate > animatedRate)
	{
		sprite->Next();
		lastAnimate = now;
	}
}

void BrickBreak::setType( int type )
{
	switch (type)
	{
	case BB_LEFT_TOP:
		fXOldVelocity = -5;
		fYOldVelocity = -60;
		break;
	case BB_RIGHT_TOP:
		fXOldVelocity = 5;
		fYOldVelocity = -60;
		break;
	case BB_LEFT_BOTTOM:
		fXOldVelocity = -5;
		fYOldVelocity = -50;
		break;
	case BB_RIGHT_BOTTOM:
		fXOldVelocity = 5;
		fYOldVelocity = -50;
		break;
	}
}
