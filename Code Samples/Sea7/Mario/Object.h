#pragma once
#include "DirectX.h"
#include "Sprite.h"

class Object
{
public:
	LPD3DXSPRITE spriteHandler;
	LPDIRECT3DSURFACE9 backbuffer;

	RECT recDrawArea;	//Rectangle holds object image.
	RECT recRealArea;	//Rectangle holds real part of object.
	int width;
	int height;

	int iKind;			//Kind of this Object.

	bool isSolid;		//Check collision.

	int animatedRate;
	DWORD lastAnimate;

	DWORD lastUpdate;

	Sprite* sprite;		//Sprite.

	//This object start to moving and do everything it can do. Or can say it is now in screen.
	bool start;
public:
	Object(void);
	~Object(void);

	virtual void Update();
	virtual void Render(int xScreen, int yScreen);
	virtual void Render();

	// Check to see if this object collide with another object.
	virtual bool CheckCollision(Object* obj);
	// Process after a collision happen.
	virtual void ProcessCollision(int iKind);
	virtual void UpdateRect(int left, int top, int width, int height);
	void UpdateRect(int left, int top);

	void UpdateRecReal(int left, int top);
	virtual void GetTick();

	//Start to go in real, it can do anything from now on.
	virtual void Start();
};