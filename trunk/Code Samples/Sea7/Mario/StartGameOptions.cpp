#include "StartGameOptions.h"
#include "ListTexture.h"
#include "Sprite.h"
#include "GlobalHandler.h"
#include "Define.h"

StartGameOptions::StartGameOptions(void)
{
	backGround = new Sprite(ListTexture::TT_STARTGAMEOPTION_BACKGROUND, SCREEN_WIDTH, SCREEN_HEIGHT, 1, 1);
	options = new Sprite(ListTexture::TT_TURLE_DEATH, ListTexture::TT_TURLE_DEATH_WIDTH, ListTexture::TT_TURLE_DEATH_HEIGHT, ListTexture::TT_TURLE_DEATH_COUNT, ListTexture::TT_TURLE_DEATH_SPRITEPERROW);

	choice = MENU_CONTINUE;
	startRun = false;

	leftOption = 0;
	topOption = 0;
}

StartGameOptions::~StartGameOptions(void)
{
	delete backGround;
	delete options;
}

void StartGameOptions::Render()
{
	backGround->Render(GlobalHandler::directX->backbuffer, 0, 0);

	switch (choice)
	{
	case MENU_CONTINUE:
		options->Render(GlobalHandler::directX->backbuffer, 14, 24);
		break;
	case MENU_NEWGAME:
		options->Render(GlobalHandler::directX->backbuffer, 124, 75);
		break;
	case MENU_SAVEGAME:
		options->Render(GlobalHandler::directX->backbuffer, 14, 138);
		break;
	case MENU_LOADGAME:
		options->Render(GlobalHandler::directX->backbuffer, 127, 200);
		break;
	case MENU_BACK:
		options->Render(GlobalHandler::directX->backbuffer, 14, 535);
		break;
	}
}

void StartGameOptions::OnKeyDown( int keyCode )
{
	startRun = true;

	switch (keyCode)
	{
	case DIK_UP:
		choice --;

		if (choice < MENU_CONTINUE)
			choice = MENU_BACK;
		break;
	case DIK_DOWN:
		choice ++;

		if (choice > MENU_BACK)
			choice = MENU_CONTINUE;
		break;
	case DIK_RETURN:
		if (choice == MENU_BACK)
		{
			GlobalHandler::gameState = GS_MENU;
		}
		if (choice == MENU_NEWGAME)
		{
			GlobalHandler::mapLevel = 1;
			GlobalHandler::RestartMap();
			//GlobalHandler::RestartMap();
			GlobalHandler::gameState = GS_CHANGEMAP;
		}
		if (choice == MENU_CONTINUE)
		{
			if (GlobalHandler::isStarted)
				GlobalHandler::gameState = GS_GAMEPLAY;
		}
		if (choice == MENU_SAVEGAME)
		{
			GlobalHandler::saveGame->Save();
		}
		if (choice == MENU_LOADGAME)
		{
			GlobalHandler::mapLevel = 0;
			GlobalHandler::RestartMap();
			GlobalHandler::gameState = GS_CHANGEMAP;
		}
		break;
	}
}

void StartGameOptions::Update()
{
	DWORD now = GetTickCount();
	if (now - lastUpdate > 70)
	{
		options->Next(0,2);
		lastUpdate = now;
	}
}
