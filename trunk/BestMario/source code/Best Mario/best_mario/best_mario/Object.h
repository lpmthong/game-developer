#pragma once
#include "DirectX.h"
#include "Sprite.h"

class Object{

public:
	LPD3DXSPRITE spriteHandler;
	LPDIRECT3DSURFACE9 backbuffer;

	RECT rectDraw; //Rect ve len
	int width;
	int height;

	int isKind; //Thuoc loai nao
	bool isSolid; //Co va cham khong

	int animatedRate;
	DWORD lastAnimate;

	DWORD lastUpdate;

	Sprite* sprite;	
		
	bool start; //Doi tuong nay bat dau chua

public:
	Object(void);
	~Object(void);

	virtual void Update();
	virtual void Render();
	

	virtual bool CheckCollision(Object *obj); //Kiem tra va cham voi obj khac
	virtual void ProcessCollision(int iKind);
	virtual void UpdateRect(int left, int top, int width, int height);
	void UpdateRect(int left, int top);
	virtual void GetTick();
	virtual void Start();	

};