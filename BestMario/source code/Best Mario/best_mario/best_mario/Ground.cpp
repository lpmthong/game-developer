#include "Ground.h"
#include "Define.h"
#include "ListTexture.h"

Ground::Ground(void){}

Ground::Ground(int left, int top){

	sprite = new Sprite(ListTexture::TT_GROUND, ListTexture::TT_GROUND_WIDTH, ListTexture::TT_GROUND_HEIGHT,
						ListTexture::TT_GROUND_COUNT, ListTexture::TT_GROUND_SPRITEPERROW);

	width = ListTexture::TT_GROUND_WIDTH;
	height = ListTexture::TT_GROUND_HEIGHT;
	UpdateRect(left, top, ListTexture::TT_GROUND_WIDTH, ListTexture::TT_GROUND_HEIGHT);

	isKind = GROUND;
	isSolid = true;
}

Ground::~Ground(void){}

void Ground::setType(int type){
	switch(type){
		case GROUND_LEFT:
			sprite->setIndex(0);
			break;
		case GROUND_MIDDLE:
			sprite->setIndex(1);
			break;
		case GROUND_RIGHT:
			sprite->setIndex(2);
			break;
		case GROUND_SOIL:
			sprite->setIndex(3);
			break;
		case GROUND_SOIL_LEFT:
			sprite->setIndex(4);
			break;
		case GROUND_SOIL_RIGHT:
			sprite->setIndex(5);
			break;
		case GROUND_DARK_SOIL:
			sprite->setIndex(6);
			break;
		default:
			break;
	}
}

void Ground::Update(){
	return;
}