#include "Dxlib.h"
#include "Recovery.h"

Recovery::Recovery(T_Location location) : 
	ItemBase(location, 5.f, E_ITEM_TYPE::Heal, T_Location{0, 10}), recovery_pt(2)
{

}

void Recovery::Updata()
{
	T_Location newLocation = GetLocation();
	newLocation.y += speed.y;
	SetLocation(newLocation);
}

void Recovery::Draw()
{
	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 255, 255));
}

int Recovery::GetRecovery_PT()
{
	return recovery_pt;
}