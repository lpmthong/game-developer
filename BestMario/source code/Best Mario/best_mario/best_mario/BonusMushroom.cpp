#include "BonusMushroom.h"
#include "GlobalHandler.h"
#include "Define.h"
#include "ListSound.h"
#include "CoinPickUp.h"

BonusMushroom::BonusMushroom(void){}

BonusMushroom::~BonusMushroom(void){}

BonusMushroom::BonusMushroom(int left, int top){

	sprite = new Sprite(ListTexture::TT_BONUS_MUSHROOM, ListTexture::TT_BONUS_MUSHROOM_WIDTH, ListTexture::TT_BONUS_MUSHROOM_HEIGHT,
						ListTexture::TT_BONUS_MUSHROOM_COUNT, ListTexture::TT_BONUS_MUSHROOM_SPRITEPERROW);

	width = ListTexture::TT_BONUS_MUSHROOM_WIDTH;
	height = ListTexture::TT_BONUS_MUSHROOM_HEIGHT;

	UpdateRect(left, top, ListTexture::TT_BONUS_MUSHROOM_WIDTH, ListTexture::TT_BONUS_MUSHROOM_HEIGHT);

	lastUpdate = GetTickCount();
	lastAnimate = GetTickCount();

	isSolid = true;
	isKind = BONUS_MUSHROOM;

	speed = 0.1f;

	Vx = speed;
	Vy = 0;

	alive = ALIVE;
	appear = 0;
	preparing = true;
	start = false;
}

void BonusMushroom::setBonusType(int t){
	type = t;
	switch(type){
		case GROWUP:
			sprite->Reset(ListTexture::TT_BONUS_MUSHROOM,
				ListTexture::TT_BONUS_MUSHROOM_WIDTH,		
				ListTexture::TT_BONUS_MUSHROOM_HEIGHT,		
				ListTexture::TT_BONUS_MUSHROOM_COUNT,		
				ListTexture::TT_BONUS_MUSHROOM_SPRITEPERROW);
			sprite->setIndex(0);

			GlobalHandler::sound->Play(ListSound::SOUND_BONUSRISE, false);
			break;
		case LIFE:
			sprite->Reset(ListTexture::TT_BONUS_MUSHROOM,
				ListTexture::TT_BONUS_MUSHROOM_WIDTH,		
				ListTexture::TT_BONUS_MUSHROOM_HEIGHT,		
				ListTexture::TT_BONUS_MUSHROOM_COUNT,		
				ListTexture::TT_BONUS_MUSHROOM_SPRITEPERROW);
			sprite->setIndex(1);

			GlobalHandler::sound->Play(ListSound::SOUND_BONUSRISE, false);
			break;
		case STAR:
			sprite->Reset(ListTexture::TT_STAR,
				ListTexture::TT_STAR_WIDTH,		
				ListTexture::TT_STAR_HEIGHT,		
				ListTexture::TT_STAR_COUNT,		
				ListTexture::TT_STAR_SPRITEPERROW);

			animatedRate = ListTexture::TT_STARR_ANIMATED_RATE;
			sprite->setIndex(0);

			GlobalHandler::sound->Play(ListSound::SOUND_BONUSRISE, false);
			break;
		case GUN:
			sprite->Reset(ListTexture::TT_FLOWER,
				ListTexture::TT_FLOWER_WIDTH,		
				ListTexture::TT_FLOWER_HEIGHT,		
				ListTexture::TT_FLOWER_COUNT,		
				ListTexture::TT_FLOWER_SPRITEPERROW);

			animatedRate = ListTexture::TT_FLOWER_ANIMATED_RATE;
			sprite->setIndex(0);
			Vx = 0;

			GlobalHandler::sound->Play(ListSound::SOUND_BONUSRISE, false);
			break;
		case COIN:
			CoinPickUp* coin = new CoinPickUp(rectDraw.left, rectDraw.top);
			GlobalHandler::dynamicObjManager->Add(coin);
			alive = INHELL;

			GlobalHandler::sound->Play(ListSound::SOUND_COIN, false);
			break;
	}
}

int BonusMushroom::getBonusType(){
	return type;
}

void BonusMushroom::PrepareToMove(int t){
	appear += 1;
	UpdateRect(rectDraw.left, rectDraw.top + 1);
	if (appear >= ListTexture::TT_BONUS_MUSHROOM_HEIGHT)
	{
		Vy_old = 0.5f;
		preparing = false;
	}
}

void BonusMushroom::Render(){
	RECT screen = GlobalHandler::screen;
	if (preparing)
		sprite->Render(backbuffer, rectDraw.left, rectDraw.top, screen.left , screen.bottom, appear);
	else
		sprite->Render(backbuffer, rectDraw.left, rectDraw.top, screen.left , screen.bottom);
}

void BonusMushroom::UpdateSprite(){
	DWORD now = GetTickCount();
	if (now - lastAnimate > animatedRate)
	{
		sprite->Next();
		lastAnimate = now;
	}
}

void BonusMushroom::CollideWithGround(float normalx, float normaly, float collisiontime, StaticObject *obj){
	if (normaly == 1.0f)
	{		
		if (rectDraw.right < obj->rectDraw.left + 1)
		{
			ConUpdate = true;			
			return;
		}
		Vy = 0;
		Vy_old = 0.05f;

		onGround = true;
		
		ObjBox.y += VyF * collisiontime;
		UpdateRect((int)ObjBox.x, (int)ObjBox.y + 1);
		
		UpdateObjBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, VxF, 0);
		
		VyF = 0;
		ConUpdate = true;

		//trace(L"Cl x: %f, y: %f, w: %f, h: %f, vx: %f, vy: %f", marioBox.x, marioBox.y, marioBox.x, marioBox.h, marioBox.vx, marioBox.vy);
		//trace(L"::CollideWithGround Up");
	}
	else
	{
		if (normaly == -1.0f)
		{
			
		}
		else
		{	
			//Cai if nay de laoi may truong hop ma no va cham chi ngay cai mep
			if (rectDraw.top < obj->rectDraw.top + 30 && rectDraw.top > obj->rectDraw.top - 32)
			{
				if (normalx == -1.0f)
				{
					ObjBox.x = obj->rectDraw.left - rectDraw.right + rectDraw.left;
					UpdateRect((int)ObjBox.x, (int)ObjBox.y);
				}
				else
				{
					ObjBox.x = obj->rectDraw.right + 1;
					UpdateRect((int)ObjBox.x, (int)ObjBox.y);
				}

				Vx = - Vx;			
				VxF = 0;			

				UpdateObjBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, 0, VyF);
			}
			ConUpdate = true;		
			//trace(L"::CollideWithGround Left or Right ID: %d", obj->id);			
		}
	}
}