#pragma once
#include "staticobject.h"

class Coin :
	public StaticObject
{
public:
	Coin(void);
	Coin(int left, int top);
	~Coin(void);
};
