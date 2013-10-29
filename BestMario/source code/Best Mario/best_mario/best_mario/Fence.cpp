#include "Fence.h"
#include "ListTexture.h"
#include "Define.h"

Fence::Fence(void){}

Fence::Fence(int left, int top){
	sprite = new Sprite(ListTexture::TT_FENCE, ListTexture::TT_FENCE_WIDTH, ListTexture::TT_FENCE_HEIGHT,
						ListTexture::TT_FENCE_COUNT, ListTexture::TT_FENCE_SPRITEPERROW);
	width = ListTexture::TT_FENCE_WIDTH;
	height = ListTexture::TT_FENCE_HEIGHT;

	UpdateRect(left, top, ListTexture::TT_FENCE_WIDTH, ListTexture::TT_FENCE_HEIGHT);
	map_level = 2;
	isKind = FENCE;
	isSolid = false;
}

Fence::~Fence(void){}