#include "Castle.h"




void Castle::SetAtkNum(int n)
{
	AtkNum = n;
}

void Castle::SetAtkDamage(int d)
{
	AtkDamage = d;
}

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

int Castle::GetAtkDamage() const
{
	return AtkDamage;
}

int Castle::GetAtkNum() const
{
	return AtkNum;
}
