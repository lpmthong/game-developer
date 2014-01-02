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
	int oldTop; //kiem tra xem no co dang rot xuong khong

	int lastCheckPoint; //Noi bat dau ve mario

	Box marioBox; //Cai nay de dung khi xet va cham

	float VxF, VyF;

	bool ConUpdate; //Cai nay de xem coi khong co va cham thi tiep tuc  

	bool hasGun; //Co vu khi khong

	bool loop;
	DWORD beginLoop;	//bat dau lap
	DWORD timeInLoop;	//thoi gian trong vong lap
	int kindLoop;		//loai lap
	int endMode;		//lap xong thi mario o loai nao
	int startMode;		//luc bat dau lap thi mario o loai nao
	DWORD rateLoop;		//animated rate to loop.
	DWORD lastLoop;		//time between two times change mode in loop.

	//Co star khong
	bool hasStar;
	DWORD startHasStar;
	DWORD timeHasStar;
	bool hasStarRender;

	//Bat tu nhung luc ma bi teo nho
	bool immortal;
	int immortalRender; // Cai bien nay lam cho no cho mario chop chop 0,1 thi render 2,3 thi khong render
	DWORD beginImmortal;
	DWORD timeInImmortal;

	DWORD delayShot;	//khoang cach giua 2 lan ban
	DWORD lastShot;		
	int numOfBullet;	//so luon dan co the ban ra;

	bool getEndMap;
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

	void Init(int left, int top, int mode,int LastCheckPoint, int Life, int iid);
	void InitFromFile(int left, int top, int mode,int LastCheckPoint, int Life);

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
	void CollideWithDynamicObj(int t);

	void CollideWithGround(float normalx, float normaly, float collisiontime,  StaticObject *obj);
	void CollideWithPiPe(float normalx, float normaly, float collisiontime,  StaticObject *obj);
	void CollideWithHardBrick(float normalx, float normaly, float collisiontime,  StaticObject *obj);
	void CollideWithCoin(StaticObject *obj);
	void CollideWithBrick(float normalx, float normaly, float collisiontime,  StaticObject *obj);
	void CollideWithEndMap(float normalx, float normaly, float collisiontime,  StaticObject *obj);

	void CollideWithBonusMushRoom(DynamicObject *obj);	
	void CollideWithTurtleEnemy(float normaly, DynamicObject *obj);
	void CollideWithTurtleDeath(float normaly, DynamicObject *obj);
	void CollideWithMushRoomEnemy(float normaly, DynamicObject *obj);
	void CollideWithPirhanaPlant(StaticObject *obj);
	void CollideWithCross(float normalx, float normaly, float collisiontime, DynamicObject *obj);
	
	//Cac ham thay doi luc an nam
	void ChangeModeLoop();
	void ChangeMode(int mode);

	//Xu li chet
	bool KillEnemy(DynamicObject *enemy, float normaly);
	void Die();
	void DieRightAway();
	void ProcessDying();

	void CheckImmortal();
	void UpdateCheckPoint();

	void UpdateMarioBox(float ix, float iy, float iw, float ih, float ivx, float ivy);
	void CollectCoin();
};