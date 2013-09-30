#pragma once
#include "StaticObject.h"

class Mountain : public StaticObject
{
public:
	Mountain(void);
	Mountain(int left, int top);
	~Mountain(void);
};
