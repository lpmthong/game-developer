#pragma once
#include "Sprite.h"

#define MENU_START 0
#define MENU_OPTIONS 1
#define MENU_QUIT 2

//How many item does this menu has.
#define MENU_COUNT 3

class Menu
{
	Sprite* backGround;
	Sprite* options;

	int choice;
public:
	Menu(void);
	void Render();

	void OnKeyDown(int keyCode);
	~Menu(void);
};
