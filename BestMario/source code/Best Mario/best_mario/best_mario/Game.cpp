#include "Game.h"
#include "GlobalHandler.h"

Game::Game(void){}

Game::Game(HINSTANCE hInstance, UINT _nCmdShow){
	_hInstance = hInstance;
	nCmdShow = _nCmdShow;
	_d3ddv = NULL;

	frameRate = FRAME_RATE;
}

Game::~Game(void){}

void Game::Init(){
	cleartrace();
	GlobalHandler::_directX->Init(_hInstance);
	GlobalHandler::sound->Init(GlobalHandler::_directX->_hWnd);

	GlobalHandler::screen.left		= 0;
	GlobalHandler::screen.top		= 0;
	GlobalHandler::screen.right		= SCREEN_WIDTH;
	GlobalHandler::screen.bottom	= SCREEN_HEIGHT;

	ListTexture::CreateAllTexture();
	ListSound::CreateAllSound();
	
	GlobalHandler::RestartMap();

	GlobalHandler::player->Init(18, 0, 4);
	GlobalHandler::dynamicObjManager->Add(GlobalHandler::player);	
}

bool Game::Run(){
	
	Update();

	if (GlobalHandler::quitGame)
		return false;
	GlobalHandler::_directX->BeginScene();
	
	Render();

	GlobalHandler::_directX->EndScene();
	GlobalHandler::_directX->_d3ddv->Present(NULL, NULL, NULL, NULL);
	

	return true;
}

void Game::Update(){
	/*list<StaticObject*>::iterator it;
	for(it = GlobalHandler::listStaticObj.begin(); it != GlobalHandler::listStaticObj.end(); ++it )	
	(*it)->Update();*/		
	GlobalHandler::quadTree->UpdateScreen();
	GlobalHandler::dynamicObjManager->Update();
}

void Game::Render(){

	/*list<StaticObject*>::iterator it;
	for(it = GlobalHandler::listStaticObjRender.begin(); it != GlobalHandler::listStaticObjRender.end(); ++it ){
	trace(L"Id: %d", (*it)->id);
	}*/
	
	GlobalHandler::quadTree->RenderScreen();
	GlobalHandler::dynamicObjManager->Render();
}

void Game::ProcessKeyboard(){
	GlobalHandler::_directX->ProcessKeyBoard();
	for( DWORD i = 0; i < GlobalHandler::_directX->dwElements; i++ )
	{
		int keyCode = GlobalHandler::_directX->keyEvents[i].dwOfs;
		int keyState = GlobalHandler::_directX->keyEvents[i].dwData;
		if ( (keyState & 0x80) > 0)
		{
			OnKeyDown(keyCode);			
		}
		else 
		{
			OnKeyUp(keyCode);
		}
	}
}

void Game::ProcessInput(){
	GlobalHandler::player->ProcessInput();
}

void Game::OnKeyDown(int keyCode){
	switch (GlobalHandler::gameState)
	{
		case GS_OPTION:
			break;
		case GS_MENU:
			break;
		case GS_CHANGEMAP:
			break;
		case GS_STARTGAMEOPTIONS:
			break;
		case GS_GAMEPLAY:
			GlobalHandler::player->OnKeyDown(keyCode);
			break;
	}
}

void Game::OnKeyUp(int keyCode){}