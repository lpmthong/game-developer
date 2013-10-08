#pragma once
#include "DirectX.h"
#include "QuadTree.h"
#include "trace.h"
#include "Player.h"
#include "DynamicObjManager.h"

class GlobalHandler{

public:
	static DirectX				*_directX;

	static int					backGroundColor;
	static bool					quitGame;		
	static RECT					screen;
	static int					gameState;

	static QuadTree				*quadTree;
	static DynamicObjManager	*dynamicObjManager;
	static int					mapLevel;
	static Player				*player;

	//Check point
	static int					checkpoint[2][10];
	static int					checkpoint_index;

	GlobalHandler(void);
	~GlobalHandler(void);

	static bool CheckPointInRect(int x, int y, RECT rect);
	static bool CheckRectInRect(RECT mainRect, RECT checkRect);
	
	static void UpdateScreen();
	static void RestartMap(); 
	
};