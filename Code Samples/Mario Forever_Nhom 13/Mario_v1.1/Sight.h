#pragma once
#include "Object.h"
#include "QuadTree.h"

class Sight :public Object
{
public:
	QuadTree 	*quadTree;
	Sight(void);
	Sight(int left,int top,int kind,bool visible,LPD3DXSPRITE sprite_Handle,LPDIRECT3DTEXTURE9 *texture,QuadTree *q);
	void Draw(int VirtualLeft,int Style);
	int Move();
	void BeTouch(Object *Ob);
	void WriteToFile(FILE *f);
	void Release(){}
	~Sight(void);
};
