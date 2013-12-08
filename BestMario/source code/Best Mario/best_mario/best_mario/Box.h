#pragma once

class Box{

public:
	//left, top
	float x, y;

	//Width, height
	float w, h;

	//Van toc x, y
	float vx, vy;

	Box(void);
	Box(float ix, float iy, float iw, float ih, float ivx, float ivy);
	~Box(void);
};