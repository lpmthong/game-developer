#pragma once
#include "Sprite.h"

class ChangeMap
{
	Sprite* sprite;
public:
	ChangeMap(void);
	~ChangeMap(void);

	void Render();
	void OnKeyDown(int keyCode);
};
