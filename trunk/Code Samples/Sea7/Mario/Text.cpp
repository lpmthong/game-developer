#include "Text.h"
#include "ListTexture.h"
#include "GlobalHandler.h"
#include "trace.h"

Text::Text(void)
{
	sprite = new Sprite();
	width = height = 0;

	time = new Score(0, 0);
	time->moving = false;

	score = new Score(0, 0);
	score->moving = false;

	life = new Score(0, 0);
	life->moving = false;

	coinCount = new Score(0, 0);
	coinCount->moving = false;

	mapLV = new Score(0, 0);
	mapLV->moving = false;

	gameOver = false;

	debugPlayerLeft = new Score(0, 0);
	debugPlayerLeft->moving = false;
}

Text::~Text(void)
{
	delete time;
	delete sprite;
	//delete score;
	delete life;
	delete coinCount;
	delete mapLV;
	delete debugPlayerLeft;
}

void Text::Render()
{
	RenderMario();
	RenderTime();
	RenderWorld();
	RenderCoinCount();
	RenderScore();
	
	debugPlayer();

	if (gameOver)
		RenderGameOver();
}

void Text::RenderMario()
{
	sprite->Reset(ListTexture::TT_MARIO_TEXT, ListTexture::TT_MARIO_TEXT_WIDTH, ListTexture::TT_MARIO_TEXT_HEIGHT, 1, 1);
	sprite->Render(GlobalHandler::directX->backbuffer, 50, 20);
	life->setScore(GlobalHandler::player->life);
	life->UpdateRect(GlobalHandler::screen.left + 131, 20);
	life->Render();
}

void Text::RenderGameOver()
{
	sprite->Reset(ListTexture::TT_GAMEOVER_TEXT, ListTexture::TT_GAMEOVER_TEXT_WIDTH, ListTexture::TT_GAMEOVER_TEXT_HEIGHT, 1, 1);
	sprite->Render(GlobalHandler::directX->backbuffer, SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT / 2);
}

void Text::RenderTime()
{
	sprite->Reset(ListTexture::TT_TIME_TEXT, ListTexture::TT_TIME_TEXT_WIDTH, ListTexture::TT_TIME_TEXT_HEIGHT, 1, 1);
	sprite->Render(GlobalHandler::directX->backbuffer, 700, 20);

	time->setScore(GlobalHandler::levelTime);
	time->UpdateRect(GlobalHandler::screen.left + 700, 45);
	time->Render();
}

void Text::RenderWorld()
{
	sprite->Reset(ListTexture::TT_WORLD_TEXT, ListTexture::TT_WORLD_TEXT_WIDTH, ListTexture::TT_WORLD_TEXT_HEIGHT, 1, 1);
	sprite->Render(GlobalHandler::directX->backbuffer, 500, 20);

	mapLV->setScore(GlobalHandler::mapLevel1);
	mapLV->UpdateRect(GlobalHandler::screen.left + 500, 45);
	mapLV->Render();

	mapLV->RenderCross(GlobalHandler::screen.left + 535, 45);

	mapLV->setScore(GlobalHandler::mapLevel2);
	mapLV->UpdateRect(GlobalHandler::screen.left + 540, GlobalHandler::screen.top + 45);
	mapLV->Render();
}

void Text::Update()
{
	UpdateRect(GlobalHandler::screen.left, GlobalHandler::screen.top);
}

void Text::RenderCoinCount()
{
	sprite->Reset(ListTexture::TT_COIN_COUNT, ListTexture::TT_COIN_COUNT_WIDTH, ListTexture::TT_COIN_COUNT_HEIGHT, 1, 1);
	sprite->Render(GlobalHandler::directX->backbuffer, 300, 20);

	coinCount->setScore(GlobalHandler::playerCoin);
	coinCount->UpdateRect(GlobalHandler::screen.left + 320, GlobalHandler::screen.top + 20);
	coinCount->Render();
}

void Text::RenderScore()
{
	score->setScore(GlobalHandler::playerScore);
	score->UpdateRect(GlobalHandler::screen.left + 50, 45);
	score->Render();
}

void Text::debugPlayer()
{
	debugPlayerLeft->setScore(GlobalHandler::player->recDrawArea.left);
	debugPlayerLeft->UpdateRect(GlobalHandler::screen.left + 131, 70);
	debugPlayerLeft->Render();
}
