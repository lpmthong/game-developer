#include "ListTexture.h"

LPDIRECT3DTEXTURE9	ListTexture::TT_CLOUD = NULL;
int					ListTexture::TT_CLOUD_WIDTH;
int					ListTexture::TT_CLOUD_HEIGHT;
int					ListTexture::TT_CLOUD_COUNT;
int					ListTexture::TT_CLOUD_SPRITEPERROW;
int					ListTexture::TT_CLOUD_ANIMATED_RATE;

ListTexture::ListTexture(void){}

ListTexture::~ListTexture(void){}

void ListTexture::CreateAllTexture(){
	ListTexture::TT_CLOUD							= GlobalHandler::_directX->LoadTextureFormFile("Media\\cloud.bmp",0);
	ListTexture::TT_CLOUD_WIDTH						= 64;
	ListTexture::TT_CLOUD_HEIGHT					= 45;
	ListTexture::TT_CLOUD_COUNT						= 2;
	ListTexture::TT_CLOUD_SPRITEPERROW				= 2;
	ListTexture::TT_CLOUD_ANIMATED_RATE 			= 500;
}