#include "Mario.h"
#include "Definition.h"

Mario::Mario(int left,LPD3DXSPRITE sprite_Handle,LPDIRECT3DTEXTURE9 *texture,
			 MyScreen *scr,QuadTree *q,Infomation *info,SoundManager *sManager)
{
	ID=1;
	Layer=1;
	IsActive=true;
	Kind=0;
	quadTree=q;
	infomation=info;
	Rect=new RECT();
	Rect->left=left+7;Rect->right=left+26;
	Rect->top=TOP_LAND-33;Rect->bottom=TOP_LAND-1;
	Sprite=new Sprites(false,0,2,0,33,32,sprite_Handle,texture,left,TOP_LAND-1,5000,90);
	Sprite->Enable=false;
	upDown=NULL;
	Level=0;//nho_to_ban dc
	JustChangeLevel=true;
	JustMove=false;
	screen=scr;
	OnMove=new Moving(false,10,8,2);
	Status=0;//Stand still
	bulletManager=new BulletManager(2,300);
	Sequency=rand();
	//
	soundManager=sManager;
	//LevelChange(1);LevelChange(1);
}
void Mario::WriteToFile(FILE *f)
{
	
}
void Mario::ChangeDim(bool IsJump)
{
	switch(Status)
	{
	case 0://Dung yen
		Sprite->Index=0;
		break;
	case 1://Nhay
		if(Level==0)
			Sprite->Index=2;
		else
			Sprite->Index=3;
		break;
	case 2:
		Sprite->Width=33;
		Sprite->Index=3;
		Sprite->Row=0;
		Sprite->Interval=0;
		break;
	}
	if(!IsJump)
		if(OnMove->IsLeft)
			Sprite->Row+=Sprite->Height;
		else
			Sprite->Row-=Sprite->Height;
}
void Mario::LevelChange(int Increase)
{
	if((Level<2&&Increase>0)||(Level>=0&&Increase<0))
		Level+=Increase;
	if(Increase>0)
		soundManager->Play("UpLevel",false);
	else
	{
		if(Level>=0)
			soundManager->Play("BonusAppear_LevelDown",false);
		else
		{
			soundManager->Play("Dying",false);
			Status=2;
			upDown=new UpDown(1);
			ChangeDim(true);
		}
	}
	switch(Level)
	{
	case 0:
		if(upDown==NULL)
			Sprite->Index=0;
		else
			Sprite->Index=2;
		if(OnMove->IsLeft)
		{
			Sprite->Row=32;
		}
		else
		{
			Sprite->Row=0;
		}
		Sprite->Count=2;
		Sprite->Width=Sprite->Height=32;
		Sprite->Top+=28;
		Rect->top+=28;
		break;
	case 1:
		//Sprite->Row=66;
		if(upDown==NULL)
			Sprite->Index=0;
		else
			Sprite->Index=3;
		if(OnMove->IsLeft)
		{
			Sprite->Row=126;
		}
		else
		{
			Sprite->Row=66;
		}
		Sprite->Count=3;
		Sprite->Width=33;
		Sprite->Height=60;
		if(Increase==1)
		{
			Sprite->Top-=28;
			Rect->top-=28;
		}
		break;
	case 2:
		if(upDown==NULL)
			Sprite->Index=0;
		else
			Sprite->Index=3;
		if(OnMove->IsLeft)
		{
			Sprite->Row=248;
		}
		else
		{
			Sprite->Row=188;
		}
		Sprite->Count=3;
		Sprite->Width=33;
		Sprite->Height=60;
		break;
	}
	JustChangeLevel=true;
	Sprite->RootTime=GetTickCount();
}
void Mario::Jump()
{
	if(upDown!=NULL&&Status==1&&GetTickCount()-upDown->OldTime>=(upDown->IsUp?upDown->SpeedUp:upDown->SpeedDown))//UpDown
	{
		if(upDown->IsUp)
		{
			upDown->Index--;
			upDown->Index=CheckUpDown(true);
			Sprite->Top-=upDown->Index;
			Rect->top-=upDown->Index;
			Rect->bottom-=upDown->Index;
		}
		else
		{
			if(upDown->Index<10)
				upDown->Index++;
			upDown->Index=CheckUpDown(false);
			Sprite->Top+=upDown->Index;
			Rect->top+=upDown->Index;
			Rect->bottom+=upDown->Index;
			if(Sprite->Top>=SCREEN_HEIGHT||upDown->Index==0)
			{
				if(upDown->Index==0)
				{
					Status=0;
					upDown=NULL;
					if(OnMove!=NULL)
						OnMove->FrameTime=OnMove->NFrameTime;
					if(ID==1)
						ChangeDim(true);
				}
				else
				{
					Status=2;
					if(ID==1)
					{
						upDown=new UpDown(1);
						Sprite->Top-=10;
						Rect->top-=10;
						Rect->bottom-=10;
						ChangeDim(true);
						soundManager->Play("Dying",false);
					}
									}
				return;
			}
		}
		if(upDown->Index<=0)
		{
			upDown->IsUp=false;
		}
		upDown->OldTime=GetTickCount();
	}
}

