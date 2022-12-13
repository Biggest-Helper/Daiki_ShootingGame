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

	T_Location newLocation = GetLocation();
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
	}

	int bulletCount;
	for (bulletCount = 0; bulletCount < 30; bulletCount++)
	{
		//�e�؂ꂪ�Ȃ����`�F�b�N
		if (bullets[bulletCount] == nullptr)
		{
			break;
		}
		bullets[bulletCount]->Update();

		//��ʊO�ɍs������e������
		if (bullets[bulletCount]->isScreenOut())
		{
			delete bullets[bulletCount];
			bullets[bulletCount] = nullptr;

			/*�z���O�ɋl�߂�(�\�[�g)*/
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

	//���t���[���A�e�𔭎�
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
		//�e�؂ꂪ�Ȃ����`�F�b�N
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