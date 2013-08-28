#pragma once
#include "Sprites.h"
#include "Effect.h"
#include "iostream"
#include "IO.h"
#include "SoundManager.h"

class Moving
{
public: 
	bool IsLeft;//Qua trai hay phai
	int Step;//pexel/Frame
	DWORD NFrameTime;//toc do binh thuong
	DWORD HFrameTime;//toc do nhay
	DWORD FrameTime;//Bao nhieu mili giay thi cap nhat vi tri
	DWORD OldTime;
	Moving()
	{
		IsLeft=false;FrameTime=NFrameTime=HFrameTime=30;Step=1;
		OldTime=GetTickCount();
	}	
	Moving(bool isLeft,DWORD nFrameTime,DWORD hFrameTime,int step)
	{
		IsLeft=isLeft;
		Step=step;
		HFrameTime=hFrameTime;
		FrameTime=NFrameTime=nFrameTime;
		OldTime=GetTickCount();
	}
};

class UpDown
{
public:
	int Index;
	DWORD SpeedUp;
	DWORD SpeedDown;
	DWORD OldTime;
	bool IsUp;
	bool IsSupper;
	UpDown(int Style)
	{
		switch(Style)
		{
		case 0://Nhay len
			Index=17;
			IsUp=true;
			SpeedDown=12;
			SpeedUp=10;
			break;
		case 1://Chet
			Index=15;
			IsUp=true;
			SpeedDown=30;
			SpeedUp=20;
			break;
		case 2://di chuyen va duoi chan la khoang khong
			IsUp=false;
			Index=0;
			SpeedDown=15;
			SpeedUp=10;
			break;
		case 3://Dam enemy rui nay len
			Index=100;
			IsUp=true;
			SpeedDown=1000;
			SpeedUp=1000;
			break;
		case 4://Bullet
			Index=10;
			IsUp=true;
			SpeedDown=10;
			SpeedUp=10;
			break;
		case 5://Bar
			Index=23;
			IsUp=true;
			SpeedDown=20;
			SpeedUp=20;
			break;
		}
		IsSupper=false;
		OldTime=GetTickCount();
	}
};
class Object//Day se la lop cha cho tat ca cac doi tuong sau nay
{
public:
	int ID;
	SoundManager *soundManager;
	int Layer;
	RECT *Rect;
	bool IsActive;
	bool JustMove;
	Sprites *Sprite;
	UpDown *upDown;
	bool IsLeft;
	int Sequency;//So thu tu
	int Kind;//(4 loai) mat dat,gach,dau cham hoi, va gach co nhieu coin
	int Status;//0_dung;1_Dang nhay;2_Chetrui;
	bool Visible;//An hay hien
	Moving *OnMove;
	virtual void WriteToFile(FILE *f){};
	virtual void Draw(int VirtualLeft,int Style){}
	virtual int Move(){return 0;};
	virtual void BeTouch(Object *Ob){};

	virtual void Release(){};
	Object(void)
	{		
		Rect=new RECT();
		Sprite=NULL;
	}
	~Object(void){}
};
