#pragma once
#include "enemy.h"

class TurleEnemy :
	public Enemy
{
public:
	bool stopUpdateSprite;

	DWORD beginDeath;
	DWORD timeInDeath;
	int directBeforeDeath;

public:
	bool moving;
public:
	TurleEnemy(void);
	TurleEnemy(int left, int top);
	~TurleEnemy(void);

	void UpdateSprite();
	void UpdateSpriteDying();
	void ProcessDying();

	void MoveToHell();

	virtual void setDeath();
	virtual void setAlive();

	void setDeathMoving();

	void Revive();
};
