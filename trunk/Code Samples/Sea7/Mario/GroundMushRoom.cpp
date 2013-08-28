#include "GroundMushRoom.h"
#include "Sprite.h"
#include "ListTexture.h"
#include "Define.h"

GroundMushRoom::GroundMushRoom(void)
{
}

GroundMushRoom::GroundMushRoom( int left, int top )
{
	sprite = new Sprite(ListTexture::TT_GROUND_MUSHROOM, 
						ListTexture::TT_GROUND_MUSHROOM_WIDTH, 
						ListTexture::TT_GROUND_MUSHROOM_HEIGHT, 
						ListTexture::TT_GROUND_MUSHROOM_COUNT, 
						ListTexture::TT_GROUND_MUSHROOM_SPRITEPERROW);


	width = ListTexture::TT_GROUND_MUSHROOM_WIDTH;
	height = ListTexture::TT_GROUND_MUSHROOM_HEIGHT;
	UpdateRect(left, top, ListTexture::TT_GROUND_MUSHROOM_WIDTH, ListTexture::TT_GROUND_MUSHROOM_HEIGHT);
	map_level = 2;

	iKind = GROUND;

	isSolid = true;
}

GroundMushRoom::~GroundMushRoom(void)
{
}

void GroundMushRoom::setType( int t )
{
	type = t;
	if (type == GROUND_MUSHROOM_LEFT)
		sprite->setIndex(0);
	else if (type == GROUND_MUSHROOM_MIDDLE)
		sprite->setIndex(1);
	else if (type == GROUND_MUSHROOM_RIGHT)
		sprite->setIndex(2);
}
