#include "Dxlib.h"
#include "Recovery.h"

void Recovery::Updata()
{

}

void Recovery::Draw()
{
	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 255, 255));
}

int Recovery::GetRecovery_PT()
{
	return recovery_pt;
}