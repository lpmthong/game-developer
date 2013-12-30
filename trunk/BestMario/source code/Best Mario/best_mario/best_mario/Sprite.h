#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class Sprite{
public:
	Sprite(void);
	Sprite(LPDIRECT3DTEXTURE9 texture, int width, int height, int count, int spritePerRow);
	~Sprite(void);
protected:
	LPDIRECT3DTEXTURE9 _texture;
	int _index;
	int _width;
	int _height;
	int _count;
	int _spritePerRow;
	int _distanceFromTop;

public:
	void Next();
	void Next(int start, int end);

	void Reset();
	void Reset(LPDIRECT3DTEXTURE9 texture, int width, int height, int count, int spritePerRow);
	void setIndex(int i);
	void setIndex(int start, int end);
	int	 getIndex();
	void setDistanceFromTop(int d);
	void setWidthHeight(int w, int h);
	RECT InitRenderRect();

	void Render(float x, float y);
	void Render(LPDIRECT3DSURFACE9 target, int x, int y);
	void Render(LPDIRECT3DSURFACE9 target, int x, int y, int vpx, int vpy);
	void Render(LPDIRECT3DSURFACE9 target, int x, int y, int vpx, int vpy, int top);
	void Render(LPDIRECT3DSURFACE9 target, int x, int y, int srcLeft, int srcTop, int srcRight, int srcBottom);
	void Render(LPDIRECT3DSURFACE9 target, int x, int y, int vpx, int vpy, int srcLeft, int srcTop, int srcRight, int srcBottom);
};