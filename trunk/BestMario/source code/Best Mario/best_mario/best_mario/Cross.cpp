#include "Cross.h"
#include "GlobalHandler.h"
#include "ListTexture.h"

Cross::Cross(void){}

Cross::~Cross(void){}

Cross::Cross(int left, int top, int iid){

	sprite = new Sprite(ListTexture::TT_CROSS, ListTexture::TT_CROSS_WIDTH, ListTexture::TT_CROSS_HEIGHT, 1, 1);

	id = iid;
	width = ListTexture::TT_CROSS_WIDTH;
	height = ListTexture::TT_CROSS_HEIGHT;

	UpdateRect(left, top , ListTexture::TT_CROSS_WIDTH, ListTexture::TT_CROSS_HEIGHT);

	lastUpdate = GetTickCount();

	isKind = CROSS;
	isSolid = true;

	Vy = 0;
	Vy_old = 0.0f;
	Vx = 0;

	start = false;
}

void Cross::Update(){

	DWORD now = GetTickCount();
	int t = now - lastUpdate;
	lastUpdate = now;

	int y = rectDraw.top;

	Vy = Vy_old + 0.1f;
	y += Vy * t;

	//Vy_old = Vy;

	if (y > 550)
	{
		y = 50;
		Vy = 0;
	}

	UpdateRect(rectDraw.left, y);
}