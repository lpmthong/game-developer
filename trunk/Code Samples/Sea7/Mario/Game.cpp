#include "Game.h"
#include "ListTerrain.h"
#include "ListTexture.h"
#include "GlobalHandler.h"
#include "ListSound.h"

Game::Game(void)
{
}

Game::Game(HINSTANCE _hInstance, UINT _nCmdShow)
{
	hInstance = _hInstance;
	nCmdShow = _nCmdShow;
	d3ddev = NULL;
//	directX = new DirectX(hInstance);
	frameRate = FRAME_RATE;
}

Game::~Game(void)
{
}

void Game::GameInit()
{
	cleartrace();
	GlobalHandler::directX->Init(hInstance);
	GlobalHandler::sound->Init(GlobalHandler::directX->hWnd);
//	GlobalHandler::player->Init()
//	GlobalHandler::dynamicObjManager->Add(GlobalHandler::player);
	GlobalHandler::screen.left		= 0;
	GlobalHandler::screen.top		= 0;
	GlobalHandler::screen.right		= SCREEN_WIDTH;
	GlobalHandler::screen.bottom	= SCREEN_HEIGHT;

	ListTexture::CreateAllTexture();
	ListSound::CreateAllSound();
//	ListTerrain::InitTerrain(GlobalHandler::mapLevel);

	GlobalHandler::dynamicObjManager->GetTick();

	GlobalHandler::InitText();

	menu = new Menu();
	option = new Option();
	changeMap = new ChangeMap();
	startGameOptions = new StartGameOptions();
}

void Game::GameEnd()
{
	delete menu;
	delete option;
	delete changeMap;
	delete startGameOptions;

	GlobalHandler::quadTree->Release();
	GlobalHandler::dynamicObjManager->Release();
	GlobalHandler::directX->Release();
}

bool Game::GameRun()
{
	Update();

	if (GlobalHandler::quitGame)
		return false;

	GlobalHandler::directX->BeginScene();

	Render();
	
	GlobalHandler::directX->EndScene();
	GlobalHandler::directX->d3ddev->Present(NULL, NULL, NULL, NULL);

	return true;
}

void Game::ProcessKeyboard()
{
	GlobalHandler::directX->ProcessKeyboard();

	// Scan through all data, check if the key is pressed or released
	for( DWORD i = 0; i < GlobalHandler::directX->dwElements; i++ )
	{
		int keyCode = GlobalHandler::directX->keyEvents[i].dwOfs;
		int keyState = GlobalHandler::directX->keyEvents[i].dwData;
		if ( (keyState & 0x80) > 0)
		{
			OnKeyDown(keyCode);
		//	trace(L"key down");
		}
		else 
		{
			OnKeyUp(keyCode);
		//	trace(L"key up");
		}
	}
}

void Game::OnKeyDown(int keyCode)
{
	switch (GlobalHandler::gameState)
	{
	case GS_OPTION:
		option->OnKeyDown(keyCode);
		break;
	case GS_MENU:
		menu->OnKeyDown(keyCode);
		break;
	case GS_CHANGEMAP:
		changeMap->OnKeyDown(keyCode);
		break;
	case GS_STARTGAMEOPTIONS:
		startGameOptions->OnKeyDown(keyCode);
		break;
	case GS_GAMEPLAY:
		GlobalHandler::player->OnKeyDown(keyCode);
		break;
	}
}

void Game::OnKeyUp(int keyCode)
{}

void Game::ProcessInput()
{
	GlobalHandler::player->ProcessInput();
}

void Game::UpdateScreen( int left, int top, int width, int height )
{
	screen.left = left;
	screen.top = top;
	screen.right = left + width;
	screen.bottom = top + height;
}

void Game::Render()
{
	switch (GlobalHandler::gameState)
	{
	case GS_OPTION:
		option->Render();
		break;
	case GS_MENU:
		menu->Render();
		break;
	case GS_CHANGEMAP:
		if (GlobalHandler::mapLevel == 2)
		{
			int a =12;
		}
		changeMap->Render();
		break;
	case GS_STARTGAMEOPTIONS:
		startGameOptions->Render();
		break;
	case GS_GAMEPLAY:
		GlobalHandler::quadTree->RenderScreen();
		GlobalHandler::dynamicObjManager->Render();

		//Manage all top information.
		GlobalHandler::txt->Render();
		break;
	}
}

void Game::Update()
{
	switch (GlobalHandler::gameState)
	{
	case GS_OPTION:
		break;
	case GS_MENU:
		break;
	case GS_STARTGAMEOPTIONS:
		startGameOptions->Update();
		break;
	case GS_GAMEPLAY:
		if (GlobalHandler::mapLevel == 2)
		{
			int a = 12;
		}
		GlobalHandler::quadTree->UpdateScreen();
		GlobalHandler::dynamicObjManager->Update();
		if (GlobalHandler::UpdateTime() == false)
			if (GlobalHandler::endMap == false)
			{
				GlobalHandler::player->life --;

				//This game is over.
				if (GlobalHandler::player->life < 0)
					GlobalHandler::txt->gameOver = true;

				GlobalHandler::RestartMap();

				trace(L"void Game::Update() go end map %d", GlobalHandler::mapLevel);
			}
			//else
			//{
			//	GlobalHandler::mapLevel++;
			//	GlobalHandler::RestartMap();
			//}
		break;
	}
}

void Game::RestartMap()
{
	GlobalHandler::screen.left		= 0;
	GlobalHandler::screen.top		= 0;
	GlobalHandler::screen.right		= SCREEN_WIDTH;
	GlobalHandler::screen.bottom	= SCREEN_HEIGHT;

	GlobalHandler::quadTree->Reset();
	GlobalHandler::dynamicObjManager->Reset();
	GlobalHandler::player = new Player();
	GlobalHandler::levelTime = 300;
	ListTerrain::InitTerrain(GlobalHandler::mapLevel);
	GlobalHandler::dynamicObjManager->GetTick();

	GlobalHandler::endMap = false;
	GlobalHandler::InitText();

}
