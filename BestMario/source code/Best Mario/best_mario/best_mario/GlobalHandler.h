#pragma once

#include "DirectX.h"
#include "QuadTree.h"
#include "trace.h"

class GlobalHandler{

public:
	static DirectX				*_directX;

	static int					backGroundColor;
	static bool					quitGame;		
	static RECT					screen;

	static QuadTree				*quadTree;
	static	int					mapLevel;

	GlobalHandler(void);
	~GlobalHandler(void);

	static bool CheckPointInRect(int x, int y, RECT rect);
	static bool CheckRectInRect(RECT mainRect, RECT checkRect);

	static void RestartMap(); 

};