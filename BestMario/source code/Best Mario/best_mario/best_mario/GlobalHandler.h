#pragma once

#include "DirectX.h"

class GlobalHandler{

public:
	static DirectX *_directX;

	static int backGroundColor;
	static bool quitGame;

	static RECT screen;

	GlobalHandler(void);
	~GlobalHandler(void);

};