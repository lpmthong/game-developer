#pragma once
#include "dsutil.h"
class ListSound
{
public:
	static CSound*	SOUND_STARTGAME;
	static CSound*	SOUND_BACKGROUND;
	static CSound*	SOUND_JUMP;
	static CSound*  SOUND_COIN;
	static CSound*	SOUND_BUMP;
	static CSound*	SOUND_BRICKBREAKED;
	static CSound*	SOUND_POWERUP;
	static CSound*	SOUND_BONUSRISE;
	static CSound*  SOUND_LIFE;
	static CSound*  SOUND_MIP;
	static CSound*  SOUND_KICK;
	static CSound*  SOUND_DEAD;
	static CSound*  SOUND_FIREBALL;
public:
	static void CreateAllSound();
	ListSound(void);
	~ListSound(void);
};
