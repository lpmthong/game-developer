#pragma once
#include "StaticObject.h"

class StaticCross : public StaticObject{

public:

	StaticCross(void);
	StaticCross(int left, int top, int iid);
	~StaticCross(void);
};