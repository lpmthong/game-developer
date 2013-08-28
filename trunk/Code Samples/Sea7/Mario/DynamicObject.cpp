#include "DynamicObject.h"
#include "Define.h"

DynamicObject::DynamicObject(void)
{
	isSolid = true;
	alive = ALIVE;
	start = false;

	width = 1;
	height = 1;
}

DynamicObject::~DynamicObject(void)
{
}

void DynamicObject::ProcessDying()
{

}
