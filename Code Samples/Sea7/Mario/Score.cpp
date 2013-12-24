#include "Score.h"
#include "ListTexture.h"
#include "GlobalHandler.h"
#include "trace.h"

Score::Score(void)
{
}

Score::Score( int left, int top )
{
	sprite = new Sprite(ListTexture::TT_NUMBER,				
						ListTexture::TT_NUMBER_WIDTH,
						ListTexture::TT_NUMBER_HEIGHT,		
						ListTexture::TT_NUMBER_COUNT,		
						ListTexture::TT_NUMBER_SPRITEPERROW);

	width = ListTexture::TT_NUMBER_WIDTH;
	height = ListTexture::TT_NUMBER_HEIGHT;
	UpdateRect(left, top - ListTexture::TT_NUMBER_HEIGHT, ListTexture::TT_NUMBER_WIDTH, ListTexture::TT_NUMBER_HEIGHT);
	
	isSolid = false;

	arrScoreIndex = 0;
	distanceMoving = 0;

	moving = true;
}

Score::~Score(void)
{
}

void Score::setScore( int score )
{
	//Update score in player.
/*	if (moving == true)
	{
		GlobalHandler::playerScore += score;
//		trace(L"new score %d", GlobalHandler::player->score);
	}
	*/
	arrScoreIndex = 0;
	
	if (score <= 0)
	{
		arrScore[arrScoreIndex++] = 0;
		return;
	}
	while (score != 0)
	{
		arrScore[arrScoreIndex++] = score % 10;
		score = score / 10;
	}

}

void Score::Render()
{
	for (int i = arrScoreIndex - 1; i >= 0; i--)
	{
		sprite->setIndex(arrScore[i]);

		RECT screen = GlobalHandler::screen;
		sprite->Render(GlobalHandler::directX->backbuffer, recDrawArea.left - screen.left + (arrScoreIndex - i)*15, recDrawArea.top - screen.top);
	}
}

void Score::Update()
{
	if (!moving)
		return;

	distanceMoving += 3;
	UpdateRect(recDrawArea.left, recDrawArea.top - 3);

	if (distanceMoving > 50)
		alive = INHELL;
}

void Score::RenderCross( int left, int top )
{
	sprite->setIndex(10);

	RECT screen = GlobalHandler::screen;
	sprite->Render(GlobalHandler::directX->backbuffer, left - screen.left, top - screen.top);	
}
