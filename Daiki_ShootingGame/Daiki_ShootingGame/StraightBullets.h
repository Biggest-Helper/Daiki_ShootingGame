#pragma once
#include "BulletsBase.h"
class StraightBullets : public BulletsBase
{
private:
	int bulletImage = 0;
public:
	StraightBullets(T_Location location, T_Location speed);

public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual bool isScreenOut() override;
};