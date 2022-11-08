#include "GameMainScene.h"

//コンストラクタ
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

//描画以外の更新を実装する
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
				//エネミーとプレイヤーの弾がヒットしている時、
				//エネミーにダメージを与えます。
				enemy[enemyCount]->Hit(bullets[bulletCount]->GetDamage());

				//弾を削除します
				player->DeleteBullet(bulletCount);
				bulletCount--;

				//エネミーのHPが0以下だったら、エネミーを削除します。
				if (enemy[enemyCount]->HpCheck())
				{
					//スコアの加算
					player->AddScore(enemy[enemyCount]->GetPoint());

					//エネミーの削除
					delete enemy[enemyCount];
					enemy[enemyCount] = nullptr;

					/*配列を前に詰める(ソート)*/
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
}

//描画に関することを実装する
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

//シーンの変更処理
AbstractScene* GameMainScene::ChangeScene()
{
	return this;
}