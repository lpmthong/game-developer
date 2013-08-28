#pragma once
#include "staticobject.h"

class EndMap :
	public StaticObject
{
	int movingDirect;
	int movingDistance;

	bool setScore;
	//Player get the cross or not.
	bool touchCross;
public:
	EndMap(void);
	EndMap(int left, int top);
	~EndMap(void);
	 
	void Update();
	void Render();
};
