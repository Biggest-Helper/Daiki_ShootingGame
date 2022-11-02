#pragma once
#include "SphereCollider.h"
#include "BulletsBase.h"
class CharaBase : public SphereCollider
{
protected:
	T_Location speed;
	int* image;
	BulletsBase** bullets;

public:
	CharaBase(T_Location location, float radius, T_Location speed);

public:
	virtual void Updata() = 0;
	virtual void Draw() = 0;
	virtual void Hit(int damage) = 0;
	BulletsBase** GetBullets();
	void DeleteBullet(int bulletNum);
};