#include <Windows.h>
#include "Sprite.h"
#include "d3d9.h"
#include "d3dx9.h"
#define KITTY_SPEED 0.5f
#define GROUND_Y 450
#define ANIMATE_RATE 30
#define KITTY_IMAGE_LEFT L"kitty_left.bmp"
#define KITTY_IMAGE_RIGHT L"kitty_right.bmp"
class Kitty
{
private:
	float PosX, PosY;
	float Vx, Vy;
	float Vx_last;
	bool right;
	DWORD last_time;
	Sprite *kitty_left;
	Sprite *kitty_right;

	LPD3DXSPRITE _SpriteHandler;
public:

	Kitty(LPD3DXSPRITE SpriteHandler, int _PosX);	
	void Render(int t);
	void MoveLeft();
	void MoveRight();
	void NotMove();
	void Jump();
	void Update(int t);
	void AutoMove();
	~Kitty();
};