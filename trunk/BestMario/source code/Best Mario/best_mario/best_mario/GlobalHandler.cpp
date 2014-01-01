#include "GlobalHandler.h"
#include "ListTerrain.h"
#include "ListSound.h"
#include "BonusBrick.h"
#include "Define.h"
#include "Ground.h"

DirectX				*GlobalHandler::_directX			= new DirectX();
QuadTree			*GlobalHandler::quadTree			= new QuadTree();
DXSound				*GlobalHandler::sound				= new DXSound();
SaveGame			*GlobalHandler::save				= new SaveGame();

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
int					 GlobalHandler::mapWidth			= 0;
int					 GlobalHandler::mapLevel			= 1;
int					 GlobalHandler::nextMap				= 2;
bool				 GlobalHandler::endMap				= false;
int					 GlobalHandler::gameState			= GS_MENU;
Text				*GlobalHandler::text				;
int					 GlobalHandler::time				= 300;
DWORD				 GlobalHandler::lastTime			= GetTickCount();

int					 GlobalHandler::checkpoint[3][10];
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
	GlobalHandler::checkpoint_index = 0;
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

void GlobalHandler::SaveStaticObj(){
	
	list<StaticObject*>::iterator it;
	for (it = GlobalHandler::listStaticObj.begin(); it != GlobalHandler::listStaticObj.end(); it ++)
	{
		if ((*it)->isKind == BRICK_BONUS_COIN || (*it)->isKind == BRICK_BONUS_GUN || 
			(*it)->isKind == BRICK_BONUS_LIFE || (*it)->isKind == BRICK_BONUS_LIFE_HIDDEN || (*it)->isKind == BRICK_BONUS_MUSHROOM || 
			(*it)->isKind == BRICK_BONUS_STAR)
		{
			BonusBrick *bn = ((BonusBrick *)(*it));
			GlobalHandler::save->SaveText(L" %d %d %d %d %d\n", bn->id, bn->isKind, bn->rectDraw.left, bn->rectDraw.top, bn->isEmpty);
		}
		else if((*it)->isKind == GROUND)
		{
			Ground *g = ((Ground*)(*it));
			GlobalHandler::save->SaveText(L" %d %d %d %d\n", g->id, g->type, g->rectDraw.left, g->rectDraw.top);
		}
		else if ((*it)->isKind == ENDMAP)
		{
			GlobalHandler::save->SaveText(L" %d %d %d %d\n", (*it)->id, (*it)->isKind, (*it)->rectDraw.left, (*it)->rectDraw.top - ListTexture::TT_END_MAP_HEIGHT + 32);
		}
		else if ((*it)->id != 0)		
		{
			GlobalHandler::save->SaveText(L" %d %d %d %d\n", (*it)->id, (*it)->isKind, (*it)->rectDraw.left, (*it)->rectDraw.top);
		}
	}

	for (int i = 0; i < GlobalHandler::checkpoint_index; i++)
	{		
		GlobalHandler::save->SaveText(L" %d %d %d %d\n", GlobalHandler::checkpoint[2][i], CHECKPOINT, GlobalHandler::checkpoint[0][i], GlobalHandler::checkpoint[1][i]);
	}	
}