#pragma once
#include "hardbrick.h"

class FallingCross :
	public HardBrick
{
	bool collidePlayer;
	bool fallDown;

	//start fall down.
	DWORD startFallDown;

	//time the cross is still in air.
	DWORD timeHoldOn;
public:
	FallingCross(void);
	FallingCross(int left, int top);
	~FallingCross(void);

	void ProcessCollision(int iKind);
	void Update();
};
