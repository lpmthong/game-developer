#pragma once
#include "Object.h"

class Element
{
public:
	Object *object;
	Element *next;
public:
	Element(Object *Obj);
};

class MyArrayList
{
private:
	Element *Head;
	Element *Tail;
public:
	int Count;
	MyArrayList(void);
	bool Add(Object *Obj);
	bool AddArray(Object *Obj[],int Number);
	Object *operator [](int i);
	bool Remove(Object *Obj,bool IsDelete);
	void Clear();
public:
	~MyArrayList(void);
};