#pragma once
#include "enemy.h"

class BonusMushroom :
	public Enemy
{
	float appear;
	int speed;
	int type;
public:
	BonusMushroom(void);
	BonusMushroom(int left, int top);
	~BonusMushroom(void);

	void setBonusType(int t);
	int getBonusType();

	void PrepareToMove(int t);
	void CollideMushRoomEnemy(DynamicObject* obj);
	void CollideTurleEnemy( DynamicObject* obj );
	void CollideGround(StaticObject* obj);
	void CollideBrick(DynamicObject* obj);


	void Render();
	void UpdateSprite();

	void MoveToHell();
};
