#include "DxLib.h"
#include "TripleBurstBullet.h"

TripleBurstBullet::TripleBurstBullet(T_Location location, T_Location speed) :
	BulletsBase(location, 5.f, 1, speed)
{
	bulletImage = LoadGraph("images/stg0710-2.png");
}


void TripleBurstBullet::Update()
{
	T_Location newLocation = GetLocation();
	newLocation.x += speed.x;
	newLocation.y += speed.y;
	SetLocation(newLocation);
}

void TripleBurstBullet::Draw()
{
	DrawGraph(GetLocation().x - 5, GetLocation().y - 5, bulletImage, TRUE);
	/*DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(0, 0, 255));*/
}

bool TripleBurstBullet::isScreenOut()
{
	bool ret = ((GetLocation().y + GetRadius()) <= 0);
	if (ret)
	{
		return ret;
	}

	ret = (SCREEN_HEIGHT <= (GetLocation().y - GetRadius()));
	return ret;

	ret = ((GetLocation().x + GetRadius()) <= 0);
	if (ret)
	{
		return ret;
	}

	ret = (SCREEN_WIDTH <= (GetLocation().y - GetRadius()));
	return ret;
}