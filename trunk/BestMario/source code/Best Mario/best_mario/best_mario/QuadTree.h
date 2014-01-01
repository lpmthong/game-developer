#pragma once
#include "QuadNode.h"
//#include "Define.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <map>
#include <stdio.h>
#include <algorithm>

class QuadTree {

public:	
	int mapwidth;
	int mapheight;
	int count;
	map<string, string> qTreeMap;	
	string list_id;
	RECT rNode;
	QuadNode *root;

	QuadTree(void);
	QuadTree(int _mapwidth, int _mapheight);
	~QuadTree();

	void Release();
	void Release(QuadNode *root);
	void Reset();

	void ReadQuadTreeFormFile(int level);
	void Deserialize();
	void SaveNode(QuadNode *iroot);
	void GetNodeInfo(string info);

	void RemoveObj(StaticObject* obj);
	void RemoveObj(QuadNode* root, StaticObject* obj);	

	void RenderScreen();
	void RenderScreen(QuadNode *root, int map_level);
	void RenderObj(int map_level);
	void RenderObj();

	void UpdateScreen();
	void UpdateScreen(QuadNode* root);
	

	void GetListObjCanCollide(RECT rectObj);
	void GetListObjCanCollide(RECT rectObj, QuadNode *root);

	void Save();
	void Save(QuadNode *root);
};