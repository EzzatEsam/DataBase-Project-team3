#include "Enemy.h"

Enemy::Enemy(int id, int arrTime, double d) : ID(id), ArrvTime(arrTime)
{
	SetDistance(d);
}

Enemy::Enemy(int id, int arrTime, double health, int spd, int firePower, int reloadPeriod, double d) : ID(id), ArrvTime(arrTime), Speed(spd), Health(health), FirePower(firePower), ReloadPeriod(reloadPeriod), ReloadPerioudTmp(reloadPeriod)
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

void Enemy::SetFirstShotTime(int t)
{
	if (takenTakenDamage)
	{
		return;
	}
	takenTakenDamage = true;
	FirstShotTime = t;
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

int Enemy::GetDeathTime() const
{
	return DeathTime;
}

int Enemy::GetArrvTime() const
{
	return ArrvTime;
}

void Enemy::iceMove()
{
	// If the health is half then the speed is halved as well
	int moveSpd = floor(Speed * Accumuilated_Ice);

	// Move according to such speed
	decDistanceByFactor(moveSpd);
}

void Enemy::decDistanceByFactor(double factor)
{
	if (Distance - factor > MinDistance)
		Distance -= factor;
	else
		Distance = MinDistance;
}

void Enemy::setHealth(double val)
{
	Health = val;
}

double Enemy::getHealth()
{
	return Health;
}

int Enemy::getPower()
{
	return FirePower;
}

void Enemy::increaseHealth(double val)
{
	Health += val;
}
