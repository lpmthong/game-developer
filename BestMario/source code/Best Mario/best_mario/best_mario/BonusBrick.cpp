#include "BonusBrick.h"
#include "GlobalHandler.h"
#include "BonusMushroom.h"

BonusBrick::BonusBrick(void){}
BonusBrick::~BonusBrick(void){}

BonusBrick::BonusBrick(int left, int top, bool iEmpty, int iid){

	sprite = new Sprite(ListTexture::TT_BRICK_BONUS, ListTexture::TT_BRICK_BONUS_WIDTH, ListTexture::TT_BRICK_BONUS_HEIGHT,
						ListTexture::TT_BRICK_BONUS_COUNT, ListTexture::TT_BRICK_BONUS_SPRITEPERROW);

	id = iid;
	width = ListTexture::TT_BRICK_BONUS_WIDTH;
	height = ListTexture::TT_BRICK_BONUS_HEIGHT;
	
	UpdateRect(left, top , ListTexture::TT_BRICK_BONUS_WIDTH, ListTexture::TT_BRICK_BONUS_HEIGHT);

	animatedRate = ListTexture::TT_BRICK_BONUS_ANIMATED_RATE;

	isKind = BRICK_BONUS_COIN;
	lastCollide = GetTickCount();
	isEmpty = iEmpty;	

	isSolid = true;

	hasCollide = false;
	isHardBrick = false;
	
	distancemoveup = 5;

	willRender = true;
	map_level = 2;

	if (isEmpty)
		SetEmpty();
}

void BonusBrick::ProcessCollision(int iKind){

	if (isHardBrick == true)
		return;

	lastCollide = GetTickCount();
	UpdateRect(rectDraw.left, rectDraw.top + distancemoveup);
	willRender = true;
	hasCollide = true;
	isEmpty = true;
}

void BonusBrick::Render(){
	if (willRender == false)
		return;
	RECT screen = GlobalHandler::screen;
	sprite->Render(backbuffer, rectDraw.left, rectDraw.top, screen.left , screen.bottom);
}

void BonusBrick::BonusAppear(){
	__super::BonusAppear();
	BonusMushroom* bonusMushRoom = new BonusMushroom(rectDraw.left, rectDraw.top);

	if (isKind == BRICK_BONUS_MUSHROOM)
		bonusMushRoom->setBonusType(GROWUP);
	if (isKind == BRICK_BONUS_LIFE || isKind == BRICK_BONUS_LIFE_HIDDEN)
		bonusMushRoom->setBonusType(LIFE);
	if (isKind == BRICK_BONUS_GUN)
		bonusMushRoom->setBonusType(GUN);
	if (isKind == BRICK_BONUS_COIN)
		bonusMushRoom->setBonusType(COIN);
	if (isKind == BRICK_BONUS_STAR)
		bonusMushRoom->setBonusType(STAR);

	GlobalHandler::dynamicObjManager->Add(bonusMushRoom);
}

void BonusBrick::SetEmpty(){
	isHardBrick = true;
	sprite->Reset(ListTexture::TT_EMPTY_BRICK, width, height, 1, 1);
}

int BonusBrick::getType(){
	return isKind;	
}

void BonusBrick::setType(int type)
{
	isKind = type;
	if (isKind == BRICK_BONUS_LIFE_HIDDEN)
		setHidden();
}

void BonusBrick::setHidden(){
	willRender = false;
}


