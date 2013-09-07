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
	void Reset();
	void setIndex(int i);
	int	 getIndex();
	void setDistanceFromTop(int d);
	RECT InitRenderRect();
	void Render(float x, float y);
};