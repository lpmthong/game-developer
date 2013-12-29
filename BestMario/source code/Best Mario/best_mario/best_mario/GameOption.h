#pragma once
#include "Sprite.h"



class GameOption
{
public:
	GameOption(void);
	~GameOption(void);

	Sprite *gameOption_Background;
	Sprite *gameOption_Option;
	int		choice;

	bool	isStarted;

	void Render();
	void Update();
	void OnKeyDown(int keyCode);

	
};

