#pragma once
#include "StaticObject.h"

class Cloud : public StaticObject{
public:
	Cloud(void);
	Cloud(int left, int top, int iid);
	~Cloud(void);

	void Update();
};