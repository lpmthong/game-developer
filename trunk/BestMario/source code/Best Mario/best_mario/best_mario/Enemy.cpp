#include "Enemy.h"
#include "GlobalHandler.h"
#include "Brick.h"

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
		if (alive == DYING || alive == INHELL)
		{
			if (now - beginDeath > deathTime)
				alive = INHELL;
			UpdateSpriteDying();
			return;
		}
		
		Vy = Vy_old - 0.05f;
		VxF = Vx * t;
		VyF = Vy * t;

		if (alive != DYING2)
		{
			CollideWithStaticObj();
			CollideWithDynamicObj(t);
		}		

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

	list<StaticObject*> listStatic;
	UpdateObjBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, VxF, VyF);	
	

	if (isKind == TURTLE || isKind == TURTLEDEATH)
	{		
		GlobalHandler::quadTree->GetListObjCanCollide(rectDraw);
		listStatic = GlobalHandler::listStaticObjCanCollide;
	}
	else
	{
		listStatic = GlobalHandler::listStaticObjRender;
	}
	

	list<StaticObject*>::iterator it;
	for (it = listStatic.begin(); it != listStatic.end(); ++it)
	{		
		if ((*it)->isSolid == true)
		{
			Box broadphasebox = GlobalHandler::Physic->GetSweptBroadphaseBox(ObjBox);
			Box staticBox((float)(*it)->rectDraw.left, (float)(*it)->rectDraw.top, (float)(*it)->width, (float)(*it)->height, 0.0f, 0.0f);

			if (GlobalHandler::Physic->AABBCheck(broadphasebox, staticBox))
			{
				ConUpdate = false;
				float normalx, normaly, collisiontime;
				collisiontime = GlobalHandler::Physic->SweptAABB(ObjBox, staticBox,  normalx, normaly);				
				if (collisiontime < 1.0f && collisiontime >= 0.0f)
				{				
					if ((*it)->isKind == GROUND || (*it)->isKind == HARDBRICK || (*it)->isKind == BRICK_BONUS_COIN || 
						(*it)->isKind == BRICK_BONUS_GUN || (*it)->isKind == BRICK_BONUS_LIFE || 
						(*it)->isKind == BRICK_BONUS_LIFE_HIDDEN || (*it)->isKind == BRICK_BONUS_MUSHROOM || 
						(*it)->isKind == BRICK_BONUS_STAR || (*it)->isKind == STATIC_CROSS)				
						CollideWithGround(normalx, normaly, collisiontime, (*it));				
					if ((*it)->isKind == PIPE_1 || (*it)->isKind == PIPE_2 || (*it)->isKind == PIPE_3 ||
						(*it)->isKind == PIPE_4 || (*it)->isKind == PIPE_5)
						CollideWithPiPe(normalx, normaly, collisiontime, (*it));
					if ((*it)->isKind == OUTCOIN)				
						ConUpdate = true;
					if ((*it)->isKind == BRICK)				
						CollideWithBrick(normalx, normaly, collisiontime, (*it));
					if ((*it)->isKind == PIRHANAPLANT)
						CollideWithPirhanaPlant((*it));
				}
				if (collisiontime == 1.0f)
				{
					ConUpdate = true;				
				}
			}
		}		
	}
}

void Enemy::CollideWithDynamicObj(int t){
	list<DynamicObject*> result;
	list<DynamicObject*>::iterator it;
	for (it = GlobalHandler::dynamicObjManager->listDynamicObj.begin(); it != GlobalHandler::dynamicObjManager->listDynamicObj.end(); ++it)
	{
		if ((this) != (*it))		
			if ((*it)->isSolid == true)
			{
				float Obj_VxF = (*it)->Vx * t;
				float Obj_VyF = (*it)->Vy * t;
				float VxFN = VxF - Obj_VxF;
				float VyFN = VyF - Obj_VyF;
				UpdateObjBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, VxFN, VyFN);
				Box broadphasebox = GlobalHandler::Physic->GetSweptBroadphaseBox(ObjBox);
				Box staticBox((float)(*it)->rectDraw.left, (float)(*it)->rectDraw.top, (float)(*it)->width, (float)(*it)->height, 0.0f, 0.0f);
				if (GlobalHandler::Physic->AABBCheck(broadphasebox, staticBox))
				{
					ConUpdate = true;
					float normalx, normaly, collisiontime;
					collisiontime = GlobalHandler::Physic->SweptAABB(ObjBox, staticBox,  normalx, normaly);
					if (collisiontime < 1.0f && collisiontime >= 0.0f)
					{
						if ((*it)->isKind == BONUS_MUSHROOM)
							ConUpdate = true;
						if ((*it)->isKind == MUSHROOM_ENEMY)
							CollideWithMushRoomEnemy((*it));
						if ((*it)->isKind == TURTLE || (*it)->isKind == RED_TURTLE)
							CollideWithTurtleEnemy((*it));
						if ((*it)->isKind == TURTLEDEATH || (*it)->isKind == RED_TURTLE_DEATH)
							CollideWithTurtleDeath((*it));						
					}
					if (collisiontime == 1.0f)
						ConUpdate = true;

				}				
			}		
	}
}

void Enemy::CollideWithGround(float normalx, float normaly, float collisiontime, StaticObject *obj){
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
			if (rectDraw.top < obj->rectDraw.top + 30 && rectDraw.top > obj->rectDraw.top - 32)
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
			}
			ConUpdate = true;				
		}
	}
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
		UpdateRect((int)ObjBox.x, (int)ObjBox.y);

		UpdateObjBox((float)rectDraw.left, (float)rectDraw.top, (float)width, (float)height, VxF, 0);

		VyF = 0;
		ConUpdate = true;

		//trace(L"Cl x: %f, y: %f, w: %f, h: %f, vx: %f, vy: %f", marioBox.x, marioBox.y, marioBox.x, marioBox.h, marioBox.vx, marioBox.vy);
		//trace(L"::CollideWithPIpe Up");
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

void Enemy::CollideWithBrick(float normalx, float normaly, float collisiontime, StaticObject *obj){
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
			if (rectDraw.top < obj->rectDraw.top + 30 && rectDraw.top > obj->rectDraw.top - 32)
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
			}
			ConUpdate = true;				
		}
	}
}

void Enemy::CollideWithMushRoomEnemy(DynamicObject* obj){
	ConUpdate = true;
}

void Enemy::CollideWithTurtleEnemy(DynamicObject* obj){
	ConUpdate = true;
}

void Enemy::CollideWithTurtleDeath(DynamicObject* obj){
	
	if (obj->Vx != 0.0f)
	{
		MoveToHell();
	}
	else
		ConUpdate = true;

}

void Enemy::CollideWithPirhanaPlant(StaticObject* obj){
	ConUpdate = true;
}

void Enemy::ProcessDying(){
	isSolid = false;
	alive = DYING;
	beginDeath = GetTickCount();	
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

	Score* score = new Score(rectDraw.left, rectDraw.top);
	score->setScore(200);
	GlobalHandler::dynamicObjManager->Add(score);
}

void Enemy::CheckOutScreen(){
	if (rectDraw.top < 32 || rectDraw.left < 0)
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
