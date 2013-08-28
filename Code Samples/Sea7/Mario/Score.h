#pragma once
#include "dynamicobject.h"

class Score :
	public DynamicObject
{
	int arrScore[5];
	int arrScoreIndex;

	int distanceMoving;
public:
	bool moving;
public:
	Score(void);
	Score(int left, int top);
	~Score(void);

	void setScore(int score);
	void Render();
	void Update();

	//Render a cross use for rendering map level.
	void RenderCross(int left, int top);
};
