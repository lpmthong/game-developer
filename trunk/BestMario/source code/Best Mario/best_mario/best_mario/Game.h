#ifndef GAME_MARIO
#define GAME_MARIO

#include <Windows.h>
#include "Define.h"
#include "DirectX.h"

class mGame{

	//Nhung bien nao dat giong ten kieu bien thi them cai dau _ dang truoc cai bien nha, xem xong xoa dong nay di :))
private:
	HINSTANCE _hInstance;
	HWND _hWnd;
		
	LPWSTR _name;

	static LRESULT CALLBACK _WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void InitWindow();

public:
	mGame(void);
	mGame(HINSTANCE hInstance, LPWSTR Name);
	~mGame();		
	void Init();
	//void Run();

};

#endif