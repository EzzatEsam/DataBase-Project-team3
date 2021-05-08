#include "Fighter.h"
#include "../Castle/Castle.h"

Fighter::Fighter(int id, int arrTime, double health, int spd, int firePower, int reloadPerioud, double d) : Enemy(id, arrTime, health, spd, firePower, reloadPerioud, d)
{
}

Fighter::~Fighter()
{
}

void Fighter::Move()
{
    // If the health is half then the speed is halved as well
    int moveSpd = Speed;
    if (Health < MaxHealth / 2)
        moveSpd /= 2;

    // Move according to such speed
    decDistanceByFactor(moveSpd);
}

void Fighter::Act()
{
    // Assume there is a function that points to the main castle
    Castle* pCastle;
    double k = (Health > MaxHealth / 2) ? 1 : 0.5;
    double dmg = (double)(k / Distance) * FirePower;
    pCastle->SetHealth(pCastle->GetHealth() - dmg);
}
