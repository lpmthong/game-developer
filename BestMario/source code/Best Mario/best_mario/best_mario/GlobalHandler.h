#pragma once

#include "DirectX.h"
#include "QuadTree.h"

class GlobalHandler{

public:
	static DirectX			*_directX;

	static int				backGroundColor;
	static bool				quitGame;		
	static RECT				screen;

	static QuadTree			*quadTree;

	GlobalHandler(void);
	~GlobalHandler(void);

};