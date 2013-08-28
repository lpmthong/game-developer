#pragma once
#include "DirectX.h"
#include "trace.h"
#include "Debug.h"
#include "Player.h"
#include "GlobalHandler.h"
#include "Menu.h"
#include "Option.h"
#include "ChangeMap.h"
#include "StartGameOptions.h"

#define FRAME_RATE	60

class Game
{
public:
	Game(void);
	Game(HINSTANCE _hInstance, UINT _nCmdShow);
	~Game(void);

private:
	HINSTANCE hInstance;
	UINT nCmdShow;
	LPDIRECT3DDEVICE9 d3ddev;
	DirectX *directX;

	Menu* menu;
	Option* option;
	ChangeMap* changeMap;
	StartGameOptions* startGameOptions;
public:
	RECT screen;
public:
	int frameRate;
	Player* player;

public:
	void GameInit();

	//return true: game continue;	false: quit game.
	bool GameRun();
	void GameEnd();

	void ProcessKeyboard();
	void ProcessInput();

	void Render();
	void Update();

	void RestartMap();
private:
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);

private:
	void UpdateScreen(int left, int top, int width, int height);
};

