#pragma once
#include "Object.h"

class DynamicObject : public Object
{
public:
	float fXVelocity;	//X velocity.
	float fYVelocity;	//Y velocity.

	float fXOldVelocity;
	float fYOldVelocity;

	float acceleration;

	int oldLeft;
	int oldTop;

	float fSpeed;	//Moving speed.

	DWORD lastAnimate;


	//0: alive; 1: dying; 2:in hell.
	int alive;

	int iAnimatedRate;	//Time between two times changed sprite.
public:
	DynamicObject(void);
//	virtual void Update() = 0;
	~DynamicObject(void);

	virtual void ProcessDying();
};
