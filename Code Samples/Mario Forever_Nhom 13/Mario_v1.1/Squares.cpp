#include "Squares.h"

Squares::Squares(int left,int top,int width,int height,int kind,bool visible,
				 LPD3DXSPRITE sprite_Handle,LPDIRECT3DTEXTURE9 *texture,LPDIRECT3DTEXTURE9 *texture1,int secret,Effect** ef,QuadTree *q,SoundManager *sManager)
{
	ID=0;
	Layer=1;
	effect=ef;
	Bonus_Texture=texture1;
	quadTree=q;
	Rect->left=left;Rect->top=top;
	Rect->right=Rect->left+width;
	Rect->bottom=Rect->top+height;
	if(kind==0)
	{
		Rect->left=left+2;
		Rect->right=left+width-4;
	}
	Secret=secret;
	Kind=kind;
	Visible=visible;
	IsActive=true;
	Sequency=rand();
	Status=0;//Normal
	soundManager=sManager;
	switch(Kind)
	{
	case 0://Mat dat		
	case 4://Cot
		Sprite=new Sprites(true,3,0,0,width,height,sprite_Handle,texture,left,Rect->bottom,0,0);
		CountCoin=0;
		break;
	case 5://Vat can hinh vuong
		Sprite=new Sprites(true,1,1,0,32,32,sprite_Handle,texture,Rect->left,Rect->bottom,0,0);
		CountCoin=0;
		break;
	case 3://gach co nhieu coin
		CountCoin=10;
		Sprite=new Sprites(true,0,1,0,32,32,sprite_Handle,texture,Rect->left,Rect->bottom,0,50);
		break;
	case 1://gach
		CountCoin=0;
		Sprite=new Sprites(true,0,1,0,32,32,sprite_Handle,texture,Rect->left,Rect->bottom,0,0);
		break;
	case 2://dau cham hoi
		if(Secret==0)
			CountCoin=1;
		else
			CountCoin=0;
		Sprite=new Sprites(true,0,2,32,32,32,sprite_Handle,texture,Rect->left,Rect->bottom,0,300);
		break;
	}
}
void Squares::WriteToFile(FILE *f)
{
	fwrite(&ID,sizeof(int),1,f);
	fwrite(&Rect->left,sizeof(long),1,f);
	fwrite(&Rect->top,sizeof(long),1,f);
	fwrite(&Sprite->Width,sizeof(int),1,f);
	fwrite(&Sprite->Height,sizeof(int),1,f);
	fwrite(&Secret,sizeof(int),1,f);
	fwrite(&Kind,sizeof(int),1,f);
}
void Squares::BeTouch(Object *b)
{
	if(b->ID==1)//Chi co Mario co quyen lay Items
	{
		Object *Ob=NULL;
		switch(Kind)
		{
		case 1://gach thuong
			if(((Mario*)b)->Level!=0)
			{
				for(int i=0;i<10;i++)
				{
					if(effect[i]==NULL)
					{
						effect[i]=new Effect(Rect->left,Rect->top+32,0,Sprite->sprite_Handle,Sprite->texture);
						soundManager->Play("BrickBroken",false);
						break;
					}
				}
				Sprite->TotalExistTime=1;
				Status=2;
			}
			break;
		case 2://gach dau cham hoi
			Sprite->Count=0;
			Sprite->Index=0;
			Sprite->Row=96;
			Sprite->Interval=0;
			for(int i=0;i<10,Secret==0;i++)//Coin
			{
				if(effect[i]==NULL)
				{
					effect[i]=new Effect(Rect->left+2,Rect->top-16,1,Sprite->sprite_Handle,Sprite->texture);
					break;
				}
			}
			switch(Secret)//0_Coin,1_HealthMusroom_Flower,2_ExtralifeMusroom,or 3_Star
			{
			case 0:
				((Mario*)b)->infomation->CointCounter++;
				((Mario*)b)->infomation->Score+=200;
				if(((Mario*)b)->infomation->CointCounter==100)
				{
					((Mario*)b)->infomation->CointCounter=0;
					((Mario*)b)->infomation->Life++;
				}
				soundManager->Play("GetCoin",false);
				break;
			case 1://
				soundManager->Play("BonusAppear_LevelDown",false);
				if(((Mario*)b)->Level==0)
				{
					Ob=new Bonuses(Rect->left,Rect->top,Sprite->sprite_Handle,Bonus_Texture,quadTree,1,soundManager);//tang mau
					quadTree->Add(quadTree->Root,Ob);
				}
				else
				{
					Ob=new Bonuses(Rect->left,Rect->top,Sprite->sprite_Handle,Bonus_Texture,quadTree,2,soundManager);//Flower
					quadTree->Add(quadTree->Root,Ob);
				}
				break;
			case 2:
				soundManager->Play("BonusAppear_LevelDown",false);
				Ob=new Bonuses(Rect->left,Rect->top,Sprite->sprite_Handle,Bonus_Texture,quadTree,3,soundManager);//
				quadTree->Add(quadTree->Root,Ob);
				break;
			case 3:
				soundManager->Play("BonusAppear_LevelDown",false);
				Ob=new Bonuses(Rect->left,Rect->top,Sprite->sprite_Handle,Bonus_Texture,quadTree,4,soundManager);//
				quadTree->Add(quadTree->Root,Ob);
				break;
			}
			Secret=-1;
			break;
		case 3://gach co nhieu coin
			CountCoin--;
			if(CountCoin<0)
			{
				Sprite->Index=0;
				Sprite->Row=96;
				Sprite->Interval=0;
			}
			else
			{
				soundManager->Play("GetCoin",false);
				((Mario*)b)->infomation->CointCounter++;
				((Mario*)b)->infomation->Score+=200;
				for(int i=0;i<10;i++)//Coin
				{
					if(effect[i]==NULL)
					{
						effect[i]=new Effect(Rect->left+2,Rect->top-16,1,Sprite->sprite_Handle,Sprite->texture);
						Secret=-1;
						break;
					}
				}
			}
			break;
		}
	}
}
void Squares::Draw(int VirtualLeft,int Style)
{
	D3DXVECTOR3 des;
	switch(Kind)
	{
	case 1://gach thuong
	case 2://gach dau cham hoi
	case 3://gach co nhieu coin		
	case 4://Cot		
	case 5://Vat can vuong
		Sprite->Draw(VirtualLeft,0,true);
		break;
	case 0://Land,nothing happens, kich thuoc tot nhat la: (W-18)%32
		Sprite->sprite_Handle->Begin(D3DXSPRITE_ALPHABLEND);
		RECT sr;

		sr.left=64;sr.top=0;sr.bottom=Rect->bottom-Rect->top;sr.right=sr.left+9;
		des.x=Sprite->Left-VirtualLeft;des.y=Rect->top;des.z=0;
		Sprite->sprite_Handle->Draw(*Sprite->texture,&sr,NULL,&des,D3DCOLOR_XRGB(255,255,255));

		sr.left=107;sr.top=0;sr.bottom=Rect->bottom-Rect->top;sr.right=sr.left+9;
		des.x=Rect->right-7-VirtualLeft;des.y=Rect->top;des.z=0;
		Sprite->sprite_Handle->Draw(*Sprite->texture,&sr,NULL,&des,D3DCOLOR_XRGB(255,255,255));

		int x=Rect->left+7;
		sr.left=74;sr.top=0;sr.bottom=Rect->bottom-Rect->top;sr.right=sr.left+32;
		for(int i=0;i<=(Rect->right-Rect->left-14)/32;i++)
		{
			des.x=x-VirtualLeft;des.y=Rect->top;des.z=0;
			Sprite->sprite_Handle->Draw(*Sprite->texture,&sr,NULL,&des,D3DCOLOR_XRGB(255,255,255));
			x+=32;
		}
		Sprite->sprite_Handle->End();
		break;
	}
}
int Squares::Move()
{
	return 0;
}
/*bool Squares::operator == (Squares sq)
{
	if(R.left!=sq.R.left||R.top!=sq.R.top||R.right!=sq.R.right||R.bottom!=sq.R.bottom)
		return false;//khong bang
	return true;//bang
}
void Squares::operator =(Squares sq)
{
	this->CountCoin=sq.CountCoin;
	this->Kind=sq.Kind;
	this->R.left=sq.R.left;this->R.right=sq.R.right;this->R.top=sq.R.top;this->R.bottom=sq.R.bottom;
	this->Secret=sq.Secret;
	this->Sprite=sq.Sprite;
	this->Visible=sq.Visible;
}*/
Squares::~Squares(void)
{
}
