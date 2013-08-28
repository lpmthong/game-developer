#pragma once
#include "hardbrick.h"

class Cross :
	public HardBrick
{
	DWORD updateRate;
	bool addCross;
public:
	Cross(void);
	Cross(int left, int top);
	~Cross(void);

	void Update();
};
