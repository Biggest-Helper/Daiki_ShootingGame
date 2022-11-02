#include "CharaBase.h"

CharaBase::CharaBase(T_Location location, float radius, T_Location speed) : 
	SphereCollider(location, radius), speed(speed), image(nullptr), bullets(nullptr)
{

}

BulletsBase** CharaBase::GetBullets()
{
	return bullets;
}

void CharaBase::DeleteBullet(int bulletNum)
{
	delete bullets[bulletNum];
	bullets[bulletNum] = nullptr;

	/*配列を前に詰める(ソート)*/
	for (int i = bulletNum; i < (30 - 1); i++)
	{
		if (bullets[i + 1] == nullptr)
		{
			break;
		}
		bullets[i] = bullets[i + 1];
		bullets[i + 1] = nullptr;
	}
}