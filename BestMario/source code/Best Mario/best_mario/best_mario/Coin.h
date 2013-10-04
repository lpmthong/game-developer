#pragma once
#include "StaticObject.h"

class Coin : public StaticObject{
public:
	Coin(void);
	Coin(int left, int top);
	~Coin(void);
};
