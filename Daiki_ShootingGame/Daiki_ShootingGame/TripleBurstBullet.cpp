#include "DxLib.h"
#include "TripleBurstBullet.h"

TripleBurstBullet::TripleBurstBullet(T_Location location, T_Location speed) :
	BulletsBase(location, 5.f, 1, speed)
{

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
	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(0, 0, 255));
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
}