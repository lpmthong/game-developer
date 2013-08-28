#include "Debug.h"

Debug::Debug(void)
{
}

Debug::~Debug(void)
{
	delete number;
}

void Debug::LoadResource(LPDIRECT3DDEVICE9 d3ddev)
{
	D3DXCreateSprite(d3ddev, &spriteHandler);
	d3ddev->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&backbuffer);
	
	number = new Sprite(spriteHandler, NUMBER_PATH, 50, 50, 10, 10);
}

void Debug::Render(int iNumber, int x, int y)
{
	FillArray(iNumber);
	for (int i = iIndex - 1; i >= 0; i--)
	{
		number->Render(backbuffer, x, y, aNumber[i]);
		x += 50;
	}
}

//Put all digit of a number to an array one by one.
void Debug::FillArray(int iNumber)
{
	iIndex = 0;
	int iTempNumber = iNumber;
	while (iTempNumber != 0)
	{
		aNumber[iIndex] = iTempNumber % 10;
		iIndex ++;
		iTempNumber = iTempNumber  / 10;
	}
}