#pragma once
#include "DynamicObject.h"
#include <list>
using namespace std;

class DynamicObjManager
{
	list<DynamicObject*> liDynamicObj;
public:
	DynamicObjManager(void);

	void Add(DynamicObject* obj);
	void Remove(DynamicObject* obj);
	void Update();
	void Render();

	void GetTick();

	void Release();
	void Reset();

	//Check collision between obj with dynamic object manager without object in holder.
	DynamicObject* CheckCollision(DynamicObject* obj, list<DynamicObject*> holder);

	//Happen when mario adult collide with a brick.
	void ProcessBrickBreak(DynamicObject* brick);
	~DynamicObjManager(void);

	//Check to see if obj is in holder or not.
	bool InList(list<DynamicObject*> holder, DynamicObject* obj);

	//Save file.
	void SaveFile();
};
