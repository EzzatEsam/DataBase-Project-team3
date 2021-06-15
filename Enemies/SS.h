#pragma once
#include "Enemy.h"
#include "../Castle/Castle.h"

class SS : public Enemy
{
private:
public:
    SS(int id, int arrTime, double health, int spd, int firePower, int reloadPerioud, double d = MaxDistance);
    virtual ~SS();
    virtual void Move();
    virtual void Act();
    void Act(Enemy*);

};
