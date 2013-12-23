#pragma once
#include "Define.h"
#include "DynamicObject.h"
#include "ListTexture.h"
#include "Box.h"
#include "StaticObject.h"

class Player : public DynamicObject{

public:
	int life;
	bool alive;

	bool onGround; //Dang nam tren mat dat hay cai gi do.
	bool jumping; //Co dang nhay hay khong?

	float maxSpeed;

	bool oldDirect; //Truoc khi dung thi no dang o huong nao true thi phai, false thi trai

	int lastCheckPoint; //Noi bat dau ve mario

	Box marioBox; //Cai nay de dung khi xet va cham

	float VxF, VyF;

	bool ConUpdate; //Cai nay de xem coi khong co va cham thi tiep tuc  

	bool hasGun; //Co vu khi khong
private:
	int frame_moving_left_start;
	int frame_moving_left_end;
	int frame_moving_right_start;
	int frame_moving_right_end;
	int frame_jumping_left_start;
	int frame_jumping_left_end;
	int frame_jumping_right_start;
	int frame_jumping_right_end;

public:
	Player(void);
	~Player(void);

	void Init(int mode,int LastCheckPoint, int Life);
	void InitFromFile(int mode,int LastCheckPoint, int Life);

	void setKid();
	void setAdult();
	void setGun();

	void Update();
	void Render();

	void UpdateSprite();
	//void UpdateSprite(bool flag);

	void ProcessInput();
	void OnKeyDown(int keyCode);

	//Cac ham xet va cham
	void CollideWithStaticObj();
	void CollideWithGround(float normalx, float normaly, float collisiontime,  StaticObject *obj);
	void CollideWithPiPe(float normalx, float normaly, float collisiontime,  StaticObject *obj);
	void CollideWithHardBrick(float normalx, float normaly, float collisiontime,  StaticObject *obj);
	void CollideWithCoin(StaticObject *obj);
	void CollideWithBrick(float normalx, float normaly, float collisiontime,  StaticObject *obj);

	void UpdateMarioBox(float ix, float iy, float iw, float ih, float ivx, float ivy);
	void CollectCoin();
};