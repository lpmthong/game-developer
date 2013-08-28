#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class Sprite
{
public:
	Sprite(void);
	Sprite(LPD3DXSPRITE _spriteHandler, char *path, int _width, int _height, int _count, int _spritePerRow);
	Sprite(LPDIRECT3DTEXTURE9 texture, int _width, int _height, int _count, int _spritePerRow);
	Sprite(LPD3DXSPRITE _spriteHandler, char *path, int** _iSmallPicture, int _count, int _spritePerRow);
	~Sprite(void);

private:
	LPDIRECT3DTEXTURE9 image;
	LPD3DXSPRITE spriteHandler;

	int index;
	int width;
	int height;
	int count;
	int spritePerRow;

	int distanceFromTop;

	int** iSmallPicture;

public:
	void Next();

	void Reset(LPDIRECT3DTEXTURE9 texture, int _width, int _height, int _count, int _spritePerRow);

	//Render sprite from start frame to end frame.
	void Next(int start, int end);

	void Render(LPDIRECT3DSURFACE9 target, int x, int y);
	void Render(LPDIRECT3DSURFACE9 target, int x, int y, int top);
	void Render(LPDIRECT3DSURFACE9 target, int x, int y, int srcLeft, int srcTop, int srcRight, int srcBottom);

//	void Render(LPDIRECT3DSURFACE9 target, int x, int y, int _index);
	void Reset();

	void setIndex(int i);
	int getIndex();
	void setIndex(int start, int end);
	void setTexture(LPDIRECT3DTEXTURE9 texture);
	void setDistanceFromTop(int dis);
	void setWidthHeight(int w, int h);
	int getHeight();

	RECT InitRenderRect();
	void InitTexture(LPD3DXSPRITE _spriteHandler, char *path);
	// Init normal case rect.
	RECT InitRenderRectNormal(void);
};