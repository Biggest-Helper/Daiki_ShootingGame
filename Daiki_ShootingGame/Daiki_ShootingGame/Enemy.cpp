#include "DxLib.h"
#include "Enemy.h"
#include "StraightBullets.h"
#include "CircleBullet.h"
#include "TripleBurstBullet.h"

int next[3] = 
{
	1,
	2,
	1
};

void Enemy::inputCSV()
{
	FILE* fp; // FILE
	errno_t error;  // fopen_s

	error = fopen_s(&fp, "data/T_MoveInformation.csv", "r");
	if (error != 0)
	{
		// 
		return;
	}
	else
	{
		// 
		char line[100];
		for (int i = 0; fgets(line, 100, fp) != NULL; i++)
			//while(fgets(line, 100, fp) != NULL)
		{
			sscanf_s(line, "%d, %f, %f, %d, %d, %d",
				&moveInfo[i].pattern,
				&moveInfo[i].targetLocation.x,
				&moveInfo[i].targetLocation.y,
				&moveInfo[i].next,
				&moveInfo[i].waitTimeFlame,
				&moveInfo[i].attackPattern
			);
		}

		return;
	}

	fclose(fp); //�t�@�C���N���[�Y
}

Enemy::Enemy(T_Location location) : CharaBase(location, 20.f, T_Location{3, 1}), hp(10), point(10), shotNum(0)
{
	inputCSV();

	bullets = new BulletsBase * [200];
	for (int i = 0; i < 200; i++)
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

	default:
		break;
	}



	int bulletCount;
	int bulletMax = 200;
	for (bulletCount = 0; bulletCount < bulletMax; bulletCount++)
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
			for (int i = bulletCount; i < (bulletMax - 1); i++)
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
	if (moveInfo[current].attackPattern != 0)
	{
		if (bulletCount < bulletMax && bullets[bulletCount] == nullptr)
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
			else if (moveInfo[current].attackPattern == 3)
			{
				bullets[bulletCount] = new TripleBurstBullet(GetLocation(), T_Location{ 0,1 });
			}
		}
	}

#define _DEBUG_MODE_PLAYE_

#ifdef _DEBUG_MODE_PLAYE_
	/*DrawFormatString(10, 50, GetColor(255, 255, 255), "x = %lf", GetLocation().x);
	DrawFormatString(10, 70, GetColor(255, 255, 255), "y = %lf", GetLocation().y);*/
#endif
}

void Enemy::Draw()
{
	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 0, 255));

	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 0, 0));
	for (int bulletCount = 0; bulletCount < 200; bulletCount++)
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
	if ((nextLocation.y == moveInfo[current].targetLocation.y) && (nextLocation.x == moveInfo[current].targetLocation.x))
	{
		current = moveInfo[current].next;
		return;
	}
	else
	{
		
		if (nextLocation.y != moveInfo[current].targetLocation.y)
		{
			//���݂�y���W���ڕW���Wy����̏ꍇ
			if (nextLocation.y < moveInfo[current].targetLocation.y)
			{
				nextLocation.y += speed.y;   //�G�l�~�[�������ֈړ�
				if ((GetLocation().y <= moveInfo[current].targetLocation.y) && (moveInfo[current].targetLocation.y <= nextLocation.y))
				{
					nextLocation.y = moveInfo[current].targetLocation.y;
				}
			}
			//���݂�y���W���ڕW���Wy��艺�̏ꍇ
			else
			{
				nextLocation.y -= speed.y;   //�G�l�~�[���㑤�ֈړ�
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