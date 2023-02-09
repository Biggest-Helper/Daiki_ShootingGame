#include "GameMainScene.h"
#include "GameOverScene.h"
#include "GameClearScene.h"
#include "Recovery.h"
#include "common.h"

//�R���X�g���N�^
GameMainScene::GameMainScene()
{
	T_Location location = T_Location{ 640, 500 };
	player = new Player(location);

	enemy = new Enemy * [10];
	for (int i = 0; i < 10; i++)
	{
		enemy[i] = nullptr;
	}
	enemy[0] = new Enemy(T_Location{SCREEN_WIDTH / 2, -30});
	enemyCount = 0;

	items = new ItemBase * [10];
	for (int i = 0; i < 10; i++)
	{
		items[i] = nullptr;
	}
}

//�`��ȊO�̍X�V����������
void GameMainScene::Update()
{
	player->Updata();

	
	for (enemyCount = 0; enemyCount < 10; enemyCount++)
	{
		if (enemy[enemyCount] == nullptr)
		{
			break;
		}
		enemy[enemyCount]->Updata();
	}

	for (int i = 0; i < 10; i++)
	{
		if (items[i] == nullptr)
		{
			break;
		}
		items[i]->Updata();
	}

	int bulletCount;
	BulletsBase** bullets = player->GetBullets();
	for (enemyCount = 0; enemyCount < 10; enemyCount++)
	{
		if (enemy[enemyCount] == nullptr)
		{
			break;
		}

		for (bulletCount = 0; bulletCount < 30; bulletCount++)
		{
			if (bullets[bulletCount] == nullptr)
			{
				break;
			}

			if (enemy[enemyCount]->HitSphere(bullets[bulletCount]))
			{
				//�G�l�~�[�ƃv���C���[�̒e���q�b�g���Ă��鎞�A
				//�G�l�~�[�Ƀ_���[�W��^���܂��B
				enemy[enemyCount]->Hit(bullets[bulletCount]->GetDamage());

				//�e���폜���܂�
				player->DeleteBullet(bulletCount);
				bulletCount--;

				//�G�l�~�[��HP��0�ȉ���������A�G�l�~�[���폜���܂��B
				if (enemy[enemyCount]->HpCheck())
				{
					for (int i = 0; i < 10; i++)
					{
						if (items[i] == nullptr)
						{
							items[i] = new Recovery(enemy[enemyCount]->GetLocation());
							break;
						}
					}

					//�X�R�A�̉��Z
					player->AddScore(enemy[enemyCount]->GetPoint());

					//�G�l�~�[�̍폜
					delete enemy[enemyCount];
					enemy[enemyCount] = nullptr;

					/*�z���O�ɋl�߂�(�\�[�g)*/
					for (int i = enemyCount; i < (10 - 1); i++)
					{
						if (enemy[i + 1] == nullptr)
						{
							break;
						}
						enemy[i] = enemy[i + 1];
						enemy[i + 1] = nullptr;
					}
					enemyCount--;
					break;
				}
			}
		}
	}

	//�G�̒e���擾
	BulletsBase** bullet = player->GetBullets();
	for (enemyCount = 0; enemyCount < 10; enemyCount++)
	{
		for (enemyCount; enemyCount < 10; enemyCount++)
		{
			if (enemy[enemyCount] == nullptr)
			{
				break;
			}
			bullet = enemy[enemyCount]->GetBullets();

			//�e�����[�v�ŎQ��
			for (int i = 0; i < 30; i++)
			{
				if (bullet[i] == nullptr)
				{
					break;
				}

				if (player->HitSphere(bullet[i]))
				{
					//�v���C���[�Ƀ_���[�W��^����
					player->Hit(bullet[i]->GetDamage());

					//�G�̒e���폜����;
					enemy[enemyCount]->DeleteBullet(i);
				}
			}
		}
	}

	//�G�̒e������Ă���;
	//for(�e�����[�v�ŎQ��)
	//{
	//  if(�G�̒e�� �v���C���[�̓����蔻��)
	//  {
	//     �v���C���[�Ƀ_���[�W��^����;
	//
	//     �G�̒e���폜����;
	//  }
	//}

	for (int itemCount = 0; itemCount < 10; itemCount++)
	{
		if (items[itemCount] == nullptr)
		{
			break;
		}

		if (items[itemCount]->HitSphere(player) == true)
		{
			//�񕜏���
			player->Hit(items[itemCount]);

			delete items[itemCount];
			items[itemCount] = nullptr;

			/*�z���O�ɋl�߂�(�\�[�g)*/
			for (int i = itemCount; i < (10 - 1); i++)
			{
				if (items[i + 1] == nullptr)
				{
					break;
				}
				items[i] = items[i + 1];
				items[i + 1] = nullptr;
			}
			itemCount--;
		}
	}
}

//�`��Ɋւ��邱�Ƃ���������
void GameMainScene::Draw() const
{
	player->Draw();

	int enemyCount;
	for (enemyCount = 0; enemyCount < 10; enemyCount++)
	{
		if (enemy[enemyCount] == nullptr)
		{
			break;
		}
		enemy[enemyCount]->Draw();
	}

	for (int i = 0; i < 10; i++)
	{
		if (items[i] == nullptr)
		{
			break;
		}
		items[i]->Draw();
	}
}

//�V�[���̕ύX����
AbstractScene* GameMainScene::ChangeScene()
{
	if (player->LifeCheck() == true)
	{
		return new GameOverScene;
	}

	for (enemyCount = 0; enemyCount < 10; enemyCount++)
	{
		if (enemy[enemyCount] != nullptr)
		{
			break;
		}
		else if (enemy[9] == nullptr)
		{
			return new GameClearScene;
		}
	}

	return this;
}