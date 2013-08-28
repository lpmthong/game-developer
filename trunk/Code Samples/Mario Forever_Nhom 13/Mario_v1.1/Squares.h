#pragma once
#include "Object.h"
#include "windows.h"
#include "Sprites.h"
#include "d3d9.h"
#include "d3dx9.h"
#include "QuadTree.h"
#include "Bonuses.h"
#include "Bullet.h"


class Squares: public Object//Lop vat can
//0_mat dat,1_gach,2_dau cham hoi, 3_gach co nhieu coin,4_cot,5_vat can vuong
{
public:
	Effect **effect;
	QuadTree *quadTree;
	Squares(){};
	Squares(int left,int top,int width,int height,int kind,
		bool visible,LPD3DXSPRITE sprite_Handle,LPDIRECT3DTEXTURE9 *texture,LPDIRECT3DTEXTURE9 *texture1,int secret,Effect **ef,QuadTree *q,SoundManager *sManager);
	void BeTouch(Object *Ob);
	void Draw(int VirtualLeft,int Style);
	int Move();
	void WriteToFile(FILE *f);
	~Squares(void);
	void Release(){}
private:
	LPDIRECT3DTEXTURE9 *Bonus_Texture;
	int CountCoin;//Dung cho gach co nhieu coin
	int Secret;//nothing_-1,0_Coin,1_HealthMusroom_Flower,2_ExtralifeMusroom,or 3_Star
};