#include "QuadTree.h"
#include "GlobalHandler.h"

QuadTree::QuadTree(void)
{
	count = 0;
}

QuadTree::~QuadTree(void)
{
}
QuadTree::QuadTree(int _mapWidth, int _mapHeight)
{
	mapHeight = _mapHeight;
	mapWidth = _mapWidth;
	root = new QuadNode(0, 0, mapWidth, mapHeight);
	count = 0;
}

// Add object to a node on the tree.
void QuadTree::AddNode(QuadNode* root, StaticObject* obj)
{
	if (root != NULL)
	{
		int addedPosition = FindPlaceToAddNode(root->rect, obj);

		if (addedPosition == NORMAL)
		{
			root->listObject.push_back(obj);
			count ++;
		}
		else
		{
			//Get width of the root rect.
			int rootWidth = root->rect.right - root->rect.left;

			if (rootWidth /2 >= MIN_NODE_WIDTH)
			{
				switch (addedPosition)
				{
				case LT:
					if (root->LTNode == NULL)
						root->LTNode = new QuadNode(root->rect.left, root->rect.top, rootWidth / 2, rootWidth / 2);
					AddNode(root->LTNode, obj);
					break;
				case RT:
					if (root->RTNode == NULL)
						root->RTNode = new QuadNode(root->rect.left + rootWidth / 2, root->rect.top, rootWidth / 2, rootWidth / 2);
					AddNode(root->RTNode, obj);
					break;
				case LB:
					if (root->LBNode == NULL)
						root->LBNode = new QuadNode(root->rect.left, root->rect.top + rootWidth / 2, rootWidth / 2, rootWidth / 2);
					AddNode(root->LBNode, obj);
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

// Check to find where to add new node to the tree (LT LB RT or RB).
int QuadTree::FindPlaceToAddNode(RECT rootRect, StaticObject* obj)
{
	//Two line divide the rootRect.
	int x = (rootRect.left + rootRect.right) / 2;
	int y = (rootRect.bottom + rootRect.top) / 2;

	//If the line which divide the root rect is in the object.
	if (((obj->recRealArea.left <= x) && (obj->recRealArea.right > x)) ||
		((obj->recRealArea.top <= y) && (obj->recRealArea.bottom > y)))
	{
		return NORMAL;
	}
	else
	{
		if (obj->recRealArea.right < x)
			if (obj->recRealArea.bottom < y)
				return LT;
			else
				return LB;
		else
			if (obj->recRealArea.bottom < y)
				return RT;
			else
				return RB;
	}
	return 0;
}

// Render all object on screen.
void QuadTree::RenderScreen(QuadNode* root, RECT screenRect)
{
	root->Render();

	if ((root->LTNode != NULL) && (CheckRectInRect(screenRect, root->LTNode->rect)))
		RenderScreen(root->LTNode, screenRect);
	if ((root->RTNode != NULL) && (CheckRectInRect(screenRect, root->RTNode->rect)))
		RenderScreen(root->RTNode, screenRect);
	if ((root->LBNode != NULL) && (CheckRectInRect(screenRect, root->LBNode->rect)))
		RenderScreen(root->LBNode, screenRect);
	if ((root->RBNode != NULL) && (CheckRectInRect(screenRect, root->RBNode->rect)))
		RenderScreen(root->RBNode, screenRect);
}

void QuadTree::RenderScreen( QuadNode* root, int map_level )
{
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

void QuadTree::RenderScreen()
{
	if (GlobalHandler::player->recDrawArea.left > 900)
		int a = 0;
	RenderScreen(root, 0);
	RenderScreen(root, 1);
	RenderScreen(root, 2);
}

// Check to see if mainRec is over checkRec.
bool QuadTree::CheckRectInRect(RECT mainRect, RECT checkRect)
{
	if (CheckPointInRect(checkRect.left, checkRect.top, mainRect) ||
		CheckPointInRect(checkRect.right - 1, checkRect.top, mainRect) ||
		CheckPointInRect(checkRect.left, checkRect.bottom - 1, mainRect) ||
		CheckPointInRect(checkRect.right - 1, checkRect.bottom - 1, mainRect) ||
		(mainRect.top>=checkRect.top&&mainRect.bottom<=checkRect.bottom&&checkRect.left<=mainRect.left&&checkRect.right>=mainRect.right))
		return true;
	return false;
}

// Check to see if point(x,y) is in the rect.
bool QuadTree::CheckPointInRect(int x, int y, RECT rect)
{
	if ((x >= rect.left) &&
		(x < rect.right) &&
		(y >= rect.top) &&
		(y < rect.bottom))
		return true;
	return false;
}

void QuadTree::AddNode(StaticObject* obj)
{
	AddNode(root, obj);
}

void QuadTree::Render(RECT screenRect)
{
	RenderScreen(root, screenRect);
}

void QuadTree::Render( int map_level )
{
		
}

// Check to see if obj collide with any object in the tree.
StaticObject* QuadTree::CheckCollision(QuadNode* root, DynamicObject* obj)
{
	list<StaticObject*>::iterator it;
	for (it = root->listObject.begin(); it != root->listObject.end(); it ++)
	{
		if ((*it)->isSolid)
			if (CheckRectInRect(obj->recRealArea, (*it)->recRealArea) ||
				CheckRectInRect((*it)->recRealArea, obj->recRealArea))
			{
				(*it)->ProcessCollision(obj->iKind);
				return (*it);
				
			}
	}

	if (root->LTNode != NULL && 
		(CheckRectInRect(obj->recRealArea, root->LTNode->rect) || 
		CheckRectInRect(root->LTNode->rect, obj->recRealArea)))
	{
		StaticObject* objTemp = new StaticObject();
		objTemp = CheckCollision(root->LTNode, obj);
		if (objTemp != NULL)
			return objTemp;
	}
	if (root->RTNode != NULL && 
		(CheckRectInRect(obj->recRealArea, root->RTNode->rect) || 
		CheckRectInRect(root->RTNode->rect, obj->recRealArea)))
	{
		StaticObject* objTemp = new StaticObject();
		objTemp = CheckCollision(root->RTNode, obj);
		if (objTemp != NULL)
			return objTemp;
	}
	if (root->LBNode != NULL && 
		(CheckRectInRect(obj->recRealArea, root->LBNode->rect) || 
		CheckRectInRect(root->LBNode->rect, obj->recRealArea)))
	{	
		StaticObject* objTemp = new StaticObject();
		objTemp = CheckCollision(root->LBNode, obj);
		if (objTemp != NULL)
			return objTemp;
	}
	if (root->RBNode != NULL && 
		(CheckRectInRect(obj->recRealArea, root->RBNode->rect) || 
		CheckRectInRect(root->RBNode->rect, obj->recRealArea)))
	{	
		StaticObject* objTemp = new StaticObject();
		objTemp = CheckCollision(root->RBNode, obj);
		if (objTemp != NULL)
			return objTemp;
	}
}


bool QuadTree::CheckCollisionRect(QuadNode* root, RECT rect)
{
	list<StaticObject*>::iterator it;
	for (it = root->listObject.begin(); it != root->listObject.end(); it ++)
	{
//		if ((*it)->iKind != BACKGROUND_BLOCK)
			if (CheckRectInRect(rect,(*it)->recRealArea))
			{
				return true;
			}
	}

	if (root->LTNode != NULL)
		if (CheckCollisionRect(root->LTNode, rect) == true)
			return true;
	if (root->RTNode != NULL)
		if (CheckCollisionRect(root->RTNode, rect) == true)
			return true;
	if (root->LBNode != NULL)
		if (CheckCollisionRect(root->LBNode, rect) == true)
			return true;
	if (root->RBNode != NULL)
		if (CheckCollisionRect(root->RBNode, rect) == true)
			return true;

	return false;
}

bool QuadTree::CheckCollisionRect(RECT rect)
{
	return CheckCollisionRect(root, rect);
}

StaticObject* QuadTree::CheckCollision(DynamicObject* obj)
{
	return CheckCollision(root, obj);
}

void QuadTree::Release()
{
	Release(root);
}

void QuadTree::Release( QuadNode* root )
{
	if (root->LTNode != NULL)
		Release(root->LTNode);
	if (root->RTNode != NULL)
		Release(root->RTNode);
	if (root->LBNode != NULL)
		Release(root->LBNode);
	if (root->RBNode != NULL)
		Release(root->RBNode);

	root->Release();
	delete root;
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

bool QuadTree::RemoveObj( StaticObject* obj )
{
	return RemoveObj(root, obj);
}

bool QuadTree::RemoveObj( QuadNode* root, StaticObject* obj )
{
	list<StaticObject*>::iterator it;
	for (it = root->listObject.begin(); it != root->listObject.end(); it ++)
	{
		if (obj == (*it))
		{
			root->listObject.remove(obj);
			return true;
		}
	//	trace(L"%d", obj->recRealArea.left);
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

bool QuadTree::CheckGravity( DynamicObject* obj )
{
	return true;
}

void QuadTree::Reset()
{
	Release(root);
	root = new QuadNode(0, 0, MAP_WIDTH, MAP_WIDTH);
	count = 0;
}

void QuadTree::SaveFile()
{
	SaveFile(root);
}

void QuadTree::SaveFile( QuadNode* root )
{
	if (root->LTNode != NULL)
		SaveFile(root->LTNode);
	if (root->RTNode != NULL)
		SaveFile(root->RTNode);
	if (root->LBNode != NULL)
		SaveFile(root->LBNode);
	if (root->RBNode != NULL)
		SaveFile(root->RBNode);

	root->SaveFile();
}
