#pragma once
#include "StaticObject.h"

class EndMap : public StaticObject{

public:
	int movingDirect;
	int movingDistance;

	bool setScore;
	//Player get the cross or not.
	bool touchCross;
public:
	EndMap(void);
	EndMap(int left, int top, int iid);
	~EndMap(void);

	void Render();
	void Update();
};