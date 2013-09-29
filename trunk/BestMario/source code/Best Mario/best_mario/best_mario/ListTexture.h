#pragma once
#include "GlobalHandler.h"

class ListTexture{
public:
	static LPDIRECT3DTEXTURE9	TT_CLOUD;
	static int					TT_CLOUD_WIDTH;
	static int					TT_CLOUD_HEIGHT;
	static int					TT_CLOUD_COUNT;
	static int					TT_CLOUD_SPRITEPERROW;
	static int					TT_CLOUD_ANIMATED_RATE;
public:
	static void CreateAllTexture();
	ListTexture(void);
	~ListTexture(void);
};
