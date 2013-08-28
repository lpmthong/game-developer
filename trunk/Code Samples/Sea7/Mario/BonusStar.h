#pragma once
#include "bonusmushroom.h"

class BonusStar :
	public BonusMushroom
{
public:
	BonusStar(void);
	BonusStar(int left, int top);
	~BonusStar(void);
};
