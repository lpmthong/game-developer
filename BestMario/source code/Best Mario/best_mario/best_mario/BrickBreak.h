#pragma once
#include "DynamicObject.h"

class BrickBreak : public DynamicObject{

public:

	BrickBreak(void);
	BrickBreak(int left, int top);
	~BrickBreak(void);

	void Update();
	void UpdateSprite();
	void setType(int type);

};