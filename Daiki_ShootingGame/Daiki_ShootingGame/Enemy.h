#pragma once
#include "CharaBase.h"
class Enemy : public CharaBase
{
private:
	int hp;
	int point;

public:
	virtual void Updata() override;
	virtual void Draw() override;
	virtual void Hit() override;
	void HpCheck();
	void GetPoint();
};