#pragma once
#include "ItemBase.h"
class Recovery : public ItemBase
{
private:
	int recovery_pt;

public:
	Recovery(T_Location location);

public:
	virtual void Updata() override;
	virtual void Draw() override;
	int GetRecovery_PT();
};