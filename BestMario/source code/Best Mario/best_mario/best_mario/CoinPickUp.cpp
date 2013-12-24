#include "CoinPickUp.h"
#include "GlobalHandler.h"

CoinPickUp::CoinPickUp(void){}

CoinPickUp::~CoinPickUp(void){}

CoinPickUp::CoinPickUp(int left, int top){
	sprite = new Sprite(ListTexture::TT_COIN_PICK,				
		ListTexture::TT_COIN_PICK_WIDTH,			
		ListTexture::TT_COIN_PICK_HEIGHT,		
		ListTexture::TT_COIN_PICK_COUNT,			
		ListTexture::TT_COIN_PICK_SPRITEPERROW);

	width = ListTexture::TT_COIN_PICK_WIDTH;
	height = ListTexture::TT_COIN_PICK_HEIGHT;
	animatedRate = ListTexture::TT_COIN_PICK_ANIMATED_RATE;
	UpdateRect(left, top, ListTexture::TT_COIN_PICK_WIDTH, ListTexture::TT_COIN_PICK_HEIGHT);

	isSolid = false;

	distanceMoving = 0;

	lastAnimate = GetTickCount();

	//Every time a CoinPickup appear, player get a new coin.
	GlobalHandler::player->CollectCoin();

	//Add score for player.
	Score* score = new Score(rectDraw.left, rectDraw.top);
	score->setScore(200);
	GlobalHandler::dynamicObjManager->Add(score);
	
	start = false;
}

void CoinPickUp::Update(){
	distanceMoving += 3;
	if (distanceMoving < 30)
		UpdateRect(rectDraw.left, rectDraw.top + 7);
	else
		UpdateRect(rectDraw.left, rectDraw.top - 1);

	DWORD now = GetTickCount();

	if (now - lastAnimate > animatedRate)
	{
		if (distanceMoving > 50)
			alive = INHELL;
		if (distanceMoving > 30)
		{
			if (sprite->getIndex() == 3)
				sprite->Next(3,3);
			sprite->Next(2,3);
		}
		else
			sprite->Next(0,1);
		lastAnimate = now;
	}
}