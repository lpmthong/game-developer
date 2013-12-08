#pragma once

#include "DirectX.h"
#include "ListTexture.h"

//include test
#include "StaticObject.h"
//

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
	//EndTest

public:
	void Init();
	bool Run();
	void Update();
	void Render();

	void ProcessKeyboard();
	void ProcessInput();

private:
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
};