#pragma once
#include "DynamicObject.h"

class Score:public DynamicObject
{
public:
	Score(void);
	Score(int left, int top);
	~Score(void);

	int arrScore[6];
	int arrScoreIndex;
	int distanceMoving;

	void setScore(int score);
	void Render();
	void Update();

	bool moving;
	void RenderCross(int left, int top);
};

