#pragma once
#include "DynamicObject.h"
#include "Score.h"

class Text : public DynamicObject
{
	public :

	Text();
	~Text();
	Score *time;
	Score *coin_count;
	Score *life;
	Score *score;
	Score *world;


	void Render();
	void Update();

	void TextMario();
	void TextScore();
	void TextCoinCount();
	void TextWorld();
	void TextTime();
	void TextGameOver();
};