#pragma once
#include "Object.h"

class StaticObject : public Object{

public:
	int map_level;
	int id;
public:
	StaticObject(void);
	~StaticObject(void);

};