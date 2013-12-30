#include "GlobalHandler.h"
#include "ListTerrain.h"
#include "ListSound.h"

DirectX				*GlobalHandler::_directX			= new DirectX();
QuadTree			*GlobalHandler::quadTree			= new QuadTree();
DXSound				*GlobalHandler::sound				= new DXSound();

DynamicObjManager	*GlobalHandler::dynamicObjManager	= new DynamicObjManager();
list<DynamicObject*> GlobalHandler::listRemove			;

Player				*GlobalHandler::player				= new Player();
int		             GlobalHandler::backGroundColor		= BLUE;
bool	             GlobalHandler::quitGame			= false;
bool				 GlobalHandler::isStarted			= false;


list<StaticObject*>	 GlobalHandler::listStaticObj		;
list<StaticObject*>	 GlobalHandler::listStaticObjRender ;
list<StaticObject*>	 GlobalHandler::listStaticObjCanCollide;
Collision			*GlobalHandler::Physic				;

RECT	             GlobalHandler::screen;
int					 GlobalHandler::mapLevel1			= 0;
int					 GlobalHandler::mapLevel2			= 0;
int					 GlobalHandler::mapLevel			= 1;
int					 GlobalHandler::nextMap				= 2;
bool				 GlobalHandler::endMap				= false;
int					 GlobalHandler::gameState			= GS_MENU;
Text				*GlobalHandler::text				;
int					 GlobalHandler::time				= 300;
DWORD				 GlobalHandler::lastTime			= GetTickCount();

int					 GlobalHandler::checkpoint[2][10];
int					 GlobalHandler::checkpoint_index	= 0;

int					 GlobalHandler::playerScore			= 0;
int					 GlobalHandler::playerCoin			= 0;

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

bool GlobalHandler::CheckPointInRectReal( int x, int y, RECT rect )
{
	if ((x >= rect.left) &&
		(x < rect.right) &&
		(y <= rect.top) &&
		(y > rect.bottom))
		return true;
	return false;
}

bool GlobalHandler::CheckRectInRectReal( RECT mainRect, RECT checkRect )
{
	if (CheckPointInRect(checkRect.left, checkRect.top, mainRect) ||
		CheckPointInRect(checkRect.right - 1, checkRect.top, mainRect) ||
		CheckPointInRect(checkRect.left, checkRect.bottom - 1, mainRect) ||
		CheckPointInRect(checkRect.right - 1, checkRect.bottom - 1, mainRect) ||
		(mainRect.top<=checkRect.top&&mainRect.bottom>=checkRect.bottom&&checkRect.left<=mainRect.left&&checkRect.right>=mainRect.right))
		return true;
	return false;
}

void GlobalHandler::InitText()
{
	text = new Text();
}

bool GlobalHandler::UpdateTime()
{
	DWORD now = GetTickCount();
	if(now - lastTime > 1000)
	{
		lastTime = now;
		time--;
		if(time <= 0)
			return false;
	}
	return true;
}

void GlobalHandler::UpdateScreen(){

	if (endMap)
		return;

	if (GlobalHandler::player->rectDraw.left > SCREEN_WIDTH / 2)
	{
		GlobalHandler::screen.left = GlobalHandler::player->rectDraw.left - SCREEN_WIDTH / 2;
		GlobalHandler::screen.right = GlobalHandler::screen.left + SCREEN_WIDTH;
	}
	else // cai nay la de khi nao mario chet no set lai tu dau
	{
		GlobalHandler::screen.left = 0;
		GlobalHandler::screen.right = GlobalHandler::screen.left + SCREEN_WIDTH;
	}
}

void GlobalHandler::RestartMap()
{	
	GlobalHandler::screen.left		= 0;
	GlobalHandler::screen.top		= 0;
	GlobalHandler::screen.right		= SCREEN_WIDTH;
	GlobalHandler::screen.bottom	= SCREEN_HEIGHT;
	GlobalHandler::time = 300;
	GlobalHandler::endMap = false;

	GlobalHandler::listStaticObj.clear();
	GlobalHandler::listStaticObjCanCollide.clear();
	GlobalHandler::listStaticObjRender.clear();
	GlobalHandler::player = new Player();
	
	//GlobalHandler::quadTree->Reset();
	GlobalHandler::dynamicObjManager->Release();
	
	ListTerrain::InitTerrain(GlobalHandler::mapLevel);

	GlobalHandler::dynamicObjManager->GetTick();
	
	GlobalHandler::quadTree->ReadQuadTreeFormFile(GlobalHandler::mapLevel);
	GlobalHandler::quadTree->Deserialize();
	
	GlobalHandler::isStarted = true;
	GlobalHandler::sound->Play(ListSound::SOUND_BACKGROUND, true);
	GlobalHandler::InitText();
	trace(L"void GlobalHandler::RestartMap()");
}

LPWSTR GlobalHandler::ConvertChar(char c[200]){
	wchar_t wtext[200];
	mbstowcs(wtext, c, strlen(c)+1);//Plus null
	LPWSTR ptr = wtext;
	
	return ptr;
}

