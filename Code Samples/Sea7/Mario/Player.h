#pragma once
#include "dynamicobject.h"
#include "Define.h"
#include "Sprite.h"
#include "StaticObject.h"

class Player :
	public DynamicObject
{

public:
	int life;
	bool alive;

	bool onGround;	//player on air or not.
	bool jumping;	//player jump to the air.

	bool immortal;
	int immortalRender;
	DWORD beginImmortal;
	DWORD timeInImmortal;

	bool hasStar;
	DWORD startHasStar;
	DWORD timeHasStar;
	bool hasStarRender;

	int maxSpeed;

	bool loop;
	DWORD beginLoop;	//start loop time.
	DWORD timeInLoop;	//time in loop mode
	int kindLoop;		//Kind of mario when looping.
	int endMode;		//mode of mario when loop stop.
	int startMode;		//mode of mario when loop start.
	DWORD rateLoop;		//animated rate to loop.
	DWORD lastLoop;		//time between two times change mode in loop.

	DWORD delayShot;	//time delay between twos shot times. 
	DWORD lastShot;		//last shot.
	int numOfBullet;	//limit the amount of bullet.

	bool oldDirect;	//the direct player face before stop. true: right false: left

	//Mario finish the map.
	bool getEndMap;

//	int yTemp; //If y change just a little, dont add it to real game.

	int times;	//Using it for debugging.

	int lastCheckPoint;

	int numOfCollideObject;	//Number of collided object.

	int oldLeftCollidedObject;	//Use to handle collide 2 object at the same time.
	int oldCollidedObject;	//Use to handle collide 2 object at the same time.
	bool sameColumn;	//If 2 collided object line as a collumn.
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
	Player(int left, int top);
	~Player(void);

public:
	void Init(int outMode, int outLastCheckPoint, int outLife);
	void InitFromFile(int outMode, int outLastCheckPoint, int outLife);

	void setAdult();
	void setKid();
	void setGun();

	bool hasGun;

	void Update();
	void Render();

	void UpdateSprite();

	//Update sprite right away if rightAway variable is true.
	void UpdateSprite(bool rightAway);

	void ProcessInput();
	void OnKeyDown(int keyCode);

	//handle collision with object in quadtree.
	void HandleCollisionQT();

	//handle collision with object in dynamic object list.
	void HandleCollisionDO();

	void CollidePIPE(StaticObject* obj);
	void CollideGround(StaticObject* obj);
	void CollideBrick(DynamicObject* obj);
	void CollideMushRoomEnemy(DynamicObject* enemy);
	void CollideTurle(DynamicObject* turle);
	void CollideOutCoin(StaticObject* coin);
	void CollidePirhanaPlant(DynamicObject* obj);
	void CollideEndMap(StaticObject* obj);

	void CheckImmortal();

	//Loop changing mode between adult and kid.
	void ChangeModeLoop();
	void ChangeMode(int mode);
	bool KillEnemy( DynamicObject* enemy );
	void CollideBonus( DynamicObject* obj );
	void CollideTurleDeath( DynamicObject* enemy );

	//If mario in adult mode, it will become smaller. If it in kid mode, process DieRightAway().
	void Die();
	void DieRightAway();
	void ProcessDying();

	void CollectCoin();

	void UpdateCheckPoint();

	void setLife(int l);
	void setCheckPoint(int cp);
	bool CheckCollisionAgain( DynamicObject* obj );
	bool CheckRectInRect(RECT mainRect, RECT checkRect);
	bool CheckPointInRect(int x, int y, RECT rect);
};
