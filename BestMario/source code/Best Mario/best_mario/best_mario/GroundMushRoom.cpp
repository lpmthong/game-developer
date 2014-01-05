#include "GroundMushRoom.h"
#include "Define.h"
#include "ListTexture.h"

GroundMushRoom::GroundMushRoom(void){}

GroundMushRoom::GroundMushRoom(int left, int top, int iid){

	sprite = new Sprite(ListTexture::TT_GROUND_MUSHROOM, 
		ListTexture::TT_GROUND_MUSHROOM_WIDTH, 
		ListTexture::TT_GROUND_MUSHROOM_HEIGHT, 
		ListTexture::TT_GROUND_MUSHROOM_COUNT, 
		ListTexture::TT_GROUND_MUSHROOM_SPRITEPERROW);

	id = iid;
	width = ListTexture::TT_GROUND_MUSHROOM_WIDTH;
	height = ListTexture::TT_GROUND_MUSHROOM_HEIGHT;
	UpdateRect(left, top, ListTexture::TT_GROUND_MUSHROOM_WIDTH, ListTexture::TT_GROUND_MUSHROOM_HEIGHT);
	map_level = 2;
	isKind = GROUND;
	isSolid = true;
}

GroundMushRoom::~GroundMushRoom(void){}

void GroundMushRoom::setType(int t){

	type = t;

	switch(type){
	case GROUND_MUSHROOM_LEFT:
		sprite->setIndex(0);
		break;
	case GROUND_MUSHROOM_MIDDLE:
		sprite->setIndex(1);
		break;
	case GROUND_MUSHROOM_RIGHT:
		sprite->setIndex(2);
		break;	
	default:
		break;
	}
}

void GroundMushRoom::Update(){
	return;
}