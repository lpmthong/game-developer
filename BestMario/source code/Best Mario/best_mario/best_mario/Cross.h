#pragma once
#include "DynamicObject.h"

class Cross : public DynamicObject{

public:
	Cross(void);
	Cross(int left, int top, int iid);
	~Cross(void);

	void Update();
	virtual void CheckOutScreen();
};