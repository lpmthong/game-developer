#include "Menu.h"
#include "GlobalHandler.h"
#include <dinput.h>
#include "ListTexture.h"
#include "Define.h"
#include "ListSound.h"

Menu::Menu(void)
{
	backGround = new Sprite(ListTexture::TT_MENU_BACKGROUND, SCREEN_WIDTH, SCREEN_HEIGHT, 1, 1);
	options = new Sprite(ListTexture::TT_MENU_OPTIONS, 0, 0, 0, 0);

	choice = MENU_START;
}

Menu::~Menu(void)
{
	delete backGround;
	delete options;
}

void Menu::Render()
{
	backGround->Render(GlobalHandler::directX->backbuffer, 0, 0);

	switch (choice)
	{
	case MENU_START:
		options->Render(GlobalHandler::directX->backbuffer, 580, 300, 0, 0, 143, 40);
		options->Render(GlobalHandler::directX->backbuffer, 615, 309, 0, 40, 143, 73);
		break;
	case MENU_OPTIONS:
		options->Render(GlobalHandler::directX->backbuffer, 560, 335, 0, 0, 143, 40);
		options->Render(GlobalHandler::directX->backbuffer, 605, 335, 0, 73, 143, 110);
			break;
	case MENU_QUIT:
		options->Render(GlobalHandler::directX->backbuffer, 580, 361, 0, 0, 143, 40);
		options->Render(GlobalHandler::directX->backbuffer, 615, 370, 0, 110, 143, 146);
			break;
	}
}

void Menu::OnKeyDown( int keyCode )
{
	switch (keyCode)
	{
	case DIK_UP:
		choice --;

		if (choice < MENU_START)
			choice = MENU_QUIT;
		break;
	case DIK_DOWN:
		choice ++;

		if (choice > MENU_QUIT)
			choice = MENU_START;
		break;
	case DIK_RETURN:
		if (choice == MENU_START)
		{
			//GlobalHandler::gameState = GS_CHANGEMAP;
			GlobalHandler::gameState = GS_STARTGAMEOPTIONS;
		}
		if (choice == MENU_QUIT)
		{
			GlobalHandler::quitGame = true;
		}
		if (choice == MENU_OPTIONS)
		{
			GlobalHandler::gameState = GS_OPTION;
		}
		break;
	}
}