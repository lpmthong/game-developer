#pragma once
#include "staticobject.h"

class Ground :
	public StaticObject
{
public:
	int type;
public:
	Ground(void);
	Ground(int left, int top);
	~Ground(void);

	//Left middle or right ground.
	void setType(int t);

	void Render();
};
