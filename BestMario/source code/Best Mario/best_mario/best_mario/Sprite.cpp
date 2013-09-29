#include "Sprite.h"
#include "GlobalHandler.h"

Sprite::Sprite(void){}

Sprite::Sprite(LPDIRECT3DTEXTURE9 texture, int width, int height, int count, int spritePerRow){
	_texture		 = texture;
	_width			 = width;
	_height			 = height;
	_count			 = count;
	_spritePerRow	 = spritePerRow;
	_index			 = 0;
	_distanceFromTop = 1;
}

Sprite::~Sprite(void){
	_texture->Release();
}

void Sprite::Next(){
	_index = (_index + _count - 1) % _count;
}

void Sprite::Next(int start, int end){

}

void Sprite::Reset(){
	_index = 0;
}

void Sprite::setIndex(int i){
	_index = i;
}

int Sprite::getIndex(){
	return _index;
}

void Sprite::setDistanceFromTop(int d){
	_distanceFromTop = d;
}

RECT Sprite::InitRenderRect(){
	RECT srect;
	srect.left = (_index % _spritePerRow)* _width + 1;
	srect.top = (_index / _spritePerRow)* _height + _distanceFromTop;
	srect.right = srect.left + _width ;
	srect.bottom = srect.top + _height +1;
	return srect;
}

void Sprite::Render(float x, float y){
	RECT renderRect = InitRenderRect();
	D3DXVECTOR3 position(x, y, 0);
	GlobalHandler::_directX->_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	GlobalHandler::_directX->_spriteHandler->Draw(
		_texture,
		&renderRect,
		NULL,
		&position,
		D3DCOLOR_XRGB(255,255,255)
	);

	GlobalHandler::_directX->_spriteHandler->End();
}

void Sprite::Render(LPDIRECT3DSURFACE9 target, int x, int y)
{
	RECT rect;
	rect = InitRenderRect();
	GlobalHandler::_directX->_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXVECTOR3 position((float)x, (float)y, 0);

	GlobalHandler::_directX->_spriteHandler->Draw(_texture,
		&rect,
		NULL,
		&position,
		D3DCOLOR_XRGB(255,255,255));

	GlobalHandler::_directX->_spriteHandler->End();
}


void Sprite::Render( LPDIRECT3DSURFACE9 target, int x, int y, int top )
{
	RECT rect;
	rect = InitRenderRect();
	rect.bottom = rect.top + top;
	GlobalHandler::_directX->_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXVECTOR3 position((float)x, (float)y, 0);

	GlobalHandler::_directX->_spriteHandler->Draw(_texture,
		&rect,
		NULL,
		&position,
		D3DCOLOR_XRGB(255,255,255));

	GlobalHandler::_directX->_spriteHandler->End();
}

void Sprite::Render( LPDIRECT3DSURFACE9 target, int x, int y, int srcLeft, int srcTop, int srcRight, int srcBottom )
{
	RECT rect;
	rect.left = srcLeft;
	rect.top = srcTop;
	rect.right = srcRight;
	rect.bottom = srcBottom;

	GlobalHandler::_directX->_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXVECTOR3 position((float)x, (float)y, 0);

	GlobalHandler::_directX->_spriteHandler->Draw(_texture,
		&rect,
		NULL,
		&position,
		D3DCOLOR_XRGB(255,255,255));

	GlobalHandler::_directX->_spriteHandler->End();
}
