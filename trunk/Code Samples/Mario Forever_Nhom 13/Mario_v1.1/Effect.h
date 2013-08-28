#include "Sprites.h"
#include "d3d9.h"
#include "d3dx9.h"

class Effect
{
public:
	Sprites *sprite;	
	int Kind;//Loai hieu ung nao: 0_No,1_Coin
	Effect(int left,int top,int kind,LPD3DXSPRITE sprite_Handle,LPDIRECT3DTEXTURE9 *texture)
	{
		Kind=kind;
		switch(Kind)
		{
		case 0:
			sprite=new Sprites(false,0,6,64,32,32,sprite_Handle,texture,left,top,120,20);
			break;
		case 1:
			sprite=new Sprites(false,1,1,96,32,32,sprite_Handle,texture,left,top,250,10);
			break;
		}
	}
};