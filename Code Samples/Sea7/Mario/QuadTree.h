#pragma once
#include "QuadNode.h"
#include "Define.h"
#include "trace.h"
#include "StaticObject.h"
#include "DynamicObject.h"

class QuadTree
{
private:
	QuadNode* root;
	int mapWidth;		//Map width.
	int mapHeight;		//Map height.
	int count;
public:
	QuadTree(void);
	~QuadTree(void);

	void Release();
	void Release(QuadNode* root);
	void Reset();

	QuadTree(int _mapWidth, int _mapHeight);
	// Add object to a node on the tree.
	void AddNode(QuadNode* root, StaticObject* obj);
	// Check to find where to add new node to the tree (LT LB RT or RB).
	int FindPlaceToAddNode(RECT rootRect, StaticObject* obj);
	// Render all object on screen.
	void RenderScreen(QuadNode* root, RECT screenRect);
	// Check to see if mainRec is over checkRec.
	bool CheckRectInRect(RECT mainRec, RECT checkRec);
	// Check to see if point(x,y) is in the rect.
	bool CheckPointInRect(int x, int y, RECT rect);
	void AddNode(StaticObject* obj);

	bool RemoveObj(StaticObject* obj);
	bool RemoveObj(QuadNode* root, StaticObject* obj);
	void Render(RECT screenRect);


	void Render(int map_level);
	// Render all object on screen.

	//Update all object on screen.
	void UpdateScreen();
	void UpdateScreen(QuadNode* root);
	

	void RenderScreen();
	//Render object on screen with map level.
	void RenderScreen(QuadNode* root, int map_level);

	// Check to see if obj collide with any object in the tree.
	StaticObject* CheckCollision(QuadNode* root, DynamicObject* obj);
	bool CheckCollisionRect(QuadNode* root, RECT rect);
	bool CheckCollisionRect(RECT rect);
	StaticObject* CheckCollision(DynamicObject* obj);

	//Obj has gravity?
	bool CheckGravity(DynamicObject* obj);

	void SaveFile();
	void SaveFile(QuadNode* root);
};