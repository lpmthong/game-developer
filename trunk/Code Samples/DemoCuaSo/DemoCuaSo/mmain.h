
#pragma once
#include <Windows.h>
#include "d3d9.h"
#include "d3dx9.h"

class mmain
{
public:
	HINSTANCE hInstance;
	HWND hWND;
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddev;
	LPDIRECT3DSURFACE9	backbuffer;

	mmain(void);
	~mmain(void);
	void Init(HINSTANCE m_hInstance);
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	
	UINT nCmdShow;
	void m_InitWidow();
	void m_InitDirectX();

};

