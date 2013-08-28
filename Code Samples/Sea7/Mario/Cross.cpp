#include "Cross.h"
#include "ListTexture.h"
#include "Define.h"

Cross::Cross(void)
{
}

Cross::Cross( int left, int top )
{
	sprite = new Sprite(ListTexture::TT_CROSS,
		ListTexture::TT_CROSS_WIDTH, 
		ListTexture::TT_CROSS_HEIGHT, 
		1, 
		1);

	width = ListTexture::TT_CROSS_WIDTH;
	height = ListTexture::TT_CROSS_HEIGHT + 10;

	UpdateRect(left, top, ListTexture::TT_CROSS_WIDTH, ListTexture::TT_CROSS_HEIGHT + 10);

	iKind = CROSS;
	isSolid = true;

	isHardBrick = true;

	//Just init it, dont let it start to do anything.
	start = false;

	lastUpdate = GetTickCount();
	updateRate = 2;

	addCross = false;
}

Cross::~Cross(void)
{
}

void Cross::Update()
{
	DWORD now = GetTickCount();
	if (now - lastUpdate > updateRate)
	{
		UpdateRect(recDrawArea.left, recDrawArea.top - 3);

		if (recDrawArea.top < 400 && addCross == false)
		{
			Cross* cross = new Cross(recDrawArea.left, 570);
			GlobalHandler::dynamicObjManager->Add(cross);
			addCross = true;
		}
		if (recDrawArea.top < 0)
			alive = INHELL;
		lastUpdate = now;
	}
}