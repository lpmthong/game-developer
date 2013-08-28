#pragma once
#include "staticobject.h"

class LowTree :
	public StaticObject
{
public:
	LowTree(void);
	LowTree(int left, int top);
	~LowTree(void);
};
