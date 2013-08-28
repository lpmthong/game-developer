#pragma once
#include "dynamicobject.h"
#include "Enemy.h"
#include "StaticObject.h"

class Bullet :
	public Enemy
{
private:
	int dyingLevel;		//We have three sprite for handling dying, this variable is used for that.
public:
	Bullet(void);
	Bullet(int left, int top);
	~Bullet(void);

	void CollidePIPE(int type, RECT rec);
	void CollideGround(StaticObject* obj);
	void CollideBrick(DynamicObject* obj);
	void CollideMushRoomEnemy(DynamicObject* obj);
	void CollideTurleEnemy(DynamicObject* obj);
	void CollidePirhanaPlant(DynamicObject* obj);

	void ProcessDying();
	void UpdateSpriteDying();

	void CheckOutScreen();

	void setDirect(int dir);

	void MoveToHell();
};