void Mario::Die()
{
	if(upDown!=NULL&&Status==2&&GetTickCount()-upDown->OldTime>=(upDown->IsUp?upDown->SpeedUp:upDown->SpeedDown))//Died
	{
		if(upDown->IsUp)
		{
			upDown->Index--;
			Sprite->Top-=upDown->Index;
			Rect->top-=upDown->Index;
			Rect->bottom-=upDown->Index;
		}
		else
		{
			upDown->Index++;
			Sprite->Top+=upDown->Index;
			Rect->top+=upDown->Index;
			Rect->bottom+=upDown->Index;
			if(Sprite->Top>=SCREEN_HEIGHT)
			{
				upDown=NULL;
				return;
			}
		}
		if(upDown->Index<=0)//+1>=(!upDown->IsSupper?upDown->JumpHeight:upDown->JumpHeight+5))
			upDown->IsUp=false;
		upDown->OldTime=GetTickCount();;
	}
}
int Mario::Move()
{
	if(GetTickCount()-OnMove->OldTime>=OnMove->FrameTime&&Status!=2)//'s not died yet.
	{
		int DeltaX=CheckLeftRight();
		if(Sprite->Left>=0&&Sprite->Left-screen->Rect.left>=SCREEN_WIDTH/2-20
			&&Sprite->Left-screen->Rect.left<=SCREEN_WIDTH/2+20
			&&screen->Rect.right<=screen->LimRight&&screen->Rect.left>=0)
		{
			screen->Rect.left+=DeltaX;
			screen->Rect.right+=DeltaX;
		}
		if(screen->Rect.left<0)
		{
			screen->Rect.left=0;
			screen->Rect.right=SCREEN_WIDTH;
		}
		else if(screen->Rect.right>screen->LimRight)
		{
			screen->Rect.right=screen->LimRight;
			screen->Rect.left=screen->LimRight-SCREEN_WIDTH;
		}
		Rect->left+=DeltaX;
		Rect->right+=DeltaX;
		Sprite->Left+=DeltaX;
		OnMove->OldTime=GetTickCount();
		return DeltaX;
	}
	return 0;
}
void Mario::Draw(int VirtualLeft, int Style)
{
	//Do nothing
}
void Mario::BeTouch(Object *Ob)
{
	Ob->BeTouch(this);
}
int Mario::CheckLeftRight()
{
	float x;
	x=(GetTickCount()-OnMove->OldTime)/(float)OnMove->FrameTime*OnMove->Step;
	if(x==0)
		return 0;
	x=(!OnMove->IsLeft?x:-x);
	RECT r;
	r.left=Rect->left+x;
	r.right=Rect->right+x;
	r.top=Rect->top;
	r.bottom=Rect->bottom;
	Object *ob=NULL;
	Object *o=NULL;
	while((o=quadTree->CheckCollision(quadTree->Root,r,Sequency))!=NULL
		||(screen!=NULL&&(r.left<screen->LimLeft||r.right>screen->LimRight)))//neu dung do voi cac object khac
	{
		if(o!=NULL)
		{
			ob=o;						
			if((o->ID==3&&ID==1)||(o->ID==3&&ID==2)||(o->ID==2&&ID==3)
				||(o->ID==2&&ID==2&&Status==-1)||(ID==2&&ob->ID==1)||(ID==3&&ob->ID==3)
				||(o->ID==3&&ID==4)||(o->ID==4&&ID==3))
				break;
		}
		if(!OnMove->IsLeft)
		{
			x--;
			r.left--;
			r.right--;
		}
		else
		{
			x++;
			r.left++;
			r.right++;
		}
		if(x==0)
		{
			break;
		}
	}
	if(ob!=NULL&&ob->ID!=0)
		ob->BeTouch(this);
	if(x!=0)
		JustMove=true;
	return x;
}
int Mario::CheckUpDown(bool IsUp)
{
	int y=(upDown!=NULL?upDown->Index:0);
	int z=y=(IsUp?-y:y);
	if(upDown!=NULL)
	{
		RECT r;
		r.left=Rect->left;
		r.right=Rect->right;
		r.top=Rect->top+y;
		r.bottom=Rect->bottom+y;
		Object *ob=NULL;
		Object *o=NULL;
		while((o=quadTree->CheckCollision(quadTree->Root,r,Sequency))!=NULL)//neu dung do voi cac object khac
		{
			if(o!=NULL)
			{
				ob=o;				
				if((o->ID==3&&ID==1)||(o->ID==3&&ID==2)||(o->ID==2&&ID==3)
					||(ID==1&&ob->ID==2&&upDown!=NULL&&upDown->IsUp)||(o->ID==3&&ID==4)||(o->ID==4&&ID==3))
					break;
			}
			if(!IsUp)
			{
				y--;
				r.top--;
				r.bottom--;
			}
			else
			{
				y++;
				r.top++;
				r.bottom++;
			}
			if(y==0)
			{						
				break;
			}
		}
		if(ob!=NULL)
		{
			if(ob->ID==0)
			{
				if(upDown->IsUp)
					ob->BeTouch(this);
			}
			else
				ob->BeTouch(this);
		}
	}
	if(y!=0)
		JustMove=true;
	return (y<0?-y:y);
}
Mario::~Mario(void)
{
}
