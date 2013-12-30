#include "Text.h"
#include "ListTexture.h"
#include "GlobalHandler.h"


Text::Text()
{
	sprite	= new Sprite();
	width	= height = 0;
	
	life = new Score(0, 0);
	life->moving = false;

	time	= new Score(0, 0);
	time->moving = false;

	coin_count = new Score(0, 0);
	coin_count->moving = false;

	world = new Score(0, 0);
	world->moving = false;

	score = new Score(0, 0);
	score->moving = false;
}
Text::~Text()
{
	delete sprite;
	delete score;
}

void Text::Render()
{
	TextMario();
	TextCoinCount();
	TextWorld();
	TextTime();
	TextScore();
}

void Text::Update()
{
	UpdateRect(GlobalHandler::screen.left, GlobalHandler::screen.top);
}
void Text::TextMario()
{
	sprite->Reset(ListTexture::TT_MARIO_TEXT,ListTexture::TT_MARIO_TEXT_WIDTH, ListTexture::TT_MARIO_TEXT_HEIGHT, 1, 1);
	sprite->Render(GlobalHandler::_directX->_backBuffer, 30, 10);

	life->setScore(GlobalHandler::player->life);
	life->UpdateRect(GlobalHandler::screen.left + (ListTexture::TT_MARIO_TEXT_WIDTH + 20), 590);
	life->Render();	
}

void Text::TextScore()
{
	score->setScore(GlobalHandler::playerScore);
	score->UpdateRect(GlobalHandler::screen.left + 50, 565);
	score->Render();
}
void Text::TextCoinCount()
{
	sprite->Reset(ListTexture::TT_TEXT_COIN,ListTexture::TT_TEXT_COIN_WIDTH, ListTexture::TT_TEXT_COIN_HEIGHT, 1, 1);
	sprite->Render(GlobalHandler::_directX->_backBuffer, 250, 10);

	coin_count->setScore(GlobalHandler::playerCoin);
	coin_count->UpdateRect(GlobalHandler::screen.left + 270, 590);
	coin_count->Render();
}

void Text::TextWorld()
{
	sprite->Reset(ListTexture::TT_TEXT_WORLD,ListTexture::TT_TEXT_WORLD_WIDTH, ListTexture::TT_TEXT_WORLD_HEIGHT, 1, 1);
	sprite->Render(GlobalHandler::_directX->_backBuffer, 430, 10);

	world->setScore(GlobalHandler::mapLevel1);
	world->UpdateRect(GlobalHandler::screen.left + 425, 565);
	world->Render();

	world->RenderCross(GlobalHandler::screen.left +460, 565);

	world->setScore(GlobalHandler::mapLevel2);
	world->UpdateRect(GlobalHandler::screen.left + 465 , 565);
	world->Render();
}
void Text::TextTime()
{
	sprite->Reset(ListTexture::TT_TEXT_TIME, ListTexture::TT_TEXT_TIME_WIDTH, ListTexture::TT_TEXT_TIME_HEIGHT, 1, 1);
	sprite->Render(GlobalHandler::_directX->_backBuffer, 705, 10);

	time->setScore(GlobalHandler::time);
	time->UpdateRect(GlobalHandler::screen.left + 705, 565);
	time->Render();
}
