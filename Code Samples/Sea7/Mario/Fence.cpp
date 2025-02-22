#include "Fence.h"
#include "ListTexture.h"
#include "Define.h"

Fence::Fence(void)
{
}

Fence::Fence( int left, int top )
{
	sprite = new Sprite(ListTexture::TT_FENCE, 
		ListTexture::TT_FENCE_WIDTH, 
		ListTexture::TT_FENCE_HEIGHT, 
		ListTexture::TT_FENCE_COUNT, 
		ListTexture::TT_FENCE_SPRITEPERROW);


	UpdateRect(left, top, ListTexture::TT_FENCE_WIDTH, ListTexture::TT_FENCE_HEIGHT);
	map_level = 2;

	iKind = FENCE;
	isSolid = false;
}

Fence::~Fence(void)
{
}
