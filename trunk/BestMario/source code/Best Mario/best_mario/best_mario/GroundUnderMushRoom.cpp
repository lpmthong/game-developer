#include "GroundUnderMushroom.h"
#include "Sprite.h"
#include "ListTexture.h"
#include "Define.h"

GroundUnderMushroom::GroundUnderMushroom(void)
{
}

GroundUnderMushroom::GroundUnderMushroom( int left, int top, int iid)
{
	sprite = new Sprite(ListTexture::TT_GROUND_UNDER_MUSHROOM, 
		ListTexture::TT_GROUND_UNDER_MUSHROOM_WIDTH, 
		ListTexture::TT_GROUND_UNDER_MUSHROOM_HEIGHT, 
		ListTexture::TT_GROUND_UNDER_MUSHROOM_COUNT, 
		ListTexture::TT_GROUND_UNDER_MUSHROOM_SPRITEPERROW);

	id = iid;
	UpdateRect(left, top, ListTexture::TT_GROUND_UNDER_MUSHROOM_WIDTH, ListTexture::TT_GROUND_UNDER_MUSHROOM_HEIGHT);
	map_level = 1;

	width = ListTexture::TT_GROUND_UNDER_MUSHROOM_WIDTH;
	height = ListTexture::TT_GROUND_UNDER_MUSHROOM_HEIGHT;

	isKind = GROUNDUNDERMUSHROOM;
	isSolid = true;
}

GroundUnderMushroom::~GroundUnderMushroom(void)
{
}