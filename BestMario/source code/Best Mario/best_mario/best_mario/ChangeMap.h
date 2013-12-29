#pragma once
#include "Sprite.h"
#include "Score.h"

class ChangeMap
{
public:
	ChangeMap(void);
	~ChangeMap(void);

	Sprite* changMap;
	Score*	mapLevel;

	void Render();
	void OnKeyDown(int keyCode);

};

