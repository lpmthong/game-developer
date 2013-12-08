#pragma once
#include <list>
#include "StaticObject.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <stdio.h>
#include <algorithm>

using namespace std;

class QuadNode{

public:
	list<StaticObject*> listObject;
	RECT rect;	
	QuadNode *LTNode,*LBNode, *RTNode, *RBNode;
	string id;

public:
	QuadNode(void);
	QuadNode(int left, int top, int right, int bottom, string iid);
	~QuadNode(void);

	void GetListObj(string ilist);
	void Release();
	void Render();
	void Render(int map_level);
	void Update();

	//void SaveFile();
};