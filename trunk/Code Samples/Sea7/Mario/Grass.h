#pragma once
#include "staticobject.h"

class Grass :
	public StaticObject
{
public:
	Grass(void);
	Grass(int left, int top);
	~Grass(void);
};
