#include "FallingCross.h"
#include "GlobalHandler.h"


FallingCross::FallingCross(void){}

FallingCross::~FallingCross(void){}

FallingCross::FallingCross(int left, int top, int iid){

	sprite = new Sprite(ListTexture::TT_FALLING_CROSS, ListTexture::TT_CROSS_WIDTH, ListTexture::TT_CROSS_HEIGHT, 1, 1);

	id = iid;
	width = ListTexture::TT_CROSS_WIDTH;
	height = ListTexture::TT_CROSS_HEIGHT;

	UpdateRect(left, top , ListTexture::TT_CROSS_WIDTH, ListTexture::TT_CROSS_HEIGHT);

	isKind = FALLING_CROSS;
	isSolid = true;
	touch = false;

	map_level = 2;

}

void FallingCross::ProcessCollision(int iKind){

	touch = true;
	isSolid = false;

}

void FallingCross::Update(){

	if (!touch)
		return;
	
	UpdateRect( rectDraw.left, rectDraw.top - 7);	

}

void FallingCross::Render(){

	RECT screen = GlobalHandler::screen;
	sprite->Render(backbuffer, rectDraw.left, rectDraw.top, screen.left , screen.bottom);

	if (rectDraw.top < 0)
	{
		GlobalHandler::quadTree->RemoveObj(this);
	}
}