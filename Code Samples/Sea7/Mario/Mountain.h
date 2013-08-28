#pragma once
#include "staticobject.h"

class Mountain :
	public StaticObject
{
public:
	Mountain(void);
	Mountain(int left, int top);
	~Mountain(void);
};
