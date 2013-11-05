#include "Mountain.h"
#include "Sprite.h"
#include "ListTexture.h"
#include "Define.h"

Mountain::Mountain(void)
{
}

Mountain::Mountain( int left, int top, int iid )
{
	sprite = new Sprite(ListTexture::TT_MOUNTAIN, 
						ListTexture::TT_MOUNTAIN_WIDTH, 
						ListTexture::TT_MOUNTAIN_HEIGHT, 
						ListTexture::TT_MOUNTAIN_COUNT, 
						ListTexture::TT_MOUNTAIN_SPRITEPERROW);

	id = iid;
	UpdateRect(left, top, ListTexture::TT_MOUNTAIN_WIDTH, ListTexture::TT_MOUNTAIN_HEIGHT);
	map_level = 1;
	isKind = MOUNTAIN;
	isSolid = false;
}

Mountain::~Mountain(void)
{
}
