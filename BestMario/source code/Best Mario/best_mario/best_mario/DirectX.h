#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#include "Define.h"

#define DIRECTINPUT_VERSION 0x0800
//#define KEY_DOWN(code) ( IsKeyDown(code) )
#define KEYBOARD_BUFFER_SIZE 1024

class DirectX{

public:
	DirectX(void);
	DirectX(HINSTANCE hInstance);
	~DirectX(void);

private:
	HINSTANCE _hInstance;
	UINT ncmdShow;

	LPDIRECT3D9 _d3d;

	LPDIRECTINPUT8			di;
	LPDIRECTINPUTDEVICE8		keyboard;

public:
	HWND _hWnd;
	LPDIRECT3DDEVICE9 _d3ddv;
	LPDIRECT3DSURFACE9	_backBuffer;
	LPDIRECT3DSURFACE9	_backGround;
	D3DFORMAT _backBufferFormat;

	LPD3DXSPRITE _spriteHandler;

	BYTE keyStates[256];
	DIDEVICEOBJECTDATA		keyEvents[ KEYBOARD_BUFFER_SIZE ];
	DWORD					dwElements;
public:
	void Init(HINSTANCE hInstance);

private:
	void InitWindow();
	void InitDirectX();
	void InitSpriteHandler();
	void InitKeyBoard();
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void Release();
	void ProcessKeyBoard();
	int	 IsKeyDown(int KeyCode);

public:
	LPDIRECT3DTEXTURE9 LoadTextureFromFile(char* path, D3DCOLOR transkey);
	bool BeginScene();
	bool EndScene();
};