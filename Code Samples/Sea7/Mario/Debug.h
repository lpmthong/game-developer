#pragma once
#include "DirectX.h"
#include "Define.h"
#include "Sprite.h"

class Debug
{
private:
	LPD3DXSPRITE spriteHandler;
	LPDIRECT3DSURFACE9 backbuffer;

	Sprite* number;

	int aNumber[100];
	int iIndex;
public:
	Debug(void);
	~Debug(void);

	void LoadResource(LPDIRECT3DDEVICE9 d3ddev);
	void Render(int iNumber, int x, int y);

private:
	void Debug::ResetLocation();
	void Debug::FillArray(int iNumber);

	
};
