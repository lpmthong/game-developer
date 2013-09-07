#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "Define.h"
//////////////////////////////////////////////////////////////////////////
///Khai bao class theo thu tu cac ham trong class de truc quan hon
//////////////////////////////////////////////////////////////////////////
class DirectX{

public:
	DirectX(void);
	DirectX(HINSTANCE hInstance);
	~DirectX(void);

private:
	HINSTANCE _hInstance;
	UINT ncmdShow;

	LPDIRECT3D9 _d3d;

public:
	HWND _hWnd;
	LPDIRECT3DDEVICE9 _d3ddv;
	LPDIRECT3DSURFACE9	_backBuffer;
	LPDIRECT3DSURFACE9	_backGround;
	D3DFORMAT _backBufferFormat;

	LPD3DXSPRITE _spriteHandler;

public:
	void Init(HINSTANCE hInstance);

private:
	void InitWindow();
	void InitDirectX();
	void InitSpriteHandler();
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void Release();

public:
	LPDIRECT3DTEXTURE9 LoadTextureFormFile(char* path, D3DCOLOR transkey);
	bool BeginScene();
	bool EndScene();
};