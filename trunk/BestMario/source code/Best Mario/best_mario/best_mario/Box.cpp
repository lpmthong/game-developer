#include "Box.h"

Box::Box(void){}

Box::Box(float ix, float iy, float iw, float ih, float ivx, float ivy){

	x = ix;
	y = iy;
	w = iw;
	h = ih;
	vx = ivx;
	vy = ivy;

}

Box::~Box(void){}