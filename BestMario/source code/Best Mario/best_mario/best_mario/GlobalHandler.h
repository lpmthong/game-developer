#pragma once
#include "list"
#include "DirectX.h"
#include "QuadTree.h"
#include "trace.h"
#include "Player.h"
#include "DynamicObjManager.h"
#include "StaticObject.h"
#include <stdint.h>
#include "Collision.h"
#include "DXSound.h"
#include "Text.h"

using namespace std;

class GlobalHandler{

public:
	static QuadTree				*quadTree;
	static DirectX				*_directX;
	static DXSound				*sound;

	static int					backGroundColor;
	static bool					quitGame;		
	static RECT					screen;
	static int					gameState;

	static DynamicObjManager	*dynamicObjManager;
	static int					mapLevel;
	static Player				*player;
	
	static list<StaticObject*>  listStaticObj;
	static list<StaticObject*>	listStaticObjRender; // cai list nay lay ra de for xet va cham
	static Collision			*Physic;

	//Check point
	static int					checkpoint[2][10];
	static int					checkpoint_index;

	static int					playerScore;
	static int					playerCoin;

	//text
	static Text					*text;
	static int					 time;
	static DWORD				lastUpdateTime;

	GlobalHandler(void);
	~GlobalHandler(void);

	static bool CheckPointInRect(int x, int y, RECT rect);
	static bool CheckRectInRect(RECT mainRect, RECT checkRect);
	
	static void UpdateScreen();
	static bool UpdateTime();
	static void RestartMap();	
	static void InitText();
	
	static LPWSTR ConvertChar(char c[]);
	
};