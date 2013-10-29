#include "Object.h"
#include "GlobalHandler.h"

Object::Object(void){}

Object::~Object(void){}

bool Object::CheckCollision(Object *obj){
	return false;
}

void Object::ProcessCollision(){

}

void Object::Update(){
	DWORD now = GetTickCount();
	if(now - lastAnimate > animatedRate){
		sprite->Next();
		lastAnimate = now;
	}
}

void Object::Render(){
	RECT screen = GlobalHandler::screen;
	sprite->Render(backbuffer, rectDraw.left, rectDraw.top, screen.left , screen.bottom);
}

void Object::UpdateRect(int left, int top, int width, int height){
	rectDraw.left = left;
	rectDraw.right = left + width;
	rectDraw.top = top;
	rectDraw.bottom = top + height;

	rectReal.left = rectDraw.left + 3;
	rectReal.top = rectDraw.top + 2;
	rectReal.right = rectDraw.right - 3;
	rectReal.bottom = rectDraw.bottom - 2;
}

void Object::UpdateRect(int left, int top){
	UpdateRect(left, top, width, height);
}

void Object::UpdateRectReal(int left, int top){
	UpdateRect(left - 3, top - 2);
}

void Object::GetTick(){
	lastUpdate = GetTickCount();
}

void Object::Start(){
	start = true;
	GetTick();
}
