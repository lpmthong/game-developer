#include "ChangeMap.h"
#include "ListTexture.h"
#include "GlobalHandler.h"
#include "Define.h"

ChangeMap::ChangeMap(void)
{
	changMap = new Sprite(ListTexture::TT_GAME_CHANGEMAP, SCREEN_WIDTH, SCREEN_HEIGHT, 1 , 1);
	//mapLevel = new Score(0,0);
	

}


ChangeMap::~ChangeMap(void)
{
}

void ChangeMap::Render()
{
	changMap->Render(GlobalHandler::_directX->_backBuffer, 0 , 0);
	
}

void ChangeMap::OnKeyDown(int keyCode)
{
	if( keyCode == DIK_RETURN)
	{
		GlobalHandler::RestartMap();
		GlobalHandler::gameState = GS_GAMEPLAY;
	}
}