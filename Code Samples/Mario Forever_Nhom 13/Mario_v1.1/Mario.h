#pragma once
#include "Sprites.h"
#include "windows.h"
#include "QuadTree.h"
#include "MyScreen.h"
#include "Infomation.h"

class BulletManager
{
public:
	int BulletCounter;
	int MaxBullet;
	DWORD OldTime;
	DWORD Interval;//Khoang cach giua 2 lan ban
	BulletManager(int maxB,DWORD interval)
	{
		OldTime=GetTickCount();
		BulletCounter=0;
		MaxBullet=maxB;
		Interval=interval;
	}
};

class Mario:public Object
{
public:
	//Status==2 la chet rui, lost control
	int Level;
	Infomation *infomation;
	QuadTree *quadTree;
	Mario(void)
	{
		Rect=new RECT();
		Sprite=NULL;
	}
	Mario(int left,LPD3DXSPRITE sprite_Handle,LPDIRECT3DTEXTURE9 *texture,MyScreen *scr,QuadTree *q,Infomation *info,SoundManager *sManager);
	void ChangeDim(bool IsJump);
	void LevelChange(int Increase);
	int Move();
	void BeTouch(Object *Ob);
	void Draw(int VirtualLeft,int Style);
	void WriteToFile(FILE *f);
	void Die();
	void Jump();
	int CheckLeftRight();
	int CheckUpDown(bool IsUp);
	BulletManager *bulletManager;
	~Mario(void);
	MyScreen *screen;
	void Release(){}
	bool JustChangeLevel;
};