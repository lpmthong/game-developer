#include "Object.h"
#include "GlobalHandler.h"

Object::Object(void)
{
}

Object::~Object(void)
{
}

// Check to see if this object collide with another object.
bool Object::CheckCollision(Object* obj)
{
	return false;
}

// Process after a collision happen.
void Object::ProcessCollision(int iKind)
{
}

void Object::Render(int xScreen, int yScreen)
{
	sprite->Render(backbuffer, recDrawArea.left - xScreen, recDrawArea.top - yScreen);
}

void Object::Render()
{
	RECT screen = GlobalHandler::screen;
	sprite->Render(GlobalHandler::directX->backbuffer, recDrawArea.left - screen.left, recDrawArea.top - screen.top);
//	trace(L"render %d %d", recDrawArea.left, recDrawArea.top);
}

void Object::UpdateRect(int left, int top, int iWidth, int iHeight)
{
	recDrawArea.left = left;
	recDrawArea.top = top;
	recDrawArea.right = left + iWidth;
	recDrawArea.bottom = top + iHeight;

	recRealArea.left = recDrawArea.left + 3;
	recRealArea.top = recDrawArea.top + 2;
	recRealArea.right = recDrawArea.right - 3;
	recRealArea.bottom = recDrawArea.bottom - 2;
}

void Object::UpdateRect(int left, int top)
{
	UpdateRect(left, top, width, height);
}

void Object::Update()
{
	DWORD now = GetTickCount();
	if (now - lastAnimate > animatedRate)
	{
		sprite->Next();
		lastAnimate = now;
	}
}

void Object::UpdateRecReal( int left, int top )
{
	UpdateRect(left - 3, top - 2);
}

void Object::GetTick()
{
	lastUpdate = GetTickCount();
}

void Object::Start()
{
	start = true;
	GetTick();
}
