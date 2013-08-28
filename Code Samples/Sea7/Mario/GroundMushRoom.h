#pragma once
#include "ground.h"

class GroundMushRoom :
	public Ground
{
public:
	GroundMushRoom(void);
	GroundMushRoom(int left, int top);
	~GroundMushRoom(void);

	void setType(int t);
};
