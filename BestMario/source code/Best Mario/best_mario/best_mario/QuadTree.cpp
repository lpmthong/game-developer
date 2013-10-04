#include "QuadTree.h"

QuadTree::QuadTree(void){
	count = 0;
}

QuadTree::QuadTree(int _mapwidth, int _mapheight){
	mapwidth = _mapwidth;
	mapheight = _mapheight;
	root = new QuadNode(0, 0, mapwidth, mapheight);
	count = 0;
}

QuadTree::~QuadTree(void){}

void QuadTree::Release(){
	Release(root);
}

void QuadTree::Release(QuadNode *root){

	if(root->LTNode != NULL)
		Release(root->LTNode);
	if(root->LBNode != NULL)
		Release(root->LBNode);
	if(root->RTNode != NULL)
		Release(root->RTNode);
	if(root->RTNode != NULL)
		Release(root->LTNode);

	root->Release();
	delete root;
}

void QuadTree::Reset(){

	Release(root);
	root = new QuadNode(0, 0, MAP_WIDTH, MAP_WIDTH);
	count = 0;
}

bool QuadTree::CheckPointInRect(int x, int y, RECT rect){

	if(x >= rect.left && x <= rect.right && y >= rect.top && y <= rect.bottom)
		return true;
	return false;

}

bool QuadTree::CheckRectInRect(RECT mainRect, RECT checkRect){

	if (CheckPointInRect(checkRect.left, checkRect.top, mainRect) ||
		CheckPointInRect(checkRect.right - 1, checkRect.top, mainRect) ||
		CheckPointInRect(checkRect.left, checkRect.bottom - 1, mainRect) ||
		CheckPointInRect(checkRect.right - 1, checkRect.bottom - 1, mainRect) ||
		(mainRect.top>=checkRect.top&&mainRect.bottom<=checkRect.bottom&&checkRect.left<=mainRect.left&&checkRect.right>=mainRect.right))
		return true;
	return false;

}

int QuadTree::FindPlaceToAdd(RECT rectRoot, StaticObject* obj){

	int x = (rectRoot.right + rectRoot.left ) / 2;
	int y = (rectRoot.bottom + rectRoot.top ) / 2;

	if ((obj->rectReal.left<=x && obj->rectReal.right>x) || (obj->rectReal.top <= y && obj->rectReal.bottom > y))
		return NORMAL;
	else
		if(obj->rectReal.left < x)
			if (obj->rectReal.bottom < y)
				return LT;
			else
				return LB;
		else
			if (obj->rectReal.bottom < y)
				return RT;
			else
				return RB;
	return 0;
}

void QuadTree::AddNode(StaticObject *obj){
	AddNode(root, obj);
}

void QuadTree::AddNode(QuadNode *root, StaticObject* obj){
	if (root != NULL)
	{
		int addPosition = FindPlaceToAdd(root->rect, obj);

		if (addPosition == NORMAL)
		{
			root->listObject.push_back(obj);
			count++;
		}
		else
		{
			int rootWidth = root->rect.right - root->rect.left;

			if (rootWidth / 2 > MIN_NODE_WIDTH)
			{
				switch(addPosition)
				{
					case LT:
						if (root->LTNode == NULL)
							root->LTNode = new QuadNode(root->rect.left, root->rect.top, rootWidth/2, rootWidth/2);
						AddNode(root->LTNode, obj);
						break;
					case LB:
						if(root->LBNode == NULL)
							root->LBNode = new QuadNode(root->rect.left, root->rect.top + rootWidth/2, rootWidth/2, rootWidth/2);
						AddNode(root->LBNode, obj);
						break;
					case RT:
						if (root->RTNode == NULL)
							root->RTNode = new QuadNode(root->rect.left + rootWidth/2, root->rect.top, rootWidth/2, rootWidth/2);
						AddNode(root->RTNode, obj);
						break;
					case RB:
						if (root->RBNode == NULL)
							root->RBNode = new QuadNode(root->rect.left + rootWidth / 2, root->rect.top + rootWidth / 2, rootWidth / 2, rootWidth / 2);
						AddNode(root->RBNode, obj);
						break;
				}
			}
			else
			{
				root->listObject.push_back(obj);
				count ++;
			}
		}
	}
}

bool QuadTree::RemoveObj(StaticObject* obj){
	return RemoveObj(root, obj);
}

bool QuadTree::RemoveObj(QuadNode* root, StaticObject* obj){
	list<StaticObject*>::iterator it;
	for (it = root->listObject.begin(); it != root->listObject.end(); it ++)
	{
		if (obj == (*it))
		{
			root->listObject.remove(obj);
			return true;
		}
	}

	if (root->LTNode != NULL)
		if (RemoveObj(root->LTNode, obj) == true)
			return true;
	if (root->RTNode != NULL)
		if (RemoveObj(root->RTNode, obj) == true)
			return true;
	if (root->LBNode != NULL)
		if (RemoveObj(root->LBNode, obj) == true)
			return true;
	if (root->RBNode != NULL)
		if (RemoveObj(root->RBNode, obj) == true)
			return true;

	return false;
}

void QuadTree::RenderScreen(){
	RenderScreen(root, 0);
	RenderScreen(root, 1);
	RenderScreen(root, 2);
}

void QuadTree::RenderScreen(QuadNode *root, int map_level){
	root->Render(map_level);

	if ((root->LTNode != NULL) && (CheckRectInRect(GlobalHandler::screen, root->LTNode->rect)))
		RenderScreen(root->LTNode, map_level);
	if ((root->RTNode != NULL) && (CheckRectInRect(GlobalHandler::screen, root->RTNode->rect)))
		RenderScreen(root->RTNode, map_level);
	if ((root->LBNode != NULL) && (CheckRectInRect(GlobalHandler::screen, root->LBNode->rect)))
		RenderScreen(root->LBNode, map_level);
	if ((root->RBNode != NULL) && (CheckRectInRect(GlobalHandler::screen, root->RBNode->rect)))
		RenderScreen(root->RBNode, map_level);
}

void QuadTree::UpdateScreen()
{
	UpdateScreen(root);
}

void QuadTree::UpdateScreen( QuadNode* root )
{
	root->Update();

	if ((root->LTNode != NULL) && (CheckRectInRect(GlobalHandler::screen, root->LTNode->rect)))
		UpdateScreen(root->LTNode);
	if ((root->RTNode != NULL) && (CheckRectInRect(GlobalHandler::screen, root->RTNode->rect)))
		UpdateScreen(root->RTNode);
	if ((root->LBNode != NULL) && (CheckRectInRect(GlobalHandler::screen, root->LBNode->rect)))
		UpdateScreen(root->LBNode);
	if ((root->RBNode != NULL) && (CheckRectInRect(GlobalHandler::screen, root->RBNode->rect)))
		UpdateScreen(root->RBNode);

}
