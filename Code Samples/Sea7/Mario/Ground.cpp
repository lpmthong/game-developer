#include "Ground.h"
#include "ListTexture.h"

Ground::Ground(void)
{
}

Ground::Ground( int left, int top)
{
	sprite = new Sprite(ListTexture::TT_GROUND, 
		ListTexture::TT_GROUND_WIDTH, 
		ListTexture::TT_GROUND_HEIGHT, 
		ListTexture::TT_GROUND_COUNT, 
		ListTexture::TT_GROUND_SPRITEPERROW);


	width = ListTexture::TT_GROUND_WIDTH;
	height = ListTexture::TT_GROUND_HEIGHT;
	UpdateRect(left, top, ListTexture::TT_GROUND_WIDTH, ListTexture::TT_GROUND_HEIGHT);
	map_level = 2;

	iKind = GROUND;

	isSolid = true;
}

Ground::~Ground(void)
{
}

void Ground::setType( int t )
{
	type = t;
	if (type == GROUND_LEFT)
		sprite->setIndex(0);
	else if (type == GROUND_MIDDLE)
		sprite->setIndex(1);
	else if (type == GROUND_RIGHT)
		sprite->setIndex(2);
	else if (type == GROUND_SOIL)
		sprite->setIndex(3);
	else if (type == GROUND_SOIL_LEFT)
		sprite->setIndex(4);
	else if (type == GROUND_SOIL_RIGHT)
		sprite->setIndex(5);
	else if (type == GROUND_DARK_SOIL)
		sprite->setIndex(6);
}

void Ground::Render()
{
	RECT screen = GlobalHandler::screen;
//	if (type == GROUND_SOIL_LEFT)
	//	sprite->Render(GlobalHandler::directX->backbuffer, recDrawArea.left - screen.left, recDrawArea.top - screen.top,
	//128, 0, 17, 32);
//	{
///	
//	}
//	else
		sprite->Render(GlobalHandler::directX->backbuffer, recDrawArea.left - screen.left, recDrawArea.top - screen.top);
}
