#include "Castle.h"
#include "../Enemies/Healer.h"
#include "../Enemies/Freezer.h"

Castle::Castle(double health_i)
{
	takenFreeze = 0;
	Health = health_i;
}

Castle::Castle()
{
	takenFreeze = 0;
	Health = 0;
}

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
	if (h > 0)
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

void Castle::Fire(Enemy *pE)
{
	if (Frozen)
	{
		Frozen = false;
		return;
	}
	int k = 1;
	Healer *pHealer = dynamic_cast<Healer *>(pE);
	if (pHealer != nullptr)
		k = 2;
	else
		k = 1;
	double dmg = (1.0 / pE->GetDistance()) * AtkDamage * 1.0 / k;

	pE->increaseHealth(-dmg);
}

bool Castle::Freeze(Enemy *pE)
{
	if (pE->GetStatus() != FRST) {
	pE->SetStatus(FRST);

	Freezer* pFz = dynamic_cast<Freezer*>(pE);
	if (pFz != nullptr)
		pE->Frost_Time_Steps = 3;
	else
		pE->Frost_Time_Steps = 2;
	
	return true;
	}
	else
	{
		return false;
	}
}

void Castle::setFreezengAmount(double val)
{
	takenFreeze = val;
}

double Castle::getFreezingAmount()
{
	return takenFreeze;
}

void Castle::setFrozen(bool val)
{
	Frozen = val;
}

bool Castle::getFrozen()
{
	return Frozen;
}

double Castle::getMaxFreezeAmount()
{
	return Accumelated_Freezing_Amount;
}

int Castle::getN()
{
	return AtkNum;
}
