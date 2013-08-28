#include "Define.h"
#include "GlobalHandler.h"
#include "ListTerrain.h"
#include "ListSound.h"

DirectX				*GlobalHandler::directX				= new DirectX();
QuadTree			*GlobalHandler::quadTree			= new QuadTree(MAP_WIDTH, MAP_WIDTH);
DynamicObjManager	*GlobalHandler::dynamicObjManager	= new DynamicObjManager();
DXSound				*GlobalHandler::sound				= new DXSound();
int					GlobalHandler::gameState			= GS_MENU;

Player				*GlobalHandler::player				= new Player();

RECT				GlobalHandler::screen;//		= NULL;
int					GlobalHandler::levelTime			= 300;
DWORD				GlobalHandler::lastUpdateTime		= GetTickCount();

int					GlobalHandler::mapLevel1			= 0;
int					GlobalHandler::mapLevel2			= 0;
int					GlobalHandler::backGroundColor		= BLUE;
int					GlobalHandler::mapLevel				= 1;

Text				*GlobalHandler::txt					= NULL;

int					GlobalHandler::checkpoint[2][10];
int					GlobalHandler::checkpoint_index		= 0;

bool				GlobalHandler::quitGame				= false;
bool				GlobalHandler::endMap				= false;
bool				GlobalHandler::isStarted			= false;

int					GlobalHandler::playerScore			= 0;
int					GlobalHandler::playerCoin			= 0;

SaveGame			*GlobalHandler::saveGame			= new SaveGame();

GlobalHandler::GlobalHandler(void)
{
}

GlobalHandler::~GlobalHandler(void)
{
}

// Check to see if point(x,y) is in the rect.
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

bool GlobalHandler::UpdateTime()
{
	//trace()
	DWORD now = GetTickCount();

	if (now - lastUpdateTime > 1000)
	{
		lastUpdateTime = now;
		levelTime--;

		if (levelTime <= 0)
			return false;
	}

	return true;
}

void GlobalHandler::UpdateScreen()
{
	if (endMap)
		return;

	if (GlobalHandler::player->recDrawArea.left > SCREEN_WIDTH / 2)
	{
		GlobalHandler::screen.left = GlobalHandler::player->recDrawArea.left - SCREEN_WIDTH / 2;
		GlobalHandler::screen.right = GlobalHandler::screen.left + SCREEN_WIDTH;
	}
	else
	{
		GlobalHandler::screen.left = 0;
		GlobalHandler::screen.right = GlobalHandler::screen.left + SCREEN_WIDTH;
	}
}

void GlobalHandler::InitText()
{
	txt = new Text();
}

void GlobalHandler::RestartMap()
{
	GlobalHandler::screen.left		= 0;
	GlobalHandler::screen.top		= 0;
	GlobalHandler::screen.right		= SCREEN_WIDTH;
	GlobalHandler::screen.bottom	= SCREEN_HEIGHT;
	GlobalHandler::player = new Player();
	GlobalHandler::levelTime = 300;

	GlobalHandler::quadTree->Reset();
	GlobalHandler::dynamicObjManager->Reset();
	ListTerrain::InitTerrain(GlobalHandler::mapLevel);

	GlobalHandler::dynamicObjManager->GetTick();

	GlobalHandler::endMap = false;
	GlobalHandler::InitText();

	GlobalHandler::isStarted = true;
	GlobalHandler::sound->Play(ListSound::SOUND_BACKGROUND, true);

	trace(L"void GlobalHandler::RestartMap()");
}
