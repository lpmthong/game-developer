#pragma once
#include "StaticObject.h"

class Ground : public StaticObject{

public:
	Ground(void);
	Ground(int left, int top, int iid);
	~Ground(void);
	
	void setType(int type);
	void Update();
};