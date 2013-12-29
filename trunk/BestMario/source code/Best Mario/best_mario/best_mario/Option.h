#pragma once
#include "Sprite.h"
class Option
{
public:
	Option(void);
	~Option(void);
	Sprite* option;
	void Render();
	void OnKeyDown(int keyCode);
};

