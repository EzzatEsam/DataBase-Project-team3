#include "Healer.h"
#include <iostream>
using namespace std;
Healer::Healer(int id, int arrTime, double health, int spd, int firePower, int reloadPerioud, double d) : Enemy(id, arrTime, health, spd, firePower, reloadPerioud, d)
{
}

Healer::~Healer()
{
}

void Healer::Move()
{
    // If the health is half then the speed is halved as well
    int moveSpd = Speed;
    if (Health < MaxHealth / 2)
        moveSpd /= 2;

    // Backward Movement
    if (Distance == MinDistance)
        MoveBackwardFlag = true;

    if (MoveBackwardFlag)
    {
        if (Distance == MaxDistance)
            MoveBackwardFlag = false;
        else
            Distance = (Distance + moveSpd > MaxDistance) ? 60 : Distance + moveSpd;
    }
    else
        decDistanceByFactor(moveSpd);

}

void Healer::Act()
{
}

void Healer::Act(Enemy* pEnemy)
{

    // Get k (To know which enemy to heal)
    int k;
    bool continue_flag = false; 
    if (MoveBackwardFlag && (pEnemy->GetDistance() - Distance <= 2)) {
        k = 1;
        continue_flag = true;
    }
    else if (!MoveBackwardFlag && (Distance - pEnemy->GetDistance() <= 2)) {
        k = 1;
        continue_flag = true;
    }
    else
        k = 0;

    //heal only active Enemy
    if (pEnemy->GetStatus() != FRST && continue_flag)
    {
        double addedHealth = (0.06 * Health + 0.01 * pEnemy->getHealth()) * 0.01 * k;
        pEnemy->increaseHealth(addedHealth);
    }
}
