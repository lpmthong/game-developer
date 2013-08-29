#include <windows.h>
#include "game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	TGame rec(hInstance,L"Kitty");

	rec.Init();
	rec.Run();

	return 0;
}