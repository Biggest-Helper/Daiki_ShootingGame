#include "GameMainScene.h"

//�R���X�g���N�^
GameMainScene::GameMainScene()
{
	T_Location location = T_Location{ 20, 100 };
	player = new Player(location);

	enemy = new Enemy * [10];
	for (int i = 0; i < 10; i++)
	{
		enemy[i] = nullptr;
	}
	enemy[0] = new Enemy(T_Location{ 200, 0 });

}

//�`��ȊO�̍X�V����������
void GameMainScene::Update()
{
	player->Updata();

	int enemyCount;
	for (enemyCount = 0; enemyCount < 10; enemyCount++)
	{
		if (enemy[enemyCount] == nullptr)
		{
			break;
		}
		enemy[enemyCount]->Updata();
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
}

//�V�[���̕ύX����
AbstractScene* GameMainScene::ChangeScene()
{
	return this;
}