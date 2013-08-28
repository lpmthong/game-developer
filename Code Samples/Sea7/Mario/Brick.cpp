#include "Brick.h"
#include "Define.h"
#include "ListSound.h"
#include "GlobalHandler.h"

Brick::Brick(void)
{
	Brick(0, 0);
}

Brick::Brick( int left, int top ) : DynamicObject()
{
	sprite = new Sprite(ListTexture::TT_BRICK, 
						ListTexture::TT_BRICK_WIDTH, 
						ListTexture::TT_BRICK_HEIGHT, 
						ListTexture::TT_BRICK_COUNT, 
						ListTexture::TT_BRICK_SPRITEPERROW);

	width = ListTexture::TT_BRICK_WIDTH;
	height = ListTexture::TT_BRICK_HEIGHT;

	UpdateRect(left, top, ListTexture::TT_BRICK_WIDTH, ListTexture::TT_BRICK_HEIGHT);
//	map_level = 2;

	iKind = BRICK;
	isSolid = true;

	lastCollide = GetTickCount();
	lastAnimate = GetTickCount();
	hasCollide = false;

	dis = 3;

	isHardBrick = false;

	//Just init it, dont let it start to do anything.
	start = false;
}

Brick::~Brick(void)
{
}

void Brick::ProcessCollision( int iKind )
{
	if (isHardBrick)
		return;

	if (iKind == PLAYER_KID && hasCollide == false)
	{
		if (GlobalHandler::player->recRealArea.top > recRealArea.top)
		{
			//DWORD now = GetTickCount();
			lastCollide = GetTickCount();	
			UpdateRect(recDrawArea.left, recDrawArea.top - dis);
			hasCollide = true;

			GlobalHandler::sound->Play(ListSound::SOUND_BUMP, false);
		}
	}
	else if (iKind == PLAYER_ADULT || iKind == PLAYER_ADULT_GUN)
	{
		if (GlobalHandler::player->recRealArea.top > recRealArea.top)
		{
			//DWORD now = GetTickCount();
			//GlobalHandler::dynamicObjManager->Remove(this);
			lastCollide = GetTickCount();	
			UpdateRect(recDrawArea.left, recDrawArea.top - dis);
			hasCollide = true;
			alive = DYING;
			
		}
	}
}

void Brick::Update()
{
	if (hasCollide == true)
	{
		DWORD now = GetTickCount();

		if (alive == DYING)
		{
			if (now - lastCollide > 20)
				GlobalHandler::dynamicObjManager->ProcessBrickBreak(this);
			return;
		}

		if (now - lastCollide > 150)
		{
			hasCollide = false;
			UpdateRect(recDrawArea.left, recDrawArea.top + dis);
			BonusAppear();
		}
	}

	UpdateSprite();
}

void Brick::BonusAppear()
{
	SetEmpty();
}

void Brick::SetEmpty()
{

}

void Brick::UpdateSprite()
{
	DWORD now = GetTickCount();

	if (now - lastAnimate > animatedRate)
	{
		sprite->Next();
		lastAnimate = now;
	}
}
