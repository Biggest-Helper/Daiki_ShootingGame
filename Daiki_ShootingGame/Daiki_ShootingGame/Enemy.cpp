#include "DxLib.h"
#include "Enemy.h"
#include "StraightBullets.h"

Enemy::Enemy(T_Location location) : CharaBase(location, 20.f, T_Location{0, 0.5}), hp(10), point(10)
{

}

void Enemy::Updata()
{
	T_Location newLocation = GetLocation();
	newLocation.y += speed.y;
	SetLocation(newLocation);

	int bulletCount;
	for (bulletCount = 0; bulletCount < 30; bulletCount++)
	{
		//弾切れがないかチェック
		if (bullets[bulletCount] == nullptr)
		{
			break;
		}
		bullets[bulletCount]->Update();

		//画面外に行ったら弾を消す
		if (bullets[bulletCount]->isScreenOut())
		{
			delete bullets[bulletCount];
			bullets[bulletCount] = nullptr;

			/*配列を前に詰める(ソート)*/
			for (int i = bulletCount; i < (30 - 1); i++)
			{
				if (bullets[i + 1] == nullptr)
				{
					break;
				}
				bullets[i] = bullets[i + 1];
				bullets[i + 1] = nullptr;
			}
			bulletCount--;
		}
	}

	//弾発射処理
	if (bulletCount < 30 && bullets[bulletCount] == nullptr);
	{
		bullets[bulletCount] = new StraightBullets(GetLocation());
	}
}

void Enemy::Draw()
{
	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 0, 255));
}

void Enemy::Hit(int damage)
{
	if (0 < damage)
	{
		hp -= damage;
		if (hp < 0)
		{
			hp = 0;
		}
	}
}

bool Enemy::HpCheck()
{
	bool ret = (hp <= 0);
	return ret;
}

int Enemy::GetPoint()
{
	return point;
}