#include "GlobalHandler.h"

DirectX *GlobalHandler::_directX			= new DirectX();

int		 GlobalHandler::backGroundColor		= BLUE;
bool	 GlobalHandler::quitGame			= false;

RECT	 GlobalHandler::screen;

GlobalHandler::GlobalHandler(void){}

GlobalHandler::~GlobalHandler(void){}