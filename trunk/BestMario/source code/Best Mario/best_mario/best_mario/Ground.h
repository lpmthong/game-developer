#pragma once
#include "StaticObject.h"

class Ground : public StaticObject{

public:
	int type;

	Ground(void);
	Ground(int left, int top, int iid);
	~Ground(void);
	
	void setType(int t);
	void Update();
};