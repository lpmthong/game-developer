#include "Object.h"
#include "GlobalHandler.h"


Object::Object(void){}

Object::~Object(void){}

bool Object::CheckCollision(Object *obj){
	return false;
}

void Object::ProcessCollision(int iKind){

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
}

void Object::UpdateRect(int left, int top){
	UpdateRect(left, top, width, height);
}

void Object::GetTick(){
	lastUpdate = GetTickCount();
}

void Object::Start(){
	start = true;
	GetTick();
}
