#pragma once
#include "Enemy.h"
class Fighter :
    public Enemy
{
public:

    Fighter(int id, int arrive, int hp, int atk, int relode, int ms);
    void Move();
    void Act();
};

