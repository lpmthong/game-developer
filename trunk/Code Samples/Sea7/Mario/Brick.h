#pragma once
#include "staticobject.h"
#include "ListTexture.h"

class Brick :
	public DynamicObject
{
protected:
	DWORD lastCollide;

	bool isHardBrick;

	//the distance this brick move up when player touch it.
	int dis;

public:
	//This brick has just collide with player.
	bool hasCollide;
public:
	Brick(void);
	Brick(int left, int top);

	virtual void ProcessCollision(int iKind);

	virtual void BonusAppear();

	virtual void SetEmpty();

	virtual void Update();
	void UpdateSprite();

	~Brick(void);
};
