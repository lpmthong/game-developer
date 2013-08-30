#include "d3d9.h"
#include "d3dx9.h"

class DirectX{
	
	public:
		
		HWND _hWnd;
		LPDIRECT3D9 _d3d;
		LPDIRECT3DDEVICE9 _d3ddv;
		LPDIRECT3DSURFACE9	_backBuffer;
		LPDIRECT3DSURFACE9	_backGround;
		D3DFORMAT _backBufferFormat;
		
		DirectX(void);
		DirectX(HWND hwnd);
		void InitDirectX();
		~DirectX();
};