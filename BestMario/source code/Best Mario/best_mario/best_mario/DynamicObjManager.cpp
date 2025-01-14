#include "DynamicObjManager.h"
#include "GlobalHandler.h"
#include "BrickBreak.h"
#include "ListSound.h"

DynamicObjManager::DynamicObjManager(void){}

DynamicObjManager::~DynamicObjManager(void){}

void DynamicObjManager::Add(DynamicObject *obj){

	listDynamicObj.push_back(obj);

}

void DynamicObjManager::Remove(DynamicObject *obj){

	listDynamicObj.remove(obj);
	//trace(L"Remove isKind: %d", obj->isKind);
}

void DynamicObjManager::Render(){

	list<DynamicObject*>::iterator it;
	for (it = listDynamicObj.begin(); it != listDynamicObj.end(); it++)
		(*it)->Render();
}

void DynamicObjManager::Update(){

	list<DynamicObject*> listBrickBreak;
	list<DynamicObject*> listInHell;

	list<DynamicObject*>::iterator it;
	for (it = listDynamicObj.begin(); it != listDynamicObj.end(); it++){
		if (GlobalHandler::CheckRectInRect((*it)->rectDraw, GlobalHandler::screen) == true)
		{
			if ((*it)->start == false)
			{
				(*it)->Start(); // Ong nao ma nguoi choi thay thi moi bat dau chay.
			}				
		}
		else //dua nao ra ngoai man roi thi dung co update no nua stop no di @@
		{
			if ((*it)->start == true && (*it)->isKind != PLAYER_KID && (*it)->isKind != PLAYER_ADULT && 
				(*it)->isKind != PLAYER_ADULT_GUN && (*it)->isKind == MUSHROOM_ENEMY)
				(*it)->start = false;
		}

		if ((*it)->start == true)
		{
			(*it)->Update();
			if ((*it)->isKind == BRICK_BREAK_DISAPPEAR)
				listBrickBreak.push_back((*it));
			if ((*it)->alive == INHELL)
				listInHell.push_back((*it));
		}
	}

	//Loai bo danh sach Brick Break
	list<DynamicObject*>::iterator it_bb;
	for (it_bb = listBrickBreak.begin(); it_bb != listBrickBreak.end(); it_bb++){
		Remove((*it_bb));
	}

	//loai bo danh sach inhell
	list<DynamicObject*>::iterator it_ih;
	for (it_ih = listInHell.begin(); it_ih != listInHell.end(); it_ih++){
		Remove((*it_ih));
	}

	//Xoa cac obj trong cai danh sach remove ra di
	list<DynamicObject*>::iterator it_rm;
	for (it_rm = GlobalHandler::listRemove.begin(); it_rm != GlobalHandler::listRemove.end(); it_rm++){
		Remove((*it_rm));
	}

	//trace(L"Update Dynamic ----");
}

void DynamicObjManager::Release()
{
	DynamicObject* temp;

	while (!(listDynamicObj.empty()))
	{
		list<DynamicObject*>::iterator it = listDynamicObj.begin();
		temp = (*it);
		listDynamicObj.pop_front();
		if (temp->isKind == 10)
			continue;
		delete temp;
	}
}

void DynamicObjManager::GetTick(){
	list<DynamicObject*>::iterator it;
	for (it = listDynamicObj.begin(); it != listDynamicObj.end(); it ++)
	{
		(*it)->GetTick();
	}
}

void DynamicObjManager::ProcessBrickBreak(StaticObject* brick)
{
	BrickBreak* brickBreakLT = new BrickBreak(brick->rectDraw.left, brick->rectDraw.top);
	brickBreakLT->setType(BB_LEFT_TOP);
	Add(brickBreakLT);

	BrickBreak* brickBreakRT = new BrickBreak(brick->rectDraw.left + 16, brick->rectDraw.top);
	brickBreakLT->setType(BB_RIGHT_TOP);
	Add(brickBreakRT);

	BrickBreak* brickBreakLB = new BrickBreak(brick->rectDraw.left, brick->rectDraw.top + 16);
	brickBreakLB->setType(BB_LEFT_BOTTOM);
	Add(brickBreakLB);

	BrickBreak* brickBreakRB = new BrickBreak(brick->rectDraw.left + 16, brick->rectDraw.top + 16);
	brickBreakRB->setType(BB_RIGHT_BOTTOM);
	Add(brickBreakRB);

	GlobalHandler::quadTree->RemoveObj(brick);
	GlobalHandler::sound->Play(ListSound::SOUND_BRICKBREAKED, false);
}

void DynamicObjManager::Save(){

	list<DynamicObject*>::iterator it;
	for (it = listDynamicObj.begin(); it != listDynamicObj.end(); it++){
	
		if ((*it)->isKind != BULLET && (*it)->isKind != BONUS_MUSHROOM && (*it)->isKind != PLAYER_KID && 
			(*it)->isKind != PLAYER_ADULT && (*it)->isKind != PLAYER_ADULT_GUN)
			if ((*it)->alive == ALIVE && (*it)->id > 0)			
				GlobalHandler::save->SaveText(L" %d %d %d %d\n", (*it)->id, (*it)->isKind, (*it)->rectDraw.left, (*it)->rectDraw.top);

	}
}
