#include "EndMap.h"
#include "Define.h"
#include "ListTexture.h"

EndMap::EndMap(void)
{
}

EndMap::EndMap( int left, int top )
{
	sprite = new Sprite(ListTexture::TT_END_MAP, 
						ListTexture::TT_END_MAP_WIDTH, 
						ListTexture::TT_END_MAP_HEIGHT, 
						ListTexture::TT_END_MAP_COUNT, 
						ListTexture::TT_END_MAP_SPRITEPERROW);


	width = ListTexture::TT_END_MAP_WIDTH;
	height = ListTexture::TT_END_MAP_HEIGHT;
	UpdateRect(left, top - ListTexture::TT_END_MAP_HEIGHT + 31, ListTexture::TT_END_MAP_WIDTH, ListTexture::TT_END_MAP_HEIGHT);
	map_level = 2;

	iKind = ENDMAP;
	isSolid = true;

	movingDistance = recDrawArea.top;
	movingDirect = 2;

	touchCross = false;
	setScore = false;
}

EndMap::~EndMap(void)
{
}

void EndMap::Update()
{
	movingDistance += movingDirect;
	if (movingDistance > 484)
		movingDirect = -2;
	if (movingDistance < recDrawArea.top + 13)
		movingDirect = 2;

	RECT cross;
	cross.left = recDrawArea.left + 141;
	cross.top = movingDistance;
	cross.right = cross.left + 44;
	cross.bottom = cross.top + 16;


	if (GlobalHandler::player->recRealArea.right > cross.left && !setScore)
	{
		Score* score = new Score(GlobalHandler::player->recRealArea.left, GlobalHandler::player->recRealArea.top);
		setScore = true;
		if (GlobalHandler::CheckRectInRect(cross, GlobalHandler::player->recRealArea))
		{
			touchCross = true;
			score->setScore(1000 - movingDistance);
		}
		else
			score->setScore(100);
		GlobalHandler::dynamicObjManager->Add(score);

		GlobalHandler::endMap = true;
	}
}

void EndMap::Render()
{
	RECT screen = GlobalHandler::screen;

	sprite->setIndex(0);
	sprite->Render(GlobalHandler::directX->backbuffer, recDrawArea.left - screen.left, recDrawArea.top - screen.top);

	sprite->setIndex(1);
	sprite->Render(GlobalHandler::directX->backbuffer, recDrawArea.left - screen.left + 120, recDrawArea.top - screen.top);

	sprite->setIndex(2);
	sprite->Render(GlobalHandler::directX->backbuffer, recDrawArea.left - screen.left + 185, recDrawArea.top - screen.top);

	if (!touchCross)
		sprite->Render(GlobalHandler::directX->backbuffer, 
						recDrawArea.left - screen.left + 141, movingDistance - screen.top,
						93, 272, 137, 288);
}
