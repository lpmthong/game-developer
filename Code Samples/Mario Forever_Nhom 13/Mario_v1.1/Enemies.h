#pragma once
#include "Bullet.h"
class Enemies: public Mario
{
public:
	Enemies(void)
	{
		Rect=new RECT();
		Sprite=NULL;
	}
	Enemies(int left,int top,int width,int height,MyScreen *sc,LPD3DXSPRITE sprite_Handle,LPDIRECT3DTEXTURE9 *texture,QuadTree *q,int kind,SoundManager *sManager);
	void Draw(int VirtualLeft,int Style);
	int Move();
	void BeTouch(Object *Ob);
	void WriteToFile(FILE *f);
public:
	~Enemies(void);
	void Release(){}
private:
	void ChangeDim();
	void ChangeStatus(int style);	
};
