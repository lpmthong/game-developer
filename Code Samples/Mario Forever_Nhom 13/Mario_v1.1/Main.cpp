#include "GameManager.h"
//#include "SoundManager.h"
//--------------- Global Variables--------------------------------------//
HINSTANCE hInst;
HWND hWnd;
bool Focus=false;

//SoundManager *s;
//---------------------------Function---------------------------------//
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int nCmdShow)
{
	MSG msg;
	if (!InitInstance (hInstance, nCmdShow))
		return FALSE;
	/*s=new SoundManager(hWnd);
	s->BackMusicSound.playSoundLoop(s->BackMusicBuffer);*/
	//ResetGame();
	/*InitMap();
	FILE *f=fopen("Maps\\Map0.mar","wb");
	fwrite(&mapManage->quadTree->MapWidth,sizeof(int),1,f);
	fwrite(&mapManage->quadTree->MapHeight,sizeof(int),1,f);
	fwrite(&mapManage->quadTree->Count,sizeof(int),1,f);
	mapManage->quadTree->WriteToFile(mapManage->quadTree->Root,f);
	fclose(f);*/
	GameManager *gameManager=new GameManager(hWnd,hInst);
	ZeroMemory(&msg,sizeof(msg));
	while (msg.message!=WM_QUIT)
	{
		
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	else
	{
			if(Focus)
				gameManager->KeyBoard();
			gameManager->Run();
		}
	}
	return (int) msg.wParam;
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+14);
	wcex.lpszMenuName	= NULL;;
	wcex.lpszClassName	= "Supper Mario";
	wcex.hIconSm		= NULL;
	RegisterClassEx(&wcex);
	hInst = hInstance; // Store instance handle in our global variable
	hWnd = CreateWindow("Supper Mario","Supper Mario", WS_SYSMENU|WS_MINIMIZEBOX|WS_EX_TOPMOST,
		100, 100,800+10,600+25, NULL, NULL, hInstance, NULL);
	if(!hWnd)
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_CREATE:
		srand ( (unsigned) time( NULL ) );
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_ACTIVATE:
			Focus=!Focus;
			break;
		default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return true;
}