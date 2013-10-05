#include "Game.h"
#include "Coin.h"

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
	GlobalHandler::screen.left		= 0;
	GlobalHandler::screen.top		= 0;
	GlobalHandler::screen.right		= SCREEN_WIDTH;
	GlobalHandler::screen.bottom	= SCREEN_HEIGHT;
	ListTexture::CreateAllTexture();
	
	GlobalHandler::RestartMap();
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
	GlobalHandler::quadTree->UpdateScreen();
}

void Game::Render(){
	GlobalHandler::quadTree->RenderScreen();
}