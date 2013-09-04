#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

	Game *nGame = new Game(hInstance, nCmdShow);
	nGame->Init();

	MSG msg;

	while(1){
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			if(msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (nGame->Run() == false)
			break;
	}
	delete nGame;
	return (int) msg.wParam;
}