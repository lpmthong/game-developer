//#include "mmain.h"
#include "Global.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

	MSG msg;
	//DWORD frame_start = GetTickCount();
	int done = 0;
	mmain *m =new mmain();
	m->Init(hInstance);
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0,0,PM_REMOVE))
		{
			if (msg.message==WM_QUIT)
				done=1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
				
	}
	return (int) msg.wParam;
}