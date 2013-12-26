#include "Bullet.h"
#include "GlobalHandler.h"
#include "ListTexture.h"
#include "PirhanaPlant.h"

Bullet::Bullet(void){}

Bullet::~Bullet(void){}

Bullet::Bullet(int left, int top){

	sprite = new Sprite(ListTexture::TT_BULLET, ListTexture::TT_BULLET_WIDTH, ListTexture::TT_BULLET_HEIGHT,
						ListTexture::TT_BULLET_COUNT, ListTexture::TT_BULLET_SPRITEPERROW);

	animatedRate = ListTexture::TT_BULLET_ANIMATED_RATE;
	width = ListTexture::TT_BULLET_WIDTH;
	height = ListTexture::TT_BULLET_HEIGHT;
	UpdateRect(left, top, ListTexture::TT_BULLET_WIDTH, ListTexture::TT_BULLET_HEIGHT);

	isKind = BULLET;
	isSolid = true;

	lastUpdate = GetTickCount();
	lastAnimate = GetTickCount();

	Vy_old = 0.05f;
	Vy = 0.0f;
	Vx = 0.3f;

	start = false;

}

void Bullet::CollideWithGround(float normalx, float normaly, float collisiontime, StaticObject *obj){
	if (normaly == 1.0f)
	{		
		if (rectDraw.right < obj->rectDraw.left + 1)
		{
			ConUpdate = true;			
			return;
		}
		Vy = 0.35f;
		Vy_old = 0;

		onGround = true;

		ObjBox.y += VyF * collisiontime;
		UpdateRect((int)ObjBox.x, (int)ObjBox.y);

		UpdateObjBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, VxF, 0);

		VyF = 0;
		ConUpdate = true;		
	}
	else
	{
		if (normaly == -1.0f)
		{

		}
		else
		{	
			//Cai if nay de laoi may truong hop ma no va cham chi ngay cai mep
			if (rectDraw.top < obj->rectDraw.top + 15 && rectDraw.top > obj->rectDraw.top - 32)
			{
				ProcessDying();
			}					
			ConUpdate = true;
		}
	}	
}

void Bullet::CollideWithPiPe(float normalx, float normaly, float collisiontime, StaticObject *obj){
	if (normaly == 1.0f)
	{		
		if (rectDraw.right < obj->rectDraw.left + 1)
		{
			ConUpdate = true;			
			return;
		}
		Vy = 0.35f;
		Vy_old = 0;

		onGround = true;

		ObjBox.y += VyF * collisiontime;
		UpdateRect((int)ObjBox.x, (int)ObjBox.y);

		UpdateObjBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, VxF, 0);

		VyF = 0;
		ConUpdate = true;
		trace(L"G UP");
	}
	else
	{
		if (normaly == -1.0f)
		{

		}
		else
		{	
			if (normalx == -1.0f)
			{
				ObjBox.x = obj->rectDraw.left - rectDraw.right + rectDraw.left;
				UpdateRect((int)ObjBox.x, (int)ObjBox.y);
			}
			else
			{
				ObjBox.x = obj->rectDraw.right + 1;
				UpdateRect((int)ObjBox.x, (int)ObjBox.y);
			}

			Vx = - Vx;			
			VxF = 0;			

			UpdateObjBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, 0, VyF);
			ProcessDying();
			ConUpdate = true;
		}
	}
}

void Bullet::CollideWithBrick(float normalx, float normaly, float collisiontime, StaticObject *obj){
	if (normaly == 1.0f)
	{		
		if (rectDraw.right < obj->rectDraw.left + 1)
		{
			ConUpdate = true;			
			return;
		}
		Vy = 0.35f;
		Vy_old = 0;

		onGround = true;

		ObjBox.y += VyF * collisiontime;
		UpdateRect((int)ObjBox.x, (int)ObjBox.y);

		UpdateObjBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, VxF, 0);

		VyF = 0;
		ConUpdate = true;		
	}
	else
	{
		if (normaly == -1.0f)
		{

		}
		else
		{	
			//Cai if nay de laoi may truong hop ma no va cham chi ngay cai mep
			if (rectDraw.top < obj->rectDraw.top + 15 && rectDraw.top > obj->rectDraw.top - 32)
			{
				ProcessDying();
			}					
			ConUpdate = true;
		}
	}
}

void Bullet::CollideWithMushRoomEnemy(DynamicObject* obj){
	ProcessDying();
	((Enemy*)obj)->MoveToHell();
}

void Bullet::CollideWithTurtleEnemy(DynamicObject* obj){
	ProcessDying();
	((Enemy*)obj)->MoveToHell();
}

void Bullet::CollideWithTurtleDeath(DynamicObject* obj){
	ProcessDying();
	((Enemy*)obj)->MoveToHell();
}

void Bullet::CollideWithPirhanaPlant(DynamicObject* obj){
	if (((PirhanaPlant*)obj)->appear != 0)
	{
		ProcessDying();
		obj->alive = INHELL;
	}	
}

void Bullet::ProcessDying(){
	__super::ProcessDying();

	Vx = 0;
	animatedRate = 30;
	deathTime = 100;

	GlobalHandler::player->numOfBullet--;
}

void Bullet::UpdateSpriteDying(){
	DWORD now = GetTickCount();
	if (now - lastAnimate > animatedRate)
	{
		sprite->setDistanceFromTop(ListTexture::TT_BULLET_WIDTH);
		sprite->setWidthHeight(31,31);
		sprite->Next(0,2);
		lastAnimate = now;
	}
}

void Bullet::MoveToHell(){

}

void Bullet::CheckOutScreen(){
	if (GlobalHandler::CheckRectInRect(rectDraw, GlobalHandler::screen) == false)
	{
		GlobalHandler::player->numOfBullet--;
		alive = INHELL;
	}
}

void Bullet::setDirect(int dir){
	if (dir == LEFT)
	{
		Vx = -0.3f;
	}
	else
	{
		Vx = 0.3f;
	}
}