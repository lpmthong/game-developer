#include "Enemy.h"
#include "GlobalHandler.h"

Enemy::Enemy(void){

	alive = ALIVE;
	preparing = false;
	onGround = false;
	start = false;
	ConUpdate = true;
}

Enemy::~Enemy(void){}

void Enemy::Update(){

	DWORD now = GetTickCount();
	int t = now - lastUpdate;
	lastUpdate = now;

	if (preparing)
	{
		PrepareToMove(t);
	}
	else
	{
		Vy = Vy_old - 0.1f;
		VxF = Vx * t;
		VyF = Vy * t;
		CollideWithStaticObj();
		CollideWithDynamicObj();
		if (ConUpdate == true)
		{
			NormalMove(t);		
		}		
	}

	UpdateSprite();
	CheckOutScreen();
}

void Enemy::UpdateSprite()
{
	DWORD now = GetTickCount();
	if (now - lastAnimate > animatedRate)
	{
		sprite->Next();
		lastAnimate = now;
	}
}

void Enemy::UpdateSpriteDying(){
	DWORD now = GetTickCount();
	if (now - lastAnimate > animatedRate)
	{
		sprite->Next(3,3);
		lastAnimate = now;
	}
}

void Enemy::CollideWithStaticObj(){

	UpdateObjBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, VxF, VyF);

	trace(L"BFF x: %f, y: %f, w: %f, h: %f, vx: %f, vy: %f", (float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, VxF, VyF);

	list<StaticObject*>::iterator it;
	for (it = GlobalHandler::listStaticObjRender.begin(); it != GlobalHandler::listStaticObjRender.end(); ++it)
	{
		Box broadphasebox = GlobalHandler::Physic->GetSweptBroadphaseBox(ObjBox);
		Box staticBox((float)(*it)->rectDraw.left, (float)(*it)->rectDraw.top, (float)(*it)->width, (float)(*it)->height, 0.0f, 0.0f);

		if (GlobalHandler::Physic->AABBCheck(broadphasebox, staticBox))
		{
			ConUpdate = false;
			float normalx, normaly, collisiontime;
			collisiontime = GlobalHandler::Physic->SweptAABB(ObjBox, staticBox,  normalx, normaly);			
			trace(L"AABBCheck X: %d, Y: %d, OBJX: %d, OBJY: %d, Vx: %f, Vy: %f, Time: %f, Normalx: %f, Normaly: %f, ID: %d", rectDraw.left, rectDraw.top, (*it)->rectDraw.left, (*it)->rectDraw.top, ObjBox.vx, ObjBox.vy, collisiontime, normalx, normaly,(*it)->id);
			if (collisiontime < 1.0f && collisiontime >= 0.0f)
			{				
				if ((*it)->isKind == GROUND)				
					CollideWithGround(normalx, normaly, collisiontime, (*it));		
				if ((*it)->isKind == PIPE_1 || (*it)->isKind == PIPE_2 || (*it)->isKind == PIPE_3)
					CollideWithPiPe(normalx, normaly, collisiontime, (*it));
				if ((*it)->isKind == HARDBRICK)				
					ConUpdate = true;//CollideWithHardBrick(normalx, normaly, collisiontime, (*it));
				if ((*it)->isKind == OUTCOIN)				
					ConUpdate = true;
				if ((*it)->isKind == BRICK || (*it)->isKind == BRICK_BONUS_COIN || (*it)->isKind == BRICK_BONUS_GUN || 
					(*it)->isKind == BRICK_BONUS_LIFE || (*it)->isKind == BRICK_BONUS_LIFE_HIDDEN || (*it)->isKind == BRICK_BONUS_MUSHROOM || 
					(*it)->isKind == BRICK_BONUS_STAR)				
					ConUpdate = true;
				//trace(L"X: %d, Y:%d, Time: %f, Normalx: %f, Normaly: %f, ID: %d, Type: %d", (int)marioBox.x, (int)marioBox.y, collisiontime, normalx, normaly,(*it)->id, (*it)->isKind);
			}
			if (collisiontime == 1.0f)
			{
				ConUpdate = true;
				//trace(L"Flag = false, CollisionTime: %f", collisiontime);
			}
		}
	}


}

void Enemy::CollideWithDynamicObj(){

}

void Enemy::CollideWithGround(float normalx, float normaly, float collisiontime, StaticObject *obj){

}

void Enemy::CollideWithPiPe(float normalx, float normaly, float collisiontime, StaticObject *obj){
	if (normaly == 1.0f)
	{		
		if (rectDraw.right < obj->rectDraw.left + 1)
		{
			ConUpdate = true;			
			return;
		}
		Vy = 0;
		Vy_old = 0.05f;		

		onGround = true;

		ObjBox.y += VyF * collisiontime;
		UpdateRect((int)ObjBox.x, (int)ObjBox.y + 1);

		UpdateObjBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, VxF, 0);

		VyF = 0;
		ConUpdate = true;

		//trace(L"Cl x: %f, y: %f, w: %f, h: %f, vx: %f, vy: %f", marioBox.x, marioBox.y, marioBox.x, marioBox.h, marioBox.vx, marioBox.vy);
		trace(L"::CollideWithPIpe Up");
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

			ConUpdate = true;			
			//trace(L"::CollideWithGround Left or Right");			
		}
	}
}

void Enemy::CollideWithHardBrick(float normalx, float normaly, float collisiontime, StaticObject *obj){

}

void Enemy::ProcessDying(){
	isSolid = false;
	alive = DYING;
}

void Enemy::PrepareToMove(int t){

}

void Enemy::NormalMove(int t){
	int x = rectDraw.left;
	int y = rectDraw.top;	

	x += Vx * t;
	y += Vy * t;

	UpdateRect(x, y);

	Vy_old = Vy;

	if (y < 32)
		alive = INHELL;
}

void Enemy::MoveToHell(){
	isSolid = false;
	alive = DYING2;
}

void Enemy::CheckOutScreen(){
	if (rectDraw.top < 32 || rectDraw.left < -32)
	{
		alive = INHELL;
	}
}

void Enemy::UpdateObjBox(float ix, float iy, float iw, float ih, float ivx, float ivy){
	ObjBox.x = ix;
	ObjBox.y = iy;
	ObjBox.w = iw;
	ObjBox.h = ih;
	ObjBox.vx = ivx;
	ObjBox.vy = ivy;
}
