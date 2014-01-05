#include "PirhanaPlant.h"
#include "GlobalHandler.h"
#include "ListTexture.h"

PirhanaPlant::PirhanaPlant(void){}

PirhanaPlant::~PirhanaPlant(void){}

PirhanaPlant::PirhanaPlant(int left, int top, int iid){

	sprite = new Sprite(ListTexture::TT_PIRHANA_PLANT, ListTexture::TT_PIRHANA_PLANT_WIDTH, ListTexture::TT_PIRHANA_PLANT_HEIGHT,
						ListTexture::TT_PIRHANA_PLANT_COUNT, ListTexture::TT_PIRHANA_PLANT_SPRITEPERROW);

	animatedRate = ListTexture::TT_PIRHANA_PLANT_ANIMATED_RATE;
	id = iid;
	width = ListTexture::TT_PIRHANA_PLANT_WIDTH;
	height = ListTexture::TT_PIRHANA_PLANT_HEIGHT;

	UpdateRect(left, top - ListTexture::TT_PIRHANA_PLANT_HEIGHT, ListTexture::TT_PIRHANA_PLANT_WIDTH, ListTexture::TT_PIRHANA_PLANT_HEIGHT);

	lastUpdate = GetTickCount();
	lastAnimate = GetTickCount();

	isKind = PIRHANAPLANT;
	isSolid = true;
	topSave = top;

	direct = true;
	appear = 0;

	updateRate = 50;
	timeDisappear = 2000;
	startDisappear = GetTickCount();

	map_level = 2;
}

void PirhanaPlant::Update(){

	DWORD now = GetTickCount();
	if (now - lastUpdate > updateRate)
	{
		lastUpdate = now;
		if (direct)
		{
			if (now - startDisappear > timeDisappear)
			{
				appear++;
				UpdateRect(rectDraw.left, rectDraw.top + 1);
				if (appear == ListTexture::TT_PIRHANA_PLANT_HEIGHT)
					direct = false;
			}
		}
		else
		{
			appear--;
			if (appear < 0)
			{
				appear = 0;
				if (CheckPlayerStand() == false)
				{
					direct = true;
					startDisappear = GetTickCount();
				}
			}
			else
			{
				UpdateRect(rectDraw.left, rectDraw.top - 1);
			}
		}
	}

	UpdateSprite();
}

void PirhanaPlant::UpdateSprite(){
	DWORD now = GetTickCount();
	if (now - lastAnimate > animatedRate)
	{
		sprite->Next();
		lastAnimate = now;
	}
}

void PirhanaPlant::Render(){

	RECT screen = GlobalHandler::screen;
	sprite->Render(backbuffer, rectDraw.left, rectDraw.top, screen.left , screen.bottom, appear);
}

bool PirhanaPlant::CheckPlayerStand(){

	RECT rect;
	rect.left = rectDraw.left - 20;
	rect.right = rectDraw.right + 20;
	rect.top = rectDraw.top + ListTexture::TT_PIRHANA_PLANT_HEIGHT + 10;
	rect.bottom = rect.top - ListTexture::TT_PIRHANA_PLANT_HEIGHT - 10;
	/*trace(L"Payer X: %d, Y: %d", GlobalHandler::player->rectDraw.left, GlobalHandler::player->rectDraw.top);
	trace(L"Rect L: %d, T: %d, R: %d, B: %d", rect.left, rect.top, rect.right, rect.bottom);*/
	if (GlobalHandler::CheckRectInRectReal(rect, GlobalHandler::player->rectDraw))
	{
		trace(L"Co vao");
		return true;
	}
	return false;
	
}