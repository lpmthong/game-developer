#include "FallingCross.h"

FallingCross::FallingCross(void)
{
}

FallingCross::FallingCross( int left, int top )
{
	sprite = new Sprite(ListTexture::TT_FALLING_CROSS,
		ListTexture::TT_CROSS_WIDTH, 
		ListTexture::TT_CROSS_HEIGHT, 
		1, 
		1);

	width = ListTexture::TT_CROSS_WIDTH;
	height = ListTexture::TT_CROSS_HEIGHT + 10;

	UpdateRect(left, top, ListTexture::TT_CROSS_WIDTH, ListTexture::TT_CROSS_HEIGHT + 10);

	iKind = CROSS;
	isSolid = true;

	isHardBrick = true;

	//Just init it, dont let it start to do anything.
	start = false;

	collidePlayer = false;
	fallDown = false;
	timeHoldOn = 150;
	startFallDown = GetTickCount();
	lastUpdate = GetTickCount();

	fYOldVelocity = 0;
}

FallingCross::~FallingCross(void)
{
}

void FallingCross::Update()
{
	if (collidePlayer == true && fallDown == false)
	{
		DWORD now = GetTickCount();
		if (now - startFallDown > timeHoldOn)
		{
			fallDown = true;
			lastUpdate = now;
		}
	}

	if (fallDown)
	{
		DWORD now = GetTickCount();
		int t = now - lastUpdate;
		lastUpdate = now;

		fYVelocity = fYOldVelocity - 15 * t / 100;

		int y = recRealArea.top - fYOldVelocity * t / 100 - 7 * t * t / 100000;
		UpdateRecReal(recRealArea.left, y);
		fYOldVelocity = fYVelocity;
	}

	UpdateSprite();
}

void FallingCross::ProcessCollision( int iKind )
{
	if (collidePlayer == false)
		startFallDown = GetTickCount();

	collidePlayer = true;
}
