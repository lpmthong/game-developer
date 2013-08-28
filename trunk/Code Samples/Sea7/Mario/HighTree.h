#pragma once
#include "staticobject.h"

class HighTree :
	public StaticObject
{
public:
	HighTree(void);
	HighTree(int left, int top);
	~HighTree(void);
};
