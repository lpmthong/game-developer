#pragma once
#include "StaticObject.h"

class Cloud : public StaticObject{
public:
	Cloud(void);
	Cloud(int left, int top);
	~Cloud(void);

	void Update();
};