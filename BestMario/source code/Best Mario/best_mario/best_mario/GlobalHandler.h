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
#include "SaveGame.h"
using namespace std;

class GlobalHandler{

public:
	static QuadTree				*quadTree;
	static DirectX				*_directX;
	static DXSound				*sound;
	static SaveGame				*save;

	static int					backGroundColor;
	static bool					quitGame;		
	static RECT					screen;
	static int					gameState;
	static Text					*text;
	static int					time;
	static DWORD				lastTime;
	static int					mapLevel1;
	static int					mapLevel2;
	static int					mapWidth;
	static bool					isStarted;

	static DynamicObjManager	*dynamicObjManager;
	static list<DynamicObject*>	listRemove;

	static int					mapLevel;
	static int					nextMap;
	static Player				*player;
	static bool					endMap;

	static list<StaticObject*>  listStaticObj;
	static list<StaticObject*>	listStaticObjRender; // cai list nay lay ra de for xet va cham	
	static list<StaticObject*>	listStaticObjCanCollide; // cai nay dung de xet va cham cua may thang dynamic
	static Collision			*Physic;

	

	//Check point
	static int					checkpoint[3][10];
	static int					checkpoint_index;

	static int					playerScore;
	static int					playerCoin;

	GlobalHandler(void);
	~GlobalHandler(void);

	static bool CheckPointInRect(int x, int y, RECT rect);
	static bool CheckRectInRect(RECT mainRect, RECT checkRect);

	static bool CheckPointInRectReal(int x, int y, RECT rect);
	static bool CheckRectInRectReal(RECT mainRect, RECT checkRect);
	
	static void InitText();
	static bool UpdateTime();
	static void UpdateScreen();
	static void RestartMap();

	static void SaveStaticObj();
	
};