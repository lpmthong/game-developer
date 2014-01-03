#pragma once
#include "Sprite.h"



class Menu
{
	public:
		Menu(void);
		~Menu(void);

		Sprite* menuBackground;
		Sprite* menuOption;
		Sprite* menuText;

		int choice;
		void Render();
		void OnKeyDown(int keyCode);

};