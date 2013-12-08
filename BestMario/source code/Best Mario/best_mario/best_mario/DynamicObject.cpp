#include "DynamicObject.h"


DynamicObject::DynamicObject(void){
	alive = ALIVE;
	start = false;
	isSolid = true;

	width = 1;
	height = 1;
}

DynamicObject::~DynamicObject(void){}

void DynamicObject::ProcessDying(){}