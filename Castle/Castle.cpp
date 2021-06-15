#include "Castle.h"
#include "../Enemies/Healer.h"
#include "../Enemies/Freezer.h"

Castle::Castle(double health_i)
{
	takenFreeze = 0;
	Health = health_i;
	MaxHealth = Health;
}

Castle::Castle()
{
	takenFreeze = 0;
	Health = 0;
	MaxHealth = Health;
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

void Castle::Fire(Enemy *pE, int CurrentTimeStep)
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
	castleTotalDamage += dmg;
	pE->increaseHealth(-dmg);
	pE->SetFirstShotTime(CurrentTimeStep);
	
}

bool Castle::Freeze(Enemy *pE, int CurrentTimeStep)
{
	//A frosted enemy is affected by castle fire but is not affected by castle ice
	if (pE->GetStatus() != FRST) {
	pE->SetStatus(FRST);

	Freezer* pFz = dynamic_cast<Freezer*>(pE);
	if (pFz != nullptr)
		pE->Frost_Time_Steps = 4;
	else
		pE->Frost_Time_Steps = 3;
	
	pE->SetFirstShotTime(CurrentTimeStep);
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
