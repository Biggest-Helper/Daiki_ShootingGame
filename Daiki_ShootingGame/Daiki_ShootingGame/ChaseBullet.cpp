#include "DxLib.h"
#include "ChaseBullet.h"
#include "Player.h"
ChaseBullet::ChaseBullet(T_Location location, T_Location speed) :
	BulletsBase(location, 5.f, 1, speed)
{
	playerLocation = T_Location{ 640, 500 };
	player = new Player(playerLocation);
	if (location.y < playerLocation.y)
	{
		if (location.x == playerLocation.x)
		{
			speed = { 0, 3 };
		}
		else if (location.x < playerLocation.x)
		{
			speed = { 3, 3 };
		}
		else if (location.x > playerLocation.x)
		{
			speed = { -3, 3 };
		}
	}
	else
	{
		speed = { 0, 3 };
	}
}


void ChaseBullet::Update()
{
	T_Location newLocation = GetLocation();
	newLocation.x += speed.x;
	newLocation.y += speed.y;
	SetLocation(newLocation);
}

void ChaseBullet::Draw()
{
	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(0, 0, 255));
}

bool ChaseBullet::isScreenOut()
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