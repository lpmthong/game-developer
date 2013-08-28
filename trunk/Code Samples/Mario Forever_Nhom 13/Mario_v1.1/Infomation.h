#include "d3d9.h"
#include "d3dx9.h"
#include "windows.h"

class Infomation
{
private:
	LPD3DXSPRITE sprite_Handler;
	LPDIRECT3DTEXTURE9 Info_Image;
public:
	int Score,CointCounter,Life;
	Infomation(LPD3DXSPRITE Sprite_Handler,LPDIRECT3DTEXTURE9 info_Image)
	{
		Score=CointCounter=0;
		Life=4;
		sprite_Handler=Sprite_Handler;
		Info_Image=info_Image;
	}
	void Draw()
	{
		sprite_Handler->Begin(D3DXSPRITE_ALPHABLEND);
		RECT r;
		//
		r.left=0;r.top=56;r.right=97;r.bottom=r.top+16;

		D3DXVECTOR3 des;
		des.x=des.y=10;des.z=0;
		sprite_Handler->Draw(Info_Image,&r,NULL,&des,D3DCOLOR_XRGB(255,255,255));
		DrawNumber(115,10,Life);
		DrawNumber(115,30,Score);
		//
		r.left=0;r.top=90;r.right=27;r.bottom=r.top+16;
		des.x=200;des.y=11,des.z=0;
		sprite_Handler->Draw(Info_Image,&r,NULL,&des,D3DCOLOR_XRGB(255,255,255));
		DrawNumber(250,10,CointCounter);
		sprite_Handler->End();
	}
private:
	void DrawNumber(int Right,int Top,int Number)
	{
		int number=Number;
		int Count=0;
		D3DXVECTOR3 des(Right,Top,0);
		if(number==0)
		{
			RECT r;
			r.left=0;r.right=r.left+15;
			r.top=73;r.bottom=r.top+16;
			sprite_Handler->Draw(Info_Image,&r,NULL,&des,D3DCOLOR_XRGB(255,255,255));
		}
		while(number>0)
		{
			int digit=number%10;
			RECT r;
			r.left=digit*15;r.right=r.left+15;
			r.top=73;r.bottom=r.top+16;
			des.x=Right-15*Count;des.y=Top,des.z=0;
			sprite_Handler->Draw(Info_Image,&r,NULL,&des,D3DCOLOR_XRGB(255,255,255));
			Count++;
			number=number/10;
		}
	}
};