#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Game *game = new Game(hInstance, nCmdShow);
	game->GameInit();

	MSG msg;
	DWORD frame_start = GetTickCount();
	int done = 0;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0,0,PM_REMOVE))
		{
			if (msg.message==WM_QUIT)
				done=1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();
		if (now - frame_start > 100 / game->frameRate){
			if (game->GameRun() == false)
				done = 1;
			frame_start = now;
		}

		game->ProcessKeyboard();
		game->ProcessInput();
	}

	game->GameEnd();
	delete game;
	return (int) msg.wParam;
}