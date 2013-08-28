#include "PirhanaPlant.h"
#include "Define.h"
#include "ListTexture.h"
#include "trace.h"

PirhanaPlant::PirhanaPlant(void)
{
}

PirhanaPlant::PirhanaPlant( int left, int top ) : DynamicObject()
{
	sprite = new Sprite(ListTexture::TT_PIRHANA_PLANT,
						ListTexture::TT_PIRHANA_PLANT_WIDTH,		
						ListTexture::TT_PIRHANA_PLANT_HEIGHT,		
						ListTexture::TT_PIRHANA_PLANT_COUNT,		
						ListTexture::TT_PIRHANA_PLANT_SPRITEPERROW);

	width = ListTexture::TT_PIRHANA_PLANT_WIDTH;
	height = ListTexture::TT_PIRHANA_PLANT_HEIGHT;

	UpdateRect(left, top + ListTexture::TT_PIRHANA_PLANT_HEIGHT, ListTexture::TT_PIRHANA_PLANT_WIDTH, ListTexture::TT_PIRHANA_PLANT_HEIGHT);
	animatedRate = ListTexture::TT_PIRHANA_PLANT_ANIMATED_RATE;
	//	map_level = 2;

	lastUpdate = GetTickCount();
	updateRate = 50;
	lastAnimate = GetTickCount();
	timeDisappear = 2000;

	iKind = PIRHANAPLANT;
	isSolid = true;

	alive = ALIVE;
	appear = 0;
	direct = true;
}

PirhanaPlant::~PirhanaPlant(void)
{
}

void PirhanaPlant::Update()
{
	DWORD now = GetTickCount();
	if (now - lastUpdate > updateRate)
	{
		lastUpdate = now;
		if (direct == true)
		{
			if (now - startDisappear > timeDisappear)
			{
				appear++;
				UpdateRect(recDrawArea.left, recDrawArea.top - 1);
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
				if (CheckNearPlayer() == false)
				{
					direct = true;
					startDisappear = GetTickCount();
				}
			}
			else
			{
				UpdateRect(recDrawArea.left, recDrawArea.top + 1);
			}
		}
	}
//	trace(L"%d", appear);
	UpdateSprite();
}

void PirhanaPlant::Render()
{
	RECT screen = GlobalHandler::screen;

	sprite->Render(GlobalHandler::directX->backbuffer, recDrawArea.left - screen.left, recDrawArea.top - screen.top, appear);
}

void PirhanaPlant::UpdateSprite()
{
	DWORD now = GetTickCount();
	if (now - lastAnimate > animatedRate)
	{
		lastAnimate = now;
		sprite->Next();
	}
}

bool PirhanaPlant::CheckNearPlayer()
{
	if (GlobalHandler::player->recRealArea.left > recRealArea.left - GlobalHandler::player->width * 2 &&
		GlobalHandler::player->recRealArea.left < recRealArea.right + GlobalHandler::player->width * 2)
		return true;

	return false;
}
