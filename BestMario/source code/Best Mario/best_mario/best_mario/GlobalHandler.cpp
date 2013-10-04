#include "GlobalHandler.h"

DirectX				*GlobalHandler::_directX			= new DirectX();
QuadTree			*GlobalHandler::quadTree			= new QuadTree(MAP_WIDTH, MAP_WIDTH);
int		             GlobalHandler::backGroundColor		= BLUE;
bool	             GlobalHandler::quitGame			= false;

RECT	             GlobalHandler::screen;

GlobalHandler::GlobalHandler(void){}

GlobalHandler::~GlobalHandler(void){}