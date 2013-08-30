#include "mmain.h"


mmain::mmain(void)
{
}


mmain::~mmain(void)
{
}
void mmain::Init(HINSTANCE m_hInstance){
	hInstance = m_hInstance;
	m_InitWidow();
	m_InitDirectX();
}
void mmain::m_InitWidow(){
	WNDCLASSEX wc;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_PEN);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = (WNDPROC)mmain::WinProc;
	wc.lpszClassName = "Demo";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wc);

	hWND = CreateWindowA("Demo",
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

	ShowWindow(hWND, SW_SHOWDEFAULT);
	UpdateWindow(hWND);
}
void mmain::m_InitDirectX()
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp,sizeof(d3dpp));
	d3dpp.Windowed = true;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferHeight = 600;
	d3dpp.BackBufferWidth = 800;
	d3dpp.hDeviceWindow = hWND;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

		if(FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWND, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &d3ddev)))
		if(FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWND, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &d3ddev)))
		if(FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWND, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev)))
		{
			MessageBox(0,"Can not create device","error",MB_OK);
		}
		d3ddev->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&backbuffer);
}
LRESULT CALLBACK mmain::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	switch(message){
		case WM_DESTROY:{
						PostQuitMessage(0);
						break;
					}
		default :
			return DefWindowProc(hWnd, message,wParam,lParam);
	}
	return 0;
}