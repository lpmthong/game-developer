#pragma once
#include "StaticObject.h"

class Grass : public StaticObject{

public:
	Grass(void);
	Grass(int left, int top, int iid);
	~Grass(void);

};