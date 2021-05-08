#include "Freezer.h"
#include "../Castle/Castle.h"

Freezer::Freezer(int id, int arrTime, double health, int spd, int firePower, int reloadPerioud, double d) : Enemy(id, arrTime, health, spd, firePower, reloadPerioud, d)
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
    // Assume there is a function that points to the main castle
    Castle* pCastle;
    double k = (Health > MaxHealth / 2) ? 1 : 0.5;
    double freeze = (double)2 * k * Distance / 100;

    if (pCastle->getFreezingAmount() >= 1) {
        pCastle->setFrozen(true);
        pCastle->setFreezengAmount(0);   
    }
    else {
        pCastle->setFreezengAmount(pCastle->getFreezingAmount() + freeze);   
    }

}
