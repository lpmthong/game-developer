#pragma once
#include "Sprite.h"

class Option
{
	Sprite* sprite;
public:
	Option(void);
	~Option(void);

	void Render();
	void OnKeyDown(int keyCode);
};
