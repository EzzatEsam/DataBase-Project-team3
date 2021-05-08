#include "Freezer.h"

Freezer::Freezer(int id, int arrTime, double health, int spd, int firePower, int reloadPerioud, double d) :
	Enemy(id, arrTime, health, spd, firePower, reloadPerioud, d)
{
}

Freezer::~Freezer()
{
}

void Freezer::Move()
{
	// If the health is half then the speed is halved as well
	int moveSpd = Speed;
	if (Health < MaxHealth / 2)
		moveSpd /= 2;

	// Move according to such speed
	decDistanceByFactor(moveSpd);
}

void Freezer::Act()
{
}

