#include "DxLib.h"
#include "Player.h"
#include "StraightBullets.h"
#include "KeyManager.h"

Player::Player(T_Location location) : CharaBase(location, 10.f, T_Location{2, 2}), score(0), life(10)
{
	bullets = new BulletsBase*[30];
	for (int i = 0; i < 30; i++)
	{
		bullets[i] = nullptr;
	}
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
			for (int i = 0; i < 29; i++)
			{
				if (bullets[i] == nullptr)
				{
					bullets[i] = bullets[i + 1];
					bullets[i + 1] = nullptr;
				}
			}
		}
	}

	//左クリックで弾を発射
	if (KeyManager::OnMouseClicked(MOUSE_INPUT_LEFT))
	{
		if (bulletCount < 30 && bullets[bulletCount] == nullptr);
		{
			bullets[bulletCount] = new StraightBullets(GetLocation());
		}
	}
}

void Player::Draw()
{
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

void Player::Hit()
{

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