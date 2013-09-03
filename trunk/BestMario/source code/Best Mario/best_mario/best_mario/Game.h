#pragma once

#include "DirectX.h"
#include "GlobalHandler.h"

class Game{
public:
	Game(void);
	Game(HINSTANCE _hInstance, UINT _nCmdShow);
	~Game(void);
public:
	HINSTANCE _hInstance;
	UINT nCmdShow;
	LPDIRECT3DDEVICE9 _d3ddv;
	
public:
	void Init();
};