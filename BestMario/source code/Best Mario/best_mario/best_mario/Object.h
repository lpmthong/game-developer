#pragma once
#include "DirectX.h"
#include "Sprite.h"

class Object{
public:
	LPD3DXSPRITE spriteHandler;
	LPDIRECT3DSURFACE9 backbuffer;

	RECT rectDraw; //Rect ve len
	RECT rectReal; //Rect thuc su dung de xet va cham
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
	virtual void Render(int xScreen, int yScreen);

	virtual bool CheckCollision(Object *obj); //Kiem tra va cham voi obj khac
	virtual void ProcessCollision();
	virtual void UpdateRect(int left, int top, int width, int height);
	void UpdateRect(int left, int top);
	void UpdateRectReal(int left, int top);
	virtual void GetTick();
	virtual void Start();	

};