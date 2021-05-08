#pragma once
#include "Enemy.h"
class Fighter :
    public Enemy
{
public:

    Fighter(int id, int arrTime, double health, int spd, int firePower, int reloadPerioud, double d)    void Move();
    void Act();
};

