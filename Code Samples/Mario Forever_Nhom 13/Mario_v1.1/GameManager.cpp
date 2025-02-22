#include "GameManager.h"


GameManager::~GameManager(void)
{
}
bool GameManager::InitDirect3D() 
{ 
	pD3D = NULL; 
	pd3dDevice = NULL;
	// Create the DirectX object 
	if((pD3D = Direct3DCreate9( D3D_SDK_VERSION ) )==NULL ) 
	{ 
		return false; 
	} 
	// Fill the presentation parameters structure 
	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory( &d3dpp, sizeof( d3dpp ) ); 
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; 
	d3dpp.BackBufferFormat =  D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1; 
	d3dpp.BackBufferHeight =SCREEN_HEIGHT; 
	d3dpp.BackBufferWidth = SCREEN_WIDTH;//Max:1600
	d3dpp.hDeviceWindow = hWnd; 
	// Create a default DirectX device 
	if( FAILED(pD3D->CreateDevice( D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,&pd3dDevice ) ) ) 
	{ 
		return false; 
	}
	//Create Sprite_handler
	HRESULT result=D3DXCreateSprite(pd3dDevice,&sprite_handler);
	if(result!=D3D_OK)
	{
		MessageBox(hWnd,"Can't","Create Sprite Handle",MB_OK);
		return NULL;
	}
	return true;
}
bool GameManager::InitDirectInput()
{
	HRESULT Hr;
	Hr= DirectInput8Create(hInst,DIRECTINPUT_VERSION,IID_IDirectInput8,(void**) & KeyBoard_Object, NULL); 
	if FAILED (Hr) 
		return false;
	Hr=KeyBoard_Object->CreateDevice(GUID_SysKeyboard, &KeyBoard_Device, NULL); 	
	if FAILED (Hr) 
		return false; 
	Hr = KeyBoard_Device->SetDataFormat(&c_dfDIKeyboard); 	
	if FAILED (Hr) 
		return false; 
	Hr = KeyBoard_Device->SetCooperativeLevel(hWnd, DISCL_FOREGROUND|DISCL_NONEXCLUSIVE ); 	
	if FAILED (Hr) 
		return false;
	return true;
}

