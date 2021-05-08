#include "Enemy.h"


Enemy::Enemy(int id, int arrTime, double d):ID(id),ArrvTime(arrTime)
{
	SetDistance(d);
}

Enemy::Enemy(int id, int arrTime, double health, int spd, int firePower, int reloadPeriod, double d):
	ID(id), ArrvTime(arrTime), Speed(spd), Health(health), FirePower(firePower), ReloadPeriod(reloadPeriod)
{
	SetDistance(d);
	MaxHealth = health;
}

Enemy::~Enemy()
{
}

int Enemy::GetID() const
{
	return ID;
}


void Enemy::SetStatus(ENMY_STATUS s)
{
	status = s;
}


ENMY_STATUS Enemy::GetStatus() const
{
	return status;
}


void Enemy::DecrementDist()
{
	if (Distance > MinDistance)
		Distance--;
}

void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else
		Distance = MaxDistance;
}

int Enemy::GetDistance() const
{
	return Distance;
}



int Enemy::GetArrvTime() const
{
	return ArrvTime;
}

void Enemy::decDistanceByFactor(double factor)
{
	if (Distance > MinDistance)
		Distance -= factor;
}

void Enemy::setHealth(double val)
{
	Health = val;
}

double Enemy::getHealth()
{
	return Health;
}

void Enemy::increaseHealth(double val)
{
	Health += val;
}
