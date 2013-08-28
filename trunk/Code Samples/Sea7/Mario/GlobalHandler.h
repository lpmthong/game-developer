#pragma once

#include "DirectX.h"
#include "QuadTree.h"
#include "DynamicObjManager.h"
#include "Player.h"
#include "Text.h"
#include "DXSound.h"
#include "SaveGame.h"

class GlobalHandler
{
public:
	static	DirectX				*directX;
	static	QuadTree			*quadTree;
	static	DynamicObjManager	*dynamicObjManager;
	static	DXSound				*sound;
	static	int					gameState;

	static	Player				*player;

	static	int					levelTime;
	static	DWORD				lastUpdateTime;

	//Level 1 - 1: we have to number here. So mapLevel1 and mapLevel2 present for that.
	static	int					mapLevel1;
	static	int					mapLevel2;
	static	int					backGroundColor;
	static	int					mapLevel;	//map level in real.

	static	bool				endMap;

	static	RECT				screen;

	static	Text				*txt;

	static	int					checkpoint[2][10];
	static	int					checkpoint_index;

	static	bool				quitGame;
	static	bool				isStarted;

	static	int					playerScore;
	static	int					playerCoin;

	static SaveGame				*saveGame;
public:
	GlobalHandler(void);
	~GlobalHandler(void);

public:
	static bool CheckPointInRect(int x, int y, RECT rect);
	static bool CheckRectInRect(RECT mainRect, RECT checkRect);

	static bool UpdateTime();
	static void UpdateScreen();

	static void InitText();

	static void RestartMap();
};
