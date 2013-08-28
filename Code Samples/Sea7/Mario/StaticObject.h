#pragma once
#include "Object.h"

class StaticObject : public Object
{
public:
	//hold the depth of this object.
	int map_level;
public:
	StaticObject(void);
	~StaticObject(void);

	
	// Init the rect use for drawing this object
	virtual void setRecDraw(int left, int top, int width, int height);
};
