#pragma once
#include "windows.h"
#include "d3d9.h"
#include "d3dx9.h"

class Sprites
{
public:
	bool Loop;
	int Index;
	int Count;
	int Row;
	bool Enable;
	bool Clear;//Mo hay ro rang?
	int Width,Height;
	int Alpha;
	LPD3DXSPRITE sprite_Handle;
	LPDIRECT3DTEXTURE9 *texture;
	int Left,Top;
	DWORD RootTime,OldTime;
	int TotalExistTime,Interval;
	Sprites(bool loop,int index,int count,int row,int width,int height,
	LPD3DXSPRITE spr_Handle,LPDIRECT3DTEXTURE9 *tex,int left,int top,int totalExistTime,int interval);
	void Draw(int VirtualLeft,int StyleDraw,bool isClear);
	RECT GetSRect();
	~Sprites(void);
};
