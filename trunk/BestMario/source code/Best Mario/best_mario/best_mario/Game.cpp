#include "Game.h"
#include "Sprite.h"

Game::Game(void){}

Game::Game(HINSTANCE hInstance, UINT _nCmdShow){
	_hInstance = hInstance;
	nCmdShow = _nCmdShow;
	_d3ddv = NULL;
}

Game::~Game(void){}

void Game::Init(){
	GlobalHandler::_directX->Init(_hInstance);
}

bool Game::Run(){
	LPDIRECT3DTEXTURE9 tt = GlobalHandler::_directX->LoadTextureFormFile("Media\\brick.bmp",0);
	Sprite *sprite = new Sprite(tt, 32, 32, 1, 1);

	if (GlobalHandler::quitGame)
		return false;
	GlobalHandler::_directX->BeginScene();
	sprite->Render(200, 200);
	GlobalHandler::_directX->EndScene();
	GlobalHandler::_directX->_d3ddv->Present(NULL, NULL, NULL, NULL);

	return true;
}