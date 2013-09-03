#include "DirectX.h"

DirectX::DirectX(void){	
	this->_d3d				= NULL;
	this->_d3ddv			= NULL;
	this->_backBuffer		= NULL;
	this->_backBufferFormat = D3DFMT_X8R8G8B8;
	
}

void DirectX::InitDirectX(HWND _hWnd){
	this->_d3d = Direct3DCreate9(D3D_SDK_VERSION);
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
				//MessageBoxW(0, L"Can not create device", L"error",MB_OK);
			}
			_d3ddv->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&_backBuffer);
}

DirectX::~DirectX(){
	if (this->_d3ddv!=NULL) _d3ddv->Release();
	if (this->_d3d!=NULL) _d3d->Release();
}