#pragma once
#include "BulletsBase.h"
class TripleBurstBullet : public BulletsBase
{
private:
	int bulletImage = 0;

public:
	TripleBurstBullet(T_Location location, T_Location speed);

public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual bool isScreenOut() override;
};