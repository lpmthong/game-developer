#pragma once
#include "StaticObject.h"

class Fence : public StaticObject{

public:
	Fence(void);
	Fence(int left, int top);
	~Fence(void);

};