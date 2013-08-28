#include "Option.h"
#include "GlobalHandler.h"
#include "ListTexture.h"
#include "Define.h"

Option::Option(void)
{
	sprite = new Sprite(ListTexture::TT_OPTION, SCREEN_WIDTH, SCREEN_HEIGHT, 1, 1);
}

Option::~Option(void)
{
	delete sprite;
}

void Option::Render()
{
	sprite->Render(GlobalHandler::directX->backbuffer, 0, 0);
}

void Option::OnKeyDown( int keyCode )
{
	if (keyCode == DIK_RETURN)
		GlobalHandler::gameState = GS_MENU;
}
