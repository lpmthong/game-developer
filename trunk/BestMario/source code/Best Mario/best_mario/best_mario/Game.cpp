#include "Game.h"
#include "Sprite.h"

Game::Game(void){}

Game::Game(HINSTANCE hInstance, UINT _nCmdShow){
	_hInstance = hInstance;
	nCmdShow = _nCmdShow;
	_d3ddv = NULL;

	frameRate = FRAME_RATE;
}

Game::~Game(void){}

void Game::Init(){
	GlobalHandler::_directX->Init(_hInstance);
	GlobalHandler::screen.left		= 0;
	GlobalHandler::screen.top		= 0;
	GlobalHandler::screen.right		= SCREEN_WIDTH;
	GlobalHandler::screen.bottom	= SCREEN_HEIGHT;

	ListTexture::CreateAllTexture();
	cl = new Cloud(50,50);
}

bool Game::Run(){
	
	cl->Update();
	if (GlobalHandler::quitGame)
		return false;
	GlobalHandler::_directX->BeginScene();
	cl->Render();	
	GlobalHandler::_directX->EndScene();
	GlobalHandler::_directX->_d3ddv->Present(NULL, NULL, NULL, NULL);
	
	return true;
}