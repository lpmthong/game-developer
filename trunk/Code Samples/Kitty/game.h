#ifndef GAME_TETRIS
#define GAME_TETRIS
#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include <dinput.h>
#include "Kitty.h"

#define GAME_HIGHT 600
#define GAME_WIDTH 800
 
#define BACKGROUND L"bg.bmp" 
#define KEY_DOWN(code) ( IsKeyDown(code) )
#define KEYBOARD_BUFFER_SIZE	1024

class TGame
{
protected:
	LPDIRECT3D9 _d3d;
	LPDIRECT3DDEVICE9 _d3ddv;
	LPDIRECT3DSURFACE9 _BackBuffer;
	LPDIRECT3DSURFACE9 BackGround;
	LPD3DXSPRITE _SpriteHandler;

	LPDIRECTINPUT8 _di;
	LPDIRECTINPUTDEVICE8 _KeyBoard;
	Kitty *kitty;
	Kitty *kitty_bot;
	BYTE _KeyStates[256];
	int _FrameRate;
	DWORD _DeltaTime;
	D3DFORMAT _BackBufferFormat;

	DIDEVICEOBJECTDATA _KeyEvents[KEYBOARD_BUFFER_SIZE];
	
	LPWSTR _Name;
	HINSTANCE _hInstance;
	HWND _hWnd;	
	static LRESULT CALLBACK _WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void _InitWindow();
	void _InitDirectX();
	void _InitKeyBoard();
	void ProcessKeyBoard();
	int IsKeyDown(int KeyCode);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

public:
	TGame(void);
	TGame(HINSTANCE hInstance, LPWSTR Name);
	~TGame();
	void LoadResource();	
	void Render(int t);
	void Init();
	void Run();
};

#endif


