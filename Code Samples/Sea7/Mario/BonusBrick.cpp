#include "BonusBrick.h"
#include "Define.h"
#include "ListTexture.h"
#include "BonusMushroom.h"

BonusBrick::BonusBrick(void)
{
}

BonusBrick::BonusBrick( int left, int top )
{
	sprite = new Sprite(ListTexture::TT_BRICK_BONUS, 
						ListTexture::TT_BRICK_BONUS_WIDTH, 
						ListTexture::TT_BRICK_BONUS_HEIGHT, 
						ListTexture::TT_BRICK_BONUS_COUNT, 
						ListTexture::TT_BRICK_BONUS_SPRITEPERROW);

	width = ListTexture::TT_BRICK_BONUS_WIDTH;
	height = ListTexture::TT_BRICK_BONUS_HEIGHT;

	UpdateRect(left, top, ListTexture::TT_BRICK_BONUS_WIDTH, ListTexture::TT_BRICK_BONUS_HEIGHT);
	//	map_level = 2;

	animatedRate = ListTexture::TT_BRICK_BONUS_ANIMATED_RATE;
	iKind = BRICK_BONUS_MUSHROOM;
	isSolid = true;

	lastCollide = GetTickCount();
	hasCollide = false;

	dis = 5;

	isEmpty = false;

	isHardBrick = false;

	//Just init it, dont let it start to do anything.
	start = false;

	willRender = true;
}

BonusBrick::~BonusBrick(void)
{
}

void BonusBrick::ProcessCollision( int iKind )
{
	if (isHardBrick)
		return;

	if (iKind == PLAYER_KID || iKind == PLAYER_ADULT || iKind == PLAYER_ADULT_GUN)
	{
		if (GlobalHandler::player->recRealArea.top > recRealArea.top)
		{
			//DWORD now = GetTickCount();
			lastCollide = GetTickCount();	
			UpdateRect(recDrawArea.left, recDrawArea.top - dis);
			hasCollide = true;
			willRender = true;
		}
	}
}

void BonusBrick::BonusAppear()
{
	__super::BonusAppear();
	BonusMushroom* bonusMushRoom = new BonusMushroom(recDrawArea.left, recDrawArea.top);

	if (iKind == BRICK_BONUS_MUSHROOM)
		bonusMushRoom->setBonusType(GROWUP);
	if (iKind == BRICK_BONUS_LIFE || iKind == BRICK_BONUS_LIFE_HIDDEN)
		bonusMushRoom->setBonusType(LIFE);
	if (iKind == BRICK_BONUS_GUN)
		bonusMushRoom->setBonusType(GUN);
	if (iKind == BRICK_BONUS_COIN)
		bonusMushRoom->setBonusType(COIN);
	if (iKind == BRICK_BONUS_STAR)
		bonusMushRoom->setBonusType(STAR);

	GlobalHandler::dynamicObjManager->Add(bonusMushRoom);
}

void BonusBrick::SetEmpty()
{
	isHardBrick = true;
	sprite->Reset(ListTexture::TT_EMPTY_BRICK, width, height, 1, 1);
}

int BonusBrick::getType()
{
	return iKind;
}

void BonusBrick::setType(int type)
{
	iKind = type;
	if (iKind == BRICK_BONUS_LIFE_HIDDEN)
		setHidden();
}

void BonusBrick::Render()
{
	if (willRender == false)
	{
//		trace(L"hidden");
		return;
	}
	RECT screen = GlobalHandler::screen;
	sprite->Render(GlobalHandler::directX->backbuffer, recDrawArea.left - screen.left, recDrawArea.top - screen.top);

}

void BonusBrick::setHidden()
{
	willRender = false;
}
