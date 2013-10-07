#pragma once
#include "Object.h"

class DynamicObject : public Object{

public:
	float Vx;
	float Vy;

	float Vx_old;
	float Vy_old;

	//int a;

	int oldLeft;
	int lodTop;
	
	float fSpeed;

	DWORD lastAnimate;
	int alive; //0: alive; 1: dying; 2:in hell.
	int iAnimatedRate;
public:
	DynamicObject(void);
	~DynamicObject(void);

	void ProcessDying();
};