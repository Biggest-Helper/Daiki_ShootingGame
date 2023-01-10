#include "DxLib.h"
#include "Enemy.h"
#include "StraightBullets.h"
#include "CircleBullet.h"

//�ړ��p�^�[���̌^
struct MoveInfo
{
	T_Location targetLocation;
	int pattern;
	int next;
	int waitTimeFlame;
	int attackPattern;
};

//�ړ��̃p�^�[��1
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

//�G�l�~�[�̈ړ�����(�p�^�[��1)
void Enemy::Move()
{
	//�G�l�~�[�̌��݂̍��W���擾
	T_Location nextLocation = GetLocation();

	//TRUE = �G�l�~�[���ڕW���W�ɓ��������玟�̍��W���Đݒ�
	if ((nextLocation.y == locations[current].y) && (nextLocation.x == locations[current].x))
	{
		current = next[current];
	}
	else
	{
		
		if (nextLocation.y != locations[current].y)
		{
			//���݂�y���W���ڕW���Wy����̏ꍇ
			if (nextLocation.y < locations[current].y)
			{
				nextLocation.y += speed.y;   //�G�l�~�[�������ֈړ�
				if ((GetLocation().y <= locations[current].y) && (locations[current].y <= nextLocation.y))
				{
					nextLocation.y = locations[current].y;
				}
			}
			//���݂�y���W���ڕW���Wy��艺�̏ꍇ
			else
			{
				nextLocation.y -= speed.y;   //�G�l�~�[���㑤�ֈړ�
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