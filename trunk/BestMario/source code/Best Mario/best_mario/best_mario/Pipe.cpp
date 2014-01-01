#include "Pipe.h"
#include "ListTexture.h"
#include "Define.h"

Pipe::Pipe(void)
{
}

Pipe::Pipe( int left, int top, int type, int iid)
{
	isKind = type;

	switch(isKind)
	{
		case PIPE_1:
			sprite = new Sprite(ListTexture::TT_PIPE_1,		
				ListTexture::TT_PIPE_1_WIDTH,		
				ListTexture::TT_PIPE_1_HEIGHT,		
				ListTexture::TT_PIPE_1_COUNT,	
				ListTexture::TT_PIPE_1_SPRITEPERROW);
			width = ListTexture::TT_PIPE_1_WIDTH;
			height = ListTexture::TT_PIPE_1_HEIGHT;
			UpdateRect(left, top, ListTexture::TT_PIPE_1_WIDTH, ListTexture::TT_PIPE_1_HEIGHT);
			break;
		case PIPE_2:
			sprite = new Sprite(ListTexture::TT_PIPE_2,		
				ListTexture::TT_PIPE_2_WIDTH,		
				ListTexture::TT_PIPE_2_HEIGHT,		
				ListTexture::TT_PIPE_2_COUNT,	
				ListTexture::TT_PIPE_2_SPRITEPERROW);
			width = ListTexture::TT_PIPE_2_WIDTH;
			height = ListTexture::TT_PIPE_2_HEIGHT;
			UpdateRect(left, top, ListTexture::TT_PIPE_2_WIDTH, ListTexture::TT_PIPE_2_HEIGHT);
			break;
		case PIPE_3:
			sprite = new Sprite(ListTexture::TT_PIPE_3,		
				ListTexture::TT_PIPE_3_WIDTH,		
				ListTexture::TT_PIPE_3_HEIGHT,		
				ListTexture::TT_PIPE_3_COUNT,	
				ListTexture::TT_PIPE_3_SPRITEPERROW);
			width = ListTexture::TT_PIPE_3_WIDTH;
			height = ListTexture::TT_PIPE_3_HEIGHT;
			UpdateRect(left, top, ListTexture::TT_PIPE_3_WIDTH, ListTexture::TT_PIPE_3_HEIGHT);
			break;
		case PIPE_4:
			sprite = new Sprite(ListTexture::TT_PIPE_4,		
				ListTexture::TT_PIPE_4_WIDTH,		
				ListTexture::TT_PIPE_4_HEIGHT,		
				ListTexture::TT_PIPE_4_COUNT,	
				ListTexture::TT_PIPE_4_SPRITEPERROW);
			width = ListTexture::TT_PIPE_4_WIDTH;
			height = ListTexture::TT_PIPE_4_HEIGHT;
			UpdateRect(left, top, ListTexture::TT_PIPE_4_WIDTH, ListTexture::TT_PIPE_4_HEIGHT);
			break;
		case PIPE_5:
			sprite = new Sprite(ListTexture::TT_PIPE_5,		
				ListTexture::TT_PIPE_5_WIDTH,		
				ListTexture::TT_PIPE_5_HEIGHT,		
				ListTexture::TT_PIPE_5_COUNT,	
				ListTexture::TT_PIPE_5_SPRITEPERROW);
			width = ListTexture::TT_PIPE_5_WIDTH;
			height = ListTexture::TT_PIPE_5_HEIGHT;
			UpdateRect(left, top, ListTexture::TT_PIPE_5_WIDTH, ListTexture::TT_PIPE_5_HEIGHT);
			break;		
	}
	
	id = iid;
	map_level = 2;
	isSolid = true;
}

Pipe::~Pipe(void)
{
}
