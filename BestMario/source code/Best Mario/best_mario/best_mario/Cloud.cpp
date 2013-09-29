#include "Cloud.h"
#include "ListTexture.h"
#include "Define.h"

Cloud::Cloud(void){}

Cloud::Cloud(int left, int top){
	sprite = new Sprite(ListTexture::TT_CLOUD, ListTexture::TT_CLOUD_WIDTH, ListTexture::TT_CLOUD_HEIGHT,
						ListTexture::TT_CLOUD_COUNT,ListTexture::TT_CLOUD_SPRITEPERROW);

	UpdateRect(left, top, width, height);
	isKind = CLOUD;
	isSolid = false;

	animatedRate = ListTexture::TT_CLOUD_ANIMATED_RATE;
	lastAnimate = GetTickCount();
}

Cloud::~Cloud(void){}

void Cloud::Update(){
	DWORD now = GetTickCount();
	if(now - lastAnimate > animatedRate){
		sprite->Next();
		lastAnimate = now;
	}
}