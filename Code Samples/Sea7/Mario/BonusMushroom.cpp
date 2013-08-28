#include "BonusMushroom.h"
#include "ListTexture.h"
#include "Define.h"
#include "trace.h"
#include "CoinPickUp.h"
#include "ListSound.h"
#include "GlobalHandler.h"
#include "Brick.h"

BonusMushroom::BonusMushroom(void)
{
}

BonusMushroom::BonusMushroom( int left, int top )
{
	sprite = new Sprite(ListTexture::TT_BONUS_MUSHROOM,
						ListTexture::TT_BONUS_MUSHROOM_WIDTH,		
						ListTexture::TT_BONUS_MUSHROOM_HEIGHT,		
						ListTexture::TT_BONUS_MUSHROOM_COUNT,		
						ListTexture::TT_BONUS_MUSHROOM_SPRITEPERROW);

	width = ListTexture::TT_BONUS_MUSHROOM_WIDTH;
	height = ListTexture::TT_BONUS_MUSHROOM_HEIGHT;

	UpdateRect(left, top, ListTexture::TT_BONUS_MUSHROOM_WIDTH, ListTexture::TT_BONUS_MUSHROOM_HEIGHT);
	//	map_level = 2;

	lastUpdate = GetTickCount();
	lastAnimate = GetTickCount();

	iKind = BONUS_MUSHROOM;
	isSolid = true;

	speed = 3;

	fYOldVelocity = 0;
	fXOldVelocity = speed;

	alive = ALIVE;

	appear = 0;

	preparing = true;

	//Just init it, dont let it start to do anything.
	start = false;
}

BonusMushroom::~BonusMushroom(void)
{
}

void BonusMushroom::PrepareToMove(int t)
{
	appear += 1;
	UpdateRect(recDrawArea.left, recDrawArea.top - 1);
	if (appear >= ListTexture::TT_BONUS_MUSHROOM_HEIGHT)
	{
		fYOldVelocity = 30;
		preparing = false;
	}
}

void BonusMushroom::Render()
{
	RECT screen = GlobalHandler::screen;

	if (preparing)
		sprite->Render(GlobalHandler::directX->backbuffer, recDrawArea.left - screen.left, recDrawArea.top - screen.top, appear);
	else
		sprite->Render(GlobalHandler::directX->backbuffer, recDrawArea.left - screen.left, recDrawArea.top - screen.top);
}

void BonusMushroom::setBonusType( int t )
{
	type = t;
	if (t == GROWUP)
	{
		sprite->Reset(ListTexture::TT_BONUS_MUSHROOM,
			ListTexture::TT_BONUS_MUSHROOM_WIDTH,		
			ListTexture::TT_BONUS_MUSHROOM_HEIGHT,		
			ListTexture::TT_BONUS_MUSHROOM_COUNT,		
			ListTexture::TT_BONUS_MUSHROOM_SPRITEPERROW);
		sprite->setIndex(0);

		GlobalHandler::sound->Play(ListSound::SOUND_BONUSRISE, false);
	}
	else
		if (t == LIFE)
		{
			sprite->Reset(ListTexture::TT_BONUS_MUSHROOM,
				ListTexture::TT_BONUS_MUSHROOM_WIDTH,		
				ListTexture::TT_BONUS_MUSHROOM_HEIGHT,		
				ListTexture::TT_BONUS_MUSHROOM_COUNT,		
				ListTexture::TT_BONUS_MUSHROOM_SPRITEPERROW);
			sprite->setIndex(1);

			GlobalHandler::sound->Play(ListSound::SOUND_BONUSRISE, false);
		}
		else
			if (t == STAR)
			{
				sprite->Reset(ListTexture::TT_STAR,
					ListTexture::TT_STAR_WIDTH,		
					ListTexture::TT_STAR_HEIGHT,		
					ListTexture::TT_STAR_COUNT,		
					ListTexture::TT_STAR_SPRITEPERROW);

				animatedRate = ListTexture::TT_STARR_ANIMATED_RATE;
				sprite->setIndex(0);

				GlobalHandler::sound->Play(ListSound::SOUND_BONUSRISE, false);
			}
			else
				if (t == GUN)
				{
					sprite->Reset(ListTexture::TT_FLOWER,
						ListTexture::TT_FLOWER_WIDTH,		
						ListTexture::TT_FLOWER_HEIGHT,		
						ListTexture::TT_FLOWER_COUNT,		
						ListTexture::TT_FLOWER_SPRITEPERROW);

					animatedRate = ListTexture::TT_FLOWER_ANIMATED_RATE;
					sprite->setIndex(0);
					fXOldVelocity = 0;

					GlobalHandler::sound->Play(ListSound::SOUND_BONUSRISE, false);
				}
				else
					if (t == COIN)
					{
						CoinPickUp* coin = new CoinPickUp(recDrawArea.left, recDrawArea.top);
						GlobalHandler::dynamicObjManager->Add(coin);
						alive = INHELL;

						GlobalHandler::sound->Play(ListSound::SOUND_COIN, false);
					}

}

void BonusMushroom::MoveToHell()
{

}

void BonusMushroom::CollideMushRoomEnemy( DynamicObject* obj )
{

}

void BonusMushroom::CollideTurleEnemy( DynamicObject* obj )
{

}

int BonusMushroom::getBonusType()
{
	return type;
}

void BonusMushroom::UpdateSprite()
{
	DWORD now = GetTickCount();
	if (now - lastAnimate > animatedRate)
	{
		sprite->Next();
		lastAnimate = now;
	}
}

void BonusMushroom::CollideGround( StaticObject* obj )
{
	if (type == STAR)
	{
		UpdateRecReal(recRealArea.left, obj->recRealArea.top - recRealArea.bottom + recRealArea.top);
		fYOldVelocity = 60;
	}
	else
	{
		if (oldTop + recRealArea.bottom - recRealArea.top < obj->recRealArea.top + 5)
		{
			Brick* collideBrick = (Brick*)obj;
			if (collideBrick->hasCollide == true)
			{
				MoveToHell();
			}
			UpdateRecReal(recRealArea.left, obj->recRealArea.top - recRealArea.bottom + recRealArea.top);
			fYVelocity = 0;
			fYOldVelocity = 0;
		}
		else
		{
			//Turn back.
			fXOldVelocity = -fXOldVelocity;

			int objCollideCenter = (obj->recRealArea.right + obj->recRealArea.left)/2;
			if (oldLeft < objCollideCenter)
				UpdateRecReal(obj->recRealArea.left - recRealArea.right + recRealArea.left - 1, recRealArea.top);
			else
				UpdateRecReal(obj->recRealArea.right + 1, recRealArea.top);
		}
	}
}

void BonusMushroom::CollideBrick( DynamicObject* obj )
{
	if (type != STAR)
		return;

	if (oldTop + recRealArea.bottom - recRealArea.top < obj->recRealArea.top + 5)
	{
		UpdateRecReal(recRealArea.left, obj->recRealArea.top - recRealArea.bottom + recRealArea.top);
		fYOldVelocity = 60;
	}
	else
	{
		//Turn back.
		fXOldVelocity = -fXOldVelocity;

		int objCollideCenter = (obj->recRealArea.right + obj->recRealArea.left)/2;
		if (oldLeft < objCollideCenter)
			UpdateRecReal(obj->recRealArea.left - recRealArea.right + recRealArea.left - 1, recRealArea.top);
		else
			UpdateRecReal(obj->recRealArea.right + 1, recRealArea.top);
	}
}
