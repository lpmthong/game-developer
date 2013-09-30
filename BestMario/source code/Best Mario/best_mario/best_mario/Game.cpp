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
	test = new Pipe(50,50, PIPE_CAP);
}

bool Game::Run(){
	
	test->Update();
	if (GlobalHandler::quitGame)
		return false;
	GlobalHandler::_directX->BeginScene();
	test->Render();	
	GlobalHandler::_directX->EndScene();
	GlobalHandler::_directX->_d3ddv->Present(NULL, NULL, NULL, NULL);
	
	return true;
}