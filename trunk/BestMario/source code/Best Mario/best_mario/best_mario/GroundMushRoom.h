#pragma once
#include "StaticObject.h"

class GroundMushRoom : public StaticObject{

public:
	int type;

	GroundMushRoom(void);
	GroundMushRoom(int left, int top, int iid);
	~GroundMushRoom(void);

	void setType(int t);
	void Update();
};