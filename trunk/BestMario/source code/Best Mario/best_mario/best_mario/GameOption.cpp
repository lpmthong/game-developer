#include "GameOption.h"
#include "ListTexture.h"
#include "GlobalHandler.h"
#include "Define.h"

GameOption::GameOption(void)
{
	gameOption_Background	= new Sprite(ListTexture::TT_GAMEOPTION, SCREEN_WIDTH, SCREEN_HEIGHT, 1, 1);
	gameOption_Option		= new Sprite(ListTexture::TT_GAMEOPTIONBUTTON, 0, 0, 0, 0);
	choice					= OPTION_CONTINUE;
	isStarted				= false;

}


GameOption::~GameOption(void)
{
}


void GameOption::Render()
{
	gameOption_Background->Render(GlobalHandler::_directX->_backBuffer, 0, 0);
	gameOption_Option->Render(GlobalHandler::_directX->_backBuffer, 575, 107, 0, 0, 120, 80);
	gameOption_Option->Render(GlobalHandler::_directX->_backBuffer, 439, 67, 120, 0, 240, 80);
	gameOption_Option->Render(GlobalHandler::_directX->_backBuffer, 323, 123, 240, 0, 360, 80);
	gameOption_Option->Render(GlobalHandler::_directX->_backBuffer, 257, 208, 360, 0, 480, 80);
	gameOption_Option->Render(GlobalHandler::_directX->_backBuffer, 323, 298, 480, 0, 600, 80);

	switch(choice)
	{
		case OPTION_CONTINUE:
			gameOption_Option->Render(GlobalHandler::_directX->_backBuffer, 575, 107, 0, 80, 120, 160);
			break;
		case OPTION_NEWGAME:
			gameOption_Option->Render(GlobalHandler::_directX->_backBuffer, 439, 67, 120, 80, 240, 160);
			break;
		case OPTION_SAVEGAME:
			gameOption_Option->Render(GlobalHandler::_directX->_backBuffer, 323, 123, 240, 80, 360, 160);
			break;
		case OPTION_LOADGAME:
			gameOption_Option->Render(GlobalHandler::_directX->_backBuffer, 257, 208, 360, 80, 480, 160);
			break;
		case OPTION_BACKMENU:
			gameOption_Option->Render(GlobalHandler::_directX->_backBuffer, 323, 298, 480, 80, 600, 160);
			break;
	}
}
void GameOption::OnKeyDown(int keyCode)
{
	switch(keyCode)
	{
		case DIK_UP:
		case DIK_RIGHT:
			choice--;
			if(choice<OPTION_CONTINUE)
				choice=OPTION_BACKMENU;
			break;
		case DIK_DOWN:
		case DIK_LEFT:
			choice++;
			if(choice>OPTION_BACKMENU)
				choice = OPTION_CONTINUE;
			break;
		case DIK_ESCAPE:
			
				if(GlobalHandler::isStarted)
					GlobalHandler::gameState = GS_GAMEPLAY;
			break;
		case DIK_RETURN:
			if(choice == OPTION_NEWGAME)
			{
				GlobalHandler::mapLevel = 3;
				GlobalHandler::RestartMap();
				GlobalHandler::gameState = GS_CHANGEMAP;
			//	trace(L"New Game");
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
			if(choice==OPTION_CONTINUE)
			{
				if(GlobalHandler::isStarted==true)
					GlobalHandler::gameState = GS_GAMEPLAY;
				else
					choice=OPTION_NEWGAME;
					
			}
			break;
	}
}