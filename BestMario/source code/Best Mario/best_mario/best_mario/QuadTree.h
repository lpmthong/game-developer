#pragma once
#include "QuadNode.h"
#include "Define.h"
#include "GlobalHandler.h"

class QuadTree {

public:
	QuadNode *root;
	int mapwidth;
	int mapheight;
	int count;

public:

	QuadTree(void);
	QuadTree(int _mapwidth, int _mapheight);
	~QuadTree();

	void Release();
	void Release(QuadNode *root);
	void Reset();
	
	bool CheckPointInRect(int x, int y, RECT rect);
	bool CheckRectInRect(RECT mainRect, RECT checkRect);	

	int  FindPlaceToAdd(RECT rectRoot, StaticObject* obj); //Tim vi tri de add node vao cay LT LB RT RB
	void AddNode(StaticObject *obj);
	void AddNode(QuadNode *root, StaticObject* obj); //Them node vao cay
	
	bool RemoveObj(StaticObject* obj);
	bool RemoveObj(QuadNode* root, StaticObject* obj);	

	void RenderScreen();
	void RenderScreen(QuadNode *root, int map_level);

	void UpdateScreen();
	void UpdateScreen(QuadNode* root);

};