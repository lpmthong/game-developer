#pragma once
#include "StaticObject.h"

class GroundMushRoom : public StaticObject{

public:
	GroundMushRoom(void);
	GroundMushRoom(int left, int top, int iid);
	~GroundMushRoom(void);

	void setType(int type);
	void Update();
};