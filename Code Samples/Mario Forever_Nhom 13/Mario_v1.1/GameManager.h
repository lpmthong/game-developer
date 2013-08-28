#pragma once
#include "dinput.h"
#include "dinputd.h"
#include "MapManager.h"
#include "Menu.h"

#define KEYDOWN(name, key) (name[key] & 0x80)


class GameManager
{
public:
	HWND hWnd;
	HINSTANCE hInst;
	//Graphics
	LPDIRECT3D9  pD3D;
	LPDIRECT3DDEVICE9 pd3dDevice;
	LPD3DXSPRITE sprite_handler;

	//KeyBoard
	LPDIRECTINPUT8 KeyBoard_Object;
	LPDIRECTINPUTDEVICE8A KeyBoard_Device;
	//Textures
	LPDIRECT3DTEXTURE9 BackGround_Image;
	LPDIRECT3DTEXTURE9 Mario_Image;
	LPDIRECT3DTEXTURE9 Squares_Image;
	LPDIRECT3DTEXTURE9 Enemies_Image;
	LPDIRECT3DTEXTURE9 Bonuses_Image;
	LPDIRECT3DTEXTURE9 Sight_Image;
	LPDIRECT3DTEXTURE9 First_Image;
	LPDIRECT3DTEXTURE9 Info_Image;
	//
	Mario *MyMario;
	//
	SoundManager *soundManager;
	//
	Effect *effect[10];
	//
	MapManager *mapManage;
	Menu *menu;
	Infomation *infomation;
	int Status;//0_Menu, 1_Playing, 2_GameOver, 3_Ket thuc Map

	bool InitDirect3D();
	bool InitDirectInput();
	LPDIRECT3DTEXTURE9 LoadTexture(char *filename,D3DCOLOR transcolor);
	IDirect3DSurface9* LoadSurface(char *filename);

	void KeyBoard();
	void InitTexture();

	void NewGame();
	void ResetGame();
	void FinishedMap();
	void GameOver();
	//Draw Function
	void MainDraw();
	void DrawEffect();
	void DrawMario();
	void DrawMenu();
	GameManager(HWND hwn,HINSTANCE hIn);
	void Run();
	~GameManager(void);	
};
