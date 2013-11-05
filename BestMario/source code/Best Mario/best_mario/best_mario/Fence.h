#pragma once
#include "StaticObject.h"

class Fence : public StaticObject{

public:
	Fence(void);
	Fence(int left, int top, int iid);
	~Fence(void);

};