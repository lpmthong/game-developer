#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

	Game *nGame = new Game(hInstance, nCmdShow);
	nGame->Init();

	MSG msg;
	DWORD frame_start = GetTickCount();
	int done = 0;
	while(!done){
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			if(msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();
		if (now - frame_start >= 100 / nGame->frameRate){
			if (nGame->Run() == false)
				done = 1;
			frame_start = now;
		}
		nGame->ProcessKeyboard();
		nGame->ProcessInput();
	}
	delete nGame;
	return (int) msg.wParam;
}