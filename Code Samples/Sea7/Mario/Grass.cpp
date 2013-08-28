#include "Grass.h"
#include "ListTexture.h"
#include "Define.h"

Grass::Grass(void)
{
}

Grass::Grass( int left, int top )
{
	sprite = new Sprite(ListTexture::TT_GRASS, 
		ListTexture::TT_GRASS_WIDTH, 
		ListTexture::TT_GRASS_HEIGHT, 
		ListTexture::TT_GRASS_COUNT, 
		ListTexture::TT_GRASS_SPRITEPERROW);

	UpdateRect(left, top, ListTexture::TT_GRASS_WIDTH, ListTexture::TT_GRASS_HEIGHT);
	map_level = 2;

	animatedRate = ListTexture::TT_GRASS_ANIMATED_RATE;
	lastAnimate = GetTickCount();

	iKind = GRASS;
	isSolid = false;
}

Grass::~Grass(void)
{
}
