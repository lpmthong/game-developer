#include "Collision.h"

Collision::Collision(void){}

Collision::~Collision(void){}

//Cai nay dang lam theo toa do thuc
Box Collision::GetSweptBroadphaseBox(Box b){

	Box newBox(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	newBox.x = b.vx > 0 ? b.x : b.x + b.vx; 
	newBox.y = b.vy > 0 ? b.y + b.vy : b.y; // b.y : b.y + b.vy  
	newBox.w = b.vx > 0 ? b.w + b.vx : b.w - b.vx;
	newBox.h = b.vy > 0 ? b.h + b.vy : b.h - b.vy;
	
	return newBox;
}

bool Collision::AABBCheck(Box box1, Box box2){

	return !(box1.x + box1.w < box2.x || box1.x > box2.x + box2.w || box1.y - box1.h > box2.y || box1.y < box2.y - box2.h);
	
}

//box1 la doi tuong di chuyen, box2 la doi tuong dung yen
float Collision::SweptAABB(Box box1, Box box2, float& normalx, float& normaly){

	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	if (box1.vx > 0.0f)
	{
		xInvEntry = box2.x - (box1.x + box1.w);
		xInvExit = (box2.x + box2.w) - box1.x;
	} 
	else 
	{
		xInvEntry = (box2.x + box2.w) - box1.x;
		xInvExit = box2.x - (box1.x + box1.w);		
	}

	if (box1.vy > 0.0f)
	{
		yInvEntry = (box2.y - box2.h) - box1.y;
		yInvExit = box2.y - (box1.y - box1.h);
	} 
	else 
	{
		yInvEntry = box2.y - (box1.y - box1.h);
		yInvExit = (box2.y - box2.h) - box1.y;		
	}

	float xEntry, yEntry;
	float xExit, yExit;

	if (box1.vx == 0.0f)
	{
		xEntry = -numeric_limits<float>::infinity();
		xExit = numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / box1.vx;
		xExit = xInvExit / box1.vx;
	}

	if (box1.vy == 0.0f)
	{
		yEntry = -numeric_limits<float>::infinity();
		yExit = numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / box1.vy;
		yExit = yInvExit / box1.vy;
	}
	
	float entryTime = std::max(xEntry, yEntry);
	float exitTime = std::min(xExit, yExit);

	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	} 
	else 
	{
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
		}

		return entryTime;
	}

}