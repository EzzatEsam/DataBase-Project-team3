#include "Castle.h"




void Castle::SetHealth(double h)
{
	if(h > 0)
		Health = h;
	else
		Health = 0; // killed
}

double Castle::GetHealth() const
{
	return Health;
}

void Castle::Fire(Enemy* pE)
{
	double dmg = (1.0 / pE->GetDistance()) * firePower
}
