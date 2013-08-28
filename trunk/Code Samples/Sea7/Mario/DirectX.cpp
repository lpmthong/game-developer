#include "DirectX.h"
#include "trace.h"
#include "GlobalHandler.h"
#include "Define.h"


DirectX::DirectX(void)
{
	nCmdShow = SW_SHOW;
	d3d = NULL;
	d3ddev = NULL;
	backbuffer = NULL;

	di = NULL;
	keyboard = NULL;
}
DirectX::DirectX(HINSTANCE _hInstance)
{
	hInstance = _hInstance;
	nCmdShow = SW_SHOW;
	d3d = NULL;
	d3ddev = NULL;
	backbuffer = NULL;

	di = NULL;
	keyboard = NULL;
}

DirectX::~DirectX(void)
{
}

void DirectX::Init(HINSTANCE _hInstance)
{
	hInstance = _hInstance;
	nCmdShow = SW_SHOW;
	d3d = NULL;
	d3ddev = NULL;
	backbuffer = NULL;
	dwElements = KEYBOARD_BUFFER_SIZE;

	InitWindow();
	InitDirectX();
	InitKeyboard();
	InitSpriteHandler();
}

void DirectX::InitWindow()
{
	WNDCLASSEX wc;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = (WNDPROC)DirectX::WinProc;
	wc.lpszClassName = "Demo";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wc);

	hWnd = CreateWindowA("Demo",
		"Demo",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		800,
		600,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
}

void DirectX::InitDirectX()
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp; 

	ZeroMemory( &d3dpp, sizeof(d3dpp) );

	d3dpp.Windowed   = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = 600;
	d3dpp.BackBufferWidth = 800;

	d3d->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&d3ddev);

	d3ddev->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&backbuffer);
}

void DirectX::InitKeyboard()
{
	HRESULT result = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, 
		IID_IDirectInput8, (void**)&di, NULL); 
	if (result != DI_OK)
		return;

	//Init keyboard
	result = di->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	if (result != DI_OK)
		return;

	result = keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (result != DI_OK)
		return;

	result = keyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (result != DI_OK)
		return;

	//buffered input
	DIPROPDWORD		dipdw;
	dipdw.diph.dwSize		=	sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize =	sizeof(DIPROPHEADER);
	dipdw.diph.dwHow		=	DIPH_DEVICE;
	dipdw.diph.dwObj		=	0;
	dipdw.dwData			=	KEYBOARD_BUFFER_SIZE;
	result = keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (result != DI_OK)
		return;

	result = keyboard->Acquire();
	if (result != DI_OK)
		return;
}

void DirectX::ProcessKeyboard()
{
	// Collect all key states first
	keyboard->GetDeviceState( sizeof(keyStates), keyStates);

	// Collect all buffered events
	dwElements = KEYBOARD_BUFFER_SIZE;
	keyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0 );

	/*for( DWORD i = 0; i < dwElements; i++ )
	{
		int keyCode = keyEvents[i].dwOfs;
		int keyState = keyEvents[i].dwData;
		if ((keyState & 0x80) > 0)
		{
		//	OnKeyDown(KeyCode);
			//trace(L"key down");
		}
		else 
		{
		//	OnKeyUp(KeyCode);
			//	trace(L"key up");
		}
	}*/
}

int DirectX::IsKeyDown(int KeyCode)
{
	return (keyStates[KeyCode] & 0x80) > 0;
}


LRESULT CALLBACK DirectX::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

void DirectX::Release()
{
	d3ddev->Release();
	d3d->Release();

	keyboard->Unacquire();
	keyboard->Release();
	
	di->Release();
}

void DirectX::InitSpriteHandler()
{
	D3DXCreateSprite(d3ddev, &spriteHandler);
	d3ddev->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&backbuffer);
}

LPDIRECT3DTEXTURE9 DirectX::LoadTextureFromFile(char* path, D3DCOLOR transkey )
{
	HRESULT hResult = NULL;
	LPDIRECT3DTEXTURE9 texture;
	D3DXIMAGE_INFO info;

	D3DXGetImageInfoFromFile(path, &info);
	if FAILED(hResult)
	{
		trace(L"Failed to init texture! %s", path);
		return NULL;
	}

	D3DXCreateTextureFromFileEx(d3ddev,
		path,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255,0,255),
		&info,
		NULL,
		&texture);

	if FAILED(hResult)
		return NULL;

	return texture;
}

void DirectX::DrawText( LPCTSTR text,RECT &rect, D3DCOLOR color, int type /*= DT_LEFT | DT_VCENTER*/ )
{
//	font->DrawTextW(NULL,text,-1,&rect,type | DT_WORDBREAK | DT_EXPANDTABS, color);
}

bool DirectX::BeginScene()
{
	if (GlobalHandler::backGroundColor == BLUE)
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(100, 100, 255), 1.0f, 0);
	else
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	if (FAILED(d3ddev->BeginScene()))
		return FALSE;

	return TRUE;
}

bool DirectX::EndScene()
{
	if (FAILED(d3ddev->EndScene()))
		return FALSE;

	d3ddev->Present(NULL,NULL,NULL,NULL);
	return TRUE;
}

void DirectX::InitFont(const TCHAR* fontFamily, int size, bool bold)
{
/*	HDC hDC = GetDC( NULL );
	int nLogPixelsY = GetDeviceCaps(hDC, LOGPIXELSY);
	ReleaseDC(NULL, hDC);
	int height = -size * nLogPixelsY / 72;
//	SAFE_RELEASE(this->font);
	if(FAILED(D3DXCreateFont(this->lpD3DDevice, height, 0, FW_BOLD, 1, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, fontFamily, &this->font)))
		return false;
	return true;*/
}
