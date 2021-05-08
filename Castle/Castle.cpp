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
	int k = 1;
	Healer* pHealer = dynamic_cast<Healer*>(pE);
	if (pHealer != nullptr)
		k = 2;
	else
		k = 1;
	double dmg = (1.0 / pE->GetDistance()) * firePower * 1.0 / k;

	pE->increaseHealth(-dmg);
}

void Castle::Freeze(Enemy* pE)
{
	pE->SetStatus(FRST);
}
