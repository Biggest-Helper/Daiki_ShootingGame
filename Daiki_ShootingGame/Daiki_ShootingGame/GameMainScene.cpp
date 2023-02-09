#include "GameMainScene.h"
#include "GameOverScene.h"
#include "GameClearScene.h"
#include "Recovery.h"
#include "common.h"

//コンストラクタ
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

//描画以外の更新を実装する
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
				//エネミーとプレイヤーの弾がヒットしている時、
				//エネミーにダメージを与えます。
				enemy[enemyCount]->Hit(bullets[bulletCount]->GetDamage());

				//弾を削除します
				player->DeleteBullet(bulletCount);
				bulletCount--;

				//エネミーのHPが0以下だったら、エネミーを削除します。
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

	//敵の弾を取得
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

			//弾をループで参照
			for (int i = 0; i < 30; i++)
			{
				if (bullet[i] == nullptr)
				{
					break;
				}

				if (player->HitSphere(bullet[i]))
				{
					//プレイヤーにダメージを与える
					player->Hit(bullet[i]->GetDamage());

					//敵の弾を削除する;
					enemy[enemyCount]->DeleteBullet(i);
				}
			}
		}
	}

	//敵の弾を取ってくる;
	//for(弾をループで参照)
	//{
	//  if(敵の弾と プレイヤーの当たり判定)
	//  {
	//     プレイヤーにダメージを与える;
	//
	//     敵の弾を削除する;
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
			//回復処理
			player->Hit(items[itemCount]);

			delete items[itemCount];
			items[itemCount] = nullptr;

			/*配列を前に詰める(ソート)*/
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

	for (int i = 0; i < 10; i++)
	{
		if (items[i] == nullptr)
		{
			break;
		}
		items[i]->Draw();
	}
}

//シーンの変更処理
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