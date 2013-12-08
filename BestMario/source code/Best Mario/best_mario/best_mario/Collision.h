#pragma once
#include "Box.h"
#include <cmath>
#include <algorithm>
#include <limits>
using namespace std;

class Collision{

public:
	Collision(void);
	Box GetSweptBroadphaseBox(Box b);
	bool AABBCheck(Box box1, Box box2);
	float SweptAABB(Box box1, Box box2, float& normalx, float& normaly);
	~Collision(void);
};