#pragma once
#include "DxLib.h"
#include "CharaBase.h"

//ˆÚ“®ƒpƒ^[ƒ“‚ÌŒ^
struct MoveInfo
{
	int pattern;
	T_Location targetLocation;
	int next;
	int waitTimeFlame;
	int attackPattern;
};

class Enemy : public CharaBase
{
private:
	int hp;
	int point;
	int shotNum;
	/*int Flag = FALSE;*/
	MoveInfo moveInfo[5] = {};

	int current = 0;
	int WaitCount = 0;

	int enemyImage = 0;

	void inputCSV();

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