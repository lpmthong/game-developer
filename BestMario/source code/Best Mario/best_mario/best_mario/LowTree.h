#pragma once
#include "StaticObject.h"

class LowTree : public StaticObject
{
public:
	LowTree(void);
	LowTree(int left, int top, int iid);
	~LowTree(void);
};
