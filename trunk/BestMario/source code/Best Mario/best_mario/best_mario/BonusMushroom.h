#pragma once
#include "Enemy.h"

class BonusMushroom: public Enemy{

	int appear;
	int type;
	float speed;

public:

	BonusMushroom(void);
	~BonusMushroom(void);
	BonusMushroom(int left, int top);

	void setBonusType(int t);
	int getBonusType();

	void PrepareToMove(int t);
	void CollideWithGround(float normalx, float normaly, float collisiontime,  StaticObject *obj);
	/*void CollideMushRoomEnemy(DynamicObject* obj);
	void CollideTurleEnemy( DynamicObject* obj );
	void CollideGround(StaticObject* obj);
	void CollideBrick(DynamicObject* obj);*/

	void Render();
	void UpdateSprite();
	
};