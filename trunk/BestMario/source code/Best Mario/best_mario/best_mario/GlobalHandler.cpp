#include "GlobalHandler.h"
#include "ListTerrain.h"

DirectX				*GlobalHandler::_directX			= new DirectX();
QuadTree			*GlobalHandler::quadTree			;
DynamicObjManager	*GlobalHandler::dynamicObjManager	= new DynamicObjManager();
Player				*GlobalHandler::player				= new Player();
int		             GlobalHandler::backGroundColor		= BLUE;
bool	             GlobalHandler::quitGame			= false;

RECT	             GlobalHandler::screen;
int					 GlobalHandler::mapLevel			= 1;
int					 GlobalHandler::gameState			= GS_GAMEPLAY;

int					 GlobalHandler::checkpoint[2][10];
int					 GlobalHandler::checkpoint_index	= 0;

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

void GlobalHandler::UpdateScreen(){

	if (GlobalHandler::player->rectDraw.left > SCREEN_WIDTH / 2)
	{
		GlobalHandler::screen.left = GlobalHandler::player->rectDraw.left - SCREEN_WIDTH / 2;
		GlobalHandler::screen.right = GlobalHandler::screen.left + SCREEN_WIDTH;
	}

}

void GlobalHandler::RestartMap()
{
	GlobalHandler::screen.left		= 0;
	GlobalHandler::screen.top		= 0;
	GlobalHandler::screen.right		= SCREEN_WIDTH;
	GlobalHandler::screen.bottom	= SCREEN_HEIGHT;

	//GlobalHandler::quadTree->Reset();
	GlobalHandler::dynamicObjManager->Release();
	ListTerrain::InitTerrain(GlobalHandler::mapLevel);
	
	trace(L"void GlobalHandler::RestartMap()");
}

