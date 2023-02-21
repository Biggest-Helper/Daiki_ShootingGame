#pragma once
#include "CharaBase.h"
class Player : public CharaBase
{
private:
	int score;
	int life;
	int playerImage = 0;

public:
	Player(T_Location location);

public:
	void Updata() override;
	void Draw() override;
	void Hit(int damage) override;
	bool LifeCheck();
	int GetScore();
	void AddScore(int score);
	void Hit(class ItemBase* item);
};