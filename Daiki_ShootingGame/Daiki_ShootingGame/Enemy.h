#pragma once
#include "DxLib.h"
#include "CharaBase.h"

class Enemy : public CharaBase
{
private:
	int hp;
	int point;
	int shotNum;
	/*int Flag = FALSE;*/

public:
	Enemy(T_Location location);

public:
	virtual void Updata() override;
	virtual void Draw() override;
	virtual void Hit(int damage) override;
	bool HpCheck();
	int GetPoint();
	void Move();
};