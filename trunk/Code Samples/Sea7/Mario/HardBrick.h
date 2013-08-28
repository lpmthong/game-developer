#pragma once
#include "brick.h"

class HardBrick :
	public Brick
{
public:
	HardBrick(void);
	HardBrick(int left, int top);
	~HardBrick(void);
};
