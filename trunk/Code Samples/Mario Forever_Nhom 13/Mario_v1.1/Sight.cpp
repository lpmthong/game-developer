#include "Sight.h"

Sight::Sight(void)
{
}
Sight::Sight(int left, int top, int kind, bool visible, LPD3DXSPRITE sprite_Handle, 
			 LPDIRECT3DTEXTURE9 *texture, QuadTree *q)
{
	ID=-1;
	Layer=0;
	quadTree=q;
	Rect->left=left;
	Rect->top=top;
	Kind=kind;
	Visible=visible;
	IsActive=true;
	Sequency=rand();
	Status=0;
	switch(Kind)
	{
	case 0://May
		Rect->bottom=top+48;
		Rect->right=Rect->left+64;
		Sprite=new Sprites(true,0,2,0,64,48,sprite_Handle,texture,Rect->left,Rect->bottom,0,150);
		break;
	case 1://Hang rao
		Rect->right=Rect->left+142;
		Rect->bottom=Rect->top+33;
		Sprite=new Sprites(false,0,1,48,142,33,sprite_Handle,texture,Rect->left,Rect->bottom,0,0);
		break;
	case 2://Co
		Rect->right=Rect->left+64;
		Rect->bottom=Rect->top+32;
		Sprite=new Sprites(true,0,2,80,64,32,sprite_Handle,texture,Rect->left,Rect->bottom,0,150);
		break;
	case 3://Cay to
		Rect->right=Rect->left+32;
		Rect->bottom=Rect->top+92;
		Sprite=new Sprites(false,0,1,112,32,92,sprite_Handle,texture,Rect->left,Rect->bottom,0,50);
		break;
	case 4://Cay nho
		Rect->right=Rect->left+28;
		Rect->bottom=Rect->top+60;
		Sprite=new Sprites(false,2,1,112,28,60,sprite_Handle,texture,Rect->left,Rect->bottom,0,0);
		break;
	case 5://Nui
		Rect->right=Rect->left+310;
		Rect->bottom=Rect->top+128;
		Sprite=new Sprites(false,0,1,251,310,128,sprite_Handle,texture,Rect->left,Rect->bottom,0,0);
		break;
	case 6://Mui ten
		Rect->right=Rect->left+32;
		Rect->bottom=Rect->top+33;
		Sprite=new Sprites(false,0,1,203,32,33,sprite_Handle,texture,Rect->left,Rect->bottom,0,0);
		break;
	case 7://Cot mo
		Rect->right=Rect->left+31;
		Rect->bottom=Rect->top+288;
		Sprite=new Sprites(false,11,1,0,31,288,sprite_Handle,texture,Rect->left,Rect->bottom,0,0);
		break;
	case 8://Cot binh thuong
		Layer=2;
		Rect->right=Rect->left+31;
		Rect->bottom=Rect->top+288;
		Sprite=new Sprites(false,12,1,0,31,288,sprite_Handle,texture,Rect->left,Rect->bottom,0,0);
		break;
	}
}

void Sight::WriteToFile(FILE *f)
{
	fwrite(&ID,sizeof(int),1,f);
	fwrite(&Rect->left,sizeof(long),1,f);
	fwrite(&Rect->top,sizeof(long),1,f);
	fwrite(&Kind,sizeof(int),1,f);
}
void Sight::Draw(int VirtualLeft,int Style)
{
	Sprite->Draw(VirtualLeft,0,true);
}
int Sight::Move()
{
	return 0;
}
void Sight::BeTouch(Object *Ob)
{
}
Sight::~Sight(void)
{
}
