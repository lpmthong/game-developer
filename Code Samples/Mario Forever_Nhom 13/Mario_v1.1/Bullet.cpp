#include "Bullet.h"

Bullet::Bullet(void)
{
}
Bullet::Bullet(BulletManager *bulletManager,bool isLeft,int left, int top,
			   LPD3DXSPRITE sprite_Handle, LPDIRECT3DTEXTURE9 *texture, Effect **ef, QuadTree *q,MyScreen *scr,Infomation *info)
{
	ID=4;
	Layer=1;
	this->bulletManager=bulletManager;
	effect=ef;
	quadTree=q;
	Rect->left=left;Rect->top=top;
	Rect->right=Rect->left+17;
	Rect->bottom=Rect->top+17;
	Kind=0;
	IsActive=true;
	Sequency=rand();
	Status=1;//Jumb
	Sprite=new Sprites(true,0,4,128,17,17,sprite_Handle,texture,left,top+17,120,150);
	OnMove=new Moving(isLeft,10,10,4);
	upDown=new UpDown(2);//Hut chan roi xuong
	screen=scr;
	infomation=info;
}
void Bullet::Draw(int VirtualLeft, int Style)
{
	Sprite->Draw(VirtualLeft,0,true);
}
int Bullet::Move()
{
	int DeltaX=0;
	if(IsActive&&GetTickCount()-OnMove->OldTime>=OnMove->FrameTime&&Status!=2)//'s not died yet.
	{
		DeltaX=CheckLeftRight();
		Rect->left+=DeltaX;
		Rect->right+=DeltaX;
		Sprite->Left+=DeltaX;
		if(DeltaX==0||Rect->top>SCREEN_HEIGHT)//Blow
		{
			for(int i=0;i<10;i++)
			{
				if(effect[i]==NULL)
				{
					effect[i]=new Effect((OnMove->IsLeft?Rect->left-10:Rect->left+10),Rect->top+32,0,Sprite->sprite_Handle,Sprite->texture);
					break;
				}
			}
			bulletManager->BulletCounter--;
			if(bulletManager->BulletCounter<0)
				bulletManager->BulletCounter=0;
			Status=2;
			Rect->top=SCREEN_HEIGHT+10;
			Rect->bottom=Rect->top+50;
			return 0;
		}
		OnMove->OldTime=GetTickCount();
		if(Status==0)
		{
			Status=1;
			upDown=new UpDown(4);
		}
	}
	Jump();
	return DeltaX;
}
void Bullet::BeTouch(Object *Ob)
{
}
Bullet::~Bullet(void)
{
}
