#include "MyArrayList.h"

//Class Element
Element::Element(Object *Obj)
{
	object=Obj;
	next=NULL;
}
//Class MyArrayList
MyArrayList::MyArrayList(void)
{
	Clear();	
}
void MyArrayList::Clear()
{
	Head=Tail=NULL;
	Count=0;
}
MyArrayList::~MyArrayList(void)
{
	//Head=NULL;
}
bool MyArrayList::Add(Object *Obj)
{
	if(Head==NULL)
	{
		Head=new Element(Obj);
		Tail=Head;
		Count++;
		return true;
	}
	Element *p=new Element(Obj);
	Tail->next=p;
	Tail=p;
	Count++;
	return true;
}
bool MyArrayList::AddArray(Object *Obj[], int Number)
{
	for(int i=0;i<Number;i++)
	{
		Add(Obj[i]);
	}
	return true;
}
Object *MyArrayList::operator[](int j)
{
	Element *p=Head;
	if(j<0||j>=Count)
		return NULL;
	for(int i=0;i<Count&&p!=NULL;i++)
	{
		if(i==j)
			break;
		p=p->next;
	}
	return p->object;
}
bool MyArrayList::Remove(Object *Obj,bool IsDelete)
{
	Element *Miss=Head;
	Element *p=Head;
	while(p!=NULL)
	{
		if(p->object==Obj)
		{
			if(Head->object==Obj)
			{
				Head=Head->next;
				if(Head==NULL)
					Tail=NULL;
			}
			else
			{
				Miss->next=p->next;
				if(Miss->next==NULL)
				{
					Tail=Miss;
				}
			}
			if(IsDelete)
				delete p;
			Count--;
			return true;
		}
		Miss=p;
		p=p->next;
	}
	return false;//Khong tim thay.
}