#pragma once
#include "list"
#include "StaticObject.h"
#include "DirectX.h"
using namespace std;

class QuadNode{

public:
	list<StaticObject*> listObject;
	RECT rect;
	int a;
	QuadNode *LTNode,*LBNode, *RTNode, *RBNode;

public:
	QuadNode(void);
	QuadNode(int left, int top, int width, int height);
	~QuadNode(void);

	void Release();
	void Render();
	void Render(int map_level);
	void Update();

	//void SaveFile();
};