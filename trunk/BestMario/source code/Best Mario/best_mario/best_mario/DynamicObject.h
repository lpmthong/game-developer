#pragma once
#include "Object.h"
#include "Define.h"

class DynamicObject : public Object{

public:
	int id;

	float Vx;
	float Vy;

	float Vx_old;
	float Vy_old;

	float acceleration;

	int oldLeft;
	int lodTop;
	
	float fSpeed; //toc do di chuyen cua object

	DWORD lastAnimate;
	int alive; //0: alive; 1: dying; 2:in hell.
	int iAnimatedRate;
	
public:
	DynamicObject(void);
	~DynamicObject(void);

	virtual void ProcessDying();
};