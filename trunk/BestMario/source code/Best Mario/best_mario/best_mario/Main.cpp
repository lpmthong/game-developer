#include <Windows.h>
#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	mGame _mGame(hInstance, L"demo");

	_mGame.Init();

	return 0;
}