void GameManager::InitTexture()
{
	BackGround_Image=LoadTexture("Images\\BackGround.png",0);
	Mario_Image=LoadTexture("Images\\Mario.png",0);
	Squares_Image=LoadTexture("Images\\Objects.png",0);
	Enemies_Image=LoadTexture("Images\\Enemies.png",0);
	Bonuses_Image=LoadTexture("Images\\Bonus.png",0);
	Sight_Image=LoadTexture("Images\\Sight.png",0);
	First_Image=LoadTexture("Images\\First.png",0);
	Info_Image=LoadTexture("Images\\Info.png",0);
}
void GameManager::KeyBoard()
{
	char buffer[256];
	KeyBoard_Device->Acquire();
	KeyBoard_Device->GetDeviceState(sizeof (buffer), (LPVOID )&buffer);
	if(Status!=0&&(KEYDOWN(buffer,DIK_F2)||KEYDOWN(buffer,DIK_ESCAPE)))
		Status=0;
	switch(Status)
	{
	case 0://Menu
		if(menu!=NULL&&menu->IsKeyUp)
		{
			if(KEYDOWN(buffer, DIK_UP)||KEYDOWN(buffer, DIK_LEFT))
			{
				soundManager->Play("MenuChange",false);
				menu->Seq-=1;
				if(menu->Seq<0)
					menu->Seq=menu->TotalMenuItem-1;
				menu->IsKeyUp=false;
			}
			else if(KEYDOWN(buffer, DIK_DOWN)||KEYDOWN(buffer, DIK_RIGHT))
			{
				soundManager->Play("MenuChange",false);
				menu->Seq=(menu->Seq+1)%menu->TotalMenuItem;
				menu->IsKeyUp=false;
			}
			else if(KEYDOWN(buffer,DIK_RETURN))//EnterS
			{
				menu->Accept();
				if(menu->Seq==0)
					NewGame();
			}
		}
		if(!KEYDOWN(buffer, DIK_UP)&&!KEYDOWN(buffer, DIK_LEFT)&&!KEYDOWN(buffer, DIK_DOWN)&&!KEYDOWN(buffer, DIK_RIGHT))
				menu->IsKeyUp=true;
		break;
	case 1://Playing
		if(MyMario!=NULL)
		{
				if(KEYDOWN(buffer, DIK_LEFT)&&MyMario->Status!=2)
				{ 
					if(!MyMario->Sprite->Enable)
					{
						if(MyMario->Status!=1)//Khong nhay
						{
							MyMario->Sprite->Enable=true;
						}
					}
					if(!MyMario->OnMove->IsLeft)
					{
						MyMario->OnMove->IsLeft=true;
						MyMario->ChangeDim(false);
					}
					MyMario->Move();
				}
				else if (KEYDOWN(buffer,DIK_RIGHT)&&MyMario->Status!=2)
				{
					if(!MyMario->Sprite->Enable)
					{
						if(MyMario->Status!=1)
						{						
							MyMario->Sprite->Enable=true;
						}
					}
					if(MyMario->OnMove->IsLeft)
					{
						MyMario->OnMove->IsLeft=false;
						MyMario->ChangeDim(false);
					}
					MyMario->Move();
				}
				if(KEYDOWN(buffer,DIK_LSHIFT)&&MyMario->Status!=2)
				{
					if(MyMario->Status!=1)//Khong phai dang nhay
					{
						soundManager->Play("Jump",false);
						MyMario->OnMove->FrameTime=MyMario->OnMove->HFrameTime;
						MyMario->Status=1;
						MyMario->ChangeDim(true);
						if(MyMario->upDown!=NULL)
							delete MyMario->upDown;
						MyMario->upDown=new UpDown(0);
					}
				}
				if((KEYDOWN(buffer,DIK_Z)||KEYDOWN(buffer,DIK_UP))&&MyMario->Status!=2)
				{
					if(MyMario->Status==1&&MyMario->upDown!=NULL&&!MyMario->upDown->IsSupper)
					{
						MyMario->OnMove->FrameTime=MyMario->OnMove->HFrameTime;
						MyMario->upDown->IsSupper=true;
						MyMario->upDown->Index+=3;
					}
				}
				if(KEYDOWN(buffer,DIK_Z)&&MyMario->Status!=2&&MyMario->Level>=2&&MyMario->bulletManager->BulletCounter<MyMario->bulletManager->MaxBullet
					&&GetTickCount()-MyMario->bulletManager->OldTime>MyMario->bulletManager->Interval)
				{
					MyMario->bulletManager->BulletCounter++;
					Object *Ob=new Bullet(MyMario->bulletManager,MyMario->OnMove->IsLeft,
						(MyMario->OnMove->IsLeft?MyMario->Rect->left-25:MyMario->Rect->right+20),
						MyMario->Rect->top+20,sprite_handler,&Squares_Image,effect,mapManage->quadTree,mapManage->myScreen,infomation);
					mapManage->quadTree->Add(mapManage->quadTree->Root,Ob);
					MyMario->bulletManager->OldTime=GetTickCount();
					soundManager->Play("Shoot",false);
				}
				if(!KEYDOWN(buffer,DIK_LEFT)&&!KEYDOWN(buffer,DIK_RIGHT))
					MyMario->OnMove->OldTime=GetTickCount();
		}
		break;
	}
}
//----------------------------------------------------------------------------
//Tao texture tu file anh
LPDIRECT3DTEXTURE9 GameManager::LoadTexture(char *filename,D3DCOLOR transcolor)
{
	/*LPDIRECT3DTEXTURE9 texture=NULL;
	D3DXIMAGE_INFO info;
	HRESULT result=D3DXGetImageInfoFromFileA(filename,&info);
	if(result!=D3D_OK)
	{
		MessageBox(hWnd,"Can't","Get Info",MB_OK);
		return NULL;
	}
	//D3DX_DEFAULT_NONPOW2	
	result=D3DXCreateTextureFromFileExA(pd3dDevice,filename,info.Width,info.Height,1,D3DPOOL_DEFAULT,
	D3DFMT_UNKNOWN,D3DPOOL_DEFAULT,D3DX_DEFAULT,D3DX_DEFAULT,transcolor,&info,NULL,&texture);
	/*
	result=D3DXCreateTextureFromFileExA(pd3dDevice,filename,info.Width,info.Height,1,D3DPOOL_DEFAULT,
	D3DFMT_UNKNOWN,D3DPOOL_DEFAULT,D3DX_DEFAULT,D3DX_DEFAULT,transcolor,&info,NULL,&texture);
	
	if(result!=D3D_OK)
	{
		MessageBox(hWnd,"Can't","Create Texture",MB_OK);
		return NULL;
	}
	return texture;*/
	LPDIRECT3DTEXTURE9 texture=NULL;
	D3DXIMAGE_INFO info;
	HRESULT result=D3DXGetImageInfoFromFileA(filename,&info);
	if(result!=D3D_OK)
	{
		MessageBox(hWnd,"Can't","Get Info",MB_OK);
		return NULL;
	}
	result=D3DXCreateTextureFromFileExA(pd3dDevice,filename,info.Width,info.Height,1,D3DPOOL_DEFAULT,
	D3DFMT_UNKNOWN,D3DPOOL_DEFAULT,D3DX_DEFAULT,D3DX_DEFAULT,transcolor,&info,NULL,&texture);
	if(result!=D3D_OK)
	{
		MessageBox(hWnd,"Can't","Create Texture",MB_OK);
		return NULL;
	}
	return texture;
}
IDirect3DSurface9* GameManager::LoadSurface(char *filename)
{
	IDirect3DSurface9* s=NULL;
	
	D3DXIMAGE_INFO info;
	HRESULT result=D3DXGetImageInfoFromFileA(filename,&info);
	if(result!=D3D_OK)
	{
		MessageBox(hWnd,"Can't","Get Info",MB_OK);
		return NULL;
	}

	result = pd3dDevice->CreateOffscreenPlainSurface(info.Width,info.Height,D3DFMT_X8R8G8B8,D3DPOOL_DEFAULT,&s,NULL);
	// Kiểm tra xem kết quả trả về của hàm có thành công hay không 
	if (FAILED(result)) 
		return NULL;
	result = D3DXLoadSurfaceFromFile(s,NULL,NULL,filename,NULL, D3DX_DEFAULT,0, NULL ); 	
	if (FAILED( result ) ) 
	{
		MessageBox(hWnd,("Không tìm thấy file ảnh"),("Pos"),MB_OK);
		return NULL;
	}
	return s;
}
//----------------------------------------------------------------------------
void GameManager::NewGame()
{
	infomation=new Infomation(sprite_handler,Info_Image);
	if(mapManage!=NULL)
		delete mapManage;
	mapManage=new MapManager(sprite_handler,&BackGround_Image,&Mario_Image,&Squares_Image,&Enemies_Image,&Bonuses_Image,&Sight_Image,effect,soundManager);
	if(MyMario!=NULL)
		delete MyMario;
	MyMario=new Mario(0,sprite_handler,&Mario_Image,mapManage->myScreen,mapManage->quadTree,infomation,soundManager);
	mapManage->quadTree->Add(mapManage->quadTree->Root,MyMario);
	for(int i=0;i<10;i++)
		effect[i]=NULL;
	soundManager->BackMusicSound.playSoundLoop(soundManager->BackMusicBuffer);
}
void GameManager::ResetGame()
{
	soundManager->BackMusicSound.playSoundLoop(soundManager->BackMusicBuffer);
	if(mapManage==NULL)
		mapManage=new MapManager(sprite_handler,&BackGround_Image,&Mario_Image,&Squares_Image,&Enemies_Image,&Bonuses_Image,&Sight_Image,effect,soundManager);
	else
		mapManage->LoadMap();
	if(MyMario==NULL)//bat dau game
	{
		MyMario=new Mario(0,sprite_handler,&Mario_Image,mapManage->myScreen,mapManage->quadTree,infomation,soundManager);
		mapManage->quadTree->Add(mapManage->quadTree->Root,MyMario);
	}
	else
	{
		MyMario->Rect->left=7;MyMario->Rect->right=26;
		MyMario->Rect->top=TOP_LAND-33;MyMario->Rect->bottom=TOP_LAND-1;
		delete MyMario->Sprite;
		MyMario->Sprite=new Sprites(false,0,2,0,33,32,sprite_handler,&Mario_Image,0,TOP_LAND-1,5000,90);
		MyMario->Sprite->Enable=false;
		MyMario->upDown=NULL;
		MyMario->Level=0;//nho_to_ban dc
		MyMario->JustChangeLevel=true;
		MyMario->JustMove=true;
		MyMario->Status=0;//Stand still
		MyMario->quadTree=mapManage->quadTree;
		MyMario->screen=mapManage->myScreen;
		MyMario->OnMove->IsLeft=false;
		mapManage->quadTree->Add(mapManage->quadTree->Root,MyMario);
	}
}
void GameManager::FinishedMap()
{
	mapManage->quadTree->Remove(mapManage->quadTree->Root,MyMario);
	mapManage->MapSeq++;
	if(mapManage->MapSeq>2)
		mapManage->MapSeq=1;
	mapManage->LoadMap();
	MyMario->Rect->left=7;MyMario->Rect->right=26;
	MyMario->Sprite->Left=0;
	MyMario->JustChangeLevel=true;
	MyMario->Status=0;//Stand still
	MyMario->screen=mapManage->myScreen;
	MyMario->quadTree=mapManage->quadTree;
	mapManage->quadTree->Add(mapManage->quadTree->Root,MyMario);
	soundManager->BackMusicSound.playSoundLoop(soundManager->BackMusicBuffer);
}
void GameManager::GameOver()
{
	sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);
	RECT source;
	D3DXVECTOR3 des(256,232,0);
	source.left=0;source.right=132;
	source.top=107;source.bottom=source.top+16;
	sprite_handler->Draw(Info_Image,&source,NULL,&des,D3DCOLOR_XRGB(255,255,255));
	sprite_handler->End();
}
RECT source;
//----------------------------------------------------------------------------
void GameManager::MainDraw()
{
	if(MyMario!=NULL&&MyMario->Rect->top>SCREEN_HEIGHT)
	{
		infomation->Life--;
		if(infomation->Life<1)
			Status=2;//GameOver
		else
			ResetGame();
	}
	if(Status!=3&&MyMario->Rect->right>=mapManage->myScreen->LimRight)
	{
		Status=3;//Ket thuc map
		MyMario->Sprite->RootTime=GetTickCount();
		soundManager->BackMusicSound.stopSound(soundManager->BackMusicBuffer);
		soundManager->Play("FinishMap",false);
	}
	if(Status==3&&GetTickCount()-MyMario->Sprite->RootTime>6000)
	{
		Status=1;//Play
		FinishedMap();
	}
	D3DXVECTOR3 des(0,0,0);
	sprite_handler->Draw(BackGround_Image,&source,NULL,&des,D3DCOLOR_XRGB(255,255,255));	
	mapManage->quadTree->UpdatePosition(mapManage->quadTree->Root);
	mapManage->quadTree->DrawObjects(mapManage->myScreen->Rect.left,mapManage->quadTree->Root,mapManage->myScreen->Rect,0);
	mapManage->quadTree->DrawObjects(mapManage->myScreen->Rect.left,mapManage->quadTree->Root,mapManage->myScreen->Rect,1);
	DrawMario();
	mapManage->quadTree->DrawObjects(mapManage->myScreen->Rect.left,mapManage->quadTree->Root,mapManage->myScreen->Rect,2);
	DrawEffect();
	infomation->Draw();
}
void GameManager::DrawEffect()
{
	for(int i=0;i<10;i++)
	{
		if(effect[i]!=NULL)
		{
			if(effect[i]->Kind==0)
				effect[i]->sprite->Draw(mapManage->myScreen->Rect.left,0,true);
			else
				effect[i]->sprite->Draw(mapManage->myScreen->Rect.left,-1,true);
			if(GetTickCount()-effect[i]->sprite->RootTime>=(DWORD)effect[i]->sprite->TotalExistTime)
				effect[i]=NULL;
		}
	}
}
void GameManager::DrawMario()
{
	if(MyMario!=NULL)
	{
		MyMario->Jump();
		MyMario->Die();
		if(MyMario->Status==0&&!MyMario->quadTree->IsOnObject(MyMario->Rect,MyMario->Sequency))//Allways check
		{
			MyMario->Status=1;//Jump
			MyMario->ChangeDim(true);
			MyMario->upDown=new UpDown(2);//hut chan roi xuong
		}
		if(MyMario->Status!=1)
			MyMario->Sprite->Draw(mapManage->myScreen->Rect.left,0,false);
		else
			MyMario->Sprite->Draw(mapManage->myScreen->Rect.left,2,false);
		if((GetTickCount()-MyMario->Sprite->RootTime) > (DWORD)(MyMario->Sprite->TotalExistTime))
			MyMario->JustChangeLevel=false;
	}
}
//----------------------------------------------------------------------------
void GameManager::DrawMenu()
{
	RECT source;
	source.left=source.top=0;
	source.right=SCREEN_WIDTH;
	source.bottom=SCREEN_HEIGHT;
	D3DXVECTOR3 des(0,0,0);
	sprite_handler->Draw(First_Image,&source,NULL,&des,D3DCOLOR_XRGB(255,255,255));
	menu->Draw();
}
//----------------------------------------------------------------------------
GameManager::GameManager(HWND hwn,HINSTANCE hnst)
{
	hWnd=hwn;
	hInst=hnst;
	Status=0;//Menu
	//
	MyMario=NULL;
	//
	for(int i=0;i<10;i++)
		effect[i]=NULL;
	//
	mapManage=NULL;
	//
	infomation=NULL;
	if(!InitDirect3D())
		return;
	InitTexture();
	if(!InitDirectInput())
		return;

	source.left=source.top=0;
	source.right=SCREEN_WIDTH;
	source.bottom=SCREEN_HEIGHT;
	menu=new Menu(2,sprite_handler,&Info_Image,&Status,hWnd);
	soundManager=new SoundManager(hWnd);
}

void GameManager::Run()
{
	pd3dDevice->BeginScene();
	pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET,D3DCOLOR_XRGB( 0,0,0 ), 1.0f, 0 );
	sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);
	//Insert draw code here
	switch(Status)
	{
	case 0://Menu
		DrawMenu();
		break;
	case 3://FinishMap
	case 1://Playing
		MainDraw();
		break;
	case 2://GameOver
		MainDraw();
		GameOver();
		break;
	}
	sprite_handler->End();
	pd3dDevice->EndScene();
	pd3dDevice->Present(NULL,NULL,NULL,NULL);
}