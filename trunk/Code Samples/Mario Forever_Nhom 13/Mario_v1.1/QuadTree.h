#pragma once
#include "windows.h"
#include "MyArrayList.h"
#include "Definition.h"
/*#include "IO.h"
#include "iostream"*/

#define LIM_W_H 5

class QuadNode
{
public:
	MyArrayList ArrayList;
	RECT *Rect;
	QuadNode *LT,*RT,*LB,*RB;
	QuadNode()
	{
		Rect=NULL;
		LT=RT=LB=RB=NULL;
	}
	QuadNode(int left,int top,int width,int height)
	{
		Rect=new RECT();
		Rect->left=left;Rect->top=top;
		Rect->right=Rect->left+width;
		Rect->bottom=Rect->top+height;
		LT=RT=LB=RB=NULL;
	}
};
class QuadTree
{
public:
	QuadNode *Root;
	int MapWidth,MapHeight;
	int Count;
	QuadTree(int w,int h);
	void Add(QuadNode *root,Object *Ob);
	void OutPutTree(QuadNode *root);
	//Chi in nhung cai nam tren main hinh hien tai
	void DrawObjects(int VirtualLeft,QuadNode *root,RECT Screen,int layer);
	Object* CheckCollision(QuadNode *root,RECT r,int Seq);
	bool IsOnObject(RECT *rect,int Seq);//duoi chan object la object khac hay la khoang trong
	void UpdatePosition(QuadNode *root);
	bool Remove(QuadNode *root,Object *Ob);
	void WriteToFile(QuadNode *root,FILE *f);
	~QuadTree(void);
private:
	int CheckRECT(RECT *rootRECT,Object *Ob);
	bool RECTInRECT(RECT r,RECT rect);
	bool PointInRECT(int x,int y,RECT rect);
	//0_Add binh thg
	//1_LT
	//2_RT
	//3_LB
	//4_RB
};
