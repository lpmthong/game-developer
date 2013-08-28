#include "DynamicObjManager.h"
#include "GlobalHandler.h"
#include "BrickBreak.h"
#include "trace.h"

DynamicObjManager::DynamicObjManager(void)
{
}

DynamicObjManager::~DynamicObjManager(void)
{
}

void DynamicObjManager::Add( DynamicObject* obj )
{
	liDynamicObj.push_back(obj);
}

void DynamicObjManager::Remove( DynamicObject* obj )
{
	liDynamicObj.remove(obj);
}

void DynamicObjManager::Update()
{
	//If brick break get out of screen, this variable hold that brick break and remove it from DynamicObjectManager.
	DynamicObject* brickBreak = NULL;
	DynamicObject* enemy = NULL;

	list<DynamicObject*>::iterator it;
	for (it = liDynamicObj.begin(); it != liDynamicObj.end(); it ++)
	{
		if (GlobalHandler::CheckRectInRect((*it)->recRealArea, GlobalHandler::screen) == true)
		{
			if ((*it)->start == false)
			{
				(*it)->Start();
			}
		}
		
		if ((*it)->start == true)
		{
			(*it)->Update();

			if ((*it)->iKind == BRICK_BREAK_DISAPPEAR)
				brickBreak = (*it);
			
			if ((*it)->alive == INHELL)
			{
				enemy = (*it);
				if (enemy!=NULL)
					trace(L"%d", enemy->iKind);
			}
		}
	}

	Remove(brickBreak);
	Remove(enemy);
}

void DynamicObjManager::Render()
{
	list<DynamicObject*>::iterator it;
	for (it = liDynamicObj.begin(); it != liDynamicObj.end(); it ++)
	{

		//if ((*it)->iKind == PLAYER_ADULT_GUN || (*it)->iKind == PLAYER_KID || (*it)->iKind == PLAYER_ADULT)
		//	trace(L"%d %d", (*it)->recDrawArea.left, (*it)->recDrawArea.top);
		(*it)->Render();
	}
}

void DynamicObjManager::Release()
{
	DynamicObject* temp;

	while (!(liDynamicObj.empty()))
	{
		list<DynamicObject*>::iterator it = liDynamicObj.begin();
		temp = (*it);
		liDynamicObj.pop_front();
		if (temp->iKind == 10)
			continue;
		delete temp;
	}
}

DynamicObject* DynamicObjManager::CheckCollision( DynamicObject* obj, list<DynamicObject*> holder)
{
	list<DynamicObject*>::iterator it;
	for (it = liDynamicObj.begin(); it != liDynamicObj.end(); it ++)
	{
		if ((*it) != obj)
			//obj not in list holder
			if (InList(holder, (*it)) == false)
				//Just check collide with solid object.
				if ((*it)->isSolid == true)
					//if ((*it)->iKind != MUSHROOM_ENEMY)
					if (GlobalHandler::CheckRectInRect(obj->recRealArea, (*it)->recRealArea) ||
						GlobalHandler::CheckRectInRect((*it)->recRealArea, obj->recRealArea))
						{
							//(*it)->ProcessCollision(obj->iKind);
							//trace(L"Collide with edge");
							return (*it);	
						}
	}

	return NULL;
}

void DynamicObjManager::ProcessBrickBreak( DynamicObject* brick )
{
	BrickBreak* brickBreakLT = new BrickBreak(brick->recDrawArea.left, brick->recDrawArea.top);
	brickBreakLT->setType(BB_LEFT_TOP);
	Add(brickBreakLT);

	BrickBreak* brickBreakRT = new BrickBreak(brick->recDrawArea.left + 16, brick->recDrawArea.top);
	brickBreakRT->setType(BB_RIGHT_TOP);
	Add(brickBreakRT);

	BrickBreak* brickBreakLB = new BrickBreak(brick->recDrawArea.left, brick->recDrawArea.top + 16);
	brickBreakLB->setType(BB_LEFT_BOTTOM);
	Add(brickBreakLB);

	BrickBreak* brickBreakRB = new BrickBreak(brick->recDrawArea.left + 16, brick->recDrawArea.top + 16);
	brickBreakRB->setType(BB_RIGHT_BOTTOM);
	Add(brickBreakRB);

	brick->alive = INHELL;
}

bool DynamicObjManager::InList( list<DynamicObject*> holder, DynamicObject* obj )
{
	list<DynamicObject*>::iterator it;
	for (it = holder.begin(); it != holder.end(); it ++)
	{
		if ((*it) == obj)
			return true;
	}
	return false;
}

void DynamicObjManager::GetTick()
{
	list<DynamicObject*>::iterator it;
	for (it = liDynamicObj.begin(); it != liDynamicObj.end(); it ++)
	{
		(*it)->GetTick();
	}
}

void DynamicObjManager::Reset()
{
	Release();
}

void DynamicObjManager::SaveFile()
{
	list<DynamicObject*>::iterator it;
	for (it = liDynamicObj.begin(); it != liDynamicObj.end(); it ++)
		if ((*it)->iKind != PLAYER_KID && (*it)->iKind != PLAYER_ADULT && (*it)->iKind != PLAYER_ADULT_GUN )
			GlobalHandler::saveGame->SaveObject(*it);
}
