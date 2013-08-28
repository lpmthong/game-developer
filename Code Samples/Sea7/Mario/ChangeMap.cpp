#include "ChangeMap.h"
#include "ListTexture.h"
#include "Define.h"
#include <dinput.h>
#include "GlobalHandler.h"
#include "ListSound.h"

ChangeMap::ChangeMap(void)
{
	sprite = new Sprite();
}

ChangeMap::~ChangeMap(void)
{
	delete sprite;
}

void ChangeMap::Render()
{
	sprite->Reset(ListTexture::TT_CHANGE_MAP, SCREEN_WIDTH, SCREEN_HEIGHT, 1, 1);
	sprite->Render(GlobalHandler::directX->backbuffer, 0, 0);

	sprite->Reset(ListTexture::TT_WORLD, ListTexture::TT_WORLD_WIDTH, ListTexture::TT_WORLD_HEIGHT, 1, 1);
	sprite->Render(GlobalHandler::directX->backbuffer, SCREEN_WIDTH / 2 - ListTexture::TT_WORLD_WIDTH / 2, SCREEN_HEIGHT / 2 - ListTexture::TT_WORLD_HEIGHT / 2);

	sprite->Reset(ListTexture::TT_WORLD_NUMBER, ListTexture::TT_WORLD_NUMBER_WIDTH, ListTexture::TT_WORLD_NUMBER_HEIGHT, ListTexture::TT_WORLD_NUMBER_COUNT, ListTexture::TT_WORLD_NUMBER_SPRITEPERROW);
	sprite->setIndex(GlobalHandler::mapLevel - 1);
	sprite->Render(GlobalHandler::directX->backbuffer, SCREEN_WIDTH / 2 - ListTexture::TT_WORLD_NUMBER_WIDTH / 2, 360);
}

void ChangeMap::OnKeyDown( int keyCode )
{
	if (keyCode == DIK_RETURN)
	{
		GlobalHandler::RestartMap();
		GlobalHandler::gameState = GS_GAMEPLAY;
	}
}
