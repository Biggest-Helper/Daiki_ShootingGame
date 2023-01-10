#include "DxLib.h"
#include "Enemy.h"
#include "StraightBullets.h"
#include "CircleBullet.h"

//移動パターンの型
struct MoveInfo
{
	T_Location targetLocation;
	int pattern;
	int next;
	int waitTimeFlame;
	int attackPattern;
};

//移動のパターン1
MoveInfo moveInfo[10] =
{
	{ 640, 150, 0, 1,   0, 0},
	{1260, 150, 0, 2,   0, 0},
	{   0,   0, 1, 3, 180, 1},
	{  20, 150, 0, 4,   0, 2},
	{   0,   0, 1, 5, 180, 1},
	{1260, 150, 0, 2,   0, 1},
};

T_Location locations[3] =
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

Enemy::Enemy(T_Location location) : CharaBase(location, 20.f, T_Location{5, 1}), hp(10), point(10), shotNum(0)
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

	Move();

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

//エネミーの移動処理(パターン1)
void Enemy::Move()
{
	//エネミーの現在の座標を取得
	T_Location nextLocation = GetLocation();

	//TRUE = エネミーが目標座標に到着したら次の座標を再設定
	if ((nextLocation.y == locations[current].y) && (nextLocation.x == locations[current].x))
	{
		current = next[current];
	}
	else
	{
		
		if (nextLocation.y != locations[current].y)
		{
			//現在のy座標が目標座標yより上の場合
			if (nextLocation.y < locations[current].y)
			{
				nextLocation.y += speed.y;   //エネミーを下側へ移動
				if ((GetLocation().y <= locations[current].y) && (locations[current].y <= nextLocation.y))
				{
					nextLocation.y = locations[current].y;
				}
			}
			//現在のy座標が目標座標yより下の場合
			else
			{
				nextLocation.y -= speed.y;   //エネミーを上側へ移動
				if ((nextLocation.y <= locations[current].y) && (locations[current].y <= GetLocation().y))
				{
					nextLocation.y = locations[current].y;
				}
			}
		}

		if (nextLocation.x != locations[current].x)
		{
			if (nextLocation.x < locations[current].x)
			{
				nextLocation.x += speed.x;
				if ((GetLocation().x <= locations[current].x) && (locations[current].x <= nextLocation.x))
				{
					nextLocation.x = locations[current].x;
				}
			}
			else
			{
				nextLocation.x -= speed.x;
				if ((nextLocation.x <= locations[current].x) && (locations[current].x <= GetLocation().x))
				{
					nextLocation.x = locations[current].x;
				}
			}
		}
	}

	SetLocation(nextLocation);

	/*T_Location newLocation = GetLocation();

	if (newLocation.y <= 100)
	{
		newLocation.y++;
		SetLocation(newLocation);
	}
	else
	{
		speed = { 3,0 };
		if (newLocation.x != 1280 && Flag == FALSE)
		{
			newLocation.x += speed.x;
			SetLocation(newLocation);
			if (newLocation.x >= 1280)
			{
				Flag = TRUE;
			}
		}

		if (newLocation.x != 0 && Flag == TRUE)
		{
			newLocation.x -= speed.x;
			SetLocation(newLocation);
			if (newLocation.x <= 0)
			{
				Flag = FALSE;
			}
		}
	}*/
}