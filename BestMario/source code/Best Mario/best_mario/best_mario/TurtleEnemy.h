#pragma once
#include "Enemy.h"

class TurtleEnemy : public Enemy{

public:
	bool stopUpdateSprite;
	DWORD beginDeath;
	DWORD timeInDeath;

	float old_Vx;
	bool moving;
public:

	TurtleEnemy(void);
	TurtleEnemy(int left, int top, int iid);
	~TurtleEnemy(void);

	void UpdateSprite();
	void UpdateSpriteDying();
	void MoveToHell();

	void ProcessDying();

	virtual void setAlive();
	virtual void setDeath();

	void setDeathMoving();
};