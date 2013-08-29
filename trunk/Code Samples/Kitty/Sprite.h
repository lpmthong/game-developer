#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <d3d9.h>
#include <d3dx9.h>

class Sprite {
protected: 
	LPDIRECT3DTEXTURE9 _Image;
	LPD3DXSPRITE _SpriteHandler;

	int _Index;								// Current sprite index
	int _Width;								// Sprite width
	int _Height;							// Sprite height
	int _Count;								// Number of sprites
	int _SpritePerRow;						// Number of sprites per row
public: 
	Sprite(LPD3DXSPRITE SpriteHandler, LPWSTR FilePath, int Width, int Height, int Count, int SpritePerRow);
	void Next();
	void Reset();

	// Render current sprite at location (X,Y) at the target surface
	void Render(float X, float Y);	
	~Sprite();
};

#endif