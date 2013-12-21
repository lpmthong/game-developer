#include "Brick.h"
#include "GlobalHandler.h"

Brick::Brick(void){}

Brick::~Brick(void){}

Brick::Brick(int left, int top, int iid){
	sprite = new Sprite(ListTexture::TT_BRICK, ListTexture::TT_BRICK_WIDTH, ListTexture::TT_BRICK_HEIGHT, 
						ListTexture::TT_BRICK_COUNT, ListTexture::TT_BRICK_SPRITEPERROW);

	width = ListTexture::TT_BRICK_WIDTH;
	height = ListTexture::TT_BRICK_HEIGHT;
	alive = ALIVE;

	id = iid;
	isKind = BRICK;
	isSolid = true;

	UpdateRect(left, top, ListTexture::TT_BRICK_WIDTH, ListTexture::TT_BRICK_HEIGHT);

	lastCollide = GetTickCount();
	lastAnimate = GetTickCount();
	hasCollide = false;
	distancemoveup = 3;

	isHardBrick = false;

	map_level = 2;
	start = false;
}

void Brick::ProcessCollision(int iKind)
{
	if (isHardBrick)
		return;

	if (iKind == PLAYER_KID && hasCollide == false)
	{
		lastCollide = GetTickCount();
		hasCollide = true;
		UpdateRect(rectDraw.left, rectDraw.top + distancemoveup);
	}
	else if (iKind == PLAYER_ADULT || iKind == PLAYER_ADULT_GUN) // truong hop nay thi no phai bi vo nen set alive = DYING
	{
		lastCollide = GetTickCount();	
		UpdateRect(rectDraw.left, rectDraw.top + distancemoveup);
		hasCollide = true;
		alive = DYING;		
		GlobalHandler::dynamicObjManager->ProcessBrickBreak(this);	
	}
}

void Brick::Update()
{
	if (hasCollide)
	{
		DWORD now = GetTickCount();

		//if (alive == DYING) // neu ma no bi vo
		//{
		//	if (now - lastCollide > 20)
		//		GlobalHandler::dynamicObjManager->ProcessBrickBreak(this);	
		//	return;
		//}

		if (now - lastCollide > 150) // tranh truong hop dung lien tiep
		{
			UpdateRect(rectDraw.left, rectDraw.top - distancemoveup);
			hasCollide = false;
		}
	}
}

void Brick::UpdateSprite()
{
	DWORD now = GetTickCount();
	if(now - lastAnimate > animatedRate){
		sprite->Next();
		lastAnimate = now;
	}
}

//Hai ham nay de danh khi ke thua
void Brick::BonusAppear(){}

void Brick::SetEmpty(){}