#include "DxLib.h"
#include "CircleBullet.h"

#define _USE_MATH_DEFINES
#include "math.h"

CircleBullet::CircleBullet(T_Location location, float speed, int degAngle) :
	BulletsBase(location, 5.f, 1, T_Location{0, 0})
{
	int deg = degAngle % 360;
	double rad = (M_PI / 180) * deg;
	float x = (abs(deg)) == 90 || abs(deg) == 270 ? 0 : cos(rad);
	float y = sin(rad);

	this->speed = T_Location{ (speed * x), (speed * y) };

	bulletImage = LoadGraph("images/stg0710-1.png");
}

void CircleBullet::Update()
{
	T_Location newLocation = GetLocation();
	newLocation.x += speed.x;
	newLocation.y += speed.y;
	SetLocation(newLocation);
}

void CircleBullet::Draw()
{
	DrawGraph(GetLocation().x - 5, GetLocation().y - 5, bulletImage, TRUE);
	/*DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(0, 255, 0));*/
}

bool CircleBullet::isScreenOut()
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
