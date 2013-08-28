#include "Sprites.h"
#include "windows.h"

Sprites::Sprites(bool loop,int index,int count,int row,int width,int height,
	LPD3DXSPRITE spr_Handle,LPDIRECT3DTEXTURE9 *tex,int left,int top,int totalExistTime,int interval)
{
	Loop=loop;
	Index=index;
	Count=count;
	Row=row;
	Clear=true;
	Width=width;
	Height=height;
	Alpha=255;
	sprite_Handle=spr_Handle;
	texture=tex;
	Left=left;
	Top=top-Height;
	RootTime=OldTime=GetTickCount();
	TotalExistTime=totalExistTime;
	Interval=interval;
	Enable=true;
}
void Sprites::Draw(int VirtualLeft,int StyleDraw,bool isClear)
{
	if(texture!=NULL)
	{
		if((DWORD)Interval!=0&&GetTickCount()-OldTime>=(DWORD)Interval)
		{
			if(!isClear&&GetTickCount()-RootTime<=TotalExistTime)
				Clear=!Clear;
			else
				Clear=true;
			if(Enable)
			{
				switch(StyleDraw)
				{
				case -1://Giam do alpha cho toi 0
					Alpha-=10;
					if(Alpha<0)
						Alpha=0;
					break;
				case 0://ve binh thuong
					if(Loop)
					{
						Index=(Index+1)%Count;
					}
					else
					{
						Index++;
						if(Index==Count)
						{					
							Index=0;
							Enable=false;
						}
					}
					break;
				}
			}
			OldTime=GetTickCount();
		}
		sprite_Handle->Begin(D3DXSPRITE_ALPHABLEND);
		D3DXVECTOR3 des((float)(Left-VirtualLeft),(float)Top,0);
		sprite_Handle->Draw(*texture,&GetSRect(),NULL,&des,D3DCOLOR_ARGB(Clear?Alpha:100,255,255,255));
		sprite_Handle->End();
	}
}
RECT Sprites::GetSRect()
{
	RECT r;
	r.left=Index*Width;r.top=Row;
	r.bottom=r.top+Height;
	r.right=r.left+Width;
	return r;
}
Sprites::~Sprites(void)
{
}
