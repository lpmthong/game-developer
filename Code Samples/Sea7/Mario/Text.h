#pragma once
#include "staticobject.h"
#include "DynamicObject.h"
#include "Score.h"

class Text :
	public DynamicObject
{
	Score* life;
	Score* time;
	Score* score;
	Score* coinCount;
	Score* mapLV;
	
	Score* debugPlayerLeft;
public:
	bool gameOver;
public:
	Text(void);
	~Text(void);

	void Render();
	void Update();

	void RenderMario();
	void RenderGameOver();
	void RenderTime();
	void RenderWorld();
	void RenderCoinCount();
	void RenderScore();

	void debugPlayer();
};
