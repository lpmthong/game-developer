#pragma once
#include "staticobject.h"

class GroundUnderMushroom :
	public StaticObject
{
public:
	GroundUnderMushroom(void);
	GroundUnderMushroom(int left, int top);
	~GroundUnderMushroom(void);
};
