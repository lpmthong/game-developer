#include "EndMap.h"
#include "GlobalHandler.h"
#include "ListTexture.h"

EndMap::EndMap(void){}

EndMap::~EndMap(void){}

EndMap::EndMap(int left, int top, int iid){

	sprite = new Sprite(ListTexture::TT_END_MAP, ListTexture::TT_END_MAP_WIDTH, ListTexture::TT_END_MAP_HEIGHT,
						ListTexture::TT_END_MAP_COUNT, ListTexture::TT_END_MAP_SPRITEPERROW);

	id = iid;
	isKind = ENDMAP;
	width = ListTexture::TT_END_MAP_WIDTH;
	height = ListTexture::TT_END_MAP_HEIGHT;
	UpdateRect(left, top + ListTexture::TT_END_MAP_HEIGHT - 32, ListTexture::TT_END_MAP_WIDTH, ListTexture::TT_END_MAP_HEIGHT);

	map_level = 2;
	isSolid = true;

	movingDistance = rectDraw.top - 13;
	movingDirect = -2;

	setScore = false;
	touchCross = false;
}

void EndMap::Render(){
	trace(L"CO vo day ne------------------");
	RECT screen = GlobalHandler::screen;
	sprite->setIndex(0);
	sprite->Render(GlobalHandler::_directX->_backBuffer, rectDraw.left, rectDraw.top, screen.left, screen.bottom);

	sprite->setIndex(1);
	sprite->Render(GlobalHandler::_directX->_backBuffer, rectDraw.left + 120, rectDraw.top, screen.left, screen.bottom);

	sprite->setIndex(2);
	sprite->Render(GlobalHandler::_directX->_backBuffer, rectDraw.left + 185, rectDraw.top, screen.left, screen.bottom);

	if (!touchCross)
		sprite->Render(GlobalHandler::_directX->_backBuffer, rectDraw.left + 141, movingDistance,screen.left, screen.bottom, 93, 272, 137, 288);
}

void EndMap::Update(){

	movingDistance += movingDirect;
	if (movingDistance >= rectDraw.top - 13)
		movingDirect = -2;
	if (movingDistance <= rectDraw.bottom + 16)
		movingDirect = 2;

	RECT cross;
	cross.left = rectDraw.left + 141;
	cross.top = movingDistance;
	cross.right = cross.left + 44;
	cross.bottom = cross.top - 16;

	if (GlobalHandler::player->rectDraw.right > cross.left && !setScore)
	{
		Score* score = new Score(GlobalHandler::player->rectDraw.left, GlobalHandler::player->rectDraw.top);
		setScore = true;
		if (GlobalHandler::CheckRectInRectReal(cross, GlobalHandler::player->rectDraw))
		{
			touchCross = true;
			score->setScore(1000 - 600 - movingDistance);
		}
		else
			score->setScore(100);
		GlobalHandler::dynamicObjManager->Add(score);

		GlobalHandler::endMap = true;
	}

}