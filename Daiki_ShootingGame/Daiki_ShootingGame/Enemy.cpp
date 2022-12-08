#include "DxLib.h"
#include "Enemy.h"
#include "StraightBullets.h"
#include "CircleBullet.h"

T_Location locations[4] =
{
	{640, 0},
	{640, 100},
	{1000, 100},
	{280, 100},
};

Enemy::Enemy(T_Location location) : CharaBase(location, 20.f, T_Location{0, 0}), hp(10), point(10), shotNum(0)
{
	bullets = new BulletsBase * [30];
	for (int i = 0; i < 30; i++)
	{
		bullets[i] = nullptr;
	}
}

void Enemy::Updata()
{
	/*T_Location newLocation = GetLocation();
	newLocation.y += speed.y;
	SetLocation(newLocation);*/

	/*speed = { 20,0 };
	T_Location newLocation = GetLocation();
	if (newLocation.x != 1280 && newLocation.y <= 150)
	{
		newLocation.x += speed.x;
		if (newLocation.x >= 1280)
		{
			speed = { 0,1 };
			newLocation.y += speed.y;
		}
		SetLocation(newLocation);
	}
	else if (newLocation.x != 0)
	{
		newLocation.x -= speed.x;
		if (newLocation.x <= 0)
		{
			speed = { 0,1 };
			newLocation.y -= speed.y;
		}
		SetLocation(newLocation);
	}*/

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

	//毎フレーム、弾を発射
	if (bulletCount < 30 && bullets[bulletCount] == nullptr)
	{
		bullets[bulletCount] = new CircleBullet(GetLocation(), 2.f, (10 * shotNum));
		shotNum++;
		/*bullets[bulletCount] = new StraightBullets(GetLocation(), T_Location{ 0, 2 });*/
	}
}

void Enemy::Draw()
{
	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 0, 255));

	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 0, 0));
	for (int bulletCount = 0; bulletCount < 30; bulletCount++)
	{
		//弾切れがないかチェック
		if (bullets[bulletCount] == nullptr)
		{
			break;
		}
		bullets[bulletCount]->Draw();
	}
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