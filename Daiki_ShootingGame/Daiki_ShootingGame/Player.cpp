#include "DxLib.h"
#include "Player.h"
#include "StraightBullets.h"
#include "KeyManager.h"
#include "Recovery.h"

Player::Player(T_Location location) : CharaBase(location, 10.f, T_Location{2, 2}), score(0), life(10)
{
	bullets = new BulletsBase*[30];
	for (int i = 0; i < 30; i++)
	{
		bullets[i] = nullptr;
	}

	playerImage = LoadGraph("images/gramteril051004a.png");
}

void Player::Updata()
{
	T_Location newLocation = GetLocation();

	if (KeyManager::OnKeyPressed(KEY_INPUT_W))
	{
		newLocation.y -= speed.y;
	}

	if(KeyManager::OnKeyPressed(KEY_INPUT_A))
	{
		newLocation.x -= speed.x;
	}

	if(KeyManager::OnKeyPressed(KEY_INPUT_S))
	{
		newLocation.y += speed.y;
	}

	if(KeyManager::OnKeyPressed(KEY_INPUT_D))
	{
		newLocation.x += speed.x;
	}

	/*newLocation.x += 1;*/
	SetLocation(newLocation);

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

			/* 同じ処理内容 */
			/*for (int i = bulletCount + 1; i < 30; i++)
			{
				if (bullets[i] == nullptr)
				{
					break;
				}
				bullets[i - 1] = bullets[i];
				bullets[i] = nullptr;
			}*/

			bulletCount--;
		}
	}

	//左クリックで弾を発射
	if (KeyManager::OnMouseClicked(MOUSE_INPUT_LEFT))
	{
		if (bulletCount < 30 && bullets[bulletCount] == nullptr);
		{
			bullets[bulletCount] = new StraightBullets(GetLocation(), T_Location{0, -3});
		}
	}
}

void Player::Draw()
{
#define _DEBUG_MODE_

#ifdef _DEBUG_MODE_
	DrawFormatString(10, 10, GetColor(255, 255, 255), "Life = %d", life);
	DrawFormatString(10, 30, GetColor(255, 255, 255), "Score = %d", score);
#endif

	/*DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 0, 0));*/
	for (int bulletCount = 0; bulletCount < 30; bulletCount++)
	{
		//弾切れがないかチェック
		if (bullets[bulletCount] == nullptr)
		{
			break;
		}
		bullets[bulletCount]->Draw();
	}

	DrawGraph(GetLocation().x - 24, GetLocation().y - 24, playerImage, TRUE);
}

void Player::Hit(int damage)
{
	if (0 <= damage)
	{
		life -= damage;

		if (life <= 0)
		{
			life = 0;
		}
	}
}

void Player::Hit(ItemBase* item)
{
	switch (item->GetType())
	{
	case E_ITEM_TYPE::Heal:
	{
		Recovery* recovery = dynamic_cast<Recovery*>(item);
		life += recovery->GetRecovery_PT();
		break;
	}
	default:
		break;
	}
}

bool Player::LifeCheck()
{
	bool ret = (life <= 0);
	return ret;
}

int Player::GetScore()
{
	return score;
}

void Player::AddScore(int score)
{
	if (0 <= score)
	{
		this->score += score;
	}
}