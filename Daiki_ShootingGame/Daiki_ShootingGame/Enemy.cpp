#include "DxLib.h"
#include "Enemy.h"
#include "StraightBullets.h"
#include "CircleBullet.h"

//移動パターンの型
struct MoveInfo
{
	int pattern;
	T_Location targetLocation;
	int next;
	int waitTimeFlame;
	int attackPattern;
};

MoveInfo moveInfo[5] =
{
	{0,    640, 150, 1,   0, 0},
	{0, 1200.4, 150, 2,   0, 2},
	{1,      0,   0, 3, 300, 1},
	{0,   80.2, 150, 4,   0, 2},
	{1,      0,   0, 1, 300, 1}
};

T_Location locations[4] =
{
	{640, 150},
	{1260, 150},
	{20, 150}
};

int next[3] = 
{
	1,
	2,
	1
};

int current = 0;
int WaitCount = 0;

Enemy::Enemy(T_Location location) : CharaBase(location, 20.f, T_Location{3, 1}), hp(10), point(10), shotNum(0)
{
	bullets = new BulletsBase * [30];
	for (int i = 0; i < 30; i++)
	{
		bullets[i] = nullptr;
	}
}



void Enemy::Updata()
{
	switch (moveInfo[current].pattern)
	{
	case 0:
		Move();
		break;

	case 1:
		WaitCount++;
		if (moveInfo[current].waitTimeFlame <= WaitCount)
		{
			WaitCount = 0;
			current = moveInfo[current].next;
		}
		break;

	case 2:


	default:
		break;
	}

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
	if (moveInfo[current].attackPattern != 0)
	{
		if (bulletCount < 30 && bullets[bulletCount] == nullptr)
		{
			if(moveInfo[current].attackPattern == 1)
			{
				bullets[bulletCount] = new StraightBullets(GetLocation(), T_Location{ 0, 2 });
			}
			else if (moveInfo[current].attackPattern == 2)
			{
				bullets[bulletCount] = new CircleBullet(GetLocation(), 2.f, (20 * shotNum));
				shotNum++;
				/*bullets[bulletCount] = new StraightBullets(GetLocation(), T_Location{ 0, 2 });*/
			}
		}
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

//エネミーの移動処理(パターン1)
void Enemy::Move()
{
	//エネミーの現在の座標を取得
	T_Location nextLocation = GetLocation();

	//TRUE = エネミーが目標座標に到着したら次の座標を再設定
	if ((nextLocation.y == moveInfo[current].targetLocation.y) && (nextLocation.x == moveInfo[current].targetLocation.x))
	{
		current = moveInfo[current].next;
		return;
	}
	else
	{
		
		if (nextLocation.y != moveInfo[current].targetLocation.y)
		{
			//現在のy座標が目標座標yより上の場合
			if (nextLocation.y < moveInfo[current].targetLocation.y)
			{
				nextLocation.y += speed.y;   //エネミーを下側へ移動
				if ((GetLocation().y <= moveInfo[current].targetLocation.y) && (moveInfo[current].targetLocation.y <= nextLocation.y))
				{
					nextLocation.y = moveInfo[current].targetLocation.y;
				}
			}
			//現在のy座標が目標座標yより下の場合
			else
			{
				nextLocation.y -= speed.y;   //エネミーを上側へ移動
				if ((nextLocation.y <= moveInfo[current].targetLocation.y) && (moveInfo[current].targetLocation.y <= GetLocation().y))
				{
					nextLocation.y = moveInfo[current].targetLocation.y;
				}
			}
		}

		if (nextLocation.x != moveInfo[current].targetLocation.x)
		{
			if (nextLocation.x < moveInfo[current].targetLocation.x)
			{
				nextLocation.x += speed.x;
				if ((GetLocation().x <= moveInfo[current].targetLocation.x) && (moveInfo[current].targetLocation.x <= nextLocation.x))
				{
					nextLocation.x = moveInfo[current].targetLocation.x;
				}
			}
			else
			{
				nextLocation.x -= speed.x;
				if ((nextLocation.x <= moveInfo[current].targetLocation.x) && (moveInfo[current].targetLocation.x <= GetLocation().x))
				{
					nextLocation.x = moveInfo[current].targetLocation.x;
				}
			}
		}
	}

	SetLocation(nextLocation);
}