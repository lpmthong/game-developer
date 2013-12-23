#pragma once
#include "DynamicObject.h"

class CoinPickUp : public DynamicObject
{
	int distanceMoving;
public:
	CoinPickUp(void);
	CoinPickUp(int left, int top);
	~CoinPickUp(void);

	void Update();
};