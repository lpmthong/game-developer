#pragma once
#include "DynamicObject.h"
#include <list>
#include "StaticObject.h"
#include "Box.h"
using namespace std;

class Enemy : public DynamicObject{

public:
	DWORD beginDeath; //Luc bat dau chet
	DWORD deathTime; //Thoi gian de chet :))

	StaticObject* brick; // de kiem tra chet khi bi tung vien gach

	bool preparing;
	bool onGround;
	bool ConUpdate;

	float VxF, VyF; // V per frame

	Box ObjBox;
public:

	Enemy(void);
	~Enemy(void);

	virtual void Update();
	virtual void UpdateSprite();
	virtual void UpdateSpriteDying();

	//Kiem tra va cham
	virtual void CollideWithStaticObj();
	virtual void CollideWithDynamicObj(int t);

	virtual void CollideWithGround(float normalx, float normaly, float collisiontime,  StaticObject *obj);	
	virtual void CollideWithPiPe(float normalx, float normaly, float collisiontime,  StaticObject *obj);
	virtual void CollideWithBrick(float normalx, float normaly, float collisiontime,  StaticObject *obj);

	virtual void CollideWithMushRoomEnemy(DynamicObject* obj);
	virtual void CollideWithTurtleEnemy(DynamicObject* obj);
	virtual void CollideWithTurtleDeath(DynamicObject* obj);
	virtual void CollideWithPirhanaPlant(DynamicObject* obj);

	//Cac ham khac
	virtual void ProcessDying();

	virtual void PrepareToMove(int t);
	virtual void NormalMove(int t);

	virtual void MoveToHell();
	virtual void CheckOutScreen();
	virtual void UpdateObjBox(float ix, float iy, float iw, float ih, float ivx, float ivy);
};