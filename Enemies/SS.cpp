#include "SS.h"
#include <iostream>
using namespace std;


SS::SS(int id, int arrTime, double health, int spd, int firePower, int reloadPerioud, double d) : Enemy(id, arrTime, health, spd, firePower, reloadPerioud, d)
{
    SetStatus(ACTV);
}

SS::~SS()
{
}

void SS::Move()
{
    //// If the health is half then the speed is halved as well
    //int moveSpd = Speed;
    //if (Health < MaxHealth / 2)
    //    moveSpd /= 2;

    //// Move according to such speed
    //decDistanceByFactor(moveSpd);
}

void SS::Act()
{
}

void SS::Move(int Final_Distination)
{
    int moveSpd = 3;

    if (Distance + moveSpd > Final_Distination)
        Distance = Final_Distination;
    else
        Distance += moveSpd;
}

void SS::Act(Enemy* pE)
{
    /*double k = (Health > MaxHealth / 2) ? 1 : 0.5;
    double dmg = (double)(k / Distance) * FirePower;
    pCastle->SetHealth(pCastle->GetHealth() - dmg);*/
}

