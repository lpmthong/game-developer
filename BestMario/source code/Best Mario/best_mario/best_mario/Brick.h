#pragma once
#include "StaticObject.h"
#include "ListTexture.h"

class Brick : public StaticObject {

protected:

	DWORD lastCollide; //Thoi gian ma lan cuoi mario va cham vao cuc gach
	bool isHardBrick; //Cai nay gach thuong thi chua can dung nhung sau nay may cai bonus coin hay bonus star thi can de xem no rong chua
	int distancemoveup; // cai nay de dich chuyen len khi player kid va cham duoi
public:

	bool hasCollide; //Co va cham voi player hay khong de xu li va cham
	bool alive; //Trang thai cua cuc gach

public:

	Brick(void);
	Brick(int left, int top, int iid);

	virtual void ProcessCollision(int iKind); // Xu li khi va cham xay ra

	virtual void BonusAppear(); // cam nay de sau nay may lop khac ke thua

	virtual void SetEmpty();

	virtual void Update();
	void UpdateSprite();

	~Brick(void);

};