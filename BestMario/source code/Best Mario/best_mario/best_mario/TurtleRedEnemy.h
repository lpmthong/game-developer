#pragma once
#include "TurtleEnemy.h"

class TurtleRedEnemy : public TurtleEnemy{


public:

	TurtleRedEnemy(void);
	TurtleRedEnemy(int left, int top, int iid);
	~TurtleRedEnemy(void);

	void UpdateSprite();
	void setAlive();
	void setDeath();
};