#include "Bonuses.h"

Bonuses::Bonuses(void)
{
}
Bonuses::Bonuses(int left,int top,LPD3DXSPRITE sprite_Handle,LPDIRECT3DTEXTURE9 *texture,QuadTree *q,int kind,SoundManager *sManager)
{
	IsActive=true;
	Kind=kind;
	ID=3;
	Layer=1;
	quadTree=q;
	OnMove=NULL;
	Rect=new RECT();
	upDown=NULL;
	Rect->left=left;Rect->bottom=top-1;
	soundManager=sManager;
	switch(Kind)//0_Coin,1_HealthMusroom,2_Flower,3_ExtralifeMusroom,or 4_Star
	{
	case 0://Coin
		Rect->right=Rect->left+31;
		Rect->top=top-30;
		Sprite=new Sprites(true,0,2,34,31,29,sprite_Handle,texture,left,top,0,150);
		break;
	case 1://
		OnMove=new Moving(false,20,20,2);
		Rect->right=Rect->left+30;
		Rect->top=top-34;
		Sprite=new Sprites(false,0,1,64,30,33,sprite_Handle,texture,left,top,1,0);
		break;
	case 2:
		Rect->right=Rect->left+33;
		Rect->top=top-34;
		Sprite=new Sprites(true,0,3,0,33,33,sprite_Handle,texture,left,top,0,150);
		break;
	case 3:
		OnMove=new Moving(false,20,20,2);
		Rect->right=Rect->left+31;
		Rect->top=top-34;
		Sprite=new Sprites(false,1,1,64,31,33,sprite_Handle,texture,left,top,0,0);
		break;
	case 4:
		OnMove=new Moving(false,10,10,1);
		Rect->right=Rect->left+32;
		Rect->top=top-34;
		Sprite=new Sprites(false,0,1,96,32,33,sprite_Handle,texture,left,top,0,0);
		break;
	case 5://Bar
		IsActive=false;
		upDown=new UpDown(5);
		OnMove=new Moving(false,10,10,0);
		Rect->right=Rect->left+44;
		Rect->top=top-16;
		Sprite=new Sprites(false,1,1,97,44,16,sprite_Handle,texture,left,top,0,0);
		break;
	}
	Level=0;
	JustChangeLevel=false;
	JustMove=false;
	Status=0;//Stand still
	Sequency=rand();
	screen=NULL;
}

void Bonuses::WriteToFile(FILE *f)
{
	if(Kind==5||Kind==0)
	{
		fwrite(&ID,sizeof(int),1,f);
		fwrite(&Rect->left,sizeof(long),1,f);
		fwrite(&Rect->bottom,sizeof(long),1,f);
		fwrite(&Kind,sizeof(int),1,f);
	}
}
int Bonuses::Move()
{
	int DeltaX=0;
	if(Kind!=0&&Kind!=2&&GetTickCount()-OnMove->OldTime>=OnMove->FrameTime)
	{
		DeltaX=CheckLeftRight();
		Rect->left+=DeltaX;
		Rect->right+=DeltaX;
		Sprite->Left+=DeltaX;
		OnMove->OldTime=GetTickCount();
		if(DeltaX==0)
			OnMove->IsLeft=!OnMove->IsLeft;
		if(DeltaX!=0&&Kind!=0&&Kind!=5&&Kind!=2&&Status!=1&&!quadTree->IsOnObject(Rect,Sequency))//Allways check
		{
			Status=1;//Jump
			upDown=new UpDown(2);//hut chan roi xuong
		}
		if(Status!=1&&Kind==5)//Bar
		{
			Status=1;
			upDown=new UpDown(5);
		}
	}
	Jump();
	return DeltaX;
}
void Bonuses::BeTouch(Object *Ob)
{
	if(Ob->ID==1&&Status!=2)
	{
		switch(Kind)
		{
		case 0://coin
			soundManager->Play("GetCoin",false);
			((Mario*)Ob)->infomation->Score+=200;
			((Mario*)Ob)->infomation->CointCounter++;
			if(((Mario*)Ob)->infomation->CointCounter==100)
			{
				((Mario*)Ob)->infomation->CointCounter=0;
				((Mario*)Ob)->infomation->Life++;
			}
			break;
		case 1://health
			((Mario*)Ob)->LevelChange(1);
			((Mario*)Ob)->infomation->Score+=1000;
			break;
		case 2://flower
			((Mario*)Ob)->LevelChange(1);
			((Mario*)Ob)->infomation->Score+=1500;
			break;
		case 3://extralife
			soundManager->Play("ExtraLife",false);
			((Mario*)Ob)->infomation->Life++;
			break;
		case 4://star
			soundManager->Play("ExtraLife",false);
			break;
		case 5://bar
			soundManager->Play("UpLevel",false);
			if(upDown!=NULL)
				((Mario*)Ob)->infomation->Score+=upDown->Index*100;
			break;
		}
		Sprite->TotalExistTime=1;
		Status=2;
		Rect->top=SCREEN_HEIGHT+10;
		Rect->bottom=Rect->top+50;
		//MessageBox(NULL,"","",MB_OK);
		//
	}
}
void Bonuses::Draw(int VirtualLeft,int Style)
{
	Sprite->Draw(VirtualLeft,0,true);
}
Bonuses::~Bonuses(void)
{
}
