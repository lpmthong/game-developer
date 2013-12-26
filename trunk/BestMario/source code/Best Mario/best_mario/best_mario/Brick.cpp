#include "Brick.h"
#include "GlobalHandler.h"
#include "DynamicObject.h"
#include "Enemy.h"

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
		trace(L"Brick id: %d, Cl: %d", id, hasCollide);
		CheckEnemyDie();
	}
	else if (iKind == PLAYER_ADULT || iKind == PLAYER_ADULT_GUN) // truong hop nay thi no phai bi vo nen set alive = DYING
	{
		lastCollide = GetTickCount();	
		UpdateRect(rectDraw.left, rectDraw.top + distancemoveup);
		hasCollide = true;
		alive = DYING;
		CheckEnemyDie();
		GlobalHandler::dynamicObjManager->ProcessBrickBreak(this);
	}
}

void Brick::Update()
{
	if (hasCollide)
	{
		DWORD now = GetTickCount();		

		if (now - lastCollide > 150) // tranh truong hop dung lien tiep
		{
			UpdateRect(rectDraw.left, rectDraw.top - distancemoveup);
			hasCollide = false;
			BonusAppear();
		}
	}

	UpdateSprite();
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
void Brick::BonusAppear(){
	SetEmpty();
}

void Brick::SetEmpty(){}

void Brick::CheckEnemyDie(){
	list<DynamicObject*>::iterator it;
	for (it = GlobalHandler::dynamicObjManager->listDynamicObj.begin(); it != GlobalHandler::dynamicObjManager->listDynamicObj.end(); it++)
	{
		if (GlobalHandler::CheckRectInRect((*it)->rectDraw, GlobalHandler::screen) == true)
		{			
			if (rectDraw.top < (*it)->rectDraw.top && (*it)->rectDraw.top < rectDraw.top + 33 && 
				rectDraw.left + 2 < (*it)->rectDraw.right &&  (*it)->rectDraw.left < rectDraw.right - 2)
			{
				if ((*it)->isKind == MUSHROOM_ENEMY || (*it)->isKind == TURTLE)
				{
					((Enemy*)(*it))->MoveToHell();
				}				
				return;
			}
		}
	}
}