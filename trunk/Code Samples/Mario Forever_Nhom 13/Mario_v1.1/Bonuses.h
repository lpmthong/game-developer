#pragma once
#include "Mario.h"

class Bonuses :	public Mario
{
public:
	Bonuses(void);
	Bonuses(int left,int top,LPD3DXSPRITE sprite_Handle,LPDIRECT3DTEXTURE9 *texture,QuadTree *q,int kind,SoundManager *sManager);
	int Move();
	void BeTouch(Object *Ob);
	void Draw(int VirtualLeft,int Style);
	void WriteToFile(FILE *f);
	~Bonuses(void);
};
