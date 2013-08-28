#pragma once
#include "turleenemy.h"

class RedTurleEnemy :
	public TurleEnemy
{
	//Use 2 object on 2 side of this turle to handle its AI.
//	TurleEnemy* objLeft;
	//Handle AI of this turle. This obj is in left bottom corner to check if turle is about falling.
	DynamicObject* objAI;
public:
	RedTurleEnemy(void);
	RedTurleEnemy( int left, int top );
	~RedTurleEnemy(void);

	void setAlive();
	void setDeath();
	void UpdateOtherObject();

	//this object go out of ground it is being in.
	//obj: objLeft or objRight.
	bool CheckOutGround(TurleEnemy* obj);

	void CollideGround(StaticObject* obj);
	void CollideBrick(DynamicObject* obj);

	void Render();
};
