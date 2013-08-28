#pragma once
#include "staticobject.h"

class Pipe :
	public StaticObject
{
public:
	Pipe(void);
	Pipe(int left, int top, int type);
	~Pipe(void);
};
