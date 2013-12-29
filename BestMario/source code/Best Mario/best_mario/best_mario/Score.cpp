#include "Score.h"
#include "ListTexture.h"
#include "GlobalHandler.h"

Score::Score(void)
{
}

Score::Score(int left, int top)
{
	sprite = new Sprite(ListTexture::TT_TEXT_NUMBER,ListTexture::TT_TEXT_NUMBER_WIDTH,ListTexture::TT_TEXT_NUMBER_HEIGHT,ListTexture::TT_TEXT_NUMBER_COUNT,ListTexture::TT_TEXT_NUMBER_PRITEPERROW);
	width  = ListTexture::TT_TEXT_NUMBER_WIDTH;
	height = ListTexture::TT_TEXT_NUMBER_HEIGHT;
	UpdateRect(left,top-ListTexture::TT_TEXT_NUMBER_HEIGHT, ListTexture::TT_TEXT_NUMBER_WIDTH,ListTexture::TT_TEXT_NUMBER_HEIGHT);
	arrScoreIndex = 0;

	distanceMoving = 0;
	moving = true;
}

Score::~Score(void)
{
}
void Score::setScore(int score)
{
	if(moving==true)
	{
		GlobalHandler::playerScore +=score;
	}
	arrScoreIndex = 0;
	if(score<=0)
	{
		arrScore[arrScoreIndex++]=0;
		return;
	}
	while (score!=0)
	{
		arrScore[arrScoreIndex++] =score%10;
		score = score/10;
	}
}
void Score::Render()
{
	for(int i = arrScoreIndex - 1; i >= 0; i--)
	{
		sprite->setIndex(arrScore[i]);
		RECT screen = GlobalHandler::screen;
		sprite->Render(GlobalHandler::_directX->_backBuffer,rectDraw.left-screen.left+(arrScoreIndex-i)*15,rectDraw.top-screen.top);
	}
}

void Score::Update()
{
	if(!moving)
		return;

	distanceMoving +=2;
	UpdateRect(rectDraw.left, rectDraw.top-2);
	if (distanceMoving>50)
		alive = INHELL;
}
void Score::RenderCross( int left, int top )
{
	sprite->setIndex(10);

	RECT screen = GlobalHandler::screen;
	sprite->Render(GlobalHandler::_directX->_backBuffer, left - screen.left, top - screen.top);	
}
