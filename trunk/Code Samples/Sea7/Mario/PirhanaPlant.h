#pragma once
#include "dynamicobject.h"

class PirhanaPlant :
	public DynamicObject
{
public:
	//How many pixel of this object appear in map.
	int appear;

private:
	bool direct;
	DWORD startDisappear;
	DWORD timeDisappear;

	DWORD updateRate;
public:
	PirhanaPlant(void);
	PirhanaPlant(int left, int top);
	~PirhanaPlant(void);

	void Update();
	void Render();
	void UpdateSprite();

	bool CheckNearPlayer();
};
