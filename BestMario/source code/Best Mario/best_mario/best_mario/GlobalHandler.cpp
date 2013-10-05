#include "GlobalHandler.h"
#include "ListTerrain.h"

DirectX				*GlobalHandler::_directX			= new DirectX();
QuadTree			*GlobalHandler::quadTree			= new QuadTree(MAP_WIDTH, MAP_WIDTH);
int		             GlobalHandler::backGroundColor		= BLUE;
bool	             GlobalHandler::quitGame			= false;

RECT	             GlobalHandler::screen;
int					GlobalHandler::mapLevel				= 1;

GlobalHandler::GlobalHandler(void){}

GlobalHandler::~GlobalHandler(void){}

bool GlobalHandler::CheckPointInRect( int x, int y, RECT rect )
{
	if ((x >= rect.left) &&
		(x < rect.right) &&
		(y >= rect.top) &&
		(y < rect.bottom))
		return true;
	return false;
}

bool GlobalHandler::CheckRectInRect( RECT mainRect, RECT checkRect )
{
	if (CheckPointInRect(checkRect.left, checkRect.top, mainRect) ||
		CheckPointInRect(checkRect.right - 1, checkRect.top, mainRect) ||
		CheckPointInRect(checkRect.left, checkRect.bottom - 1, mainRect) ||
		CheckPointInRect(checkRect.right - 1, checkRect.bottom - 1, mainRect) ||
		(mainRect.top>=checkRect.top&&mainRect.bottom<=checkRect.bottom&&checkRect.left<=mainRect.left&&checkRect.right>=mainRect.right))
		return true;
	return false;
}

void GlobalHandler::RestartMap()
{
	GlobalHandler::screen.left		= 0;
	GlobalHandler::screen.top		= 0;
	GlobalHandler::screen.right		= SCREEN_WIDTH;
	GlobalHandler::screen.bottom	= SCREEN_HEIGHT;

	GlobalHandler::quadTree->Reset();
	ListTerrain::InitTerrain(GlobalHandler::mapLevel);
	
	trace(L"void GlobalHandler::RestartMap()");
}