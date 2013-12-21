#pragma once
#include "dsutil.h"

class DXSound
{
private:
	CSoundManager*	m_pSoundManager;

public:
	DXSound(void);
	~DXSound(void);

public:
	BOOL	Init(HWND);
	CSound* LoadSound(char *lpszFileName);
	void	Play(CSound* wave, bool bLooped);
	void	Stop(CSound*);

	void	End();

};

