#include "QuadNode.h"
#include "Define.h"
#include "trace.h"
#include "GlobalHandler.h"

QuadNode::QuadNode(void)
{
//	rect = NULL;
	LTNode = RTNode = LBNode = RBNode = NULL;
}

QuadNode::QuadNode(int left, int top, int width, int height)
{
	//rect = new RECT();
	rect.left = left;
	rect.top = top;
	rect.right = left + width;
	rect.bottom = top + height;

//	rect(left, top, left + width, top + height);
	LTNode = RTNode = LBNode = RBNode = NULL;
	a = 0;
}

QuadNode::~QuadNode(void)
{
	//delete LTNode;
	//delete RTNode;
	//delete LBNode;
	//delete RBNode;
}

// Render all object in this node.
void QuadNode::Render()
{
	list<StaticObject*>::iterator it;
	for(it = listObject.begin(); it != listObject.end(); ++it)
	{
		(*it)->Render();
	}
}

void QuadNode::Render( int map_level )
{
	list<StaticObject*>::iterator it;
	for(it = listObject.begin(); it != listObject.end(); ++it)
	{
//		trace(L"%d", (*it)->recDrawArea.left);
		if ((*it)->map_level == map_level)
			(*it)->Render();
	}

}

void QuadNode::Release()
{
	StaticObject* temp;

	while (!(listObject.empty()))
	{
		list<StaticObject*>::iterator it = listObject.begin();
		temp = (*it);
		listObject.pop_front();
		delete temp;
	}
}

void QuadNode::Update()
{
	list<StaticObject*>::iterator it;
	for(it = listObject.begin(); it != listObject.end(); ++it)
		(*it)->Update();
}

void QuadNode::SaveFile()
{
	list<StaticObject*>::iterator it;
	for(it = listObject.begin(); it != listObject.end(); ++it)
		GlobalHandler::saveGame->SaveObject(*it);
}
