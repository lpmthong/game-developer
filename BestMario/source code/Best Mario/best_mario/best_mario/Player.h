#pragma once
#include "Define.h"
#include "DynamicObject.h"
#include "ListTexture.h"

class Player : public DynamicObject{

public:
	int life; // Cai nay bo vo truoc tu tu tinh sau
	bool onGround; //Dang nam tren mat dat hay cai gi do.
	bool jumping; //Co dang nhay hay khong?

	float maxSpeed;

	bool oldDirect; //Truoc khi dung thi no dang o huong nao true thi phai, false thi trai

	int lastCheckPoint; //Noi bat dau ve mario
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

	void Update();
	void Render();

	void UpdateSprite();
	//void UpdateSprite(bool flag);

	void ProcessInput();
	void OnKeyDown(int keyCode);

	//Cac ham xet va cham
	void CollideWithStaticObj(float vx, float vy);

};