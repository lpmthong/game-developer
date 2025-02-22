#pragma once
#include "brick.h"

class BonusBrick :	public Brick
{	
	int bonusType;
	bool willRender;
public:
	bool isEmpty;

	BonusBrick(void);
	BonusBrick(int left, int top, bool iEmpty, int iid);
	~BonusBrick(void);

	void ProcessCollision(int iKind);

	int getType();
	void setType(int type);

	void BonusAppear();
	void SetEmpty();

	void Render();
	void setHidden();
};
