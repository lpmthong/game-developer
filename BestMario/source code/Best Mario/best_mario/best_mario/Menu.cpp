#include "Menu.h"
#include "Define.h"
#include "ListTexture.h"
#include "GlobalHandler.h"

Menu::Menu(void)
{
	menuBackground	= new Sprite(ListTexture::TT_MENU_BACKGROUND , SCREEN_WIDTH , SCREEN_HEIGHT, 1 , 1);
	menuOption		= new Sprite(ListTexture::TT_MENU_OPTION,0,0,0,0);
	choice			= MENU_START;
}

Menu::~Menu(void)
{
	delete menuBackground;
	delete menuOption;
}

void Menu::Render()
{
	menuBackground->Render(GlobalHandler::_directX->_backBuffer,0,0);

	switch(choice)
	{
		case MENU_START:
			menuOption->Render(GlobalHandler::_directX->_backBuffer,580,300,0,0,143,40);
			menuOption->Render(GlobalHandler::_directX->_backBuffer,615,309,0,40,143,73);
			break;
		case MENU_OPTION:
			menuOption->Render(GlobalHandler::_directX->_backBuffer,560,335,0,0,143,40);
			menuOption->Render(GlobalHandler::_directX->_backBuffer,605,335,0,73,143,110);
			break;
		case MENU_EXIT:
			menuOption->Render(GlobalHandler::_directX->_backBuffer,580,361,0,0,143,40);
			menuOption->Render(GlobalHandler::_directX->_backBuffer,615,370,0,110,143,146);
			break;
	}

}
void Menu::OnKeyDown(int keyCode)
{
	switch(keyCode)
	{
		case  DIK_UP:
			choice--;
			if(choice < MENU_START)
				choice=MENU_EXIT;
			break;
		case  DIK_DOWN:
			choice++;
			if(choice > MENU_EXIT)
				choice = MENU_START;
			break;
		case DIK_RETURN:
			if(choice == MENU_START)
			{				
				GlobalHandler::gameState = GS_GAMEOPTION;
				break;
			}
			if(choice == MENU_OPTION)
			{
				GlobalHandler::gameState = GS_OPTION;
				break;
			}
			if(choice == MENU_EXIT)
			{
				GlobalHandler::quitGame = true;
			}
			
	}
}