#pragma once
#include "Sprite.h"

#define MENU_CONTINUE 0
#define MENU_NEWGAME 1
#define MENU_SAVEGAME 2
#define MENU_LOADGAME 3
#define MENU_BACK 4

class StartGameOptions
{
	Sprite* backGround;
	Sprite* options;

	int choice;

	bool startRun;
	DWORD lastUpdate;

	int leftOption;
	int topOption;
public:
	StartGameOptions(void);
	~StartGameOptions(void);

	void Render();
	void Update();
	void OnKeyDown(int keyCode);
};
