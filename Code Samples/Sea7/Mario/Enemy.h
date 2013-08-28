#pragma once
#include "dynamicobject.h"
#include <list>
#include "StaticObject.h"
using namespace std;

class Enemy :
	public DynamicObject
{
public:
	DWORD beginDeath;
	DWORD deathTime;

	//Use to check if player want to make this enemy die by hitting a brick.
	DynamicObject* oldBrick;
	int oldBrickTop;

	//Enemy is preparing to move and is not ready to move.
	bool preparing;

	list<DynamicObject*> liCollidedObj;

	bool onGround;

	bool debug;
public:
	Enemy(void);
	~Enemy(void);

	virtual void Update();
	virtual void UpdateSprite();
	virtual void UpdateSpriteDying();

	//handle collision with object in quadtree.
	virtual void HandleCollisionQT();

	//handle collision with object in dynamic object list.
	virtual void HandleCollisionDO();

	virtual void CollidePIPE(int type, RECT rec);
	virtual void CollideGround(StaticObject* obj);
	virtual void CollideBrick(DynamicObject* obj);
	virtual void CollideMushRoomEnemy(DynamicObject* obj);
	virtual void CollideTurleEnemy( DynamicObject* obj );
	virtual void CollidePirhanaPlant(DynamicObject* obj);

	virtual void ProcessDying();

	//Check to see if this can be death by hitting brick.
	virtual void DieByHittinBrick();
	virtual void MoveToHell();

	virtual void PrepareToMove(int t);
	virtual void NormalMove(int t);

	virtual void CheckOutScreen();

	virtual void Revive();
	void CollideTurleDeath( DynamicObject* obj );
	virtual void UpdateOtherObject();
};
