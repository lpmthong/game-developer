#include "GameOption.h"
#include "ListTexture.h"
#include "GlobalHandler.h"
#include "Define.h"

GameOption::GameOption(void)
{
	gameOption_Background	= new Sprite(ListTexture::TT_GAMEOPTION,SCREEN_WIDTH,SCREEN_HEIGHT,1,1);
	gameOption_Option		= new Sprite(ListTexture::TT_MARIO_KID,ListTexture::TT_MARIO_KID_WIDTH,ListTexture::TT_MARIO_KID_HEIGHT,1,1);

	choice					= OPTION_NEWGAME;
	isStarted				= false;

}


GameOption::~GameOption(void)
{
}


void GameOption::Render()
{
	gameOption_Background->Render(GlobalHandler::_directX->_backBuffer,0,0);
	switch(choice)
	{
		case OPTION_NEWGAME:
			gameOption_Option->Render(GlobalHandler::_directX->_backBuffer,124,75);
			break;
		case OPTION_SAVEGAME:
			gameOption_Option->Render(GlobalHandler::_directX->_backBuffer,14,138);
			break;
		case OPTION_LOADGAME:
			gameOption_Option->Render(GlobalHandler::_directX->_backBuffer,127,200);
			break;
		case OPTION_BACKMENU:
			gameOption_Option->Render(GlobalHandler::_directX->_backBuffer,14,535);
			break;
	}
}
void GameOption::OnKeyDown(int keyCode)
{
	switch(keyCode)
	{
		case DIK_UP:
			choice--;
			if(choice<OPTION_NEWGAME)
				choice=OPTION_BACKMENU;
			break;
		case DIK_DOWN:
			choice++;
			if(choice>OPTION_BACKMENU)
				choice = OPTION_NEWGAME;
			break;
		case DIK_ESCAPE:
			
				if(GlobalHandler::isStarted)
					GlobalHandler::gameState = GS_GAMEPLAY;
			break;
		case DIK_RETURN:
			if(choice == OPTION_NEWGAME)
			{
				GlobalHandler::mapLevel = 1;
				GlobalHandler::RestartMap();
				GlobalHandler::gameState = GS_CHANGEMAP;
				trace(L"New Game");
			}
			if(choice == OPTION_SAVEGAME)
			{
				GlobalHandler::save->Save();
			}
			if(choice == OPTION_LOADGAME)
			{
				GlobalHandler::mapLevel = 0;
				GlobalHandler::RestartMap();
				GlobalHandler::gameState = GS_CHANGEMAP;
			}
			if(choice == OPTION_BACKMENU)
			{
				GlobalHandler::gameState = GS_MENU;
				GlobalHandler::isStarted = false;
			}
			break;
	}
}