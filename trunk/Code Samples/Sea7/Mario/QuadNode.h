#pragma once
#include "list"
#include "DirectX.h"
#include "StaticObject.h"
using namespace std;

class QuadNode
{
public:
	list<StaticObject*> listObject;
	RECT rect;
	int a;
	QuadNode *LTNode, *RTNode, *LBNode, *RBNode;
public:
	QuadNode(void);
	QuadNode(int left, int top, int width, int height);
	~QuadNode(void);

	//Release all object in this node.
	void Release();

	// Render all object in this node.
	void Render();
	void Render(int map_level);

	void Update();

	void SaveFile();
};
