#pragma once
#include "Enemy.h"

class MushroomEnemy : public Enemy{

public:
	MushroomEnemy(void);
	MushroomEnemy(int left, int top, int iid);
	~MushroomEnemy(void);

	void MoveToHell();
	void UpdateSprite();
};