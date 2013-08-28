#include "Sprite.h"
#include "GlobalHandler.h"


Sprite::Sprite(void)
{
	distanceFromTop = 0;
}

Sprite::Sprite(LPD3DXSPRITE _spriteHandler, char *path, int** _iSmallPicture, int _count, int _spritePerRow)
{
	iSmallPicture = _iSmallPicture;
	count = _count;
	index = 0;
	spritePerRow = _spritePerRow;
	distanceFromTop = 0;

	InitTexture(_spriteHandler, path);
}

Sprite::Sprite(LPD3DXSPRITE _spriteHandler, char *path, int _width, int _height, int _count, int _spritePerRow)
{
	width = _width;
	height = _height;
	count = _count;
	spritePerRow = _spritePerRow;
	index = 0;
	distanceFromTop = 0;

	InitTexture(_spriteHandler, path);
}

Sprite::Sprite( LPDIRECT3DTEXTURE9 texture, int _width, int _height, int _count, int _spritePerRow )
{
	width = _width;
	height = _height;
	count = _count;
	spritePerRow = _spritePerRow;
	index = 0;
	distanceFromTop = 0;

	image = texture;
}

void Sprite::InitTexture(LPD3DXSPRITE _spriteHandler, char *path)
{
	D3DXIMAGE_INFO info;

	image = NULL;
	spriteHandler = _spriteHandler;

	D3DXGetImageInfoFromFile(path, &info);

	LPDIRECT3DDEVICE9 d3ddev;
	spriteHandler->GetDevice(&d3ddev);

	D3DXCreateTextureFromFileEx(d3ddev,
		path,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255,0,255),
		&info,
		NULL,
		&image);
}

Sprite::~Sprite(void)
{
}
//
//void Sprite::Render(LPDIRECT3DSURFACE9 target, int x, int y, int _index)
//{
//	index = _index;
//	Render(target, x, y);
//}

void Sprite::Render(LPDIRECT3DSURFACE9 target, int x, int y)
{
	RECT rect;
	rect = InitRenderRectNormal();
	GlobalHandler::directX->spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXVECTOR3 position((float)x, (float)y, 0);

	GlobalHandler::directX->spriteHandler->Draw(image,
		&rect,
		NULL,
		&position,
		D3DCOLOR_XRGB(255,255,255));

	GlobalHandler::directX->spriteHandler->End();
}


void Sprite::Render( LPDIRECT3DSURFACE9 target, int x, int y, int top )
{
	RECT rect;
	rect = InitRenderRectNormal();
	rect.bottom = rect.top + top;
	GlobalHandler::directX->spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXVECTOR3 position((float)x, (float)y, 0);

	GlobalHandler::directX->spriteHandler->Draw(image,
		&rect,
		NULL,
		&position,
		D3DCOLOR_XRGB(255,255,255));

	GlobalHandler::directX->spriteHandler->End();
}

void Sprite::Render( LPDIRECT3DSURFACE9 target, int x, int y, int srcLeft, int srcTop, int srcRight, int srcBottom )
{
	RECT rect;
	rect.left = srcLeft;
	rect.top = srcTop;
	rect.right = srcRight;
	rect.bottom = srcBottom;

	GlobalHandler::directX->spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXVECTOR3 position((float)x, (float)y, 0);

	GlobalHandler::directX->spriteHandler->Draw(image,
		&rect,
		NULL,
		&position,
		D3DCOLOR_XRGB(255,255,255));

	GlobalHandler::directX->spriteHandler->End();
}

RECT Sprite::InitRenderRect()
{
	RECT rect;
	try
	{
		rect.right = iSmallPicture[0][index];
		rect.bottom = iSmallPicture[1][index];
		rect.top = ((index < spritePerRow)?0:iSmallPicture[1][(((index / spritePerRow) - 1) * spritePerRow)]);
		rect.left = ((index % spritePerRow) == 0)?0:iSmallPicture[0][index - 1];
	}
	catch (int**)
	{
		rect = InitRenderRectNormal();
	}
	return rect;
}

void Sprite::Next()
{
	index = (index + count + 1) % count;
}

void Sprite::Next( int start, int end )
{
	if (index < start || index > end)
		index = start;
	else
		index = (index + (end - start + 1) + 1) % (end - start + 1) + start;
}

void Sprite::Reset()
{
	index = 0;
}//

void Sprite::Reset( LPDIRECT3DTEXTURE9 texture, int _width, int _height, int _count, int _spritePerRow )
{
	width = _width;
	height = _height;
	count = _count;
	spritePerRow = _spritePerRow;
	index = 0;

	image = texture;
}

// Init normal case rect.
RECT Sprite::InitRenderRectNormal(void)
{
	RECT rect;
	rect.top = (index / spritePerRow) * height + distanceFromTop;
	rect.left = (index % spritePerRow) * width;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;
	return rect;
}

void Sprite::setIndex( int i )
{
	index = i;
}

void Sprite::setIndex( int start, int end )
{
	if (index < start || index > end)
		index = start;
}

void Sprite::setTexture( LPDIRECT3DTEXTURE9 texture )
{
	image = texture;
}

void Sprite::setDistanceFromTop( int dis )
{
	distanceFromTop = dis;
}

int Sprite::getIndex()
{
	return index;
}

void Sprite::setWidthHeight( int w, int h )
{
	width = w;
	height = h;
}

int Sprite::getHeight()
{
	 return height;
}
