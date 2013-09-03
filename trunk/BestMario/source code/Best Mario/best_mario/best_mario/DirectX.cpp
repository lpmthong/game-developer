#include "DirectX.h"

DirectX::DirectX(void){
	ncmdShow	= NULL;
	_d3d		= NULL;
	_d3ddv		= NULL;
	_backBuffer = NULL;
	_backGround = NULL;
}

DirectX::DirectX(HINSTANCE hInstance){
	_hInstance	= hInstance;
	ncmdShow	= SW_SHOW;
	_d3d		= NULL;
	_d3ddv		= NULL;
	_backBuffer = NULL;
	_backGround = NULL;
}

DirectX::~DirectX(void){
	Release();
}

void DirectX::Init(HINSTANCE hInstance){
	_hInstance	= hInstance;
	ncmdShow	= SW_SHOW;
	_d3d		= NULL;
	_d3ddv		= NULL;
	_backBuffer = NULL;
	_backGround = NULL;

	InitWindow();
	InitDirectX();
}

void DirectX::InitWindow(){
	WNDCLASSEX wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_PEN);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hInstance = _hInstance;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.lpszClassName = L"Mario Game";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wc);

	//Center screen
	int screenX = GetSystemMetrics(SM_CYSCREEN);
	int screenY = GetSystemMetrics(SM_CXSCREEN);

	int xCtr = (screenX / 2 );
	int yCtr = (screenY / 2 ) - GAME_HIGHT;

	_hWnd = CreateWindowA("Mario Game",
		"Mario Game",
		WS_OVERLAPPEDWINDOW,
		xCtr,
		yCtr,
		GAME_WIDTH,
		GAME_HIGHT,
		NULL,
		NULL,
		_hInstance,
		NULL);

	ShowWindow(_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(_hWnd);
}

void DirectX::InitDirectX(){
	_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp,sizeof(d3dpp));
	d3dpp.Windowed = true;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferHeight = 600;
	d3dpp.BackBufferWidth = 800;
	d3dpp.hDeviceWindow = _hWnd;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	if(FAILED(_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &_d3ddv)))
		if(FAILED(_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, _hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &_d3ddv)))
			if(FAILED(_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, _hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &_d3ddv)))
			{
				MessageBoxW(0, L"Can not create device", L"error",MB_OK);
			}
			_d3ddv->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&_backBuffer);

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

void DirectX::Release(){
	if (_d3ddv!=NULL) _d3ddv->Release();
	if (_d3d!=NULL) _d3d->Release();
}