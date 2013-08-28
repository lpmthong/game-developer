#include "windows.h"
class MyScreen
{
public:	
	int LimLeft,LimRight,LimBottom;
	RECT Rect;
	MyScreen(int limLeft,int limRight,int limBottom,RECT *rect)
	{		
		LimLeft=limLeft;
		LimRight=limRight;
		LimBottom=limBottom;
		Rect=*rect;
	}
};