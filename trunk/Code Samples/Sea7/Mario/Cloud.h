#pragma once
#include "staticobject.h"

class Cloud :
	public StaticObject
{
public:
	Cloud(void);
	Cloud(int left, int top);
	~Cloud(void);

public:
	void Update();
};
