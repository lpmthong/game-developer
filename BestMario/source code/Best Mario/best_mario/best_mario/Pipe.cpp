#include "Pipe.h"
#include "ListTexture.h"
#include "Define.h"

Pipe::Pipe(void)
{
}

Pipe::Pipe( int left, int top, int type )
{
	isKind = type;

	if (isKind == PIPE_CAP)
		sprite = new Sprite(ListTexture::TT_PIPE_CAP,		
		ListTexture::TT_PIPE_CAP_WIDTH,		
		ListTexture::TT_PIPE_CAP_HEIGHT,		
		ListTexture::TT_PIPE_CAP_COUNT,	
		ListTexture::TT_PIPE_CAP_SPRITEPERROW);
	else
		sprite = new Sprite(ListTexture::TT_PIPE_BODY,		
		ListTexture::TT_PIPE_BODY_WIDTH,		
		ListTexture::TT_PIPE_BODY_HEIGHT,		
		ListTexture::TT_PIPE_BODY_COUNT,	
		ListTexture::TT_PIPE_BODY_SPRITEPERROW);

	width = ListTexture::TT_PIPE_BODY_WIDTH;
	height = ListTexture::TT_PIPE_BODY_HEIGHT;
	UpdateRect(left, top, ListTexture::TT_PIPE_BODY_WIDTH, ListTexture::TT_PIPE_BODY_HEIGHT);	

	map_level = 2;
	isSolid = true;
}

Pipe::~Pipe(void)
{
}
