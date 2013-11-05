#include "Grass.h"
#include "Define.h"
#include "ListTexture.h"

Grass::Grass(void){}

Grass::Grass(int left, int top, int iid){

	sprite = new Sprite(ListTexture::TT_GRASS, ListTexture::TT_GRASS_WIDTH, ListTexture::TT_GRASS_HEIGHT,
						ListTexture::TT_GRASS_COUNT, ListTexture::TT_GRASS_SPRITEPERROW);
	width = ListTexture::TT_GRASS_WIDTH;
	height = ListTexture::TT_GRASS_HEIGHT;
	id = iid;
	UpdateRect(left, top, ListTexture::TT_GRASS_WIDTH, ListTexture::TT_GRASS_HEIGHT);
	animatedRate = ListTexture::TT_GRASS_ANIMATED_RATE;
	lastAnimate = GetTickCount();
	map_level = 2;
	isKind = GRASS;
	isSolid = false;
}

Grass::~Grass(void){};