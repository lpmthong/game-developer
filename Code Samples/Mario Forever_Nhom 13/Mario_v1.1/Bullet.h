#pragma once
#include "Mario.h"

class Bullet :public Mario
{
public:
	Effect **effect;
	Bullet(void);
	Bullet(BulletManager* bulletCounter,bool isLeft,int left,int top,LPD3DXSPRITE sprite_Handle,LPDIRECT3DTEXTURE9 *texture,Effect **ef,QuadTree *q,MyScreen *scr,Infomation *info);
	void Draw(int VirtualLeft,int Style);
	int Move();
	void BeTouch(Object *Ob);
	void WriteToFile(FILE *f){}
	void Release()
	{
		bulletManager->BulletCounter--;
	}
	~Bullet(void);
};
