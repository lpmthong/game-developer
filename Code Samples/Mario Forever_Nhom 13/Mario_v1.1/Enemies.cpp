#include "Enemies.h"

Enemies::Enemies(int left,int top,int width,int height,MyScreen *sc,
				 LPD3DXSPRITE sprite_Handle,LPDIRECT3DTEXTURE9 *texture,QuadTree *q,int kind,SoundManager *sManager)
{
	ID=2;//
	Layer=2;
	Kind=kind;
	quadTree=q;
	Rect=new RECT();
	Rect->left=left;Rect->right=left+width;
	Rect->top=top;Rect->bottom=top+height;
	IsActive=false;//Dau tien thi bien nay co gia tri la false.
	upDown=NULL;
	Level=0;//nho_to_ban dc
	JustChangeLevel=false;
	JustMove=false;
	screen=sc;
	soundManager=sManager;
	bool r=(rand()%2==0?false:true);
	switch(Kind)
	{
	case 0://Nam 30_31
		OnMove=new Moving(r,10,10,1);
		Sprite=new Sprites(true,0,2,0,width,height,sprite_Handle,texture,left,Rect->bottom,0,160);
		break;
	case 1://Rua 32_47
		OnMove=new Moving(r,15,5,1);
		Sprite=new Sprites(true,0,2,(!OnMove->IsLeft?32:79),width,height,sprite_Handle,texture,left,Rect->bottom,0,160);
		break;
	}
	Status=0;//Stand on the floor
	//1_fall down; 2_lie down; 3_lie down and move
	bulletManager=NULL;
	Sequency=rand();
}
void Enemies::WriteToFile(FILE *f)
{
	//if(Rect->top>TOP_LAND-170)
	{
		fwrite(&ID,sizeof(int),1,f);
		fwrite(&Rect->left,sizeof(long),1,f);
		fwrite(&Rect->top,sizeof(long),1,f);
		fwrite(&Sprite->Width,sizeof(int),1,f);
		fwrite(&Sprite->Height,sizeof(int),1,f);
		fwrite(&Kind,sizeof(int),1,f);
	}
}
void Enemies::Draw(int VirtualLeft,int Style)
{
	Sprite->Draw(VirtualLeft,0,true);
}
int Enemies::Move()
{
	int DeltaX=0;
	if(IsActive&&GetTickCount()-OnMove->OldTime>=OnMove->FrameTime&&Status!=2)//'s not died yet.
	{
		DeltaX=CheckLeftRight();
		Rect->left+=DeltaX;
		Rect->right+=DeltaX;
		Sprite->Left+=DeltaX;
		OnMove->OldTime=GetTickCount();
		if(DeltaX==0)
			ChangeDim();
		if((Status==0||Status==-1)&&!quadTree->IsOnObject(Rect,Sequency))//Allways check
		{
			Status=1;//Jump
			upDown=new UpDown(2);//hut chan roi xuong
		}
	}
	Jump();
	Die();
	return DeltaX;
}
void Enemies::ChangeDim()
{
	OnMove->IsLeft=!OnMove->IsLeft;
	if(Kind==1&&Status!=-1)
		if(OnMove->IsLeft)
		{
			Sprite->Row+=Sprite->Height+2;
		}
		else
		{
			Sprite->Row-=Sprite->Height+2;
		}
}
void Enemies::ChangeStatus(int style)//bi dap hay bi ban
{
	switch(Status)
	{
	case -1://Turtle move fast.
		OnMove->FrameTime=OnMove->HFrameTime;
		Sprite->Width=34;
		Sprite->Height=30;
		Sprite->Row=126;
		Sprite->Index=0;
		Sprite->Count=3;Sprite->Interval=100;
		break;
	case 2://die (^_^)
		if(Kind==0)//Musroom
		{
			if(style==0)//bi dap
			{
				Sprite->Interval=0;
				Sprite->Index=3;
				Sprite->RootTime=GetTickCount();
				Sprite->TotalExistTime=5000;//Time to remove
			}
			else if(style==1)//bi ban
			{
				Sprite->Interval=0;
				Sprite->Index=2;
				upDown=new UpDown(1);
			}
			IsActive=false;
		}
		else if(Kind==1)//Turtle
		{
			if(style==1)//bi ban
			{
				Sprite->Interval=0;
				Sprite->Row=126;
				Sprite->Index=1;
				upDown=new UpDown(1);
			}
		}
		break;
	}
}
void Enemies::BeTouch(Object *Ob)
{
	if(Ob->ID==1)
	{
		if(Ob->Status==1&&!Ob->upDown->IsUp&&Status!=2)
		{
			Ob->Rect->top-=25;
			Ob->Rect->bottom-=25;
			Ob->Sprite->Top-=25;
			Ob->upDown->SpeedDown=50;
			if(Kind==0)
				Status=2;
			else if(Kind==1)//Turtle
			{
				if(Status==0)
				{
					Status=-1;
					Sprite->Top+=15;
					Rect->top+=15;
				}
			}
			ChangeStatus(0);//Bi dap
			soundManager->Play("EnemyDie",false);
			((Mario*)Ob)->infomation->Score+=100;
		}
		else if((Ob->Status==0&&!((Mario*)Ob)->JustChangeLevel)||(Ob->Status==1&&Ob->upDown->IsUp&&!((Mario*)Ob)->JustChangeLevel))
		{
			((Mario*)Ob)->LevelChange(-1);
		}
	}
	else if((Ob->Status==-1&&Ob->ID==2)||Ob->ID==4)//
	{
		if(Ob->ID==4)
		{
			((Mario*)Ob)->infomation->Score+=100;
			for(int i=0;i<10;i++)
			{
				if(((Bullet*)Ob)->effect[i]==NULL)
				{
					((Bullet*)Ob)->effect[i]=new Effect(((Bullet*)Ob)->Rect->left,((Bullet*)Ob)->Rect->top+32,0,((Bullet*)Ob)->Sprite->sprite_Handle,((Bullet*)Ob)->Sprite->texture);
					break;
				}
			}
			((Bullet*)Ob)->bulletManager->BulletCounter--;
			if(((Bullet*)Ob)->bulletManager->BulletCounter<0)
				((Bullet*)Ob)->bulletManager->BulletCounter=0;
			Ob->Status=2;
		}
		Status=2;
		ChangeStatus(1);//Bi ban
	}
}
Enemies::~Enemies(void)
{
}
