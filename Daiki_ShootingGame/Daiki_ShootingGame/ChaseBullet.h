#pragma once
#include "BulletsBase.h"
#include "Player.h"

class ChaseBullet : public BulletsBase
{
private:
	Player* player;
	T_Location playerLocation;

public:
	ChaseBullet(T_Location location, T_Location speed);

public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual bool isScreenOut() override;
};