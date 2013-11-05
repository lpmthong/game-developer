#pragma once
#include "StaticObject.h"

class Pipe : public StaticObject
{
public:
	Pipe(void);
	Pipe(int left, int top, int type, int iid);
	~Pipe(void);
};
