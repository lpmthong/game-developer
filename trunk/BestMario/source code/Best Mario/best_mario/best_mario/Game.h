#pragma once

#include "DirectX.h"
#include "GlobalHandler.h"

//include test

#include "Pipe.h"
#include "ListTexture.h"

#define FRAME_RATE	60

class Game{
public:
	Game(void);
	Game(HINSTANCE _hInstance, UINT _nCmdShow);
	~Game(void);
public:
	HINSTANCE _hInstance;
	UINT nCmdShow;
	LPDIRECT3DDEVICE9 _d3ddv;
	
	int frameRate;

	//Test
	Pipe *test;
	//EndTest

public:
	void Init();
	bool Run();
};