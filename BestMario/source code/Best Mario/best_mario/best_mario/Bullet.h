#pragma once
#include "Enemy.h"

class Bullet : public Enemy{

public:
	Bullet(void);
	Bullet(int left, int top);
	~Bullet(void);

	void CollideWithGround(float normalx, float normaly, float collisiontime, StaticObject *obj);
	void CollideWithPiPe(float normalx, float normaly, float collisiontime, StaticObject *obj);
	void CollideWithBrick(float normalx, float normaly, float collisiontime, StaticObject *obj);
	
	void CollideWithTurtleDeath(DynamicObject* obj);
	void CollideWithMushRoomEnemy(DynamicObject* obj);
	void CollideWithTurtleEnemy(DynamicObject* obj);
	void CollideWithPirhanaPlant(StaticObject* obj);

	void ProcessDying();
	void UpdateSpriteDying();

	void MoveToHell();

	void CheckOutScreen();
	void setDirect(int dir);
};