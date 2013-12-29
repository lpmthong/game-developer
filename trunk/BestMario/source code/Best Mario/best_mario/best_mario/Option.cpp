#include "Option.h"
#include "ListTexture.h"
#include "GlobalHandler.h"

Option::Option(void)
{
	option = new Sprite(ListTexture::TT_OPTION,SCREEN_WIDTH,SCREEN_HEIGHT,1,1);
}


Option::~Option(void)
{
}
void Option::Render()
{
	option->Render(GlobalHandler::_directX->_backBuffer,0,0);
}

void Option::OnKeyDown(int keyCode)
{
	
		if(keyCode==DIK_RETURN)
			GlobalHandler::gameState = GS_MENU;
	
}