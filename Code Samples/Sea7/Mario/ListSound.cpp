#include "ListSound.h"
#include "GlobalHandler.h"

CSound* ListSound::SOUND_STARTGAME		=	NULL;
CSound* ListSound::SOUND_BACKGROUND		=	NULL;
CSound* ListSound::SOUND_JUMP			=	NULL;
CSound*	ListSound::SOUND_COIN			=	NULL;
CSound*	ListSound::SOUND_BUMP			=	NULL;
CSound* ListSound::SOUND_BRICKBREAKED	=	NULL;
CSound* ListSound::SOUND_POWERUP		=	NULL;
CSound*	ListSound::SOUND_BONUSRISE		=	NULL;
CSound* ListSound::SOUND_LIFE			=	NULL;
CSound* ListSound::SOUND_MIP			=	NULL;
CSound* ListSound::SOUND_KICK			=	NULL;
CSound* ListSound::SOUND_DEAD			=	NULL;
CSound* ListSound::SOUND_FIREBALL		=	NULL;


void ListSound::CreateAllSound()
{
	ListSound::SOUND_STARTGAME		=	GlobalHandler::sound->LoadSound("Sounds\\StartGame.wav");
	ListSound::SOUND_BACKGROUND		=	GlobalHandler::sound->LoadSound("Sounds\\Background.wav");
	ListSound::SOUND_JUMP			=	GlobalHandler::sound->LoadSound("Sounds\\Jump.wav");
	ListSound::SOUND_COIN			=	GlobalHandler::sound->LoadSound("Sounds\\Coin.wav");
	ListSound::SOUND_BUMP			=	GlobalHandler::sound->LoadSound("Sounds\\Bump.wav");
	ListSound::SOUND_BRICKBREAKED	=	GlobalHandler::sound->LoadSound("Sounds\\BrickBreaked.wav");
	ListSound::SOUND_POWERUP		=	GlobalHandler::sound->LoadSound("Sounds\\PowerUp.wav");
	ListSound::SOUND_BONUSRISE		=	GlobalHandler::sound->LoadSound("Sounds\\BonusRise.wav");
	ListSound::SOUND_LIFE			=	GlobalHandler::sound->LoadSound("Sounds\\Life.wav");
	ListSound::SOUND_MIP			=	GlobalHandler::sound->LoadSound("Sounds\\mip.wav");
	ListSound::SOUND_KICK			=	GlobalHandler::sound->LoadSound("Sounds\\kick.wav");
	ListSound::SOUND_DEAD			=	GlobalHandler::sound->LoadSound("Sounds\\death.wav");
	ListSound::SOUND_FIREBALL		=	GlobalHandler::sound->LoadSound("Sounds\\fireball.wav");
}

ListSound::ListSound(void)
{
}

ListSound::~ListSound(void)
{
}
