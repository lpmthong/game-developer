#include "d3d9.h"
#include "d3dx9.h"
#include "Definition.h"
#include "Time.h"
#include "Sprites.h"
#include "MyArrayList.h"
#include "io.h"
#include "iostream"
#include "Squares.h"
#include "Enemies.h"
#include "Bonuses.h"
#include "Bullet.h"
#include "Sight.h"
#include "windows.h"

class MapManager
{
public:
	SoundManager *soundManager;
	QuadTree *quadTree;
	LPD3DXSPRITE sprite_handler;
	LPDIRECT3DTEXTURE9 *BackGround_Image;
	LPDIRECT3DTEXTURE9 *Mario_Image;
	LPDIRECT3DTEXTURE9 *Squares_Image;
	LPDIRECT3DTEXTURE9 *Enemies_Image;
	LPDIRECT3DTEXTURE9 *Bonuses_Image;
	LPDIRECT3DTEXTURE9 *Sight_Image;
	Effect **effect;
	MyScreen *myScreen;

	int MapSeq;//Hien tai dang o man nao?

	MapManager(LPD3DXSPRITE sprite_Handler,LPDIRECT3DTEXTURE9 *backGround_Image,
		LPDIRECT3DTEXTURE9 *mario_Image,LPDIRECT3DTEXTURE9 *squares_Image,LPDIRECT3DTEXTURE9 *enemies_Image,
		LPDIRECT3DTEXTURE9 *bonuses_Image,LPDIRECT3DTEXTURE9 *sight_Image,Effect **ef,SoundManager *sManager)
	{
		MapSeq=1;
		sprite_handler=sprite_Handler;
		BackGround_Image=backGround_Image;
		Mario_Image=mario_Image;
		Squares_Image=squares_Image;
		Enemies_Image=enemies_Image;
		Bonuses_Image=bonuses_Image;
		Sight_Image=sight_Image;
		effect=ef;
		soundManager=sManager;

		LoadMap();//Map 1
		//InitMap();
	}	
	void LoadMap()
	{
		char *filename=NULL;
		switch(MapSeq)
		{
		case 1://Map 1
			filename="Maps\\Map1.mar";					
			break;
		case 2://Map 2, tu tu rui lam (^_^)
			filename="Maps\\Map2.mar";	
			break;
		}
		if(filename!=NULL)
			ReadFromFile(filename);
	}
private:
	void InitMap()
	{
		quadTree=new QuadTree(4678,480);
		RECT Camera;
		Camera.left=0;
		Camera.top=0;
		Camera.right=Camera.left+SCREEN_WIDTH;
		Camera.bottom=SCREEN_HEIGHT;
		myScreen=new MyScreen(0,4678,SCREEN_HEIGHT,&Camera);

		Object *Try=NULL;
		//32 x A + 18

		/*
		Try=new Squares(0,TOP_LAND,210,64,0,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Sight(50,TOP_LAND-25,2,true,sprite_handler,Sight_Image,quadTree);
		quadTree->Add(quadTree->Root,Try);
//
		Try=new Squares(178,TOP_LAND-32,32,32,5,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
//
		Try=new Squares(306,TOP_LAND-32,32,32,5,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
//
		Try=new Squares(434,TOP_LAND-32,32,32,5,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
//
		Try=new Squares(562,TOP_LAND-96,32,32,5,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Squares(562,TOP_LAND-64,32,32,5,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Squares(562,TOP_LAND-32,32,32,5,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Squares(562,TOP_LAND-128,32,32,5,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Squares(594,TOP_LAND-128,32,32,2,true,sprite_handler,Squares_Image,Bonuses_Image,1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Squares(562,TOP_LAND,690,64,0,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Sight(1000,TOP_LAND-25,2,true,sprite_handler,Sight_Image,quadTree);
		quadTree->Add(quadTree->Root,Try);

		Try=new Squares(1220,TOP_LAND-32,32,32,5,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);

		Try=new Squares(800,TOP_LAND-200,306,32,0,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Sight(850,TOP_LAND-60,4,true,sprite_handler,Sight_Image,quadTree);
		quadTree->Add(quadTree->Root,Try);
		
		Try=new Enemies(900,TOP_LAND-235,31,31,myScreen,sprite_handler,Enemies_Image,quadTree,0,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Enemies(1000,TOP_LAND-235,31,31,myScreen,sprite_handler,Enemies_Image,quadTree,0,soundManager);
		quadTree->Add(quadTree->Root,Try);

		Try=new Enemies(700,TOP_LAND-46,31,45,myScreen,sprite_handler,Enemies_Image,quadTree,1,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Enemies(1000,TOP_LAND-46,31,45,myScreen,sprite_handler,Enemies_Image,quadTree,1,soundManager);
		quadTree->Add(quadTree->Root,Try);

		Try=new Bonuses(809,TOP_LAND-295,sprite_handler,Bonuses_Image,quadTree,0,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Bonuses(841,TOP_LAND-295,sprite_handler,Bonuses_Image,quadTree,0,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Bonuses(1033,TOP_LAND-295,sprite_handler,Bonuses_Image,quadTree,0,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Bonuses(1065,TOP_LAND-295,sprite_handler,Bonuses_Image,quadTree,0,soundManager);
		quadTree->Add(quadTree->Root,Try);
		int x=873;
		for(int i=0;i<5;i++)
		{
			Try=new Squares(x,TOP_LAND-328,30,32,2,true,sprite_handler,Squares_Image,Bonuses_Image,0,effect,quadTree,soundManager);
			quadTree->Add(quadTree->Root,Try);
			x+=32;
		}
		
		
//
		Try=new Bonuses(1358,TOP_LAND-160,sprite_handler,Bonuses_Image,quadTree,0,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Bonuses(1390,TOP_LAND-160,sprite_handler,Bonuses_Image,quadTree,0,soundManager);
		quadTree->Add(quadTree->Root,Try);

		Try=new Squares(1500,TOP_LAND,658,64,0,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);

		Try=new Sight(1700,TOP_LAND-25,2,true,sprite_handler,Sight_Image,quadTree);
		quadTree->Add(quadTree->Root,Try);

		Try=new Squares(1600,TOP_LAND-128,32,32,1,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Squares(1632,TOP_LAND-128,32,32,2,true,sprite_handler,Squares_Image,Bonuses_Image,0,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Squares(1664,TOP_LAND-128,32,32,1,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Squares(1696,TOP_LAND-128,32,32,3,true,sprite_handler,Squares_Image,Bonuses_Image,0,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Squares(1728,TOP_LAND-128,32,32,1,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Squares(2092,TOP_LAND-128,64,128,4,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);

		Try=new Squares(1900,TOP_LAND-256,32,32,1,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Squares(1932,TOP_LAND-256,32,32,1,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Squares(1964,TOP_LAND-256,32,32,1,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Squares(1996,TOP_LAND-256,32,32,1,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);

		Try=new Bonuses(1932,TOP_LAND-352,sprite_handler,Bonuses_Image,quadTree,0,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Bonuses(1964,TOP_LAND-352,sprite_handler,Bonuses_Image,quadTree,0,soundManager);
		quadTree->Add(quadTree->Root,Try);

		Try=new Enemies(1964,TOP_LAND-300,31,45,myScreen,sprite_handler,Enemies_Image,quadTree,1,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Enemies(1964,TOP_LAND-32,31,31,myScreen,sprite_handler,Enemies_Image,quadTree,0,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Enemies(1700,TOP_LAND-160,31,31,myScreen,sprite_handler,Enemies_Image,quadTree,0,soundManager);
		quadTree->Add(quadTree->Root,Try);
//
		Try=new Squares(2400,TOP_LAND-128,32,32,5,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
//
		Try=new Squares(2700,TOP_LAND-32,32,32,5,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Squares(2732,TOP_LAND-64,32,32,5,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Squares(2764,TOP_LAND-96,32,32,5,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Squares(2796,TOP_LAND-128,32,32,5,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Squares(2828,TOP_LAND-160,32,32,5,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);

		Try=new Squares(2700,TOP_LAND,464,64,0,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);

		Try=new Enemies(2800,TOP_LAND-50,31,45,myScreen,sprite_handler,Enemies_Image,quadTree,1,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Enemies(2900,TOP_LAND-35,31,31,myScreen,sprite_handler,Enemies_Image,quadTree,0,soundManager);
		quadTree->Add(quadTree->Root,Try);

		Try=new Squares(2900,TOP_LAND-128,30,32,2,true,sprite_handler,Squares_Image,Bonuses_Image,0,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Squares(2932,TOP_LAND-128,30,32,2,true,sprite_handler,Squares_Image,Bonuses_Image,1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Sight(2930,TOP_LAND-25,2,true,sprite_handler,Sight_Image,quadTree);
		quadTree->Add(quadTree->Root,Try);

		Try=new Bonuses(2860,TOP_LAND-352,sprite_handler,Bonuses_Image,quadTree,0,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Bonuses(2892,TOP_LAND-352,sprite_handler,Bonuses_Image,quadTree,0,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Bonuses(2924,TOP_LAND-352,sprite_handler,Bonuses_Image,quadTree,0,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Bonuses(2956,TOP_LAND-352,sprite_handler,Bonuses_Image,quadTree,0,soundManager);
		quadTree->Add(quadTree->Root,Try);

		Try=new Squares(3000,TOP_LAND-160,32,32,5,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Squares(3032,TOP_LAND-128,32,32,5,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Squares(3064,TOP_LAND-96,32,32,5,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Squares(3096,TOP_LAND-64,32,32,5,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Squares(3128,TOP_LAND-32,32,32,5,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
	//
		Try=new Squares(3300,TOP_LAND-160,338,32,0,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Sight(3320,TOP_LAND-185,2,true,sprite_handler,Sight_Image,quadTree);
		quadTree->Add(quadTree->Root,Try);

		Try=new Squares(3700,TOP_LAND,978,64,0,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);//4678
		Try=new Sight(4000,TOP_LAND-25,2,true,sprite_handler,Sight_Image,quadTree);
		quadTree->Add(quadTree->Root,Try);

		Try=new Squares(3702,TOP_LAND-128,64,128,4,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		Try=new Squares(4000,TOP_LAND-64,64,64,4,true,sprite_handler,Squares_Image,Bonuses_Image,-1,effect,quadTree,soundManager);
		quadTree->Add(quadTree->Root,Try);
		//
		Try=new Sight(4400,TOP_LAND-31,6,true,sprite_handler,Sight_Image,quadTree);
		quadTree->Add(quadTree->Root,Try);
		Try=new Sight(4647,TOP_LAND-287,8,true,sprite_handler,Sight_Image,quadTree);
		quadTree->Add(quadTree->Root,Try);
		Try=new Sight(4596,TOP_LAND-287,7,true,sprite_handler,Sight_Image,quadTree);
		quadTree->Add(quadTree->Root,Try);
		Try=new Bonuses(4603,400,sprite_handler,Bonuses_Image,quadTree,5,soundManager);
		quadTree->Add(quadTree->Root,Try);
		*/
		//
		int z=200;
		for(;z<4500;)
		{
			Try=new Sight(z,10,0,true,sprite_handler,Sight_Image,quadTree);
			quadTree->Add(quadTree->Root,Try);
			Try=new Sight(z+150,50,0,true,sprite_handler,Sight_Image,quadTree);
			quadTree->Add(quadTree->Root,Try);
			z+=500;
		}
		//---------------------------------------------------------------------
		FILE *f=fopen("Maps\\Map2.mar","wb");
		fwrite(&quadTree->MapWidth,sizeof(int),1,f);
		fwrite(&quadTree->MapHeight,sizeof(int),1,f);
		fwrite(&quadTree->Count,sizeof(int),1,f);
		quadTree->WriteToFile(quadTree->Root,f);
		fclose(f);
	}
	void ReadFromFile(char *filename)
	{
		FILE *f=fopen(filename,"rb");
		int width=0,height=0;
		fread(&width,sizeof(int),1,f);
		fread(&height,sizeof(int),1,f);
		quadTree=new QuadTree(width,height);

		RECT Camera;
		Camera.left=0;
		Camera.top=0;
		Camera.right=Camera.left+SCREEN_WIDTH;
		Camera.bottom=SCREEN_HEIGHT;
		myScreen=new MyScreen(0,width,SCREEN_HEIGHT,&Camera);

		int count=0;
		fread(&count,sizeof(int),1,f);
		int left,top,secret,kind;
		long w,h;
		for(int i=0;i<count;i++)
		{
			int id=-2;
			Object *Ob=NULL;
			fread(&id,sizeof(int),1,f);
			switch(id)
			{
			case -1://Sight
				fread(&left,sizeof(long),1,f);
				fread(&top,sizeof(long),1,f);
				fread(&kind,sizeof(int),1,f);
				Ob=new Sight(left,top,kind,true,sprite_handler,Sight_Image,quadTree);
				break;
			case 0://Square
				fread(&left,sizeof(long),1,f);
				fread(&top,sizeof(long),1,f);
				fread(&w,sizeof(int),1,f);
				fread(&h,sizeof(int),1,f);
				fread(&secret,sizeof(int),1,f);
				fread(&kind,sizeof(int),1,f);
				Ob=new Squares(left,top,w,h,kind,true,sprite_handler,Squares_Image,Bonuses_Image,secret,effect,quadTree,soundManager);
				break;
			case 2://Enenmies
				fread(&left,sizeof(long),1,f);
				fread(&top,sizeof(long),1,f);
				fread(&w,sizeof(int),1,f);
				fread(&h,sizeof(int),1,f);
				fread(&kind,sizeof(int),1,f);
				Ob=new Enemies(left,top,w,h,myScreen,sprite_handler,Enemies_Image,quadTree,kind,soundManager);
				break;
			case 3://Bonuses
				fread(&left,sizeof(long),1,f);
				fread(&top,sizeof(long),1,f);
				fread(&kind,sizeof(int),1,f);
				Ob=new Bonuses(left,top,sprite_handler,Bonuses_Image,quadTree,kind,soundManager);
				break;
			}
			if(Ob!=NULL)
				quadTree->Add(quadTree->Root,Ob);
		}
		fclose(f);
	}
};