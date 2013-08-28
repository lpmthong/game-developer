#include "HardBrick.h"

HardBrick::HardBrick(void)
{
}

HardBrick::HardBrick( int left, int top )
{
	sprite = new Sprite(ListTexture::TT_HARD_BRICK, 
						ListTexture::TT_HARD_BRICK_WIDTH, 
						ListTexture::TT_HARD_BRICK_HEIGHT, 
						ListTexture::TT_HARD_BRICK_COUNT, 
						ListTexture::TT_HARD_BRICK_SPRITEPERROW);

	width = ListTexture::TT_HARD_BRICK_WIDTH;
	height = ListTexture::TT_HARD_BRICK_HEIGHT;

	UpdateRect(left, top, ListTexture::TT_HARD_BRICK_WIDTH, ListTexture::TT_HARD_BRICK_HEIGHT);

	iKind = HARDBRICK;
	isSolid = true;

	isHardBrick = true;

	//Just init it, dont let it start to do anything.
	start = false;
}

HardBrick::~HardBrick(void)
{
}
