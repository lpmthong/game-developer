#include "Game.h"

DirectX *_directX = new DirectX();

mGame::mGame(void){}

mGame::mGame(HINSTANCE hInstance, LPWSTR Name){	

	_hInstance = hInstance;
	_name = Name;
}

void mGame::InitWindow(){
	WNDCLASSEX wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_PEN);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hInstance = _hInstance;
	wc.lpfnWndProc = (WNDPROC)mGame::_WndProc;
	wc.lpszClassName = this->_name;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wc);

	//Center screen
	int screenX = GetSystemMetrics(SM_CYSCREEN);
	int screenY = GetSystemMetrics(SM_CXSCREEN);

	int xCtr = (screenX / 2 );
	int yCtr = (screenY / 2 ) - GAME_HIGHT;

	this->_hWnd = CreateWindowA("Demo",
		"Demo",
		WS_OVERLAPPEDWINDOW,
		xCtr,
		yCtr,
		GAME_WIDTH,
		GAME_HIGHT,
		NULL,
		NULL,
		_hInstance,
		NULL);

	ShowWindow(this->_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(this->_hWnd);
}

void mGame::Init(){
	this->InitWindow();	
	_directX->InitDirectX(_hWnd);
}

void mGame::Run(){
	MSG msg;
	
	while(1){
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			if(msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	
}

LRESULT CALLBACK mGame::_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	switch (message){
		case WM_DESTROY: 
			PostQuitMessage(0);
			break;
		default: 
			return DefWindowProc(hWnd, message, wParam,lParam);
	}

	return 0;
}
mGame::~mGame()
{
	//_directX->~DirectX();
}