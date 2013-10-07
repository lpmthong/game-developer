#pragma once
#include <list>
#include "DynamicObject.h"
using namespace std;

class DynamicObjManager{

public:
	list<DynamicObject*> listDynamicObj;
	DynamicObjManager(void);
	void Add(DynamicObject *obj);
	void Remove(DynamicObject *obj);
	void Render();
	void Update();

	void GetTick();
	void Release();
	//void Reset();

	~DynamicObjManager(void);
		
	//bool InList(list<DynamicObject*> holder, DynamicObject* obj);

};