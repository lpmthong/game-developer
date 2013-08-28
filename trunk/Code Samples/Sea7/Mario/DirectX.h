#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#define KEY_DOWN(code) ( IsKeyDown(code) )
#define KEYBOARD_BUFFER_SIZE 1024

class DirectX
{
public:
	DirectX(void);
	DirectX(HINSTANCE _hInstance);
	~DirectX(void);
private:
	LPDIRECT3D9				d3d;
	
	HINSTANCE				hInstance;
	UINT					nCmdShow;


	LPDIRECTINPUT8			di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8	keyboard;	// The keyboard device 

public:
	HWND					hWnd;
	BYTE					keyStates[256];			// DirectInput keyboard state buffer 

public:
	LPDIRECT3DDEVICE9		d3ddev;
	LPDIRECT3DSURFACE9		backbuffer;

	//Sprite Handler
	LPD3DXSPRITE			spriteHandler;

	//Font handler
	LPD3DXFONT				font;

	// Buffered keyboard data
	DIDEVICEOBJECTDATA		keyEvents[ KEYBOARD_BUFFER_SIZE ];
	DWORD					dwElements;

public:
	void Init(HINSTANCE _hInstance);

private:
	void InitWindow();
	void InitDirectX();
	void InitKeyboard();
	void InitSpriteHandler();
	void InitFont(const TCHAR* fontFamily, int size, bool bold);
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void Release();
	void ProcessKeyboard();
	int IsKeyDown(int KeyCode);

public:
	LPDIRECT3DTEXTURE9 LoadTextureFromFile(char* fileName, D3DCOLOR transkey);
	void DrawText(LPCTSTR text,RECT &rect, D3DCOLOR color, int type = DT_LEFT | DT_VCENTER);

public:
	//Render
	bool BeginScene();
	bool EndScene();
};

