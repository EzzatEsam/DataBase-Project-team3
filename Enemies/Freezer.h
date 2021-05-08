#pragma once
#include "Enemy.h"
class Freezer :
    public Enemy
{
public:
    Freezer(int id, int arrive, int hp, int atk, int relode, int ms);
    void Move();
    void Act();
};



