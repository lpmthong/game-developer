#include "Coin.h"
#include "ListTexture.h"
#include "Define.h"

Coin::Coin(void)
{
}

Coin::Coin( int left, int top )
{
	sprite = new Sprite(ListTexture::TT_OUT_COIN,				
		ListTexture::TT_OUT_COIN_WIDTH,			
		ListTexture::TT_OUT_COIN_HEIGHT,		
		ListTexture::TT_OUT_COIN_COUNT,			
		ListTexture::TT_OUT_COIN_SPRITEPERROW);

	animatedRate = ListTexture::TT_OUT_COIN_ANIMATED_RATE;

	lastAnimate = GetTickCount();

	width = ListTexture::TT_OUT_COIN_WIDTH;
	height = ListTexture::TT_OUT_COIN_HEIGHT;
	UpdateRect(left, top, ListTexture::TT_OUT_COIN_WIDTH, ListTexture::TT_OUT_COIN_HEIGHT);
	map_level = 2;
	isKind = OUTCOIN;
	isSolid = true;
}

Coin::~Coin(void)
{
}
