#pragma once
#include "dynamicobject.h"
#include "Enemy.h"

class MushroomEnemy :
	public Enemy
{
public:
	MushroomEnemy(void);
	MushroomEnemy(int left, int top);
	~MushroomEnemy(void);

	void MoveToHell();
	void UpdateSprite();
};
