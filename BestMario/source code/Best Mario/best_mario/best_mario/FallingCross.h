#pragma once
#include "StaticObject.h"

class FallingCross : public StaticObject{

public:
	bool touch;

	FallingCross(void);
	FallingCross(int left, int top, int iid);
	~FallingCross(void);

	void ProcessCollision(int iKind);
	void Update();

	void Render();
};