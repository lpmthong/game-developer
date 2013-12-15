#include "DynamicObjManager.h"
#include "GlobalHandler.h"

DynamicObjManager::DynamicObjManager(void){}

DynamicObjManager::~DynamicObjManager(void){}

void DynamicObjManager::Add(DynamicObject *obj){

	listDynamicObj.push_back(obj);

}

void DynamicObjManager::Remove(DynamicObject *obj){

	listDynamicObj.remove(obj);

}

void DynamicObjManager::Render(){

	list<DynamicObject*>::iterator it;
	for (it = listDynamicObj.begin(); it != listDynamicObj.end(); it++)
		(*it)->Render();

}

void DynamicObjManager::Update(){

	list<DynamicObject*>::iterator it;
	for (it = listDynamicObj.begin(); it != listDynamicObj.end(); it++){
		if (GlobalHandler::CheckRectInRect((*it)->rectDraw, GlobalHandler::screen) == true)
		{
			if ((*it)->start == false)
			{
				(*it)->Start(); // Ong nao ma nguoi choi thay thi moi bat dau chay.
			}
		}

		if ((*it)->start == true)
		{
			(*it)->Update();			
		}
	}

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
