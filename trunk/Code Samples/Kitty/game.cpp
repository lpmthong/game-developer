#include "game.h"
#include <Windows.h>

TGame::TGame(void)
{
}
TGame::TGame(HINSTANCE hInstance, LPWSTR Name)
{
	_d3d = NULL;
	_d3ddv = NULL;
	_BackBuffer = NULL;

	_di = NULL;
	_KeyBoard = NULL;	
	_hInstance = hInstance;
	_Name = Name;
	_BackBufferFormat =  D3DFMT_X8R8G8B8;
	_FrameRate = 60;	
}

void TGame::_InitWindow()
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = _hInstance;

	wc.lpfnWndProc = (WNDPROC)TGame::_WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = _Name;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);
	//Center screen
	int screenX = GetSystemMetrics(SM_CYSCREEN);
	int screenY = GetSystemMetrics(SM_CXSCREEN);

	int xCtr = (screenX / 2 );
	int yCtr = (screenY / 2 ) - GAME_HIGHT;

	_hWnd = CreateWindow(
		_Name,
		_Name,
		WS_OVERLAPPEDWINDOW,
		xCtr,
		yCtr,
		GAME_WIDTH,
		GAME_HIGHT,
		NULL,
		NULL,
		_hInstance,
		NULL);
	

	ShowWindow(_hWnd,SW_SHOWNORMAL);
	UpdateWindow(_hWnd);
}
void TGame::_InitDirectX()
{
	_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp,sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat =  _BackBufferFormat;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = GAME_HIGHT;
	d3dpp.BackBufferWidth = GAME_WIDTH;

	_d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&_d3ddv);
	if (_d3ddv == NULL)
	{
	}
	_d3ddv->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&_BackBuffer);
	D3DXCreateSprite(_d3ddv,&_SpriteHandler);
}
void TGame::_InitKeyBoard()
{
	HRESULT hr = DirectInput8Create(_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&_di, NULL);
	if (hr!=DI_OK)
	{
		return;
	}
	hr = _di->CreateDevice(GUID_SysKeyboard, &_KeyBoard, NULL);
	if (hr!=DI_OK)
	{
		return;
	}

	hr = _KeyBoard->SetDataFormat(&c_dfDIKeyboard);

	hr = _KeyBoard->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	//Buffer Input
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj        = 0;
	dipdw.diph.dwHow        = DIPH_DEVICE;
	dipdw.dwData            = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size	

	hr = _KeyBoard->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );
	if (hr!=DI_OK) return;

	hr = _KeyBoard->Acquire(); 
	if (hr!=DI_OK) return;
}
void TGame::ProcessKeyBoard()
{
	_KeyBoard->GetDeviceState( sizeof(_KeyStates), _KeyStates);

	if (IsKeyDown(DIK_ESCAPE))
	{		
		PostMessage(_hWnd,WM_QUIT,0,0);
	}
	else
		if (IsKeyDown(DIK_RIGHT))
		{
			kitty->MoveRight();
		}
		else
			if (IsKeyDown(DIK_LEFT))
			{
				kitty->MoveLeft();
			}
			else
				kitty->NotMove();
	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	HRESULT hr = _KeyBoard->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), _KeyEvents, &dwElements, 0 );

	// Scan through all data, check if the key is pressed or released
	for( DWORD i = 0; i < dwElements; i++ ) 
	{
		int KeyCode = _KeyEvents[i].dwOfs;
		int KeyState = _KeyEvents[i].dwData;
		if ( (KeyState & 0x80) > 0)
			OnKeyDown(KeyCode);
		else 
			OnKeyUp(KeyCode);
	}
}
int TGame::IsKeyDown(int KeyCode)
{
	return (_KeyStates[KeyCode] & 0x80) > 0;
}
void TGame::OnKeyDown(int KeyCode)
{	
	switch(KeyCode)
	{
	case DIK_SPACE:
		kitty->Jump();
		break;
	}
}
void TGame::OnKeyUp(int KeyCode){}
void TGame::Init()
{
	_InitWindow();
	_InitDirectX();
	_InitKeyBoard();
	LoadResource();
}
void TGame::Render(int t)
{	
	_d3ddv->BeginScene();
	_d3ddv->StretchRect(BackGround, NULL, _BackBuffer, NULL, D3DTEXF_NONE);
	kitty->Render(t);
	kitty_bot->Render(t);
	_d3ddv->EndScene();
	_d3ddv->Present(NULL,NULL,NULL,NULL);
}
void TGame::Run()
{
	MSG msg;
	int done = 0;
	DWORD frame_start = GetTickCount();;

	DWORD tick_per_frame = 100 / _FrameRate;
	
	while (!done) 
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if (msg.message==WM_QUIT) done=1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);			
		}

		DWORD now = GetTickCount();
		_DeltaTime = now - frame_start; 
		if (_DeltaTime >= tick_per_frame)
		{
			frame_start = now;
			kitty_bot->AutoMove();
			Render(_DeltaTime);
		}
		ProcessKeyBoard();
	}
}
void TGame::LoadResource()
{
	HRESULT hResult;	
	D3DXIMAGE_INFO imageInfo;
	//D3DXCreateSprite(_d3ddv,&SpriteHandle);
	kitty = new Kitty(_SpriteHandler, 10);
	kitty_bot = new Kitty(_SpriteHandler,200);
	hResult = D3DXGetImageInfoFromFile(BACKGROUND, &imageInfo);
	if FAILED (hResult)
		return;
	hResult = _d3ddv->CreateOffscreenPlainSurface(imageInfo.Width, imageInfo.Height, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &BackGround, NULL);
	if (FAILED(hResult))
		return;
	hResult = D3DXLoadSurfaceFromFile(BackGround, NULL, NULL, BACKGROUND, NULL, D3DX_DEFAULT, 0, NULL);
	if (FAILED(hResult))
		return;
}
LRESULT CALLBACK TGame::_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
	case WM_DESTROY: 
		PostQuitMessage(0);
		break;
	default: 
		return DefWindowProc(hWnd, message, wParam,lParam);
	}

	return 0;
}
TGame::~TGame()
{
	if (_d3ddv!=NULL) _d3ddv->Release();
	if (_d3d!=NULL) _d3d->Release();

	if( _KeyBoard )  
	{
		_KeyBoard->Unacquire();
		_KeyBoard->Release();
	}

	if (_di) _di->Release();
}
