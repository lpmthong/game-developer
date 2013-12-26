#pragma once
#include "DynamicObject.h"

class PirhanaPlant : public DynamicObject{

public:
	int appear; // cai bien nay dung de ve no len giong nhu cai bonus

private:
	DWORD startDisappear;
	DWORD timeDisappear;
	DWORD updateRate;

	bool direct; // cai nay de biet khi nao nho len khi nao thut xuong

public:

	PirhanaPlant(void);
	PirhanaPlant(int left, int top, int iid);
	~PirhanaPlant(void);

	void Update();
	void UpdateSprite();
	void Render();

	bool CheckPlayerStand();
};