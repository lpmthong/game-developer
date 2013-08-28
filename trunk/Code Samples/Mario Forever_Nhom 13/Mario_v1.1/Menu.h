#include "d3d9.h"
#include "d3dx9.h"
#include "windows.h"

class Menu
{
private:
	LPD3DXSPRITE sprite_Handler;
	LPDIRECT3DTEXTURE9 *Info_Image;
	HWND hwnd;
	int *Status;//
public:
	int TotalMenuItem;
	int Seq;//0_Start, 1_Quit
	bool IsKeyUp;
	Menu(int totalMenuItem,LPD3DXSPRITE sprite_handler,LPDIRECT3DTEXTURE9 *info_Image,int *status,HWND hWnd)
	{
		Seq=0;
		Status=status;
		hwnd=hWnd;
		sprite_Handler=NULL;
		sprite_Handler=sprite_handler;
		Info_Image=info_Image;
		TotalMenuItem=totalMenuItem;
		IsKeyUp=true;
	}
	void Accept()//PressEnter
	{
		switch(Seq)
		{
		case 0://
			*Status=1;
			break;
		case 1://
			DestroyWindow(hwnd);
			break;
		}
	}
	void Draw()
	{
		RECT source;
		D3DXVECTOR3 des;
		switch(Seq)
		{
		case 0://Start
			source.left=0;source.right=99;
			source.top=0;source.bottom=28;
			des.x=454;des.y=241,des.z=0;
			sprite_Handler->Draw(*Info_Image,&source,NULL,&des,D3DCOLOR_XRGB(255,255,255));
			break;
		case 1://Quit
			source.left=0;source.right=99;
			source.top=28;source.bottom=55;
			des.x=454;des.y=270;des.z=0;
			sprite_Handler->Draw(*Info_Image,&source,NULL,&des,D3DCOLOR_XRGB(255,255,255));
			break;
		}
	}
};