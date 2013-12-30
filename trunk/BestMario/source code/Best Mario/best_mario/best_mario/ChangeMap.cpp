#include "ChangeMap.h"
#include "ListTexture.h"
#include "GlobalHandler.h"


ChangeMap::ChangeMap(void)
{
	changMap = new Sprite();

	mapLevel = new Score(0,0);
	

}


ChangeMap::~ChangeMap(void)
{
}

void ChangeMap::Render()
{
	changMap->Reset(ListTexture::TT_TEXT_WORLD,ListTexture::TT_TEXT_WORLD_WIDTH,ListTexture::TT_TEXT_WORLD_HEIGHT,1,1);
	changMap->Render(GlobalHandler::_directX->_backBuffer,SCREEN_WIDTH/2-ListTexture::TT_TEXT_WORLD_WIDTH/2,SCREEN_HEIGHT/2-ListTexture::TT_TEXT_WORLD_HEIGHT/2);
	
	mapLevel->setScore(GlobalHandler::mapLevel1);
	mapLevel->UpdateRect(GlobalHandler::screen.left + 355, 285);
	mapLevel->Render();

	mapLevel->RenderCross(GlobalHandler::screen.left +393, 285);

	mapLevel->setScore(GlobalHandler::mapLevel2);
	mapLevel->UpdateRect(GlobalHandler::screen.left + 398 , 285);
	mapLevel->Render();

}

void ChangeMap::OnKeyDown(int keyCode)
{
	if( keyCode == DIK_RETURN)
	{
		GlobalHandler::RestartMap();
		GlobalHandler::gameState = GS_GAMEPLAY;
	}
}