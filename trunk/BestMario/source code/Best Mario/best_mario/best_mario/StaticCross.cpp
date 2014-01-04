#include "StaticCross.h"
#include "GlobalHandler.h"

StaticCross::StaticCross(void){}

StaticCross::StaticCross(int left, int top, int iid){
	sprite = new Sprite(ListTexture::TT_STATIC_CROSS, ListTexture::TT_CROSS_WIDTH, ListTexture::TT_CROSS_HEIGHT, 1, 1);

	id = iid;
	width = ListTexture::TT_CROSS_WIDTH;
	height = ListTexture::TT_CROSS_HEIGHT;

	UpdateRect(left, top , ListTexture::TT_CROSS_WIDTH, ListTexture::TT_CROSS_HEIGHT);
	
	isKind = STATIC_CROSS;
	isSolid = true;

	map_level = 2;
}

StaticCross::~StaticCross(void){}