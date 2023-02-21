#include "DxLib.h"
#include "common.h"
#include "StraightBullets.h"

StraightBullets::StraightBullets(T_Location location, T_Location speed) :
	BulletsBase(location, 5.f, 1, speed)
{
	bulletImage = LoadGraph("images/stg0710-3.png");
}

void StraightBullets::Update()
{
	T_Location newLocation = GetLocation();
	newLocation.x += speed.x;
	newLocation.y += speed.y;
	SetLocation(newLocation);
}

void StraightBullets::Draw()
{
	/*DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(0, 255, 0));*/
	DrawGraph(GetLocation().x - 5, GetLocation().y - 5, bulletImage, TRUE);
}

bool StraightBullets::isScreenOut()
{
	bool ret = ((GetLocation().y + GetRadius()) <= 0);
	if (ret)
	{
		return ret;
	}

	ret = (SCREEN_HEIGHT <= (GetLocation().y - GetRadius()));
	return ret;
}